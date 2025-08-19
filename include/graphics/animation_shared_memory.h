#ifndef BONGOCAT_ANIMATION_SHARED_MEMORY_H
#define BONGOCAT_ANIMATION_SHARED_MEMORY_H

#include "sprite_sheet.h"
#include "embedded_assets.h"
#include "config/config.h"
#include "utils/time.h"

namespace bongocat::animation {
    struct animation_player_data_t {
        int frame_index{0};
        int sprite_sheet_row{0};
        int start_frame_index{0};
        int end_frame_index{0};
        platform::timestamp_ms_t time_until_next_frame_ms{0};
    };
    struct animation_shared_memory_t {
        // Animation frame data
        config::config_animation_type_t anim_type{config::config_animation_type_t::None};
        int anim_index{0};
        animation_player_data_t animation_player_data{};
        animation_t anims[assets::ANIMS_COUNT];
        ms_pet_sprite_sheet_t ms_anims[assets::MS_PETS_COUNT];

        animation_shared_memory_t() = default;
        ~animation_shared_memory_t() {
            anim_type = config::config_animation_type_t::None;
            animation_player_data = {};
            anim_index = 0;
            for (size_t i = 0; i < assets::ANIMS_COUNT; i++) {
                cleanup_animation(anims[i]);
            }
            for (size_t i = 0; i < assets::MS_PETS_COUNT; i++) {
                cleanup_animation(ms_anims[i]);
            }
        }
        animation_shared_memory_t(const animation_shared_memory_t& other)
            : anim_type(other.anim_type), anim_index(other.anim_index),
              animation_player_data(other.animation_player_data)
        {
            for (size_t i = 0; i < assets::ANIMS_COUNT; ++i) {
                anims[i] = other.anims[i];
            }
            for (size_t i = 0; i < assets::MS_PETS_COUNT; ++i) {
                ms_anims[i] = other.ms_anims[i];
            }
        }
        animation_shared_memory_t& operator=(const animation_shared_memory_t& other) {
            if (this != &other) {
                anim_type = other.anim_type;
                anim_index = other.anim_index;
                animation_player_data = other.animation_player_data;
                for (size_t i = 0; i < assets::ANIMS_COUNT; ++i) {
                    anims[i] = other.anims[i];
                }
                for (size_t i = 0; i < assets::MS_PETS_COUNT; ++i) {
                    ms_anims[i] = other.ms_anims[i];
                }
            }
            return *this;
        }

        animation_shared_memory_t(animation_shared_memory_t&& other) noexcept
            : anim_type(other.anim_type), anim_index(other.anim_index),
              animation_player_data(other.animation_player_data)
        {
            for (size_t i = 0; i < assets::ANIMS_COUNT; ++i) {
                anims[i] = move(other.anims[i]);
            }
            for (size_t i = 0; i < assets::MS_PETS_COUNT; ++i) {
                ms_anims[i] = move(other.ms_anims[i]);
            }

            other.anim_type = config::config_animation_type_t::None;
            other.anim_index = 0;
            other.animation_player_data = {};
        }
        animation_shared_memory_t& operator=(animation_shared_memory_t&& other) noexcept {
            if (this != &other) {
                anim_type = other.anim_type;
                anim_index = other.anim_index;
                animation_player_data = other.animation_player_data;
                for (size_t i = 0; i < assets::ANIMS_COUNT; ++i) {
                    anims[i] = move(other.anims[i]);
                }
                for (size_t i = 0; i < assets::MS_PETS_COUNT; ++i) {
                    ms_anims[i] = move(other.ms_anims[i]);
                }

                other.anim_type = config::config_animation_type_t::None;
                other.anim_index = 0;
                other.animation_player_data = {};
            }
            return *this;
        }
    };
}

#endif // BONGOCAT_ANIMATION_SHARED_MEMORY_H