#include "utils/system_memory.h"
#include "utils/error.h"
#include "utils/time.h"
#include <pthread.h>

namespace bongocat::platform {
    static inline constexpr time_ms_t THREAD_JOIN_TIMEOUT_MS = 5000;                                  // maximum wait for graceful exit
    static inline constexpr time_ms_t THREAD_SlEEP_WHEN_WAITING_FOR_THREAD_MS = 100;
    static inline constexpr int THREAD_SLEEP_MAX_ATTEMPTS = 2048;


    int join_thread_with_timeout(pthread_t& thread, time_ms_t timeout_ms) {
        timespec start{};
        timespec now{};
        clock_gettime(CLOCK_MONOTONIC, &start);

        int attempts = 0;
        while (attempts < THREAD_SLEEP_MAX_ATTEMPTS) {
            const int ret = pthread_tryjoin_np(thread, nullptr);
            if (ret == 0) {
                thread = 0;
                return 0;
            }
            if (ret != EBUSY) return ret;   // error other than "still running"

            // Check elapsed time
            clock_gettime(CLOCK_MONOTONIC, &now);
            const time_ms_t elapsed_ms = (now.tv_sec - start.tv_sec) * 1000 + (now.tv_nsec - start.tv_nsec) / 1000000L;
            if (elapsed_ms >= timeout_ms) return ETIMEDOUT;

            // small sleep to avoid busy waiting
            timespec ts = {.tv_sec = 0, .tv_nsec = 1000000L * THREAD_SlEEP_WHEN_WAITING_FOR_THREAD_MS};
            nanosleep(&ts, nullptr);
            attempts++;
        }

        return EBUSY;
    }

    int stop_thread_graceful_or_cancel(pthread_t& thread, atomic_bool &running_flag) {
        if (thread == 0) return 0;

        atomic_store(&running_flag, false);
        const int ret = join_thread_with_timeout(thread, THREAD_JOIN_TIMEOUT_MS);
        if (thread != 0 && ret == ETIMEDOUT) {
            BONGOCAT_LOG_WARNING("Thread did not exit in time, cancelling");
            pthread_cancel(thread);
            pthread_join(thread, nullptr);
        }

        thread = 0;

        return ret;
    }
}