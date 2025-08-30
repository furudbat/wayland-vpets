#ifndef BONGOCAT_EMBEDDED_ASSETS_CLIPPY_H
#define BONGOCAT_EMBEDDED_ASSETS_CLIPPY_H

#include "embedded_image.h"
#include <cstdint>

namespace bongocat::assets {
#ifdef FEATURE_MS_AGENT_EMBEDDED_ASSETS
    inline static constexpr size_t MS_AGENT_SPRITE_SHEET_ROW_IDLE = 0;
    inline static constexpr size_t MS_AGENT_SPRITE_SHEET_ROW_BORING = 0;
    inline static constexpr size_t MS_AGENT_SPRITE_SHEET_ROW_START_WRITING = 1;
    inline static constexpr size_t MS_AGENT_SPRITE_SHEET_ROW_WRITING = 2;
    inline static constexpr size_t MS_AGENT_SPRITE_SHEET_ROW_END_WRITING = 3;
    inline static constexpr size_t MS_AGENT_SPRITE_SHEET_ROW_SLEEP = 4;
    inline static constexpr size_t MS_AGENT_SPRITE_SHEET_ROW_WAKE_UP = 5;
    enum class ClippyAnimations : uint8_t {
        Idle = MS_AGENT_SPRITE_SHEET_ROW_IDLE,
        Boring = MS_AGENT_SPRITE_SHEET_ROW_BORING,
        StartWriting = MS_AGENT_SPRITE_SHEET_ROW_START_WRITING,
        Writing = MS_AGENT_SPRITE_SHEET_ROW_WRITING,
        EndWriting = MS_AGENT_SPRITE_SHEET_ROW_END_WRITING,
        Sleep = MS_AGENT_SPRITE_SHEET_ROW_SLEEP,
        WakeUp = MS_AGENT_SPRITE_SHEET_ROW_WAKE_UP,
    };
    inline static constexpr size_t MS_AGENTS_SPRITE_SHEET_ROWS = 6;
    inline static constexpr size_t MAX_SPRITE_SHEET_COL_FRAMES = 40;

#ifdef FEATURE_MORE_MS_AGENT_EMBEDDED_ASSETS
    inline static constexpr size_t MS_AGENTS_SPRITE_SHEET_EMBEDDED_IMAGES_COUNT = 2;
    inline static constexpr size_t MS_AGENTS_ANIMATIONS_COUNT = 2;
#else
    inline static constexpr size_t MS_AGENTS_SPRITE_SHEET_EMBEDDED_IMAGES_COUNT = 1;
    inline static constexpr size_t MS_AGENTS_ANIMATIONS_COUNT = 1;
#endif

    embedded_image_t get_ms_agent_sprite_sheet(size_t i);
    ms_agent_animation_indices_t get_ms_agent_animation_indices(size_t i);
#else
    inline static constexpr size_t MS_AGENTS_ANIMATIONS_COUNT = 0;
#endif
}

#endif // BONGOCAT_EMBEDDED_ASSETS_CLIPPY_H
