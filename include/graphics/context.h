#ifndef BONGOCAT_ANIMATION_CONTEXT_H
#define BONGOCAT_ANIMATION_CONTEXT_H

#include "embedded_assets.h"
#include "core/bongocat.h"
#include "config/config.h"
#include "platform/input_context.h"
#include "platform/wayland_context.h"
#include <stdatomic.h>
#include <stdint.h>


// both-up, left-down, right-down, both-down
#define BONGOCAT_NUM_FRAMES 4

// Idle 1, Idle 2, Angry, Down1, Happy, Eat1, Sleep1, Refuse, Down2 ~~, Eat2, Sleep2, Attack~~
// both-up, left-down, right-down, both-down, ...
#define MAX_NUM_FRAMES 15
#define MAX_DIGIMON_FRAMES 15

typedef struct {
    bool valid;
    int col;
    int row;
} sprite_sheet_animation_region_t;
typedef struct {
    int sprite_sheet_width;
    int sprite_sheet_height;
    int channels;
    uint8_t *pixels;
    size_t pixels_size;

    int frame_width;
    int frame_height;
    int total_frames;

    sprite_sheet_animation_region_t idle_1;
    sprite_sheet_animation_region_t idle_2;
    sprite_sheet_animation_region_t angry;
    sprite_sheet_animation_region_t down1;
    sprite_sheet_animation_region_t happy;
    sprite_sheet_animation_region_t at1;
    sprite_sheet_animation_region_t sleep1;
    sprite_sheet_animation_region_t refuse;
    sprite_sheet_animation_region_t sad;

    // optional
    sprite_sheet_animation_region_t down_2;
    sprite_sheet_animation_region_t eat_2;
    sprite_sheet_animation_region_t sleep_2;
    sprite_sheet_animation_region_t attack;

    // extra frames
    sprite_sheet_animation_region_t movement_1;
    sprite_sheet_animation_region_t movement_2;
} digimon_animation_t;

typedef struct {
    int sprite_sheet_width;
    int sprite_sheet_height;
    int channels;
    uint8_t *pixels;
    size_t pixels_size;

    int frame_width;
    int frame_height;
    int total_frames;

    sprite_sheet_animation_region_t both_up;
    sprite_sheet_animation_region_t left_down;
    sprite_sheet_animation_region_t right_down;
    sprite_sheet_animation_region_t both_down;

    sprite_sheet_animation_region_t _placeholder[MAX_NUM_FRAMES-4];
} bongocat_animation_t;

typedef struct {
    int sprite_sheet_width;
    int sprite_sheet_height;
    int channels;
    uint8_t *pixels;
    size_t pixels_size;

    int frame_width;
    int frame_height;
    int total_frames;

    sprite_sheet_animation_region_t frames[MAX_NUM_FRAMES];
} generic_sprite_sheet_animation_t;

static_assert(sizeof(digimon_animation_t) == sizeof(bongocat_animation_t));
typedef union {
    bongocat_animation_t bongocat;
    digimon_animation_t digimon;
    generic_sprite_sheet_animation_t sprite_sheet;
} animation_t;
static_assert(sizeof(bongocat_animation_t) == sizeof(digimon_animation_t));
static_assert(sizeof(generic_sprite_sheet_animation_t) == sizeof(bongocat_animation_t));
static_assert(sizeof(generic_sprite_sheet_animation_t) == sizeof(digimon_animation_t));

typedef struct {
    // Animation frame data
    animation_t anims[ANIMS_COUNT];
    int anim_index;
    int anim_frame_index;
    pthread_mutex_t anim_lock;

    // local copy from other thread, update after reload (shared memory)
    config_t* _local_copy_config;

    // Animation system state
    atomic_bool _animation_running;
    pthread_t _anim_thread;
    input_context_t *_input;
    wayland_context_t *_wayland;
} animation_context_t;

#endif //ANIMATION_CONTEXT_H
