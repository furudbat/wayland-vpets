#ifndef BONGOCAT_ANIMATION_EVENT_CONTEXT_H
#define BONGOCAT_ANIMATION_EVENT_CONTEXT_H

#include "graphics/animation_context.h"
#include "platform/input_context.h"

struct animation_trigger_context_t {
    // event file descriptor
    FileDescriptor trigger_efd;
    FileDescriptor render_efd;

    input_context_t *_input{nullptr};
    animation_context_t *_anim{nullptr};
};

#endif
