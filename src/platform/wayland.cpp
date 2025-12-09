#include "platform/wayland.h"

#include "../graphics/bar.h"
#include "graphics/animation.h"
#include "platform/wayland-protocols.hpp"
#include "platform/wayland_context.h"
#include "platform/wayland_shared_memory.h"
#include "utils/memory.h"
#include "wayland_hyprland.h"

#include <cassert>
#include <cerrno>
#include <climits>
#include <csignal>
#include <cstdio>
#include <cstdlib>
#include <fcntl.h>
#include <poll.h>
#include <pthread.h>
#include <sys/mman.h>
#include <sys/signalfd.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <wayland-client.h>
// #include "wayland_sway.h"
#include "platform/wayland_callbacks.h"
#include "platform/wayland_setups.h"

namespace bongocat::platform::wayland {
// =============================================================================
// GLOBAL STATE AND CONFIGURATION
// =============================================================================

static inline constexpr time_ms_t CHECK_INTERVAL_MS = 100;
static inline constexpr time_ms_t POOL_MIN_TIMEOUT_MS = 5;
static inline constexpr time_ms_t POOL_MAX_TIMEOUT_MS = 1000;
static_assert(POOL_MAX_TIMEOUT_MS >= POOL_MIN_TIMEOUT_MS);

inline static constexpr time_ms_t COND_INIT_TIMEOUT_MS = 5000;

static inline constexpr auto WAYLAND_LAYER_NAME = "OVERLAY";

// =============================================================================
// MAIN WAYLAND INTERFACE IMPLEMENTATION
// =============================================================================

created_result_t<AllocatedMemory<wayland_context_t>> create(animation::animation_context_t& animation_ctx,
                                                            const config::config_t& config) {
  AllocatedMemory<wayland_context_t> ret = make_allocated_memory<wayland_context_t>();
  assert(ret);
  if (!ret) [[unlikely]] {
    return bongocat_error_t::BONGOCAT_ERROR_MEMORY;
  }

  ret->animation_context = &animation_ctx;
  ret->thread_context._bar_height = DEFAULT_BAR_HEIGHT;

  // Initialize shared memory
  ret->thread_context.ctx_shm = make_allocated_mmap<wayland_shared_memory_t>();
  if (!ret->thread_context.ctx_shm) [[unlikely]] {
    BONGOCAT_LOG_ERROR("Failed to create shared memory for animation system: %s", strerror(errno));
    return bongocat_error_t::BONGOCAT_ERROR_MEMORY;
  }
  if (ret->thread_context.ctx_shm) [[unlikely]] {
    static_assert(WAYLAND_NUM_BUFFERS <= INT_MAX);
    for (size_t i = 0; i < WAYLAND_NUM_BUFFERS; i++) {
      ret->thread_context.ctx_shm->buffers[i] = {};
    }
    atomic_store(&ret->thread_context.ctx_shm->configured, false);
  }

  // Initialize shared memory for local config
  ret->thread_context._local_copy_config = make_allocated_mmap<config::config_t>();
  if (!ret->thread_context._local_copy_config) [[unlikely]] {
    BONGOCAT_LOG_ERROR("Failed to create shared memory for animation system: %s", strerror(errno));
    return bongocat_error_t::BONGOCAT_ERROR_MEMORY;
  }
  assert(ret->thread_context._local_copy_config);
  *ret->thread_context._local_copy_config = config;
  ret->thread_context._bar_height = config.overlay_height;

  return ret;
}

bongocat_error_t setup(wayland_context_t& ctx, animation::animation_context_t& animation_ctx) {
  ctx.animation_context = &animation_ctx;

  if (!ctx.thread_context.ctx_shm) [[unlikely]] {
    BONGOCAT_LOG_ERROR("Failed to create shared memory for animation system: %s", strerror(errno));
    return bongocat_error_t::BONGOCAT_ERROR_MEMORY;
  }
  if (!ctx.thread_context._local_copy_config) [[unlikely]] {
    BONGOCAT_LOG_ERROR("Failed to create shared memory for animation system: %s", strerror(errno));
    return bongocat_error_t::BONGOCAT_ERROR_MEMORY;
  }

  BONGOCAT_LOG_INFO("Initializing Wayland connection");

  ctx.thread_context.display = wl_display_connect(BONGOCAT_NULLPTR);
  if (ctx.thread_context.display == BONGOCAT_NULLPTR) {
    BONGOCAT_LOG_ERROR("Failed to connect to Wayland display");
    return bongocat_error_t::BONGOCAT_ERROR_WAYLAND;
  }

  bongocat_error_t result = details::wayland_setup_protocols(ctx);
  if (result != bongocat_error_t::BONGOCAT_SUCCESS) {
    return result;
  }
  result = details::wayland_setup_surface(ctx);
  if (result != bongocat_error_t::BONGOCAT_SUCCESS) {
    return result;
  }
  result = details::wayland_setup_buffer(ctx.thread_context, *ctx.animation_context);
  if (result != bongocat_error_t::BONGOCAT_SUCCESS) {
    return result;
  }

  atomic_store(&ctx.ready, true);

  BONGOCAT_LOG_INFO("Wayland initialization complete (%dx%d buffer)", ctx.thread_context._screen_width,
                    ctx.thread_context._bar_height);
  return bongocat_error_t::BONGOCAT_SUCCESS;
}

bongocat_error_t run(wayland_context_t& ctx, volatile sig_atomic_t& running, int signal_fd,
                     input::input_context_t& input, const config::config_t& config,
                     const config::config_watcher_t *config_watcher, config_reload_callback_t config_reload_callback) {
  BONGOCAT_CHECK_NULL(config_reload_callback, bongocat_error_t::BONGOCAT_ERROR_INVALID_PARAM);
  BONGOCAT_CHECK_NULL(ctx.animation_context, bongocat_error_t::BONGOCAT_ERROR_INVALID_PARAM);

  // from thread context
  wayland_thread_context& wayland_ctx = ctx.thread_context;
  // animation_context_t& anim = trigger_ctx.anim;
  //  wait for context
  ctx.animation_context->init_cond.timedwait([&]() { return atomic_load(&ctx.animation_context->ready); },
                                             COND_INIT_TIMEOUT_MS);
  input.init_cond.timedwait([&]() { return atomic_load(&ctx.animation_context->ready); }, COND_INIT_TIMEOUT_MS);
  animation::animation_context_t& animation_ctx = *ctx.animation_context;
  assert(animation_ctx._input != BONGOCAT_NULLPTR);
  assert(animation_ctx._input == &input);
  // wayland_shared_memory_t *wayland_ctx_shm = wayland_ctx.ctx_shm;

  BONGOCAT_LOG_INFO("Starting Wayland event loop");

  running = 1;
  while (running >= 1 && wayland_ctx.display != BONGOCAT_NULLPTR) {
    const time_ms_t frame_based_timeout = config.fps > 0 ? 1000 / config.fps : 0;
    // Periodic fullscreen check for fallback fullscreen detection
    timeval now{};
    gettimeofday(&now, BONGOCAT_NULLPTR);
    const time_ms_t elapsed_ms = ((now.tv_sec - ctx.fs_detector.last_check.tv_sec) * 1000L) +
                                 ((now.tv_usec - ctx.fs_detector.last_check.tv_usec) / 1000L);
    time_ms_t fullscreen_check_interval = frame_based_timeout;
    if (fullscreen_check_interval < CHECK_INTERVAL_MS) {
      fullscreen_check_interval = CHECK_INTERVAL_MS;
    }
    if (elapsed_ms >= fullscreen_check_interval) {
      details::fs_update_state_fallback(ctx);
      ctx.fs_detector.last_check = now;
    }

    // Handle Wayland events
    constexpr size_t fds_signals_index = 0;
    constexpr size_t fds_config_reload_index = 1;
    constexpr size_t fds_animation_render_index = 2;
    constexpr size_t fds_wayland_index = 3;
    constexpr nfds_t fds_count = 4;
    pollfd fds[fds_count] = {
        {.fd = signal_fd,                                                                .events = POLLIN, .revents = 0},
        {.fd = config_watcher != BONGOCAT_NULLPTR ? config_watcher->reload_efd._fd : -1,
         .events = POLLIN,
         .revents = 0                                                                                                  },
        {.fd = animation_ctx.render_efd._fd,                                             .events = POLLIN, .revents = 0},
        {.fd = wl_display_get_fd(wayland_ctx.display),                                   .events = POLLIN, .revents = 0},
    };
    static_assert(fds_count == LEN_ARRAY(fds));

    // compute desired timeout
    time_ms_t timeout_ms = frame_based_timeout;
    if (timeout_ms < POOL_MIN_TIMEOUT_MS) {
      timeout_ms = POOL_MIN_TIMEOUT_MS;
    }
    if (timeout_ms > POOL_MAX_TIMEOUT_MS) {
      timeout_ms = POOL_MAX_TIMEOUT_MS;
    }

    // avoid reloading twice, by signal OR watcher
    bool config_reload_requested = false;
    bool render_requested = false;
    bool needs_flush = false;
    bool toggle_visibility_requested = false;

    bool prepared_read = false;
    {
      int attempts = 0;
      while (wl_display_prepare_read(wayland_ctx.display) != 0 && attempts < MAX_ATTEMPTS) {
        wl_display_dispatch_pending(wayland_ctx.display);
        attempts++;
      }
      prepared_read = attempts < MAX_ATTEMPTS;
    }

    if (prepared_read) {
      // Try to flush queued requests to the compositor so it can process them and send replies.
      // If flush would block (EAGAIN), cancel the prepared read and dispatch pending events to make progress.
      const int flush_ret = wl_display_flush(wayland_ctx.display);
      if (flush_ret == -1 && errno == EAGAIN) {
        // send buffer full; need to make progress by reading pending events first
        wl_display_cancel_read(wayland_ctx.display);
        if (wl_display_dispatch_pending(wayland_ctx.display) == -1) {
          BONGOCAT_LOG_ERROR("wl_display_dispatch_pending failed after EAGAIN");
          running = 0;
        }
      } else if (flush_ret == -1) {
        BONGOCAT_LOG_ERROR("wl_display_flush failed: %s", strerror(errno));
        wl_display_cancel_read(wayland_ctx.display);
        if (wl_display_dispatch_pending(wayland_ctx.display) == -1) {
          running = 0;
        }
      }
    }

    assert(timeout_ms <= INT_MAX);
    const int poll_result = poll(fds, fds_count, static_cast<int>(timeout_ms));
    if (poll_result > 0) {
      // signal events
      if (fds[fds_signals_index].revents & POLLIN) {
        signalfd_siginfo fdsi{};
        const ssize_t s = read(fds[fds_signals_index].fd, &fdsi, sizeof(fdsi));
        if (s != sizeof(fdsi)) {
          BONGOCAT_LOG_ERROR("Failed to read signal fd");
        } else {
          switch (fdsi.ssi_signo) {
          case SIGINT:
          case SIGTERM:
          case SIGQUIT:  // Handle Ctrl+\ for graceful shutdown
          case SIGHUP:   // Handle terminal hangup
            BONGOCAT_LOG_INFO("Received signal %d, shutting down gracefully", fdsi.ssi_signo);
            running = 0;
            break;
          case SIGCHLD:
            // Handle child process termination - reap zombies
            while (waitpid(-1, BONGOCAT_NULLPTR, WNOHANG) > 0) {}
            break;
          case SIGUSR1:
            BONGOCAT_LOG_INFO("Received SIGUSR1, toggle bar visibility");
            toggle_visibility_requested = true;
            break;
          case SIGUSR2:
            BONGOCAT_LOG_INFO("Received SIGUSR2, reloading config");
            config_reload_requested = true;
            break;
          default:
            BONGOCAT_LOG_WARNING("Received unexpected signal %d", fdsi.ssi_signo);
            break;
          }
        }
      }
      if (!running) {
        // draining pools
        for (size_t i = 0; i < fds_count; i++) {
          platform::drain_event(fds[i], MAX_ATTEMPTS);
        }
        if (prepared_read) {
          wl_display_cancel_read(wayland_ctx.display);
        }
        render_requested = false;
        toggle_visibility_requested = false;
        break;
      }

      // reload config event
      if (fds[fds_config_reload_index].revents & POLLIN) {
        BONGOCAT_LOG_DEBUG("Receive reload event");
        if (config_watcher != BONGOCAT_NULLPTR) {
          platform::drain_event(fds[fds_config_reload_index], MAX_ATTEMPTS, "update config eventfd");
        }
        config_reload_requested = true;
      }

      // render event
      if (fds[fds_animation_render_index].revents & POLLIN) {
        BONGOCAT_LOG_VERBOSE("Receive render event");
        platform::drain_event(fds[fds_animation_render_index], MAX_ATTEMPTS, "render eventfd");
        if (atomic_load(&wayland_ctx.ctx_shm->configured)) {
          render_requested = true;
        }
      }

      // wayland events
      if (prepared_read) {
        if (fds[fds_wayland_index].revents & POLLIN) {
          if (wl_display_read_events(wayland_ctx.display) == -1 ||
              wl_display_dispatch_pending(wayland_ctx.display) == -1) {
            BONGOCAT_LOG_ERROR("Failed to handle Wayland events: %s", strerror(errno));
            running = 0;
            return bongocat_error_t::BONGOCAT_ERROR_WAYLAND;
          }
        } else {
          wl_display_cancel_read(wayland_ctx.display);
        }
      } else {
        if (fds[fds_wayland_index].revents & POLLIN) {
          if (wl_display_dispatch_pending(wayland_ctx.display) == -1) {
            BONGOCAT_LOG_ERROR("Failed to dispatch pending events: %s", strerror(errno));
            running = 0;
            return bongocat_error_t::BONGOCAT_ERROR_WAYLAND;
          }
        } else {
          // dispatch any events already read
          if (wl_display_dispatch_pending(wayland_ctx.display) == -1) {
            BONGOCAT_LOG_ERROR("Failed to dispatch pending Wayland events: %s", strerror(errno));
            running = 0;
            return bongocat_error_t::BONGOCAT_ERROR_WAYLAND;
          }
        }
      }

      if (render_requested) {
        if (!atomic_load(&wayland_ctx.ctx_shm->configured)) {
          BONGOCAT_LOG_VERBOSE("Surface not configured yet, skip drawing");
          render_requested = false;
        }
      }

      BONGOCAT_LOG_VERBOSE("Poll revents: poll_result=%d; signal=%x, reload=%x, render=%x, wayland=%x", poll_result,
                           fds[fds_signals_index].revents, fds[fds_config_reload_index].revents,
                           fds[fds_animation_render_index].revents, fds[fds_wayland_index].revents);
    } else if (poll_result == 0) {
      if (prepared_read) {
        wl_display_cancel_read(wayland_ctx.display);
      }
      if (wl_display_dispatch_pending(wayland_ctx.display) == -1) {
        BONGOCAT_LOG_ERROR("Failed to dispatch pending events");
        running = 0;
        return bongocat_error_t::BONGOCAT_ERROR_WAYLAND;
      }
    } else {
      if (prepared_read) {
        wl_display_cancel_read(wayland_ctx.display);
      }
      if (errno != EINTR) {
        BONGOCAT_LOG_ERROR("Poll error: %s", strerror(errno));
        running = 0;
        return bongocat_error_t::BONGOCAT_ERROR_WAYLAND;
      }
    }

    // do reload once
    if (config_reload_requested && config_reload_callback) {
      config_reload_callback();
      render_requested = true;
    }
    if (toggle_visibility_requested) {
      wayland_ctx.bar_visibility =
          wayland_ctx.bar_visibility == bar_visibility_t::Show ? bar_visibility_t::Hide : bar_visibility_t::Show;
      render_requested = true;
    }

    /// @TODO: release buffer fallback after timeout, fallback
    /*
    const auto now_ms = platform::get_current_time_ms();
    if (now_ms - wayland_ctx._last_frame_timestamp_ms > 500 &&
        all_buffers_busy(wayland_ctx.ctx_shm.ptr))
    {
        for (auto& buf : wayland_ctx.ctx_shm->buffers) {
            atomic_store(&buf.busy, false);
        }
        BONGOCAT_LOG_WARNING("Missed frame_done fallback: forcibly releasing stuck buffers");
    }
    */

    if (render_requested) {
      BONGOCAT_LOG_VERBOSE("Receive render event");
      BONGOCAT_LOG_VERBOSE("Try to draw_bar in wayland_run");

      if (!atomic_load(&wayland_ctx._frame_pending)) {
        wl_display_dispatch_pending(wayland_ctx.display);
        const auto draw_bar_result = animation::draw_bar(ctx);
        needs_flush = draw_bar_result == animation::draw_bar_result_t::FlushNeeded;
      } else {
        if (!atomic_exchange(&wayland_ctx._redraw_after_frame, true)) {
          BONGOCAT_LOG_VERBOSE("Queued redraw after frame");
          request_render(animation_ctx);
        } else {
          const auto draw_bar_result = animation::draw_bar(ctx);
          needs_flush = draw_bar_result == animation::draw_bar_result_t::FlushNeeded;
        }
      }
      render_requested = false;
    }
    toggle_visibility_requested = false;

    if (needs_flush) {
      const int flush_ret = wl_display_flush(wayland_ctx.display);
      if (flush_ret == -1 && errno == EAGAIN) {
        // send buffer full; need to make progress by reading pending events first
        wl_display_cancel_read(wayland_ctx.display);
        if (wl_display_dispatch_pending(wayland_ctx.display) == -1) {
          BONGOCAT_LOG_ERROR("wl_display_dispatch_pending failed after EAGAIN");
          running = 0;
        }
      } else if (flush_ret == -1) {
        BONGOCAT_LOG_ERROR("wl_display_flush failed: %s", strerror(errno));
        wl_display_cancel_read(wayland_ctx.display);
        if (wl_display_dispatch_pending(wayland_ctx.display) == -1) {
          running = 0;
        }
      }
    }
  }
  running = 0;

  BONGOCAT_LOG_INFO("Wayland event loop exited");
  return bongocat_error_t::BONGOCAT_SUCCESS;
}

// =============================================================================
// PUBLIC API IMPLEMENTATION
// =============================================================================

int get_screen_width(const wayland_context_t& ctx) {
  return ctx.thread_context._screen_info != BONGOCAT_NULLPTR ? ctx.thread_context._screen_info->screen_width : 0;
}

void update_config(wayland_context_t& ctx, const config::config_t& config,
                   animation::animation_context_t& animation_ctx) {
  assert(ctx.thread_context._local_copy_config);

  // Check if dimensions changed - requires buffer/surface recreation
  const auto old_height =
      ctx.thread_context._local_copy_config ? ctx.thread_context._local_copy_config->overlay_height : 0;
  const auto old_width = ctx.thread_context._screen_width;

  // update old config
  *ctx.thread_context._local_copy_config = config;

  const bool dimensions_changed = (old_height != ctx.thread_context._local_copy_config->overlay_height) ||
                                  (ctx.thread_context._local_copy_config->screen_width > 0 &&
                                   old_width != ctx.thread_context._local_copy_config->screen_width);

  if (dimensions_changed && old_height > 0 && old_width > 0 && ctx.thread_context.ctx_shm) {
    // ~~Lock animation mutex to prevent draw_bar() during config update
    // This is critical - animation thread must not access buffer while we
    // recreate it~~
    // not sure if this is needed, animation thread don't touch the bar directly,
    // it just triggers a rerender
    platform::LockGuard anim_guard(animation_ctx.thread_context.anim_lock);

    BONGOCAT_LOG_INFO("Dimensions changed (%dx%d -> %dx%d), recreating buffer...", old_width, old_height,
                      ctx.thread_context._local_copy_config->screen_width,
                      ctx.thread_context._local_copy_config->overlay_height);

    // Mark as not configured first
    assert(ctx.thread_context.ctx_shm);
    atomic_store(&ctx.thread_context.ctx_shm->configured, false);

    if (details::wayland_update_screen_width(ctx) != bongocat_error_t::BONGOCAT_SUCCESS) {
      BONGOCAT_LOG_ERROR("Failed to update width for bar");
      return;
    }
    ctx.thread_context._bar_height = config.overlay_height;

    if (ctx.thread_context._screen_width > 0 && ctx.thread_context._bar_height > 0) {
      // Cleanup old buffer
      cleanup_wayland_context_buffer(ctx.thread_context);

      // Cleanup old surface
      cleanup_wayland_context_surface(ctx.thread_context);

      if (details::wayland_update_screen_width(ctx) != bongocat_error_t::BONGOCAT_SUCCESS) {
        BONGOCAT_LOG_ERROR("Failed to update width for bar");
        return;
      }
      ctx.thread_context._bar_height = config.overlay_height;

      // Recreate surface and buffer with new dimensions
      if (details::wayland_setup_surface(ctx) != bongocat_error_t::BONGOCAT_SUCCESS) {
        BONGOCAT_LOG_ERROR("Failed to recreate surface after config change");
        return;
      }
      if (details::wayland_setup_buffer(ctx.thread_context, animation_ctx) != bongocat_error_t::BONGOCAT_SUCCESS) {
        BONGOCAT_LOG_ERROR("Failed to recreate buffer after config change");
        return;
      }

      atomic_store(&ctx.thread_context.ctx_shm->configured, true);

      // Wait for new configure event
      wl_display_roundtrip(ctx.thread_context.display);

      BONGOCAT_LOG_INFO("Buffer recreated successfully (%dx%d)", ctx.thread_context._local_copy_config->screen_width,
                        ctx.thread_context._local_copy_config->overlay_height);
    } else {
      BONGOCAT_LOG_ERROR("Buffer recreated failed (%dx%d)", ctx.thread_context._local_copy_config->screen_width,
                         ctx.thread_context._local_copy_config->overlay_height);
    }
  }

  /// @NOTE: assume animation has the same local copy as wayland config
  // animation_update_config(anim, config);
  if (atomic_load(&ctx.thread_context.ctx_shm->configured)) {
    request_render(animation_ctx);
  }
}

const char *get_current_layer_name() {
  return WAYLAND_LAYER_NAME;
}

bongocat_error_t request_render(animation::animation_context_t& animation_ctx) {
  if (animation_ctx.render_efd._fd < 0) {
    return bongocat_error_t::BONGOCAT_ERROR_INVALID_PARAM;
  }

  constexpr uint64_t u = 1;
  const ssize_t s = write(animation_ctx.render_efd._fd, &u, sizeof(u));
  if (s != sizeof(u)) {
    BONGOCAT_LOG_WARNING("Failed to write render eventfd: %s", strerror(errno));
    return bongocat_error_t::BONGOCAT_ERROR_FILE_IO;
  }

  return bongocat_error_t::BONGOCAT_SUCCESS;
}
}  // namespace bongocat::platform::wayland
