#ifndef BONGOCAT_ANIMATION_SHARED_MEMORY_H
#define BONGOCAT_ANIMATION_SHARED_MEMORY_H

#include "sprite_sheet.h"
#include "config/config.h"
#include "utils/system_memory.h"
#include "utils/time.h"

namespace bongocat::animation {
    enum class animation_player_custom_overwrite_mirror_x : uint32_t {
        None,
        NoMirror,
        Mirror
    };
    struct animation_player_result_t {
        int32_t sprite_sheet_col{0};
        int32_t sprite_sheet_row{0};
        animation_player_custom_overwrite_mirror_x overwrite_mirror_x{animation_player_custom_overwrite_mirror_x::None};
    };

// =============================================================================
// ANIMATION STATE (shared memory between threads)
// =============================================================================

    struct animation_shared_memory_t {
        // animation state
        animation_player_result_t animation_player_result{};
        int32_t anim_index{0};
        config::config_animation_sprite_sheet_layout_t anim_type{config::config_animation_sprite_sheet_layout_t::None};
        config::config_animation_dm_set_t anim_dm_set{config::config_animation_dm_set_t::None};
        config::config_animation_custom_set_t anim_custom_set{config::config_animation_custom_set_t::None};
        float movement_offset_x{0.0};
        float anim_direction{0.0};

        // Animation frame data for sprite sheet preload
        platform::MMapArray<animation_t> bongocat_anims;
        platform::MMapArray<animation_t> dm_anims;
        platform::MMapArray<animation_t> dm20_anims;
        platform::MMapArray<animation_t> dmc_anims;
        platform::MMapArray<animation_t> dmx_anims;
        platform::MMapArray<animation_t> pen_anims;
        platform::MMapArray<animation_t> pen20_anims;
        platform::MMapArray<animation_t> dmall_anims;
        platform::MMapArray<animation_t> min_dm_anims;
        platform::MMapArray<animation_t> ms_anims;
        platform::MMapArray<animation_t> pkmn_anims;
        platform::MMapArray<animation_t> misc_anims;
        platform::MMapArray<animation_t> pmd_anims;

        // for sprite sheet hot reload (or custom sprite sheet)
        animation_t anim;

        animation_shared_memory_t() = default;
        ~animation_shared_memory_t() {
            anim_type = config::config_animation_sprite_sheet_layout_t::None;
            anim_dm_set = config::config_animation_dm_set_t::None;
            anim_custom_set = config::config_animation_custom_set_t::None;
            animation_player_result = {};
            anim_index = 0;
            movement_offset_x = 0;
            anim_direction = 0;

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

            for (size_t i = 0; i < pen_anims.count; i++) {
                cleanup_animation(pen_anims[i]);
            }
            platform::release_allocated_mmap_array(pen_anims);

            for (size_t i = 0; i < pen20_anims.count; i++) {
                cleanup_animation(pen20_anims[i]);
            }
            platform::release_allocated_mmap_array(pen20_anims);

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

            for (size_t i = 0; i < misc_anims.count; i++) {
                cleanup_animation(misc_anims[i]);
            }
            platform::release_allocated_mmap_array(misc_anims);

            for (size_t i = 0; i < pmd_anims.count; i++) {
                cleanup_animation(pmd_anims[i]);
            }
            platform::release_allocated_mmap_array(pmd_anims);

            cleanup_animation(anim);
        }
        animation_shared_memory_t(const animation_shared_memory_t& other)
            : animation_player_result(other.animation_player_result), anim_index(other.anim_index), anim_type(other.anim_type), anim_dm_set(other.anim_dm_set)
        {
            bongocat_anims = other.bongocat_anims;
            dm_anims = other.dm_anims;
            dm20_anims = other.dm20_anims;
            dmc_anims = other.dmc_anims;
            dmx_anims = other.dmx_anims;
            pen_anims = other.pen_anims;
            pen20_anims = other.pen20_anims;
            dmall_anims = other.dmall_anims;
            min_dm_anims = other.min_dm_anims;
            ms_anims = other.ms_anims;
            pkmn_anims = other.pkmn_anims;
            misc_anims = other.misc_anims;
            pmd_anims = other.pmd_anims;

            anim = other.anim;
        }
        animation_shared_memory_t& operator=(const animation_shared_memory_t& other) {
            if (this != &other) {
                anim_type = other.anim_type;
                anim_dm_set = other.anim_dm_set;
                anim_index = other.anim_index;
                animation_player_result = other.animation_player_result;

                bongocat_anims = other.bongocat_anims;
                dm_anims = other.dm_anims;
                dm20_anims = other.dm20_anims;
                dmc_anims = other.dmc_anims;
                dmx_anims = other.dmx_anims;
                pen_anims = other.pen_anims;
                pen20_anims = other.pen20_anims;
                dmall_anims = other.dmall_anims;
                min_dm_anims = other.min_dm_anims;
                ms_anims = other.ms_anims;
                pkmn_anims = other.pkmn_anims;
                misc_anims = other.misc_anims;
                pmd_anims = other.pmd_anims;

                anim = other.anim;
            }
            return *this;
        }

