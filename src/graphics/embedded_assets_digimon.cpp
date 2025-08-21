#include "graphics/embedded_assets.h"
#include "graphics/embedded_assets_digimon.h"
#include "graphics/sprite_sheet.h"

// dm
#ifdef FEATURE_DM_EMBEDDED_ASSETS
#include "graphics/embedded_assets/dm_images.hpp"
#else
#include "graphics/embedded_assets/min_dm_images.hpp"
#endif

// dm20
#ifdef FEATURE_INCLUDE_DM20_EMBEDDED_ASSETS
#include "graphics/embedded_assets/dm20_images.hpp"
#endif

// dmc
#ifdef FEATURE_INCLUDE_DMC_EMBEDDED_ASSETS
#include "graphics/embedded_assets/dmc_images.hpp"
#endif

// dmx
#ifdef FEATURE_INCLUDE_DMX_EMBEDDED_ASSETS
#include "graphics/embedded_assets/dmx_images.hpp"
#endif

// pen20
#ifdef FEATURE_INCLUDE_PEN20_EMBEDDED_ASSETS
#include "graphics/embedded_assets/pen20_images.hpp"
#endif

namespace bongocat::assets {
#ifdef FEATURE_DM_EMBEDDED_ASSETS
#include "embedded_assets/dm_get_sprite_sheet.cpp.inl"
#elifdef FEATURE_DM20_EMBEDDED_ASSETS
#include "embedded_assets/dm20_get_sprite_sheet.cpp.inl"
#elifdef FEATURE_DMC_EMBEDDED_ASSETS
#include "embedded_assets/dmc_get_sprite_sheet.cpp.inl"
#elifdef FEATURE_DMX_EMBEDDED_ASSETS
#include "embedded_assets/dmx_get_sprite_sheet.cpp.inl"
#elifdef FEATURE_PEN20_EMBEDDED_ASSETS
#include "embedded_assets/pen20_get_sprite_sheet.cpp.inl"
#else
// Fallback for digimon
#include "embedded_assets/min_dm_get_sprite_sheet.cpp.inl"
#endif
}