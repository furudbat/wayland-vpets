#ifndef BONGOCAT_EMBEDDED_ASSETS_CLIPPY_IMAGES_H
#define BONGOCAT_EMBEDDED_ASSETS_CLIPPY_IMAGES_H

#include <cstddef>

/// @NOTE: sizes are the asset file sizes in bytes; ms_agent_images.cpp static_asserts them against the #embed data

// Embedded asset data
extern const unsigned char clippy_png[619564L];
inline constexpr size_t clippy_png_size = 619564L;

#ifdef FEATURE_MORE_MS_AGENT_EMBEDDED_ASSETS
extern const unsigned char links_png[308660L];
inline constexpr size_t links_png_size = 308660L;

extern const unsigned char rover_png[623692L];
inline constexpr size_t rover_png_size = 623692L;

extern const unsigned char merlin_png[446947L];
inline constexpr size_t merlin_png_size = 446947L;
#endif

#endif  // BONGOCAT_EMBEDDED_ASSETS_CLIPPY_IMAGES_H
