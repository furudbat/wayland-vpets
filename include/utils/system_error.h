#ifndef BONGOCAT_SYSTEM_ERROR_H
#define BONGOCAT_SYSTEM_ERROR_H

#include "error.h"
#include "memory.h"

#include <cerrno>
#include <cstdint>
#include <cstring>

namespace bongocat {

inline static constexpr size_t STRERROR_BUFLEN = 256;

inline AllocatedString get_strerror(int errnum) {
  auto ret = make_allocated_string(STRERROR_BUFLEN);

  if (ret.ptr) {
    assert(ret.capacity() >= 2);
#if defined(__GLIBC__) && defined(_GNU_SOURCE)
    // GNU version: returns char*
    char *msg = strerror_r(errnum, ret.ptr, ret.capacity());
    if (msg != ret.ptr) {
      strncpy(ret.ptr, msg, ret.capacity() - 1);
      ret.ptr[ret.capacity() - 1] = '\0';
    }
#else
    // POSIX version: returns int
    if (strerror_r(errnum, ret.ptr, ret.capacity()) != BONGOCAT_NULLPTR) {
      snprintf(ret.ptr, ret.capacity(), "Unknown error %d", errnum);
    }
#endif
  }

  return ret;
}

inline int check_errno([[maybe_unused]] const char *fd_name) {
  const int err = errno;
  // supress compiler warning
#if EAGAIN == EWOULDBLOCK
  if (err != EAGAIN && err != -1) {
    auto errstr = get_strerror(err);
    BONGOCAT_LOG_ERROR("Error reading %s: %s", fd_name, errstr.c_str());
  }
#else
  if (err != EAGAIN && err != EWOULDBLOCK && err != -1) {
    auto errstr = get_strerror(err);
    BONGOCAT_LOG_ERROR("Error reading %s: %s", fd_name, errstr.c_str());
  }
#endif
  return err;
}

#if (!defined(BONGOCAT_DISABLE_LOGGER) || defined(BONGOCAT_ENABLE_LOGGER)) && BONGOCAT_LOG_LEVEL >= 1
#  define BONGOCAT_LOG_ERROR_STRERROR_FIRST(format, ...)                              \
    do {                                                                              \
      auto _err = ::bongocat::get_strerror(errnum);                                   \
      ::bongocat::details::log_error(format, _err.c_str() __VA_OPT__(, ) __VA_ARGS__) \
    } while (0)
#  define BONGOCAT_LOG_ERROR_STRERROR_LAST(format, ...)                                              \
    do {                                                                                             \
      auto _err = ::bongocat::get_strerror(errnum);                                                  \
      ::bongocat::details::log_error(format, __VA_OPT__(, ) __VA_ARGS__ __VA_OPT__(, ) _err.c_str()) \
    } while (0)
#else
#  define BONGOCAT_LOG_ERROR_STRERROR_FIRST(format, ...)
#  define BONGOCAT_LOG_ERROR_STRERROR_LAST(format, ...)
#endif

}  // namespace bongocat

#endif  // ERROR_H