#pragma once

namespace bongocat::platform::wayland::hyprland {

static inline constexpr size_t LINE_BUF = 512;

typedef struct {
    int monitor_id{-1};     // monitor number in Hyprland
    int x{0};
    int y{0};
    int width{0};
    int height{0};
    bool fullscreen{false};
} window_info_t;

static int fs_check_compositor_fallback() {
    FILE *fp = popen("hyprctl activewindow 2>/dev/null", "r");
    if (fp) {
        bool is_fullscreen = false;

        char line[LINE_BUF];
        while (fgets(line, LINE_BUF, fp)) {
            const size_t len = strlen(line);
            if (len > 0 && line[len-1] == '\n') {
                line[len-1] = '\0';
            }

            if (strstr(line, "fullscreen: 1") || strstr(line, "fullscreen: 2") || strstr(line, "fullscreen: true")) {
                is_fullscreen = true;
                BONGOCAT_LOG_DEBUG("Fullscreen detected in Hyprland");
                break;
            }
        }

        pclose(fp);
        return is_fullscreen ? 1 : 0;
    }

    return -1;
}

static void update_outputs_with_monitor_ids(wayland_session_t& ctx) {
    FILE *fp = popen("hyprctl monitors 2>/dev/null", "r");
    if (!fp) return;

    char line[LINE_BUF];
    while (fgets(line, LINE_BUF, fp)) {
        int id = -1;
        char name[256] = {0};
        int result = sscanf(line, "Monitor %d \"%255[^\"]\"", &id, name);
        if (result < 2) {
            result = sscanf(line, "Monitor %255s (ID %d)", name, &id);
        }

        if (result == 2) {
            for (size_t i = 0; i < ctx.output_count; i++) {
                // match by xdg-output name
                if ((static_cast<uint32_t>(ctx.outputs[i].received) & static_cast<uint32_t>(output_ref_received_flags_t::Name)) && strcmp(ctx.outputs[i].name_str, name) == 0) {
                    ctx.outputs[i].hypr_id = id;
                    BONGOCAT_LOG_DEBUG("Mapped xdg-output '%s' to Hyprland ID %d", name, id);
                    break;
                }
            }
        }
    }

    pclose(fp);
}

static bool get_active_window(window_info_t& win) {
    FILE *fp = popen("hyprctl activewindow 2>/dev/null", "r");
    if (!fp) return false;

    bool has_window = false;
    win.monitor_id = -1;
    win.fullscreen = false;

    char line[LINE_BUF];
    while (fgets(line, LINE_BUF, fp)) {
        // monitor: 0
        if (strstr(line, "monitor:")) {
            sscanf(line, "%*[\t ]monitor: %d", &win.monitor_id);
            has_window = true;
        }
        // fullscreen: 0/1/2
        if (strstr(line, "fullscreen:")) {
            int val;
            if (sscanf(line, "%*[\t ]fullscreen: %d", &val) == 1) {
                win.fullscreen = (val != 0);
            }
        }
        // at: X,Y
        if (strstr(line, "at:")) {
            if (sscanf(line, "%*[\t ]at: [%d, %d]", &win.x, &win.y) < 2) {
                sscanf(line, "%*[\t ]at: %d,%d", &win.x, &win.y);
            }
        }
        // size: W,H
        if (strstr(line, "size:")) {
            if (sscanf(line, "%*[\t ]size: [%d, %d]", &win.width, &win.height) < 2) {
                sscanf(line, "%*[\t ]size: %d,%d", &win.width, &win.height);
            }
        }
    }

    pclose(fp);
    return has_window;
}

}