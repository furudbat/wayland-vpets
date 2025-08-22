#include "platform/wayland-protocols.hpp"

#include "bar.h"
#include "graphics/animation_context.h"
#include "platform/wayland.h"
#include "graphics/animation.h"
#include <wayland-client.h>
#include <cassert>

namespace bongocat::animation {
    static void frame_done(void *data, wl_callback *cb, [[maybe_unused]] uint32_t time) {
        if (!data) {
            BONGOCAT_LOG_WARNING("Handler called with null data (ignored)");
            return;
        }
        auto& ctx = *static_cast<platform::wayland::wayland_session_t *>(data);

        if (!atomic_load(&ctx.ready)) {
            BONGOCAT_LOG_WARNING("Wayland configured yet, skipping handling");
            return;
        }
        if (!ctx.animation_trigger_context) {
            BONGOCAT_LOG_WARNING("Wayland configured yet, skipping handling");
            return;
        }

        platform::wayland::wayland_context_t& wayland_ctx = ctx.wayland_context;
        //animation_context_t& anim = *ctx->animation_context;
        animation_session_t& trigger_ctx = *ctx.animation_trigger_context;
        //wayland_shared_memory_t& wayland_ctx_shm = wayland_ctx->ctx_shm;
        // read-only
        assert(wayland_ctx._local_copy_config != nullptr);
        const config::config_t& current_config = *wayland_ctx._local_copy_config;
        //const animation_shared_memory_t *const anim_shm = anim->shm;
        //assert(anim_shm);

        do {
            platform::LockGuard guard (wayland_ctx._frame_cb_lock);
            if (wayland_ctx._frame_cb == cb) {
                wl_callback_destroy(wayland_ctx._frame_cb);
                wayland_ctx._frame_cb = nullptr;

                atomic_store(&wayland_ctx._frame_pending, false);
                const platform::timestamp_ms_t now = platform::get_current_time_ms();
                assert(current_config.fps > 0);
                if (const platform::time_ms_t frame_interval_ms = 1000 / current_config.fps; wayland_ctx._last_frame_timestamp_ms <= 0 || (now - wayland_ctx._last_frame_timestamp_ms) >= frame_interval_ms) {
                    wayland_ctx._last_frame_timestamp_ms = now;

                    if (atomic_exchange(&wayland_ctx._redraw_after_frame, false)) {
                        platform::wayland::request_render(trigger_ctx);
                    }
                } else {
                    // Schedule redraw later
                    atomic_store(&wayland_ctx._redraw_after_frame, true);
                }

                BONGOCAT_LOG_VERBOSE("wl_callback.done: frame done");
            } else {
                BONGOCAT_LOG_VERBOSE("wl_callback.done: cb is not matching");
            }
        } while (false);
    }

    /// @NOTE: frame_listeners MUST pass data as wayland_listeners_context_t, see wl_callback_add_listener
    static constexpr wl_callback_listener frame_listener = {
        .done = frame_done
    };

    // =============================================================================
    // DRAWING MANAGEMENT
    // =============================================================================

    struct cat_rect_t {
        int x;
        int y;
        int width;
        int height;
    };

