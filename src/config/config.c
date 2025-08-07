#define _POSIX_C_SOURCE 200809L
#include "config/config.h"
#include "utils/error.h"
#include "utils/memory.h"
#include "graphics/context.h"
#include "graphics/embedded_assets/bongocat.h"
#include "graphics/embedded_assets.h"
#include <assert.h>
#include <ctype.h>
#include <limits.h>

// =============================================================================
// CONFIGURATION CONSTANTS AND VALIDATION RANGES
// =============================================================================

#define MIN_CAT_HEIGHT 10
#define MAX_CAT_HEIGHT 200
#define MIN_OVERLAY_HEIGHT 20
#define MAX_OVERLAY_HEIGHT 300
#define MIN_FPS 1
#define MAX_FPS 144
#define MIN_DURATION 10
#define MAX_DURATION 5000
#define MAX_INTERVAL 3600
#define MIN_TIMEOUT 0
#define MAX_TIMEOUT INT32_MAX
#define MIN_KPM 0
#define MAX_KPM 10000
static_assert(MIN_FPS > 0, "FPS can not be zero, for math reasons");

#define DEFAULT_DEVICE "/dev/input/event4"
#define DEFAULT_CONFIG_FILE_PATH "bongocat.conf"

#define DEFAULT_CAT_X_OFFSET 100
#define DEFAULT_CAT_Y_OFFSET 10
#define DEFAULT_CAT_HEIGHT 40
#define DEFAULT_OVERLAY_HEIGHT 50
#define DEFAULT_IDLE_FRAME 0
#define DEFAULT_KEYPRESS_DURATION_MS 100
#define DEFAULT_FPS 60
#define DEFAULT_OVERLAY_OPACITY 60
#define DEFAULT_ANIMATION_INDEX 0
#define DEFAULT_LAYER LAYER_TOP                     // Default to TOP for broader compatibility
#define DEFAULT_OVERLAY_POSITION POSITION_TOP
#define DEFAULT_HAPPY_KPM 0
#define DEFAULT_IDLE_SLEEP_TIMEOUT_SEC 0
#define DEFAULT_CAT_ALIGN ALIGN_CENTER

// is in debug build
#ifndef NDEBUG
#define DEFAULT_TEST_ANIMATION_DURATION_MS 200
#define DEFAULT_TEST_ANIMATION_INTERVAL_SEC 3
#define DEFAULT_ENABLE_DEBUG 1
#else
#define DEFAULT_TEST_ANIMATION_DURATION_MS 0
#define DEFAULT_TEST_ANIMATION_INTERVAL_SEC 0
#define DEFAULT_ENABLE_DEBUG 0
#endif


// Config keys
#define CAT_X_OFFSET_KEY "cat_x_offset"
#define CAT_Y_OFFSET_KEY "cat_y_offset"
#define CAT_HEIGHT_KEY "cat_height"
#define OVERLAY_HEIGHT_KEY "overlay_height"
#define OVERLAY_POSITION_KEY "overlay_position"
#define ANIMATION_NAME_KEY "animation_name"
#define INVERT_COLOR_KEY "invert_color"
#define PADDING_X_KEY "padding_x"
#define PADDING_Y_KEY "padding_y"
#define IDLE_FRAME_KEY "idle_frame"
#define ENABLE_SCHEDULED_SLEEP_KEY "enable_scheduled_sleep"
#define SLEEP_BEGIN_KEY "sleep_begin"
#define SLEEP_END_KEY "sleep_end"
#define IDLE_SLEEP_TIMEOUT_KEY "idle_sleep_timeout"
#define HAPPY_KPM_KEY "happy_kpm"
#define KEYPRESS_DURATION_KEY "keypress_duration"
#define TEST_ANIMATION_DURATION_KEY "test_animation_duration"
#define TEST_ANIMATION_INTERVAL_KEY "test_animation_interval"
#define FPS_KEY "fps"
#define OVERLAY_OPACITY_KEY "overlay_opacity"
#define ENABLE_DEBUG_KEY "enable_debug"
#define KEYBOARD_DEVICE_KEY "keyboard_device"
#define KEYBOARD_DEVICES_KEY "keyboard_devices"
#define ANIMATION_INDEX_KEY "animation_index"
#define LAYER_KEY "layer"
#define CAT_ALIGN_KEY "cat_align"

