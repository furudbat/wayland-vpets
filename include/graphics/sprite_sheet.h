#ifndef BONGOCAT_ANIMATION_SPRITE_SHEET_H
#define BONGOCAT_ANIMATION_SPRITE_SHEET_H

#include <cstdint>
#include <cstddef>

// both-up, left-down, right-down, both-down
inline static constexpr size_t BONGOCAT_NUM_FRAMES = 4;

// Idle 1, Idle 2, Angry, Down1, Happy, Eat1, Sleep1, Refuse, Down2 ~~, Eat2, Sleep2, Attack~~
// both-up, left-down, right-down, both-down, ...
inline static constexpr size_t MAX_NUM_FRAMES = 15;
inline static constexpr size_t MAX_DIGIMON_FRAMES = 15;

struct sprite_sheet_animation_region_t {
    bool valid{false};
    int col{0};
    int row{0};
};
struct digimon_animation_t {
    int sprite_sheet_width{0};
    int sprite_sheet_height{0};
    int channels{0};
    uint8_t *pixels{nullptr};
    size_t pixels_size{0};

    int frame_width{0};
    int frame_height{0};
    int total_frames{0};

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
};

struct bongocat_animation_t {
    int sprite_sheet_width{0};
    int sprite_sheet_height{0};
    int channels{0};
    uint8_t *pixels{nullptr};
    size_t pixels_size{0};

    int frame_width{0};
    int frame_height{0};
    int total_frames{0};

    sprite_sheet_animation_region_t both_up;
    sprite_sheet_animation_region_t left_down;
    sprite_sheet_animation_region_t right_down;
    sprite_sheet_animation_region_t both_down;

    sprite_sheet_animation_region_t _placeholder[MAX_NUM_FRAMES-4];
};

struct generic_sprite_sheet_animation_t {
    int sprite_sheet_width{0};
    int sprite_sheet_height{0};
    int channels{0};
    uint8_t *pixels{nullptr};
    size_t pixels_size{0};

    int frame_width{0};
    int frame_height{0};
    int total_frames{0};

    sprite_sheet_animation_region_t frames[MAX_NUM_FRAMES];
};

static_assert(sizeof(digimon_animation_t) == sizeof(bongocat_animation_t));
union animation_t {
    bongocat_animation_t bongocat;
    digimon_animation_t digimon;
    generic_sprite_sheet_animation_t sprite_sheet;
};
static_assert(sizeof(bongocat_animation_t) == sizeof(digimon_animation_t));
static_assert(sizeof(generic_sprite_sheet_animation_t) == sizeof(bongocat_animation_t));
static_assert(sizeof(generic_sprite_sheet_animation_t) == sizeof(digimon_animation_t));

#endif //BONGOCAT_ANIMATION_SPRITE_SHEET_H
