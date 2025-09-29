#ifndef BONGOCAT_UPDATE_H
#define BONGOCAT_UPDATE_H

#include "update_context.h"
#include "config/config.h"
#include "graphics/global_animation_session.h"
#include "utils/error.h"

namespace bongocat::platform::update {
    [[nodiscard]] created_result_t<AllocatedMemory<update_context_t>> create(const config::config_t& config);
    bongocat_error_t start(update_context_t& input, animation::animation_session_t& trigger_ctx, const config::config_t& config, CondVariable& configs_reloaded_cond, atomic_uint64_t& config_generation);
    bongocat_error_t restart(update_context_t& input, animation::animation_session_t& trigger_ctx, const config::config_t& config, CondVariable& configs_reloaded_cond, atomic_uint64_t& config_generation);
    void trigger_update_config(update_context_t& ctx, const config::config_t& config, uint64_t config_generation);
    void update_config(update_context_t& ctx, const config::config_t& config, uint64_t new_gen);
    const cpu_snapshot_t& get_latest_snapshot(update_context_t& ctx);
}

#endif // BONGOCAT_UPDATE_H