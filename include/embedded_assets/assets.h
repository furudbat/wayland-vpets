#ifndef BONGOCAT_ASSETS_MACROS_IMAGE_H
#define BONGOCAT_ASSETS_MACROS_IMAGE_H

#include <stdint.h>
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

#ifndef ASSETS_IMAGES_SECTION
#if defined(__GNUC__) || defined(__clang__)
#define ASSETS_IMAGES_SECTION __attribute__((section(".assets.images")))
#elif defined(_MSC_VER)
#define ASSETS_SIZES_SECTION __declspec(allocate(".assets.images"))
#pragma section(".assets", read)
#else
#define ASSETS_IMAGES_SECTION
#endif
#endif

#ifndef ASSETS_SIZES_SECTION
#if defined(__GNUC__) || defined(__clang__)
#define ASSETS_SIZES_SECTION __attribute__((section(".assets.sizes")))
#elif defined(_MSC_VER)
#define ASSETS_SIZES_SECTION __declspec(allocate(".assets.sizes"))
#pragma section(".assets", read)
#else
#define ASSETS_SIZES_SECTION
#endif
#endif


#ifndef ASSETS_IMAGES_TABLE_SECTION
#if defined(__GNUC__) || defined(__clang__)
#define ASSETS_IMAGES_TABLE_SECTION __attribute__((section(".assets.images_table")))
//#elif defined(_MSC_VER)
//#define ASSETS_IMAGES_TABLE_SECTION __declspec(allocate(".assets.images_table"))
//#pragma section(".assets.images_table", read)
#else
#define ASSETS_IMAGES_TABLE_SECTION
#endif
#endif

#ifndef ASSETS_DIMS_TABLE_SECTION
#if defined(__GNUC__) || defined(__clang__)
#define ASSETS_DIMS_TABLE_SECTION __attribute__((section(".assets.dims_table")))
//#elif defined(_MSC_VER)
//#define ASSETS_DIMS_TABLE_SECTION __declspec(allocate(".assets.dims_table"))
//#pragma section(".assets.dims_table", read)
#else
#define ASSETS_DIMS_TABLE_SECTION
#endif
#endif

#ifndef ASSETS_SPRITE_SETTINGS_SECTION
#if defined(__GNUC__) || defined(__clang__)
#define ASSETS_SPRITE_SETTINGS_SECTION __attribute__((section(".assets.sprite_settings")))
//#elif defined(_MSC_VER)
//#define ASSETS_SPRITE_SETTINGS_SECTION __declspec(allocate(".assets.sprite_settings"))
//#pragma section(".assets.sprite_settings", read)
#else
#define ASSETS_SPRITE_SETTINGS_SECTION
#endif
#endif

#ifndef ASSETS_INDICES_SECTION
#if defined(__GNUC__) || defined(__clang__)
#define ASSETS_INDICES_SECTION __attribute__((section(".assets.indices")))
//#elif defined(_MSC_VER)
//#define ASSETS_INDICES_SECTION __declspec(allocate(".assets.indices"))
//#pragma section(".assets.indices", read)
#else
#define ASSETS_INDICES_SECTION
#endif
#endif

#ifndef ASSETS_DATA_EVOL_SECTION
#if defined(__GNUC__) || defined(__clang__)
#define ASSETS_DATA_EVOL_SECTION __attribute__((section(".assets.data_evol")))
//#elif defined(_MSC_VER)
//#define ASSETS_DATA_EVOL_SECTION __declspec(allocate(".assets.data_evol"))
//#pragma section(".assets.data_evol", read)
#else
#define ASSETS_DATA_EVOL_SECTION
#endif
#endif

#ifndef CONFIG_STRING_SECTION
#if defined(__GNUC__) || defined(__clang__)
#define CONFIG_STRING_SECTION __attribute__((section(".config.str")))
//#elif defined(_MSC_VER)
//#define CONFIG_STRING_SECTION __declspec(allocate(".config.str"))
//#pragma section(".config.str", read)
#else
#define CONFIG_STRING_SECTION
#endif
#endif

#ifndef CONFIG_STRING_REF_SECTION
#if defined(__GNUC__) || defined(__clang__)
#define CONFIG_STRING_REF_SECTION __attribute__((section(".config.str_ref")))
//#elif defined(_MSC_VER)
//#define CONFIG_STRING_REF_SECTION __declspec(allocate(".config.str_ref"))
//#pragma section(".config.str_ref", read)
#else
#define CONFIG_STRING_REF_SECTION
#endif
#endif

#ifndef CONFIG_STRINGS_TABLE_SECTION
#if defined(__GNUC__) || defined(__clang__)
#define CONFIG_STRINGS_TABLE_SECTION __attribute__((section(".config.str_table")))
//#elif defined(_MSC_VER)
//#define CONFIG_STRINGS_TABLE_SECTION __declspec(allocate(".config.str_table"))
//#pragma section(".config.str_table", read)
#else
#define CONFIG_STRINGS_TABLE_SECTION
#endif
#endif

#ifndef CONFIG_ENTRIES_TABLE_SECTION
#if defined(__GNUC__) || defined(__clang__)
#define CONFIG_ENTRIES_TABLE_SECTION __attribute__((section(".config.anim_entries_table")))
//#elif defined(_MSC_VER)
//#define CONFIG_ENTRIES_TABLE_SECTION __declspec(allocate(".config.anim_entries_table"))
//#pragma section(".config.anim_entries_table", read)
#else
#define CONFIG_ENTRIES_TABLE_SECTION
#endif
#endif

#ifndef CONFIG_CUSTOM_ENTRIES_TABLE_SECTION
#if defined(__GNUC__) || defined(__clang__)
#define CONFIG_CUSTOM_ENTRIES_TABLE_SECTION __attribute__((section(".config.custom_anim_entries_table")))
//#elif defined(_MSC_VER)
//#define CONFIG_CUSTOM_ENTRIES_TABLE_SECTION __declspec(allocate(".config.custom_anim_entries_table"))
//#pragma section(".config.custom_anim_entries_table", read)
#else
#define CONFIG_CUSTOM_ENTRIES_TABLE_SECTION
#endif
#endif

#endif  // BONGOCAT_EMBEDDED_ASSETS_IMAGE_H
