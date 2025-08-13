#ifndef BONGOCAT_ANIMATION_SHARED_MEMORY_H
#define BONGOCAT_ANIMATION_SHARED_MEMORY_H

#include "sprite_sheet.h"
#include "embedded_assets.h"
#include "utils/time.h"

struct animation_shared_memory_t {
    // Animation frame data
    animation_t anims[ANIMS_COUNT];
    int anim_index{0};
    int anim_frame_index{0};
    /// @NOTE: variables can be shared between child process and parent (see mmap)
    timestamp_ms_t time_until_next_frame_ms{0};
};

#endif // BONGOCAT_INPUT_EVENT_CONTEXT_H