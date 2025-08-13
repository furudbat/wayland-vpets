#ifndef BONGOCAT_ANIMATION_EVENT_CONTEXT_H
#define BONGOCAT_ANIMATION_EVENT_CONTEXT_H

#include "graphics/animation_context.h"
#include "platform/input_context.h"

typedef struct {
    // event file descriptor
    int trigger_efd;
    int render_efd;

    input_context_t *_input;
    animation_context_t *_anim;
} animation_trigger_context_t;

#endif
