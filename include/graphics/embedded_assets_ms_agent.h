#ifndef BONGOCAT_EMBEDDED_ASSETS_MS_AGENT_INDEX_H
#define BONGOCAT_EMBEDDED_ASSETS_MS_AGENT_INDEX_H

#include "../embedded_assets/ms_agent/assets_ms_agent_features.h"

#include <cstddef>

/// ms_agent (clippy, links, rover, merlin)
#ifdef FEATURE_MS_AGENT_EMBEDDED_ASSETS
#  include "embedded_assets/ms_agent/ms_agent.hpp"
#else
namespace bongocat::assets {
inline static constexpr std::size_t MS_AGENTS_ANIM_COUNT = 0;
inline static constexpr std::size_t MS_AGENT_MAX_SPRITE_SHEET_COL_FRAMES = 0;
}  // namespace bongocat::assets
#endif

#endif  // BONGOCAT_EMBEDDED_ASSETS_MS_AGENT_INDEX_H
