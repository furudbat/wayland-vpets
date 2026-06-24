#include "config/config.h"

#include "core/bongocat.h"
#include "embedded_assets/bongocat/assets_bongocat_features.h"
#include "embedded_assets/bongocat/bongocat.h"
#include "embedded_assets/bongocat/bongocat.hpp"
#include "embedded_assets/misc/assets_misc_features.h"
#include "embedded_assets/misc/misc.hpp"
#include "embedded_assets/misc/misc_sprite.h"
#include "embedded_assets/ms_agent/assets_ms_agent_features.h"
#include "embedded_assets/ms_agent/ms_agent.hpp"
#include "embedded_assets/ms_agent/ms_agent_sprite.h"
#include "embedded_assets/pkmn/assets_pkmn_features.h"
#include "embedded_assets/pkmn/pkmn_sprite.h"
#include "embedded_assets/pmd/assets_pmd_features.h"
#include "embedded_assets/pmd/pmd_sprite.h"
#include "graphics/animation_thread_context.h"
#include "graphics/embedded_assets_dms.h"
#include "graphics/embedded_assets_pkmn.h"
#include "image_loader/custom/load_custom.h"
#include "image_loader/custom/load_custom_features.h"
#include "utils/error.h"

#include <cassert>
#include <cctype>
#include <climits>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctype.h>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <linux/input.h>
#include <sys/ioctl.h>
#include <unistd.h>

#ifdef FEATURE_MIN_DM_EMBEDDED_ASSETS
#  include "min_dm_config_parse_animation_name.h"
#endif
#ifdef FEATURE_DM_EMBEDDED_ASSETS
#  include "dm_config_parse_animation_name.h"
#endif
#ifdef FEATURE_DM20_EMBEDDED_ASSETS
#  include "dm20_config_parse_animation_name.h"
#endif
#ifdef FEATURE_DMX_EMBEDDED_ASSETS
#  include "dmx_config_parse_animation_name.h"
#endif
#ifdef FEATURE_DMC_EMBEDDED_ASSETS
#  include "dmc_config_parse_animation_name.h"
#endif
#ifdef FEATURE_PEN_EMBEDDED_ASSETS
#  include "pen_config_parse_animation_name.h"
#endif
#ifdef FEATURE_PEN20_EMBEDDED_ASSETS
#  include "pen20_config_parse_animation_name.h"
#endif
#ifdef FEATURE_DMALL_EMBEDDED_ASSETS
#  include "dmall_config_parse_animation_name.h"
#endif

#ifdef FEATURE_PKMN_EMBEDDED_ASSETS
#  include "pkmn_config_parse_animation_name.h"
#endif
#ifdef FEATURE_PMD_EMBEDDED_ASSETS
#  include "pmd_config_parse_animation_name.h"
#endif

// =============================================================================
// CONFIGURATION CONSTANTS AND VALIDATION RANGES
// =============================================================================

