#ifndef BONGOCAT_EMBEDDED_ASSETS_DIGIMON_H
#define BONGOCAT_EMBEDDED_ASSETS_DIGIMON_H

#include "embedded_assets_image.h"
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
    static inline constexpr int DIGIMON_FRAME_IDLE1     = 0;
    static inline constexpr int DIGIMON_FRAME_IDLE2     = 1;
    static inline constexpr int DIGIMON_FRAME_ANGRY     = 2;  // Angry/Refuse or Hit (Fallback), Eat Frame Fallback
    static inline constexpr int DIGIMON_FRAME_DOWN1     = 3;  // Sleep/Discipline Fallback
    static inline constexpr int DIGIMON_FRAME_HAPPY     = 4;
    static inline constexpr int DIGIMON_FRAME_EAT1      = 5;
    static inline constexpr int DIGIMON_FRAME_SLEEP1    = 6;
    static inline constexpr int DIGIMON_FRAME_REFUSE    = 7;
    static inline constexpr int DIGIMON_FRAME_SAD       = 8;

    // Optional frames
    static inline constexpr int DIGIMON_FRAME_DOWN2     = 9;
    static inline constexpr int DIGIMON_FRAME_EAT2      = 10;
    static inline constexpr int DIGIMON_FRAME_SLEEP2    = 11;
    static inline constexpr int DIGIMON_FRAME_ATTACK    = 12;

    static inline constexpr int DIGIMON_FRAME_MOVEMENT1 = 13;
    static inline constexpr int DIGIMON_FRAME_MOVEMENT2 = 14;

    static inline constexpr int HAPPY_CHANCE_PERCENT = 60;

    inline static constexpr size_t DIGIMON_SPRITE_SHEET_ROWS = 1;

    static inline constexpr size_t DIGIMON_SPRITE_SHEET_EMBEDDED_IMAGES_COUNT = (1+DIGIMON_ANIMATIONS_COUNT);

#ifndef FEATURE_INCLUDE_ONLY_BONGOCAT_EMBEDDED_ASSETS
    extern embedded_image_t get_min_dm_sprite_sheet(size_t i);
#endif
}

#endif // BONGOCAT_EMBEDDED_ASSETS_H
