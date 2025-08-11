#define _POSIX_C_SOURCE 199309L
#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_PNG
#include "graphics/embedded_assets.h"
#include "graphics/context.h"
#include "graphics/animation.h"
#include "platform/wayland.h"
#include "graphics/bar.h"
#include "utils/memory.h"
#include "utils/time.h"
#include <time.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/mman.h>

// include stb_image
#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdouble-promotion"
#pragma GCC diagnostic ignored "-Wsign-compare"  // Optional: suppress more
#endif
#include "../lib/stb_image.h"
#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic pop
#endif

// =============================================================================
// GLOBAL STATE AND CONFIGURATION
// =============================================================================

#define THRESHOLD_ALPHA 127

// Bongocat Frames
#define BONGOCAT_FRAME_BOTH_UP 0
#define BONGOCAT_FRAME_LEFT_DOWN 1
#define BONGOCAT_FRAME_RIGHT_DOWN 2
#define BONGOCAT_FRAME_BOTH_DOWN 3

#ifndef FEATURE_INCLUDE_ONLY_BONGOCAT_EMBEDDED_ASSETS
// Digimon (Sprite Sheet) Frames
#define DIGIMON_FRAME_IDLE1 0
#define DIGIMON_FRAME_IDLE2 1
#define DIGIMON_FRAME_ANGRY 2 // Angry/Refuse or Hit (Fallback), Eat Frame Fallback
#define DIGIMON_FRAME_DOWN1 3 // Sleep/Discipline Fallback
#define DIGIMON_FRAME_HAPPY 4
#define DIGIMON_FRAME_EAT1 5
#define DIGIMON_FRAME_SLEEP1 6
#define DIGIMON_FRAME_REFUSE 7
#define DIGIMON_FRAME_SAD 8

// optional frames
#define DIGIMON_FRAME_DOWN2 9
#define DIGIMON_FRAME_EAT2 10
#define DIGIMON_FRAME_SLEEP2 11
#define DIGIMON_FRAME_ATTACK 12

#define DIGIMON_FRAME_MOVEMENT1 13
#define DIGIMON_FRAME_MOVEMENT2 14

#define HAPPY_CHANCE_PERCENT 60
#endif

static int rand_minmax(int min, int max) {
    return rand() % (max - min + 1) + min;
}

// =============================================================================
// DRAWING OPERATIONS MODULE
// =============================================================================

static bool drawing_is_pixel_in_bounds(int x, int y, int width, int height) {
    return x >= 0 && y >= 0 && x < width && y < height;
}

static inline uint8_t apply_invert(uint8_t v, bool invert) {
    return v ^ (invert ? 0xFF : 0x00); // branchless invert
}

static void drawing_copy_pixel(uint8_t *dest, int dest_channels, int dest_idx,
                               const unsigned char *src, int src_channels, int src_idx,
                               drawing_copy_pixel_color_option_t option,
                               drawing_color_order_t dest_order,
                               drawing_color_order_t src_order)
{
    const int invert = (option == COPY_PIXEL_OPTION_INVERT);

    // Map source channel indices for RGB
    const int sr = (src_order == COLOR_ORDER_RGBA) ? 0 : 2;
    const int sg = 1;
    const int sb = (src_order == COLOR_ORDER_RGBA) ? 2 : 0;

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
        uint8_t gray = apply_invert(src[src_idx], invert);
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
    int dr = (dest_order == COLOR_ORDER_RGBA) ? 0 : 2;
    int dg = 1;
    int db = (dest_order == COLOR_ORDER_RGBA) ? 2 : 0;

    // Store without branching
    if (dest_channels >= 1) dest[dest_idx + dr] = r;
    if (dest_channels >= 2) dest[dest_idx + dg] = g;
    if (dest_channels >= 3) dest[dest_idx + db] = b;
    if (dest_channels >= 4) dest[dest_idx + 3]  = a;
}

