#ifndef BONGOCAT_EMBEDDED_ASSETS_IMAGE_H
#define BONGOCAT_EMBEDDED_ASSETS_IMAGE_H

#include "sprite_sheet.h"
#include <cstddef>
#include <cstdint>

namespace bongocat::assets {
    struct embedded_image_t {
        const unsigned char *data{nullptr};
        size_t size{0};
        const char *name{""};
    };
}

#endif // BONGOCAT_EMBEDDED_ASSETS_IMAGE_H
