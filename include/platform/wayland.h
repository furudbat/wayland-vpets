#ifndef BONGOCAT_WAYLAND_H
#define BONGOCAT_WAYLAND_H

#include "wayland_context.h"
#include "graphics/animation_context.h"
#include "graphics/animation_event_context.h"
#include "global_wayland_context.h"
#include "config/config.h"
#include "utils/error.h"
#include "core/bongocat.h"
#include <csignal>
#include <sys/types.h>


typedef void (*config_reload_callback_t)();

bongocat_error_t wayland_init(wayland_listeners_context_t* ctx, wayland_context_t* wayland, animation_context_t *anim, animation_trigger_context_t *trigger_ctx, const config_t *config);
bongocat_error_t wayland_run(wayland_listeners_context_t* ctx, volatile sig_atomic_t *running, int signal_fd, const config_t *config, config_watcher_t* config_watcher, config_reload_callback_t config_reload_callback);
void wayland_cleanup(wayland_listeners_context_t *ctx);
void wayland_update_config(wayland_context_t *ctx, const config_t *config, animation_trigger_context_t *trigger_ctx);
int create_shm(off_t size);
int wayland_get_screen_width(wayland_listeners_context_t* ctx);
const char* wayland_get_current_layer_name(void);
bongocat_error_t wayland_request_render(animation_trigger_context_t *trigger_ctx);

#endif // WAYLAND_H