#define VALUE_BUF 256
#define LINE_BUF 512

#define BONGOCAT_NAME "bongocat"

// =============================================================================
// CONFIGURATION VALIDATION MODULE
// =============================================================================

static void config_clamp_int(int *value, int min, int max, const char *name) {
    assert(value);
    if (*value < min || *value > max) {
        BONGOCAT_LOG_WARNING("%s %d out of range [%d-%d], clamping", name, *value, min, max);
        *value = (*value < min) ? min : max;
    }
}

static void config_validate_dimensions(config_t *config) {
    assert(config);
    config_clamp_int(&config->cat_height, MIN_CAT_HEIGHT, MAX_CAT_HEIGHT, CAT_HEIGHT_KEY);
    config_clamp_int(&config->overlay_height, MIN_OVERLAY_HEIGHT, MAX_OVERLAY_HEIGHT, OVERLAY_HEIGHT_KEY);
}

static void config_validate_timing(config_t *config) {
    assert(config);
    config_clamp_int(&config->fps, MIN_FPS, MAX_FPS, FPS_KEY);
    config_clamp_int(&config->keypress_duration_ms, MIN_DURATION, MAX_DURATION, KEYPRESS_DURATION_KEY);
    config_clamp_int(&config->test_animation_duration_ms, MIN_DURATION, MAX_DURATION, TEST_ANIMATION_DURATION_KEY);
    config_clamp_int(&config->idle_sleep_timeout_sec, MIN_TIMEOUT, MAX_TIMEOUT, IDLE_SLEEP_TIMEOUT_KEY);
    
    // Validate interval (0 is allowed to disable)
    if (config->test_animation_interval_sec < 0 || config->test_animation_interval_sec > MAX_INTERVAL) {
        BONGOCAT_LOG_WARNING(TEST_ANIMATION_INTERVAL_KEY " %d out of range [0-%d], clamping",
                           config->test_animation_interval_sec, MAX_INTERVAL);
        config->test_animation_interval_sec = (config->test_animation_interval_sec < 0) ? 0 : MAX_INTERVAL;
    }
}

static void config_validate_kpm(config_t *config) {
    assert(config);
    config_clamp_int(&config->happy_kpm, MIN_KPM, MAX_KPM, HAPPY_KPM_KEY);
}

static void config_validate_appearance(config_t *config) {
    assert(config);
    // Validate opacity
    config_clamp_int(&config->overlay_opacity, 0, 255, OVERLAY_OPACITY_KEY);

    // Validate animation index
    if (config->animation_index < 0 || config->animation_index >= ANIMS_COUNT) {
        BONGOCAT_LOG_WARNING(ANIMATION_INDEX_KEY " %d out of range [0-%d], resetting to 0",
                           config->animation_index, ANIMS_COUNT - 1);
        config->animation_index = 0;
    }

    // Validate idle frame
    if (config->animation_index == BONGOCAT_ANIM_INDEX) {
        if (config->idle_frame < 0 || config->idle_frame >= BONGOCAT_NUM_FRAMES) {
            BONGOCAT_LOG_WARNING(IDLE_FRAME_KEY "%d out of range [0-%d], resetting to 0",
                               config->idle_frame, BONGOCAT_NUM_FRAMES - 1);
            config->idle_frame = 0;
        }
    } else {
#ifdef FEATURE_INCLUDE_ONLY_BONGOCAT_EMBEDDED_ASSETS
        // digimon animation
        if (config->idle_frame < 0 || config->idle_frame >= MAX_DIGIMON_FRAMES) {
            BONGOCAT_LOG_WARNING(IDLE_FRAME_KEY "%d out of range [0-%d], resetting to 0",
                               config->idle_frame, MAX_DIGIMON_FRAMES - 1);
            config->idle_frame = 0;
        }
#endif
    }
}

