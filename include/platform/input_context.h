#ifndef BONGOCAT_INPUT_CONTEXT_H
#define BONGOCAT_INPUT_CONTEXT_H

#include "config/config.h"
#include "input_shared_memory.h"
#include "utils/system_memory.h"
#include "utils/time.h"
#include <pthread.h>
#include <stdatomic.h>

namespace bongocat::platform::input {
    struct input_unique_file_t {
        const char* device_path{nullptr};     // ref to _device_paths
        FileDescriptor fd;
    };

    struct input_context_t;
    void stop(input_context_t& ctx);
    void cleanup(input_context_t& ctx);

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



        input_context_t() = default;
        ~input_context_t() {
            cleanup(*this);
        }

        input_context_t(const input_context_t&) = delete;
        input_context_t& operator=(const input_context_t&) = delete;

        input_context_t(input_context_t&& other) noexcept
            : shm(bongocat::move(other.shm)),
              _local_copy_config(bongocat::move(other._local_copy_config)),
              _input_thread(other._input_thread),
              _capture_input_running(atomic_load(&other._capture_input_running)),
              _input_kpm_counter(atomic_load(&other._input_kpm_counter)),
              _latest_kpm_update_ms(other._latest_kpm_update_ms),
              _device_paths(bongocat::move(other._device_paths)),
              _unique_paths_indices(bongocat::move(other._unique_paths_indices)),
              _unique_paths_indices_capacity(other._unique_paths_indices_capacity),
              _unique_devices(bongocat::move(other._unique_devices))
        {
            other._input_thread = 0;
            other._capture_input_running = false;
            other._input_kpm_counter = 0;
            other._latest_kpm_update_ms = 0;
            other._unique_paths_indices_capacity = 0;
        }

        input_context_t& operator=(input_context_t&& other) noexcept {
            if (this != &other) {
                cleanup(*this);

                shm = bongocat::move(other.shm);
                _local_copy_config = bongocat::move(other._local_copy_config);
                _input_thread = other._input_thread;
                atomic_store(&_capture_input_running, atomic_load(&other._capture_input_running));
                atomic_store(&_input_kpm_counter, atomic_load(&other._input_kpm_counter));
                _latest_kpm_update_ms = other._latest_kpm_update_ms;
                _device_paths = bongocat::move(other._device_paths);
                _unique_paths_indices = bongocat::move(other._unique_paths_indices);
                _unique_paths_indices_capacity = other._unique_paths_indices_capacity;
                _unique_devices = bongocat::move(other._unique_devices);

                other._input_thread = 0;
                other._capture_input_running = false;
                other._input_kpm_counter = 0;
                other._latest_kpm_update_ms = 0;
                other._unique_paths_indices_capacity = 0;
            }
            return *this;
        }
    };
    inline void cleanup(input_context_t& input) {
        if (atomic_load(&input._capture_input_running)) {
            stop(input);
        }
        atomic_store(&input._capture_input_running, false);
        input._input_thread = 0;
        release_allocated_array(input._unique_devices);
        input._unique_paths_indices_capacity = 0;
        release_allocated_array(input._unique_paths_indices);
        for (size_t i = 0; i < input._device_paths.count; i++) {
            if (input._device_paths[i]) ::free(input._device_paths[i]);
            input._device_paths[i] = nullptr;
        }
        release_allocated_array(input._device_paths);
    }
}

#endif // BONGOCAT_INPUT_CONTEXT_H