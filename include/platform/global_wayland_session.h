#ifndef BONGOCAT_GLOBAL_WAYLAND_CONTEXT_CONTEXT_H
#define BONGOCAT_GLOBAL_WAYLAND_CONTEXT_CONTEXT_H

#include "platform/wayland-protocols.hpp"

#include "wayland_context.h"
#include "graphics/animation_context.h"
#include "graphics/global_animation_session.h"
#include <sys/time.h>

namespace bongocat::platform::wayland {
    // max. windows to track for fullscreen detection
    inline static constexpr size_t MAX_TOP_LEVELS = 128;
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

    struct wayland_session_t;
    void cleanup_wayland(wayland_session_t& ctx);

    struct wayland_session_t {
        wayland_context_t wayland_context;
        animation::animation_session_t* animation_trigger_context{nullptr};

        struct zwlr_foreign_toplevel_handle_v1* tracked_toplevels[MAX_TOP_LEVELS]{};
        size_t num_toplevels{0};

        output_ref_t outputs[MAX_OUTPUTS];
        size_t output_count{0};
        zxdg_output_manager_v1 *xdg_output_manager{nullptr};

        fullscreen_detector_t fs_detector;

        screen_info_t screen_info;
        atomic_bool ready{false};



        wayland_session_t() {
            for (size_t i = 0; i < MAX_TOP_LEVELS; i++) {
                tracked_toplevels[i] = nullptr;
            }
            for (size_t i = 0; i < MAX_OUTPUTS; i++) {
                outputs[i] = {};
            }
        }
        ~wayland_session_t() {
            cleanup_wayland(*this);
        }

        wayland_session_t(const wayland_session_t&) = delete;
        wayland_session_t& operator=(const wayland_session_t&) = delete;

         wayland_session_t(wayland_session_t&& other) noexcept
            : wayland_context(bongocat::move(other.wayland_context)),
              animation_trigger_context(other.animation_trigger_context),
              num_toplevels(other.num_toplevels),
              output_count(other.output_count),
              xdg_output_manager(other.xdg_output_manager),
              fs_detector(other.fs_detector),
              screen_info(other.screen_info)
        {
            for (size_t i = 0; i < MAX_TOP_LEVELS; ++i) {
                tracked_toplevels[i] = other.tracked_toplevels[i];
                other.tracked_toplevels[i] = nullptr;
            }
            for (size_t i = 0; i < MAX_OUTPUTS; ++i) {
                outputs[i] = other.outputs[i];
                other.outputs[i] = {};
            }
            atomic_store(&ready, atomic_load(&other.ready));

            atomic_store(&other.ready, false);
            other.animation_trigger_context = nullptr;
            other.num_toplevels = 0;
            other.output_count = 0;
            other.xdg_output_manager = nullptr;
            other.fs_detector = {};
            other.screen_info = {};
        }
        wayland_session_t& operator=(wayland_session_t&& other) noexcept {
            if (this != &other) {
                atomic_store(&ready, false);
                cleanup_wayland(*this);

                wayland_context = bongocat::move(other.wayland_context);
                animation_trigger_context = other.animation_trigger_context;
                num_toplevels = other.num_toplevels;
                output_count = other.output_count;
                xdg_output_manager = other.xdg_output_manager;
                fs_detector = other.fs_detector;
                screen_info = other.screen_info;

                for (size_t i = 0; i < MAX_TOP_LEVELS; ++i) {
                    tracked_toplevels[i] = other.tracked_toplevels[i];
                    other.tracked_toplevels[i] = nullptr;
                }
                for (size_t i = 0; i < MAX_OUTPUTS; ++i) {
                    outputs[i] = other.outputs[i];
                    other.outputs[i] = {};
                }

                atomic_store(&ready, atomic_load(&other.ready));

                atomic_store(&other.ready, false);
                other.animation_trigger_context = nullptr;
                other.num_toplevels = 0;
                other.output_count = 0;
                other.xdg_output_manager = nullptr;
                other.fs_detector = {};
                other.screen_info = {};
            }
            return *this;
        }
    };

    inline void cleanup_wayland(wayland_session_t& ctx) {
        atomic_store(&ctx.ready, false);

        // First destroy xdg_output objects
        for (size_t i = 0; i < ctx.output_count; ++i) {
            if (ctx.outputs[i].xdg_output) {
                zxdg_output_v1_destroy(ctx.outputs[i].xdg_output);
                ctx.outputs[i].xdg_output = nullptr;
            }
        }

        // Then destroy the manager
        if (ctx.xdg_output_manager) {
            zxdg_output_manager_v1_destroy(ctx.xdg_output_manager);
            ctx.xdg_output_manager = nullptr;
        }

        // Finally destroy wl_output objects
        for (size_t i = 0; i < ctx.output_count; ++i) {
            if (ctx.outputs[i].wl_output) {
                wl_output_destroy(ctx.outputs[i].wl_output);
                ctx.outputs[i].wl_output = nullptr;
            }
            ctx.outputs[i] = {};
            ctx.outputs[i].wl_output = nullptr;
        }
        ctx.output_count = 0;

        if (ctx.fs_detector.manager) {
            zwlr_foreign_toplevel_manager_v1_destroy(ctx.fs_detector.manager);
            ctx.fs_detector.manager = nullptr;
        }

        for (size_t i = 0; i < ctx.num_toplevels; ++i) {
            if (ctx.tracked_toplevels[i]) zwlr_foreign_toplevel_handle_v1_destroy(ctx.tracked_toplevels[i]);
            ctx.tracked_toplevels[i] = nullptr;
        }
        ctx.num_toplevels = 0;

        ctx.fs_detector = {};
        ctx.screen_info = {};

        // clean up wayland context
        cleanup_wayland_context(ctx.wayland_context);

        ctx.animation_trigger_context = nullptr;
    }
}

#endif
