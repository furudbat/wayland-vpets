#include "graphics/drawing.h"
#include "graphics/animation_context.h"
#include "graphics/animation.h"
#include <cassert>

namespace bongocat::animation {
    // =============================================================================
    // GLOBAL STATE AND CONFIGURATION
    // =============================================================================

    static inline constexpr uint8_t THRESHOLD_ALPHA = 127;
    static inline constexpr unsigned int FIXED_SHIFT = 16;
    static inline constexpr unsigned int FIXED_ONE   = (1u << FIXED_SHIFT);

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

    void drawing_copy_pixel(uint8_t *dest, int dest_channels, int dest_idx,
                                   const unsigned char *src, int src_channels, int src_idx,
                                   blit_image_color_option_flags_t options,
                                   blit_image_color_order_t dest_order,
                                   blit_image_color_order_t src_order)
    {
        if (has_flag(options, blit_image_color_option_flags_t::Invisible)) return;
        const bool invert = has_flag(options, blit_image_color_option_flags_t::Invert);

        // Map source channel indices for RGB
        const int sr = (src_order == blit_image_color_order_t::RGBA) ? 0 : 2;
        const int sg = 1;
        const int sb = (src_order == blit_image_color_order_t::RGBA) ? 2 : 0;

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
        const int dr = (dest_order == blit_image_color_order_t::RGBA) ? 0 : 2;
        constexpr int dg = 1;
        const int db = (dest_order == blit_image_color_order_t::RGBA) ? 2 : 0;

        // Store without branching
        if (dest_channels >= 1) dest[dest_idx + dr] = r;
        if (dest_channels >= 2) dest[dest_idx + dg] = g;
        if (dest_channels >= 3) dest[dest_idx + db] = b;
        if (dest_channels >= 4) dest[dest_idx + 3]  = a;
    }

    void blit_image_scaled(uint8_t *dest, size_t dest_size, int dest_w, int dest_h, int dest_channels,
                           const unsigned char *src, size_t src_size, int src_w, int src_h, int src_channels,
                           int src_x, int src_y,
                           int frame_w, int frame_h,
                           int offset_x, int offset_y, int target_w, int target_h,
                           blit_image_color_order_t dest_order,
                           blit_image_color_order_t src_order,
                           blit_image_color_option_flags_t options)
    {
        if (!dest || !src) return;
        if (dest_w <= 0 || dest_h <= 0 || src_w <= 0 || src_h <= 0) return;
        if (dest_channels <= 0 || src_channels <= 0) return;
        if (target_w <= 0 || target_h <= 0) return;
        if (frame_w <= 0 || frame_h <= 0) return;
        if (has_flag(options, blit_image_color_option_flags_t::Invisible)) return;

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
                                                   options, dest_order, src_order);
                            }
                        } else {
                            // opaque source (no alpha), just copy
                            drawing_copy_pixel(dest, dest_channels, dest_idx,
                                               src, src_channels, src_idx,
                                               options, dest_order, src_order);
                        }
                    }
                }

                // advance fixed x and destination pointer
                sx_fixed += inc_x;
                dest_ptr += dest_channels;
            }
        }
    }
}