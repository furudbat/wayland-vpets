#include "platform/audio/audio.h"

#include "graphics/animation.h"
#include "platform/wayland.h"
#include "utils/memory.h"

#include <cassert>
#include <cctype>
#include <cstdio>
#include <fcntl.h>
#include <linux/input.h>
#include <poll.h>
#include <pthread.h>
#include <sys/epoll.h>
#include <sys/eventfd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/timerfd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

namespace bongocat::platform::audio {

inline static constexpr int MAX_ATTEMPTS = 2048;

static inline constexpr time_ms_t AUDIO_POOL_TIMEOUT_MS = 1000;
static inline constexpr time_ms_t COND_STORED_TIMEOUT_MS = 1000;
static inline constexpr time_ms_t THREAD_SLEEP_MS = 1000;

inline static constexpr time_ms_t COND_ANIMATION_TRIGGER_INIT_TIMEOUT_MS = 5000;
inline static constexpr time_ms_t COND_RELOAD_CONFIGS_TIMEOUT_MS = 5000;

static void cleanup_audio_thread(void *arg) {
  assert(arg);
  const animation::animation_context_t& animation_context = *static_cast<animation::animation_context_t *>(arg);
  assert(animation_context._audio);
  audio_context_t& audio = *animation_context._audio;

  atomic_store(&audio._running, false);

  audio.config_updated.notify_all();

  BONGOCAT_LOG_INFO("Audio thread cleanup completed (via pthread_cancel)");
}

static void *audio_thread(void *arg) {
  assert(arg);
  animation::animation_context_t& animation_ctx = *static_cast<animation::animation_context_t *>(arg);

  // from thread context
  // animation_context_t& anim = trigger_ctx.anim;
  // wait for input context (in animation start)
  animation_ctx.init_cond.timedwait([&]() { return atomic_load(&animation_ctx.ready); },
                                    COND_ANIMATION_TRIGGER_INIT_TIMEOUT_MS);
  assert(animation_ctx._audio != BONGOCAT_NULLPTR);
  audio_context_t& audio = *animation_ctx._audio;

  // sanity checks
  assert(audio._config != BONGOCAT_NULLPTR);
  assert(audio._configs_reloaded_cond != BONGOCAT_NULLPTR);
  assert(!audio._running);
  assert(audio.shm);
  assert(audio._local_copy_config);

  // trigger initial render
  wayland::request_render(animation_ctx);

  pthread_cleanup_push(cleanup_audio_thread, arg);

  // local thread context
  /// event poll
  // 0:       reload config event
  // @TODO: add more fds for internal thread context
  constexpr size_t nfds = 1;
  pollfd pfds[nfds];

  atomic_store(&audio._running, true);
  while (atomic_load(&audio._running)) {
    pthread_testcancel();  // optional, but makes cancellation more responsive

    // read from config
    time_ms_t timeout_ms = AUDIO_POOL_TIMEOUT_MS;
    /// @TODO: variables read from config/animation
    /// update properties depending on config
    {
      // read-only config
      assert(audio._local_copy_config);
      // const config::config_t& current_config = *audio._local_copy_config;

      // enable_debug = current_config.enable_debug;

      {
        LockGuard guard(animation_ctx.thread_context.anim_lock);
        assert(animation_ctx.thread_context.shm);

        /// @TODO: update thread variables from animations
      }

      // update audio properties
      /// @TODO: update thread variables from config
    }

    // init pfds
    constexpr size_t fds_audio_config_index = 0;
    /// @TODO: add more fds_..._index
    pfds[fds_audio_config_index] = {.fd = audio.audio_config_efd._fd, .events = POLLIN, .revents = 0};
    /// @TODO: init more pfds[...] = {...};

    // poll events
    const int poll_result = poll(pfds, nfds, static_cast<int>(timeout_ms));
    if (poll_result < 0) {
      if (errno == EINTR) {
        continue;  // Interrupted by signal
      }
      BONGOCAT_LOG_ERROR("update: Poll error: %s", strerror(errno));
      break;
    }

    // cancel pooling (when not running anymore)
    if (!atomic_load(&audio._running)) {
      // draining pools
      for (size_t i = 0; i < nfds; i++) {
        if (pfds[i].revents & POLLIN) {
          drain_event(pfds[i], MAX_ATTEMPTS);
        }
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

    // @TODO: Handle other fds
    // if (pfds[...].revents & POLLIN) {
    //}

    // @TODO: trigger animation
    /*
    bool animation_triggered = false;
    if (...) {
      LockGuard guard(audio.audio_lock);
      assert(audio.shm);
      auto& audio_shm = *audio.shm;

      // read-only config
      assert(audio._local_copy_config);
      const config::config_t& current_config = *audio._local_copy_config;

      animation::trigger(animation_ctx, animation::trigger_animation_cause_mask_t::...);
    }
    */

    // handle update config
    if (reload_config) {
      assert(audio._config_generation != BONGOCAT_NULLPTR);
      assert(audio._configs_reloaded_cond != BONGOCAT_NULLPTR);
      assert(audio._config != BONGOCAT_NULLPTR);

      update_config(audio, *audio._config, new_gen);

      // wait for reload config to be done (all configs)
      const int rc = audio._configs_reloaded_cond->timedwait(
          [&] { return atomic_load(audio._config_generation) >= new_gen; }, COND_RELOAD_CONFIGS_TIMEOUT_MS);
      if (rc == ETIMEDOUT) {
        BONGOCAT_LOG_WARNING("audio: Timed out waiting for reload eventfd: %s", strerror(errno));
      }
      if constexpr (features::Debug) {
        if (atomic_load(&audio.config_seen_generation) < atomic_load(audio._config_generation)) {
          BONGOCAT_LOG_VERBOSE("audio: audio.config_seen_generation < update._config_generation; %d < %d",
                               atomic_load(&audio.config_seen_generation), atomic_load(audio._config_generation));
        }
      }
      // assert(atomic_load(&audio.config_seen_generation) >= atomic_load(audio._config_generation));
      atomic_store(&audio.config_seen_generation, atomic_load(audio._config_generation));
      BONGOCAT_LOG_INFO("audio: Audio config reloaded (gen=%u)", new_gen);
    }

    /// @TODO minimal sleep ?

    /// @TODO: dummy exit, remove after done
    atomic_store(&audio._running, false);
  }

  atomic_store(&audio._running, false);

  // Will run only on normal return
  pthread_cleanup_pop(1);  // 1 = call cleanup even if not canceled

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
    BONGOCAT_LOG_ERROR("Failed to create notify pipe for update update config: %s", strerror(errno));
    return bongocat_error_t::BONGOCAT_ERROR_FILE_IO;
  }

  /// @TODO: init thread context variables and shm

  // Initialize shared memory for local config
  ret->_local_copy_config = make_allocated_mmap<config::config_t>();
  if (!ret->_local_copy_config) [[unlikely]] {
    BONGOCAT_LOG_ERROR("Failed to create shared memory for input monitoring: %s", strerror(errno));
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

  // start update thread
  const int result = pthread_create(&audio._audio_thread, BONGOCAT_NULLPTR, audio_thread, &animation_ctx);
  if (result != 0) {
    BONGOCAT_LOG_ERROR("Failed to start audio thread: %s", strerror(errno));
    return bongocat_error_t::BONGOCAT_ERROR_THREAD;
  }

  BONGOCAT_LOG_INFO("Update monitoring started");
  return bongocat_error_t::BONGOCAT_SUCCESS;
}

bongocat_error_t restart(audio_context_t& audio, animation::animation_context_t& animation_ctx,
                         const config::config_t& config, CondVariable& configs_reloaded_cond,
                         atomic_uint64_t& config_generation) {
  BONGOCAT_LOG_INFO("Restarting audio system");
  // Stop current monitoring
  if (audio._audio_thread) {
    BONGOCAT_LOG_DEBUG("Audio thread");
    atomic_store(&audio._running, false);
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

  /// @TODO: re-init/restart audio internal thread context varaibles

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

  // start update monitoring
  const int result = pthread_create(&audio._audio_thread, BONGOCAT_NULLPTR, audio_thread, &animation_ctx);
  if (result != 0) {
    BONGOCAT_LOG_ERROR("Failed to start audio thread: %s", strerror(errno));
    return bongocat_error_t::BONGOCAT_ERROR_THREAD;
  }

  BONGOCAT_LOG_INFO("Update audio restarted");
  return bongocat_error_t::BONGOCAT_SUCCESS;
}

void stop(audio_context_t& ctx) {
  atomic_store(&ctx._running, false);
  if (ctx._audio_thread) {
    BONGOCAT_LOG_DEBUG("Stopping audio thread");
    // pthread_cancel(ctx->_update_thread);
    if (stop_thread_graceful_or_cancel(ctx._audio_thread, ctx._running) != 0) {
      BONGOCAT_LOG_ERROR("Failed to join audio thread: %s", strerror(errno));
    }
    BONGOCAT_LOG_DEBUG("Update thread terminated");
  }
  ctx._audio_thread = 0;

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
