#ifndef BONGOCAT_EMBEDDED_ASSETS_IMAGE_H
#define BONGOCAT_EMBEDDED_ASSETS_IMAGE_H

#include "config/config.h"
#include <cstddef>

namespace bongocat::assets {
    struct embedded_image_t {
        const unsigned char *data{nullptr};
        size_t size{0};
        const char *name{""};
    };

    struct config_animation_entry_t {
        const char* name{""};
        const char* id{""};
        const char* fqid{""};
        const char* fqname{""};
        int anim_index{0};
        config::config_animation_dm_set_t set{config::config_animation_dm_set_t::None};
        config::config_animation_sprite_sheet_layout_t layout{config::config_animation_sprite_sheet_layout_t::None};
    };
    struct config_custom_animation_entry_t {
        const char* name{""};
        const char* id{""};
        const char* fqid{""};
        const char* fqname{""};
        int anim_index{0};
        config::config_animation_custom_set_t set{config::config_animation_custom_set_t::None};
        config::config_animation_sprite_sheet_layout_t layout{config::config_animation_sprite_sheet_layout_t::None};
    };
}

#endif // BONGOCAT_EMBEDDED_ASSETS_IMAGE_H
