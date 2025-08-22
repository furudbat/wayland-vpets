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

namespace bongocat::platform {
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

        Mutex(const Mutex&) = delete;
        Mutex& operator=(const Mutex&) = delete;

        Mutex(Mutex&& other) noexcept {
            pt_mutex = other.pt_mutex;
            other.pt_mutex = PTHREAD_MUTEX_INITIALIZER;
        }
        Mutex& operator=(Mutex&& other) noexcept {
            if (this != &other) {
                pt_mutex = other.pt_mutex;
                other.pt_mutex = PTHREAD_MUTEX_INITIALIZER;
            }
            return *this;
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

        /*
        explicit operator pthread_mutex_t() const noexcept {
            return pt_mutex;
        }
        */
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

    template<typename T>
    struct MMapMemory;
    template<typename T>
    void release_allocated_mmap_memory(MMapMemory<T>& memory) noexcept;

    template <typename T>
    struct MMapMemory {
        T* ptr{nullptr};
        size_t _size_bytes{0};

        MMapMemory() = default;
        ~MMapMemory() noexcept {
            release_allocated_mmap_memory(*this);
        }

        MMapMemory(decltype(nullptr)) noexcept {}
        MMapMemory& operator=(decltype(nullptr)) noexcept {
            release_allocated_mmap_memory(*this);
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
                    if constexpr (is_trivially_copyable<T>::value) {
                        memcpy(ptr, other.ptr, _size_bytes);
                    } else {
                        // assign/copy
                        new (ptr) T(*other.ptr);
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
                release_allocated_mmap_memory(*this);
                _size_bytes = other._size_bytes;
                if (_size_bytes > 0) {
                    ptr = static_cast<T *>(mmap(nullptr, _size_bytes,
                                                    PROT_READ | PROT_WRITE,
                                                    MAP_SHARED | MAP_ANONYMOUS,
                                                    -1, 0));
                    if (ptr != MAP_FAILED) {
                        if constexpr (is_trivially_copyable<T>::value) {
                            memcpy(ptr, other.ptr, _size_bytes);
                        } else {
                            // assign/copy
                            new (ptr) T(*other.ptr);
                        }
                        return *this;
                    } else {
                        BONGOCAT_LOG_ERROR("mmap failed in copy assignment");
                    }
                }
                _size_bytes = 0;
                ptr = nullptr;
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
                release_allocated_mmap_memory(*this);
                ptr = other.ptr;
                _size_bytes = other._size_bytes;
                other.ptr = nullptr;
                other._size_bytes = 0;
            }
            return *this;
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
    template<typename T>
    void release_allocated_mmap_memory(MMapMemory<T>& memory) noexcept {
        if (memory.ptr != nullptr) {
            if constexpr (!is_trivially_destructible<T>::value) {
                memory.ptr->~T();
            }
            munmap(memory.ptr, memory._size_bytes);
            memory.ptr = nullptr;
            memory._size_bytes = 0;
        }
    }
    template <typename T>
    inline static MMapMemory<T> make_unallocated_mmap() noexcept {
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
                // default ctor
                new (ret.ptr) T();
                return ret;
            } else {
                BONGOCAT_LOG_ERROR("mmap failed");
            }
        }
        ret.ptr = nullptr;
        ret._size_bytes = 0;
        return ret;
    }
    template <typename T>
    inline static MMapMemory<T> make_unallocated_mmap_value(const T& value) {
        auto ret = make_allocated_mmap<T>();
        if (ret.ptr != nullptr) {
            *ret.ptr = value;
        }
        return ret;
    }


    template<typename T>
    struct MMapArray;
    template<typename T>
    void release_allocated_mmap_array(MMapArray<T>& memory) noexcept;

    template <typename T>
    struct MMapArray {
        T* data{nullptr};
        size_t count{0};
        size_t _size_bytes{0};

        MMapArray() = default;
        ~MMapArray() noexcept {
            release_allocated_mmap_array(*this);
        }

        MMapArray(decltype(nullptr)) noexcept {}
        MMapArray& operator=(decltype(nullptr)) noexcept {
            release_allocated_mmap_array(*this);
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
            data = nullptr;
            count = 0;
            _size_bytes = 0;
        }
        MMapArray& operator=(const MMapArray& other) {
            if (this != &other) {
                release_allocated_mmap_array(*this);
                count = other.count;
                _size_bytes = other._size_bytes;
                if (other.data && _size_bytes > 0) {
                    data = static_cast<T *>(mmap(nullptr, _size_bytes,
                                                 PROT_READ | PROT_WRITE,
                                                 MAP_SHARED | MAP_ANONYMOUS,
                                                 -1, 0));
                    if (data != MAP_FAILED) {
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
                release_allocated_mmap_array(*this);
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
    template<typename T>
    void release_allocated_mmap_array(MMapArray<T>& memory) noexcept {
        if (memory.data) {
            if constexpr (!is_trivially_destructible<T>::value) {
                for (size_t i = 0; i < memory.count; i++) {
                    memory.data[i].~T();
                }
            }
            munmap(memory.data, memory._size_bytes);
            memory.data = nullptr;
            memory.count = 0;
            memory._size_bytes = 0;
        }
    }
    template <typename T>
    inline static MMapArray<T> make_unallocated_mmap_array() noexcept {
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

    template<typename T>
    struct MMapFile;
    template<typename T>
    void release_allocated_mmap_file(MMapFile<T>& memory) noexcept;

    template <typename T>
    struct MMapFile {
        T* ptr{nullptr};
        size_t _size_bytes{0};
        int _fd{-1};
        off_t _offset{0};

        MMapFile() = default;
        ~MMapFile() noexcept {
            release_allocated_mmap_file(*this);
        }

        MMapFile(decltype(nullptr)) noexcept {}
        MMapFile& operator=(decltype(nullptr)) noexcept {
            release_allocated_mmap_file(*this);
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
                    if constexpr (is_trivially_copyable<T>::value) {
                        memcpy(ptr, other.ptr, _size_bytes);
                    } else {
                        new (ptr) T(*other.ptr);
                    }
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
                release_allocated_mmap_file(*this);
                _size_bytes = other._size_bytes;
                _fd = other._fd;
                _offset = other._offset;
                if (other.ptr && _size_bytes > 0) {
                    ptr = mmap(nullptr, _size_bytes,
                                   PROT_READ | PROT_WRITE,
                                   MAP_SHARED,
                                   _fd, _offset);
                    if (ptr) {
                        if constexpr (is_trivially_copyable<T>::value) {
                            memcpy(ptr, other.ptr, _size_bytes);
                        } else {
                            new (ptr) T(*other.ptr);
                        }
                        return *this;
                    } else {
                        BONGOCAT_LOG_ERROR("file mmap failed in copy assignment");
                    }
                }
                ptr = nullptr;
                _size_bytes = 0;
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
                release_allocated_mmap_file(*this);
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
    void release_allocated_mmap_file(MMapFile<T>& memory) noexcept {
        if (memory.ptr) {
            if constexpr (!is_trivially_destructible<T>::value) {
                memory.ptr->~T();
            }
            munmap(memory.ptr, memory._size_bytes);
            memory.ptr = nullptr;
            memory._size_bytes = 0;
            memory._fd = -1;
            memory._offset = 0;
        }
    }
    template <typename T>
    inline static MMapFile<T> make_unallocated_mmap_file() noexcept {
        return MMapFile<T>();
    }
    template <typename T>
    inline static MMapFile<T> make_allocated_mmap_file_uninitialized(int fd, off_t offset = 0) {
        return MMapFile<T>(fd, offset);
    }
    template <typename T>
    inline static MMapFile<T> make_allocated_mmap_file_defaulted(int fd, off_t offset = 0) {
        auto ret = MMapFile<T>(fd, offset);
        if (ret.ptr) {
            new (ret.ptr) T();
        }
        return ret;
    }
    template <typename T>
    inline static MMapFile<T> make_allocated_mmap_file_value(const T& value, int fd, off_t offset = 0) {
        auto ret = MMapFile<T>(fd, offset);
        for (size_t i = 0;i < ret.size;i++) {
            *ret.ptr = value;
        }
        return ret;
    }


    template<typename T>
    struct MMapFileBuffer;
    template<typename T>
    void release_allocated_mmap_file_buffer(MMapFileBuffer<T>& memory) noexcept;

    template <typename T>
    struct MMapFileBuffer {
        T* data{nullptr};
        size_t count{0};
        size_t _size_bytes{0};
        int _fd{-1};
        off_t _offset{0};

        MMapFileBuffer() = default;
        ~MMapFileBuffer() noexcept {
            release_allocated_mmap_file_buffer(*this);
        }

        MMapFileBuffer(decltype(nullptr)) noexcept {}
        MMapFileBuffer& operator=(decltype(nullptr)) noexcept {
            release_allocated_mmap_file_buffer(*this);
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
            data = nullptr;
            count = 0;
            _size_bytes = 0;
        }
        MMapFileBuffer& operator=(const MMapFileBuffer& other) {
            if (this != &other) {
                release_allocated_mmap_file(*this);
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
                        if constexpr (is_trivially_copyable<T>::value) {
                            memcpy(data, other.data, _size_bytes);
                        } else {
                            for (size_t i = 0; i < other.count; i++) {
                                *data[i] = *other.data[i];
                            }
                        }
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
                release_allocated_mmap_file_buffer(*this);
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
    void release_allocated_mmap_file_buffer(MMapFileBuffer<T>& memory) noexcept {
        if (memory.data) {
            if constexpr (!is_trivially_destructible<T>::value) {
                for (size_t i = 0; i < memory.count; i++) {
                    memory.data[i].~T();
                }
            }
            munmap(memory.data, memory._size_bytes);
            memory.data = nullptr;
            memory.count = 0;
            memory._size_bytes = 0;
            memory._fd = -1;
            memory._offset = 0;
        }
    }
    template <typename T>
    inline static MMapFileBuffer<T> make_unallocated_mmap_file_buffer() {
        return MMapFileBuffer<T>();
    }
    template <typename T>
    inline static MMapFileBuffer<T> make_allocated_mmap_file_buffer_uninitialized(size_t count, int fd, off_t offset = 0) {
        return MMapFileBuffer<T>(count, fd, offset);
    }
    template <typename T>
    inline static MMapFileBuffer<T> make_allocated_mmap_file_buffer_defaulted(size_t count, int fd, off_t offset = 0) {
        auto ret = count > 0 ? MMapFileBuffer<T>(count, fd, offset) : MMapFileBuffer<T>();
        for (size_t i = 0;i < ret.count;i++) {
            new (&ret.data[i]) T();
        }
        return ret;
    }
    template <typename T>
    inline static MMapFileBuffer<T> make_allocated_mmap_file_buffer_value(const T& value, size_t count, int fd, off_t offset = 0) {
        auto ret = count > 0 ? MMapFileBuffer<T>(count, fd, offset) : MMapFileBuffer<T>();
        for (size_t i = 0;i < ret.count;i++) {
            ret.data[i] = value;
        }
        return ret;
    }

    struct FileDescriptor;
    void close_fd(FileDescriptor& fd) noexcept;

    struct FileDescriptor {
        int _fd{-1};

        FileDescriptor() = default;
        explicit FileDescriptor(int fd) noexcept : _fd(fd) {}
        ~FileDescriptor() noexcept {
            close_fd(*this);
        }

        FileDescriptor(decltype(nullptr)) noexcept {}
        FileDescriptor& operator=(decltype(nullptr)) noexcept {
            close_fd(*this);
            return *this;
        }

        FileDescriptor(const FileDescriptor&) = delete;
        FileDescriptor& operator=(const FileDescriptor&) = delete;

        FileDescriptor(FileDescriptor&& other) noexcept
            : _fd(other._fd)
        {
            other._fd = -1;
        }
        FileDescriptor& operator=(FileDescriptor&& other) noexcept {
            if (this != &other) {
                close_fd(*this);
                _fd = other._fd;
                other._fd = -1;
            }
            return *this;
        }

        // Check if valid
        /*
        explicit(false) operator bool() const noexcept {
            return _fd >= 0;
        }
        */

        // conversion to int
        /*
        explicit operator int() const noexcept {
            return _fd;
        }
        */
    };
    inline void close_fd(FileDescriptor& fd) noexcept {
        if (fd._fd >= 0) {
            ::close(fd._fd);
            fd._fd = -1;
        }
    }
}

#endif // BONGOCAT_SYSTEM_MEMORY_H