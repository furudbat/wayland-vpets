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
#include <limits.h>
#include <poll.h>

#include "platform/wayland.h"

#define INPUT_EVENT_BUF 128     // Increased buffer size for better I/O efficiency
#define MAX_POLL_FDS 256
#define INPUT_POOL_TIMEOUT_MS MAX_INPUT_DEVICES

#define START_ADAPTIVE_CHECK_INTERVAL_SEC 5
#define MID_ADAPTIVE_CHECK_INTERVAL_SEC 15
#define MAX_ADAPTIVE_CHECK_INTERVAL_SEC 30

#define RESET_KPM_TIMEOUT_MS (5*1000)

#define CHILD_TERMINATE_WAIT_ATTEMPTS 10
#define CHILD_TERMINATE_WAIT_ATTEMPT_SLEEP_MS 100

static void set_default_input_thread_context(input_context_t* input) {
    assert(input);

    input->_device_paths = NULL;
    input->_device_paths_count = 0;

    input->_fds = NULL;
    input->_fds_count = 0;

    input->_unique_paths_indices = NULL;
    input->_unique_paths_indices_count = 0;
}

static void cleanup_input_thread_context(input_context_t* input) {
    assert(input);

    assert(input->_device_paths_count >= 0);
    for (int i = 0; i < input->_device_paths_count; i++) {
        if (input->_device_paths[i]) free(input->_device_paths[i]);
        input->_device_paths[i] = NULL;
    }
    BONGOCAT_SAFE_FREE(input->_device_paths);
    input->_device_paths = NULL;
    input->_device_paths_count = 0;

    // Close and free file descriptors
    if (input->_fds) {
        for (size_t i = 0; i < input->_fds_count; ++i) {
            if (input->_fds[i] >= 0) {
                close(input->_fds[i]);
                input->_fds[i] = -1;
            }
        }
        BONGOCAT_SAFE_FREE(input->_fds);
    }
    input->_fds = NULL;
    input->_fds_count = 0;

    BONGOCAT_SAFE_FREE(input->_unique_paths_indices);
    input->_unique_paths_indices = NULL;
    input->_unique_paths_indices_count = 0;

    set_default_input_thread_context(input);
}

static void cleanup_input_thread(void* arg) {
    assert(arg);
    animation_trigger_context_t* trigger_ctx = arg;
    assert(trigger_ctx->_anim);
    //animation_context_t* ctx = trigger_ctx->_anim;
    input_context_t* input = trigger_ctx->_input;

    atomic_store(&input->_capture_input_running, false);

    cleanup_input_thread_context(input);

    BONGOCAT_LOG_INFO("Input thread cleanup completed (via pthread_cancel)");
}

