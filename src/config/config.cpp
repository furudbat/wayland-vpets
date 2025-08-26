#include "config/config.h"
#include "core/bongocat.h"
#include "utils/error.h"
#include "graphics/animation_context.h"
#include "graphics/embedded_assets.h"
#include "graphics/embedded_assets/bongocat.hpp"
#include "graphics/embedded_assets/clippy.hpp"
#include <cassert>
#include <cctype>
#include <cstdio>
#include <cstdlib>



// =============================================================================
// CONFIGURATION CONSTANTS AND VALIDATION RANGES
// =============================================================================

namespace bongocat::config {
    static inline constexpr int MIN_CAT_HEIGHT = 10;
    static inline constexpr int MAX_CAT_HEIGHT = 200;
    static inline constexpr int MIN_OVERLAY_HEIGHT = 20;
    static inline constexpr int MAX_OVERLAY_HEIGHT = 300;
    static inline constexpr int MIN_FPS = 1;
    static inline constexpr int MAX_FPS = 144;
    static inline constexpr int MIN_DURATION_MS = 10;
    static inline constexpr int MAX_DURATION_MS = 5000;
    static inline constexpr int MAX_INTERVAL_SEC = 3600;
    static inline constexpr int MIN_TIMEOUT = 0;
    static inline constexpr int MAX_TIMEOUT = INT32_MAX;
    static inline constexpr int MIN_KPM = 0;
    static inline constexpr int MAX_KPM = 10000;

    static_assert(MIN_FPS > 0, "FPS cannot be zero, for math reasons");

    // Default settings
    static inline constexpr auto DEFAULT_DEVICE = "/dev/input/event4";
    static inline constexpr auto DEFAULT_CONFIG_FILE_PATH = "bongocat.conf";

    static inline constexpr int DEFAULT_CAT_X_OFFSET = 100;
    static inline constexpr int DEFAULT_CAT_Y_OFFSET = 10;
    static inline constexpr int DEFAULT_CAT_HEIGHT = 40;
    static inline constexpr int DEFAULT_OVERLAY_HEIGHT = 50;
    static inline constexpr int DEFAULT_IDLE_FRAME = 0;
    static inline constexpr platform::time_ms_t DEFAULT_KEYPRESS_DURATION_MS = 100;
    static inline constexpr int DEFAULT_FPS = 60;
    static inline constexpr int DEFAULT_OVERLAY_OPACITY = 60;
    static inline constexpr int DEFAULT_ANIMATION_INDEX = 0;
    static inline constexpr layer_type_t DEFAULT_LAYER = layer_type_t::LAYER_TOP;       // Requires enum or constant elsewhere
    static inline constexpr overlay_position_t DEFAULT_OVERLAY_POSITION = overlay_position_t::POSITION_TOP;
    static inline constexpr int DEFAULT_HAPPY_KPM = 0;
    static inline constexpr platform::time_sec_t DEFAULT_IDLE_SLEEP_TIMEOUT_SEC = 0;
    static inline constexpr align_type_t DEFAULT_CAT_ALIGN = align_type_t::ALIGN_CENTER;
    static inline constexpr platform::time_ms_t DEFAULT_TEST_ANIMATION_DURATION_MS = 0;
    static inline constexpr platform::time_sec_t DEFAULT_TEST_ANIMATION_INTERVAL_SEC = 0;

    // Debug-specific defaults
#ifndef NDEBUG
    static inline constexpr bool DEFAULT_ENABLE_DEBUG = true;
#else
    static inline constexpr bool DEFAULT_ENABLE_DEBUG = false;
#endif


    static inline constexpr auto CAT_X_OFFSET_KEY                   = "cat_x_offset";
    static inline constexpr auto CAT_Y_OFFSET_KEY                   = "cat_y_offset";
    static inline constexpr auto CAT_HEIGHT_KEY                     = "cat_height";
    static inline constexpr auto OVERLAY_HEIGHT_KEY                 = "overlay_height";
    static inline constexpr auto OVERLAY_POSITION_KEY               = "overlay_position";
    static inline constexpr auto ANIMATION_NAME_KEY                 = "animation_name";
    static inline constexpr auto INVERT_COLOR_KEY                   = "invert_color";
    static inline constexpr auto PADDING_X_KEY                      = "padding_x";
    static inline constexpr auto PADDING_Y_KEY                      = "padding_y";
    static inline constexpr auto IDLE_FRAME_KEY                     = "idle_frame";
    static inline constexpr auto ENABLE_SCHEDULED_SLEEP_KEY         = "enable_scheduled_sleep";
    static inline constexpr auto SLEEP_BEGIN_KEY                    = "sleep_begin";
    static inline constexpr auto SLEEP_END_KEY                      = "sleep_end";
    static inline constexpr auto IDLE_SLEEP_TIMEOUT_KEY             = "idle_sleep_timeout";
    static inline constexpr auto HAPPY_KPM_KEY                      = "happy_kpm";
    static inline constexpr auto KEYPRESS_DURATION_KEY              = "keypress_duration";
    static inline constexpr auto TEST_ANIMATION_DURATION_KEY        = "test_animation_duration";
    static inline constexpr auto TEST_ANIMATION_INTERVAL_KEY        = "test_animation_interval";
    static inline constexpr auto ANIMATION_SPEED_KEY                = "animation_speed";
    static inline constexpr auto FPS_KEY                            = "fps";
    static inline constexpr auto OVERLAY_OPACITY_KEY                = "overlay_opacity";
    static inline constexpr auto ENABLE_DEBUG_KEY                   = "enable_debug";
    static inline constexpr auto KEYBOARD_DEVICE_KEY                = "keyboard_device";
    static inline constexpr auto KEYBOARD_DEVICES_KEY               = "keyboard_devices";
    static inline constexpr auto ANIMATION_INDEX_KEY                = "animation_index";
    static inline constexpr auto LAYER_KEY                          = "layer";
    static inline constexpr auto CAT_ALIGN_KEY                      = "cat_align";
    static inline constexpr auto IDLE_ANIMATION_KEY                 = "idle_animation";
    static inline constexpr auto INPUT_FPS_KEY                      = "input_fps";

