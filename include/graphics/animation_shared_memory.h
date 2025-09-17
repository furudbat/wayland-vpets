#ifndef BONGOCAT_ANIMATION_SHARED_MEMORY_H
#define BONGOCAT_ANIMATION_SHARED_MEMORY_H

#include "sprite_sheet.h"
#include "config/config.h"
#include "utils/system_memory.h"
#include "utils/time.h"

namespace bongocat::animation {
    struct animation_player_data_t {
        int32_t frame_index{0};
        int32_t sprite_sheet_row{0};
        int32_t start_frame_index{0};
        int32_t end_frame_index{0};
        platform::timestamp_ms_t time_until_next_frame_ms{0};
    };

    struct animation_shared_memory_t {
        // animation state
        animation_player_data_t animation_player_data{};
        int32_t anim_index{0};
        config::config_animation_sprite_sheet_layout_t anim_type{config::config_animation_sprite_sheet_layout_t::None};
        config::config_animation_dm_set_t anim_dm_set{config::config_animation_dm_set_t::None};

        // Animation frame data for sprite sheet preload
        platform::MMapArray<animation_t> bongocat_anims;
        platform::MMapArray<animation_t> dm_anims;
        platform::MMapArray<animation_t> dm20_anims;
        platform::MMapArray<animation_t> dmc_anims;
        platform::MMapArray<animation_t> dmx_anims;
        platform::MMapArray<animation_t> dmall_anims;
        platform::MMapArray<animation_t> min_dm_anims;
        platform::MMapArray<animation_t> ms_anims;
        platform::MMapArray<animation_t> pkmn_anims;

        // for sprite sheet hot reload
        bongocat_animation_t bongocat_sprite_sheet;
        dm_animation_t dm_sprite_sheet;
        ms_agent_sprite_sheet_t ms_agent_sprite_sheet;
        pkmn_animation_t pkmn_sprite_sheet;

        animation_shared_memory_t() = default;
        ~animation_shared_memory_t() {
            anim_type = config::config_animation_sprite_sheet_layout_t::None;
            anim_dm_set = config::config_animation_dm_set_t::None;
            animation_player_data = {};
            anim_index = 0;

            for (size_t i = 0; i < bongocat_anims.count; i++) {
                cleanup_animation(bongocat_anims[i]);
            }
            platform::release_allocated_mmap_array(bongocat_anims);

            for (size_t i = 0; i < dm_anims.count; i++) {
                cleanup_animation(dm_anims[i]);
            }
            platform::release_allocated_mmap_array(dm_anims);

            for (size_t i = 0; i < dm20_anims.count; i++) {
                cleanup_animation(dm20_anims[i]);
            }
            platform::release_allocated_mmap_array(dm20_anims);

            for (size_t i = 0; i < dmc_anims.count; i++) {
                cleanup_animation(dmc_anims[i]);
            }
            platform::release_allocated_mmap_array(dmc_anims);

            for (size_t i = 0; i < dmx_anims.count; i++) {
                cleanup_animation(dmx_anims[i]);
            }
            platform::release_allocated_mmap_array(dmx_anims);

            for (size_t i = 0; i < dmall_anims.count; i++) {
                cleanup_animation(dmall_anims[i]);
            }
            platform::release_allocated_mmap_array(dmall_anims);

            for (size_t i = 0; i < min_dm_anims.count; i++) {
                cleanup_animation(min_dm_anims[i]);
            }
            platform::release_allocated_mmap_array(min_dm_anims);

            for (size_t i = 0; i < ms_anims.count; i++) {
                cleanup_animation(ms_anims[i]);
            }
            platform::release_allocated_mmap_array(ms_anims);

            for (size_t i = 0; i < pkmn_anims.count; i++) {
                cleanup_animation(pkmn_anims[i]);
            }
            platform::release_allocated_mmap_array(pkmn_anims);

            cleanup_animation(bongocat_sprite_sheet);
            cleanup_animation(dm_sprite_sheet);
            cleanup_animation(ms_agent_sprite_sheet);
            cleanup_animation(pkmn_sprite_sheet);

        }
        animation_shared_memory_t(const animation_shared_memory_t& other)
            : animation_player_data(other.animation_player_data), anim_index(other.anim_index), anim_type(other.anim_type), anim_dm_set(other.anim_dm_set)
        {
            bongocat_anims = other.bongocat_anims;
            dm_anims = other.dm_anims;
            dm20_anims = other.dm20_anims;
            dmc_anims = other.dmc_anims;
            dmx_anims = other.dmx_anims;
            dmall_anims = other.dmall_anims;
            min_dm_anims = other.min_dm_anims;
            ms_anims = other.ms_anims;
            pkmn_anims = other.pkmn_anims;

            bongocat_sprite_sheet = other.bongocat_sprite_sheet;
            dm_sprite_sheet = other.dm_sprite_sheet;
            ms_agent_sprite_sheet = other.ms_agent_sprite_sheet;
            pkmn_sprite_sheet = other.pkmn_sprite_sheet;
        }
        animation_shared_memory_t& operator=(const animation_shared_memory_t& other) {
            if (this != &other) {
                anim_type = other.anim_type;
                anim_dm_set = other.anim_dm_set;
                anim_index = other.anim_index;
                animation_player_data = other.animation_player_data;

                bongocat_anims = other.bongocat_anims;
                dm_anims = other.dm_anims;
                dm20_anims = other.dm20_anims;
                dmc_anims = other.dmc_anims;
                dmx_anims = other.dmx_anims;
                dmall_anims = other.dmall_anims;
                min_dm_anims = other.min_dm_anims;
                ms_anims = other.ms_anims;
                pkmn_anims = other.pkmn_anims;

                bongocat_sprite_sheet = other.bongocat_sprite_sheet;
                dm_sprite_sheet = other.dm_sprite_sheet;
                ms_agent_sprite_sheet = other.ms_agent_sprite_sheet;
                pkmn_sprite_sheet = other.pkmn_sprite_sheet;
            }
            return *this;
        }

