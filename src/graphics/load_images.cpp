#include "graphics/drawing.h"
#include "graphics/embedded_assets.h"
#include "graphics/animation_context.h"
#include "graphics/animation.h"
#include "utils/memory.h"
#include "stb_image.hpp"
#include "load_images.h"
#include <cassert>

namespace bongocat::animation {
    // =============================================================================
    // IMAGE LOADING MODULE
    // =============================================================================

#if defined(FEATURE_BONGOCAT_EMBEDDED_ASSETS) || defined(FEATURE_ENABLE_DM_EMBEDDED_ASSETS)

    bongocat_error_t load_sprite_sheet_from_memory(generic_sprite_sheet_animation_t& out_frames,
                                                  const uint8_t* sprite_data, size_t sprite_data_size,
                                                  int frame_columns, int frame_rows,
                                                  int padding_x, int padding_y) {
        int sheet_width = 0;
        int sheet_height = 0;
        constexpr int channels = STBI_rgb_alpha;
        assert(sprite_data_size <= INT_MAX);
        /// @TODO: stbi_load_from_memory C++ RAII wrapper
        uint8_t* sprite_sheet_pixels = stbi_load_from_memory(sprite_data, static_cast<int>(sprite_data_size), &sheet_width, &sheet_height, nullptr, channels); // Force RGBA
        if (!sprite_sheet_pixels) {
            BONGOCAT_LOG_ERROR("Failed to load sprite sheet.");
            return bongocat_error_t::BONGOCAT_ERROR_FILE_IO;
        }

        if (frame_columns == 0 || frame_rows == 0 || sheet_width % frame_columns != 0 || sheet_height % frame_rows != 0) {
            BONGOCAT_LOG_ERROR("Sprite sheet dimensions not divisible by frame grid.");
            stbi_image_free(sprite_sheet_pixels);
            sprite_sheet_pixels = nullptr;
            return bongocat_error_t::BONGOCAT_ERROR_INVALID_PARAM;
        }

        const auto frame_width = sheet_width / frame_columns;
        const auto frame_height = sheet_height / frame_rows;
        const auto total_frames = frame_columns * frame_rows;

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
        assert(channels >= 0);
        const size_t dest_pixels_size = static_cast<size_t>(dest_pixels_width) * static_cast<size_t>(dest_pixels_height) * static_cast<size_t>(channels);
        auto dest_pixels = AllocatedArray<uint8_t>(dest_pixels_size);
        if (!dest_pixels) {
            BONGOCAT_LOG_ERROR("Failed to allocate memory for dest_pixels (%zu bytes)\n", dest_pixels_size);
            stbi_image_free(sprite_sheet_pixels);
            sprite_sheet_pixels = nullptr;
            return bongocat_error_t::BONGOCAT_ERROR_MEMORY;
        }
        //memset(dest_pixels.data, 0, dest_pixels_size);

        const auto src_frame_width = frame_width;
        const auto src_frame_height = frame_height;
        const auto src_pixels_width = sheet_width;
        const auto src_pixels_height = sheet_height;
        assert(src_pixels_width >= 0);
        assert(src_pixels_height >= 0);
        assert(channels >= 0);
        const size_t src_pixels_size = static_cast<size_t>(src_pixels_width) * static_cast<size_t>(src_pixels_height) * static_cast<size_t>(channels);
        size_t frame_index = 0;
        for (int row = 0; row < frame_rows; ++row) {
            for (int col = 0; col < frame_columns; ++col) {
                const auto src_x = col * src_frame_width;
                const auto src_y = row * src_frame_height;
                const auto dst_x = col * dest_frame_width + padding_x;
                const auto dst_y = row * dest_frame_height + padding_y;
                [[maybe_unused]] const auto src_idx = (src_y * src_pixels_width + src_x) * channels;
                [[maybe_unused]] const auto dst_idx = (dst_y * dest_pixels_width + dst_x) * channels;
                assert(src_idx >= 0);
                assert(dst_idx >= 0);

                bool set_frames = false;
                for (int fy = 0; fy < src_frame_height; fy++) {
                    for (int fx = 0; fx < src_frame_width; fx++) {
                        const auto src_px_idx = ((src_y + fy) * src_pixels_width + (src_x + fx)) * channels;
                        const auto dst_px_idx = ((dst_y + fy) * dest_pixels_width + (dst_x + fx)) * channels;

                        if (src_px_idx >= 0 && dst_px_idx >= 0 &&
                            static_cast<size_t>(src_px_idx) < src_pixels_size &&
                            static_cast<size_t>(dst_px_idx) < dest_pixels_size) {
                            drawing_copy_pixel(dest_pixels.data, channels, dst_px_idx,
                                               sprite_sheet_pixels, channels, src_px_idx,
                                               blit_image_color_option_flags_t::Normal,
                                               blit_image_color_order_t::RGBA,
                                               blit_image_color_order_t::RGBA);
                            if (!set_frames && frame_index < MAX_NUM_FRAMES) {
                                set_frames = true;
                            }
                        }
                    }
                }
                if (frame_index < MAX_NUM_FRAMES) {
                    if (set_frames) {
                        out_frames.frames[frame_index] = { .valid = true, .col = col, .row = row };
                    } else {
                        out_frames.frames[frame_index] = { .valid = false, .col = 0, .row = 0, };
                    }
                }

                frame_index++;
            }
        }

        stbi_image_free(sprite_sheet_pixels);
        sprite_sheet_pixels = nullptr;

        out_frames.sprite_sheet_width = sheet_width;
        out_frames.sprite_sheet_height = sheet_height;
        out_frames.channels = channels;
        // move pixels ownership into out_frames
        out_frames.pixels = move(dest_pixels);
        dest_pixels = nullptr;
        out_frames.frame_width = dest_frame_width;
        out_frames.frame_height = dest_frame_height;
        out_frames.total_frames = total_frames;

        return bongocat_error_t::BONGOCAT_SUCCESS;
    }