static bongocat_error_t load_sprite_sheet_from_memory(generic_sprite_sheet_animation_t* out_frames,
                                          const uint8_t* sprite_data, size_t sprite_data_size,
                                          int frame_columns, int frame_rows,
                                          int padding_x, int padding_y,
                                          drawing_copy_pixel_color_option_t drawing_option) {
    int sheet_width = 0;
    int sheet_height = 0;
    int channels = STBI_rgb_alpha;
    assert(sprite_data_size <= INT_MAX);
    uint8_t* sprite_sheet_pixels = stbi_load_from_memory(sprite_data, (int)sprite_data_size, &sheet_width, &sheet_height, NULL, channels); // Force RGBA
    if (!sprite_sheet_pixels) {
        BONGOCAT_LOG_ERROR("Failed to load sprite sheet.");
        return BONGOCAT_ERROR_FILE_IO;
    }

    if (frame_columns == 0 || frame_rows == 0 ||
        sheet_width % frame_columns != 0 || sheet_height % frame_rows != 0) {
        BONGOCAT_LOG_ERROR("Sprite sheet dimensions not divisible by frame grid.");
        stbi_image_free(sprite_sheet_pixels);
        sprite_sheet_pixels = NULL;
        return BONGOCAT_ERROR_INVALID_PARAM;
    }

    const int frame_width = sheet_width / frame_columns;
    const int frame_height = sheet_height / frame_rows;
    const int total_frames = frame_columns * frame_rows;

    /*
    assert(MAX_NUM_FRAMES <= INT_MAX);
    if (total_frames > (int)MAX_NUM_FRAMES) {
        BONGOCAT_LOG_ERROR("Sprite Sheet does not fit in out_frames: %d, total_frames: %d", MAX_NUM_FRAMES, total_frames);
        stbi_image_free(sprite_sheet_pixels);
        sprite_sheet_pixels = NULL;
        return BONGOCAT_ERROR_INVALID_PARAM;
    }
    */

    const int dest_frame_width = frame_width + padding_x*2;
    const int dest_frame_height = frame_height + padding_y*2;
    const int dest_pixels_width = dest_frame_width * frame_columns;
    const int dest_pixels_height = dest_frame_height * frame_rows;
    const size_t dest_pixels_size = dest_pixels_width * dest_pixels_height * channels;
    unsigned char *dest_pixels = BONGOCAT_MALLOC(dest_pixels_size);
    memset(dest_pixels, 0, dest_pixels_size);
    if (!dest_pixels) {
        BONGOCAT_LOG_ERROR("Failed to allocate memory for dest_pixels (%zu bytes)\n", dest_pixels_size);
        stbi_image_free(sprite_sheet_pixels);
        sprite_sheet_pixels = NULL;
        return BONGOCAT_ERROR_MEMORY;
    }

    const int src_frame_width = frame_width;
    const int src_frame_height = frame_height;
    const int src_pixels_width = sheet_width;
    const int src_pixels_height = sheet_height;
    const size_t src_pixels_size = src_pixels_width * src_pixels_height * channels;
    size_t frame_index = 0;
    for (int row = 0; row < frame_rows; ++row) {
        for (int col = 0; col < frame_columns; ++col) {
            const int src_x = col * src_frame_width;
            const int src_y = row * src_frame_height;
            const int dst_x = col * dest_frame_width + padding_x;
            const int dst_y = row * dest_frame_height + padding_y;
            const int src_idx = (src_y * src_pixels_width + src_x) * channels;
            const int dst_idx = (dst_y * dest_pixels_width + dst_x) * channels;

            assert(src_idx >= 0);
            assert(dst_idx >= 0);

            bool set_frames = false;
            for (int fy = 0; fy < src_frame_height; fy++) {
                for (int fx = 0; fx < src_frame_width; fx++) {
                    int src_px_idx = ((src_y + fy) * src_pixels_width + (src_x + fx)) * channels;
                    int dst_px_idx = ((dst_y + fy) * dest_pixels_width + (dst_x + fx)) * channels;

                    if (src_px_idx >= 0 && dst_px_idx >= 0 &&
                        (size_t)src_px_idx < src_pixels_size &&
                        (size_t)dst_px_idx < dest_pixels_size) {
                        drawing_copy_pixel(dest_pixels, channels, dst_px_idx,
                                           sprite_sheet_pixels, channels, src_px_idx,
                                           drawing_option, COLOR_ORDER_RGBA, COLOR_ORDER_RGBA);
                        if (!set_frames && frame_index < MAX_NUM_FRAMES) {
                            set_frames = true;
                        }
                    }
                }
            }
            if (frame_index < MAX_NUM_FRAMES) {
                if (set_frames) {
                    out_frames->frames[frame_index] = (sprite_sheet_animation_region_t){ .valid = true, .col = col, .row = row };
                } else {
                    out_frames->frames[frame_index] = (sprite_sheet_animation_region_t){ .valid = false, .col = 0, .row = 0, };
                }
            }

            frame_index++;
        }
    }

    stbi_image_free(sprite_sheet_pixels);
    sprite_sheet_pixels = NULL;

    out_frames->sprite_sheet_width = sheet_width;
    out_frames->sprite_sheet_height = sheet_height;
    out_frames->channels = channels;
    // move pixel ownership into out frames
    out_frames->pixels = dest_pixels;
    out_frames->pixels_size = dest_pixels_size;
    dest_pixels = NULL;
    out_frames->frame_width = dest_frame_width;
    out_frames->frame_height = dest_frame_height;
    out_frames->total_frames = total_frames;

    return BONGOCAT_SUCCESS;
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


#define FIXED_SHIFT 16
#define FIXED_ONE   (1 << FIXED_SHIFT)
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
    size_t needed_dest = (size_t)dest_w * (size_t)dest_h * (size_t)dest_channels;
    size_t needed_src  = (size_t)src_w  * (size_t)src_h  * (size_t)src_channels;
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
    const int32_t inc_x = (int32_t)(((int64_t)frame_w << FIXED_SHIFT) / (int64_t)target_w);
    const int32_t inc_y = (int32_t)(((int64_t)frame_h << FIXED_SHIFT) / (int64_t)target_h);

    // Starting fixed positions for sampling: (src_x, src_y) in fixed point
    const int32_t src_x_start = (int32_t)(src_x << FIXED_SHIFT);
    const int32_t src_y_start = (int32_t)(src_y << FIXED_SHIFT);

    // Precompute some constants for row indexing
    const size_t src_row_bytes  = (size_t)src_w * (size_t)src_channels;
    const size_t dest_row_bytes = (size_t)dest_w * (size_t)dest_channels;

    // Loop over clipped target Y
    for (int ty = y0; ty < y1; ++ty) {
        const int dy = offset_y + ty;  // dest y
        assert((unsigned)dy < (unsigned)dest_h);
        // fixed-point source y for this target y
        int32_t sy_fixed = src_y_start + (int32_t)((int64_t)ty * inc_y);
        int sy = sy_fixed >> FIXED_SHIFT;
        if ((unsigned)sy >= (unsigned)src_h) continue; // out of source bounds (shouldn't happen with clipping but safe)

        // Pointers to the start of the rows
        uint8_t *dest_row = dest + (size_t)dy * dest_row_bytes;
        const uint8_t *src_row = src + (size_t)sy * src_row_bytes;

        // Start x in target coords and compute corresponding initial sx_fixed for x0
        int32_t sx_fixed = src_x_start + (int32_t)((int64_t)x0 * inc_x);

        // Destination x start and destination pointer
        int dx = offset_x + x0;
        uint8_t *dest_ptr = dest_row + (size_t)dx * dest_channels;

        // For each x in clipped horizontal range
        for (int tx = x0; tx < x1; ++tx) {
            int sx = sx_fixed >> FIXED_SHIFT;
            // If sampled source pixel is outside source bounds, skip (safe-guard)
            if ((unsigned)sx < (unsigned)src_w) {
                const uint8_t *src_pixel = src_row + (size_t)sx * src_channels;

                // If source has alpha channel and is transparent (<= threshold), skip.
                if (src_channels >= 4) {
                    if (src_pixel[3] > THRESHOLD_ALPHA) {
                        // compute indices for drawing_copy_pixel (byte offsets)
                        int dest_idx = (int)(dest_ptr - dest); // index in bytes from dest base
                        int src_idx  = (int)(src_pixel - src); // index in bytes from src base

                        drawing_copy_pixel(dest, dest_channels, dest_idx,
                                           src, src_channels, src_idx,
                                           COPY_PIXEL_OPTION_NORMAL, dest_order, src_order);
                    }
                } else {
                    // opaque source (no alpha), just copy
                    int dest_idx = (int)(dest_ptr - dest);
                    int src_idx  = (int)(src_pixel - src);

                    drawing_copy_pixel(dest, dest_channels, dest_idx,
                                       src, src_channels, src_idx,
                                       COPY_PIXEL_OPTION_NORMAL, dest_order, src_order);
                }
            }

            // advance fixed x and destination pointer
            sx_fixed += inc_x;
            dest_ptr += dest_channels;
        }
    }
}

