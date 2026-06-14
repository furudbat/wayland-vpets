#include "embedded_assets/embedded_image.h"
#include "embedded_assets/pen/pen.hpp"
#include "embedded_assets/pen/pen_evol.h"
#include "graphics/animation_shared_memory.h"

namespace bongocat::assets {
    animation::animation_evolution_data_t get_pen_evolution_data(size_t index) {
        switch (index) {
            case PEN_AERO_V_DRAMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 244800 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PEN_HOUOUMON_ANIM_INDEX
                },
              };
            case PEN_ANDROMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 244800 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PEN_ANGEWOMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 244800 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PEN_OMEGAMON_ANIM_INDEX
                },
              };
            case PEN_ANOMALOCARIMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 244800 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PEN_METAL_SEADRAMON_ANIM_INDEX
                },
              };
            case PEN_ASURAMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 244800 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PEN_WAR_GREYMON_ANIM_INDEX
                },
              };
            case PEN_ATLUR_KABUTERIMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 244800 },
                
                .num_animation_indices = 2,
                .animation_indices = {
                  PEN_HERAKLE_KABUTERIMON_ANIM_INDEX ,PEN_HOLYDRAMON_ANIM_INDEX
                },
              };
            case PEN_BAKEMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 216000 },
                
                .num_animation_indices = 3,
                .animation_indices = {
                  PEN_VAMDEMON_ANIM_INDEX ,PEN_FANTOMON_ANIM_INDEX ,PEN_PUMPMON_ANIM_INDEX
                },
              };
            case PEN_BAKUMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 72000 },
                
                .num_animation_indices = 5,
                .animation_indices = {
                  PEN_PICO_DEVIMON_ANIM_INDEX ,PEN_HANUMON_ANIM_INDEX ,PEN_GARURUMON_ANIM_INDEX ,PEN_MERAMON_ANIM_INDEX ,PEN_WIZARMON_ANIM_INDEX
                },
              };
            case PEN_BIG_MAMEMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 244800 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PEN_METAL_GARURUMON_ANIM_INDEX
                },
              };
            case PEN_BIRDRAMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 216000 },
                
                .num_animation_indices = 3,
                .animation_indices = {
                  PEN_AERO_V_DRAMON_ANIM_INDEX ,PEN_GARUDAMON_ANIM_INDEX ,PEN_DELUMON_ANIM_INDEX
                },
              };
            case PEN_BLOSSOMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 244800 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PEN_GRIFFOMON_ANIM_INDEX
                },
              };
            case PEN_BOLTMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PEN_BUBBMON_ANIM_INDEX:
              return {
                // Stage: Baby I
                .conditions = { .next_evolution_time_sec = 3600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PEN_MOCHIMON_ANIM_INDEX
                },
              };
            case PEN_CANDMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 72000 },
                
                .num_animation_indices = 4,
                .animation_indices = {
                  PEN_MERAMON_ANIM_INDEX ,PEN_WIZARMON_ANIM_INDEX ,PEN_DEVIMON_ANIM_INDEX ,PEN_BAKEMON_ANIM_INDEX
                },
              };
            case PEN_CAPRIMON_ANIM_INDEX:
              return {
                // Stage: Baby II
                .conditions = { .next_evolution_time_sec = 57600 },
                
                .num_animation_indices = 3,
                .animation_indices = {
                  PEN_TOY_AGUMON_ANIM_INDEX ,PEN_KOKUWAMON_ANIM_INDEX ,PEN_HAGURUMON_ANIM_INDEX
                },
              };
            case PEN_CHOROMON_ANIM_INDEX:
              return {
                // Stage: Baby I
                .conditions = { .next_evolution_time_sec = 3600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PEN_CAPRIMON_ANIM_INDEX
                },
              };
            case PEN_CLOCKMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 216000 },
                
                .num_animation_indices = 5,
                .animation_indices = {
                  PEN_KNIGHTMON_ANIM_INDEX ,PEN_BIG_MAMEMON_ANIM_INDEX ,PEN_ANDROMON_ANIM_INDEX ,PEN_CYBERDRAMON_ANIM_INDEX ,PEN_WARU_MONZAEMON_ANIM_INDEX
                },
              };
            case PEN_COELAMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 216000 },
                
                .num_animation_indices = 4,
                .animation_indices = {
                  PEN_MEGA_SEADRAMON_ANIM_INDEX ,PEN_ANOMALOCARIMON_ANIM_INDEX ,PEN_WHAMON_ANIM_INDEX ,PEN_DAGOMON_ANIM_INDEX
                },
              };
            case PEN_CYBERDRAMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 244800 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PEN_DAGOMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 244800 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PEN_PUKUMON_ANIM_INDEX
                },
              };
            case PEN_DEATH_MERAMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 244800 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PEN_BOLTMON_ANIM_INDEX
                },
              };
            case PEN_DELUMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 244800 },
                
                .num_animation_indices = 3,
                .animation_indices = {
                  PEN_HOUOUMON_ANIM_INDEX ,PEN_GRIFFOMON_ANIM_INDEX ,PEN_ROSEMON_ANIM_INDEX
                },
              };
            case PEN_DEVIMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 216000 },
                
                .num_animation_indices = 4,
                .animation_indices = {
                  PEN_VAMDEMON_ANIM_INDEX ,PEN_LADY_DEVIMON_ANIM_INDEX ,PEN_FANTOMON_ANIM_INDEX ,PEN_PUMPMON_ANIM_INDEX
                },
              };
            case PEN_DOKUGUMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 216000 },
                
                .num_animation_indices = 3,
                .animation_indices = {
                  PEN_WERE_GARURUMON_ANIM_INDEX ,PEN_DEATH_MERAMON_ANIM_INDEX ,PEN_VAMDEMON_ANIM_INDEX
                },
              };
            case PEN_EBIDRAMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 216000 },
                
                .num_animation_indices = 4,
                .animation_indices = {
                  PEN_MEGA_SEADRAMON_ANIM_INDEX ,PEN_HANGYOMON_ANIM_INDEX ,PEN_WHAMON_ANIM_INDEX ,PEN_DAGOMON_ANIM_INDEX
                },
              };
            case PEN_FANTOMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 244800 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PEN_PIEMON_ANIM_INDEX
                },
              };
            case PEN_FLORAMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 72000 },
                
                .num_animation_indices = 4,
                .animation_indices = {
                  PEN_TOGEMON_ANIM_INDEX ,PEN_KIWIMON_ANIM_INDEX ,PEN_WOODMON_ANIM_INDEX ,PEN_RED_VEGIMON_ANIM_INDEX
                },
              };
            case PEN_GANIMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 72000 },
                
                .num_animation_indices = 5,
                .animation_indices = {
                  PEN_RUKAMON_ANIM_INDEX ,PEN_SEADRAMON_ANIM_INDEX ,PEN_COELAMON_ANIM_INDEX ,PEN_EBIDRAMON_ANIM_INDEX ,PEN_GESOMON_ANIM_INDEX
                },
              };
            case PEN_GARUDAMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 244800 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PEN_GARURUMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 216000 },
                
                .num_animation_indices = 3,
                .animation_indices = {
                  PEN_MAMMON_ANIM_INDEX ,PEN_WERE_GARURUMON_ANIM_INDEX ,PEN_PUMPMON_ANIM_INDEX
                },
              };
            case PEN_GEKOMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 216000 },
                
                .num_animation_indices = 3,
                .animation_indices = {
                  PEN_OKUWAMON_ANIM_INDEX ,PEN_TONOSAMA_GEKOMON_ANIM_INDEX ,PEN_PICCOLOMON_ANIM_INDEX
                },
              };
            case PEN_GERBEMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 244800 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PEN_PINOCHIMON_ANIM_INDEX
                },
              };
            case PEN_GESOMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 216000 },
                
                .num_animation_indices = 4,
                .animation_indices = {
                  PEN_MARIN_DEVIMON_ANIM_INDEX ,PEN_DAGOMON_ANIM_INDEX ,PEN_ANOMALOCARIMON_ANIM_INDEX ,PEN_HANGYOMON_ANIM_INDEX
                },
              };
            case PEN_GOMAMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 72000 },
                
                .num_animation_indices = 5,
                .animation_indices = {
                  PEN_IKKAKUMON_ANIM_INDEX ,PEN_RUKAMON_ANIM_INDEX ,PEN_COELAMON_ANIM_INDEX ,PEN_EBIDRAMON_ANIM_INDEX ,PEN_OCTMON_ANIM_INDEX
                },
              };
            case PEN_GOTTSUMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 72000 },
                
                .num_animation_indices = 5,
                .animation_indices = {
                  PEN_TORTAMON_ANIM_INDEX ,PEN_TAILMON_ANIM_INDEX ,PEN_MONOCHROMON_ANIM_INDEX ,PEN_STARMON_ANIM_INDEX ,PEN_GEKOMON_ANIM_INDEX
                },
              };
            case PEN_GREYMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 216000 },
                
                .num_animation_indices = 6,
                .animation_indices = {
                  PEN_METAL_GREYMON_ANIM_INDEX ,PEN_ANDROMON_ANIM_INDEX ,PEN_CYBERDRAMON_ANIM_INDEX ,PEN_BIG_MAMEMON_ANIM_INDEX ,PEN_ASURAMON_ANIM_INDEX ,PEN_METAL_MAMEMON_ANIM_INDEX
                },
              };
            case PEN_GRIFFOMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PEN_GUARDROMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 216000 },
                
                .num_animation_indices = 3,
                .animation_indices = {
                  PEN_MEGADRAMON_ANIM_INDEX ,PEN_WARU_MONZAEMON_ANIM_INDEX ,PEN_BIG_MAMEMON_ANIM_INDEX
                },
              };
            case PEN_HAGURUMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 72000 },
                
                .num_animation_indices = 5,
                .animation_indices = {
                  PEN_GREYMON_ANIM_INDEX ,PEN_TANKMON_ANIM_INDEX ,PEN_THUNDERBALLMON_ANIM_INDEX ,PEN_GUARDROMON_ANIM_INDEX ,PEN_MECHANORIMON_ANIM_INDEX
                },
              };
            case PEN_HANGYMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 244800 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PEN_HANGYOMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 244800 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PEN_HANUMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 216000 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PEN_MAMMON_ANIM_INDEX
                },
              };
            case PEN_HERAKLE_KABUTERIMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PEN_HERKULE_KABUTERIMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PEN_HOLY_ANGEMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 244800 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PEN_OMEGAMON_ANIM_INDEX
                },
              };
            case PEN_HOLYDRAMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PEN_HOUOUMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PEN_IGNAMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 216000 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PEN_IKKAKUMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 216000 },
                
                .num_animation_indices = 4,
                .animation_indices = {
                  PEN_ZUDOMON_ANIM_INDEX ,PEN_WHAMON_ANIM_INDEX ,PEN_ANOMALOCARIMON_ANIM_INDEX ,PEN_HANGYOMON_ANIM_INDEX
                },
              };
            case PEN_JYAGAMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 244800 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PEN_JYUREIMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 244800 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PEN_PINOCHIMON_ANIM_INDEX
                },
              };
            case PEN_KABUTERIMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 216000 },
                
                .num_animation_indices = 4,
                .animation_indices = {
                  PEN_ATLUR_KABUTERIMON_ANIM_INDEX ,PEN_JYAGAMON_ANIM_INDEX ,PEN_ANGEWOMON_ANIM_INDEX ,PEN_PICCOLOMON_ANIM_INDEX
                },
              };
            case PEN_KIWIMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 216000 },
                
                .num_animation_indices = 5,
                .animation_indices = {
                  PEN_BLOSSOMON_ANIM_INDEX ,PEN_LILIMON_ANIM_INDEX ,PEN_DELUMON_ANIM_INDEX ,PEN_GARUDAMON_ANIM_INDEX ,PEN_GERBEMON_ANIM_INDEX
                },
              };
            case PEN_KNIGHTMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 244800 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PEN_KOKUWAMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 72000 },
                
                .num_animation_indices = 5,
                .animation_indices = {
                  PEN_REVOLMON_ANIM_INDEX ,PEN_TANKMON_ANIM_INDEX ,PEN_THUNDERBALLMON_ANIM_INDEX ,PEN_CLOCKMON_ANIM_INDEX ,PEN_GUARDROMON_ANIM_INDEX
                },
              };
            case PEN_KUWAGAMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 216000 },
                
                .num_animation_indices = 3,
                .animation_indices = {
                  PEN_OKUWAMON_ANIM_INDEX ,PEN_TONOSAMA_GEKOMON_ANIM_INDEX ,PEN_PICCOLOMON_ANIM_INDEX
                },
              };
            case PEN_LADY_DEVIMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 244800 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PEN_LILIMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 244800 },
                
                .num_animation_indices = 2,
                .animation_indices = {
                  PEN_ROSEMON_ANIM_INDEX ,PEN_GRIFFOMON_ANIM_INDEX
                },
              };
            case PEN_MAMMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 244800 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PEN_SKULL_MAMMON_ANIM_INDEX
                },
              };
            case PEN_MARIN_ANGEMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PEN_MARIN_DEVIMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 244800 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PEN_PUKUMON_ANIM_INDEX
                },
              };
            case PEN_MECHANORIMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 216000 },
                
                .num_animation_indices = 3,
                .animation_indices = {
                  PEN_MEGADRAMON_ANIM_INDEX ,PEN_WARU_MONZAEMON_ANIM_INDEX ,PEN_BIG_MAMEMON_ANIM_INDEX
                },
              };
            case PEN_MEGADRAMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 244800 },
                
                .num_animation_indices = 2,
                .animation_indices = {
                  PEN_MUGENDRAMON_ANIM_INDEX ,PEN_VENOM_VAMDEMON_ANIM_INDEX
                },
              };
            case PEN_MEGA_SEADRAMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 244800 },
                
                .num_animation_indices = 3,
                .animation_indices = {
                  PEN_METAL_SEADRAMON_ANIM_INDEX ,PEN_PLESIOMON_ANIM_INDEX ,PEN_MARIN_ANGEMON_ANIM_INDEX
                },
              };
            case PEN_MERAMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 216000 },
                
                .num_animation_indices = 4,
                .animation_indices = {
                  PEN_DEATH_MERAMON_ANIM_INDEX ,PEN_PUMPMON_ANIM_INDEX ,PEN_WERE_GARURUMON_ANIM_INDEX ,PEN_FANTOMON_ANIM_INDEX
                },
              };
            case PEN_METAL_ETEMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PEN_METAL_GARURUMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PEN_METAL_GREYMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 244800 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PEN_WAR_GREYMON_ANIM_INDEX
                },
              };
            case PEN_METAL_MAMEMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 244800 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PEN_METAL_GARURUMON_ANIM_INDEX
                },
              };
            case PEN_METAL_SEADRAMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PEN_MOCHIMON_ANIM_INDEX:
              return {
                // Stage: Baby II
                .conditions = { .next_evolution_time_sec = 57600 },
                
                .num_animation_indices = 3,
                .animation_indices = {
                  PEN_TENTOMON_ANIM_INDEX ,PEN_GOTTSUMON_ANIM_INDEX ,PEN_OTAMAMON_ANIM_INDEX
                },
              };
            case PEN_MOKUMON_ANIM_INDEX:
              return {
                // Stage: Baby I
                .conditions = { .next_evolution_time_sec = 3600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PEN_PETI_MERAMON_ANIM_INDEX
                },
              };
            case PEN_MONOCHROMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 216000 },
                
                .num_animation_indices = 5,
                .animation_indices = {
                  PEN_TRICERAMON_ANIM_INDEX ,PEN_PICCOLOMON_ANIM_INDEX ,PEN_JYAGAMON_ANIM_INDEX ,PEN_ANGEWOMON_ANIM_INDEX ,PEN_TONOSAMA_GEKOMON_ANIM_INDEX
                },
              };
            case PEN_MUGENDRAMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PEN_MUSHMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 72000 },
                
                .num_animation_indices = 4,
                .animation_indices = {
                  PEN_V_DRAMON_ANIM_INDEX ,PEN_BIRDRAMON_ANIM_INDEX ,PEN_WOODMON_ANIM_INDEX ,PEN_RED_VEGIMON_ANIM_INDEX
                },
              };
            case PEN_NYOKIMON_ANIM_INDEX:
              return {
                // Stage: Baby I
                .conditions = { .next_evolution_time_sec = 3600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PEN_PYOCOMON_ANIM_INDEX
                },
              };
            case PEN_OCTMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 216000 },
                
                .num_animation_indices = 4,
                .animation_indices = {
                  PEN_MARIN_DEVIMON_ANIM_INDEX ,PEN_DAGOMON_ANIM_INDEX ,PEN_ANOMALOCARIMON_ANIM_INDEX ,PEN_HANGYOMON_ANIM_INDEX
                },
              };
            case PEN_OKUWAMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 244800 },
                
                .num_animation_indices = 3,
                .animation_indices = {
                  PEN_HERAKLE_KABUTERIMON_ANIM_INDEX ,PEN_HOLYDRAMON_ANIM_INDEX ,PEN_METAL_ETEMON_ANIM_INDEX
                },
              };
            case PEN_OMEGAMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PEN_OTAMAMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 72000 },
                
                .num_animation_indices = 5,
                .animation_indices = {
                  PEN_TORTAMON_ANIM_INDEX ,PEN_TAILMON_ANIM_INDEX ,PEN_STARMON_ANIM_INDEX ,PEN_KUWAGAMON_ANIM_INDEX ,PEN_GEKOMON_ANIM_INDEX
                },
              };
            case PEN_PALMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 72000 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PEN_PETI_MERAMON_ANIM_INDEX:
              return {
                // Stage: Baby II
                .conditions = { .next_evolution_time_sec = 57600 },
                
                .num_animation_indices = 3,
                .animation_indices = {
                  PEN_BAKUMON_ANIM_INDEX ,PEN_CANDMON_ANIM_INDEX ,PEN_PICO_DEVIMON_ANIM_INDEX
                },
              };
            case PEN_PICCOLOMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 244800 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PEN_SABER_LEOMON_ANIM_INDEX
                },
              };
            case PEN_PICO_DEVIMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 72000 },
                
                .num_animation_indices = 5,
                .animation_indices = {
                  PEN_GARURUMON_ANIM_INDEX ,PEN_MERAMON_ANIM_INDEX ,PEN_WIZARMON_ANIM_INDEX ,PEN_DEVIMON_ANIM_INDEX ,PEN_BAKEMON_ANIM_INDEX
                },
              };
            case PEN_PIEMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PEN_PINOCHIMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PEN_PIYOMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 72000 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PEN_PLESIOMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PEN_PUKUMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PEN_PUMPMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 244800 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PEN_BOLTMON_ANIM_INDEX
                },
              };
            case PEN_PYOCOMON_ANIM_INDEX:
              return {
                // Stage: Baby II
                .conditions = { .next_evolution_time_sec = 57600 },
                
                .num_animation_indices = 4,
                .animation_indices = {
                  PEN_PIYOMON_ANIM_INDEX ,PEN_FLORAMON_ANIM_INDEX ,PEN_PALMON_ANIM_INDEX ,PEN_MUSHMON_ANIM_INDEX
                },
              };
            case PEN_RAKAMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 216000 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PEN_RED_VEGIMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 216000 },
                
                .num_animation_indices = 3,
                .animation_indices = {
                  PEN_JYUREIMON_ANIM_INDEX ,PEN_GERBEMON_ANIM_INDEX ,PEN_DELUMON_ANIM_INDEX
                },
              };
            case PEN_REVOLMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 216000 },
                
                .num_animation_indices = 4,
                .animation_indices = {
                  PEN_METAL_GREYMON_ANIM_INDEX ,PEN_ANDROMON_ANIM_INDEX ,PEN_CYBERDRAMON_ANIM_INDEX ,PEN_BIG_MAMEMON_ANIM_INDEX
                },
              };
            case PEN_ROSEMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PEN_RUKAMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 216000 },
                
                .num_animation_indices = 4,
                .animation_indices = {
                  PEN_ZUDOMON_ANIM_INDEX ,PEN_WHAMON_ANIM_INDEX ,PEN_ANOMALOCARIMON_ANIM_INDEX ,PEN_HANGYOMON_ANIM_INDEX
                },
              };
            case PEN_SABER_LEOMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PEN_SEADRAMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 216000 },
                
                .num_animation_indices = 5,
                .animation_indices = {
                  PEN_MEGA_SEADRAMON_ANIM_INDEX ,PEN_ANOMALOCARIMON_ANIM_INDEX ,PEN_HANGYOMON_ANIM_INDEX ,PEN_WHAMON_ANIM_INDEX ,PEN_DAGOMON_ANIM_INDEX
                },
              };
            case PEN_SHAKOMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 72000 },
                
                .num_animation_indices = 4,
                .animation_indices = {
                  PEN_IKKAKUMON_ANIM_INDEX ,PEN_SEADRAMON_ANIM_INDEX ,PEN_GESOMON_ANIM_INDEX ,PEN_OCTMON_ANIM_INDEX
                },
              };
            case PEN_SKULL_MAMMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PEN_STARMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 216000 },
                
                .num_animation_indices = 5,
                .animation_indices = {
                  PEN_TRICERAMON_ANIM_INDEX ,PEN_PICCOLOMON_ANIM_INDEX ,PEN_JYAGAMON_ANIM_INDEX ,PEN_ANGEWOMON_ANIM_INDEX ,PEN_TONOSAMA_GEKOMON_ANIM_INDEX
                },
              };
            case PEN_TAILMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 216000 },
                
                .num_animation_indices = 3,
                .animation_indices = {
                  PEN_HOLY_ANGEMON_ANIM_INDEX ,PEN_ANGEWOMON_ANIM_INDEX ,PEN_METAL_MAMEMON_ANIM_INDEX
                },
              };
            case PEN_TANKMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 216000 },
                
                .num_animation_indices = 4,
                .animation_indices = {
                  PEN_KNIGHTMON_ANIM_INDEX ,PEN_BIG_MAMEMON_ANIM_INDEX ,PEN_ANDROMON_ANIM_INDEX ,PEN_WARU_MONZAEMON_ANIM_INDEX
                },
              };
            case PEN_TENTOMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 72000 },
                
                .num_animation_indices = 5,
                .animation_indices = {
                  PEN_KABUTERIMON_ANIM_INDEX ,PEN_TORTAMON_ANIM_INDEX ,PEN_TAILMON_ANIM_INDEX ,PEN_KUWAGAMON_ANIM_INDEX ,PEN_GEKOMON_ANIM_INDEX
                },
              };
            case PEN_THUNDERBALLMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 216000 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PEN_TOGEMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 216000 },
                
                .num_animation_indices = 5,
                .animation_indices = {
                  PEN_BLOSSOMON_ANIM_INDEX ,PEN_LILIMON_ANIM_INDEX ,PEN_DELUMON_ANIM_INDEX ,PEN_GARUDAMON_ANIM_INDEX ,PEN_GERBEMON_ANIM_INDEX
                },
              };
            case PEN_TONOSAMA_GEKOMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 244800 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PEN_METAL_ETEMON_ANIM_INDEX
                },
              };
            case PEN_TORTAMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 216000 },
                
                .num_animation_indices = 3,
                .animation_indices = {
                  PEN_ATLUR_KABUTERIMON_ANIM_INDEX ,PEN_JYAGAMON_ANIM_INDEX ,PEN_PICCOLOMON_ANIM_INDEX
                },
              };
            case PEN_TOY_AGUMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 72000 },
                
                .num_animation_indices = 5,
                .animation_indices = {
                  PEN_GREYMON_ANIM_INDEX ,PEN_REVOLMON_ANIM_INDEX ,PEN_TANKMON_ANIM_INDEX ,PEN_THUNDERBALLMON_ANIM_INDEX ,PEN_CLOCKMON_ANIM_INDEX
                },
              };
            case PEN_TRICERAMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 244800 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PEN_SABER_LEOMON_ANIM_INDEX
                },
              };
            case PEN_VAMDEMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 244800 },
                
                .num_animation_indices = 2,
                .animation_indices = {
                  PEN_PIEMON_ANIM_INDEX ,PEN_SKULL_MAMMON_ANIM_INDEX
                },
              };
            case PEN_V_DRAMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 216000 },
                
                .num_animation_indices = 3,
                .animation_indices = {
                  PEN_AERO_V_DRAMON_ANIM_INDEX ,PEN_GARUDAMON_ANIM_INDEX ,PEN_DELUMON_ANIM_INDEX
                },
              };
            case PEN_VEMDEMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 244800 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PEN_VENOM_VAMDEMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PEN_WAR_GREYMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PEN_WARU_MONZAEMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 244800 },
                
                .num_animation_indices = 2,
                .animation_indices = {
                  PEN_MUGENDRAMON_ANIM_INDEX ,PEN_VENOM_VAMDEMON_ANIM_INDEX
                },
              };
            case PEN_WARU_MOZAEMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 244800 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PEN_WERE_GARURUMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 244800 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PEN_WHAMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 216000 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PEN_WIZARMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 216000 },
                
                .num_animation_indices = 4,
                .animation_indices = {
                  PEN_DEATH_MERAMON_ANIM_INDEX ,PEN_PUMPMON_ANIM_INDEX ,PEN_WERE_GARURUMON_ANIM_INDEX ,PEN_FANTOMON_ANIM_INDEX
                },
              };
            case PEN_WOODMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 216000 },
                
                .num_animation_indices = 3,
                .animation_indices = {
                  PEN_JYUREIMON_ANIM_INDEX ,PEN_GERBEMON_ANIM_INDEX ,PEN_DELUMON_ANIM_INDEX
                },
              };
            case PEN_ZUDOMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 244800 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PEN_MARIN_ANGEMON_ANIM_INDEX
                },
              };
            default: return {};
        }
        return {};
    }
}

