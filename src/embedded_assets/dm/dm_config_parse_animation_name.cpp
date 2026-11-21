#include "embedded_assets/embedded_image.h"
#include "embedded_assets/dm/dm.hpp"
#include "dm_config_parse_animation_name.h"
#include "utils/memory.h"
#include <cstdint>
#include "utils/system_memory.h"

namespace bongocat::assets {
    struct dm_animation_table_entry_t {
        // offsets into DM_STRINGS
        uint32_t name;
        uint32_t id;
        uint32_t fqid;
        uint32_t fqname;
        int32_t anim_index;
        config::config_animation_dm_set_t set;
        config::config_animation_sprite_sheet_layout_t layout;
    };
    static constexpr dm_animation_table_entry_t dm_animation_table[] CONFIG_LOCAL_STRING_SECTION = {
        { DM_AGUMON_NAME_OFF, DM_AGUMON_ID_OFF, DM_AGUMON_FQID_OFF, DM_AGUMON_FQNAME_OFF, DM_AGUMON_ANIM_INDEX, config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },  // Agumon
        { DM_AIRDRAMON_NAME_OFF, DM_AIRDRAMON_ID_OFF, DM_AIRDRAMON_FQID_OFF, DM_AIRDRAMON_FQNAME_OFF, DM_AIRDRAMON_ANIM_INDEX, config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },  // Airdramon
        { DM_ANDROMON_NAME_OFF, DM_ANDROMON_ID_OFF, DM_ANDROMON_FQID_OFF, DM_ANDROMON_FQNAME_OFF, DM_ANDROMON_ANIM_INDEX, config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },  // Andromon
        { DM_ANGEMON_NAME_OFF, DM_ANGEMON_ID_OFF, DM_ANGEMON_FQID_OFF, DM_ANGEMON_FQNAME_OFF, DM_ANGEMON_ANIM_INDEX, config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },  // Angemon
        { DM_ATLUR_KABUTERIMON_NAME_OFF, DM_ATLUR_KABUTERIMON_ID_OFF, DM_ATLUR_KABUTERIMON_FQID_OFF, DM_ATLUR_KABUTERIMON_FQNAME_OFF, DM_ATLUR_KABUTERIMON_ANIM_INDEX, config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },  // Atlur Kabuterimon
        { DM_BAKEMON_NAME_OFF, DM_BAKEMON_ID_OFF, DM_BAKEMON_FQID_OFF, DM_BAKEMON_FQNAME_OFF, DM_BAKEMON_ANIM_INDEX, config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },  // Bakemon
        { DM_BETAMON_NAME_OFF, DM_BETAMON_ID_OFF, DM_BETAMON_FQID_OFF, DM_BETAMON_FQNAME_OFF, DM_BETAMON_ANIM_INDEX, config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },  // Betamon
        { DM_BIRDRAMON_NAME_OFF, DM_BIRDRAMON_ID_OFF, DM_BIRDRAMON_FQID_OFF, DM_BIRDRAMON_FQNAME_OFF, DM_BIRDRAMON_ANIM_INDEX, config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },  // Birdramon
        { DM_BOTAMON_NAME_OFF, DM_BOTAMON_ID_OFF, DM_BOTAMON_FQID_OFF, DM_BOTAMON_FQNAME_OFF, DM_BOTAMON_ANIM_INDEX, config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },  // Botamon
        { DM_BUBBMON_NAME_OFF, DM_BUBBMON_ID_OFF, DM_BUBBMON_FQID_OFF, DM_BUBBMON_FQNAME_OFF, DM_BUBBMON_ANIM_INDEX, config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },  // Bubbmon
        { DM_CENTALMON_NAME_OFF, DM_CENTALMON_ID_OFF, DM_CENTALMON_FQID_OFF, DM_CENTALMON_FQNAME_OFF, DM_CENTALMON_ANIM_INDEX, config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },  // Centalmon
        { DM_COCKATRIMON_NAME_OFF, DM_COCKATRIMON_ID_OFF, DM_COCKATRIMON_FQID_OFF, DM_COCKATRIMON_FQNAME_OFF, DM_COCKATRIMON_ANIM_INDEX, config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },  // Cockatrimon
        { DM_COELAMON_NAME_OFF, DM_COELAMON_ID_OFF, DM_COELAMON_FQID_OFF, DM_COELAMON_FQNAME_OFF, DM_COELAMON_ANIM_INDEX, config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },  // Coelamon
        { DM_CYCLOMON_NAME_OFF, DM_CYCLOMON_ID_OFF, DM_CYCLOMON_FQID_OFF, DM_CYCLOMON_FQNAME_OFF, DM_CYCLOMON_ANIM_INDEX, config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },  // Cyclomon
        { DM_DARK_TYRANOMON_NAME_OFF, DM_DARK_TYRANOMON_ID_OFF, DM_DARK_TYRANOMON_FQID_OFF, DM_DARK_TYRANOMON_FQNAME_OFF, DM_DARK_TYRANOMON_ANIM_INDEX, config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },  // Dark Tyranomon
        { DM_DELTAMON_NAME_OFF, DM_DELTAMON_ID_OFF, DM_DELTAMON_FQID_OFF, DM_DELTAMON_FQNAME_OFF, DM_DELTAMON_ANIM_INDEX, config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },  // Deltamon
        { DM_DEVIDRAMON_NAME_OFF, DM_DEVIDRAMON_ID_OFF, DM_DEVIDRAMON_FQID_OFF, DM_DEVIDRAMON_FQNAME_OFF, DM_DEVIDRAMON_ANIM_INDEX, config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },  // Devidramon
        { DM_DEVIMON_NAME_OFF, DM_DEVIMON_ID_OFF, DM_DEVIMON_FQID_OFF, DM_DEVIMON_FQNAME_OFF, DM_DEVIMON_ANIM_INDEX, config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },  // Devimon
        { DM_DIGITAMAMON_NAME_OFF, DM_DIGITAMAMON_ID_OFF, DM_DIGITAMAMON_FQID_OFF, DM_DIGITAMAMON_FQNAME_OFF, DM_DIGITAMAMON_ANIM_INDEX, config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },  // Digitamamon
        { DM_DRIMOGEMON_NAME_OFF, DM_DRIMOGEMON_ID_OFF, DM_DRIMOGEMON_FQID_OFF, DM_DRIMOGEMON_FQNAME_OFF, DM_DRIMOGEMON_ANIM_INDEX, config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },  // Drimogemon
        { DM_ELECMON_NAME_OFF, DM_ELECMON_ID_OFF, DM_ELECMON_FQID_OFF, DM_ELECMON_FQNAME_OFF, DM_ELECMON_ANIM_INDEX, config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },  // Elecmon
        { DM_ETEMON_NAME_OFF, DM_ETEMON_ID_OFF, DM_ETEMON_FQID_OFF, DM_ETEMON_FQNAME_OFF, DM_ETEMON_ANIM_INDEX, config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },  // Etemon
        { DM_EX_TYRANOMON_NAME_OFF, DM_EX_TYRANOMON_ID_OFF, DM_EX_TYRANOMON_FQID_OFF, DM_EX_TYRANOMON_FQNAME_OFF, DM_EX_TYRANOMON_ANIM_INDEX, config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },  // Ex-Tyranomon
        { DM_FLYMON_NAME_OFF, DM_FLYMON_ID_OFF, DM_FLYMON_FQID_OFF, DM_FLYMON_FQNAME_OFF, DM_FLYMON_ANIM_INDEX, config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },  // Flymon
        { DM_GABUMON_NAME_OFF, DM_GABUMON_ID_OFF, DM_GABUMON_FQID_OFF, DM_GABUMON_FQNAME_OFF, DM_GABUMON_ANIM_INDEX, config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },  // Gabumon
        { DM_GARURUMON_NAME_OFF, DM_GARURUMON_ID_OFF, DM_GARURUMON_FQID_OFF, DM_GARURUMON_FQNAME_OFF, DM_GARURUMON_ANIM_INDEX, config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },  // Garurumon
        { DM_GAZIMON_NAME_OFF, DM_GAZIMON_ID_OFF, DM_GAZIMON_FQID_OFF, DM_GAZIMON_FQNAME_OFF, DM_GAZIMON_ANIM_INDEX, config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },  // Gazimon
        { DM_GEKOMON_NAME_OFF, DM_GEKOMON_ID_OFF, DM_GEKOMON_FQID_OFF, DM_GEKOMON_FQNAME_OFF, DM_GEKOMON_ANIM_INDEX, config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },  // Gekomon
        { DM_GIROMON_NAME_OFF, DM_GIROMON_ID_OFF, DM_GIROMON_FQID_OFF, DM_GIROMON_FQNAME_OFF, DM_GIROMON_ANIM_INDEX, config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },  // Giromon
        { DM_GIZAMON_NAME_OFF, DM_GIZAMON_ID_OFF, DM_GIZAMON_FQID_OFF, DM_GIZAMON_FQNAME_OFF, DM_GIZAMON_ANIM_INDEX, config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },  // Gizamon
        { DM_GREYMON_NAME_OFF, DM_GREYMON_ID_OFF, DM_GREYMON_FQID_OFF, DM_GREYMON_FQNAME_OFF, DM_GREYMON_ANIM_INDEX, config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },  // Greymon
        { DM_KABUTERIMON_NAME_OFF, DM_KABUTERIMON_ID_OFF, DM_KABUTERIMON_FQID_OFF, DM_KABUTERIMON_FQNAME_OFF, DM_KABUTERIMON_ANIM_INDEX, config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },  // Kabuterimon
        { DM_KOROMON_NAME_OFF, DM_KOROMON_ID_OFF, DM_KOROMON_FQID_OFF, DM_KOROMON_FQNAME_OFF, DM_KOROMON_ANIM_INDEX, config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },  // Koromon
        { DM_KUNEMON_NAME_OFF, DM_KUNEMON_ID_OFF, DM_KUNEMON_FQID_OFF, DM_KUNEMON_FQNAME_OFF, DM_KUNEMON_ANIM_INDEX, config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },  // Kunemon
        { DM_KUWAGAMON_NAME_OFF, DM_KUWAGAMON_ID_OFF, DM_KUWAGAMON_FQID_OFF, DM_KUWAGAMON_FQNAME_OFF, DM_KUWAGAMON_ANIM_INDEX, config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },  // Kuwagamon
        { DM_LEOMON_NAME_OFF, DM_LEOMON_ID_OFF, DM_LEOMON_FQID_OFF, DM_LEOMON_FQNAME_OFF, DM_LEOMON_ANIM_INDEX, config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },  // Leomon
        { DM_MAMEMON_NAME_OFF, DM_MAMEMON_ID_OFF, DM_MAMEMON_FQID_OFF, DM_MAMEMON_FQNAME_OFF, DM_MAMEMON_ANIM_INDEX, config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },  // Mamemon
        { DM_MEGADRAMON_NAME_OFF, DM_MEGADRAMON_ID_OFF, DM_MEGADRAMON_FQID_OFF, DM_MEGADRAMON_FQNAME_OFF, DM_MEGADRAMON_ANIM_INDEX, config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },  // Megadramon
        { DM_MERAMON_NAME_OFF, DM_MERAMON_ID_OFF, DM_MERAMON_FQID_OFF, DM_MERAMON_FQNAME_OFF, DM_MERAMON_ANIM_INDEX, config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },  // Meramon
        { DM_METAL_GREYMON_NAME_OFF, DM_METAL_GREYMON_ID_OFF, DM_METAL_GREYMON_FQID_OFF, DM_METAL_GREYMON_FQNAME_OFF, DM_METAL_GREYMON_ANIM_INDEX, config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },  // Metal Greymon
        { DM_METAL_MAMEMON_NAME_OFF, DM_METAL_MAMEMON_ID_OFF, DM_METAL_MAMEMON_FQID_OFF, DM_METAL_MAMEMON_FQNAME_OFF, DM_METAL_MAMEMON_ANIM_INDEX, config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },  // Metal Mamemon
        { DM_METAL_TYRANOMON_NAME_OFF, DM_METAL_TYRANOMON_ID_OFF, DM_METAL_TYRANOMON_FQID_OFF, DM_METAL_TYRANOMON_FQNAME_OFF, DM_METAL_TYRANOMON_ANIM_INDEX, config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },  // Metal Tyranomon
        { DM_MOCHIMON_NAME_OFF, DM_MOCHIMON_ID_OFF, DM_MOCHIMON_FQID_OFF, DM_MOCHIMON_FQNAME_OFF, DM_MOCHIMON_ANIM_INDEX, config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },  // Mochimon
        { DM_MOJYAMON_NAME_OFF, DM_MOJYAMON_ID_OFF, DM_MOJYAMON_FQID_OFF, DM_MOJYAMON_FQNAME_OFF, DM_MOJYAMON_ANIM_INDEX, config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },  // Mojyamon
        { DM_MONOCHROMON_NAME_OFF, DM_MONOCHROMON_ID_OFF, DM_MONOCHROMON_FQID_OFF, DM_MONOCHROMON_FQNAME_OFF, DM_MONOCHROMON_ANIM_INDEX, config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },  // Monochromon
        { DM_MONZAEMON_NAME_OFF, DM_MONZAEMON_ID_OFF, DM_MONZAEMON_FQID_OFF, DM_MONZAEMON_FQNAME_OFF, DM_MONZAEMON_ANIM_INDEX, config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },  // Monzaemon
        { DM_MUGENDRAMON_NAME_OFF, DM_MUGENDRAMON_ID_OFF, DM_MUGENDRAMON_FQID_OFF, DM_MUGENDRAMON_FQNAME_OFF, DM_MUGENDRAMON_ANIM_INDEX, config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },  // Mugendramon
        { DM_NANIMON_NAME_OFF, DM_NANIMON_ID_OFF, DM_NANIMON_FQID_OFF, DM_NANIMON_FQNAME_OFF, DM_NANIMON_ANIM_INDEX, config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },  // Nanimon
        { DM_NANOMON_NAME_OFF, DM_NANOMON_ID_OFF, DM_NANOMON_FQID_OFF, DM_NANOMON_FQNAME_OFF, DM_NANOMON_ANIM_INDEX, config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },  // Nanomon
        { DM_NUMEMON_NAME_OFF, DM_NUMEMON_ID_OFF, DM_NUMEMON_FQID_OFF, DM_NUMEMON_FQNAME_OFF, DM_NUMEMON_ANIM_INDEX, config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },  // Numemon
        { DM_OGREMON_NAME_OFF, DM_OGREMON_ID_OFF, DM_OGREMON_FQID_OFF, DM_OGREMON_FQNAME_OFF, DM_OGREMON_ANIM_INDEX, config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },  // Ogremon
        { DM_OTAMAMON_NAME_OFF, DM_OTAMAMON_ID_OFF, DM_OTAMAMON_FQID_OFF, DM_OTAMAMON_FQNAME_OFF, DM_OTAMAMON_ANIM_INDEX, config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },  // Otamamon
        { DM_PAGUMON_NAME_OFF, DM_PAGUMON_ID_OFF, DM_PAGUMON_FQID_OFF, DM_PAGUMON_FQNAME_OFF, DM_PAGUMON_ANIM_INDEX, config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },  // Pagumon
        { DM_PALMON_NAME_OFF, DM_PALMON_ID_OFF, DM_PALMON_FQID_OFF, DM_PALMON_FQNAME_OFF, DM_PALMON_ANIM_INDEX, config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },  // Palmon
        { DM_PATAMON_NAME_OFF, DM_PATAMON_ID_OFF, DM_PATAMON_FQID_OFF, DM_PATAMON_FQNAME_OFF, DM_PATAMON_ANIM_INDEX, config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },  // Patamon
        { DM_PICCOLOMON_NAME_OFF, DM_PICCOLOMON_ID_OFF, DM_PICCOLOMON_FQID_OFF, DM_PICCOLOMON_FQNAME_OFF, DM_PICCOLOMON_ANIM_INDEX, config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },  // Piccolomon
        { DM_PIYOMON_NAME_OFF, DM_PIYOMON_ID_OFF, DM_PIYOMON_FQID_OFF, DM_PIYOMON_FQNAME_OFF, DM_PIYOMON_ANIM_INDEX, config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },  // Piyomon
        { DM_POYOMON_NAME_OFF, DM_POYOMON_ID_OFF, DM_POYOMON_FQID_OFF, DM_POYOMON_FQNAME_OFF, DM_POYOMON_ANIM_INDEX, config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },  // Poyomon
        { DM_PUNIMON_NAME_OFF, DM_PUNIMON_ID_OFF, DM_PUNIMON_FQID_OFF, DM_PUNIMON_FQNAME_OFF, DM_PUNIMON_ANIM_INDEX, config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },  // Punimon
        { DM_RAREMON_NAME_OFF, DM_RAREMON_ID_OFF, DM_RAREMON_FQID_OFF, DM_RAREMON_FQNAME_OFF, DM_RAREMON_ANIM_INDEX, config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },  // Raremon
        { DM_SCUMON_NAME_OFF, DM_SCUMON_ID_OFF, DM_SCUMON_FQID_OFF, DM_SCUMON_FQNAME_OFF, DM_SCUMON_ANIM_INDEX, config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },  // Scumon
        { DM_SEADRAMON_NAME_OFF, DM_SEADRAMON_ID_OFF, DM_SEADRAMON_FQID_OFF, DM_SEADRAMON_FQNAME_OFF, DM_SEADRAMON_ANIM_INDEX, config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },  // Seadramon
        { DM_SHELLMON_NAME_OFF, DM_SHELLMON_ID_OFF, DM_SHELLMON_FQID_OFF, DM_SHELLMON_FQNAME_OFF, DM_SHELLMON_ANIM_INDEX, config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },  // Shellmon
        { DM_SKULL_GREYMON_NAME_OFF, DM_SKULL_GREYMON_ID_OFF, DM_SKULL_GREYMON_FQID_OFF, DM_SKULL_GREYMON_FQNAME_OFF, DM_SKULL_GREYMON_ANIM_INDEX, config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },  // Skull Greymon
        { DM_STARMON_NAME_OFF, DM_STARMON_ID_OFF, DM_STARMON_FQID_OFF, DM_STARMON_FQNAME_OFF, DM_STARMON_ANIM_INDEX, config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },  // Starmon
        { DM_TANEMON_NAME_OFF, DM_TANEMON_ID_OFF, DM_TANEMON_FQID_OFF, DM_TANEMON_FQNAME_OFF, DM_TANEMON_ANIM_INDEX, config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },  // Tanemon
        { DM_TENTOMON_NAME_OFF, DM_TENTOMON_ID_OFF, DM_TENTOMON_FQID_OFF, DM_TENTOMON_FQNAME_OFF, DM_TENTOMON_ANIM_INDEX, config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },  // Tentomon
        { DM_TOKOMON_NAME_OFF, DM_TOKOMON_ID_OFF, DM_TOKOMON_FQID_OFF, DM_TOKOMON_FQNAME_OFF, DM_TOKOMON_ANIM_INDEX, config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },  // Tokomon
        { DM_TONOSAMA_GEKOMON_NAME_OFF, DM_TONOSAMA_GEKOMON_ID_OFF, DM_TONOSAMA_GEKOMON_FQID_OFF, DM_TONOSAMA_GEKOMON_FQNAME_OFF, DM_TONOSAMA_GEKOMON_ANIM_INDEX, config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },  // Tonosama Gekomon
        { DM_TORTAMON_NAME_OFF, DM_TORTAMON_ID_OFF, DM_TORTAMON_FQID_OFF, DM_TORTAMON_FQNAME_OFF, DM_TORTAMON_ANIM_INDEX, config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },  // Tortamon
        { DM_TUNOMON_NAME_OFF, DM_TUNOMON_ID_OFF, DM_TUNOMON_FQID_OFF, DM_TUNOMON_FQNAME_OFF, DM_TUNOMON_ANIM_INDEX, config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },  // Tunomon
        { DM_TUSKMON_NAME_OFF, DM_TUSKMON_ID_OFF, DM_TUSKMON_FQID_OFF, DM_TUSKMON_FQNAME_OFF, DM_TUSKMON_ANIM_INDEX, config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },  // Tuskmon
        { DM_TYRANOMON_NAME_OFF, DM_TYRANOMON_ID_OFF, DM_TYRANOMON_FQID_OFF, DM_TYRANOMON_FQNAME_OFF, DM_TYRANOMON_ANIM_INDEX, config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },  // Tyranomon
        { DM_UNIMON_NAME_OFF, DM_UNIMON_ID_OFF, DM_UNIMON_FQID_OFF, DM_UNIMON_FQNAME_OFF, DM_UNIMON_ANIM_INDEX, config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },  // Unimon
        { DM_VADEMON_NAME_OFF, DM_VADEMON_ID_OFF, DM_VADEMON_FQID_OFF, DM_VADEMON_FQNAME_OFF, DM_VADEMON_ANIM_INDEX, config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },  // Vademon
        { DM_VEGIMON_NAME_OFF, DM_VEGIMON_ID_OFF, DM_VEGIMON_FQID_OFF, DM_VEGIMON_FQNAME_OFF, DM_VEGIMON_ANIM_INDEX, config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },  // Vegimon
        { DM_WHAMON_NAME_OFF, DM_WHAMON_ID_OFF, DM_WHAMON_FQID_OFF, DM_WHAMON_FQNAME_OFF, DM_WHAMON_ANIM_INDEX, config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },  // Whamon
        { DM_YUKIDARUMON_NAME_OFF, DM_YUKIDARUMON_ID_OFF, DM_YUKIDARUMON_FQID_OFF, DM_YUKIDARUMON_FQNAME_OFF, DM_YUKIDARUMON_ANIM_INDEX, config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },  // Yukidarumon
        { DM_YURAMON_NAME_OFF, DM_YURAMON_ID_OFF, DM_YURAMON_FQID_OFF, DM_YURAMON_FQNAME_OFF, DM_YURAMON_ANIM_INDEX, config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },  // Yuramon
        { DM_ZURUMON_NAME_OFF, DM_ZURUMON_ID_OFF, DM_ZURUMON_FQID_OFF, DM_ZURUMON_FQNAME_OFF, DM_ZURUMON_ANIM_INDEX, config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },  // Zurumon
        
    };
    static_assert(LEN_ARRAY(dm_animation_table) == DM_ANIM_COUNT);

    config_animation_entry_t get_config_animation_name_dm(size_t index) {
        assert(index < DM_ANIM_COUNT);
        const auto& entry = dm_animation_table[index];
        return { DM_STRINGS + entry.name, DM_STRINGS + entry.id, DM_STRINGS + entry.fqid, DM_STRINGS + entry.fqname, entry.anim_index, entry.set, entry.layout };
    }

    int config_parse_animation_name_dm(config::config_t& config, const char *value) {
        int ret = -1;
        for (size_t i = 0;ret < 0 && i < DM_ANIM_COUNT;++i) {
            const auto& entry = dm_animation_table[i];
            if (strcmp(value, DM_STRINGS + entry.name) == 0 ||
                strcmp(value, DM_STRINGS + entry.id) == 0 ||
                strcmp(value, DM_STRINGS + entry.fqid) == 0 ||
                strcmp(value, DM_STRINGS + entry.fqname) == 0) {
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