namespace bongocat::config {
static inline constexpr int MIN_CAT_HEIGHT = 8;
static inline constexpr int MAX_CAT_HEIGHT = 1024;
static inline constexpr int MIN_OVERLAY_HEIGHT = 16;
static inline constexpr int MAX_OVERLAY_HEIGHT = 2560;
static inline constexpr int MIN_FPS = 1;
static inline constexpr int MAX_FPS = 540;
static inline constexpr int MIN_DURATION_MS = 10;
static inline constexpr int MAX_DURATION_MS = 60 * 1000;
static inline constexpr int MIN_KPM = 0;
static inline constexpr int MAX_KPM = 10000;
static inline constexpr double MAX_CPU_THRESHOLD = 100.0;
static inline constexpr double MAX_CPU_RUNNING_FACTOR = 50.0;
static inline constexpr int MAX_UPDATE_RATE_MS = 60 * 60 * 1000;
static inline constexpr int MAX_SLEEP_TIMEOUT_SEC = 30 * 24 * 60 * 60;
static inline constexpr int MIN_OFFSET = -16000;
static inline constexpr int MAX_OFFSET = 16000;
static inline constexpr int MIN_MOVEMENT_RADIUS = 0;
static inline constexpr int MAX_MOVEMENT_RADIUS = MAX_OFFSET / 2;
static inline constexpr double MAX_EVOLUTION_SPEED_FACTOR = 5000.0;

static inline constexpr int MIN_HOTPLUG_SCAN_INTERVAL_MS = 0;
static inline constexpr int MAX_HOTPLUG_SCAN_INTERVAL_MS = 3600 * 1000;

static inline constexpr int MIN_CUSTOM_FRAMES = 0;
static inline constexpr int MAX_CUSTOM_FRAMES = 512;
static inline constexpr int MIN_CUSTOM_ROWS = 0;
static_assert(assets::CUSTOM_SPRITE_SHEET_MAX_ROWS > 0);
static inline constexpr int MAX_CUSTOM_ROWS = assets::CUSTOM_SPRITE_SHEET_MAX_ROWS - 1;

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
static inline constexpr int32_t DEFAULT_OVERLAY_OPACITY = 0;
static inline constexpr int32_t DEFAULT_ANIMATION_INDEX = 0;
static inline constexpr layer_type_t DEFAULT_LAYER = layer_type_t::LAYER_TOP;
static inline constexpr overlay_position_t DEFAULT_OVERLAY_POSITION = overlay_position_t::POSITION_TOP;
static inline constexpr int32_t DEFAULT_HAPPY_KPM = 0;
static inline constexpr platform::time_sec_t DEFAULT_IDLE_SLEEP_TIMEOUT_SEC = 0;
static inline constexpr align_type_t DEFAULT_CAT_ALIGN = align_type_t::ALIGN_CENTER;
static inline constexpr platform::time_ms_t DEFAULT_TEST_ANIMATION_DURATION_MS = 0;
static inline constexpr platform::time_sec_t DEFAULT_TEST_ANIMATION_INTERVAL_SEC = 0;
static inline constexpr bool DEFAULT_ENABLE_ANTIALIASING = true;
static inline constexpr double DEFAULT_MOVEMENT_WAIT_FACTOR = 5.1;
static inline constexpr bool DEFAULT_ENABLE_HAND_MAPPING = true;
static inline constexpr int32_t DEFAULT_HOTPLUG_SCAN_INTERVAL_MS = 30 * 1000;

// Debug-specific defaults
#ifndef NDEBUG
static inline constexpr bool DEFAULT_ENABLE_DEBUG = true;
#else
static inline constexpr bool DEFAULT_ENABLE_DEBUG = false;
#endif

static inline constexpr auto CAT_X_OFFSET_KEY CONFIG_STRING_SECTION = "cat_x_offset";
static inline constexpr auto CAT_Y_OFFSET_KEY CONFIG_STRING_SECTION = "cat_y_offset";
static inline constexpr auto CAT_HEIGHT_KEY CONFIG_STRING_SECTION = "cat_height";
static inline constexpr auto OVERLAY_HEIGHT_KEY CONFIG_STRING_SECTION = "overlay_height";
static inline constexpr auto OVERLAY_POSITION_KEY CONFIG_STRING_SECTION = "overlay_position";
static inline constexpr auto ANIMATION_NAME_KEY CONFIG_STRING_SECTION = "animation_name";
static inline constexpr auto INVERT_COLOR_KEY CONFIG_STRING_SECTION = "invert_color";
static inline constexpr auto PADDING_X_KEY CONFIG_STRING_SECTION = "padding_x";
static inline constexpr auto PADDING_Y_KEY CONFIG_STRING_SECTION = "padding_y";
static inline constexpr auto IDLE_FRAME_KEY CONFIG_STRING_SECTION = "idle_frame";
static inline constexpr auto ENABLE_SCHEDULED_SLEEP_KEY CONFIG_STRING_SECTION = "enable_scheduled_sleep";
static inline constexpr auto SLEEP_BEGIN_KEY CONFIG_STRING_SECTION = "sleep_begin";
static inline constexpr auto SLEEP_END_KEY CONFIG_STRING_SECTION = "sleep_end";
static inline constexpr auto IDLE_SLEEP_TIMEOUT_KEY CONFIG_STRING_SECTION = "idle_sleep_timeout";
static inline constexpr auto HAPPY_KPM_KEY CONFIG_STRING_SECTION = "happy_kpm";
static inline constexpr auto KEYPRESS_DURATION_KEY CONFIG_STRING_SECTION = "keypress_duration";
static inline constexpr auto TEST_ANIMATION_DURATION_KEY CONFIG_STRING_SECTION = "test_animation_duration";
static inline constexpr auto TEST_ANIMATION_INTERVAL_KEY CONFIG_STRING_SECTION = "test_animation_interval";
static inline constexpr auto ANIMATION_SPEED_KEY CONFIG_STRING_SECTION = "animation_speed";
static inline constexpr auto FPS_KEY CONFIG_STRING_SECTION = "fps";
static inline constexpr auto OVERLAY_OPACITY_KEY CONFIG_STRING_SECTION = "overlay_opacity";
static inline constexpr auto ENABLE_DEBUG_KEY CONFIG_STRING_SECTION = "enable_debug";
static inline constexpr auto KEYBOARD_DEVICE_KEY CONFIG_STRING_SECTION = "keyboard_device";
static inline constexpr auto KEYBOARD_DEVICES_KEY CONFIG_STRING_SECTION = "keyboard_devices";
static inline constexpr auto ANIMATION_INDEX_KEY CONFIG_STRING_SECTION = "animation_index";
static inline constexpr auto LAYER_KEY CONFIG_STRING_SECTION = "layer";  ///< DEPRECATED: use overlay_layer
static inline constexpr auto OVERLAY_LAYER_KEY CONFIG_STRING_SECTION = "overlay_layer";
static inline constexpr auto CAT_ALIGN_KEY CONFIG_STRING_SECTION = "cat_align";
static inline constexpr auto IDLE_ANIMATION_KEY CONFIG_STRING_SECTION = "idle_animation";
static inline constexpr auto INPUT_FPS_KEY CONFIG_STRING_SECTION = "input_fps";
static inline constexpr auto MIRROR_X_KEY CONFIG_STRING_SECTION = "mirror_x";
static inline constexpr auto MIRROR_Y_KEY CONFIG_STRING_SECTION = "mirror_y";
static inline constexpr auto RANDOM_KEY CONFIG_STRING_SECTION = "random";
static inline constexpr auto RANDOM_ON_RELOAD_KEY CONFIG_STRING_SECTION = "random_on_reload";
static inline constexpr auto ENABLE_ANTIALIASING_KEY CONFIG_STRING_SECTION = "enable_antialiasing";
static inline constexpr auto UPDATE_RATE_KEY CONFIG_STRING_SECTION = "update_rate";
static inline constexpr auto CPU_THRESHOLD_KEY CONFIG_STRING_SECTION = "cpu_threshold";
static inline constexpr auto CPU_RUNNING_FACTOR_KEY CONFIG_STRING_SECTION = "cpu_running_factor";
static inline constexpr auto MOVEMENT_RADIUS_KEY CONFIG_STRING_SECTION = "movement_radius";
static inline constexpr auto ENABLE_MOVEMENT_DEBUG_KEY CONFIG_STRING_SECTION = "enable_movement_debug";
static inline constexpr auto MOVEMENT_SPEED_KEY CONFIG_STRING_SECTION = "movement_speed";
static inline constexpr auto MOVEMENT_WAIT_FACTOR_KEY CONFIG_STRING_SECTION = "movement_wait_factor";
static inline constexpr auto SCREEN_WIDTH_KEY CONFIG_STRING_SECTION = "screen_width";
static inline constexpr auto MONITOR_KEY CONFIG_STRING_SECTION = "monitor";
static inline constexpr auto OUTPUT_NAME_KEY CONFIG_STRING_SECTION = "output_name";  // monitor alt key
static inline constexpr auto ENABLE_HAND_MAPPING_KEY CONFIG_STRING_SECTION = "enable_hand_mapping";
static inline constexpr auto HOTPLUG_SCAN_INTERVAL_KEY CONFIG_STRING_SECTION = "hotplug_scan_interval";
static inline constexpr auto DISABLE_FULLSCREEN_HIDE_KEY CONFIG_STRING_SECTION = "disable_fullscreen_hide";
static inline constexpr auto KEYBOARD_NAME_KEY CONFIG_STRING_SECTION = "keyboard_name";
static inline constexpr auto EVOLUTION_KEY CONFIG_STRING_SECTION = "evolution";
static inline constexpr auto EVOLUTION_SPEED_FACTOR_KEY CONFIG_STRING_SECTION = "evolution_speed_factor";

static inline constexpr auto CUSTOM_SPRITE_SHEET_FILENAME_KEY CONFIG_STRING_SECTION = "custom_sprite_sheet_filename";
static inline constexpr auto CUSTOM_IDLE_FRAMES_KEY CONFIG_STRING_SECTION = "custom_idle_frames";
static inline constexpr auto CUSTOM_BORING_FRAMES_KEY CONFIG_STRING_SECTION = "custom_boring_frames";
static inline constexpr auto CUSTOM_START_WRITING_FRAMES_KEY CONFIG_STRING_SECTION = "custom_start_writing_frames";
static inline constexpr auto CUSTOM_WRITING_FRAMES_KEY CONFIG_STRING_SECTION = "custom_writing_frames";
static inline constexpr auto CUSTOM_END_WRITING_FRAMES_KEY CONFIG_STRING_SECTION = "custom_end_writing_frames";
static inline constexpr auto CUSTOM_HAPPY_FRAMES_KEY CONFIG_STRING_SECTION = "custom_happy_frames";
static inline constexpr auto CUSTOM_ASLEEP_FRAMES_KEY CONFIG_STRING_SECTION = "custom_asleep_frames";
static inline constexpr auto CUSTOM_SLEEP_FRAMES_KEY CONFIG_STRING_SECTION = "custom_sleep_frames";
static inline constexpr auto CUSTOM_WAKE_UP_FRAMES_KEY CONFIG_STRING_SECTION = "custom_wake_up_frames";
static inline constexpr auto CUSTOM_START_WORKING_FRAMES_KEY CONFIG_STRING_SECTION = "custom_start_working_frames";
static inline constexpr auto CUSTOM_WORKING_FRAMES_KEY CONFIG_STRING_SECTION = "custom_working_frames";
static inline constexpr auto CUSTOM_END_WORKING_FRAMES_KEY CONFIG_STRING_SECTION = "custom_end_working_frames";
static inline constexpr auto CUSTOM_START_MOVING_FRAMES_KEY CONFIG_STRING_SECTION = "custom_start_moving_frames";
static inline constexpr auto CUSTOM_MOVING_FRAMES_KEY CONFIG_STRING_SECTION = "custom_moving_frames";
static inline constexpr auto CUSTOM_END_MOVING_FRAMES_KEY CONFIG_STRING_SECTION = "custom_end_moving_frames";
static inline constexpr auto CUSTOM_START_RUNNING_FRAMES_KEY CONFIG_STRING_SECTION = "custom_start_running_frames";
static inline constexpr auto CUSTOM_RUNNING_FRAMES_KEY CONFIG_STRING_SECTION = "custom_running_frames";
static inline constexpr auto CUSTOM_END_RUNNING_FRAMES_KEY CONFIG_STRING_SECTION = "custom_end_running_frames";

static inline constexpr auto CUSTOM_TOGGLE_WRITING_FRAMES_KEY CONFIG_STRING_SECTION = "custom_toggle_writing_frames";
static inline constexpr auto CUSTOM_TOGGLE_WRITING_FRAMES_RANDOM_KEY CONFIG_STRING_SECTION =
    "custom_toggle_writing_frames_random";
static inline constexpr auto CUSTOM_MIRROR_X_MOVING_KEY CONFIG_STRING_SECTION = "custom_mirror_x_moving";

static inline constexpr auto CUSTOM_IDLE_ROW_KEY CONFIG_STRING_SECTION = "custom_idle_row";
static inline constexpr auto CUSTOM_BORING_ROW_KEY CONFIG_STRING_SECTION = "custom_boring_row";
static inline constexpr auto CUSTOM_START_WRITING_ROW_KEY CONFIG_STRING_SECTION = "custom_start_writing_row";
static inline constexpr auto CUSTOM_WRITING_ROW_KEY CONFIG_STRING_SECTION = "custom_writing_row";
static inline constexpr auto CUSTOM_END_WRITING_ROW_KEY CONFIG_STRING_SECTION = "custom_end_writing_row";
static inline constexpr auto CUSTOM_HAPPY_ROW_KEY CONFIG_STRING_SECTION = "custom_happy_row";
static inline constexpr auto CUSTOM_ASLEEP_ROW_KEY CONFIG_STRING_SECTION = "custom_asleep_row";
static inline constexpr auto CUSTOM_SLEEP_ROW_KEY CONFIG_STRING_SECTION = "custom_sleep_row";
static inline constexpr auto CUSTOM_WAKE_UP_ROW_KEY CONFIG_STRING_SECTION = "custom_wake_up_row";
static inline constexpr auto CUSTOM_START_WORKING_ROW_KEY CONFIG_STRING_SECTION = "custom_start_working_row";
static inline constexpr auto CUSTOM_WORKING_ROW_KEY CONFIG_STRING_SECTION = "custom_working_row";
static inline constexpr auto CUSTOM_END_WORKING_ROW_KEY CONFIG_STRING_SECTION = "custom_end_working_row";
static inline constexpr auto CUSTOM_START_MOVING_ROW_KEY CONFIG_STRING_SECTION = "custom_start_moving_row";
static inline constexpr auto CUSTOM_MOVING_ROW_KEY CONFIG_STRING_SECTION = "custom_moving_row";
static inline constexpr auto CUSTOM_END_MOVING_ROW_KEY CONFIG_STRING_SECTION = "custom_end_moving_row";
static inline constexpr auto CUSTOM_START_RUNNING_ROW_KEY CONFIG_STRING_SECTION = "custom_start_running_row";
static inline constexpr auto CUSTOM_RUNNING_ROW_KEY CONFIG_STRING_SECTION = "custom_running_row";
static inline constexpr auto CUSTOM_END_RUNNING_ROW_KEY CONFIG_STRING_SECTION = "custom_end_running_row";
static inline constexpr auto CUSTOM_START_EVOLVING_ROW_KEY CONFIG_STRING_SECTION = "custom_start_evolving_row";
static inline constexpr auto CUSTOM_EVOLVING_ROW_KEY CONFIG_STRING_SECTION = "custom_evolving_row";
static inline constexpr auto CUSTOM_AFTER_EVOLVING_ROW_KEY CONFIG_STRING_SECTION = "custom_after_evolving_row";
static inline constexpr auto CUSTOM_ROWS_KEY CONFIG_STRING_SECTION = "custom_rows";

inline static constexpr const char *EVOLUTION_TIME_MODE_PROGRAM_START_ALT_STR = "program_start";

static inline constexpr size_t KEY_BUF = 256;
static inline constexpr size_t VALUE_BUF = PATH_MAX + 256;                      // max value + comment
static inline constexpr size_t LINE_BUF = KEY_BUF - 1 + VALUE_BUF - 1 + 1 + 1;  // key + '=' + value + '\0'

constexpr char COMMENT_CHAR_1 = '#';
constexpr char COMMENT_CHAR_2 = ';';

/*
inline static constexpr config_parsing_warning_t ignore_warnings_in_strict_mode[] = {
  config_parsing_warning_t::CustomSpriteSheetRequiredSleepAnimation,
  config_parsing_warning_t::CustomSpriteSheetRequiredMovingAnimation,
  config_parsing_warning_t::CustomSpriteSheetRequiredWritingAnimation,
  config_parsing_warning_t::CustomSpriteSheetRequiredHappyAnimation,
  config_parsing_warning_t::WarningConfigLineTooLong,
  config_parsing_warning_t::WarningInvalidAnimationName,
  config_parsing_warning_t::WarningConfigLineTooLong,
  config_parsing_warning_t::WarningInvalidConfigLine,
  config_parsing_warning_t::WarningUnknownConfigKey,
  config_parsing_warning_t::WarningMaxDeviceNamesReached,
  config_parsing_warning_t::WarningNoInputDevices,
};
BONGOCAT_NODISCARD static bool config_has_warnings(const config_parse_result_t& res) {
  return res.warnings != config_parsing_warning_t::Success;
}
BONGOCAT_NODISCARD static bool config_has_warnings(config_parsing_warning_t warn) {
  return warn != config_parsing_warning_t::Success;
}
BONGOCAT_NODISCARD static bool config_has_only_warnings(const config_parse_result_t& res) {
  return res.errors == config_parsing_error_t::Success && res.warnings != config_parsing_warning_t::Success;
}
*/

BONGOCAT_NODISCARD static config_parse_result_t config_add_parse_error(config_parse_result_t res,
                                                                       config_parsing_error_t err) {
  res.errors = flag_add(res.errors, err);
  return res;
}
BONGOCAT_NODISCARD static config_parse_result_t config_add_parse_warning(config_parse_result_t res,
                                                                         config_parsing_warning_t warn) {
  res.warnings = flag_add(res.warnings, warn);
  return res;
}
BONGOCAT_NODISCARD static config_parse_result_t config_add_parse_info(config_parse_result_t res,
                                                                      config_parsing_info_t inf) {
  res.infos = flag_add(res.infos, inf);
  return res;
}
BONGOCAT_NODISCARD static config_parse_result_t config_chain_parse_result(config_parse_result_t res,
                                                                          const config_parse_result_t& in) {
  res.fatal = flag_add(res.fatal, in.fatal);
  res.errors = flag_add(res.errors, in.errors);
  res.warnings = flag_add(res.warnings, in.warnings);
  res.infos = flag_add(res.infos, in.infos);
  return res;
}
BONGOCAT_NODISCARD static bool config_was_key_unknown(const config_parse_result_t& res) {
  return res.errors == config_parsing_error_t::Success && has_flag(res.infos, config_parsing_info_t::UnknownConfigKey);
}

// =============================================================================
// CONFIGURATION VALIDATION MODULE
// =============================================================================

static constexpr config_parsing_error_t config_clamp_int(int& value, int min, int max,
                                                         [[maybe_unused]] const char *name) {
  if (value < min || value > max) {
    BONGOCAT_LOG_WARNING("%s %d out of range [%d-%d], clamping", name, value, min, max);
    value = (value < min) ? min : max;
    return config_parsing_error_t::OutOfRangeInt;
  }
  return config_parsing_error_t::Success;
}
static constexpr config_parsing_error_t config_clamp_double(double& value, double min, double max,
                                                            [[maybe_unused]] const char *name) {
  if (value < min || value > max) {
    BONGOCAT_LOG_WARNING("%s %.2f out of range [%.0f-%.0f], clamping", name, value, min, max);
    value = (value < min) ? min : max;
    return config_parsing_error_t::OutOfRangeDouble;
  }
  return config_parsing_error_t::Success;
}

static constexpr config_parsing_error_t config_validate_max_int(const int& value, int max,
                                                                [[maybe_unused]] const char *name) {
  if (value > max) {
    BONGOCAT_LOG_WARNING("%s %d out of range [%d], clamping", name, value, max);
    return config_parsing_error_t::OutOfRangeInt;
  }
  return config_parsing_error_t::Success;
}

static config_parse_result_t config_validate_dimensions(config_t& config) {
  config_parse_result_t ret{};
  ret =
      config_add_parse_error(ret, config_clamp_int(config.cat_height, MIN_CAT_HEIGHT, MAX_CAT_HEIGHT, CAT_HEIGHT_KEY));
  ret = config_add_parse_error(
      ret, config_clamp_int(config.overlay_height, MIN_OVERLAY_HEIGHT, MAX_OVERLAY_HEIGHT, OVERLAY_HEIGHT_KEY));
  ret = config_add_parse_error(ret, config_clamp_int(config.cat_x_offset, MIN_OFFSET, MAX_OFFSET, CAT_X_OFFSET_KEY));
  ret = config_add_parse_error(ret, config_clamp_int(config.cat_y_offset, MIN_OFFSET, MAX_OFFSET, CAT_Y_OFFSET_KEY));
  ret = config_add_parse_error(
      ret, config_clamp_int(config.movement_radius, MIN_MOVEMENT_RADIUS, MAX_MOVEMENT_RADIUS, CAT_Y_OFFSET_KEY));
  ret = config_add_parse_error(ret, config_clamp_int(config.padding_x, 0, MAX_OFFSET, PADDING_X_KEY));
  ret = config_add_parse_error(ret, config_clamp_int(config.padding_y, 0, MAX_OFFSET, PADDING_Y_KEY));
  ret = config_add_parse_error(ret, config_clamp_int(config.screen_width, 0, MAX_OFFSET, SCREEN_WIDTH_KEY));
  return ret;
}

static config_parse_result_t config_validate_timing(config_t& config) {
  config_parse_result_t ret{};
  ret = config_add_parse_error(ret, config_clamp_int(config.fps, MIN_FPS, MAX_FPS, FPS_KEY));
  ret = config_add_parse_error(
      ret, config_clamp_int(config.keypress_duration_ms, MIN_DURATION_MS, MAX_DURATION_MS, KEYPRESS_DURATION_KEY));
  ret = config_add_parse_error(
      ret, config_clamp_int(config.test_animation_duration_ms, 0, MAX_DURATION_MS, TEST_ANIMATION_DURATION_KEY));
  ret =
      config_add_parse_error(ret, config_clamp_int(config.animation_speed_ms, 0, MAX_DURATION_MS, ANIMATION_SPEED_KEY));
  ret = config_add_parse_error(
      ret, config_clamp_int(config.idle_sleep_timeout_sec, 0, MAX_SLEEP_TIMEOUT_SEC, IDLE_SLEEP_TIMEOUT_KEY));
  ret = config_add_parse_error(ret, config_clamp_int(config.input_fps, 0, MAX_FPS, INPUT_FPS_KEY));
  ret = config_add_parse_error(ret, config_clamp_int(config.movement_speed, 0, MAX_DURATION_MS, MOVEMENT_SPEED_KEY));
  ret = config_add_parse_error(ret, config_clamp_int(config.hotplug_scan_interval_ms, MIN_HOTPLUG_SCAN_INTERVAL_MS,
                                                     MAX_HOTPLUG_SCAN_INTERVAL_MS, HOTPLUG_SCAN_INTERVAL_KEY));

  return ret;
}

static config_parse_result_t config_validate_kpm(config_t& config) {
  config_parse_result_t ret{};
  ret = config_add_parse_error(ret, config_clamp_int(config.happy_kpm, MIN_KPM, MAX_KPM, HAPPY_KPM_KEY));
  return ret;
}

static config_parse_result_t config_validate_update(config_t& config) {
  config_parse_result_t ret{};

  ret = config_add_parse_error(ret, config_clamp_int(config.update_rate_ms, 0, MAX_UPDATE_RATE_MS, UPDATE_RATE_KEY));
  ret = config_add_parse_error(ret, config_clamp_double(config.cpu_threshold, 0, MAX_CPU_THRESHOLD, CPU_THRESHOLD_KEY));
  ret = config_add_parse_error(
      ret, config_clamp_double(config.cpu_running_factor, 0, MAX_CPU_RUNNING_FACTOR, CPU_RUNNING_FACTOR_KEY));
  ret = config_add_parse_error(ret, config_clamp_double(config.evolution_speed_factor, 0, MAX_EVOLUTION_SPEED_FACTOR,
                                                        EVOLUTION_SPEED_FACTOR_KEY));

  return ret;
}

static config_parse_result_t config_validate_custom(config_t& config) {
  using namespace assets;
  config_parse_result_t ret{};

  if (config._custom) {
    if (config.custom_sprite_sheet_settings.feature_toggle_writing_frames >= 0) {
      config.custom_sprite_sheet_settings.feature_toggle_writing_frames =
          config.custom_sprite_sheet_settings.feature_toggle_writing_frames >= 1 ? 1 : 0;
    }
    if (config.custom_sprite_sheet_settings.feature_toggle_writing_frames_random >= 0) {
      config.custom_sprite_sheet_settings.feature_toggle_writing_frames_random =
          config.custom_sprite_sheet_settings.feature_toggle_writing_frames_random >= 1 ? 1 : 0;
    }
    if (config.custom_sprite_sheet_settings.feature_mirror_x_moving >= 0) {
      config.custom_sprite_sheet_settings.feature_mirror_x_moving =
          config.custom_sprite_sheet_settings.feature_mirror_x_moving >= 1 ? 1 : 0;
    }

    // clamp cols
    ret = config_add_parse_error(ret, config_clamp_int(config.custom_sprite_sheet_settings.idle_frames,
                                                       MIN_CUSTOM_FRAMES, MAX_CUSTOM_FRAMES, CUSTOM_IDLE_FRAMES_KEY));

    ret = config_add_parse_error(ret, config_clamp_int(config.custom_sprite_sheet_settings.boring_frames,
                                                       MIN_CUSTOM_FRAMES, MAX_CUSTOM_FRAMES, CUSTOM_BORING_FRAMES_KEY));

    ret = config_add_parse_error(ret, config_clamp_int(config.custom_sprite_sheet_settings.start_writing_frames,
                                                       MIN_CUSTOM_FRAMES, MAX_CUSTOM_FRAMES,
                                                       CUSTOM_START_WRITING_FRAMES_KEY));
    ret =
        config_add_parse_error(ret, config_clamp_int(config.custom_sprite_sheet_settings.writing_frames,
                                                     MIN_CUSTOM_FRAMES, MAX_CUSTOM_FRAMES, CUSTOM_WRITING_FRAMES_KEY));
    ret = config_add_parse_error(ret,
                                 config_clamp_int(config.custom_sprite_sheet_settings.end_writing_frames,
                                                  MIN_CUSTOM_FRAMES, MAX_CUSTOM_FRAMES, CUSTOM_END_WRITING_FRAMES_KEY));
    ret = config_add_parse_error(ret, config_clamp_int(config.custom_sprite_sheet_settings.happy_frames,
                                                       MIN_CUSTOM_FRAMES, MAX_CUSTOM_FRAMES, CUSTOM_HAPPY_FRAMES_KEY));

    ret = config_add_parse_error(ret, config_clamp_int(config.custom_sprite_sheet_settings.asleep_frames,
                                                       MIN_CUSTOM_FRAMES, MAX_CUSTOM_FRAMES, CUSTOM_ASLEEP_FRAMES_KEY));
    ret = config_add_parse_error(ret, config_clamp_int(config.custom_sprite_sheet_settings.sleep_frames,
                                                       MIN_CUSTOM_FRAMES, MAX_CUSTOM_FRAMES, CUSTOM_SLEEP_FRAMES_KEY));
    ret =
        config_add_parse_error(ret, config_clamp_int(config.custom_sprite_sheet_settings.wake_up_frames,
                                                     MIN_CUSTOM_FRAMES, MAX_CUSTOM_FRAMES, CUSTOM_WAKE_UP_FRAMES_KEY));

    ret = config_add_parse_error(ret, config_clamp_int(config.custom_sprite_sheet_settings.start_working_frames,
                                                       MIN_CUSTOM_FRAMES, MAX_CUSTOM_FRAMES,
                                                       CUSTOM_START_WORKING_FRAMES_KEY));
    ret =
        config_add_parse_error(ret, config_clamp_int(config.custom_sprite_sheet_settings.working_frames,
                                                     MIN_CUSTOM_FRAMES, MAX_CUSTOM_FRAMES, CUSTOM_WORKING_FRAMES_KEY));
    ret = config_add_parse_error(ret,
                                 config_clamp_int(config.custom_sprite_sheet_settings.end_working_frames,
                                                  MIN_CUSTOM_FRAMES, MAX_CUSTOM_FRAMES, CUSTOM_END_WORKING_FRAMES_KEY));

    ret = config_add_parse_error(ret, config_clamp_int(config.custom_sprite_sheet_settings.start_moving_frames,
                                                       MIN_CUSTOM_FRAMES, MAX_CUSTOM_FRAMES,
                                                       CUSTOM_START_MOVING_FRAMES_KEY));
    ret = config_add_parse_error(ret, config_clamp_int(config.custom_sprite_sheet_settings.moving_frames,
                                                       MIN_CUSTOM_FRAMES, MAX_CUSTOM_FRAMES, CUSTOM_MOVING_FRAMES_KEY));
    ret = config_add_parse_error(ret,
                                 config_clamp_int(config.custom_sprite_sheet_settings.end_moving_frames,
                                                  MIN_CUSTOM_FRAMES, MAX_CUSTOM_FRAMES, CUSTOM_END_MOVING_FRAMES_KEY));

    ret = config_add_parse_error(ret, config_clamp_int(config.custom_sprite_sheet_settings.start_running_frames,
                                                       MIN_CUSTOM_FRAMES, MAX_CUSTOM_FRAMES,
                                                       CUSTOM_START_RUNNING_FRAMES_KEY));
    ret =
        config_add_parse_error(ret, config_clamp_int(config.custom_sprite_sheet_settings.running_frames,
                                                     MIN_CUSTOM_FRAMES, MAX_CUSTOM_FRAMES, CUSTOM_RUNNING_FRAMES_KEY));
    ret = config_add_parse_error(ret,
                                 config_clamp_int(config.custom_sprite_sheet_settings.end_running_frames,
                                                  MIN_CUSTOM_FRAMES, MAX_CUSTOM_FRAMES, CUSTOM_END_RUNNING_FRAMES_KEY));

    // clamp rows
    if (config.custom_sprite_sheet_settings.idle_row_index >= 0) {
      ret = config_add_parse_error(ret, config_clamp_int(config.custom_sprite_sheet_settings.idle_row_index,
                                                         MIN_CUSTOM_ROWS, MAX_CUSTOM_ROWS, CUSTOM_IDLE_ROW_KEY));
    }
    if (config.custom_sprite_sheet_settings.boring_row_index >= 0) {
      ret = config_add_parse_error(ret, config_clamp_int(config.custom_sprite_sheet_settings.boring_row_index,
                                                         MIN_CUSTOM_ROWS, MAX_CUSTOM_ROWS, CUSTOM_BORING_ROW_KEY));
    }
    if (config.custom_sprite_sheet_settings.start_writing_row_index >= 0) {
      ret =
          config_add_parse_error(ret, config_clamp_int(config.custom_sprite_sheet_settings.start_writing_row_index,
                                                       MIN_CUSTOM_ROWS, MAX_CUSTOM_ROWS, CUSTOM_START_WRITING_ROW_KEY));
    }
    if (config.custom_sprite_sheet_settings.writing_row_index >= 0) {
      ret = config_add_parse_error(ret, config_clamp_int(config.custom_sprite_sheet_settings.writing_row_index,
                                                         MIN_CUSTOM_ROWS, MAX_CUSTOM_ROWS, CUSTOM_WRITING_ROW_KEY));
    }
    if (config.custom_sprite_sheet_settings.end_writing_row_index >= 0) {
      ret = config_add_parse_error(ret, config_clamp_int(config.custom_sprite_sheet_settings.end_writing_row_index,
                                                         MIN_CUSTOM_ROWS, MAX_CUSTOM_ROWS, CUSTOM_END_WRITING_ROW_KEY));
    }
    if (config.custom_sprite_sheet_settings.happy_row_index >= 0) {
      ret = config_add_parse_error(ret, config_clamp_int(config.custom_sprite_sheet_settings.happy_row_index,
                                                         MIN_CUSTOM_ROWS, MAX_CUSTOM_ROWS, CUSTOM_HAPPY_ROW_KEY));
    }
    if (config.custom_sprite_sheet_settings.asleep_row_index >= 0) {
      ret = config_add_parse_error(ret, config_clamp_int(config.custom_sprite_sheet_settings.asleep_row_index,
                                                         MIN_CUSTOM_ROWS, MAX_CUSTOM_ROWS, CUSTOM_ASLEEP_ROW_KEY));
    }
    if (config.custom_sprite_sheet_settings.sleep_row_index >= 0) {
      ret = config_add_parse_error(ret, config_clamp_int(config.custom_sprite_sheet_settings.sleep_row_index,
                                                         MIN_CUSTOM_ROWS, MAX_CUSTOM_ROWS, CUSTOM_SLEEP_ROW_KEY));
    }
    if (config.custom_sprite_sheet_settings.wake_up_row_index >= 0) {
      ret = config_add_parse_error(ret, config_clamp_int(config.custom_sprite_sheet_settings.wake_up_row_index,
                                                         MIN_CUSTOM_ROWS, MAX_CUSTOM_ROWS, CUSTOM_WAKE_UP_ROW_KEY));
    }
    if (config.custom_sprite_sheet_settings.start_working_row_index >= 0) {
      ret =
          config_add_parse_error(ret, config_clamp_int(config.custom_sprite_sheet_settings.start_working_row_index,
                                                       MIN_CUSTOM_ROWS, MAX_CUSTOM_ROWS, CUSTOM_START_WORKING_ROW_KEY));
    }
    if (config.custom_sprite_sheet_settings.working_row_index >= 0) {
      ret = config_add_parse_error(ret, config_clamp_int(config.custom_sprite_sheet_settings.working_row_index,
                                                         MIN_CUSTOM_ROWS, MAX_CUSTOM_ROWS, CUSTOM_WORKING_ROW_KEY));
    }
    if (config.custom_sprite_sheet_settings.end_working_row_index >= 0) {
      ret = config_add_parse_error(ret, config_clamp_int(config.custom_sprite_sheet_settings.end_working_row_index,
                                                         MIN_CUSTOM_ROWS, MAX_CUSTOM_ROWS, CUSTOM_END_WORKING_ROW_KEY));
    }
    if (config.custom_sprite_sheet_settings.start_moving_row_index >= 0) {
      ret =
          config_add_parse_error(ret, config_clamp_int(config.custom_sprite_sheet_settings.start_moving_row_index,
                                                       MIN_CUSTOM_ROWS, MAX_CUSTOM_ROWS, CUSTOM_START_MOVING_ROW_KEY));
    }
    if (config.custom_sprite_sheet_settings.moving_row_index >= 0) {
      ret = config_add_parse_error(ret, config_clamp_int(config.custom_sprite_sheet_settings.moving_row_index,
                                                         MIN_CUSTOM_ROWS, MAX_CUSTOM_ROWS, CUSTOM_MOVING_ROW_KEY));
    }
    if (config.custom_sprite_sheet_settings.end_moving_row_index >= 0) {
      ret = config_add_parse_error(ret, config_clamp_int(config.custom_sprite_sheet_settings.end_moving_row_index,
                                                         MIN_CUSTOM_ROWS, MAX_CUSTOM_ROWS, CUSTOM_END_MOVING_ROW_KEY));
    }
    if (config.custom_sprite_sheet_settings.start_running_row_index >= 0) {
      ret =
          config_add_parse_error(ret, config_clamp_int(config.custom_sprite_sheet_settings.start_running_row_index,
                                                       MIN_CUSTOM_ROWS, MAX_CUSTOM_ROWS, CUSTOM_START_RUNNING_ROW_KEY));
    }
    if (config.custom_sprite_sheet_settings.running_row_index >= 0) {
      ret = config_add_parse_error(ret, config_clamp_int(config.custom_sprite_sheet_settings.running_row_index,
                                                         MIN_CUSTOM_ROWS, MAX_CUSTOM_ROWS, CUSTOM_RUNNING_ROW_KEY));
    }
    if (config.custom_sprite_sheet_settings.end_running_row_index >= 0) {
      ret = config_add_parse_error(ret, config_clamp_int(config.custom_sprite_sheet_settings.end_running_row_index,
                                                         MIN_CUSTOM_ROWS, MAX_CUSTOM_ROWS, CUSTOM_END_RUNNING_ROW_KEY));
    }
    if (config.custom_sprite_sheet_settings.start_evolving_row_index >= 0) {
      ret = config_add_parse_error(ret,
                                   config_clamp_int(config.custom_sprite_sheet_settings.start_evolving_row_index,
                                                    MIN_CUSTOM_ROWS, MAX_CUSTOM_ROWS, CUSTOM_START_EVOLVING_ROW_KEY));
    } else if (config.custom_sprite_sheet_settings.start_working_row_index >= 0) {
      ret =
          config_add_parse_error(ret, config_clamp_int(config.custom_sprite_sheet_settings.start_evolving_row_index,
                                                       MIN_CUSTOM_ROWS, MAX_CUSTOM_ROWS, CUSTOM_START_WORKING_ROW_KEY));
    }
    if (config.custom_sprite_sheet_settings.evolving_row_index >= 0) {
      ret = config_add_parse_error(ret, config_clamp_int(config.custom_sprite_sheet_settings.evolving_row_index,
                                                         MIN_CUSTOM_ROWS, MAX_CUSTOM_ROWS, CUSTOM_EVOLVING_ROW_KEY));
    } else if (config.custom_sprite_sheet_settings.working_row_index >= 0) {
      ret = config_add_parse_error(ret, config_clamp_int(config.custom_sprite_sheet_settings.evolving_row_index,
                                                         MIN_CUSTOM_ROWS, MAX_CUSTOM_ROWS, CUSTOM_WORKING_ROW_KEY));
    }
    if (config.custom_sprite_sheet_settings.after_evolving_row_index >= 0) {
      ret = config_add_parse_error(ret,
                                   config_clamp_int(config.custom_sprite_sheet_settings.after_evolving_row_index,
                                                    MIN_CUSTOM_ROWS, MAX_CUSTOM_ROWS, CUSTOM_AFTER_EVOLVING_ROW_KEY));
    } else if (config.custom_sprite_sheet_settings.working_row_index >= 0) {
      ret = config_add_parse_error(ret, config_clamp_int(config.custom_sprite_sheet_settings.after_evolving_row_index,
                                                         MIN_CUSTOM_ROWS, MAX_CUSTOM_ROWS, CUSTOM_END_WORKING_ROW_KEY));
    }
    if (config.custom_sprite_sheet_settings.rows >= 0) {
      ret = config_add_parse_error(
          ret, config_clamp_int(config.custom_sprite_sheet_settings.rows, 1, MAX_CUSTOM_ROWS, CUSTOM_ROWS_KEY));
    }

    const int sprite_sheet_cols = get_custom_animation_settings_max_cols(config.custom_sprite_sheet_settings);
    const int sprite_sheet_rows = get_custom_animation_settings_rows_count(config.custom_sprite_sheet_settings);

    if (sprite_sheet_cols <= 0) {
      BONGOCAT_LOG_WARNING("custom sprite sheet has no columns");
      ret = config_add_parse_error(ret, config_parsing_error_t::InvalidCustomSpriteSheetCols);
    }

    // validate cols
    ret = config_add_parse_error(ret, config_validate_max_int(config.custom_sprite_sheet_settings.idle_frames,
                                                              sprite_sheet_cols, CUSTOM_IDLE_FRAMES_KEY));

    ret = config_add_parse_error(ret, config_validate_max_int(config.custom_sprite_sheet_settings.boring_frames,
                                                              sprite_sheet_cols, CUSTOM_BORING_FRAMES_KEY));

    ret = config_add_parse_error(ret, config_validate_max_int(config.custom_sprite_sheet_settings.start_writing_frames,
                                                              sprite_sheet_cols, CUSTOM_START_WRITING_FRAMES_KEY));
    ret = config_add_parse_error(ret, config_validate_max_int(config.custom_sprite_sheet_settings.writing_frames,
                                                              sprite_sheet_cols, CUSTOM_WRITING_FRAMES_KEY));
    ret = config_add_parse_error(ret, config_validate_max_int(config.custom_sprite_sheet_settings.end_writing_frames,
                                                              sprite_sheet_cols, CUSTOM_END_WRITING_FRAMES_KEY));
    ret = config_add_parse_error(ret, config_validate_max_int(config.custom_sprite_sheet_settings.happy_frames,
                                                              sprite_sheet_cols, CUSTOM_HAPPY_FRAMES_KEY));

    ret = config_add_parse_error(ret, config_validate_max_int(config.custom_sprite_sheet_settings.asleep_frames,
                                                              sprite_sheet_cols, CUSTOM_ASLEEP_FRAMES_KEY));
    ret = config_add_parse_error(ret, config_validate_max_int(config.custom_sprite_sheet_settings.sleep_frames,
                                                              sprite_sheet_cols, CUSTOM_SLEEP_FRAMES_KEY));
    ret = config_add_parse_error(ret, config_validate_max_int(config.custom_sprite_sheet_settings.wake_up_frames,
                                                              sprite_sheet_cols, CUSTOM_WAKE_UP_FRAMES_KEY));

    ret = config_add_parse_error(ret, config_validate_max_int(config.custom_sprite_sheet_settings.start_working_frames,
                                                              sprite_sheet_cols, CUSTOM_START_WORKING_FRAMES_KEY));
    ret = config_add_parse_error(ret, config_validate_max_int(config.custom_sprite_sheet_settings.working_frames,
                                                              sprite_sheet_cols, CUSTOM_WORKING_FRAMES_KEY));
    ret = config_add_parse_error(ret, config_validate_max_int(config.custom_sprite_sheet_settings.end_working_frames,
                                                              sprite_sheet_cols, CUSTOM_END_WORKING_FRAMES_KEY));

    ret = config_add_parse_error(ret, config_validate_max_int(config.custom_sprite_sheet_settings.start_moving_frames,
                                                              sprite_sheet_cols, CUSTOM_START_MOVING_FRAMES_KEY));
    ret = config_add_parse_error(ret, config_validate_max_int(config.custom_sprite_sheet_settings.moving_frames,
                                                              sprite_sheet_cols, CUSTOM_MOVING_FRAMES_KEY));
    ret = config_add_parse_error(ret, config_validate_max_int(config.custom_sprite_sheet_settings.end_moving_frames,
                                                              sprite_sheet_cols, CUSTOM_END_MOVING_FRAMES_KEY));

    ret = config_add_parse_error(ret, config_validate_max_int(config.custom_sprite_sheet_settings.start_running_frames,
                                                              sprite_sheet_cols, CUSTOM_START_RUNNING_FRAMES_KEY));
    ret = config_add_parse_error(ret, config_validate_max_int(config.custom_sprite_sheet_settings.running_frames,
                                                              sprite_sheet_cols, CUSTOM_RUNNING_FRAMES_KEY));
    ret = config_add_parse_error(ret, config_validate_max_int(config.custom_sprite_sheet_settings.end_running_frames,
                                                              sprite_sheet_cols, CUSTOM_END_RUNNING_FRAMES_KEY));

    // validate rows
    if (sprite_sheet_rows > 0) {
      if (config.custom_sprite_sheet_settings.idle_row_index >= 0) {
        ret = config_add_parse_error(ret, config_validate_max_int(config.custom_sprite_sheet_settings.idle_row_index,
                                                                  sprite_sheet_rows - 1, CUSTOM_IDLE_ROW_KEY));
      }
      if (config.custom_sprite_sheet_settings.boring_row_index >= 0) {
        ret = config_add_parse_error(ret, config_validate_max_int(config.custom_sprite_sheet_settings.boring_row_index,
                                                                  sprite_sheet_rows - 1, CUSTOM_BORING_ROW_KEY));
      }
      if (config.custom_sprite_sheet_settings.start_writing_row_index >= 0) {
        ret = config_add_parse_error(
            ret, config_validate_max_int(config.custom_sprite_sheet_settings.start_writing_row_index,
                                         sprite_sheet_rows - 1, CUSTOM_START_WRITING_ROW_KEY));
      }
      if (config.custom_sprite_sheet_settings.writing_row_index >= 0) {
        ret = config_add_parse_error(ret, config_validate_max_int(config.custom_sprite_sheet_settings.writing_row_index,
                                                                  sprite_sheet_rows - 1, CUSTOM_WRITING_ROW_KEY));
      }
      if (config.custom_sprite_sheet_settings.end_writing_row_index >= 0) {
        ret = config_add_parse_error(ret,
                                     config_validate_max_int(config.custom_sprite_sheet_settings.end_writing_row_index,
                                                             sprite_sheet_rows - 1, CUSTOM_END_WRITING_ROW_KEY));
      }
      if (config.custom_sprite_sheet_settings.happy_row_index >= 0) {
        ret = config_add_parse_error(ret, config_validate_max_int(config.custom_sprite_sheet_settings.happy_row_index,
                                                                  sprite_sheet_rows - 1, CUSTOM_HAPPY_ROW_KEY));
      }
      if (config.custom_sprite_sheet_settings.asleep_row_index >= 0) {
        ret = config_add_parse_error(ret, config_validate_max_int(config.custom_sprite_sheet_settings.asleep_row_index,
                                                                  sprite_sheet_rows - 1, CUSTOM_ASLEEP_ROW_KEY));
      }
      if (config.custom_sprite_sheet_settings.sleep_row_index >= 0) {
        ret = config_add_parse_error(ret, config_validate_max_int(config.custom_sprite_sheet_settings.sleep_row_index,
                                                                  sprite_sheet_rows - 1, CUSTOM_SLEEP_ROW_KEY));
      }
      if (config.custom_sprite_sheet_settings.wake_up_row_index >= 0) {
        ret = config_add_parse_error(ret, config_validate_max_int(config.custom_sprite_sheet_settings.wake_up_row_index,
                                                                  sprite_sheet_rows - 1, CUSTOM_WAKE_UP_ROW_KEY));
      }
      if (config.custom_sprite_sheet_settings.start_working_row_index >= 0) {
        ret = config_add_parse_error(
            ret, config_validate_max_int(config.custom_sprite_sheet_settings.start_working_row_index,
                                         sprite_sheet_rows - 1, CUSTOM_START_WORKING_ROW_KEY));
      }
      if (config.custom_sprite_sheet_settings.working_row_index >= 0) {
        ret = config_add_parse_error(ret, config_validate_max_int(config.custom_sprite_sheet_settings.working_row_index,
                                                                  sprite_sheet_rows - 1, CUSTOM_WORKING_ROW_KEY));
      }
      if (config.custom_sprite_sheet_settings.end_working_row_index >= 0) {
        ret = config_add_parse_error(ret,
                                     config_validate_max_int(config.custom_sprite_sheet_settings.end_working_row_index,
                                                             sprite_sheet_rows - 1, CUSTOM_END_WORKING_ROW_KEY));
      }
      if (config.custom_sprite_sheet_settings.start_moving_row_index >= 0) {
        ret = config_add_parse_error(ret,
                                     config_validate_max_int(config.custom_sprite_sheet_settings.start_moving_row_index,
                                                             sprite_sheet_rows - 1, CUSTOM_START_MOVING_ROW_KEY));
      }
      if (config.custom_sprite_sheet_settings.moving_row_index >= 0) {
        ret = config_add_parse_error(ret, config_validate_max_int(config.custom_sprite_sheet_settings.moving_row_index,
                                                                  sprite_sheet_rows - 1, CUSTOM_MOVING_ROW_KEY));
      }
      if (config.custom_sprite_sheet_settings.end_moving_row_index >= 0) {
        ret = config_add_parse_error(ret,
                                     config_validate_max_int(config.custom_sprite_sheet_settings.end_moving_row_index,
                                                             sprite_sheet_rows - 1, CUSTOM_END_MOVING_ROW_KEY));
      }
      if (config.custom_sprite_sheet_settings.start_running_row_index >= 0) {
        ret = config_add_parse_error(
            ret, config_validate_max_int(config.custom_sprite_sheet_settings.start_running_row_index,
                                         sprite_sheet_rows - 1, CUSTOM_START_RUNNING_ROW_KEY));
      }
      if (config.custom_sprite_sheet_settings.running_row_index >= 0) {
        ret = config_add_parse_error(ret, config_validate_max_int(config.custom_sprite_sheet_settings.running_row_index,
                                                                  sprite_sheet_rows - 1, CUSTOM_RUNNING_ROW_KEY));
      }
      if (config.custom_sprite_sheet_settings.end_running_row_index >= 0) {
        ret = config_add_parse_error(ret,
                                     config_validate_max_int(config.custom_sprite_sheet_settings.end_running_row_index,
                                                             sprite_sheet_rows - 1, CUSTOM_END_RUNNING_ROW_KEY));
      }
    } else {
      if (config.custom_sprite_sheet_settings.rows <= 0) {
        BONGOCAT_LOG_WARNING("custom sprite sheet has no rows");
        ret = config_add_parse_error(ret, config_parsing_error_t::InvalidCustomSpriteSheetRows);
      }
    }

    // validate sprite sheet file
    if (config.custom_sprite_sheet_filename) {
      constexpr size_t PNG_SIGNATURE_SIZE = 8;
      constexpr unsigned char PNG_SIGNATURE[PNG_SIGNATURE_SIZE] = {0x89, 'P', 'N', 'G', '\r', '\n', 0x1A, '\n'};

      // Try to open the file
      platform::FileDescriptor fd(open(config.custom_sprite_sheet_filename.c_str(), O_RDONLY));
      if (fd._fd < 0) {
        BONGOCAT_LOG_ERROR("Custom Sprite Sheet doesn't exist or can't be opened: %s",
                           config.custom_sprite_sheet_filename.c_str());
        ret = config_add_parse_error(ret, config_parsing_error_t::CustomSpriteSheetFileNotFound);
        return ret;
      }

      struct stat st;
      if (fstat(fd._fd, &st) < 0) {
        BONGOCAT_LOG_ERROR("Custom Sprite Sheet can't be opened: %s", config.custom_sprite_sheet_filename.c_str());
        ret = config_add_parse_error(ret, config_parsing_error_t::CanNotOpenCustomSpriteSheet);
        return ret;
      }
      if (st.st_size == 0) {
        BONGOCAT_LOG_ERROR("Custom Sprite Sheet is an empty file: %s", config.custom_sprite_sheet_filename.c_str());
        ret = config_add_parse_error(ret, config_parsing_error_t::CustomSpriteSheetFileEmpty);
        return ret;
      }

      unsigned char header[PNG_SIGNATURE_SIZE] = {0};
      const ssize_t n = read(fd._fd, header, PNG_SIGNATURE_SIZE);
      if (n < static_cast<ssize_t>(PNG_SIGNATURE_SIZE)) {
        BONGOCAT_LOG_ERROR("Failed to read PNG header: %s", config.custom_sprite_sheet_filename.c_str());
        ret = config_add_parse_error(ret, config_parsing_error_t::CustomSpriteSheetInvalidPNGHeader);
        return ret;
      }
      if (memcmp(header, PNG_SIGNATURE, PNG_SIGNATURE_SIZE) != 0) {
        BONGOCAT_LOG_ERROR("Invalid PNG signature: %s", config.custom_sprite_sheet_filename.c_str());
        ret = config_add_parse_error(ret, config_parsing_error_t::CustomSpriteSheetInvalidPNGSignature);
        return ret;
      }
    } else {
      // empty custom_sprite_sheet_filename
      BONGOCAT_LOG_WARNING("custom_sprite_sheet_filename is empty");
      ret = config_add_parse_error(ret, config_parsing_error_t::CustomSpriteSheetFilenameEmpty);
    }

    // validate frames
    if (config.custom_sprite_sheet_settings.idle_frames <= 0) {
      BONGOCAT_LOG_WARNING("custom sprite sheet needs at least an idle animation");
      ret = config_add_parse_error(ret, config_parsing_error_t::CustomSpriteSheetRequiredIdleAnimation);
    }

    if (config.custom_sprite_sheet_settings.wake_up_frames > 0 &&
        (config.custom_sprite_sheet_settings.asleep_frames <= 0 ||
         config.custom_sprite_sheet_settings.sleep_frames <= 0)) {
      BONGOCAT_LOG_WARNING("custom sprite sheet has a wake up animation, but no sleep animation");
      ret = config_add_parse_info(ret, config_parsing_info_t::CustomSpriteSheetRequiredSleepAnimation);
    }

    if (config.custom_sprite_sheet_settings.feature_mirror_x_moving >= 0 &&
        (config.custom_sprite_sheet_settings.start_moving_frames <= 0 &&
         config.custom_sprite_sheet_settings.moving_frames <= 0 &&
         config.custom_sprite_sheet_settings.end_moving_frames <= 0)) {
      BONGOCAT_LOG_WARNING("feature_mirror_x_moving for custom sprite sheet is used, but has no moving animation");
      ret = config_add_parse_info(ret, config_parsing_info_t::CustomSpriteSheetRequiredMovingAnimation);
    }

    if ((config.custom_sprite_sheet_settings.feature_toggle_writing_frames >= 0 ||
         config.custom_sprite_sheet_settings.feature_toggle_writing_frames_random >= 0) &&
        (config.custom_sprite_sheet_settings.start_writing_frames <= 0 &&
         config.custom_sprite_sheet_settings.writing_frames <= 0 &&
         config.custom_sprite_sheet_settings.end_writing_frames <= 0)) {
      BONGOCAT_LOG_WARNING(
          "feature_toggle_writing_frames for custom sprite sheet is used, but has no writing animation");
      ret = config_add_parse_info(ret, config_parsing_info_t::CustomSpriteSheetRequiredMovingAnimation);
    }

    if (config.enable_scheduled_sleep && (config.custom_sprite_sheet_settings.asleep_frames <= 0 &&
                                          config.custom_sprite_sheet_settings.sleep_frames <= 0)) {
      BONGOCAT_LOG_WARNING("enable_scheduled_sleep is enabled, but custom sprite sheet has no sleep animation");
      ret = config_add_parse_info(ret, config_parsing_info_t::CustomSpriteSheetRequiredSleepAnimation);
    }
    if (config.happy_kpm >= 0 && (config.custom_sprite_sheet_settings.happy_frames <= 0)) {
      BONGOCAT_LOG_WARNING("happy_kpm is used, but custom sprite sheet has no happy animation");
      ret = config_add_parse_info(ret, config_parsing_info_t::CustomSpriteSheetRequiredHappyAnimation);
    }
  }

  if (ret.errors != config_parsing_error_t::Success) {
    ret = config_add_parse_error(ret, config_parsing_error_t::InvalidCustomSpriteSheetSettings);
  }

  return ret;
}

static config_parse_result_t config_validate_appearance(config_t& config) {
  using namespace assets;
  using namespace animation;
  config_parse_result_t ret{};
  // Validate opacity
  ret = config_add_parse_error(ret, config_clamp_int(config.overlay_opacity, 0, 255, OVERLAY_OPACITY_KEY));

  switch (config.animation_sprite_sheet_layout) {
  case config_animation_sprite_sheet_layout_t::None:
    BONGOCAT_LOG_WARNING("Cant determine sprite sheet layout");
    ret = config_add_parse_error(ret, config_parsing_error_t::InvalidAnimationSpriteSheetLayout);
    break;
  case config_animation_sprite_sheet_layout_t::Bongocat:
    if constexpr (features::EnableBongocatEmbeddedAssets) {
      // Validate animation index
      static_assert(BONGOCAT_ANIMATIONS_COUNT <= INT_MAX);
      if (config.animation_index < 0 || config.animation_index >= static_cast<int>(BONGOCAT_ANIMATIONS_COUNT)) {
        BONGOCAT_LOG_WARNING("%s %d out of range [0-%d], resetting to 0", ANIMATION_INDEX_KEY, config.animation_index,
                             BONGOCAT_ANIMATIONS_COUNT - 1);
        config.animation_index = 0;
        ret = config_add_parse_error(ret, config_parsing_error_t::OutOfRangeAnimationIndex);
      }
      // Validate idle frame
      static_assert(animation::BONGOCAT_NUM_FRAMES <= INT_MAX);
      if (config.idle_frame < 0 || config.idle_frame >= static_cast<int>(BONGOCAT_NUM_FRAMES)) {
        BONGOCAT_LOG_WARNING("%s %d out of range [0-%d], resetting to 0", IDLE_FRAME_KEY, config.idle_frame,
                             BONGOCAT_NUM_FRAMES - 1);
        config.idle_frame = 0;
        ret = config_add_parse_error(ret, config_parsing_error_t::OutOfRangeIdleFrameAnimationIndex);
      }
    }
    break;
  case config_animation_sprite_sheet_layout_t::Dm:
    if constexpr (features::EnableDmEmbeddedAssets) {
      // Validate animation index
      static_assert(DM_ANIMATIONS_COUNT <= INT_MAX);
      if (config.animation_index < 0 || config.animation_index >= static_cast<int>(DM_ANIMATIONS_COUNT)) {
        BONGOCAT_LOG_WARNING("%s %d out of range [0-%d], resetting to 0", ANIMATION_INDEX_KEY, config.animation_index,
                             assets::DM_ANIMATIONS_COUNT - 1);
        config.animation_index = 0;
        ret = config_add_parse_error(ret, config_parsing_error_t::OutOfRangeAnimationIndex);
      }
      // Validate idle frame
      static_assert(animation::MAX_DIGIMON_FRAMES <= INT_MAX);
      if (config.idle_frame < 0 || config.idle_frame >= static_cast<int>(animation::MAX_DIGIMON_FRAMES)) {
        BONGOCAT_LOG_WARNING("%s %d out of range [0-%d], resetting to 0", IDLE_FRAME_KEY, config.idle_frame,
                             animation::MAX_DIGIMON_FRAMES - 1);
        config.idle_frame = 0;
        ret = config_add_parse_error(ret, config_parsing_error_t::OutOfRangeIdleFrameAnimationIndex);
      }
    }
    break;
  case config_animation_sprite_sheet_layout_t::Pkmn:
    if constexpr (features::EnablePkmnEmbeddedAssets) {
      // Validate animation index
      static_assert(PKMN_ANIMATIONS_COUNT <= INT_MAX);
      if (config.animation_index < 0 || config.animation_index >= static_cast<int>(PKMN_ANIMATIONS_COUNT)) {
        BONGOCAT_LOG_WARNING("%s %d out of range [0-%d], resetting to 0", ANIMATION_INDEX_KEY, config.animation_index,
                             assets::PKMN_ANIMATIONS_COUNT - 1);
        config.animation_index = 0;
        ret = config_add_parse_error(ret, config_parsing_error_t::OutOfRangeAnimationIndex);
      }
      // Validate idle frame
      static_assert(animation::MAX_PKMN_FRAMES <= INT_MAX);
      if (config.idle_frame < 0 || config.idle_frame >= static_cast<int>(MAX_PKMN_FRAMES)) {
        BONGOCAT_LOG_WARNING("%s %d out of range [0-%d], resetting to 0", IDLE_FRAME_KEY, config.idle_frame,
                             MAX_PKMN_FRAMES - 1);
        config.idle_frame = 0;
        ret = config_add_parse_error(ret, config_parsing_error_t::OutOfRangeIdleFrameAnimationIndex);
      }
    }
    break;
  case config_animation_sprite_sheet_layout_t::MsAgent:
    if constexpr (features::EnableMsAgentEmbeddedAssets) {
      // Validate animation index
      static_assert(assets::MS_AGENTS_ANIMATIONS_COUNT <= INT_MAX);
      if (config.animation_index < 0 || config.animation_index >= static_cast<int>(MS_AGENTS_ANIMATIONS_COUNT)) {
        BONGOCAT_LOG_WARNING("%s %d out of range [0-%d], resetting to 0", ANIMATION_INDEX_KEY, config.animation_index,
                             MS_AGENTS_ANIMATIONS_COUNT - 1);
        config.animation_index = 0;
        ret = config_add_parse_error(ret, config_parsing_error_t::OutOfRangeAnimationIndex);
      }
      // Validate idle frame
      static_assert(assets::MS_AGENT_MAX_SPRITE_SHEET_COL_FRAMES <= INT_MAX);
      if (config.idle_frame < 0 || config.idle_frame >= static_cast<int>(MS_AGENT_MAX_SPRITE_SHEET_COL_FRAMES)) {
        BONGOCAT_LOG_WARNING("%s %d out of range [0-%d], resetting to 0", IDLE_FRAME_KEY, config.idle_frame,
                             MS_AGENT_MAX_SPRITE_SHEET_COL_FRAMES - 1);
        config.idle_frame = 0;
        ret = config_add_parse_error(ret, config_parsing_error_t::OutOfRangeIdleFrameAnimationIndex);
      }
    }
    break;
  case config_animation_sprite_sheet_layout_t::Custom:
    static_assert(CUSTOM_ANIM_INDEX <= INT_MAX);
    static_assert(MAX_MISC_ANIM_INDEX <= INT_MAX);
    if constexpr (features::EnableCustomSpriteSheetsAssets) {
      if (config._custom) {
        assert(config.animation_custom_set == config_animation_custom_set_t::custom);
        // Validate animation index
        if (config.animation_index < 0 || config.animation_index > static_cast<int>(CUSTOM_ANIM_INDEX)) {
          BONGOCAT_LOG_WARNING("%s %d out of range [%d], resetting to 0", ANIMATION_INDEX_KEY, config.animation_index,
                               CUSTOM_ANIM_INDEX);
          config.animation_index = 0;
          ret = config_add_parse_error(ret, config_parsing_error_t::OutOfRangeIdleFrameAnimationIndex);
        }
        /// @TODO: validate max (idle) frames
      }
    }
    if (!config._custom) {
      switch (config.animation_custom_set) {
      case config_animation_custom_set_t::None:
        break;
      case config_animation_custom_set_t::misc:
        if constexpr (features::EnableMiscEmbeddedAssets) {
          // Validate animation index
          if (config.animation_index < 0 || config.animation_index > static_cast<int>(MAX_MISC_ANIM_INDEX)) {
            BONGOCAT_LOG_WARNING("%s %d out of range [0-%d], resetting to 0", ANIMATION_INDEX_KEY,
                                 config.animation_index, MAX_MISC_ANIM_INDEX);
            config.animation_index = 0;
            ret = config_add_parse_error(ret, config_parsing_error_t::OutOfRangeAnimationIndex);
          }
          // Validate idle frame
          static_assert(assets::MISC_MAX_SPRITE_SHEET_COL_FRAMES <= INT_MAX);
          if (config.idle_frame < 0 || config.idle_frame >= static_cast<int>(MISC_MAX_SPRITE_SHEET_COL_FRAMES)) {
            BONGOCAT_LOG_WARNING("%s %d out of range [0-%d], resetting to 0", IDLE_FRAME_KEY, config.idle_frame,
                                 assets::MISC_MAX_SPRITE_SHEET_COL_FRAMES - 1);
            config.idle_frame = 0;
            ret = config_add_parse_error(ret, config_parsing_error_t::OutOfRangeIdleFrameAnimationIndex);
          }
        }
        break;
      case config_animation_custom_set_t::pmd:
        if constexpr (features::EnablePmdEmbeddedAssets) {
          static_assert(assets::PMD_ANIM_COUNT <= INT_MAX);
          // Validate animation index
          if (config.animation_index < 0 || config.animation_index >= static_cast<int>(PMD_ANIM_COUNT)) {
            BONGOCAT_LOG_WARNING("%s %d out of range [0-%d], resetting to 0", ANIMATION_INDEX_KEY,
                                 config.animation_index, PMD_ANIM_COUNT - 1);
            config.animation_index = 0;
            ret = config_add_parse_error(ret, config_parsing_error_t::OutOfRangeAnimationIndex);
          }
          // Validate idle frame
          if (config.idle_frame < 0 || config.idle_frame >= static_cast<int>(PMD_ANIM_COUNT)) {
            BONGOCAT_LOG_WARNING("%s %d out of range [0-%d], resetting to 0", IDLE_FRAME_KEY, config.idle_frame,
                                 assets::PMD_ANIM_COUNT - 1);
            config.idle_frame = 0;
            ret = config_add_parse_error(ret, config_parsing_error_t::OutOfRangeIdleFrameAnimationIndex);
          }
        }
        break;
      case config_animation_custom_set_t::custom:
        break;
      }
    }
    break;
    /// @NOTE(assets): 5. add animation_index validation
  }
  return ret;
}

static config_parse_result_t config_validate_enums(config_t& config) {
  config_parse_result_t ret{};
  // Validate layer
  if (config.layer != layer_type_t::LAYER_BACKGROUND && config.layer != layer_type_t::LAYER_BOTTOM &&
      config.layer != layer_type_t::LAYER_TOP && config.layer != layer_type_t::LAYER_OVERLAY) {
    BONGOCAT_LOG_WARNING("Invalid layer %d, resetting to top", config.layer);
    config.layer = layer_type_t::LAYER_TOP;
    ret = config_add_parse_error(ret, config_parsing_error_t::InvalidLayer);
  }

  // Validate overlay_position
  if (config.overlay_position != overlay_position_t::POSITION_TOP &&
      config.overlay_position != overlay_position_t::POSITION_BOTTOM) {
    BONGOCAT_LOG_WARNING("Invalid %s %d, resetting to top", OVERLAY_OPACITY_KEY, config.overlay_position);
    config.overlay_position = overlay_position_t::POSITION_TOP;
    ret = config_add_parse_error(ret, config_parsing_error_t::InvalidOverlayPosition);
  }

  // Validate cat_align
  if (config.cat_align != align_type_t::ALIGN_CENTER && config.cat_align != align_type_t::ALIGN_LEFT &&
      config.cat_align != align_type_t::ALIGN_RIGHT) {
    BONGOCAT_LOG_WARNING("Invalid %s %d, resetting to center", CAT_ALIGN_KEY, config.cat_align);
    config.cat_align = align_type_t::ALIGN_CENTER;
    ret = config_add_parse_error(ret, config_parsing_error_t::InvalidCatAlign);
  }

  if constexpr (features::EnableEvolution) {
    // Validate evolution
    if (config.evolution != evolution_time_mode_t::NONE && config.evolution != evolution_time_mode_t::NORMAL &&
        config.evolution != evolution_time_mode_t::PROGRAM_START && config.evolution != evolution_time_mode_t::UPTIME) {
      BONGOCAT_LOG_WARNING("Invalid %s %d, resetting to 'none'", EVOLUTION_KEY, config.evolution);
      config.evolution = evolution_time_mode_t::NONE;
      ret = config_add_parse_error(ret, config_parsing_error_t::InvalidEvolution);
    }
    if (config.evolution != evolution_time_mode_t::NONE && config.evolution_speed_factor <= 0.0) {
      BONGOCAT_LOG_WARNING("Invalid %s is zero or below (%f), resetting to 1.0", EVOLUTION_SPEED_FACTOR_KEY,
                           config.evolution_speed_factor);
      config.evolution_speed_factor = 1.0;
      ret = config_add_parse_error(ret, config_parsing_error_t::InvalidEvolutionSpeed);
    }
  }

  return ret;
}

static config_parse_result_t config_validate_time(config_t& config) {
  config_parse_result_t ret{};
  if (config.enable_scheduled_sleep) {
    const int begin_minutes = (config.sleep_begin.hour * 60) + config.sleep_begin.min;
    const int end_minutes = (config.sleep_end.hour * 60) + config.sleep_end.min;

    if (begin_minutes == end_minutes) {
      BONGOCAT_LOG_WARNING("Sleep mode is enabled, but time is equal: %02d:%02d, disable sleep mode",
                           config.sleep_begin.hour, config.sleep_begin.min);

      config.enable_scheduled_sleep = false;
      // config.sleep_begin.hour = 0;
      // config.sleep_begin.min = 0;
      // config.sleep_end.hour = 0;
      // config.sleep_end.min = 0;

      ret = config_add_parse_error(ret, config_parsing_error_t::InvalidSleepTime);
    }
  }
  return ret;
}

static config_parse_result_t config_validate(config_t& config) {
  config_parse_result_t ret{};
  // Normalize boolean values
  /*
  config.enable_debug = config.enable_debug >= 1 ? 1 : 0;
  config.invert_color = config.invert_color >= 1 ? 1 : 0;
  config.idle_animation = config.idle_animation >= 1 ? 1 : 0;
  config.enable_scheduled_sleep = config.enable_scheduled_sleep >= 1 ? 1 : 0;
  config.mirror_x = config.mirror_x >= 1 ? 1 : 0;
  config.mirror_y = config.mirror_y >= 1 ? 1 : 0;
  config.randomize_index = config.randomize_index >= 1 ? 1 : 0;
  config.randomize_on_reload = config.randomize_on_reload >= 1 ? 1 : 0;
  config.enable_antialiasing = config.enable_antialiasing >= 1 ? 1 : 0;
  config.enable_movement_debug = config.enable_movement_debug >= 1 ? 1 : 0;
  config.enable_hand_mapping = config.enable_hand_mapping >= 1 ? 1 : 0;
  config.disable_fullscreen_hide = config.disable_fullscreen_hide >= 1 ? 1 : 0;
  */

  ret = config_chain_parse_result(ret, config_validate_dimensions(config));
  ret = config_chain_parse_result(ret, config_validate_timing(config));
  ret = config_chain_parse_result(ret, config_validate_appearance(config));
  ret = config_chain_parse_result(ret, config_validate_enums(config));
  ret = config_chain_parse_result(ret, config_validate_time(config));
  ret = config_chain_parse_result(ret, config_validate_kpm(config));
  ret = config_chain_parse_result(ret, config_validate_update(config));
  ret = config_chain_parse_result(ret, config_validate_custom(config));

  return ret;
}

// =============================================================================
// DEVICE MANAGEMENT MODULE
// =============================================================================

static config_parse_result_t config_add_keyboard_device(config_t& config, const char *device_path) {
  BONGOCAT_CHECK_NULL(device_path, config_parse_result_t(config_parsing_error_t::InvalidInputDeviceName));

  assert(config.num_keyboard_devices >= 0 && config.num_keyboard_devices < INT_MAX - 1);

  const int old_num_keyboard_devices = config.num_keyboard_devices;

  static_assert(input::MAX_INPUT_DEVICES <= INT_MAX);
  if (old_num_keyboard_devices >= static_cast<int>(input::MAX_INPUT_DEVICES)) {
    BONGOCAT_LOG_WARNING("Can not add more devices from config, max. reach: %d", input::MAX_INPUT_DEVICES);
    return config._strict ? config_parse_result_t(config_parsing_error_t::MaxDeviceNamesReached)
                          : config_parse_result_t(config_parsing_warning_t::MaxDeviceNamesReached);
  }
  const int new_num_keyboard_devices = old_num_keyboard_devices + 1;
  assert(new_num_keyboard_devices >= 0);
  assert(static_cast<size_t>(new_num_keyboard_devices) <= input::MAX_INPUT_DEVICES);

  // Add new device path
  config.keyboard_devices[old_num_keyboard_devices] = duplicate_string(device_path);
  if (!config.keyboard_devices[old_num_keyboard_devices]) [[unlikely]] {
    // free new copied strings
    for (int i = 0; i < old_num_keyboard_devices; i++) {
      /*
      if (config.keyboard_devices[i] != BONGOCAT_NULLPTR) {
        ::free(config.keyboard_devices[i]);
        config.keyboard_devices[i] = BONGOCAT_NULLPTR;
      }
      */
      release_allocated_string(config.keyboard_devices[i]);
    }
    config.num_keyboard_devices = old_num_keyboard_devices;
    BONGOCAT_LOG_ERROR("Failed to copy new keyboard device path");
    return config_parse_result_t(
        flag_add(config_parsing_error_t::StringMemoryError, config_parsing_error_t::InvalidInputDeviceName));
  }

  // update new size
  config.num_keyboard_devices = new_num_keyboard_devices;

  return {};
}

static config_parse_result_t config_add_keyboard_name(config_t& config, const char *device_path) {
  BONGOCAT_CHECK_NULL(device_path, config_parse_result_t(config_parsing_error_t::InvalidInputDeviceName));

  assert(config._num_keyboard_names >= 0 && config._num_keyboard_names < INT_MAX - 1);

  const int old_num_keyboard_names = config._num_keyboard_names;

  static_assert(input::MAX_INPUT_DEVICES <= INT_MAX);
  if (old_num_keyboard_names >= static_cast<int>(input::MAX_INPUT_DEVICES)) {
    BONGOCAT_LOG_WARNING("Can not add more keyboard_names from config, max. reach: %d", input::MAX_INPUT_DEVICES);
    return config._strict ? config_parse_result_t(config_parsing_error_t::MaxDeviceNamesReached)
                          : config_parse_result_t(config_parsing_warning_t::MaxDeviceNamesReached);
  }
  const int new_num_keyboard_names = old_num_keyboard_names + 1;
  assert(new_num_keyboard_names >= 0);
  assert(static_cast<size_t>(new_num_keyboard_names) <= input::MAX_INPUT_DEVICES);

  // Add new device path
  config._keyboard_names[old_num_keyboard_names] = duplicate_string(device_path);
  if (!config._keyboard_names[old_num_keyboard_names]) [[unlikely]] {
    config._num_keyboard_names = old_num_keyboard_names;
    BONGOCAT_LOG_ERROR("Failed to copy new keyboard name path");
    return config_parse_result_t(
        flag_add(config_parsing_error_t::StringMemoryError, config_parsing_error_t::InvalidInputDeviceName));
  }

  // update new size
  config._num_keyboard_names = new_num_keyboard_names;

  return {};
}

static config_parse_result_t config_resolve_devices(config_t& config) {
  if (config._num_keyboard_names == 0) {
    return {};
  }

  DIR *dir = opendir("/dev/input");
  if (dir == BONGOCAT_NULLPTR) {
    BONGOCAT_LOG_WARNING("Failed to open /dev/input for scanning: %s", strerror(errno));
    return config_parse_result_t(config_parsing_error_t::InvalidInputDeviceName);
  }

  [[maybe_unused]] const int devices_before = config.num_keyboard_devices;
  struct dirent *entry;
  char path[PATH_MAX];
  char name[256] = {0};

  constexpr const char *event_name = "event";
  constexpr size_t event_name_len = 5;
  assert(strlen(event_name) == event_name_len);

  config_parse_result_t ret;
  while ((entry = readdir(dir)) != BONGOCAT_NULLPTR) {
    // Only process event* nodes
    if (strncmp(entry->d_name, event_name, event_name_len) != 0) {
      continue;
    }
    // Reject any d_name with path separators or traversal (defensive)
    if (strchr(entry->d_name, '/') != BONGOCAT_NULLPTR || strstr(entry->d_name, "..") != BONGOCAT_NULLPTR) {
      continue;
    }

    snprintf(path, sizeof(path), "/dev/input/%s", entry->d_name);
    platform::FileDescriptor fd = platform::FileDescriptor(open(path, O_RDONLY));
    if (fd._fd < 0) {
      continue;
    }

    memset(name, 0, sizeof(name));
    if (ioctl(fd._fd, EVIOCGNAME(sizeof(name) - 1), name) < 0) {
      continue;
    }
    name[sizeof(name) - 1] = '\0';

    assert(config._num_keyboard_names >= 0);
    for (size_t i = 0; i < static_cast<size_t>(config._num_keyboard_names); i++) {
      assert(config._keyboard_names[i]);
      if (strstr(name, config._keyboard_names[i].c_str()) != BONGOCAT_NULLPTR) {
        BONGOCAT_LOG_VERBOSE("Found device matching name '%s' (Device: '%s'): %s", config._keyboard_names[i].c_str(),
                             name, path);
        ret = config_chain_parse_result(ret, config_add_keyboard_device(config, path));
      }
    }
  }

  // BONGOCAT_LOG_VERBOSE("Device name resolution: added %d device(s) from %d name pattern(s)",
  //                   config.num_keyboard_devices - devices_before,
  //                   config._num_keyboard_names);

  closedir(dir);
  return ret;
}

static void config_cleanup_devices(config_t& config) {
  assert(config.num_keyboard_devices >= 0);
  for (size_t i = 0; i < input::MAX_INPUT_DEVICES; i++) {
    if (i < static_cast<size_t>(config.num_keyboard_devices)) {
      release_allocated_string(config.keyboard_devices[i]);
      config.keyboard_devices[i] = BONGOCAT_NULLPTR;
    }
  }
  config.num_keyboard_devices = 0;

  assert(config._num_keyboard_names >= 0);
  for (size_t i = 0; i < static_cast<size_t>(config._num_keyboard_names); i++) {
    if (i < static_cast<size_t>(config._num_keyboard_names)) {
      release_allocated_string(config._keyboard_names[i]);
      config._keyboard_names[i] = BONGOCAT_NULLPTR;
    }
  }
  config._num_keyboard_names = 0;
}

// =============================================================================
// CONFIGURATION PARSING MODULE
// =============================================================================

static char *config_trim_str(char *key) {
  char *key_start = key;
  while (*key_start == ' ' || *key_start == '\t') {
    key_start++;
  }

  char *key_end = key_start + strlen(key_start) - 1;
  while (key_end > key_start && (*key_end == ' ' || *key_end == '\t')) {
    *key_end = '\0';
    key_end--;
  }

  return key_start;
}

static config_parse_result_t config_parse_boolean_key(config_t& config, const char *key, const char *value) {
  bool *target_boolean = [&]() -> bool * {
    if (strcmp(key, MIRROR_X_KEY) == 0) {
      return &config.mirror_x;
    } else if (strcmp(key, MIRROR_Y_KEY) == 0) {
      return &config.mirror_y;
    } else if (strcmp(key, ENABLE_ANTIALIASING_KEY) == 0) {
      return &config.enable_antialiasing;
    } else if (strcmp(key, ENABLE_DEBUG_KEY) == 0) {
      return &config.enable_debug;
    } else if (strcmp(key, INVERT_COLOR_KEY) == 0) {
      return &config.invert_color;
    } else if (strcmp(key, ENABLE_SCHEDULED_SLEEP_KEY) == 0) {
      return &config.enable_scheduled_sleep;
    } else if (strcmp(key, IDLE_ANIMATION_KEY) == 0) {
      return &config.idle_animation;
    } else if (strcmp(key, RANDOM_KEY) == 0) {
      return &config.randomize_index;
    } else if (strcmp(key, RANDOM_ON_RELOAD_KEY) == 0) {
      return &config.randomize_on_reload;
    } else if (strcmp(key, ENABLE_HAND_MAPPING_KEY) == 0) {
      return &config.enable_hand_mapping;
    } else if (strcmp(key, DISABLE_FULLSCREEN_HIDE_KEY) == 0) {
      return &config.disable_fullscreen_hide;
    } else if (strcmp(key, ENABLE_MOVEMENT_DEBUG_KEY) == 0) {
      return &config.enable_movement_debug;
    }

    return BONGOCAT_NULLPTR;
  }();
  if (target_boolean == BONGOCAT_NULLPTR) {
    return config_parse_result_t(config_parsing_info_t::UnknownConfigKey);
  }

  const auto [bool_value, read_error] = [&]() -> created_result_t<bool> {
    if (strcasecmp(value, "true") == 0 || strcasecmp(value, "yes") == 0 || strcasecmp(value, "on") == 0) {
      return true;
    }
    if (strcasecmp(value, "false") == 0 || strcasecmp(value, "no") == 0 || strcasecmp(value, "off") == 0) {
      return false;
    }

    errno = 0;
    char *endptr_int = BONGOCAT_NULLPTR;
    const auto read_value = strtol(value, &endptr_int, 10);
    if (errno != 0 || endptr_int == value || (*endptr_int != '\0' && *endptr_int != ' ' && *endptr_int != '\t')) {
      return bongocat_error_t::BONGOCAT_ERROR_INVALID_PARAM;
    }
    if (read_value < INT32_MIN || read_value > INT32_MAX) {
      return bongocat_error_t::BONGOCAT_ERROR_INVALID_PARAM;
    }

    return static_cast<int>(read_value) > 0;
  }();
  if (read_error != bongocat_error_t::BONGOCAT_SUCCESS) {
    return config_parse_result_t(config_parsing_error_t::InvalidBoolean);
  }

  assert(target_boolean != BONGOCAT_NULLPTR);
  if (features::EnableEvolution && strcmp(key, EVOLUTION_KEY) == 0) {
    config.evolution = bool_value ? evolution_time_mode_t::NORMAL : evolution_time_mode_t::NONE;
  } else {
    *target_boolean = bool_value;
  }

  return {};
}

static config_parse_result_t config_parse_integer_key(config_t& config, const char *key, const char *value) {
  const auto parse_int = [&](int& out) -> config_parse_result_t {
    errno = 0;
    char *endptr = BONGOCAT_NULLPTR;
    const long read_value = strtol(value, &endptr, 10);
    if (errno != 0 || endptr == value || (*endptr != '\0' && *endptr != ' ' && *endptr != '\t')) {
      return config_parse_result_t(config_parsing_error_t::InvalidInteger);
    }
    if (read_value < INT_MIN || read_value > INT_MAX) {
      return config_parse_result_t(config_parsing_error_t::OutOfRangeInt);
    }
    out = static_cast<int>(read_value);
    return {};
  };
  //  value-1
  const auto parse_int_row = [&](int& out) -> config_parse_result_t {
    int raw = 0;
    if (auto r = parse_int(raw); r.errors != config_parsing_error_t::Success) {
      return r;
    }
    out = raw - 1;  // 1-based in config, 0-based internally; -1 means unset
    return {};
  };
  // double fallback
  const auto parse_int_as_double = [&](double& out) -> config_parse_result_t {
    int raw = 0;
    if (auto r = parse_int(raw); r.errors != config_parsing_error_t::Success) {
      return r;
    }
    out = static_cast<double>(raw);
    return {};
  };
  // time based int
  const auto parse_int_sec_to_ms = [&](int& out) -> config_parse_result_t {
    int raw = 0;
    if (auto r = parse_int(raw); r.errors != config_parsing_error_t::Success) {
      return r;
    }
    out = raw * 1000;
    return {};
  };

  if (strcmp(key, CAT_X_OFFSET_KEY) == 0) {
    return parse_int(config.cat_x_offset);
  }
  if (strcmp(key, CAT_Y_OFFSET_KEY) == 0) {
    return parse_int(config.cat_y_offset);
  }
  if (strcmp(key, CAT_HEIGHT_KEY) == 0) {
    return parse_int(config.cat_height);
  }
  if (strcmp(key, OVERLAY_HEIGHT_KEY) == 0) {
    return parse_int(config.overlay_height);
  }
  if (strcmp(key, IDLE_FRAME_KEY) == 0) {
    return parse_int(config.idle_frame);
  }
  if (strcmp(key, KEYPRESS_DURATION_KEY) == 0) {
    return parse_int(config.keypress_duration_ms);
  }
  if (strcmp(key, TEST_ANIMATION_DURATION_KEY) == 0) {
    return parse_int(config.test_animation_duration_ms);
  }
  if (strcmp(key, TEST_ANIMATION_INTERVAL_KEY) == 0) {
    return parse_int(config.test_animation_interval_sec);
  }
  if (strcmp(key, FPS_KEY) == 0) {
    return parse_int(config.fps);
  }
  if (strcmp(key, OVERLAY_OPACITY_KEY) == 0) {
    return parse_int(config.overlay_opacity);
  }
  if (strcmp(key, ANIMATION_INDEX_KEY) == 0) {
    return parse_int(config.animation_index);
  }
  if (strcmp(key, PADDING_X_KEY) == 0) {
    return parse_int(config.padding_x);
  }
  if (strcmp(key, PADDING_Y_KEY) == 0) {
    return parse_int(config.padding_y);
  }
  if (strcmp(key, IDLE_SLEEP_TIMEOUT_KEY) == 0) {
    return parse_int(config.idle_sleep_timeout_sec);
  }
  if (strcmp(key, HAPPY_KPM_KEY) == 0) {
    return parse_int(config.happy_kpm);
  }
  if (strcmp(key, ANIMATION_SPEED_KEY) == 0) {
    return parse_int(config.animation_speed_ms);
  }
  if (strcmp(key, INPUT_FPS_KEY) == 0) {
    return parse_int(config.input_fps);
  }
  if (strcmp(key, UPDATE_RATE_KEY) == 0) {
    return parse_int(config.update_rate_ms);
  }
  if (strcmp(key, MOVEMENT_RADIUS_KEY) == 0) {
    return parse_int(config.movement_radius);
  }
  if (strcmp(key, MOVEMENT_SPEED_KEY) == 0) {
    return parse_int(config.movement_speed);
  }
  if (strcmp(key, SCREEN_WIDTH_KEY) == 0) {
    return parse_int(config.screen_width);
  }
  if (strcmp(key, HOTPLUG_SCAN_INTERVAL_KEY) == 0) {
    return parse_int_sec_to_ms(config.hotplug_scan_interval_ms);
  }

  // double fields written as int
  if (strcmp(key, CPU_THRESHOLD_KEY) == 0) {
    return parse_int_as_double(config.cpu_threshold);
  }
  if (strcmp(key, CPU_RUNNING_FACTOR_KEY) == 0) {
    return parse_int_as_double(config.cpu_running_factor);
  }
  if (strcmp(key, MOVEMENT_WAIT_FACTOR_KEY) == 0) {
    return parse_int_as_double(config.movement_wait_factor);
  }

  // feature-gated
  if (features::EnableEvolution) {
    if (strcmp(key, EVOLUTION_SPEED_FACTOR_KEY) == 0) {
      return parse_int_as_double(config.evolution_speed_factor);
    }
  }

  if (features::EnableCustomSpriteSheetsAssets) {
    if (strcmp(key, CUSTOM_IDLE_FRAMES_KEY) == 0) {
      return parse_int(config.custom_sprite_sheet_settings.idle_frames);
    }
    if (strcmp(key, CUSTOM_BORING_FRAMES_KEY) == 0) {
      return parse_int(config.custom_sprite_sheet_settings.boring_frames);
    }
    if (strcmp(key, CUSTOM_START_WRITING_FRAMES_KEY) == 0) {
      return parse_int(config.custom_sprite_sheet_settings.start_writing_frames);
    }
    if (strcmp(key, CUSTOM_WRITING_FRAMES_KEY) == 0) {
      return parse_int(config.custom_sprite_sheet_settings.writing_frames);
    }
    if (strcmp(key, CUSTOM_END_WRITING_FRAMES_KEY) == 0) {
      return parse_int(config.custom_sprite_sheet_settings.end_writing_frames);
    }
    if (strcmp(key, CUSTOM_HAPPY_FRAMES_KEY) == 0) {
      return parse_int(config.custom_sprite_sheet_settings.happy_frames);
    }
    if (strcmp(key, CUSTOM_ASLEEP_FRAMES_KEY) == 0) {
      return parse_int(config.custom_sprite_sheet_settings.asleep_frames);
    }
    if (strcmp(key, CUSTOM_SLEEP_FRAMES_KEY) == 0) {
      return parse_int(config.custom_sprite_sheet_settings.sleep_frames);
    }
    if (strcmp(key, CUSTOM_WAKE_UP_FRAMES_KEY) == 0) {
      return parse_int(config.custom_sprite_sheet_settings.wake_up_frames);
    }
    if (strcmp(key, CUSTOM_START_WORKING_FRAMES_KEY) == 0) {
      return parse_int(config.custom_sprite_sheet_settings.start_working_frames);
    }
    if (strcmp(key, CUSTOM_WORKING_FRAMES_KEY) == 0) {
      return parse_int(config.custom_sprite_sheet_settings.working_frames);
    }
    if (strcmp(key, CUSTOM_END_WORKING_FRAMES_KEY) == 0) {
      return parse_int(config.custom_sprite_sheet_settings.end_working_frames);
    }
    if (strcmp(key, CUSTOM_START_MOVING_FRAMES_KEY) == 0) {
      return parse_int(config.custom_sprite_sheet_settings.start_moving_frames);
    }
    if (strcmp(key, CUSTOM_MOVING_FRAMES_KEY) == 0) {
      return parse_int(config.custom_sprite_sheet_settings.moving_frames);
    }
    if (strcmp(key, CUSTOM_END_MOVING_FRAMES_KEY) == 0) {
      return parse_int(config.custom_sprite_sheet_settings.end_moving_frames);
    }
    if (strcmp(key, CUSTOM_START_RUNNING_FRAMES_KEY) == 0) {
      return parse_int(config.custom_sprite_sheet_settings.start_running_frames);
    }
    if (strcmp(key, CUSTOM_RUNNING_FRAMES_KEY) == 0) {
      return parse_int(config.custom_sprite_sheet_settings.running_frames);
    }
    if (strcmp(key, CUSTOM_END_RUNNING_FRAMES_KEY) == 0) {
      return parse_int(config.custom_sprite_sheet_settings.end_running_frames);
    }

    if (strcmp(key, CUSTOM_TOGGLE_WRITING_FRAMES_KEY) == 0) {
      return parse_int(config.custom_sprite_sheet_settings.feature_toggle_writing_frames);
    }
    if (strcmp(key, CUSTOM_TOGGLE_WRITING_FRAMES_RANDOM_KEY) == 0) {
      return parse_int(config.custom_sprite_sheet_settings.feature_toggle_writing_frames_random);
    }
    if (strcmp(key, CUSTOM_MIRROR_X_MOVING_KEY) == 0) {
      return parse_int(config.custom_sprite_sheet_settings.feature_mirror_x_moving);
    }

    if (strcmp(key, CUSTOM_IDLE_ROW_KEY) == 0) {
      return parse_int_row(config.custom_sprite_sheet_settings.idle_row_index);
    }
    if (strcmp(key, CUSTOM_BORING_ROW_KEY) == 0) {
      return parse_int_row(config.custom_sprite_sheet_settings.boring_row_index);
    }
    if (strcmp(key, CUSTOM_START_WRITING_ROW_KEY) == 0) {
      return parse_int_row(config.custom_sprite_sheet_settings.start_writing_row_index);
    }
    if (strcmp(key, CUSTOM_WRITING_ROW_KEY) == 0) {
      return parse_int_row(config.custom_sprite_sheet_settings.writing_row_index);
    }
    if (strcmp(key, CUSTOM_END_WRITING_ROW_KEY) == 0) {
      return parse_int_row(config.custom_sprite_sheet_settings.end_writing_row_index);
    }
    if (strcmp(key, CUSTOM_HAPPY_ROW_KEY) == 0) {
      return parse_int_row(config.custom_sprite_sheet_settings.happy_row_index);
    }
    if (strcmp(key, CUSTOM_ASLEEP_ROW_KEY) == 0) {
      return parse_int_row(config.custom_sprite_sheet_settings.asleep_row_index);
    }
    if (strcmp(key, CUSTOM_SLEEP_ROW_KEY) == 0) {
      return parse_int_row(config.custom_sprite_sheet_settings.sleep_row_index);
    }
    if (strcmp(key, CUSTOM_WAKE_UP_ROW_KEY) == 0) {
      return parse_int_row(config.custom_sprite_sheet_settings.wake_up_row_index);
    }
    if (strcmp(key, CUSTOM_START_WORKING_ROW_KEY) == 0) {
      return parse_int_row(config.custom_sprite_sheet_settings.start_working_row_index);
    }
    if (strcmp(key, CUSTOM_WORKING_ROW_KEY) == 0) {
      return parse_int_row(config.custom_sprite_sheet_settings.working_row_index);
    }
    if (strcmp(key, CUSTOM_END_WORKING_ROW_KEY) == 0) {
      return parse_int_row(config.custom_sprite_sheet_settings.end_working_row_index);
    }
    if (strcmp(key, CUSTOM_START_MOVING_ROW_KEY) == 0) {
      return parse_int_row(config.custom_sprite_sheet_settings.start_moving_row_index);
    }
    if (strcmp(key, CUSTOM_MOVING_ROW_KEY) == 0) {
      return parse_int_row(config.custom_sprite_sheet_settings.moving_row_index);
    }
    if (strcmp(key, CUSTOM_END_MOVING_ROW_KEY) == 0) {
      return parse_int_row(config.custom_sprite_sheet_settings.end_moving_row_index);
    }
    if (strcmp(key, CUSTOM_START_RUNNING_ROW_KEY) == 0) {
      return parse_int_row(config.custom_sprite_sheet_settings.start_running_row_index);
    }
    if (strcmp(key, CUSTOM_RUNNING_ROW_KEY) == 0) {
      return parse_int_row(config.custom_sprite_sheet_settings.running_row_index);
    }
    if (strcmp(key, CUSTOM_END_RUNNING_ROW_KEY) == 0) {
      return parse_int_row(config.custom_sprite_sheet_settings.end_running_row_index);
    }
    if (strcmp(key, CUSTOM_ROWS_KEY) == 0) {
      return parse_int(config.custom_sprite_sheet_settings.rows);
    }

    if (features::EnableEvolution) {
      if (strcmp(key, CUSTOM_START_EVOLVING_ROW_KEY) == 0) {
        return parse_int_row(config.custom_sprite_sheet_settings.start_evolving_row_index);
      }
      if (strcmp(key, CUSTOM_EVOLVING_ROW_KEY) == 0) {
        return parse_int_row(config.custom_sprite_sheet_settings.evolving_row_index);
      }
      if (strcmp(key, CUSTOM_AFTER_EVOLVING_ROW_KEY) == 0) {
        return parse_int_row(config.custom_sprite_sheet_settings.after_evolving_row_index);
      }
    }
  }

  return config_parse_result_t(config_parsing_info_t::UnknownConfigKey);
}

static config_parse_result_t config_parse_double_key(config_t& config, const char *key, const char *value) {
  double *target_double = [&]() -> double * {
    if (strcmp(key, CPU_THRESHOLD_KEY) == 0) {
      return &config.cpu_threshold;
    } else if (strcmp(key, CPU_RUNNING_FACTOR_KEY) == 0) {
      return &config.cpu_running_factor;
    } else if (strcmp(key, MOVEMENT_WAIT_FACTOR_KEY) == 0) {
      return &config.movement_wait_factor;
    } else if (features::EnableEvolution && strcmp(key, EVOLUTION_SPEED_FACTOR_KEY) == 0) {
      return &config.evolution_speed_factor;
    }

    return BONGOCAT_NULLPTR;
  }();
  if (target_double == BONGOCAT_NULLPTR) {
    return config_parse_result_t(config_parsing_info_t::UnknownConfigKey);
  }

  errno = 0;
  char *endptr_double = BONGOCAT_NULLPTR;
  const double double_value = strtod(value, &endptr_double);
  if (errno != 0 || endptr_double == value || *endptr_double != '\0') {
    return config_parse_result_t(config_parsing_error_t::InvalidDouble);
  }

  assert(target_double != BONGOCAT_NULLPTR);
  *target_double = double_value;

  return {};
}

static config_parse_result_t config_parse_enum_key(config_t& config, const char *key, const char *value) {
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
      return config_parse_result_t(config_parsing_error_t::InvalidLayer);
    }
  } else if (strcmp(key, OVERLAY_POSITION_KEY) == 0) {
    if (strcmp(value, POSITION_TOP_STR) == 0) {
      config.overlay_position = overlay_position_t::POSITION_TOP;
    } else if (strcmp(value, POSITION_BOTTOM_STR) == 0) {
      config.overlay_position = overlay_position_t::POSITION_BOTTOM;
    } else {
      BONGOCAT_LOG_WARNING("Invalid %s '%s', using 'top'", OVERLAY_POSITION_KEY, value);
      config.overlay_position = overlay_position_t::POSITION_TOP;
      return config_parse_result_t(config_parsing_error_t::InvalidOverlayPosition);
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
      return config_parse_result_t(config_parsing_error_t::InvalidCatAlign);
    }
  } else if (features::EnableEvolution && strcmp(key, EVOLUTION_KEY) == 0) {
    if (strcmp(value, EVOLUTION_TIME_MODE_NONE_STR) == 0) {
      config.evolution = evolution_time_mode_t::NONE;
    } else if (strcmp(value, EVOLUTION_TIME_MODE_NORMAL_STR) == 0) {
      config.evolution = evolution_time_mode_t::NORMAL;
    } else if (strcmp(value, EVOLUTION_TIME_MODE_PROGRAM_START_STR) == 0 ||
               strcmp(value, EVOLUTION_TIME_MODE_PROGRAM_START_ALT_STR) == 0) {
      config.evolution = evolution_time_mode_t::PROGRAM_START;
    } else if (strcmp(value, EVOLUTION_TIME_MODE_UPTIME_STR) == 0) {
      config.evolution = evolution_time_mode_t::UPTIME;
    } else if (strcmp(value, "1") == 0) {
      config.evolution = evolution_time_mode_t::NORMAL;
    } else if (strcmp(value, "0") == 0) {
      config.evolution = evolution_time_mode_t::NONE;
    } else {
      BONGOCAT_LOG_WARNING("Invalid %s '%s', using 'none'", EVOLUTION_KEY, value);
      config.evolution = evolution_time_mode_t::NONE;
      return config_parse_result_t(config_parsing_error_t::InvalidEvolution);
    }
  } else {
    return config_parse_result_t(config_parsing_info_t::UnknownConfigKey);
  }

  return {};
}

