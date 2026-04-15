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
load_bongocat_anim(int anim_index, get_sprite_callback_t get_sprite, size_t embedded_images_count, load_bongocat_anim_type_t type, anim_sprite_sheet_from_embedded_svgs_t svg_params);

bongocat_error_t init_bongocat_anim(animation_thread_context_t& ctx, int anim_index, get_sprite_callback_t get_sprite,
                                    size_t embedded_images_count, load_bongocat_anim_type_t type, anim_sprite_sheet_from_embedded_svgs_t svg_params);
inline anim_sprite_sheet_from_embedded_svgs_t anim_bongocat_get_svg_params(int cat_height) {
  using namespace assets;
  static_assert(BONGOCAT_SVG_FRAME_HEIGHT > 0);
  static_assert(BONGOCAT_FRAME_HEIGHT > 0);
  const int cat_h = cat_height;
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

BONGOCAT_NODISCARD created_result_t<bongocat_sprite_sheet_t> load_bongocat_sprite_sheet(const animation_thread_context_t& /*ctx*/,
                                                                                        int index);
}  // namespace bongocat::animation
