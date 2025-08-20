#include "graphics/embedded_assets.h"
#include "graphics/sprite_sheet.h"
#include "graphics/embedded_assets/clippy.hpp"

namespace bongocat::assets {
#ifndef FEATURE_INCLUDE_ONLY_BONGOCAT_EMBEDDED_ASSETS
    embedded_image_t get_ms_pet_sprite(size_t i) {
        using namespace animation;
        switch (i) {
            case CLIPPY_ANIM_INDEX: return {clippy_png, clippy_png_size, "embedded clippy.png"};
            default: return { nullptr, 0, "" };
        }
    }
#endif
}