config_parse_result_t config_parse_time(const char *value, int& hour, int& min) {
  char *endptr = BONGOCAT_NULLPTR;
  errno = 0;

  // Parse hour
  const long h = strtol(value, &endptr, 10);
  if (endptr == value || *endptr != ':' || errno == ERANGE || h < 0 || h > 23) {
    return config_parse_result_t(config_parsing_error_t::InvalidTimeString);
  }

  // Parse minute
  value = endptr + 1;  // skip ':'
  errno = 0;
  const long m = strtol(value, &endptr, 10);
  if (endptr == value || *endptr != '\0' || errno == ERANGE || m < 0 || m > 59) {
    return config_parse_result_t(config_parsing_error_t::InvalidTimeString);
  }

  hour = static_cast<int>(h);
  min = static_cast<int>(m);
  return {};
}
static config_parse_result_t is_valid_output_name(const char *name) {
  if (name == BONGOCAT_NULLPTR || name[0] == '\0') {
    return {};  // empty means "use default"
  }

  const size_t len = strnlen(name, VALUE_BUF);
  if (len >= VALUE_BUF) {
    return config_parse_result_t(config_parsing_error_t::InvalidMonitorName);
  }

  // Wayland output names are ASCII alphanumeric + hyphen + dot only.
  // Examples: DP-1, HDMI-A-1, eDP-1, DP-2-1, Virtual-1
  for (size_t i = 0; i < len; ++i) {
    const char c = name[i];
    if (!isalnum(static_cast<unsigned char>(c)) && c != '-' && c != '.') {
      return config_parse_result_t(config_parsing_error_t::InvalidMonitorName);
    }
  }
  return {};
}

