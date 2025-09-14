#include "embedded_assets/embedded_image.h"
#include "embedded_assets/dm/dm.hpp"
#include "dm_config_parse_animation_name.h"

namespace bongocat::assets {
    static const config_animation_entry_t dm_animation_table[] = {
        { DM_AGUMON_NAME, DM_AGUMON_ID, DM_AGUMON_FQID, DM_AGUMON_FQNAME, DM_AGUMON_ANIM_INDEX, config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },
        { DM_AIRDRAMON_NAME, DM_AIRDRAMON_ID, DM_AIRDRAMON_FQID, DM_AIRDRAMON_FQNAME, DM_AIRDRAMON_ANIM_INDEX, config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },
        { DM_ANDROMON_NAME, DM_ANDROMON_ID, DM_ANDROMON_FQID, DM_ANDROMON_FQNAME, DM_ANDROMON_ANIM_INDEX, config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },
        { DM_ANGEMON_NAME, DM_ANGEMON_ID, DM_ANGEMON_FQID, DM_ANGEMON_FQNAME, DM_ANGEMON_ANIM_INDEX, config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },
        { DM_BAKEMON_NAME, DM_BAKEMON_ID, DM_BAKEMON_FQID, DM_BAKEMON_FQNAME, DM_BAKEMON_ANIM_INDEX, config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },
        { DM_BETAMON_NAME, DM_BETAMON_ID, DM_BETAMON_FQID, DM_BETAMON_FQNAME, DM_BETAMON_ANIM_INDEX, config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },
        { DM_BIRDRAMON_NAME, DM_BIRDRAMON_ID, DM_BIRDRAMON_FQID, DM_BIRDRAMON_FQNAME, DM_BIRDRAMON_ANIM_INDEX, config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },
        { DM_BOTAMON_NAME, DM_BOTAMON_ID, DM_BOTAMON_FQID, DM_BOTAMON_FQNAME, DM_BOTAMON_ANIM_INDEX, config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },
        { DM_CENTALMON_NAME, DM_CENTALMON_ID, DM_CENTALMON_FQID, DM_CENTALMON_FQNAME, DM_CENTALMON_ANIM_INDEX, config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },
        { DM_COCKATRIMON_NAME, DM_COCKATRIMON_ID, DM_COCKATRIMON_FQID, DM_COCKATRIMON_FQNAME, DM_COCKATRIMON_ANIM_INDEX, config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },
        { DM_COELAMON_NAME, DM_COELAMON_ID, DM_COELAMON_FQID, DM_COELAMON_FQNAME, DM_COELAMON_ANIM_INDEX, config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },
        { DM_CORONAMON_NAME, DM_CORONAMON_ID, DM_CORONAMON_FQID, DM_CORONAMON_FQNAME, DM_CORONAMON_ANIM_INDEX, config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },
        { DM_CYCLOMON_NAME, DM_CYCLOMON_ID, DM_CYCLOMON_FQID, DM_CYCLOMON_FQNAME, DM_CYCLOMON_ANIM_INDEX, config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },
        { DM_DARK_TYRANOMON_NAME, DM_DARK_TYRANOMON_ID, DM_DARK_TYRANOMON_FQID, DM_DARK_TYRANOMON_FQNAME, DM_DARK_TYRANOMON_ANIM_INDEX, config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },
        { DM_DELTAMON_NAME, DM_DELTAMON_ID, DM_DELTAMON_FQID, DM_DELTAMON_FQNAME, DM_DELTAMON_ANIM_INDEX, config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },
        { DM_DEVIDRAMON_NAME, DM_DEVIDRAMON_ID, DM_DEVIDRAMON_FQID, DM_DEVIDRAMON_FQNAME, DM_DEVIDRAMON_ANIM_INDEX, config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },
        { DM_DEVIMON_NAME, DM_DEVIMON_ID, DM_DEVIMON_FQID, DM_DEVIMON_FQNAME, DM_DEVIMON_ANIM_INDEX, config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },
        { DM_DIGITAMAMON_NAME, DM_DIGITAMAMON_ID, DM_DIGITAMAMON_FQID, DM_DIGITAMAMON_FQNAME, DM_DIGITAMAMON_ANIM_INDEX, config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },
        { DM_DRIMOGEMON_NAME, DM_DRIMOGEMON_ID, DM_DRIMOGEMON_FQID, DM_DRIMOGEMON_FQNAME, DM_DRIMOGEMON_ANIM_INDEX, config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },
        { DM_ELECMON_NAME, DM_ELECMON_ID, DM_ELECMON_FQID, DM_ELECMON_FQNAME, DM_ELECMON_ANIM_INDEX, config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },
        { DM_ETEMON_NAME, DM_ETEMON_ID, DM_ETEMON_FQID, DM_ETEMON_FQNAME, DM_ETEMON_ANIM_INDEX, config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },
        { DM_EX_TYRANOMON_NAME, DM_EX_TYRANOMON_ID, DM_EX_TYRANOMON_FQID, DM_EX_TYRANOMON_FQNAME, DM_EX_TYRANOMON_ANIM_INDEX, config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },
        { DM_FLYMON_NAME, DM_FLYMON_ID, DM_FLYMON_FQID, DM_FLYMON_FQNAME, DM_FLYMON_ANIM_INDEX, config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },
        { DM_GABUMON_NAME, DM_GABUMON_ID, DM_GABUMON_FQID, DM_GABUMON_FQNAME, DM_GABUMON_ANIM_INDEX, config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },
        { DM_GARURUMON_NAME, DM_GARURUMON_ID, DM_GARURUMON_FQID, DM_GARURUMON_FQNAME, DM_GARURUMON_ANIM_INDEX, config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },
        { DM_GAZIMON_NAME, DM_GAZIMON_ID, DM_GAZIMON_FQID, DM_GAZIMON_FQNAME, DM_GAZIMON_ANIM_INDEX, config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },
        { DM_GIROMON_NAME, DM_GIROMON_ID, DM_GIROMON_FQID, DM_GIROMON_FQNAME, DM_GIROMON_ANIM_INDEX, config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },
        { DM_GIZAMON_NAME, DM_GIZAMON_ID, DM_GIZAMON_FQID, DM_GIZAMON_FQNAME, DM_GIZAMON_ANIM_INDEX, config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },
        { DM_GREYMON_NAME, DM_GREYMON_ID, DM_GREYMON_FQID, DM_GREYMON_FQNAME, DM_GREYMON_ANIM_INDEX, config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },
        { DM_KABUTERIMON_NAME, DM_KABUTERIMON_ID, DM_KABUTERIMON_FQID, DM_KABUTERIMON_FQNAME, DM_KABUTERIMON_ANIM_INDEX, config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },
        { DM_KOROMON_NAME, DM_KOROMON_ID, DM_KOROMON_FQID, DM_KOROMON_FQNAME, DM_KOROMON_ANIM_INDEX, config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },
        { DM_KUNEMON_NAME, DM_KUNEMON_ID, DM_KUNEMON_FQID, DM_KUNEMON_FQNAME, DM_KUNEMON_ANIM_INDEX, config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },
        { DM_KUWAGAMON_NAME, DM_KUWAGAMON_ID, DM_KUWAGAMON_FQID, DM_KUWAGAMON_FQNAME, DM_KUWAGAMON_ANIM_INDEX, config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },
        { DM_LEOMON_NAME, DM_LEOMON_ID, DM_LEOMON_FQID, DM_LEOMON_FQNAME, DM_LEOMON_ANIM_INDEX, config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },
        { DM_MAMEMON_NAME, DM_MAMEMON_ID, DM_MAMEMON_FQID, DM_MAMEMON_FQNAME, DM_MAMEMON_ANIM_INDEX, config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },
        { DM_MEGADRAMON_NAME, DM_MEGADRAMON_ID, DM_MEGADRAMON_FQID, DM_MEGADRAMON_FQNAME, DM_MEGADRAMON_ANIM_INDEX, config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },
        { DM_MERAMON_NAME, DM_MERAMON_ID, DM_MERAMON_FQID, DM_MERAMON_FQNAME, DM_MERAMON_ANIM_INDEX, config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },
        { DM_METAL_GREYMON_NAME, DM_METAL_GREYMON_ID, DM_METAL_GREYMON_FQID, DM_METAL_GREYMON_FQNAME, DM_METAL_GREYMON_ANIM_INDEX, config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },
        { DM_METAL_MAMEMON_NAME, DM_METAL_MAMEMON_ID, DM_METAL_MAMEMON_FQID, DM_METAL_MAMEMON_FQNAME, DM_METAL_MAMEMON_ANIM_INDEX, config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },
        { DM_METAL_TYRANOMON_NAME, DM_METAL_TYRANOMON_ID, DM_METAL_TYRANOMON_FQID, DM_METAL_TYRANOMON_FQNAME, DM_METAL_TYRANOMON_ANIM_INDEX, config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },
        { DM_MOJYAMON_NAME, DM_MOJYAMON_ID, DM_MOJYAMON_FQID, DM_MOJYAMON_FQNAME, DM_MOJYAMON_ANIM_INDEX, config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },
        { DM_MONOCHROMON_NAME, DM_MONOCHROMON_ID, DM_MONOCHROMON_FQID, DM_MONOCHROMON_FQNAME, DM_MONOCHROMON_ANIM_INDEX, config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },
        { DM_MONZAEMON_NAME, DM_MONZAEMON_ID, DM_MONZAEMON_FQID, DM_MONZAEMON_FQNAME, DM_MONZAEMON_ANIM_INDEX, config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },
        { DM_NANIMON_NAME, DM_NANIMON_ID, DM_NANIMON_FQID, DM_NANIMON_FQNAME, DM_NANIMON_ANIM_INDEX, config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },
        { DM_NANOMON_NAME, DM_NANOMON_ID, DM_NANOMON_FQID, DM_NANOMON_FQNAME, DM_NANOMON_ANIM_INDEX, config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },
        { DM_NUMEMON_NAME, DM_NUMEMON_ID, DM_NUMEMON_FQID, DM_NUMEMON_FQNAME, DM_NUMEMON_ANIM_INDEX, config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },
        { DM_OGREMON_NAME, DM_OGREMON_ID, DM_OGREMON_FQID, DM_OGREMON_FQNAME, DM_OGREMON_ANIM_INDEX, config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },
        { DM_PAGUMON_NAME, DM_PAGUMON_ID, DM_PAGUMON_FQID, DM_PAGUMON_FQNAME, DM_PAGUMON_ANIM_INDEX, config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },
        { DM_PALMON_NAME, DM_PALMON_ID, DM_PALMON_FQID, DM_PALMON_FQNAME, DM_PALMON_ANIM_INDEX, config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },
        { DM_PATAMON_NAME, DM_PATAMON_ID, DM_PATAMON_FQID, DM_PATAMON_FQNAME, DM_PATAMON_ANIM_INDEX, config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },
        { DM_PICCOLOMON_NAME, DM_PICCOLOMON_ID, DM_PICCOLOMON_FQID, DM_PICCOLOMON_FQNAME, DM_PICCOLOMON_ANIM_INDEX, config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },
        { DM_PIYOMON_NAME, DM_PIYOMON_ID, DM_PIYOMON_FQID, DM_PIYOMON_FQNAME, DM_PIYOMON_ANIM_INDEX, config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },
        { DM_POYOMON_NAME, DM_POYOMON_ID, DM_POYOMON_FQID, DM_POYOMON_FQNAME, DM_POYOMON_ANIM_INDEX, config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },
        { DM_PUNIMON_NAME, DM_PUNIMON_ID, DM_PUNIMON_FQID, DM_PUNIMON_FQNAME, DM_PUNIMON_ANIM_INDEX, config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },
        { DM_RAREMON_NAME, DM_RAREMON_ID, DM_RAREMON_FQID, DM_RAREMON_FQNAME, DM_RAREMON_ANIM_INDEX, config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },
        { DM_SCUMON_NAME, DM_SCUMON_ID, DM_SCUMON_FQID, DM_SCUMON_FQNAME, DM_SCUMON_ANIM_INDEX, config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },
        { DM_SEADRAMON_NAME, DM_SEADRAMON_ID, DM_SEADRAMON_FQID, DM_SEADRAMON_FQNAME, DM_SEADRAMON_ANIM_INDEX, config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },
        { DM_SHELLMON_NAME, DM_SHELLMON_ID, DM_SHELLMON_FQID, DM_SHELLMON_FQNAME, DM_SHELLMON_ANIM_INDEX, config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },
        { DM_SKULL_GREYMON_NAME, DM_SKULL_GREYMON_ID, DM_SKULL_GREYMON_FQID, DM_SKULL_GREYMON_FQNAME, DM_SKULL_GREYMON_ANIM_INDEX, config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },
        { DM_TANEMON_NAME, DM_TANEMON_ID, DM_TANEMON_FQID, DM_TANEMON_FQNAME, DM_TANEMON_ANIM_INDEX, config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },
        { DM_TOKOMON_NAME, DM_TOKOMON_ID, DM_TOKOMON_FQID, DM_TOKOMON_FQNAME, DM_TOKOMON_ANIM_INDEX, config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },
        { DM_TUNOMON_NAME, DM_TUNOMON_ID, DM_TUNOMON_FQID, DM_TUNOMON_FQNAME, DM_TUNOMON_ANIM_INDEX, config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },
        { DM_TUSKMON_NAME, DM_TUSKMON_ID, DM_TUSKMON_FQID, DM_TUSKMON_FQNAME, DM_TUSKMON_ANIM_INDEX, config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },
        { DM_TYRANOMON_NAME, DM_TYRANOMON_ID, DM_TYRANOMON_FQID, DM_TYRANOMON_FQNAME, DM_TYRANOMON_ANIM_INDEX, config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },
        { DM_UNIMON_NAME, DM_UNIMON_ID, DM_UNIMON_FQID, DM_UNIMON_FQNAME, DM_UNIMON_ANIM_INDEX, config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },
        { DM_VADEMON_NAME, DM_VADEMON_ID, DM_VADEMON_FQID, DM_VADEMON_FQNAME, DM_VADEMON_ANIM_INDEX, config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },
        { DM_VEGIMON_NAME, DM_VEGIMON_ID, DM_VEGIMON_FQID, DM_VEGIMON_FQNAME, DM_VEGIMON_ANIM_INDEX, config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },
        { DM_WHAMON_NAME, DM_WHAMON_ID, DM_WHAMON_FQID, DM_WHAMON_FQNAME, DM_WHAMON_ANIM_INDEX, config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },
        { DM_YUKIDARUMON_NAME, DM_YUKIDARUMON_ID, DM_YUKIDARUMON_FQID, DM_YUKIDARUMON_FQNAME, DM_YUKIDARUMON_ANIM_INDEX, config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },
        { DM_YURAMON_NAME, DM_YURAMON_ID, DM_YURAMON_FQID, DM_YURAMON_FQNAME, DM_YURAMON_ANIM_INDEX, config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },
    };

    config_animation_entry_t get_config_animation_name_dm(size_t index) {
        return dm_animation_table[index];
    }

    void config_parse_animation_name_dm(config::config_t& config, const char *value) {
        for (const auto& entry : dm_animation_table) {
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

