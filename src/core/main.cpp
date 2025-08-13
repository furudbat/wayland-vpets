#define _POSIX_C_SOURCE 200809L
#define _DEFAULT_SOURCE
#include "core/bongocat.h"
#include "platform/wayland.h"
#include "graphics/animation.h"
#include "platform/input.h"
#include "config/config.h"
#include "utils/error.h"
#include "utils/memory.h"
#include <csignal>
#include <sys/wait.h>
#include <sys/file.h>
#include <unistd.h>
#include <cstdlib>
#include <cassert>
#include <fcntl.h>
#include <sys/signalfd.h>

// =============================================================================
// GLOBAL STATE AND CONFIGURATION
// =============================================================================

static volatile sig_atomic_t running {0};
static int signal_fd {-1};

static config_t g_config{};
static config_watcher_t g_config_watcher{};

static input_context_t g_input_ctx{};
static animation_context_t g_animation_ctx{};
static animation_trigger_context_t g_animation_trigger_ctx{};
static wayland_context_t g_wayland_ctx{};
static wayland_listeners_context_t g_wayland_listeners_ctx{};

static pthread_mutex_t g_config_reload_mutex = PTHREAD_MUTEX_INITIALIZER;
static const char *g_signal_watch_path = NULL;

static load_config_overwrite_parameters_t g_overwrite_parameters{};

inline static constexpr size_t PID_STR_BUF = 64;

inline static constexpr time_ms_t WAIT_FOR_SHUTDOWN_MS = 5000;
inline static constexpr time_ms_t SLEEP_WAIT_FOR_SHUTDOWN_MS = 100;
static_assert(SLEEP_WAIT_FOR_SHUTDOWN_MS > 0);

// =============================================================================
// COMMAND LINE ARGUMENTS STRUCTURE
// =============================================================================

struct cli_args_t {
    const char *config_file;
    bool watch_config;
    bool toggle_mode;
    bool show_help;
    bool show_version;
    const char *output_name;
};

// =============================================================================
// PROCESS MANAGEMENT MODULE
// =============================================================================

inline static constexpr auto DEFAULT_PID_FILE = "/tmp/bongocat.pid";
inline static constexpr auto PID_FILE_WITH_SUFFIX_TEMPLATE = "/tmp/bongocat-%s.pid";

static int process_create_pid_file(const char *pid_filename) {
    const int fd = open(pid_filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd < 0) {
        BONGOCAT_LOG_ERROR("Failed to create PID file: %s", strerror(errno));
        return -1;
    }
    
    if (flock(fd, LOCK_EX | LOCK_NB) < 0) {
        close(fd);
        if (errno == EWOULDBLOCK) {
            BONGOCAT_LOG_INFO("Another instance is already running");
            return -2; // Already running
        }
        BONGOCAT_LOG_ERROR("Failed to lock PID file: %s", strerror(errno));
        return -1;
    }
    
    char pid_str[PID_STR_BUF] = {0};
    snprintf(pid_str, sizeof(pid_str), "%d\n", getpid());
    if (write(fd, pid_str, strlen(pid_str)) < 0) {
        BONGOCAT_LOG_ERROR("Failed to write PID to file: %s", strerror(errno));
        close(fd);
        return -1;
    }
    
    return fd; // Keep file descriptor open to maintain lock
}

static void process_remove_pid_file(const char* pid_filename) {
    assert(pid_filename);
    unlink(pid_filename);
}

