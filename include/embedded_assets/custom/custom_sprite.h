#ifndef BONGOCAT_EMBEDDED_ASSETS_CUSTOM_SPRITE_H
#define BONGOCAT_EMBEDDED_ASSETS_CUSTOM_SPRITE_H

#include "embedded_assets/embedded_image.h"
#include <cstddef>
#include <cstdint>

namespace bongocat::assets {
    struct custom_animation_columns_t {
        int32_t idle_frames{0};
        
        int32_t boring_frames{0};

        int32_t start_writing_frames{0};
        int32_t writing_frames{0};
        int32_t end_writing_frames{0};
        int32_t happy_frames{0};

        int32_t asleep_frames{0};
        int32_t sleep_frames{0};
        int32_t wake_up_frames{0};

        int32_t start_working_frames{0};
        int32_t working_frames{0};
        int32_t end_working_frames{0};

        int32_t start_moving_frames{0};
        int32_t moving_frames{0};
        int32_t end_moving_frames{0};
    };

    inline static constexpr size_t CUSTOM_SPRITE_SHEET_ROW_IDLE = 0;
    inline static constexpr size_t CUSTOM_SPRITE_SHEET_ROW_BORING = 1;
    inline static constexpr size_t CUSTOM_SPRITE_SHEET_ROW_START_WRITING = 2;
    inline static constexpr size_t CUSTOM_SPRITE_SHEET_ROW_WRITING = 3;
    inline static constexpr size_t CUSTOM_SPRITE_SHEET_ROW_END_WRITING = 4;
    inline static constexpr size_t CUSTOM_SPRITE_SHEET_ROW_HAPPY = 5;
    inline static constexpr size_t CUSTOM_SPRITE_SHEET_ROW_ASLEEP = 6;
    inline static constexpr size_t CUSTOM_SPRITE_SHEET_ROW_SLEEP = 7;
    inline static constexpr size_t CUSTOM_SPRITE_SHEET_ROW_WAKE_UP = 8;
    inline static constexpr size_t CUSTOM_SPRITE_SHEET_ROW_START_WORKING = 9;
    inline static constexpr size_t CUSTOM_SPRITE_SHEET_ROW_WORKING = 10;
    inline static constexpr size_t CUSTOM_SPRITE_SHEET_ROW_END_WORKING = 11;
    inline static constexpr size_t CUSTOM_SPRITE_SHEET_ROW_START_MOVING = 12;
    inline static constexpr size_t CUSTOM_SPRITE_SHEET_ROW_MOVING = 13;
    inline static constexpr size_t CUSTOM_SPRITE_SHEET_ROW_END_MOVING = 14;
    enum class CustomAnimations : uint8_t {
        Idle = CUSTOM_SPRITE_SHEET_ROW_IDLE,
        Boring = CUSTOM_SPRITE_SHEET_ROW_BORING,
        StartWriting = CUSTOM_SPRITE_SHEET_ROW_START_WRITING,
        Writing = CUSTOM_SPRITE_SHEET_ROW_WRITING,
        EndWriting = CUSTOM_SPRITE_SHEET_ROW_END_WRITING,
        Happy = CUSTOM_SPRITE_SHEET_ROW_HAPPY,
        ASleep = CUSTOM_SPRITE_SHEET_ROW_ASLEEP,
        Sleep = CUSTOM_SPRITE_SHEET_ROW_SLEEP,
        WakeUp = CUSTOM_SPRITE_SHEET_ROW_WAKE_UP,
        StartWorking = CUSTOM_SPRITE_SHEET_ROW_START_WORKING,
        Working = CUSTOM_SPRITE_SHEET_ROW_WORKING,
        EndWorking = CUSTOM_SPRITE_SHEET_ROW_END_WORKING,
        StartMoving = CUSTOM_SPRITE_SHEET_ROW_START_MOVING,
        Moving = CUSTOM_SPRITE_SHEET_ROW_MOVING,
        EndMoving = CUSTOM_SPRITE_SHEET_ROW_END_MOVING,
    };

    // custom (sprite sheet)
    inline static constexpr char CUSTOM_ID_ARR[] = "custom";
    inline static constexpr const char* CUSTOM_ID = CUSTOM_ID_ARR;
    inline static constexpr std::size_t CUSTOM_ID_LEN = sizeof(CUSTOM_ID_ARR)-1;
    inline static constexpr char CUSTOM_NAME_ARR[] = "custom";
    inline static constexpr const char* CUSTOM_NAME = CUSTOM_NAME_ARR;
    inline static constexpr std::size_t CUSTOM_NAME_LEN = sizeof(CUSTOM_NAME_ARR)-1;
}

#endif // BONGOCAT_EMBEDDED_ASSETS_CUSTOM_SPRITE_H
