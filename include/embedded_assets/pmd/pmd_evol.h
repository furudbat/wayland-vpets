#ifndef PMD_EVOL_EMBEDDED_ASSETS_HPP
#define PMD_EVOL_EMBEDDED_ASSETS_HPP

#include "graphics/animation_shared_memory.h"
#include "embedded_assets/assets.h"
#include <cstddef>

// pmd
#define ASSETS_PMD_EVOL_DATA_SECTION BONGOCAT_ASSETS_SET_SECTION(pmd, "evol_data")

namespace bongocat::assets {
BONGOCAT_NODISCARD extern animation::animation_evolution_data_t get_pmd_evolution_data(size_t i);
}
#endif