static void config_validate_enums(config_t *config) {
    assert(config);
    // Validate layer
    if (config->layer != LAYER_TOP && config->layer != LAYER_OVERLAY) {
        BONGOCAT_LOG_WARNING("Invalid layer %d, resetting to top", config->layer);
        config->layer = LAYER_TOP;
    }

    // Validate overlay_position
    if (config->overlay_position != POSITION_TOP && config->overlay_position != POSITION_BOTTOM) {
        BONGOCAT_LOG_WARNING("Invalid " OVERLAY_OPACITY_KEY " %d, resetting to top", config->overlay_position);
        config->overlay_position = POSITION_TOP;
    }

    // Validate cat_align
    if (config->cat_align != ALIGN_CENTER && config->cat_align != ALIGN_LEFT && config->cat_align != ALIGN_RIGHT) {
        BONGOCAT_LOG_WARNING("Invalid " CAT_ALIGN_KEY " %d, resetting to center", config->cat_align);
        config->cat_align = ALIGN_CENTER;
    }
}

static void config_validate_time(config_t *config) {
    assert(config);
    if (config->enable_scheduled_sleep) {
        const int begin_minutes = config->sleep_begin.hour * 60 + config->sleep_begin.min;
        const int end_minutes = config->sleep_end.hour * 60 + config->sleep_end.min;

        if (begin_minutes == end_minutes) {
            BONGOCAT_LOG_WARNING("Sleep mode is enabled, but time is equal: %02d:%02d, disable sleep mode", config->sleep_begin.hour, config->sleep_begin.min);

            config->enable_scheduled_sleep = 0;
            //config->sleep_begin.hour = 0;
            //config->sleep_begin.min = 0;
            //config->sleep_end.hour = 0;
            //config->sleep_end.min = 0;
        }
    }
}

static bongocat_error_t config_validate(config_t *config) {
    BONGOCAT_CHECK_NULL(config, BONGOCAT_ERROR_INVALID_PARAM);

    // Normalize boolean values
    config->enable_debug = config->enable_debug ? 1 : 0;
    config->invert_color = config->invert_color ? 1 : 0;
    config->enable_scheduled_sleep = config->enable_scheduled_sleep ? 1 : 0;

    config_validate_dimensions(config);
    config_validate_timing(config);
    config_validate_appearance(config);
    config_validate_enums(config);
    config_validate_time(config);
    config_validate_kpm(config);
    
    return BONGOCAT_SUCCESS;
}

// =============================================================================
// DEVICE MANAGEMENT MODULE
// =============================================================================

static bongocat_error_t config_add_keyboard_device(config_t *config, const char *device_path) {
    BONGOCAT_CHECK_NULL(config, BONGOCAT_ERROR_INVALID_PARAM);
    BONGOCAT_CHECK_NULL(device_path, BONGOCAT_ERROR_INVALID_PARAM);

    assert(config->num_keyboard_devices >= 0 && config->num_keyboard_devices < INT_MAX-1);

    const int old_num_keyboard_devices = config->num_keyboard_devices;
    char **old_keyboard_devices = config->keyboard_devices;

    // Allocate new array for device pointers
    int new_num_keyboard_devices = old_num_keyboard_devices + 1;
    char **new_keyboard_devices = BONGOCAT_MALLOC(new_num_keyboard_devices * sizeof(char *));
    if (!new_keyboard_devices) {
        BONGOCAT_LOG_ERROR("Failed to allocate memory for keyboard_devices array");
        return BONGOCAT_ERROR_MEMORY;
    }

    // Deep copy old strings into new array
    for (int i = 0; i < old_num_keyboard_devices; i++) {
        assert(old_keyboard_devices[i]);
        new_keyboard_devices[i] = strdup(old_keyboard_devices[i]);
        if (!new_keyboard_devices[i]) {
            // Free already-allocated entries
            for (int j = 0; j < i; ++j) {
                free(new_keyboard_devices[j]);
            }
            BONGOCAT_FREE(new_keyboard_devices);
            config->keyboard_devices = old_keyboard_devices;
            config->num_keyboard_devices = old_num_keyboard_devices;
            BONGOCAT_LOG_ERROR("Failed to copy keyboard device string");
            return BONGOCAT_ERROR_MEMORY;
        }
    }

    // Add new device path
    new_keyboard_devices[old_num_keyboard_devices] = strdup(device_path);
    if (!new_keyboard_devices[old_num_keyboard_devices]) {
        // free new copied strings
        for (int i = 0; i < old_num_keyboard_devices; i++) {
            if (new_keyboard_devices[i]) free(new_keyboard_devices[i]);
            new_keyboard_devices[i] = NULL;
        }
        BONGOCAT_FREE(new_keyboard_devices);
        config->keyboard_devices = old_keyboard_devices;
        config->num_keyboard_devices = old_num_keyboard_devices;
        BONGOCAT_LOG_ERROR("Failed to copy new keyboard device path");
        return BONGOCAT_ERROR_MEMORY;
    }

    // Free old list (deep)
    for (int i = 0; i < old_num_keyboard_devices; i++) {
        if (old_keyboard_devices[i]) free(old_keyboard_devices[i]);
        old_keyboard_devices[i] = NULL;
    }
    BONGOCAT_SAFE_FREE(old_keyboard_devices);

    // move new list
    config->keyboard_devices = new_keyboard_devices;
    config->num_keyboard_devices = new_num_keyboard_devices;

    return BONGOCAT_SUCCESS;
}

