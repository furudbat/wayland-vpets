#include "image_loader/custom/load_custom.h"
#include "graphics/animation_context.h"
#include "image_loader/load_images.h"

namespace bongocat::animation {

    created_result_t<custom_sprite_sheet_t> load_custom_anim(const animation_context_t& ctx, const assets::embedded_image_t& sprite_sheet_image, const assets::custom_animation_columns_t& sprite_sheet_settings) {
        using namespace assets;
        BONGOCAT_CHECK_NULL(ctx._local_copy_config.ptr, bongocat_error_t::BONGOCAT_ERROR_INVALID_PARAM);

        int sprite_sheet_cols{0};
        int sprite_sheet_rows{0};

        // detect sprite sheet cols
        sprite_sheet_cols = sprite_sheet_settings.idle_frames;

        if (sprite_sheet_settings.boring_frames >= sprite_sheet_cols) sprite_sheet_cols = sprite_sheet_settings.boring_frames;

        if (sprite_sheet_settings.start_writing_frames >= sprite_sheet_cols) sprite_sheet_cols = sprite_sheet_settings.start_writing_frames;
        if (sprite_sheet_settings.writing_frames >= sprite_sheet_cols) sprite_sheet_cols = sprite_sheet_settings.writing_frames;
        if (sprite_sheet_settings.end_writing_frames >= sprite_sheet_cols) sprite_sheet_cols = sprite_sheet_settings.end_writing_frames;
        if (sprite_sheet_settings.happy_frames >= sprite_sheet_cols) sprite_sheet_cols = sprite_sheet_settings.happy_frames;

        if (sprite_sheet_settings.asleep_frames >= sprite_sheet_cols) sprite_sheet_cols = sprite_sheet_settings.asleep_frames;
        if (sprite_sheet_settings.sleep_frames >= sprite_sheet_cols) sprite_sheet_cols = sprite_sheet_settings.sleep_frames;
        if (sprite_sheet_settings.wake_up_frames >= sprite_sheet_cols) sprite_sheet_cols = sprite_sheet_settings.wake_up_frames;

        if (sprite_sheet_settings.start_working_frames >= sprite_sheet_cols) sprite_sheet_cols = sprite_sheet_settings.start_working_frames;
        if (sprite_sheet_settings.working_frames >= sprite_sheet_cols) sprite_sheet_cols = sprite_sheet_settings.working_frames;
        if (sprite_sheet_settings.end_working_frames >= sprite_sheet_cols) sprite_sheet_cols = sprite_sheet_settings.end_working_frames;

        if (sprite_sheet_settings.start_moving_frames >= sprite_sheet_cols) sprite_sheet_cols = sprite_sheet_settings.start_moving_frames;
        if (sprite_sheet_settings.moving_frames >= sprite_sheet_cols) sprite_sheet_cols = sprite_sheet_settings.moving_frames;
        if (sprite_sheet_settings.end_moving_frames >= sprite_sheet_cols) sprite_sheet_cols = sprite_sheet_settings.end_moving_frames;

        // detect sprite sheet rows
        if (sprite_sheet_settings.idle_frames > 0) sprite_sheet_rows++;
        if (sprite_sheet_settings.boring_frames > 0) sprite_sheet_rows++;

        if (sprite_sheet_settings.start_writing_frames > 0) sprite_sheet_rows++;
        if (sprite_sheet_settings.writing_frames > 0) sprite_sheet_rows++;
        if (sprite_sheet_settings.end_writing_frames > 0) sprite_sheet_rows++;
        if (sprite_sheet_settings.happy_frames > 0) sprite_sheet_rows++;

        if (sprite_sheet_settings.asleep_frames > 0) sprite_sheet_rows++;
        if (sprite_sheet_settings.sleep_frames > 0) sprite_sheet_rows++;
        if (sprite_sheet_settings.wake_up_frames > 0) sprite_sheet_rows++;

        if (sprite_sheet_settings.start_working_frames > 0) sprite_sheet_rows++;
        if (sprite_sheet_settings.working_frames > 0) sprite_sheet_rows++;
        if (sprite_sheet_settings.end_working_frames > 0) sprite_sheet_rows++;

        if (sprite_sheet_settings.start_moving_frames > 0) sprite_sheet_rows++;
        if (sprite_sheet_settings.moving_frames > 0) sprite_sheet_rows++;
        if (sprite_sheet_settings.end_moving_frames > 0) sprite_sheet_rows++;

        if (sprite_sheet_cols == 0 || sprite_sheet_rows == 0) [[unlikely]] {
            BONGOCAT_LOG_ERROR("Load custom Animation failed, no cols and rows: %s; %i, %i", sprite_sheet_image.name, sprite_sheet_cols, sprite_sheet_rows);
            return bongocat_error_t::BONGOCAT_ERROR_ANIMATION;
        }

        auto result = load_sprite_sheet_anim(*ctx._local_copy_config, sprite_sheet_image, sprite_sheet_cols, sprite_sheet_rows);
        if (result.error != bongocat_error_t::BONGOCAT_SUCCESS) [[unlikely]] {
            BONGOCAT_LOG_ERROR("Load custom Animation failed: %s", sprite_sheet_image.name);
            return bongocat_error_t::BONGOCAT_ERROR_ANIMATION;
        }

        custom_sprite_sheet_t ret;
        ret.image = bongocat::move(result.result.image);
        ret.frame_width = bongocat::move(result.result.frame_width);
        ret.frame_height = bongocat::move(result.result.frame_height);

        // setup animations
        {
            int row = 0;

            if (sprite_sheet_settings.idle_frames > 0) {
                ret.idle = { .valid = true, .start_col = 0, .end_col = sprite_sheet_settings.idle_frames-1, .row = row };
                row++;
            }

            if (sprite_sheet_settings.boring_frames > 0) {
                ret.boring = { .valid = true, .start_col = 0, .end_col = sprite_sheet_settings.boring_frames-1, .row = row };
                row++;
            }

            if (sprite_sheet_settings.start_writing_frames > 0) {
                ret.start_writing = { .valid = true, .start_col = 0, .end_col = sprite_sheet_settings.start_writing_frames-1, .row = row };
                row++;
            }
            if (sprite_sheet_settings.writing_frames > 0) {
                ret.writing = { .valid = true, .start_col = 0, .end_col = sprite_sheet_settings.writing_frames-1, .row = row };
                row++;
            }
            if (sprite_sheet_settings.end_writing_frames > 0) {
                ret.end_writing = { .valid = true, .start_col = 0, .end_col = sprite_sheet_settings.end_writing_frames-1, .row = row };
                row++;
            }

            if (sprite_sheet_settings.happy_frames > 0) {
                ret.happy = { .valid = true, .start_col = 0, .end_col = sprite_sheet_settings.happy_frames-1, .row = row };
                row++;
            }

            if (sprite_sheet_settings.asleep_frames > 0) {
                ret.fall_asleep = { .valid = true, .start_col = 0, .end_col = sprite_sheet_settings.asleep_frames-1, .row = row };
                row++;
            }
            if (sprite_sheet_settings.sleep_frames > 0) {
                ret.sleep = { .valid = true, .start_col = 0, .end_col = sprite_sheet_settings.sleep_frames-1, .row = row };
                row++;
            }
            if (sprite_sheet_settings.wake_up_frames > 0) {
                ret.wake_up = { .valid = true, .start_col = 0, .end_col = sprite_sheet_settings.wake_up_frames-1, .row = row };
                row++;
            }

            if (sprite_sheet_settings.start_working_frames > 0) {
                ret.start_working = { .valid = true, .start_col = 0, .end_col = sprite_sheet_settings.start_working_frames-1, .row = row };
                row++;
            }
            if (sprite_sheet_settings.working_frames > 0) {
                ret.working = { .valid = true, .start_col = 0, .end_col = sprite_sheet_settings.working_frames-1, .row = row };
                row++;
            }
            if (sprite_sheet_settings.end_working_frames > 0) {
                ret.end_working = { .valid = true, .start_col = 0, .end_col = sprite_sheet_settings.end_working_frames-1, .row = row };
                row++;
            }

            if (sprite_sheet_settings.start_moving_frames > 0) {
                ret.start_moving = { .valid = true, .start_col = 0, .end_col = sprite_sheet_settings.start_moving_frames-1, .row = row };
                row++;
            }
            if (sprite_sheet_settings.moving_frames > 0) {
                ret.moving = { .valid = true, .start_col = 0, .end_col = sprite_sheet_settings.moving_frames-1, .row = row };
                row++;
            }
            if (sprite_sheet_settings.end_moving_frames > 0) {
                ret.end_moving = { .valid = true, .start_col = 0, .end_col = sprite_sheet_settings.end_moving_frames-1, .row = row };
                row++;
            }
        }

        // features
        ret.feature_idle = ret.idle.valid;
        ret.feature_boring = ret.boring.valid;
        ret.feature_writing = ret.writing.valid || ret.start_writing.valid || ret.end_writing.valid;
        ret.feature_writing_happy = ret.feature_writing && ret.happy.valid;
        ret.feature_sleep = ret.sleep.valid || ret.fall_asleep.valid;
        ret.feature_sleep_wake_up = ret.feature_sleep && ret.wake_up.valid;
        ret.feature_working = ret.working.valid || ret.start_working.valid || ret.end_working.valid;
        ret.feature_moving = ret.moving.valid || ret.start_moving.valid || ret.end_moving.valid;
        // is feature_toggle_writing_frames enabled or writing has only 2 frames (default)
        ret.feature_writing_toggle_frames = ret.working.valid && (sprite_sheet_settings.feature_toggle_writing_frames >= 1 || (sprite_sheet_settings.feature_toggle_writing_frames < 0 && !ret.start_moving.valid && !ret.end_working.valid && ret.working.valid && sprite_sheet_settings.working_frames == 2));

        if (!ret.feature_idle) [[unlikely]] {
            BONGOCAT_LOG_WARNING("Custom Animation without idle animation: %s", sprite_sheet_image.name);
        }

        return ret;
    }

}
