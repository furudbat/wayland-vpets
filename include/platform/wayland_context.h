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
typedef struct {
    struct wl_display *display;
    struct wl_compositor *compositor;
    struct wl_shm *shm;
    struct zwlr_layer_shell_v1 *layer_shell;
    struct xdg_wm_base *xdg_wm_base;
    struct wl_output *output;
    struct wl_surface *surface;
    struct zwlr_layer_surface_v1 *layer_surface;

    // @NOTE: variable can be shared between child process and parent (see mmap)
    wayland_shared_memory_t *ctx_shm;

    // local copy from other thread, update after reload (shared memory)
    config_t *_local_copy_config;
    int _screen_width;
    char* _output_name_str;                  // Will default to automatic one if kept null
    bool _fullscreen_detected;

    // frame done callback data
    struct wl_callback *_frame_cb;
    pthread_mutex_t _frame_cb_lock;
    atomic_bool _frame_pending;
    atomic_bool _redraw_after_frame;
    timestamp_ms_t _last_frame_timestamp_ms;
} wayland_context_t;

#endif // BONGOCAT_WAYLAND_CONTEXT_H