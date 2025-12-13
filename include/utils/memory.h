#ifndef BONGOCAT_MEMORY_H
#define BONGOCAT_MEMORY_H

#include "./time.h"
#include "utils/error.h"

#include <cassert>
#include <cstring>
#include <stdatomic.h>
#if defined(__GNUC__) || defined(__GNUG__)
#  include <type_traits>
#endif

namespace bongocat {

// =============================================================================
// MEMORY POOL
// =============================================================================

// Memory pool for efficient allocation
struct memory_pool_t {
  void *data{BONGOCAT_NULLPTR};
  size_t size{0};
  size_t used{0};
  size_t alignment{0};
};

// =============================================================================
// MEMORY ALLOCATION FUNCTIONS
// =============================================================================

// Safe memory allocation functions
BONGOCAT_NODISCARD void *malloc(size_t size);
BONGOCAT_NODISCARD void *calloc(size_t count, size_t size);
BONGOCAT_NODISCARD void *realloc(void *ptr, size_t size);
void free(void *ptr);

// =============================================================================
// MEMORY POOL FUNCTIONS
// =============================================================================

// Memory pool functions
BONGOCAT_NODISCARD memory_pool_t *memory_pool_create(size_t size, size_t alignment);
BONGOCAT_NODISCARD void *memory_pool_alloc(memory_pool_t& pool, size_t size);
void memory_pool_reset(memory_pool_t& pool);
void memory_pool_destroy(memory_pool_t& pool);

// =============================================================================
// MEMORY STATISTICS
// =============================================================================

#if !defined(BONGOCAT_DISABLE_MEMORY_STATISTICS) || defined(BONGOCAT_ENABLE_MEMORY_STATISTICS)
// Memory statistics
struct memory_stats_t {
  atomic_size_t total_allocated;
  atomic_size_t current_allocated;
  atomic_size_t peak_allocated;
  atomic_size_t allocation_count;
  atomic_size_t free_count;
};

void memory_get_stats(memory_stats_t& stats);
#endif
void memory_print_stats();

// =============================================================================
// DEBUG BUILD FEATURES
// =============================================================================

// Memory leak detection (debug builds)
#ifndef NDEBUG
#  define BONGOCAT_MALLOC(size) ::bongocat::malloc_debug(size, __FILE__, __LINE__)
#  define BONGOCAT_FREE(ptr)    ::bongocat::free_debug(ptr, __FILE__, __LINE__)
void *malloc_debug(size_t size, const char *file, int line);
void free_debug(void *ptr, const char *file, int line);
void memory_leak_check();
#else
#  define BONGOCAT_MALLOC(size) ::bongocat::malloc(size)
#  define BONGOCAT_FREE(ptr)    ::bongocat::free(ptr)
#endif

// =============================================================================
// RAII CLEANUP MACROS
// =============================================================================

// Cleanup function for auto-freeing malloc'd memory
/*
inline void auto_free_impl(void *ptr) {
  void **p = static_cast<void **>(ptr);
  if (*p) {
    free(*p);
    *p = BONGOCAT_NULLPTR;
  }
}
*/

// Auto-free heap allocations when variable goes out of scope
// #define BONGOCAT_AUTO_FREE __attribute__((cleanup(bongocat::auto_free_impl)))

#define BONGOCAT_SAFE_FREE(ptr)            \
  do {                                     \
    if (ptr) {                             \
      free(reinterpret_cast<void *>(ptr)); \
      (ptr) = BONGOCAT_NULLPTR;            \
    }                                      \
  } while (0)

template <typename T, std::size_t N>
constexpr std::size_t LEN_ARRAY(const T (&)[N]) noexcept {
  return N;
}

// Cleanup implementation for auto pool (must be after memory_pool_t definition)
/*
inline void bongocat_auto_pool_impl(struct memory_pool **pool) {
  if (*pool) {
    memory_pool_destroy(*pool);
    *pool = BONGOCAT_NULLPTR;
  }
}
*/

// Auto-destroy memory pool when variable goes out of scope
// #define BONGOCAT_AUTO_POOL __attribute__((cleanup(bongocat::auto_pool_impl)))

template <typename T>
struct is_trivially_copyable {
#if defined(__clang__)
  inline static constexpr bool value = __is_trivially_copyable(T);
#elif defined(__GNUC__) || defined(__GNUG__)
  inline static constexpr bool value = __is_trivially_copyable(T);
#elif defined(_MSC_VER)
  inline static constexpr bool value = __is_trivially_copyable(T);
#else
  inline static constexpr bool value = false;
#endif
};

template <typename T>
struct is_trivially_destructible {
#if defined(__clang__)
  inline static constexpr bool value = __is_trivially_destructible(T);
#elif defined(__GNUC__) || defined(__GNUG__)
  // GCC requires `typename T` to be fully resolved
  // static constexpr bool value = __is_trivially_destructible(T);
  /// @FIXME: expected nested-name-specifier before »T« [-Wtemplate-body]
  /// Fallback: use STL
  inline static constexpr bool value = std::is_trivially_destructible_v<T>;
#elif defined(_MSC_VER)
  inline static constexpr bool value = __is_trivially_destructible(T);
#else
  inline static constexpr bool value = false;
#endif
};

// =============================================================================
// RAII CLEANUP
// =============================================================================

template <typename T>
class AllocatedMemory;
template <typename T>
void release_allocated_memory(AllocatedMemory<T>& memory) noexcept;

template <typename T>
class AllocatedMemory {
public:
  T *ptr{BONGOCAT_NULLPTR};
  size_t _size_bytes{0};

