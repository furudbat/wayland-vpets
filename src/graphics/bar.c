#define _POSIX_C_SOURCE 200809L
#include "graphics/bar.h"
#include "graphics/context.h"
#include "platform/wayland.h"
#include "graphics/animation.h"
#include "../protocols/wlr-foreign-toplevel-management-v1-client-protocol.h"
#include <assert.h>
#include <unistd.h>
#include <pthread.h>
#include <wayland-client.h>



// =============================================================================
// DRAWING MANAGEMENT
// =============================================================================

void draw_bar(wayland_context_t *ctx, animation_context_t *anim) {
    assert(ctx);
    if (!atomic_load(&ctx->configured)) {
        BONGOCAT_LOG_VERBOSE("Surface not configured yet, skipping draw");
        return;
    }

    // read-only config
    const config_t* const current_config = ctx->_local_copy_config;
    assert(current_config);

    const int effective_opacity = ctx->fullscreen_detected ? 0 : current_config->overlay_opacity;
    
    // Clear buffer with transparency
    for (int i = 0; i < ctx->_screen_width * current_config->bar_height * RGBA_CHANNELS; i += RGBA_CHANNELS) {
        ctx->pixels[i] = 0;                      // B
        ctx->pixels[i + 1] = 0;                  // G
        ctx->pixels[i + 2] = 0;                  // R
        ctx->pixels[i + 3] = effective_opacity;  // A
    }

    // Draw cat if visible
    if (!ctx->fullscreen_detected) {
        pthread_mutex_lock(&anim->anim_lock);

        const uint8_t* frame_pixels = anim->anims[anim->anim_index].frames[anim->anim_frame_index].pixels;
        const int frame_width = anim->anims[anim->anim_index].frames[anim->anim_frame_index].width;
        const int frame_height = anim->anims[anim->anim_index].frames[anim->anim_frame_index].height;

        if (frame_pixels && frame_width > 0 && frame_height > 0) {
            const int cat_height = current_config->cat_height;
            const int cat_width = cat_height * (frame_width / (float)frame_height);
            int cat_x = 0;
            int cat_y = 0;
            switch (current_config->cat_align) {
                case ALIGN_CENTER:
                    cat_x = (ctx->_screen_width - cat_width) / 2 + current_config->cat_x_offset;
                    break;
                case ALIGN_LEFT:
                    cat_x = 0 + current_config->cat_x_offset;
                    break;
                case ALIGN_RIGHT:
                    cat_x = ctx->_screen_width - cat_width - current_config->cat_x_offset;
                    break;
                default:
                    BONGOCAT_LOG_VERBOSE("Invalid cat_align %d", current_config->cat_align);
                    break;
            }
            // vertical alignment always center
            cat_y = (current_config->bar_height - cat_height) / 2 + current_config->cat_y_offset;

            if (cat_x < -cat_width || cat_x + cat_width > ctx->_screen_width) {
                BONGOCAT_LOG_VERBOSE("Cat out of bounds (cat_x=%d, width=%d, screen_width=%d)",
                                     cat_x, cat_width, ctx->_screen_width);
            }
            if (cat_y < -cat_height || cat_y + cat_height > current_config->bar_height) {
                BONGOCAT_LOG_VERBOSE("Cat out of bounds (cat_y=%d, height=%d, bar_height=%d)",
                                     cat_y, cat_height, current_config->bar_height);
            }

            sblit_image_scaled(ctx->pixels, ctx->pixels_size,
                               ctx->_screen_width, current_config->bar_height,
                               frame_pixels,
                               frame_width * frame_height * RGBA_CHANNELS,
                               frame_width,
                               frame_height,
                               cat_x, cat_y, cat_width, cat_height);
        } else {
            BONGOCAT_LOG_VERBOSE("Skip drawing empty frame: index: %d, frame: %d", anim->anim_index, anim->anim_frame_index);
        }
        pthread_mutex_unlock(&anim->anim_lock);
    } else {
        BONGOCAT_LOG_VERBOSE("Cat hidden due to fullscreen detection");
    }

    wl_surface_attach(ctx->surface, ctx->buffer, 0, 0);
    wl_surface_damage_buffer(ctx->surface, 0, 0, ctx->_screen_width, current_config->bar_height);
    wl_surface_commit(ctx->surface);
    wl_display_flush(ctx->display);
}
