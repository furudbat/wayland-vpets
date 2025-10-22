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

    struct sprite_sheet_animations_t {
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

        sprite_sheet_animations_t animations;
    };

    struct pkmn_sprite_sheet_t {
        generic_sprite_sheet_image_t image;

        int32_t frame_width{0};
        int32_t frame_height{0};
        int32_t total_frames{0};

        sprite_sheet_animation_frame_t idle_1;
        sprite_sheet_animation_frame_t idle_2;

        sprite_sheet_animations_t animations;
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

        sprite_sheet_animations_t animations;
    };

    struct ms_agent_sprite_sheet_animation_section_t {
        bool valid{false};
        int32_t start_col{0};
        int32_t end_col{0};
        int32_t row{0};
    };
    struct ms_agent_sprite_sheet_t {
        generic_sprite_sheet_image_t image;

        int32_t frame_width{0};
        int32_t frame_height{0};

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

        ms_agent_sprite_sheet_animation_section_t happy;
    };

    struct generic_sprite_sheet_t {
        generic_sprite_sheet_image_t image{};

        int32_t frame_width{0};
        int32_t frame_height{0};
        int32_t total_frames{0};

        sprite_sheet_animation_frame_t frames[MAX_NUM_FRAMES];
    };

    struct animation_t;
    void cleanup_animation(animation_t& anim);

    // sprite_sheet variant
    struct animation_t {
        union {
            bongocat_sprite_sheet_t bongocat;
            dm_sprite_sheet_t dm;
            ms_agent_sprite_sheet_t ms_agent;
            pkmn_sprite_sheet_t pkmn;
            generic_sprite_sheet_t sprite_sheet;
        };
        enum class Type : uint8_t { Generic, Bongocat, Dm, MsAgent, Pkmn } type{Type::Generic};

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
            type = Type::Generic;
        }
        ~animation_t() {
            cleanup_animation(*this);
        }

        animation_t(const animation_t& other) {
            type = other.type;
            switch (other.type) {
                case Type::Bongocat:  bongocat  = other.bongocat;  break;
                case Type::Dm:        dm        = other.dm;        break;
                case Type::MsAgent:   ms_agent  = other.ms_agent;  break;
                case Type::Pkmn:      pkmn      = other.pkmn;      break;
                case Type::Generic:   sprite_sheet = other.sprite_sheet; break;
            }
        }
        animation_t& operator=(const animation_t& other) {
            if (this != &other) {
                cleanup_animation(*this);
                type = other.type;
                switch (other.type) {
                    case Type::Bongocat:  bongocat  = other.bongocat;  break;
                    case Type::Dm:        dm        = other.dm;        break;
                    case Type::MsAgent:   ms_agent  = other.ms_agent;  break;
                    case Type::Pkmn:      pkmn      = other.pkmn;      break;
                    case Type::Generic:   sprite_sheet = other.sprite_sheet; break;
                }
            }
            return *this;
        }

        animation_t(animation_t&& other) noexcept {
            type = other.type;
            switch (other.type) {
                case Type::Bongocat:
                    new (&bongocat) bongocat_sprite_sheet_t(bongocat::move(other.bongocat));
                    break;
                case Type::Dm:
                    new (&dm) dm_sprite_sheet_t(bongocat::move(other.dm));
                    break;
                case Type::MsAgent:
                    new (&ms_agent) ms_agent_sprite_sheet_t(bongocat::move(other.ms_agent));
                    break;
                case Type::Pkmn:
                    new (&pkmn) pkmn_sprite_sheet_t(bongocat::move(other.pkmn));
                    break;
                case Type::Generic:
                    new (&sprite_sheet) generic_sprite_sheet_t(bongocat::move(other.sprite_sheet));
                    break;
            }
            other.type = Type::Generic;
            new (&other.sprite_sheet) generic_sprite_sheet_t();
        }
        animation_t& operator=(animation_t&& other) noexcept {
            if (this != &other) {
                cleanup_animation(*this);
                type = other.type;
                switch (other.type) {
                    case Type::Bongocat:
                        new (&bongocat) bongocat_sprite_sheet_t(bongocat::move(other.bongocat));
                        break;
                    case Type::Dm:
                        new (&dm) dm_sprite_sheet_t(bongocat::move(other.dm));
                        break;
                    case Type::MsAgent:
                        new (&ms_agent) ms_agent_sprite_sheet_t(bongocat::move(other.ms_agent));
                        break;
                    case Type::Pkmn:
                        new (&pkmn) pkmn_sprite_sheet_t(bongocat::move(other.pkmn));
                        break;
                    case Type::Generic:
                        new (&sprite_sheet) generic_sprite_sheet_t(bongocat::move(other.sprite_sheet));
                        break;
                }
                other.type = Type::Generic;
                new (&other.sprite_sheet) generic_sprite_sheet_t();
            }
            return *this;
        }

        explicit animation_t(bongocat_sprite_sheet_t&& sheet) noexcept
            : bongocat(bongocat::move(sheet)), type(Type::Bongocat) {}

        explicit animation_t(dm_sprite_sheet_t&& sheet) noexcept
            : dm(bongocat::move(sheet)), type(Type::Dm) {}

        explicit animation_t(ms_agent_sprite_sheet_t&& sheet) noexcept
            : ms_agent(bongocat::move(sheet)), type(Type::MsAgent) {}

        explicit animation_t(pkmn_sprite_sheet_t&& sheet) noexcept
            : pkmn(bongocat::move(sheet)), type(Type::Pkmn) {}

        explicit animation_t(generic_sprite_sheet_t&& sheet) noexcept
            : sprite_sheet(bongocat::move(sheet)), type(Type::Generic) {}


        animation_t& operator=(bongocat_sprite_sheet_t&& sheet) noexcept {
            cleanup_animation(*this);
            new (&bongocat) bongocat_sprite_sheet_t(bongocat::move(sheet));
            type = Type::Bongocat;
            return *this;
        }
        animation_t& operator=(dm_sprite_sheet_t&& sheet) noexcept {
            cleanup_animation(*this);
            new (&dm) dm_sprite_sheet_t(bongocat::move(sheet));
            type = Type::Dm;
            return *this;
        }
        animation_t& operator=(ms_agent_sprite_sheet_t&& sheet) noexcept {
            cleanup_animation(*this);
            new (&ms_agent) ms_agent_sprite_sheet_t(bongocat::move(sheet));
            type = Type::MsAgent;
            return *this;
        }
        animation_t& operator=(pkmn_sprite_sheet_t&& sheet) noexcept {
            cleanup_animation(*this);
            new (&pkmn) pkmn_sprite_sheet_t(bongocat::move(sheet));
            type = Type::Pkmn;
            return *this;
        }
        animation_t& operator=(generic_sprite_sheet_t&& sheet) noexcept {
            cleanup_animation(*this);
            new (&sprite_sheet) generic_sprite_sheet_t(bongocat::move(sheet));
            type = Type::Generic;
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
        sprite_sheet.animations = {};
    }
    inline void cleanup_animation(bongocat_sprite_sheet_t& sprite_sheet) {
        release_allocated_array(sprite_sheet.image.pixels);
        sprite_sheet.image.sprite_sheet_width = 0;
        sprite_sheet.image.sprite_sheet_height = 0;
        sprite_sheet.image.channels = 0;
        sprite_sheet.frame_width = 0;
        sprite_sheet.frame_height = 0;
        sprite_sheet.total_frames = 0;
        sprite_sheet.animations = {};
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
        switch (anim.type) {
            case animation_t::Type::Bongocat:
                release_allocated_array(anim.bongocat.image.pixels);
                anim.bongocat.image.sprite_sheet_width = 0;
                anim.bongocat.image.sprite_sheet_height = 0;
                anim.bongocat.image.channels = 0;
                anim.bongocat.frame_width = 0;
                anim.bongocat.frame_height = 0;
                break;
            case animation_t::Type::Dm:
                release_allocated_array(anim.dm.image.pixels);
                anim.dm.image.sprite_sheet_width = 0;
                anim.dm.image.sprite_sheet_height = 0;
                anim.dm.image.channels = 0;
                anim.dm.frame_width = 0;
                anim.dm.frame_height = 0;

                anim.dm.total_frames = 0;
                break;
            case animation_t::Type::MsAgent:
                release_allocated_array(anim.ms_agent.image.pixels);
                anim.ms_agent.image.sprite_sheet_width = 0;
                anim.ms_agent.image.sprite_sheet_height = 0;
                anim.ms_agent.image.channels = 0;
                anim.ms_agent.frame_width = 0;
                anim.ms_agent.frame_height = 0;
                break;
            case animation_t::Type::Pkmn:
                release_allocated_array(anim.pkmn.image.pixels);
                anim.pkmn.image.sprite_sheet_width = 0;
                anim.pkmn.image.sprite_sheet_height = 0;
                anim.pkmn.image.channels = 0;
                anim.pkmn.frame_width = 0;
                anim.pkmn.frame_height = 0;
                break;
            case animation_t::Type::Generic:
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
                break;
        }
    }
}

#endif //BONGOCAT_ANIMATION_SPRITE_SHEET_H
