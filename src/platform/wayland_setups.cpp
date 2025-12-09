#include "platform/wayland_setups.h"

#include "../graphics/bar.h"
#include "graphics/animation.h"
#include "platform/wayland-protocols.hpp"
#include "platform/wayland.h"
#include "platform/wayland_context.h"
#include "platform/wayland_shared_memory.h"
#include "utils/memory.h"
#include "wayland_hyprland.h"

#include <cassert>
#include <cerrno>
#include <climits>
#include <csignal>
#include <cstdio>
#include <cstdlib>
#include <fcntl.h>
#include <poll.h>
#include <pthread.h>
#include <sys/mman.h>
#include <sys/signalfd.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <wayland-client.h>
// #include "wayland_sway.h"
#include "platform/wayland_callbacks.h"

namespace bongocat::platform::wayland::details {
// =============================================================================
// GLOBAL STATE AND CONFIGURATION
// =============================================================================

static inline constexpr int CREATE_SHM_MAX_ATTEMPTS = 100;

static inline constexpr auto WAYLAND_LAYER_NAMESPACE = "bongocat-overlay";

static inline constexpr size_t CREATE_SHM_NAME_SUFFIX_LEN = 8;
static inline constexpr char CREATE_SHM_NAME_TEMPLATE[] = "/bongocat-bar-shm-XXXXXXXX";
static inline constexpr size_t CREATE_SHM_NAME_PREFIX_LEN =
    LEN_ARRAY(CREATE_SHM_NAME_TEMPLATE) - 1 - CREATE_SHM_NAME_SUFFIX_LEN;
static_assert((CREATE_SHM_NAME_PREFIX_LEN + CREATE_SHM_NAME_SUFFIX_LEN) == LEN_ARRAY(CREATE_SHM_NAME_TEMPLATE) - 1);

// =============================================================================
// BUFFER AND DRAWING MANAGEMENT
// =============================================================================

FileDescriptor create_shm(off_t size) {
  char *name = strdup(CREATE_SHM_NAME_TEMPLATE);
  constexpr char charset_arr[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
  constexpr size_t charset_len = sizeof(charset_arr) - 1;
  int fd = -1;

  random_xoshiro128 rng(slow_rand());
  for (int i = 0; i < CREATE_SHM_MAX_ATTEMPTS; i++) {
    for (size_t j = 0; j < CREATE_SHM_NAME_SUFFIX_LEN; j++) {
      assert(sizeof(charset_arr) - 1 > 0);
      name[CREATE_SHM_NAME_PREFIX_LEN + j] = charset_arr[rng.range(0, charset_len - 1)];
    }
    fd = shm_open(name, O_RDWR | O_CREAT | O_EXCL, 0600);
    if (fd >= 0) {
      shm_unlink(name);
      break;
    }
  }

  if (fd < 0 || ftruncate(fd, size) < 0) {
    close(fd);
    fd = -1;
    perror("shm");
  }

  ::free(name);
  return FileDescriptor(fd);
}

// =============================================================================
// MAIN WAYLAND INTERFACE IMPLEMENTATION
// =============================================================================

bongocat_error_t wayland_update_screen_width(wayland_context_t& ctx) {
  wayland_thread_context& wayland_ctx = ctx.thread_context;

  // read-only config
  assert(wayland_ctx._local_copy_config);
  const config::config_t& current_config = *wayland_ctx._local_copy_config;

  wayland_ctx.output = BONGOCAT_NULLPTR;
  wayland_ctx.bound_output_name = 0;
  wayland_ctx.using_named_output = false;
  if (current_config.output_name != BONGOCAT_NULLPTR) {
    for (size_t i = 0; i < ctx.output_count; ++i) {
      if (has_flag(ctx.outputs[i].received, output_ref_received_flags_t::Name) &&
          strcmp(ctx.outputs[i].name_str, current_config.output_name) == 0) {
        wayland_ctx.output = ctx.outputs[i].wl_output;
        wayland_ctx._output_name_str = ctx.outputs[i].name_str;
        wayland_ctx._screen_info = &ctx.screen_infos[i];
        wayland_ctx.bound_output_name = ctx.outputs[i].name;  // Store registry name for tracking
        wayland_ctx.using_named_output = true;                // User specified this output
        BONGOCAT_LOG_INFO("Matched output: %s", wayland_ctx._output_name_str);
        break;
      }
    }

    if (wayland_ctx.output == BONGOCAT_NULLPTR) {
      if (current_config._strict) {
        BONGOCAT_LOG_ERROR("Could not find output named '%s'", current_config.output_name);
        return bongocat_error_t::BONGOCAT_ERROR_INVALID_PARAM;
      } else {
        BONGOCAT_LOG_ERROR("Could not find output named '%s', defaulting to first output", current_config.output_name);
      }
    }
  }

  // Fallback
  if (wayland_ctx.output == BONGOCAT_NULLPTR && ctx.output_count > 0) {
    wayland_ctx.output = ctx.outputs[0].wl_output;
    wayland_ctx._output_name_str = ctx.outputs[0].name_str;
    wayland_ctx._screen_info = &ctx.screen_infos[0];
    wayland_ctx.bound_output_name = ctx.outputs[0].name;
    wayland_ctx.using_named_output = false;  // Using fallback, not a named output
    BONGOCAT_LOG_WARNING("Falling back to first output: %s", wayland_ctx._output_name_str);
  }

  if (wayland_ctx.compositor == BONGOCAT_NULLPTR || wayland_ctx.shm == BONGOCAT_NULLPTR ||
      wayland_ctx.layer_shell == BONGOCAT_NULLPTR) {
    BONGOCAT_LOG_ERROR("Missing required Wayland protocols");
    return bongocat_error_t::BONGOCAT_ERROR_WAYLAND;
  }

  // Configure screen dimensions
  int screen_width{DEFAULT_SCREEN_WIDTH};
  if (current_config.screen_width > 0) {
    BONGOCAT_LOG_WARNING("Use screen width from config: %d", current_config.screen_width);
    screen_width = current_config.screen_width;
  } else {
    // auto-detect screen width
    if (wayland_ctx.output != BONGOCAT_NULLPTR) {
      wl_display_roundtrip(wayland_ctx.display);
      if (wayland_ctx._screen_info != BONGOCAT_NULLPTR && wayland_ctx._screen_info->screen_width > 0) {
        BONGOCAT_LOG_INFO("Detected screen width: %d", wayland_ctx._screen_info->screen_width);
        screen_width = wayland_ctx._screen_info->screen_width;
      } else {
        BONGOCAT_LOG_WARNING("Using default screen width: %d", DEFAULT_SCREEN_WIDTH);
        screen_width = DEFAULT_SCREEN_WIDTH;
      }
    } else {
      BONGOCAT_LOG_WARNING("No output found, using default screen width: %d", DEFAULT_SCREEN_WIDTH);
      screen_width = DEFAULT_SCREEN_WIDTH;
      if (current_config._strict) {
        return bongocat_error_t::BONGOCAT_ERROR_INVALID_PARAM;
      }
    }
  }
  wayland_ctx._screen_width = screen_width;

  return bongocat_error_t::BONGOCAT_SUCCESS;
}
bongocat_error_t wayland_setup_protocols(wayland_context_t& ctx) {
  wayland_thread_context& wayland_ctx = ctx.thread_context;
  // animation_context_t& anim = *ctx.animation_context;
  // animation_trigger_context_t& trigger_ctx = *ctx.animation_trigger_context;

  // read-only config
  // assert(wayland_ctx._local_copy_config != nullptr);
  // const config::config_t& current_config = *wayland_ctx._local_copy_config;

  /// @TODO: add RAII wrapper for wl_registry
  wl_registry *registry = wl_display_get_registry(wayland_ctx.display);
  if (registry == BONGOCAT_NULLPTR) {
    BONGOCAT_LOG_ERROR("Failed to get Wayland registry");
    return bongocat_error_t::BONGOCAT_ERROR_WAYLAND;
  }

  wl_registry_add_listener(registry, &details::reg_listener, &ctx);
  wl_display_roundtrip(wayland_ctx.display);

  if (ctx.xdg_output_manager != BONGOCAT_NULLPTR) {
    for (size_t i = 0; i < ctx.output_count && i < MAX_OUTPUTS; i++) {
      ctx.outputs[i].wayland = &ctx;
      ctx.outputs[i].xdg_output =
          zxdg_output_manager_v1_get_xdg_output(ctx.xdg_output_manager, ctx.outputs[i].wl_output);
      zxdg_output_v1_add_listener(ctx.outputs[i].xdg_output, &details::xdg_output_listener, &ctx.outputs[i]);
      ctx.screen_infos[i] = {};
      assert(ctx.outputs[i].wl_output);
      ctx.screen_infos[i].wl_output = ctx.outputs[i].wl_output;
    }

    // Wait for all xdg_output events
    wl_display_roundtrip(wayland_ctx.display);  // Process initial events
    wl_display_roundtrip(wayland_ctx.display);  // Ensure all `done` events arrive
    BONGOCAT_LOG_DEBUG("Listener bound for xdg_output and foreign toplevel handle");

    // DE specific inits
    hyprland::update_outputs_with_monitor_ids(ctx);
  }

  if (wayland_ctx.compositor == BONGOCAT_NULLPTR || wayland_ctx.shm == BONGOCAT_NULLPTR ||
      wayland_ctx.layer_shell == BONGOCAT_NULLPTR) {
    BONGOCAT_LOG_ERROR("Missing required Wayland protocols");
    wl_registry_destroy(registry);
    return bongocat_error_t::BONGOCAT_ERROR_WAYLAND;
  }

  const bongocat_error_t result_update_screen_width = wayland_update_screen_width(ctx);
  if (result_update_screen_width != bongocat_error_t::BONGOCAT_SUCCESS) {
    wl_registry_destroy(registry);
    return result_update_screen_width;
  }

  // move new registry
  if (wayland_ctx.registry != BONGOCAT_NULLPTR) {
    wl_registry_destroy(wayland_ctx.registry);
  }
  wayland_ctx.registry = registry;
  registry = BONGOCAT_NULLPTR;

  for (size_t i = 0; i < ctx.output_count && i < MAX_OUTPUTS; i++) {
    ctx.outputs[i].wayland = &ctx;
  }

  return bongocat_error_t::BONGOCAT_SUCCESS;
}

bongocat_error_t wayland_setup_surface(wayland_context_t& ctx) {
  wayland_thread_context& wayland_ctx = ctx.thread_context;
  // animation_context_t& anim = *ctx.animation_context;
  // animation_trigger_context_t& trigger_ctx = *ctx.animation_trigger_context;

  // read-only config
  assert(wayland_ctx._local_copy_config);
  const config::config_t& current_config = *wayland_ctx._local_copy_config;

  wayland_ctx.surface = wl_compositor_create_surface(wayland_ctx.compositor);
  if (wayland_ctx.surface == BONGOCAT_NULLPTR) {
    BONGOCAT_LOG_ERROR("Failed to create surface");
    return bongocat_error_t::BONGOCAT_ERROR_WAYLAND;
  }

  zwlr_layer_shell_v1_layer layer = ZWLR_LAYER_SHELL_V1_LAYER_OVERLAY;
  switch (current_config.layer) {
  case config::layer_type_t::LAYER_BACKGROUND:
    layer = ZWLR_LAYER_SHELL_V1_LAYER_BACKGROUND;
    break;
  case config::layer_type_t::LAYER_BOTTOM:
    layer = ZWLR_LAYER_SHELL_V1_LAYER_BOTTOM;
    break;
  case config::layer_type_t::LAYER_TOP:
    layer = ZWLR_LAYER_SHELL_V1_LAYER_TOP;
    break;
  case config::layer_type_t::LAYER_OVERLAY:
    layer = ZWLR_LAYER_SHELL_V1_LAYER_OVERLAY;
    break;
  }
  wayland_ctx.layer_surface = zwlr_layer_shell_v1_get_layer_surface(wayland_ctx.layer_shell, wayland_ctx.surface,
                                                                    wayland_ctx.output, layer, WAYLAND_LAYER_NAMESPACE);
  if (wayland_ctx.layer_surface == BONGOCAT_NULLPTR) {
    BONGOCAT_LOG_ERROR("Failed to create layer surface");
    return bongocat_error_t::BONGOCAT_ERROR_WAYLAND;
  }

  // Configure layer surface
  uint32_t anchor = ZWLR_LAYER_SURFACE_V1_ANCHOR_LEFT | ZWLR_LAYER_SURFACE_V1_ANCHOR_RIGHT;
  switch (current_config.overlay_position) {
  case config::overlay_position_t::POSITION_TOP:
    anchor |= ZWLR_LAYER_SURFACE_V1_ANCHOR_TOP;
    break;
  case config::overlay_position_t::POSITION_BOTTOM:
    anchor |= ZWLR_LAYER_SURFACE_V1_ANCHOR_BOTTOM;
    break;
  default:
    BONGOCAT_LOG_ERROR("Invalid overlay_position %d for layer surface, set to top (default)");
    anchor |= ZWLR_LAYER_SURFACE_V1_ANCHOR_TOP;
    break;
  }

  assert(wayland_ctx._bar_height >= 0);
  // assert(current_config.bar_height <= UINT32_MAX);
  if (wayland_ctx._bar_height == 0) {
    BONGOCAT_LOG_ERROR("Can not set anchor with bar_height=0");
    zwlr_layer_surface_v1_destroy(wayland_ctx.layer_surface);
    return bongocat_error_t::BONGOCAT_ERROR_WAYLAND;
  }
  zwlr_layer_surface_v1_set_anchor(wayland_ctx.layer_surface, anchor);
  zwlr_layer_surface_v1_set_size(wayland_ctx.layer_surface, 0, static_cast<uint32_t>(wayland_ctx._bar_height));
  zwlr_layer_surface_v1_set_exclusive_zone(wayland_ctx.layer_surface, -1);
  zwlr_layer_surface_v1_set_keyboard_interactivity(wayland_ctx.layer_surface,
                                                   ZWLR_LAYER_SURFACE_V1_KEYBOARD_INTERACTIVITY_NONE);
  zwlr_layer_surface_v1_add_listener(wayland_ctx.layer_surface, &details::layer_listener, &ctx);

  // Make surface click-through
  wl_region *input_region = wl_compositor_create_region(wayland_ctx.compositor);
  if (input_region != BONGOCAT_NULLPTR) {
    wl_surface_set_input_region(wayland_ctx.surface, input_region);
    wl_region_destroy(input_region);
    input_region = BONGOCAT_NULLPTR;
  }

  wl_surface_commit(wayland_ctx.surface);
  if constexpr (WAYLAND_NUM_BUFFERS == 1) {
    wl_display_roundtrip(wayland_ctx.display);
  }
  return bongocat_error_t::BONGOCAT_SUCCESS;
}

bongocat_error_t wayland_setup_buffer(wayland_thread_context& wayland_context,
                                      animation::animation_context_t& animation_ctx) {
  // read-only config
  assert(wayland_context._local_copy_config);
  // const config::config_t& current_config = *wayland_context._local_copy_config;

  wayland_shared_memory_t& wayland_ctx_shm = *wayland_context.ctx_shm;

  /// @TODO: limit screen_width and bar_height for buffer_size
  const int32_t buffer_width = wayland_context._screen_width;
  const int32_t buffer_height = wayland_context._bar_height;
  assert(buffer_width >= 0);
  assert(buffer_height >= 0);
  assert(RGBA_CHANNELS >= 0);
  const size_t buffer_size = static_cast<size_t>(buffer_width) * static_cast<size_t>(buffer_height) * RGBA_CHANNELS;
  if (buffer_size <= 0) {
    BONGOCAT_LOG_ERROR("Invalid buffer size: %d", buffer_size);
    return bongocat_error_t::BONGOCAT_ERROR_WAYLAND;
  }

  static_assert(WAYLAND_NUM_BUFFERS > 0);
  static_assert(WAYLAND_NUM_BUFFERS <= INT32_MAX);
  if (buffer_size > INT32_MAX / static_cast<int32_t>(WAYLAND_NUM_BUFFERS)) {
    BONGOCAT_LOG_ERROR("Buffer size too large for SHM pool offset");
    return bongocat_error_t::BONGOCAT_ERROR_WAYLAND;
  }
  assert(buffer_size <= INT32_MAX / static_cast<int32_t>(WAYLAND_NUM_BUFFERS));
  const size_t total_size = buffer_size * WAYLAND_NUM_BUFFERS;

  assert(total_size <= INT32_MAX);
  FileDescriptor fd = create_shm(static_cast<off_t>(total_size));
  if (fd._fd < 0) {
    return bongocat_error_t::BONGOCAT_ERROR_FILE_IO;
  }

  wl_shm_pool *pool = wl_shm_create_pool(wayland_context.shm, fd._fd, static_cast<int32_t>(total_size));
  if (pool == BONGOCAT_NULLPTR) {
    BONGOCAT_LOG_ERROR("Failed to create shared memory pool");
    return bongocat_error_t::BONGOCAT_ERROR_WAYLAND;
  }

  static_assert(WAYLAND_NUM_BUFFERS > 0);
  static_assert(WAYLAND_NUM_BUFFERS <= INT32_MAX);
  for (size_t i = 0; i < WAYLAND_NUM_BUFFERS; i++) {
    // assert(buffer_size >= 0);
    assert(i <= INT32_MAX);
    assert(buffer_size <= INT32_MAX);
    assert(buffer_size <= static_cast<size_t>(INT32_MAX));
    assert(buffer_size <= static_cast<size_t>(INT32_MAX) / WAYLAND_NUM_BUFFERS);
    const off_t offset = static_cast<off_t>(i) * static_cast<off_t>(buffer_size);

    assert(static_cast<size_t>(buffer_size) <= SIZE_MAX);
    wayland_ctx_shm.buffers[i].pixels = make_allocated_mmap_file_buffer_value<uint8_t>(0, buffer_size, fd._fd, offset);
    if (!wayland_ctx_shm.buffers[i].pixels) {
      BONGOCAT_LOG_ERROR("Failed to map shared memory: %s", strerror(errno));
      for (size_t j = 0; j < i; j++) {
        cleanup_shm_buffer(wayland_ctx_shm.buffers[j]);
      }
      wl_shm_pool_destroy(pool);
      return bongocat_error_t::BONGOCAT_ERROR_MEMORY;
    }

    // assert(buffer_size >= 0);
    assert(i <= INT32_MAX);
    assert(buffer_size <= INT32_MAX);
    assert(offset <= INT32_MAX);
    wayland_ctx_shm.buffers[i].buffer = wl_shm_pool_create_buffer(
        pool, static_cast<int32_t>(offset), wayland_context._screen_width, wayland_context._bar_height,
        wayland_context._screen_width * RGBA_CHANNELS, WL_SHM_FORMAT_ARGB8888);
    if (wayland_ctx_shm.buffers[i].buffer == BONGOCAT_NULLPTR) {
      BONGOCAT_LOG_ERROR("Failed to create buffer");
      for (size_t j = 0; j < i; j++) {
        cleanup_shm_buffer(wayland_ctx_shm.buffers[j]);
      }
      wl_shm_pool_destroy(pool);
      return bongocat_error_t::BONGOCAT_ERROR_WAYLAND;
    }

    // created buffer successfully, set other properties
    assert(i <= INT_MAX);
    wayland_ctx_shm.buffers[i].index = i;
    atomic_store(&wayland_ctx_shm.buffers[i].busy, false);
    atomic_store(&wayland_ctx_shm.buffers[i].pending, false);
    wayland_ctx_shm.buffers[i]._animation_context = &animation_ctx;
    wayland_ctx_shm.buffers[i]._wayland_thread_context = &wayland_context;
    wl_buffer_add_listener(wayland_ctx_shm.buffers[i].buffer, &details::buffer_listener, &wayland_ctx_shm.buffers[i]);
  }

  wl_shm_pool_destroy(pool);

  wayland_ctx_shm.current_buffer_index = 0;

  return bongocat_error_t::BONGOCAT_SUCCESS;
}
}  // namespace bongocat::platform::wayland::details
