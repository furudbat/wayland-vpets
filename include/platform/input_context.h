#ifndef BONGOCAT_INPUT_CONTEXT_H
#define BONGOCAT_INPUT_CONTEXT_H

#include "config/config.h"
#include "input_shared_memory.h"
#include "utils/system_memory.h"
#include "utils/time.h"

#include <libudev.h>
#include <pthread.h>
#include <stdatomic.h>

namespace bongocat::platform::input {
enum class input_unique_file_type_t : uint8_t {
  NONE,
  File,
  Symlink,
};
struct input_unique_file_t;
void cleanup(input_unique_file_t& file);
struct input_unique_file_t {
  const char *_device_path{nullptr};  // original string from config (ref to input_context_t._device_paths[i])
  char *canonical_path{nullptr};      // resolved real path (malloc'd)
  FileDescriptor fd;
  input_unique_file_type_t type{input_unique_file_type_t::NONE};

  input_unique_file_t() = default;
  ~input_unique_file_t() {
    cleanup(*this);
  }

  input_unique_file_t(const input_unique_file_t& other) = delete;
  input_unique_file_t& operator=(const input_unique_file_t& other) = delete;

  input_unique_file_t(input_unique_file_t&& other) noexcept
      : _device_path(other._device_path)
      , canonical_path(other.canonical_path)
      , fd(bongocat::move(other.fd))
      , type(other.type) {
    other._device_path = nullptr;
    other.canonical_path = nullptr;
    other.type = input_unique_file_type_t::NONE;
  }
  input_unique_file_t& operator=(input_unique_file_t&& other) noexcept {
    if (this != &other) {
      cleanup(*this);

      _device_path = other._device_path;
      canonical_path = other.canonical_path;
      fd = bongocat::move(other.fd);
      type = other.type;

      other._device_path = nullptr;
      other.canonical_path = nullptr;
      other.type = input_unique_file_type_t::NONE;
    }
    return *this;
  }
};
inline void cleanup(input_unique_file_t& file) {
  close_fd(file.fd);
  file._device_path = nullptr;
  if (file.canonical_path)
    ::free(file.canonical_path);
  file.canonical_path = nullptr;
  file.type = input_unique_file_type_t::NONE;
}

struct input_context_t;
void stop(input_context_t& ctx);
// Cleanup input monitoring resources
void cleanup(input_context_t& ctx);

// =============================================================================
// INPUT STATE
// =============================================================================

struct input_context_t {
  // local copy from other thread, update after reload (shared memory)
  MMapMemory<config::config_t> _local_copy_config;
  MMapMemory<input_shared_memory_t> shm;

  atomic_bool _capture_input_running{false};
  pthread_t _input_thread{0};
  atomic_int _input_kpm_counter{0};
  timestamp_ms_t _latest_kpm_update_ms{0};
  // lock for shm
  Mutex input_lock;

  // thread context
  AllocatedArray<char *> _device_paths;  // local copy of devices (from config)
  AllocatedArray<size_t> _unique_paths_indices;
  size_t _unique_paths_indices_capacity{0};  // keep real _unique_paths_indices count here, shrink
                                             // _unique_paths_indices.count to used unique_paths_indices
  AllocatedArray<input_unique_file_t> _unique_devices;
  /// udev monitoring
  udev *_udev{nullptr};
  udev_monitor *_udev_mon{nullptr};
  int _udev_fd{-1};

  // config reload threading
  FileDescriptor update_config_efd;  // get new_gen from here
  atomic_uint64_t config_seen_generation{0};
  platform::CondVariable config_updated;

  // globals (references)
  const config::config_t *_config{nullptr};
  platform::CondVariable *_configs_reloaded_cond{nullptr};
  atomic_uint64_t *_config_generation{nullptr};
  atomic_bool ready;
  platform::CondVariable init_cond;

  input_context_t() = default;
  ~input_context_t() {
    cleanup(*this);
  }

  input_context_t(const input_context_t&) = delete;
  input_context_t& operator=(const input_context_t&) = delete;
  input_context_t(input_context_t&& other) noexcept = delete;
  input_context_t& operator=(input_context_t&& other) noexcept = delete;
};
inline void cleanup(input_context_t& ctx) {
  if (atomic_load(&ctx._capture_input_running)) {
    stop(ctx);
    // input_lock should be unlocked
  }
  atomic_store(&ctx._capture_input_running, false);
  ctx._input_thread = 0;

  release_allocated_array(ctx._unique_devices);
  ctx._unique_paths_indices_capacity = 0;
  release_allocated_array(ctx._unique_paths_indices);
  for (size_t i = 0; i < ctx._device_paths.count; i++) {
    if (ctx._device_paths[i])
      ::free(ctx._device_paths[i]);
    ctx._device_paths[i] = nullptr;
  }
  release_allocated_array(ctx._device_paths);

  if (ctx._udev_mon)
    udev_monitor_unref(ctx._udev_mon);
  if (ctx._udev)
    udev_unref(ctx._udev);
  ctx._udev_mon = nullptr;
  ctx._udev = nullptr;
  ctx._udev_fd = -1;

  close_fd(ctx.update_config_efd);
  atomic_store(&ctx.config_seen_generation, 0);

  release_allocated_mmap_memory(ctx._local_copy_config);
  release_allocated_mmap_memory(ctx.shm);

  ctx._config = nullptr;
  ctx._configs_reloaded_cond = nullptr;
  ctx._config_generation = nullptr;
  atomic_store(&ctx.ready, false);
  ctx.init_cond.notify_all();
}
}  // namespace bongocat::platform::input

#endif  // BONGOCAT_INPUT_CONTEXT_H