static void* capture_input_thread(void* arg) {
    assert(arg);
    animation_trigger_context_t* trigger_ctx = arg;
    assert(trigger_ctx->_anim);
    //animation_context_t* ctx = trigger_ctx->_anim;
    input_context_t* input = trigger_ctx->_input;

    // read-only config
    const config_t *const current_config = input->_local_copy_config;
    assert(current_config);
    const bool enable_debug = current_config->enable_debug;

    // keep local copies of device_paths
    do {
        assert(current_config->num_keyboard_devices >= 0);
        input->_device_paths_count = current_config->num_keyboard_devices;
        const char *const *device_paths = (const char * const*)current_config->keyboard_devices;        // pls don't modify single keyboard_devices (string)
        input->_device_paths = BONGOCAT_MALLOC(input->_device_paths_count * sizeof(char*));
        for (int i = 0; i < input->_device_paths_count; i++) {
            input->_device_paths[i] = strdup(device_paths[i]);
            if (!input->_device_paths[i]) {
                atomic_store(&input->_capture_input_running, false);
                for (int j = 0; j < i; j++) {
                    if (input->_device_paths[j]) free(input->_device_paths[j]);
                    input->_device_paths[j] = NULL;
                }
                cleanup_input_thread_context(input);
                BONGOCAT_LOG_ERROR("Failed to allocate memory for device_paths");
                return NULL;
            }
        }
    } while(0);

    BONGOCAT_LOG_DEBUG("Starting input capture on %d devices", input->_device_paths_count);

    input->_fds_count = input->_device_paths_count;
    input->_fds = BONGOCAT_MALLOC(input->_fds_count * sizeof(int));
    input->_unique_paths_indices_count = input->_device_paths_count;
    input->_unique_paths_indices = BONGOCAT_MALLOC(input->_unique_paths_indices_count * sizeof(size_t));
    if (!input->_fds || !input->_unique_paths_indices) {
        atomic_store(&input->_capture_input_running, false);
        BONGOCAT_SAFE_FREE(input->_fds);
        input->_fds = NULL;
        input->_fds_count = 0;
        BONGOCAT_SAFE_FREE(input->_unique_paths_indices);
        input->_unique_paths_indices = NULL;
        input->_unique_paths_indices_count = 0;
        cleanup_input_thread_context(input);
        BONGOCAT_LOG_ERROR("Failed to allocate memory for file descriptors");
        return NULL;
    }

    int num_unique_devices = 0;
    // First pass: deduplicate device paths
    assert(input->_fds_count <= INT_MAX);
    assert(input->_device_paths_count <= INT_MAX);
    for (int i = 0; i < (int)input->_fds_count && i < (int)input->_device_paths_count; i++) {
        bool is_duplicate = false;
        for (int j = 0; j < num_unique_devices && j < (int)input->_unique_paths_indices_count; j++) {
            const char* device_path = input->_device_paths[i];
            if (strcmp(device_path, input->_device_paths[input->_unique_paths_indices[j]]) == 0) {
                is_duplicate = true;
                break;
            }
        }

        if (!is_duplicate && num_unique_devices < (int)input->_unique_paths_indices_count) {
            input->_unique_paths_indices[num_unique_devices] = i;
            num_unique_devices++;
        }
    }
    assert(num_unique_devices <= input->_device_paths_count);

    BONGOCAT_LOG_DEBUG("Deduplicated %d devices to %d unique devices", input->_device_paths_count, num_unique_devices);

    // Open all unique devices
    int valid_devices = 0;
    assert(input->_fds_count <= INT_MAX);
    assert(input->_device_paths_count <= INT_MAX);
    assert(input->_unique_paths_indices_count <= INT_MAX);
    assert(input->_device_paths_count >= 0);
    for (int i = 0; i < (int)input->_fds_count; i++) {
        input->_fds[i] = -1;
        if (i < input->_device_paths_count && i < (int)input->_unique_paths_indices_count && input->_unique_paths_indices[i] < (size_t)input->_device_paths_count) {
            const char* device_path = input->_device_paths[input->_unique_paths_indices[i]];

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
            valid_devices++;
        }
    }

    // Update num_devices to reflect unique devices for the rest of the function
    if (valid_devices == 0) {
        atomic_store(&input->_capture_input_running, false);
        BONGOCAT_LOG_ERROR("No valid input devices found");
        cleanup_input_thread_context(input);
        return NULL;
    }

    BONGOCAT_LOG_INFO("Successfully opened %d/%d input devices", valid_devices, input->_device_paths_count);
    // trigger initial render
    wayland_request_render(trigger_ctx);

    pthread_cleanup_push(cleanup_input_thread, arg);

    int check_counter = 0;  // check is done periodically
    int adaptive_check_interval_sec = START_ADAPTIVE_CHECK_INTERVAL_SEC;
    struct pollfd pfds[MAX_POLL_FDS] = {0};
    struct input_event ev[INPUT_EVENT_BUF] = {0};

    atomic_store(&input->_capture_input_running, true);
    while (atomic_load(&input->_capture_input_running)) {
        pthread_testcancel();  // optional, but makes cancellation more responsive

        // init pollfd array
        nfds_t nfds = 0;
        for (size_t i = 0; i < input->_unique_paths_indices_count && i < MAX_POLL_FDS; i++) {
            if (input->_fds[i] >= 0) {
                nfds++;
            }
        }
        if (nfds == 0) {
            BONGOCAT_LOG_ERROR("All input devices became unavailable");
            break;
        } else if (nfds > MAX_POLL_FDS) {
            BONGOCAT_LOG_ERROR("Max input devices fds: %d/%d (%d)", nfds, MAX_POLL_FDS, input->_unique_paths_indices_count);
        }
        do {
            nfds_t pfds_idx = 0;
            assert(input->_device_paths_count >= 0);
            for (size_t i = 0; i < input->_unique_paths_indices_count && i < (size_t)input->_device_paths_count && i < MAX_POLL_FDS; i++) {
                if (input->_fds[i] >= 0) {
                    pfds[pfds_idx].fd = input->_fds[i];
                    pfds[pfds_idx].events = POLLIN;
                    pfds[pfds_idx].revents = 0;
                    pfds_idx++;
                }
            }
        } while(0);

        const int poll_result = poll(pfds, nfds, INPUT_POOL_TIMEOUT_MS);
        if (poll_result < 0) {
            if (errno == EINTR) continue; // Interrupted by signal
            BONGOCAT_LOG_ERROR("Poll error: %s", strerror(errno));
            break;
        }

        if (poll_result == 0) {
            assert(input->_device_paths_count >= 0);
            // Timeout — adaptive device checking
            check_counter++;
            if (check_counter >= (adaptive_check_interval_sec * (1000 / 100))) {
                check_counter = 0;
                bool found_new_device = false;
                for (size_t i = 0; i < input->_unique_paths_indices_count && i < (size_t)input->_device_paths_count && i < MAX_POLL_FDS; i++) {
                    if (input->_unique_paths_indices[i] >= (size_t)input->_device_paths_count) continue;

                    const char* device_path = input->_device_paths[input->_unique_paths_indices[i]];
                    if (input->_fds[i] < 0) {
                        struct stat st;
                        if (stat(device_path, &st) == 0 && S_ISCHR(st.st_mode)) {
                            int new_fd = open(device_path, O_RDONLY | O_NONBLOCK);
                            if (new_fd >= 0) {
                                input->_fds[i] = new_fd;
                                found_new_device = true;
                                BONGOCAT_LOG_INFO("New input device detected and opened: %s (fd=%d)", device_path, new_fd);
                            }
                        }
                    }
                }

                if (!found_new_device && adaptive_check_interval_sec < MAX_ADAPTIVE_CHECK_INTERVAL_SEC) {
                    adaptive_check_interval_sec =
                        (adaptive_check_interval_sec < MID_ADAPTIVE_CHECK_INTERVAL_SEC)
                            ? MID_ADAPTIVE_CHECK_INTERVAL_SEC
                            : MAX_ADAPTIVE_CHECK_INTERVAL_SEC;
                    BONGOCAT_LOG_DEBUG("Increased device check interval to %d seconds", adaptive_check_interval_sec);
                } else if (found_new_device && adaptive_check_interval_sec > START_ADAPTIVE_CHECK_INTERVAL_SEC) {
                    adaptive_check_interval_sec = START_ADAPTIVE_CHECK_INTERVAL_SEC;
                    BONGOCAT_LOG_DEBUG("Reset device check interval to %d seconds", START_ADAPTIVE_CHECK_INTERVAL_SEC);
                }
            }
            continue;
        }


        // Handle ready devices
        for (nfds_t p = 0; p < nfds; p++) {
            if (pfds[p].revents & POLLIN) {
                const int rd = read(pfds[p].fd, ev, sizeof(ev));
                if (rd < 0) {
                    if (errno == EAGAIN) continue;
                    BONGOCAT_LOG_WARNING("Read error on fd=%d: %s", pfds[p].fd, strerror(errno));
                    close(pfds[p].fd);
                    for (size_t i = 0; i < input->_unique_paths_indices_count; i++) {
                        if (input->_fds[i] == pfds[p].fd) {
                            input->_fds[i] = -1;
                            pfds[i].fd = -1;
                            break;
                        }
                    }
                    pfds[p].fd = -1;
                    continue;
                }
                if (rd == 0 || rd % sizeof(struct input_event) != 0) {
                    BONGOCAT_LOG_WARNING("EOF or partial read on fd=%d", pfds[p].fd);
                    close(pfds[p].fd);
                    for (size_t i = 0; i < input->_unique_paths_indices_count; i++) {
                        if (input->_fds[i] == pfds[p].fd) {
                            input->_fds[i] = -1;
                            pfds[i].fd = -1;
                            break;
                        }
                    }
                    pfds[p].fd = -1;
                    continue;
                }

                const int num_events = rd / sizeof(struct input_event);
                bool key_pressed = false;
                for (int j = 0; j < num_events; j++) {
                    if (ev[j].type == EV_KEY && ev[j].value == 1) {
                        key_pressed = true;
                        if (enable_debug) {
                            BONGOCAT_LOG_VERBOSE("Key event: fd=%d, code=%d, time=%lld.%06lld",
                                                 pfds[p].fd, ev[j].code,
                                                 ev[j].time.tv_sec, ev[j].time.tv_usec);
                        } else {
                            break;
                        }
                    }
                }

                const timestamp_ms_t now = get_current_time_ms();
                if (key_pressed) {
                    if (now - input->_latest_kpm_update_ms >= 2000.0/current_config->fps) {
                        const int input_kpm_counter = atomic_load(&input->_input_kpm_counter);
                        if (input_kpm_counter > 0) {
                            const time_ms_t duration_ms = now - input->_latest_kpm_update_ms;
                            const double duration_min = duration_ms / 60000.0;
                            input->shm->kpm = input_kpm_counter / duration_min;
                            atomic_store(&input->_input_kpm_counter, 0);
                            input->_latest_kpm_update_ms = now;
                        }
                    }
                    input->shm->last_key_pressed_timestamp = now;
                    atomic_fetch_add(&input->shm->input_counter, 1);
                    atomic_fetch_add(&input->_input_kpm_counter, 1);
                    animation_trigger(trigger_ctx);
                } else {
                    if (input->shm->kpm > 0 && now - input->_latest_kpm_update_ms >= RESET_KPM_TIMEOUT_MS) {
                        input->shm->kpm = 0;
                        atomic_store(&input->_input_kpm_counter, 0);
                        input->_latest_kpm_update_ms = now;
                    }
                }
            }

            if (pfds[p].revents & (POLLERR | POLLHUP | POLLNVAL)) {
                close(pfds[p].fd);
                for (size_t i = 0; i < input->_unique_paths_indices_count; i++) {
                    if (input->_fds[i] == pfds[p].fd) {
                        input->_fds[i] = -1;
                        pfds[i].fd = -1;
                        break;
                    }
                }
                pfds[p].fd = -1;
            }
        }

        // revalidate valid devices
        valid_devices = 0;
        assert(input->_fds_count <= INT_MAX);
        assert(input->_device_paths_count <= INT_MAX);
        assert(input->_unique_paths_indices_count <= INT_MAX);
        assert(input->_device_paths_count >= 0);
        for (int i = 0; i < (int)input->_fds_count; i++) {
            input->_fds[i] = -1;
            if (i < input->_device_paths_count && i < (int)input->_unique_paths_indices_count && input->_unique_paths_indices[i] < (size_t)input->_device_paths_count) {
                const char* device_path = input->_device_paths[input->_unique_paths_indices[i]];

                // Validate device path exists and is readable
                struct stat st;
                if (stat(device_path, &st) != 0) {
                    BONGOCAT_LOG_VERBOSE("Input device does not exist: %s", device_path);
                    if (input->_fds[i] >= 0) close(input->_fds[i]);
                    input->_fds[i] = -1;
                }
                if (!S_ISCHR(st.st_mode)) {
                    BONGOCAT_LOG_VERBOSE("Input device is not a character device: %s", device_path);
                    if (input->_fds[i] >= 0) close(input->_fds[i]);
                    input->_fds[i] = -1;
                }

                if (input->_fds[i] < 0) {
                    input->_fds[i] = open(device_path, O_RDONLY | O_NONBLOCK);
                    if (input->_fds[i] < 0) {
                        BONGOCAT_LOG_VERBOSE("Failed to re-open %s: %s", device_path, strerror(errno));
                        continue;
                    }
                    // re-validate device path exists and is readable
                    if (stat(device_path, &st) != 0) {
                        BONGOCAT_LOG_VERBOSE("Input device does not exist: %s", device_path);
                        if (input->_fds[i] >= 0) close(input->_fds[i]);
                        input->_fds[i] = -1;
                    }
                    if (!S_ISCHR(st.st_mode)) {
                        BONGOCAT_LOG_VERBOSE("Input device is not a character device: %s", device_path);
                        if (input->_fds[i] >= 0) close(input->_fds[i]);
                        input->_fds[i] = -1;
                    }
                }
                valid_devices++;
            }
        }
        if (valid_devices == 0) {
            BONGOCAT_LOG_ERROR("All input devices became unavailable");
        }
    }
    atomic_store(&input->_capture_input_running, false);

    // Will run only on normal return
    pthread_cleanup_pop(1);  // 1 = call cleanup even if not canceled

    // done when callback cleanup_input_thread
    //cleanup_input_thread_context(arg);
    assert(input->_device_paths == NULL);
    assert(input->_fds == NULL);
    assert(input->_unique_paths_indices == NULL);

    BONGOCAT_LOG_INFO("Input monitoring stopped");

    return NULL;
}

