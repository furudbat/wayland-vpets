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

#include "image_loader/load_images.h"

// =============================================================================
// GLOBAL STATE AND CONFIGURATION
// =============================================================================

namespace bongocat {
    static inline constexpr platform::time_ms_t WAIT_FOR_SHUTDOWN_MS = 5000;
    static inline constexpr platform::time_ms_t SLEEP_WAIT_FOR_SHUTDOWN_MS = 100;
    static_assert(SLEEP_WAIT_FOR_SHUTDOWN_MS > 0);

    static inline constexpr platform::time_ms_t WAIT_FOR_SHUTDOWN_ANIMATION_THREAD_MS = 5000;
    static inline constexpr platform::time_ms_t WAIT_FOR_SHUTDOWN_INPUT_THREAD_MS = 2000;
    static inline constexpr platform::time_ms_t WAIT_FOR_SHUTDOWN_CONFIG_WATCHER_THREAD_MS = 1000;
    inline static constexpr platform::time_ms_t COND_RELOAD_CONFIG_TIMEOUT_MS = 5000;

    inline static constexpr platform::time_ms_t WAIT_FOR_FLUSH_BEFORE_EXIT_MS = 100;

    struct main_context_t;
    void stop_threads(main_context_t& context);
    void cleanup(main_context_t& context);

    struct main_context_t {
        volatile sig_atomic_t running {0};
        platform::FileDescriptor signal_fd {-1};

        config::config_t config;
        config::load_config_overwrite_parameters_t overwrite_config_parameters;

        AllocatedMemory<config::config_watcher_t> config_watcher;
        AllocatedMemory<platform::input::input_context_t> input;   AllocatedMemory<animation::animation_session_t> animation;
        AllocatedMemory<platform::wayland::wayland_session_t> wayland;

        const char *signal_watch_path{nullptr};
        atomic_uint64_t config_generation{0};
        platform::CondVariable configs_reloaded_cond{};
        platform::Mutex sync_configs;

        char* pid_filename{nullptr};

        main_context_t() = default;
        ~main_context_t() {
            cleanup(*this);
        }
        main_context_t(const main_context_t&) = delete;
        main_context_t& operator=(const main_context_t&) = delete;
        main_context_t(main_context_t&& other) noexcept = delete;
        main_context_t& operator=(main_context_t&& other) noexcept = delete;
    };
    inline void stop_threads(main_context_t& context) {
        context.running = 0;
        // stop threads
        if (context.animation != nullptr) atomic_store(&context.animation->anim._animation_running, false);
        if (context.input != nullptr) atomic_store(&context.input->_capture_input_running, false);
        if (context.config_watcher != nullptr) atomic_store(&context.config_watcher->_running, false);

        // wait for threads
        if (context.animation != nullptr) platform::join_thread_with_timeout(context.animation->anim._anim_thread, WAIT_FOR_SHUTDOWN_ANIMATION_THREAD_MS);
        if (context.input != nullptr) platform::join_thread_with_timeout(context.input->_input_thread, WAIT_FOR_SHUTDOWN_INPUT_THREAD_MS);
        if (context.config_watcher != nullptr) platform::join_thread_with_timeout(context.config_watcher->_watcher_thread, WAIT_FOR_SHUTDOWN_CONFIG_WATCHER_THREAD_MS);

        // stop threads
        if (context.animation != nullptr) animation::stop(*context.animation);
        if (context.input != nullptr) platform::input::stop(*context.input);
        if (context.config_watcher != nullptr) config::stop_watcher(*context.config_watcher);

        context.config_generation = 0;
    }
    void cleanup(main_context_t& context) {
        stop_threads(context);

        // Cleanup Wayland
        if (context.wayland != nullptr) cleanup_wayland(*context.wayland);

        // remove references (avoid dangling pointers)
        if (context.wayland != nullptr) context.wayland->animation_trigger_context = nullptr;
        if (context.animation != nullptr) context.animation->_input = nullptr;

        // Cleanup systems
        if (context.animation != nullptr) cleanup(*context.animation);
        if (context.input != nullptr) cleanup(*context.input);
        if (context.signal_fd._fd >= 0) close_fd(context.signal_fd);
        if (context.config_watcher != nullptr) cleanup_watcher(*context.config_watcher);
        context.signal_watch_path = nullptr;

        release_allocated_memory(context.config_watcher);
        release_allocated_memory(context.input);
        release_allocated_memory(context.animation);
        release_allocated_memory(context.wayland);

        // Cleanup configuration
        cleanup(context.config);
        context.overwrite_config_parameters.output_name = nullptr;

        // cleanup signals handler
        platform::close_fd(context.signal_fd);

        if (context.pid_filename) ::free(context.pid_filename);
        context.pid_filename = nullptr;
    }