static config_parse_result_t config_parse_string(config_t& config, const char *key, const char *value,
                                                 const load_config_overwrite_parameters_t& overwrite_parameters) {
  using namespace assets;
  if (strcmp(key, MONITOR_KEY) == 0 || strcmp(key, OUTPUT_NAME_KEY) == 0) {
    if (value != BONGOCAT_NULLPTR && value[0] != '\0') {
      if (auto valid_result = is_valid_output_name(value); valid_result.errors != config_parsing_error_t::Success) {
        BONGOCAT_LOG_WARNING("Invalid output name '%s', ignoring", value);
        return valid_result;
      }

      release_allocated_string(config.output_name);
      config.output_name = duplicate_string(value);
      if (!config.output_name) [[unlikely]] {
        BONGOCAT_LOG_ERROR("Failed to allocate memory for interface output");
        return config_parse_result_t(
            flag_add(config_parsing_error_t::InvalidMonitorName, config_parsing_error_t::StringMemoryError));
      }
    } else {
      release_allocated_string(config.output_name);
      config.output_name = BONGOCAT_NULLPTR;
    }
  } else if (strcmp(key, CUSTOM_SPRITE_SHEET_FILENAME_KEY) == 0) {
    release_allocated_string(config.custom_sprite_sheet_filename);
    if (value != BONGOCAT_NULLPTR && value[0] != '\0') {
      config.custom_sprite_sheet_filename = duplicate_string(value);
      if (!config.custom_sprite_sheet_filename) [[unlikely]] {
        BONGOCAT_LOG_ERROR("Failed to allocate memory for custom sprite sheet filename");
        return config_parse_result_t(flag_add(config_parsing_error_t::InvalidCustomSpriteSheetFilename,
                                              config_parsing_error_t::StringMemoryError));
      }
    } else {
      config.custom_sprite_sheet_filename = BONGOCAT_NULLPTR;
    }
  } else if (strcmp(key, SLEEP_BEGIN_KEY) == 0) {
    if (value != BONGOCAT_NULLPTR && value[0] != '\0') {
      int hour{0};
      int min{0};
      if (auto result_parse_time = config_parse_time(value, hour, min);
          result_parse_time.errors != config_parsing_error_t::Success) {
        return config_chain_parse_result(
            result_parse_time, config_add_parse_error(result_parse_time, config_parsing_error_t::InvalidSleepTime));
      }
      if (hour < 0 || hour > 23 || min < 0 || min > 59) {
        return config_parse_result_t(config_parsing_error_t::InvalidSleepTime);
      }

      config.sleep_begin.hour = hour;
      config.sleep_begin.min = min;
    } else {
      config.sleep_begin.hour = 0;
      config.sleep_begin.min = 0;
    }
  } else if (strcmp(key, SLEEP_END_KEY) == 0) {
    if (value != BONGOCAT_NULLPTR && value[0] != '\0') {
      int hour{0};
      int min{0};
      if (auto result_parse_time = config_parse_time(value, hour, min);
          result_parse_time.errors != config_parsing_error_t::Success) {
        return config_chain_parse_result(
            result_parse_time, config_add_parse_error(result_parse_time, config_parsing_error_t::InvalidSleepTime));
      }
      if (hour < 0 || hour > 23 || min < 0 || min > 59) {
        return config_parse_result_t(config_parsing_error_t::InvalidSleepTime);
      }

      config.sleep_end.hour = hour;
      config.sleep_end.min = min;
    } else {
      config.sleep_end.hour = 0;
      config.sleep_end.min = 0;
    }
  } else if (strcmp(key, ANIMATION_NAME_KEY) == 0) {
    using namespace assets;
    if (overwrite_parameters.animation_name != BONGOCAT_NULLPTR) {
      value = overwrite_parameters.animation_name;
    }

    config_parse_result_t ret;
    // set config._animation_name
    release_allocated_string(config._animation_name);
    config._animation_name = value != BONGOCAT_NULLPTR ? duplicate_string(value) : make_null_string();

    release_allocated_string(config._loaded_animation_fqname);

    // reset state
    config.animation_sprite_sheet_layout = config_animation_sprite_sheet_layout_t::None;
    config.animation_dm_set = config_animation_dm_set_t::None;
    config.animation_custom_set = config_animation_custom_set_t::None;
    config.animation_index = -1;

    // is fully name like dm:..., dm20:..., dmc:...
    [[maybe_unused]] const bool is_fqn = strchr(value, ':') != BONGOCAT_NULLPTR;
    bool animation_found = false;

    if constexpr (features::EnableBongocatEmbeddedAssets) {
      // check for bongocat
      if (strcmp(value, BONGOCAT_NAME) == 0 || strcmp(value, BONGOCAT_ID) == 0 || strcmp(value, BONGOCAT_FQID) == 0 ||
          strcmp(value, BONGOCAT_FQNAME) == 0) {
        config.animation_index = BONGOCAT_ANIM_INDEX;
        config.animation_sprite_sheet_layout = config_animation_sprite_sheet_layout_t::Bongocat;
        config._loaded_animation_fqname = duplicate_string(BONGOCAT_FQNAME);
      }

      animation_found = config.animation_index >= 0;
    }

    // check for dm
    if constexpr (features::EnableDmEmbeddedAssets) {
      using namespace assets;
#ifdef FEATURE_MIN_DM_EMBEDDED_ASSETS
      if ((!is_fqn && animation_found) || (is_fqn && !animation_found) ||
          (!is_fqn && !animation_found)) {  // overwrite animation when needed, priorities the fq names
        const int found_index = config_parse_animation_name_min_dm(config, value);
        if (found_index >= 0) {
          assert(found_index >= 0);
          /*
          if (config._loaded_animation_fqname != BONGOCAT_NULLPTR) {
            ::free(config._loaded_animation_fqname);
            config._loaded_animation_fqname = BONGOCAT_NULLPTR;
          }
          */
          config._loaded_animation_fqname =
              duplicate_string(get_config_animation_name_min_dm(static_cast<size_t>(found_index)).fqname);
          BONGOCAT_LOG_DEBUG("Animation found for %s", value);
        }
      }
      animation_found = config.animation_index >= 0;
#endif

      /// @TODO: use macros (or templates) to reduce copy&paste code

      /// @NOTE(assets): 3. add more dm versions here, config animation_name parsing
#ifdef FEATURE_DM_EMBEDDED_ASSETS
      if ((!is_fqn && animation_found) || (is_fqn && !animation_found) ||
          (!is_fqn && !animation_found)) {  // overwrite animation when needed, priorities the fq names
        const int found_index = config_parse_animation_name_dm(config, value);
        if (found_index >= 0) {
          assert(found_index >= 0);
          /*
          if (config._loaded_animation_fqname != BONGOCAT_NULLPTR) {
            ::free(config._loaded_animation_fqname);
            config._loaded_animation_fqname = BONGOCAT_NULLPTR;
          }
          */
          config._loaded_animation_fqname =
              duplicate_string(get_config_animation_name_dm(static_cast<size_t>(found_index)).fqname);
          BONGOCAT_LOG_DEBUG("Animation found for %s: %s", value, config._loaded_animation_fqname.c_str());
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
          /*
          if (config._loaded_animation_fqname != BONGOCAT_NULLPTR) {
            ::free(config._loaded_animation_fqname);
            config._loaded_animation_fqname = BONGOCAT_NULLPTR;
          }
          */
          config._loaded_animation_fqname =
              duplicate_string(get_config_animation_name_dm20(static_cast<size_t>(found_index)).fqname);
          BONGOCAT_LOG_DEBUG("Animation found for %s: %s", value, config._loaded_animation_fqname.c_str());
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
          /*
          if (config._loaded_animation_fqname != BONGOCAT_NULLPTR) {
            ::free(config._loaded_animation_fqname);
            config._loaded_animation_fqname = BONGOCAT_NULLPTR;
          }
          */
          config._loaded_animation_fqname =
              duplicate_string(get_config_animation_name_dmx(static_cast<size_t>(found_index)).fqname);
          BONGOCAT_LOG_DEBUG("Animation found for %s: %s", value, config._loaded_animation_fqname.c_str());
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
          /*
          if (config._loaded_animation_fqname != BONGOCAT_NULLPTR) {
            ::free(config._loaded_animation_fqname);
            config._loaded_animation_fqname = BONGOCAT_NULLPTR;
          }
          */
          config._loaded_animation_fqname =
              duplicate_string(get_config_animation_name_dmc(static_cast<size_t>(found_index)).fqname);
          BONGOCAT_LOG_DEBUG("Animation found for %s: %s", value, config._loaded_animation_fqname.c_str());
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
          /*
          if (config._loaded_animation_fqname != BONGOCAT_NULLPTR) {
            ::free(config._loaded_animation_fqname);
            config._loaded_animation_fqname = BONGOCAT_NULLPTR;
          }
          */
          config._loaded_animation_fqname =
              duplicate_string(get_config_animation_name_pen(static_cast<size_t>(found_index)).fqname);
          BONGOCAT_LOG_DEBUG("Animation found for %s: %s", value, config._loaded_animation_fqname.c_str());
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
          /*
          if (config._loaded_animation_fqname != BONGOCAT_NULLPTR) {
            ::free(config._loaded_animation_fqname);
            config._loaded_animation_fqname = BONGOCAT_NULLPTR;
          }
          */
          config._loaded_animation_fqname =
              duplicate_string(get_config_animation_name_pen20(static_cast<size_t>(found_index)).fqname);
          BONGOCAT_LOG_DEBUG("Animation found for %s: %s", value, config._loaded_animation_fqname.c_str());
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
          /*
          if (config._loaded_animation_fqname != BONGOCAT_NULLPTR) {
            ::free(config._loaded_animation_fqname);
            config._loaded_animation_fqname = BONGOCAT_NULLPTR;
          }
          */
          config._loaded_animation_fqname =
              duplicate_string(get_config_animation_name_dmall(static_cast<size_t>(found_index)).fqname);
          BONGOCAT_LOG_DEBUG("Animation found for %s: %s", value, config._loaded_animation_fqname.c_str());
        }
        animation_found = config.animation_index >= 0;
      }
#endif
    }

    // check for MS agent
    if constexpr (features::EnableMsAgentEmbeddedAssets) {
      // check for ms pets (clippy)
      if (strcmp(value, CLIPPY_NAME) == 0 || strcmp(value, CLIPPY_ID) == 0 || strcmp(value, CLIPPY_FQID) == 0 ||
          strcmp(value, CLIPPY_FQNAME) == 0) {
        config.animation_index = CLIPPY_ANIM_INDEX;
        config.animation_sprite_sheet_layout = config_animation_sprite_sheet_layout_t::MsAgent;
        /*
        if (config._loaded_animation_fqname != BONGOCAT_NULLPTR) {
          ::free(config._loaded_animation_fqname);
          config._loaded_animation_fqname = BONGOCAT_NULLPTR;
        }
        */
        config._loaded_animation_fqname = duplicate_string(CLIPPY_FQNAME);
      }
#ifdef FEATURE_MORE_MS_AGENT_EMBEDDED_ASSETS
      /// @NOTE(assets): 4. add more MS Agents here
      // Links
      if (strcmp(value, LINKS_NAME) == 0 || strcmp(value, LINKS_ID) == 0 || strcmp(value, LINKS_FQID) == 0 ||
          strcmp(value, LINKS_FQNAME) == 0) {
        config.animation_index = LINKS_ANIM_INDEX;
        config.animation_sprite_sheet_layout = config_animation_sprite_sheet_layout_t::MsAgent;
        /*
        if (config._loaded_animation_fqname != BONGOCAT_NULLPTR) {
          ::free(config._loaded_animation_fqname);
          config._loaded_animation_fqname = BONGOCAT_NULLPTR;
        }
        */
        config._loaded_animation_fqname = duplicate_string(LINKS_FQNAME);
      }
      // Rover
      if (strcmp(value, ROVER_NAME) == 0 || strcmp(value, ROVER_ID) == 0 || strcmp(value, ROVER_FQID) == 0 ||
          strcmp(value, ROVER_FQNAME) == 0) {
        config.animation_index = ROVER_ANIM_INDEX;
        config.animation_sprite_sheet_layout = config_animation_sprite_sheet_layout_t::MsAgent;
        /*
        if (config._loaded_animation_fqname != BONGOCAT_NULLPTR) {
          ::free(config._loaded_animation_fqname);
          config._loaded_animation_fqname = BONGOCAT_NULLPTR;
        }
        */
        config._loaded_animation_fqname = duplicate_string(ROVER_FQNAME);
      }
      // Merlin
      if (strcmp(value, MERLIN_NAME) == 0 || strcmp(value, MERLIN_ID) == 0 || strcmp(value, MERLIN_FQID) == 0 ||
          strcmp(value, MERLIN_FQNAME) == 0) {
        config.animation_index = MERLIN_ANIM_INDEX;
        config.animation_sprite_sheet_layout = config_animation_sprite_sheet_layout_t::MsAgent;
        /*
        if (config._loaded_animation_fqname != BONGOCAT_NULLPTR) {
          ::free(config._loaded_animation_fqname);
          config._loaded_animation_fqname = BONGOCAT_NULLPTR;
        }
        */
        config._loaded_animation_fqname = duplicate_string(MERLIN_FQNAME);
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
          /*
          if (config._loaded_animation_fqname != BONGOCAT_NULLPTR) {
            ::free(config._loaded_animation_fqname);
            config._loaded_animation_fqname = BONGOCAT_NULLPTR;
          }
          */
          config._loaded_animation_fqname =
              duplicate_string(get_config_animation_name_pkmn(static_cast<size_t>(found_index)).fqname);
          BONGOCAT_LOG_DEBUG("Animation found for %s: %s", value, config._loaded_animation_fqname.c_str());
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
          /*
          if (config._loaded_animation_fqname != BONGOCAT_NULLPTR) {
            ::free(config._loaded_animation_fqname);
            config._loaded_animation_fqname = BONGOCAT_NULLPTR;
          }
          */
          config._loaded_animation_fqname =
              duplicate_string(get_config_animation_name_pmd(static_cast<size_t>(found_index)).fqname);
          BONGOCAT_LOG_DEBUG("Animation found for %s: %s", value, config._loaded_animation_fqname.c_str());
        }
        animation_found = config.animation_index >= 0;
      }
#endif
    }

    // check for Misc (neko)
    if constexpr (features::EnableMiscEmbeddedAssets) {
      // check neko
      if (strcmp(value, MISC_NEKO_NAME) == 0 || strcmp(value, MISC_NEKO_ID) == 0 ||
          strcmp(value, MISC_NEKO_FQID) == 0 || strcmp(value, MISC_NEKO_FQNAME) == 0) {
        config.animation_index = MISC_NEKO_ANIM_INDEX;
        config.animation_sprite_sheet_layout = config_animation_sprite_sheet_layout_t::Custom;
        config.animation_custom_set = config_animation_custom_set_t::misc;
        /*
        if (config._loaded_animation_fqname != BONGOCAT_NULLPTR) {
          ::free(config._loaded_animation_fqname);
          config._loaded_animation_fqname = BONGOCAT_NULLPTR;
        }
        */
        config._loaded_animation_fqname = duplicate_string(MISC_NEKO_FQNAME);
        animation_found = config.animation_index >= 0;
      }
    }
    /// @NOTE(assets): 4. add more config animation_name parsring here

    // check for custom sprite sheet
    if constexpr (features::EnableCustomSpriteSheetsAssets) {
      // check custom
      if (strcmp(value, CUSTOM_NAME) == 0 || strcmp(value, CUSTOM_ID) == 0) {
        config.animation_index = CUSTOM_ANIM_INDEX;
        config.animation_sprite_sheet_layout = config_animation_sprite_sheet_layout_t::Custom;
        config.animation_custom_set = config_animation_custom_set_t::custom;
        /*
        if (config._loaded_animation_fqname != BONGOCAT_NULLPTR) {
          ::free(config._loaded_animation_fqname);
          config._loaded_animation_fqname = BONGOCAT_NULLPTR;
        }
        */
        config._loaded_animation_fqname = duplicate_string(config.custom_sprite_sheet_filename);
        animation_found = config.animation_index >= 0;
        config._custom = config.animation_index == CUSTOM_ANIM_INDEX;

        if (!config.custom_sprite_sheet_filename) {
          BONGOCAT_LOG_WARNING("custom_sprite_sheet_filename required for custom sprite sheet");
          animation_found = false;
          ret = config_add_parse_error(ret, config_parsing_error_t::FilenameRequiredForCustomSpriteSheet);
        }
      }
    }

    animation_found = config.animation_index >= 0 &&
                      config.animation_sprite_sheet_layout != config_animation_sprite_sheet_layout_t::None;
    if (!animation_found) {
      if (config.animation_index >= 0 &&
          config.animation_sprite_sheet_layout == config_animation_sprite_sheet_layout_t::None) {
        BONGOCAT_LOG_WARNING(
            "animation_index is set, but not animation_type (unknown type for index=%i and value='%s')",
            config.animation_index, value);
      }
      if (config._strict) {
        BONGOCAT_LOG_ERROR("animation_name: Invalid %s '%s'", ANIMATION_NAME_KEY, value);
        ret = config_add_parse_warning(ret, config_parsing_warning_t::InvalidAnimationName);
        return ret;
      }

      BONGOCAT_LOG_WARNING("animation_name: Invalid %s '%s', using '%s'", ANIMATION_NAME_KEY, value, BONGOCAT_NAME);
      config.animation_index = BONGOCAT_ANIM_INDEX;
      config.animation_sprite_sheet_layout = config_animation_sprite_sheet_layout_t::Bongocat;
      config.animation_dm_set = config_animation_dm_set_t::None;
      config.animation_custom_set = config_animation_custom_set_t::None;
      config._loaded_animation_fqname = duplicate_string(BONGOCAT_FQNAME);
      ret = config_add_parse_warning(ret, config_parsing_warning_t::InvalidAnimationName);
      return ret;
    }
  } else {
    return config_parse_result_t(config_parsing_info_t::UnknownConfigKey);
  }

  return {};
}

