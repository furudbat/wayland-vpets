#ifndef BONGOCAT_AUDIO_CONTEXT_H
#define BONGOCAT_AUDIO_CONTEXT_H

#include "audio_shared_memory.h"
#include "config/config.h"
#include "module.h"
#include "utils/system_memory.h"

#include <pthread.h>
#include <stdatomic.h>

namespace bongocat::platform::audio {

BONGOCAT_STUBS_BEGIN

struct audio_context_t;
BONGOCAT_AUDIO_STUB_INLINE void stop(audio_context_t& ctx) BONGOCAT_AUDIO_STUB;
void cleanup(audio_context_t& ctx);

struct audio_context_t {
  // local copy from other thread, update after reload (shared memory)
  MMapMemory<config::config_t> _local_copy_config;
  MMapMemory<audio_shared_memory_t> shm;

  atomic_bool _running{false};
  pthread_t _audio_thread{0};
  // lock for shm
  Mutex audio_lock;
  platform::CondVariable audio_cond;

  // thread context
  // @TODO: add more internal thread context ...

  // config reload threading
  FileDescriptor audio_config_efd;  // get new_gen from here
  atomic_uint64_t config_seen_generation{0};
  platform::CondVariable config_updated;

  // globals (references)
  const config::config_t *_config{BONGOCAT_NULLPTR};
  platform::CondVariable *_configs_reloaded_cond{BONGOCAT_NULLPTR};
  atomic_uint64_t *_config_generation{BONGOCAT_NULLPTR};
  atomic_bool ready;
  platform::CondVariable init_cond;

  audio_context_t() = default;
  ~audio_context_t() {
    cleanup(*this);
  }

  audio_context_t(const audio_context_t&) = delete;
  audio_context_t& operator=(const audio_context_t&) = delete;
  audio_context_t(audio_context_t&& other) noexcept = delete;
  audio_context_t& operator=(audio_context_t&& other) noexcept = delete;
};
inline void cleanup(audio_context_t& ctx) {
  if (atomic_load(&ctx._running)) {
    stop(ctx);
    // audio_lock should be unlocked
  }
  atomic_store(&ctx._running, false);
  ctx._audio_thread = 0;

  /// @TODO: clean up thread context

  close_fd(ctx.audio_config_efd);
  atomic_store(&ctx.config_seen_generation, 0);

  release_allocated_mmap_memory(ctx._local_copy_config);
  release_allocated_mmap_memory(ctx.shm);

  ctx._config = BONGOCAT_NULLPTR;
  ctx._configs_reloaded_cond = BONGOCAT_NULLPTR;
  ctx._config_generation = BONGOCAT_NULLPTR;
  atomic_store(&ctx.ready, false);
  ctx.init_cond.notify_all();
}

BONGOCAT_STUBS_END

}  // namespace bongocat::platform::audio

#endif