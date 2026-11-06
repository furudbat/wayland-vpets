#include "embedded_assets/embedded_image.h"
#include "embedded_assets/min_dm/min_dm.hpp"
#include "embedded_assets/min_dm/min_dm_images.h"
#include "embedded_assets/min_dm/min_dm_sprite.h"

namespace bongocat::assets {
    static const embedded_image_t min_dm_images_table[] = {
    {min_dm_botamon_png, min_dm_botamon_png_size, "botamon"},
    {min_dm_koromon_png, min_dm_koromon_png_size, "koromon"},
    {min_dm_agumon_png, min_dm_agumon_png_size, "agumon"},
    {min_dm_betamon_png, min_dm_betamon_png_size, "betamon"},
    {min_dm_greymon_png, min_dm_greymon_png_size, "greymon"},
    {min_dm_tyranomon_png, min_dm_tyranomon_png_size, "tyranomon"},
    {min_dm_devimon_png, min_dm_devimon_png_size, "devimon"},
    {min_dm_meramon_png, min_dm_meramon_png_size, "meramon"},
    {min_dm_airdramon_png, min_dm_airdramon_png_size, "airdramon"},
    {min_dm_seadramon_png, min_dm_seadramon_png_size, "seadramon"},
    {min_dm_numemon_png, min_dm_numemon_png_size, "numemon"},
    {min_dm_metal_greymon_png, min_dm_metal_greymon_png_size, "metal_greymon"},
    {min_dm_mamemon_png, min_dm_mamemon_png_size, "mamemon"},
{min_dm_monzaemon_png, min_dm_monzaemon_png_size, "monzaemon"},
};
embedded_image_t get_min_dm_sprite_sheet(size_t index) {
  assert(LEN_ARRAY(min_dm_images_table) == MIN_DM_ANIM_COUNT);
  assert(index < MIN_DM_ANIM_COUNT);
  return min_dm_images_table[index];
}
}

