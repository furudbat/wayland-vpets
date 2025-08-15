#ifndef BONGOCAT_BONGOCAT_H
#define BONGOCAT_BONGOCAT_H

#include <cstdint>
#include <cstddef>

// Version
inline static constexpr const char* BONGOCAT_VERSION = "2.0.0";

// Common constants
inline static constexpr int DEFAULT_SCREEN_WIDTH = 1920;
inline static constexpr int DEFAULT_BAR_HEIGHT = 40;
inline static constexpr int RGBA_CHANNELS = 4;
inline static constexpr int BGRA_CHANNELS = 4;

inline static constexpr size_t MAX_INPUT_DEVICES = 256;

namespace bongocat {}

#endif // BONGOCAT_BONGOCAT_H