#include "wayland_sway.h"

#include "utils/error.h"

#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fcntl.h>
#include <pthread.h>
#include <sys/signalfd.h>
#include <sys/types.h>
#include <wayland-client.h>

namespace bongocat::platform::wayland::sway {

int fs_check_compositor_fallback() {
  FILE *fp = popen("swaymsg -t get_tree 2>/dev/null", "r");
  if (fp) {
    bool is_fullscreen = false;

    char sway_buffer[SWAY_BUF] = {0};
    while (fgets(sway_buffer, SWAY_BUF, fp)) {
      if (strstr(sway_buffer, "\"fullscreen_mode\":1")) {
        is_fullscreen = true;
        BONGOCAT_LOG_DEBUG("Fullscreen detected in Sway");
        break;
      }
    }

    pclose(fp);
    return is_fullscreen ? 1 : 0;
  }

  return -1;
}

}  // namespace bongocat::platform::wayland::sway
