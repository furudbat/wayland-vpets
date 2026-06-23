#ifndef BONGOCAT_BONGOCAT_H
#define BONGOCAT_BONGOCAT_H

#include "utils/error.h"
#include "utils/memory.h"

#include <cstddef>
#include <cstdint>

// =============================================================================
// VERSION
// =============================================================================

// Version
inline static constexpr const char *BONGOCAT_VERSION = "5.0.0";

// =============================================================================
// COMPILE-TIME CONSTANTS
// =============================================================================

// Common constants
inline static constexpr int32_t DEFAULT_SCREEN_WIDTH = 1920;
inline static constexpr int32_t DEFAULT_BAR_HEIGHT = 40;
static inline constexpr int32_t DEFAULT_FPS = 60;
inline static constexpr int32_t RGBA_CHANNELS = 4;
inline static constexpr int32_t BGRA_CHANNELS = 4;

namespace bongocat {
template <typename T>
struct created_result_t {
  T result{};
  bongocat_error_t error{bongocat_error_t::BONGOCAT_SUCCESS};

  created_result_t() = default;
  explicit(false) created_result_t(bongocat_error_t err) : error(err) {}
  explicit(false) created_result_t(T&& res) : result(bongocat::move(res)) {}
};

// feature flags
namespace features {
  // experimental
  inline static constexpr bool BongocatIdleAnimation = false;
  inline static constexpr bool BongocatBoringAnimation = false;

#ifndef NDEBUG
  inline static constexpr bool Debug = true;
#else
  inline static constexpr bool Debug = false;
#endif

#if !defined(BONGOCAT_DISABLE_MEMORY_STATISTICS) || defined(BONGOCAT_ENABLE_MEMORY_STATISTICS)
  inline static constexpr bool EnableMemoryStatistics = true;
#else
  inline static constexpr bool EnableMemoryStatistics = false;
#endif

#if !defined(BONGOCAT_DISABLE_LOGGER) || defined(BONGOCAT_ENABLE_LOGGER)
  inline static constexpr bool EnableLogger = true;
#else
  inline static constexpr bool EnableLogger = false;
#endif

#ifdef FEATURE_PRELOAD_ASSETS
  inline static constexpr bool EnablePreloadAssets = true;
#else
  inline static constexpr bool EnablePreloadAssets = false;
#endif

#ifdef FEATURE_LAZY_LOAD_ASSETS
  inline static constexpr bool EnableLazyLoadAssets = true;
#else
  inline static constexpr bool EnableLazyLoadAssets = false;
#endif

#ifdef FEATURE_EVOLUTION
  inline static constexpr bool EnableEvolution = true;
#else
  inline static constexpr bool EnableEvolution = false;
#endif
}  // namespace features

// Global constants
namespace input {
  inline static constexpr size_t MAX_INPUT_DEVICES = 256;
  static_assert(MAX_INPUT_DEVICES <= INT32_MAX);
}  // namespace input
namespace platform {
  inline static constexpr double ENABLED_MIN_CPU_PERCENT = 1.0;             // in percent
  inline static constexpr double TRIGGER_ANIMATION_CPU_DIFF_PERCENT = 1.0;  // in percent
}  // namespace platform

template <typename Enum>
concept FlagEnum = std::is_enum_v<Enum> && (std::is_same_v<std::underlying_type_t<Enum>, uint32_t> ||
                                            std::is_same_v<std::underlying_type_t<Enum>, uint64_t>);
template <FlagEnum Enum>
BONGOCAT_NODISCARD constexpr Enum flag_or(Enum lhs, Enum rhs) noexcept {
  using U = std::underlying_type_t<Enum>;
  return static_cast<Enum>(static_cast<U>(lhs) | static_cast<U>(rhs));
}
template <FlagEnum Enum>
BONGOCAT_NODISCARD constexpr Enum flag_and(Enum lhs, Enum rhs) noexcept {
  using U = std::underlying_type_t<Enum>;
  return static_cast<Enum>(static_cast<U>(lhs) & static_cast<U>(rhs));
}
template <FlagEnum Enum>
BONGOCAT_NODISCARD constexpr Enum flag_xor(Enum lhs, Enum rhs) noexcept {
  using U = std::underlying_type_t<Enum>;
  return static_cast<Enum>(static_cast<U>(lhs) ^ static_cast<U>(rhs));
}
template <FlagEnum Enum>
BONGOCAT_NODISCARD constexpr Enum flag_not(Enum rhs) noexcept {
  using U = std::underlying_type_t<Enum>;
  return static_cast<Enum>(~static_cast<U>(rhs));
}
template <FlagEnum Enum>
BONGOCAT_NODISCARD constexpr Enum flag_add(Enum lhs, Enum rhs) noexcept {
  return flag_or(lhs, rhs);
}
template <FlagEnum Enum>
BONGOCAT_NODISCARD constexpr Enum flag_remove(Enum lhs, Enum rhs) noexcept {
  return flag_and(lhs, flag_not(rhs));
}
template <FlagEnum Enum>
BONGOCAT_NODISCARD constexpr Enum flag_assign(Enum lhs, Enum rhs) noexcept {
  return flag_and(lhs, rhs);
}
template <FlagEnum Enum>
BONGOCAT_NODISCARD constexpr bool has_flag(Enum value, Enum flag) noexcept {
  return flag_and(value, flag) == flag;
}
template <FlagEnum Enum>
BONGOCAT_NODISCARD constexpr bool has_any_flag(Enum value, Enum flag) noexcept {
  using U = std::underlying_type_t<Enum>;
  return static_cast<U>(flag_and(value, flag)) != U{0};
}
}  // namespace bongocat

#endif  // BONGOCAT_BONGOCAT_H