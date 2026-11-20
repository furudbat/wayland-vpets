#include "embedded_assets/embedded_image.h"
#include "embedded_assets/min_dm/min_dm.hpp"
#include "embedded_assets/min_dm/min_dm_evol.h"
#include "graphics/animation_shared_memory.h"

/// @NOTE: Generated evolution data min_dm

namespace bongocat::assets {
      struct compact_evolution_conditions_t {
          int32_t next_evolution_time_sec{-1};
          int8_t min_lvl{-1};
      };
      struct compact_evolution_data_t {
          compact_evolution_conditions_t conditions;
          uint8_t num_animation_indices{0};
          int16_t animation_indices[animation::MAX_ANIMATION_EVOLUTION_INDICIES]{};
      };
      static animation::animation_evolution_data_t expand_evolution_data(const compact_evolution_data_t& data) {
          animation::animation_evolution_data_t ret;
          ret.conditions.next_evolution_time_sec = data.conditions.next_evolution_time_sec;
          ret.conditions.min_lvl = data.conditions.min_lvl;
          ret.num_animation_indices = data.num_animation_indices;
          for (size_t i = 0; i < animation::MAX_ANIMATION_EVOLUTION_INDICIES; ++i) {
              ret.animation_indices[i] = data.animation_indices[i];
          }
          return ret;
      }
    static constexpr compact_evolution_data_t min_dm_evol_data_table[] ASSETS_MIN_DM_EVOL_DATA_SECTION = {
        // Name: Botamon
        {
            // Stage: Baby I
            .conditions = { .next_evolution_time_sec = 600 },
            .num_animation_indices = 1,
            .animation_indices = {
                MIN_DM_KOROMON_ANIM_INDEX
            },
        },
        // Name: Koromon
        {
            // Stage: Baby II
            .conditions = { .next_evolution_time_sec = 21600 },
            .num_animation_indices = 2,
            .animation_indices = {
                MIN_DM_AGUMON_ANIM_INDEX ,MIN_DM_BETAMON_ANIM_INDEX
            },
        },
        // Name: Agumon
        {
            // Stage: Child
            .conditions = { .next_evolution_time_sec = 86400 },
            .num_animation_indices = 5,
            .animation_indices = {
                MIN_DM_GREYMON_ANIM_INDEX ,MIN_DM_TYRANOMON_ANIM_INDEX ,MIN_DM_DEVIMON_ANIM_INDEX ,MIN_DM_MERAMON_ANIM_INDEX ,MIN_DM_NUMEMON_ANIM_INDEX
            },
        },
        // Name: Betamon
        {
            // Stage: Child
            .conditions = { .next_evolution_time_sec = 86400 },
            .num_animation_indices = 5,
            .animation_indices = {
                MIN_DM_DEVIMON_ANIM_INDEX ,MIN_DM_MERAMON_ANIM_INDEX ,MIN_DM_AIRDRAMON_ANIM_INDEX ,MIN_DM_SEADRAMON_ANIM_INDEX ,MIN_DM_NUMEMON_ANIM_INDEX
            },
        },
        // Name: Greymon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 129600 },
            .num_animation_indices = 1,
            .animation_indices = {
                MIN_DM_METAL_GREYMON_ANIM_INDEX
            },
        },
        // Name: Tyranomon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 129600 },
            .num_animation_indices = 1,
            .animation_indices = {
                MIN_DM_MAMEMON_ANIM_INDEX
            },
        },
        // Name: Devimon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 129600 },
            .num_animation_indices = 1,
            .animation_indices = {
                MIN_DM_METAL_GREYMON_ANIM_INDEX
            },
        },
        // Name: Meramon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 129600 },
            .num_animation_indices = 1,
            .animation_indices = {
                MIN_DM_MAMEMON_ANIM_INDEX
            },
        },
        // Name: Airdramon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 129600 },
            .num_animation_indices = 1,
            .animation_indices = {
                MIN_DM_METAL_GREYMON_ANIM_INDEX
            },
        },
        // Name: Seadramon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 129600 },
            .num_animation_indices = 1,
            .animation_indices = {
                MIN_DM_MAMEMON_ANIM_INDEX
            },
        },
        // Name: Numemon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 129600 },
            .num_animation_indices = 1,
            .animation_indices = {
                MIN_DM_MONZAEMON_ANIM_INDEX
            },
        },
        // Name: Metal Greymon
        {
            // Stage: Perfect
            .conditions = { .next_evolution_time_sec = 172800 },
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Mamemon
        {
            // Stage: Perfect
            .conditions = { .next_evolution_time_sec = 172800 },
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Monzaemon
        {
            // Stage: Perfect
            .conditions = { .next_evolution_time_sec = 172800 },
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
    };
    static_assert(LEN_ARRAY(min_dm_evol_data_table) == MIN_DM_ANIM_COUNT, "re-run scripts/generate_embedded_assets_min_dm_evol.sh");
    animation::animation_evolution_data_t get_min_dm_evolution_data(size_t index) {
        using namespace assets;
        assert(index < MIN_DM_ANIM_COUNT);
        return expand_evolution_data(min_dm_evol_data_table[index]);
    }
}