    inline main_context_t& get_main_context() {
        static main_context_t g_instance;
        return g_instance;
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
        int32_t randomize_index{-1};
        int32_t strict{-1};
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

    static pid_t process_get_running_pid(const char* program_name, const char* pid_filename) {
        assert(program_name);
        assert(pid_filename);
        platform::FileDescriptor fd = platform::FileDescriptor(::open(pid_filename, O_RDONLY));
        if (fd._fd < 0) {
            return -1; // No PID file exists
        }

        // Try to get a shared lock to read the file
        if (flock(fd._fd, LOCK_SH | LOCK_NB) < 0) {
            if (errno == EWOULDBLOCK) {
                // File is locked by another process, so it's running
                // We need to read the PID anyway, so let's try without lock
                fd = platform::FileDescriptor(::open(pid_filename, O_RDONLY));
                if (fd._fd < 0) return -1;
            } else {
                return -1;
            }
        }

        char pid_str[PID_STR_BUF] = {0};
        const ssize_t bytes_read = read(fd._fd, pid_str, sizeof(pid_str) - 1);
        platform::close_fd(fd);
        if (bytes_read <= 0) {
            return -1;
        }
        pid_str[bytes_read] = '\0';
        pid_str[strcspn(pid_str, "\r\n")] = '\0';
        for (char* p = pid_str; *p; ++p) {
            if (*p == '\n' || *p == '\r' || *p == ' ' || *p == '\t') {
                *p = '\0';
                break;
            }
        }


        char *endptr = nullptr;
        errno = 0; // Reset errno before call
        const auto pid = static_cast<pid_t>(strtol(pid_str, &endptr, 10));
        if (endptr == pid_str) {
            return -1; // no digits at all
        }
        if ((errno == ERANGE) || pid < 0) {
            BONGOCAT_LOG_ERROR("'%s' out of range for pid_t", pid_str);
            return -1;
        }

        char exe_path[PATH_MAX] = {0};
        snprintf(exe_path, sizeof(exe_path), "/proc/%d/exe", pid);
        char buf[PATH_MAX] = {0};
        ssize_t len = readlink(exe_path, buf, sizeof(buf) - 1);
        if (len > 0) {
            buf[len] = '\0';

            const char* exe_basename = strrchr(buf, '/');
            exe_basename = exe_basename ? exe_basename + 1 : buf;

            const char* prog_basename = strrchr(program_name, '/');
            prog_basename = prog_basename ? prog_basename + 1 : program_name;

            if (strcmp(exe_basename, prog_basename) != 0) {
                return -1;
            }
        }

        // Check if process is actually running
        if (kill(pid, 0) == 0) {
            return pid; // Process is running
        }

        return -1;
    }

    static int process_handle_toggle(const char* program_name, const char* pid_filename) {
        const pid_t running_pid = process_get_running_pid(program_name, pid_filename);
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

    static void config_reload_callback() {
        assert(get_main_context().input != nullptr);
        assert(get_main_context().animation != nullptr);
        assert(get_main_context().signal_watch_path != nullptr);
        BONGOCAT_LOG_INFO("Reloading configuration from: %s (%s)", get_main_context().signal_watch_path, (get_main_context().config_watcher) ? get_main_context().config_watcher->config_path : "");
        assert(get_main_context().config_watcher == nullptr || strcmp(get_main_context().config_watcher->config_path, get_main_context().signal_watch_path) == 0);

        // Create a temporary config to test loading
        auto [new_config, error] = config::load(get_main_context().signal_watch_path, get_main_context().overwrite_config_parameters);
        if (error != bongocat_error_t::BONGOCAT_SUCCESS) {
            BONGOCAT_LOG_ERROR("Failed to reload config: %s", bongocat::error_string(error));
            BONGOCAT_LOG_INFO("Keeping current configuration");
            return;
        }

        // If successful, update the global config
        bool devices_changed = false;
        {
            platform::LockGuard guard (get_main_context().sync_configs);
            uint64_t new_gen{atomic_load(&get_main_context().config_generation)};
            config::config_t old_config = get_main_context().config;
            // keep old animation, don't randomize
            if (old_config.randomize_index && new_config.randomize_index &&
                old_config.animation_sprite_sheet_layout == new_config.animation_sprite_sheet_layout &&
                old_config.animation_dm_set == new_config.animation_dm_set) {
                new_config.keep_old_animation_index = 1;
            }
            // If successful, check if input devices changed before updating config
            devices_changed = config_devices_changed(old_config, new_config);
            get_main_context().config = bongocat::move(new_config);
            /// @NOTE: don't use new_config after move
            new_config = {};
            // Initialize error system with debug setting
            bongocat::error_init(get_main_context().config.enable_debug);

            // Increment generation atomically
            new_gen = atomic_fetch_add(&get_main_context().config_generation, 1) + 1;

            // Update the running systems with new config
            platform::input::trigger_update_config(*get_main_context().input, get_main_context().config, new_gen);
            animation::trigger_update_config(*get_main_context().animation, get_main_context().config, new_gen);
            update_config(get_main_context().wayland->wayland_context, get_main_context().config, *get_main_context().animation);

            /// @TODO: use pthread barrier
            // Wait for both workers to catch up
            get_main_context().input->config_updated.timedwait([&] {
                return !atomic_load(&get_main_context().input->_capture_input_running) || get_main_context().input->config_seen_generation >= new_gen;
            }, COND_RELOAD_CONFIG_TIMEOUT_MS);
            get_main_context().animation->anim.config_updated.timedwait([&] {
                return !atomic_load(&get_main_context().animation->anim._animation_running) || get_main_context().animation->anim.config_seen_generation >= new_gen;
            }, COND_RELOAD_CONFIG_TIMEOUT_MS);

            get_main_context().config.keep_old_animation_index = 0;
            // fallback when cond hits timeout (sync config generations)
            if (atomic_load(&get_main_context().input->_capture_input_running)) {
                atomic_store(&get_main_context().input->config_seen_generation, new_gen);
            }
            if (atomic_load(&get_main_context().animation->anim._animation_running)) {
                atomic_store(&get_main_context().animation->anim.config_seen_generation, new_gen);
            }
            atomic_store(&get_main_context().config_generation, new_gen);
        }
        // Tell workers they can continue
        get_main_context().configs_reloaded_cond.notify_all();

        BONGOCAT_LOG_INFO("Configuration reloaded successfully!");
        BONGOCAT_LOG_INFO("New screen dimensions: %dx%d", get_main_context().wayland->wayland_context._screen_width, get_main_context().wayland->wayland_context._bar_height);

        assert(get_main_context().animation != nullptr);
        animation::trigger(*get_main_context().animation);

        // Check if input devices changed and restart monitoring if needed
        if (devices_changed) {
            BONGOCAT_LOG_INFO("Input devices changed, restarting input monitoring");
            const bongocat_error_t input_result = platform::input::restart(*get_main_context().input, *get_main_context().animation, get_main_context().config, get_main_context().configs_reloaded_cond, get_main_context().config_generation);
            if (input_result != bongocat_error_t::BONGOCAT_SUCCESS) {
                BONGOCAT_LOG_ERROR("Failed to restart input monitoring: %s", bongocat::error_string(input_result));
            } else {
                BONGOCAT_LOG_INFO("Input monitoring restarted successfully");
            }
        }
    }

    static bongocat_error_t start_config_watcher(main_context_t& ctx, const char *config_file) {
        auto [config_watcher, error] = config::create_watcher(config_file);
        if (error == bongocat_error_t::BONGOCAT_SUCCESS) {
            ctx.config_watcher = bongocat::move(config_watcher);
            config::start_watcher(*ctx.config_watcher);
            BONGOCAT_LOG_INFO("Config file watching enabled for: %s", config_file);
        } else {
            BONGOCAT_LOG_WARNING("Failed to initialize config watcher, continuing without hot-reload");
        }
        return error;
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
        sigaddset(&mask, SIGUSR1);
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
        {
            auto [input, input_error] = platform::input::create(ctx.config);
            if (input_error != bongocat_error_t::BONGOCAT_SUCCESS) {
                BONGOCAT_LOG_ERROR("Failed to initialize animation system: %s", bongocat::error_string(input_error));
                return input_error;
            }
            ctx.input = bongocat::move(input);
        }

        // Initialize animation system
        {
            animation::init_image_loader();
            auto [animation, animation_error] = animation::create(ctx.config);
            if (animation_error != bongocat_error_t::BONGOCAT_SUCCESS) {
                BONGOCAT_LOG_ERROR("Failed to initialize animation system: %s", bongocat::error_string(animation_error));
                return animation_error;
            }
            ctx.animation = bongocat::move(animation);
        }

        // Initialize Wayland
        {
            assert(ctx.animation != nullptr);
            /// @NOTE: animation needed only for reference
            auto [wayland, wayland_error] = platform::wayland::create(*ctx.animation, ctx.config);
            if (wayland_error != bongocat_error_t::BONGOCAT_SUCCESS) {
                BONGOCAT_LOG_ERROR("Failed to initialize Wayland: %s", bongocat::error_string(wayland_error));
                return wayland_error;
            }
            ctx.wayland = bongocat::move(wayland);
        }

        // Setup wayland
        assert(ctx.input != nullptr);
        assert(ctx.animation != nullptr);
        bongocat_error_t setup_wayland_result = setup(*ctx.wayland, *ctx.animation);
        if (setup_wayland_result != bongocat_error_t::BONGOCAT_SUCCESS) {
            BONGOCAT_LOG_ERROR("Failed to setup wayland: %s", bongocat::error_string(setup_wayland_result));
            return setup_wayland_result;
        }

        // Start animation thread
        bongocat_error_t start_animation_result = animation::start(*ctx.animation, *ctx.input, ctx.config, get_main_context().configs_reloaded_cond, get_main_context().config_generation);
        if (start_animation_result != bongocat_error_t::BONGOCAT_SUCCESS) {
            BONGOCAT_LOG_ERROR("Failed to start animation thread: %s", bongocat::error_string(start_animation_result));
            return start_animation_result;
        }

        // Start input monitoring
        bongocat_error_t start_input_result = platform::input::start(*ctx.input, *ctx.animation, ctx.config, get_main_context().configs_reloaded_cond, get_main_context().config_generation);
        if (start_input_result != bongocat_error_t::BONGOCAT_SUCCESS) {
            BONGOCAT_LOG_ERROR("Failed to start input monitoring: %s", bongocat::error_string(start_input_result));
            return start_input_result;
        }

        return bongocat_error_t::BONGOCAT_SUCCESS;
    }

    [[ noreturn ]] static void system_cleanup_and_exit(main_context_t& ctx, int exit_code) {
        BONGOCAT_LOG_INFO("Stop threads...");
        ctx.running = 0;
        stop_threads(ctx);

        BONGOCAT_LOG_INFO("Performing cleanup...");
        process_remove_pid_file(ctx.pid_filename);
        // clean up context before global cleanup (log mutex, etc.)
        cleanup(ctx);

        BONGOCAT_LOG_INFO("Cleanup complete, exiting with code %d", exit_code);
        usleep(WAIT_FOR_FLUSH_BEFORE_EXIT_MS*1000);
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
        printf("      --random          Enable random animation_index, at start (overwrite random_index from config)\n");
        printf("      --strict          Enable strict mode, only start up with a valid config and valid parameter\n");
        printf("\nConfiguration is loaded from bongocat.conf in the current directory.\n");
    }

    static void cli_show_version() {
        printf("Bongo Cat Overlay v%s\n", BONGOCAT_VERSION);
        printf("Built with fast optimizations\n");
    }

    static created_result_t<cli_args_t> cli_parse_arguments(int argc, char *argv[]) {
        cli_args_t args{};

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
                    return bongocat_error_t::BONGOCAT_ERROR_INVALID_PARAM;
                }
            } else if (strcmp(argv[i], "--watch-config") == 0 || strcmp(argv[i], "-w") == 0) {
                args.watch_config = true;
            } else if (strcmp(argv[i], "--toggle") == 0 || strcmp(argv[i], "-t") == 0) {
                args.toggle_mode = true;
            } else if (strcmp(argv[i], "--random") == 0) {
                args.randomize_index = 1;
            } else if (strcmp(argv[i], "--strict") == 0) {
                args.strict = 1;
            } else if (strcmp(argv[i], "--output-name") == 0 || strcmp(argv[i], "-o") == 0) {
                if (i + 1 < argc) {
                    args.output_name = argv[i + 1];
                    i++; // Skip the next argument since it's the output name
                } else {
                    BONGOCAT_LOG_ERROR("--output-name option requires a output name");
                    return bongocat_error_t::BONGOCAT_ERROR_INVALID_PARAM;
                }
            } else {
                BONGOCAT_LOG_WARNING("Unknown argument: %s", argv[i]);
            }
        }

