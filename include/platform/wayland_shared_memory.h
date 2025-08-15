#ifndef BONGOCAT_WAYLAND_SHARED_MEMORY_H
#define BONGOCAT_WAYLAND_SHARED_MEMORY_H

#include "graphics/animation_event_context.h"
#include <wayland-client.h>
#include <stdatomic.h>

namespace bongocat::platform {
    inline static constexpr size_t WAYLAND_NUM_BUFFERS = 1;

    struct wayland_shm_buffer_t {
        wl_buffer *buffer{nullptr};
        MMapFileBuffer<uint8_t> pixels;
        atomic_bool busy{false};        // 0 free / 1 busy
        atomic_bool pending{false};     // 0/1: a render was requested while busy
        int index{0};

        // extra context for listeners
        animation::animation_trigger_context_t *_animation_trigger_context{nullptr};


        wayland_shm_buffer_t() = default;
        wayland_shm_buffer_t(wayland_shm_buffer_t&& other) noexcept
            : buffer(other.buffer),
              pixels(bongocat_move(other.pixels)),
              busy(false),         // atomics cannot be moved, reset to default
              pending(false),      // same here
              index(other.index),
              _animation_trigger_context(other._animation_trigger_context)
        {
            other.buffer = nullptr;
            other.index = 0;
            other._animation_trigger_context = nullptr;
            atomic_store(&busy, atomic_load(&other.busy));
            atomic_store(&other.busy, false);
            atomic_store(&pending, atomic_load(&other.pending));
            atomic_store(&other.pending, false);
        }
        wayland_shm_buffer_t& operator=(wayland_shm_buffer_t&& other) noexcept {
            if (this != &other) {
                buffer = other.buffer;
                pixels = std::move(other.pixels);
                busy = false;           // reset atomics
                pending = false;
                index = other.index;
                _animation_trigger_context = other._animation_trigger_context;

                other.buffer = nullptr;
                other.index = 0;
                other._animation_trigger_context = nullptr;
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
        wayland_shared_memory_t(wayland_shared_memory_t&& other) noexcept
            : buffers{}, current_buffer_index(other.current_buffer_index),
              configured(false) // atomics cannot be moved
        {
            // Manually move each buffer
            for (size_t i = 0; i < WAYLAND_NUM_BUFFERS; i++) {
                buffers[i] = bongocat_move(other.buffers[i]);
            }
            other.current_buffer_index = 0;
            atomic_store(&configured, atomic_load(&other.configured));
            atomic_store(&other.configured, false);
        }

        wayland_shared_memory_t& operator=(wayland_shared_memory_t&& other) noexcept {
            if (this != &other) {
                current_buffer_index = other.current_buffer_index;
                for (size_t i = 0; i < WAYLAND_NUM_BUFFERS; ++i) {
                    buffers[i] = bongocat_move(other.buffers[i]);
                }
                atomic_store(&configured, atomic_load(&other.configured));
                atomic_store(&other.configured, false);
                other.current_buffer_index = 0;
            }
            return *this;
        }
    };
}

#endif // BONGOCAT_WAYLAND_SHARED_MEMORY_H