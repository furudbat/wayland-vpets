#include "config/config.h"
#include "core/bongocat.h"
#include "utils/error.h"
#include "graphics/animation_context.h"
#include <cassert>
#include <cctype>
#include <cstdio>
#include <cstdlib>

#include "graphics/embedded_assets_dms.h"
#include "graphics/embedded_assets_pkmn.h"
#include "embedded_assets/bongocat/bongocat.h"
#include "embedded_assets/bongocat/bongocat.hpp"
#include "embedded_assets/ms_agent/ms_agent.hpp"
#include "embedded_assets/ms_agent/ms_agent_sprite.h"
#include "embedded_assets/pkmn/pkmn_sprite.h"
#include "embedded_assets/misc/misc.hpp"
#include "embedded_assets/misc/misc_sprite.h"
#include "embedded_assets/pmd/pmd_sprite.h"

#ifdef FEATURE_DM_EMBEDDED_ASSETS
#include "dm_config_parse_animation_name.h"
#endif
#ifdef FEATURE_DM20_EMBEDDED_ASSETS
#include "dm20_config_parse_animation_name.h"
#endif
#ifdef FEATURE_DMX_EMBEDDED_ASSETS
#include "dmx_config_parse_animation_name.h"
#endif
#ifdef FEATURE_DMC_EMBEDDED_ASSETS
#include "dmc_config_parse_animation_name.h"
#endif
#ifdef FEATURE_PEN_EMBEDDED_ASSETS
#include "pen_config_parse_animation_name.h"
#endif
#ifdef FEATURE_PEN20_EMBEDDED_ASSETS
#include "pen20_config_parse_animation_name.h"
#endif
#ifdef FEATURE_DMALL_EMBEDDED_ASSETS
#include "dmall_config_parse_animation_name.h"
#endif

#ifdef FEATURE_PKMN_EMBEDDED_ASSETS
#include "pkmn_config_parse_animation_name.h"
#endif
#ifdef FEATURE_PMD_EMBEDDED_ASSETS
#include "pmd_config_parse_animation_name.h"
#endif


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
    static inline constexpr int MIN_KPM = 0;
    static inline constexpr int MAX_KPM = 10000;
    static inline constexpr double MAX_CPU_THRESHOLD = 100.0;
    static inline constexpr double MAX_CPU_RUNNING_FACTOR = 10.0;
    static inline constexpr int MAX_UPDATE_RATE_MS = 60 * 60 * 1000;
    static inline constexpr int MAX_SLEEP_TIMEOUT_SEC = 30 * 24 * 60 * 60;
    static inline constexpr int MIN_OFFSET = -16000;
    static inline constexpr int MAX_OFFSET = 16000;
    static inline constexpr int MIN_MOVEMENT_RADIUS = 0;
    static inline constexpr int MAX_MOVEMENT_RADIUS = MAX_OFFSET/2;

    static inline constexpr int MIN_CUSTOM_FRAMES = 0;
    static inline constexpr int MAX_CUSTOM_FRAMES = 512;
    static inline constexpr int MIN_CUSTOM_ROWS = 0;
    static_assert(assets::CUSTOM_SPRITE_SHEET_MAX_ROWS > 0);
    static inline constexpr int MAX_CUSTOM_ROWS = assets::CUSTOM_SPRITE_SHEET_MAX_ROWS-1;

    static_assert(MIN_FPS > 0, "FPS cannot be zero, for math reasons");

    // Default settings
    static inline constexpr auto DEFAULT_DEVICE = "/dev/input/event4";
    static inline constexpr auto DEFAULT_CONFIG_FILE_PATH = "bongocat.conf";

    static inline constexpr int32_t DEFAULT_CAT_X_OFFSET = 100;
    static inline constexpr int32_t DEFAULT_CAT_Y_OFFSET = 10;
    static inline constexpr int32_t DEFAULT_CAT_HEIGHT = 40;
    static inline constexpr int32_t DEFAULT_OVERLAY_HEIGHT = 50;
    static inline constexpr int32_t DEFAULT_IDLE_FRAME = 0;
    static inline constexpr platform::time_ms_t DEFAULT_KEYPRESS_DURATION_MS = 100;
    static inline constexpr int32_t DEFAULT_OVERLAY_OPACITY = 60;
    static inline constexpr int32_t DEFAULT_ANIMATION_INDEX = 0;
    static inline constexpr layer_type_t DEFAULT_LAYER = layer_type_t::LAYER_OVERLAY;
    static inline constexpr overlay_position_t DEFAULT_OVERLAY_POSITION = overlay_position_t::POSITION_TOP;
    static inline constexpr int32_t DEFAULT_HAPPY_KPM = 0;
    static inline constexpr platform::time_sec_t DEFAULT_IDLE_SLEEP_TIMEOUT_SEC = 0;
    static inline constexpr align_type_t DEFAULT_CAT_ALIGN = align_type_t::ALIGN_CENTER;
    static inline constexpr platform::time_ms_t DEFAULT_TEST_ANIMATION_DURATION_MS = 0;
    static inline constexpr platform::time_sec_t DEFAULT_TEST_ANIMATION_INTERVAL_SEC = 0;
    static inline constexpr int32_t DEFAULT_ENABLE_ANTIALIASING = 1;

    // Debug-specific defaults
#ifndef NDEBUG
    static inline constexpr int32_t DEFAULT_ENABLE_DEBUG = 1;
