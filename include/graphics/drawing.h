#ifndef BONGOCAT_ANIMATION_DRAWING_IMAGES_H
#define BONGOCAT_ANIMATION_DRAWING_IMAGES_H

#include "utils/error.h"

#include <cstdint>

namespace bongocat::animation {
enum class blit_image_color_option_flags_t : uint32_t {
  Normal = 0,
  Invisible = (1u << 0u),
  Invert = (1u << 1u),
  MirrorX = (1u << 2u),
  MirrorY = (1u << 3u),
  BilinearInterpolation = (1u << 4u),
  DisableThresholdAlpha = (1u << 5u),
};
enum class blit_image_color_order_t : uint8_t {
  RGBA,
  BGRA
};

// =============================================================================
// RENDERING UTILITIES
// =============================================================================

void drawing_copy_pixel(uint8_t *dest, int dest_channels, int dest_idx, const unsigned char *src, int src_channels,
                        int src_idx, blit_image_color_option_flags_t option, blit_image_color_order_t dest_order,
                        blit_image_color_order_t src_order);
void drawing_blend_pixel(uint8_t *dest, int dest_channels, int dest_idx, uint8_t src_r, uint8_t src_g, uint8_t src_b,
                         uint8_t src_a, int src_channels, blit_image_color_option_flags_t options,
                         blit_image_color_order_t dest_order, blit_image_color_order_t src_order);

// Blit scaled image to destination buffer
void blit_image_scaled(uint8_t *dest, size_t dest_size, int dest_w, int dest_h, int dest_channels,
                       const unsigned char *src, size_t src_size, int src_w, int src_h, int src_channels, int src_x,
                       int src_y, int frame_w, int frame_h, int offset_x, int offset_y, int target_w, int target_h,
                       blit_image_color_order_t dest_order, blit_image_color_order_t src_order,
                       blit_image_color_option_flags_t options);

namespace details {
  struct scale_120_params {
    int logical;
    uint32_t scale120;
  };
  BONGOCAT_NODISCARD int scale_size_120(scale_120_params params);
  BONGOCAT_NODISCARD int scale_offset_120(scale_120_params params);

  struct in_output_logical_size_t {
    int width;
    int height;
  };
  struct output_logical_size_result_t {
    int32_t width{0};
    int32_t height{0};
  };
  BONGOCAT_NODISCARD output_logical_size_result_t output_logical_size(in_output_logical_size_t raw, int transform,
                                                                      int integer_scale, in_output_logical_size_t xdg);
}  // namespace details

}  // namespace bongocat::animation

#endif  // BONGOCAT_ANIMATION_DRAWING_IMAGES_H