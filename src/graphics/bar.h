#ifndef BONGOCAT_ANIMATION_BAR_H
#define BONGOCAT_ANIMATION_BAR_H

#include "platform/wayland_context.h"

namespace bongocat::animation {
enum class draw_bar_result_t : uint8_t {
  Skip,
  Busy,
  FlushNeeded,
  NoFlushNeeded,
};

// Draw the overlay bar
draw_bar_result_t draw_bar(platform::wayland::wayland_context_t& ctx);
}  // namespace bongocat::animation

#endif  // BONGOCAT_ANIMATION_BAR_H