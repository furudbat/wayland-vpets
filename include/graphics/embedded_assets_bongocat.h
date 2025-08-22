#ifndef BONGOCAT_EMBEDDED_ASSETS_BONGOCAT_H
#define BONGOCAT_EMBEDDED_ASSETS_BONGOCAT_H

#include "sprite_sheet.h"
#include "embedded_assets_image.h"
#include <cstddef>

namespace bongocat::assets {
#ifdef FEATURE_BONGOCAT_EMBEDDED_ASSETS
    // Bongocat Frames
    inline static constexpr int BONGOCAT_FRAME_BOTH_UP = 0;
    inline static constexpr int BONGOCAT_FRAME_LEFT_DOWN = 1;
    inline static constexpr int BONGOCAT_FRAME_RIGHT_DOWN = 2;
    inline static constexpr int BONGOCAT_FRAME_BOTH_DOWN = 3;
    inline static constexpr std::size_t BONGOCAT_SPRITE_SHEET_COLS = 4;
    inline static constexpr std::size_t BONGOCAT_SPRITE_SHEET_ROWS = 1;

    inline static constexpr size_t BONGOCAT_EMBEDDED_IMAGES_COUNT = animation::BONGOCAT_NUM_FRAMES;
    inline static constexpr size_t BONGOCAT_ANIMATIONS_COUNT = 1;

    extern embedded_image_t get_bongocat_sprite(size_t i);
#else
    inline static constexpr size_t BONGOCAT_ANIMATIONS_COUNT = 0;
#endif
}

#endif // BONGOCAT_EMBEDDED_ASSETS_BONGOCAT_H
