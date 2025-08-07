#define _POSIX_C_SOURCE 200809L
#define _DEFAULT_SOURCE
#include "core/bongocat.h"
#include "utils/time.h"
#include "utils/error.h"
#include <string.h>
#include <unistd.h>
#include <sys/select.h>
#include <assert.h>
#include <sys/inotify.h>
#include <sys/time.h>
#include <sys/eventfd.h>

#define RELOAD_DEBOUNCE_MS 1000
#define RELOAD_DELAY_MS 100

static void *config_watcher_thread(void *arg) {
    assert(arg);

    config_watcher_t *watcher = arg;
    char buffer[INOTIFY_BUF_LEN] = {0};
    timestamp_ms_t last_reload_timestamp = get_current_time_ms();

    BONGOCAT_LOG_INFO("Config watcher started for: %s", watcher->config_path);

    atomic_store(&watcher->_running, true);
    while (atomic_load(&watcher->_running)) {
        fd_set read_fds;
        
        FD_ZERO(&read_fds);
        FD_SET(watcher->inotify_fd, &read_fds);

        // Set timeout to 1 second to allow checking watching flag
        struct timeval timeout = (struct timeval){.tv_sec = 1, .tv_usec = 0};
        const int select_result = select(watcher->inotify_fd + 1, &read_fds, NULL, NULL, &timeout);
        
        if (select_result < 0) {
            if (errno == EINTR) continue;
            BONGOCAT_LOG_ERROR("Config watcher select failed: %s", strerror(errno));
            break;
        }
        
        if (select_result == 0) {
            // Timeout, continue to check watching flag
            continue;
        }
        
        if (FD_ISSET(watcher->inotify_fd, &read_fds)) {
            ssize_t length = read(watcher->inotify_fd, buffer, INOTIFY_BUF_LEN);
            
            if (length < 0) {
                BONGOCAT_LOG_ERROR("Config watcher read failed: %s", strerror(errno));
                continue;
            }
            
            bool should_reload = false;
            ssize_t i = 0;
            while (i < length) {
                struct inotify_event *event = (struct inotify_event *)&buffer[i];
                
                if (event->mask & (IN_MODIFY | IN_MOVED_TO)) {
                    should_reload = true;
                }
                
                i += INOTIFY_EVENT_SIZE + event->len;
            }

            if (should_reload) {
                // Debounce: only reload if at least some time have passed since last reload
                const timestamp_ms_t current_time = get_current_time_ms();
                if (current_time - last_reload_timestamp >= RELOAD_DEBOUNCE_MS) {
                    BONGOCAT_LOG_INFO("Config file changed, reloading...");
                    // Small delay to ensure file write is complete
                    usleep(RELOAD_DELAY_MS*1000);

                    static const char buf[RELOAD_EVENT_BUF] = {'R', '\0', 0};
                    if (write(watcher->reload_efd, buf, sizeof(char)*RELOAD_EVENT_BUF) >= 0) {
                        BONGOCAT_LOG_DEBUG("Write reload event in watcher");
                    } else {
                        BONGOCAT_LOG_ERROR("Failed to write to notify pipe in watcher: %s", strerror(errno));
                    }

                    last_reload_timestamp = current_time;
                }
            }
        }
    }
    atomic_store(&watcher->_running, false);
    
    BONGOCAT_LOG_INFO("Config watcher stopped");
    return NULL;
}

bongocat_error_t config_watcher_init(config_watcher_t *watcher, const char *config_path) {
    BONGOCAT_CHECK_NULL(watcher, BONGOCAT_ERROR_INVALID_PARAM);
    BONGOCAT_CHECK_NULL(config_path, BONGOCAT_ERROR_INVALID_PARAM);
    
    memset(watcher, 0, sizeof(config_watcher_t));
    
    // Initialize inotify
    watcher->inotify_fd = inotify_init1(IN_NONBLOCK);
    if (watcher->inotify_fd < 0) {
        BONGOCAT_LOG_ERROR("Failed to initialize inotify: %s", strerror(errno));
        return BONGOCAT_ERROR_FILE_IO;
    }
    
    // Store config path
    watcher->config_path = strdup(config_path);
    if (!watcher->config_path) {
        close(watcher->inotify_fd);
        return BONGOCAT_ERROR_MEMORY;
    }
    
    // Add watch for the config file
    watcher->watch_fd = inotify_add_watch(watcher->inotify_fd, config_path, 
                                         IN_MODIFY | IN_MOVED_TO | IN_CREATE);
    if (watcher->watch_fd < 0) {
        BONGOCAT_LOG_ERROR("Failed to add inotify watch for %s: %s", config_path, strerror(errno));
        free(watcher->config_path);
        close(watcher->inotify_fd);
        return BONGOCAT_ERROR_FILE_IO;
    }

    watcher->reload_efd = eventfd(0, 0);
    if (watcher->reload_efd < 0) {
        BONGOCAT_LOG_ERROR("Failed to create notify pipe for config reload: %s", strerror(errno));
        free(watcher->config_path);
        close(watcher->inotify_fd);
        return BONGOCAT_ERROR_FILE_IO;
    }
    
    return 0;
}

void config_watcher_start(config_watcher_t *watcher) {
    if (!watcher) {
        return;
    }

    if (pthread_create(&watcher->watcher_thread, NULL, config_watcher_thread, watcher) != 0) {
        atomic_store(&watcher->_running, false);
        BONGOCAT_LOG_ERROR("Failed to create config watcher thread: %s", strerror(errno));
        return;
    }
    
    BONGOCAT_LOG_INFO("Config watcher thread started");
}

void config_watcher_stop(config_watcher_t *watcher) {
    if (!watcher) {
        return;
    }
    
    atomic_store(&watcher->_running, false);
    pthread_cancel(watcher->watcher_thread);
    // Wait for thread to finish
    if (pthread_join(watcher->watcher_thread, NULL) != 0) {
        BONGOCAT_LOG_ERROR("Failed to join config watcher thread: %s", strerror(errno));
    }
}

void config_watcher_cleanup(config_watcher_t *watcher) {
    if (!watcher) {
        return;
    }
    
    config_watcher_stop(watcher);
    
    if (watcher->watch_fd >= 0) {
        inotify_rm_watch(watcher->inotify_fd, watcher->watch_fd);
    }
    
    if (watcher->inotify_fd >= 0) {
        close(watcher->inotify_fd);
    }
    
    if (watcher->config_path) {
        free(watcher->config_path);
        watcher->config_path = NULL;
    }

    close(watcher->reload_efd);
    
    memset(watcher, 0, sizeof(config_watcher_t));
}