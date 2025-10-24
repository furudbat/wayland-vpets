#include "embedded_assets/embedded_image.h"
#include "embedded_assets/misc/misc.hpp"
#include "embedded_assets/misc/misc_images.h"
#include "embedded_assets/misc/misc_sprite.h"

namespace bongocat::assets {
    embedded_image_t get_misc_sprite_sheet(size_t i) {
        using namespace assets;
        switch (i) {
            case MISC_NEKO_ANIM_INDEX: return {misc_neko_png, misc_neko_png_size, "neko"};
            default: return { nullptr, 0, "" };
        }
        return { nullptr, 0, "" };
    }

    custom_animation_columns_t get_misc_sprite_sheet_columns(size_t i) {
        using namespace assets;
        switch (i) {
            case MISC_NEKO_ANIM_INDEX: return MISC_NEKO_SPRITE_SHEET_SETTINGS;
            default: return {};
        }
        return {};
    }
}