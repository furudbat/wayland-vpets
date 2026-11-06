#include "core/bongocat.h"
#include "embedded_assets/embedded_image.h"
#include "embedded_assets/min_dm/min_dm.hpp"
#include "embedded_assets/min_dm/min_dm_sprite.h"
#include "graphics/animation_thread_context.h"
#include "graphics/sprite_sheet.h"
#include "image_loader/base_dm/load_dm.h"
#include "image_loader/dm/load_images_dm.h"
#include "image_loader/min_dm/load_images_min_dm.h"
#include "embedded_assets/min_dm/min_dm_images.h"

namespace bongocat::animation {
    static constexpr assets::embedded_sprite_sheet_dims_t min_dm_dims_table[] = {
      {assets::MIN_DM_BOTAMON_SPRITE_SHEET_COLS,       assets::MIN_DM_BOTAMON_SPRITE_SHEET_ROWS},
      {assets::MIN_DM_KOROMON_SPRITE_SHEET_COLS,       assets::MIN_DM_KOROMON_SPRITE_SHEET_ROWS},
      {assets::MIN_DM_AGUMON_SPRITE_SHEET_COLS,        assets::MIN_DM_AGUMON_SPRITE_SHEET_ROWS},
      {assets::MIN_DM_BETAMON_SPRITE_SHEET_COLS,       assets::MIN_DM_BETAMON_SPRITE_SHEET_ROWS},

      {assets::MIN_DM_GREYMON_SPRITE_SHEET_COLS,       assets::MIN_DM_GREYMON_SPRITE_SHEET_ROWS},
      {assets::MIN_DM_TYRANOMON_SPRITE_SHEET_COLS,     assets::MIN_DM_TYRANOMON_SPRITE_SHEET_ROWS},
      {assets::MIN_DM_DEVIMON_SPRITE_SHEET_COLS,       assets::MIN_DM_DEVIMON_SPRITE_SHEET_ROWS},
      {assets::MIN_DM_MERAMON_SPRITE_SHEET_COLS,       assets::MIN_DM_MERAMON_SPRITE_SHEET_ROWS},
      {assets::MIN_DM_AIRDRAMON_SPRITE_SHEET_COLS,     assets::MIN_DM_AIRDRAMON_SPRITE_SHEET_ROWS},
      {assets::MIN_DM_SEADRAMON_SPRITE_SHEET_COLS,     assets::MIN_DM_SEADRAMON_SPRITE_SHEET_ROWS},
      {assets::MIN_DM_NUMEMON_SPRITE_SHEET_COLS,       assets::MIN_DM_NUMEMON_SPRITE_SHEET_ROWS},

      {assets::MIN_DM_METAL_GREYMON_SPRITE_SHEET_COLS, assets::MIN_DM_METAL_GREYMON_SPRITE_SHEET_ROWS},
      {assets::MIN_DM_MAMEMON_SPRITE_SHEET_COLS,       assets::MIN_DM_MAMEMON_SPRITE_SHEET_ROWS},
      {assets::MIN_DM_MONZAEMON_SPRITE_SHEET_COLS,     assets::MIN_DM_MONZAEMON_SPRITE_SHEET_ROWS},
    };
    static const unsigned char* min_dm_pngs_table[] = {
        min_dm_botamon_png,
        min_dm_koromon_png,
        min_dm_agumon_png,
        min_dm_betamon_png,

        min_dm_greymon_png,
        min_dm_tyranomon_png,
        min_dm_devimon_png,
        min_dm_meramon_png,
        min_dm_airdramon_png,
        min_dm_seadramon_png,
        min_dm_numemon_png,

        min_dm_metal_greymon_png,
        min_dm_mamemon_png,
        min_dm_monzaemon_png,
    };
    static const size_t min_dm_png_sizes_table[] = {
      min_dm_botamon_png_size,
      min_dm_koromon_png_size,
      min_dm_agumon_png_size,
      min_dm_betamon_png_size,

      min_dm_greymon_png_size,
      min_dm_tyranomon_png_size,
      min_dm_devimon_png_size,
      min_dm_meramon_png_size,
      min_dm_airdramon_png_size,
      min_dm_seadramon_png_size,
      min_dm_numemon_png_size,

      min_dm_metal_greymon_png_size,
      min_dm_mamemon_png_size,
      min_dm_monzaemon_png_size,
    };
    static const char* min_dm_names_table[] = {
        "botamon",
        "koromon",
        "agumon",
        "betamon",

        "greymon",
        "tyranomon",
        "devimon",
        "meramon",
        "airdramon",
        "seadramon",
        "numemon",

        "metal_greymon",
        "mamemon",
        "monzaemon",
    };
    created_result_t<dm_sprite_sheet_t> load_min_dm_sprite_sheet(const animation_thread_context_t& ctx, size_t index) {
        using namespace assets;
        assert(LEN_ARRAY(min_dm_dims_table) == MIN_DM_ANIM_COUNT);
        assert(LEN_ARRAY(min_dm_pngs_table) == MIN_DM_ANIM_COUNT);
        assert(LEN_ARRAY(min_dm_png_sizes_table) == MIN_DM_ANIM_COUNT);
        assert(LEN_ARRAY(min_dm_names_table) == MIN_DM_ANIM_COUNT);
        assert(index < MIN_DM_ANIM_COUNT);
        auto result = load_base_dm_anim(ctx, index, {min_dm_pngs_table[index], min_dm_png_sizes_table[index], min_dm_names_table[index]}, min_dm_dims_table[index].cols, min_dm_dims_table[index].rows);
        return result;
    }
    void init_all_min_dm_anim(animation_thread_context_t& ctx) {
        using namespace assets;
        for (size_t i = 0;i < MIN_DM_ANIM_COUNT;++i) {
            init_min_dm_anim(ctx, i, {min_dm_pngs_table[i], min_dm_png_sizes_table[i], min_dm_names_table[i]}, min_dm_dims_table[i].cols, min_dm_dims_table[i].rows);
        }
    }
}  // namespace bongocat::animation