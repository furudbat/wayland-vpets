#include "wayland_hyprland.h"

#include "platform/wayland_setups.h"
#include "utils/error.h"

#include <cassert>
#include <cerrno>
#include <cstdio>
#include <pthread.h>
#include <sys/signalfd.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <wayland-client.h>

namespace bongocat::platform::wayland::hyprland {

int fs_check_compositor_fallback(wayland_context_t& ctx) {
  constexpr const char *argv[] = {HYPRCTL_COMMAND, "activewindow", BONGOCAT_NULLPTR};
  details::spawn_pipe_t sp = details::safe_popen_read_spawn(ctx, HYPRCTL_COMMAND, argv);

  if (sp.fp != BONGOCAT_NULLPTR) {
    bool is_fullscreen = false;

    char line[LINE_BUF];
    while (fgets(line, LINE_BUF, sp.fp)) {
      const size_t len = strlen(line);
      if (len > 0 && line[len - 1] == '\n') {
        line[len - 1] = '\0';
      }

      if (strstr(line, "fullscreen: 1") != BONGOCAT_NULLPTR || strstr(line, "fullscreen: 2") != BONGOCAT_NULLPTR ||
          strstr(line, "fullscreen: true") != BONGOCAT_NULLPTR) {
        is_fullscreen = true;
        BONGOCAT_LOG_DEBUG("Fullscreen detected in Hyprland");
        break;
      }
    }

    return is_fullscreen ? 1 : 0;
  }

  return -1;
}

void update_outputs_with_monitor_ids(wayland_context_t& ctx) {
  constexpr const char *argv[] = {HYPRCTL_COMMAND, "monitors", BONGOCAT_NULLPTR};
  details::spawn_pipe_t sp = details::safe_popen_read_spawn(ctx, HYPRCTL_COMMAND, argv);
  if (sp.fp == BONGOCAT_NULLPTR) {
    return;
  }

  char line[LINE_BUF];
  while (fgets(line, LINE_BUF, sp.fp)) {
    int id = -1;
    char name[256] = {0};
    int result = sscanf(line, "Monitor %d \"%255[^\"]\"", &id, name);
    if (result < 2) {
      result = sscanf(line, "Monitor %255s (ID %d)", name, &id);
    }

    if (result == 2) {
      for (size_t i = 0; i < ctx.output_count; i++) {
        // match by xdg-output name
        if (has_flag(ctx.outputs[i].received, output_ref_received_flags_t::Name) &&
            strcmp(ctx.outputs[i].name_str, name) == 0) {
          ctx.outputs[i].hypr_id = id;
          BONGOCAT_LOG_DEBUG("Mapped xdg-output '%s' to Hyprland ID %d", name, id);
          break;
        }
      }
    }
  }
}

bool get_active_window(wayland_context_t& ctx, window_info_t& win) {
  constexpr const char *argv[] = {HYPRCTL_COMMAND, "activewindow", BONGOCAT_NULLPTR};
  details::spawn_pipe_t sp = details::safe_popen_read_spawn(ctx, HYPRCTL_COMMAND, argv);
  FILE *fp = sp.fp;
  if (fp == BONGOCAT_NULLPTR) {
    return false;
  }

  bool has_window = false;
  win.monitor_id = -1;
  win.fullscreen = false;
  win.x = 0;
  win.y = 0;
  win.width = 0;
  win.height = 0;

  char line[4096];
  while (fgets(line, sizeof(line), fp) != BONGOCAT_NULLPTR) {
    // remove trailing newline
    size_t len = strlen(line);
    if (len > 0 && line[len - 1] == '\n') {
      line[len - 1] = '\0';
    }

    // monitor: 0
    if (strstr(line, "monitor:") != BONGOCAT_NULLPTR) {
      if (sscanf(line, "%*[\t ]monitor: %d", &win.monitor_id) == 1) {
        has_window = true;
      }
    }

    // fullscreen: 0/1/2
    if (strstr(line, "fullscreen:") != BONGOCAT_NULLPTR) {
      int val;
      if (sscanf(line, "%*[\t ]fullscreen: %d", &val) == 1) {
        win.fullscreen = (val != 0);
      }
    }

    // at: X,Y
    if (strstr(line, "at:") != BONGOCAT_NULLPTR) {
      if (sscanf(line, "%*[\t ]at: [%d, %d]", &win.x, &win.y) < 2) {
        sscanf(line, "%*[\t ]at: %d,%d", &win.x, &win.y);
      }
    }

    // size: W,H
    if (strstr(line, "size:") != BONGOCAT_NULLPTR) {
      if (sscanf(line, "%*[\t ]size: [%d, %d]", &win.width, &win.height) < 2) {
        sscanf(line, "%*[\t ]size: %d,%d", &win.width, &win.height);
      }
    }
  }

  return has_window;
}

}  // namespace bongocat::platform::wayland::hyprland