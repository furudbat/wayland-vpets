#ifndef BONGOCAT_EMBEDDED_ASSETS_CUSTOM_SPRITE_H
#define BONGOCAT_EMBEDDED_ASSETS_CUSTOM_SPRITE_H

#include "graphics/embedded_assets_misc.h"
#include "custom_sprite_settings.h"
#include "embedded_assets/assets.h"
#include <cstddef>
#include <cstdint>

namespace bongocat::assets {
// custom sprite sheet (at run time); < 1 is reserved for misc, see misc.hpp and MISC_ANIM_COUNT, so misc is also custom but everything after that is user-custom
inline static constexpr std::size_t CUSTOM_ANIM_INDEX = MISC_ANIM_COUNT;

// custom (sprite sheet)
inline static constexpr char CUSTOM_ID_ARR[] CONFIG_STRING_SECTION = "custom";
inline static constexpr const char *CUSTOM_ID = CUSTOM_ID_ARR;
inline static constexpr std::size_t CUSTOM_ID_LEN = sizeof(CUSTOM_ID_ARR) - 1;
inline static constexpr char CUSTOM_NAME_ARR[] CONFIG_STRING_SECTION = "custom";
inline static constexpr const char *CUSTOM_NAME = CUSTOM_NAME_ARR;
inline static constexpr std::size_t CUSTOM_NAME_LEN = sizeof(CUSTOM_NAME_ARR) - 1;

static inline constexpr int CUSTOM_HAPPY_CHANCE_PERCENT = 60;

inline int get_custom_animation_settings_rows_count(const custom_animation_settings_t& sprite_sheet_settings) {
  if (sprite_sheet_settings.rows >= 1) {
    return sprite_sheet_settings.rows;
  }

  int sprite_sheet_rows{0};

  // detect sprite sheet rows
  if (sprite_sheet_settings.idle_frames > 0)
    sprite_sheet_rows++;
  if (sprite_sheet_settings.boring_frames > 0)
    sprite_sheet_rows++;

  if (sprite_sheet_settings.start_writing_frames > 0)
    sprite_sheet_rows++;
  if (sprite_sheet_settings.writing_frames > 0)
    sprite_sheet_rows++;
  if (sprite_sheet_settings.end_writing_frames > 0)
    sprite_sheet_rows++;
  if (sprite_sheet_settings.happy_frames > 0)
    sprite_sheet_rows++;

  if (sprite_sheet_settings.asleep_frames > 0)
    sprite_sheet_rows++;
  if (sprite_sheet_settings.sleep_frames > 0)
    sprite_sheet_rows++;
  if (sprite_sheet_settings.wake_up_frames > 0)
    sprite_sheet_rows++;

  if (sprite_sheet_settings.start_working_frames > 0)
    sprite_sheet_rows++;
  if (sprite_sheet_settings.working_frames > 0)
    sprite_sheet_rows++;
  if (sprite_sheet_settings.end_working_frames > 0)
    sprite_sheet_rows++;

  if (sprite_sheet_settings.start_moving_frames > 0)
    sprite_sheet_rows++;
  if (sprite_sheet_settings.moving_frames > 0)
    sprite_sheet_rows++;
  if (sprite_sheet_settings.end_moving_frames > 0)
    sprite_sheet_rows++;

  if (sprite_sheet_settings.start_running_frames > 0)
    sprite_sheet_rows++;
  if (sprite_sheet_settings.running_frames > 0)
    sprite_sheet_rows++;
  if (sprite_sheet_settings.end_running_frames > 0)
    sprite_sheet_rows++;

  return sprite_sheet_rows;
}
inline int get_custom_animation_settings_max_cols(const custom_animation_settings_t& sprite_sheet_settings) {
  int sprite_sheet_cols = sprite_sheet_settings.idle_frames;

  if (sprite_sheet_settings.boring_frames >= sprite_sheet_cols)
    sprite_sheet_cols = sprite_sheet_settings.boring_frames;

  if (sprite_sheet_settings.start_writing_frames >= sprite_sheet_cols)
    sprite_sheet_cols = sprite_sheet_settings.start_writing_frames;
  if (sprite_sheet_settings.writing_frames >= sprite_sheet_cols)
    sprite_sheet_cols = sprite_sheet_settings.writing_frames;
  if (sprite_sheet_settings.end_writing_frames >= sprite_sheet_cols)
    sprite_sheet_cols = sprite_sheet_settings.end_writing_frames;
  if (sprite_sheet_settings.happy_frames >= sprite_sheet_cols)
    sprite_sheet_cols = sprite_sheet_settings.happy_frames;

  if (sprite_sheet_settings.asleep_frames >= sprite_sheet_cols)
    sprite_sheet_cols = sprite_sheet_settings.asleep_frames;
  if (sprite_sheet_settings.sleep_frames >= sprite_sheet_cols)
    sprite_sheet_cols = sprite_sheet_settings.sleep_frames;
  if (sprite_sheet_settings.wake_up_frames >= sprite_sheet_cols)
    sprite_sheet_cols = sprite_sheet_settings.wake_up_frames;

  if (sprite_sheet_settings.start_working_frames >= sprite_sheet_cols)
    sprite_sheet_cols = sprite_sheet_settings.start_working_frames;
  if (sprite_sheet_settings.working_frames >= sprite_sheet_cols)
    sprite_sheet_cols = sprite_sheet_settings.working_frames;
  if (sprite_sheet_settings.end_working_frames >= sprite_sheet_cols)
    sprite_sheet_cols = sprite_sheet_settings.end_working_frames;

  if (sprite_sheet_settings.start_moving_frames >= sprite_sheet_cols)
    sprite_sheet_cols = sprite_sheet_settings.start_moving_frames;
  if (sprite_sheet_settings.moving_frames >= sprite_sheet_cols)
    sprite_sheet_cols = sprite_sheet_settings.moving_frames;
  if (sprite_sheet_settings.end_moving_frames >= sprite_sheet_cols)
    sprite_sheet_cols = sprite_sheet_settings.end_moving_frames;

  if (sprite_sheet_settings.start_running_frames >= sprite_sheet_cols)
    sprite_sheet_cols = sprite_sheet_settings.start_running_frames;
  if (sprite_sheet_settings.running_frames >= sprite_sheet_cols)
    sprite_sheet_cols = sprite_sheet_settings.running_frames;
  if (sprite_sheet_settings.end_running_frames >= sprite_sheet_cols)
    sprite_sheet_cols = sprite_sheet_settings.end_running_frames;

  return sprite_sheet_cols;
}
}  // namespace bongocat::assets

#endif  // BONGOCAT_EMBEDDED_ASSETS_CUSTOM_SPRITE_H
