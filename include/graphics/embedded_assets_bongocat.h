#ifndef BONGOCAT_EMBEDDED_ASSETS_BONGOCAT_H
#define BONGOCAT_EMBEDDED_ASSETS_BONGOCAT_H

#include "animation_constants.h"
#include "sprite_sheet.h"
#include "embedded_assets_image.h"
#include "graphics/embedded_assets/bongocat.hpp"
#include <cstddef>

namespace bongocat::assets {
    inline static constexpr size_t BONGOCAT_EMBEDDED_IMAGES_COUNT = animation::BONGOCAT_NUM_FRAMES;
    /*
    inline constinit embedded_image_t bongocat_embedded_images[BONGOCAT_EMBEDDED_IMAGES_COUNT] = {
        {bongo_cat_both_up_png, bongo_cat_both_up_png_size, "embedded bongo-cat-both-up.png"},
        {bongo_cat_left_down_png, bongo_cat_left_down_png_size, "embedded bongo-cat-left-down.png"},
        {bongo_cat_right_down_png, bongo_cat_right_down_png_size, "embedded bongo-cat-right-down.png"},
        {bongo_cat_both_down_png, bongo_cat_both_down_png_size, "embedded bongo-cat-both-down.png"},
    };
    */
    inline static constexpr size_t BONGOCAT_ANIMATIONS_COUNT = 1;

    constexpr embedded_image_t get_bongocat_sprite(size_t i) {
        using namespace animation;
        switch (i) {
            case BONGOCAT_FRAME_BOTH_UP: return {bongo_cat_both_up_png, bongo_cat_both_up_png_size, "embedded bongo-cat-both-up.png"};
            case BONGOCAT_FRAME_LEFT_DOWN: return {bongo_cat_left_down_png, bongo_cat_left_down_png_size, "embedded bongo-cat-left-down.png"};
            case BONGOCAT_FRAME_RIGHT_DOWN: return {bongo_cat_right_down_png, bongo_cat_right_down_png_size, "embedded bongo-cat-right-down.png"};
            case BONGOCAT_FRAME_BOTH_DOWN: return {bongo_cat_both_down_png, bongo_cat_both_down_png_size, "embedded bongo-cat-both-down.png"};
            default: return { nullptr, 0, "" };
        }
    }
}

#endif // BONGOCAT_EMBEDDED_ASSETS_BONGOCAT_H