    static inline constexpr size_t VALUE_BUF = 256;
    static inline constexpr size_t LINE_BUF  = 512;

    static inline constexpr auto BONGOCAT_NAME = "bongocat";

    // =============================================================================
    // CONFIGURATION VALIDATION MODULE
    // =============================================================================

    static constexpr void config_clamp_int(int& value, int min, int max, [[maybe_unused]] const char *name) {
        if (value < min || value > max) {
            BONGOCAT_LOG_WARNING("%s %d out of range [%d-%d], clamping", name, value, min, max);
            value = (value < min) ? min : max;
        }
    }

    static void config_validate_dimensions(config_t& config) {
        config_clamp_int(config.cat_height, MIN_CAT_HEIGHT, MAX_CAT_HEIGHT, CAT_HEIGHT_KEY);
        config_clamp_int(config.overlay_height, MIN_OVERLAY_HEIGHT, MAX_OVERLAY_HEIGHT, OVERLAY_HEIGHT_KEY);
    }

    static void config_validate_timing(config_t& config) {
        config_clamp_int(config.fps, MIN_FPS, MAX_FPS, FPS_KEY);
        config_clamp_int(config.keypress_duration_ms, MIN_DURATION_MS, MAX_DURATION_MS, KEYPRESS_DURATION_KEY);
        config_clamp_int(config.test_animation_duration_ms, 0, MAX_DURATION_MS, TEST_ANIMATION_DURATION_KEY);
        config_clamp_int(config.animation_speed_ms, 0, MAX_DURATION_MS, TEST_ANIMATION_DURATION_KEY);
        config_clamp_int(config.idle_sleep_timeout_sec, 0, MAX_TIMEOUT, IDLE_SLEEP_TIMEOUT_KEY);
        config_clamp_int(config.input_fps, 0, MAX_FPS, INPUT_FPS_KEY);

        // Validate interval (0 is allowed to disable)
        if (config.test_animation_interval_sec < 0 || config.test_animation_interval_sec > MAX_INTERVAL_SEC) {
            BONGOCAT_LOG_WARNING("%s %d out of range [0-%dsec], clamping",
                                 TEST_ANIMATION_INTERVAL_KEY, config.test_animation_interval_sec, MAX_INTERVAL_SEC);
            config.test_animation_interval_sec = (config.test_animation_interval_sec < 0) ? 0 : MAX_INTERVAL_SEC;
        }
        if (config.animation_speed_ms < 0 || config.animation_speed_ms > MAX_INTERVAL_SEC*1000) {
            BONGOCAT_LOG_WARNING("%s %d out of range [0-%dms], clamping",
                                 ANIMATION_SPEED_KEY, config.test_animation_interval_sec, MAX_INTERVAL_SEC*1000);
            config.animation_speed_ms = (config.animation_speed_ms < 0) ? 0 : MAX_INTERVAL_SEC*1000;
        }
    }

    static void config_validate_kpm(config_t& config) {
        config_clamp_int(config.happy_kpm, MIN_KPM, MAX_KPM, HAPPY_KPM_KEY);
    }

