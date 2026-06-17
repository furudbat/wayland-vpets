#include "embedded_assets/embedded_image.h"
#include "embedded_assets/pen/pen.hpp"
#include "embedded_assets/pen/pen_evol.h"
#include "graphics/animation_shared_memory.h"

/// @NOTE: Generated evolution data pen

namespace bongocat::assets {
    static constexpr animation::animation_evolution_data_t pen_evol_data_table[] = {
        // Name: Aero V-dramon
        {
            // Stage: Perfect
            .conditions = { .next_evolution_time_sec = 244800 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PEN_HOUOUMON_ANIM_INDEX
            },
        },
        // Name: Andromon
        {
            // Stage: Perfect
            .conditions = { .next_evolution_time_sec = 244800 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Angewomon
        {
            // Stage: Perfect
            .conditions = { .next_evolution_time_sec = 244800 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PEN_OMEGAMON_ANIM_INDEX
            },
        },
        // Name: Anomalocarimon
        {
            // Stage: Perfect
            .conditions = { .next_evolution_time_sec = 244800 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PEN_METAL_SEADRAMON_ANIM_INDEX
            },
        },
        // Name: Asuramon
        {
            // Stage: Perfect
            .conditions = { .next_evolution_time_sec = 244800 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PEN_WAR_GREYMON_ANIM_INDEX
            },
        },
        // Name: Atlur Kabuterimon
        {
            // Stage: Perfect
            .conditions = { .next_evolution_time_sec = 244800 },
            
            .num_animation_indices = 2,
            .animation_indices = {
                PEN_HERAKLE_KABUTERIMON_ANIM_INDEX ,PEN_HOLYDRAMON_ANIM_INDEX
            },
        },
        // Name: Bakemon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 216000 },
            
            .num_animation_indices = 3,
            .animation_indices = {
                PEN_VAMDEMON_ANIM_INDEX ,PEN_FANTOMON_ANIM_INDEX ,PEN_PUMPMON_ANIM_INDEX
            },
        },
        // Name: Bakumon
        {
            // Stage: Child
            .conditions = { .next_evolution_time_sec = 72000 },
            
            .num_animation_indices = 5,
            .animation_indices = {
                PEN_PICO_DEVIMON_ANIM_INDEX ,PEN_HANUMON_ANIM_INDEX ,PEN_GARURUMON_ANIM_INDEX ,PEN_MERAMON_ANIM_INDEX ,PEN_WIZARMON_ANIM_INDEX
            },
        },
        // Name: Big Mamemon
        {
            // Stage: Perfect
            .conditions = { .next_evolution_time_sec = 244800 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PEN_METAL_GARURUMON_ANIM_INDEX
            },
        },
        // Name: Birdramon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 216000 },
            
            .num_animation_indices = 3,
            .animation_indices = {
                PEN_AERO_V_DRAMON_ANIM_INDEX ,PEN_GARUDAMON_ANIM_INDEX ,PEN_DELUMON_ANIM_INDEX
            },
        },
        // Name: Blossomon
        {
            // Stage: Perfect
            .conditions = { .next_evolution_time_sec = 244800 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PEN_GRIFFOMON_ANIM_INDEX
            },
        },
        // Name: Boltmon
        {
            // Stage: Ultimate
            .conditions = { .next_evolution_time_sec = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Bubbmon
        {
            // Stage: Baby I
            .conditions = { .next_evolution_time_sec = 3600 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PEN_MOCHIMON_ANIM_INDEX
            },
        },
        // Name: Candmon
        {
            // Stage: Child
            .conditions = { .next_evolution_time_sec = 72000 },
            
            .num_animation_indices = 4,
            .animation_indices = {
                PEN_MERAMON_ANIM_INDEX ,PEN_WIZARMON_ANIM_INDEX ,PEN_DEVIMON_ANIM_INDEX ,PEN_BAKEMON_ANIM_INDEX
            },
        },
        // Name: Caprimon
        {
            // Stage: Baby II
            .conditions = { .next_evolution_time_sec = 57600 },
            
            .num_animation_indices = 3,
            .animation_indices = {
                PEN_TOY_AGUMON_ANIM_INDEX ,PEN_KOKUWAMON_ANIM_INDEX ,PEN_HAGURUMON_ANIM_INDEX
            },
        },
        // Name: Choromon
        {
            // Stage: Baby I
            .conditions = { .next_evolution_time_sec = 3600 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PEN_CAPRIMON_ANIM_INDEX
            },
        },
        // Name: Clockmon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 216000 },
            
            .num_animation_indices = 5,
            .animation_indices = {
                PEN_KNIGHTMON_ANIM_INDEX ,PEN_BIG_MAMEMON_ANIM_INDEX ,PEN_ANDROMON_ANIM_INDEX ,PEN_CYBERDRAMON_ANIM_INDEX ,PEN_WARU_MONZAEMON_ANIM_INDEX
            },
        },
        // Name: Coelamon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 216000 },
            
            .num_animation_indices = 4,
            .animation_indices = {
                PEN_MEGA_SEADRAMON_ANIM_INDEX ,PEN_ANOMALOCARIMON_ANIM_INDEX ,PEN_WHAMON_ANIM_INDEX ,PEN_DAGOMON_ANIM_INDEX
            },
        },
        // Name: Cyberdramon
        {
            // Stage: Perfect
            .conditions = { .next_evolution_time_sec = 244800 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Dagomon
        {
            // Stage: Perfect
            .conditions = { .next_evolution_time_sec = 244800 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PEN_PUKUMON_ANIM_INDEX
            },
        },
        // Name: Death Meramon
        {
            // Stage: Perfect
            .conditions = { .next_evolution_time_sec = 244800 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PEN_BOLTMON_ANIM_INDEX
            },
        },
        // Name: Delumon
        {
            // Stage: Perfect
            .conditions = { .next_evolution_time_sec = 244800 },
            
            .num_animation_indices = 3,
            .animation_indices = {
                PEN_HOUOUMON_ANIM_INDEX ,PEN_GRIFFOMON_ANIM_INDEX ,PEN_ROSEMON_ANIM_INDEX
            },
        },
        // Name: Devimon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 216000 },
            
            .num_animation_indices = 4,
            .animation_indices = {
                PEN_VAMDEMON_ANIM_INDEX ,PEN_LADY_DEVIMON_ANIM_INDEX ,PEN_FANTOMON_ANIM_INDEX ,PEN_PUMPMON_ANIM_INDEX
            },
        },
        // Name: Dokugumon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 216000 },
            
            .num_animation_indices = 3,
            .animation_indices = {
                PEN_WERE_GARURUMON_ANIM_INDEX ,PEN_DEATH_MERAMON_ANIM_INDEX ,PEN_VAMDEMON_ANIM_INDEX
            },
        },
        // Name: Ebidramon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 216000 },
            
            .num_animation_indices = 4,
            .animation_indices = {
                PEN_MEGA_SEADRAMON_ANIM_INDEX ,PEN_HANGYOMON_ANIM_INDEX ,PEN_WHAMON_ANIM_INDEX ,PEN_DAGOMON_ANIM_INDEX
            },
        },
        // Name: Fantomon
        {
            // Stage: Perfect
            .conditions = { .next_evolution_time_sec = 244800 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PEN_PIEMON_ANIM_INDEX
            },
        },
        // Name: Floramon
        {
            // Stage: Child
            .conditions = { .next_evolution_time_sec = 72000 },
            
            .num_animation_indices = 4,
            .animation_indices = {
                PEN_TOGEMON_ANIM_INDEX ,PEN_KIWIMON_ANIM_INDEX ,PEN_WOODMON_ANIM_INDEX ,PEN_RED_VEGIMON_ANIM_INDEX
            },
        },
        // Name: Ganimon
        {
            // Stage: Child
            .conditions = { .next_evolution_time_sec = 72000 },
            
            .num_animation_indices = 5,
            .animation_indices = {
                PEN_RUKAMON_ANIM_INDEX ,PEN_SEADRAMON_ANIM_INDEX ,PEN_COELAMON_ANIM_INDEX ,PEN_EBIDRAMON_ANIM_INDEX ,PEN_GESOMON_ANIM_INDEX
            },
        },
        // Name: Garudamon
        {
            // Stage: Perfect
            .conditions = { .next_evolution_time_sec = 244800 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Garurumon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 216000 },
            
            .num_animation_indices = 3,
            .animation_indices = {
                PEN_MAMMON_ANIM_INDEX ,PEN_WERE_GARURUMON_ANIM_INDEX ,PEN_PUMPMON_ANIM_INDEX
            },
        },
        // Name: Gekomon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 216000 },
            
