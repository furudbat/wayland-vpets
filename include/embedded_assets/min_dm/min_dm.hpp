#ifndef MIN_DM_EMBEDDED_ASSETS_HPP
#define MIN_DM_EMBEDDED_ASSETS_HPP

#include "embedded_assets/assets.h"
#include <cstddef>

// min_dm
#define ASSETS_MIN_DM_SPRITE_SETTINGS_SECTION BONGOCAT_ASSETS_SET_SECTION(min_dm, "sprite_settings")
#define ASSETS_MIN_DM_DIMS_SECTION BONGOCAT_ASSETS_SET_SECTION(min_dm, "dims")
//#define ASSETS_MIN_DM_EVOL_DATA_SECTION BONGOCAT_ASSETS_SET_SECTION(min_dm, "evol_data")

namespace bongocat::assets {
// Name: Botamon
inline static constexpr char MIN_DM_BOTAMON_FQID_ARR[] CONFIG_STRING_SECTION = "dm:botamon";
inline static constexpr const char* MIN_DM_BOTAMON_FQID = MIN_DM_BOTAMON_FQID_ARR;
inline static constexpr size_t MIN_DM_BOTAMON_FQID_LEN = sizeof(MIN_DM_BOTAMON_FQID_ARR)-1;
inline static constexpr char MIN_DM_BOTAMON_ID_ARR[] CONFIG_STRING_SECTION = "botamon";
inline static constexpr const char* MIN_DM_BOTAMON_ID = MIN_DM_BOTAMON_ID_ARR;
inline static constexpr size_t MIN_DM_BOTAMON_ID_LEN = sizeof(MIN_DM_BOTAMON_ID_ARR)-1;
inline static constexpr char MIN_DM_BOTAMON_NAME_ARR[] CONFIG_STRING_SECTION = "Botamon";
inline static constexpr const char* MIN_DM_BOTAMON_NAME = MIN_DM_BOTAMON_NAME_ARR;
inline static constexpr size_t MIN_DM_BOTAMON_NAME_LEN = sizeof(MIN_DM_BOTAMON_NAME_ARR)-1;
inline static constexpr char MIN_DM_BOTAMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "dm:Botamon";
inline static constexpr const char* MIN_DM_BOTAMON_FQNAME = MIN_DM_BOTAMON_FQNAME_ARR;
inline static constexpr size_t MIN_DM_BOTAMON_FQNAME_LEN = sizeof(MIN_DM_BOTAMON_FQNAME_ARR)-1;
inline static constexpr int MIN_DM_BOTAMON_SPRITE_SHEET_COLS ASSETS_MIN_DM_DIMS_SECTION =    11;
inline static constexpr int MIN_DM_BOTAMON_SPRITE_SHEET_ROWS ASSETS_MIN_DM_DIMS_SECTION =    1;
inline static constexpr size_t MIN_DM_BOTAMON_SPRITE_SHEET_FRAMES_COUNT = 11;
inline static constexpr std::size_t MIN_DM_BOTAMON_ANIM_INDEX = 0;

// Name: Koromon
inline static constexpr char MIN_DM_KOROMON_FQID_ARR[] CONFIG_STRING_SECTION = "dm:koromon";
inline static constexpr const char* MIN_DM_KOROMON_FQID = MIN_DM_KOROMON_FQID_ARR;
inline static constexpr size_t MIN_DM_KOROMON_FQID_LEN = sizeof(MIN_DM_KOROMON_FQID_ARR)-1;
inline static constexpr char MIN_DM_KOROMON_ID_ARR[] CONFIG_STRING_SECTION = "koromon";
inline static constexpr const char* MIN_DM_KOROMON_ID = MIN_DM_KOROMON_ID_ARR;
inline static constexpr size_t MIN_DM_KOROMON_ID_LEN = sizeof(MIN_DM_KOROMON_ID_ARR)-1;
inline static constexpr char MIN_DM_KOROMON_NAME_ARR[] CONFIG_STRING_SECTION = "Koromon";
inline static constexpr const char* MIN_DM_KOROMON_NAME = MIN_DM_KOROMON_NAME_ARR;
inline static constexpr size_t MIN_DM_KOROMON_NAME_LEN = sizeof(MIN_DM_KOROMON_NAME_ARR)-1;
inline static constexpr char MIN_DM_KOROMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "dm:Koromon";
inline static constexpr const char* MIN_DM_KOROMON_FQNAME = MIN_DM_KOROMON_FQNAME_ARR;
inline static constexpr size_t MIN_DM_KOROMON_FQNAME_LEN = sizeof(MIN_DM_KOROMON_FQNAME_ARR)-1;
inline static constexpr int MIN_DM_KOROMON_SPRITE_SHEET_COLS ASSETS_MIN_DM_DIMS_SECTION =    9;
inline static constexpr int MIN_DM_KOROMON_SPRITE_SHEET_ROWS ASSETS_MIN_DM_DIMS_SECTION =    1;
inline static constexpr size_t MIN_DM_KOROMON_SPRITE_SHEET_FRAMES_COUNT = 9;
inline static constexpr std::size_t MIN_DM_KOROMON_ANIM_INDEX = 1;

// Name: Agumon
inline static constexpr char MIN_DM_AGUMON_FQID_ARR[] CONFIG_STRING_SECTION = "dm:agumon";
inline static constexpr const char* MIN_DM_AGUMON_FQID = MIN_DM_AGUMON_FQID_ARR;
inline static constexpr size_t MIN_DM_AGUMON_FQID_LEN = sizeof(MIN_DM_AGUMON_FQID_ARR)-1;
inline static constexpr char MIN_DM_AGUMON_ID_ARR[] CONFIG_STRING_SECTION = "agumon";
inline static constexpr const char* MIN_DM_AGUMON_ID = MIN_DM_AGUMON_ID_ARR;
inline static constexpr size_t MIN_DM_AGUMON_ID_LEN = sizeof(MIN_DM_AGUMON_ID_ARR)-1;
inline static constexpr char MIN_DM_AGUMON_NAME_ARR[] CONFIG_STRING_SECTION = "Agumon";
inline static constexpr const char* MIN_DM_AGUMON_NAME = MIN_DM_AGUMON_NAME_ARR;
inline static constexpr size_t MIN_DM_AGUMON_NAME_LEN = sizeof(MIN_DM_AGUMON_NAME_ARR)-1;
inline static constexpr char MIN_DM_AGUMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "dm:Agumon";
inline static constexpr const char* MIN_DM_AGUMON_FQNAME = MIN_DM_AGUMON_FQNAME_ARR;
inline static constexpr size_t MIN_DM_AGUMON_FQNAME_LEN = sizeof(MIN_DM_AGUMON_FQNAME_ARR)-1;
inline static constexpr int MIN_DM_AGUMON_SPRITE_SHEET_COLS ASSETS_MIN_DM_DIMS_SECTION =    9;
inline static constexpr int MIN_DM_AGUMON_SPRITE_SHEET_ROWS ASSETS_MIN_DM_DIMS_SECTION =    1;
inline static constexpr size_t MIN_DM_AGUMON_SPRITE_SHEET_FRAMES_COUNT = 9;
inline static constexpr std::size_t MIN_DM_AGUMON_ANIM_INDEX = 2;

// Name: Betamon
inline static constexpr char MIN_DM_BETAMON_FQID_ARR[] CONFIG_STRING_SECTION = "dm:betamon";
inline static constexpr const char* MIN_DM_BETAMON_FQID = MIN_DM_BETAMON_FQID_ARR;
inline static constexpr size_t MIN_DM_BETAMON_FQID_LEN = sizeof(MIN_DM_BETAMON_FQID_ARR)-1;
inline static constexpr char MIN_DM_BETAMON_ID_ARR[] CONFIG_STRING_SECTION = "betamon";
inline static constexpr const char* MIN_DM_BETAMON_ID = MIN_DM_BETAMON_ID_ARR;
inline static constexpr size_t MIN_DM_BETAMON_ID_LEN = sizeof(MIN_DM_BETAMON_ID_ARR)-1;
inline static constexpr char MIN_DM_BETAMON_NAME_ARR[] CONFIG_STRING_SECTION = "Betamon";
inline static constexpr const char* MIN_DM_BETAMON_NAME = MIN_DM_BETAMON_NAME_ARR;
inline static constexpr size_t MIN_DM_BETAMON_NAME_LEN = sizeof(MIN_DM_BETAMON_NAME_ARR)-1;
inline static constexpr char MIN_DM_BETAMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "dm:Betamon";
inline static constexpr const char* MIN_DM_BETAMON_FQNAME = MIN_DM_BETAMON_FQNAME_ARR;
inline static constexpr size_t MIN_DM_BETAMON_FQNAME_LEN = sizeof(MIN_DM_BETAMON_FQNAME_ARR)-1;
inline static constexpr int MIN_DM_BETAMON_SPRITE_SHEET_COLS ASSETS_MIN_DM_DIMS_SECTION =    10;
inline static constexpr int MIN_DM_BETAMON_SPRITE_SHEET_ROWS ASSETS_MIN_DM_DIMS_SECTION =    1;
inline static constexpr size_t MIN_DM_BETAMON_SPRITE_SHEET_FRAMES_COUNT = 10;
inline static constexpr std::size_t MIN_DM_BETAMON_ANIM_INDEX = 3;

// Name: Greymon
inline static constexpr char MIN_DM_GREYMON_FQID_ARR[] CONFIG_STRING_SECTION = "dm:greymon";
inline static constexpr const char* MIN_DM_GREYMON_FQID = MIN_DM_GREYMON_FQID_ARR;
inline static constexpr size_t MIN_DM_GREYMON_FQID_LEN = sizeof(MIN_DM_GREYMON_FQID_ARR)-1;
inline static constexpr char MIN_DM_GREYMON_ID_ARR[] CONFIG_STRING_SECTION = "greymon";
inline static constexpr const char* MIN_DM_GREYMON_ID = MIN_DM_GREYMON_ID_ARR;
inline static constexpr size_t MIN_DM_GREYMON_ID_LEN = sizeof(MIN_DM_GREYMON_ID_ARR)-1;
inline static constexpr char MIN_DM_GREYMON_NAME_ARR[] CONFIG_STRING_SECTION = "Greymon";
inline static constexpr const char* MIN_DM_GREYMON_NAME = MIN_DM_GREYMON_NAME_ARR;
inline static constexpr size_t MIN_DM_GREYMON_NAME_LEN = sizeof(MIN_DM_GREYMON_NAME_ARR)-1;
inline static constexpr char MIN_DM_GREYMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "dm:Greymon";
inline static constexpr const char* MIN_DM_GREYMON_FQNAME = MIN_DM_GREYMON_FQNAME_ARR;
inline static constexpr size_t MIN_DM_GREYMON_FQNAME_LEN = sizeof(MIN_DM_GREYMON_FQNAME_ARR)-1;
inline static constexpr int MIN_DM_GREYMON_SPRITE_SHEET_COLS ASSETS_MIN_DM_DIMS_SECTION =    10;
inline static constexpr int MIN_DM_GREYMON_SPRITE_SHEET_ROWS ASSETS_MIN_DM_DIMS_SECTION =    1;
inline static constexpr size_t MIN_DM_GREYMON_SPRITE_SHEET_FRAMES_COUNT = 10;
inline static constexpr std::size_t MIN_DM_GREYMON_ANIM_INDEX = 4;

// Name: Tyranomon
inline static constexpr char MIN_DM_TYRANOMON_FQID_ARR[] CONFIG_STRING_SECTION = "dm:tyranomon";
inline static constexpr const char* MIN_DM_TYRANOMON_FQID = MIN_DM_TYRANOMON_FQID_ARR;
inline static constexpr size_t MIN_DM_TYRANOMON_FQID_LEN = sizeof(MIN_DM_TYRANOMON_FQID_ARR)-1;
inline static constexpr char MIN_DM_TYRANOMON_ID_ARR[] CONFIG_STRING_SECTION = "tyranomon";
inline static constexpr const char* MIN_DM_TYRANOMON_ID = MIN_DM_TYRANOMON_ID_ARR;
inline static constexpr size_t MIN_DM_TYRANOMON_ID_LEN = sizeof(MIN_DM_TYRANOMON_ID_ARR)-1;
inline static constexpr char MIN_DM_TYRANOMON_NAME_ARR[] CONFIG_STRING_SECTION = "Tyranomon";
inline static constexpr const char* MIN_DM_TYRANOMON_NAME = MIN_DM_TYRANOMON_NAME_ARR;
inline static constexpr size_t MIN_DM_TYRANOMON_NAME_LEN = sizeof(MIN_DM_TYRANOMON_NAME_ARR)-1;
inline static constexpr char MIN_DM_TYRANOMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "dm:Tyranomon";
inline static constexpr const char* MIN_DM_TYRANOMON_FQNAME = MIN_DM_TYRANOMON_FQNAME_ARR;
inline static constexpr size_t MIN_DM_TYRANOMON_FQNAME_LEN = sizeof(MIN_DM_TYRANOMON_FQNAME_ARR)-1;
inline static constexpr int MIN_DM_TYRANOMON_SPRITE_SHEET_COLS ASSETS_MIN_DM_DIMS_SECTION =    9;
inline static constexpr int MIN_DM_TYRANOMON_SPRITE_SHEET_ROWS ASSETS_MIN_DM_DIMS_SECTION =    1;
inline static constexpr size_t MIN_DM_TYRANOMON_SPRITE_SHEET_FRAMES_COUNT = 9;
inline static constexpr std::size_t MIN_DM_TYRANOMON_ANIM_INDEX = 5;

// Name: Devimon
inline static constexpr char MIN_DM_DEVIMON_FQID_ARR[] CONFIG_STRING_SECTION = "dm:devimon";
inline static constexpr const char* MIN_DM_DEVIMON_FQID = MIN_DM_DEVIMON_FQID_ARR;
inline static constexpr size_t MIN_DM_DEVIMON_FQID_LEN = sizeof(MIN_DM_DEVIMON_FQID_ARR)-1;
inline static constexpr char MIN_DM_DEVIMON_ID_ARR[] CONFIG_STRING_SECTION = "devimon";
inline static constexpr const char* MIN_DM_DEVIMON_ID = MIN_DM_DEVIMON_ID_ARR;
inline static constexpr size_t MIN_DM_DEVIMON_ID_LEN = sizeof(MIN_DM_DEVIMON_ID_ARR)-1;
inline static constexpr char MIN_DM_DEVIMON_NAME_ARR[] CONFIG_STRING_SECTION = "Devimon";
inline static constexpr const char* MIN_DM_DEVIMON_NAME = MIN_DM_DEVIMON_NAME_ARR;
inline static constexpr size_t MIN_DM_DEVIMON_NAME_LEN = sizeof(MIN_DM_DEVIMON_NAME_ARR)-1;
inline static constexpr char MIN_DM_DEVIMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "dm:Devimon";
inline static constexpr const char* MIN_DM_DEVIMON_FQNAME = MIN_DM_DEVIMON_FQNAME_ARR;
inline static constexpr size_t MIN_DM_DEVIMON_FQNAME_LEN = sizeof(MIN_DM_DEVIMON_FQNAME_ARR)-1;
inline static constexpr int MIN_DM_DEVIMON_SPRITE_SHEET_COLS ASSETS_MIN_DM_DIMS_SECTION =    9;
inline static constexpr int MIN_DM_DEVIMON_SPRITE_SHEET_ROWS ASSETS_MIN_DM_DIMS_SECTION =    1;
inline static constexpr size_t MIN_DM_DEVIMON_SPRITE_SHEET_FRAMES_COUNT = 9;
inline static constexpr std::size_t MIN_DM_DEVIMON_ANIM_INDEX = 6;

// Name: Meramon
inline static constexpr char MIN_DM_MERAMON_FQID_ARR[] CONFIG_STRING_SECTION = "dm:meramon";
inline static constexpr const char* MIN_DM_MERAMON_FQID = MIN_DM_MERAMON_FQID_ARR;
inline static constexpr size_t MIN_DM_MERAMON_FQID_LEN = sizeof(MIN_DM_MERAMON_FQID_ARR)-1;
inline static constexpr char MIN_DM_MERAMON_ID_ARR[] CONFIG_STRING_SECTION = "meramon";
inline static constexpr const char* MIN_DM_MERAMON_ID = MIN_DM_MERAMON_ID_ARR;
inline static constexpr size_t MIN_DM_MERAMON_ID_LEN = sizeof(MIN_DM_MERAMON_ID_ARR)-1;
inline static constexpr char MIN_DM_MERAMON_NAME_ARR[] CONFIG_STRING_SECTION = "Meramon";
inline static constexpr const char* MIN_DM_MERAMON_NAME = MIN_DM_MERAMON_NAME_ARR;
inline static constexpr size_t MIN_DM_MERAMON_NAME_LEN = sizeof(MIN_DM_MERAMON_NAME_ARR)-1;
inline static constexpr char MIN_DM_MERAMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "dm:Meramon";
inline static constexpr const char* MIN_DM_MERAMON_FQNAME = MIN_DM_MERAMON_FQNAME_ARR;
inline static constexpr size_t MIN_DM_MERAMON_FQNAME_LEN = sizeof(MIN_DM_MERAMON_FQNAME_ARR)-1;
inline static constexpr int MIN_DM_MERAMON_SPRITE_SHEET_COLS ASSETS_MIN_DM_DIMS_SECTION =    9;
inline static constexpr int MIN_DM_MERAMON_SPRITE_SHEET_ROWS ASSETS_MIN_DM_DIMS_SECTION =    1;
inline static constexpr size_t MIN_DM_MERAMON_SPRITE_SHEET_FRAMES_COUNT = 9;
inline static constexpr std::size_t MIN_DM_MERAMON_ANIM_INDEX = 7;

// Name: Airdramon
inline static constexpr char MIN_DM_AIRDRAMON_FQID_ARR[] CONFIG_STRING_SECTION = "dm:airdramon";
inline static constexpr const char* MIN_DM_AIRDRAMON_FQID = MIN_DM_AIRDRAMON_FQID_ARR;
inline static constexpr size_t MIN_DM_AIRDRAMON_FQID_LEN = sizeof(MIN_DM_AIRDRAMON_FQID_ARR)-1;
inline static constexpr char MIN_DM_AIRDRAMON_ID_ARR[] CONFIG_STRING_SECTION = "airdramon";
inline static constexpr const char* MIN_DM_AIRDRAMON_ID = MIN_DM_AIRDRAMON_ID_ARR;
inline static constexpr size_t MIN_DM_AIRDRAMON_ID_LEN = sizeof(MIN_DM_AIRDRAMON_ID_ARR)-1;
inline static constexpr char MIN_DM_AIRDRAMON_NAME_ARR[] CONFIG_STRING_SECTION = "Airdramon";
inline static constexpr const char* MIN_DM_AIRDRAMON_NAME = MIN_DM_AIRDRAMON_NAME_ARR;
inline static constexpr size_t MIN_DM_AIRDRAMON_NAME_LEN = sizeof(MIN_DM_AIRDRAMON_NAME_ARR)-1;
inline static constexpr char MIN_DM_AIRDRAMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "dm:Airdramon";
inline static constexpr const char* MIN_DM_AIRDRAMON_FQNAME = MIN_DM_AIRDRAMON_FQNAME_ARR;
inline static constexpr size_t MIN_DM_AIRDRAMON_FQNAME_LEN = sizeof(MIN_DM_AIRDRAMON_FQNAME_ARR)-1;
inline static constexpr int MIN_DM_AIRDRAMON_SPRITE_SHEET_COLS ASSETS_MIN_DM_DIMS_SECTION =    9;
inline static constexpr int MIN_DM_AIRDRAMON_SPRITE_SHEET_ROWS ASSETS_MIN_DM_DIMS_SECTION =    1;
inline static constexpr size_t MIN_DM_AIRDRAMON_SPRITE_SHEET_FRAMES_COUNT = 9;
inline static constexpr std::size_t MIN_DM_AIRDRAMON_ANIM_INDEX = 8;

// Name: Seadramon
inline static constexpr char MIN_DM_SEADRAMON_FQID_ARR[] CONFIG_STRING_SECTION = "dm:seadramon";
inline static constexpr const char* MIN_DM_SEADRAMON_FQID = MIN_DM_SEADRAMON_FQID_ARR;
inline static constexpr size_t MIN_DM_SEADRAMON_FQID_LEN = sizeof(MIN_DM_SEADRAMON_FQID_ARR)-1;
inline static constexpr char MIN_DM_SEADRAMON_ID_ARR[] CONFIG_STRING_SECTION = "seadramon";
inline static constexpr const char* MIN_DM_SEADRAMON_ID = MIN_DM_SEADRAMON_ID_ARR;
inline static constexpr size_t MIN_DM_SEADRAMON_ID_LEN = sizeof(MIN_DM_SEADRAMON_ID_ARR)-1;
inline static constexpr char MIN_DM_SEADRAMON_NAME_ARR[] CONFIG_STRING_SECTION = "Seadramon";
inline static constexpr const char* MIN_DM_SEADRAMON_NAME = MIN_DM_SEADRAMON_NAME_ARR;
inline static constexpr size_t MIN_DM_SEADRAMON_NAME_LEN = sizeof(MIN_DM_SEADRAMON_NAME_ARR)-1;
inline static constexpr char MIN_DM_SEADRAMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "dm:Seadramon";
inline static constexpr const char* MIN_DM_SEADRAMON_FQNAME = MIN_DM_SEADRAMON_FQNAME_ARR;
inline static constexpr size_t MIN_DM_SEADRAMON_FQNAME_LEN = sizeof(MIN_DM_SEADRAMON_FQNAME_ARR)-1;
inline static constexpr int MIN_DM_SEADRAMON_SPRITE_SHEET_COLS ASSETS_MIN_DM_DIMS_SECTION =    8;
inline static constexpr int MIN_DM_SEADRAMON_SPRITE_SHEET_ROWS ASSETS_MIN_DM_DIMS_SECTION =    1;
inline static constexpr size_t MIN_DM_SEADRAMON_SPRITE_SHEET_FRAMES_COUNT = 8;
inline static constexpr std::size_t MIN_DM_SEADRAMON_ANIM_INDEX = 9;

// Name: Numemon
inline static constexpr char MIN_DM_NUMEMON_FQID_ARR[] CONFIG_STRING_SECTION = "dm:numemon";
inline static constexpr const char* MIN_DM_NUMEMON_FQID = MIN_DM_NUMEMON_FQID_ARR;
inline static constexpr size_t MIN_DM_NUMEMON_FQID_LEN = sizeof(MIN_DM_NUMEMON_FQID_ARR)-1;
inline static constexpr char MIN_DM_NUMEMON_ID_ARR[] CONFIG_STRING_SECTION = "numemon";
inline static constexpr const char* MIN_DM_NUMEMON_ID = MIN_DM_NUMEMON_ID_ARR;
inline static constexpr size_t MIN_DM_NUMEMON_ID_LEN = sizeof(MIN_DM_NUMEMON_ID_ARR)-1;
inline static constexpr char MIN_DM_NUMEMON_NAME_ARR[] CONFIG_STRING_SECTION = "Numemon";
inline static constexpr const char* MIN_DM_NUMEMON_NAME = MIN_DM_NUMEMON_NAME_ARR;
inline static constexpr size_t MIN_DM_NUMEMON_NAME_LEN = sizeof(MIN_DM_NUMEMON_NAME_ARR)-1;
inline static constexpr char MIN_DM_NUMEMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "dm:Numemon";
inline static constexpr const char* MIN_DM_NUMEMON_FQNAME = MIN_DM_NUMEMON_FQNAME_ARR;
inline static constexpr size_t MIN_DM_NUMEMON_FQNAME_LEN = sizeof(MIN_DM_NUMEMON_FQNAME_ARR)-1;
inline static constexpr int MIN_DM_NUMEMON_SPRITE_SHEET_COLS ASSETS_MIN_DM_DIMS_SECTION =    9;
inline static constexpr int MIN_DM_NUMEMON_SPRITE_SHEET_ROWS ASSETS_MIN_DM_DIMS_SECTION =    1;
inline static constexpr size_t MIN_DM_NUMEMON_SPRITE_SHEET_FRAMES_COUNT = 9;
inline static constexpr std::size_t MIN_DM_NUMEMON_ANIM_INDEX = 10;

// Name: Metal Greymon
inline static constexpr char MIN_DM_METAL_GREYMON_FQID_ARR[] CONFIG_STRING_SECTION = "dm:metal_greymon";
inline static constexpr const char* MIN_DM_METAL_GREYMON_FQID = MIN_DM_METAL_GREYMON_FQID_ARR;
inline static constexpr size_t MIN_DM_METAL_GREYMON_FQID_LEN = sizeof(MIN_DM_METAL_GREYMON_FQID_ARR)-1;
inline static constexpr char MIN_DM_METAL_GREYMON_ID_ARR[] CONFIG_STRING_SECTION = "metal_greymon";
inline static constexpr const char* MIN_DM_METAL_GREYMON_ID = MIN_DM_METAL_GREYMON_ID_ARR;
inline static constexpr size_t MIN_DM_METAL_GREYMON_ID_LEN = sizeof(MIN_DM_METAL_GREYMON_ID_ARR)-1;
inline static constexpr char MIN_DM_METAL_GREYMON_NAME_ARR[] CONFIG_STRING_SECTION = "Metal Greymon";
inline static constexpr const char* MIN_DM_METAL_GREYMON_NAME = MIN_DM_METAL_GREYMON_NAME_ARR;
inline static constexpr size_t MIN_DM_METAL_GREYMON_NAME_LEN = sizeof(MIN_DM_METAL_GREYMON_NAME_ARR)-1;
inline static constexpr char MIN_DM_METAL_GREYMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "dm:Metal Greymon";
inline static constexpr const char* MIN_DM_METAL_GREYMON_FQNAME = MIN_DM_METAL_GREYMON_FQNAME_ARR;
inline static constexpr size_t MIN_DM_METAL_GREYMON_FQNAME_LEN = sizeof(MIN_DM_METAL_GREYMON_FQNAME_ARR)-1;
inline static constexpr int MIN_DM_METAL_GREYMON_SPRITE_SHEET_COLS ASSETS_MIN_DM_DIMS_SECTION =    9;
inline static constexpr int MIN_DM_METAL_GREYMON_SPRITE_SHEET_ROWS ASSETS_MIN_DM_DIMS_SECTION =    1;
inline static constexpr size_t MIN_DM_METAL_GREYMON_SPRITE_SHEET_FRAMES_COUNT = 9;
inline static constexpr std::size_t MIN_DM_METAL_GREYMON_ANIM_INDEX = 11;

// Name: Mamemon
inline static constexpr char MIN_DM_MAMEMON_FQID_ARR[] CONFIG_STRING_SECTION = "dm:mamemon";
inline static constexpr const char* MIN_DM_MAMEMON_FQID = MIN_DM_MAMEMON_FQID_ARR;
inline static constexpr size_t MIN_DM_MAMEMON_FQID_LEN = sizeof(MIN_DM_MAMEMON_FQID_ARR)-1;
inline static constexpr char MIN_DM_MAMEMON_ID_ARR[] CONFIG_STRING_SECTION = "mamemon";
inline static constexpr const char* MIN_DM_MAMEMON_ID = MIN_DM_MAMEMON_ID_ARR;
inline static constexpr size_t MIN_DM_MAMEMON_ID_LEN = sizeof(MIN_DM_MAMEMON_ID_ARR)-1;
inline static constexpr char MIN_DM_MAMEMON_NAME_ARR[] CONFIG_STRING_SECTION = "Mamemon";
inline static constexpr const char* MIN_DM_MAMEMON_NAME = MIN_DM_MAMEMON_NAME_ARR;
inline static constexpr size_t MIN_DM_MAMEMON_NAME_LEN = sizeof(MIN_DM_MAMEMON_NAME_ARR)-1;
inline static constexpr char MIN_DM_MAMEMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "dm:Mamemon";
inline static constexpr const char* MIN_DM_MAMEMON_FQNAME = MIN_DM_MAMEMON_FQNAME_ARR;
inline static constexpr size_t MIN_DM_MAMEMON_FQNAME_LEN = sizeof(MIN_DM_MAMEMON_FQNAME_ARR)-1;
inline static constexpr int MIN_DM_MAMEMON_SPRITE_SHEET_COLS ASSETS_MIN_DM_DIMS_SECTION =    9;
inline static constexpr int MIN_DM_MAMEMON_SPRITE_SHEET_ROWS ASSETS_MIN_DM_DIMS_SECTION =    1;
inline static constexpr size_t MIN_DM_MAMEMON_SPRITE_SHEET_FRAMES_COUNT = 9;
inline static constexpr std::size_t MIN_DM_MAMEMON_ANIM_INDEX = 12;

// Name: Monzaemon
inline static constexpr char MIN_DM_MONZAEMON_FQID_ARR[] CONFIG_STRING_SECTION = "dm:monzaemon";
inline static constexpr const char* MIN_DM_MONZAEMON_FQID = MIN_DM_MONZAEMON_FQID_ARR;
inline static constexpr size_t MIN_DM_MONZAEMON_FQID_LEN = sizeof(MIN_DM_MONZAEMON_FQID_ARR)-1;
inline static constexpr char MIN_DM_MONZAEMON_ID_ARR[] CONFIG_STRING_SECTION = "monzaemon";
inline static constexpr const char* MIN_DM_MONZAEMON_ID = MIN_DM_MONZAEMON_ID_ARR;
inline static constexpr size_t MIN_DM_MONZAEMON_ID_LEN = sizeof(MIN_DM_MONZAEMON_ID_ARR)-1;
inline static constexpr char MIN_DM_MONZAEMON_NAME_ARR[] CONFIG_STRING_SECTION = "Monzaemon";
inline static constexpr const char* MIN_DM_MONZAEMON_NAME = MIN_DM_MONZAEMON_NAME_ARR;
inline static constexpr size_t MIN_DM_MONZAEMON_NAME_LEN = sizeof(MIN_DM_MONZAEMON_NAME_ARR)-1;
inline static constexpr char MIN_DM_MONZAEMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "dm:Monzaemon";
inline static constexpr const char* MIN_DM_MONZAEMON_FQNAME = MIN_DM_MONZAEMON_FQNAME_ARR;
inline static constexpr size_t MIN_DM_MONZAEMON_FQNAME_LEN = sizeof(MIN_DM_MONZAEMON_FQNAME_ARR)-1;
inline static constexpr int MIN_DM_MONZAEMON_SPRITE_SHEET_COLS ASSETS_MIN_DM_DIMS_SECTION =    9;
inline static constexpr int MIN_DM_MONZAEMON_SPRITE_SHEET_ROWS ASSETS_MIN_DM_DIMS_SECTION =    1;
inline static constexpr size_t MIN_DM_MONZAEMON_SPRITE_SHEET_FRAMES_COUNT = 9;
inline static constexpr std::size_t MIN_DM_MONZAEMON_ANIM_INDEX = 13;

inline static constexpr std::size_t MIN_DM_ANIM_COUNT = 14;
}  // namespace bongocat::assets

#endif  // MIN_DM_EMBEDDED_ASSETS_HPP