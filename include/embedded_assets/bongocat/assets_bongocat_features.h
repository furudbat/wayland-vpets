#ifndef BONGOCAT_EMBEDDED_ASSETS_BONGOCAT_FEATURES_H
#define BONGOCAT_EMBEDDED_ASSETS_BONGOCAT_FEATURES_H

// feature flags
namespace bongocat::features {

#ifdef FEATURE_BONGOCAT_EMBEDDED_ASSETS
  static constexpr bool EnableBongocatEmbeddedAssets = true;
#  ifdef FEATURE_USE_BONGOCAT_SVG
  static constexpr bool EnableBongocatSvg = true;
#  else
  static constexpr bool EnableBongocatSvg = false;
#  endif
#else
  static constexpr bool EnableBongocatEmbeddedAssets = false;
  static constexpr bool EnableBongocatSvg = false;
#endif

}  // namespace features

#endif