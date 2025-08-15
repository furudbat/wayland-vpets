#ifndef BONGOCAT_ANIMATION_SPRITE_SHEET_H
#define BONGOCAT_ANIMATION_SPRITE_SHEET_H

#include "utils/memory.h"
#include <cstdint>
#include <cstddef>

namespace bongocat::animation {
    // both-up, left-down, right-down, both-down
    inline static constexpr size_t BONGOCAT_NUM_FRAMES = 4;

    // Idle 1, Idle 2, Angry, Down1, Happy, Eat1, Sleep1, Refuse, Down2 ~~, Eat2, Sleep2, Attack~~
    // both-up, left-down, right-down, both-down, ...
    inline static constexpr size_t MAX_NUM_FRAMES = 15;
    inline static constexpr size_t MAX_DIGIMON_FRAMES = 15;

    struct sprite_sheet_animation_region_t {
        bool valid{false};
        int col{0};
        int row{0};
    };
    struct digimon_animation_t {
        int sprite_sheet_width{0};
        int sprite_sheet_height{0};
        int channels{0};
        AllocatedArray<uint8_t> pixels;

        int frame_width{0};
        int frame_height{0};
        int total_frames{0};

        sprite_sheet_animation_region_t idle_1;
        sprite_sheet_animation_region_t idle_2;
        sprite_sheet_animation_region_t angry;
        sprite_sheet_animation_region_t down1;
        sprite_sheet_animation_region_t happy;
        sprite_sheet_animation_region_t at1;
        sprite_sheet_animation_region_t sleep1;
        sprite_sheet_animation_region_t refuse;
        sprite_sheet_animation_region_t sad;

        // optional
        sprite_sheet_animation_region_t down_2;
        sprite_sheet_animation_region_t eat_2;
        sprite_sheet_animation_region_t sleep_2;
        sprite_sheet_animation_region_t attack;

        // extra frames
        sprite_sheet_animation_region_t movement_1;
        sprite_sheet_animation_region_t movement_2;
    };

    struct bongocat_animation_t {
        int sprite_sheet_width{0};
        int sprite_sheet_height{0};
        int channels{0};
        AllocatedArray<uint8_t> pixels;

        int frame_width{0};
        int frame_height{0};
        int total_frames{0};

        sprite_sheet_animation_region_t both_up;
        sprite_sheet_animation_region_t left_down;
        sprite_sheet_animation_region_t right_down;
        sprite_sheet_animation_region_t both_down;

        sprite_sheet_animation_region_t _placeholder[MAX_NUM_FRAMES-4];
    };

    struct generic_sprite_sheet_animation_t {
        int sprite_sheet_width{0};
        int sprite_sheet_height{0};
        int channels{0};
        AllocatedArray<uint8_t> pixels;

        int frame_width{0};
        int frame_height{0};
        int total_frames{0};

        sprite_sheet_animation_region_t frames[MAX_NUM_FRAMES];
    };

    static_assert(sizeof(digimon_animation_t) == sizeof(bongocat_animation_t));
    static_assert(sizeof(bongocat_animation_t) == sizeof(digimon_animation_t));
    static_assert(sizeof(generic_sprite_sheet_animation_t) == sizeof(bongocat_animation_t));
    static_assert(sizeof(generic_sprite_sheet_animation_t) == sizeof(digimon_animation_t));
    struct animation_t {
        union {
            bongocat_animation_t bongocat;
            digimon_animation_t digimon;
            generic_sprite_sheet_animation_t sprite_sheet;
        };

        animation_t() {
            sprite_sheet.sprite_sheet_width = 0;
            sprite_sheet.sprite_sheet_height = 0;
            sprite_sheet.channels = 0;
            sprite_sheet.pixels = {};
            sprite_sheet.frame_width = 0;
            sprite_sheet.frame_height = 0;
            sprite_sheet.total_frames = 0;
            for (size_t i = 0; i < MAX_NUM_FRAMES; i++) {
                sprite_sheet.frames[i] = {};
            }
        }
        ~animation_t() {
            sprite_sheet.sprite_sheet_width = 0;
            sprite_sheet.sprite_sheet_height = 0;
            sprite_sheet.channels = 0;
            sprite_sheet.pixels = {};
            sprite_sheet.frame_width = 0;
            sprite_sheet.frame_height = 0;
            sprite_sheet.total_frames = 0;
            for (size_t i = 0; i < MAX_NUM_FRAMES; i++) {
                sprite_sheet.frames[i] = {};
            }
        }

