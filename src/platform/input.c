#define _POSIX_C_SOURCE 200809L
#define _DEFAULT_SOURCE
#include "platform/input.h"
#include "graphics/animation.h"
#include "utils/memory.h"
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <pthread.h>
#include <linux/input.h>
#include <signal.h>
#include <unistd.h>
#include <assert.h>
#include <fcntl.h>

#define INPUT_EVENT_BUF 128     // Increased buffer size for better I/O efficiency

#define START_ADAPTIVE_CHECK_INTERVAL_SEC 5
#define MID_ADAPTIVE_CHECK_INTERVAL_SEC 15
#define MAX_ADAPTIVE_CHECK_INTERVAL_SEC 30

#define CHILD_TERMINATE_WAIT_ATTEMPTS 10
#define CHILD_TERMINATE_WAIT_ATTEMPT_SLEEP_MS 100


static void cleanup_input_thread(void* arg) {
    assert(arg);
    input_context_t* input = (input_context_t*)arg;
    // read-only config
    //const config_t* const current_config = input->_local_copy_config;
    //assert(current_config);
    assert(input);

    atomic_store(&input->_capture_input_running, false);

    // Close and free file descriptors
    if (input->_fds) {
        for (size_t i = 0; i < input->_fds_count; ++i) {
            if (input->_fds[i] >= 0) {
                close(input->_fds[i]);
            }
        }
        BONGOCAT_SAFE_FREE(input->_fds);
    }
    input->_fds_count = 0;

    BONGOCAT_SAFE_FREE(input->_unique_paths_indices);
    input->_unique_paths_indices_count = 0;

    BONGOCAT_LOG_INFO("Input thread cleanup completed (via pthread_cancel)");
}

