#ifndef BONGOCAT_ANIMATION_SPRITE_SHEET_H
#define BONGOCAT_ANIMATION_SPRITE_SHEET_H

#include "utils/memory.h"
#include <cstdint>

namespace bongocat::animation {
    // both-up, left-down, right-down, both-down
    inline static constexpr size_t BONGOCAT_NUM_FRAMES = 4;
    // Idle 1, Idle 2, Angry, Down1, Happy, Eat1, Sleep1, Refuse, Down2 ~~, Eat2, Sleep2, Attack~~
    inline static constexpr size_t MAX_DIGIMON_FRAMES = 15;
    // Idle 1, Idle 2
    inline static constexpr size_t MAX_PKMN_FRAMES = 2;

    inline static constexpr size_t MAX_NUM_FRAMES = 15;

    struct sprite_sheet_animation_region_t {
        bool valid{false};
        int32_t col{0};
        int32_t row{0};
    };

    struct generic_sprite_sheet_image_t {
        int32_t sprite_sheet_width{0};
        int32_t sprite_sheet_height{0};
        int32_t channels{0};
        AllocatedArray<uint8_t> pixels;
    };

    struct dm_animation_t {
        generic_sprite_sheet_image_t image;

        int32_t frame_width{0};
        int32_t frame_height{0};
        int32_t total_frames{0};

        sprite_sheet_animation_region_t idle_1;
        sprite_sheet_animation_region_t idle_2;
        sprite_sheet_animation_region_t angry;
        sprite_sheet_animation_region_t down1;
        sprite_sheet_animation_region_t happy;
        sprite_sheet_animation_region_t eat1;
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

    struct pkmn_animation_t {
        generic_sprite_sheet_image_t image;

        int32_t frame_width{0};
        int32_t frame_height{0};
        int32_t total_frames{0};

        sprite_sheet_animation_region_t idle_1;
        sprite_sheet_animation_region_t idle_2;

        sprite_sheet_animation_region_t _placeholder[MAX_NUM_FRAMES-2];
    };

    struct bongocat_animation_t {
        generic_sprite_sheet_image_t image;

        int32_t frame_width{0};
        int32_t frame_height{0};
        int32_t total_frames{0};

        sprite_sheet_animation_region_t both_up;
        sprite_sheet_animation_region_t left_down;
        sprite_sheet_animation_region_t right_down;
        sprite_sheet_animation_region_t both_down;

        sprite_sheet_animation_region_t _placeholder[MAX_NUM_FRAMES-4];
    };

    struct ms_agent_sprite_sheet_animation_region_t {
        bool valid{false};
        int16_t start_col{0};
        int16_t end_col{0};
        int32_t row{0};
    };
    static_assert(sizeof(sprite_sheet_animation_region_t) == sizeof(ms_agent_sprite_sheet_animation_region_t));
    struct ms_agent_sprite_sheet_t {
        generic_sprite_sheet_image_t image;

        int32_t frame_width{0};
        int32_t frame_height{0};
        int32_t _placeholder_total_frames{0};

        ms_agent_sprite_sheet_animation_region_t idle;
        ms_agent_sprite_sheet_animation_region_t boring;

        ms_agent_sprite_sheet_animation_region_t start_writing;
        ms_agent_sprite_sheet_animation_region_t writing;
        ms_agent_sprite_sheet_animation_region_t end_writing;

        ms_agent_sprite_sheet_animation_region_t sleep;
        ms_agent_sprite_sheet_animation_region_t wake_up;

        ms_agent_sprite_sheet_animation_region_t start_working;
        ms_agent_sprite_sheet_animation_region_t working;
        ms_agent_sprite_sheet_animation_region_t end_working;

        ms_agent_sprite_sheet_animation_region_t start_moving;
        ms_agent_sprite_sheet_animation_region_t moving;
        ms_agent_sprite_sheet_animation_region_t end_moving;

        sprite_sheet_animation_region_t _placeholder[MAX_NUM_FRAMES-13];
    };

