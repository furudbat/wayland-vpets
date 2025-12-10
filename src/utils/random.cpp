#include "utils/random.h"

#include "utils/system_memory.h"

#include <cstdint>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

namespace bongocat::platform {
static inline constexpr int MAX_ATTEMPTS = 2048;

uint32_t slow_rand() {
  constexpr const char *random_device_filename = "/dev/urandom";
  FileDescriptor fd(open(random_device_filename, O_RDONLY | O_CLOEXEC | O_NONBLOCK));
  if (fd._fd < 0) {
    BONGOCAT_LOG_ERROR("Can not open random device: %s", random_device_filename);
  }
  uint32_t val = 0;

  ssize_t r = read(fd._fd, &val, sizeof(val));
  if (r == static_cast<ssize_t>(sizeof(val))) {
    return val;
  }
  if (r == -1) {
    // Non-blocking mode: return on EAGAIN (no entropy available yet)
    // or on other read errors (errno preserved).
    return 0;
  }

  // Partial read: try to finish the request but still respect non-blocking.
  // If we encounter EAGAIN or other error, return 0.
  size_t got = (r > 0) ? static_cast<size_t>(r) : 0;
  unsigned char *p = reinterpret_cast<unsigned char *>(&val);
  int attempts = 0;
  while (got < sizeof(val) && attempts < MAX_ATTEMPTS) {
    r = read(fd._fd, p + got, sizeof(val) - got);
    if (r > 0) {
      got += static_cast<size_t>(r);
      continue;
    }
    if (r == 0) {
      errno = EIO;
      return 0;
    }
    if (errno == EINTR) {
      attempts++;
      continue; /* retry on interrupt */
    }
    // If EAGAIN (non-blocking & no data), or any other error -> fail
    return 0;
  }

  return val;
}
}  // namespace bongocat::platform
