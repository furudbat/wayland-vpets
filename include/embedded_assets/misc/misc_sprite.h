#ifndef BONGOCAT_EMBEDDED_ASSETS_MISC_H
#define BONGOCAT_EMBEDDED_ASSETS_MISC_H

#include "embedded_assets/embedded_image.h"

namespace bongocat::assets {
inline static constexpr size_t MISC_SPRITE_SHEET_EMBEDDED_IMAGES_COUNT = 1;
inline static constexpr size_t MISC_ANIMATIONS_COUNT = 1;

[[nodiscard]] extern embedded_image_t get_misc_sprite_sheet(size_t i);
[[nodiscard]] extern custom_animation_settings_t get_misc_sprite_sheet_columns(size_t i);
}  // namespace bongocat::assets

#endif