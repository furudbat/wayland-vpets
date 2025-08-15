#ifndef BONGOCAT_SYSTEM_MEMORY_H
#define BONGOCAT_SYSTEM_MEMORY_H

#include "./memory.h"
#include "./time.h"
#include "utils/error.h"
#include <sys/mman.h>
#include <unistd.h>
#include <stdatomic.h>
#include <pthread.h>
#include <cassert>

int join_thread_with_timeout(pthread_t& thread, time_ms_t timeout_ms);
int stop_thread_graceful_or_cancel(pthread_t& thread, atomic_bool& running_flag);

struct Mutex {
    pthread_mutex_t pt_mutex{};

    Mutex() {
        if (pthread_mutex_init(&pt_mutex, nullptr) != 0) {
            BONGOCAT_LOG_ERROR("Failed to initialize mutex");
        }
    }
    ~Mutex() {
        pthread_mutex_destroy(&pt_mutex);
    }

    // Delete copy operations — a mutex should not be copied
    Mutex(const Mutex&) = delete;
    Mutex& operator=(const Mutex&) = delete;

    // Allow move
    Mutex(Mutex&& other) noexcept {
        pt_mutex = other.pt_mutex;
    }

    void _lock() {
        if (const int rc = pthread_mutex_lock(&pt_mutex); rc != 0) {
            BONGOCAT_LOG_ERROR("pthread_mutex_lock failed");
        }
    }

    void _unlock() {
        if (const int rc = pthread_mutex_unlock(&pt_mutex); rc != 0) {
            BONGOCAT_LOG_ERROR("pthread_mutex_unlock failed");
        }
    }
};
struct LockGuard {
    explicit LockGuard(Mutex& m) : _mutex(m) {
        _mutex._lock();
    }
    ~LockGuard() {
        _mutex._unlock();
    }

    // No copying, no move
    LockGuard(const LockGuard&) = delete;
    LockGuard& operator=(const LockGuard&) = delete;
    LockGuard(const LockGuard&&) = delete;
    LockGuard&& operator=(const LockGuard&&) = delete;

    Mutex& _mutex;
};



template <typename T>
struct MMapMemory {
    T* ptr{nullptr};
    size_t _size_bytes{0};

    MMapMemory() = default;

    MMapMemory(decltype(nullptr)) noexcept {}
    MMapMemory& operator=(decltype(nullptr)) noexcept {
        _release();
        return *this;
    }

    MMapMemory(const MMapMemory& other)
        : _size_bytes(other._size_bytes)
    {
        if (other.ptr && _size_bytes > 0) {
            ptr = static_cast<T *>(mmap(nullptr, _size_bytes,
                                        PROT_READ | PROT_WRITE,
                                        MAP_SHARED | MAP_ANONYMOUS,
                                        -1, 0));
            if (ptr != MAP_FAILED) {
                if constexpr (bongocat_is_trivially_copyable<T>::value) {
                    memcpy(ptr, other.ptr, _size_bytes);
                } else {
                    // assign/copy
                    *ptr = *other.ptr;
                }
                return;
            } else {
                BONGOCAT_LOG_ERROR("mmap failed in copy constructor");
            }
        }
        _size_bytes = 0;
        ptr = nullptr;
    }
    MMapMemory& operator=(const MMapMemory& other) {
        if (this != &other) {
            _release();
            _size_bytes = other._size_bytes;
            if (_size_bytes > 0) {
                void* p = static_cast<T *>(mmap(nullptr, _size_bytes,
                                                PROT_READ | PROT_WRITE,
                                                MAP_SHARED | MAP_ANONYMOUS,
                                                -1, 0));
                if (p != MAP_FAILED) {
                    ptr = static_cast<T*>(p);
                    if constexpr (bongocat_is_trivially_copyable<T>::value) {
                        memcpy(ptr, other.ptr, _size_bytes);
                    } else {
                        // assign/copy
                        *ptr = *other.ptr;
                    }
                } else {
                    _size_bytes = 0;
                    ptr = nullptr;
                    BONGOCAT_LOG_ERROR("mmap failed in copy assignment");
                }
            }
        }
        return *this;
    }

