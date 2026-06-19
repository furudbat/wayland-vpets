#ifndef BONGOCAT_EMBEDDED_ASSETS_BONGOCAT_HPP
#define BONGOCAT_EMBEDDED_ASSETS_BONGOCAT_HPP

#include <cstddef>

namespace bongocat::assets {
// Name: Bongo Cat
inline static constexpr char BONGOCAT_FQID_ARR[] CONFIG_STRING_SECTION = "bongocat";
inline static constexpr const char *BONGOCAT_FQID CONFIG_STRING_SECTION = BONGOCAT_FQID_ARR;
inline static constexpr std::size_t BONGOCAT_FQID_LEN CONFIG_STRING_SECTION = sizeof(BONGOCAT_FQID_ARR) - 1;
inline static constexpr char BONGOCAT_ID_ARR[] CONFIG_STRING_SECTION = "bongocat";
inline static constexpr const char *BONGOCAT_ID CONFIG_STRING_SECTION = BONGOCAT_ID_ARR;
inline static constexpr std::size_t BONGOCAT_ID_LEN CONFIG_STRING_SECTION = sizeof(BONGOCAT_ID_ARR) - 1;
inline static constexpr char BONGOCAT_NAME_ARR[] CONFIG_STRING_SECTION = "bongocat";
inline static constexpr const char *BONGOCAT_NAME CONFIG_STRING_SECTION = BONGOCAT_NAME_ARR;
inline static constexpr std::size_t BONGOCAT_NAME_LEN CONFIG_STRING_SECTION = sizeof(BONGOCAT_NAME_ARR) - 1;
inline static constexpr char BONGOCAT_FQNAME_ARR[] CONFIG_STRING_SECTION = "bongocat";
inline static constexpr const char *BONGOCAT_FQNAME CONFIG_STRING_SECTION = BONGOCAT_FQNAME_ARR;
inline static constexpr std::size_t BONGOCAT_FQNAME_LEN CONFIG_STRING_SECTION = sizeof(BONGOCAT_FQNAME_ARR) - 1;
inline static constexpr std::size_t BONGOCAT_ANIM_INDEX ASSETS_DATA3_SECTION = 0;

inline static constexpr std::size_t BONGOCAT_ANIM_COUNT = 1;
}  // namespace bongocat::assets

#endif  // BONGOCAT_EMBEDDED_ASSETS_BONGOCAT_HPP
