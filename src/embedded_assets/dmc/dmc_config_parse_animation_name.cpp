#include "embedded_assets/embedded_image.h"
#include "embedded_assets/dmc/dmc.hpp"
#include "dmc_config_parse_animation_name.h"
#include "utils/memory.h"
#include <cstdint>
#include "utils/system_memory.h"

namespace bongocat::assets {
    struct dmc_animation_table_entry_t {
        // offsets into DMC_STRINGS
        uint32_t name;
        uint32_t id;
        uint32_t fqid;
        uint32_t fqname;
        int32_t anim_index;
        config::config_animation_dm_set_t set;
        config::config_animation_sprite_sheet_layout_t layout;
    };
    static constexpr dmc_animation_table_entry_t dmc_animation_table[] CONFIG_LOCAL_STRING_SECTION = {
        { DMC_AGUMON_NAME_OFF, DMC_AGUMON_ID_OFF, DMC_AGUMON_FQID_OFF, DMC_AGUMON_FQNAME_OFF, DMC_AGUMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },  // Agumon
        { DMC_AIRDRAMON_NAME_OFF, DMC_AIRDRAMON_ID_OFF, DMC_AIRDRAMON_FQID_OFF, DMC_AIRDRAMON_FQNAME_OFF, DMC_AIRDRAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },  // Airdramon
        { DMC_ANDROMON_NAME_OFF, DMC_ANDROMON_ID_OFF, DMC_ANDROMON_FQID_OFF, DMC_ANDROMON_FQNAME_OFF, DMC_ANDROMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },  // Andromon
        { DMC_ANGEMON_NAME_OFF, DMC_ANGEMON_ID_OFF, DMC_ANGEMON_FQID_OFF, DMC_ANGEMON_FQNAME_OFF, DMC_ANGEMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },  // Angemon
        { DMC_BAKEMON_NAME_OFF, DMC_BAKEMON_ID_OFF, DMC_BAKEMON_FQID_OFF, DMC_BAKEMON_FQNAME_OFF, DMC_BAKEMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },  // Bakemon
        { DMC_BANCHO_LEOMON_NAME_OFF, DMC_BANCHO_LEOMON_ID_OFF, DMC_BANCHO_LEOMON_FQID_OFF, DMC_BANCHO_LEOMON_FQNAME_OFF, DMC_BANCHO_LEOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },  // Bancho Leomon
        { DMC_BANCHO_MAMEMON_NAME_OFF, DMC_BANCHO_MAMEMON_ID_OFF, DMC_BANCHO_MAMEMON_FQID_OFF, DMC_BANCHO_MAMEMON_FQNAME_OFF, DMC_BANCHO_MAMEMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },  // Bancho Mamemon
        { DMC_BETAMON_NAME_OFF, DMC_BETAMON_ID_OFF, DMC_BETAMON_FQID_OFF, DMC_BETAMON_FQNAME_OFF, DMC_BETAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },  // Betamon
        { DMC_BIRDRAMON_NAME_OFF, DMC_BIRDRAMON_ID_OFF, DMC_BIRDRAMON_FQID_OFF, DMC_BIRDRAMON_FQNAME_OFF, DMC_BIRDRAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },  // Birdramon
        { DMC_BLITZ_GREYMON_NAME_OFF, DMC_BLITZ_GREYMON_ID_OFF, DMC_BLITZ_GREYMON_FQID_OFF, DMC_BLITZ_GREYMON_FQNAME_OFF, DMC_BLITZ_GREYMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },  // Blitz Greymon
        { DMC_BLOOM_LORDMON_NAME_OFF, DMC_BLOOM_LORDMON_ID_OFF, DMC_BLOOM_LORDMON_FQID_OFF, DMC_BLOOM_LORDMON_FQNAME_OFF, DMC_BLOOM_LORDMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },  // Bloom Lordmon
        { DMC_BOTAMON_NAME_OFF, DMC_BOTAMON_ID_OFF, DMC_BOTAMON_FQID_OFF, DMC_BOTAMON_FQNAME_OFF, DMC_BOTAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },  // Botamon
        { DMC_CENTAURMON_NAME_OFF, DMC_CENTAURMON_ID_OFF, DMC_CENTAURMON_FQID_OFF, DMC_CENTAURMON_FQNAME_OFF, DMC_CENTAURMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },  // Centaurmon
        { DMC_CHAOSDRAMON_NAME_OFF, DMC_CHAOSDRAMON_ID_OFF, DMC_CHAOSDRAMON_FQID_OFF, DMC_CHAOSDRAMON_FQNAME_OFF, DMC_CHAOSDRAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },  // Chaosdramon
        { DMC_CHAOSMON_NAME_OFF, DMC_CHAOSMON_ID_OFF, DMC_CHAOSMON_FQID_OFF, DMC_CHAOSMON_FQNAME_OFF, DMC_CHAOSMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },  // Chaosmon
        { DMC_CHIMAIRAMON_NAME_OFF, DMC_CHIMAIRAMON_ID_OFF, DMC_CHIMAIRAMON_FQID_OFF, DMC_CHIMAIRAMON_FQNAME_OFF, DMC_CHIMAIRAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },  // Chimairamon
        { DMC_COCKATRIMON_NAME_OFF, DMC_COCKATRIMON_ID_OFF, DMC_COCKATRIMON_FQID_OFF, DMC_COCKATRIMON_FQNAME_OFF, DMC_COCKATRIMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },  // Cockatrimon
        { DMC_COELAMON_NAME_OFF, DMC_COELAMON_ID_OFF, DMC_COELAMON_FQID_OFF, DMC_COELAMON_FQNAME_OFF, DMC_COELAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },  // Coelamon
        { DMC_CRES_GARURUMON_NAME_OFF, DMC_CRES_GARURUMON_ID_OFF, DMC_CRES_GARURUMON_FQID_OFF, DMC_CRES_GARURUMON_FQNAME_OFF, DMC_CRES_GARURUMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },  // Cres Garurumon
        { DMC_CYCLOMON_NAME_OFF, DMC_CYCLOMON_ID_OFF, DMC_CYCLOMON_FQID_OFF, DMC_CYCLOMON_FQNAME_OFF, DMC_CYCLOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },  // Cyclomon
        { DMC_DARKDRAMON_NAME_OFF, DMC_DARKDRAMON_ID_OFF, DMC_DARKDRAMON_FQID_OFF, DMC_DARKDRAMON_FQNAME_OFF, DMC_DARKDRAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },  // Darkdramon
        { DMC_DARK_TYRANOMON_NAME_OFF, DMC_DARK_TYRANOMON_ID_OFF, DMC_DARK_TYRANOMON_FQID_OFF, DMC_DARK_TYRANOMON_FQNAME_OFF, DMC_DARK_TYRANOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },  // Dark Tyranomon
        { DMC_DELTAMON_NAME_OFF, DMC_DELTAMON_ID_OFF, DMC_DELTAMON_FQID_OFF, DMC_DELTAMON_FQNAME_OFF, DMC_DELTAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },  // Deltamon
        { DMC_DEVIDRAMON_NAME_OFF, DMC_DEVIDRAMON_ID_OFF, DMC_DEVIDRAMON_FQID_OFF, DMC_DEVIDRAMON_FQNAME_OFF, DMC_DEVIDRAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },  // Devidramon
        { DMC_DEVIMON_NAME_OFF, DMC_DEVIMON_ID_OFF, DMC_DEVIMON_FQID_OFF, DMC_DEVIMON_FQNAME_OFF, DMC_DEVIMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },  // Devimon
        { DMC_DIGITAMAMON_NAME_OFF, DMC_DIGITAMAMON_ID_OFF, DMC_DIGITAMAMON_FQID_OFF, DMC_DIGITAMAMON_FQNAME_OFF, DMC_DIGITAMAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },  // Digitamamon
        { DMC_DRIMOGEMON_NAME_OFF, DMC_DRIMOGEMON_ID_OFF, DMC_DRIMOGEMON_FQID_OFF, DMC_DRIMOGEMON_FQNAME_OFF, DMC_DRIMOGEMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },  // Drimogemon
        { DMC_EBEMON_NAME_OFF, DMC_EBEMON_ID_OFF, DMC_EBEMON_FQID_OFF, DMC_EBEMON_FQNAME_OFF, DMC_EBEMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },  // Ebemon
        { DMC_ELECMON_NAME_OFF, DMC_ELECMON_ID_OFF, DMC_ELECMON_FQID_OFF, DMC_ELECMON_FQNAME_OFF, DMC_ELECMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },  // Elecmon
        { DMC_ETEMON_NAME_OFF, DMC_ETEMON_ID_OFF, DMC_ETEMON_FQID_OFF, DMC_ETEMON_FQNAME_OFF, DMC_ETEMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },  // Etemon
        { DMC_EX_TYRANOMON_NAME_OFF, DMC_EX_TYRANOMON_ID_OFF, DMC_EX_TYRANOMON_FQID_OFF, DMC_EX_TYRANOMON_FQNAME_OFF, DMC_EX_TYRANOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },  // Ex-Tyranomon
        { DMC_FLYMON_NAME_OFF, DMC_FLYMON_ID_OFF, DMC_FLYMON_FQID_OFF, DMC_FLYMON_FQNAME_OFF, DMC_FLYMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },  // Flymon
        { DMC_GABUMON_NAME_OFF, DMC_GABUMON_ID_OFF, DMC_GABUMON_FQID_OFF, DMC_GABUMON_FQNAME_OFF, DMC_GABUMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },  // Gabumon
        { DMC_GAIOUMON_NAME_OFF, DMC_GAIOUMON_ID_OFF, DMC_GAIOUMON_FQID_OFF, DMC_GAIOUMON_FQNAME_OFF, DMC_GAIOUMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },  // Gaioumon
        { DMC_GANKOOMON_NAME_OFF, DMC_GANKOOMON_ID_OFF, DMC_GANKOOMON_FQID_OFF, DMC_GANKOOMON_FQNAME_OFF, DMC_GANKOOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },  // Gankoomon
        { DMC_GARURUMON_NAME_OFF, DMC_GARURUMON_ID_OFF, DMC_GARURUMON_FQID_OFF, DMC_GARURUMON_FQNAME_OFF, DMC_GARURUMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },  // Garurumon
        { DMC_GAZIMON_NAME_OFF, DMC_GAZIMON_ID_OFF, DMC_GAZIMON_FQID_OFF, DMC_GAZIMON_FQNAME_OFF, DMC_GAZIMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },  // Gazimon
        { DMC_GIROMON_NAME_OFF, DMC_GIROMON_ID_OFF, DMC_GIROMON_FQID_OFF, DMC_GIROMON_FQNAME_OFF, DMC_GIROMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },  // Giromon
        { DMC_GIZAMON_NAME_OFF, DMC_GIZAMON_ID_OFF, DMC_GIZAMON_FQID_OFF, DMC_GIZAMON_FQNAME_OFF, DMC_GIZAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },  // Gizamon
        { DMC_GOKUMON_NAME_OFF, DMC_GOKUMON_ID_OFF, DMC_GOKUMON_FQID_OFF, DMC_GOKUMON_FQNAME_OFF, DMC_GOKUMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },  // Gokumon
        { DMC_GREYMON_NAME_OFF, DMC_GREYMON_ID_OFF, DMC_GREYMON_FQID_OFF, DMC_GREYMON_FQNAME_OFF, DMC_GREYMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },  // Greymon
        { DMC_HI_ANDROMON_NAME_OFF, DMC_HI_ANDROMON_ID_OFF, DMC_HI_ANDROMON_FQID_OFF, DMC_HI_ANDROMON_FQNAME_OFF, DMC_HI_ANDROMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },  // Hi Andromon
        { DMC_KABUTERIMON_NAME_OFF, DMC_KABUTERIMON_ID_OFF, DMC_KABUTERIMON_FQID_OFF, DMC_KABUTERIMON_FQNAME_OFF, DMC_KABUTERIMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },  // Kabuterimon
        { DMC_KOROMON_NAME_OFF, DMC_KOROMON_ID_OFF, DMC_KOROMON_FQID_OFF, DMC_KOROMON_FQNAME_OFF, DMC_KOROMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },  // Koromon
        { DMC_KUNEMON_NAME_OFF, DMC_KUNEMON_ID_OFF, DMC_KUNEMON_FQID_OFF, DMC_KUNEMON_FQNAME_OFF, DMC_KUNEMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },  // Kunemon
        { DMC_KUWAGAMON_NAME_OFF, DMC_KUWAGAMON_ID_OFF, DMC_KUWAGAMON_FQID_OFF, DMC_KUWAGAMON_FQNAME_OFF, DMC_KUWAGAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },  // Kuwagamon
        { DMC_LEOMON_NAME_OFF, DMC_LEOMON_ID_OFF, DMC_LEOMON_FQID_OFF, DMC_LEOMON_FQNAME_OFF, DMC_LEOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },  // Leomon
        { DMC_MAMEMON_NAME_OFF, DMC_MAMEMON_ID_OFF, DMC_MAMEMON_FQID_OFF, DMC_MAMEMON_FQNAME_OFF, DMC_MAMEMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },  // Mamemon
        { DMC_MEGADRAMON_NAME_OFF, DMC_MEGADRAMON_ID_OFF, DMC_MEGADRAMON_FQID_OFF, DMC_MEGADRAMON_FQNAME_OFF, DMC_MEGADRAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },  // Megadramon
        { DMC_MERAMON_NAME_OFF, DMC_MERAMON_ID_OFF, DMC_MERAMON_FQID_OFF, DMC_MERAMON_FQNAME_OFF, DMC_MERAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },  // Meramon
        { DMC_METAL_GREYMON_VIRUS_NAME_OFF, DMC_METAL_GREYMON_VIRUS_ID_OFF, DMC_METAL_GREYMON_VIRUS_FQID_OFF, DMC_METAL_GREYMON_VIRUS_FQNAME_OFF, DMC_METAL_GREYMON_VIRUS_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },  // Metal Greymon (Virus)
        { DMC_METAL_MAMEMON_NAME_OFF, DMC_METAL_MAMEMON_ID_OFF, DMC_METAL_MAMEMON_FQID_OFF, DMC_METAL_MAMEMON_FQNAME_OFF, DMC_METAL_MAMEMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },  // Metal Mamemon
        { DMC_METAL_TYRANOMON_NAME_OFF, DMC_METAL_TYRANOMON_ID_OFF, DMC_METAL_TYRANOMON_FQID_OFF, DMC_METAL_TYRANOMON_FQNAME_OFF, DMC_METAL_TYRANOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },  // Metal Tyranomon
        { DMC_MILLENNIUMON_NAME_OFF, DMC_MILLENNIUMON_ID_OFF, DMC_MILLENNIUMON_FQID_OFF, DMC_MILLENNIUMON_FQNAME_OFF, DMC_MILLENNIUMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },  // Millenniumon
        { DMC_MOJYAMON_NAME_OFF, DMC_MOJYAMON_ID_OFF, DMC_MOJYAMON_FQID_OFF, DMC_MOJYAMON_FQNAME_OFF, DMC_MOJYAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },  // Mojyamon
        { DMC_MONOCHROMON_NAME_OFF, DMC_MONOCHROMON_ID_OFF, DMC_MONOCHROMON_FQID_OFF, DMC_MONOCHROMON_FQNAME_OFF, DMC_MONOCHROMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },  // Monochromon
        { DMC_MONZAEMON_NAME_OFF, DMC_MONZAEMON_ID_OFF, DMC_MONZAEMON_FQID_OFF, DMC_MONZAEMON_FQNAME_OFF, DMC_MONZAEMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },  // Monzaemon
        { DMC_MUGENDRAMON_NAME_OFF, DMC_MUGENDRAMON_ID_OFF, DMC_MUGENDRAMON_FQID_OFF, DMC_MUGENDRAMON_FQNAME_OFF, DMC_MUGENDRAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },  // Mugendramon
        { DMC_NANIMON_NAME_OFF, DMC_NANIMON_ID_OFF, DMC_NANIMON_FQID_OFF, DMC_NANIMON_FQNAME_OFF, DMC_NANIMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },  // Nanimon
        { DMC_NANOMON_NAME_OFF, DMC_NANOMON_ID_OFF, DMC_NANOMON_FQID_OFF, DMC_NANOMON_FQNAME_OFF, DMC_NANOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },  // Nanomon
        { DMC_NUMEMON_NAME_OFF, DMC_NUMEMON_ID_OFF, DMC_NUMEMON_FQID_OFF, DMC_NUMEMON_FQNAME_OFF, DMC_NUMEMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },  // Numemon
        { DMC_OGREMON_NAME_OFF, DMC_OGREMON_ID_OFF, DMC_OGREMON_FQID_OFF, DMC_OGREMON_FQNAME_OFF, DMC_OGREMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },  // Ogremon
        { DMC_OMEGAMON_ALTER_S_NAME_OFF, DMC_OMEGAMON_ALTER_S_ID_OFF, DMC_OMEGAMON_ALTER_S_FQID_OFF, DMC_OMEGAMON_ALTER_S_FQNAME_OFF, DMC_OMEGAMON_ALTER_S_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },  // Omegamon Alter-S
        { DMC_PAGUMON_NAME_OFF, DMC_PAGUMON_ID_OFF, DMC_PAGUMON_FQID_OFF, DMC_PAGUMON_FQNAME_OFF, DMC_PAGUMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },  // Pagumon
        { DMC_PALMON_NAME_OFF, DMC_PALMON_ID_OFF, DMC_PALMON_FQID_OFF, DMC_PALMON_FQNAME_OFF, DMC_PALMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },  // Palmon
        { DMC_PATAMON_NAME_OFF, DMC_PATAMON_ID_OFF, DMC_PATAMON_FQID_OFF, DMC_PATAMON_FQNAME_OFF, DMC_PATAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },  // Patamon
        { DMC_PICCOLOMON_NAME_OFF, DMC_PICCOLOMON_ID_OFF, DMC_PICCOLOMON_FQID_OFF, DMC_PICCOLOMON_FQNAME_OFF, DMC_PICCOLOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },  // Piccolomon
        { DMC_PIYOMON_NAME_OFF, DMC_PIYOMON_ID_OFF, DMC_PIYOMON_FQID_OFF, DMC_PIYOMON_FQNAME_OFF, DMC_PIYOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },  // Piyomon
        { DMC_POYOMON_NAME_OFF, DMC_POYOMON_ID_OFF, DMC_POYOMON_FQID_OFF, DMC_POYOMON_FQNAME_OFF, DMC_POYOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },  // Poyomon
        { DMC_PUNIMON_NAME_OFF, DMC_PUNIMON_ID_OFF, DMC_PUNIMON_FQID_OFF, DMC_PUNIMON_FQNAME_OFF, DMC_PUNIMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },  // Punimon
        { DMC_RAIDENMON_NAME_OFF, DMC_RAIDENMON_ID_OFF, DMC_RAIDENMON_FQID_OFF, DMC_RAIDENMON_FQNAME_OFF, DMC_RAIDENMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },  // Raidenmon
        { DMC_RAREMON_NAME_OFF, DMC_RAREMON_ID_OFF, DMC_RAREMON_FQID_OFF, DMC_RAREMON_FQNAME_OFF, DMC_RAREMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },  // Raremon
        { DMC_SCUMON_NAME_OFF, DMC_SCUMON_ID_OFF, DMC_SCUMON_FQID_OFF, DMC_SCUMON_FQNAME_OFF, DMC_SCUMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },  // Scumon
        { DMC_SEADRAMON_NAME_OFF, DMC_SEADRAMON_ID_OFF, DMC_SEADRAMON_FQID_OFF, DMC_SEADRAMON_FQNAME_OFF, DMC_SEADRAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },  // Seadramon
        { DMC_SHELLMON_NAME_OFF, DMC_SHELLMON_ID_OFF, DMC_SHELLMON_FQID_OFF, DMC_SHELLMON_FQNAME_OFF, DMC_SHELLMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },  // Shellmon
        { DMC_SHIN_MONZAEMON_NAME_OFF, DMC_SHIN_MONZAEMON_ID_OFF, DMC_SHIN_MONZAEMON_FQID_OFF, DMC_SHIN_MONZAEMON_FQNAME_OFF, DMC_SHIN_MONZAEMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },  // Shin Monzaemon
        { DMC_SKULL_GREYMON_NAME_OFF, DMC_SKULL_GREYMON_ID_OFF, DMC_SKULL_GREYMON_FQID_OFF, DMC_SKULL_GREYMON_FQNAME_OFF, DMC_SKULL_GREYMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },  // Skull Greymon
        { DMC_SKULL_MAMMON_NAME_OFF, DMC_SKULL_MAMMON_ID_OFF, DMC_SKULL_MAMMON_FQID_OFF, DMC_SKULL_MAMMON_FQNAME_OFF, DMC_SKULL_MAMMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },  // Skull Mammon
        { DMC_TANEMON_NAME_OFF, DMC_TANEMON_ID_OFF, DMC_TANEMON_FQID_OFF, DMC_TANEMON_FQNAME_OFF, DMC_TANEMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },  // Tanemon
        { DMC_TOKOMON_NAME_OFF, DMC_TOKOMON_ID_OFF, DMC_TOKOMON_FQID_OFF, DMC_TOKOMON_FQNAME_OFF, DMC_TOKOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },  // Tokomon
        { DMC_TSUNOMON_NAME_OFF, DMC_TSUNOMON_ID_OFF, DMC_TSUNOMON_FQID_OFF, DMC_TSUNOMON_FQNAME_OFF, DMC_TSUNOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },  // Tsunomon
        { DMC_TUSKMON_NAME_OFF, DMC_TUSKMON_ID_OFF, DMC_TUSKMON_FQID_OFF, DMC_TUSKMON_FQNAME_OFF, DMC_TUSKMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },  // Tuskmon
        { DMC_TYRANOMON_NAME_OFF, DMC_TYRANOMON_ID_OFF, DMC_TYRANOMON_FQID_OFF, DMC_TYRANOMON_FQNAME_OFF, DMC_TYRANOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },  // Tyranomon
        { DMC_UNIMON_NAME_OFF, DMC_UNIMON_ID_OFF, DMC_UNIMON_FQID_OFF, DMC_UNIMON_FQNAME_OFF, DMC_UNIMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },  // Unimon
        { DMC_VADEMON_NAME_OFF, DMC_VADEMON_ID_OFF, DMC_VADEMON_FQID_OFF, DMC_VADEMON_FQNAME_OFF, DMC_VADEMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },  // Vademon
        { DMC_VEGIMON_NAME_OFF, DMC_VEGIMON_ID_OFF, DMC_VEGIMON_FQID_OFF, DMC_VEGIMON_FQNAME_OFF, DMC_VEGIMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },  // Vegimon
        { DMC_WHAMON_NAME_OFF, DMC_WHAMON_ID_OFF, DMC_WHAMON_FQID_OFF, DMC_WHAMON_FQNAME_OFF, DMC_WHAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },  // Whamon
        { DMC_YUKIDARUMON_NAME_OFF, DMC_YUKIDARUMON_ID_OFF, DMC_YUKIDARUMON_FQID_OFF, DMC_YUKIDARUMON_FQNAME_OFF, DMC_YUKIDARUMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },  // Yukidarumon
        { DMC_YURAMON_NAME_OFF, DMC_YURAMON_ID_OFF, DMC_YURAMON_FQID_OFF, DMC_YURAMON_FQNAME_OFF, DMC_YURAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },  // Yuramon
        { DMC_ZURUMON_NAME_OFF, DMC_ZURUMON_ID_OFF, DMC_ZURUMON_FQID_OFF, DMC_ZURUMON_FQNAME_OFF, DMC_ZURUMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },  // Zurumon
        
    };
    static_assert(LEN_ARRAY(dmc_animation_table) == DMC_ANIM_COUNT);

    config_animation_entry_t get_config_animation_name_dmc(size_t index) {
        assert(index < DMC_ANIM_COUNT);
        const auto& entry = dmc_animation_table[index];
        return { DMC_STRINGS + entry.name, DMC_STRINGS + entry.id, DMC_STRINGS + entry.fqid, DMC_STRINGS + entry.fqname, entry.anim_index, entry.set, entry.layout };
    }

    int config_parse_animation_name_dmc(config::config_t& config, const char *value) {
        int ret = -1;
        for (size_t i = 0;ret < 0 && i < DMC_ANIM_COUNT;++i) {
            const auto& entry = dmc_animation_table[i];
            if (strcmp(value, DMC_STRINGS + entry.name) == 0 ||
                strcmp(value, DMC_STRINGS + entry.id) == 0 ||
                strcmp(value, DMC_STRINGS + entry.fqid) == 0 ||
                strcmp(value, DMC_STRINGS + entry.fqname) == 0) {
                config.animation_index = entry.anim_index;
                config.animation_dm_set = entry.set;
                config.animation_sprite_sheet_layout = entry.layout;
                ret = entry.anim_index;
                break;
            }
        }
        return ret;
    }
}
