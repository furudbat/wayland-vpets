#ifndef BONGOCAT_EMBEDDED_ASSETS_DMALL_FEATURES_H
#define BONGOCAT_EMBEDDED_ASSETS_DMALL_FEATURES_H

// feature flags
namespace bongocat::features {

#ifdef FEATURE_ENABLE_DM_EMBEDDED_ASSETS
#  ifdef FEATURE_DMALL_EMBEDDED_ASSETS
  static constexpr bool EnableDmAllEmbeddedAssets = true;
#  else
  static constexpr bool EnableDmAllEmbeddedAssets = false;
#  endif
#else
  static constexpr bool EnableDmAllEmbeddedAssets = false;
#endif

}  // namespace features

#endif