    int anim_load_embedded_images_into_sprite_sheet(generic_sprite_sheet_animation_t& anim, get_sprite_callback_t get_sprite, size_t embedded_images_count) {
        int total_frames = 0;
        int max_frame_width = 0;
        int max_frame_height = 0;
        int max_channels = 0;
        auto loaded_images = AllocatedArray<loaded_sprite_sheet_frame_t>(embedded_images_count);
        for (size_t i = 0;i < embedded_images_count && i < loaded_images.count; i++) {
            const assets::embedded_image_t img = get_sprite(i);

            BONGOCAT_LOG_DEBUG("Loading embedded image: %s", img.name);
            loaded_images[i].channels = STBI_rgb_alpha;
            assert(img.size <= INT_MAX);
            loaded_images[i].pixels = stbi_load_from_memory(img.data, static_cast<int>(img.size),
                                                      &loaded_images[i].frame_width,
                                                      &loaded_images[i].frame_height,
                                                      nullptr, loaded_images[i].channels);
            if (!loaded_images[i].pixels) {
                BONGOCAT_LOG_ERROR("Failed to load embedded image: %s", img.name);
                continue;
            }
            assert(loaded_images[i].frame_width >= 0);
            assert(loaded_images[i].frame_height >= 0);
            assert(loaded_images[i].channels >= 0);
            loaded_images[i].pixels_size = static_cast<size_t>(loaded_images[i].frame_width) * static_cast<size_t>(loaded_images[i].frame_height) * static_cast<size_t>(loaded_images[i].channels);

            // update image properties
            max_frame_width = loaded_images[i].frame_width > max_frame_width ? loaded_images[i].frame_width : max_frame_width;
            max_frame_height = loaded_images[i].frame_height > max_frame_height ? loaded_images[i].frame_height : max_frame_height;
            max_channels = loaded_images[i].channels > max_channels ? loaded_images[i].channels : max_channels;

            BONGOCAT_LOG_DEBUG("Loaded %dx%d embedded image", loaded_images[i].frame_width, loaded_images[i].frame_height);
            total_frames++;
        }

        anim.frame_width = max_frame_width;
        anim.frame_height = max_frame_height;
        anim.total_frames = total_frames;
        anim.sprite_sheet_width = max_frame_width * total_frames;
        anim.sprite_sheet_height = max_frame_height;
        anim.channels = max_channels;
        // create sprite sheet
        assert(anim.sprite_sheet_width >= 0);
        assert(anim.sprite_sheet_height >= 0);
        assert(anim.channels >= 0);
        anim.pixels = make_allocated_array<uint8_t>(static_cast<size_t>(anim.sprite_sheet_width) * static_cast<size_t>(anim.sprite_sheet_height) * static_cast<size_t>(anim.channels));
        if (!anim.pixels) {
            anim.frame_width = 0;
            anim.frame_height = 0;
            anim.total_frames = 0;
            anim.sprite_sheet_width = 0;
            anim.sprite_sheet_height = 0;
            anim.channels = 0;

            for (size_t i = 0; i < loaded_images.count; i++) {
                if (loaded_images[i].pixels) stbi_image_free(loaded_images[i].pixels);
                loaded_images[i].pixels = nullptr;
            }
            return -1;
        }
        // reset frames
        //memset(anim->pixels.data, 0, anim->pixels.count * sizeof(uint8_t));
        for (size_t i = 0;i < MAX_NUM_FRAMES;i++) {
            anim.frames[i] = {};
        }
        // append images into one sprite sheet
        assert(max_frame_width >= 0);
        assert(max_channels >= 0);
        assert(anim.sprite_sheet_width >= 0);
        for (size_t frame = 0; frame < loaded_images.count; frame++) {
            const loaded_sprite_sheet_frame_t& src = loaded_images[frame];
            assert(src.channels >= 0);
            assert(src.frame_width >= 0);
            assert(src.frame_height >= 0);
            if (src.pixels && src.frame_height > 0) {
                // copy pixel data of sub-region
                assert(src.frame_height >= 0);
                for (size_t y = 0; y < static_cast<size_t>(src.frame_height); y++) {
                    unsigned char* dest_row = anim.pixels.data +
                        ((y) * static_cast<size_t>(anim.sprite_sheet_width) + (frame * static_cast<size_t>(max_frame_width))) * static_cast<size_t>(max_channels);
                    const unsigned char* src_row = src.pixels + (y * static_cast<size_t>(src.frame_width) * static_cast<size_t>(src.channels));
                    memcpy(dest_row, src_row, static_cast<size_t>(src.frame_width) * static_cast<size_t>(max_channels));
                }

                // update sub-region
                if (frame < MAX_NUM_FRAMES) {
                    anim.frames[frame] = { .valid = true, .col = static_cast<int>(frame), .row = 0 };
                }
            } else {
                if (frame < MAX_NUM_FRAMES) {
                    anim.frames[frame] = { .valid = false, .col = static_cast<int>(frame), .row = 0 };
                }
            }
        }


        for (size_t i = 0; i < loaded_images.count; i++) {
            if (loaded_images[i].pixels) stbi_image_free(loaded_images[i].pixels);
            loaded_images[i].pixels = nullptr;
        }
        return total_frames;
    }
#endif

#ifdef FEATURE_MS_AGENT_EMBEDDED_ASSETS
    int anim_load_sprite_sheet(const config::config_t& config, generic_sprite_sheet_animation_t& anim, const assets::embedded_image_t& sprite_sheet_image, int sprite_sheet_cols, int sprite_sheet_rows) {
        if (sprite_sheet_cols < 0 || sprite_sheet_rows < 0) {
            return -1;
        }

        assert(sprite_sheet_image.size <= INT_MAX);

        const auto result = load_sprite_sheet_from_memory(anim,
                                      sprite_sheet_image.data, sprite_sheet_image.size,
                                      sprite_sheet_cols, sprite_sheet_rows,
                                      config.padding_x, config.padding_y);
        if (result != bongocat_error_t::BONGOCAT_SUCCESS) {
            BONGOCAT_LOG_ERROR("Sprite Sheet load failed: %s", sprite_sheet_image.name);
            return -1;
        }
        if (anim.total_frames <= 0) {
            BONGOCAT_LOG_ERROR("Sprite Sheet is empty: %s", sprite_sheet_image.name);
            return 0;
        }

        // assume every frame is the same size, pick first frame
        BONGOCAT_LOG_DEBUG("Loaded %dx%d sprite sheet with %d frames", anim.sprite_sheet_width, anim.sprite_sheet_height, anim.total_frames);

        return anim.total_frames;
    }
#endif

