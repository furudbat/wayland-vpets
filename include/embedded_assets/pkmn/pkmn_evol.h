#ifndef PKMN_EVOL_EMBEDDED_ASSETS_HPP
#define PKMN_EVOL_EMBEDDED_ASSETS_HPP

#include "graphics/animation_shared_memory.h"
#include <cstddef>

namespace bongocat::assets {
BONGOCAT_NODISCARD extern animation::animation_evolution_data_t get_pkmn_evolution_data(size_t i);
}
#endif