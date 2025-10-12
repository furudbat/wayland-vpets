#include "load_images_pen.h"
#include "embedded_assets/pen/pen.hpp"
#include "graphics/animation_context.h"
#include "image_loader/load_images.h"
#include "image_loader/base_dm/load_dm.h"

namespace bongocat::animation {
bongocat_error_t init_pen_anim(animation_context_t& ctx, int anim_index, const assets::embedded_image_t& sprite_sheet_image, int sprite_sheet_cols, int sprite_sheet_rows) {
    using namespace assets;
    BONGOCAT_CHECK_NULL(ctx.shm.ptr, bongocat_error_t::BONGOCAT_ERROR_INVALID_PARAM);
    BONGOCAT_CHECK_NULL(ctx._local_copy_config.ptr, bongocat_error_t::BONGOCAT_ERROR_INVALID_PARAM);

    assert(anim_index >= 0 && static_cast<size_t>(anim_index) < PEN_ANIM_COUNT);
    BONGOCAT_LOG_VERBOSE("Load pen Animation (%d/%d): %s ...", anim_index, PEN_ANIM_COUNT, sprite_sheet_image.name);
    auto result = load_dm_anim(ctx, anim_index, sprite_sheet_image, sprite_sheet_cols, sprite_sheet_rows);
    if (result.error != bongocat_error_t::BONGOCAT_SUCCESS) [[unlikely]] {
        BONGOCAT_LOG_ERROR("Load pen Animation failed: %s, index: %d", sprite_sheet_image.name, anim_index);
        return bongocat_error_t::BONGOCAT_ERROR_ANIMATION;
    }
    assert(result.result.total_frames > 0); ///< this SHOULD always work if it's an valid EMBEDDED image

    assert(anim_index >= 0);
    ctx.shm->pen_anims[static_cast<size_t>(anim_index)].dm = bongocat::move(result.result);

    return bongocat_error_t::BONGOCAT_SUCCESS;
}
}
