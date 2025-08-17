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
    static inline constexpr int MAX_ATTEMPTS = 2048;

    struct wayland_context_t;
    void cleanup_wayland_context(wayland_context_t& ctx);

    struct wayland_context_t {
        wl_display *display{nullptr};
        wl_compositor *compositor{nullptr};
        wl_shm *shm{nullptr};
        zwlr_layer_shell_v1 *layer_shell{nullptr};
        struct xdg_wm_base *xdg_wm_base{nullptr};
        wl_output *output{nullptr};
        wl_surface *surface{nullptr};
        zwlr_layer_surface_v1 *layer_surface{nullptr};

        // @NOTE: variable can be shared between child process and parent (see mmap)
        MMapMemory<wayland_shared_memory_t> ctx_shm;

        // local copy from other thread, update after reload (shared memory)
        MMapMemory<config::config_t> _local_copy_config;
        int _screen_width{0};
        char* _output_name_str{nullptr};                  // ref to existing name in output, Will default to automatic one if kept null
        bool _fullscreen_detected{false};

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

        wayland_context_t(wayland_context_t&& other) noexcept
            : display(other.display),
              compositor(other.compositor),
              shm(other.shm),
              layer_shell(other.layer_shell),
              xdg_wm_base(other.xdg_wm_base),
              output(other.output),
              surface(other.surface),
              layer_surface(other.layer_surface),
              ctx_shm(bongocat::move(other.ctx_shm)),
              _local_copy_config(bongocat::move(other._local_copy_config)),
              _screen_width(other._screen_width),
              _output_name_str(other._output_name_str),
              _fullscreen_detected(other._fullscreen_detected),
              _frame_cb(other._frame_cb),
              _frame_cb_lock(bongocat::move(other._frame_cb_lock)),
              _frame_pending(other._frame_pending.load()),
              _redraw_after_frame(other._redraw_after_frame.load()),
              _last_frame_timestamp_ms(other._last_frame_timestamp_ms)
        {
            other.display = nullptr;
            other.compositor = nullptr;
            other.shm = nullptr;
            other.layer_shell = nullptr;
            other.xdg_wm_base = nullptr;
            other.output = nullptr;
            other.surface = nullptr;
            other.layer_surface = nullptr;
            other._output_name_str = nullptr;
            other._frame_cb = nullptr;
            other._frame_pending = false;
            other._redraw_after_frame = false;
            other._screen_width = 0;
            other._fullscreen_detected = false;
            other._last_frame_timestamp_ms = 0;
        }
        wayland_context_t& operator=(wayland_context_t&& other) noexcept {
            if (this != &other) {
                this->~wayland_context_t(); // cleanup current

                display = other.display;
                compositor = other.compositor;
                shm = other.shm;
                layer_shell = other.layer_shell;
                xdg_wm_base = other.xdg_wm_base;
                output = other.output;
                surface = other.surface;
                layer_surface = other.layer_surface;

                ctx_shm = bongocat::move(other.ctx_shm);
                _local_copy_config = bongocat::move(other._local_copy_config);

                _screen_width = other._screen_width;
                _output_name_str = other._output_name_str;
                _fullscreen_detected = other._fullscreen_detected;

                _frame_cb = other._frame_cb;
                _frame_cb_lock = bongocat::move(other._frame_cb_lock);
                _frame_pending.store(other._frame_pending.load());
                _redraw_after_frame.store(other._redraw_after_frame.load());
                _last_frame_timestamp_ms = other._last_frame_timestamp_ms;

                // reset moved-from
                other.display = nullptr;
                other.compositor = nullptr;
                other.shm = nullptr;
                other.layer_shell = nullptr;
                other.xdg_wm_base = nullptr;
                other.output = nullptr;
                other.surface = nullptr;
                other.layer_surface = nullptr;
                other._output_name_str = nullptr;
                other._frame_cb = nullptr;
                other._frame_pending = false;
                other._redraw_after_frame = false;
                other._screen_width = 0;
                other._fullscreen_detected = false;
                other._last_frame_timestamp_ms = 0;
            }
            return *this;
        }
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
        ctx._frame_pending.store(false);
        ctx._redraw_after_frame.store(false);
        ctx._frame_cb_lock._unlock();
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
        ctx._screen_width = 0;
        ctx._fullscreen_detected = false;
    }
}

#endif // BONGOCAT_WAYLAND_CONTEXT_H