#include "utils/memory.h"
#include "utils/system_memory.h"
#include "utils/error.h"
#include "core/bongocat.h"
#include <cstdint>
#include <cassert>
#include <pthread.h>
#include <cstdlib>

namespace bongocat {
    namespace details {
#if !defined(BONGOCAT_DISABLE_MEMORY_STATISTICS) || defined(BONGOCAT_ENABLE_MEMORY_STATISTICS)
        inline memory_stats_t& get_memory_stats() {
            static memory_stats_t g_instance{};
            return g_instance;
        }
        inline platform::Mutex& get_memory_mutex() {
            static platform::Mutex g_instance;
            return g_instance;
        }
#endif

#ifndef NDEBUG
        struct allocation_record_t {
            void *ptr{nullptr};
            size_t size{0};
            const char *file{};
            int line{0};
            allocation_record_t *next{nullptr};
        };

        inline allocation_record_t*& get_allocations() {
            static allocation_record_t *g_instance = nullptr;
            return g_instance;
        }
#endif
    }


    void* malloc(size_t size) {
        if (size == 0) {
            BONGOCAT_LOG_WARNING("Attempted to allocate 0 bytes");
            return nullptr;
        }

        void *ptr = ::malloc(size);
        if (!ptr) {
            BONGOCAT_LOG_ERROR("Failed to allocate %zu bytes", size);
            return nullptr;
        }

#if !defined(BONGOCAT_DISABLE_MEMORY_STATISTICS) || defined(BONGOCAT_ENABLE_MEMORY_STATISTICS)
        {
            using namespace details;
            platform::LockGuard guard(get_memory_mutex());
            get_memory_stats().total_allocated += size;
            get_memory_stats().current_allocated += size;
            if (get_memory_stats().current_allocated > get_memory_stats().peak_allocated) {
                atomic_store(&get_memory_stats().peak_allocated, atomic_load(&get_memory_stats().current_allocated));
            }
            ++get_memory_stats().allocation_count;
        }
#endif

        return ptr;
    }

    void* calloc(size_t count, size_t size) {
        if (count == 0 || size == 0) {
            BONGOCAT_LOG_WARNING("Attempted to allocate 0 bytes");
            return nullptr;
        }

        // Check for overflow
        assert(size > 0);
        if (count > SIZE_MAX / size) {
            BONGOCAT_LOG_ERROR("Integer overflow in calloc");
            return nullptr;
        }

        void *ptr = ::calloc(count, size);
        if (!ptr) {
            BONGOCAT_LOG_ERROR("Failed to allocate %zu bytes", count * size);
            return nullptr;
        }

#if !defined(BONGOCAT_DISABLE_MEMORY_STATISTICS) || defined(BONGOCAT_ENABLE_MEMORY_STATISTICS)
        {
            using namespace details;
            platform::LockGuard guard(get_memory_mutex());
            const size_t total_size = count * size;
            get_memory_stats().total_allocated += total_size;
            get_memory_stats().current_allocated += total_size;
            if (get_memory_stats().current_allocated > get_memory_stats().peak_allocated) {
                atomic_store(&get_memory_stats().peak_allocated, atomic_load(&get_memory_stats().current_allocated));
            }
            ++get_memory_stats().allocation_count;
        }
#endif

        return ptr;
    }

    void* bongocat_realloc(void *ptr, size_t size) {
        if (size == 0) {
            bongocat::free(ptr);
            return nullptr;
        }

        void *new_ptr = ::realloc(ptr, size);
        if (!new_ptr) {
            BONGOCAT_LOG_ERROR("Failed to reallocate to %zu bytes", size);
            return nullptr;
        }

        // Note: We can't track size changes accurately without storing original sizes
        // This is a limitation of this simple tracking system

        return new_ptr;
    }

    void free(void *ptr) {
        if (!ptr) return;

        ::free(ptr);

#if !defined(BONGOCAT_DISABLE_MEMORY_STATISTICS) || defined(BONGOCAT_ENABLE_MEMORY_STATISTICS)
        {
            using namespace details;
            platform::LockGuard guard(get_memory_mutex());
            ++get_memory_stats().free_count;
            /*
            if (static_cast<int>(g_memory_stats.free_count) > static_cast<int>(g_memory_stats.allocation_count)) {
                BONGOCAT_LOG_VERBOSE("Potential double free: %d/%d", atomic_load(&g_memory_stats.allocation_count), atomic_load(&g_memory_stats.free_count));
            }
            */
        }
#endif
    }

    memory_pool_t* memory_pool_create(size_t size, size_t alignment) {
        if (size == 0 || alignment == 0) {
            BONGOCAT_LOG_ERROR("Invalid memory pool parameters");
            return nullptr;
        }

        // Validate alignment is a power of 2
        if ((alignment & (alignment - 1)) != 0) {
          BONGOCAT_LOG_ERROR("Memory pool alignment must be a power of 2, got %zu",
                             alignment);
          return NULL;
        }

        auto *pool = static_cast<memory_pool_t *>(bongocat::malloc(sizeof(memory_pool_t)));
        if (!pool) return nullptr;

        pool->data = bongocat::malloc(size);
        if (!pool->data) {
            bongocat::free(pool);
            return nullptr;
        }

        pool->size = size;
        pool->used = 0;
        pool->alignment = alignment;

        return pool;
    }

