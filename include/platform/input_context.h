#ifndef BONGOCAT_INPUT_CONTEXT_H
#define BONGOCAT_INPUT_CONTEXT_H

#include "config/config.h"
#include "input_shared_memory.h"
#include "utils/time.h"
#include <pthread.h>
#include <stdatomic.h>

struct input_context_t {
    input_shared_memory_t *shm{nullptr};

    // local copy from other thread, update after reload (shared memory)
    config_t *_local_copy_config{nullptr};

    pthread_t _input_thread{0};
    atomic_bool _capture_input_running{false};
    atomic_int _input_kpm_counter{0};
    timestamp_ms_t _latest_kpm_update_ms{0};

    // thread context
    char* *_device_paths;    // local copy of devices
    int _device_paths_count{0};
    int *_fds{nullptr};
    size_t _fds_count{0};
    size_t *_unique_paths_indices{nullptr};
    size_t _unique_paths_indices_count{0};
};

#endif // BONGOCAT_INPUT_CONTEXT_H