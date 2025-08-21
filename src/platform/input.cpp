#include "platform/input.h"
#include "graphics/animation.h"
#include "utils/memory.h"
#include "platform/wayland.h"
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <pthread.h>
#include <linux/input.h>
#include <unistd.h>
#include <cassert>
#include <climits>
#include <fcntl.h>
#include <poll.h>

namespace bongocat::platform::input {
    static inline constexpr size_t INPUT_EVENT_BUF = 128;
    static inline constexpr size_t MAX_POLL_FDS = 256;

    static inline constexpr auto INPUT_POOL_TIMEOUT_MS = 10;

    static inline constexpr time_sec_t START_ADAPTIVE_CHECK_INTERVAL_SEC = 5;
    static inline constexpr time_sec_t MID_ADAPTIVE_CHECK_INTERVAL_SEC   = 15;
    static inline constexpr time_sec_t MAX_ADAPTIVE_CHECK_INTERVAL_SEC   = 30;

    static inline constexpr time_ms_t RESET_KPM_TIMEOUT_MS = 5 * 1000;

    static void cleanup_input_devices_paths(input_context_t& input, size_t device_paths_count) {
        for (size_t i = 0; i < device_paths_count; i++) {
            if (input._device_paths[i]) ::free(input._device_paths[i]);
            input._device_paths[i] = nullptr;
        }
        release_allocated_array(input._device_paths);
    }

    static void cleanup_input_thread_context(input_context_t& input) {
        cleanup_input_devices_paths(input, input._device_paths.count);
        release_allocated_array(input._device_paths);
        release_allocated_array(input._unique_paths_indices);
        input._unique_paths_indices_capacity = 0;
        release_allocated_array(input._unique_devices);
    }

    static void cleanup_input_thread(void* arg) {
        assert(arg);
        animation::animation_session_t& trigger_ctx = *static_cast<animation::animation_session_t *>(arg);
        assert(trigger_ctx._input);
        //animation_context_t& ctx = trigger_ctx.anim;
        input_context_t& input = *trigger_ctx._input;

        atomic_store(&input._capture_input_running, false);

        cleanup_input_thread_context(input);

        BONGOCAT_LOG_INFO("Input thread cleanup completed (via pthread_cancel)");
    }

    inline static bool is_device_valid(const char* path) {
        struct stat fd_st{};
        return stat(path, &fd_st) == 0 && (S_ISCHR(fd_st.st_mode) && !S_ISLNK(fd_st.st_mode));
    }
    inline static bool is_open_device_valid(int fd) {
        struct stat fd_st{};
        return fd >= 0 && fstat(fd, &fd_st) == 0 && (S_ISCHR(fd_st.st_mode) && !S_ISLNK(fd_st.st_mode));
    }

