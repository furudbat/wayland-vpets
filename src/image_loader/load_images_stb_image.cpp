#include "image_loader/load_images.h"
// include stb_image
#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdouble-promotion"
#pragma GCC diagnostic ignored "-Wsign-compare"
#pragma GCC diagnostic ignored "-Wunused-function"
#pragma GCC diagnostic ignored "-Wold-style-cast"
#pragma GCC diagnostic ignored "-Wsign-conversion"
#pragma GCC diagnostic ignored "-Wcast-align"
#pragma GCC diagnostic ignored "-Wconversion"
#if defined(__GNUC__) && !defined(__clang__)
#pragma GCC diagnostic ignored "-Wduplicated-branches"
#pragma GCC diagnostic ignored "-Wuseless-cast"
//#pragma GCC diagnostic ignored "-Wimplicit-int-conversion"
#endif
#endif
#include "stb_image.h"

#include <sys/mman.h>
#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic pop
#endif

namespace bongocat::animation {
    created_result_t<Image> load_image(const unsigned char *data, size_t size, int desired_channels) {
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

    void cleanup_image(Image& image) {
      if (image.pixels) {
        platform::release_allocated_mmap_array(image.pixels);
      }
      image.pixels = BONGOCAT_NULLPTR;
    }

    void init_image_loader() {
      BONGOCAT_LOG_VERBOSE("stb_image image loader initialized");
    }
}