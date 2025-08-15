#ifndef BONGOCAT_CONFIG_WATCHER_H
#define BONGOCAT_CONFIG_WATCHER_H

#include "utils/error.h"
#include "utils/system_memory.h"
#include <pthread.h>
#include <stdatomic.h>
#include <sys/inotify.h>

namespace bongocat::config {
    // Config watcher constants
    inline static constexpr size_t INOTIFY_EVENT_SIZE = sizeof(struct inotify_event);
    inline static constexpr size_t INOTIFY_BUF_LEN = 1024 * (INOTIFY_EVENT_SIZE + 16);

    // Config watcher structure
    struct config_watcher_t{
        platform::FileDescriptor inotify_fd;
        platform::FileDescriptor watch_fd;
        char *config_path{nullptr};

        // event file descriptor
        platform::FileDescriptor reload_efd;

        pthread_t _watcher_thread{0};
        atomic_bool _running{false};
    };

    // Config watcher function declarations
    bongocat_error_t init(config_watcher_t& watcher, const char *config_path);
    void start_watcher(config_watcher_t& watcher);
    void stop_watcher(config_watcher_t& watcher);
    void cleanup_watcher(config_watcher_t& watcher);
}

#endif // BONGOCAT_CONFIG_WATCHER_H