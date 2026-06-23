#ifndef BONGOCAT_CONFIG_H
#define BONGOCAT_CONFIG_H

#include "core/bongocat.h"
#include "embedded_assets/assets.h"
#include "embedded_assets/custom/custom_sprite.h"
#include "utils/error.h"

#include <cassert>
#include <cstdint>
#include <cstdlib>
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
inline static constexpr const char *POSITION_TOP_STR = "top";
inline static constexpr const char *POSITION_BOTTOM_STR = "bottom";
BONGOCAT_NODISCARD constexpr const char *to_string(overlay_position_t position) noexcept {
  switch (position) {
  case overlay_position_t::POSITION_TOP:
    return POSITION_TOP_STR;
  case overlay_position_t::POSITION_BOTTOM:
    return POSITION_BOTTOM_STR;
  default:
    return "unknown";
  }
}

enum class layer_type_t : int8_t {
  LAYER_BACKGROUND = 0,
  LAYER_BOTTOM = 1,
  LAYER_TOP = 2,
  LAYER_OVERLAY = 3,
};
inline static constexpr const char *LAYER_BACKGROUND_STR = "background";
inline static constexpr const char *LAYER_BOTTOM_STR = "bottom";
inline static constexpr const char *LAYER_TOP_STR = "top";
inline static constexpr const char *LAYER_OVERLAY_STR = "overlay";
BONGOCAT_NODISCARD constexpr const char *to_string(layer_type_t layer) noexcept {
  switch (layer) {
  case layer_type_t::LAYER_BACKGROUND:
    return LAYER_BACKGROUND_STR;
  case layer_type_t::LAYER_BOTTOM:
    return LAYER_BOTTOM_STR;
  case layer_type_t::LAYER_TOP:
    return LAYER_TOP_STR;
  case layer_type_t::LAYER_OVERLAY:
    return LAYER_OVERLAY_STR;
  default:
    return "unknown";
  }
}

enum class align_type_t : int8_t {
  ALIGN_CENTER = 0,
  ALIGN_LEFT = -1,
  ALIGN_RIGHT = 1,
};
inline static constexpr const char *ALIGN_CENTER_STR = "center";
inline static constexpr const char *ALIGN_LEFT_STR = "left";
inline static constexpr const char *ALIGN_RIGHT_STR = "right";
BONGOCAT_NODISCARD constexpr const char *to_string(align_type_t align) noexcept {
  switch (align) {
  case align_type_t::ALIGN_CENTER:
    return ALIGN_CENTER_STR;
  case align_type_t::ALIGN_LEFT:
    return ALIGN_LEFT_STR;
  case align_type_t::ALIGN_RIGHT:
    return ALIGN_RIGHT_STR;
  default:
    return "unknown";
  }
}

enum class evolution_time_mode_t : uint8_t {
  NONE,
  NORMAL,
  PROGRAM_START,
  UPTIME,
};
inline static constexpr const char *EVOLUTION_TIME_MODE_NONE_STR = "none";
inline static constexpr const char *EVOLUTION_TIME_MODE_NORMAL_STR = "normal";
inline static constexpr const char *EVOLUTION_TIME_MODE_PROGRAM_START_STR = "program";
inline static constexpr const char *EVOLUTION_TIME_MODE_UPTIME_STR = "uptime";
BONGOCAT_NODISCARD constexpr const char *to_string(evolution_time_mode_t position) noexcept {
  switch (position) {
  case evolution_time_mode_t::NONE:
    return EVOLUTION_TIME_MODE_NONE_STR;
  case evolution_time_mode_t::NORMAL:
    return EVOLUTION_TIME_MODE_NORMAL_STR;
  case evolution_time_mode_t::PROGRAM_START:
    return EVOLUTION_TIME_MODE_PROGRAM_START_STR;
  case evolution_time_mode_t::UPTIME:
    return EVOLUTION_TIME_MODE_UPTIME_STR;
  default:
    return "unknown";
  }
}

// =============================================================================
// CONFIGURATION FUNCTIONS
// =============================================================================

struct config_t;
void config_free_keyboard_devices(config_t& config);
[[deprecated("use copy-ctor")]] void config_copy_keyboard_devices_from(config_t& config, const config_t& other);
void config_free_keyboard_names(config_t& config);
[[deprecated("use copy-ctor")]] void config_copy_keyboard_names_from(config_t& config, const config_t& other);
void cleanup(config_t& config);

// =============================================================================
// CONFIGURATION TYPES
// =============================================================================