// =============================================================================
// ANIMATION STATE MANAGEMENT MODULE
// =============================================================================

static bool is_sleep_time(const config_t *config) {
    time_t raw_time;
    struct tm *time_info;

    time(&raw_time);
    time_info = localtime(&raw_time);

    const int now_minutes = time_info->tm_hour * 60 + time_info->tm_min;
    const int begin = config->sleep_begin.hour * 60 + config->sleep_begin.min;
    const int end = config->sleep_end.hour * 60 + config->sleep_end.min;

    // Normal range (e.g., 10:00–22:00): begin < end && (now_minutes >= begin && now_minutes < end)
    // Overnight range (e.g., 22:00–06:00): begin > end && (now_minutes >= begin || now_minutes < end)

    return (begin == end) ||
           (begin < end ? (now_minutes >= begin && now_minutes < end)
                        : (now_minutes >= begin || now_minutes < end));
}

typedef struct {
    timestamp_us_t hold_until_us;
    int test_counter;
    int test_interval_frames;
    time_ns_t frame_time_ns;
} animation_state_t;

static int anim_get_random_active_frame(animation_context_t* ctx, const input_context_t* input) {
#ifdef FEATURE_INCLUDE_ONLY_BONGOCAT_EMBEDDED_ASSETS
    UNUSED(ctx); UNUSED(input);
    return rand_minmax(1, 2); // Frame 1 or 2 (active frames)
#else
    if (ctx->anim_index == BONGOCAT_ANIM_INDEX) {
        return rand_minmax(1, 2); // Frame 1 or 2 (active frames)
    }

    const int current_frame = ctx->anim_frame_index;

    // read-only config
    const config_t* const current_config = ctx->_local_copy_config;
    assert(current_config);

    // toggle sleep frame (if 2 frame exists for sleeping)
    if (current_config->enable_scheduled_sleep && is_sleep_time(current_config)) {
        if (current_frame == DIGIMON_FRAME_SLEEP1) {
            if (ctx->anims[ctx->anim_index].digimon.sleep_2.valid) {
                return DIGIMON_FRAME_SLEEP2;
            } else if (ctx->anims[ctx->anim_index].digimon.sleep1.valid) {
                return DIGIMON_FRAME_SLEEP1;
            } else if (ctx->anims[ctx->anim_index].digimon.down1.valid) {
                BONGOCAT_LOG_VERBOSE("No Sleeping Frame for %d", ctx->anim_index);
                // fallback frame
                return DIGIMON_FRAME_DOWN1;
            }
        } else if (current_frame == DIGIMON_FRAME_SLEEP2) {
            if (ctx->anims[ctx->anim_index].digimon.sleep1.valid) {
                return DIGIMON_FRAME_SLEEP1;
            } else if (ctx->anims[ctx->anim_index].digimon.down1.valid) {
                BONGOCAT_LOG_VERBOSE("No Sleeping Frame for %d", ctx->anim_index);
                // fallback frame
                return DIGIMON_FRAME_DOWN1;
            }
        }
    }

    // toggle frame
    if (current_frame == DIGIMON_FRAME_IDLE1) {
        if (*input->kpm > 0) {
            if (current_config->happy_kpm > 0 && *input->kpm >= current_config->happy_kpm) {
                if (ctx->anims[ctx->anim_index].digimon.happy.valid) {
                    if (rand() % 100 < HAPPY_CHANCE_PERCENT) {
                        return DIGIMON_FRAME_HAPPY;
                    }
                }
            }
        }

        return DIGIMON_FRAME_IDLE2;
    } else if (current_frame == DIGIMON_FRAME_IDLE2) {
        return DIGIMON_FRAME_IDLE1;
    }

    return rand_minmax(0, 1); // Frame 0 or 1 (active frames)
#endif
}

