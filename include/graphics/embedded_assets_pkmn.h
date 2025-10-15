#ifndef BONGOCAT_EMBEDDED_ASSETS_PKMN_INDEX_H
#define BONGOCAT_EMBEDDED_ASSETS_PKMN_INDEX_H

#include <cstddef>

/// pkmn
#ifdef FEATURE_PKMN_EMBEDDED_ASSETS
#include "embedded_assets/pkmn/pkmn.hpp"
#else
namespace bongocat::assets {
    inline static constexpr size_t PKMN_ANIM_COUNT = 0;
}
#endif


namespace bongocat::assets {
    inline static constexpr size_t PKMN_ANIMATIONS_COUNT = PKMN_ANIM_COUNT;
}

namespace bongocat::assets {
    static inline constexpr int PKMN_FRAME_IDLE1     = 0;
    static inline constexpr int PKMN_FRAME_IDLE2     = 1;
    inline static constexpr size_t PKMN_SPRITE_SHEET_ROW = 0;

    inline static constexpr size_t PKMN_SPRITE_SHEET_COLS = 2;
    inline static constexpr size_t PKMN_SPRITE_SHEET_ROWS = 1;
}

#endif