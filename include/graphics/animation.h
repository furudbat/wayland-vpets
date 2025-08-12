#ifndef BONGOCAT_ANIMATION_H
#define BONGOCAT_ANIMATION_H

#include "config/config.h"
#include "utils/error.h"
#include "platform/input_context.h"
#include "animation_context.h"
#include "animation_event_context.h"

bongocat_error_t animation_init(animation_trigger_context_t *trigger_ctx, animation_context_t *ctx, const config_t *config);
bongocat_error_t animation_start(animation_trigger_context_t *trigger_ctx, animation_context_t *ctx, input_context_t *input);
void animation_stop(animation_context_t *ctx);
void animation_cleanup(animation_trigger_context_t *trigger_ctx, animation_context_t *ctx);
void animation_trigger(animation_trigger_context_t *ctx);
void animation_update_config(animation_context_t *ctx, const config_t *config);

typedef enum {
    COPY_PIXEL_OPTION_NORMAL,
    COPY_PIXEL_OPTION_INVERT,
} drawing_copy_pixel_color_option_t;
typedef enum {
    COLOR_ORDER_RGBA,
    COLOR_ORDER_BGRA
} drawing_color_order_t;
void blit_image_scaled(uint8_t *dest, size_t dest_size, int dest_w, int dest_h, int dest_channels,
                       const unsigned char *src, size_t src_size, int src_w, int src_h, int src_channels,
                       int src_x, int src_y,
                       int frame_w, int frame_h,
                       int offset_x, int offset_y, int target_w, int target_h,
                       drawing_color_order_t dest_order,
                       drawing_color_order_t src_order);

#endif // ANIMATION_H