#pragma once

#include "core/bongocat.h"
#include "graphics/sprite_sheet.h"
#include "embedded_assets/embedded_image.h"
#include "embedded_assets/custom/custom_sprite.h"

namespace bongocat::animation {
    struct animation_context_t;
    [[nodiscard]] created_result_t<custom_sprite_sheet_t> load_custom_anim(const animation_context_t& ctx, const assets::embedded_image_t& sprite_sheet_image, const assets::custom_animation_columns_t& sprite_sheet_settings);
}
