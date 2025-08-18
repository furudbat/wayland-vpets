#pragma once
#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_PNG
#include "graphics/embedded_assets.h"
#include "graphics/animation_context.h"
#include "graphics/animation.h"
#include "utils/memory.h"
#include <pthread.h>
#include <cassert>

// include stb_image
#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdouble-promotion"
#pragma GCC diagnostic ignored "-Wsign-compare"
#pragma GCC diagnostic ignored "-Wunused-function"
#pragma GCC diagnostic ignored "-Wold-style-cast"
#pragma GCC diagnostic ignored "-Wsign-conversion"
#pragma GCC diagnostic ignored "-Wcast-align"
#pragma GCC diagnostic ignored "-Wconversion"
#if defined(__GNUC__) && !defined(__clang__)
#pragma GCC diagnostic ignored "-Wduplicated-branches"
#pragma GCC diagnostic ignored "-Wuseless-cast"
//#pragma GCC diagnostic ignored "-Wimplicit-int-conversion"
#endif
#endif
#include "../lib/stb_image.h"
#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic pop
#endif

namespace bongocat::animation {
    // =============================================================================
    // GLOBAL STATE AND CONFIGURATION
    // =============================================================================

    static inline constexpr uint8_t THRESHOLD_ALPHA = 127;

    // =============================================================================
    // DRAWING OPERATIONS MODULE
    // =============================================================================

    /*
    static bool drawing_is_pixel_in_bounds(int x, int y, int width, int height) {
        return x >= 0 && y >= 0 && x < width && y < height;
    }
    */

    constexpr static uint8_t apply_invert(uint8_t v, bool invert) {
        return v ^ (invert ? 0xFF : 0x00); // branchless invert
    }

    static void drawing_copy_pixel(uint8_t *dest, int dest_channels, int dest_idx,
                                   const unsigned char *src, int src_channels, int src_idx,
                                   drawing_copy_pixel_color_option_t option,
                                   drawing_color_order_t dest_order,
                                   drawing_color_order_t src_order)
    {
        const bool invert = option == drawing_copy_pixel_color_option_t::COPY_PIXEL_OPTION_INVERT;

        // Map source channel indices for RGB
        const int sr = (src_order == drawing_color_order_t::COLOR_ORDER_RGBA) ? 0 : 2;
        const int sg = 1;
        const int sb = (src_order == drawing_color_order_t::COLOR_ORDER_RGBA) ? 2 : 0;

        // Load into RGBA without branches
        uint8_t r, g, b, a;
        if (src_channels == 1) {
            // 1-channel grayscale -> fill all channels with 0/255
            uint8_t v = src[src_idx] ? 255 : 0;
            v = apply_invert(v, invert);
            r = g = b = a = v;
        }
        else if (src_channels == 2) {
            // 2-channel grayscale + alpha (alpha ignored in original)
            const uint8_t gray = apply_invert(src[src_idx], invert);
            r = g = b = gray;
            a = 255;
        }
        else {
            // RGB / RGBA
            r = apply_invert(src[src_idx + sr], invert);
            g = apply_invert(src[src_idx + sg], invert);
            b = apply_invert(src[src_idx + sb], invert);
            a = (src_channels >= 4) ? src[src_idx + 3] : 255; // Alpha not inverted
        }

        // Map destination channel indices
        const int dr = (dest_order == drawing_color_order_t::COLOR_ORDER_RGBA) ? 0 : 2;
        constexpr int dg = 1;
        const int db = (dest_order == drawing_color_order_t::COLOR_ORDER_RGBA) ? 2 : 0;

        // Store without branching
        if (dest_channels >= 1) dest[dest_idx + dr] = r;
        if (dest_channels >= 2) dest[dest_idx + dg] = g;
        if (dest_channels >= 3) dest[dest_idx + db] = b;
        if (dest_channels >= 4) dest[dest_idx + 3]  = a;
    }

    [[maybe_unused]] static bongocat_error_t load_sprite_sheet_from_memory(generic_sprite_sheet_animation_t& out_frames,
                                              const uint8_t* sprite_data, size_t sprite_data_size,
                                              int frame_columns, int frame_rows,
                                              int padding_x, int padding_y,
                                              drawing_copy_pixel_color_option_t drawing_option) {
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
                                               drawing_option, drawing_color_order_t::COLOR_ORDER_RGBA, drawing_color_order_t::COLOR_ORDER_RGBA);
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

    /*
    static void free_frames(animation_frame_t* frames, size_t frame_count) {
        for (size_t i = 0; i < frame_count; ++i) {
            BONGOCAT_SAFE_FREE(frames[i].pixels);
        }
        BONGOCAT_FREE(frames);
        frames = NULL;
    }
    */


