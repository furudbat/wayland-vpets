#include "graphics/drawing.h"

#include <cassert>
#include <cmath>

namespace bongocat::animation::details {

int scale_size_120(scale_120_params params) {
  if (params.logical <= 0 || params.scale120 == 0) {
    return 0;
  }
  return static_cast<int>((static_cast<int64_t>(params.logical) * params.scale120 + 119) / 120);
}

int scale_offset_120(scale_120_params params) {
  if (params.logical >= 0) {
    return scale_size_120(params);
  }
  return -scale_size_120({.logical = -params.logical, .scale120 = params.scale120});
}

output_logical_size_result_t output_logical_size(in_output_logical_size_t raw, int transform, int integer_scale,
                                                 in_output_logical_size_t xdg) {
  output_logical_size_result_t ret;
  if (xdg.width > 0 && xdg.height > 0) {
    ret.width = xdg.width;
    ret.height = xdg.height;
    return ret;
  }

  const bool rotated = transform == 1 || transform == 3 || transform == 5 || transform == 7;

  const int w = rotated ? raw.height : raw.width;
  const int h = rotated ? raw.width : raw.height;
  const int scale = integer_scale > 0 ? integer_scale : 1;

  ret.width = w > 0 ? (w + scale - 1) / scale : 0;
  ret.height = h > 0 ? (h + scale - 1) / scale : 0;

  return ret;
}

}  // namespace bongocat::animation::details