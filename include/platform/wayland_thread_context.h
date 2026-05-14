#ifndef BONGOCAT_WAYLAND_CONTEXT_H
#define BONGOCAT_WAYLAND_CONTEXT_H

struct zwlr_layer_shell_v1;
struct zwlr_layer_surface_v1;
#include "config/config.h"
#include "platform/wayland-protocols.hpp"
#include "wayland_shared_memory.h"

#include <stdatomic.h>
#include <wayland-client.h>

namespace bongocat::platform::wayland {
inline static constexpr int MAX_ATTEMPTS = 4096;
inline static constexpr int DEFAULT_PREFER_SCALE = 120;

struct wayland_thread_context;
// Cleanup Wayland resources
void cleanup_wayland_context(wayland_thread_context& ctx);

enum class bar_visibility_t : bool {
  Hide = false,
  Show = true
};

struct screen_info_t;

struct wayland_thread_context {
  wl_display *display{BONGOCAT_NULLPTR};
  wl_compositor *compositor{BONGOCAT_NULLPTR};
  wl_shm *shm{BONGOCAT_NULLPTR};
  zwlr_layer_shell_v1 *layer_shell{BONGOCAT_NULLPTR};
  struct xdg_wm_base *xdg_wm_base{BONGOCAT_NULLPTR};
  wl_output *output{BONGOCAT_NULLPTR};
  wl_surface *surface{BONGOCAT_NULLPTR};
  zwlr_layer_surface_v1 *layer_surface{BONGOCAT_NULLPTR};
  struct wl_registry *registry{BONGOCAT_NULLPTR};
  uint32_t layer_shell_version{0};

  // Output reconnection handling
  uint32_t bound_output_name{0};   // Registry name of our bound output
  bool using_named_output{false};  // True if user specified an output name

  // local copy from other thread, update after reload (shared memory)
  MMapMemory<config::config_t> _local_copy_config;
  MMapMemory<wayland_shared_memory_t> ctx_shm;
  bar_visibility_t bar_visibility{bar_visibility_t::Show};

  int32_t _overlay_height{0};     // applied_height
  int32_t _screen_width{0};       // applied_width
  // ref to existing name in output, Will default to automatic one if kept null
  char *_output_name_str{BONGOCAT_NULLPTR};  // bound_screen_name
  bool _fullscreen_detected{false};
  screen_info_t *_screen_info{BONGOCAT_NULLPTR};
  config::layer_type_t _layer{config::layer_type_t::LAYER_TOP};
  config::overlay_position_t _overlay_position{config::overlay_position_t::POSITION_BOTTOM};
  AllocatedString _target_output_name;  // applied_output_name

  // frame done callback data
  wl_callback *_frame_cb{BONGOCAT_NULLPTR};
  Mutex _frame_cb_lock;
  atomic_bool _frame_pending{false};
  atomic_bool _redraw_after_frame{false};
  timestamp_ms_t _last_frame_timestamp_ms{0};

  // HiDPI: fractional-scale + viewporter
  struct wp_viewporter *viewporter{BONGOCAT_NULLPTR};
  struct wp_fractional_scale_manager_v1 *fractional_scale_mgr{BONGOCAT_NULLPTR};
  struct wp_viewport *_viewport{BONGOCAT_NULLPTR};
  struct wp_fractional_scale_v1 *_fractional_scale_obj{BONGOCAT_NULLPTR};
  // Effective render scale, encoded as numerator over 120 (so 120 = 1.0×, 240 =
  // 2.0×, 180 = 1.5×). Updated via wp_fractional_scale_v1::preferred_scale or
  // wl_output::scale fallback.
  uint32_t _preferred_scale{DEFAULT_PREFER_SCALE};

  wayland_thread_context() = default;
  ~wayland_thread_context() {
    cleanup_wayland_context(*this);
  }