static config_parse_result_t config_parse_key_value(config_t& config, const char *key, const char *value,
                                                    const load_config_overwrite_parameters_t& overwrite_parameters) {
  // validate keys
  if (key == BONGOCAT_NULLPTR || key[0] == '\0') {
    return config_parse_result_t(config_parsing_info_t::InvalidConfigLine);
  }
  if (strnlen(key, KEY_BUF) >= KEY_BUF) {
    return config_parse_result_t(config_parsing_info_t::InvalidConfigLine);
  }
  // reject non-printable ASCII key
  for (const char *p = key; *p != '\0'; ++p) {
    if (!isprint(static_cast<unsigned char>(*p))) {
      BONGOCAT_LOG_WARNING("Non-printable character in config key, ignoring line");
      return config_parse_result_t(config_parsing_info_t::InvalidConfigLine);
    }
  }
  if (value == BONGOCAT_NULLPTR) {
    return config_parse_result_t(config_parsing_info_t::InvalidConfigLine);
  }
  if (strnlen(value, VALUE_BUF) >= VALUE_BUF) {
    return config_parse_result_t(config_parsing_info_t::ConfigLineTooLong);
  }

  const auto key_was_handled = [](const config_parse_result_t& res) {
    return !has_flag(res.infos, config_parsing_info_t::UnknownConfigKey);
  };
  const auto return_handled_result = [](config_parse_result_t res) -> config_parse_result_t {
    res.infos = flag_remove(res.infos, config_parsing_info_t::UnknownConfigKey);
    return res;
  };

  if (auto r = config_parse_enum_key(config, key, value); key_was_handled(r)) {
    return return_handled_result(r);
  }
  if (auto r = config_parse_string(config, key, value, overwrite_parameters); key_was_handled(r)) {
    return return_handled_result(r);
  }

  if (auto r = config_parse_boolean_key(config, key, value); key_was_handled(r)) {
    return return_handled_result(r);
  }
  if (auto r = config_parse_double_key(config, key, value); key_was_handled(r)) {
    return return_handled_result(r);
  }
  if (auto r = config_parse_integer_key(config, key, value); key_was_handled(r)) {
    return return_handled_result(r);
  }

  // Handle device keys
  if (strcmp(key, KEYBOARD_NAME_KEY) == 0) {
    if (value[0] == '\0') {
      return config_parse_result_t(config_parsing_info_t::InvalidConfigLine);
    }
    // Reject format string probes (%s%s%s) and injection attempts
    for (const char *p = value; *p != '\0'; ++p) {
      const unsigned char c = static_cast<unsigned char>(*p);
      if (!isprint(c)) {
        BONGOCAT_LOG_WARNING("Non-printable character in keyboard_name: %s", value);
        return config_parse_result_t(config_parsing_error_t::InvalidInputDeviceName);
      }
    }

    return config_add_keyboard_name(config, value);
  }
  // Handle device keys
  if (strcmp(key, KEYBOARD_DEVICE_KEY) == 0 || strcmp(key, KEYBOARD_DEVICES_KEY) == 0) {
    // Validate path starts with /dev/input/ and has no traversal
    if (strncmp(value, "/dev/input/", 11) != 0) {
      BONGOCAT_LOG_WARNING("keyboard_device path must start with /dev/input/: %s", value);
      return config_parse_result_t(config_parsing_error_t::InvalidInputDeviceName);
    }
    // No path traversal
    if (strstr(value, "..") != BONGOCAT_NULLPTR) {
      BONGOCAT_LOG_WARNING("Path traversal detected in device path: %s", value);
      return config_parse_result_t(config_parsing_error_t::InvalidInputDeviceName);
    }

    // No shell metacharacters or whitespace
    // Catches: $(curl ...), `cat`, event0;rm, event4\<newline>, spaces
    for (const char *p = value; *p != '\0'; ++p) {
      const unsigned char c = static_cast<unsigned char>(*p);
      if (!isprint(c) || c == ';' || c == '|' || c == '&' || c == '$' || c == '`' || c == '\'' || c == '"' ||
          c == '\\' || c == ' ' || c == '\t') {
        BONGOCAT_LOG_WARNING("Invalid character in keyboard_device path: %s", value);
        return config_parse_result_t(config_parsing_error_t::InvalidInputDeviceName);
      }
    }

    // Only allow /dev/input/event<digits> or /dev/input/by-id/... etc.
    // Anything after /dev/input/ must start with a valid char
    const char *subpath = value + 11;  // skip "/dev/input/"
    if (subpath[0] == '\0') {
      BONGOCAT_LOG_WARNING("keyboard_device path has no device name: %s", value);
      return config_parse_result_t(config_parsing_error_t::InvalidInputDeviceName);
    }

    return config_add_keyboard_device(config, value);
  }

  return config_parse_result_t(config_parsing_info_t::UnknownConfigKey);
}

