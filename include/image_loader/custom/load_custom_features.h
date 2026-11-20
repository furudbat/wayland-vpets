#pragma once

// feature flags
namespace bongocat::features {
#ifdef FEATURE_CUSTOM_SPRITE_SHEETS
static constexpr bool EnableCustomSpriteSheetsAssets = true;
#else
static constexpr bool EnableCustomSpriteSheetsAssets = false;
#endif
}  // namespace features
