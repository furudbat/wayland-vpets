#ifndef BONGOCAT_EMBEDDED_ASSETS_DMX_FEATURES_H
#define BONGOCAT_EMBEDDED_ASSETS_DMX_FEATURES_H

// feature flags
namespace bongocat::features {

#ifdef FEATURE_ENABLE_DM_EMBEDDED_ASSETS
#  ifdef FEATURE_DMX_EMBEDDED_ASSETS
  static constexpr bool EnableDmxEmbeddedAssets = true;
#  else
  static constexpr bool EnableDmxEmbeddedAssets = false;
#  endif
#else
  static constexpr bool EnableDmxEmbeddedAssets = false;
#endif

}  // namespace features

#endif