#include "load_images_misc.h"

#include "embedded_assets/embedded_image.h"
#include "embedded_assets/misc/misc.hpp"
#include "graphics/animation_thread_context.h"
#include "image_loader/custom/load_custom.h"

namespace bongocat::animation {
bongocat_error_t init_misc_anim(animation_thread_context_t& ctx, int anim_index,
                                const assets::embedded_image_t& sprite_sheet_image,
                                const assets::custom_animation_settings_t& sprite_sheet_settings) {
  using namespace assets;
  BONGOCAT_CHECK_NULL(ctx.shm.ptr, bongocat_error_t::BONGOCAT_ERROR_INVALID_PARAM);
  BONGOCAT_CHECK_NULL(ctx._local_copy_config.ptr, bongocat_error_t::BONGOCAT_ERROR_INVALID_PARAM);

  assert(anim_index >= 0 && static_cast<size_t>(anim_index) < MISC_ANIM_COUNT);
  BONGOCAT_LOG_VERBOSE("Load misc Animation (%d/%d): %s ...", anim_index, MISC_ANIM_COUNT, sprite_sheet_image.name);
  auto result = load_custom_anim(ctx, sprite_sheet_image, sprite_sheet_settings);
  if (result.error != bongocat_error_t::BONGOCAT_SUCCESS) [[unlikely]] {
    BONGOCAT_LOG_ERROR("Load misc Animation failed: %s, index: %d", sprite_sheet_image.name, anim_index);
    return bongocat_error_t::BONGOCAT_ERROR_ANIMATION;
  }

  assert(anim_index >= 0);
  ctx.shm->misc_anims[static_cast<size_t>(anim_index)] = bongocat::move(result.result);
  assert(ctx.shm->misc_anims[static_cast<size_t>(anim_index)].type == animation_t::type_t::Custom);

  return bongocat_error_t::BONGOCAT_SUCCESS;
}
}  // namespace bongocat::animation
