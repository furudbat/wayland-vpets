#ifndef BONGOCAT_EMBEDDED_LOAD_IMAGES_H
#define BONGOCAT_EMBEDDED_LOAD_IMAGES_H

#include "graphics/sprite_sheet.h"
#include "core/bongocat.h"
#include "config/config.h"
#include "utils/memory.h"
#include "embedded_assets/embedded_image.h"
#include <cstdlib>

namespace bongocat::animation {
    // =============================================================================
    // IMAGE LOADING MODULE
    // =============================================================================

    struct Image;
    created_result_t<Image> load_image(const unsigned char *data, size_t size, int desired_channels = RGBA_CHANNELS);
    void cleanup_image(Image& image);
    void init_image_loader();

    struct Image {
        unsigned char *pixels{nullptr};
        int width{0};
        int height{0};
        int channels{0};

        Image() = default;
        ~Image() {
            cleanup_image(*this);
        }

        Image(const Image& other)
            : width(other.width), height(other.height), channels(other.channels)
        {
            assert(width >= 0);
            assert(height >= 0);
            assert(channels >= 0);
            const size_t data_size = static_cast<size_t>(width) * static_cast<size_t>(height) * static_cast<size_t>(channels);
            pixels = static_cast<unsigned char*>(::malloc(data_size));
            ::memcpy(pixels, other.pixels, data_size);
        }
        Image& operator=(const Image& other) {
            if (this == &other) return *this;

            cleanup_image(*this);

            width = other.width;
            height = other.height;
            channels = other.channels;

            assert(width >= 0);
            assert(height >= 0);
            assert(channels >= 0);
            const size_t data_size = static_cast<size_t>(width) * static_cast<size_t>(height) * static_cast<size_t>(channels);
            pixels = static_cast<unsigned char*>(::malloc(data_size));
            ::memcpy(pixels, other.pixels, data_size);

            return *this;
        }

        Image(Image&& other) noexcept
            : pixels(other.pixels), width(other.width), height(other.height), channels(other.channels)
        {
            other.pixels = nullptr;
            other.width = 0;
            other.height = 0;
            other.channels = 0;
        }
        Image& operator=(Image&& other) noexcept {
            if (this == &other) return *this;

            cleanup_image(*this);

            pixels = other.pixels;
            width = other.width;
            height = other.height;
            channels = other.channels;

            other.pixels = nullptr;
            other.width = 0;
            other.height = 0;
            other.channels = 0;

            return *this;
        }
    };

    using get_sprite_callback_t = assets::embedded_image_t (*)(size_t);

    struct animation_context_t;
    [[nodiscard]] created_result_t<generic_sprite_sheet_t> anim_sprite_sheet_from_embedded_images(get_sprite_callback_t get_sprite, size_t embedded_images_count);
    [[nodiscard]] created_result_t<generic_sprite_sheet_t> load_sprite_sheet_anim(const config::config_t& config, const assets::embedded_image_t& sprite_sheet_image, int sprite_sheet_cols, int sprite_sheet_rows);
}

#endif