static pid_t process_get_running_pid(const char* pid_filename) {
    assert(pid_filename);
    int fd = open(pid_filename, O_RDONLY);
    if (fd < 0) {
        return -1; // No PID file exists
    }
    
    // Try to get a shared lock to read the file
    if (flock(fd, LOCK_SH | LOCK_NB) < 0) {
        close(fd);
        if (errno == EWOULDBLOCK) {
            // File is locked by another process, so it's running
            // We need to read the PID anyway, so let's try without lock
            fd = open(DEFAULT_PID_FILE, O_RDONLY);
            if (fd < 0) return -1;
        } else {
            return -1;
        }
    }
    
    char pid_str[PID_STR_BUF] = {0};
    ssize_t bytes_read = read(fd, pid_str, sizeof(pid_str) - 1);
    close(fd);
    
    if (bytes_read <= 0) {
        return -1;
    }
    
    pid_str[bytes_read] = '\0';
    pid_t pid = (pid_t)atoi(pid_str);
    
    if (pid <= 0) {
        return -1;
    }
    
    // Check if process is actually running
    if (kill(pid, 0) == 0) {
        return pid; // Process is running
    }

    return -1;
}

static int process_handle_toggle(const char* pid_filename) {
    const pid_t running_pid = process_get_running_pid(pid_filename);
    if (running_pid < 0) {
        // Process is not running, remove stale PID file
        process_remove_pid_file(pid_filename);
    }

    if (running_pid > 0) {
        // Process is running, kill it
        BONGOCAT_LOG_INFO("Stopping bongocat (PID: %d)", running_pid);
        if (kill(running_pid, SIGTERM) == 0) {
            // Wait a bit for graceful shutdown
            for (int i = 0; i < WAIT_FOR_SHUTDOWN_MS/SLEEP_WAIT_FOR_SHUTDOWN_MS; i++) { // Wait up to 5 seconds
                if (kill(running_pid, 0) != 0) {
                    BONGOCAT_LOG_INFO("Bongocat stopped successfully");
                    return 0;
                }
                usleep(SLEEP_WAIT_FOR_SHUTDOWN_MS*1000); // 100ms
            }
            
            // Force kill if still running
            BONGOCAT_LOG_WARNING("Force killing bongocat");
            kill(running_pid, SIGKILL);
            BONGOCAT_LOG_INFO("Bongocat force stopped");
        } else {
            BONGOCAT_LOG_ERROR("Failed to stop bongocat: %s", strerror(errno));
            return 1;
        }
    } else {
        BONGOCAT_LOG_INFO("Bongocat is not running, starting it now");
        return -1; // Signal to continue with normal startup
    }
    
    return 0;
}


// =============================================================================
// CONFIGURATION MANAGEMENT MODULE
// =============================================================================

static bool config_devices_changed(const config_t *old_config, const config_t *new_config) {
    assert(old_config);
    assert(new_config);
    if (old_config->num_keyboard_devices != new_config->num_keyboard_devices) {
        return true;
    }

    // Check if any device paths changed
    for (int i = 0; i < new_config->num_keyboard_devices; i++) {
        bool found = false;
        for (int j = 0; j < old_config->num_keyboard_devices; j++) {
            if (strcmp(new_config->keyboard_devices[i], old_config->keyboard_devices[j]) == 0) {
                found = true;
                break;
            }
        }
        if (!found) {
            return true;
        }
    }

    return false;
}

