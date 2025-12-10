#pragma once

#include "core/bongocat.h"
#include "graphics/sprite_sheet.h"
#include "embedded_assets/embedded_image.h"
#include "embedded_assets/custom/custom_sprite.h"

namespace bongocat::animation {
    struct animation_thread_context_t;
    bongocat_error_t init_pmd_anim(animation_thread_context_t& ctx, int anim_index, const assets::embedded_image_t& sprite_sheet_image, const assets::custom_animation_settings_t& sprite_sheet_settings);

    [[nodiscard]] created_result_t<custom_sprite_sheet_t> load_pmd_sprite_sheet(const animation_thread_context_t& ctx, int index);
}
