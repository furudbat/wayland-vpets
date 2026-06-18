#include "embedded_assets/ms_agent/ms_agent_images.h"

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

// Embedded asset data
const unsigned char clippy_png[] ASSETS_SECTION = {
#embed "../../../assets/ms_agent/clippy.png"
};
const size_t clippy_png_size ASSETS_SECTION = sizeof(clippy_png);

#ifdef FEATURE_MORE_MS_AGENT_EMBEDDED_ASSETS
const unsigned char links_png[] ASSETS_SECTION = {
#  embed "../../../assets/ms_agent/links.png"
};
const size_t links_png_size = sizeof(links_png);

const unsigned char rover_png[] ASSETS_SECTION = {
#  embed "../../../assets/ms_agent/rover.png"
};
const size_t rover_png_size ASSETS_SECTION = sizeof(rover_png);

const unsigned char merlin_png[] ASSETS_SECTION = {
#  embed "../../../assets/ms_agent/merlin.png"
};
const size_t merlin_png_size ASSETS_SECTION = sizeof(merlin_png);
#endif
