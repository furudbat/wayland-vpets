#ifndef BONGOCAT_ANIMATION_SHARED_MEMORY_H
#define BONGOCAT_ANIMATION_SHARED_MEMORY_H

#include "sprite_sheet.h"
#include "graphics/embedded_assets.h"
#include "config/config.h"
#include "utils/time.h"


namespace bongocat::animation {
    // see config.animation_index (int32_t)
    static_assert(assets::BONGOCAT_ANIMATIONS_COUNT <= INT32_MAX);
    static_assert(assets::DM_ANIMATIONS_COUNT <= INT32_MAX);
    static_assert(assets::MS_AGENTS_ANIMATIONS_COUNT <= INT32_MAX);

    struct animation_player_data_t {
        int32_t frame_index{0};
        int32_t sprite_sheet_row{0};
        int32_t start_frame_index{0};
        int32_t end_frame_index{0};
        platform::timestamp_ms_t time_until_next_frame_ms{0};
    };
    struct animation_shared_memory_t {
        // Animation frame data
#ifdef FEATURE_BONGOCAT_EMBEDDED_ASSETS
        static constexpr size_t bongocat_anims_count{assets::BONGOCAT_ANIMATIONS_COUNT};
        animation_t bongocat_anims[bongocat_anims_count];
#endif

#ifdef FEATURE_ENABLE_DM_EMBEDDED_ASSETS
#ifdef FEATURE_DM20_EMBEDDED_ASSETS
        static constexpr size_t dm_anims_count{assets::DM20_ANIM_COUNT};
        animation_t dm_anims[dm_anims_count];
#elif FEATURE_DM_EMBEDDED_ASSETS
        static constexpr size_t dm_anims_count{assets::DM_ANIM_COUNT};
        animation_t dm_anims[dm_anims_count];
#elif FEATURE_MIN_DM_EMBEDDED_ASSETS
        static constexpr size_t dm_anims_count{assets::DM_ANIM_COUNT};
        animation_t dm_anims[dm_anims_count];
#endif

#ifdef FEATURE_PEN20_EMBEDDED_ASSETS
        static constexpr size_t pen20_anims_count{assets::PEN20_ANIM_COUNT};
        animation_t pen20_anims[pen20_anims_count];
#endif
#ifdef FEATURE_DMX_EMBEDDED_ASSETS
        static constexpr size_t dmx_anims_count{assets::DMX_ANIM_COUNT};
        animation_t dmx_anims[dmx_anims_count];
#endif
#ifdef FEATURE_DMC_EMBEDDED_ASSETS
        static constexpr size_t dmc_anims_count{assets::DM20_ANIM_COUNT};
        animation_t dmc_anims[dmc_anims_count];
#endif
#endif

#ifdef FEATURE_MS_AGENT_EMBEDDED_ASSETS
        static constexpr size_t ms_anims_count{assets::MS_AGENTS_ANIMATIONS_COUNT};
        ms_pet_sprite_sheet_t ms_anims[ms_anims_count];
#endif
        animation_player_data_t animation_player_data{};
        int32_t anim_index{0};
        config::config_animation_sprite_sheet_layout_t anim_type{config::config_animation_sprite_sheet_layout_t::None};
        config::config_animation_dm_set_t anim_dm_set{config::config_animation_dm_set_t::None};



