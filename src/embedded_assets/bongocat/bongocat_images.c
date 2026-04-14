#include "embedded_assets/bongocat/bongocat_images.h"

#include <stddef.h>

// Embedded asset data
const unsigned char bongo_cat_both_up_png[] = {
#embed "../../../assets/bongo-cat-both-up.png"
};
const size_t bongo_cat_both_up_png_size = sizeof(bongo_cat_both_up_png);

const unsigned char bongo_cat_left_down_png[] = {
#embed "../../../assets/bongo-cat-left-down.png"
};
const size_t bongo_cat_left_down_png_size = sizeof(bongo_cat_left_down_png);

const unsigned char bongo_cat_right_down_png[] = {
#embed "../../../assets/bongo-cat-right-down.png"
};
const size_t bongo_cat_right_down_png_size = sizeof(bongo_cat_right_down_png);

const unsigned char bongo_cat_both_down_png[] = {
#embed "../../../assets/bongo-cat-both-down.png"
};
const size_t bongo_cat_both_down_png_size = sizeof(bongo_cat_both_down_png);


#ifdef FEATURE_USE_BONGOCAT_SVG
// Embedded asset data (svg)
const unsigned char bongo_cat_both_up_svg[] = {
#embed "../../../assets/new/bongo-both-up.svg"
};
const size_t bongo_cat_both_up_svg_size = sizeof(bongo_cat_both_up_svg);

const unsigned char bongo_cat_left_down_svg[] = {
#embed "../../../assets/new/bongo-left-down.svg"
};
const size_t bongo_cat_left_down_svg_size = sizeof(bongo_cat_left_down_svg);

const unsigned char bongo_cat_right_down_svg[] = {
#embed "../../../assets/new/bongo-right-down.svg"
};
const size_t bongo_cat_right_down_svg_size = sizeof(bongo_cat_right_down_svg);

const unsigned char bongo_cat_both_down_svg[] = {
#embed "../../../assets/new/bongo-both-down.svg"
};
const size_t bongo_cat_both_down_svg_size = sizeof(bongo_cat_both_down_svg);

const unsigned char bongo_cat_sleeping_svg[] = {
#embed "../../../assets/new/bongo-sleeping.svg"
};
const size_t bongo_cat_sleeping_svg_size = sizeof(bongo_cat_sleeping_svg);
#endif