#ifndef BONGOCAT_BONGOCAT_H
#define BONGOCAT_BONGOCAT_H

#include <cstdint>
#include <cstddef>
#include "utils/error.h"
#include "utils/memory.h"

// Version
inline static constexpr const char* BONGOCAT_VERSION = "3.3.1";

// Common constants
inline static constexpr int32_t DEFAULT_SCREEN_WIDTH = 1920;
inline static constexpr int32_t DEFAULT_BAR_HEIGHT = 40;
static inline constexpr int32_t DEFAULT_FPS = 60;
inline static constexpr int32_t RGBA_CHANNELS = 4;
inline static constexpr int32_t BGRA_CHANNELS = 4;

namespace bongocat {
    template<typename T>
    struct created_result_t {
        T result{};
        bongocat_error_t error{bongocat_error_t::BONGOCAT_SUCCESS};

        created_result_t() = default;
        explicit(false) created_result_t(bongocat_error_t err) : error(err) {}
        explicit(false) created_result_t(T&& res) : result(bongocat::move(res)), error(bongocat_error_t::BONGOCAT_SUCCESS) {}
    };

    namespace features {
        // experimental
        inline static constexpr bool BongocatIdleAnimation = false;
        inline static constexpr bool BongocatBoringAnimation = false;


#ifndef NDEBUG
        inline static constexpr bool Debug = true;
#else
        inline static constexpr bool Debug = false;
#endif

#ifdef FEATURE_BONGOCAT_EMBEDDED_ASSETS
        inline static constexpr bool EnableBongocatEmbeddedAssets = true;
#else
        inline static constexpr bool EnableBongocatEmbeddedAssets = false;
#endif

#ifdef FEATURE_ENABLE_DM_EMBEDDED_ASSETS
        inline static constexpr bool EnableDmEmbeddedAssets = true;
#ifdef FEATURE_DM_EMBEDDED_ASSETS
        inline static constexpr bool EnableFullDmEmbeddedAssets = true;
#else
        inline static constexpr bool EnableFullDmEmbeddedAssets = false;
#endif
#ifdef FEATURE_DM20_EMBEDDED_ASSETS
        inline static constexpr bool EnableDm20EmbeddedAssets = true;
#else
        inline static constexpr bool EnableDm20EmbeddedAssets = false;
#endif
#ifdef FEATURE_DMC_EMBEDDED_ASSETS
        inline static constexpr bool EnableDmcEmbeddedAssets = true;
#else
        inline static constexpr bool EnableDmcEmbeddedAssets = false;
#endif
#ifdef FEATURE_DMX_EMBEDDED_ASSETS
        inline static constexpr bool EnableDmxEmbeddedAssets = true;
#else
        inline static constexpr bool EnableDmxEmbeddedAssets = false;
#endif
#ifdef FEATURE_PEN_EMBEDDED_ASSETS
        inline static constexpr bool EnablePenEmbeddedAssets = true;
#else
        inline static constexpr bool EnablePenEmbeddedAssets = false;
#endif
#ifdef FEATURE_PEN20_EMBEDDED_ASSETS
        inline static constexpr bool EnablePen20EmbeddedAssets = true;
#else
        inline static constexpr bool EnablePen20EmbeddedAssets = false;
#endif
#ifdef FEATURE_DMALL_EMBEDDED_ASSETS
        inline static constexpr bool EnableDmAllEmbeddedAssets = true;
#else
        inline static constexpr bool EnableDmAllEmbeddedAssets = false;
#endif
#if !defined(FEATURE_DM_EMBEDDED_ASSETS) && !defined(FEATURE_DM20_EMBEDDED_ASSETS) && !defined(FEATURE_DMC_EMBEDDED_ASSETS) && !defined(FEATURE_DMX_EMBEDDED_ASSETS) && !defined(FEATURE_PEN20_EMBEDDED_ASSETS) && !defined(FEATURE_DMALL_EMBEDDED_ASSETS)
        inline static constexpr bool EnableMinDmEmbeddedAssets = true;
#else
        inline static constexpr bool EnableMinDmEmbeddedAssets = false;
#endif
#else
        inline static constexpr bool EnableDmEmbeddedAssets = false;
        inline static constexpr bool EnableFullDmEmbeddedAssets = false;
        inline static constexpr bool EnableDm20EmbeddedAssets = false;
        inline static constexpr bool EnableDmcEmbeddedAssets = false;
        inline static constexpr bool EnableDmxEmbeddedAssets = false;
        inline static constexpr bool EnablePenEmbeddedAssets = false;
        inline static constexpr bool EnablePen20EmbeddedAssets = false;
        inline static constexpr bool EnableMinDmEmbeddedAssets = false;
        inline static constexpr bool EnableDmAllEmbeddedAssets = false;
#endif

#ifdef FEATURE_MS_AGENT_EMBEDDED_ASSETS
        inline static constexpr bool EnableMsAgentEmbeddedAssets = true;
#else
        inline static constexpr bool EnableMsAgentEmbeddedAssets = false;
#endif

#ifdef FEATURE_PKMN_EMBEDDED_ASSETS
        inline static constexpr bool EnablePkmnEmbeddedAssets = true;
#else
        inline static constexpr bool EnablePkmnEmbeddedAssets = false;
#endif

#ifdef FEATURE_MISC_EMBEDDED_ASSETS
        inline static constexpr bool EnableMiscEmbeddedAssets = true;
#else
        inline static constexpr bool EnableMiscEmbeddedAssets = false;
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

#ifdef FEATURE_USE_HYBRID_IMAGE_BACKEND
        inline static constexpr bool UseHybridImageBackend = true;
#else
        inline static constexpr bool UseHybridImageBackend = false;

#ifdef FEATURE_USE_PNGLE
        inline static constexpr bool UsePngleImageBackend = true;
#else
        inline static constexpr bool UsePngleImageBackend = false;
#endif

#ifdef FEATURE_USE_STB_IMAGE
        inline static constexpr bool UseStbImageBackend = true;
#else
        inline static constexpr bool UseStbImageBackend = false;
#endif
#endif

#ifdef FEATURE_CUSTOM_SPRITE_SHEETS
        inline static constexpr bool EnableCustomSpriteSheetsAssets = true;
#else
        inline static constexpr bool EnableCustomSpriteSheetsAssets = false;
#endif

    }

