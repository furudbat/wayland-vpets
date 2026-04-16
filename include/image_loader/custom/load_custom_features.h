#pragma once

// feature flags
namespace bongocat::features {
#ifdef FEATURE_CUSTOM_SPRITE_SHEETS
inline static constexpr bool EnableCustomSpriteSheetsAssets = true;
#else
inline static constexpr bool EnableCustomSpriteSheetsAssets = false;
#endif
}  // namespace features
