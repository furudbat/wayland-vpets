#include "load_images_misc.h"
#include "misc_images.h"
#include "core/bongocat.h"
#include "embedded_assets/embedded_image.h"
#include "embedded_assets/misc/misc.hpp"
#include "embedded_assets/misc/misc_sprite.h"
#include "graphics/animation_thread_context.h"
#include "graphics/sprite_sheet.h"
#include "image_loader/custom/load_custom.h"

namespace bongocat::animation {

static constexpr assets::custom_animation_settings_t misc_settings_table[] = {
  assets::MISC_NEKO_SPRITE_SHEET_SETTINGS,
};

static const unsigned char* misc_pngs_table[] = {
  misc_neko_png,
};
static const size_t misc_png_sizes_table[] = {
  misc_neko_png_size,
};
static const char* misc_names_table[] = {
  "neko",
};

created_result_t<custom_sprite_sheet_t> load_misc_sprite_sheet(const animation_thread_context_t& ctx, size_t index) {
  using namespace assets;
  assert(LEN_ARRAY(misc_settings_table) == MISC_ANIM_COUNT);
  assert(LEN_ARRAY(misc_pngs_table) == MISC_ANIM_COUNT);
  assert(LEN_ARRAY(misc_png_sizes_table) == MISC_ANIM_COUNT);
  assert(LEN_ARRAY(misc_names_table) == MISC_ANIM_COUNT);
  assert(index < MISC_ANIM_COUNT);
  auto result = load_custom_anim(ctx, {misc_pngs_table[index], misc_png_sizes_table[index], misc_names_table[index]}, misc_settings_table[index]);
  return result;
}
void init_all_misc_anim(animation_thread_context_t& ctx) {
  using namespace assets;
  for (size_t i = 0;i < MISC_ANIM_COUNT;++i) {
    init_misc_anim(ctx, i, {misc_pngs_table[i], misc_png_sizes_table[i], misc_names_table[i]}, misc_settings_table[i]);
  }
}
}  // namespace bongocat::animation