    // Global constants
    namespace input {
        inline static constexpr size_t MAX_INPUT_DEVICES = 256;
        static_assert(MAX_INPUT_DEVICES <= INT32_MAX);
    }
    namespace platform {
        inline static constexpr double ENABLED_MIN_CPU_PERCENT = 1.0; // in percent
        inline static constexpr double TRIGGER_ANIMATION_CPU_DIFF_PERCENT = 1.0; // in percent
    }


    template <typename Enum>
    requires std::is_enum_v<Enum> &&
             (std::is_same_v<std::underlying_type_t<Enum>, uint32_t> || std::is_same_v<std::underlying_type_t<Enum>, uint64_t>)
    [[nodiscard]] inline constexpr Enum flag_or(Enum lhs, Enum rhs) noexcept {
        return static_cast<Enum>(static_cast<std::underlying_type_t<Enum>>(lhs) | static_cast<std::underlying_type_t<Enum>>(rhs));
    }
    template <typename Enum>
    requires std::is_enum_v<Enum> &&
             (std::is_same_v<std::underlying_type_t<Enum>, uint32_t> || std::is_same_v<std::underlying_type_t<Enum>, uint64_t>)
    [[nodiscard]] inline constexpr Enum flag_and(Enum lhs, Enum rhs) noexcept {
        return static_cast<Enum>(static_cast<std::underlying_type_t<Enum>>(lhs) & static_cast<std::underlying_type_t<Enum>>(rhs));
    }
    template <typename Enum>
    requires std::is_enum_v<Enum> &&
             (std::is_same_v<std::underlying_type_t<Enum>, uint32_t> || std::is_same_v<std::underlying_type_t<Enum>, uint64_t>)
    [[nodiscard]] inline constexpr Enum flag_xor(Enum lhs, Enum rhs) noexcept {
        return static_cast<Enum>(static_cast<std::underlying_type_t<Enum>>(lhs) ^ static_cast<std::underlying_type_t<Enum>>(rhs));
    }
    template <typename Enum>
    requires std::is_enum_v<Enum> &&
             (std::is_same_v<std::underlying_type_t<Enum>, uint32_t> || std::is_same_v<std::underlying_type_t<Enum>, uint64_t>)
    [[nodiscard]] inline constexpr Enum flag_not(Enum rhs) noexcept {
        return static_cast<Enum>(~static_cast<std::underlying_type_t<Enum>>(rhs));
    }
    template <typename Enum>
    requires std::is_enum_v<Enum> &&
             (std::is_same_v<std::underlying_type_t<Enum>, uint32_t> || std::is_same_v<std::underlying_type_t<Enum>, uint64_t>)
    [[nodiscard]] inline constexpr Enum flag_add(Enum lhs, Enum rhs) noexcept {
        lhs = flag_or(lhs, rhs);
        return lhs;
    }
    template <typename Enum>
    requires std::is_enum_v<Enum> &&
             (std::is_same_v<std::underlying_type_t<Enum>, uint32_t> || std::is_same_v<std::underlying_type_t<Enum>, uint64_t>)
    [[nodiscard]] inline constexpr Enum flag_remove(Enum lhs, Enum rhs) noexcept {
        return static_cast<Enum>(static_cast<uint32_t>(lhs) & ~static_cast<uint32_t>(rhs));
    }
    template <typename Enum>
    requires std::is_enum_v<Enum> &&
             (std::is_same_v<std::underlying_type_t<Enum>, uint32_t> || std::is_same_v<std::underlying_type_t<Enum>, uint64_t>)
    [[nodiscard]] inline constexpr Enum flag_assign(Enum lhs, Enum rhs) noexcept {
        lhs = flag_and(lhs, rhs);
        return lhs;
    }
    template <typename Enum>
    requires std::is_enum_v<Enum> &&
             (std::is_same_v<std::underlying_type_t<Enum>, uint32_t> || std::is_same_v<std::underlying_type_t<Enum>, uint64_t>)
    [[nodiscard]] inline constexpr bool has_flag(Enum value, Enum flag) noexcept {
        return (static_cast<uint32_t>(value) & static_cast<uint32_t>(flag)) != 0;
    }
}

#endif // BONGOCAT_BONGOCAT_H