  constexpr AllocatedMemory() = default;
  ~AllocatedMemory() noexcept {
    release_allocated_memory(*this);
  }

  explicit AllocatedMemory(decltype(BONGOCAT_NULLPTR)) noexcept {}
  AllocatedMemory& operator=(decltype(BONGOCAT_NULLPTR)) noexcept {
    release_allocated_memory(*this);
    return *this;
  }

  AllocatedMemory(const AllocatedMemory& other) : _size_bytes(other._size_bytes) {
    _size_bytes = sizeof(T);
    if (other.ptr != BONGOCAT_NULLPTR && _size_bytes > 0) {
      ptr = static_cast<T *>(BONGOCAT_MALLOC(_size_bytes));
      if (ptr != BONGOCAT_NULLPTR) {
        if constexpr (is_trivially_copyable<T>::value) {
          memcpy(ptr, other.ptr, _size_bytes);
        } else {
          new (ptr) T(*other.ptr);
        }
      } else {
        _size_bytes = 0;
        ptr = BONGOCAT_NULLPTR;
        BONGOCAT_LOG_ERROR("memory allocation failed");
      }
    } else {
      _size_bytes = 0;
    }
  }
  AllocatedMemory& operator=(const AllocatedMemory& other) {
    if (this != &other) {
      release_allocated_memory(*this);
      _size_bytes = sizeof(T);
      if (other.ptr != BONGOCAT_NULLPTR && _size_bytes > 0) {
        ptr = static_cast<T *>(BONGOCAT_MALLOC(_size_bytes));
        if (ptr) {
          if constexpr (is_trivially_copyable<T>::value) {
            memcpy(ptr, other.ptr, _size_bytes);
          } else {
            new (ptr) T(*other.ptr);
          }
        } else {
          _size_bytes = 0;
          ptr = BONGOCAT_NULLPTR;
          BONGOCAT_LOG_ERROR("memory allocation failed");
        }
      } else {
        _size_bytes = 0;
      }
    }
    return *this;
  }