#else
    static inline constexpr int32_t DEFAULT_ENABLE_DEBUG = 0;
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
    static inline constexpr auto LAYER_KEY                          = "layer";                      ///< DEPRECATED: use overlay_layer
    static inline constexpr auto OVERLAY_LAYER_KEY                  = "overlay_layer";
    static inline constexpr auto CAT_ALIGN_KEY                      = "cat_align";
    static inline constexpr auto IDLE_ANIMATION_KEY                 = "idle_animation";
    static inline constexpr auto INPUT_FPS_KEY                      = "input_fps";
    static inline constexpr auto MIRROR_X_KEY                       = "mirror_x";
    static inline constexpr auto MIRROR_Y_KEY                       = "mirror_y";
    static inline constexpr auto RANDOM_KEY                         = "random";
    static inline constexpr auto RANDOM_ON_RELOAD_KEY               = "random_on_reload";
    static inline constexpr auto ENABLE_ANTIALIASING_KEY            = "enable_antialiasing";
    static inline constexpr auto UPDATE_RATE_KEY                    = "update_rate";
    static inline constexpr auto CPU_THRESHOLD_KEY                  = "cpu_threshold";
    static inline constexpr auto CPU_RUNNING_FACTOR_KEY             = "cpu_running_factor";
    static inline constexpr auto MOVEMENT_RADIUS_KEY                = "movement_radius";
    static inline constexpr auto ENABLE_MOVEMENT_DEBUG_KEY          = "enable_movement_debug";
    static inline constexpr auto MOVEMENT_SPEED_KEY                 = "movement_speed";
    static inline constexpr auto SCREEN_WIDTH_KEY                   = "screen_width";
    static inline constexpr auto MONITOR_KEY                        = "monitor";
    static inline constexpr auto OUTPUT_NAME_KEY                    = "output_name";  // monitor alt key

    static inline constexpr auto CUSTOM_SPRITE_SHEET_FILENAME_KEY   = "custom_sprite_sheet_filename";
    static inline constexpr auto CUSTOM_IDLE_FRAMES_KEY             = "custom_idle_frames";
    static inline constexpr auto CUSTOM_BORING_FRAMES_KEY           = "custom_boring_frames";
    static inline constexpr auto CUSTOM_START_WRITING_FRAMES_KEY    = "custom_start_writing_frames";
    static inline constexpr auto CUSTOM_WRITING_FRAMES_KEY          = "custom_writing_frames";
    static inline constexpr auto CUSTOM_END_WRITING_FRAMES_KEY      = "custom_end_writing_frames";
    static inline constexpr auto CUSTOM_HAPPY_FRAMES_KEY            = "custom_happy_frames";
    static inline constexpr auto CUSTOM_ASLEEP_FRAMES_KEY           = "custom_asleep_frames";
    static inline constexpr auto CUSTOM_SLEEP_FRAMES_KEY            = "custom_sleep_frames";
    static inline constexpr auto CUSTOM_WAKE_UP_FRAMES_KEY          = "custom_wake_up_frames";
    static inline constexpr auto CUSTOM_START_WORKING_FRAMES_KEY    = "custom_start_working_frames";
    static inline constexpr auto CUSTOM_WORKING_FRAMES_KEY          = "custom_working_frames";
    static inline constexpr auto CUSTOM_END_WORKING_FRAMES_KEY      = "custom_end_working_frames";
    static inline constexpr auto CUSTOM_START_MOVING_FRAMES_KEY     = "custom_start_moving_frames";
    static inline constexpr auto CUSTOM_MOVING_FRAMES_KEY           = "custom_moving_frames";
    static inline constexpr auto CUSTOM_END_MOVING_FRAMES_KEY       = "custom_end_moving_frames";
    static inline constexpr auto CUSTOM_START_RUNNING_FRAMES_KEY    = "custom_start_running_frames";
    static inline constexpr auto CUSTOM_RUNNING_FRAMES_KEY          = "custom_running_frames";
    static inline constexpr auto CUSTOM_END_RUNNING_FRAMES_KEY      = "custom_end_running_frames";

    static inline constexpr auto CUSTOM_TOGGLE_WRITING_FRAMES_KEY           = "custom_toggle_writing_frames";
    static inline constexpr auto CUSTOM_TOGGLE_WRITING_FRAMES_RANDOM_KEY    = "custom_toggle_writing_frames_random";
    static inline constexpr auto CUSTOM_MIRROR_X_MOVING_KEY                 = "custom_mirror_x_moving";

    static inline constexpr auto CUSTOM_IDLE_ROW_KEY                = "custom_idle_row";
    static inline constexpr auto CUSTOM_BORING_ROW_KEY              = "custom_boring_row";
    static inline constexpr auto CUSTOM_START_WRITING_ROW_KEY       = "custom_start_writing_row";
    static inline constexpr auto CUSTOM_WRITING_ROW_KEY             = "custom_writing_row";
    static inline constexpr auto CUSTOM_END_WRITING_ROW_KEY         = "custom_end_writing_row";
    static inline constexpr auto CUSTOM_HAPPY_ROW_KEY               = "custom_happy_row";
    static inline constexpr auto CUSTOM_ASLEEP_ROW_KEY              = "custom_asleep_row";
    static inline constexpr auto CUSTOM_SLEEP_ROW_KEY               = "custom_sleep_row";
    static inline constexpr auto CUSTOM_WAKE_UP_ROW_KEY             = "custom_wake_up_row";
    static inline constexpr auto CUSTOM_START_WORKING_ROW_KEY       = "custom_start_working_row";
    static inline constexpr auto CUSTOM_WORKING_ROW_KEY             = "custom_working_row";
    static inline constexpr auto CUSTOM_END_WORKING_ROW_KEY         = "custom_end_working_row";
    static inline constexpr auto CUSTOM_START_MOVING_ROW_KEY        = "custom_start_moving_row";
    static inline constexpr auto CUSTOM_MOVING_ROW_KEY              = "custom_moving_row";
    static inline constexpr auto CUSTOM_END_MOVING_ROW_KEY          = "custom_end_moving_row";
    static inline constexpr auto CUSTOM_START_RUNNING_ROW_KEY       = "custom_start_running_row";
    static inline constexpr auto CUSTOM_RUNNING_ROW_KEY             = "custom_running_row";
    static inline constexpr auto CUSTOM_END_RUNNING_ROW_KEY         = "custom_end_running_row";
    static inline constexpr auto CUSTOM_ROWS_KEY                    = "custom_rows";

    static inline constexpr size_t KEY_BUF = 256;
    static inline constexpr size_t VALUE_BUF = PATH_MAX + 256; // max value + comment
    static inline constexpr size_t LINE_BUF  = KEY_BUF-1 + VALUE_BUF-1 + 1 + 1; // key + '=' + value + '\0'

    // =============================================================================
    // CONFIGURATION VALIDATION MODULE
    // =============================================================================

    static constexpr uint64_t config_clamp_int(int& value, int min, int max, [[maybe_unused]] const char *name) {
        if (value < min || value > max) {
            BONGOCAT_LOG_WARNING("%s %d out of range [%d-%d], clamping", name, value, min, max);
            value = (value < min) ? min : max;
            return (1u << 0);
        }
        return 0;
    }
    static constexpr uint64_t config_clamp_double(double& value, double min, double max, [[maybe_unused]] const char *name) {
        if (value < min || value > max) {
            BONGOCAT_LOG_WARNING("%s %.2f out of range [%.0f-%.0f], clamping", name, value, min, max);
            value = (value < min) ? min : max;
            return (1u << 0);
        }
        return 0;
    }

    static constexpr uint64_t config_validate_max_int(const int& value, int max, [[maybe_unused]] const char *name) {
        if (value > max) {
            BONGOCAT_LOG_WARNING("%s %d out of range [%d], clamping", name, value, max);
            return (1u << 0);
        }
        return 0;
    }

    static uint64_t config_validate_dimensions(config_t& config) {
        uint64_t ret{0};
        ret |= config_clamp_int(config.cat_height, MIN_CAT_HEIGHT, MAX_CAT_HEIGHT, CAT_HEIGHT_KEY);
        ret |= config_clamp_int(config.overlay_height, MIN_OVERLAY_HEIGHT, MAX_OVERLAY_HEIGHT, OVERLAY_HEIGHT_KEY);
        ret |= config_clamp_int(config.cat_x_offset, MIN_OFFSET, MAX_OFFSET, CAT_X_OFFSET_KEY);
        ret |= config_clamp_int(config.cat_y_offset, MIN_OFFSET, MAX_OFFSET, CAT_Y_OFFSET_KEY);
        ret |= config_clamp_int(config.movement_radius, MIN_MOVEMENT_RADIUS, MAX_MOVEMENT_RADIUS, CAT_Y_OFFSET_KEY);
        ret |= config_clamp_int(config.padding_x, 0, MAX_OFFSET, PADDING_X_KEY);
        ret |= config_clamp_int(config.padding_y, 0, MAX_OFFSET, PADDING_Y_KEY);
        ret |= config_clamp_int(config.screen_width, 0, MAX_OFFSET, SCREEN_WIDTH_KEY);
        return ret;
    }

    static uint64_t config_validate_timing(config_t& config) {
        uint64_t ret{0};
        ret |= config_clamp_int(config.fps, MIN_FPS, MAX_FPS, FPS_KEY);
        ret |= config_clamp_int(config.keypress_duration_ms, MIN_DURATION_MS, MAX_DURATION_MS, KEYPRESS_DURATION_KEY);
        ret |= config_clamp_int(config.test_animation_duration_ms, 0, MAX_DURATION_MS, TEST_ANIMATION_DURATION_KEY);
        ret |= config_clamp_int(config.animation_speed_ms, 0, MAX_DURATION_MS, ANIMATION_SPEED_KEY);
        ret |= config_clamp_int(config.idle_sleep_timeout_sec, 0, MAX_SLEEP_TIMEOUT_SEC, IDLE_SLEEP_TIMEOUT_KEY);
        ret |= config_clamp_int(config.input_fps, 0, MAX_FPS, INPUT_FPS_KEY);
        ret |= config_clamp_int(config.movement_speed, 0, MAX_DURATION_MS, MOVEMENT_SPEED_KEY);

        // Validate interval (0 is allowed to disable)
        if (config.test_animation_interval_sec < 0 || config.test_animation_interval_sec > MAX_INTERVAL_SEC) {
            BONGOCAT_LOG_WARNING("%s %d out of range [0-%dsec], clamping",
                                 TEST_ANIMATION_INTERVAL_KEY, config.test_animation_interval_sec, MAX_INTERVAL_SEC);
            config.test_animation_interval_sec = (config.test_animation_interval_sec < 0) ? 0 : MAX_INTERVAL_SEC;
            ret = (1u << 1);
        }
        if (config.animation_speed_ms < 0 || config.animation_speed_ms > MAX_INTERVAL_SEC*1000) {
            BONGOCAT_LOG_WARNING("%s %d out of range [0-%dms], clamping",
                                 ANIMATION_SPEED_KEY, config.test_animation_interval_sec, MAX_INTERVAL_SEC*1000);
            config.animation_speed_ms = (config.animation_speed_ms < 0) ? 0 : MAX_INTERVAL_SEC*1000;
            ret = (1u << 2);
        }
        return ret;
    }

    static uint64_t config_validate_kpm(config_t& config) {
        return config_clamp_int(config.happy_kpm, MIN_KPM, MAX_KPM, HAPPY_KPM_KEY);
    }

    static uint64_t config_validate_update(config_t& config) {
        uint64_t ret{0};

        ret |= config_clamp_int(config.update_rate_ms, 0, MAX_UPDATE_RATE_MS, UPDATE_RATE_KEY);
        ret |= config_clamp_double(config.cpu_threshold, 0, MAX_CPU_THRESHOLD, CPU_THRESHOLD_KEY);
        ret |= config_clamp_double(config.cpu_running_factor, 0, MAX_CPU_RUNNING_FACTOR, CPU_RUNNING_FACTOR_KEY);

        return ret;
    }

    static uint64_t config_validate_custom(config_t& config) {
        using namespace assets;
        uint64_t ret{0};

        if (config._custom) {
            if (config.custom_sprite_sheet_settings.feature_toggle_writing_frames >= 0) {
                config.custom_sprite_sheet_settings.feature_toggle_writing_frames = config.custom_sprite_sheet_settings.feature_toggle_writing_frames ? 1 : 0;
            }
            if (config.custom_sprite_sheet_settings.feature_toggle_writing_frames_random >= 0) {
                config.custom_sprite_sheet_settings.feature_toggle_writing_frames_random = config.custom_sprite_sheet_settings.feature_toggle_writing_frames_random ? 1 : 0;
            }
            if (config.custom_sprite_sheet_settings.feature_mirror_x_moving >= 0) {
                config.custom_sprite_sheet_settings.feature_mirror_x_moving = config.custom_sprite_sheet_settings.feature_mirror_x_moving ? 1 : 0;
            }

            // clamp cols
            ret |= config_clamp_int(config.custom_sprite_sheet_settings.idle_frames, MIN_CUSTOM_FRAMES, MAX_CUSTOM_FRAMES, CUSTOM_IDLE_FRAMES_KEY);

            ret |= config_clamp_int(config.custom_sprite_sheet_settings.boring_frames, MIN_CUSTOM_FRAMES, MAX_CUSTOM_FRAMES, CUSTOM_BORING_FRAMES_KEY);

            ret |= config_clamp_int(config.custom_sprite_sheet_settings.start_writing_frames, MIN_CUSTOM_FRAMES, MAX_CUSTOM_FRAMES, CUSTOM_START_WRITING_FRAMES_KEY);
            ret |= config_clamp_int(config.custom_sprite_sheet_settings.writing_frames, MIN_CUSTOM_FRAMES, MAX_CUSTOM_FRAMES, CUSTOM_WRITING_FRAMES_KEY);
            ret |= config_clamp_int(config.custom_sprite_sheet_settings.end_writing_frames, MIN_CUSTOM_FRAMES, MAX_CUSTOM_FRAMES, CUSTOM_END_WRITING_FRAMES_KEY);
            ret |= config_clamp_int(config.custom_sprite_sheet_settings.happy_frames, MIN_CUSTOM_FRAMES, MAX_CUSTOM_FRAMES, CUSTOM_HAPPY_FRAMES_KEY);

            ret |= config_clamp_int(config.custom_sprite_sheet_settings.asleep_frames, MIN_CUSTOM_FRAMES, MAX_CUSTOM_FRAMES, CUSTOM_ASLEEP_FRAMES_KEY);
            ret |= config_clamp_int(config.custom_sprite_sheet_settings.sleep_frames, MIN_CUSTOM_FRAMES, MAX_CUSTOM_FRAMES, CUSTOM_SLEEP_FRAMES_KEY);
            ret |= config_clamp_int(config.custom_sprite_sheet_settings.wake_up_frames, MIN_CUSTOM_FRAMES, MAX_CUSTOM_FRAMES, CUSTOM_WAKE_UP_FRAMES_KEY);

            ret |= config_clamp_int(config.custom_sprite_sheet_settings.start_working_frames, MIN_CUSTOM_FRAMES, MAX_CUSTOM_FRAMES, CUSTOM_START_WORKING_FRAMES_KEY);
            ret |= config_clamp_int(config.custom_sprite_sheet_settings.working_frames, MIN_CUSTOM_FRAMES, MAX_CUSTOM_FRAMES, CUSTOM_WORKING_FRAMES_KEY);
            ret |= config_clamp_int(config.custom_sprite_sheet_settings.end_working_frames, MIN_CUSTOM_FRAMES, MAX_CUSTOM_FRAMES, CUSTOM_END_WORKING_FRAMES_KEY);

            ret |= config_clamp_int(config.custom_sprite_sheet_settings.start_moving_frames, MIN_CUSTOM_FRAMES, MAX_CUSTOM_FRAMES, CUSTOM_START_MOVING_FRAMES_KEY);
            ret |= config_clamp_int(config.custom_sprite_sheet_settings.moving_frames, MIN_CUSTOM_FRAMES, MAX_CUSTOM_FRAMES, CUSTOM_MOVING_FRAMES_KEY);
            ret |= config_clamp_int(config.custom_sprite_sheet_settings.end_moving_frames, MIN_CUSTOM_FRAMES, MAX_CUSTOM_FRAMES, CUSTOM_END_MOVING_FRAMES_KEY);

            ret |= config_clamp_int(config.custom_sprite_sheet_settings.start_running_frames, MIN_CUSTOM_FRAMES, MAX_CUSTOM_FRAMES, CUSTOM_START_RUNNING_FRAMES_KEY);
            ret |= config_clamp_int(config.custom_sprite_sheet_settings.running_frames, MIN_CUSTOM_FRAMES, MAX_CUSTOM_FRAMES, CUSTOM_RUNNING_FRAMES_KEY);
            ret |= config_clamp_int(config.custom_sprite_sheet_settings.end_running_frames, MIN_CUSTOM_FRAMES, MAX_CUSTOM_FRAMES, CUSTOM_END_RUNNING_FRAMES_KEY);

            // clamp rows
            if (config.custom_sprite_sheet_settings.idle_row_index >= 0) {
                ret |= config_clamp_int(config.custom_sprite_sheet_settings.idle_row_index, MIN_CUSTOM_ROWS, MAX_CUSTOM_ROWS, CUSTOM_IDLE_ROW_KEY);
            }
            if (config.custom_sprite_sheet_settings.boring_row_index >= 0) {
                ret |= config_clamp_int(config.custom_sprite_sheet_settings.boring_row_index, MIN_CUSTOM_ROWS, MAX_CUSTOM_ROWS, CUSTOM_BORING_ROW_KEY);
            }
            if (config.custom_sprite_sheet_settings.start_writing_row_index >= 0) {
                ret |= config_clamp_int(config.custom_sprite_sheet_settings.start_writing_row_index, MIN_CUSTOM_ROWS, MAX_CUSTOM_ROWS, CUSTOM_START_WRITING_ROW_KEY);
            }
            if (config.custom_sprite_sheet_settings.writing_row_index >= 0) {
                ret |= config_clamp_int(config.custom_sprite_sheet_settings.writing_row_index, MIN_CUSTOM_ROWS, MAX_CUSTOM_ROWS, CUSTOM_WRITING_ROW_KEY);
            }
            if (config.custom_sprite_sheet_settings.end_writing_row_index >= 0) {
                ret |= config_clamp_int(config.custom_sprite_sheet_settings.end_writing_row_index, MIN_CUSTOM_ROWS, MAX_CUSTOM_ROWS, CUSTOM_END_WRITING_ROW_KEY);
            }
            if (config.custom_sprite_sheet_settings.happy_row_index >= 0) {
                ret |= config_clamp_int(config.custom_sprite_sheet_settings.happy_row_index, MIN_CUSTOM_ROWS, MAX_CUSTOM_ROWS, CUSTOM_HAPPY_ROW_KEY);
            }
            if (config.custom_sprite_sheet_settings.asleep_row_index >= 0) {
                ret |= config_clamp_int(config.custom_sprite_sheet_settings.asleep_row_index, MIN_CUSTOM_ROWS, MAX_CUSTOM_ROWS, CUSTOM_ASLEEP_ROW_KEY);
            }
            if (config.custom_sprite_sheet_settings.sleep_row_index >= 0) {
                ret |= config_clamp_int(config.custom_sprite_sheet_settings.sleep_row_index, MIN_CUSTOM_ROWS, MAX_CUSTOM_ROWS, CUSTOM_SLEEP_ROW_KEY);
            }
            if (config.custom_sprite_sheet_settings.wake_up_row_index >= 0) {
                ret |= config_clamp_int(config.custom_sprite_sheet_settings.wake_up_row_index, MIN_CUSTOM_ROWS, MAX_CUSTOM_ROWS, CUSTOM_WAKE_UP_ROW_KEY);
            }
            if (config.custom_sprite_sheet_settings.start_working_row_index >= 0) {
                ret |= config_clamp_int(config.custom_sprite_sheet_settings.start_working_row_index, MIN_CUSTOM_ROWS, MAX_CUSTOM_ROWS, CUSTOM_START_WORKING_ROW_KEY);
            }
            if (config.custom_sprite_sheet_settings.working_row_index >= 0) {
                ret |= config_clamp_int(config.custom_sprite_sheet_settings.working_row_index, MIN_CUSTOM_ROWS, MAX_CUSTOM_ROWS, CUSTOM_WORKING_ROW_KEY);
            }
            if (config.custom_sprite_sheet_settings.end_working_row_index >= 0) {
                ret |= config_clamp_int(config.custom_sprite_sheet_settings.end_working_row_index, MIN_CUSTOM_ROWS, MAX_CUSTOM_ROWS, CUSTOM_END_WORKING_ROW_KEY);
            }
            if (config.custom_sprite_sheet_settings.start_moving_row_index >= 0) {
                ret |= config_clamp_int(config.custom_sprite_sheet_settings.start_moving_row_index, MIN_CUSTOM_ROWS, MAX_CUSTOM_ROWS, CUSTOM_START_MOVING_ROW_KEY);
            }
            if (config.custom_sprite_sheet_settings.moving_row_index >= 0) {
                ret |= config_clamp_int(config.custom_sprite_sheet_settings.moving_row_index, MIN_CUSTOM_ROWS, MAX_CUSTOM_ROWS, CUSTOM_MOVING_ROW_KEY);
            }
            if (config.custom_sprite_sheet_settings.end_moving_row_index >= 0) {
                ret |= config_clamp_int(config.custom_sprite_sheet_settings.end_moving_row_index, MIN_CUSTOM_ROWS, MAX_CUSTOM_ROWS, CUSTOM_END_MOVING_ROW_KEY);
            }
            if (config.custom_sprite_sheet_settings.start_running_row_index >= 0) {
                ret |= config_clamp_int(config.custom_sprite_sheet_settings.start_running_row_index, MIN_CUSTOM_ROWS, MAX_CUSTOM_ROWS, CUSTOM_START_RUNNING_ROW_KEY);
            }
            if (config.custom_sprite_sheet_settings.running_row_index >= 0) {
                ret |= config_clamp_int(config.custom_sprite_sheet_settings.running_row_index, MIN_CUSTOM_ROWS, MAX_CUSTOM_ROWS, CUSTOM_RUNNING_ROW_KEY);
            }
            if (config.custom_sprite_sheet_settings.end_running_row_index >= 0) {
                ret |= config_clamp_int(config.custom_sprite_sheet_settings.end_running_row_index, MIN_CUSTOM_ROWS, MAX_CUSTOM_ROWS, CUSTOM_END_RUNNING_ROW_KEY);
            }
            if (config.custom_sprite_sheet_settings.rows >= 0) {
                ret |= config_clamp_int(config.custom_sprite_sheet_settings.rows, 1, MAX_CUSTOM_ROWS, CUSTOM_ROWS_KEY);
            }


            const int sprite_sheet_cols = get_custom_animation_settings_max_cols(config.custom_sprite_sheet_settings);
            const int sprite_sheet_rows = get_custom_animation_settings_rows_count(config.custom_sprite_sheet_settings);

            if (sprite_sheet_cols <= 0) {
                BONGOCAT_LOG_WARNING("custom sprite sheet has no columns");
                ret |= (1u << 3);
            }

            // validate cols
            ret |= config_validate_max_int(config.custom_sprite_sheet_settings.idle_frames, sprite_sheet_cols, CUSTOM_IDLE_FRAMES_KEY);

            ret |= config_validate_max_int(config.custom_sprite_sheet_settings.boring_frames, sprite_sheet_cols, CUSTOM_BORING_FRAMES_KEY);

            ret |= config_validate_max_int(config.custom_sprite_sheet_settings.start_writing_frames, sprite_sheet_cols, CUSTOM_START_WRITING_FRAMES_KEY);
            ret |= config_validate_max_int(config.custom_sprite_sheet_settings.writing_frames, sprite_sheet_cols, CUSTOM_WRITING_FRAMES_KEY);
            ret |= config_validate_max_int(config.custom_sprite_sheet_settings.end_writing_frames, sprite_sheet_cols, CUSTOM_END_WRITING_FRAMES_KEY);
            ret |= config_validate_max_int(config.custom_sprite_sheet_settings.happy_frames, sprite_sheet_cols, CUSTOM_HAPPY_FRAMES_KEY);

            ret |= config_validate_max_int(config.custom_sprite_sheet_settings.asleep_frames, sprite_sheet_cols, CUSTOM_ASLEEP_FRAMES_KEY);
            ret |= config_validate_max_int(config.custom_sprite_sheet_settings.sleep_frames, sprite_sheet_cols, CUSTOM_SLEEP_FRAMES_KEY);
            ret |= config_validate_max_int(config.custom_sprite_sheet_settings.wake_up_frames, sprite_sheet_cols, CUSTOM_WAKE_UP_FRAMES_KEY);

            ret |= config_validate_max_int(config.custom_sprite_sheet_settings.start_working_frames, sprite_sheet_cols, CUSTOM_START_WORKING_FRAMES_KEY);
            ret |= config_validate_max_int(config.custom_sprite_sheet_settings.working_frames, sprite_sheet_cols, CUSTOM_WORKING_FRAMES_KEY);
            ret |= config_validate_max_int(config.custom_sprite_sheet_settings.end_working_frames, sprite_sheet_cols, CUSTOM_END_WORKING_FRAMES_KEY);

            ret |= config_validate_max_int(config.custom_sprite_sheet_settings.start_moving_frames, sprite_sheet_cols, CUSTOM_START_MOVING_FRAMES_KEY);
            ret |= config_validate_max_int(config.custom_sprite_sheet_settings.moving_frames, sprite_sheet_cols, CUSTOM_MOVING_FRAMES_KEY);
            ret |= config_validate_max_int(config.custom_sprite_sheet_settings.end_moving_frames, sprite_sheet_cols, CUSTOM_END_MOVING_FRAMES_KEY);

            ret |= config_validate_max_int(config.custom_sprite_sheet_settings.start_running_frames, sprite_sheet_cols, CUSTOM_START_RUNNING_FRAMES_KEY);
            ret |= config_validate_max_int(config.custom_sprite_sheet_settings.running_frames, sprite_sheet_cols, CUSTOM_RUNNING_FRAMES_KEY);
            ret |= config_validate_max_int(config.custom_sprite_sheet_settings.end_running_frames, sprite_sheet_cols, CUSTOM_END_RUNNING_FRAMES_KEY);

            // validate rows
            if (sprite_sheet_rows > 0) {
                if (config.custom_sprite_sheet_settings.idle_row_index >= 0) {
                    ret |= config_validate_max_int(config.custom_sprite_sheet_settings.idle_row_index, sprite_sheet_rows-1, CUSTOM_IDLE_ROW_KEY);
                }
                if (config.custom_sprite_sheet_settings.boring_row_index >= 0) {
                    ret |= config_validate_max_int(config.custom_sprite_sheet_settings.boring_row_index, sprite_sheet_rows-1, CUSTOM_BORING_ROW_KEY);
                }
                if (config.custom_sprite_sheet_settings.start_writing_row_index >= 0) {
                    ret |= config_validate_max_int(config.custom_sprite_sheet_settings.start_writing_row_index, sprite_sheet_rows-1, CUSTOM_START_WRITING_ROW_KEY);
                }
                if (config.custom_sprite_sheet_settings.writing_row_index >= 0) {
                    ret |= config_validate_max_int(config.custom_sprite_sheet_settings.writing_row_index, sprite_sheet_rows-1, CUSTOM_WRITING_ROW_KEY);
                }
                if (config.custom_sprite_sheet_settings.end_writing_row_index >= 0) {
                    ret |= config_validate_max_int(config.custom_sprite_sheet_settings.end_writing_row_index, sprite_sheet_rows-1, CUSTOM_END_WRITING_ROW_KEY);
                }
                if (config.custom_sprite_sheet_settings.happy_row_index >= 0) {
                    ret |= config_validate_max_int(config.custom_sprite_sheet_settings.happy_row_index, sprite_sheet_rows-1, CUSTOM_HAPPY_ROW_KEY);
                }
                if (config.custom_sprite_sheet_settings.asleep_row_index >= 0) {
                    ret |= config_validate_max_int(config.custom_sprite_sheet_settings.asleep_row_index, sprite_sheet_rows-1, CUSTOM_ASLEEP_ROW_KEY);
                }
                if (config.custom_sprite_sheet_settings.sleep_row_index >= 0) {
                    ret |= config_validate_max_int(config.custom_sprite_sheet_settings.sleep_row_index, sprite_sheet_rows-1, CUSTOM_SLEEP_ROW_KEY);
                }
                if (config.custom_sprite_sheet_settings.wake_up_row_index >= 0) {
                    ret |= config_validate_max_int(config.custom_sprite_sheet_settings.wake_up_row_index, sprite_sheet_rows-1, CUSTOM_WAKE_UP_ROW_KEY);
                }
                if (config.custom_sprite_sheet_settings.start_working_row_index >= 0) {
                    ret |= config_validate_max_int(config.custom_sprite_sheet_settings.start_working_row_index, sprite_sheet_rows-1, CUSTOM_START_WORKING_ROW_KEY);
                }
                if (config.custom_sprite_sheet_settings.working_row_index >= 0) {
                    ret |= config_validate_max_int(config.custom_sprite_sheet_settings.working_row_index, sprite_sheet_rows-1, CUSTOM_WORKING_ROW_KEY);
                }
                if (config.custom_sprite_sheet_settings.end_working_row_index >= 0) {
                    ret |= config_validate_max_int(config.custom_sprite_sheet_settings.end_working_row_index, sprite_sheet_rows-1, CUSTOM_END_WORKING_ROW_KEY);
                }
                if (config.custom_sprite_sheet_settings.start_moving_row_index >= 0) {
                    ret |= config_validate_max_int(config.custom_sprite_sheet_settings.start_moving_row_index, sprite_sheet_rows-1, CUSTOM_START_MOVING_ROW_KEY);
                }
                if (config.custom_sprite_sheet_settings.moving_row_index >= 0) {
                    ret |= config_validate_max_int(config.custom_sprite_sheet_settings.moving_row_index, sprite_sheet_rows-1, CUSTOM_MOVING_ROW_KEY);
                }
                if (config.custom_sprite_sheet_settings.end_moving_row_index >= 0) {
                    ret |= config_validate_max_int(config.custom_sprite_sheet_settings.end_moving_row_index, sprite_sheet_rows-1, CUSTOM_END_MOVING_ROW_KEY);
                }
                if (config.custom_sprite_sheet_settings.start_running_row_index >= 0) {
                    ret |= config_validate_max_int(config.custom_sprite_sheet_settings.start_running_row_index, sprite_sheet_rows-1, CUSTOM_START_RUNNING_ROW_KEY);
                }
                if (config.custom_sprite_sheet_settings.running_row_index >= 0) {
                    ret |= config_validate_max_int(config.custom_sprite_sheet_settings.running_row_index, sprite_sheet_rows-1, CUSTOM_RUNNING_ROW_KEY);
                }
                if (config.custom_sprite_sheet_settings.end_running_row_index >= 0) {
                    ret |= config_validate_max_int(config.custom_sprite_sheet_settings.end_running_row_index, sprite_sheet_rows-1, CUSTOM_END_RUNNING_ROW_KEY);
                }
            } else {
                if (config.custom_sprite_sheet_settings.rows <= 0) {
                    BONGOCAT_LOG_WARNING("custom sprite sheet has no rows");
                    ret |= (1u << 4);
                }
            }


            // validate sprite sheet file
            if (config.custom_sprite_sheet_filename != nullptr && strlen(config.custom_sprite_sheet_filename) != 0) {
                constexpr size_t PNG_SIGNATURE_SIZE = 8;
                constexpr unsigned char PNG_SIGNATURE[PNG_SIGNATURE_SIZE] = {
                    0x89, 'P', 'N', 'G', '\r', '\n', 0x1A, '\n'
                };

                // Try to open the file
                platform::FileDescriptor fd (open(config.custom_sprite_sheet_filename, O_RDONLY));
                if (fd._fd < 0) {
                    BONGOCAT_LOG_ERROR("Custom Sprite Sheet doesn't exist or can't be opened: %s", config.custom_sprite_sheet_filename);
                    ret |= (1u << 6);
                    return ret;
                }

                struct stat st;
                if (fstat(fd._fd, &st) < 0) {
                    BONGOCAT_LOG_ERROR("Custom Sprite Sheet can't be opened: %s", config.custom_sprite_sheet_filename);
                    ret |= (1u << 7);
                    return ret;
                }
                if (st.st_size == 0) {
                    BONGOCAT_LOG_ERROR("Custom Sprite Sheet is an empty file: %s", config.custom_sprite_sheet_filename);
                    ret |= (1u << 8);
                    return ret;
                }

                unsigned char header[PNG_SIGNATURE_SIZE] = {0};
                const ssize_t n = read(fd._fd, header, PNG_SIGNATURE_SIZE);
                if (n < static_cast<ssize_t>(PNG_SIGNATURE_SIZE)) {
                    BONGOCAT_LOG_ERROR("Failed to read PNG header: %s", config.custom_sprite_sheet_filename);
                    ret |= (1u << 9);
                    return ret;
                }
                if (memcmp(header, PNG_SIGNATURE, PNG_SIGNATURE_SIZE) != 0) {
                    BONGOCAT_LOG_ERROR("Invalid PNG signature: %s", config.custom_sprite_sheet_filename);
                    ret |= (1u << 10);
                    return ret;
                }
            } else {
                // empty custom_sprite_sheet_filename
                BONGOCAT_LOG_WARNING("custom_sprite_sheet_filename is empty");
                ret |= (1u << 5);
            }

            // validate frames
            if (config.custom_sprite_sheet_settings.idle_frames <= 0) {
                BONGOCAT_LOG_WARNING("custom sprite sheet needs at least an idle animation");
                ret |= (1u << 11);
            }

            if (config.custom_sprite_sheet_settings.wake_up_frames > 0 &&
                (config.custom_sprite_sheet_settings.asleep_frames <= 0 || config.custom_sprite_sheet_settings.sleep_frames <= 0)) {
                BONGOCAT_LOG_WARNING("custom sprite sheet has a wake up animation, but no sleep animation");
                //ret |= (1u << 12);
                // to hard of an error in strict mode, just print warning
            }

            if (config.custom_sprite_sheet_settings.feature_mirror_x_moving >= 0 &&
                (config.custom_sprite_sheet_settings.start_moving_frames <= 0 && config.custom_sprite_sheet_settings.moving_frames <= 0 && config.custom_sprite_sheet_settings.end_moving_frames <= 0)) {
                BONGOCAT_LOG_WARNING("feature_mirror_x_moving for custom sprite sheet is used, but has no moving animation");
                //ret |= (1u << 13);
            }

            if ((config.custom_sprite_sheet_settings.feature_toggle_writing_frames >= 0 || config.custom_sprite_sheet_settings.feature_toggle_writing_frames_random >= 0) &&
                (config.custom_sprite_sheet_settings.start_writing_frames <= 0 && config.custom_sprite_sheet_settings.writing_frames <= 0 && config.custom_sprite_sheet_settings.end_writing_frames <= 0)) {
                BONGOCAT_LOG_WARNING("feature_toggle_writing_frames for custom sprite sheet is used, but has no writing animation");
                //ret |= (1u << 14);
            }

            if (config.enable_scheduled_sleep >= 0 &&
                (config.custom_sprite_sheet_settings.asleep_frames <= 0 && config.custom_sprite_sheet_settings.sleep_frames <= 0)) {
                BONGOCAT_LOG_WARNING("enable_scheduled_sleep is enabled, but custom sprite sheet has no sleep animation");
                //ret |= (1u << 15);
            }
            if (config.happy_kpm >= 0 &&
                (config.custom_sprite_sheet_settings.happy_frames <= 0)) {
                BONGOCAT_LOG_WARNING("happy_kpm is used, but custom sprite sheet has no happy animation");
                //ret |= (1u << 16);
            }
        }

        return ret;
    }

    static uint64_t config_validate_appearance(config_t& config) {
        using namespace assets;
        using namespace animation;
        uint64_t ret{0};
        // Validate opacity
        ret |= config_clamp_int(config.overlay_opacity, 0, 255, OVERLAY_OPACITY_KEY);

        switch (config.animation_sprite_sheet_layout) {
            case config_animation_sprite_sheet_layout_t::None:
                BONGOCAT_LOG_WARNING("Cant determine sprite sheet layout");
                /// @TODO: move validation error codes (1 << ..) into constants
                ret |= (1u << 17);
                break;
            case config_animation_sprite_sheet_layout_t::Bongocat:
                if constexpr (features::EnableBongocatEmbeddedAssets) {
                    // Validate animation index
                    assert(BONGOCAT_ANIMATIONS_COUNT <= INT_MAX);
                    if (config.animation_index < 0 || config.animation_index >= static_cast<int>(BONGOCAT_ANIMATIONS_COUNT)) {
                        BONGOCAT_LOG_WARNING("%s %d out of range [0-%d], resetting to 0",
                                             ANIMATION_INDEX_KEY, config.animation_index, BONGOCAT_ANIMATIONS_COUNT - 1);
                        config.animation_index = 0;
                        ret |= (1u << 18);
                    }
                    // Validate idle frame
                    assert(animation::BONGOCAT_NUM_FRAMES <= INT_MAX);
                    if (config.idle_frame < 0 || config.idle_frame >= static_cast<int>(BONGOCAT_NUM_FRAMES)) {
                        BONGOCAT_LOG_WARNING("%s %d out of range [0-%d], resetting to 0",
                                             IDLE_FRAME_KEY, config.idle_frame, BONGOCAT_NUM_FRAMES - 1);
                        config.idle_frame = 0;
                        ret |= (1u << 19);
                    }
                }
                break;
            case config_animation_sprite_sheet_layout_t::Dm:
                if constexpr (features::EnableDmEmbeddedAssets) {
                    // Validate animation index
                    assert(DM_ANIMATIONS_COUNT <= INT_MAX);
                    if (config.animation_index < 0 || config.animation_index >= static_cast<int>(DM_ANIMATIONS_COUNT)) {
                        BONGOCAT_LOG_WARNING("%s %d out of range [0-%d], resetting to 0",
                                             ANIMATION_INDEX_KEY, config.animation_index, assets::DM_ANIMATIONS_COUNT - 1);
                        config.animation_index = 0;
                        ret |= (1u << 20);
                    }
                    // Validate idle frame
                    assert(animation::MAX_DIGIMON_FRAMES <= INT_MAX);
                    if (config.idle_frame < 0 || config.idle_frame >= static_cast<int>(animation::MAX_DIGIMON_FRAMES)) {
                        BONGOCAT_LOG_WARNING("%s %d out of range [0-%d], resetting to 0",
                                             IDLE_FRAME_KEY, config.idle_frame, animation::MAX_DIGIMON_FRAMES - 1);
                        config.idle_frame = 0;
                        ret |= (1u << 21);
                    }
                }
                break;
            case config_animation_sprite_sheet_layout_t::Pkmn:
                if constexpr (features::EnablePkmnEmbeddedAssets) {
                    // Validate animation index
                    assert(DM_ANIMATIONS_COUNT <= INT_MAX);
                    if (config.animation_index < 0 || config.animation_index >= static_cast<int>(PKMN_ANIMATIONS_COUNT)) {
                        BONGOCAT_LOG_WARNING("%s %d out of range [0-%d], resetting to 0",
                                             ANIMATION_INDEX_KEY, config.animation_index, assets::PKMN_ANIMATIONS_COUNT - 1);
                        config.animation_index = 0;
                        ret |= (1u << 22);
                    }
                    // Validate idle frame
                    assert(animation::MAX_DIGIMON_FRAMES <= INT_MAX);
                    if (config.idle_frame < 0 || config.idle_frame >= static_cast<int>(MAX_PKMN_FRAMES)) {
                        BONGOCAT_LOG_WARNING("%s %d out of range [0-%d], resetting to 0",
                                             IDLE_FRAME_KEY, config.idle_frame, MAX_PKMN_FRAMES - 1);
                        config.idle_frame = 0;
                        ret |= (1u << 23);
                    }
                }
                break;
            case config_animation_sprite_sheet_layout_t::MsAgent:
                if constexpr (features::EnableMsAgentEmbeddedAssets) {
                    // Validate animation index
                    assert(assets::MS_AGENTS_ANIMATIONS_COUNT <= INT_MAX);
                    if (config.animation_index < 0 || config.animation_index >= static_cast<int>(MS_AGENTS_ANIMATIONS_COUNT)) {
                        BONGOCAT_LOG_WARNING("%s %d out of range [0-%d], resetting to 0",
                                             ANIMATION_INDEX_KEY, config.animation_index, MS_AGENTS_ANIMATIONS_COUNT - 1);
                        config.animation_index = 0;
                        ret |= (1u << 24);
                    }
                    // Validate idle frame
                    assert(assets::MS_AGENT_MAX_SPRITE_SHEET_COL_FRAMES <= INT_MAX);
                    if (config.idle_frame < 0 || config.idle_frame >= static_cast<int>(MS_AGENT_MAX_SPRITE_SHEET_COL_FRAMES)) {
                        BONGOCAT_LOG_WARNING("%s %d out of range [0-%d], resetting to 0",
                                             IDLE_FRAME_KEY, config.idle_frame, MS_AGENT_MAX_SPRITE_SHEET_COL_FRAMES - 1);
                        config.idle_frame = 0;
                        ret |= (1u << 25);
                    }
                }
                break;
            case config_animation_sprite_sheet_layout_t::Custom:
                assert(CUSTOM_ANIM_INDEX <= INT_MAX);
                assert(MAX_MISC_ANIM_INDEX <= INT_MAX);
                if constexpr (features::EnableCustomSpriteSheetsAssets) {
                    if (config._custom) {
                        // Validate animation index
                        if (config.animation_index < 0 || config.animation_index > static_cast<int>(CUSTOM_ANIM_INDEX)) {
                            BONGOCAT_LOG_WARNING("%s %d out of range [%d], resetting to 0",
                                                 ANIMATION_INDEX_KEY, config.animation_index, CUSTOM_ANIM_INDEX);
                            config.animation_index = 0;
                            ret |= (1u << 26);
                        }
                        /// @TODO: validate max (idle) frames
                    }
                }
                if constexpr (features::EnableMiscEmbeddedAssets) {
                    if (!config._custom) {
                        // Validate animation index
                        if (config.animation_index < 0 || config.animation_index > static_cast<int>(MAX_MISC_ANIM_INDEX)) {
                            BONGOCAT_LOG_WARNING("%s %d out of range [0-%d], resetting to 0",
                                                 ANIMATION_INDEX_KEY, config.animation_index, MAX_MISC_ANIM_INDEX);
                            config.animation_index = 0;
                            ret |= (1u << 27);
                        }
                        // Validate idle frame
                        assert(assets::MISC_MAX_SPRITE_SHEET_COL_FRAMES <= INT_MAX);
                        if (config.idle_frame < 0 || config.idle_frame >= static_cast<int>(MISC_MAX_SPRITE_SHEET_COL_FRAMES)) {
                            BONGOCAT_LOG_WARNING("%s %d out of range [0-%d], resetting to 0",
                                                 IDLE_FRAME_KEY, config.idle_frame, assets::MISC_MAX_SPRITE_SHEET_COL_FRAMES - 1);
                            config.idle_frame = 0;
                            ret |= (1u << 28);
                        }
                    }
                }
                break;
            /// @NOTE(assets): 5. add animation_index validation
        }
        return ret;
    }

    static uint32_t config_validate_enums(config_t& config) {
        uint32_t ret{0};
        // Validate layer
        if (config.layer != layer_type_t::LAYER_BACKGROUND &&
            config.layer != layer_type_t::LAYER_BOTTOM &&
            config.layer != layer_type_t::LAYER_TOP &&
            config.layer != layer_type_t::LAYER_OVERLAY) {
            BONGOCAT_LOG_WARNING("Invalid layer %d, resetting to top", config.layer);
            config.layer = layer_type_t::LAYER_TOP;
            ret |= (1uz << 29);
        }

        // Validate overlay_position
        if (config.overlay_position != overlay_position_t::POSITION_TOP && config.overlay_position != overlay_position_t::POSITION_BOTTOM) {
            BONGOCAT_LOG_WARNING("Invalid %s %d, resetting to top", OVERLAY_OPACITY_KEY, config.overlay_position);
            config.overlay_position = overlay_position_t::POSITION_TOP;
            ret |= (1uz << 30);
        }

        // Validate cat_align
        if (config.cat_align != align_type_t::ALIGN_CENTER && config.cat_align != align_type_t::ALIGN_LEFT && config.cat_align != align_type_t::ALIGN_RIGHT) {
            BONGOCAT_LOG_WARNING("Invalid %s %d, resetting to center", CAT_ALIGN_KEY, config.cat_align);
            config.cat_align = align_type_t::ALIGN_CENTER;
            ret |= (1uz << 31);
        }

        return ret;
    }

    static uint64_t config_validate_time(config_t& config) {
        uint64_t ret{0};
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
                ret |= (1uz << 32);
            }
        }
        return ret;
    }

    static bongocat_error_t config_validate(config_t& config) {
        uint64_t ret{0};
        // Normalize boolean values
        config.enable_debug = config.enable_debug ? 1 : 0;
        config.invert_color = config.invert_color ? 1 : 0;
        config.idle_animation = config.idle_animation ? 1 : 0;
        config.enable_scheduled_sleep = config.enable_scheduled_sleep ? 1 : 0;
        config.mirror_x = config.mirror_x ? 1 : 0;
        config.mirror_y = config.mirror_y ? 1 : 0;
        config.randomize_index = config.randomize_index ? 1 : 0;
        config.randomize_on_reload = config.randomize_on_reload ? 1 : 0;
        config.enable_antialiasing = config.enable_antialiasing ? 1 : 0;
        config.enable_movement_debug = config.enable_movement_debug ? 1 : 0;

        ret |= config_validate_dimensions(config);
        ret |= config_validate_timing(config);
        ret |= config_validate_appearance(config);
        ret |= config_validate_enums(config);
        ret |= config_validate_time(config);
        ret |= config_validate_kpm(config);
        ret |= config_validate_update(config);
        ret |= config_validate_custom(config);

        if (config._strict) {
            if (ret != 0) [[unlikely]] {
                BONGOCAT_LOG_ERROR("Failed to load configuration in strict mode: %x", ret);
                return bongocat_error_t::BONGOCAT_ERROR_INVALID_PARAM;
            }
        }
        return bongocat_error_t::BONGOCAT_SUCCESS;
    }

    // =============================================================================
    // DEVICE MANAGEMENT MODULE
    // =============================================================================

    static bongocat_error_t config_add_keyboard_device(config_t& config, const char *device_path) {
        BONGOCAT_CHECK_NULL(device_path, bongocat_error_t::BONGOCAT_ERROR_INVALID_PARAM);

        assert(config.num_keyboard_devices >= 0 && config.num_keyboard_devices < INT_MAX-1);

        const int old_num_keyboard_devices = config.num_keyboard_devices;

        assert(input::MAX_INPUT_DEVICES <= INT_MAX);
        if (old_num_keyboard_devices >= static_cast<int>(input::MAX_INPUT_DEVICES)) {
            BONGOCAT_LOG_WARNING("Can not add more devices from config, max. reach: %d", input::MAX_INPUT_DEVICES);
            return config._strict ? bongocat_error_t::BONGOCAT_ERROR_INVALID_PARAM : bongocat_error_t::BONGOCAT_SUCCESS;
        }
        const int new_num_keyboard_devices = old_num_keyboard_devices + 1;
        assert(new_num_keyboard_devices >= 0);
        assert(static_cast<size_t>(new_num_keyboard_devices) <= input::MAX_INPUT_DEVICES);

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
        for (size_t i = 0; i < input::MAX_INPUT_DEVICES; i++) {
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

    static char* config_trim_str(char *key) {
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
        errno = 0;
        char* endptr_int = nullptr;
        const int int_value = static_cast<int>(strtol(value, &endptr_int, 10));
        if (errno != 0 || endptr_int == value || *endptr_int != '\0') {
            return bongocat_error_t::BONGOCAT_ERROR_INVALID_PARAM;
        }

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
        } else if (strcmp(key, MIRROR_X_KEY) == 0) {
            config.mirror_x = int_value;
        } else if (strcmp(key, MIRROR_Y_KEY) == 0) {
            config.mirror_y = int_value;
        } else if (strcmp(key, ENABLE_ANTIALIASING_KEY) == 0) {
            config.enable_antialiasing = int_value;
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
        } else if (strcmp(key, RANDOM_KEY) == 0) {
            config.randomize_index = int_value;
        } else if (strcmp(key, RANDOM_ON_RELOAD_KEY) == 0) {
            config.randomize_on_reload = int_value;
        } else if (strcmp(key, UPDATE_RATE_KEY) == 0) {
            config.update_rate_ms = int_value;
        } else if (strcmp(key, CPU_THRESHOLD_KEY) == 0) {
            config.cpu_threshold = int_value;
        } else if (strcmp(key, CPU_RUNNING_FACTOR_KEY) == 0) {
            config.cpu_running_factor = int_value;
        } else if (strcmp(key, MOVEMENT_RADIUS_KEY) == 0) {
            config.movement_radius = int_value;
        } else if (strcmp(key, ENABLE_MOVEMENT_DEBUG_KEY) == 0) {
            config.enable_movement_debug = int_value;
        } else if (strcmp(key, MOVEMENT_SPEED_KEY) == 0) {
            config.movement_speed = int_value;
        } else if (strcmp(key, SCREEN_WIDTH_KEY) == 0) {
            config.screen_width = int_value;
        } else if (strcmp(key, CUSTOM_IDLE_FRAMES_KEY) == 0) {
            config.custom_sprite_sheet_settings.idle_frames = int_value;
        } else if (strcmp(key, CUSTOM_BORING_FRAMES_KEY) == 0) {
            config.custom_sprite_sheet_settings.boring_frames = int_value;
        } else if (strcmp(key, CUSTOM_START_WRITING_FRAMES_KEY) == 0) {
            config.custom_sprite_sheet_settings.start_writing_frames = int_value;
        } else if (strcmp(key, CUSTOM_WRITING_FRAMES_KEY) == 0) {
            config.custom_sprite_sheet_settings.writing_frames = int_value;
        } else if (strcmp(key, CUSTOM_END_WRITING_FRAMES_KEY) == 0) {
            config.custom_sprite_sheet_settings.end_writing_frames = int_value;
        } else if (strcmp(key, CUSTOM_HAPPY_FRAMES_KEY) == 0) {
            config.custom_sprite_sheet_settings.happy_frames = int_value;
        } else if (strcmp(key, CUSTOM_ASLEEP_FRAMES_KEY) == 0) {
            config.custom_sprite_sheet_settings.asleep_frames = int_value;
        } else if (strcmp(key, CUSTOM_SLEEP_FRAMES_KEY) == 0) {
            config.custom_sprite_sheet_settings.sleep_frames = int_value;
        } else if (strcmp(key, CUSTOM_WAKE_UP_FRAMES_KEY) == 0) {
            config.custom_sprite_sheet_settings.wake_up_frames = int_value;
        } else if (strcmp(key, CUSTOM_START_WORKING_FRAMES_KEY) == 0) {
            config.custom_sprite_sheet_settings.start_working_frames = int_value;
        } else if (strcmp(key, CUSTOM_WORKING_FRAMES_KEY) == 0) {
            config.custom_sprite_sheet_settings.working_frames = int_value;
        } else if (strcmp(key, CUSTOM_END_WORKING_FRAMES_KEY) == 0) {
            config.custom_sprite_sheet_settings.end_working_frames = int_value;
        } else if (strcmp(key, CUSTOM_START_MOVING_FRAMES_KEY) == 0) {
            config.custom_sprite_sheet_settings.start_moving_frames = int_value;
        } else if (strcmp(key, CUSTOM_MOVING_FRAMES_KEY) == 0) {
            config.custom_sprite_sheet_settings.moving_frames = int_value;
        } else if (strcmp(key, CUSTOM_END_MOVING_FRAMES_KEY) == 0) {
            config.custom_sprite_sheet_settings.end_moving_frames = int_value;
        } else if (strcmp(key, CUSTOM_START_RUNNING_FRAMES_KEY) == 0) {
            config.custom_sprite_sheet_settings.start_running_frames = int_value;
        } else if (strcmp(key, CUSTOM_RUNNING_FRAMES_KEY) == 0) {
            config.custom_sprite_sheet_settings.running_frames = int_value;
        } else if (strcmp(key, CUSTOM_END_RUNNING_FRAMES_KEY) == 0) {
            config.custom_sprite_sheet_settings.end_running_frames = int_value;
        } else if (strcmp(key, CUSTOM_TOGGLE_WRITING_FRAMES_KEY) == 0) {
            config.custom_sprite_sheet_settings.feature_toggle_writing_frames = int_value;
        } else if (strcmp(key, CUSTOM_TOGGLE_WRITING_FRAMES_RANDOM_KEY) == 0) {
            config.custom_sprite_sheet_settings.feature_toggle_writing_frames_random = int_value;
        } else if (strcmp(key, CUSTOM_MIRROR_X_MOVING_KEY) == 0) {
            config.custom_sprite_sheet_settings.feature_mirror_x_moving = int_value;
        } else if (strcmp(key, CUSTOM_IDLE_ROW_KEY) == 0) {
            config.custom_sprite_sheet_settings.idle_row_index = int_value - 1;
        } else if (strcmp(key, CUSTOM_BORING_ROW_KEY) == 0) {
            config.custom_sprite_sheet_settings.boring_row_index = int_value - 1;
        } else if (strcmp(key, CUSTOM_START_WRITING_ROW_KEY) == 0) {
            config.custom_sprite_sheet_settings.start_writing_row_index = int_value - 1;
        } else if (strcmp(key, CUSTOM_WRITING_ROW_KEY) == 0) {
            config.custom_sprite_sheet_settings.writing_row_index = int_value - 1;
        } else if (strcmp(key, CUSTOM_END_WRITING_ROW_KEY) == 0) {
            config.custom_sprite_sheet_settings.end_writing_row_index = int_value - 1;
        } else if (strcmp(key, CUSTOM_HAPPY_ROW_KEY) == 0) {
            config.custom_sprite_sheet_settings.happy_row_index = int_value - 1;
        } else if (strcmp(key, CUSTOM_ASLEEP_ROW_KEY) == 0) {
            config.custom_sprite_sheet_settings.asleep_row_index = int_value - 1;
        } else if (strcmp(key, CUSTOM_SLEEP_ROW_KEY) == 0) {
            config.custom_sprite_sheet_settings.sleep_row_index = int_value - 1;
        } else if (strcmp(key, CUSTOM_WAKE_UP_ROW_KEY) == 0) {
            config.custom_sprite_sheet_settings.wake_up_row_index = int_value - 1;
        } else if (strcmp(key, CUSTOM_START_WORKING_ROW_KEY) == 0) {
            config.custom_sprite_sheet_settings.start_working_row_index = int_value - 1;
        } else if (strcmp(key, CUSTOM_WORKING_ROW_KEY) == 0) {
            config.custom_sprite_sheet_settings.working_row_index = int_value - 1;
        } else if (strcmp(key, CUSTOM_END_WORKING_ROW_KEY) == 0) {
            config.custom_sprite_sheet_settings.end_working_row_index = int_value - 1;
        } else if (strcmp(key, CUSTOM_START_MOVING_ROW_KEY) == 0) {
            config.custom_sprite_sheet_settings.start_moving_row_index = int_value - 1;
        } else if (strcmp(key, CUSTOM_MOVING_ROW_KEY) == 0) {
            config.custom_sprite_sheet_settings.moving_row_index = int_value - 1;
        } else if (strcmp(key, CUSTOM_END_MOVING_ROW_KEY) == 0) {
            config.custom_sprite_sheet_settings.end_moving_row_index = int_value - 1;
        } else if (strcmp(key, CUSTOM_START_RUNNING_ROW_KEY) == 0) {
            config.custom_sprite_sheet_settings.start_running_row_index = int_value - 1;
        } else if (strcmp(key, CUSTOM_RUNNING_ROW_KEY) == 0) {
            config.custom_sprite_sheet_settings.running_row_index = int_value - 1;
        } else if (strcmp(key, CUSTOM_END_RUNNING_ROW_KEY) == 0) {
            config.custom_sprite_sheet_settings.end_running_row_index = int_value - 1;
        } else if (strcmp(key, CUSTOM_ROWS_KEY) == 0) {
            config.custom_sprite_sheet_settings.rows = int_value;
        } else {
            return bongocat_error_t::BONGOCAT_ERROR_INVALID_PARAM; // Unknown key
        }

        return bongocat_error_t::BONGOCAT_SUCCESS;
    }

    static bongocat_error_t config_parse_double_key(config_t& config, const char *key, const char *value) {
        errno = 0;
        char* endptr_double = nullptr;
        const double double_value = strtod(value, &endptr_double);
        if (errno != 0 || endptr_double == value || *endptr_double != '\0') {
            return bongocat_error_t::BONGOCAT_ERROR_INVALID_PARAM;
        }

        if (strcmp(key, CPU_THRESHOLD_KEY) == 0) {
            config.cpu_threshold = double_value;
        } else if (strcmp(key, CPU_RUNNING_FACTOR_KEY) == 0) {
            config.cpu_running_factor = double_value;
        } else {
            return bongocat_error_t::BONGOCAT_ERROR_INVALID_PARAM; // Unknown key
        }

        return bongocat_error_t::BONGOCAT_SUCCESS;
    }

    static bongocat_error_t config_parse_enum_key(config_t& config, const char *key, const char *value) {
        if (strcmp(key, LAYER_KEY) == 0 || strcmp(key, OVERLAY_LAYER_KEY) == 0) {
            if (strcmp(value, LAYER_TOP_STR) == 0) {
                config.layer = layer_type_t::LAYER_TOP;
            } else if (strcmp(value, LAYER_OVERLAY_STR) == 0) {
                config.layer = layer_type_t::LAYER_OVERLAY;
            } else if (strcmp(value, LAYER_BOTTOM_STR) == 0) {
                config.layer = layer_type_t::LAYER_BOTTOM;
            } else if (strcmp(value, LAYER_BACKGROUND_STR) == 0) {
                config.layer = layer_type_t::LAYER_BACKGROUND;
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
    static bongocat_error_t config_parse_string(config_t& config, const char *key, const char *value, const load_config_overwrite_parameters_t& overwrite_parameters) {
        using namespace assets;
        if (strcmp(key, MONITOR_KEY) == 0 || strcmp(key, OUTPUT_NAME_KEY) == 0) {
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
        } else if (strcmp(key, CUSTOM_SPRITE_SHEET_FILENAME_KEY) == 0) {
            if (config.custom_sprite_sheet_filename) {
                ::free(config.custom_sprite_sheet_filename);
                config.custom_sprite_sheet_filename = nullptr;
            }
            if (value && value[0] != '\0') {
                config.custom_sprite_sheet_filename = strdup(value);
                if (!config.custom_sprite_sheet_filename) {
                    BONGOCAT_LOG_ERROR("Failed to allocate memory for custom sprite sheet filename");
                    return bongocat_error_t::BONGOCAT_ERROR_MEMORY;
                }
            } else {
                config.custom_sprite_sheet_filename = nullptr;
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
            using namespace assets;
            if (overwrite_parameters.animation_name) {
                value = overwrite_parameters.animation_name;
            }

            // set config._animation_name
            if (config._animation_name) ::free(config._animation_name);
            config._animation_name = nullptr;
            config._animation_name = value ? strdup(value) : nullptr;

            // reset state
            config.animation_sprite_sheet_layout = config_animation_sprite_sheet_layout_t::None;
            config.animation_dm_set = config_animation_dm_set_t::None;
            config.animation_custom_set = config_animation_custom_set_t::None;
            config.animation_index = -1;

            // is fully name like dm:..., dm20:..., dmc:...
            [[maybe_unused]] const bool is_fqn = strchr(value, ':') != nullptr;
            bool animation_found = false;

            if constexpr (features::EnableBongocatEmbeddedAssets) {
                // check for bongocat
                if (strcmp(value, BONGOCAT_NAME) == 0 ||
                    strcmp(value, BONGOCAT_ID) == 0 ||
                    strcmp(value, BONGOCAT_FQID) == 0 ||
                    strcmp(value, BONGOCAT_FQNAME) == 0) {
                    config.animation_index = BONGOCAT_ANIM_INDEX;
                    config.animation_sprite_sheet_layout = config_animation_sprite_sheet_layout_t::Bongocat;
                }

                animation_found = config.animation_index >= 0;
            }

            // check for dm
            if constexpr (features::EnableDmEmbeddedAssets) {
                using namespace assets;
#ifdef FEATURE_MIN_DM_EMBEDDED_ASSETS
                if ((!is_fqn && animation_found) || (is_fqn && !animation_found) || (!is_fqn && !animation_found)) {    // overwrite animation when needed, priorities the fq names
#include "min_dm_config_parse_enum_key.cpp.inl"
                    if (config.animation_index >= 0) {
                        BONGOCAT_LOG_DEBUG("Animation found for %s", value);
                    }
                }
                animation_found = config.animation_index >= 0;
#endif

                /// @TODO: use macros (or templates) to reduce copy&paste code

                /// @NOTE(assets): 3. add more dm versions here, config animation_name parsing
#ifdef FEATURE_DM_EMBEDDED_ASSETS
                if ((!is_fqn && animation_found) || (is_fqn && !animation_found) || (!is_fqn && !animation_found)) {    // overwrite animation when needed, priorities the fq names
                    const int found_index = config_parse_animation_name_dm(config, value);
                    if (found_index >= 0) {
                        assert(found_index >= 0);
                        BONGOCAT_LOG_DEBUG("Animation found for %s: %s", value, get_config_animation_name_dm(static_cast<size_t>(found_index)).fqname);
                    }
                    animation_found = config.animation_index >= 0;
                }
#endif
#ifdef FEATURE_DM20_EMBEDDED_ASSETS
                // overwrite animation when not found or full name
                if ((!is_fqn && animation_found) || (is_fqn && !animation_found) || (!is_fqn && !animation_found)) {
                    const int found_index = config_parse_animation_name_dm20(config, value);
                    if (found_index >= 0) {
                        assert(found_index >= 0);
                        BONGOCAT_LOG_DEBUG("Animation found for %s: %s", value, get_config_animation_name_dm20(static_cast<size_t>(found_index)).fqname);
                    }
                    animation_found = config.animation_index >= 0;
                }
#endif
#ifdef FEATURE_DMX_EMBEDDED_ASSETS
                // overwrite animation when not found or full name
                if ((!is_fqn && animation_found) || (is_fqn && !animation_found) || (!is_fqn && !animation_found)) {
                    const int found_index = config_parse_animation_name_dmx(config, value);
                    if (found_index >= 0) {
                        assert(found_index >= 0);
                        BONGOCAT_LOG_DEBUG("Animation found for %s: %s", value, get_config_animation_name_dmx(static_cast<size_t>(found_index)).fqname);
                    }
                    animation_found = config.animation_index >= 0;
                }
#endif
#ifdef FEATURE_DMC_EMBEDDED_ASSETS
                // overwrite animation when not found or full name
                if ((!is_fqn && animation_found) || (is_fqn && !animation_found) || (!is_fqn && !animation_found)) {
                    const int found_index = config_parse_animation_name_dmc(config, value);
                    if (found_index >= 0) {
                        assert(config.animation_index >= 0);
                        BONGOCAT_LOG_DEBUG("Animation found for %s: %s", value, get_config_animation_name_dmc(static_cast<size_t>(found_index)).fqname);
                    }
                    animation_found = config.animation_index >= 0;
                }
#endif
#ifdef FEATURE_PEN_EMBEDDED_ASSETS
                // overwrite animation when not found or full name
                if ((!is_fqn && animation_found) || (is_fqn && !animation_found) || (!is_fqn && !animation_found)) {
                    const int found_index = config_parse_animation_name_pen(config, value);
                    if (found_index >= 0) {
                        assert(found_index >= 0);
                        BONGOCAT_LOG_DEBUG("Animation found for %s: %s", value, get_config_animation_name_pen(static_cast<size_t>(found_index)).fqname);
                    }
                    animation_found = config.animation_index >= 0;
                }
#endif
#ifdef FEATURE_PEN20_EMBEDDED_ASSETS
                // overwrite animation when not found or full name
                if ((!is_fqn && animation_found) || (is_fqn && !animation_found) || (!is_fqn && !animation_found)) {
                    const int found_index = config_parse_animation_name_pen20(config, value);
                    if (found_index >= 0) {
                        assert(found_index >= 0);
                        BONGOCAT_LOG_DEBUG("Animation found for %s: %s", value, get_config_animation_name_pen20(static_cast<size_t>(found_index)).fqname);
                    }
                    animation_found = config.animation_index >= 0;
                }
#endif
#ifdef FEATURE_DMALL_EMBEDDED_ASSETS
                // overwrite animation when not found or full name
                if ((!is_fqn && animation_found) || (is_fqn && !animation_found) || (!is_fqn && !animation_found)) {
                    const int found_index = config_parse_animation_name_dmall(config, value);
                    if (found_index >= 0) {
                        assert(found_index >= 0);
                        BONGOCAT_LOG_DEBUG("Animation found for %s: %s", value, get_config_animation_name_dmall(static_cast<size_t>(found_index)).fqname);
                    }
                    animation_found = config.animation_index >= 0;
                }
#endif
            }

            // check for MS agent
            if constexpr (features::EnableMsAgentEmbeddedAssets) {
                // check for ms pets (clippy)
                if (strcmp(value, CLIPPY_NAME) == 0 ||
                    strcmp(value, CLIPPY_ID) == 0 ||
                    strcmp(value, CLIPPY_FQID) == 0 ||
                    strcmp(value, CLIPPY_FQNAME) == 0) {
                    config.animation_index = CLIPPY_ANIM_INDEX;
                    config.animation_sprite_sheet_layout = config_animation_sprite_sheet_layout_t::MsAgent;
                }
#ifdef FEATURE_MORE_MS_AGENT_EMBEDDED_ASSETS
                /// @NOTE(assets): 4. add more MS Agents here
                // Links
                if (strcmp(value, LINKS_NAME) == 0 ||
                    strcmp(value, LINKS_ID) == 0 ||
                    strcmp(value, LINKS_FQID) == 0 ||
                    strcmp(value, LINKS_FQNAME) == 0) {
                    config.animation_index = LINKS_ANIM_INDEX;
                    config.animation_sprite_sheet_layout = config_animation_sprite_sheet_layout_t::MsAgent;
                }
                // Rover
                if (strcmp(value, ROVER_NAME) == 0 ||
                    strcmp(value, ROVER_ID) == 0 ||
                    strcmp(value, ROVER_FQID) == 0 ||
                    strcmp(value, ROVER_FQNAME) == 0) {
                    config.animation_index = ROVER_ANIM_INDEX;
                    config.animation_sprite_sheet_layout = config_animation_sprite_sheet_layout_t::MsAgent;
                }
                // Merlin
                if (strcmp(value, MERLIN_NAME) == 0 ||
                    strcmp(value, MERLIN_ID) == 0 ||
                    strcmp(value, MERLIN_FQID) == 0 ||
                    strcmp(value, MERLIN_FQNAME) == 0) {
                    config.animation_index = MERLIN_ANIM_INDEX;
                    config.animation_sprite_sheet_layout = config_animation_sprite_sheet_layout_t::MsAgent;
                }
#endif

                animation_found = config.animation_index >= 0;
            }

            // check for pkmn
            if constexpr (features::EnablePkmnEmbeddedAssets) {
                using namespace assets;
#ifdef FEATURE_PKMN_EMBEDDED_ASSETS
                if ((!is_fqn && animation_found) || (is_fqn && !animation_found) || (!is_fqn && !animation_found)) {
                    const int found_index = config_parse_animation_name_pkmn(config, value);
                    if (found_index >= 0) {
                        assert(found_index >= 0);
                        BONGOCAT_LOG_DEBUG("Animation found for %s: %s", value, get_config_animation_name_pkmn(static_cast<size_t>(found_index)).fqname);
                    }
                    animation_found = config.animation_index >= 0;
                }
#endif
            }
            // check for pmd (pkmn)
            if constexpr (features::EnablePmdEmbeddedAssets) {
                using namespace assets;
#ifdef FEATURE_PMD_EMBEDDED_ASSETS
                if ((!is_fqn && animation_found) || (is_fqn && !animation_found) || (!is_fqn && !animation_found)) {
                    const int found_index = config_parse_animation_name_pmd(config, value);
                    if (found_index >= 0) {
                        assert(found_index >= 0);
                        BONGOCAT_LOG_DEBUG("Animation found for %s: %s", value, get_config_animation_name_pmd(static_cast<size_t>(found_index)).fqname);
                    }
                    animation_found = config.animation_index >= 0;
                }
#endif
            }

            // check for Misc (neko)
            if constexpr (features::EnableMiscEmbeddedAssets) {
                // check neko
                if (strcmp(value, MISC_NEKO_NAME) == 0 ||
                    strcmp(value, MISC_NEKO_ID) == 0 ||
                    strcmp(value, MISC_NEKO_FQID) == 0 ||
                    strcmp(value, MISC_NEKO_FQNAME) == 0) {
                    config.animation_index = MISC_NEKO_ANIM_INDEX;
                    config.animation_sprite_sheet_layout = config_animation_sprite_sheet_layout_t::Custom;
                    config.animation_custom_set = config_animation_custom_set_t::misc;
                    animation_found = config.animation_index >= 0;
                }
            }
            /// @NOTE(assets): 4. add more config animation_name parsring here

            // check for custom sprite sheet
            if constexpr (features::EnableCustomSpriteSheetsAssets) {
                // check custom
                if (strcmp(value, CUSTOM_NAME) == 0 ||
                    strcmp(value, CUSTOM_ID) == 0) {
                    config.animation_index = CUSTOM_ANIM_INDEX;
                    config.animation_sprite_sheet_layout = config_animation_sprite_sheet_layout_t::Custom;
                    config.animation_custom_set = config_animation_custom_set_t::custom;
                    animation_found = config.animation_index >= 0;
                    config._custom = config.animation_index == CUSTOM_ANIM_INDEX;
                }
            }

            animation_found = config.animation_index >= 0 && config.animation_sprite_sheet_layout != config_animation_sprite_sheet_layout_t::None;
            if (!animation_found) {
                if (config.animation_index >= 0 && config.animation_sprite_sheet_layout == config_animation_sprite_sheet_layout_t::None) {
                    BONGOCAT_LOG_WARNING("animation_index is set, but not animation_type (unknown type for index=%i and value='%s')", config.animation_index, value);
                }
                if (config._strict) {
                    BONGOCAT_LOG_ERROR("Invalid %s '%s'", ANIMATION_NAME_KEY, value, BONGOCAT_NAME);
                    return bongocat_error_t::BONGOCAT_ERROR_INVALID_PARAM;
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

    static bongocat_error_t config_parse_key_value(config_t& config, const char *key, const char *value, const load_config_overwrite_parameters_t& overwrite_parameters) {
        // Try integer keys first
        if (config_parse_integer_key(config, key, value) == bongocat_error_t::BONGOCAT_SUCCESS) {
            return bongocat_error_t::BONGOCAT_SUCCESS;
        }
        // Try double keys first
        if (config_parse_double_key(config, key, value) == bongocat_error_t::BONGOCAT_SUCCESS) {
            return bongocat_error_t::BONGOCAT_SUCCESS;
        }

        // Try enum keys
        if (config_parse_enum_key(config, key, value) == bongocat_error_t::BONGOCAT_SUCCESS) {
            return bongocat_error_t::BONGOCAT_SUCCESS;
        }

        // Try string
        if (config_parse_string(config, key, value, overwrite_parameters) == bongocat_error_t::BONGOCAT_SUCCESS) {
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


    static bongocat_error_t config_parse_file(FILE *file, config_t& config, const load_config_overwrite_parameters_t& overwrite_parameters) {
        char line[LINE_BUF] = {0};
        char key[KEY_BUF] = {0};
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
            static_assert(VALUE_BUF >= PATH_MAX);
            static_assert(255 < KEY_BUF);
            static_assert(4351 < VALUE_BUF);
            if (sscanf(line, " %255[^=]=%4351[^\n]", key, value) == 2) {
                // Cut off trailing comment in value
                char *comment = strchr(value, '#');
                if (comment) {
                    *comment = '\0';  // terminate string before '#'
                }

                char *trimmed_key = config_trim_str(key);
                char *trimmed_value = config_trim_str(value);

                bongocat_error_t parse_result = config_parse_key_value(config, trimmed_key, trimmed_value, overwrite_parameters);
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

        return result;
    }

    static bongocat_error_t config_parse_file(config_t& config, const char *config_file_path, load_config_overwrite_parameters_t overwrite_parameters) {
        const char *file_path = config_file_path ? config_file_path : DEFAULT_CONFIG_FILE_PATH;

        FILE *file = fopen(file_path, "r");
        if (!file) {
            if (overwrite_parameters.strict >= 0) {
                BONGOCAT_LOG_INFO("Config file '%s' not found", file_path);
                return bongocat_error_t::BONGOCAT_ERROR_FILE_IO;
            }
            BONGOCAT_LOG_INFO("Config file '%s' not found, using defaults", file_path);
            return bongocat_error_t::BONGOCAT_SUCCESS;
        }

        bongocat_error_t result = config_parse_file(file, config, overwrite_parameters);

        fclose(file);

        if (result == bongocat_error_t::BONGOCAT_SUCCESS) {
            BONGOCAT_LOG_INFO("Loaded configuration from %s", file_path);
        }

        return result;
    }

    static bongocat_error_t config_parse_stdin(config_t& config, const load_config_overwrite_parameters_t& overwrite_parameters) {
        FILE *file = stdin;

        bongocat_error_t result = config_parse_file(file, config, overwrite_parameters);
        if (result == bongocat_error_t::BONGOCAT_SUCCESS) {
            BONGOCAT_LOG_INFO("Loaded configuration from stdin");
        }

        return result;
    }

    // =============================================================================
    // DEFAULT CONFIGURATION MODULE
    // =============================================================================

    void set_defaults(config_t& config) {
        config_t cfg{};

        cfg.output_name = nullptr;
        assert(input::MAX_INPUT_DEVICES <= INT_MAX);
        for (int i = 0; i < static_cast<int>(input::MAX_INPUT_DEVICES); i++) {
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
        cfg.mirror_x = 0;
        cfg.mirror_y = 0;
        cfg.enable_antialiasing = DEFAULT_ENABLE_ANTIALIASING;
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
        cfg.animation_dm_set = config_animation_dm_set_t::None;
        cfg.animation_custom_set = config_animation_custom_set_t::None;
        cfg.idle_animation = 0;
        cfg.input_fps = 0;          // when 0 fallback to fps
        cfg.randomize_index = 0;
        cfg.randomize_on_reload = 0;
        cfg.screen_width = 0;
        cfg.custom_sprite_sheet_settings = {};
        cfg._keep_old_animation_index = false;
        cfg._strict = false;
        cfg._custom = false;
        cfg.custom_sprite_sheet_filename = nullptr;
        cfg._animation_name = nullptr;

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
                BONGOCAT_LOG_DEBUG("  dm: %03d/%03d (set=%d) at offset (%d,%d)",
                                   config.animation_index, DM_ANIMATIONS_COUNT, config.animation_dm_set,
                                   config.cat_x_offset, config.cat_y_offset);
                break;
            case config_animation_sprite_sheet_layout_t::Pkmn:
                BONGOCAT_LOG_DEBUG("  pkmn: %03d at offset (%d,%d)",
                                   config.animation_index,
                                   config.cat_x_offset, config.cat_y_offset);
                break;
            case config_animation_sprite_sheet_layout_t::MsAgent:
                BONGOCAT_LOG_DEBUG("  MS Agent: %02d at offset (%d,%d)",
                                   config.animation_index,
                                   config.cat_x_offset, config.cat_y_offset);
                break;
            case config_animation_sprite_sheet_layout_t::Custom:
                assert(MAX_MISC_ANIM_INDEX <= INT32_MAX);
                if (config.animation_custom_set == config_animation_custom_set_t::misc) {
                    BONGOCAT_LOG_DEBUG("  Misc: %03d/%03d at offset (%d,%d)",
                                       config.animation_index, MAX_MISC_ANIM_INDEX,
                                       config.cat_x_offset, config.cat_y_offset);
                } else if (config.animation_custom_set == config_animation_custom_set_t::custom) {
                    BONGOCAT_LOG_DEBUG("  Custom: %s at offset (%d,%d)", config.custom_sprite_sheet_filename,
                                       config.cat_x_offset, config.cat_y_offset);
                }
                break;
        }
        BONGOCAT_LOG_DEBUG("  FPS: %d, Opacity: %d, Random: %d", config.fps, config.overlay_opacity, config.randomize_index);
        BONGOCAT_LOG_DEBUG("  Mirror: X=%d, Y=%d", config.mirror_x, config.mirror_y);
        BONGOCAT_LOG_DEBUG("  Anti-aliasing: %s", config.enable_antialiasing ? "enabled" : "disabled");
        BONGOCAT_LOG_DEBUG("  Position: %s", config.overlay_position == overlay_position_t::POSITION_TOP ? "top" : "bottom");
        BONGOCAT_LOG_DEBUG("  Alignment: %d", config.cat_align, config.cat_align == align_type_t::ALIGN_CENTER ? "(center)" : "");
        BONGOCAT_LOG_DEBUG("  Layer: %s", config.layer == layer_type_t::LAYER_TOP ? "top" : "overlay");
        BONGOCAT_LOG_DEBUG("  Output Screen: %s", config.output_name);
    }

    // =============================================================================
    // PUBLIC API IMPLEMENTATION
    // =============================================================================

    created_result_t<config_t> load(const char *config_file_path, load_config_overwrite_parameters_t overwrite_parameters) {
        BONGOCAT_CHECK_NULL(config_file_path, bongocat_error_t::BONGOCAT_ERROR_INVALID_PARAM);

        config_t ret;
        set_defaults(ret);

        // Parse config file and override defaults
        bongocat_error_t result = bongocat_error_t::BONGOCAT_ERROR_CONFIG;
        if (strcmp(config_file_path, "-") == 0) {
            result = config_parse_stdin(ret, overwrite_parameters);
        } else {
            result = config_parse_file(ret, config_file_path, overwrite_parameters);
        }
        if (result != bongocat_error_t::BONGOCAT_SUCCESS) [[unlikely]] {
            BONGOCAT_LOG_ERROR("Failed to parse configuration file: %s", bongocat::error_string(result));
            return result;
        }

        if (overwrite_parameters.output_name) {
            if (ret.output_name) ::free(ret.output_name);
            ret.output_name = strdup(overwrite_parameters.output_name);
        }
        if (overwrite_parameters.randomize_index >= 0) {
            ret.randomize_index = overwrite_parameters.randomize_index ? 1 : 0;
        }
        if (overwrite_parameters.strict >= 0) {
            ret._strict = overwrite_parameters.strict >= 1;
        }

        if (ret.input_fps <= 0) {
            ret.input_fps = ret.fps;
        }

        // Set default keyboard device if none specified
        if (ret.num_keyboard_devices == 0) {
            if (!ret._strict) {
                result = config_set_default_devices(ret);
                if (result != bongocat_error_t::BONGOCAT_SUCCESS) {
                    BONGOCAT_LOG_ERROR("Failed to set default keyboard devices: %s", bongocat::error_string(result));
                    return result;
                }
            }
        }

        // Validate and sanitize configuration
        result = config_validate(ret);
        if (result != bongocat_error_t::BONGOCAT_SUCCESS) {
            BONGOCAT_LOG_ERROR("Configuration validation failed: %s", bongocat::error_string(result));
            return result;
        }

        if (ret.num_keyboard_devices == 0) {
            if (!ret._strict) {
                // Set default keyboard device if none specified
                result = config_set_default_devices(ret);
                if (result != bongocat_error_t::BONGOCAT_SUCCESS) {
                    BONGOCAT_LOG_ERROR("Failed to set default keyboard devices: %s", bongocat::error_string(result));
                    return result;
                } else {
                    BONGOCAT_LOG_INFO("No device loaded, use default keyboard device: %s", DEFAULT_DEVICE);
                }
            } else {
                BONGOCAT_LOG_INFO("No device loaded");
            }
        }

        // Log configuration summary
        config_log_summary(ret);

        return ret;
    }

    void reset(config_t& config) {
        config_cleanup_devices(config);
        set_defaults(config);
    }
}