#include "graphics/animation_thread_context.h"
#include "graphics/drawing.h"

#include <cassert>
#include <cmath>

namespace bongocat::animation {
// =============================================================================
// GLOBAL STATE AND CONFIGURATION
// =============================================================================

static inline constexpr uint8_t THRESHOLD_ALPHA = 120;
static inline constexpr unsigned int FIXED_SHIFT = 16;
static inline constexpr unsigned int FIXED_ONE = (1u << FIXED_SHIFT);

// =============================================================================
// DRAWING OPERATIONS MODULE
// =============================================================================

/*
static bool drawing_is_pixel_in_bounds(int x, int y, int width, int height) {
    return x >= 0 && y >= 0 && x < width && y < height;
}
*/

constexpr static uint8_t apply_invert(uint8_t v, bool invert) {
  return v ^ (invert ? 0xFF : 0x00);  // branchless invert
}

static void drawing_copy_pixel_rgba(uint8_t *dest, int dest_channels, int dest_idx, blit_image_color_order_t dest_order,
                                    uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
  // Map destination channel indices
  const int dr = (dest_order == blit_image_color_order_t::RGBA) ? 0 : 2;
  constexpr int dg = 1;
  const int db = (dest_order == blit_image_color_order_t::RGBA) ? 2 : 0;

  // Store without branching
  if (dest_channels >= 1) {
    dest[dest_idx + dr] = r;
  }
  if (dest_channels >= 2) {
    dest[dest_idx + dg] = g;
  }
  if (dest_channels >= 3) {
    dest[dest_idx + db] = b;
  }
  if (dest_channels >= 4) {
    dest[dest_idx + 3] = a;
  }
}

void drawing_copy_pixel(uint8_t *dest, int dest_channels, int dest_idx, const unsigned char *src, int src_channels,
                        int src_idx, blit_image_color_option_flags_t options, blit_image_color_order_t dest_order,
                        blit_image_color_order_t src_order) {
  if (has_flag(options, blit_image_color_option_flags_t::Invisible)) {
    return;
  }
  const bool invert = has_flag(options, blit_image_color_option_flags_t::Invert);

  // Map source channel indices for RGB
  const int sr = (src_order == blit_image_color_order_t::RGBA) ? 0 : 2;
  const int sg = 1;
  const int sb = (src_order == blit_image_color_order_t::RGBA) ? 2 : 0;

  // Load into RGBA without branches
  uint8_t r{0};
  uint8_t g{0};
  uint8_t b{0};
  uint8_t a{0};
  if (src_channels == 1) {
    // 1-channel grayscale -> fill all channels with 0/255
    uint8_t v = src[src_idx] > 0 ? 255 : 0;
    v = apply_invert(v, invert);
    r = g = b = a = v;
  } else if (src_channels == 2) {
    // 2-channel grayscale + alpha (alpha ignored in original)
    const uint8_t gray = apply_invert(src[src_idx], invert);
    r = g = b = gray;
    a = 255;
  } else {
    // RGB / RGBA
    r = apply_invert(src[src_idx + sr], invert);
    g = apply_invert(src[src_idx + sg], invert);
    b = apply_invert(src[src_idx + sb], invert);
    a = (src_channels >= 4) ? src[src_idx + 3] : 255;  // Alpha not inverted
  }

  drawing_copy_pixel_rgba(dest, dest_channels, dest_idx, dest_order, r, g, b, a);
}

void drawing_blend_pixel(uint8_t *dest, int dest_channels, int dest_idx, uint8_t src_r, uint8_t src_g, uint8_t src_b,
                         uint8_t src_a, int src_channels, blit_image_color_option_flags_t options,
                         blit_image_color_order_t dest_order, blit_image_color_order_t src_order) {
  if (has_flag(options, blit_image_color_option_flags_t::Invisible)) {
    return;
  }
  const bool invert = has_flag(options, blit_image_color_option_flags_t::Invert);

  // Map source channel indices for RGB
  const uint8_t sr = (src_order == blit_image_color_order_t::RGBA) ? src_r : src_b;
  const uint8_t sg = src_g;
  const uint8_t sb = (src_order == blit_image_color_order_t::RGBA) ? src_b : src_r;
  const uint8_t sa = src_a;

  // Skip fully transparent pixels
  if (sa == 0) {
    return;
  }

  // Load into RGBA without branches
  uint8_t r{0};
  uint8_t g{0};
  uint8_t b{0};
  uint8_t a{0};
  if (src_channels == 1) {
    // 1-channel grayscale -> fill all channels with 0/255
    uint8_t v = sr > 0 ? 255 : 0;
    v = apply_invert(v, invert);
    r = g = b = a = v;
  } else if (src_channels == 2) {
    // 2-channel grayscale + alpha (alpha ignored in original)
    const uint8_t gray = apply_invert(sr, invert);
    r = g = b = gray;
    a = 255;
  } else {
    // Fully opaque - direct copy (fast path)
    if (src_a == 255) {
      // RGB / RGBA
      r = apply_invert(sr, invert);
      g = apply_invert(sg, invert);
      b = apply_invert(sb, invert);
      a = 255;  // Alpha not inverted
    } else {
      // Alpha blend: out = src * alpha + dest * (1 - alpha)
      const float alpha = static_cast<float>(sa) / 255.0f;
      const float inv_alpha = 1.0f - alpha;

      // Map source channel indices for RGB
      const uint8_t dr = (dest_order == blit_image_color_order_t::RGBA) ? dest[dest_idx + 0] : dest[dest_idx + 2];
      const uint8_t dg = dest[dest_idx + 1];
      const uint8_t db = (dest_order == blit_image_color_order_t::RGBA) ? dest[dest_idx + 2] : dest[dest_idx + 0];
      // const uint8_t da = dest[dest_idx + 3];

      r = static_cast<uint8_t>(lroundf((sr * alpha) + (dr * inv_alpha)));
      g = static_cast<uint8_t>(lroundf((sg * alpha) + (dg * inv_alpha)));
      b = static_cast<uint8_t>(lroundf((sb * alpha) + (db * inv_alpha)));
      a = 255;  // Alpha not inverted
    }
  }

  drawing_copy_pixel_rgba(dest, dest_channels, dest_idx, dest_order, r, g, b, a);
}

struct drawing_get_pixel_result_t {
  unsigned char r{0};
  unsigned char g{0};
  unsigned char b{0};
  unsigned char a{0};
};
// Bilinear interpolation for smooth scaling
static drawing_get_pixel_result_t drawing_get_interpolated_pixel(const unsigned char *src, size_t src_size, int src_w,
                                                                 int src_h, int src_channels, float fx, float fy) {
  // Clamp coordinates to image bounds
  if (fx < 0) {
    fx = 0;
  }
  if (fy < 0) {
    fy = 0;
  }
  if (fx >= static_cast<float>(src_w - 1)) {
    fx = static_cast<float>(src_w - 1);
  }
  if (fy >= static_cast<float>(src_h - 1)) {
    fy = static_cast<float>(src_h - 1);
  }

  const int x1 = static_cast<int>(fx);
  const int y1 = static_cast<int>(fy);
  int x2 = x1 + 1;
  int y2 = y1 + 1;

  // Clamp to bounds
  if (x2 >= src_w) {
    x2 = src_w - 1;
  }
  if (y2 >= src_h) {
    y2 = src_h - 1;
  }

  const float dx = fx - static_cast<float>(x1);
  const float dy = fy - static_cast<float>(y1);

  // Get the four surrounding pixels
  const int idx_tl = (y1 * src_w + x1) * src_channels;  // top-left
  const int idx_tr = (y1 * src_w + x2) * src_channels;  // top-right
  const int idx_bl = (y2 * src_w + x1) * src_channels;  // bottom-left
  const int idx_br = (y2 * src_w + x2) * src_channels;  // bottom-right

  // Interpolate each channel
  drawing_get_pixel_result_t ret;
  for (int c = 0; c < src_channels; c++) {
    assert(idx_tl >= 0);
    assert(idx_tr >= 0);
    assert(idx_bl >= 0);
    assert(idx_br >= 0);
    const size_t tl_idx_c = static_cast<size_t>(idx_tl) + static_cast<size_t>(c);
    const size_t tr_idx_c = static_cast<size_t>(idx_tr) + static_cast<size_t>(c);
    const size_t bl_idx_c = static_cast<size_t>(idx_bl) + static_cast<size_t>(c);
    const size_t br_idx_c = static_cast<size_t>(idx_br) + static_cast<size_t>(c);

    if (tl_idx_c < src_size && tr_idx_c < src_size && bl_idx_c < src_size && br_idx_c < src_size) {
      const float top = (static_cast<float>(src[tl_idx_c]) * (1.0f - dx)) + (static_cast<float>(src[tr_idx_c]) * dx);
      const float bottom = (static_cast<float>(src[bl_idx_c]) * (1.0f - dx)) + (static_cast<float>(src[br_idx_c]) * dx);
      const float result = (top * (1.0f - dy)) + (bottom * dy);

      switch (c) {
      case 0:
        ret.r = static_cast<uint8_t>(lroundf(result));
        break;  // R
      case 1:
        ret.g = static_cast<uint8_t>(lroundf(result));
        break;  // G
      case 2:
        ret.b = static_cast<uint8_t>(lroundf(result));
        break;  // B
      case 3:
        ret.a = static_cast<uint8_t>(lroundf(result));
        break;  // A
      default:
        break;
      }
    }
  }
  return ret;
}

// Box filter for high-quality downscaling - averages all source pixels that
// map to a destination pixel. Produces much smoother results than bilinear
// when shrinking images significantly.
static drawing_get_pixel_result_t drawing_get_box_filtered_pixel(const unsigned char *src, size_t src_size, int src_w,
                                                                 int src_h, int src_channels, float fx, float fy) {
  // Clamp coordinates to image bounds
  if (fx < 0) {
    fx = 0;
  }
  if (fy < 0) {
    fy = 0;
  }
  if (fx >= static_cast<float>(src_w - 1)) {
    fx = static_cast<float>(src_w - 1);
  }
  if (fy >= static_cast<float>(src_h - 1)) {
    fy = static_cast<float>(src_h - 1);
  }

  const int x1 = static_cast<int>(fx);
  const int y1 = static_cast<int>(fy);
  int x2 = x1 + 1;
  int y2 = y1 + 1;

  // Clamp to bounds
  if (x2 >= src_w) {
    x2 = src_w - 1;
  }
  if (y2 >= src_h) {
    y2 = src_h - 1;
  }

  // Indices of 2×2 block
  const int idx_tl = (y1 * src_w + x1) * src_channels;
  const int idx_tr = (y1 * src_w + x2) * src_channels;
  const int idx_bl = (y2 * src_w + x1) * src_channels;
  const int idx_br = (y2 * src_w + x2) * src_channels;

  float sum_r = 0.0f;
  float sum_g = 0.0f;
  float sum_b = 0.0f;
  float sum_a = 0.0f;
  int count = 0;

  // Accumulate function (manual inline)
  const int base_indices[4] = {idx_tl, idx_tr, idx_bl, idx_br};

  assert(src_channels >= 0);
  for (int i = 0; i < src_channels; i++) {
    const int base = base_indices[i];
    if (base < 0) {
      continue;
    }

    for (int c = 0; c < src_channels; c++) {
      const size_t idx_c = static_cast<size_t>(base) + static_cast<size_t>(c);
      if (idx_c >= src_size) {
        continue;
      }

      const float v = src[idx_c];
      switch (c) {
      case 0:
        sum_r += v;
        break;
      case 1:
        sum_g += v;
        break;
      case 2:
        sum_b += v;
        break;
      case 3:
        sum_a += v;
        break;
      }
    }
    count++;
  }

  if (count == 0) {
    count = 1;
  }

  drawing_get_pixel_result_t ret;
  // Average
  ret.r = static_cast<uint8_t>(lroundf(sum_r / static_cast<float>(count)));
  ret.g = static_cast<uint8_t>(lroundf(sum_g / static_cast<float>(count)));
  ret.b = static_cast<uint8_t>(lroundf(sum_b / static_cast<float>(count)));
  if (src_channels == 4) {
    ret.a = static_cast<uint8_t>(lroundf(sum_a / static_cast<float>(count)));
  } else {
    ret.a = 255;
  }
  return ret;
}

void blit_image_scaled(uint8_t *dest, size_t dest_size, int dest_w, int dest_h, int dest_channels,
                       const unsigned char *src, size_t src_size, int src_w, int src_h, int src_channels, int src_x,
                       int src_y, int frame_w, int frame_h, int offset_x, int offset_y, int target_w, int target_h,
                       blit_image_color_order_t dest_order, blit_image_color_order_t src_order,
                       blit_image_color_option_flags_t options) {
  if (dest == BONGOCAT_NULLPTR || src == BONGOCAT_NULLPTR) {
    return;
  }
  if (dest_w <= 0 || dest_h <= 0 || src_w <= 0 || src_h <= 0) {
    return;
  }
  if (dest_channels <= 0 || src_channels <= 0) {
    return;
  }
  if (target_w <= 0 || target_h <= 0) {
    return;
  }
  if (frame_w <= 0 || frame_h <= 0) {
    return;
  }
  if (has_flag(options, blit_image_color_option_flags_t::Invisible)) {
    return;
  }

  assert(dest_w >= 0);
  assert(dest_h >= 0);
  assert(dest_channels >= 0);
  assert(src_w >= 0);
  assert(src_h >= 0);
  assert(src_channels >= 0);
  // Verify buffers are large enough
  const size_t needed_dest =
      static_cast<size_t>(dest_w) * static_cast<size_t>(dest_h) * static_cast<size_t>(dest_channels);
  const size_t needed_src = static_cast<size_t>(src_w) * static_cast<size_t>(src_h) * static_cast<size_t>(src_channels);
  if (dest_size < needed_dest || src_size < needed_src) {
    return;
  }

  // Clip destination rectangle
  const int dst_left = offset_x;
  const int dst_top = offset_y;
  const int dst_right = offset_x + target_w;
  const int dst_bottom = offset_y + target_h;

  int x0 = 0;
  int x1 = target_w;
  if (dst_left < 0) {
    x0 = -dst_left;
  }
  if (dst_right > dest_w) {
    x1 = target_w - (dst_right - dest_w);
  }
  if (x0 >= x1) {
    return;
  }

  int y0 = 0;
  int y1 = target_h;
  if (dst_top < 0) {
    y0 = -dst_top;
  }
  if (dst_bottom > dest_h) {
    y1 = target_h - (dst_bottom - dest_h);
  }
  if (y0 >= y1) {
    return;
  }

  // Fixed-point increments
  assert(target_w > 0);
  assert(target_h > 0);
  int32_t inc_x = static_cast<int32_t>((static_cast<int64_t>(frame_w) << FIXED_SHIFT) / target_w);
  int32_t inc_y = static_cast<int32_t>((static_cast<int64_t>(frame_h) << FIXED_SHIFT) / target_h);

  int32_t src_x_start = src_x << FIXED_SHIFT;
  int32_t src_y_start = src_y << FIXED_SHIFT;

  const bool use_bilinear_interpolation = has_flag(options, blit_image_color_option_flags_t::BilinearInterpolation);
  const bool mirror_x = has_flag(options, blit_image_color_option_flags_t::MirrorX);
  const bool mirror_y = has_flag(options, blit_image_color_option_flags_t::MirrorY);
  const bool disable_threshold_alpha =
      use_bilinear_interpolation || has_flag(options, blit_image_color_option_flags_t::DisableThresholdAlpha);

  // MirrorX / MirrorY affect direction and start point
  if (mirror_x) {
    src_x_start = (src_x + frame_w - 1) << FIXED_SHIFT;
    inc_x = -inc_x;
  }
  if (mirror_y) {
    src_y_start = (src_y + frame_h - 1) << FIXED_SHIFT;
    inc_y = -inc_y;
  }

  const size_t src_row_bytes = static_cast<size_t>(src_w) * static_cast<size_t>(src_channels);
  const size_t dest_row_bytes = static_cast<size_t>(dest_w) * static_cast<size_t>(dest_channels);

  const bool is_downscaling = (target_w < src_w) || (target_h < src_h);

  for (int ty = y0; ty < y1; ++ty) {
    const int dy = offset_y + ty;
    assert(dy < dest_h);

    const int32_t sy_fixed = src_y_start + static_cast<int32_t>(static_cast<int64_t>(ty) * inc_y);
    const int sy = sy_fixed >> FIXED_SHIFT;

    if (static_cast<unsigned>(sy) >= static_cast<unsigned>(src_h)) {
      continue;
    }

    const uint8_t *dest_row = dest + (static_cast<size_t>(dy) * dest_row_bytes);
    const unsigned char *src_row = src + (static_cast<size_t>(sy) * src_row_bytes);

    int32_t sx_fixed = src_x_start + static_cast<int32_t>(static_cast<int64_t>(x0) * inc_x);
    const uint8_t *dest_ptr = dest_row + (static_cast<size_t>(offset_x + x0) * static_cast<size_t>(dest_channels));

    for (int tx = x0; tx < x1; ++tx) {
      // const int dx = offset_x + tx;
      // assert(dx < dest_w);
      const int sx = sx_fixed >> FIXED_SHIFT;

      if (static_cast<unsigned>(sx) < static_cast<unsigned>(src_w)) {
        const uint8_t *src_pixel = src_row + (static_cast<size_t>(sx) * static_cast<size_t>(src_channels));
        const int dest_idx = static_cast<int>(dest_ptr - dest);
        const int src_idx = static_cast<int>(src_pixel - src);

        if (use_bilinear_interpolation) {
          // Use bilinear interpolation for smooth scaling
          const float fx = static_cast<float>(sx_fixed) / static_cast<float>(1 << FIXED_SHIFT);
          const float fy = static_cast<float>(sy_fixed) / static_cast<float>(1 << FIXED_SHIFT);

          if (src_channels >= 4) {
            if (disable_threshold_alpha || src_pixel[3] > THRESHOLD_ALPHA) {
              const drawing_get_pixel_result_t pixel =
                  (is_downscaling) ? drawing_get_box_filtered_pixel(src, src_size, src_w, src_h, src_channels, fx, fy)
                                   : drawing_get_interpolated_pixel(src, src_size, src_w, src_h, src_channels, fx, fy);
              drawing_blend_pixel(dest, dest_channels, dest_idx, pixel.r, pixel.g, pixel.b, pixel.a, 4, options, dest_order,
                                  blit_image_color_order_t::RGBA);
            }
          }
        } else {
          // Use nearest-neighbor scaling (original behavior)
          if (src_channels >= 4) {
            if (disable_threshold_alpha || src_pixel[3] > THRESHOLD_ALPHA) {
              drawing_copy_pixel(dest, dest_channels, dest_idx, src, src_channels, src_idx, options, dest_order,
                                 src_order);
            }
          } else {
            drawing_copy_pixel(dest, dest_channels, dest_idx, src, src_channels, src_idx, options, dest_order,
                               src_order);
          }
        }
      }

      sx_fixed += inc_x;
      dest_ptr += dest_channels;
    }
  }
}
}  // namespace bongocat::animation