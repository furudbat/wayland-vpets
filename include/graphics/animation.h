#ifndef BONGOCAT_ANIMATION_H
#define BONGOCAT_ANIMATION_H

#include "animation_context.h"
#include "animation_thread_context.h"
#include "config/config.h"
#include "graphics/animation_shared_memory.h"
#include "platform/input_context.h"
#include "platform/update_context.h"
#include "utils/error.h"

#include <cstdint>

namespace bongocat::animation {
struct animation_state_t;
enum class trigger_animation_cause_mask_t : uint64_t {
  NONE = 0,
  Init = (1u << 0),
  KeyPress = (1u << 1),
  IdleUpdate = (1u << 2),
  CpuUpdate = (1u << 3),
  UpdateConfig = (1u << 4),
  Timeout = (1u << 5),
  EvolutionUpdate = (1u << 6),
  StartEvolution = (1u << 7),
};

// =============================================================================
// ANIMATION LIFECYCLE
// =============================================================================

// Initialize animation system - must be checked
BONGOCAT_NODISCARD created_result_t<AllocatedMemory<animation_context_t>> create(const config::config_t& config);

// Start animation thread - must be checked
BONGOCAT_NODISCARD bongocat_error_t start(animation_context_t& ctx, platform::input::input_context_t& input,
                                          platform::update::update_context_t& upd, const config::config_t& config,
                                          platform::CondVariable& configs_reloaded_cond,
                                          atomic_uint64_t& config_generation);

// Trigger key press animation
void trigger(animation_context_t& ctx, trigger_animation_cause_mask_t cause);
void trigger_update_config(animation_context_t& ctx, const config::config_t& config, uint64_t config_generation);
void trigger_reload_animation(animation_context_t& animation_ctx);

void update_config(animation_thread_context_t& ctx, const config::config_t& config, uint64_t new_gen);
created_result_t<animation_t *> hot_load_animation(animation_thread_context_t& ctx);
BONGOCAT_NODISCARD animation_t& get_current_animation(animation_thread_context_t& ctx);

namespace details {
  created_result_t<custom_sprite_sheet_t> anim_load_custom_animation(animation_thread_context_t& ctx,
                                                                     const config::config_t& config);

  struct phys_dim_params {
    int logical{0};
    int scale120{120};
  };
  int phys_dim(phys_dim_params params);
  void update_cat_height_physical(animation_thread_context_t& ctx);

  void update_evolution_data(animation_shared_memory_t& shm);
}  // namespace details
}  // namespace bongocat::animation

extern "C" {
extern const char __start_assets_images[];
extern const char __stop_assets_images[];
extern const char __start_assets_data_evol[];
extern const char __stop_assets_data_evol[];
extern const char __start_assets_sprite_settings[];
extern const char __stop_assets_sprite_settings[];
}

#endif  // BONGOCAT_ANIMATION_H