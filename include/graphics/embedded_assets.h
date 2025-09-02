#ifndef BONGOCAT_EMBEDDED_ASSETS_H
#define BONGOCAT_EMBEDDED_ASSETS_H

#include "sprite_sheet.h"

#ifdef FEATURE_BONGOCAT_EMBEDDED_ASSETS
#include "embedded_assets_bongocat.h"
#else
namespace bongocat::assets {
    inline static constexpr size_t BONGOCAT_ANIMATIONS_COUNT    = 0;
}
#endif

#ifdef FEATURE_ENABLE_DM_EMBEDDED_ASSETS
#include "embedded_assets_dms.h"
#else
namespace bongocat::assets {
    inline static constexpr size_t DM_ANIMATIONS_COUNT          = 0;
}
#endif

#ifdef FEATURE_MS_AGENT_EMBEDDED_ASSETS
#include "embedded_assets_ms_agents.h"
#else
namespace bongocat::assets {
    inline static constexpr size_t MS_AGENTS_ANIMATIONS_COUNT   = 0;
}
#endif

#endif // BONGOCAT_EMBEDDED_ASSETS_H
