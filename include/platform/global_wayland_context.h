#ifndef BONGOCAT_GLOBAL_WAYLAND_CONTEXT_CONTEXT_H
#define BONGOCAT_GLOBAL_WAYLAND_CONTEXT_CONTEXT_H

#include "platform/wayland-protocols.hpp"

#include "wayland_context.h"
#include "graphics/animation_context.h"
#include "graphics/animation_event_context.h"
#include <sys/time.h>

namespace bongocat::platform {
    inline static constexpr size_t MAX_TOPLEVELS = 64;
    inline static constexpr size_t MAX_OUTPUTS = 8;               // Maximum monitor outputs to store
    inline static constexpr size_t OUTPUT_NAME_SIZE = 128;

    // =============================================================================
    // FULLSCREEN DETECTION MODULE
    // =============================================================================

    struct fullscreen_detector_t {
        struct zwlr_foreign_toplevel_manager_v1 *manager{nullptr};
        bool has_fullscreen_toplevel{false};
        timeval last_check{};
    };

    // =============================================================================
    // SCREEN DIMENSION MANAGEMENT
    // =============================================================================

    struct screen_info_t {
        int screen_width{0};
        int screen_height{0};
        int transform{0};
        int raw_width{0};
        int raw_height{0};
        bool mode_received{false};
        bool geometry_received{false};
    };


    // Output monitor reference structure
    struct output_ref_t {
        struct wl_output *wl_output{nullptr};
        zxdg_output_v1 *xdg_output{nullptr};
        uint32_t name{0};                         // Registry name
        char name_str[OUTPUT_NAME_SIZE]{};        // From xdg-output
        bool name_received{false};
    };

    struct wayland_listeners_context_t {
        wayland_context_t* wayland_context{nullptr};
        animation::animation_context_t* animation_context{nullptr};
        animation::animation_trigger_context_t* animation_trigger_context{nullptr};

        struct zwlr_foreign_toplevel_handle_v1* tracked_toplevels[MAX_TOPLEVELS]{};
        size_t num_toplevels{0};

        output_ref_t outputs[MAX_OUTPUTS];
        size_t output_count{0};
        zxdg_output_manager_v1 *xdg_output_manager{nullptr};

        fullscreen_detector_t fs_detector;

        screen_info_t screen_info;
    };
}

#endif
