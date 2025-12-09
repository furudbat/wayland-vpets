#include "utils/time.h"

#include <ctime>
#include <sys/time.h>

namespace bongocat::platform {
timestamp_us_t get_current_time_us() {
  timeval now{};
  gettimeofday(&now, nullptr);
  return now.tv_sec * 1000000LL + now.tv_usec;
}
timestamp_ms_t get_current_time_ms() {
  return get_current_time_us() / 1000;
}

time_us_t get_uptime_us() {
  timespec ts{};
  if (clock_gettime(CLOCK_BOOTTIME, &ts) != 0) {
    return 0;
  }
  return ts.tv_sec * 1000000000LL + ts.tv_nsec;
}
time_ms_t get_uptime_ms() {
  return get_uptime_us() / 1000;
}
}  // namespace bongocat::platform