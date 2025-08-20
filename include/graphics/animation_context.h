#ifndef BONGOCAT_ANIMATION_CONTEXT_H
#define BONGOCAT_ANIMATION_CONTEXT_H

#include "animation_shared_memory.h"
#include "config/config.h"
#include "utils/system_memory.h"
#include "utils/random.h"
#include <stdatomic.h>

namespace bongocat::animation {

    struct animation_context_t;
    void stop(animation_context_t& ctx);
    void cleanup(animation_context_t& ctx);

    struct animation_context_t {
        /// @NOTE: variables can be shared between child process and parent (see mmap)
        platform::MMapMemory<animation_shared_memory_t> shm;

        // local copy from other thread, update after reload (shared memory)
        platform::MMapMemory<config::config_t> _local_copy_config;

        // Animation system state
        atomic_bool _animation_running{false};
        pthread_t _anim_thread{0};
        platform::Mutex anim_lock;
        platform::random_xoshiro128 rng;


        animation_context_t() = default;
        ~animation_context_t() {
            cleanup(*this);
        }

        animation_context_t(const animation_context_t&) = delete;
        animation_context_t& operator=(const animation_context_t&) = delete;

        animation_context_t(animation_context_t&& other) noexcept
            : shm(bongocat::move(other.shm)),
              _local_copy_config(bongocat::move(other._local_copy_config)),
              _animation_running(atomic_load(&other._animation_running)),
              _anim_thread(other._anim_thread),
              anim_lock(bongocat::move(other.anim_lock)),
              rng(bongocat::move(other.rng)) {
            other._animation_running = false;
            other._anim_thread = 0;
        }
        animation_context_t& operator=(animation_context_t&& other) noexcept {
            if (this != &other) {
                cleanup(*this);

                shm = bongocat::move(other.shm);
                _local_copy_config = bongocat::move(other._local_copy_config);
                atomic_store(&_animation_running, atomic_load(&other._animation_running));
                _anim_thread = other._anim_thread;
                anim_lock = bongocat::move(other.anim_lock);
                rng = bongocat::move(other.rng);

                other._animation_running = false;
                other._anim_thread = 0;
                other.rng = platform::random_xoshiro128(0);
            }
            return *this;
        }
    };
    inline void cleanup(animation_context_t& ctx) {
        if (atomic_load(&ctx._animation_running)) {
            ctx.anim_lock._unlock();
            stop(ctx);
        }
        atomic_store(&ctx._animation_running, false);
        ctx._anim_thread = 0;
        platform::release_allocated_mmap_memory(ctx.shm);
        platform::release_allocated_mmap_memory(ctx._local_copy_config);
        ctx.rng = platform::random_xoshiro128(0);
    }
}

#endif //BONGOCAT_ANIMATION_CONTEXT_H
