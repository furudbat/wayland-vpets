#include "embedded_assets/embedded_image.h"
#include "embedded_assets/dmc/dmc.hpp"
#include "embedded_assets/dmc/dmc_evol.h"
#include "graphics/animation_shared_memory.h"

/// @NOTE: Generated evolution data dmc

namespace bongocat::assets {
    static constexpr animation::animation_evolution_data_t dmc_evol_data_table[] ASSETS_DATA_EVOL_SECTION = {
        // Name: Agumon
        {
            // Stage: Child
            .conditions = { .next_evolution_time_sec = 86400 },
            
            .num_animation_indices = 5,
            .animation_indices = {
                DMC_GREYMON_ANIM_INDEX ,DMC_TYRANOMON_ANIM_INDEX ,DMC_DEVIMON_ANIM_INDEX ,DMC_MERAMON_ANIM_INDEX ,DMC_NUMEMON_ANIM_INDEX
            },
        },
        // Name: Airdramon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 129600 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DMC_METAL_GREYMON_ANIM_INDEX
            },
        },
        // Name: Andromon
        {
            // Stage: Perfect
            .conditions = { .next_evolution_time_sec = 172800 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DMC_HI_ANDROMON_ANIM_INDEX
            },
        },
        // Name: Angemon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 129600 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DMC_SKULL_GREYMON_ANIM_INDEX
            },
        },
        // Name: Babydmon
        {
            // Stage: Baby II
            .conditions = { .next_evolution_time_sec = 43200 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Bakemon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 129600 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DMC_GIROMON_ANIM_INDEX
            },
        },
        // Name: Bancho Leomon
        {
            // Stage: Ultimate
            .conditions = { .next_evolution_time_sec = 230400 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DMC_CHAOSMON_ANIM_INDEX
            },
        },
        // Name: Bancho Mamemon
        {
            // Stage: Ultimate
            .conditions = { .next_evolution_time_sec = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Betamon
        {
            // Stage: Child
            .conditions = { .next_evolution_time_sec = 86400 },
            
            .num_animation_indices = 5,
            .animation_indices = {
                DMC_DEVIMON_ANIM_INDEX ,DMC_MERAMON_ANIM_INDEX ,DMC_AIRDRAMON_ANIM_INDEX ,DMC_SEADRAMON_ANIM_INDEX ,DMC_NUMEMON_ANIM_INDEX
            },
        },
        // Name: Birdramon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 129600 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DMC_SKULL_GREYMON_ANIM_INDEX
            },
        },
        // Name: Blitz Greymon
        {
            // Stage: Ultimate
            .conditions = { .next_evolution_time_sec = 230400 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DMC_OMEGAMON_ALTER_S_ANIM_INDEX
            },
        },
        // Name: Bloom Lordmon
        {
            // Stage: Ultimate
            .conditions = { .next_evolution_time_sec = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Botamon
        {
            // Stage: Baby I
            .conditions = { .next_evolution_time_sec = 600 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DMC_KOROMON_ANIM_INDEX
            },
        },
        // Name: Centalmon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 129600 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DMC_GIROMON_ANIM_INDEX
            },
        },
        // Name: Chaosdramon
        {
            // Stage: Ultimate
            .conditions = { .next_evolution_time_sec = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Chaosmon
        {
            // Stage: Ultimate
            .conditions = { .next_evolution_time_sec = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Chimairamon
        {
            // Stage: Perfect
            .conditions = { .next_evolution_time_sec = 172800 },
            
            .num_animation_indices = 2,
            .animation_indices = {
                DMC_BANCHO_LEOMON_ANIM_INDEX ,DMC_MILLENNIUMON_ANIM_INDEX
            },
        },
        // Name: Cockatrimon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 129600 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DMC_PICCOLOMON_ANIM_INDEX
            },
        },
        // Name: Coelamon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 129600 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DMC_MEGADRAMON_ANIM_INDEX
            },
        },
        // Name: Coronamon
        {
            // Stage: Child
            .conditions = { .next_evolution_time_sec = 86400 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Cres Garurumon
        {
            // Stage: Ultimate
            .conditions = { .next_evolution_time_sec = 230400 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DMC_OMEGAMON_ALTER_S_ANIM_INDEX
            },
        },
        // Name: Cyclomon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 129600 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DMC_NANOMON_ANIM_INDEX
            },
        },
        // Name: Darkdramon
        {
            // Stage: Ultimate
            .conditions = { .next_evolution_time_sec = 230400 },
            
            .num_animation_indices = 2,
            .animation_indices = {
                DMC_CHAOSMON_ANIM_INDEX ,DMC_CHAOSDRAMON_ANIM_INDEX
            },
        },
        // Name: Dark Tyranomon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 129600 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DMC_METAL_TYRANOMON_ANIM_INDEX
            },
        },
        // Name: Deltamon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 129600 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DMC_NANOMON_ANIM_INDEX
            },
        },
        // Name: Devidramon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 129600 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DMC_METAL_TYRANOMON_ANIM_INDEX
            },
        },
        // Name: Devimon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 129600 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DMC_METAL_GREYMON_ANIM_INDEX
            },
        },
        // Name: Digitamamon
        {
            // Stage: Perfect
            .conditions = { .next_evolution_time_sec = 172800 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DMC_GANKOOMON_ANIM_INDEX
            },
        },
        // Name: Drimogemon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 129600 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DMC_GIROMON_ANIM_INDEX
            },
        },
        // Name: Ebemon
        {
            // Stage: Ultimate
            .conditions = { .next_evolution_time_sec = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Elecmon
        {
            // Stage: Child
            .conditions = { .next_evolution_time_sec = 86400 },
            
            .num_animation_indices = 5,
            .animation_indices = {
                DMC_ANGEMON_ANIM_INDEX ,DMC_YUKIDARUMON_ANIM_INDEX ,DMC_BIRDRAMON_ANIM_INDEX ,DMC_WHAMON_ANIM_INDEX ,DMC_VEGIMON_ANIM_INDEX
            },
        },
        // Name: Etemon
        {
            // Stage: Perfect
            .conditions = { .next_evolution_time_sec = 172800 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DMC_BANCHO_LEOMON_ANIM_INDEX
            },
        },
        // Name: Ex-Tyranomon
        {
            // Stage: Perfect
            .conditions = { .next_evolution_time_sec = 172800 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DMC_GAIOUMON_ANIM_INDEX
            },
        },
        // Name: Flymon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 129600 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DMC_METAL_TYRANOMON_ANIM_INDEX
            },
        },
        // Name: Gabumon
        {
            // Stage: Child
            .conditions = { .next_evolution_time_sec = 86400 },
            
            .num_animation_indices = 5,
            .animation_indices = {
                DMC_KABUTERIMON_ANIM_INDEX ,DMC_GARURUMON_ANIM_INDEX ,DMC_ANGEMON_ANIM_INDEX ,DMC_YUKIDARUMON_ANIM_INDEX ,DMC_VEGIMON_ANIM_INDEX
            },
        },
        // Name: Gaioumon
        {
            // Stage: Ultimate
            .conditions = { .next_evolution_time_sec = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Gankoomon
        {
            // Stage: Ultimate
            .conditions = { .next_evolution_time_sec = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Garurumon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 129600 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DMC_METAL_MAMEMON_ANIM_INDEX
            },
        },
        // Name: Gazimon
        {
            // Stage: Child
            .conditions = { .next_evolution_time_sec = 86400 },
            
            .num_animation_indices = 5,
            .animation_indices = {
                DMC_DARK_TYRANOMON_ANIM_INDEX ,DMC_CYCLOMON_ANIM_INDEX ,DMC_DEVIDRAMON_ANIM_INDEX ,DMC_TUSKMON_ANIM_INDEX ,DMC_RAREMON_ANIM_INDEX
            },
        },
        // Name: Giromon
        {
            // Stage: Perfect
            .conditions = { .next_evolution_time_sec = 172800 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DMC_GOKUMON_ANIM_INDEX
            },
        },
        // Name: Gizamon
        {
            // Stage: Child
            .conditions = { .next_evolution_time_sec = 86400 },
            
            .num_animation_indices = 5,
            .animation_indices = {
                DMC_DEVIDRAMON_ANIM_INDEX ,DMC_TUSKMON_ANIM_INDEX ,DMC_FLYMON_ANIM_INDEX ,DMC_DELTAMON_ANIM_INDEX ,DMC_RAREMON_ANIM_INDEX
            },
        },
        // Name: Gokumon
        {
            // Stage: Ultimate
            .conditions = { .next_evolution_time_sec = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Greymon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 129600 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DMC_METAL_GREYMON_ANIM_INDEX
            },
        },
        // Name: Hi Andromon
        {
            // Stage: Ultimate
            .conditions = { .next_evolution_time_sec = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Kabuterimon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 129600 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DMC_SKULL_GREYMON_ANIM_INDEX
            },
        },
        // Name: Koromon
        {
            // Stage: Baby II
            .conditions = { .next_evolution_time_sec = 43200 },
            
            .num_animation_indices = 2,
            .animation_indices = {
                DMC_AGUMON_ANIM_INDEX ,DMC_BETAMON_ANIM_INDEX
            },
        },
        // Name: Kunemon
        {
            // Stage: Child
            .conditions = { .next_evolution_time_sec = 86400 },
            
            .num_animation_indices = 5,
            .animation_indices = {
                DMC_OGREMON_ANIM_INDEX ,DMC_BAKEMON_ANIM_INDEX ,DMC_SHELLMON_ANIM_INDEX ,DMC_DRIMOGEMON_ANIM_INDEX ,DMC_SCUMON_ANIM_INDEX
            },
        },
        // Name: Kuwagamon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 129600 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DMC_PICCOLOMON_ANIM_INDEX
            },
        },
        // Name: Leomon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 129600 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DMC_MEGADRAMON_ANIM_INDEX
            },
        },
        // Name: Mamemon
        {
            // Stage: Perfect
            .conditions = { .next_evolution_time_sec = 172800 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DMC_BANCHO_MAMEMON_ANIM_INDEX
            },
        },
        // Name: Megadramon
        {
            // Stage: Perfect
            .conditions = { .next_evolution_time_sec = 172800 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DMC_DARKDRAMON_ANIM_INDEX
            },
        },
        // Name: Meramon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 129600 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DMC_MAMEMON_ANIM_INDEX
            },
        },
        // Name: Metal Garurumon
        {
            // Stage: Ultimate
            .conditions = { .next_evolution_time_sec = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Metal Greymon
        {
            // Stage: Perfect
            .conditions = { .next_evolution_time_sec = 172800 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Metal Greymon (Virus)
        {
            // Stage: Perfect
            .conditions = { .next_evolution_time_sec = 172800 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DMC_BLITZ_GREYMON_ANIM_INDEX
            },
        },
        // Name: Metal Mamemon
        {
            // Stage: Perfect
            .conditions = { .next_evolution_time_sec = 172800 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DMC_CRES_GARURUMON_ANIM_INDEX
            },
        },
        // Name: Metal Tyranomon
        {
            // Stage: Perfect
            .conditions = { .next_evolution_time_sec = 172800 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DMC_MUGENDRAMON_ANIM_INDEX
            },
        },
        // Name: Millenniumon
        {
            // Stage: Ultimate
            .conditions = { .next_evolution_time_sec = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Mojyamon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 129600 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DMC_PICCOLOMON_ANIM_INDEX
            },
        },
        // Name: Monochromon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 129600 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DMC_MEGADRAMON_ANIM_INDEX
            },
        },
        // Name: Monzaemon
        {
            // Stage: Perfect
            .conditions = { .next_evolution_time_sec = 172800 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DMC_SHIN_MONZAEMON_ANIM_INDEX
            },
        },
        // Name: Mugendramon
        {
            // Stage: Ultimate
            .conditions = { .next_evolution_time_sec = 230400 },
            
            .num_animation_indices = 2,
            .animation_indices = {
                DMC_MILLENNIUMON_ANIM_INDEX ,DMC_CHAOSDRAMON_ANIM_INDEX
            },
        },
        // Name: Nanimon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 129600 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DMC_DIGITAMAMON_ANIM_INDEX
            },
        },
        // Name: Nanomon
        {
            // Stage: Perfect
            .conditions = { .next_evolution_time_sec = 172800 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DMC_RAIDENMON_ANIM_INDEX
            },
        },
        // Name: Numemon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 129600 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DMC_MONZAEMON_ANIM_INDEX
            },
        },
        // Name: Ogremon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 129600 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DMC_ANDROMON_ANIM_INDEX
            },
        },
        // Name: Omegamon Alter S
        {
            // Stage: Ultimate
            .conditions = { .next_evolution_time_sec = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Omegamon
        {
            // Stage: Ultimate
            .conditions = { .next_evolution_time_sec = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Orgemon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 129600 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Pagumon
        {
            // Stage: Baby II
            .conditions = { .next_evolution_time_sec = 43200 },
            
            .num_animation_indices = 2,
            .animation_indices = {
                DMC_GAZIMON_ANIM_INDEX ,DMC_GIZAMON_ANIM_INDEX
            },
        },
        // Name: Palmon
        {
            // Stage: Child
            .conditions = { .next_evolution_time_sec = 86400 },
            
            .num_animation_indices = 5,
            .animation_indices = {
                DMC_LEOMON_ANIM_INDEX ,DMC_KUWAGAMON_ANIM_INDEX ,DMC_COELAMON_ANIM_INDEX ,DMC_MOJYAMON_ANIM_INDEX ,DMC_NANIMON_ANIM_INDEX
            },
        },
        // Name: Patamon
        {
            // Stage: Child
            .conditions = { .next_evolution_time_sec = 86400 },
            
            .num_animation_indices = 5,
            .animation_indices = {
                DMC_UNIMON_ANIM_INDEX ,DMC_CENTALMON_ANIM_INDEX ,DMC_OGREMON_ANIM_INDEX ,DMC_BAKEMON_ANIM_INDEX ,DMC_SCUMON_ANIM_INDEX
            },
        },
        // Name: Petitmon
        {
            // Stage: Baby I
            .conditions = { .next_evolution_time_sec = 600 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Piccolomon
        {
            // Stage: Perfect
            .conditions = { .next_evolution_time_sec = 172800 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DMC_BLOOM_LORDMON_ANIM_INDEX
            },
        },
        // Name: Piyomon
        {
            // Stage: Child
            .conditions = { .next_evolution_time_sec = 86400 },
            
            .num_animation_indices = 5,
            .animation_indices = {
                DMC_MONOCHROMON_ANIM_INDEX ,DMC_COCKATRIMON_ANIM_INDEX ,DMC_LEOMON_ANIM_INDEX ,DMC_KUWAGAMON_ANIM_INDEX ,DMC_NANIMON_ANIM_INDEX
            },
        },
        // Name: Poyomon
        {
            // Stage: Baby I
            .conditions = { .next_evolution_time_sec = 600 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DMC_TOKOMON_ANIM_INDEX
            },
        },
        // Name: Punimon
        {
            // Stage: Baby I
            .conditions = { .next_evolution_time_sec = 600 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DMC_TSUNOMON_ANIM_INDEX
            },
        },
        // Name: Raidenmon
        {
            // Stage: Ultimate
            .conditions = { .next_evolution_time_sec = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Raremon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 129600 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DMC_EX_TYRANOMON_ANIM_INDEX
            },
        },
        // Name: Rust Tyranomon
        {
            // Stage: Ultimate
            .conditions = { .next_evolution_time_sec = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Scumon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 129600 },
            
            .num_animation_indices = 2,
            .animation_indices = {
                DMC_ETEMON_ANIM_INDEX ,DMC_CHIMAIRAMON_ANIM_INDEX
            },
        },
        // Name: Seadramon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 129600 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DMC_MAMEMON_ANIM_INDEX
            },
        },
        // Name: Shellmon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 129600 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DMC_ANDROMON_ANIM_INDEX
            },
        },
        // Name: Shin Monzaemon
        {
            // Stage: Ultimate
            .conditions = { .next_evolution_time_sec = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Skull Greymon
        {
            // Stage: Perfect
            .conditions = { .next_evolution_time_sec = 172800 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DMC_SKULL_MAMMON_ANIM_INDEX
            },
        },
        // Name: Skull Mammon
        {
            // Stage: Ultimate
            .conditions = { .next_evolution_time_sec = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Tanemon
        {
            // Stage: Baby II
            .conditions = { .next_evolution_time_sec = 43200 },
            
            .num_animation_indices = 2,
            .animation_indices = {
                DMC_PIYOMON_ANIM_INDEX ,DMC_PALMON_ANIM_INDEX
            },
        },
        // Name: Titamon
        {
            // Stage: Ultimate
            .conditions = { .next_evolution_time_sec = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Tokomon
        {
            // Stage: Baby II
            .conditions = { .next_evolution_time_sec = 43200 },
            
            .num_animation_indices = 2,
            .animation_indices = {
                DMC_PATAMON_ANIM_INDEX ,DMC_KUNEMON_ANIM_INDEX
            },
        },
        // Name: Tsunomon
        {
            // Stage: Baby II
            .conditions = { .next_evolution_time_sec = 43200 },
            
            .num_animation_indices = 2,
            .animation_indices = {
                DMC_GABUMON_ANIM_INDEX ,DMC_ELECMON_ANIM_INDEX
            },
        },
        // Name: Tuskmon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 129600 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DMC_NANOMON_ANIM_INDEX
            },
        },
        // Name: Tyranomon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 129600 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DMC_MAMEMON_ANIM_INDEX
            },
        },
        // Name: Unimon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 129600 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DMC_ANDROMON_ANIM_INDEX
            },
        },
        // Name: Vademon
        {
            // Stage: Perfect
            .conditions = { .next_evolution_time_sec = 172800 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DMC_EBEMON_ANIM_INDEX
            },
        },
        // Name: Vegimon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 129600 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DMC_VADEMON_ANIM_INDEX
            },
        },
        // Name: War Greymon
        {
            // Stage: Ultimate
            .conditions = { .next_evolution_time_sec = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Were Garurumon
        {
            // Stage: Perfect
            .conditions = { .next_evolution_time_sec = 172800 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Whamon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 129600 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DMC_METAL_MAMEMON_ANIM_INDEX
            },
        },
        // Name: Yukidarumon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 129600 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DMC_METAL_MAMEMON_ANIM_INDEX
            },
        },
        // Name: Yuramon
        {
            // Stage: Baby I
            .conditions = { .next_evolution_time_sec = 600 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DMC_TANEMON_ANIM_INDEX
            },
        },
        // Name: Zurumon
        {
            // Stage: Baby I
            .conditions = { .next_evolution_time_sec = 600 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DMC_PAGUMON_ANIM_INDEX
            },
        },

    };
    animation::animation_evolution_data_t get_dmc_evolution_data(size_t index) {
        using namespace assets;
        assert(LEN_ARRAY(dmc_evol_data_table) == DMC_ANIM_COUNT);
        assert(index < DMC_ANIM_COUNT);
        auto result = dmc_evol_data_table[index];
        return result;
    }
}