static void config_reload_callback() {
    BONGOCAT_LOG_INFO("Reloading configuration from: %s", g_config_watcher.config_path);
    
    // Create a temporary config to test loading
    config_t new_config;
    config_set_defaults(&new_config);
    bongocat_error_t result = load_config(&new_config, g_config_watcher.config_path, &g_overwrite_parameters);
    if (result != bongocat_error_t::BONGOCAT_SUCCESS) {
        BONGOCAT_LOG_ERROR("Failed to reload config: %s", bongocat_error_string(result));
        BONGOCAT_LOG_INFO("Keeping current configuration");
        return;
    }


    // If successful, check if input devices changed before updating config
    bool devices_changed = config_devices_changed(&g_config, &new_config);

    // Clean up old output_name if it exists and is different
    if (g_config.output_name && new_config.output_name &&
        strcmp(g_config.output_name, new_config.output_name) != 0) {
        free(g_config.output_name);
    } else if (g_config.output_name && !new_config.output_name) {
        free(g_config.output_name);
    }

    // If successful, update the global config
    pthread_mutex_lock(&g_config_reload_mutex);
    // free old config (make g_config 'available' for new_config)
    config_t old_config = g_config;
    for (size_t i = 0; i < MAX_INPUT_DEVICES; i++) {
        if (old_config.keyboard_devices[i]) free(old_config.keyboard_devices[i]);
        old_config.keyboard_devices[i] = NULL;
        g_config.keyboard_devices[i] = NULL;
    }
    old_config.num_keyboard_devices = 0;
    g_config.num_keyboard_devices = 0;
    // move new_config into g_config, move devices too
    memcpy(&g_config, &new_config, sizeof(config_t));
    // Update the running systems with new config
    input_update_config(&g_input_ctx, &g_config);
    animation_update_config(&g_animation_ctx, &g_config);
    wayland_update_config(&g_wayland_ctx, &g_config, &g_animation_trigger_ctx);
    
    // Check if input devices changed and restart monitoring if needed
    if (devices_changed) {
        BONGOCAT_LOG_INFO("Input devices changed, restarting input monitoring");
        bongocat_error_t input_result = input_restart_monitoring(&g_animation_trigger_ctx, &g_input_ctx,
                                                                 g_config.keyboard_devices,
                                                                 g_config.num_keyboard_devices,
                                                                 g_config.enable_debug);
        if (input_result != bongocat_error_t::BONGOCAT_SUCCESS) {
            BONGOCAT_LOG_ERROR("Failed to restart input monitoring: %s", bongocat_error_string(input_result));
        } else {
            BONGOCAT_LOG_INFO("Input monitoring restarted successfully");
        }
    }

    // free old keyboard_devices
    config_cleanup(&old_config);
    pthread_mutex_unlock(&g_config_reload_mutex);

    BONGOCAT_LOG_INFO("Configuration reloaded successfully!");
    BONGOCAT_LOG_INFO("New screen dimensions: %dx%d", g_wayland_ctx._screen_width, g_config.bar_height);
}

static bongocat_error_t config_setup_watcher(const char *config_file) {
    const char *watch_path = config_file ? config_file : "bongocat.conf";
    g_signal_watch_path = config_file ? config_file : "bongocat.conf";

    if (config_watcher_init(&g_config_watcher, watch_path) == bongocat_error_t::BONGOCAT_SUCCESS) {
        config_watcher_start(&g_config_watcher);
        BONGOCAT_LOG_INFO("Config file watching enabled for: %s", watch_path);
        return bongocat_error_t::BONGOCAT_SUCCESS;
    } else {
        BONGOCAT_LOG_WARNING("Failed to initialize config watcher, continuing without hot-reload");
        return bongocat_error_t::BONGOCAT_ERROR_CONFIG;
    }
}

// =============================================================================
// SIGNAL HANDLING MODULE
// =============================================================================

static bongocat_error_t signal_setup_handlers(void) {
    sigset_t mask;
    sigemptyset(&mask);
    sigaddset(&mask, SIGINT);
    sigaddset(&mask, SIGTERM);
    sigaddset(&mask, SIGCHLD);
    sigaddset(&mask, SIGUSR2);

    // Block signals globally so they are only delivered via signalfd
    if (sigprocmask(SIG_BLOCK, &mask, NULL) == -1) {
        BONGOCAT_LOG_ERROR("Failed to block signals: %s", strerror(errno));
        return bongocat_error_t::BONGOCAT_ERROR_THREAD;
    }

    signal_fd = signalfd(-1, &mask, SFD_NONBLOCK | SFD_CLOEXEC);
    if (signal_fd == -1) {
        BONGOCAT_LOG_ERROR("Failed to create signalfd: %s", strerror(errno));
        return bongocat_error_t::BONGOCAT_ERROR_THREAD;
    }

    return bongocat_error_t::BONGOCAT_SUCCESS;
}

// =============================================================================
// SYSTEM INITIALIZATION AND CLEANUP MODULE
// =============================================================================

