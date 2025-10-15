#ifndef BONGOCAT_ANIMATION_SPRITE_SHEET_H
#define BONGOCAT_ANIMATION_SPRITE_SHEET_H

#include "utils/memory.h"
#include <cstdint>

namespace bongocat::animation {
    // bongocat: both-up, left-down, right-down, both-down
    inline static constexpr size_t BONGOCAT_NUM_FRAMES = 4;
    // dm: Idle 1, Idle 2, Angry, Down1, Happy, Eat1, Sleep1, Refuse, Down2 ~~, Eat2, Sleep2, Attack~~
    inline static constexpr size_t MAX_DIGIMON_FRAMES = 16;
    // pkmn: Idle 1, Idle 2
    inline static constexpr size_t MAX_PKMN_FRAMES = 2;
    // @NOTE: MS agents can have more frames and are more custom

    inline static constexpr size_t MAX_NUM_FRAMES = 16;

    inline static constexpr size_t MAX_ANIMATION_FRAMES = 4;
    // @NOTE: MS agents can have more frames per row and are more custom

    struct sprite_sheet_animation_frame_t {
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

    struct dm_sprite_sheet_frames_t {
        sprite_sheet_animation_frame_t idle_1;      // 0
        sprite_sheet_animation_frame_t idle_2;      // 1
        sprite_sheet_animation_frame_t angry;       // 2
        sprite_sheet_animation_frame_t down_1;      // 3
        sprite_sheet_animation_frame_t happy;       // 4
        sprite_sheet_animation_frame_t eat_1;       // 5
        sprite_sheet_animation_frame_t sleep_1;     // 6
        sprite_sheet_animation_frame_t refuse;      // 7
        sprite_sheet_animation_frame_t sad;         // 8

        // optional
        sprite_sheet_animation_frame_t down_2;      // 9
        sprite_sheet_animation_frame_t eat_2;       //10
        sprite_sheet_animation_frame_t sleep_2;     //11
        sprite_sheet_animation_frame_t attack_1;    //12

        // extra frames
        sprite_sheet_animation_frame_t movement_1;  //13
        sprite_sheet_animation_frame_t movement_2;  //14
        sprite_sheet_animation_frame_t attack_2;    //15
    };

    struct dm_sprite_sheet_animations_t {
        int32_t idle[MAX_ANIMATION_FRAMES]{};
        int32_t boring[MAX_ANIMATION_FRAMES]{};
        int32_t writing[MAX_ANIMATION_FRAMES]{};
        int32_t sleep[MAX_ANIMATION_FRAMES]{};
        int32_t wake_up[MAX_ANIMATION_FRAMES]{};
        int32_t working[MAX_ANIMATION_FRAMES]{};  // attack
        int32_t moving[MAX_ANIMATION_FRAMES]{};
        int32_t happy[MAX_ANIMATION_FRAMES]{};
    };

    struct dm_sprite_sheet_t {
        generic_sprite_sheet_image_t image;

        int32_t frame_width{0};
        int32_t frame_height{0};
        int32_t total_frames{0};

        dm_sprite_sheet_frames_t frames;

        dm_sprite_sheet_animations_t animations;
    };

    struct pkmn_sprite_sheet_t {
        generic_sprite_sheet_image_t image;

        int32_t frame_width{0};
        int32_t frame_height{0};
        int32_t total_frames{0};

        sprite_sheet_animation_frame_t idle_1;
        sprite_sheet_animation_frame_t idle_2;

        sprite_sheet_animation_frame_t _rest_frames[MAX_NUM_FRAMES-2];

        dm_sprite_sheet_animations_t _cached_animations;
    };

    struct bongocat_sprite_sheet_t {
        generic_sprite_sheet_image_t image;

        int32_t frame_width{0};
        int32_t frame_height{0};
        int32_t total_frames{0};

        sprite_sheet_animation_frame_t both_up;
        sprite_sheet_animation_frame_t left_down;
        sprite_sheet_animation_frame_t right_down;
        sprite_sheet_animation_frame_t both_down;

        sprite_sheet_animation_frame_t _rest_frames[MAX_NUM_FRAMES-4];

        dm_sprite_sheet_animations_t _cached_animations;
    };

    struct ms_agent_sprite_sheet_animation_section_t {
        bool valid{false};
        int16_t start_col{0};
        int16_t end_col{0};
        int32_t row{0};
    };
    static_assert(sizeof(sprite_sheet_animation_frame_t) == sizeof(ms_agent_sprite_sheet_animation_section_t));
    struct ms_agent_sprite_sheet_t {
        generic_sprite_sheet_image_t image;

        int32_t frame_width{0};
        int32_t frame_height{0};
        int32_t _placeholder_total_frames{0};

        ms_agent_sprite_sheet_animation_section_t idle;
        ms_agent_sprite_sheet_animation_section_t boring;

        ms_agent_sprite_sheet_animation_section_t start_writing;
        ms_agent_sprite_sheet_animation_section_t writing;
        ms_agent_sprite_sheet_animation_section_t end_writing;

        ms_agent_sprite_sheet_animation_section_t sleep;
        ms_agent_sprite_sheet_animation_section_t wake_up;