static void anim_trigger_frame_change(animation_context_t* ctx,
                                      int new_frame, long duration_us, long current_time_us,
                                      animation_state_t *state) {
    assert(ctx);
    assert(state);
    // read-only config
    const config_t* const current_config = ctx->_local_copy_config;
    assert(current_config);

    if (current_config->enable_debug) {
        BONGOCAT_LOG_VERBOSE("Animation frame change: %d (duration: %ld us)", new_frame, duration_us);
    }
    
    ctx->anim_frame_index = new_frame;
    state->hold_until_us = current_time_us + duration_us;
}

static void anim_handle_test_animation(animation_context_t* ctx, const input_context_t* input, animation_state_t *state, timestamp_us_t current_time_us) {
    assert(ctx);
    assert(state);
    assert(input);
    // read-only config
    const config_t* const current_config = ctx->_local_copy_config;
    assert(current_config);

    if (current_config->test_animation_interval_sec <= 0) {
        return;
    }
    
    state->test_counter++;
    if (state->test_counter > state->test_interval_frames) {
        const int new_frame = anim_get_random_active_frame(ctx, input);
        const time_us_t duration_us = current_config->test_animation_duration_ms * 1000;
        
        BONGOCAT_LOG_VERBOSE("Test animation trigger");
        anim_trigger_frame_change(ctx, new_frame, duration_us, current_time_us, state);
        state->test_counter = 0;
    }
}

static void anim_handle_key_press(animation_context_t* ctx, input_context_t *input, animation_state_t *state, timestamp_us_t current_time_us) {
    assert(ctx);
    assert(state);
    assert(input);
    // read-only config
    const config_t* const current_config = ctx->_local_copy_config;
    assert(current_config);

    if (!*input->any_key_pressed) {
        return;
    }
    
    const int new_frame = anim_get_random_active_frame(ctx, input);
    const time_us_t duration_us = current_config->keypress_duration_ms * 1000;
    
    BONGOCAT_LOG_VERBOSE("Key press detected - switching to frame %d", new_frame);
    anim_trigger_frame_change(ctx, new_frame, duration_us, current_time_us, state);

    *input->any_key_pressed = 0;
    state->test_counter = 0; // Reset test counter
}

