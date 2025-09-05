#ifndef BONGOCAT_EMBEDDED_LOAD_iMAGES_H
#define BONGOCAT_EMBEDDED_LOAD_iMAGES_H

#include "utils/memory.h"
#include "stb_image.hpp"
#include "embedded_assets/embedded_image.h"

namespace bongocat::animation {
    // =============================================================================
    // IMAGE LOADING MODULE
    // =============================================================================

    struct Image {
        stbi_uc *pixels{nullptr};
        int width{0};
        int height{0};
        int channels{0};
        int _channels_in_file{0};

        Image() = default;
        explicit Image(stbi_uc const *data, int size, int desired_channels = STBI_rgb_alpha) {
            pixels = stbi_load_from_memory(data, size, &width, &height, &_channels_in_file, desired_channels);
            channels = desired_channels;
        }
        ~Image() {
            if (pixels) stbi_image_free(pixels);
            pixels = nullptr;
        }

        Image(const Image& other)
            : width(other.width), height(other.height), channels(other.channels), _channels_in_file(other._channels_in_file)
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

            if (pixels) stbi_image_free(pixels);
            pixels = nullptr;

            width = other.width;
            height = other.height;
            channels = other.channels;
            _channels_in_file = other._channels_in_file;

            assert(width >= 0);
            assert(height >= 0);
            assert(channels >= 0);
            const size_t data_size = static_cast<size_t>(width) * static_cast<size_t>(height) * static_cast<size_t>(channels);
            pixels = static_cast<unsigned char*>(::malloc(data_size));
            ::memcpy(pixels, other.pixels, data_size);

            return *this;
        }

        Image(Image&& other) noexcept
            : pixels(other.pixels), width(other.width), height(other.height), channels(other.channels), _channels_in_file(other._channels_in_file)
        {
            other.pixels = nullptr;
            other.width = 0;
            other.height = 0;
            other.channels = 0;
            other._channels_in_file = 0;
        }
        Image& operator=(Image&& other) noexcept {
            if (this == &other) return *this;

            if (pixels) stbi_image_free(pixels);
            pixels = nullptr;

            pixels = other.pixels;
            width = other.width;
            height = other.height;
            channels = other.channels;
            _channels_in_file = other._channels_in_file;

            other.pixels = nullptr;
            other.width = 0;
            other.height = 0;
            other.channels = 0;
            other._channels_in_file = 0;

            return *this;
        }
    };

    using get_sprite_callback_t = assets::embedded_image_t (*)(size_t);

    struct animation_context_t;
    [[nodiscard]] created_result_t<generic_sprite_sheet_animation_t> anim_sprite_sheet_from_embedded_images(get_sprite_callback_t get_sprite, size_t embedded_images_count);
    [[nodiscard]] created_result_t<generic_sprite_sheet_animation_t> load_sprite_sheet_anim(const config::config_t& config, const assets::embedded_image_t& sprite_sheet_image, int sprite_sheet_cols, int sprite_sheet_rows);
}

#endif