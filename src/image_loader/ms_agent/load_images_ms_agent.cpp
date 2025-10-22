#include "graphics/drawing.h"
#include "graphics/animation_context.h"
#include "graphics/animation.h"
#include "utils/memory.h"
#include "image_loader/load_images.h"
#include "embedded_assets/ms_agent/ms_agent_sprite.h"
#include "embedded_assets/ms_agent/ms_agent.hpp"
#include <cassert>


namespace bongocat::animation {
    [[nodiscard]] static created_result_t<ms_agent_sprite_sheet_t> load_ms_agent_sprite_sheet_from_memory(const uint8_t* sprite_data, size_t sprite_data_size,
                                                                                                          int frame_columns, int frame_rows,
                                                                                                          int padding_x, int padding_y) {
        auto [sprite_sheet, sprite_sheet_error] = load_image(sprite_data, sprite_data_size, RGBA_CHANNELS); // Force RGBA
        if (sprite_sheet_error != bongocat_error_t::BONGOCAT_SUCCESS) [[unlikely]] {
            BONGOCAT_LOG_ERROR("Failed to load sprite sheet.");
            return sprite_sheet_error;
        }

        assert(frame_columns != 0 && frame_rows != 0 && sprite_sheet.width % frame_columns == 0 && sprite_sheet.height % frame_rows == 0);
        if (frame_columns == 0 || frame_rows == 0 || sprite_sheet.width % frame_columns != 0 || sprite_sheet.height % frame_rows != 0) {
            BONGOCAT_LOG_ERROR("Sprite sheet dimensions not divisible by frame grid; frame_columns=%d, frame_rows=%d vs %dx%d sprite size", frame_columns, frame_rows, sprite_sheet.width, sprite_sheet.height);
            return bongocat_error_t::BONGOCAT_ERROR_INVALID_PARAM;
        }

        const auto frame_width = sprite_sheet.width / frame_columns;
        const auto frame_height = sprite_sheet.height / frame_rows;

        /*
        assert(MAX_NUM_FRAMES <= INT_MAX);
        if (total_frames > (int)MAX_NUM_FRAMES) {
            BONGOCAT_LOG_ERROR("Sprite Sheet does not fit in out_frames: %d, total_frames: %d", MAX_NUM_FRAMES, total_frames);
            return BONGOCAT_ERROR_INVALID_PARAM;
        }
        */

        const auto dest_frame_width = frame_width + padding_x*2;
        const auto dest_frame_height = frame_height + padding_y*2;
        const auto dest_pixels_width = dest_frame_width * frame_columns;
        const auto dest_pixels_height = dest_frame_height * frame_rows;
        assert(dest_pixels_width >= 0);
        assert(dest_pixels_height >= 0);
        assert(sprite_sheet.channels >= 0);
        const size_t dest_pixels_size = static_cast<size_t>(dest_pixels_width) * static_cast<size_t>(dest_pixels_height) * static_cast<size_t>(sprite_sheet.channels);
        auto dest_pixels = make_allocated_array<uint8_t>(dest_pixels_size);
        if (!dest_pixels) {
            BONGOCAT_LOG_ERROR("Failed to allocate memory for dest_pixels (%zu bytes)\n", dest_pixels_size);
            return bongocat_error_t::BONGOCAT_ERROR_MEMORY;
        }
        //memset(dest_pixels.data, 0, dest_pixels_size);

        const auto src_frame_width = frame_width;
        const auto src_frame_height = frame_height;
        const auto src_pixels_width = sprite_sheet.width;
        const auto src_pixels_height = sprite_sheet.height;
        assert(src_pixels_width >= 0);
        assert(src_pixels_height >= 0);
        assert(sprite_sheet.channels >= 0);
        const size_t src_pixels_size = static_cast<size_t>(src_pixels_width) * static_cast<size_t>(src_pixels_height) * static_cast<size_t>(sprite_sheet.channels);
        size_t frame_index = 0;
        for (int row = 0; row < frame_rows; ++row) {
            for (int col = 0; col < frame_columns; ++col) {
                const auto src_x = col * src_frame_width;
                const auto src_y = row * src_frame_height;
                const auto dst_x = col * dest_frame_width + padding_x;
                const auto dst_y = row * dest_frame_height + padding_y;
                [[maybe_unused]] const auto src_idx = (src_y * src_pixels_width + src_x) * sprite_sheet.channels;
                [[maybe_unused]] const auto dst_idx = (dst_y * dest_pixels_width + dst_x) * sprite_sheet.channels;
                assert(src_idx >= 0);
                assert(dst_idx >= 0);

                bool set_frames = false;
                for (int fy = 0; fy < src_frame_height; fy++) {
                    for (int fx = 0; fx < src_frame_width; fx++) {
                        const auto src_px_idx = ((src_y + fy) * src_pixels_width + (src_x + fx)) * sprite_sheet.channels;
                        const auto dst_px_idx = ((dst_y + fy) * dest_pixels_width + (dst_x + fx)) * sprite_sheet.channels;

                        if (src_px_idx >= 0 && dst_px_idx >= 0 &&
                            static_cast<size_t>(src_px_idx) < src_pixels_size &&
                            static_cast<size_t>(dst_px_idx) < dest_pixels_size) {
                            drawing_copy_pixel(dest_pixels.data, sprite_sheet.channels, dst_px_idx,
                                               sprite_sheet.pixels, sprite_sheet.channels, src_px_idx,
                                               blit_image_color_option_flags_t::Normal,
                                               blit_image_color_order_t::RGBA,
                                               blit_image_color_order_t::RGBA);
                            if (!set_frames && frame_index < MAX_NUM_FRAMES) {
                                set_frames = true;
                            }
                        }
                    }
                }
                frame_index++;
            }
        }

        ms_agent_sprite_sheet_t ret;
        ret.image.sprite_sheet_width = sprite_sheet.width;
        ret.image.sprite_sheet_height = sprite_sheet.height;
        ret.image.channels = sprite_sheet.channels;
        // move pixels ownership into out_frames
        ret.image.pixels = move(dest_pixels);
        dest_pixels = nullptr;
        ret.frame_width = dest_frame_width;
        ret.frame_height = dest_frame_height;

        return ret;
    }

