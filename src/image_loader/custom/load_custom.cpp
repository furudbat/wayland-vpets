#include "image_loader/custom/load_custom.h"
#include "graphics/animation_context.h"
#include "image_loader/load_images.h"

namespace bongocat::animation {

    created_result_t<assets::custom_image_t> load_custom_sprite_sheet_file(const char* filename) {
        using namespace assets;
        BONGOCAT_CHECK_NULL(filename, bongocat_error_t::BONGOCAT_ERROR_INVALID_PARAM);

        auto file_content_result = platform::make_allocated_mmap_file_content_open(filename);
        if (file_content_result.error != bongocat_error_t::BONGOCAT_SUCCESS) {
            return file_content_result.error;
        }

        assets::custom_image_t ret;
        ret.data = bongocat::move(file_content_result.result);
        ret.name = ::strdup(filename);
        return ret;
    }
    void free_custom_sprite_sheet_file(assets::custom_image_t& image) noexcept {
        platform::release_allocated_mmap_file_content(image.data);
        if (image.name) ::free(image.name);
        image.name = nullptr;
    }

    created_result_t<custom_sprite_sheet_t> load_custom_anim(const animation_context_t& ctx, const assets::custom_image_t& sprite_sheet_image, const assets::custom_animation_settings_t& sprite_sheet_settings) {
        assert(sprite_sheet_image.data._size_bytes >= 0);
        return load_custom_anim(ctx, assets::embedded_image_t{ .data = sprite_sheet_image.data.data, .size = static_cast<size_t>(sprite_sheet_image.data._size_bytes), .name = sprite_sheet_image.name ? sprite_sheet_image.name : "" }, sprite_sheet_settings);
    }
    created_result_t<custom_sprite_sheet_t> load_custom_anim(const animation_context_t& ctx, const assets::embedded_image_t& sprite_sheet_image, const assets::custom_animation_settings_t& sprite_sheet_settings) {
        using namespace assets;
        BONGOCAT_CHECK_NULL(ctx._local_copy_config.ptr, bongocat_error_t::BONGOCAT_ERROR_INVALID_PARAM);

        const int sprite_sheet_cols = get_custom_animation_settings_max_cols(sprite_sheet_settings);
        const int sprite_sheet_rows = get_custom_animation_settings_rows_count(sprite_sheet_settings);

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
        if (sprite_sheet_rows > 0) {
            int row = 0;

            if (sprite_sheet_settings.idle_frames > 0) {
                ret.idle = { .valid = true, .start_col = 0, .end_col = sprite_sheet_settings.idle_frames-1, .row = sprite_sheet_settings.idle_row_index >= 0 ? sprite_sheet_settings.idle_row_index : row };
                ret.idle.row = ret.idle.row >= 0 ? ret.idle.row : 0;
                ret.idle.row = ret.idle.row < sprite_sheet_rows ? ret.idle.row : sprite_sheet_rows-1;
                row++;
            }

            if (sprite_sheet_settings.boring_frames > 0) {
                ret.boring = { .valid = true, .start_col = 0, .end_col = sprite_sheet_settings.boring_frames-1, .row = sprite_sheet_settings.boring_row_index >= 0 ? sprite_sheet_settings.boring_row_index : row };
                ret.boring.row = ret.boring.row >= 0 ? ret.boring.row : 0;
                ret.boring.row = ret.boring.row < sprite_sheet_rows ? ret.boring.row : sprite_sheet_rows-1;
                row++;
            }

            if (sprite_sheet_settings.start_writing_frames > 0) {
                ret.start_writing = { .valid = true, .start_col = 0, .end_col = sprite_sheet_settings.start_writing_frames-1, .row = sprite_sheet_settings.start_writing_row_index >= 0 ? sprite_sheet_settings.start_writing_row_index : row };
                ret.start_writing.row = ret.start_writing.row >= 0 ? ret.start_writing.row : 0;
                ret.start_writing.row = ret.start_writing.row < sprite_sheet_rows ? ret.start_writing.row : sprite_sheet_rows-1;
                row++;
            }
            if (sprite_sheet_settings.writing_frames > 0) {
                ret.writing = { .valid = true, .start_col = 0, .end_col = sprite_sheet_settings.writing_frames-1, .row = sprite_sheet_settings.writing_row_index >= 0 ? sprite_sheet_settings.writing_row_index : row };
                ret.writing.row = ret.writing.row >= 0 ? ret.writing.row : 0;
                ret.writing.row = ret.writing.row < sprite_sheet_rows ? ret.writing.row : sprite_sheet_rows-1;
                row++;
            }
            if (sprite_sheet_settings.end_writing_frames > 0) {
                ret.end_writing = { .valid = true, .start_col = 0, .end_col = sprite_sheet_settings.end_writing_frames-1, .row = sprite_sheet_settings.end_writing_row_index >= 0 ? sprite_sheet_settings.end_writing_row_index : row };
                ret.end_writing.row = ret.end_writing.row >= 0 ? ret.end_writing.row : 0;
                ret.end_writing.row = ret.end_writing.row < sprite_sheet_rows ? ret.end_writing.row : sprite_sheet_rows-1;
                row++;
            }

            if (sprite_sheet_settings.happy_frames > 0) {
                ret.happy = { .valid = true, .start_col = 0, .end_col = sprite_sheet_settings.happy_frames-1, .row = sprite_sheet_settings.happy_row_index >= 0 ? sprite_sheet_settings.happy_row_index : row };
                ret.happy.row = ret.happy.row >= 0 ? ret.happy.row : 0;
                ret.happy.row = ret.happy.row < sprite_sheet_rows ? ret.happy.row : sprite_sheet_rows-1;
                row++;
            }

            if (sprite_sheet_settings.asleep_frames > 0) {
                ret.fall_asleep = { .valid = true, .start_col = 0, .end_col = sprite_sheet_settings.asleep_frames-1, .row = sprite_sheet_settings.asleep_row_index >= 0 ? sprite_sheet_settings.asleep_row_index : row };
                ret.fall_asleep.row = ret.fall_asleep.row >= 0 ? ret.fall_asleep.row : 0;
                ret.fall_asleep.row = ret.fall_asleep.row < sprite_sheet_rows ? ret.fall_asleep.row : sprite_sheet_rows-1;
                row++;
            }
            if (sprite_sheet_settings.sleep_frames > 0) {
                ret.sleep = { .valid = true, .start_col = 0, .end_col = sprite_sheet_settings.sleep_frames-1, .row = sprite_sheet_settings.sleep_row_index >= 0 ? sprite_sheet_settings.sleep_row_index : row };
                ret.sleep.row = ret.sleep.row >= 0 ? ret.sleep.row : 0;
                ret.sleep.row = ret.sleep.row < sprite_sheet_rows ? ret.sleep.row : sprite_sheet_rows-1;
                row++;
            }
            if (sprite_sheet_settings.wake_up_frames > 0) {
                ret.wake_up = { .valid = true, .start_col = 0, .end_col = sprite_sheet_settings.wake_up_frames-1, .row = sprite_sheet_settings.wake_up_row_index >= 0 ? sprite_sheet_settings.wake_up_row_index : row };
                ret.wake_up.row = ret.wake_up.row >= 0 ? ret.wake_up.row : 0;
                ret.wake_up.row = ret.wake_up.row < sprite_sheet_rows ? ret.wake_up.row : sprite_sheet_rows-1;
                row++;
            }

            if (sprite_sheet_settings.start_working_frames > 0) {
                ret.start_working = { .valid = true, .start_col = 0, .end_col = sprite_sheet_settings.start_working_frames-1, .row = sprite_sheet_settings.start_working_row_index >= 0 ? sprite_sheet_settings.start_working_row_index : row };
                ret.start_working.row = ret.start_working.row >= 0 ? ret.start_working.row : 0;
                ret.start_working.row = ret.start_working.row < sprite_sheet_rows ? ret.start_working.row : sprite_sheet_rows-1;
                row++;
            }
            if (sprite_sheet_settings.working_frames > 0) {
                ret.working = { .valid = true, .start_col = 0, .end_col = sprite_sheet_settings.working_frames-1, .row = sprite_sheet_settings.working_row_index >= 0 ? sprite_sheet_settings.working_row_index : row };
                ret.working.row = ret.working.row >= 0 ? ret.working.row : 0;
                ret.working.row = ret.working.row < sprite_sheet_rows ? ret.working.row : sprite_sheet_rows-1;
                row++;
            }
            if (sprite_sheet_settings.end_working_frames > 0) {
                ret.end_working = { .valid = true, .start_col = 0, .end_col = sprite_sheet_settings.end_working_frames-1, .row = sprite_sheet_settings.end_working_row_index >= 0 ? sprite_sheet_settings.end_working_row_index : row };
                ret.end_working.row = ret.end_working.row >= 0 ? ret.end_working.row : 0;
                ret.end_working.row = ret.end_working.row < sprite_sheet_rows ? ret.end_working.row : sprite_sheet_rows-1;
                row++;
            }

            if (sprite_sheet_settings.start_moving_frames > 0) {
                ret.start_moving = { .valid = true, .start_col = 0, .end_col = sprite_sheet_settings.start_moving_frames-1, .row = sprite_sheet_settings.start_moving_row_index >= 0 ? sprite_sheet_settings.start_moving_row_index : row };
                ret.start_moving.row = ret.start_moving.row >= 0 ? ret.start_moving.row : 0;
                ret.start_moving.row = ret.start_moving.row < sprite_sheet_rows ? ret.start_moving.row : sprite_sheet_rows-1;
                row++;
            }
            if (sprite_sheet_settings.moving_frames > 0) {
                ret.moving = { .valid = true, .start_col = 0, .end_col = sprite_sheet_settings.moving_frames-1, .row = sprite_sheet_settings.moving_row_index >= 0 ? sprite_sheet_settings.moving_row_index : row };
                ret.moving.row = ret.moving.row >= 0 ? ret.moving.row : 0;
                ret.moving.row = ret.moving.row < sprite_sheet_rows ? ret.moving.row : sprite_sheet_rows-1;
                row++;
            }
            if (sprite_sheet_settings.end_moving_frames > 0) {
                ret.end_moving = { .valid = true, .start_col = 0, .end_col = sprite_sheet_settings.end_moving_frames-1, .row = sprite_sheet_settings.end_moving_row_index >= 0 ? sprite_sheet_settings.end_moving_row_index : row };
                ret.end_moving.row = ret.end_moving.row >= 0 ? ret.end_moving.row : 0;
                ret.end_moving.row = ret.end_moving.row < sprite_sheet_rows ? ret.end_moving.row : sprite_sheet_rows-1;
                row++;
            }

            if (sprite_sheet_settings.start_running_frames > 0) {
                ret.start_running = { .valid = true, .start_col = 0, .end_col = sprite_sheet_settings.start_running_frames-1, .row = sprite_sheet_settings.start_running_row_index >= 0 ? sprite_sheet_settings.start_running_row_index : row };
                if (ret.start_moving.valid) {
                    ret.start_running.row = ret.start_moving.row;
                } else {
                    ret.start_running.row = ret.start_running.row >= 0 ? ret.start_running.row : 0;
                    ret.start_running.row = ret.start_running.row < sprite_sheet_rows ? ret.start_running.row : sprite_sheet_rows-1;
                }
                row++;
            } else if (ret.start_moving.valid) {
                ret.start_running = { .valid = true, .start_col = ret.start_moving.start_col, .end_col = ret.start_moving.end_col, .row = sprite_sheet_settings.start_running_row_index >= 0 ? sprite_sheet_settings.start_running_row_index : ret.start_moving.row };
            }
            if (sprite_sheet_settings.running_frames > 0) {
                ret.running = { .valid = true, .start_col = 0, .end_col = sprite_sheet_settings.running_frames-1, .row = sprite_sheet_settings.running_row_index >= 0 ? sprite_sheet_settings.running_row_index : row };
                if (ret.moving.valid) {
                    ret.running.row = ret.moving.row;
                } else {
                    ret.running.row = ret.running.row >= 0 ? ret.running.row : 0;
                    ret.running.row = ret.running.row < sprite_sheet_rows ? ret.running.row : sprite_sheet_rows-1;
                }
                row++;
            } else if (ret.moving.valid) {
                ret.running = { .valid = true, .start_col = ret.moving.start_col, .end_col = ret.moving.end_col, .row = sprite_sheet_settings.running_row_index >= 0 ? sprite_sheet_settings.running_row_index : ret.moving.row };
            }
            if (sprite_sheet_settings.end_running_frames > 0) {
                ret.end_running = { .valid = true, .start_col = 0, .end_col = sprite_sheet_settings.end_running_frames-1, .row = sprite_sheet_settings.end_running_row_index >= 0 ? sprite_sheet_settings.end_running_row_index : row };
                if (ret.end_moving.valid) {
                    ret.end_running.row = ret.end_moving.row;
                } else {
                    ret.end_running.row = ret.end_running.row >= 0 ? ret.end_running.row : 0;
                    ret.end_running.row = ret.end_running.row < sprite_sheet_rows ? ret.end_running.row : sprite_sheet_rows-1;
                }
                row++;
            } else if (ret.end_moving.valid) {
                ret.end_running = { .valid = true, .start_col = ret.end_moving.start_col, .end_col = ret.end_moving.end_col, .row = sprite_sheet_settings.end_running_row_index >= 0 ? sprite_sheet_settings.end_running_row_index : ret.end_moving.row };
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
        ret.feature_running = ret.running.valid || ret.start_running.valid || ret.end_running.valid;
        // is feature_toggle_writing_frames enabled or writing has only 2 frames (default)
        ret.feature_writing_toggle_frames = ret.working.valid && (sprite_sheet_settings.feature_toggle_writing_frames >= 1 || (sprite_sheet_settings.feature_toggle_writing_frames < 0 && !ret.start_moving.valid && !ret.end_working.valid && ret.working.valid && sprite_sheet_settings.working_frames == 2));
        ret.feature_writing_toggle_frames_random = ret.working.valid && (sprite_sheet_settings.feature_toggle_writing_frames_random >= 1 || (sprite_sheet_settings.feature_toggle_writing_frames_random < 0 && !ret.start_moving.valid && !ret.end_working.valid && ret.working.valid && sprite_sheet_settings.working_frames == 2));

        if (!ret.feature_idle) [[unlikely]] {
            BONGOCAT_LOG_WARNING("Custom Animation without idle animation: %s", sprite_sheet_image.name);
            // default to first frame
            ret.idle = { .valid = true, .start_col = 0, .end_col = 0, .row = sprite_sheet_settings.idle_row_index >= 0 ? sprite_sheet_settings.idle_row_index : 0 };
            ret.idle.row = ret.idle.row >= 0 ? ret.idle.row : 0;
            ret.idle.row = ret.idle.row < sprite_sheet_rows ? ret.idle.row : sprite_sheet_rows-1;
        }

        return ret;
    }

}