static bongocat_error_t system_initialize_components(void) {
    bongocat_error_t result;
    
    // Initialize Wayland
    /// @NOTE: animation needed only for reference
    result = wayland_init(&g_wayland_listeners_ctx, &g_wayland_ctx, &g_animation_ctx, &g_animation_trigger_ctx, &g_config);
    if (result != bongocat_error_t::BONGOCAT_SUCCESS) {
        BONGOCAT_LOG_ERROR("Failed to initialize Wayland: %s", bongocat_error_string(result));
        return result;
    }
    
    // Initialize animation system
    result = animation_init(&g_animation_trigger_ctx, &g_animation_ctx, &g_config);
    if (result != bongocat_error_t::BONGOCAT_SUCCESS) {
        BONGOCAT_LOG_ERROR("Failed to initialize animation system: %s", bongocat_error_string(result));
        return result;
    }
    
    // Start input monitoring
    result = input_start_monitoring(&g_animation_trigger_ctx, &g_input_ctx, g_config.keyboard_devices, g_config.num_keyboard_devices, g_config.enable_debug);
    if (result != bongocat_error_t::BONGOCAT_SUCCESS) {
        BONGOCAT_LOG_ERROR("Failed to start input monitoring: %s", bongocat_error_string(result));
        return result;
    }
    
    // Start animation thread
    result = animation_start(&g_animation_trigger_ctx, &g_animation_ctx, &g_input_ctx);
    if (result != bongocat_error_t::BONGOCAT_SUCCESS) {
        BONGOCAT_LOG_ERROR("Failed to start animation thread: %s", bongocat_error_string(result));
        return result;
    }

    return bongocat_error_t::BONGOCAT_SUCCESS;
}

[[ noreturn ]] static void system_cleanup_and_exit(char* pid_filename, int exit_code) {
    BONGOCAT_LOG_INFO("Performing cleanup...");

    running = 0;

    // Remove PID file
    process_remove_pid_file(pid_filename);
    if (pid_filename) free(pid_filename);
    pid_filename = NULL;

    // Cleanup Wayland
    wayland_cleanup(&g_wayland_listeners_ctx);

    // stop threads
    atomic_store(&g_animation_ctx._animation_running, false);
    atomic_store(&g_input_ctx._capture_input_running, false);
    atomic_store(&g_config_watcher._running, false);
    join_thread_with_timeout(&g_animation_ctx._anim_thread, 1000);
    join_thread_with_timeout(&g_input_ctx._input_thread, 2000);
    join_thread_with_timeout(&g_config_watcher._watcher_thread, 5000);
    animation_stop(&g_animation_ctx);
    input_stop(&g_input_ctx);
    config_watcher_stop(&g_config_watcher);

    // Cleanup input system
    input_cleanup(&g_input_ctx);
    // Cleanup animation system
    animation_cleanup(&g_animation_trigger_ctx, &g_animation_ctx);
    // Cleanup config watcher
    config_watcher_cleanup(&g_config_watcher);

    if (signal_fd >= 0) close(signal_fd);
    g_signal_watch_path = NULL;

#ifndef BONGOCAT_DISABLE_MEMORY_STATISTICS
    // Print memory statistics in debug mode
    if (g_config.enable_debug) {
        memory_print_stats();
    }
#endif

    // Cleanup configuration
    config_cleanup(&g_config);
    g_overwrite_parameters.output_name = NULL;

#ifndef NDEBUG
    memory_leak_check();
#endif
    
    BONGOCAT_LOG_INFO("Cleanup complete, exiting with code %d", exit_code);
    exit(exit_code);
}

// =============================================================================
// COMMAND LINE PROCESSING MODULE
// =============================================================================

static void cli_show_help(const char *program_name) {
    printf("Bongo Cat Wayland Overlay\n");
    printf("Usage: %s [options]\n", program_name);
    printf("Options:\n");
    printf("  -h, --help            Show this help message\n");
    printf("  -v, --version         Show version information\n");
    printf("  -c, --config          Specify config file (default: bongocat.conf)\n");
    printf("  -w, --watch-config    Watch config file for changes and reload automatically\n");
    printf("  -t, --toggle          Toggle bongocat on/off (start if not running, stop if running)\n");
    printf("  -o, --output-name     Specify output name (overwrite output_name from config)\n");
    printf("\nConfiguration is loaded from bongocat.conf in the current directory.\n");
}