    created_result_t<ms_agent_sprite_sheet_t> load_ms_agent_sprite_sheet(const config::config_t& config, const assets::embedded_image_t& sprite_sheet_image, int sprite_sheet_cols, int sprite_sheet_rows) {
        if (sprite_sheet_cols < 0 || sprite_sheet_rows < 0) {
            return bongocat_error_t::BONGOCAT_ERROR_INVALID_PARAM;
        }

        assert(sprite_sheet_image.size <= INT_MAX);
        auto result = load_ms_agent_sprite_sheet_from_memory(sprite_sheet_image.data, sprite_sheet_image.size,
                                                       sprite_sheet_cols, sprite_sheet_rows,
                                                       config.padding_x, config.padding_y);
        if (result.error != bongocat_error_t::BONGOCAT_SUCCESS) [[unlikely]] {
            BONGOCAT_LOG_ERROR("Sprite Sheet load failed: %s", sprite_sheet_image.name);
            return result.error;
        }

        // assume every frame is the same size, pick first frame
        BONGOCAT_LOG_DEBUG("Loaded %dx%d sprite sheet", result.result.image.sprite_sheet_width, result.result.image.sprite_sheet_height);

        return result;
    }

    created_result_t<ms_agent_sprite_sheet_t> load_ms_agent_anim(const animation_context_t& ctx, [[maybe_unused]] int anim_index, const assets::embedded_image_t& sprite_sheet_image, int sprite_sheet_cols, int sprite_sheet_rows, const assets::ms_agent_animation_indices_t& animation_data) {
        using namespace assets;
        BONGOCAT_CHECK_NULL(ctx._local_copy_config.ptr, bongocat_error_t::BONGOCAT_ERROR_INVALID_PARAM);

        BONGOCAT_LOG_VERBOSE("Load MS agent Animation(index=%d) ...", anim_index);
        auto result = load_ms_agent_sprite_sheet(*ctx._local_copy_config, sprite_sheet_image, sprite_sheet_cols, sprite_sheet_rows);
        if (result.error != bongocat_error_t::BONGOCAT_SUCCESS) [[unlikely]] {
            return result.error;
        }


        // setup animation frames data
        if (result.result.frame_height > 0 && sprite_sheet_rows > 0) {
            [[maybe_unused]] const auto rows = result.result.image.sprite_sheet_height / result.result.frame_height;
            assert(rows == sprite_sheet_rows);

            assert(sprite_sheet_rows > 0);
            if (static_cast<size_t>(sprite_sheet_rows - 1) >= MS_AGENT_SPRITE_SHEET_ROW_IDLE) {
                result.result.idle = { .valid = true, .start_col = animation_data.start_index_frame_idle, .end_col = animation_data.end_index_frame_idle, .row = MS_AGENT_SPRITE_SHEET_ROW_IDLE };
            }
            if (static_cast<size_t>(sprite_sheet_rows - 1) >= MS_AGENT_SPRITE_SHEET_ROW_BORING) {
                result.result.boring = { .valid = true, .start_col = animation_data.start_index_frame_boring, .end_col = animation_data.end_index_frame_boring, .row = MS_AGENT_SPRITE_SHEET_ROW_BORING };
            }
            if (static_cast<size_t>(sprite_sheet_rows - 1) >= MS_AGENT_SPRITE_SHEET_ROW_START_WRITING) {
                result.result.start_writing = { .valid = true, .start_col = animation_data.start_index_frame_start_writing, .end_col = animation_data.end_index_frame_start_writing, .row = MS_AGENT_SPRITE_SHEET_ROW_START_WRITING };
            }
            if (static_cast<size_t>(sprite_sheet_rows - 1) >= MS_AGENT_SPRITE_SHEET_ROW_WRITING) {
                result.result.writing = { .valid = true, .start_col = animation_data.start_index_frame_writing, .end_col = animation_data.end_index_frame_writing, .row = MS_AGENT_SPRITE_SHEET_ROW_WRITING };
            }
            if (static_cast<size_t>(sprite_sheet_rows - 1) >= MS_AGENT_SPRITE_SHEET_ROW_END_WRITING) {
                result.result.end_writing = { .valid = true, .start_col = animation_data.start_index_frame_end_writing, .end_col = animation_data.end_index_frame_end_writing, .row = MS_AGENT_SPRITE_SHEET_ROW_END_WRITING };
            }
            if (static_cast<size_t>(sprite_sheet_rows - 1) >= MS_AGENT_SPRITE_SHEET_ROW_SLEEP) {
                result.result.sleep = { .valid = true, .start_col = animation_data.start_index_frame_sleep, .end_col = animation_data.end_index_frame_sleep, .row = MS_AGENT_SPRITE_SHEET_ROW_SLEEP };
            }
            if (static_cast<size_t>(sprite_sheet_rows - 1) >= MS_AGENT_SPRITE_SHEET_ROW_WAKE_UP) {
                result.result.wake_up = { .valid = true, .start_col = animation_data.start_index_frame_wake_up, .end_col = animation_data.end_index_frame_wake_up, .row = MS_AGENT_SPRITE_SHEET_ROW_WAKE_UP };
            }
            if (static_cast<size_t>(sprite_sheet_rows - 1) >= MS_AGENT_SPRITE_SHEET_ROW_START_WORKING) {
                result.result.start_working = { .valid = true, .start_col = animation_data.start_index_frame_start_working, .end_col = animation_data.end_index_frame_start_working, .row = MS_AGENT_SPRITE_SHEET_ROW_START_WORKING };
            }
            if (static_cast<size_t>(sprite_sheet_rows - 1) >= MS_AGENT_SPRITE_SHEET_ROW_WORKING) {
                result.result.working = { .valid = true, .start_col = animation_data.start_index_frame_working, .end_col = animation_data.end_index_frame_working, .row = MS_AGENT_SPRITE_SHEET_ROW_WORKING };
            }
            if (static_cast<size_t>(sprite_sheet_rows - 1) >= MS_AGENT_SPRITE_SHEET_ROW_END_WORKING) {
                result.result.end_working = { .valid = true, .start_col = animation_data.start_index_frame_end_working, .end_col = animation_data.end_index_frame_end_working, .row = MS_AGENT_SPRITE_SHEET_ROW_END_WORKING };
            }
            if (static_cast<size_t>(sprite_sheet_rows - 1) >= MS_AGENT_SPRITE_SHEET_ROW_START_MOVING) {
                result.result.start_moving = { .valid = true, .start_col = animation_data.start_index_frame_start_moving, .end_col = animation_data.end_index_frame_start_moving, .row = MS_AGENT_SPRITE_SHEET_ROW_START_MOVING };
            }
            if (static_cast<size_t>(sprite_sheet_rows - 1) >= MS_AGENT_SPRITE_SHEET_ROW_MOVING) {
                result.result.moving = { .valid = true, .start_col = animation_data.start_index_frame_moving, .end_col = animation_data.end_index_frame_moving, .row = MS_AGENT_SPRITE_SHEET_ROW_MOVING };
            }
            if (static_cast<size_t>(sprite_sheet_rows - 1) >= MS_AGENT_SPRITE_SHEET_ROW_END_MOVING) {
                result.result.end_moving = { .valid = true, .start_col = animation_data.start_index_frame_end_moving, .end_col = animation_data.end_index_frame_end_moving, .row = MS_AGENT_SPRITE_SHEET_ROW_END_MOVING };
            }
            //if (static_cast<size_t>(sprite_sheet_rows - 1) >= MS_AGENT_SPRITE_SHEET_ROW_HAPPY) {
            //    result.result.happy = { .valid = true, .start_col = animation_data.start_index_frame_happy), .end_col = animation_data.end_index_happy_moving), .row = MS_AGENT_SPRITE_SHEET_ROW_HAPPY };
            //}
        }

        return bongocat::move(result.result);
    }

