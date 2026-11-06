#ifndef BONGOCAT_EMBEDDED_LOAD_IMAGES_H
#define BONGOCAT_EMBEDDED_LOAD_IMAGES_H

#include "config/config.h"
#include "core/bongocat.h"
#include "embedded_assets/embedded_image.h"
#include "graphics/sprite_sheet.h"
#include "utils/memory.h"
#include "utils/system_memory.h"

#include <cstdlib>
#include <cstdint>

// feature flags
namespace features {

#ifdef FEATURE_USE_HYBRID_IMAGE_BACKEND
inline static constexpr bool UseHybridImageBackend = true;
#else
inline static constexpr bool UseHybridImageBackend = false;

#  ifdef FEATURE_USE_PNGLE
inline static constexpr bool UsePngleImageBackend = true;
#  else
inline static constexpr bool UsePngleImageBackend = false;
#  endif

#  ifdef FEATURE_USE_STB_IMAGE
inline static constexpr bool UseStbImageBackend = true;
#  else
inline static constexpr bool UseStbImageBackend = false;
#  endif
#endif

}  // namespace features

namespace bongocat::animation {
// =============================================================================
// IMAGE LOADING MODULE
// =============================================================================

class Image;
BONGOCAT_NODISCARD created_result_t<Image> load_image(const unsigned char *data, size_t size, int desired_channels = RGBA_CHANNELS);
void cleanup_image(Image& image);
void init_image_loader();

class Image {
public:
  platform::MMapArray<uint8_t, MAP_PRIVATE> pixels;
  int width{0};
  int height{0};
  int channels{0};

  Image() = default;
  ~Image() {
    cleanup_image(*this);
  }

  Image(const Image& other) = default;
  Image& operator=(const Image& other) = default;
  Image(Image&& other) noexcept = default;
  Image& operator=(Image&& other) noexcept = default;
};

BONGOCAT_NODISCARD created_result_t<Image> make_image(int width, int height, int desired_channels = RGBA_CHANNELS);

// =============================================================================
// SPRITE SHEET DECODING (decode straight into the final layout)
// =============================================================================

struct sprite_sheet_layout_t {
  int32_t frame_columns{1};
  int32_t frame_rows{1};
  int32_t padding_x{0};
  int32_t padding_y{0};
};
BONGOCAT_NODISCARD created_result_t<generic_sprite_sheet_image_t>
load_sprite_sheet_image(const unsigned char *data, size_t size, sprite_sheet_layout_t layout);

namespace details {
  /// Maps source pixels of the decoded PNG to the padded destination layout.
  struct sprite_sheet_layout_mapper_t {
    int32_t src_width{0};
    int32_t src_height{0};
    int32_t frame_width{0};   ///< source frame size (without padding)
    int32_t frame_height{0};  ///< source frame size (without padding)
    int32_t padding_x{0};
    int32_t padding_y{0};
    int32_t dest_width{0};   ///< padded sprite sheet width (row stride in pixels)
    int32_t dest_height{0};  ///< padded sprite sheet height
    bool valid{false};

    BONGOCAT_NODISCARD constexpr bool has_padding() const noexcept {
      return padding_x != 0 || padding_y != 0;
    }
    BONGOCAT_NODISCARD constexpr size_t dest_size_bytes() const noexcept {
      return static_cast<size_t>(dest_width) * static_cast<size_t>(dest_height) * RGBA_CHANNELS;
    }

    /// destination row of source row y (0 <= y < src_height)
    BONGOCAT_NODISCARD constexpr int32_t dest_y(int32_t y) const noexcept {
      return y + (((y / frame_height) * 2) + 1) * padding_y;
    }
    /// destination column of source column x (0 <= x < src_width)
    BONGOCAT_NODISCARD constexpr int32_t dest_x(int32_t x) const noexcept {
      return x + (((x / frame_width) * 2) + 1) * padding_x;
    }
  };

  /// compute the padded size
  BONGOCAT_NODISCARD sprite_sheet_layout_mapper_t make_sprite_sheet_layout_mapper(int32_t src_width, int32_t src_height,
                                                                                  sprite_sheet_layout_t layout);
  BONGOCAT_NODISCARD created_result_t<generic_sprite_sheet_image_t>
  allocate_sprite_sheet_image(const sprite_sheet_layout_mapper_t& mapper);

  /// copy an already decoded RGBA image into the layout
  void copy_rgba_into_sprite_sheet_layout(generic_sprite_sheet_image_t& dest, const sprite_sheet_layout_mapper_t& mapper,
                                          const uint8_t *src_rgba);
}  // namespace details


using get_sprite_callback_t = assets::embedded_image_t (*)(size_t);

struct animation_thread_context_t;
BONGOCAT_NODISCARD created_result_t<generic_sprite_sheet_t>
anim_sprite_sheet_from_embedded_images(get_sprite_callback_t get_sprite, size_t embedded_images_count);

BONGOCAT_NODISCARD created_result_t<generic_sprite_sheet_t>
load_sprite_sheet_anim(const config::config_t& config, const assets::embedded_image_t& sprite_sheet_image,
                       int sprite_sheet_cols, int sprite_sheet_rows);

}  // namespace bongocat::animation

#endif