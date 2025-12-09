#include "load_images_pmd.h"
#include "graphics/animation_thread_context.h"
#include "image_loader/custom/load_custom.h"
#include "embedded_assets/embedded_image.h"
#include "embedded_assets/pmd/pmd.hpp"

namespace bongocat::animation {
    bongocat_error_t init_pmd_anim(animation_thread_context_t& ctx, int anim_index, const assets::embedded_image_t& sprite_sheet_image, const assets::custom_animation_settings_t& sprite_sheet_settings) {
        using namespace assets;
        BONGOCAT_CHECK_NULL(ctx.shm.ptr, bongocat_error_t::BONGOCAT_ERROR_INVALID_PARAM);
        BONGOCAT_CHECK_NULL(ctx._local_copy_config.ptr, bongocat_error_t::BONGOCAT_ERROR_INVALID_PARAM);

        assert(anim_index >= 0 && static_cast<size_t>(anim_index) < PMD_ANIM_COUNT);
        BONGOCAT_LOG_VERBOSE("Load pmd Animation (%d/%d): %s ...", anim_index, PMD_ANIM_COUNT, sprite_sheet_image.name);
        auto result = load_custom_anim(ctx, sprite_sheet_image, sprite_sheet_settings);
        if (result.error != bongocat_error_t::BONGOCAT_SUCCESS) [[unlikely]] {
            BONGOCAT_LOG_ERROR("Load pmd Animation failed: %s, index: %d", sprite_sheet_image.name, anim_index);
            return bongocat_error_t::BONGOCAT_ERROR_ANIMATION;
        }

        assert(anim_index >= 0);
        ctx.shm->pmd_anims[static_cast<size_t>(anim_index)] = bongocat::move(result.result);
        assert(ctx.shm->pmd_anims[static_cast<size_t>(anim_index)].type == animation_t::type_t::Custom);

        return bongocat_error_t::BONGOCAT_SUCCESS;
    }
}
