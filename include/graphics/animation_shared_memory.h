#ifndef BONGOCAT_ANIMATION_SHARED_MEMORY_H
#define BONGOCAT_ANIMATION_SHARED_MEMORY_H

#include "sprite_sheet.h"
#include "embedded_assets.h"
#include "utils/time.h"

struct animation_shared_memory_t {
    /// @NOTE: variables can be shared between child process and parent (see mmap)
    // Animation frame data
    animation_t anims[ANIMS_COUNT];
    int anim_index{0};
    int anim_frame_index{0};
    timestamp_ms_t time_until_next_frame_ms{0};
};

#endif // BONGOCAT_ANIMATION_SHARED_MEMORY_H