#include "platform/audio/audio.h"

#include "graphics/animation.h"
#include "platform/audio/audio_beat_detector.h"
#include "platform/audio/audio_peak_detector.h"
#include "platform/wayland.h"
#include "utils/memory.h"

#include <cassert>
#include <cctype>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fcntl.h>
#include <poll.h>
#include <pthread.h>
#include <stdatomic.h>
#include <sys/eventfd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <unistd.h>
#ifdef __GLIBC__
#  include <malloc.h>
#endif

#include <pipewire/pipewire.h>
#include <spa/param/audio/format-utils.h>
extern "C" {
#include <cavacore.h>
}

namespace bongocat::platform::audio {

// Audio format
static constexpr size_t SAMPLE_RATE_HZ = 24000;
static constexpr size_t SAMPLE_SIZE_BYTES = sizeof(sample_buffer_bytes_t);  // 8 bytes

static constexpr size_t SAMPLE_BUFFER_FRAMES = 4096;

static_assert(SAMPLE_RATE_HZ > 0);
static constexpr size_t SAMPLE_BUFFER_SIZE = SAMPLE_BUFFER_FRAMES * MAX_CHANNELS;
static constexpr size_t SAMPLE_BUFFER_BYTES = SAMPLE_BUFFER_SIZE * SAMPLE_SIZE_BYTES;
static constexpr double SAMPLE_BUFFER_MS =
    1000.0 * static_cast<double>(SAMPLE_BUFFER_FRAMES) / SAMPLE_RATE_HZ;  // ~170.7 ms
static_assert(SAMPLE_BUFFER_MS >= 170.0);
static_assert(SAMPLE_BUFFER_BYTES == 32 * 1024);
static_assert(SAMPLE_BUFFER_SIZE > 0);

static constexpr int MAX_ATTEMPTS = 2048;

static constexpr time_ms_t AUDIO_POOL_TIMEOUT_MS = 1000;
static constexpr time_ms_t COND_STORED_TIMEOUT_MS = 1000;
static constexpr time_ms_t THREAD_SLEEP_MS = 1000;

static constexpr time_ms_t COND_ANIMATION_TRIGGER_INIT_TIMEOUT_MS = 5000;
static constexpr time_ms_t COND_RELOAD_CONFIGS_TIMEOUT_MS = 5000;

static constexpr int CAVA_AUTOSENS = 1;
// spectrum + beat detection run on fixed hops of the audio stream (independent of poll/wakeup timing),
// onsets are timestamped on the audio sample timeline -> precise BPM (up to 300 BPM)
static constexpr time_ms_t ANALYSIS_HOP_MS = 10;
// smoothing (0..1): low = fast reaction
static constexpr double CAVA_NOISE_REDUCTION = 0.3;
static constexpr int CAVA_LOW_CUT_OFF_HZ = 50;
static constexpr int CAVA_HIGH_CUT_OFF_HZ = 10000;
static constexpr int CAVA_SCALING_MODE = CAVA_SCALING_LINEAR;
static constexpr double CAVA_INPUT_SCALE = 32768.0;  // F32 (-1..1) -> 16-bit range (cava input convention)

static_assert(SAMPLE_RATE_HZ <= UINT32_MAX);
static_assert(MAX_CHANNELS <= UINT32_MAX);
static constexpr uint32_t STREAM_RATE_HZ = static_cast<uint32_t>(SAMPLE_RATE_HZ);
static constexpr uint32_t STREAM_CHANNELS = static_cast<uint32_t>(MAX_CHANNELS);
static_assert(STREAM_RATE_HZ / 2 > static_cast<uint32_t>(CAVA_HIGH_CUT_OFF_HZ),
              "Nyquist must be above the high cut-off");

// silence: RMS below ~-80 dBFS for a while
// tempo unknown: SILENCE_HOLD_MS; tempo known: a bit longer than one beat (no beat expected anymore), stop fast
static constexpr double SILENCE_RMS = 1e-4;
static constexpr time_ms_t SILENCE_HOLD_MS = 1500;
static constexpr time_ms_t SILENCE_MIN_HOLD_MS = 400;
// keep the tempo over short pauses (resume reacts immediately), forget it after a longer silence (next song)
// (same as the beat detector forgets old onsets)
static constexpr time_ms_t BEAT_MEMORY_MS = details::ONSET_MAX_INTERVAL_MS * 2;

// peak (happy): see audio_peak_detector.h; shm.peak is cleared after this time
static constexpr time_ms_t PEAK_COOLDOWN_MS = details::PEAK_COOLDOWN_MS;
static constexpr double LEVEL_EMA_ALPHA = 0.4;

// beat/onset detection + BPM: see audio_beat_detector.h
// speed factor = animation frame time / beat interval -> one (dance) frame per beat
static constexpr double MIN_SPEED_FACTOR = 0.05;
static constexpr double MAX_SPEED_FACTOR = 20.0;
// beat clock: onsets within +-BEAT_WINDOW (of the beat interval) around the predicted beat re-sync the beat phase,
// onsets outside (off-beat) are ignored; missed beats are triggered at the predicted time.
// two consecutive off-beat onsets one beat interval apart (+-BEAT_WINDOW) mean the phase is wrong (e.g. after a tempo
// change): re-lock the beat clock to the onsets
static constexpr double BEAT_WINDOW = 0.25;

static constexpr double BEAT_LEAD_MS = 100.0;
static constexpr double BEAT_LEAD_MAX_RATIO = 0.4;
static_assert(BEAT_LEAD_MAX_RATIO < 1.0 - BEAT_WINDOW);
static_assert(MAX_SPEED_FACTOR >= MIN_SPEED_FACTOR);

static constexpr time_ms_t MIN_IDLE_TRIGGER_INTERVAL_MS = 100;
static constexpr time_ms_t MIN_ANALYSIS_MS = 5;
static constexpr double LOW_BPM_INTERVAL = 60000.0;

static constexpr time_ms_t RECONNECT_DELAY_MS = 2000;

static constexpr size_t POD_BUFFER_SIZE = 1024;

static constexpr const char *PW_PROP_MEDIA_TYPE_VALUE = "Audio";
static constexpr const char *PW_PROP_MEDIA_CATEGORY_VALUE = "Capture";
static constexpr const char *PW_PROP_MEDIA_MEDIA_ROLE = "Music";
static constexpr const char *PW_PROP_NODE_NAME_VALUE = "bongocat-audio";
static constexpr const char *PW_PROP_APP_NAME_VALUE = "bongocat";
static constexpr const char *PW_PROP_STREAM_MEDIA_NAME_VALUE = "bongocat-audio";

struct audio_analysis_state_t {
  timestamp_ms_t last_analysis{0};
  timestamp_ms_t silence_since{0};
  timestamp_ms_t last_idle_trigger{0};
  timestamp_ms_t last_peak{0};
  bool active{false};
  double level{0};

  // beat clock (one AudioUpdate per beat)
  timestamp_ms_t last_beat{0};           // last beat (triggered)
  bool last_beat_predicted{false};       // last beat was predicted (no onset)
  bool next_beat_triggered{false};       // next beat already triggered early (latency compensation)
  timestamp_ms_t last_offbeat_onset{0};  // last off-beat onset (phase re-lock)

  // beat detection (spectral flux onsets -> BPM)
  details::beat_detector_t beat;
  double stream_time_ms{0};
  details::bar_normalizer_t norm;  // gain independent beat detection

