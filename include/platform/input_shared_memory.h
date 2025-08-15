#ifndef BONGOCAT_INPUT_SHARED_MEMORY_H
#define BONGOCAT_INPUT_SHARED_MEMORY_H

#include "utils/time.h"
#include <stdatomic.h>

namespace bongocat::platform {
    struct input_shared_memory_t {
        int any_key_pressed{0};
        int kpm{0};                    // keystrokes per minute
        atomic_int input_counter{0};
        timestamp_ms_t last_key_pressed_timestamp{0};
    };
}

#endif // BONGOCAT_INPUT_SHARED_MEMORY_H