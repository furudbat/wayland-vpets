#ifndef BONGOCAT_EMBEDDED_ASSETS_DM_FEATURES_H
#define BONGOCAT_EMBEDDED_ASSETS_DM_FEATURES_H

// feature flags
namespace bongocat::features {

#ifdef FEATURE_ENABLE_DM_EMBEDDED_ASSETS
//  inline static constexpr bool EnableDmEmbeddedAssets = true;
#  ifdef FEATURE_DM_EMBEDDED_ASSETS
  inline static constexpr bool EnableFullDmEmbeddedAssets = true;
#  else
  inline static constexpr bool EnableFullDmEmbeddedAssets = false;
#  endif
#else
  inline static constexpr bool EnableFullDmEmbeddedAssets = false;
#endif


}  // namespace features

#endif