#ifndef BONGOCAT_WAYLAND_SETUPS_H
#define BONGOCAT_WAYLAND_SETUPS_H

#include "graphics/animation.h"
#include "platform/wayland_shared_memory.h"
#include "platform/global_wayland_session.h"

namespace bongocat::platform::wayland::details {
    /// @TODO: use created_result_t for shm
    // Create shared memory buffer - returns fd or -1 on error
    BONGOCAT_NODISCARD FileDescriptor create_shm(off_t size);

    BONGOCAT_NODISCARD bongocat_error_t wayland_setup_protocols(wayland_session_t& ctx);
    BONGOCAT_NODISCARD bongocat_error_t wayland_update_screen_width(wayland_session_t& ctx);
    BONGOCAT_NODISCARD bongocat_error_t wayland_setup_surface(wayland_session_t& ctx);
    BONGOCAT_NODISCARD bongocat_error_t wayland_setup_buffer(wayland_context_t& wayland_context, animation::animation_session_t& anim);
}

#endif