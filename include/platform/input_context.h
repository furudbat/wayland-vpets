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
        // ref to input_context_t._device_paths[i]
        const char* device_path{nullptr};
        FileDescriptor fd;
    };

    struct input_context_t;
    void stop(input_context_t& ctx);
    void cleanup(input_context_t& ctx);

    struct input_context_t {
        // local copy from other thread, update after reload (shared memory)
        MMapMemory<config::config_t> _local_copy_config;
        MMapMemory<input_shared_memory_t> shm;

        atomic_bool _capture_input_running{false};
        pthread_t _input_thread{0};
        // lock for shm
        Mutex input_lock;
        atomic_int _input_kpm_counter{0};
        timestamp_ms_t _latest_kpm_update_ms{0};

        // thread context
        AllocatedArray<char*> _device_paths;           // local copy of devices (from config)
        AllocatedArray<size_t> _unique_paths_indices;
        size_t _unique_paths_indices_capacity{0};      // keep real _unique_paths_indices count here, shrink _unique_paths_indices.count to used unique_paths_indices
        AllocatedArray<input_unique_file_t> _unique_devices;

        // config reload threading
        pthread_mutex_t *config_reload_mutex{nullptr};
        FileDescriptor update_config_efd;
        atomic_uint64_t config_seen_generation{0};
        pthread_cond_t *config_reload_cond{nullptr};
        atomic_uint64_t *config_generation{nullptr};

        // globals (references)
        const config::config_t *_config{nullptr};

        input_context_t() = default;
        ~input_context_t() {
            cleanup(*this);
        }

        input_context_t(const input_context_t&) = delete;
        input_context_t& operator=(const input_context_t&) = delete;

        input_context_t(input_context_t&& other) noexcept
            : _local_copy_config(bongocat::move(other._local_copy_config)),
              shm(bongocat::move(other.shm)),
              _capture_input_running(atomic_load(&other._capture_input_running)),
              _input_thread(other._input_thread),
              input_lock(bongocat::move(other.input_lock)),
              _input_kpm_counter(atomic_load(&other._input_kpm_counter)),
              _latest_kpm_update_ms(other._latest_kpm_update_ms),
              _device_paths(bongocat::move(other._device_paths)),
              _unique_paths_indices(bongocat::move(other._unique_paths_indices)),
              _unique_paths_indices_capacity(other._unique_paths_indices_capacity),
              _unique_devices(bongocat::move(other._unique_devices)),
              config_reload_mutex(other.config_reload_mutex),
              update_config_efd(bongocat::move(other.update_config_efd)),
              config_seen_generation(atomic_load(&other.config_seen_generation)),
              config_reload_cond(other.config_reload_cond),
              config_generation(other.config_generation),
              _config(other._config)
        {
            other._input_thread = 0;
            other._capture_input_running = false;
            other._input_kpm_counter = 0;
            other._latest_kpm_update_ms = 0;
            other._unique_paths_indices_capacity = 0;
            other.config_reload_mutex = nullptr;
            other.config_reload_cond = nullptr;
            other.config_generation = nullptr;
            atomic_store(&other.config_seen_generation, 0);
            other._config = nullptr;
        }

        input_context_t& operator=(input_context_t&& other) noexcept {
            if (this != &other) {
                cleanup(*this);

                _local_copy_config = bongocat::move(other._local_copy_config);
                shm = bongocat::move(other.shm);
                atomic_store(&_capture_input_running, atomic_load(&other._capture_input_running));
                _input_thread = other._input_thread;
                input_lock = bongocat::move(other.input_lock);
                atomic_store(&_input_kpm_counter, atomic_load(&other._input_kpm_counter));
                _latest_kpm_update_ms = other._latest_kpm_update_ms;
                _device_paths = bongocat::move(other._device_paths);
                _unique_paths_indices = bongocat::move(other._unique_paths_indices);
                _unique_paths_indices_capacity = other._unique_paths_indices_capacity;
                _unique_devices = bongocat::move(other._unique_devices);
                config_reload_mutex = other.config_reload_mutex;
                update_config_efd = bongocat::move(other.update_config_efd);
                atomic_store(&config_seen_generation, atomic_load(&other.config_seen_generation));
                config_reload_cond = other.config_reload_cond;
                config_generation = other.config_generation;
                _config = other._config;

                other._input_thread = 0;
                other._capture_input_running = false;
                other._input_kpm_counter = 0;
                other._latest_kpm_update_ms = 0;
                other._unique_paths_indices_capacity = 0;
                other._config = nullptr;
                other.config_reload_mutex = nullptr;
                other.config_reload_cond = nullptr;
                atomic_store(&other.config_seen_generation, 0);
                other.config_generation = nullptr;
            }
            return *this;
        }
    };
    inline void cleanup(input_context_t& ctx) {
        if (atomic_load(&ctx._capture_input_running)) {
            ctx.input_lock._unlock();
            stop(ctx);
        }
        atomic_store(&ctx._capture_input_running, false);
        ctx._input_thread = 0;
        release_allocated_array(ctx._unique_devices);
        ctx._unique_paths_indices_capacity = 0;
        release_allocated_array(ctx._unique_paths_indices);
        for (size_t i = 0; i < ctx._device_paths.count; i++) {
            if (ctx._device_paths[i]) ::free(ctx._device_paths[i]);
            ctx._device_paths[i] = nullptr;
        }
        release_allocated_array(ctx._device_paths);
        ctx._config = nullptr;
        ctx.config_reload_mutex = nullptr;
        ctx.config_reload_cond = nullptr;
        atomic_store(&ctx.config_seen_generation, 0);
        ctx.config_generation = nullptr;
    }
}

#endif // BONGOCAT_INPUT_CONTEXT_H