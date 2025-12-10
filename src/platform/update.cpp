#include "platform/update.h"

#include "graphics/animation.h"
#include "platform/wayland.h"
#include "utils/memory.h"

#include <cassert>
#include <cctype>
#include <cstdio>
#include <fcntl.h>
#include <linux/input.h>
#include <poll.h>
#include <pthread.h>
#include <sys/epoll.h>
#include <sys/eventfd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

namespace bongocat::platform::update {
inline static constexpr int MAX_ATTEMPTS = 2048;
inline static constexpr size_t GET_CPU_PRESENT_LAST_BUF = 256;
inline static constexpr size_t CPU_INFO_BUF = 8192;

static inline constexpr auto UPDATE_POOL_TIMEOUT_MS = 1000;
static inline constexpr auto COND_STORED_TIMEOUT_MS = 1000;

inline static constexpr time_ms_t COND_ANIMATION_TRIGGER_INIT_TIMEOUT_MS = 5000;
inline static constexpr time_ms_t COND_RELOAD_CONFIGS_TIMEOUT_MS = 5000;

inline static constexpr const char *FILENAME_CPU_PRESET = "/sys/devices/system/cpu/present";
inline static constexpr const char *FILENAME_PROC_STAT = "/proc/stat";

static void cleanup_update_thread(void *arg) {
  assert(arg);
  const animation::animation_context_t& animation_context = *static_cast<animation::animation_context_t *>(arg);
  assert(animation_context._update);
  update_context_t& input = *animation_context._update;

  atomic_store(&input._running, false);

  input.config_updated.notify_all();

  BONGOCAT_LOG_INFO("Update thread cleanup completed (via pthread_cancel)");
}

static int set_nonblocking(int fd) {
  const int flags = fcntl(fd, F_GETFL, 0);
  if (flags == -1) {
    return -1;
  }
  return fcntl(fd, F_SETFL, flags | O_NONBLOCK);
}

/*
static size_t get_cpu_present_last(int fd) {
    lseek(fd, 0, SEEK_SET);
    char buf[GET_CPU_PRESENT_LAST_BUF] = {0};
    ssize_t len = read(fd, buf, sizeof(buf)-1);
    if (len <= 0) return 0;
    assert(len >= 0 && static_cast<size_t>(len) < GET_CPU_PRESENT_LAST_BUF);
    buf[len] = '\0';

    const char* last_sep = strpbrk(buf, "-,");
    if (last_sep) {
        return strtoul(last_sep + 1, nullptr, 10);
    }
    return 0;
}
*/

static const cpu_snapshot_t& get_latest_snapshot_unlocked(update_context_t& ctx) {
  assert(ctx.shm);
  auto& update_shm = *ctx.shm;
  ctx.update_cond.timedwait([&]() { return update_shm.cpu_snapshots.stored > 0; }, COND_STORED_TIMEOUT_MS);
  static_assert(CpuSnapshotRingBufferMaxHistory > 0);
  const size_t latest =
      (update_shm.cpu_snapshots.head + CpuSnapshotRingBufferMaxHistory - 1) % CpuSnapshotRingBufferMaxHistory;
  assert(latest < CpuSnapshotRingBufferMaxHistory);
  return update_shm.cpu_snapshots.history[latest];
}

const cpu_snapshot_t& get_latest_snapshot(update_context_t& ctx) {
  LockGuard guard(ctx.update_lock);
  return get_latest_snapshot_unlocked(ctx);
}

static size_t parse_cpuinfo_fd(int fd, size_t cpu_present_last, cpu_stat_t *out, size_t out_size) {
  lseek(fd, 0, SEEK_SET);
  char buf[CPU_INFO_BUF] = {0};
  const ssize_t len = read(fd, buf, sizeof(buf) - 1);
  if (len <= 0) {
    return 0;
  }
  assert(len >= 0 && static_cast<size_t>(len) < CPU_INFO_BUF);
  buf[len] = '\0';

  ssize_t current_cpu_number = -1;
  size_t used = 0;

  char *saveptr = BONGOCAT_NULLPTR;
  char *line = strtok_r(buf, "\n", &saveptr);
  while (line) {
    if (strncmp(line, "cpu", 3) != 0) {
      break;
    }

    size_t line_cpu_number = 0;
    if (current_cpu_number >= 0) {
      line_cpu_number = strtoul(line + 3, BONGOCAT_NULLPTR, 10);
      assert(current_cpu_number >= 0);
      // assert(current_cpu_number <= SIZE_MAX);
      while (line_cpu_number > static_cast<size_t>(current_cpu_number) && used < out_size) {
        out[used] = {};
        used++;
        current_cpu_number++;
      }
    }

    char *p = line;
    while (*p && !isspace(static_cast<unsigned char>(*p))) {
      p++;
    }
    while (*p && isspace(static_cast<unsigned char>(*p))) {
      p++;
    }

    constexpr size_t times_size = 16;
    size_t times[times_size] = {0};
    size_t times_count = 0;
    char *tok = strtok(p, " \t");
    while (tok && times_count < times_size) {
      times[times_count++] = strtoull(tok, BONGOCAT_NULLPTR, 10);
      tok = strtok(BONGOCAT_NULLPTR, " \t");
    }

    size_t idle_time = 0;
    size_t total_time = 0;
    assert(times_size >= 5);
    if (times_count >= 5) {
      idle_time = times[3] + times[4];
      for (size_t i = 0; i < times_count; i++) {
        total_time += times[i];
      }
    }

    if (used < MaxCpus) {
      out[used] = cpu_stat_t{.idle_time = idle_time, .total_time = total_time};
      used++;
    }
    current_cpu_number++;

    line = strtok_r(BONGOCAT_NULLPTR, "\n", &saveptr);
  }

  if (current_cpu_number >= 0) {
    assert(current_cpu_number >= 0);
    // assert(current_cpu_number <= SIZE_MAX);
    while (static_cast<size_t>(current_cpu_number) <= cpu_present_last && used < out_size) {
      out[used] = {};
      used++;
      current_cpu_number++;
    }
  }

  return used;
}

static double compute_avg_cpu_usage(const cpu_snapshot_t& prev, const cpu_snapshot_t& curr) {
  assert(curr.count == prev.count);  // both snapshots must have same CPU count

  size_t total_delta = 0;
  size_t idle_delta = 0;
  for (size_t i = 0; i < curr.count; i++) {
    const cpu_stat_t& p = prev.stats[i];
    const cpu_stat_t& c = curr.stats[i];

    const size_t d_total = (c.total_time > p.total_time) ? (c.total_time - p.total_time) : 0;
    const size_t d_idle = (c.idle_time > p.idle_time) ? (c.idle_time - p.idle_time) : 0;

    total_delta += d_total;
    idle_delta += d_idle;
  }

  if (total_delta == 0) {
    return 0.0;
  }
  return 100.0 * static_cast<double>(total_delta - idle_delta) / static_cast<double>(total_delta);
}

static double compute_max_cpu_usage(const cpu_snapshot_t& prev, const cpu_snapshot_t& curr) {
  assert(curr.count == prev.count);  // both snapshots must have same CPU count

  double max_usage = 0.0;

  for (size_t i = 0; i < curr.count; i++) {
    const cpu_stat_t *p = &prev.stats[i];
    const cpu_stat_t *c = &curr.stats[i];

    const size_t d_total = (c->total_time > p->total_time) ? (c->total_time - p->total_time) : 0;
    const size_t d_idle = (c->idle_time > p->idle_time) ? (c->idle_time - p->idle_time) : 0;
    if (d_total == 0) {
      continue;  // skip if no change
    }

    const double usage = 100.0 * static_cast<double>(d_total - d_idle) / static_cast<double>(d_total);
    if (usage > max_usage) {
      max_usage = usage;
    }
  }

  return max_usage;
}

static void *update_thread(void *arg) {
  assert(arg);
  animation::animation_context_t& animation_ctx = *static_cast<animation::animation_context_t *>(arg);

  // from thread context
  // animation_context_t& anim = trigger_ctx.anim;
  // wait for input context (in animation start)
  animation_ctx.init_cond.timedwait([&]() { return atomic_load(&animation_ctx.ready); },
                                    COND_ANIMATION_TRIGGER_INIT_TIMEOUT_MS);
  assert(animation_ctx._input != BONGOCAT_NULLPTR);
  update_context_t& upd = *animation_ctx._update;

  // sanity checks
  assert(upd._config != BONGOCAT_NULLPTR);
  assert(upd._configs_reloaded_cond != BONGOCAT_NULLPTR);
  assert(!upd._running);
  assert(upd.shm);
  assert(upd._local_copy_config);
  assert(upd.update_config_efd._fd >= 0);
  assert(upd.fd_present._fd >= 0);
  assert(upd.fd_stat._fd >= 0);

  // trigger initial render
  wayland::request_render(animation_ctx);

  pthread_cleanup_push(cleanup_update_thread, arg);

  // local thread context
  /// event poll
  // 0:       reload config event
  // 1:       fd_stat
  // 2:       fd_present
  constexpr size_t nfds = 3;
  pollfd pfds[nfds];

  atomic_store(&upd._running, true);
  while (atomic_load(&upd._running)) {
    pthread_testcancel();  // optional, but makes cancellation more responsive

    // read from config
    time_ms_t timeout = UPDATE_POOL_TIMEOUT_MS;
    time_ms_t update_rate_ms = 0;
    time_ms_t animation_speed_ms = 0;
    double cpu_threshold = 0;
    int fps = 0;
    // bool enable_debug = false;
    {
      // read-only config
      assert(upd._local_copy_config);
      const config::config_t& current_config = *upd._local_copy_config;

      // enable_debug = current_config.enable_debug;

      cpu_threshold = current_config.cpu_threshold;
      update_rate_ms = current_config.update_rate_ms;
      animation_speed_ms = current_config.animation_speed_ms;
      fps = current_config.fps;
      if (update_rate_ms > 0) {
        timeout = update_rate_ms;
      } else if (animation_speed_ms > 0) {
        timeout = animation_speed_ms;
      } else if (current_config.fps > 0) {
        timeout = 1000 / current_config.fps / 2;
      }
    }

    // init pfds
    constexpr size_t fds_update_config_index = 0;
    constexpr size_t fds_stat_index = 1;
    constexpr size_t fds_preset_index = 2;
    pfds[fds_update_config_index] = {.fd = upd.update_config_efd._fd, .events = POLLIN, .revents = 0};
    pfds[fds_stat_index] = {.fd = upd.fd_stat._fd, .events = POLLIN, .revents = 0};
    pfds[fds_preset_index] = {.fd = upd.fd_present._fd, .events = POLLIN, .revents = 0};

    // poll events
    const int poll_result = poll(pfds, nfds, static_cast<int>(timeout));
    if (poll_result < 0) {
      if (errno == EINTR) {
        continue;  // Interrupted by signal
      }
      BONGOCAT_LOG_ERROR("update: Poll error: %s", strerror(errno));
      break;
    }

    // cancel pooling (when not running anymore)
    if (!atomic_load(&upd._running)) {
      // draining pools
      for (size_t i = 0; i < nfds; i++) {
        if (pfds[i].revents & POLLIN) {
          drain_event(pfds[i], MAX_ATTEMPTS);
        }
      }
      break;
    }

    // Handle config update
    assert(upd._config_generation != BONGOCAT_NULLPTR);
    bool reload_config = false;
    uint64_t new_gen{atomic_load(upd._config_generation)};
    if (pfds[fds_update_config_index].revents & POLLIN) {
      BONGOCAT_LOG_DEBUG("update: Receive update config event");
      drain_event(pfds[fds_update_config_index], MAX_ATTEMPTS, "update config eventfd");
      reload_config = new_gen > 0;
    }

    // Handle stat
    if (pfds[fds_stat_index].revents & POLLIN) {
      BONGOCAT_LOG_VERBOSE("update: Receive update CPU stats event");
      drain_event(pfds[fds_stat_index], MAX_ATTEMPTS, FILENAME_PROC_STAT);

      if (update_rate_ms > 0) {
        platform::LockGuard guard(upd.update_lock);
        assert(upd.shm);
        auto& update_shm = *upd.shm;

        const size_t count = parse_cpuinfo_fd(
            upd.fd_stat._fd, 0, update_shm.cpu_snapshots.history[update_shm.cpu_snapshots.head].stats, MaxCpus);
        update_shm.cpu_snapshots.history[update_shm.cpu_snapshots.head].count = count;

        {
          LockGuard guard_cond(upd.update_cond._mutex);
          update_shm.cpu_snapshots.head = (update_shm.cpu_snapshots.head + 1) % CpuSnapshotRingBufferMaxHistory;
          if (update_shm.cpu_snapshots.stored < CpuSnapshotRingBufferMaxHistory) {
            update_shm.cpu_snapshots.stored++;
          }
          pthread_cond_broadcast(&upd.update_cond._cond);
        }
      }
    }

    // cpu_present file changed
    if (pfds[fds_preset_index].revents & POLLIN) {
      BONGOCAT_LOG_VERBOSE("update: Receive update CPU present event");
      drain_event(pfds[fds_preset_index], MAX_ATTEMPTS, FILENAME_CPU_PRESET);

      if (update_rate_ms > 0) {
        BONGOCAT_LOG_VERBOSE("update: cpu_present file changed (hotplug)");
      }
    }

    // trigger animation
    bool animation_triggered = false;
    if (update_rate_ms > 0) {
      LockGuard guard(upd.update_lock);
      assert(upd.shm);
      auto& update_shm = *upd.shm;

      // read-only config
      assert(upd._local_copy_config);
      const config::config_t& current_config = *upd._local_copy_config;

      update_shm.latest_snapshot = &get_latest_snapshot_unlocked(upd);

      if (update_shm.cpu_snapshots.stored >= 2) {
        const size_t latest =
            (update_shm.cpu_snapshots.head + CpuSnapshotRingBufferMaxHistory - 1) % CpuSnapshotRingBufferMaxHistory;
        const size_t prev_i = (latest + CpuSnapshotRingBufferMaxHistory - 1) % CpuSnapshotRingBufferMaxHistory;

        const cpu_snapshot_t& curr = update_shm.cpu_snapshots.history[latest];
        const cpu_snapshot_t& prev = update_shm.cpu_snapshots.history[prev_i];

        update_shm.avg_cpu_usage = compute_avg_cpu_usage(prev, curr);
        update_shm.max_cpu_usage = compute_max_cpu_usage(prev, curr);

        const bool above_threshold = current_config.cpu_threshold >= ENABLED_MIN_CPU_PERCENT &&
                                     (update_shm.avg_cpu_usage >= current_config.cpu_threshold ||
                                      update_shm.max_cpu_usage >= current_config.cpu_threshold);
        const bool lower_threshold = current_config.cpu_threshold >= ENABLED_MIN_CPU_PERCENT &&
                                     (update_shm.last_avg_cpu_usage >= current_config.cpu_threshold ||
                                      update_shm.last_max_cpu_usage >= current_config.cpu_threshold) &&
                                     (update_shm.avg_cpu_usage < current_config.cpu_threshold ||
                                      update_shm.max_cpu_usage < current_config.cpu_threshold);
        const bool crossed_delta =
            fabs(update_shm.avg_cpu_usage - update_shm.last_avg_cpu_usage) >= TRIGGER_ANIMATION_CPU_DIFF_PERCENT ||
            fabs(update_shm.max_cpu_usage - update_shm.last_max_cpu_usage) >= TRIGGER_ANIMATION_CPU_DIFF_PERCENT;
        if (above_threshold || lower_threshold) {
          if (!update_shm.cpu_active || crossed_delta) {
            BONGOCAT_LOG_VERBOSE("update: avg. CPU: %.2f (max: %.2f)", update_shm.avg_cpu_usage,
                                 update_shm.max_cpu_usage);
            animation::trigger(animation_ctx, animation::trigger_animation_cause_mask_t::CpuUpdate);
            if (lower_threshold) {
              animation::trigger(animation_ctx, animation::trigger_animation_cause_mask_t::IdleUpdate);
            }
            animation_triggered = true;
          }
          update_shm.cpu_active = true;
        } else {
          if (update_shm.cpu_active) {
            update_shm.cpu_active = false;
            animation::trigger(animation_ctx, animation::trigger_animation_cause_mask_t::CpuUpdate);
            animation::trigger(animation_ctx, animation::trigger_animation_cause_mask_t::IdleUpdate);
          }
        }
      }

      update_shm.last_avg_cpu_usage = update_shm.avg_cpu_usage;
      update_shm.last_max_cpu_usage = update_shm.max_cpu_usage;
    }

    // handle update config
    if (reload_config) {
      assert(upd._config_generation != BONGOCAT_NULLPTR);
      assert(upd._configs_reloaded_cond != BONGOCAT_NULLPTR);
      assert(upd._config != BONGOCAT_NULLPTR);

      update_config(upd, *upd._config, new_gen);

      // wait for reload config to be done (all configs)
      const int rc = upd._configs_reloaded_cond->timedwait(
          [&] { return atomic_load(upd._config_generation) >= new_gen; }, COND_RELOAD_CONFIGS_TIMEOUT_MS);
      if (rc == ETIMEDOUT) {
        BONGOCAT_LOG_WARNING("update: Timed out waiting for reload eventfd: %s", strerror(errno));
      }
      if constexpr (features::Debug) {
        if (atomic_load(&upd.config_seen_generation) < atomic_load(upd._config_generation)) {
          BONGOCAT_LOG_VERBOSE("update: update.config_seen_generation < update._config_generation; %d < %d",
                               atomic_load(&upd.config_seen_generation), atomic_load(upd._config_generation));
        }
      }
      // assert(atomic_load(&upd.config_seen_generation) >= atomic_load(upd._config_generation));
      atomic_store(&upd.config_seen_generation, atomic_load(upd._config_generation));
      BONGOCAT_LOG_INFO("update: Update config reloaded (gen=%u)", new_gen);
    }

    if (update_rate_ms > 0) {
      // sleep
      timespec ts;
      ts.tv_sec = 0;
      assert(fps > 0);
      if (animation_triggered && animation_speed_ms > 0) {
        // when animation were triggered, wait for animation to end (assumption), before triggering a possible new
        // animation
        ts.tv_nsec = animation_speed_ms * 1000 * 1000;
      } else if (animation_triggered) {
        ts.tv_nsec = (1000L / fps) * 1000 * 1000;
      } else {
        ts.tv_nsec = timeout * 1000 * 1000;
      }
      while (ts.tv_nsec >= 1000000000LL) {
        ts.tv_nsec -= 1000000000LL;
        ts.tv_sec += 1;
      }
      nanosleep(&ts, BONGOCAT_NULLPTR);
      {
        LockGuard guard(upd.update_lock);
        assert(upd.shm);
        auto& update_shm = *upd.shm;
        update_shm.cpu_active = false;
      }
    } else {
      if (update_rate_ms == 0 || cpu_threshold < ENABLED_MIN_CPU_PERCENT) {
        atomic_store(&upd._running, false);
        BONGOCAT_LOG_WARNING("update: Stop update thread, not needed");
      }
    }
  }

  atomic_store(&upd._running, false);

  // Will run only on normal return
  pthread_cleanup_pop(1);  // 1 = call cleanup even if not canceled

  BONGOCAT_LOG_INFO("Update monitoring stopped");

  return BONGOCAT_NULLPTR;
}

created_result_t<AllocatedMemory<update_context_t>> create(const config::config_t& config) {
  AllocatedMemory<update_context_t> ret = make_allocated_memory<update_context_t>();
  // assert(ret != nullptr);
  if (!ret) [[unlikely]] {
    return bongocat_error_t::BONGOCAT_ERROR_MEMORY;
  }

  ret->_running = false;

  BONGOCAT_LOG_INFO("Initializing update monitoring system");

  // Initialize shared memory
  ret->shm = make_allocated_mmap<update_shared_memory_t>();
  if (!ret->shm) [[unlikely]] {
    BONGOCAT_LOG_ERROR("Failed to create shared memory for update monitoring: %s", strerror(errno));
    return bongocat_error_t::BONGOCAT_ERROR_MEMORY;
  }

  // Initialize shared memory for local config
  ret->_local_copy_config = make_allocated_mmap<config::config_t>();
  if (!ret->_local_copy_config) [[unlikely]] {
    BONGOCAT_LOG_ERROR("Failed to create shared memory for update monitoring: %s", strerror(errno));
    return bongocat_error_t::BONGOCAT_ERROR_MEMORY;
  }
  assert(ret->_local_copy_config);
  *ret->_local_copy_config = config;

  ret->update_config_efd = platform::FileDescriptor(eventfd(0, EFD_NONBLOCK | EFD_CLOEXEC));
  if (ret->update_config_efd._fd < 0) [[unlikely]] {
    BONGOCAT_LOG_ERROR("Failed to create notify pipe for update update config: %s", strerror(errno));
    return bongocat_error_t::BONGOCAT_ERROR_FILE_IO;
  }

  // open files
  ret->fd_present = FileDescriptor(open(FILENAME_CPU_PRESET, O_RDONLY));
  if (ret->fd_present._fd < 0) {
    BONGOCAT_LOG_ERROR("Failed to open cpu_present");
    return bongocat_error_t::BONGOCAT_ERROR_FILE_IO;
  }
  set_nonblocking(ret->fd_present._fd);

  ret->fd_stat = FileDescriptor(open(FILENAME_PROC_STAT, O_RDONLY));
  if (ret->fd_stat._fd < 0) {
    BONGOCAT_LOG_ERROR("Failed to open proc stat");
    return bongocat_error_t::BONGOCAT_ERROR_FILE_IO;
  }
  set_nonblocking(ret->fd_stat._fd);

  BONGOCAT_LOG_INFO("Input monitoring started");
  return ret;
}

bongocat_error_t start(update_context_t& upd, animation::animation_context_t& animation_ctx,
                       const config::config_t& config, CondVariable& configs_reloaded_cond,
                       atomic_uint64_t& config_generation) {
  BONGOCAT_LOG_INFO("Initializing update monitoring");

  // Initialize shared memory for key press flag
  upd.shm = make_allocated_mmap<update_shared_memory_t>();
  if (!upd.shm) [[unlikely]] {
    BONGOCAT_LOG_ERROR("Failed to create shared memory for input monitoring: %s", strerror(errno));
    return bongocat_error_t::BONGOCAT_ERROR_MEMORY;
  }

  // Initialize shared memory for local config
  upd._local_copy_config = make_allocated_mmap<config::config_t>();
  if (!upd._local_copy_config) [[unlikely]] {
    BONGOCAT_LOG_ERROR("Failed to create shared memory for input monitoring: %s", strerror(errno));
    return bongocat_error_t::BONGOCAT_ERROR_MEMORY;
  }
  assert(upd._local_copy_config);
  update_config(upd, config, atomic_load(&config_generation));

  // wait for animation trigger to be ready (input should be the same)
  const int cond_ret = animation_ctx.init_cond.timedwait([&]() { return atomic_load(&animation_ctx.ready); },
                                                         COND_ANIMATION_TRIGGER_INIT_TIMEOUT_MS);
  if (cond_ret == ETIMEDOUT) {
    BONGOCAT_LOG_ERROR("Failed to initialize input monitoring: waiting for animation thread to start in time");
  } else {
    assert(animation_ctx._update == &upd);
  }
  // set extern/global references
  {
    // guard for anim_update_state
    LockGuard guard(animation_ctx.thread_context.anim_lock);
    animation_ctx._update = &upd;
  }
  animation_ctx.init_cond.notify_all();
  upd._config = &config;
  upd._configs_reloaded_cond = &configs_reloaded_cond;
  upd._config_generation = &config_generation;
  atomic_store(&upd.ready, true);
  upd.init_cond.notify_all();

  upd._configs_reloaded_cond->notify_all();

  // start update thread
  const int result = pthread_create(&upd._update_thread, BONGOCAT_NULLPTR, update_thread, &animation_ctx);
  if (result != 0) {
    BONGOCAT_LOG_ERROR("Failed to start update thread: %s", strerror(errno));
    return bongocat_error_t::BONGOCAT_ERROR_THREAD;
  }

  BONGOCAT_LOG_INFO("Update monitoring started");
  return bongocat_error_t::BONGOCAT_SUCCESS;
}

bongocat_error_t restart(update_context_t& upd, animation::animation_context_t& animation_ctx,
                         const config::config_t& config, CondVariable& configs_reloaded_cond,
                         atomic_uint64_t& config_generation) {
  BONGOCAT_LOG_INFO("Restarting update system");
  // Stop current monitoring
  if (upd._update_thread) {
    BONGOCAT_LOG_DEBUG("Update thread");
    atomic_store(&upd._running, false);
    // pthread_cancel(ctx->_update_thread);
    if (stop_thread_graceful_or_cancel(upd._update_thread, upd._running) != 0) {
      BONGOCAT_LOG_ERROR("Failed to join update thread: %s", strerror(errno));
    }
    BONGOCAT_LOG_DEBUG("Update thread terminated");
  }

  /// @TODO: re-create context with create(), avoid duplicate code
  {
    LockGuard guard(upd.update_lock);
    // Start new monitoring (reuse shared memory if it exists)
    if (!upd.shm) {
      upd.shm = make_allocated_mmap<update_shared_memory_t>();
      if (upd.shm.ptr == MAP_FAILED) {
        BONGOCAT_LOG_ERROR("Failed to create shared memory for update thread: %s", strerror(errno));
        return bongocat_error_t::BONGOCAT_ERROR_MEMORY;
      }
    }
  }

  if (!upd._local_copy_config) {
    upd._local_copy_config = make_unallocated_mmap_value<config::config_t>(config);
    if (!upd._local_copy_config) {
      BONGOCAT_LOG_ERROR("Failed to create shared memory for update: %s", strerror(errno));
      return bongocat_error_t::BONGOCAT_ERROR_MEMORY;
    }
  }
  assert(upd._local_copy_config);
  update_config(upd, config, atomic_load(&config_generation));

  if (upd.update_config_efd._fd < 0) {
    upd.update_config_efd = platform::FileDescriptor(eventfd(0, EFD_NONBLOCK | EFD_CLOEXEC));
    if (upd.update_config_efd._fd < 0) {
      BONGOCAT_LOG_ERROR("Failed to create notify pipe for update, update config: %s", strerror(errno));
      return bongocat_error_t::BONGOCAT_ERROR_FILE_IO;
    }
  }

  // re-open files
  /// @TODO: healthcheck of fd before re-start

  if (upd.fd_present._fd < 0) {
    upd.fd_present = FileDescriptor(open(FILENAME_CPU_PRESET, O_RDONLY));
    if (upd.fd_present._fd < 0) {
      BONGOCAT_LOG_ERROR("Failed to open cpu_present");
      return bongocat_error_t::BONGOCAT_ERROR_FILE_IO;
    }
    set_nonblocking(upd.fd_present._fd);
  }
  if (upd.fd_stat._fd < 0) {
    upd.fd_stat = FileDescriptor(open(FILENAME_PROC_STAT, O_RDONLY));
    if (upd.fd_stat._fd < 0) {
      BONGOCAT_LOG_ERROR("Failed to open proc stat");
      return bongocat_error_t::BONGOCAT_ERROR_FILE_IO;
    }
    set_nonblocking(upd.fd_stat._fd);
  }

  // if (trigger_ctx._update != ctx._update) {
  //     BONGOCAT_LOG_DEBUG("Update context in animation differs from animation trigger update context");
  // }

  // set extern/global references
  {
    // guard for anim_update_state
    LockGuard guard(animation_ctx.thread_context.anim_lock);
    animation_ctx._update = &upd;
  }
  upd._config = &config;
  upd._configs_reloaded_cond = &configs_reloaded_cond;
  upd._config_generation = &config_generation;
  atomic_store(&upd.config_seen_generation, atomic_load(&config_generation));
  upd.init_cond.notify_all();
  upd._configs_reloaded_cond->notify_all();

  // start update monitoring
  const int result = pthread_create(&upd._update_thread, BONGOCAT_NULLPTR, update_thread, &animation_ctx);
  if (result != 0) {
    BONGOCAT_LOG_ERROR("Failed to start update thread: %s", strerror(errno));
    return bongocat_error_t::BONGOCAT_ERROR_THREAD;
  }

  BONGOCAT_LOG_INFO("Update thread restarted");
  return bongocat_error_t::BONGOCAT_SUCCESS;
}

void stop(update_context_t& ctx) {
  atomic_store(&ctx._running, false);
  if (ctx._update_thread) {
    BONGOCAT_LOG_DEBUG("Stopping update thread");
    // pthread_cancel(ctx->_update_thread);
    if (stop_thread_graceful_or_cancel(ctx._update_thread, ctx._running) != 0) {
      BONGOCAT_LOG_ERROR("Failed to join update thread: %s", strerror(errno));
    }
    BONGOCAT_LOG_DEBUG("Update thread terminated");
  }
  ctx._update_thread = 0;

  ctx._config = BONGOCAT_NULLPTR;
  ctx._configs_reloaded_cond = BONGOCAT_NULLPTR;
  ctx._config_generation = BONGOCAT_NULLPTR;

  ctx.config_updated.notify_all();
  atomic_store(&ctx.ready, false);
  ctx.init_cond.notify_all();
}

void trigger_update_config(update_context_t& upd, const config::config_t& config, uint64_t config_generation) {
  upd._config = &config;
  if (write(upd.update_config_efd._fd, &config_generation, sizeof(uint64_t)) >= 0) {
    BONGOCAT_LOG_VERBOSE("Write update trigger update config");
  } else {
    BONGOCAT_LOG_ERROR("Failed to write to notify pipe in update: %s", strerror(errno));
  }
}

void update_config(update_context_t& upd, const config::config_t& config, uint64_t new_gen) {
  assert(upd._local_copy_config);

  *upd._local_copy_config = config;

  atomic_store(&upd.config_seen_generation, new_gen);
  // Signal main that reload is done
  upd.config_updated.notify_all();
}
}  // namespace bongocat::platform::update
