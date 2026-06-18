#include "embedded_assets/embedded_image.h"
#include "embedded_assets/min_dm/min_dm.hpp"
#include "min_dm_config_parse_animation_name.h"

namespace bongocat::assets {
    static const config_animation_entry_t min_dm_animation_table[] = {
      { DM_BOTAMON_NAME,       DM_BOTAMON_ID,       DM_BOTAMON_FQID,       DM_BOTAMON_FQNAME,       DM_BOTAMON_ANIM_INDEX,       config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },
      { DM_KOROMON_NAME,       DM_KOROMON_ID,       DM_KOROMON_FQID,       DM_KOROMON_FQNAME,       DM_KOROMON_ANIM_INDEX,       config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },
      { DM_AGUMON_NAME,        DM_AGUMON_ID,        DM_AGUMON_FQID,        DM_AGUMON_FQNAME,        DM_AGUMON_ANIM_INDEX,        config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },
      { DM_BETAMON_NAME,       DM_BETAMON_ID,       DM_BETAMON_FQID,       DM_BETAMON_FQNAME,       DM_BETAMON_ANIM_INDEX,       config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },

      { DM_GREYMON_NAME,       DM_GREYMON_ID,       DM_GREYMON_FQID,       DM_GREYMON_FQNAME,       DM_GREYMON_ANIM_INDEX,       config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },
      { DM_TYRANOMON_NAME,     DM_TYRANOMON_ID,     DM_TYRANOMON_FQID,     DM_TYRANOMON_FQNAME,     DM_TYRANOMON_ANIM_INDEX,     config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },
      { DM_DEVIMON_NAME,       DM_DEVIMON_ID,       DM_DEVIMON_FQID,       DM_DEVIMON_FQNAME,       DM_DEVIMON_ANIM_INDEX,       config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },
      { DM_MERAMON_NAME,       DM_MERAMON_ID,       DM_MERAMON_FQID,       DM_MERAMON_FQNAME,       DM_MERAMON_ANIM_INDEX,       config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },
      { DM_AIRDRAMON_NAME,     DM_AIRDRAMON_ID,     DM_AIRDRAMON_FQID,     DM_AIRDRAMON_FQNAME,     DM_AIRDRAMON_ANIM_INDEX,     config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },
      { DM_SEADRAMON_NAME,     DM_SEADRAMON_ID,     DM_SEADRAMON_FQID,     DM_SEADRAMON_FQNAME,     DM_SEADRAMON_ANIM_INDEX,     config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },
      { DM_NUMEMON_NAME,       DM_NUMEMON_ID,       DM_NUMEMON_FQID,       DM_NUMEMON_FQNAME,       DM_NUMEMON_ANIM_INDEX,       config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },

      { DM_METAL_GREYMON_NAME, DM_METAL_GREYMON_ID, DM_METAL_GREYMON_FQID, DM_METAL_GREYMON_FQNAME, DM_METAL_GREYMON_ANIM_INDEX, config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },
      { DM_MAMEMON_NAME,       DM_MAMEMON_ID,       DM_MAMEMON_FQID,       DM_MAMEMON_FQNAME,       DM_MAMEMON_ANIM_INDEX,       config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },
      { DM_MONZAEMON_NAME,     DM_MONZAEMON_ID,     DM_MONZAEMON_FQID,     DM_MONZAEMON_FQNAME,     DM_MONZAEMON_ANIM_INDEX,     config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },
  };

    config_animation_entry_t get_config_animation_name_min_dm(size_t index) {
        assert(index < MIN_DM_ANIM_COUNT);
        return min_dm_animation_table[index];
    }

    int config_parse_animation_name_min_dm(config::config_t& config, const char *value) {
        for (const auto& entry : min_dm_animation_table) {
            if (strcmp(value, entry.name) == 0 ||
                strcmp(value, entry.id) == 0 ||
                strcmp(value, entry.fqid) == 0 ||
                strcmp(value, entry.fqname) == 0) {
                config.animation_index = entry.anim_index;
                config.animation_dm_set = entry.set;
                config.animation_sprite_sheet_layout = entry.layout;
                return entry.anim_index;
            }
        }
        return -1;
    }
}

