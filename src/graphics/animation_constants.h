#ifndef BONGOCAT_ANIMATION_CONST_H
#define BONGOCAT_ANIMATION_CONST_H

namespace bongocat::animation {
// Bongocat Frames
inline static constexpr int BONGOCAT_FRAME_BOTH_UP = 0;
inline static constexpr int BONGOCAT_FRAME_LEFT_DOWN = 1;
inline static constexpr int BONGOCAT_FRAME_RIGHT_DOWN = 2;
inline static constexpr int BONGOCAT_FRAME_BOTH_DOWN = 3;

#ifndef FEATURE_INCLUDE_ONLY_BONGOCAT_EMBEDDED_ASSETS
static inline constexpr int DIGIMON_FRAME_IDLE1     = 0;
static inline constexpr int DIGIMON_FRAME_IDLE2     = 1;
static inline constexpr int DIGIMON_FRAME_ANGRY     = 2;  // Angry/Refuse or Hit (Fallback), Eat Frame Fallback
static inline constexpr int DIGIMON_FRAME_DOWN1     = 3;  // Sleep/Discipline Fallback
static inline constexpr int DIGIMON_FRAME_HAPPY     = 4;
static inline constexpr int DIGIMON_FRAME_EAT1      = 5;
static inline constexpr int DIGIMON_FRAME_SLEEP1    = 6;
static inline constexpr int DIGIMON_FRAME_REFUSE    = 7;
static inline constexpr int DIGIMON_FRAME_SAD       = 8;

// Optional frames
static inline constexpr int DIGIMON_FRAME_DOWN2     = 9;
static inline constexpr int DIGIMON_FRAME_EAT2      = 10;
static inline constexpr int DIGIMON_FRAME_SLEEP2    = 11;
static inline constexpr int DIGIMON_FRAME_ATTACK    = 12;

static inline constexpr int DIGIMON_FRAME_MOVEMENT1 = 13;
static inline constexpr int DIGIMON_FRAME_MOVEMENT2 = 14;

static inline constexpr int HAPPY_CHANCE_PERCENT = 60;
#endif
}

#endif