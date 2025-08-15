#ifndef BONGOCAT_MEMORY_H
#define BONGOCAT_MEMORY_H

#include "./time.h"
#include "utils/error.h"
#include <stdatomic.h>
#include <cassert>
#if defined(__GNUC__) || defined(__GNUG__)
#include <type_traits>
#endif

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




template <typename T>
struct bongocat_is_trivially_copyable {
#if defined(__clang__)
    static constexpr bool value = __is_trivially_copyable(T);
#elif defined(__GNUC__) || defined(__GNUG__)
    static constexpr bool value = __is_trivially_copyable(T);
#elif defined(_MSC_VER)
    static constexpr bool value = __is_trivially_copyable(T);
#else
    static constexpr bool value = false;
#endif
};

template <typename T>
struct bongocat_is_trivially_destructible {
#if defined(__clang__)
    static constexpr bool value = __is_trivially_destructible(T);
#elif defined(__GNUC__) || defined(__GNUG__)
    // GCC requires `typename T` to be fully resolved
    //static constexpr bool value = __is_trivially_destructible(T);
    /// @FIXME: expected nested-name-specifier before »T« [-Wtemplate-body]
    /// Fallback to STL
    static constexpr bool value = std::is_trivially_destructible<T>::value;
#elif defined(_MSC_VER)
    static constexpr bool value = __is_trivially_destructible(T);
#else
    static constexpr bool value = false;
#endif
};

template<typename T>
struct AllocatedMemory {
    T* ptr{nullptr};
    size_t _size_bytes{0};

    AllocatedMemory() = default;

    AllocatedMemory(decltype(nullptr)) noexcept {}
    AllocatedMemory& operator=(decltype(nullptr)) noexcept {
        _release();
        return *this;
    }

    AllocatedMemory(const AllocatedMemory& other)
        : _size_bytes(other._size_bytes)
    {
        _size_bytes = sizeof(T);
        if (other.ptr != nullptr && _size_bytes > 0) {
            ptr = static_cast<T*>(BONGOCAT_MALLOC(_size_bytes));
            if (ptr != nullptr) {
                if constexpr (bongocat_is_trivially_copyable<T>::value) {
                    memcpy(ptr, other.ptr, _size_bytes);
                } else {
                    *ptr = *other.ptr;
                }
            } else {
                _size_bytes = 0;
                ptr = nullptr;
                BONGOCAT_LOG_ERROR("memory allocation failed");
            }
        } else {
            _size_bytes = 0;
        }
    }
    AllocatedMemory& operator=(const AllocatedMemory& other) {
        if (this != &other) {
            _release();
            _size_bytes = sizeof(T);
            if (other.ptr != nullptr && _size_bytes > 0) {
                ptr = static_cast<T*>(BONGOCAT_MALLOC(_size_bytes));
                if (ptr) {
                    if constexpr (bongocat_is_trivially_copyable<T>::value) {
                        memcpy(ptr, other.ptr, _size_bytes);
                    } else {
                        *ptr = *other.ptr;
                    }
                } else {
                    _size_bytes = 0;
                    ptr = nullptr;
                    BONGOCAT_LOG_ERROR("memory allocation failed");
                }
            } else {
                _size_bytes = 0;
            }
        }
        return *this;
    }

    AllocatedMemory(AllocatedMemory&& other) noexcept
        : ptr(other.ptr), _size_bytes(other._size_bytes)
    {
        other.ptr = nullptr;
        other._size_bytes = 0;
    }
    AllocatedMemory& operator=(AllocatedMemory&& other) noexcept {
        if (this != &other) {
            _release();
            ptr = other.ptr;
            _size_bytes = other._size_bytes;
            other.ptr = nullptr;
            other._size_bytes = 0;
        }
        return *this;
    }

    // Release memory manually
    void _release() {
        if (ptr) {
            if (!bongocat_is_trivially_destructible<T>::value) {
                ptr->~T();
            }
            BONGOCAT_FREE(ptr);
            ptr = nullptr;
            _size_bytes = 0;
        }
    }

    ~AllocatedMemory() {
        _release();
    }

    // Implicit conversion to bool
    explicit(false) operator bool() const noexcept {
        return ptr != nullptr;
    }

    T& operator*() {
        assert(ptr);
        return *ptr;
    }
    const T& operator*() const {
        assert(ptr);
        return *ptr;
    }
    T* operator->() {
        assert(ptr);
        return ptr;
    }
    const T* operator->() const {
        assert(ptr);
        return ptr;
    }
    operator T*() noexcept {
        return ptr;
    }
    operator const T*() const noexcept {
        return ptr;
    }

    bool operator==(decltype(nullptr)) const noexcept {
        return ptr == nullptr;
    }
    bool operator!=(decltype(nullptr)) const noexcept {
        return ptr != nullptr;
    }
};
template <typename T>
inline static AllocatedMemory<T> make_null_memory() {
    return AllocatedMemory<T>();
}
template <typename T>
inline static AllocatedMemory<T> make_allocated_memory() {
    AllocatedMemory<T> ret;
    ret._size_bytes = sizeof(T);
    if (ret._size_bytes > 0) {
        ret.ptr = static_cast<T*>(BONGOCAT_MALLOC(ret._size_bytes));
        if (ret.ptr != nullptr) {
            // default ctor
            new (ret.ptr) T();
            return ret;
        } else {
            BONGOCAT_LOG_ERROR("memory allocation failed");
        }
    }
    ret._size_bytes = 0;
    ret.ptr = nullptr;
    return ret;
}

