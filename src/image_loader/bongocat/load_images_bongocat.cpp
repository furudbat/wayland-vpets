#include "graphics/drawing.h"
#include "graphics/animation_context.h"
#include "graphics/animation.h"
#include "utils/memory.h"
#include "image_loader/load_images.h"
#include "embedded_assets/bongocat/bongocat.hpp"
#include "embedded_assets/bongocat/bongocat.h"
#include <cassert>


namespace bongocat::animation {
    created_result_t<bongocat_animation_t> load_bongocat_anim(int anim_index, get_sprite_callback_t get_sprite, size_t embedded_images_count) {
        BONGOCAT_LOG_VERBOSE("Load bongocat Animation(index=%d) ...", anim_index);
        auto result = anim_sprite_sheet_from_embedded_images(get_sprite, embedded_images_count);
        if (result.error != bongocat_error_t::BONGOCAT_SUCCESS) {
            return result.error;
        }

        bongocat_animation_t ret;
        ret.image = bongocat::move(result.result.image);
        ret.frame_width = bongocat::move(result.result.frame_width);
        ret.frame_height = bongocat::move(result.result.frame_height);
        ret.total_frames = bongocat::move(result.result.total_frames);
        ret.both_up = bongocat::move(result.result.frames[0]);
        ret.left_down = bongocat::move(result.result.frames[1]);
        ret.right_down = bongocat::move(result.result.frames[2]);
        ret.both_down = bongocat::move(result.result.frames[3]);

        return ret;
    }

    bongocat_error_t init_bongocat_anim(animation_context_t& ctx, int anim_index, get_sprite_callback_t get_sprite, size_t embedded_images_count) {
        using namespace assets;
        BONGOCAT_CHECK_NULL(ctx.shm.ptr, bongocat_error_t::BONGOCAT_ERROR_INVALID_PARAM);
        BONGOCAT_CHECK_NULL(ctx._local_copy_config.ptr, bongocat_error_t::BONGOCAT_ERROR_INVALID_PARAM);

        assert(anim_index >= 0 && static_cast<size_t>(anim_index) < BONGOCAT_ANIM_COUNT);
        BONGOCAT_LOG_VERBOSE("Load bongocat Animation (%d/%d): %s ...", anim_index, BONGOCAT_ANIM_COUNT, get_sprite(embedded_images_count).name);
        auto result = load_bongocat_anim(anim_index, get_sprite, embedded_images_count);
        if (result.error != bongocat_error_t::BONGOCAT_SUCCESS) {
            BONGOCAT_LOG_ERROR("Load bongocat Animation failed: index: %d", anim_index);
            return result.error;
        }
        assert(result.result.total_frames > 0); ///< this SHOULD always work if it's an valid EMBEDDED image
        assert(MAX_NUM_FRAMES <= INT_MAX);
        assert(result.result.total_frames <= static_cast<int>(MAX_NUM_FRAMES));
        if (result.result.total_frames > static_cast<int>(MAX_NUM_FRAMES)) {
            BONGOCAT_LOG_ERROR("Sprite Sheet does not fit in out_frames: %d, total_frames: %d", MAX_NUM_FRAMES, result.result.total_frames);
            return bongocat_error_t::BONGOCAT_ERROR_INVALID_PARAM;
        }

        assert(anim_index >= 0);
        ctx.shm->bongocat_anims[static_cast<size_t>(anim_index)].bongocat = bongocat::move(result.result);

        return bongocat_error_t::BONGOCAT_SUCCESS;
    }

    created_result_t<bongocat_animation_t> load_bongocat_sprite_sheet(const animation_context_t& /*ctx*/, int index) {
        using namespace assets;
        using namespace animation;
        switch (index) {
            case BONGOCAT_ANIM_INDEX: return load_bongocat_anim(BONGOCAT_ANIM_INDEX, get_bongocat_sprite, BONGOCAT_EMBEDDED_IMAGES_COUNT);
            default: return bongocat_error_t::BONGOCAT_ERROR_INVALID_PARAM;
        }
        return bongocat_error_t::BONGOCAT_ERROR_INVALID_PARAM;
    }
}
