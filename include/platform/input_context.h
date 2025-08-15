#ifndef BONGOCAT_INPUT_CONTEXT_H
#define BONGOCAT_INPUT_CONTEXT_H

#include "config/config.h"
#include "input_shared_memory.h"
#include "utils/system_memory.h"
#include "utils/time.h"
#include <pthread.h>
#include <stdatomic.h>

namespace bongocat::platform {
    struct input_unique_file_t {
        const char* device_path{nullptr};     // ref to _device_paths
        FileDescriptor fd;
    };

    struct input_context_t {
        /// @NOTE: variables can be shared between child process and parent (see mmap)
        MMapMemory<input_shared_memory_t> shm;

        // local copy from other thread, update after reload (shared memory)
        MMapMemory<config::config_t> _local_copy_config;

        pthread_t _input_thread{0};
        atomic_bool _capture_input_running{false};
        atomic_int _input_kpm_counter{0};
        timestamp_ms_t _latest_kpm_update_ms{0};

        // thread context
        AllocatedArray<char*> _device_paths;           // local copy of devices
        AllocatedArray<size_t> _unique_paths_indices;
        size_t _unique_paths_indices_capacity{0};      // keep real _unique_paths_indices count here, shrink _unique_paths_indices.count to used unique_paths_indices
        AllocatedArray<input_unique_file_t> _unique_devices;
    };
}

#endif // BONGOCAT_INPUT_CONTEXT_H