#include "platform/wayland-protocols.hpp"

#include "bar.h"
#include "graphics/drawing.h"
#include "graphics/animation_context.h"
#include "platform/wayland.h"
#include "graphics/animation.h"
#include <wayland-client.h>
#include <cassert>

#include "embedded_assets/misc/misc.hpp"

namespace bongocat::animation {
    inline static uint32_t DEFAULT_FILL_COLOR = 0x00000000; // ARGB
    inline static uint32_t DEBUG_MOVEMENT_BAR_COLOR = 0xFFFF0000; // ARGB

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

        {
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
        }
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

    cat_rect_t get_position(const platform::wayland::wayland_context_t& wayland_ctx, const generic_sprite_sheet_t& sheet, const config::config_t& config) {
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
    cat_rect_t get_position(const platform::wayland::wayland_context_t& wayland_ctx, const ms_agent_sprite_sheet_t& sheet, const config::config_t& config) {
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
    cat_rect_t get_position(const platform::wayland::wayland_context_t& wayland_ctx, const custom_sprite_sheet_t& sheet, const config::config_t& config) {
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

    void draw_sprite(platform::wayland::wayland_session_t& ctx, const generic_sprite_sheet_t& sheet, blit_image_color_option_flags_t extra_drawing_option = blit_image_color_option_flags_t::Normal) {
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
        const int frame_index = anim_shm.animation_player_result.sprite_sheet_col;

        assert(wayland_ctx_shm->current_buffer_index >= 0);
        assert(platform::wayland::WAYLAND_NUM_BUFFERS <= INT_MAX);
        const int next_buffer_index = (wayland_ctx_shm->current_buffer_index + 1) % static_cast<int>(platform::wayland::WAYLAND_NUM_BUFFERS);
        platform::wayland::wayland_shm_buffer_t *shm_buffer = &wayland_ctx_shm->buffers[next_buffer_index];

        uint8_t *pixels = shm_buffer->pixels.data;
        const size_t pixels_size = shm_buffer->pixels._size_bytes;

        assert(frame_index >= 0 && static_cast<size_t>(frame_index) < MAX_NUM_FRAMES);
        const sprite_sheet_animation_frame_t* region = sheet.frames[frame_index].valid
                    ? &sheet.frames[frame_index]
                    : nullptr;

        auto [cat_x, cat_y, cat_width, cat_height] = get_position(wayland_ctx, sheet, current_config);
        auto cat_x_with_offset  = cat_x + static_cast<int32_t>(anim_shm.movement_offset_x);

        if (region) {
            // draw debug rectangle
            if (current_config.enable_movement_debug && current_config.movement_radius > 0) {
                cat_rect_t movement_debug_bar{};
                switch (current_config.cat_align) {
                    case config::align_type_t::ALIGN_CENTER:
                        movement_debug_bar = { .x = cat_x + cat_width/2 - current_config.movement_radius, .y = 0, .width = current_config.movement_radius * 2, .height = wayland_ctx._bar_height };
                        break;
                    case config::align_type_t::ALIGN_LEFT:
                        movement_debug_bar = { .x = cat_x, .y = 0, .width = current_config.movement_radius * 2, .height = wayland_ctx._bar_height };
                        break;
                    case config::align_type_t::ALIGN_RIGHT:
                        movement_debug_bar = { .x = cat_x + cat_width - current_config.movement_radius*2, .y = 0, .width = current_config.movement_radius * 2, .height = wayland_ctx._bar_height };
                        break;
                }

                const bool bar_visible = !wayland_ctx._fullscreen_detected && wayland_ctx.bar_visibility == platform::wayland::bar_visibility_t::Show;
                const int effective_opacity = bar_visible ? current_config.overlay_opacity : 0;
                const uint32_t fill = DEBUG_MOVEMENT_BAR_COLOR & (0x00FFFFFF | (static_cast<uint32_t>(effective_opacity) << 24u)); // RGBA, little-endian
                auto *p = reinterpret_cast<uint32_t *>(pixels);
                assert(wayland_ctx._screen_width >= 0);
                [[maybe_unused]] const size_t total_pixels = static_cast<size_t>(wayland_ctx._screen_width) * static_cast<size_t>(wayland_ctx._bar_height);
                for (int32_t y = movement_debug_bar.y;y < movement_debug_bar.y + movement_debug_bar.height && y < wayland_ctx._bar_height; y++) {
                    for (int32_t x = movement_debug_bar.x;x < movement_debug_bar.x + movement_debug_bar.width && x < wayland_ctx._screen_width; x++) {
                        if (x >= 0 && y >= 0) {
                            size_t pi = static_cast<size_t>(x) + static_cast<size_t>(y) * static_cast<size_t>(wayland_ctx._screen_width);
                            assert(pi < total_pixels);
                            p[pi] = fill;
                        }
                    }
                }
            }

            blit_image_color_option_flags_t drawing_option = blit_image_color_option_flags_t::Normal;
            if (current_config.invert_color) {
                drawing_option = flag_add(drawing_option, blit_image_color_option_flags_t::Invert);
            }
            if (anim_shm.anim_direction >= 1.0f) {
                if (!current_config.mirror_x) {
                    drawing_option = flag_add(drawing_option, blit_image_color_option_flags_t::MirrorX);
                }
            } else {
                if (current_config.mirror_x) {
                    drawing_option = flag_add(drawing_option, blit_image_color_option_flags_t::MirrorX);
                }
            }
            if (current_config.mirror_y) {
                drawing_option = flag_add(drawing_option, blit_image_color_option_flags_t::MirrorY);
            }
            if (extra_drawing_option != blit_image_color_option_flags_t::Normal) {
                drawing_option = flag_add(drawing_option, extra_drawing_option);
            }

            blit_image_scaled(pixels, pixels_size,
                              wayland_ctx._screen_width, wayland_ctx._bar_height, BGRA_CHANNELS,
                              sheet.image.pixels.data, sheet.image.pixels._size_bytes,  sheet.image.sprite_sheet_width, sheet.image.sprite_sheet_height, sheet.image.channels,
                              region->col * sheet.frame_width, region->row * sheet.frame_height,
                              sheet.frame_width, sheet.frame_height,
                              cat_x_with_offset, cat_y, cat_width, cat_height,
                              blit_image_color_order_t::BGRA, blit_image_color_order_t::RGBA, drawing_option);
        }
    }

    void draw_sprite(platform::wayland::wayland_session_t& ctx, const ms_agent_sprite_sheet_t& sheet, int col, int row) {
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

        blit_image_color_option_flags_t drawing_option = blit_image_color_option_flags_t::Normal;
        if (current_config.invert_color) {
            drawing_option = flag_add(drawing_option, blit_image_color_option_flags_t::Invert);
        }
        if (current_config.mirror_x) {
            drawing_option = flag_add(drawing_option, blit_image_color_option_flags_t::MirrorX);
        }
        if (current_config.mirror_y) {
            drawing_option = flag_add(drawing_option, blit_image_color_option_flags_t::MirrorY);
        }
        if (current_config.enable_antialiasing) {
            drawing_option = flag_add(drawing_option, blit_image_color_option_flags_t::BilinearInterpolation);
        }

        blit_image_scaled(pixels, pixels_size,
                          wayland_ctx._screen_width, wayland_ctx._bar_height, BGRA_CHANNELS,
                          sheet.image.pixels.data, sheet.image.pixels._size_bytes,  sheet.image.sprite_sheet_width, sheet.image.sprite_sheet_height, sheet.image.channels,
                          col * sheet.frame_width, row * sheet.frame_height,
                          sheet.frame_width, sheet.frame_height,
                          cat_x, cat_y, cat_width, cat_height,
                          blit_image_color_order_t::BGRA, blit_image_color_order_t::RGBA, drawing_option);
    }

    void draw_sprite(platform::wayland::wayland_session_t& ctx, const custom_sprite_sheet_t& sheet, int col, int row) {
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

        auto [cat_x, cat_y, cat_width, cat_height] = get_position(wayland_ctx, sheet, current_config);
        auto cat_x_with_offset  = cat_x + static_cast<int32_t>(anim_shm.movement_offset_x);

        // draw debug rectangle
        if (current_config.enable_movement_debug && current_config.movement_radius > 0) {
            cat_rect_t movement_debug_bar{};
            switch (current_config.cat_align) {
                case config::align_type_t::ALIGN_CENTER:
                    movement_debug_bar = { .x = cat_x + cat_width/2 - current_config.movement_radius, .y = 0, .width = current_config.movement_radius * 2, .height = wayland_ctx._bar_height };
                    break;
                case config::align_type_t::ALIGN_LEFT:
                    movement_debug_bar = { .x = cat_x, .y = 0, .width = current_config.movement_radius * 2, .height = wayland_ctx._bar_height };
                    break;
                case config::align_type_t::ALIGN_RIGHT:
                    movement_debug_bar = { .x = cat_x + cat_width - current_config.movement_radius*2, .y = 0, .width = current_config.movement_radius * 2, .height = wayland_ctx._bar_height };
                    break;
            }

            const bool bar_visible = !wayland_ctx._fullscreen_detected && wayland_ctx.bar_visibility == platform::wayland::bar_visibility_t::Show;
            const int effective_opacity = bar_visible ? current_config.overlay_opacity : 0;
            const uint32_t fill = DEBUG_MOVEMENT_BAR_COLOR & (0x00FFFFFF | (static_cast<uint32_t>(effective_opacity) << 24u)); // RGBA, little-endian
            auto *p = reinterpret_cast<uint32_t *>(pixels);
            assert(wayland_ctx._screen_width >= 0);
            [[maybe_unused]] const size_t total_pixels = static_cast<size_t>(wayland_ctx._screen_width) * static_cast<size_t>(wayland_ctx._bar_height);
            for (int32_t y = movement_debug_bar.y;y < movement_debug_bar.y + movement_debug_bar.height && y < wayland_ctx._bar_height; y++) {
                for (int32_t x = movement_debug_bar.x;x < movement_debug_bar.x + movement_debug_bar.width && x < wayland_ctx._screen_width; x++) {
                    if (x >= 0 && y >= 0) {
                        size_t pi = static_cast<size_t>(x) + static_cast<size_t>(y) * static_cast<size_t>(wayland_ctx._screen_width);
                        assert(pi < total_pixels);
                        p[pi] = fill;
                    }
                }
            }
        }

        blit_image_color_option_flags_t drawing_option = blit_image_color_option_flags_t::Normal;
        if (current_config.invert_color) {
            drawing_option = flag_add(drawing_option, blit_image_color_option_flags_t::Invert);
        }
        if (anim_shm.anim_direction >= 1.0f) {
            if (!current_config.mirror_x) {
                drawing_option = flag_add(drawing_option, blit_image_color_option_flags_t::MirrorX);
            }
        } else {
            if (current_config.mirror_x) {
                drawing_option = flag_add(drawing_option, blit_image_color_option_flags_t::MirrorX);
            }
        }
        if (current_config.mirror_y) {
            drawing_option = flag_add(drawing_option, blit_image_color_option_flags_t::MirrorY);
        }
        if (current_config.enable_antialiasing) {
            drawing_option = flag_add(drawing_option, blit_image_color_option_flags_t::BilinearInterpolation);
        }
        /*
        if (extra_drawing_option != blit_image_color_option_flags_t::Normal) {
            drawing_option = flag_add(drawing_option, extra_drawing_option);
        }
        */

        blit_image_scaled(pixels, pixels_size,
                          wayland_ctx._screen_width, wayland_ctx._bar_height, BGRA_CHANNELS,
                          sheet.image.pixels.data, sheet.image.pixels._size_bytes,  sheet.image.sprite_sheet_width, sheet.image.sprite_sheet_height, sheet.image.channels,
                          col * sheet.frame_width, row * sheet.frame_height,
                          sheet.frame_width, sheet.frame_height,
                          cat_x_with_offset, cat_y, cat_width, cat_height,
                          blit_image_color_order_t::BGRA, blit_image_color_order_t::RGBA, drawing_option);
    }

    bool draw_bar(platform::wayland::wayland_session_t& ctx) {
        platform::wayland::wayland_context_t& wayland_ctx = ctx.wayland_context;
        animation_context_t& anim = ctx.animation_trigger_context->anim;
        //animation_trigger_context_t *trigger_ctx = ctx.animation_trigger_context;
        platform::wayland::wayland_shared_memory_t *wayland_ctx_shm = wayland_ctx.ctx_shm.ptr;

        // read-only
        assert(wayland_ctx._local_copy_config != nullptr);
        assert(anim.shm != nullptr);
        const config::config_t& current_config = *wayland_ctx._local_copy_config.ptr;

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

        const bool bar_visible = !wayland_ctx._fullscreen_detected && wayland_ctx.bar_visibility == platform::wayland::bar_visibility_t::Show;
        const int effective_opacity = bar_visible ? current_config.overlay_opacity : 0;

        assert(wayland_ctx._screen_width >= 0);
        assert(wayland_ctx._bar_height >= 0);
        assert(effective_opacity >= 0);

        // Fast clear with 32-bit fill
        const uint32_t fill = DEFAULT_FILL_COLOR | (static_cast<uint32_t>(effective_opacity) << 24u); // RGBA, little-endian
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

        {
            platform::LockGuard guard (anim.anim_lock);
            const animation_shared_memory_t& anim_shm = *anim.shm;

            if (bar_visible) {
                switch (anim_shm.anim_type) {
                    case config::config_animation_sprite_sheet_layout_t::None:
                        break;
                    case config::config_animation_sprite_sheet_layout_t::Bongocat: {
                        if constexpr (!features::EnableLazyLoadAssets || features::EnablePreloadAssets) {
                            assert(anim_shm.anim_index >= 0 && static_cast<size_t>(anim_shm.anim_index) < anim_shm.bongocat_anims.count);
                        }
                        const animation_t& cat_anim = get_current_animation(anim);
                        assert(cat_anim.type == animation_t::Type::Bongocat);
                        const generic_sprite_sheet_t& sheet = cat_anim.sprite_sheet;
                        draw_sprite(ctx, sheet, current_config.enable_antialiasing ? blit_image_color_option_flags_t::BilinearInterpolation : blit_image_color_option_flags_t::Normal);
                    }break;
                    case config::config_animation_sprite_sheet_layout_t::Dm: {
                        if constexpr (!features::EnableLazyLoadAssets || features::EnablePreloadAssets) {
                            switch (anim_shm.anim_dm_set) {
                                case config::config_animation_dm_set_t::None:
                                    break;
                                case config::config_animation_dm_set_t::min_dm: {
                                    assert(anim_shm.anim_index >= 0 && static_cast<size_t>(anim_shm.anim_index) < anim_shm.min_dm_anims.count);
                                }break;
                                case config::config_animation_dm_set_t::dm: {
                                    assert(anim_shm.anim_index >= 0 && static_cast<size_t>(anim_shm.anim_index) < anim_shm.dm_anims.count);
                                }break;
                                case config::config_animation_dm_set_t::dm20: {
                                    assert(anim_shm.anim_index >= 0 && static_cast<size_t>(anim_shm.anim_index) < anim_shm.dm20_anims.count);
                                }break;
                                case config::config_animation_dm_set_t::dmx: {
                                    assert(anim_shm.anim_index >= 0 && static_cast<size_t>(anim_shm.anim_index) < anim_shm.dmx_anims.count);
                                }break;
                                case config::config_animation_dm_set_t::pen: {
                                    assert(anim_shm.anim_index >= 0 && static_cast<size_t>(anim_shm.anim_index) < anim_shm.pen_anims.count);
                                }break;
                                case config::config_animation_dm_set_t::pen20: {
                                    assert(anim_shm.anim_index >= 0 && static_cast<size_t>(anim_shm.anim_index) < anim_shm.pen20_anims.count);
                                }break;
                                case config::config_animation_dm_set_t::dmc: {
                                    assert(anim_shm.anim_index >= 0 && static_cast<size_t>(anim_shm.anim_index) < anim_shm.dmc_anims.count);
                                }break;
                                case config::config_animation_dm_set_t::dmall: {
                                    assert(anim_shm.anim_index >= 0 && static_cast<size_t>(anim_shm.anim_index) < anim_shm.dmall_anims.count);
                                }break;
                            }
                        }
                        const animation_t& dm_anim = get_current_animation(anim);
                        assert(dm_anim.type == animation_t::Type::Dm);
                        const generic_sprite_sheet_t& sheet = dm_anim.sprite_sheet;
                        draw_sprite(ctx, sheet);
                    }break;
                    case config::config_animation_sprite_sheet_layout_t::Pkmn: {
                        if constexpr (!features::EnableLazyLoadAssets || features::EnablePreloadAssets) {
                            assert(anim_shm.anim_index >= 0 && static_cast<size_t>(anim_shm.anim_index) < anim_shm.pkmn_anims.count);
                        }
                        const animation_t& pkmn_anim = get_current_animation(anim);
                        assert(pkmn_anim.type == animation_t::Type::Pkmn);
                        const generic_sprite_sheet_t& sheet = pkmn_anim.sprite_sheet;
                        draw_sprite(ctx, sheet);
                    }break;
                    case config::config_animation_sprite_sheet_layout_t::MsAgent:{
                        if constexpr (!features::EnableLazyLoadAssets || features::EnablePreloadAssets) {
                            assert(anim_shm.anim_index >= 0 && static_cast<size_t>(anim_shm.anim_index) < anim_shm.ms_anims.count);
                        }
                        const animation_t& ms_anim = get_current_animation(anim);
                        assert(ms_anim.type == animation_t::Type::MsAgent);
                        const ms_agent_sprite_sheet_t& sheet = ms_anim.ms_agent;
                        const int col = anim_shm.animation_player_result.sprite_sheet_col;
                        const int row = anim_shm.animation_player_result.sprite_sheet_row;
                        draw_sprite(ctx, sheet, col, row);
                    }break;
                    case config::config_animation_sprite_sheet_layout_t::Custom:{
                        const int col = anim_shm.animation_player_result.sprite_sheet_col;
                        const int row = anim_shm.animation_player_result.sprite_sheet_row;
                        assert(anim_shm.anim_index >= 0);
                        if (features::EnableCustomSpriteSheetsAssets && anim_shm.anim_index >= 0 && static_cast<size_t>(anim_shm.anim_index) == assets::CUSTOM_ANIM_INDEX) {
                            const animation_t& custom_anim = get_current_animation(anim);
                            assert(custom_anim.type == animation_t::Type::Custom);
                            const custom_sprite_sheet_t& sheet = custom_anim.custom;
                            draw_sprite(ctx, sheet, col, row);
                        } else if (features::EnableMiscEmbeddedAssets) {
                            if constexpr (!features::EnableLazyLoadAssets || features::EnablePreloadAssets) {
                                assert(anim_shm.anim_index >= 0 && static_cast<size_t>(anim_shm.anim_index) < anim_shm.misc_anims.count);
                            }
                            const animation_t& custom_anim = get_current_animation(anim);
                            assert(custom_anim.type == animation_t::Type::Custom);
                            const custom_sprite_sheet_t& sheet = custom_anim.custom;
                            draw_sprite(ctx, sheet, col, row);
                        }
                    }break;
                }
            } else {
                BONGOCAT_LOG_VERBOSE("skip drawing, keep buffer clean: fullscreen=%d, visibility=%d", wayland_ctx._fullscreen_detected, wayland_ctx.bar_visibility);
            }
        }

        assert(shm_buffer->buffer);

        atomic_store(&shm_buffer->busy, true);
        wl_surface_attach(wayland_ctx.surface, shm_buffer->buffer, 0, 0);
        wl_surface_damage_buffer(wayland_ctx.surface, 0, 0, wayland_ctx._screen_width, wayland_ctx._bar_height);
        wl_surface_commit(wayland_ctx.surface);
        wayland_ctx_shm->current_buffer_index = next_buffer_index;

        {
            platform::LockGuard guard (wayland_ctx._frame_cb_lock);
            if (!atomic_load(&wayland_ctx._frame_pending) && !wayland_ctx._frame_cb) {
                wayland_ctx._frame_cb = wl_surface_frame(wayland_ctx.surface);
                wl_callback_add_listener(wayland_ctx._frame_cb, &frame_listener, &ctx);
                atomic_store(&wayland_ctx._frame_pending, true);
                BONGOCAT_LOG_VERBOSE("Set frame pending");
            }
        }

        return true;
    }
}
