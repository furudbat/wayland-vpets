#ifndef BONGOCAT_EMBEDDED_ASSETS_DMX_FEATURES_H
#define BONGOCAT_EMBEDDED_ASSETS_DMX_FEATURES_H

// feature flags
namespace bongocat::features {

#ifdef FEATURE_ENABLE_DM_EMBEDDED_ASSETS
#  ifdef FEATURE_DMX_EMBEDDED_ASSETS
  inline static constexpr bool EnableDmxEmbeddedAssets = true;
#  else
  inline static constexpr bool EnableDmxEmbeddedAssets = false;
#  endif
#else
  inline static constexpr bool EnableDmxEmbeddedAssets = false;
#endif

}  // namespace features

#endif