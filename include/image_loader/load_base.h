#ifndef BONGOCAT_EMBEDDED_LOAD_BASE_H
#define BONGOCAT_EMBEDDED_LOAD_BASE_H

#include "config/config.h"
#include "core/bongocat.h"
#include "embedded_assets/embedded_image.h"
#include "graphics/sprite_sheet.h"
#include <cstdlib>
#include <cstdint>

namespace bongocat::animation {
struct anim_sprite_sheet_from_embedded_svgs_t {
  int target_w;
  int target_h;
  float tx{0.0f};
  float ty{0.0f};
  uint32_t alpha_mask{0};
};
struct anim_sprite_sheet_from_embedded_svgs_cropping_t {
  int left{0};
  int right{0};
  int top{0};
  int bottom{0};
};
}  // namespace bongocat::animation
#endif