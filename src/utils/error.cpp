#include "utils/error.h"
#include "utils/system_memory.h"
#include <cassert>
#include <cstdarg>
#include <ctime>
#include <sys/time.h>
#include <cstdio>
#include <stdatomic.h>
#include <cstring>

namespace bongocat {
    namespace details {
        inline atomic_bool& get_debug_enabled() {
            static atomic_bool g_instance = true;
            return g_instance;
        }
    }

    void error_init(bool enable_debug) {
        atomic_store(&details::get_debug_enabled(), enable_debug);
    }

#if !defined(BONGOCAT_DISABLE_LOGGER) || defined(BONGOCAT_ENABLE_LOGGER)
    namespace details {
        inline platform::Mutex& get_log_mutex() {
            static platform::Mutex g_instance;
            return g_instance;
        }

        inline void log_timestamp(FILE *stream) {
            timeval tv{};
            tm tm_info{};
            char timestamp[64] = {0};

            gettimeofday(&tv, nullptr);
            localtime_r(&tv.tv_sec, &tm_info); // Thread-safe version

            strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", &tm_info);
            fprintf(stream, "[%s.%03ld] ", timestamp, tv.tv_usec / 1000);
        }

        // Core log function using va_list
        inline void log_vprintf(const char* name, const char* format, va_list args) {
            const int name_len = static_cast<int>(strlen(name));
            assert(name_len > 0);

            platform::LockGuard guard (get_log_mutex());
            log_timestamp(stdout);
            fprintf(stdout, "%.*s: ", name_len, name);
            vfprintf(stdout, format, args);
            fprintf(stdout, "\n");
            fflush(stdout);
        }

        // Convenience inline functions
        void log_error(const char* fmt, ...) {
            va_list args; va_start(args, fmt); log_vprintf("ERROR", fmt, args); va_end(args);
        }

        void log_warning(const char* fmt, ...) {
            va_list args; va_start(args, fmt); log_vprintf("WARNING", fmt, args); va_end(args);
        }

        void log_info(const char* fmt, ...) {
            va_list args; va_start(args, fmt); log_vprintf("INFO", fmt, args); va_end(args);
        }

        void log_debug(const char* fmt, ...) {
            if (!atomic_load(&get_debug_enabled())) return;
            va_list args; va_start(args, fmt); log_vprintf("DEBUG", fmt, args); va_end(args);
        }

        void log_verbose(const char* fmt, ...) {
            if (!atomic_load(&get_debug_enabled())) return;
            va_list args; va_start(args, fmt); log_vprintf("VERBOSE", fmt, args); va_end(args);
        }
    }
#endif

    const char* error_string(bongocat_error_t error) {
        switch (error) {
            case bongocat_error_t::BONGOCAT_SUCCESS: return "Success";
            case bongocat_error_t::BONGOCAT_ERROR_MEMORY: return "Memory allocation error";
            case bongocat_error_t::BONGOCAT_ERROR_FILE_IO: return "File I/O error";
            case bongocat_error_t::BONGOCAT_ERROR_WAYLAND: return "Wayland error";
            case bongocat_error_t::BONGOCAT_ERROR_CONFIG: return "Configuration error";
            case bongocat_error_t::BONGOCAT_ERROR_INPUT: return "Input error";
            case bongocat_error_t::BONGOCAT_ERROR_ANIMATION: return "Animation error";
            case bongocat_error_t::BONGOCAT_ERROR_THREAD: return "Thread error";
            case bongocat_error_t::BONGOCAT_ERROR_INVALID_PARAM: return "Invalid parameter";
            case bongocat_error_t::BONGOCAT_ERROR_IMAGE: return "Load image error";
            default: return "Unknown error";
        }
    }
}
