#ifndef BONGOCAT_ANIMATION_H
#define BONGOCAT_ANIMATION_H

#include "config/config.h"
#include "utils/error.h"
#include "platform/input_context.h"
#include "platform/update_context.h"
#include "animation_context.h"
#include "global_animation_session.h"

namespace bongocat::animation {
    enum class trigger_animation_cause_mask_t : uint64_t {
        NONE = 0,
        Init = (1U << 0),
        KeyPress = (1U << 1),
        IdleUpdate = (1U << 2),
        CpuUpdate = (1U << 3),
        UpdateConfig = (1U << 4),
        Timeout = (1U << 5),
    };

// =============================================================================
// ANIMATION LIFECYCLE
// =============================================================================

    // Initialize animation system - must be checked
    BONGOCAT_NODISCARD created_result_t<AllocatedMemory<animation_session_t>> create(const config::config_t& config);

    // Start animation thread - must be checked
    BONGOCAT_NODISCARD bongocat_error_t start(animation_session_t& ctx, platform::input::input_context_t& input, platform::update::update_context_t& upd, const config::config_t& config, platform::CondVariable& configs_reloaded_cond, atomic_uint64_t& config_generation);

    // Trigger key press animation
    void trigger(animation_session_t& ctx, trigger_animation_cause_mask_t cause);
    void trigger_update_config(animation_session_t& ctx, const config::config_t& config, uint64_t config_generation);

    void update_config(animation_context_t& ctx, const config::config_t& config, uint64_t new_gen);
    created_result_t<animation_t*> hot_load_animation(animation_context_t& ctx);
    BONGOCAT_NODISCARD animation_t& get_current_animation(animation_context_t& ctx);

    namespace details {
        created_result_t<custom_sprite_sheet_t> anim_load_custom_animation(animation_context_t& ctx, const config::config_t& config);
    }
}

#endif // BONGOCAT_ANIMATION_H