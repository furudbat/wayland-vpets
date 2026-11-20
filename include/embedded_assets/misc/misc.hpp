#ifndef MISC_EMBEDDED_ASSETS_HPP
#define MISC_EMBEDDED_ASSETS_HPP

#include "embedded_assets/assets.h"
#include "embedded_assets/custom/custom_sprite_settings.h"

#include <cstddef>

// misc
#define ASSETS_MISC_SPRITE_SETTINGS_SECTION(name) BONGOCAT_ASSETS_SET_SECTION_FOR(misc, "sprite_settings", name)
#define ASSETS_MISC_DIMS_SECTION(name) BONGOCAT_ASSETS_SET_SECTION_FOR(misc, "dims", name)
//#define ASSETS_MISC_EVOL_DATA_SECTION BONGOCAT_ASSETS_SET_SECTION(misc, "evol_data")

namespace bongocat::assets {
// neko
inline constexpr char MISC_NEKO_FQID_ARR[] CONFIG_STRING_SECTION(MISC_NEKO_FQID_ARR) = "misc:neko";
inline constexpr const char *MISC_NEKO_FQID = MISC_NEKO_FQID_ARR;
inline constexpr std::size_t MISC_NEKO_FQID_LEN = sizeof(MISC_NEKO_FQID_ARR) - 1;
inline constexpr char MISC_NEKO_ID_ARR[] CONFIG_STRING_SECTION(MISC_NEKO_ID_ARR) = "neko";
inline constexpr const char *MISC_NEKO_ID = MISC_NEKO_ID_ARR;
inline constexpr std::size_t MISC_NEKO_ID_LEN = sizeof(MISC_NEKO_ID_ARR) - 1;
inline constexpr char MISC_NEKO_NAME_ARR[] CONFIG_STRING_SECTION(MISC_NEKO_NAME_ARR) = "neko";
inline constexpr const char *MISC_NEKO_NAME = MISC_NEKO_NAME_ARR;
inline constexpr std::size_t MISC_NEKO_NAME_LEN = sizeof(MISC_NEKO_NAME_ARR) - 1;
inline constexpr char MISC_NEKO_FQNAME_ARR[] CONFIG_STRING_SECTION(MISC_NEKO_FQNAME_ARR) = "misc:neko";
inline constexpr const char *MISC_NEKO_FQNAME = MISC_NEKO_FQNAME_ARR;
inline constexpr std::size_t MISC_NEKO_FQNAME_LEN = sizeof(MISC_NEKO_FQNAME_ARR) - 1;
inline constexpr std::size_t MISC_NEKO_ANIM_INDEX = 0;
inline constexpr custom_animation_settings_t MISC_NEKO_SPRITE_SHEET_SETTINGS ASSETS_MISC_SPRITE_SETTINGS_SECTION(MISC_NEKO_SPRITE_SHEET_SETTINGS) = {
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
inline constexpr int MISC_NEKO_SPRITE_SHEET_ROWS ASSETS_MISC_DIMS_SECTION(MISC_NEKO_SPRITE_SHEET_ROWS) = 9;
inline constexpr int MISC_NEKO_SPRITE_SHEET_MAX_COLS ASSETS_MISC_DIMS_SECTION(MISC_NEKO_SPRITE_SHEET_MAX_COLS) = 2;

inline constexpr std::size_t MAX_MISC_ANIM_INDEX = 0;
inline constexpr std::size_t MISC_ANIM_COUNT = 1;

inline constexpr size_t MISC_MAX_SPRITE_SHEET_COL_FRAMES = 2;
}  // namespace bongocat::assets

#endif  // MISC_EMBEDDED_ASSETS_HPP