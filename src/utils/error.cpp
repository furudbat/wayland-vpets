#include "utils/error.h"
#include <cstdarg>
#include <ctime>
#include <sys/time.h>
#include <cstdio>
#include <stdatomic.h>
#include <cstring>

static atomic_bool debug_enabled = true;

void bongocat_error_init(bool enable_debug) {
    atomic_store(&debug_enabled, enable_debug);
}

[[maybe_unused]] static void log_timestamp(FILE *stream) {
    timeval tv{};
    tm tm_info{};
    char timestamp[64] = {0};

    gettimeofday(&tv, nullptr);
    localtime_r(&tv.tv_sec, &tm_info); // Thread-safe version

    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", &tm_info);
    fprintf(stream, "[%s.%03ld] ", timestamp, tv.tv_usec / 1000);
}

#ifndef BONGOCAT_DISABLE_LOGGER


// Core log function using va_list
inline void log_vprintf(const char* name, const char* format, va_list args) {
    log_timestamp(stdout);
    fprintf(stdout, "%.*s: ", (int)strlen(name), name);
    vfprintf(stdout, format, args);
    fprintf(stdout, "\n");
    fflush(stdout);
}

// Convenience inline functions
void bongocat_log_error(const char* fmt, ...) {
    va_list args; va_start(args, fmt); log_vprintf("ERROR", fmt, args); va_end(args);
}

void bongocat_log_warning(const char* fmt, ...) {
    va_list args; va_start(args, fmt); log_vprintf("WARNING", fmt, args); va_end(args);
}

void bongocat_log_info(const char* fmt, ...) {
    va_list args; va_start(args, fmt); log_vprintf("INFO", fmt, args); va_end(args);
}

void bongocat_log_debug(const char* fmt, ...) {
    if (!debug_enabled.load()) return;
    va_list args; va_start(args, fmt); log_vprintf("DEBUG", fmt, args); va_end(args);
}

void bongocat_log_verbose(const char* fmt, ...) {
    if (!debug_enabled.load()) return;
    va_list args; va_start(args, fmt); log_vprintf("VERBOSE", fmt, args); va_end(args);
}

#endif

const char* bongocat_error_string(bongocat_error_t error) {
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
        default: return "Unknown error";
    }
}