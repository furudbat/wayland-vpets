#include "embedded_assets/bongocat/bongocat.h"
#include "embedded_assets/bongocat/bongocat_images.h"
#include "embedded_assets/embedded_image.h"
#include "utils/system_memory.h"

namespace bongocat::assets {
    static const embedded_image_t bongocat_images_table[] ASSETS_TABLE_SECTION = {
    {bongo_cat_both_up_png, bongo_cat_both_up_png_size, "bongo-cat-both-up"},
    {bongo_cat_left_down_png, bongo_cat_left_down_png_size, "bongo-cat-left-down"},
    {bongo_cat_right_down_png, bongo_cat_right_down_png_size, "bongo-cat-right-down"},
    {bongo_cat_both_down_png, bongo_cat_both_down_png_size, "bongo-cat-both-down"},
    {bongo_cat_sleeping_png, bongo_cat_sleeping_png_size, "bongo-cat-sleeping"},
    };
embedded_image_t get_bongocat_sprite(size_t index) {
  assert(LEN_ARRAY(bongocat_images_table) == BONGOCAT_EMBEDDED_IMAGES_COUNT);
  assert(index < BONGOCAT_EMBEDDED_IMAGES_COUNT);
  return bongocat_images_table[index];
}
}  // namespace bongocat::assets