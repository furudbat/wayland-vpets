#include "graphics/embedded_assets/clippy_images.h"
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
#endif
