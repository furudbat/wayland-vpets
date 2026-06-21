#include "embedded_assets/embedded_image.h"
#include "embedded_assets/pkmn/pkmn.hpp"
#include "embedded_assets/pkmn/pkmn_evol.h"
#include "graphics/animation_shared_memory.h"

/// @NOTE: Generated evolution data pkmn

namespace bongocat::assets {
    static constexpr animation::animation_evolution_data_t pkmn_evol_data_table[] ASSETS_DATA_EVOL_SECTION = {
        // Name: Bulbasaur
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 16 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_IVYSAUR_ANIM_INDEX
            },
        },
        // Name: Ivysaur
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_VENUSAUR_ANIM_INDEX
            },
        },
        // Name: Venusaur
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Charmander
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 16 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_CHARMELEON_ANIM_INDEX
            },
        },
        // Name: Charmeleon
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 36 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_CHARIZARD_ANIM_INDEX
            },
        },
        // Name: Charizard
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Squirtle
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 16 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_WARTORTLE_ANIM_INDEX
            },
        },
        // Name: Wartortle
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 36 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_BLASTOISE_ANIM_INDEX
            },
        },
        // Name: Blastoise
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Caterpie
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 7 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_METAPOD_ANIM_INDEX
            },
        },
        // Name: Metapod
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 10 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_BUTTERFREE_ANIM_INDEX
            },
        },
        // Name: Butterfree
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Weedle
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 7 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_KAKUNA_ANIM_INDEX
            },
        },
        // Name: Kakuna
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 10 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_BEEDRILL_ANIM_INDEX
            },
        },
        // Name: Beedrill
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Pidgey
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 18 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_PIDGEOTTO_ANIM_INDEX
            },
        },
        // Name: Pidgeotto
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 36 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_PIDGEOT_ANIM_INDEX
            },
        },
        // Name: Pidgeot
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Rattata
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 20 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_RATICATE_ANIM_INDEX
            },
        },
        // Name: Raticate
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Spearow
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 20 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_FEAROW_ANIM_INDEX
            },
        },
        // Name: Fearow
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Ekans
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 22 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_ARBOK_ANIM_INDEX
            },
        },
        // Name: Arbok
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Pikachu
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_RAICHU_ANIM_INDEX
            },
        },
        // Name: Raichu
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Sandshrew
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 22 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_SANDSLASH_ANIM_INDEX
            },
        },
        // Name: Sandslash
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Nidoran-f
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 16 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_NIDORINA_ANIM_INDEX
            },
        },
        // Name: Nidorina
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_NIDOQUEEN_ANIM_INDEX
            },
        },
        // Name: Nidoqueen
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Nidoran-m
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 16 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_NIDORINO_ANIM_INDEX
            },
        },
        // Name: Nidorino
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_NIDOKING_ANIM_INDEX
            },
        },
        // Name: Nidoking
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Clefairy
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_CLEFABLE_ANIM_INDEX
            },
        },
        // Name: Clefable
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Vulpix
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_NINETALES_ANIM_INDEX
            },
        },
        // Name: Ninetales
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Jigglypuff
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_WIGGLYTUFF_ANIM_INDEX
            },
        },
        // Name: Wigglytuff
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Zubat
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 22 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_GOLBAT_ANIM_INDEX
            },
        },
        // Name: Golbat
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 24 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_CROBAT_ANIM_INDEX
            },
        },
        // Name: Oddish
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 21 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_GLOOM_ANIM_INDEX
            },
        },
        // Name: Gloom
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
            
            .num_animation_indices = 2,
            .animation_indices = {
                PKMN_VILEPLUME_ANIM_INDEX ,PKMN_BELLOSSOM_ANIM_INDEX
            },
        },
        // Name: Vileplume
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Paras
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 24 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_PARASECT_ANIM_INDEX
            },
        },
        // Name: Parasect
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Venonat
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 31 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_VENOMOTH_ANIM_INDEX
            },
        },
        // Name: Venomoth
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Diglett
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 26 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_DUGTRIO_ANIM_INDEX
            },
        },
        // Name: Dugtrio
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Meowth
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 24 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_PERSIAN_ANIM_INDEX
            },
        },
        // Name: Persian
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Psyduck
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 33 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_GOLDUCK_ANIM_INDEX
            },
        },
        // Name: Golduck
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Mankey
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 28 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_PRIMEAPE_ANIM_INDEX
            },
        },
        // Name: Primeape
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 24 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Growlithe
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_ARCANINE_ANIM_INDEX
            },
        },
        // Name: Arcanine
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Poliwag
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 25 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_POLIWHIRL_ANIM_INDEX
            },
        },
        // Name: Poliwhirl
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
            
            .num_animation_indices = 2,
            .animation_indices = {
                PKMN_POLIWRATH_ANIM_INDEX ,PKMN_POLITOED_ANIM_INDEX
            },
        },
        // Name: Poliwrath
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Abra
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 16 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_KADABRA_ANIM_INDEX
            },
        },
        // Name: Kadabra
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 28 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_ALAKAZAM_ANIM_INDEX
            },
        },
        // Name: Alakazam
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Machop
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 28 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_MACHOKE_ANIM_INDEX
            },
        },
        // Name: Machoke
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 28 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_MACHAMP_ANIM_INDEX
            },
        },
        // Name: Machamp
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Bellsprout
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 21 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_WEEPINBELL_ANIM_INDEX
            },
        },
        // Name: Weepinbell
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_VICTREEBEL_ANIM_INDEX
            },
        },
        // Name: Victreebel
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Tentacool
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 30 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_TENTACRUEL_ANIM_INDEX
            },
        },
        // Name: Tentacruel
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Geodude
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 25 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_GRAVELER_ANIM_INDEX
            },
        },
        // Name: Graveler
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 28 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_GOLEM_ANIM_INDEX
            },
        },
        // Name: Golem
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Ponyta
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 40 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_RAPIDASH_ANIM_INDEX
            },
        },
        // Name: Rapidash
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Slowpoke
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
            
            .num_animation_indices = 2,
            .animation_indices = {
                PKMN_SLOWBRO_ANIM_INDEX ,PKMN_SLOWKING_ANIM_INDEX
            },
        },
        // Name: Slowbro
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Magnemite
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 30 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_MAGNETON_ANIM_INDEX
            },
        },
        // Name: Magneton
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 24 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_MAGNEZONE_ANIM_INDEX
            },
        },
        // Name: Farfetchd
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 24 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Doduo
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 31 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_DODRIO_ANIM_INDEX
            },
        },
        // Name: Dodrio
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Seel
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 34 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_DEWGONG_ANIM_INDEX
            },
        },
        // Name: Dewgong
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Grimer
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 38 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_MUK_ANIM_INDEX
            },
        },
        // Name: Muk
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Shellder
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_CLOYSTER_ANIM_INDEX
            },
        },
        // Name: Cloyster
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Gastly
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 25 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_HAUNTER_ANIM_INDEX
            },
        },
        // Name: Haunter
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 28 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_GENGAR_ANIM_INDEX
            },
        },
        // Name: Gengar
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Onix
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_STEELIX_ANIM_INDEX
            },
        },
        // Name: Drowzee
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 26 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_HYPNO_ANIM_INDEX
            },
        },
        // Name: Hypno
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Krabby
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 28 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_KINGLER_ANIM_INDEX
            },
        },
        // Name: Kingler
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Voltorb
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 30 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_ELECTRODE_ANIM_INDEX
            },
        },
        // Name: Electrode
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Exeggcute
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_EXEGGUTOR_ANIM_INDEX
            },
        },
        // Name: Exeggutor
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Cubone
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 28 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_MAROWAK_ANIM_INDEX
            },
        },
        // Name: Marowak
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Hitmonlee
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Hitmonchan
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Lickitung
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 24 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_LICKILICKY_ANIM_INDEX
            },
        },
        // Name: Koffing
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 35 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_WEEZING_ANIM_INDEX
            },
        },
        // Name: Weezing
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Rhyhorn
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 42 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_RHYDON_ANIM_INDEX
            },
        },
        // Name: Rhydon
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_RHYPERIOR_ANIM_INDEX
            },
        },
        // Name: Chansey
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 24 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_BLISSEY_ANIM_INDEX
            },
        },
        // Name: Tangela
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 24 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_TANGROWTH_ANIM_INDEX
            },
        },
        // Name: Kangaskhan
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Horsea
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_SEADRA_ANIM_INDEX
            },
        },
        // Name: Seadra
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_KINGDRA_ANIM_INDEX
            },
        },
        // Name: Goldeen
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 33 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_SEAKING_ANIM_INDEX
            },
        },
        // Name: Seaking
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Staryu
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_STARMIE_ANIM_INDEX
            },
        },
        // Name: Starmie
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Mr-mime
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 42 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Scyther
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_SCIZOR_ANIM_INDEX
            },
        },
        // Name: Jynx
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Electabuzz
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_ELECTIVIRE_ANIM_INDEX
            },
        },
        // Name: Magmar
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_MAGMORTAR_ANIM_INDEX
            },
        },
        // Name: Pinsir
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Tauros
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Magikarp
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 20 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_GYARADOS_ANIM_INDEX
            },
        },
        // Name: Gyarados
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Lapras
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Ditto
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Eevee
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 24 },
            
            .num_animation_indices = 7,
            .animation_indices = {
                PKMN_VAPOREON_ANIM_INDEX ,PKMN_JOLTEON_ANIM_INDEX ,PKMN_FLAREON_ANIM_INDEX ,PKMN_ESPEON_ANIM_INDEX ,PKMN_UMBREON_ANIM_INDEX ,PKMN_LEAFEON_ANIM_INDEX ,PKMN_GLACEON_ANIM_INDEX
            },
        },
        // Name: Vaporeon
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Jolteon
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Flareon
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Porygon
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_PORYGON2_ANIM_INDEX
            },
        },
        // Name: Omanyte
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 40 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_OMASTAR_ANIM_INDEX
            },
        },
        // Name: Omastar
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Kabuto
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 40 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_KABUTOPS_ANIM_INDEX
            },
        },
        // Name: Kabutops
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Aerodactyl
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Snorlax
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Articuno
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Zapdos
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Moltres
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Dratini
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 30 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_DRAGONAIR_ANIM_INDEX
            },
        },
        // Name: Dragonair
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 55 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_DRAGONITE_ANIM_INDEX
            },
        },
        // Name: Dragonite
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Mewtwo
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Mew
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Chikorita
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 16 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_BAYLEEF_ANIM_INDEX
            },
        },
        // Name: Bayleef
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_MEGANIUM_ANIM_INDEX
            },
        },
        // Name: Meganium
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Cyndaquil
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 14 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_QUILAVA_ANIM_INDEX
            },
        },
        // Name: Quilava
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 36 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_TYPHLOSION_ANIM_INDEX
            },
        },
        // Name: Typhlosion
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Totodile
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 18 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_CROCONAW_ANIM_INDEX
            },
        },
        // Name: Croconaw
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 30 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_FERALIGATR_ANIM_INDEX
            },
        },
        // Name: Feraligatr
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Sentret
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 15 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_FURRET_ANIM_INDEX
            },
        },
        // Name: Furret
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Hoothoot
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 20 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_NOCTOWL_ANIM_INDEX
            },
        },
        // Name: Noctowl
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Ledyba
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 18 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_LEDIAN_ANIM_INDEX
            },
        },
        // Name: Ledian
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Spinarak
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 22 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_ARIADOS_ANIM_INDEX
            },
        },
        // Name: Ariados
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Crobat
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Chinchou
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 27 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_LANTURN_ANIM_INDEX
            },
        },
        // Name: Lanturn
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Pichu
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 24 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_PIKACHU_ANIM_INDEX
            },
        },
        // Name: Cleffa
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 24 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_CLEFAIRY_ANIM_INDEX
            },
        },
        // Name: Igglybuff
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 24 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_JIGGLYPUFF_ANIM_INDEX
            },
        },
        // Name: Togepi
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 24 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_TOGETIC_ANIM_INDEX
            },
        },
        // Name: Togetic
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_TOGEKISS_ANIM_INDEX
            },
        },
        // Name: Natu
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 25 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_XATU_ANIM_INDEX
            },
        },
        // Name: Xatu
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Mareep
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 15 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_FLAAFFY_ANIM_INDEX
            },
        },
        // Name: Flaaffy
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 30 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_AMPHAROS_ANIM_INDEX
            },
        },
        // Name: Ampharos
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Bellossom
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Marill
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 18 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_AZUMARILL_ANIM_INDEX
            },
        },
        // Name: Azumarill
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Sudowoodo
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Politoed
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Hoppip
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 18 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_SKIPLOOM_ANIM_INDEX
            },
        },
        // Name: Skiploom
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 27 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_JUMPLUFF_ANIM_INDEX
            },
        },
        // Name: Jumpluff
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Aipom
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 24 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_AMBIPOM_ANIM_INDEX
            },
        },
        // Name: Sunkern
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_SUNFLORA_ANIM_INDEX
            },
        },
        // Name: Sunflora
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Yanma
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 24 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_YANMEGA_ANIM_INDEX
            },
        },
        // Name: Wooper
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 20 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_QUAGSIRE_ANIM_INDEX
            },
        },
        // Name: Quagsire
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Espeon
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Umbreon
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Murkrow
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_HONCHKROW_ANIM_INDEX
            },
        },
        // Name: Slowking
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Misdreavus
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_MISMAGIUS_ANIM_INDEX
            },
        },
        // Name: Unown
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Wobbuffet
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Girafarig
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 24 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Pineco
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 31 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_FORRETRESS_ANIM_INDEX
            },
        },
        // Name: Forretress
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Dunsparce
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 24 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Gligar
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_GLISCOR_ANIM_INDEX
            },
        },
        // Name: Steelix
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Snubbull
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 23 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_GRANBULL_ANIM_INDEX
            },
        },
        // Name: Granbull
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Qwilfish
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 24 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Scizor
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Shuckle
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Heracross
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Sneasel
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_WEAVILE_ANIM_INDEX
            },
        },
        // Name: Teddiursa
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 30 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_URSARING_ANIM_INDEX
            },
        },
        // Name: Ursaring
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Slugma
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 38 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_MAGCARGO_ANIM_INDEX
            },
        },
        // Name: Magcargo
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Swinub
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 33 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_PILOSWINE_ANIM_INDEX
            },
        },
        // Name: Piloswine
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 24 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_MAMOSWINE_ANIM_INDEX
            },
        },
        // Name: Corsola
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 38 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Remoraid
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 25 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_OCTILLERY_ANIM_INDEX
            },
        },
        // Name: Octillery
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Delibird
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Mantine
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Skarmory
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Houndour
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 24 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_HOUNDOOM_ANIM_INDEX
            },
        },
        // Name: Houndoom
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Kingdra
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Phanpy
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 25 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_DONPHAN_ANIM_INDEX
            },
        },
        // Name: Donphan
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Porygon2
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_PORYGON_Z_ANIM_INDEX
            },
        },
        // Name: Stantler
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 24 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Smeargle
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Tyrogue
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 20 },
            
            .num_animation_indices = 3,
            .animation_indices = {
                PKMN_HITMONLEE_ANIM_INDEX ,PKMN_HITMONCHAN_ANIM_INDEX ,PKMN_HITMONTOP_ANIM_INDEX
            },
        },
        // Name: Hitmontop
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Smoochum
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 30 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_JYNX_ANIM_INDEX
            },
        },
        // Name: Elekid
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 30 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_ELECTABUZZ_ANIM_INDEX
            },
        },
        // Name: Magby
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 30 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_MAGMAR_ANIM_INDEX
            },
        },
        // Name: Miltank
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Blissey
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Raikou
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Entei
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Suicune
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Larvitar
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 30 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_PUPITAR_ANIM_INDEX
            },
        },
        // Name: Pupitar
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 55 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_TYRANITAR_ANIM_INDEX
            },
        },
        // Name: Tyranitar
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Lugia
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Ho-oh
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Celebi
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Treecko
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 16 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_GROVYLE_ANIM_INDEX
            },
        },
        // Name: Grovyle
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 36 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_SCEPTILE_ANIM_INDEX
            },
        },
        // Name: Sceptile
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Torchic
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 16 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_COMBUSKEN_ANIM_INDEX
            },
        },
        // Name: Combusken
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 36 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_BLAZIKEN_ANIM_INDEX
            },
        },
        // Name: Blaziken
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Mudkip
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 16 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_MARSHTOMP_ANIM_INDEX
            },
        },
        // Name: Marshtomp
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 36 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_SWAMPERT_ANIM_INDEX
            },
        },
        // Name: Swampert
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Poochyena
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 18 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_MIGHTYENA_ANIM_INDEX
            },
        },
        // Name: Mightyena
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Zigzagoon
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 20 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_LINOONE_ANIM_INDEX
            },
        },
        // Name: Linoone
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 35 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Wurmple
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 7 },
            
            .num_animation_indices = 2,
            .animation_indices = {
                PKMN_SILCOON_ANIM_INDEX ,PKMN_CASCOON_ANIM_INDEX
            },
        },
        // Name: Silcoon
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 10 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_BEAUTIFLY_ANIM_INDEX
            },
        },
        // Name: Beautifly
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Cascoon
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 10 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_DUSTOX_ANIM_INDEX
            },
        },
        // Name: Dustox
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Lotad
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 14 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_LOMBRE_ANIM_INDEX
            },
        },
        // Name: Lombre
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_LUDICOLO_ANIM_INDEX
            },
        },
        // Name: Ludicolo
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Seedot
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 14 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_NUZLEAF_ANIM_INDEX
            },
        },
        // Name: Nuzleaf
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_SHIFTRY_ANIM_INDEX
            },
        },
        // Name: Shiftry
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Taillow
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 22 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_SWELLOW_ANIM_INDEX
            },
        },
        // Name: Swellow
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Wingull
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 25 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_PELIPPER_ANIM_INDEX
            },
        },
        // Name: Pelipper
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Ralts
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 20 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_KIRLIA_ANIM_INDEX
            },
        },
        // Name: Kirlia
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 30 },
            
            .num_animation_indices = 2,
            .animation_indices = {
                PKMN_GARDEVOIR_ANIM_INDEX ,PKMN_GALLADE_ANIM_INDEX
            },
        },
        // Name: Gardevoir
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Surskit
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 22 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_MASQUERAIN_ANIM_INDEX
            },
        },
        // Name: Masquerain
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Shroomish
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 23 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_BRELOOM_ANIM_INDEX
            },
        },
        // Name: Breloom
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Slakoth
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 18 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_VIGOROTH_ANIM_INDEX
            },
        },
        // Name: Vigoroth
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 36 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_SLAKING_ANIM_INDEX
            },
        },
        // Name: Slaking
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Nincada
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 20 },
            
            .num_animation_indices = 2,
            .animation_indices = {
                PKMN_NINJASK_ANIM_INDEX ,PKMN_SHEDINJA_ANIM_INDEX
            },
        },
        // Name: Ninjask
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Shedinja
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Whismur
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 20 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_LOUDRED_ANIM_INDEX
            },
        },
        // Name: Loudred
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 40 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_EXPLOUD_ANIM_INDEX
            },
        },
        // Name: Exploud
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Makuhita
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 24 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_HARIYAMA_ANIM_INDEX
            },
        },
        // Name: Hariyama
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Azurill
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 24 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_MARILL_ANIM_INDEX
            },
        },
        // Name: Nosepass
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 24 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_PROBOPASS_ANIM_INDEX
            },
        },
        // Name: Skitty
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_DELCATTY_ANIM_INDEX
            },
        },
        // Name: Delcatty
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Sableye
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Mawile
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Aron
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_LAIRON_ANIM_INDEX
            },
        },
        // Name: Lairon
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 42 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_AGGRON_ANIM_INDEX
            },
        },
        // Name: Aggron
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Meditite
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 37 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_MEDICHAM_ANIM_INDEX
            },
        },
        // Name: Medicham
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Electrike
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 26 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_MANECTRIC_ANIM_INDEX
            },
        },
        // Name: Manectric
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Plusle
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Minun
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Volbeat
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Illumise
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Roselia
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_ROSERADE_ANIM_INDEX
            },
        },
        // Name: Gulpin
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 26 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_SWALOT_ANIM_INDEX
            },
        },
        // Name: Swalot
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Carvanha
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 30 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_SHARPEDO_ANIM_INDEX
            },
        },
        // Name: Sharpedo
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Wailmer
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 40 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_WAILORD_ANIM_INDEX
            },
        },
        // Name: Wailord
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Numel
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 33 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_CAMERUPT_ANIM_INDEX
            },
        },
        // Name: Camerupt
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Torkoal
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Spoink
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_GRUMPIG_ANIM_INDEX
            },
        },
        // Name: Grumpig
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Spinda
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Trapinch
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 35 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_VIBRAVA_ANIM_INDEX
            },
        },
        // Name: Vibrava
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 45 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_FLYGON_ANIM_INDEX
            },
        },
        // Name: Flygon
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Cacnea
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_CACTURNE_ANIM_INDEX
            },
        },
        // Name: Cacturne
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Swablu
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 35 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_ALTARIA_ANIM_INDEX
            },
        },
        // Name: Altaria
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Zangoose
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Seviper
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Lunatone
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Solrock
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Barboach
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 30 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_WHISCASH_ANIM_INDEX
            },
        },
        // Name: Whiscash
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Corphish
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 30 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_CRAWDAUNT_ANIM_INDEX
            },
        },
        // Name: Crawdaunt
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Baltoy
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 36 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_CLAYDOL_ANIM_INDEX
            },
        },
        // Name: Claydol
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Lileep
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 40 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_CRADILY_ANIM_INDEX
            },
        },
        // Name: Cradily
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Anorith
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 40 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_ARMALDO_ANIM_INDEX
            },
        },
        // Name: Armaldo
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Feebas
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 24 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_MILOTIC_ANIM_INDEX
            },
        },
        // Name: Milotic
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Castform
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Kecleon
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Shuppet
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 37 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_BANETTE_ANIM_INDEX
            },
        },
        // Name: Banette
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Duskull
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 37 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_DUSCLOPS_ANIM_INDEX
            },
        },
        // Name: Dusclops
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_DUSKNOIR_ANIM_INDEX
            },
        },
        // Name: Tropius
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Chimecho
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Absol
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Wynaut
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 15 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_WOBBUFFET_ANIM_INDEX
            },
        },
        // Name: Snorunt
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
            
            .num_animation_indices = 2,
            .animation_indices = {
                PKMN_GLALIE_ANIM_INDEX ,PKMN_FROSLASS_ANIM_INDEX
            },
        },
        // Name: Glalie
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Spheal
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_SEALEO_ANIM_INDEX
            },
        },
        // Name: Sealeo
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 44 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_WALREIN_ANIM_INDEX
            },
        },
        // Name: Walrein
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Clamperl
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
            
            .num_animation_indices = 2,
            .animation_indices = {
                PKMN_HUNTAIL_ANIM_INDEX ,PKMN_GOREBYSS_ANIM_INDEX
            },
        },
        // Name: Huntail
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Gorebyss
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Relicanth
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Luvdisc
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Bagon
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 30 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_SHELGON_ANIM_INDEX
            },
        },
        // Name: Shelgon
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 50 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_SALAMENCE_ANIM_INDEX
            },
        },
        // Name: Salamence
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Beldum
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 20 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_METANG_ANIM_INDEX
            },
        },
        // Name: Metang
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 45 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_METAGROSS_ANIM_INDEX
            },
        },
        // Name: Metagross
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Regirock
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Regice
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Registeel
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Latias
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Latios
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Kyogre
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Groudon
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Rayquaza
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Jirachi
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Deoxys
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Turtwig
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 18 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_GROTLE_ANIM_INDEX
            },
        },
        // Name: Grotle
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_TORTERRA_ANIM_INDEX
            },
        },
        // Name: Torterra
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Chimchar
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 14 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_MONFERNO_ANIM_INDEX
            },
        },
        // Name: Monferno
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 36 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_INFERNAPE_ANIM_INDEX
            },
        },
        // Name: Infernape
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Piplup
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 16 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_PRINPLUP_ANIM_INDEX
            },
        },
        // Name: Prinplup
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 36 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_EMPOLEON_ANIM_INDEX
            },
        },
        // Name: Empoleon
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Starly
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 14 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_STARAVIA_ANIM_INDEX
            },
        },
        // Name: Staravia
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 34 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_STARAPTOR_ANIM_INDEX
            },
        },
        // Name: Staraptor
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Bidoof
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 15 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_BIBAREL_ANIM_INDEX
            },
        },
        // Name: Bibarel
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Kricketot
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 10 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_KRICKETUNE_ANIM_INDEX
            },
        },
        // Name: Kricketune
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Shinx
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 15 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_LUXIO_ANIM_INDEX
            },
        },
        // Name: Luxio
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 30 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_LUXRAY_ANIM_INDEX
            },
        },
        // Name: Luxray
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Budew
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 24 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_ROSELIA_ANIM_INDEX
            },
        },
        // Name: Roserade
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Cranidos
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 30 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_RAMPARDOS_ANIM_INDEX
            },
        },
        // Name: Rampardos
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Shieldon
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 30 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_BASTIODON_ANIM_INDEX
            },
        },
        // Name: Bastiodon
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Burmy
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 20 },
            
            .num_animation_indices = 2,
            .animation_indices = {
                PKMN_WORMADAM_ANIM_INDEX ,PKMN_MOTHIM_ANIM_INDEX
            },
        },
        // Name: Wormadam
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Mothim
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Combee
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 21 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_VESPIQUEN_ANIM_INDEX
            },
        },
        // Name: Vespiquen
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Pachirisu
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Buizel
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 26 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_FLOATZEL_ANIM_INDEX
            },
        },
        // Name: Floatzel
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Cherubi
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 25 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_CHERRIM_ANIM_INDEX
            },
        },
        // Name: Cherrim
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Shellos
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 30 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_GASTRODON_ANIM_INDEX
            },
        },
        // Name: Gastrodon
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Ambipom
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Drifloon
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 28 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_DRIFBLIM_ANIM_INDEX
            },
        },
        // Name: Drifblim
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Buneary
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 24 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_LOPUNNY_ANIM_INDEX
            },
        },
        // Name: Lopunny
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Mismagius
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Honchkrow
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Glameow
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 38 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_PURUGLY_ANIM_INDEX
            },
        },
        // Name: Purugly
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Chingling
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 24 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_CHIMECHO_ANIM_INDEX
            },
        },
        // Name: Stunky
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 34 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_SKUNTANK_ANIM_INDEX
            },
        },
        // Name: Skuntank
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Bronzor
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 33 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_BRONZONG_ANIM_INDEX
            },
        },
        // Name: Bronzong
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Bonsly
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 24 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_SUDOWOODO_ANIM_INDEX
            },
        },
        // Name: Mime-jr
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 24 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_MR_MIME_ANIM_INDEX
            },
        },
        // Name: Happiny
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_CHANSEY_ANIM_INDEX
            },
        },
        // Name: Chatot
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Spiritomb
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Gible
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 24 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_GABITE_ANIM_INDEX
            },
        },
        // Name: Gabite
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 48 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_GARCHOMP_ANIM_INDEX
            },
        },
        // Name: Garchomp
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Munchlax
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 24 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_SNORLAX_ANIM_INDEX
            },
        },
        // Name: Riolu
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 24 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_LUCARIO_ANIM_INDEX
            },
        },
        // Name: Lucario
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Hippopotas
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 34 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_HIPPOWDON_ANIM_INDEX
            },
        },
        // Name: Hippowdon
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Skorupi
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 40 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_DRAPION_ANIM_INDEX
            },
        },
        // Name: Drapion
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Croagunk
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 37 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_TOXICROAK_ANIM_INDEX
            },
        },
        // Name: Toxicroak
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Carnivine
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Finneon
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 31 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_LUMINEON_ANIM_INDEX
            },
        },
        // Name: Lumineon
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Mantyke
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 24 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_MANTINE_ANIM_INDEX
            },
        },
        // Name: Snover
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 40 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_ABOMASNOW_ANIM_INDEX
            },
        },
        // Name: Abomasnow
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Weavile
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Magnezone
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Lickilicky
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Rhyperior
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Tangrowth
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Electivire
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Magmortar
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Togekiss
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Yanmega
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Leafeon
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Glaceon
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Gliscor
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Mamoswine
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Porygon-z
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Gallade
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Probopass
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Dusknoir
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Froslass
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Rotom
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Uxie
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Mesprit
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Azelf
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Dialga
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Palkia
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Heatran
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Regigigas
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Giratina
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Cresselia
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Phione
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_MANAPHY_ANIM_INDEX
            },
        },
        // Name: Manaphy
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Darkrai
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Shaymin
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Arceus
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Victini
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Snivy
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 17 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_SERVINE_ANIM_INDEX
            },
        },
        // Name: Servine
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 36 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_SERPERIOR_ANIM_INDEX
            },
        },
        // Name: Serperior
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Tepig
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 17 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_PIGNITE_ANIM_INDEX
            },
        },
        // Name: Pignite
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 36 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_EMBOAR_ANIM_INDEX
            },
        },
        // Name: Emboar
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Oshawott
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 17 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_DEWOTT_ANIM_INDEX
            },
        },
        // Name: Dewott
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 36 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_SAMUROTT_ANIM_INDEX
            },
        },
        // Name: Samurott
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Patrat
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 20 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_WATCHOG_ANIM_INDEX
            },
        },
        // Name: Watchog
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Lillipup
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 16 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_HERDIER_ANIM_INDEX
            },
        },
        // Name: Herdier
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_STOUTLAND_ANIM_INDEX
            },
        },
        // Name: Stoutland
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Purrloin
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 20 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_LIEPARD_ANIM_INDEX
            },
        },
        // Name: Liepard
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Pansage
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_SIMISAGE_ANIM_INDEX
            },
        },
        // Name: Simisage
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Pansear
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_SIMISEAR_ANIM_INDEX
            },
        },
        // Name: Simisear
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Panpour
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_SIMIPOUR_ANIM_INDEX
            },
        },
        // Name: Simipour
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Munna
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_MUSHARNA_ANIM_INDEX
            },
        },
        // Name: Musharna
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Pidove
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 21 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_TRANQUILL_ANIM_INDEX
            },
        },
        // Name: Tranquill
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_UNFEZANT_ANIM_INDEX
            },
        },
        // Name: Unfezant
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Blitzle
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 27 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_ZEBSTRIKA_ANIM_INDEX
            },
        },
        // Name: Zebstrika
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Roggenrola
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 25 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_BOLDORE_ANIM_INDEX
            },
        },
        // Name: Boldore
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 28 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_GIGALITH_ANIM_INDEX
            },
        },
        // Name: Gigalith
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Woobat
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 24 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_SWOOBAT_ANIM_INDEX
            },
        },
        // Name: Swoobat
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Drilbur
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 31 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_EXCADRILL_ANIM_INDEX
            },
        },
        // Name: Excadrill
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Audino
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Timburr
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 25 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_GURDURR_ANIM_INDEX
            },
        },
        // Name: Gurdurr
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 28 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_CONKELDURR_ANIM_INDEX
            },
        },
        // Name: Conkeldurr
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Tympole
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 25 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_PALPITOAD_ANIM_INDEX
            },
        },
        // Name: Palpitoad
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 36 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_SEISMITOAD_ANIM_INDEX
            },
        },
        // Name: Seismitoad
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Throh
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Sawk
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Sewaddle
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 20 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_SWADLOON_ANIM_INDEX
            },
        },
        // Name: Swadloon
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 24 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_LEAVANNY_ANIM_INDEX
            },
        },
        // Name: Leavanny
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Venipede
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 22 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_WHIRLIPEDE_ANIM_INDEX
            },
        },
        // Name: Whirlipede
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 30 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_SCOLIPEDE_ANIM_INDEX
            },
        },
        // Name: Scolipede
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Cottonee
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_WHIMSICOTT_ANIM_INDEX
            },
        },
        // Name: Whimsicott
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Petilil
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_LILLIGANT_ANIM_INDEX
            },
        },
        // Name: Lilligant
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Basculin
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 24 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Sandile
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 29 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_KROKOROK_ANIM_INDEX
            },
        },
        // Name: Krokorok
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 40 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_KROOKODILE_ANIM_INDEX
            },
        },
        // Name: Krookodile
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Darumaka
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_DARMANITAN_ANIM_INDEX
            },
        },
        // Name: Darmanitan
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Maractus
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Dwebble
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 34 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_CRUSTLE_ANIM_INDEX
            },
        },
        // Name: Crustle
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Scraggy
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 39 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_SCRAFTY_ANIM_INDEX
            },
        },
        // Name: Scrafty
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Sigilyph
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Yamask
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 24 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_COFAGRIGUS_ANIM_INDEX
            },
        },
        // Name: Cofagrigus
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Tirtouga
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 37 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_CARRACOSTA_ANIM_INDEX
            },
        },
        // Name: Carracosta
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Archen
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 37 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_ARCHEOPS_ANIM_INDEX
            },
        },
        // Name: Archeops
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Trubbish
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 36 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_GARBODOR_ANIM_INDEX
            },
        },
        // Name: Garbodor
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Zorua
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 30 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_ZOROARK_ANIM_INDEX
            },
        },
        // Name: Zoroark
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Minccino
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_CINCCINO_ANIM_INDEX
            },
        },
        // Name: Cinccino
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Gothita
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_GOTHORITA_ANIM_INDEX
            },
        },
        // Name: Gothorita
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 41 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_GOTHITELLE_ANIM_INDEX
            },
        },
        // Name: Gothitelle
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Solosis
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_DUOSION_ANIM_INDEX
            },
        },
        // Name: Duosion
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 41 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_REUNICLUS_ANIM_INDEX
            },
        },
        // Name: Reuniclus
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Ducklett
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 35 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_SWANNA_ANIM_INDEX
            },
        },
        // Name: Swanna
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Vanillite
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 35 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_VANILLISH_ANIM_INDEX
            },
        },
        // Name: Vanillish
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 47 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_VANILLUXE_ANIM_INDEX
            },
        },
        // Name: Vanilluxe
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Deerling
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 34 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_SAWSBUCK_ANIM_INDEX
            },
        },
        // Name: Sawsbuck
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Emolga
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Karrablast
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 28 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_ESCAVALIER_ANIM_INDEX
            },
        },
        // Name: Escavalier
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Foongus
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 39 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_AMOONGUSS_ANIM_INDEX
            },
        },
        // Name: Amoonguss
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Frillish
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 40 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_JELLICENT_ANIM_INDEX
            },
        },
        // Name: Jellicent
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Alomomola
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Joltik
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 36 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_GALVANTULA_ANIM_INDEX
            },
        },
        // Name: Galvantula
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Ferroseed
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 40 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_FERROTHORN_ANIM_INDEX
            },
        },
        // Name: Ferrothorn
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Klink
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 38 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_KLANG_ANIM_INDEX
            },
        },
        // Name: Klang
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 49 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_KLINKLANG_ANIM_INDEX
            },
        },
        // Name: Klinklang
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Tynamo
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 39 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_EELEKTRIK_ANIM_INDEX
            },
        },
        // Name: Eelektrik
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_EELEKTROSS_ANIM_INDEX
            },
        },
        // Name: Eelektross
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Elgyem
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 42 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_BEHEEYEM_ANIM_INDEX
            },
        },
        // Name: Beheeyem
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Litwick
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 41 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_LAMPENT_ANIM_INDEX
            },
        },
        // Name: Lampent
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 32 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_CHANDELURE_ANIM_INDEX
            },
        },
        // Name: Chandelure
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Axew
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 38 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_FRAXURE_ANIM_INDEX
            },
        },
        // Name: Fraxure
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 48 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_HAXORUS_ANIM_INDEX
            },
        },
        // Name: Haxorus
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Cubchoo
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 37 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_BEARTIC_ANIM_INDEX
            },
        },
        // Name: Beartic
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Cryogonal
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Shelmet
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 28 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_ACCELGOR_ANIM_INDEX
            },
        },
        // Name: Accelgor
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Stunfisk
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Mienfoo
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 50 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_MIENSHAO_ANIM_INDEX
            },
        },
        // Name: Mienshao
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Druddigon
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Golett
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 43 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_GOLURK_ANIM_INDEX
            },
        },
        // Name: Golurk
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Pawniard
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 52 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_BISHARP_ANIM_INDEX
            },
        },
        // Name: Bisharp
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 24 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Bouffalant
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Rufflet
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 54 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_BRAVIARY_ANIM_INDEX
            },
        },
        // Name: Braviary
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Vullaby
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 54 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_MANDIBUZZ_ANIM_INDEX
            },
        },
        // Name: Mandibuzz
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Heatmor
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Durant
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Deino
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 50 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_ZWEILOUS_ANIM_INDEX
            },
        },
        // Name: Zweilous
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 64 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_HYDREIGON_ANIM_INDEX
            },
        },
        // Name: Hydreigon
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Larvesta
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = 59 },
            
            .num_animation_indices = 1,
            .animation_indices = {
                PKMN_VOLCARONA_ANIM_INDEX
            },
        },
        // Name: Volcarona
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Cobalion
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Terrakion
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Virizion
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Tornadus
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Thundurus
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Reshiram
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Zekrom
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Landorus
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Kyurem
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Keldeo
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Meloetta
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },
        // Name: Genesect
        {
            // Stage: 
            .conditions = { .next_evolution_time_sec = -1, .min_lvl = -1 },
            
            .num_animation_indices = 0,
            .animation_indices = {
                
            },
        },

    };
    animation::animation_evolution_data_t get_pkmn_evolution_data(size_t index) {
        using namespace assets;
        assert(LEN_ARRAY(pkmn_evol_data_table) == PKMN_ANIM_COUNT);
        assert(index < PKMN_ANIM_COUNT);
        auto result = pkmn_evol_data_table[index];
        return result;
    }
}

