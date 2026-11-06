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

/// x / 255, exactly rounded (same result as lroundf(x / 255.0f)) for 0 <= x <= 255 * 255
constexpr static uint8_t div255_round(uint32_t x) {
  return static_cast<uint8_t>((x + 128u + ((x + 128u) >> 8u)) >> 8u);
}
/// src * alpha + dest * (1 - alpha)
constexpr static uint8_t blend_channel(uint8_t src, uint8_t dest, uint8_t alpha) {
  return div255_round((static_cast<uint32_t>(src) * alpha) + (static_cast<uint32_t>(dest) * (255u - alpha)));
}

// -----------------------------------------------------------------------------
// 4-channel fast paths (RGBA/BGRA -> RGBA/BGRA), used by blit_image_scaled
// color order and invert get resolved ONCE per blit, not per pixel:
//   SwapRB:      src and dest order differ (RGBA <-> BGRA) => swap R and B
//   invert_mask: 0x00 (normal) or 0xFF (invert), applied with XOR (branchless), alpha is never inverted
// -----------------------------------------------------------------------------
static inline void copy_pixel_4ch_swap_rb(uint8_t *dest, const uint8_t *src, uint8_t invert_mask) {
  dest[0] = src[2] ^ invert_mask;
  dest[2] = src[0] ^ invert_mask;
  dest[1] = src[1] ^ invert_mask;
  dest[3] = src[3];
}
static inline void copy_pixel_4ch_normal(uint8_t *dest, const uint8_t *src, uint8_t invert_mask) {
  dest[0] = src[0] ^ invert_mask;
  dest[2] = src[2] ^ invert_mask;
  dest[1] = src[1] ^ invert_mask;
  dest[3] = src[3];
}

