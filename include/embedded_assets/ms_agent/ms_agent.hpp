#ifndef BONGOCAT_EMBEDDED_ASSETS_CLIPPY_HPP
#define BONGOCAT_EMBEDDED_ASSETS_CLIPPY_HPP

#include <cstddef>
#include "embedded_assets/assets.h"

namespace bongocat::assets {
// Name: Clippy
inline static constexpr size_t CLIPPY_SPRITE_SHEET_COLS = 40;
inline static constexpr size_t CLIPPY_SPRITE_SHEET_ROWS = 6;
inline static constexpr size_t CLIPPY_FRAMES_IDLE = 4;
inline static constexpr size_t CLIPPY_FRAMES_BORING = 40;
inline static constexpr size_t CLIPPY_FRAMES_START_WRITING = 9;
inline static constexpr size_t CLIPPY_FRAMES_WRITING = 35;
inline static constexpr size_t CLIPPY_FRAMES_END_WRITING = 5;
inline static constexpr size_t CLIPPY_FRAMES_SLEEP = 19;
inline static constexpr size_t CLIPPY_FRAMES_WAKE_UP = 16;

inline static constexpr char CLIPPY_FQID_ARR[] CONFIG_STRING_SECTION = "ms_agent:clippy";
inline static constexpr const char *CLIPPY_FQID CONFIG_STRING_REF_SECTION = CLIPPY_FQID_ARR;
inline static constexpr std::size_t CLIPPY_FQID_LEN CONFIG_STRING_SECTION = sizeof(CLIPPY_FQID_ARR) - 1;
inline static constexpr char CLIPPY_ID_ARR[] CONFIG_STRING_SECTION = "clippy";
inline static constexpr const char *CLIPPY_ID CONFIG_STRING_REF_SECTION = CLIPPY_ID_ARR;
inline static constexpr std::size_t CLIPPY_ID_LEN CONFIG_STRING_SECTION = sizeof(CLIPPY_ID_ARR) - 1;
inline static constexpr char CLIPPY_NAME_ARR[] CONFIG_STRING_SECTION = "Clippy";
inline static constexpr const char *CLIPPY_NAME CONFIG_STRING_REF_SECTION = CLIPPY_NAME_ARR;
inline static constexpr std::size_t CLIPPY_NAME_LEN CONFIG_STRING_SECTION = sizeof(CLIPPY_NAME_ARR) - 1;
inline static constexpr char CLIPPY_FQNAME_ARR[] CONFIG_STRING_SECTION = "ms_agent:Clippy";
inline static constexpr const char *CLIPPY_FQNAME CONFIG_STRING_REF_SECTION = CLIPPY_FQNAME_ARR;
inline static constexpr std::size_t CLIPPY_FQNAME_LEN CONFIG_STRING_SECTION = sizeof(CLIPPY_FQNAME_ARR) - 1;
inline static constexpr size_t CLIPPY_ANIM_INDEX ASSETS_INDICES_SECTION = 0;

#ifdef FEATURE_MORE_MS_AGENT_EMBEDDED_ASSETS
// Name: Links
inline static constexpr size_t LINKS_SPRITE_SHEET_COLS = 35;
inline static constexpr size_t LINKS_SPRITE_SHEET_ROWS = 6;
inline static constexpr size_t LINKS_FRAMES_IDLE = 3;
inline static constexpr size_t LINKS_FRAMES_BORING = 18;
inline static constexpr size_t LINKS_FRAMES_START_WRITING = 13;
inline static constexpr size_t LINKS_FRAMES_WRITING = 35;
inline static constexpr size_t LINKS_FRAMES_END_WRITING = 5;
inline static constexpr size_t LINKS_FRAMES_SLEEP = 20;
inline static constexpr size_t LINKS_FRAMES_WAKE_UP = 14;

inline static constexpr char LINKS_FQID_ARR[] CONFIG_STRING_SECTION = "ms_agent:links";
inline static constexpr const char *LINKS_FQID CONFIG_STRING_REF_SECTION = LINKS_FQID_ARR;
inline static constexpr std::size_t LINKS_FQID_LEN CONFIG_STRING_SECTION = sizeof(LINKS_FQID_ARR) - 1;
inline static constexpr char LINKS_ID_ARR[] CONFIG_STRING_SECTION = "links";
inline static constexpr const char *LINKS_ID CONFIG_STRING_REF_SECTION = LINKS_ID_ARR;
inline static constexpr std::size_t LINKS_ID_LEN CONFIG_STRING_SECTION = sizeof(LINKS_ID_ARR) - 1;
inline static constexpr char LINKS_NAME_ARR[] CONFIG_STRING_SECTION = "Links";
inline static constexpr const char *LINKS_NAME CONFIG_STRING_REF_SECTION = LINKS_NAME_ARR;
inline static constexpr std::size_t LINKS_NAME_LEN CONFIG_STRING_SECTION = sizeof(LINKS_NAME_ARR) - 1;
inline static constexpr char LINKS_FQNAME_ARR[] CONFIG_STRING_SECTION = "ms_agent:Links";
inline static constexpr const char *LINKS_FQNAME CONFIG_STRING_REF_SECTION = LINKS_FQNAME_ARR;
inline static constexpr std::size_t LINKS_FQNAME_LEN CONFIG_STRING_SECTION = sizeof(LINKS_FQNAME_ARR) - 1;
inline static constexpr size_t LINKS_ANIM_INDEX ASSETS_INDICES_SECTION = 1;

// Name: Rover
inline static constexpr size_t ROVER_SPRITE_SHEET_COLS = 102;
inline static constexpr size_t ROVER_SPRITE_SHEET_ROWS = 6;
inline static constexpr size_t ROVER_FRAMES_IDLE = 1;
inline static constexpr size_t ROVER_FRAMES_BORING = 102;
inline static constexpr size_t ROVER_FRAMES_START_WRITING = 9;
inline static constexpr size_t ROVER_FRAMES_WRITING = 34;
inline static constexpr size_t ROVER_FRAMES_END_WRITING = 12;
inline static constexpr size_t ROVER_FRAMES_SLEEP = 85;
inline static constexpr size_t ROVER_FRAMES_WAKE_UP = 14;

inline static constexpr char ROVER_FQID_ARR[] CONFIG_STRING_SECTION = "ms_agent:rover";
inline static constexpr const char *ROVER_FQID CONFIG_STRING_REF_SECTION = ROVER_FQID_ARR;
inline static constexpr std::size_t ROVER_FQID_LEN CONFIG_STRING_SECTION = sizeof(ROVER_FQID_ARR) - 1;
inline static constexpr char ROVER_ID_ARR[] CONFIG_STRING_SECTION = "rover";
inline static constexpr const char *ROVER_ID CONFIG_STRING_REF_SECTION = ROVER_ID_ARR;
inline static constexpr std::size_t ROVER_ID_LEN CONFIG_STRING_SECTION = sizeof(ROVER_ID_ARR) - 1;
inline static constexpr char ROVER_NAME_ARR[] CONFIG_STRING_SECTION = "Rover";
inline static constexpr const char *ROVER_NAME CONFIG_STRING_REF_SECTION = ROVER_NAME_ARR;
inline static constexpr std::size_t ROVER_NAME_LEN CONFIG_STRING_SECTION = sizeof(ROVER_NAME_ARR) - 1;
inline static constexpr char ROVER_FQNAME_ARR[] CONFIG_STRING_SECTION = "ms_agent:Rover";
inline static constexpr const char *ROVER_FQNAME CONFIG_STRING_REF_SECTION = ROVER_FQNAME_ARR;
inline static constexpr std::size_t ROVER_FQNAME_LEN CONFIG_STRING_SECTION = sizeof(ROVER_FQNAME_ARR) - 1;
inline static constexpr size_t ROVER_ANIM_INDEX ASSETS_INDICES_SECTION = 2;

// Name: Merlin
inline static constexpr size_t MERLIN_SPRITE_SHEET_COLS = 22;
inline static constexpr size_t MERLIN_SPRITE_SHEET_ROWS = 6;
inline static constexpr size_t MERLIN_FRAMES_IDLE = 1;
inline static constexpr size_t MERLIN_FRAMES_BORING = 22;
inline static constexpr size_t MERLIN_FRAMES_START_WRITING = 6;
inline static constexpr size_t MERLIN_FRAMES_WRITING = 14;
inline static constexpr size_t MERLIN_FRAMES_END_WRITING = 6;
inline static constexpr size_t MERLIN_FRAMES_SLEEP = 20;
inline static constexpr size_t MERLIN_FRAMES_WAKE_UP = 6;

inline static constexpr char MERLIN_FQID_ARR[] CONFIG_STRING_SECTION = "ms_agent:merlin";
inline static constexpr const char *MERLIN_FQID CONFIG_STRING_REF_SECTION = MERLIN_FQID_ARR;
inline static constexpr std::size_t MERLIN_FQID_LEN CONFIG_STRING_SECTION = sizeof(MERLIN_FQID_ARR) - 1;
inline static constexpr char MERLIN_ID_ARR[] CONFIG_STRING_SECTION = "merlin";
inline static constexpr const char *MERLIN_ID CONFIG_STRING_REF_SECTION = MERLIN_ID_ARR;
inline static constexpr std::size_t MERLIN_ID_LEN CONFIG_STRING_SECTION = sizeof(MERLIN_ID_ARR) - 1;
inline static constexpr char MERLIN_NAME_ARR[] CONFIG_STRING_SECTION = "Merlin";
inline static constexpr const char *MERLIN_NAME CONFIG_STRING_REF_SECTION = MERLIN_NAME_ARR;
inline static constexpr std::size_t MERLIN_NAME_LEN CONFIG_STRING_SECTION = sizeof(MERLIN_NAME_ARR) - 1;
inline static constexpr char MERLIN_FQNAME_ARR[] CONFIG_STRING_SECTION = "ms_agent:Merlin";
inline static constexpr const char *MERLIN_FQNAME CONFIG_STRING_REF_SECTION = MERLIN_FQNAME_ARR;
inline static constexpr std::size_t MERLIN_FQNAME_LEN CONFIG_STRING_SECTION = sizeof(MERLIN_FQNAME_ARR) - 1;
inline static constexpr size_t MERLIN_ANIM_INDEX ASSETS_INDICES_SECTION = 3;

inline static constexpr size_t MS_AGENTS_ANIM_COUNT = 4;
/// @TODO: determine the biggest cols from MS agents
inline static constexpr size_t MS_AGENT_MAX_SPRITE_SHEET_COL_FRAMES = ROVER_SPRITE_SHEET_COLS;
#else
inline static constexpr size_t MS_AGENTS_ANIM_COUNT = 1;
inline static constexpr size_t MS_AGENT_MAX_SPRITE_SHEET_COL_FRAMES = CLIPPY_SPRITE_SHEET_COLS;
#endif
}  // namespace bongocat::assets

#endif  // BONGOCAT_EMBEDDED_ASSETS_CLIPPY_HPP
