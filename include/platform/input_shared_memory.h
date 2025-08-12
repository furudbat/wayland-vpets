#ifndef BONGOCAT_INPUT_SHARED_MEMORY_H
#define BONGOCAT_INPUT_SHARED_MEMORY_H

#include "utils/time.h"
#include <stdatomic.h>

typedef struct {
    /// @NOTE: variables can be shared between child process and parent (see mmap)
    int any_key_pressed;
    int kpm;                    // keystrokes per minute
    atomic_int input_counter;
    timestamp_ms_t last_key_pressed_timestamp;
} input_shared_memory_t;

#endif // BONGOCAT_INPUT_EVENT_CONTEXT_H