#ifndef BONGOCAT_CONFIG_H
#define BONGOCAT_CONFIG_H

#include "core/bongocat.h"
#include "utils/error.h"
#include <cstdlib>
#include <cassert>
#include <cstring>

namespace bongocat::config {
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

    struct config_t;
    void config_free_keyboard_devices(config_t& config);
    void config_copy_keyboard_devices_from(config_t& config, const config_t& other);
    void cleanup(config_t& config);

    enum class config_animation_type_t : uint8_t {
        None,
        Bongocat,
        Digimon,
        MsPet,
    };

    struct config_t {
        char *output_name{nullptr};
        char *keyboard_devices[MAX_INPUT_DEVICES]{};
        int num_keyboard_devices{0};
        int cat_x_offset{0};
        int cat_y_offset{0};
        int cat_height{0};
        int overlay_height{0};
        int idle_frame{0};
        int keypress_duration_ms{0};
        int test_animation_duration_ms{0};
        int test_animation_interval_sec{0};
        int animation_speed_ms{0};
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

        config_animation_type_t animation_type{config_animation_type_t::None};
        int idle_animation{0};
        int input_fps{0};


        // Make Config movable and copyable
        config_t() {
            for (size_t i = 0; i < MAX_INPUT_DEVICES; ++i) {
                keyboard_devices[i] = nullptr;
            }
        }
        ~config_t() {
            cleanup(*this);
        }

        config_t(const config_t& other)
            : cat_x_offset(other.cat_x_offset),
              cat_y_offset(other.cat_y_offset),
              cat_height(other.cat_height),
              overlay_height(other.overlay_height),
              idle_frame(other.idle_frame),
              keypress_duration_ms(other.keypress_duration_ms),
              test_animation_duration_ms(other.test_animation_duration_ms),
              test_animation_interval_sec(other.test_animation_interval_sec),
              animation_speed_ms(other.animation_speed_ms),
              fps(other.fps),
              overlay_opacity(other.overlay_opacity),
              enable_debug(other.enable_debug),
              layer(other.layer),
              overlay_position(other.overlay_position),
              animation_index(other.animation_index),
              invert_color(other.invert_color),
              padding_x(other.padding_x),
              padding_y(other.padding_y),
              enable_scheduled_sleep(other.enable_scheduled_sleep),
              sleep_begin(other.sleep_begin),
              sleep_end(other.sleep_end),
              idle_sleep_timeout_sec(other.idle_sleep_timeout_sec),
              happy_kpm(other.happy_kpm),
              cat_align(other.cat_align),
              animation_type(other.animation_type),
              idle_animation(other.idle_animation),
              input_fps(other.input_fps)
        {
            output_name = other.output_name ? strdup(other.output_name) : nullptr;
            config_copy_keyboard_devices_from(*this, other);
        }

        config_t& operator=(const config_t& other) {
            if (this != &other) {
                cleanup(*this);

                cat_x_offset = other.cat_x_offset;
                cat_y_offset = other.cat_y_offset;
                cat_height = other.cat_height;
                overlay_height = other.overlay_height;
                idle_frame = other.idle_frame;
                keypress_duration_ms = other.keypress_duration_ms;
                test_animation_duration_ms = other.test_animation_duration_ms;
                test_animation_interval_sec = other.test_animation_interval_sec;
                animation_speed_ms = other.animation_speed_ms;
                fps = other.fps;
                overlay_opacity = other.overlay_opacity;
                enable_debug = other.enable_debug;
                layer = other.layer;
                overlay_position = other.overlay_position;
                animation_index = other.animation_index;
                invert_color = other.invert_color;
                padding_x = other.padding_x;
                padding_y = other.padding_y;
                enable_scheduled_sleep = other.enable_scheduled_sleep;
                sleep_begin = other.sleep_begin;
                sleep_end = other.sleep_end;
                idle_sleep_timeout_sec = other.idle_sleep_timeout_sec;
                happy_kpm = other.happy_kpm;
                cat_align = other.cat_align;
                animation_type = other.animation_type;
                idle_animation = other.idle_animation;
                input_fps = other.input_fps;

                output_name = other.output_name ? strdup(other.output_name) : nullptr;
                config_copy_keyboard_devices_from(*this, other);
            }
            return *this;
        }

