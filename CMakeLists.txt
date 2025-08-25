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



project(bongocat LANGUAGES C CXX VERSION 2.1.1)

# Feature Flags
include(CMakeDependentOption)
option(FEATURE_BONGOCAT_EMBEDDED_ASSETS "Include bongocat assets (default)" ON)
option(FEATURE_ENABLE_DM_EMBEDDED_ASSETS "Enable include dm embedded assets" ON)
# TODO: add more dm version assets
cmake_dependent_option(FEATURE_DM_EMBEDDED_ASSETS "Include dm embedded assets" OFF FEATURE_ENABLE_DM_EMBEDDED_ASSETS OFF)
#cmake_dependent_option(FEATURE_DM20_EMBEDDED_ASSETS "Include dm20 embedded assets" OFF FEATURE_ENABLE_DM_EMBEDDED_ASSETS OFF)
#cmake_dependent_option(FEATURE_DMC_EMBEDDED_ASSETS "Include dmc embedded assets" OFF FEATURE_ENABLE_DM_EMBEDDED_ASSETS OFF)
#cmake_dependent_option(FEATURE_DMX_EMBEDDED_ASSETS "Include dmx embedded assets" OFF FEATURE_ENABLE_DM_EMBEDDED_ASSETS OFF)
#cmake_dependent_option(FEATURE_PEN20_EMBEDDED_ASSETS "Include pen20 embedded assets" OFF FEATURE_ENABLE_DM_EMBEDDED_ASSETS OFF)
option(FEATURE_MS_AGENT_EMBEDDED_ASSETS "Include MS agents (clippy) embedded assets" ON)
option(FEATURE_DISABLE_LOGGER "Disable Logger (makes enable_debug option obsolete)" OFF)
option(FEATURE_PRELOAD_ASSETS "Preload available assets (More RAM usage, sprite switching on hot-reload)" OFF)

option(ENABLE_ASAN "Enable Address Sanitizer" OFF)
option(ENABLE_UBSAN "Enable Undefined Behavior Sanitizer" OFF)
option(ENABLE_TSAN "Enable Thread Sanitizer" OFF)

# project_options
# More Warnings
set(CLANG_WARNINGS
        -Wall
        -Wextra # reasonable and standard
        -Wextra-semi # Warn about semicolon after in-class function definition.
        -Wshadow # warn the user if a variable declaration shadows one from a parent context
        -Wnon-virtual-dtor # warn the user if a class with virtual functions has a non-virtual destructor. This helps
        # catch hard to track down memory errors
        -Wold-style-cast # warn for c-style casts
        -Wcast-align # warn for potential performance problem casts
        -Wunused # warn on anything being unused
        -Woverloaded-virtual # warn if you overload (not override) a virtual function
        -Wpedantic # warn if non-standard C++ is used
        -Wconversion # warn on type conversions that may lose data
        -Wsign-conversion # warn on sign conversions
        -Wnull-dereference # warn if a null dereference is detected
        -Wdouble-promotion # warn if float is implicit promoted to double
        -Wformat=2 # warn on security issues around functions that format output (ie printf)
        -Wimplicit-fallthrough # warn on statements that fallthrough without an explicit annotation
)
set(GCC_WARNINGS
        ${CLANG_WARNINGS}
        -Wmisleading-indentation # warn if indentation implies blocks where blocks do not exist
        -Wduplicated-cond # warn if if / else chain has duplicated conditions
        -Wduplicated-branches # warn if if / else branches have duplicated code
        -Wlogical-op # warn about logical operations being used where bitwise were probably wanted
        -Wuseless-cast # warn if you perform a cast to the same type
)
set(C_WARNING_FLAGS
        -Wall -Wextra -Wpedantic -Wformat=2 -Wstrict-prototypes
        -Wmissing-prototypes -Wold-style-definition -Wredundant-decls
        -Wnested-externs -Wmissing-include-dirs -Wlogical-op
        -Wjump-misses-init -Wdouble-promotion -Wshadow
)
set(GCC_C_WARNING_FLAGS
        -Wall -Wextra -Wpedantic -Wshadow -Wcast-align -Wunused 
        -Wconversion -Wsign-conversion -Wformat=2 -Wimplicit-fallthrough 
        -Wnull-dereference -Wdouble-promotion -Wmissing-prototypes 
        -Wstrict-prototypes -Wpointer-arith -Wundef 
        -Wmissing-field-initializers -Wvla)
