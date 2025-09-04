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
            pthread_mutexattr_t attr;
            pthread_mutexattr_init(&attr);
            pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_ERRORCHECK);
            if (pthread_mutex_init(&pt_mutex, &attr) != 0) {
                BONGOCAT_LOG_ERROR("Failed to initialize mutex");
            }
            pthread_mutexattr_destroy(&attr);
        }
        ~Mutex() {
            int rc = pthread_mutex_destroy(&pt_mutex);
            if (rc == EBUSY) {
                // still locked → try to unlock first
                rc = pthread_mutex_unlock(&pt_mutex);
                if (rc != 0) {
                    BONGOCAT_LOG_ERROR("pthread_mutex_unlock in destructor failed");
                }
                pthread_mutex_destroy(&pt_mutex);
            } else if (rc != 0) {
                BONGOCAT_LOG_ERROR("pthread_mutex_destroy failed");
            }
        }

        Mutex(const Mutex&) = delete;
        Mutex& operator=(const Mutex&) = delete;
        Mutex(Mutex&&) = delete;
        Mutex& operator=(Mutex&&) = delete;

        void _lock() {
            if (const int rc = pthread_mutex_lock(&pt_mutex); rc != 0) {
                BONGOCAT_LOG_ERROR("pthread_mutex_lock failed");
            }
        }
        void _unlock() {
            if (const int rc = pthread_mutex_unlock(&pt_mutex); rc != 0) {
                if (rc != EPERM) { // ignore "not owner"
                    BONGOCAT_LOG_ERROR("pthread_mutex_unlock failed");
                }
            }
        }

        /*
        explicit operator pthread_mutex_t() const noexcept {
            return pt_mutex;
        }
        */
    };
    struct LockGuard {
        explicit LockGuard(Mutex& m) : pt_mutex(&m.pt_mutex) {
            if (const int rc = pthread_mutex_lock(pt_mutex); rc != 0) {
                BONGOCAT_LOG_ERROR("LockGuard: pthread_mutex_lock failed");
            }
        }
        explicit LockGuard(pthread_mutex_t& m) : pt_mutex(&m) {
            if (const int rc = pthread_mutex_lock(pt_mutex); rc != 0) {
                BONGOCAT_LOG_ERROR("LockGuard: pthread_mutex_lock failed");
            }
        }
        ~LockGuard() {
          if (const int rc = pthread_mutex_unlock(pt_mutex); rc != 0) {
                BONGOCAT_LOG_ERROR("LockGuard: pthread_mutex_unlock failed");
            }
        }

        // No copying, no move
        LockGuard(const LockGuard&) = delete;
        LockGuard& operator=(const LockGuard&) = delete;
        LockGuard(const LockGuard&&) = delete;
        LockGuard&& operator=(const LockGuard&&) = delete;

        pthread_mutex_t *pt_mutex{nullptr};
    };

    struct SingleCondVariable;
    void cond_destroy(SingleCondVariable& cond);
    struct SingleCondVariable {
        Mutex mutex;
        pthread_cond_t cond;
        atomic_bool _predicate{false};
        bool _inited{false};

        SingleCondVariable() {
            pthread_cond_init(&cond, nullptr);
            _inited = true;
        }

        ~SingleCondVariable() {
            cond_destroy(*this);
        }

        // No copying, no move
        SingleCondVariable(const SingleCondVariable&) = delete;
        SingleCondVariable& operator=(const SingleCondVariable&) = delete;
        SingleCondVariable(const SingleCondVariable&&) = delete;
        SingleCondVariable&& operator=(const SingleCondVariable&&) = delete;
    };
    inline void cond_destroy(SingleCondVariable& cond) {
        atomic_store(&cond._predicate, true);
        if (cond._inited) pthread_cond_broadcast(&cond.cond);
        if (cond._inited) pthread_cond_destroy(&cond.cond);
        cond._inited = false;
    }

    struct CondVariable {
        CondVariable() {
            pthread_mutex_init(&_mutex, nullptr);
            pthread_cond_init(&_cond, nullptr);
        }

        // No copying, no move
        CondVariable(const CondVariable&) = delete;
        CondVariable& operator=(const CondVariable&) = delete;
        CondVariable(const CondVariable&&) = delete;
        CondVariable&& operator=(const CondVariable&&) = delete;

        ~CondVariable() {
            pthread_cond_broadcast(&_cond);
            pthread_cond_destroy(&_cond);
            pthread_mutex_destroy(&_mutex);
        }

        template <typename Predicate>
        [[deprecated("better use timedwait")]] int wait(Predicate&& pred) {
            int ret = 0;
            pthread_mutex_lock(&_mutex);
            while (!pred()) {
                ret = pthread_cond_wait(&_cond, &_mutex);
            }
            pthread_mutex_unlock(&_mutex);
            return ret;
        }

        template <typename Predicate>
        int timedwait(Predicate&& pred, time_ms_t timeout_ms) {
            struct timespec ts;
            clock_gettime(CLOCK_REALTIME, &ts);
            ts.tv_sec  += timeout_ms / 1000;
            ts.tv_nsec += (timeout_ms % 1000) * 1000000LL;
            // normalize time
            if (ts.tv_nsec >= 1000000000LL) {
                ts.tv_sec++;
                ts.tv_nsec -= 1000000000LL;
            }

            int ret = 0;
            pthread_mutex_lock(&_mutex);
            while (!pred()) {
                ret = pthread_cond_timedwait(&_cond, &_mutex, &ts);
                if (ret == ETIMEDOUT) {
                    pthread_mutex_unlock(&_mutex);
                    return ret;
                }
            }
            pthread_mutex_unlock(&_mutex);
            return ret;
        }

        void notify_all() {
            pthread_mutex_lock(&_mutex);
            pthread_cond_broadcast(&_cond);
            pthread_mutex_unlock(&_mutex);
        }

        pthread_mutex_t _mutex;
        pthread_cond_t _cond;
    };

    struct CondVarGuard {
        explicit CondVarGuard(pthread_mutex_t& m, pthread_cond_t& c, atomic_bool& pred)
            : _mutex(m), _cond(c), _predicate(pred)
        {
            pthread_mutex_lock(&_mutex);
        }
        explicit CondVarGuard(SingleCondVariable& cond)
            : _mutex(cond.mutex.pt_mutex), _cond(cond.cond), _predicate(cond._predicate)
        {
            pthread_mutex_lock(&_mutex);
        }

        ~CondVarGuard() {
            pthread_mutex_unlock(&_mutex);
        }

        // No copying, no move
        CondVarGuard(const CondVarGuard&) = delete;
        CondVariable& operator=(const CondVarGuard&) = delete;
        CondVarGuard(const CondVarGuard&&) = delete;
        CondVarGuard&& operator=(const CondVarGuard&&) = delete;

        // Wait until predicate becomes true
        [[deprecated("better use timedwait")]] int wait() {
            int ret = 0;
            while (!atomic_load(&_predicate)) {
                ret = pthread_cond_wait(&_cond, &_mutex);
            }
            return ret;
        }

        int timedwait(time_ms_t timeout) {
            struct timespec ts;
            clock_gettime(CLOCK_REALTIME, &ts);
            ts.tv_sec  += timeout / 1000;
            ts.tv_nsec += (timeout % 1000) * 1000000LL;
            // normalize time
            if (ts.tv_nsec >= 1000000000LL) {
                ts.tv_sec++;
                ts.tv_nsec -= 1000000000LL;
            }

            int ret = 0;
            while (!atomic_load(&_predicate)) {
                ret = pthread_cond_timedwait(&_cond, &_mutex, &ts);
            }
            return ret;
        }

        // Set predicate and signal all waiting threads
        void notify() {
            atomic_store(&_predicate, true);
            pthread_cond_broadcast(&_cond);
        }

        pthread_mutex_t& _mutex;
        pthread_cond_t& _cond;
        atomic_bool& _predicate;
    };


    template<typename T>
    struct MMapMemory;
    template<typename T>
    void release_allocated_mmap_memory(MMapMemory<T>& memory) noexcept;

    template <typename T>
    struct MMapMemory {
        T* ptr{nullptr};
        size_t _size_bytes{0};

        constexpr MMapMemory() = default;
        ~MMapMemory() noexcept {
            release_allocated_mmap_memory(*this);
        }

        explicit MMapMemory(decltype(nullptr)) noexcept {}
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
        constexpr const T& operator*() const {
            assert(ptr && ptr != MAP_FAILED);
            return *ptr;
        }
        T* operator->() {
            assert(ptr && ptr != MAP_FAILED);
            return ptr;
        }
        constexpr const T* operator->() const {
            assert(ptr && ptr != MAP_FAILED);
            return ptr;
        }
        explicit operator T*() noexcept {
            return ptr;
        }
        constexpr explicit operator const T*() const noexcept {
            return ptr;
        }

        constexpr explicit operator bool() const noexcept {
            return ptr != nullptr && ptr != MAP_FAILED;
        }

        constexpr bool operator==(decltype(nullptr)) const noexcept {
            return ptr == nullptr;
        }
        constexpr bool operator!=(decltype(nullptr)) const noexcept {
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

        constexpr MMapArray() = default;
        ~MMapArray() noexcept {
            release_allocated_mmap_array(*this);
        }

        explicit MMapArray(decltype(nullptr)) noexcept {}
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
                                data[i] = other.data[i];
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
        constexpr const T& operator[](size_t index) const {
            assert(index < count);
            return data[index];
        }

        constexpr explicit operator bool() const noexcept {
            return data != nullptr && data != MAP_FAILED;
        }

        constexpr bool operator==(decltype(nullptr)) const noexcept {
            return data == nullptr;
        }
        constexpr bool operator!=(decltype(nullptr)) const noexcept {
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
        for (size_t i = 0;i < ret.count;i++) {
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

        constexpr MMapFile() = default;
        ~MMapFile() noexcept {
            release_allocated_mmap_file(*this);
        }

        explicit MMapFile(decltype(nullptr)) noexcept {}
        MMapFile& operator=(decltype(nullptr)) noexcept {
            release_allocated_mmap_file(*this);
            return *this;
        }

        explicit MMapFile(int fd, off_t offset = 0)
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

        constexpr explicit operator bool() const noexcept {
            return ptr != nullptr && ptr != MAP_FAILED;
        }

        constexpr bool operator==(decltype(nullptr)) const noexcept {
            return ptr == nullptr;
        }
        constexpr bool operator!=(decltype(nullptr)) const noexcept {
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

        constexpr MMapFileBuffer() = default;
        ~MMapFileBuffer() noexcept {
            release_allocated_mmap_file_buffer(*this);
        }

        explicit MMapFileBuffer(decltype(nullptr)) noexcept {}
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

        constexpr explicit operator bool() const noexcept {
            return data != nullptr && data != MAP_FAILED;
        }

        constexpr bool operator==(decltype(nullptr)) const noexcept {
            return data == nullptr;
        }
        constexpr bool operator!=(decltype(nullptr)) const noexcept {
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

        constexpr FileDescriptor() = default;
        explicit FileDescriptor(int fd) noexcept : _fd(fd) {}
        ~FileDescriptor() noexcept {
            close_fd(*this);
        }

        explicit FileDescriptor(decltype(nullptr)) noexcept {}
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