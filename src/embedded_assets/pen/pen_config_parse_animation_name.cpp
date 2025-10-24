#include "embedded_assets/embedded_image.h"
#include "embedded_assets/pen/pen.hpp"
#include "pen_config_parse_animation_name.h"

namespace bongocat::assets {
    static const config_animation_entry_t pen_animation_table[] = {
        { PEN_AERO_V_DRAMON_NAME, PEN_AERO_V_DRAMON_ID, PEN_AERO_V_DRAMON_FQID, PEN_AERO_V_DRAMON_FQNAME, PEN_AERO_V_DRAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN_ANGEWOMON_NAME, PEN_ANGEWOMON_ID, PEN_ANGEWOMON_FQID, PEN_ANGEWOMON_FQNAME, PEN_ANGEWOMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN_ANOMALOCARIMON_NAME, PEN_ANOMALOCARIMON_ID, PEN_ANOMALOCARIMON_FQID, PEN_ANOMALOCARIMON_FQNAME, PEN_ANOMALOCARIMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN_ASURAMON_NAME, PEN_ASURAMON_ID, PEN_ASURAMON_FQID, PEN_ASURAMON_FQNAME, PEN_ASURAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN_ATLUR_KABUTERIMON_NAME, PEN_ATLUR_KABUTERIMON_ID, PEN_ATLUR_KABUTERIMON_FQID, PEN_ATLUR_KABUTERIMON_FQNAME, PEN_ATLUR_KABUTERIMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN_BAKUMON_NAME, PEN_BAKUMON_ID, PEN_BAKUMON_FQID, PEN_BAKUMON_FQNAME, PEN_BAKUMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN_BIG_MAMEMON_NAME, PEN_BIG_MAMEMON_ID, PEN_BIG_MAMEMON_FQID, PEN_BIG_MAMEMON_FQNAME, PEN_BIG_MAMEMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN_BLOSSOMON_NAME, PEN_BLOSSOMON_ID, PEN_BLOSSOMON_FQID, PEN_BLOSSOMON_FQNAME, PEN_BLOSSOMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN_BOLTMON_NAME, PEN_BOLTMON_ID, PEN_BOLTMON_FQID, PEN_BOLTMON_FQNAME, PEN_BOLTMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN_BUBBMON_NAME, PEN_BUBBMON_ID, PEN_BUBBMON_FQID, PEN_BUBBMON_FQNAME, PEN_BUBBMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN_CANDMON_NAME, PEN_CANDMON_ID, PEN_CANDMON_FQID, PEN_CANDMON_FQNAME, PEN_CANDMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN_CAPRIMON_NAME, PEN_CAPRIMON_ID, PEN_CAPRIMON_FQID, PEN_CAPRIMON_FQNAME, PEN_CAPRIMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN_CHOROMON_NAME, PEN_CHOROMON_ID, PEN_CHOROMON_FQID, PEN_CHOROMON_FQNAME, PEN_CHOROMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN_CLOCKMON_NAME, PEN_CLOCKMON_ID, PEN_CLOCKMON_FQID, PEN_CLOCKMON_FQNAME, PEN_CLOCKMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN_CYBERDRAMON_NAME, PEN_CYBERDRAMON_ID, PEN_CYBERDRAMON_FQID, PEN_CYBERDRAMON_FQNAME, PEN_CYBERDRAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN_DAGOMON_NAME, PEN_DAGOMON_ID, PEN_DAGOMON_FQID, PEN_DAGOMON_FQNAME, PEN_DAGOMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN_DEATH_MERAMON_NAME, PEN_DEATH_MERAMON_ID, PEN_DEATH_MERAMON_FQID, PEN_DEATH_MERAMON_FQNAME, PEN_DEATH_MERAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN_DELUMON_NAME, PEN_DELUMON_ID, PEN_DELUMON_FQID, PEN_DELUMON_FQNAME, PEN_DELUMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN_DOKUGUMON_NAME, PEN_DOKUGUMON_ID, PEN_DOKUGUMON_FQID, PEN_DOKUGUMON_FQNAME, PEN_DOKUGUMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN_EBIDRAMON_NAME, PEN_EBIDRAMON_ID, PEN_EBIDRAMON_FQID, PEN_EBIDRAMON_FQNAME, PEN_EBIDRAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN_FANTOMON_NAME, PEN_FANTOMON_ID, PEN_FANTOMON_FQID, PEN_FANTOMON_FQNAME, PEN_FANTOMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN_FLORAMON_NAME, PEN_FLORAMON_ID, PEN_FLORAMON_FQID, PEN_FLORAMON_FQNAME, PEN_FLORAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN_GANIMON_NAME, PEN_GANIMON_ID, PEN_GANIMON_FQID, PEN_GANIMON_FQNAME, PEN_GANIMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN_GARUDAMON_NAME, PEN_GARUDAMON_ID, PEN_GARUDAMON_FQID, PEN_GARUDAMON_FQNAME, PEN_GARUDAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN_GEKOMON_NAME, PEN_GEKOMON_ID, PEN_GEKOMON_FQID, PEN_GEKOMON_FQNAME, PEN_GEKOMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN_GERBEMON_NAME, PEN_GERBEMON_ID, PEN_GERBEMON_FQID, PEN_GERBEMON_FQNAME, PEN_GERBEMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN_GESOMON_NAME, PEN_GESOMON_ID, PEN_GESOMON_FQID, PEN_GESOMON_FQNAME, PEN_GESOMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN_GOMAMON_NAME, PEN_GOMAMON_ID, PEN_GOMAMON_FQID, PEN_GOMAMON_FQNAME, PEN_GOMAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN_GOTTSUMON_NAME, PEN_GOTTSUMON_ID, PEN_GOTTSUMON_FQID, PEN_GOTTSUMON_FQNAME, PEN_GOTTSUMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN_GRIFFOMON_NAME, PEN_GRIFFOMON_ID, PEN_GRIFFOMON_FQID, PEN_GRIFFOMON_FQNAME, PEN_GRIFFOMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN_GUARDROMON_NAME, PEN_GUARDROMON_ID, PEN_GUARDROMON_FQID, PEN_GUARDROMON_FQNAME, PEN_GUARDROMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN_HAGURUMON_NAME, PEN_HAGURUMON_ID, PEN_HAGURUMON_FQID, PEN_HAGURUMON_FQNAME, PEN_HAGURUMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN_HANGYMON_NAME, PEN_HANGYMON_ID, PEN_HANGYMON_FQID, PEN_HANGYMON_FQNAME, PEN_HANGYMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN_HANUMON_NAME, PEN_HANUMON_ID, PEN_HANUMON_FQID, PEN_HANUMON_FQNAME, PEN_HANUMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN_HERKULE_KABUTERIMON_NAME, PEN_HERKULE_KABUTERIMON_ID, PEN_HERKULE_KABUTERIMON_FQID, PEN_HERKULE_KABUTERIMON_FQNAME, PEN_HERKULE_KABUTERIMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN_HOLY_ANGEMON_NAME, PEN_HOLY_ANGEMON_ID, PEN_HOLY_ANGEMON_FQID, PEN_HOLY_ANGEMON_FQNAME, PEN_HOLY_ANGEMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN_HOLYDRAMON_NAME, PEN_HOLYDRAMON_ID, PEN_HOLYDRAMON_FQID, PEN_HOLYDRAMON_FQNAME, PEN_HOLYDRAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN_HOUOUMON_NAME, PEN_HOUOUMON_ID, PEN_HOUOUMON_FQID, PEN_HOUOUMON_FQNAME, PEN_HOUOUMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN_IGNAMON_NAME, PEN_IGNAMON_ID, PEN_IGNAMON_FQID, PEN_IGNAMON_FQNAME, PEN_IGNAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN_IKKAKUMON_NAME, PEN_IKKAKUMON_ID, PEN_IKKAKUMON_FQID, PEN_IKKAKUMON_FQNAME, PEN_IKKAKUMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN_JYAGAMON_NAME, PEN_JYAGAMON_ID, PEN_JYAGAMON_FQID, PEN_JYAGAMON_FQNAME, PEN_JYAGAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN_JYUREIMON_NAME, PEN_JYUREIMON_ID, PEN_JYUREIMON_FQID, PEN_JYUREIMON_FQNAME, PEN_JYUREIMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN_KIWIMON_NAME, PEN_KIWIMON_ID, PEN_KIWIMON_FQID, PEN_KIWIMON_FQNAME, PEN_KIWIMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN_KNIGHTMON_NAME, PEN_KNIGHTMON_ID, PEN_KNIGHTMON_FQID, PEN_KNIGHTMON_FQNAME, PEN_KNIGHTMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN_KOKUWAMON_NAME, PEN_KOKUWAMON_ID, PEN_KOKUWAMON_FQID, PEN_KOKUWAMON_FQNAME, PEN_KOKUWAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN_LADY_DEVIMON_NAME, PEN_LADY_DEVIMON_ID, PEN_LADY_DEVIMON_FQID, PEN_LADY_DEVIMON_FQNAME, PEN_LADY_DEVIMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN_LILIMON_NAME, PEN_LILIMON_ID, PEN_LILIMON_FQID, PEN_LILIMON_FQNAME, PEN_LILIMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN_MAMMON_NAME, PEN_MAMMON_ID, PEN_MAMMON_FQID, PEN_MAMMON_FQNAME, PEN_MAMMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN_MARIN_ANGEMON_NAME, PEN_MARIN_ANGEMON_ID, PEN_MARIN_ANGEMON_FQID, PEN_MARIN_ANGEMON_FQNAME, PEN_MARIN_ANGEMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN_MARIN_DEVIMON_NAME, PEN_MARIN_DEVIMON_ID, PEN_MARIN_DEVIMON_FQID, PEN_MARIN_DEVIMON_FQNAME, PEN_MARIN_DEVIMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN_MECHANORIMON_NAME, PEN_MECHANORIMON_ID, PEN_MECHANORIMON_FQID, PEN_MECHANORIMON_FQNAME, PEN_MECHANORIMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN_MEGA_SEADRAMON_NAME, PEN_MEGA_SEADRAMON_ID, PEN_MEGA_SEADRAMON_FQID, PEN_MEGA_SEADRAMON_FQNAME, PEN_MEGA_SEADRAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN_METAL_ETEMON_NAME, PEN_METAL_ETEMON_ID, PEN_METAL_ETEMON_FQID, PEN_METAL_ETEMON_FQNAME, PEN_METAL_ETEMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN_METAL_SEADRAMON_NAME, PEN_METAL_SEADRAMON_ID, PEN_METAL_SEADRAMON_FQID, PEN_METAL_SEADRAMON_FQNAME, PEN_METAL_SEADRAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN_MOCHIMON_NAME, PEN_MOCHIMON_ID, PEN_MOCHIMON_FQID, PEN_MOCHIMON_FQNAME, PEN_MOCHIMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN_MOKUMON_NAME, PEN_MOKUMON_ID, PEN_MOKUMON_FQID, PEN_MOKUMON_FQNAME, PEN_MOKUMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN_MUSHMON_NAME, PEN_MUSHMON_ID, PEN_MUSHMON_FQID, PEN_MUSHMON_FQNAME, PEN_MUSHMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN_NYOKIMON_NAME, PEN_NYOKIMON_ID, PEN_NYOKIMON_FQID, PEN_NYOKIMON_FQNAME, PEN_NYOKIMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN_OCTMON_NAME, PEN_OCTMON_ID, PEN_OCTMON_FQID, PEN_OCTMON_FQNAME, PEN_OCTMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN_OKUWAMON_NAME, PEN_OKUWAMON_ID, PEN_OKUWAMON_FQID, PEN_OKUWAMON_FQNAME, PEN_OKUWAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN_OTAMAMON_NAME, PEN_OTAMAMON_ID, PEN_OTAMAMON_FQID, PEN_OTAMAMON_FQNAME, PEN_OTAMAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN_PETI_MERAMON_NAME, PEN_PETI_MERAMON_ID, PEN_PETI_MERAMON_FQID, PEN_PETI_MERAMON_FQNAME, PEN_PETI_MERAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN_PICO_DEVIMON_NAME, PEN_PICO_DEVIMON_ID, PEN_PICO_DEVIMON_FQID, PEN_PICO_DEVIMON_FQNAME, PEN_PICO_DEVIMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN_PIEMON_NAME, PEN_PIEMON_ID, PEN_PIEMON_FQID, PEN_PIEMON_FQNAME, PEN_PIEMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN_PLESIOMON_NAME, PEN_PLESIOMON_ID, PEN_PLESIOMON_FQID, PEN_PLESIOMON_FQNAME, PEN_PLESIOMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN_PUKUMON_NAME, PEN_PUKUMON_ID, PEN_PUKUMON_FQID, PEN_PUKUMON_FQNAME, PEN_PUKUMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN_PUMPMON_NAME, PEN_PUMPMON_ID, PEN_PUMPMON_FQID, PEN_PUMPMON_FQNAME, PEN_PUMPMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN_PYOCOMON_NAME, PEN_PYOCOMON_ID, PEN_PYOCOMON_FQID, PEN_PYOCOMON_FQNAME, PEN_PYOCOMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN_RAKAMON_NAME, PEN_RAKAMON_ID, PEN_RAKAMON_FQID, PEN_RAKAMON_FQNAME, PEN_RAKAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN_RED_VEGIMON_NAME, PEN_RED_VEGIMON_ID, PEN_RED_VEGIMON_FQID, PEN_RED_VEGIMON_FQNAME, PEN_RED_VEGIMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN_REVOLMON_NAME, PEN_REVOLMON_ID, PEN_REVOLMON_FQID, PEN_REVOLMON_FQNAME, PEN_REVOLMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN_ROSEMON_NAME, PEN_ROSEMON_ID, PEN_ROSEMON_FQID, PEN_ROSEMON_FQNAME, PEN_ROSEMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN_SABER_LEOMON_NAME, PEN_SABER_LEOMON_ID, PEN_SABER_LEOMON_FQID, PEN_SABER_LEOMON_FQNAME, PEN_SABER_LEOMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN_SHAKOMON_NAME, PEN_SHAKOMON_ID, PEN_SHAKOMON_FQID, PEN_SHAKOMON_FQNAME, PEN_SHAKOMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN_STARMON_NAME, PEN_STARMON_ID, PEN_STARMON_FQID, PEN_STARMON_FQNAME, PEN_STARMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN_TAILMON_NAME, PEN_TAILMON_ID, PEN_TAILMON_FQID, PEN_TAILMON_FQNAME, PEN_TAILMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN_TANKMON_NAME, PEN_TANKMON_ID, PEN_TANKMON_FQID, PEN_TANKMON_FQNAME, PEN_TANKMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN_TENTOMON_NAME, PEN_TENTOMON_ID, PEN_TENTOMON_FQID, PEN_TENTOMON_FQNAME, PEN_TENTOMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN_THUNDERBALLMON_NAME, PEN_THUNDERBALLMON_ID, PEN_THUNDERBALLMON_FQID, PEN_THUNDERBALLMON_FQNAME, PEN_THUNDERBALLMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN_TOGEMON_NAME, PEN_TOGEMON_ID, PEN_TOGEMON_FQID, PEN_TOGEMON_FQNAME, PEN_TOGEMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN_TONOSAMA_GEKOMON_NAME, PEN_TONOSAMA_GEKOMON_ID, PEN_TONOSAMA_GEKOMON_FQID, PEN_TONOSAMA_GEKOMON_FQNAME, PEN_TONOSAMA_GEKOMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN_TORTAMON_NAME, PEN_TORTAMON_ID, PEN_TORTAMON_FQID, PEN_TORTAMON_FQNAME, PEN_TORTAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN_TOY_AGUMON_NAME, PEN_TOY_AGUMON_ID, PEN_TOY_AGUMON_FQID, PEN_TOY_AGUMON_FQNAME, PEN_TOY_AGUMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN_TRICERAMON_NAME, PEN_TRICERAMON_ID, PEN_TRICERAMON_FQID, PEN_TRICERAMON_FQNAME, PEN_TRICERAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN_V_DRAMON_NAME, PEN_V_DRAMON_ID, PEN_V_DRAMON_FQID, PEN_V_DRAMON_FQNAME, PEN_V_DRAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN_VEMDEMON_NAME, PEN_VEMDEMON_ID, PEN_VEMDEMON_FQID, PEN_VEMDEMON_FQNAME, PEN_VEMDEMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN_VENOM_VAMDEMON_NAME, PEN_VENOM_VAMDEMON_ID, PEN_VENOM_VAMDEMON_FQID, PEN_VENOM_VAMDEMON_FQNAME, PEN_VENOM_VAMDEMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN_WARU_MOZAEMON_NAME, PEN_WARU_MOZAEMON_ID, PEN_WARU_MOZAEMON_FQID, PEN_WARU_MOZAEMON_FQNAME, PEN_WARU_MOZAEMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN_WIZARMON_NAME, PEN_WIZARMON_ID, PEN_WIZARMON_FQID, PEN_WIZARMON_FQNAME, PEN_WIZARMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN_WOODMON_NAME, PEN_WOODMON_ID, PEN_WOODMON_FQID, PEN_WOODMON_FQNAME, PEN_WOODMON_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN_ZUDOMOM_NAME, PEN_ZUDOMOM_ID, PEN_ZUDOMOM_FQID, PEN_ZUDOMOM_FQNAME, PEN_ZUDOMOM_ANIM_INDEX, config::config_animation_dm_set_t::pen, config::config_animation_sprite_sheet_layout_t::Dm },
    };

    config_animation_entry_t get_config_animation_name_pen(size_t index) {
        for (const auto& entry : pen_animation_table) {
            assert(entry.anim_index >= 0);
            if (static_cast<size_t>(entry.anim_index) == index) return entry;
        }
        return pen_animation_table[index];
    }

    int config_parse_animation_name_pen(config::config_t& config, const char *value) {
        for (const auto& entry : pen_animation_table) {
            if (strcmp(value, entry.name) == 0 ||
                strcmp(value, entry.id) == 0 ||
                strcmp(value, entry.fqid) == 0 ||
                strcmp(value, entry.fqname) == 0) {
                config.animation_index = entry.anim_index;
                config.animation_dm_set = entry.set;
                config.animation_sprite_sheet_layout = entry.layout;
                return entry.anim_index;
            }
        }
        return -1;
    }
}

