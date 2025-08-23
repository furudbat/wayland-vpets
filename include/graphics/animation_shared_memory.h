#ifndef BONGOCAT_ANIMATION_SHARED_MEMORY_H
#define BONGOCAT_ANIMATION_SHARED_MEMORY_H

#include "sprite_sheet.h"
#include "graphics/embedded_assets.h"
#include "graphics/embedded_assets/bongocat.hpp"
#include "graphics/embedded_assets/clippy.hpp"
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
        config::config_animation_sprite_sheet_layout_t anim_type{config::config_animation_sprite_sheet_layout_t::None};
        int anim_index{0};
        animation_player_data_t animation_player_data{};
#ifdef FEATURE_BONGOCAT_EMBEDDED_ASSETS
        animation_t bongocat_anims[assets::BONGOCAT_ANIMATIONS_COUNT];
#endif
#ifdef FEATURE_ENABLE_DM_EMBEDDED_ASSETS
        animation_t dm_anims[assets::DM_ANIMATIONS_COUNT];
#endif
#ifdef FEATURE_CLIPPY_EMBEDDED_ASSETS
        ms_pet_sprite_sheet_t ms_anims[assets::MS_AGENTS_ANIMATIONS_COUNT];
#endif



        animation_shared_memory_t() = default;
        ~animation_shared_memory_t() {
            anim_type = config::config_animation_sprite_sheet_layout_t::None;
            animation_player_data = {};
            anim_index = 0;
#ifdef FEATURE_BONGOCAT_EMBEDDED_ASSETS
            for (size_t i = 0; i < assets::BONGOCAT_ANIMATIONS_COUNT; i++) {
                cleanup_animation(bongocat_anims[i]);
            }
#endif
#ifdef FEATURE_ENABLE_DM_EMBEDDED_ASSETS
            for (size_t i = 0; i < assets::DM_ANIMATIONS_COUNT; i++) {
                cleanup_animation(dm_anims[i]);
            }
#endif
#ifdef FEATURE_CLIPPY_EMBEDDED_ASSETS
            for (size_t i = 0; i < assets::MS_AGENTS_ANIMATIONS_COUNT; i++) {
                cleanup_animation(ms_anims[i]);
            }
#endif
        }
        animation_shared_memory_t(const animation_shared_memory_t& other)
            : anim_type(other.anim_type), anim_index(other.anim_index),
              animation_player_data(other.animation_player_data)
        {
#ifdef FEATURE_BONGOCAT_EMBEDDED_ASSETS
            for (size_t i = 0; i < assets::BONGOCAT_ANIMATIONS_COUNT; i++) {
                bongocat_anims[i] = other.bongocat_anims[i];
            }
#endif
#ifdef FEATURE_ENABLE_DM_EMBEDDED_ASSETS
            for (size_t i = 0; i < assets::DM_ANIMATIONS_COUNT; i++) {
                dm_anims[i] = other.dm_anims[i];
            }
#endif
#ifdef FEATURE_CLIPPY_EMBEDDED_ASSETS
            for (size_t i = 0; i < assets::MS_AGENTS_ANIMATIONS_COUNT; i++) {
                ms_anims[i] = other.ms_anims[i];
            }
#endif
        }
        animation_shared_memory_t& operator=(const animation_shared_memory_t& other) {
            if (this != &other) {
                anim_type = other.anim_type;
                anim_index = other.anim_index;
                animation_player_data = other.animation_player_data;
#ifdef FEATURE_BONGOCAT_EMBEDDED_ASSETS
                for (size_t i = 0; i < assets::BONGOCAT_ANIMATIONS_COUNT; i++) {
                    bongocat_anims[i] = other.bongocat_anims[i];
                }
#endif
#ifdef FEATURE_ENABLE_DM_EMBEDDED_ASSETS
                for (size_t i = 0; i < assets::DM_ANIMATIONS_COUNT; i++) {
                    dm_anims[i] = other.dm_anims[i];
                }
#endif
#ifdef FEATURE_CLIPPY_EMBEDDED_ASSETS
                for (size_t i = 0; i < assets::MS_AGENTS_ANIMATIONS_COUNT; i++) {
                    ms_anims[i] = other.ms_anims[i];
                }
#endif
            }
            return *this;
        }

        animation_shared_memory_t(animation_shared_memory_t&& other) noexcept
            : anim_type(other.anim_type), anim_index(other.anim_index),
              animation_player_data(other.animation_player_data)
        {
#ifdef FEATURE_BONGOCAT_EMBEDDED_ASSETS
            for (size_t i = 0; i < assets::BONGOCAT_ANIMATIONS_COUNT; i++) {
                bongocat_anims[i] = bongocat::move(other.bongocat_anims[i]);
            }
#endif
#ifdef FEATURE_ENABLE_DM_EMBEDDED_ASSETS
            for (size_t i = 0; i < assets::DM_ANIMATIONS_COUNT; i++) {
                dm_anims[i] = bongocat::move(other.dm_anims[i]);
            }
#endif
#ifdef FEATURE_CLIPPY_EMBEDDED_ASSETS
            for (size_t i = 0; i < assets::MS_AGENTS_ANIMATIONS_COUNT; i++) {
                ms_anims[i] = bongocat::move(other.ms_anims[i]);
            }
#endif

            other.anim_type = config::config_animation_sprite_sheet_layout_t::None;
            other.anim_index = 0;
            other.animation_player_data = {};
        }
        animation_shared_memory_t& operator=(animation_shared_memory_t&& other) noexcept {
            if (this != &other) {
                anim_type = other.anim_type;
                anim_index = other.anim_index;
                animation_player_data = other.animation_player_data;
#ifdef FEATURE_BONGOCAT_EMBEDDED_ASSETS
                for (size_t i = 0; i < assets::BONGOCAT_ANIMATIONS_COUNT; i++) {
                    bongocat_anims[i] = bongocat::move(other.bongocat_anims[i]);
                }
#endif
#ifdef FEATURE_ENABLE_DM_EMBEDDED_ASSETS
                for (size_t i = 0; i < assets::DM_ANIMATIONS_COUNT; i++) {
                    dm_anims[i] = bongocat::move(other.dm_anims[i]);
                }
#endif
#ifdef FEATURE_CLIPPY_EMBEDDED_ASSETS
                for (size_t i = 0; i < assets::MS_AGENTS_ANIMATIONS_COUNT; i++) {
                    ms_anims[i] = bongocat::move(other.ms_anims[i]);
                }
#endif

                other.anim_type = config::config_animation_sprite_sheet_layout_t::None;
                other.anim_index = 0;
                other.animation_player_data = {};
            }
            return *this;
        }
    };
}

#endif // BONGOCAT_ANIMATION_SHARED_MEMORY_H