#define _POSIX_C_SOURCE 200809L
#include "graphics/animation.h"
#include "platform/wayland.h"
#include "graphics/bar.h"
#include "utils/memory.h"
#include "../protocols/wlr-foreign-toplevel-management-v1-client-protocol.h"
#include "../protocols/xdg-output-unstable-v1-client-protocol.h"
#include <assert.h>
#include <poll.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <pthread.h>
#include <linux/input.h>
#include <signal.h>
#include <stdlib.h>
#include <wayland-client.h>
#include <sys/signalfd.h>
#include <sys/wait.h>


// =============================================================================
// GLOBAL STATE AND CONFIGURATION
// =============================================================================

#define LINE_BUF 512
#define SWAY_BUF 4096
#define MAX_TOPLEVELS 64

#define CREATE_SHM_MAX_ATTEMPTS 100
#define CHECK_INTERVAL_MS 100
#define POOL_MIN_TIMEOUT_MS 100
#define POOL_MAX_TIMEOUT_MS 1000
#define MAX_ATTEMPTS 100

#define WAYLAND_LAYER_NAME "OVERLAY"

// =============================================================================
// SCREEN DIMENSION MANAGEMENT
// =============================================================================

typedef struct {
    int screen_width;
    int screen_height;
    int transform;
    int raw_width;
    int raw_height;
    bool mode_received;
    bool geometry_received;
} screen_info_t;

static screen_info_t g_screen_info = {0};
static output_ref_t g_outputs[MAX_OUTPUTS];
static size_t g_output_count = 0;
static struct zxdg_output_manager_v1 *g_xdg_output_manager = NULL;

// use for listeners
static wayland_context_t* g_wayland_context = NULL;
static animation_context_t* g_animation_context = NULL;
static struct zwlr_foreign_toplevel_handle_v1* g_tracked_toplevels[MAX_TOPLEVELS] = {0};
static size_t g_num_toplevels = 0;

// =============================================================================
// ZXDG LISTENER IMPLEMENTATION
// =============================================================================

static void handle_xdg_output_name(void *data, struct zxdg_output_v1 *xdg_output,
                                   const char *name) {
    UNUSED(xdg_output);
    output_ref_t *oref = data;
    snprintf(oref->name_str, sizeof(oref->name_str), "%s", name);
    oref->name_received = true;
    BONGOCAT_LOG_DEBUG("xdg-output name received: %s", name);
}

static void handle_xdg_output_logical_position(void *data, struct zxdg_output_v1 *xdg_output,
                                               int32_t x, int32_t y) {
    UNUSED(data); UNUSED(xdg_output); UNUSED(x); UNUSED(y);
}
static void handle_xdg_output_logical_size(void *data, struct zxdg_output_v1 *xdg_output,
                                           int32_t width, int32_t height) {
    UNUSED(data); UNUSED(xdg_output); UNUSED(width); UNUSED(height);
}
static void handle_xdg_output_done(void *data, struct zxdg_output_v1 *xdg_output) {
    UNUSED(data); UNUSED(xdg_output);
}

static void handle_xdg_output_description(void *data, struct zxdg_output_v1 *xdg_output, const char *description) {
    UNUSED(data); UNUSED(xdg_output); UNUSED(description);
}

static const struct zxdg_output_v1_listener xdg_output_listener = {
    .logical_position = handle_xdg_output_logical_position,
    .logical_size = handle_xdg_output_logical_size,
    .done = handle_xdg_output_done,
    .name = handle_xdg_output_name,
    .description = handle_xdg_output_description
};

// =============================================================================
// FULLSCREEN DETECTION MODULE
// =============================================================================

typedef struct {
    struct zwlr_foreign_toplevel_manager_v1 *manager;
    bool has_fullscreen_toplevel;
    struct timeval last_check;
} fullscreen_detector_t;

static fullscreen_detector_t g_fs_detector = {0};

// =============================================================================
// FULLSCREEN DETECTION IMPLEMENTATION
// =============================================================================

static void fs_update_state(bool new_state) {
    assert(g_wayland_context);
    assert(g_animation_context);
    if (new_state != g_fs_detector.has_fullscreen_toplevel) {
        g_fs_detector.has_fullscreen_toplevel = new_state;
        g_wayland_context->fullscreen_detected = new_state;
        
        BONGOCAT_LOG_INFO("Fullscreen state changed: %s",
                          g_wayland_context->fullscreen_detected ? "detected" : "cleared");

        if (atomic_load(&g_wayland_context->configured)) {
            draw_bar(g_wayland_context, g_animation_context);
        }
    }
}

