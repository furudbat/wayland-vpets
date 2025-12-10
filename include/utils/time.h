#ifndef BONGOCAT_TIME_H
#define BONGOCAT_TIME_H

#include <cstdint>

namespace bongocat::platform {
using timestamp_us_t = int64_t;
using timestamp_ms_t = int64_t;
using time_us_t = int64_t;
using time_ms_t = int64_t;
using time_ns_t = int64_t;
using time_sec_t = int64_t;

[[nodiscard]] timestamp_us_t get_current_time_us();
[[nodiscard]] timestamp_ms_t get_current_time_ms();

[[nodiscard]] time_us_t get_uptime_us();
[[nodiscard]] time_ms_t get_uptime_ms();
}  // namespace bongocat::platform

#endif  // BONGOCAT_TIME_H