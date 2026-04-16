#ifndef BONGOCAT_EMBEDDED_ASSETS_DMC_FEATURES_H
#define BONGOCAT_EMBEDDED_ASSETS_DMC_FEATURES_H

// feature flags
namespace bongocat::features {

#ifdef FEATURE_ENABLE_DM_EMBEDDED_ASSETS
#  ifdef FEATURE_DMC_EMBEDDED_ASSETS
  inline static constexpr bool EnableDmcEmbeddedAssets = true;
#  else
  inline static constexpr bool EnableDmcEmbeddedAssets = false;
#  endif
#else
  inline static constexpr bool EnableDmcEmbeddedAssets = false;
#endif

}  // namespace features

#endif