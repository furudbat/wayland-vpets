#ifndef BONGOCAT_EMBEDDED_ASSETS_DMS_H
#define BONGOCAT_EMBEDDED_ASSETS_DMS_H

#include <cstddef>

#if !defined(FEATURE_DM_EMBEDDED_ASSETS) && !defined(FEATURE_DM20_EMBEDDED_ASSETS) && !defined(FEATURE_DMC_EMBEDDED_ASSETS) && !defined(FEATURE_DMX_EMBEDDED_ASSETS) && !defined(FEATURE_PEN_EMBEDDED_ASSETS) && !defined(FEATURE_PEN20_EMBEDDED_ASSETS) && !defined(FEATURE_DMALL_EMBEDDED_ASSETS)
#ifdef FEATURE_ENABLE_DM_EMBEDDED_ASSETS
// Fallback dm (minimal set)
#ifndef FEATURE_MIN_DM_EMBEDDED_ASSETS
#define FEATURE_MIN_DM_EMBEDDED_ASSETS
#endif
#include "embedded_assets/min_dm/min_dm.hpp"
namespace bongocat::assets {
    inline static constexpr size_t DM_ANIM_COUNT = MIN_DM_ANIM_COUNT;
}
#else
namespace bongocat::assets {
    inline static constexpr size_t MIN_DM_ANIM_COUNT = 0;
    inline static constexpr size_t DM_ANIM_COUNT = 0;
}
#endif
namespace bongocat::assets {
    inline static constexpr size_t DM20_ANIM_COUNT = 0;
    inline static constexpr size_t PEN_ANIM_COUNT = 0;
    inline static constexpr size_t PEN20_ANIM_COUNT = 0;
    inline static constexpr size_t DMX_ANIM_COUNT = 0;
    inline static constexpr size_t DMC_ANIM_COUNT = 0;
    inline static constexpr size_t DMALL_ANIM_COUNT = 0;
}

// feature full assets
#else
namespace bongocat::assets {
    inline static constexpr size_t MIN_DM_ANIM_COUNT = 0;
}

/// dm
#ifdef FEATURE_DM_EMBEDDED_ASSETS
#include "embedded_assets/dm/dm.hpp"
#else
namespace bongocat::assets {
    inline static constexpr size_t DM_ANIM_COUNT = 0;
}
#endif

/// dm20
#ifdef FEATURE_DM20_EMBEDDED_ASSETS
#include "embedded_assets/dm20/dm20.hpp"
#else
namespace bongocat::assets {
    inline static constexpr size_t DM20_ANIM_COUNT = 0;
}
#endif

/// pen
#ifdef FEATURE_PEN_EMBEDDED_ASSETS
#include "embedded_assets/pen/pen.hpp"
#else
namespace bongocat::assets {
    inline static constexpr size_t PEN_ANIM_COUNT = 0;
}
#endif

/// pen20
#ifdef FEATURE_PEN20_EMBEDDED_ASSETS
#include "embedded_assets/pen20/pen20.hpp"
#else
namespace bongocat::assets {
    inline static constexpr size_t PEN20_ANIM_COUNT = 0;
}
#endif

/// dmx
#ifdef FEATURE_DMX_EMBEDDED_ASSETS
#include "embedded_assets/dmx/dmx.hpp"
#else
namespace bongocat::assets {
    inline static constexpr size_t DMX_ANIM_COUNT = 0;
}
#endif

/// dmc
#ifdef FEATURE_DMC_EMBEDDED_ASSETS
#include "embedded_assets/dmc/dmc.hpp"
#else
namespace bongocat::assets {
    inline static constexpr size_t DMC_ANIM_COUNT = 0;
}
#endif

/// dmall
#ifdef FEATURE_DMALL_EMBEDDED_ASSETS
#include "embedded_assets/dmall/dmall.hpp"
#else
namespace bongocat::assets {
    inline static constexpr size_t DMALL_ANIM_COUNT = 0;
}
#endif

#endif

namespace bongocat::assets {
    inline static constexpr size_t DM_ANIMATIONS_COUNT = DM_ANIM_COUNT+DM20_ANIM_COUNT+PEN_ANIM_COUNT+PEN20_ANIM_COUNT+DMX_ANIM_COUNT+DMC_ANIM_COUNT+DMALL_ANIM_COUNT;
}

namespace bongocat::assets {
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

    inline static constexpr size_t DM_SPRITE_SHEET_MAX_COLS = 15;
    inline static constexpr size_t DM_SPRITE_SHEET_ROWS = 1;
    inline static constexpr size_t DM_SPRITE_SHEET_ROW = 0;

    static inline constexpr int DM_HAPPY_CHANCE_PERCENT = 60;
}

#endif