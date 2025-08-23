cmake_minimum_required(VERSION 3.24)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_C_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD_REQUIRED ON)
include(FetchContent)
if(CMAKE_VERSION VERSION_GREATER_EQUAL "3.24.0")
    cmake_policy(SET CMP0135 NEW)
endif()

get_property(BUILDING_MULTI_CONFIG GLOBAL PROPERTY GENERATOR_IS_MULTI_CONFIG)
if(BUILDING_MULTI_CONFIG)
    if(NOT CMAKE_BUILD_TYPE)
        # Make sure that all supported configuration types have their associated conan packages available. You can reduce this list to only the
        # configuration types you use, but only if one is not forced-set on the command line for VS
        message(TRACE "Setting up multi-config build types")
        set(CMAKE_CONFIGURATION_TYPES
                Debug Release RelWithDebInfo MinSizeRel
                CACHE STRING "Enabled build types" FORCE)
    else()
        message(TRACE "User chose a specific build type, so we are using that")
        set(CMAKE_CONFIGURATION_TYPES
                ${CMAKE_BUILD_TYPE}
                CACHE STRING "Enabled build types" FORCE)
    endif()
endif()
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the build type." FORCE)
endif()



project(bongocat LANGUAGES C CXX VERSION 2.1.0)

# Feature Flags
include(CMakeDependentOption)
option(FEATURE_BONGOCAT_EMBEDDED_ASSETS "Include bongocat assets (default)" ON)
option(FEATURE_DIGIMON_EMBEDDED_ASSETS "Include digimon embedded assets" ON)
# TODO: add more digimon assets
#cmake_dependent_option(FEATURE_DM_EMBEDDED_ASSETS "Include dm embedded assets" OFF FEATURE_DIGIMON_EMBEDDED_ASSETS OFF)
#cmake_dependent_option(FEATURE_DM20_EMBEDDED_ASSETS "Include dm20 embedded assets" OFF FEATURE_DIGIMON_EMBEDDED_ASSETS OFF)
#cmake_dependent_option(FEATURE_DMC_EMBEDDED_ASSETS "Include dmc embedded assets" OFF FEATURE_DIGIMON_EMBEDDED_ASSETS OFF)
#cmake_dependent_option(FEATURE_DMX_EMBEDDED_ASSETS "Include dmx embedded assets" OFF FEATURE_DIGIMON_EMBEDDED_ASSETS OFF)
#cmake_dependent_option(FEATURE_PEN20_EMBEDDED_ASSETS "Include pen20 embedded assets" OFF FEATURE_DIGIMON_EMBEDDED_ASSETS OFF)
option(FEATURE_CLIPPY_EMBEDDED_ASSETS "Include clippy embedded assets" ON)
option(FEATURE_DISABLE_LOGGER "Disable Logger (makes enable_debug option obsolete)" OFF)
option(FEATURE_PRELOAD_ASSETS "Preload available assets (More RAM usage, sprite switching on hot-reload)" OFF)

# project_options
# More Warnings
set(C_WARNING_FLAGS
        -Wall
        -Wextra
        -Wpedantic
        -Wformat=2
        -Wstrict-prototypes
        -Wmissing-prototypes
        -Wold-style-definition
        -Wredundant-decls
        -Wnested-externs
        -Wmissing-include-dirs
        -Wdouble-promotion
        -Wshadow
)
set(CXX_WARNING_FLAGS
        -Wall
        -Wextra
        -Wpedantic
        -Wformat=2
        -Wredundant-decls
        -Wmissing-include-dirs
        -Wdouble-promotion
        -Wshadow
)
add_library(project_warnings INTERFACE)
target_compile_options(project_warnings INTERFACE $<$<COMPILE_LANGUAGE:C>:${C_WARNING_FLAGS}> $<$<COMPILE_LANGUAGE:CXX>:${CXX_WARNING_FLAGS}>)
add_library(project_options INTERFACE)
target_compile_options(project_options INTERFACE $<$<C_COMPILER_ID:MSVC>:/external:anglebrackets /external:W0>)
target_compile_options(project_options INTERFACE $<$<CXX_COMPILER_ID:MSVC>:/external:anglebrackets /external:W0>)



