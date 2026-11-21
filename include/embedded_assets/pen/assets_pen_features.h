#ifndef BONGOCAT_EMBEDDED_ASSETS_PEN_FEATURES_H
#define BONGOCAT_EMBEDDED_ASSETS_PEN_FEATURES_H

// feature flags
namespace bongocat::features {

#ifdef FEATURE_ENABLE_DM_EMBEDDED_ASSETS
#  ifdef FEATURE_PEN_EMBEDDED_ASSETS
  static constexpr bool EnablePenEmbeddedAssets = true;
#  else
  static constexpr bool EnablePenEmbeddedAssets = false;
#  endif
#else
  static constexpr bool EnablePenEmbeddedAssets = false;
#endif

}  // namespace features

#endif