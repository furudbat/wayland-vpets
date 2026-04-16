#ifndef BONGOCAT_EMBEDDED_ASSETS_PEN20_FEATURES_H
#define BONGOCAT_EMBEDDED_ASSETS_PEN20_FEATURES_H

// feature flags
namespace bongocat::features {

#ifdef FEATURE_ENABLE_DM_EMBEDDED_ASSETS
#  ifdef FEATURE_PEN20_EMBEDDED_ASSETS
  inline static constexpr bool EnablePen20EmbeddedAssets = true;
#  else
  inline static constexpr bool EnablePen20EmbeddedAssets = false;
#  endif
#else
  inline static constexpr bool EnablePen20EmbeddedAssets = false;
#endif

}  // namespace features

#endif