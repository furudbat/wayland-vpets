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

    const config_t *current_config = ctx->_local_copy_config;
    assert(current_config);

    const int effective_opacity = ctx->fullscreen_detected ? 0 : current_config->overlay_opacity;

    // Fast clear with 32-bit fill
    const uint32_t fill = (effective_opacity << 24); // RGBA, little-endian
    uint32_t *p = (uint32_t*)ctx->pixels;
    size_t total_pixels = (size_t)ctx->_screen_width * current_config->bar_height;
    for (size_t i = 0; i < total_pixels; i++) {
        p[i] = fill;
    }

    // Draw cat if visible
    if (!ctx->fullscreen_detected) {
        pthread_mutex_lock(&anim->anim_lock);

        animation_t *cur_anim = &anim->anims[anim->anim_index];
        generic_sprite_sheet_animation_t *sheet = &cur_anim->sprite_sheet;

        const sprite_sheet_animation_region_t *region =
            cur_anim->sprite_sheet.frames[anim->anim_frame_index].valid
            ? &sheet->frames[anim->anim_frame_index]
            : NULL;

        if (region && sheet->frame_width > 0 && sheet->frame_height > 0) {
            const int cat_height = current_config->cat_height;
            const int cat_width  = (int)(cat_height * (sheet->frame_width / (float)sheet->frame_height));

            int cat_x = 0;
            switch (current_config->cat_align) {
                case ALIGN_CENTER:
                    cat_x = (ctx->_screen_width - cat_width) / 2 + current_config->cat_x_offset;
                    break;
                case ALIGN_LEFT:
                    cat_x = current_config->cat_x_offset;
                    break;
                case ALIGN_RIGHT:
                    cat_x = ctx->_screen_width - cat_width - current_config->cat_x_offset;
                    break;
                default:
                    BONGOCAT_LOG_VERBOSE("Invalid cat_align %d", current_config->cat_align);
                    break;
            }
            const int cat_y = (current_config->bar_height - cat_height) / 2 + current_config->cat_y_offset;

            // Draw cat
            blit_image_scaled(ctx->pixels, ctx->pixels_size,
                              ctx->_screen_width, current_config->bar_height, BGRA_CHANNELS,
                              sheet->pixels, sheet->pixels_size,  sheet->sprite_sheet_width, sheet->sprite_sheet_height, sheet->channels,
                              region->col * sheet->frame_width, region->row * sheet->frame_height,
                              sheet->frame_width, sheet->frame_height,
                              cat_x, cat_y, cat_width, cat_height,
                              COLOR_ORDER_BGRA, COLOR_ORDER_RGBA);
        } else {
            BONGOCAT_LOG_VERBOSE("Skip drawing empty frame: index=%d, frame=%d", anim->anim_index, anim->anim_frame_index);
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