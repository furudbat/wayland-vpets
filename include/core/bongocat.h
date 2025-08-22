#ifndef BONGOCAT_BONGOCAT_H
#define BONGOCAT_BONGOCAT_H

#include <cstdint>
#include <cstddef>

#include "utils/error.h"
#include "utils/memory.h"

// Version
inline static constexpr const char* BONGOCAT_VERSION = "2.1.0";

// Common constants
inline static constexpr int DEFAULT_SCREEN_WIDTH = 1920;
inline static constexpr int DEFAULT_BAR_HEIGHT = 40;
inline static constexpr int RGBA_CHANNELS = 4;
inline static constexpr int BGRA_CHANNELS = 4;

inline static constexpr size_t MAX_INPUT_DEVICES = 256;

namespace bongocat {
    template<typename T>
    struct created_result_t {
        T result{};
        bongocat_error_t error{bongocat_error_t::BONGOCAT_SUCCESS};

        created_result_t() = default;
        explicit(false) created_result_t(bongocat_error_t err) : error(err) {}
        explicit(false) created_result_t(T&& res) : result(bongocat::move(res)) {}
    };
}

#endif // BONGOCAT_BONGOCAT_H