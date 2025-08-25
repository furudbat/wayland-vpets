#include "graphics/embedded_assets.h"
#include "graphics/sprite_sheet.h"
#include "graphics/embedded_assets/clippy.hpp"
#include "graphics/embedded_assets/clippy_images.h"

namespace bongocat::assets {
    embedded_image_t get_ms_agent_sprite_sheet(size_t i) {
        using namespace animation;
        switch (i) {
            case CLIPPY_ANIM_INDEX: return {clippy_png, clippy_png_size, "embedded clippy.png"};
            default: return { nullptr, 0, "" };
        }
    }
}