    static void* capture_input_thread(void* arg) {
        assert(arg);
        animation::animation_session_t& trigger_ctx = *static_cast<animation::animation_session_t *>(arg);
        assert(trigger_ctx._input);
        //animation_context_t& anim = trigger_ctx.anim;
        input_context_t& input = *trigger_ctx._input;

        // read-only config
        assert(input._local_copy_config != nullptr);
        const config::config_t& current_config = *input._local_copy_config;
        const bool enable_debug = current_config.enable_debug;

        // keep local copies of device_paths
        do {
            assert(current_config.num_keyboard_devices >= 0);
            int device_paths_count = current_config.num_keyboard_devices;
            const char *const *device_paths = current_config.keyboard_devices;        // pls don't modify single keyboard_devices (string)
            assert(device_paths_count >= 0);
            input._device_paths = make_allocated_array<char*>(static_cast<size_t>(device_paths_count));
            for (size_t i = 0; i < input._device_paths.count; i++) {
                input._device_paths[i] = strdup(device_paths[i]);
                if (!input._device_paths[i]) {
                    atomic_store(&input._capture_input_running, false);
                    cleanup_input_devices_paths(input, i);
                    cleanup_input_thread_context(input);
                    BONGOCAT_LOG_ERROR("Failed to allocate memory for device_paths");
                    return nullptr;
                }
            }
        } while(false);

        BONGOCAT_LOG_DEBUG("Starting input capture on %d devices", input._device_paths.count);

        // init unique devices
        input._unique_paths_indices_capacity = input._device_paths.count;
        input._unique_paths_indices = make_allocated_array_with_value<size_t>(input._unique_paths_indices_capacity, 0);
        if (!input._unique_paths_indices) {
            atomic_store(&input._capture_input_running, false);
            cleanup_input_thread_context(input);
            BONGOCAT_LOG_ERROR("Failed to allocate memory for file descriptors");
            return nullptr;
        }
        size_t num_unique_devices = 0;
        // First pass: deduplicate device paths
        for (size_t i = 0; i < input._device_paths.count; i++) {
            if (i >= input._unique_paths_indices.count) break;
            bool is_duplicate = false;
            for (size_t j = 0; j < input._device_paths.count; j++) {
                if (j >= input._unique_paths_indices.count) break;
                if (const char* device_path = input._device_paths[i]; strcmp(device_path, input._device_paths[input._unique_paths_indices[j]]) == 0) {
                    is_duplicate = true;
                    break;
                }
            }

            if (!is_duplicate && num_unique_devices < input._unique_paths_indices.count) {
                input._unique_paths_indices[num_unique_devices] = i;
                num_unique_devices++;
            }
        }
        assert(num_unique_devices <= input._device_paths.count);
        // shrink size, @NOTE: don't do this with mmap array
        input._unique_paths_indices.count = num_unique_devices;

        BONGOCAT_LOG_DEBUG("Deduplicated %d devices to %d unique devices", input._device_paths.count, num_unique_devices);

        size_t track_valid_devices = 0;
        // Open all unique devices
        if (input._unique_paths_indices.count > 0) {
            input._unique_devices = make_allocated_array<input_unique_file_t>(input._unique_paths_indices.count);
            if (!input._unique_devices) {
                atomic_store(&input._capture_input_running, false);
                cleanup_input_thread_context(input);
                BONGOCAT_LOG_ERROR("Failed to allocate memory for file descriptors");
                return nullptr;
            }
            size_t valid_devices = 0;
            for (size_t i = 0;i < input._unique_paths_indices.count; i++) {
                input._unique_devices[i] = {};
                if (i < input._unique_paths_indices.count) {
                    if (input._unique_paths_indices[i] < input._device_paths.count) {
                        const char* device_path = input._device_paths[input._unique_paths_indices[i]];

                        if (!is_device_valid(device_path)) {
                            // @TODO: better message why it's NOT valid
                            BONGOCAT_LOG_WARNING("Invalid input device: %s", device_path);
                            continue;
                        }

                        input._unique_devices[i].device_path = nullptr;
                        input._unique_devices[i].fd = FileDescriptor(open(device_path, O_RDONLY | O_NONBLOCK));
                        if (input._unique_devices[i].fd._fd < 0) {
                            BONGOCAT_LOG_WARNING("Failed to open %s: %s", device_path, strerror(errno));
                            continue;
                        }
                        input._unique_devices[i].device_path = device_path;
                        valid_devices++;

                        BONGOCAT_LOG_INFO("Input monitoring started on %s (fd=%d)", input._unique_devices[i].device_path, input._unique_devices[i].fd._fd);
                    }
                }
            }
            // Update num_devices to reflect unique devices for the rest of the function
            if (valid_devices == 0) {
                atomic_store(&input._capture_input_running, false);
                BONGOCAT_LOG_ERROR("No valid input devices found");
                cleanup_input_thread_context(input);
                return nullptr;
            }

            track_valid_devices = valid_devices;
            BONGOCAT_LOG_INFO("Successfully opened %d/%d input devices", valid_devices, input._device_paths.count);
        }

        // trigger initial render
        wayland::request_render(trigger_ctx);

        pthread_cleanup_push(cleanup_input_thread, arg);

        int check_counter = 0;  // check is done periodically
        time_sec_t adaptive_check_interval_sec = START_ADAPTIVE_CHECK_INTERVAL_SEC;
        pollfd pfds[MAX_POLL_FDS];
        input_event ev[INPUT_EVENT_BUF];

        atomic_store(&input._capture_input_running, true);
        while (atomic_load(&input._capture_input_running)) {
            pthread_testcancel();  // optional, but makes cancellation more responsive

            // only map valid fds into pfds
            nfds_t nfds = 0;
            for (size_t i = 0; i < input._unique_devices.count && i < MAX_POLL_FDS; i++) {
                if (input._unique_devices[i].fd._fd >= 0) {
                    pfds[nfds].fd = input._unique_devices[i].fd._fd;
                    pfds[nfds].events = POLLIN;
                    pfds[nfds].revents = 0;
                    nfds++;
                }
            }
            if (nfds == 0) {
                BONGOCAT_LOG_ERROR("All input devices became unavailable");
                break;
            } else if (nfds > MAX_POLL_FDS) {
                BONGOCAT_LOG_WARNING("Max input devices fds: %d/%d (%d)", nfds, MAX_POLL_FDS, input._unique_devices.count);
                nfds = MAX_POLL_FDS;
            }

            int timeout = INPUT_POOL_TIMEOUT_MS;
            if (current_config.input_fps > 0) {
                timeout = 1000 / current_config.input_fps;
            } else if (current_config.fps > 0) {
                timeout = 1000 / current_config.fps / 2;
            }
            const int poll_result = poll(pfds, nfds, timeout);
            if (poll_result < 0) {
                if (errno == EINTR) continue; // Interrupted by signal
                BONGOCAT_LOG_ERROR("Poll error: %s", strerror(errno));
                break;
            }

            if (poll_result == 0) {
                // Timeout — adaptive device checking
                check_counter++;
                if (check_counter >= (adaptive_check_interval_sec * (1000 / 100))) {
                    check_counter = 0;
                    bool found_new_device = false;
                    for (size_t i = 0; i < input._unique_devices.count; i++) {
                        const char* device_path = input._unique_devices[i].device_path;
                        bool need_reopen = false;
                        // If an fd is already open, check if it is still valid
                        if (input._unique_devices[i].fd._fd >= 0) {
                            if (!is_open_device_valid(input._unique_devices[i].fd._fd)) {
                                // fd no longer valid
                                need_reopen = true;
                            } else {
                                // check if device node changed
                                struct stat old_st{};
                                if (input._unique_devices[i].fd._fd >= 0 &&
                                    fstat(input._unique_devices[i].fd._fd, &old_st) == 0) {
                                    struct stat new_st{};
                                    if (stat(device_path, &new_st) == 0) {
                                        if (old_st.st_rdev != new_st.st_rdev) {
                                            need_reopen = true;
                                        }
                                    }
                                    }
                            }
                        } else {
                            // FD never opened
                            need_reopen = true;
                        }

                        if (need_reopen) {
                            // Close old FD if still open
                            if (input._unique_devices[i].fd._fd >= 0) {
                                close_fd(input._unique_devices[i].fd);
                            }

                            if (int new_fd = open(device_path, O_RDONLY | O_NONBLOCK | O_CLOEXEC); new_fd >= 0) {
                                if (is_open_device_valid(new_fd)) {
                                    input._unique_devices[i].fd = FileDescriptor(new_fd);
                                    new_fd = -1;
                                    found_new_device = true;
                                    BONGOCAT_LOG_INFO("New input device detected and opened: %s (fd=%d)", device_path, input._unique_devices[i].fd._fd);
                                } else {
                                    // Not a valid char device — close immediately
                                    close(new_fd);
                                    BONGOCAT_LOG_VERBOSE("File opened but not a char device: %s", device_path);
                                }
                            } else {
                                BONGOCAT_LOG_VERBOSE("Failed to open input device: %s (%s)", device_path, strerror(errno));
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
                    const ssize_t rd = read(pfds[p].fd, ev, sizeof(ev));
                    if (rd < 0) {
                        if (errno == EAGAIN) continue;
                        BONGOCAT_LOG_WARNING("Read error on fd=%d: %s", pfds[p].fd, strerror(errno));
                        close(pfds[p].fd);
                        // pfds[p].fd is only a reference, reset also the owner (unique_fd)
                        for (size_t i = 0; i < input._unique_devices.count; i++) {
                            if (input._unique_devices[i].fd._fd == pfds[p].fd) {
                                input._unique_devices[i].fd._fd = -1;
                                pfds[i].fd = -1;
                                break;
                            }
                        }
                        pfds[p].fd = -1;
                        continue;
                    }
                    assert(rd >= 0);
                    if (rd == 0 || static_cast<size_t>(rd) % sizeof(input_event) != 0) {
                        BONGOCAT_LOG_WARNING("EOF or partial read on fd=%d", pfds[p].fd);
                        close(pfds[p].fd);
                        // pfds[p].fd is only a reference, reset also the owner (unique_fd)
                        for (size_t i = 0; i < input._unique_devices.count; i++) {
                            if (input._unique_devices[i].fd._fd == pfds[p].fd) {
                                input._unique_devices[i].fd._fd = -1;
                                pfds[i].fd = -1;
                                break;
                            }
                        }
                        pfds[p].fd = -1;
                        continue;
                    }

                    assert(rd >= 0);
                    assert(sizeof(input_event) > 0);
                    const auto num_events =  static_cast<ssize_t>(static_cast<size_t>(rd) / sizeof(input_event));
                    bool key_pressed = false;
                    for (ssize_t j = 0; j < num_events; j++) {
                        if (ev[j].type == EV_KEY && ev[j].value == 1) {
                            key_pressed = true;
                            if (enable_debug) {
                                BONGOCAT_LOG_VERBOSE("Key event: fd=%d, code=%d, time=%lld.%06lld",
                                                     pfds[p].fd, ev[j].code,
                                                     ev[j].time.tv_sec, ev[j].time.tv_usec);
                            } else {
                                // break early, when no debug (no print needed for every key press)
                                break;
                            }
                        }
                    }

                    const timestamp_ms_t now = get_current_time_ms();
                    if (key_pressed) {
                        const time_ms_t duration_ms = now - input._latest_kpm_update_ms;
                        time_ms_t min_key_press_check_time_ms = timeout*2;
                        if (current_config.input_fps > 0) {
                            min_key_press_check_time_ms = 2000 / current_config.input_fps;
                        } else if (current_config.fps > 0) {
                            min_key_press_check_time_ms = 2000 / current_config.fps;
                        }
                        if (duration_ms >= min_key_press_check_time_ms) {
                            const int input_kpm_counter = atomic_load(&input._input_kpm_counter);
                            if (input_kpm_counter > 0) {
                                if (duration_ms > 0) {
                                    const double duration_min = static_cast<double>(duration_ms) / 60000.0;
                                    assert(duration_min > 0.0);
                                    input.shm->kpm = static_cast<int>(static_cast<double>(input_kpm_counter) / duration_min);
                                } else {
                                    input.shm->kpm = 0;
                                }
                                atomic_store(&input._input_kpm_counter, 0);
                                input._latest_kpm_update_ms = now;
                            }
                        }
                        input.shm->last_key_pressed_timestamp = now;
                        atomic_fetch_add(&input.shm->input_counter, 1);
                        atomic_fetch_add(&input._input_kpm_counter, 1);
                        trigger(trigger_ctx);
                    } else {
                        if (input.shm->kpm > 0 && now - input._latest_kpm_update_ms >= RESET_KPM_TIMEOUT_MS) {
                            input.shm->kpm = 0;
                            atomic_store(&input._input_kpm_counter, 0);
                            input._latest_kpm_update_ms = now;
                        }
                    }
                }

                if (pfds[p].revents & (POLLERR | POLLHUP | POLLNVAL)) {
                    close(pfds[p].fd);
                    // pfds[p].fd is only a reference, reset also the owner (unique_fd)
                    for (size_t i = 0; i < input._unique_devices.count; i++) {
                        if (input._unique_devices[i].fd._fd == pfds[p].fd) {
                            input._unique_devices[i].fd._fd = -1;
                            pfds[i].fd = -1;
                            break;
                        }
                    }
                    pfds[p].fd = -1;
                }
            }

            // Revalidate valid devices
            do {
                size_t valid_devices = 0;
                for (size_t i = 0; i < input._unique_devices.count; i++) {
                    const char* device_path = input._unique_devices[i].device_path;

                    bool is_valid = false;
                    // Check if existing fd is still valid
                    if (input._unique_devices[i].fd._fd >= 0) {
                        if (is_open_device_valid(input._unique_devices[i].fd._fd)) {
                            is_valid = true;
                        } else {
                            close_fd(input._unique_devices[i].fd);
                        }
                    }

                    if (!is_valid) {
                        // reopen device
                        if (int new_fd = open(device_path, O_RDONLY | O_NONBLOCK | O_CLOEXEC); new_fd >= 0) {
                            if (is_open_device_valid(input._unique_devices[i].fd._fd)) {
                                input._unique_devices[i].fd = FileDescriptor(new_fd);
                                new_fd = -1;
                                BONGOCAT_LOG_VERBOSE("Re-opened input device: %s (fd=%d)", device_path, input._unique_devices[i].fd._fd);
                                is_valid = true;
                            } else {
                                close(new_fd);
                                new_fd = -1;
                                BONGOCAT_LOG_VERBOSE("Opened but invalid device: %s", device_path);
                            }
                        } else {
                            BONGOCAT_LOG_VERBOSE("Failed to re-open %s: %s", device_path, strerror(errno));
                        }
                    }

                    if (is_valid) {
                        valid_devices++;
                    } else {
                        // reset to invalid
                        close_fd(input._unique_devices[i].fd);
                    }
                }

                track_valid_devices = valid_devices;
                if (valid_devices == 0) {
                    BONGOCAT_LOG_VERBOSE("All input devices became unavailable");
                }
            } while (false);
        }
        atomic_store(&input._capture_input_running, false);
        if (track_valid_devices == 0) {
            BONGOCAT_LOG_ERROR("All input devices are unavailable");
        }

        // Will run only on normal return
        pthread_cleanup_pop(1);  // 1 = call cleanup even if not canceled

        // done when callback cleanup_input_thread
        //cleanup_input_thread_context(arg);
        assert(!input._device_paths);
        assert(!input._unique_devices);
        assert(!input._unique_paths_indices);
        assert(input._unique_paths_indices_capacity == 0);

        BONGOCAT_LOG_INFO("Input monitoring stopped");

        return nullptr;
    }

    created_result_t<input_context_t> create(const config::config_t& config) {
        input_context_t ret;

        if (config.num_keyboard_devices <= 0) {
            BONGOCAT_LOG_ERROR("No input devices specified");
            return bongocat_error_t::BONGOCAT_ERROR_INVALID_PARAM;
        }

        const timestamp_ms_t now = get_current_time_ms();
        ret._capture_input_running = false;
        ret._input_kpm_counter = 0;
        ret._latest_kpm_update_ms = now;

        BONGOCAT_LOG_INFO("Initializing input monitoring system for %d devices", config.num_keyboard_devices);

        // Initialize shared memory for key press flag
        ret.shm = make_allocated_mmap<input_shared_memory_t>();
        if (!ret.shm.ptr) {
            BONGOCAT_LOG_ERROR("Failed to create shared memory for input monitoring: %s", strerror(errno));
            return bongocat_error_t::BONGOCAT_ERROR_MEMORY;
        }
        ret.shm->any_key_pressed = 0;
        ret.shm->kpm = 0;
        ret.shm->input_counter = 0;
        ret.shm->last_key_pressed_timestamp = 0;

        // Initialize shared memory for local config
        ret._local_copy_config = make_allocated_mmap<config::config_t>();
        if (!ret._local_copy_config.ptr) {
            BONGOCAT_LOG_ERROR("Failed to create shared memory for input monitoring: %s", strerror(errno));
            return bongocat_error_t::BONGOCAT_ERROR_MEMORY;
        }
        assert(ret._local_copy_config != nullptr);
        *ret._local_copy_config = config;

        BONGOCAT_LOG_INFO("Input monitoring started");
        return ret;
    }

    bongocat_error_t start_monitoring(input_context_t& input, animation::animation_session_t& trigger_ctx, const config::config_t& config) {
        if (config.num_keyboard_devices <= 0) {
            BONGOCAT_LOG_ERROR("No input devices specified");
            return bongocat_error_t::BONGOCAT_ERROR_INVALID_PARAM;
        }

        const timestamp_ms_t now = get_current_time_ms();
        input._latest_kpm_update_ms = now;

        BONGOCAT_LOG_INFO("Initializing input monitoring system for %d devices", config.num_keyboard_devices);

        // Initialize shared memory for key press flag
        input.shm = make_allocated_mmap<input_shared_memory_t>();
        if (!input.shm.ptr) {
            BONGOCAT_LOG_ERROR("Failed to create shared memory for input monitoring: %s", strerror(errno));
            return bongocat_error_t::BONGOCAT_ERROR_MEMORY;
        }
        input.shm->any_key_pressed = 0;
        input.shm->kpm = 0;
        input.shm->input_counter = 0;
        input.shm->last_key_pressed_timestamp = now;        // for idle check timestamp should be zero

        // Initialize shared memory for local config
        input._local_copy_config = make_allocated_mmap<config::config_t>();
        if (!input._local_copy_config.ptr) {
            BONGOCAT_LOG_ERROR("Failed to create shared memory for input monitoring: %s", strerror(errno));
            return bongocat_error_t::BONGOCAT_ERROR_MEMORY;
        }
        assert(input._local_copy_config != nullptr);
        *input._local_copy_config = config;

        // start input monitoring
        trigger_ctx._input = &input;
        const int result = pthread_create(&input._input_thread, nullptr, capture_input_thread, &trigger_ctx);
        if (result != 0) {
            BONGOCAT_LOG_ERROR("Failed to start input monitoring thread: %s", strerror(errno));
            return bongocat_error_t::BONGOCAT_ERROR_THREAD;
        }

        BONGOCAT_LOG_INFO("Input monitoring started");
        return bongocat_error_t::BONGOCAT_SUCCESS;
    }

    bongocat_error_t restart_monitoring(input_context_t& input, animation::animation_session_t& trigger_ctx, const config::config_t& config) {
        BONGOCAT_LOG_INFO("Restarting input monitoring system");
        // Stop current monitoring
        if (input._input_thread) {
            BONGOCAT_LOG_DEBUG("Input monitoring thread");
            atomic_store(&input._capture_input_running, false);
            //pthread_cancel(ctx->_input_thread);
            if (stop_thread_graceful_or_cancel(input._input_thread, input._capture_input_running) != 0) {
                BONGOCAT_LOG_ERROR("Failed to join input thread: %s", strerror(errno));
            }
            BONGOCAT_LOG_DEBUG("Input monitoring thread terminated");
        }

        // already done when stop current input thread
        //cleanup_input_thread_context(ctx);
        assert(!input._device_paths);
        assert(!input._unique_paths_indices);
        assert(!input._unique_devices);
        assert(input._unique_paths_indices_capacity == 0);

        input_context_t ret;

        // reset stats
        //ret._latest_kpm_update_ms = get_current_time_ms();

        // Start new monitoring (reuse shared memory if it exists)
        if (ret.shm == nullptr) {
            ret.shm = make_allocated_mmap<input_shared_memory_t>();
            if (ret.shm.ptr == MAP_FAILED) {
                BONGOCAT_LOG_ERROR("Failed to create shared memory for input monitoring: %s", strerror(errno));
                return bongocat_error_t::BONGOCAT_ERROR_MEMORY;
            }
        }


        if (ret._local_copy_config == nullptr) {
            ret._local_copy_config = make_unallocated_mmap_value<config::config_t>(config);
            if (ret._local_copy_config != nullptr) {
                BONGOCAT_LOG_ERROR("Failed to create shared memory for input monitoring: %s", strerror(errno));
                return bongocat_error_t::BONGOCAT_ERROR_MEMORY;
            }
        }
        assert(ret._local_copy_config != nullptr);

        //if (trigger_ctx._input != ctx._input) {
        //    BONGOCAT_LOG_DEBUG("Input context in animation differs from animation trigger input context");
        //}

        input = bongocat::move(ret);
        trigger_ctx._input = &input;
        // start input monitoring
        if (pthread_create(&input._input_thread, nullptr, capture_input_thread, &trigger_ctx) != 0) {
            BONGOCAT_LOG_ERROR("Failed to fork input monitoring process: %s", strerror(errno));
            cleanup_input_thread_context(input);
            return bongocat_error_t::BONGOCAT_ERROR_THREAD;
        }

        BONGOCAT_LOG_INFO("Input monitoring restarted");
        return bongocat_error_t::BONGOCAT_SUCCESS;
    }

    void stop(input_context_t& ctx) {
        atomic_store(&ctx._capture_input_running, false);
        if (ctx._input_thread) {
            BONGOCAT_LOG_DEBUG("Stopping input thread");
            //pthread_cancel(ctx->_input_thread);
            if (stop_thread_graceful_or_cancel(ctx._input_thread, ctx._capture_input_running) != 0) {
                BONGOCAT_LOG_ERROR("Failed to join input thread: %s", strerror(errno));
            }
            BONGOCAT_LOG_DEBUG("Input monitoring thread terminated");
        }
        ctx._input_thread = 0;
    }

    void update_config(input_context_t& ctx, const config::config_t& config) {
        assert(ctx._local_copy_config != nullptr);

        *ctx._local_copy_config = config;
        /// @NOTE: input thread required so the new config has affect
    }
}