set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(PROTOCOLS_DIR ${CMAKE_SOURCE_DIR}/protocols)
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
if(DEFINED ENV{WAYLAND_PROTOCOLS_DIR})
    set(WAYLAND_PROTOCOLS_DIR "$ENV{WAYLAND_PROTOCOLS_DIR}" CACHE PATH "Path to wayland-protocols")
else()
    set(WAYLAND_PROTOCOLS_DIR "/usr/share/wayland-protocols" CACHE PATH "Path to wayland-protocols")
endif()




set(PROTOCOL_XML_WLR ${PROTOCOLS_DIR}/wlr-layer-shell-unstable-v1.xml)
set(PROTOCOL_XML_XDG ${WAYLAND_PROTOCOLS_DIR}/stable/xdg-shell/xdg-shell.xml)
set(PROTOCOL_XML_WLR_FOREIGN ${PROTOCOLS_DIR}/wlr-foreign-toplevel-management-unstable-v1.xml)
set(PROTOCOL_XML_XDG_OUTPUT ${PROTOCOLS_DIR}/xdg-output-unstable-v1.xml)
set(GENERATED_PROTOCOLS_SOURCES
    ${PROTOCOLS_DIR}/zwlr-layer-shell-v1-protocol.c
    ${PROTOCOLS_DIR}/xdg-shell-protocol.c
    ${PROTOCOLS_DIR}/wlr-foreign-toplevel-management-v1-protocol.c
    ${PROTOCOLS_DIR}/xdg-output-unstable-v1-protocol.c
)
set(GENERATED_PROTOCOLS_HEADERS
    ${PROTOCOLS_DIR}/zwlr-layer-shell-v1-client-protocol.h
    ${PROTOCOLS_DIR}/xdg-shell-client-protocol.h
    ${PROTOCOLS_DIR}/wlr-foreign-toplevel-management-v1-client-protocol.h
    ${PROTOCOLS_DIR}/xdg-output-unstable-v1-client-protocol.h
)
set(GENERATED_PROTOCOLS
    ${GENERATED_PROTOCOLS_SOURCES}
    ${GENERATED_PROTOCOLS_HEADERS}
)
find_program(WAYLAND_SCANNER_EXECUTABLE wayland-scanner REQUIRED)
add_custom_command(OUTPUT ${GENERATED_PROTOCOLS}
    COMMAND ${WAYLAND_SCANNER_EXECUTABLE} client-header ${PROTOCOL_XML_XDG} ${PROTOCOLS_DIR}/xdg-shell-client-protocol.h
    COMMAND ${WAYLAND_SCANNER_EXECUTABLE} private-code ${PROTOCOL_XML_XDG} ${PROTOCOLS_DIR}/xdg-shell-protocol.c
    COMMAND ${WAYLAND_SCANNER_EXECUTABLE} client-header ${PROTOCOL_XML_WLR} ${PROTOCOLS_DIR}/zwlr-layer-shell-v1-client-protocol.h
    COMMAND ${WAYLAND_SCANNER_EXECUTABLE} private-code ${PROTOCOL_XML_WLR} ${PROTOCOLS_DIR}/zwlr-layer-shell-v1-protocol.c
    COMMAND ${WAYLAND_SCANNER_EXECUTABLE} private-code ${PROTOCOL_XML_WLR_FOREIGN} ${PROTOCOLS_DIR}/wlr-foreign-toplevel-management-v1-protocol.c
    COMMAND ${WAYLAND_SCANNER_EXECUTABLE} client-header ${PROTOCOL_XML_WLR_FOREIGN} ${PROTOCOLS_DIR}/wlr-foreign-toplevel-management-v1-client-protocol.h
    COMMAND ${WAYLAND_SCANNER_EXECUTABLE} client-header ${PROTOCOL_XML_XDG_OUTPUT} ${PROTOCOLS_DIR}/xdg-output-unstable-v1-client-protocol.h
    COMMAND ${WAYLAND_SCANNER_EXECUTABLE} private-code ${PROTOCOL_XML_XDG_OUTPUT} ${PROTOCOLS_DIR}/xdg-output-unstable-v1-protocol.c
    DEPENDS ${PROTOCOL_XML_WLR} ${PROTOCOL_XML_XDG} ${PROTOCOL_XML_WLR_FOREIGN} ${PROTOCOL_XML_XDG_OUTPUT}
    COMMENT "Generating Wayland protocol files..."
)
add_custom_target(protocols DEPENDS ${GENERATED_PROTOCOLS})


