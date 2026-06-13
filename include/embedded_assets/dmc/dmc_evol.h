#ifndef DMC_EVOL_EMBEDDED_ASSETS_HPP
#define DMC_EVOL_EMBEDDED_ASSETS_HPP

#include "graphics/animation_shared_memory.h"
#include <cstddef>

namespace bongocat::assets {
BONGOCAT_NODISCARD extern animation::animation_evolution_data_t get_dmc_evolution_data(size_t i);
}
#endif