    static void config_validate_appearance(config_t& config) {
        // Validate opacity
        config_clamp_int(config.overlay_opacity, 0, 255, OVERLAY_OPACITY_KEY);

        switch (config.animation_sprite_sheet_layout) {
            case config_animation_sprite_sheet_layout_t::None:
                BONGOCAT_LOG_WARNING("Cant determine sprite sheet layout");
                break;
            case config_animation_sprite_sheet_layout_t::Bongocat:
#ifdef FEATURE_BONGOCAT_EMBEDDED_ASSETS
                // Validate animation index
                assert(assets::BONGOCAT_ANIMATIONS_COUNT <= INT_MAX);
                if (config.animation_index < 0 || config.animation_index >= static_cast<int>(assets::BONGOCAT_ANIMATIONS_COUNT)) {
                    BONGOCAT_LOG_WARNING("%s %d out of range [0-%d], resetting to 0",
                                         ANIMATION_INDEX_KEY, config.animation_index, assets::BONGOCAT_ANIMATIONS_COUNT - 1);
                    config.animation_index = 0;
                }
                // Validate idle frame
                assert(animation::BONGOCAT_NUM_FRAMES <= INT_MAX);
                if (config.idle_frame < 0 || config.idle_frame >= static_cast<int>(animation::BONGOCAT_NUM_FRAMES)) {
                    BONGOCAT_LOG_WARNING("%s %d out of range [0-%d], resetting to 0",
                                         IDLE_FRAME_KEY, config.idle_frame, animation::BONGOCAT_NUM_FRAMES - 1);
                    config.idle_frame = 0;
                }
#endif
                break;
            case config_animation_sprite_sheet_layout_t::Dm:
#ifdef FEATURE_ENABLE_DM_EMBEDDED_ASSETS
                // Validate animation index
                assert(assets::DM_ANIMATIONS_COUNT <= INT_MAX);
                if (config.animation_index < 0 || config.animation_index >= static_cast<int>(assets::DM_ANIMATIONS_COUNT)) {
                    BONGOCAT_LOG_WARNING("%s %d out of range [0-%d], resetting to 0",
                                         ANIMATION_INDEX_KEY, config.animation_index, assets::DM_ANIMATIONS_COUNT - 1);
                    config.animation_index = 0;
                }
                // Validate idle frame
                assert(animation::MAX_DIGIMON_FRAMES <= INT_MAX);
                if (config.idle_frame < 0 || config.idle_frame >= static_cast<int>(animation::MAX_DIGIMON_FRAMES)) {
                    BONGOCAT_LOG_WARNING("%s %d out of range [0-%d], resetting to 0",
                                         IDLE_FRAME_KEY, config.idle_frame, animation::MAX_DIGIMON_FRAMES - 1);
                    config.idle_frame = 0;
                }
#endif
                break;
            case config_animation_sprite_sheet_layout_t::MsAgent:
#ifdef FEATURE_MS_AGENT_EMBEDDED_ASSETS
                // Validate animation index
                assert(assets::MS_AGENTS_ANIMATIONS_COUNT <= INT_MAX);
                if (config.animation_index < 0 || config.animation_index >= static_cast<int>(assets::MS_AGENTS_ANIMATIONS_COUNT)) {
                    BONGOCAT_LOG_WARNING("%s %d out of range [0-%d], resetting to 0",
                                         ANIMATION_INDEX_KEY, config.animation_index, assets::MS_AGENTS_ANIMATIONS_COUNT - 1);
                    config.animation_index = 0;
                }
                // Validate idle frame
                assert(assets::CLIPPY_FRAMES_IDLE <= INT_MAX);
                if (config.idle_frame < 0 || config.idle_frame >= static_cast<int>(assets::CLIPPY_FRAMES_IDLE)) {
                    BONGOCAT_LOG_WARNING("%s %d out of range [0-%d], resetting to 0",
                                         IDLE_FRAME_KEY, config.idle_frame, assets::CLIPPY_FRAMES_IDLE - 1);
                    config.idle_frame = 0;
                }
#endif
                break;
        }
    }

    static void config_validate_enums(config_t& config) {
        // Validate layer
        if (config.layer != layer_type_t::LAYER_TOP && config.layer != layer_type_t::LAYER_OVERLAY) {
            BONGOCAT_LOG_WARNING("Invalid layer %d, resetting to top", config.layer);
            config.layer = layer_type_t::LAYER_TOP;
        }

        // Validate overlay_position
        if (config.overlay_position != overlay_position_t::POSITION_TOP && config.overlay_position != overlay_position_t::POSITION_BOTTOM) {
            BONGOCAT_LOG_WARNING("Invalid %s %d, resetting to top", OVERLAY_OPACITY_KEY, config.overlay_position);
            config.overlay_position = overlay_position_t::POSITION_TOP;
        }

        // Validate cat_align
        if (config.cat_align != align_type_t::ALIGN_CENTER && config.cat_align != align_type_t::ALIGN_LEFT && config.cat_align != align_type_t::ALIGN_RIGHT) {
            BONGOCAT_LOG_WARNING("Invalid %s %d, resetting to center", CAT_ALIGN_KEY, config.cat_align);
            config.cat_align = align_type_t::ALIGN_CENTER;
        }
    }

    static void config_validate_time(config_t& config) {
        if (config.enable_scheduled_sleep) {
            const int begin_minutes = config.sleep_begin.hour * 60 + config.sleep_begin.min;
            const int end_minutes = config.sleep_end.hour * 60 + config.sleep_end.min;

            if (begin_minutes == end_minutes) {
                BONGOCAT_LOG_WARNING("Sleep mode is enabled, but time is equal: %02d:%02d, disable sleep mode", config.sleep_begin.hour, config.sleep_begin.min);

                config.enable_scheduled_sleep = 0;
                //config.sleep_begin.hour = 0;
                //config.sleep_begin.min = 0;
                //config.sleep_end.hour = 0;
                //config.sleep_end.min = 0;
            }
        }
    }

