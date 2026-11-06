#ifndef PEN20_EVOL_EMBEDDED_ASSETS_HPP
#define PEN20_EVOL_EMBEDDED_ASSETS_HPP

#include "embedded_assets/assets.h"
#include "graphics/animation_shared_memory.h"
#include <cstddef>

// pen20
#define ASSETS_PEN20_EVOL_DATA_SECTION BONGOCAT_ASSETS_SET_SECTION(pen20, "evol_data")

namespace bongocat::assets {
BONGOCAT_NODISCARD extern animation::animation_evolution_data_t get_pen20_evolution_data(size_t i);
}
#endif