        return args;
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
    const auto [args, args_result] = cli_parse_arguments(argc, argv);
    if (args_result != bongocat_error_t::BONGOCAT_SUCCESS) {
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

    main_context_t& ctx = get_main_context();

    // Load configuration
    ctx.overwrite_config_parameters = {
        .output_name = args.output_name,
        .randomize_index = args.randomize_index,
        .strict = args.strict,
    };
    auto [config, config_error] = config::load(args.config_file, ctx.overwrite_config_parameters);
    if (config_error != bongocat_error_t::BONGOCAT_SUCCESS) {
        BONGOCAT_LOG_ERROR("Failed to load configuration: %s", bongocat::error_string(config_error));
        return EXIT_FAILURE;
    }
    ctx.config = bongocat::move(config);
    bongocat::error_init(ctx.config.enable_debug);

    // set pid file, based on output_name
    if (ctx.config.output_name && ctx.config.output_name[0] != '\0') {
        const int needed_size = snprintf(nullptr, 0, PID_FILE_WITH_SUFFIX_TEMPLATE, ctx.config.output_name) + 1;
        assert(needed_size >= 0);
        ctx.pid_filename = static_cast<char *>(::malloc(static_cast<size_t>(needed_size)));
        if (ctx.pid_filename != nullptr) {
            snprintf(ctx.pid_filename, static_cast<size_t>(needed_size), PID_FILE_WITH_SUFFIX_TEMPLATE, ctx.config.output_name);
        } else {
            BONGOCAT_LOG_ERROR("Failed to allocate PID filename");
            return EXIT_FAILURE;
        }
    } else {
        ctx.pid_filename = strdup(DEFAULT_PID_FILE);
    }

    // Handle toggle mode
    if (args.toggle_mode) {
        BONGOCAT_LOG_INFO("Toggle... (pid=%s)", ctx.pid_filename);
        if (const int toggle_result = process_handle_toggle(argv[0], ctx.pid_filename); toggle_result >= 0) {
            return toggle_result; // Either successfully toggled off or error
        }
        // toggle_result == -1 means continue with startup
    }

    // Create PID file to track this instance
    const platform::FileDescriptor pid_fd = process_create_pid_file(ctx.pid_filename);
    if (pid_fd._fd == -2) {
        BONGOCAT_LOG_ERROR("Another instance of bongocat is already running");
        return EXIT_FAILURE;
    } else if (pid_fd._fd < 0) {
        BONGOCAT_LOG_ERROR("Failed to create PID file");
        return EXIT_FAILURE;
    }
    BONGOCAT_LOG_INFO("PID file created: %s", ctx.pid_filename);

    // more randomness is needed to create better shm names, see create_shm
    const auto pid = getpid();
    // seed once, include pid for better randomness
    srand(static_cast<unsigned>(time(nullptr)) ^ static_cast<unsigned>(pid));

    BONGOCAT_LOG_INFO("bongocat PID: %d", pid);

    // Setup signal handlers
    ctx.signal_watch_path = args.config_file;
    bongocat_error_t signal_result = signal_setup_handlers(ctx);
    if (signal_result != bongocat_error_t::BONGOCAT_SUCCESS) {
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
        system_cleanup_and_exit(ctx, EXIT_FAILURE);
    }

    assert(ctx.input != nullptr);
    assert(ctx.animation != nullptr);
    assert(ctx.wayland != nullptr);

    if (abs(ctx.config.cat_x_offset) > ctx.wayland->wayland_context._screen_width) {
        BONGOCAT_LOG_WARNING("cat_x_offset %d may position cat off-screen (screen width: %d)",
                            ctx.config.cat_x_offset, ctx.wayland->wayland_context._screen_width);
    }

    BONGOCAT_LOG_INFO("Bar dimensions: %dx%d", ctx.wayland->wayland_context._screen_width, ctx.config.overlay_height);

    BONGOCAT_LOG_INFO("Bongo Cat Overlay configured successfully");

    // trigger initial rendering
    platform::wayland::request_render(*ctx.animation);
    // Main Wayland event loop with graceful shutdown
    assert(ctx.wayland != nullptr);
    assert(ctx.input != nullptr);
    /// @NOTE: config_watcher os optional
    result = run(*ctx.wayland, ctx.running, ctx.signal_fd._fd, *ctx.input, ctx.config, ctx.config_watcher.ptr, config_reload_callback);
    if (result != bongocat_error_t::BONGOCAT_SUCCESS) {
        BONGOCAT_LOG_ERROR("Wayland event loop error: %s", bongocat::error_string(result));
        system_cleanup_and_exit(ctx, EXIT_FAILURE);
    }
    
    BONGOCAT_LOG_INFO("Main loop exited, shutting down");
    system_cleanup_and_exit(ctx, EXIT_SUCCESS);

    // Never reached
    //return EXIT_SUCCESS;
}