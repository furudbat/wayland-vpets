#ifndef BONGOCAT_EMBEDDED_ASSETS_BONGOCAT_HPP
#define BONGOCAT_EMBEDDED_ASSETS_BONGOCAT_HPP

#include "embedded_assets/assets.h"
#include <cstddef>

namespace bongocat::assets {
// Name: Bongo Cat
inline static constexpr char BONGOCAT_FQID_ARR[] CONFIG_STRING_SECTION = "bongocat";
inline static constexpr const char *BONGOCAT_FQID = BONGOCAT_FQID_ARR;
inline static constexpr std::size_t BONGOCAT_FQID_LEN = sizeof(BONGOCAT_FQID_ARR) - 1;
inline static constexpr char BONGOCAT_ID_ARR[] CONFIG_STRING_SECTION = "bongocat";
inline static constexpr const char *BONGOCAT_ID = BONGOCAT_ID_ARR;
inline static constexpr std::size_t BONGOCAT_ID_LEN = sizeof(BONGOCAT_ID_ARR) - 1;
inline static constexpr char BONGOCAT_NAME_ARR[] CONFIG_STRING_SECTION = "bongocat";
inline static constexpr const char *BONGOCAT_NAME = BONGOCAT_NAME_ARR;
inline static constexpr std::size_t BONGOCAT_NAME_LEN = sizeof(BONGOCAT_NAME_ARR) - 1;
inline static constexpr char BONGOCAT_FQNAME_ARR[] CONFIG_STRING_SECTION = "bongocat";
inline static constexpr const char *BONGOCAT_FQNAME = BONGOCAT_FQNAME_ARR;
inline static constexpr std::size_t BONGOCAT_FQNAME_LEN = sizeof(BONGOCAT_FQNAME_ARR) - 1;
inline static constexpr std::size_t BONGOCAT_ANIM_INDEX = 0;

inline static constexpr std::size_t BONGOCAT_ANIM_COUNT = 1;
}  // namespace bongocat::assets

#endif  // BONGOCAT_EMBEDDED_ASSETS_BONGOCAT_HPP
