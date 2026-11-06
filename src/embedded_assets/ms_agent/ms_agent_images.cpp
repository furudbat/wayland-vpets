#pragma GCC diagnostic ignored "-Wc++26-extensions"  // #embed is C++26, GCC/Clang extension before that
#include "embedded_assets/assets.h"
#include "embedded_assets/ms_agent/ms_agent_images.h"
#include <cstddef>

// Embedded asset data
const unsigned char clippy_png[] ASSETS_MS_AGENT_IMAGES_SECTION = {
#embed "../../../assets/ms_agent/clippy.png"
};
static_assert(sizeof(clippy_png) == clippy_png_size, "assets/ms_agent/clippy.png changed, update ms_agent_images.h");

#ifdef FEATURE_MORE_MS_AGENT_EMBEDDED_ASSETS
const unsigned char links_png[] ASSETS_MS_AGENT_IMAGES_SECTION = {
#embed "../../../assets/ms_agent/links.png"
};
static_assert(sizeof(links_png) == links_png_size, "assets/ms_agent/links.png changed, update ms_agent_images.h");

const unsigned char rover_png[] ASSETS_MS_AGENT_IMAGES_SECTION = {
#embed "../../../assets/ms_agent/rover.png"
};
static_assert(sizeof(rover_png) == rover_png_size, "assets/ms_agent/rover.png changed, update ms_agent_images.h");

const unsigned char merlin_png[] ASSETS_MS_AGENT_IMAGES_SECTION = {
#embed "../../../assets/ms_agent/merlin.png"
};
static_assert(sizeof(merlin_png) == merlin_png_size, "assets/ms_agent/merlin.png changed, update ms_agent_images.h");
#endif
