#ifndef BONGOCAT_ANIMATION_H
#define BONGOCAT_ANIMATION_H

#include "config/config.h"
#include "utils/error.h"
#include "platform/input_context.h"
#include "animation_context.h"
#include "global_animation_context.h"

namespace bongocat::animation {
    created_result_t<animation_session_t> create(const config::config_t& config);
    bongocat_error_t start(animation_session_t& ctx, platform::input::input_context_t& input);
    void trigger(animation_session_t& ctx);
    void update_config(animation_context_t& ctx, const config::config_t& config);

    enum class drawing_copy_pixel_color_option_t : uint8_t {
        COPY_PIXEL_OPTION_NORMAL,
        COPY_PIXEL_OPTION_INVERT,
    };
    enum class drawing_color_order_t : uint8_t {
        COLOR_ORDER_RGBA,
        COLOR_ORDER_BGRA
    };
    void blit_image_scaled(uint8_t *dest, size_t dest_size, int dest_w, int dest_h, int dest_channels,
                           const unsigned char *src, size_t src_size, int src_w, int src_h, int src_channels,
                           int src_x, int src_y,
                           int frame_w, int frame_h,
                           int offset_x, int offset_y, int target_w, int target_h,
                           drawing_color_order_t dest_order,
                           drawing_color_order_t src_order);
}

#endif // BONGOCAT_ANIMATION_H