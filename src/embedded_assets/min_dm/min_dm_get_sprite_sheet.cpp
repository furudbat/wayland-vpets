#include "embedded_assets/embedded_image.h"
#include "embedded_assets/min_dm/min_dm.hpp"
#include "embedded_assets/min_dm/min_dm_images.h"
#include "embedded_assets/min_dm/min_dm_sprite.h"

namespace bongocat::assets {
    static const embedded_image_t min_dm_images_table[] ASSETS_IMAGES_TABLE_SECTION = {
    {dm_botamon_png, dm_botamon_png_size, DM_BOTAMON_NAME},
    {dm_koromon_png, dm_koromon_png_size, "koromon"},
    {dm_agumon_png, dm_agumon_png_size, "agumon"},
    {dm_betamon_png, dm_betamon_png_size, "betamon"},
    {dm_greymon_png, dm_greymon_png_size, "greymon"},
    {dm_tyranomon_png, dm_tyranomon_png_size, "tyranomon"},
    {dm_devimon_png, dm_devimon_png_size, "devimon"},
    {dm_meramon_png, dm_meramon_png_size, "meramon"},
    {dm_airdramon_png, dm_airdramon_png_size, "airdramon"},
    {dm_seadramon_png, dm_seadramon_png_size, "seadramon"},
    {dm_numemon_png, dm_numemon_png_size, "numemon"},
    {dm_metal_greymon_png, dm_metal_greymon_png_size, "metal_greymon"},
    {dm_mamemon_png, dm_mamemon_png_size, "mamemon"},
{dm_monzaemon_png, dm_monzaemon_png_size, "monzaemon"},
};
embedded_image_t get_min_dm_sprite_sheet(size_t index) {
  assert(LEN_ARRAY(min_dm_images_table) == MIN_DM_ANIM_COUNT);
  assert(index < MIN_DM_ANIM_COUNT);
  return min_dm_images_table[index];
}
}

