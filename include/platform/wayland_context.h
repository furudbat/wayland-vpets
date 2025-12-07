#ifndef BONGOCAT_WAYLAND_CONTEXT_H
#define BONGOCAT_WAYLAND_CONTEXT_H

struct zwlr_layer_shell_v1;
struct zwlr_layer_surface_v1;
#include "platform/wayland-protocols.hpp"

#include "wayland_shared_memory.h"
#include "config/config.h"
#include <wayland-client.h>
#include <stdatomic.h>


namespace bongocat::platform::wayland {
    inline static constexpr int MAX_ATTEMPTS = 4096;

    struct wayland_context_t;
    // Cleanup Wayland resources
    void cleanup_wayland_context(wayland_context_t& ctx);

    enum class bar_visibility_t : bool { Hide = false, Show = true };

    struct screen_info_t;

    struct wayland_context_t {
        wl_display *display{nullptr};
        wl_compositor *compositor{nullptr};
        wl_shm *shm{nullptr};
        zwlr_layer_shell_v1 *layer_shell{nullptr};
        struct xdg_wm_base *xdg_wm_base{nullptr};
        wl_output *output{nullptr};
        wl_surface *surface{nullptr};
        zwlr_layer_surface_v1 *layer_surface{nullptr};

        // local copy from other thread, update after reload (shared memory)
        MMapMemory<config::config_t> _local_copy_config;
        MMapMemory<wayland_shared_memory_t> ctx_shm;
        bar_visibility_t bar_visibility {bar_visibility_t::Show};

        int32_t _bar_height{0};
        int32_t _screen_width{0};
        char* _output_name_str{nullptr};                  // ref to existing name in output, Will default to automatic one if kept null
        bool _fullscreen_detected{false};
        screen_info_t *_screen_info{nullptr};

        // frame done callback data
        wl_callback *_frame_cb{nullptr};
        Mutex _frame_cb_lock;
        atomic_bool _frame_pending{false};
        atomic_bool _redraw_after_frame{false};
        timestamp_ms_t _last_frame_timestamp_ms{0};



        wayland_context_t() = default;
        ~wayland_context_t() {
            cleanup_wayland_context(*this);
        }

        wayland_context_t(const wayland_context_t&) = delete;
        wayland_context_t& operator=(const wayland_context_t&) = delete;
        wayland_context_t(wayland_context_t&& other) noexcept = delete;
        wayland_context_t& operator=(wayland_context_t&& other) noexcept = delete;
    };

    inline void cleanup_wayland_context(wayland_context_t& ctx) {
        if (ctx.ctx_shm.ptr && ctx.ctx_shm.ptr != MAP_FAILED) {
            atomic_store(&ctx.ctx_shm->configured, false);
        }

        // drain pending events
        if (ctx.display) {
            wl_display_flush(ctx.display);
            wl_display_roundtrip(ctx.display);
            int attempts = 0;
            while (wl_display_dispatch_pending(ctx.display) > 0 && attempts <= MAX_ATTEMPTS) {
                attempts++;
            }
            if (attempts >= MAX_ATTEMPTS && wl_display_dispatch_pending(ctx.display) > 0) {
                BONGOCAT_LOG_ERROR("Cant fully drain wayland display, max attempts: %i", attempts);
            }
        }

        // release frame.done handler
        atomic_store(&ctx._frame_pending, false);
        atomic_store(&ctx._redraw_after_frame, false);
        // ctx._frame_cb_lock should be unlocked
        if (ctx._frame_cb) wl_callback_destroy(ctx._frame_cb);
        ctx._frame_cb = nullptr;
        ctx._last_frame_timestamp_ms = 0;

        // surfaces
        if (ctx.layer_surface) {
            zwlr_layer_surface_v1_destroy(ctx.layer_surface);
            ctx.layer_surface = nullptr;
        }
        if (ctx.surface) {
            wl_surface_destroy(ctx.surface);
            ctx.surface = nullptr;
        }

        if (ctx.layer_shell) {
            zwlr_layer_shell_v1_destroy(ctx.layer_shell);
            ctx.layer_shell = nullptr;
        }
        if (ctx.xdg_wm_base) {
            xdg_wm_base_destroy(ctx.xdg_wm_base);
            ctx.xdg_wm_base = nullptr;
        }
        if (ctx.shm) {
            wl_shm_destroy(ctx.shm);
            ctx.shm = nullptr;
        }
        if (ctx.compositor) {
            wl_compositor_destroy(ctx.compositor);
            ctx.compositor = nullptr;
        }

        // release shm
        if (ctx.ctx_shm.ptr && ctx.ctx_shm.ptr != MAP_FAILED) {
            for (size_t i = 0; i < WAYLAND_NUM_BUFFERS; i++) {
                cleanup_shm_buffer(ctx.ctx_shm->buffers[i]);
            }
        }
        release_allocated_mmap_memory(ctx.ctx_shm);
        release_allocated_mmap_memory(ctx._local_copy_config);

        if (ctx.display) {
            wl_display_disconnect(ctx.display);
            ctx.display = nullptr;
        }


        // Note: output is just a reference to one of the outputs[] entries
        // It will be destroyed when we destroy the outputs[] array above
        ctx.output = nullptr;

        // Reset state
        ctx.display = nullptr;
        ctx.compositor = nullptr;
        ctx.shm = nullptr;
        ctx.layer_shell = nullptr;
        ctx.xdg_wm_base = nullptr;
        ctx.output = nullptr;
        ctx.surface = nullptr;
        ctx.layer_surface = nullptr;
        ctx._output_name_str = nullptr;
        ctx._frame_pending = false;
        ctx._redraw_after_frame = false;
        ctx._bar_height = 0;
        ctx._screen_width = 0;
        ctx._fullscreen_detected = false;
        ctx._screen_info = nullptr;
    }
}

#endif // BONGOCAT_WAYLAND_CONTEXT_H