#include "utils/error.h"
#include <cstdarg>
#include <ctime>
#include <sys/time.h>
#include <cstdio>

static int debug_enabled = 1;

void bongocat_error_init(int enable_debug) {
    debug_enabled = enable_debug;
}

static void log_timestamp(FILE *stream) {
    timeval tv{};
    tm tm_info{};
    char timestamp[64] = {0};

    gettimeofday(&tv, NULL);
    localtime_r(&tv.tv_sec, &tm_info); // Thread-safe version

    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", &tm_info);
    fprintf(stream, "[%s.%03ld] ", timestamp, tv.tv_usec / 1000);
}

#ifndef BONGOCAT_DISABLE_LOGGER

#define bongocat_log_x(format, name) \
    va_list args; \
    log_timestamp(stdout); \
    fprintf(stdout, name ": "); \
    va_start(args, format); \
    vfprintf(stdout, format, args); \
    va_end(args); \
    fprintf(stdout, "\n"); \
    fflush(stdout);

void bongocat_log_error(const char *format, ...) {
    bongocat_log_x(format, "ERROR")
}

void bongocat_log_warning(const char *format, ...) {
    bongocat_log_x(format, "WARNING")
}

void bongocat_log_info(const char *format, ...) {
    bongocat_log_x(format, "INFO")
}

void bongocat_log_debug(const char *format, ...) {
    if (!debug_enabled) return;
    
    bongocat_log_x(format, "DEBUG")
}
void bongocat_log_verbose(const char *format, ...) {
    if (!debug_enabled) return;

    bongocat_log_x(format, "VERBOSE")
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