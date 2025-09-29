#include "image_loader/load_images.h"
#include <cassert>
#include <cstdlib>
#include <cstring>

// include pngle
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
#include "pngle.h"
#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic pop
#endif

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
    inline static constexpr size_t HybridImageBackendPngleThresholdBytes = 192 * 1024; // 192kb

    struct decode_state_t {
        Image *image{nullptr};
        int desired_channels{RGBA_CHANNELS};
    };
    static created_result_t<Image> load_image_pngle(const unsigned char *data, size_t size, int desired_channels) {
        Image ret;
        pngle_t *pngle = pngle_new();
        if (!pngle) {
            return bongocat_error_t::BONGOCAT_ERROR_IMAGE;
        }

        decode_state_t state { .image = &ret, .desired_channels = desired_channels };

        // Pixel callback: pngle calls this for each RGBA pixel
        pngle_set_draw_callback(pngle,
            [](pngle_t *p_pngle, uint32_t x, uint32_t y, [[maybe_unused]] uint32_t w, [[maybe_unused]] uint32_t h, const uint8_t rgba[4]) {
                auto *st = static_cast<decode_state_t*>(pngle_get_user_data(p_pngle));
                Image *img = st->image;

                constexpr uint32_t channels = 4;
                if (!img->pixels) {
                    // Allocate buffer on first pixel
                    img->width  = static_cast<int>(pngle_get_width(p_pngle));
                    img->height = static_cast<int>(pngle_get_height(p_pngle));
                    img->channels = channels; // pngle always gives RGBA
                    size_t buf_size = pngle_get_width(p_pngle) * pngle_get_height(p_pngle) * channels;
                    img->pixels = static_cast<unsigned char*>(::malloc(buf_size));
                    if (!img->pixels) return;
                }

                unsigned char *dst = &img->pixels[(y * pngle_get_width(p_pngle) + x) * channels];
                dst[0] = rgba[0];
                dst[1] = rgba[1];
                dst[2] = rgba[2];
                dst[3] = rgba[3];
            });

        pngle_set_user_data(pngle, &state);

        // Feed the PNG data
        const int fed = pngle_feed(pngle, data, size);
        if (fed < 0) {
            pngle_destroy(pngle);
            if (ret.pixels) ::free(ret.pixels);
            ret.pixels = nullptr;
            return bongocat_error_t::BONGOCAT_ERROR_IMAGE;
        }

        pngle_destroy(pngle);

        if (!ret.pixels) {
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

    static created_result_t<Image> load_image_stb_image(const unsigned char *data, size_t size, int desired_channels) {
        Image ret;
        assert(size <= INT_MAX);
        int channels_in_file;
        ret.pixels = stbi_load_from_memory(data, static_cast<int>(size), &ret.width, &ret.height, &channels_in_file, desired_channels);
        if (ret.pixels == nullptr) {
            ret.pixels = nullptr;
            return bongocat_error_t::BONGOCAT_ERROR_IMAGE;
        }
        assert(ret.width > 0);
        assert(ret.height > 0);
        assert(channels_in_file > 0);
        ret.channels = desired_channels;
        return ret;
    }

    created_result_t<Image> load_image(const unsigned char *data, size_t size, int desired_channels) {
        if (size >= HybridImageBackendPngleThresholdBytes) {
            return load_image_pngle(data, size, desired_channels);
        }

        return load_image_stb_image(data, size, desired_channels);
    }

    void cleanup_image(Image& image) {
        if (image.pixels) ::free(image.pixels);
        image.pixels = nullptr;
    }

    void init_image_loader() {

    }
}