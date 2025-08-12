#ifndef BONGOCAT_WAYLAND_SHARED_MEMORY_H
#define BONGOCAT_WAYLAND_SHARED_MEMORY_H

#include "graphics/animation_event_context.h"
#include "../protocols/xdg-shell-client-protocol.h"
#include <wayland-client.h>
#include <stdatomic.h>

#define WAYLAND_NUM_BUFFERS 1

typedef struct {
    struct wl_buffer *buffer;
    uint8_t *pixels;
    size_t pixels_size;
    atomic_bool busy;        // 0 free / 1 busy
    atomic_bool pending;     // 0/1: a render was requested while busy
    int index;

    // extra context for listeners
    animation_trigger_context_t *_animation_trigger_context;
} wayland_shm_buffer_t;

// Wayland globals
typedef struct {
    wayland_shm_buffer_t buffers[WAYLAND_NUM_BUFFERS];
    int current_buffer_index;
    atomic_bool configured;
} wayland_shared_memory_t;

#endif // BONGOCAT_WAYLAND_SHARED_MEMORY_H