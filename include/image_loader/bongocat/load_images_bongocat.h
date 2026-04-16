#pragma once

#include "embedded_assets/bongocat/bongocat.h"
#include "core/bongocat.h"
#include "graphics/sprite_sheet.h"
#include "image_loader/load_images.h"
#include "image_loader/load_svgs.h"

namespace bongocat::animation {
struct animation_thread_context_t;

enum class load_bongocat_anim_type_t : uint8_t {
  PNG,
  SVG,
};
BONGOCAT_NODISCARD created_result_t<bongocat_sprite_sheet_t>
load_bongocat_anim(int anim_index, get_sprite_callback_t get_sprite, size_t embedded_images_count,
                   load_bongocat_anim_type_t type, anim_sprite_sheet_from_embedded_svgs_t svg_params,
                   anim_sprite_sheet_from_embedded_svgs_cropping_t cropping);

bongocat_error_t init_bongocat_anim(animation_thread_context_t& ctx, int anim_index, get_sprite_callback_t get_sprite,
                                    size_t embedded_images_count, load_bongocat_anim_type_t type, anim_sprite_sheet_from_embedded_svgs_t svg_params);

inline anim_sprite_sheet_from_embedded_svgs_t anim_bongocat_get_svg_params(int cat_height) {
  using namespace assets;
  static_assert(BONGOCAT_SVG_FRAME_HEIGHT > 0);
  static_assert(BONGOCAT_SVG_FRAME_REAL_CAT_HEIGHT > 0);

  // scale so that the _visible cat_ becomes cat_height
  const float scale =
      static_cast<float>(cat_height) /
      static_cast<float>(BONGOCAT_SVG_FRAME_REAL_CAT_HEIGHT);

  const int target_w = static_cast<int>(
      BONGOCAT_SVG_FRAME_WIDTH * scale);

  const int target_h = static_cast<int>(
      BONGOCAT_SVG_FRAME_HEIGHT * scale);

  return {
    .target_w = target_w,
    .target_h = target_h,
    .tx = static_cast<float>(BONGOCAT_SVG_FRAME_TX) * scale,
    .ty = static_cast<float>(BONGOCAT_SVG_FRAME_TY) * scale,
    .alpha_mask = BONGOCAT_SVG_ALPHA_MASK,
  };
}
inline anim_sprite_sheet_from_embedded_svgs_cropping_t anim_bongocat_get_svg_cropping(int cat_height) {
  using namespace assets;
  static_assert(BONGOCAT_SVG_FRAME_HEIGHT > 0);
  static_assert(BONGOCAT_SVG_FRAME_REAL_CAT_HEIGHT > 0);

  // cropping must scale with _visible cat_
  const float scale =
      static_cast<float>(cat_height) /
      static_cast<float>(BONGOCAT_SVG_FRAME_REAL_CAT_HEIGHT);

  const float pad_x =
      (BONGOCAT_SVG_FRAME_WIDTH - BONGOCAT_SVG_FRAME_REAL_CAT_WIDTH) / 2.0f;
  const float pad_y =
      (BONGOCAT_SVG_FRAME_HEIGHT - BONGOCAT_SVG_FRAME_REAL_CAT_HEIGHT) / 2.0f;

  return {
    .left   = static_cast<int>(pad_x * scale),
    .right  = static_cast<int>(pad_x * scale),
    .top    = static_cast<int>(pad_y * scale),
    .bottom = static_cast<int>(pad_y * scale),
  };
}

BONGOCAT_NODISCARD created_result_t<bongocat_sprite_sheet_t> load_bongocat_sprite_sheet(const animation_thread_context_t& /*ctx*/,
                                                                                        int index);
}  // namespace bongocat::animation
