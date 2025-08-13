#ifndef BONGOCAT_CONFIG_H
#define BONGOCAT_CONFIG_H

#include "core/bongocat.h"
#include "utils/error.h"
#include <cstdint>

enum class overlay_position_t : uint8_t {
    POSITION_TOP,
    POSITION_BOTTOM,
    /*
    POSITION_TOP_LEFT,
    POSITION_BOTTOM_LEFT,
    POSITION_TOP_RIGHT,
    POSITION_BOTTOM_RIGHT,
    */
};
inline static constexpr const char* POSITION_TOP_STR = "top";
inline static constexpr const char* POSITION_BOTTOM_STR = "bottom";

enum class layer_type_t : uint8_t {
    LAYER_TOP = 0,
    LAYER_OVERLAY = 1
};
inline static constexpr const char* LAYER_TOP_STR = "top";
inline static constexpr const char* LAYER_OVERLAY_STR = "overlay";

enum class align_type_t : int8_t {
    ALIGN_CENTER = 0,
    ALIGN_LEFT = -1,
    ALIGN_RIGHT = 1,
};
inline static constexpr const char* ALIGN_CENTER_STR = "center";
inline static constexpr const char* ALIGN_LEFT_STR = "left";
inline static constexpr const char* ALIGN_RIGHT_STR = "right";

struct config_time_t {
    int hour{0};
    int min{0};
};

struct config_t {
    int bar_height{0};
    char *output_name{NULL};
    char *keyboard_devices[MAX_INPUT_DEVICES];
    int num_keyboard_devices{0};
    int cat_x_offset{0};
    int cat_y_offset{0};
    int cat_height{0};
    int overlay_height{0};
    int idle_frame{0};
    int keypress_duration_ms{0};
    int test_animation_duration_ms{0};
    int test_animation_interval_sec{0};
    int fps{0};
    int overlay_opacity{0};
    int enable_debug{0};
    layer_type_t layer{layer_type_t::LAYER_TOP};
    overlay_position_t overlay_position{overlay_position_t::POSITION_TOP};

    int animation_index{0};
    int invert_color{0};
    int padding_x{0};
    int padding_y{0};

    int enable_scheduled_sleep{0};
    config_time_t sleep_begin;
    config_time_t sleep_end;
    int idle_sleep_timeout_sec{0};

    int happy_kpm{0};

    align_type_t cat_align{align_type_t::ALIGN_CENTER};
};

struct load_config_overwrite_parameters_t {
    const char* output_name;
};
bongocat_error_t load_config(config_t *config, const char *config_file_path, const load_config_overwrite_parameters_t *overwrite_parameters);
void config_cleanup(config_t *config);

void config_set_defaults(config_t *config);

#endif // CONFIG_H