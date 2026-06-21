#ifndef BONGOCAT_EMBEDDED_ASSETS_BONGOCAT_H
#define BONGOCAT_EMBEDDED_ASSETS_BONGOCAT_H

#include "core/bongocat.h"
#include "embedded_assets/embedded_image.h"
#include "graphics/sprite_sheet.h"
#include <cstddef>
#include <cstdint>

namespace bongocat::animation {
struct animation_thread_context_t;
}

namespace bongocat::assets {
// Bongocat Frames
inline static constexpr int BONGOCAT_FRAME_BOTH_UP = 0;
inline static constexpr int BONGOCAT_FRAME_LEFT_DOWN = 1;
inline static constexpr int BONGOCAT_FRAME_RIGHT_DOWN = 2;
inline static constexpr int BONGOCAT_FRAME_BOTH_DOWN = 3;
inline static constexpr int BONGOCAT_FRAME_SLEEPING = 4;

inline static constexpr size_t BONGOCAT_SPRITE_SHEET_COLS = 5;
inline static constexpr size_t BONGOCAT_SPRITE_SHEET_ROWS = 1;
inline static constexpr size_t BONGOCAT_SPRITE_SHEET_ROW = 0;

// apparently
inline static constexpr int BONGOCAT_FRAME_WIDTH = 864;
inline static constexpr int BONGOCAT_FRAME_HEIGHT = 360;

inline static constexpr int BONGOCAT_SVG_FRAME_WIDTH = 500;
inline static constexpr int BONGOCAT_SVG_FRAME_HEIGHT = 500;
inline static constexpr int BONGOCAT_SVG_FRAME_TX = 0;
inline static constexpr int BONGOCAT_SVG_FRAME_TY = 0;
inline static constexpr uint32_t BONGOCAT_SVG_ALPHA_MASK = 0x808080FF; // rgba(128,128,128,255)
inline static constexpr int BONGOCAT_SVG_FRAME_REAL_CAT_WIDTH = 390;
inline static constexpr int BONGOCAT_SVG_FRAME_REAL_CAT_HEIGHT = 216;

inline static constexpr size_t BONGOCAT_EMBEDDED_IMAGES_COUNT = animation::BONGOCAT_NUM_FRAMES;
inline static constexpr size_t BONGOCAT_ANIMATIONS_COUNT = 1;

BONGOCAT_NODISCARD extern embedded_image_t get_bongocat_sprite(size_t i);
BONGOCAT_NODISCARD extern created_result_t<animation::generic_sprite_sheet_t>
get_bongocat_sprite_sheet(const animation::animation_thread_context_t& ctx, size_t index);

BONGOCAT_NODISCARD extern embedded_image_t get_bongocat_sprite_svg(size_t i);
}  // namespace bongocat::assets

#endif  // BONGOCAT_EMBEDDED_ASSETS_BONGOCAT_H