        ms_agent_sprite_sheet_animation_section_t start_working;
        ms_agent_sprite_sheet_animation_section_t working;
        ms_agent_sprite_sheet_animation_section_t end_working;

        ms_agent_sprite_sheet_animation_section_t start_moving;
        ms_agent_sprite_sheet_animation_section_t moving;
        ms_agent_sprite_sheet_animation_section_t end_moving;

        sprite_sheet_animation_frame_t _rest_frames[MAX_NUM_FRAMES-13];

        dm_sprite_sheet_animations_t _placeholder_animations;
    };

    struct generic_sprite_sheet_t {
        generic_sprite_sheet_image_t image{};

        int32_t frame_width{0};
        int32_t frame_height{0};
        int32_t total_frames{0};

        sprite_sheet_animation_frame_t frames[MAX_NUM_FRAMES];

        dm_sprite_sheet_animations_t _placeholder_animations{};
    };

    struct animation_t;
    void cleanup_animation(animation_t& anim);

    static_assert(sizeof(dm_sprite_sheet_t) == sizeof(bongocat_sprite_sheet_t));
    static_assert(sizeof(bongocat_sprite_sheet_t) == sizeof(dm_sprite_sheet_t));
    static_assert(sizeof(generic_sprite_sheet_t) == sizeof(bongocat_sprite_sheet_t));
    static_assert(sizeof(generic_sprite_sheet_t) == sizeof(dm_sprite_sheet_t));
    static_assert(sizeof(generic_sprite_sheet_t) == sizeof(ms_agent_sprite_sheet_t));
    static_assert(sizeof(generic_sprite_sheet_t) == sizeof(pkmn_sprite_sheet_t));
    struct animation_t {
        union {
            bongocat_sprite_sheet_t bongocat;
            dm_sprite_sheet_t dm;
            ms_agent_sprite_sheet_t ms_agent;
            pkmn_sprite_sheet_t pkmn;
            generic_sprite_sheet_t sprite_sheet;
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
            sprite_sheet._placeholder_animations = {};
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
            sprite_sheet._placeholder_animations = other.sprite_sheet._placeholder_animations;
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
                sprite_sheet._placeholder_animations = other.sprite_sheet._placeholder_animations;
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
            sprite_sheet._placeholder_animations = other.sprite_sheet._placeholder_animations;

            other.sprite_sheet.image = {};
            other.sprite_sheet.frame_width = 0;
            other.sprite_sheet.frame_height = 0;
            other.sprite_sheet.total_frames = 0;
            for (size_t i = 0; i < MAX_NUM_FRAMES; i++) {
                sprite_sheet.frames[i] = {};
            }
            other.sprite_sheet._placeholder_animations = {};
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
                sprite_sheet._placeholder_animations = other.sprite_sheet._placeholder_animations;

                other.sprite_sheet.image = {};
                other.sprite_sheet.frame_width = 0;
                other.sprite_sheet.frame_height = 0;
                other.sprite_sheet.total_frames = 0;
                for (size_t i = 0; i < MAX_NUM_FRAMES; i++) {
                    sprite_sheet.frames[i] = {};
                }
                other.sprite_sheet._placeholder_animations = {};
            }
            return *this;
        }
    };
    inline void cleanup_animation(generic_sprite_sheet_t& sprite_sheet) {
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
        sprite_sheet._placeholder_animations = {};
    }
    inline void cleanup_animation(dm_sprite_sheet_t& sprite_sheet) {
        release_allocated_array(sprite_sheet.image.pixels);
        sprite_sheet.image.sprite_sheet_width = 0;
        sprite_sheet.image.sprite_sheet_height = 0;
        sprite_sheet.image.channels = 0;
        sprite_sheet.frame_width = 0;
        sprite_sheet.frame_height = 0;
        sprite_sheet.total_frames = 0;
        sprite_sheet.animations = {};
    }
    inline void cleanup_animation(pkmn_sprite_sheet_t& sprite_sheet) {
        release_allocated_array(sprite_sheet.image.pixels);
        sprite_sheet.image.sprite_sheet_width = 0;
        sprite_sheet.image.sprite_sheet_height = 0;
        sprite_sheet.image.channels = 0;
        sprite_sheet.frame_width = 0;
        sprite_sheet.frame_height = 0;
        sprite_sheet.total_frames = 0;
        sprite_sheet._cached_animations = {};
    }
    inline void cleanup_animation(bongocat_sprite_sheet_t& sprite_sheet) {
        release_allocated_array(sprite_sheet.image.pixels);
        sprite_sheet.image.sprite_sheet_width = 0;
        sprite_sheet.image.sprite_sheet_height = 0;
        sprite_sheet.image.channels = 0;
        sprite_sheet.frame_width = 0;
        sprite_sheet.frame_height = 0;
        sprite_sheet.total_frames = 0;
        sprite_sheet._cached_animations = {};
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

        sprite_sheet._placeholder_animations = {};
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
        anim.sprite_sheet._placeholder_animations = {};
    }
}

#endif //BONGOCAT_ANIMATION_SPRITE_SHEET_H
