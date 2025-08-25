#ifndef BONGOCAT_ANIMATION_H
#define BONGOCAT_ANIMATION_H

#include "config/config.h"
#include "utils/error.h"
#include "platform/input_context.h"
#include "animation_context.h"
#include "global_animation_session.h"

namespace bongocat::animation {
    created_result_t<AllocatedMemory<animation_session_t>> create(const config::config_t& config);
    bongocat_error_t start(animation_session_t& ctx, platform::input::input_context_t& input, const config::config_t& config, pthread_mutex_t& config_reload_mutex, pthread_cond_t& config_reload_cond, atomic_uint64_t& config_generation);
    void trigger(animation_session_t& ctx);
    void trigger_update_config(animation_session_t& ctx, const config::config_t& config);
    void update_config(animation_context_t& ctx, const config::config_t& config);
}

#endif // BONGOCAT_ANIMATION_H