static void anim_handle_idle_return(animation_context_t* ctx, input_context_t *input, animation_state_t *state, timestamp_us_t current_time_us) {
    assert(ctx);
    assert(state);
    assert(input);
    // read-only config
    const config_t* const current_config = ctx->_local_copy_config;
    assert(current_config);

    // Sleep Mode
    if (current_config->enable_scheduled_sleep) {
        if (is_sleep_time(current_config)) {
            if (ctx->anim_index == BONGOCAT_ANIM_INDEX) {
                ctx->anim_frame_index = BONGOCAT_FRAME_BOTH_DOWN;
                return;
            }

#ifndef FEATURE_INCLUDE_ONLY_BONGOCAT_EMBEDDED_ASSETS
            // assume it's a digimon
            if (ctx->anims[ctx->anim_index].digimon.sleep1.valid) {
                ctx->anim_frame_index = DIGIMON_FRAME_SLEEP1;
                return;
            }
            if (ctx->anims[ctx->anim_index].digimon.down1.valid) {
                // fallback frame
                ctx->anim_frame_index = DIGIMON_FRAME_DOWN1;
                return;
            }
#endif
        }
    }

    // Idle Sleep
    if (current_config->idle_sleep_timeout_sec > 0 && *input->last_key_pressed_timestamp > 0) {
        const timestamp_ms_t now = get_current_time_ms();
        const time_ms_t idle_sleep_timeout_ms = current_config->idle_sleep_timeout_sec*1000;
        if (now - *input->last_key_pressed_timestamp >= idle_sleep_timeout_ms) {
            if (ctx->anim_index == BONGOCAT_ANIM_INDEX) {
                ctx->anim_frame_index = BONGOCAT_FRAME_BOTH_DOWN;
                return;
            }

#ifndef FEATURE_INCLUDE_ONLY_BONGOCAT_EMBEDDED_ASSETS
            // assume it's a digimon
            if (ctx->anims[ctx->anim_index].digimon.down1.valid) {
                ctx->anim_frame_index = DIGIMON_FRAME_DOWN1;
                return;
            }
#endif
        }
    }

    if (current_time_us <= state->hold_until_us) {
        return;
    }
    
    if (ctx->anim_frame_index != current_config->idle_frame) {
        BONGOCAT_LOG_VERBOSE("Returning to idle frame %d", current_config->idle_frame);
        ctx->anim_frame_index = current_config->idle_frame;
    }
}

static void anim_update_state(animation_context_t* ctx, input_context_t *input, animation_state_t *state) {
    assert(ctx);
    assert(state);
    assert(input);

    timestamp_us_t current_time_us = get_current_time_us();
    
    pthread_mutex_lock(&ctx->anim_lock);
    
    anim_handle_test_animation(ctx, input, state, current_time_us);
    anim_handle_key_press(ctx, input, state, current_time_us);
    anim_handle_idle_return(ctx, input, state, current_time_us);
    
    pthread_mutex_unlock(&ctx->anim_lock);
}

// =============================================================================
// ANIMATION THREAD MANAGEMENT MODULE
// =============================================================================

static void anim_init_state(animation_context_t* ctx, animation_state_t *state) {
    assert(ctx);
    assert(state);
    // read-only config
    const config_t* const current_config = ctx->_local_copy_config;
    assert(current_config);
    assert(current_config->fps != 0);

    state->hold_until_us = 0;
    state->test_counter = 0;
    state->test_interval_frames = current_config->test_animation_interval_sec * current_config->fps;
    state->frame_time_ns = 1000000000LL / current_config->fps;
}



static void *anim_thread_main(void *arg) {
    assert(arg);
    animation_context_t* ctx = arg;

    animation_state_t state;
    anim_init_state(ctx, &state);
    
    const struct timespec frame_delay = {0, state.frame_time_ns};
    
    atomic_store(&ctx->_animation_running, true);
    BONGOCAT_LOG_DEBUG("Animation thread main loop started");
    
    while (atomic_load(&ctx->_animation_running)) {
        anim_update_state(ctx, ctx->_input, &state);
        draw_bar(ctx->_wayland, ctx);
        nanosleep(&frame_delay, NULL);
    }
    
    BONGOCAT_LOG_DEBUG("Animation thread main loop exited");

    return NULL;
}

// =============================================================================
// IMAGE LOADING MODULE
// =============================================================================

typedef struct {
    const unsigned char *data;
    size_t size;
    const char *name;
} embedded_image_t;

#define BONGOCAT_EMBEDDED_IMAGES_COUNT BONGOCAT_NUM_FRAMES
static embedded_image_t* init_bongocat_embedded_images(void) {
    static embedded_image_t bongocat_embedded_images[BONGOCAT_EMBEDDED_IMAGES_COUNT];

    bongocat_embedded_images[BONGOCAT_FRAME_BOTH_UP] = (embedded_image_t){bongo_cat_both_up_png, bongo_cat_both_up_png_size, "embedded bongo-cat-both-up.png"};
    bongocat_embedded_images[BONGOCAT_FRAME_LEFT_DOWN] = (embedded_image_t){bongo_cat_left_down_png, bongo_cat_left_down_png_size, "embedded bongo-cat-left-down.png"};
    bongocat_embedded_images[BONGOCAT_FRAME_RIGHT_DOWN] = (embedded_image_t){bongo_cat_right_down_png, bongo_cat_right_down_png_size, "embedded bongo-cat-right-down.png"};
    bongocat_embedded_images[BONGOCAT_FRAME_BOTH_DOWN] = (embedded_image_t){bongo_cat_both_down_png, bongo_cat_both_down_png_size, "embedded bongo-cat-both-down.png"};

    return bongocat_embedded_images;
}