        animation_shared_memory_t() = default;
        ~animation_shared_memory_t() {
            using namespace assets;
            anim_type = config::config_animation_sprite_sheet_layout_t::None;
            anim_dm_set = config::config_animation_dm_set_t::None;
            animation_player_data = {};
            anim_index = 0;

#ifdef FEATURE_BONGOCAT_EMBEDDED_ASSETS
            for (size_t i = 0; i < bongocat_anims_count; i++) {
                cleanup_animation(bongocat_anims[i]);
            }
#endif

#ifdef FEATURE_ENABLE_DM_EMBEDDED_ASSETS
#ifdef FEATURE_DM20_EMBEDDED_ASSETS
            for (size_t i = 0; i < dm_anims_count; i++) {
                cleanup_animation(dm_anims[i]);
            }
#elif FEATURE_DM_EMBEDDED_ASSETS
            for (size_t i = 0; i < dm_anims_count; i++) {
                cleanup_animation(dm_anims[i]);
            }
#elif FEATURE_MIN_DM_EMBEDDED_ASSETS
            for (size_t i = 0; i < dm_anims_count; i++) {
                cleanup_animation(dm_anims[i]);
            }
#endif

#if FEATURE_PEN20_EMBEDDED_ASSETS
            for (size_t i = 0; i < pen20_anims_count; i++) {
                cleanup_animation(pen20_anims[i]);
            }
#endif
#if FEATURE_DMX_EMBEDDED_ASSETS
            for (size_t i = 0; i < dmx_anims_count; i++) {
                cleanup_animation(dmx_anims[i]);
            }
#endif
#if FEATURE_DMC_EMBEDDED_ASSETS
            for (size_t i = 0; i < dmc_anims_count; i++) {
                cleanup_animation(dmc_anims[i]);
            }
#endif
#endif

#ifdef FEATURE_MS_AGENT_EMBEDDED_ASSETS
            for (size_t i = 0; i < ms_anims_count; i++) {
                cleanup_animation(ms_anims[i]);
            }
#endif
        }
        animation_shared_memory_t(const animation_shared_memory_t& other)
            : animation_player_data(other.animation_player_data), anim_index(other.anim_index), anim_type(other.anim_type), anim_dm_set(other.anim_dm_set)
        {
            using namespace assets;
#ifdef FEATURE_BONGOCAT_EMBEDDED_ASSETS
            for (size_t i = 0; i < bongocat_anims_count; i++) {
                bongocat_anims[i] = other.bongocat_anims[i];
            }
#endif
#ifdef FEATURE_ENABLE_DM_EMBEDDED_ASSETS
#ifdef FEATURE_DM20_EMBEDDED_ASSETS
            for (size_t i = 0; i < dm_anims_count; i++) {
                cleanup_animation(dm_anims[i]);
            }
#elif FEATURE_DM_EMBEDDED_ASSETS
            for (size_t i = 0; i < dm_anims_count; i++) {
                cleanup_animation(dm_anims[i]);
            }
#elif FEATURE_MIN_DM_EMBEDDED_ASSETS
            for (size_t i = 0; i < dm_anims_count; i++) {
                cleanup_animation(dm_anims[i]);
            }
#endif

#if FEATURE_PEN20_EMBEDDED_ASSETS
            for (size_t i = 0; i < pen20_anims_count; i++) {
                cleanup_animation(pen20_anims[i]);
            }
#endif
#if FEATURE_DMX_EMBEDDED_ASSETS
            for (size_t i = 0; i < dmx_anims_count; i++) {
                cleanup_animation(dmx_anims[i]);
            }
#endif
#if FEATURE_DMC_EMBEDDED_ASSETS
            for (size_t i = 0; i < dmc_anims_count; i++) {
                cleanup_animation(dmc_anims[i]);
            }
#endif
#endif
#ifdef FEATURE_MS_AGENT_EMBEDDED_ASSETS
            for (size_t i = 0; i < ms_anims_count; i++) {
                ms_anims[i] = other.ms_anims[i];
            }
#endif
        }
        animation_shared_memory_t& operator=(const animation_shared_memory_t& other) {
            using namespace assets;
            if (this != &other) {
                anim_type = other.anim_type;
                anim_dm_set = other.anim_dm_set;
                anim_index = other.anim_index;
                animation_player_data = other.animation_player_data;
#ifdef FEATURE_BONGOCAT_EMBEDDED_ASSETS
                for (size_t i = 0; i < bongocat_anims_count; i++) {
                    bongocat_anims[i] = other.bongocat_anims[i];
                }
#endif
#ifdef FEATURE_ENABLE_DM_EMBEDDED_ASSETS
#ifdef FEATURE_DM20_EMBEDDED_ASSETS
                for (size_t i = 0; i < dm_anims_count; i++) {
                    dm_anims[i] = other.dm_anims[i];
                }
#elif FEATURE_DM_EMBEDDED_ASSETS
                for (size_t i = 0; i < dm_anims_count; i++) {
                    dm_anims[i] = other.dm_anims[i];
                }
#elif FEATURE_MIN_DM_EMBEDDED_ASSETS
                for (size_t i = 0; i < dm_anims_count; i++) {
                    dm_anims[i] = other.dm_anims[i];
                }
#endif

#if FEATURE_PEN20_EMBEDDED_ASSETS
                for (size_t i = 0; i < pen20_anims_count; i++) {
                    pen20_anims[i] = other.pen20_anims[i];
                }
#endif

#if FEATURE_DMX_EMBEDDED_ASSETS
                for (size_t i = 0; i < dmx_anims_count; i++) {
                    dmx_anims[i] = other.dmx_anims[i];
                }
#endif

#if FEATURE_DMC_EMBEDDED_ASSETS
                for (size_t i = 0; i < dmc_anims_count; i++) {
                    dmc_anims[i] = other.dmc_anims[i];
                }
#endif
#endif

#ifdef FEATURE_MS_AGENT_EMBEDDED_ASSETS
                for (size_t i = 0; i < ms_anims_count; i++) {
                    ms_anims[i] = other.ms_anims[i];
                }
#endif

            }
            return *this;
        }

