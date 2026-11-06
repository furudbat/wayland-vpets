#include "ms_agent_images.h"
#include "embedded_assets/ms_agent/ms_agent.hpp"
#include "embedded_assets/ms_agent/ms_agent_sprite.h"
#include "graphics/animation.h"
#include "graphics/animation_thread_context.h"
#include "graphics/drawing.h"
#include "image_loader/load_images.h"
#include "utils/memory.h"

#include <cassert>

namespace bongocat::animation {

static const unsigned char* ms_agent_pngs_table[] = {
  clippy_png,
#ifdef FEATURE_MORE_MS_AGENT_EMBEDDED_ASSETS
  links_png,
  rover_png,
  merlin_png,
#endif
};
static const size_t ms_agent_png_sizes_table[] = {
  clippy_png_size,
#ifdef FEATURE_MORE_MS_AGENT_EMBEDDED_ASSETS
  links_png_size,
  rover_png_size,
  merlin_png_size,
#endif
};
static const char* ms_agent_names_table[] = {
  "Clippy",
#ifdef FEATURE_MORE_MS_AGENT_EMBEDDED_ASSETS
  "Links",
  "Rover",
  "Merlin",
#endif
};


BONGOCAT_NODISCARD static created_result_t<ms_agent_sprite_sheet_t>
load_ms_agent_sprite_sheet_from_memory(const uint8_t *sprite_data, size_t sprite_data_size, int frame_columns,
                                       int frame_rows, int padding_x, int padding_y) {
  // decode straight into the final (padded) layout
  auto [image, error] = load_sprite_sheet_image(sprite_data, sprite_data_size,
                                                {.frame_columns = frame_columns,
                                                 .frame_rows = frame_rows,
                                                 .padding_x = padding_x,
                                                 .padding_y = padding_y});
  if (error != bongocat_error_t::BONGOCAT_SUCCESS) [[unlikely]] {
    BONGOCAT_LOG_ERROR("Failed to load sprite sheet.");
    return error;
  }
  assert(frame_columns > 0 && frame_rows > 0);
  assert(image.sprite_sheet_width % frame_columns == 0);
  assert(image.sprite_sheet_height % frame_rows == 0);

  assert(frame_columns > 0 && frame_rows > 0);
  // padded frame size, image.sprite_sheet_width/height are the padded size (= row stride for blitting)
  return ms_agent_sprite_sheet_t{
    .image = bongocat::move(image),
    .frame_width = image.sprite_sheet_width / frame_columns,
    .frame_height = image.sprite_sheet_height / frame_rows,

    .idle{},
    .boring{},
    .start_writing{},
    .writing{},
    .end_writing{},

    .sleep{},
    .wake_up{},
    .start_working{},
    .working{},
    .end_working{},
    .start_moving{},
    .moving{},
    .end_moving{},
    .happy{},
    .start_running{},
    .running{},
    .end_running{},
  };
}

created_result_t<ms_agent_sprite_sheet_t> load_ms_agent_sprite_sheet(const config::config_t& config,
                                                                     const assets::embedded_image_t& sprite_sheet_image,
                                                                     int sprite_sheet_cols, int sprite_sheet_rows) {
  if (sprite_sheet_cols < 0 || sprite_sheet_rows < 0) {
    return bongocat_error_t::BONGOCAT_ERROR_INVALID_PARAM;
  }

  assert(sprite_sheet_image.size <= INT_MAX);
  auto result =
      load_ms_agent_sprite_sheet_from_memory(sprite_sheet_image.data, sprite_sheet_image.size, sprite_sheet_cols,
                                             sprite_sheet_rows, config.padding_x, config.padding_y);
  if (result.error != bongocat_error_t::BONGOCAT_SUCCESS) [[unlikely]] {
    BONGOCAT_LOG_ERROR("Sprite Sheet load failed: %s", sprite_sheet_image.name);
    return result.error;
  }

  // assume every frame is the same size, pick first frame
  BONGOCAT_LOG_DEBUG("Loaded %dx%d sprite sheet", result.result.image.sprite_sheet_width,
                     result.result.image.sprite_sheet_height);

  return result;
}

created_result_t<ms_agent_sprite_sheet_t>
load_ms_agent_anim(const animation_thread_context_t& ctx, [[maybe_unused]] size_t anim_index,
                   const assets::embedded_image_t& sprite_sheet_image, int sprite_sheet_cols, int sprite_sheet_rows,
                   const assets::ms_agent_animation_indices_t& animation_data) {
  using namespace assets;
  BONGOCAT_CHECK_NULL(ctx._local_copy_config.ptr, bongocat_error_t::BONGOCAT_ERROR_INVALID_PARAM);

  BONGOCAT_LOG_VERBOSE("Load MS agent Animation(index=%d) ...", anim_index);
  auto result =
      load_ms_agent_sprite_sheet(*ctx._local_copy_config, sprite_sheet_image, sprite_sheet_cols, sprite_sheet_rows);
  if (result.error != bongocat_error_t::BONGOCAT_SUCCESS) [[unlikely]] {
    return result.error;
  }

  // setup animation frames data
  if (result.result.frame_height > 0 && sprite_sheet_rows > 0) {
    [[maybe_unused]] const auto rows = result.result.image.sprite_sheet_height / result.result.frame_height;
    assert(rows == sprite_sheet_rows);

    assert(sprite_sheet_rows > 0);
    if (static_cast<size_t>(sprite_sheet_rows - 1) >= MS_AGENT_SPRITE_SHEET_ROW_IDLE) {
      result.result.idle = {.valid = true,
                            .start_col = animation_data.start_index_frame_idle,
                            .end_col = animation_data.end_index_frame_idle,
                            .row = MS_AGENT_SPRITE_SHEET_ROW_IDLE};
    }
    if (static_cast<size_t>(sprite_sheet_rows - 1) >= MS_AGENT_SPRITE_SHEET_ROW_BORING) {
      result.result.boring = {.valid = true,
                              .start_col = animation_data.start_index_frame_boring,
                              .end_col = animation_data.end_index_frame_boring,
                              .row = MS_AGENT_SPRITE_SHEET_ROW_BORING};
    }
    if (static_cast<size_t>(sprite_sheet_rows - 1) >= MS_AGENT_SPRITE_SHEET_ROW_START_WRITING) {
      result.result.start_writing = {.valid = true,
                                     .start_col = animation_data.start_index_frame_start_writing,
                                     .end_col = animation_data.end_index_frame_start_writing,
                                     .row = MS_AGENT_SPRITE_SHEET_ROW_START_WRITING};
    }
    if (static_cast<size_t>(sprite_sheet_rows - 1) >= MS_AGENT_SPRITE_SHEET_ROW_WRITING) {
      result.result.writing = {.valid = true,
                               .start_col = animation_data.start_index_frame_writing,
                               .end_col = animation_data.end_index_frame_writing,
                               .row = MS_AGENT_SPRITE_SHEET_ROW_WRITING};
    }
    if (static_cast<size_t>(sprite_sheet_rows - 1) >= MS_AGENT_SPRITE_SHEET_ROW_END_WRITING) {
      result.result.end_writing = {.valid = true,
                                   .start_col = animation_data.start_index_frame_end_writing,
                                   .end_col = animation_data.end_index_frame_end_writing,
                                   .row = MS_AGENT_SPRITE_SHEET_ROW_END_WRITING};
    }
    if (static_cast<size_t>(sprite_sheet_rows - 1) >= MS_AGENT_SPRITE_SHEET_ROW_SLEEP) {
      result.result.sleep = {.valid = true,
                             .start_col = animation_data.start_index_frame_sleep,
                             .end_col = animation_data.end_index_frame_sleep,
                             .row = MS_AGENT_SPRITE_SHEET_ROW_SLEEP};
    }
    if (static_cast<size_t>(sprite_sheet_rows - 1) >= MS_AGENT_SPRITE_SHEET_ROW_WAKE_UP) {
      result.result.wake_up = {.valid = true,
                               .start_col = animation_data.start_index_frame_wake_up,
                               .end_col = animation_data.end_index_frame_wake_up,
                               .row = MS_AGENT_SPRITE_SHEET_ROW_WAKE_UP};
    }
    if (static_cast<size_t>(sprite_sheet_rows - 1) >= MS_AGENT_SPRITE_SHEET_ROW_START_WORKING) {
      result.result.start_working = {.valid = true,
                                     .start_col = animation_data.start_index_frame_start_working,
                                     .end_col = animation_data.end_index_frame_start_working,
                                     .row = MS_AGENT_SPRITE_SHEET_ROW_START_WORKING};
    }
    if (static_cast<size_t>(sprite_sheet_rows - 1) >= MS_AGENT_SPRITE_SHEET_ROW_WORKING) {
      result.result.working = {.valid = true,
                               .start_col = animation_data.start_index_frame_working,
                               .end_col = animation_data.end_index_frame_working,
                               .row = MS_AGENT_SPRITE_SHEET_ROW_WORKING};
    }
    if (static_cast<size_t>(sprite_sheet_rows - 1) >= MS_AGENT_SPRITE_SHEET_ROW_END_WORKING) {
      result.result.end_working = {.valid = true,
                                   .start_col = animation_data.start_index_frame_end_working,
                                   .end_col = animation_data.end_index_frame_end_working,
                                   .row = MS_AGENT_SPRITE_SHEET_ROW_END_WORKING};
    }
    if (static_cast<size_t>(sprite_sheet_rows - 1) >= MS_AGENT_SPRITE_SHEET_ROW_START_MOVING) {
      result.result.start_moving = {.valid = true,
                                    .start_col = animation_data.start_index_frame_start_moving,
                                    .end_col = animation_data.end_index_frame_start_moving,
                                    .row = MS_AGENT_SPRITE_SHEET_ROW_START_MOVING};
    }
    if (static_cast<size_t>(sprite_sheet_rows - 1) >= MS_AGENT_SPRITE_SHEET_ROW_MOVING) {
      result.result.moving = {.valid = true,
                              .start_col = animation_data.start_index_frame_moving,
                              .end_col = animation_data.end_index_frame_moving,
                              .row = MS_AGENT_SPRITE_SHEET_ROW_MOVING};
    }
    if (static_cast<size_t>(sprite_sheet_rows - 1) >= MS_AGENT_SPRITE_SHEET_ROW_END_MOVING) {
      result.result.end_moving = {.valid = true,
                                  .start_col = animation_data.start_index_frame_end_moving,
                                  .end_col = animation_data.end_index_frame_end_moving,
                                  .row = MS_AGENT_SPRITE_SHEET_ROW_END_MOVING};
    }
    // if (static_cast<size_t>(sprite_sheet_rows - 1) >= MS_AGENT_SPRITE_SHEET_ROW_HAPPY) {
    //     result.result.happy = { .valid = true, .start_col = animation_data.start_index_frame_happy), .end_col =
    //     animation_data.end_index_happy_moving), .row = MS_AGENT_SPRITE_SHEET_ROW_HAPPY };
    // }
  }

  return bongocat::move(result.result);
}

created_result_t<ms_agent_sprite_sheet_t>
init_ms_agent_anim(animation_thread_context_t& ctx, size_t anim_index, const assets::embedded_image_t& sprite_sheet_image,
                   int sprite_sheet_cols, int sprite_sheet_rows,
                   const assets::ms_agent_animation_indices_t& animation_data) {
  using namespace assets;
  BONGOCAT_CHECK_NULL(ctx.shm.ptr, bongocat_error_t::BONGOCAT_ERROR_INVALID_PARAM);
  BONGOCAT_CHECK_NULL(ctx._local_copy_config.ptr, bongocat_error_t::BONGOCAT_ERROR_INVALID_PARAM);

  assert(anim_index < MS_AGENTS_ANIM_COUNT);
  BONGOCAT_LOG_VERBOSE("Load MS agent Animation (%d/%d): %s ...", anim_index, MS_AGENTS_ANIM_COUNT,
                       sprite_sheet_image.name);
  auto result =
      load_ms_agent_anim(ctx, anim_index, sprite_sheet_image, sprite_sheet_cols, sprite_sheet_rows, animation_data);
  if (result.error != bongocat_error_t::BONGOCAT_SUCCESS) {
    BONGOCAT_LOG_ERROR("Load MS agent Animation failed: %s, index: %d", sprite_sheet_image.name, anim_index);
    return bongocat_error_t::BONGOCAT_ERROR_ANIMATION;
  }
  assert(result.error ==
         bongocat_error_t::BONGOCAT_SUCCESS);  ///< this SHOULD always work if it's an valid EMBEDDED image

  ctx.shm->ms_anims[anim_index] = bongocat::move(result.result);
  assert(ctx.shm->ms_anims[anim_index].type == animation_t::type_t::MsAgent);

  return bongocat_error_t::BONGOCAT_SUCCESS;
}




created_result_t<ms_agent_sprite_sheet_t> load_ms_agent_sprite_sheet(const animation_thread_context_t& ctx, size_t index) {
  using namespace assets;
  using namespace animation;
  assert(index < MS_AGENTS_ANIM_COUNT);
  const auto dims = get_ms_agent_sprite_sheet_dims(index);
  const auto image = get_ms_agent_sprite_sheet(index);
  auto result = load_ms_agent_anim(ctx, index, image,
                            dims.cols, dims.rows,
                            get_ms_agent_animation_indices(index));
  return result;
}

void init_all_ms_agent_anim(animation_thread_context_t& ctx) {
  using namespace assets;
  for (size_t i = 0;i < MS_AGENTS_ANIM_COUNT;++i) {
    const auto dims = get_ms_agent_sprite_sheet_dims(i);
    init_ms_agent_anim(ctx, i, {ms_agent_pngs_table[i], ms_agent_png_sizes_table[i], ms_agent_names_table[i]}, dims.cols, dims.rows,
                            get_ms_agent_animation_indices(i));
  }
}
}  // namespace bongocat::animation
