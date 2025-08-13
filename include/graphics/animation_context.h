#ifndef BONGOCAT_ANIMATION_CONTEXT_H
#define BONGOCAT_ANIMATION_CONTEXT_H

#include "animation_shared_memory.h"
#include "config/config.h"
#include "platform/input_context.h"
#include <stdatomic.h>

typedef struct {
    animation_shared_memory_t *shm;
    pthread_mutex_t anim_lock;

    // local copy from other thread, update after reload (shared memory)
    config_t* _local_copy_config;

    // Animation system state
    atomic_bool _animation_running;
    pthread_t _anim_thread;
} animation_context_t;

#endif //ANIMATION_CONTEXT_H