    static bongocat_error_t config_validate(config_t& config) {
        // Normalize boolean values
        config.enable_debug = config.enable_debug ? 1 : 0;
        config.invert_color = config.invert_color ? 1 : 0;
        config.idle_animation = config.idle_animation ? 1 : 0;
        config.enable_scheduled_sleep = config.enable_scheduled_sleep ? 1 : 0;

        config_validate_dimensions(config);
        config_validate_timing(config);
        config_validate_appearance(config);
        config_validate_enums(config);
        config_validate_time(config);
        config_validate_kpm(config);

        return bongocat_error_t::BONGOCAT_SUCCESS;
    }

    // =============================================================================
    // DEVICE MANAGEMENT MODULE
    // =============================================================================

    static bongocat_error_t config_add_keyboard_device(config_t& config, const char *device_path) {
        BONGOCAT_CHECK_NULL(device_path, bongocat_error_t::BONGOCAT_ERROR_INVALID_PARAM);

        assert(config.num_keyboard_devices >= 0 && config.num_keyboard_devices < INT_MAX-1);

        const int old_num_keyboard_devices = config.num_keyboard_devices;

        assert(MAX_INPUT_DEVICES <= INT_MAX);
        if (old_num_keyboard_devices >= static_cast<int>(MAX_INPUT_DEVICES)) {
            BONGOCAT_LOG_WARNING("Can not add more devices from config, max. reach: %d", MAX_INPUT_DEVICES);
            return bongocat_error_t::BONGOCAT_SUCCESS;
        }
        const int new_num_keyboard_devices = old_num_keyboard_devices + 1;
        assert(new_num_keyboard_devices >= 0);
        assert(static_cast<size_t>(new_num_keyboard_devices) <= MAX_INPUT_DEVICES);

        // Add new device path
        config.keyboard_devices[old_num_keyboard_devices] = strdup(device_path);
        if (!config.keyboard_devices[old_num_keyboard_devices]) {
            // free new copied strings
            for (int i = 0; i < old_num_keyboard_devices; i++) {
                if (config.keyboard_devices[i]) ::free(config.keyboard_devices[i]);
                config.keyboard_devices[i] = nullptr;
            }
            config.num_keyboard_devices = old_num_keyboard_devices;
            BONGOCAT_LOG_ERROR("Failed to copy new keyboard device path");
            return bongocat_error_t::BONGOCAT_ERROR_MEMORY;
        }

        // update new size
        config.num_keyboard_devices = new_num_keyboard_devices;

        return bongocat_error_t::BONGOCAT_SUCCESS;
    }

    static void config_cleanup_devices(config_t& config) {
        assert(config.num_keyboard_devices >= 0);
        for (size_t i = 0; i < MAX_INPUT_DEVICES; i++) {
            if (i < static_cast<size_t>(config.num_keyboard_devices)) {
                if (config.keyboard_devices[i]) ::free(config.keyboard_devices[i]);
            }
            config.keyboard_devices[i] = nullptr;
        }
        config.num_keyboard_devices = 0;
    }

    // =============================================================================
    // CONFIGURATION PARSING MODULE
    // =============================================================================

    static char* config_trim_key(char *key) {
        char *key_start = key;
        while (*key_start == ' ' || *key_start == '\t') key_start++;

        char *key_end = key_start + strlen(key_start) - 1;
        while (key_end > key_start && (*key_end == ' ' || *key_end == '\t')) {
            *key_end = '\0';
            key_end--;
        }

        return key_start;
    }

    static bongocat_error_t config_parse_integer_key(config_t& config, const char *key, const char *value) {
        const int int_value = static_cast<int>(strtol(value, nullptr, 10));

        if (strcmp(key, CAT_X_OFFSET_KEY) == 0) {
            config.cat_x_offset = int_value;
        } else if (strcmp(key, CAT_Y_OFFSET_KEY) == 0) {
            config.cat_y_offset = int_value;
        } else if (strcmp(key, CAT_HEIGHT_KEY) == 0) {
            config.cat_height = int_value;
        } else if (strcmp(key, OVERLAY_HEIGHT_KEY) == 0) {
            config.overlay_height = int_value;
        } else if (strcmp(key, IDLE_FRAME_KEY) == 0) {
            config.idle_frame = int_value;
        } else if (strcmp(key, KEYPRESS_DURATION_KEY) == 0) {
            config.keypress_duration_ms = int_value;
        } else if (strcmp(key, TEST_ANIMATION_DURATION_KEY) == 0) {
            config.test_animation_duration_ms = int_value;
        } else if (strcmp(key, TEST_ANIMATION_INTERVAL_KEY) == 0) {
            config.test_animation_interval_sec = int_value;
        } else if (strcmp(key, FPS_KEY) == 0) {
            config.fps = int_value;
        } else if (strcmp(key, OVERLAY_OPACITY_KEY) == 0) {
            config.overlay_opacity = int_value;
        } else if (strcmp(key, ENABLE_DEBUG_KEY) == 0) {
            config.enable_debug = int_value;
        } else if (strcmp(key, ANIMATION_INDEX_KEY) == 0) {
            config.animation_index = int_value;
        } else if (strcmp(key, INVERT_COLOR_KEY) == 0) {
            config.invert_color = int_value;
        } else if (strcmp(key, PADDING_X_KEY) == 0) {
            config.padding_x = int_value;
        } else if (strcmp(key, PADDING_Y_KEY) == 0) {
            config.padding_y = int_value;
        } else if (strcmp(key, ENABLE_SCHEDULED_SLEEP_KEY) == 0) {
            config.enable_scheduled_sleep = int_value;
        } else if (strcmp(key, IDLE_SLEEP_TIMEOUT_KEY) == 0) {
            config.idle_sleep_timeout_sec = int_value;
        } else if (strcmp(key, HAPPY_KPM_KEY) == 0) {
            config.happy_kpm = int_value;
        } else if (strcmp(key, ANIMATION_SPEED_KEY) == 0) {
            config.animation_speed_ms = int_value;
        } else if (strcmp(key, IDLE_ANIMATION_KEY) == 0) {
            config.idle_animation = int_value;
        } else if (strcmp(key, INPUT_FPS_KEY) == 0) {
            config.input_fps = int_value;
        } else {
            return bongocat_error_t::BONGOCAT_ERROR_INVALID_PARAM; // Unknown key
        }

        return bongocat_error_t::BONGOCAT_SUCCESS;
    }

