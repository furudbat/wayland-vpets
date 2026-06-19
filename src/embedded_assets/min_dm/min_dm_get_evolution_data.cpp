#include "embedded_assets/embedded_image.h"
#include "embedded_assets/min_dm/min_dm.hpp"
#include "embedded_assets/min_dm/min_dm_evol.h"
#include "graphics/animation_shared_memory.h"

namespace bongocat::assets {

inline static constexpr animation::animation_evolution_conditions_t STAGE_I_CONDITIONS = {
  .next_evolution_time_sec = 10 * 60,  // 10 min
};
inline static constexpr animation::animation_evolution_conditions_t STAGE_II_CONDITIONS = {
  .next_evolution_time_sec = 6 * (60 * 60),  // 6h
};
inline static constexpr animation::animation_evolution_conditions_t STAGE_III_CONDITIONS = {
  .next_evolution_time_sec = 24 * (60 * 60),  // 24h
};
inline static constexpr animation::animation_evolution_conditions_t STAGE_IV_CONDITIONS = {
  .next_evolution_time_sec = 36 * (60 * 60),  // 36h
};
inline static constexpr animation::animation_evolution_conditions_t STAGE_V_CONDITIONS = {
  .next_evolution_time_sec = 48 * (60 * 60),  // 48h
};
inline static constexpr animation::animation_evolution_conditions_t STAGE_VI_CONDITIONS = {
  .next_evolution_time_sec = -1,  // N/A
};
inline static constexpr animation::animation_evolution_conditions_t STAGE_VIp_CONDITIONS = {
  .next_evolution_time_sec = -1,  // N/A
};

static constexpr animation::animation_evolution_data_t min_dm_evol_data_table[] ASSETS_DATA_EVOL_SECTION = {
    {
      .conditions = STAGE_I_CONDITIONS,

      .num_animation_indices = 1,
      .animation_indices ={
        DM_KOROMON_ANIM_INDEX,
      },
    },
    {
      .conditions = STAGE_II_CONDITIONS,

      .num_animation_indices = 2,
      .animation_indices ={
        DM_AGUMON_ANIM_INDEX,
        DM_BETAMON_ANIM_INDEX,
      },
    },
    {
      .conditions = STAGE_III_CONDITIONS,

      .num_animation_indices = 5,
      .animation_indices ={
        DM_GREYMON_ANIM_INDEX,
        DM_TYRANOMON_ANIM_INDEX,
        DM_DEVIMON_ANIM_INDEX,
        DM_MERAMON_ANIM_INDEX,
        DM_NUMEMON_ANIM_INDEX,
      },
    },
    {
      .conditions = STAGE_III_CONDITIONS,

      .num_animation_indices = 5,
      .animation_indices ={
        DM_DEVIMON_ANIM_INDEX,
        DM_MERAMON_ANIM_INDEX,
        DM_AIRDRAMON_ANIM_INDEX,
        DM_SEADRAMON_ANIM_INDEX,
        DM_NUMEMON_ANIM_INDEX,
      },
    },
    {
      .conditions = STAGE_IV_CONDITIONS,

      .num_animation_indices = 1,
      .animation_indices ={
        DM_METAL_GREYMON_ANIM_INDEX,
      },
    },
    {
      .conditions = STAGE_IV_CONDITIONS,

      .num_animation_indices = 1,
      .animation_indices ={
        DM_MAMEMON_ANIM_INDEX,
      },
    },
    {
      .conditions = STAGE_IV_CONDITIONS,

      .num_animation_indices = 1,
      .animation_indices ={
        DM_METAL_GREYMON_ANIM_INDEX,
      },
    },
    {
      .conditions = STAGE_IV_CONDITIONS,

      .num_animation_indices = 1,
      .animation_indices ={
        DM_MAMEMON_ANIM_INDEX,
      },
    },
    {
      .conditions = STAGE_IV_CONDITIONS,

      .num_animation_indices = 1,
      .animation_indices ={
        DM_METAL_GREYMON_ANIM_INDEX,
      },
    },
    {
      .conditions = STAGE_IV_CONDITIONS,

      .num_animation_indices = 1,
      .animation_indices ={
        DM_METAL_GREYMON_ANIM_INDEX,
      },
    },
    {
      .conditions = STAGE_IV_CONDITIONS,

      .num_animation_indices = 1,
      .animation_indices ={
        DM_MONZAEMON_ANIM_INDEX,
      },
    },
    {
      .conditions = {},

      .num_animation_indices = 0,
      .animation_indices ={
      },
    },
    {
      .conditions = {},

      .num_animation_indices = 0,
      .animation_indices ={
      },
    },
    {
      .conditions = {},

      .num_animation_indices = 0,
      .animation_indices ={
      },
    },
};
animation::animation_evolution_data_t get_min_dm_evolution_data(size_t index) {
  using namespace assets;
  assert(LEN_ARRAY(min_dm_evol_data_table) == MIN_DM_ANIM_COUNT);
  assert(index < MIN_DM_ANIM_COUNT);
  return min_dm_evol_data_table[index];
}
}  // namespace bongocat::assets