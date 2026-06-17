#pragma once

#include "core/bongocat.h"
#include "graphics/sprite_sheet.h"
#include "embedded_assets/embedded_image.h"

namespace bongocat::animation {
    struct animation_thread_context_t;
    BONGOCAT_NODISCARD created_result_t<pkmn_sprite_sheet_t> load_pkmn_anim(const animation_thread_context_t& ctx, size_t anim_index, const assets::embedded_image_t& sprite_sheet_image, int sprite_sheet_cols, int sprite_sheet_rows);

    bongocat_error_t init_pkmn_anim(animation_thread_context_t& ctx, size_t anim_index, const assets::embedded_image_t& sprite_sheet_image, int sprite_sheet_cols, int sprite_sheet_rows);

    BONGOCAT_NODISCARD created_result_t<pkmn_sprite_sheet_t> load_pkmn_sprite_sheet(const animation_thread_context_t& ctx, size_t index);
}