static void cli_show_version(void) {
    printf("Bongo Cat Overlay v%s\n", BONGOCAT_VERSION);
    printf("Built with fast optimizations\n");
}

static int cli_parse_arguments(int argc, char *argv[], cli_args_t *args) {
    // Initialize arguments with defaults
    *args = (cli_args_t){
        .config_file = NULL,
        .watch_config = false,
        .toggle_mode = false,
        .show_help = false,
        .show_version = false,
        .output_name = NULL,
    };

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--help") == 0 || strcmp(argv[i], "-h") == 0) {
            args->show_help = true;
        } else if (strcmp(argv[i], "--version") == 0 || strcmp(argv[i], "-v") == 0) {
            args->show_version = true;
        } else if (strcmp(argv[i], "--config") == 0 || strcmp(argv[i], "-c") == 0) {
            if (i + 1 < argc) {
                args->config_file = argv[i + 1];
                i++; // Skip the next argument since it's the config file path
            } else {
                BONGOCAT_LOG_ERROR("--config option requires a file path");
                return EXIT_FAILURE;
            }
        } else if (strcmp(argv[i], "--watch-config") == 0 || strcmp(argv[i], "-w") == 0) {
            args->watch_config = true;
        } else if (strcmp(argv[i], "--toggle") == 0 || strcmp(argv[i], "-t") == 0) {
            args->toggle_mode = true;
        } else if (strcmp(argv[i], "--output-name") == 0 || strcmp(argv[i], "-o") == 0) {
            if (i + 1 < argc) {
                args->output_name = argv[i + 1];
                i++; // Skip the next argument since it's the output name
            } else {
                BONGOCAT_LOG_ERROR("--output-name option requires a output name");
                return EXIT_FAILURE;
            }
        } else {
            BONGOCAT_LOG_WARNING("Unknown argument: %s", argv[i]);
        }
    }
    
    return 0;
}

// =============================================================================
// MAIN APPLICATION ENTRY POINT
// =============================================================================

