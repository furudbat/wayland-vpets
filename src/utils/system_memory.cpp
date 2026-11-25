#include "utils/system_memory.h"

#include "utils/error.h"
#include "utils/time.h"

#include <cerrno>
#include <cstring>
#include <ctime>
#include <poll.h>
#include <pthread.h>

namespace bongocat::platform {
static constexpr time_ms_t THREAD_JOIN_TIMEOUT_MS = 5000;  // maximum wait for graceful exit
static constexpr time_ms_t THREAD_SlEEP_WHEN_WAITING_FOR_THREAD_MS = 100;
static constexpr int THREAD_JOIN_MAX_ATTEMPTS = 2048;
static constexpr int MAX_PPOOL_WAKE_ATTEMPTS = 4096;

int join_thread_with_timeout(pthread_t& thread, time_ms_t timeout_ms) {
  if (thread == 0) {
    return 0;
  }

  // block until the thread exits (or deadline), no polling granularity
  timespec deadline{};
  clock_gettime(CLOCK_REALTIME, &deadline);
  deadline.tv_sec += timeout_ms / 1000;
  deadline.tv_nsec += (timeout_ms % 1000) * 1000000L;
  if (deadline.tv_nsec >= 1000000000L) {
    deadline.tv_sec += 1;
    deadline.tv_nsec -= 1000000000L;
  }

  int ret = 0;
  int attempts = 0;
  do {
    ret = pthread_timedjoin_np(thread, BONGOCAT_NULLPTR, &deadline);
    attempts++;
  } while (ret == EINTR && attempts < THREAD_JOIN_MAX_ATTEMPTS);
  if (ret == 0) {
    thread = 0;
  }
  return ret;
}

void wake_eventfd(int efd) noexcept {
  if (efd < 0) {
    return;
  }
  const uint64_t u = 1;
  [[maybe_unused]] const ssize_t ret = write(efd, &u, sizeof(u));
}

static bool ppoll_wake_fd(int wake_fd, const struct timespec *rel_timeout) noexcept {
  pollfd pfd = {.fd = wake_fd, .events = POLLIN, .revents = 0};
  int attempts = 0;
  while (attempts < MAX_PPOOL_WAKE_ATTEMPTS) {
    const int ret = ppoll(&pfd, wake_fd >= 0 ? 1 : 0, rel_timeout, BONGOCAT_NULLPTR);
    attempts++;
    if (ret < 0 && errno == EINTR) {
      // @NOTE: rel_timeout is not updated, interrupted sleep can be a bit longer
      continue;
    }
    return ret != 0;
  }
  return false;
}

bool sleep_or_wake(int wake_fd, time_ms_t timeout_ms) noexcept {
  if (timeout_ms <= 0) {
    return false;
  }
  struct timespec ts{};
  ts.tv_sec = timeout_ms / 1000;
  ts.tv_nsec = (timeout_ms % 1000) * 1000000L;
  return ppoll_wake_fd(wake_fd, &ts);
}

bool sleep_until_or_wake(int wake_fd, const struct timespec& abs_time) noexcept {
  struct timespec now{};
  clock_gettime(CLOCK_MONOTONIC, &now);
  struct timespec rel = {.tv_sec = abs_time.tv_sec - now.tv_sec, .tv_nsec = abs_time.tv_nsec - now.tv_nsec};
  if (rel.tv_nsec < 0) {
    rel.tv_nsec += 1000000000L;
    rel.tv_sec -= 1;
  }
  if (rel.tv_sec < 0) {
    return false;
  }
  return ppoll_wake_fd(wake_fd, &rel);
}

int stop_thread_graceful_or_cancel(pthread_t& thread, atomic_bool& running_flag) {
  if (thread == 0) {
    return 0;
  }

  atomic_store(&running_flag, false);
  const int ret = join_thread_with_timeout(thread, THREAD_JOIN_TIMEOUT_MS);
  if (thread != 0 && ret == ETIMEDOUT) {
    BONGOCAT_LOG_WARNING("Thread did not exit in time, cancelling: %dms", THREAD_JOIN_TIMEOUT_MS);
    pthread_cancel(thread);
    pthread_join(thread, BONGOCAT_NULLPTR);
  }

  thread = 0;

  return ret;
}

namespace {
  struct page_region_t {
    uintptr_t begin{0};
    size_t size{0};
    size_t page_size{4096};
    bool valid{false};  ///< page-aligned (or empty)
  };

