#pragma once

#include "core/bongocat.h"
#include "embedded_assets/embedded_image.h"
#include "graphics/sprite_sheet.h"

namespace bongocat::animation {

struct load_dm_anim_options_t {
  bool sleep_in_bed{false};
};
void patch_dm_anim(dm_sprite_sheet_t& ret, load_dm_anim_options_t options);

struct animation_thread_context_t;
BONGOCAT_NODISCARD created_result_t<dm_sprite_sheet_t> load_dm_anim(const animation_thread_context_t& ctx, int anim_index,
                                                                    const assets::embedded_image_t& sprite_sheet_image,
                                                                    int sprite_sheet_cols, int sprite_sheet_rows,
                                                                    load_dm_anim_options_t options = {});
}  // namespace bongocat::animation
