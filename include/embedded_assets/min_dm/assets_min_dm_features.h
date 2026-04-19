#ifndef BONGOCAT_EMBEDDED_ASSETS_MIN_DM_FEATURES_H
#define BONGOCAT_EMBEDDED_ASSETS_MIN_DM_FEATURES_H

// feature flags
namespace bongocat::features {

#ifdef FEATURE_ENABLE_DM_EMBEDDED_ASSETS
  inline static constexpr bool EnableDmEmbeddedAssets = true;
#  if !defined(FEATURE_DM_EMBEDDED_ASSETS) && !defined(FEATURE_DM20_EMBEDDED_ASSETS) && \
      !defined(FEATURE_DMC_EMBEDDED_ASSETS) && !defined(FEATURE_DMX_EMBEDDED_ASSETS) && \
      !defined(FEATURE_PEN20_EMBEDDED_ASSETS) && !defined(FEATURE_DMALL_EMBEDDED_ASSETS)
  inline static constexpr bool EnableMinDmEmbeddedAssets = true;
#  else
  inline static constexpr bool EnableMinDmEmbeddedAssets = false;
#  endif
#else
  inline static constexpr bool EnableMinDmEmbeddedAssets = false;
#endif
}  // namespace features

#endif