  page_region_t get_page_region(const char *start, const char *stop, [[maybe_unused]] const char *name) {
    page_region_t ret;
    const uintptr_t begin = reinterpret_cast<uintptr_t>(start);
    const uintptr_t end = reinterpret_cast<uintptr_t>(stop);
    // weak range symbols of a set that is not linked are both null => empty
    if (start == BONGOCAT_NULLPTR || stop == BONGOCAT_NULLPTR || end <= begin) {
      ret.valid = true;
      return ret;
    }

    // the linker script aligns both ends to MAXPAGESIZE (>= runtime page size);
    // madvise needs a page-aligned start, a misaligned end would be rounded up into the next section
    const long sys_page_size = sysconf(_SC_PAGESIZE);
    ret.page_size = sys_page_size > 0 ? static_cast<size_t>(sys_page_size) : 4096;
    assert(begin % ret.page_size == 0);
    assert(end % ret.page_size == 0);
    if (begin % ret.page_size != 0 || end % ret.page_size != 0) [[unlikely]] {
      BONGOCAT_LOG_WARNING("madvise: %s is not page-aligned (page size: %zu), skip", name, ret.page_size);
      return ret;
    }
    ret.begin = begin;
    ret.size = end - begin;
    ret.valid = true;
    return ret;
  }
}  // namespace

size_t resident_region_bytes(const char *start, const char *stop) {
  const page_region_t region = get_page_region(start, stop, "region");
  if (!region.valid || region.size == 0) {
    return 0;
  }
  // NOT mincore(): for file mappings it reports the page cache, not what is mapped into THIS process (RSS).
  // /proc/self/pagemap: 8 bytes per page, bit 63 = present (readable without privileges, only the PFN is hidden)
  const int fd = open("/proc/self/pagemap", O_RDONLY | O_CLOEXEC);
  if (fd < 0) {
    return 0;
  }
  static constexpr size_t CHUNK_PAGES = 256;
  uint64_t entries[CHUNK_PAGES];
  const size_t total_pages = region.size / region.page_size;
  const size_t first_page = region.begin / region.page_size;
  size_t resident_pages = 0;
  for (size_t page = 0; page < total_pages; page += CHUNK_PAGES) {
    const size_t count = (total_pages - page) < CHUNK_PAGES ? (total_pages - page) : CHUNK_PAGES;
    const ssize_t read_bytes =
        pread(fd, entries, count * sizeof(uint64_t), static_cast<off_t>((first_page + page) * sizeof(uint64_t)));
    if (read_bytes <= 0) {
      break;
    }
    const size_t read_entries = static_cast<size_t>(read_bytes) / sizeof(uint64_t);
    for (size_t i = 0; i < read_entries; ++i) {
      resident_pages += (entries[i] >> 63) & 1u;
    }
  }
  close(fd);
  return resident_pages * region.page_size;
}

bool advise_random_access_region(const char *start, const char *stop, [[maybe_unused]] const char *name) {
  const page_region_t region = get_page_region(start, stop, name);
  if (!region.valid) [[unlikely]] {
    return false;
  }
  if (region.size == 0) {
    return true;
  }
  if (madvise(reinterpret_cast<void *>(region.begin), region.size, MADV_RANDOM) != 0) {
    BONGOCAT_LOG_WARNING("madvise: failed to set random access for %s: %s", name, strerror(errno));
    return false;
  }
  BONGOCAT_LOG_VERBOSE("madvise: random access for %s: %zu kb", name, region.size / 1024);
  return true;
}

bool prefetch_readonly_region(const char *start, const char *stop, [[maybe_unused]] const char *name) {
  const page_region_t region = get_page_region(start, stop, name);
  if (!region.valid) [[unlikely]] {
    return false;
  }
  if (region.size == 0) {
    return true;
  }
  if (madvise(reinterpret_cast<void *>(region.begin), region.size, MADV_WILLNEED) != 0) {
    BONGOCAT_LOG_WARNING("madvise: failed to prefetch %s: %s", name, strerror(errno));
    return false;
  }
  BONGOCAT_LOG_VERBOSE("madvise: prefetch %s: %zu kb", name, region.size / 1024);
  return true;
}

bool evict_readonly_region(const char *start, const char *stop, [[maybe_unused]] const char *name) {
  const page_region_t region = get_page_region(start, stop, name);
  if (!region.valid) [[unlikely]] {
    return false;
  }
  if (region.size == 0) {
    // empty block, e.g. set not linked or no assets of that kind in this build
    return true;
  }

#if (!defined(BONGOCAT_DISABLE_LOGGER) || defined(BONGOCAT_ENABLE_LOGGER)) && BONGOCAT_LOG_LEVEL >= 5
  // how much of the region was actually paged in by this load (should be just the used images/tables)
  const size_t resident = resident_region_bytes(start, stop);
#endif
  if (madvise(reinterpret_cast<void *>(region.begin), region.size, MADV_DONTNEED) != 0) {
    BONGOCAT_LOG_WARNING("madvise: failed to evict %s: %s", name, strerror(errno));
    return false;
  }
  BONGOCAT_LOG_VERBOSE("madvise: evicted %s: %zu kb resident of %zu kb", name, resident / 1024, region.size / 1024);
  return true;
}
}  // namespace bongocat::platform