#ifndef BONGOCAT_EMBEDDED_ASSETS_H
#define BONGOCAT_EMBEDDED_ASSETS_H

#include <cstdint>
#include <cstddef>

#include "sprite_sheet.h"

#ifndef FEATURE_INCLUDE_ONLY_BONGOCAT_EMBEDDED_ASSETS
#ifdef FEATURE_INCLUDE_DM_EMBEDDED_ASSETS
#include "embedded_assets/dm.h"
#else
//#define DM_ANIM_COUNT 0
#include "embedded_assets/min_dm.hpp"
#endif
namespace bongocat::assets {
    inline static constexpr size_t DM_ANIM_START_INDEX  = 0;
}

#ifdef FEATURE_INCLUDE_DM20_EMBEDDED_ASSETS
#include "embedded_assets/dm20.h"
#else
namespace bongocat::assets {
    inline static constexpr size_t DM20_ANIM_COUNT = 0;
}
#endif
namespace bongocat::assets {
    inline static constexpr size_t DM20_ANIM_START_INDEX = DM_ANIM_START_INDEX+DM_ANIM_COUNT;
}

#ifdef FEATURE_INCLUDE_DMC_EMBEDDED_ASSETS
#include "embedded_assets/dmc.h"
#else
namespace bongocat::assets {
    inline static constexpr size_t DMC_ANIM_COUNT = 0;
}
#endif
namespace bongocat::assets {
    inline static constexpr size_t DMC_ANIM_START_INDEX = DM20_ANIM_START_INDEX+DM20_ANIM_COUNT;
}

#ifdef FEATURE_INCLUDE_DMX_EMBEDDED_ASSETS
#include "embedded_assets/dmx.h"
#else
namespace bongocat::assets {
    inline static constexpr size_t DMX_ANIM_COUNT = 0;
}
#endif
namespace bongocat::assets {
    inline static constexpr size_t DMX_ANIM_START_INDEX = DMC_ANIM_START_INDEX+DMC_ANIM_COUNT;
}

#ifdef FEATURE_INCLUDE_PEN20_EMBEDDED_ASSETS
#include "embedded_assets/pen20.h"
#else
namespace bongocat::assets {
    inline static constexpr size_t PEN20_ANIM_COUNT = 0;
}
#endif
namespace bongocat::assets {
    inline static constexpr size_t PEN20_ANIM_START_INDEX = DMX_ANIM_START_INDEX+DMX_ANIM_COUNT;
}

namespace bongocat::assets {
    inline static constexpr size_t DIGIMON_ANIMATIONS_COUNT = DM_ANIM_COUNT+DM20_ANIM_COUNT+DMC_ANIM_COUNT+DMX_ANIM_COUNT+PEN20_ANIM_COUNT;
}
#else
namespace bongocat::assets {
    inline static constexpr size_t DIGIMON_ANIMATIONS_COUNT = 0;
}
#endif
namespace bongocat::assets {
    inline static constexpr size_t ANIMS_COUNT = 1+DIGIMON_ANIMATIONS_COUNT;
}


namespace bongocat::assets::details {
    struct embedded_image_t {
        const unsigned char *data{nullptr};
        size_t size{0};
        const char *name{""};
    };

    inline static constexpr size_t BONGOCAT_EMBEDDED_IMAGES_COUNT = animation::BONGOCAT_NUM_FRAMES;
    extern const embedded_image_t* bongocat_embedded_images;

#ifndef FEATURE_INCLUDE_ONLY_BONGOCAT_EMBEDDED_ASSETS
    static inline constexpr size_t DIGIMON_SPRITE_SHEET_EMBEDDED_IMAGES_COUNT = (1+DIGIMON_ANIMATIONS_COUNT);
    extern const embedded_image_t* digimon_sprite_sheet_embedded_images;
#endif
}

#endif // BONGOCAT_EMBEDDED_ASSETS_H
