#include "embedded_assets/ms_agent/ms_agent_images.h"
#include <stddef.h>

// Embedded asset data
const unsigned char clippy_png[] = {
#embed "../../../assets/clippy.png"
};
const size_t clippy_png_size = sizeof(clippy_png);


#ifdef FEATURE_MORE_MS_AGENT_EMBEDDED_ASSETS
const unsigned char links_png[] = {
#embed "../../../assets/links.png"
};
const size_t links_png_size = sizeof(links_png);

const unsigned char rover_png[] = {
#embed "../../../assets/rover.png"
};
const size_t rover_png_size = sizeof(rover_png);
#endif
