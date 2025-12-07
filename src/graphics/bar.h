#ifndef BONGOCAT_ANIMATION_BAR_H
#define BONGOCAT_ANIMATION_BAR_H

#include "platform/global_wayland_session.h"

namespace bongocat::animation {
    enum class draw_bar_result_t : uint8_t {
        Skip,
        Busy,
        FlushNeeded,
        NoFlushNeeded,
    };

    // Draw the overlay bar
    draw_bar_result_t draw_bar(platform::wayland::wayland_session_t& ctx);
}

#endif // BONGOCAT_ANIMATION_BAR_H