#ifndef BONGOCAT_ERROR_H
#define BONGOCAT_ERROR_H

#include <cstdio>
#include <cstdlib>
#include <cerrno>
#include <cstring>
#include <cstdint>

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
    BONGOCAT_ERROR_INVALID_PARAM
};

// Error handling macros
#define BONGOCAT_CHECK_NULL(ptr, error_code) \
    do { \
        if ((ptr) == NULL) { \
            BONGOCAT_LOG_ERROR("NULL pointer: %s at %s:%d", #ptr, __FILE__, __LINE__); \
            return (error_code); \
        } \
    } while(0)

#define BONGOCAT_CHECK_ERROR(condition, error_code, message) \
    do { \
        if (condition) { \
            BONGOCAT_LOG_ERROR("%s at %s:%d", message, __FILE__, __LINE__); \
            return (error_code); \
        } \
    } while(0)

#ifndef BONGOCAT_DISABLE_LOGGER
// Logging functions
void bongocat_log_error(const char *format, ...);
void bongocat_log_warning(const char *format, ...);
void bongocat_log_info(const char *format, ...);
void bongocat_log_debug(const char *format, ...);
void bongocat_log_verbose(const char *format, ...);

#endif

// Error handling initialization
void bongocat_error_init(int enable_debug);
const char* bongocat_error_string(bongocat_error_t error);

// 0 = Error
// 1 = Warning
// 2 = Info
// 3 = Debug
// 3 = Verbose
#ifndef BONGOCAT_LOG_LEVEL
#define BONGOCAT_LOG_LEVEL 3
#endif

#if !defined(BONGOCAT_DISABLE_LOGGER) && BONGOCAT_LOG_LEVEL >= 0
#define BONGOCAT_LOG_ERROR(format, ...) bongocat_log_error(format, ##__VA_ARGS__)
#else
#define BONGOCAT_LOG_ERROR(format, ...) ((void)0)
#endif

#if !defined(BONGOCAT_DISABLE_LOGGER) && BONGOCAT_LOG_LEVEL >= 1
#define BONGOCAT_LOG_WARNING(format, ...) bongocat_log_warning(format, ##__VA_ARGS__)
#else
#define BONGOCAT_LOG_WARNING(format, ...) ((void)0)
#endif

#if !defined(BONGOCAT_DISABLE_LOGGER) && BONGOCAT_LOG_LEVEL >= 2
#define BONGOCAT_LOG_INFO(format, ...) bongocat_log_info(format, ##__VA_ARGS__)
#else
#define BONGOCAT_LOG_INFO(format, ...) ((void)0)
#endif

#if !defined(BONGOCAT_DISABLE_LOGGER) && BONGOCAT_LOG_LEVEL >= 3
#define BONGOCAT_LOG_DEBUG(format, ...) bongocat_log_debug(format, ##__VA_ARGS__)
#else
#define BONGOCAT_LOG_DEBUG(format, ...) ((void)0)
#endif

#if !defined(BONGOCAT_DISABLE_LOGGER) && BONGOCAT_LOG_LEVEL >= 4
#define BONGOCAT_LOG_VERBOSE(format, ...) bongocat_log_verbose(format, ##__VA_ARGS__)
#else
#define BONGOCAT_LOG_VERBOSE(format, ...) ((void)0)
#endif

/// @DEPRECATED: use cpp [[maybe_unused]] attribute
#define UNUSED(x) (void)(x)

#endif // ERROR_H