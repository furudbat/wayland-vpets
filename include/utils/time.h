#ifndef BONGOCAT_TIME_H
#define BONGOCAT_TIME_H

#include <ctime>
#include <cstdint>

using timestamp_us_t = int64_t;
using timestamp_ms_t = int64_t;
using time_us_t = int64_t;
using time_ms_t = int64_t;
using time_ns_t = int64_t;
using time_sec_t = int64_t;

timestamp_us_t get_current_time_us(void);
timestamp_ms_t get_current_time_ms(void);

time_us_t get_uptime_us(void);
time_ms_t get_uptime_ms(void);

#endif // TIME_H