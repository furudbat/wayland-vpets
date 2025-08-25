#ifndef BONGOCAT_ANIMATION_DRAWING_IMAGES_H
#define BONGOCAT_ANIMATION_DRAWING_IMAGES_H

#include <cstddef>
#include <cstdint>

namespace bongocat::animation {
    enum class blit_image_color_option_flags_t : uint32_t {
        Invisible = (1u << 0),
        Normal = (1u << 1),
        Invert = (1u << 2),
    };
    enum class blit_image_color_order_t : uint8_t {
        RGBA,
        BGRA
    };

    void drawing_copy_pixel(uint8_t *dest, int dest_channels, int dest_idx,
                                   const unsigned char *src, int src_channels, int src_idx,
                                   blit_image_color_option_flags_t option,
                                   blit_image_color_order_t dest_order,
                                   blit_image_color_order_t src_order);
    void blit_image_scaled(uint8_t *dest, size_t dest_size, int dest_w, int dest_h, int dest_channels,
                           const unsigned char *src, size_t src_size, int src_w, int src_h, int src_channels,
                           int src_x, int src_y,
                           int frame_w, int frame_h,
                           int offset_x, int offset_y, int target_w, int target_h,
                           blit_image_color_order_t dest_order,
                           blit_image_color_order_t src_order,
                           blit_image_color_option_flags_t options);
}

#endif // BONGOCAT_ANIMATION_DRAWING_IMAGES_H