#ifndef FEATURE_INCLUDE_ONLY_BONGOCAT_EMBEDDED_ASSETS
#define DIGIMON_SPRITE_SHEET_EMBEDDED_IMAGES_COUNT (1+DIGIMON_ANIMATIONS_COUNT)
static embedded_image_t* init_digimon_embedded_images(void) {
    static embedded_image_t digimon_sprite_sheet_embedded_images[DIGIMON_SPRITE_SHEET_EMBEDDED_IMAGES_COUNT];

    // index 0 is reserved for bongocat, no sprite sheet exists
    digimon_sprite_sheet_embedded_images[BONGOCAT_ANIM_INDEX] = (embedded_image_t){NULL, 0, "bongocat.png"};

#ifdef FEATURE_INCLUDE_DM_EMBEDDED_ASSETS
    /// @TODO: add full assets
#else
    //digimon_sprite_sheet_embedded_images[DM_AGUMON_ANIM_INDEX] = (embedded_image_t){dm_agumon_png, dm_agumon_png_size, "embedded agumon"};
    #include "embedded_assets/min_dm_init_digimon_embedded_images.c.inl"
    /// @TODO: index more digimons here
#endif

    return digimon_sprite_sheet_embedded_images;
}
#endif

// clean up image data allocated (copied)
static void anim_free_pixels(generic_sprite_sheet_animation_t *anims) {
    for (size_t i = 0; i < MAX_NUM_FRAMES; i++) {
        anims->frames[i] = (sprite_sheet_animation_region_t){ .valid = false, .col = 0, .row = 0 };
    }
    if (anims->pixels) BONGOCAT_FREE(anims->pixels);
    anims->pixels = NULL;
    anims->pixels_size = 0;
    anims->sprite_sheet_width = 0;
    anims->sprite_sheet_height = 0;
    anims->channels = 0;
    anims->frame_width = 0;
    anims->frame_height = 0;
    anims->total_frames = 0;
}


typedef struct {
    int channels;
    uint8_t *pixels;
    size_t pixels_size;
    int frame_width;
    int frame_height;
} loaded_sprite_sheet_frame_t;
static bongocat_error_t anim_load_embedded_images_into_sprite_sheet(generic_sprite_sheet_animation_t *anim, const embedded_image_t *embedded_images, size_t embedded_images_count) {
    assert(anim);

    int total_frames = 0;
    int max_frame_width = 0;
    int max_frame_height = 0;
    int max_channels = 0;
    loaded_sprite_sheet_frame_t* loaded_images = BONGOCAT_MALLOC(embedded_images_count * sizeof(loaded_sprite_sheet_frame_t));
    for (size_t i = 0;i < embedded_images_count; i++) {
        const embedded_image_t *img = &embedded_images[i];

        BONGOCAT_LOG_DEBUG("Loading embedded image: %s", img->name);

        loaded_images[i].channels = STBI_rgb_alpha;
        assert(img->size <= INT_MAX);
        loaded_images[i].pixels = stbi_load_from_memory(img->data, (int)img->size,
                                                  &loaded_images[i].frame_width,
                                                  &loaded_images[i].frame_height,
                                                  NULL, loaded_images[i].channels);
        if (!loaded_images[i].pixels) {
            BONGOCAT_LOG_ERROR("Failed to load embedded image: %s", img->name);
            continue;
        }
        loaded_images[i].pixels_size = loaded_images[i].frame_width * loaded_images[i].frame_height * loaded_images[i].channels;

        max_frame_width = loaded_images[i].frame_width > max_frame_width ? loaded_images[i].frame_width : max_frame_width;
        max_frame_height = loaded_images[i].frame_height > max_frame_height ? loaded_images[i].frame_height : max_frame_height;
        max_channels = loaded_images[i].channels > max_channels ? loaded_images[i].channels : max_channels;

        BONGOCAT_LOG_DEBUG("Loaded %dx%d embedded image", loaded_images[i].frame_width, loaded_images[i].frame_height);

        total_frames++;
    }

    anim->frame_width = max_frame_width;
    anim->frame_height = max_frame_height;
    anim->total_frames = total_frames;
    anim->sprite_sheet_width = max_frame_width * total_frames;
    anim->sprite_sheet_height = max_frame_height;
    anim->channels = max_channels;
    anim->pixels_size = anim->sprite_sheet_width * anim->sprite_sheet_height * anim->channels;
    anim->pixels = BONGOCAT_MALLOC(anim->pixels_size);
    if (!anim->pixels) {
        anim->frame_width = 0;
        anim->frame_height = 0;
        anim->total_frames = 0;
        anim->pixels_size = 0;
        anim->sprite_sheet_width = 0;
        anim->sprite_sheet_height = 0;
        anim->channels = 0;
        return BONGOCAT_ERROR_MEMORY;
    }
    memset(anim->pixels, 0, anim->pixels_size);
    memset(anim->frames, 0, MAX_NUM_FRAMES * sizeof(sprite_sheet_animation_region_t));
    for (int frame = 0; frame < total_frames; frame++) {
        const loaded_sprite_sheet_frame_t *src = &loaded_images[frame];
        if (!src) {
            if (frame < MAX_NUM_FRAMES) {
                anim->frames[frame] = (sprite_sheet_animation_region_t){ .valid = false, .col = frame, .row = 0 };
            }
            continue;
        }

        for (int y = 0; y < src->frame_height; y++) {
            unsigned char* dest_row = anim->pixels +
                ((y) * anim->sprite_sheet_width + (frame * max_frame_width)) * max_channels;
            const unsigned char* src_row = src->pixels + (y * src->frame_width * src->channels);
            memcpy(dest_row, src_row, src->frame_width * max_channels);
        }

        if (frame < MAX_NUM_FRAMES) {
            anim->frames[frame] = (sprite_sheet_animation_region_t){ .valid = true, .col = frame, .row = 0 };
        }
    }

    for (int i = 0; i < total_frames; i++) {
        if (loaded_images[i].pixels) stbi_image_free(loaded_images[i].pixels);
        loaded_images[i].pixels = NULL;
    }
    BONGOCAT_SAFE_FREE(loaded_images);
    loaded_images = NULL;
    
    return BONGOCAT_SUCCESS;
}

