#pragma once

namespace bongocat::platform::wayland::sway {

static inline constexpr size_t SWAY_BUF = 4096;

static int fs_check_compositor_fallback() {
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

}
