#include "image_loader/load_images.h"
#include <cassert>
#include <cstdlib>
#include <cstring>
#include <cstdint>
#include <climits>

// include pngle
#if defined(__GNUC__) || defined(__clang__)
#  pragma GCC diagnostic push
#  pragma GCC diagnostic ignored "-Wdouble-promotion"
#  pragma GCC diagnostic ignored "-Wsign-compare"
#  pragma GCC diagnostic ignored "-Wunused-function"
#  pragma GCC diagnostic ignored "-Wold-style-cast"
#  pragma GCC diagnostic ignored "-Wsign-conversion"
#  pragma GCC diagnostic ignored "-Wcast-align"
#  pragma GCC diagnostic ignored "-Wconversion"
#  if defined(__GNUC__) && !defined(__clang__)
#    pragma GCC diagnostic ignored "-Wduplicated-branches"
#    pragma GCC diagnostic ignored "-Wuseless-cast"
// #pragma GCC diagnostic ignored "-Wimplicit-int-conversion"
#  endif
#endif
#include "pngle.h"
#if defined(__GNUC__) || defined(__clang__)
#  pragma GCC diagnostic pop
#endif

// include stb_image
#if defined(__GNUC__) || defined(__clang__)
#  pragma GCC diagnostic push
#  pragma GCC diagnostic ignored "-Wdouble-promotion"
#  pragma GCC diagnostic ignored "-Wsign-compare"
#  pragma GCC diagnostic ignored "-Wunused-function"
#  pragma GCC diagnostic ignored "-Wold-style-cast"
#  pragma GCC diagnostic ignored "-Wsign-conversion"
#  pragma GCC diagnostic ignored "-Wcast-align"
#  pragma GCC diagnostic ignored "-Wconversion"
#  if defined(__GNUC__) && !defined(__clang__)
#    pragma GCC diagnostic ignored "-Wduplicated-branches"
#    pragma GCC diagnostic ignored "-Wuseless-cast"
// #pragma GCC diagnostic ignored "-Wimplicit-int-conversion"
#  endif
#endif
#include "stb_image.h"
#if defined(__GNUC__) || defined(__clang__)
#  pragma GCC diagnostic pop
#endif

