#include "embedded_assets/embedded_image.h"
#include "embedded_assets/pmd/pmd.hpp"
#include "embedded_assets/pmd/pmd_evol.h"
#include "graphics/animation_shared_memory.h"

namespace bongocat::assets {
    animation::animation_evolution_data_t get_pmd_evolution_data(size_t index) {
        switch (index) {
            case PMD_BULBASAUR_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 16 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_IVYSAUR_ANIM_INDEX
                },
              };
            case PMD_IVYSAUR_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_VENUSAUR_ANIM_INDEX
                },
              };
            case PMD_VENUSAUR_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_CHARMANDER_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 16 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_CHARMELEON_ANIM_INDEX
                },
              };
            case PMD_CHARMELEON_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 36 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_CHARIZARD_ANIM_INDEX
                },
              };
            case PMD_CHARIZARD_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_SQUIRTLE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 16 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_WARTORTLE_ANIM_INDEX
                },
              };
            case PMD_WARTORTLE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 36 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_BLASTOISE_ANIM_INDEX
                },
              };
            case PMD_BLASTOISE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_CATERPIE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 7 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_METAPOD_ANIM_INDEX
                },
              };
            case PMD_METAPOD_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 10 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_BUTTERFREE_ANIM_INDEX
                },
              };
            case PMD_BUTTERFREE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_WEEDLE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 7 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_KAKUNA_ANIM_INDEX
                },
              };
            case PMD_KAKUNA_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 10 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_BEEDRILL_ANIM_INDEX
                },
              };
            case PMD_BEEDRILL_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_PIDGEY_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 18 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_PIDGEOTTO_ANIM_INDEX
                },
              };
            case PMD_PIDGEOTTO_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 36 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_PIDGEOT_ANIM_INDEX
                },
              };
            case PMD_PIDGEOT_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_RATTATA_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 20 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_RATICATE_ANIM_INDEX
                },
              };
            case PMD_RATICATE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_SPEAROW_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 20 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_FEAROW_ANIM_INDEX
                },
              };
            case PMD_FEAROW_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_EKANS_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 22 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_ARBOK_ANIM_INDEX
                },
              };
            case PMD_ARBOK_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_PIKACHU_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_RAICHU_ANIM_INDEX
                },
              };
            case PMD_RAICHU_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_SANDSHREW_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 22 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_SANDSLASH_ANIM_INDEX
                },
              };
            case PMD_SANDSLASH_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_NIDORAN_F_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 16 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_NIDORINA_ANIM_INDEX
                },
              };
            case PMD_NIDORINA_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_NIDOQUEEN_ANIM_INDEX
                },
              };
            case PMD_NIDOQUEEN_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_NIDORAN_M_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 16 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_NIDORINO_ANIM_INDEX
                },
              };
            case PMD_NIDORINO_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_NIDOKING_ANIM_INDEX
                },
              };
            case PMD_NIDOKING_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_CLEFAIRY_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_CLEFABLE_ANIM_INDEX
                },
              };
            case PMD_CLEFABLE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_VULPIX_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_NINETALES_ANIM_INDEX
                },
              };
            case PMD_NINETALES_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_JIGGLYPUFF_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_WIGGLYTUFF_ANIM_INDEX
                },
              };
            case PMD_WIGGLYTUFF_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_ZUBAT_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 22 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_GOLBAT_ANIM_INDEX
                },
              };
            case PMD_GOLBAT_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 24 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_CROBAT_ANIM_INDEX
                },
              };
            case PMD_ODDISH_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 21 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_GLOOM_ANIM_INDEX
                },
              };
            case PMD_GLOOM_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
                
                .num_animation_indices = 2,
                .animation_indices = {
                  PMD_VILEPLUME_ANIM_INDEX ,PMD_BELLOSSOM_ANIM_INDEX
                },
              };
            case PMD_VILEPLUME_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_PARAS_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 24 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_PARASECT_ANIM_INDEX
                },
              };
            case PMD_PARASECT_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_VENONAT_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 31 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_VENOMOTH_ANIM_INDEX
                },
              };
            case PMD_VENOMOTH_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_DIGLETT_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 26 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_DUGTRIO_ANIM_INDEX
                },
              };
            case PMD_DUGTRIO_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_MEOWTH_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 24 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_PERSIAN_ANIM_INDEX
                },
              };
            case PMD_PERSIAN_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_PSYDUCK_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 33 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_GOLDUCK_ANIM_INDEX
                },
              };
            case PMD_GOLDUCK_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_MANKEY_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 28 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_PRIMEAPE_ANIM_INDEX
                },
              };
            case PMD_PRIMEAPE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 24 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_GROWLITHE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_ARCANINE_ANIM_INDEX
                },
              };
            case PMD_ARCANINE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_POLIWAG_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 25 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_POLIWHIRL_ANIM_INDEX
                },
              };
            case PMD_POLIWHIRL_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
                
                .num_animation_indices = 2,
                .animation_indices = {
                  PMD_POLIWRATH_ANIM_INDEX ,PMD_POLITOED_ANIM_INDEX
                },
              };
            case PMD_POLIWRATH_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_ABRA_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 16 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_KADABRA_ANIM_INDEX
                },
              };
            case PMD_KADABRA_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 28 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_ALAKAZAM_ANIM_INDEX
                },
              };
            case PMD_ALAKAZAM_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_MACHOP_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 28 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_MACHOKE_ANIM_INDEX
                },
              };
            case PMD_MACHOKE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 28 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_MACHAMP_ANIM_INDEX
                },
              };
            case PMD_MACHAMP_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_BELLSPROUT_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 21 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_WEEPINBELL_ANIM_INDEX
                },
              };
            case PMD_WEEPINBELL_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_VICTREEBEL_ANIM_INDEX
                },
              };
            case PMD_VICTREEBEL_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_TENTACOOL_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 30 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_TENTACRUEL_ANIM_INDEX
                },
              };
            case PMD_TENTACRUEL_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_GEODUDE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 25 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_GRAVELER_ANIM_INDEX
                },
              };
            case PMD_GRAVELER_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 28 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_GOLEM_ANIM_INDEX
                },
              };
            case PMD_GOLEM_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_PONYTA_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 40 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_RAPIDASH_ANIM_INDEX
                },
              };
            case PMD_RAPIDASH_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_SLOWPOKE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
                
                .num_animation_indices = 2,
                .animation_indices = {
                  PMD_SLOWBRO_ANIM_INDEX ,PMD_SLOWKING_ANIM_INDEX
                },
              };
            case PMD_SLOWBRO_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_MAGNEMITE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 30 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_MAGNETON_ANIM_INDEX
                },
              };
            case PMD_MAGNETON_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 24 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_MAGNEZONE_ANIM_INDEX
                },
              };
            case PMD_FARFETCHD_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 24 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_SIRFETCHD_ANIM_INDEX
                },
              };
            case PMD_DODUO_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 31 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_DODRIO_ANIM_INDEX
                },
              };
            case PMD_DODRIO_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_SEEL_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 34 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_DEWGONG_ANIM_INDEX
                },
              };
            case PMD_DEWGONG_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_GRIMER_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 38 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_MUK_ANIM_INDEX
                },
              };
            case PMD_MUK_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_SHELLDER_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_CLOYSTER_ANIM_INDEX
                },
              };
            case PMD_CLOYSTER_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_GASTLY_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 25 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_HAUNTER_ANIM_INDEX
                },
              };
            case PMD_HAUNTER_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 28 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_GENGAR_ANIM_INDEX
                },
              };
            case PMD_GENGAR_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_ONIX_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_STEELIX_ANIM_INDEX
                },
              };
            case PMD_DROWZEE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 26 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_HYPNO_ANIM_INDEX
                },
              };
            case PMD_HYPNO_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_KRABBY_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 28 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_KINGLER_ANIM_INDEX
                },
              };
            case PMD_KINGLER_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_VOLTORB_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 30 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_ELECTRODE_ANIM_INDEX
                },
              };
            case PMD_ELECTRODE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_EXEGGCUTE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_EXEGGUTOR_ANIM_INDEX
                },
              };
            case PMD_EXEGGUTOR_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_CUBONE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 28 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_MAROWAK_ANIM_INDEX
                },
              };
            case PMD_MAROWAK_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_HITMONLEE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_HITMONCHAN_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_LICKITUNG_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 24 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_LICKILICKY_ANIM_INDEX
                },
              };
            case PMD_KOFFING_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 35 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_WEEZING_ANIM_INDEX
                },
              };
            case PMD_WEEZING_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_RHYHORN_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 42 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_RHYDON_ANIM_INDEX
                },
              };
            case PMD_RHYDON_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_RHYPERIOR_ANIM_INDEX
                },
              };
            case PMD_CHANSEY_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 24 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_BLISSEY_ANIM_INDEX
                },
              };
            case PMD_TANGELA_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 24 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_TANGROWTH_ANIM_INDEX
                },
              };
            case PMD_KANGASKHAN_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_HORSEA_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_SEADRA_ANIM_INDEX
                },
              };
            case PMD_SEADRA_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_KINGDRA_ANIM_INDEX
                },
              };
            case PMD_GOLDEEN_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 33 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_SEAKING_ANIM_INDEX
                },
              };
            case PMD_SEAKING_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_STARYU_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_STARMIE_ANIM_INDEX
                },
              };
            case PMD_STARMIE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_MR_MIME_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 42 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_SCYTHER_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
                
                .num_animation_indices = 2,
                .animation_indices = {
                  PMD_SCIZOR_ANIM_INDEX ,PMD_KLEAVOR_ANIM_INDEX
                },
              };
            case PMD_JYNX_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_ELECTABUZZ_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_ELECTIVIRE_ANIM_INDEX
                },
              };
            case PMD_MAGMAR_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_MAGMORTAR_ANIM_INDEX
                },
              };
            case PMD_PINSIR_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_TAUROS_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_MAGIKARP_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 20 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_GYARADOS_ANIM_INDEX
                },
              };
            case PMD_GYARADOS_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_LAPRAS_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_DITTO_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_EEVEE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 24 },
                
                .num_animation_indices = 8,
                .animation_indices = {
                  PMD_VAPOREON_ANIM_INDEX ,PMD_JOLTEON_ANIM_INDEX ,PMD_FLAREON_ANIM_INDEX ,PMD_ESPEON_ANIM_INDEX ,PMD_UMBREON_ANIM_INDEX ,PMD_LEAFEON_ANIM_INDEX ,PMD_GLACEON_ANIM_INDEX ,PMD_SYLVEON_ANIM_INDEX
                },
              };
            case PMD_VAPOREON_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_JOLTEON_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_FLAREON_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_PORYGON_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_PORYGON2_ANIM_INDEX
                },
              };
            case PMD_OMANYTE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 40 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_OMASTAR_ANIM_INDEX
                },
              };
            case PMD_OMASTAR_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_KABUTO_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 40 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_KABUTOPS_ANIM_INDEX
                },
              };
            case PMD_KABUTOPS_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_AERODACTYL_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_SNORLAX_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_ARTICUNO_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_ZAPDOS_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_MOLTRES_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_DRATINI_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 30 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_DRAGONAIR_ANIM_INDEX
                },
              };
            case PMD_DRAGONAIR_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 55 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_DRAGONITE_ANIM_INDEX
                },
              };
            case PMD_DRAGONITE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_MEWTWO_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_MEW_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_CHIKORITA_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 16 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_BAYLEEF_ANIM_INDEX
                },
              };
            case PMD_BAYLEEF_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_MEGANIUM_ANIM_INDEX
                },
              };
            case PMD_MEGANIUM_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_CYNDAQUIL_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 14 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_QUILAVA_ANIM_INDEX
                },
              };
            case PMD_QUILAVA_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 36 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_TYPHLOSION_ANIM_INDEX
                },
              };
            case PMD_TYPHLOSION_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_TOTODILE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 18 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_CROCONAW_ANIM_INDEX
                },
              };
            case PMD_CROCONAW_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 30 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_FERALIGATR_ANIM_INDEX
                },
              };
            case PMD_FERALIGATR_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_SENTRET_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 15 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_FURRET_ANIM_INDEX
                },
              };
            case PMD_FURRET_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_HOOTHOOT_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 20 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_NOCTOWL_ANIM_INDEX
                },
              };
            case PMD_NOCTOWL_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_LEDYBA_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 18 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_LEDIAN_ANIM_INDEX
                },
              };
            case PMD_LEDIAN_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_SPINARAK_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 22 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_ARIADOS_ANIM_INDEX
                },
              };
            case PMD_ARIADOS_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_CROBAT_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_CHINCHOU_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 27 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_LANTURN_ANIM_INDEX
                },
              };
            case PMD_LANTURN_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_PICHU_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 24 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_PIKACHU_ANIM_INDEX
                },
              };
            case PMD_CLEFFA_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 24 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_CLEFAIRY_ANIM_INDEX
                },
              };
            case PMD_IGGLYBUFF_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 24 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_JIGGLYPUFF_ANIM_INDEX
                },
              };
            case PMD_TOGEPI_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 24 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_TOGETIC_ANIM_INDEX
                },
              };
            case PMD_TOGETIC_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_TOGEKISS_ANIM_INDEX
                },
              };
            case PMD_NATU_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 25 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_XATU_ANIM_INDEX
                },
              };
            case PMD_XATU_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_MAREEP_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 15 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_FLAAFFY_ANIM_INDEX
                },
              };
            case PMD_FLAAFFY_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 30 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_AMPHAROS_ANIM_INDEX
                },
              };
            case PMD_AMPHAROS_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_BELLOSSOM_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_MARILL_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 18 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_AZUMARILL_ANIM_INDEX
                },
              };
            case PMD_AZUMARILL_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_SUDOWOODO_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_POLITOED_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_HOPPIP_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 18 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_SKIPLOOM_ANIM_INDEX
                },
              };
            case PMD_SKIPLOOM_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 27 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_JUMPLUFF_ANIM_INDEX
                },
              };
            case PMD_JUMPLUFF_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_AIPOM_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 24 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_AMBIPOM_ANIM_INDEX
                },
              };
            case PMD_SUNKERN_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_SUNFLORA_ANIM_INDEX
                },
              };
            case PMD_SUNFLORA_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_YANMA_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 24 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_YANMEGA_ANIM_INDEX
                },
              };
            case PMD_WOOPER_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 20 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_QUAGSIRE_ANIM_INDEX
                },
              };
            case PMD_QUAGSIRE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_ESPEON_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_UMBREON_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_MURKROW_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_HONCHKROW_ANIM_INDEX
                },
              };
            case PMD_SLOWKING_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_MISDREAVUS_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_MISMAGIUS_ANIM_INDEX
                },
              };
            case PMD_UNOWN_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_WOBBUFFET_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_GIRAFARIG_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 24 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_PINECO_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 31 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_FORRETRESS_ANIM_INDEX
                },
              };
            case PMD_FORRETRESS_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_DUNSPARCE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 24 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_GLIGAR_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_GLISCOR_ANIM_INDEX
                },
              };
            case PMD_STEELIX_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_SNUBBULL_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 23 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_GRANBULL_ANIM_INDEX
                },
              };
            case PMD_GRANBULL_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_QWILFISH_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 24 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_OVERQWIL_ANIM_INDEX
                },
              };
            case PMD_SCIZOR_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_SHUCKLE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_HERACROSS_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_SNEASEL_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
                
                .num_animation_indices = 2,
                .animation_indices = {
                  PMD_WEAVILE_ANIM_INDEX ,PMD_SNEASLER_ANIM_INDEX
                },
              };
            case PMD_TEDDIURSA_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 30 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_URSARING_ANIM_INDEX
                },
              };
            case PMD_URSARING_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_URSALUNA_ANIM_INDEX
                },
              };
            case PMD_SLUGMA_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 38 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_MAGCARGO_ANIM_INDEX
                },
              };
            case PMD_MAGCARGO_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_SWINUB_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 33 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_PILOSWINE_ANIM_INDEX
                },
              };
            case PMD_PILOSWINE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 24 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_MAMOSWINE_ANIM_INDEX
                },
              };
            case PMD_CORSOLA_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 38 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_CURSOLA_ANIM_INDEX
                },
              };
            case PMD_REMORAID_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 25 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_OCTILLERY_ANIM_INDEX
                },
              };
            case PMD_OCTILLERY_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_DELIBIRD_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_MANTINE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_SKARMORY_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_HOUNDOUR_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 24 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_HOUNDOOM_ANIM_INDEX
                },
              };
            case PMD_HOUNDOOM_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_KINGDRA_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_PHANPY_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 25 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_DONPHAN_ANIM_INDEX
                },
              };
            case PMD_DONPHAN_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_PORYGON2_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_PORYGON_Z_ANIM_INDEX
                },
              };
            case PMD_STANTLER_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 24 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_WYRDEER_ANIM_INDEX
                },
              };
            case PMD_SMEARGLE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_TYROGUE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 20 },
                
                .num_animation_indices = 3,
                .animation_indices = {
                  PMD_HITMONLEE_ANIM_INDEX ,PMD_HITMONCHAN_ANIM_INDEX ,PMD_HITMONTOP_ANIM_INDEX
                },
              };
            case PMD_HITMONTOP_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_SMOOCHUM_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 30 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_JYNX_ANIM_INDEX
                },
              };
            case PMD_ELEKID_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 30 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_ELECTABUZZ_ANIM_INDEX
                },
              };
            case PMD_MAGBY_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 30 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_MAGMAR_ANIM_INDEX
                },
              };
            case PMD_MILTANK_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_BLISSEY_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_RAIKOU_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_ENTEI_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_SUICUNE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_LARVITAR_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 30 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_PUPITAR_ANIM_INDEX
                },
              };
            case PMD_PUPITAR_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 55 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_TYRANITAR_ANIM_INDEX
                },
              };
            case PMD_TYRANITAR_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_LUGIA_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_HO_OH_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_CELEBI_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_TREECKO_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 16 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_GROVYLE_ANIM_INDEX
                },
              };
            case PMD_GROVYLE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 36 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_SCEPTILE_ANIM_INDEX
                },
              };
            case PMD_SCEPTILE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_TORCHIC_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 16 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_COMBUSKEN_ANIM_INDEX
                },
              };
            case PMD_COMBUSKEN_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 36 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_BLAZIKEN_ANIM_INDEX
                },
              };
            case PMD_BLAZIKEN_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_MUDKIP_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 16 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_MARSHTOMP_ANIM_INDEX
                },
              };
            case PMD_MARSHTOMP_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 36 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_SWAMPERT_ANIM_INDEX
                },
              };
            case PMD_SWAMPERT_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_POOCHYENA_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 18 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_MIGHTYENA_ANIM_INDEX
                },
              };
            case PMD_MIGHTYENA_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_ZIGZAGOON_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 20 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_LINOONE_ANIM_INDEX
                },
              };
            case PMD_LINOONE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 35 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_OBSTAGOON_ANIM_INDEX
                },
              };
            case PMD_WURMPLE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 7 },
                
                .num_animation_indices = 2,
                .animation_indices = {
                  PMD_SILCOON_ANIM_INDEX ,PMD_CASCOON_ANIM_INDEX
                },
              };
            case PMD_SILCOON_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 10 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_BEAUTIFLY_ANIM_INDEX
                },
              };
            case PMD_BEAUTIFLY_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_CASCOON_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 10 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_DUSTOX_ANIM_INDEX
                },
              };
            case PMD_DUSTOX_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_LOTAD_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 14 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_LOMBRE_ANIM_INDEX
                },
              };
            case PMD_LOMBRE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_LUDICOLO_ANIM_INDEX
                },
              };
            case PMD_LUDICOLO_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_SEEDOT_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 14 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_NUZLEAF_ANIM_INDEX
                },
              };
            case PMD_NUZLEAF_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_SHIFTRY_ANIM_INDEX
                },
              };
            case PMD_SHIFTRY_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_TAILLOW_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 22 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_SWELLOW_ANIM_INDEX
                },
              };
            case PMD_SWELLOW_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_WINGULL_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 25 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_PELIPPER_ANIM_INDEX
                },
              };
            case PMD_PELIPPER_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_RALTS_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 20 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_KIRLIA_ANIM_INDEX
                },
              };
            case PMD_KIRLIA_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 30 },
                
                .num_animation_indices = 2,
                .animation_indices = {
                  PMD_GARDEVOIR_ANIM_INDEX ,PMD_GALLADE_ANIM_INDEX
                },
              };
            case PMD_GARDEVOIR_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_SURSKIT_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 22 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_MASQUERAIN_ANIM_INDEX
                },
              };
            case PMD_MASQUERAIN_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_SHROOMISH_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 23 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_BRELOOM_ANIM_INDEX
                },
              };
            case PMD_BRELOOM_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_SLAKOTH_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 18 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_VIGOROTH_ANIM_INDEX
                },
              };
            case PMD_VIGOROTH_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 36 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_SLAKING_ANIM_INDEX
                },
              };
            case PMD_SLAKING_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_NINCADA_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 20 },
                
                .num_animation_indices = 2,
                .animation_indices = {
                  PMD_NINJASK_ANIM_INDEX ,PMD_SHEDINJA_ANIM_INDEX
                },
              };
            case PMD_NINJASK_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_SHEDINJA_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_WHISMUR_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 20 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_LOUDRED_ANIM_INDEX
                },
              };
            case PMD_LOUDRED_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 40 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_EXPLOUD_ANIM_INDEX
                },
              };
            case PMD_EXPLOUD_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_MAKUHITA_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 24 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_HARIYAMA_ANIM_INDEX
                },
              };
            case PMD_HARIYAMA_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_AZURILL_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 24 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_MARILL_ANIM_INDEX
                },
              };
            case PMD_NOSEPASS_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 24 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_PROBOPASS_ANIM_INDEX
                },
              };
            case PMD_SKITTY_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_DELCATTY_ANIM_INDEX
                },
              };
            case PMD_DELCATTY_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_SABLEYE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_MAWILE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_ARON_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_LAIRON_ANIM_INDEX
                },
              };
            case PMD_LAIRON_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 42 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_AGGRON_ANIM_INDEX
                },
              };
            case PMD_AGGRON_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_MEDITITE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 37 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_MEDICHAM_ANIM_INDEX
                },
              };
            case PMD_MEDICHAM_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_ELECTRIKE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 26 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_MANECTRIC_ANIM_INDEX
                },
              };
            case PMD_MANECTRIC_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_PLUSLE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_MINUN_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_VOLBEAT_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_ILLUMISE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_ROSELIA_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_ROSERADE_ANIM_INDEX
                },
              };
            case PMD_GULPIN_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 26 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_SWALOT_ANIM_INDEX
                },
              };
            case PMD_SWALOT_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_CARVANHA_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 30 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_SHARPEDO_ANIM_INDEX
                },
              };
            case PMD_SHARPEDO_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_WAILMER_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 40 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_WAILORD_ANIM_INDEX
                },
              };
            case PMD_WAILORD_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_NUMEL_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 33 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_CAMERUPT_ANIM_INDEX
                },
              };
            case PMD_CAMERUPT_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_TORKOAL_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_SPOINK_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_GRUMPIG_ANIM_INDEX
                },
              };
            case PMD_GRUMPIG_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_SPINDA_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_TRAPINCH_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 35 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_VIBRAVA_ANIM_INDEX
                },
              };
            case PMD_VIBRAVA_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 45 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_FLYGON_ANIM_INDEX
                },
              };
            case PMD_FLYGON_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_CACNEA_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_CACTURNE_ANIM_INDEX
                },
              };
            case PMD_CACTURNE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_SWABLU_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 35 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_ALTARIA_ANIM_INDEX
                },
              };
            case PMD_ALTARIA_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_ZANGOOSE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_SEVIPER_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_LUNATONE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_SOLROCK_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_BARBOACH_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 30 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_WHISCASH_ANIM_INDEX
                },
              };
            case PMD_WHISCASH_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_CORPHISH_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 30 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_CRAWDAUNT_ANIM_INDEX
                },
              };
            case PMD_CRAWDAUNT_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_BALTOY_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 36 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_CLAYDOL_ANIM_INDEX
                },
              };
            case PMD_CLAYDOL_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_LILEEP_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 40 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_CRADILY_ANIM_INDEX
                },
              };
            case PMD_CRADILY_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_ANORITH_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 40 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_ARMALDO_ANIM_INDEX
                },
              };
            case PMD_ARMALDO_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_FEEBAS_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 24 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_MILOTIC_ANIM_INDEX
                },
              };
            case PMD_MILOTIC_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_CASTFORM_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_KECLEON_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_SHUPPET_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 37 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_BANETTE_ANIM_INDEX
                },
              };
            case PMD_BANETTE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_DUSKULL_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 37 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_DUSCLOPS_ANIM_INDEX
                },
              };
            case PMD_DUSCLOPS_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_DUSKNOIR_ANIM_INDEX
                },
              };
            case PMD_TROPIUS_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_CHIMECHO_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_ABSOL_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_WYNAUT_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 15 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_WOBBUFFET_ANIM_INDEX
                },
              };
            case PMD_SNORUNT_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
                
                .num_animation_indices = 2,
                .animation_indices = {
                  PMD_GLALIE_ANIM_INDEX ,PMD_FROSLASS_ANIM_INDEX
                },
              };
            case PMD_GLALIE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_SPHEAL_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_SEALEO_ANIM_INDEX
                },
              };
            case PMD_SEALEO_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 44 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_WALREIN_ANIM_INDEX
                },
              };
            case PMD_WALREIN_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_CLAMPERL_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
                
                .num_animation_indices = 2,
                .animation_indices = {
                  PMD_HUNTAIL_ANIM_INDEX ,PMD_GOREBYSS_ANIM_INDEX
                },
              };
            case PMD_HUNTAIL_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_GOREBYSS_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_RELICANTH_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_LUVDISC_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_BAGON_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 30 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_SHELGON_ANIM_INDEX
                },
              };
            case PMD_SHELGON_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 50 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_SALAMENCE_ANIM_INDEX
                },
              };
            case PMD_SALAMENCE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_BELDUM_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 20 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_METANG_ANIM_INDEX
                },
              };
            case PMD_METANG_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 45 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_METAGROSS_ANIM_INDEX
                },
              };
            case PMD_METAGROSS_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_REGIROCK_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_REGICE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_REGISTEEL_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_LATIAS_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_LATIOS_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_KYOGRE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_GROUDON_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_RAYQUAZA_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_JIRACHI_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_DEOXYS_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_TURTWIG_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 18 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_GROTLE_ANIM_INDEX
                },
              };
            case PMD_GROTLE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_TORTERRA_ANIM_INDEX
                },
              };
            case PMD_TORTERRA_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_CHIMCHAR_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 14 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_MONFERNO_ANIM_INDEX
                },
              };
            case PMD_MONFERNO_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 36 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_INFERNAPE_ANIM_INDEX
                },
              };
            case PMD_INFERNAPE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_PIPLUP_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 16 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_PRINPLUP_ANIM_INDEX
                },
              };
            case PMD_PRINPLUP_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 36 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_EMPOLEON_ANIM_INDEX
                },
              };
            case PMD_EMPOLEON_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_STARLY_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 14 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_STARAVIA_ANIM_INDEX
                },
              };
            case PMD_STARAVIA_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 34 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_STARAPTOR_ANIM_INDEX
                },
              };
            case PMD_STARAPTOR_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_BIDOOF_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 15 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_BIBAREL_ANIM_INDEX
                },
              };
            case PMD_BIBAREL_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_KRICKETOT_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 10 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_KRICKETUNE_ANIM_INDEX
                },
              };
            case PMD_KRICKETUNE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_SHINX_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 15 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_LUXIO_ANIM_INDEX
                },
              };
            case PMD_LUXIO_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 30 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_LUXRAY_ANIM_INDEX
                },
              };
            case PMD_LUXRAY_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_BUDEW_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 24 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_ROSELIA_ANIM_INDEX
                },
              };
            case PMD_ROSERADE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_CRANIDOS_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 30 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_RAMPARDOS_ANIM_INDEX
                },
              };
            case PMD_RAMPARDOS_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_SHIELDON_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 30 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_BASTIODON_ANIM_INDEX
                },
              };
            case PMD_BASTIODON_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_BURMY_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 20 },
                
                .num_animation_indices = 2,
                .animation_indices = {
                  PMD_WORMADAM_ANIM_INDEX ,PMD_MOTHIM_ANIM_INDEX
                },
              };
            case PMD_WORMADAM_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_MOTHIM_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_COMBEE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 21 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_VESPIQUEN_ANIM_INDEX
                },
              };
            case PMD_VESPIQUEN_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_PACHIRISU_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_BUIZEL_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 26 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_FLOATZEL_ANIM_INDEX
                },
              };
            case PMD_FLOATZEL_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_CHERUBI_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 25 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_CHERRIM_ANIM_INDEX
                },
              };
            case PMD_CHERRIM_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_SHELLOS_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 30 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_GASTRODON_ANIM_INDEX
                },
              };
            case PMD_GASTRODON_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_AMBIPOM_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_DRIFLOON_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 28 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_DRIFBLIM_ANIM_INDEX
                },
              };
            case PMD_DRIFBLIM_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_BUNEARY_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 24 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_LOPUNNY_ANIM_INDEX
                },
              };
            case PMD_LOPUNNY_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_MISMAGIUS_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_HONCHKROW_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_GLAMEOW_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 38 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_PURUGLY_ANIM_INDEX
                },
              };
            case PMD_PURUGLY_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_CHINGLING_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 24 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_CHIMECHO_ANIM_INDEX
                },
              };
            case PMD_STUNKY_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 34 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_SKUNTANK_ANIM_INDEX
                },
              };
            case PMD_SKUNTANK_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_BRONZOR_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 33 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_BRONZONG_ANIM_INDEX
                },
              };
            case PMD_BRONZONG_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_BONSLY_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 24 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_SUDOWOODO_ANIM_INDEX
                },
              };
            case PMD_MIME_JR_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 24 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_MR_MIME_ANIM_INDEX
                },
              };
            case PMD_HAPPINY_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_CHANSEY_ANIM_INDEX
                },
              };
            case PMD_CHATOT_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_SPIRITOMB_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_GIBLE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 24 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_GABITE_ANIM_INDEX
                },
              };
            case PMD_GABITE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 48 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_GARCHOMP_ANIM_INDEX
                },
              };
            case PMD_GARCHOMP_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_MUNCHLAX_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 24 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_SNORLAX_ANIM_INDEX
                },
              };
            case PMD_RIOLU_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 24 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_LUCARIO_ANIM_INDEX
                },
              };
            case PMD_LUCARIO_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_HIPPOPOTAS_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 34 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_HIPPOWDON_ANIM_INDEX
                },
              };
            case PMD_HIPPOWDON_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_SKORUPI_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 40 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_DRAPION_ANIM_INDEX
                },
              };
            case PMD_DRAPION_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_CROAGUNK_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 37 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_TOXICROAK_ANIM_INDEX
                },
              };
            case PMD_TOXICROAK_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_CARNIVINE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_FINNEON_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 31 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_LUMINEON_ANIM_INDEX
                },
              };
            case PMD_LUMINEON_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_MANTYKE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 24 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_MANTINE_ANIM_INDEX
                },
              };
            case PMD_SNOVER_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 40 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_ABOMASNOW_ANIM_INDEX
                },
              };
            case PMD_ABOMASNOW_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_WEAVILE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_MAGNEZONE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_LICKILICKY_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_RHYPERIOR_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_TANGROWTH_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_ELECTIVIRE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_MAGMORTAR_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_TOGEKISS_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_YANMEGA_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_LEAFEON_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_GLACEON_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_GLISCOR_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_MAMOSWINE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_PORYGON_Z_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_GALLADE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_PROBOPASS_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_DUSKNOIR_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_FROSLASS_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_ROTOM_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_UXIE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_MESPRIT_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_AZELF_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_DIALGA_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_PALKIA_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_HEATRAN_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_REGIGIGAS_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_GIRATINA_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_CRESSELIA_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_PHIONE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_MANAPHY_ANIM_INDEX
                },
              };
            case PMD_MANAPHY_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_DARKRAI_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_SHAYMIN_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_ARCEUS_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_VICTINI_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_SNIVY_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 17 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_SERVINE_ANIM_INDEX
                },
              };
            case PMD_SERVINE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 36 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_SERPERIOR_ANIM_INDEX
                },
              };
            case PMD_SERPERIOR_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_TEPIG_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 17 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_PIGNITE_ANIM_INDEX
                },
              };
            case PMD_PIGNITE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 36 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_EMBOAR_ANIM_INDEX
                },
              };
            case PMD_EMBOAR_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_OSHAWOTT_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 17 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_DEWOTT_ANIM_INDEX
                },
              };
            case PMD_DEWOTT_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 36 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_SAMUROTT_ANIM_INDEX
                },
              };
            case PMD_SAMUROTT_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_PATRAT_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 20 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_WATCHOG_ANIM_INDEX
                },
              };
            case PMD_WATCHOG_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_LILLIPUP_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 16 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_HERDIER_ANIM_INDEX
                },
              };
            case PMD_HERDIER_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_STOUTLAND_ANIM_INDEX
                },
              };
            case PMD_STOUTLAND_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_PURRLOIN_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 20 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_LIEPARD_ANIM_INDEX
                },
              };
            case PMD_LIEPARD_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_PANSAGE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_SIMISAGE_ANIM_INDEX
                },
              };
            case PMD_SIMISAGE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_PANSEAR_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_PANPOUR_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_MUNNA_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_MUSHARNA_ANIM_INDEX
                },
              };
            case PMD_MUSHARNA_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_PIDOVE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 21 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_UNFEZANT_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_ROGGENROLA_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 25 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_BOLDORE_ANIM_INDEX
                },
              };
            case PMD_BOLDORE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 28 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_GIGALITH_ANIM_INDEX
                },
              };
            case PMD_GIGALITH_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_WOOBAT_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 24 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_SWOOBAT_ANIM_INDEX
                },
              };
            case PMD_SWOOBAT_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_DRILBUR_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 31 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_EXCADRILL_ANIM_INDEX
                },
              };
            case PMD_EXCADRILL_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_AUDINO_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_TIMBURR_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 25 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_GURDURR_ANIM_INDEX
                },
              };
            case PMD_GURDURR_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 28 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_CONKELDURR_ANIM_INDEX
                },
              };
            case PMD_CONKELDURR_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_TYMPOLE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 25 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_PALPITOAD_ANIM_INDEX
                },
              };
            case PMD_PALPITOAD_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 36 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_SEISMITOAD_ANIM_INDEX
                },
              };
            case PMD_SEISMITOAD_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_SEWADDLE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 20 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_SWADLOON_ANIM_INDEX
                },
              };
            case PMD_SWADLOON_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 24 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_LEAVANNY_ANIM_INDEX
                },
              };
            case PMD_LEAVANNY_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_VENIPEDE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 22 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_WHIRLIPEDE_ANIM_INDEX
                },
              };
            case PMD_WHIRLIPEDE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 30 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_SCOLIPEDE_ANIM_INDEX
                },
              };
            case PMD_SCOLIPEDE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_COTTONEE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_WHIMSICOTT_ANIM_INDEX
                },
              };
            case PMD_WHIMSICOTT_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_PETILIL_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_LILLIGANT_ANIM_INDEX
                },
              };
            case PMD_LILLIGANT_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_BASCULIN_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 24 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_BASCULEGION_ANIM_INDEX
                },
              };
            case PMD_SANDILE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 29 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_KROKOROK_ANIM_INDEX
                },
              };
            case PMD_KROKOROK_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 40 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_KROOKODILE_ANIM_INDEX
                },
              };
            case PMD_KROOKODILE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_DARUMAKA_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_DARMANITAN_ANIM_INDEX
                },
              };
            case PMD_DARMANITAN_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_MARACTUS_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_DWEBBLE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 34 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_SCRAGGY_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 39 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_SCRAFTY_ANIM_INDEX
                },
              };
            case PMD_SCRAFTY_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_SIGILYPH_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_YAMASK_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 24 },
                
                .num_animation_indices = 2,
                .animation_indices = {
                  PMD_COFAGRIGUS_ANIM_INDEX ,PMD_RUNERIGUS_ANIM_INDEX
                },
              };
            case PMD_COFAGRIGUS_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_ARCHEN_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 37 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_ARCHEOPS_ANIM_INDEX
                },
              };
            case PMD_ARCHEOPS_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_TRUBBISH_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 36 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_GARBODOR_ANIM_INDEX
                },
              };
            case PMD_GARBODOR_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_ZORUA_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 30 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_ZOROARK_ANIM_INDEX
                },
              };
            case PMD_ZOROARK_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_MINCCINO_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_CINCCINO_ANIM_INDEX
                },
              };
            case PMD_CINCCINO_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_GOTHITA_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_GOTHORITA_ANIM_INDEX
                },
              };
            case PMD_GOTHORITA_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 41 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_GOTHITELLE_ANIM_INDEX
                },
              };
            case PMD_GOTHITELLE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_SOLOSIS_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_DUOSION_ANIM_INDEX
                },
              };
            case PMD_DUOSION_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 41 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_REUNICLUS_ANIM_INDEX
                },
              };
            case PMD_REUNICLUS_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_SWANNA_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_VANILLITE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 35 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_VANILLISH_ANIM_INDEX
                },
              };
            case PMD_VANILLISH_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 47 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_VANILLUXE_ANIM_INDEX
                },
              };
            case PMD_VANILLUXE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_DEERLING_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 34 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_SAWSBUCK_ANIM_INDEX
                },
              };
            case PMD_SAWSBUCK_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_EMOLGA_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_KARRABLAST_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 28 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_ESCAVALIER_ANIM_INDEX
                },
              };
            case PMD_ESCAVALIER_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_FOONGUS_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 39 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_JELLICENT_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_ALOMOMOLA_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_JOLTIK_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 36 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_GALVANTULA_ANIM_INDEX
                },
              };
            case PMD_GALVANTULA_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_FERROSEED_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 40 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_FERROTHORN_ANIM_INDEX
                },
              };
            case PMD_FERROTHORN_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_TYNAMO_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 39 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_EELEKTRIK_ANIM_INDEX
                },
              };
            case PMD_EELEKTRIK_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_EELEKTROSS_ANIM_INDEX
                },
              };
            case PMD_EELEKTROSS_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_ELGYEM_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 42 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_BEHEEYEM_ANIM_INDEX
                },
              };
            case PMD_BEHEEYEM_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_LITWICK_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 41 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_LAMPENT_ANIM_INDEX
                },
              };
            case PMD_LAMPENT_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_CHANDELURE_ANIM_INDEX
                },
              };
            case PMD_CHANDELURE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_AXEW_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 38 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_FRAXURE_ANIM_INDEX
                },
              };
            case PMD_FRAXURE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 48 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_HAXORUS_ANIM_INDEX
                },
              };
            case PMD_HAXORUS_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_CUBCHOO_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 37 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_BEARTIC_ANIM_INDEX
                },
              };
            case PMD_BEARTIC_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_CRYOGONAL_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_STUNFISK_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_MIENFOO_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 50 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_MIENSHAO_ANIM_INDEX
                },
              };
            case PMD_MIENSHAO_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_DRUDDIGON_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_GOLETT_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 43 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_GOLURK_ANIM_INDEX
                },
              };
            case PMD_GOLURK_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_PAWNIARD_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 52 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_BISHARP_ANIM_INDEX
                },
              };
            case PMD_BISHARP_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 24 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_RUFFLET_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 54 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_BRAVIARY_ANIM_INDEX
                },
              };
            case PMD_BRAVIARY_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_VULLABY_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 54 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_MANDIBUZZ_ANIM_INDEX
                },
              };
            case PMD_MANDIBUZZ_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_HEATMOR_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_DURANT_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_DEINO_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 50 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_ZWEILOUS_ANIM_INDEX
                },
              };
            case PMD_ZWEILOUS_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 64 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_HYDREIGON_ANIM_INDEX
                },
              };
            case PMD_HYDREIGON_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_LARVESTA_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 59 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_VOLCARONA_ANIM_INDEX
                },
              };
            case PMD_VOLCARONA_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_COBALION_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_TERRAKION_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_VIRIZION_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_TORNADUS_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_THUNDURUS_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_RESHIRAM_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_ZEKROM_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_LANDORUS_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_KYUREM_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_KELDEO_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_MELOETTA_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_GENESECT_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_CHESPIN_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 16 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_QUILLADIN_ANIM_INDEX
                },
              };
            case PMD_QUILLADIN_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 36 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_CHESNAUGHT_ANIM_INDEX
                },
              };
            case PMD_CHESNAUGHT_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_FENNEKIN_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 16 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_BRAIXEN_ANIM_INDEX
                },
              };
            case PMD_BRAIXEN_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 36 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_DELPHOX_ANIM_INDEX
                },
              };
            case PMD_DELPHOX_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_FROAKIE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 16 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_FROGADIER_ANIM_INDEX
                },
              };
            case PMD_FROGADIER_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 36 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_GRENINJA_ANIM_INDEX
                },
              };
            case PMD_GRENINJA_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_BUNNELBY_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 20 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_FLETCHLING_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 17 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_FLETCHINDER_ANIM_INDEX
                },
              };
            case PMD_FLETCHINDER_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 35 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_TALONFLAME_ANIM_INDEX
                },
              };
            case PMD_TALONFLAME_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_SCATTERBUG_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 9 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_SPEWPA_ANIM_INDEX
                },
              };
            case PMD_SPEWPA_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 12 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_VIVILLON_ANIM_INDEX
                },
              };
            case PMD_VIVILLON_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_LITLEO_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 35 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_FLABEBE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 19 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_FLOETTE_ANIM_INDEX
                },
              };
            case PMD_FLOETTE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_FLORGES_ANIM_INDEX
                },
              };
            case PMD_FLORGES_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_SKIDDO_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_GOGOAT_ANIM_INDEX
                },
              };
            case PMD_GOGOAT_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_PANCHAM_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_PANGORO_ANIM_INDEX
                },
              };
            case PMD_PANGORO_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_FURFROU_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_ESPURR_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 25 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_MEOWSTIC_ANIM_INDEX
                },
              };
            case PMD_MEOWSTIC_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_HONEDGE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 35 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_DOUBLADE_ANIM_INDEX
                },
              };
            case PMD_DOUBLADE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_AEGISLASH_ANIM_INDEX
                },
              };
            case PMD_AEGISLASH_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_SPRITZEE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_AROMATISSE_ANIM_INDEX
                },
              };
            case PMD_AROMATISSE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_SWIRLIX_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_SLURPUFF_ANIM_INDEX
                },
              };
            case PMD_SLURPUFF_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_INKAY_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 30 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_MALAMAR_ANIM_INDEX
                },
              };
            case PMD_MALAMAR_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_BINACLE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 39 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_BARBARACLE_ANIM_INDEX
                },
              };
            case PMD_BARBARACLE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_SKRELP_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 48 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_DRAGALGE_ANIM_INDEX
                },
              };
            case PMD_DRAGALGE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_CLAUNCHER_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 37 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_CLAWITZER_ANIM_INDEX
                },
              };
            case PMD_CLAWITZER_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_HELIOPTILE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_HELIOLISK_ANIM_INDEX
                },
              };
            case PMD_HELIOLISK_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_TYRUNT_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 39 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_TYRANTRUM_ANIM_INDEX
                },
              };
            case PMD_TYRANTRUM_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_AMAURA_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 39 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_AURORUS_ANIM_INDEX
                },
              };
            case PMD_AURORUS_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_SYLVEON_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_HAWLUCHA_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_DEDENNE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_CARBINK_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_GOOMY_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 40 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_SLIGGOO_ANIM_INDEX
                },
              };
            case PMD_SLIGGOO_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 50 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_GOODRA_ANIM_INDEX
                },
              };
            case PMD_GOODRA_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_KLEFKI_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_PHANTUMP_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 28 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_TREVENANT_ANIM_INDEX
                },
              };
            case PMD_TREVENANT_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_PUMPKABOO_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 28 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_GOURGEIST_ANIM_INDEX
                },
              };
            case PMD_GOURGEIST_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_BERGMITE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 37 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_NOIBAT_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 48 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_NOIVERN_ANIM_INDEX
                },
              };
            case PMD_NOIVERN_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_XERNEAS_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_YVELTAL_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_ZYGARDE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_DIANCIE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_HOOPA_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_VOLCANION_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_ROWLET_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 17 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_DARTRIX_ANIM_INDEX
                },
              };
            case PMD_DARTRIX_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 34 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_DECIDUEYE_ANIM_INDEX
                },
              };
            case PMD_DECIDUEYE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_LITTEN_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 17 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_TORRACAT_ANIM_INDEX
                },
              };
            case PMD_TORRACAT_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 34 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_INCINEROAR_ANIM_INDEX
                },
              };
            case PMD_INCINEROAR_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_POPPLIO_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 17 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_BRIONNE_ANIM_INDEX
                },
              };
            case PMD_BRIONNE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 34 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_PRIMARINA_ANIM_INDEX
                },
              };
            case PMD_PRIMARINA_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_TOUCANNON_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_GRUBBIN_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 20 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_CHARJABUG_ANIM_INDEX
                },
              };
            case PMD_CHARJABUG_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 24 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_VIKAVOLT_ANIM_INDEX
                },
              };
            case PMD_VIKAVOLT_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_CRABRAWLER_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 24 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_CRABOMINABLE_ANIM_INDEX
                },
              };
            case PMD_CRABOMINABLE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_CUTIEFLY_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 25 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_RIBOMBEE_ANIM_INDEX
                },
              };
            case PMD_RIBOMBEE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_ROCKRUFF_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 25 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_LYCANROC_ANIM_INDEX
                },
              };
            case PMD_LYCANROC_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_WISHIWASHI_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_MAREANIE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 38 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_MUDBRAY_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 30 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_MUDSDALE_ANIM_INDEX
                },
              };
            case PMD_MUDSDALE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_DEWPIDER_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 22 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_ARAQUANID_ANIM_INDEX
                },
              };
            case PMD_ARAQUANID_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_FOMANTIS_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 34 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_LURANTIS_ANIM_INDEX
                },
              };
            case PMD_LURANTIS_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_MORELULL_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 24 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_SALANDIT_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 33 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_SALAZZLE_ANIM_INDEX
                },
              };
            case PMD_SALAZZLE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_STUFFUL_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 27 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_BEWEAR_ANIM_INDEX
                },
              };
            case PMD_BEWEAR_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_BOUNSWEET_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 18 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_STEENEE_ANIM_INDEX
                },
              };
            case PMD_STEENEE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 24 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_TSAREENA_ANIM_INDEX
                },
              };
            case PMD_TSAREENA_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_COMFEY_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_PASSIMIAN_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_WIMPOD_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 30 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_GOLISOPOD_ANIM_INDEX
                },
              };
            case PMD_GOLISOPOD_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_SANDYGAST_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 42 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_PALOSSAND_ANIM_INDEX
                },
              };
            case PMD_PALOSSAND_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_PYUKUMUKU_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_TYPE_NULL_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 24 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_SILVALLY_ANIM_INDEX
                },
              };
            case PMD_SILVALLY_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_MINIOR_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_KOMALA_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_TURTONATOR_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_TOGEDEMARU_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_MIMIKYU_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_BRUXISH_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_DRAMPA_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_DHELMISE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_JANGMO_O_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 35 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_HAKAMO_O_ANIM_INDEX
                },
              };
            case PMD_HAKAMO_O_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 45 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_KOMMO_O_ANIM_INDEX
                },
              };
            case PMD_KOMMO_O_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_TAPU_KOKO_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_TAPU_LELE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_TAPU_BULU_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_TAPU_FINI_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_COSMOG_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 43 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_COSMOEM_ANIM_INDEX
                },
              };
            case PMD_COSMOEM_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 53 },
                
                .num_animation_indices = 2,
                .animation_indices = {
                  PMD_SOLGALEO_ANIM_INDEX ,PMD_LUNALA_ANIM_INDEX
                },
              };
            case PMD_SOLGALEO_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_LUNALA_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_NIHILEGO_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_BUZZWOLE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_PHEROMOSA_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_XURKITREE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_CELESTEELA_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_KARTANA_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_GUZZLORD_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_NECROZMA_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_MAGEARNA_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_MARSHADOW_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_POIPOLE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 24 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_NAGANADEL_ANIM_INDEX
                },
              };
            case PMD_NAGANADEL_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_STAKATAKA_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_BLACEPHALON_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_ZERAORA_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_MELTAN_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_MELMETAL_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_GROOKEY_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 16 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_THWACKEY_ANIM_INDEX
                },
              };
            case PMD_THWACKEY_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 35 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_RILLABOOM_ANIM_INDEX
                },
              };
            case PMD_RILLABOOM_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_SCORBUNNY_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 16 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_RABOOT_ANIM_INDEX
                },
              };
            case PMD_RABOOT_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 35 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_CINDERACE_ANIM_INDEX
                },
              };
            case PMD_CINDERACE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_SOBBLE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 16 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_DRIZZILE_ANIM_INDEX
                },
              };
            case PMD_DRIZZILE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 35 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_INTELEON_ANIM_INDEX
                },
              };
            case PMD_INTELEON_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_SKWOVET_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 24 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_ROOKIDEE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 18 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_CORVISQUIRE_ANIM_INDEX
                },
              };
            case PMD_CORVISQUIRE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 38 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_CORVIKNIGHT_ANIM_INDEX
                },
              };
            case PMD_CORVIKNIGHT_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_BLIPBUG_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 10 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_DOTTLER_ANIM_INDEX
                },
              };
            case PMD_DOTTLER_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 30 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_ORBEETLE_ANIM_INDEX
                },
              };
            case PMD_ORBEETLE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_NICKIT_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 18 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_THIEVUL_ANIM_INDEX
                },
              };
            case PMD_THIEVUL_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_GOSSIFLEUR_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 20 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_ELDEGOSS_ANIM_INDEX
                },
              };
            case PMD_ELDEGOSS_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_WOOLOO_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 24 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_CHEWTLE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 22 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_DREDNAW_ANIM_INDEX
                },
              };
            case PMD_DREDNAW_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_YAMPER_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 25 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_APPLIN_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
                
                .num_animation_indices = 2,
                .animation_indices = {
                  PMD_FLAPPLE_ANIM_INDEX ,PMD_APPLETUN_ANIM_INDEX
                },
              };
            case PMD_FLAPPLE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_APPLETUN_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_SILICOBRA_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 36 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_SANDACONDA_ANIM_INDEX
                },
              };
            case PMD_SANDACONDA_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_CRAMORANT_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_ARROKUDA_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 26 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_TOXEL_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 30 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_TOXTRICITY_ANIM_INDEX
                },
              };
            case PMD_TOXTRICITY_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_SIZZLIPEDE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 28 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_CENTISKORCH_ANIM_INDEX
                },
              };
            case PMD_CENTISKORCH_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_CLOBBOPUS_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 24 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_GRAPPLOCT_ANIM_INDEX
                },
              };
            case PMD_GRAPPLOCT_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_SINISTEA_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_POLTEAGEIST_ANIM_INDEX
                },
              };
            case PMD_POLTEAGEIST_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_HATENNA_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_HATTREM_ANIM_INDEX
                },
              };
            case PMD_HATTREM_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 42 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_HATTERENE_ANIM_INDEX
                },
              };
            case PMD_HATTERENE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_IMPIDIMP_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_MORGREM_ANIM_INDEX
                },
              };
            case PMD_MORGREM_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 42 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_GRIMMSNARL_ANIM_INDEX
                },
              };
            case PMD_GRIMMSNARL_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_OBSTAGOON_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_CURSOLA_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_SIRFETCHD_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_RUNERIGUS_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_MILCERY_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 24 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_ALCREMIE_ANIM_INDEX
                },
              };
            case PMD_ALCREMIE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_PINCURCHIN_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_SNOM_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 24 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_FROSMOTH_ANIM_INDEX
                },
              };
            case PMD_FROSMOTH_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_STONJOURNER_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_EISCUE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_INDEEDEE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_MORPEKO_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_COPPERAJAH_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_DRACOZOLT_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_ARCTOZOLT_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_DRACOVISH_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_ARCTOVISH_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_DURALUDON_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_DREEPY_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 50 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_DRAKLOAK_ANIM_INDEX
                },
              };
            case PMD_DRAKLOAK_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 60 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_DRAGAPULT_ANIM_INDEX
                },
              };
            case PMD_DRAGAPULT_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_ZACIAN_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_ETERNATUS_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_KUBFU_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 24 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PMD_URSHIFU_ANIM_INDEX
                },
              };
            case PMD_URSHIFU_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_REGIELEKI_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_REGIDRAGO_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_SPECTRIER_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_CALYREX_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_WYRDEER_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_KLEAVOR_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_URSALUNA_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_BASCULEGION_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_SNEASLER_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_OVERQWIL_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PMD_ENAMORUS_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            default: return {};
        }
        return {};
    }
}

