#include "embedded_assets/embedded_image.h"
#include "embedded_assets/pen/pen.hpp"
#include "embedded_assets/pen/pen_images.h"
#include "embedded_assets/pen/pen_sprite.h"

namespace bongocat::assets {
    embedded_image_t get_pen_sprite_sheet(size_t index) {
        switch (index) {
            case PEN_AERO_V_DRAMON_ANIM_INDEX: return {pen_aero_v_dramon_png, pen_aero_v_dramon_png_size, "aero_v_dramon"};
            case PEN_ANGEWOMON_ANIM_INDEX: return {pen_angewomon_png, pen_angewomon_png_size, "angewomon"};
            case PEN_ANOMALOCARIMON_ANIM_INDEX: return {pen_anomalocarimon_png, pen_anomalocarimon_png_size, "anomalocarimon"};
            case PEN_ASURAMON_ANIM_INDEX: return {pen_asuramon_png, pen_asuramon_png_size, "asuramon"};
            case PEN_ATLUR_KABUTERIMON_ANIM_INDEX: return {pen_atlur_kabuterimon_png, pen_atlur_kabuterimon_png_size, "atlur_kabuterimon"};
            case PEN_BAKUMON_ANIM_INDEX: return {pen_bakumon_png, pen_bakumon_png_size, "bakumon"};
            case PEN_BIG_MAMEMON_ANIM_INDEX: return {pen_big_mamemon_png, pen_big_mamemon_png_size, "big_mamemon"};
            case PEN_BLOSSOMON_ANIM_INDEX: return {pen_blossomon_png, pen_blossomon_png_size, "blossomon"};
            case PEN_BOLTMON_ANIM_INDEX: return {pen_boltmon_png, pen_boltmon_png_size, "boltmon"};
            case PEN_BUBBMON_ANIM_INDEX: return {pen_bubbmon_png, pen_bubbmon_png_size, "bubbmon"};
            case PEN_CANDMON_ANIM_INDEX: return {pen_candmon_png, pen_candmon_png_size, "candmon"};
            case PEN_CAPRIMON_ANIM_INDEX: return {pen_caprimon_png, pen_caprimon_png_size, "caprimon"};
            case PEN_CHOROMON_ANIM_INDEX: return {pen_choromon_png, pen_choromon_png_size, "choromon"};
            case PEN_CLOCKMON_ANIM_INDEX: return {pen_clockmon_png, pen_clockmon_png_size, "clockmon"};
            case PEN_CYBERDRAMON_ANIM_INDEX: return {pen_cyberdramon_png, pen_cyberdramon_png_size, "cyberdramon"};
            case PEN_DAGOMON_ANIM_INDEX: return {pen_dagomon_png, pen_dagomon_png_size, "dagomon"};
            case PEN_DEATH_MERAMON_ANIM_INDEX: return {pen_death_meramon_png, pen_death_meramon_png_size, "death_meramon"};
            case PEN_DELUMON_ANIM_INDEX: return {pen_delumon_png, pen_delumon_png_size, "delumon"};
            case PEN_DOKUGUMON_ANIM_INDEX: return {pen_dokugumon_png, pen_dokugumon_png_size, "dokugumon"};
            case PEN_EBIDRAMON_ANIM_INDEX: return {pen_ebidramon_png, pen_ebidramon_png_size, "ebidramon"};
            case PEN_FANTOMON_ANIM_INDEX: return {pen_fantomon_png, pen_fantomon_png_size, "fantomon"};
            case PEN_FLORAMON_ANIM_INDEX: return {pen_floramon_png, pen_floramon_png_size, "floramon"};
            case PEN_GANIMON_ANIM_INDEX: return {pen_ganimon_png, pen_ganimon_png_size, "ganimon"};
            case PEN_GARUDAMON_ANIM_INDEX: return {pen_garudamon_png, pen_garudamon_png_size, "garudamon"};
            case PEN_GEKOMON_ANIM_INDEX: return {pen_gekomon_png, pen_gekomon_png_size, "gekomon"};
            case PEN_GERBEMON_ANIM_INDEX: return {pen_gerbemon_png, pen_gerbemon_png_size, "gerbemon"};
            case PEN_GESOMON_ANIM_INDEX: return {pen_gesomon_png, pen_gesomon_png_size, "gesomon"};
            case PEN_GOMAMON_ANIM_INDEX: return {pen_gomamon_png, pen_gomamon_png_size, "gomamon"};
            case PEN_GOTTSUMON_ANIM_INDEX: return {pen_gottsumon_png, pen_gottsumon_png_size, "gottsumon"};
            case PEN_GRIFFOMON_ANIM_INDEX: return {pen_griffomon_png, pen_griffomon_png_size, "griffomon"};
            case PEN_GUARDROMON_ANIM_INDEX: return {pen_guardromon_png, pen_guardromon_png_size, "guardromon"};
            case PEN_HAGURUMON_ANIM_INDEX: return {pen_hagurumon_png, pen_hagurumon_png_size, "hagurumon"};
            case PEN_HANGYMON_ANIM_INDEX: return {pen_hangymon_png, pen_hangymon_png_size, "hangymon"};
            case PEN_HANUMON_ANIM_INDEX: return {pen_hanumon_png, pen_hanumon_png_size, "hanumon"};
            case PEN_HERKULE_KABUTERIMON_ANIM_INDEX: return {pen_herkule_kabuterimon_png, pen_herkule_kabuterimon_png_size, "herkule_kabuterimon"};
            case PEN_HOLY_ANGEMON_ANIM_INDEX: return {pen_holy_angemon_png, pen_holy_angemon_png_size, "holy_angemon"};
            case PEN_HOLYDRAMON_ANIM_INDEX: return {pen_holydramon_png, pen_holydramon_png_size, "holydramon"};
            case PEN_HOUOUMON_ANIM_INDEX: return {pen_hououmon_png, pen_hououmon_png_size, "hououmon"};
            case PEN_IGNAMON_ANIM_INDEX: return {pen_ignamon_png, pen_ignamon_png_size, "ignamon"};
            case PEN_IKKAKUMON_ANIM_INDEX: return {pen_ikkakumon_png, pen_ikkakumon_png_size, "ikkakumon"};
            case PEN_JYAGAMON_ANIM_INDEX: return {pen_jyagamon_png, pen_jyagamon_png_size, "jyagamon"};
            case PEN_JYUREIMON_ANIM_INDEX: return {pen_jyureimon_png, pen_jyureimon_png_size, "jyureimon"};
            case PEN_KIWIMON_ANIM_INDEX: return {pen_kiwimon_png, pen_kiwimon_png_size, "kiwimon"};
            case PEN_KNIGHTMON_ANIM_INDEX: return {pen_knightmon_png, pen_knightmon_png_size, "knightmon"};
            case PEN_KOKUWAMON_ANIM_INDEX: return {pen_kokuwamon_png, pen_kokuwamon_png_size, "kokuwamon"};
            case PEN_LADY_DEVIMON_ANIM_INDEX: return {pen_lady_devimon_png, pen_lady_devimon_png_size, "lady_devimon"};
            case PEN_LILIMON_ANIM_INDEX: return {pen_lilimon_png, pen_lilimon_png_size, "lilimon"};
            case PEN_MAMMON_ANIM_INDEX: return {pen_mammon_png, pen_mammon_png_size, "mammon"};
            case PEN_MARIN_ANGEMON_ANIM_INDEX: return {pen_marin_angemon_png, pen_marin_angemon_png_size, "marin_angemon"};
            case PEN_MARIN_DEVIMON_ANIM_INDEX: return {pen_marin_devimon_png, pen_marin_devimon_png_size, "marin_devimon"};
            case PEN_MECHANORIMON_ANIM_INDEX: return {pen_mechanorimon_png, pen_mechanorimon_png_size, "mechanorimon"};
            case PEN_MEGA_SEADRAMON_ANIM_INDEX: return {pen_mega_seadramon_png, pen_mega_seadramon_png_size, "mega_seadramon"};
            case PEN_METAL_ETEMON_ANIM_INDEX: return {pen_metal_etemon_png, pen_metal_etemon_png_size, "metal_etemon"};
            case PEN_METAL_SEADRAMON_ANIM_INDEX: return {pen_metal_seadramon_png, pen_metal_seadramon_png_size, "metal_seadramon"};
            case PEN_MOCHIMON_ANIM_INDEX: return {pen_mochimon_png, pen_mochimon_png_size, "mochimon"};
            case PEN_MOKUMON_ANIM_INDEX: return {pen_mokumon_png, pen_mokumon_png_size, "mokumon"};
            case PEN_MUSHMON_ANIM_INDEX: return {pen_mushmon_png, pen_mushmon_png_size, "mushmon"};
            case PEN_NYOKIMON_ANIM_INDEX: return {pen_nyokimon_png, pen_nyokimon_png_size, "nyokimon"};
            case PEN_OCTMON_ANIM_INDEX: return {pen_octmon_png, pen_octmon_png_size, "octmon"};
            case PEN_OKUWAMON_ANIM_INDEX: return {pen_okuwamon_png, pen_okuwamon_png_size, "okuwamon"};
            case PEN_OTAMAMON_ANIM_INDEX: return {pen_otamamon_png, pen_otamamon_png_size, "otamamon"};
            case PEN_PETI_MERAMON_ANIM_INDEX: return {pen_peti_meramon_png, pen_peti_meramon_png_size, "peti_meramon"};
            case PEN_PICO_DEVIMON_ANIM_INDEX: return {pen_pico_devimon_png, pen_pico_devimon_png_size, "pico_devimon"};
            case PEN_PIEMON_ANIM_INDEX: return {pen_piemon_png, pen_piemon_png_size, "piemon"};
            case PEN_PLESIOMON_ANIM_INDEX: return {pen_plesiomon_png, pen_plesiomon_png_size, "plesiomon"};
            case PEN_PUKUMON_ANIM_INDEX: return {pen_pukumon_png, pen_pukumon_png_size, "pukumon"};
            case PEN_PUMPMON_ANIM_INDEX: return {pen_pumpmon_png, pen_pumpmon_png_size, "pumpmon"};
            case PEN_PYOCOMON_ANIM_INDEX: return {pen_pyocomon_png, pen_pyocomon_png_size, "pyocomon"};
            case PEN_RAKAMON_ANIM_INDEX: return {pen_rakamon_png, pen_rakamon_png_size, "rakamon"};
            case PEN_RED_VEGIMON_ANIM_INDEX: return {pen_red_vegimon_png, pen_red_vegimon_png_size, "red_vegimon"};
            case PEN_REVOLMON_ANIM_INDEX: return {pen_revolmon_png, pen_revolmon_png_size, "revolmon"};
            case PEN_ROSEMON_ANIM_INDEX: return {pen_rosemon_png, pen_rosemon_png_size, "rosemon"};
            case PEN_SABER_LEOMON_ANIM_INDEX: return {pen_saber_leomon_png, pen_saber_leomon_png_size, "saber_leomon"};
            case PEN_SHAKOMON_ANIM_INDEX: return {pen_shakomon_png, pen_shakomon_png_size, "shakomon"};
            case PEN_STARMON_ANIM_INDEX: return {pen_starmon_png, pen_starmon_png_size, "starmon"};
            case PEN_TAILMON_ANIM_INDEX: return {pen_tailmon_png, pen_tailmon_png_size, "tailmon"};
            case PEN_TANKMON_ANIM_INDEX: return {pen_tankmon_png, pen_tankmon_png_size, "tankmon"};
            case PEN_TENTOMON_ANIM_INDEX: return {pen_tentomon_png, pen_tentomon_png_size, "tentomon"};
            case PEN_THUNDERBALLMON_ANIM_INDEX: return {pen_thunderballmon_png, pen_thunderballmon_png_size, "thunderballmon"};
            case PEN_TOGEMON_ANIM_INDEX: return {pen_togemon_png, pen_togemon_png_size, "togemon"};
            case PEN_TONOSAMA_GEKOMON_ANIM_INDEX: return {pen_tonosama_gekomon_png, pen_tonosama_gekomon_png_size, "tonosama_gekomon"};
            case PEN_TORTAMON_ANIM_INDEX: return {pen_tortamon_png, pen_tortamon_png_size, "tortamon"};
            case PEN_TOY_AGUMON_ANIM_INDEX: return {pen_toy_agumon_png, pen_toy_agumon_png_size, "toy_agumon"};
            case PEN_TRICERAMON_ANIM_INDEX: return {pen_triceramon_png, pen_triceramon_png_size, "triceramon"};
            case PEN_V_DRAMON_ANIM_INDEX: return {pen_v_dramon_png, pen_v_dramon_png_size, "v_dramon"};
            case PEN_VEMDEMON_ANIM_INDEX: return {pen_vemdemon_png, pen_vemdemon_png_size, "vemdemon"};
            case PEN_VENOM_VAMDEMON_ANIM_INDEX: return {pen_venom_vamdemon_png, pen_venom_vamdemon_png_size, "venom_vamdemon"};
            case PEN_WARU_MOZAEMON_ANIM_INDEX: return {pen_waru_mozaemon_png, pen_waru_mozaemon_png_size, "waru_mozaemon"};
            case PEN_WIZARMON_ANIM_INDEX: return {pen_wizarmon_png, pen_wizarmon_png_size, "wizarmon"};
            case PEN_WOODMON_ANIM_INDEX: return {pen_woodmon_png, pen_woodmon_png_size, "woodmon"};
            case PEN_ZUDOMOM_ANIM_INDEX: return {pen_zudomom_png, pen_zudomom_png_size, "zudomom"};
            default: return { nullptr, 0, "" };
        }
        return { nullptr, 0, "" };
    }
}

