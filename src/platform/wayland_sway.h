#pragma once

#include "platform/global_wayland_session.h"

namespace bongocat::platform::wayland::sway {

static inline constexpr size_t SWAY_BUF = 4096;

extern int fs_check_compositor_fallback();

}  // namespace bongocat::platform::wayland::sway
