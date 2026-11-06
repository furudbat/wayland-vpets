#ifndef BONGOCAT_EMBEDDED_ASSETS_BONGOCAT_IMAGES_H
#define BONGOCAT_EMBEDDED_ASSETS_BONGOCAT_IMAGES_H

#include "embedded_assets/assets.h"
#include <cstddef>

// bongocat
#define ASSETS_BONGOCAT_IMAGES_SECTION BONGOCAT_ASSETS_SET_SECTION(bongocat, "images")
#define ASSETS_BONGOCAT_IMAGE_SIZES_SECTION BONGOCAT_ASSETS_SET_SECTION(bongocat, "image_sizes")

/// @NOTE: sizes are the asset file sizes in bytes; bongocat_images.cpp static_asserts them against the #embed data

// Embedded asset data
extern const unsigned char bongo_cat_both_up_png[6873];
inline constexpr size_t bongo_cat_both_up_png_size ASSETS_BONGOCAT_IMAGE_SIZES_SECTION = 6873;

extern const unsigned char bongo_cat_left_down_png[7387];
inline constexpr size_t bongo_cat_left_down_png_size ASSETS_BONGOCAT_IMAGE_SIZES_SECTION = 7387;

extern const unsigned char bongo_cat_right_down_png[7023];
inline constexpr size_t bongo_cat_right_down_png_size ASSETS_BONGOCAT_IMAGE_SIZES_SECTION = 7023;

extern const unsigned char bongo_cat_both_down_png[18400];
inline constexpr size_t bongo_cat_both_down_png_size ASSETS_BONGOCAT_IMAGE_SIZES_SECTION = 18400;

extern const unsigned char bongo_cat_sleeping_png[18602];
inline constexpr size_t bongo_cat_sleeping_png_size ASSETS_BONGOCAT_IMAGE_SIZES_SECTION = 18602;


// Embedded asset data (new svg files)
extern const unsigned char bongo_cat_both_up_svg[9029];
inline constexpr size_t bongo_cat_both_up_svg_size ASSETS_BONGOCAT_IMAGE_SIZES_SECTION = 9029;

extern const unsigned char bongo_cat_left_down_svg[6397];
inline constexpr size_t bongo_cat_left_down_svg_size ASSETS_BONGOCAT_IMAGE_SIZES_SECTION = 6397;

extern const unsigned char bongo_cat_right_down_svg[6767];
inline constexpr size_t bongo_cat_right_down_svg_size ASSETS_BONGOCAT_IMAGE_SIZES_SECTION = 6767;

extern const unsigned char bongo_cat_both_down_svg[9834];
inline constexpr size_t bongo_cat_both_down_svg_size ASSETS_BONGOCAT_IMAGE_SIZES_SECTION = 9834;

extern const unsigned char bongo_cat_sleeping_svg[5860];
inline constexpr size_t bongo_cat_sleeping_svg_size ASSETS_BONGOCAT_IMAGE_SIZES_SECTION = 5860;
#endif
