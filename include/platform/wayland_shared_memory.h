#ifndef BONGOCAT_WAYLAND_SHARED_MEMORY_H
#define BONGOCAT_WAYLAND_SHARED_MEMORY_H

#include "graphics/global_animation_session.h"
#include <wayland-client.h>
#include <stdatomic.h>

namespace bongocat::platform::wayland {
    // single-buffer, double-buffer or triple-buffer
    inline static constexpr size_t WAYLAND_NUM_BUFFERS = 1;

    struct wayland_shm_buffer_t;
    void cleanup_shm_buffer(wayland_shm_buffer_t& buffer);

    struct wayland_shm_buffer_t {
        wl_buffer *buffer{nullptr};
        MMapFileBuffer<uint8_t> pixels;
        atomic_bool busy{false};        // 0: free / 1: busy
        atomic_bool pending{false};     // 0/1: a render was requested while busy
        size_t index{0};                  // index track from wayland_shared_memory_t.buffers

        // extra context for listeners
        animation::animation_session_t *_animation_trigger_context{nullptr};



        wayland_shm_buffer_t() = default;
        ~wayland_shm_buffer_t() {
            cleanup_shm_buffer(*this);
        }

        wayland_shm_buffer_t(const wayland_shm_buffer_t&) = delete;
        wayland_shm_buffer_t& operator=(const wayland_shm_buffer_t&) = delete;

        wayland_shm_buffer_t(wayland_shm_buffer_t&& other) noexcept
            : buffer(other.buffer),
              pixels(bongocat::move(other.pixels)),
              index(other.index),
              _animation_trigger_context(other._animation_trigger_context)
        {
            atomic_store(&busy, atomic_load(&other.busy));
            atomic_store(&pending, atomic_load(&other.pending));

            other.buffer = nullptr;
            other.index = 0;
            other._animation_trigger_context = nullptr;
            atomic_store(&other.busy, false);
            atomic_store(&other.pending, false);
        }
        wayland_shm_buffer_t& operator=(wayland_shm_buffer_t&& other) noexcept {
            if (this != &other) {
                buffer = other.buffer;
                pixels = bongocat::move(other.pixels);
                atomic_store(&busy, atomic_load(&other.busy));
                atomic_store(&pending, atomic_load(&other.pending));
                index = other.index;
                _animation_trigger_context = other._animation_trigger_context;

                other.buffer = nullptr;
                other.index = 0;
                other._animation_trigger_context = nullptr;
                atomic_store(&other.busy, false);
                atomic_store(&other.pending, false);
            }
            return *this;
        }
    };

    // Wayland globals
    struct wayland_shared_memory_t {
        wayland_shm_buffer_t buffers[WAYLAND_NUM_BUFFERS];
        int current_buffer_index{0};
        atomic_bool configured{false};



        wayland_shared_memory_t() = default;
        ~wayland_shared_memory_t() {
            atomic_store(&configured, false);
            current_buffer_index = 0;
            for (size_t i = 0; i < WAYLAND_NUM_BUFFERS; i++) {
                cleanup_shm_buffer(buffers[i]);
            }
        }

        wayland_shared_memory_t(const wayland_shared_memory_t&) = delete;
        wayland_shared_memory_t& operator=(const wayland_shared_memory_t&) = delete;

        wayland_shared_memory_t(wayland_shared_memory_t&& other) noexcept
            : buffers{}
        {
            atomic_store(&configured, false);
            current_buffer_index = other.current_buffer_index;
            // Manually move each buffer
            for (size_t i = 0; i < WAYLAND_NUM_BUFFERS; i++) {
                buffers[i] = bongocat::move(other.buffers[i]);
            }
            atomic_store(&configured, atomic_load(&other.configured));

            other.current_buffer_index = 0;
            atomic_store(&other.configured, false);
        }
        wayland_shared_memory_t& operator=(wayland_shared_memory_t&& other) noexcept {
            if (this != &other) {
                atomic_store(&configured, false);
                current_buffer_index = other.current_buffer_index;
                for (size_t i = 0; i < WAYLAND_NUM_BUFFERS; ++i) {
                    buffers[i] = move(other.buffers[i]);
                }
                atomic_store(&configured, atomic_load(&other.configured));

                other.current_buffer_index = 0;
                atomic_store(&other.configured, false);
            }
            return *this;
        }
    };

    inline void cleanup_shm_buffer(wayland_shm_buffer_t& buffer) {
        atomic_store(&buffer.pending, false);
        atomic_store(&buffer.busy, true);
        if (buffer.buffer) wl_buffer_destroy(buffer.buffer);
        buffer.buffer = nullptr;
        release_allocated_mmap_file_buffer(buffer.pixels);
        atomic_store(&buffer.busy, false);
        buffer.index = 0;
        buffer._animation_trigger_context = nullptr;
    }
}

#endif // BONGOCAT_WAYLAND_SHARED_MEMORY_H