#ifndef BONGOCAT_INPUT_H
#define BONGOCAT_INPUT_H

#include "input_context.h"
#include "config/config.h"
#include "graphics/global_animation_session.h"
#include "utils/error.h"

namespace bongocat::platform::input {
    [[nodiscard]] created_result_t<AllocatedMemory<input_context_t>> create(const config::config_t& config);
    bongocat_error_t start(input_context_t& input, animation::animation_session_t& trigger_ctx, const config::config_t& config, CondVariable& configs_reloaded_cond, atomic_uint64_t& config_generation);
    bongocat_error_t restart(input_context_t& input, animation::animation_session_t& trigger_ctx, const config::config_t& config, CondVariable& configs_reloaded_cond, atomic_uint64_t& config_generation);
    void trigger_update_config(input_context_t& ctx, const config::config_t& config, uint64_t config_generation);
    void update_config(input_context_t& ctx, const config::config_t& config, uint64_t new_gen);
}

#endif // BONGOCAT_INPUT_H