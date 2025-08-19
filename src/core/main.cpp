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
#include <cstdio>
#include <cassert>
#include <fcntl.h>
#include <sys/signalfd.h>

// =============================================================================
// GLOBAL STATE AND CONFIGURATION
// =============================================================================

namespace bongocat {
    inline static constexpr platform::time_ms_t WAIT_FOR_SHUTDOWN_MS = 5000;
    inline static constexpr platform::time_ms_t SLEEP_WAIT_FOR_SHUTDOWN_MS = 100;
    static_assert(SLEEP_WAIT_FOR_SHUTDOWN_MS > 0);

    struct main_context_t;
    void stop_threads(main_context_t& context);
    void cleanup(main_context_t& context);

    struct main_context_t {
        volatile sig_atomic_t running {0};
        platform::FileDescriptor signal_fd {-1};

        config::config_t config;
        config::config_watcher_t config_watcher;
        config::load_config_overwrite_parameters_t overwrite_config_parameters;

        platform::input::input_context_t input;
        animation::animation_session_t animation;
        platform::wayland::wayland_session_t wayland;

        platform::Mutex config_reload_mutex;
        const char *signal_watch_path{nullptr};

        main_context_t() = default;
        ~main_context_t() {
            cleanup(*this);
        }
        main_context_t(const main_context_t&) = delete;
        main_context_t& operator=(const main_context_t&) = delete;
        main_context_t(main_context_t&&) noexcept = default;
        main_context_t& operator=(main_context_t&&) noexcept = default;
    };
    inline void stop_threads(main_context_t& context) {
        context.running = 0;
        // stop threads
        atomic_store(&context.animation.anim._animation_running, false);
        atomic_store(&context.input._capture_input_running, false);
        atomic_store(&context.config_watcher._running, false);
        platform::join_thread_with_timeout(context.animation.anim._anim_thread, 2000);
        platform::join_thread_with_timeout(context.input._input_thread, 2000);
        platform::join_thread_with_timeout(context.config_watcher._watcher_thread, 5000);
        animation::stop(context.animation.anim);
        platform::input::stop(context.input);
        config::stop_watcher(context.config_watcher);
        //context.animation.anim._anim_thread = 0;
        //context.input._input_thread = 0;
        //context.config_watcher._watcher_thread = 0;
    }
    void cleanup(main_context_t& context) {
        stop_threads(context);

        // Cleanup Wayland
        cleanup_wayland(context.wayland);

        // remove references (avoid dangling pointers)
        context.wayland.animation_trigger_context = nullptr;
        context.animation._input = nullptr;

        // Cleanup systems
        cleanup(context.animation);
        cleanup(context.input);
        if (context.signal_fd._fd >= 0) close_fd(context.signal_fd);
        context.signal_watch_path = nullptr;
        cleanup_watcher(context.config_watcher);

        // Cleanup configuration
        cleanup(context.config);
        context.overwrite_config_parameters.output_name = nullptr;

        // cleanup signals handler
        platform::close_fd(context.signal_fd);
    }

    // =============================================================================
    // COMMAND LINE ARGUMENTS STRUCTURE
    // =============================================================================

    struct cli_args_t {
        const char *config_file{};
        bool watch_config{false};
        bool toggle_mode{false};
        bool show_help{false};
        bool show_version{false};
        const char *output_name{};
    };

    // =============================================================================
    // PROCESS MANAGEMENT MODULE
    // =============================================================================

    inline static constexpr size_t PID_STR_BUF = 64;
    
    inline static constexpr auto DEFAULT_PID_FILE = "/tmp/bongocat.pid";
    inline static constexpr auto PID_FILE_WITH_SUFFIX_TEMPLATE = "/tmp/bongocat-%s.pid";

    static platform::FileDescriptor process_create_pid_file(const char *pid_filename) {
        platform::FileDescriptor fd = platform::FileDescriptor(open(pid_filename, O_CREAT | O_WRONLY | O_TRUNC, 0644));
        if (fd._fd < 0) {
            BONGOCAT_LOG_ERROR("Failed to create PID file: %s", strerror(errno));
            return platform::FileDescriptor(-1);
        }

        if (flock(fd._fd, LOCK_EX | LOCK_NB) < 0) {
            if (errno == EWOULDBLOCK) {
                BONGOCAT_LOG_INFO("Another instance is already running");
                return platform::FileDescriptor(-2); // Already running
            }
            BONGOCAT_LOG_ERROR("Failed to lock PID file: %s", strerror(errno));
            return platform::FileDescriptor(-1);
        }

        char pid_str[PID_STR_BUF] = {};
        snprintf(pid_str, sizeof(pid_str), "%d\n", getpid());
        if (write(fd._fd, pid_str, strlen(pid_str)) < 0) {
            BONGOCAT_LOG_ERROR("Failed to write PID to file: %s", strerror(errno));
            return platform::FileDescriptor(-1);
        }

        return fd; // Keep file descriptor open to maintain lock
    }

