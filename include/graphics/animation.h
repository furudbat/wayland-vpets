#ifndef BONGOCAT_ANIMATION_H
#define BONGOCAT_ANIMATION_H

#include "config/config.h"
#include "utils/error.h"
#include "platform/input_context.h"
#include "platform/update_context.h"
#include "animation_context.h"
#include "global_animation_session.h"

namespace bongocat::animation {
    [[nodiscard]] created_result_t<AllocatedMemory<animation_session_t>> create(const config::config_t& config);
    bongocat_error_t start(animation_session_t& ctx, platform::input::input_context_t& input, platform::update::update_context_t& upd, const config::config_t& config, platform::CondVariable& configs_reloaded_cond, atomic_uint64_t& config_generation);
    void trigger(animation_session_t& ctx);
    void trigger_update_config(animation_session_t& ctx, const config::config_t& config, uint64_t config_generation);
    void update_config(animation_context_t& ctx, const config::config_t& config, uint64_t new_gen);
    created_result_t<animation_t*> hot_load_animation(animation_context_t& ctx);
    [[nodiscard]] animation_t& get_current_animation(animation_context_t& ctx);
}

#endif // BONGOCAT_ANIMATION_H