#include "embedded_assets/assets.h"
#include "embedded_assets/ms_agent/ms_agent_images.h"
#include <stddef.h>

// Embedded asset data
const unsigned char clippy_png[] ASSETS_IMAGES_SECTION = {
#embed "../../../assets/ms_agent/clippy.png"
};
const size_t clippy_png_size ASSETS_SIZES_SECTION = sizeof(clippy_png);

#ifdef FEATURE_MORE_MS_AGENT_EMBEDDED_ASSETS
const unsigned char links_png[] ASSETS_IMAGES_SECTION = {
#  embed "../../../assets/ms_agent/links.png"
};
const size_t links_png_size = sizeof(links_png);

const unsigned char rover_png[] ASSETS_IMAGES_SECTION = {
#  embed "../../../assets/ms_agent/rover.png"
};
const size_t rover_png_size ASSETS_SIZES_SECTION = sizeof(rover_png);

const unsigned char merlin_png[] ASSETS_IMAGES_SECTION = {
#  embed "../../../assets/ms_agent/merlin.png"
};
const size_t merlin_png_size ASSETS_SIZES_SECTION = sizeof(merlin_png);
#endif