    static bongocat_error_t config_parse_enum_key(config_t& config, const char *key, const char *value) {
        if (strcmp(key, LAYER_KEY) == 0) {
            if (strcmp(value, LAYER_TOP_STR) == 0) {
                config.layer = layer_type_t::LAYER_TOP;
            } else if (strcmp(value, LAYER_OVERLAY_STR) == 0) {
                config.layer = layer_type_t::LAYER_OVERLAY;
            } else {
                BONGOCAT_LOG_WARNING("Invalid %s '%s', using 'top'", LAYER_KEY, value);
                config.layer = layer_type_t::LAYER_TOP;
            }
        } else if (strcmp(key, OVERLAY_POSITION_KEY) == 0) {
            if (strcmp(value, POSITION_TOP_STR) == 0) {
                config.overlay_position = overlay_position_t::POSITION_TOP;
            } else if (strcmp(value, POSITION_BOTTOM_STR) == 0) {
                config.overlay_position = overlay_position_t::POSITION_BOTTOM;
            } else {
                BONGOCAT_LOG_WARNING("Invalid %s '%s', using 'top'", OVERLAY_POSITION_KEY, value);
                config.overlay_position = overlay_position_t::POSITION_TOP;
            }
        } else if (strcmp(key, CAT_ALIGN_KEY) == 0) {
            if (strcmp(value, ALIGN_CENTER_STR) == 0) {
                config.cat_align = align_type_t::ALIGN_CENTER;
            } else if (strcmp(value, ALIGN_LEFT_STR) == 0) {
                config.cat_align = align_type_t::ALIGN_LEFT;
            } else if (strcmp(value, ALIGN_RIGHT_STR) == 0) {
                config.cat_align = align_type_t::ALIGN_RIGHT;
            } else {
                BONGOCAT_LOG_WARNING("Invalid %s '%s', using 'center'", CAT_ALIGN_KEY, value);
                config.cat_align = align_type_t::ALIGN_CENTER;
            }
        } else {
            return bongocat_error_t::BONGOCAT_ERROR_INVALID_PARAM; // Unknown key
        }

        return bongocat_error_t::BONGOCAT_SUCCESS;
    }


