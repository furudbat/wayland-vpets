#ifndef MISC_EMBEDDED_ASSETS_IMAGES_H
#define MISC_EMBEDDED_ASSETS_IMAGES_H

#include "embedded_assets/assets.h"
#include <cstddef>

// misc
#define ASSETS_MISC_IMAGES_SECTION BONGOCAT_ASSETS_SET_SECTION(misc, "images")
#define ASSETS_MISC_IMAGE_SIZES_SECTION BONGOCAT_ASSETS_SET_SECTION(misc, "image_sizes")

// neko
extern const unsigned char misc_neko_png[4726];
inline constexpr size_t misc_neko_png_size ASSETS_MISC_IMAGE_SIZES_SECTION = 4726;

#endif  // MISC_EMBEDDED_ASSETS_IMAGES_H
