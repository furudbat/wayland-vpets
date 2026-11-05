#include "platform/wayland.h"
#include "platform/wayland_callbacks.h"
#include "platform/wayland_setups.h"
#include "utils/error.h"

#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fcntl.h>
#include <pthread.h>
#include <sys/signalfd.h>
#include <sys/types.h>
#include <wayland-client.h>

namespace bongocat::platform::wayland {

BONGOCAT_NODISCARD static created_result_t<AllocatedMemory<wayland_context_t>> connect_display() {
  AllocatedMemory<wayland_context_t> ret = make_allocated_memory<wayland_context_t>();
  assert(ret);
  if (!ret) [[unlikely]] {
    return bongocat_error_t::BONGOCAT_ERROR_MEMORY;
  }

  // Initialize shared memory
  ret->thread_context.ctx_shm = make_allocated_mmap<wayland_shared_memory_t>();
  if (!ret->thread_context.ctx_shm) [[unlikely]] {
    return bongocat_error_t::BONGOCAT_ERROR_MEMORY;
  } else {
    static_assert(WAYLAND_NUM_BUFFERS <= INT_MAX);
    for (size_t i = 0; i < WAYLAND_NUM_BUFFERS; i++) {
      ret->thread_context.ctx_shm->buffers[i] = {};
    }
    atomic_store(&ret->thread_context.ctx_shm->configured, false);
  }

  // Initialize shared memory for local config
  ret->thread_context._local_copy_config = make_allocated_mmap<config::config_t>();
  if (!ret->thread_context._local_copy_config) [[unlikely]] {
    return bongocat_error_t::BONGOCAT_ERROR_MEMORY;
  }
  assert(ret->thread_context._local_copy_config);
  // Dummy config

  ret->_environ = ::environ;

  assert(ret->thread_context.ctx_shm);
  assert(ret->thread_context._local_copy_config);
  ret->thread_context.display = wl_display_connect(BONGOCAT_NULLPTR);
  if (ret->thread_context.display == BONGOCAT_NULLPTR) {
    return bongocat_error_t::BONGOCAT_ERROR_WAYLAND;
  }

  {
    assert(ret);
    bongocat_error_t result = details::wayland_setup_protocols(*ret);
    if (result != bongocat_error_t::BONGOCAT_SUCCESS) {
      return result;
    }
  }

  // NOTE: surface not needed, also fails because bar_height=0
  /*
  {
    assert(ret);
    bongocat_error_t result = details::wayland_setup_surface(*ret);
    if (result != bongocat_error_t::BONGOCAT_SUCCESS) {
      return result;
    }
  }
  */

  atomic_store(&ret->ready, false);

  // The second roundtrip delivers output and xdg-output events.
  if (wl_display_roundtrip(ret->thread_context.display) < 0) {
    return bongocat_error_t::BONGOCAT_ERROR_WAYLAND;
  }

  return ret;
}

int cli_list_monitors(const cli_list_monitors_args_t& args) {
  AllocatedMemory<wayland_context_t> ctx;
  {
    auto result = connect_display();
    if (result.error != bongocat_error_t::BONGOCAT_SUCCESS) {
      fprintf(stderr, "Wayland: cannot connect; check WAYLAND_DISPLAY and XDG_RUNTIME_DIR\n");
      return EXIT_FAILURE;
    }

    ctx = bongocat::move(result.result);
    if (ctx == BONGOCAT_NULLPTR) [[unlikely]] {
      return EXIT_FAILURE;
    }
  }

  assert(ctx);
  for (size_t i = 0; i < ctx->output_count && i < MAX_OUTPUTS; i++) {
    if (ctx->outputs[i].wl_output) {
      printf("%s: %dx%d scale=%d\n", ctx->outputs[i].name_str, ctx->outputs[i].width, ctx->outputs[i].height,
             ctx->outputs[i].wl_scale);
    }
  }
  const auto failure = !ctx->thread_context.compositor || !ctx->thread_context.shm || !ctx->thread_context.layer_shell;

  if (args.doctor) {
    assert(ctx);
    printf("Protocols: compositor-v4=%s shm=%s layer-shell=%s "
           "viewporter=%s fractional-scale=%s foreign-toplevel=%s\n",
           ctx->thread_context.compositor ? "yes" : "missing", ctx->thread_context.shm ? "yes" : "missing",
           ctx->thread_context.layer_shell ? "yes" : "missing", ctx->thread_context.viewporter ? "yes" : "no",
           ctx->thread_context.fractional_scale_mgr ? "yes" : "no", details::fullscreen_available(*ctx) ? "yes" : "no");
  }

  return !failure ? EXIT_SUCCESS : EXIT_FAILURE;
}

}  // namespace bongocat::platform::wayland
