#ifndef BONGOCAT_EMBEDDED_ASSETS_MS_AGENT_FEATURES_H
#define BONGOCAT_EMBEDDED_ASSETS_MS_AGENT_FEATURES_H

// feature flags
namespace bongocat::features {

#ifdef FEATURE_MS_AGENT_EMBEDDED_ASSETS
inline static constexpr bool EnableMsAgentEmbeddedAssets = true;
#else
inline static constexpr bool EnableMsAgentEmbeddedAssets = false;
#endif

}  // namespace features

#endif