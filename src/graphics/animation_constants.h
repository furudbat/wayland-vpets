#ifndef BONGOCAT_ANIMATION_CONST_H
#define BONGOCAT_ANIMATION_CONST_H

// Bongocat Frames
inline static constexpr int BONGOCAT_FRAME_BOTH_UP = 0;
inline static constexpr int BONGOCAT_FRAME_LEFT_DOWN = 1;
inline static constexpr int BONGOCAT_FRAME_RIGHT_DOWN = 2;
inline static constexpr int BONGOCAT_FRAME_BOTH_DOWN = 3;

#ifndef FEATURE_INCLUDE_ONLY_BONGOCAT_EMBEDDED_ASSETS

static inline constexpr int FRAME_IDLE1     = 0;
static inline constexpr int FRAME_IDLE2     = 1;
static inline constexpr int FRAME_ANGRY     = 2;  // Angry/Refuse or Hit (Fallback), Eat Frame Fallback
static inline constexpr int FRAME_DOWN1     = 3;  // Sleep/Discipline Fallback
static inline constexpr int FRAME_HAPPY     = 4;
static inline constexpr int FRAME_EAT1      = 5;
static inline constexpr int FRAME_SLEEP1    = 6;
static inline constexpr int FRAME_REFUSE    = 7;
static inline constexpr int FRAME_SAD       = 8;

// Optional frames
static inline constexpr int FRAME_DOWN2     = 9;
static inline constexpr int FRAME_EAT2      = 10;
static inline constexpr int FRAME_SLEEP2    = 11;
static inline constexpr int FRAME_ATTACK    = 12;

static inline constexpr int FRAME_MOVEMENT1 = 13;
static inline constexpr int FRAME_MOVEMENT2 = 14;

static inline constexpr int HAPPY_CHANCE_PERCENT = 60;
#endif

#endif