    cat_rect_t get_position(const platform::wayland::wayland_context_t& wayland_ctx, const generic_sprite_sheet_animation_t& sheet, const config::config_t& config) {
        const int cat_height = config.cat_height;
        const int cat_width  = static_cast<int>(static_cast<float>(cat_height) * (static_cast<float>(sheet.frame_width) / static_cast<float>(sheet.frame_height)));

        int cat_x = 0;
        switch (config.cat_align) {
            case config::align_type_t::ALIGN_CENTER:
                cat_x = (wayland_ctx._screen_width - cat_width) / 2 + config.cat_x_offset;
                break;
            case config::align_type_t::ALIGN_LEFT:
                cat_x = config.cat_x_offset;
                break;
            case config::align_type_t::ALIGN_RIGHT:
                cat_x = wayland_ctx._screen_width - cat_width - config.cat_x_offset;
                break;
            default:
                BONGOCAT_LOG_VERBOSE("Invalid cat_align %d", config.cat_align);
                break;
        }
        const int cat_y = (wayland_ctx._bar_height - cat_height) / 2 + config.cat_y_offset;

        return { .x = cat_x, .y = cat_y, .width = cat_width, .height = cat_height };
    }
    cat_rect_t get_position(const platform::wayland::wayland_context_t& wayland_ctx, const ms_pet_sprite_sheet_t& sheet, const config::config_t& config) {
        const int cat_height = config.cat_height;
        const int cat_width  = static_cast<int>(static_cast<float>(cat_height) * (static_cast<float>(sheet.frame_width) / static_cast<float>(sheet.frame_height)));

        int cat_x = 0;
        switch (config.cat_align) {
            case config::align_type_t::ALIGN_CENTER:
                cat_x = (wayland_ctx._screen_width - cat_width) / 2 + config.cat_x_offset;
                break;
            case config::align_type_t::ALIGN_LEFT:
                cat_x = config.cat_x_offset;
                break;
            case config::align_type_t::ALIGN_RIGHT:
                cat_x = wayland_ctx._screen_width - cat_width - config.cat_x_offset;
                break;
            default:
                BONGOCAT_LOG_VERBOSE("Invalid cat_align %d", config.cat_align);
                break;
        }
        const int cat_y = (wayland_ctx._bar_height - cat_height) / 2 + config.cat_y_offset;

        return { .x = cat_x, .y = cat_y, .width = cat_width, .height = cat_height };
    }

    void draw_sprite(platform::wayland::wayland_session_t& ctx, const generic_sprite_sheet_animation_t& sheet) {
        if (sheet.frame_width <= 0 || sheet.frame_height <= 0) {
            return;
        }

        platform::wayland::wayland_context_t& wayland_ctx = ctx.wayland_context;
        animation_context_t& anim = ctx.animation_trigger_context->anim;
        //animation_trigger_context_t *trigger_ctx = ctx.animation_trigger_context;
        platform::wayland::wayland_shared_memory_t *wayland_ctx_shm = wayland_ctx.ctx_shm.ptr;

        assert(wayland_ctx._local_copy_config != nullptr);
        assert(anim.shm != nullptr);
        const config::config_t& current_config = *wayland_ctx._local_copy_config.ptr;
        const animation_shared_memory_t& anim_shm = *anim.shm;

        assert(wayland_ctx_shm->current_buffer_index >= 0);
        assert(platform::wayland::WAYLAND_NUM_BUFFERS <= INT_MAX);
        const int next_buffer_index = (wayland_ctx_shm->current_buffer_index + 1) % static_cast<int>(platform::wayland::WAYLAND_NUM_BUFFERS);
        platform::wayland::wayland_shm_buffer_t *shm_buffer = &wayland_ctx_shm->buffers[next_buffer_index];

        uint8_t *pixels = shm_buffer->pixels.data;
        const size_t pixels_size = shm_buffer->pixels._size_bytes;

        const sprite_sheet_animation_region_t* region = sheet.frames[anim_shm.animation_player_data.frame_index].valid
                    ? &sheet.frames[anim_shm.animation_player_data.frame_index]
                    : nullptr;

        auto [cat_x, cat_y, cat_width, cat_height] = get_position(wayland_ctx, sheet, current_config);

        if (region) {
            blit_image_scaled(pixels, pixels_size,
                              wayland_ctx._screen_width, wayland_ctx._bar_height, BGRA_CHANNELS,
                              sheet.pixels.data, sheet.pixels._size_bytes,  sheet.sprite_sheet_width, sheet.sprite_sheet_height, sheet.channels,
                              region->col * sheet.frame_width, region->row * sheet.frame_height,
                              sheet.frame_width, sheet.frame_height,
                              cat_x, cat_y, cat_width, cat_height,
                              drawing_color_order_t::COLOR_ORDER_BGRA, drawing_color_order_t::COLOR_ORDER_RGBA);
        }
    }

#ifndef FEATURE_INCLUDE_ONLY_BONGOCAT_EMBEDDED_ASSETS
    void draw_sprite(platform::wayland::wayland_session_t& ctx, const ms_pet_sprite_sheet_t& sheet, int col, int row) {
        if (sheet.frame_width <= 0 || sheet.frame_height <= 0) {
            return;
        }

        platform::wayland::wayland_context_t& wayland_ctx = ctx.wayland_context;
        //animation_context_t& anim = ctx.animation_trigger_context->anim;
        //animation_trigger_context_t *trigger_ctx = ctx.animation_trigger_context;
        platform::wayland::wayland_shared_memory_t *wayland_ctx_shm = wayland_ctx.ctx_shm.ptr;

        assert(wayland_ctx._local_copy_config != nullptr);
        //assert(anim.shm != nullptr);
        const config::config_t& current_config = *wayland_ctx._local_copy_config.ptr;
        //const animation_shared_memory_t& anim_shm = *anim.shm;

        assert(wayland_ctx_shm->current_buffer_index >= 0);
        assert(platform::wayland::WAYLAND_NUM_BUFFERS <= INT_MAX);
        const int next_buffer_index = (wayland_ctx_shm->current_buffer_index + 1) % static_cast<int>(platform::wayland::WAYLAND_NUM_BUFFERS);
        platform::wayland::wayland_shm_buffer_t *shm_buffer = &wayland_ctx_shm->buffers[next_buffer_index];

        uint8_t *pixels = shm_buffer->pixels.data;
        const size_t pixels_size = shm_buffer->pixels._size_bytes;

        auto [cat_x, cat_y, cat_width, cat_height] = get_position(wayland_ctx, sheet, current_config);

        blit_image_scaled(pixels, pixels_size,
                          wayland_ctx._screen_width, wayland_ctx._bar_height, BGRA_CHANNELS,
                          sheet.pixels.data, sheet.pixels._size_bytes,  sheet.sprite_sheet_width, sheet.sprite_sheet_height, sheet.channels,
                          col * sheet.frame_width, row * sheet.frame_height,
                          sheet.frame_width, sheet.frame_height,
                          cat_x, cat_y, cat_width, cat_height,
                          drawing_color_order_t::COLOR_ORDER_BGRA, drawing_color_order_t::COLOR_ORDER_RGBA);
    }
#endif

