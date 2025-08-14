#include "bar.h"
#include "graphics/animation_context.h"
#include "platform/wayland.h"
#include "graphics/animation.h"
#include "../protocols/wlr-foreign-toplevel-management-v1-client-protocol.h"
#include <wayland-client.h>
#include <cassert>
#include <pthread.h>

static void frame_done(void *data, wl_callback *cb, [[maybe_unused]] uint32_t time) {
    assert(data);
    auto *ctx = static_cast<wayland_listeners_context_t *>(data);

    assert(ctx->wayland_context);
    assert(ctx->animation_trigger_context);
    wayland_context_t& wayland_ctx = *ctx->wayland_context;
    //animation_context_t& anim = *ctx->animation_context;
    animation_trigger_context_t& trigger_ctx = *ctx->animation_trigger_context;
    //wayland_shared_memory_t& wayland_ctx_shm = wayland_ctx->ctx_shm;
    // read-only
    assert(wayland_ctx._local_copy_config);
    const config_t& current_config = *wayland_ctx._local_copy_config;
    //const animation_shared_memory_t *const anim_shm = anim->shm;
    //assert(anim_shm);

    pthread_mutex_lock(&wayland_ctx._frame_cb_lock);
    if (wayland_ctx._frame_cb == cb) {
        wl_callback_destroy(wayland_ctx._frame_cb);
        wayland_ctx._frame_cb = nullptr;

        atomic_store(&wayland_ctx._frame_pending, false);
        const timestamp_ms_t now = get_current_time_ms();
        assert(current_config.fps > 0);
        if (const time_ms_t frame_interval_ms = 1000 / current_config.fps; wayland_ctx._last_frame_timestamp_ms <= 0 || (now - wayland_ctx._last_frame_timestamp_ms) >= frame_interval_ms) {
            wayland_ctx._last_frame_timestamp_ms = now;

            if (atomic_exchange(&wayland_ctx._redraw_after_frame, false)) {
                wayland_request_render(trigger_ctx);
            }
        } else {
            // Schedule redraw later
            atomic_store(&wayland_ctx._redraw_after_frame, true);
        }

        BONGOCAT_LOG_VERBOSE("wl_callback.done: frame done");
    } else {
        BONGOCAT_LOG_VERBOSE("wl_callback.done: cb is not matching");
    }
    pthread_mutex_unlock(&wayland_ctx._frame_cb_lock);
}

/// @NOTE: frame_listeners MUST pass data as wayland_listeners_context_t, see wl_callback_add_listener
static constexpr wl_callback_listener frame_listener = {
    .done = frame_done
};

// =============================================================================
// DRAWING MANAGEMENT
// =============================================================================

