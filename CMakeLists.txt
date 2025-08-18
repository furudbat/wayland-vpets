cmake_minimum_required(VERSION 3.24)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_C_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD_REQUIRED ON)
include(FetchContent)
if(CMAKE_VERSION VERSION_GREATER_EQUAL "3.24.0")
    cmake_policy(SET CMP0135 NEW)
endif()

# Add project_options from https://github.com/aminya/project_options
# Change the version in the following URL to update the package (watch the releases of the repository for future updates)
set(PROJECT_OPTIONS_VERSION "v0.41.0")
FetchContent_Declare(
        _project_options
        URL https://github.com/aminya/project_options/archive/refs/tags/${PROJECT_OPTIONS_VERSION}.zip)
FetchContent_MakeAvailable(_project_options)
include(${_project_options_SOURCE_DIR}/Index.cmake)
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

include(CMakeDependentOption)
option(OPT_ENABLE_IPO "Enable IPO/LTO" ON)
option(OPT_WARNINGS_AS_ERRORS "Treat Warnings As Errors" ${CMAKE_COMPILE_WARNING_AS_ERROR})
if(ENABLE_TESTING AND ("${CMAKE_BUILD_TYPE}" MATCHES "Debug" OR "${CMAKE_BUILD_TYPE}" MATCHES "RelWithDebInfo"))
    set(DEFAULT_OPT_ENABLE_SANITIZER_ADDRESS ON)
else()
    set(DEFAULT_OPT_ENABLE_SANITIZER_ADDRESS OFF)
endif()
option(OPT_ENABLE_SANITIZER_ADDRESS "Enable address sanitizer" ${DEFAULT_OPT_ENABLE_SANITIZER_ADDRESS})
if(ENABLE_TESTING AND ("${CMAKE_BUILD_TYPE}" MATCHES "Debug" OR "${CMAKE_BUILD_TYPE}" MATCHES "RelWithDebInfo"))
    if(NOT MSVC)
        set(DEFAULT_OPT_ENABLE_SANITIZER_UNDEFINED ON)
    else()
        set(DEFAULT_OPT_ENABLE_SANITIZER_UNDEFINED OFF)
    endif()
else()
    set(DEFAULT_OPT_ENABLE_SANITIZER_UNDEFINED OFF)
endif()
option(OPT_ENABLE_SANITIZER_UNDEFINED "Enable undefined sanitizer" ${DEFAULT_OPT_ENABLE_SANITIZER_UNDEFINED})
option(OPT_ENABLE_SANITIZER_THREAD "Enable thread sanitizer" OFF)
option(OPT_ENABLE_SANITIZER_MEMORY "Enable memory sanitizer" OFF)
option(OPT_ENABLE_UNITY_BUILD "Enable unity builds" OFF)
cmake_dependent_option(OPT_ENABLE_CLANG_TIDY "Enable clang-tidy" ON ENABLE_STATIC_ANALYZER OFF)
cmake_dependent_option(OPT_ENABLE_CPPCHECK "Enable cpp-check analysis" ON ENABLE_STATIC_ANALYZER OFF)
option(OPT_ENABLE_PCH "Enable precompiled headers" OFF)
option(OPT_ENABLE_CACHE "Enable ccache" ON)
if(${PLATFORM} MATCHES "Desktop")
    set(DEFAULT_OPT_ENABLE_HARDENING ON)
else()
    set(DEFAULT_OPT_ENABLE_HARDENING OFF)
endif()
option(OPT_ENABLE_HARDENING "Enable hardening" ${DEFAULT_OPT_ENABLE_HARDENING})


project(bongocat LANGUAGES C CXX VERSION 2.0.0)

# TODO: add assets options and fully implement switching assets + optimization
#option(INCLUDE_DM_EMBEDDED_ASSETS "Include dm embedded assets (fully)" OFF)
#option(INCLUDE_DM20_EMBEDDED_ASSETS "Include dm20 embedded assets" OFF)
#option(INCLUDE_DMC_EMBEDDED_ASSETS "Include dmc embedded assets" OFF)
#option(INCLUDE_DMX_EMBEDDED_ASSETS "Include dmx embedded assets" OFF)
#option(INCLUDE_PEN20_EMBEDDED_ASSETS "Include pen20 embedded assets" OFF)
option(INCLUDE_ONLY_BONGOCAT_EMBEDDED_ASSETS "Include only bongocat assets, exclude digimon assets" OFF)

# project_options
find_linker(PROJECT_OPTIONS_LINKER)
set(ENABLE_CLANG_TIDY OFF)
set(ENABLE_CPPCHECK OFF)
set(ENABLE_COVERAGE OFF)
set(ENABLE_INCLUDE_WHAT_YOU_USE OFF)
set(ENABLE_BUILD_WITH_TIME_TRACE OFF)
set(ENABLE_GCC_ANALYZER OFF)
if(ENABLE_STATIC_ANALYZER)
    set(ENABLE_CLANG_TIDY "ENABLE_CLANG_TIDY")
    set(ENABLE_CPPCHECK "ENABLE_CPPCHECK")
    set(ENABLE_INCLUDE_WHAT_YOU_USE "ENABLE_INCLUDE_WHAT_YOU_USE")
    set(ENABLE_GCC_ANALYZER "ENABLE_GCC_ANALYZER")
endif()
if(ENABLE_STATIC_ANALYZER_INCLUDE_WHAT_YOU_USE)
    set(ENABLE_INCLUDE_WHAT_YOU_USE "ENABLE_INCLUDE_WHAT_YOU_USE")
endif()
if(OPT_ENABLE_COVERAGE)
    set(ENABLE_COVERAGE "ENABLE_COVERAGE")
endif()
if(ENABLE_TIME_TRACE)
    set(ENABLE_BUILD_WITH_TIME_TRACE "ENABLE_BUILD_WITH_TIME_TRACE")
endif()
if(OPT_ENABLE_IPO)
    set(ENABLE_IPO "ENABLE_INTERPROCEDURAL_OPTIMIZATION ENABLE_NATIVE_OPTIMIZATION")
    set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
endif()
if(OPT_WARNINGS_AS_ERRORS)
    set(WARNINGS_AS_ERRORS "WARNINGS_AS_ERRORS")
endif()
if(OPT_ENABLE_SANITIZER_ADDRESS)
    set(ENABLE_SANITIZER_ADDRESS ${SUPPORT_SANITIZER_ADDRESS})
endif()
if(OPT_ENABLE_SANITIZER_LEAK)
    set(ENABLE_SANITIZER_LEAK ${SUPPORT_SANITIZER_LEAK})
endif()
if(OPT_ENABLE_SANITIZER_UNDEFINED)
    set(ENABLE_SANITIZER_UNDEFINED_BEHAVIOR ${SUPPORT_SANITIZER_UNDEFINED_BEHAVIOR})
endif()
if(OPT_ENABLE_SANITIZER_THREAD)
    set(ENABLE_SANITIZER_THREAD ${SUPPORT_SANITIZER_THREAD})
endif()
if(OPT_ENABLE_SANITIZER_MEMORY)
    set(ENABLE_SANITIZER_MEMORY ${SUPPORT_SANITIZER_MEMORY})
endif()
if(OPT_ENABLE_UNITY_BUILD)
    set(ENABLE_UNITY "ENABLE_UNITY")
endif()
if(OPT_ENABLE_CLANG_TIDY)
    set(ENABLE_CLANG_TIDY "ENABLE_CLANG_TIDY")
endif()
if(OPT_ENABLE_CPPCHECK)
    set(ENABLE_CPPCHECK "ENABLE_CPPCHECK")
endif()
if(OPT_ENABLE_PCH)
    set(ENABLE_PCH "ENABLE_PCH")
endif()
if(OPT_ENABLE_CACHE)
    set(ENABLE_CACHE "ENABLE_CACHE")
endif()
if(OPT_ENABLE_HARDENING)
    set(ENABLE_CONTROL_FLOW_PROTECTION "ENABLE_CONTROL_FLOW_PROTECTION")
    set(ENABLE_STACK_PROTECTION "ENABLE_STACK_PROTECTION")
    set(ENABLE_OVERFLOW_PROTECTION "ENABLE_OVERFLOW_PROTECTION")
    set(ENABLE_ELF_PROTECTION "ENABLE_ELF_PROTECTION")
    # set(ENABLE_RUNTIME_SYMBOLS_RESOLUTION "ENABLE_RUNTIME_SYMBOLS_RESOLUTION")
endif()
# defaulted_project_options sets recommended defaults and provides user and developer modes and full GUI support for choosing options at
# configure time for more flexibility, look into project_options() macro Initialize project_options variable related to this project This
# overwrites `project_options` and sets `project_warnings` uncomment the options to enable them:
project_options(
        ${ENABLE_CACHE}
        ${ENABLE_CPPCHECK}
        ${ENABLE_CLANG_TIDY}
        ${ENABLE_INCLUDE_WHAT_YOU_USE}
        ENABLE_VS_ANALYSIS
        ${ENABLE_IPO}
        ${ENABLE_COVERAGE}
        ${ENABLE_SANITIZER_ADDRESS}
        ${ENABLE_SANITIZER_UNDEFINED_BEHAVIOR}
        ${ENABLE_SANITIZER_THREAD}
        ${ENABLE_SANITIZER_MEMORY}
        ${ENABLE_CONTROL_FLOW_PROTECTION}
        ${ENABLE_STACK_PROTECTION}
        ${ENABLE_OVERFLOW_PROTECTION}
        ${ENABLE_ELF_PROTECTION}
        ${ENABLE_RUNTIME_SYMBOLS_RESOLUTION}
        ${WARNINGS_AS_ERRORS}
        ${ENABLE_BUILD_WITH_TIME_TRACE}
        ${ENABLE_UNITY}
        LINKER
        ${PROJECT_OPTIONS_LINKER}
        CPPCHECK_OPTIONS
        --enable=style,performance,warning,portability
        --inline-suppr
        # We cannot act on a bug/missing feature of cppcheck
        --suppress=cppcheckError
        --suppress=internalAstError
        # if a file does not have an internalAstError, we get an unmatchedSuppression error
        --suppress=unmatchedSuppression
        --suppress=passedByValue
        --suppress=syntaxError
        --suppress=*:${CMAKE_BINARY_DIR}/_deps/*
        --suppress=*:${CMAKE_SOURCE_DIR}/libs/*
        --inconclusive)
message(STATUS "Use Linker: ${PROJECT_OPTIONS_LINKER}")
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
if (INCLUDE_ONLY_BONGOCAT_EMBEDDED_ASSETS)
    target_compile_definitions(bongocat PRIVATE FEATURE_INCLUDE_ONLY_BONGOCAT_EMBEDDED_ASSETS)
else()
    if (INCLUDE_DM_EMBEDDED_ASSETS)
        set(SOURCES ${SOURCES} "${SRC_DIR}/graphics/embedded_assets/dm.c")
        target_compile_definitions(bongocat PRIVATE FEATURE_INCLUDE_DM_EMBEDDED_ASSETS)
    elseif (INCLUDE_DM20_EMBEDDED_ASSETS)
        set(SOURCES ${SOURCES} "${SRC_DIR}/graphics/embedded_assets/dm20.c")
        target_compile_definitions(bongocat PRIVATE FEATURE_INCLUDE_DM20_EMBEDDED_ASSETS)
    elseif (INCLUDE_DMC_EMBEDDED_ASSETS)
        set(SOURCES ${SOURCES} "${SRC_DIR}/graphics/embedded_assets/dmc.c")
        target_compile_definitions(bongocat PRIVATE FEATURE_INCLUDE_DMC_EMBEDDED_ASSETS)
    elseif (INCLUDE_DMX_EMBEDDED_ASSETS)
        set(SOURCES ${SOURCES} "${SRC_DIR}/graphics/embedded_assets/dmx.c")
        target_compile_definitions(bongocat PRIVATE FEATURE_INCLUDE_DMX_EMBEDDED_ASSETS)
    elseif (INCLUDE_PEN20_EMBEDDED_ASSETS)
        set(SOURCES ${SOURCES} "${SRC_DIR}/graphics/embedded_assets/pen20.c")
        target_compile_definitions(bongocat PRIVATE FEATURE_INCLUDE_PEN20_EMBEDDED_ASSETS)
    else()
        # Fallback digimon assets
        set(SOURCES ${SOURCES} "${SRC_DIR}/graphics/embedded_assets/min_dm.c")
        target_compile_definitions(bongocat PRIVATE FEATURE_INCLUDE_MIN_DM_EMBEDDED_ASSETS)
    endif()
endif()

target_sources(bongocat PRIVATE ${SOURCES} ${GENERATED_PROTOCOLS_SOURCES})
add_dependencies(bongocat protocols)
target_include_directories(bongocat PRIVATE ${INCLUDE_DIR})
target_include_directories(bongocat SYSTEM PRIVATE ${PROTOCOLS_DIR} ${CMAKE_SOURCE_DIR}/lib)

target_link_libraries(bongocat PRIVATE project_warnings project_options)
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
    $<$<AND:$<COMPILE_LANGUAGE:C>,$<CXX_COMPILER_ID:Clang>>:-std=gnu23>
    $<$<AND:$<COMPILE_LANGUAGE:CXX>,$<CXX_COMPILER_ID:Clang>>:-std=gnu++26>
    $<$<AND:$<COMPILE_LANGUAGE:C>,$<CXX_COMPILER_ID:Clang>>:-Wno-c23-extensions>
    $<$<AND:$<COMPILE_LANGUAGE:CXX>,$<CXX_COMPILER_ID:Clang>>:-Wno-c23-extensions>
)

# no exceptions
target_compile_options(bongocat PRIVATE
        $<$<COMPILE_LANGUAGE:CXX>:
            -fno-exceptions -fno-rtti
            #-ffreestanding                 # free, malloc etc. is in use
            -nostdlib++
            -fno-use-cxa-atexit             # global destructs not needed ?
            #-fno-threadsafe-statics        # local statics are in use
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
        $<$<CONFIG:MinSizeRel>:-fno-inline-functions -fomit-frame-pointer -fno-asynchronous-unwind-tables -fno-unwind-tables -ffunction-sections -fdata-sections>
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
target_include_directories(bongocat PRIVATE ${WAYLAND_CLIENT_INCLUDE_DIRS})
target_compile_options(bongocat PRIVATE ${WAYLAND_CLIENT_CFLAGS_OTHER})
target_link_libraries(bongocat PRIVATE ${WAYLAND_CLIENT_LIBRARIES})
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
