#include "platform/wayland_callbacks.h"

#include "../graphics/bar.h"
#include "graphics/animation.h"
#include "platform/wayland-protocols.hpp"
#include "platform/wayland.h"
#include "platform/wayland_context.h"
#include "platform/wayland_setups.h"
#include "platform/wayland_shared_memory.h"
#include "utils/memory.h"
#include "wayland_hyprland.h"
#include "wayland_sway.h"

#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <pthread.h>
#include <sys/signalfd.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <wayland-client.h>

namespace bongocat::platform::wayland::details {

#ifdef __cplusplus
#  define wl_array_for_each_typed(pos, array, type)           \
    for (type *pos = reinterpret_cast<type *>((array)->data); \
         reinterpret_cast<const char *>(pos) < (reinterpret_cast<const char *>((array)->data) + (array)->size); ++pos)
#endif

// =============================================================================
// ZXDG LISTENER IMPLEMENTATION
// =============================================================================

void handle_xdg_output_name(void *data, [[maybe_unused]] zxdg_output_v1 *xdg_output, const char *name) {
  if (data == BONGOCAT_NULLPTR || name == BONGOCAT_NULLPTR) {
    BONGOCAT_LOG_VERBOSE("Handler called with null data (ignored)");
    return;
  }
  auto *oref = static_cast<output_ref_t *>(data);

  /// name received
  {
    snprintf(oref->name_str, sizeof(oref->name_str), "%s", name);
    oref->received = flag_add<output_ref_received_flags_t>(oref->received, output_ref_received_flags_t::Name);
    BONGOCAT_LOG_DEBUG("xdg_output.name: xdg-output name received: %s", name);
  }

  // @NOTE: this should always be set ?
  // assert(oref->wayland);

  /// Reconnection handling
  if (oref->wayland != BONGOCAT_NULLPTR) {
    wayland_context_t& wayland_ctx = *oref->wayland;
    wayland_thread_context& wayland_thread_ctx = oref->wayland->thread_context;
    // animation_context_t& anim = *ctx.animation_context;
    // animation_trigger_context_t& trigger_ctx = *ctx.animation_trigger_context;

    // read-only config
    assert(wayland_ctx.thread_context._local_copy_config != nullptr);
    const config::config_t& current_config = *wayland_ctx.thread_context._local_copy_config;

    // Check if this is the output we're waiting for (reconnection case)
    if (!atomic_load(&wayland_ctx._output_lost)) {
      return;
    }

    bool should_reconnect = false;
    // Case 1: User specified an output name - match exactly
    if (wayland_thread_ctx.using_named_output && current_config.output_name) {
      should_reconnect = (strcmp(name, current_config.output_name.c_str()) == 0);
    }
    // Case 2: Using fallback (first output) - reconnect to any output
    else if (!wayland_thread_ctx.using_named_output) {
      should_reconnect = true;
      BONGOCAT_LOG_DEBUG("xdg_output.name: Using fallback output, accepting '%s'", name);
    }

    if (should_reconnect) {
      BONGOCAT_LOG_DEBUG("xdg_output.name: Target output '%s' reconnected!", name);

      // Set new output
      wayland_thread_ctx.output = oref->wl_output;
      wayland_thread_ctx.bound_output_name = oref->name;
      atomic_store(&oref->wayland->_output_lost, false);
      wl_display_roundtrip(wayland_thread_ctx.display);
      wayland_update_output(wayland_ctx);

      // Clean up old surface if it exists
      cleanup_wayland_context_surface(wayland_thread_ctx);

      // Recreate surface on new output
      // Note: wayland_setup_surface already commits, triggering a configure
      // event. The layer_surface_configure callback will ack and call draw_bar()
      // to render.
      if (wayland_setup_surface(*oref->wayland) == bongocat_error_t::BONGOCAT_SUCCESS) {
        assert(wayland_thread_ctx.ctx_shm);
        if (wayland_thread_ctx.ctx_shm) {
          /// @TODO: premature configured ?
          // atomic_store(&wayland_thread_ctx.ctx_shm->configured, true);
          if (!atomic_load(&wayland_thread_ctx.ctx_shm->configured)) {
            BONGOCAT_LOG_WARNING("xdg_output.name: assuming configured, yet");
          }
        }
        // Wait for configure event to be processed
        wl_display_roundtrip(wayland_thread_ctx.display);
        if (oref->wayland->animation_context != BONGOCAT_NULLPTR) {
          request_render(*oref->wayland->animation_context);
        }
        BONGOCAT_LOG_DEBUG("xdg_output.name: Surface recreated, configure event processed");
      } else {
        BONGOCAT_LOG_ERROR("xdg_output.name: Failed to recreate surface on reconnected output");
      }
    }
  }
}

void handle_xdg_output_logical_position(void *data, [[maybe_unused]] zxdg_output_v1 *xdg_output, int32_t x, int32_t y) {
  if (data == BONGOCAT_NULLPTR) {
    BONGOCAT_LOG_VERBOSE("Handler called with null data (ignored)");
    return;
  }
  auto *oref = static_cast<output_ref_t *>(data);

  oref->x = x;
  oref->y = y;
  oref->received = flag_add<output_ref_received_flags_t>(oref->received, output_ref_received_flags_t::LogicalPosition);

  BONGOCAT_LOG_VERBOSE("xdg_output.logical_position: %d,%d received", x, y);
}
void handle_xdg_output_logical_size(void *data, [[maybe_unused]] zxdg_output_v1 *xdg_output, int32_t width,
                                    int32_t height) {
  if (data == BONGOCAT_NULLPTR) {
    BONGOCAT_LOG_VERBOSE("Handler called with null data (ignored)");
    return;
  }
  auto *oref = static_cast<output_ref_t *>(data);

  oref->width = width;
  oref->height = height;
  oref->received = flag_add<output_ref_received_flags_t>(oref->received, output_ref_received_flags_t::LogicalSize);

  // propagate into screen_info_t
  if (oref->wayland != BONGOCAT_NULLPTR) {
    wayland_context_t& wayland_ctx = *oref->wayland;
    // wayland_thread_context& wayland_thread_ctx = oref->wayland->thread_context;

    for (size_t i = 0; i < MAX_OUTPUTS; ++i) {
      if (wayland_ctx.screen_infos[i].wl_output == oref->wl_output) {
        wayland_ctx.screen_infos[i].logical_width = width;
        wayland_ctx.screen_infos[i].logical_height = height;
        break;
      }
    }
  }

  BONGOCAT_LOG_VERBOSE("xdg_output.logical_size: %dx%d received", width, height);
}
void handle_xdg_output_done(void *data, [[maybe_unused]] zxdg_output_v1 *xdg_output) {
  if (data == BONGOCAT_NULLPTR) {
    BONGOCAT_LOG_VERBOSE("Handler called with null data (ignored)");
    return;
  }
  auto *oref = static_cast<output_ref_t *>(data);

  // propagate into screen_info_t
  if (oref->wayland != BONGOCAT_NULLPTR) {
    wayland_context_t& wayland_ctx = *oref->wayland;
    // wayland_thread_context& wayland_thread_ctx = oref->wayland->thread_context;

    for (size_t i = 0; i < MAX_OUTPUTS; ++i) {
      if (wayland_ctx.screen_infos[i].wl_output == oref->wl_output) {
        wayland_ctx.screen_infos[i].logical_width = oref->width;
        wayland_ctx.screen_infos[i].logical_height = oref->height;
        break;
      }
    }
  }
  BONGOCAT_LOG_VERBOSE("xdg_output.done: done received");
}

void handle_xdg_output_description(void *data, [[maybe_unused]] zxdg_output_v1 *xdg_output,
                                   [[maybe_unused]] const char *description) {
  if (data == BONGOCAT_NULLPTR) {
    BONGOCAT_LOG_VERBOSE("Handler called with null data (ignored)");
    return;
  }
  // auto *oref = static_cast<output_ref_t *>(data);

  BONGOCAT_LOG_VERBOSE("xdg_output.description: description received");
}

// =============================================================================
// FULLSCREEN DETECTION IMPLEMENTATION
// =============================================================================

struct update_fullscreen_state_toplevel_state_t {
  bool is_fullscreen{false};
  bool is_activated{false};
};
static bool fs_update_state(wayland_context_t& ctx, update_fullscreen_state_toplevel_state_t new_state) {
  if (!atomic_load(&ctx.ready)) {
    BONGOCAT_LOG_VERBOSE("Wayland configured yet, skipping update");
    return false;
  }
  if (ctx.animation_context == BONGOCAT_NULLPTR) {
    BONGOCAT_LOG_VERBOSE("Wayland not configured yet");
    return false;
  }

  // const wayland_shared_memory_t& wayland_ctx_shm = *ctx.wayland_context.ctx_shm;

  if (new_state.is_fullscreen != ctx.fs_detector.has_fullscreen_toplevel) {
    ctx.fs_detector.has_fullscreen_toplevel = new_state.is_fullscreen;
    ctx.thread_context._fullscreen_detected = new_state.is_fullscreen;

    BONGOCAT_LOG_DEBUG("Fullscreen state changed: %s",
                       ctx.thread_context._fullscreen_detected ? "detected" : "cleared");

    if (ctx.thread_context.ctx_shm && atomic_load(&ctx.thread_context.ctx_shm->configured)) {
      request_render(*ctx.animation_context);
    } else {
      BONGOCAT_LOG_VERBOSE("Wayland not configured yet, skipping request rendering");
    }

    return true;
  }

  return false;
}

namespace hyprland {
  static int fs_update_state(wayland_context_t& ctx) {
    if (wayland::hyprland::window_info_t win; wayland::hyprland::get_active_window(ctx, win)) {
      bool find_output = false;
      wl_output *found_wl_output = BONGOCAT_NULLPTR;
      for (size_t i = 0; i < ctx.output_count; i++) {
        if (ctx.outputs[i].hypr_id == win.monitor_id) {
          if (ctx.thread_context.output == ctx.outputs[i].wl_output) {
            found_wl_output = ctx.outputs[i].wl_output;
            find_output = true;
            break;
          }
        }
      }
      if (find_output && ctx.thread_context.output == found_wl_output) {
        details::fs_update_state(ctx, {.is_fullscreen = win.fullscreen, .is_activated = true});
        return win.fullscreen ? 2 : 1;
      }

      return 0;
    }

    return -1;
  }
}  // namespace hyprland

static bool fs_check_compositor_fallback(wayland_context_t& ctx) {
  // BONGOCAT_LOG_VERBOSE("Using compositor-specific fullscreen detection");

  // Try Hyprland first
  if (const int result = wayland::hyprland::fs_check_compositor_fallback(ctx); result >= 0) {
    return result == 1;
  }

  // Try Sway as fallback
  if (const int result = wayland::sway::fs_check_compositor_fallback(ctx); result >= 0) {
    return result == 1;
  }

  BONGOCAT_LOG_DEBUG("No supported compositor found for fullscreen detection");
  return false;
}

static bool fs_check_status(wayland_context_t& ctx) {
  if (!atomic_load(&ctx.ready)) {
    BONGOCAT_LOG_VERBOSE("Wayland configured yet, skipping handling");
    return false;
  }

  if (ctx.fs_detector.manager != BONGOCAT_NULLPTR) {
    return ctx.fs_detector.has_fullscreen_toplevel;
  }

  return fs_check_compositor_fallback(ctx);
}

void fs_update_state_fallback(wayland_context_t& ctx) {
  for (size_t i = 0; i < ctx.num_toplevels; ++i) {
    const tracked_toplevel_t& tracked = ctx.tracked_toplevels[i];
    // Skip handles that are not mapped or destroyed
    if (tracked.handle == BONGOCAT_NULLPTR) {
      continue;
    }
    if (tracked.is_fullscreen) {
      // Only update overlay if on our output
      if (tracked.output == ctx.thread_context.output) {
        fs_update_state(ctx, {.is_fullscreen = true, .is_activated = true});
        return;
      }
    }
  }

  const bool new_fullscreen = fs_check_status(ctx);
  if (new_fullscreen != ctx.thread_context._fullscreen_detected) {
    fs_update_state(ctx, {.is_fullscreen = new_fullscreen, .is_activated = true});
  }
}

struct update_fullscreen_state_toplevel_result_t {
  bool output_found{false};
  bool changed{false};
};
static update_fullscreen_state_toplevel_result_t
update_fullscreen_state_toplevel(wayland_context_t& ctx, tracked_toplevel_t& tracked,
                                 update_fullscreen_state_toplevel_state_t state) {
  bool state_changed = tracked.is_fullscreen != state.is_fullscreen || tracked.is_activated != state.is_activated;
  tracked.is_fullscreen = state.is_fullscreen;
  tracked.is_activated = state.is_activated;

  /// @NOTE: tracked.output can always be NULL when no output.enter/output.leave event were triggered
  // Only trigger overlay update if this fullscreen window is on our output
  if (tracked.output == ctx.thread_context.output && state_changed) {
    state_changed = fs_update_state(ctx, state);
    BONGOCAT_LOG_VERBOSE("Fullscreen state updated for window %p: (fullscreen=%d;activated=%d)",
                         static_cast<void *>(tracked.handle), state.is_fullscreen, state.is_activated);
    return {.output_found = true, .changed = state_changed};
  }

  return {.output_found = false, .changed = state_changed};
}

// Foreign toplevel protocol event handlers
void fs_handle_toplevel_state(void *data, [[maybe_unused]] zwlr_foreign_toplevel_handle_v1 *handle, wl_array *state) {
  if (data == BONGOCAT_NULLPTR) {
    BONGOCAT_LOG_VERBOSE("Handler called with null data (ignored)");
    return;
  }
  wayland_context_t& ctx = *static_cast<wayland_context_t *>(data);
  if (!atomic_load(&ctx.ready)) {
    BONGOCAT_LOG_VERBOSE("Wayland configured yet, skipping handling");
    return;
  }
  // only check for state changes when everything is ready, no need to do something before like fullscreen check

  // check if fullscreen state event change
  bool is_fullscreen = false;
  bool is_activated = false;
  wl_array_for_each_typed(state_ptr, state, uint32_t) {
    if (*state_ptr == ZWLR_FOREIGN_TOPLEVEL_HANDLE_V1_STATE_FULLSCREEN) {
      is_fullscreen = true;
    }
    if (*state_ptr == ZWLR_FOREIGN_TOPLEVEL_HANDLE_V1_STATE_ACTIVATED) {
      is_activated = true;
    }
  }

  /// @NOTE: tracked.output can always be NULL when no output.enter/output.leave event were triggered
  bool output_found = false;
  bool handle_tracked = false;
  bool handle_has_output = false;
  for (size_t i = 0; i < ctx.num_toplevels; ++i) {
    if (ctx.tracked_toplevels[i].handle == handle) {
      handle_tracked = true;
      handle_has_output |= ctx.tracked_toplevels[i].output == BONGOCAT_NULLPTR;
      auto [output_found_result, changed] = update_fullscreen_state_toplevel(
          ctx, ctx.tracked_toplevels[i], {.is_fullscreen = is_fullscreen, .is_activated = is_activated});
      output_found |= output_found_result;

      if (output_found_result) {
        if (changed) {
          BONGOCAT_LOG_VERBOSE("fs_handle_toplevel.state: Update fullscreen state: (fullscreen=%d;activated=%d)",
                               is_fullscreen, is_activated);
        }
      }
    }
  }

  // This toplevel is known to belong to a different output. Do not use
  // compositor-global fallbacks, otherwise fullscreen on monitor A can hide
  // overlay on monitor B.
  if (handle_tracked && handle_has_output && !output_found) {
    return;
  }

  // fallback: check for hyprland active fullscreen windows
  if (!output_found) {
    if (const int result = hyprland::fs_update_state(ctx); result >= 0) {
      output_found = true;
      BONGOCAT_LOG_VERBOSE("fs_handle_toplevel.state: Update fullscreen state: %d (hyprland)", result);
    }
  }

  // fallback: global fullscreen
  // Safe when single-output, or when the compositor never sends output_enter
  // events (e.g. KDE/KWin). In the latter case, per-output tracking is
  // impossible, so we use the global activated+fullscreen state as a best
  // effort. On multi-monitor setups without output events, fullscreen on
  // any monitor will hide the overlay on all monitors - acceptable trade-off
  // vs never hiding at all.
  if (!output_found && (ctx.output_count <= 1 || !atomic_load(&ctx._compositor_sends_output_events))) {
    // Case 1: Window becomes active - update state based on its fullscreen
    // status
    if (is_activated) {
      atomic_store(&ctx._active_toplevel_fullscreen, is_fullscreen);

      const bool changed = fs_update_state(ctx, {.is_fullscreen = is_fullscreen, .is_activated = is_activated});
      if (changed) {
        BONGOCAT_LOG_VERBOSE("fs_handle_toplevel.state: Update fullscreen state: (fullscreen=%d;activated=%d)",
                             is_fullscreen, is_activated);
      }
    }
    // Case 2: Previously active fullscreen window loses activation
    // (e.g., switching to empty workspace) - show bongocat
    else if (!is_activated) {
      atomic_store(&ctx._active_toplevel_fullscreen, false);

      const bool changed = fs_update_state(ctx, {.is_fullscreen = false, .is_activated = is_activated});
      if (changed) {
        BONGOCAT_LOG_VERBOSE("fs_handle_toplevel.state: Update fullscreen state: (fullscreen=%d;activated=%d)",
                             is_fullscreen, is_activated);
      }
    }
  }
}

void fs_handle_toplevel_closed(void *data, zwlr_foreign_toplevel_handle_v1 *handle) {
  if (data == BONGOCAT_NULLPTR) {
    BONGOCAT_LOG_VERBOSE("Handler called with null data (ignored)");
    return;
  }
  wayland_context_t& ctx = *static_cast<wayland_context_t *>(data);
  if (!atomic_load(&ctx.ready)) {
    BONGOCAT_LOG_VERBOSE("Wayland configured yet, skipping handling");
    return;
  }

  bool closed_on_current_output = false;
  bool closed_was_fullscreen = false;
  for (size_t i = 0; i < ctx.num_toplevels; ++i) {
    if (ctx.tracked_toplevels[i].handle == handle) {
      closed_on_current_output = ctx.tracked_toplevels[i].output == ctx.thread_context.output;
      closed_was_fullscreen = ctx.tracked_toplevels[i].is_fullscreen;
      break;
    }
  }

  if (closed_on_current_output && closed_was_fullscreen) {
    ctx._active_toplevel_fullscreen = false;
    fs_update_state(ctx, {.is_fullscreen = false, .is_activated = true});
  }

  // remove from tracked_toplevels if present
  for (size_t i = 0; i < ctx.num_toplevels; ++i) {
    if (ctx.tracked_toplevels[i].handle == handle) {
      if (ctx.tracked_toplevels[i].handle != BONGOCAT_NULLPTR) {
        zwlr_foreign_toplevel_handle_v1_destroy(ctx.tracked_toplevels[i].handle);
        ctx.tracked_toplevels[i].handle = BONGOCAT_NULLPTR;
      }
      // compact array to keep contiguous
      for (size_t j = i; j + 1 < ctx.num_toplevels; ++j) {
        ctx.tracked_toplevels[j] = ctx.tracked_toplevels[j + 1];
      }
      ctx.tracked_toplevels[ctx.num_toplevels - 1] = {};
      ctx.num_toplevels--;
      break;
    }
  }

  BONGOCAT_LOG_DEBUG("fs_handle_toplevel.closed: Close toplevel handle");
}

// Minimal event handlers for unused events
void fs_handle_title(void *data, [[maybe_unused]] zwlr_foreign_toplevel_handle_v1 *handle,
                     [[maybe_unused]] const char *title) {
  if (data == BONGOCAT_NULLPTR) {
    BONGOCAT_LOG_VERBOSE("Handler called with null data (ignored)");
    return;
  }
  // wayland_session_t& ctx = *static_cast<wayland_session_t *>(data);

  BONGOCAT_LOG_VERBOSE("fs_toplevel_listener.title: title received");
}

void fs_handle_app_id(void *data, [[maybe_unused]] zwlr_foreign_toplevel_handle_v1 *handle,
                      [[maybe_unused]] const char *app_id) {
  if (data == BONGOCAT_NULLPTR) {
    BONGOCAT_LOG_VERBOSE("Handler called with null data (ignored)");
    return;
  }
  // wayland_session_t& ctx = *static_cast<wayland_session_t *>(data);

  BONGOCAT_LOG_VERBOSE("fs_toplevel_listener.app_id: app_id received");
}

void fs_handle_output_enter(void *data, [[maybe_unused]] zwlr_foreign_toplevel_handle_v1 *handle,
                            [[maybe_unused]] wl_output *output) {
  if (data == BONGOCAT_NULLPTR) {
    BONGOCAT_LOG_VERBOSE("Handler called with null data (ignored)");
    return;
  }
  wayland_context_t& ctx = *static_cast<wayland_context_t *>(data);

  atomic_store(&ctx._compositor_sends_output_events, true);

  for (size_t i = 0; i < ctx.num_toplevels; i++) {
    auto& tracked = ctx.tracked_toplevels[i];
    if (tracked.handle == handle) {
      BONGOCAT_LOG_VERBOSE("fs_toplevel_listener.output_enter: update tracked_toplevels[%i] output", i);
      tracked.output = output;
      if (tracked.is_fullscreen) {
        if (tracked.output == ctx.thread_context.output) {
          fs_update_state(ctx, {.is_fullscreen = true, .is_activated = true});
        }
      }
      break;
    }
  }

  BONGOCAT_LOG_VERBOSE("fs_toplevel_listener.output_enter: output received");
}

void fs_handle_output_leave(void *data, [[maybe_unused]] zwlr_foreign_toplevel_handle_v1 *handle,
                            [[maybe_unused]] wl_output *output) {
  if (data == BONGOCAT_NULLPTR) {
    BONGOCAT_LOG_VERBOSE("Handler called with null data (ignored)");
    return;
  }
  wayland_context_t& ctx = *static_cast<wayland_context_t *>(data);

  for (size_t i = 0; i < ctx.num_toplevels; i++) {
    auto& tracked = ctx.tracked_toplevels[i];
    if (tracked.handle == handle && tracked.output == output) {
      BONGOCAT_LOG_VERBOSE("fs_toplevel_listener.output_leave: update tracked_toplevels[%i] output", i);
      if (tracked.is_fullscreen && tracked.output == ctx.thread_context.output) {
        fs_update_state(ctx, {.is_fullscreen = false, .is_activated = false});
      }
      tracked.output = BONGOCAT_NULLPTR;
      break;
    }
  }

  BONGOCAT_LOG_VERBOSE("fs_toplevel_listener.output_leave: output received");
}

void fs_handle_done(void *data, [[maybe_unused]] zwlr_foreign_toplevel_handle_v1 *handle) {
  if (data == BONGOCAT_NULLPTR) {
    BONGOCAT_LOG_VERBOSE("Handler called with null data (ignored)");
    return;
  }
  // wayland_session_t& ctx = *static_cast<wayland_session_t *>(data);

  BONGOCAT_LOG_VERBOSE("fs_toplevel_listener.done: done received");
}

void fs_handle_parent(void *data, [[maybe_unused]] zwlr_foreign_toplevel_handle_v1 *handle,
                      [[maybe_unused]] zwlr_foreign_toplevel_handle_v1 *parent) {
  if (data == BONGOCAT_NULLPTR) {
    BONGOCAT_LOG_VERBOSE("Handler called with null data (ignored)");
    return;
  }
  // wayland_session_t& ctx = *static_cast<wayland_session_t *>(data);

  BONGOCAT_LOG_VERBOSE("fs_toplevel_listener.parent: parent received");
}

void fs_handle_manager_toplevel(void *data, [[maybe_unused]] zwlr_foreign_toplevel_manager_v1 *manager,
                                zwlr_foreign_toplevel_handle_v1 *toplevel) {
  if (data == BONGOCAT_NULLPTR) {
    BONGOCAT_LOG_WARNING("Handler called with null data (ignored)");
    return;
  }
  wayland_context_t& ctx = *static_cast<wayland_context_t *>(data);

  BONGOCAT_LOG_VERBOSE("fs_toplevel_manager_listener.toplevel: toplevel received");

  zwlr_foreign_toplevel_handle_v1_add_listener(toplevel, &fs_toplevel_listener, &ctx);
  if (ctx.num_toplevels < MAX_TOP_LEVELS) {
    bool already_tracked = false;
    for (size_t i = 0; i < ctx.num_toplevels; i++) {
      if (ctx.tracked_toplevels[i].handle == toplevel) {
        already_tracked = true;
        break;
      }
    }
    if (!already_tracked) {
      ctx.tracked_toplevels[ctx.num_toplevels].handle = toplevel;
      ctx.num_toplevels++;
    }
  } else {
    BONGOCAT_LOG_ERROR("fs_toplevel_manager_listener.toplevel: toplevel tracker is full, %zu max: %d",
                       ctx.num_toplevels, MAX_TOP_LEVELS);
  }

  BONGOCAT_LOG_DEBUG("fs_toplevel_manager_listener.toplevel: New toplevel registered for fullscreen monitoring: %zu",
                     ctx.num_toplevels);
}

void fs_handle_manager_finished(void *data, zwlr_foreign_toplevel_manager_v1 *manager) {
  if (data == BONGOCAT_NULLPTR) {
    BONGOCAT_LOG_VERBOSE("Handler called with null data (ignored)");
    return;
  }
  wayland_context_t& ctx = *static_cast<wayland_context_t *>(data);
  if (!atomic_load(&ctx.ready)) {
    BONGOCAT_LOG_VERBOSE("Wayland configured yet, skipping handling");
    return;
  }

  BONGOCAT_LOG_DEBUG("fs_toplevel_manager_listener.finished: Foreign toplevel manager finished");
  if (manager != BONGOCAT_NULLPTR) {
    zwlr_foreign_toplevel_manager_v1_destroy(manager);
    manager = BONGOCAT_NULLPTR;
  }
  ctx.fs_detector.manager = BONGOCAT_NULLPTR;
}

// =============================================================================
// SCREEN DIMENSION MANAGEMENT
// =============================================================================

/*
static void screen_calculate_dimensions(screen_info_t& screen_info) {
  if (screen_info.received == screen_info_received_flags_t::None ||
      (static_cast<uint32_t>(screen_info.received) & static_cast<uint32_t>(screen_info_received_flags_t::Geometry)) ==
          0 ||
      (static_cast<uint32_t>(screen_info.received) & static_cast<uint32_t>(screen_info_received_flags_t::Mode)) == 0) {
    return;
  }

  const bool is_rotated = screen_info.transform == WL_OUTPUT_TRANSFORM_90 ||
                          screen_info.transform == WL_OUTPUT_TRANSFORM_270 ||
                          screen_info.transform == WL_OUTPUT_TRANSFORM_FLIPPED_90 ||
                          screen_info.transform == WL_OUTPUT_TRANSFORM_FLIPPED_270;

  if (is_rotated) {
    screen_info.screen_width = screen_info.raw_height;
    screen_info.screen_height = screen_info.raw_width;
    BONGOCAT_LOG_DEBUG("Detected rotated screen: %dx%d (transform: %d)", screen_info.raw_height, screen_info.raw_width,
                       screen_info.transform);
  } else {
    screen_info.screen_width = screen_info.raw_width;
    screen_info.screen_height = screen_info.raw_height;
    BONGOCAT_LOG_DEBUG("Detected screen: %dx%d (transform: %d)", screen_info.raw_width, screen_info.raw_height,
                       screen_info.transform);
  }
}
*/

// =============================================================================
// WAYLAND EVENT HANDLERS
// =============================================================================

void layer_surface_configure(void *data, zwlr_layer_surface_v1 *ls, uint32_t serial, [[maybe_unused]] uint32_t w,
                             [[maybe_unused]] uint32_t h) {
  if (data == BONGOCAT_NULLPTR) {
    BONGOCAT_LOG_VERBOSE("Handler called with null data (ignored)");
    return;
  }
  wayland_context_t& ctx = *static_cast<wayland_context_t *>(data);

  assert(ctx.animation_context != BONGOCAT_NULLPTR);
  assert(ctx.thread_context.ctx_shm);
  wayland_shared_memory_t& wayland_ctx_shm = *ctx.thread_context.ctx_shm;

  zwlr_layer_surface_v1_ack_configure(ls, serial);
  atomic_store(&wayland_ctx_shm.configured, true);
  if (atomic_load(&ctx.ready)) {
    // trigger initial rendering
    request_render(*ctx.animation_context);
  }

  BONGOCAT_LOG_DEBUG("layer_surface.configure: Layer surface configured: %dx%d", w, h);
}
void layer_surface_closed(void *data, [[maybe_unused]] zwlr_layer_surface_v1 *ls) {
  if (data == BONGOCAT_NULLPTR) {
    BONGOCAT_LOG_VERBOSE("Handler called with null data (ignored)");
    return;
  }
  const wayland_context_t& ctx = *static_cast<wayland_context_t *>(data);
  if (!atomic_load(&ctx.ready)) {
    BONGOCAT_LOG_VERBOSE("Wayland configured yet, skipping handling");
    return;
  }

  BONGOCAT_LOG_VERBOSE("layer_surface.closed: Layer surface closed");
}

void xdg_wm_base_ping(void *data, xdg_wm_base *wm_base, uint32_t serial) {
  assert(data);
  [[maybe_unused]] const wayland_context_t& ctx = *static_cast<wayland_context_t *>(data);

  BONGOCAT_LOG_VERBOSE("xdg_wm_base.ping: base pong %x", serial);
  xdg_wm_base_pong(wm_base, serial);
}

void output_geometry(void *data, [[maybe_unused]] wl_output *wl_output, [[maybe_unused]] int32_t x,
                     [[maybe_unused]] int32_t y, [[maybe_unused]] int32_t physical_width,
                     [[maybe_unused]] int32_t physical_height, [[maybe_unused]] int32_t subpixel,
                     [[maybe_unused]] const char *make, [[maybe_unused]] const char *model, int32_t transform) {
  if (data == BONGOCAT_NULLPTR) {
    BONGOCAT_LOG_VERBOSE("Handler called with null data (ignored)");
    return;
  }
  wayland_context_t& ctx = *static_cast<wayland_context_t *>(data);

  for (size_t i = 0; i < MAX_OUTPUTS; i++) {
    if (ctx.screen_infos[i].wl_output == wl_output) {
      ctx.screen_infos[i].transform = transform;

      ctx.screen_infos[i].received =
          static_cast<screen_info_received_flags_t>(static_cast<uint32_t>(ctx.screen_infos[i].received) |
                                                    static_cast<uint32_t>(screen_info_received_flags_t::Geometry));
      // screen_calculate_dimensions(ctx.screen_infos[i]);
    }
  }
  BONGOCAT_LOG_DEBUG("wl_output.geometry: Output transform: %d", transform);
}

void output_mode(void *data, [[maybe_unused]] wl_output *wl_output, uint32_t flags, int32_t width, int32_t height,
                 [[maybe_unused]] int32_t refresh) {
  if (data == BONGOCAT_NULLPTR) {
    BONGOCAT_LOG_VERBOSE("Handler called with null data (ignored)");
    return;
  }
  wayland_context_t& ctx = *static_cast<wayland_context_t *>(data);

  BONGOCAT_LOG_VERBOSE("wl_output.mode: mode received: %u", flags);

  if (flags & WL_OUTPUT_MODE_CURRENT) {
    for (size_t i = 0; i < MAX_OUTPUTS; i++) {
      if (ctx.screen_infos[i].wl_output == wl_output) {
        ctx.screen_infos[i].physical_width = width;
        ctx.screen_infos[i].physical_height = height;

        ctx.screen_infos[i].received =
            static_cast<screen_info_received_flags_t>(static_cast<uint32_t>(ctx.screen_infos[i].received) |
                                                      static_cast<uint32_t>(screen_info_received_flags_t::Mode));
        BONGOCAT_LOG_DEBUG("wl_output.mode: Received raw screen mode: %dx%d", width, height);
        // screen_calculate_dimensions(ctx.screen_infos[i]);
      }
    }
  }
}

void output_done(void *data, [[maybe_unused]] wl_output *wl_output) {
  if (data == BONGOCAT_NULLPTR) {
    BONGOCAT_LOG_VERBOSE("Handler called with null data (ignored)");
    return;
  }
  // wayland_context_t& ctx = *static_cast<wayland_context_t *>(data);

  BONGOCAT_LOG_DEBUG("wl_output.done: Output configuration complete");
}

void output_scale(void *data, [[maybe_unused]] wl_output *wl_output, [[maybe_unused]] int32_t factor) {
  if (data == BONGOCAT_NULLPTR) {
    BONGOCAT_LOG_VERBOSE("Handler called with null data (ignored)");
    return;
  }
  wayland_context_t& ctx = *static_cast<wayland_context_t *>(data);

  if (factor < 1) {
    factor = 1;
  }

  for (size_t i = 0; i < ctx.output_count; ++i) {
    if (ctx.outputs[i].wl_output == wl_output) {
      ctx.outputs[i].wl_scale = factor;
      break;
    }
  }

  for (size_t i = 0; i < MAX_OUTPUTS; i++) {
    if (ctx.screen_infos[i].wl_output == wl_output) {
      ctx.screen_infos[i].scale = factor;

      ctx.screen_infos[i].received =
          static_cast<screen_info_received_flags_t>(static_cast<uint32_t>(ctx.screen_infos[i].received) |
                                                    static_cast<uint32_t>(screen_info_received_flags_t::Scale));
    }
  }

  BONGOCAT_LOG_VERBOSE("wl_output.scale: factor received (%d)", factor);
}

void output_name(void *data, [[maybe_unused]] wl_output *wl_output, [[maybe_unused]] const char *name) {
  if (data == BONGOCAT_NULLPTR) {
    BONGOCAT_LOG_VERBOSE("Handler called with null data (ignored)");
    return;
  }
  // wayland_session_t& ctx = *static_cast<wayland_session_t *>(data);

  BONGOCAT_LOG_VERBOSE("wl_output.name: name received");
}

void output_description(void *data, [[maybe_unused]] wl_output *wl_output, [[maybe_unused]] const char *name) {
  if (data == BONGOCAT_NULLPTR) {
    BONGOCAT_LOG_VERBOSE("Handler called with null data (ignored)");
    return;
  }
  // wayland_session_t& ctx = *static_cast<wayland_session_t *>(data);

  BONGOCAT_LOG_VERBOSE("wl_output.description: description received");
}

void buffer_release(void *data, wl_buffer *buffer) {
  if (data == BONGOCAT_NULLPTR) {
    BONGOCAT_LOG_VERBOSE("Handler called with null data (ignored)");
    return;
  }
  wayland_shm_buffer_t& wayland_shm_buffer = *static_cast<wayland_shm_buffer_t *>(data);

  if (wayland_shm_buffer.buffer == buffer) {
    atomic_store(&wayland_shm_buffer.busy, false);
    BONGOCAT_LOG_VERBOSE("wl_buffer.release: buffer %d released", wayland_shm_buffer.index);

    /*
    if (atomic_exchange(&wayland_shm_buffer._wayland_context->_redraw_after_frame, false)) {
        // @TODO: render immediately (optional)
    }
    */
  } else {
    BONGOCAT_LOG_VERBOSE("wl_buffer.release: buffer is not matching with data.buffer");
  }
}

void frame_done(void *data, wl_callback *cb, [[maybe_unused]] uint32_t time) {
  if (data == BONGOCAT_NULLPTR) {
    BONGOCAT_LOG_WARNING("Handler called with null data (ignored)");
    return;
  }
  auto& ctx = *static_cast<platform::wayland::wayland_context_t *>(data);

  if (!atomic_load(&ctx.ready)) {
    BONGOCAT_LOG_WARNING("Wayland configured yet, skipping handling");
    return;
  }
  if (!ctx.animation_context) {
    BONGOCAT_LOG_WARNING("Wayland configured yet, skipping handling");
    return;
  }

  platform::wayland::wayland_thread_context& wayland_ctx = ctx.thread_context;
  // animation_context_t& anim = *ctx->animation_context;
  // animation::animation_session_t& trigger_ctx = *ctx.animation_trigger_context;
  // wayland_shared_memory_t& wayland_ctx_shm = wayland_ctx->ctx_shm;
  //  read-only
  assert(wayland_ctx._local_copy_config);
  // const config::config_t& current_config = *wayland_ctx._local_copy_config;
  // const animation_shared_memory_t *const anim_shm = anim->shm;
  // assert(anim_shm);

  // Clear frame callback under lock
  {
    platform::LockGuard guard(wayland_ctx._frame_cb_lock);
    if (wayland_ctx._frame_cb == cb) {
      wl_callback_destroy(wayland_ctx._frame_cb);
      wayland_ctx._frame_cb = BONGOCAT_NULLPTR;
      atomic_store(&wayland_ctx._frame_pending, false);
      BONGOCAT_LOG_VERBOSE("wl_callback.done: frame done");
    } else {
      BONGOCAT_LOG_VERBOSE("wl_callback.done: cb is not matching");
    }
  }

  // Fallback for missed buffer.release
  platform::wayland::wayland_shared_memory_t *shm_ctx = wayland_ctx.ctx_shm.ptr;
  assert(shm_ctx);
  /// @TODO: a second buffer may have been submitted after the one whose frame callback just fired. That buffer may
  /// still be actively read by the compositor. track the submitted buffer pointer explicitly and only clear that one.
  if constexpr (platform::wayland::WAYLAND_NUM_BUFFERS == 1) {
    for (size_t i = 0; i < platform::wayland::WAYLAND_NUM_BUFFERS; i++) {
      auto& buf = shm_ctx->buffers[i];
      if (atomic_load(&buf.busy)) {
        atomic_store(&buf.busy, false);
        BONGOCAT_LOG_WARNING("wl_callback.done: fallback released stuck buffer %zu (missed wl_buffer.release)", i);
      }
    }
  }

  if (atomic_exchange(&wayland_ctx._redraw_after_frame, false)) {
    // render immediately
    BONGOCAT_LOG_VERBOSE("wl_callback.done: redraw");
    animation::draw_bar(ctx);
  }
}

// Helper to handle output reconnection
void wayland_handle_output_reconnect(output_ref_t *oref, struct wl_output *new_output, uint32_t registry_name,
                                     [[maybe_unused]] const char *output_name) {
  assert(oref->wayland);

  wayland_thread_context& wayland_ctx = oref->wayland->thread_context;
  // animation_context_t& anim = *ctx.animation_context;
  // animation_trigger_context_t& trigger_ctx = *ctx.animation_trigger_context;

  // read-only config
  // assert(wayland_ctx._local_copy_config != nullptr);
  // const config::config_t& current_config = *wayland_ctx._local_copy_config;

  BONGOCAT_LOG_DEBUG("wayland_handle_output_reconnect: Output '%s' reconnected (registry name %u)", output_name,
                     registry_name);

  // Clean up old surface if it exists
  cleanup_wayland_context_surface(wayland_ctx);

  // Set new output
  wayland_ctx.output = new_output;
  wayland_ctx.bound_output_name = registry_name;
  atomic_store(&oref->wayland->_output_lost, false);

  // Recreate surface on new output
  if (wayland_setup_surface(*oref->wayland) == bongocat_error_t::BONGOCAT_SUCCESS) {
    assert(wayland_ctx.ctx_shm.ptr && wayland_ctx.ctx_shm.ptr != MAP_FAILED);
    if (wayland_ctx.ctx_shm) {
      /// @TODO: pre-matured configured ?
      // atomic_store(&wayland_ctx.ctx_shm->configured, true);
      if (!atomic_load(&wayland_ctx.ctx_shm->configured)) {
        BONGOCAT_LOG_WARNING("wayland_handle_output_reconnect: assuming configured, yet");
      }
    }
    BONGOCAT_LOG_DEBUG("wayland_handle_output_reconnect: Surface recreated on reconnected output");
    wl_display_roundtrip(wayland_ctx.display);
    if (oref->wayland->animation_context != BONGOCAT_NULLPTR) {
      request_render(*oref->wayland->animation_context);
    }
  } else {
    BONGOCAT_LOG_ERROR("wayland_handle_output_reconnect: Failed to recreate surface on reconnected output");
  }
}

// =============================================================================
// HIDPI: FRACTIONAL SCALE HANDLING
// =============================================================================

void fractional_scale_preferred_scale([[maybe_unused]] void *data, [[maybe_unused]] struct wp_fractional_scale_v1 *fs,
                                      uint32_t scale) {
  if (data == BONGOCAT_NULLPTR) {
    BONGOCAT_LOG_WARNING("Handler called with null data (ignored)");
    return;
  }

  wayland_context_t& ctx = *static_cast<wayland_context_t *>(data);
  wayland_thread_context& wayland_ctx = ctx.thread_context;

  BONGOCAT_LOG_DEBUG("fractional_scale_preferred_scale: Compositor requested fractional scale %u/120 (%.3f)", scale,
                     static_cast<double>(scale) / 120.0);

  if (scale == 0 || scale == wayland_ctx._preferred_scale) {
    BONGOCAT_LOG_VERBOSE("fractional_scale_preferred_scale: No change in scale");
    return;
  }

  wayland_ctx._preferred_scale = scale;
  BONGOCAT_LOG_VERBOSE("fractional_scale_preferred_scale: update _current_scale_120: %d", wayland_ctx._preferred_scale);
  if (wayland_ctx.surface != BONGOCAT_NULLPTR && wayland_ctx.ctx_shm != BONGOCAT_NULLPTR &&
      atomic_load(&wayland_ctx.ctx_shm->configured)) {
    if (details::wayland_update_screen_info(ctx, {
                                                     .skip_display_events = true,
                                                 }) != bongocat_error_t::BONGOCAT_SUCCESS) {
      BONGOCAT_LOG_ERROR("fractional_scale_preferred_scale: Failed to update width for recreate buffer");
    }
    BONGOCAT_LOG_VERBOSE("fractional_scale_preferred_scale: recreate buffer...");
    details::wayland_recreate_buffer(ctx);
  }
  if (ctx.animation_context != BONGOCAT_NULLPTR && ctx.animation_context->thread_context.shm != BONGOCAT_NULLPTR) {
    platform::LockGuard anim_guard(ctx.animation_context->thread_context.anim_lock);
    assert(scale <= INT_MAX);
    ctx.animation_context->thread_context.shm->scale120 = static_cast<int>(scale);
    ctx.animation_context->thread_context.shm->cat_height_phys =
        phys_dim(ctx, ctx.animation_context->thread_context._local_copy_config->cat_height);
    trigger_reload_animation(*ctx.animation_context);
    // request_render(*ctx.animation_context);
  } else {
    BONGOCAT_LOG_WARNING("fractional_scale_preferred_scale: animation_context is not setup, yet");
  }
}

// =============================================================================
// WAYLAND PROTOCOL REGISTRY
// =============================================================================

inline uint32_t bind_min_ver(uint32_t v, uint32_t desired) {
  return v < desired ? v : desired;
}
void registry_global(void *data, wl_registry *reg, uint32_t name, const char *iface, uint32_t ver) {
  if (data == BONGOCAT_NULLPTR) {
    BONGOCAT_LOG_VERBOSE("Handler called with null data (ignored)");
    return;
  }
  wayland_context_t& ctx = *static_cast<wayland_context_t *>(data);

  BONGOCAT_LOG_VERBOSE("wl_registry.global: registry received: %s; version: %u", iface, ver);

  constexpr uint32_t wl_compositor_interface_version = 4;
  constexpr uint32_t wl_shm_interface_version = 1;
  constexpr uint32_t zwlr_layer_shell_v1_interface_version = 4;
  constexpr uint32_t xdg_wm_base_interface_version = 1;
  constexpr uint32_t zxdg_output_manager_v1_interface_version = 3;
  constexpr uint32_t wl_output_interface_version = 2;
  constexpr uint32_t zwlr_foreign_toplevel_manager_v1_interface_version = 3;
  constexpr uint32_t wp_viewporter_interface_version = 1;
  constexpr uint32_t wp_fractional_scale_manager_v1_interface_version = 1;

  if (strcmp(iface, wl_compositor_interface.name) == 0) {
    ctx.thread_context.compositor = static_cast<wl_compositor *>(
        wl_registry_bind(reg, name, &wl_compositor_interface, bind_min_ver(ver, wl_compositor_interface_version)));
    BONGOCAT_LOG_VERBOSE("wl_registry.global: compositor registry bind");
  } else if (strcmp(iface, wl_shm_interface.name) == 0) {
    ctx.thread_context.shm = static_cast<wl_shm *>(
        wl_registry_bind(reg, name, &wl_shm_interface, bind_min_ver(ver, wl_shm_interface_version)));
    BONGOCAT_LOG_VERBOSE("wl_registry.global: shm registry bind");
  } else if (strcmp(iface, zwlr_layer_shell_v1_interface.name) == 0) {
    const uint32_t bind_version = bind_min_ver(ver, zwlr_layer_shell_v1_interface_version);
    ctx.thread_context.layer_shell =
        static_cast<zwlr_layer_shell_v1 *>(wl_registry_bind(reg, name, &zwlr_layer_shell_v1_interface, bind_version));
    ctx.thread_context.layer_shell_version = bind_version;
    BONGOCAT_LOG_VERBOSE("wl_registry.global: layer_shell registry bind");
    BONGOCAT_LOG_VERBOSE("wl_registry.global: layer_shell version (compositor): %u, bound: %u",
                         ctx.thread_context.layer_shell_version, bind_version);
  } else if (strcmp(iface, xdg_wm_base_interface.name) == 0) {
    ctx.thread_context.xdg_wm_base = static_cast<xdg_wm_base *>(
        wl_registry_bind(reg, name, &xdg_wm_base_interface, bind_min_ver(ver, xdg_wm_base_interface_version)));
    BONGOCAT_LOG_VERBOSE("wl_registry.global: xdg_wm_base registry bind");
    if (ctx.thread_context.xdg_wm_base != BONGOCAT_NULLPTR) {
      xdg_wm_base_add_listener(ctx.thread_context.xdg_wm_base, &xdg_wm_base_listener, &ctx);
    }
  } else if (strcmp(iface, zxdg_output_manager_v1_interface.name) == 0) {
    ctx.xdg_output_manager = static_cast<zxdg_output_manager_v1 *>(wl_registry_bind(
        reg, name, &zxdg_output_manager_v1_interface, bind_min_ver(ver, zxdg_output_manager_v1_interface_version)));
    BONGOCAT_LOG_VERBOSE("wl_registry.global: xdg_output_manager registry bind");
  } else if (strcmp(iface, wl_output_interface.name) == 0) {
    if (ctx.output_count < MAX_OUTPUTS) {
      ctx.outputs[ctx.output_count].name = name;
      ctx.outputs[ctx.output_count].wl_output = static_cast<wl_output *>(
          wl_registry_bind(reg, name, &wl_output_interface, bind_min_ver(ver, wl_output_interface_version)));
      wl_output_add_listener(ctx.outputs[ctx.output_count].wl_output, &output_listener, &ctx);
      BONGOCAT_LOG_VERBOSE("wl_registry.global: wl_output registry bind: %i", ctx.output_count);

      // If we lost our output, get xdg_output to check if this is the one
      // reconnecting
      if (atomic_load(&ctx._output_lost) && ctx.xdg_output_manager != BONGOCAT_NULLPTR) {
        ctx.outputs[ctx.output_count].xdg_output =
            zxdg_output_manager_v1_get_xdg_output(ctx.xdg_output_manager, ctx.outputs[ctx.output_count].wl_output);
        ctx.outputs[ctx.output_count].received = flag_remove<output_ref_received_flags_t>(
            ctx.outputs[ctx.output_count].received, output_ref_received_flags_t::Name);
        ctx.outputs[ctx.output_count].wayland = &ctx;
        zxdg_output_v1_add_listener(ctx.outputs[ctx.output_count].xdg_output, &xdg_output_listener,
                                    &ctx.outputs[ctx.output_count]);
        BONGOCAT_LOG_VERBOSE("wl_registry.global: New output appeared while output_lost, checking name...");
      }

      ctx.output_count++;
    }
  } else if (strcmp(iface, zwlr_foreign_toplevel_manager_v1_interface.name) == 0) {
    ctx.fs_detector.manager = static_cast<zwlr_foreign_toplevel_manager_v1 *>(
        wl_registry_bind(reg, name, &zwlr_foreign_toplevel_manager_v1_interface,
                         bind_min_ver(ver, zwlr_foreign_toplevel_manager_v1_interface_version)));
    BONGOCAT_LOG_VERBOSE("wl_registry.global: foreign_toplevel_manager (fs_detector.manager) registry bind");
    if (ctx.fs_detector.manager != BONGOCAT_NULLPTR) {
      zwlr_foreign_toplevel_manager_v1_add_listener(ctx.fs_detector.manager, &fs_manager_listener, &ctx);
      BONGOCAT_LOG_DEBUG(
          "wl_registry.global: Foreign toplevel manager bound - using Wayland protocol for fullscreen detection");
    }
  } else if (strcmp(iface, wp_viewporter_interface.name) == 0) {
    ctx.thread_context.viewporter = static_cast<wp_viewporter *>(
        wl_registry_bind(reg, name, &wp_viewporter_interface, bind_min_ver(ver, wp_viewporter_interface_version)));
    BONGOCAT_LOG_VERBOSE("wl_registry.global: viewporter registry bind");
  } else if (strcmp(iface, wp_fractional_scale_manager_v1_interface.name) == 0) {
    ctx.thread_context.fractional_scale_mgr = static_cast<wp_fractional_scale_manager_v1 *>(
        wl_registry_bind(reg, name, &wp_fractional_scale_manager_v1_interface,
                         bind_min_ver(ver, wp_fractional_scale_manager_v1_interface_version)));
    BONGOCAT_LOG_VERBOSE("wl_registry.global: fractional_scale_mgr registry bind");
  }
}

void registry_remove(void *data, [[maybe_unused]] wl_registry *registry, [[maybe_unused]] uint32_t name) {
  if (data == BONGOCAT_NULLPTR || registry == BONGOCAT_NULLPTR) {
    BONGOCAT_LOG_WARNING("Handler called with null data (ignored)");
    return;
  }
  wayland_context_t& ctx = *static_cast<wayland_context_t *>(data);
  platform::wayland::wayland_thread_context& wayland_ctx = ctx.thread_context;
  // animation_context_t& anim = ctx.animation_trigger_context->anim;
  // animation_trigger_context_t *trigger_ctx = ctx.animation_trigger_context;

  if (!wayland_ctx.ctx_shm) {
    BONGOCAT_LOG_WARNING("Handler called with null wayland_ctx.ctx_shm (ignored)");
    return;
  }
  assert(wayland_ctx.ctx_shm.ptr);
  platform::wayland::wayland_shared_memory_t& wayland_ctx_shm = *wayland_ctx.ctx_shm;

  BONGOCAT_LOG_VERBOSE("wl_registry.global_remove: registry received");

  size_t removed_index = ctx.output_count;
  for (size_t i = 0; i < ctx.output_count; ++i) {
    if (ctx.outputs[i].name == name) {
      removed_index = i;
      break;
    }
  }
  if (removed_index >= ctx.output_count) {
    return;
  }

  // Check if the removed global is our bound output
  const bool removed_bound = name == ctx.thread_context.bound_output_name && ctx.thread_context.bound_output_name != 0;
  if (removed_bound) {
    BONGOCAT_LOG_VERBOSE("wl_registry.global_remove: Bound output disconnected (registry name %u)", name);
    atomic_store(&ctx._output_lost, true);
    atomic_store(&wayland_ctx_shm.configured, false);

    // Clean up the old output reference
    wayland_ctx.output = BONGOCAT_NULLPTR;
    wayland_ctx.bound_output_name = 0;
    wayland_ctx._output_name_str = BONGOCAT_NULLPTR;
  }

  // Remove from outputs array
  for (size_t i = 0; i < ctx.output_count; ++i) {
    if (ctx.outputs[i].name == name) {
      if (ctx.outputs[i].xdg_output != BONGOCAT_NULLPTR) {
        zxdg_output_v1_destroy(ctx.outputs[i].xdg_output);
        ctx.outputs[i].xdg_output = BONGOCAT_NULLPTR;
      }
      if (ctx.outputs[i].wl_output != BONGOCAT_NULLPTR) {
        wl_output_destroy(ctx.outputs[i].wl_output);
        ctx.outputs[i].wl_output = BONGOCAT_NULLPTR;
      }
      // Shift remaining outputs
      for (size_t j = i; j < ctx.output_count - 1; ++j) {
        ctx.outputs[j] = ctx.outputs[j + 1];
      }
      // Zero out the now-unused slot
      ctx.outputs[ctx.output_count - 1] = {};
      ctx.output_count--;
      break;
    }
  }

  if (!removed_bound && wayland_ctx.output != BONGOCAT_NULLPTR) {
    wayland_ctx._output_name_str = BONGOCAT_NULLPTR;
    for (size_t i = 0; i < ctx.output_count; ++i) {
      if (ctx.outputs[i].wl_output == wayland_ctx.output) {
        wayland_ctx._output_name_str = ctx.outputs[i].name_str;
      }
    }
  }
}

}  // namespace bongocat::platform::wayland::details
