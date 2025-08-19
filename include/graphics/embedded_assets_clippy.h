#ifndef BONGOCAT_EMBEDDED_ASSETS_CLIPPY_H
#define BONGOCAT_EMBEDDED_ASSETS_CLIPPY_H

#include "embedded_assets_image.h"
#include "sprite_sheet.h"
#include "graphics/embedded_assets/clippy.hpp"
#include <cstddef>
#include <cstdint>


namespace bongocat::assets {
#ifndef FEATURE_INCLUDE_ONLY_BONGOCAT_EMBEDDED_ASSETS
    enum class ClippyAnimations : uint8_t {
        Idle,
        StartWriting,
        Writing,
        EndWriting,
    };


    // Clippy
    inline static constexpr std::size_t CLIPPY_SPRITE_SHEET_COLS = 40;
    inline static constexpr std::size_t CLIPPY_SPRITE_SHEET_ROWS = 4;
    inline static constexpr std::size_t CLIPPY_ANIM_INDEX = 0;
    inline static constexpr std::size_t CLIPPY_FRAMES_IDLE = 40;
    inline static constexpr std::size_t CLIPPY_FRAMES_START_WRITING = 9;
    inline static constexpr std::size_t CLIPPY_FRAMES_WRITING = 35;
    inline static constexpr std::size_t CLIPPY_FRAMES_END_WRITING = 5;


    static inline constexpr size_t MS_PETS_SPRITE_SHEET_EMBEDDED_IMAGES_COUNT = 1;
    inline static constexpr size_t MS_PETS_ANIMATIONS_COUNT = 1;

    constexpr embedded_image_t get_ms_pet_sprite(size_t i) {
        using namespace animation;
        switch (i) {
            case CLIPPY_ANIM_INDEX: return {clippy_png, clippy_png_size, "embedded clippy.png"};
            default: return { nullptr, 0, "" };
        }
    }
#endif
}

#endif // BONGOCAT_EMBEDDED_ASSETS_H
