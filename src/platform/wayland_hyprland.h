#pragma once

#include "platform/global_wayland_session.h"

namespace bongocat::platform::wayland::hyprland {

static inline constexpr size_t LINE_BUF = 512;

struct window_info_t {
    int monitor_id{-1};     // monitor number in Hyprland
    int x{0};
    int y{0};
    int width{0};
    int height{0};
    bool fullscreen{false};
};

extern int fs_check_compositor_fallback();

extern void update_outputs_with_monitor_ids(wayland_session_t& ctx);

extern bool get_active_window(window_info_t& win);
}
