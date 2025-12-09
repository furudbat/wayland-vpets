#include "config/config_watcher.h"

#include "platform/wayland_context.h"
#include "utils/error.h"
#include "utils/system_memory.h"
#include "utils/time.h"

#include <cassert>
#include <cstring>
#include <libgen.h>
#include <poll.h>
#include <pthread.h>
#include <sys/eventfd.h>
#include <sys/inotify.h>
#include <sys/stat.h>
#include <unistd.h>

namespace bongocat::config {
static inline constexpr int MAX_ATTEMPTS = 2048;
static inline constexpr int RECREATE_MAX_ATTEMPTS = 10;
static inline constexpr platform::time_ms_t RELOAD_DEBOUNCE_MS = 1000;
static inline constexpr platform::time_ms_t RELOAD_DELAY_MS = 100;
static inline constexpr platform::time_ms_t RECREATE_SLEEP_ATTEMPT_MS = 100;
static inline constexpr platform::time_ms_t TIMEOUT_MS = 100;

static constexpr uint32_t FILE_MASK = IN_MODIFY | IN_CLOSE_WRITE | IN_ATTRIB | IN_MOVE_SELF | IN_DELETE_SELF;
static constexpr uint32_t DIR_MASK = IN_CREATE | IN_MOVED_TO | IN_DELETE | IN_MOVED_FROM;

static bongocat_error_t reinitialize_inotify(config_watcher_t& watcher) {
  if (watcher.inotify_fd._fd >= 0) {
    platform::close_fd(watcher.inotify_fd);
  }

  watcher.inotify_fd = platform::FileDescriptor(inotify_init1(IN_NONBLOCK | IN_CLOEXEC));
  if (watcher.inotify_fd._fd < 0) {
    BONGOCAT_LOG_ERROR("config_watcher: Failed to reinit inotify: %s", strerror(errno));
    return bongocat_error_t::BONGOCAT_ERROR_FILE_IO;
  }

  watcher.wd_dir =
      platform::FileDescriptor(inotify_add_watch(watcher.inotify_fd._fd, dirname(watcher.config_path), DIR_MASK));
  watcher.wd_file = platform::FileDescriptor(inotify_add_watch(watcher.inotify_fd._fd, watcher.config_path, FILE_MASK));

  if (watcher.wd_dir._fd < 0 || watcher.wd_file._fd < 0) {
    BONGOCAT_LOG_WARNING("config_watcher: partial reinit of inotify watches");
  }

  return bongocat_error_t::BONGOCAT_SUCCESS;
}

static void *config_watcher_thread(void *arg) {
  assert(arg);
  auto& watcher = *static_cast<config_watcher_t *>(arg);

  char buffer[INOTIFY_BUF_LEN] = {};
  platform::timestamp_ms_t last_reload_timestamp = platform::get_current_time_ms();

  constexpr size_t fds_inotify_index = 0;
  constexpr nfds_t fds_count = 1;
  pollfd fds[fds_count] = {
      {.fd = watcher.inotify_fd._fd, .events = POLLIN, .revents = 0},
  };
  constexpr int timeout_ms = TIMEOUT_MS;

  BONGOCAT_LOG_INFO("config_watcher: Config watcher started for: %s", watcher.config_path);

  atomic_store(&watcher._running, true);
  while (atomic_load(&watcher._running)) {
    int ret = poll(fds, fds_count, timeout_ms);
    if (ret < 0) {
      if (errno == EINTR) {
        continue;
      }
      BONGOCAT_LOG_ERROR("config_watcher: Config watcher poll failed: %s", strerror(errno));
      break;
    }
    if (!atomic_load(&watcher._running)) {
      // draining pools
      for (size_t i = 0; i < fds_count; i++) {
        if (fds[i].revents & POLLIN) {
          int attempts = 0;
          uint64_t u;
          while (read(fds[i].fd, &u, sizeof(uint64_t)) == sizeof(uint64_t) && attempts < MAX_ATTEMPTS) {
            attempts++;
          }
        }
      }
      break;
    }

    if (fds[fds_inotify_index].revents & POLLIN) {
      const ssize_t length = read(watcher.inotify_fd._fd, buffer, config::INOTIFY_BUF_LEN);
      if (length <= 0) {
        if (errno == EINVAL || errno == EBADF) {
          BONGOCAT_LOG_WARNING("config_watcher: inotify fd invalidated (likely after suspend). Reinitializing...");
          reinitialize_inotify(watcher);
          continue;
        }
        BONGOCAT_LOG_ERROR("config_watcher: Config watcher read failed: %s", strerror(errno));
        continue;
      }

      bool should_reload = false;
      bool file_went_away = false;
      bool file_recreated = false;

      ssize_t i = 0;
      int attempts = 0;
      while (i < length && attempts < MAX_ATTEMPTS) {
        const auto *event = reinterpret_cast<const struct inotify_event *>(&buffer[i]);
        assert(event);

        BONGOCAT_LOG_VERBOSE("config_watcher: inotify event: wd=%d mask=0x%08X name=%s", event->wd, event->mask,
                             event->len ? event->name : "(none)");

        // File events
        if (event->wd == watcher.wd_file._fd) {
          should_reload |= event->mask & (IN_MODIFY | IN_CLOSE_WRITE | IN_ATTRIB);
          file_went_away |= event->mask & (IN_MOVE_SELF | IN_DELETE_SELF);
        }
        // Directory events (watch for recreate)
        else if (event->wd == watcher.wd_dir._fd) {
          if ((event->mask & (IN_CREATE | IN_MOVED_TO)) && event->len > 0) {
            file_recreated |= strcmp(event->name, basename(watcher.config_path)) == 0;
          }
        }
        // Inotify queue overflow (critical)
        else if (event->mask & IN_Q_OVERFLOW) {
          BONGOCAT_LOG_WARNING("config_watcher: inotify event queue overflow, forcing full reload");
          should_reload = true;
        }

        assert(config::INOTIFY_EVENT_SIZE <= SSIZE_MAX);
        i += static_cast<ssize_t>(config::INOTIFY_EVENT_SIZE) + event->len;
        attempts++;
      }

      // Handle file disappearance
      if (file_went_away && watcher.wd_file._fd >= 0) {
        BONGOCAT_LOG_VERBOSE("config_watcher: Config file went away; removing file watch");
        inotify_rm_watch(watcher.inotify_fd._fd, watcher.wd_file._fd);
        watcher.wd_file._fd = -1;
        // the file is gone, wait for recreation
        should_reload = false;
      }

      // Handle recreation
      if (file_recreated) {
        BONGOCAT_LOG_VERBOSE("config_watcher: Config file recreated; re-adding file watch");
        int new_wd = inotify_add_watch(watcher.inotify_fd._fd, watcher.config_path, FILE_MASK);
        if (new_wd >= 0) {
          watcher.wd_file = platform::FileDescriptor(new_wd);
          new_wd = -1;
          should_reload = true;
        } else {
          BONGOCAT_LOG_ERROR("config_watcher: Failed to re-add file watch: %s", strerror(errno));
          should_reload = false;
        }
      }

      // ensure file exists (from IN_CLOSE_WRITE/IN_MODIFY)
      if (should_reload) {
        // If we don't currently have a file watch (it was removed), try stat the file
        bool file_exists = false;
        if (watcher.wd_file._fd >= 0) {
          file_exists = true;
        } else {
          // small retry loop to handle race where create races with our handling
          struct stat st{};
          for (int attempt = 0; attempt < RECREATE_MAX_ATTEMPTS; attempt++) {
            if (stat(watcher.config_path, &st) == 0) {
              file_exists = true;
              break;
            }
            // small sleep before next stat
            usleep(RECREATE_SLEEP_ATTEMPT_MS * 1000);
          }
        }

        if (!file_exists) {
          BONGOCAT_LOG_VERBOSE("config_watcher: Reload skipped: config file not present yet (will wait for recreate)");
          should_reload = false;
        }
      }

      // Debounce reloads
      if (should_reload) {
        // Debounce: only reload if at least some time have passed since last reload
        const platform::timestamp_ms_t now = platform::get_current_time_ms();
        if (now - last_reload_timestamp >= RELOAD_DEBOUNCE_MS) {
          // Small delay to ensure file write is complete
          usleep(RELOAD_DELAY_MS * 1000);
          last_reload_timestamp = now;

          BONGOCAT_LOG_INFO("config_watcher: Config file changed, trigger reload");
          uint64_t u = 1;
          if (write(watcher.reload_efd._fd, &u, sizeof(uint64_t)) >= 0) {
            BONGOCAT_LOG_DEBUG("config_watcher: Write reload event in watcher");
          } else {
            BONGOCAT_LOG_ERROR("config_watcher: Failed to write to notify pipe in watcher: %s", strerror(errno));
          }
        }
      }
    }
  }
  atomic_store(&watcher._running, false);

  BONGOCAT_LOG_INFO("config_watcher: Config watcher stopped");
  return BONGOCAT_NULLPTR;
}

created_result_t<AllocatedMemory<config_watcher_t>> create_watcher(const char *config_path) {
  BONGOCAT_CHECK_NULL(config_path, bongocat_error_t::BONGOCAT_ERROR_INVALID_PARAM);
  AllocatedMemory<config_watcher_t> ret = make_allocated_memory<config_watcher_t>();
  assert(ret != BONGOCAT_NULLPTR);
  if (ret == BONGOCAT_NULLPTR) [[unlikely]] {
    return bongocat_error_t::BONGOCAT_ERROR_MEMORY;
  }

  // Store config path
  ret->config_path = strdup(config_path);
  if (!ret->config_path) [[unlikely]] {
    return bongocat_error_t::BONGOCAT_ERROR_MEMORY;
  }

  // Initialize inotify
  ret->inotify_fd = platform::FileDescriptor(inotify_init1(IN_NONBLOCK));
  if (ret->inotify_fd._fd < 0) [[unlikely]] {
    BONGOCAT_LOG_ERROR("Failed to initialize inotify: %s", strerror(errno));
    return bongocat_error_t::BONGOCAT_ERROR_FILE_IO;
  }

  constexpr size_t dirbuf_size = PATH_MAX;
  char dirbuf[dirbuf_size] = {0};
  strncpy(dirbuf, config_path, dirbuf_size - 1);
  dirbuf[dirbuf_size - 1] = '\0';
  const char *dir = dirname(dirbuf);
  if (!dir) [[unlikely]] {
    BONGOCAT_LOG_ERROR("dirname() failed for path %s", ret->config_path);
    return bongocat_error_t::BONGOCAT_ERROR_FILE_IO;
  }

  ret->wd_file = platform::FileDescriptor(inotify_add_watch(ret->inotify_fd._fd, ret->config_path, FILE_MASK));
  if (ret->wd_file._fd < 0) {
    BONGOCAT_LOG_ERROR("Failed to add inotify watch for file %s: %s", ret->config_path, strerror(errno));
    return bongocat_error_t::BONGOCAT_ERROR_FILE_IO;
  }

  ret->wd_dir = platform::FileDescriptor(inotify_add_watch(ret->inotify_fd._fd, dir, DIR_MASK));
  if (ret->wd_dir._fd < 0) {
    BONGOCAT_LOG_ERROR("Failed to add inotify watch for dir %s: %s", dir, strerror(errno));
    return bongocat_error_t::BONGOCAT_ERROR_FILE_IO;
  }

  ret->reload_efd = platform::FileDescriptor(eventfd(0, EFD_NONBLOCK | EFD_CLOEXEC));
  if (ret->reload_efd._fd < 0) {
    BONGOCAT_LOG_ERROR("Failed to create notify pipe for config reload: %s", strerror(errno));
    return bongocat_error_t::BONGOCAT_ERROR_FILE_IO;
  }

  return ret;
}

void start_watcher(config_watcher_t& watcher) {
  if (pthread_create(&watcher._watcher_thread, BONGOCAT_NULLPTR, config_watcher_thread, &watcher) != 0) {
    atomic_store(&watcher._running, false);
    BONGOCAT_LOG_ERROR("Failed to create config watcher thread: %s", strerror(errno));
    return;
  }

  BONGOCAT_LOG_INFO("Config watcher thread started");
}

void stop_watcher(config_watcher_t& watcher) {
  atomic_store(&watcher._running, false);
  if (watcher._watcher_thread) {
    BONGOCAT_LOG_DEBUG("Stopping config watcher thread");
    // pthread_cancel(watcher->_watcher_thread);
    //  Wait for thread to finish
    if (platform::stop_thread_graceful_or_cancel(watcher._watcher_thread, watcher._running) != 0) {
      BONGOCAT_LOG_ERROR("Failed to join config watcher thread: %s", strerror(errno));
    }
    BONGOCAT_LOG_DEBUG("config watcher thread terminated");
  }
  watcher._watcher_thread = 0;
}
}  // namespace bongocat::config
