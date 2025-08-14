#ifndef BONGOCAT_INPUT_SHARED_MEMORY_H
#define BONGOCAT_INPUT_SHARED_MEMORY_H

#include "utils/time.h"
#include <stdatomic.h>

struct input_shared_memory_t {
    /// @NOTE: variables can be shared between child process and parent (see mmap)
    int any_key_pressed{0};
    int kpm{0};                    // keystrokes per minute
    atomic_int input_counter{0};
    timestamp_ms_t last_key_pressed_timestamp{0};
};

#endif // BONGOCAT_INPUT_SHARED_MEMORY_H