static bool fs_check_compositor_fallback(void) {
    BONGOCAT_LOG_DEBUG("Using compositor-specific fullscreen detection");
    
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

static bool fs_check_status(void) {
    if (g_fs_detector.manager) {
        return g_fs_detector.has_fullscreen_toplevel;
    }
    return fs_check_compositor_fallback();
}

// Foreign toplevel protocol event handlers
static void fs_handle_toplevel_state(void *data, struct zwlr_foreign_toplevel_handle_v1 *handle,
                                     struct wl_array *state) {
    UNUSED(data); UNUSED(handle);
    
    bool is_fullscreen = false;
    uint32_t *state_ptr = NULL;
    
    wl_array_for_each(state_ptr, state) {
        if (*state_ptr == ZWLR_FOREIGN_TOPLEVEL_HANDLE_V1_STATE_FULLSCREEN) {
            is_fullscreen = true;
            break;
        }
    }
    
    fs_update_state(is_fullscreen);
}

static void fs_handle_toplevel_closed(void *data, struct zwlr_foreign_toplevel_handle_v1 *handle) {
    UNUSED(data);
    zwlr_foreign_toplevel_handle_v1_destroy(handle);
}

// Minimal event handlers for unused events
static void fs_handle_title(void *data, struct zwlr_foreign_toplevel_handle_v1 *handle, const char *title) {
    UNUSED(data); UNUSED(handle); UNUSED(title);
}

static void fs_handle_app_id(void *data, struct zwlr_foreign_toplevel_handle_v1 *handle, const char *app_id) {
    UNUSED(data); UNUSED(handle); UNUSED(app_id);
}

static void fs_handle_output_enter(void *data, struct zwlr_foreign_toplevel_handle_v1 *handle, struct wl_output *output) {
    UNUSED(data); UNUSED(handle); UNUSED(output);
}

static void fs_handle_output_leave(void *data, struct zwlr_foreign_toplevel_handle_v1 *handle, struct wl_output *output) {
    UNUSED(data); UNUSED(handle); UNUSED(output);
}

static void fs_handle_done(void *data, struct zwlr_foreign_toplevel_handle_v1 *handle) {
    UNUSED(data); UNUSED(handle);
}

static void fs_handle_parent(void *data, struct zwlr_foreign_toplevel_handle_v1 *handle, struct zwlr_foreign_toplevel_handle_v1 *parent) {
    UNUSED(data); UNUSED(handle); UNUSED(parent);
}

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
    UNUSED(data); UNUSED(manager);

    zwlr_foreign_toplevel_handle_v1_add_listener(toplevel, &fs_toplevel_listener, NULL);
    if (g_num_toplevels < MAX_TOPLEVELS) {
        bool already_tracked = false;
        for (size_t i = 0; i < g_num_toplevels; i++) {
            if (g_tracked_toplevels[i] == toplevel) {
                already_tracked = true;
                break;
            }
        }
        if (!already_tracked) {
            g_tracked_toplevels[g_num_toplevels] = toplevel;
            g_num_toplevels++;
        }
    } else {
        BONGOCAT_LOG_ERROR("toplevel tracker is full, %zu max: %d", g_num_toplevels, MAX_TOPLEVELS);
    }

    BONGOCAT_LOG_DEBUG("New toplevel registered for fullscreen monitoring: %zu", g_num_toplevels);
}

static void fs_handle_manager_finished(void *data, struct zwlr_foreign_toplevel_manager_v1 *manager) {
    UNUSED(data);
    BONGOCAT_LOG_INFO("Foreign toplevel manager finished");
    zwlr_foreign_toplevel_manager_v1_destroy(manager);
    g_fs_detector.manager = NULL;
}

static const struct zwlr_foreign_toplevel_manager_v1_listener fs_manager_listener = {
    .toplevel = fs_handle_manager_toplevel,
    .finished = fs_handle_manager_finished,
};

// =============================================================================
// SCREEN DIMENSION MANAGEMENT
// =============================================================================