    created_result_t<ms_agent_sprite_sheet_t> init_ms_agent_anim(animation_context_t& ctx, int anim_index, const assets::embedded_image_t& sprite_sheet_image, int sprite_sheet_cols, int sprite_sheet_rows, const assets::ms_agent_animation_indices_t& animation_data) {
        using namespace assets;
        BONGOCAT_CHECK_NULL(ctx.shm.ptr, bongocat_error_t::BONGOCAT_ERROR_INVALID_PARAM);
        BONGOCAT_CHECK_NULL(ctx._local_copy_config.ptr, bongocat_error_t::BONGOCAT_ERROR_INVALID_PARAM);

        assert(anim_index >= 0 && static_cast<size_t>(anim_index) < MS_AGENTS_ANIM_COUNT);
        BONGOCAT_LOG_VERBOSE("Load MS agent Animation (%d/%d): %s ...", anim_index, MS_AGENTS_ANIM_COUNT, sprite_sheet_image.name);
        auto result = load_ms_agent_anim(ctx, anim_index, sprite_sheet_image, sprite_sheet_cols, sprite_sheet_rows, animation_data);
        if (result.error != bongocat_error_t::BONGOCAT_SUCCESS) {
            BONGOCAT_LOG_ERROR("Load MS agent Animation failed: %s, index: %d", sprite_sheet_image.name, anim_index);
            return bongocat_error_t::BONGOCAT_ERROR_ANIMATION;
        }
        assert(result.error == bongocat_error_t::BONGOCAT_SUCCESS); ///< this SHOULD always work if it's an valid EMBEDDED image

        assert(anim_index >= 0);
        ctx.shm->ms_anims[static_cast<size_t>(anim_index)].ms_agent = bongocat::move(result.result);

        return bongocat_error_t::BONGOCAT_SUCCESS;
    }

