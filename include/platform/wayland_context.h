#ifndef BONGOCAT_WAYLAND_CONTEXT_H
#define BONGOCAT_WAYLAND_CONTEXT_H

#include "wayland_shared_memory.h"
#include "config/config.h"
#include <wayland-client.h>
#include <stdatomic.h>

struct zwlr_layer_shell_v1;
struct zwlr_layer_surface_v1;

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
    MMapMemory<wayland_shared_memory_t> ctx_shm;

    // local copy from other thread, update after reload (shared memory)
    MMapMemory<config_t> _local_copy_config;
    int _screen_width{0};
    char* _output_name_str;                  // Will default to automatic one if kept null
    bool _fullscreen_detected{false};

    // frame done callback data
    wl_callback *_frame_cb{nullptr};
    Mutex _frame_cb_lock;
    atomic_bool _frame_pending{false};
    atomic_bool _redraw_after_frame{false};
    timestamp_ms_t _last_frame_timestamp_ms{0};
};

#endif // BONGOCAT_WAYLAND_CONTEXT_H