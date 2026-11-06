#include "image_loader/load_images.h"
#include "image_loader/load_svgs.h"
#include "graphics/animation.h"
#include "graphics/animation_thread_context.h"
#include "graphics/drawing.h"
#include "utils/memory.h"
#include <cassert>
#include <cstring>
#include <cstdint>

namespace bongocat::animation {
// =============================================================================
// SPRITE SHEET LAYOUT (shared by all image backends)
// =============================================================================

namespace details {
  sprite_sheet_layout_mapper_t make_sprite_sheet_layout_mapper(int32_t src_width, int32_t src_height,
                                                               sprite_sheet_layout_t layout) {
    sprite_sheet_layout_mapper_t ret;
    if (src_width <= 0 || src_height <= 0 || layout.frame_columns <= 0 || layout.frame_rows <= 0 ||
        layout.padding_x < 0 || layout.padding_y < 0 || src_width % layout.frame_columns != 0 ||
        src_height % layout.frame_rows != 0) {
      BONGOCAT_LOG_ERROR(
          "Sprite sheet dimensions not divisible by frame grid; frame_columns=%d, frame_rows=%d vs %dx%d sprite size",
          layout.frame_columns, layout.frame_rows, src_width, src_height);
      return ret;
    }
    ret.src_width = src_width;
    ret.src_height = src_height;
    ret.frame_width = src_width / layout.frame_columns;
    ret.frame_height = src_height / layout.frame_rows;
    ret.padding_x = layout.padding_x;
    ret.padding_y = layout.padding_y;
    ret.dest_width = (ret.frame_width + (layout.padding_x * 2)) * layout.frame_columns;
    ret.dest_height = (ret.frame_height + (layout.padding_y * 2)) * layout.frame_rows;
    ret.valid = true;
    return ret;
  }

  created_result_t<generic_sprite_sheet_image_t> allocate_sprite_sheet_image(const sprite_sheet_layout_mapper_t& mapper) {
    if (!mapper.valid) [[unlikely]] {
      return bongocat_error_t::BONGOCAT_ERROR_INVALID_PARAM;
    }
    generic_sprite_sheet_image_t ret;
    const size_t size_bytes = mapper.dest_size_bytes();
    ret.pixels = make_allocated_array_uninitialized<uint8_t>(size_bytes);
    if (!ret.pixels) [[unlikely]] {
      BONGOCAT_LOG_ERROR("Failed to allocate memory for sprite sheet (%zu bytes)", size_bytes);
      return bongocat_error_t::BONGOCAT_ERROR_MEMORY;
    }
    /// @TODO: only memset to zero, when padding is needed, otherwise the whole pace gets used anyway
    if (mapper.has_padding()) {
      ::memset(ret.pixels.data, 0, size_bytes);
    }
    ret.sprite_sheet_width = mapper.dest_width;
    ret.sprite_sheet_height = mapper.dest_height;
    ret.channels = RGBA_CHANNELS;
    return ret;
  }

