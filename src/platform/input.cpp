#include "platform/input.h"

#include "graphics/animation.h"
#include "platform/wayland.h"
#include "utils/memory.h"

#include <cassert>
#include <cstdio>
#include <fcntl.h>
#include <libudev.h>
#include <linux/input.h>
#include <poll.h>
#include <pthread.h>
#include <sys/eventfd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

namespace bongocat::platform::input {
static inline constexpr size_t INPUT_EVENT_BUF = 128;
static inline constexpr size_t MAX_DEVICE_FDS = 256;
inline static constexpr int MAX_ATTEMPTS = 2048;

static inline constexpr auto INPUT_POOL_TIMEOUT_MS = 10;

static inline constexpr time_sec_t START_ADAPTIVE_CHECK_INTERVAL_SEC = 5;
static inline constexpr time_sec_t MID_ADAPTIVE_CHECK_INTERVAL_SEC = 15;
static inline constexpr time_sec_t MAX_ADAPTIVE_CHECK_INTERVAL_SEC = 30;

static inline constexpr time_ms_t RESET_KPM_TIMEOUT_MS = 5 * 1000;

inline static constexpr time_ms_t COND_ANIMATION_TRIGGER_INIT_TIMEOUT_MS = 5000;
inline static constexpr time_ms_t COND_RELOAD_CONFIGS_TIMEOUT_MS = 5000;

inline static constexpr size_t TEST_STDIN_BUF_LEN = 256;

// Uses Linux input keycodes from <linux/input-event-codes.h>
// Left-hand keys on QWERTY keyboard
// clang-format off
    inline static constexpr int INPUT_LEFT_KEYS[] = {
      // Number row left half (1-6)
      2, 3, 4, 5, 6, 7,           // KEY_1 to KEY_6
      // QWERTY row left half
      16, 17, 18, 19, 20,         // KEY_Q, KEY_W, KEY_E, KEY_R, KEY_T
      // Home row left half
      30, 31, 32, 33, 34,         // KEY_A, KEY_S, KEY_D, KEY_F, KEY_G
      // Bottom row left half
      44, 45, 46, 47, 48,         // KEY_Z, KEY_X, KEY_C, KEY_V, KEY_B
      // Modifiers and special keys (left side)
      1,                          // KEY_ESC
      15,                         // KEY_TAB
      58,                         // KEY_CAPSLOCK
      42,                         // KEY_LEFTSHIFT
      29,                         // KEY_LEFTCTRL
      56,                         // KEY_LEFTALT
      41,                         // KEY_GRAVE (backtick)
      125,                        // KEY_LEFTMETA (super)
    };
// clang-format on

static input_hand_mapping_t get_hand_mapping_form_keycode([[maybe_unused]] const input_context_t& input, int keycode) {
  // read-only config
  assert(input._local_copy_config);
  // const config::config_t& current_config = *input._local_copy_config;

  for (size_t i = 0; i < LEN_ARRAY(INPUT_LEFT_KEYS); i++) {
    if (keycode == INPUT_LEFT_KEYS[i]) {
      return input_hand_mapping_t::Left;  // Left hand
    }
  }
  return input_hand_mapping_t::Right;  // Right hand (default for all other keys)
}

static void cleanup_input_devices_paths(input_context_t& input, size_t device_paths_count) {
  for (size_t i = 0; i < device_paths_count; i++) {
    if (input._device_paths[i] != BONGOCAT_NULLPTR) {
      ::free(input._device_paths[i]);
      input._device_paths[i] = BONGOCAT_NULLPTR;
    }
  }
  release_allocated_array(input._device_paths);
}

static void cleanup_input_thread_context(input_context_t& input) {
  cleanup_input_devices_paths(input, input._device_paths.count);
  release_allocated_array(input._device_paths);
  release_allocated_array(input._unique_paths_indices);
  input._unique_paths_indices_capacity = 0;
  release_allocated_array(input._unique_devices);
  if (input._udev_mon != BONGOCAT_NULLPTR) {
    udev_monitor_unref(input._udev_mon);
    input._udev_mon = BONGOCAT_NULLPTR;
  }
  if (input._udev != BONGOCAT_NULLPTR) {
    udev_unref(input._udev);
    input._udev = BONGOCAT_NULLPTR;
  }
  input._udev_fd = -1;
}

static void cleanup_input_thread(void *arg) {
  assert(arg);
  const animation::animation_context_t& animation_context = *static_cast<animation::animation_context_t *>(arg);
  assert(animation_context._input);
  input_context_t& input = *animation_context._input;

  atomic_store(&input._capture_input_running, false);

  input.config_updated.notify_all();

  cleanup_input_thread_context(*animation_context._input);

  BONGOCAT_LOG_INFO("Input thread cleanup completed (via pthread_cancel)");
}

inline static bool is_device_valid(const char *path) {
  struct stat fd_st{};
  return stat(path, &fd_st) == 0 && (S_ISCHR(fd_st.st_mode) && !S_ISLNK(fd_st.st_mode));
}
inline static bool is_open_device_valid(int fd) {
  struct stat fd_st{};
  return fd >= 0 && fstat(fd, &fd_st) == 0 && (S_ISCHR(fd_st.st_mode) && !S_ISLNK(fd_st.st_mode));
}
inline static void trigger_key_press(animation::animation_context_t& animation_ctx, int keycode = 0) {
  assert(animation_ctx._input);
  // animation_context_t& anim = trigger_ctx.anim;
  input_context_t& input = *animation_ctx._input;

  // read-only config
  assert(input._local_copy_config);
  const config::config_t& current_config = *input._local_copy_config;

  int timeout = INPUT_POOL_TIMEOUT_MS;
  if (current_config.input_fps > 0) {
    timeout = 1000 / current_config.input_fps;
  } else if (current_config.fps > 0) {
    timeout = 1000 / current_config.fps / 3;
  }

  const timestamp_ms_t now = get_current_time_ms();
  const time_ms_t duration_ms = now - input._latest_kpm_update_ms;
  time_ms_t min_key_press_check_time_ms = timeout * 2L;
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
  input.shm->any_key_pressed = keycode != 0 ? 1 : 0;
  input.shm->last_key_pressed_timestamp = now;
  atomic_fetch_add(&input.shm->input_counter, 1);
  atomic_fetch_add(&input._input_kpm_counter, 1);
  if (current_config.enable_hand_mapping >= 1 && keycode != 0) {
    input.shm->hand_mapping = get_hand_mapping_form_keycode(input, keycode);
  } else {
    input.shm->hand_mapping = input_hand_mapping_t::None;
  }
  animation::trigger(animation_ctx, animation::trigger_animation_cause_mask_t::KeyPress);
}

// for testing
static FileDescriptor open_tty_nonblocking() {
  int fd = dup(STDIN_FILENO);
  if (fd < 0) {
    BONGOCAT_LOG_ERROR("dup stdin");
    return FileDescriptor(fd);
  }
  const int flags = fcntl(fd, F_GETFL, 0);
  if (flags < 0) {
    BONGOCAT_LOG_ERROR("fcntl getfl");
    close(fd);
    fd = -1;
    return FileDescriptor(fd);
  }
  if (fcntl(fd, F_SETFL, flags | O_NONBLOCK) < 0) {
    BONGOCAT_LOG_ERROR("fcntl setfl");
    close(fd);
    fd = -1;
    return FileDescriptor(fd);
  }
  return FileDescriptor(fd);
}

struct sync_devices_options_t {
  bool reload_devices_needed{false};
};
struct sync_devices_options_result_t {
  size_t valid_devices{0};
  size_t broken_symlink{0};
  size_t failed{0};
  size_t ignore{0};
};
BONGOCAT_NODISCARD static created_result_t<sync_devices_options_result_t>
sync_devices(input_context_t& input, sync_devices_options_t options = {}) {
  assert(input.shm);

  size_t valid_devices = 0;
  // Ensure buffer size
  if (input._unique_paths_indices_capacity < input._device_paths.count || options.reload_devices_needed) {
    auto new_unique_devices = make_allocated_array<input_unique_file_t>(input._device_paths.count);
    if (!new_unique_devices) {
      BONGOCAT_LOG_ERROR("Failed to allocate memory for unique devices");
      return bongocat_error_t::BONGOCAT_ERROR_MEMORY;
    }
    auto new_unique_paths_indices = make_allocated_array<size_t>(input._device_paths.count);
    if (!new_unique_paths_indices) {
      release_allocated_array(input._unique_devices);
      BONGOCAT_LOG_ERROR("Failed to allocate memory for unique path indices");
      return bongocat_error_t::BONGOCAT_ERROR_MEMORY;
    }
    input._unique_devices = bongocat::move(new_unique_devices);
    input._unique_paths_indices = bongocat::move(new_unique_paths_indices);
    input._unique_paths_indices_capacity = input._device_paths.count;
  }

  size_t broken_symlink = 0;
  size_t failed = 0;
  size_t ignore = 0;

  // recover real size for syncing
  input._unique_devices.count = input._unique_paths_indices_capacity;
  input._unique_paths_indices.count = input._unique_paths_indices_capacity;
  size_t num_unique_devices = 0;
  for (size_t i = 0; i < input._device_paths.count; i++) {
    const char *device_path = input._device_paths[i];

    // Resolve to canonical path
    char resolved[PATH_MAX];
    const char *candidate = BONGOCAT_NULLPTR;
    input_unique_file_type_t new_type = input_unique_file_type_t::File;

    struct stat lst{};
    if (lstat(device_path, &lst) == 0 && S_ISLNK(lst.st_mode)) {
      new_type = input_unique_file_type_t::Symlink;
      if (realpath(device_path, resolved) != BONGOCAT_NULLPTR) {
        candidate = resolved;
      } else {
        BONGOCAT_LOG_WARNING("Broken symlink: %s", device_path);
        broken_symlink++;
        continue;
      }
    } else {
      candidate = device_path;
    }

    // Skip if non-existent
    if (access(candidate, F_OK) != 0) {
      failed++;
      BONGOCAT_LOG_WARNING("Device missing: %s", candidate);
      continue;
    }

    // Check if we already added this canonical path
    bool duplicate = false;
    for (size_t j = 0; j < num_unique_devices; j++) {
      const input_unique_file_t& prev = input._unique_devices[j];
      if (prev.canonical_path != BONGOCAT_NULLPTR && strcmp(prev.canonical_path, candidate) == 0) {
        duplicate = true;
        break;
      }
    }
    if (duplicate) {
      continue;
    }

    input_unique_file_t& cur = input._unique_devices[num_unique_devices];
    input._unique_paths_indices[num_unique_devices] = i;

    // Decide if we need to replace real_device_path
    bool need_reopen = false;
    bool need_replace = false;
    if (cur.canonical_path != BONGOCAT_NULLPTR) {
      need_replace = strcmp(cur.canonical_path, candidate) != 0;
    }
    if (static_cast<bool>(cur.canonical_path) != static_cast<bool>(candidate)) {
      need_reopen = cur.canonical_path == BONGOCAT_NULLPTR && candidate != BONGOCAT_NULLPTR;
      need_replace = true;
    }
    if (!need_reopen && cur.type != new_type) {
      need_reopen = true;
    }

    // Check existing FD
    if (!need_reopen && cur.fd._fd >= 0 && is_open_device_valid(cur.fd._fd)) {
      valid_devices++;
      num_unique_devices++;
      continue;
    }

    // Reopen
    if (need_reopen || need_replace) {
      close_fd(cur.fd);
      struct stat st{};
      if (stat(candidate, &st) == 0 && S_ISCHR(st.st_mode)) {
        if (need_reopen) {
          int fd = open(candidate, O_RDONLY | O_NONBLOCK | O_CLOEXEC);
          if (fd >= 0 && is_open_device_valid(fd)) {
            cur.fd = FileDescriptor(fd);
            BONGOCAT_LOG_INFO("Opened input device: %s (fd=%d)", candidate, cur.fd._fd);
          }
        }
        if (cur.fd._fd >= 0 && is_open_device_valid(cur.fd._fd)) {
          // Replace canonical path if changed
          if (need_replace) {
            if (cur.canonical_path != BONGOCAT_NULLPTR) {
              ::free(cur.canonical_path);
              cur.canonical_path = BONGOCAT_NULLPTR;
            }
            cur.canonical_path = ::strdup(candidate);
          }
          cur.type = new_type;
          cur._device_path = device_path;
          valid_devices++;
        } else {
          cleanup(cur);
          failed++;
          BONGOCAT_LOG_WARNING("Failed to open %s", candidate);
        }
      } else {
        cleanup(cur);
        ignore++;
        BONGOCAT_LOG_WARNING("Ignoring non-char device: %s", candidate);
      }
    }

    num_unique_devices++;
  }

  assert(num_unique_devices <= input._device_paths.count);
  // shrink size, @NOTE: don't do this with mmap array
  input._unique_devices.count = num_unique_devices;
  input._unique_paths_indices.count = num_unique_devices;
  return sync_devices_options_result_t{
      .valid_devices = valid_devices,
      .broken_symlink = broken_symlink,
      .failed = failed,
      .ignore = ignore,
  };
}

static bongocat_error_t setup_udev_monitor(input_context_t& input) {
  if (input._udev_mon != BONGOCAT_NULLPTR) {
    udev_monitor_unref(input._udev_mon);
    input._udev_mon = BONGOCAT_NULLPTR;
  }
  if (input._udev != BONGOCAT_NULLPTR) {
    udev_unref(input._udev);
    input._udev = BONGOCAT_NULLPTR;
  }
  input._udev_fd = -1;

  input._udev = udev_new();
  if (input._udev == BONGOCAT_NULLPTR) {
    BONGOCAT_LOG_ERROR("Failed to init udev\n");
    return bongocat_error_t::BONGOCAT_ERROR_MEMORY;
  }

  input._udev_mon = udev_monitor_new_from_netlink(input._udev, "udev");
  if (input._udev_mon == BONGOCAT_NULLPTR) {
    BONGOCAT_LOG_ERROR("Failed to create udev monitor\n");
    udev_unref(input._udev);
    input._udev = BONGOCAT_NULLPTR;
    return bongocat_error_t::BONGOCAT_ERROR_MEMORY;
  }

  // only care about input subsystem
  udev_monitor_filter_add_match_subsystem_devtype(input._udev_mon, "input", BONGOCAT_NULLPTR);
  udev_monitor_enable_receiving(input._udev_mon);

  input._udev_fd = udev_monitor_get_fd(input._udev_mon);
  return bongocat_error_t::BONGOCAT_SUCCESS;
}

static void *input_thread(void *arg) {
  assert(arg);
  animation::animation_context_t& animation_ctx = *static_cast<animation::animation_context_t *>(arg);

  // from thread context
  // animation_context_t& anim = trigger_ctx.anim;
  // wait for input context (in animation start)
  animation_ctx.init_cond.timedwait([&]() { return atomic_load(&animation_ctx.ready); },
                                    COND_ANIMATION_TRIGGER_INIT_TIMEOUT_MS);
  assert(animation_ctx._input != BONGOCAT_NULLPTR);
  input_context_t& input = *animation_ctx._input;

  // sanity checks
  assert(input._config != BONGOCAT_NULLPTR);
  assert(input._configs_reloaded_cond != BONGOCAT_NULLPTR);
  assert(!input._capture_input_running);
  assert(input.shm);
  assert(input._local_copy_config);
  assert(input.update_config_efd._fd >= 0);

  // keep local copies of device_paths
  {
    // read-only config
    assert(input._local_copy_config);
    const config::config_t& current_config = *input._local_copy_config;

    assert(current_config.num_keyboard_devices >= 0);
    const int device_paths_count = current_config.num_keyboard_devices;
    const char *const *device_paths = current_config.keyboard_devices;
    assert(device_paths_count >= 0);
    input._device_paths = make_allocated_array<char *>(static_cast<size_t>(device_paths_count));
    for (size_t i = 0; i < input._device_paths.count; i++) {
      input._device_paths[i] = strdup(device_paths[i]);
      if (input._device_paths[i] == BONGOCAT_NULLPTR) {
        atomic_store(&input._capture_input_running, false);
        cleanup_input_devices_paths(input, i);
        cleanup_input_thread_context(input);
        BONGOCAT_LOG_ERROR("input: Failed to allocate memory for device_paths");
        return BONGOCAT_NULLPTR;
      }
    }
  }

  BONGOCAT_LOG_DEBUG("input: Starting input capture on %d devices", input._device_paths.count);

  // init unique devices
  size_t track_valid_devices = 0;
  {
    [[maybe_unused]] const auto t0 = platform::get_current_time_us();
    auto [sync_devices_result, init_devices_result] = sync_devices(input);
    if (init_devices_result != bongocat_error_t::BONGOCAT_SUCCESS) [[unlikely]] {
      atomic_store(&input._capture_input_running, false);
      cleanup_input_thread_context(input);
      BONGOCAT_LOG_ERROR("input: Failed to init devices and file descriptors");
      return BONGOCAT_NULLPTR;
    }
    [[maybe_unused]] const auto t1 = platform::get_current_time_us();

    BONGOCAT_LOG_INFO("input: Successfully opened %d/%d input devices; init time %.3fms (%.6fsec)",
                      sync_devices_result.valid_devices, input._device_paths.count,
                      static_cast<double>(t1 - t0) / 1000.0, static_cast<double>(t1 - t0) / 1000000.0);
    track_valid_devices = sync_devices_result.valid_devices;
  }

  // udev monitoring
  {
    const bongocat_error_t udev_result = setup_udev_monitor(input);
    if (udev_result != bongocat_error_t::BONGOCAT_SUCCESS) [[unlikely]] {
      BONGOCAT_LOG_WARNING("Can't create udev monitoring");
    } else {
      BONGOCAT_LOG_INFO("Start udev monitoring");
    }
  }

  // trigger initial render
  wayland::request_render(animation_ctx);

  pthread_cleanup_push(cleanup_input_thread, arg);

  // local thread context
  int check_counter = 0;  // check is done periodically
  time_sec_t adaptive_check_interval_sec = START_ADAPTIVE_CHECK_INTERVAL_SEC;
  /// event poll
  // 0:       reload config event
  // 1:       udev monitor fd
  // 2 - n:   device events
  // last:    stdin (optional)
  constexpr size_t MAX_PFDS = 2 + MAX_DEVICE_FDS + ((features::Debug) ? 1 : 0);
  pollfd pfds[MAX_PFDS];
  input_event ev[INPUT_EVENT_BUF];

  constexpr bool include_stdin = features::Debug;
  FileDescriptor tty_fd;
  if constexpr (include_stdin) {
    tty_fd = open_tty_nonblocking();
    BONGOCAT_LOG_INFO("input: Open stdin for testing (fd=%d)", tty_fd._fd);
  }

  atomic_store(&input._capture_input_running, true);
  while (atomic_load(&input._capture_input_running)) {
    pthread_testcancel();  // optional, but makes cancellation more responsive

    // read from config
    int timeout = INPUT_POOL_TIMEOUT_MS;
    bool enable_debug = false;
    {
      // read-only config
      assert(input._local_copy_config);
      const config::config_t& current_config = *input._local_copy_config;

      enable_debug = current_config.enable_debug >= 1;

      if (current_config.input_fps > 0) {
        timeout = 1000 / current_config.input_fps;
      } else if (current_config.fps > 0) {
        timeout = 1000 / current_config.fps / 3;
      }
    }

    // only map valid fds into pfds
    constexpr size_t fds_update_config_index = 0;
    constexpr size_t fds_udev_monitor_index = 1;
    constexpr size_t fds_device_potential_start_index = 2;
    pfds[fds_update_config_index] = {.fd = input.update_config_efd._fd, .events = POLLIN, .revents = 0};
    pfds[fds_udev_monitor_index] = {.fd = input._udev_fd, .events = POLLIN, .revents = 0};

    assert(fds_device_potential_start_index < SSIZE_MAX);
    const ssize_t fds_device_start_index =
        input._unique_devices.count > 0 ? static_cast<ssize_t>(fds_device_potential_start_index) : -1;
    ssize_t fds_device_end_index = input._unique_devices.count > 0 ? fds_device_start_index : -1;
    nfds_t nfds = fds_device_potential_start_index;
    nfds_t device_nfds = 0;
    for (size_t i = 0; i < input._unique_devices.count && i < MAX_DEVICE_FDS; i++) {
      if (input._unique_devices[i].fd._fd >= 0) {
        pfds[nfds].fd = input._unique_devices[i].fd._fd;
        pfds[nfds].events = POLLIN;
        pfds[nfds].revents = 0;
        nfds++;
        device_nfds++;
      }
    }
    assert(device_nfds <= input._unique_devices.count);
    assert(input._unique_devices.count <= SSIZE_MAX);
    fds_device_end_index = (fds_device_start_index >= 0 && device_nfds > 0)
                               ? fds_device_start_index + static_cast<ssize_t>(device_nfds)
                               : fds_device_start_index;

    ssize_t fds_stdin_index = -1;
    if constexpr (include_stdin) {
      if (fds_device_end_index >= 0) {
        fds_stdin_index = fds_device_end_index + 1;
      } else {
        fds_stdin_index = 1;
      }
    }
    if (device_nfds == 0 && !include_stdin) {
      BONGOCAT_LOG_ERROR("input: All input devices became unavailable");
      break;
    } else if (device_nfds > MAX_DEVICE_FDS) {
      device_nfds = MAX_DEVICE_FDS;
      fds_stdin_index = -1;
    }
    if (nfds > MAX_PFDS) {
      nfds = MAX_PFDS - ((include_stdin) ? 2 : 1);
    }
    if (fds_stdin_index >= 0) {
      pfds[fds_stdin_index] = {.fd = tty_fd._fd, .events = POLLIN, .revents = 0};
      nfds++;
    }
    {
      // read-only config
      assert(input._local_copy_config);
      const config::config_t& current_config = *input._local_copy_config;
      if (device_nfds > MAX_DEVICE_FDS) {
        if (current_config._strict) {
          BONGOCAT_LOG_ERROR("input: Max input devices fds: %d/%d (%d)", device_nfds, MAX_DEVICE_FDS,
                             input._unique_devices.count);
          break;
        } else {
          BONGOCAT_LOG_WARNING("input: Max input devices fds: %d/%d (%d)", device_nfds, MAX_DEVICE_FDS,
                               input._unique_devices.count);
        }
      }
    }

    /// @TODO: move to tests
    // check indices
    if constexpr (features::Debug) {
      // const bool has_update_config = fds_update_config_index >= 0;
      // const bool has_udev = fds_udev_monitor_index >= 0;
      const bool has_std_in = fds_stdin_index >= 0;
      const bool has_devices = input._unique_devices.count > 0;

      // include every fd
      if (has_devices && has_std_in) {
        assert(fds_update_config_index == 0);
        assert(fds_udev_monitor_index == 1);
        assert(fds_device_start_index >= 0);
        assert(fds_device_end_index >= 0);
        assert(fds_stdin_index >= 0);

        assert(fds_update_config_index == 0);
        assert(static_cast<size_t>(fds_device_start_index) > fds_update_config_index);
        assert(static_cast<size_t>(fds_device_end_index) > fds_update_config_index);
        assert(fds_device_end_index >= fds_device_start_index);
        assert(fds_stdin_index > fds_device_end_index);

        // assert(device_nfds >= 0);
        // assert(nfds >= 0);
        assert(device_nfds <= SSIZE_MAX);
        assert(nfds <= SSIZE_MAX);
        assert(static_cast<ssize_t>(device_nfds) == fds_device_end_index - fds_device_start_index);
        assert(static_cast<ssize_t>(nfds) == fds_device_end_index - fds_device_start_index + 3);
      }
      // only update + devices
      if (has_devices && !has_std_in) {
        assert(fds_update_config_index == 0);
        assert(fds_udev_monitor_index == 1);
        assert(fds_device_start_index >= 0);
        assert(fds_device_end_index >= 0);
        assert(fds_stdin_index == -1);

        assert(fds_update_config_index == 0);
        assert(fds_device_end_index >= 0);
        assert(static_cast<size_t>(fds_device_end_index) > fds_update_config_index);
        assert(fds_device_end_index >= fds_device_start_index);

        // assert(device_nfds >= 0);
        // assert(nfds >= 0);
        assert(device_nfds <= SSIZE_MAX);
        assert(nfds <= SSIZE_MAX);
        assert(static_cast<ssize_t>(device_nfds) == fds_device_end_index - fds_device_start_index);
        assert(static_cast<ssize_t>(nfds) == fds_device_end_index - fds_device_start_index + 3);
      }
      // only devices
      if (has_devices && !has_std_in) {
        assert(fds_update_config_index == 0);
        assert(fds_udev_monitor_index == 1);
        assert(fds_device_start_index >= 0);
        assert(fds_device_end_index >= 0);
        assert(fds_stdin_index == -1);

        assert(fds_device_end_index >= 0 && static_cast<size_t>(fds_device_end_index) <= SIZE_MAX);
        assert(static_cast<size_t>(fds_device_end_index) > fds_update_config_index);
        assert(fds_device_end_index >= fds_device_start_index);

        // assert(device_nfds >= 0);
        // assert(nfds >= 0);
        assert(device_nfds <= SSIZE_MAX);
        assert(nfds <= SSIZE_MAX);
        assert(static_cast<ssize_t>(device_nfds) == fds_device_end_index - fds_device_start_index);
        assert(static_cast<ssize_t>(nfds) == fds_device_end_index - fds_device_start_index);
      }
      // nothing (empty)
      if (!has_devices && !has_std_in) {
        assert(fds_update_config_index == 0);
        assert(fds_udev_monitor_index == 1);
        assert(fds_device_start_index == -1);
        assert(fds_device_end_index == -1);
        assert(fds_stdin_index == -1);

        assert(fds_device_end_index >= 0 && static_cast<size_t>(fds_device_end_index) <= SIZE_MAX);
        assert(static_cast<size_t>(fds_device_end_index) > fds_update_config_index);
        assert(fds_device_end_index >= fds_device_start_index);

        assert(device_nfds == 0);
        assert(nfds == 2);
      }
      // no devices, only config
      if (!has_devices && !has_std_in) {
        assert(fds_update_config_index == 0);
        assert(fds_udev_monitor_index == 1);
        assert(fds_udev_monitor_index == 1);
        assert(fds_device_start_index == -1);
        assert(fds_device_end_index == -1);
        assert(fds_stdin_index == -1);

        assert(device_nfds == 0);
        assert(nfds == 2);
      }
      // no devices, only config + stdin
      if (!has_devices && has_std_in) {
        assert(fds_update_config_index == 0);
        assert(fds_udev_monitor_index == 1);
        assert(fds_device_start_index == -1);
        assert(fds_device_end_index == -1);
        assert(fds_stdin_index == 1);

        assert(device_nfds == 0);
        assert(nfds == 3);
      }
    }

    // poll events
    const int poll_result = poll(pfds, nfds, timeout);
    if (poll_result < 0) {
      if (errno == EINTR) {
        continue;  // Interrupted by signal
      }
      BONGOCAT_LOG_ERROR("input: Poll error: %s", strerror(errno));
      break;
    }
    if (poll_result == 0) {
      // Timeout — adaptive device checking
      check_counter++;
      if (check_counter >= (adaptive_check_interval_sec * (1000 / 100))) {
        check_counter = 0;
        bool found_new_device = false;
        for (size_t i = 0; i < input._unique_devices.count; i++) {
          const char *device_path = input._unique_devices[i].canonical_path;
          bool need_reopen = false;
          if (device_path == BONGOCAT_NULLPTR) {
            continue;
          }
          // If an fd is already open, check if it is still valid
          if (input._unique_devices[i].fd._fd >= 0) {
            if (!is_open_device_valid(input._unique_devices[i].fd._fd)) {
              // fd no longer valid
              need_reopen = true;
            } else {
              // check if device node changed
              struct stat old_st{};
              if (input._unique_devices[i].fd._fd >= 0 && fstat(input._unique_devices[i].fd._fd, &old_st) == 0) {
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
                BONGOCAT_LOG_INFO("input: New input device detected and opened: %s (fd=%d)", device_path,
                                  input._unique_devices[i].fd._fd);
              } else {
                // Not a valid char device — close immediately
                close(new_fd);
                BONGOCAT_LOG_VERBOSE("input: vFile opened but not a char device: %s", device_path);
              }
            } else {
              BONGOCAT_LOG_VERBOSE("input: Failed to open input device: %s (%s)", device_path, strerror(errno));
            }
          }
        }

        if (!found_new_device && adaptive_check_interval_sec < MAX_ADAPTIVE_CHECK_INTERVAL_SEC) {
          adaptive_check_interval_sec = (adaptive_check_interval_sec < MID_ADAPTIVE_CHECK_INTERVAL_SEC)
                                            ? MID_ADAPTIVE_CHECK_INTERVAL_SEC
                                            : MAX_ADAPTIVE_CHECK_INTERVAL_SEC;
          BONGOCAT_LOG_DEBUG("input: Increased device check interval to %d seconds", adaptive_check_interval_sec);
        } else if (found_new_device && adaptive_check_interval_sec > START_ADAPTIVE_CHECK_INTERVAL_SEC) {
          adaptive_check_interval_sec = START_ADAPTIVE_CHECK_INTERVAL_SEC;
          BONGOCAT_LOG_DEBUG("input: Reset device check interval to %d seconds", START_ADAPTIVE_CHECK_INTERVAL_SEC);
        }
      }
      continue;
    }

    // cancel pooling (when not running anymore)
    if (!atomic_load(&input._capture_input_running)) {
      // draining pools
      if (pfds[fds_update_config_index].revents & POLLIN) {
        drain_event(pfds[fds_update_config_index], MAX_ATTEMPTS);
      }
      if (pfds[fds_udev_monitor_index].revents & POLLIN) {
        drain_event(pfds[fds_udev_monitor_index], MAX_ATTEMPTS);
      }
      if (fds_device_start_index >= 0) {
        assert(fds_device_start_index >= 0);
        assert(fds_device_end_index >= 0);
        for (nfds_t p = static_cast<nfds_t>(fds_device_start_index); p <= static_cast<nfds_t>(fds_device_end_index);
             p++) {
          // Handle ready devices
          if (pfds[p].revents & POLLIN) {
            // discard evdev input
            [[maybe_unused]] auto discard_result = read(pfds[p].fd, ev, sizeof(ev));
            ((void)discard_result);
          }
        }
      }
      if (fds_stdin_index >= 0) {
        if (pfds[fds_stdin_index].revents & POLLIN) {
          char buf[TEST_STDIN_BUF_LEN] = {0};
          // Drain stdin until empty (EAGAIN)
          int attempts = 0;
          ssize_t rd = 0;
          while (attempts < MAX_ATTEMPTS) {
            rd = read(pfds[fds_stdin_index].fd, buf, TEST_STDIN_BUF_LEN);
            if (rd > 0) {
              continue;
            }
#if EAGAIN != EWOULDBLOCK
            if (rd == -1 && (errno == EAGAIN || errno == EWOULDBLOCK)) {
#else
            if (rd == -1 && errno == EAGAIN) {
#endif
              break;  // drained completely
            } else {
              break;  // EOF or error
            }
          }
        }
      }
      break;
    }

    // handle hotplug
    bool sync_devices_needed = false;
    bool reload_devices_needed = false;
    if (pfds[fds_udev_monitor_index].revents & POLLIN) {
      BONGOCAT_LOG_DEBUG("input: Receive udev event");
      size_t attempts = 0;
      udev_device *dev = BONGOCAT_NULLPTR;
      while ((dev = udev_monitor_receive_device(input._udev_mon)) != BONGOCAT_NULLPTR && attempts < MAX_ATTEMPTS) {
        const char *action = udev_device_get_action(dev);
        const char *node = udev_device_get_devnode(dev);

        if (action != BONGOCAT_NULLPTR && node != BONGOCAT_NULLPTR) {
          BONGOCAT_LOG_VERBOSE("input: udev %s: %s", action, node);
          if (strcmp(action, "add") == 0 || strcmp(action, "remove") == 0) {
            sync_devices_needed = true;
            reload_devices_needed = true;
          }
        }

        udev_device_unref(dev);
        attempts++;
      }
      drain_event(pfds[fds_udev_monitor_index], MAX_ATTEMPTS, "udev monitor fd");
    }

    // Handle config update
    assert(input._config_generation != BONGOCAT_NULLPTR);
    bool reload_config = false;
    uint64_t new_gen{atomic_load(input._config_generation)};
    if (pfds[fds_update_config_index].revents & POLLIN) {
      BONGOCAT_LOG_DEBUG("input: Receive update config event");
      drain_event(pfds[fds_update_config_index], MAX_ATTEMPTS, "update config eventfd");
      reload_config = new_gen > 0;
      sync_devices_needed |= reload_config;
    }

    // Handle device events
    {
      platform::LockGuard guard(input.input_lock);
      assert(input.shm);
      // auto& input_shm = *input.shm;

      if (fds_device_start_index >= 0) {
        assert(fds_device_start_index >= 0);
        assert(fds_device_end_index >= 0);
        for (nfds_t p = static_cast<nfds_t>(fds_device_start_index); p <= static_cast<nfds_t>(fds_device_end_index);
             p++) {
          // Handle ready devices
          if (pfds[p].revents & POLLIN) {
            // handle evdev input
            const ssize_t rd = read(pfds[p].fd, ev, sizeof(ev));
            if (rd < 0) {
              if (errno == ENODEV) {
                sync_devices_needed = true;
              }
              if (errno == EAGAIN) {
                continue;
              }
              BONGOCAT_LOG_WARNING("input: Read error on fd=%d: %s", pfds[p].fd, strerror(errno));
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
              sync_devices_needed = true;
              continue;
            }
            assert(rd >= 0);
            if (rd == 0 || static_cast<size_t>(rd) % sizeof(input_event) != 0) {
              BONGOCAT_LOG_WARNING("input: EOF or partial read on fd=%d", pfds[p].fd);
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
              sync_devices_needed = true;
              continue;
            }

            bool key_pressed = false;
            // keep captured keycode short-lived
            int captured_keycode = 0;
            assert(rd >= 0);
            assert(sizeof(input_event) > 0);
            const auto num_events = static_cast<ssize_t>(static_cast<size_t>(rd) / sizeof(input_event));
            for (ssize_t j = 0; j < num_events; j++) {
              if (ev[j].type == EV_KEY && ev[j].value == 1) {
                key_pressed = true;
                captured_keycode = ev[j].code;  // Store for hand mapping
                if (enable_debug) {
                  BONGOCAT_LOG_VERBOSE("input: Key event: fd=%d, code=%d, time=%lld.%06lld", pfds[p].fd, ev[j].code,
                                       ev[j].time.tv_sec, ev[j].time.tv_usec);
                } else {
                  // break loop early, when no debug (no print needed for every key press)
                  break;
                }
              }
            }

            const timestamp_ms_t now = get_current_time_ms();
            if (key_pressed) {
              trigger_key_press(animation_ctx, captured_keycode);
            } else {
              input.shm->any_key_pressed = 0;
              input.shm->hand_mapping = input_hand_mapping_t::None;
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
            sync_devices_needed = true;
          }
        }
      }

      // simulate "any key pressed"
      if (fds_stdin_index >= 0) {
        if (pfds[fds_stdin_index].revents & POLLIN) {
          char buf[TEST_STDIN_BUF_LEN] = {0};
          bool got_key = false;

          // Drain stdin until empty (EAGAIN)
          int attempts = 0;
          ssize_t rd = 0;
          while (attempts < MAX_ATTEMPTS) {
            rd = read(pfds[fds_stdin_index].fd, buf, TEST_STDIN_BUF_LEN);
            if (rd > 0) {
              got_key = true;
            }
#if EAGAIN != EWOULDBLOCK
            if (rd == -1 && (errno == EAGAIN || errno == EWOULDBLOCK)) {
#else
            if (rd == -1 && errno == EAGAIN) {
#endif
              break;  // drained completely
            } else {
              break;  // EOF or error
            }
          }

          if (got_key) {
            trigger_key_press(animation_ctx);
            if (enable_debug) {
              const size_t len = (rd > 0) ? (static_cast<size_t>(rd) < TEST_STDIN_BUF_LEN ? static_cast<size_t>(rd)
                                                                                          : TEST_STDIN_BUF_LEN - 1)
                                          : 0;
              buf[len] = '\0';
              BONGOCAT_LOG_VERBOSE("input: stdin input: %s", buf);
            }
          }
        }
      }
    }

    // Revalidate valid devices
    if (sync_devices_needed) {
      platform::LockGuard guard(input.input_lock);

      auto [sync_devices_result, revalid_devices_result] =
          sync_devices(input, {.reload_devices_needed = reload_devices_needed});
      if (revalid_devices_result != bongocat_error_t::BONGOCAT_SUCCESS) {
        BONGOCAT_LOG_ERROR("input: Failed to revalidate devices and file descriptors");
      } else {
        if (sync_devices_result.valid_devices == 0) {
          BONGOCAT_LOG_VERBOSE("input: All input devices became unavailable");
        }
      }
      track_valid_devices = sync_devices_result.valid_devices;
    }

    // handle update config
    if (reload_config) {
      assert(input._config_generation != BONGOCAT_NULLPTR);
      assert(input._configs_reloaded_cond != BONGOCAT_NULLPTR);
      assert(input._config != BONGOCAT_NULLPTR);

      update_config(input, *input._config, new_gen);

      // wait for reload config to be done (all configs)
      const int rc = input._configs_reloaded_cond->timedwait(
          [&] { return atomic_load(input._config_generation) >= new_gen; }, COND_RELOAD_CONFIGS_TIMEOUT_MS);
      if (rc == ETIMEDOUT) {
        BONGOCAT_LOG_WARNING("input: Timed out waiting for reload eventfd: %s", strerror(errno));
      }
      if constexpr (features::Debug) {
        if (atomic_load(&input.config_seen_generation) < atomic_load(input._config_generation)) {
          BONGOCAT_LOG_VERBOSE("input: input.config_seen_generation < input._config_generation; %d < %d",
                               atomic_load(&input.config_seen_generation), atomic_load(input._config_generation));
        }
      }
      // assert(atomic_load(&input.config_seen_generation) >= atomic_load(input._config_generation));
      atomic_store(&input.config_seen_generation, atomic_load(input._config_generation));
      BONGOCAT_LOG_INFO("input: Input config reloaded (gen=%u)", new_gen);
    }
  }

  close_fd(tty_fd);

  atomic_store(&input._capture_input_running, false);
  if (track_valid_devices == 0) {
    BONGOCAT_LOG_ERROR("input: All input devices are unavailable");
  }

  // Will run only on normal return
  pthread_cleanup_pop(1);  // 1 = call cleanup even if not canceled

  // done when callback cleanup_input_thread
  // cleanup_input_thread_context(arg);
  // sanity check for clean up
  assert(input._device_paths == BONGOCAT_NULLPTR);
  assert(input._unique_devices == BONGOCAT_NULLPTR);
  assert(input._unique_paths_indices == BONGOCAT_NULLPTR);
  assert(input._unique_paths_indices_capacity == 0);

  BONGOCAT_LOG_INFO("Input monitoring stopped");

  return BONGOCAT_NULLPTR;
}

created_result_t<AllocatedMemory<input_context_t>> create(const config::config_t& config) {
  AllocatedMemory<input_context_t> ret = make_allocated_memory<input_context_t>();
  assert(ret);
  if (ret == BONGOCAT_NULLPTR) [[unlikely]] {
    return bongocat_error_t::BONGOCAT_ERROR_MEMORY;
  }
  if (config.num_keyboard_devices <= 0) {
    BONGOCAT_LOG_WARNING("No input devices specified");
  }

  const timestamp_ms_t now = get_current_time_ms();
  ret->_capture_input_running = false;
  ret->_input_kpm_counter = 0;
  ret->_latest_kpm_update_ms = now;

  BONGOCAT_LOG_INFO("Initializing input monitoring system for %d devices", config.num_keyboard_devices);

  // Initialize shared memory for key press flag
  ret->shm = make_allocated_mmap<input_shared_memory_t>();
  if (!ret->shm.ptr) {
    BONGOCAT_LOG_ERROR("Failed to create shared memory for input monitoring: %s", strerror(errno));
    return bongocat_error_t::BONGOCAT_ERROR_MEMORY;
  }
  ret->shm->any_key_pressed = 0;
  ret->shm->hand_mapping = input_hand_mapping_t::None;
  ret->shm->kpm = 0;
  ret->shm->input_counter = 0;
  ret->shm->last_key_pressed_timestamp = 0;

  // Initialize shared memory for local config
  ret->_local_copy_config = make_allocated_mmap<config::config_t>();
  if (!ret->_local_copy_config) {
    BONGOCAT_LOG_ERROR("Failed to create shared memory for input monitoring: %s", strerror(errno));
    return bongocat_error_t::BONGOCAT_ERROR_MEMORY;
  }
  assert(ret->_local_copy_config);
  *ret->_local_copy_config = config;

  ret->update_config_efd = platform::FileDescriptor(eventfd(0, EFD_NONBLOCK | EFD_CLOEXEC));
  if (ret->update_config_efd._fd < 0) {
    BONGOCAT_LOG_ERROR("Failed to create notify pipe for input update config: %s", strerror(errno));
    return bongocat_error_t::BONGOCAT_ERROR_FILE_IO;
  }

  BONGOCAT_LOG_INFO("Input monitoring started");
  return ret;
}

bongocat_error_t start(input_context_t& input, animation::animation_context_t& animation_ctx,
                       const config::config_t& config, CondVariable& configs_reloaded_cond,
                       atomic_uint64_t& config_generation) {
  if (config.num_keyboard_devices < 0) {
    BONGOCAT_LOG_ERROR("No input devices specified");
    return bongocat_error_t::BONGOCAT_ERROR_INVALID_PARAM;
  } else if (config.num_keyboard_devices == 0) {
    BONGOCAT_LOG_WARNING("No input devices specified");
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
  input.shm->hand_mapping = input_hand_mapping_t::None;
  input.shm->kpm = 0;
  input.shm->input_counter = 0;
  input.shm->last_key_pressed_timestamp = now;  // for idle check timestamp should be zero

  // Initialize shared memory for local config
  input._local_copy_config = make_allocated_mmap<config::config_t>();
  if (!input._local_copy_config) {
    BONGOCAT_LOG_ERROR("Failed to create shared memory for input monitoring: %s", strerror(errno));
    return bongocat_error_t::BONGOCAT_ERROR_MEMORY;
  }
  assert(input._local_copy_config);
  update_config(input, config, atomic_load(&config_generation));

  // wait for animation trigger to be ready (input should be the same)
  int cond_ret = animation_ctx.init_cond.timedwait([&]() { return atomic_load(&animation_ctx.ready); },
                                                   COND_ANIMATION_TRIGGER_INIT_TIMEOUT_MS);
  if (cond_ret == ETIMEDOUT) {
    BONGOCAT_LOG_ERROR("Failed to initialize input monitoring: waiting for animation thread to start in time");
  } else {
    assert(animation_ctx._input == &input);
  }
  // set extern/global references
  {
    // guard for anim_update_state
    LockGuard guard(animation_ctx.thread_context.anim_lock);
    animation_ctx._input = &input;
  }
  animation_ctx.init_cond.notify_all();
  input._config = &config;
  input._configs_reloaded_cond = &configs_reloaded_cond;
  input._config_generation = &config_generation;
  atomic_store(&input.ready, true);
  input.init_cond.notify_all();

  input._configs_reloaded_cond->notify_all();

  // start input monitoring thread
  const int result = pthread_create(&input._input_thread, BONGOCAT_NULLPTR, input_thread, &animation_ctx);
  if (result != 0) {
    BONGOCAT_LOG_ERROR("Failed to start input monitoring thread: %s", strerror(errno));
    return bongocat_error_t::BONGOCAT_ERROR_THREAD;
  }

  BONGOCAT_LOG_INFO("Input monitoring started");
  return bongocat_error_t::BONGOCAT_SUCCESS;
}

bongocat_error_t restart(input_context_t& input, animation::animation_context_t& animation_ctx,
                         const config::config_t& config, CondVariable& configs_reloaded_cond,
                         atomic_uint64_t& config_generation) {
  BONGOCAT_LOG_INFO("Restarting input monitoring system");
  // Stop current monitoring
  if (input._input_thread) {
    BONGOCAT_LOG_DEBUG("Input monitoring thread");
    atomic_store(&input._capture_input_running, false);
    // pthread_cancel(ctx->_input_thread);
    if (stop_thread_graceful_or_cancel(input._input_thread, input._capture_input_running) != 0) {
      BONGOCAT_LOG_ERROR("Failed to join input thread: %s", strerror(errno));
    }
    BONGOCAT_LOG_DEBUG("Input monitoring thread terminated");
  }

  // already done when stop current input thread
  // cleanup_input_thread_context(ctx);
  assert(!input._device_paths);
  assert(!input._unique_paths_indices);
  assert(!input._unique_devices);
  assert(input._unique_paths_indices_capacity == 0);

  // reset stats
  // ret._latest_kpm_update_ms = get_current_time_ms();

  /// @TODO: re-create context with create(), avoid duplicate code

  // Start new monitoring (reuse shared memory if it exists)
  {
    LockGuard guard(input.input_lock);
    if (!input.shm) {
      input.shm = make_allocated_mmap<input_shared_memory_t>();
      if (input.shm.ptr == MAP_FAILED) {
        BONGOCAT_LOG_ERROR("Failed to create shared memory for input monitoring: %s", strerror(errno));
        return bongocat_error_t::BONGOCAT_ERROR_MEMORY;
      }
    }
  }

  if (!input._local_copy_config) {
    input._local_copy_config = make_unallocated_mmap_value<config::config_t>(config);
    if (!input._local_copy_config) {
      BONGOCAT_LOG_ERROR("Failed to create shared memory for input monitoring: %s", strerror(errno));
      return bongocat_error_t::BONGOCAT_ERROR_MEMORY;
    }
  }
  assert(input._local_copy_config);
  update_config(input, config, atomic_load(&config_generation));

  if (input.update_config_efd._fd < 0) {
    input.update_config_efd = platform::FileDescriptor(eventfd(0, EFD_NONBLOCK | EFD_CLOEXEC));
    if (input.update_config_efd._fd < 0) {
      BONGOCAT_LOG_ERROR("Failed to create notify pipe for input, update config: %s", strerror(errno));
      return bongocat_error_t::BONGOCAT_ERROR_FILE_IO;
    }
  }

  // if (trigger_ctx._input != ctx._input) {
  //     BONGOCAT_LOG_DEBUG("Input context in animation differs from animation trigger input context");
  // }

  // set extern/global references
  {
    // guard for anim_update_state
    LockGuard guard(animation_ctx.thread_context.anim_lock);
    animation_ctx._input = &input;
  }
  input._config = &config;
  input._configs_reloaded_cond = &configs_reloaded_cond;
  input._config_generation = &config_generation;
  atomic_store(&input.config_seen_generation, atomic_load(&config_generation));
  input.init_cond.notify_all();
  input._configs_reloaded_cond->notify_all();

  // start input monitoring
  const int result = pthread_create(&input._input_thread, BONGOCAT_NULLPTR, input_thread, &animation_ctx);
  if (result != 0) {
    BONGOCAT_LOG_ERROR("Failed to start input monitoring thread: %s", strerror(errno));
    return bongocat_error_t::BONGOCAT_ERROR_THREAD;
  }

  BONGOCAT_LOG_INFO("Input monitoring restarted");
  return bongocat_error_t::BONGOCAT_SUCCESS;
}

void stop(input_context_t& ctx) {
  atomic_store(&ctx._capture_input_running, false);
  if (ctx._input_thread) {
    BONGOCAT_LOG_DEBUG("Stopping input thread");
    // pthread_cancel(ctx->_input_thread);
    if (stop_thread_graceful_or_cancel(ctx._input_thread, ctx._capture_input_running) != 0) {
      BONGOCAT_LOG_ERROR("Failed to join input thread: %s", strerror(errno));
    }
    BONGOCAT_LOG_DEBUG("Input monitoring thread terminated");
  }
  ctx._input_thread = 0;

  ctx._config = BONGOCAT_NULLPTR;
  ctx._configs_reloaded_cond = BONGOCAT_NULLPTR;
  ctx._config_generation = BONGOCAT_NULLPTR;

  ctx.config_updated.notify_all();
  atomic_store(&ctx.ready, false);
  ctx.init_cond.notify_all();
}

void trigger_update_config(input_context_t& input, const config::config_t& config, uint64_t config_generation) {
  // assert(input.anim._local_copy_config != nullptr);
  // assert(input.anim.shm != nullptr);

  input._config = &config;
  if (write(input.update_config_efd._fd, &config_generation, sizeof(uint64_t)) >= 0) {
    BONGOCAT_LOG_VERBOSE("Write input trigger update config");
  } else {
    BONGOCAT_LOG_ERROR("Failed to write to notify pipe in input: %s", strerror(errno));
  }
}

void update_config(input_context_t& input, const config::config_t& config, uint64_t new_gen) {
  assert(input._local_copy_config);

  *input._local_copy_config = config;

  atomic_store(&input.config_seen_generation, new_gen);
  // Signal main that reload is done
  input.config_updated.notify_all();
}
}  // namespace bongocat::platform::input
