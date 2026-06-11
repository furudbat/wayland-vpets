#ifndef BONGOCAT_CONFIG_H
#define BONGOCAT_CONFIG_H

#include "core/bongocat.h"
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
[[nodiscard]] constexpr const char *to_string(overlay_position_t position) noexcept {
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
[[nodiscard]] constexpr const char *to_string(layer_type_t layer) noexcept {
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
[[nodiscard]] constexpr const char *to_string(align_type_t align) noexcept {
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

// =============================================================================
// CONFIGURATION FUNCTIONS
// =============================================================================

struct config_t;
void config_free_keyboard_devices(config_t& config);
void config_copy_keyboard_devices_from(config_t& config, const config_t& other);
void config_free_keyboard_names(config_t& config);
void config_copy_keyboard_names_from(config_t& config, const config_t& other);
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

  bool enable_feature_evolution{false};

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
    for (size_t i = 0; i < input::MAX_INPUT_DEVICES; ++i) {
      _keyboard_names[i] = BONGOCAT_NULLPTR;
    }
    */
  }
  ~config_t() {
    cleanup(*this);
  }

  config_t(const config_t& other)
      : cat_x_offset(other.cat_x_offset)
      , cat_y_offset(other.cat_y_offset)
      , cat_height(other.cat_height)
      , overlay_height(other.overlay_height)
      , idle_frame(other.idle_frame)
      , keypress_duration_ms(other.keypress_duration_ms)
      , test_animation_duration_ms(other.test_animation_duration_ms)
      , test_animation_interval_sec(other.test_animation_interval_sec)
      , animation_speed_ms(other.animation_speed_ms)
      , fps(other.fps)
      , overlay_opacity(other.overlay_opacity)
      , mirror_x(other.mirror_x)
      , mirror_y(other.mirror_y)
      , enable_antialiasing(other.enable_antialiasing)
      , enable_debug(other.enable_debug)
      , layer(other.layer)
      , overlay_position(other.overlay_position)
      , animation_index(other.animation_index)
      , invert_color(other.invert_color)
      , padding_x(other.padding_x)
      , padding_y(other.padding_y)
      , enable_scheduled_sleep(other.enable_scheduled_sleep)
      , sleep_begin(other.sleep_begin)
      , sleep_end(other.sleep_end)
      , idle_sleep_timeout_sec(other.idle_sleep_timeout_sec)
      , happy_kpm(other.happy_kpm)
      , cat_align(other.cat_align)
      , animation_sprite_sheet_layout(other.animation_sprite_sheet_layout)
      , animation_dm_set(other.animation_dm_set)
      , animation_custom_set(other.animation_custom_set)
      , idle_animation(other.idle_animation)
      , input_fps(other.input_fps)
      , randomize_index(other.randomize_index)
      , randomize_on_reload(other.randomize_on_reload)
      , update_rate_ms(other.update_rate_ms)
      , cpu_threshold(other.cpu_threshold)
      , cpu_running_factor(other.cpu_running_factor)
      , movement_radius(other.movement_radius)
      , enable_movement_debug(other.enable_movement_debug)
      , movement_speed(other.movement_speed)
      , movement_wait_factor(other.movement_wait_factor)
      , screen_width(other.screen_width)
      , custom_sprite_sheet_settings(other.custom_sprite_sheet_settings)
      , enable_hand_mapping(other.enable_hand_mapping)
      , hotplug_scan_interval_ms(other.hotplug_scan_interval_ms)
      , disable_fullscreen_hide(other.disable_fullscreen_hide)
      , enable_feature_evolution(other.enable_feature_evolution)
      , _keep_old_animation_index(other._keep_old_animation_index)
      , _strict(other._strict)
      , _custom(other._custom) {
    output_name = duplicate_string(other.output_name);
    config_copy_keyboard_devices_from(*this, other);
    config_copy_keyboard_names_from(*this, other);
    custom_sprite_sheet_filename = duplicate_string(other.custom_sprite_sheet_filename);
    _animation_name = duplicate_string(other._animation_name);
    _loaded_animation_fqname = duplicate_string(other._loaded_animation_fqname);
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
      mirror_x = other.mirror_x;
      mirror_y = other.mirror_y;
      enable_antialiasing = other.enable_antialiasing;
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
      animation_sprite_sheet_layout = other.animation_sprite_sheet_layout;
      animation_dm_set = other.animation_dm_set;
      animation_custom_set = other.animation_custom_set;
      idle_animation = other.idle_animation;
      input_fps = other.input_fps;
      randomize_index = other.randomize_index;
      randomize_on_reload = other.randomize_on_reload;
      update_rate_ms = other.update_rate_ms;
      movement_radius = other.movement_radius;
      enable_movement_debug = other.enable_movement_debug;
      movement_speed = other.movement_speed;
      movement_wait_factor = other.movement_wait_factor;
      cpu_threshold = other.cpu_threshold;
      cpu_running_factor = other.cpu_running_factor;
      screen_width = other.screen_width;
      custom_sprite_sheet_settings = other.custom_sprite_sheet_settings;
      enable_hand_mapping = other.enable_hand_mapping;
      hotplug_scan_interval_ms = other.hotplug_scan_interval_ms;
      disable_fullscreen_hide = other.disable_fullscreen_hide;
      enable_feature_evolution = other.enable_feature_evolution;
      _keep_old_animation_index = other._keep_old_animation_index;
      _strict = other._strict;
      _custom = other._custom;

      output_name = duplicate_string(other.output_name);
      config_copy_keyboard_devices_from(*this, other);
      config_copy_keyboard_names_from(*this, other);
      custom_sprite_sheet_filename = duplicate_string(other.custom_sprite_sheet_filename);
      _animation_name = duplicate_string(other._animation_name);
      _loaded_animation_fqname = duplicate_string(other._loaded_animation_fqname);
    }
    return *this;
  }

  config_t(config_t&& other) noexcept
      : output_name(bongocat::move(other.output_name))
      , cat_x_offset(other.cat_x_offset)
      , cat_y_offset(other.cat_y_offset)
      , cat_height(other.cat_height)
      , overlay_height(other.overlay_height)
      , idle_frame(other.idle_frame)
      , keypress_duration_ms(other.keypress_duration_ms)
      , test_animation_duration_ms(other.test_animation_duration_ms)
      , test_animation_interval_sec(other.test_animation_interval_sec)
      , animation_speed_ms(other.animation_speed_ms)
      , fps(other.fps)
      , overlay_opacity(other.overlay_opacity)
      , mirror_x(other.mirror_x)
      , mirror_y(other.mirror_y)
      , enable_antialiasing(other.enable_antialiasing)
      , enable_debug(other.enable_debug)
      , layer(other.layer)
      , overlay_position(other.overlay_position)
      , animation_index(other.animation_index)
      , invert_color(other.invert_color)
      , padding_x(other.padding_x)
      , padding_y(other.padding_y)
      , enable_scheduled_sleep(other.enable_scheduled_sleep)
      , sleep_begin(other.sleep_begin)
      , sleep_end(other.sleep_end)
      , idle_sleep_timeout_sec(other.idle_sleep_timeout_sec)
      , happy_kpm(other.happy_kpm)
      , cat_align(other.cat_align)
      , animation_sprite_sheet_layout(other.animation_sprite_sheet_layout)
      , animation_dm_set(other.animation_dm_set)
      , animation_custom_set(other.animation_custom_set)
      , idle_animation(other.idle_animation)
      , input_fps(other.input_fps)
      , randomize_index(other.randomize_index)
      , randomize_on_reload(other.randomize_on_reload)
      , update_rate_ms(other.update_rate_ms)
      , cpu_threshold(other.cpu_threshold)
      , cpu_running_factor(other.cpu_running_factor)
      , movement_radius(other.movement_radius)
      , enable_movement_debug(other.enable_movement_debug)
      , movement_speed(other.movement_speed)
      , movement_wait_factor(other.movement_wait_factor)
      , screen_width(other.screen_width)
      , custom_sprite_sheet_filename(bongocat::move(other.custom_sprite_sheet_filename))
      , custom_sprite_sheet_settings(bongocat::move(other.custom_sprite_sheet_settings))
      , enable_hand_mapping(other.enable_hand_mapping)
      , hotplug_scan_interval_ms(other.hotplug_scan_interval_ms)
      , disable_fullscreen_hide(other.disable_fullscreen_hide)
      , enable_feature_evolution(other.enable_feature_evolution)
      , _keep_old_animation_index(other._keep_old_animation_index)
      , _strict(other._strict)
      , _custom(other._custom)
      , _animation_name(bongocat::move(other._animation_name))
      , _loaded_animation_fqname(bongocat::move(other._loaded_animation_fqname)) {
    for (int i = 0; i < other.num_keyboard_devices; ++i) {
      keyboard_devices[i] = bongocat::move(other.keyboard_devices[i]);
      other.keyboard_devices[i] = BONGOCAT_NULLPTR;
    }
    num_keyboard_devices = other.num_keyboard_devices;

    for (int i = 0; i < other._num_keyboard_names; ++i) {
      _keyboard_names[i] = bongocat::move(other._keyboard_names[i]);
      other._keyboard_names[i] = BONGOCAT_NULLPTR;
    }
    _num_keyboard_names = other._num_keyboard_names;

    other.num_keyboard_devices = 0;
    other._num_keyboard_names = 0;
    other.output_name = BONGOCAT_NULLPTR;
    other.custom_sprite_sheet_filename = BONGOCAT_NULLPTR;
    other._animation_name = BONGOCAT_NULLPTR;
    other._loaded_animation_fqname = BONGOCAT_NULLPTR;
  }

  config_t& operator=(config_t&& other) noexcept {
    if (this != &other) {
      cleanup(*this);

      output_name = bongocat::move(other.output_name);
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
      mirror_x = other.mirror_x;
      mirror_y = other.mirror_y;
      enable_antialiasing = other.enable_antialiasing;
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
      animation_sprite_sheet_layout = other.animation_sprite_sheet_layout;
      animation_dm_set = other.animation_dm_set;
      animation_custom_set = other.animation_custom_set;
      idle_animation = other.idle_animation;
      input_fps = other.input_fps;
      randomize_index = other.randomize_index;
      randomize_on_reload = other.randomize_on_reload;
      update_rate_ms = other.update_rate_ms;
      cpu_threshold = other.cpu_threshold;
      cpu_running_factor = other.cpu_running_factor;
      movement_radius = other.movement_radius;
      enable_movement_debug = other.enable_movement_debug;
      movement_speed = other.movement_speed;
      movement_wait_factor = other.movement_wait_factor;
      custom_sprite_sheet_filename = bongocat::move(other.custom_sprite_sheet_filename);
      screen_width = other.screen_width;
      custom_sprite_sheet_settings = bongocat::move(other.custom_sprite_sheet_settings);
      enable_hand_mapping = other.enable_hand_mapping;
      hotplug_scan_interval_ms = other.hotplug_scan_interval_ms;
      disable_fullscreen_hide = other.disable_fullscreen_hide;
      enable_feature_evolution = other.enable_feature_evolution;
      _keep_old_animation_index = other._keep_old_animation_index;
      _strict = other._strict;
      _custom = other._custom;
      _animation_name = bongocat::move(other._animation_name);
      _loaded_animation_fqname = bongocat::move(other._loaded_animation_fqname);

      for (int i = 0; i < other.num_keyboard_devices; ++i) {
        keyboard_devices[i] = bongocat::move(other.keyboard_devices[i]);
        // release_allocated_string(other.keyboard_devices[i]);
        other.keyboard_devices[i] = BONGOCAT_NULLPTR;
      }
      num_keyboard_devices = other.num_keyboard_devices;

      for (int i = 0; i < other._num_keyboard_names; ++i) {
        _keyboard_names[i] = bongocat::move(other._keyboard_names[i]);
        // release_allocated_string(other._keyboard_names[i]);
        //  other._keyboard_names[i] = BONGOCAT_NULLPTR;
      }
      _num_keyboard_names = other._num_keyboard_names;

      other.num_keyboard_devices = 0;
      other._num_keyboard_names = 0;
      other.output_name = BONGOCAT_NULLPTR;
      other.custom_sprite_sheet_filename = BONGOCAT_NULLPTR;
      other._animation_name = BONGOCAT_NULLPTR;
      other._loaded_animation_fqname = BONGOCAT_NULLPTR;
    }
    return *this;
  }
};
inline void cleanup(config_t& config) {
  release_allocated_string(config.output_name);
  config_free_keyboard_devices(config);
  config_free_keyboard_names(config);
  release_allocated_string(config.custom_sprite_sheet_filename);
  release_allocated_string(config._animation_name);
  release_allocated_string(config._loaded_animation_fqname);
}

