#ifndef PEN_EVOL_EMBEDDED_ASSETS_HPP
#define PEN_EVOL_EMBEDDED_ASSETS_HPP

#include "embedded_assets/assets.h"
#include "graphics/animation_shared_memory.h"
#include <cstddef>

// pen
#define ASSETS_PEN_EVOL_DATA_SECTION BONGOCAT_ASSETS_SET_SECTION(pen, "evol_data")

namespace bongocat::assets {
BONGOCAT_NODISCARD extern animation::animation_evolution_data_t get_pen_evolution_data(size_t i);
}
#endif