struct config_time_t {
  int hour{0};
  int min{0};
};
enum class config_animation_sprite_sheet_layout_t : uint8_t {
  None,
  Bongocat,
  Dm,
  MsAgent,
  Pkmn,
  Custom,
};
enum class config_animation_dm_set_t : uint8_t {
  None,
  min_dm,
  dm,
  dm20,
  dmx,
  pen,
  pen20,
  dmc,
  dmall,
};
enum class config_animation_custom_set_t : uint8_t {
  None,
  misc,
  pmd,
  custom,
};

struct config_t {
  AllocatedString output_name{BONGOCAT_NULLPTR};
  AllocatedString keyboard_devices[input::MAX_INPUT_DEVICES];
  int32_t num_keyboard_devices{0};
  int32_t cat_x_offset{0};
  int32_t cat_y_offset{0};
  int32_t cat_height{0};
  int32_t overlay_height{0};
  int32_t idle_frame{0};
  int32_t keypress_duration_ms{0};
  int32_t test_animation_duration_ms{0};
  int32_t test_animation_interval_sec{0};
  int32_t animation_speed_ms{0};
  int32_t fps{0};
  int32_t overlay_opacity{0};
  bool mirror_x{false};             // reflect across Y axis (horizontal flip)
  bool mirror_y{false};             // reflect across X axis (vertical flip)
  bool enable_antialiasing{false};  // enable bilinear interpolation for smooth scaling
  bool enable_debug{false};
  layer_type_t layer{layer_type_t::LAYER_TOP};
  overlay_position_t overlay_position{overlay_position_t::POSITION_TOP};

  int32_t animation_index{0};
  bool invert_color{false};
  int32_t padding_x{0};
  int32_t padding_y{0};

  bool enable_scheduled_sleep{false};
  config_time_t sleep_begin;
  config_time_t sleep_end;
  int32_t idle_sleep_timeout_sec{0};

  int32_t happy_kpm{0};

  align_type_t cat_align{align_type_t::ALIGN_CENTER};

  config_animation_sprite_sheet_layout_t animation_sprite_sheet_layout{config_animation_sprite_sheet_layout_t::None};
  config_animation_dm_set_t animation_dm_set{config_animation_dm_set_t::None};
  config_animation_custom_set_t animation_custom_set{config_animation_custom_set_t::None};
  bool idle_animation{false};
  int32_t input_fps{0};
  bool randomize_index{false};
  bool randomize_on_reload{false};

  int32_t update_rate_ms{0};
  double cpu_threshold{0};
  double cpu_running_factor{0};

  int32_t movement_radius{0};
  int32_t enable_movement_debug{0};
  int32_t movement_speed{0};
  double movement_wait_factor{0};

  int32_t screen_width{0};

  AllocatedString custom_sprite_sheet_filename{BONGOCAT_NULLPTR};  // must be png file
  assets::custom_animation_settings_t custom_sprite_sheet_settings{};

  bool enable_hand_mapping{false};

  int32_t hotplug_scan_interval_ms{0};

  // Fullscreen behavior
  bool disable_fullscreen_hide{false};

  evolution_time_mode_t evolution{evolution_time_mode_t::NONE};
  double evolution_speed_factor{1.0};

  // Device matching by name (for hotplug/auto-detection)
  AllocatedString _keyboard_names[input::MAX_INPUT_DEVICES];
  int32_t _num_keyboard_names{0};

  // for keep old index when reload config
  bool _keep_old_animation_index{false};
  bool _strict{false};
  bool _custom{false};                                // is custom sprite sheet
  AllocatedString _animation_name{BONGOCAT_NULLPTR};  // original animation_anim from parsing config
  AllocatedString _loaded_animation_fqname{BONGOCAT_NULLPTR};

  // Make Config movable and copyable
  config_t() {
    for (size_t i = 0; i < input::MAX_INPUT_DEVICES; ++i) {
      keyboard_devices[i] = BONGOCAT_NULLPTR;
    }
    /*
  AllocatedString _keyboard_names[input::MAX_INPUT_DEVICES];
  int32_t _num_keyboard_names{0};
    for (size_t i = 0; i < input::MAX_INPUT_DEVICES; ++i) {
      _keyboard_names[i] = BONGOCAT_NULLPTR;
    }
    */
  }
  ~config_t() {
    cleanup(*this);
  }