  // peak detection (most bars at the top -> happy)
  details::peak_detector_t peak;
};

namespace details {
  struct pw_audio_backend_t {
    atomic_bool audio_backend_ready{false};
    atomic_bool pw_initialized{false};
  };
  inline pw_audio_backend_t& get_pw_audio_backend() {
    static pw_audio_backend_t g_instance{};
    return g_instance;
  }

  static void ensure_pw_init() {
    (void)get_pw_audio_backend();
    if (!atomic_load(&details::get_pw_audio_backend().audio_backend_ready)) {
      BONGOCAT_LOG_WARNING("audio: audio backend not initialized");
    }
    bool expected = false;
    if (atomic_compare_exchange_strong(&details::get_pw_audio_backend().pw_initialized, &expected, true)) {
      pw_init(BONGOCAT_NULLPTR, BONGOCAT_NULLPTR);
    }
  }
}  // namespace details
void init_audio_backend() {
  (void)details::get_pw_audio_backend();
  atomic_store(&details::get_pw_audio_backend().audio_backend_ready, true);
}
void deinit_audio_backend() {
  (void)details::get_pw_audio_backend();
  atomic_store(&details::get_pw_audio_backend().audio_backend_ready, false);
  bool expected = true;
  if (atomic_compare_exchange_strong(&details::get_pw_audio_backend().pw_initialized, &expected, false)) {
    pw_deinit();
  }
}

namespace details {
  static void destroy_cava(audio_backend_t& backend) {
    if (backend.cava != BONGOCAT_NULLPTR) {
      // cava_destroy only frees the plan internals, the plan itself is malloc'ed by cava_init
      cava_destroy(backend.cava);
      ::free(backend.cava);
      backend.cava = BONGOCAT_NULLPTR;
    }
  }

  static void reset_samples(audio_backend_t& backend) {
    // zero raw audio data (only the used part, untouched pages stay non-resident)
    if (backend.cava_in && backend.cava_in_used > 0) {
      explicit_bzero(backend.cava_in.data, backend.cava_in_used * sizeof(double));
    }
    explicit_bzero(backend.cava_out, sizeof(backend.cava_out));
    backend.cava_in_count = 0;
    backend.cava_in_used = 0;
    backend.rms_acc = 0;
    backend.rms_n = 0;
  }

  static bongocat_error_t create_cava(audio_backend_t& backend, uint32_t rate, uint32_t channels) {
    destroy_cava(backend);
    reset_samples(backend);
    if (rate == 0 || channels == 0 || channels > MAX_CHANNELS) {
      BONGOCAT_LOG_WARNING("audio: unsupported audio format (rate=%u, channels=%u)", rate, channels);
      return bongocat_error_t::BONGOCAT_ERROR_INVALID_PARAM;
    }
    backend.cava = cava_init(CAVA_BARS, rate, static_cast<int>(channels), CAVA_AUTOSENS, CAVA_NOISE_REDUCTION,
                             CAVA_LOW_CUT_OFF_HZ, CAVA_HIGH_CUT_OFF_HZ, CAVA_SCALING_MODE);
    if (backend.cava == BONGOCAT_NULLPTR || backend.cava->status != 0) {
      BONGOCAT_LOG_ERROR("audio: failed to init cavacore: %s",
                         backend.cava ? backend.cava->error_message : "out of memory");
      ::free(backend.cava);
      backend.cava = BONGOCAT_NULLPTR;
      return bongocat_error_t::BONGOCAT_ERROR_AUDIO;
    }
    // plans are created, drop the planner wisdom (not needed for fftw_execute)
    fftw_forget_wisdom();
    backend.rate = rate;
    backend.channels = channels;
    BONGOCAT_LOG_DEBUG("audio: cavacore initialized (rate=%u, channels=%u, bars=%d)", rate, channels, CAVA_BARS);
    return bongocat_error_t::BONGOCAT_SUCCESS;
  }

  // PipeWire stream events
  static void on_state_changed(void *data, pw_stream_state old, pw_stream_state state, const char *error) {
    assert(data != BONGOCAT_NULLPTR);
    auto& backend = *static_cast<audio_backend_t *>(data);
    BONGOCAT_LOG_DEBUG("audio: stream state %s -> %s", pw_stream_state_as_string(old),
                       pw_stream_state_as_string(state));
    if (state == PW_STREAM_STATE_ERROR ||
        (state == PW_STREAM_STATE_UNCONNECTED && old != PW_STREAM_STATE_UNCONNECTED)) {
      BONGOCAT_LOG_WARNING("audio: stream disconnected: %s, reconnecting", error ? error : "");
      backend.needs_reconnect = true;
      backend.reconnect_at = get_current_time_ms() + RECONNECT_DELAY_MS;
    }
  }

  static void on_param_changed(void *data, uint32_t id, const spa_pod *param) {
    assert(data != BONGOCAT_NULLPTR);
    auto& backend = *static_cast<audio_backend_t *>(data);
    if (param == BONGOCAT_NULLPTR || id != SPA_PARAM_Format) {
      return;
    }

    uint32_t media_type{0};
    uint32_t media_subtype{0};
    if (spa_format_parse(param, &media_type, &media_subtype) < 0) {
      return;
    }
    if (media_type != SPA_MEDIA_TYPE_audio || media_subtype != SPA_MEDIA_SUBTYPE_raw) {
      return;
    }

    spa_audio_info_raw info{};
    if (spa_format_audio_raw_parse(param, &info) < 0) {
      return;
    }
    if (info.format != SPA_AUDIO_FORMAT_F32) {
      BONGOCAT_LOG_WARNING("audio: unexpected sample format: %u", info.format);
      return;
    }
    if (info.rate != backend.rate || info.channels != backend.channels || backend.cava == BONGOCAT_NULLPTR) {
      create_cava(backend, info.rate, info.channels);
    }
  }

  static void on_process(void *data) {
    assert(data != BONGOCAT_NULLPTR);
    auto& backend = *static_cast<audio_backend_t *>(data);
    if (backend.stream == BONGOCAT_NULLPTR) {
      return;
    }
    pw_buffer *b = pw_stream_dequeue_buffer(backend.stream);
    if (b == BONGOCAT_NULLPTR) {
      return;
    }

    const spa_buffer *buf = b->buffer;
    if (buf != BONGOCAT_NULLPTR && buf->n_datas > 0 && buf->datas[0].data != BONGOCAT_NULLPTR &&
        buf->datas[0].chunk != BONGOCAT_NULLPTR && backend.cava != BONGOCAT_NULLPTR && backend.cava_in) {
      const spa_data& d = buf->datas[0];
      const uint32_t offset = d.chunk->offset < d.maxsize ? d.chunk->offset : d.maxsize;
      const uint32_t size = d.chunk->size <= d.maxsize - offset ? d.chunk->size : d.maxsize - offset;
      const auto *samples = reinterpret_cast<const float *>(static_cast<const uint8_t *>(d.data) + offset);
      size_t n_samples = size / sizeof(float);

      // keep only the newest samples when overflowing (drop oldest)
      if (n_samples > SAMPLE_BUFFER_SIZE) {
        samples += n_samples - SAMPLE_BUFFER_SIZE;
        n_samples = SAMPLE_BUFFER_SIZE;
      }
      if (backend.cava_in_count + n_samples > SAMPLE_BUFFER_SIZE) {
        const size_t drop = backend.cava_in_count + n_samples - SAMPLE_BUFFER_SIZE;
        memmove(backend.cava_in.data, backend.cava_in.data + drop, (backend.cava_in_count - drop) * sizeof(double));
        backend.cava_in_count -= drop;
      }
      for (size_t i = 0; i < n_samples; i++) {
        const double s = static_cast<double>(samples[i]);
        // cavacore expects 16-bit sample range (like cava itself), F32 is -1..1:
        // unscaled input needs a ~32768x higher autosens, which takes many seconds to ramp up
        backend.cava_in.data[backend.cava_in_count++] = s * CAVA_INPUT_SCALE;
        backend.rms_acc += s * s;  // RMS on the normalized signal (silence threshold)
      }
      backend.rms_n += n_samples;
      if (backend.cava_in_count > backend.cava_in_used) {
        backend.cava_in_used = backend.cava_in_count;
      }
    }

    pw_stream_queue_buffer(backend.stream, b);
  }