static void* capture_input_thread(void* arg) {
    assert(arg);
    input_context_t* input = (input_context_t*)arg;
    // read-only config
    const config_t* const current_config = input->_local_copy_config;
    assert(current_config);
    const char **device_paths = (const char **)current_config->keyboard_devices; // pls don't modify single keyboard_devices (string)
    int num_devices = current_config->num_keyboard_devices;
    int enable_debug = current_config->enable_debug;
    assert(input);
    assert(num_devices >= 0);

    BONGOCAT_LOG_DEBUG("Starting input capture on %d devices", num_devices);

    // free resources if not already
    BONGOCAT_SAFE_FREE(input->_fds);
    BONGOCAT_SAFE_FREE(input->_unique_paths_indices);

    input->_fds_count = num_devices;
    input->_fds = BONGOCAT_MALLOC(input->_fds_count * sizeof(int));
    input->_unique_paths_indices_count = num_devices;
    input->_unique_paths_indices = BONGOCAT_MALLOC(input->_unique_paths_indices_count * sizeof(size_t));
    if (!input->_fds || !input->_unique_paths_indices) {
        atomic_store(&input->_capture_input_running, false);
        BONGOCAT_SAFE_FREE(input->_fds);
        input->_fds_count = 0;
        BONGOCAT_SAFE_FREE(input->_unique_paths_indices);
        input->_unique_paths_indices_count = 0;
        BONGOCAT_LOG_ERROR("Failed to allocate memory for file descriptors");
        return NULL;
    }

    int max_fd = -1;
    int valid_devices = 0;
    size_t unique_devices = 0;

    // First pass: deduplicate device paths
    for (size_t i = 0; i < input->_fds_count; i++) {
        bool is_duplicate = false;
        for (size_t j = 0; j < unique_devices && j < input->_unique_paths_indices_count; j++) {
            const char* device_path = device_paths[i];
            if (strcmp(device_path, device_paths[input->_unique_paths_indices[j]]) == 0) {
                is_duplicate = true;
                break;
            }
        }

        if (!is_duplicate && unique_devices < input->_unique_paths_indices_count) {
            input->_unique_paths_indices[unique_devices] = i;
            unique_devices++;
        }
    }

    BONGOCAT_LOG_DEBUG("Deduplicated %d devices to %d unique devices", num_devices, unique_devices);

    // Open all unique devices
    for (size_t i = 0; i < input->_fds_count; i++) {
        input->_fds[i] = -1;
        const char* device_path = device_paths[input->_unique_paths_indices[i]];

        // Validate device path exists and is readable
        struct stat st;
        if (stat(device_path, &st) != 0) {
            BONGOCAT_LOG_WARNING("Input device does not exist: %s", device_path);
            continue;
        }

        if (!S_ISCHR(st.st_mode)) {
            BONGOCAT_LOG_WARNING("Input device is not a character device: %s", device_path);
            continue;
        }

        input->_fds[i] = open(device_path, O_RDONLY | O_NONBLOCK);
        if (input->_fds[i] < 0) {
            BONGOCAT_LOG_WARNING("Failed to open %s: %s", device_path, strerror(errno));
            continue;
        }

        BONGOCAT_LOG_INFO("Input monitoring started on %s (fd=%d)", device_path, input->_fds[i]);
        if (input->_fds[i] > max_fd) {
            max_fd = input->_fds[i];
        }
        valid_devices++;
    }

    // Update num_devices to reflect unique devices for the rest of the function
    num_devices = unique_devices;

    if (valid_devices == 0) {
        atomic_store(&input->_capture_input_running, false);
        BONGOCAT_LOG_ERROR("No valid input devices found");
        // no valid devices open, no need to close
        BONGOCAT_SAFE_FREE(input->_fds);
        input->_fds_count = 0;
        BONGOCAT_SAFE_FREE(input->_unique_paths_indices);
        input->_unique_paths_indices_count = 0;
        return NULL;
    }

    BONGOCAT_LOG_INFO("Successfully opened %d/%d input devices", valid_devices, num_devices);

    struct input_event ev[INPUT_EVENT_BUF] = {0}; // Increased buffer size for better I/O efficiency
    fd_set readfds;
    int check_counter = 0;  // check is done every second (see timeout below)
    int adaptive_check_interval_sec = START_ADAPTIVE_CHECK_INTERVAL_SEC; // increase over time

    pthread_cleanup_push(cleanup_input_thread, input);

    atomic_store(&input->_capture_input_running, true);
    while (atomic_load(&input->_capture_input_running)) {
        pthread_testcancel();  // optional, but makes cancellation more responsive
        FD_ZERO(&readfds);

        // Optimize: only rebuild fd_set when devices change, track current max_fd
        int current_max_fd = -1;
        for (size_t i = 0; i < input->_unique_paths_indices_count; i++) {
            if (input->_fds[i] >= 0) {
                FD_SET(input->_fds[i], &readfds);
                if (input->_fds[i] > current_max_fd) {
                    current_max_fd = input->_fds[i];
                }
            }
        }
        max_fd = current_max_fd;

        /// @TODO: refactor using pool instead of select ?
        struct timeval timeout = (struct timeval){.tv_sec = 1, .tv_usec = 0};
        int select_result = select(max_fd + 1, &readfds, NULL, NULL, &timeout);
        if (select_result < 0) {
            if (errno == EINTR) continue; // Interrupted by signal
            BONGOCAT_LOG_ERROR("Select error: %s", strerror(errno));
            break;
        }

        if (select_result == 0) {
            // Adaptive device checking - increase if no new devices found
            check_counter++;
            if (check_counter >= adaptive_check_interval_sec) {
                check_counter = 0;
                bool found_new_device = false;

                // Check for devices that have become available
                for (size_t i = 0; i < input->_unique_paths_indices_count; i++) {
                    const char* device_path = device_paths[input->_unique_paths_indices[i]];
                    if (input->_fds[i] < 0) { // Device was not available before
                        struct stat st;
                        if (stat(device_path, &st) == 0 && S_ISCHR(st.st_mode)) {
                            // Device is now available, try to open it
                            int new_fd = open(device_path, O_RDONLY | O_NONBLOCK);
                            if (new_fd >= 0) {
                                input->_fds[i] = new_fd;
                                if (new_fd > max_fd) {
                                    max_fd = new_fd;
                                }
                                valid_devices++;
                                found_new_device = true;
                                BONGOCAT_LOG_INFO("New input device detected and opened: %s (fd=%d)", device_path, new_fd);
                            }
                        }
                    }
                }

                // Adaptive interval: if no new devices found, increase check interval
                if (!found_new_device && adaptive_check_interval_sec < MAX_ADAPTIVE_CHECK_INTERVAL_SEC) {
                    adaptive_check_interval_sec = (adaptive_check_interval_sec < MID_ADAPTIVE_CHECK_INTERVAL_SEC) ? MID_ADAPTIVE_CHECK_INTERVAL_SEC : MAX_ADAPTIVE_CHECK_INTERVAL_SEC;
                    BONGOCAT_LOG_DEBUG("Increased device check interval to %d seconds", adaptive_check_interval_sec);
                } else if (found_new_device && adaptive_check_interval_sec > START_ADAPTIVE_CHECK_INTERVAL_SEC) {
                    // Reset to frequent checking when devices are being connected
                    adaptive_check_interval_sec = START_ADAPTIVE_CHECK_INTERVAL_SEC;
                    BONGOCAT_LOG_DEBUG("Reset device check interval to %d seconds", START_ADAPTIVE_CHECK_INTERVAL_SEC);
                }
            }
            continue; // Continue to next iteration
        }

        // Check which devices have data
        for (size_t i = 0; i < input->_unique_paths_indices_count; i++) {
            const char* device_path = device_paths[input->_unique_paths_indices[i]];
            if (input->_fds[i] >= 0 && FD_ISSET(input->_fds[i], &readfds)) {
                const int rd = read(input->_fds[i], ev, sizeof(ev));
                // error
                if (rd < 0) {
                    if (errno == EAGAIN) continue;
                    BONGOCAT_LOG_WARNING("Read error on %s: %s", device_path, strerror(errno));
                    close(input->_fds[i]);
                    input->_fds[i] = -1;
                    valid_devices--;
                    continue;
                }
                // empty
                if (rd == 0) {
                    BONGOCAT_LOG_WARNING("EOF on input device %s", device_path);
                    close(input->_fds[i]);
                    input->_fds[i] = -1;
                    valid_devices--;
                    continue;
                }
                // check for full size
                if (rd % sizeof(struct input_event) != 0) {
                    BONGOCAT_LOG_WARNING("Partial input_event read from device %s", device_path);
                    close(input->_fds[i]);
                    input->_fds[i] = -1;
                    valid_devices--;
                    continue;
                }

                // Batch process events for better performance
                const int num_events = rd / sizeof(struct input_event);
                bool key_pressed = false;

                for (int j = 0; j < num_events; j++) {
                    if (ev[j].type == EV_KEY && ev[j].value == 1) {
                        key_pressed = true;
                        if (enable_debug) {
                            BONGOCAT_LOG_VERBOSE("Key event: device=%s, code=%d, time=%lld.%06lld",
                                                 device_path, ev[j].code, ev[j].time.tv_sec, ev[j].time.tv_usec);
                        }
                    }
                }

                // Trigger animation only once per batch to reduce overhead
                if (key_pressed) {
                    const timestamp_ms_t now = get_current_time_ms();
                    BONGOCAT_LOG_VERBOSE("Last time input pressed: %dms (%lld)", now - *input->last_key_pressed_timestamp, *input->last_key_pressed_timestamp);
                    // update KPM
                    if (now - input->_latest_kpm_update_ms >= 1000.0/current_config->fps) {
                        if (input->_input_kpm_counter > 0) {
                            const time_ms_t duration_ms = now - input->_latest_kpm_update_ms;

                            const double duration_min = duration_ms / 60000.0;
                            *input->kpm = input->_input_kpm_counter / duration_min;
                            BONGOCAT_LOG_VERBOSE("Input KPM: %d, delta: %dms, counter: %d", *input->kpm, duration_ms, input->_input_kpm_counter);

                            input->_input_kpm_counter = 0;
                            input->_latest_kpm_update_ms = now;
                        }
                    }

                    *input->last_key_pressed_timestamp = now;
                    *input->input_counter = *input->input_counter + 1;
                    input->_input_kpm_counter++;
                    animation_trigger(input);
                }
            }
        }

        // Exit if no valid devices remain
        if (valid_devices == 0) {
            BONGOCAT_LOG_ERROR("All input devices became unavailable");
            break;
        }
    }
    atomic_store(&input->_capture_input_running, false);

    // Will run only on normal return
    pthread_cleanup_pop(1);  // 1 = call cleanup even if not canceled

    // done when callback cleanup_input_thread
    /*
    // Close all (open) file descriptors
    if (input->_fds) {
        for (int i = 0; i < num_devices; i++) {
            if (input->_fds[i] >= 0) {
                close(input->_fds[i]);
            }
        }
    }
    BONGOCAT_SAFE_FREE(input->_fds);
    BONGOCAT_SAFE_FREE(input->_unique_paths_indices);
    */

    BONGOCAT_LOG_INFO("Input monitoring stopped");

    return NULL;
}

