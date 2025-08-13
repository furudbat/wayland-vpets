#ifndef BONGOCAT_BONGOCAT_H
#define BONGOCAT_BONGOCAT_H

#include "utils/error.h"
#include <pthread.h>
#include <stdatomic.h>
#include <cstdint>
#include <sys/inotify.h>

#ifndef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 200809L
#endif

// Version
inline static constexpr const char* BONGOCAT_VERSION = "1.4.0";

// Common constants
inline static constexpr int DEFAULT_SCREEN_WIDTH = 1920;
inline static constexpr int DEFAULT_BAR_HEIGHT = 40;
inline static constexpr int RGBA_CHANNELS = 4;
inline static constexpr int BGRA_CHANNELS = 4;

inline static constexpr size_t MAX_INPUT_DEVICES = 256;

// Config watcher constants
inline static constexpr size_t INOTIFY_EVENT_SIZE = (sizeof(struct inotify_event));
inline static constexpr size_t INOTIFY_BUF_LEN = (1024 * (INOTIFY_EVENT_SIZE + 16));

// Config watcher structure
struct config_watcher_t{
    int inotify_fd{-1};
    int watch_fd{-1};
    char *config_path{NULL};

    // event file descriptor
    int reload_efd{-1};

    pthread_t _watcher_thread{0};
    atomic_bool _running{false};
};

// Config watcher function declarations
bongocat_error_t config_watcher_init(config_watcher_t *watcher, const char *config_path);
void config_watcher_start(config_watcher_t *watcher);
void config_watcher_stop(config_watcher_t *watcher);
void config_watcher_cleanup(config_watcher_t *watcher);

#endif // BONGOCAT_H