  static constexpr pw_stream_events stream_events = {
      .version = PW_VERSION_STREAM_EVENTS,
      .destroy = BONGOCAT_NULLPTR,
      .state_changed = on_state_changed,
      .control_info = BONGOCAT_NULLPTR,
      .io_changed = BONGOCAT_NULLPTR,
      .param_changed = on_param_changed,
      .add_buffer = BONGOCAT_NULLPTR,
      .remove_buffer = BONGOCAT_NULLPTR,
      .process = on_process,
      .drained = BONGOCAT_NULLPTR,
      .command = BONGOCAT_NULLPTR,
      .trigger_done = BONGOCAT_NULLPTR,
  };

  // tear down PipeWire stream/context and cavacore, wipe samples
  static void destroy_stream(audio_backend_t& backend) {
    if (backend.loop != BONGOCAT_NULLPTR) {
      pw_loop_enter(backend.loop);
    }
    if (backend.stream != BONGOCAT_NULLPTR) {
      spa_hook_remove(&backend.stream_listener);
      pw_stream_destroy(backend.stream);
      backend.stream = BONGOCAT_NULLPTR;
    }
    if (backend.core != BONGOCAT_NULLPTR) {
      pw_core_disconnect(backend.core);
      backend.core = BONGOCAT_NULLPTR;
    }
    if (backend.context != BONGOCAT_NULLPTR) {
      pw_context_destroy(backend.context);
      backend.context = BONGOCAT_NULLPTR;
    }
    if (backend.loop != BONGOCAT_NULLPTR) {
      pw_loop_leave(backend.loop);
      pw_loop_destroy(backend.loop);
      backend.loop = BONGOCAT_NULLPTR;
    }
    backend.thread_loop_entered = false;
    destroy_cava(backend);
    reset_samples(backend);
    release_allocated_array(backend.cava_in);
    backend.rate = 0;
    backend.channels = 0;
    backend.needs_reconnect = false;
    backend.reconnect_at = 0;
  }

  // connect (or re-connect) stream: request F32 interleaved stereo, rate is negotiated (graph rate)
  static bongocat_error_t connect_stream(audio_backend_t& backend) {
    assert(backend.stream != BONGOCAT_NULLPTR);
    uint8_t pod_buffer[POD_BUFFER_SIZE];
    spa_pod_builder builder{};
    spa_pod_builder_init(&builder, pod_buffer, sizeof(pod_buffer));
    spa_audio_info_raw info{};
    info.format = SPA_AUDIO_FORMAT_F32;
    info.rate = STREAM_RATE_HZ;  // fixed rate: PipeWire resamples, cava FFT size depends on the rate
    info.channels = STREAM_CHANNELS;
    info.position[0] = SPA_AUDIO_CHANNEL_FL;
    info.position[1] = SPA_AUDIO_CHANNEL_FR;
    const spa_pod *params[1] = {spa_format_audio_raw_build(&builder, SPA_PARAM_EnumFormat, &info)};

    const auto flags = static_cast<pw_stream_flags>(PW_STREAM_FLAG_AUTOCONNECT | PW_STREAM_FLAG_MAP_BUFFERS);
    if (pw_stream_connect(backend.stream, PW_DIRECTION_INPUT, PW_ID_ANY, flags, params, 1) < 0) {
      BONGOCAT_LOG_ERROR("audio: failed to connect PipeWire stream");
      return bongocat_error_t::BONGOCAT_ERROR_AUDIO;
    }
    return bongocat_error_t::BONGOCAT_SUCCESS;
  }

  // re-connect stream after error/disconnect
  static void reconnect_stream(audio_backend_t& backend) {
    if (backend.stream == BONGOCAT_NULLPTR) {
      return;
    }
    BONGOCAT_LOG_DEBUG("audio: reconnecting stream");
    pw_stream_disconnect(backend.stream);
    reset_samples(backend);
    if (connect_stream(backend) != bongocat_error_t::BONGOCAT_SUCCESS) {
      backend.needs_reconnect = true;
      backend.reconnect_at = get_current_time_ms() + RECONNECT_DELAY_MS;
      return;
    }
    backend.needs_reconnect = false;
  }

  // connect to PipeWire and capture sink
  static bongocat_error_t create_stream(audio_backend_t& backend, const config::config_t& config) {
    destroy_stream(backend);

    // sample buffer (uninitialized: only used pages become resident, wiped after use)
    backend.cava_in = make_allocated_array_uninitialized<double>(SAMPLE_BUFFER_SIZE);
    if (!backend.cava_in) {
      BONGOCAT_LOG_ERROR("audio: failed to allocate sample buffer");
      return bongocat_error_t::BONGOCAT_ERROR_MEMORY;
    }
    backend.cava_in_count = 0;
    backend.cava_in_used = 0;

    ensure_pw_init();
    backend.loop = pw_loop_new(BONGOCAT_NULLPTR);
    if (backend.loop == BONGOCAT_NULLPTR) {
      BONGOCAT_LOG_ERROR("audio: failed to create PipeWire loop");
      return bongocat_error_t::BONGOCAT_ERROR_AUDIO;
    }
    pw_loop_enter(backend.loop);

    const auto pw_setup_result = [&] -> bongocat_error_t {
      // only load the modules a capture stream needs (protocol-native, client-node, adapter), skip:
      // rt (realtime via rtkit), client-device, metadata, session-manager
      // support.dbus: don't load the dbus support plugin (libspa-dbus + libdbus)
      pw_properties *context_props =
          pw_properties_new("module.rt", "false", "module.client-device", "false", "module.metadata", "false",
                            "module.session-manager", "false", "support.dbus", "false", BONGOCAT_NULLPTR);
      // pw_context_new takes ownership of props
      backend.context = pw_context_new(backend.loop, context_props, 0);
      if (backend.context == BONGOCAT_NULLPTR) {
        BONGOCAT_LOG_ERROR("audio: failed to create PipeWire context");
        return bongocat_error_t::BONGOCAT_ERROR_AUDIO;
      }
      backend.core = pw_context_connect(backend.context, BONGOCAT_NULLPTR, 0);
      if (backend.core == BONGOCAT_NULLPTR) {
        BONGOCAT_LOG_WARNING("audio: failed to connect to PipeWire: %s", strerror(errno));
        return bongocat_error_t::BONGOCAT_ERROR_AUDIO;
      }

      pw_properties *props =
          pw_properties_new(PW_KEY_MEDIA_TYPE, PW_PROP_MEDIA_TYPE_VALUE, PW_KEY_MEDIA_CATEGORY,
                            PW_PROP_MEDIA_CATEGORY_VALUE, PW_KEY_MEDIA_ROLE, PW_PROP_MEDIA_MEDIA_ROLE, PW_KEY_NODE_NAME,
                            PW_PROP_NODE_NAME_VALUE, PW_KEY_APP_NAME, PW_PROP_APP_NAME_VALUE, BONGOCAT_NULLPTR);
      if (props == BONGOCAT_NULLPTR) {
        return bongocat_error_t::BONGOCAT_ERROR_AUDIO;
      }
      // capture from sink monitor (what is playing), never from a microphone
      pw_properties_set(props, PW_KEY_STREAM_CAPTURE_SINK, "true");
      if (config.audio_sink && config.audio_sink.c_str()[0] != '\0') {
        pw_properties_set(props, PW_KEY_TARGET_OBJECT, config.audio_sink.c_str());
      }

      // pw_stream_new takes ownership of props
      backend.stream = pw_stream_new(backend.core, PW_PROP_STREAM_MEDIA_NAME_VALUE, props);
      if (backend.stream == BONGOCAT_NULLPTR) {
        BONGOCAT_LOG_ERROR("audio: failed to create PipeWire stream");
        return bongocat_error_t::BONGOCAT_ERROR_AUDIO;
      }
      backend.stream_listener = {};
      pw_stream_add_listener(backend.stream, &backend.stream_listener, &stream_events, &backend);

      return connect_stream(backend);
    }();
    pw_loop_leave(backend.loop);
    if (pw_setup_result != bongocat_error_t::BONGOCAT_SUCCESS) {
      destroy_stream(backend);
      return pw_setup_result;
    }

    // initial cava plan
    create_cava(backend, STREAM_RATE_HZ, STREAM_CHANNELS);

    // return memory freed during PipeWire/FFTW setup (audio thread arena) back to the OS
#ifdef __GLIBC__
    malloc_trim(0);
#endif

    BONGOCAT_LOG_INFO("audio: capturing sink monitor (%s)",
                      config.audio_sink && config.audio_sink.length() > 0 ? config.audio_sink.c_str() : "default sink");
    return bongocat_error_t::BONGOCAT_SUCCESS;
  }