add_executable(bongocat)
set(SOURCES
    ${SRC_DIR}/config/config.cpp
    ${SRC_DIR}/config/config_watcher.cpp
    ${SRC_DIR}/core/main.cpp
    ${SRC_DIR}/graphics/animation.cpp
    ${SRC_DIR}/graphics/animation_init.cpp
    ${SRC_DIR}/graphics/bar.cpp
    ${SRC_DIR}/graphics/embedded_assets.cpp
    ${SRC_DIR}/platform/input.cpp
    ${SRC_DIR}/platform/wayland.cpp
    ${SRC_DIR}/utils/error.cpp
    ${SRC_DIR}/utils/memory.cpp
    ${SRC_DIR}/utils/system_memory.cpp
    ${SRC_DIR}/utils/time.cpp
)
target_sources(bongocat PRIVATE ${SOURCES} ${GENERATED_PROTOCOLS_SOURCES})
add_dependencies(bongocat protocols)

if (FEATURE_BONGOCAT_EMBEDDED_ASSETS)
    add_library(assets_bongocat OBJECT ${SRC_DIR}/graphics/embedded_assets_bongocat.cpp)
    target_include_directories(assets_bongocat PRIVATE ${INCLUDE_DIR})
    target_compile_definitions(assets_bongocat PUBLIC FEATURE_BONGOCAT_EMBEDDED_ASSETS)
    target_link_libraries(bongocat PRIVATE $<TARGET_OBJECTS:assets_bongocat>)
    target_compile_definitions(bongocat PRIVATE FEATURE_BONGOCAT_EMBEDDED_ASSETS)
endif()
if (FEATURE_DIGIMON_EMBEDDED_ASSETS)
    add_library(assets_dm OBJECT ${SRC_DIR}/graphics/embedded_assets_digimon.cpp)
    target_include_directories(assets_dm PRIVATE ${INCLUDE_DIR})
    target_compile_definitions(assets_dm PUBLIC FEATURE_DIGIMON_EMBEDDED_ASSETS)
    target_link_libraries(bongocat PRIVATE $<TARGET_OBJECTS:assets_dm>)
    target_compile_definitions(bongocat PRIVATE FEATURE_DIGIMON_EMBEDDED_ASSETS)
endif()
if (FEATURE_CLIPPY_EMBEDDED_ASSETS)
    add_library(assets_clippy OBJECT ${SRC_DIR}/graphics/embedded_assets_clippy.cpp)
    target_include_directories(assets_clippy PRIVATE ${INCLUDE_DIR})
    target_compile_definitions(assets_clippy PUBLIC FEATURE_CLIPPY_EMBEDDED_ASSETS)
    target_link_libraries(bongocat PRIVATE $<TARGET_OBJECTS:assets_clippy>)
    target_compile_definitions(bongocat PRIVATE FEATURE_CLIPPY_EMBEDDED_ASSETS)
endif()
if (FEATURE_DISABLE_LOGGER)
    target_compile_definitions(bongocat PRIVATE BONGOCAT_DISABLE_MEMORY_STATISTICS BONGOCAT_DISABLE_LOGGER)
endif()
if (FEATURE_PRELOAD_ASSETS)
    target_compile_definitions(bongocat PRIVATE FEATURE_PRELOAD_ASSETS)
endif()

target_include_directories(bongocat PRIVATE ${INCLUDE_DIR})
target_include_directories(bongocat SYSTEM PRIVATE ${PROTOCOLS_DIR} ${CMAKE_SOURCE_DIR}/lib)