  AllocatedMemory(AllocatedMemory&& other) noexcept : ptr(other.ptr), _size_bytes(other._size_bytes) {
    other.ptr = BONGOCAT_NULLPTR;
    other._size_bytes = 0;
  }
  AllocatedMemory& operator=(AllocatedMemory&& other) noexcept {
    if (this != &other) {
      release_allocated_memory(*this);
      ptr = other.ptr;
      _size_bytes = other._size_bytes;
      other.ptr = BONGOCAT_NULLPTR;
      other._size_bytes = 0;
    }
    return *this;
  }

  constexpr operator bool() const noexcept {
    return ptr != BONGOCAT_NULLPTR;
  }

  T& operator*() {
    assert(ptr != nullptr);
    return *ptr;
  }
  constexpr const T& operator*() const {
    assert(ptr != nullptr);
    return *ptr;
  }
  T *operator->() {
    assert(ptr);
    return ptr;
  }
  constexpr const T *operator->() const {
    assert(ptr);
    return ptr;
  }
  explicit operator T *() noexcept {
    return ptr;
  }
  constexpr explicit operator const T *() const noexcept {
    return ptr;
  }

  constexpr bool operator==(decltype(BONGOCAT_NULLPTR)) const noexcept {
    return ptr == BONGOCAT_NULLPTR;
  }
  constexpr bool operator!=(decltype(BONGOCAT_NULLPTR)) const noexcept {
    return ptr != BONGOCAT_NULLPTR;
  }
};
template <typename T>
void release_allocated_memory(AllocatedMemory<T>& memory) noexcept {
  if (memory.ptr != BONGOCAT_NULLPTR) {
    if constexpr (!is_trivially_destructible<T>::value) {
      memory.ptr->~T();
    }
    BONGOCAT_SAFE_FREE(memory.ptr);
    memory.ptr = BONGOCAT_NULLPTR;
    memory._size_bytes = 0;
  }
}
template <typename T>
BONGOCAT_NODISCARD inline static AllocatedMemory<T> make_null_memory() noexcept {
  return AllocatedMemory<T>();
}
template <typename T>
BONGOCAT_NODISCARD inline static AllocatedMemory<T> make_allocated_memory() {
  AllocatedMemory<T> ret;
  ret._size_bytes = sizeof(T);
  if (ret._size_bytes > 0) {
    ret.ptr = static_cast<T *>(BONGOCAT_MALLOC(ret._size_bytes));
    if (ret.ptr != BONGOCAT_NULLPTR) {
      // default ctor
      new (ret.ptr) T();
      return ret;
    } else {
      BONGOCAT_LOG_ERROR("memory allocation failed");
    }
  }
  ret._size_bytes = 0;
  ret.ptr = BONGOCAT_NULLPTR;
  return ret;
}

template <typename T>
class AllocatedArray;
template <typename T>
void release_allocated_array(AllocatedArray<T>& memory) noexcept;

template <typename T>
class AllocatedArray {
public:
  T *data{BONGOCAT_NULLPTR};
  size_t count{0};
  size_t _size_bytes{0};

  constexpr AllocatedArray() = default;
  ~AllocatedArray() noexcept {
    release_allocated_array(*this);
  }

  explicit AllocatedArray(decltype(BONGOCAT_NULLPTR)) noexcept {}
  AllocatedArray& operator=(decltype(BONGOCAT_NULLPTR)) noexcept {
    release_allocated_array(*this);
    return *this;
  }

  explicit AllocatedArray(size_t p_count) : count(p_count), _size_bytes(sizeof(T) * count) {
    if (_size_bytes > 0) {
      data = static_cast<T *>(BONGOCAT_MALLOC(_size_bytes));
      if (data) {
        return;
      } else {
        BONGOCAT_LOG_ERROR("malloc array failed: %zu bytes", _size_bytes);
      }
    }
    count = 0;
    _size_bytes = 0;
  }

