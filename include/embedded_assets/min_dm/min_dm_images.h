#ifndef MIN_DM_EMBEDDED_ASSETS_IMAGES_H
#define MIN_DM_EMBEDDED_ASSETS_IMAGES_H

#include "embedded_assets/assets.h"
#include "embedded_assets/dm/dm_images.h"
#include <cstddef>

// min_dm
#define ASSETS_MIN_DM_IMAGES_SECTION BONGOCAT_ASSETS_SET_SECTION(min_dm, "images")
#define ASSETS_MIN_DM_IMAGE_SIZES_SECTION(name) BONGOCAT_ASSETS_SET_SECTION_FOR(min_dm, "image_sizes", name)

// Botamon
extern const unsigned char min_dm_botamon_png[dm_botamon_png_size];
inline constexpr size_t min_dm_botamon_png_size ASSETS_MIN_DM_IMAGE_SIZES_SECTION(min_dm_botamon_png_size) = dm_botamon_png_size;

// Koromon
extern const unsigned char min_dm_koromon_png[dm_koromon_png_size];
inline constexpr size_t min_dm_koromon_png_size ASSETS_MIN_DM_IMAGE_SIZES_SECTION(min_dm_koromon_png_size) = dm_koromon_png_size;

// Agumon
extern const unsigned char min_dm_agumon_png[dm_agumon_png_size];
inline constexpr size_t min_dm_agumon_png_size ASSETS_MIN_DM_IMAGE_SIZES_SECTION(min_dm_agumon_png_size) = dm_agumon_png_size;

// Betamon
extern const unsigned char min_dm_betamon_png[dm_betamon_png_size];
inline constexpr size_t min_dm_betamon_png_size ASSETS_MIN_DM_IMAGE_SIZES_SECTION(min_dm_betamon_png_size) = dm_betamon_png_size;

// Greymon
extern const unsigned char min_dm_greymon_png[dm_greymon_png_size];
inline constexpr size_t min_dm_greymon_png_size ASSETS_MIN_DM_IMAGE_SIZES_SECTION(min_dm_greymon_png_size) = dm_greymon_png_size;

// Tyranomon
extern const unsigned char min_dm_tyranomon_png[dm_tyranomon_png_size];
inline constexpr size_t min_dm_tyranomon_png_size ASSETS_MIN_DM_IMAGE_SIZES_SECTION(min_dm_tyranomon_png_size) = dm_tyranomon_png_size;

// Devimon
extern const unsigned char min_dm_devimon_png[dm_devimon_png_size];
inline constexpr size_t min_dm_devimon_png_size ASSETS_MIN_DM_IMAGE_SIZES_SECTION(min_dm_devimon_png_size) = dm_devimon_png_size;

// Meramon
extern const unsigned char min_dm_meramon_png[dm_meramon_png_size];
inline constexpr size_t min_dm_meramon_png_size ASSETS_MIN_DM_IMAGE_SIZES_SECTION(min_dm_meramon_png_size) = dm_meramon_png_size;

// Airdramon
extern const unsigned char min_dm_airdramon_png[dm_airdramon_png_size];
inline constexpr size_t min_dm_airdramon_png_size ASSETS_MIN_DM_IMAGE_SIZES_SECTION(min_dm_airdramon_png_size) = dm_airdramon_png_size;

// Seadramon
extern const unsigned char min_dm_seadramon_png[dm_seadramon_png_size];
inline constexpr size_t min_dm_seadramon_png_size ASSETS_MIN_DM_IMAGE_SIZES_SECTION(min_dm_seadramon_png_size) = dm_seadramon_png_size;

// Numemon
extern const unsigned char min_dm_numemon_png[dm_numemon_png_size];
inline constexpr size_t min_dm_numemon_png_size ASSETS_MIN_DM_IMAGE_SIZES_SECTION(min_dm_numemon_png_size) = dm_numemon_png_size;

// Metal Greymon
extern const unsigned char min_dm_metal_greymon_png[dm_metal_greymon_png_size];
inline constexpr size_t min_dm_metal_greymon_png_size ASSETS_MIN_DM_IMAGE_SIZES_SECTION(min_dm_metal_greymon_png_size) = dm_metal_greymon_png_size;

// Mamemon
extern const unsigned char min_dm_mamemon_png[dm_mamemon_png_size];
inline constexpr size_t min_dm_mamemon_png_size ASSETS_MIN_DM_IMAGE_SIZES_SECTION(min_dm_mamemon_png_size) = dm_mamemon_png_size;

// Monzaemon
extern const unsigned char min_dm_monzaemon_png[dm_monzaemon_png_size];
inline constexpr size_t min_dm_monzaemon_png_size ASSETS_MIN_DM_IMAGE_SIZES_SECTION(min_dm_monzaemon_png_size) = dm_monzaemon_png_size;

#endif  // MIN_DM_EMBEDDED_ASSETS_IMAGES_H
