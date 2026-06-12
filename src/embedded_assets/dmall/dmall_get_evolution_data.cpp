#include "embedded_assets/embedded_image.h"
#include "embedded_assets/dmall/dmall.hpp"
#include "embedded_assets/dmall/dmall_evol.hpp"
#include "graphics/animation_shared_memory.h"

namespace bongocat::assets {

inline static constexpr animation::animation_evolution_conditions_t STAGE_I_CONDITIONS = {
  .next_evolution_time_sec = 10 * 60,  // 10 min
};
inline static constexpr animation::animation_evolution_conditions_t STAGE_II_CONDITIONS = {
  .next_evolution_time_sec = 12 * (60 * 60),  // 12h
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

animation::animation_evolution_data_t get_dmall_evolution_data(size_t i) {
  using namespace assets;
  switch (i) {
    /*
  case DMALL_BOTAMON_ANIM_INDEX:
    return {
      .conditions = STAGE_I_CONDITIONS,

      .num_animation_indices = 1,
      .animation_indices ={
        DMALL_KOROMON_ANIM_INDEX,
      },
    };
    */
  case DMALL_KOROMON_ANIM_INDEX:
    return {
      .conditions = STAGE_II_CONDITIONS,

      .num_animation_indices = 1,
      .animation_indices ={
        DMALL_AGUMON_ANIM_INDEX,
        //DMALL_BETAMON_ANIM_INDEX,
      },
    };
  case DMALL_AGUMON_ANIM_INDEX:
    return {
      .conditions = STAGE_III_CONDITIONS,

      .num_animation_indices = 5,
      .animation_indices ={
        DMALL_GREYMON_ANIM_INDEX,
        DMALL_TYRANOMON_ANIM_INDEX,
        DMALL_DEVIMON_ANIM_INDEX,
        DMALL_MERAMON_ANIM_INDEX,
        DMALL_NUMEMON_ANIM_INDEX,
      },
    };
  /*
  case DMALL_BETAMON_ANIM_INDEX:
    return {
      .conditions = STAGE_III_CONDITIONS,

      .num_animation_indices = 5,
      .animation_indices ={
        DMALL_DEVIMON_ANIM_INDEX,
        DMALL_MERAMON_ANIM_INDEX,
        DMALL_AIRDRAMON_ANIM_INDEX,
        DMALL_SEADRAMON_ANIM_INDEX,
        DMALL_NUMEMON_ANIM_INDEX,
      },
    };
    */
  case DMALL_GREYMON_ANIM_INDEX:
    return {
      .conditions = STAGE_IV_CONDITIONS,

      .num_animation_indices = 1,
      .animation_indices ={
        DMALL_METAL_GREYMON_ANIM_INDEX,
      },
    };
  case DMALL_TYRANOMON_ANIM_INDEX:
    return {
      .conditions = STAGE_IV_CONDITIONS,

      .num_animation_indices = 1,
      .animation_indices ={
        DMALL_MAMEMON_ANIM_INDEX,
      },
    };
  case DMALL_DEVIMON_ANIM_INDEX:
    return {
      .conditions = STAGE_IV_CONDITIONS,

      .num_animation_indices = 1,
      .animation_indices ={
        DMALL_METAL_GREYMON_ANIM_INDEX,
      },
    };
  case DMALL_MERAMON_ANIM_INDEX:
    return {
      .conditions = STAGE_IV_CONDITIONS,

      .num_animation_indices = 1,
      .animation_indices ={
        DMALL_MAMEMON_ANIM_INDEX,
      },
    };
  case DMALL_AIRDRAMON_ANIM_INDEX:
    return {
      .conditions = STAGE_IV_CONDITIONS,

      .num_animation_indices = 1,
      .animation_indices ={
        DMALL_METAL_GREYMON_ANIM_INDEX,
      },
    };
  case DMALL_SEADRAMON_ANIM_INDEX:
    return {
      .conditions = STAGE_IV_CONDITIONS,

      .num_animation_indices = 1,
      .animation_indices ={
        DMALL_METAL_GREYMON_ANIM_INDEX,
      },
    };
  case DMALL_NUMEMON_ANIM_INDEX:
    return {
      .conditions = STAGE_IV_CONDITIONS,

      .num_animation_indices = 1,
      .animation_indices ={
        DMALL_MONZAEMON_ANIM_INDEX,
      },
    };
  case DMALL_METAL_GREYMON_ANIM_INDEX:
    return {
      .conditions = STAGE_V_CONDITIONS,

      .num_animation_indices = 1,
      .animation_indices ={
        DMALL_BLITZ_GREYMON_ANIM_INDEX,
      },
    };
  case DMALL_MAMEMON_ANIM_INDEX:
    return {
      .conditions = STAGE_V_CONDITIONS,

      .num_animation_indices = 1,
      .animation_indices ={
        DMALL_BANCHO_MAMEMON_ANIM_INDEX,
      },
    };
  case DMALL_MONZAEMON_ANIM_INDEX:
  case DMALL_BLITZ_GREYMON_ANIM_INDEX:
    return {
      .conditions = STAGE_VI_JOGRESS_CONDITIONS,

      .num_animation_indices = 1,
      .animation_indices ={
        DMALL_BANCHO_MAMEMON_ANIM_INDEX,
      },
    };
  case DMALL_BANCHO_MAMEMON_ANIM_INDEX:
  case DMALL_OMEGAMON_ALTER_S_ANIM_INDEX:
  default:
    return {};
  }
  return {};
}
}  // namespace bongocat::assets