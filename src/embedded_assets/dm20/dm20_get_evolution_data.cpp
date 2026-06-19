#include "embedded_assets/embedded_image.h"
#include "embedded_assets/dm20/dm20.hpp"
#include "embedded_assets/dm20/dm20_evol.h"
#include "graphics/animation_shared_memory.h"

/// @NOTE: Generated evolution data dm20

namespace bongocat::assets {
    static constexpr animation::animation_evolution_data_t dm20_evol_data_table[] ASSETS_DATA_EVOL_SECTION = {
        // Name: Aegisdramon
        {
            // Stage: Ultimate
            .conditions = { .next_evolution_time_sec = 230400 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DM20_RUST_TYRANOMON_ANIM_INDEX
            },
        },
        // Name: Agumon
        {
            // Stage: Child
            .conditions = { .next_evolution_time_sec = 86400 },
            
            .num_animation_indices = 5,
            .animation_indices = {
                DM20_GREYMON_ANIM_INDEX ,DM20_TYRANOMON_ANIM_INDEX ,DM20_DEVIMON_ANIM_INDEX ,DM20_MERAMON_ANIM_INDEX ,DM20_NUMEMON_ANIM_INDEX
            },
        },
        // Name: Airdramon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 129600 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DM20_METAL_GREYMON_ANIM_INDEX
            },
        },
        // Name: Alphamon
        {
            // Stage: Ultimate
            .conditions = { .next_evolution_time_sec = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Andromon
        {
            // Stage: Perfect
            .conditions = { .next_evolution_time_sec = 172800 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DM20_HI_ANDROMON_ANIM_INDEX
            },
        },
        // Name: Angemon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 129600 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DM20_SKULL_GREYMON_ANIM_INDEX
            },
        },
        // Name: Apollomon
        {
            // Stage: Ultimate
            .conditions = { .next_evolution_time_sec = 230400 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DM20_GRACE_NOVAMON_ANIM_INDEX
            },
        },
        // Name: Babydmon
        {
            // Stage: Baby II
            .conditions = { .next_evolution_time_sec = 21600 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DM20_DRACOMON_ANIM_INDEX
            },
        },
        // Name: Bakemon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 129600 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DM20_GIROMON_ANIM_INDEX
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
        // Name: Bao Hackmon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 129600 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DM20_SAVIOR_HACKMON_ANIM_INDEX
            },
        },
        // Name: Betamon
        {
            // Stage: Child
            .conditions = { .next_evolution_time_sec = 86400 },
            
            .num_animation_indices = 5,
            .animation_indices = {
                DM20_DEVIMON_ANIM_INDEX ,DM20_MERAMON_ANIM_INDEX ,DM20_AIRDRAMON_ANIM_INDEX ,DM20_SEADRAMON_ANIM_INDEX ,DM20_NUMEMON_ANIM_INDEX
            },
        },
        // Name: Birdramon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 129600 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DM20_SKULL_GREYMON_ANIM_INDEX
            },
        },
        // Name: Blitz Greymon
        {
            // Stage: Ultimate
            .conditions = { .next_evolution_time_sec = 230400 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DM20_OMEGAMON_ALTER_S_ANIM_INDEX
            },
        },
        // Name: Botamon
        {
            // Stage: Baby I
            .conditions = { .next_evolution_time_sec = 600 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DM20_KOROMON_ANIM_INDEX
            },
        },
        // Name: Breakdramon
        {
            // Stage: Ultimate
            .conditions = { .next_evolution_time_sec = 230400 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DM20_EXAMON_ANIM_INDEX
            },
        },
        // Name: Centalmon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 129600 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DM20_GIROMON_ANIM_INDEX
            },
        },
        // Name: Cockatrimon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 129600 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DM20_PICCOLOMON_ANIM_INDEX
            },
        },
        // Name: Coelamon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 129600 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DM20_MEGADRAMON_ANIM_INDEX
            },
        },
        // Name: Coredramon (Blue)
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 129600 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DM20_WINGDRAMON_ANIM_INDEX
            },
        },
        // Name: Coredramon (Green)
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 129600 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DM20_GROUNDRAMON_ANIM_INDEX
            },
        },
        // Name: Coronamon
        {
            // Stage: Child
            .conditions = { .next_evolution_time_sec = 86400 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DM20_FIRAMON_ANIM_INDEX
            },
        },
        // Name: Crescemon
        {
            // Stage: Perfect
            .conditions = { .next_evolution_time_sec = 172800 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DM20_DIANAMON_ANIM_INDEX
            },
        },
        // Name: Cres Garurumon
        {
            // Stage: Ultimate
            .conditions = { .next_evolution_time_sec = 230400 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DM20_OMEGAMON_ALTER_S_ANIM_INDEX
            },
        },
        // Name: Cyclomon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 129600 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DM20_NANOMON_ANIM_INDEX
            },
        },
        // Name: Dark Tyranomon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 129600 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DM20_METAL_TYRANOMON_ANIM_INDEX
            },
        },
        // Name: Deltamon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 129600 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DM20_NANOMON_ANIM_INDEX
            },
        },
        // Name: Devidramon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 129600 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DM20_METAL_TYRANOMON_ANIM_INDEX
            },
        },
        // Name: Devimon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 129600 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DM20_METAL_GREYMON_ANIM_INDEX
            },
        },
        // Name: Dianamon
        {
            // Stage: Ultimate
            .conditions = { .next_evolution_time_sec = 230400 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DM20_GRACE_NOVAMON_ANIM_INDEX
            },
        },
        // Name: Digitamamon
        {
            // Stage: Perfect
            .conditions = { .next_evolution_time_sec = 172800 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DM20_TITAMON_ANIM_INDEX
            },
        },
        // Name: Dodomon
        {
            // Stage: Baby I
            .conditions = { .next_evolution_time_sec = 600 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DM20_DORIMON_ANIM_INDEX
            },
        },
        // Name: Dorimon
        {
            // Stage: Baby II
            .conditions = { .next_evolution_time_sec = 21600 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DM20_DORUMON_ANIM_INDEX
            },
        },
        // Name: DORUgamon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 129600 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DM20_DORUGUREMON_ANIM_INDEX
            },
        },
        // Name: DORUguremon
        {
            // Stage: Perfect
            .conditions = { .next_evolution_time_sec = 172800 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DM20_ALPHAMON_ANIM_INDEX
            },
        },
        // Name: DORUmon
        {
            // Stage: Child
            .conditions = { .next_evolution_time_sec = 86400 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DM20_DORUGAMON_ANIM_INDEX
            },
        },
        // Name: Dracomon
        {
            // Stage: Child
            .conditions = { .next_evolution_time_sec = 86400 },
            
            .num_animation_indices = 2,
            .animation_indices = {
                DM20_COREDRAMON_BLUE_ANIM_INDEX ,DM20_COREDRAMON_GREEN_ANIM_INDEX
            },
        },
        // Name: Drimogemon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 129600 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DM20_GIROMON_ANIM_INDEX
            },
        },
        // Name: Duramon
        {
            // Stage: Perfect
            .conditions = { .next_evolution_time_sec = 172800 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DM20_DURANDAMON_ANIM_INDEX
            },
        },
        // Name: Durandamon
        {
            // Stage: Ultimate
            .conditions = { .next_evolution_time_sec = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Durandramon
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
                DM20_ANGEMON_ANIM_INDEX ,DM20_YUKIDARUMON_ANIM_INDEX ,DM20_BIRDRAMON_ANIM_INDEX ,DM20_WHAMON_ANIM_INDEX ,DM20_VEGIMON_ANIM_INDEX
            },
        },
        // Name: Etemon
        {
            // Stage: Perfect
            .conditions = { .next_evolution_time_sec = 172800 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DM20_KING_ETEMON_ANIM_INDEX
            },
        },
        // Name: Examon
        {
            // Stage: Ultimate
            .conditions = { .next_evolution_time_sec = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Ex-Tyranomon
        {
            // Stage: Perfect
            .conditions = { .next_evolution_time_sec = 172800 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DM20_PINOCHIMON_ANIM_INDEX
            },
        },
        // Name: Firamon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 129600 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DM20_FLAREMON_ANIM_INDEX
            },
        },
        // Name: Flaremon
        {
            // Stage: Perfect
            .conditions = { .next_evolution_time_sec = 172800 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DM20_APOLLOMON_ANIM_INDEX
            },
        },
        // Name: Flymon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 129600 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DM20_METAL_TYRANOMON_ANIM_INDEX
            },
        },
        // Name: Gabumon
        {
            // Stage: Child
            .conditions = { .next_evolution_time_sec = 86400 },
            
            .num_animation_indices = 5,
            .animation_indices = {
                DM20_KABUTERIMON_ANIM_INDEX ,DM20_GARURUMON_ANIM_INDEX ,DM20_ANGEMON_ANIM_INDEX ,DM20_YUKIDARUMON_ANIM_INDEX ,DM20_VEGIMON_ANIM_INDEX
            },
        },
        // Name: Garurumon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 129600 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DM20_METAL_MAMEMON_ANIM_INDEX
            },
        },
        // Name: Gazimon
        {
            // Stage: Child
            .conditions = { .next_evolution_time_sec = 86400 },
            
            .num_animation_indices = 5,
            .animation_indices = {
                DM20_DARK_TYRANOMON_ANIM_INDEX ,DM20_CYCLOMON_ANIM_INDEX ,DM20_DEVIDRAMON_ANIM_INDEX ,DM20_TUSKMON_ANIM_INDEX ,DM20_RAREMON_ANIM_INDEX
            },
        },
        // Name: Giromon
        {
            // Stage: Perfect
            .conditions = { .next_evolution_time_sec = 172800 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Gizamon
        {
            // Stage: Child
            .conditions = { .next_evolution_time_sec = 86400 },
            
            .num_animation_indices = 5,
            .animation_indices = {
                DM20_DEVIDRAMON_ANIM_INDEX ,DM20_TUSKMON_ANIM_INDEX ,DM20_FLYMON_ANIM_INDEX ,DM20_DELTAMON_ANIM_INDEX ,DM20_RAREMON_ANIM_INDEX
            },
        },
        // Name: Grace Novamon
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
                DM20_METAL_GREYMON_ANIM_INDEX
            },
        },
        // Name: Groundramon
        {
            // Stage: Perfect
            .conditions = { .next_evolution_time_sec = 172800 },
            
            .num_animation_indices = 2,
            .animation_indices = {
                DM20_BREAKDRAMON_ANIM_INDEX ,DM20_YAMATOS_METAL_GARURUMON_ANIM_INDEX
            },
        },
        // Name: Hackmon
        {
            // Stage: Child
            .conditions = { .next_evolution_time_sec = 86400 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DM20_BAO_HACKMON_ANIM_INDEX
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
        // Name: Jesmon
        {
            // Stage: Ultimate
            .conditions = { .next_evolution_time_sec = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Jijimon
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
                DM20_SKULL_GREYMON_ANIM_INDEX
            },
        },
        // Name: King Etemon
        {
            // Stage: Ultimate
            .conditions = { .next_evolution_time_sec = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Koromon
        {
            // Stage: Baby II
            .conditions = { .next_evolution_time_sec = 21600 },
            
            .num_animation_indices = 2,
            .animation_indices = {
                DM20_AGUMON_ANIM_INDEX ,DM20_BETAMON_ANIM_INDEX
            },
        },
        // Name: Kunemon
        {
            // Stage: Child
            .conditions = { .next_evolution_time_sec = 86400 },
            
            .num_animation_indices = 5,
            .animation_indices = {
                DM20_OGREMON_ANIM_INDEX ,DM20_BAKEMON_ANIM_INDEX ,DM20_SHELLMON_ANIM_INDEX ,DM20_DRIMOGEMON_ANIM_INDEX ,DM20_SCUMON_ANIM_INDEX
            },
        },
        // Name: Kuwagamon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 129600 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DM20_PICCOLOMON_ANIM_INDEX
            },
        },
        // Name: Lekismon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 129600 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DM20_CRESCEMON_ANIM_INDEX
            },
        },
        // Name: Leomon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 129600 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DM20_MEGADRAMON_ANIM_INDEX
            },
        },
        // Name: Lunamon
        {
            // Stage: Child
            .conditions = { .next_evolution_time_sec = 86400 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DM20_LEKISMON_ANIM_INDEX
            },
        },
        // Name: Mamemon
        {
            // Stage: Perfect
            .conditions = { .next_evolution_time_sec = 172800 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Megadramon
        {
            // Stage: Perfect
            .conditions = { .next_evolution_time_sec = 172800 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DM20_AEGISDRAMON_ANIM_INDEX
            },
        },
        // Name: Meicoomon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 129600 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DM20_MEICRACKMON_ANIM_INDEX
            },
        },
        // Name: Meicrackmon
        {
            // Stage: Perfect
            .conditions = { .next_evolution_time_sec = 172800 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DM20_RASIELMON_ANIM_INDEX
            },
        },
        // Name: Meramon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 129600 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DM20_MAMEMON_ANIM_INDEX
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
        // Name: Metal Mamemon
        {
            // Stage: Perfect
            .conditions = { .next_evolution_time_sec = 172800 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DM20_CRES_GARURUMON_ANIM_INDEX
            },
        },
        // Name: Metal Tyranomon
        {
            // Stage: Perfect
            .conditions = { .next_evolution_time_sec = 172800 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DM20_MUGENDRAMON_ANIM_INDEX
            },
        },
        // Name: Mojyamon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 129600 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DM20_PICCOLOMON_ANIM_INDEX
            },
        },
        // Name: Monchromon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 129600 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Monochromon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 129600 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DM20_MEGADRAMON_ANIM_INDEX
            },
        },
        // Name: Monzaemon
        {
            // Stage: Perfect
            .conditions = { .next_evolution_time_sec = 172800 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Mozaemon
        {
            // Stage: Perfect
            .conditions = { .next_evolution_time_sec = 172800 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Mugendramon
        {
            // Stage: Ultimate
            .conditions = { .next_evolution_time_sec = 230400 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DM20_RUST_TYRANOMON_ANIM_INDEX
            },
        },
        // Name: Nanimon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 129600 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DM20_DIGITAMAMON_ANIM_INDEX
            },
        },
        // Name: Nanomon
        {
            // Stage: Perfect
            .conditions = { .next_evolution_time_sec = 172800 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Numemon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 129600 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DM20_MONZAEMON_ANIM_INDEX
            },
        },
        // Name: Nyaromon
        {
            // Stage: Baby II
            .conditions = { .next_evolution_time_sec = 21600 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DM20_PLOTMON_ANIM_INDEX
            },
        },
        // Name: Ogremon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 129600 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DM20_ANDROMON_ANIM_INDEX
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
        // Name: Pagumon
        {
            // Stage: Baby II
            .conditions = { .next_evolution_time_sec = 21600 },
            
            .num_animation_indices = 2,
            .animation_indices = {
                DM20_GAZIMON_ANIM_INDEX ,DM20_GIZAMON_ANIM_INDEX
            },
        },
        // Name: Pakumon
        {
            // Stage: Ultimate
            .conditions = { .next_evolution_time_sec = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Palmon
        {
            // Stage: Child
            .conditions = { .next_evolution_time_sec = 86400 },
            
            .num_animation_indices = 5,
            .animation_indices = {
                DM20_LEOMON_ANIM_INDEX ,DM20_KUWAGAMON_ANIM_INDEX ,DM20_COELAMON_ANIM_INDEX ,DM20_MOJYAMON_ANIM_INDEX ,DM20_NANIMON_ANIM_INDEX
            },
        },
        // Name: Patamon
        {
            // Stage: Child
            .conditions = { .next_evolution_time_sec = 86400 },
            
            .num_animation_indices = 5,
            .animation_indices = {
                DM20_UNIMON_ANIM_INDEX ,DM20_CENTALMON_ANIM_INDEX ,DM20_OGREMON_ANIM_INDEX ,DM20_BAKEMON_ANIM_INDEX ,DM20_SCUMON_ANIM_INDEX
            },
        },
        // Name: Petitmon
        {
            // Stage: Baby I
            .conditions = { .next_evolution_time_sec = 600 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DM20_BABYDMON_ANIM_INDEX
            },
        },
        // Name: Piccolomon
        {
            // Stage: Perfect
            .conditions = { .next_evolution_time_sec = 172800 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Pinochimon
        {
            // Stage: Ultimate
            .conditions = { .next_evolution_time_sec = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Pitchmon
        {
            // Stage: Baby I
            .conditions = { .next_evolution_time_sec = 600 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DM20_PUKAMON_ANIM_INDEX
            },
        },
        // Name: Piyomon
        {
            // Stage: Child
            .conditions = { .next_evolution_time_sec = 86400 },
            
            .num_animation_indices = 5,
            .animation_indices = {
                DM20_MONOCHROMON_ANIM_INDEX ,DM20_COCKATRIMON_ANIM_INDEX ,DM20_LEOMON_ANIM_INDEX ,DM20_KUWAGAMON_ANIM_INDEX ,DM20_NANIMON_ANIM_INDEX
            },
        },
        // Name: Plotmon
        {
            // Stage: Child
            .conditions = { .next_evolution_time_sec = 86400 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DM20_MEICOOMON_ANIM_INDEX
            },
        },
        // Name: Poyomon
        {
            // Stage: Baby I
            .conditions = { .next_evolution_time_sec = 600 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DM20_TOKOMON_ANIM_INDEX
            },
        },
        // Name: Pukamon
        {
            // Stage: Baby II
            .conditions = { .next_evolution_time_sec = 21600 },
            
            .num_animation_indices = 2,
            .animation_indices = {
                DM20_CORONAMON_ANIM_INDEX ,DM20_LUNAMON_ANIM_INDEX
            },
        },
        // Name: Punimon
        {
            // Stage: Baby I
            .conditions = { .next_evolution_time_sec = 600 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DM20_TUNOMON_ANIM_INDEX
            },
        },
        // Name: Raremon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 129600 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DM20_EX_TYRANOMON_ANIM_INDEX
            },
        },
        // Name: Rasielmon
        {
            // Stage: Ultimate
            .conditions = { .next_evolution_time_sec = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
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
        // Name: Sakumon
        {
            // Stage: Baby I
            .conditions = { .next_evolution_time_sec = 600 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DM20_SAKUTTOMON_ANIM_INDEX
            },
        },
        // Name: Sakuttomon
        {
            // Stage: Baby II
            .conditions = { .next_evolution_time_sec = 21600 },
            
            .num_animation_indices = 2,
            .animation_indices = {
                DM20_ZUBAMON_ANIM_INDEX ,DM20_HACKMON_ANIM_INDEX
            },
        },
        // Name: Savior Hackmon
        {
            // Stage: Perfect
            .conditions = { .next_evolution_time_sec = 172800 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DM20_JESMON_ANIM_INDEX
            },
        },
        // Name: Scumon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 129600 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DM20_ETEMON_ANIM_INDEX
            },
        },
        // Name: Seadramon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 129600 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DM20_MAMEMON_ANIM_INDEX
            },
        },
        // Name: Shellmon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 129600 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DM20_ANDROMON_ANIM_INDEX
            },
        },
        // Name: Skull Greymon
        {
            // Stage: Perfect
            .conditions = { .next_evolution_time_sec = 172800 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DM20_SKULL_MAMMON_ANIM_INDEX
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
        // Name: Slayerdramon
        {
            // Stage: Ultimate
            .conditions = { .next_evolution_time_sec = 230400 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DM20_EXAMON_ANIM_INDEX
            },
        },
        // Name: Taichi Metal Greymon
        {
            // Stage: Perfect
            .conditions = { .next_evolution_time_sec = 172800 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Taichis Agumon
        {
            // Stage: Child
            .conditions = { .next_evolution_time_sec = 86400 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DM20_TAICHIS_GREYMON_ANIM_INDEX
            },
        },
        // Name: Taichis Greymon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 129600 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DM20_TAICHIS_METAL_GREYMON_ANIM_INDEX
            },
        },
        // Name: Taichis Metal Greymon
        {
            // Stage: Perfect
            .conditions = { .next_evolution_time_sec = 172800 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DM20_TAICHIS_WAR_GREYMON_ANIM_INDEX
            },
        },
        // Name: Taichis War Greymon
        {
            // Stage: Ultimate
            .conditions = { .next_evolution_time_sec = 230400 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DM20_OMEGAMON_ANIM_INDEX
            },
        },
        // Name: Tanemon
        {
            // Stage: Baby II
            .conditions = { .next_evolution_time_sec = 21600 },
            
            .num_animation_indices = 2,
            .animation_indices = {
                DM20_PIYOMON_ANIM_INDEX ,DM20_PALMON_ANIM_INDEX
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
            .conditions = { .next_evolution_time_sec = 21600 },
            
            .num_animation_indices = 2,
            .animation_indices = {
                DM20_PATAMON_ANIM_INDEX ,DM20_KUNEMON_ANIM_INDEX
            },
        },
        // Name: Tsunomon
        {
            // Stage: Baby II
            .conditions = { .next_evolution_time_sec = 21600 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Tunomon
        {
            // Stage: Baby II
            .conditions = { .next_evolution_time_sec = 21600 },
            
            .num_animation_indices = 2,
            .animation_indices = {
                DM20_GABUMON_ANIM_INDEX ,DM20_ELECMON_ANIM_INDEX
            },
        },
        // Name: Tuskmon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 129600 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DM20_NANOMON_ANIM_INDEX
            },
        },
        // Name: Tyranomon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 129600 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DM20_MAMEMON_ANIM_INDEX
            },
        },
        // Name: Unimon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 129600 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DM20_ANDROMON_ANIM_INDEX
            },
        },
        // Name: Vademon
        {
            // Stage: Perfect
            .conditions = { .next_evolution_time_sec = 172800 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Vegimon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 129600 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DM20_VADEMON_ANIM_INDEX
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
                DM20_METAL_MAMEMON_ANIM_INDEX
            },
        },
        // Name: Wingdramon
        {
            // Stage: Perfect
            .conditions = { .next_evolution_time_sec = 172800 },
            
            .num_animation_indices = 2,
            .animation_indices = {
                DM20_SLAYERDRAMON_ANIM_INDEX ,DM20_TAICHIS_WAR_GREYMON_ANIM_INDEX
            },
        },
        // Name: Yamato Gabumon
        {
            // Stage: Child
            .conditions = { .next_evolution_time_sec = 86400 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Yamatos Gabumon
        {
            // Stage: Child
            .conditions = { .next_evolution_time_sec = 86400 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DM20_YAMATOS_GARURUMON_ANIM_INDEX
            },
        },
        // Name: Yamatos Garurumon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 129600 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DM20_YAMATOS_WERE_GARURUMON_ANIM_INDEX
            },
        },
        // Name: Yamatos Metal Garurumon
        {
            // Stage: Ultimate
            .conditions = { .next_evolution_time_sec = 230400 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DM20_OMEGAMON_ANIM_INDEX
            },
        },
        // Name: Yamatos Were Garurumon
        {
            // Stage: Perfect
            .conditions = { .next_evolution_time_sec = 172800 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DM20_YAMATOS_METAL_GARURUMON_ANIM_INDEX
            },
        },
        // Name: Yukidarumon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 129600 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DM20_METAL_MAMEMON_ANIM_INDEX
            },
        },
        // Name: Yukimi Botamon
        {
            // Stage: Baby I
            .conditions = { .next_evolution_time_sec = 600 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Yuramon
        {
            // Stage: Baby I
            .conditions = { .next_evolution_time_sec = 600 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DM20_TANEMON_ANIM_INDEX
            },
        },
        // Name: Zubaeagermon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 129600 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DM20_DURAMON_ANIM_INDEX
            },
        },
        // Name: Zubamon
        {
            // Stage: Child
            .conditions = { .next_evolution_time_sec = 86400 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DM20_ZUBAEAGERMON_ANIM_INDEX
            },
        },
        // Name: Zurumon
        {
            // Stage: Baby I
            .conditions = { .next_evolution_time_sec = 600 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DM20_PAGUMON_ANIM_INDEX
            },
        },

    };
    animation::animation_evolution_data_t get_dm20_evolution_data(size_t index) {
        using namespace assets;
        assert(LEN_ARRAY(dm20_evol_data_table) == DM20_ANIM_COUNT);
        assert(index < DM20_ANIM_COUNT);
        auto result = dm20_evol_data_table[index];
        platform::details::asset_unload(dm20_evol_data_table, sizeof(animation::animation_evolution_data_t)*DM20_ANIM_COUNT);
        return result;
    }
}

