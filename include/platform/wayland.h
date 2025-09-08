#ifndef BONGOCAT_WAYLAND_H
#define BONGOCAT_WAYLAND_H

#include "config/config_watcher.h"
#include "wayland_context.h"
#include "graphics/global_animation_session.h"
#include "global_wayland_session.h"
#include "config/config.h"
#include "utils/error.h"
#include <csignal>

namespace bongocat::platform::wayland {
    using config_reload_callback_t = void (*)();

    [[nodiscard]] created_result_t<AllocatedMemory<wayland_session_t>> create(animation::animation_session_t& anim, const config::config_t& config);
    bongocat_error_t setup(wayland_session_t& ctx, animation::animation_session_t& anim);
    bongocat_error_t run(wayland_session_t& ctx, volatile sig_atomic_t& running, int signal_fd, input::input_context_t& input, const config::config_t& config, const config::config_watcher_t* config_watcher, config_reload_callback_t config_reload_callback);
    void update_config(wayland_context_t& ctx, const config::config_t& config, animation::animation_session_t& trigger_ctx);

    [[nodiscard]] FileDescriptor create_shm(off_t size);

    [[nodiscard]] int get_screen_width(const wayland_session_t& ctx);
    [[nodiscard]] const char* get_current_layer_name();
    bongocat_error_t request_render(animation::animation_session_t& trigger_ctx);
}

#endif // BONGOCAT_WAYLAND_H