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
    struct dm_animation_t {
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

    struct animation_t;
    void cleanup_animation(animation_t& anim);

    static_assert(sizeof(dm_animation_t) == sizeof(bongocat_animation_t));
    static_assert(sizeof(bongocat_animation_t) == sizeof(dm_animation_t));
    static_assert(sizeof(generic_sprite_sheet_animation_t) == sizeof(bongocat_animation_t));
    static_assert(sizeof(generic_sprite_sheet_animation_t) == sizeof(dm_animation_t));
    struct animation_t {
        union {
            bongocat_animation_t bongocat;
            dm_animation_t dm;
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
            cleanup_animation(*this);
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
                cleanup_animation(*this);
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
            sprite_sheet.pixels = bongocat::move(other.sprite_sheet.pixels);
            sprite_sheet.frame_width = other.sprite_sheet.frame_width;
            sprite_sheet.frame_height = other.sprite_sheet.frame_height;
            sprite_sheet.total_frames = other.sprite_sheet.total_frames;
            for (size_t i = 0; i < MAX_NUM_FRAMES; i++) {
                sprite_sheet.frames[i] = bongocat::move(other.sprite_sheet.frames[i]);
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
                sprite_sheet.pixels = bongocat::move(other.sprite_sheet.pixels);
                sprite_sheet.frame_width = other.sprite_sheet.frame_width;
                sprite_sheet.frame_height = other.sprite_sheet.frame_height;
                sprite_sheet.total_frames = other.sprite_sheet.total_frames;
                for (size_t i = 0; i < MAX_NUM_FRAMES; i++) {
                    sprite_sheet.frames[i] = bongocat::move(other.sprite_sheet.frames[i]);
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
    inline void cleanup_animation(animation_t& anim) {
        release_allocated_array(anim.sprite_sheet.pixels);
        anim.sprite_sheet.sprite_sheet_width = 0;
        anim.sprite_sheet.sprite_sheet_height = 0;
        anim.sprite_sheet.channels = 0;
        anim.sprite_sheet.frame_width = 0;
        anim.sprite_sheet.frame_height = 0;
        anim.sprite_sheet.total_frames = 0;
        for (size_t i = 0; i < MAX_NUM_FRAMES; i++) {
            anim.sprite_sheet.frames[i] = {};
        }
    }


    struct ms_pet_sprite_sheet_t;
    void cleanup_animation(ms_pet_sprite_sheet_t& sprite_sheet);

    struct ms_pet_sprite_sheet_t {
        int sprite_sheet_width{0};
        int sprite_sheet_height{0};
        int channels{0};
        AllocatedArray<uint8_t> pixels;

        int frame_width{0};
        int frame_height{0};

        ms_pet_sprite_sheet_t() {
            sprite_sheet_width = 0;
            sprite_sheet_height = 0;
            channels = 0;
            pixels = {};
            frame_width = 0;
            frame_height = 0;
        }
        ~ms_pet_sprite_sheet_t() {
            cleanup_animation(*this);
        }

        ms_pet_sprite_sheet_t(const ms_pet_sprite_sheet_t& other) {
            sprite_sheet_width = other.sprite_sheet_width;
            sprite_sheet_height = other.sprite_sheet_height;
            channels = other.channels;
            pixels = other.pixels;
            frame_width = other.frame_width;
            frame_height = other.frame_height;
        }
        ms_pet_sprite_sheet_t& operator=(const ms_pet_sprite_sheet_t& other) {
            if (this != &other) {
                cleanup_animation(*this);
                sprite_sheet_width = other.sprite_sheet_width;
                sprite_sheet_height = other.sprite_sheet_height;
                channels = other.channels;
                pixels = other.pixels;
                frame_width = other.frame_width;
                frame_height = other.frame_height;
            }
            return *this;
        }

        ms_pet_sprite_sheet_t(ms_pet_sprite_sheet_t&& other) noexcept {
            sprite_sheet_width = other.sprite_sheet_width;
            sprite_sheet_height = other.sprite_sheet_height;
            channels = other.channels;
            pixels = bongocat::move(other.pixels);
            frame_width = other.frame_width;
            frame_height = other.frame_height;

            other.sprite_sheet_width = 0;
            other.sprite_sheet_height = 0;
            other.channels = 0;
            other.pixels = {};
            other.frame_width = 0;
            other.frame_height = 0;
        }
        ms_pet_sprite_sheet_t& operator=(ms_pet_sprite_sheet_t&& other) noexcept {
            if (this != &other) {
                sprite_sheet_width = other.sprite_sheet_width;
                sprite_sheet_height = other.sprite_sheet_height;
                channels = other.channels;
                pixels = bongocat::move(other.pixels);
                frame_width = other.frame_width;
                frame_height = other.frame_height;

                other.sprite_sheet_width = 0;
                other.sprite_sheet_height = 0;
                other.channels = 0;
                other.pixels = {};
                other.frame_width = 0;
                other.frame_height = 0;
            }
            return *this;
        }
    };
    inline void cleanup_animation(ms_pet_sprite_sheet_t& sprite_sheet) {
        release_allocated_array(sprite_sheet.pixels);
        sprite_sheet.sprite_sheet_width = 0;
        sprite_sheet.sprite_sheet_height = 0;
        sprite_sheet.channels = 0;
        sprite_sheet.frame_width = 0;
        sprite_sheet.frame_height = 0;
    }
}

#endif //BONGOCAT_ANIMATION_SPRITE_SHEET_H
