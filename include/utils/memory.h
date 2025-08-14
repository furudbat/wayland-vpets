#ifndef BONGOCAT_MEMORY_H
#define BONGOCAT_MEMORY_H

#include "utils/error.h"
#include <stdatomic.h>
#include <pthread.h>

#include "time.h"

// Memory pool for efficient allocation
struct memory_pool_t {
    void *data{nullptr};
    size_t size{0};
    size_t used{0};
    size_t alignment{0};
};

// Safe memory allocation functions
void* bongocat_malloc(size_t size);
void* bongocat_calloc(size_t count, size_t size);
void* bongocat_realloc(void *ptr, size_t size);
void bongocat_free(void *ptr);

// Memory pool functions
memory_pool_t* memory_pool_create(size_t size, size_t alignment);
void* memory_pool_alloc(memory_pool_t& pool, size_t size);
void memory_pool_reset(memory_pool_t& pool);
void memory_pool_destroy(memory_pool_t& pool);

#ifndef BONGOCAT_DISABLE_MEMORY_STATISTICS
// Memory statistics
struct memory_stats_t {
    atomic_size_t total_allocated;
    atomic_size_t current_allocated;
    atomic_size_t peak_allocated;
    atomic_size_t allocation_count;
    atomic_size_t free_count;
};

void memory_get_stats(memory_stats_t& stats);
void memory_print_stats();
#endif

// Memory leak detection (debug builds)
#ifndef NDEBUG
#define BONGOCAT_MALLOC(size) bongocat_malloc_debug(size, __FILE__, __LINE__)
#define BONGOCAT_FREE(ptr) bongocat_free_debug(ptr, __FILE__, __LINE__)
void* bongocat_malloc_debug(size_t size, const char *file, int line);
void bongocat_free_debug(void *ptr, const char *file, int line);
void memory_leak_check();
#else
#define BONGOCAT_MALLOC(size) bongocat_malloc(size)
#define BONGOCAT_FREE(ptr) bongocat_free(ptr)
#endif

#define BONGOCAT_SAFE_FREE(ptr) \
    do { \
        if (ptr) { \
            BONGOCAT_FREE(ptr); \
            ptr = NULL; \
        } \
    } while(false)

#define LEN_ARRAY(x)  (sizeof(x) / sizeof((x)[0]))

int join_thread_with_timeout(pthread_t& thread, time_ms_t timeout_ms);
int stop_thread_graceful_or_cancel(pthread_t& thread, atomic_bool& running_flag);

#endif // MEMORY_H