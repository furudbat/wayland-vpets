#ifndef BONGOCAT_ANIMATION_BAR_H
#define BONGOCAT_ANIMATION_BAR_H

#include "platform/global_wayland_context.h"

namespace bongocat::animation {
    bool draw_bar(platform::wayland_listeners_context_t& ctx);
}

#endif // BONGOCAT_ANIMATION_BAR_H