static void config_cleanup_devices(config_t *config) {
    if (config->keyboard_devices) {
        for (int i = 0; i < config->num_keyboard_devices; i++) {
            free(config->keyboard_devices[i]);
        }
        BONGOCAT_SAFE_FREE(config->keyboard_devices);
        config->keyboard_devices = NULL;
        config->num_keyboard_devices = 0;
    }
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

static bongocat_error_t config_parse_integer_key(config_t *config, const char *key, const char *value) {
    int int_value = (int)strtol(value, NULL, 10);
    
    if (strcmp(key, CAT_X_OFFSET_KEY) == 0) {
        config->cat_x_offset = int_value;
    } else if (strcmp(key, CAT_Y_OFFSET_KEY) == 0) {
        config->cat_y_offset = int_value;
    } else if (strcmp(key, CAT_HEIGHT_KEY) == 0) {
        config->cat_height = int_value;
    } else if (strcmp(key, OVERLAY_HEIGHT_KEY) == 0) {
        config->overlay_height = int_value;
    } else if (strcmp(key, IDLE_FRAME_KEY) == 0) {
        config->idle_frame = int_value;
    } else if (strcmp(key, KEYPRESS_DURATION_KEY) == 0) {
        config->keypress_duration_ms = int_value;
    } else if (strcmp(key, TEST_ANIMATION_DURATION_KEY) == 0) {
        config->test_animation_duration_ms = int_value;
    } else if (strcmp(key, TEST_ANIMATION_INTERVAL_KEY) == 0) {
        config->test_animation_interval_sec = int_value;
    } else if (strcmp(key, FPS_KEY) == 0) {
        config->fps = int_value;
    } else if (strcmp(key, OVERLAY_OPACITY_KEY) == 0) {
        config->overlay_opacity = int_value;
    } else if (strcmp(key, ENABLE_DEBUG_KEY) == 0) {
        config->enable_debug = int_value;
    } else if (strcmp(key, ANIMATION_INDEX_KEY) == 0) {
        config->animation_index = int_value;
    } else if (strcmp(key, INVERT_COLOR_KEY) == 0) {
        config->invert_color = int_value;
    } else if (strcmp(key, PADDING_X_KEY) == 0) {
        config->padding_x = int_value;
    } else if (strcmp(key, PADDING_Y_KEY) == 0) {
        config->padding_y = int_value;
    } else if (strcmp(key, ENABLE_SCHEDULED_SLEEP_KEY) == 0) {
        config->enable_scheduled_sleep = int_value;
    } else if (strcmp(key, IDLE_SLEEP_TIMEOUT_KEY) == 0) {
        config->idle_sleep_timeout_sec = int_value;
    } else if (strcmp(key, HAPPY_KPM_KEY) == 0) {
        config->happy_kpm = int_value;
    } else {
        return BONGOCAT_ERROR_INVALID_PARAM; // Unknown key
    }
    
    return BONGOCAT_SUCCESS;
}

static bongocat_error_t config_parse_enum_key(config_t *config, const char *key, const char *value) {
    if (strcmp(key, LAYER_KEY) == 0) {
        if (strcmp(value, LAYER_TOP_STR) == 0) {
            config->layer = LAYER_TOP;
        } else if (strcmp(value, LAYER_OVERLAY_STR) == 0) {
            config->layer = LAYER_OVERLAY;
        } else {
            BONGOCAT_LOG_WARNING("Invalid " LAYER_KEY " '%s', using 'top'", value);
            config->layer = LAYER_TOP;
        }
    } else if (strcmp(key, OVERLAY_POSITION_KEY) == 0) {
        if (strcmp(value, POSITION_TOP_STR) == 0) {
            config->overlay_position = POSITION_TOP;
        } else if (strcmp(value, POSITION_BOTTOM_STR) == 0) {
            config->overlay_position = POSITION_BOTTOM;
        } else {
            BONGOCAT_LOG_WARNING("Invalid " OVERLAY_POSITION_KEY " '%s', using 'top'", value);
            config->overlay_position = POSITION_TOP;
        }
    } else if (strcmp(key, CAT_ALIGN_KEY) == 0) {
        if (strcmp(value, ALIGN_CENTER_STR) == 0) {
            config->cat_align = ALIGN_CENTER;
        } else if (strcmp(value, ALIGN_LEFT_STR) == 0) {
            config->cat_align = ALIGN_LEFT;
        } else if (strcmp(value, ALIGN_RIGHT_STR) == 0) {
            config->cat_align = ALIGN_RIGHT;
        } else {
            BONGOCAT_LOG_WARNING("Invalid " CAT_ALIGN_KEY " '%s', using 'center'", value);
            config->cat_align = ALIGN_CENTER;
        }
    } else {
        return BONGOCAT_ERROR_INVALID_PARAM; // Unknown key
    }
    
    return BONGOCAT_SUCCESS;
}

static bongocat_error_t config_parse_string(config_t *config, const char *key, const char *value) {
    if (strcmp(key, SLEEP_BEGIN_KEY) == 0) {
        if (value && value[0] != '\0') {
            int hour, min;
            if (sscanf(value, "%2d:%2d", &hour, &min) != 2 || hour < 0 || hour > 23 || min < 0 || min > 59) {
                return BONGOCAT_ERROR_INVALID_PARAM; // Invalid time format
            }

            config->sleep_begin.hour = hour;
            config->sleep_begin.min = min;
        } else {
            config->sleep_begin.hour = 0;
            config->sleep_begin.min = 0;
        }
    } else if (strcmp(key, SLEEP_END_KEY) == 0) {
        if (value && value[0] != '\0') {
            int hour, min;
            if (sscanf(value, "%2d:%2d", &hour, &min) != 2 || hour < 0 || hour > 23 || min < 0 || min > 59) {
                return BONGOCAT_ERROR_INVALID_PARAM; // Invalid time format
            }

            config->sleep_end.hour = hour;
            config->sleep_end.min = min;
        } else {
            config->sleep_end.hour = 0;
            config->sleep_end.min = 0;
        }
    } else if (strcmp(key, ANIMATION_NAME_KEY) == 0) {
        char lower_value[VALUE_BUF] = {0};
        memset(lower_value, 0, VALUE_BUF);
        for(size_t i = 0; i < strlen(value); i++) {
            lower_value[i] = (char)tolower(value[i]);
        }

        config->animation_index = -1;

        if (strcmp(lower_value, BONGOCAT_NAME) == 0) {
            config->animation_index = BONGOCAT_ANIM_INDEX;
        }

#ifndef FEATURE_INCLUDE_ONLY_BONGOCAT_EMBEDDED_ASSETS
#ifdef FEATURE_INCLUDE_DM_EMBEDDED_ASSETS
        /// @TODO: add full assets
#else
        //if (strcmp(lower_value, "agumon") == 0) {
        //    config->animation_index = DM_AGUMON_ANIM_INDEX;
        //}
#include "../graphics/embedded_assets/min_dm_config_parse_enum_key.c.inl"
#endif
#endif

        if (config->animation_index < 0) {
            BONGOCAT_LOG_WARNING("Invalid " ANIMATION_NAME_KEY " '%s', using '" BONGOCAT_NAME "'", value);
            config->animation_index = BONGOCAT_ANIM_INDEX;
        }
    } else {
        return BONGOCAT_ERROR_INVALID_PARAM; // Unknown key
    }

    return BONGOCAT_SUCCESS;
}

static bongocat_error_t config_parse_key_value(config_t *config, const char *key, const char *value) {
    // Try integer keys first
    if (config_parse_integer_key(config, key, value) == BONGOCAT_SUCCESS) {
        return BONGOCAT_SUCCESS;
    }
    
    // Try enum keys
    if (config_parse_enum_key(config, key, value) == BONGOCAT_SUCCESS) {
        return BONGOCAT_SUCCESS;
    }

    // Try string
    if (config_parse_string(config, key, value) == BONGOCAT_SUCCESS) {
        return BONGOCAT_SUCCESS;
    }
    
    // Handle device keys
    if (strcmp(key, KEYBOARD_DEVICE_KEY) == 0 || strcmp(key, KEYBOARD_DEVICES_KEY) == 0) {
        return config_add_keyboard_device(config, value);
    }
    
    // Unknown key
    return BONGOCAT_ERROR_INVALID_PARAM;
}

static bool config_is_comment_or_empty(const char *line) {
    return (line[0] == '#' || line[0] == '\0' || strspn(line, " \t") == strlen(line));
}

static bongocat_error_t config_parse_file(config_t *config, const char *config_file_path) {
    BONGOCAT_CHECK_NULL(config, BONGOCAT_ERROR_INVALID_PARAM);
    
    const char *file_path = config_file_path ? config_file_path : DEFAULT_CONFIG_FILE_PATH;
    
    FILE *file = fopen(file_path, "r");
    if (!file) {
        BONGOCAT_LOG_INFO("Config file '%s' not found, using defaults", file_path);
        return BONGOCAT_SUCCESS;
    }
    
    char line[LINE_BUF] = {0};
    char key[VALUE_BUF] = {0};
    char value[VALUE_BUF] = {0};
    int line_number = 0;
    bongocat_error_t result = BONGOCAT_SUCCESS;
    
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
            if (parse_result == BONGOCAT_ERROR_INVALID_PARAM) {
                BONGOCAT_LOG_WARNING("Unknown configuration key '%s' at line %d", trimmed_key, line_number);
            } else if (parse_result != BONGOCAT_SUCCESS) {
                result = parse_result;
                break;
            }
        } else if (strlen(line) > 0) {
            BONGOCAT_LOG_WARNING("Invalid configuration line %d: %s", line_number, line);
        }
    }
    
    fclose(file);
    
    if (result == BONGOCAT_SUCCESS) {
        BONGOCAT_LOG_INFO("Loaded configuration from %s", file_path);
    }
    
    return result;
}

