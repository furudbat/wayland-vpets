#ifndef BONGOCAT_EMBEDDED_ASSETS_BONGOCAT_IMAGES_HPP
#define BONGOCAT_EMBEDDED_ASSETS_BONGOCAT_IMAGES_HPP

#include <cstddef>

namespace bongocat::assets {
    // Embedded asset data
    inline static constexpr unsigned char bongo_cat_both_up_png[] = {
#embed "../../../assets/bongo-cat-both-up.png"
    };
    inline static constexpr std::size_t bongo_cat_both_up_png_size = sizeof(bongo_cat_both_up_png);

    inline static constexpr unsigned char bongo_cat_left_down_png[] = {
#embed "../../../assets/bongo-cat-left-down.png"
    };
    inline static constexpr std::size_t bongo_cat_left_down_png_size = sizeof(bongo_cat_left_down_png);

    inline static constexpr unsigned char bongo_cat_right_down_png[] = {
#embed "../../../assets/bongo-cat-right-down.png"
    };
    inline static constexpr std::size_t bongo_cat_right_down_png_size = sizeof(bongo_cat_right_down_png);

    inline static constexpr unsigned char bongo_cat_both_down_png[] = {
#embed "../../../assets/bongo-cat-both-down.png"
    };
    inline static constexpr std::size_t bongo_cat_both_down_png_size = sizeof(bongo_cat_both_down_png);
}

#endif // BONGOCAT_EMBEDDED_ASSETS_BONGOCAT_IMAGES_HPP
