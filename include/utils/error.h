#ifndef BONGOCAT_ERROR_H
#define BONGOCAT_ERROR_H

#include <cerrno>
#include <cstdint>
#include <cstring>

// =============================================================================
// C23 MODERN FEATURES
// =============================================================================

// Nodiscard attribute for functions that return values that must be used
#ifdef __cplusplus
#  define BONGOCAT_NODISCARD [[nodiscard]]
#else
#  if __STDC_VERSION__ >= 202311L
#    define BONGOCAT_NODISCARD [[nodiscard]]
#  else
#    define BONGOCAT_NODISCARD __attribute__((warn_unused_result))
#  endif
#endif

#ifdef __cplusplus
#  define BONGOCAT_NULLPTR nullptr
#else
// Null pointer (C23 nullptr or fallback)
#  if __STDC_VERSION__ >= 202311L
#    define BONGOCAT_NULLPTR nullptr
#  else
#    define BONGOCAT_NULLPTR NULL
#  endif
#endif

// Unreachable code hint for optimizer
#if __STDC_VERSION__ >= 202311L
#  define BONGOCAT_UNREACHABLE() unreachable()
#else
#  define BONGOCAT_UNREACHABLE() __builtin_unreachable()
#endif

namespace bongocat {

// =============================================================================
// ERROR CODES
// =============================================================================

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
  BONGOCAT_ERROR_IMAGE,
};

// =============================================================================
// GUARD CLAUSE MACROS
// =============================================================================

// Guard clause for null pointer - returns early with error
#define BONGOCAT_CHECK_NULL(ptr, error_code)                                     \
  do {                                                                           \
    if ((ptr) == BONGOCAT_NULLPTR) {                                             \
      BONGOCAT_LOG_ERROR("NULL pointer: %s at %s:%d", #ptr, __FILE__, __LINE__); \
      return (error_code);                                                       \
    }                                                                            \
  } while (0)

// Guard clause for error conditions - returns early with error
#define BONGOCAT_CHECK_ERROR(condition, error_code, message)          \
  do {                                                                \
    if (condition) {                                                  \
      BONGOCAT_LOG_ERROR("%s at %s:%d", message, __FILE__, __LINE__); \
      return (error_code);                                            \
    }                                                                 \
  } while (0)

// Guard clause for boolean conditions - returns early with value
#define BONGOCAT_GUARD(condition, return_value) \
  do {                                          \
    if (condition) {                            \
      return (return_value);                    \
    }                                           \
  } while (0)

// =============================================================================
// LOGGING FUNCTIONS
// =============================================================================

#if !defined(BONGOCAT_DISABLE_LOGGER) || defined(BONGOCAT_ENABLE_LOGGER)
namespace details {
  // Logging functions
  void log_error(const char *format, ...);
  void log_warning(const char *format, ...);
  void log_info(const char *format, ...);
  void log_debug(const char *format, ...);
  void log_verbose(const char *format, ...);
}  // namespace details
#endif

// =============================================================================
// ERROR HANDLING
// =============================================================================

// Error handling initialization
void error_init(bool enable_debug);
BONGOCAT_NODISCARD const char *error_string(bongocat_error_t error);

// 1 = Error
// 2 = Warning
// 3 = Info
// 4 = Debug
// 5 = Verbose
#ifndef BONGOCAT_LOG_LEVEL
#  define BONGOCAT_LOG_LEVEL 3
#endif
namespace features {
#if defined(BONGOCAT_LOG_LEVEL)
  inline static constexpr int LogLevel = BONGOCAT_LOG_LEVEL;
#endif
}  // namespace features

#if (!defined(BONGOCAT_DISABLE_LOGGER) || defined(BONGOCAT_ENABLE_LOGGER)) && BONGOCAT_LOG_LEVEL >= 1
#  define BONGOCAT_LOG_ERROR(format, ...) ::bongocat::details::log_error(format __VA_OPT__(, ) __VA_ARGS__)
#else
#  define BONGOCAT_LOG_ERROR(format, ...)
#endif

#if (!defined(BONGOCAT_DISABLE_LOGGER) || defined(BONGOCAT_ENABLE_LOGGER)) && BONGOCAT_LOG_LEVEL >= 2
#  define BONGOCAT_LOG_WARNING(format, ...) ::bongocat::details::log_warning(format __VA_OPT__(, ) __VA_ARGS__)
#else
#  define BONGOCAT_LOG_WARNING(format, ...)
#endif

#if (!defined(BONGOCAT_DISABLE_LOGGER) || defined(BONGOCAT_ENABLE_LOGGER)) && BONGOCAT_LOG_LEVEL >= 3
#  define BONGOCAT_LOG_INFO(format, ...) ::bongocat::details::log_info(format __VA_OPT__(, ) __VA_ARGS__)
#else
#  define BONGOCAT_LOG_INFO(format, ...)
#endif

#if (!defined(BONGOCAT_DISABLE_LOGGER) || defined(BONGOCAT_ENABLE_LOGGER)) && BONGOCAT_LOG_LEVEL >= 4
#  define BONGOCAT_LOG_DEBUG(format, ...) ::bongocat::details::log_debug(format __VA_OPT__(, ) __VA_ARGS__)
#else
#  define BONGOCAT_LOG_DEBUG(format, ...)
#endif

#if (!defined(BONGOCAT_DISABLE_LOGGER) || defined(BONGOCAT_ENABLE_LOGGER)) && BONGOCAT_LOG_LEVEL >= 5
#  define BONGOCAT_LOG_VERBOSE(format, ...) ::bongocat::details::log_verbose(format __VA_OPT__(, ) __VA_ARGS__)
#else
#  define BONGOCAT_LOG_VERBOSE(format, ...)
#endif

inline int check_errno([[maybe_unused]] const char *fd_name) {
  const int err = errno;
  // supress compiler warning
#if EAGAIN == EWOULDBLOCK
  if (err != EAGAIN && err != -1) {
    BONGOCAT_LOG_ERROR("Error reading %s: %s", fd_name, strerror(err));
  }
#else
  if (err != EAGAIN && err != EWOULDBLOCK && err != -1) {
    BONGOCAT_LOG_ERROR("Error reading %s: %s", fd_name, strerror(err));
  }
#endif
  return err;
}
}  // namespace bongocat

#endif  // ERROR_H