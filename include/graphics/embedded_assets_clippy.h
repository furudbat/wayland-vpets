#ifndef BONGOCAT_EMBEDDED_ASSETS_CLIPPY_H
#define BONGOCAT_EMBEDDED_ASSETS_CLIPPY_H

#include "embedded_assets_image.h"
#include <cstddef>
#include <cstdint>


namespace bongocat::assets {
    inline static constexpr size_t CLIPPY_SPRITE_SHEET_ROW_IDLE = 0;
    inline static constexpr size_t CLIPPY_SPRITE_SHEET_ROW_BORING = 0;
    inline static constexpr size_t CLIPPY_SPRITE_SHEET_ROW_START_WRITING = 1;
    inline static constexpr size_t CLIPPY_SPRITE_SHEET_ROW_WRITING = 2;
    inline static constexpr size_t CLIPPY_SPRITE_SHEET_ROW_END_WRITING = 3;
    inline static constexpr size_t CLIPPY_SPRITE_SHEET_ROW_SLEEP = 4;
    inline static constexpr size_t CLIPPY_SPRITE_SHEET_ROW_WAKE_UP = 5;
    enum class ClippyAnimations : uint8_t {
        Idle = CLIPPY_SPRITE_SHEET_ROW_IDLE,
        Boring = CLIPPY_SPRITE_SHEET_ROW_BORING,
        StartWriting = CLIPPY_SPRITE_SHEET_ROW_START_WRITING,
        Writing = CLIPPY_SPRITE_SHEET_ROW_WRITING,
        EndWriting = CLIPPY_SPRITE_SHEET_ROW_END_WRITING,
        Sleep = CLIPPY_SPRITE_SHEET_ROW_SLEEP,
        WakeUp = CLIPPY_SPRITE_SHEET_ROW_WAKE_UP,
    };


    // Clippy
    inline static constexpr size_t CLIPPY_SPRITE_SHEET_COLS = 40;
    inline static constexpr size_t CLIPPY_SPRITE_SHEET_ROWS = 6;
    inline static constexpr size_t CLIPPY_ANIM_INDEX = 0;
    inline static constexpr size_t CLIPPY_FRAMES_IDLE = 4;
    inline static constexpr size_t CLIPPY_FRAMES_BORING = 40;
    inline static constexpr size_t CLIPPY_FRAMES_START_WRITING = 9;
    inline static constexpr size_t CLIPPY_FRAMES_WRITING = 35;
    inline static constexpr size_t CLIPPY_FRAMES_END_WRITING = 5;
    inline static constexpr size_t CLIPPY_FRAMES_SLEEP = 19;
    inline static constexpr size_t CLIPPY_FRAMES_WAKE_UP = 16;


    static inline constexpr size_t MS_PETS_SPRITE_SHEET_EMBEDDED_IMAGES_COUNT = 1;
    inline static constexpr size_t MS_PETS_SPRITE_SHEET_ROWS = 6;

#ifndef FEATURE_INCLUDE_ONLY_BONGOCAT_EMBEDDED_ASSETS
    inline static constexpr size_t MS_PETS_ANIMATIONS_COUNT = 1;
#else
    inline static constexpr size_t MS_PETS_ANIMATIONS_COUNT = 0;
#endif

#ifndef FEATURE_INCLUDE_ONLY_BONGOCAT_EMBEDDED_ASSETS
    embedded_image_t get_ms_pet_sprite(size_t i);
#endif
}

#endif // BONGOCAT_EMBEDDED_ASSETS_H
