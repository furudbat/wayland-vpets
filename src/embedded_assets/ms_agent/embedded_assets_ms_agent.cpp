#include "embedded_assets/embedded_image.h"
#include "embedded_assets/ms_agent/ms_agent.hpp"
#include "embedded_assets/ms_agent/ms_agent_images.h"
#include "embedded_assets/ms_agent/ms_agent_sprite.h"

namespace bongocat::assets {

static const embedded_image_t ms_agent_images_table[] = {
  {clippy_png, clippy_png_size, "clippy"},
#ifdef FEATURE_MORE_MS_AGENT_EMBEDDED_ASSETS
  {links_png, links_png_size, "links"},
  {rover_png, rover_png_size, "rover"},
  {merlin_png, merlin_png_size, "merlin"},
#endif
};

static const ms_agent_animation_indices_t ms_agent_animation_indices_table[] = {
    {
        .start_index_frame_idle = 0,
        .end_index_frame_idle = CLIPPY_FRAMES_IDLE - 1,

        .start_index_frame_boring = 0,
        .end_index_frame_boring = CLIPPY_FRAMES_BORING - 1,

        .start_index_frame_start_writing = 0,
        .end_index_frame_start_writing = CLIPPY_FRAMES_START_WRITING - 1,

        .start_index_frame_writing = 0,
        .end_index_frame_writing = CLIPPY_FRAMES_WRITING - 1,

        .start_index_frame_end_writing = 0,
        .end_index_frame_end_writing = CLIPPY_FRAMES_END_WRITING - 1,

        .start_index_frame_sleep = 0,
        .end_index_frame_sleep = CLIPPY_FRAMES_SLEEP - 1,

        .start_index_frame_wake_up = 0,
        .end_index_frame_wake_up = CLIPPY_FRAMES_WAKE_UP - 1,
    },
#ifdef FEATURE_MORE_MS_AGENT_EMBEDDED_ASSETS
    {
        .start_index_frame_idle = 0,
        .end_index_frame_idle = LINKS_FRAMES_IDLE - 1,

        .start_index_frame_boring = 0,
        .end_index_frame_boring = LINKS_FRAMES_BORING - 1,

        .start_index_frame_start_writing = 0,
        .end_index_frame_start_writing = LINKS_FRAMES_START_WRITING - 1,

        .start_index_frame_writing = 0,
        .end_index_frame_writing = LINKS_FRAMES_WRITING - 1,

        .start_index_frame_end_writing = 0,
        .end_index_frame_end_writing = LINKS_FRAMES_END_WRITING - 1,

        .start_index_frame_sleep = 0,
        .end_index_frame_sleep = LINKS_FRAMES_SLEEP - 1,

        .start_index_frame_wake_up = 0,
        .end_index_frame_wake_up = LINKS_FRAMES_WAKE_UP - 1,
    },
    {
        .start_index_frame_idle = 0,
        .end_index_frame_idle = ROVER_FRAMES_IDLE - 1,

        .start_index_frame_boring = 0,
        .end_index_frame_boring = ROVER_FRAMES_BORING - 1,

        .start_index_frame_start_writing = 0,
        .end_index_frame_start_writing = ROVER_FRAMES_START_WRITING - 1,

        .start_index_frame_writing = 0,
        .end_index_frame_writing = ROVER_FRAMES_WRITING - 1,

        .start_index_frame_end_writing = 0,
        .end_index_frame_end_writing = ROVER_FRAMES_END_WRITING - 1,

        .start_index_frame_sleep = 0,
        .end_index_frame_sleep = ROVER_FRAMES_SLEEP - 1,

        .start_index_frame_wake_up = 0,
        .end_index_frame_wake_up = ROVER_FRAMES_WAKE_UP - 1,
    },
    {
        .start_index_frame_idle = 0,
        .end_index_frame_idle = MERLIN_FRAMES_IDLE - 1,

        .start_index_frame_boring = 0,
        .end_index_frame_boring = MERLIN_FRAMES_BORING - 1,

        .start_index_frame_start_writing = 0,
        .end_index_frame_start_writing = MERLIN_FRAMES_START_WRITING - 1,

        .start_index_frame_writing = 0,
        .end_index_frame_writing = MERLIN_FRAMES_WRITING - 1,

        .start_index_frame_end_writing = 0,
        .end_index_frame_end_writing = MERLIN_FRAMES_END_WRITING - 1,

        .start_index_frame_sleep = 0,
        .end_index_frame_sleep = MERLIN_FRAMES_SLEEP - 1,

        .start_index_frame_wake_up = 0,
        .end_index_frame_wake_up = MERLIN_FRAMES_WAKE_UP - 1,
    },
#endif
};

embedded_image_t get_ms_agent_sprite_sheet(size_t index) {
  assert(LEN_ARRAY(ms_agent_images_table) == MISC_ANIM_COUNT);
  assert(index < MISC_ANIM_COUNT);
  return ms_agent_images_table[index];
}

ms_agent_animation_indices_t get_ms_agent_animation_indices(size_t index) {
  assert(LEN_ARRAY(ms_agent_animation_indices_table) == MISC_ANIM_COUNT);
  assert(index < MISC_ANIM_COUNT);
  return ms_agent_animation_indices_table[index];
}
}  // namespace bongocat::assets