    bongocat_error_t load_sprite_sheet_from_memory(ms_pet_sprite_sheet_t& out_frames,
                                              const uint8_t* sprite_data, size_t sprite_data_size,
                                              int frame_columns, int frame_rows,
                                              int padding_x, int padding_y) {
        int sheet_width = 0;
        int sheet_height = 0;
        constexpr int channels = STBI_rgb_alpha;
        assert(sprite_data_size <= INT_MAX);
        /// @TODO: stbi_load_from_memory C++ RAII wrapper
        uint8_t* sprite_sheet_pixels = stbi_load_from_memory(sprite_data, static_cast<int>(sprite_data_size), &sheet_width, &sheet_height, nullptr, channels); // Force RGBA
        if (!sprite_sheet_pixels) {
            BONGOCAT_LOG_ERROR("Failed to load sprite sheet.");
            return bongocat_error_t::BONGOCAT_ERROR_FILE_IO;
        }

        if (frame_columns == 0 || frame_rows == 0 ||
            sheet_width % frame_columns != 0 || sheet_height % frame_rows != 0) {
            BONGOCAT_LOG_ERROR("Sprite sheet dimensions not divisible by frame grid.");
            stbi_image_free(sprite_sheet_pixels);
            sprite_sheet_pixels = nullptr;
            return bongocat_error_t::BONGOCAT_ERROR_INVALID_PARAM;
            }

        const auto frame_width = sheet_width / frame_columns;
        const auto frame_height = sheet_height / frame_rows;

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
        assert(channels >= 0);
        const size_t dest_pixels_size = static_cast<size_t>(dest_pixels_width) * static_cast<size_t>(dest_pixels_height) * static_cast<size_t>(channels);
        auto dest_pixels = AllocatedArray<uint8_t>(dest_pixels_size);
        if (!dest_pixels) {
            BONGOCAT_LOG_ERROR("Failed to allocate memory for dest_pixels (%zu bytes)\n", dest_pixels_size);
            stbi_image_free(sprite_sheet_pixels);
            sprite_sheet_pixels = nullptr;
            return bongocat_error_t::BONGOCAT_ERROR_MEMORY;
        }
        //memset(dest_pixels.data, 0, dest_pixels_size);

        const auto src_frame_width = frame_width;
        const auto src_frame_height = frame_height;
        const auto src_pixels_width = sheet_width;
        const auto src_pixels_height = sheet_height;
        assert(src_pixels_width >= 0);
        assert(src_pixels_height >= 0);
        assert(channels >= 0);
        const size_t src_pixels_size = static_cast<size_t>(src_pixels_width) * static_cast<size_t>(src_pixels_height) * static_cast<size_t>(channels);
        size_t frame_index = 0;
        for (int row = 0; row < frame_rows; ++row) {
            for (int col = 0; col < frame_columns; ++col) {
                const auto src_x = col * src_frame_width;
                const auto src_y = row * src_frame_height;
                const auto dst_x = col * dest_frame_width + padding_x;
                const auto dst_y = row * dest_frame_height + padding_y;
                [[maybe_unused]] const auto src_idx = (src_y * src_pixels_width + src_x) * channels;
                [[maybe_unused]] const auto dst_idx = (dst_y * dest_pixels_width + dst_x) * channels;
                assert(src_idx >= 0);
                assert(dst_idx >= 0);

                bool set_frames = false;
                for (int fy = 0; fy < src_frame_height; fy++) {
                    for (int fx = 0; fx < src_frame_width; fx++) {
                        const auto src_px_idx = ((src_y + fy) * src_pixels_width + (src_x + fx)) * channels;
                        const auto dst_px_idx = ((dst_y + fy) * dest_pixels_width + (dst_x + fx)) * channels;

                        if (src_px_idx >= 0 && dst_px_idx >= 0 &&
                            static_cast<size_t>(src_px_idx) < src_pixels_size &&
                            static_cast<size_t>(dst_px_idx) < dest_pixels_size) {
                            drawing_copy_pixel(dest_pixels.data, channels, dst_px_idx,
                                               sprite_sheet_pixels, channels, src_px_idx,
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

        stbi_image_free(sprite_sheet_pixels);
        sprite_sheet_pixels = nullptr;

        out_frames.sprite_sheet_width = sheet_width;
        out_frames.sprite_sheet_height = sheet_height;
        out_frames.channels = channels;
        // move pixels ownership into out_frames
        out_frames.pixels = move(dest_pixels);
        dest_pixels = nullptr;
        out_frames.frame_width = dest_frame_width;
        out_frames.frame_height = dest_frame_height;

        return bongocat_error_t::BONGOCAT_SUCCESS;
    }

#ifdef FEATURE_MS_AGENT_EMBEDDED_ASSETS
    bongocat_error_t anim_load_sprite_sheet(const config::config_t& config, ms_pet_sprite_sheet_t& anim, const assets::embedded_image_t& sprite_sheet_image, int sprite_sheet_cols, int sprite_sheet_rows) {
        if (sprite_sheet_cols < 0 || sprite_sheet_rows < 0) {
            return bongocat_error_t::BONGOCAT_ERROR_INVALID_PARAM;
        }

        assert(sprite_sheet_image.size <= INT_MAX);
        const auto result = load_sprite_sheet_from_memory(anim,
                                      sprite_sheet_image.data, sprite_sheet_image.size,
                                      sprite_sheet_cols, sprite_sheet_rows,
                                      config.padding_x, config.padding_y);
        if (result != bongocat_error_t::BONGOCAT_SUCCESS) {
            BONGOCAT_LOG_ERROR("Sprite Sheet load failed: %s", sprite_sheet_image.name);
            return result;
        }

        // assume every frame is the same size, pick first frame
        BONGOCAT_LOG_DEBUG("Loaded %dx%d sprite sheet with %d frames", anim.sprite_sheet_width, anim.sprite_sheet_height);

        return bongocat_error_t::BONGOCAT_SUCCESS;
    }
#endif

#ifdef FEATURE_BONGOCAT_EMBEDDED_ASSETS
    bongocat_error_t init_bongocat_anim(animation_context_t& ctx, int anim_index, get_sprite_callback_t get_sprite, size_t embedded_images_count) {
        using namespace assets;
        BONGOCAT_CHECK_NULL(ctx.shm.ptr, bongocat_error_t::BONGOCAT_ERROR_INVALID_PARAM);
        BONGOCAT_CHECK_NULL(ctx._local_copy_config.ptr, bongocat_error_t::BONGOCAT_ERROR_INVALID_PARAM);

        assert(anim_index < BONGOCAT_ANIMATIONS_COUNT);
        const int sprite_sheet_count = anim_load_embedded_images_into_sprite_sheet(ctx.shm->bongocat_anims[anim_index].sprite_sheet, get_sprite, embedded_images_count);
        if (sprite_sheet_count < 0) {
            BONGOCAT_LOG_ERROR("Load dm Animation failed: index: %d", anim_index);

            return bongocat_error_t::BONGOCAT_ERROR_ANIMATION;
        }

        return bongocat_error_t::BONGOCAT_SUCCESS;
    }
#endif

#ifdef FEATURE_ENABLE_DM_EMBEDDED_ASSETS
    bongocat_error_t init_dm_anim(animation_context_t& ctx, int anim_index, const assets::embedded_image_t& sprite_sheet_image, int sprite_sheet_cols, int sprite_sheet_rows) {
        using namespace assets;
        BONGOCAT_CHECK_NULL(ctx.shm.ptr, bongocat_error_t::BONGOCAT_ERROR_INVALID_PARAM);
        BONGOCAT_CHECK_NULL(ctx._local_copy_config.ptr, bongocat_error_t::BONGOCAT_ERROR_INVALID_PARAM);

        assert(anim_index < DM_ANIMATIONS_COUNT);
        const int sprite_sheet_count = anim_load_sprite_sheet(*ctx._local_copy_config, ctx.shm->dm_anims[anim_index].sprite_sheet, sprite_sheet_image, sprite_sheet_cols, sprite_sheet_rows);
        if (sprite_sheet_count < 0) {
            BONGOCAT_LOG_ERROR("Load dm Animation failed: %s, index: %d", sprite_sheet_image.name, anim_index);

            return bongocat_error_t::BONGOCAT_ERROR_ANIMATION;
        }

        return bongocat_error_t::BONGOCAT_SUCCESS;
    }
#endif

#ifdef FEATURE_MS_AGENT_EMBEDDED_ASSETS
    bongocat_error_t init_ms_pet_anim(animation_context_t& ctx, int anim_index, const assets::embedded_image_t& sprite_sheet_image, int sprite_sheet_cols, int sprite_sheet_rows) {
        using namespace assets;
        BONGOCAT_CHECK_NULL(ctx.shm.ptr, bongocat_error_t::BONGOCAT_ERROR_INVALID_PARAM);
        BONGOCAT_CHECK_NULL(ctx._local_copy_config.ptr, bongocat_error_t::BONGOCAT_ERROR_INVALID_PARAM);

        assert(anim_index < MS_AGENTS_ANIMATIONS_COUNT);
        const bongocat_error_t result = anim_load_sprite_sheet(*ctx._local_copy_config, ctx.shm->ms_anims[anim_index], sprite_sheet_image, sprite_sheet_cols, sprite_sheet_rows);
        if (result != bongocat_error_t::BONGOCAT_SUCCESS) {
            BONGOCAT_LOG_ERROR("Load dm Animation failed: %s, index: %d", sprite_sheet_image.name, anim_index);

            return bongocat_error_t::BONGOCAT_ERROR_ANIMATION;
        }

        return bongocat_error_t::BONGOCAT_SUCCESS;
    }
#endif
}