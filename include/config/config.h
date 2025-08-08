#ifndef BONGOCAT_CONFIG_H
#define BONGOCAT_CONFIG_H

#include "utils/error.h"

typedef enum {
    POSITION_TOP,
    POSITION_BOTTOM,
    /*
    POSITION_TOP_LEFT,
    POSITION_BOTTOM_LEFT,
    POSITION_TOP_RIGHT,
    POSITION_BOTTOM_RIGHT,
    */
} overlay_position_t;
#define POSITION_TOP_STR "top"
#define POSITION_BOTTOM_STR "bottom"

typedef enum {
    LAYER_TOP = 0,
    LAYER_OVERLAY = 1
} layer_type_t;
#define LAYER_TOP_STR "top"
#define LAYER_OVERLAY_STR "overlay"

typedef enum {
    ALIGN_CENTER = 0,
    ALIGN_LEFT = -1,
    ALIGN_RIGHT = 1,
} align_type_t;
#define ALIGN_CENTER_STR "center"
#define ALIGN_LEFT_STR "left"
#define ALIGN_RIGHT_STR "right"

typedef struct {
    int hour;
    int min;
} config_time_t;

typedef struct {
    int bar_height;
    char *output_name;
    char **keyboard_devices;
    int num_keyboard_devices;
    int cat_x_offset;
    int cat_y_offset;
    int cat_height;
    int overlay_height;
    int idle_frame;
    int keypress_duration_ms;
    int test_animation_duration_ms;
    int test_animation_interval_sec;
    int fps;
    int overlay_opacity;
    int enable_debug;
    layer_type_t layer;
    overlay_position_t overlay_position;

    int animation_index;
    int invert_color;
    int padding_x;
    int padding_y;

    int enable_scheduled_sleep;
    config_time_t sleep_begin;
    config_time_t sleep_end;
    int idle_sleep_timeout_sec;

    int happy_kpm;

    align_type_t cat_align;
} config_t;

bongocat_error_t load_config(config_t *config, const char *config_file_path);
void config_cleanup(config_t *config);

void config_set_defaults(config_t *config);

#endif // CONFIG_H