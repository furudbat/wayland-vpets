#include "embedded_assets/embedded_image.h"
#include "embedded_assets/dmx/dmx.hpp"
#include "embedded_assets/dmx/dmx_evol.h"
#include "graphics/animation_shared_memory.h"

/// @NOTE: Generated evolution data dmx

namespace bongocat::assets {
    static constexpr animation::animation_evolution_data_t dmx_evol_data_table[] ASSETS_DATA_EVOL_SECTION = {
        // Name: Agumon (Black) X
        {
            // Stage: Child
            .conditions = { .next_evolution_time_sec = 86400 },
            
            .num_animation_indices = 4,
            .animation_indices = {
                DMX_DARK_TYRANOMON_X_ANIM_INDEX ,DMX_KUWAGAMON_X_ANIM_INDEX ,DMX_NUMEMON_X_ANIM_INDEX ,DMX_ALLOMON_X_ANIM_INDEX
            },
        },
        // Name: Agumon X
        {
            // Stage: Child
            .conditions = { .next_evolution_time_sec = 86400 },
            
            .num_animation_indices = 3,
            .animation_indices = {
                DMX_TYRANOMON_X_ANIM_INDEX ,DMX_TOBUCATMON_ANIM_INDEX ,DMX_DAMEMON_ANIM_INDEX
            },
        },
        // Name: Allomon X
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 115200 },
            
