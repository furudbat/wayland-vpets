#include "platform/wayland_setups.h"

#include "graphics/animation.h"
#include "platform/wayland-protocols.hpp"
#include "platform/wayland.h"
#include "platform/wayland_context.h"
#include "platform/wayland_shared_memory.h"
#include "utils/memory.h"
#include "wayland_hyprland.h"

#include <cassert>
#include <cerrno>
#include <cstdlib>
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

int phys_dim(const wayland_thread_context& ctx, int logical) {
  if (logical <= 0) {
    return 0;
  }

  if (ctx._preferred_scale <= 0) {
    return logical;
  }

  assert(ctx._preferred_scale <= INT_MAX);
  return animation::details::phys_dim({
      .logical = logical,
      .scale120 = static_cast<int>(ctx._preferred_scale),
  });
}

// =============================================================================
// BUFFER AND DRAWING MANAGEMENT
// =============================================================================

created_result_t<FileDescriptor> create_shm(off_t size) {
  auto name = duplicate_string(CREATE_SHM_NAME_TEMPLATE);
  constexpr char charset_arr[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
  constexpr size_t charset_len = sizeof(charset_arr) - 1;
  int fd = -1;

  random_xoshiro128 rng(slow_rand());
  for (int i = 0; i < CREATE_SHM_MAX_ATTEMPTS; i++) {
    for (size_t j = 0; j < CREATE_SHM_NAME_SUFFIX_LEN; j++) {
      static_assert(sizeof(charset_arr) - 1 > 0);
      assert(CREATE_SHM_NAME_PREFIX_LEN + j < name.capacity());
      name.ptr[CREATE_SHM_NAME_PREFIX_LEN + j] = charset_arr[rng.range(0, charset_len - 1)];
    }
    fd = shm_open(name.c_str(), O_RDWR | O_CREAT | O_EXCL, 0600);
    if (fd >= 0) {
      shm_unlink(name.c_str());
      break;
    }
  }

  if (fd < 0 || ftruncate(fd, size) < 0) {
    close(fd);
    fd = -1;
    return bongocat_error_t::BONGOCAT_ERROR_FILE_IO;
  }

  return FileDescriptor(fd);
}

// =============================================================================
// MAIN WAYLAND INTERFACE IMPLEMENTATION
// =============================================================================

bongocat_error_t wayland_update_output(wayland_context_t& ctx) {
  wayland_thread_context& wayland_ctx = ctx.thread_context;

  // read-only config
  assert(wayland_ctx._local_copy_config);
  const config::config_t& current_config = *wayland_ctx._local_copy_config;

  wayland_ctx.output = BONGOCAT_NULLPTR;
  wayland_ctx.bound_output_name = 0;
  wayland_ctx.using_named_output = false;
  wayland_ctx._output_name_str = BONGOCAT_NULLPTR;

  if (current_config.output_name) {
    for (size_t i = 0; i < ctx.output_count; ++i) {
      if (has_flag(ctx.outputs[i].received, output_ref_received_flags_t::Name) &&
          strcmp(ctx.outputs[i].name_str, current_config.output_name.c_str()) == 0) {
        wayland_ctx.output = ctx.outputs[i].wl_output;
        wayland_ctx._output_name_str = ctx.outputs[i].name_str;
        wayland_ctx._screen_info = &ctx.screen_infos[i];
        wayland_ctx.bound_output_name = ctx.outputs[i].name;  // Store registry name for tracking
        wayland_ctx.using_named_output = true;                // User specified this output

        BONGOCAT_LOG_INFO("Matched output: %s (registry name %u, %s)", ctx.outputs[i].name_str,
                          wayland_ctx.bound_output_name, wayland_ctx._output_name_str);
        break;
      }
    }

    if (wayland_ctx.output == BONGOCAT_NULLPTR) {
      if (current_config._strict) {
        BONGOCAT_LOG_ERROR("Could not find output named '%s'", current_config.output_name.c_str());
        return bongocat_error_t::BONGOCAT_ERROR_INVALID_PARAM;
      } else {
        BONGOCAT_LOG_ERROR("Could not find output named '%s', defaulting to first output",
                           current_config.output_name.c_str());
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

    BONGOCAT_LOG_WARNING("Falling back to first output (registry name %u, %s)", wayland_ctx.bound_output_name,
                         wayland_ctx._output_name_str);
  }

  return bongocat_error_t::BONGOCAT_SUCCESS;
}
created_result_t<int> wayland_update_current_output_info(wayland_context_t& ctx) {
  wayland_thread_context& wayland_ctx = ctx.thread_context;

  // read-only config
  assert(wayland_ctx._local_copy_config);
  const config::config_t& current_config = *wayland_ctx._local_copy_config;

  // auto-detect screen width
  bool output_found = false;
  int screen_width{DEFAULT_SCREEN_WIDTH};
  char *bound_screen_name{BONGOCAT_NULLPTR};
  screen_info_t *screen_info{BONGOCAT_NULLPTR};
  if (wayland_ctx.output != BONGOCAT_NULLPTR) {
    wl_display_roundtrip(wayland_ctx.display);
    // update screen_infos

    for (size_t i = 0; i < ctx.output_count && i < MAX_OUTPUTS; i++) {
      if (ctx.screen_infos[i].wl_output == ctx.thread_context.output) {
        BONGOCAT_LOG_INFO("Detected screen name: %s", ctx.outputs[i].name_str);
        bound_screen_name = ctx.outputs[i].name_str;

        if (ctx.screen_infos[i].logical_width > 0 && ctx.screen_infos[i].logical_width <= INT16_MAX) {
          BONGOCAT_LOG_INFO("Detected screen width: %d", ctx.screen_infos[i].logical_width);
          screen_info = &ctx.screen_infos[i];
          screen_width = ctx.screen_infos[i].logical_width;
          output_found = true;
        }
      }
    }
  } else {
    screen_width = DEFAULT_SCREEN_WIDTH;
    if (current_config._strict) {
      return bongocat_error_t::BONGOCAT_ERROR_INVALID_PARAM;
    }
    output_found = false;
  }

  if (output_found) {
    // assert(screen_width > 0);
    ctx.thread_context._output_name_str = bound_screen_name;
    ctx.thread_context._screen_info = screen_info;
    ctx.thread_context._screen_width = screen_width;
  } else {
    BONGOCAT_LOG_WARNING("No output found, using default screen width: %d", DEFAULT_SCREEN_WIDTH);
  }

  return screen_width;
}
bongocat_error_t wayland_update_screen_info(wayland_context_t& ctx, wayland_update_screen_info_options_t options) {
  wayland_thread_context& wayland_ctx = ctx.thread_context;

  // read-only config
  assert(wayland_ctx._local_copy_config);
  const config::config_t& current_config = *wayland_ctx._local_copy_config;

  wayland_update_output(ctx);

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
      if (!options.skip_display_events) {
        wl_display_roundtrip(wayland_ctx.display);
      }
      if (wayland_ctx._screen_info != BONGOCAT_NULLPTR && wayland_ctx._screen_info->logical_width > 0 &&
          wayland_ctx._screen_info->logical_width < INT16_MAX) {
        BONGOCAT_LOG_INFO("Detected screen width: %d", wayland_ctx._screen_info->logical_width);
        screen_width = wayland_ctx._screen_info->logical_width;
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
      ctx.screen_infos[i] = {};
      ctx.screen_infos[i].wl_output = ctx.outputs[i].wl_output;
      zxdg_output_v1_add_listener(ctx.outputs[i].xdg_output, &details::xdg_output_listener, &ctx.outputs[i]);

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

  wayland_update_output(ctx);

  if (wayland_ctx.compositor == BONGOCAT_NULLPTR || wayland_ctx.shm == BONGOCAT_NULLPTR ||
      wayland_ctx.layer_shell == BONGOCAT_NULLPTR) {
    if (wayland_ctx.compositor == BONGOCAT_NULLPTR) {
      BONGOCAT_LOG_ERROR("Missing protocol: wl_compositor");
    }
    if (wayland_ctx.shm == BONGOCAT_NULLPTR) {
      BONGOCAT_LOG_ERROR("Missing protocol: wl_shm");
    }
    if (wayland_ctx.layer_shell == BONGOCAT_NULLPTR) {
      BONGOCAT_LOG_ERROR("Missing protocol: wlr-layer-shell (required for "
                         "overlay rendering). Your compositor may not support "
                         "this protocol.");
    }
    BONGOCAT_LOG_ERROR("Missing required Wayland protocols");

    wl_registry_destroy(registry);
    return bongocat_error_t::BONGOCAT_ERROR_WAYLAND;
  }

  // Warn about optional protocols
  if (!fs_detector_available(ctx)) {
    BONGOCAT_LOG_WARNING("Foreign toplevel protocol not available - fullscreen "
                         "detection disabled. Overlay will not auto-hide when "
                         "apps go fullscreen.");
  }

  // Configure screen dimensions
  wayland_update_current_output_info(ctx);
  auto [result_update_screen_width, result_update_screen_width_error] =
      wayland_update_current_output_info(ctx);  // wayland_update_screen_info(ctx);
  if (result_update_screen_width_error != bongocat_error_t::BONGOCAT_SUCCESS) {
    wl_registry_destroy(registry);
    return result_update_screen_width_error;
  }

  // Keep registry alive for output reconnection handling
  // move new registry
  if (wayland_ctx.registry != BONGOCAT_NULLPTR) {
    // destroy old registry
    wl_registry_destroy(wayland_ctx.registry);
  }
  wayland_ctx.registry = registry;
  registry = BONGOCAT_NULLPTR;

  for (size_t i = 0; i < ctx.output_count && i < MAX_OUTPUTS; i++) {
    ctx.outputs[i].wayland = &ctx;
  }

  return bongocat_error_t::BONGOCAT_SUCCESS;
}

zwlr_layer_shell_v1_layer wayland_apply_layer_properties_v1(wayland_context_t& ctx) {
  wayland_thread_context& wayland_ctx = ctx.thread_context;
  // animation_context_t& anim = *ctx.animation_context;
  // animation_trigger_context_t& trigger_ctx = *ctx.animation_trigger_context;

  // read-only config
  assert(wayland_ctx._local_copy_config);
  const config::config_t& current_config = *wayland_ctx._local_copy_config;

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

  if (wayland_ctx.layer_surface != BONGOCAT_NULLPTR) {
    assert(wayland_ctx.layer_shell_version >= 2);
    zwlr_layer_surface_v1_set_layer(wayland_ctx.layer_surface, layer);
    BONGOCAT_LOG_INFO("Layer changed to %i", layer);
  }

  return layer;
}
uint32_t wayland_apply_anchor_properties_v1(wayland_context_t& ctx) {
  wayland_thread_context& wayland_ctx = ctx.thread_context;
  // animation_context_t& anim = *ctx.animation_context;
  // animation_trigger_context_t& trigger_ctx = *ctx.animation_trigger_context;

  // read-only config
  assert(wayland_ctx._local_copy_config);
  const config::config_t& current_config = *wayland_ctx._local_copy_config;

  uint32_t anchor = ZWLR_LAYER_SURFACE_V1_ANCHOR_LEFT | ZWLR_LAYER_SURFACE_V1_ANCHOR_RIGHT;
  switch (current_config.overlay_position) {
  case config::overlay_position_t::POSITION_TOP:
    anchor |= ZWLR_LAYER_SURFACE_V1_ANCHOR_TOP;
    break;
  case config::overlay_position_t::POSITION_BOTTOM:
    anchor |= ZWLR_LAYER_SURFACE_V1_ANCHOR_BOTTOM;
    break;
  default:
    BONGOCAT_LOG_ERROR("Invalid overlay_position %d for layer surface, set to top (default)",
                       static_cast<int>(current_config.overlay_position));
    anchor |= ZWLR_LAYER_SURFACE_V1_ANCHOR_TOP;
    break;
  }

  if (wayland_ctx.layer_surface != BONGOCAT_NULLPTR) {
    zwlr_layer_surface_v1_set_anchor(wayland_ctx.layer_surface, anchor);
    BONGOCAT_LOG_INFO("Overlay position changed to %u", anchor);
  }

  return anchor;
}

// Pick effective scale_120 from output's wl_output::scale when fractional
// protocol is unavailable.
static uint32_t scale_120_from_output(const wayland_context_t& ctx) {
  for (size_t i = 0; i < ctx.output_count && i < MAX_OUTPUTS; i++) {
    if (ctx.screen_infos[i].wl_output == ctx.thread_context.output) {
      if (ctx.screen_infos[i].scale > 0) {
        return static_cast<uint32_t>(ctx.screen_infos[i].scale) * 120u;
      }
    }
  }

  return 120;
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

  // HiDPI plumbing: pair surface with a viewport (so we can render at
  // physical-pixel resolution and let compositor downscale to the logical
  // size) and a fractional-scale receiver (so we learn the preferred scale).
  if (wayland_ctx.viewporter != BONGOCAT_NULLPTR && wayland_ctx._viewport == BONGOCAT_NULLPTR) {
    wayland_ctx._viewport = wp_viewporter_get_viewport(wayland_ctx.viewporter, wayland_ctx.surface);
  }
  if (wayland_ctx.fractional_scale_mgr != BONGOCAT_NULLPTR && wayland_ctx._fractional_scale_obj == BONGOCAT_NULLPTR) {
    wayland_ctx._fractional_scale_obj =
        wp_fractional_scale_manager_v1_get_fractional_scale(wayland_ctx.fractional_scale_mgr, wayland_ctx.surface);
    if (wayland_ctx._fractional_scale_obj != BONGOCAT_NULLPTR) {
      wp_fractional_scale_v1_add_listener(wayland_ctx._fractional_scale_obj, &fractional_scale_listener, &ctx);
      BONGOCAT_LOG_VERBOSE("wayland_setup_surface: get fractional scale by fractional_scale_listener");
    }
  }

  // If fractional protocol is unavailable, seed scale from wl_output integer
  // scale so the first buffer is sized correctly.
  if (wayland_ctx._fractional_scale_obj == BONGOCAT_NULLPTR) {
    wayland_ctx._preferred_scale = scale_120_from_output(ctx);
    BONGOCAT_LOG_VERBOSE("wayland_setup_surface: fractional protocol is unavailable, fallback: %d",
                         wayland_ctx._preferred_scale);
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
  assert(wayland_ctx._overlay_height >= 0);
  // assert(current_config.bar_height <= UINT32_MAX);
  if (wayland_ctx._overlay_height == 0) {
    BONGOCAT_LOG_ERROR("Can not set anchor with bar_height=0");
    zwlr_layer_surface_v1_destroy(wayland_ctx.layer_surface);
    return bongocat_error_t::BONGOCAT_ERROR_WAYLAND;
  }
  wayland_apply_anchor_properties_v1(ctx);
  zwlr_layer_surface_v1_set_size(wayland_ctx.layer_surface, 0, static_cast<uint32_t>(wayland_ctx._overlay_height));
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

created_result_t<wayland_setup_buffer_result_t> wayland_setup_buffer(wayland_thread_context& wayland_context,
                                                                     animation::animation_context_t& animation_ctx) {
  // read-only config
  assert(wayland_context._local_copy_config);
  // const config::config_t& current_config = *wayland_context._local_copy_config;

  wayland_shared_memory_t& wayland_ctx_shm = *wayland_context.ctx_shm;

  const int logical_w = wayland_context._screen_width;
  const int logical_h = wayland_context._overlay_height;
  const int phys_w = details::phys_dim(wayland_context, logical_w);
  const int phys_h = details::phys_dim(wayland_context, logical_h);
  assert(phys_w <= INT32_MAX);
  assert(phys_h <= INT32_MAX);
  /// @TODO: limit screen_width and bar_height for buffer_size
  const int32_t buffer_width = phys_w;
  const int32_t buffer_height = phys_h;
  assert(buffer_width >= 0);
  assert(buffer_height >= 0);
  static_assert(RGBA_CHANNELS >= 0);
  const size_t buffer_size = static_cast<size_t>(buffer_width) * static_cast<size_t>(buffer_height) * RGBA_CHANNELS;
  if (buffer_size <= 0) {
    BONGOCAT_LOG_ERROR("Invalid buffer size: %zu", buffer_size);
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

  FileDescriptor fd;
  {
    assert(total_size <= INT32_MAX);
    auto [fd_shm, fd_shm_error] = create_shm(static_cast<off_t>(total_size));
    if (fd_shm_error != bongocat_error_t::BONGOCAT_SUCCESS) {
      return fd_shm_error;
    }
    fd = bongocat::move(fd_shm);
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
    wayland_ctx_shm.buffers[i].buffer = wl_shm_pool_create_buffer(pool, static_cast<int32_t>(offset), phys_w, phys_h,
                                                                  phys_w * RGBA_CHANNELS, WL_SHM_FORMAT_ARGB8888);
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
    wayland_ctx_shm.buffers[i]._physical_buffer_width = phys_w;
    wayland_ctx_shm.buffers[i]._physical_buffer_height = phys_h;
    wl_buffer_add_listener(wayland_ctx_shm.buffers[i].buffer, &details::buffer_listener, &wayland_ctx_shm.buffers[i]);
  }

  wl_shm_pool_destroy(pool);

  wayland_ctx_shm.current_buffer_index = 0;

  if (wayland_context.surface != BONGOCAT_NULLPTR) {
    int integer_scale = static_cast<int>((wayland_context._preferred_scale + 119u) / 120u);
    if (integer_scale < 1) {
      integer_scale = 1;
    }
    wl_surface_set_buffer_scale(wayland_context.surface, integer_scale);
  }
  if (wayland_context._viewport != BONGOCAT_NULLPTR) {
    wp_viewport_set_destination(wayland_context._viewport, logical_w, logical_h);
  }

  BONGOCAT_LOG_VERBOSE("Buffer allocated: logical %dx%d, physical %dx%d, scale %u/120", logical_w, logical_h, phys_w,
                       phys_h, wayland_context._preferred_scale);

  return wayland_setup_buffer_result_t{
      .logical_w = logical_w,
      .logical_h = logical_h,
      .phys_w = phys_w,
      .phys_h = phys_h,
  };
}

spawn_pipe_t safe_popen_read_spawn(wayland_context_t& ctx, const char *path, const char *const *argv) {
  int pipefd[2] = {-1, -1};
  spawn_pipe_t result;

  if (pipe(pipefd) != 0) {
    return result;
  }

  posix_spawn_file_actions_t actions;
  posix_spawn_file_actions_init(&actions);

  // Redirect stdout -> pipe
  posix_spawn_file_actions_adddup2(&actions, pipefd[1], STDOUT_FILENO);

  // Redirect stderr -> /dev/null
  int devnull_fd = open("/dev/null", O_WRONLY);
  if (devnull_fd >= 0) {
    posix_spawn_file_actions_adddup2(&actions, devnull_fd, STDERR_FILENO);
  }

  posix_spawn_file_actions_addclose(&actions, pipefd[0]);

  pid_t pid{-1};
  // @NOTE: safe-const cast for argv
  if (posix_spawn(&pid, path, &actions, BONGOCAT_NULLPTR, const_cast<char *const *>(argv), ctx._environ) != 0) {
    close(pipefd[0]);
    close(pipefd[1]);
    // pipefd[0] = -1;
    // pipefd[1] = -1;
    posix_spawn_file_actions_destroy(&actions);
    return result;
  }

  posix_spawn_file_actions_destroy(&actions);
  close(pipefd[1]);
  // pipefd[1] = -1;

  result.fp = fdopen(pipefd[0], "r");
  result.pid = pid;
  return result;
}
int safe_pclose_spawn(spawn_pipe_t& sp) {
  int status = 0;
  if (sp.fp) {
    fclose(sp.fp);
    sp.fp = BONGOCAT_NULLPTR;
  }

  if (sp.pid > 0) {
    waitpid(sp.pid, &status, 0);
  }

  return status;
}

bool fs_detector_available(wayland_context_t& ctx) {
  return ctx.fs_detector.manager != BONGOCAT_NULLPTR;
}

}  // namespace bongocat::platform::wayland::details