  void copy_rgba_into_sprite_sheet_layout(generic_sprite_sheet_image_t& dest, const sprite_sheet_layout_mapper_t& mapper,
                                          const uint8_t *src_rgba) {
    assert(mapper.valid);
    assert(dest.pixels._size_bytes >= mapper.dest_size_bytes());
    if (!mapper.has_padding()) {
      // 1:1 copy without padding
      ::memcpy(dest.pixels.data, src_rgba, mapper.dest_size_bytes());
      return;
    }
    const size_t src_stride = static_cast<size_t>(mapper.src_width) * RGBA_CHANNELS;
    const size_t dest_stride = static_cast<size_t>(mapper.dest_width) * RGBA_CHANNELS;
    const size_t frame_row_bytes = static_cast<size_t>(mapper.frame_width) * RGBA_CHANNELS;
    const int32_t frame_columns = mapper.src_width / mapper.frame_width;
    for (int32_t y = 0; y < mapper.src_height; ++y) {
      const uint8_t *src_row = src_rgba + (static_cast<size_t>(y) * src_stride);
      uint8_t *dest_row = dest.pixels.data + (static_cast<size_t>(mapper.dest_y(y)) * dest_stride);
      for (int32_t col = 0; col < frame_columns; ++col) {
        const int32_t src_x = col * mapper.frame_width;
        ::memcpy(dest_row + (static_cast<size_t>(mapper.dest_x(src_x)) * RGBA_CHANNELS),
                 src_row + (static_cast<size_t>(src_x) * RGBA_CHANNELS), frame_row_bytes);
      }
    }
  }
}  // namespace details

// =============================================================================
// IMAGE LOADING MODULE
// =============================================================================

BONGOCAT_NODISCARD static created_result_t<generic_sprite_sheet_t>
load_sprite_sheet_from_memory(const uint8_t *sprite_data, size_t sprite_data_size, int frame_columns, int frame_rows,
                              int padding_x, int padding_y) {
  // decode straight into the final (padded) layout
  auto [image, image_error] = load_sprite_sheet_image(sprite_data, sprite_data_size,
                                                      {.frame_columns = frame_columns,
                                                       .frame_rows = frame_rows,
                                                       .padding_x = padding_x,
                                                       .padding_y = padding_y});
  if (image_error != bongocat_error_t::BONGOCAT_SUCCESS) [[unlikely]] {
    BONGOCAT_LOG_ERROR("Failed to load sprite sheet (%d cols x %d rows)", frame_columns, frame_rows);
    return image_error;
  }
  assert(frame_columns > 0 && frame_rows > 0);
  assert(image.sprite_sheet_width % frame_columns == 0);
  assert(image.sprite_sheet_height % frame_rows == 0);

  generic_sprite_sheet_t ret;
  // padded frame size; image.sprite_sheet_width/height are the padded size (= row stride for blitting)
  ret.frame_width = image.sprite_sheet_width / frame_columns;
  ret.frame_height = image.sprite_sheet_height / frame_rows;
  ret.total_frames = frame_columns * frame_rows;
  ret.image = bongocat::move(image);

  int frame_index = 0;
  for (int row = 0; row < frame_rows; ++row) {
    for (int col = 0; col < frame_columns; ++col) {
      if (static_cast<size_t>(frame_index) < MAX_NUM_FRAMES) {
        ret.frames[frame_index] = {.valid = true, .col = col, .row = row};
      }
      frame_index++;
    }
  }

  return ret;
}

namespace details {
  struct png_size_t {
    int32_t width{0};
    int32_t height{0};
    bool valid{false};
  };
  /// read width/height from the PNG header (IHDR) without decoding anything
  BONGOCAT_NODISCARD static png_size_t read_png_size(const uint8_t *data, size_t size) {
    // 8 bytes signature, 4 bytes chunk length, "IHDR", 4 bytes width, 4 bytes height (big endian)
    static constexpr uint8_t PNG_SIGNATURE[8] = {0x89, 'P', 'N', 'G', '\r', '\n', 0x1A, '\n'};
    static constexpr size_t PNG_SIGNATURE_OFFSET = 8 + 4;
    static constexpr size_t PNG_IHDR_MIN_SIZE = 24;
    static constexpr const char PNG_IHDR[] = "IHDR";
    static constexpr size_t PNG_IHDR_LEN = sizeof(PNG_IHDR)-1;
    static_assert(PNG_IHDR_LEN == 4);
    static constexpr size_t PNG_SIGNATURE_IHDR_OFFSET = PNG_SIGNATURE_OFFSET + PNG_IHDR_LEN;
    static constexpr size_t PNG_SIGNATURE_IHDR_OFFSET_WIDTH = PNG_SIGNATURE_IHDR_OFFSET + 4;

    png_size_t ret;
    if (data == BONGOCAT_NULLPTR || size < PNG_IHDR_MIN_SIZE) {
      return ret;
    }
    if (::memcmp(data, PNG_SIGNATURE, sizeof(PNG_SIGNATURE)) != 0 ||
        ::memcmp(data + PNG_SIGNATURE_OFFSET, PNG_IHDR, PNG_IHDR_LEN) != 0) {
      return ret;
    }
    const auto read_u32_be = [](const uint8_t *p) -> uint32_t {
      return (static_cast<uint32_t>(p[0]) << 24u) | (static_cast<uint32_t>(p[1]) << 16u) |
             (static_cast<uint32_t>(p[2]) << 8u) | static_cast<uint32_t>(p[3]);
    };
    const uint32_t w = read_u32_be(data + PNG_SIGNATURE_IHDR_OFFSET);
    const uint32_t h = read_u32_be(data + PNG_SIGNATURE_IHDR_OFFSET_WIDTH);
    if (w == 0 || h == 0 || w > INT32_MAX || h > INT32_MAX) {
      return ret;
    }
    ret.width = static_cast<int32_t>(w);
    ret.height = static_cast<int32_t>(h);
    ret.valid = true;
    return ret;
  }
}  // namespace details

created_result_t<generic_sprite_sheet_t> anim_sprite_sheet_from_embedded_images(get_sprite_callback_t get_sprite,
                                                                                size_t embedded_images_count) {
  generic_sprite_sheet_t ret;

  // 1. frame size from the PNG headers only (no decoding), so the sprite sheet can be allocated first
  int total_frames = 0;
  int max_frame_width = 0;
  int max_frame_height = 0;
  int max_channels = RGBA_CHANNELS;
  // assume img is always RGBA
  for (size_t i = 0; i < embedded_images_count; i++) {
    const assets::embedded_image_t img = get_sprite(i);
    const details::png_size_t png_size = details::read_png_size(img.data, img.size);
    if (!png_size.valid) [[unlikely]] {
      BONGOCAT_LOG_ERROR("Failed to read embedded image header: %s", img.name);
      continue;
    }
    max_frame_width = png_size.width > max_frame_width ? png_size.width : max_frame_width;
    max_frame_height = png_size.height > max_frame_height ? png_size.height : max_frame_height;
    total_frames++;
  }
  if (max_frame_width <= 0 || max_frame_height <= 0) [[unlikely]] {
    return bongocat_error_t::BONGOCAT_ERROR_IMAGE;
  }

  // 2. allocate the final sprite sheet once (one slot per embedded image)
  const auto slots = static_cast<int32_t>(embedded_images_count);
  ret.frame_width = max_frame_width;
  ret.frame_height = max_frame_height;
  ret.total_frames = total_frames;
  ret.image.sprite_sheet_width = max_frame_width * slots;
  ret.image.sprite_sheet_height = max_frame_height;
  ret.image.channels = max_channels;
  const size_t sheet_size_bytes = static_cast<size_t>(ret.image.sprite_sheet_width) *
                                  static_cast<size_t>(ret.image.sprite_sheet_height) * static_cast<size_t>(ret.image.channels);
  ret.image.pixels = make_allocated_array_uninitialized<uint8_t>(sheet_size_bytes);
  if (!ret.image.pixels) [[unlikely]] {
    ret.frame_width = 0;
    ret.frame_height = 0;
    ret.total_frames = 0;
    ret.image.sprite_sheet_width = 0;
    ret.image.sprite_sheet_height = 0;
    ret.image.channels = 0;
    return bongocat_error_t::BONGOCAT_ERROR_MEMORY;
  }
  // keep the rest transparent
  ::memset(ret.image.pixels.data, 0, sheet_size_bytes);
  for (size_t i = 0; i < MAX_NUM_FRAMES; i++) {
    ret.frames[i] = {};
  }

  assert(ret.image.channels >= 0);
  // 3. decode one image at a time
  const size_t dest_stride = static_cast<size_t>(ret.image.sprite_sheet_width) * static_cast<size_t>(ret.image.channels);
  for (size_t frame = 0; frame < embedded_images_count; frame++) {
    const assets::embedded_image_t img = get_sprite(frame);
    BONGOCAT_LOG_DEBUG("Loading embedded image: %s", img.name);
    bool loaded = false;
    {
      auto [src, image_error] = load_image(img.data, img.size, RGBA_CHANNELS);
      if (image_error != bongocat_error_t::BONGOCAT_SUCCESS) [[unlikely]] {
        BONGOCAT_LOG_ERROR("Failed to load embedded image: %s (%d)", img.name, image_error);
      } else if (src.pixels != BONGOCAT_NULLPTR && src.width > 0 && src.height > 0 && src.width <= max_frame_width &&
                 src.height <= max_frame_height) {
        const size_t src_stride = static_cast<size_t>(src.width) * RGBA_CHANNELS;
        uint8_t *dest_slot = ret.image.pixels.data + (frame * static_cast<size_t>(max_frame_width) * RGBA_CHANNELS);
        for (size_t y = 0; y < static_cast<size_t>(src.height); y++) {
          ::memcpy(dest_slot + (y * dest_stride), src.pixels.data + (y * src_stride), src_stride);
        }
        BONGOCAT_LOG_DEBUG("Loaded %dx%d embedded image", src.width, src.height);
        loaded = true;
      }
    }
    if (frame < MAX_NUM_FRAMES) {
      ret.frames[frame] = {.valid = loaded, .col = static_cast<int>(frame), .row = 0};
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

BONGOCAT_NODISCARD created_result_t<Image> make_image(int width, int height, int desired_channels) {
  BONGOCAT_CHECK_ERROR(width < 0, bongocat_error_t::BONGOCAT_ERROR_IMAGE, "image width can not be negative");
  BONGOCAT_CHECK_ERROR(height < 0, bongocat_error_t::BONGOCAT_ERROR_IMAGE, "image height can not be negative");
  BONGOCAT_CHECK_ERROR(desired_channels < 0, bongocat_error_t::BONGOCAT_ERROR_IMAGE, "image channels can not be negative");

  Image ret;
  if (width == 0 || height == 0 || desired_channels == 0) {
    return ret;
  }

  assert(width > 0);
  assert(height > 0);
  assert(desired_channels > 0);
  const size_t data_size = static_cast<size_t>(width) *
                     static_cast<size_t>(height) *
                     static_cast<size_t>(desired_channels);
  assert(data_size > 0);

  ret.width = width;
  ret.height = height;
  ret.channels = desired_channels;
  ret.pixels = platform::make_allocated_mmap_array<unsigned char, MAP_PRIVATE>(data_size);

  return ret;
}
}  // namespace bongocat::animation