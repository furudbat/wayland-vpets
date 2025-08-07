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

// Child process signal handler - exits quietly without logging
static void child_signal_handler(int sig) {
    switch (sig) {
        case SIGINT:
        case SIGTERM:
            _exit(EXIT_SUCCESS);
            //break;
        case SIGCHLD:
            break;
        case SIGUSR2:
            // ignore
            break;
        default:
            BONGOCAT_LOG_WARNING("Received unexpected signal %d", sig);
            break;
    }
}

static void capture_input_multiple(input_context_t *input, char **device_paths, int num_devices, int enable_debug) {
    assert(input);
    assert(num_devices >= 0);
    // read-only config
    const config_t* const current_config = input->_local_copy_config;
    assert(current_config);

    // Set up child-specific signal handlers to avoid duplicate logging
    struct sigaction sa;
    sa.sa_handler = child_signal_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    sigaction(SIGTERM, &sa, NULL);
    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGUSR2, &sa, NULL);
    signal(SIGPIPE, SIG_IGN);

    BONGOCAT_LOG_DEBUG("Starting input capture on %d devices", num_devices);

    int *fds = BONGOCAT_MALLOC(num_devices * sizeof(int));
    int *unique_paths_indices = BONGOCAT_MALLOC(num_devices * sizeof(int));
    if (!fds || !unique_paths_indices) {
        BONGOCAT_SAFE_FREE(fds);
        BONGOCAT_SAFE_FREE(unique_paths_indices);
        atomic_store(&input->_capture_input_running, false);
        BONGOCAT_LOG_ERROR("Failed to allocate memory for file descriptors");
        _exit(EXIT_FAILURE);
    }
    
    int max_fd = -1;
    int valid_devices = 0;
    int unique_devices = 0;
    
    // First pass: deduplicate device paths
    for (int i = 0; i < num_devices; i++) {
        bool is_duplicate = false;
        for (int j = 0; j < unique_devices; j++) {
            if (strcmp(device_paths[i], device_paths[unique_paths_indices[j]]) == 0) {
                is_duplicate = true;
                break;
            }
        }
        if (!is_duplicate) {
            unique_paths_indices[unique_devices] = i;
            unique_devices++;
        }
    }
    
    BONGOCAT_LOG_DEBUG("Deduplicated %d devices to %d unique devices", num_devices, unique_devices);
    
    // Open all unique devices
    for (int i = 0; i < unique_devices; i++) {
        fds[i] = -1;
        
        // Validate device path exists and is readable
        struct stat st;
        if (stat(device_paths[unique_paths_indices[i]], &st) != 0) {
            BONGOCAT_LOG_WARNING("Input device does not exist: %s", device_paths[unique_paths_indices[i]]);
            continue;
        }
        
        if (!S_ISCHR(st.st_mode)) {
            BONGOCAT_LOG_WARNING("Input device is not a character device: %s", device_paths[unique_paths_indices[i]]);
            continue;
        }
        
        fds[i] = open(device_paths[unique_paths_indices[i]], O_RDONLY | O_NONBLOCK);
        if (fds[i] < 0) {
            BONGOCAT_LOG_WARNING("Failed to open %s: %s", device_paths[unique_paths_indices[i]], strerror(errno));
            continue;
        }
        
        BONGOCAT_LOG_INFO("Input monitoring started on %s (fd=%d)", device_paths[unique_paths_indices[i]], fds[i]);
        if (fds[i] > max_fd) {
            max_fd = fds[i];
        }
        valid_devices++;
    }
    
    // Update num_devices to reflect unique devices for the rest of the function
    num_devices = unique_devices;
    
    if (valid_devices == 0) {
        atomic_store(&input->_capture_input_running, false);
        BONGOCAT_LOG_ERROR("No valid input devices found");
        BONGOCAT_SAFE_FREE(fds);
        _exit(EXIT_FAILURE);
    }
    
    BONGOCAT_LOG_INFO("Successfully opened %d/%d input devices", valid_devices, num_devices);

    struct input_event ev[INPUT_EVENT_BUF]; // Increased buffer size for better I/O efficiency
    int rd;
    fd_set readfds;
    int check_counter = 0;  // check is done every second (see timeout below)
    int adaptive_check_interval_sec = START_ADAPTIVE_CHECK_INTERVAL_SEC; // increase over time

    atomic_store(&input->_capture_input_running, true);
    while (atomic_load(&input->_capture_input_running)) {
        FD_ZERO(&readfds);
        
        // Optimize: only rebuild fd_set when devices change, track current max_fd
        int current_max_fd = -1;
        for (int i = 0; i < num_devices; i++) {
            if (fds[i] >= 0) {
                FD_SET(fds[i], &readfds);
                if (fds[i] > current_max_fd) {
                    current_max_fd = fds[i];
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
                for (int i = 0; i < num_devices; i++) {
                    if (fds[i] < 0) { // Device was not available before
                        struct stat st;
                        if (stat(device_paths[unique_paths_indices[i]], &st) == 0 && S_ISCHR(st.st_mode)) {
                            // Device is now available, try to open it
                            int new_fd = open(device_paths[unique_paths_indices[i]], O_RDONLY | O_NONBLOCK);
                            if (new_fd >= 0) {
                                fds[i] = new_fd;
                                if (new_fd > max_fd) {
                                    max_fd = new_fd;
                                }
                                valid_devices++;
                                found_new_device = true;
                                BONGOCAT_LOG_INFO("New input device detected and opened: %s (fd=%d)", device_paths[unique_paths_indices[i]], new_fd);
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
        for (int i = 0; i < num_devices; i++) {
            if (fds[i] >= 0 && FD_ISSET(fds[i], &readfds)) {
                rd = read(fds[i], ev, sizeof(ev));
                // error
                if (rd < 0) {
                    if (errno == EAGAIN) continue;
                    BONGOCAT_LOG_WARNING("Read error on %s: %s", device_paths[unique_paths_indices[i]], strerror(errno));
                    close(fds[i]);
                    fds[i] = -1;
                    valid_devices--;
                    continue;
                }
                // empty
                if (rd == 0) {
                    BONGOCAT_LOG_WARNING("EOF on input device %s", device_paths[unique_paths_indices[i]]);
                    close(fds[i]);
                    fds[i] = -1;
                    valid_devices--;
                    continue;
                }
                // check for full size
                if (rd % sizeof(struct input_event) != 0) {
                    BONGOCAT_LOG_WARNING("Partial input_event read from device %s", device_paths[unique_paths_indices[i]]);
                    close(fds[i]);
                    fds[i] = -1;
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
                                                 device_paths[unique_paths_indices[i]], ev[j].code, ev[j].time.tv_sec, ev[j].time.tv_usec);
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
                    //BONGOCAT_LOG_DEBUG("Input KPM: %d, counter: %d", *input->kpm, *input->input_counter);
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

    // Close all file descriptors
    for (int i = 0; i < num_devices; i++) {
        if (fds[i] >= 0) {
            close(fds[i]);
        }
    }
    
    BONGOCAT_SAFE_FREE(fds);
    BONGOCAT_SAFE_FREE(unique_paths_indices);
    BONGOCAT_LOG_INFO("Input monitoring stopped");
}

bongocat_error_t input_start_monitoring(input_context_t* ctx, char **device_paths, int num_devices, int enable_debug) {
    assert(ctx);

    BONGOCAT_CHECK_NULL(device_paths, BONGOCAT_ERROR_INVALID_PARAM);
    
    if (num_devices <= 0) {
        BONGOCAT_LOG_ERROR("No input devices specified");
        return BONGOCAT_ERROR_INVALID_PARAM;
    }

    const timestamp_ms_t now = get_current_time_ms();
    ctx->_input_child_pid = -1;
    ctx->_capture_input_running = false;
    ctx->_input_kpm_counter = 0;
    ctx->_latest_kpm_update_ms = now;

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
        if (ctx->any_key_pressed != MAP_FAILED) munmap(ctx->any_key_pressed, sizeof(int));
        BONGOCAT_LOG_ERROR("Failed to create shared memory for input monitoring: %s", strerror(errno));
        return BONGOCAT_ERROR_MEMORY;
    }
    *ctx->kpm = 0;

    // Initialize shared memory for counter
    ctx->input_counter = (atomic_int *)mmap(NULL, sizeof(atomic_int), PROT_READ | PROT_WRITE,
                                        MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if (ctx->input_counter == MAP_FAILED) {
        if (ctx->any_key_pressed != MAP_FAILED) munmap(ctx->any_key_pressed, sizeof(int));
        if (ctx->kpm != MAP_FAILED) munmap(ctx->kpm, sizeof(int));
        BONGOCAT_LOG_ERROR("Failed to create shared memory for input monitoring: %s", strerror(errno));
        return BONGOCAT_ERROR_MEMORY;
    }
    *ctx->input_counter = 0;

    // Initialize shared memory for timestamp
    ctx->last_key_pressed_timestamp = (timestamp_ms_t *)mmap(NULL, sizeof(timestamp_ms_t), PROT_READ | PROT_WRITE,
                                        MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if (ctx->last_key_pressed_timestamp == MAP_FAILED) {
        if (ctx->any_key_pressed != MAP_FAILED) munmap(ctx->any_key_pressed, sizeof(int));
        if (ctx->kpm != MAP_FAILED) munmap(ctx->kpm, sizeof(int));
        if (ctx->input_counter != MAP_FAILED) munmap(ctx->input_counter, sizeof(atomic_int));
        BONGOCAT_LOG_ERROR("Failed to create shared memory for input monitoring: %s", strerror(errno));
        return BONGOCAT_ERROR_MEMORY;
    }
    *ctx->last_key_pressed_timestamp = now;

    // Initialize shared memory for local config
    ctx->_local_copy_config = (config_t *)mmap(NULL, sizeof(config_t), PROT_READ | PROT_WRITE,
                                        MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if (ctx->_local_copy_config == MAP_FAILED) {
        if (ctx->any_key_pressed != MAP_FAILED) munmap(ctx->any_key_pressed, sizeof(int));
        if (ctx->kpm != MAP_FAILED) munmap(ctx->kpm, sizeof(int));
        if (ctx->input_counter != MAP_FAILED) munmap(ctx->input_counter, sizeof(atomic_int));
        if (ctx->last_key_pressed_timestamp != MAP_FAILED) munmap(ctx->last_key_pressed_timestamp, sizeof(timestamp_ms_t));
        BONGOCAT_LOG_ERROR("Failed to create shared memory for input monitoring: %s", strerror(errno));
        return BONGOCAT_ERROR_MEMORY;
    }
    config_set_defaults(ctx->_local_copy_config);

    // Fork process for input monitoring
    ctx->_input_child_pid = fork();
    if (ctx->_input_child_pid < 0) {
        atomic_store(&ctx->_capture_input_running, false);
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

    if (ctx->_input_child_pid == 0) {
        // Child process - handle keyboard input from multiple devices
        BONGOCAT_LOG_DEBUG("Input monitoring child process started (PID: %d)", getpid());
        // use _exit, when running in a child process
        capture_input_multiple(ctx, device_paths, num_devices, enable_debug);
        _exit(EXIT_SUCCESS);
    }
    
    BONGOCAT_LOG_INFO("Input monitoring started (child PID: %d)", ctx->_input_child_pid);
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
            BONGOCAT_LOG_DEBUG("Parameter for restarting monitoring don't match with setting from config");
            }
    }

    ctx->_input_kpm_counter = 0;
    //ctx->_latest_kpm_update_ms = get_current_time_ms();
    
    // Stop current monitoring
    if (ctx->_input_child_pid > 0) {
        BONGOCAT_LOG_DEBUG("Stopping current input monitoring (PID: %d)", ctx->_input_child_pid);
        kill(ctx->_input_child_pid, SIGTERM);
        
        // Wait for child to terminate with timeout
        int status;
        int wait_attempts = 0;
        while (wait_attempts < CHILD_TERMINATE_WAIT_ATTEMPTS) {
            pid_t result = waitpid(ctx->_input_child_pid, &status, WNOHANG);
            if (result == ctx->_input_child_pid) {
                atomic_store(&ctx->_capture_input_running, false);
                BONGOCAT_LOG_DEBUG("Previous input monitoring process terminated");
                break;
            } else if (result == -1 && ctx->_capture_input_running) {
                atomic_store(&ctx->_capture_input_running, false);
                BONGOCAT_LOG_WARNING("Error waiting for input child process: %s", strerror(errno));
                break;
            }
            
            usleep(CHILD_TERMINATE_WAIT_ATTEMPT_SLEEP_MS*1000);
            wait_attempts++;
        }
        
        // Force kill if still running
        if (wait_attempts >= CHILD_TERMINATE_WAIT_ATTEMPTS) {
            atomic_store(&ctx->_capture_input_running, false);
            BONGOCAT_LOG_WARNING("Force killing previous input monitoring process");
            kill(ctx->_input_child_pid, SIGKILL);
            waitpid(ctx->_input_child_pid, &status, 0);
        }
        
        ctx->_input_child_pid = -1;
    }
    
    // Start new monitoring (reuse shared memory if it exists)
    const bool need_new_shm_any_key_pressed = (ctx->any_key_pressed == NULL || ctx->any_key_pressed == MAP_FAILED);
    if (need_new_shm_any_key_pressed) {
        ctx->any_key_pressed = (int *)mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE,
                                     MAP_SHARED | MAP_ANONYMOUS, -1, 0);
        if (ctx->any_key_pressed == MAP_FAILED) {
            BONGOCAT_LOG_ERROR("Failed to create shared memory for input monitoring: %s", strerror(errno));
            return BONGOCAT_ERROR_MEMORY;
        }
        *ctx->any_key_pressed = 0;
    }
    const bool need_new_shm_kpm = (ctx->kpm == NULL || ctx->kpm == MAP_FAILED);
    if (need_new_shm_kpm) {
        ctx->kpm = (int *)mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE,
                                     MAP_SHARED | MAP_ANONYMOUS, -1, 0);
        if (ctx->kpm == MAP_FAILED) {
            BONGOCAT_LOG_ERROR("Failed to create shared memory for input monitoring: %s", strerror(errno));
            return BONGOCAT_ERROR_MEMORY;
        }
        *ctx->kpm = 0;
    }
    const bool need_new_shm_input_counter = (ctx->input_counter == NULL || ctx->input_counter == MAP_FAILED);
    if (need_new_shm_input_counter) {
        ctx->input_counter = (atomic_int *)mmap(NULL, sizeof(atomic_int), PROT_READ | PROT_WRITE,
                                     MAP_SHARED | MAP_ANONYMOUS, -1, 0);
        if (ctx->input_counter == MAP_FAILED) {
            BONGOCAT_LOG_ERROR("Failed to create shared memory for input monitoring: %s", strerror(errno));
            return BONGOCAT_ERROR_MEMORY;
        }
        *ctx->input_counter = 0;
    }
    const bool need_new_shm_last_key_pressed_timestamp = (ctx->last_key_pressed_timestamp == NULL || ctx->last_key_pressed_timestamp == MAP_FAILED);
    if (need_new_shm_last_key_pressed_timestamp) {
        ctx->last_key_pressed_timestamp = (timestamp_ms_t *)mmap(NULL, sizeof(timestamp_ms_t), PROT_READ | PROT_WRITE,
                                     MAP_SHARED | MAP_ANONYMOUS, -1, 0);
        if (ctx->last_key_pressed_timestamp == MAP_FAILED) {
            BONGOCAT_LOG_ERROR("Failed to create shared memory for input monitoring: %s", strerror(errno));
            return BONGOCAT_ERROR_MEMORY;
        }
        *ctx->last_key_pressed_timestamp = 0;
    }
    const bool need_new_shm_local_copy_config = (ctx->_local_copy_config == NULL || ctx->_local_copy_config == MAP_FAILED);
    if (need_new_shm_local_copy_config) {
        ctx->_local_copy_config = (config_t *)mmap(NULL, sizeof(config_t), PROT_READ | PROT_WRITE,
                                     MAP_SHARED | MAP_ANONYMOUS, -1, 0);
        if (ctx->_local_copy_config == MAP_FAILED) {
            BONGOCAT_LOG_ERROR("Failed to create shared memory for input monitoring: %s", strerror(errno));
            return BONGOCAT_ERROR_MEMORY;
        }
        config_set_defaults(ctx->_local_copy_config);
    }

    // Fork new process for input monitoring
    ctx->_input_child_pid = fork();
    if (ctx->_input_child_pid < 0) {
        BONGOCAT_LOG_ERROR("Failed to fork input monitoring process: %s", strerror(errno));
        if (need_new_shm_any_key_pressed) {
            munmap(ctx->any_key_pressed, sizeof(int));
            ctx->any_key_pressed = NULL;
        }
        if (need_new_shm_kpm) {
            munmap(ctx->kpm, sizeof(int));
            ctx->kpm = NULL;
        }
        if (need_new_shm_input_counter) {
            munmap(ctx->input_counter, sizeof(atomic_int));
            ctx->input_counter = NULL;
        }
        if (need_new_shm_last_key_pressed_timestamp) {
            munmap(ctx->last_key_pressed_timestamp, sizeof(timestamp_ms_t));
            ctx->last_key_pressed_timestamp = NULL;
        }
        if (need_new_shm_local_copy_config) {
            munmap(ctx->_local_copy_config, sizeof(config_t));
            ctx->_local_copy_config = NULL;
        }
        return BONGOCAT_ERROR_THREAD;
    }
    
    if (ctx->_input_child_pid == 0) {
        atomic_store(&ctx->_capture_input_running, false);
        // Child process - handle keyboard input from multiple devices
        BONGOCAT_LOG_DEBUG("Input monitoring child process restarted (PID: %d)", getpid());
        capture_input_multiple(ctx, device_paths, num_devices, enable_debug);
        _exit(0);
    }
    
    BONGOCAT_LOG_INFO("Input monitoring restarted (child PID: %d)", ctx->_input_child_pid);
    return BONGOCAT_SUCCESS;
}

void input_cleanup(input_context_t* ctx) {
    BONGOCAT_LOG_INFO("Cleaning up input monitoring system");
    
    // Terminate child process if it exists
    if (ctx->_input_child_pid > 0) {
        atomic_store(&ctx->_capture_input_running, false);
        BONGOCAT_LOG_DEBUG("Terminating input monitoring child process (PID: %d)", ctx->_input_child_pid);
        kill(ctx->_input_child_pid, SIGTERM);
        
        // Wait for child to terminate with timeout
        int status;
        int wait_attempts = 0;
        while (wait_attempts < CHILD_TERMINATE_WAIT_ATTEMPTS) {
            const pid_t result = waitpid(ctx->_input_child_pid, &status, WNOHANG);
            if (result == ctx->_input_child_pid) {
                atomic_store(&ctx->_capture_input_running, false);
                BONGOCAT_LOG_DEBUG("Input monitoring child process terminated gracefully");
                break;
            } else if (result == -1 && ctx->_capture_input_running) {
                atomic_store(&ctx->_capture_input_running, false);
                BONGOCAT_LOG_WARNING("Error waiting for input child process: %s", strerror(errno));
                break;
            }
            
            usleep(CHILD_TERMINATE_WAIT_ATTEMPT_SLEEP_MS*1000);
            wait_attempts++;
        }
        
        // Force kill if still running
        if (wait_attempts >= CHILD_TERMINATE_WAIT_ATTEMPTS) {
            atomic_store(&ctx->_capture_input_running, false);
            BONGOCAT_LOG_WARNING("Force killing input monitoring child process");
            kill(ctx->_input_child_pid, SIGKILL);
            waitpid(ctx->_input_child_pid, &status, 0);
        }
        
        ctx->_input_child_pid = -1;
    }
    
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