            .num_animation_indices = 4,
            .animation_indices = {
                DMX_TRICERAMON_X_ANIM_INDEX ,DMX_METAL_FANTOMON_ANIM_INDEX ,DMX_MAMMON_X_ANIM_INDEX ,DMX_MAMETYRAMON_ANIM_INDEX
            },
        },
        // Name: Alphamon Ouryuken
        {
            // Stage: Ultimate
            .conditions = { .next_evolution_time_sec = 172800 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Alphamon
        {
            // Stage: Ultimate
            .conditions = { .next_evolution_time_sec = 172800 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Ancient Sphinxmon
        {
            // Stage: Ultimate
            .conditions = { .next_evolution_time_sec = 172800 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Angewomon X
        {
            // Stage: Perfect
            .conditions = { .next_evolution_time_sec = 144000 },
            
            .num_animation_indices = 12,
            .animation_indices = {
                DMX_CHERUBIMON_VIRTUE_X_ANIM_INDEX ,DMX_GODDRAMON_X_ANIM_INDEX ,DMX_OURYUMON_ANIM_INDEX ,DMX_OFANIMON_X_ANIM_INDEX ,DMX_PLESIOMON_X_ANIM_INDEX ,DMX_GAIOUMON_ANIM_INDEX ,DMX_DINOTIGERMON_ANIM_INDEX ,DMX_HOLYDRAMON_X_ANIM_INDEX ,DMX_EBEMON_X_ANIM_INDEX ,DMX_HEXEBLAUMON_ANIM_INDEX ,DMX_METALLICDRAMON_ANIM_INDEX ,DMX_NOBLE_PUMPMON_ANIM_INDEX
            },
        },
        // Name: Anomalocarimon X
        {
            // Stage: Perfect
            .conditions = { .next_evolution_time_sec = 144000 },
            
            .num_animation_indices = 12,
            .animation_indices = {
                DMX_CHERUBIMON_VIRTUE_X_ANIM_INDEX ,DMX_GODDRAMON_X_ANIM_INDEX ,DMX_OURYUMON_ANIM_INDEX ,DMX_OFANIMON_X_ANIM_INDEX ,DMX_PLESIOMON_X_ANIM_INDEX ,DMX_GAIOUMON_ANIM_INDEX ,DMX_DINOTIGERMON_ANIM_INDEX ,DMX_HOLYDRAMON_X_ANIM_INDEX ,DMX_EBEMON_X_ANIM_INDEX ,DMX_HEXEBLAUMON_ANIM_INDEX ,DMX_METALLICDRAMON_ANIM_INDEX ,DMX_NOBLE_PUMPMON_ANIM_INDEX
            },
        },
        // Name: Bagramon
        {
            // Stage: Ultimate
            .conditions = { .next_evolution_time_sec = 230400 },
            
            .num_animation_indices = 2,
            .animation_indices = {
                DMX_DARKNESS_BAGRAMON_ANIM_INDEX ,DMX_BARBAMON_X_ANIM_INDEX
            },
        },
        // Name: Barbamon X
        {
            // Stage: Ultimate
            .conditions = { .next_evolution_time_sec = 172800 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Beel Starmon X
        {
            // Stage: Ultimate
            .conditions = { .next_evolution_time_sec = 230400 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DMX_DIABLOMON_X_ANIM_INDEX
            },
        },
        // Name: Beelzebumon X
        {
            // Stage: Ultimate
            .conditions = { .next_evolution_time_sec = 230400 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DMX_DIABLOMON_X_ANIM_INDEX
            },
        },
        // Name: Belial Vamdemon
        {
            // Stage: Ultimate
            .conditions = { .next_evolution_time_sec = 230400 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DMX_DIABLOMON_X_ANIM_INDEX
            },
        },
        // Name: Belphemon X
        {
            // Stage: Ultimate
            .conditions = { .next_evolution_time_sec = 172800 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Black Wargreymon X
        {
            // Stage: Ultimate
            .conditions = { .next_evolution_time_sec = 172800 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Black War Greymon X
        {
            // Stage: Ultimate
            .conditions = { .next_evolution_time_sec = 230400 },
            
            .num_animation_indices = 3,
            .animation_indices = {
                DMX_DEMON_X_ANIM_INDEX ,DMX_RASENMON_ANIM_INDEX ,DMX_BARBAMON_X_ANIM_INDEX
            },
        },
        // Name: Cannonbeemon
        {
            // Stage: Perfect
            .conditions = { .next_evolution_time_sec = 144000 },
            
            .num_animation_indices = 12,
            .animation_indices = {
                DMX_RAPIDMON_X_ANIM_INDEX ,DMX_JUSTIMON_X_ANIM_INDEX ,DMX_ALPHAMON_ANIM_INDEX ,DMX_HOUOUMON_X_ANIM_INDEX ,DMX_TIGER_VESPAMON_ANIM_INDEX ,DMX_GAIOUMON_ANIM_INDEX ,DMX_DINOTIGERMON_ANIM_INDEX ,DMX_HOLYDRAMON_X_ANIM_INDEX ,DMX_EBEMON_X_ANIM_INDEX ,DMX_HEXEBLAUMON_ANIM_INDEX ,DMX_METALLICDRAMON_ANIM_INDEX ,DMX_NOBLE_PUMPMON_ANIM_INDEX
            },
        },
        // Name: Cannon Beemon
        {
            // Stage: Perfect
            .conditions = { .next_evolution_time_sec = 144000 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Cerberumon X
        {
            // Stage: Perfect
            .conditions = { .next_evolution_time_sec = 144000 },
            
            .num_animation_indices = 5,
            .animation_indices = {
                DMX_SAKUYAMON_X_ANIM_INDEX ,DMX_SLEIPMON_X_ANIM_INDEX ,DMX_BELIAL_VAMDEMON_ANIM_INDEX ,DMX_JESMON_X_ANIM_INDEX ,DMX_PLATINUM_NUMEMON_ANIM_INDEX
            },
        },
        // Name: Chaosdramon X
        {
            // Stage: Ultimate
            .conditions = { .next_evolution_time_sec = 230400 },
            
            .num_animation_indices = 3,
            .animation_indices = {
                DMX_DEMON_X_ANIM_INDEX ,DMX_LUCEMON_X_ANIM_INDEX ,DMX_DIABLOMON_X_ANIM_INDEX
            },
        },
        // Name: Cherubimon (Vice) X
        {
            // Stage: Ultimate
            .conditions = { .next_evolution_time_sec = 230400 },
            
            .num_animation_indices = 2,
            .animation_indices = {
                DMX_BELPHEMON_X_ANIM_INDEX ,DMX_BARBAMON_X_ANIM_INDEX
            },
        },
        // Name: Cherubimon (Virtue) X
        {
            // Stage: Ultimate
            .conditions = { .next_evolution_time_sec = 230400 },
            
            .num_animation_indices = 8,
            .animation_indices = {
                DMX_ULFORCE_V_DRAMON_X_ANIM_INDEX ,DMX_EXAMON_X_ANIM_INDEX ,DMX_DUFTMON_X_ANIM_INDEX ,DMX_SLEIPMON_X_ANIM_INDEX ,DMX_JESMON_X_ANIM_INDEX ,DMX_OMEGAMON_X_ANIM_INDEX ,DMX_ALPHAMON_OURYUKEN_ANIM_INDEX ,DMX_JESMON_GX_ANIM_INDEX
            },
        },
        // Name: Cho-Hakkaimon
        {
            // Stage: Perfect
            .conditions = { .next_evolution_time_sec = 144000 },
            
            .num_animation_indices = 5,
            .animation_indices = {
                DMX_BEEL_STARMON_X_ANIM_INDEX ,DMX_CRANIUMMON_X_ANIM_INDEX ,DMX_METAL_GARURUMON_X_ANIM_INDEX ,DMX_BELIAL_VAMDEMON_ANIM_INDEX ,DMX_PLATINUM_NUMEMON_ANIM_INDEX
            },
        },
        // Name: Cocomon
        {
            // Stage: Baby I
            .conditions = { .next_evolution_time_sec = 600 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Craniummon X
        {
            // Stage: Ultimate
            .conditions = { .next_evolution_time_sec = 230400 },
            
            .num_animation_indices = 2,
            .animation_indices = {
                DMX_LORD_KNIGHTMON_X_ANIM_INDEX ,DMX_ALPHAMON_ANIM_INDEX
            },
        },
        // Name: Crys Paledramon
        {
            // Stage: Perfect
            .conditions = { .next_evolution_time_sec = 144000 },
            
            .num_animation_indices = 12,
            .animation_indices = {
                DMX_RAPIDMON_X_ANIM_INDEX ,DMX_JUSTIMON_X_ANIM_INDEX ,DMX_ALPHAMON_ANIM_INDEX ,DMX_HOUOUMON_X_ANIM_INDEX ,DMX_TIGER_VESPAMON_ANIM_INDEX ,DMX_GAIOUMON_ANIM_INDEX ,DMX_DINOTIGERMON_ANIM_INDEX ,DMX_HOLYDRAMON_X_ANIM_INDEX ,DMX_EBEMON_X_ANIM_INDEX ,DMX_HEXEBLAUMON_ANIM_INDEX ,DMX_METALLICDRAMON_ANIM_INDEX ,DMX_NOBLE_PUMPMON_ANIM_INDEX
            },
        },
        // Name: Cyberdramon X
        {
            // Stage: Perfect
            .conditions = { .next_evolution_time_sec = 144000 },
            
            .num_animation_indices = 12,
            .animation_indices = {
                DMX_RAPIDMON_X_ANIM_INDEX ,DMX_JUSTIMON_X_ANIM_INDEX ,DMX_ALPHAMON_ANIM_INDEX ,DMX_HOUOUMON_X_ANIM_INDEX ,DMX_TIGER_VESPAMON_ANIM_INDEX ,DMX_GAIOUMON_ANIM_INDEX ,DMX_DINOTIGERMON_ANIM_INDEX ,DMX_HOLYDRAMON_X_ANIM_INDEX ,DMX_EBEMON_X_ANIM_INDEX ,DMX_HEXEBLAUMON_ANIM_INDEX ,DMX_METALLICDRAMON_ANIM_INDEX ,DMX_NOBLE_PUMPMON_ANIM_INDEX
            },
        },
        // Name: Damemon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 115200 },
            
            .num_animation_indices = 5,
            .animation_indices = {
                DMX_CERBERUMON_X_ANIM_INDEX ,DMX_SKULL_BALUCHIMON_ANIM_INDEX ,DMX_MEGALO_GROWMON_X_ANIM_INDEX ,DMX_CHO_HAKKAIMON_ANIM_INDEX ,DMX_LILIMON_X_ANIM_INDEX
            },
        },
        // Name: Dark Knightmon X
        {
            // Stage: Ultimate
            .conditions = { .next_evolution_time_sec = 230400 },
            
            .num_animation_indices = 3,
            .animation_indices = {
                DMX_LUCEMON_X_ANIM_INDEX ,DMX_DARKNESS_BAGRAMON_ANIM_INDEX ,DMX_BARBAMON_X_ANIM_INDEX
            },
        },
        // Name: Darkness Bagramon
        {
            // Stage: Ultimate
            .conditions = { .next_evolution_time_sec = 172800 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Dark Tyranomon X
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 115200 },
            
            .num_animation_indices = 4,
            .animation_indices = {
                DMX_METAL_GREYMON_VIRUS_X_ANIM_INDEX ,DMX_MAMMON_X_ANIM_INDEX ,DMX_TRICERAMON_X_ANIM_INDEX ,DMX_MAMETYRAMON_ANIM_INDEX
            },
        },
        // Name: Demon X
        {
            // Stage: Ultimate
            .conditions = { .next_evolution_time_sec = 172800 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Diablomon X
        {
            // Stage: Ultimate
            .conditions = { .next_evolution_time_sec = 172800 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Dinorexmon
        {
            // Stage: Ultimate
            .conditions = { .next_evolution_time_sec = 230400 },
            
            .num_animation_indices = 2,
            .animation_indices = {
                DMX_LEVIAMON_X_ANIM_INDEX ,DMX_BARBAMON_X_ANIM_INDEX
            },
        },
        // Name: Dinotigermon
        {
            // Stage: Ultimate
            .conditions = { .next_evolution_time_sec = 230400 },
            
            .num_animation_indices = 8,
            .animation_indices = {
                DMX_MAGNAMON_X_ANIM_INDEX ,DMX_GANKOOMON_X_ANIM_INDEX ,DMX_DYNASMON_X_ANIM_INDEX ,DMX_CRANIUMMON_X_ANIM_INDEX ,DMX_LORD_KNIGHTMON_X_ANIM_INDEX ,DMX_DUKEMON_X_ANIM_INDEX ,DMX_ALPHAMON_OURYUKEN_ANIM_INDEX ,DMX_JESMON_GX_ANIM_INDEX
            },
        },
        // Name: DORUgamon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 115200 },
            
            .num_animation_indices = 10,
            .animation_indices = {
                DMX_DORUGUREMON_ANIM_INDEX ,DMX_CYBERDRAMON_X_ANIM_INDEX ,DMX_OMEGA_SHOUTMON_X_ANIM_INDEX ,DMX_GARUDAMON_X_ANIM_INDEX ,DMX_CANNONBEEMON_ANIM_INDEX ,DMX_GRADEMON_ANIM_INDEX ,DMX_MAMEMON_X_ANIM_INDEX ,DMX_CRYS_PALEDRAMON_ANIM_INDEX ,DMX_JAZARICHMON_ANIM_INDEX ,DMX_PUMPMON_ANIM_INDEX
            },
        },
        // Name: DORUguremon
        {
            // Stage: Perfect
            .conditions = { .next_evolution_time_sec = 144000 },
            
            .num_animation_indices = 12,
            .animation_indices = {
                DMX_RAPIDMON_X_ANIM_INDEX ,DMX_JUSTIMON_X_ANIM_INDEX ,DMX_ALPHAMON_ANIM_INDEX ,DMX_HOUOUMON_X_ANIM_INDEX ,DMX_TIGER_VESPAMON_ANIM_INDEX ,DMX_GAIOUMON_ANIM_INDEX ,DMX_DINOTIGERMON_ANIM_INDEX ,DMX_HOLYDRAMON_X_ANIM_INDEX ,DMX_EBEMON_X_ANIM_INDEX ,DMX_HEXEBLAUMON_ANIM_INDEX ,DMX_METALLICDRAMON_ANIM_INDEX ,DMX_NOBLE_PUMPMON_ANIM_INDEX
            },
        },
        // Name: DORUmon
        {
            // Stage: Child
            .conditions = { .next_evolution_time_sec = 86400 },
            
            .num_animation_indices = 7,
            .animation_indices = {
                DMX_DORUGAMON_ANIM_INDEX ,DMX_PTERANOMON_X_ANIM_INDEX ,DMX_TOGEMON_X_ANIM_INDEX ,DMX_SIESAMON_X_ANIM_INDEX ,DMX_OMEKAMON_ANIM_INDEX ,DMX_PALEDRAMON_ANIM_INDEX ,DMX_JAZARDMON_ANIM_INDEX
            },
        },
        // Name: Dracomon X
        {
            // Stage: Child
            .conditions = { .next_evolution_time_sec = 86400 },
            
            .num_animation_indices = 2,
            .animation_indices = {
                DMX_GROWMON_X_ANIM_INDEX ,DMX_DAMEMON_ANIM_INDEX
            },
        },
        // Name: Duftmon X
        {
            // Stage: Ultimate
            .conditions = { .next_evolution_time_sec = 172800 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Dukemon X
        {
            // Stage: Ultimate
            .conditions = { .next_evolution_time_sec = 172800 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Duskmon
        {
            // Stage: Child
            .conditions = { .next_evolution_time_sec = 86400 },
            
            .num_animation_indices = 4,
            .animation_indices = {
                DMX_DARK_TYRANOMON_X_ANIM_INDEX ,DMX_OGREMON_X_ANIM_INDEX ,DMX_VELGRMON_ANIM_INDEX ,DMX_NUMEMON_X_ANIM_INDEX
            },
        },
        // Name: Dynasmon X
        {
            // Stage: Ultimate
            .conditions = { .next_evolution_time_sec = 172800 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Ebemon X
        {
            // Stage: Ultimate
            .conditions = { .next_evolution_time_sec = 230400 },
            
            .num_animation_indices = 8,
            .animation_indices = {
                DMX_MAGNAMON_X_ANIM_INDEX ,DMX_GANKOOMON_X_ANIM_INDEX ,DMX_DYNASMON_X_ANIM_INDEX ,DMX_CRANIUMMON_X_ANIM_INDEX ,DMX_LORD_KNIGHTMON_X_ANIM_INDEX ,DMX_DUKEMON_X_ANIM_INDEX ,DMX_ALPHAMON_OURYUKEN_ANIM_INDEX ,DMX_JESMON_GX_ANIM_INDEX
            },
        },
        // Name: Examon
        {
            // Stage: Ultimate
            .conditions = { .next_evolution_time_sec = 172800 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Examon X
        {
            // Stage: Ultimate
            .conditions = { .next_evolution_time_sec = 172800 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Filmon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 115200 },
            
            .num_animation_indices = 7,
            .animation_indices = {
                DMX_METAL_GREYMON_VIRUS_X_ANIM_INDEX ,DMX_TRICERAMON_X_ANIM_INDEX ,DMX_VAMDEMON_X_ANIM_INDEX ,DMX_MEGA_SEADRAMON_X_ANIM_INDEX ,DMX_STIFFILMON_ANIM_INDEX ,DMX_MAMETYRAMON_ANIM_INDEX ,DMX_KAISER_LEOMON_ANIM_INDEX
            },
        },
        // Name: Gabumon X
        {
            // Stage: Child
            .conditions = { .next_evolution_time_sec = 86400 },
            
            .num_animation_indices = 3,
            .animation_indices = {
                DMX_RHINOMON_X_ANIM_INDEX ,DMX_TOBUCATMON_ANIM_INDEX ,DMX_DAMEMON_ANIM_INDEX
            },
        },
        // Name: Gaioumon
        {
            // Stage: Ultimate
            .conditions = { .next_evolution_time_sec = 230400 },
            
            .num_animation_indices = 8,
            .animation_indices = {
                DMX_MAGNAMON_X_ANIM_INDEX ,DMX_GANKOOMON_X_ANIM_INDEX ,DMX_DYNASMON_X_ANIM_INDEX ,DMX_CRANIUMMON_X_ANIM_INDEX ,DMX_LORD_KNIGHTMON_X_ANIM_INDEX ,DMX_DUKEMON_X_ANIM_INDEX ,DMX_ALPHAMON_OURYUKEN_ANIM_INDEX ,DMX_JESMON_GX_ANIM_INDEX
            },
        },
        // Name: Gankoomon X
        {
            // Stage: Ultimate
            .conditions = { .next_evolution_time_sec = 230400 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DMX_JESMON_GX_ANIM_INDEX
            },
        },
        // Name: Garudamon X
        {
            // Stage: Perfect
            .conditions = { .next_evolution_time_sec = 144000 },
            
            .num_animation_indices = 12,
            .animation_indices = {
                DMX_RAPIDMON_X_ANIM_INDEX ,DMX_JUSTIMON_X_ANIM_INDEX ,DMX_ALPHAMON_ANIM_INDEX ,DMX_HOUOUMON_X_ANIM_INDEX ,DMX_TIGER_VESPAMON_ANIM_INDEX ,DMX_GAIOUMON_ANIM_INDEX ,DMX_DINOTIGERMON_ANIM_INDEX ,DMX_HOLYDRAMON_X_ANIM_INDEX ,DMX_EBEMON_X_ANIM_INDEX ,DMX_HEXEBLAUMON_ANIM_INDEX ,DMX_METALLICDRAMON_ANIM_INDEX ,DMX_NOBLE_PUMPMON_ANIM_INDEX
            },
        },
        // Name: Giga Seadramon
        {
            // Stage: Ultimate
            .conditions = { .next_evolution_time_sec = 230400 },
            
            .num_animation_indices = 2,
            .animation_indices = {
                DMX_LEVIAMON_X_ANIM_INDEX ,DMX_BARBAMON_X_ANIM_INDEX
            },
        },
        // Name: Ginryumon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 115200 },
            
            .num_animation_indices = 10,
            .animation_indices = {
                DMX_HISYARYUMON_ANIM_INDEX ,DMX_RIZE_GREYMON_X_ANIM_INDEX ,DMX_MONZAEMON_X_ANIM_INDEX ,DMX_ANGEWOMON_X_ANIM_INDEX ,DMX_ANOMALOCARIMON_X_ANIM_INDEX ,DMX_GRADEMON_ANIM_INDEX ,DMX_MAMEMON_X_ANIM_INDEX ,DMX_CRYS_PALEDRAMON_ANIM_INDEX ,DMX_JAZARICHMON_ANIM_INDEX ,DMX_PUMPMON_ANIM_INDEX
            },
        },
        // Name: Goddramon X
        {
            // Stage: Ultimate
            .conditions = { .next_evolution_time_sec = 230400 },
            
            .num_animation_indices = 8,
            .animation_indices = {
                DMX_ULFORCE_V_DRAMON_X_ANIM_INDEX ,DMX_EXAMON_X_ANIM_INDEX ,DMX_DUFTMON_X_ANIM_INDEX ,DMX_SLEIPMON_X_ANIM_INDEX ,DMX_JESMON_X_ANIM_INDEX ,DMX_OMEGAMON_X_ANIM_INDEX ,DMX_ALPHAMON_OURYUKEN_ANIM_INDEX ,DMX_JESMON_GX_ANIM_INDEX
            },
        },
        // Name: Gomamon X
        {
            // Stage: Child
            .conditions = { .next_evolution_time_sec = 86400 },
            
            .num_animation_indices = 3,
            .animation_indices = {
                DMX_MANTARAYMON_X_ANIM_INDEX ,DMX_KUWAGAMON_X_ANIM_INDEX ,DMX_ALLOMON_X_ANIM_INDEX
            },
        },
        // Name: Grademon
        {
            // Stage: Perfect
            .conditions = { .next_evolution_time_sec = 144000 },
            
            .num_animation_indices = 12,
            .animation_indices = {
                DMX_RAPIDMON_X_ANIM_INDEX ,DMX_JUSTIMON_X_ANIM_INDEX ,DMX_ALPHAMON_ANIM_INDEX ,DMX_HOUOUMON_X_ANIM_INDEX ,DMX_TIGER_VESPAMON_ANIM_INDEX ,DMX_GAIOUMON_ANIM_INDEX ,DMX_DINOTIGERMON_ANIM_INDEX ,DMX_HOLYDRAMON_X_ANIM_INDEX ,DMX_EBEMON_X_ANIM_INDEX ,DMX_HEXEBLAUMON_ANIM_INDEX ,DMX_METALLICDRAMON_ANIM_INDEX ,DMX_NOBLE_PUMPMON_ANIM_INDEX
            },
        },
        // Name: Grand Darcumon
        {
            // Stage: Ultimate
            .conditions = { .next_evolution_time_sec = 172800 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Grand Dracumon
        {
            // Stage: Ultimate
            .conditions = { .next_evolution_time_sec = 172800 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Grandis Kuwagamon
        {
            // Stage: Ultimate
            .conditions = { .next_evolution_time_sec = 230400 },
            
            .num_animation_indices = 2,
            .animation_indices = {
                DMX_LEVIAMON_X_ANIM_INDEX ,DMX_BARBAMON_X_ANIM_INDEX
            },
        },
        // Name: Growmon X
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 115200 },
            
            .num_animation_indices = 4,
            .animation_indices = {
                DMX_MEGALO_GROWMON_X_ANIM_INDEX ,DMX_CHO_HAKKAIMON_ANIM_INDEX ,DMX_METAL_TYRANOMON_X_ANIM_INDEX ,DMX_YATAGARAMON_ANIM_INDEX
            },
        },
        // Name: Gummymon
        {
            // Stage: Baby II
            .conditions = { .next_evolution_time_sec = 43200 },
            
            .num_animation_indices = 4,
            .animation_indices = {
                DMX_TERRIERMON_X_ANIM_INDEX ,DMX_PALMON_X_ANIM_INDEX ,DMX_DORUMON_ANIM_INDEX ,DMX_JAZAMON_ANIM_INDEX
            },
        },
        // Name: Herissmon
        {
            // Stage: Child
            .conditions = { .next_evolution_time_sec = 86400 },
            
            .num_animation_indices = 3,
            .animation_indices = {
                DMX_SANGLOUPMON_ANIM_INDEX ,DMX_TYRANOMON_X_ANIM_INDEX ,DMX_DAMEMON_ANIM_INDEX
            },
        },
        // Name: Hexeblaumon
        {
            // Stage: Ultimate
            .conditions = { .next_evolution_time_sec = 230400 },
            
            .num_animation_indices = 8,
            .animation_indices = {
                DMX_MAGNAMON_X_ANIM_INDEX ,DMX_GANKOOMON_X_ANIM_INDEX ,DMX_DYNASMON_X_ANIM_INDEX ,DMX_CRANIUMMON_X_ANIM_INDEX ,DMX_LORD_KNIGHTMON_X_ANIM_INDEX ,DMX_DUKEMON_X_ANIM_INDEX ,DMX_ALPHAMON_OURYUKEN_ANIM_INDEX ,DMX_JESMON_GX_ANIM_INDEX
            },
        },
        // Name: Hisyaryumon
        {
            // Stage: Perfect
            .conditions = { .next_evolution_time_sec = 144000 },
            
            .num_animation_indices = 12,
            .animation_indices = {
                DMX_CHERUBIMON_VIRTUE_X_ANIM_INDEX ,DMX_GODDRAMON_X_ANIM_INDEX ,DMX_OURYUMON_ANIM_INDEX ,DMX_OFANIMON_X_ANIM_INDEX ,DMX_PLESIOMON_X_ANIM_INDEX ,DMX_GAIOUMON_ANIM_INDEX ,DMX_DINOTIGERMON_ANIM_INDEX ,DMX_HOLYDRAMON_X_ANIM_INDEX ,DMX_EBEMON_X_ANIM_INDEX ,DMX_HEXEBLAUMON_ANIM_INDEX ,DMX_METALLICDRAMON_ANIM_INDEX ,DMX_NOBLE_PUMPMON_ANIM_INDEX
            },
        },
        // Name: Holydramon X
        {
            // Stage: Ultimate
            .conditions = { .next_evolution_time_sec = 230400 },
            
            .num_animation_indices = 8,
            .animation_indices = {
                DMX_MAGNAMON_X_ANIM_INDEX ,DMX_GANKOOMON_X_ANIM_INDEX ,DMX_DYNASMON_X_ANIM_INDEX ,DMX_CRANIUMMON_X_ANIM_INDEX ,DMX_LORD_KNIGHTMON_X_ANIM_INDEX ,DMX_DUKEMON_X_ANIM_INDEX ,DMX_ALPHAMON_OURYUKEN_ANIM_INDEX ,DMX_JESMON_GX_ANIM_INDEX
            },
        },
        // Name: Hououmon X
        {
            // Stage: Ultimate
            .conditions = { .next_evolution_time_sec = 230400 },
            
            .num_animation_indices = 8,
            .animation_indices = {
                DMX_MAGNAMON_X_ANIM_INDEX ,DMX_GANKOOMON_X_ANIM_INDEX ,DMX_DYNASMON_X_ANIM_INDEX ,DMX_CRANIUMMON_X_ANIM_INDEX ,DMX_LORD_KNIGHTMON_X_ANIM_INDEX ,DMX_DUKEMON_X_ANIM_INDEX ,DMX_ALPHAMON_OURYUKEN_ANIM_INDEX ,DMX_JESMON_GX_ANIM_INDEX
            },
        },
        // Name: Impmon X
        {
            // Stage: Child
            .conditions = { .next_evolution_time_sec = 86400 },
            
            .num_animation_indices = 4,
            .animation_indices = {
                DMX_OGREMON_X_ANIM_INDEX ,DMX_SEADRAMON_X_ANIM_INDEX ,DMX_NUMEMON_X_ANIM_INDEX ,DMX_ALLOMON_X_ANIM_INDEX
            },
        },
        // Name: Jararchimon
        {
            // Stage: Perfect
            .conditions = { .next_evolution_time_sec = 144000 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Jazamon
        {
            // Stage: Child
            .conditions = { .next_evolution_time_sec = 86400 },
            
            .num_animation_indices = 8,
            .animation_indices = {
                DMX_SIESAMON_X_ANIM_INDEX ,DMX_MERAMON_X_ANIM_INDEX ,DMX_DORUGAMON_ANIM_INDEX ,DMX_PTERANOMON_X_ANIM_INDEX ,DMX_TOGEMON_X_ANIM_INDEX ,DMX_OMEKAMON_ANIM_INDEX ,DMX_PALEDRAMON_ANIM_INDEX ,DMX_JAZARDMON_ANIM_INDEX
            },
        },
        // Name: Jazardmon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 115200 },
            
            .num_animation_indices = 10,
            .animation_indices = {
                DMX_OMEGA_SHOUTMON_X_ANIM_INDEX ,DMX_CYBERDRAMON_X_ANIM_INDEX ,DMX_DORUGUREMON_ANIM_INDEX ,DMX_GARUDAMON_X_ANIM_INDEX ,DMX_CANNONBEEMON_ANIM_INDEX ,DMX_GRADEMON_ANIM_INDEX ,DMX_MAMEMON_X_ANIM_INDEX ,DMX_CRYS_PALEDRAMON_ANIM_INDEX ,DMX_JAZARICHMON_ANIM_INDEX ,DMX_PUMPMON_ANIM_INDEX
            },
        },
        // Name: Jazarichmon
        {
            // Stage: Perfect
            .conditions = { .next_evolution_time_sec = 144000 },
            
            .num_animation_indices = 12,
            .animation_indices = {
                DMX_RAPIDMON_X_ANIM_INDEX ,DMX_JUSTIMON_X_ANIM_INDEX ,DMX_ALPHAMON_ANIM_INDEX ,DMX_HOUOUMON_X_ANIM_INDEX ,DMX_TIGER_VESPAMON_ANIM_INDEX ,DMX_GAIOUMON_ANIM_INDEX ,DMX_DINOTIGERMON_ANIM_INDEX ,DMX_HOLYDRAMON_X_ANIM_INDEX ,DMX_EBEMON_X_ANIM_INDEX ,DMX_HEXEBLAUMON_ANIM_INDEX ,DMX_METALLICDRAMON_ANIM_INDEX ,DMX_NOBLE_PUMPMON_ANIM_INDEX
            },
        },
        // Name: Jesmon GX
        {
            // Stage: Ultimate
            .conditions = { .next_evolution_time_sec = 172800 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Jesmon X
        {
            // Stage: Ultimate
            .conditions = { .next_evolution_time_sec = 230400 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DMX_ALPHAMON_ANIM_INDEX
            },
        },
        // Name: Justimon X
        {
            // Stage: Ultimate
            .conditions = { .next_evolution_time_sec = 230400 },
            
            .num_animation_indices = 8,
            .animation_indices = {
                DMX_MAGNAMON_X_ANIM_INDEX ,DMX_GANKOOMON_X_ANIM_INDEX ,DMX_DYNASMON_X_ANIM_INDEX ,DMX_CRANIUMMON_X_ANIM_INDEX ,DMX_LORD_KNIGHTMON_X_ANIM_INDEX ,DMX_DUKEMON_X_ANIM_INDEX ,DMX_ALPHAMON_OURYUKEN_ANIM_INDEX ,DMX_JESMON_GX_ANIM_INDEX
            },
        },
        // Name: Kaiser Leomon
        {
            // Stage: Perfect
            .conditions = { .next_evolution_time_sec = 144000 },
            
            .num_animation_indices = 7,
            .animation_indices = {
                DMX_OFANIMON_FALLDOWN_MODE_X_ANIM_INDEX ,DMX_ULTIMATE_BRACHIOMON_ANIM_INDEX ,DMX_CHERUBIMON_VICE_X_ANIM_INDEX ,DMX_DINOREXMON_ANIM_INDEX ,DMX_RAIHIMON_ANIM_INDEX ,DMX_BAGRAMON_ANIM_INDEX ,DMX_BEEL_STARMON_X_ANIM_INDEX
            },
        },
        // Name: Keemon
        {
            // Stage: Baby I
            .conditions = { .next_evolution_time_sec = 600 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Keramon X
        {
            // Stage: Child
            .conditions = { .next_evolution_time_sec = 86400 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DMX_DIABLOMON_X_ANIM_INDEX
            },
        },
        // Name: Kiimon
        {
            // Stage: Baby I
            .conditions = { .next_evolution_time_sec = 600 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DMX_YAAMON_ANIM_INDEX
            },
        },
        // Name: Kokuwamon X
        {
            // Stage: Child
            .conditions = { .next_evolution_time_sec = 86400 },
            
            .num_animation_indices = 5,
            .animation_indices = {
                DMX_KUWAGAMON_X_ANIM_INDEX ,DMX_FILMON_ANIM_INDEX ,DMX_NUMEMON_X_ANIM_INDEX ,DMX_VELGRMON_ANIM_INDEX ,DMX_ALLOMON_X_ANIM_INDEX
            },
        },
        // Name: Kuwagamon X
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 115200 },
            
            .num_animation_indices = 3,
            .animation_indices = {
                DMX_OKUWAMON_X_ANIM_INDEX ,DMX_MAMETYRAMON_ANIM_INDEX ,DMX_MAMMON_X_ANIM_INDEX
            },
        },
        // Name: Lady Devimon X
        {
            // Stage: Perfect
            .conditions = { .next_evolution_time_sec = 144000 },
            
            .num_animation_indices = 4,
            .animation_indices = {
                DMX_OFANIMON_FALLDOWN_MODE_X_ANIM_INDEX ,DMX_GRANDIS_KUWAGAMON_ANIM_INDEX ,DMX_ROSEMON_X_ANIM_INDEX ,DMX_BEEL_STARMON_X_ANIM_INDEX
            },
        },
        // Name: Leomon X
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 115200 },
            
            .num_animation_indices = 4,
            .animation_indices = {
                DMX_CERBERUMON_X_ANIM_INDEX ,DMX_METAL_GREYMON_X_ANIM_INDEX ,DMX_METAL_TYRANOMON_X_ANIM_INDEX ,DMX_YATAGARAMON_ANIM_INDEX
            },
        },
        // Name: Leviamon X
        {
            // Stage: Ultimate
            .conditions = { .next_evolution_time_sec = 172800 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Lilimon X
        {
            // Stage: Perfect
            .conditions = { .next_evolution_time_sec = 144000 },
            
            .num_animation_indices = 4,
            .animation_indices = {
                DMX_RAFFLESIMON_ANIM_INDEX ,DMX_BEEL_STARMON_X_ANIM_INDEX ,DMX_VALDURMON_ANIM_INDEX ,DMX_PLATINUM_NUMEMON_ANIM_INDEX
            },
        },
        // Name: Lilithmon X
        {
            // Stage: Ultimate
            .conditions = { .next_evolution_time_sec = 172800 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Lopmon X
        {
            // Stage: Child
            .conditions = { .next_evolution_time_sec = 86400 },
            
            .num_animation_indices = 8,
            .animation_indices = {
                DMX_PEGASMON_X_ANIM_INDEX ,DMX_WIZARMON_X_ANIM_INDEX ,DMX_GINRYUMON_ANIM_INDEX ,DMX_TAILMON_X_ANIM_INDEX ,DMX_TYLOMON_X_ANIM_INDEX ,DMX_OMEKAMON_ANIM_INDEX ,DMX_PALEDRAMON_ANIM_INDEX ,DMX_JAZARDMON_ANIM_INDEX
            },
        },
        // Name: Lord Kightmon X
        {
            // Stage: Ultimate
            .conditions = { .next_evolution_time_sec = 172800 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Lord Knightmon X
        {
            // Stage: Ultimate
            .conditions = { .next_evolution_time_sec = 172800 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Lucemon X
        {
            // Stage: Ultimate
            .conditions = { .next_evolution_time_sec = 172800 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Magidramon X
        {
            // Stage: Ultimate
            .conditions = { .next_evolution_time_sec = 172800 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Magnamon X
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 115200 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Mamemon X
        {
            // Stage: Perfect
            .conditions = { .next_evolution_time_sec = 144000 },
            
            .num_animation_indices = 12,
            .animation_indices = {
                DMX_RAPIDMON_X_ANIM_INDEX ,DMX_JUSTIMON_X_ANIM_INDEX ,DMX_ALPHAMON_ANIM_INDEX ,DMX_HOUOUMON_X_ANIM_INDEX ,DMX_TIGER_VESPAMON_ANIM_INDEX ,DMX_GAIOUMON_ANIM_INDEX ,DMX_DINOTIGERMON_ANIM_INDEX ,DMX_HOLYDRAMON_X_ANIM_INDEX ,DMX_EBEMON_X_ANIM_INDEX ,DMX_HEXEBLAUMON_ANIM_INDEX ,DMX_METALLICDRAMON_ANIM_INDEX ,DMX_NOBLE_PUMPMON_ANIM_INDEX
            },
        },
        // Name: Mametyramon
        {
            // Stage: Perfect
            .conditions = { .next_evolution_time_sec = 144000 },
            
            .num_animation_indices = 9,
            .animation_indices = {
                DMX_PRINCE_MAMEMON_X_ANIM_INDEX ,DMX_BLACK_WAR_GREYMON_X_ANIM_INDEX ,DMX_DARK_KNIGHTMON_X_ANIM_INDEX ,DMX_METAL_PIRANIMON_ANIM_INDEX ,DMX_BAGRAMON_ANIM_INDEX ,DMX_RAIHIMON_ANIM_INDEX ,DMX_CHAOSDRAMON_X_ANIM_INDEX ,DMX_RASENMON_FURY_MODE_ANIM_INDEX ,DMX_ROSEMON_X_ANIM_INDEX
            },
        },
        // Name: Mame Tyramon
        {
            // Stage: Perfect
            .conditions = { .next_evolution_time_sec = 144000 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Mammon X
        {
            // Stage: Perfect
            .conditions = { .next_evolution_time_sec = 144000 },
            
            .num_animation_indices = 5,
            .animation_indices = {
                DMX_GRANDIS_KUWAGAMON_ANIM_INDEX ,DMX_OFANIMON_FALLDOWN_MODE_X_ANIM_INDEX ,DMX_SKULL_MAMMON_X_ANIM_INDEX ,DMX_BEEL_STARMON_X_ANIM_INDEX ,DMX_ROSEMON_X_ANIM_INDEX
            },
        },
        // Name: Mantaraymon X
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 115200 },
            
            .num_animation_indices = 3,
            .animation_indices = {
                DMX_LADY_DEVIMON_X_ANIM_INDEX ,DMX_MAMETYRAMON_ANIM_INDEX ,DMX_OKUWAMON_X_ANIM_INDEX
            },
        },
        // Name: Megalo Growmon X
        {
            // Stage: Perfect
            .conditions = { .next_evolution_time_sec = 144000 },
            
            .num_animation_indices = 5,
            .animation_indices = {
                DMX_MEGIDRAMON_X_ANIM_INDEX ,DMX_CRANIUMMON_X_ANIM_INDEX ,DMX_JESMON_X_ANIM_INDEX ,DMX_BELIAL_VAMDEMON_ANIM_INDEX ,DMX_PLATINUM_NUMEMON_ANIM_INDEX
            },
        },
        // Name: Mega Seadramon X
        {
            // Stage: Perfect
            .conditions = { .next_evolution_time_sec = 144000 },
            
            .num_animation_indices = 3,
            .animation_indices = {
                DMX_GIGA_SEADRAMON_ANIM_INDEX ,DMX_CHAOSDRAMON_X_ANIM_INDEX ,DMX_SKULL_MAMMON_X_ANIM_INDEX
            },
        },
        // Name: Megidramon X
        {
            // Stage: Ultimate
            .conditions = { .next_evolution_time_sec = 230400 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DMX_DUKEMON_X_ANIM_INDEX
            },
        },
        // Name: Mephismon X
        {
            // Stage: Perfect
            .conditions = { .next_evolution_time_sec = 144000 },
            
            .num_animation_indices = 4,
            .animation_indices = {
                DMX_CHERUBIMON_VICE_X_ANIM_INDEX ,DMX_DINOREXMON_ANIM_INDEX ,DMX_ROSEMON_X_ANIM_INDEX ,DMX_BEEL_STARMON_X_ANIM_INDEX
            },
        },
        // Name: Meramon X
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 115200 },
            
            .num_animation_indices = 10,
            .animation_indices = {
                DMX_OMEGA_SHOUTMON_X_ANIM_INDEX ,DMX_CYBERDRAMON_X_ANIM_INDEX ,DMX_DORUGUREMON_ANIM_INDEX ,DMX_GARUDAMON_X_ANIM_INDEX ,DMX_CANNONBEEMON_ANIM_INDEX ,DMX_GRADEMON_ANIM_INDEX ,DMX_MAMEMON_X_ANIM_INDEX ,DMX_CRYS_PALEDRAMON_ANIM_INDEX ,DMX_JAZARICHMON_ANIM_INDEX ,DMX_PUMPMON_ANIM_INDEX
            },
        },
        // Name: Metal Fantomon
        {
            // Stage: Perfect
            .conditions = { .next_evolution_time_sec = 144000 },
            
            .num_animation_indices = 5,
            .animation_indices = {
                DMX_DINOREXMON_ANIM_INDEX ,DMX_CHAOSDRAMON_X_ANIM_INDEX ,DMX_SKULL_MAMMON_X_ANIM_INDEX ,DMX_METAL_PIRANIMON_ANIM_INDEX ,DMX_DARK_KNIGHTMON_X_ANIM_INDEX
            },
        },
        // Name: Metal Garurumon X
        {
            // Stage: Ultimate
            .conditions = { .next_evolution_time_sec = 230400 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DMX_OMEGAMON_X_ANIM_INDEX
            },
        },
        // Name: Metal Greymon (Virus) X
        {
            // Stage: Perfect
            .conditions = { .next_evolution_time_sec = 144000 },
            
            .num_animation_indices = 6,
            .animation_indices = {
                DMX_BLACK_WAR_GREYMON_X_ANIM_INDEX ,DMX_ULTIMATE_BRACHIOMON_ANIM_INDEX ,DMX_SKULL_MAMMON_X_ANIM_INDEX ,DMX_PRINCE_MAMEMON_X_ANIM_INDEX ,DMX_METAL_PIRANIMON_ANIM_INDEX ,DMX_CHAOSDRAMON_X_ANIM_INDEX
            },
        },
        // Name: Metal Greymon X
        {
            // Stage: Perfect
            .conditions = { .next_evolution_time_sec = 144000 },
            
            .num_animation_indices = 4,
            .animation_indices = {
                DMX_WAR_GREYMON_X_ANIM_INDEX ,DMX_JESMON_X_ANIM_INDEX ,DMX_VALDURMON_ANIM_INDEX ,DMX_PLATINUM_NUMEMON_ANIM_INDEX
            },
        },
        // Name: Metallicdramon
        {
            // Stage: Ultimate
            .conditions = { .next_evolution_time_sec = 230400 },
            
            .num_animation_indices = 8,
            .animation_indices = {
                DMX_MAGNAMON_X_ANIM_INDEX ,DMX_GANKOOMON_X_ANIM_INDEX ,DMX_DYNASMON_X_ANIM_INDEX ,DMX_CRANIUMMON_X_ANIM_INDEX ,DMX_LORD_KNIGHTMON_X_ANIM_INDEX ,DMX_DUKEMON_X_ANIM_INDEX ,DMX_ALPHAMON_OURYUKEN_ANIM_INDEX ,DMX_JESMON_GX_ANIM_INDEX
            },
        },
        // Name: Metal Piranimon
        {
            // Stage: Ultimate
            .conditions = { .next_evolution_time_sec = 230400 },
            
            .num_animation_indices = 3,
            .animation_indices = {
                DMX_LILITHMON_X_ANIM_INDEX ,DMX_BELPHEMON_X_ANIM_INDEX ,DMX_BARBAMON_X_ANIM_INDEX
            },
        },
        // Name: Metal Tyranomon X
        {
            // Stage: Perfect
            .conditions = { .next_evolution_time_sec = 144000 },
            
            .num_animation_indices = 8,
            .animation_indices = {
                DMX_BEELZEBUMON_X_ANIM_INDEX ,DMX_WAR_GREYMON_X_ANIM_INDEX ,DMX_SLEIPMON_X_ANIM_INDEX ,DMX_MEGIDRAMON_X_ANIM_INDEX ,DMX_METAL_GARURUMON_X_ANIM_INDEX ,DMX_CRANIUMMON_X_ANIM_INDEX ,DMX_BELIAL_VAMDEMON_ANIM_INDEX ,DMX_PLATINUM_NUMEMON_ANIM_INDEX
            },
        },
        // Name: Minervamon X
        {
            // Stage: Ultimate
            .conditions = { .next_evolution_time_sec = 172800 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Monzaemon X
        {
            // Stage: Perfect
            .conditions = { .next_evolution_time_sec = 144000 },
            
            .num_animation_indices = 12,
            .animation_indices = {
                DMX_CHERUBIMON_VIRTUE_X_ANIM_INDEX ,DMX_GODDRAMON_X_ANIM_INDEX ,DMX_OURYUMON_ANIM_INDEX ,DMX_OFANIMON_X_ANIM_INDEX ,DMX_PLESIOMON_X_ANIM_INDEX ,DMX_GAIOUMON_ANIM_INDEX ,DMX_DINOTIGERMON_ANIM_INDEX ,DMX_HOLYDRAMON_X_ANIM_INDEX ,DMX_EBEMON_X_ANIM_INDEX ,DMX_HEXEBLAUMON_ANIM_INDEX ,DMX_METALLICDRAMON_ANIM_INDEX ,DMX_NOBLE_PUMPMON_ANIM_INDEX
            },
        },
        // Name: Nefertimon X
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 115200 },
            
            .num_animation_indices = 3,
            .animation_indices = {
                DMX_MEPHISMON_X_ANIM_INDEX ,DMX_MAMETYRAMON_ANIM_INDEX ,DMX_MEGA_SEADRAMON_X_ANIM_INDEX
            },
        },
        // Name: Noble Pumpmon
        {
            // Stage: Ultimate
            .conditions = { .next_evolution_time_sec = 172800 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Numemon X
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 115200 },
            
            .num_animation_indices = 10,
            .animation_indices = {
                DMX_METAL_GREYMON_VIRUS_X_ANIM_INDEX ,DMX_OKUWAMON_X_ANIM_INDEX ,DMX_LADY_DEVIMON_X_ANIM_INDEX ,DMX_TRICERAMON_X_ANIM_INDEX ,DMX_VAMDEMON_X_ANIM_INDEX ,DMX_MEGA_SEADRAMON_X_ANIM_INDEX ,DMX_MEPHISMON_X_ANIM_INDEX ,DMX_METAL_FANTOMON_ANIM_INDEX ,DMX_STIFFILMON_ANIM_INDEX ,DMX_KAISER_LEOMON_ANIM_INDEX
            },
        },
        // Name: Ofanimon Falldown Mode
        {
            // Stage: Ultimate
            .conditions = { .next_evolution_time_sec = 172800 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Ofanimon Falldown Mode X
        {
            // Stage: Ultimate
            .conditions = { .next_evolution_time_sec = 230400 },
            
            .num_animation_indices = 2,
            .animation_indices = {
                DMX_LILITHMON_X_ANIM_INDEX ,DMX_BARBAMON_X_ANIM_INDEX
            },
        },
        // Name: Ofanimon X
        {
            // Stage: Ultimate
            .conditions = { .next_evolution_time_sec = 230400 },
            
            .num_animation_indices = 8,
            .animation_indices = {
                DMX_ULFORCE_V_DRAMON_X_ANIM_INDEX ,DMX_EXAMON_X_ANIM_INDEX ,DMX_DUFTMON_X_ANIM_INDEX ,DMX_SLEIPMON_X_ANIM_INDEX ,DMX_JESMON_X_ANIM_INDEX ,DMX_OMEGAMON_X_ANIM_INDEX ,DMX_ALPHAMON_OURYUKEN_ANIM_INDEX ,DMX_JESMON_GX_ANIM_INDEX
            },
        },
        // Name: Ogremon X
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 115200 },
            
            .num_animation_indices = 4,
            .animation_indices = {
                DMX_VAMDEMON_X_ANIM_INDEX ,DMX_MAMMON_X_ANIM_INDEX ,DMX_METAL_FANTOMON_ANIM_INDEX ,DMX_MAMETYRAMON_ANIM_INDEX
            },
        },
        // Name: Ogudomon X
        {
            // Stage: Ultimate
            .conditions = { .next_evolution_time_sec = 172800 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Okuwamon X
        {
            // Stage: Perfect
            .conditions = { .next_evolution_time_sec = 144000 },
            
            .num_animation_indices = 4,
            .animation_indices = {
                DMX_GRANDIS_KUWAGAMON_ANIM_INDEX ,DMX_ROSEMON_X_ANIM_INDEX ,DMX_BEEL_STARMON_X_ANIM_INDEX ,DMX_SKULL_MAMMON_X_ANIM_INDEX
            },
        },
        // Name: Omegamon X
        {
            // Stage: Ultimate
            .conditions = { .next_evolution_time_sec = 172800 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Omega Shoutmon X
        {
            // Stage: Perfect
            .conditions = { .next_evolution_time_sec = 144000 },
            
            .num_animation_indices = 12,
            .animation_indices = {
                DMX_RAPIDMON_X_ANIM_INDEX ,DMX_JUSTIMON_X_ANIM_INDEX ,DMX_ALPHAMON_ANIM_INDEX ,DMX_HOUOUMON_X_ANIM_INDEX ,DMX_TIGER_VESPAMON_ANIM_INDEX ,DMX_GAIOUMON_ANIM_INDEX ,DMX_DINOTIGERMON_ANIM_INDEX ,DMX_HOLYDRAMON_X_ANIM_INDEX ,DMX_EBEMON_X_ANIM_INDEX ,DMX_HEXEBLAUMON_ANIM_INDEX ,DMX_METALLICDRAMON_ANIM_INDEX ,DMX_NOBLE_PUMPMON_ANIM_INDEX
            },
        },
        // Name: Omekamon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 115200 },
            
            .num_animation_indices = 10,
            .animation_indices = {
                DMX_OMEGA_SHOUTMON_X_ANIM_INDEX ,DMX_CYBERDRAMON_X_ANIM_INDEX ,DMX_DORUGUREMON_ANIM_INDEX ,DMX_GARUDAMON_X_ANIM_INDEX ,DMX_CANNONBEEMON_ANIM_INDEX ,DMX_GRADEMON_ANIM_INDEX ,DMX_MAMEMON_X_ANIM_INDEX ,DMX_CRYS_PALEDRAMON_ANIM_INDEX ,DMX_JAZARICHMON_ANIM_INDEX ,DMX_PUMPMON_ANIM_INDEX
            },
        },
        // Name: Ophanimon Falldown Mode
        {
            // Stage: Ultimate
            .conditions = { .next_evolution_time_sec = 172800 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Ophanimon X
        {
            // Stage: Ultimate
            .conditions = { .next_evolution_time_sec = 172800 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Otamamon X
        {
            // Stage: Child
            .conditions = { .next_evolution_time_sec = 86400 },
            
            .num_animation_indices = 5,
            .animation_indices = {
                DMX_SEADRAMON_X_ANIM_INDEX ,DMX_FILMON_ANIM_INDEX ,DMX_NUMEMON_X_ANIM_INDEX ,DMX_VELGRMON_ANIM_INDEX ,DMX_ALLOMON_X_ANIM_INDEX
            },
        },
        // Name: Ouryumon
        {
            // Stage: Ultimate
            .conditions = { .next_evolution_time_sec = 230400 },
            
            .num_animation_indices = 8,
            .animation_indices = {
                DMX_ULFORCE_V_DRAMON_X_ANIM_INDEX ,DMX_EXAMON_X_ANIM_INDEX ,DMX_DUFTMON_X_ANIM_INDEX ,DMX_SLEIPMON_X_ANIM_INDEX ,DMX_JESMON_X_ANIM_INDEX ,DMX_OMEGAMON_X_ANIM_INDEX ,DMX_ALPHAMON_OURYUKEN_ANIM_INDEX ,DMX_JESMON_GX_ANIM_INDEX
            },
        },
        // Name: Paledramon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 115200 },
            
            .num_animation_indices = 10,
            .animation_indices = {
                DMX_OMEGA_SHOUTMON_X_ANIM_INDEX ,DMX_CYBERDRAMON_X_ANIM_INDEX ,DMX_DORUGUREMON_ANIM_INDEX ,DMX_GARUDAMON_X_ANIM_INDEX ,DMX_CANNONBEEMON_ANIM_INDEX ,DMX_GRADEMON_ANIM_INDEX ,DMX_MAMEMON_X_ANIM_INDEX ,DMX_CRYS_PALEDRAMON_ANIM_INDEX ,DMX_JAZARICHMON_ANIM_INDEX ,DMX_PUMPMON_ANIM_INDEX
            },
        },
        // Name: Palmon X
        {
            // Stage: Child
            .conditions = { .next_evolution_time_sec = 86400 },
            
            .num_animation_indices = 8,
            .animation_indices = {
                DMX_TOGEMON_X_ANIM_INDEX ,DMX_SIESAMON_X_ANIM_INDEX ,DMX_MERAMON_X_ANIM_INDEX ,DMX_DORUGAMON_ANIM_INDEX ,DMX_PTERANOMON_X_ANIM_INDEX ,DMX_OMEKAMON_ANIM_INDEX ,DMX_PALEDRAMON_ANIM_INDEX ,DMX_JAZARDMON_ANIM_INDEX
            },
        },
        // Name: Pegasmon X
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 115200 },
            
            .num_animation_indices = 9,
            .animation_indices = {
                DMX_RIZE_GREYMON_X_ANIM_INDEX ,DMX_MONZAEMON_X_ANIM_INDEX ,DMX_ANGEWOMON_X_ANIM_INDEX ,DMX_ANOMALOCARIMON_X_ANIM_INDEX ,DMX_GRADEMON_ANIM_INDEX ,DMX_MAMEMON_X_ANIM_INDEX ,DMX_CRYS_PALEDRAMON_ANIM_INDEX ,DMX_JAZARICHMON_ANIM_INDEX ,DMX_PUMPMON_ANIM_INDEX
            },
        },
        // Name: Platinum Numemon
        {
            // Stage: Ultimate
            .conditions = { .next_evolution_time_sec = 230400 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DMX_OMEGAMON_X_ANIM_INDEX
            },
        },
        // Name: Plesiomon X
        {
            // Stage: Ultimate
            .conditions = { .next_evolution_time_sec = 230400 },
            
            .num_animation_indices = 8,
            .animation_indices = {
                DMX_ULFORCE_V_DRAMON_X_ANIM_INDEX ,DMX_EXAMON_X_ANIM_INDEX ,DMX_DUFTMON_X_ANIM_INDEX ,DMX_SLEIPMON_X_ANIM_INDEX ,DMX_JESMON_X_ANIM_INDEX ,DMX_OMEGAMON_X_ANIM_INDEX ,DMX_ALPHAMON_OURYUKEN_ANIM_INDEX ,DMX_JESMON_GX_ANIM_INDEX
            },
        },
        // Name: Plotmon X
        {
            // Stage: Child
            .conditions = { .next_evolution_time_sec = 86400 },
            
            .num_animation_indices = 3,
            .animation_indices = {
                DMX_NEFERTIMON_X_ANIM_INDEX ,DMX_SEADRAMON_X_ANIM_INDEX ,DMX_ALLOMON_X_ANIM_INDEX
            },
        },
        // Name: Prince Mamemon X
        {
            // Stage: Ultimate
            .conditions = { .next_evolution_time_sec = 230400 },
            
            .num_animation_indices = 3,
            .animation_indices = {
                DMX_DEMON_X_ANIM_INDEX ,DMX_LUCEMON_X_ANIM_INDEX ,DMX_DIABLOMON_X_ANIM_INDEX
            },
        },
        // Name: Pteranmon X
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 115200 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Pteranomon X
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 115200 },
            
            .num_animation_indices = 10,
            .animation_indices = {
                DMX_OMEGA_SHOUTMON_X_ANIM_INDEX ,DMX_CYBERDRAMON_X_ANIM_INDEX ,DMX_DORUGUREMON_ANIM_INDEX ,DMX_GARUDAMON_X_ANIM_INDEX ,DMX_CANNONBEEMON_ANIM_INDEX ,DMX_GRADEMON_ANIM_INDEX ,DMX_MAMEMON_X_ANIM_INDEX ,DMX_CRYS_PALEDRAMON_ANIM_INDEX ,DMX_JAZARICHMON_ANIM_INDEX ,DMX_PUMPMON_ANIM_INDEX
            },
        },
        // Name: Pumpmon
        {
            // Stage: Perfect
            .conditions = { .next_evolution_time_sec = 144000 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DMX_NOBLE_PUMPMON_ANIM_INDEX
            },
        },
        // Name: Puttimon
        {
            // Stage: Baby I
            .conditions = { .next_evolution_time_sec = 600 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DMX_TOKOMON_X_ANIM_INDEX
            },
        },
        // Name: Rafflesimon
        {
            // Stage: Ultimate
            .conditions = { .next_evolution_time_sec = 230400 },
            
            .num_animation_indices = 2,
            .animation_indices = {
                DMX_MINERVAMON_X_ANIM_INDEX ,DMX_LORD_KNIGHTMON_X_ANIM_INDEX
            },
        },
        // Name: Raihimon
        {
            // Stage: Perfect
            .conditions = { .next_evolution_time_sec = 144000 },
            
            .num_animation_indices = 2,
            .animation_indices = {
                DMX_ANCIENT_SPHINXMON_ANIM_INDEX ,DMX_BEELZEBUMON_X_ANIM_INDEX
            },
        },
        // Name: Rapidmon X
        {
            // Stage: Ultimate
            .conditions = { .next_evolution_time_sec = 230400 },
            
            .num_animation_indices = 8,
            .animation_indices = {
                DMX_MAGNAMON_X_ANIM_INDEX ,DMX_GANKOOMON_X_ANIM_INDEX ,DMX_DYNASMON_X_ANIM_INDEX ,DMX_CRANIUMMON_X_ANIM_INDEX ,DMX_LORD_KNIGHTMON_X_ANIM_INDEX ,DMX_DUKEMON_X_ANIM_INDEX ,DMX_ALPHAMON_OURYUKEN_ANIM_INDEX ,DMX_JESMON_GX_ANIM_INDEX
            },
        },
        // Name: Rasenmon Fury Mode
        {
            // Stage: Ultimate
            .conditions = { .next_evolution_time_sec = 230400 },
            
            .num_animation_indices = 2,
            .animation_indices = {
                DMX_RASENMON_ANIM_INDEX ,DMX_DIABLOMON_X_ANIM_INDEX
            },
        },
        // Name: Rasenmon
        {
            // Stage: Ultimate
            .conditions = { .next_evolution_time_sec = 172800 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Rekamon X
        {
            // Stage: Child
            .conditions = { .next_evolution_time_sec = 86400 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Renamon X
        {
            // Stage: Child
            .conditions = { .next_evolution_time_sec = 86400 },
            
            .num_animation_indices = 3,
            .animation_indices = {
                DMX_LEOMON_X_ANIM_INDEX ,DMX_SANGLOUPMON_ANIM_INDEX ,DMX_DAMEMON_ANIM_INDEX
            },
        },
        // Name: Rhinomon X
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 115200 },
            
            .num_animation_indices = 3,
            .animation_indices = {
                DMX_WERE_GARURUMON_X_ANIM_INDEX ,DMX_MEGALO_GROWMON_X_ANIM_INDEX ,DMX_YATAGARAMON_ANIM_INDEX
            },
        },
        // Name: Rize Greymon X
        {
            // Stage: Perfect
            .conditions = { .next_evolution_time_sec = 144000 },
            
            .num_animation_indices = 12,
            .animation_indices = {
                DMX_CHERUBIMON_VIRTUE_X_ANIM_INDEX ,DMX_GODDRAMON_X_ANIM_INDEX ,DMX_OURYUMON_ANIM_INDEX ,DMX_OFANIMON_X_ANIM_INDEX ,DMX_PLESIOMON_X_ANIM_INDEX ,DMX_GAIOUMON_ANIM_INDEX ,DMX_DINOTIGERMON_ANIM_INDEX ,DMX_HOLYDRAMON_X_ANIM_INDEX ,DMX_EBEMON_X_ANIM_INDEX ,DMX_HEXEBLAUMON_ANIM_INDEX ,DMX_METALLICDRAMON_ANIM_INDEX ,DMX_NOBLE_PUMPMON_ANIM_INDEX
            },
        },
        // Name: Rosemon X
        {
            // Stage: Ultimate
            .conditions = { .next_evolution_time_sec = 230400 },
            
            .num_animation_indices = 3,
            .animation_indices = {
                DMX_LILITHMON_X_ANIM_INDEX ,DMX_BELPHEMON_X_ANIM_INDEX ,DMX_BARBAMON_X_ANIM_INDEX
            },
        },
        // Name: Ryudamon
        {
            // Stage: Child
            .conditions = { .next_evolution_time_sec = 86400 },
            
            .num_animation_indices = 7,
            .animation_indices = {
                DMX_GINRYUMON_ANIM_INDEX ,DMX_WIZARMON_X_ANIM_INDEX ,DMX_TAILMON_X_ANIM_INDEX ,DMX_TYLOMON_X_ANIM_INDEX ,DMX_OMEKAMON_ANIM_INDEX ,DMX_PALEDRAMON_ANIM_INDEX ,DMX_JAZARDMON_ANIM_INDEX
            },
        },
        // Name: Sakuyamon X
        {
            // Stage: Ultimate
            .conditions = { .next_evolution_time_sec = 230400 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DMX_DUKEMON_X_ANIM_INDEX
            },
        },
        // Name: Sangloupmon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 115200 },
            
            .num_animation_indices = 2,
            .animation_indices = {
                DMX_CERBERUMON_X_ANIM_INDEX ,DMX_SKULL_BALUCHIMON_ANIM_INDEX
            },
        },
        // Name: Sangoupmon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 115200 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Seadramon X
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 115200 },
            
            .num_animation_indices = 3,
            .animation_indices = {
                DMX_MEGA_SEADRAMON_X_ANIM_INDEX ,DMX_MAMETYRAMON_ANIM_INDEX ,DMX_MAMMON_X_ANIM_INDEX
            },
        },
        // Name: Shakomon X
        {
            // Stage: Child
            .conditions = { .next_evolution_time_sec = 86400 },
            
            .num_animation_indices = 7,
            .animation_indices = {
                DMX_WIZARMON_X_ANIM_INDEX ,DMX_GINRYUMON_ANIM_INDEX ,DMX_TAILMON_X_ANIM_INDEX ,DMX_TYLOMON_X_ANIM_INDEX ,DMX_OMEKAMON_ANIM_INDEX ,DMX_PALEDRAMON_ANIM_INDEX ,DMX_JAZARDMON_ANIM_INDEX
            },
        },
        // Name: Siesamon X
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 115200 },
            
            .num_animation_indices = 10,
            .animation_indices = {
                DMX_OMEGA_SHOUTMON_X_ANIM_INDEX ,DMX_CYBERDRAMON_X_ANIM_INDEX ,DMX_DORUGUREMON_ANIM_INDEX ,DMX_GARUDAMON_X_ANIM_INDEX ,DMX_CANNONBEEMON_ANIM_INDEX ,DMX_GRADEMON_ANIM_INDEX ,DMX_MAMEMON_X_ANIM_INDEX ,DMX_CRYS_PALEDRAMON_ANIM_INDEX ,DMX_JAZARICHMON_ANIM_INDEX ,DMX_PUMPMON_ANIM_INDEX
            },
        },
        // Name: Sistermon Blanc
        {
            // Stage: Child
            .conditions = { .next_evolution_time_sec = 86400 },
            
            .num_animation_indices = 2,
            .animation_indices = {
                DMX_RHINOMON_X_ANIM_INDEX ,DMX_DAMEMON_ANIM_INDEX
            },
        },
        // Name: Skull Baluchimon
        {
            // Stage: Perfect
            .conditions = { .next_evolution_time_sec = 144000 },
            
            .num_animation_indices = 4,
            .animation_indices = {
                DMX_SAKUYAMON_X_ANIM_INDEX ,DMX_VALDURMON_ANIM_INDEX ,DMX_SLEIPMON_X_ANIM_INDEX ,DMX_PLATINUM_NUMEMON_ANIM_INDEX
            },
        },
        // Name: Skull Mammon X
        {
            // Stage: Ultimate
            .conditions = { .next_evolution_time_sec = 230400 },
            
            .num_animation_indices = 2,
            .animation_indices = {
                DMX_LEVIAMON_X_ANIM_INDEX ,DMX_BARBAMON_X_ANIM_INDEX
            },
        },
        // Name: Sleipmon X
        {
            // Stage: Ultimate
            .conditions = { .next_evolution_time_sec = 230400 },
            
            .num_animation_indices = 2,
            .animation_indices = {
                DMX_MINERVAMON_X_ANIM_INDEX ,DMX_ALPHAMON_ANIM_INDEX
            },
        },
        // Name: Stiffilmon
        {
            // Stage: Perfect
            .conditions = { .next_evolution_time_sec = 144000 },
            
            .num_animation_indices = 7,
            .animation_indices = {
                DMX_BLACK_WAR_GREYMON_X_ANIM_INDEX ,DMX_GRANDIS_KUWAGAMON_ANIM_INDEX ,DMX_DARK_KNIGHTMON_X_ANIM_INDEX ,DMX_GIGA_SEADRAMON_ANIM_INDEX ,DMX_RASENMON_FURY_MODE_ANIM_INDEX ,DMX_BAGRAMON_ANIM_INDEX ,DMX_ROSEMON_X_ANIM_INDEX
            },
        },
        // Name: Stiffimon
        {
            // Stage: Perfect
            .conditions = { .next_evolution_time_sec = 144000 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Tailmon X
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 115200 },
            
            .num_animation_indices = 9,
            .animation_indices = {
                DMX_ANGEWOMON_X_ANIM_INDEX ,DMX_RIZE_GREYMON_X_ANIM_INDEX ,DMX_MONZAEMON_X_ANIM_INDEX ,DMX_ANOMALOCARIMON_X_ANIM_INDEX ,DMX_GRADEMON_ANIM_INDEX ,DMX_MAMEMON_X_ANIM_INDEX ,DMX_CRYS_PALEDRAMON_ANIM_INDEX ,DMX_JAZARICHMON_ANIM_INDEX ,DMX_PUMPMON_ANIM_INDEX
            },
        },
        // Name: Terriermon X
        {
            // Stage: Child
            .conditions = { .next_evolution_time_sec = 86400 },
            
            .num_animation_indices = 8,
            .animation_indices = {
                DMX_SIESAMON_X_ANIM_INDEX ,DMX_MERAMON_X_ANIM_INDEX ,DMX_DORUGAMON_ANIM_INDEX ,DMX_PTERANOMON_X_ANIM_INDEX ,DMX_TOGEMON_X_ANIM_INDEX ,DMX_OMEKAMON_ANIM_INDEX ,DMX_PALEDRAMON_ANIM_INDEX ,DMX_JAZARDMON_ANIM_INDEX
            },
        },
        // Name: Tierriermon X
        {
            // Stage: Child
            .conditions = { .next_evolution_time_sec = 86400 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Tiger Vespamon
        {
            // Stage: Ultimate
            .conditions = { .next_evolution_time_sec = 230400 },
            
            .num_animation_indices = 8,
            .animation_indices = {
                DMX_MAGNAMON_X_ANIM_INDEX ,DMX_GANKOOMON_X_ANIM_INDEX ,DMX_DYNASMON_X_ANIM_INDEX ,DMX_CRANIUMMON_X_ANIM_INDEX ,DMX_LORD_KNIGHTMON_X_ANIM_INDEX ,DMX_DUKEMON_X_ANIM_INDEX ,DMX_ALPHAMON_OURYUKEN_ANIM_INDEX ,DMX_JESMON_GX_ANIM_INDEX
            },
        },
        // Name: Tobcatmon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 115200 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Tobucatmon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 115200 },
            
            .num_animation_indices = 5,
            .animation_indices = {
                DMX_SKULL_BALUCHIMON_ANIM_INDEX ,DMX_METAL_GREYMON_X_ANIM_INDEX ,DMX_CHO_HAKKAIMON_ANIM_INDEX ,DMX_WERE_GARURUMON_X_ANIM_INDEX ,DMX_YATAGARAMON_ANIM_INDEX
            },
        },
        // Name: Togemon X
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 115200 },
            
            .num_animation_indices = 10,
            .animation_indices = {
                DMX_OMEGA_SHOUTMON_X_ANIM_INDEX ,DMX_CYBERDRAMON_X_ANIM_INDEX ,DMX_DORUGUREMON_ANIM_INDEX ,DMX_GARUDAMON_X_ANIM_INDEX ,DMX_CANNONBEEMON_ANIM_INDEX ,DMX_GRADEMON_ANIM_INDEX ,DMX_MAMEMON_X_ANIM_INDEX ,DMX_CRYS_PALEDRAMON_ANIM_INDEX ,DMX_JAZARICHMON_ANIM_INDEX ,DMX_PUMPMON_ANIM_INDEX
            },
        },
        // Name: Tokomon X
        {
            // Stage: Baby II
            .conditions = { .next_evolution_time_sec = 43200 },
            
            .num_animation_indices = 6,
            .animation_indices = {
                DMX_RENAMON_X_ANIM_INDEX ,DMX_AGUMON_X_ANIM_INDEX ,DMX_HERISSMON_ANIM_INDEX ,DMX_DRACOMON_X_ANIM_INDEX ,DMX_GABUMON_X_ANIM_INDEX ,DMX_SISTERMON_BLANC_ANIM_INDEX
            },
        },
        // Name: Triceramon X
        {
            // Stage: Perfect
            .conditions = { .next_evolution_time_sec = 144000 },
            
            .num_animation_indices = 5,
            .animation_indices = {
                DMX_ULTIMATE_BRACHIOMON_ANIM_INDEX ,DMX_CHAOSDRAMON_X_ANIM_INDEX ,DMX_PRINCE_MAMEMON_X_ANIM_INDEX ,DMX_SKULL_MAMMON_X_ANIM_INDEX ,DMX_METAL_PIRANIMON_ANIM_INDEX
            },
        },
        // Name: Tylomon X
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 115200 },
            
            .num_animation_indices = 9,
            .animation_indices = {
                DMX_ANOMALOCARIMON_X_ANIM_INDEX ,DMX_RIZE_GREYMON_X_ANIM_INDEX ,DMX_MONZAEMON_X_ANIM_INDEX ,DMX_ANGEWOMON_X_ANIM_INDEX ,DMX_GRADEMON_ANIM_INDEX ,DMX_MAMEMON_X_ANIM_INDEX ,DMX_CRYS_PALEDRAMON_ANIM_INDEX ,DMX_JAZARICHMON_ANIM_INDEX ,DMX_PUMPMON_ANIM_INDEX
            },
        },
        // Name: Tyranomon X
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 115200 },
            
            .num_animation_indices = 3,
            .animation_indices = {
                DMX_METAL_GREYMON_X_ANIM_INDEX ,DMX_METAL_TYRANOMON_X_ANIM_INDEX ,DMX_YATAGARAMON_ANIM_INDEX
            },
        },
        // Name: Ulforce V-dramon X
        {
            // Stage: Ultimate
            .conditions = { .next_evolution_time_sec = 172800 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Ultimate Brachimon
        {
            // Stage: Ultimate
            .conditions = { .next_evolution_time_sec = 172800 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Ultimate Brachiomon
        {
            // Stage: Ultimate
            .conditions = { .next_evolution_time_sec = 230400 },
            
            .num_animation_indices = 2,
            .animation_indices = {
                DMX_LEVIAMON_X_ANIM_INDEX ,DMX_BARBAMON_X_ANIM_INDEX
            },
        },
        // Name: Valdurmon
        {
            // Stage: Ultimate
            .conditions = { .next_evolution_time_sec = 230400 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DMX_DUKEMON_X_ANIM_INDEX
            },
        },
        // Name: Vamdemon X
        {
            // Stage: Perfect
            .conditions = { .next_evolution_time_sec = 144000 },
            
            .num_animation_indices = 5,
            .animation_indices = {
                DMX_DARK_KNIGHTMON_X_ANIM_INDEX ,DMX_CHERUBIMON_VICE_X_ANIM_INDEX ,DMX_METAL_PIRANIMON_ANIM_INDEX ,DMX_PRINCE_MAMEMON_X_ANIM_INDEX ,DMX_CHAOSDRAMON_X_ANIM_INDEX
            },
        },
        // Name: Velgrmon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 115200 },
            
            .num_animation_indices = 7,
            .animation_indices = {
                DMX_LADY_DEVIMON_X_ANIM_INDEX ,DMX_OKUWAMON_X_ANIM_INDEX ,DMX_MEPHISMON_X_ANIM_INDEX ,DMX_METAL_FANTOMON_ANIM_INDEX ,DMX_KAISER_LEOMON_ANIM_INDEX ,DMX_MAMETYRAMON_ANIM_INDEX ,DMX_STIFFILMON_ANIM_INDEX
            },
        },
        // Name: Voltobautamon
        {
            // Stage: Ultimate
            .conditions = { .next_evolution_time_sec = 172800 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: War Greymon X
        {
            // Stage: Ultimate
            .conditions = { .next_evolution_time_sec = 230400 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DMX_OMEGAMON_X_ANIM_INDEX
            },
        },
        // Name: Were Garurumon X
        {
            // Stage: Perfect
            .conditions = { .next_evolution_time_sec = 144000 },
            
            .num_animation_indices = 4,
            .animation_indices = {
                DMX_METAL_GARURUMON_X_ANIM_INDEX ,DMX_JESMON_X_ANIM_INDEX ,DMX_VALDURMON_ANIM_INDEX ,DMX_PLATINUM_NUMEMON_ANIM_INDEX
            },
        },
        // Name: Wizarmon X
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 115200 },
            
            .num_animation_indices = 9,
            .animation_indices = {
                DMX_RIZE_GREYMON_X_ANIM_INDEX ,DMX_MONZAEMON_X_ANIM_INDEX ,DMX_ANGEWOMON_X_ANIM_INDEX ,DMX_ANOMALOCARIMON_X_ANIM_INDEX ,DMX_GRADEMON_ANIM_INDEX ,DMX_MAMEMON_X_ANIM_INDEX ,DMX_CRYS_PALEDRAMON_ANIM_INDEX ,DMX_JAZARICHMON_ANIM_INDEX ,DMX_PUMPMON_ANIM_INDEX
            },
        },
        // Name: Yaamon
        {
            // Stage: Baby II
            .conditions = { .next_evolution_time_sec = 43200 },
            
            .num_animation_indices = 8,
            .animation_indices = {
                DMX_GOMAMON_X_ANIM_INDEX ,DMX_KOKUWAMON_X_ANIM_INDEX ,DMX_AGUMON_BLACK_X_ANIM_INDEX ,DMX_HERISSMON_ANIM_INDEX ,DMX_DUSKMON_ANIM_INDEX ,DMX_PLOTMON_X_ANIM_INDEX ,DMX_OTAMAMON_X_ANIM_INDEX ,DMX_IMPMON_X_ANIM_INDEX
            },
        },
        // Name: Yatagaramon
        {
            // Stage: Perfect
            .conditions = { .next_evolution_time_sec = 144000 },
            
            .num_animation_indices = 5,
            .animation_indices = {
                DMX_SAKUYAMON_X_ANIM_INDEX ,DMX_BEEL_STARMON_X_ANIM_INDEX ,DMX_VALDURMON_ANIM_INDEX ,DMX_BELIAL_VAMDEMON_ANIM_INDEX ,DMX_PLATINUM_NUMEMON_ANIM_INDEX
            },
        },
        // Name: Zerimon
        {
            // Stage: Baby I
            .conditions = { .next_evolution_time_sec = 600 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DMX_GUMMYMON_ANIM_INDEX
            },
        },

    };
    animation::animation_evolution_data_t get_dmx_evolution_data(size_t index) {
        using namespace assets;
        assert(LEN_ARRAY(dmx_evol_data_table) == DMX_ANIM_COUNT);
        assert(index < DMX_ANIM_COUNT);
        auto result = dmx_evol_data_table[index];
        platform::details::asset_unload(dmx_evol_data_table, sizeof(animation::animation_evolution_data_t)*DMX_ANIM_COUNT);
        return result;
    }
}

