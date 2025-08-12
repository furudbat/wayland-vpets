#ifndef BONGOCAT_ANIMATION_SHARED_MEMORY_H
#define BONGOCAT_ANIMATION_SHARED_MEMORY_H

#include "sprite_sheet.h"
#include "embedded_assets.h"
#include "utils/time.h"

typedef struct {
    // Animation frame data
    animation_t anims[ANIMS_COUNT];
    int anim_index;
    int anim_frame_index;
    /// @NOTE: variables can be shared between child process and parent (see mmap)
    timestamp_ms_t time_until_next_frame_ms;
} animation_shared_memory_t;

#endif // BONGOCAT_INPUT_EVENT_CONTEXT_H