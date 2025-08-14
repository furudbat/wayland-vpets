#ifndef BONGOCAT_WAYLAND_CONTEXT_H
#define BONGOCAT_WAYLAND_CONTEXT_H

#include "wayland_shared_memory.h"
#include "config/config.h"
#include "../protocols/zwlr-layer-shell-v1-client-protocol.h"
#include "../protocols/xdg-shell-client-protocol.h"
#include <wayland-client.h>
#include <stdatomic.h>

// Wayland globals
struct wayland_context_t {
    wl_display *display{nullptr};
    wl_compositor *compositor{nullptr};
    wl_shm *shm{nullptr};
    zwlr_layer_shell_v1 *layer_shell{nullptr};
    struct xdg_wm_base *xdg_wm_base{nullptr};
    wl_output *output{nullptr};
    wl_surface *surface{nullptr};
    zwlr_layer_surface_v1 *layer_surface{nullptr};

    // @NOTE: variable can be shared between child process and parent (see mmap)
    wayland_shared_memory_t *ctx_shm{nullptr};

    // local copy from other thread, update after reload (shared memory)
    config_t *_local_copy_config{nullptr};
    int _screen_width{0};
    char* _output_name_str;                  // Will default to automatic one if kept null
    bool _fullscreen_detected{false};

    // frame done callback data
    wl_callback *_frame_cb{nullptr};
    pthread_mutex_t _frame_cb_lock{};
    atomic_bool _frame_pending{false};
    atomic_bool _redraw_after_frame{false};
    timestamp_ms_t _last_frame_timestamp_ms{0};
};

#endif // BONGOCAT_WAYLAND_CONTEXT_H