int main(int argc, char *argv[]) {
    bongocat_error_t result;

    // Initialize error system early
    bongocat_error_init(1); // Enable debug initially

    BONGOCAT_LOG_INFO("Starting Bongo Cat Overlay v%s", BONGOCAT_VERSION);

    // Parse command line arguments
    cli_args_t args{};
    if (cli_parse_arguments(argc, argv, &args) != 0) {
        return EXIT_FAILURE;
    }

    // Handle help and version requests
    if (args.show_help) {
        cli_show_help(argv[0]);
        return EXIT_SUCCESS;
    }

    if (args.show_version) {
        cli_show_version();
        return EXIT_SUCCESS;
    }

    // init default values
    config_set_defaults(&g_config);
    // in case config watcher is not started/inited
    g_config_watcher.inotify_fd = -1;
    g_config_watcher.watch_fd = -1;
    g_config_watcher.config_path = NULL;
    g_config_watcher.reload_efd = -1;
    g_config_watcher._watcher_thread = 0;
    g_config_watcher._running = false;

    // Load configuration
    g_overwrite_parameters = (load_config_overwrite_parameters_t){
        .output_name = args.output_name,
    };
    result = load_config(&g_config, args.config_file, &g_overwrite_parameters);
    if (result != bongocat_error_t::BONGOCAT_SUCCESS) {
        BONGOCAT_LOG_ERROR("Failed to load configuration: %s", bongocat_error_string(result));
        return EXIT_FAILURE;
    }

    // set pid file, based on output_name
    char* pid_filename = NULL;
    if (g_config.output_name && g_config.output_name[0] != '\0') {
        size_t needed_size = snprintf(NULL, 0, PID_FILE_WITH_SUFFIX_TEMPLATE, g_config.output_name) + 1;
        pid_filename = (char*)malloc(needed_size);
        if (pid_filename != NULL) {
            snprintf(pid_filename, needed_size, PID_FILE_WITH_SUFFIX_TEMPLATE, g_config.output_name);
        } else {
            BONGOCAT_LOG_ERROR("Failed to allocate PID filename");
            config_cleanup(&g_config);
            return EXIT_FAILURE;
        }
    } else {
        pid_filename = strdup(DEFAULT_PID_FILE);
    }

    // Handle toggle mode
    if (args.toggle_mode) {
        int toggle_result = process_handle_toggle(pid_filename);
        if (toggle_result >= 0) {
            if (pid_filename) free(pid_filename);
            return toggle_result; // Either successfully toggled off or error
        }
        // toggle_result == -1 means continue with startup
    }

    // Create PID file to track this instance
    const int pid_fd = process_create_pid_file(pid_filename);
    if (pid_fd == -2) {
        BONGOCAT_LOG_ERROR("Another instance of bongocat is already running");
        if (pid_filename) free(pid_filename);
        config_cleanup(&g_config);
        return EXIT_FAILURE;
    } else if (pid_fd < 0) {
        BONGOCAT_LOG_ERROR("Failed to create PID file");
        if (pid_filename) free(pid_filename);
        config_cleanup(&g_config);
        return EXIT_FAILURE;
    }
    BONGOCAT_LOG_INFO("PID file created: %s", pid_filename);

    // more randomness is needed to create better shm names, see create_shm
    srand((unsigned)time(NULL) ^ getpid()); // seed once, include pid for better randomness

    // Setup signal handlers
    g_signal_watch_path = args.config_file;
    result = signal_setup_handlers();
    if (result != bongocat_error_t::BONGOCAT_SUCCESS) {
        config_cleanup(&g_config);
        process_remove_pid_file(pid_filename);
        if (pid_filename) free(pid_filename);
        BONGOCAT_LOG_ERROR("Failed to setup signal handlers: %s", bongocat_error_string(result));
        return EXIT_FAILURE;
    }

    
    // Initialize config watcher if requested
    if (args.watch_config) {
        config_setup_watcher(args.config_file);
    }
    
    // Initialize all system components
    result = system_initialize_components();
    if (result != bongocat_error_t::BONGOCAT_SUCCESS) {
        system_cleanup_and_exit(pid_filename, EXIT_FAILURE);
    }

    if (abs(g_config.cat_x_offset) > g_wayland_ctx._screen_width) {
        BONGOCAT_LOG_WARNING("cat_x_offset %d may position cat off-screen (screen width: %d)",
                            g_config.cat_x_offset, g_wayland_ctx._screen_width);
    }

    BONGOCAT_LOG_INFO("Bar dimensions: %dx%d", g_wayland_ctx._screen_width, g_config.bar_height);

    // Validate Setup
    assert(g_animation_trigger_ctx._input == &g_input_ctx);
    assert(g_animation_trigger_ctx._anim == &g_animation_ctx);

    BONGOCAT_LOG_INFO("Bongo Cat Overlay configured successfully");

    // trigger initial rendering
    wayland_request_render(&g_animation_trigger_ctx);
    // Main Wayland event loop with graceful shutdown
    result = wayland_run(&g_wayland_listeners_ctx, &running, signal_fd, &g_config, &g_config_watcher, config_reload_callback);
    if (result != bongocat_error_t::BONGOCAT_SUCCESS) {
        BONGOCAT_LOG_ERROR("Wayland event loop error: %s", bongocat_error_string(result));
        system_cleanup_and_exit(pid_filename, EXIT_FAILURE);
    }
    
    BONGOCAT_LOG_INFO("Main loop exited, shutting down");
    system_cleanup_and_exit(pid_filename, EXIT_SUCCESS);
    
    return EXIT_SUCCESS; // Never reached
}