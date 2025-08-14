#ifndef BONGOCAT_ANIMATION_EVENT_CONTEXT_H
#define BONGOCAT_ANIMATION_EVENT_CONTEXT_H

#include "graphics/animation_context.h"
#include "platform/input_context.h"

struct animation_trigger_context_t {
    // event file descriptor
    int trigger_efd{-1};
    int render_efd{-1};

    input_context_t *_input{nullptr};
    animation_context_t *_anim{nullptr};
};

#endif
