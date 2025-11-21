#ifndef BONGOCAT_EMBEDDED_ASSETS_CUSTOM_SPRITE_H
#define BONGOCAT_EMBEDDED_ASSETS_CUSTOM_SPRITE_H

#include <cstddef>
#include <cstdint>

namespace bongocat::assets {
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
    inline static constexpr size_t CUSTOM_SPRITE_SHEET_ROW_START_RUNNING = 15;
    inline static constexpr size_t CUSTOM_SPRITE_SHEET_ROW_RUNNING = 16;
    inline static constexpr size_t CUSTOM_SPRITE_SHEET_ROW_END_RUNNING = 17;
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
        StartRunning = CUSTOM_SPRITE_SHEET_ROW_START_RUNNING,
        Running = CUSTOM_SPRITE_SHEET_ROW_RUNNING,
        EndRunning = CUSTOM_SPRITE_SHEET_ROW_END_RUNNING,
    };
    inline static constexpr size_t CUSTOM_SPRITE_SHEET_MAX_ROWS = 18;

    // custom (sprite sheet)
    inline static constexpr char CUSTOM_ID_ARR[] = "custom";
    inline static constexpr const char* CUSTOM_ID = CUSTOM_ID_ARR;
    inline static constexpr std::size_t CUSTOM_ID_LEN = sizeof(CUSTOM_ID_ARR)-1;
    inline static constexpr char CUSTOM_NAME_ARR[] = "custom";
    inline static constexpr const char* CUSTOM_NAME = CUSTOM_NAME_ARR;
    inline static constexpr std::size_t CUSTOM_NAME_LEN = sizeof(CUSTOM_NAME_ARR)-1;


    static inline constexpr int CUSTOM_HAPPY_CHANCE_PERCENT = 60;


    struct custom_animation_settings_t {
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

        int32_t start_running_frames{0};
        int32_t running_frames{0};
        int32_t end_running_frames{0};

        int32_t feature_toggle_writing_frames{-1};
        int32_t feature_toggle_writing_frames_random{-1};
        int32_t feature_mirror_x_moving{-1};

        // row lines (optional)
        int32_t idle_row_index{-1};

        int32_t boring_row_index{-1};

        int32_t start_writing_row_index{-1};
        int32_t writing_row_index{-1};
        int32_t end_writing_row_index{-1};
        int32_t happy_row_index{-1};

        int32_t asleep_row_index{-1};
        int32_t sleep_row_index{-1};
        int32_t wake_up_row_index{-1};

        int32_t start_working_row_index{-1};
        int32_t working_row_index{-1};
        int32_t end_working_row_index{-1};

        int32_t start_moving_row_index{-1};
        int32_t moving_row_index{-1};
        int32_t end_moving_row_index{-1};

        int32_t start_running_row_index{-1};
        int32_t running_row_index{-1};
        int32_t end_running_row_index{-1};
    };

    inline int get_custom_animation_settings_rows_count(const custom_animation_settings_t& sprite_sheet_settings) {
        int sprite_sheet_rows{0};

        // detect sprite sheet rows
        if (sprite_sheet_settings.idle_frames > 0) sprite_sheet_rows++;
        if (sprite_sheet_settings.boring_frames > 0) sprite_sheet_rows++;

        if (sprite_sheet_settings.start_writing_frames > 0) sprite_sheet_rows++;
        if (sprite_sheet_settings.writing_frames > 0) sprite_sheet_rows++;
        if (sprite_sheet_settings.end_writing_frames > 0) sprite_sheet_rows++;
        if (sprite_sheet_settings.happy_frames > 0) sprite_sheet_rows++;

        if (sprite_sheet_settings.asleep_frames > 0) sprite_sheet_rows++;
        if (sprite_sheet_settings.sleep_frames > 0) sprite_sheet_rows++;
        if (sprite_sheet_settings.wake_up_frames > 0) sprite_sheet_rows++;

        if (sprite_sheet_settings.start_working_frames > 0) sprite_sheet_rows++;
        if (sprite_sheet_settings.working_frames > 0) sprite_sheet_rows++;
        if (sprite_sheet_settings.end_working_frames > 0) sprite_sheet_rows++;

        if (sprite_sheet_settings.start_moving_frames > 0) sprite_sheet_rows++;
        if (sprite_sheet_settings.moving_frames > 0) sprite_sheet_rows++;
        if (sprite_sheet_settings.end_moving_frames > 0) sprite_sheet_rows++;

        if (sprite_sheet_settings.start_running_frames > 0) sprite_sheet_rows++;
        if (sprite_sheet_settings.running_frames > 0) sprite_sheet_rows++;
        if (sprite_sheet_settings.end_running_frames > 0) sprite_sheet_rows++;

        return sprite_sheet_rows;
    }
    inline int get_custom_animation_settings_max_cols(const custom_animation_settings_t& sprite_sheet_settings) {
        int sprite_sheet_cols = sprite_sheet_settings.idle_frames;

        if (sprite_sheet_settings.boring_frames >= sprite_sheet_cols) sprite_sheet_cols = sprite_sheet_settings.boring_frames;

        if (sprite_sheet_settings.start_writing_frames >= sprite_sheet_cols) sprite_sheet_cols = sprite_sheet_settings.start_writing_frames;
        if (sprite_sheet_settings.writing_frames >= sprite_sheet_cols) sprite_sheet_cols = sprite_sheet_settings.writing_frames;
        if (sprite_sheet_settings.end_writing_frames >= sprite_sheet_cols) sprite_sheet_cols = sprite_sheet_settings.end_writing_frames;
        if (sprite_sheet_settings.happy_frames >= sprite_sheet_cols) sprite_sheet_cols = sprite_sheet_settings.happy_frames;

        if (sprite_sheet_settings.asleep_frames >= sprite_sheet_cols) sprite_sheet_cols = sprite_sheet_settings.asleep_frames;
        if (sprite_sheet_settings.sleep_frames >= sprite_sheet_cols) sprite_sheet_cols = sprite_sheet_settings.sleep_frames;
        if (sprite_sheet_settings.wake_up_frames >= sprite_sheet_cols) sprite_sheet_cols = sprite_sheet_settings.wake_up_frames;

        if (sprite_sheet_settings.start_working_frames >= sprite_sheet_cols) sprite_sheet_cols = sprite_sheet_settings.start_working_frames;
        if (sprite_sheet_settings.working_frames >= sprite_sheet_cols) sprite_sheet_cols = sprite_sheet_settings.working_frames;
        if (sprite_sheet_settings.end_working_frames >= sprite_sheet_cols) sprite_sheet_cols = sprite_sheet_settings.end_working_frames;

        if (sprite_sheet_settings.start_moving_frames >= sprite_sheet_cols) sprite_sheet_cols = sprite_sheet_settings.start_moving_frames;
        if (sprite_sheet_settings.moving_frames >= sprite_sheet_cols) sprite_sheet_cols = sprite_sheet_settings.moving_frames;
        if (sprite_sheet_settings.end_moving_frames >= sprite_sheet_cols) sprite_sheet_cols = sprite_sheet_settings.end_moving_frames;

        if (sprite_sheet_settings.start_running_frames >= sprite_sheet_cols) sprite_sheet_cols = sprite_sheet_settings.start_running_frames;
        if (sprite_sheet_settings.running_frames >= sprite_sheet_cols) sprite_sheet_cols = sprite_sheet_settings.running_frames;
        if (sprite_sheet_settings.end_running_frames >= sprite_sheet_cols) sprite_sheet_cols = sprite_sheet_settings.end_running_frames;

        return sprite_sheet_cols;
    }
}

#endif // BONGOCAT_EMBEDDED_ASSETS_CUSTOM_SPRITE_H
