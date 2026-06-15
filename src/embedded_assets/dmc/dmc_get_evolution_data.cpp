#include "embedded_assets/embedded_image.h"
#include "embedded_assets/dmc/dmc.hpp"
#include "embedded_assets/dmc/dmc_evol.h"
#include "graphics/animation_shared_memory.h"

namespace bongocat::assets {
    animation::animation_evolution_data_t get_dmc_evolution_data(size_t index) {
        switch (index) {
            case DMC_AGUMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 5,
                .animation_indices = {
                  DMC_GREYMON_ANIM_INDEX ,DMC_TYRANOMON_ANIM_INDEX ,DMC_DEVIMON_ANIM_INDEX ,DMC_MERAMON_ANIM_INDEX ,DMC_NUMEMON_ANIM_INDEX
                },
              };
            case DMC_AIRDRAMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DMC_METAL_GREYMON_ANIM_INDEX
                },
              };
            case DMC_ANDROMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DMC_HI_ANDROMON_ANIM_INDEX
                },
              };
            case DMC_ANGEMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DMC_SKULL_GREYMON_ANIM_INDEX
                },
              };
            case DMC_BABYDMON_ANIM_INDEX:
              return {
                // Stage: Baby II
                .conditions = { .next_evolution_time_sec = 43200 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMC_BAKEMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DMC_GIROMON_ANIM_INDEX
                },
              };
            case DMC_BANCHO_LEOMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = 230400 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DMC_CHAOSMON_ANIM_INDEX
                },
              };
            case DMC_BANCHO_MAMEMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMC_BETAMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 5,
                .animation_indices = {
                  DMC_DEVIMON_ANIM_INDEX ,DMC_MERAMON_ANIM_INDEX ,DMC_AIRDRAMON_ANIM_INDEX ,DMC_SEADRAMON_ANIM_INDEX ,DMC_NUMEMON_ANIM_INDEX
                },
              };
            case DMC_BIRDRAMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DMC_SKULL_GREYMON_ANIM_INDEX
                },
              };
            case DMC_BLITZ_GREYMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = 230400 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DMC_OMEGAMON_ALTER_S_ANIM_INDEX
                },
              };
            case DMC_BLOOM_LORDMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMC_BOTAMON_ANIM_INDEX:
              return {
                // Stage: Baby I
                .conditions = { .next_evolution_time_sec = 600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DMC_KOROMON_ANIM_INDEX
                },
              };
            case DMC_CENTALMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DMC_GIROMON_ANIM_INDEX
                },
              };
            case DMC_CHAOSDRAMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMC_CHAOSMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMC_CHIMAIRAMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 2,
                .animation_indices = {
                  DMC_BANCHO_LEOMON_ANIM_INDEX ,DMC_MILLENNIUMON_ANIM_INDEX
                },
              };
            case DMC_COCKATRIMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DMC_PICCOLOMON_ANIM_INDEX
                },
              };
            case DMC_COELAMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DMC_MEGADRAMON_ANIM_INDEX
                },
              };
            case DMC_CORONAMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMC_CRES_GARURUMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = 230400 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DMC_OMEGAMON_ALTER_S_ANIM_INDEX
                },
              };
            case DMC_CYCLOMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DMC_NANOMON_ANIM_INDEX
                },
              };
            case DMC_DARKDRAMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = 230400 },
                
                .num_animation_indices = 2,
                .animation_indices = {
                  DMC_CHAOSMON_ANIM_INDEX ,DMC_CHAOSDRAMON_ANIM_INDEX
                },
              };
            case DMC_DARK_TYRANOMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DMC_METAL_TYRANOMON_ANIM_INDEX
                },
              };
            case DMC_DELTAMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DMC_NANOMON_ANIM_INDEX
                },
              };
            case DMC_DEVIDRAMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DMC_METAL_TYRANOMON_ANIM_INDEX
                },
              };
            case DMC_DEVIMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DMC_METAL_GREYMON_ANIM_INDEX
                },
              };
            case DMC_DIGITAMAMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DMC_GANKOOMON_ANIM_INDEX
                },
              };
            case DMC_DRIMOGEMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DMC_GIROMON_ANIM_INDEX
                },
              };
            case DMC_EBEMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMC_ELECMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 5,
                .animation_indices = {
                  DMC_ANGEMON_ANIM_INDEX ,DMC_YUKIDARUMON_ANIM_INDEX ,DMC_BIRDRAMON_ANIM_INDEX ,DMC_WHAMON_ANIM_INDEX ,DMC_VEGIMON_ANIM_INDEX
                },
              };
            case DMC_ETEMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DMC_BANCHO_LEOMON_ANIM_INDEX
                },
              };
            case DMC_EX_TYRANOMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DMC_GAIOUMON_ANIM_INDEX
                },
              };
            case DMC_FLYMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DMC_METAL_TYRANOMON_ANIM_INDEX
                },
              };
            case DMC_GABUMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 5,
                .animation_indices = {
                  DMC_KABUTERIMON_ANIM_INDEX ,DMC_GARURUMON_ANIM_INDEX ,DMC_ANGEMON_ANIM_INDEX ,DMC_YUKIDARUMON_ANIM_INDEX ,DMC_VEGIMON_ANIM_INDEX
                },
              };
            case DMC_GAIOUMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMC_GANKOOMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMC_GARURUMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DMC_METAL_MAMEMON_ANIM_INDEX
                },
              };
            case DMC_GAZIMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 5,
                .animation_indices = {
                  DMC_DARK_TYRANOMON_ANIM_INDEX ,DMC_CYCLOMON_ANIM_INDEX ,DMC_DEVIDRAMON_ANIM_INDEX ,DMC_TUSKMON_ANIM_INDEX ,DMC_RAREMON_ANIM_INDEX
                },
              };
            case DMC_GIROMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DMC_GOKUMON_ANIM_INDEX
                },
              };
            case DMC_GIZAMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 5,
                .animation_indices = {
                  DMC_DEVIDRAMON_ANIM_INDEX ,DMC_TUSKMON_ANIM_INDEX ,DMC_FLYMON_ANIM_INDEX ,DMC_DELTAMON_ANIM_INDEX ,DMC_RAREMON_ANIM_INDEX
                },
              };
            case DMC_GOKUMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMC_GREYMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DMC_METAL_GREYMON_ANIM_INDEX
                },
              };
            case DMC_HI_ANDROMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMC_KABUTERIMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DMC_SKULL_GREYMON_ANIM_INDEX
                },
              };
            case DMC_KOROMON_ANIM_INDEX:
              return {
                // Stage: Baby II
                .conditions = { .next_evolution_time_sec = 43200 },
                
                .num_animation_indices = 2,
                .animation_indices = {
                  DMC_AGUMON_ANIM_INDEX ,DMC_BETAMON_ANIM_INDEX
                },
              };
            case DMC_KUNEMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 5,
                .animation_indices = {
                  DMC_OGREMON_ANIM_INDEX ,DMC_BAKEMON_ANIM_INDEX ,DMC_SHELLMON_ANIM_INDEX ,DMC_DRIMOGEMON_ANIM_INDEX ,DMC_SCUMON_ANIM_INDEX
                },
              };
            case DMC_KUWAGAMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DMC_PICCOLOMON_ANIM_INDEX
                },
              };
            case DMC_LEOMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DMC_MEGADRAMON_ANIM_INDEX
                },
              };
            case DMC_MAMEMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMC_MEGADRAMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DMC_DARKDRAMON_ANIM_INDEX
                },
              };
            case DMC_MERAMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DMC_MAMEMON_ANIM_INDEX
                },
              };
            case DMC_METAL_GARURUMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMC_METAL_GREYMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMC_METAL_GREYMON_VIRUS_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DMC_BLITZ_GREYMON_ANIM_INDEX
                },
              };
            case DMC_METAL_MAMEMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DMC_CRES_GARURUMON_ANIM_INDEX
                },
              };
            case DMC_METAL_TYRANOMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DMC_MUGENDRAMON_ANIM_INDEX
                },
              };
            case DMC_MILLENNIUMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMC_MOJYAMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DMC_PICCOLOMON_ANIM_INDEX
                },
              };
            case DMC_MOJYMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMC_MONOCHROMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DMC_MEGADRAMON_ANIM_INDEX
                },
              };
            case DMC_MONZAEMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMC_MOZAEMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMC_MUGENDRAMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = 230400 },
                
                .num_animation_indices = 2,
                .animation_indices = {
                  DMC_MILLENNIUMON_ANIM_INDEX ,DMC_CHAOSDRAMON_ANIM_INDEX
                },
              };
            case DMC_NANIMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DMC_DIGITAMAMON_ANIM_INDEX
                },
              };
            case DMC_NANOMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DMC_RAIDENMON_ANIM_INDEX
                },
              };
            case DMC_NUMEMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DMC_MONZAEMON_ANIM_INDEX
                },
              };
            case DMC_OGREMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DMC_ANDROMON_ANIM_INDEX
                },
              };
            case DMC_OMEGAMON_ALTER_S_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMC_OMEGAMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMC_ORGEMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMC_PAGUMON_ANIM_INDEX:
              return {
                // Stage: Baby II
                .conditions = { .next_evolution_time_sec = 43200 },
                
                .num_animation_indices = 2,
                .animation_indices = {
                  DMC_GAZIMON_ANIM_INDEX ,DMC_GIZAMON_ANIM_INDEX
                },
              };
            case DMC_PALMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 5,
                .animation_indices = {
                  DMC_LEOMON_ANIM_INDEX ,DMC_KUWAGAMON_ANIM_INDEX ,DMC_COELAMON_ANIM_INDEX ,DMC_MOJYAMON_ANIM_INDEX ,DMC_NANIMON_ANIM_INDEX
                },
              };
            case DMC_PATAMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 5,
                .animation_indices = {
                  DMC_UNIMON_ANIM_INDEX ,DMC_CENTALMON_ANIM_INDEX ,DMC_OGREMON_ANIM_INDEX ,DMC_BAKEMON_ANIM_INDEX ,DMC_SCUMON_ANIM_INDEX
                },
              };
            case DMC_PETITMON_ANIM_INDEX:
              return {
                // Stage: Baby I
                .conditions = { .next_evolution_time_sec = 600 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMC_PICCOLOMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DMC_BLOOM_LORDMON_ANIM_INDEX
                },
              };
            case DMC_PIYOMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 5,
                .animation_indices = {
                  DMC_MONOCHROMON_ANIM_INDEX ,DMC_COCKATRIMON_ANIM_INDEX ,DMC_LEOMON_ANIM_INDEX ,DMC_KUWAGAMON_ANIM_INDEX ,DMC_NANIMON_ANIM_INDEX
                },
              };
            case DMC_POYOMON_ANIM_INDEX:
              return {
                // Stage: Baby I
                .conditions = { .next_evolution_time_sec = 600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DMC_TOKOMON_ANIM_INDEX
                },
              };
            case DMC_PUNIMON_ANIM_INDEX:
              return {
                // Stage: Baby I
                .conditions = { .next_evolution_time_sec = 600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DMC_TUNOMON_ANIM_INDEX
                },
              };
            case DMC_RAIDENMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMC_RAREMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DMC_EX_TYRANOMON_ANIM_INDEX
                },
              };
            case DMC_RUST_TYRANOMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMC_SCUMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 2,
                .animation_indices = {
                  DMC_ETEMON_ANIM_INDEX ,DMC_CHIMAIRAMON_ANIM_INDEX
                },
              };
            case DMC_SEADRAMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DMC_MAMEMON_ANIM_INDEX
                },
              };
            case DMC_SHELLMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DMC_ANDROMON_ANIM_INDEX
                },
              };
            case DMC_SHIN_MONZAEMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMC_SKULL_GREYMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DMC_SKULL_MAMMON_ANIM_INDEX
                },
              };
            case DMC_SKULL_MAMMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMC_TANEMON_ANIM_INDEX:
              return {
                // Stage: Baby II
                .conditions = { .next_evolution_time_sec = 43200 },
                
                .num_animation_indices = 2,
                .animation_indices = {
                  DMC_PIYOMON_ANIM_INDEX ,DMC_PALMON_ANIM_INDEX
                },
              };
            case DMC_TITAMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMC_TOKOMON_ANIM_INDEX:
              return {
                // Stage: Baby II
                .conditions = { .next_evolution_time_sec = 43200 },
                
                .num_animation_indices = 2,
                .animation_indices = {
                  DMC_PATAMON_ANIM_INDEX ,DMC_KUNEMON_ANIM_INDEX
                },
              };
            case DMC_TSUNOMON_ANIM_INDEX:
              return {
                // Stage: Baby II
                .conditions = { .next_evolution_time_sec = 43200 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMC_TUNOMON_ANIM_INDEX:
              return {
                // Stage: Baby II
                .conditions = { .next_evolution_time_sec = 43200 },
                
                .num_animation_indices = 2,
                .animation_indices = {
                  DMC_GABUMON_ANIM_INDEX ,DMC_ELECMON_ANIM_INDEX
                },
              };
            case DMC_TUSKMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DMC_NANOMON_ANIM_INDEX
                },
              };
            case DMC_TYRANOMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DMC_MAMEMON_ANIM_INDEX
                },
              };
            case DMC_UNIMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DMC_ANDROMON_ANIM_INDEX
                },
              };
            case DMC_VADEMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DMC_EBEMON_ANIM_INDEX
                },
              };
            case DMC_VEGIMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DMC_VADEMON_ANIM_INDEX
                },
              };
            case DMC_WAR_GREYMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMC_WERE_GARURUMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMC_WHAMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DMC_METAL_MAMEMON_ANIM_INDEX
                },
              };
            case DMC_YUKIDARUMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DMC_METAL_MAMEMON_ANIM_INDEX
                },
              };
            case DMC_YURAMON_ANIM_INDEX:
              return {
                // Stage: Baby I
                .conditions = { .next_evolution_time_sec = 600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DMC_TANEMON_ANIM_INDEX
                },
              };
            case DMC_ZURUMON_ANIM_INDEX:
              return {
                // Stage: Baby I
                .conditions = { .next_evolution_time_sec = 600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DMC_PAGUMON_ANIM_INDEX
                },
              };
            default: return {};
        }
        return {};
    }
}

