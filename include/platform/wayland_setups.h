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
BONGOCAT_NODISCARD bongocat_error_t wayland_setup_buffer(wayland_thread_context& wayland_context,
                                                         animation::animation_context_t& animation_ctx);


struct spawn_pipe_t;
int safe_pclose_spawn(spawn_pipe_t& sp);

struct spawn_pipe_t {
  FILE *fp{nullptr};
  pid_t pid{-1};

  spawn_pipe_t() = default;
  spawn_pipe_t(const spawn_pipe_t&) = delete;
  spawn_pipe_t& operator=(const spawn_pipe_t&) = delete;
  spawn_pipe_t(spawn_pipe_t&& other) noexcept : fp(other.fp), pid(other.pid) {
    other.fp = nullptr;
    other.pid = -1;
  }
  spawn_pipe_t& operator=(spawn_pipe_t&& other) noexcept = delete;
  ~spawn_pipe_t() {
    safe_pclose_spawn(*this);
  }
};
BONGOCAT_NODISCARD spawn_pipe_t safe_popen_read_spawn(wayland_context_t& ctx, const char *path, const char *const *argv);

}  // namespace bongocat::platform::wayland::details

#endif