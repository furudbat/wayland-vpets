#ifndef BONGOCAT_EMBEDDED_ASSETS_H
#define BONGOCAT_EMBEDDED_ASSETS_H

#include "sprite_sheet.h"
#include <cstddef>

#ifdef FEATURE_BONGOCAT_EMBEDDED_ASSETS
namespace bongocat::assets {
    // sprite sheet uses it own array
    inline static constexpr size_t BONGOCAT_ANIM_START_INDEX  = 0;
}
#include "embedded_assets_bongocat.h"
#else
namespace bongocat::assets {
    inline static constexpr size_t BONGOCAT_ANIM_START_INDEX  = 0;
    inline static constexpr size_t BONGOCAT_ANIMATIONS_COUNT  = 0;
}
#endif

#ifdef FEATURE_DIGIMON_EMBEDDED_ASSETS
namespace bongocat::assets {
    // sprite sheet uses it own array
    inline static constexpr size_t DM_ANIM_START_INDEX        = 0;
}
#include "embedded_assets_digimon.h"
#else
namespace bongocat::assets {
    inline static constexpr size_t DM_ANIM_START_INDEX        = 0;
    inline static constexpr size_t DIGIMON_ANIMATIONS_COUNT   = 0;
}
#endif

#ifdef FEATURE_CLIPPY_EMBEDDED_ASSETS
namespace bongocat::assets {
    // sprite sheet uses it own array
    inline static constexpr size_t MS_PETS_ANIM_START_INDEX   = 0;
}
#include "embedded_assets_clippy.h"
#else
namespace bongocat::assets {
    inline static constexpr size_t MS_PETS_ANIM_START_INDEX   = 0;
    inline static constexpr size_t MS_PETS_ANIMATIONS_COUNT   = 0;
}
#endif

#endif // BONGOCAT_EMBEDDED_ASSETS_H
