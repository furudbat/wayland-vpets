#include "embedded_assets/min_dm/min_dm_images.h"

#include <stddef.h>

#ifndef ASSETS_SECTION
#if defined(__GNUC__) || defined(__clang__)
  #define ASSETS_SECTION __attribute__((section(".assets")))
#elif defined(_MSC_VER)
  #define ASSETS_SECTION __declspec(allocate(".assets"))
  #pragma section(".assets", read)
#else
  #define ASSETS_SECTION
#endif
#endif

// Botamon
const unsigned char dm_botamon_png[] ASSETS_SECTION = {
#embed "../../../assets/dm/Botamon.png"
};
const size_t dm_botamon_png_size ASSETS_SECTION = sizeof(dm_botamon_png);

// Koromon
const unsigned char dm_koromon_png[] ASSETS_SECTION = {
#embed "../../../assets/dm/Koromon.png"
};
const size_t dm_koromon_png_size ASSETS_SECTION = sizeof(dm_koromon_png);

// Agumon
const unsigned char dm_agumon_png[] ASSETS_SECTION = {
#embed "../../../assets/dm/Agumon.png"
};
const size_t dm_agumon_png_size ASSETS_SECTION = sizeof(dm_agumon_png);

// Betamon
const unsigned char dm_betamon_png[] ASSETS_SECTION = {
#embed "../../../assets/dm/Betamon.png"
};
const size_t dm_betamon_png_size = sizeof(dm_betamon_png);

// Greymon
const unsigned char dm_greymon_png[] ASSETS_SECTION = {
#embed "../../../assets/dm/Greymon.png"
};
const size_t dm_greymon_png_size ASSETS_SECTION = sizeof(dm_greymon_png);

// Tyranomon
const unsigned char dm_tyranomon_png[] ASSETS_SECTION = {
#embed "../../../assets/dm/Tyranomon.png"
};
const size_t dm_tyranomon_png_size ASSETS_SECTION = sizeof(dm_tyranomon_png);

// Devimon
const unsigned char dm_devimon_png[] ASSETS_SECTION = {
#embed "../../../assets/dm/Devimon.png"
};
const size_t dm_devimon_png_size ASSETS_SECTION = sizeof(dm_devimon_png);

// Meramon
const unsigned char dm_meramon_png[] ASSETS_SECTION = {
#embed "../../../assets/dm/Meramon.png"
};
const size_t dm_meramon_png_size ASSETS_SECTION = sizeof(dm_meramon_png);

// Airdramon
const unsigned char dm_airdramon_png[] ASSETS_SECTION = {
#embed "../../../assets/dm/Airdramon.png"
};
const size_t dm_airdramon_png_size ASSETS_SECTION = sizeof(dm_airdramon_png);

// Seadramon
const unsigned char dm_seadramon_png[] ASSETS_SECTION = {
#embed "../../../assets/dm/Seadramon.png"
};
const size_t dm_seadramon_png_size ASSETS_SECTION = sizeof(dm_seadramon_png);

// Numemon
const unsigned char dm_numemon_png[] ASSETS_SECTION = {
#embed "../../../assets/dm/Numemon.png"
};
const size_t dm_numemon_png_size ASSETS_SECTION = sizeof(dm_numemon_png);

// Metal Greymon
const unsigned char dm_metal_greymon_png[] ASSETS_SECTION = {
#embed "../../../assets/dm/Metal Greymon.png"
};
const size_t dm_metal_greymon_png_size = sizeof(dm_metal_greymon_png);

// Mamemon
const unsigned char dm_mamemon_png[] ASSETS_SECTION = {
#embed "../../../assets/dm/Mamemon.png"
};
const size_t dm_mamemon_png_size = sizeof(dm_mamemon_png);

// Monzaemon
const unsigned char dm_monzaemon_png[] ASSETS_SECTION = {
#embed "../../../assets/dm/Monzaemon.png"
};
const size_t dm_monzaemon_png_size ASSETS_SECTION = sizeof(dm_monzaemon_png);
