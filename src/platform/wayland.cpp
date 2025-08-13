#define _POSIX_C_SOURCE 200809L
#include "graphics/animation.h"
#include "platform/wayland.h"
#include "platform/wayland_shared_memory.h"
#include "platform/global_wayland_context.h"
#include "utils/memory.h"
#include "../graphics/bar.h"
#include "../protocols/wlr-foreign-toplevel-management-v1-client-protocol.h"
#include "../protocols/xdg-output-unstable-v1-client-protocol.h"
#include <cassert>
#include <poll.h>
#include <unistd.h>
#include <fcntl.h>
#include <cerrno>
#include <climits>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <pthread.h>
#include <linux/input.h>
#include <csignal>
#include <cstdlib>
#include <wayland-client.h>
#include <sys/signalfd.h>
#include <sys/wait.h>

#ifdef __cplusplus
#define wl_array_for_each_typed(pos, array, type) \
for (type *pos = static_cast<type*>((array)->data); \
reinterpret_cast<const char*>(pos) < \
(reinterpret_cast<const char*>((array)->data) + (array)->size); \
++pos)
#endif

// =============================================================================
// GLOBAL STATE AND CONFIGURATION
// =============================================================================

static inline constexpr size_t LINE_BUF = 512;
static inline constexpr size_t SWAY_BUF = 4096;

static inline constexpr int CREATE_SHM_MAX_ATTEMPTS     = 100;
static inline constexpr time_ms_t CHECK_INTERVAL_MS     = 100;
static inline constexpr time_ms_t POOL_MIN_TIMEOUT_MS   = 5;
static inline constexpr time_ms_t POOL_MAX_TIMEOUT_MS   = 1000;
static inline constexpr int MAX_ATTEMPTS                = 2048;

static_assert(POOL_MAX_TIMEOUT_MS >= POOL_MIN_TIMEOUT_MS);

static inline constexpr auto WAYLAND_LAYER_NAME = "OVERLAY";


// =============================================================================
// ZXDG LISTENER IMPLEMENTATION
// =============================================================================

static void handle_xdg_output_name(void *data, struct zxdg_output_v1 *xdg_output,
                                   const char *name) {
    UNUSED(xdg_output);

    output_ref_t *oref = (output_ref_t *)data;
    assert(oref);

    snprintf(oref->name_str, sizeof(oref->name_str), "%s", name);
    oref->name_received = true;
    BONGOCAT_LOG_DEBUG("xdg_output.name: xdg-output name received: %s", name);
}

static void handle_xdg_output_logical_position(void *data, struct zxdg_output_v1 *xdg_output,
                                               int32_t x, int32_t y) {
    UNUSED(xdg_output); UNUSED(x); UNUSED(y);

    output_ref_t *oref = (output_ref_t *)data;
    assert(oref);

    BONGOCAT_LOG_VERBOSE("xdg_output.logical_position: %d,%d received", x, y);
}
static void handle_xdg_output_logical_size(void *data, struct zxdg_output_v1 *xdg_output,
                                           int32_t width, int32_t height) {
    UNUSED(xdg_output); UNUSED(width); UNUSED(height);

    output_ref_t *oref = (output_ref_t *)data;
    assert(oref);

    BONGOCAT_LOG_VERBOSE("xdg_output.logical_size: %dx%d received", width, height);
}
static void handle_xdg_output_done(void *data, struct zxdg_output_v1 *xdg_output) {
    UNUSED(xdg_output);

    output_ref_t *oref = (output_ref_t *)data;
    assert(oref);

    BONGOCAT_LOG_VERBOSE("xdg_output.done: done received");
}

static void handle_xdg_output_description(void *data, struct zxdg_output_v1 *xdg_output, const char *description) {
    UNUSED(xdg_output); UNUSED(description);

    output_ref_t *oref = (output_ref_t *)data;
    assert(oref);

    BONGOCAT_LOG_VERBOSE("xdg_output.description: description received");
}

/// @NOTE: xdg_output_listeners MUST pass data as output_ref_t, see zxdg_output_v1_add_listener
static constexpr zxdg_output_v1_listener xdg_output_listener = {
    .logical_position = handle_xdg_output_logical_position,
    .logical_size = handle_xdg_output_logical_size,
    .done = handle_xdg_output_done,
    .name = handle_xdg_output_name,
    .description = handle_xdg_output_description
};


// =============================================================================
// FULLSCREEN DETECTION IMPLEMENTATION
// =============================================================================

static bool fs_update_state(wayland_listeners_context_t *ctx, bool new_state) {
    assert(ctx->animation_trigger_context);
    assert(ctx->animation_context);
    assert(ctx->wayland_context);
    assert(ctx->wayland_context->ctx_shm);
    const wayland_shared_memory_t *const wayland_ctx_shm = ctx->wayland_context->ctx_shm;

    if (new_state != ctx->fs_detector.has_fullscreen_toplevel) {
        ctx->fs_detector.has_fullscreen_toplevel = new_state;
        ctx->wayland_context->_fullscreen_detected = new_state;
        
        BONGOCAT_LOG_INFO("Fullscreen state changed: %s",
                          ctx->wayland_context->_fullscreen_detected ? "detected" : "cleared");

        if (atomic_load(&wayland_ctx_shm->configured)) {
            wayland_request_render(ctx->animation_trigger_context);
        } else {
            BONGOCAT_LOG_WARNING("Surface not configured yet, skip request render for fullscreen change");
        }

        return true;
    }

    return false;
}

static bool fs_check_compositor_fallback(void) {
    BONGOCAT_LOG_VERBOSE("Using compositor-specific fullscreen detection");
    
    // Try Hyprland first
    FILE *fp = popen("hyprctl activewindow 2>/dev/null", "r");
    if (fp) {
        char line[LINE_BUF] = {0};
        bool is_fullscreen = false;
        
        while (fgets(line, sizeof(line), fp)) {
            size_t len = strlen(line);
            if (len > 0 && line[len-1] == '\n') {
                line[len-1] = '\0';
            }
            
            if (strstr(line, "fullscreen: 1") || strstr(line, "fullscreen: 2") || 
                strstr(line, "fullscreen: true")) {
                is_fullscreen = true;
                BONGOCAT_LOG_DEBUG("Fullscreen detected in Hyprland");
                break;
            }
        }
        pclose(fp);
        return is_fullscreen;
    }
    
    // Try Sway as fallback
    fp = popen("swaymsg -t get_tree 2>/dev/null", "r");
    if (fp) {
        char sway_buffer[SWAY_BUF] = {0};
        bool is_fullscreen = false;
        
        while (fgets(sway_buffer, sizeof(sway_buffer), fp)) {
            if (strstr(sway_buffer, "\"fullscreen_mode\":1")) {
                is_fullscreen = true;
                BONGOCAT_LOG_DEBUG("Fullscreen detected in Sway");
                break;
            }
        }
        pclose(fp);
        return is_fullscreen;
    }
    
    BONGOCAT_LOG_DEBUG("No supported compositor found for fullscreen detection");
    return false;
}

static bool fs_check_status(wayland_listeners_context_t *ctx) {
    if (ctx->fs_detector.manager) {
        return ctx->fs_detector.has_fullscreen_toplevel;
    }

    return fs_check_compositor_fallback();
}

// Foreign toplevel protocol event handlers
static void fs_handle_toplevel_state(void *data, struct zwlr_foreign_toplevel_handle_v1 *handle,
                                     struct wl_array *state) {
    UNUSED(handle);

    assert(data);
    wayland_listeners_context_t *ctx = (wayland_listeners_context_t*)data;
    
    bool is_fullscreen = false;
    uint32_t *state_ptr = NULL;
    wl_array_for_each_typed(state_ptr, state, uint32_t) {
        if (*state_ptr == ZWLR_FOREIGN_TOPLEVEL_HANDLE_V1_STATE_FULLSCREEN) {
            is_fullscreen = true;
            break;
        }
    }

    const bool changed = fs_update_state(ctx, is_fullscreen);
    if (changed) {
        BONGOCAT_LOG_VERBOSE("fs_handle_toplevel.state: Update fullscreen state: %d", is_fullscreen);
    }
}