  static int get_backend_fd(const audio_backend_t& backend) {
    if (backend.loop == BONGOCAT_NULLPTR) {
      return -1;
    }
    return pw_loop_get_fd(backend.loop);
  }

  // set up audio stream (when enabled)
  static bongocat_error_t setup_stream(audio_context_t& audio) {
    assert(audio._backend);
    assert(audio._local_copy_config);
    assert(!atomic_load(&audio._running));
    const config::config_t& current_config = *audio._local_copy_config;
    if (!current_config.enable_audio) {
      BONGOCAT_LOG_DEBUG("audio: audio disabled, no stream");
      return bongocat_error_t::BONGOCAT_SUCCESS;
    }

    if (const auto result = create_stream(*audio._backend, current_config);
        result != bongocat_error_t::BONGOCAT_SUCCESS) {
      BONGOCAT_LOG_WARNING("audio: failed to set up audio stream, audio disabled until restart");
      return result;
    }

    return bongocat_error_t::BONGOCAT_SUCCESS;
  }

  // tear down audio stream
  static void teardown_stream(audio_context_t& audio) {
    if (audio._backend) {
      destroy_stream(*audio._backend);
    }
    if (audio.shm) {
      LockGuard guard(audio.audio_lock);
      *audio.shm = {};
    }
  }

  // ---------------------------------------------------------------------------
  // analysis
  // ---------------------------------------------------------------------------
  inline static double clamp01(double v) {
    return v < 0.0 ? 0.0 : (v > 1.0 ? 1.0 : v);
  }

  static void reset_beat_detection(audio_analysis_state_t& state) {
    beat_detector_reset(state.beat);
    peak_detector_reset(state.peak);
    state.stream_time_ms = 0;
    state.level = 0;
    state.last_beat = 0;
    state.last_beat_predicted = false;
    state.next_beat_triggered = false;
    state.last_offbeat_onset = 0;
    details::bar_normalizer_reset(state.norm);
  }