        config_t(config_t&& other) noexcept
            : output_name(other.output_name),
              num_keyboard_devices(other.num_keyboard_devices),
              cat_x_offset(other.cat_x_offset),
              cat_y_offset(other.cat_y_offset),
              cat_height(other.cat_height),
              overlay_height(other.overlay_height),
              idle_frame(other.idle_frame),
              keypress_duration_ms(other.keypress_duration_ms),
              test_animation_duration_ms(other.test_animation_duration_ms),
              test_animation_interval_sec(other.test_animation_interval_sec),
              animation_speed_ms(other.animation_speed_ms),
              fps(other.fps),
              overlay_opacity(other.overlay_opacity),
              enable_debug(other.enable_debug),
              layer(other.layer),
              overlay_position(other.overlay_position),
              animation_index(other.animation_index),
              invert_color(other.invert_color),
              padding_x(other.padding_x),
              padding_y(other.padding_y),
              enable_scheduled_sleep(other.enable_scheduled_sleep),
              sleep_begin(other.sleep_begin),
              sleep_end(other.sleep_end),
              idle_sleep_timeout_sec(other.idle_sleep_timeout_sec),
              happy_kpm(other.happy_kpm),
              cat_align(other.cat_align),
              animation_type(other.animation_type),
              idle_animation(other.idle_animation),
              input_fps(other.input_fps)
        {
            for (int i = 0; i < num_keyboard_devices; ++i) {
                keyboard_devices[i] = other.keyboard_devices[i];
                other.keyboard_devices[i] = nullptr;
            }
            other.output_name = nullptr;
            other.num_keyboard_devices = 0;
        }

        config_t& operator=(config_t&& other) noexcept {
            if (this != &other) {
                cleanup(*this);

                output_name = other.output_name;
                num_keyboard_devices = other.num_keyboard_devices;
                cat_x_offset = other.cat_x_offset;
                cat_y_offset = other.cat_y_offset;
                cat_height = other.cat_height;
                overlay_height = other.overlay_height;
                idle_frame = other.idle_frame;
                keypress_duration_ms = other.keypress_duration_ms;
                test_animation_duration_ms = other.test_animation_duration_ms;
                test_animation_interval_sec = other.test_animation_interval_sec;
                animation_speed_ms = other.animation_speed_ms;
                fps = other.fps;
                overlay_opacity = other.overlay_opacity;
                enable_debug = other.enable_debug;
                layer = other.layer;
                overlay_position = other.overlay_position;
                animation_index = other.animation_index;
                invert_color = other.invert_color;
                padding_x = other.padding_x;
                padding_y = other.padding_y;
                enable_scheduled_sleep = other.enable_scheduled_sleep;
                sleep_begin = other.sleep_begin;
                sleep_end = other.sleep_end;
                idle_sleep_timeout_sec = other.idle_sleep_timeout_sec;
                happy_kpm = other.happy_kpm;
                cat_align = other.cat_align;
                animation_type = other.animation_type;
                idle_animation = other.idle_animation;
                input_fps = other.input_fps;

                for (int i = 0; i < num_keyboard_devices; ++i) {
                    keyboard_devices[i] = other.keyboard_devices[i];
                    other.keyboard_devices[i] = nullptr;
                }
                other.output_name = nullptr;
                other.num_keyboard_devices = 0;
            }
            return *this;
        }
    };
    inline void cleanup(config_t& config) {
        if (config.output_name) ::free(config.output_name);
        config.output_name = nullptr;
        config_free_keyboard_devices(config);
    }

    inline void config_free_keyboard_devices(config_t& config) {
        assert(config.num_keyboard_devices >= 0);
        for (size_t i = 0; i < static_cast<size_t>(config.num_keyboard_devices) && i < MAX_INPUT_DEVICES; i++) {
            if (config.keyboard_devices[i]) ::free(config.keyboard_devices[i]);
            config.keyboard_devices[i] = nullptr;
        }
        config.num_keyboard_devices = 0;
    }
    inline void config_copy_keyboard_devices_from(config_t& config, const config_t& other) {
        config_free_keyboard_devices(config);
        config.num_keyboard_devices = other.num_keyboard_devices;
        assert(config.num_keyboard_devices >= 0);
        for (size_t i = 0; i < static_cast<size_t>(config.num_keyboard_devices) && i < MAX_INPUT_DEVICES; i++) {
            config.keyboard_devices[i] = other.keyboard_devices[i] ? strdup(other.keyboard_devices[i]) : nullptr;
        }
    }

    struct load_config_overwrite_parameters_t {
        const char* output_name{nullptr};
    };
    created_result_t<config_t> load(const char *config_file_path, load_config_overwrite_parameters_t overwrite_parameters);
    void reset(config_t& config);

    void set_defaults(config_t& config);
}

#endif // BONGOCAT_CONFIG_H