static bool config_is_comment_or_empty(const char *line) {
  return ((line[0] == COMMENT_CHAR_1 || line[0] == COMMENT_CHAR_2) || line[0] == '\0' ||
          strspn(line, " \t") == strlen(line));
}

static config_parse_result_t config_parse_file(FILE *file, config_t& config,
                                               const load_config_overwrite_parameters_t& overwrite_parameters) {
  char line[LINE_BUF] = {0};

  [[maybe_unused]] int line_number = 0;
  config_parse_result_t ret{};

  while (fgets(line, LINE_BUF, file) != BONGOCAT_NULLPTR) {
    line_number++;

    const size_t line_len = strnlen(line, LINE_BUF);

    // validate newline
    if (line_len == LINE_BUF - 1 && line[line_len - 1] != '\n') {
      BONGOCAT_LOG_WARNING("Configuration line %d too long", line_number);
      ret = config_add_parse_info(ret, config_parsing_info_t::ConfigLineTooLong);
      // Flush remainder of the line
      int ch;
      while ((ch = fgetc(file)) != '\n' && ch != EOF) {}
      continue;
    }

    // Remove trailing newline
    if (line_len > 0 && line[line_len - 1] == '\n') {
      line[line_len - 1] = '\0';
    }

    // Skip comments and empty lines
    if (config_is_comment_or_empty(line)) {
      continue;
    }

    char *eq = strchr(line, '=');
    if (eq == BONGOCAT_NULLPTR) {
      BONGOCAT_LOG_WARNING("Invalid configuration line %d: %s", line_number, line);
      ret = config_add_parse_info(ret, config_parsing_info_t::InvalidConfigLine);
      continue;
    }
    *eq = '\0';
    char *key = line;
    char *value = eq + 1;
    // Ensure '=' is inside bounds
    ptrdiff_t eq_offset = eq - line;
    if (eq_offset < 0 || static_cast<size_t>(eq_offset) >= sizeof(line)) {
      BONGOCAT_LOG_WARNING("Invalid configuration line %d: malformed separator", line_number);
      ret = config_add_parse_info(ret, config_parsing_info_t::InvalidConfigLine);
      continue;
    }

    // Remove trailing comments
    {
      char *comment_1 = strchr(value, COMMENT_CHAR_1);
      if (comment_1 != BONGOCAT_NULLPTR) {
        *comment_1 = '\0';
      }
    }
    {
      char *comment_2 = strchr(value, COMMENT_CHAR_2);
      if (comment_2 != BONGOCAT_NULLPTR) {
        *comment_2 = '\0';
      }
    }

    const char *trimmed_key = config_trim_str(key);
    const char *trimmed_value = config_trim_str(value);
    if (trimmed_key == BONGOCAT_NULLPTR || trimmed_value == BONGOCAT_NULLPTR) {
      BONGOCAT_LOG_WARNING("Invalid configuration line %d: trim failure", line_number);
      ret = config_add_parse_info(ret, config_parsing_info_t::InvalidConfigLine);
      continue;
    }

    const size_t key_len = strnlen(trimmed_key, KEY_BUF);
    const size_t value_len = strnlen(trimmed_value, VALUE_BUF);
    if (key_len == 0) {
      BONGOCAT_LOG_WARNING("Invalid configuration line %d: empty key", line_number);
      ret = config_add_parse_info(ret, config_parsing_info_t::InvalidConfigLine);
      continue;
    }
    if (key_len >= KEY_BUF) {
      BONGOCAT_LOG_WARNING("Configuration key too long at line %d", line_number);
      ret = config_add_parse_info(ret, config_parsing_info_t::InvalidConfigLine);
      continue;
    }
    if (value_len >= VALUE_BUF) {
      BONGOCAT_LOG_WARNING("Configuration value too long at line %d", line_number);
      ret = config_add_parse_info(ret, config_parsing_info_t::ConfigLineTooLong);
      continue;
    }

    const auto parse_result = config_parse_key_value(config, trimmed_key, trimmed_value, overwrite_parameters);
    if (config_was_key_unknown(parse_result)) {
      BONGOCAT_LOG_WARNING("Unknown configuration key '%s' at line %d", trimmed_key, line_number);
    }
    ret = config_chain_parse_result(ret, parse_result);
  }

  return ret;
}

