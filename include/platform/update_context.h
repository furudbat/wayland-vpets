#ifndef BONGOCAT_UPDATE_CONTEXT_H
#define BONGOCAT_UPDATE_CONTEXT_H

#include "config/config.h"
#include "update_shared_memory.h"
#include "utils/system_memory.h"
#include "utils/time.h"

#include <pthread.h>
#include <stdatomic.h>

namespace bongocat::platform::update {
struct update_context_t;
void stop(update_context_t& ctx);
void cleanup(update_context_t& ctx);

struct update_context_t {
  // local copy from other thread, update after reload (shared memory)
  MMapMemory<config::config_t> _local_copy_config;
  MMapMemory<update_shared_memory_t> shm;

  atomic_bool _running{false};
  pthread_t _update_thread{0};
  // lock for shm
  Mutex update_lock;
  platform::CondVariable update_cond;

  // thread context
  FileDescriptor fd_stat;
  FileDescriptor fd_present;

  // config reload threading
  FileDescriptor update_config_efd;  // get new_gen from here
  atomic_uint64_t config_seen_generation{0};
  platform::CondVariable config_updated;

  // globals (references)
  const config::config_t *_config{BONGOCAT_NULLPTR};
  platform::CondVariable *_configs_reloaded_cond{BONGOCAT_NULLPTR};
  atomic_uint64_t *_config_generation{BONGOCAT_NULLPTR};
  atomic_bool ready;
  platform::CondVariable init_cond;

  update_context_t() = default;
  ~update_context_t() {
    cleanup(*this);
  }

  update_context_t(const update_context_t&) = delete;
  update_context_t& operator=(const update_context_t&) = delete;
  update_context_t(update_context_t&& other) noexcept = delete;
  update_context_t& operator=(update_context_t&& other) noexcept = delete;
};
inline void cleanup(update_context_t& ctx) {
  if (atomic_load(&ctx._running)) {
    stop(ctx);
    // input_lock should be unlocked
  }
  atomic_store(&ctx._running, false);
  ctx._update_thread = 0;

  close_fd(ctx.fd_present);
  close_fd(ctx.fd_stat);

  close_fd(ctx.update_config_efd);
  atomic_store(&ctx.config_seen_generation, 0);

  release_allocated_mmap_memory(ctx._local_copy_config);
  release_allocated_mmap_memory(ctx.shm);

  ctx._config = BONGOCAT_NULLPTR;
  ctx._configs_reloaded_cond = BONGOCAT_NULLPTR;
  ctx._config_generation = BONGOCAT_NULLPTR;
  atomic_store(&ctx.ready, false);
  ctx.init_cond.notify_all();
}
}  // namespace bongocat::platform::update

#endif  // BONGOCAT_INPUT_CONTEXT_H