inline void config_free_keyboard_devices(config_t& config) {
  assert(config.num_keyboard_devices >= 0);
  for (size_t i = 0; i < static_cast<size_t>(config.num_keyboard_devices) && i < input::MAX_INPUT_DEVICES; i++) {
    /*
    if (config.keyboard_devices[i] != BONGOCAT_NULLPTR) {
      ::free(config.keyboard_devices[i]);
      config.keyboard_devices[i] = BONGOCAT_NULLPTR;
    }
    */
    release_allocated_string(config.keyboard_devices[i]);
  }
  config.num_keyboard_devices = 0;
}
inline void config_free_keyboard_names(config_t& config) {
  assert(config._num_keyboard_names >= 0);
  for (size_t i = 0; i < static_cast<size_t>(config._num_keyboard_names) && i < input::MAX_INPUT_DEVICES; i++) {
    /*
    if (config._keyboard_names[i] != BONGOCAT_NULLPTR) {
      ::free(config._keyboard_names[i]);
      config._keyboard_names[i] = BONGOCAT_NULLPTR;
    }
    */
    release_allocated_string(config._keyboard_names[i]);
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

struct load_config_overwrite_parameters_t {
  const char *output_name{BONGOCAT_NULLPTR};
  int32_t randomize_index{-1};
  int32_t strict{-1};
  const char *animation_name{BONGOCAT_NULLPTR};
};
BONGOCAT_NODISCARD created_result_t<config_t> load(const char *config_file_path,
                                                   load_config_overwrite_parameters_t overwrite_parameters);
void reset(config_t& config);

void set_defaults(config_t& config);

// Resolve config file path with XDG fallback
// Returns a static/allocated path, or NULL if none found.
AllocatedString resolve_path(const char *explicit_path);

}  // namespace bongocat::config

#endif  // BONGOCAT_CONFIG_H