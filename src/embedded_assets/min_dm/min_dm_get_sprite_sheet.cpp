#include "embedded_assets/embedded_image.h"
#include "embedded_assets/min_dm/min_dm.hpp"
#include "embedded_assets/min_dm/min_dm_images.h"
#include "embedded_assets/min_dm/min_dm_sprite.h"

namespace bongocat::assets {
    embedded_image_t get_min_dm_sprite_sheet(size_t i) {
        using namespace assets;
        switch (i) {
            case DM_BOTAMON_ANIM_INDEX: return {dm_botamon_png, dm_botamon_png_size, "botamon"};
            case DM_KOROMON_ANIM_INDEX: return {dm_koromon_png, dm_koromon_png_size, "koromon"};
            case DM_AGUMON_ANIM_INDEX: return {dm_agumon_png, dm_agumon_png_size, "agumon"};
            case DM_BETAMON_ANIM_INDEX: return {dm_betamon_png, dm_betamon_png_size, "betamon"};
            case DM_GREYMON_ANIM_INDEX: return {dm_greymon_png, dm_greymon_png_size, "greymon"};
            case DM_TYRANOMON_ANIM_INDEX: return {dm_tyranomon_png, dm_tyranomon_png_size, "tyranomon"};
            case DM_DEVIMON_ANIM_INDEX: return {dm_devimon_png, dm_devimon_png_size, "devimon"};
            case DM_MERAMON_ANIM_INDEX: return {dm_meramon_png, dm_meramon_png_size, "meramon"};
            case DM_AIRDRAMON_ANIM_INDEX: return {dm_airdramon_png, dm_airdramon_png_size, "airdramon"};
            case DM_SEADRAMON_ANIM_INDEX: return {dm_seadramon_png, dm_seadramon_png_size, "seadramon"};
            case DM_NUMEMON_ANIM_INDEX: return {dm_numemon_png, dm_numemon_png_size, "numemon"};
            case DM_METAL_GREYMON_ANIM_INDEX: return {dm_metal_greymon_png, dm_metal_greymon_png_size, "metal_greymon"};
            case DM_MAMEMON_ANIM_INDEX: return {dm_mamemon_png, dm_mamemon_png_size, "mamemon"};
            case DM_MONZAEMON_ANIM_INDEX: return {dm_monzaemon_png, dm_monzaemon_png_size, "monzaemon"};
            default: return { nullptr, 0, "" };
        }
        return { nullptr, 0, "" };
    }
}