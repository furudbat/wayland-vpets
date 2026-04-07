#include "wayland_sway.h"

#include "platform/wayland_setups.h"
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

int fs_check_compositor_fallback(wayland_context_t& ctx) {
  constexpr const char *argv[] = {SWAYMSG_COMMAND, "-t", "get_tree", NULL};
  details::spawn_pipe_t sp = details::safe_popen_read_spawn(ctx, SWAYMSG_COMMAND, argv);

  if (sp.fp != BONGOCAT_NULLPTR) {
    bool is_fullscreen = false;

    char sway_buffer[SWAY_BUF] = {0};
    while (fgets(sway_buffer, SWAY_BUF, sp.fp)) {
      if (strstr(sway_buffer, "\"fullscreen_mode\":1")) {
        is_fullscreen = true;
        BONGOCAT_LOG_DEBUG("Fullscreen detected in Sway");
        break;
      }
    }

    return is_fullscreen ? 1 : 0;
  }

  return -1;
}

}  // namespace bongocat::platform::wayland::sway