  AllocatedArray(const AllocatedArray& other) : count(other.count), _size_bytes(other._size_bytes) {
    if (other.data && _size_bytes > 0) {
      data = static_cast<T *>(BONGOCAT_MALLOC(_size_bytes));
      if (data) {
        if constexpr (is_trivially_copyable<T>::value) {
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
    data = BONGOCAT_NULLPTR;
  }
  AllocatedArray& operator=(const AllocatedArray& other) {
    if (this != &other) {
      release_allocated_array(*this);
      count = other.count;
      _size_bytes = other._size_bytes;
      if (other.data && _size_bytes > 0) {
        data = static_cast<T *>(BONGOCAT_MALLOC(_size_bytes));
        if (data) {
          if constexpr (is_trivially_copyable<T>::value) {
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
      data = BONGOCAT_NULLPTR;
    }
    return *this;
  }

  AllocatedArray(AllocatedArray&& other) noexcept
      : data(other.data)
      , count(other.count)
      , _size_bytes(other._size_bytes) {
    other.data = BONGOCAT_NULLPTR;
    other.count = 0;
    other._size_bytes = 0;
  }
  AllocatedArray& operator=(AllocatedArray&& other) noexcept {
    if (this != &other) {
      release_allocated_array(*this);
      data = other.data;
      count = other.count;
      _size_bytes = other._size_bytes;
      other.data = BONGOCAT_NULLPTR;
      other.count = 0;
      other._size_bytes = 0;
    }
    return *this;
  }

  T& operator[](size_t index) {
    assert(index < count);
    return data[index];
  }
  constexpr const T& operator[](size_t index) const {
    assert(index < count);
    return data[index];
  }

  constexpr explicit operator bool() const noexcept {
    return data != BONGOCAT_NULLPTR;
  }

  constexpr bool operator==(decltype(BONGOCAT_NULLPTR)) const noexcept {
    return data == BONGOCAT_NULLPTR;
  }
  constexpr bool operator!=(decltype(BONGOCAT_NULLPTR)) const noexcept {
    return data != BONGOCAT_NULLPTR;
  }
};
template <typename T>
void release_allocated_array(AllocatedArray<T>& memory) noexcept {
  if (memory.data != BONGOCAT_NULLPTR) {
    if constexpr (!is_trivially_destructible<T>::value) {
      for (size_t i = 0; i < memory.count; i++) {
        memory.data[i].~T();
      }
    }
    BONGOCAT_SAFE_FREE(memory.data);
    memory.data = BONGOCAT_NULLPTR;
    memory.count = 0;
    memory._size_bytes = 0;
  }
}

template <typename T>
BONGOCAT_NODISCARD inline static AllocatedArray<T> make_unallocated_array() noexcept {
  return AllocatedArray<T>();
}
template <typename T>
BONGOCAT_NODISCARD inline static AllocatedArray<T> make_allocated_array_uninitialized(size_t count) {
  return count > 0 ? AllocatedArray<T>(count) : AllocatedArray<T>();
}
template <typename T>
BONGOCAT_NODISCARD inline static AllocatedArray<T> make_allocated_array(size_t count) {
  auto ret = count > 0 ? AllocatedArray<T>(count) : AllocatedArray<T>();
  for (size_t i = 0; i < ret.count; i++) {
    new (&ret.data[i]) T();
  }
  return ret;
}
template <typename T>
BONGOCAT_NODISCARD inline static AllocatedArray<T> make_allocated_array_with_value(size_t count, const T& value) {
  auto ret = count > 0 ? AllocatedArray<T>(count) : AllocatedArray<T>();
  for (size_t i = 0; i < ret.count; i++) {
    ret.data[i] = value;
  }
  return ret;
}

// remove_reference implementation (no STL)
template <typename T>
struct remove_reference {
  typedef T type;
};
template <typename T>
struct remove_reference<T&> {
  typedef T type;
};
template <typename T>
struct remove_reference<T&&> {
  typedef T type;
};

// move implementation (no STL)
template <typename T>
inline typename remove_reference<T>::type&& move(T&& t) {
  typedef typename remove_reference<T>::type U;
  return static_cast<U&&>(t);
}
}  // namespace bongocat

#endif  // BONGOCAT_MEMORY_H