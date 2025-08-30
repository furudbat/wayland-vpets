#include "graphics/embedded_assets.h"
#include "graphics/sprite_sheet.h"
#include "graphics/embedded_assets/clippy.hpp"
#include "graphics/embedded_assets/clippy_images.h"

namespace bongocat::assets {
    embedded_image_t get_ms_agent_sprite_sheet(size_t i) {
        using namespace animation;
        switch (i) {
            case CLIPPY_ANIM_INDEX: return {clippy_png, clippy_png_size, "embedded clippy.png"};
#ifdef FEATURE_MORE_MS_AGENT_EMBEDDED_ASSETS
            case LINKS_ANIM_INDEX: return {links_png, links_png_size, "embedded links.png"};
#endif
            default: return {};
        }
    }

    ms_agent_animation_indices_t get_ms_agent_animation_indices(size_t i) {
        using namespace animation;
        switch (i) {
            case CLIPPY_ANIM_INDEX: return {
                .start_index_frame_idle = 0,
                .end_index_frame_idle = CLIPPY_FRAMES_IDLE-1,
                
                .start_index_frame_boring = 0,
                .end_index_frame_boring = CLIPPY_FRAMES_BORING-1,

                .start_index_frame_start_writing = 0,
                .end_index_frame_start_writing = CLIPPY_FRAMES_START_WRITING-1,

                .start_index_frame_writing = 0,
                .end_index_frame_writing = CLIPPY_FRAMES_WRITING-1,

                .start_index_frame_end_writing = 0,
                .end_index_frame_end_writing = CLIPPY_FRAMES_END_WRITING-1,

                .start_index_frame_sleep = 0,
                .end_index_frame_sleep = CLIPPY_FRAMES_SLEEP-1,

                .start_index_frame_wake_up = 0,
                .end_index_frame_wake_up = CLIPPY_FRAMES_WAKE_UP-1,
            };
#ifdef FEATURE_MORE_MS_AGENT_EMBEDDED_ASSETS
            case LINKS_ANIM_INDEX: return {
                .start_index_frame_idle = 0,
                .end_index_frame_idle = LINKS_FRAMES_IDLE-1,
                
                .start_index_frame_boring = 0,
                .end_index_frame_boring = LINKS_FRAMES_BORING-1,

                .start_index_frame_start_writing = 0,
                .end_index_frame_start_writing = LINKS_FRAMES_START_WRITING-1,

                .start_index_frame_writing = 0,
                .end_index_frame_writing = LINKS_FRAMES_WRITING-1,

                .start_index_frame_end_writing = 0,
                .end_index_frame_end_writing = LINKS_FRAMES_END_WRITING-1,

                .start_index_frame_sleep = 0,
                .end_index_frame_sleep = LINKS_FRAMES_SLEEP-1,

                .start_index_frame_wake_up = 0,
                .end_index_frame_wake_up = LINKS_FRAMES_WAKE_UP-1,
            };
#endif
            default: return {};
        }
    }
}