        animation_t(const animation_t& other) {
            sprite_sheet.sprite_sheet_width = other.sprite_sheet.sprite_sheet_width;
            sprite_sheet.sprite_sheet_height = other.sprite_sheet.sprite_sheet_height;
            sprite_sheet.channels = other.sprite_sheet.channels;
            sprite_sheet.pixels = other.sprite_sheet.pixels;
            sprite_sheet.frame_width = other.sprite_sheet.frame_width;
            sprite_sheet.frame_height = other.sprite_sheet.frame_height;
            sprite_sheet.total_frames = other.sprite_sheet.total_frames;
            for (size_t i = 0; i < MAX_NUM_FRAMES; i++) {
                sprite_sheet.frames[i] = other.sprite_sheet.frames[i];
            }
        }
        animation_t& operator=(const animation_t& other) {
            if (this != &other) {
                sprite_sheet.sprite_sheet_width = other.sprite_sheet.sprite_sheet_width;
                sprite_sheet.sprite_sheet_height = other.sprite_sheet.sprite_sheet_height;
                sprite_sheet.channels = other.sprite_sheet.channels;
                sprite_sheet.pixels = other.sprite_sheet.pixels;
                sprite_sheet.frame_width = other.sprite_sheet.frame_width;
                sprite_sheet.frame_height = other.sprite_sheet.frame_height;
                sprite_sheet.total_frames = other.sprite_sheet.total_frames;
                for (size_t i = 0; i < MAX_NUM_FRAMES; i++) {
                    sprite_sheet.frames[i] = other.sprite_sheet.frames[i];
                }
            }
            return *this;
        }

        animation_t(animation_t&& other) noexcept {
            sprite_sheet.sprite_sheet_width = other.sprite_sheet.sprite_sheet_width;
            sprite_sheet.sprite_sheet_height = other.sprite_sheet.sprite_sheet_height;
            sprite_sheet.channels = other.sprite_sheet.channels;
            sprite_sheet.pixels = bongocat_move(other.sprite_sheet.pixels);
            sprite_sheet.frame_width = other.sprite_sheet.frame_width;
            sprite_sheet.frame_height = other.sprite_sheet.frame_height;
            sprite_sheet.total_frames = other.sprite_sheet.total_frames;
            for (size_t i = 0; i < MAX_NUM_FRAMES; i++) {
                sprite_sheet.frames[i] = bongocat_move(other.sprite_sheet.frames[i]);
            }

            other.sprite_sheet.sprite_sheet_width = 0;
            other.sprite_sheet.sprite_sheet_height = 0;
            other.sprite_sheet.channels = 0;
            other.sprite_sheet.pixels = {};
            other.sprite_sheet.frame_width = 0;
            other.sprite_sheet.frame_height = 0;
            other.sprite_sheet.total_frames = 0;
            for (size_t i = 0; i < MAX_NUM_FRAMES; i++) {
                sprite_sheet.frames[i] = {};
            }
        }
        animation_t& operator=(animation_t&& other) noexcept {
            if (this != &other) {
                sprite_sheet.sprite_sheet_width = other.sprite_sheet.sprite_sheet_width;
                sprite_sheet.sprite_sheet_height = other.sprite_sheet.sprite_sheet_height;
                sprite_sheet.channels = other.sprite_sheet.channels;
                sprite_sheet.pixels = bongocat_move(other.sprite_sheet.pixels);
                sprite_sheet.frame_width = other.sprite_sheet.frame_width;
                sprite_sheet.frame_height = other.sprite_sheet.frame_height;
                sprite_sheet.total_frames = other.sprite_sheet.total_frames;
                for (size_t i = 0; i < MAX_NUM_FRAMES; i++) {
                    sprite_sheet.frames[i] = bongocat_move(other.sprite_sheet.frames[i]);
                }

                other.sprite_sheet.sprite_sheet_width = 0;
                other.sprite_sheet.sprite_sheet_height = 0;
                other.sprite_sheet.channels = 0;
                other.sprite_sheet.pixels = {};
                other.sprite_sheet.frame_width = 0;
                other.sprite_sheet.frame_height = 0;
                other.sprite_sheet.total_frames = 0;
                for (size_t i = 0; i < MAX_NUM_FRAMES; i++) {
                    sprite_sheet.frames[i] = {};
                }
            }
            return *this;
        }
    };
}

#endif //BONGOCAT_ANIMATION_SPRITE_SHEET_H