    void* memory_pool_alloc(memory_pool_t& pool, size_t size) {
        if (size == 0) return nullptr;

        // Align the size
        const size_t aligned_size = (size + pool.alignment - 1) & ~(pool.alignment - 1);

        if (pool.used + aligned_size > pool.size) {
            BONGOCAT_LOG_ERROR("Memory pool exhausted");
            return nullptr;
        }

        void *ptr = static_cast<char *>(pool.data) + pool.used;
        pool.used += aligned_size;

        return ptr;
    }

    void memory_pool_reset(memory_pool_t *pool) {
        if (pool) {
            pool->used = 0;
        }
    }

    void memory_pool_destroy(memory_pool_t *pool) {
        if (pool) {
            bongocat::free(pool->data);
            bongocat::free(pool);
        }
    }

#if !defined(BONGOCAT_DISABLE_MEMORY_STATISTICS) || defined(BONGOCAT_ENABLE_MEMORY_STATISTICS)
    void memory_get_stats(memory_stats_t *stats) {
        if (!stats) return;

        {
            using namespace details;
            platform::LockGuard guard(get_memory_mutex());
            stats->total_allocated    = atomic_load(&get_memory_stats().total_allocated);
            stats->current_allocated  = atomic_load(&get_memory_stats().current_allocated);
            stats->peak_allocated     = atomic_load(&get_memory_stats().peak_allocated);
            stats->allocation_count   = atomic_load(&get_memory_stats().allocation_count);
            stats->free_count         = atomic_load(&get_memory_stats().free_count);
        }
    }

    void memory_print_stats() {
        memory_stats_t stats;
        memory_get_stats(&stats);

        {
            using namespace details;
            platform::LockGuard guard(get_memory_mutex());
            const size_t total_allocated = atomic_load(&stats.total_allocated);
            const size_t current_allocated = atomic_load(&stats.current_allocated);
            const size_t peak_allocated = atomic_load(&stats.peak_allocated);
            const size_t allocation_count = atomic_load(&stats.allocation_count);
            const size_t free_count = atomic_load(&stats.free_count);

            assert(allocation_count <= INT_MAX);
            assert(free_count <= INT_MAX);

            bongocat::details::log_info("Memory Statistics:");
            bongocat::details::log_info("  Total allocated: %zu bytes (%.2f MB)", total_allocated, static_cast<double>(total_allocated) / (1024.0 * 1024.0));
            bongocat::details::log_info("  Current allocated: %zu bytes (%.2f MB)", current_allocated, static_cast<double>(current_allocated) / (1024.0 * 1024.0));
            bongocat::details::log_info("  Peak allocated: %zu bytes (%.2f MB)", peak_allocated, static_cast<double>(peak_allocated) / (1024.0 * 1024.0));
            bongocat::details::log_info("  Allocations: %zu", allocation_count);
            bongocat::details::log_info("  Frees: %zu", free_count);
            bongocat::details::log_info("  Potential leaks: %d", static_cast<int>(allocation_count) - static_cast<int>(free_count));
        }
    }
#else
    void memory_print_stats() {}
#endif

#ifndef NDEBUG
    void* malloc_debug(size_t size, const char *file, int line) {
        void *ptr = bongocat::malloc(size);
        if (!ptr) return nullptr;

        {
            using namespace details;
            platform::LockGuard guard(details::get_memory_mutex());
            auto *record = static_cast<allocation_record_t *>(::malloc(sizeof(allocation_record_t)));
            if (record) {
                record->ptr = ptr;
                record->size = size;
                record->file = file;
                record->line = line;
                record->next = get_allocations();
                get_allocations() = record;
            }
        }

        return ptr;
    }

    void free_debug(void *ptr, const char *file, int line) {
        if (!ptr) return;

        {
            using namespace details;
            platform::LockGuard guard(details::get_memory_mutex());
            allocation_record_t **current = &get_allocations();
            while (*current) {
                if ((*current)->ptr == ptr) {
                    allocation_record_t *to_remove = *current;
                    *current = (*current)->next;
                    assert(to_remove);
                    ::free(to_remove);
                    break;
                }
                current = &(*current)->next;
            }
        }

        bongocat::free(ptr);

#if !defined(BONGOCAT_DISABLE_MEMORY_STATISTICS) || defined(BONGOCAT_ENABLE_MEMORY_STATISTICS)
        {
            using namespace details;
            platform::LockGuard guard(details::get_memory_mutex());
            const size_t free_count = atomic_load(&get_memory_stats().free_count);
            const size_t current_allocated = atomic_load(&get_memory_stats().current_allocated);
            if (free_count > current_allocated) {
                BONGOCAT_LOG_WARNING("possible double free, one free is to much: Frees: %zu; Allocations: %zu %s:%d", free_count > current_allocated, file, line);
            }
        }
#endif
    }

    void memory_leak_check() {
        using namespace details;
        platform::LockGuard guard(get_memory_mutex());
        if (!get_allocations()) {
            BONGOCAT_LOG_INFO("No memory leaks detected");
            return;
        }

        BONGOCAT_LOG_ERROR("Memory leaks detected:");
        allocation_record_t *current = get_allocations();
        while (current) {
            BONGOCAT_LOG_ERROR("  %zu bytes at %s:%d", current->size, current->file, current->line);
            current = current->next;
        }
    }
#endif
}
