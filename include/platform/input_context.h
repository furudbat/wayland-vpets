#ifndef BONGOCAT_INPUT_CONTEXT_H
#define BONGOCAT_INPUT_CONTEXT_H

#include "utils/time.h"
#include <pthread.h>
#include <stdatomic.h>
#include "config/config.h"

typedef struct {
    /// @NOTE: variables can be shared between child process and parent (see mmap)
    int *any_key_pressed;
    int *kpm;                    // keystrokes per minute
    atomic_int *input_counter;
    timestamp_ms_t *last_key_pressed_timestamp;

    // local copy from other thread, update after reload (shared memory)
    config_t* _local_copy_config;

    pthread_t _input_thread;
    atomic_bool _capture_input_running;
    atomic_int _input_kpm_counter;
    timestamp_ms_t _latest_kpm_update_ms;

    // thread context
    int *_fds;
    size_t _fds_count;
    size_t *_unique_paths_indices;
    size_t _unique_paths_indices_count;
} input_context_t;

#endif // BONGOCAT_INPUT_CONTEXT_H