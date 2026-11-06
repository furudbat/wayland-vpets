#pragma GCC diagnostic ignored "-Wc++26-extensions"  // #embed is C++26, GCC/Clang extension before that
#include "embedded_assets/assets.h"
#include "embedded_assets/misc/misc_images.h"
#include <cstddef>

// neko
const unsigned char misc_neko_png[] ASSETS_MISC_IMAGES_SECTION = {
#embed "../../../assets/misc/neko.png"
};
static_assert(sizeof(misc_neko_png) == misc_neko_png_size, "assets/misc/neko.png changed, update misc_images.h");
