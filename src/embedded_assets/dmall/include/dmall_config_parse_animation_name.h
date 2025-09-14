#ifndef BONGOCAT_EMBEDDED_ASSETS_CONFIG_PARSE_DMALL_ANIMATION_NAME_H
#define BONGOCAT_EMBEDDED_ASSETS_CONFIG_PARSE_DMALL_ANIMATION_NAME_H

#include "config/config.h"
#include "embedded_assets/embedded_image.h"

namespace bongocat::assets {
    [[nodiscard]] extern config_animation_entry_t get_config_animation_name_dmall(size_t i);
    extern void config_parse_animation_name_dmall(config::config_t& config, const char *value);
}

#endif

