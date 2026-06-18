#include "embedded_assets/bongocat/bongocat.h"
#include "embedded_assets/bongocat/bongocat_images.h"
#include "embedded_assets/embedded_image.h"
#include "utils/system_memory.h"

namespace bongocat::assets {
    static const embedded_image_t bongocat_images_table[] = {
    {bongo_cat_both_up_svg, bongo_cat_both_up_svg_size, "bongo-cat-both-up"},
    {bongo_cat_left_down_svg, bongo_cat_left_down_svg_size, "bongo-cat-left-down"},
    {bongo_cat_right_down_svg, bongo_cat_right_down_svg_size, "bongo-cat-right-down"},
    {bongo_cat_both_down_svg, bongo_cat_both_down_svg_size, "bongo-cat-both-down"},
    {bongo_cat_sleeping_svg, bongo_cat_sleeping_svg_size, "bongo-cat-sleeping"},
    };
embedded_image_t get_bongocat_sprite_svg(size_t index) {
  assert(LEN_ARRAY(bongocat_images_table) == BONGOCAT_EMBEDDED_IMAGES_COUNT);
  assert(index < BONGOCAT_EMBEDDED_IMAGES_COUNT);
  return bongocat_images_table[index];
}

void asset_unload_bongocat_svg() {
  platform::details::asset_unload(bongo_cat_both_up_svg, bongo_cat_both_up_svg_size);
  platform::details::asset_unload(bongo_cat_left_down_svg, bongo_cat_left_down_svg_size);
  platform::details::asset_unload(bongo_cat_right_down_svg, bongo_cat_right_down_svg_size);
  platform::details::asset_unload(bongo_cat_both_down_svg, bongo_cat_both_down_svg_size);
  platform::details::asset_unload(bongo_cat_sleeping_svg, bongo_cat_sleeping_svg_size);
}
}  // namespace bongocat::assets