#ifndef BONGOCAT_EMBEDDED_ASSETS_DMALL_FEATURES_H
#define BONGOCAT_EMBEDDED_ASSETS_DMALL_FEATURES_H

// feature flags
namespace bongocat::features {

#ifdef FEATURE_ENABLE_DM_EMBEDDED_ASSETS
#  ifdef FEATURE_DMALL_EMBEDDED_ASSETS
  inline static constexpr bool EnableDmAllEmbeddedAssets = true;
#  else
  inline static constexpr bool EnableDmAllEmbeddedAssets = false;
#  endif
#else
  inline static constexpr bool EnableDmAllEmbeddedAssets = false;
#endif

}  // namespace features

#endif