static void screen_calculate_dimensions(void) {
    if (!g_screen_info.mode_received || !g_screen_info.geometry_received || g_screen_info.screen_width > 0) {
        return;
    }
    
    bool is_rotated = (g_screen_info.transform == WL_OUTPUT_TRANSFORM_90 ||
                      g_screen_info.transform == WL_OUTPUT_TRANSFORM_270 ||
                      g_screen_info.transform == WL_OUTPUT_TRANSFORM_FLIPPED_90 ||
                      g_screen_info.transform == WL_OUTPUT_TRANSFORM_FLIPPED_270);
    
    if (is_rotated) {
        g_screen_info.screen_width = g_screen_info.raw_height;
        g_screen_info.screen_height = g_screen_info.raw_width;
        BONGOCAT_LOG_INFO("Detected rotated screen: %dx%d (transform: %d)",
                         g_screen_info.raw_height, g_screen_info.raw_width, g_screen_info.transform);
    } else {
        g_screen_info.screen_width = g_screen_info.raw_width;
        g_screen_info.screen_height = g_screen_info.raw_height;
        BONGOCAT_LOG_INFO("Detected screen: %dx%d (transform: %d)",
                         g_screen_info.raw_width, g_screen_info.raw_height, g_screen_info.transform);
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

static void layer_surface_configure(void *data ,
                                   struct zwlr_layer_surface_v1 *ls,
                                   uint32_t serial, uint32_t w, uint32_t h) {
    UNUSED(data);
    assert(g_wayland_context);
    assert(g_animation_context);
    BONGOCAT_LOG_DEBUG("Layer surface configured: %dx%d", w, h);
    zwlr_layer_surface_v1_ack_configure(ls, serial);
    atomic_store(&g_wayland_context->configured, true);
    draw_bar(g_wayland_context, g_animation_context);
}

static struct zwlr_layer_surface_v1_listener layer_listener = {
    .configure = layer_surface_configure,
    .closed = NULL,
};

static void xdg_wm_base_ping(void *data ,
                            struct xdg_wm_base *wm_base, uint32_t serial) {
    UNUSED(data);
    xdg_wm_base_pong(wm_base, serial);
}

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
    UNUSED(data); UNUSED(wl_output);
    UNUSED(x); UNUSED(y);
    UNUSED(physical_width); UNUSED(physical_height);
    UNUSED(subpixel);
    UNUSED(make); UNUSED(model);

    g_screen_info.transform = transform;
    g_screen_info.geometry_received = true;
    BONGOCAT_LOG_DEBUG("Output transform: %d", transform);
    screen_calculate_dimensions();
}

static void output_mode(void *data ,
                       struct wl_output *wl_output ,
                       uint32_t flags, int32_t width, int32_t height,
                       int32_t refresh) {
    UNUSED(data); UNUSED(wl_output);
    UNUSED(refresh);

    if (flags & WL_OUTPUT_MODE_CURRENT) {
        g_screen_info.raw_width = width;
        g_screen_info.raw_height = height;
        g_screen_info.mode_received = true;
        BONGOCAT_LOG_DEBUG("Received raw screen mode: %dx%d", width, height);
        screen_calculate_dimensions();
    }
}

static void output_done(void *data,
                       struct wl_output *wl_output) {
    UNUSED(data); UNUSED(wl_output);
    screen_calculate_dimensions();
    BONGOCAT_LOG_DEBUG("Output configuration complete");
}

static void output_scale(void *data,
                        struct wl_output *wl_output,
                        int32_t factor) {
    UNUSED(data); UNUSED(wl_output); UNUSED(factor);
    // Scale not needed for our use case
}

static struct wl_output_listener output_listener = {
    .geometry = output_geometry,
    .mode = output_mode,
    .done = output_done,
    .scale = output_scale,
};

// =============================================================================
// WAYLAND PROTOCOL REGISTRY
// =============================================================================

static void registry_global(void *data , struct wl_registry *reg,
                           uint32_t name, const char *iface, uint32_t ver) {
    UNUSED(data); UNUSED(ver);
    assert(g_wayland_context);
    assert(g_outputs);

    if (strcmp(iface, wl_compositor_interface.name) == 0) {
        g_wayland_context->compositor = (struct wl_compositor *)wl_registry_bind(reg, name, &wl_compositor_interface, 4);
    } else if (strcmp(iface, wl_shm_interface.name) == 0) {
        g_wayland_context->shm = (struct wl_shm *)wl_registry_bind(reg, name, &wl_shm_interface, 1);
    } else if (strcmp(iface, zwlr_layer_shell_v1_interface.name) == 0) {
        g_wayland_context->layer_shell = (struct zwlr_layer_shell_v1 *)wl_registry_bind(reg, name, &zwlr_layer_shell_v1_interface, 1);
    } else if (strcmp(iface, xdg_wm_base_interface.name) == 0) {
        g_wayland_context->xdg_wm_base = (struct xdg_wm_base *)wl_registry_bind(reg, name, &xdg_wm_base_interface, 1);
        if (g_wayland_context->xdg_wm_base) {
            xdg_wm_base_add_listener(g_wayland_context->xdg_wm_base, &xdg_wm_base_listener, NULL);
        }
    } else if (strcmp(iface, zxdg_output_manager_v1_interface.name) == 0) {
        g_xdg_output_manager = wl_registry_bind(reg, name, &zxdg_output_manager_v1_interface, 3);
    } else if (strcmp(iface, wl_output_interface.name) == 0) {
        if (g_output_count < MAX_OUTPUTS) {
            g_outputs[g_output_count].name = name;
            g_outputs[g_output_count].wl_output = wl_registry_bind(reg, name, &wl_output_interface, 2);
            wl_output_add_listener(g_outputs[g_output_count].wl_output, &output_listener, NULL);
            g_output_count++;
        }
    } else if (strcmp(iface, zwlr_foreign_toplevel_manager_v1_interface.name) == 0) {
        g_fs_detector.manager = (struct zwlr_foreign_toplevel_manager_v1 *)
            wl_registry_bind(reg, name, &zwlr_foreign_toplevel_manager_v1_interface, 3);
        if (g_fs_detector.manager) {
            zwlr_foreign_toplevel_manager_v1_add_listener(g_fs_detector.manager, &fs_manager_listener, NULL);
            BONGOCAT_LOG_INFO("Foreign toplevel manager bound - using Wayland protocol for fullscreen detection");
        }
    }
}

static void registry_remove(void *data,
                           struct wl_registry *registry,
                           uint32_t name ) {
    UNUSED(data); UNUSED(registry); UNUSED(name);
}

static struct wl_registry_listener reg_listener = {
    .global = registry_global,
    .global_remove = registry_remove
};

// =============================================================================
// MAIN WAYLAND INTERFACE IMPLEMENTATION
// =============================================================================

static bongocat_error_t wayland_setup_protocols(wayland_context_t* ctx, animation_context_t *anim) {
    BONGOCAT_CHECK_NULL(ctx, BONGOCAT_ERROR_INVALID_PARAM);

    if (g_wayland_context && g_wayland_context != ctx)  {
        BONGOCAT_LOG_WARNING("Switch wayland context, context was already setup?");
    }
    if (g_animation_context && g_animation_context != anim)  {
        BONGOCAT_LOG_WARNING("Switch animation context, context was already setup?");
    }
    g_wayland_context = ctx;
    g_animation_context = anim;
    // assume g_tracked_toplevels is not used, yet
    if (g_num_toplevels == 0) {
        for (size_t i = 0; i < MAX_TOPLEVELS; ++i) {
            g_tracked_toplevels[i] = NULL;
        }
    }
    // read-only config
    const config_t* const current_config = ctx->_local_copy_config;
    assert(current_config);

    struct wl_registry *registry = wl_display_get_registry(ctx->display);
    if (!registry) {
        BONGOCAT_LOG_ERROR("Failed to get Wayland registry");
        return BONGOCAT_ERROR_WAYLAND;
    }

    wl_registry_add_listener(registry, &reg_listener, NULL);
    wl_display_roundtrip(ctx->display);

    if (g_xdg_output_manager) {
        for (size_t i = 0; i < g_output_count; ++i) {
            g_outputs[i].xdg_output = zxdg_output_manager_v1_get_xdg_output(g_xdg_output_manager, g_outputs[i].wl_output);
            zxdg_output_v1_add_listener(g_outputs[i].xdg_output, &xdg_output_listener, &g_outputs[i]);
        }

        // Wait for all xdg_output events
        wl_display_roundtrip(ctx->display);
    }

    ctx->output = NULL;
    if (current_config->output_name) {
        for (size_t i = 0; i < g_output_count; ++i) {
            if (g_outputs[i].name_received &&
                strcmp(g_outputs[i].name_str, current_config->output_name) == 0) {
                ctx->output = g_outputs[i].wl_output;
                BONGOCAT_LOG_INFO("Matched output: %s", g_outputs[i].name_str);
                break;
            }
        }

        if (!ctx->output) {
            bongocat_log_error("Could not find output named '%s', defaulting to first output",
                               current_config->output_name);
        }
    }

    // Fallback
    if (!ctx->output && g_output_count > 0) {
        ctx->output = g_outputs[0].wl_output;
        BONGOCAT_LOG_WARNING("Falling back to first output");
    }

    if (!ctx->compositor || !ctx->shm || !ctx->layer_shell) {
        BONGOCAT_LOG_ERROR("Missing required Wayland protocols");
        wl_registry_destroy(registry);
        return BONGOCAT_ERROR_WAYLAND;
    }

    // Configure screen dimensions
    int screen_width = DEFAULT_SCREEN_WIDTH;
    if (ctx->output) {
        wl_display_roundtrip(ctx->display);
        if (g_screen_info.screen_width > 0) {
            BONGOCAT_LOG_INFO("Detected screen width: %d", g_screen_info.screen_width);
            screen_width = g_screen_info.screen_width;
        } else {
            BONGOCAT_LOG_WARNING("Using default screen width: %d", DEFAULT_SCREEN_WIDTH);
            screen_width = DEFAULT_SCREEN_WIDTH;
        }
    } else {
        BONGOCAT_LOG_WARNING("No output found, using default screen width: %d", DEFAULT_SCREEN_WIDTH);
        screen_width = DEFAULT_SCREEN_WIDTH;
    }
    ctx->_screen_width = screen_width;

    wl_registry_destroy(registry);
    return BONGOCAT_SUCCESS;
}

static bongocat_error_t wayland_setup_surface(wayland_context_t* ctx) {
    BONGOCAT_CHECK_NULL(ctx, BONGOCAT_ERROR_INVALID_PARAM);
    // read-only config
    const config_t* const current_config = ctx->_local_copy_config;
    assert(current_config);

    ctx->surface = wl_compositor_create_surface(ctx->compositor);
    if (!ctx->surface) {
        BONGOCAT_LOG_ERROR("Failed to create surface");
        return BONGOCAT_ERROR_WAYLAND;
    }

    ctx->layer_surface = zwlr_layer_shell_v1_get_layer_surface(ctx->layer_shell, ctx->surface, ctx->output,
                                                      ZWLR_LAYER_SHELL_V1_LAYER_OVERLAY,
                                                      "bongocat-overlay");

    if (!ctx->layer_surface) {
        bongocat_log_error("Failed to create layer surface");
        return BONGOCAT_ERROR_WAYLAND;
    }

    // Configure layer surface
    uint32_t anchor = ZWLR_LAYER_SURFACE_V1_ANCHOR_LEFT | ZWLR_LAYER_SURFACE_V1_ANCHOR_RIGHT;
    switch (current_config->overlay_position) {
        case POSITION_TOP:
            anchor |= ZWLR_LAYER_SURFACE_V1_ANCHOR_TOP;
            break;
        case POSITION_BOTTOM:
            anchor |= ZWLR_LAYER_SURFACE_V1_ANCHOR_BOTTOM;
            break;
        default:
            BONGOCAT_LOG_ERROR("Invalid overlay_position %d for layer surface, set to top (default)");
            anchor |= ZWLR_LAYER_SURFACE_V1_ANCHOR_TOP;
            break;
    }
    
    zwlr_layer_surface_v1_set_anchor(ctx->layer_surface, anchor);
    zwlr_layer_surface_v1_set_size(ctx->layer_surface, 0, current_config->bar_height);
    zwlr_layer_surface_v1_set_exclusive_zone(ctx->layer_surface, -1);
    zwlr_layer_surface_v1_set_keyboard_interactivity(ctx->layer_surface,
                                                     ZWLR_LAYER_SURFACE_V1_KEYBOARD_INTERACTIVITY_NONE);
    zwlr_layer_surface_v1_add_listener(ctx->layer_surface, &layer_listener, NULL);

    // Make surface click-through
    struct wl_region *input_region = wl_compositor_create_region(ctx->compositor);
    if (input_region) {
        wl_surface_set_input_region(ctx->surface, input_region);
        wl_region_destroy(input_region);
    }

    wl_surface_commit(ctx->surface);
    return BONGOCAT_SUCCESS;
}

static bongocat_error_t wayland_setup_buffer(wayland_context_t* ctx) {
    BONGOCAT_CHECK_NULL(ctx, BONGOCAT_ERROR_INVALID_PARAM);
    // read-only config
    const config_t* const current_config = ctx->_local_copy_config;
    assert(current_config);

    off_t size = ctx->_screen_width * current_config->bar_height * RGBA_CHANNELS;
    if (size <= 0) {
        BONGOCAT_LOG_ERROR("Invalid buffer size: %d", size);
        return BONGOCAT_ERROR_WAYLAND;
    }

    const int fd = create_shm(size);
    if (fd < 0) {
        return BONGOCAT_ERROR_WAYLAND;
    }

    assert(size >= 0 && (size_t)size <= SIZE_MAX);
    ctx->pixels_size = size;
    ctx->pixels = (uint8_t *)mmap(NULL, ctx->pixels_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (ctx->pixels == MAP_FAILED) {
        BONGOCAT_LOG_ERROR("Failed to map shared memory: %s", strerror(errno));
        close(fd);
        return BONGOCAT_ERROR_MEMORY;
    }

    assert(size <= INT32_MAX);
    struct wl_shm_pool *pool = wl_shm_create_pool(ctx->shm, fd, (int32_t)size);
    if (!pool) {
        BONGOCAT_LOG_ERROR("Failed to create shared memory pool");
        munmap(ctx->pixels, size);
        ctx->pixels = NULL;
        close(fd);
        return BONGOCAT_ERROR_WAYLAND;
    }

    ctx->buffer = wl_shm_pool_create_buffer(pool, 0, ctx->_screen_width,
                                      current_config->bar_height,
                                      ctx->_screen_width * RGBA_CHANNELS,
                                      WL_SHM_FORMAT_ARGB8888);
    if (!ctx->buffer) {
        BONGOCAT_LOG_ERROR("Failed to create buffer");
        wl_shm_pool_destroy(pool);
        munmap(ctx->pixels, size);
        ctx->pixels = NULL;
        close(fd);
        return BONGOCAT_ERROR_WAYLAND;
    }

    wl_shm_pool_destroy(pool);
    close(fd);
    return BONGOCAT_SUCCESS;
}

bongocat_error_t wayland_init(wayland_context_t* ctx, const config_t *config, animation_context_t *anim) {
    BONGOCAT_CHECK_NULL(ctx, BONGOCAT_ERROR_INVALID_PARAM);
    BONGOCAT_CHECK_NULL(config, BONGOCAT_ERROR_INVALID_PARAM);
    BONGOCAT_CHECK_NULL(anim, BONGOCAT_ERROR_INVALID_PARAM);

    ctx->display = NULL;
    ctx->compositor = NULL;
    ctx->shm = NULL;
    ctx->layer_shell = NULL;
    ctx->xdg_wm_base = NULL;
    ctx->output = NULL;
    ctx->surface = NULL;
    ctx->buffer = NULL;
    ctx->layer_surface = NULL;
    ctx->pixels = NULL;
    atomic_store(&ctx->configured, false);
    ctx->_screen_width = DEFAULT_SCREEN_WIDTH;

    // Initialize shared memory for local config
    ctx->_local_copy_config = (config_t *)mmap(NULL, sizeof(config_t), PROT_READ | PROT_WRITE,
                                        MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if (ctx->_local_copy_config == MAP_FAILED) {
        BONGOCAT_LOG_ERROR("Failed to create shared memory for animation system: %s", strerror(errno));
        return BONGOCAT_ERROR_MEMORY;
    }
    wayland_update_config(ctx, config, anim);

    BONGOCAT_LOG_INFO("Initializing Wayland connection");

    ctx->display = wl_display_connect(NULL);
    if (!ctx->display) {
        if (ctx->_local_copy_config && ctx->_local_copy_config != MAP_FAILED) {
            if (ctx->_local_copy_config->output_name) free(ctx->_local_copy_config->output_name);
            ctx->_local_copy_config->output_name = NULL;
            munmap(ctx->_local_copy_config, sizeof(config_t));
            ctx->_local_copy_config = NULL;
        }
        BONGOCAT_LOG_ERROR("Failed to connect to Wayland display");
        return BONGOCAT_ERROR_WAYLAND;
    }

    bongocat_error_t result;
    if ((result = wayland_setup_protocols(ctx, anim)) != BONGOCAT_SUCCESS ||
        (result = wayland_setup_surface(ctx)) != BONGOCAT_SUCCESS ||
        (result = wayland_setup_buffer(ctx)) != BONGOCAT_SUCCESS) {
        wayland_cleanup(ctx);
        return result;
    }

    BONGOCAT_LOG_INFO("Wayland initialization complete (%dx%d buffer)",
                     ctx->_screen_width, ctx->_local_copy_config->bar_height);
    return BONGOCAT_SUCCESS;
}

bongocat_error_t wayland_run(wayland_context_t* ctx, volatile sig_atomic_t *running, int signal_fd, const config_t* config, config_watcher_t* config_watcher, config_reload_callback_t config_reload_callback) {
    BONGOCAT_CHECK_NULL(ctx, BONGOCAT_ERROR_INVALID_PARAM);
    BONGOCAT_CHECK_NULL(running, BONGOCAT_ERROR_INVALID_PARAM);
    BONGOCAT_CHECK_NULL(config_reload_callback, BONGOCAT_ERROR_INVALID_PARAM);
    BONGOCAT_CHECK_NULL(g_wayland_context, BONGOCAT_ERROR_WAYLAND);

    // assume ctx and g_wayland_context are the same for all the wayland listener and registers etc.
    assert(ctx == g_wayland_context);

    BONGOCAT_LOG_INFO("Starting Wayland event loop");

    *running = 1;
    while (*running && ctx->display) {
        // Periodic fullscreen check for fallback detection
        struct timeval now;
        gettimeofday(&now, NULL);
        long elapsed_ms = (now.tv_sec - g_fs_detector.last_check.tv_sec) * 1000 +
                         (now.tv_usec - g_fs_detector.last_check.tv_usec) / 1000;
        
        if (elapsed_ms >= CHECK_INTERVAL_MS) {
            bool new_state = fs_check_status();
            if (new_state != ctx->fullscreen_detected) {
                fs_update_state(new_state);
            }
            g_fs_detector.last_check = now;
        }

        // Handle Wayland events
        const size_t fds_signals_index = 0;
        const size_t fds_config_reload_index = 1;
        const size_t fds_wayland_index = 2;
        const int fds_count = 3;
        struct pollfd fds[3] = {
            { .fd = signal_fd, .events = POLLIN },
            { .fd = config_watcher->reload_efd, .events = POLLIN },
            { .fd = wl_display_get_fd(ctx->display), .events = POLLIN },
        };
        assert(fds_count == LEN_ARRAY(fds));

        while (wl_display_prepare_read(ctx->display) != 0) {
            if (wl_display_dispatch_pending(ctx->display) == -1) {
                BONGOCAT_LOG_ERROR("Failed to dispatch pending events");
                *running = 0;
                return BONGOCAT_ERROR_WAYLAND;
            }
        }


        // check (wayland) pool twice as the FPS
        int timeout_ms = config->fps > 0 ? 1000 / config->fps / 2 : 0;
        timeout_ms = timeout_ms < POOL_MIN_TIMEOUT_MS ? POOL_MIN_TIMEOUT_MS : timeout_ms;
        timeout_ms = timeout_ms > POOL_MAX_TIMEOUT_MS ? POOL_MAX_TIMEOUT_MS : timeout_ms;
        // avoid reloading twice, by signal OR watcher
        bool config_reloaded = false;
        const int poll_result = poll(fds, fds_count, timeout_ms);
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
                            if (config_reload_callback && !config_reloaded) {
                                config_reload_callback();
                                config_reloaded = true;
                            }
                            break;
                        default:
                            BONGOCAT_LOG_WARNING("Received unexpected signal %d", fdsi.ssi_signo);
                            break;
                    }
                }
            }
            if (!*running) {
                // draining pool
                if (fds[fds_config_reload_index].revents & POLLIN) {
                    int attempts = 0;
                    uint64_t u;
                    while (read(config_watcher->reload_efd, &u, sizeof(uint64_t)) == sizeof(uint64_t) && attempts < MAX_ATTEMPTS) {
                        attempts++;
                    }
                }
                wl_display_cancel_read(ctx->display);
                break;
            }

            // reload config event
            if (fds[fds_config_reload_index].revents & POLLIN) {
                BONGOCAT_LOG_DEBUG("Receive reload event");

                uint64_t u;
                while (read(config_watcher->reload_efd, &u, sizeof(uint64_t)) == sizeof(uint64_t)) {
                    if (config_reload_callback && !config_reloaded) {
                        config_reload_callback();
                        config_reloaded = true;
                    }
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
            }

            // wayland events
            if (fds[fds_wayland_index].revents & POLLIN) {
                if (wl_display_read_events(ctx->display) == -1 ||
                    wl_display_dispatch_pending(ctx->display) == -1) {
                    BONGOCAT_LOG_ERROR("Failed to handle Wayland events");
                    *running = 0;
                    return BONGOCAT_ERROR_WAYLAND;
                }
            } else {
                wl_display_cancel_read(ctx->display);
            }

            //BONGOCAT_LOG_VERBOSE("Poll revents: signal=%x, reload=%x, wayland=%x", fds[0].revents, fds[1].revents, fds[2].revents);
        } else if (poll_result == 0) {
            wl_display_cancel_read(ctx->display);
        } else {
            wl_display_cancel_read(ctx->display);
            if (errno != EINTR) {
                BONGOCAT_LOG_ERROR("Poll error: %s", strerror(errno));
                *running = 0;
                return BONGOCAT_ERROR_WAYLAND;
            }
        }

        wl_display_flush(ctx->display);
    }
    *running = 0;

    BONGOCAT_LOG_INFO("Wayland event loop exited");
    return BONGOCAT_SUCCESS;
}