// =============================================================================
// DEFAULT CONFIGURATION MODULE
// =============================================================================

void config_set_defaults(config_t *config) {
    *config = (config_t) {
        .bar_height = DEFAULT_BAR_HEIGHT,
        /*
        .asset_paths = {
            "assets/bongo-cat-both-up.png",
            "assets/bongo-cat-left-down.png",
            "assets/bongo-cat-right-down.png"
        },
        */
        .keyboard_devices = NULL,
        .num_keyboard_devices = 0,
        .cat_x_offset = DEFAULT_CAT_X_OFFSET,
        .cat_y_offset = DEFAULT_CAT_Y_OFFSET,
        .cat_height = DEFAULT_CAT_HEIGHT,
        .overlay_height = DEFAULT_OVERLAY_HEIGHT,
        .idle_frame = DEFAULT_IDLE_FRAME,
        .keypress_duration_ms = DEFAULT_KEYPRESS_DURATION_MS,
        .test_animation_duration_ms = DEFAULT_TEST_ANIMATION_DURATION_MS,
        .test_animation_interval_sec = DEFAULT_TEST_ANIMATION_INTERVAL_SEC,
        .fps = DEFAULT_FPS,
        .overlay_opacity = DEFAULT_OVERLAY_OPACITY,
        .enable_debug = DEFAULT_ENABLE_DEBUG,
        .layer = DEFAULT_LAYER,
        .overlay_position = DEFAULT_OVERLAY_POSITION,

        .animation_index = DEFAULT_ANIMATION_INDEX,
        .invert_color = 0,
        .padding_x = 0,
        .padding_y = 0,

        .enable_scheduled_sleep = 0,
        .sleep_begin = {0},
        .sleep_end = {0},
        .idle_sleep_timeout_sec = DEFAULT_IDLE_SLEEP_TIMEOUT_SEC,

        .happy_kpm = DEFAULT_HAPPY_KPM,
        .cat_align = DEFAULT_CAT_ALIGN,
    };
}

