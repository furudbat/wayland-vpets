#ifndef BONGOCAT_EMBEDDED_ASSETS_MISC_INDEX_H
#define BONGOCAT_EMBEDDED_ASSETS_MISC_INDEX_H

#include "embedded_assets/custom/custom_sprite_settings.h"
#include "embedded_assets/misc/assets_misc_features.h"

#include <cstddef>

/// misc (neko)
#ifdef FEATURE_MISC_EMBEDDED_ASSETS
#  include "embedded_assets/misc/misc.hpp"
#else
namespace bongocat::assets {
inline static constexpr std::size_t MISC_ANIM_COUNT = 0;
inline static constexpr std::size_t MAX_MISC_ANIM_INDEX = 0;
inline static constexpr std::size_t MISC_MAX_SPRITE_SHEET_COL_FRAMES = 0;
}  // namespace bongocat::assets
#endif

#endif  // BONGOCAT_EMBEDDED_ASSETS_MISC_INDEX_H
