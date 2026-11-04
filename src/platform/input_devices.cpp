#include "graphics/animation.h"
#include "platform/input.h"
#include "platform/wayland.h"
#include "utils/memory.h"

#include <cassert>
#include <cstdio>
#include <dirent.h>
#include <fcntl.h>
#include <libudev.h>
#include <linux/input.h>
#include <poll.h>
#include <pthread.h>
#include <sys/eventfd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

namespace bongocat::platform::input {

inline static constexpr auto BITS_PER_LONG{(8 * sizeof(unsigned long))};

inline static constexpr size_t NUMBERS_SIZE = 1024;
inline static constexpr size_t DEVICE_NAME_SIZE = PATH_MAX;

static bool is_keyboard(int fd) {
  static_assert(BITS_PER_LONG != 0);
  constexpr size_t bits_size = (KEY_MAX / BITS_PER_LONG) + 1;
  unsigned long bits[bits_size] = {0};
  if (ioctl(fd, EVIOCGBIT(EV_KEY, sizeof(bits)), bits) < 0) {
    return false;
  }
  static const unsigned keys[] = {KEY_A, KEY_Z, KEY_ENTER, KEY_SPACE};
  for (size_t i = 0; i < LEN_ARRAY(keys); i++) {
    if (!(bits[keys[i] / BITS_PER_LONG] & (1UL << (keys[i] % BITS_PER_LONG)))) {
      return false;
    }
  }
  return true;
}

static void device_name(int fd, char *name, size_t size) {
  memset(name, 0, size);
  if (ioctl(fd, EVIOCGNAME(size - 1), name) < 0) {
    name[0] = '\0';
  }
}

// Explicit paths match by device number, so by-id and by-path links work.
// Without selectors every keyboard is used.
/*
static bool device_selected(int fd, dev_t identity, char *const *paths,
                            int num_paths, char *const *names, int num_names) {
  if (!num_paths && !num_names) {
    return is_keyboard(fd);
  }
  for (int i = 0; i < num_paths; i++) {
    struct stat selected;
    if (stat(paths[i], &selected) == 0 && S_ISCHR(selected.st_mode) &&
        selected.st_rdev == identity) {
      return true;
    }
  }
  if (num_names) {
    char name[256];
    device_name(fd, name, sizeof(name));
    for (int i = 0; i < num_names; i++) {
      if (strstr(name, names[i])) {
        return true;
      }
    }
  }
  return false;
}
*/

static bool event_node(const char *name, unsigned *number) {
  char *end{BONGOCAT_NULLPTR};
  if (strncmp(name, "event", 5) != 0 || !name[5]) {
    return false;
  }
  errno = 0;
  unsigned long value = strtoul(name + 5, &end, 10);
  if (errno || *end || value > UINT_MAX) {
    return false;
  }
  *number = static_cast<unsigned>(value);
  return true;
}

static int compare_unsigned(const void *a, const void *b) {
  unsigned x = *static_cast<const unsigned *>(a);
  unsigned y = *static_cast<const unsigned *>(b);
  return (x > y) - (x < y);
}

// Prints the /dev/input/by-id links that resolve to path.
static bool print_links(const char *path, const cli_list_devices_args_t& args) {
  bool ret = false;
  DIR *dir = opendir("/dev/input/by-id");

  struct dirent *entry;
  while (dir && (entry = readdir(dir))) {
    char link[PATH_MAX] = {0};
    char target[PATH_MAX] = {0};
    if (entry->d_name[0] != '.' &&
        snprintf(link, sizeof(link), "/dev/input/by-id/%s", entry->d_name) < static_cast<int>(sizeof(link)) &&
        realpath(link, target) && strcmp(target, path) == 0) {
      if (args.config_format) {
        printf("keyboard_device=%s\n", link);
      } else {
        printf("    keyboard_device=%s\n", link);
      }
      ret = true;
    }
  }

  if (dir) {
    closedir(dir);
  }

  return ret;
}

int cli_list_devices(input_context_t& ctx, const cli_list_devices_args_t& args) {
  DIR *dir = opendir("/dev/input");
  if (!dir) {
    fprintf(stderr, "/dev/input: %s\n", strerror(errno));
    return EXIT_FAILURE;
  }
  unsigned numbers[NUMBERS_SIZE] = {0};
  size_t count = 0;
  struct dirent *entry;
  while ((entry = readdir(dir)) && count < NUMBERS_SIZE) {
    count += event_node(entry->d_name, &numbers[count]);
  }
  closedir(dir);

  qsort(numbers, count, sizeof(*numbers), compare_unsigned);
  unsigned keyboards = 0;
  for (size_t i = 0; i < count; i++) {
    char path[PATH_MAX] = {0};
    snprintf(path, sizeof(path), "/dev/input/event%u", numbers[i]);

    (void)details::privilege_raise(ctx);
    FileDescriptor fd(open(path, O_RDONLY | O_NONBLOCK | O_CLOEXEC));
    (void)details::privilege_lower(ctx);

    if (fd._fd < 0) {
      printf("%s: inaccessible (%s)\n", path, strerror(errno));
      continue;
    }

    char name[DEVICE_NAME_SIZE] = {0};
    device_name(fd._fd, name, sizeof(name));

    const bool keyboard = is_keyboard(fd._fd);
    close_fd(fd);
    if (args.config_format) {
      printf("# %s%s\n", name, keyboard ? " [keyboard]" : "");
    } else {
      printf("%s: %s%s\n", path, name, keyboard ? " [keyboard]" : "");
    }
    if (keyboard) {
      keyboards++;
      if (args.config_format) {
        printf("keyboard_name=%s\n", name);
      } else {
        printf("    keyboard_name=%s\n", name);
      }
      print_links(path, args);
    }
  }
  if (keyboards == 0) {
    fprintf(stderr, "No accessible keyboards; check device ACLs or input group membership.\n");
  }

  return keyboards > 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}

}  // namespace bongocat::platform::input