target_link_libraries(bongocat PRIVATE project_warnings project_options)
target_compile_options(bongocat PRIVATE
    $<$<COMPILE_LANGUAGE:C>:
        ${C_WARNING_FLAGS}
        -fstack-protector-strong
    >
    $<$<AND:$<COMPILE_LANGUAGE:C>,$<C_COMPILER_ID:GNU>>:-Wlogical-op -Wjump-misses-init>

    $<$<COMPILE_LANGUAGE:CXX>:
        ${CXX_WARNING_FLAGS}
        -fstack-protector-strong
    >
    $<$<AND:$<COMPILE_LANGUAGE:CXX>,$<CXX_COMPILER_ID:GNU>>:-Wlogical-op>
)
# supress warning: embed is a Clang extension [-Wc23-extensions]
target_compile_options(bongocat PRIVATE
    $<$<AND:$<COMPILE_LANGUAGE:C>,$<C_COMPILER_ID:Clang>>:-std=gnu23>
    $<$<AND:$<COMPILE_LANGUAGE:CXX>,$<CXX_COMPILER_ID:Clang>>:-std=gnu++26>
    $<$<AND:$<COMPILE_LANGUAGE:C>,$<C_COMPILER_ID:Clang>>:-Wno-c23-extensions>
    $<$<AND:$<COMPILE_LANGUAGE:CXX>,$<CXX_COMPILER_ID:Clang>>:-Wno-c23-extensions>
)

# no exceptions
target_compile_options(bongocat PRIVATE
        $<$<COMPILE_LANGUAGE:CXX>:
            -fno-exceptions -fno-rtti
            #-ffreestanding                 # free, malloc etc. are in use
            -nostdlib++
            -fno-use-cxa-atexit             # global destructs not needed ?, cleanup is done manually
            -fno-threadsafe-statics         # no local statics are in use (?)
        >
)

# optimization
target_compile_options(bongocat PRIVATE
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
            -fno-unwind-tables
            -ffunction-sections
            -fdata-sections
            -fno-unroll-loops
            -fmerge-all-constants
            -fno-math-errno
            -fno-stack-protector
        >
)
target_compile_definitions(bongocat PRIVATE
        $<$<CONFIG:Debug>:BONGOCAT_LOG_LEVEL=5>
        $<$<CONFIG:RelWithDebInfo>:BONGOCAT_LOG_LEVEL=4>
        $<$<CONFIG:MinSizeRel>:BONGOCAT_DISABLE_MEMORY_STATISTICS>
        $<$<CONFIG:MinSizeRel>:BONGOCAT_DISABLE_LOGGER>
)
target_link_options(bongocat PRIVATE $<$<CONFIG:MinSizeRel>:-Wl,--gc-sections -s>)
set_target_properties(bongocat PROPERTIES INTERPROCEDURAL_OPTIMIZATION TRUE)

# wayland-client dependency
find_package(PkgConfig REQUIRED)

pkg_check_modules(WAYLAND_CLIENT REQUIRED wayland-client)
add_library(wayland_client INTERFACE)
target_include_directories(wayland_client INTERFACE ${WAYLAND_CLIENT_INCLUDE_DIRS})
target_compile_options(wayland_client INTERFACE ${WAYLAND_CLIENT_CFLAGS_OTHER})
target_link_libraries(wayland_client INTERFACE ${WAYLAND_CLIENT_LIBRARIES})
target_link_libraries(bongocat PRIVATE wayland_client)

find_package(Threads REQUIRED)
target_link_libraries(bongocat PRIVATE m rt Threads::Threads)


include(GNUInstallDirs)
install(TARGETS bongocat DESTINATION ${CMAKE_INSTALL_BINDIR})
install(FILES bongocat.conf DESTINATION ${CMAKE_INSTALL_DATADIR}/bongocat RENAME bongocat.conf.example)
install(PROGRAMS scripts/find_input_devices.sh DESTINATION ${CMAKE_INSTALL_BINDIR} RENAME bongocat-find-devices)

set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES "${GENERATED_PROTOCOLS}")

# If MSVC is being used, and ASAN is enabled, we need to set the debugger environment so that it behaves well with MSVC's debugger, and we
# can run the target from visual studio
if(MSVC)
    get_all_installable_targets(all_targets)
    message("all_targets=${all_targets}")
    set_target_properties(${all_targets} PROPERTIES VS_DEBUGGER_ENVIRONMENT "PATH=$(VC_ExecutablePath_x64);%PATH%")
endif()
