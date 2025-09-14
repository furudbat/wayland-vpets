#include "embedded_assets/embedded_image.h"
#include "embedded_assets/dmc/dmc.hpp"
#include "dmc_config_parse_animation_name.h"

namespace bongocat::assets {
    static const config_animation_entry_t dmc_animation_table[] = {
        { DMC_AGUMON_NAME, DMC_AGUMON_ID, DMC_AGUMON_FQID, DMC_AGUMON_FQNAME, DMC_AGUMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMC_AIRDRAMON_NAME, DMC_AIRDRAMON_ID, DMC_AIRDRAMON_FQID, DMC_AIRDRAMON_FQNAME, DMC_AIRDRAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMC_ANDROMON_NAME, DMC_ANDROMON_ID, DMC_ANDROMON_FQID, DMC_ANDROMON_FQNAME, DMC_ANDROMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMC_ANGEMON_NAME, DMC_ANGEMON_ID, DMC_ANGEMON_FQID, DMC_ANGEMON_FQNAME, DMC_ANGEMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMC_BABYDMON_NAME, DMC_BABYDMON_ID, DMC_BABYDMON_FQID, DMC_BABYDMON_FQNAME, DMC_BABYDMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMC_BAKEMON_NAME, DMC_BAKEMON_ID, DMC_BAKEMON_FQID, DMC_BAKEMON_FQNAME, DMC_BAKEMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMC_BANCHO_MAMEMON_NAME, DMC_BANCHO_MAMEMON_ID, DMC_BANCHO_MAMEMON_FQID, DMC_BANCHO_MAMEMON_FQNAME, DMC_BANCHO_MAMEMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMC_BETAMON_NAME, DMC_BETAMON_ID, DMC_BETAMON_FQID, DMC_BETAMON_FQNAME, DMC_BETAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMC_BIRDRAMON_NAME, DMC_BIRDRAMON_ID, DMC_BIRDRAMON_FQID, DMC_BIRDRAMON_FQNAME, DMC_BIRDRAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMC_BLITZ_GREYMON_NAME, DMC_BLITZ_GREYMON_ID, DMC_BLITZ_GREYMON_FQID, DMC_BLITZ_GREYMON_FQNAME, DMC_BLITZ_GREYMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMC_BOTAMON_NAME, DMC_BOTAMON_ID, DMC_BOTAMON_FQID, DMC_BOTAMON_FQNAME, DMC_BOTAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMC_CENTALMON_NAME, DMC_CENTALMON_ID, DMC_CENTALMON_FQID, DMC_CENTALMON_FQNAME, DMC_CENTALMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMC_COCKATRIMON_NAME, DMC_COCKATRIMON_ID, DMC_COCKATRIMON_FQID, DMC_COCKATRIMON_FQNAME, DMC_COCKATRIMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMC_COELAMON_NAME, DMC_COELAMON_ID, DMC_COELAMON_FQID, DMC_COELAMON_FQNAME, DMC_COELAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMC_CORONAMON_NAME, DMC_CORONAMON_ID, DMC_CORONAMON_FQID, DMC_CORONAMON_FQNAME, DMC_CORONAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMC_CRES_GARURUMON_NAME, DMC_CRES_GARURUMON_ID, DMC_CRES_GARURUMON_FQID, DMC_CRES_GARURUMON_FQNAME, DMC_CRES_GARURUMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMC_CYCLOMON_NAME, DMC_CYCLOMON_ID, DMC_CYCLOMON_FQID, DMC_CYCLOMON_FQNAME, DMC_CYCLOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMC_DARK_TYRANOMON_NAME, DMC_DARK_TYRANOMON_ID, DMC_DARK_TYRANOMON_FQID, DMC_DARK_TYRANOMON_FQNAME, DMC_DARK_TYRANOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMC_DELTAMON_NAME, DMC_DELTAMON_ID, DMC_DELTAMON_FQID, DMC_DELTAMON_FQNAME, DMC_DELTAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMC_DEVIDRAMON_NAME, DMC_DEVIDRAMON_ID, DMC_DEVIDRAMON_FQID, DMC_DEVIDRAMON_FQNAME, DMC_DEVIDRAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMC_DEVIMON_NAME, DMC_DEVIMON_ID, DMC_DEVIMON_FQID, DMC_DEVIMON_FQNAME, DMC_DEVIMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMC_DIGITAMAMON_NAME, DMC_DIGITAMAMON_ID, DMC_DIGITAMAMON_FQID, DMC_DIGITAMAMON_FQNAME, DMC_DIGITAMAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMC_DRIMOGEMON_NAME, DMC_DRIMOGEMON_ID, DMC_DRIMOGEMON_FQID, DMC_DRIMOGEMON_FQNAME, DMC_DRIMOGEMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMC_ELECMON_NAME, DMC_ELECMON_ID, DMC_ELECMON_FQID, DMC_ELECMON_FQNAME, DMC_ELECMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMC_ETEMON_NAME, DMC_ETEMON_ID, DMC_ETEMON_FQID, DMC_ETEMON_FQNAME, DMC_ETEMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMC_EX_TYRANOMON_NAME, DMC_EX_TYRANOMON_ID, DMC_EX_TYRANOMON_FQID, DMC_EX_TYRANOMON_FQNAME, DMC_EX_TYRANOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMC_FLYMON_NAME, DMC_FLYMON_ID, DMC_FLYMON_FQID, DMC_FLYMON_FQNAME, DMC_FLYMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMC_GABUMON_NAME, DMC_GABUMON_ID, DMC_GABUMON_FQID, DMC_GABUMON_FQNAME, DMC_GABUMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMC_GARURUMON_NAME, DMC_GARURUMON_ID, DMC_GARURUMON_FQID, DMC_GARURUMON_FQNAME, DMC_GARURUMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMC_GAZIMON_NAME, DMC_GAZIMON_ID, DMC_GAZIMON_FQID, DMC_GAZIMON_FQNAME, DMC_GAZIMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMC_GIROMON_NAME, DMC_GIROMON_ID, DMC_GIROMON_FQID, DMC_GIROMON_FQNAME, DMC_GIROMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMC_GIZAMON_NAME, DMC_GIZAMON_ID, DMC_GIZAMON_FQID, DMC_GIZAMON_FQNAME, DMC_GIZAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMC_GREYMON_NAME, DMC_GREYMON_ID, DMC_GREYMON_FQID, DMC_GREYMON_FQNAME, DMC_GREYMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMC_HI_ANDROMON_NAME, DMC_HI_ANDROMON_ID, DMC_HI_ANDROMON_FQID, DMC_HI_ANDROMON_FQNAME, DMC_HI_ANDROMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMC_KABUTERIMON_NAME, DMC_KABUTERIMON_ID, DMC_KABUTERIMON_FQID, DMC_KABUTERIMON_FQNAME, DMC_KABUTERIMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMC_KOROMON_NAME, DMC_KOROMON_ID, DMC_KOROMON_FQID, DMC_KOROMON_FQNAME, DMC_KOROMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMC_KUNEMON_NAME, DMC_KUNEMON_ID, DMC_KUNEMON_FQID, DMC_KUNEMON_FQNAME, DMC_KUNEMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMC_KUWAGAMON_NAME, DMC_KUWAGAMON_ID, DMC_KUWAGAMON_FQID, DMC_KUWAGAMON_FQNAME, DMC_KUWAGAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMC_LEOMON_NAME, DMC_LEOMON_ID, DMC_LEOMON_FQID, DMC_LEOMON_FQNAME, DMC_LEOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMC_MAMEMON_NAME, DMC_MAMEMON_ID, DMC_MAMEMON_FQID, DMC_MAMEMON_FQNAME, DMC_MAMEMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMC_MEGADRAMON_NAME, DMC_MEGADRAMON_ID, DMC_MEGADRAMON_FQID, DMC_MEGADRAMON_FQNAME, DMC_MEGADRAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMC_MERAMON_NAME, DMC_MERAMON_ID, DMC_MERAMON_FQID, DMC_MERAMON_FQNAME, DMC_MERAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMC_METAL_GARURUMON_NAME, DMC_METAL_GARURUMON_ID, DMC_METAL_GARURUMON_FQID, DMC_METAL_GARURUMON_FQNAME, DMC_METAL_GARURUMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMC_METAL_GREYMON_NAME, DMC_METAL_GREYMON_ID, DMC_METAL_GREYMON_FQID, DMC_METAL_GREYMON_FQNAME, DMC_METAL_GREYMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMC_METAL_GREYMON_VIRUS_NAME, DMC_METAL_GREYMON_VIRUS_ID, DMC_METAL_GREYMON_VIRUS_FQID, DMC_METAL_GREYMON_VIRUS_FQNAME, DMC_METAL_GREYMON_VIRUS_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMC_METAL_MAMEMON_NAME, DMC_METAL_MAMEMON_ID, DMC_METAL_MAMEMON_FQID, DMC_METAL_MAMEMON_FQNAME, DMC_METAL_MAMEMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMC_METAL_TYRANOMON_NAME, DMC_METAL_TYRANOMON_ID, DMC_METAL_TYRANOMON_FQID, DMC_METAL_TYRANOMON_FQNAME, DMC_METAL_TYRANOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMC_MOJYMON_NAME, DMC_MOJYMON_ID, DMC_MOJYMON_FQID, DMC_MOJYMON_FQNAME, DMC_MOJYMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMC_MONOCHROMON_NAME, DMC_MONOCHROMON_ID, DMC_MONOCHROMON_FQID, DMC_MONOCHROMON_FQNAME, DMC_MONOCHROMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMC_MOZAEMON_NAME, DMC_MOZAEMON_ID, DMC_MOZAEMON_FQID, DMC_MOZAEMON_FQNAME, DMC_MOZAEMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMC_MUGENDRAMON_NAME, DMC_MUGENDRAMON_ID, DMC_MUGENDRAMON_FQID, DMC_MUGENDRAMON_FQNAME, DMC_MUGENDRAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMC_NANIMON_NAME, DMC_NANIMON_ID, DMC_NANIMON_FQID, DMC_NANIMON_FQNAME, DMC_NANIMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMC_NANOMON_NAME, DMC_NANOMON_ID, DMC_NANOMON_FQID, DMC_NANOMON_FQNAME, DMC_NANOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMC_NUMEMON_NAME, DMC_NUMEMON_ID, DMC_NUMEMON_FQID, DMC_NUMEMON_FQNAME, DMC_NUMEMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMC_OMEGAMON_ALTER_S_NAME, DMC_OMEGAMON_ALTER_S_ID, DMC_OMEGAMON_ALTER_S_FQID, DMC_OMEGAMON_ALTER_S_FQNAME, DMC_OMEGAMON_ALTER_S_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMC_OMEGAMON_NAME, DMC_OMEGAMON_ID, DMC_OMEGAMON_FQID, DMC_OMEGAMON_FQNAME, DMC_OMEGAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMC_ORGEMON_NAME, DMC_ORGEMON_ID, DMC_ORGEMON_FQID, DMC_ORGEMON_FQNAME, DMC_ORGEMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMC_PAGUMON_NAME, DMC_PAGUMON_ID, DMC_PAGUMON_FQID, DMC_PAGUMON_FQNAME, DMC_PAGUMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMC_PALMON_NAME, DMC_PALMON_ID, DMC_PALMON_FQID, DMC_PALMON_FQNAME, DMC_PALMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMC_PATAMON_NAME, DMC_PATAMON_ID, DMC_PATAMON_FQID, DMC_PATAMON_FQNAME, DMC_PATAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMC_PETITMON_NAME, DMC_PETITMON_ID, DMC_PETITMON_FQID, DMC_PETITMON_FQNAME, DMC_PETITMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMC_PICCOLOMON_NAME, DMC_PICCOLOMON_ID, DMC_PICCOLOMON_FQID, DMC_PICCOLOMON_FQNAME, DMC_PICCOLOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMC_PIYOMON_NAME, DMC_PIYOMON_ID, DMC_PIYOMON_FQID, DMC_PIYOMON_FQNAME, DMC_PIYOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMC_POYOMON_NAME, DMC_POYOMON_ID, DMC_POYOMON_FQID, DMC_POYOMON_FQNAME, DMC_POYOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMC_PUNIMON_NAME, DMC_PUNIMON_ID, DMC_PUNIMON_FQID, DMC_PUNIMON_FQNAME, DMC_PUNIMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMC_RAIDENMON_NAME, DMC_RAIDENMON_ID, DMC_RAIDENMON_FQID, DMC_RAIDENMON_FQNAME, DMC_RAIDENMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMC_RAREMON_NAME, DMC_RAREMON_ID, DMC_RAREMON_FQID, DMC_RAREMON_FQNAME, DMC_RAREMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMC_RUST_TYRANOMON_NAME, DMC_RUST_TYRANOMON_ID, DMC_RUST_TYRANOMON_FQID, DMC_RUST_TYRANOMON_FQNAME, DMC_RUST_TYRANOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMC_SCUMON_NAME, DMC_SCUMON_ID, DMC_SCUMON_FQID, DMC_SCUMON_FQNAME, DMC_SCUMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMC_SEADRAMON_NAME, DMC_SEADRAMON_ID, DMC_SEADRAMON_FQID, DMC_SEADRAMON_FQNAME, DMC_SEADRAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMC_SHELLMON_NAME, DMC_SHELLMON_ID, DMC_SHELLMON_FQID, DMC_SHELLMON_FQNAME, DMC_SHELLMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMC_SHIN_MONZAEMON_NAME, DMC_SHIN_MONZAEMON_ID, DMC_SHIN_MONZAEMON_FQID, DMC_SHIN_MONZAEMON_FQNAME, DMC_SHIN_MONZAEMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMC_SKULL_GREYMON_NAME, DMC_SKULL_GREYMON_ID, DMC_SKULL_GREYMON_FQID, DMC_SKULL_GREYMON_FQNAME, DMC_SKULL_GREYMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMC_SKULL_MAMMON_NAME, DMC_SKULL_MAMMON_ID, DMC_SKULL_MAMMON_FQID, DMC_SKULL_MAMMON_FQNAME, DMC_SKULL_MAMMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMC_TANEMON_NAME, DMC_TANEMON_ID, DMC_TANEMON_FQID, DMC_TANEMON_FQNAME, DMC_TANEMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMC_TITAMON_NAME, DMC_TITAMON_ID, DMC_TITAMON_FQID, DMC_TITAMON_FQNAME, DMC_TITAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMC_TOKOMON_NAME, DMC_TOKOMON_ID, DMC_TOKOMON_FQID, DMC_TOKOMON_FQNAME, DMC_TOKOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMC_TSUNOMON_NAME, DMC_TSUNOMON_ID, DMC_TSUNOMON_FQID, DMC_TSUNOMON_FQNAME, DMC_TSUNOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMC_TUSKMON_NAME, DMC_TUSKMON_ID, DMC_TUSKMON_FQID, DMC_TUSKMON_FQNAME, DMC_TUSKMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMC_TYRANOMON_NAME, DMC_TYRANOMON_ID, DMC_TYRANOMON_FQID, DMC_TYRANOMON_FQNAME, DMC_TYRANOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMC_UNIMON_NAME, DMC_UNIMON_ID, DMC_UNIMON_FQID, DMC_UNIMON_FQNAME, DMC_UNIMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMC_VADEMON_NAME, DMC_VADEMON_ID, DMC_VADEMON_FQID, DMC_VADEMON_FQNAME, DMC_VADEMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMC_VEGIMON_NAME, DMC_VEGIMON_ID, DMC_VEGIMON_FQID, DMC_VEGIMON_FQNAME, DMC_VEGIMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMC_WAR_GREYMON_NAME, DMC_WAR_GREYMON_ID, DMC_WAR_GREYMON_FQID, DMC_WAR_GREYMON_FQNAME, DMC_WAR_GREYMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMC_WERE_GARURUMON_NAME, DMC_WERE_GARURUMON_ID, DMC_WERE_GARURUMON_FQID, DMC_WERE_GARURUMON_FQNAME, DMC_WERE_GARURUMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMC_WHAMON_NAME, DMC_WHAMON_ID, DMC_WHAMON_FQID, DMC_WHAMON_FQNAME, DMC_WHAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMC_YUKIDARUMON_NAME, DMC_YUKIDARUMON_ID, DMC_YUKIDARUMON_FQID, DMC_YUKIDARUMON_FQNAME, DMC_YUKIDARUMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMC_YURAMON_NAME, DMC_YURAMON_ID, DMC_YURAMON_FQID, DMC_YURAMON_FQNAME, DMC_YURAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMC_ZURUMON_NAME, DMC_ZURUMON_ID, DMC_ZURUMON_FQID, DMC_ZURUMON_FQNAME, DMC_ZURUMON_ANIM_INDEX, config::config_animation_dm_set_t::dmc, config::config_animation_sprite_sheet_layout_t::Dm },
    };

    config_animation_entry_t get_config_animation_name_dmc(size_t index) {
        return dmc_animation_table[index];
    }

    void config_parse_animation_name_dmc(config::config_t& config, const char *value) {
        for (const auto& entry : dmc_animation_table) {
            if (strcmp(value, entry.name) == 0 ||
                strcmp(value, entry.id) == 0 ||
                strcmp(value, entry.fqid) == 0 ||
                strcmp(value, entry.fqname) == 0) {
                config.animation_index = entry.anim_index;
                config.animation_dm_set = entry.set;
                config.animation_sprite_sheet_layout = entry.layout;
                break;
            }
        }
    }
}