  wayland_thread_context(const wayland_thread_context&) = delete;
  wayland_thread_context& operator=(const wayland_thread_context&) = delete;
  wayland_thread_context(wayland_thread_context&& other) noexcept = delete;
  wayland_thread_context& operator=(wayland_thread_context&& other) noexcept = delete;
};

inline void cleanup_wayland_context_protocols(wayland_thread_context& ctx) {
  if (ctx.ctx_shm) {
    atomic_store(&ctx.ctx_shm->configured, false);
  }

  if (ctx.registry != BONGOCAT_NULLPTR) {
    wl_registry_destroy(ctx.registry);
    ctx.registry = BONGOCAT_NULLPTR;
  }
}
inline void cleanup_wayland_context_surface(wayland_thread_context& ctx) {
  if (ctx.ctx_shm) {
    atomic_store(&ctx.ctx_shm->configured, false);
  }

  if (ctx.layer_surface != BONGOCAT_NULLPTR) {
    zwlr_layer_surface_v1_destroy(ctx.layer_surface);
    ctx.layer_surface = BONGOCAT_NULLPTR;
  }

  // Per-surface HiDPI receivers must die with the surface; setup_surface
  // will recreate them attached to the new wl_surface.
  if (ctx._fractional_scale_obj) {
    wp_fractional_scale_v1_destroy(ctx._fractional_scale_obj);
    ctx._fractional_scale_obj = BONGOCAT_NULLPTR;
  }
  if (ctx._viewport) {
    wp_viewport_destroy(ctx._viewport);
    ctx._viewport = BONGOCAT_NULLPTR;
  }
  // Destroy fractional-scale and viewport receivers before the surface they
  // reference.

  if (ctx.surface != BONGOCAT_NULLPTR) {
    wl_surface_destroy(ctx.surface);
    ctx.surface = BONGOCAT_NULLPTR;
  }
}
inline void cleanup_wayland_context_buffer(wayland_thread_context& ctx) {
  if (ctx.ctx_shm) {
    atomic_store(&ctx.ctx_shm->configured, false);
  }

  if (ctx.ctx_shm) {
    for (size_t i = 0; i < WAYLAND_NUM_BUFFERS; i++) {
      cleanup_shm_buffer(ctx.ctx_shm->buffers[i]);
    }

    ctx.ctx_shm->current_buffer_index = 0;
  }

  ctx._screen_width = 0;
  ctx._overlay_height = 0;
}
inline void cleanup_wayland_context(wayland_thread_context& ctx) {
  if (ctx.ctx_shm) {
    atomic_store(&ctx.ctx_shm->configured, false);
  }

  // drain pending events
  if (ctx.display != BONGOCAT_NULLPTR) {
    wl_display_flush(ctx.display);
    wl_display_roundtrip(ctx.display);
    int attempts = 0;
    while (wl_display_dispatch_pending(ctx.display) > 0 && attempts <= MAX_ATTEMPTS) {
      attempts++;
    }
    if (attempts >= MAX_ATTEMPTS && wl_display_dispatch_pending(ctx.display) > 0) {
      BONGOCAT_LOG_ERROR("Cant fully drain wayland display, max attempts: %i", attempts);
    }
  }

  cleanup_wayland_context_protocols(ctx);

  // release frame.done handler
  atomic_store(&ctx._frame_pending, false);
  atomic_store(&ctx._redraw_after_frame, false);
  // ctx._frame_cb_lock should be unlocked
  if (ctx._frame_cb != BONGOCAT_NULLPTR) {
    wl_callback_destroy(ctx._frame_cb);
    ctx._frame_cb = BONGOCAT_NULLPTR;
  }
  ctx._last_frame_timestamp_ms = 0;

  // surfaces
  cleanup_wayland_context_surface(ctx);

  if (ctx.layer_shell != BONGOCAT_NULLPTR) {
    zwlr_layer_shell_v1_destroy(ctx.layer_shell);
    ctx.layer_shell = BONGOCAT_NULLPTR;
    ctx.layer_shell_version = 0;
  }
  if (ctx.xdg_wm_base != BONGOCAT_NULLPTR) {
    xdg_wm_base_destroy(ctx.xdg_wm_base);
    ctx.xdg_wm_base = BONGOCAT_NULLPTR;
  }
  if (ctx.shm != BONGOCAT_NULLPTR) {
    wl_shm_destroy(ctx.shm);
    ctx.shm = BONGOCAT_NULLPTR;
  }
  if (ctx.compositor != BONGOCAT_NULLPTR) {
    wl_compositor_destroy(ctx.compositor);
    ctx.compositor = BONGOCAT_NULLPTR;
  }

  // release shm
  cleanup_wayland_context_buffer(ctx);
  release_allocated_mmap_memory(ctx.ctx_shm);
  release_allocated_mmap_memory(ctx._local_copy_config);

  if (ctx.display != BONGOCAT_NULLPTR) {
    wl_display_disconnect(ctx.display);
    ctx.display = BONGOCAT_NULLPTR;
  }

  // Note: output is just a reference to one of the outputs[] entries
  // It will be destroyed when we destroy the outputs[] array above
  ctx.output = BONGOCAT_NULLPTR;
  ctx.bound_output_name = 0;
  ctx.using_named_output = false;

  // Reset state
  ctx.display = BONGOCAT_NULLPTR;
  ctx.compositor = BONGOCAT_NULLPTR;
  ctx.shm = BONGOCAT_NULLPTR;
  ctx.layer_shell = BONGOCAT_NULLPTR;
  ctx.xdg_wm_base = BONGOCAT_NULLPTR;
  ctx.output = BONGOCAT_NULLPTR;
  ctx.surface = BONGOCAT_NULLPTR;
  ctx.layer_surface = BONGOCAT_NULLPTR;
  ctx._output_name_str = BONGOCAT_NULLPTR;
  ctx._frame_pending = false;
  ctx._redraw_after_frame = false;
  ctx._overlay_height = 0;
  ctx._screen_width = 0;
  ctx._fullscreen_detected = false;
  ctx._screen_info = BONGOCAT_NULLPTR;
  ctx._layer = config::layer_type_t::LAYER_TOP;
  ctx._overlay_position = config::overlay_position_t::POSITION_BOTTOM;

  ctx.viewporter = BONGOCAT_NULLPTR;
  ctx.fractional_scale_mgr = BONGOCAT_NULLPTR;
  ctx._viewport = BONGOCAT_NULLPTR;
  ctx._fractional_scale_obj = BONGOCAT_NULLPTR;
  ctx._preferred_scale = DEFAULT_PREFER_SCALE;
}
}  // namespace bongocat::platform::wayland

#endif  // BONGOCAT_WAYLAND_CONTEXT_H