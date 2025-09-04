#pragma once

#include "core/bongocat.h"
#include "graphics/sprite_sheet.h"
#include "embedded_assets/embedded_image.h"

namespace bongocat::animation {
    struct animation_context_t;
    created_result_t<ms_agent_sprite_sheet_t> load_ms_agent_sprite_sheet(const config::config_t& config, const assets::embedded_image_t& sprite_sheet_image, int sprite_sheet_cols, int sprite_sheet_rows);
    created_result_t<ms_agent_sprite_sheet_t> load_ms_agent_anim(const animation_context_t& ctx, int anim_index, const assets::embedded_image_t& sprite_sheet_image, int sprite_sheet_cols, int sprite_sheet_rows);
    created_result_t<ms_agent_sprite_sheet_t> init_ms_agent_anim(animation_context_t& ctx, int anim_index, const assets::embedded_image_t& sprite_sheet_image, int sprite_sheet_cols, int sprite_sheet_rows);

    created_result_t<ms_agent_sprite_sheet_t> load_ms_agent_sprite_sheet(const animation_context_t& ctx, int index);
}