set(CLANG_C_WARNING_FLAGS
        -Wall -Wextra -Wpedantic -Wshadow -Wcast-align -Wunused 
        -Wconversion -Wsign-conversion -Wformat=2 -Wimplicit-fallthrough 
        -Wnull-dereference -Wdouble-promotion -Wmissing-prototypes 
        -Wstrict-prototypes -Wpointer-arith -Wundef 
        -Wmissing-field-initializers -Wvla 
        -Wmisleading-indentation -Wduplicated-cond -Wduplicated-branches -Wlogical-op)
add_library(project_warnings INTERFACE)
target_compile_options(project_warnings INTERFACE $<$<COMPILE_LANGUAGE:C>:${C_WARNING_FLAGS}>)
target_compile_options(project_warnings INTERFACE
        $<$<AND:$<COMPILE_LANGUAGE:C>,$<CXX_COMPILER_ID:Clang>>:${CLANG_C_WARNINGS}>
        $<$<AND:$<COMPILE_LANGUAGE:C>,$<CXX_COMPILER_ID:GNU>>:${GCC_C_WARNINGS}>
        $<$<AND:$<COMPILE_LANGUAGE:CXX>,$<CXX_COMPILER_ID:Clang>>:${CLANG_WARNINGS}>
        $<$<AND:$<COMPILE_LANGUAGE:CXX>,$<CXX_COMPILER_ID:GNU>>:${GCC_WARNINGS}>
)
add_library(project_options INTERFACE)
#target_compile_options(project_options INTERFACE $<$<C_COMPILER_ID:MSVC>:/external:anglebrackets /external:W0>)
#target_compile_options(project_options INTERFACE $<$<CXX_COMPILER_ID:MSVC>:/external:anglebrackets /external:W0>)
set_target_properties(project_options PROPERTIES INTERPROCEDURAL_OPTIMIZATION_RELEASE ON)
set_target_properties(project_options PROPERTIES INTERPROCEDURAL_OPTIMIZATION_RELWITHDEBINFO ON)
add_library(project_sanitizers INTERFACE)
if(CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
    # Check for incompatible options
    if(ENABLE_ASAN AND ENABLE_TSAN)
        message(FATAL_ERROR "ASan and TSan are incompatible. Please enable only one of them.")
    endif()
    if(ENABLE_ASAN)
        target_compile_options(project_sanitizers INTERFACE -fsanitize=address)
        target_link_options(project_sanitizers INTERFACE -fsanitize=address)
    endif()
    if(ENABLE_UBSAN)
        target_compile_options(project_sanitizers INTERFACE -fsanitize=undefined)
        target_link_options(project_sanitizers INTERFACE -fsanitize=undefined)
    endif()
    if(ENABLE_TSAN)
        target_compile_options(project_sanitizers INTERFACE -fsanitize=thread)
        target_link_options(project_sanitizers INTERFACE -fsanitize=thread)
    endif()
endif()


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
set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES "${GENERATED_PROTOCOLS}")