static config_parse_result_t config_parse_file(config_t& config, const char *config_file_path,
                                               load_config_overwrite_parameters_t overwrite_parameters) {
  const char *file_path = config_file_path != BONGOCAT_NULLPTR ? config_file_path : DEFAULT_CONFIG_FILE_PATH;

  FILE *file = fopen(file_path, "r");
  if (file == BONGOCAT_NULLPTR) {
    if (overwrite_parameters.strict >= 1) {
      BONGOCAT_LOG_INFO("Config file '%s' not found", file_path);
      return config_parse_result_t(config_parsing_fatal_t::ConfigNotFound);
    }
    BONGOCAT_LOG_INFO("Config file '%s' not found, using defaults", file_path);
    set_defaults(config);
    return config_parse_result_t(config_parsing_info_t::ConfigNotFoundUseDefault);
  }

  const auto result = config_parse_file(file, config, overwrite_parameters);
  fclose(file);
  file = BONGOCAT_NULLPTR;

  BONGOCAT_LOG_INFO("Loaded configuration from %s", file_path);

  return result;
}

static config_parse_result_t config_parse_stdin(config_t& config,
                                                const load_config_overwrite_parameters_t& overwrite_parameters) {
  FILE *file = stdin;

  const auto result = config_parse_file(file, config, overwrite_parameters);
  if (result.errors == config_parsing_error_t::Success) {
    BONGOCAT_LOG_INFO("Loaded configuration from stdin");
  }

  return result;
}

