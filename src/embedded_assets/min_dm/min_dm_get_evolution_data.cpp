#include "embedded_assets/embedded_image.h"
#include "embedded_assets/min_dm/min_dm.hpp"
#include "embedded_assets/min_dm/min_dm_evol.hpp"
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

animation::animation_evolution_data_t get_min_dm_evolution_data(size_t i) {
  using namespace assets;
  switch (i) {
  case DM_BOTAMON_ANIM_INDEX:
    return {
      .conditions = STAGE_I_CONDITIONS,

      .num_animation_indices = 1,
      .animation_indices ={
        DM_KOROMON_ANIM_INDEX,
      },
    };
  case DM_KOROMON_ANIM_INDEX:
    return {
      .conditions = STAGE_II_CONDITIONS,

      .num_animation_indices = 2,
      .animation_indices ={
        DM_AGUMON_ANIM_INDEX,
        DM_BETAMON_ANIM_INDEX,
      },
    };
  case DM_AGUMON_ANIM_INDEX:
    return {
      .conditions = STAGE_III_CONDITIONS,

      .num_animation_indices = 5,
      .animation_indices ={
        DM_GREYMON_ANIM_INDEX,
        DM_TYRANOMON_ANIM_INDEX,
        DM_DEVIMON_ANIM_INDEX,
        DM_MERAMON_ANIM_INDEX,
        DM_NUMEMON_ANIM_INDEX,
      },
    };
  case DM_BETAMON_ANIM_INDEX:
    return {
      .conditions = STAGE_III_CONDITIONS,

      .num_animation_indices = 5,
      .animation_indices ={
        DM_DEVIMON_ANIM_INDEX,
        DM_MERAMON_ANIM_INDEX,
        DM_AIRDRAMON_ANIM_INDEX,
        DM_SEADRAMON_ANIM_INDEX,
        DM_NUMEMON_ANIM_INDEX,
      },
    };
  case DM_GREYMON_ANIM_INDEX:
    return {
      .conditions = STAGE_IV_CONDITIONS,

      .num_animation_indices = 1,
      .animation_indices ={
        DM_METAL_GREYMON_ANIM_INDEX,
      },
    };
  case DM_TYRANOMON_ANIM_INDEX:
    return {
      .conditions = STAGE_IV_CONDITIONS,

      .num_animation_indices = 1,
      .animation_indices ={
        DM_MAMEMON_ANIM_INDEX,
      },
    };
  case DM_DEVIMON_ANIM_INDEX:
    return {
      .conditions = STAGE_IV_CONDITIONS,

      .num_animation_indices = 1,
      .animation_indices ={
        DM_METAL_GREYMON_ANIM_INDEX,
      },
    };
  case DM_MERAMON_ANIM_INDEX:
    return {
      .conditions = STAGE_IV_CONDITIONS,

      .num_animation_indices = 1,
      .animation_indices ={
        DM_MAMEMON_ANIM_INDEX,
      },
    };
  case DM_AIRDRAMON_ANIM_INDEX:
    return {
      .conditions = STAGE_IV_CONDITIONS,

      .num_animation_indices = 1,
      .animation_indices ={
        DM_METAL_GREYMON_ANIM_INDEX,
      },
    };
  case DM_SEADRAMON_ANIM_INDEX:
    return {
      .conditions = STAGE_IV_CONDITIONS,

      .num_animation_indices = 1,
      .animation_indices ={
        DM_METAL_GREYMON_ANIM_INDEX,
      },
    };
  case DM_NUMEMON_ANIM_INDEX:
    return {
      .conditions = STAGE_IV_CONDITIONS,

      .num_animation_indices = 1,
      .animation_indices ={
        DM_MONZAEMON_ANIM_INDEX,
      },
    };
  case DM_METAL_GREYMON_ANIM_INDEX:
  case DM_MAMEMON_ANIM_INDEX:
  case DM_MONZAEMON_ANIM_INDEX:
  default:
    return {};
  }
  return {};
}
}  // namespace bongocat::assets