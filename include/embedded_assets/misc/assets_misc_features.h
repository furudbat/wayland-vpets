#ifndef BONGOCAT_EMBEDDED_ASSETS_MISC_FEATURES_H
#define BONGOCAT_EMBEDDED_ASSETS_MISC_FEATURES_H

// feature flags
namespace bongocat::features {

#ifdef FEATURE_MISC_EMBEDDED_ASSETS
inline static constexpr bool EnableMiscEmbeddedAssets = true;
#else
inline static constexpr bool EnableMiscEmbeddedAssets = false;
#endif

}  // namespace features

#endif