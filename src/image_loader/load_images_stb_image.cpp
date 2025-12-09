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
#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic pop
#endif

namespace bongocat::animation {
    created_result_t<Image> load_image(const unsigned char *data, size_t size, int desired_channels) {
        Image ret;
        assert(size <= INT_MAX);
        int channels_in_file;
        ret.pixels = stbi_load_from_memory(data, static_cast<int>(size), &ret.width, &ret.height, &channels_in_file, desired_channels);
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
          stbi_image_free(image.pixels);
        }
        image.pixels = BONGOCAT_NULLPTR;
    }

    void init_image_loader() {

    }
}