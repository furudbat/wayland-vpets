#include "embedded_assets/embedded_image.h"
#include "embedded_assets/dmx/dmx.hpp"
#include "embedded_assets/dmx/dmx_evol.h"
#include "graphics/animation_shared_memory.h"

namespace bongocat::assets {
    animation::animation_evolution_data_t get_dmx_evolution_data(size_t index) {
        switch (index) {
            case DMX_AGUMON_BLACK_X_ANIM_INDEX:
              return {
                // Stage: 
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 4,
                .animation_indices = {
                  DMX_DARK_TYRANOMON_X_ANIM_INDEX ,DMX_KUWAGAMON_X_ANIM_INDEX ,DMX_NUMEMON_X_ANIM_INDEX ,DMX_ALLOMON_X_ANIM_INDEX
                },
              };
            case DMX_AGUMON_X_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 2,
                .animation_indices = {
                  DMX_TYRANOMON_X_ANIM_INDEX ,DMX_DAMEMON_ANIM_INDEX
                },
              };
            case DMX_ALLOMON_X_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 115200 },
                
                .num_animation_indices = 3,
                .animation_indices = {
                  DMX_TRICERAMON_X_ANIM_INDEX ,DMX_METAL_FANTOMON_ANIM_INDEX ,DMX_MAMMON_X_ANIM_INDEX
                },
              };
            case DMX_ALPHAMON_OURYUKEN_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMX_ALPHAMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMX_ANCIENT_SPHINXMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMX_ANGEWOMON_X_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 144000 },
                
                .num_animation_indices = 11,
                .animation_indices = {
                  DMX_CHERUBIMON_VIRTUE_X_ANIM_INDEX ,DMX_GODDRAMON_X_ANIM_INDEX ,DMX_OURYUMON_ANIM_INDEX ,DMX_PLESIOMON_X_ANIM_INDEX ,DMX_GAIOUMON_ANIM_INDEX ,DMX_DINOTIGERMON_ANIM_INDEX ,DMX_HOLYDRAMON_X_ANIM_INDEX ,DMX_EBEMON_X_ANIM_INDEX ,DMX_HEXEBLAUMON_ANIM_INDEX ,DMX_METALLICDRAMON_ANIM_INDEX ,DMX_NOBLE_PUMPMON_ANIM_INDEX
                },
              };
            case DMX_ANOMALOCARIMON_X_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 144000 },
                
                .num_animation_indices = 11,
                .animation_indices = {
                  DMX_CHERUBIMON_VIRTUE_X_ANIM_INDEX ,DMX_GODDRAMON_X_ANIM_INDEX ,DMX_OURYUMON_ANIM_INDEX ,DMX_PLESIOMON_X_ANIM_INDEX ,DMX_GAIOUMON_ANIM_INDEX ,DMX_DINOTIGERMON_ANIM_INDEX ,DMX_HOLYDRAMON_X_ANIM_INDEX ,DMX_EBEMON_X_ANIM_INDEX ,DMX_HEXEBLAUMON_ANIM_INDEX ,DMX_METALLICDRAMON_ANIM_INDEX ,DMX_NOBLE_PUMPMON_ANIM_INDEX
                },
              };
            case DMX_BAGRAMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 2,
                .animation_indices = {
                  DMX_DARKNESS_BAGRAMON_ANIM_INDEX ,DMX_BARBAMON_X_ANIM_INDEX
                },
              };
            case DMX_BARBAMON_X_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMX_BEEL_STARMON_X_ANIM_INDEX:
              return {
                // Stage: 
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DMX_DIABLOMON_X_ANIM_INDEX
                },
              };
            case DMX_BEELZEBUMON_X_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DMX_DIABLOMON_X_ANIM_INDEX
                },
              };
            case DMX_BELIAL_VAMDEMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DMX_DIABLOMON_X_ANIM_INDEX
                },
              };
            case DMX_BELPHEMON_X_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMX_BLACK_WARGREYMON_X_ANIM_INDEX:
              return {
                // Stage: 
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMX_CANNON_BEEMON_ANIM_INDEX:
              return {
                // Stage: 
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMX_CERBERUMON_X_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 144000 },
                
                .num_animation_indices = 5,
                .animation_indices = {
                  DMX_SAKUYAMON_X_ANIM_INDEX ,DMX_SLEIPMON_X_ANIM_INDEX ,DMX_BELIAL_VAMDEMON_ANIM_INDEX ,DMX_JESMON_X_ANIM_INDEX ,DMX_PLATINUM_NUMEMON_ANIM_INDEX
                },
              };
            case DMX_CHAOSDRAMON_X_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 3,
                .animation_indices = {
                  DMX_DEMON_X_ANIM_INDEX ,DMX_LUCEMON_X_ANIM_INDEX ,DMX_DIABLOMON_X_ANIM_INDEX
                },
              };
            case DMX_CHERUBIMON_VICE_X_ANIM_INDEX:
              return {
                // Stage: 
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 2,
                .animation_indices = {
                  DMX_BELPHEMON_X_ANIM_INDEX ,DMX_BARBAMON_X_ANIM_INDEX
                },
              };
            case DMX_CHERUBIMON_VIRTUE_X_ANIM_INDEX:
              return {
                // Stage: 
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 7,
                .animation_indices = {
                  DMX_ULFORCE_V_DRAMON_X_ANIM_INDEX ,DMX_EXAMON_X_ANIM_INDEX ,DMX_DUFTMON_X_ANIM_INDEX ,DMX_SLEIPMON_X_ANIM_INDEX ,DMX_JESMON_X_ANIM_INDEX ,DMX_OMEGAMON_X_ANIM_INDEX ,DMX_JESMON_GX_ANIM_INDEX
                },
              };
            case DMX_CHOCOMON_ANIM_INDEX:
              return {
                // Stage: Baby II
                .conditions = { .next_evolution_time_sec = 43200 },
                
                .num_animation_indices = 4,
                .animation_indices = {
                  DMX_LOPMON_X_ANIM_INDEX ,DMX_SHAKOMON_X_ANIM_INDEX ,DMX_RYUDAMON_ANIM_INDEX ,DMX_JAZAMON_ANIM_INDEX
                },
              };
            case DMX_CHO_HAKKAIMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 144000 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMX_COCOMON_ANIM_INDEX:
              return {
                // Stage: Baby I
                .conditions = { .next_evolution_time_sec = 600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DMX_CHOCOMON_ANIM_INDEX
                },
              };
            case DMX_CRANIUMMON_X_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DMX_ALPHAMON_ANIM_INDEX
                },
              };
            case DMX_CRYS_PALEDRAMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 144000 },
                
                .num_animation_indices = 12,
                .animation_indices = {
                  DMX_RAPIDMON_X_ANIM_INDEX ,DMX_JUSTIMON_X_ANIM_INDEX ,DMX_ALPHAMON_ANIM_INDEX ,DMX_HOUOUMON_X_ANIM_INDEX ,DMX_TIGER_VESPAMON_ANIM_INDEX ,DMX_GAIOUMON_ANIM_INDEX ,DMX_DINOTIGERMON_ANIM_INDEX ,DMX_HOLYDRAMON_X_ANIM_INDEX ,DMX_EBEMON_X_ANIM_INDEX ,DMX_HEXEBLAUMON_ANIM_INDEX ,DMX_METALLICDRAMON_ANIM_INDEX ,DMX_NOBLE_PUMPMON_ANIM_INDEX
                },
              };
            case DMX_CYBERDRAMON_X_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 144000 },
                
                .num_animation_indices = 12,
                .animation_indices = {
                  DMX_RAPIDMON_X_ANIM_INDEX ,DMX_JUSTIMON_X_ANIM_INDEX ,DMX_ALPHAMON_ANIM_INDEX ,DMX_HOUOUMON_X_ANIM_INDEX ,DMX_TIGER_VESPAMON_ANIM_INDEX ,DMX_GAIOUMON_ANIM_INDEX ,DMX_DINOTIGERMON_ANIM_INDEX ,DMX_HOLYDRAMON_X_ANIM_INDEX ,DMX_EBEMON_X_ANIM_INDEX ,DMX_HEXEBLAUMON_ANIM_INDEX ,DMX_METALLICDRAMON_ANIM_INDEX ,DMX_NOBLE_PUMPMON_ANIM_INDEX
                },
              };
            case DMX_DAMEMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 115200 },
                
                .num_animation_indices = 4,
                .animation_indices = {
                  DMX_CERBERUMON_X_ANIM_INDEX ,DMX_SKULL_BALUCHIMON_ANIM_INDEX ,DMX_MEGALO_GROWMON_X_ANIM_INDEX ,DMX_LILIMON_X_ANIM_INDEX
                },
              };
            case DMX_DARK_KNIGHTMON_X_ANIM_INDEX:
              return {
                // Stage: 
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 3,
                .animation_indices = {
                  DMX_LUCEMON_X_ANIM_INDEX ,DMX_DARKNESS_BAGRAMON_ANIM_INDEX ,DMX_BARBAMON_X_ANIM_INDEX
                },
              };
            case DMX_DARKNESS_BAGRAMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMX_DARK_TYRANOMON_X_ANIM_INDEX:
              return {
                // Stage: 
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 3,
                .animation_indices = {
                  DMX_METAL_GREYMON_VIRUS_X_ANIM_INDEX ,DMX_MAMMON_X_ANIM_INDEX ,DMX_TRICERAMON_X_ANIM_INDEX
                },
              };
            case DMX_DEMON_X_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMX_DIABLOMON_X_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMX_DINOREXMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 2,
                .animation_indices = {
                  DMX_LEVIAMON_X_ANIM_INDEX ,DMX_BARBAMON_X_ANIM_INDEX
                },
              };
            case DMX_DINOTIGERMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 6,
                .animation_indices = {
                  DMX_MAGNAMON_X_ANIM_INDEX ,DMX_GANKOOMON_X_ANIM_INDEX ,DMX_DYNASMON_X_ANIM_INDEX ,DMX_CRANIUMMON_X_ANIM_INDEX ,DMX_DUKEMON_X_ANIM_INDEX ,DMX_JESMON_GX_ANIM_INDEX
                },
              };
            case DMX_DORUGAMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 115200 },
                
                .num_animation_indices = 8,
                .animation_indices = {
                  DMX_DORUGUREMON_ANIM_INDEX ,DMX_CYBERDRAMON_X_ANIM_INDEX ,DMX_OMEGA_SHOUTMON_X_ANIM_INDEX ,DMX_GARUDAMON_X_ANIM_INDEX ,DMX_GRADEMON_ANIM_INDEX ,DMX_MAMEMON_X_ANIM_INDEX ,DMX_CRYS_PALEDRAMON_ANIM_INDEX ,DMX_PUMPMON_ANIM_INDEX
                },
              };
            case DMX_DORUGUREMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 144000 },
                
                .num_animation_indices = 12,
                .animation_indices = {
                  DMX_RAPIDMON_X_ANIM_INDEX ,DMX_JUSTIMON_X_ANIM_INDEX ,DMX_ALPHAMON_ANIM_INDEX ,DMX_HOUOUMON_X_ANIM_INDEX ,DMX_TIGER_VESPAMON_ANIM_INDEX ,DMX_GAIOUMON_ANIM_INDEX ,DMX_DINOTIGERMON_ANIM_INDEX ,DMX_HOLYDRAMON_X_ANIM_INDEX ,DMX_EBEMON_X_ANIM_INDEX ,DMX_HEXEBLAUMON_ANIM_INDEX ,DMX_METALLICDRAMON_ANIM_INDEX ,DMX_NOBLE_PUMPMON_ANIM_INDEX
                },
              };
            case DMX_DORUMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 6,
                .animation_indices = {
                  DMX_DORUGAMON_ANIM_INDEX ,DMX_TOGEMON_X_ANIM_INDEX ,DMX_SIESAMON_X_ANIM_INDEX ,DMX_OMEKAMON_ANIM_INDEX ,DMX_PALEDRAMON_ANIM_INDEX ,DMX_JAZARDMON_ANIM_INDEX
                },
              };
            case DMX_DRACOMON_X_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 2,
                .animation_indices = {
                  DMX_GROWMON_X_ANIM_INDEX ,DMX_DAMEMON_ANIM_INDEX
                },
              };
            case DMX_DUFTMON_X_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMX_DUKEMON_X_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMX_DUSKMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 3,
                .animation_indices = {
                  DMX_DARK_TYRANOMON_X_ANIM_INDEX ,DMX_OGREMON_X_ANIM_INDEX ,DMX_NUMEMON_X_ANIM_INDEX
                },
              };
            case DMX_DYNASMON_X_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMX_EBEMON_X_ANIM_INDEX:
              return {
                // Stage: 
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 6,
                .animation_indices = {
                  DMX_MAGNAMON_X_ANIM_INDEX ,DMX_GANKOOMON_X_ANIM_INDEX ,DMX_DYNASMON_X_ANIM_INDEX ,DMX_CRANIUMMON_X_ANIM_INDEX ,DMX_DUKEMON_X_ANIM_INDEX ,DMX_JESMON_GX_ANIM_INDEX
                },
              };
            case DMX_EXAMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMX_EXAMON_X_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMX_FILMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 115200 },
                
                .num_animation_indices = 5,
                .animation_indices = {
                  DMX_METAL_GREYMON_VIRUS_X_ANIM_INDEX ,DMX_TRICERAMON_X_ANIM_INDEX ,DMX_VAMDEMON_X_ANIM_INDEX ,DMX_MEGA_SEADRAMON_X_ANIM_INDEX ,DMX_KAISER_LEOMON_ANIM_INDEX
                },
              };
            case DMX_GABUMON_X_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 2,
                .animation_indices = {
                  DMX_RHINOMON_X_ANIM_INDEX ,DMX_DAMEMON_ANIM_INDEX
                },
              };
            case DMX_GAIOUMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 6,
                .animation_indices = {
                  DMX_MAGNAMON_X_ANIM_INDEX ,DMX_GANKOOMON_X_ANIM_INDEX ,DMX_DYNASMON_X_ANIM_INDEX ,DMX_CRANIUMMON_X_ANIM_INDEX ,DMX_DUKEMON_X_ANIM_INDEX ,DMX_JESMON_GX_ANIM_INDEX
                },
              };
            case DMX_GANKOOMON_X_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DMX_JESMON_GX_ANIM_INDEX
                },
              };
            case DMX_GARUDAMON_X_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 144000 },
                
                .num_animation_indices = 12,
                .animation_indices = {
                  DMX_RAPIDMON_X_ANIM_INDEX ,DMX_JUSTIMON_X_ANIM_INDEX ,DMX_ALPHAMON_ANIM_INDEX ,DMX_HOUOUMON_X_ANIM_INDEX ,DMX_TIGER_VESPAMON_ANIM_INDEX ,DMX_GAIOUMON_ANIM_INDEX ,DMX_DINOTIGERMON_ANIM_INDEX ,DMX_HOLYDRAMON_X_ANIM_INDEX ,DMX_EBEMON_X_ANIM_INDEX ,DMX_HEXEBLAUMON_ANIM_INDEX ,DMX_METALLICDRAMON_ANIM_INDEX ,DMX_NOBLE_PUMPMON_ANIM_INDEX
                },
              };
            case DMX_GIGA_SEADRAMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 2,
                .animation_indices = {
                  DMX_LEVIAMON_X_ANIM_INDEX ,DMX_BARBAMON_X_ANIM_INDEX
                },
              };
            case DMX_GINRYUMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 115200 },
                
                .num_animation_indices = 9,
                .animation_indices = {
                  DMX_HISYARYUMON_ANIM_INDEX ,DMX_RIZE_GREYMON_X_ANIM_INDEX ,DMX_MONZAEMON_X_ANIM_INDEX ,DMX_ANGEWOMON_X_ANIM_INDEX ,DMX_ANOMALOCARIMON_X_ANIM_INDEX ,DMX_GRADEMON_ANIM_INDEX ,DMX_MAMEMON_X_ANIM_INDEX ,DMX_CRYS_PALEDRAMON_ANIM_INDEX ,DMX_PUMPMON_ANIM_INDEX
                },
              };
            case DMX_GODDRAMON_X_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 7,
                .animation_indices = {
                  DMX_ULFORCE_V_DRAMON_X_ANIM_INDEX ,DMX_EXAMON_X_ANIM_INDEX ,DMX_DUFTMON_X_ANIM_INDEX ,DMX_SLEIPMON_X_ANIM_INDEX ,DMX_JESMON_X_ANIM_INDEX ,DMX_OMEGAMON_X_ANIM_INDEX ,DMX_JESMON_GX_ANIM_INDEX
                },
              };
            case DMX_GOMAMON_X_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 3,
                .animation_indices = {
                  DMX_MANTARAYMON_X_ANIM_INDEX ,DMX_KUWAGAMON_X_ANIM_INDEX ,DMX_ALLOMON_X_ANIM_INDEX
                },
              };
            case DMX_GRADEMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 144000 },
                
                .num_animation_indices = 12,
                .animation_indices = {
                  DMX_RAPIDMON_X_ANIM_INDEX ,DMX_JUSTIMON_X_ANIM_INDEX ,DMX_ALPHAMON_ANIM_INDEX ,DMX_HOUOUMON_X_ANIM_INDEX ,DMX_TIGER_VESPAMON_ANIM_INDEX ,DMX_GAIOUMON_ANIM_INDEX ,DMX_DINOTIGERMON_ANIM_INDEX ,DMX_HOLYDRAMON_X_ANIM_INDEX ,DMX_EBEMON_X_ANIM_INDEX ,DMX_HEXEBLAUMON_ANIM_INDEX ,DMX_METALLICDRAMON_ANIM_INDEX ,DMX_NOBLE_PUMPMON_ANIM_INDEX
                },
              };
            case DMX_GRAND_DARCUMON_ANIM_INDEX:
              return {
                // Stage: 
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMX_GRANDIS_KUWAGAMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 2,
                .animation_indices = {
                  DMX_LEVIAMON_X_ANIM_INDEX ,DMX_BARBAMON_X_ANIM_INDEX
                },
              };
            case DMX_GROWMON_X_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 115200 },
                
                .num_animation_indices = 3,
                .animation_indices = {
                  DMX_MEGALO_GROWMON_X_ANIM_INDEX ,DMX_METAL_TYRANOMON_X_ANIM_INDEX ,DMX_YATAGARAMON_ANIM_INDEX
                },
              };
            case DMX_GUMMYMON_ANIM_INDEX:
              return {
                // Stage: Baby II
                .conditions = { .next_evolution_time_sec = 43200 },
                
                .num_animation_indices = 3,
                .animation_indices = {
                  DMX_PALMON_X_ANIM_INDEX ,DMX_DORUMON_ANIM_INDEX ,DMX_JAZAMON_ANIM_INDEX
                },
              };
            case DMX_HERISSMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 2,
                .animation_indices = {
                  DMX_TYRANOMON_X_ANIM_INDEX ,DMX_DAMEMON_ANIM_INDEX
                },
              };
            case DMX_HEXEBLAUMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 6,
                .animation_indices = {
                  DMX_MAGNAMON_X_ANIM_INDEX ,DMX_GANKOOMON_X_ANIM_INDEX ,DMX_DYNASMON_X_ANIM_INDEX ,DMX_CRANIUMMON_X_ANIM_INDEX ,DMX_DUKEMON_X_ANIM_INDEX ,DMX_JESMON_GX_ANIM_INDEX
                },
              };
            case DMX_HISYARYUMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 144000 },
                
                .num_animation_indices = 11,
                .animation_indices = {
                  DMX_CHERUBIMON_VIRTUE_X_ANIM_INDEX ,DMX_GODDRAMON_X_ANIM_INDEX ,DMX_OURYUMON_ANIM_INDEX ,DMX_PLESIOMON_X_ANIM_INDEX ,DMX_GAIOUMON_ANIM_INDEX ,DMX_DINOTIGERMON_ANIM_INDEX ,DMX_HOLYDRAMON_X_ANIM_INDEX ,DMX_EBEMON_X_ANIM_INDEX ,DMX_HEXEBLAUMON_ANIM_INDEX ,DMX_METALLICDRAMON_ANIM_INDEX ,DMX_NOBLE_PUMPMON_ANIM_INDEX
                },
              };
            case DMX_HOLYDRAMON_X_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 6,
                .animation_indices = {
                  DMX_MAGNAMON_X_ANIM_INDEX ,DMX_GANKOOMON_X_ANIM_INDEX ,DMX_DYNASMON_X_ANIM_INDEX ,DMX_CRANIUMMON_X_ANIM_INDEX ,DMX_DUKEMON_X_ANIM_INDEX ,DMX_JESMON_GX_ANIM_INDEX
                },
              };
            case DMX_HOUOUMON_X_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 6,
                .animation_indices = {
                  DMX_MAGNAMON_X_ANIM_INDEX ,DMX_GANKOOMON_X_ANIM_INDEX ,DMX_DYNASMON_X_ANIM_INDEX ,DMX_CRANIUMMON_X_ANIM_INDEX ,DMX_DUKEMON_X_ANIM_INDEX ,DMX_JESMON_GX_ANIM_INDEX
                },
              };
            case DMX_IMPMON_X_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 4,
                .animation_indices = {
                  DMX_OGREMON_X_ANIM_INDEX ,DMX_SEADRAMON_X_ANIM_INDEX ,DMX_NUMEMON_X_ANIM_INDEX ,DMX_ALLOMON_X_ANIM_INDEX
                },
              };
            case DMX_JARARCHIMON_ANIM_INDEX:
              return {
                // Stage: 
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMX_JAZAMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 7,
                .animation_indices = {
                  DMX_SIESAMON_X_ANIM_INDEX ,DMX_MERAMON_X_ANIM_INDEX ,DMX_DORUGAMON_ANIM_INDEX ,DMX_TOGEMON_X_ANIM_INDEX ,DMX_OMEKAMON_ANIM_INDEX ,DMX_PALEDRAMON_ANIM_INDEX ,DMX_JAZARDMON_ANIM_INDEX
                },
              };
            case DMX_JAZARDMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 115200 },
                
                .num_animation_indices = 8,
                .animation_indices = {
                  DMX_OMEGA_SHOUTMON_X_ANIM_INDEX ,DMX_CYBERDRAMON_X_ANIM_INDEX ,DMX_DORUGUREMON_ANIM_INDEX ,DMX_GARUDAMON_X_ANIM_INDEX ,DMX_GRADEMON_ANIM_INDEX ,DMX_MAMEMON_X_ANIM_INDEX ,DMX_CRYS_PALEDRAMON_ANIM_INDEX ,DMX_PUMPMON_ANIM_INDEX
                },
              };
            case DMX_JESMON_GX_ANIM_INDEX:
              return {
                // Stage: 
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMX_JESMON_X_ANIM_INDEX:
              return {
                // Stage: 
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DMX_ALPHAMON_ANIM_INDEX
                },
              };
            case DMX_JUSTIMON_X_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 6,
                .animation_indices = {
                  DMX_MAGNAMON_X_ANIM_INDEX ,DMX_GANKOOMON_X_ANIM_INDEX ,DMX_DYNASMON_X_ANIM_INDEX ,DMX_CRANIUMMON_X_ANIM_INDEX ,DMX_DUKEMON_X_ANIM_INDEX ,DMX_JESMON_GX_ANIM_INDEX
                },
              };
            case DMX_KAISER_LEOMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 144000 },
                
                .num_animation_indices = 5,
                .animation_indices = {
                  DMX_CHERUBIMON_VICE_X_ANIM_INDEX ,DMX_DINOREXMON_ANIM_INDEX ,DMX_RAIHIMON_ANIM_INDEX ,DMX_BAGRAMON_ANIM_INDEX ,DMX_BEEL_STARMON_X_ANIM_INDEX
                },
              };
            case DMX_KEEMON_ANIM_INDEX:
              return {
                // Stage: Baby I
                .conditions = { .next_evolution_time_sec = 600 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMX_KERAMON_X_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DMX_DIABLOMON_X_ANIM_INDEX
                },
              };
            case DMX_KIIMON_ANIM_INDEX:
              return {
                // Stage: 
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DMX_YAAMON_ANIM_INDEX
                },
              };
            case DMX_KOKUWAMON_X_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 4,
                .animation_indices = {
                  DMX_KUWAGAMON_X_ANIM_INDEX ,DMX_FILMON_ANIM_INDEX ,DMX_NUMEMON_X_ANIM_INDEX ,DMX_ALLOMON_X_ANIM_INDEX
                },
              };
            case DMX_KUWAGAMON_X_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 115200 },
                
                .num_animation_indices = 2,
                .animation_indices = {
                  DMX_OKUWAMON_X_ANIM_INDEX ,DMX_MAMMON_X_ANIM_INDEX
                },
              };
            case DMX_LADY_DEVIMON_X_ANIM_INDEX:
              return {
                // Stage: 
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 3,
                .animation_indices = {
                  DMX_GRANDIS_KUWAGAMON_ANIM_INDEX ,DMX_ROSEMON_X_ANIM_INDEX ,DMX_BEEL_STARMON_X_ANIM_INDEX
                },
              };
            case DMX_LEOMON_X_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 115200 },
                
                .num_animation_indices = 4,
                .animation_indices = {
                  DMX_CERBERUMON_X_ANIM_INDEX ,DMX_METAL_GREYMON_X_ANIM_INDEX ,DMX_METAL_TYRANOMON_X_ANIM_INDEX ,DMX_YATAGARAMON_ANIM_INDEX
                },
              };
            case DMX_LEVIAMON_X_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMX_LILIMON_X_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 144000 },
                
                .num_animation_indices = 4,
                .animation_indices = {
                  DMX_RAFFLESIMON_ANIM_INDEX ,DMX_BEEL_STARMON_X_ANIM_INDEX ,DMX_VALDURMON_ANIM_INDEX ,DMX_PLATINUM_NUMEMON_ANIM_INDEX
                },
              };
            case DMX_LILITHMON_X_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMX_LOPMON_X_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 8,
                .animation_indices = {
                  DMX_PEGASMON_X_ANIM_INDEX ,DMX_WIZARMON_X_ANIM_INDEX ,DMX_GINRYUMON_ANIM_INDEX ,DMX_TAILMON_X_ANIM_INDEX ,DMX_TYLOMON_X_ANIM_INDEX ,DMX_OMEKAMON_ANIM_INDEX ,DMX_PALEDRAMON_ANIM_INDEX ,DMX_JAZARDMON_ANIM_INDEX
                },
              };
            case DMX_LORD_KIGHTMON_X_ANIM_INDEX:
              return {
                // Stage: 
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMX_LUCEMON_X_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMX_MAGIDRAMON_X_ANIM_INDEX:
              return {
                // Stage: 
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMX_MAGNAMON_X_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 115200 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMX_MAMEMON_X_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 144000 },
                
                .num_animation_indices = 12,
                .animation_indices = {
                  DMX_RAPIDMON_X_ANIM_INDEX ,DMX_JUSTIMON_X_ANIM_INDEX ,DMX_ALPHAMON_ANIM_INDEX ,DMX_HOUOUMON_X_ANIM_INDEX ,DMX_TIGER_VESPAMON_ANIM_INDEX ,DMX_GAIOUMON_ANIM_INDEX ,DMX_DINOTIGERMON_ANIM_INDEX ,DMX_HOLYDRAMON_X_ANIM_INDEX ,DMX_EBEMON_X_ANIM_INDEX ,DMX_HEXEBLAUMON_ANIM_INDEX ,DMX_METALLICDRAMON_ANIM_INDEX ,DMX_NOBLE_PUMPMON_ANIM_INDEX
                },
              };
            case DMX_MAME_TYRAMON_ANIM_INDEX:
              return {
                // Stage: 
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMX_MAMMON_X_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 144000 },
                
                .num_animation_indices = 4,
                .animation_indices = {
                  DMX_GRANDIS_KUWAGAMON_ANIM_INDEX ,DMX_SKULL_MAMMON_X_ANIM_INDEX ,DMX_BEEL_STARMON_X_ANIM_INDEX ,DMX_ROSEMON_X_ANIM_INDEX
                },
              };
            case DMX_MANTARAYMON_X_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 115200 },
                
                .num_animation_indices = 2,
                .animation_indices = {
                  DMX_LADY_DEVIMON_X_ANIM_INDEX ,DMX_OKUWAMON_X_ANIM_INDEX
                },
              };
            case DMX_MEGALO_GROWMON_X_ANIM_INDEX:
              return {
                // Stage: 
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 4,
                .animation_indices = {
                  DMX_CRANIUMMON_X_ANIM_INDEX ,DMX_JESMON_X_ANIM_INDEX ,DMX_BELIAL_VAMDEMON_ANIM_INDEX ,DMX_PLATINUM_NUMEMON_ANIM_INDEX
                },
              };
            case DMX_MEGA_SEADRAMON_X_ANIM_INDEX:
              return {
                // Stage: 
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 3,
                .animation_indices = {
                  DMX_GIGA_SEADRAMON_ANIM_INDEX ,DMX_CHAOSDRAMON_X_ANIM_INDEX ,DMX_SKULL_MAMMON_X_ANIM_INDEX
                },
              };
            case DMX_MEPHISMON_X_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 144000 },
                
                .num_animation_indices = 4,
                .animation_indices = {
                  DMX_CHERUBIMON_VICE_X_ANIM_INDEX ,DMX_DINOREXMON_ANIM_INDEX ,DMX_ROSEMON_X_ANIM_INDEX ,DMX_BEEL_STARMON_X_ANIM_INDEX
                },
              };
            case DMX_MERAMON_X_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 115200 },
                
                .num_animation_indices = 8,
                .animation_indices = {
                  DMX_OMEGA_SHOUTMON_X_ANIM_INDEX ,DMX_CYBERDRAMON_X_ANIM_INDEX ,DMX_DORUGUREMON_ANIM_INDEX ,DMX_GARUDAMON_X_ANIM_INDEX ,DMX_GRADEMON_ANIM_INDEX ,DMX_MAMEMON_X_ANIM_INDEX ,DMX_CRYS_PALEDRAMON_ANIM_INDEX ,DMX_PUMPMON_ANIM_INDEX
                },
              };
            case DMX_METAL_FANTOMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 144000 },
                
                .num_animation_indices = 5,
                .animation_indices = {
                  DMX_DINOREXMON_ANIM_INDEX ,DMX_CHAOSDRAMON_X_ANIM_INDEX ,DMX_SKULL_MAMMON_X_ANIM_INDEX ,DMX_METAL_PIRANIMON_ANIM_INDEX ,DMX_DARK_KNIGHTMON_X_ANIM_INDEX
                },
              };
            case DMX_METAL_GARURUMON_X_ANIM_INDEX:
              return {
                // Stage: 
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DMX_OMEGAMON_X_ANIM_INDEX
                },
              };
            case DMX_METAL_GREYMON_VIRUS_X_ANIM_INDEX:
              return {
                // Stage: 
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 4,
                .animation_indices = {
                  DMX_SKULL_MAMMON_X_ANIM_INDEX ,DMX_PRINCE_MAMEMON_X_ANIM_INDEX ,DMX_METAL_PIRANIMON_ANIM_INDEX ,DMX_CHAOSDRAMON_X_ANIM_INDEX
                },
              };
            case DMX_METAL_GREYMON_X_ANIM_INDEX:
              return {
                // Stage: 
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 4,
                .animation_indices = {
                  DMX_WAR_GREYMON_X_ANIM_INDEX ,DMX_JESMON_X_ANIM_INDEX ,DMX_VALDURMON_ANIM_INDEX ,DMX_PLATINUM_NUMEMON_ANIM_INDEX
                },
              };
            case DMX_METALLICDRAMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 6,
                .animation_indices = {
                  DMX_MAGNAMON_X_ANIM_INDEX ,DMX_GANKOOMON_X_ANIM_INDEX ,DMX_DYNASMON_X_ANIM_INDEX ,DMX_CRANIUMMON_X_ANIM_INDEX ,DMX_DUKEMON_X_ANIM_INDEX ,DMX_JESMON_GX_ANIM_INDEX
                },
              };
            case DMX_METAL_PIRANIMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 3,
                .animation_indices = {
                  DMX_LILITHMON_X_ANIM_INDEX ,DMX_BELPHEMON_X_ANIM_INDEX ,DMX_BARBAMON_X_ANIM_INDEX
                },
              };
            case DMX_METAL_TYRANOMON_X_ANIM_INDEX:
              return {
                // Stage: 
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 7,
                .animation_indices = {
                  DMX_BEELZEBUMON_X_ANIM_INDEX ,DMX_WAR_GREYMON_X_ANIM_INDEX ,DMX_SLEIPMON_X_ANIM_INDEX ,DMX_METAL_GARURUMON_X_ANIM_INDEX ,DMX_CRANIUMMON_X_ANIM_INDEX ,DMX_BELIAL_VAMDEMON_ANIM_INDEX ,DMX_PLATINUM_NUMEMON_ANIM_INDEX
                },
              };
            case DMX_MINERVAMON_X_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMX_MONZAEMON_X_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 144000 },
                
                .num_animation_indices = 11,
                .animation_indices = {
                  DMX_CHERUBIMON_VIRTUE_X_ANIM_INDEX ,DMX_GODDRAMON_X_ANIM_INDEX ,DMX_OURYUMON_ANIM_INDEX ,DMX_PLESIOMON_X_ANIM_INDEX ,DMX_GAIOUMON_ANIM_INDEX ,DMX_DINOTIGERMON_ANIM_INDEX ,DMX_HOLYDRAMON_X_ANIM_INDEX ,DMX_EBEMON_X_ANIM_INDEX ,DMX_HEXEBLAUMON_ANIM_INDEX ,DMX_METALLICDRAMON_ANIM_INDEX ,DMX_NOBLE_PUMPMON_ANIM_INDEX
                },
              };
            case DMX_NEFERTIMON_X_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 115200 },
                
                .num_animation_indices = 2,
                .animation_indices = {
                  DMX_MEPHISMON_X_ANIM_INDEX ,DMX_MEGA_SEADRAMON_X_ANIM_INDEX
                },
              };
            case DMX_NOBLE_PUMPMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMX_NUMEMON_X_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 115200 },
                
                .num_animation_indices = 9,
                .animation_indices = {
                  DMX_METAL_GREYMON_VIRUS_X_ANIM_INDEX ,DMX_OKUWAMON_X_ANIM_INDEX ,DMX_LADY_DEVIMON_X_ANIM_INDEX ,DMX_TRICERAMON_X_ANIM_INDEX ,DMX_VAMDEMON_X_ANIM_INDEX ,DMX_MEGA_SEADRAMON_X_ANIM_INDEX ,DMX_MEPHISMON_X_ANIM_INDEX ,DMX_METAL_FANTOMON_ANIM_INDEX ,DMX_KAISER_LEOMON_ANIM_INDEX
                },
              };
            case DMX_OGREMON_X_ANIM_INDEX:
              return {
                // Stage: 
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 3,
                .animation_indices = {
                  DMX_VAMDEMON_X_ANIM_INDEX ,DMX_MAMMON_X_ANIM_INDEX ,DMX_METAL_FANTOMON_ANIM_INDEX
                },
              };
            case DMX_OGUDOMON_X_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMX_OKUWAMON_X_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 144000 },
                
                .num_animation_indices = 4,
                .animation_indices = {
                  DMX_GRANDIS_KUWAGAMON_ANIM_INDEX ,DMX_ROSEMON_X_ANIM_INDEX ,DMX_BEEL_STARMON_X_ANIM_INDEX ,DMX_SKULL_MAMMON_X_ANIM_INDEX
                },
              };
            case DMX_OMEGAMON_X_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMX_OMEGA_SHOUTMON_X_ANIM_INDEX:
              return {
                // Stage: 
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 12,
                .animation_indices = {
                  DMX_RAPIDMON_X_ANIM_INDEX ,DMX_JUSTIMON_X_ANIM_INDEX ,DMX_ALPHAMON_ANIM_INDEX ,DMX_HOUOUMON_X_ANIM_INDEX ,DMX_TIGER_VESPAMON_ANIM_INDEX ,DMX_GAIOUMON_ANIM_INDEX ,DMX_DINOTIGERMON_ANIM_INDEX ,DMX_HOLYDRAMON_X_ANIM_INDEX ,DMX_EBEMON_X_ANIM_INDEX ,DMX_HEXEBLAUMON_ANIM_INDEX ,DMX_METALLICDRAMON_ANIM_INDEX ,DMX_NOBLE_PUMPMON_ANIM_INDEX
                },
              };
            case DMX_OMEKAMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 115200 },
                
                .num_animation_indices = 8,
                .animation_indices = {
                  DMX_OMEGA_SHOUTMON_X_ANIM_INDEX ,DMX_CYBERDRAMON_X_ANIM_INDEX ,DMX_DORUGUREMON_ANIM_INDEX ,DMX_GARUDAMON_X_ANIM_INDEX ,DMX_GRADEMON_ANIM_INDEX ,DMX_MAMEMON_X_ANIM_INDEX ,DMX_CRYS_PALEDRAMON_ANIM_INDEX ,DMX_PUMPMON_ANIM_INDEX
                },
              };
            case DMX_OPHANIMON_FALLDOWN_MODE_ANIM_INDEX:
              return {
                // Stage: 
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMX_OPHANIMON_X_ANIM_INDEX:
              return {
                // Stage: 
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMX_OTAMAMON_X_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 4,
                .animation_indices = {
                  DMX_SEADRAMON_X_ANIM_INDEX ,DMX_FILMON_ANIM_INDEX ,DMX_NUMEMON_X_ANIM_INDEX ,DMX_ALLOMON_X_ANIM_INDEX
                },
              };
            case DMX_OURYUMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 7,
                .animation_indices = {
                  DMX_ULFORCE_V_DRAMON_X_ANIM_INDEX ,DMX_EXAMON_X_ANIM_INDEX ,DMX_DUFTMON_X_ANIM_INDEX ,DMX_SLEIPMON_X_ANIM_INDEX ,DMX_JESMON_X_ANIM_INDEX ,DMX_OMEGAMON_X_ANIM_INDEX ,DMX_JESMON_GX_ANIM_INDEX
                },
              };
            case DMX_PALEDRAMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 115200 },
                
                .num_animation_indices = 8,
                .animation_indices = {
                  DMX_OMEGA_SHOUTMON_X_ANIM_INDEX ,DMX_CYBERDRAMON_X_ANIM_INDEX ,DMX_DORUGUREMON_ANIM_INDEX ,DMX_GARUDAMON_X_ANIM_INDEX ,DMX_GRADEMON_ANIM_INDEX ,DMX_MAMEMON_X_ANIM_INDEX ,DMX_CRYS_PALEDRAMON_ANIM_INDEX ,DMX_PUMPMON_ANIM_INDEX
                },
              };
            case DMX_PALMON_X_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 7,
                .animation_indices = {
                  DMX_TOGEMON_X_ANIM_INDEX ,DMX_SIESAMON_X_ANIM_INDEX ,DMX_MERAMON_X_ANIM_INDEX ,DMX_DORUGAMON_ANIM_INDEX ,DMX_OMEKAMON_ANIM_INDEX ,DMX_PALEDRAMON_ANIM_INDEX ,DMX_JAZARDMON_ANIM_INDEX
                },
              };
            case DMX_PEGASMON_X_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 115200 },
                
                .num_animation_indices = 8,
                .animation_indices = {
                  DMX_RIZE_GREYMON_X_ANIM_INDEX ,DMX_MONZAEMON_X_ANIM_INDEX ,DMX_ANGEWOMON_X_ANIM_INDEX ,DMX_ANOMALOCARIMON_X_ANIM_INDEX ,DMX_GRADEMON_ANIM_INDEX ,DMX_MAMEMON_X_ANIM_INDEX ,DMX_CRYS_PALEDRAMON_ANIM_INDEX ,DMX_PUMPMON_ANIM_INDEX
                },
              };
            case DMX_PLATINUM_NUMEMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DMX_OMEGAMON_X_ANIM_INDEX
                },
              };
            case DMX_PLESIOMON_X_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 7,
                .animation_indices = {
                  DMX_ULFORCE_V_DRAMON_X_ANIM_INDEX ,DMX_EXAMON_X_ANIM_INDEX ,DMX_DUFTMON_X_ANIM_INDEX ,DMX_SLEIPMON_X_ANIM_INDEX ,DMX_JESMON_X_ANIM_INDEX ,DMX_OMEGAMON_X_ANIM_INDEX ,DMX_JESMON_GX_ANIM_INDEX
                },
              };
            case DMX_PLOTMON_X_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 3,
                .animation_indices = {
                  DMX_NEFERTIMON_X_ANIM_INDEX ,DMX_SEADRAMON_X_ANIM_INDEX ,DMX_ALLOMON_X_ANIM_INDEX
                },
              };
            case DMX_PRINCE_MAMEMON_X_ANIM_INDEX:
              return {
                // Stage: 
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 3,
                .animation_indices = {
                  DMX_DEMON_X_ANIM_INDEX ,DMX_LUCEMON_X_ANIM_INDEX ,DMX_DIABLOMON_X_ANIM_INDEX
                },
              };
            case DMX_PTERANMON_X_ANIM_INDEX:
              return {
                // Stage: 
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMX_PUMPMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 144000 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DMX_NOBLE_PUMPMON_ANIM_INDEX
                },
              };
            case DMX_PUTTIMON_ANIM_INDEX:
              return {
                // Stage: Baby I
                .conditions = { .next_evolution_time_sec = 600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DMX_TOKOMON_X_ANIM_INDEX
                },
              };
            case DMX_RAFFLESIMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DMX_MINERVAMON_X_ANIM_INDEX
                },
              };
            case DMX_RAIHIMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 144000 },
                
                .num_animation_indices = 2,
                .animation_indices = {
                  DMX_ANCIENT_SPHINXMON_ANIM_INDEX ,DMX_BEELZEBUMON_X_ANIM_INDEX
                },
              };
            case DMX_RAPIDMON_X_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 6,
                .animation_indices = {
                  DMX_MAGNAMON_X_ANIM_INDEX ,DMX_GANKOOMON_X_ANIM_INDEX ,DMX_DYNASMON_X_ANIM_INDEX ,DMX_CRANIUMMON_X_ANIM_INDEX ,DMX_DUKEMON_X_ANIM_INDEX ,DMX_JESMON_GX_ANIM_INDEX
                },
              };
            case DMX_RASENMON_FURY_MODE_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMX_RASENMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMX_REKAMON_X_ANIM_INDEX:
              return {
                // Stage: 
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMX_RHINOMON_X_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 115200 },
                
                .num_animation_indices = 3,
                .animation_indices = {
                  DMX_WERE_GARURUMON_X_ANIM_INDEX ,DMX_MEGALO_GROWMON_X_ANIM_INDEX ,DMX_YATAGARAMON_ANIM_INDEX
                },
              };
            case DMX_RIZE_GREYMON_X_ANIM_INDEX:
              return {
                // Stage: 
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 11,
                .animation_indices = {
                  DMX_CHERUBIMON_VIRTUE_X_ANIM_INDEX ,DMX_GODDRAMON_X_ANIM_INDEX ,DMX_OURYUMON_ANIM_INDEX ,DMX_PLESIOMON_X_ANIM_INDEX ,DMX_GAIOUMON_ANIM_INDEX ,DMX_DINOTIGERMON_ANIM_INDEX ,DMX_HOLYDRAMON_X_ANIM_INDEX ,DMX_EBEMON_X_ANIM_INDEX ,DMX_HEXEBLAUMON_ANIM_INDEX ,DMX_METALLICDRAMON_ANIM_INDEX ,DMX_NOBLE_PUMPMON_ANIM_INDEX
                },
              };
            case DMX_ROSEMON_X_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 3,
                .animation_indices = {
                  DMX_LILITHMON_X_ANIM_INDEX ,DMX_BELPHEMON_X_ANIM_INDEX ,DMX_BARBAMON_X_ANIM_INDEX
                },
              };
            case DMX_RYUDAMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 7,
                .animation_indices = {
                  DMX_GINRYUMON_ANIM_INDEX ,DMX_WIZARMON_X_ANIM_INDEX ,DMX_TAILMON_X_ANIM_INDEX ,DMX_TYLOMON_X_ANIM_INDEX ,DMX_OMEKAMON_ANIM_INDEX ,DMX_PALEDRAMON_ANIM_INDEX ,DMX_JAZARDMON_ANIM_INDEX
                },
              };
            case DMX_SAKUYAMON_X_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DMX_DUKEMON_X_ANIM_INDEX
                },
              };
            case DMX_SANGOUPMON_ANIM_INDEX:
              return {
                // Stage: 
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMX_SEADRAMON_X_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 115200 },
                
                .num_animation_indices = 2,
                .animation_indices = {
                  DMX_MEGA_SEADRAMON_X_ANIM_INDEX ,DMX_MAMMON_X_ANIM_INDEX
                },
              };
            case DMX_SHAKOMON_X_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 7,
                .animation_indices = {
                  DMX_WIZARMON_X_ANIM_INDEX ,DMX_GINRYUMON_ANIM_INDEX ,DMX_TAILMON_X_ANIM_INDEX ,DMX_TYLOMON_X_ANIM_INDEX ,DMX_OMEKAMON_ANIM_INDEX ,DMX_PALEDRAMON_ANIM_INDEX ,DMX_JAZARDMON_ANIM_INDEX
                },
              };
            case DMX_SIESAMON_X_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 115200 },
                
                .num_animation_indices = 8,
                .animation_indices = {
                  DMX_OMEGA_SHOUTMON_X_ANIM_INDEX ,DMX_CYBERDRAMON_X_ANIM_INDEX ,DMX_DORUGUREMON_ANIM_INDEX ,DMX_GARUDAMON_X_ANIM_INDEX ,DMX_GRADEMON_ANIM_INDEX ,DMX_MAMEMON_X_ANIM_INDEX ,DMX_CRYS_PALEDRAMON_ANIM_INDEX ,DMX_PUMPMON_ANIM_INDEX
                },
              };
            case DMX_SISTERMON_BLANC_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 2,
                .animation_indices = {
                  DMX_RHINOMON_X_ANIM_INDEX ,DMX_DAMEMON_ANIM_INDEX
                },
              };
            case DMX_SKULL_BALUCHIMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 144000 },
                
                .num_animation_indices = 4,
                .animation_indices = {
                  DMX_SAKUYAMON_X_ANIM_INDEX ,DMX_VALDURMON_ANIM_INDEX ,DMX_SLEIPMON_X_ANIM_INDEX ,DMX_PLATINUM_NUMEMON_ANIM_INDEX
                },
              };
            case DMX_SKULL_MAMMON_X_ANIM_INDEX:
              return {
                // Stage: 
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 2,
                .animation_indices = {
                  DMX_LEVIAMON_X_ANIM_INDEX ,DMX_BARBAMON_X_ANIM_INDEX
                },
              };
            case DMX_SLEIPMON_X_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 2,
                .animation_indices = {
                  DMX_MINERVAMON_X_ANIM_INDEX ,DMX_ALPHAMON_ANIM_INDEX
                },
              };
            case DMX_STIFFIMON_ANIM_INDEX:
              return {
                // Stage: 
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMX_TAILMON_X_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 115200 },
                
                .num_animation_indices = 8,
                .animation_indices = {
                  DMX_ANGEWOMON_X_ANIM_INDEX ,DMX_RIZE_GREYMON_X_ANIM_INDEX ,DMX_MONZAEMON_X_ANIM_INDEX ,DMX_ANOMALOCARIMON_X_ANIM_INDEX ,DMX_GRADEMON_ANIM_INDEX ,DMX_MAMEMON_X_ANIM_INDEX ,DMX_CRYS_PALEDRAMON_ANIM_INDEX ,DMX_PUMPMON_ANIM_INDEX
                },
              };
            case DMX_TIERRIERMON_X_ANIM_INDEX:
              return {
                // Stage: 
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMX_TIGER_VESPAMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 6,
                .animation_indices = {
                  DMX_MAGNAMON_X_ANIM_INDEX ,DMX_GANKOOMON_X_ANIM_INDEX ,DMX_DYNASMON_X_ANIM_INDEX ,DMX_CRANIUMMON_X_ANIM_INDEX ,DMX_DUKEMON_X_ANIM_INDEX ,DMX_JESMON_GX_ANIM_INDEX
                },
              };
            case DMX_TOBCATMON_ANIM_INDEX:
              return {
                // Stage: 
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMX_TOGEMON_X_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 115200 },
                
                .num_animation_indices = 8,
                .animation_indices = {
                  DMX_OMEGA_SHOUTMON_X_ANIM_INDEX ,DMX_CYBERDRAMON_X_ANIM_INDEX ,DMX_DORUGUREMON_ANIM_INDEX ,DMX_GARUDAMON_X_ANIM_INDEX ,DMX_GRADEMON_ANIM_INDEX ,DMX_MAMEMON_X_ANIM_INDEX ,DMX_CRYS_PALEDRAMON_ANIM_INDEX ,DMX_PUMPMON_ANIM_INDEX
                },
              };
            case DMX_TOKOMON_X_ANIM_INDEX:
              return {
                // Stage: Baby II
                .conditions = { .next_evolution_time_sec = 43200 },
                
                .num_animation_indices = 2,
                .animation_indices = {
                  DMX_AGUMON_X_ANIM_INDEX ,DMX_HERISSMON_ANIM_INDEX
                },
              };
            case DMX_TRICERAMON_X_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 144000 },
                
                .num_animation_indices = 4,
                .animation_indices = {
                  DMX_CHAOSDRAMON_X_ANIM_INDEX ,DMX_PRINCE_MAMEMON_X_ANIM_INDEX ,DMX_SKULL_MAMMON_X_ANIM_INDEX ,DMX_METAL_PIRANIMON_ANIM_INDEX
                },
              };
            case DMX_TYLOMON_X_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 115200 },
                
                .num_animation_indices = 8,
                .animation_indices = {
                  DMX_ANOMALOCARIMON_X_ANIM_INDEX ,DMX_RIZE_GREYMON_X_ANIM_INDEX ,DMX_MONZAEMON_X_ANIM_INDEX ,DMX_ANGEWOMON_X_ANIM_INDEX ,DMX_GRADEMON_ANIM_INDEX ,DMX_MAMEMON_X_ANIM_INDEX ,DMX_CRYS_PALEDRAMON_ANIM_INDEX ,DMX_PUMPMON_ANIM_INDEX
                },
              };
            case DMX_TYRANOMON_X_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 115200 },
                
                .num_animation_indices = 3,
                .animation_indices = {
                  DMX_METAL_GREYMON_X_ANIM_INDEX ,DMX_METAL_TYRANOMON_X_ANIM_INDEX ,DMX_YATAGARAMON_ANIM_INDEX
                },
              };
            case DMX_ULFORCE_V_DRAMON_X_ANIM_INDEX:
              return {
                // Stage: 
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMX_ULTIMATE_BRACHIMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMX_VALDURMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DMX_DUKEMON_X_ANIM_INDEX
                },
              };
            case DMX_VAMDEMON_X_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 144000 },
                
                .num_animation_indices = 5,
                .animation_indices = {
                  DMX_DARK_KNIGHTMON_X_ANIM_INDEX ,DMX_CHERUBIMON_VICE_X_ANIM_INDEX ,DMX_METAL_PIRANIMON_ANIM_INDEX ,DMX_PRINCE_MAMEMON_X_ANIM_INDEX ,DMX_CHAOSDRAMON_X_ANIM_INDEX
                },
              };
            case DMX_VELGRMAN_ANIM_INDEX:
              return {
                // Stage: 
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMX_VOLTOBAUTAMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMX_WAR_GREYMON_X_ANIM_INDEX:
              return {
                // Stage: 
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DMX_OMEGAMON_X_ANIM_INDEX
                },
              };
            case DMX_WERE_GARURUMON_X_ANIM_INDEX:
              return {
                // Stage: 
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 4,
                .animation_indices = {
                  DMX_METAL_GARURUMON_X_ANIM_INDEX ,DMX_JESMON_X_ANIM_INDEX ,DMX_VALDURMON_ANIM_INDEX ,DMX_PLATINUM_NUMEMON_ANIM_INDEX
                },
              };
            case DMX_WIZARMON_X_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 115200 },
                
                .num_animation_indices = 8,
                .animation_indices = {
                  DMX_RIZE_GREYMON_X_ANIM_INDEX ,DMX_MONZAEMON_X_ANIM_INDEX ,DMX_ANGEWOMON_X_ANIM_INDEX ,DMX_ANOMALOCARIMON_X_ANIM_INDEX ,DMX_GRADEMON_ANIM_INDEX ,DMX_MAMEMON_X_ANIM_INDEX ,DMX_CRYS_PALEDRAMON_ANIM_INDEX ,DMX_PUMPMON_ANIM_INDEX
                },
              };
            case DMX_YAAMON_ANIM_INDEX:
              return {
                // Stage: 
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 8,
                .animation_indices = {
                  DMX_GOMAMON_X_ANIM_INDEX ,DMX_KOKUWAMON_X_ANIM_INDEX ,DMX_AGUMON_BLACK_X_ANIM_INDEX ,DMX_HERISSMON_ANIM_INDEX ,DMX_DUSKMON_ANIM_INDEX ,DMX_PLOTMON_X_ANIM_INDEX ,DMX_OTAMAMON_X_ANIM_INDEX ,DMX_IMPMON_X_ANIM_INDEX
                },
              };
            case DMX_YATAGARAMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 144000 },
                
                .num_animation_indices = 5,
                .animation_indices = {
                  DMX_SAKUYAMON_X_ANIM_INDEX ,DMX_BEEL_STARMON_X_ANIM_INDEX ,DMX_VALDURMON_ANIM_INDEX ,DMX_BELIAL_VAMDEMON_ANIM_INDEX ,DMX_PLATINUM_NUMEMON_ANIM_INDEX
                },
              };
            case DMX_ZERIMON_ANIM_INDEX:
              return {
                // Stage: Baby I
                .conditions = { .next_evolution_time_sec = 600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DMX_GUMMYMON_ANIM_INDEX
                },
              };
            default: return {};
        }
        return {};
    }
}

