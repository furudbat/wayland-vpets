#include "embedded_assets/embedded_image.h"
#include "embedded_assets/dmall/dmall.hpp"
#include "embedded_assets/dmall/dmall_evol.h"
#include "graphics/animation_shared_memory.h"

namespace bongocat::assets {
    animation::animation_evolution_data_t get_dmall_evolution_data(size_t index) {
        switch (index) {
            case DMALL_AEGISDRAMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMALL_AERO_V_DRAMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 13,
                .animation_indices = {
                  DMALL_ULFORCE_V_DRAMON_ANIM_INDEX ,DMALL_CHAOSDRAMON_ANIM_INDEX ,DMALL_DARKDRAMON_ANIM_INDEX ,DMALL_DORUGORAMON_ANIM_INDEX ,DMALL_DUKEMON_ANIM_INDEX ,DMALL_HOUOUMON_ANIM_INDEX ,DMALL_MEGIDRAMON_ANIM_INDEX ,DMALL_METAL_GARURUMON_ANIM_INDEX ,DMALL_MUGENDRAMON_ANIM_INDEX ,DMALL_PLESIOMON_ANIM_INDEX ,DMALL_RAFFLESIMON_ANIM_INDEX ,DMALL_ULFORCE_V_DRAMON_ANIM_INDEX ,DMALL_WAR_GREYMON_ANIM_INDEX
                },
              };
            case DMALL_AGUMON_2006_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_GEO_GREYMON_ANIM_INDEX ,DMALL_AIRDRAMON_ANIM_INDEX ,DMALL_ANGEMON_ANIM_INDEX ,DMALL_BIRDRAMON_ANIM_INDEX ,DMALL_BLACK_GROWMON_ANIM_INDEX ,DMALL_CYCLOMON_ANIM_INDEX ,DMALL_DEVIMON_ANIM_INDEX ,DMALL_DORUGAMON_ANIM_INDEX ,DMALL_EBIDRAMON_ANIM_INDEX ,DMALL_FIRAMON_ANIM_INDEX ,DMALL_GAOGAMON_ANIM_INDEX ,DMALL_GAWAPPAMON_ANIM_INDEX ,DMALL_GEO_GREYMON_ANIM_INDEX ,DMALL_GOLD_NUMEMON_ANIM_INDEX ,DMALL_GREYMON_ANIM_INDEX
                },
              };
            case DMALL_AGUMON_BLACK_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_GREYMON_BLUE_ANIM_INDEX ,DMALL_AIRDRAMON_ANIM_INDEX ,DMALL_ANGEMON_ANIM_INDEX ,DMALL_BIRDRAMON_ANIM_INDEX ,DMALL_CYCLOMON_ANIM_INDEX ,DMALL_DEATH_X_DORUGAMON_ANIM_INDEX ,DMALL_DEVIMON_ANIM_INDEX ,DMALL_DORUGAMON_ANIM_INDEX ,DMALL_EBIDRAMON_ANIM_INDEX ,DMALL_FUGAMON_ANIM_INDEX ,DMALL_GARURUMON_ANIM_INDEX ,DMALL_GEO_GREYMON_ANIM_INDEX ,DMALL_GEREMON_ANIM_INDEX ,DMALL_GREYMON_ANIM_INDEX ,DMALL_GREYMON_BLUE_ANIM_INDEX
                },
              };
            case DMALL_AGUMON_BLACK_X_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 8,
                .animation_indices = {
                  DMALL_DARK_TYRANOMON_X_ANIM_INDEX ,DMALL_KUWAGAMON_X_ANIM_INDEX ,DMALL_NUMEMON_X_ANIM_INDEX ,DMALL_ALLOMON_X_ANIM_INDEX ,DMALL_GEO_GREYMON_ANIM_INDEX ,DMALL_GREYMON_ANIM_INDEX ,DMALL_GREYMON_BLUE_ANIM_INDEX ,DMALL_TYRANOMON_ANIM_INDEX
                },
              };
            case DMALL_AGUMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_CENTALMON_ANIM_INDEX ,DMALL_GREYMON_ANIM_INDEX ,DMALL_MERAMON_ANIM_INDEX ,DMALL_TYRANOMON_ANIM_INDEX ,DMALL_GREYMON_ANIM_INDEX ,DMALL_TYRANOMON_ANIM_INDEX ,DMALL_DEVIMON_ANIM_INDEX ,DMALL_MERAMON_ANIM_INDEX ,DMALL_NUMEMON_ANIM_INDEX ,DMALL_AIRDRAMON_ANIM_INDEX ,DMALL_ALGOMON_ADULT_ANIM_INDEX ,DMALL_ANGEMON_ANIM_INDEX ,DMALL_BAKEMON_ANIM_INDEX ,DMALL_BIRDRAMON_ANIM_INDEX ,DMALL_CENTALMON_ANIM_INDEX
                },
              };
            case DMALL_AGUMON_X_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_OMEKAMON_ANIM_INDEX ,DMALL_TYRANOMON_X_ANIM_INDEX ,DMALL_TOBUCATMON_ANIM_INDEX ,DMALL_DAMEMON_ANIM_INDEX ,DMALL_AIRDRAMON_ANIM_INDEX ,DMALL_ANGEMON_ANIM_INDEX ,DMALL_BIRDRAMON_ANIM_INDEX ,DMALL_DAMEMON_ANIM_INDEX ,DMALL_DEATH_X_DORUGAMON_ANIM_INDEX ,DMALL_DEVIMON_ANIM_INDEX ,DMALL_DORUGAMON_ANIM_INDEX ,DMALL_EBIDRAMON_ANIM_INDEX ,DMALL_GARURUMON_ANIM_INDEX ,DMALL_GEO_GREYMON_ANIM_INDEX ,DMALL_GREYMON_ANIM_INDEX
                },
              };
            case DMALL_AGUMON_YUKI_NO_KIZUNA_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMALL_AIRDRAMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_CHIMAIRAMON_ANIM_INDEX ,DMALL_MEGADRAMON_ANIM_INDEX ,DMALL_METAL_GREYMON_VIRUS_ANIM_INDEX ,DMALL_METAL_GREYMON_ANIM_INDEX ,DMALL_AERO_V_DRAMON_ANIM_INDEX ,DMALL_ANDROMON_ANIM_INDEX ,DMALL_ANGEWOMON_ANIM_INDEX ,DMALL_ASURAMON_ANIM_INDEX ,DMALL_BAALMON_ANIM_INDEX ,DMALL_BIG_MAMEMON_ANIM_INDEX ,DMALL_CHIMAIRAMON_ANIM_INDEX ,DMALL_CYBERDRAMON_ANIM_INDEX ,DMALL_DELUMON_ANIM_INDEX ,DMALL_DURAMON_ANIM_INDEX ,DMALL_GARUDAMON_ANIM_INDEX
                },
              };
            case DMALL_ALGOMON_ADULT_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 9,
                .animation_indices = {
                  DMALL_ANDROMON_ANIM_INDEX ,DMALL_ANOMALOCARIMON_ANIM_INDEX ,DMALL_BIG_MAMEMON_ANIM_INDEX ,DMALL_CHIMAIRAMON_ANIM_INDEX ,DMALL_MAMEMON_ANIM_INDEX ,DMALL_METAL_GREYMON_ANIM_INDEX ,DMALL_METAL_TYRANOMON_ANIM_INDEX ,DMALL_WARU_SEADRAMON_ANIM_INDEX ,DMALL_WERE_GARURUMON_ANIM_INDEX
                },
              };
            case DMALL_ALGOMON_BABYII_ANIM_INDEX:
              return {
                // Stage: Baby II
                .conditions = { .next_evolution_time_sec = 43200 },
                
                .num_animation_indices = 6,
                .animation_indices = {
                  DMALL_ALGOMON_CHILD_ANIM_INDEX ,DMALL_AGUMON_ANIM_INDEX ,DMALL_ALGOMON_CHILD_ANIM_INDEX ,DMALL_GHOSTMON_ANIM_INDEX ,DMALL_LABRAMON_ANIM_INDEX ,DMALL_WORMMON_ANIM_INDEX
                },
              };
            case DMALL_ALGOMON_BABYI_ANIM_INDEX:
              return {
                // Stage: Baby I
                .conditions = { .next_evolution_time_sec = 600 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMALL_ALGOMON_CHILD_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 3,
                .animation_indices = {
                  DMALL_ALGOMON_ADULT_ANIM_INDEX ,DMALL_ALGOMON_ADULT_ANIM_INDEX ,DMALL_DEVIMON_ANIM_INDEX
                },
              };
            case DMALL_ALGOMON_ULTIMATE_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMALL_ALLOMON_X_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 10,
                .animation_indices = {
                  DMALL_TRICERAMON_X_ANIM_INDEX ,DMALL_MAMMON_X_ANIM_INDEX ,DMALL_MAMETYRAMON_ANIM_INDEX ,DMALL_HISYARYUMON_ANIM_INDEX ,DMALL_MAMETYRAMON_ANIM_INDEX ,DMALL_MEGALO_GROWMON_ANIM_INDEX ,DMALL_OROCHIMON_ANIM_INDEX ,DMALL_SKULL_BALUCHIMON_ANIM_INDEX ,DMALL_WARU_MONZAEMON_ANIM_INDEX ,DMALL_ZUDOMON_ANIM_INDEX
                },
              };
            case DMALL_ALPHAMON_OURYUKEN_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMALL_ALPHAMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMALL_ALRAUMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_ZASSOUMON_ANIM_INDEX ,DMALL_GEREMON_ANIM_INDEX ,DMALL_ICEMON_ANIM_INDEX ,DMALL_ICE_DEVIMON_ANIM_INDEX ,DMALL_IGAMON_ANIM_INDEX ,DMALL_KIWIMON_ANIM_INDEX ,DMALL_NUMEMON_ANIM_INDEX ,DMALL_RED_VEGIMON_ANIM_INDEX ,DMALL_SCUMON_ANIM_INDEX ,DMALL_TOGEMON_ANIM_INDEX ,DMALL_VEGIMON_ANIM_INDEX ,DMALL_WIZARMON_ANIM_INDEX ,DMALL_WOODMON_ANIM_INDEX ,DMALL_YANMAMON_ANIM_INDEX ,DMALL_YOUKOMON_ANIM_INDEX
                },
              };
            case DMALL_ANCIENT_BEATMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMALL_ANCIENT_MEGATHERIUMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMALL_ANCIENT_MERMAIMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMALL_ANCIENT_SPHINXMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMALL_ANDIRAMON_DATA_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 12,
                .animation_indices = {
                  DMALL_CHERUBIMON_VIRTUE_ANIM_INDEX ,DMALL_BEELZEBUMON_ANIM_INDEX ,DMALL_CHAOS_DUKEMON_ANIM_INDEX ,DMALL_CHERUBIMON_VICE_ANIM_INDEX ,DMALL_CHERUBIMON_VIRTUE_ANIM_INDEX ,DMALL_DIABLOMON_ANIM_INDEX ,DMALL_DIANAMON_ANIM_INDEX ,DMALL_DUFTMON_ANIM_INDEX ,DMALL_HOUOUMON_ANIM_INDEX ,DMALL_LILITHMON_ANIM_INDEX ,DMALL_SAINT_GALGOMON_ANIM_INDEX ,DMALL_SERAPHIMON_ANIM_INDEX
                },
              };
            case DMALL_ANDIRAMON_VIRUS_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 8,
                .animation_indices = {
                  DMALL_CHERUBIMON_VICE_ANIM_INDEX ,DMALL_CHERUBIMON_VICE_ANIM_INDEX ,DMALL_CHERUBIMON_VIRTUE_ANIM_INDEX ,DMALL_DIABLOMON_ANIM_INDEX ,DMALL_DUFTMON_ANIM_INDEX ,DMALL_HOUOUMON_ANIM_INDEX ,DMALL_ROSEMON_ANIM_INDEX ,DMALL_SAINT_GALGOMON_ANIM_INDEX
                },
              };
            case DMALL_ANDROMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_HI_ANDROMON_ANIM_INDEX ,DMALL_MUGENDRAMON_ANIM_INDEX ,DMALL_HI_ANDROMON_ANIM_INDEX ,DMALL_BLITZ_GREYMON_ANIM_INDEX ,DMALL_BOLTMON_ANIM_INDEX ,DMALL_CHAOSDRAMON_ANIM_INDEX ,DMALL_CRANIUMMON_ANIM_INDEX ,DMALL_GOKUMON_ANIM_INDEX ,DMALL_HI_ANDROMON_ANIM_INDEX ,DMALL_HOLYDRAMON_ANIM_INDEX ,DMALL_METAL_ETEMON_ANIM_INDEX ,DMALL_METAL_GARURUMON_ANIM_INDEX ,DMALL_MUGENDRAMON_ANIM_INDEX ,DMALL_PIEMON_ANIM_INDEX ,DMALL_PLESIOMON_ANIM_INDEX
                },
              };
            case DMALL_ANGEMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_HOLY_ANGEMON_ANIM_INDEX ,DMALL_SKULL_GREYMON_ANIM_INDEX ,DMALL_AERO_V_DRAMON_ANIM_INDEX ,DMALL_ANDROMON_ANIM_INDEX ,DMALL_ANGEWOMON_ANIM_INDEX ,DMALL_ARCHNEMON_ANIM_INDEX ,DMALL_ASURAMON_ANIM_INDEX ,DMALL_BAALMON_ANIM_INDEX ,DMALL_BIG_MAMEMON_ANIM_INDEX ,DMALL_BLUE_MERAMON_ANIM_INDEX ,DMALL_CHIMAIRAMON_ANIM_INDEX ,DMALL_CYBERDRAMON_ANIM_INDEX ,DMALL_DEATH_MERAMON_ANIM_INDEX ,DMALL_DURAMON_ANIM_INDEX ,DMALL_GARUDAMON_ANIM_INDEX
                },
              };
            case DMALL_ANGEWOMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_HOLYDRAMON_ANIM_INDEX ,DMALL_MASTEMON_ANIM_INDEX ,DMALL_BEELZEBUMON_ANIM_INDEX ,DMALL_BELIAL_VAMDEMON_ANIM_INDEX ,DMALL_DARKDRAMON_ANIM_INDEX ,DMALL_GRAND_DRACUMON_ANIM_INDEX ,DMALL_HERAKLE_KABUTERIMON_ANIM_INDEX ,DMALL_HOLYDRAMON_ANIM_INDEX ,DMALL_HOUOUMON_ANIM_INDEX ,DMALL_LILITHMON_ANIM_INDEX ,DMALL_MARIN_ANGEMON_ANIM_INDEX ,DMALL_MASTEMON_ANIM_INDEX ,DMALL_METAL_ETEMON_ANIM_INDEX ,DMALL_MUGENDRAMON_ANIM_INDEX ,DMALL_OMEGAMON_ANIM_INDEX
                },
              };
            case DMALL_ANGEWOMON_X_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 12,
                .animation_indices = {
                  DMALL_CHERUBIMON_VIRTUE_X_ANIM_INDEX ,DMALL_GODDRAMON_X_ANIM_INDEX ,DMALL_OURYUMON_ANIM_INDEX ,DMALL_PLESIOMON_X_ANIM_INDEX ,DMALL_GAIOUMON_ANIM_INDEX ,DMALL_DINOTIGERMON_ANIM_INDEX ,DMALL_HOLYDRAMON_X_ANIM_INDEX ,DMALL_EBEMON_X_ANIM_INDEX ,DMALL_HEXEBLAUMON_ANIM_INDEX ,DMALL_METALLICDRAMON_ANIM_INDEX ,DMALL_NOBLE_PUMPMON_ANIM_INDEX ,DMALL_DINOTIGERMON_ANIM_INDEX
                },
              };
            case DMALL_ANOMALOCARIMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 14,
                .animation_indices = {
                  DMALL_ANCIENT_MERMAIMON_ANIM_INDEX ,DMALL_BLITZ_GREYMON_ANIM_INDEX ,DMALL_BOLTMON_ANIM_INDEX ,DMALL_CTHYLLAMON_ANIM_INDEX ,DMALL_GRANDIS_KUWAGAMON_ANIM_INDEX ,DMALL_GRIFFOMON_ANIM_INDEX ,DMALL_HERAKLE_KABUTERIMON_ANIM_INDEX ,DMALL_METAL_GARURUMON_ANIM_INDEX ,DMALL_METAL_SEADRAMON_ANIM_INDEX ,DMALL_PIEMON_ANIM_INDEX ,DMALL_PLESIOMON_ANIM_INDEX ,DMALL_PUKUMON_ANIM_INDEX ,DMALL_SABER_LEOMON_ANIM_INDEX ,DMALL_WAR_GREYMON_ANIM_INDEX
                },
              };
            case DMALL_ANOMALOCARIMON_X_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_CHERUBIMON_VIRTUE_X_ANIM_INDEX ,DMALL_GODDRAMON_X_ANIM_INDEX ,DMALL_OURYUMON_ANIM_INDEX ,DMALL_PLESIOMON_X_ANIM_INDEX ,DMALL_GAIOUMON_ANIM_INDEX ,DMALL_DINOTIGERMON_ANIM_INDEX ,DMALL_HOLYDRAMON_X_ANIM_INDEX ,DMALL_EBEMON_X_ANIM_INDEX ,DMALL_HEXEBLAUMON_ANIM_INDEX ,DMALL_METALLICDRAMON_ANIM_INDEX ,DMALL_NOBLE_PUMPMON_ANIM_INDEX ,DMALL_CTHYLLAMON_ANIM_INDEX ,DMALL_DINOTIGERMON_ANIM_INDEX ,DMALL_GAIOUMON_ANIM_INDEX ,DMALL_GIGA_SEADRAMON_ANIM_INDEX
                },
              };
            case DMALL_APOCALYMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMALL_APOLLOMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMALL_ARCHNEMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 12,
                .animation_indices = {
                  DMALL_ANCIENT_BEATMON_ANIM_INDEX ,DMALL_APOCALYMON_ANIM_INDEX ,DMALL_BEELZEBUMON_ANIM_INDEX ,DMALL_BELIAL_VAMDEMON_ANIM_INDEX ,DMALL_BLACK_WAR_GREYMON_ANIM_INDEX ,DMALL_BLOOM_LORDMON_ANIM_INDEX ,DMALL_DEMON_ANIM_INDEX ,DMALL_GIGA_SEADRAMON_ANIM_INDEX ,DMALL_LILITHMON_ANIM_INDEX ,DMALL_LOTUSMON_ANIM_INDEX ,DMALL_PIEMON_ANIM_INDEX ,DMALL_RAFFLESIMON_ANIM_INDEX
                },
              };
            case DMALL_ARKADIMON_BABY_ANIM_INDEX:
              return {
                // Stage: Baby II
                .conditions = { .next_evolution_time_sec = 43200 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMALL_ARKADIMON_CHILD_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DMALL_LEOMON_ANIM_INDEX
                },
              };
            case DMALL_ARMADIMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_ANGEMON_ANIM_INDEX ,DMALL_CYCLOMON_ANIM_INDEX ,DMALL_DOKUGUMON_ANIM_INDEX ,DMALL_GEREMON_ANIM_INDEX ,DMALL_GOLD_NUMEMON_ANIM_INDEX ,DMALL_HANUMON_ANIM_INDEX ,DMALL_MEICOOMON_ANIM_INDEX ,DMALL_MONOCHROMON_ANIM_INDEX ,DMALL_NUMEMON_ANIM_INDEX ,DMALL_SCUMON_ANIM_INDEX ,DMALL_SHEEPMON_ANIM_INDEX ,DMALL_SHELLMON_ANIM_INDEX ,DMALL_TANKMON_ANIM_INDEX ,DMALL_THUNDERBALLMON_ANIM_INDEX ,DMALL_TOGEMON_ANIM_INDEX
                },
              };
            case DMALL_ARMAGEMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMALL_ASTAMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 6,
                .animation_indices = {
                  DMALL_ANCIENT_MEGATHERIUMON_ANIM_INDEX ,DMALL_BEELZEBUMON_ANIM_INDEX ,DMALL_GRAND_DRACUMON_ANIM_INDEX ,DMALL_MEGIDRAMON_ANIM_INDEX ,DMALL_SABER_LEOMON_ANIM_INDEX ,DMALL_VENOM_VAMDEMON_ANIM_INDEX
                },
              };
            case DMALL_ASURAMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 5,
                .animation_indices = {
                  DMALL_BOLTMON_ANIM_INDEX ,DMALL_MARIN_ANGEMON_ANIM_INDEX ,DMALL_METAL_GARURUMON_ANIM_INDEX ,DMALL_OURYUMON_ANIM_INDEX ,DMALL_WAR_GREYMON_ANIM_INDEX
                },
              };
            case DMALL_ATLUR_KABUTERIMON_BLUE_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 8,
                .animation_indices = {
                  DMALL_HERAKLE_KABUTERIMON_ANIM_INDEX ,DMALL_ANCIENT_BEATMON_ANIM_INDEX ,DMALL_CRANIUMMON_ANIM_INDEX ,DMALL_DORUGORAMON_ANIM_INDEX ,DMALL_HERAKLE_KABUTERIMON_ANIM_INDEX ,DMALL_HOLYDRAMON_ANIM_INDEX ,DMALL_SAINT_GALGOMON_ANIM_INDEX ,DMALL_SKULL_MAMMON_ANIM_INDEX
                },
              };
            case DMALL_ATLUR_KABUTERIMON_RED_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 12,
                .animation_indices = {
                  DMALL_HERAKLE_KABUTERIMON_ANIM_INDEX ,DMALL_ANCIENT_BEATMON_ANIM_INDEX ,DMALL_CHAOS_DUKEMON_ANIM_INDEX ,DMALL_CRANIUMMON_ANIM_INDEX ,DMALL_DUKEMON_ANIM_INDEX ,DMALL_GRANDIS_KUWAGAMON_ANIM_INDEX ,DMALL_HERAKLE_KABUTERIMON_ANIM_INDEX ,DMALL_HOLYDRAMON_ANIM_INDEX ,DMALL_ROSEMON_ANIM_INDEX ,DMALL_SAINT_GALGOMON_ANIM_INDEX ,DMALL_VENOM_VAMDEMON_ANIM_INDEX ,DMALL_WAR_GREYMON_ANIM_INDEX
                },
              };
            case DMALL_AXEKNIGHTMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 3,
                .animation_indices = {
                  DMALL_DARKNESS_BAGRAMON_ANIM_INDEX ,DMALL_BEELZEBUMON_ANIM_INDEX ,DMALL_DARKNESS_BAGRAMON_ANIM_INDEX
                },
              };
            case DMALL_BAALMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 3,
                .animation_indices = {
                  DMALL_BEELZEBUMON_ANIM_INDEX ,DMALL_NOBLE_PUMPMON_ANIM_INDEX ,DMALL_PIEMON_ANIM_INDEX
                },
              };
            case DMALL_BABOONGAMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 2,
                .animation_indices = {
                  DMALL_GOGMAMON_ANIM_INDEX ,DMALL_MACH_GAOGAMON_ANIM_INDEX
                },
              };
            case DMALL_BABYDMON_ANIM_INDEX:
              return {
                // Stage: Baby II
                .conditions = { .next_evolution_time_sec = 43200 },
                
                .num_animation_indices = 2,
                .animation_indices = {
                  DMALL_HACKMON_ANIM_INDEX ,DMALL_OTAMAMON_ANIM_INDEX
                },
              };
            case DMALL_BAGRAMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = 230400 },
                
                .num_animation_indices = 2,
                .animation_indices = {
                  DMALL_DARKNESS_BAGRAMON_ANIM_INDEX ,DMALL_BARBAMON_X_ANIM_INDEX
                },
              };
            case DMALL_BAKEMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_VAMDEMON_ANIM_INDEX ,DMALL_GIROMON_ANIM_INDEX ,DMALL_AERO_V_DRAMON_ANIM_INDEX ,DMALL_ANOMALOCARIMON_ANIM_INDEX ,DMALL_ASTAMON_ANIM_INDEX ,DMALL_ASURAMON_ANIM_INDEX ,DMALL_BAALMON_ANIM_INDEX ,DMALL_BEOWOLFMON_ANIM_INDEX ,DMALL_BIG_MAMEMON_ANIM_INDEX ,DMALL_BLOSSOMON_ANIM_INDEX ,DMALL_BLUE_MERAMON_ANIM_INDEX ,DMALL_CHIMAIRAMON_ANIM_INDEX ,DMALL_DAGOMON_ANIM_INDEX ,DMALL_DARK_KNIGHTMON_ANIM_INDEX ,DMALL_DEATH_MERAMON_ANIM_INDEX
                },
              };
            case DMALL_BAKUMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_MONOCHROMON_ANIM_INDEX ,DMALL_ANGEMON_ANIM_INDEX ,DMALL_BAKEMON_ANIM_INDEX ,DMALL_BLACK_TAILMON_ANIM_INDEX ,DMALL_DOBERMON_ANIM_INDEX ,DMALL_DOGMON_ANIM_INDEX ,DMALL_GARURUMON_ANIM_INDEX ,DMALL_GURURUMON_ANIM_INDEX ,DMALL_HANUMON_ANIM_INDEX ,DMALL_KYUBIMON_ANIM_INDEX ,DMALL_LEOMON_ANIM_INDEX ,DMALL_MEICOOMON_ANIM_INDEX ,DMALL_MERAMON_ANIM_INDEX ,DMALL_NUMEMON_ANIM_INDEX ,DMALL_MONOCHROMON_ANIM_INDEX
                },
              };
            case DMALL_BANCHO_LEOMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = 230400 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DMALL_CHAOSMON_ANIM_INDEX
                },
              };
            case DMALL_BANCHO_LILIMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMALL_BANCHO_MAMEMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMALL_BARBAMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMALL_BARBAMON_X_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMALL_BEARMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_GRYZMON_ANIM_INDEX ,DMALL_DOBERMON_ANIM_INDEX ,DMALL_GALGOMON_ANIM_INDEX ,DMALL_GAOGAMON_ANIM_INDEX ,DMALL_GARURUMON_ANIM_INDEX ,DMALL_GREYMON_BLUE_ANIM_INDEX ,DMALL_GRYZMON_ANIM_INDEX ,DMALL_HYOUGAMON_ANIM_INDEX ,DMALL_KIWIMON_ANIM_INDEX ,DMALL_LEOMON_ANIM_INDEX ,DMALL_MEICOOMON_ANIM_INDEX ,DMALL_MIKEMON_ANIM_INDEX ,DMALL_NUMEMON_ANIM_INDEX ,DMALL_SCUMON_ANIM_INDEX ,DMALL_STARMON_ANIM_INDEX
                },
              };
            case DMALL_BEEL_STARMON_X_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = 230400 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DMALL_DIABLOMON_X_ANIM_INDEX
                },
              };
            case DMALL_BEELZEBUMON_BLAST_MODE_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMALL_BEELZEBUMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMALL_BEELZEBUMON_X_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = 230400 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DMALL_DIABLOMON_X_ANIM_INDEX
                },
              };
            case DMALL_BELIAL_VAMDEMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = 230400 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DMALL_DIABLOMON_X_ANIM_INDEX
                },
              };
            case DMALL_BELPHEMON_RAGE_MODE_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMALL_BELPHEMON_X_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMALL_BEOWOLFMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 3,
                .animation_indices = {
                  DMALL_ANCIENT_MERMAIMON_ANIM_INDEX ,DMALL_DUFTMON_ANIM_INDEX ,DMALL_METAL_GARURUMON_ANIM_INDEX
                },
              };
            case DMALL_BIBIMON_ANIM_INDEX:
              return {
                // Stage: Baby II
                .conditions = { .next_evolution_time_sec = 43200 },
                
                .num_animation_indices = 2,
                .animation_indices = {
                  DMALL_PULSEMON_ANIM_INDEX ,DMALL_PULSEMON_ANIM_INDEX
                },
              };
            case DMALL_BIG_MAMEMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 14,
                .animation_indices = {
                  DMALL_BOLTMON_ANIM_INDEX ,DMALL_CRES_GARURUMON_ANIM_INDEX ,DMALL_GRAND_LOCOMON_ANIM_INDEX ,DMALL_GRIFFOMON_ANIM_INDEX ,DMALL_HI_ANDROMON_ANIM_INDEX ,DMALL_METAL_GARURUMON_ANIM_INDEX ,DMALL_METAL_SEADRAMON_ANIM_INDEX ,DMALL_PLATINUM_NUMEMON_ANIM_INDEX ,DMALL_PLESIOMON_ANIM_INDEX ,DMALL_PRINCE_MAMEMON_ANIM_INDEX ,DMALL_SABER_LEOMON_ANIM_INDEX ,DMALL_SAINT_GALGOMON_ANIM_INDEX ,DMALL_VENOM_VAMDEMON_ANIM_INDEX ,DMALL_WAR_GREYMON_ANIM_INDEX
                },
              };
            case DMALL_BIRDRAMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_GARUDAMON_ANIM_INDEX ,DMALL_SKULL_GREYMON_ANIM_INDEX ,DMALL_AERO_V_DRAMON_ANIM_INDEX ,DMALL_ANDROMON_ANIM_INDEX ,DMALL_ANGEWOMON_ANIM_INDEX ,DMALL_ASURAMON_ANIM_INDEX ,DMALL_ATLUR_KABUTERIMON_BLUE_ANIM_INDEX ,DMALL_ATLUR_KABUTERIMON_RED_ANIM_INDEX ,DMALL_BAALMON_ANIM_INDEX ,DMALL_BIG_MAMEMON_ANIM_INDEX ,DMALL_BLOSSOMON_ANIM_INDEX ,DMALL_BLUE_MERAMON_ANIM_INDEX ,DMALL_CHIMAIRAMON_ANIM_INDEX ,DMALL_CYBERDRAMON_ANIM_INDEX ,DMALL_DEATH_MERAMON_ANIM_INDEX
                },
              };
            case DMALL_BITMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 3,
                .animation_indices = {
                  DMALL_ASURAMON_ANIM_INDEX ,DMALL_GARUDAMON_ANIM_INDEX ,DMALL_KNIGHTMON_ANIM_INDEX
                },
              };
            case DMALL_BLACK_GALGOMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 5,
                .animation_indices = {
                  DMALL_BLACK_RAPIDMON_ANIM_INDEX ,DMALL_CYBERDRAMON_ANIM_INDEX ,DMALL_METAL_GREYMON_VIRUS_ANIM_INDEX ,DMALL_NANOMON_ANIM_INDEX ,DMALL_PAILDRAMON_ANIM_INDEX
                },
              };
            case DMALL_BLACK_GAOGAMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 2,
                .animation_indices = {
                  DMALL_BLACK_MACH_GAOGAMON_ANIM_INDEX ,DMALL_BLACK_MACH_GAOGAMON_ANIM_INDEX
                },
              };
            case DMALL_BLACK_GROWMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 12,
                .animation_indices = {
                  DMALL_BLACK_MEGALO_GROWMON_ANIM_INDEX ,DMALL_BLACK_MEGALO_GROWMON_ANIM_INDEX ,DMALL_DEATH_MERAMON_ANIM_INDEX ,DMALL_GRADEMON_ANIM_INDEX ,DMALL_MEGALO_GROWMON_ANIM_INDEX ,DMALL_MEGALO_GROWMON_ORANGE_ANIM_INDEX ,DMALL_MEPHISMON_ANIM_INDEX ,DMALL_MONZAEMON_ANIM_INDEX ,DMALL_PANDAMON_ANIM_INDEX ,DMALL_RIZE_GREYMON_ANIM_INDEX ,DMALL_SKULL_GREYMON_ANIM_INDEX ,DMALL_VAMDEMON_ANIM_INDEX
                },
              };
            case DMALL_BLACK_GUILMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 2,
                .animation_indices = {
                  DMALL_BLACK_GROWMON_ANIM_INDEX ,DMALL_BLACK_GROWMON_ANIM_INDEX
                },
              };
            case DMALL_BLACK_KING_NUMEMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 7,
                .animation_indices = {
                  DMALL_PLATINUM_NUMEMON_ANIM_INDEX ,DMALL_CTHYLLAMON_ANIM_INDEX ,DMALL_GIGA_SEADRAMON_ANIM_INDEX ,DMALL_METAL_ETEMON_ANIM_INDEX ,DMALL_PLATINUM_NUMEMON_ANIM_INDEX ,DMALL_PRINCE_MAMEMON_ANIM_INDEX ,DMALL_SHIN_MONZAEMON_ANIM_INDEX
                },
              };
            case DMALL_BLACK_MACH_GAOGAMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 2,
                .animation_indices = {
                  DMALL_CHAOSDRAMON_ANIM_INDEX ,DMALL_MUGENDRAMON_ANIM_INDEX
                },
              };
            case DMALL_BLACK_MEGALO_GROWMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 10,
                .animation_indices = {
                  DMALL_CHAOS_DUKEMON_ANIM_INDEX ,DMALL_BEELZEBUMON_ANIM_INDEX ,DMALL_BLACK_WAR_GREYMON_ANIM_INDEX ,DMALL_CHAOS_DUKEMON_ANIM_INDEX ,DMALL_CHAOSDRAMON_ANIM_INDEX ,DMALL_DARKDRAMON_ANIM_INDEX ,DMALL_DUKEMON_ANIM_INDEX ,DMALL_GAIOUMON_ANIM_INDEX ,DMALL_MEGIDRAMON_ANIM_INDEX ,DMALL_MUGENDRAMON_ANIM_INDEX
                },
              };
            case DMALL_BLACK_RAPIDMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 6,
                .animation_indices = {
                  DMALL_BLACK_SAINT_GALGOMON_ANIM_INDEX ,DMALL_CHAOSDRAMON_ANIM_INDEX ,DMALL_METAL_GARURUMON_ANIM_INDEX ,DMALL_MUGENDRAMON_ANIM_INDEX ,DMALL_SAINT_GALGOMON_ANIM_INDEX ,DMALL_SERAPHIMON_ANIM_INDEX
                },
              };
            case DMALL_BLACK_SAINT_GALGOMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMALL_BLACK_SERAPHIMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMALL_BLACK_TAILMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 9,
                .animation_indices = {
                  DMALL_CYBERDRAMON_ANIM_INDEX ,DMALL_DARK_SUPERSTARMON_ANIM_INDEX ,DMALL_DEATH_MERAMON_ANIM_INDEX ,DMALL_HOLY_ANGEMON_ANIM_INDEX ,DMALL_KNIGHTMON_ANIM_INDEX ,DMALL_NEO_DEVIMON_ANIM_INDEX ,DMALL_PANDAMON_ANIM_INDEX ,DMALL_SKULL_BALUCHIMON_ANIM_INDEX ,DMALL_WARU_MONZAEMON_ANIM_INDEX
                },
              };
            case DMALL_BLACK_WAR_GREYMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMALL_BLACK_WAR_GREYMON_X_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = 230400 },
                
                .num_animation_indices = 3,
                .animation_indices = {
                  DMALL_DEMON_X_ANIM_INDEX ,DMALL_RASENMON_ANIM_INDEX ,DMALL_BARBAMON_X_ANIM_INDEX
                },
              };
            case DMALL_BLITZ_GREYMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = 230400 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DMALL_OMEGAMON_ALTER_S_ANIM_INDEX
                },
              };
            case DMALL_BLOOM_LORDMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMALL_BLOSSOMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 13,
                .animation_indices = {
                  DMALL_BARBAMON_ANIM_INDEX ,DMALL_BLOOM_LORDMON_ANIM_INDEX ,DMALL_BOLTMON_ANIM_INDEX ,DMALL_GRIFFOMON_ANIM_INDEX ,DMALL_LILITHMON_ANIM_INDEX ,DMALL_LOTUSMON_ANIM_INDEX ,DMALL_METAL_GARURUMON_ANIM_INDEX ,DMALL_METAL_SEADRAMON_ANIM_INDEX ,DMALL_PLESIOMON_ANIM_INDEX ,DMALL_RAFFLESIMON_ANIM_INDEX ,DMALL_ROSEMON_ANIM_INDEX ,DMALL_SABER_LEOMON_ANIM_INDEX ,DMALL_ULFORCE_V_DRAMON_ANIM_INDEX
                },
              };
            case DMALL_BLUCOMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 14,
                .animation_indices = {
                  DMALL_PALEDRAMON_ANIM_INDEX ,DMALL_SIESAMON_X_ANIM_INDEX ,DMALL_MERAMON_X_ANIM_INDEX ,DMALL_DORUGAMON_ANIM_INDEX ,DMALL_PTERANOMON_X_ANIM_INDEX ,DMALL_TOGEMON_X_ANIM_INDEX ,DMALL_OMEKAMON_ANIM_INDEX ,DMALL_PALEDRAMON_ANIM_INDEX ,DMALL_JAZARDMON_ANIM_INDEX ,DMALL_GINRYUMON_ANIM_INDEX ,DMALL_HYOUGAMON_ANIM_INDEX ,DMALL_OMEKAMON_ANIM_INDEX ,DMALL_PALEDRAMON_ANIM_INDEX ,DMALL_YUKIDARUMON_ANIM_INDEX
                },
              };
            case DMALL_BLUE_MERAMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 9,
                .animation_indices = {
                  DMALL_BARBAMON_ANIM_INDEX ,DMALL_BOLTMON_ANIM_INDEX ,DMALL_DARKDRAMON_ANIM_INDEX ,DMALL_DEMON_ANIM_INDEX ,DMALL_GANKOOMON_ANIM_INDEX ,DMALL_HOUOUMON_ANIM_INDEX ,DMALL_LEVIAMON_ANIM_INDEX ,DMALL_PIEMON_ANIM_INDEX ,DMALL_ROSEMON_ANIM_INDEX
                },
              };
            case DMALL_BOLTMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMALL_BOMBMON_ANIM_INDEX:
              return {
                // Stage: Baby I
                .conditions = { .next_evolution_time_sec = 600 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMALL_BOMMON_ANIM_INDEX:
              return {
                // Stage: Baby I
                .conditions = { .next_evolution_time_sec = 600 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMALL_BOUTMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 2,
                .animation_indices = {
                  DMALL_KAZUCHIMON_ANIM_INDEX ,DMALL_KAZUCHIMON_ANIM_INDEX
                },
              };
            case DMALL_BRYWELUDRAMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMALL_BUBBMON_ANIM_INDEX:
              return {
                // Stage: Baby I
                .conditions = { .next_evolution_time_sec = 600 },
                
                .num_animation_indices = 5,
                .animation_indices = {
                  DMALL_MOCHIMON_ANIM_INDEX ,DMALL_MOCHIMON_ANIM_INDEX ,DMALL_NYAROMON_ANIM_INDEX ,DMALL_PYOCOMON_ANIM_INDEX ,DMALL_TANEMON_ANIM_INDEX
                },
              };
            case DMALL_BUDMON_ANIM_INDEX:
              return {
                // Stage: Baby II
                .conditions = { .next_evolution_time_sec = 43200 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_AGUMON_ANIM_INDEX ,DMALL_GOMAMON_ANIM_INDEX ,DMALL_LALAMON_ANIM_INDEX ,DMALL_YUKI_AGUMON_ANIM_INDEX ,DMALL_AGUMON_ANIM_INDEX ,DMALL_DOKUNEMON_ANIM_INDEX ,DMALL_GAOMON_ANIM_INDEX ,DMALL_GOMAMON_ANIM_INDEX ,DMALL_HAGURUMON_ANIM_INDEX ,DMALL_LALAMON_ANIM_INDEX ,DMALL_MUSHMON_ANIM_INDEX ,DMALL_PALMON_ANIM_INDEX ,DMALL_PIYOMON_ANIM_INDEX ,DMALL_TENTOMON_ANIM_INDEX ,DMALL_WORMMON_ANIM_INDEX
                },
              };
            case DMALL_BURGERMON_MAMA_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 2,
                .animation_indices = {
                  DMALL_DIGITAMAMON_ANIM_INDEX ,DMALL_JYAGAMON_ANIM_INDEX
                },
              };
            case DMALL_BURGERMON_PAPA_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 2,
                .animation_indices = {
                  DMALL_DIGITAMAMON_ANIM_INDEX ,DMALL_JYAGAMON_ANIM_INDEX
                },
              };
            case DMALL_CANDMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_BAKEMON_ANIM_INDEX ,DMALL_MERAMON_ANIM_INDEX ,DMALL_WIZARMON_ANIM_INDEX ,DMALL_AIRDRAMON_ANIM_INDEX ,DMALL_BAKEMON_ANIM_INDEX ,DMALL_BIRDRAMON_ANIM_INDEX ,DMALL_BLACK_GROWMON_ANIM_INDEX ,DMALL_CLOCKMON_ANIM_INDEX ,DMALL_DEVIMON_ANIM_INDEX ,DMALL_GAOGAMON_ANIM_INDEX ,DMALL_GARURUMON_ANIM_INDEX ,DMALL_GAWAPPAMON_ANIM_INDEX ,DMALL_GEO_GREYMON_ANIM_INDEX ,DMALL_GROWMON_ANIM_INDEX ,DMALL_GUARDROMON_ANIM_INDEX
                },
              };
            case DMALL_CANNONBEEMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_RAPIDMON_X_ANIM_INDEX ,DMALL_JUSTIMON_X_ANIM_INDEX ,DMALL_ALPHAMON_ANIM_INDEX ,DMALL_HOUOUMON_X_ANIM_INDEX ,DMALL_TIGER_VESPAMON_ANIM_INDEX ,DMALL_GAIOUMON_ANIM_INDEX ,DMALL_DINOTIGERMON_ANIM_INDEX ,DMALL_HOLYDRAMON_X_ANIM_INDEX ,DMALL_EBEMON_X_ANIM_INDEX ,DMALL_HEXEBLAUMON_ANIM_INDEX ,DMALL_METALLICDRAMON_ANIM_INDEX ,DMALL_NOBLE_PUMPMON_ANIM_INDEX ,DMALL_ALPHAMON_ANIM_INDEX ,DMALL_ANCIENT_BEATMON_ANIM_INDEX ,DMALL_CHAOSDRAMON_ANIM_INDEX
                },
              };
            case DMALL_CAPRIMON_ANIM_INDEX:
              return {
                // Stage: Baby II
                .conditions = { .next_evolution_time_sec = 43200 },
                
                .num_animation_indices = 8,
                .animation_indices = {
                  DMALL_ARMADIMON_ANIM_INDEX ,DMALL_COMMANDRAMON_ANIM_INDEX ,DMALL_HAGURUMON_ANIM_INDEX ,DMALL_IMPMON_ANIM_INDEX ,DMALL_KOKABUTERIMON_ANIM_INDEX ,DMALL_KOKUWAMON_ANIM_INDEX ,DMALL_PHASCOMON_ANIM_INDEX ,DMALL_SOLARMON_ANIM_INDEX
                },
              };
            case DMALL_CATCHMAMEMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 3,
                .animation_indices = {
                  DMALL_PINOCHIMON_ANIM_INDEX ,DMALL_PLATINUM_NUMEMON_ANIM_INDEX ,DMALL_PRINCE_MAMEMON_ANIM_INDEX
                },
              };
            case DMALL_CATURAMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 5,
                .animation_indices = {
                  DMALL_BEELZEBUMON_ANIM_INDEX ,DMALL_CHAOSDRAMON_ANIM_INDEX ,DMALL_HI_ANDROMON_ANIM_INDEX ,DMALL_SABER_LEOMON_ANIM_INDEX ,DMALL_SAKUYAMON_ANIM_INDEX
                },
              };
            case DMALL_CENTALMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_GIROMON_ANIM_INDEX ,DMALL_AERO_V_DRAMON_ANIM_INDEX ,DMALL_ANDROMON_ANIM_INDEX ,DMALL_ANOMALOCARIMON_ANIM_INDEX ,DMALL_ASURAMON_ANIM_INDEX ,DMALL_BEOWOLFMON_ANIM_INDEX ,DMALL_BIG_MAMEMON_ANIM_INDEX ,DMALL_BLACK_RAPIDMON_ANIM_INDEX ,DMALL_CYBERDRAMON_ANIM_INDEX ,DMALL_DAGOMON_ANIM_INDEX ,DMALL_DARK_KNIGHTMON_ANIM_INDEX ,DMALL_DURAMON_ANIM_INDEX ,DMALL_GARUDAMON_ANIM_INDEX ,DMALL_GERBEMON_ANIM_INDEX ,DMALL_GIROMON_ANIM_INDEX
                },
              };
            case DMALL_CERBERUMON_X_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 9,
                .animation_indices = {
                  DMALL_SAKUYAMON_X_ANIM_INDEX ,DMALL_SLEIPMON_X_ANIM_INDEX ,DMALL_BELIAL_VAMDEMON_ANIM_INDEX ,DMALL_JESMON_X_ANIM_INDEX ,DMALL_PLATINUM_NUMEMON_ANIM_INDEX ,DMALL_BARBAMON_ANIM_INDEX ,DMALL_BELIAL_VAMDEMON_ANIM_INDEX ,DMALL_PLATINUM_NUMEMON_ANIM_INDEX ,DMALL_WAR_GREYMON_ANIM_INDEX
                },
              };
            case DMALL_CHAMBLEMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DMALL_MARIN_CHIMAIRAMON_ANIM_INDEX
                },
              };
            case DMALL_CHAOSDRAMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMALL_CHAOSDRAMON_X_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = 230400 },
                
                .num_animation_indices = 3,
                .animation_indices = {
                  DMALL_DEMON_X_ANIM_INDEX ,DMALL_LUCEMON_X_ANIM_INDEX ,DMALL_DIABLOMON_X_ANIM_INDEX
                },
              };
            case DMALL_CHAOS_DUKEMON_CORE_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMALL_CHAOS_DUKEMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMALL_CHAOSMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMALL_CHERUBIMON_VICE_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMALL_CHERUBIMON_VICE_X_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = 230400 },
                
                .num_animation_indices = 2,
                .animation_indices = {
                  DMALL_BELPHEMON_X_ANIM_INDEX ,DMALL_BARBAMON_X_ANIM_INDEX
                },
              };
            case DMALL_CHERUBIMON_VIRTUE_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMALL_CHERUBIMON_VIRTUE_X_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = 230400 },
                
                .num_animation_indices = 8,
                .animation_indices = {
                  DMALL_ULFORCE_V_DRAMON_X_ANIM_INDEX ,DMALL_EXAMON_X_ANIM_INDEX ,DMALL_DUFTMON_X_ANIM_INDEX ,DMALL_SLEIPMON_X_ANIM_INDEX ,DMALL_JESMON_X_ANIM_INDEX ,DMALL_OMEGAMON_X_ANIM_INDEX ,DMALL_ALPHAMON_OURYUKEN_ANIM_INDEX ,DMALL_JESMON_GX_ANIM_INDEX
                },
              };
            case DMALL_CHIBICKMON_ANIM_INDEX:
              return {
                // Stage: Baby I
                .conditions = { .next_evolution_time_sec = 600 },
                
                .num_animation_indices = 2,
                .animation_indices = {
                  DMALL_PICKMON_ANIM_INDEX ,DMALL_PICKMON_ANIM_INDEX
                },
              };
            case DMALL_CHIBIMON_ANIM_INDEX:
              return {
                // Stage: Baby II
                .conditions = { .next_evolution_time_sec = 43200 },
                
                .num_animation_indices = 2,
                .animation_indices = {
                  DMALL_V_MON_ANIM_INDEX ,DMALL_V_MON_ANIM_INDEX
                },
              };
            case DMALL_CHICCHIMON_ANIM_INDEX:
              return {
                // Stage: Baby II
                .conditions = { .next_evolution_time_sec = 43200 },
                
                .num_animation_indices = 4,
                .animation_indices = {
                  DMALL_HYOKOMON_ANIM_INDEX ,DMALL_HYOKOMON_ANIM_INDEX ,DMALL_MUCHOMON_ANIM_INDEX ,DMALL_PENMON_ANIM_INDEX
                },
              };
            case DMALL_CHICOMON_ANIM_INDEX:
              return {
                // Stage: Baby I
                .conditions = { .next_evolution_time_sec = 600 },
                
                .num_animation_indices = 2,
                .animation_indices = {
                  DMALL_CHIBIMON_ANIM_INDEX ,DMALL_CHIBIMON_ANIM_INDEX
                },
              };
            case DMALL_CHIMAIRAMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_MILLENNIUMON_ANIM_INDEX ,DMALL_BANCHO_LEOMON_ANIM_INDEX ,DMALL_MILLENNIUMON_ANIM_INDEX ,DMALL_ARMAGEMON_ANIM_INDEX ,DMALL_BANCHO_LEOMON_ANIM_INDEX ,DMALL_CHAOSDRAMON_ANIM_INDEX ,DMALL_CHAOSMON_ANIM_INDEX ,DMALL_DEATHMON_ANIM_INDEX ,DMALL_DEATHMON_BLACK_ANIM_INDEX ,DMALL_GRANDIS_KUWAGAMON_ANIM_INDEX ,DMALL_MEGIDRAMON_ANIM_INDEX ,DMALL_METAL_ETEMON_ANIM_INDEX ,DMALL_MILLENNIUMON_ANIM_INDEX ,DMALL_MUGENDRAMON_ANIM_INDEX ,DMALL_PLESIOMON_ANIM_INDEX
                },
              };
            case DMALL_CHOCOMON_ANIM_INDEX:
              return {
                // Stage: Baby II
                .conditions = { .next_evolution_time_sec = 43200 },
                
                .num_animation_indices = 12,
                .animation_indices = {
                  DMALL_LOPMON_ANIM_INDEX ,DMALL_LOPMON_X_ANIM_INDEX ,DMALL_SHAKOMON_X_ANIM_INDEX ,DMALL_RYUDAMON_ANIM_INDEX ,DMALL_BLUCOMON_ANIM_INDEX ,DMALL_JAZAMON_ANIM_INDEX ,DMALL_BLUCOMON_ANIM_INDEX ,DMALL_JAZAMON_ANIM_INDEX ,DMALL_LOPMON_ANIM_INDEX ,DMALL_PICO_DEVIMON_ANIM_INDEX ,DMALL_RYUDAMON_ANIM_INDEX ,DMALL_WORMMON_ANIM_INDEX
                },
              };
            case DMALL_CHO_HAKKAIMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 2,
                .animation_indices = {
                  DMALL_BELIAL_VAMDEMON_ANIM_INDEX ,DMALL_PLATINUM_NUMEMON_ANIM_INDEX
                },
              };
            case DMALL_CHOROMON_ANIM_INDEX:
              return {
                // Stage: Baby I
                .conditions = { .next_evolution_time_sec = 600 },
                
                .num_animation_indices = 3,
                .animation_indices = {
                  DMALL_CAPRIMON_ANIM_INDEX ,DMALL_MOCHIMON_ANIM_INDEX ,DMALL_PAGUMON_ANIM_INDEX
                },
              };
            case DMALL_CLEAR_AGUMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_ANGEMON_ANIM_INDEX ,DMALL_BLACK_GALGOMON_ANIM_INDEX ,DMALL_CLOCKMON_ANIM_INDEX ,DMALL_DOGMON_ANIM_INDEX ,DMALL_GEO_GREYMON_ANIM_INDEX ,DMALL_GEREMON_ANIM_INDEX ,DMALL_GREYMON_ANIM_INDEX ,DMALL_GREYMON_BLUE_ANIM_INDEX ,DMALL_GROWMON_ORANGE_ANIM_INDEX ,DMALL_GUARDROMON_ANIM_INDEX ,DMALL_GUARDROMON_GOLD_ANIM_INDEX ,DMALL_HYOUGAMON_ANIM_INDEX ,DMALL_ICE_DEVIMON_ANIM_INDEX ,DMALL_IGAMON_ANIM_INDEX ,DMALL_NUMEMON_ANIM_INDEX
                },
              };
            case DMALL_CLOCKMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_AERO_V_DRAMON_ANIM_INDEX ,DMALL_ANDROMON_ANIM_INDEX ,DMALL_ANOMALOCARIMON_ANIM_INDEX ,DMALL_ASURAMON_ANIM_INDEX ,DMALL_BEOWOLFMON_ANIM_INDEX ,DMALL_BIG_MAMEMON_ANIM_INDEX ,DMALL_CYBERDRAMON_ANIM_INDEX ,DMALL_DAGOMON_ANIM_INDEX ,DMALL_DARK_KNIGHTMON_ANIM_INDEX ,DMALL_DEATH_MERAMON_ANIM_INDEX ,DMALL_DURAMON_ANIM_INDEX ,DMALL_GARUDAMON_ANIM_INDEX ,DMALL_GERBEMON_ANIM_INDEX ,DMALL_GIROMON_ANIM_INDEX ,DMALL_HANGYOMON_ANIM_INDEX
                },
              };
            case DMALL_COCOMON_ANIM_INDEX:
              return {
                // Stage: Baby I
                .conditions = { .next_evolution_time_sec = 600 },
                
                .num_animation_indices = 3,
                .animation_indices = {
                  DMALL_CHOCOMON_ANIM_INDEX ,DMALL_CHOCOMON_ANIM_INDEX ,DMALL_CHOCOMON_ANIM_INDEX
                },
              };
            case DMALL_COELAMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_MEGADRAMON_ANIM_INDEX ,DMALL_AERO_V_DRAMON_ANIM_INDEX ,DMALL_ANDROMON_ANIM_INDEX ,DMALL_ANOMALOCARIMON_ANIM_INDEX ,DMALL_ASURAMON_ANIM_INDEX ,DMALL_BEOWOLFMON_ANIM_INDEX ,DMALL_BIG_MAMEMON_ANIM_INDEX ,DMALL_CHIMAIRAMON_ANIM_INDEX ,DMALL_CYBERDRAMON_ANIM_INDEX ,DMALL_DAGOMON_ANIM_INDEX ,DMALL_DARK_KNIGHTMON_ANIM_INDEX ,DMALL_DURAMON_ANIM_INDEX ,DMALL_GARUDAMON_ANIM_INDEX ,DMALL_GERBEMON_ANIM_INDEX ,DMALL_GIROMON_ANIM_INDEX
                },
              };
            case DMALL_COMMANDRAMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 7,
                .animation_indices = {
                  DMALL_CLOCKMON_ANIM_INDEX ,DMALL_DOBERMON_ANIM_INDEX ,DMALL_GREYMON_ANIM_INDEX ,DMALL_GUARDROMON_ANIM_INDEX ,DMALL_HANUMON_ANIM_INDEX ,DMALL_MONOCHROMON_ANIM_INDEX ,DMALL_NUMEMON_ANIM_INDEX
                },
              };
            case DMALL_CORONAMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 10,
                .animation_indices = {
                  DMALL_FIRAMON_ANIM_INDEX ,DMALL_BIRDRAMON_ANIM_INDEX ,DMALL_FIRAMON_ANIM_INDEX ,DMALL_GAOGAMON_ANIM_INDEX ,DMALL_GEO_GREYMON_ANIM_INDEX ,DMALL_GROWMON_ANIM_INDEX ,DMALL_LEOMON_ANIM_INDEX ,DMALL_LYNXMON_ANIM_INDEX ,DMALL_MERAMON_ANIM_INDEX ,DMALL_PIDMON_ANIM_INDEX
                },
              };
            case DMALL_COTSUCOMON_ANIM_INDEX:
              return {
                // Stage: Baby I
                .conditions = { .next_evolution_time_sec = 600 },
                
                .num_animation_indices = 2,
                .animation_indices = {
                  DMALL_KAKKINMON_ANIM_INDEX ,DMALL_KAKKINMON_ANIM_INDEX
                },
              };
            case DMALL_CRANIUMMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMALL_CRANIUMMON_X_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = 230400 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DMALL_ALPHAMON_ANIM_INDEX
                },
              };
            case DMALL_CRESCEMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 14,
                .animation_indices = {
                  DMALL_DIANAMON_ANIM_INDEX ,DMALL_ANCIENT_MEGATHERIUMON_ANIM_INDEX ,DMALL_BOLTMON_ANIM_INDEX ,DMALL_CHERUBIMON_VIRTUE_ANIM_INDEX ,DMALL_DIANAMON_ANIM_INDEX ,DMALL_GRIFFOMON_ANIM_INDEX ,DMALL_HEXEBLAUMON_ANIM_INDEX ,DMALL_LEVIAMON_ANIM_INDEX ,DMALL_METAL_GARURUMON_ANIM_INDEX ,DMALL_METAL_SEADRAMON_ANIM_INDEX ,DMALL_PLESIOMON_ANIM_INDEX ,DMALL_ROSEMON_ANIM_INDEX ,DMALL_SKULL_MAMMON_ANIM_INDEX ,DMALL_SABER_LEOMON_ANIM_INDEX
                },
              };
            case DMALL_CRES_GARURUMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = 230400 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DMALL_OMEGAMON_ALTER_S_ANIM_INDEX
                },
              };
            case DMALL_CRYS_PALEDRAMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_HEXEBLAUMON_ANIM_INDEX ,DMALL_RAPIDMON_X_ANIM_INDEX ,DMALL_JUSTIMON_X_ANIM_INDEX ,DMALL_ALPHAMON_ANIM_INDEX ,DMALL_HOUOUMON_X_ANIM_INDEX ,DMALL_TIGER_VESPAMON_ANIM_INDEX ,DMALL_GAIOUMON_ANIM_INDEX ,DMALL_DINOTIGERMON_ANIM_INDEX ,DMALL_HOLYDRAMON_X_ANIM_INDEX ,DMALL_EBEMON_X_ANIM_INDEX ,DMALL_HEXEBLAUMON_ANIM_INDEX ,DMALL_METALLICDRAMON_ANIM_INDEX ,DMALL_NOBLE_PUMPMON_ANIM_INDEX ,DMALL_ALPHAMON_ANIM_INDEX ,DMALL_ANCIENT_MEGATHERIUMON_ANIM_INDEX
                },
              };
            case DMALL_CTHYLLAMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMALL_CUPIMON_ANIM_INDEX:
              return {
                // Stage: Baby II
                .conditions = { .next_evolution_time_sec = 43200 },
                
                .num_animation_indices = 4,
                .animation_indices = {
                  DMALL_IMPMON_ANIM_INDEX ,DMALL_LUCEMON_ANIM_INDEX ,DMALL_PLOTMON_ANIM_INDEX ,DMALL_TERRIERMON_ANIM_INDEX
                },
              };
            case DMALL_CURIMON_ANIM_INDEX:
              return {
                // Stage: Baby I
                .conditions = { .next_evolution_time_sec = 600 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMALL_CYBERDRAMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 12,
                .animation_indices = {
                  DMALL_ALPHAMON_ANIM_INDEX ,DMALL_BLACK_WAR_GREYMON_ANIM_INDEX ,DMALL_CHAOSDRAMON_ANIM_INDEX ,DMALL_DEATHMON_BLACK_ANIM_INDEX ,DMALL_HERAKLE_KABUTERIMON_ANIM_INDEX ,DMALL_HOLYDRAMON_ANIM_INDEX ,DMALL_MUGENDRAMON_ANIM_INDEX ,DMALL_PLESIOMON_ANIM_INDEX ,DMALL_SAINT_GALGOMON_ANIM_INDEX ,DMALL_TITAMON_ANIM_INDEX ,DMALL_VENOM_VAMDEMON_ANIM_INDEX ,DMALL_WAR_GREYMON_ANIM_INDEX
                },
              };
            case DMALL_CYBERDRAMON_X_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 14,
                .animation_indices = {
                  DMALL_RAPIDMON_X_ANIM_INDEX ,DMALL_JUSTIMON_X_ANIM_INDEX ,DMALL_ALPHAMON_ANIM_INDEX ,DMALL_HOUOUMON_X_ANIM_INDEX ,DMALL_TIGER_VESPAMON_ANIM_INDEX ,DMALL_GAIOUMON_ANIM_INDEX ,DMALL_DINOTIGERMON_ANIM_INDEX ,DMALL_HOLYDRAMON_X_ANIM_INDEX ,DMALL_EBEMON_X_ANIM_INDEX ,DMALL_HEXEBLAUMON_ANIM_INDEX ,DMALL_METALLICDRAMON_ANIM_INDEX ,DMALL_NOBLE_PUMPMON_ANIM_INDEX ,DMALL_GAIOUMON_ANIM_INDEX ,DMALL_TIGER_VESPAMON_ANIM_INDEX
                },
              };
            case DMALL_CYCLOMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_NANOMON_ANIM_INDEX ,DMALL_AERO_V_DRAMON_ANIM_INDEX ,DMALL_ANDROMON_ANIM_INDEX ,DMALL_ANOMALOCARIMON_ANIM_INDEX ,DMALL_ASTAMON_ANIM_INDEX ,DMALL_ASURAMON_ANIM_INDEX ,DMALL_BIG_MAMEMON_ANIM_INDEX ,DMALL_BEOWOLFMON_ANIM_INDEX ,DMALL_CHIMAIRAMON_ANIM_INDEX ,DMALL_CYBERDRAMON_ANIM_INDEX ,DMALL_DAGOMON_ANIM_INDEX ,DMALL_DARK_KNIGHTMON_ANIM_INDEX ,DMALL_DORUGUREMON_ANIM_INDEX ,DMALL_ETEMON_ANIM_INDEX ,DMALL_GERBEMON_ANIM_INDEX
                },
              };
            case DMALL_DAGOMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 14,
                .animation_indices = {
                  DMALL_ANCIENT_MEGATHERIUMON_ANIM_INDEX ,DMALL_CTHYLLAMON_ANIM_INDEX ,DMALL_DARKDRAMON_ANIM_INDEX ,DMALL_DEMON_ANIM_INDEX ,DMALL_GIGA_SEADRAMON_ANIM_INDEX ,DMALL_LEVIAMON_ANIM_INDEX ,DMALL_METAL_ETEMON_ANIM_INDEX ,DMALL_METAL_SEADRAMON_ANIM_INDEX ,DMALL_PIEMON_ANIM_INDEX ,DMALL_PINOCHIMON_ANIM_INDEX ,DMALL_PLESIOMON_ANIM_INDEX ,DMALL_PUKUMON_ANIM_INDEX ,DMALL_REGALECUSMON_ANIM_INDEX ,DMALL_VENOM_VAMDEMON_ANIM_INDEX
                },
              };
            case DMALL_DAMEMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 7,
                .animation_indices = {
                  DMALL_CERBERUMON_X_ANIM_INDEX ,DMALL_LUCEMON_FALLDOWN_MODE_ANIM_INDEX ,DMALL_SKULL_BALUCHIMON_ANIM_INDEX ,DMALL_MEGALO_GROWMON_X_ANIM_INDEX ,DMALL_LILIMON_X_ANIM_INDEX ,DMALL_ANDROMON_ANIM_INDEX ,DMALL_SKULL_BALUCHIMON_ANIM_INDEX
                },
              };
            case DMALL_DARKDRAMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = 230400 },
                
                .num_animation_indices = 2,
                .animation_indices = {
                  DMALL_CHAOSMON_ANIM_INDEX ,DMALL_CHAOSDRAMON_ANIM_INDEX
                },
              };
            case DMALL_DARK_KNIGHTMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 3,
                .animation_indices = {
                  DMALL_DARKNESS_BAGRAMON_ANIM_INDEX ,DMALL_BEELZEBUMON_ANIM_INDEX ,DMALL_DARKNESS_BAGRAMON_ANIM_INDEX
                },
              };
            case DMALL_DARKNESS_BAGRAMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMALL_DARK_SUPERSTARMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 3,
                .animation_indices = {
                  DMALL_DARKDRAMON_ANIM_INDEX ,DMALL_KAISER_GREYMON_ANIM_INDEX ,DMALL_METAL_GARURUMON_BLACK_ANIM_INDEX
                },
              };
            case DMALL_DARK_TYRANOMON_X_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 6,
                .animation_indices = {
                  DMALL_METAL_GREYMON_VIRUS_X_ANIM_INDEX ,DMALL_MAMMON_X_ANIM_INDEX ,DMALL_TRICERAMON_X_ANIM_INDEX ,DMALL_MAMETYRAMON_ANIM_INDEX ,DMALL_MAMETYRAMON_ANIM_INDEX ,DMALL_METAL_TYRANOMON_ANIM_INDEX
                },
              };
            case DMALL_DEATH_MERAMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_BEELZEBUMON_ANIM_INDEX ,DMALL_BARBAMON_ANIM_INDEX ,DMALL_BEELZEBUMON_ANIM_INDEX ,DMALL_BOLTMON_ANIM_INDEX ,DMALL_DEMON_ANIM_INDEX ,DMALL_GANKOOMON_ANIM_INDEX ,DMALL_GRIFFOMON_ANIM_INDEX ,DMALL_MEGIDRAMON_ANIM_INDEX ,DMALL_METAL_GARURUMON_ANIM_INDEX ,DMALL_METAL_SEADRAMON_ANIM_INDEX ,DMALL_NOBLE_PUMPMON_ANIM_INDEX ,DMALL_PIEMON_ANIM_INDEX ,DMALL_PLESIOMON_ANIM_INDEX ,DMALL_SABER_LEOMON_ANIM_INDEX ,DMALL_SKULL_MAMMON_ANIM_INDEX
                },
              };
            case DMALL_DEATHMON_BLACK_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMALL_DEATHMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMALL_DEATH_X_DORUGAMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 3,
                .animation_indices = {
                  DMALL_ANDROMON_ANIM_INDEX ,DMALL_DORUGUREMON_ANIM_INDEX ,DMALL_METAL_TYRANOMON_ANIM_INDEX
                },
              };
            case DMALL_DELUMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 10,
                .animation_indices = {
                  DMALL_BOLTMON_ANIM_INDEX ,DMALL_GRIFFOMON_ANIM_INDEX ,DMALL_HOUOUMON_ANIM_INDEX ,DMALL_MEGIDRAMON_ANIM_INDEX ,DMALL_METAL_GARURUMON_ANIM_INDEX ,DMALL_METAL_SEADRAMON_ANIM_INDEX ,DMALL_PINOCHIMON_ANIM_INDEX ,DMALL_PLESIOMON_ANIM_INDEX ,DMALL_ROSEMON_ANIM_INDEX ,DMALL_SABER_LEOMON_ANIM_INDEX
                },
              };
            case DMALL_DEMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMALL_DEMON_X_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMALL_DEVIMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_NEO_DEVIMON_ANIM_INDEX ,DMALL_METAL_GREYMON_ANIM_INDEX ,DMALL_AERO_V_DRAMON_ANIM_INDEX ,DMALL_ANOMALOCARIMON_ANIM_INDEX ,DMALL_ASTAMON_ANIM_INDEX ,DMALL_ASURAMON_ANIM_INDEX ,DMALL_BAALMON_ANIM_INDEX ,DMALL_BEOWOLFMON_ANIM_INDEX ,DMALL_BIG_MAMEMON_ANIM_INDEX ,DMALL_BLUE_MERAMON_ANIM_INDEX ,DMALL_CHIMAIRAMON_ANIM_INDEX ,DMALL_CRESCEMON_ANIM_INDEX ,DMALL_DAGOMON_ANIM_INDEX ,DMALL_DARK_KNIGHTMON_ANIM_INDEX ,DMALL_DEATH_MERAMON_ANIM_INDEX
                },
              };
            case DMALL_DIABLOMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMALL_DIABLOMON_X_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMALL_DIANAMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMALL_DIGINORIMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMALL_DIGITAMAMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_TITAMON_ANIM_INDEX ,DMALL_GANKOOMON_ANIM_INDEX ,DMALL_ANCIENT_SPHINXMON_ANIM_INDEX ,DMALL_BOLTMON_ANIM_INDEX ,DMALL_BRYWELUDRAMON_ANIM_INDEX ,DMALL_DEATHMON_ANIM_INDEX ,DMALL_DEATHMON_BLACK_ANIM_INDEX ,DMALL_DIABLOMON_ANIM_INDEX ,DMALL_DUKEMON_ANIM_INDEX ,DMALL_GANKOOMON_ANIM_INDEX ,DMALL_GRIFFOMON_ANIM_INDEX ,DMALL_KING_ETEMON_ANIM_INDEX ,DMALL_LEVIAMON_ANIM_INDEX ,DMALL_LILITHMON_ANIM_INDEX ,DMALL_MARIN_ANGEMON_ANIM_INDEX
                },
              };
            case DMALL_DINOHUMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 11,
                .animation_indices = {
                  DMALL_BLACK_RAPIDMON_ANIM_INDEX ,DMALL_CYBERDRAMON_ANIM_INDEX ,DMALL_GRADEMON_ANIM_INDEX ,DMALL_HISYARYUMON_ANIM_INDEX ,DMALL_JYUREIMON_ANIM_INDEX ,DMALL_KNIGHTMON_ANIM_INDEX ,DMALL_MARIN_DEVIMON_ANIM_INDEX ,DMALL_MEPHISMON_ANIM_INDEX ,DMALL_OROCHIMON_ANIM_INDEX ,DMALL_PAILDRAMON_ANIM_INDEX ,DMALL_SHAWUJINMON_ANIM_INDEX
                },
              };
            case DMALL_DINOREXMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = 230400 },
                
                .num_animation_indices = 2,
                .animation_indices = {
                  DMALL_LEVIAMON_X_ANIM_INDEX ,DMALL_BARBAMON_X_ANIM_INDEX
                },
              };
            case DMALL_DINOTIGERMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = 230400 },
                
                .num_animation_indices = 7,
                .animation_indices = {
                  DMALL_MAGNAMON_X_ANIM_INDEX ,DMALL_GANKOOMON_X_ANIM_INDEX ,DMALL_DYNASMON_X_ANIM_INDEX ,DMALL_CRANIUMMON_X_ANIM_INDEX ,DMALL_DUKEMON_X_ANIM_INDEX ,DMALL_ALPHAMON_OURYUKEN_ANIM_INDEX ,DMALL_JESMON_GX_ANIM_INDEX
                },
              };
            case DMALL_DOBERMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 11,
                .animation_indices = {
                  DMALL_ANGEWOMON_ANIM_INDEX ,DMALL_BEOWOLFMON_ANIM_INDEX ,DMALL_CATURAMON_ANIM_INDEX ,DMALL_CHIMAIRAMON_ANIM_INDEX ,DMALL_DARK_SUPERSTARMON_ANIM_INDEX ,DMALL_DELUMON_ANIM_INDEX ,DMALL_MEGALO_GROWMON_ANIM_INDEX ,DMALL_SCORPIOMON_ANIM_INDEX ,DMALL_SIRENMON_ANIM_INDEX ,DMALL_VAMDEMON_ANIM_INDEX ,DMALL_WERE_GARURUMON_ANIM_INDEX
                },
              };
            case DMALL_DODOMON_ANIM_INDEX:
              return {
                // Stage: Baby I
                .conditions = { .next_evolution_time_sec = 600 },
                
                .num_animation_indices = 4,
                .animation_indices = {
                  DMALL_DORIMON_ANIM_INDEX ,DMALL_WANYAMON_ANIM_INDEX ,DMALL_DORIMON_ANIM_INDEX ,DMALL_WANYAMON_ANIM_INDEX
                },
              };
            case DMALL_DOGMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 2,
                .animation_indices = {
                  DMALL_DIGITAMAMON_ANIM_INDEX ,DMALL_METAL_GREYMON_VIRUS_ANIM_INDEX
                },
              };
            case DMALL_DOKIMON_ANIM_INDEX:
              return {
                // Stage: Baby I
                .conditions = { .next_evolution_time_sec = 600 },
                
                .num_animation_indices = 2,
                .animation_indices = {
                  DMALL_BIBIMON_ANIM_INDEX ,DMALL_BIBIMON_ANIM_INDEX
                },
              };
            case DMALL_DOKUGUMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_AERO_V_DRAMON_ANIM_INDEX ,DMALL_ANDROMON_ANIM_INDEX ,DMALL_ANOMALOCARIMON_ANIM_INDEX ,DMALL_ARCHNEMON_ANIM_INDEX ,DMALL_ASTAMON_ANIM_INDEX ,DMALL_ASURAMON_ANIM_INDEX ,DMALL_ATLUR_KABUTERIMON_BLUE_ANIM_INDEX ,DMALL_ATLUR_KABUTERIMON_RED_ANIM_INDEX ,DMALL_BEOWOLFMON_ANIM_INDEX ,DMALL_BIG_MAMEMON_ANIM_INDEX ,DMALL_BLOSSOMON_ANIM_INDEX ,DMALL_CATURAMON_ANIM_INDEX ,DMALL_DAGOMON_ANIM_INDEX ,DMALL_DARK_KNIGHTMON_ANIM_INDEX ,DMALL_DURAMON_ANIM_INDEX
                },
              };
            case DMALL_DOKUNEMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 11,
                .animation_indices = {
                  DMALL_DOKUGUMON_ANIM_INDEX ,DMALL_GOKIMON_ANIM_INDEX ,DMALL_KUWAGAMON_ANIM_INDEX ,DMALL_MORI_SHELLMON_ANIM_INDEX ,DMALL_NISE_DRIMOGEMON_ANIM_INDEX ,DMALL_PLATINUM_SCUMON_ANIM_INDEX ,DMALL_SAND_YANMAMON_ANIM_INDEX ,DMALL_TOGEMON_ANIM_INDEX ,DMALL_WOODMON_ANIM_INDEX ,DMALL_YANMAMON_ANIM_INDEX ,DMALL_ZASSOUMON_ANIM_INDEX
                },
              };
            case DMALL_DORIMON_ANIM_INDEX:
              return {
                // Stage: Baby II
                .conditions = { .next_evolution_time_sec = 43200 },
                
                .num_animation_indices = 6,
                .animation_indices = {
                  DMALL_DORUMON_ANIM_INDEX ,DMALL_AGUMON_BLACK_ANIM_INDEX ,DMALL_ALRAUMON_ANIM_INDEX ,DMALL_ARMADIMON_ANIM_INDEX ,DMALL_DORUMON_ANIM_INDEX ,DMALL_LOPMON_ANIM_INDEX
                },
              };
            case DMALL_DORUGAMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_DORUGUREMON_ANIM_INDEX ,DMALL_DORUGUREMON_ANIM_INDEX ,DMALL_CYBERDRAMON_X_ANIM_INDEX ,DMALL_OMEGA_SHOUTMON_X_ANIM_INDEX ,DMALL_GARUDAMON_X_ANIM_INDEX ,DMALL_CANNONBEEMON_ANIM_INDEX ,DMALL_GRADEMON_ANIM_INDEX ,DMALL_MAMEMON_X_ANIM_INDEX ,DMALL_CRYS_PALEDRAMON_ANIM_INDEX ,DMALL_JAZARICHMON_ANIM_INDEX ,DMALL_PUMPMON_ANIM_INDEX ,DMALL_AERO_V_DRAMON_ANIM_INDEX ,DMALL_ANDROMON_ANIM_INDEX ,DMALL_ANOMALOCARIMON_ANIM_INDEX ,DMALL_ASURAMON_ANIM_INDEX
                },
              };
            case DMALL_DORUGORAMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMALL_DORUGUREMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_ALPHAMON_ANIM_INDEX ,DMALL_DORUGORAMON_ANIM_INDEX ,DMALL_GAIOUMON_ANIM_INDEX ,DMALL_RAPIDMON_X_ANIM_INDEX ,DMALL_JUSTIMON_X_ANIM_INDEX ,DMALL_ALPHAMON_ANIM_INDEX ,DMALL_HOUOUMON_X_ANIM_INDEX ,DMALL_TIGER_VESPAMON_ANIM_INDEX ,DMALL_GAIOUMON_ANIM_INDEX ,DMALL_DINOTIGERMON_ANIM_INDEX ,DMALL_HOLYDRAMON_X_ANIM_INDEX ,DMALL_EBEMON_X_ANIM_INDEX ,DMALL_HEXEBLAUMON_ANIM_INDEX ,DMALL_METALLICDRAMON_ANIM_INDEX ,DMALL_NOBLE_PUMPMON_ANIM_INDEX
                },
              };
            case DMALL_DORUMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_DEATH_X_DORUGAMON_ANIM_INDEX ,DMALL_DORUGAMON_ANIM_INDEX ,DMALL_RAPTORDRAMON_ANIM_INDEX ,DMALL_DORUGAMON_ANIM_INDEX ,DMALL_PTERANOMON_X_ANIM_INDEX ,DMALL_TOGEMON_X_ANIM_INDEX ,DMALL_SIESAMON_X_ANIM_INDEX ,DMALL_OMEKAMON_ANIM_INDEX ,DMALL_PALEDRAMON_ANIM_INDEX ,DMALL_JAZARDMON_ANIM_INDEX ,DMALL_AIRDRAMON_ANIM_INDEX ,DMALL_CENTALMON_ANIM_INDEX ,DMALL_COELAMON_ANIM_INDEX ,DMALL_CYCLOMON_ANIM_INDEX ,DMALL_DEATH_X_DORUGAMON_ANIM_INDEX
                },
              };
            case DMALL_DRACOMON_X_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 3,
                .animation_indices = {
                  DMALL_GROWMON_X_ANIM_INDEX ,DMALL_DAMEMON_ANIM_INDEX ,DMALL_DAMEMON_ANIM_INDEX
                },
              };
            case DMALL_DRACUMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_SANGLOUPMON_ANIM_INDEX ,DMALL_BAKEMON_ANIM_INDEX ,DMALL_DEATH_X_DORUGAMON_ANIM_INDEX ,DMALL_DEVIMON_ANIM_INDEX ,DMALL_DOBERMON_ANIM_INDEX ,DMALL_DOGMON_ANIM_INDEX ,DMALL_DORUGAMON_ANIM_INDEX ,DMALL_GEKOMON_ANIM_INDEX ,DMALL_MERAMON_ANIM_INDEX ,DMALL_PORCUPAMON_ANIM_INDEX ,DMALL_SANGLOUPMON_ANIM_INDEX ,DMALL_SCUMON_ANIM_INDEX ,DMALL_SOULMON_ANIM_INDEX ,DMALL_STARMON_ANIM_INDEX ,DMALL_WIZARMON_ANIM_INDEX
                },
              };
            case DMALL_DRIMOGEMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_GIROMON_ANIM_INDEX ,DMALL_AERO_V_DRAMON_ANIM_INDEX ,DMALL_ANDROMON_ANIM_INDEX ,DMALL_ANOMALOCARIMON_ANIM_INDEX ,DMALL_ASURAMON_ANIM_INDEX ,DMALL_ATLUR_KABUTERIMON_RED_ANIM_INDEX ,DMALL_BEOWOLFMON_ANIM_INDEX ,DMALL_BIG_MAMEMON_ANIM_INDEX ,DMALL_CYBERDRAMON_ANIM_INDEX ,DMALL_DAGOMON_ANIM_INDEX ,DMALL_DARK_KNIGHTMON_ANIM_INDEX ,DMALL_DORUGUREMON_ANIM_INDEX ,DMALL_DURAMON_ANIM_INDEX ,DMALL_GARUDAMON_ANIM_INDEX ,DMALL_GERBEMON_ANIM_INDEX
                },
              };
            case DMALL_DUFTMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMALL_DUFTMON_X_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMALL_DUKEMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMALL_DUKEMON_X_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMALL_DURAMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 6,
                .animation_indices = {
                  DMALL_HOLYDRAMON_ANIM_INDEX ,DMALL_MUGENDRAMON_ANIM_INDEX ,DMALL_OURYUMON_ANIM_INDEX ,DMALL_PLESIOMON_ANIM_INDEX ,DMALL_TIGER_VESPAMON_ANIM_INDEX ,DMALL_WAR_GREYMON_ANIM_INDEX
                },
              };
            case DMALL_DUSKMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 6,
                .animation_indices = {
                  DMALL_VELGRMON_ANIM_INDEX ,DMALL_DARK_TYRANOMON_X_ANIM_INDEX ,DMALL_OGREMON_X_ANIM_INDEX ,DMALL_VELGRMON_ANIM_INDEX ,DMALL_NUMEMON_X_ANIM_INDEX ,DMALL_VELGRMON_ANIM_INDEX
                },
              };
            case DMALL_DYNASMON_X_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMALL_EBEMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMALL_EBEMON_X_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = 230400 },
                
                .num_animation_indices = 7,
                .animation_indices = {
                  DMALL_MAGNAMON_X_ANIM_INDEX ,DMALL_GANKOOMON_X_ANIM_INDEX ,DMALL_DYNASMON_X_ANIM_INDEX ,DMALL_CRANIUMMON_X_ANIM_INDEX ,DMALL_DUKEMON_X_ANIM_INDEX ,DMALL_ALPHAMON_OURYUKEN_ANIM_INDEX ,DMALL_JESMON_GX_ANIM_INDEX
                },
              };
            case DMALL_EBIDRAMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_GUSOKUMON_ANIM_INDEX ,DMALL_HANGYOMON_ANIM_INDEX ,DMALL_AERO_V_DRAMON_ANIM_INDEX ,DMALL_ANDROMON_ANIM_INDEX ,DMALL_ANOMALOCARIMON_ANIM_INDEX ,DMALL_ASURAMON_ANIM_INDEX ,DMALL_BEOWOLFMON_ANIM_INDEX ,DMALL_BIG_MAMEMON_ANIM_INDEX ,DMALL_CYBERDRAMON_ANIM_INDEX ,DMALL_DAGOMON_ANIM_INDEX ,DMALL_DARK_KNIGHTMON_ANIM_INDEX ,DMALL_DURAMON_ANIM_INDEX ,DMALL_GARUDAMON_ANIM_INDEX ,DMALL_GERBEMON_ANIM_INDEX ,DMALL_GUSOKUMON_ANIM_INDEX
                },
              };
            case DMALL_EKAKIMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMALL_ELECMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_GARURUMON_BLACK_ANIM_INDEX ,DMALL_LEOMON_ANIM_INDEX ,DMALL_ANGEMON_ANIM_INDEX ,DMALL_YUKIDARUMON_ANIM_INDEX ,DMALL_BIRDRAMON_ANIM_INDEX ,DMALL_WHAMON_ANIM_INDEX ,DMALL_VEGIMON_ANIM_INDEX ,DMALL_ANGEMON_ANIM_INDEX ,DMALL_BAKEMON_ANIM_INDEX ,DMALL_BIRDRAMON_ANIM_INDEX ,DMALL_CENTALMON_ANIM_INDEX ,DMALL_GARURUMON_ANIM_INDEX ,DMALL_GARURUMON_BLACK_ANIM_INDEX ,DMALL_GAWAPPAMON_ANIM_INDEX ,DMALL_GEKOMON_ANIM_INDEX
                },
              };
            case DMALL_ELECMON_VIOLET_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_THUNDERBALLMON_ANIM_INDEX ,DMALL_CENTALMON_ANIM_INDEX ,DMALL_GEREMON_ANIM_INDEX ,DMALL_HOOKMON_ANIM_INDEX ,DMALL_HYOUGAMON_ANIM_INDEX ,DMALL_IKKAKUMON_ANIM_INDEX ,DMALL_LEOMON_ANIM_INDEX ,DMALL_MAD_LEOMON_ANIM_INDEX ,DMALL_NUMEMON_ANIM_INDEX ,DMALL_RED_VEGIMON_ANIM_INDEX ,DMALL_SHEEPMON_ANIM_INDEX ,DMALL_SHIMA_UNIMON_ANIM_INDEX ,DMALL_TAILMON_ANIM_INDEX ,DMALL_THUNDERBALLMON_ANIM_INDEX ,DMALL_VEGIMON_ANIM_INDEX
                },
              };
            case DMALL_ENTMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMALL_ETEMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 14,
                .animation_indices = {
                  DMALL_KING_ETEMON_ANIM_INDEX ,DMALL_METAL_ETEMON_ANIM_INDEX ,DMALL_BANCHO_LEOMON_ANIM_INDEX ,DMALL_BANCHO_LEOMON_ANIM_INDEX ,DMALL_DARKDRAMON_ANIM_INDEX ,DMALL_DEATHMON_BLACK_ANIM_INDEX ,DMALL_DEMON_ANIM_INDEX ,DMALL_KING_ETEMON_ANIM_INDEX ,DMALL_METAL_ETEMON_ANIM_INDEX ,DMALL_PIEMON_ANIM_INDEX ,DMALL_PLATINUM_NUMEMON_ANIM_INDEX ,DMALL_PUKUMON_ANIM_INDEX ,DMALL_SAINT_GALGOMON_ANIM_INDEX ,DMALL_VENOM_VAMDEMON_ANIM_INDEX
                },
              };
            case DMALL_EXAMON_X_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMALL_FILMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 12,
                .animation_indices = {
                  DMALL_STIFFILMON_ANIM_INDEX ,DMALL_METAL_GREYMON_VIRUS_X_ANIM_INDEX ,DMALL_TRICERAMON_X_ANIM_INDEX ,DMALL_VAMDEMON_X_ANIM_INDEX ,DMALL_MEGA_SEADRAMON_X_ANIM_INDEX ,DMALL_STIFFILMON_ANIM_INDEX ,DMALL_MAMETYRAMON_ANIM_INDEX ,DMALL_KAISER_LEOMON_ANIM_INDEX ,DMALL_ANDROMON_ANIM_INDEX ,DMALL_KAISER_LEOMON_ANIM_INDEX ,DMALL_MAMETYRAMON_ANIM_INDEX ,DMALL_STIFFILMON_ANIM_INDEX
                },
              };
            case DMALL_FIRAMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_FLAREMON_ANIM_INDEX ,DMALL_AERO_V_DRAMON_ANIM_INDEX ,DMALL_ANDROMON_ANIM_INDEX ,DMALL_ANGEWOMON_ANIM_INDEX ,DMALL_ASURAMON_ANIM_INDEX ,DMALL_BAALMON_ANIM_INDEX ,DMALL_BIG_MAMEMON_ANIM_INDEX ,DMALL_CYBERDRAMON_ANIM_INDEX ,DMALL_DURAMON_ANIM_INDEX ,DMALL_FLAREMON_ANIM_INDEX ,DMALL_GARUDAMON_ANIM_INDEX ,DMALL_HANGYOMON_ANIM_INDEX ,DMALL_HOLY_ANGEMON_ANIM_INDEX ,DMALL_JYAGAMON_ANIM_INDEX ,DMALL_MACH_GAOGAMON_ANIM_INDEX
                },
              };
            case DMALL_FLAREMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 10,
                .animation_indices = {
                  DMALL_APOLLOMON_ANIM_INDEX ,DMALL_APOLLOMON_ANIM_INDEX ,DMALL_DUKEMON_ANIM_INDEX ,DMALL_HOLYDRAMON_ANIM_INDEX ,DMALL_MUGENDRAMON_ANIM_INDEX ,DMALL_PLESIOMON_ANIM_INDEX ,DMALL_ROSEMON_ANIM_INDEX ,DMALL_SABER_LEOMON_ANIM_INDEX ,DMALL_VOLCANICDRAMON_ANIM_INDEX ,DMALL_WAR_GREYMON_ANIM_INDEX
                },
              };
            case DMALL_FLORAMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_KIWIMON_ANIM_INDEX ,DMALL_VEGIMON_ANIM_INDEX ,DMALL_BIRDRAMON_ANIM_INDEX ,DMALL_BLACK_GALGOMON_ANIM_INDEX ,DMALL_BLACK_TAILMON_ANIM_INDEX ,DMALL_DOBERMON_ANIM_INDEX ,DMALL_EBIDRAMON_ANIM_INDEX ,DMALL_GARURUMON_BLACK_ANIM_INDEX ,DMALL_IGAMON_ANIM_INDEX ,DMALL_KABUTERIMON_ANIM_INDEX ,DMALL_KIWIMON_ANIM_INDEX ,DMALL_KYUBIMON_ANIM_INDEX ,DMALL_KYUBIMON_SILVER_ANIM_INDEX ,DMALL_MEICOOMON_ANIM_INDEX ,DMALL_NUMEMON_ANIM_INDEX
                },
              };
            case DMALL_FUFUMON_ANIM_INDEX:
              return {
                // Stage: Baby I
                .conditions = { .next_evolution_time_sec = 600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DMALL_KYOKYOMON_ANIM_INDEX
                },
              };
            case DMALL_FUGAMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 6,
                .animation_indices = {
                  DMALL_BLACK_MEGALO_GROWMON_ANIM_INDEX ,DMALL_ETEMON_ANIM_INDEX ,DMALL_GARUDAMON_ANIM_INDEX ,DMALL_MACH_GAOGAMON_ANIM_INDEX ,DMALL_OKUWAMON_ANIM_INDEX ,DMALL_WERE_GARURUMON_ANIM_INDEX
                },
              };
            case DMALL_FUNBEEMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 11,
                .animation_indices = {
                  DMALL_DOKUGUMON_ANIM_INDEX ,DMALL_DORUGAMON_ANIM_INDEX ,DMALL_GINRYUMON_ANIM_INDEX ,DMALL_GOLD_NUMEMON_ANIM_INDEX ,DMALL_GUARDROMON_GOLD_ANIM_INDEX ,DMALL_KABUTERIMON_ANIM_INDEX ,DMALL_KUWAGAMON_ANIM_INDEX ,DMALL_OMEKAMON_ANIM_INDEX ,DMALL_RAPTORDRAMON_ANIM_INDEX ,DMALL_TOGEMON_ANIM_INDEX ,DMALL_WASPMON_ANIM_INDEX
                },
              };
            case DMALL_GABUMON_X_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_RHINOMON_X_ANIM_INDEX ,DMALL_TOBUCATMON_ANIM_INDEX ,DMALL_DAMEMON_ANIM_INDEX ,DMALL_ANGEMON_ANIM_INDEX ,DMALL_BLACK_TAILMON_ANIM_INDEX ,DMALL_CENTALMON_ANIM_INDEX ,DMALL_DAMEMON_ANIM_INDEX ,DMALL_DOBERMON_ANIM_INDEX ,DMALL_DOKUGUMON_ANIM_INDEX ,DMALL_DORUGAMON_ANIM_INDEX ,DMALL_FUGAMON_ANIM_INDEX ,DMALL_GAOGAMON_ANIM_INDEX ,DMALL_GARURUMON_ANIM_INDEX ,DMALL_GARURUMON_BLACK_ANIM_INDEX ,DMALL_GEO_GREYMON_ANIM_INDEX
                },
              };
            case DMALL_GAIOUMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = 230400 },
                
                .num_animation_indices = 7,
                .animation_indices = {
                  DMALL_MAGNAMON_X_ANIM_INDEX ,DMALL_GANKOOMON_X_ANIM_INDEX ,DMALL_DYNASMON_X_ANIM_INDEX ,DMALL_CRANIUMMON_X_ANIM_INDEX ,DMALL_DUKEMON_X_ANIM_INDEX ,DMALL_ALPHAMON_OURYUKEN_ANIM_INDEX ,DMALL_JESMON_GX_ANIM_INDEX
                },
              };
            case DMALL_GALGOMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 7,
                .animation_indices = {
                  DMALL_BLACK_RAPIDMON_ANIM_INDEX ,DMALL_CRESCEMON_ANIM_INDEX ,DMALL_JYAGAMON_ANIM_INDEX ,DMALL_MACH_GAOGAMON_ANIM_INDEX ,DMALL_MEGALO_GROWMON_ANIM_INDEX ,DMALL_METAL_MAMEMON_ANIM_INDEX ,DMALL_PANDAMON_ANIM_INDEX
                },
              };
            case DMALL_GAMMAMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMALL_GANIMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 14,
                .animation_indices = {
                  DMALL_COELAMON_ANIM_INDEX ,DMALL_COELAMON_ANIM_INDEX ,DMALL_EBIDRAMON_ANIM_INDEX ,DMALL_GALGOMON_ANIM_INDEX ,DMALL_GAWAPPAMON_ANIM_INDEX ,DMALL_GEKOMON_ANIM_INDEX ,DMALL_GESOMON_ANIM_INDEX ,DMALL_LEOMON_ANIM_INDEX ,DMALL_MONOCHROMON_ANIM_INDEX ,DMALL_MORI_SHELLMON_ANIM_INDEX ,DMALL_RUKAMON_ANIM_INDEX ,DMALL_SEADRAMON_ANIM_INDEX ,DMALL_SHELLMON_ANIM_INDEX ,DMALL_WHAMON_ANIM_INDEX
                },
              };
            case DMALL_GANKOOMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMALL_GANKOOMON_X_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = 230400 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DMALL_JESMON_GX_ANIM_INDEX
                },
              };
            case DMALL_GAOGAMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_MACH_GAOGAMON_ANIM_INDEX ,DMALL_ANOMALOCARIMON_ANIM_INDEX ,DMALL_CRESCEMON_ANIM_INDEX ,DMALL_DARK_SUPERSTARMON_ANIM_INDEX ,DMALL_DIGITAMAMON_ANIM_INDEX ,DMALL_GERBEMON_ANIM_INDEX ,DMALL_GOGMAMON_ANIM_INDEX ,DMALL_KAISER_LEOMON_ANIM_INDEX ,DMALL_LILAMON_ANIM_INDEX ,DMALL_MACH_GAOGAMON_ANIM_INDEX ,DMALL_MAMMON_ANIM_INDEX ,DMALL_MEGA_SEADRAMON_ANIM_INDEX ,DMALL_MONZAEMON_ANIM_INDEX ,DMALL_OROCHIMON_ANIM_INDEX ,DMALL_PANJYAMON_ANIM_INDEX
                },
              };
            case DMALL_GAOMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_BLACK_GAOGAMON_ANIM_INDEX ,DMALL_GAOGAMON_ANIM_INDEX ,DMALL_ANGEMON_ANIM_INDEX ,DMALL_BABOONGAMON_ANIM_INDEX ,DMALL_BLACK_GAOGAMON_ANIM_INDEX ,DMALL_BLACK_TAILMON_ANIM_INDEX ,DMALL_CENTALMON_ANIM_INDEX ,DMALL_FIRAMON_ANIM_INDEX ,DMALL_GALGOMON_ANIM_INDEX ,DMALL_GAOGAMON_ANIM_INDEX ,DMALL_GARURUMON_ANIM_INDEX ,DMALL_GAWAPPAMON_ANIM_INDEX ,DMALL_GEO_GREYMON_ANIM_INDEX ,DMALL_GOKIMON_ANIM_INDEX ,DMALL_GOLD_NUMEMON_ANIM_INDEX
                },
              };
            case DMALL_GARUDAMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 12,
                .animation_indices = {
                  DMALL_HOUOUMON_ANIM_INDEX ,DMALL_BEELZEBUMON_ANIM_INDEX ,DMALL_DEMON_ANIM_INDEX ,DMALL_DUKEMON_ANIM_INDEX ,DMALL_GRIFFOMON_ANIM_INDEX ,DMALL_HOLYDRAMON_ANIM_INDEX ,DMALL_HOUOUMON_ANIM_INDEX ,DMALL_METAL_GARURUMON_ANIM_INDEX ,DMALL_SERAPHIMON_ANIM_INDEX ,DMALL_ULFORCE_V_DRAMON_ANIM_INDEX ,DMALL_VALDURMON_ANIM_INDEX ,DMALL_WAR_GREYMON_ANIM_INDEX
                },
              };
            case DMALL_GARUDAMON_X_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_RAPIDMON_X_ANIM_INDEX ,DMALL_JUSTIMON_X_ANIM_INDEX ,DMALL_ALPHAMON_ANIM_INDEX ,DMALL_HOUOUMON_X_ANIM_INDEX ,DMALL_TIGER_VESPAMON_ANIM_INDEX ,DMALL_GAIOUMON_ANIM_INDEX ,DMALL_DINOTIGERMON_ANIM_INDEX ,DMALL_HOLYDRAMON_X_ANIM_INDEX ,DMALL_EBEMON_X_ANIM_INDEX ,DMALL_HEXEBLAUMON_ANIM_INDEX ,DMALL_METALLICDRAMON_ANIM_INDEX ,DMALL_NOBLE_PUMPMON_ANIM_INDEX ,DMALL_DEMON_ANIM_INDEX ,DMALL_GAIOUMON_ANIM_INDEX ,DMALL_GRIFFOMON_ANIM_INDEX
                },
              };
            case DMALL_GARURUMON_BLACK_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_BLACK_RAPIDMON_ANIM_INDEX ,DMALL_BLUE_MERAMON_ANIM_INDEX ,DMALL_CATURAMON_ANIM_INDEX ,DMALL_CHIMAIRAMON_ANIM_INDEX ,DMALL_DORUGUREMON_ANIM_INDEX ,DMALL_ETEMON_ANIM_INDEX ,DMALL_HOLY_ANGEMON_ANIM_INDEX ,DMALL_MACH_GAOGAMON_ANIM_INDEX ,DMALL_MAMMON_ANIM_INDEX ,DMALL_METAL_GREYMON_ANIM_INDEX ,DMALL_PAILDRAMON_ANIM_INDEX ,DMALL_PANDAMON_ANIM_INDEX ,DMALL_PANJYAMON_ANIM_INDEX ,DMALL_PUMPMON_ANIM_INDEX ,DMALL_WARU_MONZAEMON_ANIM_INDEX
                },
              };
            case DMALL_GARURUMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_CHIMAIRAMON_ANIM_INDEX ,DMALL_WERE_GARURUMON_ANIM_INDEX ,DMALL_METAL_MAMEMON_ANIM_INDEX ,DMALL_AERO_V_DRAMON_ANIM_INDEX ,DMALL_ANDROMON_ANIM_INDEX ,DMALL_ANGEWOMON_ANIM_INDEX ,DMALL_ANOMALOCARIMON_ANIM_INDEX ,DMALL_ASURAMON_ANIM_INDEX ,DMALL_ATLUR_KABUTERIMON_RED_ANIM_INDEX ,DMALL_BAALMON_ANIM_INDEX ,DMALL_BEOWOLFMON_ANIM_INDEX ,DMALL_BIG_MAMEMON_ANIM_INDEX ,DMALL_BLUE_MERAMON_ANIM_INDEX ,DMALL_CATURAMON_ANIM_INDEX ,DMALL_CHIMAIRAMON_ANIM_INDEX
                },
              };
            case DMALL_GAWAPPAMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 12,
                .animation_indices = {
                  DMALL_SHAWUJINMON_ANIM_INDEX ,DMALL_BLOSSOMON_ANIM_INDEX ,DMALL_DIGITAMAMON_ANIM_INDEX ,DMALL_HANGYOMON_ANIM_INDEX ,DMALL_MACH_GAOGAMON_ANIM_INDEX ,DMALL_MAMMON_ANIM_INDEX ,DMALL_MEGA_SEADRAMON_ANIM_INDEX ,DMALL_MEGALO_GROWMON_ANIM_INDEX ,DMALL_RIZE_GREYMON_ANIM_INDEX ,DMALL_SHAWUJINMON_ANIM_INDEX ,DMALL_TONOSAMA_GEKOMON_ANIM_INDEX ,DMALL_WARU_SEADRAMON_ANIM_INDEX
                },
              };
            case DMALL_GAZIMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_HANUMON_ANIM_INDEX ,DMALL_LEOMON_ANIM_INDEX ,DMALL_CYCLOMON_ANIM_INDEX ,DMALL_BLACK_TAILMON_ANIM_INDEX ,DMALL_BITMON_ANIM_INDEX ,DMALL_CYCLOMON_ANIM_INDEX ,DMALL_DEVIMON_ANIM_INDEX ,DMALL_DOBERMON_ANIM_INDEX ,DMALL_DOKUGUMON_ANIM_INDEX ,DMALL_DORUGAMON_ANIM_INDEX ,DMALL_GALGOMON_ANIM_INDEX ,DMALL_GAOGAMON_ANIM_INDEX ,DMALL_GARURUMON_ANIM_INDEX ,DMALL_GARURUMON_BLACK_ANIM_INDEX ,DMALL_GRYZMON_ANIM_INDEX
                },
              };
            case DMALL_GAZIMON_X_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_BITMON_ANIM_INDEX ,DMALL_CYCLOMON_ANIM_INDEX ,DMALL_DEVIMON_ANIM_INDEX ,DMALL_DOBERMON_ANIM_INDEX ,DMALL_DORUGAMON_ANIM_INDEX ,DMALL_GALGOMON_ANIM_INDEX ,DMALL_GAOGAMON_ANIM_INDEX ,DMALL_GARURUMON_ANIM_INDEX ,DMALL_GRYZMON_ANIM_INDEX ,DMALL_LEOMON_ANIM_INDEX ,DMALL_LYNXMON_ANIM_INDEX ,DMALL_SANGLOUPMON_ANIM_INDEX ,DMALL_SHEEPMON_ANIM_INDEX ,DMALL_TAILMON_ANIM_INDEX ,DMALL_TORTAMON_ANIM_INDEX
                },
              };
            case DMALL_GEKOMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_TONOSAMA_GEKOMON_ANIM_INDEX ,DMALL_AERO_V_DRAMON_ANIM_INDEX ,DMALL_ANOMALOCARIMON_ANIM_INDEX ,DMALL_ASTAMON_ANIM_INDEX ,DMALL_ASURAMON_ANIM_INDEX ,DMALL_BEOWOLFMON_ANIM_INDEX ,DMALL_BIG_MAMEMON_ANIM_INDEX ,DMALL_DAGOMON_ANIM_INDEX ,DMALL_DARK_KNIGHTMON_ANIM_INDEX ,DMALL_ETEMON_ANIM_INDEX ,DMALL_GERBEMON_ANIM_INDEX ,DMALL_HANGYOMON_ANIM_INDEX ,DMALL_MACH_GAOGAMON_ANIM_INDEX ,DMALL_MEGADRAMON_ANIM_INDEX ,DMALL_MEGALO_GROWMON_ANIM_INDEX
                },
              };
            case DMALL_GEO_GREYMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_RIZE_GREYMON_ANIM_INDEX ,DMALL_ANDROMON_ANIM_INDEX ,DMALL_ANOMALOCARIMON_ANIM_INDEX ,DMALL_CYBERDRAMON_ANIM_INDEX ,DMALL_DIGITAMAMON_ANIM_INDEX ,DMALL_DURAMON_ANIM_INDEX ,DMALL_FLAREMON_ANIM_INDEX ,DMALL_GERBEMON_ANIM_INDEX ,DMALL_GIGADRAMON_ANIM_INDEX ,DMALL_LILAMON_ANIM_INDEX ,DMALL_MACH_GAOGAMON_ANIM_INDEX ,DMALL_MAMMON_ANIM_INDEX ,DMALL_MEGA_SEADRAMON_ANIM_INDEX ,DMALL_MEGALO_GROWMON_ANIM_INDEX ,DMALL_MEGALO_GROWMON_ORANGE_ANIM_INDEX
                },
              };
            case DMALL_GERBEMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 12,
                .animation_indices = {
                  DMALL_BANCHO_LEOMON_ANIM_INDEX ,DMALL_DARKDRAMON_ANIM_INDEX ,DMALL_DEMON_ANIM_INDEX ,DMALL_METAL_ETEMON_ANIM_INDEX ,DMALL_OURYUMON_ANIM_INDEX ,DMALL_PIEMON_ANIM_INDEX ,DMALL_PINOCHIMON_ANIM_INDEX ,DMALL_PLATINUM_NUMEMON_ANIM_INDEX ,DMALL_PUKUMON_ANIM_INDEX ,DMALL_ROSEMON_ANIM_INDEX ,DMALL_SERAPHIMON_ANIM_INDEX ,DMALL_VENOM_VAMDEMON_ANIM_INDEX
                },
              };
            case DMALL_GEREMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 7,
                .animation_indices = {
                  DMALL_BLACK_KING_NUMEMON_ANIM_INDEX ,DMALL_ETEMON_ANIM_INDEX ,DMALL_METAL_MAMEMON_ANIM_INDEX ,DMALL_MONZAEMON_ANIM_INDEX ,DMALL_SUPERSTARMON_ANIM_INDEX ,DMALL_VADEMON_ANIM_INDEX ,DMALL_WARU_MONZAEMON_ANIM_INDEX
                },
              };
            case DMALL_GESOMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_AERO_V_DRAMON_ANIM_INDEX ,DMALL_ANOMALOCARIMON_ANIM_INDEX ,DMALL_ASTAMON_ANIM_INDEX ,DMALL_ASURAMON_ANIM_INDEX ,DMALL_BEOWOLFMON_ANIM_INDEX ,DMALL_BIG_MAMEMON_ANIM_INDEX ,DMALL_DAGOMON_ANIM_INDEX ,DMALL_DARK_KNIGHTMON_ANIM_INDEX ,DMALL_ETEMON_ANIM_INDEX ,DMALL_GERBEMON_ANIM_INDEX ,DMALL_HANGYOMON_ANIM_INDEX ,DMALL_MAMETYRAMON_ANIM_INDEX ,DMALL_MARIN_DEVIMON_ANIM_INDEX ,DMALL_MEGA_SEADRAMON_ANIM_INDEX ,DMALL_MEGADRAMON_ANIM_INDEX
                },
              };
            case DMALL_GHOSTMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 6,
                .animation_indices = {
                  DMALL_BAKEMON_ANIM_INDEX ,DMALL_ALGOMON_ADULT_ANIM_INDEX ,DMALL_BAKEMON_ANIM_INDEX ,DMALL_DEVIMON_ANIM_INDEX ,DMALL_SABERDRAMON_ANIM_INDEX ,DMALL_WIZARMON_ANIM_INDEX
                },
              };
            case DMALL_GIGADRAMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_BLACK_SAINT_GALGOMON_ANIM_INDEX ,DMALL_CHAOSDRAMON_ANIM_INDEX ,DMALL_DARKDRAMON_ANIM_INDEX ,DMALL_DIABLOMON_ANIM_INDEX ,DMALL_DORUGORAMON_ANIM_INDEX ,DMALL_GAIOUMON_ANIM_INDEX ,DMALL_GIGA_SEADRAMON_ANIM_INDEX ,DMALL_GRAND_LOCOMON_ANIM_INDEX ,DMALL_GUNDRAMON_ANIM_INDEX ,DMALL_HERAKLE_KABUTERIMON_ANIM_INDEX ,DMALL_HI_ANDROMON_ANIM_INDEX ,DMALL_MEGIDRAMON_ANIM_INDEX ,DMALL_METAL_GARURUMON_BLACK_ANIM_INDEX ,DMALL_METAL_SEADRAMON_ANIM_INDEX ,DMALL_MUGENDRAMON_ANIM_INDEX
                },
              };
            case DMALL_GIGA_SEADRAMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = 230400 },
                
                .num_animation_indices = 2,
                .animation_indices = {
                  DMALL_LEVIAMON_X_ANIM_INDEX ,DMALL_BARBAMON_X_ANIM_INDEX
                },
              };
            case DMALL_GIGIMON_ANIM_INDEX:
              return {
                // Stage: Baby II
                .conditions = { .next_evolution_time_sec = 43200 },
                
                .num_animation_indices = 11,
                .animation_indices = {
                  DMALL_GUILMON_ANIM_INDEX ,DMALL_AGUMON_ANIM_INDEX ,DMALL_CANDMON_ANIM_INDEX ,DMALL_DORUMON_ANIM_INDEX ,DMALL_GUILMON_ANIM_INDEX ,DMALL_HACKMON_ANIM_INDEX ,DMALL_HAGURUMON_ANIM_INDEX ,DMALL_PICO_DEVIMON_ANIM_INDEX ,DMALL_SOLARMON_ANIM_INDEX ,DMALL_TENTOMON_ANIM_INDEX ,DMALL_V_MON_ANIM_INDEX
                },
              };
            case DMALL_GINRYUMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_HISYARYUMON_ANIM_INDEX ,DMALL_HISYARYUMON_ANIM_INDEX ,DMALL_MONZAEMON_X_ANIM_INDEX ,DMALL_ANGEWOMON_X_ANIM_INDEX ,DMALL_ANOMALOCARIMON_X_ANIM_INDEX ,DMALL_GRADEMON_ANIM_INDEX ,DMALL_MAMEMON_X_ANIM_INDEX ,DMALL_CRYS_PALEDRAMON_ANIM_INDEX ,DMALL_JAZARICHMON_ANIM_INDEX ,DMALL_PUMPMON_ANIM_INDEX ,DMALL_ASURAMON_ANIM_INDEX ,DMALL_CANNONBEEMON_ANIM_INDEX ,DMALL_DURAMON_ANIM_INDEX ,DMALL_GRADEMON_ANIM_INDEX ,DMALL_HISYARYUMON_ANIM_INDEX
                },
              };
            case DMALL_GIROMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_GOKUMON_ANIM_INDEX ,DMALL_CHAOSDRAMON_ANIM_INDEX ,DMALL_CRANIUMMON_ANIM_INDEX ,DMALL_DEATHMON_ANIM_INDEX ,DMALL_GIGA_SEADRAMON_ANIM_INDEX ,DMALL_GOKUMON_ANIM_INDEX ,DMALL_HI_ANDROMON_ANIM_INDEX ,DMALL_HOLYDRAMON_ANIM_INDEX ,DMALL_METAL_ETEMON_ANIM_INDEX ,DMALL_MUGENDRAMON_ANIM_INDEX ,DMALL_PLESIOMON_ANIM_INDEX ,DMALL_PRINCE_MAMEMON_ANIM_INDEX ,DMALL_PUKUMON_ANIM_INDEX ,DMALL_RAIDENMON_ANIM_INDEX ,DMALL_SERAPHIMON_ANIM_INDEX
                },
              };
            case DMALL_GIZAMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_BLACK_GROWMON_ANIM_INDEX ,DMALL_COELAMON_ANIM_INDEX ,DMALL_CYCLOMON_ANIM_INDEX ,DMALL_DEVIMON_ANIM_INDEX ,DMALL_DOBERMON_ANIM_INDEX ,DMALL_DRIMOGEMON_ANIM_INDEX ,DMALL_EBIDRAMON_ANIM_INDEX ,DMALL_GEKOMON_ANIM_INDEX ,DMALL_GEREMON_ANIM_INDEX ,DMALL_GESOMON_ANIM_INDEX ,DMALL_HANUMON_ANIM_INDEX ,DMALL_ICE_DEVIMON_ANIM_INDEX ,DMALL_KUWAGAMON_ANIM_INDEX ,DMALL_KYUBIMON_ANIM_INDEX ,DMALL_MEICOOMON_ANIM_INDEX
                },
              };
            case DMALL_GODDRAMON_X_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = 230400 },
                
                .num_animation_indices = 8,
                .animation_indices = {
                  DMALL_ULFORCE_V_DRAMON_X_ANIM_INDEX ,DMALL_EXAMON_X_ANIM_INDEX ,DMALL_DUFTMON_X_ANIM_INDEX ,DMALL_SLEIPMON_X_ANIM_INDEX ,DMALL_JESMON_X_ANIM_INDEX ,DMALL_OMEGAMON_X_ANIM_INDEX ,DMALL_ALPHAMON_OURYUKEN_ANIM_INDEX ,DMALL_JESMON_GX_ANIM_INDEX
                },
              };
            case DMALL_GOGMAMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 3,
                .animation_indices = {
                  DMALL_ANCIENT_SPHINXMON_ANIM_INDEX ,DMALL_DINOREXMON_ANIM_INDEX ,DMALL_HOLYDRAMON_ANIM_INDEX
                },
              };
            case DMALL_GOKIMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 9,
                .animation_indices = {
                  DMALL_ARCHNEMON_ANIM_INDEX ,DMALL_ATLUR_KABUTERIMON_BLUE_ANIM_INDEX ,DMALL_GERBEMON_ANIM_INDEX ,DMALL_OKUWAMON_ANIM_INDEX ,DMALL_OROCHIMON_ANIM_INDEX ,DMALL_PAILDRAMON_ANIM_INDEX ,DMALL_SCORPIOMON_ANIM_INDEX ,DMALL_TONOSAMA_GEKOMON_ANIM_INDEX ,DMALL_VAMDEMON_ANIM_INDEX
                },
              };
            case DMALL_GOKUMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMALL_GOLD_NUMEMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 5,
                .animation_indices = {
                  DMALL_BLACK_KING_NUMEMON_ANIM_INDEX ,DMALL_MONZAEMON_ANIM_INDEX ,DMALL_VADEMON_ANIM_INDEX ,DMALL_WARU_MONZAEMON_ANIM_INDEX ,DMALL_WARU_SEADRAMON_ANIM_INDEX
                },
              };
            case DMALL_GOLD_V_DRAMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 3,
                .animation_indices = {
                  DMALL_AERO_V_DRAMON_ANIM_INDEX ,DMALL_MEGA_SEADRAMON_ANIM_INDEX ,DMALL_METAL_GREYMON_ANIM_INDEX
                },
              };
            case DMALL_GOMAMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_IKKAKUMON_ANIM_INDEX ,DMALL_COELAMON_ANIM_INDEX ,DMALL_DRIMOGEMON_ANIM_INDEX ,DMALL_EBIDRAMON_ANIM_INDEX ,DMALL_GAOGAMON_ANIM_INDEX ,DMALL_GARURUMON_ANIM_INDEX ,DMALL_GAWAPPAMON_ANIM_INDEX ,DMALL_GESOMON_ANIM_INDEX ,DMALL_HYOUGAMON_ANIM_INDEX ,DMALL_ICE_DEVIMON_ANIM_INDEX ,DMALL_ICEMON_ANIM_INDEX ,DMALL_IKKAKUMON_ANIM_INDEX ,DMALL_LEOMON_ANIM_INDEX ,DMALL_MEICOOMON_ANIM_INDEX ,DMALL_NUMEMON_ANIM_INDEX
                },
              };
            case DMALL_GOMAMON_X_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 11,
                .animation_indices = {
                  DMALL_MANTARAYMON_X_ANIM_INDEX ,DMALL_KUWAGAMON_X_ANIM_INDEX ,DMALL_ALLOMON_X_ANIM_INDEX ,DMALL_COELAMON_ANIM_INDEX ,DMALL_EBIDRAMON_ANIM_INDEX ,DMALL_GAWAPPAMON_ANIM_INDEX ,DMALL_GESOMON_ANIM_INDEX ,DMALL_IKKAKUMON_ANIM_INDEX ,DMALL_RUKAMON_ANIM_INDEX ,DMALL_SUNFLOWMON_ANIM_INDEX ,DMALL_WHAMON_ANIM_INDEX
                },
              };
            case DMALL_GOROMON_ANIM_INDEX:
              return {
                // Stage: Baby II
                .conditions = { .next_evolution_time_sec = 43200 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DMALL_SUNARIZAMON_ANIM_INDEX
                },
              };
            case DMALL_GOTSUMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_ICEMON_ANIM_INDEX ,DMALL_MONOCHROMON_ANIM_INDEX ,DMALL_AIRDRAMON_ANIM_INDEX ,DMALL_CLOCKMON_ANIM_INDEX ,DMALL_CYCLOMON_ANIM_INDEX ,DMALL_DOKUGUMON_ANIM_INDEX ,DMALL_GARURUMON_ANIM_INDEX ,DMALL_GEKOMON_ANIM_INDEX ,DMALL_GEREMON_ANIM_INDEX ,DMALL_GOLD_V_DRAMON_ANIM_INDEX ,DMALL_GREYMON_ANIM_INDEX ,DMALL_GROWMON_ANIM_INDEX ,DMALL_GUARDROMON_ANIM_INDEX ,DMALL_HANUMON_ANIM_INDEX ,DMALL_ICEMON_ANIM_INDEX
                },
              };
            case DMALL_GRACE_NOVAMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMALL_GRADEMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_ALPHAMON_ANIM_INDEX ,DMALL_RAPIDMON_X_ANIM_INDEX ,DMALL_JUSTIMON_X_ANIM_INDEX ,DMALL_ALPHAMON_ANIM_INDEX ,DMALL_HOUOUMON_X_ANIM_INDEX ,DMALL_TIGER_VESPAMON_ANIM_INDEX ,DMALL_GAIOUMON_ANIM_INDEX ,DMALL_DINOTIGERMON_ANIM_INDEX ,DMALL_HOLYDRAMON_X_ANIM_INDEX ,DMALL_EBEMON_X_ANIM_INDEX ,DMALL_HEXEBLAUMON_ANIM_INDEX ,DMALL_METALLICDRAMON_ANIM_INDEX ,DMALL_NOBLE_PUMPMON_ANIM_INDEX ,DMALL_ALPHAMON_ANIM_INDEX ,DMALL_DORUGORAMON_ANIM_INDEX
                },
              };
            case DMALL_GRAND_DRACUMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMALL_GRANDIS_KUWAGAMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = 230400 },
                
                .num_animation_indices = 2,
                .animation_indices = {
                  DMALL_LEVIAMON_X_ANIM_INDEX ,DMALL_BARBAMON_X_ANIM_INDEX
                },
              };
            case DMALL_GRAND_LOCOMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMALL_GRAPPLEOMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 8,
                .animation_indices = {
                  DMALL_SABER_LEOMON_ANIM_INDEX ,DMALL_APOLLOMON_ANIM_INDEX ,DMALL_BANCHO_LEOMON_ANIM_INDEX ,DMALL_DINOTIGERMON_ANIM_INDEX ,DMALL_DUFTMON_ANIM_INDEX ,DMALL_GRIFFOMON_ANIM_INDEX ,DMALL_SABER_LEOMON_ANIM_INDEX ,DMALL_SAINT_GALGOMON_ANIM_INDEX
                },
              };
            case DMALL_GREAT_KING_SCUMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 2,
                .animation_indices = {
                  DMALL_KING_ETEMON_ANIM_INDEX ,DMALL_METAL_ETEMON_ANIM_INDEX
                },
              };
            case DMALL_GREYMON_2010_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_BIG_MAMEMON_ANIM_INDEX ,DMALL_CHIMAIRAMON_ANIM_INDEX ,DMALL_CYBERDRAMON_ANIM_INDEX ,DMALL_DORUGUREMON_ANIM_INDEX ,DMALL_KNIGHTMON_ANIM_INDEX ,DMALL_MAMEMON_ANIM_INDEX ,DMALL_MEGADRAMON_ANIM_INDEX ,DMALL_MEGALO_GROWMON_ANIM_INDEX ,DMALL_METAL_GREYMON_ANIM_INDEX ,DMALL_METAL_GREYMON_VIRUS_ANIM_INDEX ,DMALL_METAL_TYRANOMON_ANIM_INDEX ,DMALL_OROCHIMON_ANIM_INDEX ,DMALL_PAILDRAMON_ANIM_INDEX ,DMALL_RIZE_GREYMON_ANIM_INDEX ,DMALL_SKULL_GREYMON_ANIM_INDEX
                },
              };
            case DMALL_GREYMON_BLUE_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_METAL_GREYMON_VIRUS_ANIM_INDEX ,DMALL_BIG_MAMEMON_ANIM_INDEX ,DMALL_CHIMAIRAMON_ANIM_INDEX ,DMALL_CYBERDRAMON_ANIM_INDEX ,DMALL_DORUGUREMON_ANIM_INDEX ,DMALL_GIGADRAMON_ANIM_INDEX ,DMALL_KNIGHTMON_ANIM_INDEX ,DMALL_MAMEMON_ANIM_INDEX ,DMALL_MAMETYRAMON_ANIM_INDEX ,DMALL_MEGADRAMON_ANIM_INDEX ,DMALL_MEGALO_GROWMON_ANIM_INDEX ,DMALL_METAL_GREYMON_ANIM_INDEX ,DMALL_METAL_GREYMON_VIRUS_ANIM_INDEX ,DMALL_METAL_TYRANOMON_ANIM_INDEX ,DMALL_OROCHIMON_ANIM_INDEX
                },
              };
            case DMALL_GREYMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_METAL_GREYMON_ANIM_INDEX ,DMALL_BIG_MAMEMON_ANIM_INDEX ,DMALL_CHIMAIRAMON_ANIM_INDEX ,DMALL_CYBERDRAMON_ANIM_INDEX ,DMALL_DORUGUREMON_ANIM_INDEX ,DMALL_KNIGHTMON_ANIM_INDEX ,DMALL_MAMEMON_ANIM_INDEX ,DMALL_MEGADRAMON_ANIM_INDEX ,DMALL_MEGALO_GROWMON_ANIM_INDEX ,DMALL_METAL_GREYMON_ANIM_INDEX ,DMALL_METAL_GREYMON_VIRUS_ANIM_INDEX ,DMALL_METAL_TYRANOMON_ANIM_INDEX ,DMALL_OROCHIMON_ANIM_INDEX ,DMALL_PAILDRAMON_ANIM_INDEX ,DMALL_RIZE_GREYMON_ANIM_INDEX
                },
              };
            case DMALL_GREYMON_X_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 5,
                .animation_indices = {
                  DMALL_METAL_GREYMON_ANIM_INDEX ,DMALL_METAL_GREYMON_VIRUS_ANIM_INDEX ,DMALL_METAL_TYRANOMON_ANIM_INDEX ,DMALL_RIZE_GREYMON_ANIM_INDEX ,DMALL_SKULL_GREYMON_ANIM_INDEX
                },
              };
            case DMALL_GRIFFOMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMALL_GROWMON_ORANGE_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 9,
                .animation_indices = {
                  DMALL_MEGALO_GROWMON_ORANGE_ANIM_INDEX ,DMALL_BLACK_MEGALO_GROWMON_ANIM_INDEX ,DMALL_GIGADRAMON_ANIM_INDEX ,DMALL_MEGALO_GROWMON_ANIM_INDEX ,DMALL_MEGALO_GROWMON_ORANGE_ANIM_INDEX ,DMALL_METAL_GREYMON_ANIM_INDEX ,DMALL_METAL_GREYMON_VIRUS_ANIM_INDEX ,DMALL_OROCHIMON_ANIM_INDEX ,DMALL_RIZE_GREYMON_ANIM_INDEX
                },
              };
            case DMALL_GROWMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_MEGALO_GROWMON_ANIM_INDEX ,DMALL_SKULL_GREYMON_ANIM_INDEX ,DMALL_AERO_V_DRAMON_ANIM_INDEX ,DMALL_ANOMALOCARIMON_ANIM_INDEX ,DMALL_ASTAMON_ANIM_INDEX ,DMALL_ASURAMON_ANIM_INDEX ,DMALL_BEOWOLFMON_ANIM_INDEX ,DMALL_BIG_MAMEMON_ANIM_INDEX ,DMALL_BLACK_MEGALO_GROWMON_ANIM_INDEX ,DMALL_BLUE_MERAMON_ANIM_INDEX ,DMALL_DAGOMON_ANIM_INDEX ,DMALL_DARK_KNIGHTMON_ANIM_INDEX ,DMALL_DIGITAMAMON_ANIM_INDEX ,DMALL_DORUGUREMON_ANIM_INDEX ,DMALL_ETEMON_ANIM_INDEX
                },
              };
            case DMALL_GROWMON_X_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 14,
                .animation_indices = {
                  DMALL_MEGALO_GROWMON_X_ANIM_INDEX ,DMALL_METAL_TYRANOMON_X_ANIM_INDEX ,DMALL_YATAGARAMON_ANIM_INDEX ,DMALL_BLACK_MEGALO_GROWMON_ANIM_INDEX ,DMALL_HISYARYUMON_ANIM_INDEX ,DMALL_GIGADRAMON_ANIM_INDEX ,DMALL_MAMETYRAMON_ANIM_INDEX ,DMALL_MEGALO_GROWMON_ANIM_INDEX ,DMALL_MEGALO_GROWMON_ORANGE_ANIM_INDEX ,DMALL_MEGA_SEADRAMON_ANIM_INDEX ,DMALL_METAL_GREYMON_VIRUS_ANIM_INDEX ,DMALL_OROCHIMON_ANIM_INDEX ,DMALL_RIZE_GREYMON_ANIM_INDEX ,DMALL_SKULL_BALUCHIMON_ANIM_INDEX
                },
              };
            case DMALL_GRYZMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 10,
                .animation_indices = {
                  DMALL_ASTAMON_ANIM_INDEX ,DMALL_CATURAMON_ANIM_INDEX ,DMALL_CYBERDRAMON_ANIM_INDEX ,DMALL_DELUMON_ANIM_INDEX ,DMALL_MACH_GAOGAMON_ANIM_INDEX ,DMALL_MAMMON_ANIM_INDEX ,DMALL_MONZAEMON_ANIM_INDEX ,DMALL_NANOMON_ANIM_INDEX ,DMALL_PANDAMON_ANIM_INDEX ,DMALL_WERE_GARURUMON_ANIM_INDEX
                },
              };
            case DMALL_GUARDROMON_GOLD_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 6,
                .animation_indices = {
                  DMALL_ANDROMON_ANIM_INDEX ,DMALL_CANNONBEEMON_ANIM_INDEX ,DMALL_DURAMON_ANIM_INDEX ,DMALL_GRADEMON_ANIM_INDEX ,DMALL_METAL_MAMEMON_ANIM_INDEX ,DMALL_NANOMON_ANIM_INDEX
                },
              };
            case DMALL_GUARDROMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_ANDROMON_ANIM_INDEX ,DMALL_AERO_V_DRAMON_ANIM_INDEX ,DMALL_ANDROMON_ANIM_INDEX ,DMALL_ANOMALOCARIMON_ANIM_INDEX ,DMALL_ASTAMON_ANIM_INDEX ,DMALL_ASURAMON_ANIM_INDEX ,DMALL_BEOWOLFMON_ANIM_INDEX ,DMALL_BIG_MAMEMON_ANIM_INDEX ,DMALL_CHIMAIRAMON_ANIM_INDEX ,DMALL_DAGOMON_ANIM_INDEX ,DMALL_DARK_KNIGHTMON_ANIM_INDEX ,DMALL_ETEMON_ANIM_INDEX ,DMALL_GERBEMON_ANIM_INDEX ,DMALL_GIGADRAMON_ANIM_INDEX ,DMALL_HANGYOMON_ANIM_INDEX
                },
              };
            case DMALL_GUILMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_BLACK_GROWMON_ANIM_INDEX ,DMALL_GROWMON_ANIM_INDEX ,DMALL_AIRDRAMON_ANIM_INDEX ,DMALL_BIRDRAMON_ANIM_INDEX ,DMALL_BLACK_GROWMON_ANIM_INDEX ,DMALL_CENTALMON_ANIM_INDEX ,DMALL_CYCLOMON_ANIM_INDEX ,DMALL_DEATH_X_DORUGAMON_ANIM_INDEX ,DMALL_DEVIMON_ANIM_INDEX ,DMALL_EBIDRAMON_ANIM_INDEX ,DMALL_GEREMON_ANIM_INDEX ,DMALL_GESOMON_ANIM_INDEX ,DMALL_GEO_GREYMON_ANIM_INDEX ,DMALL_GINRYUMON_ANIM_INDEX ,DMALL_GREYMON_ANIM_INDEX
                },
              };
            case DMALL_GUILMON_X_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_BLACK_GROWMON_ANIM_INDEX ,DMALL_CENTALMON_ANIM_INDEX ,DMALL_CYCLOMON_ANIM_INDEX ,DMALL_DEATH_X_DORUGAMON_ANIM_INDEX ,DMALL_EBIDRAMON_ANIM_INDEX ,DMALL_GEO_GREYMON_ANIM_INDEX ,DMALL_GESOMON_ANIM_INDEX ,DMALL_GINRYUMON_ANIM_INDEX ,DMALL_GREYMON_BLUE_ANIM_INDEX ,DMALL_GROWMON_ANIM_INDEX ,DMALL_GROWMON_ORANGE_ANIM_INDEX ,DMALL_KYUBIMON_ANIM_INDEX ,DMALL_LEOMON_ANIM_INDEX ,DMALL_MECHANORIMON_ANIM_INDEX ,DMALL_MERAMON_ANIM_INDEX
                },
              };
            case DMALL_GUMMYMON_ANIM_INDEX:
              return {
                // Stage: Baby II
                .conditions = { .next_evolution_time_sec = 43200 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_TERRIERMON_ANIM_INDEX ,DMALL_TERRIERMON_X_ANIM_INDEX ,DMALL_PALMON_X_ANIM_INDEX ,DMALL_DORUMON_ANIM_INDEX ,DMALL_BLUCOMON_ANIM_INDEX ,DMALL_JAZAMON_ANIM_INDEX ,DMALL_ARMADIMON_ANIM_INDEX ,DMALL_BAKUMON_ANIM_INDEX ,DMALL_BLUCOMON_ANIM_INDEX ,DMALL_CLEAR_AGUMON_ANIM_INDEX ,DMALL_DORUMON_ANIM_INDEX ,DMALL_GAOMON_ANIM_INDEX ,DMALL_HAGURUMON_ANIM_INDEX ,DMALL_JAZAMON_ANIM_INDEX ,DMALL_RENAMON_ANIM_INDEX
                },
              };
            case DMALL_GUNDRAMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMALL_GURURUMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 8,
                .animation_indices = {
                  DMALL_ASTAMON_ANIM_INDEX ,DMALL_BLACK_MEGALO_GROWMON_ANIM_INDEX ,DMALL_BLUE_MERAMON_ANIM_INDEX ,DMALL_MACH_GAOGAMON_ANIM_INDEX ,DMALL_MAMMON_ANIM_INDEX ,DMALL_OKUWAMON_ANIM_INDEX ,DMALL_TRICERAMON_ANIM_INDEX ,DMALL_WERE_GARURUMON_ANIM_INDEX
                },
              };
            case DMALL_GUSOKUMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 5,
                .animation_indices = {
                  DMALL_AEGISDRAMON_ANIM_INDEX ,DMALL_ANCIENT_MERMAIMON_ANIM_INDEX ,DMALL_METAL_SEADRAMON_ANIM_INDEX ,DMALL_PLESIOMON_ANIM_INDEX ,DMALL_REGALECUSMON_ANIM_INDEX
                },
              };
            case DMALL_HACKMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_GEO_GREYMON_ANIM_INDEX ,DMALL_GEREMON_ANIM_INDEX ,DMALL_GOLD_V_DRAMON_ANIM_INDEX ,DMALL_GREYMON_ANIM_INDEX ,DMALL_GROWMON_ANIM_INDEX ,DMALL_GURURUMON_ANIM_INDEX ,DMALL_LEOMON_ANIM_INDEX ,DMALL_MONOCHROMON_ANIM_INDEX ,DMALL_NUMEMON_ANIM_INDEX ,DMALL_PLATINUM_SCUMON_ANIM_INDEX ,DMALL_RED_V_DRAMON_ANIM_INDEX ,DMALL_SCUMON_ANIM_INDEX ,DMALL_TAILMON_ANIM_INDEX ,DMALL_TARGETMON_ANIM_INDEX ,DMALL_XV_MON_ANIM_INDEX
                },
              };
            case DMALL_HAGURUMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_GUARDROMON_ANIM_INDEX ,DMALL_GUARDROMON_GOLD_ANIM_INDEX ,DMALL_CENTALMON_ANIM_INDEX ,DMALL_CLOCKMON_ANIM_INDEX ,DMALL_COELAMON_ANIM_INDEX ,DMALL_CYCLOMON_ANIM_INDEX ,DMALL_DEVIMON_ANIM_INDEX ,DMALL_DOBERMON_ANIM_INDEX ,DMALL_GALGOMON_ANIM_INDEX ,DMALL_GEREMON_ANIM_INDEX ,DMALL_GOLD_NUMEMON_ANIM_INDEX ,DMALL_GOLD_V_DRAMON_ANIM_INDEX ,DMALL_GREYMON_ANIM_INDEX ,DMALL_GROWMON_ANIM_INDEX ,DMALL_GUARDROMON_ANIM_INDEX
                },
              };
            case DMALL_HANGYOMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 10,
                .animation_indices = {
                  DMALL_ANCIENT_MERMAIMON_ANIM_INDEX ,DMALL_BOLTMON_ANIM_INDEX ,DMALL_CTHYLLAMON_ANIM_INDEX ,DMALL_GRIFFOMON_ANIM_INDEX ,DMALL_MARIN_ANGEMON_ANIM_INDEX ,DMALL_METAL_GARURUMON_ANIM_INDEX ,DMALL_METAL_SEADRAMON_ANIM_INDEX ,DMALL_PLESIOMON_ANIM_INDEX ,DMALL_PUKUMON_ANIM_INDEX ,DMALL_SABER_LEOMON_ANIM_INDEX
                },
              };
            case DMALL_HANUMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_AERO_V_DRAMON_ANIM_INDEX ,DMALL_ANDROMON_ANIM_INDEX ,DMALL_ANGEWOMON_ANIM_INDEX ,DMALL_ASURAMON_ANIM_INDEX ,DMALL_BAALMON_ANIM_INDEX ,DMALL_BIG_MAMEMON_ANIM_INDEX ,DMALL_CYBERDRAMON_ANIM_INDEX ,DMALL_DURAMON_ANIM_INDEX ,DMALL_GARUDAMON_ANIM_INDEX ,DMALL_HANGYOMON_ANIM_INDEX ,DMALL_HOLY_ANGEMON_ANIM_INDEX ,DMALL_JYAGAMON_ANIM_INDEX ,DMALL_MAMMON_ANIM_INDEX ,DMALL_MEGADRAMON_ANIM_INDEX ,DMALL_MONZAEMON_ANIM_INDEX
                },
              };
            case DMALL_HERAKLE_KABUTERIMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMALL_HERISSMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 7,
                .animation_indices = {
                  DMALL_FILMON_ANIM_INDEX ,DMALL_SANGLOUPMON_ANIM_INDEX ,DMALL_TYRANOMON_X_ANIM_INDEX ,DMALL_DAMEMON_ANIM_INDEX ,DMALL_DAMEMON_ANIM_INDEX ,DMALL_FILMON_ANIM_INDEX ,DMALL_SANGLOUPMON_ANIM_INDEX
                },
              };
            case DMALL_HEXEBLAUMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = 230400 },
                
                .num_animation_indices = 7,
                .animation_indices = {
                  DMALL_MAGNAMON_X_ANIM_INDEX ,DMALL_GANKOOMON_X_ANIM_INDEX ,DMALL_DYNASMON_X_ANIM_INDEX ,DMALL_CRANIUMMON_X_ANIM_INDEX ,DMALL_DUKEMON_X_ANIM_INDEX ,DMALL_ALPHAMON_OURYUKEN_ANIM_INDEX ,DMALL_JESMON_GX_ANIM_INDEX
                },
              };
            case DMALL_HI_ANDROMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMALL_HISYARYUMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_OURYUMON_ANIM_INDEX ,DMALL_CHERUBIMON_VIRTUE_X_ANIM_INDEX ,DMALL_GODDRAMON_X_ANIM_INDEX ,DMALL_OURYUMON_ANIM_INDEX ,DMALL_PLESIOMON_X_ANIM_INDEX ,DMALL_GAIOUMON_ANIM_INDEX ,DMALL_DINOTIGERMON_ANIM_INDEX ,DMALL_HOLYDRAMON_X_ANIM_INDEX ,DMALL_EBEMON_X_ANIM_INDEX ,DMALL_HEXEBLAUMON_ANIM_INDEX ,DMALL_METALLICDRAMON_ANIM_INDEX ,DMALL_NOBLE_PUMPMON_ANIM_INDEX ,DMALL_ALPHAMON_ANIM_INDEX ,DMALL_DINOREXMON_ANIM_INDEX ,DMALL_DINOTIGERMON_ANIM_INDEX
                },
              };
            case DMALL_HIYARIMON_ANIM_INDEX:
              return {
                // Stage: Baby II
                .conditions = { .next_evolution_time_sec = 43200 },
                
                .num_animation_indices = 3,
                .animation_indices = {
                  DMALL_BEARMON_ANIM_INDEX ,DMALL_BLUCOMON_ANIM_INDEX ,DMALL_PENMON_ANIM_INDEX
                },
              };
            case DMALL_HOLY_ANGEMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_SERAPHIMON_ANIM_INDEX ,DMALL_ALPHAMON_ANIM_INDEX ,DMALL_BARBAMON_ANIM_INDEX ,DMALL_BEELZEBUMON_ANIM_INDEX ,DMALL_BELIAL_VAMDEMON_ANIM_INDEX ,DMALL_BLACK_SERAPHIMON_ANIM_INDEX ,DMALL_CHERUBIMON_VIRTUE_ANIM_INDEX ,DMALL_DEMON_ANIM_INDEX ,DMALL_DUKEMON_ANIM_INDEX ,DMALL_HOLYDRAMON_ANIM_INDEX ,DMALL_HOUOUMON_ANIM_INDEX ,DMALL_LILITHMON_ANIM_INDEX ,DMALL_MARIN_ANGEMON_ANIM_INDEX ,DMALL_METAL_ETEMON_ANIM_INDEX ,DMALL_OMEGAMON_ANIM_INDEX
                },
              };
            case DMALL_HOLY_DIGITAMAMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMALL_HOLYDRAMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMALL_HOLYDRAMON_X_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = 230400 },
                
                .num_animation_indices = 7,
                .animation_indices = {
                  DMALL_MAGNAMON_X_ANIM_INDEX ,DMALL_GANKOOMON_X_ANIM_INDEX ,DMALL_DYNASMON_X_ANIM_INDEX ,DMALL_CRANIUMMON_X_ANIM_INDEX ,DMALL_DUKEMON_X_ANIM_INDEX ,DMALL_ALPHAMON_OURYUKEN_ANIM_INDEX ,DMALL_JESMON_GX_ANIM_INDEX
                },
              };
            case DMALL_HOOKMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 9,
                .animation_indices = {
                  DMALL_INSEKIMON_ANIM_INDEX ,DMALL_MERMAIMON_ANIM_INDEX ,DMALL_METAL_MAMEMON_ANIM_INDEX ,DMALL_PIRANIMON_ANIM_INDEX ,DMALL_SHAWUJINMON_ANIM_INDEX ,DMALL_SIRENMON_ANIM_INDEX ,DMALL_TONOSAMA_GEKOMON_ANIM_INDEX ,DMALL_WARU_SEADRAMON_ANIM_INDEX ,DMALL_ZUDOMON_ANIM_INDEX
                },
              };
            case DMALL_HOUOUMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMALL_HOUOUMON_X_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = 230400 },
                
                .num_animation_indices = 7,
                .animation_indices = {
                  DMALL_MAGNAMON_X_ANIM_INDEX ,DMALL_GANKOOMON_X_ANIM_INDEX ,DMALL_DYNASMON_X_ANIM_INDEX ,DMALL_CRANIUMMON_X_ANIM_INDEX ,DMALL_DUKEMON_X_ANIM_INDEX ,DMALL_ALPHAMON_OURYUKEN_ANIM_INDEX ,DMALL_JESMON_GX_ANIM_INDEX
                },
              };
            case DMALL_HYOKOMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 3,
                .animation_indices = {
                  DMALL_BIRDRAMON_ANIM_INDEX ,DMALL_DINOHUMON_ANIM_INDEX ,DMALL_KABUTERIMON_ANIM_INDEX
                },
              };
            case DMALL_HYOUGAMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 13,
                .animation_indices = {
                  DMALL_BLACK_MEGALO_GROWMON_ANIM_INDEX ,DMALL_BLUE_MERAMON_ANIM_INDEX ,DMALL_CRYS_PALEDRAMON_ANIM_INDEX ,DMALL_ETEMON_ANIM_INDEX ,DMALL_GIGADRAMON_ANIM_INDEX ,DMALL_HANGYOMON_ANIM_INDEX ,DMALL_MAMMON_ANIM_INDEX ,DMALL_PANJYAMON_ANIM_INDEX ,DMALL_TEKKAMON_ANIM_INDEX ,DMALL_VAMDEMON_ANIM_INDEX ,DMALL_WARU_MONZAEMON_ANIM_INDEX ,DMALL_WERE_GARURUMON_ANIM_INDEX ,DMALL_ZUDOMON_ANIM_INDEX
                },
              };
            case DMALL_ICE_DEVIMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 14,
                .animation_indices = {
                  DMALL_BAALMON_ANIM_INDEX ,DMALL_BLUE_MERAMON_ANIM_INDEX ,DMALL_CATURAMON_ANIM_INDEX ,DMALL_CRESCEMON_ANIM_INDEX ,DMALL_DAGOMON_ANIM_INDEX ,DMALL_GIGADRAMON_ANIM_INDEX ,DMALL_JYUREIMON_ANIM_INDEX ,DMALL_MARIN_DEVIMON_ANIM_INDEX ,DMALL_NEO_DEVIMON_ANIM_INDEX ,DMALL_PANJYAMON_ANIM_INDEX ,DMALL_SHAWUJINMON_ANIM_INDEX ,DMALL_SKULL_BALUCHIMON_ANIM_INDEX ,DMALL_VAMDEMON_ANIM_INDEX ,DMALL_ZUDOMON_ANIM_INDEX
                },
              };
            case DMALL_ICEMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_ASTAMON_ANIM_INDEX ,DMALL_BIG_MAMEMON_ANIM_INDEX ,DMALL_BLUE_MERAMON_ANIM_INDEX ,DMALL_CRESCEMON_ANIM_INDEX ,DMALL_CYBERDRAMON_ANIM_INDEX ,DMALL_ETEMON_ANIM_INDEX ,DMALL_HANGYOMON_ANIM_INDEX ,DMALL_INSEKIMON_ANIM_INDEX ,DMALL_MAMEMON_ANIM_INDEX ,DMALL_MAMMON_ANIM_INDEX ,DMALL_NANOMON_ANIM_INDEX ,DMALL_PANJYAMON_ANIM_INDEX ,DMALL_VADEMON_ANIM_INDEX ,DMALL_WERE_GARURUMON_ANIM_INDEX ,DMALL_ZUDOMON_ANIM_INDEX
                },
              };
            case DMALL_IGAMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_AERO_V_DRAMON_ANIM_INDEX ,DMALL_ANDROMON_ANIM_INDEX ,DMALL_ANGEWOMON_ANIM_INDEX ,DMALL_ANOMALOCARIMON_ANIM_INDEX ,DMALL_ASURAMON_ANIM_INDEX ,DMALL_BEOWOLFMON_ANIM_INDEX ,DMALL_BIG_MAMEMON_ANIM_INDEX ,DMALL_CYBERDRAMON_ANIM_INDEX ,DMALL_DAGOMON_ANIM_INDEX ,DMALL_DARK_KNIGHTMON_ANIM_INDEX ,DMALL_DURAMON_ANIM_INDEX ,DMALL_GARUDAMON_ANIM_INDEX ,DMALL_GERBEMON_ANIM_INDEX ,DMALL_GIROMON_ANIM_INDEX ,DMALL_HANGYOMON_ANIM_INDEX
                },
              };
            case DMALL_IKKAKUMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_ZUDOMON_ANIM_INDEX ,DMALL_AERO_V_DRAMON_ANIM_INDEX ,DMALL_ANDROMON_ANIM_INDEX ,DMALL_ANGEWOMON_ANIM_INDEX ,DMALL_ANOMALOCARIMON_ANIM_INDEX ,DMALL_ASURAMON_ANIM_INDEX ,DMALL_BAALMON_ANIM_INDEX ,DMALL_BIG_MAMEMON_ANIM_INDEX ,DMALL_BLACK_MEGALO_GROWMON_ANIM_INDEX ,DMALL_CYBERDRAMON_ANIM_INDEX ,DMALL_DURAMON_ANIM_INDEX ,DMALL_GARUDAMON_ANIM_INDEX ,DMALL_GIGADRAMON_ANIM_INDEX ,DMALL_HANGYOMON_ANIM_INDEX ,DMALL_JYAGAMON_ANIM_INDEX
                },
              };
            case DMALL_IMPERIALDRAMON_FIGHTER_MODE_BLACK_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMALL_IMPERIALDRAMON_FIGHTER_MODE_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMALL_IMPERIALDRAMON_PALADIN_MODE_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMALL_IMPMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_MERAMON_ANIM_INDEX ,DMALL_WIZARMON_ANIM_INDEX ,DMALL_AIRDRAMON_ANIM_INDEX ,DMALL_ANGEMON_ANIM_INDEX ,DMALL_BAKEMON_ANIM_INDEX ,DMALL_BLACK_GROWMON_ANIM_INDEX ,DMALL_BLACK_TAILMON_ANIM_INDEX ,DMALL_CLOCKMON_ANIM_INDEX ,DMALL_DEVIMON_ANIM_INDEX ,DMALL_FUGAMON_ANIM_INDEX ,DMALL_GOKIMON_ANIM_INDEX ,DMALL_GROWMON_ANIM_INDEX ,DMALL_GURURUMON_ANIM_INDEX ,DMALL_ICE_DEVIMON_ANIM_INDEX ,DMALL_KYUBIMON_ANIM_INDEX
                },
              };
            case DMALL_IMPMON_X_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 4,
                .animation_indices = {
                  DMALL_OGREMON_X_ANIM_INDEX ,DMALL_SEADRAMON_X_ANIM_INDEX ,DMALL_NUMEMON_X_ANIM_INDEX ,DMALL_ALLOMON_X_ANIM_INDEX
                },
              };
            case DMALL_INSEKIMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 6,
                .animation_indices = {
                  DMALL_BOLTMON_ANIM_INDEX ,DMALL_CHERUBIMON_VIRTUE_ANIM_INDEX ,DMALL_CRANIUMMON_ANIM_INDEX ,DMALL_DIANAMON_ANIM_INDEX ,DMALL_METAL_ETEMON_ANIM_INDEX ,DMALL_METAL_GARURUMON_ANIM_INDEX
                },
              };
            case DMALL_JAZAMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 12,
                .animation_indices = {
                  DMALL_JAZARDMON_ANIM_INDEX ,DMALL_SIESAMON_X_ANIM_INDEX ,DMALL_MERAMON_X_ANIM_INDEX ,DMALL_DORUGAMON_ANIM_INDEX ,DMALL_PTERANOMON_X_ANIM_INDEX ,DMALL_TOGEMON_X_ANIM_INDEX ,DMALL_OMEKAMON_ANIM_INDEX ,DMALL_PALEDRAMON_ANIM_INDEX ,DMALL_JAZARDMON_ANIM_INDEX ,DMALL_BIRDRAMON_ANIM_INDEX ,DMALL_JAZARDMON_ANIM_INDEX ,DMALL_OMEKAMON_ANIM_INDEX
                },
              };
            case DMALL_JAZARDMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 14,
                .animation_indices = {
                  DMALL_JAZARICHMON_ANIM_INDEX ,DMALL_OMEGA_SHOUTMON_X_ANIM_INDEX ,DMALL_CYBERDRAMON_X_ANIM_INDEX ,DMALL_DORUGUREMON_ANIM_INDEX ,DMALL_GARUDAMON_X_ANIM_INDEX ,DMALL_CANNONBEEMON_ANIM_INDEX ,DMALL_GRADEMON_ANIM_INDEX ,DMALL_MAMEMON_X_ANIM_INDEX ,DMALL_CRYS_PALEDRAMON_ANIM_INDEX ,DMALL_JAZARICHMON_ANIM_INDEX ,DMALL_PUMPMON_ANIM_INDEX ,DMALL_CANNONBEEMON_ANIM_INDEX ,DMALL_JAZARICHMON_ANIM_INDEX ,DMALL_PUMPMON_ANIM_INDEX
                },
              };
            case DMALL_JAZARICHMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_METALLICDRAMON_ANIM_INDEX ,DMALL_RAPIDMON_X_ANIM_INDEX ,DMALL_JUSTIMON_X_ANIM_INDEX ,DMALL_ALPHAMON_ANIM_INDEX ,DMALL_HOUOUMON_X_ANIM_INDEX ,DMALL_TIGER_VESPAMON_ANIM_INDEX ,DMALL_GAIOUMON_ANIM_INDEX ,DMALL_DINOTIGERMON_ANIM_INDEX ,DMALL_HOLYDRAMON_X_ANIM_INDEX ,DMALL_EBEMON_X_ANIM_INDEX ,DMALL_HEXEBLAUMON_ANIM_INDEX ,DMALL_METALLICDRAMON_ANIM_INDEX ,DMALL_NOBLE_PUMPMON_ANIM_INDEX ,DMALL_HOUOUMON_ANIM_INDEX ,DMALL_METALLICDRAMON_ANIM_INDEX
                },
              };
            case DMALL_JESMON_GX_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMALL_JESMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMALL_JESMON_X_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = 230400 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DMALL_ALPHAMON_ANIM_INDEX
                },
              };
            case DMALL_JUNKMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMALL_JUSTIMON_X_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = 230400 },
                
                .num_animation_indices = 7,
                .animation_indices = {
                  DMALL_MAGNAMON_X_ANIM_INDEX ,DMALL_GANKOOMON_X_ANIM_INDEX ,DMALL_DYNASMON_X_ANIM_INDEX ,DMALL_CRANIUMMON_X_ANIM_INDEX ,DMALL_DUKEMON_X_ANIM_INDEX ,DMALL_ALPHAMON_OURYUKEN_ANIM_INDEX ,DMALL_JESMON_GX_ANIM_INDEX
                },
              };
            case DMALL_JYAGAMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 10,
                .animation_indices = {
                  DMALL_ANCIENT_SPHINXMON_ANIM_INDEX ,DMALL_DEATHMON_ANIM_INDEX ,DMALL_DINOREXMON_ANIM_INDEX ,DMALL_HERAKLE_KABUTERIMON_ANIM_INDEX ,DMALL_HOLYDRAMON_ANIM_INDEX ,DMALL_MUGENDRAMON_ANIM_INDEX ,DMALL_PLESIOMON_ANIM_INDEX ,DMALL_ROSEMON_ANIM_INDEX ,DMALL_SABER_LEOMON_ANIM_INDEX ,DMALL_WAR_GREYMON_ANIM_INDEX
                },
              };
            case DMALL_JYARIMON_ANIM_INDEX:
              return {
                // Stage: Baby I
                .conditions = { .next_evolution_time_sec = 600 },
                
                .num_animation_indices = 2,
                .animation_indices = {
                  DMALL_GIGIMON_ANIM_INDEX ,DMALL_GIGIMON_ANIM_INDEX
                },
              };
            case DMALL_JYUREIMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 11,
                .animation_indices = {
                  DMALL_DEATHMON_ANIM_INDEX ,DMALL_PINOCHIMON_ANIM_INDEX ,DMALL_DARKDRAMON_ANIM_INDEX ,DMALL_DEATHMON_ANIM_INDEX ,DMALL_DEMON_ANIM_INDEX ,DMALL_KUZUHAMON_ANIM_INDEX ,DMALL_METAL_ETEMON_ANIM_INDEX ,DMALL_PIEMON_ANIM_INDEX ,DMALL_PINOCHIMON_ANIM_INDEX ,DMALL_PUKUMON_ANIM_INDEX ,DMALL_VENOM_VAMDEMON_ANIM_INDEX
                },
              };
            case DMALL_KABUTERIMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_ATLUR_KABUTERIMON_BLUE_ANIM_INDEX ,DMALL_ATLUR_KABUTERIMON_RED_ANIM_INDEX ,DMALL_CHIMAIRAMON_ANIM_INDEX ,DMALL_SKULL_GREYMON_ANIM_INDEX ,DMALL_AERO_V_DRAMON_ANIM_INDEX ,DMALL_ANDROMON_ANIM_INDEX ,DMALL_ANGEWOMON_ANIM_INDEX ,DMALL_ANOMALOCARIMON_ANIM_INDEX ,DMALL_ASURAMON_ANIM_INDEX ,DMALL_ATLUR_KABUTERIMON_BLUE_ANIM_INDEX ,DMALL_ATLUR_KABUTERIMON_RED_ANIM_INDEX ,DMALL_BAALMON_ANIM_INDEX ,DMALL_BIG_MAMEMON_ANIM_INDEX ,DMALL_CANNONBEEMON_ANIM_INDEX ,DMALL_CHIMAIRAMON_ANIM_INDEX
                },
              };
            case DMALL_KAISER_GREYMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMALL_KAISER_LEOMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 11,
                .animation_indices = {
                  DMALL_CHERUBIMON_VICE_X_ANIM_INDEX ,DMALL_DINOREXMON_ANIM_INDEX ,DMALL_RAIHIMON_ANIM_INDEX ,DMALL_BAGRAMON_ANIM_INDEX ,DMALL_BEEL_STARMON_X_ANIM_INDEX ,DMALL_ANCIENT_SPHINXMON_ANIM_INDEX ,DMALL_BAGRAMON_ANIM_INDEX ,DMALL_DEATHMON_ANIM_INDEX ,DMALL_DINOREXMON_ANIM_INDEX ,DMALL_DINOTIGERMON_ANIM_INDEX ,DMALL_ULTIMATE_BRACHIMON_ANIM_INDEX
                },
              };
            case DMALL_KAKKINMON_ANIM_INDEX:
              return {
                // Stage: Baby II
                .conditions = { .next_evolution_time_sec = 43200 },
                
                .num_animation_indices = 2,
                .animation_indices = {
                  DMALL_LUDOMON_ANIM_INDEX ,DMALL_LUDOMON_ANIM_INDEX
                },
              };
            case DMALL_KARATSUKI_NUMEMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_BLACK_KING_NUMEMON_ANIM_INDEX ,DMALL_DIGITAMAMON_ANIM_INDEX ,DMALL_MACH_GAOGAMON_ANIM_INDEX ,DMALL_MAMMON_ANIM_INDEX ,DMALL_MEGA_SEADRAMON_ANIM_INDEX ,DMALL_MERMAIMON_ANIM_INDEX ,DMALL_MONZAEMON_ANIM_INDEX ,DMALL_OROCHIMON_ANIM_INDEX ,DMALL_PANDAMON_ANIM_INDEX ,DMALL_PIRANIMON_ANIM_INDEX ,DMALL_RIZE_GREYMON_ANIM_INDEX ,DMALL_SHAWUJINMON_ANIM_INDEX ,DMALL_SIRENMON_ANIM_INDEX ,DMALL_TEKKAMON_ANIM_INDEX ,DMALL_TONOSAMA_GEKOMON_ANIM_INDEX
                },
              };
            case DMALL_KAZUCHIMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMALL_KERAMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 13,
                .animation_indices = {
                  DMALL_BAKEMON_ANIM_INDEX ,DMALL_DOKUGUMON_ANIM_INDEX ,DMALL_GARURUMON_ANIM_INDEX ,DMALL_GEREMON_ANIM_INDEX ,DMALL_GUARDROMON_ANIM_INDEX ,DMALL_KABUTERIMON_ANIM_INDEX ,DMALL_MECHANORIMON_ANIM_INDEX ,DMALL_MEICOOMON_ANIM_INDEX ,DMALL_NUMEMON_ANIM_INDEX ,DMALL_PLATINUM_SCUMON_ANIM_INDEX ,DMALL_SCUMON_ANIM_INDEX ,DMALL_SOULMON_ANIM_INDEX ,DMALL_WIZARMON_ANIM_INDEX
                },
              };
            case DMALL_KERAMON_X_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DMALL_DIABLOMON_X_ANIM_INDEX
                },
              };
            case DMALL_KETOMON_ANIM_INDEX:
              return {
                // Stage: Baby I
                .conditions = { .next_evolution_time_sec = 600 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMALL_KIIMON_ANIM_INDEX:
              return {
                // Stage: Baby I
                .conditions = { .next_evolution_time_sec = 600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DMALL_YAAMON_ANIM_INDEX
                },
              };
            case DMALL_KING_ETEMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMALL_KIWIMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_BLOSSOMON_ANIM_INDEX ,DMALL_SIRENMON_ANIM_INDEX ,DMALL_AERO_V_DRAMON_ANIM_INDEX ,DMALL_ANDROMON_ANIM_INDEX ,DMALL_ANOMALOCARIMON_ANIM_INDEX ,DMALL_ASURAMON_ANIM_INDEX ,DMALL_BEOWOLFMON_ANIM_INDEX ,DMALL_BIG_MAMEMON_ANIM_INDEX ,DMALL_BLOSSOMON_ANIM_INDEX ,DMALL_CYBERDRAMON_ANIM_INDEX ,DMALL_DAGOMON_ANIM_INDEX ,DMALL_DARK_KNIGHTMON_ANIM_INDEX ,DMALL_DELUMON_ANIM_INDEX ,DMALL_DURAMON_ANIM_INDEX ,DMALL_GARUDAMON_ANIM_INDEX
                },
              };
            case DMALL_KNIGHTMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 14,
                .animation_indices = {
                  DMALL_DUFTMON_ANIM_INDEX ,DMALL_ALPHAMON_ANIM_INDEX ,DMALL_BOLTMON_ANIM_INDEX ,DMALL_CHAOS_DUKEMON_ANIM_INDEX ,DMALL_CRANIUMMON_ANIM_INDEX ,DMALL_DUFTMON_ANIM_INDEX ,DMALL_DUKEMON_ANIM_INDEX ,DMALL_GRIFFOMON_ANIM_INDEX ,DMALL_METAL_GARURUMON_ANIM_INDEX ,DMALL_METAL_SEADRAMON_ANIM_INDEX ,DMALL_PLESIOMON_ANIM_INDEX ,DMALL_SABER_LEOMON_ANIM_INDEX ,DMALL_SERAPHIMON_ANIM_INDEX ,DMALL_WAR_GREYMON_ANIM_INDEX
                },
              };
            case DMALL_KOEMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 9,
                .animation_indices = {
                  DMALL_GREYMON_ANIM_INDEX ,DMALL_HANUMON_ANIM_INDEX ,DMALL_HOOKMON_ANIM_INDEX ,DMALL_IGAMON_ANIM_INDEX ,DMALL_KIWIMON_ANIM_INDEX ,DMALL_KOUGAMON_ANIM_INDEX ,DMALL_SHEEPMON_ANIM_INDEX ,DMALL_SHELLMON_ANIM_INDEX ,DMALL_TANKMON_ANIM_INDEX
                },
              };
            case DMALL_KOKABUTERIMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 4,
                .animation_indices = {
                  DMALL_HANUMON_ANIM_INDEX ,DMALL_KABUTERIMON_ANIM_INDEX ,DMALL_KUWAGAMON_ANIM_INDEX ,DMALL_THUNDERBALLMON_ANIM_INDEX
                },
              };
            case DMALL_KOKUWAMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_GUARDROMON_ANIM_INDEX ,DMALL_BITMON_ANIM_INDEX ,DMALL_BLACK_GALGOMON_ANIM_INDEX ,DMALL_CENTALMON_ANIM_INDEX ,DMALL_CLOCKMON_ANIM_INDEX ,DMALL_DEVIMON_ANIM_INDEX ,DMALL_EBIDRAMON_ANIM_INDEX ,DMALL_GUARDROMON_ANIM_INDEX ,DMALL_ICE_DEVIMON_ANIM_INDEX ,DMALL_KUWAGAMON_ANIM_INDEX ,DMALL_MECHANORIMON_ANIM_INDEX ,DMALL_RHINOMON_ANIM_INDEX ,DMALL_SHIMA_UNIMON_ANIM_INDEX ,DMALL_SOULMON_ANIM_INDEX ,DMALL_TANKMON_ANIM_INDEX
                },
              };
            case DMALL_KOKUWAMON_X_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_KUWAGAMON_X_ANIM_INDEX ,DMALL_FILMON_ANIM_INDEX ,DMALL_NUMEMON_X_ANIM_INDEX ,DMALL_VELGRMON_ANIM_INDEX ,DMALL_ALLOMON_X_ANIM_INDEX ,DMALL_BITMON_ANIM_INDEX ,DMALL_BLACK_GALGOMON_ANIM_INDEX ,DMALL_CLOCKMON_ANIM_INDEX ,DMALL_DEVIMON_ANIM_INDEX ,DMALL_EBIDRAMON_ANIM_INDEX ,DMALL_FILMON_ANIM_INDEX ,DMALL_GUARDROMON_ANIM_INDEX ,DMALL_ICE_DEVIMON_ANIM_INDEX ,DMALL_KUWAGAMON_ANIM_INDEX ,DMALL_MECHANORIMON_ANIM_INDEX
                },
              };
            case DMALL_KOROMON_ANIM_INDEX:
              return {
                // Stage: Baby II
                .conditions = { .next_evolution_time_sec = 43200 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_AGUMON_ANIM_INDEX ,DMALL_AGUMON_BLACK_ANIM_INDEX ,DMALL_YUKI_AGUMON_ANIM_INDEX ,DMALL_AGUMON_ANIM_INDEX ,DMALL_AGUMON_ANIM_INDEX ,DMALL_AGUMON_BLACK_ANIM_INDEX ,DMALL_CANDMON_ANIM_INDEX ,DMALL_GAOMON_ANIM_INDEX ,DMALL_GUILMON_ANIM_INDEX ,DMALL_HACKMON_ANIM_INDEX ,DMALL_JAZAMON_ANIM_INDEX ,DMALL_KUNEMON_ANIM_INDEX ,DMALL_LALAMON_ANIM_INDEX ,DMALL_LUCEMON_ANIM_INDEX ,DMALL_PICO_DEVIMON_ANIM_INDEX
                },
              };
            case DMALL_KOUGAMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 5,
                .animation_indices = {
                  DMALL_DEATH_MERAMON_ANIM_INDEX ,DMALL_GIROMON_ANIM_INDEX ,DMALL_JYUREIMON_ANIM_INDEX ,DMALL_LILAMON_ANIM_INDEX ,DMALL_LILIMON_ANIM_INDEX
                },
              };
            case DMALL_KOZENIMON_ANIM_INDEX:
              return {
                // Stage: Baby II
                .conditions = { .next_evolution_time_sec = 43200 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMALL_KUNEMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_OGREMON_ANIM_INDEX ,DMALL_BAKEMON_ANIM_INDEX ,DMALL_SHELLMON_ANIM_INDEX ,DMALL_DRIMOGEMON_ANIM_INDEX ,DMALL_SCUMON_ANIM_INDEX ,DMALL_AIRDRAMON_ANIM_INDEX ,DMALL_BAKEMON_ANIM_INDEX ,DMALL_CENTALMON_ANIM_INDEX ,DMALL_DOKUGUMON_ANIM_INDEX ,DMALL_DRIMOGEMON_ANIM_INDEX ,DMALL_GOKIMON_ANIM_INDEX ,DMALL_KABUTERIMON_ANIM_INDEX ,DMALL_KUWAGAMON_ANIM_INDEX ,DMALL_NUMEMON_ANIM_INDEX ,DMALL_RED_VEGIMON_ANIM_INDEX
                },
              };
            case DMALL_KURAMON_ANIM_INDEX:
              return {
                // Stage: Baby I
                .conditions = { .next_evolution_time_sec = 600 },
                
                .num_animation_indices = 4,
                .animation_indices = {
                  DMALL_TSUMEMON_ANIM_INDEX ,DMALL_TSUMEMON_ANIM_INDEX ,DMALL_PAGUMON_ANIM_INDEX ,DMALL_TSUMEMON_ANIM_INDEX
                },
              };
            case DMALL_KUWAGAMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_CHIMAIRAMON_ANIM_INDEX ,DMALL_MEGADRAMON_ANIM_INDEX ,DMALL_METAL_TYRANOMON_ANIM_INDEX ,DMALL_OKUWAMON_ANIM_INDEX ,DMALL_PICCOLOMON_ANIM_INDEX ,DMALL_AERO_V_DRAMON_ANIM_INDEX ,DMALL_ANOMALOCARIMON_ANIM_INDEX ,DMALL_ARCHNEMON_ANIM_INDEX ,DMALL_ASTAMON_ANIM_INDEX ,DMALL_ASURAMON_ANIM_INDEX ,DMALL_ATLUR_KABUTERIMON_BLUE_ANIM_INDEX ,DMALL_ATLUR_KABUTERIMON_RED_ANIM_INDEX ,DMALL_BEOWOLFMON_ANIM_INDEX ,DMALL_BLOSSOMON_ANIM_INDEX ,DMALL_CANNONBEEMON_ANIM_INDEX
                },
              };
            case DMALL_KUWAGAMON_X_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 12,
                .animation_indices = {
                  DMALL_OKUWAMON_X_ANIM_INDEX ,DMALL_MAMETYRAMON_ANIM_INDEX ,DMALL_MAMMON_X_ANIM_INDEX ,DMALL_ARCHNEMON_ANIM_INDEX ,DMALL_ATLUR_KABUTERIMON_BLUE_ANIM_INDEX ,DMALL_BLOSSOMON_ANIM_INDEX ,DMALL_DORUGUREMON_ANIM_INDEX ,DMALL_MAMETYRAMON_ANIM_INDEX ,DMALL_OKUWAMON_ANIM_INDEX ,DMALL_PAILDRAMON_ANIM_INDEX ,DMALL_SCORPIOMON_ANIM_INDEX ,DMALL_TONOSAMA_GEKOMON_ANIM_INDEX
                },
              };
            case DMALL_KUZUHAMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMALL_KYOKYOMON_ANIM_INDEX:
              return {
                // Stage: Baby II
                .conditions = { .next_evolution_time_sec = 43200 },
                
                .num_animation_indices = 3,
                .animation_indices = {
                  DMALL_RYUDAMON_ANIM_INDEX ,DMALL_COMMANDRAMON_ANIM_INDEX ,DMALL_RYUDAMON_ANIM_INDEX
                },
              };
            case DMALL_KYUBIMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 9,
                .animation_indices = {
                  DMALL_BLUE_MERAMON_ANIM_INDEX ,DMALL_CATURAMON_ANIM_INDEX ,DMALL_CHIMAIRAMON_ANIM_INDEX ,DMALL_MEPHISMON_ANIM_INDEX ,DMALL_MONZAEMON_ANIM_INDEX ,DMALL_PANJYAMON_ANIM_INDEX ,DMALL_VAMDEMON_ANIM_INDEX ,DMALL_WARU_MONZAEMON_ANIM_INDEX ,DMALL_WERE_GARURUMON_ANIM_INDEX
                },
              };
            case DMALL_KYUBIMON_SILVER_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 5,
                .animation_indices = {
                  DMALL_CHIMAIRAMON_ANIM_INDEX ,DMALL_GIGADRAMON_ANIM_INDEX ,DMALL_MEPHISMON_ANIM_INDEX ,DMALL_VAMDEMON_ANIM_INDEX ,DMALL_WARU_MONZAEMON_ANIM_INDEX
                },
              };
            case DMALL_LABRAMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 14,
                .animation_indices = {
                  DMALL_DOBERMON_ANIM_INDEX ,DMALL_ALGOMON_ADULT_ANIM_INDEX ,DMALL_BLACK_GALGOMON_ANIM_INDEX ,DMALL_COELAMON_ANIM_INDEX ,DMALL_DOBERMON_ANIM_INDEX ,DMALL_DOGMON_ANIM_INDEX ,DMALL_GALGOMON_ANIM_INDEX ,DMALL_GAOGAMON_ANIM_INDEX ,DMALL_GROWMON_ANIM_INDEX ,DMALL_IKKAKUMON_ANIM_INDEX ,DMALL_LEOMON_ANIM_INDEX ,DMALL_KYUBIMON_ANIM_INDEX ,DMALL_TOBUCATMON_ANIM_INDEX ,DMALL_XV_MON_ANIM_INDEX
                },
              };
            case DMALL_LADYDEVIMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_APOCALYMON_ANIM_INDEX ,DMALL_LILITHMON_ANIM_INDEX ,DMALL_MASTEMON_ANIM_INDEX ,DMALL_APOCALYMON_ANIM_INDEX ,DMALL_BEELZEBUMON_ANIM_INDEX ,DMALL_DARKDRAMON_ANIM_INDEX ,DMALL_DEATHMON_BLACK_ANIM_INDEX ,DMALL_DEMON_ANIM_INDEX ,DMALL_DIABLOMON_ANIM_INDEX ,DMALL_KUZUHAMON_ANIM_INDEX ,DMALL_LILITHMON_ANIM_INDEX ,DMALL_LOTUSMON_ANIM_INDEX ,DMALL_MASTEMON_ANIM_INDEX ,DMALL_METAL_ETEMON_ANIM_INDEX ,DMALL_METAL_GARURUMON_BLACK_ANIM_INDEX
                },
              };
            case DMALL_LADYDEVIMON_X_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DMALL_GRANDIS_KUWAGAMON_ANIM_INDEX
                },
              };
            case DMALL_LALAMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_SUNFLOWMON_ANIM_INDEX ,DMALL_BAKEMON_ANIM_INDEX ,DMALL_BIRDRAMON_ANIM_INDEX ,DMALL_GAOGAMON_ANIM_INDEX ,DMALL_GEO_GREYMON_ANIM_INDEX ,DMALL_GOLD_NUMEMON_ANIM_INDEX ,DMALL_IGAMON_ANIM_INDEX ,DMALL_KOUGAMON_ANIM_INDEX ,DMALL_LEOMON_ANIM_INDEX ,DMALL_NUMEMON_ANIM_INDEX ,DMALL_REPPAMON_ANIM_INDEX ,DMALL_RED_VEGIMON_ANIM_INDEX ,DMALL_SEADRAMON_ANIM_INDEX ,DMALL_SOULMON_ANIM_INDEX ,DMALL_SUNFLOWMON_ANIM_INDEX
                },
              };
            case DMALL_LAVOGARITAMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 2,
                .animation_indices = {
                  DMALL_VOLCANICDRAMON_ANIM_INDEX ,DMALL_VOLCANICDRAMON_ANIM_INDEX
                },
              };
            case DMALL_LAVORVOMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 4,
                .animation_indices = {
                  DMALL_LAVOGARITAMON_ANIM_INDEX ,DMALL_DEATH_MERAMON_ANIM_INDEX ,DMALL_FLAREMON_ANIM_INDEX ,DMALL_LAVOGARITAMON_ANIM_INDEX
                },
              };
            case DMALL_LEAFMON_ANIM_INDEX:
              return {
                // Stage: Baby I
                .conditions = { .next_evolution_time_sec = 600 },
                
                .num_animation_indices = 2,
                .animation_indices = {
                  DMALL_MINOMON_ANIM_INDEX ,DMALL_MINOMON_ANIM_INDEX
                },
              };
            case DMALL_LEKISMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_CRESCEMON_ANIM_INDEX ,DMALL_AERO_V_DRAMON_ANIM_INDEX ,DMALL_ANDROMON_ANIM_INDEX ,DMALL_ANOMALOCARIMON_ANIM_INDEX ,DMALL_ASURAMON_ANIM_INDEX ,DMALL_BEOWOLFMON_ANIM_INDEX ,DMALL_BIG_MAMEMON_ANIM_INDEX ,DMALL_CRESCEMON_ANIM_INDEX ,DMALL_CYBERDRAMON_ANIM_INDEX ,DMALL_DAGOMON_ANIM_INDEX ,DMALL_DARK_KNIGHTMON_ANIM_INDEX ,DMALL_DURAMON_ANIM_INDEX ,DMALL_GARUDAMON_ANIM_INDEX ,DMALL_GERBEMON_ANIM_INDEX ,DMALL_HANGYOMON_ANIM_INDEX
                },
              };
            case DMALL_LEOMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_PANJYAMON_ANIM_INDEX ,DMALL_MEGADRAMON_ANIM_INDEX ,DMALL_AERO_V_DRAMON_ANIM_INDEX ,DMALL_ANDROMON_ANIM_INDEX ,DMALL_ANGEWOMON_ANIM_INDEX ,DMALL_ASTAMON_ANIM_INDEX ,DMALL_ASURAMON_ANIM_INDEX ,DMALL_BAALMON_ANIM_INDEX ,DMALL_BIG_MAMEMON_ANIM_INDEX ,DMALL_CHIMAIRAMON_ANIM_INDEX ,DMALL_CYBERDRAMON_ANIM_INDEX ,DMALL_ETEMON_ANIM_INDEX ,DMALL_DORUGUREMON_ANIM_INDEX ,DMALL_DURAMON_ANIM_INDEX ,DMALL_FLAREMON_ANIM_INDEX
                },
              };
            case DMALL_LEOMON_X_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 14,
                .animation_indices = {
                  DMALL_CERBERUMON_X_ANIM_INDEX ,DMALL_METAL_TYRANOMON_X_ANIM_INDEX ,DMALL_YATAGARAMON_ANIM_INDEX ,DMALL_DELUMON_ANIM_INDEX ,DMALL_DORUGUREMON_ANIM_INDEX ,DMALL_GRADEMON_ANIM_INDEX ,DMALL_HANGYOMON_ANIM_INDEX ,DMALL_KAISER_LEOMON_ANIM_INDEX ,DMALL_MACH_GAOGAMON_ANIM_INDEX ,DMALL_MAMMON_ANIM_INDEX ,DMALL_MEGADRAMON_ANIM_INDEX ,DMALL_PANJYAMON_ANIM_INDEX ,DMALL_PICCOLOMON_ANIM_INDEX ,DMALL_WERE_GARURUMON_ANIM_INDEX
                },
              };
            case DMALL_LEVIAMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMALL_LEVIAMON_X_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMALL_LILAMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_LOTUSMON_ANIM_INDEX ,DMALL_ROSEMON_ANIM_INDEX ,DMALL_BANCHO_LEOMON_ANIM_INDEX ,DMALL_BANCHO_LILIMON_ANIM_INDEX ,DMALL_DEMON_ANIM_INDEX ,DMALL_HERAKLE_KABUTERIMON_ANIM_INDEX ,DMALL_HOLYDRAMON_ANIM_INDEX ,DMALL_LILITHMON_ANIM_INDEX ,DMALL_LOTUSMON_ANIM_INDEX ,DMALL_MARIN_ANGEMON_ANIM_INDEX ,DMALL_OURYUMON_ANIM_INDEX ,DMALL_PINOCHIMON_ANIM_INDEX ,DMALL_PLATINUM_NUMEMON_ANIM_INDEX ,DMALL_ROSEMON_ANIM_INDEX ,DMALL_SERAPHIMON_ANIM_INDEX
                },
              };
            case DMALL_LILIMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_BANCHO_LILIMON_ANIM_INDEX ,DMALL_ROSEMON_ANIM_INDEX ,DMALL_BANCHO_LILIMON_ANIM_INDEX ,DMALL_BELIAL_VAMDEMON_ANIM_INDEX ,DMALL_BLOOM_LORDMON_ANIM_INDEX ,DMALL_BOLTMON_ANIM_INDEX ,DMALL_GRIFFOMON_ANIM_INDEX ,DMALL_HOLYDRAMON_ANIM_INDEX ,DMALL_LILITHMON_ANIM_INDEX ,DMALL_LOTUSMON_ANIM_INDEX ,DMALL_MARIN_ANGEMON_ANIM_INDEX ,DMALL_METAL_GARURUMON_ANIM_INDEX ,DMALL_METAL_SEADRAMON_ANIM_INDEX ,DMALL_PINOCHIMON_ANIM_INDEX ,DMALL_PLESIOMON_ANIM_INDEX
                },
              };
            case DMALL_LILIMON_X_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 12,
                .animation_indices = {
                  DMALL_RAFFLESIMON_ANIM_INDEX ,DMALL_BEEL_STARMON_X_ANIM_INDEX ,DMALL_VALDURMON_ANIM_INDEX ,DMALL_PLATINUM_NUMEMON_ANIM_INDEX ,DMALL_BANCHO_LILIMON_ANIM_INDEX ,DMALL_HOLYDRAMON_ANIM_INDEX ,DMALL_LILITHMON_ANIM_INDEX ,DMALL_MARIN_ANGEMON_ANIM_INDEX ,DMALL_PLATINUM_NUMEMON_ANIM_INDEX ,DMALL_RAFFLESIMON_ANIM_INDEX ,DMALL_ROSEMON_ANIM_INDEX ,DMALL_VALDURMON_ANIM_INDEX
                },
              };
            case DMALL_LILITHMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMALL_LILITHMON_X_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMALL_LOPMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_TURUIEMON_ANIM_INDEX ,DMALL_BITMON_ANIM_INDEX ,DMALL_BLACK_GALGOMON_ANIM_INDEX ,DMALL_BLACK_TAILMON_ANIM_INDEX ,DMALL_CENTALMON_ANIM_INDEX ,DMALL_COELAMON_ANIM_INDEX ,DMALL_DEVIMON_ANIM_INDEX ,DMALL_GALGOMON_ANIM_INDEX ,DMALL_GEREMON_ANIM_INDEX ,DMALL_GRYZMON_ANIM_INDEX ,DMALL_KYUBIMON_SILVER_ANIM_INDEX ,DMALL_LEKISMON_ANIM_INDEX ,DMALL_LEOMON_ANIM_INDEX ,DMALL_LYNXMON_ANIM_INDEX ,DMALL_MEICOOMON_ANIM_INDEX
                },
              };
            case DMALL_LOPMON_X_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 12,
                .animation_indices = {
                  DMALL_PEGASMON_X_ANIM_INDEX ,DMALL_WIZARMON_X_ANIM_INDEX ,DMALL_GINRYUMON_ANIM_INDEX ,DMALL_TAILMON_X_ANIM_INDEX ,DMALL_TYLOMON_X_ANIM_INDEX ,DMALL_OMEKAMON_ANIM_INDEX ,DMALL_PALEDRAMON_ANIM_INDEX ,DMALL_JAZARDMON_ANIM_INDEX ,DMALL_BLACK_GALGOMON_ANIM_INDEX ,DMALL_GALGOMON_ANIM_INDEX ,DMALL_GINRYUMON_ANIM_INDEX ,DMALL_TURUIEMON_ANIM_INDEX
                },
              };
            case DMALL_LORDKNIGHTMON_X_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMALL_LOTUSMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMALL_LUCEMON_FALLDOWN_MODE_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_OGUDOMON_ANIM_INDEX ,DMALL_BEELZEBUMON_X_ANIM_INDEX ,DMALL_WAR_GREYMON_X_ANIM_INDEX ,DMALL_BELIAL_VAMDEMON_ANIM_INDEX ,DMALL_RAFFLESIMON_ANIM_INDEX ,DMALL_PLATINUM_NUMEMON_ANIM_INDEX ,DMALL_BARBAMON_ANIM_INDEX ,DMALL_BELIAL_VAMDEMON_ANIM_INDEX ,DMALL_DEMON_ANIM_INDEX ,DMALL_GRAND_DRACUMON_ANIM_INDEX ,DMALL_OGUDOMON_ANIM_INDEX ,DMALL_PLATINUM_NUMEMON_ANIM_INDEX ,DMALL_RAFFLESIMON_ANIM_INDEX ,DMALL_SERAPHIMON_ANIM_INDEX ,DMALL_VENOM_VAMDEMON_ANIM_INDEX
                },
              };
            case DMALL_LUCEMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 11,
                .animation_indices = {
                  DMALL_ANGEMON_ANIM_INDEX ,DMALL_DEVIMON_ANIM_INDEX ,DMALL_GEREMON_ANIM_INDEX ,DMALL_HANUMON_ANIM_INDEX ,DMALL_ICE_DEVIMON_ANIM_INDEX ,DMALL_NUMEMON_ANIM_INDEX ,DMALL_PIDMON_ANIM_INDEX ,DMALL_SCUMON_ANIM_INDEX ,DMALL_TORTAMON_ANIM_INDEX ,DMALL_V_DRAMON_ANIM_INDEX ,DMALL_WIZARMON_ANIM_INDEX
                },
              };
            case DMALL_LUCEMON_SATAN_MODE_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMALL_LUCEMON_X_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMALL_LUDOMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 3,
                .animation_indices = {
                  DMALL_TIA_LUDOMON_ANIM_INDEX ,DMALL_REPPAMON_ANIM_INDEX ,DMALL_TIA_LUDOMON_ANIM_INDEX
                },
              };
            case DMALL_LUNAMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 10,
                .animation_indices = {
                  DMALL_LEKISMON_ANIM_INDEX ,DMALL_GAOGAMON_ANIM_INDEX ,DMALL_GARURUMON_ANIM_INDEX ,DMALL_HYOUGAMON_ANIM_INDEX ,DMALL_ICEMON_ANIM_INDEX ,DMALL_LEKISMON_ANIM_INDEX ,DMALL_MAD_LEOMON_ANIM_INDEX ,DMALL_SANGLOUPMON_ANIM_INDEX ,DMALL_TAILMON_ANIM_INDEX ,DMALL_YUKIDARUMON_ANIM_INDEX
                },
              };
            case DMALL_LYNXMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 8,
                .animation_indices = {
                  DMALL_BLACK_RAPIDMON_ANIM_INDEX ,DMALL_BLUE_MERAMON_ANIM_INDEX ,DMALL_CATURAMON_ANIM_INDEX ,DMALL_DORUGUREMON_ANIM_INDEX ,DMALL_FLAREMON_ANIM_INDEX ,DMALL_KNIGHTMON_ANIM_INDEX ,DMALL_MONZAEMON_ANIM_INDEX ,DMALL_WERE_GARURUMON_ANIM_INDEX
                },
              };
            case DMALL_MACH_GAOGAMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 12,
                .animation_indices = {
                  DMALL_BANCHO_LEOMON_ANIM_INDEX ,DMALL_CHAOSDRAMON_ANIM_INDEX ,DMALL_DEMON_ANIM_INDEX ,DMALL_DIANAMON_ANIM_INDEX ,DMALL_GANKOOMON_ANIM_INDEX ,DMALL_HOLYDRAMON_ANIM_INDEX ,DMALL_METAL_GARURUMON_ANIM_INDEX ,DMALL_ROSEMON_ANIM_INDEX ,DMALL_SABER_LEOMON_ANIM_INDEX ,DMALL_SAINT_GALGOMON_ANIM_INDEX ,DMALL_SAKUYAMON_ANIM_INDEX ,DMALL_SERAPHIMON_ANIM_INDEX
                },
              };
            case DMALL_MAD_LEOMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 11,
                .animation_indices = {
                  DMALL_ANOMALOCARIMON_ANIM_INDEX ,DMALL_ASTAMON_ANIM_INDEX ,DMALL_BAALMON_ANIM_INDEX ,DMALL_BIG_MAMEMON_ANIM_INDEX ,DMALL_DURAMON_ANIM_INDEX ,DMALL_HANGYOMON_ANIM_INDEX ,DMALL_KAISER_LEOMON_ANIM_INDEX ,DMALL_PICCOLOMON_ANIM_INDEX ,DMALL_PUMPMON_ANIM_INDEX ,DMALL_RAIHIMON_ANIM_INDEX ,DMALL_RIZE_GREYMON_ANIM_INDEX
                },
              };
            case DMALL_MAGNAMON_X_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 3,
                .animation_indices = {
                  DMALL_GARUDAMON_ANIM_INDEX ,DMALL_KNIGHTMON_ANIM_INDEX ,DMALL_PAILDRAMON_ANIM_INDEX
                },
              };
            case DMALL_MAMBOMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 3,
                .animation_indices = {
                  DMALL_GIROMON_ANIM_INDEX ,DMALL_HANGYOMON_ANIM_INDEX ,DMALL_RIZE_GREYMON_ANIM_INDEX
                },
              };
            case DMALL_MAMEMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_PRINCE_MAMEMON_ANIM_INDEX ,DMALL_BANCHO_MAMEMON_ANIM_INDEX ,DMALL_BLITZ_GREYMON_ANIM_INDEX ,DMALL_BOLTMON_ANIM_INDEX ,DMALL_GRIFFOMON_ANIM_INDEX ,DMALL_METAL_GARURUMON_ANIM_INDEX ,DMALL_METAL_SEADRAMON_ANIM_INDEX ,DMALL_MUGENDRAMON_ANIM_INDEX ,DMALL_PINOCHIMON_ANIM_INDEX ,DMALL_PLATINUM_NUMEMON_ANIM_INDEX ,DMALL_PLESIOMON_ANIM_INDEX ,DMALL_PRINCE_MAMEMON_ANIM_INDEX ,DMALL_ROSEMON_ANIM_INDEX ,DMALL_SABER_LEOMON_ANIM_INDEX ,DMALL_VALDURMON_ANIM_INDEX
                },
              };
            case DMALL_MAMEMON_X_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_RAPIDMON_X_ANIM_INDEX ,DMALL_JUSTIMON_X_ANIM_INDEX ,DMALL_ALPHAMON_ANIM_INDEX ,DMALL_HOUOUMON_X_ANIM_INDEX ,DMALL_TIGER_VESPAMON_ANIM_INDEX ,DMALL_GAIOUMON_ANIM_INDEX ,DMALL_DINOTIGERMON_ANIM_INDEX ,DMALL_HOLYDRAMON_X_ANIM_INDEX ,DMALL_EBEMON_X_ANIM_INDEX ,DMALL_HEXEBLAUMON_ANIM_INDEX ,DMALL_METALLICDRAMON_ANIM_INDEX ,DMALL_NOBLE_PUMPMON_ANIM_INDEX ,DMALL_BANCHO_MAMEMON_ANIM_INDEX ,DMALL_DINOTIGERMON_ANIM_INDEX ,DMALL_HEXEBLAUMON_ANIM_INDEX
                },
              };
            case DMALL_MAMETYRAMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_DINOREXMON_ANIM_INDEX ,DMALL_PRINCE_MAMEMON_X_ANIM_INDEX ,DMALL_BLACK_WAR_GREYMON_X_ANIM_INDEX ,DMALL_METAL_PIRANIMON_ANIM_INDEX ,DMALL_BAGRAMON_ANIM_INDEX ,DMALL_RAIHIMON_ANIM_INDEX ,DMALL_CHAOSDRAMON_X_ANIM_INDEX ,DMALL_RASENMON_FURY_MODE_ANIM_INDEX ,DMALL_ROSEMON_X_ANIM_INDEX ,DMALL_BAGRAMON_ANIM_INDEX ,DMALL_BLACK_WAR_GREYMON_ANIM_INDEX ,DMALL_DARKDRAMON_ANIM_INDEX ,DMALL_DINOREXMON_ANIM_INDEX ,DMALL_DINOTIGERMON_ANIM_INDEX ,DMALL_GAIOUMON_ANIM_INDEX
                },
              };
            case DMALL_MAMMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 12,
                .animation_indices = {
                  DMALL_SKULL_MAMMON_ANIM_INDEX ,DMALL_ANCIENT_MEGATHERIUMON_ANIM_INDEX ,DMALL_BEELZEBUMON_ANIM_INDEX ,DMALL_BOLTMON_ANIM_INDEX ,DMALL_CRANIUMMON_ANIM_INDEX ,DMALL_DUFTMON_ANIM_INDEX ,DMALL_HEXEBLAUMON_ANIM_INDEX ,DMALL_METAL_GARURUMON_ANIM_INDEX ,DMALL_METAL_GARURUMON_BLACK_ANIM_INDEX ,DMALL_SABER_LEOMON_ANIM_INDEX ,DMALL_SERAPHIMON_ANIM_INDEX ,DMALL_SKULL_MAMMON_ANIM_INDEX
                },
              };
            case DMALL_MAMMON_X_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 7,
                .animation_indices = {
                  DMALL_GRANDIS_KUWAGAMON_ANIM_INDEX ,DMALL_SKULL_MAMMON_X_ANIM_INDEX ,DMALL_BEEL_STARMON_X_ANIM_INDEX ,DMALL_ROSEMON_X_ANIM_INDEX ,DMALL_METAL_GARURUMON_BLACK_ANIM_INDEX ,DMALL_SERAPHIMON_ANIM_INDEX ,DMALL_SKULL_MAMMON_ANIM_INDEX
                },
              };
            case DMALL_MANTARAYMON_X_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 7,
                .animation_indices = {
                  DMALL_MAMETYRAMON_ANIM_INDEX ,DMALL_OKUWAMON_X_ANIM_INDEX ,DMALL_DAGOMON_ANIM_INDEX ,DMALL_HANGYOMON_ANIM_INDEX ,DMALL_MAMETYRAMON_ANIM_INDEX ,DMALL_MARIN_DEVIMON_ANIM_INDEX ,DMALL_SKULL_BALUCHIMON_ANIM_INDEX
                },
              };
            case DMALL_MANTICOREMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 3,
                .animation_indices = {
                  DMALL_BRYWELUDRAMON_ANIM_INDEX ,DMALL_DEATHMON_BLACK_ANIM_INDEX ,DMALL_DUKEMON_ANIM_INDEX
                },
              };
            case DMALL_MARIN_ANGEMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMALL_MARIN_CHIMAIRAMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 7,
                .animation_indices = {
                  DMALL_ANCIENT_MEGATHERIUMON_ANIM_INDEX ,DMALL_GIGA_SEADRAMON_ANIM_INDEX ,DMALL_MARIN_ANGEMON_ANIM_INDEX ,DMALL_METAL_SEADRAMON_ANIM_INDEX ,DMALL_PLATINUM_NUMEMON_ANIM_INDEX ,DMALL_PLESIOMON_ANIM_INDEX ,DMALL_REGALECUSMON_ANIM_INDEX
                },
              };
            case DMALL_MARIN_DEVIMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_ANCIENT_MERMAIMON_ANIM_INDEX ,DMALL_ANCIENT_MEGATHERIUMON_ANIM_INDEX ,DMALL_CTHYLLAMON_ANIM_INDEX ,DMALL_DARKDRAMON_ANIM_INDEX ,DMALL_DEMON_ANIM_INDEX ,DMALL_DIABLOMON_ANIM_INDEX ,DMALL_LEVIAMON_ANIM_INDEX ,DMALL_LILITHMON_ANIM_INDEX ,DMALL_MARIN_ANGEMON_ANIM_INDEX ,DMALL_METAL_ETEMON_ANIM_INDEX ,DMALL_METAL_SEADRAMON_ANIM_INDEX ,DMALL_MUGENDRAMON_ANIM_INDEX ,DMALL_PIEMON_ANIM_INDEX ,DMALL_PINOCHIMON_ANIM_INDEX ,DMALL_PLESIOMON_ANIM_INDEX
                },
              };
            case DMALL_MASTEMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMALL_MECHANORIMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_AERO_V_DRAMON_ANIM_INDEX ,DMALL_ANDROMON_ANIM_INDEX ,DMALL_ANOMALOCARIMON_ANIM_INDEX ,DMALL_ASTAMON_ANIM_INDEX ,DMALL_ASURAMON_ANIM_INDEX ,DMALL_BEOWOLFMON_ANIM_INDEX ,DMALL_BIG_MAMEMON_ANIM_INDEX ,DMALL_DAGOMON_ANIM_INDEX ,DMALL_DARK_KNIGHTMON_ANIM_INDEX ,DMALL_ETEMON_ANIM_INDEX ,DMALL_GERBEMON_ANIM_INDEX ,DMALL_GIGADRAMON_ANIM_INDEX ,DMALL_GIROMON_ANIM_INDEX ,DMALL_HANGYOMON_ANIM_INDEX ,DMALL_MAMEMON_ANIM_INDEX
                },
              };
            case DMALL_MEGADRAMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_DEATHMON_ANIM_INDEX ,DMALL_MUGENDRAMON_ANIM_INDEX ,DMALL_DARKDRAMON_ANIM_INDEX ,DMALL_AEGISDRAMON_ANIM_INDEX ,DMALL_BLACK_WAR_GREYMON_ANIM_INDEX ,DMALL_CHAOSDRAMON_ANIM_INDEX ,DMALL_DARKDRAMON_ANIM_INDEX ,DMALL_DEATHMON_ANIM_INDEX ,DMALL_DEMON_ANIM_INDEX ,DMALL_DINOREXMON_ANIM_INDEX ,DMALL_DUKEMON_ANIM_INDEX ,DMALL_GAIOUMON_ANIM_INDEX ,DMALL_HERAKLE_KABUTERIMON_ANIM_INDEX ,DMALL_MEGIDRAMON_ANIM_INDEX ,DMALL_METAL_ETEMON_ANIM_INDEX
                },
              };
            case DMALL_MEGALO_GROWMON_ORANGE_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 12,
                .animation_indices = {
                  DMALL_BLACK_WAR_GREYMON_ANIM_INDEX ,DMALL_CHAOS_DUKEMON_ANIM_INDEX ,DMALL_CHAOSDRAMON_ANIM_INDEX ,DMALL_DARKDRAMON_ANIM_INDEX ,DMALL_DEMON_ANIM_INDEX ,DMALL_DINOREXMON_ANIM_INDEX ,DMALL_DUKEMON_ANIM_INDEX ,DMALL_HI_ANDROMON_ANIM_INDEX ,DMALL_MEGIDRAMON_ANIM_INDEX ,DMALL_METAL_PIRANIMON_ANIM_INDEX ,DMALL_MUGENDRAMON_ANIM_INDEX ,DMALL_WAR_GREYMON_ANIM_INDEX
                },
              };
            case DMALL_MEGALO_GROWMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_DUKEMON_ANIM_INDEX ,DMALL_MEGIDRAMON_ANIM_INDEX ,DMALL_BARBAMON_ANIM_INDEX ,DMALL_BLACK_WAR_GREYMON_ANIM_INDEX ,DMALL_CHAOS_DUKEMON_ANIM_INDEX ,DMALL_CHAOSDRAMON_ANIM_INDEX ,DMALL_DARKDRAMON_ANIM_INDEX ,DMALL_DEMON_ANIM_INDEX ,DMALL_DINOREXMON_ANIM_INDEX ,DMALL_DUKEMON_ANIM_INDEX ,DMALL_HI_ANDROMON_ANIM_INDEX ,DMALL_KAISER_GREYMON_ANIM_INDEX ,DMALL_LEVIAMON_ANIM_INDEX ,DMALL_MEGIDRAMON_ANIM_INDEX ,DMALL_METAL_GARURUMON_ANIM_INDEX
                },
              };
            case DMALL_MEGALO_GROWMON_X_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_MEGIDRAMON_X_ANIM_INDEX ,DMALL_CRANIUMMON_X_ANIM_INDEX ,DMALL_JESMON_X_ANIM_INDEX ,DMALL_BELIAL_VAMDEMON_ANIM_INDEX ,DMALL_PLATINUM_NUMEMON_ANIM_INDEX ,DMALL_BELIAL_VAMDEMON_ANIM_INDEX ,DMALL_BLACK_WAR_GREYMON_ANIM_INDEX ,DMALL_CHAOS_DUKEMON_ANIM_INDEX ,DMALL_CHAOSDRAMON_ANIM_INDEX ,DMALL_DINOREXMON_ANIM_INDEX ,DMALL_DINOTIGERMON_ANIM_INDEX ,DMALL_DUKEMON_ANIM_INDEX ,DMALL_HI_ANDROMON_ANIM_INDEX ,DMALL_MEGIDRAMON_ANIM_INDEX ,DMALL_METAL_PIRANIMON_ANIM_INDEX
                },
              };
            case DMALL_MEGA_SEADRAMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_AEGISDRAMON_ANIM_INDEX ,DMALL_APOCALYMON_ANIM_INDEX ,DMALL_BLACK_WAR_GREYMON_ANIM_INDEX ,DMALL_BOLTMON_ANIM_INDEX ,DMALL_DEMON_ANIM_INDEX ,DMALL_DORUGORAMON_ANIM_INDEX ,DMALL_GIGA_SEADRAMON_ANIM_INDEX ,DMALL_GRIFFOMON_ANIM_INDEX ,DMALL_HOLYDRAMON_ANIM_INDEX ,DMALL_LEVIAMON_ANIM_INDEX ,DMALL_MARIN_ANGEMON_ANIM_INDEX ,DMALL_METAL_GARURUMON_ANIM_INDEX ,DMALL_METAL_PIRANIMON_ANIM_INDEX ,DMALL_METAL_SEADRAMON_ANIM_INDEX ,DMALL_MUGENDRAMON_ANIM_INDEX
                },
              };
            case DMALL_MEGA_SEADRAMON_X_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 14,
                .animation_indices = {
                  DMALL_GIGA_SEADRAMON_ANIM_INDEX ,DMALL_CHAOSDRAMON_X_ANIM_INDEX ,DMALL_SKULL_MAMMON_X_ANIM_INDEX ,DMALL_BLACK_WAR_GREYMON_ANIM_INDEX ,DMALL_DORUGORAMON_ANIM_INDEX ,DMALL_GIGA_SEADRAMON_ANIM_INDEX ,DMALL_GRANDIS_KUWAGAMON_ANIM_INDEX ,DMALL_HOLYDRAMON_ANIM_INDEX ,DMALL_LEVIAMON_ANIM_INDEX ,DMALL_MARIN_ANGEMON_ANIM_INDEX ,DMALL_METAL_PIRANIMON_ANIM_INDEX ,DMALL_METAL_SEADRAMON_ANIM_INDEX ,DMALL_PLESIOMON_ANIM_INDEX ,DMALL_SERAPHIMON_ANIM_INDEX
                },
              };
            case DMALL_MEGIDRAMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMALL_MEGIDRAMON_X_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = 230400 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DMALL_DUKEMON_X_ANIM_INDEX
                },
              };
            case DMALL_MEICOOMON_BABY_ANIM_INDEX:
              return {
                // Stage: Baby II
                .conditions = { .next_evolution_time_sec = 43200 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMALL_MEICOOMON_CHILD_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 2,
                .animation_indices = {
                  DMALL_MEICOOMON_ANIM_INDEX ,DMALL_MEICOOMON_ANIM_INDEX
                },
              };
            case DMALL_MEICOOMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 12,
                .animation_indices = {
                  DMALL_MEICRACKMON_ANIM_INDEX ,DMALL_ANGEWOMON_ANIM_INDEX ,DMALL_ANOMALOCARIMON_ANIM_INDEX ,DMALL_BAALMON_ANIM_INDEX ,DMALL_BIG_MAMEMON_ANIM_INDEX ,DMALL_DELUMON_ANIM_INDEX ,DMALL_DURAMON_ANIM_INDEX ,DMALL_HANGYOMON_ANIM_INDEX ,DMALL_MEICRACKMON_ANIM_INDEX ,DMALL_PICCOLOMON_ANIM_INDEX ,DMALL_PUMPMON_ANIM_INDEX ,DMALL_RIZE_GREYMON_ANIM_INDEX
                },
              };
            case DMALL_MEICRACKMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 6,
                .animation_indices = {
                  DMALL_RASIELMON_ANIM_INDEX ,DMALL_HOLYDRAMON_ANIM_INDEX ,DMALL_MUGENDRAMON_ANIM_INDEX ,DMALL_PLESIOMON_ANIM_INDEX ,DMALL_RASIELMON_ANIM_INDEX ,DMALL_WAR_GREYMON_ANIM_INDEX
                },
              };
            case DMALL_MEICRACKMON_VICIOUS_MODE_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 4,
                .animation_indices = {
                  DMALL_RAGUELMON_ANIM_INDEX ,DMALL_MASTEMON_ANIM_INDEX ,DMALL_RAGUELMON_ANIM_INDEX ,DMALL_ROSEMON_ANIM_INDEX
                },
              };
            case DMALL_MEPHISMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 6,
                .animation_indices = {
                  DMALL_BARBAMON_ANIM_INDEX ,DMALL_DEMON_ANIM_INDEX ,DMALL_GRAND_DRACUMON_ANIM_INDEX ,DMALL_METAL_SEADRAMON_ANIM_INDEX ,DMALL_PIEMON_ANIM_INDEX ,DMALL_SAKUYAMON_ANIM_INDEX
                },
              };
            case DMALL_MEPHISMON_X_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 5,
                .animation_indices = {
                  DMALL_CHERUBIMON_VICE_X_ANIM_INDEX ,DMALL_DINOREXMON_ANIM_INDEX ,DMALL_ROSEMON_X_ANIM_INDEX ,DMALL_BEEL_STARMON_X_ANIM_INDEX ,DMALL_DINOREXMON_ANIM_INDEX
                },
              };
            case DMALL_MERAMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_BLUE_MERAMON_ANIM_INDEX ,DMALL_DEATH_MERAMON_ANIM_INDEX ,DMALL_MAMEMON_ANIM_INDEX ,DMALL_AERO_V_DRAMON_ANIM_INDEX ,DMALL_ANDROMON_ANIM_INDEX ,DMALL_ANOMALOCARIMON_ANIM_INDEX ,DMALL_ASURAMON_ANIM_INDEX ,DMALL_BEOWOLFMON_ANIM_INDEX ,DMALL_BIG_MAMEMON_ANIM_INDEX ,DMALL_BLACK_MEGALO_GROWMON_ANIM_INDEX ,DMALL_CYBERDRAMON_ANIM_INDEX ,DMALL_BLUE_MERAMON_ANIM_INDEX ,DMALL_DAGOMON_ANIM_INDEX ,DMALL_DARK_KNIGHTMON_ANIM_INDEX ,DMALL_DARK_SUPERSTARMON_ANIM_INDEX
                },
              };
            case DMALL_MERAMON_X_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 11,
                .animation_indices = {
                  DMALL_OMEGA_SHOUTMON_X_ANIM_INDEX ,DMALL_CYBERDRAMON_X_ANIM_INDEX ,DMALL_DORUGUREMON_ANIM_INDEX ,DMALL_GARUDAMON_X_ANIM_INDEX ,DMALL_CANNONBEEMON_ANIM_INDEX ,DMALL_GRADEMON_ANIM_INDEX ,DMALL_MAMEMON_X_ANIM_INDEX ,DMALL_CRYS_PALEDRAMON_ANIM_INDEX ,DMALL_JAZARICHMON_ANIM_INDEX ,DMALL_PUMPMON_ANIM_INDEX ,DMALL_GRADEMON_ANIM_INDEX
                },
              };
            case DMALL_MERMAIMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 9,
                .animation_indices = {
                  DMALL_AEGISDRAMON_ANIM_INDEX ,DMALL_ANCIENT_MEGATHERIUMON_ANIM_INDEX ,DMALL_ANCIENT_MERMAIMON_ANIM_INDEX ,DMALL_DIANAMON_ANIM_INDEX ,DMALL_LEVIAMON_ANIM_INDEX ,DMALL_MARIN_ANGEMON_ANIM_INDEX ,DMALL_METAL_SEADRAMON_ANIM_INDEX ,DMALL_PLESIOMON_ANIM_INDEX ,DMALL_REGALECUSMON_ANIM_INDEX
                },
              };
            case DMALL_METAL_ETEMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMALL_METAL_GARURUMON_BLACK_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMALL_METAL_GARURUMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMALL_METAL_GARURUMON_X_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = 230400 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DMALL_OMEGAMON_X_ANIM_INDEX
                },
              };
            case DMALL_METAL_GREYMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_BLACK_WAR_GREYMON_ANIM_INDEX ,DMALL_BLITZ_GREYMON_ANIM_INDEX ,DMALL_WAR_GREYMON_ANIM_INDEX ,DMALL_ALPHAMON_ANIM_INDEX ,DMALL_BLACK_WAR_GREYMON_ANIM_INDEX ,DMALL_BLITZ_GREYMON_ANIM_INDEX ,DMALL_CHAOSDRAMON_ANIM_INDEX ,DMALL_DARKDRAMON_ANIM_INDEX ,DMALL_DINOREXMON_ANIM_INDEX ,DMALL_DUKEMON_ANIM_INDEX ,DMALL_GAIOUMON_ANIM_INDEX ,DMALL_HOLYDRAMON_ANIM_INDEX ,DMALL_KAISER_GREYMON_ANIM_INDEX ,DMALL_MEGIDRAMON_ANIM_INDEX ,DMALL_METAL_GARURUMON_ANIM_INDEX
                },
              };
            case DMALL_METAL_GREYMON_VIRUS_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_BLACK_WAR_GREYMON_ANIM_INDEX ,DMALL_BLITZ_GREYMON_ANIM_INDEX ,DMALL_BLITZ_GREYMON_ANIM_INDEX ,DMALL_ALPHAMON_ANIM_INDEX ,DMALL_BLACK_WAR_GREYMON_ANIM_INDEX ,DMALL_BLITZ_GREYMON_ANIM_INDEX ,DMALL_BOLTMON_ANIM_INDEX ,DMALL_CHAOSDRAMON_ANIM_INDEX ,DMALL_CHERUBIMON_VICE_ANIM_INDEX ,DMALL_DEMON_ANIM_INDEX ,DMALL_DIABLOMON_ANIM_INDEX ,DMALL_DUKEMON_ANIM_INDEX ,DMALL_GAIOUMON_ANIM_INDEX ,DMALL_METAL_ETEMON_ANIM_INDEX ,DMALL_METAL_GARURUMON_ANIM_INDEX
                },
              };
            case DMALL_METAL_GREYMON_VIRUS_X_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 8,
                .animation_indices = {
                  DMALL_BLACK_WAR_GREYMON_X_ANIM_INDEX ,DMALL_SKULL_MAMMON_X_ANIM_INDEX ,DMALL_PRINCE_MAMEMON_X_ANIM_INDEX ,DMALL_METAL_PIRANIMON_ANIM_INDEX ,DMALL_CHAOSDRAMON_X_ANIM_INDEX ,DMALL_CHAOSDRAMON_ANIM_INDEX ,DMALL_METAL_PIRANIMON_ANIM_INDEX ,DMALL_WAR_GREYMON_ANIM_INDEX
                },
              };
            case DMALL_METALGREYMON_X_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 13,
                .animation_indices = {
                  DMALL_BANCHO_LEOMON_ANIM_INDEX ,DMALL_BLACK_WAR_GREYMON_ANIM_INDEX ,DMALL_CHAOSDRAMON_ANIM_INDEX ,DMALL_DUKEMON_ANIM_INDEX ,DMALL_GAIOUMON_ANIM_INDEX ,DMALL_GIGA_SEADRAMON_ANIM_INDEX ,DMALL_GRANDIS_KUWAGAMON_ANIM_INDEX ,DMALL_METAL_ETEMON_ANIM_INDEX ,DMALL_METAL_GARURUMON_ANIM_INDEX ,DMALL_MUGENDRAMON_ANIM_INDEX ,DMALL_PLATINUM_NUMEMON_ANIM_INDEX ,DMALL_VALDURMON_ANIM_INDEX ,DMALL_WAR_GREYMON_ANIM_INDEX
                },
              };
            case DMALL_METALLICDRAMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = 230400 },
                
                .num_animation_indices = 7,
                .animation_indices = {
                  DMALL_MAGNAMON_X_ANIM_INDEX ,DMALL_GANKOOMON_X_ANIM_INDEX ,DMALL_DYNASMON_X_ANIM_INDEX ,DMALL_CRANIUMMON_X_ANIM_INDEX ,DMALL_DUKEMON_X_ANIM_INDEX ,DMALL_ALPHAMON_OURYUKEN_ANIM_INDEX ,DMALL_JESMON_GX_ANIM_INDEX
                },
              };
            case DMALL_METAL_MAMEMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_MUGENDRAMON_ANIM_INDEX ,DMALL_CRES_GARURUMON_ANIM_INDEX ,DMALL_BOLTMON_ANIM_INDEX ,DMALL_CHAOSDRAMON_ANIM_INDEX ,DMALL_CRES_GARURUMON_ANIM_INDEX ,DMALL_GRAND_LOCOMON_ANIM_INDEX ,DMALL_GRIFFOMON_ANIM_INDEX ,DMALL_HI_ANDROMON_ANIM_INDEX ,DMALL_HOLYDRAMON_ANIM_INDEX ,DMALL_METAL_GARURUMON_ANIM_INDEX ,DMALL_METAL_SEADRAMON_ANIM_INDEX ,DMALL_MUGENDRAMON_ANIM_INDEX ,DMALL_PLESIOMON_ANIM_INDEX ,DMALL_PRINCE_MAMEMON_ANIM_INDEX ,DMALL_SABER_LEOMON_ANIM_INDEX
                },
              };
            case DMALL_METAL_MAMEMON_X_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 2,
                .animation_indices = {
                  DMALL_METAL_GARURUMON_ANIM_INDEX ,DMALL_PRINCE_MAMEMON_ANIM_INDEX
                },
              };
            case DMALL_METAL_PHANTOMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 8,
                .animation_indices = {
                  DMALL_GOKUMON_ANIM_INDEX ,DMALL_ALPHAMON_ANIM_INDEX ,DMALL_DEMON_ANIM_INDEX ,DMALL_DINOREXMON_ANIM_INDEX ,DMALL_GOKUMON_ANIM_INDEX ,DMALL_METAL_PIRANIMON_ANIM_INDEX ,DMALL_OURYUMON_ANIM_INDEX ,DMALL_TIGER_VESPAMON_ANIM_INDEX
                },
              };
            case DMALL_METAL_PIRANIMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = 230400 },
                
                .num_animation_indices = 3,
                .animation_indices = {
                  DMALL_LILITHMON_X_ANIM_INDEX ,DMALL_BELPHEMON_X_ANIM_INDEX ,DMALL_BARBAMON_X_ANIM_INDEX
                },
              };
            case DMALL_METAL_SEADRAMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMALL_METAL_TYRANOMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_MUGENDRAMON_ANIM_INDEX ,DMALL_MUGENDRAMON_ANIM_INDEX ,DMALL_ARMAGEMON_ANIM_INDEX ,DMALL_BLACK_SAINT_GALGOMON_ANIM_INDEX ,DMALL_BLACK_WAR_GREYMON_ANIM_INDEX ,DMALL_BLITZ_GREYMON_ANIM_INDEX ,DMALL_CHAOSDRAMON_ANIM_INDEX ,DMALL_DARKDRAMON_ANIM_INDEX ,DMALL_DEMON_ANIM_INDEX ,DMALL_DUKEMON_ANIM_INDEX ,DMALL_GRAND_LOCOMON_ANIM_INDEX ,DMALL_GUNDRAMON_ANIM_INDEX ,DMALL_MEGIDRAMON_ANIM_INDEX ,DMALL_METAL_ETEMON_ANIM_INDEX ,DMALL_METAL_GARURUMON_BLACK_ANIM_INDEX
                },
              };
            case DMALL_METAL_TYRANOMON_X_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_BEELZEBUMON_X_ANIM_INDEX ,DMALL_WAR_GREYMON_X_ANIM_INDEX ,DMALL_SLEIPMON_X_ANIM_INDEX ,DMALL_MEGIDRAMON_X_ANIM_INDEX ,DMALL_METAL_GARURUMON_X_ANIM_INDEX ,DMALL_CRANIUMMON_X_ANIM_INDEX ,DMALL_BELIAL_VAMDEMON_ANIM_INDEX ,DMALL_PLATINUM_NUMEMON_ANIM_INDEX ,DMALL_BELIAL_VAMDEMON_ANIM_INDEX ,DMALL_BLACK_SAINT_GALGOMON_ANIM_INDEX ,DMALL_BLACK_WAR_GREYMON_ANIM_INDEX ,DMALL_CHAOSDRAMON_ANIM_INDEX ,DMALL_MEGIDRAMON_ANIM_INDEX ,DMALL_METAL_GARURUMON_BLACK_ANIM_INDEX ,DMALL_MUGENDRAMON_ANIM_INDEX
                },
              };
            case DMALL_MIKEMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DMALL_ZUDOMON_ANIM_INDEX
                },
              };
            case DMALL_MILLENNIUMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMALL_MIMICMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 2,
                .animation_indices = {
                  DMALL_DURAMON_ANIM_INDEX ,DMALL_MANTICOREMON_ANIM_INDEX
                },
              };
            case DMALL_MINERVAMON_X_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMALL_MINOMON_ANIM_INDEX:
              return {
                // Stage: Baby II
                .conditions = { .next_evolution_time_sec = 43200 },
                
                .num_animation_indices = 5,
                .animation_indices = {
                  DMALL_WORMMON_ANIM_INDEX ,DMALL_KOKUWAMON_ANIM_INDEX ,DMALL_KUNEMON_ANIM_INDEX ,DMALL_TENTOMON_ANIM_INDEX ,DMALL_WORMMON_ANIM_INDEX
                },
              };
            case DMALL_MOCHIMON_ANIM_INDEX:
              return {
                // Stage: Baby II
                .conditions = { .next_evolution_time_sec = 43200 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_HACKMON_ANIM_INDEX ,DMALL_TENTOMON_ANIM_INDEX ,DMALL_CANDMON_ANIM_INDEX ,DMALL_DOKUNEMON_ANIM_INDEX ,DMALL_ELECMON_ANIM_INDEX ,DMALL_FUNBEEMON_ANIM_INDEX ,DMALL_GANIMON_ANIM_INDEX ,DMALL_HACKMON_ANIM_INDEX ,DMALL_HAGURUMON_ANIM_INDEX ,DMALL_IMPMON_ANIM_INDEX ,DMALL_KOKABUTERIMON_ANIM_INDEX ,DMALL_KUNEMON_ANIM_INDEX ,DMALL_LALAMON_ANIM_INDEX ,DMALL_MORPHOMON_ANIM_INDEX ,DMALL_OTAMAMON_ANIM_INDEX
                },
              };
            case DMALL_MOKUMON_ANIM_INDEX:
              return {
                // Stage: Baby I
                .conditions = { .next_evolution_time_sec = 600 },
                
                .num_animation_indices = 3,
                .animation_indices = {
                  DMALL_CAPRIMON_ANIM_INDEX ,DMALL_KOROMON_ANIM_INDEX ,DMALL_SUNMON_ANIM_INDEX
                },
              };
            case DMALL_MONIMON_ANIM_INDEX:
              return {
                // Stage: Baby II
                .conditions = { .next_evolution_time_sec = 43200 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DMALL_HAGURUMON_ANIM_INDEX
                },
              };
            case DMALL_MONOCHROMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_CHIMAIRAMON_ANIM_INDEX ,DMALL_MEGADRAMON_ANIM_INDEX ,DMALL_VERMILLIMON_ANIM_INDEX ,DMALL_MEGADRAMON_ANIM_INDEX ,DMALL_AERO_V_DRAMON_ANIM_INDEX ,DMALL_ANDROMON_ANIM_INDEX ,DMALL_ANGEWOMON_ANIM_INDEX ,DMALL_ASURAMON_ANIM_INDEX ,DMALL_ATLUR_KABUTERIMON_BLUE_ANIM_INDEX ,DMALL_CHIMAIRAMON_ANIM_INDEX ,DMALL_ANOMALOCARIMON_ANIM_INDEX ,DMALL_BEOWOLFMON_ANIM_INDEX ,DMALL_BIG_MAMEMON_ANIM_INDEX ,DMALL_CYBERDRAMON_ANIM_INDEX ,DMALL_DAGOMON_ANIM_INDEX
                },
              };
            case DMALL_MONOCHROMON_X_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 14,
                .animation_indices = {
                  DMALL_AERO_V_DRAMON_ANIM_INDEX ,DMALL_ANDROMON_ANIM_INDEX ,DMALL_ANGEWOMON_ANIM_INDEX ,DMALL_GARUDAMON_ANIM_INDEX ,DMALL_HISYARYUMON_ANIM_INDEX ,DMALL_JYAGAMON_ANIM_INDEX ,DMALL_MAMETYRAMON_ANIM_INDEX ,DMALL_MEGADRAMON_ANIM_INDEX ,DMALL_METAL_TYRANOMON_ANIM_INDEX ,DMALL_PICCOLOMON_ANIM_INDEX ,DMALL_SKULL_BALUCHIMON_ANIM_INDEX ,DMALL_TONOSAMA_GEKOMON_ANIM_INDEX ,DMALL_TRICERAMON_ANIM_INDEX ,DMALL_VERMILLIMON_ANIM_INDEX
                },
              };
            case DMALL_MONZAEMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_LILITHMON_ANIM_INDEX ,DMALL_SHIN_MONZAEMON_ANIM_INDEX ,DMALL_BANCHO_LEOMON_ANIM_INDEX ,DMALL_CHERUBIMON_VIRTUE_ANIM_INDEX ,DMALL_DEATHMON_ANIM_INDEX ,DMALL_HOLYDRAMON_ANIM_INDEX ,DMALL_KING_ETEMON_ANIM_INDEX ,DMALL_LILITHMON_ANIM_INDEX ,DMALL_MARIN_ANGEMON_ANIM_INDEX ,DMALL_METAL_ETEMON_ANIM_INDEX ,DMALL_MUGENDRAMON_ANIM_INDEX ,DMALL_PIEMON_ANIM_INDEX ,DMALL_PINOCHIMON_ANIM_INDEX ,DMALL_PLATINUM_NUMEMON_ANIM_INDEX ,DMALL_PLESIOMON_ANIM_INDEX
                },
              };
            case DMALL_MONZAEMON_X_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 14,
                .animation_indices = {
                  DMALL_CHERUBIMON_VIRTUE_X_ANIM_INDEX ,DMALL_GODDRAMON_X_ANIM_INDEX ,DMALL_OURYUMON_ANIM_INDEX ,DMALL_PLESIOMON_X_ANIM_INDEX ,DMALL_GAIOUMON_ANIM_INDEX ,DMALL_DINOTIGERMON_ANIM_INDEX ,DMALL_HOLYDRAMON_X_ANIM_INDEX ,DMALL_EBEMON_X_ANIM_INDEX ,DMALL_HEXEBLAUMON_ANIM_INDEX ,DMALL_METALLICDRAMON_ANIM_INDEX ,DMALL_NOBLE_PUMPMON_ANIM_INDEX ,DMALL_DINOTIGERMON_ANIM_INDEX ,DMALL_PLATINUM_NUMEMON_ANIM_INDEX ,DMALL_SHIN_MONZAEMON_ANIM_INDEX
                },
              };
            case DMALL_MOONMON_ANIM_INDEX:
              return {
                // Stage: Baby II
                .conditions = { .next_evolution_time_sec = 43200 },
                
                .num_animation_indices = 5,
                .animation_indices = {
                  DMALL_LUNAMON_ANIM_INDEX ,DMALL_AGUMON_BLACK_ANIM_INDEX ,DMALL_GAZIMON_ANIM_INDEX ,DMALL_LOPMON_ANIM_INDEX ,DMALL_LUNAMON_ANIM_INDEX
                },
              };
            case DMALL_MORI_SHELLMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 4,
                .animation_indices = {
                  DMALL_ANOMALOCARIMON_ANIM_INDEX ,DMALL_DIGITAMAMON_ANIM_INDEX ,DMALL_TRICERAMON_ANIM_INDEX ,DMALL_VERMILLIMON_ANIM_INDEX
                },
              };
            case DMALL_MORPHOMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 2,
                .animation_indices = {
                  DMALL_GOKIMON_ANIM_INDEX ,DMALL_WASPMON_ANIM_INDEX
                },
              };
            case DMALL_MUCHOMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 10,
                .animation_indices = {
                  DMALL_AIRDRAMON_ANIM_INDEX ,DMALL_BIRDRAMON_ANIM_INDEX ,DMALL_FUGAMON_ANIM_INDEX ,DMALL_GUARDROMON_ANIM_INDEX ,DMALL_HYOUGAMON_ANIM_INDEX ,DMALL_IKKAKUMON_ANIM_INDEX ,DMALL_SABERDRAMON_ANIM_INDEX ,DMALL_SEADRAMON_ANIM_INDEX ,DMALL_V_DRAMON_ANIM_INDEX ,DMALL_YOUKOMON_ANIM_INDEX
                },
              };
            case DMALL_MUGENDRAMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = 230400 },
                
                .num_animation_indices = 2,
                .animation_indices = {
                  DMALL_MILLENNIUMON_ANIM_INDEX ,DMALL_CHAOSDRAMON_ANIM_INDEX
                },
              };
            case DMALL_MUSHMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_WOODMON_ANIM_INDEX ,DMALL_BIRDRAMON_ANIM_INDEX ,DMALL_BITMON_ANIM_INDEX ,DMALL_DEVIMON_ANIM_INDEX ,DMALL_DOKUGUMON_ANIM_INDEX ,DMALL_GROWMON_ANIM_INDEX ,DMALL_IGAMON_ANIM_INDEX ,DMALL_KOUGAMON_ANIM_INDEX ,DMALL_KUWAGAMON_ANIM_INDEX ,DMALL_MONOCHROMON_ANIM_INDEX ,DMALL_NUMEMON_ANIM_INDEX ,DMALL_RED_VEGIMON_ANIM_INDEX ,DMALL_SCUMON_ANIM_INDEX ,DMALL_SUNFLOWMON_ANIM_INDEX ,DMALL_TAILMON_ANIM_INDEX
                },
              };
            case DMALL_NANOMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_RAIDENMON_ANIM_INDEX ,DMALL_BARBAMON_ANIM_INDEX ,DMALL_DARKDRAMON_ANIM_INDEX ,DMALL_DEATHMON_ANIM_INDEX ,DMALL_DEATHMON_BLACK_ANIM_INDEX ,DMALL_DEMON_ANIM_INDEX ,DMALL_GRAND_LOCOMON_ANIM_INDEX ,DMALL_METAL_ETEMON_ANIM_INDEX ,DMALL_METAL_GARURUMON_BLACK_ANIM_INDEX ,DMALL_MUGENDRAMON_ANIM_INDEX ,DMALL_PIEMON_ANIM_INDEX ,DMALL_PINOCHIMON_ANIM_INDEX ,DMALL_PLATINUM_NUMEMON_ANIM_INDEX ,DMALL_PUKUMON_ANIM_INDEX ,DMALL_RAIDENMON_ANIM_INDEX
                },
              };
            case DMALL_NEFERTIMON_X_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 11,
                .animation_indices = {
                  DMALL_MEPHISMON_X_ANIM_INDEX ,DMALL_MAMETYRAMON_ANIM_INDEX ,DMALL_MEGA_SEADRAMON_X_ANIM_INDEX ,DMALL_ANGEWOMON_ANIM_INDEX ,DMALL_ETEMON_ANIM_INDEX ,DMALL_INSEKIMON_ANIM_INDEX ,DMALL_KNIGHTMON_ANIM_INDEX ,DMALL_LILAMON_ANIM_INDEX ,DMALL_MAMETYRAMON_ANIM_INDEX ,DMALL_MERMAIMON_ANIM_INDEX ,DMALL_SCORPIOMON_ANIM_INDEX
                },
              };
            case DMALL_NEO_DEVIMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 8,
                .animation_indices = {
                  DMALL_BEELZEBUMON_ANIM_INDEX ,DMALL_BLITZ_GREYMON_ANIM_INDEX ,DMALL_DEATHMON_ANIM_INDEX ,DMALL_DEMON_ANIM_INDEX ,DMALL_LILITHMON_ANIM_INDEX ,DMALL_MEGIDRAMON_ANIM_INDEX ,DMALL_SERAPHIMON_ANIM_INDEX ,DMALL_WAR_GREYMON_ANIM_INDEX
                },
              };
            case DMALL_NISE_DRIMOGEMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 5,
                .animation_indices = {
                  DMALL_ATLUR_KABUTERIMON_BLUE_ANIM_INDEX ,DMALL_DIGITAMAMON_ANIM_INDEX ,DMALL_DORUGUREMON_ANIM_INDEX ,DMALL_INSEKIMON_ANIM_INDEX ,DMALL_VERMILLIMON_ANIM_INDEX
                },
              };
            case DMALL_NOBLE_PUMPMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMALL_NUMEMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_MONZAEMON_ANIM_INDEX ,DMALL_MONZAEMON_ANIM_INDEX ,DMALL_AERO_V_DRAMON_ANIM_INDEX ,DMALL_ANOMALOCARIMON_ANIM_INDEX ,DMALL_ASTAMON_ANIM_INDEX ,DMALL_ASURAMON_ANIM_INDEX ,DMALL_BEOWOLFMON_ANIM_INDEX ,DMALL_BIG_MAMEMON_ANIM_INDEX ,DMALL_BLACK_KING_NUMEMON_ANIM_INDEX ,DMALL_DAGOMON_ANIM_INDEX ,DMALL_DARK_KNIGHTMON_ANIM_INDEX ,DMALL_DELUMON_ANIM_INDEX ,DMALL_DIGITAMAMON_ANIM_INDEX ,DMALL_ETEMON_ANIM_INDEX ,DMALL_GERBEMON_ANIM_INDEX
                },
              };
            case DMALL_NUMEMON_X_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 13,
                .animation_indices = {
                  DMALL_METAL_GREYMON_VIRUS_X_ANIM_INDEX ,DMALL_OKUWAMON_X_ANIM_INDEX ,DMALL_TRICERAMON_X_ANIM_INDEX ,DMALL_VAMDEMON_X_ANIM_INDEX ,DMALL_MEGA_SEADRAMON_X_ANIM_INDEX ,DMALL_MEPHISMON_X_ANIM_INDEX ,DMALL_STIFFILMON_ANIM_INDEX ,DMALL_KAISER_LEOMON_ANIM_INDEX ,DMALL_BLACK_KING_NUMEMON_ANIM_INDEX ,DMALL_KAISER_LEOMON_ANIM_INDEX ,DMALL_MONZAEMON_ANIM_INDEX ,DMALL_STIFFILMON_ANIM_INDEX ,DMALL_WARU_MONZAEMON_ANIM_INDEX
                },
              };
            case DMALL_NYAROMON_ANIM_INDEX:
              return {
                // Stage: Baby II
                .conditions = { .next_evolution_time_sec = 43200 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_PLOTMON_ANIM_INDEX ,DMALL_TINKERMON_ANIM_INDEX ,DMALL_AGUMON_ANIM_INDEX ,DMALL_ARMADIMON_ANIM_INDEX ,DMALL_BAKUMON_ANIM_INDEX ,DMALL_BEARMON_ANIM_INDEX ,DMALL_ELECMON_ANIM_INDEX ,DMALL_GAMMAMON_ANIM_INDEX ,DMALL_GAOMON_ANIM_INDEX ,DMALL_GIZAMON_ANIM_INDEX ,DMALL_GUILMON_ANIM_INDEX ,DMALL_HACKMON_ANIM_INDEX ,DMALL_LOPMON_ANIM_INDEX ,DMALL_LUCEMON_ANIM_INDEX ,DMALL_LUNAMON_ANIM_INDEX
                },
              };
            case DMALL_NYOKIMON_ANIM_INDEX:
              return {
                // Stage: Baby I
                .conditions = { .next_evolution_time_sec = 600 },
                
                .num_animation_indices = 5,
                .animation_indices = {
                  DMALL_PYOCOMON_ANIM_INDEX ,DMALL_BUDMON_ANIM_INDEX ,DMALL_KOROMON_ANIM_INDEX ,DMALL_PYOCOMON_ANIM_INDEX ,DMALL_TANEMON_ANIM_INDEX
                },
              };
            case DMALL_OFANIMON_CORE_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMALL_OFANIMON_FALLDOWN_MODE_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMALL_OGREMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_DIGITAMAMON_ANIM_INDEX ,DMALL_REBELLIMON_ANIM_INDEX ,DMALL_ANDROMON_ANIM_INDEX ,DMALL_AERO_V_DRAMON_ANIM_INDEX ,DMALL_ANDROMON_ANIM_INDEX ,DMALL_ANOMALOCARIMON_ANIM_INDEX ,DMALL_ARCHNEMON_ANIM_INDEX ,DMALL_ASURAMON_ANIM_INDEX ,DMALL_ASTAMON_ANIM_INDEX ,DMALL_BEOWOLFMON_ANIM_INDEX ,DMALL_BIG_MAMEMON_ANIM_INDEX ,DMALL_BLACK_MEGALO_GROWMON_ANIM_INDEX ,DMALL_CHIMAIRAMON_ANIM_INDEX ,DMALL_CYBERDRAMON_ANIM_INDEX ,DMALL_DAGOMON_ANIM_INDEX
                },
              };
            case DMALL_OGREMON_X_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 4,
                .animation_indices = {
                  DMALL_VAMDEMON_X_ANIM_INDEX ,DMALL_MAMMON_X_ANIM_INDEX ,DMALL_MAMETYRAMON_ANIM_INDEX ,DMALL_MAMETYRAMON_ANIM_INDEX
                },
              };
            case DMALL_OGUDOMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMALL_OGUDOMON_X_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMALL_OKUWAMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 12,
                .animation_indices = {
                  DMALL_ANCIENT_BEATMON_ANIM_INDEX ,DMALL_DARKDRAMON_ANIM_INDEX ,DMALL_DIABLOMON_ANIM_INDEX ,DMALL_GRANDIS_KUWAGAMON_ANIM_INDEX ,DMALL_HERAKLE_KABUTERIMON_ANIM_INDEX ,DMALL_HOLYDRAMON_ANIM_INDEX ,DMALL_METAL_ETEMON_ANIM_INDEX ,DMALL_PINOCHIMON_ANIM_INDEX ,DMALL_PUKUMON_ANIM_INDEX ,DMALL_SABER_LEOMON_ANIM_INDEX ,DMALL_TIGER_VESPAMON_ANIM_INDEX ,DMALL_VENOM_VAMDEMON_ANIM_INDEX
                },
              };
            case DMALL_OKUWAMON_X_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 12,
                .animation_indices = {
                  DMALL_GRANDIS_KUWAGAMON_ANIM_INDEX ,DMALL_GRANDIS_KUWAGAMON_ANIM_INDEX ,DMALL_ROSEMON_X_ANIM_INDEX ,DMALL_BEEL_STARMON_X_ANIM_INDEX ,DMALL_SKULL_MAMMON_X_ANIM_INDEX ,DMALL_ANCIENT_BEATMON_ANIM_INDEX ,DMALL_DORUGORAMON_ANIM_INDEX ,DMALL_GIGA_SEADRAMON_ANIM_INDEX ,DMALL_GRANDIS_KUWAGAMON_ANIM_INDEX ,DMALL_HERAKLE_KABUTERIMON_ANIM_INDEX ,DMALL_HOLYDRAMON_ANIM_INDEX ,DMALL_METAL_ETEMON_ANIM_INDEX
                },
              };
            case DMALL_OMEGAMON_ALTER_S_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMALL_OMEGAMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMALL_OMEGAMON_X_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMALL_OMEGAMON_ZWART_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMALL_OMEGA_SHOUTMON_X_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_RAPIDMON_X_ANIM_INDEX ,DMALL_JUSTIMON_X_ANIM_INDEX ,DMALL_ALPHAMON_ANIM_INDEX ,DMALL_HOUOUMON_X_ANIM_INDEX ,DMALL_TIGER_VESPAMON_ANIM_INDEX ,DMALL_GAIOUMON_ANIM_INDEX ,DMALL_DINOTIGERMON_ANIM_INDEX ,DMALL_HOLYDRAMON_X_ANIM_INDEX ,DMALL_EBEMON_X_ANIM_INDEX ,DMALL_HEXEBLAUMON_ANIM_INDEX ,DMALL_METALLICDRAMON_ANIM_INDEX ,DMALL_NOBLE_PUMPMON_ANIM_INDEX ,DMALL_ALPHAMON_ANIM_INDEX ,DMALL_DINOTIGERMON_ANIM_INDEX ,DMALL_TIGER_VESPAMON_ANIM_INDEX
                },
              };
            case DMALL_OMEKAMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_OMEGA_SHOUTMON_X_ANIM_INDEX ,DMALL_CYBERDRAMON_X_ANIM_INDEX ,DMALL_DORUGUREMON_ANIM_INDEX ,DMALL_GARUDAMON_X_ANIM_INDEX ,DMALL_CANNONBEEMON_ANIM_INDEX ,DMALL_GRADEMON_ANIM_INDEX ,DMALL_MAMEMON_X_ANIM_INDEX ,DMALL_CRYS_PALEDRAMON_ANIM_INDEX ,DMALL_JAZARICHMON_ANIM_INDEX ,DMALL_PUMPMON_ANIM_INDEX ,DMALL_CANNONBEEMON_ANIM_INDEX ,DMALL_CRYS_PALEDRAMON_ANIM_INDEX ,DMALL_DORUGUREMON_ANIM_INDEX ,DMALL_GRADEMON_ANIM_INDEX ,DMALL_HISYARYUMON_ANIM_INDEX
                },
              };
            case DMALL_OPHANIMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMALL_OPHANIMON_X_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMALL_ORDINEMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMALL_OROCHIMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 5,
                .animation_indices = {
                  DMALL_CRES_GARURUMON_ANIM_INDEX ,DMALL_HOLYDRAMON_ANIM_INDEX ,DMALL_METAL_ETEMON_ANIM_INDEX ,DMALL_METAL_GARURUMON_ANIM_INDEX ,DMALL_SHIN_MONZAEMON_ANIM_INDEX
                },
              };
            case DMALL_OTAMAMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_GEKOMON_ANIM_INDEX ,DMALL_COELAMON_ANIM_INDEX ,DMALL_GAWAPPAMON_ANIM_INDEX ,DMALL_GEKOMON_ANIM_INDEX ,DMALL_GEREMON_ANIM_INDEX ,DMALL_GESOMON_ANIM_INDEX ,DMALL_HOOKMON_ANIM_INDEX ,DMALL_KUWAGAMON_ANIM_INDEX ,DMALL_MEICOOMON_ANIM_INDEX ,DMALL_MONOCHROMON_ANIM_INDEX ,DMALL_NUMEMON_ANIM_INDEX ,DMALL_PLATINUM_SCUMON_ANIM_INDEX ,DMALL_SCUMON_ANIM_INDEX ,DMALL_SEADRAMON_ANIM_INDEX ,DMALL_SHELLMON_ANIM_INDEX
                },
              };
            case DMALL_OTAMAMON_RED_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 10,
                .animation_indices = {
                  DMALL_GEKOMON_ANIM_INDEX ,DMALL_GREYMON_ANIM_INDEX ,DMALL_HOOKMON_ANIM_INDEX ,DMALL_SEADRAMON_ANIM_INDEX ,DMALL_SHELLMON_ANIM_INDEX ,DMALL_STARMON_ANIM_INDEX ,DMALL_TAILMON_ANIM_INDEX ,DMALL_TORTAMON_ANIM_INDEX ,DMALL_WHAMON_ANIM_INDEX ,DMALL_YANMAMON_ANIM_INDEX
                },
              };
            case DMALL_OTAMAMON_X_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_SEADRAMON_X_ANIM_INDEX ,DMALL_FILMON_ANIM_INDEX ,DMALL_NUMEMON_X_ANIM_INDEX ,DMALL_VELGRMON_ANIM_INDEX ,DMALL_ALLOMON_X_ANIM_INDEX ,DMALL_FILMON_ANIM_INDEX ,DMALL_GEKOMON_ANIM_INDEX ,DMALL_HOOKMON_ANIM_INDEX ,DMALL_SEADRAMON_ANIM_INDEX ,DMALL_SHELLMON_ANIM_INDEX ,DMALL_STARMON_ANIM_INDEX ,DMALL_TAILMON_ANIM_INDEX ,DMALL_TORTAMON_ANIM_INDEX ,DMALL_VELGRMON_ANIM_INDEX ,DMALL_WHAMON_ANIM_INDEX
                },
              };
            case DMALL_OURYUMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = 230400 },
                
                .num_animation_indices = 8,
                .animation_indices = {
                  DMALL_ULFORCE_V_DRAMON_X_ANIM_INDEX ,DMALL_EXAMON_X_ANIM_INDEX ,DMALL_DUFTMON_X_ANIM_INDEX ,DMALL_SLEIPMON_X_ANIM_INDEX ,DMALL_JESMON_X_ANIM_INDEX ,DMALL_OMEGAMON_X_ANIM_INDEX ,DMALL_ALPHAMON_OURYUKEN_ANIM_INDEX ,DMALL_JESMON_GX_ANIM_INDEX
                },
              };
            case DMALL_PAFUMON_ANIM_INDEX:
              return {
                // Stage: Baby I
                .conditions = { .next_evolution_time_sec = 600 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMALL_PAGUMON_ANIM_INDEX:
              return {
                // Stage: Baby II
                .conditions = { .next_evolution_time_sec = 43200 },
                
                .num_animation_indices = 11,
                .animation_indices = {
                  DMALL_GIZAMON_ANIM_INDEX ,DMALL_GAZIMON_ANIM_INDEX ,DMALL_GIZAMON_ANIM_INDEX ,DMALL_BEARMON_ANIM_INDEX ,DMALL_GAZIMON_ANIM_INDEX ,DMALL_GHOSTMON_ANIM_INDEX ,DMALL_GIZAMON_ANIM_INDEX ,DMALL_IMPMON_ANIM_INDEX ,DMALL_LOPMON_ANIM_INDEX ,DMALL_OTAMAMON_ANIM_INDEX ,DMALL_PICO_DEVIMON_ANIM_INDEX
                },
              };
            case DMALL_PAILDRAMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_ANCIENT_SPHINXMON_ANIM_INDEX ,DMALL_CHAOSDRAMON_ANIM_INDEX ,DMALL_DEATHMON_ANIM_INDEX ,DMALL_DORUGORAMON_ANIM_INDEX ,DMALL_DUKEMON_ANIM_INDEX ,DMALL_GRAND_LOCOMON_ANIM_INDEX ,DMALL_GUNDRAMON_ANIM_INDEX ,DMALL_HERAKLE_KABUTERIMON_ANIM_INDEX ,DMALL_MEGIDRAMON_ANIM_INDEX ,DMALL_METAL_GARURUMON_ANIM_INDEX ,DMALL_METAL_SEADRAMON_ANIM_INDEX ,DMALL_SERAPHIMON_ANIM_INDEX ,DMALL_ULFORCE_V_DRAMON_ANIM_INDEX ,DMALL_VALDURMON_ANIM_INDEX ,DMALL_WAR_GREYMON_ANIM_INDEX
                },
              };
            case DMALL_PALEDRAMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_CRYS_PALEDRAMON_ANIM_INDEX ,DMALL_OMEGA_SHOUTMON_X_ANIM_INDEX ,DMALL_CYBERDRAMON_X_ANIM_INDEX ,DMALL_DORUGUREMON_ANIM_INDEX ,DMALL_GARUDAMON_X_ANIM_INDEX ,DMALL_CANNONBEEMON_ANIM_INDEX ,DMALL_GRADEMON_ANIM_INDEX ,DMALL_MAMEMON_X_ANIM_INDEX ,DMALL_CRYS_PALEDRAMON_ANIM_INDEX ,DMALL_JAZARICHMON_ANIM_INDEX ,DMALL_PUMPMON_ANIM_INDEX ,DMALL_CRESCEMON_ANIM_INDEX ,DMALL_CRYS_PALEDRAMON_ANIM_INDEX ,DMALL_DORUGUREMON_ANIM_INDEX ,DMALL_HISYARYUMON_ANIM_INDEX
                },
              };
            case DMALL_PALMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_SUNFLOWMON_ANIM_INDEX ,DMALL_TOGEMON_ANIM_INDEX ,DMALL_LEOMON_ANIM_INDEX ,DMALL_KUWAGAMON_ANIM_INDEX ,DMALL_COELAMON_ANIM_INDEX ,DMALL_ANGEMON_ANIM_INDEX ,DMALL_BAKEMON_ANIM_INDEX ,DMALL_BIRDRAMON_ANIM_INDEX ,DMALL_CENTALMON_ANIM_INDEX ,DMALL_COELAMON_ANIM_INDEX ,DMALL_DOKUGUMON_ANIM_INDEX ,DMALL_FUGAMON_ANIM_INDEX ,DMALL_GEREMON_ANIM_INDEX ,DMALL_GROWMON_ANIM_INDEX ,DMALL_IGAMON_ANIM_INDEX
                },
              };
            case DMALL_PALMON_X_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_TOGEMON_X_ANIM_INDEX ,DMALL_SIESAMON_X_ANIM_INDEX ,DMALL_MERAMON_X_ANIM_INDEX ,DMALL_DORUGAMON_ANIM_INDEX ,DMALL_PTERANOMON_X_ANIM_INDEX ,DMALL_OMEKAMON_ANIM_INDEX ,DMALL_PALEDRAMON_ANIM_INDEX ,DMALL_JAZARDMON_ANIM_INDEX ,DMALL_ANGEMON_ANIM_INDEX ,DMALL_DOKUGUMON_ANIM_INDEX ,DMALL_FUGAMON_ANIM_INDEX ,DMALL_GROWMON_ANIM_INDEX ,DMALL_IGAMON_ANIM_INDEX ,DMALL_KIWIMON_ANIM_INDEX ,DMALL_KOUGAMON_ANIM_INDEX
                },
              };
            case DMALL_PANDAMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 7,
                .animation_indices = {
                  DMALL_BANCHO_LEOMON_ANIM_INDEX ,DMALL_DARKDRAMON_ANIM_INDEX ,DMALL_DEATHMON_ANIM_INDEX ,DMALL_KING_ETEMON_ANIM_INDEX ,DMALL_METAL_GARURUMON_ANIM_INDEX ,DMALL_METAL_GARURUMON_BLACK_ANIM_INDEX ,DMALL_OMEGAMON_ZWART_ANIM_INDEX
                },
              };
            case DMALL_PANJYAMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 10,
                .animation_indices = {
                  DMALL_ANCIENT_MEGATHERIUMON_ANIM_INDEX ,DMALL_BANCHO_LEOMON_ANIM_INDEX ,DMALL_DINOTIGERMON_ANIM_INDEX ,DMALL_DUFTMON_ANIM_INDEX ,DMALL_GANKOOMON_ANIM_INDEX ,DMALL_HEXEBLAUMON_ANIM_INDEX ,DMALL_HOLYDRAMON_ANIM_INDEX ,DMALL_SABER_LEOMON_ANIM_INDEX ,DMALL_SAKUYAMON_ANIM_INDEX ,DMALL_SKULL_MAMMON_ANIM_INDEX
                },
              };
            case DMALL_PANJYAMON_X_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 5,
                .animation_indices = {
                  DMALL_ANCIENT_MEGATHERIUMON_ANIM_INDEX ,DMALL_BANCHO_LEOMON_ANIM_INDEX ,DMALL_DINOTIGERMON_ANIM_INDEX ,DMALL_HOLYDRAMON_ANIM_INDEX ,DMALL_SABER_LEOMON_ANIM_INDEX
                },
              };
            case DMALL_PAOMON_ANIM_INDEX:
              return {
                // Stage: Baby I
                .conditions = { .next_evolution_time_sec = 600 },
                
                .num_animation_indices = 2,
                .animation_indices = {
                  DMALL_XIAOMON_ANIM_INDEX ,DMALL_XIAOMON_ANIM_INDEX
                },
              };
            case DMALL_PARASAURMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 4,
                .animation_indices = {
                  DMALL_ARCHNEMON_ANIM_INDEX ,DMALL_BLOSSOMON_ANIM_INDEX ,DMALL_ENTMON_ANIM_INDEX ,DMALL_LILIMON_ANIM_INDEX
                },
              };
            case DMALL_PEGASMON_X_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 10,
                .animation_indices = {
                  DMALL_MONZAEMON_X_ANIM_INDEX ,DMALL_ANGEWOMON_X_ANIM_INDEX ,DMALL_ANOMALOCARIMON_X_ANIM_INDEX ,DMALL_GRADEMON_ANIM_INDEX ,DMALL_MAMEMON_X_ANIM_INDEX ,DMALL_CRYS_PALEDRAMON_ANIM_INDEX ,DMALL_JAZARICHMON_ANIM_INDEX ,DMALL_PUMPMON_ANIM_INDEX ,DMALL_GRADEMON_ANIM_INDEX ,DMALL_HISYARYUMON_ANIM_INDEX
                },
              };
            case DMALL_PENMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_RUKAMON_ANIM_INDEX ,DMALL_YUKIDARUMON_ANIM_INDEX ,DMALL_AIRDRAMON_ANIM_INDEX ,DMALL_BAKEMON_ANIM_INDEX ,DMALL_BIRDRAMON_ANIM_INDEX ,DMALL_DOBERMON_ANIM_INDEX ,DMALL_EBIDRAMON_ANIM_INDEX ,DMALL_GARURUMON_ANIM_INDEX ,DMALL_GESOMON_ANIM_INDEX ,DMALL_GREYMON_ANIM_INDEX ,DMALL_IKKAKUMON_ANIM_INDEX ,DMALL_KIWIMON_ANIM_INDEX ,DMALL_LEOMON_ANIM_INDEX ,DMALL_MERAMON_ANIM_INDEX ,DMALL_MONOCHROMON_ANIM_INDEX
                },
              };
            case DMALL_PETIMERAMON_ANIM_INDEX:
              return {
                // Stage: Baby II
                .conditions = { .next_evolution_time_sec = 43200 },
                
                .num_animation_indices = 12,
                .animation_indices = {
                  DMALL_CANDMON_ANIM_INDEX ,DMALL_GHOSTMON_ANIM_INDEX ,DMALL_VORVOMON_ANIM_INDEX ,DMALL_BAKUMON_ANIM_INDEX ,DMALL_CANDMON_ANIM_INDEX ,DMALL_CORONAMON_ANIM_INDEX ,DMALL_GHOSTMON_ANIM_INDEX ,DMALL_GUILMON_ANIM_INDEX ,DMALL_IMPMON_ANIM_INDEX ,DMALL_PICO_DEVIMON_ANIM_INDEX ,DMALL_PLOTMON_ANIM_INDEX ,DMALL_VORVOMON_ANIM_INDEX
                },
              };
            case DMALL_PETITMAMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 2,
                .animation_indices = {
                  DMALL_DEVIMON_ANIM_INDEX ,DMALL_IGAMON_ANIM_INDEX
                },
              };
            case DMALL_PETITMON_ANIM_INDEX:
              return {
                // Stage: Baby I
                .conditions = { .next_evolution_time_sec = 600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DMALL_BABYDMON_ANIM_INDEX
                },
              };
            case DMALL_PHANTOMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_APOCALYMON_ANIM_INDEX ,DMALL_BARBAMON_ANIM_INDEX ,DMALL_BLACK_WAR_GREYMON_ANIM_INDEX ,DMALL_DARKDRAMON_ANIM_INDEX ,DMALL_DEATHMON_BLACK_ANIM_INDEX ,DMALL_DEMON_ANIM_INDEX ,DMALL_METAL_ETEMON_ANIM_INDEX ,DMALL_MUGENDRAMON_ANIM_INDEX ,DMALL_NOBLE_PUMPMON_ANIM_INDEX ,DMALL_PIEMON_ANIM_INDEX ,DMALL_PINOCHIMON_ANIM_INDEX ,DMALL_PUKUMON_ANIM_INDEX ,DMALL_TITAMON_ANIM_INDEX ,DMALL_VENOM_VAMDEMON_ANIM_INDEX ,DMALL_WAR_GREYMON_ANIM_INDEX
                },
              };
            case DMALL_PHASCOMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 9,
                .animation_indices = {
                  DMALL_PORCUPAMON_ANIM_INDEX ,DMALL_LEOMON_ANIM_INDEX ,DMALL_MAD_LEOMON_ANIM_INDEX ,DMALL_PORCUPAMON_ANIM_INDEX ,DMALL_SANGLOUPMON_ANIM_INDEX ,DMALL_SHADRAMON_ANIM_INDEX ,DMALL_TROOPMON_ANIM_INDEX ,DMALL_WIZARMON_ANIM_INDEX ,DMALL_YUKIDARUMON_ANIM_INDEX
                },
              };
            case DMALL_PICCOLOMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_BLOOM_LORDMON_ANIM_INDEX ,DMALL_BLOOM_LORDMON_ANIM_INDEX ,DMALL_BOLTMON_ANIM_INDEX ,DMALL_BRYWELUDRAMON_ANIM_INDEX ,DMALL_CHERUBIMON_VIRTUE_ANIM_INDEX ,DMALL_DEATHMON_BLACK_ANIM_INDEX ,DMALL_GRIFFOMON_ANIM_INDEX ,DMALL_HOLYDRAMON_ANIM_INDEX ,DMALL_HOUOUMON_ANIM_INDEX ,DMALL_MARIN_ANGEMON_ANIM_INDEX ,DMALL_METAL_GARURUMON_ANIM_INDEX ,DMALL_METAL_SEADRAMON_ANIM_INDEX ,DMALL_MUGENDRAMON_ANIM_INDEX ,DMALL_PIEMON_ANIM_INDEX ,DMALL_PLESIOMON_ANIM_INDEX
                },
              };
            case DMALL_PICKMON_ANIM_INDEX:
              return {
                // Stage: Baby II
                .conditions = { .next_evolution_time_sec = 43200 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DMALL_GUILMON_ANIM_INDEX
                },
              };
            case DMALL_PICO_DEVIMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_DEVIMON_ANIM_INDEX ,DMALL_ANGEMON_ANIM_INDEX ,DMALL_BAKEMON_ANIM_INDEX ,DMALL_BLACK_GROWMON_ANIM_INDEX ,DMALL_BLACK_TAILMON_ANIM_INDEX ,DMALL_COELAMON_ANIM_INDEX ,DMALL_CYCLOMON_ANIM_INDEX ,DMALL_DEATH_X_DORUGAMON_ANIM_INDEX ,DMALL_DEVIMON_ANIM_INDEX ,DMALL_DINOHUMON_ANIM_INDEX ,DMALL_DOKUGUMON_ANIM_INDEX ,DMALL_EBIDRAMON_ANIM_INDEX ,DMALL_GARURUMON_ANIM_INDEX ,DMALL_GEREMON_ANIM_INDEX ,DMALL_GREYMON_ANIM_INDEX
                },
              };
            case DMALL_PIDMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 10,
                .animation_indices = {
                  DMALL_ANGEWOMON_ANIM_INDEX ,DMALL_ASURAMON_ANIM_INDEX ,DMALL_CYBERDRAMON_ANIM_INDEX ,DMALL_FLAREMON_ANIM_INDEX ,DMALL_GARUDAMON_ANIM_INDEX ,DMALL_GIROMON_ANIM_INDEX ,DMALL_HOLY_ANGEMON_ANIM_INDEX ,DMALL_INSEKIMON_ANIM_INDEX ,DMALL_LILIMON_ANIM_INDEX ,DMALL_MONZAEMON_ANIM_INDEX
                },
              };
            case DMALL_PIEMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMALL_PINOCHIMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMALL_PIPIMON_ANIM_INDEX:
              return {
                // Stage: Baby I
                .conditions = { .next_evolution_time_sec = 600 },
                
                .num_animation_indices = 2,
                .animation_indices = {
                  DMALL_PYOCOMON_ANIM_INDEX ,DMALL_TANEMON_ANIM_INDEX
                },
              };
            case DMALL_PIRANIMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 5,
                .animation_indices = {
                  DMALL_ANCIENT_MERMAIMON_ANIM_INDEX ,DMALL_LEVIAMON_ANIM_INDEX ,DMALL_METAL_SEADRAMON_ANIM_INDEX ,DMALL_PLESIOMON_ANIM_INDEX ,DMALL_REGALECUSMON_ANIM_INDEX
                },
              };
            case DMALL_PITCHMON_ANIM_INDEX:
              return {
                // Stage: Baby I
                .conditions = { .next_evolution_time_sec = 600 },
                
                .num_animation_indices = 4,
                .animation_indices = {
                  DMALL_PUKAMON_ANIM_INDEX ,DMALL_PUKAMON_ANIM_INDEX ,DMALL_NYAROMON_ANIM_INDEX ,DMALL_TUNOMON_ANIM_INDEX
                },
              };
            case DMALL_PIYOMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_BIRDRAMON_ANIM_INDEX ,DMALL_MONOCHROMON_ANIM_INDEX ,DMALL_LEOMON_ANIM_INDEX ,DMALL_KUWAGAMON_ANIM_INDEX ,DMALL_AIRDRAMON_ANIM_INDEX ,DMALL_ANGEMON_ANIM_INDEX ,DMALL_BAKEMON_ANIM_INDEX ,DMALL_BIRDRAMON_ANIM_INDEX ,DMALL_BLACK_GROWMON_ANIM_INDEX ,DMALL_BLACK_TAILMON_ANIM_INDEX ,DMALL_CENTALMON_ANIM_INDEX ,DMALL_DOKUGUMON_ANIM_INDEX ,DMALL_FUGAMON_ANIM_INDEX ,DMALL_GARURUMON_BLACK_ANIM_INDEX ,DMALL_GAWAPPAMON_ANIM_INDEX
                },
              };
            case DMALL_PLATINUM_NUMEMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = 230400 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DMALL_OMEGAMON_X_ANIM_INDEX
                },
              };
            case DMALL_PLATINUM_SCUMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 6,
                .animation_indices = {
                  DMALL_ETEMON_ANIM_INDEX ,DMALL_GERBEMON_ANIM_INDEX ,DMALL_GREAT_KING_SCUMON_ANIM_INDEX ,DMALL_INSEKIMON_ANIM_INDEX ,DMALL_METAL_MAMEMON_ANIM_INDEX ,DMALL_VADEMON_ANIM_INDEX
                },
              };
            case DMALL_PLESIOMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMALL_PLESIOMON_X_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = 230400 },
                
                .num_animation_indices = 8,
                .animation_indices = {
                  DMALL_ULFORCE_V_DRAMON_X_ANIM_INDEX ,DMALL_EXAMON_X_ANIM_INDEX ,DMALL_DUFTMON_X_ANIM_INDEX ,DMALL_SLEIPMON_X_ANIM_INDEX ,DMALL_JESMON_X_ANIM_INDEX ,DMALL_OMEGAMON_X_ANIM_INDEX ,DMALL_ALPHAMON_OURYUKEN_ANIM_INDEX ,DMALL_JESMON_GX_ANIM_INDEX
                },
              };
            case DMALL_PLOTMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_TAILMON_ANIM_INDEX ,DMALL_AIRDRAMON_ANIM_INDEX ,DMALL_ANGEMON_ANIM_INDEX ,DMALL_BITMON_ANIM_INDEX ,DMALL_BLACK_TAILMON_ANIM_INDEX ,DMALL_CENTALMON_ANIM_INDEX ,DMALL_DOBERMON_ANIM_INDEX ,DMALL_DRIMOGEMON_ANIM_INDEX ,DMALL_GALGOMON_ANIM_INDEX ,DMALL_GAOGAMON_ANIM_INDEX ,DMALL_GARURUMON_ANIM_INDEX ,DMALL_GEREMON_ANIM_INDEX ,DMALL_GREYMON_ANIM_INDEX ,DMALL_GUARDROMON_ANIM_INDEX ,DMALL_ICEMON_ANIM_INDEX
                },
              };
            case DMALL_PLOTMON_X_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_NEFERTIMON_X_ANIM_INDEX ,DMALL_SEADRAMON_X_ANIM_INDEX ,DMALL_ALLOMON_X_ANIM_INDEX ,DMALL_AIRDRAMON_ANIM_INDEX ,DMALL_ANGEMON_ANIM_INDEX ,DMALL_BLACK_TAILMON_ANIM_INDEX ,DMALL_GAOGAMON_ANIM_INDEX ,DMALL_GARURUMON_ANIM_INDEX ,DMALL_GREYMON_ANIM_INDEX ,DMALL_GUARDROMON_ANIM_INDEX ,DMALL_ICEMON_ANIM_INDEX ,DMALL_LYNXMON_ANIM_INDEX ,DMALL_MEICOOMON_ANIM_INDEX ,DMALL_PIDMON_ANIM_INDEX ,DMALL_REPPAMON_ANIM_INDEX
                },
              };
            case DMALL_POKOMON_ANIM_INDEX:
              return {
                // Stage: Baby II
                .conditions = { .next_evolution_time_sec = 43200 },
                
                .num_animation_indices = 2,
                .animation_indices = {
                  DMALL_RENAMON_ANIM_INDEX ,DMALL_RENAMON_ANIM_INDEX
                },
              };
            case DMALL_POPOMON_ANIM_INDEX:
              return {
                // Stage: Baby I
                .conditions = { .next_evolution_time_sec = 600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DMALL_WANYAMON_ANIM_INDEX
                },
              };
            case DMALL_PORCUPAMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_ASTAMON_ANIM_INDEX ,DMALL_AERO_V_DRAMON_ANIM_INDEX ,DMALL_ANOMALOCARIMON_ANIM_INDEX ,DMALL_ASTAMON_ANIM_INDEX ,DMALL_ASURAMON_ANIM_INDEX ,DMALL_BAALMON_ANIM_INDEX ,DMALL_BEOWOLFMON_ANIM_INDEX ,DMALL_BIG_MAMEMON_ANIM_INDEX ,DMALL_DAGOMON_ANIM_INDEX ,DMALL_DARK_KNIGHTMON_ANIM_INDEX ,DMALL_ETEMON_ANIM_INDEX ,DMALL_GERBEMON_ANIM_INDEX ,DMALL_HANGYOMON_ANIM_INDEX ,DMALL_MEGADRAMON_ANIM_INDEX ,DMALL_MEGALO_GROWMON_ANIM_INDEX
                },
              };
            case DMALL_POROMON_ANIM_INDEX:
              return {
                // Stage: Baby II
                .conditions = { .next_evolution_time_sec = 43200 },
                
                .num_animation_indices = 2,
                .animation_indices = {
                  DMALL_TINKERMON_ANIM_INDEX ,DMALL_WORMMON_ANIM_INDEX
                },
              };
            case DMALL_PRINCE_MAMEMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMALL_PRINCE_MAMEMON_X_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = 230400 },
                
                .num_animation_indices = 3,
                .animation_indices = {
                  DMALL_DEMON_X_ANIM_INDEX ,DMALL_LUCEMON_X_ANIM_INDEX ,DMALL_DIABLOMON_X_ANIM_INDEX
                },
              };
            case DMALL_PTERANOMON_X_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 14,
                .animation_indices = {
                  DMALL_OMEGA_SHOUTMON_X_ANIM_INDEX ,DMALL_CYBERDRAMON_X_ANIM_INDEX ,DMALL_DORUGUREMON_ANIM_INDEX ,DMALL_GARUDAMON_X_ANIM_INDEX ,DMALL_CANNONBEEMON_ANIM_INDEX ,DMALL_GRADEMON_ANIM_INDEX ,DMALL_MAMEMON_X_ANIM_INDEX ,DMALL_CRYS_PALEDRAMON_ANIM_INDEX ,DMALL_JAZARICHMON_ANIM_INDEX ,DMALL_PUMPMON_ANIM_INDEX ,DMALL_ANDROMON_ANIM_INDEX ,DMALL_BLOSSOMON_ANIM_INDEX ,DMALL_CANNONBEEMON_ANIM_INDEX ,DMALL_MAMETYRAMON_ANIM_INDEX
                },
              };
            case DMALL_PUKAMON_ANIM_INDEX:
              return {
                // Stage: Baby II
                .conditions = { .next_evolution_time_sec = 43200 },
                
                .num_animation_indices = 14,
                .animation_indices = {
                  DMALL_GOMAMON_ANIM_INDEX ,DMALL_CLEAR_AGUMON_ANIM_INDEX ,DMALL_CORONAMON_ANIM_INDEX ,DMALL_GANIMON_ANIM_INDEX ,DMALL_GIZAMON_ANIM_INDEX ,DMALL_GOMAMON_ANIM_INDEX ,DMALL_KOEMON_ANIM_INDEX ,DMALL_LUNAMON_ANIM_INDEX ,DMALL_OTAMAMON_ANIM_INDEX ,DMALL_PENMON_ANIM_INDEX ,DMALL_SANGOMON_ANIM_INDEX ,DMALL_SHAKOMON_ANIM_INDEX ,DMALL_V_MON_ANIM_INDEX ,DMALL_YUKI_AGUMON_ANIM_INDEX
                },
              };
            case DMALL_PUKUMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMALL_PULSEMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DMALL_THUNDERBALLMON_ANIM_INDEX
                },
              };
            case DMALL_PUMPMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 14,
                .animation_indices = {
                  DMALL_NOBLE_PUMPMON_ANIM_INDEX ,DMALL_NOBLE_PUMPMON_ANIM_INDEX ,DMALL_BEELZEBUMON_ANIM_INDEX ,DMALL_BOLTMON_ANIM_INDEX ,DMALL_DINOTIGERMON_ANIM_INDEX ,DMALL_GRIFFOMON_ANIM_INDEX ,DMALL_METAL_GARURUMON_ANIM_INDEX ,DMALL_METAL_SEADRAMON_ANIM_INDEX ,DMALL_NOBLE_PUMPMON_ANIM_INDEX ,DMALL_PIEMON_ANIM_INDEX ,DMALL_PINOCHIMON_ANIM_INDEX ,DMALL_PLESIOMON_ANIM_INDEX ,DMALL_ROSEMON_ANIM_INDEX ,DMALL_SABER_LEOMON_ANIM_INDEX
                },
              };
            case DMALL_PUPUMON_ANIM_INDEX:
              return {
                // Stage: Baby I
                .conditions = { .next_evolution_time_sec = 600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DMALL_PUROROMON_ANIM_INDEX
                },
              };
            case DMALL_PUROROMON_ANIM_INDEX:
              return {
                // Stage: Baby II
                .conditions = { .next_evolution_time_sec = 43200 },
                
                .num_animation_indices = 3,
                .animation_indices = {
                  DMALL_DORUMON_ANIM_INDEX ,DMALL_FUNBEEMON_ANIM_INDEX ,DMALL_RYUDAMON_ANIM_INDEX
                },
              };
            case DMALL_PURURUMON_ANIM_INDEX:
              return {
                // Stage: Baby I
                .conditions = { .next_evolution_time_sec = 600 },
                
                .num_animation_indices = 3,
                .animation_indices = {
                  DMALL_POROMON_ANIM_INDEX ,DMALL_NYAROMON_ANIM_INDEX ,DMALL_POROMON_ANIM_INDEX
                },
              };
            case DMALL_PUSUMON_ANIM_INDEX:
              return {
                // Stage: Baby I
                .conditions = { .next_evolution_time_sec = 600 },
                
                .num_animation_indices = 2,
                .animation_indices = {
                  DMALL_PUSURIMON_ANIM_INDEX ,DMALL_PUSURIMON_ANIM_INDEX
                },
              };
            case DMALL_PUSURIMON_ANIM_INDEX:
              return {
                // Stage: Baby II
                .conditions = { .next_evolution_time_sec = 43200 },
                
                .num_animation_indices = 2,
                .animation_indices = {
                  DMALL_HERISSMON_ANIM_INDEX ,DMALL_HERISSMON_ANIM_INDEX
                },
              };
            case DMALL_PUTTIMON_ANIM_INDEX:
              return {
                // Stage: Baby I
                .conditions = { .next_evolution_time_sec = 600 },
                
                .num_animation_indices = 3,
                .animation_indices = {
                  DMALL_CUPIMON_ANIM_INDEX ,DMALL_TOKOMON_X_ANIM_INDEX ,DMALL_CUPIMON_ANIM_INDEX
                },
              };
            case DMALL_PUYOMON_ANIM_INDEX:
              return {
                // Stage: Baby I
                .conditions = { .next_evolution_time_sec = 600 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMALL_PYOCOMON_ANIM_INDEX:
              return {
                // Stage: Baby II
                .conditions = { .next_evolution_time_sec = 43200 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_PIYOMON_ANIM_INDEX ,DMALL_ELECMON_ANIM_INDEX ,DMALL_ELECMON_VIOLET_ANIM_INDEX ,DMALL_FLORAMON_ANIM_INDEX ,DMALL_GAZIMON_ANIM_INDEX ,DMALL_HYOKOMON_ANIM_INDEX ,DMALL_JAZAMON_ANIM_INDEX ,DMALL_KUNEMON_ANIM_INDEX ,DMALL_MUCHOMON_ANIM_INDEX ,DMALL_MUSHMON_ANIM_INDEX ,DMALL_PALMON_ANIM_INDEX ,DMALL_PENMON_ANIM_INDEX ,DMALL_PHASCOMON_ANIM_INDEX ,DMALL_PICO_DEVIMON_ANIM_INDEX ,DMALL_PIYOMON_ANIM_INDEX
                },
              };
            case DMALL_PYONMON_ANIM_INDEX:
              return {
                // Stage: Baby I
                .conditions = { .next_evolution_time_sec = 600 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMALL_RAFFLESIMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = 230400 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DMALL_MINERVAMON_X_ANIM_INDEX
                },
              };
            case DMALL_RAGNA_LORDMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMALL_RAGUELMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMALL_RAIDENMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMALL_RAIHIMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 5,
                .animation_indices = {
                  DMALL_ANCIENT_SPHINXMON_ANIM_INDEX ,DMALL_BEELZEBUMON_X_ANIM_INDEX ,DMALL_ANCIENT_SPHINXMON_ANIM_INDEX ,DMALL_DEATHMON_ANIM_INDEX ,DMALL_DINOTIGERMON_ANIM_INDEX
                },
              };
            case DMALL_RAIJI_LUDOMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 4,
                .animation_indices = {
                  DMALL_BRYWELUDRAMON_ANIM_INDEX ,DMALL_BRYWELUDRAMON_ANIM_INDEX ,DMALL_DEATHMON_BLACK_ANIM_INDEX ,DMALL_DUKEMON_ANIM_INDEX
                },
              };
            case DMALL_RAPIDMON_ARMOR_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 2,
                .animation_indices = {
                  DMALL_CYBERDRAMON_ANIM_INDEX ,DMALL_MEGALO_GROWMON_ANIM_INDEX
                },
              };
            case DMALL_RAPIDMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 2,
                .animation_indices = {
                  DMALL_CYBERDRAMON_ANIM_INDEX ,DMALL_MEGALO_GROWMON_ANIM_INDEX
                },
              };
            case DMALL_RAPIDMON_X_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = 230400 },
                
                .num_animation_indices = 7,
                .animation_indices = {
                  DMALL_MAGNAMON_X_ANIM_INDEX ,DMALL_GANKOOMON_X_ANIM_INDEX ,DMALL_DYNASMON_X_ANIM_INDEX ,DMALL_CRANIUMMON_X_ANIM_INDEX ,DMALL_DUKEMON_X_ANIM_INDEX ,DMALL_ALPHAMON_OURYUKEN_ANIM_INDEX ,DMALL_JESMON_GX_ANIM_INDEX
                },
              };
            case DMALL_RAPTORDRAMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 14,
                .animation_indices = {
                  DMALL_GRADEMON_ANIM_INDEX ,DMALL_BLACK_MEGALO_GROWMON_ANIM_INDEX ,DMALL_CANNONBEEMON_ANIM_INDEX ,DMALL_CYBERDRAMON_ANIM_INDEX ,DMALL_DORUGUREMON_ANIM_INDEX ,DMALL_DURAMON_ANIM_INDEX ,DMALL_GIGADRAMON_ANIM_INDEX ,DMALL_GRADEMON_ANIM_INDEX ,DMALL_HISYARYUMON_ANIM_INDEX ,DMALL_HOLY_ANGEMON_ANIM_INDEX ,DMALL_MAMEMON_ANIM_INDEX ,DMALL_MEGADRAMON_ANIM_INDEX ,DMALL_MEGALO_GROWMON_ANIM_INDEX ,DMALL_METAL_GREYMON_ANIM_INDEX
                },
              };
            case DMALL_RASENMON_FURY_MODE_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = 230400 },
                
                .num_animation_indices = 2,
                .animation_indices = {
                  DMALL_RASENMON_ANIM_INDEX ,DMALL_DIABLOMON_X_ANIM_INDEX
                },
              };
            case DMALL_RASENMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMALL_RASIELMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMALL_REBELLIMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 4,
                .animation_indices = {
                  DMALL_CHAOSDRAMON_ANIM_INDEX ,DMALL_GUNDRAMON_ANIM_INDEX ,DMALL_GRAND_LOCOMON_ANIM_INDEX ,DMALL_MUGENDRAMON_ANIM_INDEX
                },
              };
            case DMALL_RED_V_DRAMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 4,
                .animation_indices = {
                  DMALL_AERO_V_DRAMON_ANIM_INDEX ,DMALL_ATLUR_KABUTERIMON_RED_ANIM_INDEX ,DMALL_MEGALO_GROWMON_ANIM_INDEX ,DMALL_METAL_TYRANOMON_ANIM_INDEX
                },
              };
            case DMALL_RED_VEGIMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_AERO_V_DRAMON_ANIM_INDEX ,DMALL_ANOMALOCARIMON_ANIM_INDEX ,DMALL_ASTAMON_ANIM_INDEX ,DMALL_ASURAMON_ANIM_INDEX ,DMALL_ATLUR_KABUTERIMON_RED_ANIM_INDEX ,DMALL_BEOWOLFMON_ANIM_INDEX ,DMALL_BIG_MAMEMON_ANIM_INDEX ,DMALL_DAGOMON_ANIM_INDEX ,DMALL_DARK_KNIGHTMON_ANIM_INDEX ,DMALL_DELUMON_ANIM_INDEX ,DMALL_ETEMON_ANIM_INDEX ,DMALL_GERBEMON_ANIM_INDEX ,DMALL_HANGYOMON_ANIM_INDEX ,DMALL_JYUREIMON_ANIM_INDEX ,DMALL_LILIMON_ANIM_INDEX
                },
              };
            case DMALL_REGALECUSMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMALL_RELEMON_ANIM_INDEX:
              return {
                // Stage: Baby I
                .conditions = { .next_evolution_time_sec = 600 },
                
                .num_animation_indices = 2,
                .animation_indices = {
                  DMALL_POKOMON_ANIM_INDEX ,DMALL_POKOMON_ANIM_INDEX
                },
              };
            case DMALL_RENAMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_KYUBIMON_ANIM_INDEX ,DMALL_YOUKOMON_ANIM_INDEX ,DMALL_BLACK_GROWMON_ANIM_INDEX ,DMALL_BLACK_TAILMON_ANIM_INDEX ,DMALL_DEVIMON_ANIM_INDEX ,DMALL_DOGMON_ANIM_INDEX ,DMALL_EBIDRAMON_ANIM_INDEX ,DMALL_GARURUMON_ANIM_INDEX ,DMALL_GEREMON_ANIM_INDEX ,DMALL_GINRYUMON_ANIM_INDEX ,DMALL_GOLD_NUMEMON_ANIM_INDEX ,DMALL_GROWMON_ANIM_INDEX ,DMALL_GUARDROMON_ANIM_INDEX ,DMALL_HANUMON_ANIM_INDEX ,DMALL_ICE_DEVIMON_ANIM_INDEX
                },
              };
            case DMALL_RENAMON_X_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 5,
                .animation_indices = {
                  DMALL_LEOMON_X_ANIM_INDEX ,DMALL_SANGLOUPMON_ANIM_INDEX ,DMALL_DAMEMON_ANIM_INDEX ,DMALL_DAMEMON_ANIM_INDEX ,DMALL_SANGLOUPMON_ANIM_INDEX
                },
              };
            case DMALL_REPPAMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_AERO_V_DRAMON_ANIM_INDEX ,DMALL_ANDROMON_ANIM_INDEX ,DMALL_ANGEWOMON_ANIM_INDEX ,DMALL_ASURAMON_ANIM_INDEX ,DMALL_BAALMON_ANIM_INDEX ,DMALL_BEOWOLFMON_ANIM_INDEX ,DMALL_BIG_MAMEMON_ANIM_INDEX ,DMALL_BLOSSOMON_ANIM_INDEX ,DMALL_CRESCEMON_ANIM_INDEX ,DMALL_CYBERDRAMON_ANIM_INDEX ,DMALL_DELUMON_ANIM_INDEX ,DMALL_DIGITAMAMON_ANIM_INDEX ,DMALL_DURAMON_ANIM_INDEX ,DMALL_GARUDAMON_ANIM_INDEX ,DMALL_GIROMON_ANIM_INDEX
                },
              };
            case DMALL_RHINOMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 5,
                .animation_indices = {
                  DMALL_DORUGUREMON_ANIM_INDEX ,DMALL_HOLY_ANGEMON_ANIM_INDEX ,DMALL_MEGADRAMON_ANIM_INDEX ,DMALL_METAL_GREYMON_VIRUS_ANIM_INDEX ,DMALL_METAL_MAMEMON_ANIM_INDEX
                },
              };
            case DMALL_RHINOMON_X_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 8,
                .animation_indices = {
                  DMALL_WERE_GARURUMON_X_ANIM_INDEX ,DMALL_MEGALO_GROWMON_X_ANIM_INDEX ,DMALL_YATAGARAMON_ANIM_INDEX ,DMALL_DORUGUREMON_ANIM_INDEX ,DMALL_HOLY_ANGEMON_ANIM_INDEX ,DMALL_MEGADRAMON_ANIM_INDEX ,DMALL_METAL_GREYMON_VIRUS_ANIM_INDEX ,DMALL_METAL_MAMEMON_ANIM_INDEX
                },
              };
            case DMALL_RIZE_GREYMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 11,
                .animation_indices = {
                  DMALL_GAIOUMON_ANIM_INDEX ,DMALL_BANCHO_LEOMON_ANIM_INDEX ,DMALL_CHAOSDRAMON_ANIM_INDEX ,DMALL_DEMON_ANIM_INDEX ,DMALL_DUFTMON_ANIM_INDEX ,DMALL_DUKEMON_ANIM_INDEX ,DMALL_GAIOUMON_ANIM_INDEX ,DMALL_KAISER_GREYMON_ANIM_INDEX ,DMALL_ROSEMON_ANIM_INDEX ,DMALL_SERAPHIMON_ANIM_INDEX ,DMALL_WAR_GREYMON_ANIM_INDEX
                },
              };
            case DMALL_RIZEGREYMON_X_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 4,
                .animation_indices = {
                  DMALL_CHAOSDRAMON_ANIM_INDEX ,DMALL_GAIOUMON_ANIM_INDEX ,DMALL_OURYUMON_ANIM_INDEX ,DMALL_WAR_GREYMON_ANIM_INDEX
                },
              };
            case DMALL_ROSEMON_BURST_MODE_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMALL_ROSEMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMALL_ROSEMON_X_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = 230400 },
                
                .num_animation_indices = 3,
                .animation_indices = {
                  DMALL_LILITHMON_X_ANIM_INDEX ,DMALL_BELPHEMON_X_ANIM_INDEX ,DMALL_BARBAMON_X_ANIM_INDEX
                },
              };
            case DMALL_RUKAMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_AERO_V_DRAMON_ANIM_INDEX ,DMALL_ANDROMON_ANIM_INDEX ,DMALL_ANGEWOMON_ANIM_INDEX ,DMALL_ANOMALOCARIMON_ANIM_INDEX ,DMALL_ASURAMON_ANIM_INDEX ,DMALL_BAALMON_ANIM_INDEX ,DMALL_BIG_MAMEMON_ANIM_INDEX ,DMALL_CHIMAIRAMON_ANIM_INDEX ,DMALL_CYBERDRAMON_ANIM_INDEX ,DMALL_DURAMON_ANIM_INDEX ,DMALL_GARUDAMON_ANIM_INDEX ,DMALL_HANGYOMON_ANIM_INDEX ,DMALL_JYAGAMON_ANIM_INDEX ,DMALL_MARIN_DEVIMON_ANIM_INDEX ,DMALL_MEGADRAMON_ANIM_INDEX
                },
              };
            case DMALL_RUST_TYRANNOMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMALL_RYUDAMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_DEATH_X_DORUGAMON_ANIM_INDEX ,DMALL_GINRYUMON_ANIM_INDEX ,DMALL_GINRYUMON_ANIM_INDEX ,DMALL_WIZARMON_X_ANIM_INDEX ,DMALL_TAILMON_X_ANIM_INDEX ,DMALL_TYLOMON_X_ANIM_INDEX ,DMALL_OMEKAMON_ANIM_INDEX ,DMALL_PALEDRAMON_ANIM_INDEX ,DMALL_JAZARDMON_ANIM_INDEX ,DMALL_AIRDRAMON_ANIM_INDEX ,DMALL_COELAMON_ANIM_INDEX ,DMALL_DEATH_X_DORUGAMON_ANIM_INDEX ,DMALL_DOKUGUMON_ANIM_INDEX ,DMALL_GEO_GREYMON_ANIM_INDEX ,DMALL_GINRYUMON_ANIM_INDEX
                },
              };
            case DMALL_SABERDRAMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 8,
                .animation_indices = {
                  DMALL_BAALMON_ANIM_INDEX ,DMALL_CYBERDRAMON_ANIM_INDEX ,DMALL_GARUDAMON_ANIM_INDEX ,DMALL_MEGADRAMON_ANIM_INDEX ,DMALL_OKUWAMON_ANIM_INDEX ,DMALL_PUMPMON_ANIM_INDEX ,DMALL_VAMDEMON_ANIM_INDEX ,DMALL_WARU_SEADRAMON_ANIM_INDEX
                },
              };
            case DMALL_SABER_LEOMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMALL_SAGOMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMALL_SAINT_GALGOMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMALL_SAKUYAMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMALL_SAKUYAMON_X_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = 230400 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DMALL_DUKEMON_X_ANIM_INDEX
                },
              };
            case DMALL_SAND_YANMAMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 4,
                .animation_indices = {
                  DMALL_ANOMALOCARIMON_ANIM_INDEX ,DMALL_GIGADRAMON_ANIM_INDEX ,DMALL_OKUWAMON_ANIM_INDEX ,DMALL_TONOSAMA_GEKOMON_ANIM_INDEX
                },
              };
            case DMALL_SANGLOUPMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 10,
                .animation_indices = {
                  DMALL_LUCEMON_FALLDOWN_MODE_ANIM_INDEX ,DMALL_CERBERUMON_X_ANIM_INDEX ,DMALL_SKULL_BALUCHIMON_ANIM_INDEX ,DMALL_ANGEWOMON_ANIM_INDEX ,DMALL_ARCHNEMON_ANIM_INDEX ,DMALL_ASTAMON_ANIM_INDEX ,DMALL_MEPHISMON_ANIM_INDEX ,DMALL_SCORPIOMON_ANIM_INDEX ,DMALL_SKULL_BALUCHIMON_ANIM_INDEX ,DMALL_VAMDEMON_ANIM_INDEX
                },
              };
            case DMALL_SANGOMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 5,
                .animation_indices = {
                  DMALL_SHELLMON_ANIM_INDEX ,DMALL_HOOKMON_ANIM_INDEX ,DMALL_SEADRAMON_ANIM_INDEX ,DMALL_SHELLMON_ANIM_INDEX ,DMALL_TOBIUMON_ANIM_INDEX
                },
              };
            case DMALL_SAVIORHACKMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 6,
                .animation_indices = {
                  DMALL_BOLTMON_ANIM_INDEX ,DMALL_GRIFFOMON_ANIM_INDEX ,DMALL_METAL_GARURUMON_ANIM_INDEX ,DMALL_METAL_SEADRAMON_ANIM_INDEX ,DMALL_PLESIOMON_ANIM_INDEX ,DMALL_SABER_LEOMON_ANIM_INDEX
                },
              };
            case DMALL_SCORPIOMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 7,
                .animation_indices = {
                  DMALL_ANCIENT_BEATMON_ANIM_INDEX ,DMALL_ANCIENT_SPHINXMON_ANIM_INDEX ,DMALL_GRAND_DRACUMON_ANIM_INDEX ,DMALL_HOLYDRAMON_ANIM_INDEX ,DMALL_KUZUHAMON_ANIM_INDEX ,DMALL_LILITHMON_ANIM_INDEX ,DMALL_SERAPHIMON_ANIM_INDEX
                },
              };
            case DMALL_SCUMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_ETEMON_ANIM_INDEX ,DMALL_GREAT_KING_SCUMON_ANIM_INDEX ,DMALL_ETEMON_ANIM_INDEX ,DMALL_CHIMAIRAMON_ANIM_INDEX ,DMALL_AERO_V_DRAMON_ANIM_INDEX ,DMALL_ANOMALOCARIMON_ANIM_INDEX ,DMALL_ASTAMON_ANIM_INDEX ,DMALL_ASURAMON_ANIM_INDEX ,DMALL_ATLUR_KABUTERIMON_RED_ANIM_INDEX ,DMALL_BEOWOLFMON_ANIM_INDEX ,DMALL_BIG_MAMEMON_ANIM_INDEX ,DMALL_BLACK_KING_NUMEMON_ANIM_INDEX ,DMALL_CHIMAIRAMON_ANIM_INDEX ,DMALL_DAGOMON_ANIM_INDEX ,DMALL_DARK_KNIGHTMON_ANIM_INDEX
                },
              };
            case DMALL_SEADRAMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_MAMEMON_ANIM_INDEX ,DMALL_MEGA_SEADRAMON_ANIM_INDEX ,DMALL_WARU_SEADRAMON_ANIM_INDEX ,DMALL_MAMEMON_ANIM_INDEX ,DMALL_AERO_V_DRAMON_ANIM_INDEX ,DMALL_ANDROMON_ANIM_INDEX ,DMALL_ANOMALOCARIMON_ANIM_INDEX ,DMALL_ASURAMON_ANIM_INDEX ,DMALL_BEOWOLFMON_ANIM_INDEX ,DMALL_BIG_MAMEMON_ANIM_INDEX ,DMALL_BLACK_RAPIDMON_ANIM_INDEX ,DMALL_CYBERDRAMON_ANIM_INDEX ,DMALL_DAGOMON_ANIM_INDEX ,DMALL_DARK_KNIGHTMON_ANIM_INDEX ,DMALL_DURAMON_ANIM_INDEX
                },
              };
            case DMALL_SEADRAMON_X_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 13,
                .animation_indices = {
                  DMALL_MEGA_SEADRAMON_X_ANIM_INDEX ,DMALL_MAMETYRAMON_ANIM_INDEX ,DMALL_MAMMON_X_ANIM_INDEX ,DMALL_ANOMALOCARIMON_ANIM_INDEX ,DMALL_BLACK_RAPIDMON_ANIM_INDEX ,DMALL_DAGOMON_ANIM_INDEX ,DMALL_GRADEMON_ANIM_INDEX ,DMALL_HISYARYUMON_ANIM_INDEX ,DMALL_MAMEMON_ANIM_INDEX ,DMALL_MAMETYRAMON_ANIM_INDEX ,DMALL_MEGADRAMON_ANIM_INDEX ,DMALL_MEGA_SEADRAMON_ANIM_INDEX ,DMALL_WARU_SEADRAMON_ANIM_INDEX
                },
              };
            case DMALL_SERAPHIMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMALL_SHADRAMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 12,
                .animation_indices = {
                  DMALL_ANOMALOCARIMON_ANIM_INDEX ,DMALL_ASTAMON_ANIM_INDEX ,DMALL_ATLUR_KABUTERIMON_BLUE_ANIM_INDEX ,DMALL_BAALMON_ANIM_INDEX ,DMALL_BIG_MAMEMON_ANIM_INDEX ,DMALL_DARK_KNIGHTMON_ANIM_INDEX ,DMALL_DURAMON_ANIM_INDEX ,DMALL_HANGYOMON_ANIM_INDEX ,DMALL_PAILDRAMON_ANIM_INDEX ,DMALL_PICCOLOMON_ANIM_INDEX ,DMALL_PUMPMON_ANIM_INDEX ,DMALL_RIZE_GREYMON_ANIM_INDEX
                },
              };
            case DMALL_SHAKOMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_EBIDRAMON_ANIM_INDEX ,DMALL_SHELLMON_ANIM_INDEX ,DMALL_COELAMON_ANIM_INDEX ,DMALL_DORUGAMON_ANIM_INDEX ,DMALL_EBIDRAMON_ANIM_INDEX ,DMALL_GAWAPPAMON_ANIM_INDEX ,DMALL_GEKOMON_ANIM_INDEX ,DMALL_GESOMON_ANIM_INDEX ,DMALL_HOOKMON_ANIM_INDEX ,DMALL_IKKAKUMON_ANIM_INDEX ,DMALL_NUMEMON_ANIM_INDEX ,DMALL_RUKAMON_ANIM_INDEX ,DMALL_SEADRAMON_ANIM_INDEX ,DMALL_SHELLMON_ANIM_INDEX ,DMALL_TOBUCATMON_ANIM_INDEX
                },
              };
            case DMALL_SHAKOMON_X_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_WIZARMON_X_ANIM_INDEX ,DMALL_GINRYUMON_ANIM_INDEX ,DMALL_TAILMON_X_ANIM_INDEX ,DMALL_TYLOMON_X_ANIM_INDEX ,DMALL_OMEKAMON_ANIM_INDEX ,DMALL_PALEDRAMON_ANIM_INDEX ,DMALL_JAZARDMON_ANIM_INDEX ,DMALL_COELAMON_ANIM_INDEX ,DMALL_EBIDRAMON_ANIM_INDEX ,DMALL_GESOMON_ANIM_INDEX ,DMALL_GINRYUMON_ANIM_INDEX ,DMALL_IKKAKUMON_ANIM_INDEX ,DMALL_OMEKAMON_ANIM_INDEX ,DMALL_SEADRAMON_ANIM_INDEX ,DMALL_SHELLMON_ANIM_INDEX
                },
              };
            case DMALL_SHAWUJINMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 4,
                .animation_indices = {
                  DMALL_BARBAMON_ANIM_INDEX ,DMALL_CRANIUMMON_ANIM_INDEX ,DMALL_METAL_GARURUMON_ANIM_INDEX ,DMALL_METAL_SEADRAMON_ANIM_INDEX
                },
              };
            case DMALL_SHEEPMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 2,
                .animation_indices = {
                  DMALL_KAISER_LEOMON_ANIM_INDEX ,DMALL_METAL_TYRANOMON_ANIM_INDEX
                },
              };
            case DMALL_SHELLMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_ANDROMON_ANIM_INDEX ,DMALL_AERO_V_DRAMON_ANIM_INDEX ,DMALL_ANDROMON_ANIM_INDEX ,DMALL_ANOMALOCARIMON_ANIM_INDEX ,DMALL_ASURAMON_ANIM_INDEX ,DMALL_BEOWOLFMON_ANIM_INDEX ,DMALL_BIG_MAMEMON_ANIM_INDEX ,DMALL_BLOSSOMON_ANIM_INDEX ,DMALL_CHIMAIRAMON_ANIM_INDEX ,DMALL_CYBERDRAMON_ANIM_INDEX ,DMALL_DAGOMON_ANIM_INDEX ,DMALL_DARK_KNIGHTMON_ANIM_INDEX ,DMALL_DURAMON_ANIM_INDEX ,DMALL_GARUDAMON_ANIM_INDEX ,DMALL_GERBEMON_ANIM_INDEX
                },
              };
            case DMALL_SHIMA_UNIMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 6,
                .animation_indices = {
                  DMALL_ANDROMON_ANIM_INDEX ,DMALL_ASURAMON_ANIM_INDEX ,DMALL_CYBERDRAMON_ANIM_INDEX ,DMALL_HANGYOMON_ANIM_INDEX ,DMALL_MAMMON_ANIM_INDEX ,DMALL_SKULL_GREYMON_ANIM_INDEX
                },
              };
            case DMALL_SHIN_MONZAEMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMALL_SHOOTMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DMALL_KAZUCHIMON_ANIM_INDEX
                },
              };
            case DMALL_SIESAMON_X_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 12,
                .animation_indices = {
                  DMALL_OMEGA_SHOUTMON_X_ANIM_INDEX ,DMALL_CYBERDRAMON_X_ANIM_INDEX ,DMALL_DORUGUREMON_ANIM_INDEX ,DMALL_GARUDAMON_X_ANIM_INDEX ,DMALL_CANNONBEEMON_ANIM_INDEX ,DMALL_GRADEMON_ANIM_INDEX ,DMALL_MAMEMON_X_ANIM_INDEX ,DMALL_CRYS_PALEDRAMON_ANIM_INDEX ,DMALL_JAZARICHMON_ANIM_INDEX ,DMALL_PUMPMON_ANIM_INDEX ,DMALL_DORUGUREMON_ANIM_INDEX ,DMALL_GRADEMON_ANIM_INDEX
                },
              };
            case DMALL_SIRENMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 4,
                .animation_indices = {
                  DMALL_ANCIENT_MEGATHERIUMON_ANIM_INDEX ,DMALL_ANCIENT_MERMAIMON_ANIM_INDEX ,DMALL_MARIN_ANGEMON_ANIM_INDEX ,DMALL_REGALECUSMON_ANIM_INDEX
                },
              };
            case DMALL_SISTERMON_BLANC_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 5,
                .animation_indices = {
                  DMALL_RHINOMON_X_ANIM_INDEX ,DMALL_DAMEMON_ANIM_INDEX ,DMALL_DAMEMON_ANIM_INDEX ,DMALL_GALGOMON_ANIM_INDEX ,DMALL_LEKISMON_ANIM_INDEX
                },
              };
            case DMALL_SKULL_BALUCHIMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 13,
                .animation_indices = {
                  DMALL_SAKUYAMON_X_ANIM_INDEX ,DMALL_VALDURMON_ANIM_INDEX ,DMALL_SLEIPMON_X_ANIM_INDEX ,DMALL_PLATINUM_NUMEMON_ANIM_INDEX ,DMALL_ANCIENT_SPHINXMON_ANIM_INDEX ,DMALL_DINOREXMON_ANIM_INDEX ,DMALL_DINOTIGERMON_ANIM_INDEX ,DMALL_GRIFFOMON_ANIM_INDEX ,DMALL_OURYUMON_ANIM_INDEX ,DMALL_PLATINUM_NUMEMON_ANIM_INDEX ,DMALL_SKULL_MAMMON_ANIM_INDEX ,DMALL_ULTIMATE_BRACHIMON_ANIM_INDEX ,DMALL_VALDURMON_ANIM_INDEX
                },
              };
            case DMALL_SKULL_GREYMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_MUGENDRAMON_ANIM_INDEX ,DMALL_SKULL_MAMMON_ANIM_INDEX ,DMALL_BLACK_WAR_GREYMON_ANIM_INDEX ,DMALL_CHAOSDRAMON_ANIM_INDEX ,DMALL_CRANIUMMON_ANIM_INDEX ,DMALL_DEMON_ANIM_INDEX ,DMALL_GAIOUMON_ANIM_INDEX ,DMALL_MEGIDRAMON_ANIM_INDEX ,DMALL_METAL_ETEMON_ANIM_INDEX ,DMALL_MILLENNIUMON_ANIM_INDEX ,DMALL_MUGENDRAMON_ANIM_INDEX ,DMALL_OMEGAMON_ZWART_ANIM_INDEX ,DMALL_PIEMON_ANIM_INDEX ,DMALL_PINOCHIMON_ANIM_INDEX ,DMALL_PUKUMON_ANIM_INDEX
                },
              };
            case DMALL_SKULLKNIGHTMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 5,
                .animation_indices = {
                  DMALL_DARK_KNIGHTMON_ANIM_INDEX ,DMALL_ANDROMON_ANIM_INDEX ,DMALL_ASURAMON_ANIM_INDEX ,DMALL_DARK_KNIGHTMON_ANIM_INDEX ,DMALL_MARIN_DEVIMON_ANIM_INDEX
                },
              };
            case DMALL_SKULL_MAMMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMALL_SKULL_MAMMON_X_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = 230400 },
                
                .num_animation_indices = 2,
                .animation_indices = {
                  DMALL_LEVIAMON_X_ANIM_INDEX ,DMALL_BARBAMON_X_ANIM_INDEX
                },
              };
            case DMALL_SLEIPMON_X_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = 230400 },
                
                .num_animation_indices = 2,
                .animation_indices = {
                  DMALL_MINERVAMON_X_ANIM_INDEX ,DMALL_ALPHAMON_ANIM_INDEX
                },
              };
            case DMALL_SOLARMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_CLOCKMON_ANIM_INDEX ,DMALL_GUARDROMON_GOLD_ANIM_INDEX ,DMALL_BIRDRAMON_ANIM_INDEX ,DMALL_CLOCKMON_ANIM_INDEX ,DMALL_GEREMON_ANIM_INDEX ,DMALL_GOLD_NUMEMON_ANIM_INDEX ,DMALL_GUARDROMON_ANIM_INDEX ,DMALL_GUARDROMON_GOLD_ANIM_INDEX ,DMALL_GURURUMON_ANIM_INDEX ,DMALL_MERAMON_ANIM_INDEX ,DMALL_NUMEMON_ANIM_INDEX ,DMALL_RED_VEGIMON_ANIM_INDEX ,DMALL_SCUMON_ANIM_INDEX ,DMALL_STARMON_ANIM_INDEX ,DMALL_TURUIEMON_ANIM_INDEX
                },
              };
            case DMALL_SORCERYMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 8,
                .animation_indices = {
                  DMALL_ASURAMON_ANIM_INDEX ,DMALL_BLUE_MERAMON_ANIM_INDEX ,DMALL_DAGOMON_ANIM_INDEX ,DMALL_HOLY_ANGEMON_ANIM_INDEX ,DMALL_JYUREIMON_ANIM_INDEX ,DMALL_PANJYAMON_ANIM_INDEX ,DMALL_PICCOLOMON_ANIM_INDEX ,DMALL_SHAWUJINMON_ANIM_INDEX
                },
              };
            case DMALL_SOULMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 2,
                .animation_indices = {
                  DMALL_METAL_GREYMON_VIRUS_ANIM_INDEX ,DMALL_VAMDEMON_ANIM_INDEX
                },
              };
            case DMALL_STARMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_SUPERSTARMON_ANIM_INDEX ,DMALL_AERO_V_DRAMON_ANIM_INDEX ,DMALL_ANDROMON_ANIM_INDEX ,DMALL_ANGEWOMON_ANIM_INDEX ,DMALL_ANOMALOCARIMON_ANIM_INDEX ,DMALL_ASURAMON_ANIM_INDEX ,DMALL_BEOWOLFMON_ANIM_INDEX ,DMALL_BIG_MAMEMON_ANIM_INDEX ,DMALL_BLOSSOMON_ANIM_INDEX ,DMALL_CRESCEMON_ANIM_INDEX ,DMALL_CYBERDRAMON_ANIM_INDEX ,DMALL_DAGOMON_ANIM_INDEX ,DMALL_DARK_KNIGHTMON_ANIM_INDEX ,DMALL_DARK_SUPERSTARMON_ANIM_INDEX ,DMALL_DIGITAMAMON_ANIM_INDEX
                },
              };
            case DMALL_STIFFILMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 11,
                .animation_indices = {
                  DMALL_RASENMON_ANIM_INDEX ,DMALL_BLACK_WAR_GREYMON_X_ANIM_INDEX ,DMALL_GRANDIS_KUWAGAMON_ANIM_INDEX ,DMALL_GIGA_SEADRAMON_ANIM_INDEX ,DMALL_RASENMON_FURY_MODE_ANIM_INDEX ,DMALL_BAGRAMON_ANIM_INDEX ,DMALL_ROSEMON_X_ANIM_INDEX ,DMALL_BAGRAMON_ANIM_INDEX ,DMALL_GIGA_SEADRAMON_ANIM_INDEX ,DMALL_GRANDIS_KUWAGAMON_ANIM_INDEX ,DMALL_RASENMON_ANIM_INDEX
                },
              };
            case DMALL_SUBMARINMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 10,
                .animation_indices = {
                  DMALL_ARCHNEMON_ANIM_INDEX ,DMALL_DELUMON_ANIM_INDEX ,DMALL_GUSOKUMON_ANIM_INDEX ,DMALL_MARIN_DEVIMON_ANIM_INDEX ,DMALL_MEGA_SEADRAMON_ANIM_INDEX ,DMALL_MERMAIMON_ANIM_INDEX ,DMALL_PAILDRAMON_ANIM_INDEX ,DMALL_PICCOLOMON_ANIM_INDEX ,DMALL_PIRANIMON_ANIM_INDEX ,DMALL_WARU_SEADRAMON_ANIM_INDEX
                },
              };
            case DMALL_SUNAMON_ANIM_INDEX:
              return {
                // Stage: Baby I
                .conditions = { .next_evolution_time_sec = 600 },
                
                .num_animation_indices = 2,
                .animation_indices = {
                  DMALL_GOROMON_ANIM_INDEX ,DMALL_GOROMON_ANIM_INDEX
                },
              };
            case DMALL_SUNARIZAMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 4,
                .animation_indices = {
                  DMALL_BABOONGAMON_ANIM_INDEX ,DMALL_GOKIMON_ANIM_INDEX ,DMALL_TOGEMON_ANIM_INDEX ,DMALL_TORTAMON_ANIM_INDEX
                },
              };
            case DMALL_SUNFLOWMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 14,
                .animation_indices = {
                  DMALL_LILAMON_ANIM_INDEX ,DMALL_ANGEWOMON_ANIM_INDEX ,DMALL_ARCHNEMON_ANIM_INDEX ,DMALL_ATLUR_KABUTERIMON_RED_ANIM_INDEX ,DMALL_BLOSSOMON_ANIM_INDEX ,DMALL_CANNONBEEMON_ANIM_INDEX ,DMALL_GERBEMON_ANIM_INDEX ,DMALL_HOLY_ANGEMON_ANIM_INDEX ,DMALL_JYUREIMON_ANIM_INDEX ,DMALL_LILAMON_ANIM_INDEX ,DMALL_LILIMON_ANIM_INDEX ,DMALL_MACH_GAOGAMON_ANIM_INDEX ,DMALL_MAMEMON_ANIM_INDEX ,DMALL_RIZE_GREYMON_ANIM_INDEX
                },
              };
            case DMALL_SUNMON_ANIM_INDEX:
              return {
                // Stage: Baby II
                .conditions = { .next_evolution_time_sec = 43200 },
                
                .num_animation_indices = 4,
                .animation_indices = {
                  DMALL_CORONAMON_ANIM_INDEX ,DMALL_CORONAMON_ANIM_INDEX ,DMALL_GUILMON_ANIM_INDEX ,DMALL_PLOTMON_ANIM_INDEX
                },
              };
            case DMALL_SUPERSTARMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 6,
                .animation_indices = {
                  DMALL_GANKOOMON_ANIM_INDEX ,DMALL_KAISER_GREYMON_ANIM_INDEX ,DMALL_MARIN_ANGEMON_ANIM_INDEX ,DMALL_PLATINUM_NUMEMON_ANIM_INDEX ,DMALL_PRINCE_MAMEMON_ANIM_INDEX ,DMALL_SUSANOOMON_ANIM_INDEX
                },
              };
            case DMALL_SUSANOOMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMALL_SWIMMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 6,
                .animation_indices = {
                  DMALL_COELAMON_ANIM_INDEX ,DMALL_IGAMON_ANIM_INDEX ,DMALL_NUMEMON_ANIM_INDEX ,DMALL_TOBIUMON_ANIM_INDEX ,DMALL_TYRANOMON_ANIM_INDEX ,DMALL_WHAMON_ANIM_INDEX
                },
              };
            case DMALL_TAILMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_ANGEWOMON_ANIM_INDEX ,DMALL_DARK_KNIGHTMON_ANIM_INDEX ,DMALL_AERO_V_DRAMON_ANIM_INDEX ,DMALL_ANDROMON_ANIM_INDEX ,DMALL_ANGEWOMON_ANIM_INDEX ,DMALL_ASURAMON_ANIM_INDEX ,DMALL_ATLUR_KABUTERIMON_BLUE_ANIM_INDEX ,DMALL_ATLUR_KABUTERIMON_RED_ANIM_INDEX ,DMALL_BAALMON_ANIM_INDEX ,DMALL_BIG_MAMEMON_ANIM_INDEX ,DMALL_CYBERDRAMON_ANIM_INDEX ,DMALL_DARK_KNIGHTMON_ANIM_INDEX ,DMALL_DURAMON_ANIM_INDEX ,DMALL_GARUDAMON_ANIM_INDEX ,DMALL_HANGYOMON_ANIM_INDEX
                },
              };
            case DMALL_TAILMON_X_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_ANGEWOMON_X_ANIM_INDEX ,DMALL_MONZAEMON_X_ANIM_INDEX ,DMALL_ANOMALOCARIMON_X_ANIM_INDEX ,DMALL_GRADEMON_ANIM_INDEX ,DMALL_MAMEMON_X_ANIM_INDEX ,DMALL_CRYS_PALEDRAMON_ANIM_INDEX ,DMALL_JAZARICHMON_ANIM_INDEX ,DMALL_PUMPMON_ANIM_INDEX ,DMALL_ANGEWOMON_ANIM_INDEX ,DMALL_ATLUR_KABUTERIMON_RED_ANIM_INDEX ,DMALL_GRADEMON_ANIM_INDEX ,DMALL_HOLY_ANGEMON_ANIM_INDEX ,DMALL_JYAGAMON_ANIM_INDEX ,DMALL_LILAMON_ANIM_INDEX ,DMALL_WERE_GARURUMON_ANIM_INDEX
                },
              };
            case DMALL_TANEMON_ANIM_INDEX:
              return {
                // Stage: Baby II
                .conditions = { .next_evolution_time_sec = 43200 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_LALAMON_ANIM_INDEX ,DMALL_PALMON_ANIM_INDEX ,DMALL_PIYOMON_ANIM_INDEX ,DMALL_PALMON_ANIM_INDEX ,DMALL_ALRAUMON_ANIM_INDEX ,DMALL_FLORAMON_ANIM_INDEX ,DMALL_FUNBEEMON_ANIM_INDEX ,DMALL_KUNEMON_ANIM_INDEX ,DMALL_LALAMON_ANIM_INDEX ,DMALL_MUSHMON_ANIM_INDEX ,DMALL_PALMON_ANIM_INDEX ,DMALL_PICO_DEVIMON_ANIM_INDEX ,DMALL_PIYOMON_ANIM_INDEX ,DMALL_RENAMON_ANIM_INDEX ,DMALL_TINKERMON_ANIM_INDEX
                },
              };
            case DMALL_TANKMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_AERO_V_DRAMON_ANIM_INDEX ,DMALL_ANDROMON_ANIM_INDEX ,DMALL_ANOMALOCARIMON_ANIM_INDEX ,DMALL_ASURAMON_ANIM_INDEX ,DMALL_BEOWOLFMON_ANIM_INDEX ,DMALL_BIG_MAMEMON_ANIM_INDEX ,DMALL_CANNONBEEMON_ANIM_INDEX ,DMALL_CYBERDRAMON_ANIM_INDEX ,DMALL_DAGOMON_ANIM_INDEX ,DMALL_DARK_KNIGHTMON_ANIM_INDEX ,DMALL_DEATH_MERAMON_ANIM_INDEX ,DMALL_DURAMON_ANIM_INDEX ,DMALL_GERBEMON_ANIM_INDEX ,DMALL_GARUDAMON_ANIM_INDEX ,DMALL_GIGADRAMON_ANIM_INDEX
                },
              };
            case DMALL_TARGETMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_AERO_V_DRAMON_ANIM_INDEX ,DMALL_ANOMALOCARIMON_ANIM_INDEX ,DMALL_ASTAMON_ANIM_INDEX ,DMALL_ASURAMON_ANIM_INDEX ,DMALL_BEOWOLFMON_ANIM_INDEX ,DMALL_BIG_MAMEMON_ANIM_INDEX ,DMALL_DAGOMON_ANIM_INDEX ,DMALL_DARK_KNIGHTMON_ANIM_INDEX ,DMALL_DURAMON_ANIM_INDEX ,DMALL_ETEMON_ANIM_INDEX ,DMALL_GERBEMON_ANIM_INDEX ,DMALL_GREAT_KING_SCUMON_ANIM_INDEX ,DMALL_HANGYOMON_ANIM_INDEX ,DMALL_MEGADRAMON_ANIM_INDEX ,DMALL_MEGALO_GROWMON_ANIM_INDEX
                },
              };
            case DMALL_TEKKAMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 7,
                .animation_indices = {
                  DMALL_BOLTMON_ANIM_INDEX ,DMALL_GOKUMON_ANIM_INDEX ,DMALL_HERAKLE_KABUTERIMON_ANIM_INDEX ,DMALL_HI_ANDROMON_ANIM_INDEX ,DMALL_PIEMON_ANIM_INDEX ,DMALL_PINOCHIMON_ANIM_INDEX ,DMALL_PRINCE_MAMEMON_ANIM_INDEX
                },
              };
            case DMALL_TENTOMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_KABUTERIMON_ANIM_INDEX ,DMALL_AIRDRAMON_ANIM_INDEX ,DMALL_CENTALMON_ANIM_INDEX ,DMALL_CYCLOMON_ANIM_INDEX ,DMALL_DINOHUMON_ANIM_INDEX ,DMALL_DOBERMON_ANIM_INDEX ,DMALL_DOKUGUMON_ANIM_INDEX ,DMALL_GEKOMON_ANIM_INDEX ,DMALL_GEREMON_ANIM_INDEX ,DMALL_GOKIMON_ANIM_INDEX ,DMALL_GUARDROMON_ANIM_INDEX ,DMALL_KABUTERIMON_ANIM_INDEX ,DMALL_KUWAGAMON_ANIM_INDEX ,DMALL_MEICOOMON_ANIM_INDEX ,DMALL_MONOCHROMON_ANIM_INDEX
                },
              };
            case DMALL_TERRIERMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_GALGOMON_ANIM_INDEX ,DMALL_ANGEMON_ANIM_INDEX ,DMALL_BLACK_GALGOMON_ANIM_INDEX ,DMALL_BLACK_TAILMON_ANIM_INDEX ,DMALL_CENTALMON_ANIM_INDEX ,DMALL_CLOCKMON_ANIM_INDEX ,DMALL_DEVIMON_ANIM_INDEX ,DMALL_DINOHUMON_ANIM_INDEX ,DMALL_DOGMON_ANIM_INDEX ,DMALL_EBIDRAMON_ANIM_INDEX ,DMALL_GALGOMON_ANIM_INDEX ,DMALL_GEREMON_ANIM_INDEX ,DMALL_GREYMON_ANIM_INDEX ,DMALL_GREYMON_BLUE_ANIM_INDEX ,DMALL_GROWMON_ANIM_INDEX
                },
              };
            case DMALL_TERRIERMON_X_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 12,
                .animation_indices = {
                  DMALL_SIESAMON_X_ANIM_INDEX ,DMALL_MERAMON_X_ANIM_INDEX ,DMALL_DORUGAMON_ANIM_INDEX ,DMALL_PTERANOMON_X_ANIM_INDEX ,DMALL_TOGEMON_X_ANIM_INDEX ,DMALL_OMEKAMON_ANIM_INDEX ,DMALL_PALEDRAMON_ANIM_INDEX ,DMALL_JAZARDMON_ANIM_INDEX ,DMALL_BLACK_GALGOMON_ANIM_INDEX ,DMALL_DORUGAMON_ANIM_INDEX ,DMALL_GALGOMON_ANIM_INDEX ,DMALL_TURUIEMON_ANIM_INDEX
                },
              };
            case DMALL_THUNDERBALLMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_AERO_V_DRAMON_ANIM_INDEX ,DMALL_ANDROMON_ANIM_INDEX ,DMALL_ANOMALOCARIMON_ANIM_INDEX ,DMALL_ASURAMON_ANIM_INDEX ,DMALL_BEOWOLFMON_ANIM_INDEX ,DMALL_BIG_MAMEMON_ANIM_INDEX ,DMALL_BLACK_RAPIDMON_ANIM_INDEX ,DMALL_BOUTMON_ANIM_INDEX ,DMALL_CYBERDRAMON_ANIM_INDEX ,DMALL_DAGOMON_ANIM_INDEX ,DMALL_DARK_KNIGHTMON_ANIM_INDEX ,DMALL_DURAMON_ANIM_INDEX ,DMALL_GARUDAMON_ANIM_INDEX ,DMALL_GERBEMON_ANIM_INDEX ,DMALL_GIROMON_ANIM_INDEX
                },
              };
            case DMALL_TIA_LUDOMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 5,
                .animation_indices = {
                  DMALL_RAIJI_LUDOMON_ANIM_INDEX ,DMALL_DIGITAMAMON_ANIM_INDEX ,DMALL_MANTICOREMON_ANIM_INDEX ,DMALL_PICCOLOMON_ANIM_INDEX ,DMALL_RAIJI_LUDOMON_ANIM_INDEX
                },
              };
            case DMALL_TIGER_VESPAMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = 230400 },
                
                .num_animation_indices = 7,
                .animation_indices = {
                  DMALL_MAGNAMON_X_ANIM_INDEX ,DMALL_GANKOOMON_X_ANIM_INDEX ,DMALL_DYNASMON_X_ANIM_INDEX ,DMALL_CRANIUMMON_X_ANIM_INDEX ,DMALL_DUKEMON_X_ANIM_INDEX ,DMALL_ALPHAMON_OURYUKEN_ANIM_INDEX ,DMALL_JESMON_GX_ANIM_INDEX
                },
              };
            case DMALL_TINKERMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 3,
                .animation_indices = {
                  DMALL_PARASAURMON_ANIM_INDEX ,DMALL_VEGIMON_ANIM_INDEX ,DMALL_ZASSOUMON_ANIM_INDEX
                },
              };
            case DMALL_TITAMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMALL_TOBIUMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 7,
                .animation_indices = {
                  DMALL_DAGOMON_ANIM_INDEX ,DMALL_GUSOKUMON_ANIM_INDEX ,DMALL_MARIN_CHIMAIRAMON_ANIM_INDEX ,DMALL_MEGA_SEADRAMON_ANIM_INDEX ,DMALL_MERMAIMON_ANIM_INDEX ,DMALL_PIRANIMON_ANIM_INDEX ,DMALL_WARU_SEADRAMON_ANIM_INDEX
                },
              };
            case DMALL_TOBUCATMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 6,
                .animation_indices = {
                  DMALL_SKULL_BALUCHIMON_ANIM_INDEX ,DMALL_WERE_GARURUMON_X_ANIM_INDEX ,DMALL_YATAGARAMON_ANIM_INDEX ,DMALL_HISYARYUMON_ANIM_INDEX ,DMALL_MAMETYRAMON_ANIM_INDEX ,DMALL_SKULL_BALUCHIMON_ANIM_INDEX
                },
              };
            case DMALL_TOGEMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_LILIMON_ANIM_INDEX ,DMALL_AERO_V_DRAMON_ANIM_INDEX ,DMALL_ANDROMON_ANIM_INDEX ,DMALL_ANOMALOCARIMON_ANIM_INDEX ,DMALL_ASURAMON_ANIM_INDEX ,DMALL_BEOWOLFMON_ANIM_INDEX ,DMALL_BIG_MAMEMON_ANIM_INDEX ,DMALL_BLOSSOMON_ANIM_INDEX ,DMALL_CYBERDRAMON_ANIM_INDEX ,DMALL_DAGOMON_ANIM_INDEX ,DMALL_DARK_KNIGHTMON_ANIM_INDEX ,DMALL_DELUMON_ANIM_INDEX ,DMALL_DURAMON_ANIM_INDEX ,DMALL_GARUDAMON_ANIM_INDEX ,DMALL_GERBEMON_ANIM_INDEX
                },
              };
            case DMALL_TOGEMON_X_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_OMEGA_SHOUTMON_X_ANIM_INDEX ,DMALL_CYBERDRAMON_X_ANIM_INDEX ,DMALL_DORUGUREMON_ANIM_INDEX ,DMALL_GARUDAMON_X_ANIM_INDEX ,DMALL_CANNONBEEMON_ANIM_INDEX ,DMALL_GRADEMON_ANIM_INDEX ,DMALL_MAMEMON_X_ANIM_INDEX ,DMALL_CRYS_PALEDRAMON_ANIM_INDEX ,DMALL_JAZARICHMON_ANIM_INDEX ,DMALL_PUMPMON_ANIM_INDEX ,DMALL_BLOSSOMON_ANIM_INDEX ,DMALL_CANNONBEEMON_ANIM_INDEX ,DMALL_DORUGUREMON_ANIM_INDEX ,DMALL_GARUDAMON_ANIM_INDEX ,DMALL_GERBEMON_ANIM_INDEX
                },
              };
            case DMALL_TOKOMON_X_ANIM_INDEX:
              return {
                // Stage: Baby II
                .conditions = { .next_evolution_time_sec = 43200 },
                
                .num_animation_indices = 8,
                .animation_indices = {
                  DMALL_RENAMON_X_ANIM_INDEX ,DMALL_AGUMON_X_ANIM_INDEX ,DMALL_HERISSMON_ANIM_INDEX ,DMALL_DRACOMON_X_ANIM_INDEX ,DMALL_GABUMON_X_ANIM_INDEX ,DMALL_SISTERMON_BLANC_ANIM_INDEX ,DMALL_HERISSMON_ANIM_INDEX ,DMALL_SISTERMON_BLANC_ANIM_INDEX
                },
              };
            case DMALL_TONOSAMA_GEKOMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 11,
                .animation_indices = {
                  DMALL_DARKDRAMON_ANIM_INDEX ,DMALL_DEMON_ANIM_INDEX ,DMALL_GIGA_SEADRAMON_ANIM_INDEX ,DMALL_KING_ETEMON_ANIM_INDEX ,DMALL_LEVIAMON_ANIM_INDEX ,DMALL_METAL_ETEMON_ANIM_INDEX ,DMALL_PIEMON_ANIM_INDEX ,DMALL_PINOCHIMON_ANIM_INDEX ,DMALL_PLESIOMON_ANIM_INDEX ,DMALL_PUKUMON_ANIM_INDEX ,DMALL_VENOM_VAMDEMON_ANIM_INDEX
                },
              };
            case DMALL_TORIKARA_BALLMON_ANIM_INDEX:
              return {
                // Stage: Baby II
                .conditions = { .next_evolution_time_sec = 43200 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMALL_TORTAMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_AERO_V_DRAMON_ANIM_INDEX ,DMALL_ANDROMON_ANIM_INDEX ,DMALL_ANGEWOMON_ANIM_INDEX ,DMALL_ASURAMON_ANIM_INDEX ,DMALL_ATLUR_KABUTERIMON_BLUE_ANIM_INDEX ,DMALL_BAALMON_ANIM_INDEX ,DMALL_BIG_MAMEMON_ANIM_INDEX ,DMALL_CYBERDRAMON_ANIM_INDEX ,DMALL_DURAMON_ANIM_INDEX ,DMALL_GARUDAMON_ANIM_INDEX ,DMALL_GOGMAMON_ANIM_INDEX ,DMALL_HANGYOMON_ANIM_INDEX ,DMALL_HOLY_ANGEMON_ANIM_INDEX ,DMALL_JYAGAMON_ANIM_INDEX ,DMALL_MEGADRAMON_ANIM_INDEX
                },
              };
            case DMALL_TOYAGUMON_BLACK_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_DEVIMON_ANIM_INDEX ,DMALL_FUGAMON_ANIM_INDEX ,DMALL_GARURUMON_BLACK_ANIM_INDEX ,DMALL_GEO_GREYMON_ANIM_INDEX ,DMALL_GEREMON_ANIM_INDEX ,DMALL_GREYMON_ANIM_INDEX ,DMALL_GREYMON_BLUE_ANIM_INDEX ,DMALL_GUARDROMON_ANIM_INDEX ,DMALL_MECHANORIMON_ANIM_INDEX ,DMALL_NUMEMON_ANIM_INDEX ,DMALL_RAPTORDRAMON_ANIM_INDEX ,DMALL_SCUMON_ANIM_INDEX ,DMALL_STARMON_ANIM_INDEX ,DMALL_TANKMON_ANIM_INDEX ,DMALL_THUNDERBALLMON_ANIM_INDEX
                },
              };
            case DMALL_TOYAGUMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_CLOCKMON_ANIM_INDEX ,DMALL_DEVIMON_ANIM_INDEX ,DMALL_GALGOMON_ANIM_INDEX ,DMALL_GAOGAMON_ANIM_INDEX ,DMALL_GARURUMON_BLACK_ANIM_INDEX ,DMALL_GAWAPPAMON_ANIM_INDEX ,DMALL_GEO_GREYMON_ANIM_INDEX ,DMALL_GREYMON_ANIM_INDEX ,DMALL_GREYMON_BLUE_ANIM_INDEX ,DMALL_GROWMON_ORANGE_ANIM_INDEX ,DMALL_GUARDROMON_ANIM_INDEX ,DMALL_GUARDROMON_GOLD_ANIM_INDEX ,DMALL_LEOMON_ANIM_INDEX ,DMALL_MECHANORIMON_ANIM_INDEX ,DMALL_NUMEMON_ANIM_INDEX
                },
              };
            case DMALL_TRICERAMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_ANCIENT_SPHINXMON_ANIM_INDEX ,DMALL_BOLTMON_ANIM_INDEX ,DMALL_DARKDRAMON_ANIM_INDEX ,DMALL_DINOREXMON_ANIM_INDEX ,DMALL_DUKEMON_ANIM_INDEX ,DMALL_GRANDIS_KUWAGAMON_ANIM_INDEX ,DMALL_GRIFFOMON_ANIM_INDEX ,DMALL_HERAKLE_KABUTERIMON_ANIM_INDEX ,DMALL_METAL_GARURUMON_ANIM_INDEX ,DMALL_METAL_ETEMON_ANIM_INDEX ,DMALL_METAL_SEADRAMON_ANIM_INDEX ,DMALL_MUGENDRAMON_ANIM_INDEX ,DMALL_PLESIOMON_ANIM_INDEX ,DMALL_SABER_LEOMON_ANIM_INDEX ,DMALL_SAINT_GALGOMON_ANIM_INDEX
                },
              };
            case DMALL_TRICERAMON_X_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 13,
                .animation_indices = {
                  DMALL_CHAOSDRAMON_X_ANIM_INDEX ,DMALL_PRINCE_MAMEMON_X_ANIM_INDEX ,DMALL_SKULL_MAMMON_X_ANIM_INDEX ,DMALL_METAL_PIRANIMON_ANIM_INDEX ,DMALL_DINOREXMON_ANIM_INDEX ,DMALL_DINOTIGERMON_ANIM_INDEX ,DMALL_GRANDIS_KUWAGAMON_ANIM_INDEX ,DMALL_METAL_PIRANIMON_ANIM_INDEX ,DMALL_OURYUMON_ANIM_INDEX ,DMALL_ROSEMON_ANIM_INDEX ,DMALL_SABER_LEOMON_ANIM_INDEX ,DMALL_ULTIMATE_BRACHIMON_ANIM_INDEX ,DMALL_VALDURMON_ANIM_INDEX
                },
              };
            case DMALL_TROOPMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DMALL_DARK_KNIGHTMON_ANIM_INDEX
                },
              };
            case DMALL_TSUBUMON_ANIM_INDEX:
              return {
                // Stage: Baby I
                .conditions = { .next_evolution_time_sec = 600 },
                
                .num_animation_indices = 2,
                .animation_indices = {
                  DMALL_UPAMON_ANIM_INDEX ,DMALL_UPAMON_ANIM_INDEX
                },
              };
            case DMALL_TSUCHIDARUMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 5,
                .animation_indices = {
                  DMALL_INSEKIMON_ANIM_INDEX ,DMALL_JYAGAMON_ANIM_INDEX ,DMALL_PANDAMON_ANIM_INDEX ,DMALL_PUMPMON_ANIM_INDEX ,DMALL_TEKKAMON_ANIM_INDEX
                },
              };
            case DMALL_TSUMEMON_ANIM_INDEX:
              return {
                // Stage: Baby II
                .conditions = { .next_evolution_time_sec = 43200 },
                
                .num_animation_indices = 7,
                .animation_indices = {
                  DMALL_KERAMON_ANIM_INDEX ,DMALL_KERAMON_X_ANIM_INDEX ,DMALL_AGUMON_BLACK_ANIM_INDEX ,DMALL_DRACUMON_ANIM_INDEX ,DMALL_GAZIMON_ANIM_INDEX ,DMALL_KERAMON_ANIM_INDEX ,DMALL_PICO_DEVIMON_ANIM_INDEX
                },
              };
            case DMALL_TSUNOMON_ANIM_INDEX:
              return {
                // Stage: Baby II
                .conditions = { .next_evolution_time_sec = 43200 },
                
                .num_animation_indices = 14,
                .animation_indices = {
                  DMALL_ELECMON_ANIM_INDEX ,DMALL_BLUCOMON_ANIM_INDEX ,DMALL_DRACUMON_ANIM_INDEX ,DMALL_ELECMON_ANIM_INDEX ,DMALL_GAOMON_ANIM_INDEX ,DMALL_GOMAMON_ANIM_INDEX ,DMALL_HAGURUMON_ANIM_INDEX ,DMALL_KOEMON_ANIM_INDEX ,DMALL_KUNEMON_ANIM_INDEX ,DMALL_PENMON_ANIM_INDEX ,DMALL_PICO_DEVIMON_ANIM_INDEX ,DMALL_RYUDAMON_ANIM_INDEX ,DMALL_SHAKOMON_ANIM_INDEX ,DMALL_V_MON_ANIM_INDEX
                },
              };
            case DMALL_TUNOMON_ANIM_INDEX:
              return {
                // Stage: Baby II
                .conditions = { .next_evolution_time_sec = 43200 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_ELECMON_ANIM_INDEX ,DMALL_ELECMON_ANIM_INDEX ,DMALL_BLUCOMON_ANIM_INDEX ,DMALL_DRACUMON_ANIM_INDEX ,DMALL_ELECMON_ANIM_INDEX ,DMALL_GAOMON_ANIM_INDEX ,DMALL_GOMAMON_ANIM_INDEX ,DMALL_HAGURUMON_ANIM_INDEX ,DMALL_KOEMON_ANIM_INDEX ,DMALL_KUNEMON_ANIM_INDEX ,DMALL_PENMON_ANIM_INDEX ,DMALL_PICO_DEVIMON_ANIM_INDEX ,DMALL_RYUDAMON_ANIM_INDEX ,DMALL_SHAKOMON_ANIM_INDEX ,DMALL_V_MON_ANIM_INDEX
                },
              };
            case DMALL_TURUIEMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 6,
                .animation_indices = {
                  DMALL_CYBERDRAMON_ANIM_INDEX ,DMALL_HOLY_ANGEMON_ANIM_INDEX ,DMALL_KNIGHTMON_ANIM_INDEX ,DMALL_MEGADRAMON_ANIM_INDEX ,DMALL_MONZAEMON_ANIM_INDEX ,DMALL_WERE_GARURUMON_ANIM_INDEX
                },
              };
            case DMALL_TYLOMON_X_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_ANOMALOCARIMON_X_ANIM_INDEX ,DMALL_MONZAEMON_X_ANIM_INDEX ,DMALL_ANGEWOMON_X_ANIM_INDEX ,DMALL_GRADEMON_ANIM_INDEX ,DMALL_MAMEMON_X_ANIM_INDEX ,DMALL_CRYS_PALEDRAMON_ANIM_INDEX ,DMALL_JAZARICHMON_ANIM_INDEX ,DMALL_PUMPMON_ANIM_INDEX ,DMALL_BIG_MAMEMON_ANIM_INDEX ,DMALL_BLOSSOMON_ANIM_INDEX ,DMALL_ETEMON_ANIM_INDEX ,DMALL_GIGADRAMON_ANIM_INDEX ,DMALL_MARIN_DEVIMON_ANIM_INDEX ,DMALL_MEGA_SEADRAMON_ANIM_INDEX ,DMALL_MERMAIMON_ANIM_INDEX
                },
              };
            case DMALL_TYRANNOMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_METAL_TYRANOMON_ANIM_INDEX ,DMALL_SKULL_GREYMON_ANIM_INDEX ,DMALL_AERO_V_DRAMON_ANIM_INDEX ,DMALL_ANDROMON_ANIM_INDEX ,DMALL_ANGEWOMON_ANIM_INDEX ,DMALL_ANOMALOCARIMON_ANIM_INDEX ,DMALL_ASURAMON_ANIM_INDEX ,DMALL_BEOWOLFMON_ANIM_INDEX ,DMALL_BIG_MAMEMON_ANIM_INDEX ,DMALL_CYBERDRAMON_ANIM_INDEX ,DMALL_DAGOMON_ANIM_INDEX ,DMALL_DARK_KNIGHTMON_ANIM_INDEX ,DMALL_DEATH_MERAMON_ANIM_INDEX ,DMALL_DELUMON_ANIM_INDEX ,DMALL_DORUGUREMON_ANIM_INDEX
                },
              };
            case DMALL_TYRANNOMON_X_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMALL_TYRANOMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_METAL_TYRANOMON_ANIM_INDEX ,DMALL_SKULL_GREYMON_ANIM_INDEX ,DMALL_MAMEMON_ANIM_INDEX ,DMALL_AERO_V_DRAMON_ANIM_INDEX ,DMALL_ANDROMON_ANIM_INDEX ,DMALL_ANGEWOMON_ANIM_INDEX ,DMALL_ANOMALOCARIMON_ANIM_INDEX ,DMALL_ASURAMON_ANIM_INDEX ,DMALL_BEOWOLFMON_ANIM_INDEX ,DMALL_BIG_MAMEMON_ANIM_INDEX ,DMALL_CYBERDRAMON_ANIM_INDEX ,DMALL_DAGOMON_ANIM_INDEX ,DMALL_DARK_KNIGHTMON_ANIM_INDEX ,DMALL_DEATH_MERAMON_ANIM_INDEX ,DMALL_DELUMON_ANIM_INDEX
                },
              };
            case DMALL_TYRANOMON_X_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 2,
                .animation_indices = {
                  DMALL_METAL_TYRANOMON_X_ANIM_INDEX ,DMALL_YATAGARAMON_ANIM_INDEX
                },
              };
            case DMALL_ULFORCE_V_DRAMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMALL_ULFORCE_V_DRAMON_X_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMALL_ULTIMATE_BRACHIMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMALL_UPAMON_ANIM_INDEX:
              return {
                // Stage: Baby II
                .conditions = { .next_evolution_time_sec = 43200 },
                
                .num_animation_indices = 7,
                .animation_indices = {
                  DMALL_ARMADIMON_ANIM_INDEX ,DMALL_AGUMON_ANIM_INDEX ,DMALL_ARMADIMON_ANIM_INDEX ,DMALL_GIZAMON_ANIM_INDEX ,DMALL_SANGOMON_ANIM_INDEX ,DMALL_SWIMMON_ANIM_INDEX ,DMALL_V_MON_ANIM_INDEX
                },
              };
            case DMALL_VADEMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 11,
                .animation_indices = {
                  DMALL_EBEMON_ANIM_INDEX ,DMALL_DARKDRAMON_ANIM_INDEX ,DMALL_DEMON_ANIM_INDEX ,DMALL_HERAKLE_KABUTERIMON_ANIM_INDEX ,DMALL_HI_ANDROMON_ANIM_INDEX ,DMALL_KING_ETEMON_ANIM_INDEX ,DMALL_METAL_ETEMON_ANIM_INDEX ,DMALL_PIEMON_ANIM_INDEX ,DMALL_PINOCHIMON_ANIM_INDEX ,DMALL_PUKUMON_ANIM_INDEX ,DMALL_VENOM_VAMDEMON_ANIM_INDEX
                },
              };
            case DMALL_VALDURMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = 230400 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DMALL_DUKEMON_X_ANIM_INDEX
                },
              };
            case DMALL_VAMDEMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_BELIAL_VAMDEMON_ANIM_INDEX ,DMALL_VENOM_VAMDEMON_ANIM_INDEX ,DMALL_APOCALYMON_ANIM_INDEX ,DMALL_BARBAMON_ANIM_INDEX ,DMALL_BEELZEBUMON_ANIM_INDEX ,DMALL_BELIAL_VAMDEMON_ANIM_INDEX ,DMALL_BLACK_WAR_GREYMON_ANIM_INDEX ,DMALL_BOLTMON_ANIM_INDEX ,DMALL_DARKDRAMON_ANIM_INDEX ,DMALL_DEMON_ANIM_INDEX ,DMALL_GRAND_DRACUMON_ANIM_INDEX ,DMALL_KUZUHAMON_ANIM_INDEX ,DMALL_METAL_ETEMON_ANIM_INDEX ,DMALL_METAL_GARURUMON_BLACK_ANIM_INDEX ,DMALL_NOBLE_PUMPMON_ANIM_INDEX
                },
              };
            case DMALL_VAMDEMON_X_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 5,
                .animation_indices = {
                  DMALL_CHERUBIMON_VICE_X_ANIM_INDEX ,DMALL_METAL_PIRANIMON_ANIM_INDEX ,DMALL_PRINCE_MAMEMON_X_ANIM_INDEX ,DMALL_CHAOSDRAMON_X_ANIM_INDEX ,DMALL_METAL_PIRANIMON_ANIM_INDEX
                },
              };
            case DMALL_V_DRAMON_BLACK_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 10,
                .animation_indices = {
                  DMALL_AERO_V_DRAMON_ANIM_INDEX ,DMALL_ANDROMON_ANIM_INDEX ,DMALL_CYBERDRAMON_ANIM_INDEX ,DMALL_DELUMON_ANIM_INDEX ,DMALL_GARUDAMON_ANIM_INDEX ,DMALL_METAL_GREYMON_ANIM_INDEX ,DMALL_METAL_GREYMON_VIRUS_ANIM_INDEX ,DMALL_OROCHIMON_ANIM_INDEX ,DMALL_PAILDRAMON_ANIM_INDEX ,DMALL_TEKKAMON_ANIM_INDEX
                },
              };
            case DMALL_V_DRAMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_AERO_V_DRAMON_ANIM_INDEX ,DMALL_AERO_V_DRAMON_ANIM_INDEX ,DMALL_ANDROMON_ANIM_INDEX ,DMALL_ANGEWOMON_ANIM_INDEX ,DMALL_ASURAMON_ANIM_INDEX ,DMALL_BAALMON_ANIM_INDEX ,DMALL_BIG_MAMEMON_ANIM_INDEX ,DMALL_CYBERDRAMON_ANIM_INDEX ,DMALL_DELUMON_ANIM_INDEX ,DMALL_DIGITAMAMON_ANIM_INDEX ,DMALL_DURAMON_ANIM_INDEX ,DMALL_GARUDAMON_ANIM_INDEX ,DMALL_HANGYOMON_ANIM_INDEX ,DMALL_HOLY_ANGEMON_ANIM_INDEX ,DMALL_JYAGAMON_ANIM_INDEX
                },
              };
            case DMALL_VEGIMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_VADEMON_ANIM_INDEX ,DMALL_VADEMON_ANIM_INDEX ,DMALL_AERO_V_DRAMON_ANIM_INDEX ,DMALL_ANOMALOCARIMON_ANIM_INDEX ,DMALL_ARCHNEMON_ANIM_INDEX ,DMALL_ASTAMON_ANIM_INDEX ,DMALL_ASURAMON_ANIM_INDEX ,DMALL_ATLUR_KABUTERIMON_BLUE_ANIM_INDEX ,DMALL_ATLUR_KABUTERIMON_RED_ANIM_INDEX ,DMALL_BEOWOLFMON_ANIM_INDEX ,DMALL_BIG_MAMEMON_ANIM_INDEX ,DMALL_BLOSSOMON_ANIM_INDEX ,DMALL_DAGOMON_ANIM_INDEX ,DMALL_DARK_KNIGHTMON_ANIM_INDEX ,DMALL_DIGITAMAMON_ANIM_INDEX
                },
              };
            case DMALL_VELGRMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 10,
                .animation_indices = {
                  DMALL_KAISER_LEOMON_ANIM_INDEX ,DMALL_OKUWAMON_X_ANIM_INDEX ,DMALL_MEPHISMON_X_ANIM_INDEX ,DMALL_KAISER_LEOMON_ANIM_INDEX ,DMALL_MAMETYRAMON_ANIM_INDEX ,DMALL_STIFFILMON_ANIM_INDEX ,DMALL_KAISER_LEOMON_ANIM_INDEX ,DMALL_MAMETYRAMON_ANIM_INDEX ,DMALL_RAIHIMON_ANIM_INDEX ,DMALL_STIFFILMON_ANIM_INDEX
                },
              };
            case DMALL_VENOM_VAMDEMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMALL_VERMILLIMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 7,
                .animation_indices = {
                  DMALL_BLACK_WAR_GREYMON_ANIM_INDEX ,DMALL_GAIOUMON_ANIM_INDEX ,DMALL_MUGENDRAMON_ANIM_INDEX ,DMALL_OMEGAMON_ZWART_ANIM_INDEX ,DMALL_ROSEMON_ANIM_INDEX ,DMALL_SKULL_MAMMON_ANIM_INDEX ,DMALL_WAR_GREYMON_ANIM_INDEX
                },
              };
            case DMALL_V_MON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_GOLD_V_DRAMON_ANIM_INDEX ,DMALL_V_DRAMON_ANIM_INDEX ,DMALL_XV_MON_ANIM_INDEX ,DMALL_AIRDRAMON_ANIM_INDEX ,DMALL_ANGEMON_ANIM_INDEX ,DMALL_BLACK_GROWMON_ANIM_INDEX ,DMALL_CENTALMON_ANIM_INDEX ,DMALL_GAOGAMON_ANIM_INDEX ,DMALL_GEO_GREYMON_ANIM_INDEX ,DMALL_GEREMON_ANIM_INDEX ,DMALL_GOLD_V_DRAMON_ANIM_INDEX ,DMALL_GREYMON_ANIM_INDEX ,DMALL_GROWMON_ANIM_INDEX ,DMALL_GUARDROMON_ANIM_INDEX ,DMALL_HOOKMON_ANIM_INDEX
                },
              };
            case DMALL_VOLCANICDRAMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMALL_VOLTO_BAUTAMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMALL_VORVOMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 5,
                .animation_indices = {
                  DMALL_LAVORVOMON_ANIM_INDEX ,DMALL_BIRDRAMON_ANIM_INDEX ,DMALL_LAVORVOMON_ANIM_INDEX ,DMALL_MERAMON_ANIM_INDEX ,DMALL_TYRANOMON_ANIM_INDEX
                },
              };
            case DMALL_WANYAMON_ANIM_INDEX:
              return {
                // Stage: Baby II
                .conditions = { .next_evolution_time_sec = 43200 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_BEARMON_ANIM_INDEX ,DMALL_ELECMON_ANIM_INDEX ,DMALL_GAOMON_ANIM_INDEX ,DMALL_RENAMON_ANIM_INDEX ,DMALL_AGUMON_ANIM_INDEX ,DMALL_BAKUMON_ANIM_INDEX ,DMALL_BEARMON_ANIM_INDEX ,DMALL_CANDMON_ANIM_INDEX ,DMALL_CORONAMON_ANIM_INDEX ,DMALL_DORUMON_ANIM_INDEX ,DMALL_ELECMON_ANIM_INDEX ,DMALL_GAOMON_ANIM_INDEX ,DMALL_GIZAMON_ANIM_INDEX ,DMALL_GOMAMON_ANIM_INDEX ,DMALL_HAGURUMON_ANIM_INDEX
                },
              };
            case DMALL_WAR_GREYMON_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMALL_WAR_GREYMON_X_ANIM_INDEX:
              return {
                // Stage: Ultimate
                .conditions = { .next_evolution_time_sec = 230400 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  DMALL_OMEGAMON_X_ANIM_INDEX
                },
              };
            case DMALL_WARU_MONZAEMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 12,
                .animation_indices = {
                  DMALL_BEELZEBUMON_ANIM_INDEX ,DMALL_DARKDRAMON_ANIM_INDEX ,DMALL_DEMON_ANIM_INDEX ,DMALL_METAL_ETEMON_ANIM_INDEX ,DMALL_MUGENDRAMON_ANIM_INDEX ,DMALL_PIEMON_ANIM_INDEX ,DMALL_PINOCHIMON_ANIM_INDEX ,DMALL_PLATINUM_NUMEMON_ANIM_INDEX ,DMALL_PUKUMON_ANIM_INDEX ,DMALL_SABER_LEOMON_ANIM_INDEX ,DMALL_SHIN_MONZAEMON_ANIM_INDEX ,DMALL_VENOM_VAMDEMON_ANIM_INDEX
                },
              };
            case DMALL_WARU_SEADRAMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 14,
                .animation_indices = {
                  DMALL_ANCIENT_MERMAIMON_ANIM_INDEX ,DMALL_BLACK_WAR_GREYMON_ANIM_INDEX ,DMALL_CRES_GARURUMON_ANIM_INDEX ,DMALL_DEMON_ANIM_INDEX ,DMALL_GAIOUMON_ANIM_INDEX ,DMALL_GIGA_SEADRAMON_ANIM_INDEX ,DMALL_LEVIAMON_ANIM_INDEX ,DMALL_METAL_ETEMON_ANIM_INDEX ,DMALL_METAL_GARURUMON_ANIM_INDEX ,DMALL_METAL_SEADRAMON_ANIM_INDEX ,DMALL_PLATINUM_NUMEMON_ANIM_INDEX ,DMALL_PLESIOMON_ANIM_INDEX ,DMALL_PUKUMON_ANIM_INDEX ,DMALL_REGALECUSMON_ANIM_INDEX
                },
              };
            case DMALL_WASPMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 7,
                .animation_indices = {
                  DMALL_CANNONBEEMON_ANIM_INDEX ,DMALL_ATLUR_KABUTERIMON_RED_ANIM_INDEX ,DMALL_CANNONBEEMON_ANIM_INDEX ,DMALL_DORUGUREMON_ANIM_INDEX ,DMALL_GRADEMON_ANIM_INDEX ,DMALL_HISYARYUMON_ANIM_INDEX ,DMALL_OKUWAMON_ANIM_INDEX
                },
              };
            case DMALL_WEREGARURUMON_BLACK_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_METAL_GARURUMON_BLACK_ANIM_INDEX ,DMALL_BANCHO_LEOMON_ANIM_INDEX ,DMALL_BOLTMON_ANIM_INDEX ,DMALL_CRES_GARURUMON_ANIM_INDEX ,DMALL_DEMON_ANIM_INDEX ,DMALL_DINOTIGERMON_ANIM_INDEX ,DMALL_DUFTMON_ANIM_INDEX ,DMALL_HOLYDRAMON_ANIM_INDEX ,DMALL_METAL_GARURUMON_ANIM_INDEX ,DMALL_METAL_GARURUMON_BLACK_ANIM_INDEX ,DMALL_METAL_SEADRAMON_ANIM_INDEX ,DMALL_OMEGAMON_ZWART_ANIM_INDEX ,DMALL_SAINT_GALGOMON_ANIM_INDEX ,DMALL_SAKUYAMON_ANIM_INDEX ,DMALL_SERAPHIMON_ANIM_INDEX
                },
              };
            case DMALL_WERE_GARURUMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_CRES_GARURUMON_ANIM_INDEX ,DMALL_METAL_GARURUMON_ANIM_INDEX ,DMALL_BANCHO_LEOMON_ANIM_INDEX ,DMALL_BOLTMON_ANIM_INDEX ,DMALL_CRES_GARURUMON_ANIM_INDEX ,DMALL_DARKDRAMON_ANIM_INDEX ,DMALL_DEMON_ANIM_INDEX ,DMALL_DINOTIGERMON_ANIM_INDEX ,DMALL_DUFTMON_ANIM_INDEX ,DMALL_HOLYDRAMON_ANIM_INDEX ,DMALL_METAL_GARURUMON_ANIM_INDEX ,DMALL_METAL_GARURUMON_BLACK_ANIM_INDEX ,DMALL_METAL_SEADRAMON_ANIM_INDEX ,DMALL_MUGENDRAMON_ANIM_INDEX ,DMALL_NOBLE_PUMPMON_ANIM_INDEX
                },
              };
            case DMALL_WERE_GARURUMON_X_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_METAL_GARURUMON_X_ANIM_INDEX ,DMALL_JESMON_X_ANIM_INDEX ,DMALL_VALDURMON_ANIM_INDEX ,DMALL_PLATINUM_NUMEMON_ANIM_INDEX ,DMALL_BOLTMON_ANIM_INDEX ,DMALL_DEMON_ANIM_INDEX ,DMALL_DUKEMON_ANIM_INDEX ,DMALL_METAL_GARURUMON_ANIM_INDEX ,DMALL_METAL_GARURUMON_BLACK_ANIM_INDEX ,DMALL_METAL_SEADRAMON_ANIM_INDEX ,DMALL_PLATINUM_NUMEMON_ANIM_INDEX ,DMALL_ROSEMON_ANIM_INDEX ,DMALL_SAINT_GALGOMON_ANIM_INDEX ,DMALL_SAKUYAMON_ANIM_INDEX ,DMALL_SERAPHIMON_ANIM_INDEX
                },
              };
            case DMALL_WHAMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_METAL_MAMEMON_ANIM_INDEX ,DMALL_AERO_V_DRAMON_ANIM_INDEX ,DMALL_ANDROMON_ANIM_INDEX ,DMALL_ANGEWOMON_ANIM_INDEX ,DMALL_ASURAMON_ANIM_INDEX ,DMALL_BAALMON_ANIM_INDEX ,DMALL_BIG_MAMEMON_ANIM_INDEX ,DMALL_CHIMAIRAMON_ANIM_INDEX ,DMALL_CYBERDRAMON_ANIM_INDEX ,DMALL_DURAMON_ANIM_INDEX ,DMALL_GARUDAMON_ANIM_INDEX ,DMALL_HANGYOMON_ANIM_INDEX ,DMALL_HOLY_ANGEMON_ANIM_INDEX ,DMALL_JYAGAMON_ANIM_INDEX ,DMALL_MAMEMON_ANIM_INDEX
                },
              };
            case DMALL_WIZARMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_AERO_V_DRAMON_ANIM_INDEX ,DMALL_ANDROMON_ANIM_INDEX ,DMALL_ANGEWOMON_ANIM_INDEX ,DMALL_ANOMALOCARIMON_ANIM_INDEX ,DMALL_ASURAMON_ANIM_INDEX ,DMALL_BAALMON_ANIM_INDEX ,DMALL_BEOWOLFMON_ANIM_INDEX ,DMALL_BIG_MAMEMON_ANIM_INDEX ,DMALL_CYBERDRAMON_ANIM_INDEX ,DMALL_DARK_KNIGHTMON_ANIM_INDEX ,DMALL_DAGOMON_ANIM_INDEX ,DMALL_DEATH_MERAMON_ANIM_INDEX ,DMALL_DIGITAMAMON_ANIM_INDEX ,DMALL_DORUGUREMON_ANIM_INDEX ,DMALL_DURAMON_ANIM_INDEX
                },
              };
            case DMALL_WIZARMON_X_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 8,
                .animation_indices = {
                  DMALL_MONZAEMON_X_ANIM_INDEX ,DMALL_ANGEWOMON_X_ANIM_INDEX ,DMALL_ANOMALOCARIMON_X_ANIM_INDEX ,DMALL_GRADEMON_ANIM_INDEX ,DMALL_MAMEMON_X_ANIM_INDEX ,DMALL_CRYS_PALEDRAMON_ANIM_INDEX ,DMALL_JAZARICHMON_ANIM_INDEX ,DMALL_PUMPMON_ANIM_INDEX
                },
              };
            case DMALL_WOODMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_JYUREIMON_ANIM_INDEX ,DMALL_AERO_V_DRAMON_ANIM_INDEX ,DMALL_ANOMALOCARIMON_ANIM_INDEX ,DMALL_ASTAMON_ANIM_INDEX ,DMALL_ASURAMON_ANIM_INDEX ,DMALL_BEOWOLFMON_ANIM_INDEX ,DMALL_BIG_MAMEMON_ANIM_INDEX ,DMALL_BLOSSOMON_ANIM_INDEX ,DMALL_DAGOMON_ANIM_INDEX ,DMALL_DARK_KNIGHTMON_ANIM_INDEX ,DMALL_DELUMON_ANIM_INDEX ,DMALL_ETEMON_ANIM_INDEX ,DMALL_GERBEMON_ANIM_INDEX ,DMALL_HANGYOMON_ANIM_INDEX ,DMALL_JYUREIMON_ANIM_INDEX
                },
              };
            case DMALL_WORMMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_SHADRAMON_ANIM_INDEX ,DMALL_AIRDRAMON_ANIM_INDEX ,DMALL_ANGEMON_ANIM_INDEX ,DMALL_BAKEMON_ANIM_INDEX ,DMALL_DEVIMON_ANIM_INDEX ,DMALL_DOKUGUMON_ANIM_INDEX ,DMALL_GARURUMON_ANIM_INDEX ,DMALL_GOKIMON_ANIM_INDEX ,DMALL_GEREMON_ANIM_INDEX ,DMALL_GREYMON_ANIM_INDEX ,DMALL_ICE_DEVIMON_ANIM_INDEX ,DMALL_KABUTERIMON_ANIM_INDEX ,DMALL_KUWAGAMON_ANIM_INDEX ,DMALL_MEICOOMON_ANIM_INDEX ,DMALL_MERAMON_ANIM_INDEX
                },
              };
            case DMALL_XIAOMON_ANIM_INDEX:
              return {
                // Stage: Baby II
                .conditions = { .next_evolution_time_sec = 43200 },
                
                .num_animation_indices = 2,
                .animation_indices = {
                  DMALL_LABRAMON_ANIM_INDEX ,DMALL_LABRAMON_ANIM_INDEX
                },
              };
            case DMALL_XV_MON_BLACK_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 8,
                .animation_indices = {
                  DMALL_AERO_V_DRAMON_ANIM_INDEX ,DMALL_ANDROMON_ANIM_INDEX ,DMALL_HOLY_ANGEMON_ANIM_INDEX ,DMALL_MEGADRAMON_ANIM_INDEX ,DMALL_OROCHIMON_ANIM_INDEX ,DMALL_PAILDRAMON_ANIM_INDEX ,DMALL_SKULL_GREYMON_ANIM_INDEX ,DMALL_YATAGARAMON_ANIM_INDEX
                },
              };
            case DMALL_XV_MON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_PAILDRAMON_ANIM_INDEX ,DMALL_AERO_V_DRAMON_ANIM_INDEX ,DMALL_ANDROMON_ANIM_INDEX ,DMALL_ANOMALOCARIMON_ANIM_INDEX ,DMALL_BAALMON_ANIM_INDEX ,DMALL_BIG_MAMEMON_ANIM_INDEX ,DMALL_DIGITAMAMON_ANIM_INDEX ,DMALL_DORUGUREMON_ANIM_INDEX ,DMALL_DURAMON_ANIM_INDEX ,DMALL_GARUDAMON_ANIM_INDEX ,DMALL_HANGYOMON_ANIM_INDEX ,DMALL_HISYARYUMON_ANIM_INDEX ,DMALL_HOLY_ANGEMON_ANIM_INDEX ,DMALL_MEGADRAMON_ANIM_INDEX ,DMALL_MEGALO_GROWMON_ANIM_INDEX
                },
              };
            case DMALL_YAAMON_ANIM_INDEX:
              return {
                // Stage: Baby II
                .conditions = { .next_evolution_time_sec = 43200 },
                
                .num_animation_indices = 14,
                .animation_indices = {
                  DMALL_IMPMON_ANIM_INDEX ,DMALL_GOMAMON_X_ANIM_INDEX ,DMALL_KOKUWAMON_X_ANIM_INDEX ,DMALL_AGUMON_BLACK_X_ANIM_INDEX ,DMALL_HERISSMON_ANIM_INDEX ,DMALL_DUSKMON_ANIM_INDEX ,DMALL_PLOTMON_X_ANIM_INDEX ,DMALL_OTAMAMON_X_ANIM_INDEX ,DMALL_IMPMON_X_ANIM_INDEX ,DMALL_DORUMON_ANIM_INDEX ,DMALL_DUSKMON_ANIM_INDEX ,DMALL_HERISSMON_ANIM_INDEX ,DMALL_IMPMON_ANIM_INDEX ,DMALL_KERAMON_ANIM_INDEX
                },
              };
            case DMALL_YANMAMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 7,
                .animation_indices = {
                  DMALL_ATLUR_KABUTERIMON_RED_ANIM_INDEX ,DMALL_HANGYOMON_ANIM_INDEX ,DMALL_LILIMON_ANIM_INDEX ,DMALL_MEGADRAMON_ANIM_INDEX ,DMALL_OKUWAMON_ANIM_INDEX ,DMALL_PICCOLOMON_ANIM_INDEX ,DMALL_PUMPMON_ANIM_INDEX
                },
              };
            case DMALL_YATAGARAMON_2006_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_BARBAMON_ANIM_INDEX ,DMALL_BELIAL_VAMDEMON_ANIM_INDEX ,DMALL_CHAOSMON_ANIM_INDEX ,DMALL_DARKDRAMON_ANIM_INDEX ,DMALL_GRIFFOMON_ANIM_INDEX ,DMALL_HOUOUMON_ANIM_INDEX ,DMALL_KUZUHAMON_ANIM_INDEX ,DMALL_LILITHMON_ANIM_INDEX ,DMALL_METAL_GARURUMON_ANIM_INDEX ,DMALL_METALLICDRAMON_ANIM_INDEX ,DMALL_OURYUMON_ANIM_INDEX ,DMALL_PLATINUM_NUMEMON_ANIM_INDEX ,DMALL_SUSANOOMON_ANIM_INDEX ,DMALL_ULFORCE_V_DRAMON_ANIM_INDEX ,DMALL_VALDURMON_ANIM_INDEX
                },
              };
            case DMALL_YATAGARAMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 8,
                .animation_indices = {
                  DMALL_SAKUYAMON_X_ANIM_INDEX ,DMALL_BEEL_STARMON_X_ANIM_INDEX ,DMALL_VALDURMON_ANIM_INDEX ,DMALL_BELIAL_VAMDEMON_ANIM_INDEX ,DMALL_PLATINUM_NUMEMON_ANIM_INDEX ,DMALL_HOUOUMON_ANIM_INDEX ,DMALL_ROSEMON_ANIM_INDEX ,DMALL_VALDURMON_ANIM_INDEX
                },
              };
            case DMALL_YOUKOMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 5,
                .animation_indices = {
                  DMALL_ATLUR_KABUTERIMON_BLUE_ANIM_INDEX ,DMALL_BLACK_RAPIDMON_ANIM_INDEX ,DMALL_CATURAMON_ANIM_INDEX ,DMALL_DEATH_MERAMON_ANIM_INDEX ,DMALL_SKULL_BALUCHIMON_ANIM_INDEX
                },
              };
            case DMALL_YUKI_AGUMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_AIRDRAMON_ANIM_INDEX ,DMALL_DOBERMON_ANIM_INDEX ,DMALL_GEO_GREYMON_ANIM_INDEX ,DMALL_GEREMON_ANIM_INDEX ,DMALL_GREYMON_ANIM_INDEX ,DMALL_GREYMON_BLUE_ANIM_INDEX ,DMALL_GROWMON_ANIM_INDEX ,DMALL_GURURUMON_ANIM_INDEX ,DMALL_HOOKMON_ANIM_INDEX ,DMALL_HYOUGAMON_ANIM_INDEX ,DMALL_ICEMON_ANIM_INDEX ,DMALL_IKKAKUMON_ANIM_INDEX ,DMALL_LEKISMON_ANIM_INDEX ,DMALL_NUMEMON_ANIM_INDEX ,DMALL_SCUMON_ANIM_INDEX
                },
              };
            case DMALL_YUKIDARUMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 15,
                .animation_indices = {
                  DMALL_METAL_MAMEMON_ANIM_INDEX ,DMALL_AERO_V_DRAMON_ANIM_INDEX ,DMALL_ANDROMON_ANIM_INDEX ,DMALL_ANGEWOMON_ANIM_INDEX ,DMALL_ASURAMON_ANIM_INDEX ,DMALL_BAALMON_ANIM_INDEX ,DMALL_BIG_MAMEMON_ANIM_INDEX ,DMALL_BLUE_MERAMON_ANIM_INDEX ,DMALL_CHIMAIRAMON_ANIM_INDEX ,DMALL_CRESCEMON_ANIM_INDEX ,DMALL_CYBERDRAMON_ANIM_INDEX ,DMALL_DURAMON_ANIM_INDEX ,DMALL_GARUDAMON_ANIM_INDEX ,DMALL_GUSOKUMON_ANIM_INDEX ,DMALL_HANGYOMON_ANIM_INDEX
                },
              };
            case DMALL_YUKIMI_BOTAMON_ANIM_INDEX:
              return {
                // Stage: Baby I
                .conditions = { .next_evolution_time_sec = 600 },
                
                .num_animation_indices = 6,
                .animation_indices = {
                  DMALL_HIYARIMON_ANIM_INDEX ,DMALL_NYAROMON_ANIM_INDEX ,DMALL_HIYARIMON_ANIM_INDEX ,DMALL_MOONMON_ANIM_INDEX ,DMALL_NYAROMON_ANIM_INDEX ,DMALL_TUNOMON_ANIM_INDEX
                },
              };
            case DMALL_YURAMON_ANIM_INDEX:
              return {
                // Stage: Baby I
                .conditions = { .next_evolution_time_sec = 600 },
                
                .num_animation_indices = 6,
                .animation_indices = {
                  DMALL_BUDMON_ANIM_INDEX ,DMALL_TANEMON_ANIM_INDEX ,DMALL_TANEMON_ANIM_INDEX ,DMALL_BUDMON_ANIM_INDEX ,DMALL_KOROMON_ANIM_INDEX ,DMALL_TANEMON_ANIM_INDEX
                },
              };
            case DMALL_ZASSOUMON_ANIM_INDEX:
              return {
                // Stage: Adult
                .conditions = { .next_evolution_time_sec = 129600 },
                
                .num_animation_indices = 4,
                .animation_indices = {
                  DMALL_BLOSSOMON_ANIM_INDEX ,DMALL_BLOSSOMON_ANIM_INDEX ,DMALL_LILAMON_ANIM_INDEX ,DMALL_TONOSAMA_GEKOMON_ANIM_INDEX
                },
              };
            case DMALL_ZENIMON_ANIM_INDEX:
              return {
                // Stage: Child
                .conditions = { .next_evolution_time_sec = 86400 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case DMALL_ZERIMON_ANIM_INDEX:
              return {
                // Stage: Baby I
                .conditions = { .next_evolution_time_sec = 600 },
                
                .num_animation_indices = 3,
                .animation_indices = {
                  DMALL_GUMMYMON_ANIM_INDEX ,DMALL_GUMMYMON_ANIM_INDEX ,DMALL_GUMMYMON_ANIM_INDEX
                },
              };
            case DMALL_ZUDOMON_ANIM_INDEX:
              return {
                // Stage: Perfect
                .conditions = { .next_evolution_time_sec = 172800 },
                
                .num_animation_indices = 11,
                .animation_indices = {
                  DMALL_PLESIOMON_ANIM_INDEX ,DMALL_ANCIENT_MEGATHERIUMON_ANIM_INDEX ,DMALL_BOLTMON_ANIM_INDEX ,DMALL_GIGA_SEADRAMON_ANIM_INDEX ,DMALL_MARIN_ANGEMON_ANIM_INDEX ,DMALL_METAL_GARURUMON_ANIM_INDEX ,DMALL_METAL_SEADRAMON_ANIM_INDEX ,DMALL_PLESIOMON_ANIM_INDEX ,DMALL_SABER_LEOMON_ANIM_INDEX ,DMALL_SERAPHIMON_ANIM_INDEX ,DMALL_TITAMON_ANIM_INDEX
                },
              };
            case DMALL_ZURUMON_ANIM_INDEX:
              return {
                // Stage: Baby I
                .conditions = { .next_evolution_time_sec = 600 },
                
                .num_animation_indices = 5,
                .animation_indices = {
                  DMALL_PAGUMON_ANIM_INDEX ,DMALL_CAPRIMON_ANIM_INDEX ,DMALL_KOROMON_ANIM_INDEX ,DMALL_MOCHIMON_ANIM_INDEX ,DMALL_PAGUMON_ANIM_INDEX
                },
              };
            default: return {};
        }
        return {};
    }
}

