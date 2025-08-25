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
        // local copy from other thread, update after reload (shared memory)
        platform::MMapMemory<config::config_t> _local_copy_config;
        platform::MMapMemory<animation_shared_memory_t> shm;

        // Animation system state
        atomic_bool _animation_running{false};
        pthread_t _anim_thread{0};
        platform::random_xoshiro128 _rng;
        // lock for shm
        platform::Mutex anim_lock;



        animation_context_t() = default;
        ~animation_context_t() {
            cleanup(*this);
        }

        animation_context_t(const animation_context_t&) = delete;
        animation_context_t& operator=(const animation_context_t&) = delete;
        animation_context_t(animation_context_t&& other) = delete;
        animation_context_t& operator=(animation_context_t&& other) = delete;

        /*
        /// @TODO: anim_lock is not movable, move it into heap, make it movable
        animation_context_t(animation_context_t&& other) noexcept
            : _local_copy_config(bongocat::move(other._local_copy_config)),
              shm(bongocat::move(other.shm)),
              _animation_running(atomic_load(&other._animation_running)),
              _anim_thread(other._anim_thread),
              anim_lock(bongocat::move(other.anim_lock)),
              _rng(bongocat::move(other._rng)) {
            other._animation_running = false;
            other._anim_thread = 0;
        }
        animation_context_t& operator=(animation_context_t&& other) noexcept {
            if (this != &other) {
                cleanup(*this);

                _local_copy_config = bongocat::move(other._local_copy_config);
                shm = bongocat::move(other.shm);
                atomic_store(&_animation_running, atomic_load(&other._animation_running));
                _anim_thread = other._anim_thread;
                anim_lock = bongocat::move(other.anim_lock);
                _rng = bongocat::move(other._rng);

                other._animation_running = false;
                other._anim_thread = 0;
                other._rng = platform::random_xoshiro128(0);
            }
            return *this;
        }
        */
    };
    inline void cleanup(animation_context_t& ctx) {
        if (atomic_load(&ctx._animation_running)) {
            stop(ctx);
            // ctx.anim_lock should be unlocked
        }
        atomic_store(&ctx._animation_running, false);
        ctx._anim_thread = 0;
        platform::release_allocated_mmap_memory(ctx.shm);
        platform::release_allocated_mmap_memory(ctx._local_copy_config);
        ctx._rng = platform::random_xoshiro128(0);
    }
}

#endif //BONGOCAT_ANIMATION_CONTEXT_H
