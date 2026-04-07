#pragma once

#include "platform/wayland_context.h"

namespace bongocat::platform::wayland::sway {

static inline constexpr size_t SWAY_BUF = 4096;
static inline constexpr const char * const SWAYMSG_COMMAND = "/usr/bin/swaymsg";

extern int fs_check_compositor_fallback(wayland_context_t& ctx);

}  // namespace bongocat::platform::wayland::sway