static bongocat_error_t config_set_default_devices(config_t *config) {
    if (!config->keyboard_devices) {
        return config_add_keyboard_device(config, DEFAULT_DEVICE);
    }
    return BONGOCAT_SUCCESS;
}

static void config_finalize(config_t *config) {
    // Update bar_height from config
    // Update bar_height from config
    config->bar_height = config->overlay_height;
    
    // Initialize error system with debug setting
    bongocat_error_init(config->enable_debug);
}

static void config_log_summary(const config_t *config) {
    BONGOCAT_LOG_DEBUG("Configuration loaded successfully");
    BONGOCAT_LOG_DEBUG("  Bar: %dpx", config->bar_height);
    if (config->animation_index == BONGOCAT_ANIM_INDEX) {
        BONGOCAT_LOG_DEBUG("  Cat: %dx%d at offset (%d,%d)",
                          config->cat_height, (config->cat_height * 954) / 393,
                          config->cat_x_offset, config->cat_y_offset);

    } else {
        BONGOCAT_LOG_DEBUG("  Digimon: %02d at offset (%d,%d)",
                          config->animation_index,
                          config->cat_x_offset, config->cat_y_offset);
    }
    BONGOCAT_LOG_DEBUG("  FPS: %d, Opacity: %d", config->fps, config->overlay_opacity);
    BONGOCAT_LOG_DEBUG("  Position: %s", config->overlay_position == POSITION_TOP ? "top" : "bottom");
    BONGOCAT_LOG_DEBUG("  Alignment: %d", config->cat_align, config->cat_align == ALIGN_CENTER ? "(center)" : "");
    BONGOCAT_LOG_DEBUG("  Layer: %s", config->layer == LAYER_TOP ? "top" : "overlay");
}

