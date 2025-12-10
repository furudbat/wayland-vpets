#pragma once

#include "platform/wayland_context.h"

namespace bongocat::platform::wayland::sway {

static inline constexpr size_t SWAY_BUF = 4096;

extern int fs_check_compositor_fallback();

}  // namespace bongocat::platform::wayland::sway
