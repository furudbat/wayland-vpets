#ifndef BONGOCAT_EMBEDDED_ASSETS_CLIPPY_HPP
#define BONGOCAT_EMBEDDED_ASSETS_CLIPPY_HPP

#include "embedded_assets/assets.h"
#include <cstddef>

// ms_agent
#define ASSETS_MS_AGENT_SPRITE_SETTINGS_SECTION(name) BONGOCAT_ASSETS_SET_SECTION_FOR(ms_agent, "sprite_settings", name)
#define ASSETS_MS_AGENT_DIMS_SECTION(name) BONGOCAT_ASSETS_SET_SECTION_FOR(ms_agent, "dims", name)
//#define ASSETS_MS_AGENT_EVOL_DATA_SECTION BONGOCAT_ASSETS_SET_SECTION(ms_agent, "evol_data")

namespace bongocat::assets {
// Name: Clippy
inline constexpr int CLIPPY_SPRITE_SHEET_COLS ASSETS_MS_AGENT_DIMS_SECTION(CLIPPY_SPRITE_SHEET_COLS) = 40;
inline constexpr int CLIPPY_SPRITE_SHEET_ROWS ASSETS_MS_AGENT_DIMS_SECTION(CLIPPY_SPRITE_SHEET_ROWS) = 6;
inline constexpr size_t CLIPPY_FRAMES_IDLE = 4;
inline constexpr size_t CLIPPY_FRAMES_BORING = 40;
inline constexpr size_t CLIPPY_FRAMES_START_WRITING = 9;
inline constexpr size_t CLIPPY_FRAMES_WRITING = 35;
inline constexpr size_t CLIPPY_FRAMES_END_WRITING = 5;
inline constexpr size_t CLIPPY_FRAMES_SLEEP = 19;
inline constexpr size_t CLIPPY_FRAMES_WAKE_UP = 16;

inline constexpr char CLIPPY_FQID_ARR[] CONFIG_STRING_SECTION(CLIPPY_FQID_ARR) = "ms_agent:clippy";
inline constexpr const char *CLIPPY_FQID = CLIPPY_FQID_ARR;
inline constexpr std::size_t CLIPPY_FQID_LEN = sizeof(CLIPPY_FQID_ARR) - 1;
inline constexpr char CLIPPY_ID_ARR[] CONFIG_STRING_SECTION(CLIPPY_ID_ARR) = "clippy";
inline constexpr const char *CLIPPY_ID = CLIPPY_ID_ARR;
inline constexpr std::size_t CLIPPY_ID_LEN = sizeof(CLIPPY_ID_ARR) - 1;
inline constexpr char CLIPPY_NAME_ARR[] CONFIG_STRING_SECTION(CLIPPY_NAME_ARR) = "Clippy";
inline constexpr const char *CLIPPY_NAME = CLIPPY_NAME_ARR;
inline constexpr std::size_t CLIPPY_NAME_LEN = sizeof(CLIPPY_NAME_ARR) - 1;
inline constexpr char CLIPPY_FQNAME_ARR[] CONFIG_STRING_SECTION(CLIPPY_FQNAME_ARR) = "ms_agent:Clippy";
inline constexpr const char *CLIPPY_FQNAME = CLIPPY_FQNAME_ARR;
inline constexpr std::size_t CLIPPY_FQNAME_LEN = sizeof(CLIPPY_FQNAME_ARR) - 1;
inline constexpr size_t CLIPPY_ANIM_INDEX = 0;

#ifdef FEATURE_MORE_MS_AGENT_EMBEDDED_ASSETS
// Name: Links
inline constexpr size_t LINKS_SPRITE_SHEET_COLS ASSETS_MS_AGENT_DIMS_SECTION(LINKS_SPRITE_SHEET_COLS) = 35;
inline constexpr size_t LINKS_SPRITE_SHEET_ROWS ASSETS_MS_AGENT_DIMS_SECTION(LINKS_SPRITE_SHEET_ROWS) = 6;
inline constexpr size_t LINKS_FRAMES_IDLE = 3;
inline constexpr size_t LINKS_FRAMES_BORING = 18;
inline constexpr size_t LINKS_FRAMES_START_WRITING = 13;
inline constexpr size_t LINKS_FRAMES_WRITING = 35;
inline constexpr size_t LINKS_FRAMES_END_WRITING = 5;
inline constexpr size_t LINKS_FRAMES_SLEEP = 20;
inline constexpr size_t LINKS_FRAMES_WAKE_UP = 14;

inline constexpr char LINKS_FQID_ARR[] CONFIG_STRING_SECTION(LINKS_FQID_ARR) = "ms_agent:links";
inline constexpr const char *LINKS_FQID = LINKS_FQID_ARR;
inline constexpr std::size_t LINKS_FQID_LEN = sizeof(LINKS_FQID_ARR) - 1;
inline constexpr char LINKS_ID_ARR[] CONFIG_STRING_SECTION(LINKS_ID_ARR) = "links";
inline constexpr const char *LINKS_ID = LINKS_ID_ARR;
inline constexpr std::size_t LINKS_ID_LEN = sizeof(LINKS_ID_ARR) - 1;
inline constexpr char LINKS_NAME_ARR[] CONFIG_STRING_SECTION(LINKS_NAME_ARR) = "Links";
inline constexpr const char *LINKS_NAME = LINKS_NAME_ARR;
inline constexpr std::size_t LINKS_NAME_LEN = sizeof(LINKS_NAME_ARR) - 1;
inline constexpr char LINKS_FQNAME_ARR[] CONFIG_STRING_SECTION(LINKS_FQNAME_ARR) = "ms_agent:Links";
inline constexpr const char *LINKS_FQNAME = LINKS_FQNAME_ARR;
inline constexpr std::size_t LINKS_FQNAME_LEN = sizeof(LINKS_FQNAME_ARR) - 1;
inline constexpr size_t LINKS_ANIM_INDEX = 1;

// Name: Rover
inline constexpr size_t ROVER_SPRITE_SHEET_COLS ASSETS_MS_AGENT_DIMS_SECTION(ROVER_SPRITE_SHEET_COLS) = 102;
inline constexpr size_t ROVER_SPRITE_SHEET_ROWS ASSETS_MS_AGENT_DIMS_SECTION(ROVER_SPRITE_SHEET_ROWS) = 6;
inline constexpr size_t ROVER_FRAMES_IDLE = 1;
inline constexpr size_t ROVER_FRAMES_BORING = 102;
inline constexpr size_t ROVER_FRAMES_START_WRITING = 9;
inline constexpr size_t ROVER_FRAMES_WRITING = 34;
inline constexpr size_t ROVER_FRAMES_END_WRITING = 12;
inline constexpr size_t ROVER_FRAMES_SLEEP = 85;
inline constexpr size_t ROVER_FRAMES_WAKE_UP = 14;

inline constexpr char ROVER_FQID_ARR[] CONFIG_STRING_SECTION(ROVER_FQID_ARR) = "ms_agent:rover";
inline constexpr const char *ROVER_FQID = ROVER_FQID_ARR;
inline constexpr std::size_t ROVER_FQID_LEN = sizeof(ROVER_FQID_ARR) - 1;
inline constexpr char ROVER_ID_ARR[] CONFIG_STRING_SECTION(ROVER_ID_ARR) = "rover";
inline constexpr const char *ROVER_ID = ROVER_ID_ARR;
inline constexpr std::size_t ROVER_ID_LEN = sizeof(ROVER_ID_ARR) - 1;
inline constexpr char ROVER_NAME_ARR[] CONFIG_STRING_SECTION(ROVER_NAME_ARR) = "Rover";
inline constexpr const char *ROVER_NAME = ROVER_NAME_ARR;
inline constexpr std::size_t ROVER_NAME_LEN = sizeof(ROVER_NAME_ARR) - 1;
inline constexpr char ROVER_FQNAME_ARR[] CONFIG_STRING_SECTION(ROVER_FQNAME_ARR) = "ms_agent:Rover";
inline constexpr const char *ROVER_FQNAME = ROVER_FQNAME_ARR;
inline constexpr std::size_t ROVER_FQNAME_LEN = sizeof(ROVER_FQNAME_ARR) - 1;
inline constexpr size_t ROVER_ANIM_INDEX = 2;

// Name: Merlin
inline constexpr size_t MERLIN_SPRITE_SHEET_COLS ASSETS_MS_AGENT_DIMS_SECTION(MERLIN_SPRITE_SHEET_COLS) = 22;
inline constexpr size_t MERLIN_SPRITE_SHEET_ROWS ASSETS_MS_AGENT_DIMS_SECTION(MERLIN_SPRITE_SHEET_ROWS) = 6;
inline constexpr size_t MERLIN_FRAMES_IDLE = 1;
inline constexpr size_t MERLIN_FRAMES_BORING = 22;
inline constexpr size_t MERLIN_FRAMES_START_WRITING = 6;
inline constexpr size_t MERLIN_FRAMES_WRITING = 14;
inline constexpr size_t MERLIN_FRAMES_END_WRITING = 6;
inline constexpr size_t MERLIN_FRAMES_SLEEP = 20;
inline constexpr size_t MERLIN_FRAMES_WAKE_UP = 6;

inline constexpr char MERLIN_FQID_ARR[] CONFIG_STRING_SECTION(MERLIN_FQID_ARR) = "ms_agent:merlin";
inline constexpr const char *MERLIN_FQID = MERLIN_FQID_ARR;
inline constexpr std::size_t MERLIN_FQID_LEN = sizeof(MERLIN_FQID_ARR) - 1;
inline constexpr char MERLIN_ID_ARR[] CONFIG_STRING_SECTION(MERLIN_ID_ARR) = "merlin";
inline constexpr const char *MERLIN_ID = MERLIN_ID_ARR;
inline constexpr std::size_t MERLIN_ID_LEN = sizeof(MERLIN_ID_ARR) - 1;
inline constexpr char MERLIN_NAME_ARR[] CONFIG_STRING_SECTION(MERLIN_NAME_ARR) = "Merlin";
inline constexpr const char *MERLIN_NAME = MERLIN_NAME_ARR;
inline constexpr std::size_t MERLIN_NAME_LEN = sizeof(MERLIN_NAME_ARR) - 1;
inline constexpr char MERLIN_FQNAME_ARR[] CONFIG_STRING_SECTION(MERLIN_FQNAME_ARR) = "ms_agent:Merlin";
inline constexpr const char *MERLIN_FQNAME = MERLIN_FQNAME_ARR;
inline constexpr std::size_t MERLIN_FQNAME_LEN = sizeof(MERLIN_FQNAME_ARR) - 1;
inline constexpr size_t MERLIN_ANIM_INDEX = 3;

static constexpr size_t MS_AGENTS_ANIM_COUNT = 4;
/// @TODO: determine the biggest cols from MS agents
static constexpr size_t MS_AGENT_MAX_SPRITE_SHEET_COL_FRAMES = ROVER_SPRITE_SHEET_COLS;
#else
static constexpr size_t MS_AGENTS_ANIM_COUNT = 1;
static constexpr size_t MS_AGENT_MAX_SPRITE_SHEET_COL_FRAMES = CLIPPY_SPRITE_SHEET_COLS;
#endif
}  // namespace bongocat::assets

#endif  // BONGOCAT_EMBEDDED_ASSETS_CLIPPY_HPP
