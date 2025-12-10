#include "image_loader/base_dm/load_dm.h"

#include "graphics/animation_thread_context.h"
#include "image_loader/load_images.h"

namespace bongocat::animation {

created_result_t<dm_sprite_sheet_t> load_dm_anim(const animation_thread_context_t& ctx, [[maybe_unused]] int anim_index,
                                                 const assets::embedded_image_t& sprite_sheet_image,
                                                 int sprite_sheet_cols, int sprite_sheet_rows) {
  using namespace assets;
  BONGOCAT_CHECK_NULL(ctx._local_copy_config.ptr, bongocat_error_t::BONGOCAT_ERROR_INVALID_PARAM);

  auto result =
      load_sprite_sheet_anim(*ctx._local_copy_config, sprite_sheet_image, sprite_sheet_cols, sprite_sheet_rows);
  if (result.error != bongocat_error_t::BONGOCAT_SUCCESS) [[unlikely]] {
    BONGOCAT_LOG_ERROR("Load dm Animation failed: %s, index: %d", sprite_sheet_image.name, anim_index);
    return bongocat_error_t::BONGOCAT_ERROR_ANIMATION;
  }
  assert(result.result.total_frames > 0);  ///< this SHOULD always work if it's an valid EMBEDDED image
  assert(MAX_NUM_FRAMES <= INT_MAX);
  assert(result.result.total_frames <= static_cast<int>(MAX_NUM_FRAMES));
  if (result.result.total_frames > static_cast<int>(MAX_NUM_FRAMES)) {
    BONGOCAT_LOG_ERROR("Sprite Sheet does not fit in out_frames: %d, total_frames: %d", MAX_NUM_FRAMES,
                       result.result.total_frames);
    return bongocat_error_t::BONGOCAT_ERROR_INVALID_PARAM;
  }

  dm_sprite_sheet_t ret;
  ret.image = bongocat::move(result.result.image);
  ret.frame_width = bongocat::move(result.result.frame_width);
  ret.frame_height = bongocat::move(result.result.frame_height);
  ret.total_frames = bongocat::move(result.result.total_frames);

  ret.frames.idle_1 = bongocat::move(result.result.frames[0]);
  ret.frames.idle_2 = bongocat::move(result.result.frames[1]);
  ret.frames.angry = bongocat::move(result.result.frames[2]);
  ret.frames.down = bongocat::move(result.result.frames[3]);
  ret.frames.happy = bongocat::move(result.result.frames[4]);
  ret.frames.eat_1 = bongocat::move(result.result.frames[5]);
  ret.frames.sleep = bongocat::move(result.result.frames[6]);
  ret.frames.refuse = bongocat::move(result.result.frames[7]);
  ret.frames.sad = bongocat::move(result.result.frames[8]);

  ret.frames.lose_1 = bongocat::move(result.result.frames[9]);
  ret.frames.eat_2 = bongocat::move(result.result.frames[10]);
  ret.frames.lose_2 = bongocat::move(result.result.frames[11]);
  ret.frames.attack_1 = bongocat::move(result.result.frames[12]);

  ret.frames.movement_1 = bongocat::move(result.result.frames[13]);
  ret.frames.movement_2 = bongocat::move(result.result.frames[14]);

  // setup animations
  using namespace assets;

  // minimal frames existing
  assert(ret.frames.idle_1.valid);
  assert(ret.frames.idle_2.valid);
  assert(ret.frames.angry.valid);
  assert(ret.frames.down.valid);

  assert(MAX_ANIMATION_FRAMES >= 4);
  ret.animations.idle[0] = ret.frames.idle_1.col;
  ret.animations.idle[1] = ret.frames.idle_2.col;
  ret.animations.idle[2] = ret.frames.idle_1.col;
  ret.animations.idle[3] = ret.frames.idle_2.col;

  ret.animations.boring[0] = ret.frames.sad.col ? ret.frames.sad.col : ret.frames.idle_1.col;
  ret.animations.boring[1] = ret.frames.lose_1.col ? ret.frames.lose_1.col : ret.frames.idle_2.col;
  ret.animations.boring[2] = ret.frames.lose_2.col ? ret.frames.lose_2.col : ret.frames.idle_1.col;
  ret.animations.boring[3] = ret.frames.idle_2.col;

  ret.animations.writing[0] = ret.frames.idle_2.col;
  ret.animations.writing[1] = ret.frames.idle_1.col;
  ret.animations.writing[2] = ret.frames.idle_2.col;
  ret.animations.writing[3] = ret.frames.idle_1.col;

  // sleep animation
  if (ret.frames.sleep.valid) {
    ret.animations.sleep[0] = ret.frames.sleep.col;
    ret.animations.sleep[1] = ret.frames.sleep.col;
    ret.animations.sleep[2] = ret.frames.sleep.col;
    ret.animations.sleep[3] = ret.frames.sleep.col;
  } else if (ret.frames.down.valid) {
    ret.animations.sleep[0] = ret.frames.down.col;
    ret.animations.sleep[1] = ret.frames.down.col;
    ret.animations.sleep[2] = ret.frames.down.col;
    ret.animations.sleep[3] = ret.frames.down.col;
  } else {
    // fallback
    ret.animations.sleep[0] = ret.frames.idle_2.col;
    ret.animations.sleep[1] = ret.frames.idle_2.col;
    ret.animations.sleep[2] = ret.frames.idle_2.col;
    ret.animations.sleep[3] = ret.frames.idle_2.col;
  }

  ret.animations.wake_up[0] = ret.frames.idle_1.col;
  ret.animations.wake_up[1] = ret.frames.idle_2.col;
  ret.animations.wake_up[2] = ret.frames.idle_1.col;
  ret.animations.wake_up[3] = ret.frames.idle_2.col;

  // working/attack animation
  ret.animations.working[0] = ret.frames.idle_1.col;
  ret.animations.working[1] = ret.frames.idle_2.col;
  ret.animations.working[2] = ret.frames.angry.valid ? ret.frames.angry.col : ret.frames.idle_1.col;
  ret.animations.working[3] = ret.frames.idle_2.col;
  ret.animations.working[2] = ret.frames.attack_1.valid ? ret.frames.attack_1.col : ret.animations.working[2];
  ret.animations.working[3] = ret.frames.attack_2.valid ? ret.frames.attack_2.col : ret.animations.working[3];

  // moving/walking animation
  if (ret.frames.movement_1.valid || ret.frames.movement_2.valid) {
    ret.animations.moving[0] = ret.frames.movement_1.valid ? ret.frames.movement_1.col : ret.frames.idle_1.col;
    ret.animations.moving[1] = ret.frames.movement_1.valid ? ret.frames.movement_1.col : ret.frames.idle_1.col;
    ret.animations.moving[2] = ret.frames.movement_2.valid ? ret.frames.movement_2.col : ret.frames.idle_2.col;
    ret.animations.moving[3] = ret.frames.movement_2.valid ? ret.frames.movement_2.col : ret.frames.idle_2.col;
  } else {
    // fallback
    ret.animations.moving[0] = ret.frames.idle_1.col;
    ret.animations.moving[1] = ret.frames.idle_1.col;
    ret.animations.moving[2] = ret.frames.idle_2.col;
    ret.animations.moving[3] = ret.frames.idle_2.col;
  }
  // running animation (same as moving)
  if (ret.frames.movement_1.valid || ret.frames.movement_2.valid) {
    ret.animations.running[0] = ret.frames.movement_1.valid ? ret.frames.movement_1.col : ret.frames.idle_1.col;
    ret.animations.running[1] = ret.frames.movement_1.valid ? ret.frames.movement_1.col : ret.frames.idle_1.col;
    ret.animations.running[2] = ret.frames.movement_2.valid ? ret.frames.movement_2.col : ret.frames.idle_2.col;
    ret.animations.running[3] = ret.frames.movement_2.valid ? ret.frames.movement_2.col : ret.frames.idle_2.col;
  } else {
    // fallback
    ret.animations.running[0] = ret.frames.idle_1.col;
    ret.animations.running[1] = ret.frames.idle_1.col;
    ret.animations.running[2] = ret.frames.idle_2.col;
    ret.animations.running[3] = ret.frames.idle_2.col;
  }

  // happy animation
  if (ret.frames.happy.valid) {
    ret.animations.happy[0] = ret.frames.happy.valid ? ret.frames.happy.col : ret.frames.idle_2.col;
    ret.animations.happy[1] = ret.frames.idle_1.col;
    ret.animations.happy[2] = ret.frames.happy.valid ? ret.frames.happy.col : ret.frames.idle_2.col;
    ret.animations.happy[3] = ret.frames.idle_1.col;
  } else {
    // fallback
    ret.animations.happy[0] = ret.frames.idle_1.col;
    ret.animations.happy[1] = ret.frames.idle_2.col;
    ret.animations.happy[2] = ret.frames.idle_1.col;
    ret.animations.happy[3] = ret.frames.idle_2.col;
  }

  return ret;
}

}  // namespace bongocat::animation