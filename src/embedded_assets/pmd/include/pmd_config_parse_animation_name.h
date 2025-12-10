#ifndef BONGOCAT_EMBEDDED_ASSETS_CONFIG_PARSE_CUSTOM_PMD_ANIMATION_NAME_H
#define BONGOCAT_EMBEDDED_ASSETS_CONFIG_PARSE_CUSTOM_PMD_ANIMATION_NAME_H

#include "config/config.h"
#include "embedded_assets/embedded_image.h"

namespace bongocat::assets {
    BONGOCAT_NODISCARD extern config_custom_animation_entry_t get_config_animation_name_pmd(size_t i);
    extern int config_parse_animation_name_pmd(config::config_t& config, const char *value);
}

#endif