        animation_shared_memory_t(animation_shared_memory_t&& other) noexcept
            : animation_player_data(other.animation_player_data), anim_index(other.anim_index), anim_type(other.anim_type), anim_dm_set(other.anim_dm_set)
        {
            bongocat_anims = bongocat::move(other.bongocat_anims);
            dm_anims = bongocat::move(other.dm_anims);
            dm20_anims = bongocat::move(other.dm20_anims);
            dmc_anims = bongocat::move(other.dmc_anims);
            dmx_anims = bongocat::move(other.dmx_anims);
            dmall_anims = bongocat::move(other.dmall_anims);
            min_dm_anims = bongocat::move(other.min_dm_anims);
            ms_anims = bongocat::move(other.ms_anims);
            pkmn_anims = bongocat::move(other.pkmn_anims);

            bongocat_sprite_sheet = bongocat::move(other.bongocat_sprite_sheet);
            dm_sprite_sheet = bongocat::move(other.dm_sprite_sheet);
            ms_agent_sprite_sheet = bongocat::move(other.ms_agent_sprite_sheet);
            pkmn_sprite_sheet = bongocat::move(other.pkmn_sprite_sheet);

            cleanup_animation(other.bongocat_sprite_sheet);
            cleanup_animation(other.dm_sprite_sheet);
            cleanup_animation(other.ms_agent_sprite_sheet);
            cleanup_animation(other.pkmn_sprite_sheet);
            platform::release_allocated_mmap_array(other.bongocat_anims);
            platform::release_allocated_mmap_array(other.dm_anims);
            platform::release_allocated_mmap_array(other.dm20_anims);
            platform::release_allocated_mmap_array(other.dmc_anims);
            platform::release_allocated_mmap_array(other.dmx_anims);
            platform::release_allocated_mmap_array(other.dmall_anims);
            platform::release_allocated_mmap_array(other.min_dm_anims);
            platform::release_allocated_mmap_array(other.ms_anims);
            platform::release_allocated_mmap_array(other.pkmn_anims);
            other.anim_type = config::config_animation_sprite_sheet_layout_t::None;
            other.anim_dm_set = config::config_animation_dm_set_t::None;
            other.anim_index = 0;
            other.animation_player_data = {};
        }
        animation_shared_memory_t& operator=(animation_shared_memory_t&& other) noexcept {
            if (this != &other) {
                anim_type = other.anim_type;
                anim_index = other.anim_index;
                animation_player_data = other.animation_player_data;

                bongocat_anims = bongocat::move(other.bongocat_anims);
                dm_anims = bongocat::move(other.dm_anims);
                dm20_anims = bongocat::move(other.dm20_anims);
                dmc_anims = bongocat::move(other.dmc_anims);
                dmx_anims = bongocat::move(other.dmx_anims);
                dmall_anims = bongocat::move(other.dmall_anims);
                min_dm_anims = bongocat::move(other.min_dm_anims);
                ms_anims = bongocat::move(other.ms_anims);
                pkmn_anims = bongocat::move(other.pkmn_anims);

                bongocat_sprite_sheet = bongocat::move(other.bongocat_sprite_sheet);
                dm_sprite_sheet = bongocat::move(other.dm_sprite_sheet);
                ms_agent_sprite_sheet = bongocat::move(other.ms_agent_sprite_sheet);
                pkmn_sprite_sheet = bongocat::move(other.pkmn_sprite_sheet);

                cleanup_animation(other.bongocat_sprite_sheet);
                cleanup_animation(other.dm_sprite_sheet);
                cleanup_animation(other.ms_agent_sprite_sheet);
                cleanup_animation(other.pkmn_sprite_sheet);
                platform::release_allocated_mmap_array(other.bongocat_anims);
                platform::release_allocated_mmap_array(other.dm_anims);
                platform::release_allocated_mmap_array(other.dm20_anims);
                platform::release_allocated_mmap_array(other.dmc_anims);
                platform::release_allocated_mmap_array(other.dmx_anims);
                platform::release_allocated_mmap_array(other.dmall_anims);
                platform::release_allocated_mmap_array(other.min_dm_anims);
                platform::release_allocated_mmap_array(other.ms_anims);
                platform::release_allocated_mmap_array(other.pkmn_anims);
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