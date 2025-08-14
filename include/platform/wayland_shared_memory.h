#ifndef BONGOCAT_WAYLAND_SHARED_MEMORY_H
#define BONGOCAT_WAYLAND_SHARED_MEMORY_H

#include "graphics/animation_event_context.h"
#include "../protocols/xdg-shell-client-protocol.h"
#include <wayland-client.h>
#include <stdatomic.h>

inline static constexpr size_t WAYLAND_NUM_BUFFERS = 1;

struct wayland_shm_buffer_t {
    wl_buffer *buffer{nullptr};
    uint8_t *pixels{nullptr};
    size_t pixels_size{0};
    atomic_bool busy{false};        // 0 free / 1 busy
    atomic_bool pending{false};     // 0/1: a render was requested while busy
    int index{0};

    // extra context for listeners
    animation_trigger_context_t *_animation_trigger_context{nullptr};
};

// Wayland globals
struct wayland_shared_memory_t {
    wayland_shm_buffer_t buffers[WAYLAND_NUM_BUFFERS];
    int current_buffer_index{0};
    atomic_bool configured{false};
};

#endif // BONGOCAT_WAYLAND_SHARED_MEMORY_H