struct premul_pixel_4ch_t {
  uint8_t c0{0};
  uint8_t c1{0};
  uint8_t c2{0};
  uint8_t a{0};
};
/// premultiplied invert: (255 - c) * a / 255 = a - c * a / 255
constexpr static uint8_t invert_premul(uint8_t c, uint8_t a, bool invert) {
  return invert ? static_cast<uint8_t>(a - c) : c;
}
// "source over" into the (premultiplied) ARGB8888 wayland buffer, keeps the coverage of the edges in dest alpha:
//   out_c = src_c + dest_c * (1 - src_a)
//   out_a = src_a + dest_a * (1 - src_a)
static inline void composite_premul_4ch_swap_rb(uint8_t *dest, premul_pixel_4ch_t px, bool invert) {
  if (px.a == 0) {
    return;
  }
  const uint32_t ia = 255u - px.a;
  const uint8_t c0 = invert_premul(px.c0, px.a, invert);
  const uint8_t c1 = invert_premul(px.c1, px.a, invert);
  const uint8_t c2 = invert_premul(px.c2, px.a, invert);
  dest[0] = static_cast<uint8_t>(c2 + div255_round(dest[0] * ia));
  dest[1] = static_cast<uint8_t>(c1 + div255_round(dest[1] * ia));
  dest[2] = static_cast<uint8_t>(c0 + div255_round(dest[2] * ia));
  dest[3] = static_cast<uint8_t>(px.a + div255_round(dest[3] * ia));
}
static inline void composite_premul_4ch_normal(uint8_t *dest, premul_pixel_4ch_t px, bool invert) {
  if (px.a == 0) {
    return;
  }
  const uint32_t ia = 255u - px.a;
  const uint8_t c0 = invert_premul(px.c0, px.a, invert);
  const uint8_t c1 = invert_premul(px.c1, px.a, invert);
  const uint8_t c2 = invert_premul(px.c2, px.a, invert);
  dest[0] = static_cast<uint8_t>(c0 + div255_round(dest[0] * ia));
  dest[1] = static_cast<uint8_t>(c1 + div255_round(dest[1] * ia));
  dest[2] = static_cast<uint8_t>(c2 + div255_round(dest[2] * ia));
  dest[3] = static_cast<uint8_t>(px.a + div255_round(dest[3] * ia));
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
    // invert the source color first (alpha is never inverted), then blend
    r = apply_invert(sr, invert);
    g = apply_invert(sg, invert);
    b = apply_invert(sb, invert);
    a = 255;
    if (sa != 255) {
      // Alpha blend: out = src * alpha + dest * (1 - alpha), integer math (exactly rounded like lroundf)
      const uint8_t dr = (dest_order == blit_image_color_order_t::RGBA) ? dest[dest_idx + 0] : dest[dest_idx + 2];
      const uint8_t dg = dest[dest_idx + 1];
      const uint8_t db = (dest_order == blit_image_color_order_t::RGBA) ? dest[dest_idx + 2] : dest[dest_idx + 0];
      r = blend_channel(r, dr, sa);
      g = blend_channel(g, dg, sa);
      b = blend_channel(b, db, sa);
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

struct blit_scaled_4ch_params_t {
  uint8_t *dest{BONGOCAT_NULLPTR};
  size_t dest_row_bytes{0};
  const unsigned char *src{BONGOCAT_NULLPTR};
  size_t src_size{0};
  int src_w{0};
  int src_h{0};
  size_t src_row_bytes{0};
  int x0{0};
  int x1{0};
  int y0{0};
  int y1{0};
  int offset_x{0};
  int offset_y{0};
  int32_t src_x_start{0};
  int32_t src_y_start{0};
  int32_t inc_x{0};
  int32_t inc_y{0};
  uint8_t invert_mask{0x00};
  bool disable_threshold_alpha{false};
  bool bilinear{false};
  bool box_filter{false};

  // filtered path (bilinear/box): sample pixel centers, clamped to the current frame (no bleeding from neighbors)
  int frame_x{0};
  int frame_y{0};
  int frame_w{0};
  int frame_h{0};
  int target_w{0};
  int target_h{0};
  float scale_x{1.0f};  ///< source pixels per target pixel
  float scale_y{1.0f};
  bool mirror_x{false};
  bool mirror_y{false};
  bool invert{false};
};

static inline int clamp_int(int v, int lo, int hi) {
  return v < lo ? lo : (v > hi ? hi : v);
}

/// bilinear sample (premultiplied) at continuous source position (fx, fy), clamped to the frame
static premul_pixel_4ch_t sample_bilinear_premul_4ch(const blit_scaled_4ch_params_t& p, float fx, float fy) {
  // continuous coords -> pixel center coords
  fx -= 0.5f;
  fy -= 0.5f;
  const float flx = floorf(fx);
  const float fly = floorf(fy);
  const auto wx = static_cast<uint32_t>(lroundf((fx - flx) * 256.0f));  // 0..256
  const auto wy = static_cast<uint32_t>(lroundf((fy - fly) * 256.0f));
  const int frame_x_max = p.frame_x + p.frame_w - 1;
  const int frame_y_max = p.frame_y + p.frame_h - 1;
  const int xa = clamp_int(static_cast<int>(flx), p.frame_x, frame_x_max);
  const int xb = clamp_int(static_cast<int>(flx) + 1, p.frame_x, frame_x_max);
  const int ya = clamp_int(static_cast<int>(fly), p.frame_y, frame_y_max);
  const int yb = clamp_int(static_cast<int>(fly) + 1, p.frame_y, frame_y_max);

  const unsigned char *row_a = p.src + (static_cast<size_t>(ya) * p.src_row_bytes);
  const unsigned char *row_b = p.src + (static_cast<size_t>(yb) * p.src_row_bytes);
  const unsigned char *taps[4] = {row_a + (static_cast<size_t>(xa) * 4), row_a + (static_cast<size_t>(xb) * 4),
                                  row_b + (static_cast<size_t>(xa) * 4), row_b + (static_cast<size_t>(xb) * 4)};
  const uint32_t weights[4] = {(256u - wx) * (256u - wy), wx * (256u - wy), (256u - wx) * wy, wx * wy};  // sum 65536

  uint64_t sum_a = 0;
  uint64_t sum_c0 = 0;
  uint64_t sum_c1 = 0;
  uint64_t sum_c2 = 0;
  for (int i = 0; i < 4; ++i) {
    const uint64_t aw = static_cast<uint64_t>(taps[i][3]) * weights[i];
    sum_a += aw;
    sum_c0 += taps[i][0] * aw;
    sum_c1 += taps[i][1] * aw;
    sum_c2 += taps[i][2] * aw;
  }
  premul_pixel_4ch_t ret;
  ret.a = static_cast<uint8_t>((sum_a + 32768u) >> 16u);
  constexpr uint64_t color_div = 255ull * 65536ull;
  const auto premul = [&](uint64_t sum) -> uint8_t {
    const uint64_t c = (sum + (color_div / 2)) / color_div;
    return static_cast<uint8_t>(c < ret.a ? c : ret.a);
  };
  ret.c0 = premul(sum_c0);
  ret.c1 = premul(sum_c1);
  ret.c2 = premul(sum_c2);
  return ret;
}

/// box filter (premultiplied): average of all source pixels covered by target pixel (tx, ty) of the frame
static premul_pixel_4ch_t sample_box_premul_4ch(const blit_scaled_4ch_params_t& p, int tx, int ty) {
  const int frame_x_max = p.frame_w - 1;
  const int frame_y_max = p.frame_h - 1;
  const int x_begin = clamp_int(static_cast<int>(floorf(static_cast<float>(tx) * p.scale_x)), 0, frame_x_max);
  const int y_begin = clamp_int(static_cast<int>(floorf(static_cast<float>(ty) * p.scale_y)), 0, frame_y_max);
  int x_end = clamp_int(static_cast<int>(ceilf(static_cast<float>(tx + 1) * p.scale_x)) - 1, 0, frame_x_max);
  int y_end = clamp_int(static_cast<int>(ceilf(static_cast<float>(ty + 1) * p.scale_y)) - 1, 0, frame_y_max);
  x_end = x_end < x_begin ? x_begin : x_end;
  y_end = y_end < y_begin ? y_begin : y_end;

  uint64_t sum_a = 0;
  uint64_t sum_c0 = 0;
  uint64_t sum_c1 = 0;
  uint64_t sum_c2 = 0;
  for (int y = y_begin; y <= y_end; ++y) {
    const unsigned char *px =
        p.src + (static_cast<size_t>(p.frame_y + y) * p.src_row_bytes) + (static_cast<size_t>(p.frame_x + x_begin) * 4);
    for (int x = x_begin; x <= x_end; ++x, px += 4) {
      const uint64_t a = px[3];
      sum_a += a;
      sum_c0 += px[0] * a;
      sum_c1 += px[1] * a;
      sum_c2 += px[2] * a;
    }
  }
  const auto count = static_cast<uint64_t>(x_end - x_begin + 1) * static_cast<uint64_t>(y_end - y_begin + 1);
  premul_pixel_4ch_t ret;
  ret.a = static_cast<uint8_t>((sum_a + (count / 2)) / count);
  const uint64_t color_div = 255ull * count;
  const auto premul = [&](uint64_t sum) -> uint8_t {
    const uint64_t c = (sum + (color_div / 2)) / color_div;
    return static_cast<uint8_t>(c < ret.a ? c : ret.a);
  };
  ret.c0 = premul(sum_c0);
  ret.c1 = premul(sum_c1);
  ret.c2 = premul(sum_c2);
  return ret;
}

/// anti-aliased sample of target pixel (tx, ty): premultiplied bilinear (upscaling) / box filter (downscaling)
static inline premul_pixel_4ch_t sample_filtered_premul_4ch(const blit_scaled_4ch_params_t& p, int tx, int ty) {
  // target pixel -> frame-local target pixel (mirroring flips the target, not the sampling)
  const int ftx = p.mirror_x ? (p.target_w - 1 - tx) : tx;
  const int fty = p.mirror_y ? (p.target_h - 1 - ty) : ty;
  if (p.box_filter) {
    return sample_box_premul_4ch(p, ftx, fty);
  }
  const float fx = static_cast<float>(p.frame_x) + ((static_cast<float>(ftx) + 0.5f) * p.scale_x);
  const float fy = static_cast<float>(p.frame_y) + ((static_cast<float>(fty) + 0.5f) * p.scale_y);
  return sample_bilinear_premul_4ch(p, fx, fy);
}

/// RGBA/BGRA -> RGBA/BGRA: options, color order and filter are resolved before the loops,
/// the nearest-neighbor inner loop is a plain 4-byte (swizzled) copy
static void blit_image_scaled_4ch_swap_rb(const blit_scaled_4ch_params_t& p) {
  for (int ty = p.y0; ty < p.y1; ++ty) {
    const int32_t sy_fixed = p.src_y_start + static_cast<int32_t>(static_cast<int64_t>(ty) * p.inc_y);
    const int sy = sy_fixed >> FIXED_SHIFT;
    if (static_cast<unsigned>(sy) >= static_cast<unsigned>(p.src_h)) {
      continue;
    }

    const unsigned char *src_row = p.src + (static_cast<size_t>(sy) * p.src_row_bytes);
    uint8_t *dest_ptr = p.dest + (static_cast<size_t>(p.offset_y + ty) * p.dest_row_bytes) +
                        (static_cast<size_t>(p.offset_x + p.x0) * 4);
    int32_t sx_fixed = p.src_x_start + static_cast<int32_t>(static_cast<int64_t>(p.x0) * p.inc_x);

    if (!p.bilinear) {
      // nearest-neighbor
      for (int tx = p.x0; tx < p.x1; ++tx, sx_fixed += p.inc_x, dest_ptr += 4) {
        const int sx = sx_fixed >> FIXED_SHIFT;
        if (static_cast<unsigned>(sx) >= static_cast<unsigned>(p.src_w)) {
          continue;
        }
        const unsigned char *src_pixel = src_row + (static_cast<size_t>(sx) * 4);
        if (p.disable_threshold_alpha || src_pixel[3] > THRESHOLD_ALPHA) {
          copy_pixel_4ch_swap_rb(dest_ptr, src_pixel, p.invert_mask);
        }
      }
    } else {
      // anti-aliased: bilinear (upscaling) / box filter (downscaling), premultiplied + "source over"
      for (int tx = p.x0; tx < p.x1; ++tx, dest_ptr += 4) {
        composite_premul_4ch_swap_rb(dest_ptr, sample_filtered_premul_4ch(p, tx, ty), p.invert);
      }
    }
  }
}
static void blit_image_scaled_4ch_normal(const blit_scaled_4ch_params_t& p) {
  for (int ty = p.y0; ty < p.y1; ++ty) {
    const int32_t sy_fixed = p.src_y_start + static_cast<int32_t>(static_cast<int64_t>(ty) * p.inc_y);
    const int sy = sy_fixed >> FIXED_SHIFT;
    if (static_cast<unsigned>(sy) >= static_cast<unsigned>(p.src_h)) {
      continue;
    }

    const unsigned char *src_row = p.src + (static_cast<size_t>(sy) * p.src_row_bytes);
    uint8_t *dest_ptr = p.dest + (static_cast<size_t>(p.offset_y + ty) * p.dest_row_bytes) +
                        (static_cast<size_t>(p.offset_x + p.x0) * 4);
    int32_t sx_fixed = p.src_x_start + static_cast<int32_t>(static_cast<int64_t>(p.x0) * p.inc_x);

    if (!p.bilinear) {
      // nearest-neighbor
      for (int tx = p.x0; tx < p.x1; ++tx, sx_fixed += p.inc_x, dest_ptr += 4) {
        const int sx = sx_fixed >> FIXED_SHIFT;
        if (static_cast<unsigned>(sx) >= static_cast<unsigned>(p.src_w)) {
          continue;
        }
        const unsigned char *src_pixel = src_row + (static_cast<size_t>(sx) * 4);
        if (p.disable_threshold_alpha || src_pixel[3] > THRESHOLD_ALPHA) {
          copy_pixel_4ch_normal(dest_ptr, src_pixel, p.invert_mask);
        }
      }
    } else {
      // anti-aliased: bilinear (upscaling) / box filter (downscaling), premultiplied + "source over"
      for (int tx = p.x0; tx < p.x1; ++tx, dest_ptr += 4) {
        composite_premul_4ch_normal(dest_ptr, sample_filtered_premul_4ch(p, tx, ty), p.invert);
      }
    }
  }
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

  // downscaling = one FRAME gets shrunk (not the whole sprite sheet)
  const bool is_downscaling = (target_w < frame_w) || (target_h < frame_h);

  // common case: 4 channels on both sides (all sprite sheets are RGBA, the wayland buffer is BGRA)
  if (src_channels == 4 && dest_channels == 4) {
    const blit_scaled_4ch_params_t params{
        .dest = dest,
        .dest_row_bytes = dest_row_bytes,
        .src = src,
        .src_size = src_size,
        .src_w = src_w,
        .src_h = src_h,
        .src_row_bytes = src_row_bytes,
        .x0 = x0,
        .x1 = x1,
        .y0 = y0,
        .y1 = y1,
        .offset_x = offset_x,
        .offset_y = offset_y,
        .src_x_start = src_x_start,
        .src_y_start = src_y_start,
        .inc_x = inc_x,
        .inc_y = inc_y,
        .invert_mask = has_flag(options, blit_image_color_option_flags_t::Invert) ? static_cast<uint8_t>(0xFF)
                                                                                  : static_cast<uint8_t>(0x00),
        .disable_threshold_alpha = disable_threshold_alpha,
        .bilinear = use_bilinear_interpolation,
        .box_filter = is_downscaling,
        .frame_x = src_x,
        .frame_y = src_y,
        .frame_w = frame_w,
        .frame_h = frame_h,
        .target_w = target_w,
        .target_h = target_h,
        .scale_x = static_cast<float>(frame_w) / static_cast<float>(target_w),
        .scale_y = static_cast<float>(frame_h) / static_cast<float>(target_h),
        .mirror_x = mirror_x,
        .mirror_y = mirror_y,
        .invert = has_flag(options, blit_image_color_option_flags_t::Invert),
    };
    if (src_order != dest_order) {
      blit_image_scaled_4ch_swap_rb(params);
    } else {
      blit_image_scaled_4ch_normal(params);
    }
    return;
  }

  // generic path (1-3 channels)

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
              drawing_blend_pixel(dest, dest_channels, dest_idx, pixel.r, pixel.g, pixel.b, pixel.a, 4, options,
                                  dest_order, blit_image_color_order_t::RGBA);
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