    static void process_remove_pid_file(const char* pid_filename) {
        assert(pid_filename);
        unlink(pid_filename);
    }

    static pid_t process_get_running_pid(const char* pid_filename) {
        assert(pid_filename);
        platform::FileDescriptor fd = platform::FileDescriptor(::open(pid_filename, O_RDONLY));
        if (fd._fd < 0) {
            return -1; // No PID file exists
        }

        // Try to get a shared lock to read the file
        if (flock(fd._fd, LOCK_SH | LOCK_NB) < 0) {
            platform::close_fd(fd);
            if (errno == EWOULDBLOCK) {
                // File is locked by another process, so it's running
                // We need to read the PID anyway, so let's try without lock
                fd = platform::FileDescriptor(::open(DEFAULT_PID_FILE, O_RDONLY));
                if (fd._fd < 0) return -1;
            } else {
                return -1;
            }
        }

        char pid_str[PID_STR_BUF] = {};
        const ssize_t bytes_read = read(fd._fd, pid_str, sizeof(pid_str) - 1);
        platform::close_fd(fd);

        if (bytes_read <= 0) {
            return -1;
        }

        pid_str[bytes_read] = '\0';
        char *endptr = nullptr;
        errno = 0; // Reset errno before call
        const auto pid = static_cast<pid_t>(strtol(pid_str, &endptr, 10));
        if (endptr == pid_str) {
            return -1;
        }
        if (*endptr != '\0') {
            BONGOCAT_LOG_ERROR("'%s' contains invalid characters", pid_str);
        } else if ((errno == ERANGE) || pid < 0) {
            BONGOCAT_LOG_ERROR("'%s' out of range for pid_t", pid_str);
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

    static bool config_devices_changed(const config::config_t& old_config, const config::config_t& new_config) {
        if (old_config.num_keyboard_devices != new_config.num_keyboard_devices) {
            return true;
        }

        // Check if any device paths changed
        for (int i = 0; i < new_config.num_keyboard_devices; i++) {
            bool found = false;
            for (int j = 0; j < old_config.num_keyboard_devices; j++) {
                if (strcmp(new_config.keyboard_devices[i], old_config.keyboard_devices[j]) == 0) {
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

    main_context_t* g_main_context = nullptr;
    static void config_reload_callback() {
        assert(g_main_context);
        BONGOCAT_LOG_INFO("Reloading configuration from: %s", g_main_context->config_watcher.config_path);

        // Create a temporary config to test loading
        auto [new_config, result] = config::load(g_main_context->config_watcher.config_path, g_main_context->overwrite_config_parameters);
        if (result != bongocat_error_t::BONGOCAT_SUCCESS) {
            BONGOCAT_LOG_ERROR("Failed to reload config: %s", bongocat::error_string(result));
            BONGOCAT_LOG_INFO("Keeping current configuration");
            return;
        }



        // If successful, update the global config
        do {
            platform::LockGuard config_reload_mutex_guard(g_main_context->config_reload_mutex);

            config::config_t old_config = g_main_context->config;
            // If successful, check if input devices changed before updating config
            const bool devices_changed = config_devices_changed(old_config, new_config);
            g_main_context->config = bongocat::move(new_config);
            // Initialize error system with debug setting
            bongocat::error_init(g_main_context->config.enable_debug);
            /// @NOTE: don't use new_config after move
            // Update the running systems with new config
            platform::input::update_config(g_main_context->input, g_main_context->config);
            animation::update_config(g_main_context->animation.anim, g_main_context->config);
            update_config(g_main_context->wayland.wayland_context, g_main_context->config, g_main_context->animation);

            // Check if input devices changed and restart monitoring if needed
            if (devices_changed) {
                BONGOCAT_LOG_INFO("Input devices changed, restarting input monitoring");
                const bongocat_error_t input_result = platform::input::restart_monitoring(g_main_context->input, g_main_context->animation, g_main_context->config);
                if (input_result != bongocat_error_t::BONGOCAT_SUCCESS) {
                    BONGOCAT_LOG_ERROR("Failed to restart input monitoring: %s", bongocat::error_string(input_result));
                } else {
                    BONGOCAT_LOG_INFO("Input monitoring restarted successfully");
                }
            }
        } while(false);

        BONGOCAT_LOG_INFO("Configuration reloaded successfully!");
        BONGOCAT_LOG_INFO("New screen dimensions: %dx%d", g_main_context->wayland.wayland_context._screen_width, g_main_context->wayland.wayland_context._bar_height);
    }

    static bongocat_error_t start_config_watcher(main_context_t& ctx, const char *config_file) {
        auto [config_watcher, result] = config::create_watcher(config_file);
        if (result == bongocat_error_t::BONGOCAT_SUCCESS) {
            ctx.config_watcher = bongocat::move(config_watcher);
            config::start_watcher(ctx.config_watcher);
            BONGOCAT_LOG_INFO("Config file watching enabled for: %s", config_file);
        } else {
            BONGOCAT_LOG_WARNING("Failed to initialize config watcher, continuing without hot-reload");
        }
        return result;
    }

    // =============================================================================
    // SIGNAL HANDLING MODULE
    // =============================================================================

    static bongocat_error_t signal_setup_handlers(main_context_t& ctx) {
        sigset_t mask;
        sigemptyset(&mask);
        sigaddset(&mask, SIGINT);
        sigaddset(&mask, SIGTERM);
        sigaddset(&mask, SIGCHLD);
        sigaddset(&mask, SIGUSR2);

        // Block signals globally so they are only delivered via signalfd
        if (sigprocmask(SIG_BLOCK, &mask, nullptr) == -1) {
            BONGOCAT_LOG_ERROR("Failed to block signals: %s", strerror(errno));
            return bongocat_error_t::BONGOCAT_ERROR_THREAD;
        }

        ctx.signal_fd = platform::FileDescriptor(signalfd(-1, &mask, SFD_NONBLOCK | SFD_CLOEXEC));
        if (ctx.signal_fd._fd == -1) {
            BONGOCAT_LOG_ERROR("Failed to create signalfd: %s", strerror(errno));
            return bongocat_error_t::BONGOCAT_ERROR_THREAD;
        }

        return bongocat_error_t::BONGOCAT_SUCCESS;
    }

    // =============================================================================
    // SYSTEM INITIALIZATION AND CLEANUP MODULE
    // =============================================================================

    static bongocat_error_t system_initialize_components(main_context_t& ctx) {
        // Initialize input system
        do {
            auto [input, input_result] = platform::input::create(ctx.config);
            if (input_result != bongocat_error_t::BONGOCAT_SUCCESS) {
                BONGOCAT_LOG_ERROR("Failed to initialize animation system: %s", bongocat::error_string(input_result));
                return input_result;
            }
            ctx.input = bongocat::move(input);
        } while (false);

        // Initialize animation system
        do {
            auto [animation, animation_result] = animation::create(ctx.config);
            if (animation_result != bongocat_error_t::BONGOCAT_SUCCESS) {
                BONGOCAT_LOG_ERROR("Failed to initialize animation system: %s", bongocat::error_string(animation_result));
                return animation_result;
            }
            ctx.animation = bongocat::move(animation);
        } while (false);

        // Initialize Wayland
        do {
            /// @NOTE: animation needed only for reference
            auto [wayland, wayland_result] = platform::wayland::create(ctx.animation, ctx.config);
            if (wayland_result != bongocat_error_t::BONGOCAT_SUCCESS) {
                BONGOCAT_LOG_ERROR("Failed to initialize Wayland: %s", bongocat::error_string(wayland_result));
                return wayland_result;
            }
            ctx.wayland = bongocat::move(wayland);
        } while (false);

        // Setup wayland
        bongocat_error_t setup_wayland_result = setup(ctx.wayland, ctx.animation);
        if (setup_wayland_result != bongocat_error_t::BONGOCAT_SUCCESS) {
            BONGOCAT_LOG_ERROR("Failed to setup wayland: %s", bongocat::error_string(setup_wayland_result));
            return setup_wayland_result;
        }

        // Start input monitoring
        bongocat_error_t start_input_result = platform::input::start_monitoring(ctx.input, ctx.animation, ctx.config);
        if (start_input_result != bongocat_error_t::BONGOCAT_SUCCESS) {
            BONGOCAT_LOG_ERROR("Failed to start input monitoring: %s", bongocat::error_string(start_input_result));
            return start_input_result;
        }

        // Start animation thread
        bongocat_error_t start_animation_result = animation::start(ctx.animation, ctx.input);
        if (start_animation_result != bongocat_error_t::BONGOCAT_SUCCESS) {
            BONGOCAT_LOG_ERROR("Failed to start animation thread: %s", bongocat::error_string(start_animation_result));
            return start_animation_result;
        }

        return bongocat_error_t::BONGOCAT_SUCCESS;
    }

    [[ noreturn ]] static void system_cleanup_and_exit(main_context_t& ctx, char* pid_filename, int exit_code) {
        BONGOCAT_LOG_INFO("Performing cleanup...");

         [[maybe_unused]] const bool enable_debug = ctx.config.enable_debug;

        ctx.running = 0;
        // Remove PID file
        process_remove_pid_file(pid_filename);
        if (pid_filename) ::free(pid_filename);

        cleanup(ctx);
        g_main_context = nullptr;

#ifndef BONGOCAT_DISABLE_MEMORY_STATISTICS
        // Print memory statistics in debug mode
        if (enable_debug) {
            memory_print_stats();
        }
#endif

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

    static void cli_show_version() {
        printf("Bongo Cat Overlay v%s\n", BONGOCAT_VERSION);
        printf("Built with fast optimizations\n");
    }

    static int cli_parse_arguments(int argc, char *argv[], cli_args_t& args) {
        // Initialize arguments with defaults
        args = {
            .config_file = nullptr,
            .watch_config = false,
            .toggle_mode = false,
            .show_help = false,
            .show_version = false,
            .output_name = nullptr,
        };

        for (int i = 1; i < argc; i++) {
            if (strcmp(argv[i], "--help") == 0 || strcmp(argv[i], "-h") == 0) {
                args.show_help = true;
            } else if (strcmp(argv[i], "--version") == 0 || strcmp(argv[i], "-v") == 0) {
                args.show_version = true;
            } else if (strcmp(argv[i], "--config") == 0 || strcmp(argv[i], "-c") == 0) {
                if (i + 1 < argc) {
                    args.config_file = argv[i + 1];
                    i++; // Skip the next argument since it's the config file path
                } else {
                    BONGOCAT_LOG_ERROR("--config option requires a file path");
                    return EXIT_FAILURE;
                }
            } else if (strcmp(argv[i], "--watch-config") == 0 || strcmp(argv[i], "-w") == 0) {
                args.watch_config = true;
            } else if (strcmp(argv[i], "--toggle") == 0 || strcmp(argv[i], "-t") == 0) {
                args.toggle_mode = true;
            } else if (strcmp(argv[i], "--output-name") == 0 || strcmp(argv[i], "-o") == 0) {
                if (i + 1 < argc) {
                    args.output_name = argv[i + 1];
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
}

// =============================================================================
// MAIN APPLICATION ENTRY POINT
// =============================================================================

int main(int argc, char *argv[]) {
    using namespace bongocat;

    // Initialize error system early
    bongocat::error_init(true); // Enable debug initially

    BONGOCAT_LOG_INFO("Starting Bongo Cat Overlay v%s", BONGOCAT_VERSION);

    // Parse command line arguments
    cli_args_t args{};
    if (cli_parse_arguments(argc, argv, args) != 0) {
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

    static main_context_t ctx;
    g_main_context = &ctx;

    // Load configuration
    ctx.overwrite_config_parameters = {
        .output_name = args.output_name,
    };
    auto [config, config_result] = config::load(args.config_file, ctx.overwrite_config_parameters);
    if (config_result != bongocat_error_t::BONGOCAT_SUCCESS) {
        BONGOCAT_LOG_ERROR("Failed to load configuration: %s", bongocat::error_string(config_result));
        return EXIT_FAILURE;
    }
    ctx.config = bongocat::move(config);
    bongocat::error_init(ctx.config.enable_debug);

    // set pid file, based on output_name
    char* pid_filename = nullptr;
    if (ctx.config.output_name && ctx.config.output_name[0] != '\0') {
        const int needed_size = snprintf(nullptr, 0, PID_FILE_WITH_SUFFIX_TEMPLATE, ctx.config.output_name) + 1;
        assert(needed_size >= 0);
        pid_filename = static_cast<char *>(::malloc(static_cast<size_t>(needed_size)));
        if (pid_filename != nullptr) {
            snprintf(pid_filename, static_cast<size_t>(needed_size), PID_FILE_WITH_SUFFIX_TEMPLATE, ctx.config.output_name);
        } else {
            BONGOCAT_LOG_ERROR("Failed to allocate PID filename");
            return EXIT_FAILURE;
        }
    } else {
        pid_filename = strdup(DEFAULT_PID_FILE);
    }

    // Handle toggle mode
    if (args.toggle_mode) {
        if (const int toggle_result = process_handle_toggle(pid_filename); toggle_result >= 0) {
            if (pid_filename) ::free(pid_filename);
            return toggle_result; // Either successfully toggled off or error
        }
        // toggle_result == -1 means continue with startup
    }

    // Create PID file to track this instance
    const platform::FileDescriptor pid_fd = process_create_pid_file(pid_filename);
    if (pid_fd._fd == -2) {
        BONGOCAT_LOG_ERROR("Another instance of bongocat is already running");
        if (pid_filename) ::free(pid_filename);
        return EXIT_FAILURE;
    } else if (pid_fd._fd < 0) {
        BONGOCAT_LOG_ERROR("Failed to create PID file");
        if (pid_filename) ::free(pid_filename);
        return EXIT_FAILURE;
    }
    BONGOCAT_LOG_INFO("PID file created: %s", pid_filename);

    // more randomness is needed to create better shm names, see create_shm
    const auto pid = getpid();
    srand(static_cast<unsigned>(time(nullptr)) ^ static_cast<unsigned>(pid)); // seed once, include pid for better randomness

    // Setup signal handlers
    ctx.signal_watch_path = args.config_file;
    bongocat_error_t signal_result = signal_setup_handlers(ctx);
    if (signal_result != bongocat_error_t::BONGOCAT_SUCCESS) {
        process_remove_pid_file(pid_filename);
        if (pid_filename) ::free(pid_filename);
        BONGOCAT_LOG_ERROR("Failed to setup signal handlers: %s", bongocat::error_string(signal_result));
        return EXIT_FAILURE;
    }
    BONGOCAT_LOG_INFO("Signal handler configure (fd=%i)", ctx.signal_fd._fd);
    
    // Initialize config watcher if requested
    if (args.watch_config && args.config_file) {
        start_config_watcher(ctx, args.config_file);
    } else {
        BONGOCAT_LOG_INFO("No config watcher, continuing without hot-reload");
    }
    
    // Initialize all system components
    bongocat_error_t result = system_initialize_components(ctx);
    if (result != bongocat_error_t::BONGOCAT_SUCCESS) {
        system_cleanup_and_exit(ctx, pid_filename, EXIT_FAILURE);
    }

    if (abs(ctx.config.cat_x_offset) > ctx.wayland.wayland_context._screen_width) {
        BONGOCAT_LOG_WARNING("cat_x_offset %d may position cat off-screen (screen width: %d)",
                            ctx.config.cat_x_offset, ctx.wayland.wayland_context._screen_width);
    }

    BONGOCAT_LOG_INFO("Bar dimensions: %dx%d", ctx.wayland.wayland_context._screen_width, ctx.config.overlay_height);

    BONGOCAT_LOG_INFO("Bongo Cat Overlay configured successfully");

    // trigger initial rendering
    platform::wayland::request_render(ctx.animation);
    // Main Wayland event loop with graceful shutdown
    result = run(ctx.wayland, ctx.running, ctx.signal_fd._fd, ctx.input, ctx.config, ctx.config_watcher, config_reload_callback);
    if (result != bongocat_error_t::BONGOCAT_SUCCESS) {
        BONGOCAT_LOG_ERROR("Wayland event loop error: %s", bongocat::error_string(result));
        system_cleanup_and_exit(ctx, pid_filename, EXIT_FAILURE);
    }
    
    BONGOCAT_LOG_INFO("Main loop exited, shutting down");
    system_cleanup_and_exit(ctx, pid_filename, EXIT_SUCCESS);

    // Never reached
    //return EXIT_SUCCESS;
}