#ifndef BONGOCAT_ANIMATION_SHARED_MEMORY_H
#define BONGOCAT_ANIMATION_SHARED_MEMORY_H

#include "sprite_sheet.h"
#include "embedded_assets.h"
#include "utils/time.h"

namespace bongocat::animation {
    struct animation_shared_memory_t {
        // Animation frame data
        animation_t anims[assets::ANIMS_COUNT];
        int anim_index{0};
        int anim_frame_index{0};
        platform::timestamp_ms_t time_until_next_frame_ms{0};

        animation_shared_memory_t() = default;
        ~animation_shared_memory_t() {
            time_until_next_frame_ms = 0;
            anim_frame_index = 0;
            anim_index = 0;
            for (size_t i = 0; i < assets::ANIMS_COUNT; i++) {
                cleanup_animation(anims[i]);
            }
        }
        animation_shared_memory_t(const animation_shared_memory_t& other)
            : anim_index(other.anim_index),
              anim_frame_index(other.anim_frame_index),
              time_until_next_frame_ms(other.time_until_next_frame_ms)
        {
            for (size_t i = 0; i < assets::ANIMS_COUNT; ++i) {
                anims[i] = other.anims[i];
            }
        }
        animation_shared_memory_t& operator=(const animation_shared_memory_t& other) {
            if (this != &other) {
                anim_index = other.anim_index;
                anim_frame_index = other.anim_frame_index;
                time_until_next_frame_ms = other.time_until_next_frame_ms;
                for (size_t i = 0; i < assets::ANIMS_COUNT; ++i) {
                    anims[i] = other.anims[i];
                }
            }
            return *this;
        }

        animation_shared_memory_t(animation_shared_memory_t&& other) noexcept
            : anim_index(other.anim_index),
              anim_frame_index(other.anim_frame_index),
              time_until_next_frame_ms(other.time_until_next_frame_ms)
        {
            for (size_t i = 0; i < assets::ANIMS_COUNT; ++i) {
                anims[i] = move(other.anims[i]);
            }
            other.anim_index = 0;
            other.anim_frame_index = 0;
            other.time_until_next_frame_ms = 0;
        }
        animation_shared_memory_t& operator=(animation_shared_memory_t&& other) noexcept {
            if (this != &other) {
                anim_index = other.anim_index;
                anim_frame_index = other.anim_frame_index;
                time_until_next_frame_ms = other.time_until_next_frame_ms;
                for (size_t i = 0; i < assets::ANIMS_COUNT; ++i) {
                    anims[i] = move(other.anims[i]);
                }
                other.anim_index = 0;
                other.anim_frame_index = 0;
                other.time_until_next_frame_ms = 0;
            }
            return *this;
        }
    };
}

#endif // BONGOCAT_ANIMATION_SHARED_MEMORY_H