  // active -> silent: forget levels/peaks, keep the tempo (see BEAT_MEMORY_MS)
  static void reset_on_silence(audio_analysis_state_t& state, audio_backend_t& backend) {
    peak_detector_reset(state.peak);
    state.level = 0;
    details::bar_normalizer_reset(state.norm);
    if (backend.cava != BONGOCAT_NULLPTR) {
      // re-enable the fast initial ramp-up of cava's autosens (keep the learned sensitivity),
      // the next audio may be much quieter; louder audio overshoots and lowers the sensitivity quickly
      backend.cava->sens_init = 1;
    }
  }
}  // namespace details

static void cleanup_audio_thread(void *arg) {
  assert(arg != BONGOCAT_NULLPTR);
  const animation::animation_context_t& animation_context = *static_cast<animation::animation_context_t *>(arg);
  assert(animation_context._audio);
  audio_context_t& audio = *animation_context._audio;

  atomic_store(&audio._running, false);

  // leave PipeWire loop
  if (audio._backend && audio._backend->loop != BONGOCAT_NULLPTR && audio._backend->thread_loop_entered) {
    pw_loop_leave(audio._backend->loop);
    audio._backend->thread_loop_entered = false;
  }

  audio.config_updated.notify_all();

  BONGOCAT_LOG_INFO("Audio thread cleanup completed");
}

static void *audio_thread(void *arg) {
  assert(arg != BONGOCAT_NULLPTR);
  animation::animation_context_t& animation_ctx = *static_cast<animation::animation_context_t *>(arg);

  assert(animation_ctx._audio != BONGOCAT_NULLPTR);
  audio_context_t& audio = *animation_ctx._audio;
  // wait for input context (in animation start)
  animation_ctx.init_cond.timedwait(
      [&]() { return atomic_load(&animation_ctx.ready) || !atomic_load(&audio._running); },
      COND_ANIMATION_TRIGGER_INIT_TIMEOUT_MS);

  // sanity checks
  assert(audio._config != BONGOCAT_NULLPTR);
  assert(audio._configs_reloaded_cond != BONGOCAT_NULLPTR);
  assert(audio.shm);
  assert(audio._local_copy_config);

  // trigger initial render
  wayland::request_render(animation_ctx);

  pthread_cleanup_push(cleanup_audio_thread, arg);

  // local thread context
  audio_analysis_state_t analysis{};
  bool enable_audio = false;
  assert(audio._backend);
  audio_backend_t& backend = *audio._backend;
  // stream is set up in start()/restart(), only run the PipeWire loop in this thread
  if (backend.loop != BONGOCAT_NULLPTR) {
    pw_loop_enter(backend.loop);
    backend.thread_loop_entered = true;
  }

  /// event poll
  // 0:       reload config event
  // 1:       PipeWire loop fd
  constexpr size_t nfds = 2;
  pollfd pfds[nfds];

  atomic_store(&audio._running, true);
  while (atomic_load(&audio._running)) {
    pthread_testcancel();  // optional, but makes cancellation more responsive

    // read from config
    time_ms_t timeout_ms = AUDIO_POOL_TIMEOUT_MS;
    time_ms_t idle_trigger_interval_ms = MIN_IDLE_TRIGGER_INTERVAL_MS;
    time_ms_t analysis_ms = AUDIO_POOL_TIMEOUT_MS;         // audio analysis (cava, beat detection) interval
    time_ms_t animation_frame_ms = AUDIO_POOL_TIMEOUT_MS;  // animation frame time (same as in animation thread)
    time_ms_t animation_speed_ms = 0;
    // int fps = 0;
    [[maybe_unused]] bool enable_debug = false;
    double audio_happy_peak = 0.0;
    {
      // read-only config
      assert(audio._local_copy_config);
      const config::config_t& current_config = *audio._local_copy_config;

      enable_audio = current_config.enable_audio;
      audio_happy_peak = current_config.audio_happy_peak;
      enable_debug = current_config.enable_debug;

      animation_speed_ms = current_config.animation_speed_ms;
      // fps = current_config.fps;
      if (current_config.audio_fps > 0) {
        timeout_ms = 1000 / current_config.audio_fps;
      } else if (animation_speed_ms > 0) {
        timeout_ms = animation_speed_ms;
      } else if (current_config.input_fps > 0) {
        timeout_ms = 1000 / current_config.input_fps / 2;
      } else if (current_config.fps > 0) {
        timeout_ms = 1000 / current_config.fps / 2;
      }

      // animation frame time, base for the speed factor (see animation.cpp)
      if (animation_speed_ms > 0) {
        animation_frame_ms = animation_speed_ms;
      } else if (current_config.fps > 0) {
        animation_frame_ms = 1000 / current_config.fps;
      }

      // audio analysis needs a high rate for beat detection (independent of animation speed)
      if (current_config.audio_fps > 0) {
        analysis_ms = 1000 / current_config.audio_fps;
      } else if (current_config.fps > 0) {
        analysis_ms = 1000 / current_config.fps;
      }
      if (analysis_ms <= 0) {
        analysis_ms = MIN_ANALYSIS_MS;
      }
      if (enable_audio && analysis.active && timeout_ms > analysis_ms) {
        // active: wake up for analysis/beat clock/silence detection even without stream events
        // inactive: new audio wakes up the poll (PipeWire fd), no need to wake up more often
        timeout_ms = analysis_ms;
      }

      // tempo unknown (yet): keep the animation going with one frame per animation frame time
      idle_trigger_interval_ms =
          animation_frame_ms > MIN_IDLE_TRIGGER_INTERVAL_MS ? animation_frame_ms : MIN_IDLE_TRIGGER_INTERVAL_MS;

      if (enable_audio && backend.stream != BONGOCAT_NULLPTR) {
        // re-connect stream after error/disconnect
        if (backend.needs_reconnect) {
          const timestamp_ms_t now = get_current_time_ms();
          if (now >= backend.reconnect_at) {
            details::reconnect_stream(backend);
          } else if (backend.reconnect_at - now < timeout_ms) {
            timeout_ms = backend.reconnect_at - now;
          }
        }
      }
    }

    audio.pw_loop_fd = enable_audio ? details::get_backend_fd(backend) : -1;

    // init pfds
    constexpr size_t fds_audio_config_index = 0;
    constexpr size_t fds_audio_stream_index = 1;
    pfds[fds_audio_config_index] = {.fd = audio.audio_config_efd._fd, .events = POLLIN, .revents = 0};
    pfds[fds_audio_stream_index] = {.fd = audio.pw_loop_fd, .events = POLLIN, .revents = 0};

    // poll events
    const int poll_result = poll(pfds, nfds, static_cast<int>(timeout_ms));
    if (poll_result < 0) {
      if (errno == EINTR) {
        continue;  // Interrupted by signal
      }
      BONGOCAT_LOG_ERROR("audio: Poll error: %s", strerror(errno));
      break;
    }

    // cancel pooling (when not running anymore)
    if (!atomic_load(&audio._running)) {
      // draining pools
      if (pfds[fds_audio_config_index].revents & POLLIN) {
        drain_event(pfds[fds_audio_config_index], MAX_ATTEMPTS);
      }
      break;
    }

    // Handle config update
    assert(audio._config_generation != BONGOCAT_NULLPTR);
    bool reload_config = false;
    uint64_t new_gen{atomic_load(audio._config_generation)};
    if (pfds[fds_audio_config_index].revents & POLLIN) {
      BONGOCAT_LOG_DEBUG("audio: Receive audio config event");
      drain_event(pfds[fds_audio_config_index], MAX_ATTEMPTS, "audio config eventfd");
      reload_config = new_gen > 0;
    }

    // Handle audio stream events (process samples into thread-local buffer)
    if (backend.loop != BONGOCAT_NULLPTR && (pfds[fds_audio_stream_index].revents & POLLIN)) {
      pw_loop_iterate(backend.loop, 0);
    }

    // analyse audio and trigger animation (every frame)
    const timestamp_ms_t now = get_current_time_ms();
    if (enable_audio && backend.cava != BONGOCAT_NULLPTR && (now - analysis.last_analysis) >= analysis_ms) {
      analysis.last_analysis = now;

      // RMS for silence detection (raw signal, before autosens)
      const double rms = backend.rms_n > 0 ? sqrt(backend.rms_acc / static_cast<double>(backend.rms_n)) : 0.0;
      backend.rms_acc = 0;
      backend.rms_n = 0;

      // silence
      if (rms < SILENCE_RMS) {
        if (analysis.silence_since == 0) {
          analysis.silence_since = now;
        }
      } else {
        analysis.silence_since = 0;
      }
      const time_ms_t quiet_ms = analysis.silence_since != 0 ? now - analysis.silence_since : 0;
      const time_ms_t silence_hold_ms = [&]() -> time_ms_t {
        if (analysis.beat.bpm <= 0.0) {
          return SILENCE_HOLD_MS;
        }
        // no onset within the next beat (+ beat window): music stopped
        const auto hold = static_cast<time_ms_t>(LOW_BPM_INTERVAL / analysis.beat.bpm * (1.0 + BEAT_WINDOW));
        return hold > SILENCE_MIN_HOLD_MS ? hold : SILENCE_MIN_HOLD_MS;
      }();
      const bool silent = analysis.silence_since != 0 && quiet_ms >= silence_hold_ms;
      const bool was_active = analysis.active;
      const bool detect_beats = !silent && (rms >= SILENCE_RMS || was_active);

      // spectrum + beat (onset) and peak detection on fixed hops (sample timeline)
      bool onset = false;
      bool peak_hit = false;
      {
        static_assert(static_cast<size_t>(CAVA_BARS) * MAX_CHANNELS <= details::PEAK_DETECTOR_MAX_BARS);
        static_assert(SAMPLE_BUFFER_SIZE <= INT_MAX);
        static_assert(static_cast<size_t>(CAVA_BARS) * MAX_CHANNELS <= details::BEAT_DETECTOR_MAX_BARS);
        static_assert(static_cast<size_t>(CAVA_BARS) * MAX_CHANNELS <= details::BAR_NORM_MAX_BARS);
        const size_t channels = backend.channels > 0 ? backend.channels : STREAM_CHANNELS;
        const double rate = backend.rate > 0 ? static_cast<double>(backend.rate) : static_cast<double>(STREAM_RATE_HZ);
        const size_t total_bars = static_cast<size_t>(CAVA_BARS) * channels;
        size_t hop_samples = static_cast<size_t>(rate * static_cast<double>(ANALYSIS_HOP_MS) / 1000.0) * channels;
        if (hop_samples == 0) {
          hop_samples = channels;
        }
        if (backend.cava_in_count == 0) {
          // no new samples: keep bars falling
          cava_execute(backend.cava_in.data, 0, backend.cava_out, backend.cava);
        }
        for (size_t offset = 0; offset < backend.cava_in_count; offset += hop_samples) {
          assert(rate > 0);
          const size_t n = backend.cava_in_count - offset < hop_samples ? backend.cava_in_count - offset : hop_samples;
          cava_execute(backend.cava_in.data + offset, static_cast<int>(n), backend.cava_out, backend.cava);
          analysis.stream_time_ms += static_cast<double>(n / channels) * 1000.0 / rate;
          const auto stream_now = static_cast<timestamp_ms_t>(analysis.stream_time_ms);
          const double *beat_bars = details::bar_normalizer_process(analysis.norm, backend.cava_out, total_bars,
                                                                    static_cast<double>(n / channels) * 1000.0 / rate);
          if (detect_beats && beat_detector_process(analysis.beat, beat_bars, total_bars, stream_now) ==
                                  details::beat_detector_process_t::OnSetDetected) {
            onset = true;
            BONGOCAT_LOG_VERBOSE("audio: onset (flux=%.3f, bpm=%.1f)", analysis.beat.flux, analysis.beat.bpm);
          }
          // peak: most bars reach the top
          if (detect_beats &&
              details::peak_detector_process(analysis.peak, backend.cava_out, total_bars, stream_now,
                                             audio_happy_peak) == details::peak_detector_process_result_t::Peaked) {
            peak_hit = true;
          }
        }
        backend.cava_in_count = 0;
      }

      bool peak_reached = false;
      if (silent) {
        if (was_active) {
          details::reset_on_silence(analysis, backend);
        }
        analysis.active = false;
        if (quiet_ms >= BEAT_MEMORY_MS && analysis.beat.bpm > 0.0) {
          // long silence: forget tempo (next song)
          details::reset_beat_detection(analysis);
        }
      } else if (rms >= SILENCE_RMS || was_active) {
        analysis.active = true;

        // aggregate bars (all channels)
        const size_t channels = backend.channels > 0 ? backend.channels : 1;
        const size_t total_bars = static_cast<size_t>(CAVA_BARS) * channels;
        double sum = 0;
        double max_bar = 0;
        for (size_t i = 0; i < total_bars; i++) {
          const double v = details::clamp01(backend.cava_out[i]);
          sum += v;
          max_bar = v > max_bar ? v : max_bar;
        }
        assert(total_bars != 0);
        const double mean = sum / static_cast<double>(total_bars);

        // level: mix of overall energy and strongest band, smoothed
        const double instant_level = 0.5 * mean + 0.5 * max_bar;
        analysis.level = (1.0 - LEVEL_EMA_ALPHA) * analysis.level + LEVEL_EMA_ALPHA * instant_level;

        // peak (happy): most bars reached the top (cooldown + re-arm in peak detector)
        peak_reached = peak_hit;
        if (peak_reached) {
          analysis.last_peak = now;
        }
      }

      // beat clock: one beat per beat interval, phase-locked to onsets
      const double bpm = analysis.active ? analysis.beat.bpm : 0.0;
      const bool beat = [&] {
        if (!analysis.active) {
          return false;
        }
        if (bpm <= 0.0) {
          // tempo unknown (yet): every onset is a beat
          if (onset) {
            analysis.last_beat = now;
            analysis.last_beat_predicted = false;
          }
          return onset;
        }
        assert(bpm > 0.0);
        const double beat_interval_ms = LOW_BPM_INTERVAL / bpm;
        const auto since_last_beat = static_cast<double>(now - analysis.last_beat);
        if (analysis.last_beat == 0 || since_last_beat > beat_interval_ms * 4.0) {
          // (re-)start beat clock
          if (onset) {
            analysis.last_beat = now;
            analysis.last_beat_predicted = false;
            analysis.next_beat_triggered = false;
            analysis.last_offbeat_onset = 0;
          }
          return onset;
        }
        // last_beat is the beat phase (on the beat), the trigger fires `lead` before the next beat
        const double lead_ms = BEAT_LEAD_MS < beat_interval_ms * BEAT_LEAD_MAX_RATIO
                                   ? BEAT_LEAD_MS
                                   : beat_interval_ms * BEAT_LEAD_MAX_RATIO;
        if (onset) {
          if (since_last_beat >= beat_interval_ms * (1.0 - BEAT_WINDOW)) {
            // onset close to (or after) the predicted beat: re-sync phase, trigger if not already done early
            const bool trigger = !analysis.next_beat_triggered;
            analysis.last_beat = now;
            analysis.last_beat_predicted = false;
            analysis.next_beat_triggered = false;
            analysis.last_offbeat_onset = 0;
            return trigger;
          }
          if (analysis.last_beat_predicted && since_last_beat <= beat_interval_ms * BEAT_WINDOW) {
            // late onset shortly after a predicted beat: re-sync phase, beat was already triggered
            analysis.last_beat = now;
            analysis.last_beat_predicted = false;
            return false;
          }
          // off-beat onset
          if (analysis.last_offbeat_onset != 0) {
            const auto since_offbeat = static_cast<double>(now - analysis.last_offbeat_onset);
            const double phase_error = since_offbeat - beat_interval_ms;
            if (phase_error >= -beat_interval_ms * BEAT_WINDOW && phase_error <= beat_interval_ms * BEAT_WINDOW) {
              // off-beat onsets keep coming on a steady beat: the beat phase is wrong, re-lock to the onsets
              const bool trigger = !analysis.next_beat_triggered;
              analysis.last_beat = now;
              analysis.last_beat_predicted = false;
              analysis.next_beat_triggered = false;
              analysis.last_offbeat_onset = 0;
              return trigger;
            }
          }
          analysis.last_offbeat_onset = now;
          return false;
        }
        if (since_last_beat >= beat_interval_ms * (1.0 + BEAT_WINDOW)) {
          // missed onset: keep the beat going (predicted)
          const bool trigger = !analysis.next_beat_triggered;
          analysis.last_beat += static_cast<timestamp_ms_t>(beat_interval_ms);
          analysis.last_beat_predicted = true;
          analysis.next_beat_triggered = false;
          return trigger;
        }
        if (!analysis.next_beat_triggered && since_last_beat >= beat_interval_ms - lead_ms) {
          // trigger early (latency compensation), the onset re-syncs the phase
          analysis.next_beat_triggered = true;
          return true;
        }
        return false;
      }();

      // speed factor: one animation frame per beat (animation frame time / beat interval)
      const double speed_factor = [&] {
        if (!analysis.active || bpm <= 0.0 || animation_frame_ms <= 0) {
          return 1.0;
        }
        assert(bpm > 0.0);
        const double beat_interval_ms = LOW_BPM_INTERVAL / bpm;
        assert(beat_interval_ms > 0.0);
        const double f = static_cast<double>(animation_frame_ms) / beat_interval_ms;
        return f < MIN_SPEED_FACTOR ? MIN_SPEED_FACTOR : (f > MAX_SPEED_FACTOR ? MAX_SPEED_FACTOR : f);
      }();

      // update shared memory (only derived values)
      {
        LockGuard guard(audio.audio_lock);
        assert(audio.shm != BONGOCAT_NULLPTR);
        auto& audio_shm = *audio.shm;
        audio_shm.active = analysis.active;
        audio_shm.level = analysis.active ? analysis.level : 0.0;
        audio_shm.bpm = bpm;
        audio_shm.speed_factor = speed_factor;
        audio_shm.beat_sync = analysis.active && bpm > 0.0;
        if (peak_reached) {
          audio_shm.peak = true;
          audio_shm.last_peak_timestamp = now;
        } else if (audio_shm.peak && now - audio_shm.last_peak_timestamp >= PEAK_COOLDOWN_MS) {
          audio_shm.peak = false;
        }
      }

      // trigger animation (outside of audio lock)
      if (analysis.active) {
        const auto last_idle_trigger_diff = now - analysis.last_idle_trigger;
        if (peak_reached) {
          BONGOCAT_LOG_VERBOSE("audio: peak reached (bars at top=%.2f, level=%.2f, bpm=%.1f)", analysis.peak.fraction,
                               analysis.level, analysis.beat.bpm);
          animation::trigger(animation_ctx, animation::trigger_animation_cause_mask_t::AudioPeak);
          analysis.last_idle_trigger = now;
        } else if (beat) {
          // every beat: one (dance) frame per beat
          BONGOCAT_LOG_VERBOSE("audio: beat%s (bpm=%.1f, speed_factor=%.2f)", onset ? "" : " (predicted/early)", bpm,
                               speed_factor);
          animation::trigger(animation_ctx, animation::trigger_animation_cause_mask_t::AudioUpdate);
          analysis.last_idle_trigger = now;
        } else if (bpm <= 0.0 && last_idle_trigger_diff >= idle_trigger_interval_ms) {
          // tempo unknown (yet): keep animation going
          animation::trigger(animation_ctx, animation::trigger_animation_cause_mask_t::AudioUpdate);
          analysis.last_idle_trigger = now;
        }
        if (!was_active) {
          BONGOCAT_LOG_DEBUG("audio: audio active");
        }

        if (enable_debug) {
          assert(audio.shm != BONGOCAT_NULLPTR);
          [[maybe_unused]] auto& audio_shm = *audio.shm;
          BONGOCAT_LOG_VERBOSE("audio: level=%.2f, peak=%.2f, bpm=%.2f, speed_factor=%.2f", audio_shm.level,
                               analysis.peak.fraction, audio_shm.bpm, audio_shm.speed_factor);
        }
      } else if (was_active) {
        // active -> silent: last update, so the animation can go back to normal speed
        BONGOCAT_LOG_DEBUG("audio: silence");
        if (enable_debug) {
          assert(audio.shm != BONGOCAT_NULLPTR);
          [[maybe_unused]] auto& audio_shm = *audio.shm;
          BONGOCAT_LOG_VERBOSE("audio: level=%.2f, peak=%.2f, bpm=%.2f, speed_factor=%.2f", audio_shm.level,
                               analysis.peak.fraction, audio_shm.bpm, audio_shm.speed_factor);
        }

        animation::trigger(animation_ctx, animation::trigger_animation_cause_mask_t::AudioStop);
      }
      // silent: no animation trigger
    }

    // handle update config
    if (reload_config) {
      assert(audio._config_generation != BONGOCAT_NULLPTR);
      assert(audio._configs_reloaded_cond != BONGOCAT_NULLPTR);
      assert(audio._config != BONGOCAT_NULLPTR);

      // @NOTE: when enable_audio or audio_sink changed, the audio thread gets restarted (stream re-created)
      update_config(audio, *audio._config, new_gen);

      // wait for reload config to be done (all configs)
      const int rc = audio._configs_reloaded_cond->timedwait(
          [&] { return atomic_load(audio._config_generation) >= new_gen || !atomic_load(&audio._running); },
          COND_RELOAD_CONFIGS_TIMEOUT_MS);
      if (rc == ETIMEDOUT) {
        BONGOCAT_LOG_WARNING("audio: Timed out waiting for reload eventfd: %s", strerror(errno));
      }
      if constexpr (features::Debug) {
        if (atomic_load(&audio.config_seen_generation) < atomic_load(audio._config_generation)) {
          BONGOCAT_LOG_VERBOSE("audio: audio.config_seen_generation < update._config_generation; %d < %d",
                               atomic_load(&audio.config_seen_generation), atomic_load(audio._config_generation));
        }
      }
      atomic_store(&audio.config_seen_generation, atomic_load(audio._config_generation));

      BONGOCAT_LOG_INFO("audio: Audio config reloaded (gen=%u)", new_gen);
    }
  }

  atomic_store(&audio._running, false);

  // Will run only on normal return
  pthread_cleanup_pop(1);  // 1 = call cleanup even if not canceled

  // leave PipeWire loop
  /*
  if (audio._backend && audio._backend->loop != BONGOCAT_NULLPTR) {
    pw_loop_leave(audio._backend->loop);
  }
  */
  // done when callback cleanup_audio_thread
  // cleanup_audio_thread_context(arg);
  // sanity check for clean up
  assert(!audio._backend || audio._backend->thread_loop_entered == false);

  BONGOCAT_LOG_INFO("Audio monitoring stopped");

  return BONGOCAT_NULLPTR;
}

created_result_t<AllocatedMemory<audio_context_t>> create(const config::config_t& config) {
  AllocatedMemory<audio_context_t> ret = make_allocated_memory<audio_context_t>();
  // assert(ret != nullptr);
  if (!ret) [[unlikely]] {
    return bongocat_error_t::BONGOCAT_ERROR_MEMORY;
  }

  ret->_running = false;

  // Initialize shared memory
  ret->shm = make_allocated_mmap<audio_shared_memory_t>();
  if (!ret->shm) [[unlikely]] {
    BONGOCAT_LOG_ERROR("Failed to create shared memory for audio monitoring: %s", strerror(errno));
    return bongocat_error_t::BONGOCAT_ERROR_MEMORY;
  }

  // Initialize shared memory for local config
  ret->_local_copy_config = make_allocated_mmap<config::config_t>();
  if (!ret->_local_copy_config) [[unlikely]] {
    BONGOCAT_LOG_ERROR("Failed to create shared memory for audio monitoring: %s", strerror(errno));
    return bongocat_error_t::BONGOCAT_ERROR_MEMORY;
  }
  assert(ret->_local_copy_config);
  *ret->_local_copy_config = config;

  ret->audio_config_efd = platform::FileDescriptor(eventfd(0, EFD_NONBLOCK | EFD_CLOEXEC));
  if (ret->audio_config_efd._fd < 0) [[unlikely]] {
    BONGOCAT_LOG_ERROR("Failed to create notify pipe for audio config: %s", strerror(errno));
    return bongocat_error_t::BONGOCAT_ERROR_FILE_IO;
  }

  ret->_backend = make_allocated_memory<audio_backend_t>();
  if (!ret->_backend) [[unlikely]] {
    BONGOCAT_LOG_ERROR("Failed to allocate audio backend: %s", strerror(errno));
    return bongocat_error_t::BONGOCAT_ERROR_MEMORY;
  }

  return ret;
}

bongocat_error_t start(audio_context_t& audio, animation::animation_context_t& animation_ctx,
                       const config::config_t& config, CondVariable& configs_reloaded_cond,
                       atomic_uint64_t& config_generation) {
  BONGOCAT_LOG_INFO("Initializing audio monitoring");
  assert(audio.shm);
  assert(audio._local_copy_config);
  update_config(audio, config, atomic_load(&config_generation));

  // wait for animation trigger to be ready (input should be the same)
  const int cond_ret = animation_ctx.init_cond.timedwait([&]() { return atomic_load(&animation_ctx.ready); },
                                                         COND_ANIMATION_TRIGGER_INIT_TIMEOUT_MS);
  if (cond_ret == ETIMEDOUT) {
    BONGOCAT_LOG_ERROR("Failed to initialize audio monitoring: waiting for animation thread to start in time");
  } else {
    assert(animation_ctx._audio == &audio);
  }
  // set extern/global references
  {
    // guard for anim_update_state
    LockGuard guard(animation_ctx.thread_context.anim_lock);
    animation_ctx._audio = &audio;
  }
  animation_ctx.init_cond.notify_all();
  audio._config = &config;
  audio._configs_reloaded_cond = &configs_reloaded_cond;
  audio._config_generation = &config_generation;
  atomic_store(&audio.ready, true);
  audio.init_cond.notify_all();

  audio._configs_reloaded_cond->notify_all();

  // assert(audio._backend);
  details::setup_stream(audio);

  // start audio thread
  atomic_store(&audio._running, true);
  const int result = pthread_create(&audio._audio_thread, BONGOCAT_NULLPTR, audio_thread, &animation_ctx);
  if (result != 0) {
    atomic_store(&audio._running, false);
    BONGOCAT_LOG_ERROR("Failed to start audio thread: %s", strerror(errno));
    return bongocat_error_t::BONGOCAT_ERROR_THREAD;
  }

  BONGOCAT_LOG_INFO("Update monitoring started");
  return bongocat_error_t::BONGOCAT_SUCCESS;
}

void request_stop(audio_context_t& ctx) {
  atomic_store(&ctx._running, false);
  wake_eventfd(ctx.audio_config_efd._fd);
  ctx.audio_cond.notify_all();
  ctx.init_cond.notify_all();
  ctx.config_updated.notify_all();
  if (ctx._configs_reloaded_cond != BONGOCAT_NULLPTR) {
    ctx._configs_reloaded_cond->notify_all();
  }
}

bongocat_error_t restart(audio_context_t& audio, animation::animation_context_t& animation_ctx,
                         const config::config_t& config, CondVariable& configs_reloaded_cond,
                         atomic_uint64_t& config_generation) {
  BONGOCAT_LOG_INFO("Restarting audio system");
  // Stop current monitoring
  if (audio._audio_thread) {
    BONGOCAT_LOG_DEBUG("Audio thread");
    request_stop(audio);
    // pthread_cancel(ctx->_audio_thread);
    if (stop_thread_graceful_or_cancel(audio._audio_thread, audio._running) != 0) {
      BONGOCAT_LOG_ERROR("Failed to join audio thread: %s", strerror(errno));
    }
    BONGOCAT_LOG_DEBUG("Audio thread terminated");
  }

  /// @TODO: re-create context with create(), avoid duplicate code
  {
    LockGuard guard(audio.audio_lock);
    // Start new monitoring (reuse shared memory if it exists)
    if (!audio.shm) {
      audio.shm = make_allocated_mmap<audio_shared_memory_t>();
      if (audio.shm.ptr == MAP_FAILED) {
        BONGOCAT_LOG_ERROR("Failed to create shared memory for audio thread: %s", strerror(errno));
        return bongocat_error_t::BONGOCAT_ERROR_MEMORY;
      }
    }
  }

  if (!audio._local_copy_config) {
    audio._local_copy_config = make_unallocated_mmap_value<config::config_t>(config);
    if (!audio._local_copy_config) {
      BONGOCAT_LOG_ERROR("Failed to create shared memory for audio: %s", strerror(errno));
      return bongocat_error_t::BONGOCAT_ERROR_MEMORY;
    }
  }
  assert(audio._local_copy_config);
  update_config(audio, config, atomic_load(&config_generation));

  if (audio.audio_config_efd._fd < 0) {
    audio.audio_config_efd = platform::FileDescriptor(eventfd(0, EFD_NONBLOCK | EFD_CLOEXEC));
    if (audio.audio_config_efd._fd < 0) {
      BONGOCAT_LOG_ERROR("Failed to create notify pipe for update, update config: %s", strerror(errno));
      return bongocat_error_t::BONGOCAT_ERROR_FILE_IO;
    }
  }

  // re-create audio stream
  if (!audio._backend) {
    audio._backend = make_allocated_memory<audio_backend_t>();
    if (!audio._backend) [[unlikely]] {
      BONGOCAT_LOG_ERROR("Failed to allocate audio backend: %s", strerror(errno));
      return bongocat_error_t::BONGOCAT_ERROR_MEMORY;
    }
  }
  assert(audio._backend);
  details::teardown_stream(audio);
  details::setup_stream(audio);

  // if (trigger_ctx._audio != ctx._audio) {
  //     BONGOCAT_LOG_DEBUG("Audio context in animation differs from animation trigger update context");
  // }

  // set extern/global references
  {
    // guard for anim_update_state
    LockGuard guard(animation_ctx.thread_context.anim_lock);
    animation_ctx._audio = &audio;
  }
  audio._config = &config;
  audio._configs_reloaded_cond = &configs_reloaded_cond;
  audio._config_generation = &config_generation;
  atomic_store(&audio.config_seen_generation, atomic_load(&config_generation));
  audio.init_cond.notify_all();
  audio._configs_reloaded_cond->notify_all();

  // start audio monitoring
  atomic_store(&audio._running, true);
  const int result = pthread_create(&audio._audio_thread, BONGOCAT_NULLPTR, audio_thread, &animation_ctx);
  if (result != 0) {
    atomic_store(&audio._running, false);
    BONGOCAT_LOG_ERROR("Failed to start audio thread: %s", strerror(errno));
    return bongocat_error_t::BONGOCAT_ERROR_THREAD;
  }

  BONGOCAT_LOG_INFO("Update audio restarted");
  return bongocat_error_t::BONGOCAT_SUCCESS;
}

void stop(audio_context_t& ctx) {
  request_stop(ctx);
  if (ctx._audio_thread) {
    BONGOCAT_LOG_DEBUG("Stopping audio thread");
    // pthread_cancel(ctx->_update_thread);
    if (stop_thread_graceful_or_cancel(ctx._audio_thread, ctx._running) != 0) {
      BONGOCAT_LOG_ERROR("Failed to join audio thread: %s", strerror(errno));
    }
    BONGOCAT_LOG_DEBUG("Audio thread terminated");
  }
  ctx._audio_thread = 0;

  details::teardown_stream(ctx);

  ctx._config = BONGOCAT_NULLPTR;
  ctx._configs_reloaded_cond = BONGOCAT_NULLPTR;
  ctx._config_generation = BONGOCAT_NULLPTR;

  ctx.config_updated.notify_all();
  atomic_store(&ctx.ready, false);
  ctx.init_cond.notify_all();
}

void trigger_audio_config(audio_context_t& audio, const config::config_t& config, uint64_t config_generation) {
  audio._config = &config;
  if (write(audio.audio_config_efd._fd, &config_generation, sizeof(uint64_t)) >= 0) {
    BONGOCAT_LOG_VERBOSE("Write audio trigger update config");
  } else {
    BONGOCAT_LOG_ERROR("Failed to write to notify pipe in audio: %s", strerror(errno));
  }
}

void update_config(audio_context_t& audio, const config::config_t& config, uint64_t new_gen) {
  assert(audio._local_copy_config);

  *audio._local_copy_config = config;

  atomic_store(&audio.config_seen_generation, new_gen);
  // Signal main that reload is done
  audio.config_updated.notify_all();
}
}  // namespace bongocat::platform::audio