    struct generic_sprite_sheet_animation_t {
        generic_sprite_sheet_image_t image;

        int32_t frame_width{0};
        int32_t frame_height{0};
        int32_t total_frames{0};

        sprite_sheet_animation_region_t frames[MAX_NUM_FRAMES];
    };

    struct animation_t;
    void cleanup_animation(animation_t& anim);

    static_assert(sizeof(dm_animation_t) == sizeof(bongocat_animation_t));
    static_assert(sizeof(bongocat_animation_t) == sizeof(dm_animation_t));
    static_assert(sizeof(generic_sprite_sheet_animation_t) == sizeof(bongocat_animation_t));
    static_assert(sizeof(generic_sprite_sheet_animation_t) == sizeof(dm_animation_t));
    static_assert(sizeof(generic_sprite_sheet_animation_t) == sizeof(ms_agent_sprite_sheet_t));
    static_assert(sizeof(generic_sprite_sheet_animation_t) == sizeof(pkmn_animation_t));
    struct animation_t {
        union {
            bongocat_animation_t bongocat;
            dm_animation_t dm;
            ms_agent_sprite_sheet_t ms_agent;
            pkmn_animation_t pkmn;
            generic_sprite_sheet_animation_t sprite_sheet;
        };

        animation_t() {
            sprite_sheet.image.pixels.data = nullptr;
            sprite_sheet.image.pixels.count = 0;
            sprite_sheet.image.channels = 0;
            sprite_sheet.image.sprite_sheet_width = 0;
            sprite_sheet.image.sprite_sheet_height = 0;
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
            sprite_sheet.image.sprite_sheet_width = other.sprite_sheet.image.sprite_sheet_width;
            sprite_sheet.image.sprite_sheet_height = other.sprite_sheet.image.sprite_sheet_height;
            sprite_sheet.image.channels = other.sprite_sheet.image.channels;
            sprite_sheet.image.pixels = other.sprite_sheet.image.pixels;
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
                sprite_sheet.image.sprite_sheet_width = other.sprite_sheet.image.sprite_sheet_width;
                sprite_sheet.image.sprite_sheet_height = other.sprite_sheet.image.sprite_sheet_height;
                sprite_sheet.image.channels = other.sprite_sheet.image.channels;
                sprite_sheet.image.pixels = other.sprite_sheet.image.pixels;
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
            sprite_sheet.image.sprite_sheet_width = other.sprite_sheet.image.sprite_sheet_width;
            sprite_sheet.image.sprite_sheet_height = other.sprite_sheet.image.sprite_sheet_height;
            sprite_sheet.image.channels = other.sprite_sheet.image.channels;
            sprite_sheet.image.pixels = bongocat::move(other.sprite_sheet.image.pixels);
            sprite_sheet.frame_width = other.sprite_sheet.frame_width;
            sprite_sheet.frame_height = other.sprite_sheet.frame_height;
            sprite_sheet.total_frames = other.sprite_sheet.total_frames;
            for (size_t i = 0; i < MAX_NUM_FRAMES; i++) {
                sprite_sheet.frames[i] = bongocat::move(other.sprite_sheet.frames[i]);
            }

            other.sprite_sheet.image = {};
            other.sprite_sheet.frame_width = 0;
            other.sprite_sheet.frame_height = 0;
            other.sprite_sheet.total_frames = 0;
            for (size_t i = 0; i < MAX_NUM_FRAMES; i++) {
                sprite_sheet.frames[i] = {};
            }
        }
        animation_t& operator=(animation_t&& other) noexcept {
            if (this != &other) {
                sprite_sheet.image.sprite_sheet_width = other.sprite_sheet.image.sprite_sheet_width;
                sprite_sheet.image.sprite_sheet_height = other.sprite_sheet.image.sprite_sheet_height;
                sprite_sheet.image.channels = other.sprite_sheet.image.channels;
                sprite_sheet.image.pixels = bongocat::move(other.sprite_sheet.image.pixels);
                sprite_sheet.frame_width = other.sprite_sheet.frame_width;
                sprite_sheet.frame_height = other.sprite_sheet.frame_height;
                sprite_sheet.total_frames = other.sprite_sheet.total_frames;
                for (size_t i = 0; i < MAX_NUM_FRAMES; i++) {
                    sprite_sheet.frames[i] = bongocat::move(other.sprite_sheet.frames[i]);
                }

                other.sprite_sheet.image = {};
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
    inline void cleanup_animation(generic_sprite_sheet_animation_t& sprite_sheet) {
        release_allocated_array(sprite_sheet.image.pixels);
        sprite_sheet.image.sprite_sheet_width = 0;
        sprite_sheet.image.sprite_sheet_height = 0;
        sprite_sheet.image.channels = 0;
        sprite_sheet.frame_width = 0;
        sprite_sheet.frame_height = 0;
        sprite_sheet.total_frames = 0;
        for (size_t i = 0; i < MAX_NUM_FRAMES; i++) {
            sprite_sheet.frames[i] = {};
        }
    }
    inline void cleanup_animation(dm_animation_t& sprite_sheet) {
        release_allocated_array(sprite_sheet.image.pixels);
        sprite_sheet.image.sprite_sheet_width = 0;
        sprite_sheet.image.sprite_sheet_height = 0;
        sprite_sheet.image.channels = 0;
        sprite_sheet.frame_width = 0;
        sprite_sheet.frame_height = 0;
        sprite_sheet.total_frames = 0;
    }
    inline void cleanup_animation(pkmn_animation_t& sprite_sheet) {
        release_allocated_array(sprite_sheet.image.pixels);
        sprite_sheet.image.sprite_sheet_width = 0;
        sprite_sheet.image.sprite_sheet_height = 0;
        sprite_sheet.image.channels = 0;
        sprite_sheet.frame_width = 0;
        sprite_sheet.frame_height = 0;
        sprite_sheet.total_frames = 0;
    }
    inline void cleanup_animation(bongocat_animation_t& sprite_sheet) {
        release_allocated_array(sprite_sheet.image.pixels);
        sprite_sheet.image.sprite_sheet_width = 0;
        sprite_sheet.image.sprite_sheet_height = 0;
        sprite_sheet.image.channels = 0;
        sprite_sheet.frame_width = 0;
        sprite_sheet.frame_height = 0;
        sprite_sheet.total_frames = 0;
    }
    inline void cleanup_animation(ms_agent_sprite_sheet_t& sprite_sheet) {
        release_allocated_array(sprite_sheet.image.pixels);
        sprite_sheet.image.sprite_sheet_width = 0;
        sprite_sheet.image.sprite_sheet_height = 0;
        sprite_sheet.image.channels = 0;
        sprite_sheet.frame_width = 0;
        sprite_sheet.frame_height = 0;

        sprite_sheet.idle = {};
        sprite_sheet.boring = {};
        sprite_sheet.start_writing = {};
        sprite_sheet.writing = {};
        sprite_sheet.end_writing = {};
        sprite_sheet.sleep = {};
        sprite_sheet.wake_up = {};
        sprite_sheet.start_working = {};
        sprite_sheet.working = {};
        sprite_sheet.end_working = {};
        sprite_sheet.start_moving = {};
        sprite_sheet.moving = {};
        sprite_sheet.end_moving = {};
    }
    inline void cleanup_animation(animation_t& anim) {
        release_allocated_array(anim.sprite_sheet.image.pixels);
        anim.sprite_sheet.image.sprite_sheet_width = 0;
        anim.sprite_sheet.image.sprite_sheet_height = 0;
        anim.sprite_sheet.image.channels = 0;
        anim.sprite_sheet.frame_width = 0;
        anim.sprite_sheet.frame_height = 0;

        anim.sprite_sheet.total_frames = 0;
        for (size_t i = 0; i < MAX_NUM_FRAMES; i++) {
            anim.sprite_sheet.frames[i] = {};
        }
    }
}

#endif //BONGOCAT_ANIMATION_SPRITE_SHEET_H
