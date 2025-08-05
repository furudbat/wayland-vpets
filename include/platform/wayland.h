#ifndef BONGOCAT_WAYLAND_H
#define BONGOCAT_WAYLAND_H

#include "config/config.h"
#include "utils/error.h"
#include "graphics/context.h"
#include "../protocols/zwlr-layer-shell-v1-client-protocol.h"
#include "../protocols/xdg-shell-client-protocol.h"
#include <signal.h>
#include <wayland-client.h>
#include <sys/types.h>

typedef void (*config_reload_callback_t)();

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
    bool configured;
    bool fullscreen_detected;

    // local copy from other thread, update after reload (shared memory)
    config_t* _local_copy_config;
    int _screen_width;

    animation_context_t *_anim;
} wayland_context_t;

bongocat_error_t wayland_init(wayland_context_t* ctx, const config_t *config, animation_context_t* anim);
bongocat_error_t wayland_run(wayland_context_t* ctx, volatile sig_atomic_t *running, int signal_fd, config_watcher_t* config_watcher, config_reload_callback_t config_reload_callback);
void wayland_cleanup(wayland_context_t *ctx);
void wayland_update_config(wayland_context_t *ctx, const config_t *config, animation_context_t* anim);
void draw_bar(wayland_context_t *ctx);
int create_shm(off_t size);
int wayland_get_screen_width(void);
const char* wayland_get_current_layer_name(void);

#endif // WAYLAND_H