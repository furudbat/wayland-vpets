#include "embedded_assets/embedded_image.h"
#include "embedded_assets/bongocat/bongocat.h"
#include "embedded_assets/bongocat/bongocat_images.h"

namespace bongocat::assets {
    embedded_image_t get_bongocat_sprite(size_t i) {
        using namespace assets;
        switch (i) {
            case BONGOCAT_FRAME_BOTH_UP: return {bongo_cat_both_up_png, bongo_cat_both_up_png_size, "bongo-cat-both-up"};
            case BONGOCAT_FRAME_LEFT_DOWN: return {bongo_cat_left_down_png, bongo_cat_left_down_png_size, "bongo-cat-left-down"};
            case BONGOCAT_FRAME_RIGHT_DOWN: return {bongo_cat_right_down_png, bongo_cat_right_down_png_size, "bongo-cat-right-down"};
            case BONGOCAT_FRAME_BOTH_DOWN: return {bongo_cat_both_down_png, bongo_cat_both_down_png_size, "bongo-cat-both-down"};
            default: return {};
        }
        return { };
    }
}