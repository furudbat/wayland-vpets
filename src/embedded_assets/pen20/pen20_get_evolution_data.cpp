#include "embedded_assets/embedded_image.h"
#include "embedded_assets/pen20/pen20.hpp"
#include "embedded_assets/pen20/pen20_evol.h"
#include "graphics/animation_shared_memory.h"

namespace bongocat::assets {
    animation::animation_evolution_data_t get_pen20_evolution_data(size_t index) {
        switch (index) {
            case PEN20_AERO_V_DRAMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PEN20_HOUOUMON_ANIM_INDEX
                },
              };
            case PEN20_AGUMON_HAKASE_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 2,
                .animation_indices = {
                  PEN20_DEVIDRAMON_ANIM_INDEX ,PEN20_COREDRAMON_GREEN_ANIM_INDEX
                },
              };
            case PEN20_ALPHAMON_OURYUKEN_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PEN20_ANDIRAMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PEN20_CHERUBIMON_ANIM_INDEX
                },
              };
            case PEN20_ANDROMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PEN20_MUGENDRAMON_ANIM_INDEX
                },
              };
            case PEN20_ANGEWOMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 3,
                .animation_indices = {
                  PEN20_HOLYDRAMON_ANIM_INDEX ,PEN20_OFANIMON_ANIM_INDEX ,PEN20_MASTEMON_ANIM_INDEX
                },
              };
            case PEN20_ANOMALOCARIMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PEN20_METAL_SEADRAMON_ANIM_INDEX
                },
              };
            case PEN20_ARRESTERDRAMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 144000 },
                
                .num_animation_indices = 2,
                .animation_indices = {
                  PEN20_RIZE_GREYMON_ANIM_INDEX ,PEN20_MEGALO_GROWMON_ANIM_INDEX
                },
              };
            case PEN20_ASTAMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PEN20_ASTRAMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PEN20_ASURAMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PEN20_WAR_GREYMON_ANIM_INDEX
                },
              };
            case PEN20_ATLUR_KABUTERIMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PEN20_HERAKLE_KABUTERIMON_ANIM_INDEX
                },
              };
            case PEN20_BAALMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PEN20_BAKEMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 144000 },
                
                .num_animation_indices = 3,
                .animation_indices = {
                  PEN20_FANTOMON_ANIM_INDEX ,PEN20_PUMPMON_ANIM_INDEX ,PEN20_LADY_DEVIMON_ANIM_INDEX
                },
              };
            case PEN20_BAKUMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 5,
                .animation_indices = {
                  PEN20_PICO_DEVIMON_ANIM_INDEX ,PEN20_HANUMON_ANIM_INDEX ,PEN20_GARURUMON_ANIM_INDEX ,PEN20_MERAMON_ANIM_INDEX ,PEN20_WIZARMON_ANIM_INDEX
                },
              };
            case PEN20_BANCHO_LEOMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = 259200 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PEN20_CHAOSMON_ANIM_INDEX
                },
              };
            case PEN20_BEELZEBUMON_BLAST_MODE_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PEN20_BEOWOLFMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PEN20_BEOWULFMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PEN20_BIG_MAMEMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PEN20_METAL_GARURUMON_ANIM_INDEX
                },
              };
            case PEN20_BIRDRAMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 144000 },
                
                .num_animation_indices = 3,
                .animation_indices = {
                  PEN20_GARUDAMON_ANIM_INDEX ,PEN20_AERO_V_DRAMON_ANIM_INDEX ,PEN20_DELUMON_ANIM_INDEX
                },
              };
            case PEN20_BLOSSOMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PEN20_GRIFFOMON_ANIM_INDEX
                },
              };
            case PEN20_BOLTMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PEN20_BREAKDRAMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = 259200 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PEN20_EXAMON_ANIM_INDEX
                },
              };
            case PEN20_BRYWELUDRAMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = 259200 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PEN20_RAGNA_LORDMON_ANIM_INDEX
                },
              };
            case PEN20_BUBBMON_ANIM_INDEX:
              return {
                // Stage: Baby I
                .conditions = { .next_evolution_time_sec = 600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PEN20_MOCHIMON_ANIM_INDEX
                },
              };
            case PEN20_BUDMON_ANIM_INDEX:
              return {
                // Stage: Baby II
                .conditions = { .next_evolution_time_sec = 43200 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PEN20_LALAMON_ANIM_INDEX
                },
              };
            case PEN20_BUSHI_AGUMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 3,
                .animation_indices = {
                  PEN20_REPPAMON_ANIM_INDEX ,PEN20_ARRESTERDRAMON_ANIM_INDEX ,PEN20_MANBOMON_ANIM_INDEX
                },
              };
            case PEN20_CANDMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 4,
                .animation_indices = {
                  PEN20_MERAMON_ANIM_INDEX ,PEN20_WIZARMON_ANIM_INDEX ,PEN20_DEVIMON_ANIM_INDEX ,PEN20_BAKEMON_ANIM_INDEX
                },
              };
            case PEN20_CAPRIMON_ANIM_INDEX:
              return {
                // Stage: Baby II
                .conditions = { .next_evolution_time_sec = 43200 },
                
                .num_animation_indices = 3,
                .animation_indices = {
                  PEN20_TOY_AGUMON_ANIM_INDEX ,PEN20_KOKUWAMON_ANIM_INDEX ,PEN20_HAGURUMON_ANIM_INDEX
                },
              };
            case PEN20_CHAOSMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PEN20_CHERUBIMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PEN20_CHIBIMON_ANIM_INDEX:
              return {
                // Stage: Baby II
                .conditions = { .next_evolution_time_sec = 43200 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PEN20_V_MON_ANIM_INDEX
                },
              };
            case PEN20_CHICOMON_ANIM_INDEX:
              return {
                // Stage: Baby I
                .conditions = { .next_evolution_time_sec = 600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PEN20_CHIBIMON_ANIM_INDEX
                },
              };
            case PEN20_CHOROMON_ANIM_INDEX:
              return {
                // Stage: Baby I
                .conditions = { .next_evolution_time_sec = 600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PEN20_CAPRIMON_ANIM_INDEX
                },
              };
            case PEN20_CLOCKMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 144000 },
                
                .num_animation_indices = 3,
                .animation_indices = {
                  PEN20_KNIGHTMON_ANIM_INDEX ,PEN20_BIG_MAMEMON_ANIM_INDEX ,PEN20_ANDROMON_ANIM_INDEX
                },
              };
            case PEN20_COCOMON_ANIM_INDEX:
              return {
                // Stage: Baby I
                .conditions = { .next_evolution_time_sec = 600 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PEN20_COELAMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 144000 },
                
                .num_animation_indices = 4,
                .animation_indices = {
                  PEN20_MEGA_SEADRAMON_ANIM_INDEX ,PEN20_ANOMALOCARIMON_ANIM_INDEX ,PEN20_WHAMON_ANIM_INDEX ,PEN20_DAGOMON_ANIM_INDEX
                },
              };
            case PEN20_COREDRAMON_BLUE_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 144000 },
                
                .num_animation_indices = 3,
                .animation_indices = {
                  PEN20_WINGDRAMON_ANIM_INDEX ,PEN20_GROUNDRAMON_ANIM_INDEX ,PEN20_MEGADRAMON_ANIM_INDEX
                },
              };
            case PEN20_COREDRAMON_GREEN_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 144000 },
                
                .num_animation_indices = 3,
                .animation_indices = {
                  PEN20_GROUNDRAMON_ANIM_INDEX ,PEN20_WINGDRAMON_ANIM_INDEX ,PEN20_MEGADRAMON_ANIM_INDEX
                },
              };
            case PEN20_COTSUCOMON_ANIM_INDEX:
              return {
                // Stage: Baby I
                .conditions = { .next_evolution_time_sec = 600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PEN20_KAKKINMON_ANIM_INDEX
                },
              };
            case PEN20_CYBERDRAMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PEN20_WAR_GREYMON_ANIM_INDEX
                },
              };
            case PEN20_DAGOMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PEN20_PUKUMON_ANIM_INDEX
                },
              };
            case PEN20_DARKDRAMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = 259200 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PEN20_CHAOSMON_ANIM_INDEX
                },
              };
            case PEN20_DARK_KNIGHTMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PEN20_DEATH_MERAMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 2,
                .animation_indices = {
                  PEN20_BOLTMON_ANIM_INDEX ,PEN20_SKULL_MAMMON_ANIM_INDEX
                },
              };
            case PEN20_DELUMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 2,
                .animation_indices = {
                  PEN20_GRIFFOMON_ANIM_INDEX ,PEN20_HOUOUMON_ANIM_INDEX
                },
              };
            case PEN20_DEVIDRAMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 144000 },
                
                .num_animation_indices = 3,
                .animation_indices = {
                  PEN20_MEGADRAMON_ANIM_INDEX ,PEN20_WINGDRAMON_ANIM_INDEX ,PEN20_GROUNDRAMON_ANIM_INDEX
                },
              };
            case PEN20_DEVIMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 144000 },
                
                .num_animation_indices = 3,
                .animation_indices = {
                  PEN20_VAMDEMON_ANIM_INDEX ,PEN20_LADY_DEVIMON_ANIM_INDEX ,PEN20_PUMPMON_ANIM_INDEX
                },
              };
            case PEN20_DOKUGUMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 144000 },
                
                .num_animation_indices = 3,
                .animation_indices = {
                  PEN20_LADY_DEVIMON_ANIM_INDEX ,PEN20_VAMDEMON_ANIM_INDEX ,PEN20_PUMPMON_ANIM_INDEX
                },
              };
            case PEN20_DORUGORAMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PEN20_DURAMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PEN20_DURANDAMON_ANIM_INDEX
                },
              };
            case PEN20_DURANDAMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = 259200 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PEN20_RAGNA_LORDMON_ANIM_INDEX
                },
              };
            case PEN20_EBIDRAMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 144000 },
                
                .num_animation_indices = 4,
                .animation_indices = {
                  PEN20_MEGA_SEADRAMON_ANIM_INDEX ,PEN20_HANGYOMON_ANIM_INDEX ,PEN20_WHAMON_ANIM_INDEX ,PEN20_DAGOMON_ANIM_INDEX
                },
              };
            case PEN20_ETEMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PEN20_BANCHO_LEOMON_ANIM_INDEX
                },
              };
            case PEN20_EXAMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PEN20_FANTOMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PEN20_PIEMON_ANIM_INDEX
                },
              };
            case PEN20_FLORAMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 4,
                .animation_indices = {
                  PEN20_KIWIMON_ANIM_INDEX ,PEN20_TOGEMON_ANIM_INDEX ,PEN20_V_DRAMON_ANIM_INDEX ,PEN20_RED_VEGIMON_ANIM_INDEX
                },
              };
            case PEN20_FUFUMON_ANIM_INDEX:
              return {
                // Stage: Baby I
                .conditions = { .next_evolution_time_sec = 600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PEN20_KYOKYOMON_ANIM_INDEX
                },
              };
            case PEN20_GALGOMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 144000 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PEN20_RAPIDMON_ANIM_INDEX
                },
              };
            case PEN20_GANIMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 5,
                .animation_indices = {
                  PEN20_RUKAMON_ANIM_INDEX ,PEN20_SEADRAMON_ANIM_INDEX ,PEN20_COELAMON_ANIM_INDEX ,PEN20_EBIDRAMON_ANIM_INDEX ,PEN20_GESOMON_ANIM_INDEX
                },
              };
            case PEN20_GARUDAMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PEN20_HOUOUMON_ANIM_INDEX
                },
              };
            case PEN20_GARURUMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 144000 },
                
                .num_animation_indices = 6,
                .animation_indices = {
                  PEN20_WERE_GARURUMON_ANIM_INDEX ,PEN20_MAMMON_ANIM_INDEX ,PEN20_WERE_GARURUMON_ANIM_INDEX ,PEN20_PUMPMON_ANIM_INDEX ,PEN20_ANGEWOMON_ANIM_INDEX ,PEN20_METAL_MAMEMON_ANIM_INDEX
                },
              };
            case PEN20_GEKOMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 144000 },
                
                .num_animation_indices = 2,
                .animation_indices = {
                  PEN20_TONOSAMA_GEKOMON_ANIM_INDEX ,PEN20_PICCOLOMON_ANIM_INDEX
                },
              };
            case PEN20_GERBEMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PEN20_PINOCHIMON_ANIM_INDEX
                },
              };
            case PEN20_GESOMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 144000 },
                
                .num_animation_indices = 3,
                .animation_indices = {
                  PEN20_MARIN_DEVIMON_ANIM_INDEX ,PEN20_DAGOMON_ANIM_INDEX ,PEN20_HANGYOMON_ANIM_INDEX
                },
              };
            case PEN20_GINRYUMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 144000 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PEN20_HISYARYUMON_ANIM_INDEX
                },
              };
            case PEN20_GOMAMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 5,
                .animation_indices = {
                  PEN20_IKKAKUMON_ANIM_INDEX ,PEN20_RUKAMON_ANIM_INDEX ,PEN20_COELAMON_ANIM_INDEX ,PEN20_EBIDRAMON_ANIM_INDEX ,PEN20_OCTMON_ANIM_INDEX
                },
              };
            case PEN20_GOTTSUMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 5,
                .animation_indices = {
                  PEN20_TORTAMON_ANIM_INDEX ,PEN20_TAILMON_ANIM_INDEX ,PEN20_MONOCHROMON_ANIM_INDEX ,PEN20_STARMON_ANIM_INDEX ,PEN20_GEKOMON_ANIM_INDEX
                },
              };
            case PEN20_GREYMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 144000 },
                
                .num_animation_indices = 5,
                .animation_indices = {
                  PEN20_METAL_GREYMON_ANIM_INDEX ,PEN20_CYBERDRAMON_ANIM_INDEX ,PEN20_BIG_MAMEMON_ANIM_INDEX ,PEN20_ASURAMON_ANIM_INDEX ,PEN20_METAL_MAMEMON_ANIM_INDEX
                },
              };
            case PEN20_GRIFFOMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PEN20_GROUNDRAMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PEN20_BREAKDRAMON_ANIM_INDEX
                },
              };
            case PEN20_GROWMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 144000 },
                
                .num_animation_indices = 3,
                .animation_indices = {
                  PEN20_MEGALO_GROWMON_ANIM_INDEX ,PEN20_RIZE_GREYMON_ANIM_INDEX ,PEN20_BEOWOLFMON_ANIM_INDEX
                },
              };
            case PEN20_GUARDROMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 144000 },
                
                .num_animation_indices = 2,
                .animation_indices = {
                  PEN20_MEGADRAMON_ANIM_INDEX ,PEN20_BIG_MAMEMON_ANIM_INDEX
                },
              };
            case PEN20_GUIMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PEN20_GUMMYMON_ANIM_INDEX:
              return {
                // Stage: Baby II
                .conditions = { .next_evolution_time_sec = 43200 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PEN20_TERRIERMON_ANIM_INDEX
                },
              };
            case PEN20_HAGURUMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 4,
                .animation_indices = {
                  PEN20_GUARDROMON_ANIM_INDEX ,PEN20_MECHANORIMON_ANIM_INDEX ,PEN20_GREYMON_ANIM_INDEX ,PEN20_TANKMON_ANIM_INDEX
                },
              };
            case PEN20_HANGYMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PEN20_HANGYOMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PEN20_PLESIOMON_ANIM_INDEX
                },
              };
            case PEN20_HANUMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 144000 },
                
                .num_animation_indices = 3,
                .animation_indices = {
                  PEN20_MAMMON_ANIM_INDEX ,PEN20_WERE_GARURUMON_ANIM_INDEX ,PEN20_PUMPMON_ANIM_INDEX
                },
              };
            case PEN20_HERAKLE_KABUTERIMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PEN20_HERKULE_KABUTERIMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PEN20_HISYARYUMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PEN20_OURYUMON_ANIM_INDEX
                },
              };
            case PEN20_HOLY_ANGEMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PEN20_SERAPHIMON_ANIM_INDEX
                },
              };
            case PEN20_HOLYDRAMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PEN20_HOUOUMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PEN20_IGNAMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 144000 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PEN20_IKKAKUMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 144000 },
                
                .num_animation_indices = 3,
                .animation_indices = {
                  PEN20_ZUDOMON_ANIM_INDEX ,PEN20_WHAMON_ANIM_INDEX ,PEN20_ANOMALOCARIMON_ANIM_INDEX
                },
              };
            case PEN20_IMPERIALDRAMON_FIGHTER_MODE_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = 259200 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PEN20_IMPMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 3,
                .animation_indices = {
                  PEN20_TROOPMON_ANIM_INDEX ,PEN20_SHADRAMON_ANIM_INDEX ,PEN20_PORCUPAMON_ANIM_INDEX
                },
              };
            case PEN20_JESMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = 259200 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PEN20_JESMON_X_ANIM_INDEX
                },
              };
            case PEN20_JESMON_X_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PEN20_JYAGAMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PEN20_HOLYDRAMON_ANIM_INDEX
                },
              };
            case PEN20_JYUREIMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PEN20_PINOCHIMON_ANIM_INDEX
                },
              };
            case PEN20_KABUTERIMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 144000 },
                
                .num_animation_indices = 4,
                .animation_indices = {
                  PEN20_ATLUR_KABUTERIMON_ANIM_INDEX ,PEN20_JYAGAMON_ANIM_INDEX ,PEN20_ANGEWOMON_ANIM_INDEX ,PEN20_PICCOLOMON_ANIM_INDEX
                },
              };
            case PEN20_KAKKINMON_ANIM_INDEX:
              return {
                // Stage: Baby II
                .conditions = { .next_evolution_time_sec = 43200 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PEN20_LUDOMON_ANIM_INDEX
                },
              };
            case PEN20_KIWIMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 144000 },
                
                .num_animation_indices = 4,
                .animation_indices = {
                  PEN20_BLOSSOMON_ANIM_INDEX ,PEN20_DELUMON_ANIM_INDEX ,PEN20_GARUDAMON_ANIM_INDEX ,PEN20_GERBEMON_ANIM_INDEX
                },
              };
            case PEN20_KNIGHTMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 2,
                .animation_indices = {
                  PEN20_WAR_GREYMON_ANIM_INDEX ,PEN20_METAL_GARURUMON_ANIM_INDEX
                },
              };
            case PEN20_KOKUWAMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 4,
                .animation_indices = {
                  PEN20_CLOCKMON_ANIM_INDEX ,PEN20_THUNDERBALLMON_ANIM_INDEX ,PEN20_REVOLMON_ANIM_INDEX ,PEN20_GUARDROMON_ANIM_INDEX
                },
              };
            case PEN20_KUWAGAMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 144000 },
                
                .num_animation_indices = 3,
                .animation_indices = {
                  PEN20_OKUWAMON_ANIM_INDEX ,PEN20_TONOSAMA_GEKOMON_ANIM_INDEX ,PEN20_PICCOLOMON_ANIM_INDEX
                },
              };
            case PEN20_KYOKYOMON_ANIM_INDEX:
              return {
                // Stage: Baby II
                .conditions = { .next_evolution_time_sec = 43200 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PEN20_RYUDAMON_ANIM_INDEX
                },
              };
            case PEN20_LADY_DEVIMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PEN20_MASTEMON_ANIM_INDEX
                },
              };
            case PEN20_LALAMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PEN20_SUNFLOWMON_ANIM_INDEX
                },
              };
            case PEN20_LAVOGARITAMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PEN20_VOLCANICDRAMON_ANIM_INDEX
                },
              };
            case PEN20_LAVORVOMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 144000 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PEN20_LAVOGARITAMON_ANIM_INDEX
                },
              };
            case PEN20_LILAMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PEN20_LOTUSMON_ANIM_INDEX
                },
              };
            case PEN20_LILIMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PEN20_ROSEMON_ANIM_INDEX
                },
              };
            case PEN20_LOPMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PEN20_TURUIEMON_ANIM_INDEX
                },
              };
            case PEN20_LOTUSMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = 259200 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PEN20_RAFFLESIMON_ANIM_INDEX
                },
              };
            case PEN20_LUDOMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PEN20_TIA_LUDOMON_ANIM_INDEX
                },
              };
            case PEN20_MAD_LEOMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 144000 },
                
                .num_animation_indices = 2,
                .animation_indices = {
                  PEN20_BAALMON_ANIM_INDEX ,PEN20_ASTAMON_ANIM_INDEX
                },
              };
            case PEN20_MAMBOMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 144000 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PEN20_MAMMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PEN20_SKULL_MAMMON_ANIM_INDEX
                },
              };
            case PEN20_MANBOMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 144000 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PEN20_RIZE_GREYMON_ANIM_INDEX
                },
              };
            case PEN20_MARIN_ANGEMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PEN20_MARIN_DEVIMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PEN20_PUKUMON_ANIM_INDEX
                },
              };
            case PEN20_MASTEMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PEN20_MECHANORIMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 144000 },
                
                .num_animation_indices = 2,
                .animation_indices = {
                  PEN20_MEGADRAMON_ANIM_INDEX ,PEN20_BIG_MAMEMON_ANIM_INDEX
                },
              };
            case PEN20_MEGADRAMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 2,
                .animation_indices = {
                  PEN20_MUGENDRAMON_ANIM_INDEX ,PEN20_DARKDRAMON_ANIM_INDEX
                },
              };
            case PEN20_MEGALO_GROWMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PEN20_MEGA_SEADRAMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 2,
                .animation_indices = {
                  PEN20_MARIN_ANGEMON_ANIM_INDEX ,PEN20_METAL_SEADRAMON_ANIM_INDEX
                },
              };
            case PEN20_MEICRACKMON_VICIOUS_MODE_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PEN20_RAGUELMON_ANIM_INDEX
                },
              };
            case PEN20_MERAMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 144000 },
                
                .num_animation_indices = 4,
                .animation_indices = {
                  PEN20_DEATH_MERAMON_ANIM_INDEX ,PEN20_PUMPMON_ANIM_INDEX ,PEN20_WERE_GARURUMON_ANIM_INDEX ,PEN20_FANTOMON_ANIM_INDEX
                },
              };
            case PEN20_METAL_ETEMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PEN20_METAL_GARURUMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = 259200 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PEN20_OMEGAMON_ANIM_INDEX
                },
              };
            case PEN20_METAL_GREYMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PEN20_WAR_GREYMON_ANIM_INDEX
                },
              };
            case PEN20_METAL_MAMEMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PEN20_METAL_GARURUMON_ANIM_INDEX
                },
              };
            case PEN20_METAL_SEADRAMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PEN20_MOCHIMON_ANIM_INDEX:
              return {
                // Stage: Baby II
                .conditions = { .next_evolution_time_sec = 43200 },
                
                .num_animation_indices = 3,
                .animation_indices = {
                  PEN20_TENTOMON_ANIM_INDEX ,PEN20_GOTTSUMON_ANIM_INDEX ,PEN20_OTAMAMON_ANIM_INDEX
                },
              };
            case PEN20_MOKUMON_ANIM_INDEX:
              return {
                // Stage: Baby I
                .conditions = { .next_evolution_time_sec = 600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PEN20_PETI_MERAMON_ANIM_INDEX
                },
              };
            case PEN20_MONCHROMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 144000 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PEN20_MONOCHROMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 144000 },
                
                .num_animation_indices = 5,
                .animation_indices = {
                  PEN20_TRICERAMON_ANIM_INDEX ,PEN20_PICCOLOMON_ANIM_INDEX ,PEN20_JYAGAMON_ANIM_INDEX ,PEN20_ANGEWOMON_ANIM_INDEX ,PEN20_TONOSAMA_GEKOMON_ANIM_INDEX
                },
              };
            case PEN20_MUGENDRAMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PEN20_MUSHMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 4,
                .animation_indices = {
                  PEN20_WOODMON_ANIM_INDEX ,PEN20_RED_VEGIMON_ANIM_INDEX ,PEN20_V_DRAMON_ANIM_INDEX ,PEN20_BIRDRAMON_ANIM_INDEX
                },
              };
            case PEN20_NYOKIMON_ANIM_INDEX:
              return {
                // Stage: Baby I
                .conditions = { .next_evolution_time_sec = 600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PEN20_PYOCOMON_ANIM_INDEX
                },
              };
            case PEN20_OCTMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 144000 },
                
                .num_animation_indices = 3,
                .animation_indices = {
                  PEN20_MARIN_DEVIMON_ANIM_INDEX ,PEN20_DAGOMON_ANIM_INDEX ,PEN20_ANOMALOCARIMON_ANIM_INDEX
                },
              };
            case PEN20_OFANIMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PEN20_OGUDOMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PEN20_OKUWAMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 2,
                .animation_indices = {
                  PEN20_HERAKLE_KABUTERIMON_ANIM_INDEX ,PEN20_METAL_ETEMON_ANIM_INDEX
                },
              };
            case PEN20_OMEGAMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = 273600 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PEN20_ORDINEMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PEN20_OTAMAMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 5,
                .animation_indices = {
                  PEN20_TORTAMON_ANIM_INDEX ,PEN20_TAILMON_ANIM_INDEX ,PEN20_STARMON_ANIM_INDEX ,PEN20_KUWAGAMON_ANIM_INDEX ,PEN20_GEKOMON_ANIM_INDEX
                },
              };
            case PEN20_OURYUMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = 259200 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PEN20_ALPHAMON_OURYUKEN_ANIM_INDEX
                },
              };
            case PEN20_PAILDRAMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PEN20_IMPERIALDRAMON_FIGHTER_MODE_ANIM_INDEX
                },
              };
            case PEN20_PALMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 4,
                .animation_indices = {
                  PEN20_TOGEMON_ANIM_INDEX ,PEN20_KIWIMON_ANIM_INDEX ,PEN20_RED_VEGIMON_ANIM_INDEX ,PEN20_BIRDRAMON_ANIM_INDEX
                },
              };
            case PEN20_PETI_MERAMON_ANIM_INDEX:
              return {
                // Stage: Baby II
                .conditions = { .next_evolution_time_sec = 43200 },
                
                .num_animation_indices = 3,
                .animation_indices = {
                  PEN20_BAKUMON_ANIM_INDEX ,PEN20_CANDMON_ANIM_INDEX ,PEN20_PICO_DEVIMON_ANIM_INDEX
                },
              };
            case PEN20_PHASCOMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 3,
                .animation_indices = {
                  PEN20_TROOPMON_ANIM_INDEX ,PEN20_SHADRAMON_ANIM_INDEX ,PEN20_PORCUPAMON_ANIM_INDEX
                },
              };
            case PEN20_PICCOLOMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PEN20_SABER_LEOMON_ANIM_INDEX
                },
              };
            case PEN20_PICO_DEVIMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 5,
                .animation_indices = {
                  PEN20_GARURUMON_ANIM_INDEX ,PEN20_MERAMON_ANIM_INDEX ,PEN20_WIZARMON_ANIM_INDEX ,PEN20_DEVIMON_ANIM_INDEX ,PEN20_BAKEMON_ANIM_INDEX
                },
              };
            case PEN20_PIEMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = 259200 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PEN20_VOLTOBAUTAMON_ANIM_INDEX
                },
              };
            case PEN20_PINOCHIMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PEN20_PIYOMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PEN20_PLESIOMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PEN20_PORCUPAMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 144000 },
                
                .num_animation_indices = 3,
                .animation_indices = {
                  PEN20_ASTAMON_ANIM_INDEX ,PEN20_BAALMON_ANIM_INDEX ,PEN20_DARK_KNIGHTMON_ANIM_INDEX
                },
              };
            case PEN20_PORCUPMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 144000 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PEN20_PUKUMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PEN20_PUMPMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PEN20_BOLTMON_ANIM_INDEX
                },
              };
            case PEN20_PYOCOMON_ANIM_INDEX:
              return {
                // Stage: Baby II
                .conditions = { .next_evolution_time_sec = 43200 },
                
                .num_animation_indices = 4,
                .animation_indices = {
                  PEN20_PIYOMON_ANIM_INDEX ,PEN20_FLORAMON_ANIM_INDEX ,PEN20_PALMON_ANIM_INDEX ,PEN20_MUSHMON_ANIM_INDEX
                },
              };
            case PEN20_RAFFLESIMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PEN20_RAGNA_LORDMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PEN20_RAGUELMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = 259200 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PEN20_ORDINEMON_ANIM_INDEX
                },
              };
            case PEN20_RAIJI_LUDOMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PEN20_BRYWELUDRAMON_ANIM_INDEX
                },
              };
            case PEN20_RAKAMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 144000 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PEN20_RAPIDMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 144000 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PEN20_SAINT_GALGOMON_ANIM_INDEX
                },
              };
            case PEN20_RED_VEGIMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 144000 },
                
                .num_animation_indices = 3,
                .animation_indices = {
                  PEN20_JYUREIMON_ANIM_INDEX ,PEN20_GERBEMON_ANIM_INDEX ,PEN20_DELUMON_ANIM_INDEX
                },
              };
            case PEN20_REPPAMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 144000 },
                
                .num_animation_indices = 3,
                .animation_indices = {
                  PEN20_BEOWOLFMON_ANIM_INDEX ,PEN20_RIZE_GREYMON_ANIM_INDEX ,PEN20_MEGALO_GROWMON_ANIM_INDEX
                },
              };
            case PEN20_REVOLMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 144000 },
                
                .num_animation_indices = 3,
                .animation_indices = {
                  PEN20_METAL_GREYMON_ANIM_INDEX ,PEN20_ANDROMON_ANIM_INDEX ,PEN20_BIG_MAMEMON_ANIM_INDEX
                },
              };
            case PEN20_RIZE_GREYMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PEN20_ROSEMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = 259200 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PEN20_RAFFLESIMON_ANIM_INDEX
                },
              };
            case PEN20_RUKAMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 144000 },
                
                .num_animation_indices = 3,
                .animation_indices = {
                  PEN20_ZUDOMON_ANIM_INDEX ,PEN20_WHAMON_ANIM_INDEX ,PEN20_HANGYOMON_ANIM_INDEX
                },
              };
            case PEN20_RYUDAMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PEN20_GINRYUMON_ANIM_INDEX
                },
              };
            case PEN20_SABER_LEOMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PEN20_SAINT_GALGOMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PEN20_SAVIOR_HACKMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PEN20_JESMON_ANIM_INDEX
                },
              };
            case PEN20_SEADRAMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 144000 },
                
                .num_animation_indices = 4,
                .animation_indices = {
                  PEN20_MEGA_SEADRAMON_ANIM_INDEX ,PEN20_HANGYOMON_ANIM_INDEX ,PEN20_WHAMON_ANIM_INDEX ,PEN20_DAGOMON_ANIM_INDEX
                },
              };
            case PEN20_SERAPHIMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PEN20_SHADRAMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 144000 },
                
                .num_animation_indices = 2,
                .animation_indices = {
                  PEN20_DARK_KNIGHTMON_ANIM_INDEX ,PEN20_ASTAMON_ANIM_INDEX
                },
              };
            case PEN20_SHAKOMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 4,
                .animation_indices = {
                  PEN20_IKKAKUMON_ANIM_INDEX ,PEN20_SEADRAMON_ANIM_INDEX ,PEN20_GESOMON_ANIM_INDEX ,PEN20_OCTMON_ANIM_INDEX
                },
              };
            case PEN20_SKULL_MAMMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PEN20_SLAYERDRAMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = 259200 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PEN20_EXAMON_ANIM_INDEX
                },
              };
            case PEN20_STARMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 144000 },
                
                .num_animation_indices = 5,
                .animation_indices = {
                  PEN20_TRICERAMON_ANIM_INDEX ,PEN20_PICCOLOMON_ANIM_INDEX ,PEN20_JYAGAMON_ANIM_INDEX ,PEN20_ANGEWOMON_ANIM_INDEX ,PEN20_TONOSAMA_GEKOMON_ANIM_INDEX
                },
              };
            case PEN20_SUNFLOWMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 144000 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PEN20_LILAMON_ANIM_INDEX
                },
              };
            case PEN20_TAILMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 144000 },
                
                .num_animation_indices = 6,
                .animation_indices = {
                  PEN20_ANGEWOMON_ANIM_INDEX ,PEN20_JYAGAMON_ANIM_INDEX ,PEN20_PICCOLOMON_ANIM_INDEX ,PEN20_ANGEWOMON_ANIM_INDEX ,PEN20_HOLY_ANGEMON_ANIM_INDEX ,PEN20_METAL_MAMEMON_ANIM_INDEX
                },
              };
            case PEN20_TANKMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 144000 },
                
                .num_animation_indices = 3,
                .animation_indices = {
                  PEN20_KNIGHTMON_ANIM_INDEX ,PEN20_BIG_MAMEMON_ANIM_INDEX ,PEN20_ANDROMON_ANIM_INDEX
                },
              };
            case PEN20_TARGETMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 144000 },
                
                .num_animation_indices = 3,
                .animation_indices = {
                  PEN20_ETEMON_ANIM_INDEX ,PEN20_DURAMON_ANIM_INDEX ,PEN20_SAVIOR_HACKMON_ANIM_INDEX
                },
              };
            case PEN20_TENTOMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 5,
                .animation_indices = {
                  PEN20_KABUTERIMON_ANIM_INDEX ,PEN20_TORTAMON_ANIM_INDEX ,PEN20_TAILMON_ANIM_INDEX ,PEN20_KUWAGAMON_ANIM_INDEX ,PEN20_GEKOMON_ANIM_INDEX
                },
              };
            case PEN20_TERRIERMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PEN20_GALGOMON_ANIM_INDEX
                },
              };
            case PEN20_THUNDERBALLMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 144000 },
                
                .num_animation_indices = 3,
                .animation_indices = {
                  PEN20_KNIGHTMON_ANIM_INDEX ,PEN20_CYBERDRAMON_ANIM_INDEX ,PEN20_BIG_MAMEMON_ANIM_INDEX
                },
              };
            case PEN20_TIA_LUDOMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 144000 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PEN20_RAIJI_LUDOMON_ANIM_INDEX
                },
              };
            case PEN20_TOGEMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 144000 },
                
                .num_animation_indices = 4,
                .animation_indices = {
                  PEN20_LILIMON_ANIM_INDEX ,PEN20_DELUMON_ANIM_INDEX ,PEN20_GARUDAMON_ANIM_INDEX ,PEN20_GERBEMON_ANIM_INDEX
                },
              };
            case PEN20_TONOSAMA_GEKOMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PEN20_METAL_ETEMON_ANIM_INDEX
                },
              };
            case PEN20_TORTAMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 144000 },
                
                .num_animation_indices = 3,
                .animation_indices = {
                  PEN20_ATLUR_KABUTERIMON_ANIM_INDEX ,PEN20_JYAGAMON_ANIM_INDEX ,PEN20_PICCOLOMON_ANIM_INDEX
                },
              };
            case PEN20_TOY_AGUMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 4,
                .animation_indices = {
                  PEN20_GREYMON_ANIM_INDEX ,PEN20_REVOLMON_ANIM_INDEX ,PEN20_CLOCKMON_ANIM_INDEX ,PEN20_THUNDERBALLMON_ANIM_INDEX
                },
              };
            case PEN20_TRICERAMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PEN20_SABER_LEOMON_ANIM_INDEX
                },
              };
            case PEN20_TROOPMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 144000 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PEN20_DARK_KNIGHTMON_ANIM_INDEX
                },
              };
            case PEN20_TURUIEMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 144000 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PEN20_ANDIRAMON_ANIM_INDEX
                },
              };
            case PEN20_VAMDEMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 2,
                .animation_indices = {
                  PEN20_PIEMON_ANIM_INDEX ,PEN20_VOLTOBAUTAMON_ANIM_INDEX
                },
              };
            case PEN20_V_DRAMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 144000 },
                
                .num_animation_indices = 3,
                .animation_indices = {
                  PEN20_AERO_V_DRAMON_ANIM_INDEX ,PEN20_GARUDAMON_ANIM_INDEX ,PEN20_DELUMON_ANIM_INDEX
                },
              };
            case PEN20_VEMDEMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PEN20_VENOM_VAMDEMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PEN20_V_MON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 2,
                .animation_indices = {
                  PEN20_XV_MON_ANIM_INDEX ,PEN20_V_DRAMON_ANIM_INDEX
                },
              };
            case PEN20_VOLCANICDRAMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PEN20_VOLTOBAUTAMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PEN20_VORVOMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PEN20_LAVORVOMON_ANIM_INDEX
                },
              };
            case PEN20_WAR_GREYMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = 259200 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PEN20_OMEGAMON_ANIM_INDEX
                },
              };
            case PEN20_WARU_MOZAEMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PEN20_WERE_GARURUMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 2,
                .animation_indices = {
                  PEN20_SKULL_MAMMON_ANIM_INDEX ,PEN20_METAL_GARURUMON_ANIM_INDEX
                },
              };
            case PEN20_WHAMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 144000 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PEN20_PLESIOMON_ANIM_INDEX
                },
              };
            case PEN20_WINGDRAMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PEN20_SLAYERDRAMON_ANIM_INDEX
                },
              };
            case PEN20_WIZARMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 144000 },
                
                .num_animation_indices = 4,
                .animation_indices = {
                  PEN20_DEATH_MERAMON_ANIM_INDEX ,PEN20_PUMPMON_ANIM_INDEX ,PEN20_WERE_GARURUMON_ANIM_INDEX ,PEN20_FANTOMON_ANIM_INDEX
                },
              };
            case PEN20_WOODMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 144000 },
                
                .num_animation_indices = 3,
                .animation_indices = {
                  PEN20_JYUREIMON_ANIM_INDEX ,PEN20_GERBEMON_ANIM_INDEX ,PEN20_DELUMON_ANIM_INDEX
                },
              };
            case PEN20_XV_MON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 144000 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PEN20_PAILDRAMON_ANIM_INDEX
                },
              };
            case PEN20_ZERIMON_ANIM_INDEX:
              return {
                // Stage: Baby I
                .conditions = { .next_evolution_time_sec = 600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PEN20_GUMMYMON_ANIM_INDEX
                },
              };
            case PEN20_ZUDOMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PEN20_MARIN_ANGEMON_ANIM_INDEX
                },
              };
            default: return {};
        }
        return {};
    }
}