bongocat_error_t input_start_monitoring(animation_trigger_context_t *trigger_ctx, input_context_t* ctx, char **device_paths, int num_devices, int enable_debug) {
    BONGOCAT_CHECK_NULL(ctx, BONGOCAT_ERROR_INVALID_PARAM);
    BONGOCAT_CHECK_NULL(device_paths, BONGOCAT_ERROR_INVALID_PARAM);
    
    if (num_devices <= 0) {
        BONGOCAT_LOG_ERROR("No input devices specified");
        return BONGOCAT_ERROR_INVALID_PARAM;
    }

    const timestamp_ms_t now = get_current_time_ms();
    ctx->_capture_input_running = false;
    ctx->_input_kpm_counter = 0;
    ctx->_latest_kpm_update_ms = now;
    set_default_input_thread_context(ctx);

    BONGOCAT_LOG_INFO("Initializing input monitoring system for %d devices", num_devices);
    
    // Initialize shared memory for key press flag
    ctx->shm = (input_shared_memory_t *)mmap(NULL, sizeof(input_shared_memory_t), PROT_READ | PROT_WRITE,
                                 MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if (ctx->shm == MAP_FAILED) {
        BONGOCAT_LOG_ERROR("Failed to create shared memory for input monitoring: %s", strerror(errno));
        return BONGOCAT_ERROR_MEMORY;
    }
    ctx->shm->any_key_pressed = 0;
    ctx->shm->kpm = 0;
    ctx->shm->input_counter = 0;
    ctx->shm->last_key_pressed_timestamp = 0;

    // Initialize shared memory for local config
    ctx->_local_copy_config = (config_t *)mmap(NULL, sizeof(config_t), PROT_READ | PROT_WRITE,
                                        MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if (ctx->_local_copy_config == MAP_FAILED) {
        if (ctx->shm && ctx->shm != MAP_FAILED) munmap(ctx->shm, sizeof(input_shared_memory_t));
        BONGOCAT_LOG_ERROR("Failed to create shared memory for input monitoring: %s", strerror(errno));
        return BONGOCAT_ERROR_MEMORY;
    }
    config_set_defaults(ctx->_local_copy_config);

    // assume the parameters are the same as in the config
    memcpy(ctx->_local_copy_config->keyboard_devices, device_paths, MAX_INPUT_DEVICES * sizeof(char *));
    ctx->_local_copy_config->num_keyboard_devices = num_devices;
    ctx->_local_copy_config->enable_debug = enable_debug;

    //if (trigger_ctx->_input != ctx->_input) {
    //    BONGOCAT_LOG_DEBUG("Input context in animation differs from animation trigger input context");
    //}
    trigger_ctx->_input = ctx;

    // start input monitoring
    const int result = pthread_create(&ctx->_input_thread, NULL, capture_input_thread, trigger_ctx);
    if (result != 0) {
        atomic_store(&ctx->_capture_input_running, false);
        BONGOCAT_LOG_ERROR("Failed to start input monitoring thread: %s", strerror(errno));
        if (ctx->shm && ctx->shm != MAP_FAILED) munmap(ctx->shm, sizeof(int));
        ctx->shm = NULL;
        ctx->_local_copy_config = NULL;
        cleanup_input_thread_context(ctx);
        return BONGOCAT_ERROR_THREAD;
    }
    
    BONGOCAT_LOG_INFO("Input monitoring started");
    return BONGOCAT_SUCCESS;
}

bongocat_error_t input_restart_monitoring(animation_trigger_context_t *trigger_ctx, input_context_t* ctx, char **device_paths, int num_devices, int enable_debug) {
    BONGOCAT_CHECK_NULL(trigger_ctx, BONGOCAT_ERROR_INVALID_PARAM);
    BONGOCAT_CHECK_NULL(ctx, BONGOCAT_ERROR_INVALID_PARAM);
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
        //pthread_cancel(ctx->_input_thread);
        if (stop_thread_graceful_or_cancel(&ctx->_input_thread, &ctx->_capture_input_running) != 0) {
            BONGOCAT_LOG_ERROR("Failed to join input thread: %s", strerror(errno));
        }
        BONGOCAT_LOG_DEBUG("Input monitoring thread terminated");
    }

    // already done when stop current input thread
    //cleanup_input_thread_context(ctx);
    assert(ctx->_device_paths == NULL);
    assert(ctx->_fds == NULL);
    assert(ctx->_unique_paths_indices == NULL);
    
    // Start new monitoring (reuse shared memory if it exists)
    const bool need_new_shm = ctx->shm == NULL || ctx->shm == MAP_FAILED;
    if (need_new_shm) {
        ctx->shm = (input_shared_memory_t *)mmap(NULL, sizeof(input_shared_memory_t), PROT_READ | PROT_WRITE,
                                     MAP_SHARED | MAP_ANONYMOUS, -1, 0);
        if (ctx->shm == MAP_FAILED) {
            BONGOCAT_LOG_ERROR("Failed to create shared memory for input monitoring: %s", strerror(errno));
            cleanup_input_thread_context(ctx);
            return BONGOCAT_ERROR_MEMORY;
        }
    }
    if (ctx->shm) {
        ctx->shm->any_key_pressed = 0;
        ctx->shm->kpm = 0;
        ctx->shm->input_counter = 0;
        ctx->shm->last_key_pressed_timestamp = 0;
    }


    const bool need_new_shm_local_copy_config = ctx->_local_copy_config == NULL || ctx->_local_copy_config == MAP_FAILED;
    if (need_new_shm_local_copy_config) {
        ctx->_local_copy_config = (config_t *)mmap(NULL, sizeof(config_t), PROT_READ | PROT_WRITE,
                                     MAP_SHARED | MAP_ANONYMOUS, -1, 0);
        if (ctx->_local_copy_config == MAP_FAILED) {
            BONGOCAT_LOG_ERROR("Failed to create shared memory for input monitoring: %s", strerror(errno));
            if (ctx->shm && ctx->shm != MAP_FAILED) munmap(ctx->shm, sizeof(input_shared_memory_t));
            cleanup_input_thread_context(ctx);
            return BONGOCAT_ERROR_MEMORY;
        }
    }
    if (ctx->_local_copy_config) {
        config_set_defaults(ctx->_local_copy_config);
    }

    // assume the parameters are the same as in the config
    memcpy(ctx->_local_copy_config->keyboard_devices, device_paths, MAX_INPUT_DEVICES * sizeof(char*));
    ctx->_local_copy_config->num_keyboard_devices = num_devices;
    ctx->_local_copy_config->enable_debug = enable_debug;

    //if (trigger_ctx->_input != ctx->_input) {
    //    BONGOCAT_LOG_DEBUG("Input context in animation differs from animation trigger input context");
    //}
    trigger_ctx->_input = ctx;

    // start input monitoring
    if (pthread_create(&ctx->_input_thread, NULL, capture_input_thread, trigger_ctx) != 0) {
        BONGOCAT_LOG_ERROR("Failed to fork input monitoring process: %s", strerror(errno));
        if (ctx->shm && ctx->shm != MAP_FAILED) munmap(ctx->shm, sizeof(input_shared_memory_t));
        if (ctx->_local_copy_config && ctx->_local_copy_config != MAP_FAILED) munmap(ctx->_local_copy_config, sizeof(config_t));
        ctx->shm = NULL;
        ctx->_local_copy_config = NULL;
        cleanup_input_thread_context(ctx);
        return BONGOCAT_ERROR_THREAD;
    }

    BONGOCAT_LOG_INFO("Input monitoring restarted");
    return BONGOCAT_SUCCESS;
}

void input_stop(input_context_t* ctx) {
    if (!ctx) return;

    atomic_store(&ctx->_capture_input_running, false);
    if (ctx->_input_thread) {
        BONGOCAT_LOG_DEBUG("Stopping input thread");
        //pthread_cancel(ctx->_input_thread);
        if (stop_thread_graceful_or_cancel(&ctx->_input_thread, &ctx->_capture_input_running) != 0) {
            BONGOCAT_LOG_ERROR("Failed to join input thread: %s", strerror(errno));
        }
        BONGOCAT_LOG_DEBUG("Input monitoring thread terminated");
    }
    ctx->_input_thread = 0;
}

void input_cleanup(input_context_t* ctx) {
    if (!ctx) return;

    BONGOCAT_LOG_INFO("Cleaning up input monitoring system");

    input_stop(ctx);

    // should be done in cancel thread
    //cleanup_input_thread_context(ctx);
    assert(ctx->_device_paths == NULL);
    assert(ctx->_fds == NULL);
    assert(ctx->_unique_paths_indices == NULL);
    
    // Cleanup shared memory
    if (ctx->shm && ctx->shm != MAP_FAILED) {
        munmap(ctx->shm, sizeof(input_shared_memory_t));
        ctx->shm = NULL;
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
    /// @TODO: deep copy from config for keyboard_devices
    memset(ctx->_local_copy_config->keyboard_devices, 0, MAX_INPUT_DEVICES * sizeof(char*));
    ctx->_local_copy_config->num_keyboard_devices = 0;
    ctx->_local_copy_config->output_name = NULL;
}
