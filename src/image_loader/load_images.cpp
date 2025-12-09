#include "image_loader/load_images.h"

#include "graphics/animation.h"
#include "graphics/animation_context.h"
#include "graphics/drawing.h"
#include "utils/memory.h"

#include <cassert>

namespace bongocat::animation {
// =============================================================================
// IMAGE LOADING MODULE
// =============================================================================

BONGOCAT_NODISCARD static created_result_t<generic_sprite_sheet_t>
load_sprite_sheet_from_memory(const uint8_t *sprite_data, size_t sprite_data_size, int frame_columns, int frame_rows,
                              int padding_x, int padding_y) {
  generic_sprite_sheet_t ret;

  auto [sprite_sheet, sprite_sheet_error] = load_image(sprite_data, sprite_data_size, RGBA_CHANNELS);
  if (sprite_sheet_error != bongocat_error_t::BONGOCAT_SUCCESS) [[unlikely]] {
    BONGOCAT_LOG_ERROR("Failed to load sprite sheet. %dx%d", sprite_sheet.width, sprite_sheet.height);
    return sprite_sheet_error;
  }

  assert(frame_columns != 0 && frame_rows != 0 && sprite_sheet.width % frame_columns == 0 &&
         sprite_sheet.height % frame_rows == 0);
  if (frame_columns == 0 || frame_rows == 0 || sprite_sheet.width % frame_columns != 0 ||
      sprite_sheet.height % frame_rows != 0) {
    BONGOCAT_LOG_ERROR(
        "Sprite sheet dimensions not divisible by frame grid; frame_columns=%d, frame_rows=%d vs %dx%d sprite size",
        frame_columns, frame_rows, sprite_sheet.width, sprite_sheet.height);
    return bongocat_error_t::BONGOCAT_ERROR_INVALID_PARAM;
  }

  const auto frame_width = sprite_sheet.width / frame_columns;
  const auto frame_height = sprite_sheet.height / frame_rows;
  const auto total_frames = frame_columns * frame_rows;

  const auto dest_frame_width = frame_width + (padding_x * 2);
  const auto dest_frame_height = frame_height + (padding_y * 2);
  const auto dest_pixels_width = dest_frame_width * frame_columns;
  const auto dest_pixels_height = dest_frame_height * frame_rows;
  assert(dest_pixels_width >= 0);
  assert(dest_pixels_height >= 0);
  assert(sprite_sheet.channels >= 0);
  const size_t dest_pixels_size = static_cast<size_t>(dest_pixels_width) * static_cast<size_t>(dest_pixels_height) *
                                  static_cast<size_t>(sprite_sheet.channels);
  auto dest_pixels = make_allocated_array<uint8_t>(dest_pixels_size);
  if (!dest_pixels) {
    BONGOCAT_LOG_ERROR("Failed to allocate memory for dest_pixels (%zu bytes)\n", dest_pixels_size);
    return bongocat_error_t::BONGOCAT_ERROR_MEMORY;
  }
  // memset(dest_pixels.data, 0, dest_pixels_size);

  const auto src_frame_width = frame_width;
  const auto src_frame_height = frame_height;
  const auto src_pixels_width = sprite_sheet.width;
  const auto src_pixels_height = sprite_sheet.height;
  assert(src_pixels_width >= 0);
  assert(src_pixels_height >= 0);
  assert(sprite_sheet.channels >= 0);
  const size_t src_pixels_size = static_cast<size_t>(src_pixels_width) * static_cast<size_t>(src_pixels_height) *
                                 static_cast<size_t>(sprite_sheet.channels);
  size_t frame_index = 0;
  for (int row = 0; row < frame_rows; ++row) {
    for (int col = 0; col < frame_columns; ++col) {
      const auto src_x = col * src_frame_width;
      const auto src_y = row * src_frame_height;
      const auto dst_x = (col * dest_frame_width) + padding_x;
      const auto dst_y = (row * dest_frame_height) + padding_y;
      [[maybe_unused]] const auto src_idx = (src_y * src_pixels_width + src_x) * sprite_sheet.channels;
      [[maybe_unused]] const auto dst_idx = (dst_y * dest_pixels_width + dst_x) * sprite_sheet.channels;
      assert(src_idx >= 0);
      assert(dst_idx >= 0);

      bool set_frames = false;
      for (int fy = 0; fy < src_frame_height; fy++) {
        for (int fx = 0; fx < src_frame_width; fx++) {
          const auto src_px_idx = ((src_y + fy) * src_pixels_width + (src_x + fx)) * sprite_sheet.channels;
          const auto dst_px_idx = ((dst_y + fy) * dest_pixels_width + (dst_x + fx)) * sprite_sheet.channels;

          if (src_px_idx >= 0 && dst_px_idx >= 0 && static_cast<size_t>(src_px_idx) < src_pixels_size &&
              static_cast<size_t>(dst_px_idx) < dest_pixels_size) {
            drawing_copy_pixel(dest_pixels.data, sprite_sheet.channels, dst_px_idx, sprite_sheet.pixels,
                               sprite_sheet.channels, src_px_idx, blit_image_color_option_flags_t::Normal,
                               blit_image_color_order_t::RGBA, blit_image_color_order_t::RGBA);
            if (!set_frames && frame_index < MAX_NUM_FRAMES) {
              set_frames = true;
            }
          }
        }
      }
      if (frame_index < MAX_NUM_FRAMES) {
        if (set_frames) {
          ret.frames[frame_index] = {.valid = true, .col = col, .row = row};
        } else {
          ret.frames[frame_index] = {
              .valid = false,
              .col = 0,
              .row = 0,
          };
        }
      }

      frame_index++;
    }
  }

  ret.image.sprite_sheet_width = sprite_sheet.width;
  ret.image.sprite_sheet_height = sprite_sheet.height;
  ret.image.channels = sprite_sheet.channels;
  // move pixels ownership into out_frames
  ret.image.pixels = bongocat::move(dest_pixels);
  dest_pixels = BONGOCAT_NULLPTR;
  ret.frame_width = dest_frame_width;
  ret.frame_height = dest_frame_height;
  ret.total_frames = total_frames;

  return ret;
}

created_result_t<generic_sprite_sheet_t> anim_sprite_sheet_from_embedded_images(get_sprite_callback_t get_sprite,
                                                                                size_t embedded_images_count) {
  generic_sprite_sheet_t ret;

  int total_frames = 0;
  int max_frame_width = 0;
  int max_frame_height = 0;
  int max_channels = 0;
  auto loaded_images = make_allocated_array<Image>(embedded_images_count);
  for (size_t i = 0; i < embedded_images_count && i < loaded_images.count; i++) {
    const assets::embedded_image_t img = get_sprite(i);

    BONGOCAT_LOG_DEBUG("Loading embedded image: %s", img.name);
    auto [loaded_image, image_error] = load_image(img.data, img.size, RGBA_CHANNELS);
    if (image_error != bongocat_error_t::BONGOCAT_SUCCESS) [[unlikely]] {
      BONGOCAT_LOG_ERROR("Failed to load embedded image: %s (%d)", img.name, image_error);
      continue;
    }
    loaded_images[i] = bongocat::move(loaded_image);
    assert(loaded_images[i].width >= 0);
    assert(loaded_images[i].height >= 0);
    assert(loaded_images[i].channels >= 0);

    // update image properties
    max_frame_width = loaded_images[i].width > max_frame_width ? loaded_images[i].width : max_frame_width;
    max_frame_height = loaded_images[i].height > max_frame_height ? loaded_images[i].height : max_frame_height;
    max_channels = loaded_images[i].channels > max_channels ? loaded_images[i].channels : max_channels;

    BONGOCAT_LOG_DEBUG("Loaded %dx%d embedded image", loaded_images[i].width, loaded_images[i].height);
    total_frames++;
  }

  ret.frame_width = max_frame_width;
  ret.frame_height = max_frame_height;
  ret.total_frames = total_frames;
  ret.image.sprite_sheet_width = max_frame_width * total_frames;
  ret.image.sprite_sheet_height = max_frame_height;
  ret.image.channels = max_channels;
  // create sprite sheet
  assert(ret.image.sprite_sheet_width >= 0);
  assert(ret.image.sprite_sheet_height >= 0);
  assert(ret.image.channels >= 0);
  ret.image.pixels = make_allocated_array<uint8_t>(static_cast<size_t>(ret.image.sprite_sheet_width) *
                                                   static_cast<size_t>(ret.image.sprite_sheet_height) *
                                                   static_cast<size_t>(ret.image.channels));
  if (!ret.image.pixels) {
    ret.frame_width = 0;
    ret.frame_height = 0;
    ret.total_frames = 0;
    ret.image.sprite_sheet_width = 0;
    ret.image.sprite_sheet_height = 0;
    ret.image.channels = 0;

    for (size_t i = 0; i < loaded_images.count; i++) {
      if (loaded_images[i].pixels != BONGOCAT_NULLPTR) {
        ::free(loaded_images[i].pixels);
        loaded_images[i].pixels = BONGOCAT_NULLPTR;
      }
    }
    return bongocat_error_t::BONGOCAT_ERROR_MEMORY;
  }
  // reset frames
  // memset(anim->pixels.data, 0, anim->pixels.count * sizeof(uint8_t));
  for (size_t i = 0; i < MAX_NUM_FRAMES; i++) {
    ret.frames[i] = {};
  }
  // append images into one sprite sheet
  assert(max_frame_width >= 0);
  assert(max_channels >= 0);
  assert(ret.image.sprite_sheet_width >= 0);
  for (size_t frame = 0; frame < loaded_images.count; frame++) {
    const auto& src = loaded_images[frame];
    assert(src.channels >= 0);
    assert(src.width >= 0);
    assert(src.height >= 0);
    if (src.pixels != BONGOCAT_NULLPTR && src.height > 0) {
      // copy pixel data of sub-region
      assert(src.height >= 0);
      for (size_t y = 0; y < static_cast<size_t>(src.height); y++) {
        unsigned char *dest_row = ret.image.pixels.data + ((y * static_cast<size_t>(ret.image.sprite_sheet_width)) +
                                                           (frame * static_cast<size_t>(max_frame_width))) *
                                                              static_cast<size_t>(max_channels);
        const unsigned char *src_row =
            src.pixels + (y * static_cast<size_t>(src.width) * static_cast<size_t>(src.channels));
        memcpy(dest_row, src_row, static_cast<size_t>(src.width) * static_cast<size_t>(max_channels));
      }

      // update sub-region
      if (frame < MAX_NUM_FRAMES) {
        ret.frames[frame] = {.valid = true, .col = static_cast<int>(frame), .row = 0};
      }
    } else {
      if (frame < MAX_NUM_FRAMES) {
        ret.frames[frame] = {.valid = false, .col = static_cast<int>(frame), .row = 0};
      }
    }
  }

  for (size_t i = 0; i < loaded_images.count; i++) {
    if (loaded_images[i].pixels != BONGOCAT_NULLPTR) {
      ::free(loaded_images[i].pixels);
      loaded_images[i].pixels = BONGOCAT_NULLPTR;
    }
  }
  return ret;
}

created_result_t<generic_sprite_sheet_t> load_sprite_sheet_anim(const config::config_t& config,
                                                                const assets::embedded_image_t& sprite_sheet_image,
                                                                int sprite_sheet_cols, int sprite_sheet_rows) {
  if (sprite_sheet_cols < 0 || sprite_sheet_rows < 0) {
    return bongocat_error_t::BONGOCAT_ERROR_INVALID_PARAM;
  }

  assert(sprite_sheet_image.size <= INT_MAX);
  auto result = load_sprite_sheet_from_memory(sprite_sheet_image.data, sprite_sheet_image.size, sprite_sheet_cols,
                                              sprite_sheet_rows, config.padding_x, config.padding_y);
  if (result.error != bongocat_error_t::BONGOCAT_SUCCESS) [[unlikely]] {
    BONGOCAT_LOG_ERROR("Sprite Sheet load failed: %s", sprite_sheet_image.name);
    return result.error;
  }
  if (result.result.total_frames <= 0) {
    BONGOCAT_LOG_ERROR("Sprite Sheet is empty: %s", sprite_sheet_image.name);
    return bongocat_error_t::BONGOCAT_ERROR_ANIMATION;
  }

  // assume every frame is the same size, pick first frame
  BONGOCAT_LOG_DEBUG("Loaded %dx%d sprite sheet with %d frames", result.result.image.sprite_sheet_width,
                     result.result.image.sprite_sheet_height, result.result.total_frames);

  return result;
}
}  // namespace bongocat::animation