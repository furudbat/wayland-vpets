#ifndef BONGOCAT_ANIMATION_BAR_H
#define BONGOCAT_ANIMATION_BAR_H

#include "platform/global_wayland_context.h"

namespace bongocat::animation {
    bool draw_bar(platform::wayland::wayland_session_t& ctx);
}

#endif // BONGOCAT_ANIMATION_BAR_H