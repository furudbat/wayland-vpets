#pragma GCC diagnostic ignored "-Wc++26-extensions"  // #embed is C++26, GCC/Clang extension before that
#include "embedded_assets/assets.h"
#include "embedded_assets/bongocat/bongocat_images.h"
#include <cstddef>

// Embedded asset data
const unsigned char bongo_cat_both_up_png[] ASSETS_IMAGES_SECTION = {
#embed "../../../assets/bongo-cat-both-up.png"
};
static_assert(sizeof(bongo_cat_both_up_png) == bongo_cat_both_up_png_size, "assets/bongo-cat-both-up.png changed, update bongocat_images.h");

const unsigned char bongo_cat_left_down_png[] ASSETS_IMAGES_SECTION = {
#embed "../../../assets/bongo-cat-left-down.png"
};
static_assert(sizeof(bongo_cat_left_down_png) == bongo_cat_left_down_png_size, "assets/bongo-cat-left-down.png changed, update bongocat_images.h");

const unsigned char bongo_cat_right_down_png[] ASSETS_IMAGES_SECTION = {
#embed "../../../assets/bongo-cat-right-down.png"
};
static_assert(sizeof(bongo_cat_right_down_png) == bongo_cat_right_down_png_size, "assets/bongo-cat-right-down.png changed, update bongocat_images.h");

const unsigned char bongo_cat_both_down_png[] ASSETS_IMAGES_SECTION = {
#embed "../../../assets/bongo-cat-both-down.png"
};
static_assert(sizeof(bongo_cat_both_down_png) == bongo_cat_both_down_png_size, "assets/bongo-cat-both-down.png changed, update bongocat_images.h");

const unsigned char bongo_cat_sleeping_png[] ASSETS_IMAGES_SECTION = {
#embed "../../../assets/bongo-cat-sleeping.png"
};
static_assert(sizeof(bongo_cat_sleeping_png) == bongo_cat_sleeping_png_size, "assets/bongo-cat-sleeping.png changed, update bongocat_images.h");


// Embedded asset data (svg)
const unsigned char bongo_cat_both_up_svg[] ASSETS_IMAGES_SECTION = {
#embed "../../../assets/new/bongo-both-up.svg"
};
static_assert(sizeof(bongo_cat_both_up_svg) == bongo_cat_both_up_svg_size, "assets/new/bongo-both-up.svg changed, update bongocat_images.h");

const unsigned char bongo_cat_left_down_svg[] ASSETS_IMAGES_SECTION = {
#embed "../../../assets/new/bongo-left-down.svg"
};
static_assert(sizeof(bongo_cat_left_down_svg) == bongo_cat_left_down_svg_size, "assets/new/bongo-left-down.svg changed, update bongocat_images.h");

const unsigned char bongo_cat_right_down_svg[] ASSETS_IMAGES_SECTION = {
#embed "../../../assets/new/bongo-right-down.svg"
};
static_assert(sizeof(bongo_cat_right_down_svg) == bongo_cat_right_down_svg_size, "assets/new/bongo-right-down.svg changed, update bongocat_images.h");

const unsigned char bongo_cat_both_down_svg[] ASSETS_IMAGES_SECTION = {
#embed "../../../assets/new/bongo-both-down.svg"
};
static_assert(sizeof(bongo_cat_both_down_svg) == bongo_cat_both_down_svg_size, "assets/new/bongo-both-down.svg changed, update bongocat_images.h");

const unsigned char bongo_cat_sleeping_svg[] ASSETS_IMAGES_SECTION = {
#embed "../../../assets/new/bongo-sleeping.svg"
};
static_assert(sizeof(bongo_cat_sleeping_svg) == bongo_cat_sleeping_svg_size, "assets/new/bongo-sleeping.svg changed, update bongocat_images.h");
