#include "embedded_assets/embedded_image.h"
#include "embedded_assets/min_dm/min_dm.hpp"
#include "min_dm_config_parse_animation_name.h"

namespace bongocat::assets {
    static const config_animation_entry_t min_dm_animation_table[] CONFIG_ENTRIES_TABLE_SECTION = {
      { MIN_DM_BOTAMON_NAME,       MIN_DM_BOTAMON_ID,       MIN_DM_BOTAMON_FQID,       MIN_DM_BOTAMON_FQNAME,       MIN_DM_BOTAMON_ANIM_INDEX,       config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },
      { MIN_DM_KOROMON_NAME,       MIN_DM_KOROMON_ID,       MIN_DM_KOROMON_FQID,       MIN_DM_KOROMON_FQNAME,       MIN_DM_KOROMON_ANIM_INDEX,       config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },
      { MIN_DM_AGUMON_NAME,        MIN_DM_AGUMON_ID,        MIN_DM_AGUMON_FQID,        MIN_DM_AGUMON_FQNAME,        MIN_DM_AGUMON_ANIM_INDEX,        config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },
      { MIN_DM_BETAMON_NAME,       MIN_DM_BETAMON_ID,       MIN_DM_BETAMON_FQID,       MIN_DM_BETAMON_FQNAME,       MIN_DM_BETAMON_ANIM_INDEX,       config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },

      { MIN_DM_GREYMON_NAME,       MIN_DM_GREYMON_ID,       MIN_DM_GREYMON_FQID,       MIN_DM_GREYMON_FQNAME,       MIN_DM_GREYMON_ANIM_INDEX,       config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },
      { MIN_DM_TYRANOMON_NAME,     MIN_DM_TYRANOMON_ID,     MIN_DM_TYRANOMON_FQID,     MIN_DM_TYRANOMON_FQNAME,     MIN_DM_TYRANOMON_ANIM_INDEX,     config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },
      { MIN_DM_DEVIMON_NAME,       MIN_DM_DEVIMON_ID,       MIN_DM_DEVIMON_FQID,       MIN_DM_DEVIMON_FQNAME,       MIN_DM_DEVIMON_ANIM_INDEX,       config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },
      { MIN_DM_MERAMON_NAME,       MIN_DM_MERAMON_ID,       MIN_DM_MERAMON_FQID,       MIN_DM_MERAMON_FQNAME,       MIN_DM_MERAMON_ANIM_INDEX,       config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },
      { MIN_DM_AIRDRAMON_NAME,     MIN_DM_AIRDRAMON_ID,     MIN_DM_AIRDRAMON_FQID,     MIN_DM_AIRDRAMON_FQNAME,     MIN_DM_AIRDRAMON_ANIM_INDEX,     config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },
      { MIN_DM_SEADRAMON_NAME,     MIN_DM_SEADRAMON_ID,     MIN_DM_SEADRAMON_FQID,     MIN_DM_SEADRAMON_FQNAME,     MIN_DM_SEADRAMON_ANIM_INDEX,     config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },
      { MIN_DM_NUMEMON_NAME,       MIN_DM_NUMEMON_ID,       MIN_DM_NUMEMON_FQID,       MIN_DM_NUMEMON_FQNAME,       MIN_DM_NUMEMON_ANIM_INDEX,       config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },

      { MIN_DM_METAL_GREYMON_NAME, MIN_DM_METAL_GREYMON_ID, MIN_DM_METAL_GREYMON_FQID, MIN_DM_METAL_GREYMON_FQNAME, MIN_DM_METAL_GREYMON_ANIM_INDEX, config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },
      { MIN_DM_MAMEMON_NAME,       MIN_DM_MAMEMON_ID,       MIN_DM_MAMEMON_FQID,       MIN_DM_MAMEMON_FQNAME,       MIN_DM_MAMEMON_ANIM_INDEX,       config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },
      { MIN_DM_MONZAEMON_NAME,     MIN_DM_MONZAEMON_ID,     MIN_DM_MONZAEMON_FQID,     MIN_DM_MONZAEMON_FQNAME,     MIN_DM_MONZAEMON_ANIM_INDEX,     config::config_animation_dm_set_t::dm, config::config_animation_sprite_sheet_layout_t::Dm },
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

