#include "embedded_assets/embedded_image.h"
#include "embedded_assets/pkmn/pkmn.hpp"
#include "embedded_assets/pkmn/pkmn_evol.h"
#include "graphics/animation_shared_memory.h"

namespace bongocat::assets {
    animation::animation_evolution_data_t get_pkmn_evolution_data(size_t index) {
        switch (index) {
            case PKMN_BULBASAUR_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 16 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_IVYSAUR_ANIM_INDEX
                },
              };
            case PKMN_IVYSAUR_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_VENUSAUR_ANIM_INDEX
                },
              };
            case PKMN_VENUSAUR_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_CHARMANDER_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 16 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_CHARMELEON_ANIM_INDEX
                },
              };
            case PKMN_CHARMELEON_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 36 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_CHARIZARD_ANIM_INDEX
                },
              };
            case PKMN_CHARIZARD_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_SQUIRTLE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 16 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_WARTORTLE_ANIM_INDEX
                },
              };
            case PKMN_WARTORTLE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 36 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_BLASTOISE_ANIM_INDEX
                },
              };
            case PKMN_BLASTOISE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_CATERPIE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 7 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_METAPOD_ANIM_INDEX
                },
              };
            case PKMN_METAPOD_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 10 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_BUTTERFREE_ANIM_INDEX
                },
              };
            case PKMN_BUTTERFREE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_WEEDLE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 7 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_KAKUNA_ANIM_INDEX
                },
              };
            case PKMN_KAKUNA_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 10 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_BEEDRILL_ANIM_INDEX
                },
              };
            case PKMN_BEEDRILL_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_PIDGEY_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 18 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_PIDGEOTTO_ANIM_INDEX
                },
              };
            case PKMN_PIDGEOTTO_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 36 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_PIDGEOT_ANIM_INDEX
                },
              };
            case PKMN_PIDGEOT_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_RATTATA_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 20 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_RATICATE_ANIM_INDEX
                },
              };
            case PKMN_RATICATE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_SPEAROW_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 20 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_FEAROW_ANIM_INDEX
                },
              };
            case PKMN_FEAROW_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_EKANS_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 22 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_ARBOK_ANIM_INDEX
                },
              };
            case PKMN_ARBOK_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_PIKACHU_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_RAICHU_ANIM_INDEX
                },
              };
            case PKMN_RAICHU_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_SANDSHREW_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 22 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_SANDSLASH_ANIM_INDEX
                },
              };
            case PKMN_SANDSLASH_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_NIDORAN_F_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 16 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_NIDORINA_ANIM_INDEX
                },
              };
            case PKMN_NIDORINA_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_NIDOQUEEN_ANIM_INDEX
                },
              };
            case PKMN_NIDOQUEEN_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_NIDORAN_M_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 16 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_NIDORINO_ANIM_INDEX
                },
              };
            case PKMN_NIDORINO_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_NIDOKING_ANIM_INDEX
                },
              };
            case PKMN_NIDOKING_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_CLEFAIRY_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_CLEFABLE_ANIM_INDEX
                },
              };
            case PKMN_CLEFABLE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_VULPIX_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_NINETALES_ANIM_INDEX
                },
              };
            case PKMN_NINETALES_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_JIGGLYPUFF_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_WIGGLYTUFF_ANIM_INDEX
                },
              };
            case PKMN_WIGGLYTUFF_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_ZUBAT_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 22 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_GOLBAT_ANIM_INDEX
                },
              };
            case PKMN_GOLBAT_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 24 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_CROBAT_ANIM_INDEX
                },
              };
            case PKMN_ODDISH_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 21 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_GLOOM_ANIM_INDEX
                },
              };
            case PKMN_GLOOM_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
                
                .num_animation_indices = 2,
                .animation_indices = {
                  PKMN_VILEPLUME_ANIM_INDEX ,PKMN_BELLOSSOM_ANIM_INDEX
                },
              };
            case PKMN_VILEPLUME_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_PARAS_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 24 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_PARASECT_ANIM_INDEX
                },
              };
            case PKMN_PARASECT_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_VENONAT_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 31 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_VENOMOTH_ANIM_INDEX
                },
              };
            case PKMN_VENOMOTH_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_DIGLETT_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 26 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_DUGTRIO_ANIM_INDEX
                },
              };
            case PKMN_DUGTRIO_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_MEOWTH_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 24 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_PERSIAN_ANIM_INDEX
                },
              };
            case PKMN_PERSIAN_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_PSYDUCK_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 33 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_GOLDUCK_ANIM_INDEX
                },
              };
            case PKMN_GOLDUCK_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_MANKEY_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 28 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_PRIMEAPE_ANIM_INDEX
                },
              };
            case PKMN_PRIMEAPE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 24 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_GROWLITHE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_ARCANINE_ANIM_INDEX
                },
              };
            case PKMN_ARCANINE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_POLIWAG_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 25 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_POLIWHIRL_ANIM_INDEX
                },
              };
            case PKMN_POLIWHIRL_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
                
                .num_animation_indices = 2,
                .animation_indices = {
                  PKMN_POLIWRATH_ANIM_INDEX ,PKMN_POLITOED_ANIM_INDEX
                },
              };
            case PKMN_POLIWRATH_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_ABRA_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 16 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_KADABRA_ANIM_INDEX
                },
              };
            case PKMN_KADABRA_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 28 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_ALAKAZAM_ANIM_INDEX
                },
              };
            case PKMN_ALAKAZAM_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_MACHOP_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 28 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_MACHOKE_ANIM_INDEX
                },
              };
            case PKMN_MACHOKE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 28 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_MACHAMP_ANIM_INDEX
                },
              };
            case PKMN_MACHAMP_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_BELLSPROUT_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 21 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_WEEPINBELL_ANIM_INDEX
                },
              };
            case PKMN_WEEPINBELL_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_VICTREEBEL_ANIM_INDEX
                },
              };
            case PKMN_VICTREEBEL_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_TENTACOOL_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 30 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_TENTACRUEL_ANIM_INDEX
                },
              };
            case PKMN_TENTACRUEL_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_GEODUDE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 25 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_GRAVELER_ANIM_INDEX
                },
              };
            case PKMN_GRAVELER_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 28 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_GOLEM_ANIM_INDEX
                },
              };
            case PKMN_GOLEM_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_PONYTA_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 40 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_RAPIDASH_ANIM_INDEX
                },
              };
            case PKMN_RAPIDASH_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_SLOWPOKE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
                
                .num_animation_indices = 2,
                .animation_indices = {
                  PKMN_SLOWBRO_ANIM_INDEX ,PKMN_SLOWKING_ANIM_INDEX
                },
              };
            case PKMN_SLOWBRO_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_MAGNEMITE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 30 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_MAGNETON_ANIM_INDEX
                },
              };
            case PKMN_MAGNETON_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 24 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_MAGNEZONE_ANIM_INDEX
                },
              };
            case PKMN_FARFETCHD_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 24 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_DODUO_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 31 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_DODRIO_ANIM_INDEX
                },
              };
            case PKMN_DODRIO_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_SEEL_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 34 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_DEWGONG_ANIM_INDEX
                },
              };
            case PKMN_DEWGONG_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_GRIMER_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 38 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_MUK_ANIM_INDEX
                },
              };
            case PKMN_MUK_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_SHELLDER_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_CLOYSTER_ANIM_INDEX
                },
              };
            case PKMN_CLOYSTER_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_GASTLY_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 25 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_HAUNTER_ANIM_INDEX
                },
              };
            case PKMN_HAUNTER_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 28 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_GENGAR_ANIM_INDEX
                },
              };
            case PKMN_GENGAR_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_ONIX_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_STEELIX_ANIM_INDEX
                },
              };
            case PKMN_DROWZEE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 26 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_HYPNO_ANIM_INDEX
                },
              };
            case PKMN_HYPNO_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_KRABBY_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 28 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_KINGLER_ANIM_INDEX
                },
              };
            case PKMN_KINGLER_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_VOLTORB_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 30 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_ELECTRODE_ANIM_INDEX
                },
              };
            case PKMN_ELECTRODE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_EXEGGCUTE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_EXEGGUTOR_ANIM_INDEX
                },
              };
            case PKMN_EXEGGUTOR_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_CUBONE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 28 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_MAROWAK_ANIM_INDEX
                },
              };
            case PKMN_MAROWAK_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_HITMONLEE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_HITMONCHAN_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_LICKITUNG_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 24 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_LICKILICKY_ANIM_INDEX
                },
              };
            case PKMN_KOFFING_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 35 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_WEEZING_ANIM_INDEX
                },
              };
            case PKMN_WEEZING_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_RHYHORN_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 42 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_RHYDON_ANIM_INDEX
                },
              };
            case PKMN_RHYDON_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_RHYPERIOR_ANIM_INDEX
                },
              };
            case PKMN_CHANSEY_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 24 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_BLISSEY_ANIM_INDEX
                },
              };
            case PKMN_TANGELA_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 24 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_TANGROWTH_ANIM_INDEX
                },
              };
            case PKMN_KANGASKHAN_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_HORSEA_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_SEADRA_ANIM_INDEX
                },
              };
            case PKMN_SEADRA_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_KINGDRA_ANIM_INDEX
                },
              };
            case PKMN_GOLDEEN_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 33 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_SEAKING_ANIM_INDEX
                },
              };
            case PKMN_SEAKING_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_STARYU_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_STARMIE_ANIM_INDEX
                },
              };
            case PKMN_STARMIE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_MR_MIME_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 42 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_SCYTHER_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_SCIZOR_ANIM_INDEX
                },
              };
            case PKMN_JYNX_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_ELECTABUZZ_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_ELECTIVIRE_ANIM_INDEX
                },
              };
            case PKMN_MAGMAR_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_MAGMORTAR_ANIM_INDEX
                },
              };
            case PKMN_PINSIR_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_TAUROS_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_MAGIKARP_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 20 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_GYARADOS_ANIM_INDEX
                },
              };
            case PKMN_GYARADOS_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_LAPRAS_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_DITTO_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_EEVEE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 24 },
                
                .num_animation_indices = 7,
                .animation_indices = {
                  PKMN_VAPOREON_ANIM_INDEX ,PKMN_JOLTEON_ANIM_INDEX ,PKMN_FLAREON_ANIM_INDEX ,PKMN_ESPEON_ANIM_INDEX ,PKMN_UMBREON_ANIM_INDEX ,PKMN_LEAFEON_ANIM_INDEX ,PKMN_GLACEON_ANIM_INDEX
                },
              };
            case PKMN_VAPOREON_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_JOLTEON_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_FLAREON_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_PORYGON_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_PORYGON2_ANIM_INDEX
                },
              };
            case PKMN_OMANYTE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 40 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_OMASTAR_ANIM_INDEX
                },
              };
            case PKMN_OMASTAR_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_KABUTO_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 40 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_KABUTOPS_ANIM_INDEX
                },
              };
            case PKMN_KABUTOPS_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_AERODACTYL_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_SNORLAX_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_ARTICUNO_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_ZAPDOS_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_MOLTRES_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_DRATINI_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 30 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_DRAGONAIR_ANIM_INDEX
                },
              };
            case PKMN_DRAGONAIR_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 55 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_DRAGONITE_ANIM_INDEX
                },
              };
            case PKMN_DRAGONITE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_MEWTWO_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_MEW_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_CHIKORITA_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 16 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_BAYLEEF_ANIM_INDEX
                },
              };
            case PKMN_BAYLEEF_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_MEGANIUM_ANIM_INDEX
                },
              };
            case PKMN_MEGANIUM_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_CYNDAQUIL_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 14 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_QUILAVA_ANIM_INDEX
                },
              };
            case PKMN_QUILAVA_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 36 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_TYPHLOSION_ANIM_INDEX
                },
              };
            case PKMN_TYPHLOSION_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_TOTODILE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 18 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_CROCONAW_ANIM_INDEX
                },
              };
            case PKMN_CROCONAW_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 30 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_FERALIGATR_ANIM_INDEX
                },
              };
            case PKMN_FERALIGATR_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_SENTRET_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 15 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_FURRET_ANIM_INDEX
                },
              };
            case PKMN_FURRET_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_HOOTHOOT_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 20 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_NOCTOWL_ANIM_INDEX
                },
              };
            case PKMN_NOCTOWL_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_LEDYBA_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 18 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_LEDIAN_ANIM_INDEX
                },
              };
            case PKMN_LEDIAN_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_SPINARAK_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 22 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_ARIADOS_ANIM_INDEX
                },
              };
            case PKMN_ARIADOS_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_CROBAT_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_CHINCHOU_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 27 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_LANTURN_ANIM_INDEX
                },
              };
            case PKMN_LANTURN_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_PICHU_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 24 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_PIKACHU_ANIM_INDEX
                },
              };
            case PKMN_CLEFFA_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 24 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_CLEFAIRY_ANIM_INDEX
                },
              };
            case PKMN_IGGLYBUFF_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 24 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_JIGGLYPUFF_ANIM_INDEX
                },
              };
            case PKMN_TOGEPI_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 24 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_TOGETIC_ANIM_INDEX
                },
              };
            case PKMN_TOGETIC_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_TOGEKISS_ANIM_INDEX
                },
              };
            case PKMN_NATU_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 25 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_XATU_ANIM_INDEX
                },
              };
            case PKMN_XATU_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_MAREEP_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 15 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_FLAAFFY_ANIM_INDEX
                },
              };
            case PKMN_FLAAFFY_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 30 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_AMPHAROS_ANIM_INDEX
                },
              };
            case PKMN_AMPHAROS_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_BELLOSSOM_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_MARILL_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 18 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_AZUMARILL_ANIM_INDEX
                },
              };
            case PKMN_AZUMARILL_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_SUDOWOODO_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_POLITOED_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_HOPPIP_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 18 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_SKIPLOOM_ANIM_INDEX
                },
              };
            case PKMN_SKIPLOOM_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 27 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_JUMPLUFF_ANIM_INDEX
                },
              };
            case PKMN_JUMPLUFF_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_AIPOM_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 24 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_AMBIPOM_ANIM_INDEX
                },
              };
            case PKMN_SUNKERN_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_SUNFLORA_ANIM_INDEX
                },
              };
            case PKMN_SUNFLORA_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_YANMA_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 24 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_YANMEGA_ANIM_INDEX
                },
              };
            case PKMN_WOOPER_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 20 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_QUAGSIRE_ANIM_INDEX
                },
              };
            case PKMN_QUAGSIRE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_ESPEON_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_UMBREON_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_MURKROW_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_HONCHKROW_ANIM_INDEX
                },
              };
            case PKMN_SLOWKING_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_MISDREAVUS_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_MISMAGIUS_ANIM_INDEX
                },
              };
            case PKMN_UNOWN_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_WOBBUFFET_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_GIRAFARIG_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 24 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_PINECO_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 31 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_FORRETRESS_ANIM_INDEX
                },
              };
            case PKMN_FORRETRESS_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_DUNSPARCE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 24 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_GLIGAR_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_GLISCOR_ANIM_INDEX
                },
              };
            case PKMN_STEELIX_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_SNUBBULL_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 23 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_GRANBULL_ANIM_INDEX
                },
              };
            case PKMN_GRANBULL_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_QWILFISH_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 24 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_SCIZOR_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_SHUCKLE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_HERACROSS_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_SNEASEL_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_WEAVILE_ANIM_INDEX
                },
              };
            case PKMN_TEDDIURSA_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 30 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_URSARING_ANIM_INDEX
                },
              };
            case PKMN_URSARING_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_SLUGMA_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 38 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_MAGCARGO_ANIM_INDEX
                },
              };
            case PKMN_MAGCARGO_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_SWINUB_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 33 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_PILOSWINE_ANIM_INDEX
                },
              };
            case PKMN_PILOSWINE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 24 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_MAMOSWINE_ANIM_INDEX
                },
              };
            case PKMN_CORSOLA_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 38 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_REMORAID_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 25 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_OCTILLERY_ANIM_INDEX
                },
              };
            case PKMN_OCTILLERY_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_DELIBIRD_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_MANTINE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_SKARMORY_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_HOUNDOUR_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 24 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_HOUNDOOM_ANIM_INDEX
                },
              };
            case PKMN_HOUNDOOM_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_KINGDRA_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_PHANPY_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 25 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_DONPHAN_ANIM_INDEX
                },
              };
            case PKMN_DONPHAN_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_PORYGON2_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_PORYGON_Z_ANIM_INDEX
                },
              };
            case PKMN_STANTLER_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 24 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_SMEARGLE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_TYROGUE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 20 },
                
                .num_animation_indices = 3,
                .animation_indices = {
                  PKMN_HITMONLEE_ANIM_INDEX ,PKMN_HITMONCHAN_ANIM_INDEX ,PKMN_HITMONTOP_ANIM_INDEX
                },
              };
            case PKMN_HITMONTOP_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_SMOOCHUM_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 30 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_JYNX_ANIM_INDEX
                },
              };
            case PKMN_ELEKID_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 30 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_ELECTABUZZ_ANIM_INDEX
                },
              };
            case PKMN_MAGBY_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 30 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_MAGMAR_ANIM_INDEX
                },
              };
            case PKMN_MILTANK_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_BLISSEY_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_RAIKOU_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_ENTEI_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_SUICUNE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_LARVITAR_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 30 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_PUPITAR_ANIM_INDEX
                },
              };
            case PKMN_PUPITAR_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 55 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_TYRANITAR_ANIM_INDEX
                },
              };
            case PKMN_TYRANITAR_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_LUGIA_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_HO_OH_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_CELEBI_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_TREECKO_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 16 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_GROVYLE_ANIM_INDEX
                },
              };
            case PKMN_GROVYLE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 36 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_SCEPTILE_ANIM_INDEX
                },
              };
            case PKMN_SCEPTILE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_TORCHIC_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 16 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_COMBUSKEN_ANIM_INDEX
                },
              };
            case PKMN_COMBUSKEN_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 36 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_BLAZIKEN_ANIM_INDEX
                },
              };
            case PKMN_BLAZIKEN_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_MUDKIP_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 16 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_MARSHTOMP_ANIM_INDEX
                },
              };
            case PKMN_MARSHTOMP_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 36 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_SWAMPERT_ANIM_INDEX
                },
              };
            case PKMN_SWAMPERT_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_POOCHYENA_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 18 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_MIGHTYENA_ANIM_INDEX
                },
              };
            case PKMN_MIGHTYENA_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_ZIGZAGOON_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 20 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_LINOONE_ANIM_INDEX
                },
              };
            case PKMN_LINOONE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 35 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_WURMPLE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 7 },
                
                .num_animation_indices = 2,
                .animation_indices = {
                  PKMN_SILCOON_ANIM_INDEX ,PKMN_CASCOON_ANIM_INDEX
                },
              };
            case PKMN_SILCOON_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 10 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_BEAUTIFLY_ANIM_INDEX
                },
              };
            case PKMN_BEAUTIFLY_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_CASCOON_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 10 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_DUSTOX_ANIM_INDEX
                },
              };
            case PKMN_DUSTOX_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_LOTAD_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 14 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_LOMBRE_ANIM_INDEX
                },
              };
            case PKMN_LOMBRE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_LUDICOLO_ANIM_INDEX
                },
              };
            case PKMN_LUDICOLO_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_SEEDOT_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 14 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_NUZLEAF_ANIM_INDEX
                },
              };
            case PKMN_NUZLEAF_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_SHIFTRY_ANIM_INDEX
                },
              };
            case PKMN_SHIFTRY_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_TAILLOW_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 22 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_SWELLOW_ANIM_INDEX
                },
              };
            case PKMN_SWELLOW_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_WINGULL_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 25 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_PELIPPER_ANIM_INDEX
                },
              };
            case PKMN_PELIPPER_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_RALTS_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 20 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_KIRLIA_ANIM_INDEX
                },
              };
            case PKMN_KIRLIA_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 30 },
                
                .num_animation_indices = 2,
                .animation_indices = {
                  PKMN_GARDEVOIR_ANIM_INDEX ,PKMN_GALLADE_ANIM_INDEX
                },
              };
            case PKMN_GARDEVOIR_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_SURSKIT_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 22 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_MASQUERAIN_ANIM_INDEX
                },
              };
            case PKMN_MASQUERAIN_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_SHROOMISH_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 23 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_BRELOOM_ANIM_INDEX
                },
              };
            case PKMN_BRELOOM_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_SLAKOTH_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 18 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_VIGOROTH_ANIM_INDEX
                },
              };
            case PKMN_VIGOROTH_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 36 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_SLAKING_ANIM_INDEX
                },
              };
            case PKMN_SLAKING_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_NINCADA_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 20 },
                
                .num_animation_indices = 2,
                .animation_indices = {
                  PKMN_NINJASK_ANIM_INDEX ,PKMN_SHEDINJA_ANIM_INDEX
                },
              };
            case PKMN_NINJASK_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_SHEDINJA_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_WHISMUR_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 20 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_LOUDRED_ANIM_INDEX
                },
              };
            case PKMN_LOUDRED_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 40 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_EXPLOUD_ANIM_INDEX
                },
              };
            case PKMN_EXPLOUD_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_MAKUHITA_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 24 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_HARIYAMA_ANIM_INDEX
                },
              };
            case PKMN_HARIYAMA_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_AZURILL_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 24 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_MARILL_ANIM_INDEX
                },
              };
            case PKMN_NOSEPASS_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 24 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_PROBOPASS_ANIM_INDEX
                },
              };
            case PKMN_SKITTY_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_DELCATTY_ANIM_INDEX
                },
              };
            case PKMN_DELCATTY_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_SABLEYE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_MAWILE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_ARON_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_LAIRON_ANIM_INDEX
                },
              };
            case PKMN_LAIRON_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 42 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_AGGRON_ANIM_INDEX
                },
              };
            case PKMN_AGGRON_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_MEDITITE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 37 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_MEDICHAM_ANIM_INDEX
                },
              };
            case PKMN_MEDICHAM_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_ELECTRIKE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 26 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_MANECTRIC_ANIM_INDEX
                },
              };
            case PKMN_MANECTRIC_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_PLUSLE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_MINUN_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_VOLBEAT_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_ILLUMISE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_ROSELIA_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_ROSERADE_ANIM_INDEX
                },
              };
            case PKMN_GULPIN_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 26 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_SWALOT_ANIM_INDEX
                },
              };
            case PKMN_SWALOT_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_CARVANHA_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 30 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_SHARPEDO_ANIM_INDEX
                },
              };
            case PKMN_SHARPEDO_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_WAILMER_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 40 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_WAILORD_ANIM_INDEX
                },
              };
            case PKMN_WAILORD_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_NUMEL_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 33 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_CAMERUPT_ANIM_INDEX
                },
              };
            case PKMN_CAMERUPT_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_TORKOAL_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_SPOINK_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_GRUMPIG_ANIM_INDEX
                },
              };
            case PKMN_GRUMPIG_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_SPINDA_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_TRAPINCH_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 35 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_VIBRAVA_ANIM_INDEX
                },
              };
            case PKMN_VIBRAVA_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 45 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_FLYGON_ANIM_INDEX
                },
              };
            case PKMN_FLYGON_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_CACNEA_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_CACTURNE_ANIM_INDEX
                },
              };
            case PKMN_CACTURNE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_SWABLU_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 35 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_ALTARIA_ANIM_INDEX
                },
              };
            case PKMN_ALTARIA_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_ZANGOOSE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_SEVIPER_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_LUNATONE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_SOLROCK_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_BARBOACH_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 30 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_WHISCASH_ANIM_INDEX
                },
              };
            case PKMN_WHISCASH_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_CORPHISH_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 30 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_CRAWDAUNT_ANIM_INDEX
                },
              };
            case PKMN_CRAWDAUNT_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_BALTOY_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 36 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_CLAYDOL_ANIM_INDEX
                },
              };
            case PKMN_CLAYDOL_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_LILEEP_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 40 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_CRADILY_ANIM_INDEX
                },
              };
            case PKMN_CRADILY_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_ANORITH_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 40 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_ARMALDO_ANIM_INDEX
                },
              };
            case PKMN_ARMALDO_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_FEEBAS_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 24 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_MILOTIC_ANIM_INDEX
                },
              };
            case PKMN_MILOTIC_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_CASTFORM_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_KECLEON_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_SHUPPET_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 37 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_BANETTE_ANIM_INDEX
                },
              };
            case PKMN_BANETTE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_DUSKULL_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 37 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_DUSCLOPS_ANIM_INDEX
                },
              };
            case PKMN_DUSCLOPS_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_DUSKNOIR_ANIM_INDEX
                },
              };
            case PKMN_TROPIUS_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_CHIMECHO_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_ABSOL_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_WYNAUT_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 15 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_WOBBUFFET_ANIM_INDEX
                },
              };
            case PKMN_SNORUNT_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
                
                .num_animation_indices = 2,
                .animation_indices = {
                  PKMN_GLALIE_ANIM_INDEX ,PKMN_FROSLASS_ANIM_INDEX
                },
              };
            case PKMN_GLALIE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_SPHEAL_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_SEALEO_ANIM_INDEX
                },
              };
            case PKMN_SEALEO_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 44 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_WALREIN_ANIM_INDEX
                },
              };
            case PKMN_WALREIN_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_CLAMPERL_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
                
                .num_animation_indices = 2,
                .animation_indices = {
                  PKMN_HUNTAIL_ANIM_INDEX ,PKMN_GOREBYSS_ANIM_INDEX
                },
              };
            case PKMN_HUNTAIL_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_GOREBYSS_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_RELICANTH_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_LUVDISC_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_BAGON_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 30 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_SHELGON_ANIM_INDEX
                },
              };
            case PKMN_SHELGON_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 50 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_SALAMENCE_ANIM_INDEX
                },
              };
            case PKMN_SALAMENCE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_BELDUM_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 20 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_METANG_ANIM_INDEX
                },
              };
            case PKMN_METANG_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 45 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_METAGROSS_ANIM_INDEX
                },
              };
            case PKMN_METAGROSS_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_REGIROCK_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_REGICE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_REGISTEEL_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_LATIAS_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_LATIOS_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_KYOGRE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_GROUDON_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_RAYQUAZA_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_JIRACHI_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_DEOXYS_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_TURTWIG_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 18 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_GROTLE_ANIM_INDEX
                },
              };
            case PKMN_GROTLE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_TORTERRA_ANIM_INDEX
                },
              };
            case PKMN_TORTERRA_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_CHIMCHAR_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 14 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_MONFERNO_ANIM_INDEX
                },
              };
            case PKMN_MONFERNO_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 36 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_INFERNAPE_ANIM_INDEX
                },
              };
            case PKMN_INFERNAPE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_PIPLUP_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 16 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_PRINPLUP_ANIM_INDEX
                },
              };
            case PKMN_PRINPLUP_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 36 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_EMPOLEON_ANIM_INDEX
                },
              };
            case PKMN_EMPOLEON_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_STARLY_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 14 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_STARAVIA_ANIM_INDEX
                },
              };
            case PKMN_STARAVIA_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 34 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_STARAPTOR_ANIM_INDEX
                },
              };
            case PKMN_STARAPTOR_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_BIDOOF_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 15 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_BIBAREL_ANIM_INDEX
                },
              };
            case PKMN_BIBAREL_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_KRICKETOT_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 10 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_KRICKETUNE_ANIM_INDEX
                },
              };
            case PKMN_KRICKETUNE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_SHINX_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 15 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_LUXIO_ANIM_INDEX
                },
              };
            case PKMN_LUXIO_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 30 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_LUXRAY_ANIM_INDEX
                },
              };
            case PKMN_LUXRAY_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_BUDEW_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 24 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_ROSELIA_ANIM_INDEX
                },
              };
            case PKMN_ROSERADE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_CRANIDOS_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 30 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_RAMPARDOS_ANIM_INDEX
                },
              };
            case PKMN_RAMPARDOS_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_SHIELDON_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 30 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_BASTIODON_ANIM_INDEX
                },
              };
            case PKMN_BASTIODON_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_BURMY_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 20 },
                
                .num_animation_indices = 2,
                .animation_indices = {
                  PKMN_WORMADAM_ANIM_INDEX ,PKMN_MOTHIM_ANIM_INDEX
                },
              };
            case PKMN_WORMADAM_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_MOTHIM_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_COMBEE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 21 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_VESPIQUEN_ANIM_INDEX
                },
              };
            case PKMN_VESPIQUEN_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_PACHIRISU_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_BUIZEL_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 26 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_FLOATZEL_ANIM_INDEX
                },
              };
            case PKMN_FLOATZEL_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_CHERUBI_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 25 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_CHERRIM_ANIM_INDEX
                },
              };
            case PKMN_CHERRIM_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_SHELLOS_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 30 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_GASTRODON_ANIM_INDEX
                },
              };
            case PKMN_GASTRODON_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_AMBIPOM_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_DRIFLOON_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 28 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_DRIFBLIM_ANIM_INDEX
                },
              };
            case PKMN_DRIFBLIM_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_BUNEARY_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 24 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_LOPUNNY_ANIM_INDEX
                },
              };
            case PKMN_LOPUNNY_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_MISMAGIUS_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_HONCHKROW_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_GLAMEOW_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 38 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_PURUGLY_ANIM_INDEX
                },
              };
            case PKMN_PURUGLY_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_CHINGLING_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 24 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_CHIMECHO_ANIM_INDEX
                },
              };
            case PKMN_STUNKY_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 34 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_SKUNTANK_ANIM_INDEX
                },
              };
            case PKMN_SKUNTANK_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_BRONZOR_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 33 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_BRONZONG_ANIM_INDEX
                },
              };
            case PKMN_BRONZONG_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_BONSLY_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 24 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_SUDOWOODO_ANIM_INDEX
                },
              };
            case PKMN_MIME_JR_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 24 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_MR_MIME_ANIM_INDEX
                },
              };
            case PKMN_HAPPINY_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_CHANSEY_ANIM_INDEX
                },
              };
            case PKMN_CHATOT_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_SPIRITOMB_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_GIBLE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 24 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_GABITE_ANIM_INDEX
                },
              };
            case PKMN_GABITE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 48 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_GARCHOMP_ANIM_INDEX
                },
              };
            case PKMN_GARCHOMP_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_MUNCHLAX_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 24 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_SNORLAX_ANIM_INDEX
                },
              };
            case PKMN_RIOLU_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 24 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_LUCARIO_ANIM_INDEX
                },
              };
            case PKMN_LUCARIO_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_HIPPOPOTAS_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 34 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_HIPPOWDON_ANIM_INDEX
                },
              };
            case PKMN_HIPPOWDON_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_SKORUPI_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 40 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_DRAPION_ANIM_INDEX
                },
              };
            case PKMN_DRAPION_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_CROAGUNK_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 37 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_TOXICROAK_ANIM_INDEX
                },
              };
            case PKMN_TOXICROAK_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_CARNIVINE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_FINNEON_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 31 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_LUMINEON_ANIM_INDEX
                },
              };
            case PKMN_LUMINEON_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_MANTYKE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 24 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_MANTINE_ANIM_INDEX
                },
              };
            case PKMN_SNOVER_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 40 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_ABOMASNOW_ANIM_INDEX
                },
              };
            case PKMN_ABOMASNOW_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_WEAVILE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_MAGNEZONE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_LICKILICKY_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_RHYPERIOR_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_TANGROWTH_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_ELECTIVIRE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_MAGMORTAR_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_TOGEKISS_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_YANMEGA_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_LEAFEON_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_GLACEON_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_GLISCOR_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_MAMOSWINE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_PORYGON_Z_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_GALLADE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_PROBOPASS_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_DUSKNOIR_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_FROSLASS_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_ROTOM_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_UXIE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_MESPRIT_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_AZELF_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_DIALGA_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_PALKIA_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_HEATRAN_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_REGIGIGAS_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_GIRATINA_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_CRESSELIA_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_PHIONE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_MANAPHY_ANIM_INDEX
                },
              };
            case PKMN_MANAPHY_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_DARKRAI_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_SHAYMIN_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_ARCEUS_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_VICTINI_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_SNIVY_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 17 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_SERVINE_ANIM_INDEX
                },
              };
            case PKMN_SERVINE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 36 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_SERPERIOR_ANIM_INDEX
                },
              };
            case PKMN_SERPERIOR_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_TEPIG_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 17 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_PIGNITE_ANIM_INDEX
                },
              };
            case PKMN_PIGNITE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 36 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_EMBOAR_ANIM_INDEX
                },
              };
            case PKMN_EMBOAR_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_OSHAWOTT_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 17 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_DEWOTT_ANIM_INDEX
                },
              };
            case PKMN_DEWOTT_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 36 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_SAMUROTT_ANIM_INDEX
                },
              };
            case PKMN_SAMUROTT_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_PATRAT_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 20 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_WATCHOG_ANIM_INDEX
                },
              };
            case PKMN_WATCHOG_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_LILLIPUP_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 16 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_HERDIER_ANIM_INDEX
                },
              };
            case PKMN_HERDIER_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_STOUTLAND_ANIM_INDEX
                },
              };
            case PKMN_STOUTLAND_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_PURRLOIN_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 20 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_LIEPARD_ANIM_INDEX
                },
              };
            case PKMN_LIEPARD_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_PANSAGE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_SIMISAGE_ANIM_INDEX
                },
              };
            case PKMN_SIMISAGE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_PANSEAR_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_SIMISEAR_ANIM_INDEX
                },
              };
            case PKMN_SIMISEAR_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_PANPOUR_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_SIMIPOUR_ANIM_INDEX
                },
              };
            case PKMN_SIMIPOUR_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_MUNNA_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_MUSHARNA_ANIM_INDEX
                },
              };
            case PKMN_MUSHARNA_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_PIDOVE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 21 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_TRANQUILL_ANIM_INDEX
                },
              };
            case PKMN_TRANQUILL_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_UNFEZANT_ANIM_INDEX
                },
              };
            case PKMN_UNFEZANT_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_BLITZLE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 27 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_ZEBSTRIKA_ANIM_INDEX
                },
              };
            case PKMN_ZEBSTRIKA_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_ROGGENROLA_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 25 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_BOLDORE_ANIM_INDEX
                },
              };
            case PKMN_BOLDORE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 28 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_GIGALITH_ANIM_INDEX
                },
              };
            case PKMN_GIGALITH_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_WOOBAT_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 24 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_SWOOBAT_ANIM_INDEX
                },
              };
            case PKMN_SWOOBAT_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_DRILBUR_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 31 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_EXCADRILL_ANIM_INDEX
                },
              };
            case PKMN_EXCADRILL_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_AUDINO_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_TIMBURR_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 25 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_GURDURR_ANIM_INDEX
                },
              };
            case PKMN_GURDURR_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 28 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_CONKELDURR_ANIM_INDEX
                },
              };
            case PKMN_CONKELDURR_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_TYMPOLE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 25 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_PALPITOAD_ANIM_INDEX
                },
              };
            case PKMN_PALPITOAD_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 36 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_SEISMITOAD_ANIM_INDEX
                },
              };
            case PKMN_SEISMITOAD_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_THROH_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_SAWK_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_SEWADDLE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 20 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_SWADLOON_ANIM_INDEX
                },
              };
            case PKMN_SWADLOON_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 24 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_LEAVANNY_ANIM_INDEX
                },
              };
            case PKMN_LEAVANNY_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_VENIPEDE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 22 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_WHIRLIPEDE_ANIM_INDEX
                },
              };
            case PKMN_WHIRLIPEDE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 30 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_SCOLIPEDE_ANIM_INDEX
                },
              };
            case PKMN_SCOLIPEDE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_COTTONEE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_WHIMSICOTT_ANIM_INDEX
                },
              };
            case PKMN_WHIMSICOTT_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_PETILIL_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_LILLIGANT_ANIM_INDEX
                },
              };
            case PKMN_LILLIGANT_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_BASCULIN_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 24 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_SANDILE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 29 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_KROKOROK_ANIM_INDEX
                },
              };
            case PKMN_KROKOROK_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 40 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_KROOKODILE_ANIM_INDEX
                },
              };
            case PKMN_KROOKODILE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_DARUMAKA_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_DARMANITAN_ANIM_INDEX
                },
              };
            case PKMN_DARMANITAN_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_MARACTUS_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_DWEBBLE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 34 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_CRUSTLE_ANIM_INDEX
                },
              };
            case PKMN_CRUSTLE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_SCRAGGY_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 39 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_SCRAFTY_ANIM_INDEX
                },
              };
            case PKMN_SCRAFTY_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_SIGILYPH_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_YAMASK_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 24 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_COFAGRIGUS_ANIM_INDEX
                },
              };
            case PKMN_COFAGRIGUS_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_TIRTOUGA_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 37 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_CARRACOSTA_ANIM_INDEX
                },
              };
            case PKMN_CARRACOSTA_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_ARCHEN_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 37 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_ARCHEOPS_ANIM_INDEX
                },
              };
            case PKMN_ARCHEOPS_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_TRUBBISH_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 36 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_GARBODOR_ANIM_INDEX
                },
              };
            case PKMN_GARBODOR_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_ZORUA_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 30 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_ZOROARK_ANIM_INDEX
                },
              };
            case PKMN_ZOROARK_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_MINCCINO_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_CINCCINO_ANIM_INDEX
                },
              };
            case PKMN_CINCCINO_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_GOTHITA_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_GOTHORITA_ANIM_INDEX
                },
              };
            case PKMN_GOTHORITA_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 41 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_GOTHITELLE_ANIM_INDEX
                },
              };
            case PKMN_GOTHITELLE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_SOLOSIS_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_DUOSION_ANIM_INDEX
                },
              };
            case PKMN_DUOSION_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 41 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_REUNICLUS_ANIM_INDEX
                },
              };
            case PKMN_REUNICLUS_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_DUCKLETT_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 35 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_SWANNA_ANIM_INDEX
                },
              };
            case PKMN_SWANNA_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_VANILLITE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 35 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_VANILLISH_ANIM_INDEX
                },
              };
            case PKMN_VANILLISH_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 47 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_VANILLUXE_ANIM_INDEX
                },
              };
            case PKMN_VANILLUXE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_DEERLING_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 34 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_SAWSBUCK_ANIM_INDEX
                },
              };
            case PKMN_SAWSBUCK_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_EMOLGA_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_KARRABLAST_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 28 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_ESCAVALIER_ANIM_INDEX
                },
              };
            case PKMN_ESCAVALIER_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_FOONGUS_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 39 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_AMOONGUSS_ANIM_INDEX
                },
              };
            case PKMN_AMOONGUSS_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_FRILLISH_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 40 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_JELLICENT_ANIM_INDEX
                },
              };
            case PKMN_JELLICENT_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_ALOMOMOLA_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_JOLTIK_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 36 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_GALVANTULA_ANIM_INDEX
                },
              };
            case PKMN_GALVANTULA_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_FERROSEED_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 40 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_FERROTHORN_ANIM_INDEX
                },
              };
            case PKMN_FERROTHORN_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_KLINK_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 38 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_KLANG_ANIM_INDEX
                },
              };
            case PKMN_KLANG_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 49 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_KLINKLANG_ANIM_INDEX
                },
              };
            case PKMN_KLINKLANG_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_TYNAMO_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 39 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_EELEKTRIK_ANIM_INDEX
                },
              };
            case PKMN_EELEKTRIK_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_EELEKTROSS_ANIM_INDEX
                },
              };
            case PKMN_EELEKTROSS_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_ELGYEM_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 42 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_BEHEEYEM_ANIM_INDEX
                },
              };
            case PKMN_BEHEEYEM_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_LITWICK_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 41 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_LAMPENT_ANIM_INDEX
                },
              };
            case PKMN_LAMPENT_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_CHANDELURE_ANIM_INDEX
                },
              };
            case PKMN_CHANDELURE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_AXEW_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 38 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_FRAXURE_ANIM_INDEX
                },
              };
            case PKMN_FRAXURE_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 48 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_HAXORUS_ANIM_INDEX
                },
              };
            case PKMN_HAXORUS_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_CUBCHOO_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 37 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_BEARTIC_ANIM_INDEX
                },
              };
            case PKMN_BEARTIC_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_CRYOGONAL_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_SHELMET_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 28 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_ACCELGOR_ANIM_INDEX
                },
              };
            case PKMN_ACCELGOR_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_STUNFISK_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_MIENFOO_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 50 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_MIENSHAO_ANIM_INDEX
                },
              };
            case PKMN_MIENSHAO_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_DRUDDIGON_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_GOLETT_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 43 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_GOLURK_ANIM_INDEX
                },
              };
            case PKMN_GOLURK_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_PAWNIARD_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 52 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_BISHARP_ANIM_INDEX
                },
              };
            case PKMN_BISHARP_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 24 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_BOUFFALANT_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_RUFFLET_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 54 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_BRAVIARY_ANIM_INDEX
                },
              };
            case PKMN_BRAVIARY_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_VULLABY_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 54 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_MANDIBUZZ_ANIM_INDEX
                },
              };
            case PKMN_MANDIBUZZ_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_HEATMOR_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_DURANT_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_DEINO_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 50 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_ZWEILOUS_ANIM_INDEX
                },
              };
            case PKMN_ZWEILOUS_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 64 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_HYDREIGON_ANIM_INDEX
                },
              };
            case PKMN_HYDREIGON_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_LARVESTA_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = 59 },
                
                .num_animation_indices = 1,
                .animation_indices = {
                  PKMN_VOLCARONA_ANIM_INDEX
                },
              };
            case PKMN_VOLCARONA_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_COBALION_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_TERRAKION_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_VIRIZION_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_TORNADUS_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_THUNDURUS_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_RESHIRAM_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_ZEKROM_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_LANDORUS_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_KYUREM_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_KELDEO_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_MELOETTA_ANIM_INDEX:
              return {
                .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
                
                .num_animation_indices = 0,
                .animation_indices = {
                  
                },
              };
            case PKMN_GENESECT_ANIM_INDEX:
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

