#ifndef BONGOCAT_WAYLAND_SETUPS_H
#define BONGOCAT_WAYLAND_SETUPS_H

#include "graphics/animation.h"
#include "platform/wayland_context.h"
#include "platform/wayland_shared_memory.h"

#include <cstdio>
#include <fcntl.h>
#include <spawn.h>
#include <sys/wait.h>
#include <unistd.h>

namespace bongocat::platform::wayland::details {
/// @TODO: use created_result_t for shm
// Create shared memory buffer - returns fd or -1 on error
BONGOCAT_NODISCARD created_result_t<FileDescriptor> create_shm(off_t size);

BONGOCAT_NODISCARD bongocat_error_t wayland_setup_protocols(wayland_context_t& ctx);
BONGOCAT_NODISCARD bongocat_error_t wayland_update_screen_info(wayland_context_t& ctx);
BONGOCAT_NODISCARD bongocat_error_t wayland_setup_surface(wayland_context_t& ctx);

struct wayland_setup_buffer_result_t {
  int32_t logical_w{0};
  int32_t logical_h{0};
  int32_t phys_w{0};
  int32_t phys_h{0};
  uint32_t scale_120{0};
};
BONGOCAT_NODISCARD created_result_t<wayland_setup_buffer_result_t> wayland_setup_buffer(wayland_thread_context& wayland_context,
                                                         animation::animation_context_t& animation_ctx);

struct spawn_pipe_t;
int safe_pclose_spawn(spawn_pipe_t& sp);

struct spawn_pipe_t {
  FILE *fp{BONGOCAT_NULLPTR};
  pid_t pid{-1};

  spawn_pipe_t() = default;
  spawn_pipe_t(const spawn_pipe_t&) = delete;
  spawn_pipe_t& operator=(const spawn_pipe_t&) = delete;
  spawn_pipe_t(spawn_pipe_t&& other) noexcept : fp(other.fp), pid(other.pid) {
    other.fp = BONGOCAT_NULLPTR;
    other.pid = -1;
  }
  spawn_pipe_t& operator=(spawn_pipe_t&& other) noexcept = delete;
  ~spawn_pipe_t() {
    safe_pclose_spawn(*this);
  }
};
BONGOCAT_NODISCARD spawn_pipe_t safe_popen_read_spawn(wayland_context_t& ctx, const char *path,
                                                      const char *const *argv);

created_result_t<int> wayland_update_current_output_info(wayland_context_t& ctx);
bongocat_error_t wayland_update_output(wayland_context_t& ctx);
BONGOCAT_NODISCARD bool fs_detector_available(wayland_context_t& ctx);
zwlr_layer_shell_v1_layer wayland_apply_layer_properties_v1(wayland_context_t& ctx);
uint32_t wayland_apply_anchor_properties_v1(wayland_context_t& ctx);


// Ceil-divide logical pixels by 120 / scale_120 to get physical pixels.
int phys_dim(const wayland_thread_context& ctx, int logical);

}  // namespace bongocat::platform::wayland::details

#endif