    MMapMemory(MMapMemory&& other) noexcept
        : ptr(other.ptr), _size_bytes(other._size_bytes)
    {
        other.ptr = nullptr;
        other._size_bytes = 0;
    }
    MMapMemory& operator=(MMapMemory&& other) noexcept {
        if (this != &other) {
            _release();
            ptr = other.ptr;
            _size_bytes = other._size_bytes;
            other.ptr = nullptr;
            other._size_bytes = 0;
        }
        return *this;
    }

    void _release() {
        if (ptr) {
            munmap(ptr, _size_bytes);
            ptr = nullptr;
            _size_bytes = 0;
        }
    }

    ~MMapMemory() {
        _release();
    }

    T& operator*() {
        assert(ptr && ptr != MAP_FAILED);
        return *ptr;
    }
    const T& operator*() const {
        assert(ptr && ptr != MAP_FAILED);
        return *ptr;
    }
    T* operator->() {
        assert(ptr && ptr != MAP_FAILED);
        return ptr;
    }
    const T* operator->() const {
        assert(ptr && ptr != MAP_FAILED);
        return ptr;
    }
    operator T*() noexcept {
        return ptr;
    }
    operator const T*() const noexcept {
        return ptr;
    }

    explicit operator bool() const noexcept {
        return ptr != nullptr && ptr != MAP_FAILED;
    }

    bool operator==(decltype(nullptr)) const noexcept {
        return ptr == nullptr;
    }
    bool operator!=(decltype(nullptr)) const noexcept {
        return ptr != nullptr;
    }
};
template <typename T>
inline static MMapMemory<T> make_unallocated_mmap() {
    return MMapMemory<T>();
}
// Allocate shared memory using mmap
template <typename T>
inline static MMapMemory<T> make_allocated_mmap() {
    MMapMemory<T> ret;
    ret._size_bytes = sizeof(T);
    if (ret._size_bytes > 0) {
        ret.ptr = static_cast<T *>(mmap(nullptr, ret._size_bytes,
                                        PROT_READ | PROT_WRITE,
                                        MAP_SHARED | MAP_ANONYMOUS,
                                        -1, 0));
        if (ret.ptr && ret.ptr != MAP_FAILED) {
            if constexpr (bongocat_is_trivially_copyable<T>::value) {
                memset(ret.ptr, 0, ret._size_bytes);
            } else {
                // default ctor
                new (ret.ptr) T();
            }
            return ret;
        } else {
            BONGOCAT_LOG_ERROR("malloc failed");
        }
    }
    ret._size_bytes = 0;
    ret.ptr = nullptr;
    return ret;
}

template <typename T>
requires bongocat_is_trivially_copyable<T>::value
struct MMapArray {
    T* data{nullptr};
    size_t count{0};
    size_t _size_bytes{0};

    MMapArray() = default;

    MMapArray(decltype(nullptr)) noexcept {}
    MMapArray& operator=(decltype(nullptr)) noexcept {
        _release();
        return *this;
    }

    // Allocate shared memory using mmap and count
    explicit MMapArray(size_t p_count)
        : count(p_count), _size_bytes(sizeof(T) * count)
    {
        if (_size_bytes > 0) {
            data = static_cast<T *>(mmap(nullptr, _size_bytes,
                                         PROT_READ | PROT_WRITE,
                                         MAP_SHARED | MAP_ANONYMOUS,
                                         -1, 0));
            if (data != MAP_FAILED) {
                return;
            } else {
                BONGOCAT_LOG_ERROR("mmap buffer failed");
            }
        }
        data = nullptr;
        count = 0;
        _size_bytes = 0;
    }

