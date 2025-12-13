#include "bar.h"

#include "embedded_assets/bongocat/bongocat.h"
#include "embedded_assets/misc/misc.hpp"
#include "graphics/animation.h"
#include "graphics/animation_thread_context.h"
#include "graphics/drawing.h"
#include "graphics/embedded_assets_dms.h"
#include "graphics/embedded_assets_pkmn.h"
#include "platform/wayland-protocols.hpp"
#include "platform/wayland.h"
#include "platform/wayland_callbacks.h"

#include <cassert>
#include <wayland-client.h>

namespace bongocat::animation {
inline static constexpr uint32_t DEFAULT_FILL_COLOR = 0x00000000;        // ARGB
inline static constexpr uint32_t DEBUG_MOVEMENT_BAR_COLOR = 0xFFFF0000;  // ARGB

// =============================================================================
// DRAWING MANAGEMENT
// =============================================================================

struct cat_rect_t {
  int x;
  int y;
  int width;
  int height;
};

template <class SpriteSheet>
/// @TODO: required SpriteSheet must be _sprite_sheet_t
cat_rect_t get_position(const platform::wayland::wayland_thread_context& wayland_ctx, const SpriteSheet& sheet,
                        const config::config_t& config) {
  const int cat_height = config.cat_height;
  const int cat_width = static_cast<int>(static_cast<float>(cat_height) * (static_cast<float>(sheet.frame_width) /
                                                                           static_cast<float>(sheet.frame_height)));

  int cat_x = 0;
  switch (config.cat_align) {
  case config::align_type_t::ALIGN_CENTER:
    cat_x = (wayland_ctx._screen_width - cat_width) / 2 + config.cat_x_offset;
    break;
  case config::align_type_t::ALIGN_LEFT:
    cat_x = config.cat_x_offset;
    break;
  case config::align_type_t::ALIGN_RIGHT:
    cat_x = wayland_ctx._screen_width - cat_width - config.cat_x_offset;
    break;
  default:
    BONGOCAT_LOG_VERBOSE("Invalid cat_align %d", config.cat_align);
    break;
  }
  const int cat_y = ((wayland_ctx._bar_height - cat_height) / 2) + config.cat_y_offset;

  return {.x = cat_x, .y = cat_y, .width = cat_width, .height = cat_height};
}

/// @TODO: make draw_sprite more generic (template?)
void draw_sprite(platform::wayland::wayland_context_t& ctx, platform::wayland::wayland_shm_buffer_t& shm_buffer,
                 const bongocat_sprite_sheet_t& sheet,
                 blit_image_color_option_flags_t extra_drawing_option = blit_image_color_option_flags_t::Normal) {
  using namespace assets;
  if (sheet.frame_width <= 0 || sheet.frame_height <= 0) {
    return;
  }

  const platform::wayland::wayland_thread_context& wayland_ctx = ctx.thread_context;
  animation_thread_context_t& anim = ctx.animation_context->thread_context;
  // animation_trigger_context_t *trigger_ctx = ctx.animation_trigger_context;
  // platform::wayland::wayland_shared_memory_t *wayland_ctx_shm = wayland_ctx.ctx_shm.ptr;

  assert(wayland_ctx._local_copy_config);
  assert(anim.shm);
  const config::config_t& current_config = *wayland_ctx._local_copy_config.ptr;
  const animation_shared_memory_t& anim_shm = *anim.shm;

  uint8_t *pixels = shm_buffer.pixels.data;
  const size_t pixels_size = shm_buffer.pixels._size_bytes;

  const sprite_sheet_animation_frame_t *region = BONGOCAT_NULLPTR;
  switch (anim_shm.animation_player_result.sprite_sheet_col) {
  case BONGOCAT_FRAME_BOTH_UP:
    region = &sheet.both_up;
    break;
  case BONGOCAT_FRAME_LEFT_DOWN:
    region = &sheet.left_down;
    break;
  case BONGOCAT_FRAME_RIGHT_DOWN:
    region = &sheet.right_down;
    break;
  case BONGOCAT_FRAME_BOTH_DOWN:
    region = &sheet.both_down;
    break;
  default:
    assert(anim_shm.animation_player_result.sprite_sheet_col >= 0 &&
           static_cast<size_t>(anim_shm.animation_player_result.sprite_sheet_col) < BONGOCAT_SPRITE_SHEET_COLS);
    break;
  }

  auto [cat_x, cat_y, cat_width, cat_height] = get_position(wayland_ctx, sheet, current_config);
  auto cat_x_with_offset = cat_x + static_cast<int32_t>(anim_shm.movement_offset_x);

  if (region != BONGOCAT_NULLPTR) {
    // draw debug rectangle
    if (current_config.enable_movement_debug >= 1 && current_config.movement_radius > 0) {
      cat_rect_t movement_debug_bar{};
      switch (current_config.cat_align) {
      case config::align_type_t::ALIGN_CENTER:
        movement_debug_bar = {.x = cat_x + (cat_width / 2) - current_config.movement_radius,
                              .y = 0,
                              .width = current_config.movement_radius * 2,
                              .height = wayland_ctx._bar_height};
        break;
      case config::align_type_t::ALIGN_LEFT:
        movement_debug_bar = {
            .x = cat_x, .y = 0, .width = current_config.movement_radius * 2, .height = wayland_ctx._bar_height};
        break;
      case config::align_type_t::ALIGN_RIGHT:
        movement_debug_bar = {.x = cat_x + cat_width - (current_config.movement_radius * 2),
                              .y = 0,
                              .width = current_config.movement_radius * 2,
                              .height = wayland_ctx._bar_height};
        break;
      }

      // Skip fullscreen hiding when layer is LAYER_OVERLAY (always visible)
      const bool is_overlay_layer = current_config.layer == config::layer_type_t::LAYER_OVERLAY;
      const bool is_fullscreen = !is_overlay_layer && wayland_ctx._fullscreen_detected;
      const bool bar_visible =
          !is_fullscreen && wayland_ctx.bar_visibility == platform::wayland::bar_visibility_t::Show;
      const int effective_opacity = bar_visible ? current_config.overlay_opacity : 0;
      const uint32_t fill = DEBUG_MOVEMENT_BAR_COLOR &
                            (0x00FFFFFF | (static_cast<uint32_t>(effective_opacity) << 24u));  // RGBA, little-endian
      auto *p = reinterpret_cast<uint32_t *>(pixels);
      assert(wayland_ctx._screen_width >= 0);
      [[maybe_unused]] const size_t total_pixels =
          static_cast<size_t>(wayland_ctx._screen_width) * static_cast<size_t>(wayland_ctx._bar_height);
      for (int32_t y = movement_debug_bar.y;
           y < movement_debug_bar.y + movement_debug_bar.height && y < wayland_ctx._bar_height; y++) {
        for (int32_t x = movement_debug_bar.x;
             x < movement_debug_bar.x + movement_debug_bar.width && x < wayland_ctx._screen_width; x++) {
          if (x >= 0 && y >= 0) {
            const size_t pi =
                static_cast<size_t>(x) + (static_cast<size_t>(y) * static_cast<size_t>(wayland_ctx._screen_width));
            assert(pi < total_pixels);
            p[pi] = fill;
          }
        }
      }
    }

    blit_image_color_option_flags_t drawing_option = blit_image_color_option_flags_t::Normal;
    if (current_config.invert_color >= 1) {
      drawing_option = flag_add(drawing_option, blit_image_color_option_flags_t::Invert);
    }
    if (anim_shm.anim_direction >= 1.0f) {
      if (current_config.mirror_x <= 0) {
        drawing_option = flag_add(drawing_option, blit_image_color_option_flags_t::MirrorX);
      }
    } else {
      if (current_config.mirror_x >= 1) {
        drawing_option = flag_add(drawing_option, blit_image_color_option_flags_t::MirrorX);
      }
    }
    if (current_config.mirror_y >= 1) {
      drawing_option = flag_add(drawing_option, blit_image_color_option_flags_t::MirrorY);
    }
    if (current_config.enable_antialiasing >= 1) {
      drawing_option = flag_add(drawing_option, blit_image_color_option_flags_t::BilinearInterpolation);
    }
    if (extra_drawing_option != blit_image_color_option_flags_t::Normal) {
      drawing_option = flag_add(drawing_option, extra_drawing_option);
    }

    blit_image_scaled(pixels, pixels_size, wayland_ctx._screen_width, wayland_ctx._bar_height, BGRA_CHANNELS,
                      sheet.image.pixels.data, sheet.image.pixels._size_bytes, sheet.image.sprite_sheet_width,
                      sheet.image.sprite_sheet_height, sheet.image.channels, region->col * sheet.frame_width,
                      region->row * sheet.frame_height, sheet.frame_width, sheet.frame_height, cat_x_with_offset, cat_y,
                      cat_width, cat_height, blit_image_color_order_t::BGRA, blit_image_color_order_t::RGBA,
                      drawing_option);
  }
}

void draw_sprite(platform::wayland::wayland_context_t& ctx, platform::wayland::wayland_shm_buffer_t& shm_buffer,
                 const dm_sprite_sheet_t& sheet,
                 blit_image_color_option_flags_t extra_drawing_option = blit_image_color_option_flags_t::Normal) {
  using namespace assets;
  if (sheet.frame_width <= 0 || sheet.frame_height <= 0) {
    return;
  }

  const platform::wayland::wayland_thread_context& wayland_ctx = ctx.thread_context;
  animation_thread_context_t& anim = ctx.animation_context->thread_context;
  // animation_trigger_context_t *trigger_ctx = ctx.animation_trigger_context;
  // platform::wayland::wayland_shared_memory_t *wayland_ctx_shm = wayland_ctx.ctx_shm.ptr;

  assert(wayland_ctx._local_copy_config);
  assert(anim.shm);
  const config::config_t& current_config = *wayland_ctx._local_copy_config.ptr;
  const animation_shared_memory_t& anim_shm = *anim.shm;

  uint8_t *pixels = shm_buffer.pixels.data;
  const size_t pixels_size = shm_buffer.pixels._size_bytes;

  const sprite_sheet_animation_frame_t *region = BONGOCAT_NULLPTR;
  switch (anim_shm.animation_player_result.sprite_sheet_col) {
  case DM_FRAME_IDLE1:
    region = &sheet.frames.idle_1;
    break;
  case DM_FRAME_IDLE2:
    region = &sheet.frames.idle_2;
    break;
  case DM_FRAME_ANGRY:
    region = &sheet.frames.angry;
    break;
  case DM_FRAME_DOWN:
    region = &sheet.frames.down;
    break;
  case DM_FRAME_HAPPY:
    region = &sheet.frames.happy;
    break;
  case DM_FRAME_EAT1:
    region = &sheet.frames.eat_1;
    break;
  case DM_FRAME_SLEEP:
    region = &sheet.frames.sleep;
    break;
  case DM_FRAME_REFUSE:
    region = &sheet.frames.refuse;
    break;
  case DM_FRAME_SAD:
    region = &sheet.frames.sad;
    break;
  case DM_FRAME_LOSE1:
    region = &sheet.frames.lose_1;
    break;
  case DM_FRAME_EAT2:
    region = &sheet.frames.eat_2;
    break;
  case DM_FRAME_LOSE2:
    region = &sheet.frames.lose_2;
    break;
  case DM_FRAME_ATTACK:
    region = &sheet.frames.attack_1;
    break;
  case DM_FRAME_MOVEMENT1:
    region = &sheet.frames.movement_1;
    break;
  case DM_FRAME_MOVEMENT2:
    region = &sheet.frames.movement_2;
    break;
  default:
    assert(anim_shm.animation_player_result.sprite_sheet_col >= 0 &&
           static_cast<size_t>(anim_shm.animation_player_result.sprite_sheet_col) < DM_SPRITE_SHEET_MAX_COLS);
    break;
  }

  auto [cat_x, cat_y, cat_width, cat_height] = get_position(wayland_ctx, sheet, current_config);
  auto cat_x_with_offset = cat_x + static_cast<int32_t>(anim_shm.movement_offset_x);

  if (region != BONGOCAT_NULLPTR) {
    // draw debug rectangle
    if (current_config.enable_movement_debug >= 1 && current_config.movement_radius > 0) {
      cat_rect_t movement_debug_bar{};
      switch (current_config.cat_align) {
      case config::align_type_t::ALIGN_CENTER:
        movement_debug_bar = {.x = cat_x + (cat_width / 2) - current_config.movement_radius,
                              .y = 0,
                              .width = current_config.movement_radius * 2,
                              .height = wayland_ctx._bar_height};
        break;
      case config::align_type_t::ALIGN_LEFT:
        movement_debug_bar = {
            .x = cat_x, .y = 0, .width = current_config.movement_radius * 2, .height = wayland_ctx._bar_height};
        break;
      case config::align_type_t::ALIGN_RIGHT:
        movement_debug_bar = {.x = cat_x + cat_width - (current_config.movement_radius * 2),
                              .y = 0,
                              .width = current_config.movement_radius * 2,
                              .height = wayland_ctx._bar_height};
        break;
      }

      const bool bar_visible =
          !wayland_ctx._fullscreen_detected && wayland_ctx.bar_visibility == platform::wayland::bar_visibility_t::Show;
      const int effective_opacity = bar_visible ? current_config.overlay_opacity : 0;
      const uint32_t fill = DEBUG_MOVEMENT_BAR_COLOR &
                            (0x00FFFFFF | (static_cast<uint32_t>(effective_opacity) << 24u));  // RGBA, little-endian
      auto *p = reinterpret_cast<uint32_t *>(pixels);
      assert(wayland_ctx._screen_width >= 0);
      [[maybe_unused]] const size_t total_pixels =
          static_cast<size_t>(wayland_ctx._screen_width) * static_cast<size_t>(wayland_ctx._bar_height);
      for (int32_t y = movement_debug_bar.y;
           y < movement_debug_bar.y + movement_debug_bar.height && y < wayland_ctx._bar_height; y++) {
        for (int32_t x = movement_debug_bar.x;
             x < movement_debug_bar.x + movement_debug_bar.width && x < wayland_ctx._screen_width; x++) {
          if (x >= 0 && y >= 0) {
            const size_t pi =
                static_cast<size_t>(x) + (static_cast<size_t>(y) * static_cast<size_t>(wayland_ctx._screen_width));
            assert(pi < total_pixels);
            p[pi] = fill;
          }
        }
      }
    }

    blit_image_color_option_flags_t drawing_option = blit_image_color_option_flags_t::Normal;
    if (current_config.invert_color >= 1) {
      drawing_option = flag_add(drawing_option, blit_image_color_option_flags_t::Invert);
    }
    if (anim_shm.anim_direction >= 1.0f) {
      if (current_config.mirror_x <= 0) {
        drawing_option = flag_add(drawing_option, blit_image_color_option_flags_t::MirrorX);
      }
    } else {
      if (current_config.mirror_x >= 1) {
        drawing_option = flag_add(drawing_option, blit_image_color_option_flags_t::MirrorX);
      }
    }
    if (current_config.mirror_y >= 1) {
      drawing_option = flag_add(drawing_option, blit_image_color_option_flags_t::MirrorY);
    }
    if (extra_drawing_option != blit_image_color_option_flags_t::Normal) {
      drawing_option = flag_add(drawing_option, extra_drawing_option);
    }

    blit_image_scaled(pixels, pixels_size, wayland_ctx._screen_width, wayland_ctx._bar_height, BGRA_CHANNELS,
                      sheet.image.pixels.data, sheet.image.pixels._size_bytes, sheet.image.sprite_sheet_width,
                      sheet.image.sprite_sheet_height, sheet.image.channels, region->col * sheet.frame_width,
                      region->row * sheet.frame_height, sheet.frame_width, sheet.frame_height, cat_x_with_offset, cat_y,
                      cat_width, cat_height, blit_image_color_order_t::BGRA, blit_image_color_order_t::RGBA,
                      drawing_option);
  }
}

void draw_sprite(platform::wayland::wayland_context_t& ctx, platform::wayland::wayland_shm_buffer_t& shm_buffer,
                 const pkmn_sprite_sheet_t& sheet,
                 blit_image_color_option_flags_t extra_drawing_option = blit_image_color_option_flags_t::Normal) {
  using namespace assets;
  if (sheet.frame_width <= 0 || sheet.frame_height <= 0) {
    return;
  }

  const platform::wayland::wayland_thread_context& wayland_ctx = ctx.thread_context;
  animation_thread_context_t& anim = ctx.animation_context->thread_context;
  // animation_trigger_context_t *trigger_ctx = ctx.animation_trigger_context;
  // platform::wayland::wayland_shared_memory_t *wayland_ctx_shm = wayland_ctx.ctx_shm.ptr;

  assert(wayland_ctx._local_copy_config);
  assert(anim.shm);
  const config::config_t& current_config = *wayland_ctx._local_copy_config.ptr;
  const animation_shared_memory_t& anim_shm = *anim.shm;

  uint8_t *pixels = shm_buffer.pixels.data;
  const size_t pixels_size = shm_buffer.pixels._size_bytes;

  const sprite_sheet_animation_frame_t *region = BONGOCAT_NULLPTR;
  switch (anim_shm.animation_player_result.sprite_sheet_col) {
  case PKMN_FRAME_IDLE1:
    region = &sheet.idle_1;
    break;
  case PKMN_FRAME_IDLE2:
    region = &sheet.idle_2;
    break;
  default:
    assert(anim_shm.animation_player_result.sprite_sheet_col >= 0 &&
           static_cast<size_t>(anim_shm.animation_player_result.sprite_sheet_col) < PKMN_SPRITE_SHEET_COLS);
    break;
  }

  auto [cat_x, cat_y, cat_width, cat_height] = get_position(wayland_ctx, sheet, current_config);
  auto cat_x_with_offset = cat_x + static_cast<int32_t>(anim_shm.movement_offset_x);

  if (region != BONGOCAT_NULLPTR) {
    // draw debug rectangle
    if (current_config.enable_movement_debug >= 1 && current_config.movement_radius > 0) {
      cat_rect_t movement_debug_bar{};
      switch (current_config.cat_align) {
      case config::align_type_t::ALIGN_CENTER:
        movement_debug_bar = {.x = cat_x + (cat_width / 2) - current_config.movement_radius,
                              .y = 0,
                              .width = current_config.movement_radius * 2,
                              .height = wayland_ctx._bar_height};
        break;
      case config::align_type_t::ALIGN_LEFT:
        movement_debug_bar = {
            .x = cat_x, .y = 0, .width = current_config.movement_radius * 2, .height = wayland_ctx._bar_height};
        break;
      case config::align_type_t::ALIGN_RIGHT:
        movement_debug_bar = {.x = cat_x + cat_width - (current_config.movement_radius * 2),
                              .y = 0,
                              .width = current_config.movement_radius * 2,
                              .height = wayland_ctx._bar_height};
        break;
      }

      const bool bar_visible =
          !wayland_ctx._fullscreen_detected && wayland_ctx.bar_visibility == platform::wayland::bar_visibility_t::Show;
      const int effective_opacity = bar_visible ? current_config.overlay_opacity : 0;
      const uint32_t fill = DEBUG_MOVEMENT_BAR_COLOR &
                            (0x00FFFFFF | (static_cast<uint32_t>(effective_opacity) << 24u));  // RGBA, little-endian
      auto *p = reinterpret_cast<uint32_t *>(pixels);
      assert(wayland_ctx._screen_width >= 0);
      [[maybe_unused]] const size_t total_pixels =
          static_cast<size_t>(wayland_ctx._screen_width) * static_cast<size_t>(wayland_ctx._bar_height);
      for (int32_t y = movement_debug_bar.y;
           y < movement_debug_bar.y + movement_debug_bar.height && y < wayland_ctx._bar_height; y++) {
        for (int32_t x = movement_debug_bar.x;
             x < movement_debug_bar.x + movement_debug_bar.width && x < wayland_ctx._screen_width; x++) {
          if (x >= 0 && y >= 0) {
            const size_t pi =
                static_cast<size_t>(x) + (static_cast<size_t>(y) * static_cast<size_t>(wayland_ctx._screen_width));
            assert(pi < total_pixels);
            p[pi] = fill;
          }
        }
      }
    }

    blit_image_color_option_flags_t drawing_option = blit_image_color_option_flags_t::Normal;
    if (current_config.invert_color >= 1) {
      drawing_option = flag_add(drawing_option, blit_image_color_option_flags_t::Invert);
    }
    if (anim_shm.anim_direction >= 1.0f) {
      if (current_config.mirror_x <= 0) {
        drawing_option = flag_add(drawing_option, blit_image_color_option_flags_t::MirrorX);
      }
    } else {
      if (current_config.mirror_x >= 1) {
        drawing_option = flag_add(drawing_option, blit_image_color_option_flags_t::MirrorX);
      }
    }
    if (current_config.mirror_y >= 1) {
      drawing_option = flag_add(drawing_option, blit_image_color_option_flags_t::MirrorY);
    }
    if (extra_drawing_option != blit_image_color_option_flags_t::Normal) {
      drawing_option = flag_add(drawing_option, extra_drawing_option);
    }

    blit_image_scaled(pixels, pixels_size, wayland_ctx._screen_width, wayland_ctx._bar_height, BGRA_CHANNELS,
                      sheet.image.pixels.data, sheet.image.pixels._size_bytes, sheet.image.sprite_sheet_width,
                      sheet.image.sprite_sheet_height, sheet.image.channels, region->col * sheet.frame_width,
                      region->row * sheet.frame_height, sheet.frame_width, sheet.frame_height, cat_x_with_offset, cat_y,
                      cat_width, cat_height, blit_image_color_order_t::BGRA, blit_image_color_order_t::RGBA,
                      drawing_option);
  }
}

void draw_sprite(platform::wayland::wayland_context_t& ctx, platform::wayland::wayland_shm_buffer_t& shm_buffer,
                 const ms_agent_sprite_sheet_t& sheet, int col, int row) {
  if (sheet.frame_width <= 0 || sheet.frame_height <= 0) {
    return;
  }

  const platform::wayland::wayland_thread_context& wayland_ctx = ctx.thread_context;
  // animation_context_t& anim = ctx.animation_trigger_context->anim;
  // animation_trigger_context_t *trigger_ctx = ctx.animation_trigger_context;
  // platform::wayland::wayland_shared_memory_t *wayland_ctx_shm = wayland_ctx.ctx_shm.ptr;

  assert(wayland_ctx._local_copy_config);
  // assert(anim.shm);
  const config::config_t& current_config = *wayland_ctx._local_copy_config.ptr;
  // const animation_shared_memory_t& anim_shm = *anim.shm;

  uint8_t *pixels = shm_buffer.pixels.data;
  const size_t pixels_size = shm_buffer.pixels._size_bytes;

  auto [cat_x, cat_y, cat_width, cat_height] = get_position(wayland_ctx, sheet, current_config);

  blit_image_color_option_flags_t drawing_option = blit_image_color_option_flags_t::Normal;
  if (current_config.invert_color >= 1) {
    drawing_option = flag_add(drawing_option, blit_image_color_option_flags_t::Invert);
  }
  if (current_config.mirror_x >= 1) {
    drawing_option = flag_add(drawing_option, blit_image_color_option_flags_t::MirrorX);
  }
  if (current_config.mirror_y >= 1) {
    drawing_option = flag_add(drawing_option, blit_image_color_option_flags_t::MirrorY);
  }
  if (current_config.enable_antialiasing >= 1) {
    drawing_option = flag_add(drawing_option, blit_image_color_option_flags_t::BilinearInterpolation);
  }

  blit_image_scaled(pixels, pixels_size, wayland_ctx._screen_width, wayland_ctx._bar_height, BGRA_CHANNELS,
                    sheet.image.pixels.data, sheet.image.pixels._size_bytes, sheet.image.sprite_sheet_width,
                    sheet.image.sprite_sheet_height, sheet.image.channels, col * sheet.frame_width,
                    row * sheet.frame_height, sheet.frame_width, sheet.frame_height, cat_x, cat_y, cat_width,
                    cat_height, blit_image_color_order_t::BGRA, blit_image_color_order_t::RGBA, drawing_option);
}

enum class draw_sprite_overwrite_option_t : uint32_t {
  None = 0,
  MovementNoMirror = (1 << 0),
  MovementMirror = (1 << 1),
  DisableThresholdAlpha = (1 << 2),
};
void draw_sprite(platform::wayland::wayland_context_t& ctx, platform::wayland::wayland_shm_buffer_t& shm_buffer,
                 const custom_sprite_sheet_t& sheet, int col, int row,
                 draw_sprite_overwrite_option_t overwrite_option = draw_sprite_overwrite_option_t::None) {
  if (sheet.frame_width <= 0 || sheet.frame_height <= 0) {
    return;
  }

  const platform::wayland::wayland_thread_context& wayland_ctx = ctx.thread_context;
  animation_thread_context_t& anim = ctx.animation_context->thread_context;
  // animation_trigger_context_t *trigger_ctx = ctx.animation_trigger_context;
  // platform::wayland::wayland_shared_memory_t *wayland_ctx_shm = wayland_ctx.ctx_shm.ptr;

  assert(wayland_ctx._local_copy_config);
  assert(anim.shm);
  const config::config_t& current_config = *wayland_ctx._local_copy_config.ptr;
  const animation_shared_memory_t& anim_shm = *anim.shm;

  uint8_t *pixels = shm_buffer.pixels.data;
  const size_t pixels_size = shm_buffer.pixels._size_bytes;

  auto [cat_x, cat_y, cat_width, cat_height] = get_position(wayland_ctx, sheet, current_config);
  auto cat_x_with_offset = cat_x + static_cast<int32_t>(anim_shm.movement_offset_x);

  // draw debug rectangle
  if (current_config.enable_movement_debug >= 1 && current_config.movement_radius > 0) {
    cat_rect_t movement_debug_bar{};
    switch (current_config.cat_align) {
    case config::align_type_t::ALIGN_CENTER:
      movement_debug_bar = {.x = cat_x + (cat_width / 2) - current_config.movement_radius,
                            .y = 0,
                            .width = current_config.movement_radius * 2,
                            .height = wayland_ctx._bar_height};
      break;
    case config::align_type_t::ALIGN_LEFT:
      movement_debug_bar = {
          .x = cat_x, .y = 0, .width = current_config.movement_radius * 2, .height = wayland_ctx._bar_height};
      break;
    case config::align_type_t::ALIGN_RIGHT:
      movement_debug_bar = {.x = cat_x + cat_width - (current_config.movement_radius * 2),
                            .y = 0,
                            .width = current_config.movement_radius * 2,
                            .height = wayland_ctx._bar_height};
      break;
    }

    const bool bar_visible =
        !wayland_ctx._fullscreen_detected && wayland_ctx.bar_visibility == platform::wayland::bar_visibility_t::Show;
    const int effective_opacity = bar_visible ? current_config.overlay_opacity : 0;
    const uint32_t fill = DEBUG_MOVEMENT_BAR_COLOR &
                          (0x00FFFFFF | (static_cast<uint32_t>(effective_opacity) << 24u));  // RGBA, little-endian
    auto *p = reinterpret_cast<uint32_t *>(pixels);
    assert(wayland_ctx._screen_width >= 0);
    [[maybe_unused]] const size_t total_pixels =
        static_cast<size_t>(wayland_ctx._screen_width) * static_cast<size_t>(wayland_ctx._bar_height);
    for (int32_t y = movement_debug_bar.y;
         y < movement_debug_bar.y + movement_debug_bar.height && y < wayland_ctx._bar_height; y++) {
      for (int32_t x = movement_debug_bar.x;
           x < movement_debug_bar.x + movement_debug_bar.width && x < wayland_ctx._screen_width; x++) {
        if (x >= 0 && y >= 0) {
          const size_t pi =
              static_cast<size_t>(x) + (static_cast<size_t>(y) * static_cast<size_t>(wayland_ctx._screen_width));
          assert(pi < total_pixels);
          p[pi] = fill;
        }
      }
    }
  }

  blit_image_color_option_flags_t drawing_option = blit_image_color_option_flags_t::Normal;
  if (current_config.invert_color >= 1) {
    drawing_option = flag_add(drawing_option, blit_image_color_option_flags_t::Invert);
  }
  if (current_config.mirror_y >= 1) {
    drawing_option = flag_add(drawing_option, blit_image_color_option_flags_t::MirrorY);
  }
  if (current_config.enable_antialiasing >= 1) {
    drawing_option = flag_add(drawing_option, blit_image_color_option_flags_t::BilinearInterpolation);
  }
  switch (overwrite_option) {
  case draw_sprite_overwrite_option_t::None:
    if (anim_shm.anim_direction >= 1.0f) {
      if (current_config.mirror_x <= 0) {
        drawing_option = flag_add(drawing_option, blit_image_color_option_flags_t::MirrorX);
      }
    } else {
      if (current_config.mirror_x >= 1) {
        drawing_option = flag_add(drawing_option, blit_image_color_option_flags_t::MirrorX);
      }
    }
    break;
  case draw_sprite_overwrite_option_t::MovementNoMirror:
    if (anim_shm.anim_direction >= 1.0f) {
      drawing_option = flag_remove(drawing_option, blit_image_color_option_flags_t::MirrorX);
    }
    break;
  case draw_sprite_overwrite_option_t::MovementMirror:
    if (anim_shm.anim_direction < 0.0f) {
      drawing_option = flag_add(drawing_option, blit_image_color_option_flags_t::MirrorX);
    }
    break;
  case draw_sprite_overwrite_option_t::DisableThresholdAlpha:
    drawing_option = flag_add(drawing_option, blit_image_color_option_flags_t::DisableThresholdAlpha);
    break;
  }

  blit_image_scaled(pixels, pixels_size, wayland_ctx._screen_width, wayland_ctx._bar_height, BGRA_CHANNELS,
                    sheet.image.pixels.data, sheet.image.pixels._size_bytes, sheet.image.sprite_sheet_width,
                    sheet.image.sprite_sheet_height, sheet.image.channels, col * sheet.frame_width,
                    row * sheet.frame_height, sheet.frame_width, sheet.frame_height, cat_x_with_offset, cat_y,
                    cat_width, cat_height, blit_image_color_order_t::BGRA, blit_image_color_order_t::RGBA,
                    drawing_option);
}

static bool draw_bar_on_buffer(platform::wayland::wayland_context_t& ctx,
                               platform::wayland::wayland_shm_buffer_t& shm_buffer) {
  const platform::wayland::wayland_thread_context& wayland_ctx = ctx.thread_context;
  animation_thread_context_t& anim = ctx.animation_context->thread_context;
  // animation_trigger_context_t *trigger_ctx = ctx.animation_trigger_context;
  // platform::wayland::wayland_shared_memory_t *wayland_ctx_shm = wayland_ctx.ctx_shm.ptr;

  // read-only
  assert(wayland_ctx._local_copy_config);
  assert(anim.shm);
  const config::config_t& current_config = *wayland_ctx._local_copy_config.ptr;

  assert(shm_buffer.pixels.data);
  uint8_t *pixels = shm_buffer.pixels.data;
  const size_t pixels_size = shm_buffer.pixels._size_bytes;

  const bool bar_visible =
      !wayland_ctx._fullscreen_detected && wayland_ctx.bar_visibility == platform::wayland::bar_visibility_t::Show;
  const int effective_opacity = bar_visible ? current_config.overlay_opacity : 0;

  assert(wayland_ctx._screen_width >= 0);
  assert(wayland_ctx._bar_height >= 0);
  assert(effective_opacity >= 0);

  // Fast clear with 32-bit fill
  const uint32_t fill = DEFAULT_FILL_COLOR | (static_cast<uint32_t>(effective_opacity) << 24u);  // RGBA, little-endian
  auto *p = reinterpret_cast<uint32_t *>(pixels);
  const size_t total_pixels =
      static_cast<size_t>(wayland_ctx._screen_width) * static_cast<size_t>(wayland_ctx._bar_height);
  if (current_config.enable_debug >= 1) {
    if (const size_t expected_bytes = total_pixels * sizeof(uint32_t); expected_bytes > pixels_size) {
      BONGOCAT_LOG_VERBOSE("draw_bar: pixel write would overflow buffer (expected %zu bytes, have %zu). Aborting draw.",
                           expected_bytes, pixels_size);
      return false;
    }
  }
  for (size_t i = 0; i < total_pixels; i++) {
    p[i] = fill;
  }

  {
    platform::LockGuard guard(anim.anim_lock);
    const animation_shared_memory_t& anim_shm = *anim.shm;

    if (bar_visible) {
      switch (anim_shm.anim_type) {
      case config::config_animation_sprite_sheet_layout_t::None:
        break;
      case config::config_animation_sprite_sheet_layout_t::Bongocat: {
        if constexpr (!features::EnableLazyLoadAssets || features::EnablePreloadAssets) {
          assert(anim_shm.anim_index >= 0 && static_cast<size_t>(anim_shm.anim_index) < anim_shm.bongocat_anims.count);
        }
        const animation_t& cat_anim = get_current_animation(anim);
        assert(cat_anim.type == animation_t::type_t::Bongocat);
        const bongocat_sprite_sheet_t& sheet = cat_anim.bongocat;
        draw_sprite(ctx, shm_buffer, sheet,
                    current_config.enable_antialiasing >= 1 ? blit_image_color_option_flags_t::BilinearInterpolation
                                                            : blit_image_color_option_flags_t::Normal);
      } break;
      case config::config_animation_sprite_sheet_layout_t::Dm: {
        if constexpr (!features::EnableLazyLoadAssets || features::EnablePreloadAssets) {
          switch (anim_shm.anim_dm_set) {
          case config::config_animation_dm_set_t::None:
            break;
          case config::config_animation_dm_set_t::min_dm: {
            assert(anim_shm.anim_index >= 0 && static_cast<size_t>(anim_shm.anim_index) < anim_shm.min_dm_anims.count);
          } break;
          case config::config_animation_dm_set_t::dm: {
            assert(anim_shm.anim_index >= 0 && static_cast<size_t>(anim_shm.anim_index) < anim_shm.dm_anims.count);
          } break;
          case config::config_animation_dm_set_t::dm20: {
            assert(anim_shm.anim_index >= 0 && static_cast<size_t>(anim_shm.anim_index) < anim_shm.dm20_anims.count);
          } break;
          case config::config_animation_dm_set_t::dmx: {
            assert(anim_shm.anim_index >= 0 && static_cast<size_t>(anim_shm.anim_index) < anim_shm.dmx_anims.count);
          } break;
          case config::config_animation_dm_set_t::pen: {
            assert(anim_shm.anim_index >= 0 && static_cast<size_t>(anim_shm.anim_index) < anim_shm.pen_anims.count);
          } break;
          case config::config_animation_dm_set_t::pen20: {
            assert(anim_shm.anim_index >= 0 && static_cast<size_t>(anim_shm.anim_index) < anim_shm.pen20_anims.count);
          } break;
          case config::config_animation_dm_set_t::dmc: {
            assert(anim_shm.anim_index >= 0 && static_cast<size_t>(anim_shm.anim_index) < anim_shm.dmc_anims.count);
          } break;
          case config::config_animation_dm_set_t::dmall: {
            assert(anim_shm.anim_index >= 0 && static_cast<size_t>(anim_shm.anim_index) < anim_shm.dmall_anims.count);
          } break;
          }
        }
        const animation_t& dm_anim = get_current_animation(anim);
        assert(dm_anim.type == animation_t::type_t::Dm);
        const dm_sprite_sheet_t& sheet = dm_anim.dm;
        draw_sprite(ctx, shm_buffer, sheet);
      } break;
      case config::config_animation_sprite_sheet_layout_t::Pkmn: {
        if constexpr (!features::EnableLazyLoadAssets || features::EnablePreloadAssets) {
          assert(anim_shm.anim_index >= 0 && static_cast<size_t>(anim_shm.anim_index) < anim_shm.pkmn_anims.count);
        }
        const animation_t& pkmn_anim = get_current_animation(anim);
        assert(pkmn_anim.type == animation_t::type_t::Pkmn);
        const auto& sheet = pkmn_anim.pkmn;
        draw_sprite(ctx, shm_buffer, sheet);
      } break;
      case config::config_animation_sprite_sheet_layout_t::MsAgent: {
        if constexpr (!features::EnableLazyLoadAssets || features::EnablePreloadAssets) {
          assert(anim_shm.anim_index >= 0 && static_cast<size_t>(anim_shm.anim_index) < anim_shm.ms_anims.count);
        }
        const animation_t& ms_anim = get_current_animation(anim);
        assert(ms_anim.type == animation_t::type_t::MsAgent);
        const ms_agent_sprite_sheet_t& sheet = ms_anim.ms_agent;
        const int col = anim_shm.animation_player_result.sprite_sheet_col;
        const int row = anim_shm.animation_player_result.sprite_sheet_row;
        draw_sprite(ctx, shm_buffer, sheet, col, row);
      } break;
      case config::config_animation_sprite_sheet_layout_t::Custom: {
        const int col = anim_shm.animation_player_result.sprite_sheet_col;
        const int row = anim_shm.animation_player_result.sprite_sheet_row;
        assert(anim_shm.anim_index >= 0);
        switch (anim_shm.anim_custom_set) {
        case config::config_animation_custom_set_t::None:
          break;
        case config::config_animation_custom_set_t::misc:
          if (features::EnableMiscEmbeddedAssets) {
            if constexpr (!features::EnableLazyLoadAssets || features::EnablePreloadAssets) {
              assert(anim_shm.anim_index >= 0 && static_cast<size_t>(anim_shm.anim_index) < anim_shm.misc_anims.count);
            }
            const animation_t& custom_anim = get_current_animation(anim);
            assert(custom_anim.type == animation_t::type_t::Custom);
            const custom_sprite_sheet_t& sheet = custom_anim.custom;
            draw_sprite(ctx, shm_buffer, sheet, col, row);
          }
          break;
        case config::config_animation_custom_set_t::pmd:
          if (features::EnablePmdEmbeddedAssets) {
            if constexpr (!features::EnableLazyLoadAssets || features::EnablePreloadAssets) {
              assert(anim_shm.anim_index >= 0 && static_cast<size_t>(anim_shm.anim_index) < anim_shm.pmd_anims.count);
            }
            const animation_t& custom_anim = get_current_animation(anim);
            assert(custom_anim.type == animation_t::type_t::Custom);
            const custom_sprite_sheet_t& sheet = custom_anim.custom;
            draw_sprite_overwrite_option_t overwrite_drawing_options{draw_sprite_overwrite_option_t::None};
            // Mirroring for pmd sprite sheets not needed
            /*
            switch (anim_shm.animation_player_result.overwrite_mirror_x) {
                case animation_player_custom_overwrite_mirror_x::None:
                    break;
                case animation_player_custom_overwrite_mirror_x::NoMirror:
                    overwrite_drawing_options =
            flag_add(overwrite_drawing_options,draw_sprite_overwrite_option_t::MovementNoMirror); break; case
            animation_player_custom_overwrite_mirror_x::Mirror: overwrite_drawing_options =
            flag_add(overwrite_drawing_options,draw_sprite_overwrite_option_t::MovementMirror); break;
            }
            */

            draw_sprite(ctx, shm_buffer, sheet, col, row, overwrite_drawing_options);
          }
          break;
        case config::config_animation_custom_set_t::custom:
          if (features::EnableCustomSpriteSheetsAssets && anim_shm.anim_index >= 0 &&
              static_cast<size_t>(anim_shm.anim_index) == assets::CUSTOM_ANIM_INDEX) {
            const animation_t& custom_anim = get_current_animation(anim);
            assert(custom_anim.type == animation_t::type_t::Custom);
            const custom_sprite_sheet_t& sheet = custom_anim.custom;

            draw_sprite_overwrite_option_t overwrite_drawing_options{draw_sprite_overwrite_option_t::None};
            switch (anim_shm.animation_player_result.overwrite_mirror_x) {
            case animation_player_custom_overwrite_mirror_x::None:
              break;
            case animation_player_custom_overwrite_mirror_x::NoMirror:
              overwrite_drawing_options =
                  flag_add(overwrite_drawing_options, draw_sprite_overwrite_option_t::MovementNoMirror);
              break;
            case animation_player_custom_overwrite_mirror_x::Mirror:
              overwrite_drawing_options =
                  flag_add(overwrite_drawing_options, draw_sprite_overwrite_option_t::MovementMirror);
              break;
            }
            overwrite_drawing_options =
                flag_add(overwrite_drawing_options, draw_sprite_overwrite_option_t::DisableThresholdAlpha);

            draw_sprite(ctx, shm_buffer, sheet, col, row, overwrite_drawing_options);
          }
          break;
        }
      } break;
      }
    } else {
      BONGOCAT_LOG_VERBOSE("skip drawing, keep buffer clean: fullscreen=%d, visibility=%d",
                           wayland_ctx._fullscreen_detected, wayland_ctx.bar_visibility);
    }
  }

  return true;
}

draw_bar_result_t draw_bar(platform::wayland::wayland_context_t& ctx) {
  platform::wayland::wayland_thread_context& wayland_ctx = ctx.thread_context;
  // animation_context_t& anim = ctx.animation_trigger_context->anim;
  // animation_trigger_context_t *trigger_ctx = ctx.animation_trigger_context;
  platform::wayland::wayland_shared_memory_t& wayland_ctx_shm = *wayland_ctx.ctx_shm.ptr;

  // read-only
  assert(wayland_ctx._local_copy_config);
  // assert(anim.shm);
  const config::config_t& current_config = *wayland_ctx._local_copy_config.ptr;

  if (!atomic_load(&wayland_ctx_shm.configured)) {
    BONGOCAT_LOG_VERBOSE("Surface not configured yet, skipping draw");
    return draw_bar_result_t::Skip;
  }

  // assert(wayland_ctx_shm->current_buffer_index >= 0);
  static_assert(platform::wayland::WAYLAND_NUM_BUFFERS > 0);
  static_assert(platform::wayland::WAYLAND_NUM_BUFFERS <= INT_MAX);
  [[maybe_unused]] const size_t current_buffer_index = wayland_ctx_shm.current_buffer_index;
  [[maybe_unused]] size_t next_buffer_index =
      (wayland_ctx_shm.current_buffer_index + 1) % platform::wayland::WAYLAND_NUM_BUFFERS;

  platform::wayland::wayland_shm_buffer_t *shm_buffer = BONGOCAT_NULLPTR;
  if constexpr (platform::wayland::WAYLAND_NUM_BUFFERS == 1) {
    shm_buffer = &wayland_ctx_shm.buffers[0];
    if (atomic_load(&shm_buffer->busy)) {
      BONGOCAT_LOG_VERBOSE("Wayland: single buffer still busy, skip draw");
      atomic_store(&wayland_ctx._redraw_after_frame, true);
      return draw_bar_result_t::Busy;
    }
  } else {
    for (size_t i = 0; i < platform::wayland::WAYLAND_NUM_BUFFERS; i++) {
      // assert(next_buffer_index >= 0);
      auto *buf = &wayland_ctx_shm.buffers[next_buffer_index];
      if (!atomic_load(&buf->busy)) {
        shm_buffer = buf;
        next_buffer_index = i;
        break;
      }
      next_buffer_index = (next_buffer_index + 1) % platform::wayland::WAYLAND_NUM_BUFFERS;
    }

    if (shm_buffer == BONGOCAT_NULLPTR) {
      BONGOCAT_LOG_VERBOSE("draw_bar: All buffers busy, skip drawing");
      atomic_store(&wayland_ctx._redraw_after_frame, true);
      return draw_bar_result_t::Busy;
    }
  }

  assert(shm_buffer);
  if (!shm_buffer->pixels) {
    BONGOCAT_LOG_VERBOSE("draw_bar: Config or pixels not ready, skipping draw");
    return draw_bar_result_t::Skip;
  }

  // for calc render time
  [[maybe_unused]] const auto t0 = platform::get_current_time_us();

  BONGOCAT_LOG_VERBOSE("draw_bar: using buffer %zu", next_buffer_index);
  if constexpr (platform::wayland::WAYLAND_NUM_BUFFERS > 1) {
    wayland_ctx_shm.current_buffer_index = next_buffer_index;
    BONGOCAT_LOG_VERBOSE("draw_bar: new current_buffer_index: %i", next_buffer_index);
  }
  assert(wayland_ctx_shm.current_buffer_index < platform::wayland::WAYLAND_NUM_BUFFERS);

  assert(shm_buffer);
  draw_bar_on_buffer(ctx, *shm_buffer);

  assert(shm_buffer->buffer);
  wl_surface_attach(wayland_ctx.surface, shm_buffer->buffer, 0, 0);
  wl_surface_damage_buffer(wayland_ctx.surface, 0, 0, wayland_ctx._screen_width, wayland_ctx._bar_height);

  {
    platform::LockGuard guard(wayland_ctx._frame_cb_lock);
    if (!atomic_load(&wayland_ctx._frame_pending) && wayland_ctx._frame_cb == BONGOCAT_NULLPTR) {
      wayland_ctx._frame_cb = wl_surface_frame(wayland_ctx.surface);
      wl_callback_add_listener(wayland_ctx._frame_cb, &platform::wayland::details::frame_listener, &ctx);
      atomic_store(&wayland_ctx._frame_pending, true);
      BONGOCAT_LOG_VERBOSE("draw_bar: Set frame pending");
    } else {
      // Frame callback is pending: queue redraw after current frame
      atomic_store(&wayland_ctx._redraw_after_frame, true);
      BONGOCAT_LOG_VERBOSE("draw_bar: Queued redraw after pending frame");
    }
  }

  wl_surface_commit(wayland_ctx.surface);

  atomic_store(&shm_buffer->busy, true);

  /// @TODO: flush here or on main ???
  const int flush_ret = wl_display_flush(wayland_ctx.display);
  if (flush_ret == -1 && errno == EAGAIN) {
    // send buffer full; need to make progress by reading pending events first
    wl_display_cancel_read(wayland_ctx.display);
    if (wl_display_dispatch_pending(wayland_ctx.display) == -1) {
      BONGOCAT_LOG_ERROR("draw_bar: wl_display_dispatch_pending failed after EAGAIN");
    }
  } else if (flush_ret == -1) {
    BONGOCAT_LOG_ERROR("draw_bar: wl_display_flush failed: %s", strerror(errno));
    wl_display_cancel_read(wayland_ctx.display);
    wl_display_dispatch_pending(wayland_ctx.display);
  }

  const platform::timestamp_ms_t now = platform::get_current_time_ms();
  assert(current_config.fps > 0);
  if (const platform::time_ms_t frame_interval_ms = 1000 / current_config.fps;
      wayland_ctx._last_frame_timestamp_ms <= 0 || (now - wayland_ctx._last_frame_timestamp_ms) >= frame_interval_ms) {
    wayland_ctx._last_frame_timestamp_ms = now;
  }

  [[maybe_unused]] const auto t1 = platform::get_current_time_us();
  BONGOCAT_LOG_VERBOSE("draw_bar: time %.3fms (%.6fsec)", static_cast<double>(t1 - t0) / 1000.0,
                       static_cast<double>(t1 - t0) / 1000000.0);

  return draw_bar_result_t::NoFlushNeeded;
}
}  // namespace bongocat::animation