bool draw_bar(wayland_listeners_context_t& ctx) {
    wayland_context_t *wayland_ctx = ctx.wayland_context;
    animation_context_t *anim = ctx.animation_context;
    //animation_trigger_context_t *trigger_ctx = ctx.animation_trigger_context;
    wayland_shared_memory_t *wayland_ctx_shm = wayland_ctx->ctx_shm;

    // read-only
    const config_t *const current_config = wayland_ctx->_local_copy_config;
    assert(current_config);
    const animation_shared_memory_t *const anim_shm = anim->shm;
    assert(anim_shm);

    if (!atomic_load(&wayland_ctx_shm->configured)) {
        BONGOCAT_LOG_VERBOSE("Surface not configured yet, skipping draw");
        return false;
    }

    assert(wayland_ctx_shm->current_buffer_index >= 0);
    assert(WAYLAND_NUM_BUFFERS <= INT_MAX);
    const int next_buffer_index = (wayland_ctx_shm->current_buffer_index + 1) % static_cast<int>(WAYLAND_NUM_BUFFERS);
    wayland_shm_buffer_t *shm_buffer = &wayland_ctx_shm->buffers[next_buffer_index];

    if (atomic_load(&shm_buffer->busy)) {
        BONGOCAT_LOG_VERBOSE("Buffer still busy, skip drawing: buffer: %i", next_buffer_index);
        atomic_store(&shm_buffer->pending, true);
        return false;
    }


    uint8_t *pixels = shm_buffer->pixels;
    const size_t pixels_size = shm_buffer->pixels_size;

    const int effective_opacity = wayland_ctx->_fullscreen_detected ? 0 : current_config->overlay_opacity;

    // Fast clear with 32-bit fill
    const uint32_t fill = (effective_opacity << 24); // RGBA, little-endian
    auto *p = reinterpret_cast<uint32_t *>(pixels);
    const size_t total_pixels = static_cast<size_t>(wayland_ctx->_screen_width) * current_config->bar_height;
    if (current_config->enable_debug) {
        if (const size_t expected_bytes = total_pixels * sizeof(uint32_t); expected_bytes > pixels_size) {
            BONGOCAT_LOG_VERBOSE("draw_bar: pixel write would overflow buffer (expected %zu bytes, have %zu). Aborting draw.",
                                 expected_bytes, pixels_size);
            return false;
        }
    }
    for (size_t i = 0; i < total_pixels; i++) {
        p[i] = fill;
    }

    pthread_mutex_lock(&anim->anim_lock);

    const animation_t *cur_anim = &anim_shm->anims[anim_shm->anim_index];
    const generic_sprite_sheet_animation_t *sheet = &cur_anim->sprite_sheet;

    const sprite_sheet_animation_region_t *region =
        cur_anim->sprite_sheet.frames[anim_shm->anim_frame_index].valid
        ? &sheet->frames[anim_shm->anim_frame_index]
        : nullptr;

    if (!wayland_ctx->_fullscreen_detected) {
        if (region && sheet->frame_width > 0 && sheet->frame_height > 0) {
            const int cat_height = current_config->cat_height;
            const int cat_width  = static_cast<int>(static_cast<float>(cat_height) * (static_cast<float>(sheet->frame_width) / static_cast<float>(sheet->frame_height)));

            int cat_x = 0;
            switch (current_config->cat_align) {
                case align_type_t::ALIGN_CENTER:
                    cat_x = (wayland_ctx->_screen_width - cat_width) / 2 + current_config->cat_x_offset;
                    break;
                case align_type_t::ALIGN_LEFT:
                    cat_x = current_config->cat_x_offset;
                    break;
                case align_type_t::ALIGN_RIGHT:
                    cat_x = wayland_ctx->_screen_width - cat_width - current_config->cat_x_offset;
                    break;
                default:
                    BONGOCAT_LOG_VERBOSE("Invalid cat_align %d", current_config->cat_align);
                    break;
            }
            const int cat_y = (current_config->bar_height - cat_height) / 2 + current_config->cat_y_offset;

            // Draw cat
            blit_image_scaled(pixels, pixels_size,
                              wayland_ctx->_screen_width, current_config->bar_height, BGRA_CHANNELS,
                              sheet->pixels, sheet->pixels_size,  sheet->sprite_sheet_width, sheet->sprite_sheet_height, sheet->channels,
                              region->col * sheet->frame_width, region->row * sheet->frame_height,
                              sheet->frame_width, sheet->frame_height,
                              cat_x, cat_y, cat_width, cat_height,
                              drawing_color_order_t::COLOR_ORDER_BGRA, drawing_color_order_t::COLOR_ORDER_RGBA);
        } else {
            BONGOCAT_LOG_VERBOSE("Skip drawing empty frame: index=%d, frame=%d", anim_shm->anim_index, anim_shm->anim_frame_index);
        }
    } else {
        BONGOCAT_LOG_VERBOSE("fullscreen detected, skip drawing, keep buffer clean");
    }

    pthread_mutex_unlock(&anim->anim_lock);

    assert(shm_buffer->buffer);

    atomic_store(&shm_buffer->busy, true);
    wl_surface_attach(wayland_ctx->surface, shm_buffer->buffer, 0, 0);
    wl_surface_damage_buffer(wayland_ctx->surface, 0, 0, wayland_ctx->_screen_width, current_config->bar_height);
    wl_surface_commit(wayland_ctx->surface);
    wayland_ctx_shm->current_buffer_index = next_buffer_index;

    pthread_mutex_lock(&wayland_ctx->_frame_cb_lock);
    if (!atomic_load(&wayland_ctx->_frame_pending) && !wayland_ctx->_frame_cb) {
        wayland_ctx->_frame_cb = wl_surface_frame(wayland_ctx->surface);
        wl_callback_add_listener(wayland_ctx->_frame_cb, &frame_listener, &ctx);
        atomic_store(&wayland_ctx->_frame_pending, true);
        BONGOCAT_LOG_VERBOSE("Set frame pending");
    }
    pthread_mutex_unlock(&wayland_ctx->_frame_cb_lock);

    return true;
}