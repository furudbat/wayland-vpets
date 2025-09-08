#include "graphics/drawing.h"
#include "graphics/animation_context.h"
#include "graphics/animation.h"
#include "utils/memory.h"
#include "image_loader/load_images.h"
#include "embedded_assets/ms_agent/ms_agent.h"
#include "embedded_assets/ms_agent/ms_agent.hpp"
#include <cassert>


namespace bongocat::animation {
    static created_result_t<ms_agent_sprite_sheet_t> load_ms_agent_sprite_sheet_from_memory(const uint8_t* sprite_data, size_t sprite_data_size,
                                                                                          int frame_columns, int frame_rows,
                                                                                          int padding_x, int padding_y) {
        assert(sprite_data_size <= INT_MAX);
        /// @TODO: stbi_load_from_memory C++ RAII wrapper
        Image sprite_sheet (sprite_data, static_cast<int>(sprite_data_size), STBI_rgb_alpha); // Force RGBA
        if (!sprite_sheet.pixels) {
            BONGOCAT_LOG_ERROR("Failed to load sprite sheet.");
            return bongocat_error_t::BONGOCAT_ERROR_FILE_IO;
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
            stbi_image_free(sprite_sheet_pixels);
            sprite_sheet_pixels = NULL;
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
        if (result.error != bongocat_error_t::BONGOCAT_SUCCESS) {
            BONGOCAT_LOG_ERROR("Sprite Sheet load failed: %s", sprite_sheet_image.name);
            return result.error;
        }

        // assume every frame is the same size, pick first frame
        BONGOCAT_LOG_DEBUG("Loaded %dx%d sprite sheet with %d frames", result.result.image.sprite_sheet_width, result.result.image.sprite_sheet_height);

        return result;
    }

    created_result_t<ms_agent_sprite_sheet_t> load_ms_agent_anim(const animation_context_t& ctx, [[maybe_unused]] int anim_index, const assets::embedded_image_t& sprite_sheet_image, int sprite_sheet_cols, int sprite_sheet_rows) {
        BONGOCAT_CHECK_NULL(ctx._local_copy_config.ptr, bongocat_error_t::BONGOCAT_ERROR_INVALID_PARAM);

        BONGOCAT_LOG_VERBOSE("Load bongocat Animation(index=%d) ...", anim_index);
        auto result = load_ms_agent_sprite_sheet(*ctx._local_copy_config, sprite_sheet_image, sprite_sheet_cols, sprite_sheet_rows);
        if (result.error != bongocat_error_t::BONGOCAT_SUCCESS) {
            return result.error;
        }

        ms_agent_sprite_sheet_t ret;
        ret.image = bongocat::move(result.result.image);
        ret.frame_width = bongocat::move(result.result.frame_width);
        ret.frame_height = bongocat::move(result.result.frame_height);

        return ret;
    }

    created_result_t<ms_agent_sprite_sheet_t> init_ms_agent_anim(animation_context_t& ctx, int anim_index, const assets::embedded_image_t& sprite_sheet_image, int sprite_sheet_cols, int sprite_sheet_rows) {
        using namespace assets;
        BONGOCAT_CHECK_NULL(ctx.shm.ptr, bongocat_error_t::BONGOCAT_ERROR_INVALID_PARAM);
        BONGOCAT_CHECK_NULL(ctx._local_copy_config.ptr, bongocat_error_t::BONGOCAT_ERROR_INVALID_PARAM);

        assert(anim_index >= 0 && static_cast<size_t>(anim_index) < MS_AGENTS_ANIM_COUNT);
        BONGOCAT_LOG_VERBOSE("Load MS agent Animation (%d/%d): %s ...", anim_index, MS_AGENTS_ANIM_COUNT, sprite_sheet_image.name);
        auto result = load_ms_agent_anim(ctx, anim_index, sprite_sheet_image, sprite_sheet_cols, sprite_sheet_rows);
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
            case CLIPPY_ANIM_INDEX: return load_ms_agent_anim(ctx, CLIPPY_ANIM_INDEX, get_ms_agent_sprite_sheet(CLIPPY_ANIM_INDEX), CLIPPY_SPRITE_SHEET_COLS, CLIPPY_SPRITE_SHEET_ROWS);
#ifdef FEATURE_MORE_MS_AGENT_EMBEDDED_ASSETS
            case LINKS_ANIM_INDEX: return load_ms_agent_anim(ctx, LINKS_ANIM_INDEX, get_ms_agent_sprite_sheet(LINKS_ANIM_INDEX), LINKS_SPRITE_SHEET_COLS, LINKS_SPRITE_SHEET_ROWS);
#endif
            default: return bongocat_error_t::BONGOCAT_ERROR_INVALID_PARAM;
        }
        return bongocat_error_t::BONGOCAT_ERROR_INVALID_PARAM;
    }
}
