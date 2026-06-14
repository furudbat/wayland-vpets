#include "embedded_assets/embedded_image.h"
#include "embedded_assets/dm20/dm20.hpp"
#include "embedded_assets/dm20/dm20_evol.h"
#include "graphics/animation_shared_memory.h"

namespace bongocat::assets {
    animation::animation_evolution_data_t get_dm20_evolution_data(size_t index) {
        switch (index) {
            case DM20_AEGISDRAMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DM20_RUST_TYRANOMON_ANIM_INDEX
                },
              };
            case DM20_AGUMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 5,
                .animation_indices = {
                  DM20_GREYMON_ANIM_INDEX ,DM20_TYRANOMON_ANIM_INDEX ,DM20_DEVIMON_ANIM_INDEX ,DM20_MERAMON_ANIM_INDEX ,DM20_NUMEMON_ANIM_INDEX
                },
              };
            case DM20_AIRDRAMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DM20_METAL_GREYMON_ANIM_INDEX
                },
              };
            case DM20_ALPHAMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DM20_ANDROMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DM20_HI_ANDROMON_ANIM_INDEX
                },
              };
            case DM20_ANGEMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DM20_SKULL_GREYMON_ANIM_INDEX
                },
              };
            case DM20_APOLLOMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DM20_GRACE_NOVAMON_ANIM_INDEX
                },
              };
            case DM20_BABYDMON_ANIM_INDEX:
              return {
                // Stage: Baby II
                .conditions = { .next_evolution_time_sec = 21600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DM20_DRACOMON_ANIM_INDEX
                },
              };
            case DM20_BAKEMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DM20_GIROMON_ANIM_INDEX
                },
              };
            case DM20_BANCHO_MAMEMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DM20_BAO_HACKMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DM20_SAVIOR_HACKMON_ANIM_INDEX
                },
              };
            case DM20_BETAMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 5,
                .animation_indices = {
                  DM20_DEVIMON_ANIM_INDEX ,DM20_MERAMON_ANIM_INDEX ,DM20_AIRDRAMON_ANIM_INDEX ,DM20_SEADRAMON_ANIM_INDEX ,DM20_NUMEMON_ANIM_INDEX
                },
              };
            case DM20_BIRDRAMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DM20_SKULL_GREYMON_ANIM_INDEX
                },
              };
            case DM20_BLITZ_GREYMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DM20_OMEGAMON_ALTER_S_ANIM_INDEX
                },
              };
            case DM20_BOTAMON_ANIM_INDEX:
              return {
                // Stage: Baby I
                .conditions = { .next_evolution_time_sec = 600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DM20_KOROMON_ANIM_INDEX
                },
              };
            case DM20_BREAKDRAMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DM20_EXAMON_ANIM_INDEX
                },
              };
            case DM20_CENTALMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DM20_GIROMON_ANIM_INDEX
                },
              };
            case DM20_COCKATRIMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DM20_PICCOLOMON_ANIM_INDEX
                },
              };
            case DM20_COELAMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DM20_MEGADRAMON_ANIM_INDEX
                },
              };
            case DM20_COREDRAMON_BLUE_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DM20_WINGDRAMON_ANIM_INDEX
                },
              };
            case DM20_COREDRAMON_GREEN_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DM20_GROUNDRAMON_ANIM_INDEX
                },
              };
            case DM20_CORONAMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DM20_FIRAMON_ANIM_INDEX
                },
              };
            case DM20_CRESCEMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DM20_DIANAMON_ANIM_INDEX
                },
              };
            case DM20_CRES_GARURUMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DM20_OMEGAMON_ALTER_S_ANIM_INDEX
                },
              };
            case DM20_CYCLOMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DM20_NANOMON_ANIM_INDEX
                },
              };
            case DM20_DARK_TYRANOMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DM20_METAL_TYRANOMON_ANIM_INDEX
                },
              };
            case DM20_DELTAMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DM20_NANOMON_ANIM_INDEX
                },
              };
            case DM20_DEVIDRAMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DM20_METAL_TYRANOMON_ANIM_INDEX
                },
              };
            case DM20_DEVIMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DM20_METAL_GREYMON_ANIM_INDEX
                },
              };
            case DM20_DIANAMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DM20_GRACE_NOVAMON_ANIM_INDEX
                },
              };
            case DM20_DIGITAMAMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DM20_TITAMON_ANIM_INDEX
                },
              };
            case DM20_DODOMON_ANIM_INDEX:
              return {
                // Stage: Baby I
                .conditions = { .next_evolution_time_sec = 600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DM20_DORIMON_ANIM_INDEX
                },
              };
            case DM20_DORIMON_ANIM_INDEX:
              return {
                // Stage: Baby II
                .conditions = { .next_evolution_time_sec = 21600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DM20_DORUMON_ANIM_INDEX
                },
              };
            case DM20_DORUGAMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DM20_DORUGUREMON_ANIM_INDEX
                },
              };
            case DM20_DORUGUREMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DM20_ALPHAMON_ANIM_INDEX
                },
              };
            case DM20_DORUMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DM20_DORUGAMON_ANIM_INDEX
                },
              };
            case DM20_DRACOMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 2,
                .animation_indices = {
                  DM20_COREDRAMON_BLUE_ANIM_INDEX ,DM20_COREDRAMON_GREEN_ANIM_INDEX
                },
              };
            case DM20_DRIMOGEMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DM20_GIROMON_ANIM_INDEX
                },
              };
            case DM20_DURAMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DM20_DURANDAMON_ANIM_INDEX
                },
              };
            case DM20_DURANDAMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DM20_DURANDRAMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DM20_ELECMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 5,
                .animation_indices = {
                  DM20_ANGEMON_ANIM_INDEX ,DM20_YUKIDARUMON_ANIM_INDEX ,DM20_BIRDRAMON_ANIM_INDEX ,DM20_WHAMON_ANIM_INDEX ,DM20_VEGIMON_ANIM_INDEX
                },
              };
            case DM20_ETEMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DM20_KING_ETEMON_ANIM_INDEX
                },
              };
            case DM20_EXAMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DM20_EX_TYRANOMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DM20_PINOCHIMON_ANIM_INDEX
                },
              };
            case DM20_FIRAMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DM20_FLAREMON_ANIM_INDEX
                },
              };
            case DM20_FLAREMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DM20_APOLLOMON_ANIM_INDEX
                },
              };
            case DM20_FLYMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DM20_METAL_TYRANOMON_ANIM_INDEX
                },
              };
            case DM20_GABUMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 5,
                .animation_indices = {
                  DM20_KABUTERIMON_ANIM_INDEX ,DM20_GARURUMON_ANIM_INDEX ,DM20_ANGEMON_ANIM_INDEX ,DM20_YUKIDARUMON_ANIM_INDEX ,DM20_VEGIMON_ANIM_INDEX
                },
              };
            case DM20_GARURUMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DM20_METAL_MAMEMON_ANIM_INDEX
                },
              };
            case DM20_GAZIMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 5,
                .animation_indices = {
                  DM20_DARK_TYRANOMON_ANIM_INDEX ,DM20_CYCLOMON_ANIM_INDEX ,DM20_DEVIDRAMON_ANIM_INDEX ,DM20_TUSKMON_ANIM_INDEX ,DM20_RAREMON_ANIM_INDEX
                },
              };
            case DM20_GIROMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DM20_GIZAMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 5,
                .animation_indices = {
                  DM20_DEVIDRAMON_ANIM_INDEX ,DM20_TUSKMON_ANIM_INDEX ,DM20_FLYMON_ANIM_INDEX ,DM20_DELTAMON_ANIM_INDEX ,DM20_RAREMON_ANIM_INDEX
                },
              };
            case DM20_GRACE_NOVAMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DM20_GREYMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DM20_METAL_GREYMON_ANIM_INDEX
                },
              };
            case DM20_GROUNDRAMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 2,
                .animation_indices = {
                  DM20_BREAKDRAMON_ANIM_INDEX ,DM20_YAMATOS_METAL_GARURUMON_ANIM_INDEX
                },
              };
            case DM20_HACKMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DM20_BAO_HACKMON_ANIM_INDEX
                },
              };
            case DM20_HI_ANDROMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DM20_JESMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DM20_JIJIMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DM20_KABUTERIMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DM20_SKULL_GREYMON_ANIM_INDEX
                },
              };
            case DM20_KING_ETEMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DM20_KOROMON_ANIM_INDEX:
              return {
                // Stage: Baby II
                .conditions = { .next_evolution_time_sec = 21600 },
                
                .num_animation_indices = 2,
                .animation_indices = {
                  DM20_AGUMON_ANIM_INDEX ,DM20_BETAMON_ANIM_INDEX
                },
              };
            case DM20_KUNEMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 5,
                .animation_indices = {
                  DM20_OGREMON_ANIM_INDEX ,DM20_BAKEMON_ANIM_INDEX ,DM20_SHELLMON_ANIM_INDEX ,DM20_DRIMOGEMON_ANIM_INDEX ,DM20_SCUMON_ANIM_INDEX
                },
              };
            case DM20_KUWAGAMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DM20_PICCOLOMON_ANIM_INDEX
                },
              };
            case DM20_LEKISMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DM20_CRESCEMON_ANIM_INDEX
                },
              };
            case DM20_LEOMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DM20_MEGADRAMON_ANIM_INDEX
                },
              };
            case DM20_LUNAMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DM20_LEKISMON_ANIM_INDEX
                },
              };
            case DM20_MAMEMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DM20_MEGADRAMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DM20_AEGISDRAMON_ANIM_INDEX
                },
              };
            case DM20_MEICOOMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DM20_MEICRACKMON_ANIM_INDEX
                },
              };
            case DM20_MEICRACKMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DM20_RASIELMON_ANIM_INDEX
                },
              };
            case DM20_MERAMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DM20_MAMEMON_ANIM_INDEX
                },
              };
            case DM20_METAL_GARURUMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DM20_METAL_GREYMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DM20_METAL_MAMEMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DM20_CRES_GARURUMON_ANIM_INDEX
                },
              };
            case DM20_METAL_TYRANOMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DM20_MUGENDRAMON_ANIM_INDEX
                },
              };
            case DM20_MOJYAMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DM20_PICCOLOMON_ANIM_INDEX
                },
              };
            case DM20_MONCHROMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DM20_MONOCHROMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DM20_MEGADRAMON_ANIM_INDEX
                },
              };
            case DM20_MONZAEMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DM20_MOZAEMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DM20_MUGENDRAMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DM20_RUST_TYRANOMON_ANIM_INDEX
                },
              };
            case DM20_NANIMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DM20_DIGITAMAMON_ANIM_INDEX
                },
              };
            case DM20_NANOMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DM20_NUMEMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DM20_MONZAEMON_ANIM_INDEX
                },
              };
            case DM20_NYAROMON_ANIM_INDEX:
              return {
                // Stage: Baby II
                .conditions = { .next_evolution_time_sec = 21600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DM20_PLOTMON_ANIM_INDEX
                },
              };
            case DM20_OGREMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DM20_ANDROMON_ANIM_INDEX
                },
              };
            case DM20_OMEGAMON_ALTER_S_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DM20_OMEGAMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DM20_PAGUMON_ANIM_INDEX:
              return {
                // Stage: Baby II
                .conditions = { .next_evolution_time_sec = 21600 },
                
                .num_animation_indices = 2,
                .animation_indices = {
                  DM20_GAZIMON_ANIM_INDEX ,DM20_GIZAMON_ANIM_INDEX
                },
              };
            case DM20_PAKUMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DM20_PALMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 5,
                .animation_indices = {
                  DM20_LEOMON_ANIM_INDEX ,DM20_KUWAGAMON_ANIM_INDEX ,DM20_COELAMON_ANIM_INDEX ,DM20_MOJYAMON_ANIM_INDEX ,DM20_NANIMON_ANIM_INDEX
                },
              };
            case DM20_PATAMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 5,
                .animation_indices = {
                  DM20_UNIMON_ANIM_INDEX ,DM20_CENTALMON_ANIM_INDEX ,DM20_OGREMON_ANIM_INDEX ,DM20_BAKEMON_ANIM_INDEX ,DM20_SCUMON_ANIM_INDEX
                },
              };
            case DM20_PETITMON_ANIM_INDEX:
              return {
                // Stage: Baby I
                .conditions = { .next_evolution_time_sec = 600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DM20_BABYDMON_ANIM_INDEX
                },
              };
            case DM20_PICCOLOMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DM20_PINOCHIMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DM20_PITCHMON_ANIM_INDEX:
              return {
                // Stage: Baby I
                .conditions = { .next_evolution_time_sec = 600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DM20_PUKAMON_ANIM_INDEX
                },
              };
            case DM20_PIYOMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 5,
                .animation_indices = {
                  DM20_MONOCHROMON_ANIM_INDEX ,DM20_COCKATRIMON_ANIM_INDEX ,DM20_LEOMON_ANIM_INDEX ,DM20_KUWAGAMON_ANIM_INDEX ,DM20_NANIMON_ANIM_INDEX
                },
              };
            case DM20_PLOTMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DM20_MEICOOMON_ANIM_INDEX
                },
              };
            case DM20_POYOMON_ANIM_INDEX:
              return {
                // Stage: Baby I
                .conditions = { .next_evolution_time_sec = 600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DM20_TOKOMON_ANIM_INDEX
                },
              };
            case DM20_PUKAMON_ANIM_INDEX:
              return {
                // Stage: Baby II
                .conditions = { .next_evolution_time_sec = 21600 },
                
                .num_animation_indices = 2,
                .animation_indices = {
                  DM20_CORONAMON_ANIM_INDEX ,DM20_LUNAMON_ANIM_INDEX
                },
              };
            case DM20_PUNIMON_ANIM_INDEX:
              return {
                // Stage: Baby I
                .conditions = { .next_evolution_time_sec = 600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DM20_TUNOMON_ANIM_INDEX
                },
              };
            case DM20_RAREMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DM20_EX_TYRANOMON_ANIM_INDEX
                },
              };
            case DM20_RASIELMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DM20_RUST_TYRANOMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DM20_SAKUMON_ANIM_INDEX:
              return {
                // Stage: Baby I
                .conditions = { .next_evolution_time_sec = 600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DM20_SAKUTTOMON_ANIM_INDEX
                },
              };
            case DM20_SAKUTTOMON_ANIM_INDEX:
              return {
                // Stage: Baby II
                .conditions = { .next_evolution_time_sec = 21600 },
                
                .num_animation_indices = 2,
                .animation_indices = {
                  DM20_ZUBAMON_ANIM_INDEX ,DM20_HACKMON_ANIM_INDEX
                },
              };
            case DM20_SAVIOR_HACKMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DM20_JESMON_ANIM_INDEX
                },
              };
            case DM20_SCUMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DM20_ETEMON_ANIM_INDEX
                },
              };
            case DM20_SEADRAMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DM20_MAMEMON_ANIM_INDEX
                },
              };
            case DM20_SHELLMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DM20_ANDROMON_ANIM_INDEX
                },
              };
            case DM20_SKULL_GREYMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DM20_SKULL_MAMMON_ANIM_INDEX
                },
              };
            case DM20_SKULL_MAMMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DM20_SLAYERDRAMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DM20_EXAMON_ANIM_INDEX
                },
              };
            case DM20_TAICHI_METAL_GREYMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DM20_TAICHIS_AGUMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DM20_TAICHIS_GREYMON_ANIM_INDEX
                },
              };
            case DM20_TAICHIS_GREYMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DM20_TAICHIS_METAL_GREYMON_ANIM_INDEX
                },
              };
            case DM20_TAICHIS_METAL_GREYMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DM20_TAICHIS_WAR_GREYMON_ANIM_INDEX
                },
              };
            case DM20_TAICHIS_WAR_GREYMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DM20_OMEGAMON_ANIM_INDEX
                },
              };
            case DM20_TANEMON_ANIM_INDEX:
              return {
                // Stage: Baby II
                .conditions = { .next_evolution_time_sec = 21600 },
                
                .num_animation_indices = 2,
                .animation_indices = {
                  DM20_PIYOMON_ANIM_INDEX ,DM20_PALMON_ANIM_INDEX
                },
              };
            case DM20_TITAMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DM20_TOKOMON_ANIM_INDEX:
              return {
                // Stage: Baby II
                .conditions = { .next_evolution_time_sec = 21600 },
                
                .num_animation_indices = 2,
                .animation_indices = {
                  DM20_PATAMON_ANIM_INDEX ,DM20_KUNEMON_ANIM_INDEX
                },
              };
            case DM20_TSUNOMON_ANIM_INDEX:
              return {
                // Stage: Baby II
                .conditions = { .next_evolution_time_sec = 21600 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DM20_TUNOMON_ANIM_INDEX:
              return {
                // Stage: Baby II
                .conditions = { .next_evolution_time_sec = 21600 },
                
                .num_animation_indices = 2,
                .animation_indices = {
                  DM20_GABUMON_ANIM_INDEX ,DM20_ELECMON_ANIM_INDEX
                },
              };
            case DM20_TUSKMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DM20_NANOMON_ANIM_INDEX
                },
              };
            case DM20_TYRANOMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DM20_MAMEMON_ANIM_INDEX
                },
              };
            case DM20_UNIMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DM20_ANDROMON_ANIM_INDEX
                },
              };
            case DM20_VADEMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DM20_VEGIMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DM20_VADEMON_ANIM_INDEX
                },
              };
            case DM20_WAR_GREYMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DM20_WERE_GARURUMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DM20_WHAMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DM20_METAL_MAMEMON_ANIM_INDEX
                },
              };
            case DM20_WINGDRAMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 2,
                .animation_indices = {
                  DM20_SLAYERDRAMON_ANIM_INDEX ,DM20_TAICHIS_WAR_GREYMON_ANIM_INDEX
                },
              };
            case DM20_YAMATO_GABUMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DM20_YAMATOS_GABUMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DM20_YAMATOS_GARURUMON_ANIM_INDEX
                },
              };
            case DM20_YAMATOS_GARURUMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DM20_YAMATOS_WERE_GARURUMON_ANIM_INDEX
                },
              };
            case DM20_YAMATOS_METAL_GARURUMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DM20_OMEGAMON_ANIM_INDEX
                },
              };
            case DM20_YAMATOS_WERE_GARURUMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DM20_YAMATOS_METAL_GARURUMON_ANIM_INDEX
                },
              };
            case DM20_YUKIDARUMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DM20_METAL_MAMEMON_ANIM_INDEX
                },
              };
            case DM20_YUKIMI_BOTAMON_ANIM_INDEX:
              return {
                // Stage: Baby I
                .conditions = { .next_evolution_time_sec = 600 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DM20_YURAMON_ANIM_INDEX:
              return {
                // Stage: Baby I
                .conditions = { .next_evolution_time_sec = 600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DM20_TANEMON_ANIM_INDEX
                },
              };
            case DM20_ZUBAEAGERMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DM20_DURAMON_ANIM_INDEX
                },
              };
            case DM20_ZUBAMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DM20_ZUBAEAGERMON_ANIM_INDEX
                },
              };
            case DM20_ZURUMON_ANIM_INDEX:
              return {
                // Stage: Baby I
                .conditions = { .next_evolution_time_sec = 600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DM20_PAGUMON_ANIM_INDEX
                },
              };
            default: return {};
        }
        return {};
    }
}

