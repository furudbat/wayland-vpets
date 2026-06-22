#ifndef MISC_EMBEDDED_ASSETS_HPP
#define MISC_EMBEDDED_ASSETS_HPP

#include "embedded_assets/custom/custom_sprite.h"

#include <cstddef>

namespace bongocat::assets {
// neko
inline static constexpr char MISC_NEKO_FQID_ARR[] CONFIG_STRING_SECTION = "misc:neko";
inline static constexpr const char *MISC_NEKO_FQID CONFIG_STRING_REF_SECTION = MISC_NEKO_FQID_ARR;
inline static constexpr std::size_t MISC_NEKO_FQID_LEN CONFIG_STRING_SECTION = sizeof(MISC_NEKO_FQID_ARR) - 1;
inline static constexpr char MISC_NEKO_ID_ARR[] CONFIG_STRING_SECTION = "neko";
inline static constexpr const char *MISC_NEKO_ID CONFIG_STRING_REF_SECTION = MISC_NEKO_ID_ARR;
inline static constexpr std::size_t MISC_NEKO_ID_LEN CONFIG_STRING_SECTION = sizeof(MISC_NEKO_ID_ARR) - 1;
inline static constexpr char MISC_NEKO_NAME_ARR[] CONFIG_STRING_SECTION = "neko";
inline static constexpr const char *MISC_NEKO_NAME CONFIG_STRING_REF_SECTION = MISC_NEKO_NAME_ARR;
inline static constexpr std::size_t MISC_NEKO_NAME_LEN CONFIG_STRING_SECTION = sizeof(MISC_NEKO_NAME_ARR) - 1;
inline static constexpr char MISC_NEKO_FQNAME_ARR[] CONFIG_STRING_SECTION = "misc:neko";
inline static constexpr const char *MISC_NEKO_FQNAME CONFIG_STRING_REF_SECTION = MISC_NEKO_FQNAME_ARR;
inline static constexpr std::size_t MISC_NEKO_FQNAME_LEN CONFIG_STRING_SECTION = sizeof(MISC_NEKO_FQNAME_ARR) - 1;
inline static constexpr std::size_t MISC_NEKO_ANIM_INDEX ASSETS_INDICES_SECTION = 0;
inline static constexpr custom_animation_settings_t MISC_NEKO_SPRITE_SHEET_SETTINGS ASSETS_SPRITE_SETTINGS_SECTION = {
    .idle_frames = 2,
    .boring_frames = 2,
    .writing_frames = 2,
    .happy_frames = 2,
    .asleep_frames = 2,
    .sleep_frames = 2,
    .wake_up_frames = 1,
    .working_frames = 2,
    .moving_frames = 2,
    .feature_toggle_writing_frames = 1,
};
inline static constexpr std::size_t MISC_NEKO_SPRITE_SHEET_ROWS = 9;
inline static constexpr std::size_t MISC_NEKO_SPRITE_SHEET_MAX_COLS = 2;

inline static constexpr std::size_t MAX_MISC_ANIM_INDEX = 0;
inline static constexpr std::size_t MISC_ANIM_COUNT = 1;
// custom sprite sheet (at run time)
inline static constexpr std::size_t CUSTOM_ANIM_INDEX = 1;

inline static constexpr size_t MISC_MAX_SPRITE_SHEET_COL_FRAMES = 2;
}  // namespace bongocat::assets

#endif  // MISC_EMBEDDED_ASSETS_HPP