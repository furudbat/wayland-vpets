#ifndef BONGOCAT_ANIMATION_H
#define BONGOCAT_ANIMATION_H

#include "animation_context.h"
#include "animation_thread_context.h"
#include "config/config.h"
#include "drawing.h"
#include "graphics/animation_shared_memory.h"
#include "platform/input_context.h"
#include "platform/update_context.h"
#include "utils/error.h"

#include <cstdint>

namespace bongocat::animation {
struct animation_state_t;
enum class trigger_animation_cause_mask_t : uint64_t {
  NONE = 0,
  Init = (1u << 0u),
  KeyPress = (1u << 1u),
  IdleUpdate = (1u << 2u),
  CpuUpdate = (1u << 3u),
  UpdateConfig = (1u << 4u),
  Timeout = (1u << 5u),
  EvolutionUpdate = (1u << 6u),
  StartEvolution = (1u << 7u),
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

  BONGOCAT_NODISCARD int phys_dim(scale_120_params params);
  void update_cat_height_physical(animation_thread_context_t& ctx);

  void update_evolution_data(animation_shared_memory_t& shm);

  void unload_assets_readonly_sections();
  void unload_current_assets_set_readonly_sections(const animation_shared_memory_t& anim_shm);

  struct assets_set_region_t {
    const char *start{BONGOCAT_NULLPTR};
    const char *stop{BONGOCAT_NULLPTR};
    const char *name{"none"};
  };
#define BONGOCAT_ASSETS_SET_REGION(set)                                        \
  ::bongocat::animation::details::assets_set_region_t {                        \
    _bongocat_start_assets_##set, _bongocat_stop_assets_##set, ".assets." #set \
  }

  assets_set_region_t get_assets_set_region(const animation_shared_memory_t& anim_shm);
  void load_assets_set_readonly_sections(const assets_set_region_t& region);
  void unload_assets_set_readonly_sections(const assets_set_region_t& region);

  class assets_set_scope_t {
  public:
    assets_set_scope_t() = default;
    explicit assets_set_scope_t(const assets_set_region_t& region) {
      load(region);
    }
    ~assets_set_scope_t() {
      unload();
    }
    assets_set_scope_t(const assets_set_scope_t&) = delete;
    assets_set_scope_t& operator=(const assets_set_scope_t&) = delete;
    assets_set_scope_t(assets_set_scope_t&&) = delete;
    assets_set_scope_t& operator=(assets_set_scope_t&&) = delete;

    void load(const assets_set_region_t& region) {
      unload();
      _region = region;
      _loaded = true;
      load_assets_set_readonly_sections(_region);
    }
    void unload() {
      if (_loaded) {
        unload_assets_set_readonly_sections(_region);
        _loaded = false;
      }
    }

  private:
    assets_set_region_t _region;
    bool _loaded{false};
  };
}  // namespace details

}  // namespace bongocat::animation

extern "C" {
extern const char _bongocat_start_assets[];
extern const char _bongocat_stop_assets[];
}

#endif  // BONGOCAT_ANIMATION_H