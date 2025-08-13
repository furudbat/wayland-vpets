#ifndef BONGOCAT_WAYLAND_CONTEXT_H
#define BONGOCAT_WAYLAND_CONTEXT_H

#include "wayland_shared_memory.h"
#include "config/config.h"
#include "../protocols/zwlr-layer-shell-v1-client-protocol.h"
#include "../protocols/xdg-shell-client-protocol.h"
#include <wayland-client.h>
#include <stdatomic.h>
#include <pthread.h>

// Wayland globals
struct wayland_context_t {
    wl_display *display{NULL};
    wl_compositor *compositor{NULL};
    wl_shm *shm{NULL};
    zwlr_layer_shell_v1 *layer_shell{NULL};
    struct xdg_wm_base *xdg_wm_base{NULL};
    wl_output *output{NULL};
    wl_surface *surface{NULL};
    zwlr_layer_surface_v1 *layer_surface{NULL};

    // @NOTE: variable can be shared between child process and parent (see mmap)
    wayland_shared_memory_t *ctx_shm{NULL};

    // local copy from other thread, update after reload (shared memory)
    config_t *_local_copy_config{NULL};
    int _screen_width{0};
    char* _output_name_str;                  // Will default to automatic one if kept null
    bool _fullscreen_detected{false};

    // frame done callback data
    wl_callback *_frame_cb{NULL};
    pthread_mutex_t _frame_cb_lock{};
    atomic_bool _frame_pending{false};
    atomic_bool _redraw_after_frame{false};
    timestamp_ms_t _last_frame_timestamp_ms{0};
};

#endif // BONGOCAT_WAYLAND_CONTEXT_H