#include "graphics/embedded_assets.h"
#include "graphics/embedded_assets/bongocat.hpp"
#include "animation_constants.h"


namespace bongocat::assets::details {
    extern const embedded_image_t* init_bongocat_embedded_images();

    const embedded_image_t* bongocat_embedded_images = init_bongocat_embedded_images();

    const embedded_image_t* init_bongocat_embedded_images() {
        using namespace assets;
        using namespace animation;

        static constexpr embedded_image_t _bongocat_embedded_images[BONGOCAT_EMBEDDED_IMAGES_COUNT] = {
            /*_bongocat_embedded_images[BONGOCAT_FRAME_BOTH_UP] = */{bongo_cat_both_up_png, bongo_cat_both_up_png_size, "embedded bongo-cat-both-up.png"},
            /*_bongocat_embedded_images[BONGOCAT_FRAME_LEFT_DOWN] = */{bongo_cat_left_down_png, bongo_cat_left_down_png_size, "embedded bongo-cat-left-down.png"},
            /*_bongocat_embedded_images[BONGOCAT_FRAME_RIGHT_DOWN] = */{bongo_cat_right_down_png, bongo_cat_right_down_png_size, "embedded bongo-cat-right-down.png"},
            /*_bongocat_embedded_images[BONGOCAT_FRAME_BOTH_DOWN] = */{bongo_cat_both_down_png, bongo_cat_both_down_png_size, "embedded bongo-cat-both-down.png"},
        };

        return _bongocat_embedded_images;
    }


#ifndef FEATURE_INCLUDE_ONLY_BONGOCAT_EMBEDDED_ASSETS
    extern const embedded_image_t* init_digimon_embedded_images();

    const embedded_image_t* digimon_sprite_sheet_embedded_images = init_digimon_embedded_images();

    const embedded_image_t* init_digimon_embedded_images() {
        using namespace assets;

        static constexpr embedded_image_t _digimon_sprite_sheet_embedded_images[DIGIMON_SPRITE_SHEET_EMBEDDED_IMAGES_COUNT] = {
            // index 0 is reserved for bongocat, no sprite sheet exists
            {nullptr, 0, "bongocat.png"},
#ifdef FEATURE_INCLUDE_DM_EMBEDDED_ASSETS
        /// @TODO: add full assets
#else
        //{dm_agumon_png, dm_agumon_png_size, "embedded agumon"},
#include "embedded_assets/min_dm_digimon_embedded_images_array.cpp.inl"
        /// @TODO: index more digimons here
#endif
        };

        return _digimon_sprite_sheet_embedded_images;
    }

#endif
}
