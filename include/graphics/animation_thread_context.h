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

enum class animation_state_row_t : uint8_t {
  Idle,
  StartWriting,
  Writing,
  EndWriting,
  Happy,
  FallASleep,
  Sleep,
  FallASleepIdle,
  IdleSleep,
  WakeUp,
  Boring,
  Test,
  StartWorking,
  Working,
  EndWorking,
  StartMoving,
  Moving,
  EndMoving,
  StartRunning,
  Running,
  EndRunning,
  StartEvolution,
  Evolution,
  AfterEvolution,
};

struct animation_state_t {
  // animation timing
  platform::time_ms_t frame_delta_ms_counter{0};
  platform::time_ms_t update_delta_ms_counter{0};
  platform::time_ns_t frame_time_ns{0};
  platform::time_ms_t frame_time_ms{0};
  platform::time_ms_t hold_frame_ms{0};
  platform::timestamp_ms_t last_frame_update_ms{0};
  platform::timestamp_ms_t time_until_next_frame_ms{0};

  // state
  bool hold_frame_after_release{false};
  bool show_boring_animation_once{false};
  bool swap_animation_done{false};

  // moving
  float anim_velocity{0.0};
  float anim_distance{0.0};
  float anim_last_direction{0.0};
  int32_t anim_pause_after_movement_ms{0};

  // animation player data
  animation_state_row_t row_state{animation_state_row_t::Idle};
  // for ms agent and sprite sheets
  int32_t start_col_index{0};
  int32_t end_col_index{0};
  // for am/bongocat/pkmn (cached animation frames)
  int32_t animations_index{0};  // for sprite_sheet.frames (col indices) array

  bool _hold_write_animation_started{false};
};

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

  animation_state_t _state;

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
  ctx._state = {};

  close_fd(ctx.update_config_efd);
  atomic_store(&ctx.config_seen_generation, 0);

  platform::release_allocated_mmap_memory(ctx.shm);
  platform::release_allocated_mmap_memory(ctx._local_copy_config);
  ctx._rng = {};
}
}  // namespace bongocat::animation

#endif  // BONGOCAT_ANIMATION_CONTEXT_H
