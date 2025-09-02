#include "graphics/embedded_assets.h"
#include "graphics/sprite_sheet.h"

/// @TODO: split file into more units, better usage in CMake build

// Fallback for dm (minimal set, Version 1) (images)
#ifdef FEATURE_MIN_DM_EMBEDDED_ASSETS
#include "graphics/embedded_assets/min_dm_images.h"
#endif

// dm (images)
#ifdef FEATURE_DM_EMBEDDED_ASSETS
#include "graphics/embedded_assets/dm_images.h"
#endif

// dm20 (images)
#ifdef FEATURE_DM20_EMBEDDED_ASSETS
#include "graphics/embedded_assets/dm20_images.h"
#endif

// pen20 (images)
#ifdef FEATURE_PEN20_EMBEDDED_ASSETS
#include "graphics/embedded_assets/pen20_images.h"
#endif

// dmx (images)
#ifdef FEATURE_DMX_EMBEDDED_ASSETS
#include "graphics/embedded_assets/dmx_images.h"
#endif

// dmc (images)
#ifdef FEATURE_DMC_EMBEDDED_ASSETS
#include "graphics/embedded_assets/dmc_images.h"
#endif

namespace bongocat::assets {

// Fallback for dm (minimal set, Version 1)
#ifdef FEATURE_MIN_DM_EMBEDDED_ASSETS
#include "embedded_assets/min_dm_get_sprite_sheet.cpp.inl"
#endif

#ifdef FEATURE_DM_EMBEDDED_ASSETS
#include "embedded_assets/dm_get_sprite_sheet.cpp.inl"
#endif

#ifdef FEATURE_DM20_EMBEDDED_ASSETS
#include "embedded_assets/dm20_get_sprite_sheet.cpp.inl"
#endif

#ifdef FEATURE_PEN20_EMBEDDED_ASSETS
#include "embedded_assets/pen20_get_sprite_sheet.cpp.inl"
#endif

#ifdef FEATURE_DMX_EMBEDDED_ASSETS
#include "embedded_assets/dmx_get_sprite_sheet.cpp.inl"
#endif

#ifdef FEATURE_DMC_EMBEDDED_ASSETS
#include "embedded_assets/dmc_get_sprite_sheet.cpp.inl"
#endif

}