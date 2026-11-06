#ifndef DM20_EVOL_EMBEDDED_ASSETS_HPP
#define DM20_EVOL_EMBEDDED_ASSETS_HPP

#include "embedded_assets/assets.h"
#include "graphics/animation_shared_memory.h"
#include <cstddef>

// dm
#define ASSETS_DM20_EVOL_DATA_SECTION BONGOCAT_ASSETS_SET_SECTION(dm20, "evol_data")

namespace bongocat::assets {
BONGOCAT_NODISCARD extern animation::animation_evolution_data_t get_dm20_evolution_data(size_t i);
}
#endif