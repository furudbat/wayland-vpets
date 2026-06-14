#include "embedded_assets/embedded_image.h"
#include "embedded_assets/dm/dm.hpp"
#include "embedded_assets/dm/dm_evol.h"
#include "graphics/animation_shared_memory.h"

namespace bongocat::assets {
    animation::animation_evolution_data_t get_dm_evolution_data(size_t index) {
        switch (index) {
            case DM_AGUMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 5,
                .animation_indices = {
                  DM_GREYMON_ANIM_INDEX ,DM_TYRANOMON_ANIM_INDEX ,DM_DEVIMON_ANIM_INDEX ,DM_MERAMON_ANIM_INDEX ,DM_NUMEMON_ANIM_INDEX
                },
              };
            case DM_AIRDRAMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DM_METAL_GREYMON_ANIM_INDEX
                },
              };
            case DM_ANDROMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DM_ANGEMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DM_SKULL_GREYMON_ANIM_INDEX
                },
              };
            case DM_BAKEMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DM_GIROMON_ANIM_INDEX
                },
              };
            case DM_BETAMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 5,
                .animation_indices = {
                  DM_DEVIMON_ANIM_INDEX ,DM_MERAMON_ANIM_INDEX ,DM_AIRDRAMON_ANIM_INDEX ,DM_SEADRAMON_ANIM_INDEX ,DM_NUMEMON_ANIM_INDEX
                },
              };
            case DM_BIRDRAMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DM_SKULL_GREYMON_ANIM_INDEX
                },
              };
            case DM_BOTAMON_ANIM_INDEX:
              return {
                // Stage: Baby I
                .conditions = { .next_evolution_time_sec = 600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DM_KOROMON_ANIM_INDEX
                },
              };
            case DM_CENTALMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DM_GIROMON_ANIM_INDEX
                },
              };
            case DM_COCKATRIMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DM_PICCOLOMON_ANIM_INDEX
                },
              };
            case DM_COELAMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DM_MEGADRAMON_ANIM_INDEX
                },
              };
            case DM_CORONAMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DM_CYCLOMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DM_NANOMON_ANIM_INDEX
                },
              };
            case DM_DARK_TYRANOMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DM_METAL_TYRANOMON_ANIM_INDEX
                },
              };
            case DM_DELTAMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DM_NANOMON_ANIM_INDEX
                },
              };
            case DM_DEVIDRAMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DM_METAL_TYRANOMON_ANIM_INDEX
                },
              };
            case DM_DEVIMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DM_METAL_GREYMON_ANIM_INDEX
                },
              };
            case DM_DIGITAMAMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DM_DRIMOGEMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DM_GIROMON_ANIM_INDEX
                },
              };
            case DM_ELECMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 5,
                .animation_indices = {
                  DM_ANGEMON_ANIM_INDEX ,DM_YUKIDARUMON_ANIM_INDEX ,DM_BIRDRAMON_ANIM_INDEX ,DM_WHAMON_ANIM_INDEX ,DM_VEGIMON_ANIM_INDEX
                },
              };
            case DM_ETEMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DM_EX_TYRANOMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DM_FLYMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DM_METAL_TYRANOMON_ANIM_INDEX
                },
              };
            case DM_GABUMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 5,
                .animation_indices = {
                  DM_KABUTERIMON_ANIM_INDEX ,DM_GARURUMON_ANIM_INDEX ,DM_ANGEMON_ANIM_INDEX ,DM_YUKIDARUMON_ANIM_INDEX ,DM_VEGIMON_ANIM_INDEX
                },
              };
            case DM_GARURUMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DM_METAL_MAMEMON_ANIM_INDEX
                },
              };
            case DM_GAZIMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 5,
                .animation_indices = {
                  DM_DARK_TYRANOMON_ANIM_INDEX ,DM_CYCLOMON_ANIM_INDEX ,DM_DEVIDRAMON_ANIM_INDEX ,DM_TUSKMON_ANIM_INDEX ,DM_RAREMON_ANIM_INDEX
                },
              };
            case DM_GIROMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DM_GIZAMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 5,
                .animation_indices = {
                  DM_DEVIDRAMON_ANIM_INDEX ,DM_TUSKMON_ANIM_INDEX ,DM_FLYMON_ANIM_INDEX ,DM_DELTAMON_ANIM_INDEX ,DM_RAREMON_ANIM_INDEX
                },
              };
            case DM_GREYMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DM_METAL_GREYMON_ANIM_INDEX
                },
              };
            case DM_KABUTERIMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DM_SKULL_GREYMON_ANIM_INDEX
                },
              };
            case DM_KOROMON_ANIM_INDEX:
              return {
                // Stage: Baby II
                .conditions = { .next_evolution_time_sec = 21600 },
                
                .num_animation_indices = 2,
                .animation_indices = {
                  DM_AGUMON_ANIM_INDEX ,DM_BETAMON_ANIM_INDEX
                },
              };
            case DM_KUNEMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 5,
                .animation_indices = {
                  DM_OGREMON_ANIM_INDEX ,DM_BAKEMON_ANIM_INDEX ,DM_SHELLMON_ANIM_INDEX ,DM_DRIMOGEMON_ANIM_INDEX ,DM_SCUMON_ANIM_INDEX
                },
              };
            case DM_KUWAGAMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DM_PICCOLOMON_ANIM_INDEX
                },
              };
            case DM_LEOMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DM_MEGADRAMON_ANIM_INDEX
                },
              };
            case DM_MAMEMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DM_MEGADRAMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DM_MERAMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DM_MAMEMON_ANIM_INDEX
                },
              };
            case DM_METAL_GREYMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DM_METAL_MAMEMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DM_METAL_TYRANOMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DM_MUGENDRAMON_ANIM_INDEX
                },
              };
            case DM_MOJYAMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DM_PICCOLOMON_ANIM_INDEX
                },
              };
            case DM_MONOCHROMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DM_MEGADRAMON_ANIM_INDEX
                },
              };
            case DM_MONZAEMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DM_MUGENDRAMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DM_NANIMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DM_DIGITAMAMON_ANIM_INDEX
                },
              };
            case DM_NANOMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DM_NUMEMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DM_MONZAEMON_ANIM_INDEX
                },
              };
            case DM_OGREMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DM_ANDROMON_ANIM_INDEX
                },
              };
            case DM_PAGUMON_ANIM_INDEX:
              return {
                // Stage: Baby II
                .conditions = { .next_evolution_time_sec = 21600 },
                
                .num_animation_indices = 2,
                .animation_indices = {
                  DM_GAZIMON_ANIM_INDEX ,DM_GIZAMON_ANIM_INDEX
                },
              };
            case DM_PALMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 5,
                .animation_indices = {
                  DM_LEOMON_ANIM_INDEX ,DM_KUWAGAMON_ANIM_INDEX ,DM_COELAMON_ANIM_INDEX ,DM_MOJYAMON_ANIM_INDEX ,DM_NANIMON_ANIM_INDEX
                },
              };
            case DM_PATAMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 5,
                .animation_indices = {
                  DM_UNIMON_ANIM_INDEX ,DM_CENTALMON_ANIM_INDEX ,DM_OGREMON_ANIM_INDEX ,DM_BAKEMON_ANIM_INDEX ,DM_SCUMON_ANIM_INDEX
                },
              };
            case DM_PICCOLOMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DM_PIYOMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 5,
                .animation_indices = {
                  DM_MONOCHROMON_ANIM_INDEX ,DM_COCKATRIMON_ANIM_INDEX ,DM_LEOMON_ANIM_INDEX ,DM_KUWAGAMON_ANIM_INDEX ,DM_NANIMON_ANIM_INDEX
                },
              };
            case DM_POYOMON_ANIM_INDEX:
              return {
                // Stage: Baby I
                .conditions = { .next_evolution_time_sec = 600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DM_TOKOMON_ANIM_INDEX
                },
              };
            case DM_PUNIMON_ANIM_INDEX:
              return {
                // Stage: Baby I
                .conditions = { .next_evolution_time_sec = 600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DM_TUNOMON_ANIM_INDEX
                },
              };
            case DM_RAREMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DM_EX_TYRANOMON_ANIM_INDEX
                },
              };
            case DM_SCUMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DM_ETEMON_ANIM_INDEX
                },
              };
            case DM_SEADRAMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DM_MAMEMON_ANIM_INDEX
                },
              };
            case DM_SHELLMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DM_ANDROMON_ANIM_INDEX
                },
              };
            case DM_SKULL_GREYMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DM_TANEMON_ANIM_INDEX:
              return {
                // Stage: Baby II
                .conditions = { .next_evolution_time_sec = 21600 },
                
                .num_animation_indices = 2,
                .animation_indices = {
                  DM_PIYOMON_ANIM_INDEX ,DM_PALMON_ANIM_INDEX
                },
              };
            case DM_TOKOMON_ANIM_INDEX:
              return {
                // Stage: Baby II
                .conditions = { .next_evolution_time_sec = 21600 },
                
                .num_animation_indices = 2,
                .animation_indices = {
                  DM_PATAMON_ANIM_INDEX ,DM_KUNEMON_ANIM_INDEX
                },
              };
            case DM_TUNOMON_ANIM_INDEX:
              return {
                // Stage: Baby II
                .conditions = { .next_evolution_time_sec = 21600 },
                
                .num_animation_indices = 2,
                .animation_indices = {
                  DM_GABUMON_ANIM_INDEX ,DM_ELECMON_ANIM_INDEX
                },
              };
            case DM_TUSKMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DM_NANOMON_ANIM_INDEX
                },
              };
            case DM_TYRANOMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DM_MAMEMON_ANIM_INDEX
                },
              };
            case DM_UNIMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DM_ANDROMON_ANIM_INDEX
                },
              };
            case DM_VADEMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DM_VEGIMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DM_VADEMON_ANIM_INDEX
                },
              };
            case DM_WHAMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DM_METAL_MAMEMON_ANIM_INDEX
                },
              };
            case DM_YUKIDARUMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DM_METAL_MAMEMON_ANIM_INDEX
                },
              };
            case DM_YURAMON_ANIM_INDEX:
              return {
                // Stage: Baby I
                .conditions = { .next_evolution_time_sec = 600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DM_TANEMON_ANIM_INDEX
                },
              };
            default: return {};
        }
        return {};
    }
}

