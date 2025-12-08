#ifndef BONGOCAT_WAYLAND_CALLBACKS_H
#define BONGOCAT_WAYLAND_CALLBACKS_H

#include "wayland-protocols.hpp"

#include <sys/types.h>
#include <wayland-client.h>
#include <sys/signalfd.h>

namespace bongocat::platform::wayland::details {

    // =============================================================================
    // ZXDG LISTENER IMPLEMENTATION
    // =============================================================================

    extern void handle_xdg_output_name(void *data, zxdg_output_v1 *xdg_output, const char *name);

    extern void handle_xdg_output_logical_position(void *data, zxdg_output_v1 *xdg_output, int32_t x, int32_t y);
    extern void handle_xdg_output_logical_size(void *data, zxdg_output_v1 *xdg_output, int32_t width, int32_t height);
    extern void handle_xdg_output_done(void *data, zxdg_output_v1 *xdg_output);
    extern void handle_xdg_output_description(void *data, zxdg_output_v1 *xdg_output, const char *description);

    /// @NOTE: xdg_output_listeners MUST pass data as output_ref_t, see zxdg_output_v1_add_listener
    inline static constexpr zxdg_output_v1_listener xdg_output_listener = {
        .logical_position = handle_xdg_output_logical_position,
        .logical_size = handle_xdg_output_logical_size,
        .done = handle_xdg_output_done,
        .name = handle_xdg_output_name,
        .description = handle_xdg_output_description
    };


    // =============================================================================
    // FULLSCREEN DETECTION IMPLEMENTATION
    // =============================================================================

    // Foreign toplevel protocol event handlers
    extern void fs_handle_toplevel_state(void *data, zwlr_foreign_toplevel_handle_v1 *handle,
                                         wl_array *state);

    extern void fs_handle_toplevel_closed(void *data, zwlr_foreign_toplevel_handle_v1 *handle);

    // Minimal event handlers for unused events
    extern void fs_handle_title(void *data, zwlr_foreign_toplevel_handle_v1 *handle, const char *title);
    extern void fs_handle_app_id(void *data, zwlr_foreign_toplevel_handle_v1 *handle, const char *app_id);
    extern void fs_handle_output_enter(void *data, zwlr_foreign_toplevel_handle_v1 *handle, wl_output *output);
    extern void fs_handle_output_leave(void *data, zwlr_foreign_toplevel_handle_v1 *handle, wl_output *output);
    extern void fs_handle_done(void *data, zwlr_foreign_toplevel_handle_v1 *handle);
    extern void fs_handle_parent(void *data, zwlr_foreign_toplevel_handle_v1 *handle, zwlr_foreign_toplevel_handle_v1 *parent);

    /// @NOTE: fs_toplevel_listener MUST pass data as output_ref_t, see zwlr_foreign_toplevel_handle_v1_add_listener
    inline static constexpr zwlr_foreign_toplevel_handle_v1_listener fs_toplevel_listener = {
        .title = fs_handle_title,
        .app_id = fs_handle_app_id,
        .output_enter = fs_handle_output_enter,
        .output_leave = fs_handle_output_leave,
        .state = fs_handle_toplevel_state,
        .done = fs_handle_done,
        .closed = fs_handle_toplevel_closed,
        .parent = fs_handle_parent,
    };

    extern void fs_update_state_fallback(wayland_session_t& ctx);

    extern void fs_handle_manager_toplevel(void *data, zwlr_foreign_toplevel_manager_v1 *manager,
                                          zwlr_foreign_toplevel_handle_v1 *toplevel);
    extern void fs_handle_manager_finished(void *data, zwlr_foreign_toplevel_manager_v1 *manager);

    /// @NOTE: fs_manager_listeners MUST pass data as wayland_listeners_context_t, see zwlr_foreign_toplevel_manager_v1_add_listener
    inline static constexpr zwlr_foreign_toplevel_manager_v1_listener fs_manager_listener = {
        .toplevel = fs_handle_manager_toplevel,
        .finished = fs_handle_manager_finished,
    };

    // =============================================================================
    // WAYLAND EVENT HANDLERS
    // =============================================================================

    extern void layer_surface_configure(void *data,
                                       zwlr_layer_surface_v1 *ls,
                                       uint32_t serial, uint32_t w, uint32_t h);
    extern void layer_surface_closed(void *data, zwlr_layer_surface_v1 *ls);

    /// @NOTE: layer_listeners MUST pass data as wayland_listeners_context_t, see zwlr_layer_surface_v1_add_listener
    inline static constexpr zwlr_layer_surface_v1_listener layer_listener = {
        .configure = layer_surface_configure,
        .closed = layer_surface_closed,
    };


    extern void xdg_wm_base_ping(void *data, xdg_wm_base *wm_base, uint32_t serial);

    /// @NOTE: xdg_wm_base_listeners MUST pass data as wayland_listeners_context_t, see xdg_wm_base_add_listener
    inline static constexpr xdg_wm_base_listener xdg_wm_base_listener = {
        .ping = xdg_wm_base_ping,
    };

    extern void output_geometry(void *data,
                                wl_output *wl_output,
                                int32_t x,
                                int32_t y,
                                int32_t physical_width,
                                int32_t physical_height,
                                int32_t subpixel,
                                const char *make,
                                const char *model,
                                int32_t transform);
    extern void output_mode(void *data ,
                            wl_output *wl_output,
                            uint32_t flags, int32_t width, int32_t height,
                            int32_t refresh);
    extern void output_done(void *data, wl_output *wl_output);
    extern void output_scale(void *data,
                            wl_output *wl_output,
                            int32_t factor);
    extern void output_name(void *data, wl_output *wl_output, const char *name);
    extern void output_description(void *data, wl_output *wl_output, const char *name);

    /// @NOTE: output_listeners MUST pass data as wayland_listeners_context_t, see wl_output_add_listener
    inline static constexpr wl_output_listener output_listener = {
        .geometry = output_geometry,
        .mode = output_mode,
        .done = output_done,
        .scale = output_scale,
        .name = output_name,
        .description = output_description,
    };

    // =============================================================================
    // WAYLAND PROTOCOL REGISTRY
    // =============================================================================

    extern void registry_global(void *data , wl_registry *reg,
                                uint32_t name, const char *iface,
                                uint32_t ver);
    extern void registry_remove(void *data,
                               wl_registry *registry,
                               uint32_t name);

    /// @NOTE: reg_listeners MUST pass data as wayland_listeners_context_t, see zxdg_output_v1_add_listener
    inline static constexpr wl_registry_listener reg_listener = {
        .global = registry_global,
        .global_remove = registry_remove
    };

    // =============================================================================
    // FRAME DRAWING HANDLER
    // =============================================================================

    extern void buffer_release(void *data, wl_buffer *buffer);

    /// @NOTE: buffer_listeners MUST pass data as wayland_shm_buffer_t, see wl_buffer_add_listener
    inline static constexpr wl_buffer_listener buffer_listener = {
        .release = buffer_release,
    };

    extern void frame_done(void *data, wl_callback *cb, uint32_t time);

    /// @NOTE: frame_listeners MUST pass data as wayland_listeners_context_t, see wl_callback_add_listener
    inline static constexpr wl_callback_listener frame_listener = {
        .done = frame_done
    };

    void wayland_handle_output_reconnect(struct wl_output *new_output, uint32_t registry_name, const char *output_name);
}

#endif