static int anim_load_sprite_sheet(const config_t *config, generic_sprite_sheet_animation_t *anim, const embedded_image_t *sprite_sheet_image, int sprite_sheet_cols, int sprite_sheet_rows) {
    BONGOCAT_CHECK_NULL(config, -1);
    BONGOCAT_CHECK_NULL(anim, -1);
    BONGOCAT_CHECK_NULL(sprite_sheet_image, -1);

    if (sprite_sheet_cols < 0 || sprite_sheet_rows < 0) {
        return BONGOCAT_ERROR_INVALID_PARAM;
    }

    assert(sprite_sheet_image->size <= INT_MAX);

    const int result = load_sprite_sheet_from_memory(anim,
                                  sprite_sheet_image->data, (int)sprite_sheet_image->size,
                                  sprite_sheet_cols, sprite_sheet_rows,
                                  config->padding_x, config->padding_y,
                                  config->invert_color ? COPY_PIXEL_OPTION_INVERT : COPY_PIXEL_OPTION_NORMAL);
    if (result != 0) {
        BONGOCAT_LOG_ERROR("Sprite Sheet load failed: %s", sprite_sheet_image->name);
        return -1;
    }
    if (anim->total_frames <= 0) {
        BONGOCAT_LOG_ERROR("Sprite Sheet is empty: %s", sprite_sheet_image->name);
        return 0;
    }

    // assume every frame is the same size, pick first frame
    BONGOCAT_LOG_DEBUG("Loaded %dx%d sprite sheet with %d frames", anim->sprite_sheet_width, anim->sprite_sheet_height, anim->total_frames);

    return anim->total_frames;
}

#ifndef FEATURE_INCLUDE_ONLY_BONGOCAT_EMBEDDED_ASSETS
static bongocat_error_t init_digimon_anim(animation_context_t* ctx, int anim_index, const embedded_image_t* sprite_sheet_image, int sprite_sheet_cols, int sprite_sheet_rows) {
    const int sprite_sheet_count = anim_load_sprite_sheet(ctx->_local_copy_config, &ctx->anims[anim_index].sprite_sheet, sprite_sheet_image, sprite_sheet_cols, sprite_sheet_rows);
    if (sprite_sheet_count < 0) {
        BONGOCAT_LOG_ERROR("Load Digimon Animation failed: %s, index: %d", sprite_sheet_image->name, anim_index);

        return BONGOCAT_ERROR_ANIMATION;
    }

    return BONGOCAT_SUCCESS;
}
#endif

// =============================================================================
// PUBLIC API IMPLEMENTATION
// =============================================================================