  config_t(const config_t& other) = default;
  config_t& operator=(const config_t& other) = default;
  config_t(config_t&& other) noexcept = default;
  config_t& operator=(config_t&& other) noexcept = default;
};
inline void cleanup(config_t& config) {
  release_allocated_string(config.output_name);
  config.output_name = BONGOCAT_NULLPTR;
  config_free_keyboard_devices(config);
  config_free_keyboard_names(config);
  release_allocated_string(config.custom_sprite_sheet_filename);
  release_allocated_string(config._animation_name);
  release_allocated_string(config._loaded_animation_fqname);
  config.custom_sprite_sheet_filename = BONGOCAT_NULLPTR;
  config._animation_name = BONGOCAT_NULLPTR;
  config._loaded_animation_fqname = BONGOCAT_NULLPTR;
}

inline void config_free_keyboard_devices(config_t& config) {
  assert(config.num_keyboard_devices >= 0);
  for (size_t i = 0; i < static_cast<size_t>(config.num_keyboard_devices) && i < input::MAX_INPUT_DEVICES; i++) {
    release_allocated_string(config.keyboard_devices[i]);
    config.keyboard_devices[i] = BONGOCAT_NULLPTR;
  }
  config.num_keyboard_devices = 0;
}
inline void config_free_keyboard_names(config_t& config) {
  assert(config._num_keyboard_names >= 0);
  for (size_t i = 0; i < static_cast<size_t>(config._num_keyboard_names) && i < input::MAX_INPUT_DEVICES; i++) {
    release_allocated_string(config._keyboard_names[i]);
    config._keyboard_names[i] = BONGOCAT_NULLPTR;
  }
  config._num_keyboard_names = 0;
}
inline void config_copy_keyboard_devices_from(config_t& config, const config_t& other) {
  config_free_keyboard_devices(config);
  config.num_keyboard_devices = other.num_keyboard_devices;
  assert(config.num_keyboard_devices >= 0);
  for (size_t i = 0; i < static_cast<size_t>(config.num_keyboard_devices) && i < input::MAX_INPUT_DEVICES; i++) {
    config.keyboard_devices[i] = duplicate_string(other.keyboard_devices[i]);
  }
}
inline void config_copy_keyboard_names_from(config_t& config, const config_t& other) {
  config_free_keyboard_names(config);
  config._num_keyboard_names = other._num_keyboard_names;
  assert(config._num_keyboard_names >= 0);
  for (size_t i = 0; i < static_cast<size_t>(config._num_keyboard_names) && i < input::MAX_INPUT_DEVICES; i++) {
    config._keyboard_names[i] = duplicate_string(other._keyboard_names[i]);
  }
}

// =============================================================================
// CONFIGURATION FUNCTIONS
// =============================================================================

enum class config_parsing_error_t : uint64_t {
  Success = 0,
  //Warnings = (1uz << 0),
  OutOfRangeInt = (1uz << 1),
  OutOfRangeDouble = (1uz << 2),
  InvalidBoolean = (1uz << 3),
  InvalidInteger = (1uz << 4),
  InvalidTimeString = (1uz << 5),
  StringMemoryError = (1uz << 6),

  InvalidTestAnimationIntervalSec = (1uz << 7),
  InvalidAnimationSpeedMs = (1uz << 8),
  InvalidAnimationNameStrict  = (1uz << 9),
  //WarningInvalidAnimationName = (1uz << 10),
  InvalidMonitorName = (1uz << 11),
  InvalidInputDeviceName = (1uz << 12),
  MaxDeviceNamesReachedStrict = (1uz << 13),
  //WarningMaxDeviceNamesReached = (1uz << 14),

  InvalidCustomSpriteSheetSettings = (1uz << 15),
  InvalidCustomSpriteSheetCols = (1uz << 16),
  InvalidCustomSpriteSheetRows = (1uz << 17),
  CustomSpriteSheetFileNotFound = (1uz << 18),
  CanNotOpenCustomSpriteSheet = (1uz << 19),
  CustomSpriteSheetFileEmpty = (1uz << 20),
  CustomSpriteSheetInvalidPNGHeader = (1uz << 21),
  CustomSpriteSheetInvalidPNGSignature = (1uz << 22),
  InvalidCustomSpriteSheetFilename = (1uz << 23),
  CustomSpriteSheetFilenameEmpty = (1uz << 24),
  CustomSpriteSheetRequiredIdleAnimation = (1uz << 25),

  // Warnings: Optional Animations
  //CustomSpriteSheetRequiredSleepAnimation = (1uz << 26),
  //CustomSpriteSheetRequiredMovingAnimation = (1uz << 27),
  //CustomSpriteSheetRequiredWritingAnimation = (1uz << 28),
  //CustomSpriteSheetRequiredHappyAnimation = (1uz << 29),

  InvalidAnimationSpriteSheetLayout = (1uz << 30),
  OutOfRangeAnimationIndex = (1uz << 31),
  OutOfRangeIdleFrameAnimationIndex = (1uz << 32),
  FilenameRequiredForCustomSpriteSheet = (1uz << 33),

