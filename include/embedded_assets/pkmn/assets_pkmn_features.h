#ifndef BONGOCAT_EMBEDDED_ASSETS_PKMN_FEATURES_H
#define BONGOCAT_EMBEDDED_ASSETS_PKMN_FEATURES_H

// feature flags
namespace bongocat::features {

#ifdef FEATURE_PKMN_EMBEDDED_ASSETS
static constexpr bool EnablePkmnEmbeddedAssets = true;
#else
static constexpr bool EnablePkmnEmbeddedAssets = false;
#endif

}  // namespace features

#endif