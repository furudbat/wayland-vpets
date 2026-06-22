#include "embedded_assets/embedded_image.h"
#include "embedded_assets/misc/misc.hpp"
#include "embedded_assets/misc/misc_images.h"
#include "embedded_assets/misc/misc_sprite.h"

namespace bongocat::assets {

static const custom_animation_settings_t misc_settings_table[] ASSETS_SPRITE_SETTINGS_SECTION = {
        MISC_NEKO_SPRITE_SHEET_SETTINGS,
};
static const embedded_image_t misc_images_table[] ASSETS_IMAGES_TABLE_SECTION = {
  {misc_neko_png, misc_neko_png_size, MISC_NEKO_NAME},
};

embedded_image_t get_misc_sprite_sheet([[maybe_unused]] size_t índex) {
  assert(LEN_ARRAY(misc_images_table) == MISC_ANIM_COUNT);
  //assert(index < MISC_ANIM_COUNT);
  //return misc_images_table[index];
  return *misc_images_table;
}
custom_animation_settings_t get_misc_sprite_sheet_columns([[maybe_unused]] size_t índex) {
  assert(LEN_ARRAY(misc_settings_table) == MISC_ANIM_COUNT);
  //assert(index < MISC_ANIM_COUNT);
  //return misc_settings_table[index];
  return *misc_settings_table;
}
}  // namespace bongocat::assets