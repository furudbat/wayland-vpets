#include "embedded_assets/embedded_image.h"
#include "embedded_assets/dm/dm.hpp"
#include "embedded_assets/dm/dm_images.h"
#include "embedded_assets/dm/dm.h"

namespace bongocat::assets {
    embedded_image_t get_dm_sprite_sheet(size_t i) {
        using namespace assets;
        switch (i) {
            case DM_AGUMON_ANIM_INDEX: return {dm_agumon_png, dm_agumon_png_size, "agumon"};
            case DM_AIRDRAMON_ANIM_INDEX: return {dm_airdramon_png, dm_airdramon_png_size, "airdramon"};
            case DM_ANDROMON_ANIM_INDEX: return {dm_andromon_png, dm_andromon_png_size, "andromon"};
            case DM_ANGEMON_ANIM_INDEX: return {dm_angemon_png, dm_angemon_png_size, "angemon"};
            case DM_BAKEMON_ANIM_INDEX: return {dm_bakemon_png, dm_bakemon_png_size, "bakemon"};
            case DM_BETAMON_ANIM_INDEX: return {dm_betamon_png, dm_betamon_png_size, "betamon"};
            case DM_BIRDRAMON_ANIM_INDEX: return {dm_birdramon_png, dm_birdramon_png_size, "birdramon"};
            case DM_BOTAMON_ANIM_INDEX: return {dm_botamon_png, dm_botamon_png_size, "botamon"};
            case DM_CENTALMON_ANIM_INDEX: return {dm_centalmon_png, dm_centalmon_png_size, "centalmon"};
            case DM_COCKATRIMON_ANIM_INDEX: return {dm_cockatrimon_png, dm_cockatrimon_png_size, "cockatrimon"};
            case DM_COELAMON_ANIM_INDEX: return {dm_coelamon_png, dm_coelamon_png_size, "coelamon"};
            case DM_CORONAMON_ANIM_INDEX: return {dm_coronamon_png, dm_coronamon_png_size, "coronamon"};
            case DM_CYCLOMON_ANIM_INDEX: return {dm_cyclomon_png, dm_cyclomon_png_size, "cyclomon"};
            case DM_DARK_TYRANOMON_ANIM_INDEX: return {dm_dark_tyranomon_png, dm_dark_tyranomon_png_size, "dark_tyranomon"};
            case DM_DELTAMON_ANIM_INDEX: return {dm_deltamon_png, dm_deltamon_png_size, "deltamon"};
            case DM_DEVIDRAMON_ANIM_INDEX: return {dm_devidramon_png, dm_devidramon_png_size, "devidramon"};
            case DM_DEVIMON_ANIM_INDEX: return {dm_devimon_png, dm_devimon_png_size, "devimon"};
            case DM_DIGITAMAMON_ANIM_INDEX: return {dm_digitamamon_png, dm_digitamamon_png_size, "digitamamon"};
            case DM_DRIMOGEMON_ANIM_INDEX: return {dm_drimogemon_png, dm_drimogemon_png_size, "drimogemon"};
            case DM_ELECMON_ANIM_INDEX: return {dm_elecmon_png, dm_elecmon_png_size, "elecmon"};
            case DM_ETEMON_ANIM_INDEX: return {dm_etemon_png, dm_etemon_png_size, "etemon"};
            case DM_EX_TYRANOMON_ANIM_INDEX: return {dm_ex_tyranomon_png, dm_ex_tyranomon_png_size, "ex_tyranomon"};
            case DM_FLYMON_ANIM_INDEX: return {dm_flymon_png, dm_flymon_png_size, "flymon"};
            case DM_GABUMON_ANIM_INDEX: return {dm_gabumon_png, dm_gabumon_png_size, "gabumon"};
            case DM_GARURUMON_ANIM_INDEX: return {dm_garurumon_png, dm_garurumon_png_size, "garurumon"};
            case DM_GAZIMON_ANIM_INDEX: return {dm_gazimon_png, dm_gazimon_png_size, "gazimon"};
            case DM_GIROMON_ANIM_INDEX: return {dm_giromon_png, dm_giromon_png_size, "giromon"};
            case DM_GIZAMON_ANIM_INDEX: return {dm_gizamon_png, dm_gizamon_png_size, "gizamon"};
            case DM_GREYMON_ANIM_INDEX: return {dm_greymon_png, dm_greymon_png_size, "greymon"};
            case DM_KABUTERIMON_ANIM_INDEX: return {dm_kabuterimon_png, dm_kabuterimon_png_size, "kabuterimon"};
            case DM_KOROMON_ANIM_INDEX: return {dm_koromon_png, dm_koromon_png_size, "koromon"};
            case DM_KUNEMON_ANIM_INDEX: return {dm_kunemon_png, dm_kunemon_png_size, "kunemon"};
            case DM_KUWAGAMON_ANIM_INDEX: return {dm_kuwagamon_png, dm_kuwagamon_png_size, "kuwagamon"};
            case DM_LEOMON_ANIM_INDEX: return {dm_leomon_png, dm_leomon_png_size, "leomon"};
            case DM_MAMEMON_ANIM_INDEX: return {dm_mamemon_png, dm_mamemon_png_size, "mamemon"};
            case DM_MEGADRAMON_ANIM_INDEX: return {dm_megadramon_png, dm_megadramon_png_size, "megadramon"};
            case DM_MERAMON_ANIM_INDEX: return {dm_meramon_png, dm_meramon_png_size, "meramon"};
            case DM_METAL_GREYMON_ANIM_INDEX: return {dm_metal_greymon_png, dm_metal_greymon_png_size, "metal_greymon"};
            case DM_METAL_MAMEMON_ANIM_INDEX: return {dm_metal_mamemon_png, dm_metal_mamemon_png_size, "metal_mamemon"};
            case DM_METAL_TYRANOMON_ANIM_INDEX: return {dm_metal_tyranomon_png, dm_metal_tyranomon_png_size, "metal_tyranomon"};
            case DM_MOJYAMON_ANIM_INDEX: return {dm_mojyamon_png, dm_mojyamon_png_size, "mojyamon"};
            case DM_MONOCHROMON_ANIM_INDEX: return {dm_monochromon_png, dm_monochromon_png_size, "monochromon"};
            case DM_MONZAEMON_ANIM_INDEX: return {dm_monzaemon_png, dm_monzaemon_png_size, "monzaemon"};
            case DM_NANIMON_ANIM_INDEX: return {dm_nanimon_png, dm_nanimon_png_size, "nanimon"};
            case DM_NANOMON_ANIM_INDEX: return {dm_nanomon_png, dm_nanomon_png_size, "nanomon"};
            case DM_NUMEMON_ANIM_INDEX: return {dm_numemon_png, dm_numemon_png_size, "numemon"};
            case DM_OGREMON_ANIM_INDEX: return {dm_ogremon_png, dm_ogremon_png_size, "ogremon"};
            case DM_PAGUMON_ANIM_INDEX: return {dm_pagumon_png, dm_pagumon_png_size, "pagumon"};
            case DM_PALMON_ANIM_INDEX: return {dm_palmon_png, dm_palmon_png_size, "palmon"};
            case DM_PATAMON_ANIM_INDEX: return {dm_patamon_png, dm_patamon_png_size, "patamon"};
            case DM_PICCOLOMON_ANIM_INDEX: return {dm_piccolomon_png, dm_piccolomon_png_size, "piccolomon"};
            case DM_PIYOMON_ANIM_INDEX: return {dm_piyomon_png, dm_piyomon_png_size, "piyomon"};
            case DM_POYOMON_ANIM_INDEX: return {dm_poyomon_png, dm_poyomon_png_size, "poyomon"};
            case DM_PUNIMON_ANIM_INDEX: return {dm_punimon_png, dm_punimon_png_size, "punimon"};
            case DM_RAREMON_ANIM_INDEX: return {dm_raremon_png, dm_raremon_png_size, "raremon"};
            case DM_SCUMON_ANIM_INDEX: return {dm_scumon_png, dm_scumon_png_size, "scumon"};
            case DM_SEADRAMON_ANIM_INDEX: return {dm_seadramon_png, dm_seadramon_png_size, "seadramon"};
            case DM_SHELLMON_ANIM_INDEX: return {dm_shellmon_png, dm_shellmon_png_size, "shellmon"};
            case DM_SKULL_GREYMON_ANIM_INDEX: return {dm_skull_greymon_png, dm_skull_greymon_png_size, "skull_greymon"};
            case DM_TANEMON_ANIM_INDEX: return {dm_tanemon_png, dm_tanemon_png_size, "tanemon"};
            case DM_TOKOMON_ANIM_INDEX: return {dm_tokomon_png, dm_tokomon_png_size, "tokomon"};
            case DM_TUNOMON_ANIM_INDEX: return {dm_tunomon_png, dm_tunomon_png_size, "tunomon"};
            case DM_TUSKMON_ANIM_INDEX: return {dm_tuskmon_png, dm_tuskmon_png_size, "tuskmon"};
            case DM_TYRANOMON_ANIM_INDEX: return {dm_tyranomon_png, dm_tyranomon_png_size, "tyranomon"};
            case DM_UNIMON_ANIM_INDEX: return {dm_unimon_png, dm_unimon_png_size, "unimon"};
            case DM_VADEMON_ANIM_INDEX: return {dm_vademon_png, dm_vademon_png_size, "vademon"};
            case DM_VEGIMON_ANIM_INDEX: return {dm_vegimon_png, dm_vegimon_png_size, "vegimon"};
            case DM_WHAMON_ANIM_INDEX: return {dm_whamon_png, dm_whamon_png_size, "whamon"};
            case DM_YUKIDARUMON_ANIM_INDEX: return {dm_yukidarumon_png, dm_yukidarumon_png_size, "yukidarumon"};
            case DM_YURAMON_ANIM_INDEX: return {dm_yuramon_png, dm_yuramon_png_size, "yuramon"};
            default: return {};
        }
        return {};
    }
}
