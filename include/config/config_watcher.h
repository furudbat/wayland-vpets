#ifndef BONGOCAT_CONFIG_WATCHER_H
#define BONGOCAT_CONFIG_WATCHER_H

#include "utils/error.h"
#include "utils/system_memory.h"
#include <pthread.h>
#include <stdatomic.h>
#include <sys/inotify.h>

// Config watcher constants
inline static constexpr size_t INOTIFY_EVENT_SIZE = sizeof(struct inotify_event);
inline static constexpr size_t INOTIFY_BUF_LEN = 1024 * (INOTIFY_EVENT_SIZE + 16);

// Config watcher structure
struct config_watcher_t{
    FileDescriptor inotify_fd;
    FileDescriptor watch_fd;
    char *config_path{nullptr};

    // event file descriptor
    FileDescriptor reload_efd;

    pthread_t _watcher_thread{0};
    atomic_bool _running{false};
};

// Config watcher function declarations
bongocat_error_t config_watcher_init(config_watcher_t& watcher, const char *config_path);
void config_watcher_start(config_watcher_t& watcher);
void config_watcher_stop(config_watcher_t& watcher);
void config_watcher_cleanup(config_watcher_t& watcher);

#endif // BONGOCAT_CONFIG_WATCHER_H