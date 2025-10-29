#ifndef MISC_EMBEDDED_ASSETS_HPP
#define MISC_EMBEDDED_ASSETS_HPP

#include <cstddef>
#include "embedded_assets/custom/custom_sprite.h"

namespace bongocat::assets {
    // neko
    inline static constexpr char MISC_NEKO_FQID_ARR[] = "misc:neko";
    inline static constexpr const char* MISC_NEKO_FQID = MISC_NEKO_FQID_ARR;
    inline static constexpr std::size_t MISC_NEKO_FQID_LEN = sizeof(MISC_NEKO_FQID_ARR)-1;
    inline static constexpr char MISC_NEKO_ID_ARR[] = "neko";
    inline static constexpr const char* MISC_NEKO_ID = MISC_NEKO_ID_ARR;
    inline static constexpr std::size_t MISC_NEKO_ID_LEN = sizeof(MISC_NEKO_ID_ARR)-1;
    inline static constexpr char MISC_NEKO_NAME_ARR[] = "neko";
    inline static constexpr const char* MISC_NEKO_NAME = MISC_NEKO_NAME_ARR;
    inline static constexpr std::size_t MISC_NEKO_NAME_LEN = sizeof(MISC_NEKO_NAME_ARR)-1;
    inline static constexpr char MISC_NEKO_FQNAME_ARR[] = "misc:neko";
    inline static constexpr const char* MISC_NEKO_FQNAME = MISC_NEKO_FQNAME_ARR;
    inline static constexpr std::size_t MISC_NEKO_FQNAME_LEN = sizeof(MISC_NEKO_FQNAME_ARR)-1;
    inline static constexpr std::size_t MISC_NEKO_ANIM_INDEX = 0;
    inline static constexpr custom_animation_columns_t MISC_NEKO_SPRITE_SHEET_SETTINGS {
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
    // custom sprite sheet (at run time)
    inline static constexpr std::size_t CUSTOM_ANIM_INDEX = 1;

    inline static constexpr std::size_t MISC_ANIM_COUNT = 2;
    // +1 for custom sprite sheet as placeholder
    inline static constexpr size_t MISC_MAX_SPRITE_SHEET_COL_FRAMES = 2;
}

#endif // MISC_EMBEDDED_ASSETS_HPP