template <typename T>
struct AllocatedArray {
    T* data{nullptr};
    size_t count{0};
    size_t _size_bytes{0};

    AllocatedArray() = default;

    AllocatedArray(decltype(nullptr)) noexcept {}
    AllocatedArray& operator=(decltype(nullptr)) noexcept {
        _release();
        return *this;
    }

    explicit AllocatedArray(size_t p_count)
        : count(p_count), _size_bytes(sizeof(T) * count)
    {
        if (_size_bytes > 0) {
            data = static_cast<T*>(BONGOCAT_MALLOC(_size_bytes));
            if (data) {
                return;
            } else {
                BONGOCAT_LOG_ERROR("malloc array failed: %zu bytes", _size_bytes);
            }
        }
        count = 0;
        _size_bytes = 0;
    }

    AllocatedArray(const AllocatedArray& other)
        : count(other.count), _size_bytes(other._size_bytes)
    {
        if (other.data && _size_bytes > 0) {
            data = static_cast<T*>(BONGOCAT_MALLOC(_size_bytes));
            if (data) {
                if constexpr (bongocat_is_trivially_copyable<T>::value) {
                    memcpy(data, other.data, _size_bytes);
                } else {
                    for (size_t i = 0; i < other.count; i++) {
                        *data[i] = *other.data[i];
                    }
                }
                return;
            } else {
                BONGOCAT_LOG_ERROR("file mmap failed in copy constructor");
            }
        }

        count = 0;
        _size_bytes = 0;
        data = nullptr;
    }
    AllocatedArray& operator=(const AllocatedArray& other) {
        if (this != &other) {
            _release();
            count = other.count;
            _size_bytes = other._size_bytes;
            if (other.data && _size_bytes > 0) {
                data = static_cast<T*>(BONGOCAT_MALLOC(_size_bytes));
                if (data) {
                    if constexpr (bongocat_is_trivially_copyable<T>::value) {
                        memcpy(data, other.data, _size_bytes);
                    } else {
                        for (size_t i = 0; i < other.count; i++) {
                            *data[i] = *other.data[i];
                        }
                    }
                    return *this;
                } else {
                    BONGOCAT_LOG_ERROR("mmap buffer failed in copy assignment");
                }
            }

            count = 0;
            _size_bytes = 0;
            data = nullptr;
        }
        return *this;
    }

    AllocatedArray(AllocatedArray&& other) noexcept
        : data(other.data), count(other.count), _size_bytes(other._size_bytes)
    {
        other.data = nullptr;
        other.count = 0;
        other._size_bytes = 0;
    }
    AllocatedArray& operator=(AllocatedArray&& other) noexcept {
        if (this != &other) {
            _release();
            data = other.data;
            count = other.count;
            _size_bytes = other._size_bytes;
            other.data = nullptr;
            other.count = 0;
            other._size_bytes = 0;
        }
        return *this;
    }

    T& operator[](size_t index) {
        assert(index < count);
        return data[index];
    }
    const T& operator[](size_t index) const {
        assert(index < count);
        return data[index];
    }

    // Release memory manually
    void _release() {
        if (data != nullptr) {
            if (!bongocat_is_trivially_destructible<T>::value) {
                for (size_t i = 0; i < count; i++) {
                    data[i].~T();
                }
            }
            BONGOCAT_FREE(data);
            data = nullptr;
            count = 0;
            _size_bytes = 0;
        }
    }

    ~AllocatedArray() {
        _release();
    }

    // Implicit conversion to bool
    explicit(false) operator bool() const noexcept {
        return data != nullptr;
    }

    bool operator==(decltype(nullptr)) const noexcept {
        return data == nullptr;
    }
    bool operator!=(decltype(nullptr)) const noexcept {
        return data != nullptr;
    }
};
template <typename T>
inline static AllocatedArray<T> make_unallocated_array() {
    return AllocatedArray<T>();
}
template <typename T>
inline static AllocatedArray<T> make_allocated_array_uninitialized(size_t count) {
    return count > 0 ? AllocatedArray<T>(count) : AllocatedArray<T>();
}
template <typename T>
inline static AllocatedArray<T> make_allocated_array(size_t count) {
    auto ret= count > 0 ? AllocatedArray<T>(count) : AllocatedArray<T>();
    for (size_t i = 0;i < ret.count;i++) {
        new (&ret.data[i]) T();
    }
    return ret;
}
template <typename T>
inline static AllocatedArray<T> make_allocated_array_with_value(size_t count, const T& value) {
    auto ret= count > 0 ? AllocatedArray<T>(count) : AllocatedArray<T>();
    for (size_t i = 0;i < ret.count;i++) {
        ret.data[i] = value;
    }
    return ret;
}

// remove_reference implementation (no STL)
template <typename T> struct bongocat_remove_reference      { typedef T type; };
template <typename T> struct bongocat_remove_reference<T&>  { typedef T type; };
template <typename T> struct bongocat_remove_reference<T&&> { typedef T type; };

// move implementation (no STL)
template <typename T>
typename bongocat_remove_reference<T>::type&& bongocat_move(T&& t) {
    typedef typename bongocat_remove_reference<T>::type U;
    return static_cast<U&&>(t);
}

#endif // BONGOCAT_MEMORY_H