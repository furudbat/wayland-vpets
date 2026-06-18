#include "embedded_assets/misc/misc_images.h"

#include <stddef.h>

#ifndef ASSETS_SECTION
#if defined(__GNUC__) || defined(__clang__)
  #define ASSETS_SECTION __attribute__((section(".assets")))
#elif defined(_MSC_VER)
  #define ASSETS_SECTION __declspec(allocate(".assets"))
  #pragma section(".assets", read)
#else
  #define ASSETS_SECTION
#endif
#endif

// neko
const unsigned char misc_neko_png[] ASSETS_SECTION = {
#embed "../../../assets/misc/neko.png"
};
const size_t misc_neko_png_size ASSETS_SECTION = sizeof(misc_neko_png);
