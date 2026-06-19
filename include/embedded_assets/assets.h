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


#ifndef ASSETS_TABLE_SECTION
#if defined(__GNUC__) || defined(__clang__)
#define ASSETS_TABLE_SECTION __attribute__((section(".assets.table")))
//#elif defined(_MSC_VER)
//#define ASSETS_TABLE_SECTION __declspec(allocate(".assets.table"))
//#pragma section(".assets.table", read)
#else
#define ASSETS_TABLE_SECTION
#endif
#endif

#ifndef ASSETS_TABLE2_SECTION
#if defined(__GNUC__) || defined(__clang__)
#define ASSETS_TABLE2_SECTION __attribute__((section(".assets.table2")))
//#elif defined(_MSC_VER)
//#define ASSETS_TABLE2_SECTION __declspec(allocate(".assets.table2"))
//#pragma section(".assets.table", read)
#else
#define ASSETS_TABLE2_SECTION
#endif
#endif

#ifndef ASSETS_DATA_SECTION
#if defined(__GNUC__) || defined(__clang__)
#define ASSETS_DATA_SECTION __attribute__((section(".assets.data")))
//#elif defined(_MSC_VER)
//#define ASSETS_DATA_SECTION __declspec(allocate(".assets.data"))
//#pragma section(".assets.data", read)
#else
#define ASSETS_DATA_SECTION
#endif
#endif

#ifndef ASSETS_DATA2_SECTION
#if defined(__GNUC__) || defined(__clang__)
#define ASSETS_DATA2_SECTION __attribute__((section(".assets.data2")))
//#elif defined(_MSC_VER)
//#define ASSETS_DATA2_SECTION __declspec(allocate(".assets.data2"))
//#pragma section(".assets.data2", read)
#else
#define ASSETS_DATA2_SECTION
#endif
#endif

#ifndef ASSETS_DATA3_SECTION
#if defined(__GNUC__) || defined(__clang__)
#define ASSETS_DATA3_SECTION __attribute__((section(".assets.data3")))
//#elif defined(_MSC_VER)
//#define ASSETS_DATA3_SECTION __declspec(allocate(".assets.data3"))
//#pragma section(".assets.data3", read)
#else
#define ASSETS_DATA3_SECTION
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

#ifndef CONFIG_STRING2_SECTION
#if defined(__GNUC__) || defined(__clang__)
#define CONFIG_STRING2_SECTION __attribute__((section(".config.str2")))
//#elif defined(_MSC_VER)
//#define CONFIG_STRING2_SECTION __declspec(allocate(".config.str2"))
//#pragma section(".config.str2", read)
#else
#define CONFIG_STRING2_SECTION
#endif
#endif

#ifndef CONFIG_TABLE_SECTION
#if defined(__GNUC__) || defined(__clang__)
#define CONFIG_TABLE_SECTION __attribute__((section(".config.table")))
//#elif defined(_MSC_VER)
//#define CONFIG_TABLE_SECTION __declspec(allocate(".config.table"))
//#pragma section(".config.table", read)
#else
#define CONFIG_TABLE_SECTION
#endif
#endif

#ifndef CONFIG_DATA_SECTION
#if defined(__GNUC__) || defined(__clang__)
#define CONFIG_DATA_SECTION __attribute__((section(".config.data")))
//#elif defined(_MSC_VER)
//#define CONFIG_DATA_SECTION __declspec(allocate(".config.data"))
//#pragma section(".config.data", read)
#else
#define CONFIG_DATA_SECTION
#endif
#endif

#endif  // BONGOCAT_EMBEDDED_ASSETS_IMAGE_H
