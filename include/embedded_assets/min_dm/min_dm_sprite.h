#ifndef BONGOCAT_EMBEDDED_ASSETS_MIN_DM_H
#define BONGOCAT_EMBEDDED_ASSETS_MIN_DM_H

#include "embedded_assets/embedded_image.h"

namespace bongocat::assets {
[[nodiscard]] extern embedded_image_t get_min_dm_sprite_sheet(size_t i);
}

#endif