#ifndef PKMN_EVOL_EMBEDDED_ASSETS_HPP
#define PKMN_EVOL_EMBEDDED_ASSETS_HPP

#include "embedded_assets/assets.h"
#include "graphics/animation_shared_memory.h"
#include <cstddef>

// pkmn
#define ASSETS_PKMN_EVOL_DATA_SECTION BONGOCAT_ASSETS_SET_SECTION(pkmn, "evol_data")

namespace bongocat::assets {
BONGOCAT_NODISCARD extern animation::animation_evolution_data_t get_pkmn_evolution_data(size_t i);
}
#endif