bongocat_error_t animation_init(animation_context_t* ctx, const config_t *config) {
    BONGOCAT_CHECK_NULL(ctx, BONGOCAT_ERROR_INVALID_PARAM);
    BONGOCAT_CHECK_NULL(config, BONGOCAT_ERROR_INVALID_PARAM);

    BONGOCAT_LOG_INFO("Initializing animation system");

    // Initialize shared memory for local config
    ctx->_local_copy_config = (config_t *)mmap(NULL, sizeof(config_t), PROT_READ | PROT_WRITE,
                                        MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if (ctx->_local_copy_config == MAP_FAILED) {
        BONGOCAT_LOG_ERROR("Failed to create shared memory for animation system: %s", strerror(errno));
        return BONGOCAT_ERROR_MEMORY;
    }
    config_set_defaults(ctx->_local_copy_config);

    animation_update_config(ctx, config);
    ctx->anim_frame_index = config->idle_frame;

    ctx->anim_lock = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
    ctx->_animation_running = false;

    // empty animations
    for (size_t i = 0;i < ANIMS_COUNT; i++) {
        ctx->anims[i].sprite_sheet.sprite_sheet_width = 0;
        ctx->anims[i].sprite_sheet.sprite_sheet_height = 0;
        ctx->anims[i].sprite_sheet.channels = 4;
        ctx->anims[i].sprite_sheet.pixels = NULL;
        ctx->anims[i].sprite_sheet.pixels_size = 0;
        ctx->anims[i].sprite_sheet.frame_width = 0;
        ctx->anims[i].sprite_sheet.frame_height = 0;
        ctx->anims[i].sprite_sheet.total_frames = 0;
        for (size_t j = 0; j < MAX_NUM_FRAMES; j++) {
            ctx->anims[i].sprite_sheet.frames[j] = (sprite_sheet_animation_region_t){ .valid = false, .col = 0, .row = 0};
        }
    }
    
    // Initialize embedded images data
    const embedded_image_t* bongocat_embedded_images = init_bongocat_embedded_images();
    const int result = anim_load_embedded_images_into_sprite_sheet(&ctx->anims[BONGOCAT_ANIM_INDEX].sprite_sheet, bongocat_embedded_images, BONGOCAT_EMBEDDED_IMAGES_COUNT);
    if (result != 0) {
        munmap(ctx->_local_copy_config, sizeof(config_t));
        ctx->_local_copy_config = NULL;
        return result;
    }
    /// @TODO: check bongocat_embedded_images demantions with BONGOCAT_IMAGE_WIDTH, print warning ?

#ifndef FEATURE_INCLUDE_ONLY_BONGOCAT_EMBEDDED_ASSETS
    const embedded_image_t* digimon_sprite_sheet_embedded_images = init_digimon_embedded_images();

#ifdef FEATURE_INCLUDE_DM_EMBEDDED_ASSETS

#else
    UNUSED(init_digimon_anim);
    //init_digimon_anim(ctx, DM_AGUMON_ANIM_INDEX, &digimon_sprite_sheet_embedded_images[DM_AGUMON_ANIM_INDEX], DM_AGUMON_SPRITE_SHEET_COLS, DM_AGUMON_SPRITE_SHEET_ROWS);
    #include "embedded_assets/min_dm_init_digimon_anim.c.inl"
#endif
#endif
    
    BONGOCAT_LOG_INFO("Animation system initialized successfully with embedded assets");
    return BONGOCAT_SUCCESS;
}

bongocat_error_t animation_start(animation_context_t* ctx, input_context_t *input, wayland_context_t *wayland) {
    BONGOCAT_CHECK_NULL(ctx, BONGOCAT_ERROR_INVALID_PARAM);
    BONGOCAT_CHECK_NULL(input, BONGOCAT_ERROR_INVALID_PARAM);
    BONGOCAT_CHECK_NULL(wayland, BONGOCAT_ERROR_INVALID_PARAM);

    BONGOCAT_LOG_INFO("Starting animation thread");

    ctx->_input = input;
    ctx->_wayland = wayland;
    
    const int result = pthread_create(&ctx->_anim_thread, NULL, anim_thread_main, ctx);
    if (result != 0) {
        BONGOCAT_LOG_ERROR("Failed to create animation thread: %s", strerror(result));
        return BONGOCAT_ERROR_THREAD;
    }
    
    BONGOCAT_LOG_DEBUG("Animation thread started successfully");
    return BONGOCAT_SUCCESS;
}

void animation_cleanup(animation_context_t* ctx) {
    assert(ctx);

    if (atomic_load(&ctx->_animation_running)) {
        BONGOCAT_LOG_DEBUG("Stopping animation thread");
        atomic_store(&ctx->_animation_running, false);
        // Wait for thread to finish gracefully
        pthread_cancel(ctx->_anim_thread);
        pthread_join(ctx->_anim_thread, NULL);
        ctx->_anim_thread = 0;
        BONGOCAT_LOG_DEBUG("Animation thread stopped");
    }

    // Cleanup loaded images
    for (size_t i = 0;i < ANIMS_COUNT; i++) {
        anim_free_pixels(&ctx->anims[i].sprite_sheet);
    }
    
    // Cleanup mutex
    pthread_mutex_destroy(&ctx->anim_lock);

    if (ctx->_local_copy_config && ctx->_local_copy_config != MAP_FAILED) {
        munmap(ctx->_local_copy_config, sizeof(config_t));
        ctx->_local_copy_config = NULL;
    }
    
    BONGOCAT_LOG_DEBUG("Animation cleanup complete");
}

void animation_trigger(input_context_t *input) {
    assert(input);
    /// @TODO: use epool to trigger animation input in animation thread
    *input->any_key_pressed = 1;
}

void animation_update_config(animation_context_t *ctx, const config_t *config) {
    assert(ctx);
    assert(config);
    assert(ctx->_local_copy_config && ctx->_local_copy_config != MAP_FAILED);

#ifndef NDEBUG
    if (config->animation_index < 0 || config->animation_index >= ANIMS_COUNT) {
        BONGOCAT_LOG_WARNING("Invalid animation index %d", config->animation_index);
    }
#endif

    memcpy(ctx->_local_copy_config, config, sizeof(config_t));
    /// @FIXME: make deep copy of keyboard_devices ?
    // output_name and keyboard_devices not used, get rid of out-side reference
    ctx->_local_copy_config->output_name = NULL;
    ctx->_local_copy_config->keyboard_devices = NULL;
    ctx->_local_copy_config->num_keyboard_devices = 0;

    ctx->anim_index = config->animation_index % ANIMS_COUNT;
}