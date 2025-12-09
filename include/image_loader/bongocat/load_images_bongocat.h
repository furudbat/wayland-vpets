#pragma once

#include "core/bongocat.h"
#include "graphics/sprite_sheet.h"
#include "image_loader/load_images.h"

namespace bongocat::animation {
struct animation_context_t;
[[nodiscard]] created_result_t<bongocat_sprite_sheet_t>
load_bongocat_anim(int anim_index, get_sprite_callback_t get_sprite, size_t embedded_images_count);
bongocat_error_t init_bongocat_anim(animation_context_t& ctx, int anim_index, get_sprite_callback_t get_sprite,
                                    size_t embedded_images_count);

[[nodiscard]] created_result_t<bongocat_sprite_sheet_t> load_bongocat_sprite_sheet(const animation_context_t& /*ctx*/,
                                                                                   int index);
}  // namespace bongocat::animation
