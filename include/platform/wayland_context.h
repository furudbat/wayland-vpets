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

struct wayland_context_t;
// Cleanup Wayland resources
void cleanup_wayland_context(wayland_context_t& ctx);

enum class bar_visibility_t : bool {
  Hide = false,
  Show = true
};

struct screen_info_t;

struct wayland_context_t {
  wl_display *display{BONGOCAT_NULLPTR};
  wl_compositor *compositor{BONGOCAT_NULLPTR};
  wl_shm *shm{BONGOCAT_NULLPTR};
  zwlr_layer_shell_v1 *layer_shell{BONGOCAT_NULLPTR};
  struct xdg_wm_base *xdg_wm_base{BONGOCAT_NULLPTR};
  wl_output *output{BONGOCAT_NULLPTR};
  wl_surface *surface{BONGOCAT_NULLPTR};
  zwlr_layer_surface_v1 *layer_surface{BONGOCAT_NULLPTR};

  // Output reconnection handling
  struct wl_registry *registry{BONGOCAT_NULLPTR};
  uint32_t bound_output_name{0};   // Registry name of our bound output
  bool using_named_output{false};  // True if user specified an output name

  // local copy from other thread, update after reload (shared memory)
  MMapMemory<config::config_t> _local_copy_config;
  MMapMemory<wayland_shared_memory_t> ctx_shm;
  bar_visibility_t bar_visibility{bar_visibility_t::Show};

  int32_t _bar_height{0};
  int32_t _screen_width{0};
  char *_output_name_str{
      BONGOCAT_NULLPTR};  // ref to existing name in output, Will default to automatic one if kept null
  bool _fullscreen_detected{false};
  screen_info_t *_screen_info{BONGOCAT_NULLPTR};

  // frame done callback data
  wl_callback *_frame_cb{BONGOCAT_NULLPTR};
  Mutex _frame_cb_lock;
  atomic_bool _frame_pending{false};
  atomic_bool _redraw_after_frame{false};
  timestamp_ms_t _last_frame_timestamp_ms{0};

  wayland_context_t() = default;
  ~wayland_context_t() {
    cleanup_wayland_context(*this);
  }

  wayland_context_t(const wayland_context_t&) = delete;
  wayland_context_t& operator=(const wayland_context_t&) = delete;
  wayland_context_t(wayland_context_t&& other) noexcept = delete;
  wayland_context_t& operator=(wayland_context_t&& other) noexcept = delete;
};

inline void cleanup_wayland_context_protocols(wayland_context_t& ctx) {
  if (ctx.ctx_shm) {
    atomic_store(&ctx.ctx_shm->configured, false);
  }

  if (ctx.registry != BONGOCAT_NULLPTR) {
    wl_registry_destroy(ctx.registry);
    ctx.registry = BONGOCAT_NULLPTR;
  }
}
inline void cleanup_wayland_context_surface(wayland_context_t& ctx) {
  if (ctx.ctx_shm) {
    atomic_store(&ctx.ctx_shm->configured, false);
  }

  if (ctx.layer_surface != BONGOCAT_NULLPTR) {
    zwlr_layer_surface_v1_destroy(ctx.layer_surface);
    ctx.layer_surface = BONGOCAT_NULLPTR;
  }
  if (ctx.surface != BONGOCAT_NULLPTR) {
    wl_surface_destroy(ctx.surface);
    ctx.surface = BONGOCAT_NULLPTR;
  }
}
inline void cleanup_wayland_context_buffer(wayland_context_t& ctx) {
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
  ctx._bar_height = 0;
}
inline void cleanup_wayland_context(wayland_context_t& ctx) {
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
  ctx._bar_height = 0;
  ctx._screen_width = 0;
  ctx._fullscreen_detected = false;
  ctx._screen_info = BONGOCAT_NULLPTR;
}
}  // namespace bongocat::platform::wayland

#endif  // BONGOCAT_WAYLAND_CONTEXT_H