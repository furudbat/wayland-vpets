#ifndef BONGOCAT_AUDIO_CONTEXT_H
#define BONGOCAT_AUDIO_CONTEXT_H

#include "audio_shared_memory.h"
#include "config/config.h"
#include "module.h"
#include "utils/system_memory.h"

#include <cstddef>
#include <cstdint>
#include <pthread.h>
#include <stdatomic.h>

#ifdef BONGOCAT_ENABLE_AUDIO_MODULE
#  include <spa/utils/hook.h>

// PipeWire and cavacore
struct pw_loop;
struct pw_context;
struct pw_core;
struct pw_stream;
struct cava_plan;
#endif

namespace bongocat::platform::audio {

#if BONGOCAT_AUDIO_MODULE_ON

/// ~~stereo~~ -> mono -- @TODO: more testing, do I really need 2 channels ?
inline static constexpr size_t MAX_CHANNELS     = 1;

inline static constexpr int CAVA_BARS = 12;
inline static constexpr int CAVA_OUT_SIZE = static_cast<size_t>(CAVA_BARS) * MAX_CHANNELS;
static_assert(CAVA_BARS > 0);
static_assert(MAX_CHANNELS > 0);

using sample_buffer_bytes_t = double;

struct audio_backend_t {
  // PipeWire
  pw_loop *loop{BONGOCAT_NULLPTR};
  pw_context *context{BONGOCAT_NULLPTR};
  pw_core *core{BONGOCAT_NULLPTR};
  pw_stream *stream{BONGOCAT_NULLPTR};
  spa_hook stream_listener{};
  bool thread_loop_entered{false};  // loop entered by the audio thread

  // stream state
  bool needs_reconnect{false};
  timestamp_ms_t reconnect_at{0};

  // negotiated format
  uint32_t rate{0};
  uint32_t channels{0};

  // cavacore
  cava_plan *cava{BONGOCAT_NULLPTR};
  AllocatedArray<sample_buffer_bytes_t> cava_in;   // use allocated array, buffer can become huge (lazy init)
  size_t cava_in_count{0};
  size_t cava_in_used{0};                           // for wiping only the used part
  double cava_out[CAVA_OUT_SIZE]{};

  // RMS (silence detection)
  double rms_acc{0};
  size_t rms_n{0};
};
#else
struct audio_backend_t {};
#endif

BONGOCAT_STUBS_BEGIN

struct audio_context_t;
BONGOCAT_AUDIO_STUB_INLINE void stop(audio_context_t& ctx) BONGOCAT_AUDIO_STUB;
void cleanup(audio_context_t& ctx);

struct audio_context_t {
  // local copy from other thread, update after reload (shared memory)
  MMapMemory<config::config_t> _local_copy_config;
  MMapMemory<audio_shared_memory_t> shm;

  atomic_bool _running{false};
  pthread_t _audio_thread{0};
  // lock for shm
  Mutex audio_lock;
  platform::CondVariable audio_cond;

  AllocatedMemory<audio_backend_t> _backend;
  int pw_loop_fd{-1};

  // config reload threading
  FileDescriptor audio_config_efd;  // get new_gen from here
  atomic_uint64_t config_seen_generation{0};
  platform::CondVariable config_updated;

  // globals (references)
  const config::config_t *_config{BONGOCAT_NULLPTR};
  platform::CondVariable *_configs_reloaded_cond{BONGOCAT_NULLPTR};
  atomic_uint64_t *_config_generation{BONGOCAT_NULLPTR};
  atomic_bool ready;
  platform::CondVariable init_cond;

  audio_context_t() = default;
  ~audio_context_t() {
    cleanup(*this);
  }

  audio_context_t(const audio_context_t&) = delete;
  audio_context_t& operator=(const audio_context_t&) = delete;
  audio_context_t(audio_context_t&& other) noexcept = delete;
  audio_context_t& operator=(audio_context_t&& other) noexcept = delete;
};
inline void cleanup(audio_context_t& ctx) {
  if (atomic_load(&ctx._running)) {
    stop(ctx);
    // audio_lock should be unlocked
  }
  atomic_store(&ctx._running, false);
  ctx._audio_thread = 0;

  release_allocated_memory(ctx._backend);
  ctx.pw_loop_fd = -1;

  close_fd(ctx.audio_config_efd);
  atomic_store(&ctx.config_seen_generation, 0);

  release_allocated_mmap_memory(ctx._local_copy_config);
  release_allocated_mmap_memory(ctx.shm);

  ctx._config = BONGOCAT_NULLPTR;
  ctx._configs_reloaded_cond = BONGOCAT_NULLPTR;
  ctx._config_generation = BONGOCAT_NULLPTR;
  atomic_store(&ctx.ready, false);
  ctx.init_cond.notify_all();
}

BONGOCAT_STUBS_END

}  // namespace bongocat::platform::audio

#endif