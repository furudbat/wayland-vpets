#ifndef BONGOCAT_INPUT_SHARED_MEMORY_H
#define BONGOCAT_INPUT_SHARED_MEMORY_H

#include "utils/time.h"
#include <stdatomic.h>

namespace bongocat::platform::input {

// =============================================================================
// INPUT STATE (shared memory)
// =============================================================================

    struct input_shared_memory_t {
        int32_t any_key_pressed{0};
        int32_t kpm{0};                                     // keystrokes per minute
        atomic_int input_counter{0};
        timestamp_ms_t last_key_pressed_timestamp{0};


        input_shared_memory_t() = default;
        ~input_shared_memory_t() = default;

        input_shared_memory_t(const input_shared_memory_t& other)
            : any_key_pressed(other.any_key_pressed),
              kpm(other.kpm),
              input_counter(atomic_load(&other.input_counter)),
              last_key_pressed_timestamp(other.last_key_pressed_timestamp) {}
        input_shared_memory_t& operator=(const input_shared_memory_t& other) {
            if (this != &other) {
                any_key_pressed = other.any_key_pressed;
                kpm = other.kpm;
                atomic_store(&input_counter, atomic_load(&other.input_counter));
                last_key_pressed_timestamp = other.last_key_pressed_timestamp;
            }
            return *this;
        }

        input_shared_memory_t(input_shared_memory_t&& other) noexcept
            : any_key_pressed(other.any_key_pressed),
              kpm(other.kpm),
              last_key_pressed_timestamp(other.last_key_pressed_timestamp) {
            atomic_store(&input_counter, atomic_load(&other.input_counter));

            other.any_key_pressed = 0;
            other.kpm = 0;
            atomic_store(&other.input_counter, 0);
        }
        input_shared_memory_t& operator=(input_shared_memory_t&& other) noexcept {
            if (this != &other) {
                any_key_pressed = other.any_key_pressed;
                kpm = other.kpm;
                atomic_store(&input_counter, atomic_load(&other.input_counter));
                last_key_pressed_timestamp = other.last_key_pressed_timestamp;

                other.any_key_pressed = 0;
                other.kpm = 0;
                atomic_store(&other.input_counter, 0);
            }
            return *this;
        }
    };
}

#endif // BONGOCAT_INPUT_SHARED_MEMORY_H