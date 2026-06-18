#include "embedded_assets/bongocat/bongocat_images.h"

#include <stddef.h>

#ifndef ASSETS_SECTION
#if defined(__GNUC__) || defined(__clang__)
  #define ASSETS_SECTION __attribute__((section(".assets")))
#elif defined(_MSC_VER)
  #define ASSETS_SECTION __declspec(allocate(".assets"))
  #pragma section(".assets", read)
#else
  #define ASSETS_SECTION
#endif
#endif

// Embedded asset data
const unsigned char bongo_cat_both_up_png[] ASSETS_SECTION = {
#embed "../../../assets/bongo-cat-both-up.png"
};
const size_t bongo_cat_both_up_png_size ASSETS_SECTION = sizeof(bongo_cat_both_up_png);

const unsigned char bongo_cat_left_down_png[] ASSETS_SECTION = {
#embed "../../../assets/bongo-cat-left-down.png"
};
const size_t bongo_cat_left_down_png_size ASSETS_SECTION = sizeof(bongo_cat_left_down_png);

const unsigned char bongo_cat_right_down_png[] ASSETS_SECTION = {
#embed "../../../assets/bongo-cat-right-down.png"
};
const size_t bongo_cat_right_down_png_size ASSETS_SECTION = sizeof(bongo_cat_right_down_png);

const unsigned char bongo_cat_both_down_png[] ASSETS_SECTION = {
#embed "../../../assets/bongo-cat-both-down.png"
};
const size_t bongo_cat_both_down_png_size ASSETS_SECTION = sizeof(bongo_cat_both_down_png);

const unsigned char bongo_cat_sleeping_png[] ASSETS_SECTION = {
#embed "../../../assets/bongo-cat-sleeping.png"
};
const size_t bongo_cat_sleeping_png_size ASSETS_SECTION = sizeof(bongo_cat_sleeping_png);


// Embedded asset data (svg)
const unsigned char bongo_cat_both_up_svg[] ASSETS_SECTION = {
#embed "../../../assets/new/bongo-both-up.svg"
};
const size_t bongo_cat_both_up_svg_size ASSETS_SECTION = sizeof(bongo_cat_both_up_svg);

const unsigned char bongo_cat_left_down_svg[] ASSETS_SECTION = {
#embed "../../../assets/new/bongo-left-down.svg"
};
const size_t bongo_cat_left_down_svg_size ASSETS_SECTION = sizeof(bongo_cat_left_down_svg);

const unsigned char bongo_cat_right_down_svg[] ASSETS_SECTION = {
#embed "../../../assets/new/bongo-right-down.svg"
};
const size_t bongo_cat_right_down_svg_size ASSETS_SECTION = sizeof(bongo_cat_right_down_svg);

const unsigned char bongo_cat_both_down_svg[] ASSETS_SECTION = {
#embed "../../../assets/new/bongo-both-down.svg"
};
const size_t bongo_cat_both_down_svg_size ASSETS_SECTION = sizeof(bongo_cat_both_down_svg);

const unsigned char bongo_cat_sleeping_svg[] ASSETS_SECTION = {
#embed "../../../assets/new/bongo-sleeping.svg"
};
const size_t bongo_cat_sleeping_svg_size ASSETS_SECTION = sizeof(bongo_cat_sleeping_svg);