// =============================================================================
// PUBLIC API IMPLEMENTATION
// =============================================================================

int wayland_get_screen_width(void) {
    return g_screen_info.screen_width;
}

void wayland_update_config(wayland_context_t* ctx, const config_t *config, animation_context_t *anim) {
    assert(ctx);
    assert(config);
    assert(ctx->_local_copy_config && ctx->_local_copy_config != MAP_FAILED);

    memcpy(ctx->_local_copy_config, config, sizeof(*config));
    ctx->_local_copy_config->output_name = config->output_name ? strdup(config->output_name) : NULL;

    /// @FIXME: make deep copy of keyboard_devices ?
    // keyboard_devices not used, get rid of out-side reference
    ctx->_local_copy_config->keyboard_devices = NULL;
    ctx->_local_copy_config->num_keyboard_devices = 0;

    /// @NOTE: assume animation has the same local copy as wayland config
    //animation_update_config(anim, config);
    if (atomic_load(&ctx->configured)) {
        draw_bar(ctx, anim);
    }
}

void wayland_cleanup(wayland_context_t* ctx) {
    BONGOCAT_LOG_INFO("Cleaning up Wayland resources");

    // drain pending events
    if (ctx->display) {
        wl_display_flush(ctx->display);
        while (wl_display_dispatch_pending(ctx->display) > 0);
    }

    // First destroy xdg_output objects
    for (size_t i = 0; i < g_output_count; ++i) {
        if (g_outputs[i].xdg_output) {
            BONGOCAT_LOG_DEBUG("Destroying xdg_output %zu", i);
            zxdg_output_v1_destroy(g_outputs[i].xdg_output);
            g_outputs[i].xdg_output = NULL;
        }
    }

    // Then destroy the manager
    if (g_xdg_output_manager) {
        BONGOCAT_LOG_DEBUG("Destroying xdg_output_manager");
        zxdg_output_manager_v1_destroy(g_xdg_output_manager);
        g_xdg_output_manager = NULL;
    }

    // Finally destroy wl_output objects
    for (size_t i = 0; i < g_output_count; ++i) {
        if (g_outputs[i].wl_output) {
            BONGOCAT_LOG_DEBUG("Destroying wl_output %zu", i);
            wl_output_destroy(g_outputs[i].wl_output);
            g_outputs[i].wl_output = NULL;
        }
    }
    g_output_count = 0;

    if (ctx->buffer) {
        wl_buffer_destroy(ctx->buffer);
        ctx->buffer = NULL;
    }

    if (ctx->pixels) {
        munmap(ctx->pixels, ctx->pixels_size);
        ctx->pixels = NULL;
    }
    ctx->pixels_size = 0;

    if (ctx->layer_surface) {
        zwlr_layer_surface_v1_destroy(ctx->layer_surface);
        ctx->layer_surface = NULL;
    }

    if (ctx->surface) {
        wl_surface_destroy(ctx->surface);
        ctx->surface = NULL;
    }

    // Note: output is just a reference to one of the outputs[] entries
    // It will be destroyed when we destroy the outputs[] array above
    ctx->output = NULL;

    if (ctx->layer_shell) {
        zwlr_layer_shell_v1_destroy(ctx->layer_shell);
        ctx->layer_shell = NULL;
    }

    if (ctx->xdg_wm_base) {
        xdg_wm_base_destroy(ctx->xdg_wm_base);
        ctx->xdg_wm_base = NULL;
    }

    if (g_fs_detector.manager) {
        zwlr_foreign_toplevel_manager_v1_destroy(g_fs_detector.manager);
        g_fs_detector.manager = NULL;
    }

    if (ctx->shm) {
        wl_shm_destroy(ctx->shm);
        ctx->shm = NULL;
    }

    if (ctx->compositor) {
        wl_compositor_destroy(ctx->compositor);
        ctx->compositor = NULL;
    }

    // assume g_wayland_context for listener and register is the same, clean up register and tracking stuff
    if (g_wayland_context == ctx) {
        for (size_t i = 0; i < g_num_toplevels; ++i) {
            if (g_tracked_toplevels[i]) zwlr_foreign_toplevel_handle_v1_destroy(g_tracked_toplevels[i]);
            g_tracked_toplevels[i] = NULL;
        }
        g_num_toplevels = 0;
        g_wayland_context = NULL;
    }

    if (ctx->display) {
        wl_display_disconnect(ctx->display);
        ctx->display = NULL;
    }

    if (ctx->_local_copy_config && ctx->_local_copy_config != MAP_FAILED) {
        if (ctx->_local_copy_config->output_name) free(ctx->_local_copy_config->output_name);
        ctx->_local_copy_config->output_name = NULL;
        munmap(ctx->_local_copy_config, sizeof(config_t));
        ctx->_local_copy_config = NULL;
    }
    ctx->_screen_width = 0;

    // Reset state
    atomic_store(&ctx->configured, false);
    ctx->fullscreen_detected = false;
    memset(&g_fs_detector, 0, sizeof(g_fs_detector));
    memset(&g_screen_info, 0, sizeof(g_screen_info));

    g_animation_context = NULL;
    
    BONGOCAT_LOG_DEBUG("Wayland cleanup complete");
}

const char* wayland_get_current_layer_name(void) {
    return WAYLAND_LAYER_NAME;
}
