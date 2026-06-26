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


using get_sprite_callback_t = assets::embedded_image_t (*)(size_t);

struct animation_thread_context_t;
BONGOCAT_NODISCARD created_result_t<generic_sprite_sheet_t>
anim_sprite_sheet_from_embedded_images(get_sprite_callback_t get_sprite, size_t embedded_images_count);

BONGOCAT_NODISCARD created_result_t<generic_sprite_sheet_t>
load_sprite_sheet_anim(const config::config_t& config, const assets::embedded_image_t& sprite_sheet_image,
                       int sprite_sheet_cols, int sprite_sheet_rows);

}  // namespace bongocat::animation

#endif