#include "embedded_assets/embedded_image.h"
#include "embedded_assets/dmc/dmc.hpp"
#include "embedded_assets/dmc/dmc_images.h"
#include "embedded_assets/dmc/dmc_sprite.h"

namespace bongocat::assets {
    embedded_image_t get_dmc_sprite_sheet(size_t index) {
        switch (index) {
            case DMC_AGUMON_ANIM_INDEX: return {dmc_agumon_png, dmc_agumon_png_size, "agumon"};
            case DMC_AIRDRAMON_ANIM_INDEX: return {dmc_airdramon_png, dmc_airdramon_png_size, "airdramon"};
            case DMC_ANDROMON_ANIM_INDEX: return {dmc_andromon_png, dmc_andromon_png_size, "andromon"};
            case DMC_ANGEMON_ANIM_INDEX: return {dmc_angemon_png, dmc_angemon_png_size, "angemon"};
            case DMC_BABYDMON_ANIM_INDEX: return {dmc_babydmon_png, dmc_babydmon_png_size, "babydmon"};
            case DMC_BAKEMON_ANIM_INDEX: return {dmc_bakemon_png, dmc_bakemon_png_size, "bakemon"};
            case DMC_BANCHO_MAMEMON_ANIM_INDEX: return {dmc_bancho_mamemon_png, dmc_bancho_mamemon_png_size, "bancho_mamemon"};
            case DMC_BETAMON_ANIM_INDEX: return {dmc_betamon_png, dmc_betamon_png_size, "betamon"};
            case DMC_BIRDRAMON_ANIM_INDEX: return {dmc_birdramon_png, dmc_birdramon_png_size, "birdramon"};
            case DMC_BLITZ_GREYMON_ANIM_INDEX: return {dmc_blitz_greymon_png, dmc_blitz_greymon_png_size, "blitz_greymon"};
            case DMC_BOTAMON_ANIM_INDEX: return {dmc_botamon_png, dmc_botamon_png_size, "botamon"};
            case DMC_CENTALMON_ANIM_INDEX: return {dmc_centalmon_png, dmc_centalmon_png_size, "centalmon"};
            case DMC_COCKATRIMON_ANIM_INDEX: return {dmc_cockatrimon_png, dmc_cockatrimon_png_size, "cockatrimon"};
            case DMC_COELAMON_ANIM_INDEX: return {dmc_coelamon_png, dmc_coelamon_png_size, "coelamon"};
            case DMC_CORONAMON_ANIM_INDEX: return {dmc_coronamon_png, dmc_coronamon_png_size, "coronamon"};
            case DMC_CRES_GARURUMON_ANIM_INDEX: return {dmc_cres_garurumon_png, dmc_cres_garurumon_png_size, "cres_garurumon"};
            case DMC_CYCLOMON_ANIM_INDEX: return {dmc_cyclomon_png, dmc_cyclomon_png_size, "cyclomon"};
            case DMC_DARK_TYRANOMON_ANIM_INDEX: return {dmc_dark_tyranomon_png, dmc_dark_tyranomon_png_size, "dark_tyranomon"};
            case DMC_DELTAMON_ANIM_INDEX: return {dmc_deltamon_png, dmc_deltamon_png_size, "deltamon"};
            case DMC_DEVIDRAMON_ANIM_INDEX: return {dmc_devidramon_png, dmc_devidramon_png_size, "devidramon"};
            case DMC_DEVIMON_ANIM_INDEX: return {dmc_devimon_png, dmc_devimon_png_size, "devimon"};
            case DMC_DIGITAMAMON_ANIM_INDEX: return {dmc_digitamamon_png, dmc_digitamamon_png_size, "digitamamon"};
            case DMC_DRIMOGEMON_ANIM_INDEX: return {dmc_drimogemon_png, dmc_drimogemon_png_size, "drimogemon"};
            case DMC_ELECMON_ANIM_INDEX: return {dmc_elecmon_png, dmc_elecmon_png_size, "elecmon"};
            case DMC_ETEMON_ANIM_INDEX: return {dmc_etemon_png, dmc_etemon_png_size, "etemon"};
            case DMC_EX_TYRANOMON_ANIM_INDEX: return {dmc_ex_tyranomon_png, dmc_ex_tyranomon_png_size, "ex_tyranomon"};
            case DMC_FLYMON_ANIM_INDEX: return {dmc_flymon_png, dmc_flymon_png_size, "flymon"};
            case DMC_GABUMON_ANIM_INDEX: return {dmc_gabumon_png, dmc_gabumon_png_size, "gabumon"};
            case DMC_GARURUMON_ANIM_INDEX: return {dmc_garurumon_png, dmc_garurumon_png_size, "garurumon"};
            case DMC_GAZIMON_ANIM_INDEX: return {dmc_gazimon_png, dmc_gazimon_png_size, "gazimon"};
            case DMC_GIROMON_ANIM_INDEX: return {dmc_giromon_png, dmc_giromon_png_size, "giromon"};
            case DMC_GIZAMON_ANIM_INDEX: return {dmc_gizamon_png, dmc_gizamon_png_size, "gizamon"};
            case DMC_GREYMON_ANIM_INDEX: return {dmc_greymon_png, dmc_greymon_png_size, "greymon"};
            case DMC_HI_ANDROMON_ANIM_INDEX: return {dmc_hi_andromon_png, dmc_hi_andromon_png_size, "hi_andromon"};
            case DMC_KABUTERIMON_ANIM_INDEX: return {dmc_kabuterimon_png, dmc_kabuterimon_png_size, "kabuterimon"};
            case DMC_KOROMON_ANIM_INDEX: return {dmc_koromon_png, dmc_koromon_png_size, "koromon"};
            case DMC_KUNEMON_ANIM_INDEX: return {dmc_kunemon_png, dmc_kunemon_png_size, "kunemon"};
            case DMC_KUWAGAMON_ANIM_INDEX: return {dmc_kuwagamon_png, dmc_kuwagamon_png_size, "kuwagamon"};
            case DMC_LEOMON_ANIM_INDEX: return {dmc_leomon_png, dmc_leomon_png_size, "leomon"};
            case DMC_MAMEMON_ANIM_INDEX: return {dmc_mamemon_png, dmc_mamemon_png_size, "mamemon"};
            case DMC_MEGADRAMON_ANIM_INDEX: return {dmc_megadramon_png, dmc_megadramon_png_size, "megadramon"};
            case DMC_MERAMON_ANIM_INDEX: return {dmc_meramon_png, dmc_meramon_png_size, "meramon"};
            case DMC_METAL_GARURUMON_ANIM_INDEX: return {dmc_metal_garurumon_png, dmc_metal_garurumon_png_size, "metal_garurumon"};
            case DMC_METAL_GREYMON_ANIM_INDEX: return {dmc_metal_greymon_png, dmc_metal_greymon_png_size, "metal_greymon"};
            case DMC_METAL_GREYMON_VIRUS_ANIM_INDEX: return {dmc_metal_greymon_virus_png, dmc_metal_greymon_virus_png_size, "metal_greymon_virus"};
            case DMC_METAL_MAMEMON_ANIM_INDEX: return {dmc_metal_mamemon_png, dmc_metal_mamemon_png_size, "metal_mamemon"};
            case DMC_METAL_TYRANOMON_ANIM_INDEX: return {dmc_metal_tyranomon_png, dmc_metal_tyranomon_png_size, "metal_tyranomon"};
            case DMC_MOJYMON_ANIM_INDEX: return {dmc_mojymon_png, dmc_mojymon_png_size, "mojymon"};
            case DMC_MONOCHROMON_ANIM_INDEX: return {dmc_monochromon_png, dmc_monochromon_png_size, "monochromon"};
            case DMC_MOZAEMON_ANIM_INDEX: return {dmc_mozaemon_png, dmc_mozaemon_png_size, "mozaemon"};
            case DMC_MUGENDRAMON_ANIM_INDEX: return {dmc_mugendramon_png, dmc_mugendramon_png_size, "mugendramon"};
            case DMC_NANIMON_ANIM_INDEX: return {dmc_nanimon_png, dmc_nanimon_png_size, "nanimon"};
            case DMC_NANOMON_ANIM_INDEX: return {dmc_nanomon_png, dmc_nanomon_png_size, "nanomon"};
            case DMC_NUMEMON_ANIM_INDEX: return {dmc_numemon_png, dmc_numemon_png_size, "numemon"};
            case DMC_OMEGAMON_ALTER_S_ANIM_INDEX: return {dmc_omegamon_alter_s_png, dmc_omegamon_alter_s_png_size, "omegamon_alter_s"};
            case DMC_OMEGAMON_ANIM_INDEX: return {dmc_omegamon_png, dmc_omegamon_png_size, "omegamon"};
            case DMC_ORGEMON_ANIM_INDEX: return {dmc_orgemon_png, dmc_orgemon_png_size, "orgemon"};
            case DMC_PAGUMON_ANIM_INDEX: return {dmc_pagumon_png, dmc_pagumon_png_size, "pagumon"};
            case DMC_PALMON_ANIM_INDEX: return {dmc_palmon_png, dmc_palmon_png_size, "palmon"};
            case DMC_PATAMON_ANIM_INDEX: return {dmc_patamon_png, dmc_patamon_png_size, "patamon"};
            case DMC_PETITMON_ANIM_INDEX: return {dmc_petitmon_png, dmc_petitmon_png_size, "petitmon"};
            case DMC_PICCOLOMON_ANIM_INDEX: return {dmc_piccolomon_png, dmc_piccolomon_png_size, "piccolomon"};
            case DMC_PIYOMON_ANIM_INDEX: return {dmc_piyomon_png, dmc_piyomon_png_size, "piyomon"};
            case DMC_POYOMON_ANIM_INDEX: return {dmc_poyomon_png, dmc_poyomon_png_size, "poyomon"};
            case DMC_PUNIMON_ANIM_INDEX: return {dmc_punimon_png, dmc_punimon_png_size, "punimon"};
            case DMC_RAIDENMON_ANIM_INDEX: return {dmc_raidenmon_png, dmc_raidenmon_png_size, "raidenmon"};
            case DMC_RAREMON_ANIM_INDEX: return {dmc_raremon_png, dmc_raremon_png_size, "raremon"};
            case DMC_RUST_TYRANOMON_ANIM_INDEX: return {dmc_rust_tyranomon_png, dmc_rust_tyranomon_png_size, "rust_tyranomon"};
            case DMC_SCUMON_ANIM_INDEX: return {dmc_scumon_png, dmc_scumon_png_size, "scumon"};
            case DMC_SEADRAMON_ANIM_INDEX: return {dmc_seadramon_png, dmc_seadramon_png_size, "seadramon"};
            case DMC_SHELLMON_ANIM_INDEX: return {dmc_shellmon_png, dmc_shellmon_png_size, "shellmon"};
            case DMC_SHIN_MONZAEMON_ANIM_INDEX: return {dmc_shin_monzaemon_png, dmc_shin_monzaemon_png_size, "shin_monzaemon"};
            case DMC_SKULL_GREYMON_ANIM_INDEX: return {dmc_skull_greymon_png, dmc_skull_greymon_png_size, "skull_greymon"};
            case DMC_SKULL_MAMMON_ANIM_INDEX: return {dmc_skull_mammon_png, dmc_skull_mammon_png_size, "skull_mammon"};
            case DMC_TANEMON_ANIM_INDEX: return {dmc_tanemon_png, dmc_tanemon_png_size, "tanemon"};
            case DMC_TITAMON_ANIM_INDEX: return {dmc_titamon_png, dmc_titamon_png_size, "titamon"};
            case DMC_TOKOMON_ANIM_INDEX: return {dmc_tokomon_png, dmc_tokomon_png_size, "tokomon"};
            case DMC_TSUNOMON_ANIM_INDEX: return {dmc_tsunomon_png, dmc_tsunomon_png_size, "tsunomon"};
            case DMC_TUSKMON_ANIM_INDEX: return {dmc_tuskmon_png, dmc_tuskmon_png_size, "tuskmon"};
            case DMC_TYRANOMON_ANIM_INDEX: return {dmc_tyranomon_png, dmc_tyranomon_png_size, "tyranomon"};
            case DMC_UNIMON_ANIM_INDEX: return {dmc_unimon_png, dmc_unimon_png_size, "unimon"};
            case DMC_VADEMON_ANIM_INDEX: return {dmc_vademon_png, dmc_vademon_png_size, "vademon"};
            case DMC_VEGIMON_ANIM_INDEX: return {dmc_vegimon_png, dmc_vegimon_png_size, "vegimon"};
            case DMC_WAR_GREYMON_ANIM_INDEX: return {dmc_war_greymon_png, dmc_war_greymon_png_size, "war_greymon"};
            case DMC_WERE_GARURUMON_ANIM_INDEX: return {dmc_were_garurumon_png, dmc_were_garurumon_png_size, "were_garurumon"};
            case DMC_WHAMON_ANIM_INDEX: return {dmc_whamon_png, dmc_whamon_png_size, "whamon"};
            case DMC_YUKIDARUMON_ANIM_INDEX: return {dmc_yukidarumon_png, dmc_yukidarumon_png_size, "yukidarumon"};
            case DMC_YURAMON_ANIM_INDEX: return {dmc_yuramon_png, dmc_yuramon_png_size, "yuramon"};
            case DMC_ZURUMON_ANIM_INDEX: return {dmc_zurumon_png, dmc_zurumon_png_size, "zurumon"};
            default: return { nullptr, 0, "" };
        }
        return { nullptr, 0, "" };
    }
}

