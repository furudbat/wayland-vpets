#include "core/bongocat.h"
#include "embedded_assets/embedded_image.h"
#include "embedded_assets/misc/misc.hpp"
#include "embedded_assets/misc/misc_sprite.h"
#include "graphics/animation_thread_context.h"
#include "graphics/sprite_sheet.h"
#include "image_loader/custom/load_custom.h"

namespace bongocat::animation {
created_result_t<custom_sprite_sheet_t> load_misc_sprite_sheet(const animation_thread_context_t& ctx, int index) {
  using namespace animation;
  using namespace assets;
  switch (index) {
  case MISC_NEKO_ANIM_INDEX:
    return load_custom_anim(ctx, get_misc_sprite_sheet(MISC_NEKO_ANIM_INDEX), MISC_NEKO_SPRITE_SHEET_SETTINGS);
  default:
    return bongocat_error_t::BONGOCAT_ERROR_INVALID_PARAM;
  }
  return bongocat_error_t::BONGOCAT_ERROR_INVALID_PARAM;
}
}  // namespace bongocat::animation