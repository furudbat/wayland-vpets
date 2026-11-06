#ifndef BONGOCAT_EMBEDDED_ASSETS_CLIPPY_IMAGES_H
#define BONGOCAT_EMBEDDED_ASSETS_CLIPPY_IMAGES_H

#include "embedded_assets/assets.h"
#include <cstddef>

// ms_agent
#define ASSETS_MS_AGENT_IMAGES_SECTION BONGOCAT_ASSETS_SET_SECTION(ms_agent, "images")
#define ASSETS_MS_AGENT_IMAGE_SIZES_SECTION BONGOCAT_ASSETS_SET_SECTION(ms_agent, "image_sizes")

/// @NOTE: sizes are the asset file sizes in bytes; ms_agent_images.cpp static_asserts them against the #embed data

// Embedded asset data
extern const unsigned char clippy_png[619564L];
inline constexpr size_t clippy_png_size ASSETS_MS_AGENT_IMAGE_SIZES_SECTION = 619564L;

#ifdef FEATURE_MORE_MS_AGENT_EMBEDDED_ASSETS
extern const unsigned char links_png[308660L];
inline constexpr size_t links_png_size ASSETS_MS_AGENT_IMAGE_SIZES_SECTION = 308660L;

extern const unsigned char rover_png[623692L];
inline constexpr size_t rover_png_size ASSETS_MS_AGENT_IMAGE_SIZES_SECTION = 623692L;

extern const unsigned char merlin_png[446947L];
inline constexpr size_t merlin_png_size ASSETS_MS_AGENT_IMAGE_SIZES_SECTION = 446947L;
#endif

#endif  // BONGOCAT_EMBEDDED_ASSETS_CLIPPY_IMAGES_H
