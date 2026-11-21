#ifndef BONGOCAT_EMBEDDED_ASSETS_PMD_FEATURES_H
#define BONGOCAT_EMBEDDED_ASSETS_PMD_FEATURES_H

// feature flags
namespace bongocat::features {

#ifdef FEATURE_PMD_EMBEDDED_ASSETS
static constexpr bool EnablePmdEmbeddedAssets = true;
#else
static constexpr bool EnablePmdEmbeddedAssets = false;
#endif

}  // namespace features

#endif