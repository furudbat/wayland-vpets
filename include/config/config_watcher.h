#ifndef BONGOCAT_CONFIG_WATCHER_H
#define BONGOCAT_CONFIG_WATCHER_H

#include "core/bongocat.h"
#include "utils/system_memory.h"
#include <stdatomic.h>
#include <sys/inotify.h>
#include <cstdlib>


namespace bongocat::config {
    // Config watcher constants
    inline static constexpr size_t INOTIFY_EVENT_SIZE = sizeof(struct inotify_event);
    inline static constexpr size_t INOTIFY_BUF_LEN = 1024 * (INOTIFY_EVENT_SIZE + 16);

    struct config_watcher_t;
    void stop_watcher(config_watcher_t& watcher);
    void cleanup_watcher(config_watcher_t& watcher);

    // Config watcher structure
    struct config_watcher_t {
        platform::FileDescriptor inotify_fd;
        platform::FileDescriptor watch_fd;
        char *config_path{nullptr};

        // event file descriptor
        platform::FileDescriptor reload_efd;

        pthread_t _watcher_thread{0};
        atomic_bool _running{false};


        config_watcher_t() = default;
        ~config_watcher_t() {
            cleanup_watcher(*this);
        }

        config_watcher_t(const config_watcher_t&) = delete;
        config_watcher_t& operator=(const config_watcher_t&) = delete;

        config_watcher_t(config_watcher_t&& other) noexcept
            : inotify_fd(bongocat::move(other.inotify_fd)),
              watch_fd(bongocat::move(other.watch_fd)),
              config_path(other.config_path),
              reload_efd(bongocat::move(other.reload_efd)),
              _watcher_thread(other._watcher_thread),
              _running(atomic_load(&other._running)) {
            other.config_path = nullptr;
            other._watcher_thread = 0;
            other._running = false;
        }
        config_watcher_t& operator=(config_watcher_t&& other) noexcept {
            if (this != &other) {
                cleanup_watcher(*this);

                inotify_fd = bongocat::move(other.inotify_fd);
                watch_fd = bongocat::move(other.watch_fd);
                config_path = other.config_path;
                reload_efd = bongocat::move(other.reload_efd);
                _watcher_thread = other._watcher_thread;
                atomic_store(&_running, atomic_load(&other._running));

                other.config_path = nullptr;
                other._watcher_thread = 0;
                other._running = false;
            }
            return *this;
        }
    };
    inline void cleanup_watcher(config_watcher_t& watcher) {
        stop_watcher(watcher);

        if (watcher.watch_fd._fd >= 0) {
            inotify_rm_watch(watcher.inotify_fd._fd, watcher.watch_fd._fd);
            watcher.inotify_fd._fd = -1;
            watcher.watch_fd._fd = -1;
        }

        if (watcher.config_path) {
            ::free(watcher.config_path);
            watcher.config_path = nullptr;
        }
    }

    // Config watcher function declarations
    created_result_t<config_watcher_t> create_watcher(const char *config_path);
    void start_watcher(config_watcher_t& watcher);
}

#endif // BONGOCAT_CONFIG_WATCHER_H