#ifndef BONGOCAT_INPUT_CONTEXT_H
#define BONGOCAT_INPUT_CONTEXT_H

#include "config/config.h"
#include "input_shared_memory.h"
#include "utils/time.h"
#include <pthread.h>
#include <stdatomic.h>

typedef struct {
    input_shared_memory_t *shm;

    // local copy from other thread, update after reload (shared memory)
    config_t* _local_copy_config;

    pthread_t _input_thread;
    atomic_bool _capture_input_running;
    atomic_int _input_kpm_counter;
    timestamp_ms_t _latest_kpm_update_ms;

    // thread context
    char* *_device_paths;    // local copy of devices
    int _device_paths_count;
    int *_fds;
    size_t _fds_count;
    size_t *_unique_paths_indices;
    size_t _unique_paths_indices_count;
} input_context_t;

#endif // BONGOCAT_INPUT_CONTEXT_H