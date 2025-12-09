#ifndef BONGOCAT_ANIMATION_CONTEXT_H
#define BONGOCAT_ANIMATION_CONTEXT_H

#include "animation_shared_memory.h"
#include "config/config.h"
#include "utils/random.h"
#include "utils/system_memory.h"

#include <stdatomic.h>

namespace bongocat::animation {

// =============================================================================
// ANIMATION STATE
// =============================================================================

struct animation_thread_context_t;
void stop(animation_thread_context_t& ctx);
// Cleanup animation resources
void cleanup(animation_thread_context_t& ctx);

struct animation_thread_context_t {
  // local copy from other thread, update after reload (shared memory)
  platform::MMapMemory<config::config_t> _local_copy_config;
  platform::MMapMemory<animation_shared_memory_t> shm;

  // Animation system state
  atomic_bool _animation_running{false};
  pthread_t _anim_thread{0};
  platform::random_xoshiro128 _rng;
  // lock for shm
  platform::Mutex anim_lock;

  // config reload threading
  platform::FileDescriptor update_config_efd;  // get new_gen from here
  atomic_uint64_t config_seen_generation{0};
  platform::CondVariable config_updated;

  animation_thread_context_t() = default;
  ~animation_thread_context_t() {
    cleanup(*this);
  }

  animation_thread_context_t(const animation_thread_context_t&) = delete;
  animation_thread_context_t& operator=(const animation_thread_context_t&) = delete;
  animation_thread_context_t(animation_thread_context_t&& other) = delete;
  animation_thread_context_t& operator=(animation_thread_context_t&& other) = delete;
};
inline void cleanup(animation_thread_context_t& ctx) {
  if (atomic_load(&ctx._animation_running)) {
    stop(ctx);
    // ctx.anim_lock should be unlocked
  }
  atomic_store(&ctx._animation_running, false);
  ctx._anim_thread = 0;

  close_fd(ctx.update_config_efd);
  atomic_store(&ctx.config_seen_generation, 0);

  platform::release_allocated_mmap_memory(ctx.shm);
  platform::release_allocated_mmap_memory(ctx._local_copy_config);
  ctx._rng = platform::random_xoshiro128(0);
}
}  // namespace bongocat::animation

#endif  // BONGOCAT_ANIMATION_CONTEXT_H
