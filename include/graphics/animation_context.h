#ifndef BONGOCAT_ANIMATION_CONTEXT_H
#define BONGOCAT_ANIMATION_CONTEXT_H

#include "animation_shared_memory.h"
#include "config/config.h"
#include "platform/input_context.h"
#include "utils/system_memory.h"
#include <stdatomic.h>

namespace bongocat::animation {
    struct animation_context_t {
        /// @NOTE: variables can be shared between child process and parent (see mmap)
        platform::MMapMemory<animation_shared_memory_t> shm;

        // local copy from other thread, update after reload (shared memory)
        platform::MMapMemory<config::config_t> _local_copy_config;

        // Animation system state
        atomic_bool _animation_running{false};
        pthread_t _anim_thread{0};
        platform::Mutex anim_lock;
    };
}

#endif //BONGOCAT_ANIMATION_CONTEXT_H