    bongocat_error_t config_parse_time(const char *value, int& hour, int& min) {
        char *endptr = nullptr;
        errno = 0;

        // Parse hour
        const long h = strtol(value, &endptr, 10);
        if (endptr == value || *endptr != ':' || errno == ERANGE || h < 0 || h > 23) {
            return bongocat_error_t::BONGOCAT_ERROR_INVALID_PARAM;
        }

        // Parse minute
        value = endptr + 1; // skip ':'
        errno = 0;
        const long m = strtol(value, &endptr, 10);
        if (endptr == value || *endptr != '\0' || errno == ERANGE || m < 0 || m > 59) {
            return bongocat_error_t::BONGOCAT_ERROR_INVALID_PARAM;
        }

        hour = static_cast<int>(h);
        min = static_cast<int>(m);
        return bongocat_error_t::BONGOCAT_SUCCESS;
    }
    static bongocat_error_t config_parse_string(config_t& config, const char *key, const char *value) {
        using namespace assets;
        if (strcmp(key, "monitor") == 0) {
            if (config.output_name) {
                ::free(config.output_name);
                config.output_name = nullptr;
            }
            if (value && value[0] != '\0') {
                config.output_name = strdup(value);
                if (!config.output_name) {
                    BONGOCAT_LOG_ERROR("Failed to allocate memory for interface output");
                    return bongocat_error_t::BONGOCAT_ERROR_MEMORY;
                }
            } else {
                config.output_name = nullptr;
            }
        } else if (strcmp(key, SLEEP_BEGIN_KEY) == 0) {
            if (value && value[0] != '\0') {
                int hour{0};
                int min{0};
                if (config_parse_time(value, hour, min) != bongocat_error_t::BONGOCAT_SUCCESS) {
                    return bongocat_error_t::BONGOCAT_ERROR_INVALID_PARAM; // Invalid time format
                }
                if (hour < 0 || hour > 23 || min < 0 || min > 59) {
                    return bongocat_error_t::BONGOCAT_ERROR_INVALID_PARAM; // Invalid time format
                }

                config.sleep_begin.hour = hour;
                config.sleep_begin.min = min;
            } else {
                config.sleep_begin.hour = 0;
                config.sleep_begin.min = 0;
            }
        } else if (strcmp(key, SLEEP_END_KEY) == 0) {
            if (value && value[0] != '\0') {
                int hour{0};
                int min{0};
                if (config_parse_time(value, hour, min) != bongocat_error_t::BONGOCAT_SUCCESS) {
                    return bongocat_error_t::BONGOCAT_ERROR_INVALID_PARAM; // Invalid time format
                }
                if (hour < 0 || hour > 23 || min < 0 || min > 59) {
                    return bongocat_error_t::BONGOCAT_ERROR_INVALID_PARAM; // Invalid time format
                }

                config.sleep_end.hour = hour;
                config.sleep_end.min = min;
            } else {
                config.sleep_end.hour = 0;
                config.sleep_end.min = 0;
            }
        } else if (strcmp(key, ANIMATION_NAME_KEY) == 0) {
            char lower_value[VALUE_BUF] = {};
            memset(lower_value, 0, VALUE_BUF);
            for(size_t i = 0; i < strlen(value) && i < VALUE_BUF; i++) {
                lower_value[i] = value ? static_cast<char>(tolower(value[i])) : '\0';
            }

            config.animation_sprite_sheet_layout = config_animation_sprite_sheet_layout_t::None;
            config.animation_index = -1;

#ifdef FEATURE_BONGOCAT_EMBEDDED_ASSETS
            // check for bongocat
            if (strcmp(lower_value, BONGOCAT_NAME) == 0) {
                config.animation_index = BONGOCAT_ANIM_INDEX;
                config.animation_sprite_sheet_layout = config_animation_sprite_sheet_layout_t::Bongocat;
            }
#endif

            // check for dm
#ifdef FEATURE_ENABLE_DM_EMBEDDED_ASSETS
#ifdef FEATURE_MIN_DM_EMBEDDED_ASSETS
            //if (strcmp(lower_value, "agumon") == 0) {
            //    config->animation_index = DM_AGUMON_ANIM_INDEX;
            //}
#include "../graphics/embedded_assets/min_dm_config_parse_enum_key.cpp.inl"
#endif
#ifdef FEATURE_DM_EMBEDDED_ASSETS
#include "../graphics/embedded_assets/dm_config_parse_enum_key.cpp.inl"
#endif
#ifdef FEATURE_DM20_EMBEDDED_ASSETS
#include "../graphics/embedded_assets/dm20_config_parse_enum_key.cpp.inl"
#endif
#ifdef FEATURE_PEN20_EMBEDDED_ASSETS
#include "../graphics/embedded_assets/pen20_config_parse_enum_key.cpp.inl"
#endif
#ifdef FEATURE_DMX_EMBEDDED_ASSETS
#include "../graphics/embedded_assets/dmx_config_parse_enum_key.cpp.inl"
#endif
#ifdef FEATURE_DMC_EMBEDDED_ASSETS
#include "../graphics/embedded_assets/dmc_config_parse_enum_key.cpp.inl"
#endif
            /// @NOTE(config): add more dm versions here

            // assume animation type is not set yet, but index got set/overwritten above
            if (config.animation_index >= 0 && config.animation_sprite_sheet_layout == config_animation_sprite_sheet_layout_t::None) {
                config.animation_sprite_sheet_layout = config_animation_sprite_sheet_layout_t::Dm;
            }
#endif

            // check for ms pets (clippy)
#ifdef FEATURE_MS_AGENT_EMBEDDED_ASSETS
            if (strcmp(lower_value, "clippy") == 0) {
                config.animation_index = CLIPPY_ANIM_INDEX;
                config.animation_sprite_sheet_layout = config_animation_sprite_sheet_layout_t::MsAgent;
            }
            /// @NOTE(config): add more MS Pets here
#endif

            if (config.animation_index < 0 || config.animation_sprite_sheet_layout == config_animation_sprite_sheet_layout_t::None) {
                if (config.animation_index >= 0 && config.animation_sprite_sheet_layout == config_animation_sprite_sheet_layout_t::None) {
                    BONGOCAT_LOG_WARNING("animation_index is set, but not animation_type (unknown type for index=%i and value='%s')", config.animation_index, value);
                }
                BONGOCAT_LOG_WARNING("Invalid %s '%s', using '%s'", ANIMATION_NAME_KEY, value, BONGOCAT_NAME);
                config.animation_index = BONGOCAT_ANIM_INDEX;
                config.animation_sprite_sheet_layout = config_animation_sprite_sheet_layout_t::Bongocat;
            }
        } else {
            return bongocat_error_t::BONGOCAT_ERROR_INVALID_PARAM; // Unknown key
        }

        return bongocat_error_t::BONGOCAT_SUCCESS;
    }

