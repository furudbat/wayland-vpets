#ifndef BONGOCAT_GLOBAL_WAYLAND_CONTEXT_CONTEXT_H
#define BONGOCAT_GLOBAL_WAYLAND_CONTEXT_CONTEXT_H

#include "wayland_context.h"
#include "graphics/animation_context.h"
#include "graphics/animation_event_context.h"
#include "../protocols/xdg-output-unstable-v1-client-protocol.h"
#include <sys/time.h>

#define MAX_TOPLEVELS 64
#define MAX_OUTPUTS 8               // Maximum monitor outputs to store
#define OUTPUT_NAME_SIZE 128

// =============================================================================
// FULLSCREEN DETECTION MODULE
// =============================================================================

typedef struct {
    struct zwlr_foreign_toplevel_manager_v1 *manager;
    bool has_fullscreen_toplevel;
    struct timeval last_check;
} fullscreen_detector_t;

// =============================================================================
// SCREEN DIMENSION MANAGEMENT
// =============================================================================

typedef struct {
    int screen_width;
    int screen_height;
    int transform;
    int raw_width;
    int raw_height;
    bool mode_received;
    bool geometry_received;
} screen_info_t;


// Output monitor reference structure
typedef struct {
    struct wl_output *wl_output;
    struct zxdg_output_v1 *xdg_output;
    uint32_t name;                      // Registry name
    char name_str[OUTPUT_NAME_SIZE];    // From xdg-output
    bool name_received;
} output_ref_t;

typedef struct {
    wayland_context_t* wayland_context;
    animation_context_t* animation_context;
    animation_trigger_context_t* animation_trigger_context;

    struct zwlr_foreign_toplevel_handle_v1* tracked_toplevels[MAX_TOPLEVELS];
    size_t num_toplevels;

    output_ref_t outputs[MAX_OUTPUTS];
    size_t output_count;
    struct zxdg_output_manager_v1 *xdg_output_manager;

    fullscreen_detector_t fs_detector;

    screen_info_t screen_info;
} wayland_listeners_context_t;

#endif
