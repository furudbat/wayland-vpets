#ifndef BONGOCAT_EMBEDDED_ASSETS_BONGOCAT_IMAGES_H
#define BONGOCAT_EMBEDDED_ASSETS_BONGOCAT_IMAGES_H

#include <stddef.h>

// Embedded asset data
extern const unsigned char bongo_cat_both_up_png[];
extern const size_t bongo_cat_both_up_png_size;

extern const unsigned char bongo_cat_left_down_png[];
extern const size_t bongo_cat_left_down_png_size;

extern const unsigned char bongo_cat_right_down_png[];
extern const size_t bongo_cat_right_down_png_size;

extern const unsigned char bongo_cat_both_down_png[];
extern const size_t bongo_cat_both_down_png_size;

#ifdef FEATURE_USE_BONGOCAT_SVG
// Embedded asset data (new svg files)
extern const unsigned char bongo_cat_both_up_svg[];
extern const size_t bongo_cat_both_up_svg_size;

extern const unsigned char bongo_cat_left_down_svg[];
extern const size_t bongo_cat_left_down_svg_size;

extern const unsigned char bongo_cat_right_down_svg[];
extern const size_t bongo_cat_right_down_svg_size;

extern const unsigned char bongo_cat_both_down_svg[];
extern const size_t bongo_cat_both_down_svg_size;

extern const unsigned char bongo_cat_sleeping_svg[];
extern const size_t bongo_cat_sleeping_svg_size;
#endif

#endif  // BONGOCAT_EMBEDDED_ASSETS_BONGOCAT_IMAGES_H
