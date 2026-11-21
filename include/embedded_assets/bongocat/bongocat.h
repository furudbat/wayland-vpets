#ifndef BONGOCAT_EMBEDDED_ASSETS_BONGOCAT_H
#define BONGOCAT_EMBEDDED_ASSETS_BONGOCAT_H

#include "core/bongocat.h"
#include "embedded_assets/embedded_image.h"
#include "graphics/sprite_sheet.h"
#include "embedded_assets/assets.h"
#include <cstddef>
#include <cstdint>

// bongocat
#define ASSETS_BONGOCAT_SPRITE_SETTINGS_SECTION(name) BONGOCAT_ASSETS_SET_SECTION_FOR(bongocat, "sprite_settings", name)
#define ASSETS_BONGOCAT_DIMS_SECTION(name) BONGOCAT_ASSETS_SET_SECTION_FOR(bongocat, "dims", name)
//#define ASSETS_BONGOCAT_EVOL_DATA_SECTION BONGOCAT_ASSETS_SET_SECTION(bongocat, "evol_data")

namespace bongocat::animation {
struct animation_thread_context_t;
}

namespace bongocat::assets {
// Bongocat Frames
inline constexpr int BONGOCAT_FRAME_BOTH_UP = 0;
inline constexpr int BONGOCAT_FRAME_LEFT_DOWN = 1;
inline constexpr int BONGOCAT_FRAME_RIGHT_DOWN = 2;
inline constexpr int BONGOCAT_FRAME_BOTH_DOWN = 3;
inline constexpr int BONGOCAT_FRAME_SLEEPING = 4;

inline constexpr size_t BONGOCAT_SPRITE_SHEET_COLS ASSETS_BONGOCAT_DIMS_SECTION(BONGOCAT_SPRITE_SHEET_COLS) = 5;
inline constexpr size_t BONGOCAT_SPRITE_SHEET_ROWS ASSETS_BONGOCAT_DIMS_SECTION(BONGOCAT_SPRITE_SHEET_ROWS) = 1;
inline constexpr size_t BONGOCAT_SPRITE_SHEET_ROW = 0;

// apparently
inline constexpr int BONGOCAT_FRAME_WIDTH = 864;
inline constexpr int BONGOCAT_FRAME_HEIGHT = 360;

inline constexpr int BONGOCAT_SVG_FRAME_WIDTH = 500;
inline constexpr int BONGOCAT_SVG_FRAME_HEIGHT = 500;
inline constexpr int BONGOCAT_SVG_FRAME_TX = 0;
inline constexpr int BONGOCAT_SVG_FRAME_TY = 0;
inline constexpr uint32_t BONGOCAT_SVG_ALPHA_MASK = 0x808080FF; // rgba(128,128,128,255)
inline constexpr int BONGOCAT_SVG_FRAME_REAL_CAT_WIDTH = 390;
inline constexpr int BONGOCAT_SVG_FRAME_REAL_CAT_HEIGHT = 216;

inline constexpr size_t BONGOCAT_EMBEDDED_IMAGES_COUNT = animation::BONGOCAT_NUM_FRAMES;
inline constexpr size_t BONGOCAT_ANIMATIONS_COUNT = 1;

BONGOCAT_NODISCARD extern embedded_image_t get_bongocat_sprite(size_t i);
BONGOCAT_NODISCARD extern created_result_t<animation::generic_sprite_sheet_t>
get_bongocat_sprite_sheet(const animation::animation_thread_context_t& ctx, size_t index);

BONGOCAT_NODISCARD extern embedded_image_t get_bongocat_sprite_svg(size_t i);
}  // namespace bongocat::assets

#endif  // BONGOCAT_EMBEDDED_ASSETS_BONGOCAT_H