    static bongocat_error_t config_parse_key_value(config_t& config, const char *key, const char *value) {
        // Try integer keys first
        if (config_parse_integer_key(config, key, value) == bongocat_error_t::BONGOCAT_SUCCESS) {
            return bongocat_error_t::BONGOCAT_SUCCESS;
        }

        // Try enum keys
        if (config_parse_enum_key(config, key, value) == bongocat_error_t::BONGOCAT_SUCCESS) {
            return bongocat_error_t::BONGOCAT_SUCCESS;
        }

        // Try string
        if (config_parse_string(config, key, value) == bongocat_error_t::BONGOCAT_SUCCESS) {
            return bongocat_error_t::BONGOCAT_SUCCESS;
        }

        // Handle device keys
        if (strcmp(key, KEYBOARD_DEVICE_KEY) == 0 || strcmp(key, KEYBOARD_DEVICES_KEY) == 0) {
            return config_add_keyboard_device(config, value);
        }

        // Unknown key
        return bongocat_error_t::BONGOCAT_ERROR_INVALID_PARAM;
    }

    static bool config_is_comment_or_empty(const char *line) {
        return (line[0] == '#' || line[0] == '\0' || strspn(line, " \t") == strlen(line));
    }

    static bongocat_error_t config_parse_file(config_t& config, const char *config_file_path) {
        const char *file_path = config_file_path ? config_file_path : DEFAULT_CONFIG_FILE_PATH;

        FILE *file = fopen(file_path, "r");
        if (!file) {
            BONGOCAT_LOG_INFO("Config file '%s' not found, using defaults", file_path);
            return bongocat_error_t::BONGOCAT_SUCCESS;
        }

        char line[LINE_BUF] = {0};
        char key[VALUE_BUF] = {0};
        char value[VALUE_BUF] = {0};
        int line_number = 0;
        bongocat_error_t result = bongocat_error_t::BONGOCAT_SUCCESS;

        while (fgets(line, sizeof(line), file)) {
            line_number++;

            // Remove trailing newline
            size_t len = strlen(line);
            if (len > 0 && line[len - 1] == '\n') {
                line[len - 1] = '\0';
            }

            // Skip comments and empty lines
            if (config_is_comment_or_empty(line)) {
                continue;
            }

            // Parse key=value pairs
            static_assert(255 < VALUE_BUF);
            if (sscanf(line, " %255[^=] = %255s", key, value) == 2) {
                char *trimmed_key = config_trim_key(key);

                bongocat_error_t parse_result = config_parse_key_value(config, trimmed_key, value);
                if (parse_result == bongocat_error_t::BONGOCAT_ERROR_INVALID_PARAM) {
                    BONGOCAT_LOG_WARNING("Unknown configuration key '%s' at line %d", trimmed_key, line_number);
                } else if (parse_result != bongocat_error_t::BONGOCAT_SUCCESS) {
                    result = parse_result;
                    break;
                }
            } else if (strlen(line) > 0) {
                BONGOCAT_LOG_WARNING("Invalid configuration line %d: %s", line_number, line);
            }
        }

        fclose(file);

        if (result == bongocat_error_t::BONGOCAT_SUCCESS) {
            BONGOCAT_LOG_INFO("Loaded configuration from %s", file_path);
        }

        return result;
    }

    // =============================================================================
    // DEFAULT CONFIGURATION MODULE
    // =============================================================================

    void set_defaults(config_t& config) {
        config_t cfg;

        cfg.output_name = nullptr;
        assert(MAX_INPUT_DEVICES <= INT_MAX);
        for (int i = 0; i < static_cast<int>(MAX_INPUT_DEVICES); i++) {
            cfg.keyboard_devices[i] = nullptr;
        }
        cfg.num_keyboard_devices = 0;
        cfg.cat_x_offset = DEFAULT_CAT_X_OFFSET;
        cfg.cat_y_offset = DEFAULT_CAT_Y_OFFSET;
        cfg.cat_height = DEFAULT_CAT_HEIGHT;
        cfg.overlay_height = DEFAULT_OVERLAY_HEIGHT;
        cfg.idle_frame = DEFAULT_IDLE_FRAME;
        cfg.keypress_duration_ms = DEFAULT_KEYPRESS_DURATION_MS;
        cfg.test_animation_duration_ms = DEFAULT_TEST_ANIMATION_DURATION_MS;
        cfg.test_animation_interval_sec = DEFAULT_TEST_ANIMATION_INTERVAL_SEC;
        cfg.fps = DEFAULT_FPS;
        cfg.overlay_opacity = DEFAULT_OVERLAY_OPACITY;
        cfg.enable_debug = DEFAULT_ENABLE_DEBUG;
        cfg.layer = DEFAULT_LAYER;
        cfg.overlay_position = DEFAULT_OVERLAY_POSITION;
        cfg.animation_index = DEFAULT_ANIMATION_INDEX;
        cfg.invert_color = 0;
        cfg.padding_x = 0;
        cfg.padding_y = 0;
        cfg.enable_scheduled_sleep = 0;
        cfg.sleep_begin = {};
        cfg.sleep_end = {};
        cfg.idle_sleep_timeout_sec = DEFAULT_IDLE_SLEEP_TIMEOUT_SEC;
        cfg.happy_kpm = DEFAULT_HAPPY_KPM;
        cfg.cat_align = DEFAULT_CAT_ALIGN;
        cfg.animation_sprite_sheet_layout = config_animation_sprite_sheet_layout_t::Bongocat;
        cfg.idle_animation = 0;
        cfg.input_fps = 0;          // when 0 fallback to fps

        config = bongocat::move(cfg);
    }

