#ifndef BONGOCAT_EMBEDDED_ASSETS_PMD_SPRITE_H
#define BONGOCAT_EMBEDDED_ASSETS_PMD_SPRITE_H

#include "embedded_assets/embedded_image.h"

namespace bongocat::assets {
    BONGOCAT_NODISCARD extern embedded_image_t get_pmd_sprite_sheet(size_t i);
    BONGOCAT_NODISCARD extern custom_animation_settings_t get_pmd_sprite_sheet_settings(size_t i);
}

#endif

