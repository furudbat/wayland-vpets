#pragma once

#include "core/bongocat.h"
#include "graphics/sprite_sheet.h"
#include "embedded_assets/embedded_image.h"

namespace bongocat::animation {
    struct animation_context_t;
    bongocat_error_t init_min_dm_anim(animation_context_t& ctx, int anim_index, const assets::embedded_image_t& sprite_sheet_image, int sprite_sheet_cols, int sprite_sheet_rows);

    [[nodiscard]] created_result_t<dm_animation_t> load_min_dm_sprite_sheet(const animation_context_t& ctx, int index);
}
