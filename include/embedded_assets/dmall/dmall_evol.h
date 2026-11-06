#ifndef DMALL_EVOL_EMBEDDED_ASSETS_HPP
#define DMALL_EVOL_EMBEDDED_ASSETS_HPP

#include "embedded_assets/assets.h"
#include "graphics/animation_shared_memory.h"
#include <cstddef>

// dmall
#define ASSETS_DMALL_EVOL_DATA_SECTION BONGOCAT_ASSETS_SET_SECTION(dmall, "evol_data")

namespace bongocat::assets {
BONGOCAT_NODISCARD extern animation::animation_evolution_data_t get_dmall_evolution_data(size_t i);
}
#endif