            .num_animation_indices = 3,
            .animation_indices = {
                PEN_OKUWAMON_ANIM_INDEX ,PEN_TONOSAMA_GEKOMON_ANIM_INDEX ,PEN_PICCOLOMON_ANIM_INDEX
            },
        },
        // Name: Gerbemon
        {
            // Stage: Perfect
            .conditions = { .next_evolution_time_sec = 244800 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PEN_PINOCHIMON_ANIM_INDEX
            },
        },
        // Name: Gesomon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 216000 },
            
            .num_animation_indices = 4,
            .animation_indices = {
                PEN_MARIN_DEVIMON_ANIM_INDEX ,PEN_DAGOMON_ANIM_INDEX ,PEN_ANOMALOCARIMON_ANIM_INDEX ,PEN_HANGYOMON_ANIM_INDEX
            },
        },
        // Name: Gomamon
        {
            // Stage: Child
            .conditions = { .next_evolution_time_sec = 72000 },
            
            .num_animation_indices = 5,
            .animation_indices = {
                PEN_IKKAKUMON_ANIM_INDEX ,PEN_RUKAMON_ANIM_INDEX ,PEN_COELAMON_ANIM_INDEX ,PEN_EBIDRAMON_ANIM_INDEX ,PEN_OCTMON_ANIM_INDEX
            },
        },
        // Name: Gottsumon
        {
            // Stage: Child
            .conditions = { .next_evolution_time_sec = 72000 },
            
            .num_animation_indices = 5,
            .animation_indices = {
                PEN_TORTAMON_ANIM_INDEX ,PEN_TAILMON_ANIM_INDEX ,PEN_MONOCHROMON_ANIM_INDEX ,PEN_STARMON_ANIM_INDEX ,PEN_GEKOMON_ANIM_INDEX
            },
        },
        // Name: Greymon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 216000 },
            
            .num_animation_indices = 6,
            .animation_indices = {
                PEN_METAL_GREYMON_ANIM_INDEX ,PEN_ANDROMON_ANIM_INDEX ,PEN_CYBERDRAMON_ANIM_INDEX ,PEN_BIG_MAMEMON_ANIM_INDEX ,PEN_ASURAMON_ANIM_INDEX ,PEN_METAL_MAMEMON_ANIM_INDEX
            },
        },
        // Name: Griffomon
        {
            // Stage: Ultimate
            .conditions = { .next_evolution_time_sec = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Guardromon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 216000 },
            
            .num_animation_indices = 3,
            .animation_indices = {
                PEN_MEGADRAMON_ANIM_INDEX ,PEN_WARU_MONZAEMON_ANIM_INDEX ,PEN_BIG_MAMEMON_ANIM_INDEX
            },
        },
        // Name: Hagurumon
        {
            // Stage: Child
            .conditions = { .next_evolution_time_sec = 72000 },
            
            .num_animation_indices = 5,
            .animation_indices = {
                PEN_GREYMON_ANIM_INDEX ,PEN_TANKMON_ANIM_INDEX ,PEN_THUNDERBALLMON_ANIM_INDEX ,PEN_GUARDROMON_ANIM_INDEX ,PEN_MECHANORIMON_ANIM_INDEX
            },
        },
        // Name: Hangymon
        {
            // Stage: Perfect
            .conditions = { .next_evolution_time_sec = 244800 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Hangyomon
        {
            // Stage: Perfect
            .conditions = { .next_evolution_time_sec = 244800 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Hanumon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 216000 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PEN_MAMMON_ANIM_INDEX
            },
        },
        // Name: Herakle Kabuterimon
        {
            // Stage: Ultimate
            .conditions = { .next_evolution_time_sec = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Herkule Kabuterimon
        {
            // Stage: Ultimate
            .conditions = { .next_evolution_time_sec = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Holy Angemon
        {
            // Stage: Perfect
            .conditions = { .next_evolution_time_sec = 244800 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PEN_OMEGAMON_ANIM_INDEX
            },
        },
        // Name: Holydramon
        {
            // Stage: Ultimate
            .conditions = { .next_evolution_time_sec = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Hououmon
        {
            // Stage: Ultimate
            .conditions = { .next_evolution_time_sec = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Ignamon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 216000 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Ikkakumon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 216000 },
            
            .num_animation_indices = 4,
            .animation_indices = {
                PEN_ZUDOMON_ANIM_INDEX ,PEN_WHAMON_ANIM_INDEX ,PEN_ANOMALOCARIMON_ANIM_INDEX ,PEN_HANGYOMON_ANIM_INDEX
            },
        },
        // Name: Jyagamon
        {
            // Stage: Perfect
            .conditions = { .next_evolution_time_sec = 244800 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Jyureimon
        {
            // Stage: Perfect
            .conditions = { .next_evolution_time_sec = 244800 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PEN_PINOCHIMON_ANIM_INDEX
            },
        },
        // Name: Kabuterimon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 216000 },
            
            .num_animation_indices = 4,
            .animation_indices = {
                PEN_ATLUR_KABUTERIMON_ANIM_INDEX ,PEN_JYAGAMON_ANIM_INDEX ,PEN_ANGEWOMON_ANIM_INDEX ,PEN_PICCOLOMON_ANIM_INDEX
            },
        },
        // Name: Kiwimon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 216000 },
            
            .num_animation_indices = 5,
            .animation_indices = {
                PEN_BLOSSOMON_ANIM_INDEX ,PEN_LILIMON_ANIM_INDEX ,PEN_DELUMON_ANIM_INDEX ,PEN_GARUDAMON_ANIM_INDEX ,PEN_GERBEMON_ANIM_INDEX
            },
        },
        // Name: Knightmon
        {
            // Stage: Perfect
            .conditions = { .next_evolution_time_sec = 244800 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Kokuwamon
        {
            // Stage: Child
            .conditions = { .next_evolution_time_sec = 72000 },
            
            .num_animation_indices = 5,
            .animation_indices = {
                PEN_REVOLMON_ANIM_INDEX ,PEN_TANKMON_ANIM_INDEX ,PEN_THUNDERBALLMON_ANIM_INDEX ,PEN_CLOCKMON_ANIM_INDEX ,PEN_GUARDROMON_ANIM_INDEX
            },
        },
        // Name: Kuwagamon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 216000 },
            
            .num_animation_indices = 3,
            .animation_indices = {
                PEN_OKUWAMON_ANIM_INDEX ,PEN_TONOSAMA_GEKOMON_ANIM_INDEX ,PEN_PICCOLOMON_ANIM_INDEX
            },
        },
        // Name: Lady Devimon
        {
            // Stage: Perfect
            .conditions = { .next_evolution_time_sec = 244800 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Lilimon
        {
            // Stage: Perfect
            .conditions = { .next_evolution_time_sec = 244800 },
            
            .num_animation_indices = 2,
            .animation_indices = {
                PEN_ROSEMON_ANIM_INDEX ,PEN_GRIFFOMON_ANIM_INDEX
            },
        },
        // Name: Mammon
        {
            // Stage: Perfect
            .conditions = { .next_evolution_time_sec = 244800 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PEN_SKULL_MAMMON_ANIM_INDEX
            },
        },
        // Name: Marin Angemon
        {
            // Stage: Ultimate
            .conditions = { .next_evolution_time_sec = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Marin Devimon
        {
            // Stage: Perfect
            .conditions = { .next_evolution_time_sec = 244800 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PEN_PUKUMON_ANIM_INDEX
            },
        },
        // Name: Mechanorimon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 216000 },
            
            .num_animation_indices = 3,
            .animation_indices = {
                PEN_MEGADRAMON_ANIM_INDEX ,PEN_WARU_MONZAEMON_ANIM_INDEX ,PEN_BIG_MAMEMON_ANIM_INDEX
            },
        },
        // Name: Megadramon
        {
            // Stage: Perfect
            .conditions = { .next_evolution_time_sec = 244800 },
            
            .num_animation_indices = 2,
            .animation_indices = {
                PEN_MUGENDRAMON_ANIM_INDEX ,PEN_VENOM_VAMDEMON_ANIM_INDEX
            },
        },
        // Name: Mega Seadramon
        {
            // Stage: Perfect
            .conditions = { .next_evolution_time_sec = 244800 },
            
            .num_animation_indices = 3,
            .animation_indices = {
                PEN_METAL_SEADRAMON_ANIM_INDEX ,PEN_PLESIOMON_ANIM_INDEX ,PEN_MARIN_ANGEMON_ANIM_INDEX
            },
        },
        // Name: Meramon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 216000 },
            
            .num_animation_indices = 4,
            .animation_indices = {
                PEN_DEATH_MERAMON_ANIM_INDEX ,PEN_PUMPMON_ANIM_INDEX ,PEN_WERE_GARURUMON_ANIM_INDEX ,PEN_FANTOMON_ANIM_INDEX
            },
        },
        // Name: Metal Etemon
        {
            // Stage: Ultimate
            .conditions = { .next_evolution_time_sec = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
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
            .conditions = { .next_evolution_time_sec = 244800 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PEN_WAR_GREYMON_ANIM_INDEX
            },
        },
        // Name: Metal Mamemon
        {
            // Stage: Perfect
            .conditions = { .next_evolution_time_sec = 244800 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PEN_METAL_GARURUMON_ANIM_INDEX
            },
        },
        // Name: Metal Seadramon
        {
            // Stage: Ultimate
            .conditions = { .next_evolution_time_sec = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Mochimon
        {
            // Stage: Baby II
            .conditions = { .next_evolution_time_sec = 57600 },
            
            .num_animation_indices = 3,
            .animation_indices = {
                PEN_TENTOMON_ANIM_INDEX ,PEN_GOTTSUMON_ANIM_INDEX ,PEN_OTAMAMON_ANIM_INDEX
            },
        },
        // Name: Mokumon
        {
            // Stage: Baby I
            .conditions = { .next_evolution_time_sec = 3600 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PEN_PETI_MERAMON_ANIM_INDEX
            },
        },
        // Name: Monochromon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 216000 },
            
            .num_animation_indices = 5,
            .animation_indices = {
                PEN_TRICERAMON_ANIM_INDEX ,PEN_PICCOLOMON_ANIM_INDEX ,PEN_JYAGAMON_ANIM_INDEX ,PEN_ANGEWOMON_ANIM_INDEX ,PEN_TONOSAMA_GEKOMON_ANIM_INDEX
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
        // Name: Mushmon
        {
            // Stage: Child
            .conditions = { .next_evolution_time_sec = 72000 },
            
            .num_animation_indices = 4,
            .animation_indices = {
                PEN_V_DRAMON_ANIM_INDEX ,PEN_BIRDRAMON_ANIM_INDEX ,PEN_WOODMON_ANIM_INDEX ,PEN_RED_VEGIMON_ANIM_INDEX
            },
        },
        // Name: Nyokimon
        {
            // Stage: Baby I
            .conditions = { .next_evolution_time_sec = 3600 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PEN_PYOCOMON_ANIM_INDEX
            },
        },
        // Name: Octmon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 216000 },
            
            .num_animation_indices = 4,
            .animation_indices = {
                PEN_MARIN_DEVIMON_ANIM_INDEX ,PEN_DAGOMON_ANIM_INDEX ,PEN_ANOMALOCARIMON_ANIM_INDEX ,PEN_HANGYOMON_ANIM_INDEX
            },
        },
        // Name: Okuwamon
        {
            // Stage: Perfect
            .conditions = { .next_evolution_time_sec = 244800 },
            
            .num_animation_indices = 3,
            .animation_indices = {
                PEN_HERAKLE_KABUTERIMON_ANIM_INDEX ,PEN_HOLYDRAMON_ANIM_INDEX ,PEN_METAL_ETEMON_ANIM_INDEX
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
        // Name: Otamamon
        {
            // Stage: Child
            .conditions = { .next_evolution_time_sec = 72000 },
            
            .num_animation_indices = 5,
            .animation_indices = {
                PEN_TORTAMON_ANIM_INDEX ,PEN_TAILMON_ANIM_INDEX ,PEN_STARMON_ANIM_INDEX ,PEN_KUWAGAMON_ANIM_INDEX ,PEN_GEKOMON_ANIM_INDEX
            },
        },
        // Name: Palmon
        {
            // Stage: Child
            .conditions = { .next_evolution_time_sec = 72000 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Peti Meramon
        {
            // Stage: Baby II
            .conditions = { .next_evolution_time_sec = 57600 },
            
            .num_animation_indices = 3,
            .animation_indices = {
                PEN_BAKUMON_ANIM_INDEX ,PEN_CANDMON_ANIM_INDEX ,PEN_PICO_DEVIMON_ANIM_INDEX
            },
        },
        // Name: Piccolomon
        {
            // Stage: Perfect
            .conditions = { .next_evolution_time_sec = 244800 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PEN_SABER_LEOMON_ANIM_INDEX
            },
        },
        // Name: Pico Devimon
        {
            // Stage: Child
            .conditions = { .next_evolution_time_sec = 72000 },
            
            .num_animation_indices = 5,
            .animation_indices = {
                PEN_GARURUMON_ANIM_INDEX ,PEN_MERAMON_ANIM_INDEX ,PEN_WIZARMON_ANIM_INDEX ,PEN_DEVIMON_ANIM_INDEX ,PEN_BAKEMON_ANIM_INDEX
            },
        },
        // Name: Piemon
        {
            // Stage: Ultimate
            .conditions = { .next_evolution_time_sec = -1 },
            
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
        // Name: Piyomon
        {
            // Stage: Child
            .conditions = { .next_evolution_time_sec = 72000 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Plesiomon
        {
            // Stage: Ultimate
            .conditions = { .next_evolution_time_sec = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Pukumon
        {
            // Stage: Ultimate
            .conditions = { .next_evolution_time_sec = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Pumpmon
        {
            // Stage: Perfect
            .conditions = { .next_evolution_time_sec = 244800 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PEN_BOLTMON_ANIM_INDEX
            },
        },
        // Name: Pyocomon
        {
            // Stage: Baby II
            .conditions = { .next_evolution_time_sec = 57600 },
            
            .num_animation_indices = 4,
            .animation_indices = {
                PEN_PIYOMON_ANIM_INDEX ,PEN_FLORAMON_ANIM_INDEX ,PEN_PALMON_ANIM_INDEX ,PEN_MUSHMON_ANIM_INDEX
            },
        },
        // Name: Rakamon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 216000 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Red Vegimon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 216000 },
            
            .num_animation_indices = 3,
            .animation_indices = {
                PEN_JYUREIMON_ANIM_INDEX ,PEN_GERBEMON_ANIM_INDEX ,PEN_DELUMON_ANIM_INDEX
            },
        },
        // Name: Revolmon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 216000 },
            
            .num_animation_indices = 4,
            .animation_indices = {
                PEN_METAL_GREYMON_ANIM_INDEX ,PEN_ANDROMON_ANIM_INDEX ,PEN_CYBERDRAMON_ANIM_INDEX ,PEN_BIG_MAMEMON_ANIM_INDEX
            },
        },
        // Name: Rosemon
        {
            // Stage: Ultimate
            .conditions = { .next_evolution_time_sec = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Rukamon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 216000 },
            
            .num_animation_indices = 4,
            .animation_indices = {
                PEN_ZUDOMON_ANIM_INDEX ,PEN_WHAMON_ANIM_INDEX ,PEN_ANOMALOCARIMON_ANIM_INDEX ,PEN_HANGYOMON_ANIM_INDEX
            },
        },
        // Name: Saber Leomon
        {
            // Stage: Ultimate
            .conditions = { .next_evolution_time_sec = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Seadramon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 216000 },
            
            .num_animation_indices = 5,
            .animation_indices = {
                PEN_MEGA_SEADRAMON_ANIM_INDEX ,PEN_ANOMALOCARIMON_ANIM_INDEX ,PEN_HANGYOMON_ANIM_INDEX ,PEN_WHAMON_ANIM_INDEX ,PEN_DAGOMON_ANIM_INDEX
            },
        },
        // Name: Shakomon
        {
            // Stage: Child
            .conditions = { .next_evolution_time_sec = 72000 },
            
            .num_animation_indices = 4,
            .animation_indices = {
                PEN_IKKAKUMON_ANIM_INDEX ,PEN_SEADRAMON_ANIM_INDEX ,PEN_GESOMON_ANIM_INDEX ,PEN_OCTMON_ANIM_INDEX
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
        // Name: Starmon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 216000 },
            
            .num_animation_indices = 5,
            .animation_indices = {
                PEN_TRICERAMON_ANIM_INDEX ,PEN_PICCOLOMON_ANIM_INDEX ,PEN_JYAGAMON_ANIM_INDEX ,PEN_ANGEWOMON_ANIM_INDEX ,PEN_TONOSAMA_GEKOMON_ANIM_INDEX
            },
        },
        // Name: Tailmon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 216000 },
            
            .num_animation_indices = 3,
            .animation_indices = {
                PEN_HOLY_ANGEMON_ANIM_INDEX ,PEN_ANGEWOMON_ANIM_INDEX ,PEN_METAL_MAMEMON_ANIM_INDEX
            },
        },
        // Name: Tankmon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 216000 },
            
            .num_animation_indices = 4,
            .animation_indices = {
                PEN_KNIGHTMON_ANIM_INDEX ,PEN_BIG_MAMEMON_ANIM_INDEX ,PEN_ANDROMON_ANIM_INDEX ,PEN_WARU_MONZAEMON_ANIM_INDEX
            },
        },
        // Name: Tentomon
        {
            // Stage: Child
            .conditions = { .next_evolution_time_sec = 72000 },
            
            .num_animation_indices = 5,
            .animation_indices = {
                PEN_KABUTERIMON_ANIM_INDEX ,PEN_TORTAMON_ANIM_INDEX ,PEN_TAILMON_ANIM_INDEX ,PEN_KUWAGAMON_ANIM_INDEX ,PEN_GEKOMON_ANIM_INDEX
            },
        },
        // Name: Thunderballmon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 216000 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Togemon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 216000 },
            
            .num_animation_indices = 5,
            .animation_indices = {
                PEN_BLOSSOMON_ANIM_INDEX ,PEN_LILIMON_ANIM_INDEX ,PEN_DELUMON_ANIM_INDEX ,PEN_GARUDAMON_ANIM_INDEX ,PEN_GERBEMON_ANIM_INDEX
            },
        },
        // Name: Tonosama Gekomon
        {
            // Stage: Perfect
            .conditions = { .next_evolution_time_sec = 244800 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PEN_METAL_ETEMON_ANIM_INDEX
            },
        },
        // Name: Tortamon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 216000 },
            
            .num_animation_indices = 3,
            .animation_indices = {
                PEN_ATLUR_KABUTERIMON_ANIM_INDEX ,PEN_JYAGAMON_ANIM_INDEX ,PEN_PICCOLOMON_ANIM_INDEX
            },
        },
        // Name: Toy Agumon
        {
            // Stage: Child
            .conditions = { .next_evolution_time_sec = 72000 },
            
            .num_animation_indices = 5,
            .animation_indices = {
                PEN_GREYMON_ANIM_INDEX ,PEN_REVOLMON_ANIM_INDEX ,PEN_TANKMON_ANIM_INDEX ,PEN_THUNDERBALLMON_ANIM_INDEX ,PEN_CLOCKMON_ANIM_INDEX
            },
        },
        // Name: Triceramon
        {
            // Stage: Perfect
            .conditions = { .next_evolution_time_sec = 244800 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PEN_SABER_LEOMON_ANIM_INDEX
            },
        },
        // Name: Vamdemon
        {
            // Stage: Perfect
            .conditions = { .next_evolution_time_sec = 244800 },
            
            .num_animation_indices = 2,
            .animation_indices = {
                PEN_PIEMON_ANIM_INDEX ,PEN_SKULL_MAMMON_ANIM_INDEX
            },
        },
        // Name: V-dramon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 216000 },
            
            .num_animation_indices = 3,
            .animation_indices = {
                PEN_AERO_V_DRAMON_ANIM_INDEX ,PEN_GARUDAMON_ANIM_INDEX ,PEN_DELUMON_ANIM_INDEX
            },
        },
        // Name: Vemdemon
        {
            // Stage: Perfect
            .conditions = { .next_evolution_time_sec = 244800 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Venom Vamdemon
        {
            // Stage: Ultimate
            .conditions = { .next_evolution_time_sec = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
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
        // Name: Waru Monzaemon
        {
            // Stage: Perfect
            .conditions = { .next_evolution_time_sec = 244800 },
            
            .num_animation_indices = 2,
            .animation_indices = {
                PEN_MUGENDRAMON_ANIM_INDEX ,PEN_VENOM_VAMDEMON_ANIM_INDEX
            },
        },
        // Name: Waru Mozaemon
        {
            // Stage: Perfect
            .conditions = { .next_evolution_time_sec = 244800 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Were Garurumon
        {
            // Stage: Perfect
            .conditions = { .next_evolution_time_sec = 244800 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Whamon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 216000 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Wizarmon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 216000 },
            
            .num_animation_indices = 4,
            .animation_indices = {
                PEN_DEATH_MERAMON_ANIM_INDEX ,PEN_PUMPMON_ANIM_INDEX ,PEN_WERE_GARURUMON_ANIM_INDEX ,PEN_FANTOMON_ANIM_INDEX
            },
        },
        // Name: Woodmon
        {
            // Stage: Adult
            .conditions = { .next_evolution_time_sec = 216000 },
            
            .num_animation_indices = 3,
            .animation_indices = {
                PEN_JYUREIMON_ANIM_INDEX ,PEN_GERBEMON_ANIM_INDEX ,PEN_DELUMON_ANIM_INDEX
            },
        },
        // Name: Zudomon
        {
            // Stage: Perfect
            .conditions = { .next_evolution_time_sec = 244800 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PEN_MARIN_ANGEMON_ANIM_INDEX
            },
        },

    };
    animation::animation_evolution_data_t get_pen_evolution_data(size_t index) {
        using namespace assets;
        assert(LEN_ARRAY(pen_evol_data_table) == PEN_ANIM_COUNT);
        assert(index < PEN_ANIM_COUNT);
        return pen_evol_data_table[index];
    }
}

