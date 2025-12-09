#ifndef BONGOCAT_CONFIG_WATCHER_H
#define BONGOCAT_CONFIG_WATCHER_H

#include "core/bongocat.h"
#include "utils/system_memory.h"

#include <cstdlib>
#include <stdatomic.h>
#include <sys/inotify.h>

namespace bongocat::config {
// Inotify buffer sizing
inline static constexpr size_t INOTIFY_EVENT_SIZE = sizeof(struct inotify_event);
inline static constexpr size_t INOTIFY_BUF_LEN = 1024 * (INOTIFY_EVENT_SIZE + 16);

// =============================================================================
// TYPE DEFINITIONS
// =============================================================================

struct config_watcher_t;
// Stop watching for config changes
void stop_watcher(config_watcher_t& watcher);

// Cleanup config watcher resources
void cleanup_watcher(config_watcher_t& watcher);

// Config watcher structure
struct config_watcher_t {
  platform::FileDescriptor inotify_fd;
  platform::FileDescriptor wd_file;
  platform::FileDescriptor wd_dir;
  char *config_path{nullptr};

  platform::FileDescriptor reload_efd;

  pthread_t _watcher_thread{0};
  atomic_bool _running{false};

  config_watcher_t() = default;
  ~config_watcher_t() {
    cleanup_watcher(*this);
  }

  config_watcher_t(const config_watcher_t&) = delete;
  config_watcher_t& operator=(const config_watcher_t&) = delete;
  config_watcher_t(config_watcher_t&& other) noexcept = delete;
  config_watcher_t& operator=(config_watcher_t&& other) noexcept = delete;
};
inline void cleanup_watcher(config_watcher_t& watcher) {
  stop_watcher(watcher);

  // remove watches first (requires inotify fd still open)
  if (watcher.inotify_fd._fd >= 0 && watcher.wd_file._fd >= 0) {
    inotify_rm_watch(watcher.inotify_fd._fd, watcher.wd_file._fd);
    watcher.wd_file._fd = -1;
  }
  if (watcher.inotify_fd._fd >= 0 && watcher.wd_dir._fd >= 0) {
    inotify_rm_watch(watcher.inotify_fd._fd, watcher.wd_dir._fd);
    watcher.wd_dir._fd = -1;
  }

  close_fd(watcher.inotify_fd);
  close_fd(watcher.reload_efd);

  if (watcher.config_path) {
    ::free(watcher.config_path);
    watcher.config_path = nullptr;
  }
}

// =============================================================================
// CONFIG WATCHER FUNCTIONS
// =============================================================================

// Initialize config watcher
BONGOCAT_NODISCARD created_result_t<AllocatedMemory<config_watcher_t>> create_watcher(const char *config_path);

// Start watching for config changes
void start_watcher(config_watcher_t& watcher);
}  // namespace bongocat::config

#endif  // BONGOCAT_CONFIG_WATCHER_H