namespace bongocat::animation {
//inline static constexpr size_t HybridImageBackendPngleThresholdBytes = 192zu * 1024zu;  // 192kb
//inline static constexpr size_t HybridImageBackendPngleThresholdBytes = 1812zu;
//inline static constexpr size_t HybridImageBackendPngleThresholdBytes = 1859zu;
//inline static constexpr size_t HybridImageBackendPngleThresholdBytes = 145zu;
inline static constexpr size_t HybridImageBackendPngleThresholdBytes = 393zu;  // after profiling and testing

struct decode_state_t {
  Image *image{BONGOCAT_NULLPTR};
  int desired_channels{RGBA_CHANNELS};
  size_t buf_size{0};
};
BONGOCAT_NODISCARD static created_result_t<Image> load_image_pngle(const unsigned char *data, size_t size,
                                                                   int desired_channels) {
  Image ret;
  pngle_t *pngle = pngle_new();
  if (pngle == BONGOCAT_NULLPTR) {
    return bongocat_error_t::BONGOCAT_ERROR_IMAGE;
  }

  decode_state_t state{.image = &ret, .desired_channels = desired_channels};

  // Init callback: called once when PNG header is parsed, before any pixels
  pngle_set_init_callback(pngle, [](pngle_t *p_pngle, uint32_t w, uint32_t h) {
    auto *st = static_cast<decode_state_t *>(pngle_get_user_data(p_pngle));
    assert(w <= INT32_MAX);
    assert(h <= INT32_MAX);
    Image *img = st->image;
    constexpr uint32_t channels = 4;
    img->width = static_cast<int>(w);
    img->height = static_cast<int>(h);
    img->channels = channels;
    st->buf_size = static_cast<size_t>(w) * static_cast<size_t>(h) * channels;

    img->pixels = platform::make_allocated_mmap_array_uninitialized<unsigned char, MAP_PRIVATE>(st->buf_size);
  });

  // Pixel callback: pngle calls this for each RGBA pixel
  pngle_set_draw_callback(pngle, [](pngle_t *p_pngle, uint32_t x, uint32_t y, [[maybe_unused]] uint32_t w, [[maybe_unused]] uint32_t h, const uint8_t rgba[4]) {
    auto *st = static_cast<decode_state_t *>(pngle_get_user_data(p_pngle));
    Image *img = st->image;

    constexpr uint32_t channels = 4;
    unsigned char *dst = &img->pixels[(y * pngle_get_width(p_pngle) + x) * channels];
    dst[0] = rgba[0];
    dst[1] = rgba[1];
    dst[2] = rgba[2];
    dst[3] = rgba[3];
  });

  pngle_set_user_data(pngle, &state);

  // Feed the PNG data
  const int feed = pngle_feed(pngle, data, size);
  if (feed < 0) {
    pngle_destroy(pngle);
    pngle = BONGOCAT_NULLPTR;
    if (ret.pixels != BONGOCAT_NULLPTR) {
      platform::release_allocated_mmap_array(ret.pixels);
      ret.pixels = BONGOCAT_NULLPTR;
    }
    return bongocat_error_t::BONGOCAT_ERROR_IMAGE;
  }
  pngle_destroy(pngle);
  pngle = BONGOCAT_NULLPTR;

  if (ret.pixels == BONGOCAT_NULLPTR) {
    return bongocat_error_t::BONGOCAT_ERROR_IMAGE;
  }

  // Handle desired_channels (pngle gives RGBA only)
  if (desired_channels > 0 && desired_channels != 4) {
    // Optionally strip alpha or replicate grayscale here
    // For now, just return RGBA
    ret.channels = 4;
  }

  assert(ret.width > 0);
  assert(ret.height > 0);
  return ret;
}

BONGOCAT_NODISCARD static created_result_t<Image> load_image_stb_image(const unsigned char *data, size_t size,
int desired_channels) {
  Image ret;
  assert(size <= INT_MAX);
  int channels_in_file;
  unsigned char* stbi_pixels = stbi_load_from_memory(data, static_cast<int>(size), &ret.width, &ret.height, &channels_in_file, desired_channels);
  assert(ret.width >= 0);
  assert(ret.height >= 0);
  assert(desired_channels >= 0);
  const size_t data_size = static_cast<size_t>(ret.width) * static_cast<size_t>(ret.height) * static_cast<size_t>(desired_channels);
  ret.pixels = platform::make_allocated_mmap_array_uninitialized<unsigned char, MAP_PRIVATE>(data_size);
  memcpy(ret.pixels.data, stbi_pixels, data_size);
  stbi_image_free(stbi_pixels);
  if (ret.pixels == BONGOCAT_NULLPTR) [[unlikely]] {
    ret.pixels = BONGOCAT_NULLPTR;
    return bongocat_error_t::BONGOCAT_ERROR_IMAGE;
  }
  assert(ret.width > 0);
  assert(ret.height > 0);
  assert(channels_in_file > 0);
  ret.channels = desired_channels;
  return ret;
}

created_result_t<Image> load_image(const unsigned char *data, size_t size, int desired_channels) {
  // Estimate decompressed size (typical PNG ratio: 10-30%)
  [[maybe_unused]] const size_t est_decompressed = size * 3;

  const bool use_streaming = size >= HybridImageBackendPngleThresholdBytes;
  if (use_streaming) {
    BONGOCAT_LOG_VERBOSE("Using pngle streaming for %.1f KB image (estimated %.1f MB decompressed)",
                        static_cast<double>(size) / 1024.0, static_cast<double>(est_decompressed) / 1024.0 / 1024.0);
    return load_image_pngle(data, size, desired_channels);
  }

  BONGOCAT_LOG_VERBOSE("Using stb_image for %.1f KB image (estimated %.1f MB decompressed)",
                      static_cast<double>(size) / 1024.0, static_cast<double>(est_decompressed) / 1024.0 / 1024.0);
  return load_image_stb_image(data, size, desired_channels);
}

void cleanup_image(Image& image) {
  if (image.pixels != BONGOCAT_NULLPTR) {
    platform::release_allocated_mmap_array(image.pixels);
    image.pixels = BONGOCAT_NULLPTR;
  }
}

void init_image_loader() {
  BONGOCAT_LOG_VERBOSE("Hybrid image loader initialized");
  BONGOCAT_LOG_VERBOSE("  stb_image: images < %.0f KB (%zu Bytes)", HybridImageBackendPngleThresholdBytes / 1024.0, HybridImageBackendPngleThresholdBytes);
  BONGOCAT_LOG_VERBOSE("  pngle: images >= %.0f KB (%zu Bytes)", HybridImageBackendPngleThresholdBytes / 1024.0, HybridImageBackendPngleThresholdBytes);
}
}  // namespace bongocat::animation