// =============================================================================
// DEFAULT CONFIGURATION MODULE
// =============================================================================

void set_defaults(config_t& config) {
  config_t cfg{};

  cfg.output_name = BONGOCAT_NULLPTR;
  static_assert(input::MAX_INPUT_DEVICES <= INT_MAX);
  for (int i = 0; i < static_cast<int>(input::MAX_INPUT_DEVICES); i++) {
    cfg.keyboard_devices[i] = BONGOCAT_NULLPTR;
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
  cfg.mirror_x = false;
  cfg.mirror_y = false;
  cfg.enable_antialiasing = DEFAULT_ENABLE_ANTIALIASING;
  cfg.enable_debug = DEFAULT_ENABLE_DEBUG;
  cfg.enable_hand_mapping = DEFAULT_ENABLE_HAND_MAPPING;
  cfg.layer = DEFAULT_LAYER;
  cfg.overlay_position = DEFAULT_OVERLAY_POSITION;
  cfg.animation_index = DEFAULT_ANIMATION_INDEX;
  cfg.invert_color = false;
  cfg.padding_x = 0;
  cfg.padding_y = 0;
  cfg.enable_scheduled_sleep = false;
  cfg.sleep_begin = {};
  cfg.sleep_end = {};
  cfg.idle_sleep_timeout_sec = DEFAULT_IDLE_SLEEP_TIMEOUT_SEC;
  cfg.happy_kpm = DEFAULT_HAPPY_KPM;
  cfg.cat_align = DEFAULT_CAT_ALIGN;
  cfg.animation_sprite_sheet_layout = config_animation_sprite_sheet_layout_t::Bongocat;
  cfg.animation_dm_set = config_animation_dm_set_t::None;
  cfg.animation_custom_set = config_animation_custom_set_t::None;
  cfg.idle_animation = false;
  cfg.input_fps = 0;  // when 0 fallback to fps
  cfg.randomize_index = false;
  cfg.randomize_on_reload = false;
  cfg.movement_wait_factor = DEFAULT_MOVEMENT_WAIT_FACTOR;
  cfg.screen_width = 0;
  cfg.custom_sprite_sheet_filename = BONGOCAT_NULLPTR;
  cfg.custom_sprite_sheet_settings = {};
  cfg.hotplug_scan_interval_ms = DEFAULT_HOTPLUG_SCAN_INTERVAL_MS;
  cfg.evolution_speed_factor = 1.0;

  for (int i = 0; i < static_cast<int>(input::MAX_INPUT_DEVICES); i++) {
    cfg._keyboard_names[i] = BONGOCAT_NULLPTR;
  }
  cfg._num_keyboard_names = 0;

  cfg._keep_old_animation_index = false;
  cfg._strict = false;
  cfg._custom = false;
  cfg._animation_name = BONGOCAT_NULLPTR;
  cfg._loaded_animation_fqname = BONGOCAT_NULLPTR;

  config = bongocat::move(cfg);
}

static void config_log_result(const config_t& config, const config_parse_result_t& errors);
static void config_log_summary(const config_t& config, [[maybe_unused]] const config_parse_result_t& errors) {
  using namespace assets;
  BONGOCAT_LOG_DEBUG("Configuration loaded successfully");
  BONGOCAT_LOG_DEBUG("  Overlay Height: %dpx", config.overlay_height);
  switch (config.animation_sprite_sheet_layout) {
  case config_animation_sprite_sheet_layout_t::None:
    break;
  case config_animation_sprite_sheet_layout_t::Bongocat:
    // when loaded by default, _loaded_animation_fqname is not set
    // assert(config._loaded_animation_fqname);
    BONGOCAT_LOG_DEBUG("  Cat: '%s' %dx%d at offset (%d,%d)",
                       config._loaded_animation_fqname ? config._loaded_animation_fqname.c_str() : BONGOCAT_FQNAME,
                       (config.cat_height * BONGOCAT_FRAME_WIDTH) / BONGOCAT_FRAME_HEIGHT, config.cat_height,
                       config.cat_x_offset, config.cat_y_offset);
    break;
  case config_animation_sprite_sheet_layout_t::Dm:
    assert(config._loaded_animation_fqname);
    BONGOCAT_LOG_DEBUG("  dm: '%s' %03d/%03d (set=%d) at offset (%d,%d)", config._loaded_animation_fqname.c_str(),
                       config.animation_index, DM_ANIMATIONS_COUNT, config.animation_dm_set, config.cat_x_offset,
                       config.cat_y_offset);
    break;
  case config_animation_sprite_sheet_layout_t::Pkmn:
    assert(config._loaded_animation_fqname);
    static_assert(PKMN_ANIMATIONS_COUNT <= INT32_MAX);
    BONGOCAT_LOG_DEBUG("  pkmn: '%s' %03d/%03d at offset (%d,%d)", config._loaded_animation_fqname.c_str(),
                       config.animation_index, PKMN_ANIMATIONS_COUNT, config.cat_x_offset, config.cat_y_offset);
    break;
  case config_animation_sprite_sheet_layout_t::MsAgent:
    assert(config._loaded_animation_fqname);
    static_assert(MS_AGENTS_ANIMATIONS_COUNT <= INT32_MAX);
    BONGOCAT_LOG_DEBUG("  MS Agent: '%s' %02d/%02d at offset (%d,%d)", config._loaded_animation_fqname.c_str(),
                       config.animation_index, MS_AGENTS_ANIMATIONS_COUNT, config.cat_x_offset, config.cat_y_offset);
    break;
  case config_animation_sprite_sheet_layout_t::Custom:
    switch (config.animation_custom_set) {
    case config_animation_custom_set_t::None:
      break;
    case config_animation_custom_set_t::misc:
      assert(config._loaded_animation_fqname);
      static_assert(MISC_ANIM_COUNT <= INT32_MAX);
      BONGOCAT_LOG_DEBUG("  Misc: '%s' %03d/%03d at offset (%d,%d)", config._loaded_animation_fqname.c_str(),
                         config.animation_index, MISC_ANIMATIONS_COUNT, config.cat_x_offset, config.cat_y_offset);
      break;
    case config_animation_custom_set_t::pmd:
      assert(config._loaded_animation_fqname);
      static_assert(PMD_ANIM_COUNT <= INT32_MAX);
      BONGOCAT_LOG_DEBUG("  pkmn pmd: '%s' %04d/%04d at offset (%d,%d)", config._loaded_animation_fqname.c_str(),
                         config.animation_index, PMD_ANIMATIONS_COUNT, config.cat_x_offset, config.cat_y_offset);
      break;
    case config_animation_custom_set_t::custom:
      assert(config.custom_sprite_sheet_filename);
      assert(config._custom);
      BONGOCAT_LOG_DEBUG("  Custom: %s at offset (%d,%d)", config.custom_sprite_sheet_filename.c_str(),
                         config.cat_x_offset, config.cat_y_offset);
      break;
    }
    break;
  }
  BONGOCAT_LOG_DEBUG("  FPS: %d, Opacity: %d, Random: %d", config.fps, config.overlay_opacity, config.randomize_index);
  BONGOCAT_LOG_DEBUG("  Mirror: X=%d, Y=%d", config.mirror_x, config.mirror_y);
  BONGOCAT_LOG_DEBUG("  Anti-aliasing: %s", config.enable_antialiasing ? "enabled" : "disabled");
  BONGOCAT_LOG_DEBUG("  Position: %s", to_string(config.overlay_position));
  BONGOCAT_LOG_DEBUG("  Alignment: %d", config.cat_align, to_string(config.cat_align));
  BONGOCAT_LOG_DEBUG("  Layer: %s", to_string(config.layer));
  BONGOCAT_LOG_DEBUG("  Output Screen: %s", config.output_name.c_str());

  config_log_result(config, errors);
}
static void config_log_result([[maybe_unused]] const config_t& config,
                              [[maybe_unused]] const config_parse_result_t& errors) {
  if (errors.fatal != config_parsing_fatal_t::Success) {
    BONGOCAT_LOG_ERROR("  Fatal Code:    0x%016llx", static_cast<uint64_t>(errors.fatal));
  }
  if (errors.errors != config_parsing_error_t::Success) {
    BONGOCAT_LOG_ERROR("  Errors Code:   0x%016llx", static_cast<uint64_t>(errors.errors));
  }
  if (config._strict && errors.warnings != config_parsing_warning_t::Success) {
    BONGOCAT_LOG_ERROR("  Warnings Code: 0x%016llx", static_cast<uint64_t>(errors.warnings));
  } else if (!config._strict && errors.warnings != config_parsing_warning_t::Success) {
    BONGOCAT_LOG_WARNING("  Warnings Code: 0x%016llx", static_cast<uint64_t>(errors.warnings));
  }
  if (errors.infos != config_parsing_info_t::Success) {
    BONGOCAT_LOG_INFO("  Infos Code:    0x%016llx", static_cast<uint64_t>(errors.infos));
  }
}

static loaded_config_result_t config_after_parsing(config_t& ret, config_parse_result_t& errors,
                                                   const load_config_overwrite_parameters_t& overwrite_parameters) {
  if (overwrite_parameters.output_name != BONGOCAT_NULLPTR) {
    ret.output_name = duplicate_string(overwrite_parameters.output_name);
    if (ret.output_name) {
      if (auto valid_result = is_valid_output_name(ret.output_name.c_str());
          valid_result.errors != config_parsing_error_t::Success) {
        BONGOCAT_LOG_WARNING("Invalid output name '%s', ignoring", ret.output_name.c_str());
        errors = config_chain_parse_result(errors, valid_result);
      }

    } else {
      BONGOCAT_LOG_ERROR("Failed to allocate memory for interface output");
      errors =
          config_chain_parse_result(errors, config_parse_result_t(flag_add(config_parsing_error_t::InvalidMonitorName,
                                                                           config_parsing_error_t::StringMemoryError)));
    }
  }
  if (overwrite_parameters.randomize_index >= 0) {
    ret.randomize_index = overwrite_parameters.randomize_index >= 1 ? 1 : 0;
  }

  if (ret.input_fps <= 0) {
    ret.input_fps = ret.fps;
  }

  // Resolve keyboard_name entries to device paths.
  // Continue on scan failure so static keyboard_device entries still work.
  {
    auto devices_result = config_resolve_devices(ret);
    if (devices_result.errors != config_parsing_error_t::Success) [[unlikely]] {
      BONGOCAT_LOG_WARNING("Failed to resolve keyboard names, continuing");
    }
    errors = config_chain_parse_result(errors, devices_result);
  }

  // Validate and sanitize configuration
  errors = config_chain_parse_result(errors, config_validate(ret));

  if (ret.num_keyboard_devices == 0) {
    BONGOCAT_LOG_INFO("No device loaded");
    errors = config_add_parse_info(errors, config_parsing_info_t::NoInputDevices);
  }

  // Log configuration summary
  config_log_summary(ret, errors);

  return loaded_config_result_t(bongocat::move(ret), bongocat::move(errors));
}

// =============================================================================
// PUBLIC API IMPLEMENTATION
// =============================================================================

loaded_config_result_t load(const char *config_file_path, load_config_overwrite_parameters_t overwrite_parameters) {
  BONGOCAT_CHECK_NULL(config_file_path, loaded_config_result_t(config_parsing_fatal_t::ConfigFilenameEmpty));

  config_t ret;
  set_defaults(ret);
  config_parse_result_t errors;

  [[maybe_unused]] const auto t0 = platform::get_current_time_us();

  if (overwrite_parameters.strict >= 0) {
    ret._strict = overwrite_parameters.strict >= 1;
  }

  // Parse config file and override defaults
  {
    const auto load_result = [&]() {
      if (strcmp(config_file_path, "-") == 0) {
        return config_parse_stdin(ret, overwrite_parameters);
      }
      return config_parse_file(ret, config_file_path, overwrite_parameters);
    }();
    errors = config_chain_parse_result(errors, load_result);
    if (ret._strict && errors.fatal != config_parsing_fatal_t::Success) {
      return loaded_config_result_t(bongocat::move(errors));
    }
  }

  [[maybe_unused]] const auto t1 = platform::get_current_time_us();
  BONGOCAT_LOG_INFO("Config loaded in %.3fms (%.6fsec)", static_cast<double>(t1 - t0) / 1000.0,
                    static_cast<double>(t1 - t0) / 1000000.0);

  return config_after_parsing(ret, errors, overwrite_parameters);
}

void reset(config_t& config) {
  config_cleanup_devices(config);
  set_defaults(config);
}

AllocatedString resolve_path(const char *explicit_path) {
  if (explicit_path != BONGOCAT_NULLPTR) {
    return duplicate_string(explicit_path);
  }

  char path[PATH_MAX];

  // 1. $XDG_CONFIG_HOME/bongocat/bongocat.conf
  const char *xdg_config = getenv("XDG_CONFIG_HOME");
  if (xdg_config != BONGOCAT_NULLPTR && xdg_config[0] != '\0') {
    snprintf(path, sizeof(path), "%s/bongocat/bongocat.conf", xdg_config);
    if (access(path, R_OK) == 0) {
      return duplicate_string(path);
    }
  }

  // 2. ~/.config/bongocat/bongocat.conf
  const char *home = getenv("HOME");
  if (home != BONGOCAT_NULLPTR && home[0] != '\0') {
    snprintf(path, sizeof(path), "%s/.config/bongocat/bongocat.conf", home);
    if (access(path, R_OK) == 0) {
      return duplicate_string(path);
    }
  }

  // 3. ./bongocat.conf (CWD)
  if (access("bongocat.conf", R_OK) == 0) {
    return duplicate_string("bongocat.conf");
  }

  // No config found - will use defaults
  return make_null_string();
}

#ifdef TEST_BUILD
static config_parse_result_t config_parse_string(config_t& config, const char *content,
                                                 load_config_overwrite_parameters_t overwrite_parameters) {
  BONGOCAT_CHECK_NULL(content, config_parse_result_t(config_parsing_fatal_t::ConfigFilenameEmpty));

  FILE *file = fmemopen(const_cast<char *>(content), strlen(content), "r");
  if (file == BONGOCAT_NULLPTR) {
    return config_parse_result_t(config_parsing_fatal_t::ConfigNotFound);
  }

  const auto result = config_parse_file(file, config, overwrite_parameters);

  fclose(file);
  return result;
}

loaded_config_result_t load_from_string(const char *content, load_config_overwrite_parameters_t overwrite_parameters) {
  BONGOCAT_CHECK_NULL(content, loaded_config_result_t(config_parsing_fatal_t::ConfigFilenameEmpty));

  config_t ret;
  set_defaults(ret);
  config_parse_result_t errors;

  if (overwrite_parameters.strict >= 0) {
    ret._strict = overwrite_parameters.strict >= 1;
  }

  errors = config_chain_parse_result(errors, config_parse_string(ret, content, overwrite_parameters));
  if (ret._strict && errors.fatal != config_parsing_fatal_t::Success) {
    return loaded_config_result_t(bongocat::move(errors));
  }

  return config_after_parsing(ret, errors, overwrite_parameters);
}
#endif

}  // namespace bongocat::config