    MMapArray(const MMapArray& other)
        : count(other.count), _size_bytes(other._size_bytes)
    {
        if (other.data && _size_bytes > 0) {
            data = static_cast<T *>(mmap(nullptr, _size_bytes,
                                         PROT_READ | PROT_WRITE,
                                         MAP_SHARED | MAP_ANONYMOUS,
                                         -1, 0));
            if (data != MAP_FAILED) {
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
        data = nullptr;
        count = 0;
        _size_bytes = 0;
    }
    MMapArray& operator=(const MMapArray& other) {
        if (this != &other) {
            _release();
            count = other.count;
            _size_bytes = other._size_bytes;
            if (other.data && _size_bytes > 0) {
                data = static_cast<T *>(mmap(nullptr, _size_bytes,
                                             PROT_READ | PROT_WRITE,
                                             MAP_SHARED | MAP_ANONYMOUS,
                                             -1, 0));
                if (data != MAP_FAILED) {
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
            data = nullptr;
            count = 0;
            _size_bytes = 0;
        }
        return *this;
    }

    MMapArray(MMapArray&& other) noexcept
        : data(other.data), count(other.count), _size_bytes(other._size_bytes)
    {
        other.data = nullptr;
        other.count = 0;
        other._size_bytes = 0;
    }
    MMapArray& operator=(MMapArray&& other) noexcept {
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

    // Release memory manually
    void _release() {
        if (data) {
            munmap(data, _size_bytes);
            data = nullptr;
            count = 0;
            _size_bytes = 0;
        }
    }

    ~MMapArray() {
        _release();
    }


    T& operator[](size_t index) {
        assert(index < count);
        return data[index];
    }
    const T& operator[](size_t index) const {
        assert(index < count);
        return data[index];
    }

    explicit operator bool() const noexcept {
        return data != nullptr && data != MAP_FAILED;
    }

    bool operator==(decltype(nullptr)) const noexcept {
        return data == nullptr;
    }
    bool operator!=(decltype(nullptr)) const noexcept {
        return data != nullptr;
    }
};
template <typename T>
inline static MMapArray<T> make_unallocated_mmap_array() {
    return MMapArray<T>();
}
template <typename T>
inline static MMapArray<T> make_allocated_mmap_array_uninitialized(size_t count) {
    return count > 0? MMapArray<T>(count) : MMapArray<T>();
}
template <typename T>
inline static MMapArray<T> make_allocated_mmap_array(size_t count) {
    auto ret= count > 0 ? MMapArray<T>(count) : MMapArray<T>();
    for (size_t i = 0;i < ret.size;i++) {
        new (&ret.data[i]) T();
    }
    return ret;
}

template <typename T>
requires bongocat_is_trivially_copyable<T>::value
struct MMapFile {
    T* ptr{nullptr};
    size_t _size_bytes{0};
    int _fd{-1};
    off_t _offset{0};

    MMapFile() = default;

    MMapFile(decltype(nullptr)) noexcept {}
    MMapFile& operator=(decltype(nullptr)) noexcept {
        _release();
        return *this;
    }

    MMapFile(int fd, off_t offset = 0)
        : _size_bytes(sizeof(T)), _fd(fd), _offset(offset)
    {
        if (_size_bytes > 0) {
            ptr = mmap(nullptr, _size_bytes,
                           PROT_READ | PROT_WRITE,
                           MAP_SHARED,
                           _fd, _offset);
            if (ptr != MAP_FAILED) {
                return;
            } else {
                BONGOCAT_LOG_ERROR("mmap failed to map file");
            }
        }
        ptr = nullptr;
        _size_bytes = 0;
    }

    MMapFile(const MMapFile& other)
        : _size_bytes(other._size_bytes), _fd(other._fd), _offset(other._offset)
    {
        if (other.ptr && _size_bytes > 0) {
            ptr = mmap(nullptr, _size_bytes,
                           PROT_READ | PROT_WRITE,
                           MAP_SHARED,
                           _fd, _offset);
            if (ptr != MAP_FAILED) {
                memcpy(ptr, other.ptr, _size_bytes);
                return;
            } else {
                BONGOCAT_LOG_ERROR("file mmap failed in copy constructor");
            }
        }
        ptr = nullptr;
        _size_bytes = 0;
    }
    MMapFile& operator=(const MMapFile& other) {
        if (this != &other) {
            _release();
            _size_bytes = other._size_bytes;
            _fd = other._fd;
            _offset = other._offset;
            if (other.ptr && _size_bytes > 0) {
                ptr = mmap(nullptr, _size_bytes,
                               PROT_READ | PROT_WRITE,
                               MAP_SHARED,
                               _fd, _offset);
                if (ptr) {
                    memcpy(ptr, other.ptr, _size_bytes);
                    return *this;
                } else {
                    BONGOCAT_LOG_ERROR("file mmap failed in copy assignment");
                }
            }
            _size_bytes = 0;
            ptr = nullptr;
        }
        return *this;
    }

    MMapFile(MMapFile&& other) noexcept
        : ptr(other.ptr), _size_bytes(other._size_bytes), _fd(other._fd), _offset(other._offset)
    {
        other.ptr = nullptr;
        other._size_bytes = 0;
        other._fd = -1;
        other._offset = 0;
    }
    MMapFile& operator=(MMapFile&& other) noexcept {
        if (this != &other) {
            _release();
            ptr = other.ptr;
            _size_bytes = other._size_bytes;
            _fd = other._fd;
            _offset = other._offset;
            other.ptr = nullptr;
            other._size_bytes = 0;
            other._fd = -1;
            other._offset = 0;
        }
        return *this;
    }

    // Release memory manually
    void _release() {
        if (ptr) {
            munmap(ptr, _size_bytes);
            ptr = nullptr;
            _size_bytes = 0;
            _fd = -1;
            _offset = 0;
        }
    }

    ~MMapFile() {
        _release();
    }

    T& operator*() {
        assert(ptr);
        return *ptr;
    }

    T* operator->() {
        return ptr;
    }

    explicit operator bool() const noexcept {
        return ptr != nullptr && ptr != MAP_FAILED;
    }

    bool operator==(decltype(nullptr)) const noexcept {
        return ptr == nullptr;
    }
    bool operator!=(decltype(nullptr)) const noexcept {
        return ptr != nullptr;
    }
};
template <typename T>
inline static MMapFile<T> make_unallocated_mmap_file() {
    return MMapFile<T>();
}
template <typename T>
inline static MMapFile<T> make_allocated_mmap_file(int fd, off_t offset = 0) {
    return MMapFile<T>(fd, offset);
}


template <typename T>
requires bongocat_is_trivially_copyable<T>::value
struct MMapFileBuffer {
    T* data{nullptr};
    size_t count{0};
    size_t _size_bytes{0};
    int _fd{-1};
    off_t _offset{0};

    MMapFileBuffer() = default;

    MMapFileBuffer(decltype(nullptr)) noexcept {}
    MMapFileBuffer& operator=(decltype(nullptr)) noexcept {
        _release();
        return *this;
    }

    // Allocate shared memory using mmap
    MMapFileBuffer(size_t p_count, int fd, off_t offset = 0)
        : count(p_count), _size_bytes(sizeof(T) * count), _fd(fd), _offset(offset)
    {
        if (_size_bytes > 0) {
            data = static_cast<T *>(mmap(nullptr, _size_bytes,
                                         PROT_READ | PROT_WRITE,
                                         MAP_SHARED,
                                         _fd, _offset));
            if (data != MAP_FAILED) {
                return;
            } else {
                BONGOCAT_LOG_ERROR("mmap buffer failed to map file");
            }
        }
        data = nullptr;
        count = 0;
        _size_bytes = 0;
    }

    MMapFileBuffer(const MMapFileBuffer& other)
        : count(other.count), _size_bytes(other._size_bytes), _fd(other._fd), _offset(other._offset)
    {
        if (other.data && _size_bytes > 0) {
            data = static_cast<T *>(mmap(nullptr, _size_bytes,
                                         PROT_READ | PROT_WRITE,
                                         MAP_SHARED,
                                         _fd, _offset));
            if (data != MAP_FAILED) {
                memcpy(data, other.data, _size_bytes);
                return;
            } else {
                BONGOCAT_LOG_ERROR("file mmap failed in copy constructor");
            }
        }
        data = nullptr;
        count = 0;
        _size_bytes = 0;
    }
    MMapFileBuffer& operator=(const MMapFileBuffer& other) {
        if (this != &other) {
            _release();
            count = other.count;
            _size_bytes = other._size_bytes;
            _fd = other._fd;
            _offset = other._offset;
            if (_size_bytes > 0) {
                data = static_cast<T *>(mmap(nullptr, _size_bytes,
                                             PROT_READ | PROT_WRITE,
                                             MAP_SHARED,
                                             _fd, _offset));
                if (data != MAP_FAILED) {
                    memcpy(data, other.data, _size_bytes);
                    return *this;
                } else {
                    BONGOCAT_LOG_ERROR("file mmap buffer failed in copy assignment");
                }
            }
            data = nullptr;
            count = 0;
            _size_bytes = 0;
        }
        return *this;
    }

    MMapFileBuffer(MMapFileBuffer&& other) noexcept
        : data(other.data), count(other.count), _size_bytes(other._size_bytes), _fd(other._fd), _offset(other._offset)
    {
        other.data = nullptr;
        other.count = 0;
        other._size_bytes = 0;
        other._fd = -1;
        other._offset = 0;
    }
    MMapFileBuffer& operator=(MMapFileBuffer&& other) noexcept {
        if (this != &other) {
            _release();
            data = other.data;
            count = other.count;
            _size_bytes = other._size_bytes;
            _fd = other._fd;
            _offset = other._offset;
            other.data = nullptr;
            other.count = 0;
            other._size_bytes = 0;
            other._fd = -1;
            other._offset = 0;
        }
        return *this;
    }

    // Release memory manually
    void _release() {
        if (data) {
            munmap(data, _size_bytes);
            data = nullptr;
            count = 0;
            _size_bytes = 0;
            _fd = -1;
            _offset = 0;
        }
    }

    ~MMapFileBuffer() {
        _release();
    }


    T& operator[](size_t index) {
        assert(index < count);
        return data[index];
    }
    const T& operator[](size_t index) const {
        assert(index < count);
        return data[index];
    }

    explicit operator bool() const noexcept {
        return data != nullptr && data != MAP_FAILED;
    }

    bool operator==(decltype(nullptr)) const noexcept {
        return data == nullptr;
    }
    bool operator!=(decltype(nullptr)) const noexcept {
        return data != nullptr;
    }
};
template <typename T>
inline static MMapFileBuffer<T> make_unallocated_mmap_file_buffer() {
    return MMapFileBuffer<T>();
}
template <typename T>
inline static MMapFileBuffer<T> make_allocated_mmap_file_buffer(size_t count, int fd, off_t offset = 0) {
    return MMapFileBuffer<T>(count, fd, offset);
}


struct FileDescriptor {
    int _fd{-1};

    FileDescriptor() = default;
    explicit FileDescriptor(int fd) noexcept : _fd(fd) {}

    // Construct from nullptr (reset to -1)
    FileDescriptor(decltype(nullptr)) noexcept : _fd(-1) {}

    // No copy
    FileDescriptor(const FileDescriptor&) = delete;
    FileDescriptor& operator=(const FileDescriptor&) = delete;

    // Move constructor
    FileDescriptor(FileDescriptor&& other) noexcept
        : _fd(other._fd)
    {
        other._fd = -1;
    }

    // Move assignment
    FileDescriptor& operator=(FileDescriptor&& other) noexcept {
        if (this != &other) {
            _close();
            _fd = other._fd;
            other._fd = -1;
        }
        return *this;
    }

    // Assign from nullptr
    FileDescriptor& operator=(decltype(nullptr)) noexcept {
        _close();
        return *this;
    }

    ~FileDescriptor() {
        _close();
    }

    // Close manually
    void _close() noexcept {
        if (_fd != -1) {
            ::close(_fd);
            _fd = -1;
        }
    }

    /*
    // Check if valid
    explicit(false) operator bool() const noexcept {
        return _fd != -1;
    }
    */

    // conversion to int
    operator int() const noexcept {
        return _fd;
    }
};

#endif // BONGOCAT_SYSTEM_MEMORY_H