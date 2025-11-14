add_library(assets_custom_sprite_sheet_feature INTERFACE)
target_compile_definitions(assets_custom_sprite_sheet_feature INTERFACE FEATURE_CUSTOM_SPRITE_SHEETS)
target_link_libraries(assets_custom_sprite_sheet_feature INTERFACE assets_custom_loader)

# base options for all execs
add_library(bongocat_options INTERFACE)
if (FEATURE_DISABLE_LOGGER)
    target_compile_definitions(bongocat_options INTERFACE BONGOCAT_DISABLE_MEMORY_STATISTICS BONGOCAT_DISABLE_LOGGER)
endif()
if (FEATURE_PRELOAD_ASSETS)
    target_compile_definitions(bongocat_options INTERFACE FEATURE_PRELOAD_ASSETS)
endif()
if (FEATURE_LAZY_LOAD_ASSETS)
    target_compile_definitions(bongocat_options INTERFACE FEATURE_LAZY_LOAD_ASSETS)
endif()
if (FEATURE_CUSTOM_SPRITE_SHEETS)
    target_compile_definitions(bongocat_options INTERFACE FEATURE_CUSTOM_SPRITE_SHEETS)
    target_link_libraries(bongocat_options INTERFACE assets_custom_sprite_sheet_feature assets_custom_loader)
endif()
target_link_libraries(bongocat_options INTERFACE project_warnings project_options project_sanitizers)
target_compile_options(bongocat_options INTERFACE
    $<$<COMPILE_LANGUAGE:C>:-fstack-protector-strong>
    $<$<COMPILE_LANGUAGE:CXX>:-fstack-protector-strong>
)
# supress warning: embed is a Clang extension [-Wc23-extensions]
target_compile_options(bongocat_options INTERFACE
    $<$<AND:$<COMPILE_LANGUAGE:C>,$<C_COMPILER_ID:Clang>>:-std=gnu23>
    $<$<AND:$<COMPILE_LANGUAGE:CXX>,$<CXX_COMPILER_ID:Clang>>:-std=gnu++26>
    $<$<AND:$<COMPILE_LANGUAGE:C>,$<C_COMPILER_ID:Clang>>:-Wno-c23-extensions>
    $<$<AND:$<COMPILE_LANGUAGE:CXX>,$<CXX_COMPILER_ID:Clang>>:-Wno-c23-extensions>
)
# no exceptions
target_compile_options(bongocat_options INTERFACE
    $<$<COMPILE_LANGUAGE:CXX>:
        -fno-exceptions -fno-unwind-tables -fno-rtti
        -nostdlib++
    >
)
# optimization
target_compile_options(bongocat_options INTERFACE
    $<$<CONFIG:Release>:
        -march=native
        -fomit-frame-pointer
        -funroll-loops
        -finline-functions
    >
    $<$<CONFIG:MinSizeRel>:
        -fno-inline-functions
        -fomit-frame-pointer
        -fno-asynchronous-unwind-tables
        -fno-unroll-loops
        -fmerge-all-constants
        -fno-math-errno
        -fno-stack-protector
    >
)
target_compile_definitions(bongocat_options INTERFACE
    $<$<CONFIG:Debug>:BONGOCAT_LOG_LEVEL=5>             # Verbose
    $<$<CONFIG:RelWithDebInfo>:BONGOCAT_LOG_LEVEL=4>    # Debug
    $<$<CONFIG:Release>:BONGOCAT_LOG_LEVEL=3>           # Info
    #$<$<CONFIG:MinSizeRel>:BONGOCAT_LOG_LEVEL=0>        # NONE
    $<$<CONFIG:MinSizeRel>:BONGOCAT_DISABLE_MEMORY_STATISTICS>
    $<$<CONFIG:MinSizeRel>:BONGOCAT_DISABLE_LOGGER>
)
target_link_options(bongocat_options INTERFACE $<$<CONFIG:MinSizeRel>:-Wl,--gc-sections -s>)


add_library(bongocat_libs INTERFACE)
# wayland-client dependency
find_package(PkgConfig REQUIRED)
pkg_check_modules(WAYLAND_CLIENT REQUIRED wayland-client)
add_library(wayland_client INTERFACE)
target_include_directories(wayland_client INTERFACE ${WAYLAND_CLIENT_INCLUDE_DIRS})
target_compile_options(wayland_client INTERFACE ${WAYLAND_CLIENT_CFLAGS_OTHER})
target_link_libraries(wayland_client INTERFACE ${WAYLAND_CLIENT_LIBRARIES})
target_link_libraries(bongocat_libs INTERFACE protocols wayland_client)
# udev dependency
pkg_check_modules(UDEV REQUIRED libudev)
target_include_directories(bongocat_libs INTERFACE ${UDEV_INCLUDE_DIRS})
target_link_libraries(bongocat_libs INTERFACE ${UDEV_LIBRARIES})
# Thread dependency
find_package(Threads REQUIRED)
target_link_libraries(bongocat_libs INTERFACE m rt Threads::Threads)
target_link_options(bongocat_libs INTERFACE -Wl,--gc-sections)

# base for assembling exec(s)
set(SOURCES
        utils/error.cpp
        utils/memory.cpp
        utils/random.cpp
        utils/system_memory.cpp
        utils/time.cpp
        config/config.cpp
        config/config_watcher.cpp
        core/main.cpp
        graphics/animation.cpp
        graphics/animation_init.cpp
        graphics/bar.cpp
        graphics/drawing_images.cpp
        platform/input.cpp
        platform/update.cpp
        platform/wayland.cpp
        platform/wayland_callbacks.cpp
        platform/wayland_hyprland.cpp
        platform/wayland_sway.cpp
)
add_library(bongocat_base INTERFACE)
target_sources(bongocat_base INTERFACE ${SOURCES})
target_include_directories(bongocat_base INTERFACE ${INCLUDE_DIR})
target_link_libraries(bongocat_base INTERFACE bongocat_options bongocat_libs)
target_compile_options(bongocat_base INTERFACE -ffunction-sections -fdata-sections)

# @NOTE(assets): 2. add embedded_assets sub directory
add_subdirectory(embedded_assets/bongocat)
add_subdirectory(embedded_assets/dm)
add_subdirectory(embedded_assets/dm20)
add_subdirectory(embedded_assets/dmx)
add_subdirectory(embedded_assets/pen)
add_subdirectory(embedded_assets/pen20)
add_subdirectory(embedded_assets/dmc)
add_subdirectory(embedded_assets/dmall)
add_subdirectory(embedded_assets/min_dm)
add_subdirectory(embedded_assets/ms_agent)
add_subdirectory(embedded_assets/pkmn)
add_subdirectory(embedded_assets/misc)
add_subdirectory(image_loader)