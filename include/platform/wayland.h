#ifndef BONGOCAT_WAYLAND_H
#define BONGOCAT_WAYLAND_H

#include "config/config.h"
#include "config/config_watcher.h"
#include "graphics/animation_context.h"
#include "utils/error.h"
#include "wayland_context.h"

#include <csignal>

namespace bongocat::platform::wayland {
using config_reload_callback_t = void (*)();

// =============================================================================
// WAYLAND LIFECYCLE FUNCTIONS
// =============================================================================

// Initialize Wayland connection - must be checked
BONGOCAT_NODISCARD created_result_t<AllocatedMemory<wayland_context_t>>
create(animation::animation_context_t& animation_ctx, const config::config_t& config);
BONGOCAT_NODISCARD bongocat_error_t setup(wayland_context_t& ctx, animation::animation_context_t& animation_ctx);

// Run Wayland event loop - must be checked
BONGOCAT_NODISCARD bongocat_error_t run(wayland_context_t& ctx, volatile sig_atomic_t& running, int signal_fd,
                                        input::input_context_t& input, const config::config_t& config,
                                        const config::config_watcher_t *config_watcher,
                                        config_reload_callback_t config_reload_callback);

// Update configuration
void update_config(wayland_context_t& ctx, const config::config_t& config,
                   animation::animation_context_t& animation_ctx);

// Get detected screen width
BONGOCAT_NODISCARD int get_screen_width(const wayland_context_t& ctx);

// Get detected output name
BONGOCAT_NODISCARD const char *get_output_name(const wayland_context_t& ctx);

// Get current layer name for logging
BONGOCAT_NODISCARD const char *get_current_layer_name(wayland_context_t& ctx);

// HiDPI: convert a logical-pixel dimension to physical (buffer-coordinate)
// pixels using the active render scale. Defaults to identity (scale 1.0×) if
// the compositor has not announced a scale yet.
BONGOCAT_NODISCARD int phys_dim(const wayland_context_t& ctx, int logical);

bongocat_error_t request_render(animation::animation_context_t& animation_ctx);

namespace details {
  struct wayland_setup_buffer_result_t;
  created_result_t<wayland_setup_buffer_result_t> wayland_recreate_buffer(wayland_context_t& ctx);
}

}  // namespace bongocat::platform::wayland

#endif  // BONGOCAT_WAYLAND_H