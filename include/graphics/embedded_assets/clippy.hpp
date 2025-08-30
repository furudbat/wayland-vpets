#ifndef BONGOCAT_EMBEDDED_ASSETS_CLIPPY_HPP
#define BONGOCAT_EMBEDDED_ASSETS_CLIPPY_HPP

#include <cstddef>

namespace bongocat::assets {
    // Clippy
    inline static constexpr size_t CLIPPY_SPRITE_SHEET_COLS = 40;
    inline static constexpr size_t CLIPPY_SPRITE_SHEET_ROWS = 6;
    inline static constexpr size_t CLIPPY_FRAMES_IDLE = 4;
    inline static constexpr size_t CLIPPY_FRAMES_BORING = 40;
    inline static constexpr size_t CLIPPY_FRAMES_START_WRITING = 9;
    inline static constexpr size_t CLIPPY_FRAMES_WRITING = 35;
    inline static constexpr size_t CLIPPY_FRAMES_END_WRITING = 5;
    inline static constexpr size_t CLIPPY_FRAMES_SLEEP = 19;
    inline static constexpr size_t CLIPPY_FRAMES_WAKE_UP = 16;
    inline static constexpr size_t CLIPPY_ANIM_INDEX = 0;

#ifdef FEATURE_MORE_MS_AGENT_EMBEDDED_ASSETS
    // Links
    inline static constexpr size_t LINKS_SPRITE_SHEET_COLS = 35;
    inline static constexpr size_t LINKS_SPRITE_SHEET_ROWS = 6;
    inline static constexpr size_t LINKS_FRAMES_IDLE = 3;
    inline static constexpr size_t LINKS_FRAMES_BORING = 18;
    inline static constexpr size_t LINKS_FRAMES_START_WRITING = 13;
    inline static constexpr size_t LINKS_FRAMES_WRITING = 35;
    inline static constexpr size_t LINKS_FRAMES_END_WRITING = 5;
    inline static constexpr size_t LINKS_FRAMES_SLEEP = 20;
    inline static constexpr size_t LINKS_FRAMES_WAKE_UP = 14;
    inline static constexpr size_t LINKS_ANIM_INDEX = 1;

    inline static constexpr size_t MS_AGENTS_ANIM_COUNT = 2;
#else
    inline static constexpr size_t MS_AGENTS_ANIM_COUNT = 1;
#endif
}

#endif // BONGOCAT_EMBEDDED_ASSETS_CLIPPY_HPP
