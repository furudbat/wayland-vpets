#ifndef BONGOCAT_EMBEDDED_ASSETS_CLIPPY_IMAGES_HPP
#define BONGOCAT_EMBEDDED_ASSETS_CLIPPY_IMAGES_HPP

#include <cstddef>

namespace bongocat::assets {
    // Embedded asset data
    inline static constexpr unsigned char clippy_png[] = {
#embed "../../../assets/clippy.png"
    };
    inline static constexpr std::size_t clippy_png_size = sizeof(clippy_png);
}

#endif // BONGOCAT_EMBEDDED_ASSETS_CLIPPY_IMAGES_HPP
