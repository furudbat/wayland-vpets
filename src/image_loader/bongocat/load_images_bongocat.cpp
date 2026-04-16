#include "load_images_bongocat.h"
#include "embedded_assets/bongocat/assets_bongocat_features.h"
#include "embedded_assets/bongocat/bongocat.h"
#include "embedded_assets/bongocat/bongocat.hpp"
#include "graphics/animation.h"
#include "graphics/animation_thread_context.h"
#include "graphics/drawing.h"
#include "image_loader/load_images.h"
#include "image_loader/load_svgs.h"
#include "utils/memory.h"
#include <cassert>

namespace bongocat::animation {

created_result_t<bongocat_sprite_sheet_t>
load_bongocat_anim([[maybe_unused]] int anim_index, get_sprite_callback_t get_sprite, size_t embedded_images_count,
                    load_bongocat_anim_type_t type,
                    anim_sprite_sheet_from_embedded_svgs_t svg_params, anim_sprite_sheet_from_embedded_svgs_cropping_t cropping) {
  BONGOCAT_LOG_VERBOSE("Load bongocat Animation(index=%d) ...", anim_index);

  auto [sprite_sheet, sprite_sheet_error] = [&]() {
    switch (type) {
      case load_bongocat_anim_type_t::SVG:{
        assert(svg_params.target_w >= 0);
        assert(svg_params.target_h >= 0);
#ifdef FEATURE_USE_BONGOCAT_SVG
        return anim_sprite_sheet_from_embedded_svgs(get_sprite, embedded_images_count, svg_params, cropping);
#else
        BONGOCAT_LOG_WARNING("load_bongocat_anim: SVG not supported");
        break;
#endif
      }
      case load_bongocat_anim_type_t::PNG:
        return anim_sprite_sheet_from_embedded_images(get_sprite, embedded_images_count);
    }

    return anim_sprite_sheet_from_embedded_images(get_sprite, embedded_images_count);
  }();
  if (sprite_sheet_error != bongocat_error_t::BONGOCAT_SUCCESS) [[unlikely]] {
    return sprite_sheet_error;
  }

  bongocat_sprite_sheet_t ret;
  ret.image = bongocat::move(sprite_sheet.image);
  ret.frame_width = bongocat::move(sprite_sheet.frame_width);
  ret.frame_height = bongocat::move(sprite_sheet.frame_height);
  ret.total_frames = bongocat::move(sprite_sheet.total_frames);
  ret.both_up = bongocat::move(sprite_sheet.frames[0]);
  ret.left_down = bongocat::move(sprite_sheet.frames[1]);
  ret.right_down = bongocat::move(sprite_sheet.frames[2]);
  ret.both_down = bongocat::move(sprite_sheet.frames[3]);
  ret.sleeping = bongocat::move(sprite_sheet.frames[4]);
  sprite_sheet = {}; // generic sprite has been moved

  // setup animations (cache)
  using namespace assets;

  assert(ret.both_up.valid);
  assert(ret.left_down.valid);
  assert(ret.right_down.valid);
  assert(ret.both_down.valid);
  assert(ret.sleeping.valid);

  static_assert(MAX_ANIMATION_FRAMES >= 4);
  ret.animations.idle[0] = BONGOCAT_FRAME_BOTH_UP;
  ret.animations.idle[1] = BONGOCAT_FRAME_BOTH_UP;
  ret.animations.idle[2] = BONGOCAT_FRAME_BOTH_UP;
  ret.animations.idle[3] = BONGOCAT_FRAME_BOTH_UP;

  ret.animations.boring[0] = BONGOCAT_FRAME_SLEEPING;
  ret.animations.boring[1] = BONGOCAT_FRAME_BOTH_UP;
  ret.animations.boring[2] = BONGOCAT_FRAME_BOTH_UP;
  ret.animations.boring[3] = BONGOCAT_FRAME_BOTH_UP;

  ret.animations.writing[0] = BONGOCAT_FRAME_LEFT_DOWN;
  ret.animations.writing[1] = BONGOCAT_FRAME_RIGHT_DOWN;
  ret.animations.writing[2] = BONGOCAT_FRAME_LEFT_DOWN;
  ret.animations.writing[3] = BONGOCAT_FRAME_RIGHT_DOWN;

  ret.animations.sleep[0] = BONGOCAT_FRAME_SLEEPING;
  ret.animations.sleep[1] = BONGOCAT_FRAME_SLEEPING;
  ret.animations.sleep[2] = BONGOCAT_FRAME_SLEEPING;
  ret.animations.sleep[3] = BONGOCAT_FRAME_SLEEPING;

  ret.animations.wake_up[0] = BONGOCAT_FRAME_BOTH_UP;
  ret.animations.wake_up[1] = BONGOCAT_FRAME_BOTH_UP;
  ret.animations.wake_up[2] = BONGOCAT_FRAME_BOTH_UP;
  ret.animations.wake_up[3] = BONGOCAT_FRAME_BOTH_UP;

  ret.animations.working[0] = BONGOCAT_FRAME_LEFT_DOWN;
  ret.animations.working[1] = BONGOCAT_FRAME_RIGHT_DOWN;
  ret.animations.working[2] = BONGOCAT_FRAME_LEFT_DOWN;
  ret.animations.working[3] = BONGOCAT_FRAME_RIGHT_DOWN;

  ret.animations.moving[0] = BONGOCAT_FRAME_BOTH_UP;
  ret.animations.moving[1] = BONGOCAT_FRAME_BOTH_DOWN;
  ret.animations.moving[2] = BONGOCAT_FRAME_BOTH_UP;
  ret.animations.moving[3] = BONGOCAT_FRAME_BOTH_DOWN;

  ret.animations.happy[0] = BONGOCAT_FRAME_LEFT_DOWN;
  ret.animations.happy[1] = BONGOCAT_FRAME_RIGHT_DOWN;
  ret.animations.happy[2] = BONGOCAT_FRAME_LEFT_DOWN;
  ret.animations.happy[3] = BONGOCAT_FRAME_RIGHT_DOWN;

  ret.animations.running[0] = BONGOCAT_FRAME_BOTH_UP;
  ret.animations.running[1] = BONGOCAT_FRAME_BOTH_DOWN;
  ret.animations.running[2] = BONGOCAT_FRAME_BOTH_UP;
  ret.animations.running[3] = BONGOCAT_FRAME_BOTH_DOWN;

  ret.animations.left_writing[0] = BONGOCAT_FRAME_LEFT_DOWN;
  ret.animations.left_writing[1] = BONGOCAT_FRAME_BOTH_UP;
  ret.animations.left_writing[2] = BONGOCAT_FRAME_LEFT_DOWN;
  ret.animations.left_writing[3] = BONGOCAT_FRAME_BOTH_UP;

  ret.animations.right_writing[0] = BONGOCAT_FRAME_RIGHT_DOWN;
  ret.animations.right_writing[1] = BONGOCAT_FRAME_BOTH_UP;
  ret.animations.right_writing[2] = BONGOCAT_FRAME_RIGHT_DOWN;
  ret.animations.right_writing[3] = BONGOCAT_FRAME_BOTH_UP;

  return ret;
}

bongocat_error_t init_bongocat_anim(animation_thread_context_t& ctx, int anim_index, get_sprite_callback_t get_sprite,
                                    size_t embedded_images_count, load_bongocat_anim_type_t type,
                                    anim_sprite_sheet_from_embedded_svgs_t svg_params,
                                    anim_sprite_sheet_from_embedded_svgs_cropping_t cropping) {
  using namespace assets;
  BONGOCAT_CHECK_NULL(ctx.shm.ptr, bongocat_error_t::BONGOCAT_ERROR_INVALID_PARAM);
  BONGOCAT_CHECK_NULL(ctx._local_copy_config.ptr, bongocat_error_t::BONGOCAT_ERROR_INVALID_PARAM);

  assert(anim_index >= 0 && static_cast<size_t>(anim_index) < BONGOCAT_ANIM_COUNT);
  BONGOCAT_LOG_VERBOSE("Load bongocat Animation (%d/%d): %s ...", anim_index, BONGOCAT_ANIM_COUNT,
                       get_sprite(embedded_images_count).name);

  auto [sprite_sheet, sprite_sheet_error] = load_bongocat_anim(anim_index, get_sprite, embedded_images_count, type, svg_params, cropping);
  if (sprite_sheet_error != bongocat_error_t::BONGOCAT_SUCCESS) [[unlikely]] {
    BONGOCAT_LOG_ERROR("Load bongocat Animation failed: index: %d", anim_index);
    return sprite_sheet_error;
  }
  assert(sprite_sheet.total_frames > 0);  ///< this SHOULD always work if it's an valid EMBEDDED image
  assert(MAX_NUM_FRAMES <= INT_MAX);
  assert(sprite_sheet.total_frames <= static_cast<int>(MAX_NUM_FRAMES));
  if (sprite_sheet.total_frames > static_cast<int>(MAX_NUM_FRAMES)) {
    BONGOCAT_LOG_ERROR("Sprite Sheet does not fit in out_frames: %d, total_frames: %d", MAX_NUM_FRAMES,
                       sprite_sheet.total_frames);
    return bongocat_error_t::BONGOCAT_ERROR_INVALID_PARAM;
  }

  assert(anim_index >= 0);
  ctx.shm->bongocat_anims[static_cast<size_t>(anim_index)] = bongocat::move(sprite_sheet);
  assert(ctx.shm->bongocat_anims[static_cast<size_t>(anim_index)].type == animation_t::type_t::Bongocat);
  sprite_sheet = {}; ///< sprite sheet has been moved

  return bongocat_error_t::BONGOCAT_SUCCESS;
}

created_result_t<bongocat_sprite_sheet_t> load_bongocat_sprite_sheet(const animation_thread_context_t& ctx, int index) {
  using namespace assets;
  using namespace animation;
  BONGOCAT_CHECK_NULL(ctx.shm.ptr, bongocat_error_t::BONGOCAT_ERROR_INVALID_PARAM);
  BONGOCAT_CHECK_NULL(ctx._local_copy_config.ptr, bongocat_error_t::BONGOCAT_ERROR_INVALID_PARAM);

  switch (index) {
  case BONGOCAT_ANIM_INDEX:
    if constexpr (features::EnableBongocatSvg) {
      const int cat_height = ctx._local_copy_config->cat_height;
      const auto svg_params = anim_bongocat_get_svg_params(cat_height);
      const auto svg_cropping = anim_bongocat_get_svg_cropping(cat_height);
      return load_bongocat_anim(BONGOCAT_ANIM_INDEX, get_bongocat_sprite_svg, BONGOCAT_EMBEDDED_IMAGES_COUNT, load_bongocat_anim_type_t::SVG, svg_params, svg_cropping);
    } else {
      return load_bongocat_anim(BONGOCAT_ANIM_INDEX, get_bongocat_sprite, BONGOCAT_EMBEDDED_IMAGES_COUNT, load_bongocat_anim_type_t::PNG, {0, 0, 0, 0}, {0, 0, 0, 0});
    }
  default:
    return bongocat_error_t::BONGOCAT_ERROR_INVALID_PARAM;
  }

  return bongocat_error_t::BONGOCAT_ERROR_INVALID_PARAM;
}
}  // namespace bongocat::animation