    created_result_t<ms_agent_sprite_sheet_t> load_ms_agent_sprite_sheet(const animation_context_t& ctx, int index) {
        using namespace assets;
        using namespace animation;
        switch (index) {
            case CLIPPY_ANIM_INDEX: return load_ms_agent_anim(ctx, CLIPPY_ANIM_INDEX, get_ms_agent_sprite_sheet(CLIPPY_ANIM_INDEX), CLIPPY_SPRITE_SHEET_COLS, CLIPPY_SPRITE_SHEET_ROWS, get_ms_agent_animation_indices(CLIPPY_ANIM_INDEX));
#ifdef FEATURE_MORE_MS_AGENT_EMBEDDED_ASSETS
            case LINKS_ANIM_INDEX: return load_ms_agent_anim(ctx, LINKS_ANIM_INDEX, get_ms_agent_sprite_sheet(LINKS_ANIM_INDEX), LINKS_SPRITE_SHEET_COLS, LINKS_SPRITE_SHEET_ROWS, get_ms_agent_animation_indices(LINKS_ANIM_INDEX));
            case ROVER_ANIM_INDEX: return load_ms_agent_anim(ctx, ROVER_ANIM_INDEX, get_ms_agent_sprite_sheet(ROVER_ANIM_INDEX), ROVER_SPRITE_SHEET_COLS, ROVER_SPRITE_SHEET_ROWS, get_ms_agent_animation_indices(ROVER_ANIM_INDEX));
            case MERLIN_ANIM_INDEX: return load_ms_agent_anim(ctx, MERLIN_ANIM_INDEX, get_ms_agent_sprite_sheet(MERLIN_ANIM_INDEX), MERLIN_SPRITE_SHEET_COLS, MERLIN_SPRITE_SHEET_ROWS, get_ms_agent_animation_indices(MERLIN_ANIM_INDEX));
#endif
            default: return bongocat_error_t::BONGOCAT_ERROR_INVALID_PARAM;
        }
        return bongocat_error_t::BONGOCAT_ERROR_INVALID_PARAM;
    }
}
