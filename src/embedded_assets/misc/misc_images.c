#include "embedded_assets/assets.h"
#include "embedded_assets/misc/misc_images.h"
#include <stddef.h>

// neko
const unsigned char misc_neko_png[] ASSETS_IMAGES_SECTION = {
#embed "../../../assets/misc/neko.png"
};
const size_t misc_neko_png_size ASSETS_SIZES_SECTION = sizeof(misc_neko_png);