    static bongocat_error_t config_set_default_devices(config_t& config) {
        if (config.num_keyboard_devices == 0) {
            return config_add_keyboard_device(config, DEFAULT_DEVICE);
        }

        return bongocat_error_t::BONGOCAT_SUCCESS;
    }

    static void config_log_summary(const config_t& config) {
        using namespace assets;
        BONGOCAT_LOG_DEBUG("Configuration loaded successfully");
        BONGOCAT_LOG_DEBUG("  Overlay Height: %dpx", config.overlay_height);
        switch (config.animation_sprite_sheet_layout) {
            case config_animation_sprite_sheet_layout_t::None:
                break;
            case config_animation_sprite_sheet_layout_t::Bongocat:
                BONGOCAT_LOG_DEBUG("  Cat: %dx%d at offset (%d,%d)",
                                  config.cat_height, (config.cat_height * BONGOCAT_FRAME_WIDTH) / BONGOCAT_FRAME_HEIGHT,
                                  config.cat_x_offset, config.cat_y_offset);
                break;
            case config_animation_sprite_sheet_layout_t::Dm:
                BONGOCAT_LOG_DEBUG("  dm: %03d/%d at offset (%d,%d)",
                                  config.animation_index, DM_ANIMATIONS_COUNT,
                                  config.cat_x_offset, config.cat_y_offset);
                break;
            case config_animation_sprite_sheet_layout_t::MsAgent:
                BONGOCAT_LOG_DEBUG("  MS Agent: %02d at offset (%d,%d)",
                                  config.animation_index,
                                  config.cat_x_offset, config.cat_y_offset);
                break;
        }
        BONGOCAT_LOG_DEBUG("  FPS: %d, Opacity: %d", config.fps, config.overlay_opacity);
        BONGOCAT_LOG_DEBUG("  Position: %s", config.overlay_position == overlay_position_t::POSITION_TOP ? "top" : "bottom");
        BONGOCAT_LOG_DEBUG("  Alignment: %d", config.cat_align, config.cat_align == align_type_t::ALIGN_CENTER ? "(center)" : "");
        BONGOCAT_LOG_DEBUG("  Layer: %s", config.layer == layer_type_t::LAYER_TOP ? "top" : "overlay");
        BONGOCAT_LOG_DEBUG("  Output Screen: %s", config.output_name);
    }

    // =============================================================================
    // PUBLIC API IMPLEMENTATION
    // =============================================================================

    created_result_t<config_t> load(const char *config_file_path, load_config_overwrite_parameters_t overwrite_parameters) {
        config_t ret;
        set_defaults(ret);

        // Parse config file and override defaults
        bongocat_error_t result = config_parse_file(ret, config_file_path);
        if (result != bongocat_error_t::BONGOCAT_SUCCESS) {
            BONGOCAT_LOG_ERROR("Failed to parse configuration file: %s", bongocat::error_string(result));
            return result;
        }
        if (overwrite_parameters.output_name) {
            if (ret.output_name) ::free(ret.output_name);
            ret.output_name = strdup(overwrite_parameters.output_name);
        }
        if (ret.input_fps <= 0) {
            ret.input_fps = ret.fps;
        }

        // Set default keyboard device if none specified
        if (ret.num_keyboard_devices == 0) {
            result = config_set_default_devices(ret);
            if (result != bongocat_error_t::BONGOCAT_SUCCESS) {
                BONGOCAT_LOG_ERROR("Failed to set default keyboard devices: %s", bongocat::error_string(result));
                return result;
            }
        }

        // Validate and sanitize configuration
        result = config_validate(ret);
        if (result != bongocat_error_t::BONGOCAT_SUCCESS) {
            BONGOCAT_LOG_ERROR("Configuration validation failed: %s", bongocat::error_string(result));
            return result;
        }

        if (ret.num_keyboard_devices == 0) {
            // Set default keyboard device if none specified
            result = config_set_default_devices(ret);
            if (result != bongocat_error_t::BONGOCAT_SUCCESS) {
                BONGOCAT_LOG_ERROR("Failed to set default keyboard devices: %s", bongocat::error_string(result));
                return result;
            } else {
                BONGOCAT_LOG_INFO("No device loaded, use default keyboard device: %s", DEFAULT_DEVICE);
            }
        }

#ifndef NDEBUG
        // Add stdin as an extra debug input device
        config_add_keyboard_device(ret, "/dev/stdin");
        BONGOCAT_LOG_INFO("Add stdin for debugging: %s", "/dev/stdin");
#endif

        // Log configuration summary
        config_log_summary(ret);

        return ret;
    }

    void reset(config_t& config) {
        config_cleanup_devices(config);
        set_defaults(config);
    }
}