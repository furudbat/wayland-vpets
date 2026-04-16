#ifndef BONGOCAT_EMBEDDED_ASSETS_PEN_FEATURES_H
#define BONGOCAT_EMBEDDED_ASSETS_PEN_FEATURES_H

// feature flags
namespace bongocat::features {

#ifdef FEATURE_ENABLE_DM_EMBEDDED_ASSETS
#  ifdef FEATURE_PEN_EMBEDDED_ASSETS
  inline static constexpr bool EnablePenEmbeddedAssets = true;
#  else
  inline static constexpr bool EnablePenEmbeddedAssets = false;
#  endif
#else
  inline static constexpr bool EnablePenEmbeddedAssets = false;
#endif

}  // namespace features

#endif