        animation_shared_memory_t(animation_shared_memory_t&& other) noexcept
            : animation_player_result(other.animation_player_result), anim_index(other.anim_index), anim_type(other.anim_type), anim_dm_set(other.anim_dm_set), anim_custom_set(other.anim_custom_set)
        {
            bongocat_anims = bongocat::move(other.bongocat_anims);
            dm_anims = bongocat::move(other.dm_anims);
            dm20_anims = bongocat::move(other.dm20_anims);
            dmc_anims = bongocat::move(other.dmc_anims);
            dmx_anims = bongocat::move(other.dmx_anims);
            pen_anims = bongocat::move(other.pen_anims);
            pen20_anims = bongocat::move(other.pen20_anims);
            dmall_anims = bongocat::move(other.dmall_anims);
            min_dm_anims = bongocat::move(other.min_dm_anims);
            ms_anims = bongocat::move(other.ms_anims);
            pkmn_anims = bongocat::move(other.pkmn_anims);
            misc_anims = bongocat::move(other.misc_anims);
            pmd_anims = bongocat::move(other.pmd_anims);

            anim = bongocat::move(other.anim);

            cleanup_animation(other.anim);
            platform::release_allocated_mmap_array(other.bongocat_anims);
            platform::release_allocated_mmap_array(other.dm_anims);
            platform::release_allocated_mmap_array(other.dm20_anims);
            platform::release_allocated_mmap_array(other.dmc_anims);
            platform::release_allocated_mmap_array(other.dmx_anims);
            platform::release_allocated_mmap_array(other.pen_anims);
            platform::release_allocated_mmap_array(other.pen20_anims);
            platform::release_allocated_mmap_array(other.dmall_anims);
            platform::release_allocated_mmap_array(other.min_dm_anims);
            platform::release_allocated_mmap_array(other.ms_anims);
            platform::release_allocated_mmap_array(other.pkmn_anims);
            platform::release_allocated_mmap_array(other.misc_anims);
            platform::release_allocated_mmap_array(other.pmd_anims);

            other.anim_type = config::config_animation_sprite_sheet_layout_t::None;
            other.anim_dm_set = config::config_animation_dm_set_t::None;
            other.anim_custom_set = config::config_animation_custom_set_t::None;
            other.anim_index = 0;
            other.animation_player_result = {};
        }
        animation_shared_memory_t& operator=(animation_shared_memory_t&& other) noexcept {
            if (this != &other) {
                animation_player_result = other.animation_player_result;
                anim_index = other.anim_index;
                anim_type = other.anim_type;
                anim_dm_set = other.anim_dm_set;
                anim_custom_set = other.anim_custom_set;

                bongocat_anims = bongocat::move(other.bongocat_anims);
                dm_anims = bongocat::move(other.dm_anims);
                dm20_anims = bongocat::move(other.dm20_anims);
                dmc_anims = bongocat::move(other.dmc_anims);
                dmx_anims = bongocat::move(other.dmx_anims);
                pen_anims = bongocat::move(other.pen_anims);
                pen20_anims = bongocat::move(other.pen20_anims);
                dmall_anims = bongocat::move(other.dmall_anims);
                min_dm_anims = bongocat::move(other.min_dm_anims);
                ms_anims = bongocat::move(other.ms_anims);
                pkmn_anims = bongocat::move(other.pkmn_anims);
                misc_anims = bongocat::move(other.misc_anims);
                pmd_anims = bongocat::move(other.pmd_anims);

                anim = bongocat::move(other.anim);

                cleanup_animation(other.anim);
                platform::release_allocated_mmap_array(other.bongocat_anims);
                platform::release_allocated_mmap_array(other.dm_anims);
                platform::release_allocated_mmap_array(other.dm20_anims);
                platform::release_allocated_mmap_array(other.dmc_anims);
                platform::release_allocated_mmap_array(other.dmx_anims);
                platform::release_allocated_mmap_array(other.pen_anims);
                platform::release_allocated_mmap_array(other.pen20_anims);
                platform::release_allocated_mmap_array(other.dmall_anims);
                platform::release_allocated_mmap_array(other.min_dm_anims);
                platform::release_allocated_mmap_array(other.ms_anims);
                platform::release_allocated_mmap_array(other.pkmn_anims);
                platform::release_allocated_mmap_array(other.misc_anims);
                platform::release_allocated_mmap_array(other.pmd_anims);

                other.anim_type = config::config_animation_sprite_sheet_layout_t::None;
                other.anim_dm_set = config::config_animation_dm_set_t::None;
                other.anim_custom_set = config::config_animation_custom_set_t::None;
                other.anim_index = 0;
                other.animation_player_result = {};
            }
            return *this;
        }
    };
}

#endif // BONGOCAT_ANIMATION_SHARED_MEMORY_H