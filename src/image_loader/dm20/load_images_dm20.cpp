#include "load_images_dm20.h"
#include "graphics/animation_thread_context.h"
#include "image_loader/base_dm/load_dm.h"
#include "embedded_assets/embedded_image.h"
#include "embedded_assets/dm20/dm20.hpp"

namespace bongocat::animation {
    bongocat_error_t init_dm20_anim(animation_thread_context_t& ctx, int anim_index, const assets::embedded_image_t& sprite_sheet_image, int sprite_sheet_cols, int sprite_sheet_rows) {
        using namespace assets;
        BONGOCAT_CHECK_NULL(ctx.shm.ptr, bongocat_error_t::BONGOCAT_ERROR_INVALID_PARAM);
        BONGOCAT_CHECK_NULL(ctx._local_copy_config.ptr, bongocat_error_t::BONGOCAT_ERROR_INVALID_PARAM);

        assert(anim_index >= 0 && static_cast<size_t>(anim_index) < DM20_ANIM_COUNT);
        BONGOCAT_LOG_VERBOSE("Load dm20 Animation (%d/%d): %s ...", anim_index, DM20_ANIM_COUNT, sprite_sheet_image.name);
        auto result = load_dm_anim(ctx, anim_index, sprite_sheet_image, sprite_sheet_cols, sprite_sheet_rows);
        if (result.error != bongocat_error_t::BONGOCAT_SUCCESS) {
            BONGOCAT_LOG_ERROR("Load dm20 Animation failed: %s, index: %d", sprite_sheet_image.name, anim_index);
            return bongocat_error_t::BONGOCAT_ERROR_ANIMATION;
        }
        assert(result.result.total_frames > 0); ///< this SHOULD always work if it's an valid EMBEDDED image

        assert(anim_index >= 0);
        ctx.shm->dm20_anims[static_cast<size_t>(anim_index)] = bongocat::move(result.result);
        assert(ctx.shm->dm20_anims[static_cast<size_t>(anim_index)].type == animation_t::type_t::Dm);

        return bongocat_error_t::BONGOCAT_SUCCESS;
    }
}
