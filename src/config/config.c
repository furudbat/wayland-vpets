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

#define DEFAULT_DEVICE "/dev/input/event4"

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
    config_clamp_int(&config->cat_height, MIN_CAT_HEIGHT, MAX_CAT_HEIGHT, "cat_height");
    config_clamp_int(&config->overlay_height, MIN_OVERLAY_HEIGHT, MAX_OVERLAY_HEIGHT, "overlay_height");
}

static void config_validate_timing(config_t *config) {
    assert(config);
    config_clamp_int(&config->fps, MIN_FPS, MAX_FPS, "fps");
    config_clamp_int(&config->keypress_duration_ms, MIN_DURATION, MAX_DURATION, "keypress_duration");
    config_clamp_int(&config->test_animation_duration_ms, MIN_DURATION, MAX_DURATION, "test_animation_duration");
    config_clamp_int(&config->idle_sleep_timeout_sec, MIN_TIMEOUT, MAX_TIMEOUT, "idle_sleep_timeout");
    
    // Validate interval (0 is allowed to disable)
    if (config->test_animation_interval_sec < 0 || config->test_animation_interval_sec > MAX_INTERVAL) {
        BONGOCAT_LOG_WARNING("test_animation_interval %d out of range [0-%d], clamping",
                           config->test_animation_interval_sec, MAX_INTERVAL);
        config->test_animation_interval_sec = (config->test_animation_interval_sec < 0) ? 0 : MAX_INTERVAL;
    }
}

static void config_validate_kpm(config_t *config) {
    assert(config);
    config_clamp_int(&config->happy_kpm, MIN_KPM, MAX_KPM, "happy_kpm");
}

