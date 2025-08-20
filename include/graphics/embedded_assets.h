#ifndef BONGOCAT_EMBEDDED_ASSETS_H
#define BONGOCAT_EMBEDDED_ASSETS_H

#include "sprite_sheet.h"
#include <cstddef>

#include "embedded_assets_bongocat.h"
#include "embedded_assets_digimon.h"
#include "embedded_assets_clippy.h"

namespace bongocat::assets {
    inline static constexpr size_t ANIMS_COUNT = BONGOCAT_ANIMATIONS_COUNT+DIGIMON_ANIMATIONS_COUNT;
    inline static constexpr size_t MS_PETS_COUNT = MS_PETS_ANIMATIONS_COUNT;
}

#endif // BONGOCAT_EMBEDDED_ASSETS_H