// =============================================================================
// PUBLIC API IMPLEMENTATION
// =============================================================================

bongocat_error_t load_config(config_t *config, const char *config_file_path) {
    BONGOCAT_CHECK_NULL(config, BONGOCAT_ERROR_INVALID_PARAM);
    
    // Clear existing keyboard devices to prevent accumulation during reloads
    config_cleanup_devices(config);
    config_set_defaults(config);
    
    // Parse config file and override defaults
    bongocat_error_t result = config_parse_file(config, config_file_path);
    if (result != BONGOCAT_SUCCESS) {
        BONGOCAT_LOG_ERROR("Failed to parse configuration file: %s", bongocat_error_string(result));
        return result;
    }
    
    // Validate and sanitize configuration
    result = config_validate(config);
    if (result != BONGOCAT_SUCCESS) {
        BONGOCAT_LOG_ERROR("Configuration validation failed: %s", bongocat_error_string(result));
        return result;
    }

    if (config->keyboard_devices == NULL || config->num_keyboard_devices == 0) {
        // Set default keyboard device if none specified
        result = config_set_default_devices(config);
        if (result != BONGOCAT_SUCCESS) {
            BONGOCAT_LOG_ERROR("Failed to set default keyboard devices: %s", bongocat_error_string(result));
            return result;
        } else {
            BONGOCAT_LOG_INFO("No device loaded, use default keyboard device: %s", DEFAULT_DEVICE);
        }
    }
    
    // Finalize configuration
    config_finalize(config);
    
    // Log configuration summary
    config_log_summary(config);
    
    return BONGOCAT_SUCCESS;
}

void config_cleanup(config_t *config) {
    config_cleanup_devices(config);
    config_set_defaults(config);
}
