#ifndef BONGOCAT_EMBEDDED_ASSETS_CLIPPY_H
#define BONGOCAT_EMBEDDED_ASSETS_CLIPPY_H

#include "embedded_assets_image.h"
#include <cstddef>
#include <cstdint>


namespace bongocat::assets {
    inline static constexpr size_t CLIPPY_SPRITE_SHEET_ROW_IDLE = 0;
    inline static constexpr size_t CLIPPY_SPRITE_SHEET_ROW_START_WRITING = 1;
    inline static constexpr size_t CLIPPY_SPRITE_SHEET_ROW_WRITING = 2;
    inline static constexpr size_t CLIPPY_SPRITE_SHEET_ROW_END_WRITING = 3;
    inline static constexpr size_t CLIPPY_SPRITE_SHEET_ROW_SLEEP = 4;
    enum class ClippyAnimations : uint8_t {
        Idle = CLIPPY_SPRITE_SHEET_ROW_IDLE,
        StartWriting = CLIPPY_SPRITE_SHEET_ROW_START_WRITING,
        Writing = CLIPPY_SPRITE_SHEET_ROW_WRITING,
        EndWriting = CLIPPY_SPRITE_SHEET_ROW_END_WRITING,
        Sleep = CLIPPY_SPRITE_SHEET_ROW_SLEEP,
    };


    // Clippy
    inline static constexpr size_t CLIPPY_SPRITE_SHEET_COLS = 40;
    inline static constexpr size_t CLIPPY_SPRITE_SHEET_ROWS = 5;
    inline static constexpr size_t CLIPPY_ANIM_INDEX = 0;
    inline static constexpr size_t CLIPPY_FRAMES_IDLE = 40;
    inline static constexpr size_t CLIPPY_FRAMES_START_WRITING = 9;
    inline static constexpr size_t CLIPPY_FRAMES_WRITING = 35;
    inline static constexpr size_t CLIPPY_FRAMES_END_WRITING = 5;
    inline static constexpr size_t CLIPPY_FRAMES_SLEEP = 1;


    static inline constexpr size_t MS_PETS_SPRITE_SHEET_EMBEDDED_IMAGES_COUNT = 1;
    inline static constexpr size_t MS_PETS_SPRITE_SHEET_ROWS = 5;

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
