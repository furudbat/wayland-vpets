#ifndef BONGOCAT_EMBEDDED_ASSETS_CLIPPY_H
#define BONGOCAT_EMBEDDED_ASSETS_CLIPPY_H

#include "embedded_assets/embedded_image.h"

#include <cstddef>
#include <cstdint>

namespace bongocat::assets {
struct ms_agent_animation_indices_t {
  int32_t start_index_frame_idle{0};
  int32_t end_index_frame_idle{0};

  int32_t start_index_frame_boring{0};
  int32_t end_index_frame_boring{0};

  int32_t start_index_frame_start_writing{0};
  int32_t end_index_frame_start_writing{0};
  int32_t start_index_frame_writing{0};
  int32_t end_index_frame_writing{0};
  int32_t start_index_frame_end_writing{0};
  int32_t end_index_frame_end_writing{0};

  int32_t start_index_frame_sleep{0};
  int32_t end_index_frame_sleep{0};

  int32_t start_index_frame_wake_up{0};
  int32_t end_index_frame_wake_up{0};

  int32_t start_index_frame_start_working{0};
  int32_t end_index_frame_start_working{0};
  int32_t start_index_frame_working{0};
  int32_t end_index_frame_working{0};
  int32_t start_index_frame_end_working{0};
  int32_t end_index_frame_end_working{0};

  int32_t start_index_frame_start_moving{0};
  int32_t end_index_frame_start_moving{0};
  int32_t start_index_frame_moving{0};
  int32_t end_index_frame_moving{0};
  int32_t start_index_frame_end_moving{0};
  int32_t end_index_frame_end_moving{0};

  int32_t start_index_frame_happy{0};
  int32_t end_index_frame_happy{0};
};

inline static constexpr size_t MS_AGENT_SPRITE_SHEET_ROW_IDLE = 0;
inline static constexpr size_t MS_AGENT_SPRITE_SHEET_ROW_BORING = 0;
inline static constexpr size_t MS_AGENT_SPRITE_SHEET_ROW_START_WRITING = 1;
inline static constexpr size_t MS_AGENT_SPRITE_SHEET_ROW_WRITING = 2;
inline static constexpr size_t MS_AGENT_SPRITE_SHEET_ROW_END_WRITING = 3;
inline static constexpr size_t MS_AGENT_SPRITE_SHEET_ROW_SLEEP = 4;
inline static constexpr size_t MS_AGENT_SPRITE_SHEET_ROW_WAKE_UP = 5;
inline static constexpr size_t MS_AGENT_SPRITE_SHEET_ROW_START_WORKING = 6;
inline static constexpr size_t MS_AGENT_SPRITE_SHEET_ROW_WORKING = 7;
inline static constexpr size_t MS_AGENT_SPRITE_SHEET_ROW_END_WORKING = 8;
inline static constexpr size_t MS_AGENT_SPRITE_SHEET_ROW_START_MOVING = 9;
inline static constexpr size_t MS_AGENT_SPRITE_SHEET_ROW_MOVING = 10;
inline static constexpr size_t MS_AGENT_SPRITE_SHEET_ROW_END_MOVING = 11;
inline static constexpr size_t MS_AGENT_SPRITE_SHEET_ROW_HAPPY = 12;
enum class ClippyAnimations : uint8_t {
  Idle = MS_AGENT_SPRITE_SHEET_ROW_IDLE,
  Boring = MS_AGENT_SPRITE_SHEET_ROW_BORING,
  StartWriting = MS_AGENT_SPRITE_SHEET_ROW_START_WRITING,
  Writing = MS_AGENT_SPRITE_SHEET_ROW_WRITING,
  EndWriting = MS_AGENT_SPRITE_SHEET_ROW_END_WRITING,
  Sleep = MS_AGENT_SPRITE_SHEET_ROW_SLEEP,
  WakeUp = MS_AGENT_SPRITE_SHEET_ROW_WAKE_UP,
  // optional
  StartWorking = MS_AGENT_SPRITE_SHEET_ROW_START_WORKING,
  Working = MS_AGENT_SPRITE_SHEET_ROW_WORKING,
  EndWorking = MS_AGENT_SPRITE_SHEET_ROW_END_WORKING,
  StartMoving = MS_AGENT_SPRITE_SHEET_ROW_START_MOVING,
  Moving = MS_AGENT_SPRITE_SHEET_ROW_MOVING,
  EndMoving = MS_AGENT_SPRITE_SHEET_ROW_END_MOVING,
  Happy = MS_AGENT_SPRITE_SHEET_ROW_HAPPY,
};

#ifdef FEATURE_MORE_MS_AGENT_EMBEDDED_ASSETS
inline static constexpr size_t MS_AGENTS_SPRITE_SHEET_EMBEDDED_IMAGES_COUNT = 4;
inline static constexpr size_t MS_AGENTS_ANIMATIONS_COUNT = 4;
#else
inline static constexpr size_t MS_AGENTS_SPRITE_SHEET_EMBEDDED_IMAGES_COUNT = 1;
inline static constexpr size_t MS_AGENTS_ANIMATIONS_COUNT = 1;
#endif

[[nodiscard]] embedded_image_t get_ms_agent_sprite_sheet(size_t i);
[[nodiscard]] ms_agent_animation_indices_t get_ms_agent_animation_indices(size_t i);
}  // namespace bongocat::assets

#endif  // BONGOCAT_EMBEDDED_ASSETS_CLIPPY_H
