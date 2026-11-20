#include "image_loader/base_dm/load_dm.h"

#include "graphics/animation_thread_context.h"
#include "image_loader/load_images.h"

namespace bongocat::animation {

// BLANK_TARGET see scripts/optimize_dm_sprite_sheet.sh: idle1 idle2 angry down1 happy eat1 sleep1 refuse sad down2 eat2 sleep2 attack movement1 movement2
inline static constexpr int32_t DM_BLANK_FALLBACK[] = {-1, -1, 0, 1, 2, 2, 3, 2, 3, 3, 5, 6, 2, 0, 1};
static_assert(LEN_ARRAY(DM_BLANK_FALLBACK) <= INT32_MAX);
inline static constexpr int32_t DM_BLANK_FALLBACK_COUNT = LEN_ARRAY(DM_BLANK_FALLBACK);

static bool is_blank_frame(const generic_sprite_sheet_image_t& image, int32_t frame_width, int32_t frame_height,
                    const sprite_sheet_animation_frame_t& frame) {
  constexpr size_t RGBA_CHANNELS = 4;
  if (image.channels != static_cast<int32_t>(RGBA_CHANNELS) || image.pixels.data == nullptr) {
    return false;
  }

  assert(image.sprite_sheet_width >= 0);
  assert(frame.col >= 0);
  assert(frame.row >= 0);
  assert(frame_width >= 0);
  assert(frame_height >= 0);
  assert(image.sprite_sheet_width >= 0);
  assert(image.sprite_sheet_height >= 0);

  const auto stride = static_cast<size_t>(image.sprite_sheet_width) * RGBA_CHANNELS;
  const auto x0 = static_cast<size_t>(frame.col) * static_cast<size_t>(frame_width);
  const auto y0 = static_cast<size_t>(frame.row) * static_cast<size_t>(frame_height);
  if (x0 + static_cast<size_t>(frame_width) > static_cast<size_t>(image.sprite_sheet_width) ||
      y0 + static_cast<size_t>(frame_height) > static_cast<size_t>(image.sprite_sheet_height)) {
    return false;
  }

  // check for empty frame, @TODO: optimize scan line
  for (size_t y = y0; y < y0 + static_cast<size_t>(frame_height); y++) {
    const uint8_t *row = image.pixels.data + (y * stride) + (x0 * RGBA_CHANNELS);
    for (size_t x = 0; x < static_cast<size_t>(frame_width); x++) {
      if (row[(x * RGBA_CHANNELS) + 3] != 0) {
        return false;
      }
    }
  }

  return true;
}

static void resolve_blank_dm_frames(dm_sprite_sheet_t& ret, sprite_sheet_animation_frame_t *frames, int32_t count) {
  const int32_t n = count < DM_BLANK_FALLBACK_COUNT ? count : DM_BLANK_FALLBACK_COUNT;
  for (int32_t i = 0; i < n; i++) {
    const int32_t fallback = DM_BLANK_FALLBACK[i];

    if (fallback < 0 || !frames[i].valid) {
      continue;
    }

    // sanety check: fallbacks always point to a lower index, resolve in order
    assert(fallback < i);

    if (is_blank_frame(ret.image, ret.frame_width, ret.frame_height, frames[i])) {
      frames[i] = frames[fallback];
    }
  }
}

void patch_dm_anim(dm_sprite_sheet_t& ret, load_dm_anim_options_t options) {
  if (options.sleep_in_bed) {
    if (ret.frames.down.valid) {
      ret.animations.idle_sleep[0] = ret.frames.down.col;
      ret.animations.idle_sleep[1] = ret.frames.down.col;
      ret.animations.idle_sleep[2] = ret.frames.down.col;
      ret.animations.idle_sleep[3] = ret.frames.down.col;
    } else {
      // fallback
      ret.animations.idle_sleep[0] = ret.frames.idle_2.col;
      ret.animations.idle_sleep[1] = ret.frames.idle_2.col;
      ret.animations.idle_sleep[2] = ret.frames.idle_2.col;
      ret.animations.idle_sleep[3] = ret.frames.idle_2.col;
    }
  } else {
    ret.animations.idle_sleep[0] = ret.animations.sleep[0];
    ret.animations.idle_sleep[1] = ret.animations.sleep[1];
    ret.animations.idle_sleep[2] = ret.animations.sleep[2];
    ret.animations.idle_sleep[3] = ret.animations.sleep[3];
  }

  if (options.no_happy) {
    ret.animations.happy[0] = ret.frames.angry.valid ? ret.frames.angry.col : ret.frames.idle_1.col;
    ret.animations.happy[1] = ret.frames.idle_2.col;
    ret.animations.happy[2] = ret.frames.angry.valid ? ret.frames.angry.col : ret.frames.idle_1.col;
    ret.animations.happy[3] = ret.frames.idle_2.col;
  }
}
created_result_t<dm_sprite_sheet_t> load_base_dm_anim(const animation_thread_context_t& ctx, [[maybe_unused]] size_t anim_index,
                                                 const assets::embedded_image_t& sprite_sheet_image,
                                                 int sprite_sheet_cols, int sprite_sheet_rows,
                                                 load_dm_anim_options_t options) {
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

  // optimized sprite sheets: blank (duplicated) frames use their fallback frame
  resolve_blank_dm_frames(ret, result.result.frames, ret.total_frames);

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

  ret.animations.boring[0] = ret.frames.sad.col >= 1 ? ret.frames.sad.col : ret.frames.idle_1.col;
  ret.animations.boring[1] = ret.frames.lose_1.col >= 1 ? ret.frames.lose_1.col : ret.frames.idle_2.col;
  ret.animations.boring[2] = ret.frames.lose_2.col >= 1 ? ret.frames.lose_2.col : ret.frames.idle_1.col;
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
  ret.animations.idle_sleep[0] = ret.animations.sleep[0];
  ret.animations.idle_sleep[1] = ret.animations.sleep[1];
  ret.animations.idle_sleep[2] = ret.animations.sleep[2];
  ret.animations.idle_sleep[3] = ret.animations.sleep[3];

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
    ret.animations.happy[0] = ret.frames.angry.valid ? ret.frames.angry.col : ret.frames.idle_1.col;
    ret.animations.happy[1] = ret.frames.idle_2.col;
    ret.animations.happy[2] = ret.frames.angry.valid ? ret.frames.angry.col : ret.frames.idle_1.col;
    ret.animations.happy[3] = ret.frames.idle_2.col;
  }

  patch_dm_anim(ret, options);

  return ret;
}

}  // namespace bongocat::animation