add_executable(bongocat)
set(SOURCES
    ${SRC_DIR}/config/config.cpp
    ${SRC_DIR}/config/config_watcher.cpp
    ${SRC_DIR}/core/main.cpp
    ${SRC_DIR}/graphics/animation.cpp
    ${SRC_DIR}/graphics/animation_init.cpp
    ${SRC_DIR}/graphics/bar.cpp
    ${SRC_DIR}/graphics/drawing_images.cpp
    ${SRC_DIR}/graphics/load_images.cpp
    ${SRC_DIR}/graphics/embedded_assets.cpp
    ${SRC_DIR}/graphics/stb_image.cpp
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
    set(BONGOCAT_SOURCES ${SRC_DIR}/graphics/embedded_assets_bongocat.cpp ${SRC_DIR}/graphics/embedded_assets/bongocat_images.c)
    add_library(assets_bongocat STATIC ${BONGOCAT_SOURCES})
    target_compile_options(assets_bongocat PUBLIC -ffunction-sections -fdata-sections)
    target_include_directories(assets_bongocat PRIVATE ${INCLUDE_DIR})
    target_compile_definitions(assets_bongocat PUBLIC FEATURE_BONGOCAT_EMBEDDED_ASSETS)
    target_link_libraries(bongocat PRIVATE assets_bongocat)
endif()
if (FEATURE_ENABLE_DM_EMBEDDED_ASSETS)
    set(DM_SOURCES ${SRC_DIR}/graphics/embedded_assets_dm.cpp)
    set(DM_DEFS FEATURE_ENABLE_DM_EMBEDDED_ASSETS)
    if (FEATURE_DM_EMBEDDED_ASSETS)
        set(DM_SOURCES ${DM_SOURCES} ${SRC_DIR}/graphics/embedded_assets/dm_images.c)
        set(DM_DEFS ${DM_DEFS} FEATURE_DM_EMBEDDED_ASSETS)
    else()
        set(DM_SOURCES ${SRC_DIR}/graphics/embedded_assets/min_dm_images.c)
    endif()
    add_library(assets_dm STATIC ${DM_SOURCES})
    target_compile_options(assets_dm PUBLIC -ffunction-sections -fdata-sections)
    target_include_directories(assets_dm PRIVATE ${INCLUDE_DIR})
    target_compile_definitions(assets_dm PUBLIC ${DM_DEFS})
    target_link_libraries(bongocat PRIVATE assets_dm)
endif()
if (FEATURE_MS_AGENT_EMBEDDED_ASSETS)
    set(MS_AGENT_SOURCES ${SRC_DIR}/graphics/embedded_assets_clippy.cpp ${SRC_DIR}/graphics/embedded_assets/clippy_images.c)
    add_library(assets_clippy STATIC ${MS_AGENT_SOURCES})
    target_compile_options(assets_clippy PUBLIC -ffunction-sections -fdata-sections)
    target_include_directories(assets_clippy PRIVATE ${INCLUDE_DIR})
    target_compile_definitions(assets_clippy PUBLIC FEATURE_MS_AGENT_EMBEDDED_ASSETS)
    target_link_libraries(bongocat PRIVATE assets_clippy)
endif()
target_link_options(bongocat PRIVATE -Wl,--gc-sections)

if (FEATURE_DISABLE_LOGGER)
    target_compile_definitions(bongocat PRIVATE BONGOCAT_DISABLE_MEMORY_STATISTICS BONGOCAT_DISABLE_LOGGER)
endif()
if (FEATURE_PRELOAD_ASSETS)
    target_compile_definitions(bongocat PRIVATE FEATURE_PRELOAD_ASSETS)
endif()

target_include_directories(bongocat PRIVATE ${INCLUDE_DIR})
target_include_directories(bongocat SYSTEM PRIVATE ${PROTOCOLS_DIR} ${CMAKE_SOURCE_DIR}/lib)

target_link_libraries(bongocat PRIVATE project_warnings project_options project_sanitizers)
target_compile_options(bongocat PRIVATE
    $<$<COMPILE_LANGUAGE:C>:-fstack-protector-strong>
    $<$<COMPILE_LANGUAGE:CXX>:-fstack-protector-strong>
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
            -fno-exceptions -fno-unwind-tables -fno-rtti
            -nostdlib++
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

# wayland-client dependency
find_package(PkgConfig REQUIRED)
pkg_check_modules(WAYLAND_CLIENT REQUIRED wayland-client)
add_library(wayland_client INTERFACE)
target_include_directories(wayland_client INTERFACE ${WAYLAND_CLIENT_INCLUDE_DIRS})
target_compile_options(wayland_client INTERFACE ${WAYLAND_CLIENT_CFLAGS_OTHER})
target_link_libraries(wayland_client INTERFACE ${WAYLAND_CLIENT_LIBRARIES})
target_link_libraries(bongocat PRIVATE wayland_client)

# Thread dependency
find_package(Threads REQUIRED)
target_link_libraries(bongocat PRIVATE m rt Threads::Threads)

# Install
include(GNUInstallDirs)
install(TARGETS bongocat DESTINATION ${CMAKE_INSTALL_BINDIR})
install(FILES bongocat.conf DESTINATION ${CMAKE_INSTALL_DATADIR}/bongocat RENAME bongocat.conf.example)
install(PROGRAMS scripts/find_input_devices.sh DESTINATION ${CMAKE_INSTALL_BINDIR} RENAME bongocat-find-devices)


# If MSVC is being used, and ASAN is enabled, we need to set the debugger environment so that it behaves well with MSVC's debugger, and we
# can run the target from visual studio
if(MSVC)
    get_all_installable_targets(all_targets)
    message("all_targets=${all_targets}")
    set_target_properties(${all_targets} PROPERTIES VS_DEBUGGER_ENVIRONMENT "PATH=$(VC_ExecutablePath_x64);%PATH%")
endif()
