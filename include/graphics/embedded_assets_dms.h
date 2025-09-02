#ifndef BONGOCAT_EMBEDDED_ASSETS_DMS_H
#define BONGOCAT_EMBEDDED_ASSETS_DMS_H

#include "embedded_image.h"

#ifdef FEATURE_ENABLE_DM_EMBEDDED_ASSETS
#if !defined(FEATURE_DM_EMBEDDED_ASSETS) && !defined(FEATURE_DM20_EMBEDDED_ASSETS) && !defined(FEATURE_DMC_EMBEDDED_ASSETS) && !defined(FEATURE_DMX_EMBEDDED_ASSETS) && !defined(FEATURE_PEN20_EMBEDDED_ASSETS)
// Fallback dm (minimal set)
#ifndef FEATURE_MIN_DM_EMBEDDED_ASSETS
#define FEATURE_MIN_DM_EMBEDDED_ASSETS
#endif
// DM_ANIM_START_INDEX is defined in embedded_assets.h
#include "embedded_assets/min_dm.hpp"
namespace bongocat::assets {
    inline static constexpr size_t DM_ANIMATIONS_COUNT = DM_ANIM_COUNT;

    extern embedded_image_t get_min_dm_sprite_sheet(size_t i);
}

// feature full assets
#else

/// @NOTE: keep order in mind and double check _START_INDEX of the next set: dm, dm20, pen20, dmx, dmc
/// see config.cpp, some names can exist in other sets and can be overwritten from the next set

/// dm
#ifdef FEATURE_DM_EMBEDDED_ASSETS
// DM_ANIM_START_INDEX is defined in embedded_assets.h
#include "embedded_assets/dm.hpp"
namespace bongocat::assets {
    extern embedded_image_t get_dm_sprite_sheet(size_t i);
}
#else
namespace bongocat::assets {
    inline static constexpr size_t DM_ANIM_COUNT = 0;
}
#endif

/// dm20
#ifdef FEATURE_DM20_EMBEDDED_ASSETS
namespace bongocat::assets {
    inline static constexpr size_t DM20_ANIM_START_INDEX = DM_ANIM_START_INDEX+DM_ANIM_COUNT;
}
#include "embedded_assets/dm20.hpp"
namespace bongocat::assets {
    extern embedded_image_t get_dm20_sprite_sheet(size_t i);
}
#else
namespace bongocat::assets {
    inline static constexpr size_t DM20_ANIM_START_INDEX = DM_ANIM_START_INDEX+DM_ANIM_COUNT;
    inline static constexpr size_t DM20_ANIM_COUNT = 0;
}
#endif

/// pen20
#ifdef FEATURE_PEN20_EMBEDDED_ASSETS
namespace bongocat::assets {
    inline static constexpr size_t PEN20_ANIM_START_INDEX = DM20_ANIM_START_INDEX+DM20_ANIM_COUNT;
}
#include "embedded_assets/pen20.h"
namespace bongocat::assets {
    extern embedded_image_t get_pen20_sprite_sheet(size_t i);
}
#else
namespace bongocat::assets {
    inline static constexpr size_t PEN20_ANIM_START_INDEX = DM20_ANIM_START_INDEX+DM20_ANIM_COUNT;
    inline static constexpr size_t PEN20_ANIM_COUNT = 0;
}
#endif

/// dmx
#ifdef FEATURE_DMX_EMBEDDED_ASSETS
namespace bongocat::assets {
    inline static constexpr size_t DMX_ANIM_START_INDEX = PEN20_ANIM_START_INDEX+PEN20_ANIM_COUNT;
}
#include "embedded_assets/dmx.hpp"
namespace bongocat::assets {
    extern embedded_image_t get_dmx_sprite_sheet(size_t i);
}
#else
namespace bongocat::assets {
    inline static constexpr size_t DMX_ANIM_START_INDEX = PEN20_ANIM_START_INDEX+PEN20_ANIM_COUNT;
    inline static constexpr size_t DMX_ANIM_COUNT = 0;
}
#endif

/// dmc
#ifdef FEATURE_DMC_EMBEDDED_ASSETS
namespace bongocat::assets {
    inline static constexpr size_t DMC_ANIM_START_INDEX = DMX_ANIM_START_INDEX+DMX_ANIM_COUNT;
}
#include "embedded_assets/dmc.hpp"
namespace bongocat::assets {
    extern embedded_image_t get_dmc_sprite_sheet(size_t i);
}
#else
namespace bongocat::assets {
    inline static constexpr size_t DMC_ANIM_START_INDEX = DMX_ANIM_START_INDEX+DMX_ANIM_COUNT;
    inline static constexpr size_t DMC_ANIM_COUNT = 0;
}
#endif

namespace bongocat::assets {
    inline static constexpr size_t DM_ANIMATIONS_COUNT = DM_ANIM_COUNT+DM20_ANIM_COUNT+PEN20_ANIM_COUNT+DMX_ANIM_COUNT+DMC_ANIM_COUNT;
}
#endif
#endif

namespace bongocat::assets {
#ifdef FEATURE_ENABLE_DM_EMBEDDED_ASSETS
    static inline constexpr int DM_FRAME_IDLE1     = 0;
    static inline constexpr int DM_FRAME_IDLE2     = 1;
    static inline constexpr int DM_FRAME_ANGRY     = 2;  // Angry/Refuse or Hit (Fallback), Eat Frame Fallback
    static inline constexpr int DM_FRAME_DOWN1     = 3;  // Sleep/Discipline Fallback
    static inline constexpr int DM_FRAME_HAPPY     = 4;
    static inline constexpr int DM_FRAME_EAT1      = 5;
    static inline constexpr int DM_FRAME_SLEEP1    = 6;
    static inline constexpr int DM_FRAME_REFUSE    = 7;
    static inline constexpr int DM_FRAME_SAD       = 8;

    // Optional frames
    static inline constexpr int DM_FRAME_DOWN2     = 9;
    static inline constexpr int DM_FRAME_EAT2      = 10;
    static inline constexpr int DM_FRAME_SLEEP2    = 11;
    static inline constexpr int DM_FRAME_ATTACK    = 12;

    static inline constexpr int DM_FRAME_MOVEMENT1 = 13;
    static inline constexpr int DM_FRAME_MOVEMENT2 = 14;

    static inline constexpr int DM_HAPPY_CHANCE_PERCENT = 60;

    inline static constexpr size_t DM_SPRITE_SHEET_ROWS = 1;
#endif
}

#endif