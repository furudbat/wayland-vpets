#pragma once

#include "core/bongocat.h"
#include "embedded_assets/embedded_image.h"
#include "embedded_assets/ms_agent/ms_agent_sprite.h"
#include "graphics/sprite_sheet.h"

namespace bongocat::animation {
struct animation_context_t;
BONGOCAT_NODISCARD created_result_t<ms_agent_sprite_sheet_t>
load_ms_agent_sprite_sheet(const config::config_t& config, const assets::embedded_image_t& sprite_sheet_image,
                           int sprite_sheet_cols, int sprite_sheet_rows);
BONGOCAT_NODISCARD created_result_t<ms_agent_sprite_sheet_t>
load_ms_agent_anim(const animation_context_t& ctx, int anim_index, const assets::embedded_image_t& sprite_sheet_image,
                   int sprite_sheet_cols, int sprite_sheet_rows,
                   const assets::ms_agent_animation_indices_t& animation_data);
created_result_t<ms_agent_sprite_sheet_t>
init_ms_agent_anim(animation_context_t& ctx, int anim_index, const assets::embedded_image_t& sprite_sheet_image,
                   int sprite_sheet_cols, int sprite_sheet_rows,
                   const assets::ms_agent_animation_indices_t& animation_data);

BONGOCAT_NODISCARD created_result_t<ms_agent_sprite_sheet_t> load_ms_agent_sprite_sheet(const animation_context_t& ctx,
                                                                                        int index);
}  // namespace bongocat::animation
