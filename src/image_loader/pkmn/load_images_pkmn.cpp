#include "load_images_pkmn.h"
#include "graphics/animation_context.h"
#include "image_loader/base_dm/load_dm.h"
#include "embedded_assets/embedded_image.h"
#include "embedded_assets/pkmn/pkmn.hpp"
#include "image_loader/load_images.h"
#include "utils/error.h"

namespace bongocat::animation {
    created_result_t<pkmn_sprite_sheet_t> load_pkmn_anim(const animation_context_t& ctx, [[maybe_unused]] int anim_index, const assets::embedded_image_t& sprite_sheet_image, int sprite_sheet_cols, int sprite_sheet_rows) {
        using namespace assets;
        BONGOCAT_CHECK_NULL(ctx._local_copy_config.ptr, bongocat_error_t::BONGOCAT_ERROR_INVALID_PARAM);

        auto result = load_sprite_sheet_anim(*ctx._local_copy_config, sprite_sheet_image, sprite_sheet_cols, sprite_sheet_rows);
        if (result.error != bongocat_error_t::BONGOCAT_SUCCESS) {
            BONGOCAT_LOG_ERROR("Load pkmn Animation failed: %s, index: %d", sprite_sheet_image.name, anim_index);
            return bongocat_error_t::BONGOCAT_ERROR_ANIMATION;
        }
        assert(result.result.total_frames > 0); ///< this SHOULD always work if it's an valid EMBEDDED image
        assert(MAX_NUM_FRAMES <= INT_MAX);
        assert(result.result.total_frames <= static_cast<int>(MAX_NUM_FRAMES));
        if (result.result.total_frames > static_cast<int>(MAX_NUM_FRAMES)) {
            BONGOCAT_LOG_ERROR("Sprite Sheet does not fit in out_frames: %d, total_frames: %d", MAX_NUM_FRAMES, result.result.total_frames);
            return bongocat_error_t::BONGOCAT_ERROR_INVALID_PARAM;
        }

        pkmn_sprite_sheet_t ret;
        ret.image = bongocat::move(result.result.image);
        ret.frame_width = bongocat::move(result.result.frame_width);
        ret.frame_height = bongocat::move(result.result.frame_height);
        ret.total_frames = bongocat::move(result.result.total_frames);

        ret.idle_1 = bongocat::move(result.result.frames[0]);
        ret.idle_2 = bongocat::move(result.result.frames[1]);

        // setup animations
        using namespace assets;

        assert(ret.idle_1.valid);
        assert(ret.idle_2.valid);

        assert(MAX_ANIMATION_FRAMES >= 4);

        ret.animations.idle[0] = ret.idle_1.col;
        ret.animations.idle[1] = ret.idle_2.col;
        ret.animations.idle[2] = ret.idle_1.col;
        ret.animations.idle[3] = ret.idle_2.col;

        ret.animations.boring[0] = ret.idle_1.col;
        ret.animations.boring[1] = ret.idle_2.col;
        ret.animations.boring[2] = ret.idle_1.col;
        ret.animations.boring[3] = ret.idle_2.col;

        ret.animations.writing[0] = ret.idle_1.col;
        ret.animations.writing[1] = ret.idle_2.col;
        ret.animations.writing[2] = ret.idle_1.col;
        ret.animations.writing[3] = ret.idle_2.col;

        ret.animations.sleep[0] = ret.idle_2.col;
        ret.animations.sleep[1] = ret.idle_2.col;
        ret.animations.sleep[2] = ret.idle_2.col;
        ret.animations.sleep[3] = ret.idle_2.col;

        ret.animations.wake_up[0] = ret.idle_1.col;
        ret.animations.wake_up[1] = ret.idle_2.col;
        ret.animations.wake_up[2] = ret.idle_1.col;
        ret.animations.wake_up[3] = ret.idle_2.col;

        ret.animations.working[0] = ret.idle_1.col;
        ret.animations.working[1] = ret.idle_2.col;
        ret.animations.working[2] = ret.idle_1.col;
        ret.animations.working[3] = ret.idle_2.col;

        ret.animations.moving[0] = ret.idle_1.col;
        ret.animations.moving[1] = ret.idle_2.col;
        ret.animations.moving[2] = ret.idle_1.col;
        ret.animations.moving[3] = ret.idle_2.col;

        ret.animations.happy[0] = ret.idle_1.col;
        ret.animations.happy[1] = ret.idle_2.col;
        ret.animations.happy[2] = ret.idle_1.col;
        ret.animations.happy[3] = ret.idle_2.col;

        return ret;
    }

    bongocat_error_t init_pkmn_anim(animation_context_t& ctx, int anim_index, const assets::embedded_image_t& sprite_sheet_image, int sprite_sheet_cols, int sprite_sheet_rows) {
        using namespace assets;
        BONGOCAT_CHECK_NULL(ctx.shm.ptr, bongocat_error_t::BONGOCAT_ERROR_INVALID_PARAM);
        BONGOCAT_CHECK_NULL(ctx._local_copy_config.ptr, bongocat_error_t::BONGOCAT_ERROR_INVALID_PARAM);

        assert(anim_index >= 0 && static_cast<size_t>(anim_index) < PKMN_ANIM_COUNT);
        BONGOCAT_LOG_VERBOSE("Load pkmn Animation (%d/%d): %s ...", anim_index, PKMN_ANIM_COUNT, sprite_sheet_image.name);
        auto result = load_pkmn_anim(ctx, anim_index, sprite_sheet_image, sprite_sheet_cols, sprite_sheet_rows);
        if (result.error != bongocat_error_t::BONGOCAT_SUCCESS) {
            BONGOCAT_LOG_ERROR("Load pkmn Animation failed: %s, index: %d", sprite_sheet_image.name, anim_index);
            return bongocat_error_t::BONGOCAT_ERROR_ANIMATION;
        }
        assert(result.result.total_frames > 0); ///< this SHOULD always work if it's an valid EMBEDDED image

        assert(anim_index >= 0);
        ctx.shm->pkmn_anims[static_cast<size_t>(anim_index)].pkmn = bongocat::move(result.result);

        return bongocat_error_t::BONGOCAT_SUCCESS;
    }
}