    static inline constexpr unsigned int FIXED_SHIFT = 16;
    static inline constexpr unsigned int FIXED_ONE   = (1u << FIXED_SHIFT);
    void blit_image_scaled(uint8_t *dest, size_t dest_size, int dest_w, int dest_h, int dest_channels,
                           const unsigned char *src, size_t src_size, int src_w, int src_h, int src_channels,
                           int src_x, int src_y,
                           int frame_w, int frame_h,
                           int offset_x, int offset_y, int target_w, int target_h,
                           drawing_color_order_t dest_order,
                           drawing_color_order_t src_order)
    {
        if (!dest || !src) return;
        if (dest_w <= 0 || dest_h <= 0 || src_w <= 0 || src_h <= 0) return;
        if (dest_channels <= 0 || src_channels <= 0) return;
        if (target_w <= 0 || target_h <= 0) return;
        if (frame_w <= 0 || frame_h <= 0) return;

        // Verify buffers are large enough (simple conservative check)
        assert(dest_w >= 0);
        assert(dest_h >= 0);
        assert(dest_channels >= 0);
        assert(src_w >= 0);
        assert(src_h >= 0);
        assert(src_channels >= 0);
        const size_t needed_dest = static_cast<size_t>(dest_w) * static_cast<size_t>(dest_h) * static_cast<size_t>(dest_channels);
        const size_t needed_src  = static_cast<size_t>(src_w)  * static_cast<size_t>(src_h)  * static_cast<size_t>(src_channels);
        if (dest_size < needed_dest || src_size < needed_src) {
            return;
        }

        // Clip the destination rectangle to dest bounds:
        // target rectangle top-left in dest coordinates:
        const int dst_left   = offset_x;
        const int dst_top    = offset_y;
        const int dst_right  = offset_x + target_w;   // exclusive
        const int dst_bottom = offset_y + target_h;   // exclusive

        // compute clipped range [x0, x1) in target coordinates (x is 0..target_w-1)
        int x0 = 0, x1 = target_w;
        if (dst_left < 0)         x0 = -dst_left;
        if (dst_right > dest_w)   x1 = target_w - (dst_right - dest_w);
        if (x0 >= x1) return;

        // similarly for y
        int y0 = 0, y1 = target_h;
        if (dst_top < 0)          y0 = -dst_top;
        if (dst_bottom > dest_h)  y1 = target_h - (dst_bottom - dest_h);
        if (y0 >= y1) return;

        // Fixed-point increments (16.16)
        const auto inc_x = static_cast<int32_t>((static_cast<int64_t>(frame_w) << FIXED_SHIFT) / static_cast<int64_t>(target_w));
        const auto inc_y = static_cast<int32_t>((static_cast<int64_t>(frame_h) << FIXED_SHIFT) / static_cast<int64_t>(target_h));

        // Starting fixed positions for sampling: (src_x, src_y) in fixed point
        const int32_t src_x_start = src_x << FIXED_SHIFT;
        const int32_t src_y_start = src_y << FIXED_SHIFT;

        // Precompute some constants for row indexing
        const size_t src_row_bytes  = static_cast<size_t>(src_w) * static_cast<size_t>(src_channels);
        const size_t dest_row_bytes = static_cast<size_t>(dest_w) * static_cast<size_t>(dest_channels);

        // Loop over clipped target Y
        for (int ty = y0; ty < y1; ++ty) {
            const auto dy = offset_y + ty;  // dest y
            assert(dy < dest_h);
            // fixed-point source y for this target y
            const int32_t sy_fixed = src_y_start + static_cast<int32_t>(static_cast<int64_t>(ty) * inc_y);
            const int sy = sy_fixed >> FIXED_SHIFT;
            if (static_cast<unsigned>(sy) >= static_cast<unsigned>(src_h)) continue; // out of source bounds (shouldn't happen with clipping but safe)

            // Pointers to the start of the rows
            const uint8_t *dest_row = dest + static_cast<size_t>(dy) * dest_row_bytes;
            const uint8_t *src_row = src + static_cast<size_t>(sy) * src_row_bytes;

            // Start x in target coords and compute corresponding initial sx_fixed for x0
            int32_t sx_fixed = src_x_start + static_cast<int32_t>(static_cast<int64_t>(x0) * inc_x);

            // Destination x start and destination pointer
            const auto dx = offset_x + x0;
            assert(dest_channels >= 0);
            const unsigned char *dest_ptr = dest_row + static_cast<size_t>(dx) * static_cast<size_t>(dest_channels);

            // For each x in clipped horizontal range
            for (int tx = x0; tx < x1; ++tx) {
                // If sampled source pixel is outside source bounds, skip (safeguard)
                if (int sx = sx_fixed >> FIXED_SHIFT; static_cast<unsigned>(sx) < static_cast<unsigned>(src_w)) {
                    assert(src_channels >= 0);
                    const uint8_t *src_pixel = src_row + static_cast<size_t>(sx) * static_cast<size_t>(src_channels);
                    if (dest_ptr >= dest && src_pixel >= src) {
                        const int dest_idx = static_cast<int>(dest_ptr - dest); // index in bytes from dest base
                        const int src_idx  = static_cast<int>(src_pixel - src); // index in bytes from src base

                        // If source has alpha channel and is transparent (<= threshold), skip.
                        if (src_channels >= 4) {
                            if (src_pixel[3] > THRESHOLD_ALPHA) {
                                // compute indices for drawing_copy_pixel (byte offsets)
                                drawing_copy_pixel(dest, dest_channels, dest_idx,
                                                   src, src_channels, src_idx,
                                                   drawing_copy_pixel_color_option_t::COPY_PIXEL_OPTION_NORMAL, dest_order, src_order);
                            }
                        } else {
                            // opaque source (no alpha), just copy
                            drawing_copy_pixel(dest, dest_channels, dest_idx,
                                               src, src_channels, src_idx,
                                               drawing_copy_pixel_color_option_t::COPY_PIXEL_OPTION_NORMAL, dest_order, src_order);
                        }
                    }
                }

                // advance fixed x and destination pointer
                sx_fixed += inc_x;
                dest_ptr += dest_channels;
            }
        }
    }

