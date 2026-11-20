#ifndef BONGOCAT_EMBEDDED_ASSETS_DM20_FEATURES_H
#define BONGOCAT_EMBEDDED_ASSETS_DM20_FEATURES_H

// feature flags
namespace bongocat::features {

#ifdef FEATURE_ENABLE_DM_EMBEDDED_ASSETS
#  ifdef FEATURE_DM20_EMBEDDED_ASSETS
  static constexpr bool EnableDm20EmbeddedAssets = true;
#  else
  static constexpr bool EnableDm20EmbeddedAssets = false;
#  endif
#else
  static constexpr bool EnableDm20EmbeddedAssets = false;
#endif

}  // namespace features

#endif