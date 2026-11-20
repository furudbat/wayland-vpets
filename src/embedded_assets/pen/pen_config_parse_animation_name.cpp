#include "embedded_assets/embedded_image.h"
#include "embedded_assets/pen/pen.hpp"
#include "pen_config_parse_animation_name.h"
#include "utils/memory.h"
#include <cstdint>
#include "utils/system_memory.h"

namespace bongocat::assets {
    struct pen_animation_table_entry_t {
        // offsets into PEN_STRINGS
        uint32_t name;
        uint32_t id;
        uint32_t fqid;
        uint32_t fqname;
        int32_t anim_index;
        config::config_animation_dm_set_t set;
        config::config_animation_sprite_sheet_layout_t layout;
    };
    static constexpr pen_animation_table_entry_t pen_animation_table[] CONFIG_LOCAL_STRING_SECTION = {
        { PEN_AERO_V_DRAMON_NAME_OFF, PEN_AERO_V_DRAMON_ID_OFF, PEN_AERO_V_DRAMON_FQID_OFF, PEN_AERO_V_DRAMON_FQNAME_OFF, PEN_AERO_V_DRAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },  // Aero V-dramon
        { PEN_AGUMON_NAME_OFF, PEN_AGUMON_ID_OFF, PEN_AGUMON_FQID_OFF, PEN_AGUMON_FQNAME_OFF, PEN_AGUMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },  // Agumon
        { PEN_ANDROMON_NAME_OFF, PEN_ANDROMON_ID_OFF, PEN_ANDROMON_FQID_OFF, PEN_ANDROMON_FQNAME_OFF, PEN_ANDROMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },  // Andromon
        { PEN_ANGEMON_NAME_OFF, PEN_ANGEMON_ID_OFF, PEN_ANGEMON_FQID_OFF, PEN_ANGEMON_FQNAME_OFF, PEN_ANGEMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },  // Angemon
        { PEN_ANGEWOMON_NAME_OFF, PEN_ANGEWOMON_ID_OFF, PEN_ANGEWOMON_FQID_OFF, PEN_ANGEWOMON_FQNAME_OFF, PEN_ANGEWOMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },  // Angewomon
        { PEN_ANOMALOCARIMON_NAME_OFF, PEN_ANOMALOCARIMON_ID_OFF, PEN_ANOMALOCARIMON_FQID_OFF, PEN_ANOMALOCARIMON_FQNAME_OFF, PEN_ANOMALOCARIMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },  // Anomalocarimon
        { PEN_ASURAMON_NAME_OFF, PEN_ASURAMON_ID_OFF, PEN_ASURAMON_FQID_OFF, PEN_ASURAMON_FQNAME_OFF, PEN_ASURAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },  // Asuramon
        { PEN_ATLUR_KABUTERIMON_NAME_OFF, PEN_ATLUR_KABUTERIMON_ID_OFF, PEN_ATLUR_KABUTERIMON_FQID_OFF, PEN_ATLUR_KABUTERIMON_FQNAME_OFF, PEN_ATLUR_KABUTERIMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },  // Atlur Kabuterimon
        { PEN_BAKEMON_NAME_OFF, PEN_BAKEMON_ID_OFF, PEN_BAKEMON_FQID_OFF, PEN_BAKEMON_FQNAME_OFF, PEN_BAKEMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },  // Bakemon
        { PEN_BAKUMON_NAME_OFF, PEN_BAKUMON_ID_OFF, PEN_BAKUMON_FQID_OFF, PEN_BAKUMON_FQNAME_OFF, PEN_BAKUMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },  // Bakumon
        { PEN_BIG_MAMEMON_NAME_OFF, PEN_BIG_MAMEMON_ID_OFF, PEN_BIG_MAMEMON_FQID_OFF, PEN_BIG_MAMEMON_FQNAME_OFF, PEN_BIG_MAMEMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },  // Big Mamemon
        { PEN_BIRDRAMON_NAME_OFF, PEN_BIRDRAMON_ID_OFF, PEN_BIRDRAMON_FQID_OFF, PEN_BIRDRAMON_FQNAME_OFF, PEN_BIRDRAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },  // Birdramon
        { PEN_BLOSSOMON_NAME_OFF, PEN_BLOSSOMON_ID_OFF, PEN_BLOSSOMON_FQID_OFF, PEN_BLOSSOMON_FQNAME_OFF, PEN_BLOSSOMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },  // Blossomon
        { PEN_BOLTMON_NAME_OFF, PEN_BOLTMON_ID_OFF, PEN_BOLTMON_FQID_OFF, PEN_BOLTMON_FQNAME_OFF, PEN_BOLTMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },  // Boltmon
        { PEN_BUBBMON_NAME_OFF, PEN_BUBBMON_ID_OFF, PEN_BUBBMON_FQID_OFF, PEN_BUBBMON_FQNAME_OFF, PEN_BUBBMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },  // Bubbmon
        { PEN_CANDMON_NAME_OFF, PEN_CANDMON_ID_OFF, PEN_CANDMON_FQID_OFF, PEN_CANDMON_FQNAME_OFF, PEN_CANDMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },  // Candmon
        { PEN_CAPRIMON_NAME_OFF, PEN_CAPRIMON_ID_OFF, PEN_CAPRIMON_FQID_OFF, PEN_CAPRIMON_FQNAME_OFF, PEN_CAPRIMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },  // Caprimon
        { PEN_CHOROMON_NAME_OFF, PEN_CHOROMON_ID_OFF, PEN_CHOROMON_FQID_OFF, PEN_CHOROMON_FQNAME_OFF, PEN_CHOROMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },  // Choromon
        { PEN_CLOCKMON_NAME_OFF, PEN_CLOCKMON_ID_OFF, PEN_CLOCKMON_FQID_OFF, PEN_CLOCKMON_FQNAME_OFF, PEN_CLOCKMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },  // Clockmon
        { PEN_COELAMON_NAME_OFF, PEN_COELAMON_ID_OFF, PEN_COELAMON_FQID_OFF, PEN_COELAMON_FQNAME_OFF, PEN_COELAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },  // Coelamon
        { PEN_CYBERDRAMON_NAME_OFF, PEN_CYBERDRAMON_ID_OFF, PEN_CYBERDRAMON_FQID_OFF, PEN_CYBERDRAMON_FQNAME_OFF, PEN_CYBERDRAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },  // Cyberdramon
        { PEN_DAGOMON_NAME_OFF, PEN_DAGOMON_ID_OFF, PEN_DAGOMON_FQID_OFF, PEN_DAGOMON_FQNAME_OFF, PEN_DAGOMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },  // Dagomon
        { PEN_DEATH_MERAMON_NAME_OFF, PEN_DEATH_MERAMON_ID_OFF, PEN_DEATH_MERAMON_FQID_OFF, PEN_DEATH_MERAMON_FQNAME_OFF, PEN_DEATH_MERAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },  // Death Meramon
        { PEN_DELUMON_NAME_OFF, PEN_DELUMON_ID_OFF, PEN_DELUMON_FQID_OFF, PEN_DELUMON_FQNAME_OFF, PEN_DELUMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },  // Delumon
        { PEN_DEVIMON_NAME_OFF, PEN_DEVIMON_ID_OFF, PEN_DEVIMON_FQID_OFF, PEN_DEVIMON_FQNAME_OFF, PEN_DEVIMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },  // Devimon
        { PEN_DOKUGUMON_NAME_OFF, PEN_DOKUGUMON_ID_OFF, PEN_DOKUGUMON_FQID_OFF, PEN_DOKUGUMON_FQNAME_OFF, PEN_DOKUGUMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },  // Dokugumon
        { PEN_EBIDRAMON_NAME_OFF, PEN_EBIDRAMON_ID_OFF, PEN_EBIDRAMON_FQID_OFF, PEN_EBIDRAMON_FQNAME_OFF, PEN_EBIDRAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },  // Ebidramon
        { PEN_FANTOMON_NAME_OFF, PEN_FANTOMON_ID_OFF, PEN_FANTOMON_FQID_OFF, PEN_FANTOMON_FQNAME_OFF, PEN_FANTOMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },  // Fantomon
        { PEN_FLORAMON_NAME_OFF, PEN_FLORAMON_ID_OFF, PEN_FLORAMON_FQID_OFF, PEN_FLORAMON_FQNAME_OFF, PEN_FLORAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },  // Floramon
        { PEN_GABUMON_NAME_OFF, PEN_GABUMON_ID_OFF, PEN_GABUMON_FQID_OFF, PEN_GABUMON_FQNAME_OFF, PEN_GABUMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },  // Gabumon
        { PEN_GANIMON_NAME_OFF, PEN_GANIMON_ID_OFF, PEN_GANIMON_FQID_OFF, PEN_GANIMON_FQNAME_OFF, PEN_GANIMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },  // Ganimon
        { PEN_GARUDAMON_NAME_OFF, PEN_GARUDAMON_ID_OFF, PEN_GARUDAMON_FQID_OFF, PEN_GARUDAMON_FQNAME_OFF, PEN_GARUDAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },  // Garudamon
        { PEN_GARURUMON_NAME_OFF, PEN_GARURUMON_ID_OFF, PEN_GARURUMON_FQID_OFF, PEN_GARURUMON_FQNAME_OFF, PEN_GARURUMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },  // Garurumon
        { PEN_GEKOMON_NAME_OFF, PEN_GEKOMON_ID_OFF, PEN_GEKOMON_FQID_OFF, PEN_GEKOMON_FQNAME_OFF, PEN_GEKOMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },  // Gekomon
        { PEN_GERBEMON_NAME_OFF, PEN_GERBEMON_ID_OFF, PEN_GERBEMON_FQID_OFF, PEN_GERBEMON_FQNAME_OFF, PEN_GERBEMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },  // Gerbemon
        { PEN_GESOMON_NAME_OFF, PEN_GESOMON_ID_OFF, PEN_GESOMON_FQID_OFF, PEN_GESOMON_FQNAME_OFF, PEN_GESOMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },  // Gesomon
        { PEN_GOMAMON_NAME_OFF, PEN_GOMAMON_ID_OFF, PEN_GOMAMON_FQID_OFF, PEN_GOMAMON_FQNAME_OFF, PEN_GOMAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },  // Gomamon
        { PEN_GOTTSUMON_NAME_OFF, PEN_GOTTSUMON_ID_OFF, PEN_GOTTSUMON_FQID_OFF, PEN_GOTTSUMON_FQNAME_OFF, PEN_GOTTSUMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },  // Gottsumon
        { PEN_GREYMON_NAME_OFF, PEN_GREYMON_ID_OFF, PEN_GREYMON_FQID_OFF, PEN_GREYMON_FQNAME_OFF, PEN_GREYMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },  // Greymon
        { PEN_GRIFFOMON_NAME_OFF, PEN_GRIFFOMON_ID_OFF, PEN_GRIFFOMON_FQID_OFF, PEN_GRIFFOMON_FQNAME_OFF, PEN_GRIFFOMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },  // Griffomon
        { PEN_GUARDROMON_NAME_OFF, PEN_GUARDROMON_ID_OFF, PEN_GUARDROMON_FQID_OFF, PEN_GUARDROMON_FQNAME_OFF, PEN_GUARDROMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },  // Guardromon
        { PEN_HAGURUMON_NAME_OFF, PEN_HAGURUMON_ID_OFF, PEN_HAGURUMON_FQID_OFF, PEN_HAGURUMON_FQNAME_OFF, PEN_HAGURUMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },  // Hagurumon
        { PEN_HANGYOMON_NAME_OFF, PEN_HANGYOMON_ID_OFF, PEN_HANGYOMON_FQID_OFF, PEN_HANGYOMON_FQNAME_OFF, PEN_HANGYOMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },  // Hangyomon
        { PEN_HANUMON_NAME_OFF, PEN_HANUMON_ID_OFF, PEN_HANUMON_FQID_OFF, PEN_HANUMON_FQNAME_OFF, PEN_HANUMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },  // Hanumon
        { PEN_HERAKLE_KABUTERIMON_NAME_OFF, PEN_HERAKLE_KABUTERIMON_ID_OFF, PEN_HERAKLE_KABUTERIMON_FQID_OFF, PEN_HERAKLE_KABUTERIMON_FQNAME_OFF, PEN_HERAKLE_KABUTERIMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },  // Herakle Kabuterimon
        { PEN_HOLY_ANGEMON_NAME_OFF, PEN_HOLY_ANGEMON_ID_OFF, PEN_HOLY_ANGEMON_FQID_OFF, PEN_HOLY_ANGEMON_FQNAME_OFF, PEN_HOLY_ANGEMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },  // Holy Angemon
        { PEN_HOLYDRAMON_NAME_OFF, PEN_HOLYDRAMON_ID_OFF, PEN_HOLYDRAMON_FQID_OFF, PEN_HOLYDRAMON_FQNAME_OFF, PEN_HOLYDRAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },  // Holydramon
        { PEN_HOUOUMON_NAME_OFF, PEN_HOUOUMON_ID_OFF, PEN_HOUOUMON_FQID_OFF, PEN_HOUOUMON_FQNAME_OFF, PEN_HOUOUMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },  // Hououmon
        { PEN_IGAMON_NAME_OFF, PEN_IGAMON_ID_OFF, PEN_IGAMON_FQID_OFF, PEN_IGAMON_FQNAME_OFF, PEN_IGAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },  // Igamon
        { PEN_IKKAKUMON_NAME_OFF, PEN_IKKAKUMON_ID_OFF, PEN_IKKAKUMON_FQID_OFF, PEN_IKKAKUMON_FQNAME_OFF, PEN_IKKAKUMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },  // Ikkakumon
        { PEN_JYAGAMON_NAME_OFF, PEN_JYAGAMON_ID_OFF, PEN_JYAGAMON_FQID_OFF, PEN_JYAGAMON_FQNAME_OFF, PEN_JYAGAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },  // Jyagamon
        { PEN_JYUREIMON_NAME_OFF, PEN_JYUREIMON_ID_OFF, PEN_JYUREIMON_FQID_OFF, PEN_JYUREIMON_FQNAME_OFF, PEN_JYUREIMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },  // Jyureimon
        { PEN_KABUTERIMON_NAME_OFF, PEN_KABUTERIMON_ID_OFF, PEN_KABUTERIMON_FQID_OFF, PEN_KABUTERIMON_FQNAME_OFF, PEN_KABUTERIMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },  // Kabuterimon
        { PEN_KIWIMON_NAME_OFF, PEN_KIWIMON_ID_OFF, PEN_KIWIMON_FQID_OFF, PEN_KIWIMON_FQNAME_OFF, PEN_KIWIMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },  // Kiwimon
        { PEN_KNIGHTMON_NAME_OFF, PEN_KNIGHTMON_ID_OFF, PEN_KNIGHTMON_FQID_OFF, PEN_KNIGHTMON_FQNAME_OFF, PEN_KNIGHTMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },  // Knightmon
        { PEN_KOKUWAMON_NAME_OFF, PEN_KOKUWAMON_ID_OFF, PEN_KOKUWAMON_FQID_OFF, PEN_KOKUWAMON_FQNAME_OFF, PEN_KOKUWAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },  // Kokuwamon
        { PEN_KUWAGAMON_NAME_OFF, PEN_KUWAGAMON_ID_OFF, PEN_KUWAGAMON_FQID_OFF, PEN_KUWAGAMON_FQNAME_OFF, PEN_KUWAGAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },  // Kuwagamon
        { PEN_LADY_DEVIMON_NAME_OFF, PEN_LADY_DEVIMON_ID_OFF, PEN_LADY_DEVIMON_FQID_OFF, PEN_LADY_DEVIMON_FQNAME_OFF, PEN_LADY_DEVIMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },  // Lady Devimon
        { PEN_LEOMON_NAME_OFF, PEN_LEOMON_ID_OFF, PEN_LEOMON_FQID_OFF, PEN_LEOMON_FQNAME_OFF, PEN_LEOMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },  // Leomon
        { PEN_LILIMON_NAME_OFF, PEN_LILIMON_ID_OFF, PEN_LILIMON_FQID_OFF, PEN_LILIMON_FQNAME_OFF, PEN_LILIMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },  // Lilimon
        { PEN_MAMMON_NAME_OFF, PEN_MAMMON_ID_OFF, PEN_MAMMON_FQID_OFF, PEN_MAMMON_FQNAME_OFF, PEN_MAMMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },  // Mammon
        { PEN_MARIN_ANGEMON_NAME_OFF, PEN_MARIN_ANGEMON_ID_OFF, PEN_MARIN_ANGEMON_FQID_OFF, PEN_MARIN_ANGEMON_FQNAME_OFF, PEN_MARIN_ANGEMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },  // Marin Angemon
        { PEN_MARIN_DEVIMON_NAME_OFF, PEN_MARIN_DEVIMON_ID_OFF, PEN_MARIN_DEVIMON_FQID_OFF, PEN_MARIN_DEVIMON_FQNAME_OFF, PEN_MARIN_DEVIMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },  // Marin Devimon
        { PEN_MECHANORIMON_NAME_OFF, PEN_MECHANORIMON_ID_OFF, PEN_MECHANORIMON_FQID_OFF, PEN_MECHANORIMON_FQNAME_OFF, PEN_MECHANORIMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },  // Mechanorimon
        { PEN_MEGADRAMON_NAME_OFF, PEN_MEGADRAMON_ID_OFF, PEN_MEGADRAMON_FQID_OFF, PEN_MEGADRAMON_FQNAME_OFF, PEN_MEGADRAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },  // Megadramon
        { PEN_MEGA_SEADRAMON_NAME_OFF, PEN_MEGA_SEADRAMON_ID_OFF, PEN_MEGA_SEADRAMON_FQID_OFF, PEN_MEGA_SEADRAMON_FQNAME_OFF, PEN_MEGA_SEADRAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },  // Mega Seadramon
        { PEN_MERAMON_NAME_OFF, PEN_MERAMON_ID_OFF, PEN_MERAMON_FQID_OFF, PEN_MERAMON_FQNAME_OFF, PEN_MERAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },  // Meramon
        { PEN_METAL_ETEMON_NAME_OFF, PEN_METAL_ETEMON_ID_OFF, PEN_METAL_ETEMON_FQID_OFF, PEN_METAL_ETEMON_FQNAME_OFF, PEN_METAL_ETEMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },  // Metal Etemon
        { PEN_METAL_GARURUMON_NAME_OFF, PEN_METAL_GARURUMON_ID_OFF, PEN_METAL_GARURUMON_FQID_OFF, PEN_METAL_GARURUMON_FQNAME_OFF, PEN_METAL_GARURUMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },  // Metal Garurumon
        { PEN_METAL_GREYMON_NAME_OFF, PEN_METAL_GREYMON_ID_OFF, PEN_METAL_GREYMON_FQID_OFF, PEN_METAL_GREYMON_FQNAME_OFF, PEN_METAL_GREYMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },  // Metal Greymon
        { PEN_METAL_MAMEMON_NAME_OFF, PEN_METAL_MAMEMON_ID_OFF, PEN_METAL_MAMEMON_FQID_OFF, PEN_METAL_MAMEMON_FQNAME_OFF, PEN_METAL_MAMEMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },  // Metal Mamemon
        { PEN_METAL_SEADRAMON_NAME_OFF, PEN_METAL_SEADRAMON_ID_OFF, PEN_METAL_SEADRAMON_FQID_OFF, PEN_METAL_SEADRAMON_FQNAME_OFF, PEN_METAL_SEADRAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },  // Metal Seadramon
        { PEN_MOCHIMON_NAME_OFF, PEN_MOCHIMON_ID_OFF, PEN_MOCHIMON_FQID_OFF, PEN_MOCHIMON_FQNAME_OFF, PEN_MOCHIMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },  // Mochimon
        { PEN_MOKUMON_NAME_OFF, PEN_MOKUMON_ID_OFF, PEN_MOKUMON_FQID_OFF, PEN_MOKUMON_FQNAME_OFF, PEN_MOKUMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },  // Mokumon
        { PEN_MONOCHROMON_NAME_OFF, PEN_MONOCHROMON_ID_OFF, PEN_MONOCHROMON_FQID_OFF, PEN_MONOCHROMON_FQNAME_OFF, PEN_MONOCHROMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },  // Monochromon
        { PEN_MUGENDRAMON_NAME_OFF, PEN_MUGENDRAMON_ID_OFF, PEN_MUGENDRAMON_FQID_OFF, PEN_MUGENDRAMON_FQNAME_OFF, PEN_MUGENDRAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },  // Mugendramon
        { PEN_MUSHMON_NAME_OFF, PEN_MUSHMON_ID_OFF, PEN_MUSHMON_FQID_OFF, PEN_MUSHMON_FQNAME_OFF, PEN_MUSHMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },  // Mushmon
        { PEN_NYAROMON_NAME_OFF, PEN_NYAROMON_ID_OFF, PEN_NYAROMON_FQID_OFF, PEN_NYAROMON_FQNAME_OFF, PEN_NYAROMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },  // Nyaromon
        { PEN_NYOKIMON_NAME_OFF, PEN_NYOKIMON_ID_OFF, PEN_NYOKIMON_FQID_OFF, PEN_NYOKIMON_FQNAME_OFF, PEN_NYOKIMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },  // Nyokimon
        { PEN_OCTMON_NAME_OFF, PEN_OCTMON_ID_OFF, PEN_OCTMON_FQID_OFF, PEN_OCTMON_FQNAME_OFF, PEN_OCTMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },  // Octmon
        { PEN_OKUWAMON_NAME_OFF, PEN_OKUWAMON_ID_OFF, PEN_OKUWAMON_FQID_OFF, PEN_OKUWAMON_FQNAME_OFF, PEN_OKUWAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },  // Okuwamon
        { PEN_OMEGAMON_NAME_OFF, PEN_OMEGAMON_ID_OFF, PEN_OMEGAMON_FQID_OFF, PEN_OMEGAMON_FQNAME_OFF, PEN_OMEGAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },  // Omegamon
        { PEN_OTAMAMON_NAME_OFF, PEN_OTAMAMON_ID_OFF, PEN_OTAMAMON_FQID_OFF, PEN_OTAMAMON_FQNAME_OFF, PEN_OTAMAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },  // Otamamon
        { PEN_PALMON_NAME_OFF, PEN_PALMON_ID_OFF, PEN_PALMON_FQID_OFF, PEN_PALMON_FQNAME_OFF, PEN_PALMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },  // Palmon
        { PEN_PETI_MERAMON_NAME_OFF, PEN_PETI_MERAMON_ID_OFF, PEN_PETI_MERAMON_FQID_OFF, PEN_PETI_MERAMON_FQNAME_OFF, PEN_PETI_MERAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },  // Peti Meramon
        { PEN_PICCOLOMON_NAME_OFF, PEN_PICCOLOMON_ID_OFF, PEN_PICCOLOMON_FQID_OFF, PEN_PICCOLOMON_FQNAME_OFF, PEN_PICCOLOMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },  // Piccolomon
        { PEN_PICO_DEVIMON_NAME_OFF, PEN_PICO_DEVIMON_ID_OFF, PEN_PICO_DEVIMON_FQID_OFF, PEN_PICO_DEVIMON_FQNAME_OFF, PEN_PICO_DEVIMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },  // Pico Devimon
        { PEN_PIEMON_NAME_OFF, PEN_PIEMON_ID_OFF, PEN_PIEMON_FQID_OFF, PEN_PIEMON_FQNAME_OFF, PEN_PIEMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },  // Piemon
        { PEN_PINOCHIMON_NAME_OFF, PEN_PINOCHIMON_ID_OFF, PEN_PINOCHIMON_FQID_OFF, PEN_PINOCHIMON_FQNAME_OFF, PEN_PINOCHIMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },  // Pinochimon
        { PEN_PITCHMON_NAME_OFF, PEN_PITCHMON_ID_OFF, PEN_PITCHMON_FQID_OFF, PEN_PITCHMON_FQNAME_OFF, PEN_PITCHMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },  // Pitchmon
        { PEN_PIYOMON_NAME_OFF, PEN_PIYOMON_ID_OFF, PEN_PIYOMON_FQID_OFF, PEN_PIYOMON_FQNAME_OFF, PEN_PIYOMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },  // Piyomon
        { PEN_PLESIOMON_NAME_OFF, PEN_PLESIOMON_ID_OFF, PEN_PLESIOMON_FQID_OFF, PEN_PLESIOMON_FQNAME_OFF, PEN_PLESIOMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },  // Plesiomon
        { PEN_PLOTMON_NAME_OFF, PEN_PLOTMON_ID_OFF, PEN_PLOTMON_FQID_OFF, PEN_PLOTMON_FQNAME_OFF, PEN_PLOTMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },  // Plotmon
        { PEN_PUKAMON_NAME_OFF, PEN_PUKAMON_ID_OFF, PEN_PUKAMON_FQID_OFF, PEN_PUKAMON_FQNAME_OFF, PEN_PUKAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },  // Pukamon
        { PEN_PUKUMON_NAME_OFF, PEN_PUKUMON_ID_OFF, PEN_PUKUMON_FQID_OFF, PEN_PUKUMON_FQNAME_OFF, PEN_PUKUMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },  // Pukumon
        { PEN_PUMPMON_NAME_OFF, PEN_PUMPMON_ID_OFF, PEN_PUMPMON_FQID_OFF, PEN_PUMPMON_FQNAME_OFF, PEN_PUMPMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },  // Pumpmon
        { PEN_PYOCOMON_NAME_OFF, PEN_PYOCOMON_ID_OFF, PEN_PYOCOMON_FQID_OFF, PEN_PYOCOMON_FQNAME_OFF, PEN_PYOCOMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },  // Pyocomon
        { PEN_RED_VEGIMON_NAME_OFF, PEN_RED_VEGIMON_ID_OFF, PEN_RED_VEGIMON_FQID_OFF, PEN_RED_VEGIMON_FQNAME_OFF, PEN_RED_VEGIMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },  // Red Vegimon
        { PEN_REVOLMON_NAME_OFF, PEN_REVOLMON_ID_OFF, PEN_REVOLMON_FQID_OFF, PEN_REVOLMON_FQNAME_OFF, PEN_REVOLMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },  // Revolmon
        { PEN_ROSEMON_NAME_OFF, PEN_ROSEMON_ID_OFF, PEN_ROSEMON_FQID_OFF, PEN_ROSEMON_FQNAME_OFF, PEN_ROSEMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },  // Rosemon
        { PEN_RUKAMON_NAME_OFF, PEN_RUKAMON_ID_OFF, PEN_RUKAMON_FQID_OFF, PEN_RUKAMON_FQNAME_OFF, PEN_RUKAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },  // Rukamon
        { PEN_SABER_LEOMON_NAME_OFF, PEN_SABER_LEOMON_ID_OFF, PEN_SABER_LEOMON_FQID_OFF, PEN_SABER_LEOMON_FQNAME_OFF, PEN_SABER_LEOMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },  // Saber Leomon
        { PEN_SEADRAMON_NAME_OFF, PEN_SEADRAMON_ID_OFF, PEN_SEADRAMON_FQID_OFF, PEN_SEADRAMON_FQNAME_OFF, PEN_SEADRAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },  // Seadramon
        { PEN_SHAKOMON_NAME_OFF, PEN_SHAKOMON_ID_OFF, PEN_SHAKOMON_FQID_OFF, PEN_SHAKOMON_FQNAME_OFF, PEN_SHAKOMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },  // Shakomon
        { PEN_SKULL_MAMMON_NAME_OFF, PEN_SKULL_MAMMON_ID_OFF, PEN_SKULL_MAMMON_FQID_OFF, PEN_SKULL_MAMMON_FQNAME_OFF, PEN_SKULL_MAMMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },  // Skull Mammon
        { PEN_STARMON_NAME_OFF, PEN_STARMON_ID_OFF, PEN_STARMON_FQID_OFF, PEN_STARMON_FQNAME_OFF, PEN_STARMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },  // Starmon
        { PEN_TAILMON_NAME_OFF, PEN_TAILMON_ID_OFF, PEN_TAILMON_FQID_OFF, PEN_TAILMON_FQNAME_OFF, PEN_TAILMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },  // Tailmon
        { PEN_TANKMON_NAME_OFF, PEN_TANKMON_ID_OFF, PEN_TANKMON_FQID_OFF, PEN_TANKMON_FQNAME_OFF, PEN_TANKMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },  // Tankmon
        { PEN_TENTOMON_NAME_OFF, PEN_TENTOMON_ID_OFF, PEN_TENTOMON_FQID_OFF, PEN_TENTOMON_FQNAME_OFF, PEN_TENTOMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },  // Tentomon
        { PEN_THUNDERBALLMON_NAME_OFF, PEN_THUNDERBALLMON_ID_OFF, PEN_THUNDERBALLMON_FQID_OFF, PEN_THUNDERBALLMON_FQNAME_OFF, PEN_THUNDERBALLMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },  // Thunderballmon
        { PEN_TOGEMON_NAME_OFF, PEN_TOGEMON_ID_OFF, PEN_TOGEMON_FQID_OFF, PEN_TOGEMON_FQNAME_OFF, PEN_TOGEMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },  // Togemon
        { PEN_TONOSAMA_GEKOMON_NAME_OFF, PEN_TONOSAMA_GEKOMON_ID_OFF, PEN_TONOSAMA_GEKOMON_FQID_OFF, PEN_TONOSAMA_GEKOMON_FQNAME_OFF, PEN_TONOSAMA_GEKOMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },  // Tonosama Gekomon
        { PEN_TORTAMON_NAME_OFF, PEN_TORTAMON_ID_OFF, PEN_TORTAMON_FQID_OFF, PEN_TORTAMON_FQNAME_OFF, PEN_TORTAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },  // Tortamon
        { PEN_TOY_AGUMON_NAME_OFF, PEN_TOY_AGUMON_ID_OFF, PEN_TOY_AGUMON_FQID_OFF, PEN_TOY_AGUMON_FQNAME_OFF, PEN_TOY_AGUMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },  // Toy Agumon
        { PEN_TRICERAMON_NAME_OFF, PEN_TRICERAMON_ID_OFF, PEN_TRICERAMON_FQID_OFF, PEN_TRICERAMON_FQNAME_OFF, PEN_TRICERAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },  // Triceramon
        { PEN_VAMDEMON_NAME_OFF, PEN_VAMDEMON_ID_OFF, PEN_VAMDEMON_FQID_OFF, PEN_VAMDEMON_FQNAME_OFF, PEN_VAMDEMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },  // Vamdemon
        { PEN_V_DRAMON_NAME_OFF, PEN_V_DRAMON_ID_OFF, PEN_V_DRAMON_FQID_OFF, PEN_V_DRAMON_FQNAME_OFF, PEN_V_DRAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },  // V-dramon
        { PEN_VENOM_VAMDEMON_NAME_OFF, PEN_VENOM_VAMDEMON_ID_OFF, PEN_VENOM_VAMDEMON_FQID_OFF, PEN_VENOM_VAMDEMON_FQNAME_OFF, PEN_VENOM_VAMDEMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },  // Venom Vamdemon
        { PEN_WAR_GREYMON_NAME_OFF, PEN_WAR_GREYMON_ID_OFF, PEN_WAR_GREYMON_FQID_OFF, PEN_WAR_GREYMON_FQNAME_OFF, PEN_WAR_GREYMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },  // War Greymon
        { PEN_WARU_MONZAEMON_NAME_OFF, PEN_WARU_MONZAEMON_ID_OFF, PEN_WARU_MONZAEMON_FQID_OFF, PEN_WARU_MONZAEMON_FQNAME_OFF, PEN_WARU_MONZAEMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },  // Waru Monzaemon
        { PEN_WERE_GARURUMON_NAME_OFF, PEN_WERE_GARURUMON_ID_OFF, PEN_WERE_GARURUMON_FQID_OFF, PEN_WERE_GARURUMON_FQNAME_OFF, PEN_WERE_GARURUMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },  // Were Garurumon
        { PEN_WHAMON_NAME_OFF, PEN_WHAMON_ID_OFF, PEN_WHAMON_FQID_OFF, PEN_WHAMON_FQNAME_OFF, PEN_WHAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },  // Whamon
        { PEN_WIZARMON_NAME_OFF, PEN_WIZARMON_ID_OFF, PEN_WIZARMON_FQID_OFF, PEN_WIZARMON_FQNAME_OFF, PEN_WIZARMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },  // Wizarmon
        { PEN_WOODMON_NAME_OFF, PEN_WOODMON_ID_OFF, PEN_WOODMON_FQID_OFF, PEN_WOODMON_FQNAME_OFF, PEN_WOODMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },  // Woodmon
        { PEN_YUKIMI_BOTAMON_NAME_OFF, PEN_YUKIMI_BOTAMON_ID_OFF, PEN_YUKIMI_BOTAMON_FQID_OFF, PEN_YUKIMI_BOTAMON_FQNAME_OFF, PEN_YUKIMI_BOTAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },  // Yukimi Botamon
        { PEN_ZUDOMON_NAME_OFF, PEN_ZUDOMON_ID_OFF, PEN_ZUDOMON_FQID_OFF, PEN_ZUDOMON_FQNAME_OFF, PEN_ZUDOMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },  // Zudomon
        
    };
    static_assert(LEN_ARRAY(pen_animation_table) == PEN_ANIM_COUNT);

    config_animation_entry_t get_config_animation_name_pen(size_t index) {
        assert(index < PEN_ANIM_COUNT);
        const auto& entry = pen_animation_table[index];
        return { PEN_STRINGS + entry.name, PEN_STRINGS + entry.id, PEN_STRINGS + entry.fqid, PEN_STRINGS + entry.fqname, entry.anim_index, entry.set, entry.layout };
    }

    int config_parse_animation_name_pen(config::config_t& config, const char *value) {
        int ret = -1;
        for (size_t i = 0;ret < 0 && i < PEN_ANIM_COUNT;++i) {
            const auto& entry = pen_animation_table[i];
            if (strcmp(value, PEN_STRINGS + entry.name) == 0 ||
                strcmp(value, PEN_STRINGS + entry.id) == 0 ||
                strcmp(value, PEN_STRINGS + entry.fqid) == 0 ||
                strcmp(value, PEN_STRINGS + entry.fqname) == 0) {
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
