#ifndef BONGOCAT_EMBEDDED_ASSETS_BONGOCAT_FEATURES_H
#define BONGOCAT_EMBEDDED_ASSETS_BONGOCAT_FEATURES_H

// feature flags
namespace bongocat::features {

#ifdef FEATURE_BONGOCAT_EMBEDDED_ASSETS
  inline static constexpr bool EnableBongocatEmbeddedAssets = true;
#  ifdef FEATURE_USE_BONGOCAT_SVG
  inline static constexpr bool EnableBongocatSvg = true;
#  else
  inline static constexpr bool EnableBongocatSvg = false;
#  endif
#else
  inline static constexpr bool EnableBongocatEmbeddedAssets = false;
  inline static constexpr bool EnableBongocatSvg = false;
#endif

}  // namespace features

#endif