static void fs_handle_toplevel_closed(void *data, struct zwlr_foreign_toplevel_handle_v1 *handle) {
    assert(data);
    wayland_listeners_context_t *ctx = (wayland_listeners_context_t*)data;

    zwlr_foreign_toplevel_handle_v1_destroy(handle);

    // remove from tracked_toplevels if present
    for (size_t i = 0; i < ctx->num_toplevels; ++i) {
        if (ctx->tracked_toplevels[i] == handle) {
            ctx->tracked_toplevels[i] = NULL;
            // compact array to keep contiguous
            for (size_t j = i; j + 1 < ctx->num_toplevels; ++j) {
                ctx->tracked_toplevels[j] = ctx->tracked_toplevels[j+1];
            }
            ctx->tracked_toplevels[ctx->num_toplevels - 1] = NULL;
            ctx->num_toplevels--;
            break;
        }
    }

    BONGOCAT_LOG_DEBUG("fs_handle_toplevel.closed: Close toplevel handle");
}

// Minimal event handlers for unused events
static void fs_handle_title(void *data, struct zwlr_foreign_toplevel_handle_v1 *handle, const char *title) {
    UNUSED(handle); UNUSED(title);

    assert(data);
    //wayland_listeners_context_t *ctx = (wayland_listeners_context_t*)data;

    BONGOCAT_LOG_VERBOSE("fs_toplevel_listener.title: title received");
}

static void fs_handle_app_id(void *data, struct zwlr_foreign_toplevel_handle_v1 *handle, const char *app_id) {
    UNUSED(handle); UNUSED(app_id);

    assert(data);
    //wayland_listeners_context_t *ctx = (wayland_listeners_context_t*)data;

    BONGOCAT_LOG_VERBOSE("fs_toplevel_listener.app_id: app_id received");
}

static void fs_handle_output_enter(void *data, struct zwlr_foreign_toplevel_handle_v1 *handle, struct wl_output *output) {
    UNUSED(handle); UNUSED(output);

    assert(data);
    //wayland_listeners_context_t *ctx = (wayland_listeners_context_t*)data;

    BONGOCAT_LOG_VERBOSE("fs_toplevel_listener.output_enter: output received");
}

static void fs_handle_output_leave(void *data, struct zwlr_foreign_toplevel_handle_v1 *handle, struct wl_output *output) {
    UNUSED(handle); UNUSED(output);

    assert(data);
    //wayland_listeners_context_t *ctx = (wayland_listeners_context_t*)data;

    BONGOCAT_LOG_VERBOSE("fs_toplevel_listener.output_leave: output received");
}

static void fs_handle_done(void *data, struct zwlr_foreign_toplevel_handle_v1 *handle) {
    UNUSED(handle);

    assert(data);
    //wayland_listeners_context_t *ctx = (wayland_listeners_context_t*)data;

    BONGOCAT_LOG_VERBOSE("fs_toplevel_listener.done: done received");
}

static void fs_handle_parent(void *data, struct zwlr_foreign_toplevel_handle_v1 *handle, struct zwlr_foreign_toplevel_handle_v1 *parent) {
    UNUSED(handle); UNUSED(parent);

    assert(data);
    //wayland_listeners_context_t *ctx = (wayland_listeners_context_t*)data;

    BONGOCAT_LOG_VERBOSE("fs_toplevel_listener.parent: parent received");
}

/// @NOTE: fs_toplevel_listener MUST pass data as output_ref_t, see zwlr_foreign_toplevel_handle_v1_add_listener
static const struct zwlr_foreign_toplevel_handle_v1_listener fs_toplevel_listener = {
    .title = fs_handle_title,
    .app_id = fs_handle_app_id,
    .output_enter = fs_handle_output_enter,
    .output_leave = fs_handle_output_leave,
    .state = fs_handle_toplevel_state,
    .done = fs_handle_done,
    .closed = fs_handle_toplevel_closed,
    .parent = fs_handle_parent,
};

static void fs_handle_manager_toplevel(void *data, struct zwlr_foreign_toplevel_manager_v1 *manager, 
                                      struct zwlr_foreign_toplevel_handle_v1 *toplevel) {
    UNUSED(manager);

    assert(data);
    wayland_listeners_context_t *ctx = (wayland_listeners_context_t*)data;

    BONGOCAT_LOG_VERBOSE("fs_toplevel_manager_listener.toplevel: toplevel received");

    zwlr_foreign_toplevel_handle_v1_add_listener(toplevel, &fs_toplevel_listener, ctx);
    if (ctx->num_toplevels < MAX_TOPLEVELS) {
        bool already_tracked = false;
        for (size_t i = 0; i < ctx->num_toplevels; i++) {
            if (ctx->tracked_toplevels[i] == toplevel) {
                already_tracked = true;
                break;
            }
        }
        if (!already_tracked) {
            ctx->tracked_toplevels[ctx->num_toplevels] = toplevel;
            ctx->num_toplevels++;
        }
    } else {
        BONGOCAT_LOG_ERROR("fs_toplevel_manager_listener.toplevel: toplevel tracker is full, %zu max: %d", ctx->num_toplevels, MAX_TOPLEVELS);
    }

    BONGOCAT_LOG_DEBUG("fs_toplevel_manager_listener.toplevel: New toplevel registered for fullscreen monitoring: %zu", ctx->num_toplevels);
}

static void fs_handle_manager_finished(void *data, struct zwlr_foreign_toplevel_manager_v1 *manager) {
    assert(data);
    wayland_listeners_context_t *ctx = (wayland_listeners_context_t*)data;

    BONGOCAT_LOG_INFO("fs_toplevel_manager_listener.finished: Foreign toplevel manager finished");
    zwlr_foreign_toplevel_manager_v1_destroy(manager);
    ctx->fs_detector.manager = NULL;
}

/// @NOTE: fs_manager_listeners MUST pass data as wayland_listeners_context_t, see zwlr_foreign_toplevel_manager_v1_add_listener
static const struct zwlr_foreign_toplevel_manager_v1_listener fs_manager_listener = {
    .toplevel = fs_handle_manager_toplevel,
    .finished = fs_handle_manager_finished,
};

// =============================================================================
// SCREEN DIMENSION MANAGEMENT
// =============================================================================

static void screen_calculate_dimensions(wayland_listeners_context_t *ctx) {
    assert(ctx);

    if (!ctx->screen_info.mode_received || !ctx->screen_info.geometry_received || ctx->screen_info.screen_width > 0) {
        return;
    }
    
    const bool is_rotated = (ctx->screen_info.transform == WL_OUTPUT_TRANSFORM_90 ||
                             ctx->screen_info.transform == WL_OUTPUT_TRANSFORM_270 ||
                             ctx->screen_info.transform == WL_OUTPUT_TRANSFORM_FLIPPED_90 ||
                             ctx->screen_info.transform == WL_OUTPUT_TRANSFORM_FLIPPED_270);
    
    if (is_rotated) {
        ctx->screen_info.screen_width = ctx->screen_info.raw_height;
        ctx->screen_info.screen_height = ctx->screen_info.raw_width;
        BONGOCAT_LOG_INFO("Detected rotated screen: %dx%d (transform: %d)",
                          ctx->screen_info.raw_height, ctx->screen_info.raw_width, ctx->screen_info.transform);
    } else {
        ctx->screen_info.screen_width = ctx->screen_info.raw_width;
        ctx->screen_info.screen_height = ctx->screen_info.raw_height;
        BONGOCAT_LOG_INFO("Detected screen: %dx%d (transform: %d)",
                          ctx->screen_info.raw_width, ctx->screen_info.raw_height, ctx->screen_info.transform);
    }
}

// =============================================================================
// BUFFER AND DRAWING MANAGEMENT
// =============================================================================

