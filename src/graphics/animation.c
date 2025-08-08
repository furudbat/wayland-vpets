#define _POSIX_C_SOURCE 199309L
#define STB_IMAGE_IMPLEMENTATION
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
#define BONGOCAT_FRAME_BOTH_DOWN 1
#define BONGOCAT_FRAME_LEFT_DOWN 2
#define BONGOCAT_FRAME_RIGHT_DOWN 3

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

static const animation_frame_t empty_sprite_sheet_frame = {
    .width = 0,
    .height = 0,
    .channels = RGBA_CHANNELS,
    .pixels = NULL,
};

static bool drawing_is_pixel_in_bounds(int x, int y, int width, int height) {
    return (x >= 0 && y >= 0 && x < width && y < height);
}

typedef enum {
    COPY_PIXEL_OPTION_NORMAL,
    COPY_PIXEL_OPTION_INVERT,
} drawing_copy_pixel_color_option_t;
static void drawing_copy_pixel(uint8_t *dest, const unsigned char *src, int dest_idx, int src_idx, drawing_copy_pixel_color_option_t option) {
    switch (option) {
        case COPY_PIXEL_OPTION_NORMAL:
            dest[dest_idx + 0] = src[src_idx + 2]; // B
            dest[dest_idx + 1] = src[src_idx + 1]; // G
            dest[dest_idx + 2] = src[src_idx + 0]; // R
            dest[dest_idx + 3] = src[src_idx + 3]; // A
            break;
        case COPY_PIXEL_OPTION_INVERT:
            dest[dest_idx + 0] = 255 - src[src_idx + 2]; // B
            dest[dest_idx + 1] = 255 - src[src_idx + 1]; // G
            dest[dest_idx + 2] = 255 - src[src_idx + 0]; // R
            dest[dest_idx + 3] = src[src_idx + 3];       // A
            break;
    }
}


static bongocat_error_t copy_cropped_frame(animation_frame_t* out_frame,
                                           animation_frame_t in_frame,
                                           int padding_x, int padding_y,
                                           drawing_copy_pixel_color_option_t drawing_option) {
    *out_frame = empty_sprite_sheet_frame;
    const int width = padding_x*2 + in_frame.width;
    const int height = padding_y*2 + in_frame.height;
    const int channels = in_frame.channels;
    const unsigned char *src_pixels = in_frame.pixels;

    unsigned char *dest_pixels = BONGOCAT_MALLOC(width * height * channels);
    if (!dest_pixels) {
        return BONGOCAT_ERROR_MEMORY;
    }
    memset(dest_pixels, 0, width * height * channels);

    /// @TODO: optimize cropped region copy
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            const int src_x = x;
            const int src_y = y;
            const int dst_x = padding_x + x;
            const int dst_y = padding_y + y;

            // skip frame
            if (src_x < 0 || src_x >= width ||
                src_y < 0 || src_y >= height) {
                continue; // Skip out-of-bounds
            }
            if (dst_x < 0 || dst_x >= width ||
                dst_y < 0 || dst_y >= height) {
                continue; // Skip out-of-bounds
            }

            const int src_pixel_index = (src_y * in_frame.width + src_x) * channels;
            const int dst_pixel_index = (dst_y * width + dst_x) * channels;

            if (src_pixel_index >= in_frame.width * in_frame.width * channels ||
                dst_pixel_index >= width * height * channels) {
                continue;
            }

            drawing_copy_pixel(dest_pixels, src_pixels, dst_pixel_index, src_pixel_index, drawing_option);
        }
    }

    // move frame
    *out_frame = in_frame;
    // move dest_pixels
    out_frame->pixels = dest_pixels;
    dest_pixels = NULL;

    return BONGOCAT_SUCCESS;
}

