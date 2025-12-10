#include "core/bongocat.h"
#include "embedded_assets/embedded_image.h"
#include "embedded_assets/min_dm/min_dm.hpp"
#include "embedded_assets/min_dm/min_dm_sprite.h"
#include "graphics/animation_thread_context.h"
#include "graphics/sprite_sheet.h"
#include "image_loader/base_dm/load_dm.h"
#include "image_loader/min_dm/load_images_min_dm.h"

namespace bongocat::animation {
created_result_t<dm_sprite_sheet_t> load_min_dm_sprite_sheet(const animation_thread_context_t& ctx, int index) {
  using namespace animation;
  using namespace assets;
  switch (index) {
  case DM_BOTAMON_ANIM_INDEX:
    return load_dm_anim(ctx, DM_BOTAMON_ANIM_INDEX, get_min_dm_sprite_sheet(DM_BOTAMON_ANIM_INDEX),
                        DM_BOTAMON_SPRITE_SHEET_COLS, DM_BOTAMON_SPRITE_SHEET_ROWS);
  case DM_KOROMON_ANIM_INDEX:
    return load_dm_anim(ctx, DM_KOROMON_ANIM_INDEX, get_min_dm_sprite_sheet(DM_KOROMON_ANIM_INDEX),
                        DM_KOROMON_SPRITE_SHEET_COLS, DM_KOROMON_SPRITE_SHEET_ROWS);
  case DM_AGUMON_ANIM_INDEX:
    return load_dm_anim(ctx, DM_AGUMON_ANIM_INDEX, get_min_dm_sprite_sheet(DM_AGUMON_ANIM_INDEX),
                        DM_AGUMON_SPRITE_SHEET_COLS, DM_AGUMON_SPRITE_SHEET_ROWS);
  case DM_BETAMON_ANIM_INDEX:
    return load_dm_anim(ctx, DM_BETAMON_ANIM_INDEX, get_min_dm_sprite_sheet(DM_BETAMON_ANIM_INDEX),
                        DM_BETAMON_SPRITE_SHEET_COLS, DM_BETAMON_SPRITE_SHEET_ROWS);
  case DM_GREYMON_ANIM_INDEX:
    return load_dm_anim(ctx, DM_GREYMON_ANIM_INDEX, get_min_dm_sprite_sheet(DM_GREYMON_ANIM_INDEX),
                        DM_GREYMON_SPRITE_SHEET_COLS, DM_GREYMON_SPRITE_SHEET_ROWS);
  case DM_TYRANOMON_ANIM_INDEX:
    return load_dm_anim(ctx, DM_TYRANOMON_ANIM_INDEX, get_min_dm_sprite_sheet(DM_TYRANOMON_ANIM_INDEX),
                        DM_TYRANOMON_SPRITE_SHEET_COLS, DM_TYRANOMON_SPRITE_SHEET_ROWS);
  case DM_DEVIMON_ANIM_INDEX:
    return load_dm_anim(ctx, DM_DEVIMON_ANIM_INDEX, get_min_dm_sprite_sheet(DM_DEVIMON_ANIM_INDEX),
                        DM_DEVIMON_SPRITE_SHEET_COLS, DM_DEVIMON_SPRITE_SHEET_ROWS);
  case DM_MERAMON_ANIM_INDEX:
    return load_dm_anim(ctx, DM_MERAMON_ANIM_INDEX, get_min_dm_sprite_sheet(DM_MERAMON_ANIM_INDEX),
                        DM_MERAMON_SPRITE_SHEET_COLS, DM_MERAMON_SPRITE_SHEET_ROWS);
  case DM_AIRDRAMON_ANIM_INDEX:
    return load_dm_anim(ctx, DM_AIRDRAMON_ANIM_INDEX, get_min_dm_sprite_sheet(DM_AIRDRAMON_ANIM_INDEX),
                        DM_AIRDRAMON_SPRITE_SHEET_COLS, DM_AIRDRAMON_SPRITE_SHEET_ROWS);
  case DM_SEADRAMON_ANIM_INDEX:
    return load_dm_anim(ctx, DM_SEADRAMON_ANIM_INDEX, get_min_dm_sprite_sheet(DM_SEADRAMON_ANIM_INDEX),
                        DM_SEADRAMON_SPRITE_SHEET_COLS, DM_SEADRAMON_SPRITE_SHEET_ROWS);
  case DM_NUMEMON_ANIM_INDEX:
    return load_dm_anim(ctx, DM_NUMEMON_ANIM_INDEX, get_min_dm_sprite_sheet(DM_NUMEMON_ANIM_INDEX),
                        DM_NUMEMON_SPRITE_SHEET_COLS, DM_NUMEMON_SPRITE_SHEET_ROWS);
  case DM_METAL_GREYMON_ANIM_INDEX:
    return load_dm_anim(ctx, DM_METAL_GREYMON_ANIM_INDEX, get_min_dm_sprite_sheet(DM_METAL_GREYMON_ANIM_INDEX),
                        DM_METAL_GREYMON_SPRITE_SHEET_COLS, DM_METAL_GREYMON_SPRITE_SHEET_ROWS);
  case DM_MAMEMON_ANIM_INDEX:
    return load_dm_anim(ctx, DM_MAMEMON_ANIM_INDEX, get_min_dm_sprite_sheet(DM_MAMEMON_ANIM_INDEX),
                        DM_MAMEMON_SPRITE_SHEET_COLS, DM_MAMEMON_SPRITE_SHEET_ROWS);
  case DM_MONZAEMON_ANIM_INDEX:
    return load_dm_anim(ctx, DM_MONZAEMON_ANIM_INDEX, get_min_dm_sprite_sheet(DM_MONZAEMON_ANIM_INDEX),
                        DM_MONZAEMON_SPRITE_SHEET_COLS, DM_MONZAEMON_SPRITE_SHEET_ROWS);
  default:
    return bongocat_error_t::BONGOCAT_ERROR_INVALID_PARAM;
  }
  return bongocat_error_t::BONGOCAT_ERROR_INVALID_PARAM;
}
}  // namespace bongocat::animation