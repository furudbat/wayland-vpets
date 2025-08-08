#ifndef BONGOCAT_BONGOCAT_H
#define BONGOCAT_BONGOCAT_H

#include "utils/error.h"
#include <pthread.h>
#include <stdatomic.h>
#include <stdint.h>

#ifndef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 200809L
#endif

// Version
#define BONGOCAT_VERSION "1.3.1"

// Common constants
#define DEFAULT_SCREEN_WIDTH 1920
#define DEFAULT_BAR_HEIGHT 40
#define RGBA_CHANNELS 4
#define MAX_OUTPUTS 8               // Maximum monitor outputs to store

// Config watcher constants
#define INOTIFY_EVENT_SIZE (sizeof(struct inotify_event))
#define INOTIFY_BUF_LEN (1024 * (INOTIFY_EVENT_SIZE + 16))

// Config watcher structure
typedef struct {
    int inotify_fd;
    int watch_fd;
    char *config_path;

    // event file descriptor
    int reload_efd;

    pthread_t watcher_thread;
    atomic_bool _running;
} config_watcher_t;

#define RELOAD_EVENT_BUF 8

// Output monitor reference structure
typedef struct {
    struct wl_output *wl_output;
    struct zxdg_output_v1 *xdg_output;
    uint32_t name;         // Registry name
    char name_str[128];   // From xdg-output
    bool name_received;
} output_ref_t;

// Config watcher function declarations
bongocat_error_t config_watcher_init(config_watcher_t *watcher, const char *config_path);
void config_watcher_start(config_watcher_t *watcher);
void config_watcher_stop(config_watcher_t *watcher);
void config_watcher_cleanup(config_watcher_t *watcher);

#endif // BONGOCAT_H