int create_shm(off_t size) {
    const size_t name_suffix_len = 8;
    const size_t name_prefix_len = 9;
    char name[] = "/bar-shm-XXXXXXXX";
    assert((name_prefix_len + name_suffix_len) == strlen(name));
    const char charset[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    int fd = -1;

    for (int i = 0; i < CREATE_SHM_MAX_ATTEMPTS; i++) {
        for (size_t j = 0; j < name_suffix_len; j++) {
            name[name_prefix_len + j] = charset[rand() % (sizeof(charset) - 1)];
        }
        fd = shm_open(name, O_RDWR | O_CREAT | O_EXCL, 0600);
        if (fd >= 0) {
            shm_unlink(name);
            break;
        }
    }

    if (fd < 0 || ftruncate(fd, size) < 0) {
        perror("shm");
        return -1;
    }

    return fd;
}

// =============================================================================
// WAYLAND EVENT HANDLERS
// =============================================================================

static void layer_surface_configure(void *data,
                                   struct zwlr_layer_surface_v1 *ls,
                                   uint32_t serial, uint32_t w, uint32_t h) {
    assert(data);
    wayland_listeners_context_t *ctx = (wayland_listeners_context_t*)data;

    assert(ctx->animation_trigger_context);
    assert(ctx->wayland_context);
    assert(ctx->wayland_context->ctx_shm);
    wayland_shared_memory_t *wayland_ctx_shm = ctx->wayland_context->ctx_shm;

    zwlr_layer_surface_v1_ack_configure(ls, serial);
    atomic_store(&wayland_ctx_shm->configured, true);
    wayland_request_render(ctx->animation_trigger_context);

    BONGOCAT_LOG_DEBUG("layer_surface.configure: Layer surface configured: %dx%d", w, h);
}
static void layer_surface_closed(void *data,
                                 struct zwlr_layer_surface_v1 *ls) {
    UNUSED(ls);

    assert(data);
    //wayland_listeners_context_t *ctx = (wayland_listeners_context_t*)data;

    BONGOCAT_LOG_VERBOSE("layer_surface.closed: Layer surface closed");
}

/// @NOTE: layer_listeners MUST pass data as wayland_listeners_context_t, see zwlr_layer_surface_v1_add_listener
static struct zwlr_layer_surface_v1_listener layer_listener = {
    .configure = layer_surface_configure,
    .closed = layer_surface_closed,
};

static void xdg_wm_base_ping(void *data, struct xdg_wm_base *wm_base, uint32_t serial) {
    assert(data);
    //wayland_listeners_context_t *ctx = (wayland_listeners_context_t*)data;

    BONGOCAT_LOG_VERBOSE("xdg_wm_base.ping: base pong %x", serial);
    xdg_wm_base_pong(wm_base, serial);
}

/// @NOTE: xdg_wm_base_listeners MUST pass data as wayland_listeners_context_t, see xdg_wm_base_add_listener
static struct xdg_wm_base_listener xdg_wm_base_listener = {
    .ping = xdg_wm_base_ping,
};

static void output_geometry(void *data,
                            struct wl_output *wl_output,
                            int32_t x,
                            int32_t y,
                            int32_t physical_width,
                            int32_t physical_height,
                            int32_t subpixel,
                            const char *make,
                            const char *model,
                            int32_t transform) {
    UNUSED(wl_output);
    UNUSED(x); UNUSED(y);
    UNUSED(physical_width); UNUSED(physical_height);
    UNUSED(subpixel);
    UNUSED(make); UNUSED(model);

    assert(data);
    wayland_listeners_context_t *ctx = (wayland_listeners_context_t*)data;

    ctx->screen_info.transform = transform;
    ctx->screen_info.geometry_received = true;
    BONGOCAT_LOG_DEBUG("wl_output.geometry: Output transform: %d", transform);
    screen_calculate_dimensions(ctx);
}

static void output_mode(void *data ,
                       struct wl_output *wl_output ,
                       uint32_t flags, int32_t width, int32_t height,
                       int32_t refresh) {
    UNUSED(wl_output);
    UNUSED(refresh);

    assert(data);
    wayland_listeners_context_t *ctx = (wayland_listeners_context_t*)data;

    BONGOCAT_LOG_VERBOSE("wl_output.mode: mode received: %u", flags);

    if (flags & WL_OUTPUT_MODE_CURRENT) {
        ctx->screen_info.raw_width = width;
        ctx->screen_info.raw_height = height;
        ctx->screen_info.mode_received = true;
        BONGOCAT_LOG_DEBUG("wl_output.mode: Received raw screen mode: %dx%d", width, height);
        screen_calculate_dimensions(ctx);
    }
}

static void output_done(void *data,
                       struct wl_output *wl_output) {
    UNUSED(wl_output);

    assert(data);
    wayland_listeners_context_t *ctx = (wayland_listeners_context_t*)data;

    screen_calculate_dimensions(ctx);
    BONGOCAT_LOG_DEBUG("wl_output.done: Output configuration complete");
}

static void output_scale(void *data,
                        struct wl_output *wl_output,
                        int32_t factor) {
    UNUSED(wl_output); UNUSED(factor);

    assert(data);
    //wayland_listeners_context_t *ctx = (wayland_listeners_context_t*)data;

    // Scale not needed for our use case
    BONGOCAT_LOG_VERBOSE("wl_output.scale: factor received");
}

/// @NOTE: output_listeners MUST pass data as wayland_listeners_context_t, see wl_output_add_listener
static struct wl_output_listener output_listener = {
    .geometry = output_geometry,
    .mode = output_mode,
    .done = output_done,
    .scale = output_scale,
};


static void buffer_release(void *data, struct wl_buffer *buffer) {
    UNUSED(buffer);

    assert(data);
    wayland_shm_buffer_t *wayland_ctx_shm_buffer = (wayland_shm_buffer_t *)data;
    assert(wayland_ctx_shm_buffer->_animation_trigger_context);

    atomic_store(&wayland_ctx_shm_buffer->busy, false);
    BONGOCAT_LOG_VERBOSE("wl_buffer.release: buffer %d freed", wayland_ctx_shm_buffer->index);

    /* if someone asked for a render while this was busy, reschedule it */
    if (atomic_exchange(&wayland_ctx_shm_buffer->pending, false)) {
        BONGOCAT_LOG_VERBOSE("wl_buffer.release: pending render -> request render");
        wayland_request_render(wayland_ctx_shm_buffer->_animation_trigger_context);
    }
}

/// @NOTE: buffer_listeners MUST pass data as wayland_shm_buffer_t, see wl_buffer_add_listener
static const struct wl_buffer_listener buffer_listener = {
    .release = buffer_release,
};

// =============================================================================
// WAYLAND PROTOCOL REGISTRY
// =============================================================================

static void registry_global(void *data , struct wl_registry *reg,
                           uint32_t name, const char *iface, uint32_t ver) {
    UNUSED(ver);

    assert(data);
    wayland_listeners_context_t *ctx = (wayland_listeners_context_t*)data;
    assert(ctx->wayland_context);

    BONGOCAT_LOG_VERBOSE("wl_registry.global: registry received: %s", iface);

    if (strcmp(iface, wl_compositor_interface.name) == 0) {
        ctx->wayland_context->compositor = (struct wl_compositor *)wl_registry_bind(reg, name, &wl_compositor_interface, 4);
        BONGOCAT_LOG_VERBOSE("wl_registry.global: compositor registry bind");
    } else if (strcmp(iface, wl_shm_interface.name) == 0) {
        ctx->wayland_context->shm = (struct wl_shm *)wl_registry_bind(reg, name, &wl_shm_interface, 1);
        BONGOCAT_LOG_VERBOSE("wl_registry.global: shm registry bind");
    } else if (strcmp(iface, zwlr_layer_shell_v1_interface.name) == 0) {
        ctx->wayland_context->layer_shell = (struct zwlr_layer_shell_v1 *)wl_registry_bind(reg, name, &zwlr_layer_shell_v1_interface, 1);
        BONGOCAT_LOG_VERBOSE("wl_registry.global: layer_shell registry bind");
    } else if (strcmp(iface, xdg_wm_base_interface.name) == 0) {
        ctx->wayland_context->xdg_wm_base = (struct xdg_wm_base *)wl_registry_bind(reg, name, &xdg_wm_base_interface, 1);
        BONGOCAT_LOG_VERBOSE("wl_registry.global: xdg_wm_base registry bind");
        if (ctx->wayland_context->xdg_wm_base) {
            xdg_wm_base_add_listener(ctx->wayland_context->xdg_wm_base, &xdg_wm_base_listener, ctx);
        }
    } else if (strcmp(iface, zxdg_output_manager_v1_interface.name) == 0) {
        ctx->xdg_output_manager = (zxdg_output_manager_v1 *)wl_registry_bind(reg, name, &zxdg_output_manager_v1_interface, 3);
        BONGOCAT_LOG_VERBOSE("wl_registry.global: xdg_output_manager registry bind");
    } else if (strcmp(iface, wl_output_interface.name) == 0) {
        if (ctx->output_count < MAX_OUTPUTS) {
            ctx->outputs[ctx->output_count].name = name;
            ctx->outputs[ctx->output_count].wl_output = (wl_output *)wl_registry_bind(reg, name, &wl_output_interface, 2);
            wl_output_add_listener(ctx->outputs[ctx->output_count].wl_output, &output_listener, ctx);
            BONGOCAT_LOG_VERBOSE("wl_registry.global: wl_output registry bind: %i", ctx->output_count);
            ctx->output_count++;
        }
    } else if (strcmp(iface, zwlr_foreign_toplevel_manager_v1_interface.name) == 0) {
        ctx->fs_detector.manager = (struct zwlr_foreign_toplevel_manager_v1 *)
            wl_registry_bind(reg, name, &zwlr_foreign_toplevel_manager_v1_interface, 3);
        BONGOCAT_LOG_VERBOSE("wl_registry.global: foreign_toplevel_manager (fs_detector.manager) registry bind");
        if (ctx->fs_detector.manager) {
            zwlr_foreign_toplevel_manager_v1_add_listener(ctx->fs_detector.manager, &fs_manager_listener, ctx);
            BONGOCAT_LOG_INFO("wl_registry.global: Foreign toplevel manager bound - using Wayland protocol for fullscreen detection");
        }
    }
}

static void registry_remove(void *data,
                           struct wl_registry *registry,
                           uint32_t name) {
    assert(data);
    //wayland_listeners_context_t *ctx = (wayland_listeners_context_t*)data;

    UNUSED(registry); UNUSED(name);

    BONGOCAT_LOG_VERBOSE("wl_registry.global_remove: registry received");
}

/// @NOTE: reg_listeners MUST pass data as wayland_listeners_context_t, see zxdg_output_v1_add_listener
static struct wl_registry_listener reg_listener = {
    .global = registry_global,
    .global_remove = registry_remove
};

// =============================================================================
// MAIN WAYLAND INTERFACE IMPLEMENTATION
// =============================================================================

static bongocat_error_t wayland_setup_protocols(wayland_listeners_context_t* ctx) {
    BONGOCAT_CHECK_NULL(ctx, bongocat_error_t::BONGOCAT_ERROR_INVALID_PARAM);

    wayland_context_t *wayland_ctx = ctx->wayland_context;
    //animation_context_t *anim = ctx->animation_context;
    //animation_trigger_context_t *trigger_ctx = ctx->animation_trigger_context;

    // read-only config
    const config_t *const current_config = wayland_ctx->_local_copy_config;
    assert(current_config);

    struct wl_registry *registry = wl_display_get_registry(wayland_ctx->display);
    if (!registry) {
        BONGOCAT_LOG_ERROR("Failed to get Wayland registry");
        return bongocat_error_t::BONGOCAT_ERROR_WAYLAND;
    }

    wl_registry_add_listener(registry, &reg_listener, ctx);
    wl_display_roundtrip(wayland_ctx->display);

    if (ctx->xdg_output_manager) {
        for (size_t i = 0; i < ctx->output_count; i++) {
            ctx->outputs[i].xdg_output = zxdg_output_manager_v1_get_xdg_output(ctx->xdg_output_manager, ctx->outputs[i].wl_output);
            zxdg_output_v1_add_listener(ctx->outputs[i].xdg_output, &xdg_output_listener, &ctx->outputs[i]);
        }

        // Wait for all xdg_output events
        wl_display_roundtrip(wayland_ctx->display);
    }

    wayland_ctx->output = NULL;
    if (current_config->output_name) {
        for (size_t i = 0; i < ctx->output_count; ++i) {
            if (ctx->outputs[i].name_received &&
                strcmp(ctx->outputs[i].name_str, current_config->output_name) == 0) {
                wayland_ctx->output = ctx->outputs[i].wl_output;
                wayland_ctx->_output_name_str = ctx->outputs[i].name_str;
                BONGOCAT_LOG_INFO("Matched output: %s", wayland_ctx->_output_name_str);
                break;
            }
        }

        if (!wayland_ctx->output) {
            BONGOCAT_LOG_ERROR("Could not find output named '%s', defaulting to first output",
                               current_config->output_name);
        }
    }

    // Fallback
    if (!wayland_ctx->output && ctx->output_count > 0) {
        wayland_ctx->output = ctx->outputs[0].wl_output;
        wayland_ctx->_output_name_str = ctx->outputs[0].name_str;
        BONGOCAT_LOG_WARNING("Falling back to first output: %s", wayland_ctx->_output_name_str);
    }

    if (!wayland_ctx->compositor || !wayland_ctx->shm || !wayland_ctx->layer_shell) {
        BONGOCAT_LOG_ERROR("Missing required Wayland protocols");
        wl_registry_destroy(registry);
        return bongocat_error_t::BONGOCAT_ERROR_WAYLAND;
    }

    // Configure screen dimensions
    int screen_width = DEFAULT_SCREEN_WIDTH;
    if (wayland_ctx->output) {
        wl_display_roundtrip(wayland_ctx->display);
        if (ctx->screen_info.screen_width > 0) {
            BONGOCAT_LOG_INFO("Detected screen width: %d", ctx->screen_info.screen_width);
            screen_width = ctx->screen_info.screen_width;
        } else {
            BONGOCAT_LOG_WARNING("Using default screen width: %d", DEFAULT_SCREEN_WIDTH);
            screen_width = DEFAULT_SCREEN_WIDTH;
        }
    } else {
        BONGOCAT_LOG_WARNING("No output found, using default screen width: %d", DEFAULT_SCREEN_WIDTH);
        screen_width = DEFAULT_SCREEN_WIDTH;
    }
    wayland_ctx->_screen_width = screen_width;

    wl_registry_destroy(registry);
    return bongocat_error_t::BONGOCAT_SUCCESS;
}

static bongocat_error_t wayland_setup_surface(wayland_listeners_context_t* ctx) {
    BONGOCAT_CHECK_NULL(ctx, bongocat_error_t::BONGOCAT_ERROR_INVALID_PARAM);

    wayland_context_t *wayland_ctx = ctx->wayland_context;
    //animation_context_t *anim = ctx->animation_context;
    //animation_trigger_context_t *trigger_ctx = ctx->animation_trigger_context;

    // read-only config
    const config_t *const current_config = wayland_ctx->_local_copy_config;
    assert(current_config);

    wayland_ctx->surface = wl_compositor_create_surface(wayland_ctx->compositor);
    if (!wayland_ctx->surface) {
        BONGOCAT_LOG_ERROR("Failed to create surface");
        return bongocat_error_t::BONGOCAT_ERROR_WAYLAND;
    }

    wayland_ctx->layer_surface = zwlr_layer_shell_v1_get_layer_surface(wayland_ctx->layer_shell, wayland_ctx->surface, wayland_ctx->output,
                                                      ZWLR_LAYER_SHELL_V1_LAYER_OVERLAY,
                                                      "bongocat-overlay");

    if (!wayland_ctx->layer_surface) {
        BONGOCAT_LOG_ERROR("Failed to create layer surface");
        return bongocat_error_t::BONGOCAT_ERROR_WAYLAND;
    }

    // Configure layer surface
    uint32_t anchor = ZWLR_LAYER_SURFACE_V1_ANCHOR_LEFT | ZWLR_LAYER_SURFACE_V1_ANCHOR_RIGHT;
    switch (current_config->overlay_position) {
        case overlay_position_t::POSITION_TOP:
            anchor |= ZWLR_LAYER_SURFACE_V1_ANCHOR_TOP;
            break;
        case overlay_position_t::POSITION_BOTTOM:
            anchor |= ZWLR_LAYER_SURFACE_V1_ANCHOR_BOTTOM;
            break;
        default:
            BONGOCAT_LOG_ERROR("Invalid overlay_position %d for layer surface, set to top (default)");
            anchor |= ZWLR_LAYER_SURFACE_V1_ANCHOR_TOP;
            break;
    }
    
    zwlr_layer_surface_v1_set_anchor(wayland_ctx->layer_surface, anchor);
    zwlr_layer_surface_v1_set_size(wayland_ctx->layer_surface, 0, current_config->bar_height);
    zwlr_layer_surface_v1_set_exclusive_zone(wayland_ctx->layer_surface, -1);
    zwlr_layer_surface_v1_set_keyboard_interactivity(wayland_ctx->layer_surface,
                                                     ZWLR_LAYER_SURFACE_V1_KEYBOARD_INTERACTIVITY_NONE);
    zwlr_layer_surface_v1_add_listener(wayland_ctx->layer_surface, &layer_listener, ctx);

    // Make surface click-through
    struct wl_region *input_region = wl_compositor_create_region(wayland_ctx->compositor);
    if (input_region) {
        wl_surface_set_input_region(wayland_ctx->surface, input_region);
        wl_region_destroy(input_region);
    }

    wl_surface_commit(wayland_ctx->surface);
    return bongocat_error_t::BONGOCAT_SUCCESS;
}

static void wayland_cleanup_shm_buffer(wayland_shm_buffer_t *buffer) {
    assert(buffer);

    wl_buffer_destroy(buffer->buffer);
    if (buffer->pixels && buffer->pixels != MAP_FAILED) {
        munmap(buffer->pixels, buffer->pixels_size);
        buffer->pixels = NULL;
    }
    buffer->pixels_size = 0;
    atomic_store(&buffer->busy, false);
    atomic_store(&buffer->pending, false);
    buffer->index = 0;
    buffer->_animation_trigger_context = NULL;
}
static bongocat_error_t wayland_setup_buffer(wayland_context_t *wayland_context, animation_trigger_context_t *trigger_ctx) {
    BONGOCAT_CHECK_NULL(wayland_context, bongocat_error_t::BONGOCAT_ERROR_INVALID_PARAM);
    BONGOCAT_CHECK_NULL(trigger_ctx, bongocat_error_t::BONGOCAT_ERROR_INVALID_PARAM);

    // read-only config
    const config_t *const current_config = wayland_context->_local_copy_config;
    assert(current_config);

    wayland_shared_memory_t *wayland_ctx_shm = wayland_context->ctx_shm;

    const int32_t buffer_width = wayland_context->_screen_width;
    const int32_t buffer_height = current_config->bar_height;
    const int32_t buffer_size = buffer_width * buffer_height * RGBA_CHANNELS;
    if (buffer_size <= 0) {
        BONGOCAT_LOG_ERROR("Invalid buffer size: %d", buffer_size);
        return bongocat_error_t::BONGOCAT_ERROR_WAYLAND;
    }
    const int32_t total_size = buffer_size * WAYLAND_NUM_BUFFERS;

    const int fd = create_shm(total_size);
    if (fd < 0) {
        return bongocat_error_t::BONGOCAT_ERROR_WAYLAND;
    }

    struct wl_shm_pool *pool = wl_shm_create_pool(wayland_context->shm, fd, total_size);
    if (!pool) {
        BONGOCAT_LOG_ERROR("Failed to create shared memory pool");
        close(fd);
        return bongocat_error_t::BONGOCAT_ERROR_WAYLAND;
    }

    for (size_t i = 0; i < WAYLAND_NUM_BUFFERS; i++) {
        assert(buffer_size >= 0 && (size_t)buffer_size <= SIZE_MAX);
        wayland_ctx_shm->buffers[i].pixels_size = buffer_size;
        wayland_ctx_shm->buffers[i].pixels = (uint8_t *)mmap(NULL, wayland_ctx_shm->buffers[i].pixels_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, (off_t)i * buffer_size);
        if (wayland_ctx_shm->buffers[i].pixels == MAP_FAILED) {
            BONGOCAT_LOG_ERROR("Failed to map shared memory: %s", strerror(errno));
            for (size_t j = 0; j < i; j++) {
                wayland_cleanup_shm_buffer(&wayland_ctx_shm->buffers[j]);
            }
            wl_shm_pool_destroy(pool);
            close(fd);
            return bongocat_error_t::BONGOCAT_ERROR_MEMORY;
        }

        wayland_ctx_shm->buffers[i].buffer = wl_shm_pool_create_buffer(pool, 0, wayland_context->_screen_width,
                                          current_config->bar_height,
                                          wayland_context->_screen_width * RGBA_CHANNELS,
                                          WL_SHM_FORMAT_ARGB8888);
        if (!wayland_ctx_shm->buffers[i].buffer) {
            BONGOCAT_LOG_ERROR("Failed to create buffer");
            for (size_t j = 0; j < i; j++) {
                wayland_cleanup_shm_buffer(&wayland_ctx_shm->buffers[j]);
            }
            wl_shm_pool_destroy(pool);
            close(fd);
            return bongocat_error_t::BONGOCAT_ERROR_WAYLAND;
        }

        assert(i <= INT_MAX);
        wl_buffer_add_listener(wayland_ctx_shm->buffers[i].buffer, &buffer_listener, &wayland_ctx_shm->buffers[i]);
        wayland_ctx_shm->buffers[i].index = (int)i;
        atomic_store(&wayland_ctx_shm->buffers[i].busy, false);
        atomic_store(&wayland_ctx_shm->buffers[i].pending, false);
        wayland_ctx_shm->buffers[i]._animation_trigger_context = trigger_ctx;
    }

    wl_shm_pool_destroy(pool);
    close(fd);

    wayland_ctx_shm->current_buffer_index = 0;

    return bongocat_error_t::BONGOCAT_SUCCESS;
}

bongocat_error_t wayland_init(wayland_listeners_context_t* ctx, wayland_context_t* wayland, animation_context_t *anim, animation_trigger_context_t *trigger_ctx, const config_t *config) {
    BONGOCAT_CHECK_NULL(ctx, bongocat_error_t::BONGOCAT_ERROR_INVALID_PARAM);
    BONGOCAT_CHECK_NULL(wayland, bongocat_error_t::BONGOCAT_ERROR_INVALID_PARAM);
    BONGOCAT_CHECK_NULL(config, bongocat_error_t::BONGOCAT_ERROR_INVALID_PARAM);
    BONGOCAT_CHECK_NULL(anim, bongocat_error_t::BONGOCAT_ERROR_INVALID_PARAM);

    ctx->wayland_context = NULL;
    ctx->animation_context = NULL;
    ctx->animation_trigger_context = NULL;
    for (size_t i = 0; i < MAX_TOPLEVELS; i++) {
        ctx->tracked_toplevels[i] = NULL;
    }
    ctx->num_toplevels = 0;
    for (size_t i = 0; i < MAX_OUTPUTS; i++) {
        ctx->outputs[i].wl_output = NULL;
        ctx->outputs[i].xdg_output = NULL;
        ctx->outputs[i].name = 0;
        ctx->outputs[i].name_received = false;
        memset(ctx->outputs[i].name_str, 0, OUTPUT_NAME_SIZE);
    }
    ctx->output_count = 0;
    ctx->xdg_output_manager = NULL;

    ctx->fs_detector.has_fullscreen_toplevel = false;
    ctx->fs_detector.manager = NULL;

    ctx->screen_info.screen_width = 0;
    ctx->screen_info.screen_height = 0;
    ctx->screen_info.transform = 0;
    ctx->screen_info.raw_width = 0;
    ctx->screen_info.raw_height = 0;
    ctx->screen_info.mode_received = false;
    ctx->screen_info.geometry_received = false;

    wayland->display = NULL;
    wayland->compositor = NULL;
    wayland->shm = NULL;
    wayland->layer_shell = NULL;
    wayland->xdg_wm_base = NULL;
    wayland->output = NULL;
    wayland->surface = NULL;
    wayland->layer_surface = NULL;

    wayland->_fullscreen_detected = false;
    wayland->_screen_width = DEFAULT_SCREEN_WIDTH;
    wayland->_output_name_str = NULL;
    wayland->_frame_cb = NULL;
    wayland->_frame_pending = false;
    wayland->_redraw_after_frame = false;
    wayland->_last_frame_timestamp_ms = 0;
    pthread_mutex_init(&wayland->_frame_cb_lock, NULL);

    // Initialize shared memory
    wayland->ctx_shm = (wayland_shared_memory_t *)mmap(NULL, sizeof(wayland_shared_memory_t), PROT_READ | PROT_WRITE,
                                        MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if (wayland->ctx_shm == MAP_FAILED) {
        BONGOCAT_LOG_ERROR("Failed to create shared memory for animation system: %s", strerror(errno));
        return bongocat_error_t::BONGOCAT_ERROR_MEMORY;
    }
    if (wayland->ctx_shm) {
        static_assert(WAYLAND_NUM_BUFFERS <= INT_MAX);
        for (size_t i = 0;i < WAYLAND_NUM_BUFFERS;i++) {
            wayland->ctx_shm->buffers[i].buffer = NULL;
            wayland->ctx_shm->buffers[i].pixels = NULL;
            wayland->ctx_shm->buffers[i].pixels_size = 0;
            atomic_store(&wayland->ctx_shm->buffers[i].busy, false);
            atomic_store(&wayland->ctx_shm->buffers[i].pending, false);
            wayland->ctx_shm->buffers[i]._animation_trigger_context = NULL;

            wayland->ctx_shm->buffers[i].index = (int)i;
        }
        atomic_store(&wayland->ctx_shm->configured, false);
    }

    // Initialize shared memory for local config
    wayland->_local_copy_config = (config_t *)mmap(NULL, sizeof(config_t), PROT_READ | PROT_WRITE,
                                        MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if (wayland->_local_copy_config == MAP_FAILED) {
        BONGOCAT_LOG_ERROR("Failed to create shared memory for animation system: %s", strerror(errno));
        if (wayland->ctx_shm && wayland->ctx_shm != MAP_FAILED) {
            munmap(wayland->ctx_shm, sizeof(wayland_shared_memory_t));
            wayland->ctx_shm = NULL;
        }
        return bongocat_error_t::BONGOCAT_ERROR_MEMORY;
    }
    wayland_update_config(wayland, config, trigger_ctx);

    BONGOCAT_LOG_INFO("Initializing Wayland connection");

    wayland->display = wl_display_connect(NULL);
    if (!wayland->display) {
        if (wayland->_local_copy_config && wayland->_local_copy_config != MAP_FAILED) {
            if (wayland->_local_copy_config->output_name) free(wayland->_local_copy_config->output_name);
            wayland->_local_copy_config->output_name = NULL;
            munmap(wayland->_local_copy_config, sizeof(config_t));
            wayland->_local_copy_config = NULL;
        }
        if (wayland->ctx_shm && wayland->ctx_shm != MAP_FAILED) {
            munmap(wayland->ctx_shm, sizeof(wayland_shared_memory_t));
            wayland->ctx_shm = NULL;
        }
        BONGOCAT_LOG_ERROR("Failed to connect to Wayland display");
        return bongocat_error_t::BONGOCAT_ERROR_WAYLAND;
    }

    ctx->wayland_context = wayland;
    ctx->animation_context = anim;
    ctx->animation_trigger_context = trigger_ctx;

    ctx->num_toplevels = 0;
    for (size_t i = 0; i < MAX_TOPLEVELS; ++i) {
        ctx->tracked_toplevels[i] = NULL;
    }

    bongocat_error_t result = wayland_setup_protocols(ctx);
    if (result != bongocat_error_t::BONGOCAT_SUCCESS) {
        wayland_cleanup(ctx);
        return result;
    }
    result = wayland_setup_surface(ctx);
    if (result != bongocat_error_t::BONGOCAT_SUCCESS) {
        wayland_cleanup(ctx);
        return result;
    }
    result = wayland_setup_buffer(wayland, trigger_ctx);
    if (result != bongocat_error_t::BONGOCAT_SUCCESS) {
        wayland_cleanup(ctx);
        return result;
    }

    wl_display_flush(wayland->display);
    wl_display_roundtrip(wayland->display);

    BONGOCAT_LOG_INFO("Wayland initialization complete (%dx%d buffer)",
                      wayland->_screen_width, wayland->_local_copy_config->bar_height);
    return bongocat_error_t::BONGOCAT_SUCCESS;
}

bongocat_error_t wayland_run(wayland_listeners_context_t* ctx, volatile sig_atomic_t *running, int signal_fd, const config_t* config, config_watcher_t* config_watcher, config_reload_callback_t config_reload_callback) {
    BONGOCAT_CHECK_NULL(ctx, bongocat_error_t::BONGOCAT_ERROR_INVALID_PARAM);
    BONGOCAT_CHECK_NULL(running, bongocat_error_t::BONGOCAT_ERROR_INVALID_PARAM);
    BONGOCAT_CHECK_NULL(config_reload_callback, bongocat_error_t::BONGOCAT_ERROR_INVALID_PARAM);
    BONGOCAT_CHECK_NULL(ctx->animation_context, bongocat_error_t::BONGOCAT_ERROR_INVALID_PARAM);
    BONGOCAT_CHECK_NULL(ctx->animation_trigger_context, bongocat_error_t::BONGOCAT_ERROR_INVALID_PARAM);
    BONGOCAT_CHECK_NULL(ctx->animation_trigger_context->_anim, bongocat_error_t::BONGOCAT_ERROR_INVALID_PARAM);
    BONGOCAT_CHECK_NULL(ctx->wayland_context, bongocat_error_t::BONGOCAT_ERROR_WAYLAND);

    wayland_context_t *wayland_ctx = ctx->wayland_context;
    //animation_context_t *anim = ctx->animation_context;
    animation_trigger_context_t *trigger_ctx = ctx->animation_trigger_context;

    BONGOCAT_LOG_INFO("Starting Wayland event loop");

    *running = 1;
    while (*running && wayland_ctx->display) {
        // Periodic fullscreen check for fallback detection
        struct timeval now;
        gettimeofday(&now, NULL);
        const time_ms_t elapsed_ms = (now.tv_sec - ctx->fs_detector.last_check.tv_sec) * 1000L +
                                     (now.tv_usec - ctx->fs_detector.last_check.tv_usec) / 1000L;
        if (elapsed_ms >= CHECK_INTERVAL_MS) {
            const bool new_state = fs_check_status(ctx);
            if (new_state != wayland_ctx->_fullscreen_detected) {
                fs_update_state(ctx, new_state);
            }
            ctx->fs_detector.last_check = now;
        }

        // Handle Wayland events
        const size_t fds_signals_index = 0;
        const size_t fds_config_reload_index = 1;
        const size_t fds_animation_render_index = 2;
        const size_t fds_wayland_index = 3;
        constexpr nfds_t fds_count = 4;
        pollfd fds[fds_count] = {
            { .fd = signal_fd, .events = POLLIN },
            { .fd = config_watcher->reload_efd, .events = POLLIN },
            { .fd = trigger_ctx->render_efd, .events = POLLIN },
            { .fd = wl_display_get_fd(wayland_ctx->display), .events = POLLIN },
        };
        static_assert(fds_count == LEN_ARRAY(fds));

        // compute desired timeout
        time_ms_t frame_based_timeout = config->fps > 0 ? 1000 / config->fps : 0;
        time_ms_t timeout_ms = frame_based_timeout;
        if (timeout_ms < POOL_MIN_TIMEOUT_MS) timeout_ms = POOL_MIN_TIMEOUT_MS;
        if (timeout_ms > POOL_MAX_TIMEOUT_MS) timeout_ms = POOL_MAX_TIMEOUT_MS;

        // avoid reloading twice, by signal OR watcher
        bool config_reload_requested = false;
        bool render_requested = false;
        bool needs_flush = false;

        bool prepared_read = false;
        do {
            int attempts = 0;
            while (wl_display_prepare_read(wayland_ctx->display) != 0 && attempts < MAX_ATTEMPTS) {
                wl_display_dispatch_pending(wayland_ctx->display);
                attempts++;
            }
            prepared_read = attempts < MAX_ATTEMPTS;
        } while(0);

        if (timeout_ms > INT_MAX) timeout_ms = INT_MAX;
        const int poll_result = poll(fds, fds_count, (int)timeout_ms);
        if (poll_result > 0) {
            // signal events
            if (fds[fds_signals_index].revents & POLLIN) {
                struct signalfd_siginfo fdsi;
                ssize_t s = read(fds[fds_signals_index].fd, &fdsi, sizeof(fdsi));
                if (s != sizeof(fdsi)) {
                    BONGOCAT_LOG_ERROR("Failed to read signal fd");
                } else {
                    switch (fdsi.ssi_signo) {
                        case SIGINT:
                        case SIGTERM:
                            BONGOCAT_LOG_INFO("Received signal %d, shutting down gracefully", fdsi.ssi_signo);
                            *running = 0;
                            break;
                        case SIGCHLD:
                            while (waitpid(-1, NULL, WNOHANG) > 0);
                            break;
                        case SIGUSR2:
                            BONGOCAT_LOG_INFO("Received SIGUSR2, reloading config");
                            config_reload_requested = true;
                            break;
                        default:
                            BONGOCAT_LOG_WARNING("Received unexpected signal %d", fdsi.ssi_signo);
                            break;
                    }
                }
            }
            if (!*running) {
                // draining pools
                for (size_t i = 0; i < fds_count; i++) {
                    if (fds[i].revents & POLLIN) {
                        int attempts = 0;
                        uint64_t u;
                        while (read(fds[i].fd, &u, sizeof(uint64_t)) == sizeof(uint64_t) && attempts < MAX_ATTEMPTS) {
                            attempts++;
                        }
                    }
                }
                if (prepared_read) wl_display_cancel_read(wayland_ctx->display);
                render_requested = false;
                break;
            }

            // reload config event
            if (fds[fds_config_reload_index].revents & POLLIN) {
                BONGOCAT_LOG_DEBUG("Receive reload event");

                int attempts = 0;
                uint64_t u;
                while (read(config_watcher->reload_efd, &u, sizeof(uint64_t)) == sizeof(uint64_t) && attempts < MAX_ATTEMPTS) {
                    attempts++;
                    // continue draining if multiple writes queued
                }
                // supress compiler warning
#if EAGAIN == EWOULDBLOCK
                if (errno != EAGAIN) {
                    BONGOCAT_LOG_ERROR("Error reading reload eventfd: %s", strerror(errno));
                }
#else
                if (errno != EAGAIN && errno != EWOULDBLOCK) {
                    BONGOCAT_LOG_ERROR("Error reading reload eventfd: %s", strerror(errno));
                }
#endif

                config_reload_requested = true;
            }

            // do reload once
            if (config_reload_requested && config_reload_callback) {
                config_reload_callback();
                render_requested = true;
            }

            // render event
            if (fds[fds_animation_render_index].revents & POLLIN) {
                BONGOCAT_LOG_VERBOSE("Receive render event");

                int attempts = 0;
                uint64_t u;
                while (read(trigger_ctx->render_efd, &u, sizeof(uint64_t)) == sizeof(uint64_t) && attempts < MAX_ATTEMPTS) {
                    attempts++;
                    // continue draining if multiple writes queued
                }
                // supress compiler warning
#if EAGAIN == EWOULDBLOCK
                if (errno != EAGAIN) {
                    BONGOCAT_LOG_ERROR("Error reading render eventfd: %s", strerror(errno));
                }
#else
                if (errno != EAGAIN && errno != EWOULDBLOCK) {
                    BONGOCAT_LOG_ERROR("Error reading render eventfd: %s", strerror(errno));
                }
#endif

                render_requested = true;
            }

            // wayland events
            if (prepared_read) {
                if (fds[fds_wayland_index].revents & POLLIN) {
                    if (wl_display_read_events(wayland_ctx->display) == -1 ||
                        wl_display_dispatch_pending(wayland_ctx->display) == -1) {
                        BONGOCAT_LOG_ERROR("Failed to handle Wayland events");
                        *running = 0;
                        return bongocat_error_t::BONGOCAT_ERROR_WAYLAND;
                    }
                } else {
                    wl_display_cancel_read(wayland_ctx->display);
                }
            } else {
                if (fds[fds_wayland_index].revents & POLLIN) {
                    if (wl_display_dispatch_pending(wayland_ctx->display) == -1) {
                        BONGOCAT_LOG_ERROR("Failed to dispatch pending events");
                        *running = 0;
                        return bongocat_error_t::BONGOCAT_ERROR_WAYLAND;
                    }
                }
            }

            if (render_requested) {
                if (!atomic_load(&wayland_ctx->ctx_shm->configured)) {
                    BONGOCAT_LOG_VERBOSE("Surface not configured yet, skip drawing");
                    render_requested = false;
                }
            }

            BONGOCAT_LOG_VERBOSE("Poll revents: signal=%x, reload=%x, render=%x, wayland=%x", fds[fds_signals_index].revents, fds[fds_config_reload_index].revents, fds[fds_animation_render_index].revents, fds[fds_wayland_index].revents);
        } else if (poll_result == 0) {
            if (prepared_read) wl_display_cancel_read(wayland_ctx->display);
            if (wl_display_dispatch_pending(wayland_ctx->display) == -1) {
                BONGOCAT_LOG_ERROR("Failed to dispatch pending events");
                *running = 0;
                return bongocat_error_t::BONGOCAT_ERROR_WAYLAND;
            }
        } else {
            if (prepared_read) wl_display_cancel_read(wayland_ctx->display);
            if (errno != EINTR) {
                BONGOCAT_LOG_ERROR("Poll error: %s", strerror(errno));
                *running = 0;
                return bongocat_error_t::BONGOCAT_ERROR_WAYLAND;
            }
        }

        if (render_requested) {
            BONGOCAT_LOG_VERBOSE("Receive render event");
            BONGOCAT_LOG_VERBOSE("Try to draw_bar in wayland_run");

            if (!atomic_load(&wayland_ctx->_frame_pending)) {
                wl_display_dispatch_pending(wayland_ctx->display);
                if (draw_bar(ctx)) {
                    needs_flush = true;
                }
            } else {
                if (!atomic_exchange(&wayland_ctx->_redraw_after_frame, true)) {
                    BONGOCAT_LOG_VERBOSE("Queued redraw after frame");
                }
            }
            render_requested = false;
        }

        if (needs_flush) {
            wl_display_flush(wayland_ctx->display);
        }
    }
    *running = 0;

    BONGOCAT_LOG_INFO("Wayland event loop exited");
    return bongocat_error_t::BONGOCAT_SUCCESS;
}

// =============================================================================
// PUBLIC API IMPLEMENTATION
// =============================================================================

int wayland_get_screen_width(wayland_listeners_context_t* ctx) {
    return ctx->screen_info.screen_width;
}

void wayland_update_config(wayland_context_t* ctx, const config_t *config, animation_trigger_context_t *trigger_ctx) {
    assert(ctx);
    assert(config);
    assert(ctx->_local_copy_config && ctx->_local_copy_config != MAP_FAILED);

    memcpy(ctx->_local_copy_config, config, sizeof(*config));
    ctx->_local_copy_config->output_name = config->output_name ? strdup(config->output_name) : NULL;

    /// @FIXME: make deep copy of keyboard_devices ?
    // keyboard_devices not used, get rid of out-side reference
    for (size_t i = 0; i < MAX_INPUT_DEVICES; i++) {
        ctx->_local_copy_config->keyboard_devices[i] = NULL;
    }

    /// @NOTE: assume animation has the same local copy as wayland config
    //animation_update_config(anim, config);
    if (atomic_load(&ctx->ctx_shm->configured)) {
        wayland_request_render(trigger_ctx);
    }
}

void wayland_cleanup(wayland_listeners_context_t* ctx) {
    BONGOCAT_LOG_INFO("Cleaning up Wayland resources");

    wayland_context_t *wayland_ctx = ctx->wayland_context;
    //animation_context_t *anim = ctx->animation_context;
    //animation_trigger_context_t *trigger_ctx = ctx->animation_trigger_context;

    wayland_shared_memory_t *wayland_ctx_shm = ctx->wayland_context->ctx_shm;

    if (wayland_ctx_shm && wayland_ctx_shm != MAP_FAILED) {
        atomic_store(&wayland_ctx_shm->configured, false);
    }

    // drain pending events
    if (wayland_ctx->display) {
        wl_display_flush(wayland_ctx->display);
        while (wl_display_dispatch_pending(wayland_ctx->display) > 0);
    }

    pthread_mutex_destroy(&wayland_ctx->_frame_cb_lock);
    atomic_store(&wayland_ctx->_frame_pending, false);
    atomic_store(&wayland_ctx->_redraw_after_frame, false);
    if (wayland_ctx->_frame_cb) wl_callback_destroy(wayland_ctx->_frame_cb);
    wayland_ctx->_frame_cb = NULL;
    wayland_ctx->_last_frame_timestamp_ms = 0;

    // First destroy xdg_output objects
    for (size_t i = 0; i < ctx->output_count; ++i) {
        if (ctx->outputs[i].xdg_output) {
            BONGOCAT_LOG_DEBUG("Destroying xdg_output %zu", i);
            zxdg_output_v1_destroy(ctx->outputs[i].xdg_output);
            ctx->outputs[i].xdg_output = NULL;
        }
    }

    // Then destroy the manager
    if (ctx->xdg_output_manager) {
        BONGOCAT_LOG_DEBUG("Destroying xdg_output_manager");
        zxdg_output_manager_v1_destroy(ctx->xdg_output_manager);
        ctx->xdg_output_manager = NULL;
    }

    // Finally destroy wl_output objects
    for (size_t i = 0; i < ctx->output_count; ++i) {
        if (ctx->outputs[i].wl_output) {
            BONGOCAT_LOG_DEBUG("Destroying wl_output %zu", i);
            wl_output_destroy(ctx->outputs[i].wl_output);
            ctx->outputs[i].wl_output = NULL;
        }
        memset(&ctx->outputs[i], 0, sizeof(output_ref_t));
    }
    ctx->output_count = 0;

    // cleanup wl buffers
    if (wayland_ctx_shm && wayland_ctx_shm != MAP_FAILED) {
        for (size_t i = 0; i < WAYLAND_NUM_BUFFERS; i++) {
            wayland_cleanup_shm_buffer(&wayland_ctx_shm->buffers[i]);
        }
        wayland_ctx_shm->current_buffer_index = 0;
    }


    if (wayland_ctx->layer_surface) {
        zwlr_layer_surface_v1_destroy(wayland_ctx->layer_surface);
        wayland_ctx->layer_surface = NULL;
    }

    if (wayland_ctx->surface) {
        wl_surface_destroy(wayland_ctx->surface);
        wayland_ctx->surface = NULL;
    }

    // Note: output is just a reference to one of the outputs[] entries
    // It will be destroyed when we destroy the outputs[] array above
    wayland_ctx->output = NULL;

    if (wayland_ctx->layer_shell) {
        zwlr_layer_shell_v1_destroy(wayland_ctx->layer_shell);
        wayland_ctx->layer_shell = NULL;
    }

    if (wayland_ctx->xdg_wm_base) {
        xdg_wm_base_destroy(wayland_ctx->xdg_wm_base);
        wayland_ctx->xdg_wm_base = NULL;
    }

    if (ctx->fs_detector.manager) {
        zwlr_foreign_toplevel_manager_v1_destroy(ctx->fs_detector.manager);
        ctx->fs_detector.manager = NULL;
    }

    if (wayland_ctx->shm) {
        wl_shm_destroy(wayland_ctx->shm);
        wayland_ctx->shm = NULL;
    }

    if (wayland_ctx->compositor) {
        wl_compositor_destroy(wayland_ctx->compositor);
        wayland_ctx->compositor = NULL;
    }

    for (size_t i = 0; i < ctx->num_toplevels; ++i) {
        if (ctx->tracked_toplevels[i]) zwlr_foreign_toplevel_handle_v1_destroy(ctx->tracked_toplevels[i]);
        ctx->tracked_toplevels[i] = NULL;
    }
    ctx->num_toplevels = 0;

    if (wayland_ctx->display) {
        wl_display_disconnect(wayland_ctx->display);
        wayland_ctx->display = NULL;
    }

    if (wayland_ctx->_local_copy_config && wayland_ctx->_local_copy_config != MAP_FAILED) {
        if (wayland_ctx->_local_copy_config->output_name) free(wayland_ctx->_local_copy_config->output_name);
        wayland_ctx->_local_copy_config->output_name = NULL;
        munmap(wayland_ctx->_local_copy_config, sizeof(config_t));
        wayland_ctx->_local_copy_config = NULL;
    }
    wayland_ctx->_screen_width = 0;
    wayland_ctx->_output_name_str = NULL;

    // Reset state
    wayland_ctx->_fullscreen_detected = false;

    memset(&ctx->fs_detector, 0, sizeof(fullscreen_detector_t));
    memset(&ctx->screen_info, 0, sizeof(screen_info_t));

    if (wayland_ctx->ctx_shm && wayland_ctx->ctx_shm != MAP_FAILED) {
        munmap(wayland_ctx->ctx_shm, sizeof(wayland_shared_memory_t));
        wayland_ctx->ctx_shm = NULL;
        wayland_ctx_shm = NULL;
    }

    ctx->wayland_context = NULL;
    ctx->animation_context = NULL;
    ctx->animation_trigger_context = NULL;

    wayland_ctx = NULL;
    //anim = NULL;
    //trigger_ctx = NULL;
    
    BONGOCAT_LOG_DEBUG("Wayland cleanup complete");
}

const char* wayland_get_current_layer_name(void) {
    return WAYLAND_LAYER_NAME;
}

bongocat_error_t wayland_request_render(animation_trigger_context_t *trigger_ctx) {
    if (!trigger_ctx || trigger_ctx->render_efd < 0) {
        return bongocat_error_t::BONGOCAT_ERROR_INVALID_PARAM;
    }

    uint64_t u = 1;
    ssize_t s = write(trigger_ctx->render_efd, &u, sizeof(u));
    if (s != sizeof(u)) {
        BONGOCAT_LOG_WARNING("Failed to write render eventfd: %s", strerror(errno));
        return bongocat_error_t::BONGOCAT_ERROR_FILE_IO;
    }

    return bongocat_error_t::BONGOCAT_SUCCESS;
}