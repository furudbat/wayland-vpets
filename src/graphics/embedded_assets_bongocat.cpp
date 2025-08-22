#include "graphics/embedded_assets_bongocat.h"
#include "graphics/sprite_sheet.h"
#include "graphics/embedded_assets/bongocat.hpp"
#include "graphics/embedded_assets/bongocat_images.hpp"

namespace bongocat::assets {
    embedded_image_t get_bongocat_sprite(size_t i) {
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