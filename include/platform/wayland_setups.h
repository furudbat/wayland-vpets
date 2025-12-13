#ifndef BONGOCAT_WAYLAND_SETUPS_H
#define BONGOCAT_WAYLAND_SETUPS_H

#include "graphics/animation.h"
#include "platform/wayland_context.h"
#include "platform/wayland_shared_memory.h"

namespace bongocat::platform::wayland::details {
/// @TODO: use created_result_t for shm
// Create shared memory buffer - returns fd or -1 on error
BONGOCAT_NODISCARD created_result_t<FileDescriptor> create_shm(off_t size);

BONGOCAT_NODISCARD bongocat_error_t wayland_setup_protocols(wayland_context_t& ctx);
BONGOCAT_NODISCARD bongocat_error_t wayland_update_screen_info(wayland_context_t& ctx);
BONGOCAT_NODISCARD bongocat_error_t wayland_setup_surface(wayland_context_t& ctx);
BONGOCAT_NODISCARD bongocat_error_t wayland_setup_buffer(wayland_thread_context& wayland_context,
                                                         animation::animation_context_t& animation_ctx);
}  // namespace bongocat::platform::wayland::details

#endif