    // =============================================================================
    // IMAGE LOADING MODULE
    // =============================================================================

    // clean up image data allocated (copied)
    /*
    static void anim_free_pixels(generic_sprite_sheet_animation_t& anims) {
        for (size_t i = 0; i < MAX_NUM_FRAMES; i++) {
            anims.frames[i] = { .valid = false, .col = 0, .row = 0 };
        }
        anims.pixels = nullptr;
        anims.sprite_sheet_width = 0;
        anims.sprite_sheet_height = 0;
        anims.channels = 0;
        anims.frame_width = 0;
        anims.frame_height = 0;
        anims.total_frames = 0;
    }
    */

    struct loaded_sprite_sheet_frame_t {
        int channels{0};
        uint8_t *pixels{nullptr};
        size_t pixels_size{0};
        int frame_width{0};
        int frame_height{0};
    };
    static bongocat_error_t anim_load_embedded_images_into_sprite_sheet(generic_sprite_sheet_animation_t& anim, const assets::embedded_image_t *embedded_images, size_t embedded_images_count) {
        int total_frames = 0;
        int max_frame_width = 0;
        int max_frame_height = 0;
        int max_channels = 0;
        auto loaded_images = AllocatedArray<loaded_sprite_sheet_frame_t>(embedded_images_count);
        for (size_t i = 0;i < embedded_images_count && i < loaded_images.count; i++) {
            const assets::embedded_image_t *img = &embedded_images[i];

            BONGOCAT_LOG_DEBUG("Loading embedded image: %s", img->name);
            loaded_images[i].channels = STBI_rgb_alpha;
            assert(img->size <= INT_MAX);
            loaded_images[i].pixels = stbi_load_from_memory(img->data, static_cast<int>(img->size),
                                                      &loaded_images[i].frame_width,
                                                      &loaded_images[i].frame_height,
                                                      nullptr, loaded_images[i].channels);
            if (!loaded_images[i].pixels) {
                BONGOCAT_LOG_ERROR("Failed to load embedded image: %s", img->name);
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
            return bongocat_error_t::BONGOCAT_ERROR_MEMORY;
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
        return bongocat_error_t::BONGOCAT_SUCCESS;
    }

    [[maybe_unused]] static int anim_load_sprite_sheet(const config::config_t& config, generic_sprite_sheet_animation_t& anim, const assets::embedded_image_t& sprite_sheet_image, int sprite_sheet_cols, int sprite_sheet_rows) {
        if (sprite_sheet_cols < 0 || sprite_sheet_rows < 0) {
            return -1;
        }

        assert(sprite_sheet_image.size <= INT_MAX);

        const auto result = load_sprite_sheet_from_memory(anim,
                                      sprite_sheet_image.data, sprite_sheet_image.size,
                                      sprite_sheet_cols, sprite_sheet_rows,
                                      config.padding_x, config.padding_y,
                                      config.invert_color ? drawing_copy_pixel_color_option_t::COPY_PIXEL_OPTION_INVERT : drawing_copy_pixel_color_option_t::COPY_PIXEL_OPTION_NORMAL);
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

#ifndef FEATURE_INCLUDE_ONLY_BONGOCAT_EMBEDDED_ASSETS
    static bongocat_error_t init_digimon_anim(animation_context_t& ctx, int anim_index, const assets::embedded_image_t& sprite_sheet_image, int sprite_sheet_cols, int sprite_sheet_rows) {
        BONGOCAT_CHECK_NULL(ctx.shm.ptr, bongocat_error_t::BONGOCAT_ERROR_INVALID_PARAM);
        BONGOCAT_CHECK_NULL(ctx._local_copy_config.ptr, bongocat_error_t::BONGOCAT_ERROR_INVALID_PARAM);

        const int sprite_sheet_count = anim_load_sprite_sheet(*ctx._local_copy_config, ctx.shm->anims[anim_index].sprite_sheet, sprite_sheet_image, sprite_sheet_cols, sprite_sheet_rows);
        if (sprite_sheet_count < 0) {
            BONGOCAT_LOG_ERROR("Load Digimon Animation failed: %s, index: %d", sprite_sheet_image.name, anim_index);

            return bongocat_error_t::BONGOCAT_ERROR_ANIMATION;
        }

        return bongocat_error_t::BONGOCAT_SUCCESS;
    }
#endif
}