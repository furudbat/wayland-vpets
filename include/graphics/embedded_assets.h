#ifndef BONGOCAT_EMBEDDED_ASSETS_H
#define BONGOCAT_EMBEDDED_ASSETS_H

#include "sprite_sheet.h"
#include "graphics/embedded_assets/bongocat.hpp"
#include <cstddef>

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


namespace bongocat::assets {
    struct embedded_image_t {
        const unsigned char *data{nullptr};
        size_t size{0};
        const char *name{""};
    };

    inline static constexpr size_t BONGOCAT_EMBEDDED_IMAGES_COUNT = animation::BONGOCAT_NUM_FRAMES;
    inline constinit embedded_image_t bongocat_embedded_images[BONGOCAT_EMBEDDED_IMAGES_COUNT] = {
        /*_bongocat_embedded_images[BONGOCAT_FRAME_BOTH_UP] = */{bongo_cat_both_up_png, bongo_cat_both_up_png_size, "embedded bongo-cat-both-up.png"},
        /*_bongocat_embedded_images[BONGOCAT_FRAME_LEFT_DOWN] = */{bongo_cat_left_down_png, bongo_cat_left_down_png_size, "embedded bongo-cat-left-down.png"},
        /*_bongocat_embedded_images[BONGOCAT_FRAME_RIGHT_DOWN] = */{bongo_cat_right_down_png, bongo_cat_right_down_png_size, "embedded bongo-cat-right-down.png"},
        /*_bongocat_embedded_images[BONGOCAT_FRAME_BOTH_DOWN] = */{bongo_cat_both_down_png, bongo_cat_both_down_png_size, "embedded bongo-cat-both-down.png"},
    };

#ifndef FEATURE_INCLUDE_ONLY_BONGOCAT_EMBEDDED_ASSETS
    static inline constexpr size_t DIGIMON_SPRITE_SHEET_EMBEDDED_IMAGES_COUNT = (1+DIGIMON_ANIMATIONS_COUNT);
    inline constinit embedded_image_t digimon_sprite_sheet_embedded_images[DIGIMON_SPRITE_SHEET_EMBEDDED_IMAGES_COUNT] = {
        // index 0 is reserved for bongocat, no sprite sheet exists
        {nullptr, 0, "bongocat.png"},
#ifdef FEATURE_INCLUDE_DM_EMBEDDED_ASSETS
    /// @TODO: add full assets
#else
    //{dm_agumon_png, dm_agumon_png_size, "embedded agumon"},
#include "../../src/graphics/embedded_assets/min_dm_digimon_embedded_images_array.cpp.inl"
    /// @TODO: index more digimons here
#endif
    };
#endif
}

#endif // BONGOCAT_EMBEDDED_ASSETS_H
