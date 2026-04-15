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
  static_assert(BONGOCAT_FRAME_HEIGHT > 0);

  //constexpr auto pad_x =
  //   (BONGOCAT_SVG_FRAME_WIDTH - BONGOCAT_SVG_FRAME_REAL_CAT_WIDTH) / 2;
  constexpr auto pad_y =
     (BONGOCAT_SVG_FRAME_HEIGHT - BONGOCAT_SVG_FRAME_REAL_CAT_HEIGHT) / 2;
  constexpr auto top = (pad_y + BONGOCAT_SVG_FRAME_TY);
  constexpr auto bottom = (pad_y - BONGOCAT_SVG_FRAME_TY);

  // target_width must have bottom so the end sprite will end up in the exact height of cat_height
  // frame_height must be the same as cat_height, so the scaling didn't get messed up
  const int cat_h = cat_height + bottom + top;
  const int cat_w = (cat_h * BONGOCAT_SVG_FRAME_WIDTH) / BONGOCAT_SVG_FRAME_HEIGHT;
  assert(cat_h > 0);
  const float scale = static_cast<float>(cat_h) / static_cast<float>(BONGOCAT_SVG_FRAME_HEIGHT);

  return {
    .target_w = cat_w,
    .target_h = cat_h,
    .tx = static_cast<float>(BONGOCAT_SVG_FRAME_TX) * scale,
    .ty = static_cast<float>(BONGOCAT_SVG_FRAME_TY) * scale,
    .alpha_mask = BONGOCAT_SVG_ALPHA_MASK,
  };
}
inline anim_sprite_sheet_from_embedded_svgs_cropping_t anim_bongocat_get_svg_cropping(int cat_height) {
  using namespace assets;
  static_assert(BONGOCAT_SVG_FRAME_HEIGHT > 0);
  static_assert(BONGOCAT_FRAME_HEIGHT > 0);

   constexpr auto pad_x =
      (BONGOCAT_SVG_FRAME_WIDTH - BONGOCAT_SVG_FRAME_REAL_CAT_WIDTH) / 2;
   constexpr auto pad_y =
      (BONGOCAT_SVG_FRAME_HEIGHT - BONGOCAT_SVG_FRAME_REAL_CAT_HEIGHT) / 2;
   constexpr auto top = (pad_y + BONGOCAT_SVG_FRAME_TY);
   constexpr auto bottom = (pad_y - BONGOCAT_SVG_FRAME_TY);

  const int cat_h = cat_height + bottom + top;
  //const int cat_w = (cat_h * BONGOCAT_SVG_FRAME_WIDTH) / BONGOCAT_SVG_FRAME_HEIGHT;
  assert(cat_h > 0);
  const float scale = static_cast<float>(cat_h) / static_cast<float>(BONGOCAT_SVG_FRAME_HEIGHT);

  return {
    .left = static_cast<int>((pad_x - BONGOCAT_SVG_FRAME_TX) * scale),
    .right = static_cast<int>((pad_x + BONGOCAT_SVG_FRAME_TX) * scale),
    .top = static_cast<int>(top * scale),
    .bottom = static_cast<int>(bottom * scale),
  };
}

BONGOCAT_NODISCARD created_result_t<bongocat_sprite_sheet_t> load_bongocat_sprite_sheet(const animation_thread_context_t& /*ctx*/,
                                                                                        int index);
}  // namespace bongocat::animation
