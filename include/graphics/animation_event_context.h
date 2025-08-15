#ifndef BONGOCAT_ANIMATION_EVENT_CONTEXT_H
#define BONGOCAT_ANIMATION_EVENT_CONTEXT_H

#include "graphics/animation_context.h"
#include "platform/input_context.h"

namespace bongocat::animation {
    struct animation_trigger_context_t {
        // event file descriptor
        platform::FileDescriptor trigger_efd;
        platform::FileDescriptor render_efd;

        platform::input_context_t *_input{nullptr};
        animation_context_t *_anim{nullptr};
    };
}

#endif