        animation_shared_memory_t(animation_shared_memory_t&& other) noexcept
            : animation_player_data(other.animation_player_data), anim_index(other.anim_index), anim_type(other.anim_type), anim_dm_set(other.anim_dm_set)
        {
            using namespace assets;
#ifdef FEATURE_BONGOCAT_EMBEDDED_ASSETS
            for (size_t i = 0; i < bongocat_anims_count; i++) {
                bongocat_anims[i] = bongocat::move(other.bongocat_anims[i]);
            }
#endif

#ifdef FEATURE_ENABLE_DM_EMBEDDED_ASSETS
#ifdef FEATURE_DM20_EMBEDDED_ASSETS
            for (size_t i = 0; i < dm_anims_count; i++) {
                dm_anims[i] = bongocat::move(other.dm_anims[i]);
            }
#elif FEATURE_DM_EMBEDDED_ASSETS
            for (size_t i = 0; i < dm_anims_count; i++) {
                dm_anims[i] = bongocat::move(other.dm_anims[i]);
            }
#elif FEATURE_MIN_DM_EMBEDDED_ASSETS
            for (size_t i = 0; i < dm_anims_count; i++) {
                dm_anims[i] = bongocat::move(other.dm_anims[i]);
            }
#endif

#if FEATURE_PEN20_EMBEDDED_ASSETS
            for (size_t i = 0; i < pen20_anims_count; i++) {
                pen20_anims[i] = bongocat::move(other.pen20_anims[i]);
            }
#endif

#if FEATURE_DMX_EMBEDDED_ASSETS
            for (size_t i = 0; i < dmx_anims_count; i++) {
                dmx_anims[i] = bongocat::move(other.dmx_anims[i]);
            }
#endif

#if FEATURE_DMC_EMBEDDED_ASSETS
            for (size_t i = 0; i < dmc_anims_count; i++) {
                dmc_anims[i] = bongocat::move(other.dmc_anims[i]);
            }
#endif
#endif

#ifdef FEATURE_MS_AGENT_EMBEDDED_ASSETS
            for (size_t i = 0; i < ms_anims_count; i++) {
                ms_anims[i] = bongocat::move(other.ms_anims[i]);
            }
#endif

            other.anim_type = config::config_animation_sprite_sheet_layout_t::None;
            other.anim_dm_set = config::config_animation_dm_set_t::None;
            other.anim_index = 0;
            other.animation_player_data = {};
        }
        animation_shared_memory_t& operator=(animation_shared_memory_t&& other) noexcept {
            using namespace assets;
            if (this != &other) {
                anim_type = other.anim_type;
                anim_index = other.anim_index;
                animation_player_data = other.animation_player_data;
#ifdef FEATURE_BONGOCAT_EMBEDDED_ASSETS
                for (size_t i = 0; i < bongocat_anims_count; i++) {
                    bongocat_anims[i] = bongocat::move(other.bongocat_anims[i]);
                }
#endif

#ifdef FEATURE_ENABLE_DM_EMBEDDED_ASSETS
#ifdef FEATURE_DM20_EMBEDDED_ASSETS
                for (size_t i = 0; i < dm_anims_count; i++) {
                    dm_anims[i] = bongocat::move(other.dm_anims[i]);
                }
#elif FEATURE_DM_EMBEDDED_ASSETS
                for (size_t i = 0; i < dm_anims_count; i++) {
                    dm_anims[i] = bongocat::move(other.dm_anims[i]);
                }
#elif FEATURE_MIN_DM_EMBEDDED_ASSETS
                for (size_t i = 0; i < dm_anims_count; i++) {
                    dm_anims[i] = bongocat::move(other.dm_anims[i]);
                }
#endif

#if FEATURE_PEN20_EMBEDDED_ASSETS
                for (size_t i = 0; i < pen20_anims_count; i++) {
                    pen20_anims[i] = bongocat::move(other.pen20_anims[i]);
                }
#endif

#if FEATURE_DMX_EMBEDDED_ASSETS
                for (size_t i = 0; i < dmx_anims_count; i++) {
                    dmx_anims[i] = bongocat::move(other.dmx_anims[i]);
                }
#endif

#if FEATURE_DMC_EMBEDDED_ASSETS
                for (size_t i = 0; i < dmc_anims_count; i++) {
                    dmc_anims[i] = bongocat::move(other.dmc_anims[i]);
                }
#endif
#endif

#ifdef FEATURE_MS_AGENT_EMBEDDED_ASSETS
                for (size_t i = 0; i < ms_anims_count; i++) {
                    ms_anims[i] = bongocat::move(other.ms_anims[i]);
                }
#endif

                other.anim_type = config::config_animation_sprite_sheet_layout_t::None;
                other.anim_dm_set = config::config_animation_dm_set_t::None;
                other.anim_index = 0;
                other.animation_player_data = {};
            }
            return *this;
        }
    };
}

#endif // BONGOCAT_ANIMATION_SHARED_MEMORY_H