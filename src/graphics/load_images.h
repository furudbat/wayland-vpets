#pragma once

#include "graphics/embedded_assets.h"
#include "graphics/animation_context.h"
#include "utils/memory.h"
#include <pthread.h>

namespace bongocat::animation {
    // =============================================================================
    // IMAGE LOADING MODULE
    // =============================================================================

    struct loaded_sprite_sheet_frame_t {
        int channels{0};
        uint8_t *pixels{nullptr};
        size_t pixels_size{0};
        int frame_width{0};
        int frame_height{0};
    };

    using get_sprite_callback_t = assets::embedded_image_t (*)(size_t);

#if defined(FEATURE_BONGOCAT_EMBEDDED_ASSETS) || defined(FEATURE_ENABLE_DM_EMBEDDED_ASSETS)
    int anim_load_embedded_images_into_sprite_sheet(generic_sprite_sheet_animation_t& anim, get_sprite_callback_t get_sprite, size_t embedded_images_count);
#endif

#ifdef FEATURE_MS_AGENT_EMBEDDED_ASSETS
    bongocat_error_t load_sprite_sheet_from_memory(ms_pet_sprite_sheet_t& out_frames,
                                                  const uint8_t* sprite_data, size_t sprite_data_size,
                                                  int frame_columns, int frame_rows,
                                                  int padding_x, int padding_y);
    bongocat_error_t anim_load_sprite_sheet(const config::config_t& config, ms_pet_sprite_sheet_t& anim, const assets::embedded_image_t& sprite_sheet_image, int sprite_sheet_cols, int sprite_sheet_rows);
#endif


#ifdef FEATURE_BONGOCAT_EMBEDDED_ASSETS
    bongocat_error_t init_bongocat_anim(animation_context_t& ctx, int anim_index, get_sprite_callback_t get_sprite, size_t embedded_images_count);
#endif

#ifdef FEATURE_ENABLE_DM_EMBEDDED_ASSETS
    bongocat_error_t init_dm_anim(animation_context_t& ctx, int anim_index, const assets::embedded_image_t& sprite_sheet_image, int sprite_sheet_cols, int sprite_sheet_rows);
#endif

#ifdef FEATURE_MS_AGENT_EMBEDDED_ASSETS
    bongocat_error_t init_ms_pet_anim(animation_context_t& ctx, int anim_index, const assets::embedded_image_t& sprite_sheet_image, int sprite_sheet_cols, int sprite_sheet_rows);
#endif
}