  InvalidLayer  = (1uz << 34),
  InvalidOverlayPosition  = (1uz << 35),
  InvalidCatAlign  = (1uz << 36),
  InvalidEvolution  = (1uz << 37),
  InvalidEvolutionSpeed  = (1uz << 38),
  InvalidSleepTime  = (1uz << 39),

  //WarningConfigLineTooLong = (1uz << 40),
  //WarningInvalidConfigLine = (1uz << 41),
  //WarningUnknownConfigKey = (1uz << 42),
  //WarningNoInputDevices = (1uz << 43),

  // "hard" errors, no need to continue, more for error signal
  ConfigFilenameEmpty  = (1uz << 44),
  ConfigNotFound = (1uz << 45),
  CanNotOpenConfig = (1uz << 46),

  InvalidConfig  = (1uz << 63), // flag for if any error happs, needed ?
};
enum class config_parsing_warning_t : uint64_t {
  Success = 0,
  //Warnings = (1uz << 0),

  WarningInvalidAnimationName = (1uz << 10),    //< has fallback
  WarningMaxDeviceNamesReached = (1uz << 14),   //< skip device when full

  // Warnings: Optional Animations -- more of an info; ignore in strcit mode
  CustomSpriteSheetRequiredSleepAnimation = (1uz << 26),
  CustomSpriteSheetRequiredMovingAnimation = (1uz << 27),
  CustomSpriteSheetRequiredWritingAnimation = (1uz << 28),
  CustomSpriteSheetRequiredHappyAnimation = (1uz << 29),

  WarningConfigLineTooLong = (1uz << 40),   //< ignored line anyway
  WarningInvalidConfigLine = (1uz << 41),   //< ignored line
  WarningUnknownConfigKey = (1uz << 42),    //< so it can skip parsing for the "next key"; maybe "clear" the warning AFTER key was found ?
  WarningNoInputDevices = (1uz << 43),      //< devices are optional
};
struct config_parse_result_t {
  config_parsing_error_t errors{config_parsing_error_t::Success};
  config_parsing_warning_t warnings{config_parsing_warning_t::Success};

  config_parse_result_t() = default;
  config_parse_result_t(config_parsing_error_t errs, config_parsing_warning_t warns) : errors(errs), warnings(warns) {}
  explicit(true) config_parse_result_t(config_parsing_error_t errs) : errors(errs), warnings(config_parsing_warning_t::Success) {}
  explicit(true) config_parse_result_t(config_parsing_warning_t warns) : errors(config_parsing_error_t::Success), warnings(warns) {}
};
struct loaded_config_result_t {
  config_t config{};
  config_parse_result_t result;

  loaded_config_result_t() = default;
  loaded_config_result_t(config_t&& res, config_parsing_error_t errs, config_parsing_warning_t warns) : config(bongocat::move(res)), result(errs, warns) {}
  loaded_config_result_t(config_parsing_error_t errs, config_parsing_warning_t warns) : result(errs, warns) {}
  explicit(true) loaded_config_result_t(config_parsing_error_t errs) : result(errs) {}
  explicit(true) loaded_config_result_t(config_parsing_warning_t warns) : result(warns) {}
  explicit(false) loaded_config_result_t(config_t&& res) : config(bongocat::move(res)) {}
  explicit(false) loaded_config_result_t(config_parse_result_t res) : result(res) {}
  explicit(false) loaded_config_result_t(config_parse_result_t&& res) : result(bongocat::move(res)) {}
  explicit(true) loaded_config_result_t(config_t&& res, config_parse_result_t&& errors) : config(bongocat::move(res)), result(bongocat::move(errors)) {}
};
BONGOCAT_NODISCARD inline bool is_valid_config_result(const loaded_config_result_t& res) {
  if (res.config._strict) {
    return res.result.errors == config_parsing_error_t::Success;
  }

  return true;
}

struct load_config_overwrite_parameters_t {
  const char *output_name{BONGOCAT_NULLPTR};
  int32_t randomize_index{-1};
  int32_t strict{-1};
  const char *animation_name{BONGOCAT_NULLPTR};
};
BONGOCAT_NODISCARD loaded_config_result_t load(const char *config_file_path, load_config_overwrite_parameters_t overwrite_parameters);
void reset(config_t& config);

void set_defaults(config_t& config);

// Resolve config file path with XDG fallback
// Returns a static/allocated path, or NULL if none found.
AllocatedString resolve_path(const char *explicit_path);

}  // namespace bongocat::config

#endif  // BONGOCAT_CONFIG_H