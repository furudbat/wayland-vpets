#ifndef BONGOCAT_INPUT_H
#define BONGOCAT_INPUT_H

#include "input_context.h"
#include "config/config.h"
#include "graphics/global_animation_session.h"
#include "utils/error.h"

namespace bongocat::platform::input {
    created_result_t<AllocatedMemory<input_context_t>> create(const config::config_t& config);
    bongocat_error_t start_monitoring(input_context_t& input, animation::animation_session_t& trigger_ctx, const config::config_t& config, pthread_mutex_t& config_reload_mutex, pthread_cond_t& config_reload_cond, atomic_uint64_t& config_generation);
    bongocat_error_t restart_monitoring(input_context_t& input, animation::animation_session_t& trigger_ctx, const config::config_t& config, pthread_mutex_t& config_reload_mutex, pthread_cond_t& config_reload_cond, atomic_uint64_t& config_generation);
    void update_config(input_context_t& ctx, const config::config_t& config);
    void trigger_update_config(input_context_t& ctx, const config::config_t& config);
}

#endif // BONGOCAT_INPUT_H