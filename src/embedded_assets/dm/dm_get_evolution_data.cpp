#include "embedded_assets/embedded_image.h"
#include "embedded_assets/dm/dm.hpp"
#include "embedded_assets/dm/dm_evol.h"
#include "graphics/animation_shared_memory.h"

/// @NOTE: Generated evolution data dm

namespace bongocat::assets {
    static constexpr animation::animation_evolution_data_t dm_evol_data_table[] ASSETS_DATA_EVOL_SECTION = {
        // Name: Agumon
        {
            // Stage: Child
            .conditions = { .next_evolution_time_sec = 86400 },
            
            .num_animation_indices = 5,
            .animation_indices = {
                DM_GREYMON_ANIM_INDEX ,DM_TYRANOMON_ANIM_INDEX ,DM_DEVIMON_ANIM_INDEX ,DM_MERAMON_ANIM_INDEX ,DM_NUMEMON_ANIM_INDEX
            },
        },
        // Name: Airdramon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 129600 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DM_METAL_GREYMON_ANIM_INDEX
            },
        },
        // Name: Andromon
        {
            // Stage: Perfect
            .conditions = { .next_evolution_time_sec = 172800 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Angemon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 129600 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DM_SKULL_GREYMON_ANIM_INDEX
            },
        },
        // Name: Atlur Kabuterimon
        {
            // Stage: Perfect
            .conditions = { .next_evolution_time_sec = 172800 },
            
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
                DM_GIROMON_ANIM_INDEX
            },
        },
        // Name: Betamon
        {
            // Stage: Child
            .conditions = { .next_evolution_time_sec = 86400 },
            
            .num_animation_indices = 5,
            .animation_indices = {
                DM_DEVIMON_ANIM_INDEX ,DM_MERAMON_ANIM_INDEX ,DM_AIRDRAMON_ANIM_INDEX ,DM_SEADRAMON_ANIM_INDEX ,DM_NUMEMON_ANIM_INDEX
            },
        },
        // Name: Birdramon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 129600 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DM_SKULL_GREYMON_ANIM_INDEX
            },
        },
        // Name: Botamon
        {
            // Stage: Baby I
            .conditions = { .next_evolution_time_sec = 600 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DM_KOROMON_ANIM_INDEX
            },
        },
        // Name: Bubbmon
        {
            // Stage: Baby I
            .conditions = { .next_evolution_time_sec = 600 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DM_MOCHIMON_ANIM_INDEX
            },
        },
        // Name: Centalmon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 129600 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DM_GIROMON_ANIM_INDEX
            },
        },
        // Name: Cockatrimon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 129600 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DM_PICCOLOMON_ANIM_INDEX
            },
        },
        // Name: Coelamon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 129600 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DM_MEGADRAMON_ANIM_INDEX
            },
        },
        // Name: Cyclomon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 129600 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DM_NANOMON_ANIM_INDEX
            },
        },
        // Name: Dark Tyranomon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 129600 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DM_METAL_TYRANOMON_ANIM_INDEX
            },
        },
        // Name: Deltamon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 129600 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DM_NANOMON_ANIM_INDEX
            },
        },
        // Name: Devidramon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 129600 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DM_METAL_TYRANOMON_ANIM_INDEX
            },
        },
        // Name: Devimon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 129600 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DM_METAL_GREYMON_ANIM_INDEX
            },
        },
        // Name: Digitamamon
        {
            // Stage: Perfect
            .conditions = { .next_evolution_time_sec = 172800 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Drimogemon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 129600 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DM_GIROMON_ANIM_INDEX
            },
        },
        // Name: Elecmon
        {
            // Stage: Child
            .conditions = { .next_evolution_time_sec = 86400 },
            
            .num_animation_indices = 5,
            .animation_indices = {
                DM_ANGEMON_ANIM_INDEX ,DM_YUKIDARUMON_ANIM_INDEX ,DM_BIRDRAMON_ANIM_INDEX ,DM_WHAMON_ANIM_INDEX ,DM_VEGIMON_ANIM_INDEX
            },
        },
        // Name: Etemon
        {
            // Stage: Perfect
            .conditions = { .next_evolution_time_sec = 172800 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Ex-Tyranomon
        {
            // Stage: Perfect
            .conditions = { .next_evolution_time_sec = 172800 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Flymon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 129600 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DM_METAL_TYRANOMON_ANIM_INDEX
            },
        },
        // Name: Gabumon
        {
            // Stage: Child
            .conditions = { .next_evolution_time_sec = 86400 },
            
            .num_animation_indices = 5,
            .animation_indices = {
                DM_KABUTERIMON_ANIM_INDEX ,DM_GARURUMON_ANIM_INDEX ,DM_ANGEMON_ANIM_INDEX ,DM_YUKIDARUMON_ANIM_INDEX ,DM_VEGIMON_ANIM_INDEX
            },
        },
        // Name: Garurumon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 129600 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DM_METAL_MAMEMON_ANIM_INDEX
            },
        },
        // Name: Gazimon
        {
            // Stage: Child
            .conditions = { .next_evolution_time_sec = 86400 },
            
            .num_animation_indices = 5,
            .animation_indices = {
                DM_DARK_TYRANOMON_ANIM_INDEX ,DM_CYCLOMON_ANIM_INDEX ,DM_DEVIDRAMON_ANIM_INDEX ,DM_TUSKMON_ANIM_INDEX ,DM_RAREMON_ANIM_INDEX
            },
        },
        // Name: Gekomon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 129600 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DM_TONOSAMA_GEKOMON_ANIM_INDEX
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
                DM_DEVIDRAMON_ANIM_INDEX ,DM_TUSKMON_ANIM_INDEX ,DM_FLYMON_ANIM_INDEX ,DM_DELTAMON_ANIM_INDEX ,DM_RAREMON_ANIM_INDEX
            },
        },
        // Name: Greymon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 129600 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DM_METAL_GREYMON_ANIM_INDEX
            },
        },
        // Name: Kabuterimon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 129600 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DM_SKULL_GREYMON_ANIM_INDEX
            },
        },
        // Name: Koromon
        {
            // Stage: Baby II
            .conditions = { .next_evolution_time_sec = 21600 },
            
            .num_animation_indices = 2,
            .animation_indices = {
                DM_AGUMON_ANIM_INDEX ,DM_BETAMON_ANIM_INDEX
            },
        },
        // Name: Kunemon
        {
            // Stage: Child
            .conditions = { .next_evolution_time_sec = 86400 },
            
            .num_animation_indices = 5,
            .animation_indices = {
                DM_OGREMON_ANIM_INDEX ,DM_BAKEMON_ANIM_INDEX ,DM_SHELLMON_ANIM_INDEX ,DM_DRIMOGEMON_ANIM_INDEX ,DM_SCUMON_ANIM_INDEX
            },
        },
        // Name: Kuwagamon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 129600 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DM_PICCOLOMON_ANIM_INDEX
            },
        },
        // Name: Leomon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 129600 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DM_MEGADRAMON_ANIM_INDEX
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
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Meramon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 129600 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DM_MAMEMON_ANIM_INDEX
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
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Metal Tyranomon
        {
            // Stage: Perfect
            .conditions = { .next_evolution_time_sec = 172800 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DM_MUGENDRAMON_ANIM_INDEX
            },
        },
        // Name: Mochimon
        {
            // Stage: Baby II
            .conditions = { .next_evolution_time_sec = 21600 },
            
            .num_animation_indices = 2,
            .animation_indices = {
                DM_TENTOMON_ANIM_INDEX ,DM_OTAMAMON_ANIM_INDEX
            },
        },
        // Name: Mojyamon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 129600 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DM_PICCOLOMON_ANIM_INDEX
            },
        },
        // Name: Monochromon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 129600 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DM_MEGADRAMON_ANIM_INDEX
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
        // Name: Mugendramon
        {
            // Stage: Ultimate
            .conditions = { .next_evolution_time_sec = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Nanimon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 129600 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DM_DIGITAMAMON_ANIM_INDEX
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
                DM_MONZAEMON_ANIM_INDEX
            },
        },
        // Name: Ogremon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 129600 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DM_ANDROMON_ANIM_INDEX
            },
        },
        // Name: Otamamon
        {
            // Stage: Child
            .conditions = { .next_evolution_time_sec = 86400 },
            
            .num_animation_indices = 4,
            .animation_indices = {
                DM_TORTAMON_ANIM_INDEX ,DM_KUWAGAMON_ANIM_INDEX ,DM_MONOCHROMON_ANIM_INDEX ,DM_GEKOMON_ANIM_INDEX
            },
        },
        // Name: Pagumon
        {
            // Stage: Baby II
            .conditions = { .next_evolution_time_sec = 21600 },
            
            .num_animation_indices = 2,
            .animation_indices = {
                DM_GAZIMON_ANIM_INDEX ,DM_GIZAMON_ANIM_INDEX
            },
        },
        // Name: Palmon
        {
            // Stage: Child
            .conditions = { .next_evolution_time_sec = 86400 },
            
            .num_animation_indices = 5,
            .animation_indices = {
                DM_LEOMON_ANIM_INDEX ,DM_KUWAGAMON_ANIM_INDEX ,DM_COELAMON_ANIM_INDEX ,DM_MOJYAMON_ANIM_INDEX ,DM_NANIMON_ANIM_INDEX
            },
        },
        // Name: Patamon
        {
            // Stage: Child
            .conditions = { .next_evolution_time_sec = 86400 },
            
            .num_animation_indices = 5,
            .animation_indices = {
                DM_UNIMON_ANIM_INDEX ,DM_CENTALMON_ANIM_INDEX ,DM_OGREMON_ANIM_INDEX ,DM_BAKEMON_ANIM_INDEX ,DM_SCUMON_ANIM_INDEX
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
        // Name: Piyomon
        {
            // Stage: Child
            .conditions = { .next_evolution_time_sec = 86400 },
            
            .num_animation_indices = 5,
            .animation_indices = {
                DM_MONOCHROMON_ANIM_INDEX ,DM_COCKATRIMON_ANIM_INDEX ,DM_LEOMON_ANIM_INDEX ,DM_KUWAGAMON_ANIM_INDEX ,DM_NANIMON_ANIM_INDEX
            },
        },
        // Name: Poyomon
        {
            // Stage: Baby I
            .conditions = { .next_evolution_time_sec = 600 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DM_TOKOMON_ANIM_INDEX
            },
        },
        // Name: Punimon
        {
            // Stage: Baby I
            .conditions = { .next_evolution_time_sec = 600 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DM_TUNOMON_ANIM_INDEX
            },
        },
        // Name: Raremon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 129600 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DM_EX_TYRANOMON_ANIM_INDEX
            },
        },
        // Name: Scumon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 129600 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DM_ETEMON_ANIM_INDEX
            },
        },
        // Name: Seadramon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 129600 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DM_MAMEMON_ANIM_INDEX
            },
        },
        // Name: Shellmon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 129600 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DM_ANDROMON_ANIM_INDEX
            },
        },
        // Name: Skull Greymon
        {
            // Stage: Perfect
            .conditions = { .next_evolution_time_sec = 172800 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Starmon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 129600 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Tanemon
        {
            // Stage: Baby II
            .conditions = { .next_evolution_time_sec = 21600 },
            
            .num_animation_indices = 2,
            .animation_indices = {
                DM_PIYOMON_ANIM_INDEX ,DM_PALMON_ANIM_INDEX
            },
        },
        // Name: Tentomon
        {
            // Stage: Child
            .conditions = { .next_evolution_time_sec = 86400 },
            
            .num_animation_indices = 5,
            .animation_indices = {
                DM_KABUTERIMON_ANIM_INDEX ,DM_STARMON_ANIM_INDEX ,DM_TORTAMON_ANIM_INDEX ,DM_KUWAGAMON_ANIM_INDEX ,DM_GEKOMON_ANIM_INDEX
            },
        },
        // Name: Tokomon
        {
            // Stage: Baby II
            .conditions = { .next_evolution_time_sec = 21600 },
            
            .num_animation_indices = 2,
            .animation_indices = {
                DM_PATAMON_ANIM_INDEX ,DM_KUNEMON_ANIM_INDEX
            },
        },
        // Name: Tonosama Gekomon
        {
            // Stage: Perfect
            .conditions = { .next_evolution_time_sec = 172800 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Tortamon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 129600 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DM_ATLUR_KABUTERIMON_ANIM_INDEX
            },
        },
        // Name: Tunomon
        {
            // Stage: Baby II
            .conditions = { .next_evolution_time_sec = 21600 },
            
            .num_animation_indices = 2,
            .animation_indices = {
                DM_GABUMON_ANIM_INDEX ,DM_ELECMON_ANIM_INDEX
            },
        },
        // Name: Tuskmon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 129600 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DM_NANOMON_ANIM_INDEX
            },
        },
        // Name: Tyranomon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 129600 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DM_MAMEMON_ANIM_INDEX
            },
        },
        // Name: Unimon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 129600 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DM_ANDROMON_ANIM_INDEX
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
                DM_VADEMON_ANIM_INDEX
            },
        },
        // Name: Whamon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 129600 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DM_METAL_MAMEMON_ANIM_INDEX
            },
        },
        // Name: Yukidarumon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 129600 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DM_METAL_MAMEMON_ANIM_INDEX
            },
        },
        // Name: Yuramon
        {
            // Stage: Baby I
            .conditions = { .next_evolution_time_sec = 600 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DM_TANEMON_ANIM_INDEX
            },
        },
        // Name: Zurumon
        {
            // Stage: Baby I
            .conditions = { .next_evolution_time_sec = 600 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                DM_PAGUMON_ANIM_INDEX
            },
        },

    };
    animation::animation_evolution_data_t get_dm_evolution_data(size_t index) {
        using namespace assets;
        assert(LEN_ARRAY(dm_evol_data_table) == DM_ANIM_COUNT);
        assert(index < DM_ANIM_COUNT);
        auto result = dm_evol_data_table[index];
        return result;
    }
}

