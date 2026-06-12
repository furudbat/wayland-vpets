#include "embedded_assets/embedded_image.h"
#include "embedded_assets/dm20/dm20.hpp"
#include "embedded_assets/dm20/dm20_evol.hpp"
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
inline static constexpr animation::animation_evolution_conditions_t STAGE_VI_JOGRESS_CONDITIONS = {
  .next_evolution_time_sec = 64 * (60 * 60),  // Jogress replaced by 64h
};

animation::animation_evolution_data_t get_dm20_evolution_data(size_t i) {
  using namespace assets;
  switch (i) {
  case DM20_BOTAMON_ANIM_INDEX:
    return {
      .conditions = STAGE_I_CONDITIONS,

      .num_animation_indices = 1,
      .animation_indices ={
        DM20_KOROMON_ANIM_INDEX,
      },
    };
  case DM20_KOROMON_ANIM_INDEX:
    return {
      .conditions = STAGE_II_CONDITIONS,

      .num_animation_indices = 2,
      .animation_indices ={
        DM20_AGUMON_ANIM_INDEX,
        DM20_BETAMON_ANIM_INDEX,
      },
    };
  case DM20_AGUMON_ANIM_INDEX:
    return {
      .conditions = STAGE_III_CONDITIONS,

      .num_animation_indices = 5,
      .animation_indices ={
        DM20_GREYMON_ANIM_INDEX,
        DM20_TYRANOMON_ANIM_INDEX,
        DM20_DEVIMON_ANIM_INDEX,
        DM20_MERAMON_ANIM_INDEX,
        DM20_NUMEMON_ANIM_INDEX,
      },
    };
  case DM20_BETAMON_ANIM_INDEX:
    return {
      .conditions = STAGE_III_CONDITIONS,

      .num_animation_indices = 5,
      .animation_indices ={
        DM20_DEVIMON_ANIM_INDEX,
        DM20_MERAMON_ANIM_INDEX,
        DM20_AIRDRAMON_ANIM_INDEX,
        DM20_SEADRAMON_ANIM_INDEX,
        DM20_NUMEMON_ANIM_INDEX,
      },
    };
  case DM20_GREYMON_ANIM_INDEX:
    return {
      .conditions = STAGE_IV_CONDITIONS,

      .num_animation_indices = 1,
      .animation_indices ={
        DM20_METAL_GREYMON_ANIM_INDEX,
      },
    };
  case DM20_TYRANOMON_ANIM_INDEX:
    return {
      .conditions = STAGE_IV_CONDITIONS,

      .num_animation_indices = 1,
      .animation_indices ={
        DM20_MAMEMON_ANIM_INDEX,
      },
    };
  case DM20_DEVIMON_ANIM_INDEX:
    return {
      .conditions = STAGE_IV_CONDITIONS,

      .num_animation_indices = 1,
      .animation_indices ={
        DM20_METAL_GREYMON_ANIM_INDEX,
      },
    };
  case DM20_MERAMON_ANIM_INDEX:
    return {
      .conditions = STAGE_IV_CONDITIONS,

      .num_animation_indices = 1,
      .animation_indices ={
        DM20_MAMEMON_ANIM_INDEX,
      },
    };
  case DM20_AIRDRAMON_ANIM_INDEX:
    return {
      .conditions = STAGE_IV_CONDITIONS,

      .num_animation_indices = 1,
      .animation_indices ={
        DM20_METAL_GREYMON_ANIM_INDEX,
      },
    };
  case DM20_SEADRAMON_ANIM_INDEX:
    return {
      .conditions = STAGE_IV_CONDITIONS,

      .num_animation_indices = 1,
      .animation_indices ={
        DM20_METAL_GREYMON_ANIM_INDEX,
      },
    };
  case DM20_NUMEMON_ANIM_INDEX:
    return {
      .conditions = STAGE_IV_CONDITIONS,

      .num_animation_indices = 1,
      .animation_indices ={
        DM20_MONZAEMON_ANIM_INDEX,
      },
    };
  case DM20_METAL_GREYMON_ANIM_INDEX:
    return {
      .conditions = STAGE_V_CONDITIONS,

      .num_animation_indices = 1,
      .animation_indices ={
        DM20_BLITZ_GREYMON_ANIM_INDEX,
      },
    };
  case DM20_MAMEMON_ANIM_INDEX:
    return {
      .conditions = STAGE_V_CONDITIONS,

      .num_animation_indices = 1,
      .animation_indices ={
        DM20_BANCHO_MAMEMON_ANIM_INDEX,
      },
    };
  case DM20_MONZAEMON_ANIM_INDEX:
  case DM20_BLITZ_GREYMON_ANIM_INDEX:
    return {
      .conditions = STAGE_VI_JOGRESS_CONDITIONS,

      .num_animation_indices = 1,
      .animation_indices ={
        DM20_BANCHO_MAMEMON_ANIM_INDEX,
      },
    };
  case DM20_BANCHO_MAMEMON_ANIM_INDEX:
  case DM20_OMEGAMON_ALTER_S_ANIM_INDEX:
  default:
    return {};
  }
  return {};
}
}  // namespace bongocat::assets