    bool draw_bar(platform::wayland::wayland_session_t& ctx) {
        platform::wayland::wayland_context_t& wayland_ctx = ctx.wayland_context;
        animation_context_t& anim = ctx.animation_trigger_context->anim;
        //animation_trigger_context_t *trigger_ctx = ctx.animation_trigger_context;
        platform::wayland::wayland_shared_memory_t *wayland_ctx_shm = wayland_ctx.ctx_shm.ptr;

        // read-only
        assert(wayland_ctx._local_copy_config != nullptr);
        assert(anim.shm != nullptr);
        const config::config_t& current_config = *wayland_ctx._local_copy_config.ptr;
        const animation_shared_memory_t& anim_shm = *anim.shm;

        if (!atomic_load(&wayland_ctx_shm->configured)) {
            BONGOCAT_LOG_VERBOSE("Surface not configured yet, skipping draw");
            return false;
        }

        assert(wayland_ctx_shm->current_buffer_index >= 0);
        assert(platform::wayland::WAYLAND_NUM_BUFFERS <= INT_MAX);
        const int next_buffer_index = (wayland_ctx_shm->current_buffer_index + 1) % static_cast<int>(platform::wayland::WAYLAND_NUM_BUFFERS);
        platform::wayland::wayland_shm_buffer_t *shm_buffer = &wayland_ctx_shm->buffers[next_buffer_index];

        if (atomic_load(&shm_buffer->busy)) {
            BONGOCAT_LOG_VERBOSE("Buffer still busy, skip drawing: buffer: %i", next_buffer_index);
            atomic_store(&shm_buffer->pending, true);
            return false;
        }


        uint8_t *pixels = shm_buffer->pixels.data;
        const size_t pixels_size = shm_buffer->pixels._size_bytes;

        const int effective_opacity = wayland_ctx._fullscreen_detected ? 0 : current_config.overlay_opacity;

        assert(wayland_ctx._screen_width >= 0);
        assert(wayland_ctx._bar_height >= 0);
        assert(effective_opacity >= 0);

        // Fast clear with 32-bit fill
        const uint32_t fill = (static_cast<unsigned>(effective_opacity) << 24u); // RGBA, little-endian
        auto *p = reinterpret_cast<uint32_t *>(pixels);
        const size_t total_pixels = static_cast<size_t>(wayland_ctx._screen_width) * static_cast<size_t>(wayland_ctx._bar_height);
        if (current_config.enable_debug) {
            if (const size_t expected_bytes = total_pixels * sizeof(uint32_t); expected_bytes > pixels_size) {
                BONGOCAT_LOG_VERBOSE("draw_bar: pixel write would overflow buffer (expected %zu bytes, have %zu). Aborting draw.",
                                     expected_bytes, pixels_size);
                return false;
            }
        }
        for (size_t i = 0; i < total_pixels; i++) {
            p[i] = fill;
        }

        do {
            platform::LockGuard guard (anim.anim_lock);

            if (!wayland_ctx._fullscreen_detected) {
                switch (anim_shm.anim_type) {
                    case config::config_animation_type_t::None:
                        break;
                    case config::config_animation_type_t::Bongocat: {
#ifdef FEATURE_BONGOCAT_EMBEDDED_ASSETS
                        const animation_t& cat_anim = anim_shm.bongocat_anims[anim_shm.anim_index];
                        const generic_sprite_sheet_animation_t& sheet = cat_anim.sprite_sheet;
                        draw_sprite(ctx, sheet);
#endif
                    }break;
                    case config::config_animation_type_t::Digimon: {
#ifdef FEATURE_DIGIMON_EMBEDDED_ASSETS
                        const animation_t& dm_anim = anim_shm.dm_anims[anim_shm.anim_index];
                        const generic_sprite_sheet_animation_t& sheet = dm_anim.sprite_sheet;
                        draw_sprite(ctx, sheet);
#endif
                    }break;
                    case config::config_animation_type_t::MsPet:{
#ifdef FEATURE_CLIPPY_EMBEDDED_ASSETS
                        const ms_pet_sprite_sheet_t& sheet = anim_shm.ms_anims[anim_shm.anim_index];
                        const int col = anim_shm.animation_player_data.frame_index;
                        const int row = anim_shm.animation_player_data.sprite_sheet_row;
                        draw_sprite(ctx, sheet, col, row);
#endif
                    }break;
                }
            } else {
                BONGOCAT_LOG_VERBOSE("fullscreen detected, skip drawing, keep buffer clean");
            }
        } while (false);

        assert(shm_buffer->buffer);

        atomic_store(&shm_buffer->busy, true);
        wl_surface_attach(wayland_ctx.surface, shm_buffer->buffer, 0, 0);
        wl_surface_damage_buffer(wayland_ctx.surface, 0, 0, wayland_ctx._screen_width, wayland_ctx._bar_height);
        wl_surface_commit(wayland_ctx.surface);
        wayland_ctx_shm->current_buffer_index = next_buffer_index;

        do {
            platform::LockGuard guard (wayland_ctx._frame_cb_lock);
            if (!atomic_load(&wayland_ctx._frame_pending) && !wayland_ctx._frame_cb) {
                wayland_ctx._frame_cb = wl_surface_frame(wayland_ctx.surface);
                wl_callback_add_listener(wayland_ctx._frame_cb, &frame_listener, &ctx);
                atomic_store(&wayland_ctx._frame_pending, true);
                BONGOCAT_LOG_VERBOSE("Set frame pending");
            }
        } while (false);

        return true;
    }
}