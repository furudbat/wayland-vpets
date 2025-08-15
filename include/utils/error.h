#ifndef BONGOCAT_ERROR_H
#define BONGOCAT_ERROR_H

#include <cstdio>
#include <cerrno>
#include <cstring>
#include <cstdint>

namespace bongocat {
    // Error codes
    enum class bongocat_error_t : uint8_t {
        BONGOCAT_SUCCESS = 0,
        BONGOCAT_ERROR_MEMORY,
        BONGOCAT_ERROR_FILE_IO,
        BONGOCAT_ERROR_WAYLAND,
        BONGOCAT_ERROR_CONFIG,
        BONGOCAT_ERROR_INPUT,
        BONGOCAT_ERROR_ANIMATION,
        BONGOCAT_ERROR_THREAD,
        BONGOCAT_ERROR_INVALID_PARAM,
    };

    // Error handling macros
#define BONGOCAT_CHECK_NULL(ptr, error_code) \
do { \
if ((ptr) == nullptr) { \
BONGOCAT_LOG_ERROR("NULL pointer: %s at %s:%d", #ptr, __FILE__, __LINE__); \
return (error_code); \
} \
} while(false)

#define BONGOCAT_CHECK_ERROR(condition, error_code, message) \
do { \
if (condition) { \
BONGOCAT_LOG_ERROR("%s at %s:%d", message, __FILE__, __LINE__); \
return (error_code); \
} \
} while(false)

#ifndef BONGOCAT_DISABLE_LOGGER
    // Logging functions
    void log_error(const char *format, ...);
    void log_warning(const char *format, ...);
    void log_info(const char *format, ...);
    void log_debug(const char *format, ...);
    void log_verbose(const char *format, ...);

#endif

    // Error handling initialization
    void error_init(bool enable_debug);
    const char* error_string(bongocat_error_t error);

    // 1 = Error
    // 2 = Warning
    // 3 = Info
    // 4 = Debug
    // 5 = Verbose
#ifndef BONGOCAT_LOG_LEVEL
#define BONGOCAT_LOG_LEVEL 4
#endif

#if !defined(BONGOCAT_DISABLE_LOGGER) && BONGOCAT_LOG_LEVEL >= 1
#define BONGOCAT_LOG_ERROR(format, ...) ::bongocat::log_error(format __VA_OPT__(,) __VA_ARGS__)
#else
#define BONGOCAT_LOG_ERROR(format, ...) ((void)0)
#endif

#if !defined(BONGOCAT_DISABLE_LOGGER) && BONGOCAT_LOG_LEVEL >= 2
#define BONGOCAT_LOG_WARNING(format, ...) ::bongocat::log_warning(format __VA_OPT__(,) __VA_ARGS__)
#else
#define BONGOCAT_LOG_WARNING(format, ...) ((void)0)
#endif

#if !defined(BONGOCAT_DISABLE_LOGGER) && BONGOCAT_LOG_LEVEL >= 3
#define BONGOCAT_LOG_INFO(format, ...) ::bongocat::log_info(format __VA_OPT__(,) __VA_ARGS__)
#else
#define BONGOCAT_LOG_INFO(format, ...) ((void)0)
#endif

#if !defined(BONGOCAT_DISABLE_LOGGER) && BONGOCAT_LOG_LEVEL >= 4
#define BONGOCAT_LOG_DEBUG(format, ...) ::bongocat::log_debug(format __VA_OPT__(,) __VA_ARGS__)
#else
#define BONGOCAT_LOG_DEBUG(format, ...) ((void)0)
#endif

#if !defined(BONGOCAT_DISABLE_LOGGER) && BONGOCAT_LOG_LEVEL >= 5
#define BONGOCAT_LOG_VERBOSE(format, ...) ::bongocat::log_verbose(format __VA_OPT__(,) __VA_ARGS__)
#else
#define BONGOCAT_LOG_VERBOSE(format, ...) ((void)0)
#endif
}

#endif // ERROR_H