static bongocat_error_t load_sprite_sheet_from_memory(animation_frame_t* out_frames, size_t out_frames_count,
                                          const uint8_t* sprite_data, int sprite_size,
                                          int frame_columns, int frame_rows,
                                          int* out_frame_count,
                                          int padding_x, int padding_y,
                                          drawing_copy_pixel_color_option_t drawing_option) {
    int sheet_width, sheet_height, channels;
    uint8_t* sprite_sheet_pixels = stbi_load_from_memory(sprite_data, sprite_size, &sheet_width, &sheet_height, &channels, RGBA_CHANNELS); // Force RGBA
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

    assert(out_frames_count <= INT_MAX);
    if (total_frames > (int)out_frames_count) {
        BONGOCAT_LOG_ERROR("Sprite Sheet does not fit in out_frames: %d, total_frames: %d", out_frames_count, total_frames);
        stbi_image_free(sprite_sheet_pixels);
        sprite_sheet_pixels = NULL;
        return BONGOCAT_ERROR_INVALID_PARAM;
    }

    for (int row = 0; row < frame_rows; ++row) {
        for (int col = 0; col < frame_columns; ++col) {
            const int idx = row * frame_columns + col;

            uint8_t* frame_pixels = BONGOCAT_MALLOC(frame_width * frame_height * RGBA_CHANNELS);
            if (!frame_pixels) {
                BONGOCAT_LOG_ERROR("Failed to allocate memory for frame %d\n", idx);
                // Cleanup previously allocated
                for (int j = 0; j < idx; ++j) {
                    if (out_frames[j].pixels) BONGOCAT_FREE(out_frames[j].pixels);
                    out_frames[j].pixels = NULL;
                }
                return BONGOCAT_ERROR_MEMORY;
            }

            for (int y = 0; y < frame_height; ++y) {
                // copy pixels line
                memcpy(
                    frame_pixels + y * frame_width * RGBA_CHANNELS,
                    sprite_sheet_pixels + ((row * frame_height + y) * sheet_width + (col * frame_width)) * RGBA_CHANNELS,
                    frame_width * RGBA_CHANNELS
                );
            }

            const animation_frame_t frame_data = (animation_frame_t){
                .width = frame_width,
                .height = frame_height,
                .channels = RGBA_CHANNELS,
                .pixels = frame_pixels
            };

            copy_cropped_frame(&out_frames[idx], frame_data, padding_x, padding_y, drawing_option);

            //BONGOCAT_LOG_VERBOSE("Cropped Sprite Frame (%d): %dx%d (%dx%d)", idx, out_frames[idx].width, out_frames[idx].height, frame_width, frame_height);

            BONGOCAT_FREE(frame_pixels);
            frame_pixels = NULL;
        }
    }

    stbi_image_free(sprite_sheet_pixels);
    sprite_sheet_pixels = NULL;

    if (out_frame_count) *out_frame_count = total_frames;

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

void blit_image_scaled(uint8_t *dest, int dest_w, int dest_h,
                       const unsigned char *src, int src_w, int src_h,
                       int offset_x, int offset_y, int target_w, int target_h) {
    for (int y = 0; y < target_h; y++) {
        for (int x = 0; x < target_w; x++) {
            int dx = x + offset_x;
            int dy = y + offset_y;
            
            if (!drawing_is_pixel_in_bounds(dx, dy, dest_w, dest_h)) {
                continue;
            }

            // Map destination pixel to source pixel
            const int sx = (x * src_w) / target_w;
            const int sy = (y * src_h) / target_h;

            const int dest_idx = (dy * dest_w + dx) * RGBA_CHANNELS;
            const int src_idx = (sy * src_w + sx) * RGBA_CHANNELS;

            // Only draw non-transparent pixels
            if (src[src_idx + 3] > THRESHOLD_ALPHA) {
                drawing_copy_pixel(dest, src, dest_idx, src_idx, COPY_PIXEL_OPTION_NORMAL);
            }
        }
    }
}
void sblit_image_scaled(uint8_t *dest, size_t dest_size, int dest_w, int dest_h,
                       const unsigned char *src, size_t src_size, int src_w, int src_h,
                       int offset_x, int offset_y, int target_w, int target_h) {
    if (dest_size < RGBA_CHANNELS || src_size < RGBA_CHANNELS) {
        return;
    }
    for (int y = 0; y < target_h; y++) {
        for (int x = 0; x < target_w; x++) {
            int dx = x + offset_x;
            int dy = y + offset_y;

            if (!drawing_is_pixel_in_bounds(dx, dy, dest_w, dest_h)) {
                continue;
            }

            // Map destination pixel to source pixel
            const int sx = (x * src_w) / target_w;
            const int sy = (y * src_h) / target_h;

            const int dest_idx = (dy * dest_w + dx) * RGBA_CHANNELS;
            const int src_idx = (sy * src_w + sx) * RGBA_CHANNELS;

            assert(dest_idx >= 0);
            assert(src_idx >= 0);
            assert(dest_size >= RGBA_CHANNELS);
            assert(src_size >= RGBA_CHANNELS);
            if ((size_t)dest_idx < dest_size-RGBA_CHANNELS && (size_t)src_idx < src_size-RGBA_CHANNELS) {
                // Only draw non-transparent pixels
                if (src[src_idx + 3] > THRESHOLD_ALPHA) {
                    drawing_copy_pixel(dest, src, dest_idx, src_idx, COPY_PIXEL_OPTION_NORMAL);
                }
            }
        }
    }
}

void draw_rect(uint8_t *dest, int width, int height, int x, int y, int w, int h, 
               uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
    for (int j = y; j < y + h; j++) {
        for (int i = x; i < x + w; i++) {
            if (!drawing_is_pixel_in_bounds(i, j, width, height)) {
                continue;
            }
            
            const int idx = (j * width + i) * RGBA_CHANNELS;
            dest[idx + 0] = b;
            dest[idx + 1] = g;
            dest[idx + 2] = r;
            dest[idx + 3] = a;
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
            if (ctx->anims[ctx->anim_index].digimon.sleep_2.pixels) {
                return DIGIMON_FRAME_SLEEP2;
            } else if (ctx->anims[ctx->anim_index].digimon.sleep1.pixels) {
                return DIGIMON_FRAME_SLEEP1;
            } else if (ctx->anims[ctx->anim_index].digimon.down1.pixels) {
                BONGOCAT_LOG_VERBOSE("No Sleeping Frame for %d", ctx->anim_index);
                // fallback frame
                return DIGIMON_FRAME_DOWN1;
            }
        } else if (current_frame == DIGIMON_FRAME_SLEEP2) {
            if (ctx->anims[ctx->anim_index].digimon.sleep1.pixels) {
                return DIGIMON_FRAME_SLEEP1;
            } else if (ctx->anims[ctx->anim_index].digimon.down1.pixels) {
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
                if (ctx->anims[ctx->anim_index].digimon.happy.pixels) {
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
            if (ctx->anims[ctx->anim_index].digimon.sleep1.pixels) {
                ctx->anim_frame_index = DIGIMON_FRAME_SLEEP1;
                return;
            }
            if (ctx->anims[ctx->anim_index].digimon.down1.pixels) {
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
            if (ctx->anims[ctx->anim_index].digimon.down1.pixels) {
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

// clean up image data loaded with stbi
static void anim_cleanup_loaded_images(animation_frame_t *anim_imgs, size_t count) {
    for (size_t i = 0; i < count; i++) {
        if (anim_imgs[i].pixels) {
            stbi_image_free(anim_imgs[i].pixels);
            anim_imgs[i].pixels = NULL;
        }
        anim_imgs[i].width = 0;
        anim_imgs[i].height = 0;
    }
}

// clean up image data allocated (copied)
static void anim_free_pixels(animation_frame_t *anim_imgs, size_t count) {
    for (size_t i = 0; i < count; i++) {
        if (anim_imgs[i].pixels) {
            BONGOCAT_SAFE_FREE(anim_imgs[i].pixels);
        }
        anim_imgs[i].width = 0;
        anim_imgs[i].height = 0;
    }
}

static bongocat_error_t anim_load_embedded_images(animation_frame_t *anim_imgs, size_t anim_imgs_count, const embedded_image_t *embedded_images, size_t embedded_images_count) {
    for (size_t i = 0; i < anim_imgs_count && i < embedded_images_count; i++) {
        const embedded_image_t *img = &embedded_images[i];
        
        BONGOCAT_LOG_DEBUG("Loading embedded image: %s", img->name);

        anim_imgs[i].channels = RGBA_CHANNELS;
        assert(img->size <= INT_MAX);
        anim_imgs[i].pixels = stbi_load_from_memory(img->data, (int)img->size,
                                                  &anim_imgs[i].width,
                                                  &anim_imgs[i].height,
                                                  NULL, anim_imgs[i].channels);
        if (!anim_imgs[i].pixels) {
            BONGOCAT_LOG_ERROR("Failed to load embedded image: %s", img->name);
            anim_cleanup_loaded_images(anim_imgs, i);
            return BONGOCAT_ERROR_FILE_IO;
        }
        
        BONGOCAT_LOG_DEBUG("Loaded %dx%d embedded image", anim_imgs[i].width, anim_imgs[i].height);
    }
    
    return BONGOCAT_SUCCESS;
}

static int anim_load_sprite_sheet(const config_t *config, animation_frame_t *anim_imgs, size_t anim_imgs_count, const embedded_image_t *sprite_sheet_image, int sprite_sheet_cols, int sprite_sheet_rows) {
    BONGOCAT_CHECK_NULL(config, -1);
    BONGOCAT_CHECK_NULL(anim_imgs, -1);
    BONGOCAT_CHECK_NULL(sprite_sheet_image, -1);

    if (sprite_sheet_cols < 0 || sprite_sheet_rows < 0) {
        return BONGOCAT_ERROR_INVALID_PARAM;
    }

    assert(sprite_sheet_image->size <= INT_MAX);

    int sprite_sheet_count = 0;
    const int result = load_sprite_sheet_from_memory(anim_imgs, anim_imgs_count,
                                  sprite_sheet_image->data, (int)sprite_sheet_image->size,
                                  sprite_sheet_cols, sprite_sheet_rows,
                                  &sprite_sheet_count,
                                  config->padding_x, config->padding_y,
                                  config->invert_color ? COPY_PIXEL_OPTION_INVERT : COPY_PIXEL_OPTION_NORMAL);
    if (result != 0) {
        BONGOCAT_LOG_ERROR("Sprite Sheet load failed: %s", sprite_sheet_image->name);
        return -1;
    }
    if (sprite_sheet_count <= 0) {
        BONGOCAT_LOG_ERROR("Sprite Sheet is empty: %s", sprite_sheet_image->name);
        return 0;
    }

    // assume every frame is the same size, pick first frame
    BONGOCAT_LOG_DEBUG("Loaded %dx%d sprite sheet with %d frames", anim_imgs[0].width, anim_imgs[0].height, sprite_sheet_count);

    return sprite_sheet_count;
}

#ifndef FEATURE_INCLUDE_ONLY_BONGOCAT_EMBEDDED_ASSETS
static bongocat_error_t init_digimon_anim(animation_context_t* ctx, int anim_index, const embedded_image_t* sprite_sheet_image, int sprite_sheet_cols, int sprite_sheet_rows) {
    const int sprite_sheet_count = anim_load_sprite_sheet(ctx->_local_copy_config, ctx->anims[anim_index].frames, MAX_NUM_FRAMES, sprite_sheet_image, sprite_sheet_cols, sprite_sheet_rows);
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
        for (size_t j = 0; j < MAX_DIGIMON_FRAMES; j++) {
            ctx->anims[i].frames[j] = empty_sprite_sheet_frame;
        }
    }
    
    // Initialize embedded images data
    const embedded_image_t* bongocat_embedded_images = init_bongocat_embedded_images();
    const int result = anim_load_embedded_images(ctx->anims[BONGOCAT_ANIM_INDEX].frames, MAX_NUM_FRAMES,
                                                 bongocat_embedded_images, BONGOCAT_EMBEDDED_IMAGES_COUNT);
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
    // free bongocat images loaded from stbi
    anim_cleanup_loaded_images(ctx->anims[BONGOCAT_ANIM_INDEX].frames, MAX_NUM_FRAMES);

#ifndef FEATURE_INCLUDE_ONLY_BONGOCAT_EMBEDDED_ASSETS
    // free allocated pixels (copied pixels), rest of animations
    assert(BONGOCAT_ANIM_INDEX == 0);
    for (size_t i = 1;i < ANIMS_COUNT; i++) {
        anim_free_pixels(ctx->anims[i].frames, MAX_NUM_FRAMES);
    }
#endif
    
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