#ifndef BONGOCAT_WAYLAND_CONTEXT_H
#define BONGOCAT_WAYLAND_CONTEXT_H

#include "config/config.h"
#include "../protocols/zwlr-layer-shell-v1-client-protocol.h"
#include "../protocols/xdg-shell-client-protocol.h"
#include <wayland-client.h>
#include <stdatomic.h>

// Wayland globals
typedef struct {
    struct wl_display *display;
    struct wl_compositor *compositor;
    struct wl_shm *shm;
    struct zwlr_layer_shell_v1 *layer_shell;
    struct xdg_wm_base *xdg_wm_base;
    struct wl_output *output;
    struct wl_surface *surface;
    struct wl_buffer *buffer;
    struct zwlr_layer_surface_v1 *layer_surface;
    uint8_t *pixels;        ///< @NOTE: variable can be shared between child process and parent (see mmap)
    size_t pixels_size;
    atomic_bool configured;
    bool fullscreen_detected;

    // local copy from other thread, update after reload (shared memory)
    config_t *_local_copy_config;
    int _screen_width;
} wayland_context_t;

#endif // BONGOCAT_WAYLAND_CONTEXT_H