bongocat_error_t input_start_monitoring(input_context_t* ctx, char **device_paths, int num_devices, int enable_debug) {
    assert(ctx);
    BONGOCAT_CHECK_NULL(device_paths, BONGOCAT_ERROR_INVALID_PARAM);
    
    if (num_devices <= 0) {
        BONGOCAT_LOG_ERROR("No input devices specified");
        return BONGOCAT_ERROR_INVALID_PARAM;
    }

    const timestamp_ms_t now = get_current_time_ms();
    ctx->_capture_input_running = false;
    ctx->_input_kpm_counter = 0;
    ctx->_latest_kpm_update_ms = now;
    ctx->_fds = NULL;
    ctx->_fds_count = 0;
    ctx->_unique_paths_indices = NULL;
    ctx->_unique_paths_indices_count = 0;

    BONGOCAT_LOG_INFO("Initializing input monitoring system for %d devices", num_devices);
    
    // Initialize shared memory for key press flag
    ctx->any_key_pressed = (int *)mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE,
                                 MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if (ctx->any_key_pressed == MAP_FAILED) {
        BONGOCAT_LOG_ERROR("Failed to create shared memory for input monitoring: %s", strerror(errno));
        return BONGOCAT_ERROR_MEMORY;
    }
    *ctx->any_key_pressed = 0;

    // Initialize shared memory for KPM
    ctx->kpm = (int *)mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE,
                           MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if (ctx->kpm == MAP_FAILED) {
        if (ctx->any_key_pressed && ctx->any_key_pressed != MAP_FAILED) munmap(ctx->any_key_pressed, sizeof(int));
        BONGOCAT_LOG_ERROR("Failed to create shared memory for input monitoring: %s", strerror(errno));
        return BONGOCAT_ERROR_MEMORY;
    }
    *ctx->kpm = 0;

    // Initialize shared memory for counter
    ctx->input_counter = (atomic_int *)mmap(NULL, sizeof(atomic_int), PROT_READ | PROT_WRITE,
                                        MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if (ctx->input_counter == MAP_FAILED) {
        if (ctx->any_key_pressed && ctx->any_key_pressed != MAP_FAILED) munmap(ctx->any_key_pressed, sizeof(int));
        if (ctx->kpm && ctx->kpm != MAP_FAILED) munmap(ctx->kpm, sizeof(int));
        BONGOCAT_LOG_ERROR("Failed to create shared memory for input monitoring: %s", strerror(errno));
        return BONGOCAT_ERROR_MEMORY;
    }
    *ctx->input_counter = 0;

    // Initialize shared memory for timestamp
    ctx->last_key_pressed_timestamp = (timestamp_ms_t *)mmap(NULL, sizeof(timestamp_ms_t), PROT_READ | PROT_WRITE,
                                        MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if (ctx->last_key_pressed_timestamp == MAP_FAILED) {
        if (ctx->any_key_pressed && ctx->any_key_pressed != MAP_FAILED) munmap(ctx->any_key_pressed, sizeof(int));
        if (ctx->kpm && ctx->kpm != MAP_FAILED) munmap(ctx->kpm, sizeof(int));
        if (ctx->input_counter && ctx->input_counter != MAP_FAILED) munmap(ctx->input_counter, sizeof(atomic_int));
        BONGOCAT_LOG_ERROR("Failed to create shared memory for input monitoring: %s", strerror(errno));
        return BONGOCAT_ERROR_MEMORY;
    }
    *ctx->last_key_pressed_timestamp = now;

    // Initialize shared memory for local config
    ctx->_local_copy_config = (config_t *)mmap(NULL, sizeof(config_t), PROT_READ | PROT_WRITE,
                                        MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if (ctx->_local_copy_config == MAP_FAILED) {
        if (ctx->any_key_pressed && ctx->any_key_pressed != MAP_FAILED) munmap(ctx->any_key_pressed, sizeof(int));
        if (ctx->kpm && ctx->kpm != MAP_FAILED) munmap(ctx->kpm, sizeof(int));
        if (ctx->input_counter && ctx->input_counter != MAP_FAILED) munmap(ctx->input_counter, sizeof(atomic_int));
        if (ctx->last_key_pressed_timestamp && ctx->last_key_pressed_timestamp != MAP_FAILED) munmap(ctx->last_key_pressed_timestamp, sizeof(timestamp_ms_t));
        BONGOCAT_LOG_ERROR("Failed to create shared memory for input monitoring: %s", strerror(errno));
        return BONGOCAT_ERROR_MEMORY;
    }
    config_set_defaults(ctx->_local_copy_config);

    ctx->_local_copy_config->keyboard_devices = device_paths;
    ctx->_local_copy_config->num_keyboard_devices = num_devices;
    ctx->_local_copy_config->enable_debug = enable_debug;

    // start input monitoring
    const int result = pthread_create(&ctx->_input_thread, NULL, capture_input_thread, ctx);
    if (result != 0) {
        atomic_store(&ctx->_capture_input_running, false);
        BONGOCAT_LOG_ERROR("Failed to fork input monitoring process: %s", strerror(errno));
        if (ctx->any_key_pressed && ctx->any_key_pressed != MAP_FAILED) munmap(ctx->any_key_pressed, sizeof(int));
        if (ctx->kpm  && ctx->kpm != MAP_FAILED) munmap(ctx->kpm, sizeof(int));
        if (ctx->input_counter && ctx->input_counter != MAP_FAILED) munmap(ctx->input_counter, sizeof(atomic_int));
        if (ctx->last_key_pressed_timestamp && ctx->last_key_pressed_timestamp != MAP_FAILED) munmap(ctx->last_key_pressed_timestamp, sizeof(timestamp_ms_t));
        if (ctx->_local_copy_config && ctx->_local_copy_config != MAP_FAILED) munmap(ctx->_local_copy_config, sizeof(config_t));
        ctx->any_key_pressed = NULL;
        ctx->kpm = NULL;
        ctx->input_counter = NULL;
        ctx->last_key_pressed_timestamp = NULL;
        ctx->_local_copy_config = NULL;
        return BONGOCAT_ERROR_THREAD;
    }
    
    BONGOCAT_LOG_INFO("Input monitoring started");
    return BONGOCAT_SUCCESS;
}

bongocat_error_t input_restart_monitoring(input_context_t* ctx, char **device_paths, int num_devices, int enable_debug) {
    assert(ctx);
    // read-only config
    const config_t* const current_config = ctx->_local_copy_config;

    BONGOCAT_LOG_INFO("Restarting input monitoring system");

    // assume the passed setting comes from the (same) config
    if (current_config) {
        if (device_paths != current_config->keyboard_devices ||
            num_devices != current_config->num_keyboard_devices ||
            enable_debug != current_config->enable_debug) {
            BONGOCAT_LOG_DEBUG("Parameter for restarting monitoring don't match with settings from config");
        }
    }

    ctx->_input_kpm_counter = 0;
    //ctx->_latest_kpm_update_ms = get_current_time_ms();
    
    // Stop current monitoring
    if (ctx->_input_thread) {
        BONGOCAT_LOG_DEBUG("Input monitoring thread");
        atomic_store(&ctx->_capture_input_running, false);
        pthread_cancel(ctx->_input_thread);
        pthread_join(ctx->_input_thread, NULL);
        BONGOCAT_LOG_DEBUG("Input monitoring thread terminated");
    }

    // already done when stop current input thread
    /*
    // Close all (open) file descriptors
    if (ctx->_fds) {
        for (int i = 0; i < ctx->_fds_count; i++) {
            if (ctx->_fds[i] >= 0) {
                close(ctx->_fds[i]);
            }
        }
    }
    BONGOCAT_SAFE_FREE(ctx->_fds);
    ctx->_fds_count = 0;
    BONGOCAT_SAFE_FREE(ctx->_unique_paths_indices);
    ctx->_unique_paths_indices_count = 0;
    */
    
    // Start new monitoring (reuse shared memory if it exists)
    const bool need_new_shm_any_key_pressed = (ctx->any_key_pressed == NULL || ctx->any_key_pressed == MAP_FAILED);
    if (need_new_shm_any_key_pressed) {
        ctx->any_key_pressed = (int *)mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE,
                                     MAP_SHARED | MAP_ANONYMOUS, -1, 0);
        if (ctx->any_key_pressed == MAP_FAILED) {
            BONGOCAT_LOG_ERROR("Failed to create shared memory for input monitoring: %s", strerror(errno));
            if (ctx->any_key_pressed != MAP_FAILED) munmap(ctx->any_key_pressed, sizeof(int));
            if (ctx->kpm != MAP_FAILED) munmap(ctx->kpm, sizeof(int));
            if (ctx->input_counter != MAP_FAILED) munmap(ctx->input_counter, sizeof(atomic_int));
            if (ctx->last_key_pressed_timestamp != MAP_FAILED) munmap(ctx->last_key_pressed_timestamp, sizeof(timestamp_ms_t));
            if (ctx->_local_copy_config != MAP_FAILED) munmap(ctx->_local_copy_config, sizeof(config_t));
            ctx->any_key_pressed = NULL;
            ctx->kpm = NULL;
            ctx->input_counter = NULL;
            ctx->last_key_pressed_timestamp = NULL;
            ctx->_local_copy_config = NULL;
            return BONGOCAT_ERROR_MEMORY;
        }
    }
    if (ctx->any_key_pressed) *ctx->any_key_pressed = 0;

    const bool need_new_shm_kpm = (ctx->kpm == NULL || ctx->kpm == MAP_FAILED);
    if (need_new_shm_kpm) {
        ctx->kpm = (int *)mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE,
                                     MAP_SHARED | MAP_ANONYMOUS, -1, 0);
        if (ctx->kpm == MAP_FAILED) {
            BONGOCAT_LOG_ERROR("Failed to create shared memory for input monitoring: %s", strerror(errno));
            if (ctx->any_key_pressed != MAP_FAILED) munmap(ctx->any_key_pressed, sizeof(int));
            if (ctx->kpm != MAP_FAILED) munmap(ctx->kpm, sizeof(int));
            if (ctx->input_counter != MAP_FAILED) munmap(ctx->input_counter, sizeof(atomic_int));
            if (ctx->last_key_pressed_timestamp != MAP_FAILED) munmap(ctx->last_key_pressed_timestamp, sizeof(timestamp_ms_t));
            if (ctx->_local_copy_config != MAP_FAILED) munmap(ctx->_local_copy_config, sizeof(config_t));
            ctx->any_key_pressed = NULL;
            ctx->kpm = NULL;
            ctx->input_counter = NULL;
            ctx->last_key_pressed_timestamp = NULL;
            ctx->_local_copy_config = NULL;
            return BONGOCAT_ERROR_MEMORY;
        }
    }
    if (ctx->kpm) *ctx->kpm = 0;

    const bool need_new_shm_input_counter = (ctx->input_counter == NULL || ctx->input_counter == MAP_FAILED);
    if (need_new_shm_input_counter) {
        ctx->input_counter = (atomic_int *)mmap(NULL, sizeof(atomic_int), PROT_READ | PROT_WRITE,
                                     MAP_SHARED | MAP_ANONYMOUS, -1, 0);
        if (ctx->input_counter == MAP_FAILED) {
            BONGOCAT_LOG_ERROR("Failed to create shared memory for input monitoring: %s", strerror(errno));
            if (ctx->any_key_pressed != MAP_FAILED) munmap(ctx->any_key_pressed, sizeof(int));
            if (ctx->kpm != MAP_FAILED) munmap(ctx->kpm, sizeof(int));
            if (ctx->input_counter != MAP_FAILED) munmap(ctx->input_counter, sizeof(atomic_int));
            if (ctx->last_key_pressed_timestamp != MAP_FAILED) munmap(ctx->last_key_pressed_timestamp, sizeof(timestamp_ms_t));
            if (ctx->_local_copy_config != MAP_FAILED) munmap(ctx->_local_copy_config, sizeof(config_t));
            ctx->any_key_pressed = NULL;
            ctx->kpm = NULL;
            ctx->input_counter = NULL;
            ctx->last_key_pressed_timestamp = NULL;
            ctx->_local_copy_config = NULL;
            return BONGOCAT_ERROR_MEMORY;
        }
    }
    if (ctx->input_counter) *ctx->input_counter = 0;

    const bool need_new_shm_last_key_pressed_timestamp = (ctx->last_key_pressed_timestamp == NULL || ctx->last_key_pressed_timestamp == MAP_FAILED);
    if (need_new_shm_last_key_pressed_timestamp) {
        ctx->last_key_pressed_timestamp = (timestamp_ms_t *)mmap(NULL, sizeof(timestamp_ms_t), PROT_READ | PROT_WRITE,
                                     MAP_SHARED | MAP_ANONYMOUS, -1, 0);
        if (ctx->last_key_pressed_timestamp == MAP_FAILED) {
            BONGOCAT_LOG_ERROR("Failed to create shared memory for input monitoring: %s", strerror(errno));
            if (ctx->any_key_pressed != MAP_FAILED) munmap(ctx->any_key_pressed, sizeof(int));
            if (ctx->kpm != MAP_FAILED) munmap(ctx->kpm, sizeof(int));
            if (ctx->input_counter != MAP_FAILED) munmap(ctx->input_counter, sizeof(atomic_int));
            if (ctx->last_key_pressed_timestamp != MAP_FAILED) munmap(ctx->last_key_pressed_timestamp, sizeof(timestamp_ms_t));
            if (ctx->_local_copy_config != MAP_FAILED) munmap(ctx->_local_copy_config, sizeof(config_t));
            ctx->any_key_pressed = NULL;
            ctx->kpm = NULL;
            ctx->input_counter = NULL;
            ctx->last_key_pressed_timestamp = NULL;
            ctx->_local_copy_config = NULL;
            return BONGOCAT_ERROR_MEMORY;
        }
    }
    if (ctx->last_key_pressed_timestamp) *ctx->last_key_pressed_timestamp = 0;

    const bool need_new_shm_local_copy_config = (ctx->_local_copy_config == NULL || ctx->_local_copy_config == MAP_FAILED);
    if (need_new_shm_local_copy_config) {
        ctx->_local_copy_config = (config_t *)mmap(NULL, sizeof(config_t), PROT_READ | PROT_WRITE,
                                     MAP_SHARED | MAP_ANONYMOUS, -1, 0);
        if (ctx->_local_copy_config == MAP_FAILED) {
            BONGOCAT_LOG_ERROR("Failed to create shared memory for input monitoring: %s", strerror(errno));
            if (ctx->any_key_pressed != MAP_FAILED) munmap(ctx->any_key_pressed, sizeof(int));
            if (ctx->kpm != MAP_FAILED) munmap(ctx->kpm, sizeof(int));
            if (ctx->input_counter != MAP_FAILED) munmap(ctx->input_counter, sizeof(atomic_int));
            if (ctx->last_key_pressed_timestamp != MAP_FAILED) munmap(ctx->last_key_pressed_timestamp, sizeof(timestamp_ms_t));
            if (ctx->_local_copy_config != MAP_FAILED) munmap(ctx->_local_copy_config, sizeof(config_t));
            ctx->any_key_pressed = NULL;
            ctx->kpm = NULL;
            ctx->input_counter = NULL;
            ctx->last_key_pressed_timestamp = NULL;
            ctx->_local_copy_config = NULL;
            return BONGOCAT_ERROR_MEMORY;
        }
    }
    if (ctx->_local_copy_config) config_set_defaults(ctx->_local_copy_config);
    ctx->_local_copy_config->keyboard_devices = device_paths;
    ctx->_local_copy_config->num_keyboard_devices = num_devices;
    ctx->_local_copy_config->enable_debug = enable_debug;

    // start input monitoring
    if (pthread_create(&ctx->_input_thread, NULL, capture_input_thread, ctx) != 0) {
        BONGOCAT_LOG_ERROR("Failed to fork input monitoring process: %s", strerror(errno));
        if (ctx->any_key_pressed != MAP_FAILED) munmap(ctx->any_key_pressed, sizeof(int));
        if (ctx->kpm != MAP_FAILED) munmap(ctx->kpm, sizeof(int));
        if (ctx->input_counter != MAP_FAILED) munmap(ctx->input_counter, sizeof(atomic_int));
        if (ctx->last_key_pressed_timestamp != MAP_FAILED) munmap(ctx->last_key_pressed_timestamp, sizeof(timestamp_ms_t));
        if (ctx->_local_copy_config != MAP_FAILED) munmap(ctx->_local_copy_config, sizeof(config_t));
        ctx->any_key_pressed = NULL;
        ctx->kpm = NULL;
        ctx->input_counter = NULL;
        ctx->last_key_pressed_timestamp = NULL;
        ctx->_local_copy_config = NULL;
        return BONGOCAT_ERROR_THREAD;
    }

    BONGOCAT_LOG_INFO("Input monitoring restarted");
    return BONGOCAT_SUCCESS;
}

void input_cleanup(input_context_t* ctx) {
    BONGOCAT_LOG_INFO("Cleaning up input monitoring system");
    
    if (ctx->_input_thread) {
        atomic_store(&ctx->_capture_input_running, false);
        pthread_cancel(ctx->_input_thread);
        pthread_join(ctx->_input_thread, NULL);
        ctx->_input_thread = 0;
        BONGOCAT_LOG_DEBUG("Input monitoring thread terminated");
    }

    // should be done in cancel thread
    /*
    // Close all (open) file descriptors
    if (ctx->_fds) {
        for (size_t i = 0; i < ctx->_fds_count; i++) {
            if (ctx->_fds[i] >= 0) {
                close(ctx->_fds[i]);
            }
        }
    }
    BONGOCAT_SAFE_FREE(ctx->_fds);
    ctx->_fds_count = 0;
    BONGOCAT_SAFE_FREE(ctx->_unique_paths_indices);
    ctx->_unique_paths_indices_count = 0;
    */
    
    // Cleanup shared memory
    if (ctx->any_key_pressed && ctx->any_key_pressed != MAP_FAILED) {
        munmap(ctx->any_key_pressed, sizeof(int));
        ctx->any_key_pressed = NULL;
    }
    if (ctx->kpm && ctx->kpm != MAP_FAILED) {
        munmap(ctx->kpm, sizeof(int));
        ctx->kpm = NULL;
    }
    if (ctx->input_counter && ctx->input_counter != MAP_FAILED) {
        munmap(ctx->input_counter, sizeof(atomic_int));
        ctx->input_counter = NULL;
    }
    if (ctx->last_key_pressed_timestamp && ctx->last_key_pressed_timestamp != MAP_FAILED) {
        munmap(ctx->last_key_pressed_timestamp, sizeof(timestamp_ms_t));
        ctx->last_key_pressed_timestamp = NULL;
    }
    if (ctx->_local_copy_config && ctx->_local_copy_config != MAP_FAILED) {
        munmap(ctx->_local_copy_config, sizeof(config_t));
        ctx->_local_copy_config = NULL;
    }

    ctx->_input_kpm_counter = 0;
    ctx->_latest_kpm_update_ms = 0;
    
    BONGOCAT_LOG_DEBUG("Input monitoring cleanup complete");
}

void input_update_config(input_context_t *ctx, const config_t* config) {
    assert(ctx);
    assert(config);
    assert(ctx->_local_copy_config && ctx->_local_copy_config != MAP_FAILED);

    memcpy(ctx->_local_copy_config, config, sizeof(config_t));
}