static void config_validate_appearance(config_t *config) {
    assert(config);
    // Validate opacity
    config_clamp_int(&config->overlay_opacity, 0, 255, "overlay_opacity");

    // Validate animation index
    if (config->animation_index < 0 || config->animation_index >= ANIMS_COUNT) {
        BONGOCAT_LOG_WARNING("animation_index %d out of range [0-%d], resetting to 0",
                           config->animation_index, ANIMS_COUNT - 1);
        config->animation_index = 0;
    }

    // Validate idle frame
    if (config->animation_index == BONGOCAT_ANIM_INDEX) {
        if (config->idle_frame < 0 || config->idle_frame >= BONGOCAT_NUM_FRAMES) {
            BONGOCAT_LOG_WARNING("idle_frame %d out of range [0-%d], resetting to 0",
                               config->idle_frame, BONGOCAT_NUM_FRAMES - 1);
            config->idle_frame = 0;
        }
    } else {
#ifdef FEATURE_INCLUDE_ONLY_BONGOCAT_EMBEDDED_ASSETS
        // digimon animation
        if (config->idle_frame < 0 || config->idle_frame >= MAX_DIGIMON_FRAMES) {
            BONGOCAT_LOG_WARNING("idle_frame %d out of range [0-%d], resetting to 0",
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
        BONGOCAT_LOG_WARNING("Invalid overlay_position %d, resetting to top", config->overlay_position);
        config->overlay_position = POSITION_TOP;
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
    
    if (strcmp(key, "cat_x_offset") == 0) {
        config->cat_x_offset = int_value;
    } else if (strcmp(key, "cat_y_offset") == 0) {
        config->cat_y_offset = int_value;
    } else if (strcmp(key, "cat_height") == 0) {
        config->cat_height = int_value;
    } else if (strcmp(key, "overlay_height") == 0) {
        config->overlay_height = int_value;
    } else if (strcmp(key, "idle_frame") == 0) {
        config->idle_frame = int_value;
    } else if (strcmp(key, "keypress_duration") == 0) {
        config->keypress_duration_ms = int_value;
    } else if (strcmp(key, "test_animation_duration") == 0) {
        config->test_animation_duration_ms = int_value;
    } else if (strcmp(key, "test_animation_interval") == 0) {
        config->test_animation_interval_sec = int_value;
    } else if (strcmp(key, "fps") == 0) {
        config->fps = int_value;
    } else if (strcmp(key, "overlay_opacity") == 0) {
        config->overlay_opacity = int_value;
    } else if (strcmp(key, "enable_debug") == 0) {
        config->enable_debug = int_value;
    } else if (strcmp(key, "animation_index") == 0) {
        config->animation_index = int_value;
    } else if (strcmp(key, "invert_color") == 0) {
        config->invert_color = int_value;
    } else if (strcmp(key, "padding_x") == 0) {
        config->padding_x = int_value;
    } else if (strcmp(key, "padding_y") == 0) {
        config->padding_y = int_value;
    } else if (strcmp(key, "enable_scheduled_sleep") == 0) {
        config->enable_scheduled_sleep = int_value;
    } else if (strcmp(key, "idle_sleep_timeout") == 0) {
        config->idle_sleep_timeout_sec = int_value;
    } else if (strcmp(key, "happy_kpm") == 0) {
        config->happy_kpm = int_value;
    } else {
        return BONGOCAT_ERROR_INVALID_PARAM; // Unknown key
    }
    
    return BONGOCAT_SUCCESS;
}

static bongocat_error_t config_parse_enum_key(config_t *config, const char *key, const char *value) {
    if (strcmp(key, "layer") == 0) {
        if (strcmp(value, "top") == 0) {
            config->layer = LAYER_TOP;
        } else if (strcmp(value, "overlay") == 0) {
            config->layer = LAYER_OVERLAY;
        } else {
            BONGOCAT_LOG_WARNING("Invalid layer '%s', using 'top'", value);
            config->layer = LAYER_TOP;
        }
    } else if (strcmp(key, "overlay_position") == 0) {
        if (strcmp(value, "top") == 0) {
            config->overlay_position = POSITION_TOP;
        } else if (strcmp(value, "bottom") == 0) {
            config->overlay_position = POSITION_BOTTOM;
        } else {
            BONGOCAT_LOG_WARNING("Invalid overlay_position '%s', using 'top'", value);
            config->overlay_position = POSITION_TOP;
        }
    } else if (strcmp(key, "animation_name") == 0) {
#ifdef FEATURE_INCLUDE_ONLY_BONGOCAT_EMBEDDED_ASSETS
        // ignore animation_name, use bongocat
        config->animation_index = BONGOCAT_ANIM_INDEX;
#else
        char lower_value[256] = {0};
        memset(lower_value, 0, sizeof(lower_value));
        for(size_t i = 0; i < strlen(value); i++) {
            lower_value[i] = (char)tolower(value[i]);
        }

        config->animation_index = -1;

        if (strcmp(lower_value, "bongocat") == 0) {
            config->animation_index = BONGOCAT_ANIM_INDEX;
        }

        #ifdef FEATURE_INCLUDE_DM_EMBEDDED_ASSETS
        /// @TODO: add full assets
        #else
        //if (strcmp(lower_value, "agumon") == 0) {
        //    config->animation_index = DM_AGUMON_ANIM_INDEX;
        //}
        #include "../graphics/embedded_assets/min_dm_config_parse_enum_key.c.inl"
        #endif

        if (config->animation_index < 0) {
            BONGOCAT_LOG_WARNING("Invalid overlay_position '%s', using 'bongocat'", value);
            config->animation_index = BONGOCAT_ANIM_INDEX;
        }
#endif
    } else {
        return BONGOCAT_ERROR_INVALID_PARAM; // Unknown key
    }
    
    return BONGOCAT_SUCCESS;
}

static bongocat_error_t config_parse_string(config_t *config, const char *key, const char *value) {
    if (strcmp(key, "sleep_begin") == 0) {
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
    } else if (strcmp(key, "sleep_end") == 0) {
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
    } else if (strcmp(key, "animation_name") == 0) {
        char lower_value[256] = {0};
        memset(lower_value, 0, sizeof(lower_value));
        for(size_t i = 0; i < strlen(value); i++) {
            lower_value[i] = (char)tolower(value[i]);
        }

        config->animation_index = -1;

        if (strcmp(lower_value, "bongocat") == 0) {
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
            BONGOCAT_LOG_WARNING("Invalid overlay_position '%s', using 'bongocat'", value);
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
    if (strcmp(key, "keyboard_device") == 0 || strcmp(key, "keyboard_devices") == 0) {
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
    
    const char *file_path = config_file_path ? config_file_path : "bongocat.conf";
    
    FILE *file = fopen(file_path, "r");
    if (!file) {
        BONGOCAT_LOG_INFO("Config file '%s' not found, using defaults", file_path);
        return BONGOCAT_SUCCESS;
    }
    
    char line[512];
    char key[256], value[256];
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
        .cat_x_offset = 100,
        .cat_y_offset = 10,
        .cat_height = 40,
        .overlay_height = 50,
        .idle_frame = 0,
        .keypress_duration_ms = 100,
        .test_animation_duration_ms = 200,
        .test_animation_interval_sec = 3,
        .fps = 60,
        .overlay_opacity = 150,
        .enable_debug = 1,
        .layer = LAYER_TOP,  // Default to TOP for broader compatibility
        .overlay_position = POSITION_TOP,

        .animation_index = 0,
        .invert_color = 0,
        .padding_x = 0,
        .padding_y = 0,

        .enable_scheduled_sleep = 0,
        .sleep_begin = {0},
        .sleep_end = {0},
        .idle_sleep_timeout_sec = 0,

        .happy_kpm = 0,
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
