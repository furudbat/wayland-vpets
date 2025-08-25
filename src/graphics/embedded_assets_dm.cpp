#include "graphics/embedded_assets.h"
#include "graphics/sprite_sheet.h"

// dm
#ifdef FEATURE_DM_EMBEDDED_ASSETS
#include "graphics/embedded_assets/dm_images.h"
#endif

// dm20
#ifdef FEATURE_INCLUDE_DM20_EMBEDDED_ASSETS
#include "graphics/embedded_assets/dm20_images.h"
#endif

// dmc
#ifdef FEATURE_INCLUDE_DMC_EMBEDDED_ASSETS
#include "graphics/embedded_assets/dmc_images.h"
#endif

// dmx
#ifdef FEATURE_INCLUDE_DMX_EMBEDDED_ASSETS
#include "graphics/embedded_assets/dmx_images.h"
#endif

// pen20
#ifdef FEATURE_INCLUDE_PEN20_EMBEDDED_ASSETS
#include "graphics/embedded_assets/pen20_images.h"
#endif

// Fallback
#ifdef FEATURE_MIN_DM_EMBEDDED_ASSETS
#include "graphics/embedded_assets/min_dm_images.h"
#endif

namespace bongocat::assets {
#ifdef FEATURE_DM_EMBEDDED_ASSETS
#include "embedded_assets/dm_get_sprite_sheet.cpp.inl"
#endif

#ifdef FEATURE_DM20_EMBEDDED_ASSETS
#include "embedded_assets/dm20_get_sprite_sheet.cpp.inl"
#endif

#ifdef FEATURE_DMC_EMBEDDED_ASSETS
#include "embedded_assets/dmc_get_sprite_sheet.cpp.inl"
#endif

#ifdef FEATURE_DMX_EMBEDDED_ASSETS
#include "embedded_assets/dmx_get_sprite_sheet.cpp.inl"
#endif

#ifdef FEATURE_PEN20_EMBEDDED_ASSETS
#include "embedded_assets/pen20_get_sprite_sheet.cpp.inl"
#endif

// Fallback for dm (minimal set)
#ifdef FEATURE_MIN_DM_EMBEDDED_ASSETS
#include "embedded_assets/min_dm_get_sprite_sheet.cpp.inl"
#endif
}