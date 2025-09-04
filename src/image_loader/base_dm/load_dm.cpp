#include "image_loader/base_dm/load_dm.h"
#include "graphics/animation_context.h"
#include "image_loader/load_images.h"

namespace bongocat::animation {

    created_result_t<dm_animation_t> load_dm_anim(const animation_context_t& ctx, int anim_index, const assets::embedded_image_t& sprite_sheet_image, int sprite_sheet_cols, int sprite_sheet_rows) {
        using namespace assets;
        BONGOCAT_CHECK_NULL(ctx._local_copy_config.ptr, bongocat_error_t::BONGOCAT_ERROR_INVALID_PARAM);

        auto result = load_sprite_sheet_anim(*ctx._local_copy_config, sprite_sheet_image, sprite_sheet_cols, sprite_sheet_rows);
        if (result.error != bongocat_error_t::BONGOCAT_SUCCESS) {
            BONGOCAT_LOG_ERROR("Load dm Animation failed: %s, index: %d", sprite_sheet_image.name, anim_index);
            return bongocat_error_t::BONGOCAT_ERROR_ANIMATION;
        }
        assert(result.result.total_frames > 0); ///< this SHOULD always work if it's an valid EMBEDDED image
        assert(MAX_NUM_FRAMES <= INT_MAX);
        assert(result.result.total_frames <= static_cast<int>(MAX_NUM_FRAMES));
        if (result.result.total_frames > static_cast<int>(MAX_NUM_FRAMES)) {
            BONGOCAT_LOG_ERROR("Sprite Sheet does not fit in out_frames: %d, total_frames: %d", MAX_NUM_FRAMES, result.result.total_frames);
            return bongocat_error_t::BONGOCAT_ERROR_INVALID_PARAM;
        }

        dm_animation_t ret;
        ret.image = bongocat::move(result.result.image);
        ret.frame_width = bongocat::move(result.result.frame_width);
        ret.frame_height = bongocat::move(result.result.frame_height);
        ret.total_frames = bongocat::move(result.result.total_frames);
        ret.idle_1 = bongocat::move(result.result.frames[0]);
        ret.idle_2 = bongocat::move(result.result.frames[1]);
        ret.angry = bongocat::move(result.result.frames[2]);
        ret.down1 = bongocat::move(result.result.frames[3]);
        ret.happy = bongocat::move(result.result.frames[4]);
        ret.eat1 = bongocat::move(result.result.frames[5]);
        ret.sleep1 = bongocat::move(result.result.frames[6]);
        ret.refuse = bongocat::move(result.result.frames[7]);
        ret.sad = bongocat::move(result.result.frames[8]);

        ret.down_2 = bongocat::move(result.result.frames[9]);
        ret.eat_2 = bongocat::move(result.result.frames[10]);
        ret.sleep_2 = bongocat::move(result.result.frames[11]);
        ret.attack = bongocat::move(result.result.frames[12]);

        ret.movement_1 = bongocat::move(result.result.frames[13]);
        ret.movement_2 = bongocat::move(result.result.frames[14]);

        return ret;
    }

}
