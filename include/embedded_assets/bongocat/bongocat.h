#ifndef BONGOCAT_EMBEDDED_ASSETS_BONGOCAT_H
#define BONGOCAT_EMBEDDED_ASSETS_BONGOCAT_H

#include "core/bongocat.h"
#include "embedded_assets/embedded_image.h"
#include "graphics/sprite_sheet.h"

#include <cstddef>

namespace bongocat::animation {
struct animation_context_t;
}

namespace bongocat::assets {
// Bongocat Frames
inline static constexpr int BONGOCAT_FRAME_BOTH_UP = 0;
inline static constexpr int BONGOCAT_FRAME_LEFT_DOWN = 1;
inline static constexpr int BONGOCAT_FRAME_RIGHT_DOWN = 2;
inline static constexpr int BONGOCAT_FRAME_BOTH_DOWN = 3;

inline static constexpr size_t BONGOCAT_SPRITE_SHEET_COLS = 4;
inline static constexpr size_t BONGOCAT_SPRITE_SHEET_ROWS = 1;
inline static constexpr size_t BONGOCAT_SPRITE_SHEET_ROW = 0;

// apparently
inline static constexpr int BONGOCAT_FRAME_WIDTH = 864;
inline static constexpr int BONGOCAT_FRAME_HEIGHT = 360;

inline static constexpr size_t BONGOCAT_EMBEDDED_IMAGES_COUNT = animation::BONGOCAT_NUM_FRAMES;
inline static constexpr size_t BONGOCAT_ANIMATIONS_COUNT = 1;

[[nodiscard]] extern embedded_image_t get_bongocat_sprite(size_t i);
[[nodiscard]] extern created_result_t<animation::generic_sprite_sheet_t>
get_bongocat_sprite_sheet(const animation::animation_context_t& ctx, int index);
}  // namespace bongocat::assets

#endif  // BONGOCAT_EMBEDDED_ASSETS_BONGOCAT_H
