#ifndef BONGOCAT_EMBEDDED_ASSETS_CLIPPY_IMAGES_H
#define BONGOCAT_EMBEDDED_ASSETS_CLIPPY_IMAGES_H

#include <stddef.h>

// Embedded asset data
extern const unsigned char clippy_png[];
extern const size_t clippy_png_size;

#ifdef FEATURE_MORE_MS_AGENT_EMBEDDED_ASSETS
extern const unsigned char links_png[];
extern const size_t links_png_size;

extern const unsigned char rover_png[];
extern const size_t rover_png_size;
#endif

#endif // BONGOCAT_EMBEDDED_ASSETS_CLIPPY_IMAGES_H
