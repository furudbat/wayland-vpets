#ifndef BONGOCAT_UPDATE_SHARED_CONTEXT_H
#define BONGOCAT_UPDATE_SHARED_CONTEXT_H

#include "config/config.h"
#include "input_shared_memory.h"
#include "utils/system_memory.h"
#include "utils/time.h"
#include <pthread.h>
#include <stdatomic.h>

namespace bongocat::platform::update {
    inline static constexpr size_t MaxCpus = 256;
    inline static constexpr size_t CpuSnapshotRingBufferMaxHistory = 8;

    struct cpu_stat_t {
        size_t idle_time{0};
        size_t total_time{0};
    };
    struct cpu_snapshot_t {
        cpu_stat_t stats[MaxCpus]{};
        size_t count{0};               // how many CPUs in this snapshot
    };

    struct cpu_snapshot_ring_buffer_t {
        // ring buffer for snapshots
        cpu_snapshot_t history[CpuSnapshotRingBufferMaxHistory]{};
        size_t head{0};         // next write position
        size_t stored{0};       // number of valid snapshots
    };

    struct update_shared_memory_t {
        cpu_snapshot_ring_buffer_t cpu_snapshots;
        const cpu_snapshot_t* latest_snapshot{nullptr};
        double avg_cpu_usage{0};
        double max_cpu_usage{0};
        double last_avg_cpu_usage{0};
        double last_max_cpu_usage{0};
        bool cpu_active{false};
    };
}

#endif // BONGOCAT_INPUT_CONTEXT_H