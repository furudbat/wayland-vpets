cmake_minimum_required(VERSION 3.24)
project(bongocat LANGUAGES C CXX VERSION 1.4.0)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the build type." FORCE)
endif()

# TODO: add assets options and fully implement switching assets + optimization
#option(INCLUDE_DM_EMBEDDED_ASSETS "Include dm embedded assets (fully)" OFF)
#option(INCLUDE_DM20_EMBEDDED_ASSETS "Include dm20 embedded assets" OFF)
#option(INCLUDE_DMC_EMBEDDED_ASSETS "Include dmc embedded assets" OFF)
#option(INCLUDE_DMX_EMBEDDED_ASSETS "Include dmx embedded assets" OFF)
#option(INCLUDE_PEN20_EMBEDDED_ASSETS "Include pen20 embedded assets" OFF)
option(INCLUDE_ONLY_BONGOCAT_EMBEDDED_ASSETS "Include only bongocat assets, exclude digimon assets" OFF)
option(ENABLE_THREAD_SANITIZERS "Enable thread sanitizer, instead of address,undefined" OFF)

set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(PROTOCOLS_DIR ${CMAKE_SOURCE_DIR}/protocols)
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
if(DEFINED ENV{WAYLAND_PROTOCOLS_DIR})
    set(WAYLAND_PROTOCOLS_DIR "$ENV{WAYLAND_PROTOCOLS_DIR}" CACHE PATH "Path to wayland-protocols")
else()
    set(WAYLAND_PROTOCOLS_DIR "/usr/share/wayland-protocols" CACHE PATH "Path to wayland-protocols")
endif()


set(CMAKE_CXX_STANDARD 23)
set(CMAKE_C_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD_REQUIRED ON)


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
    ${SRC_DIR}/config/config.c
    ${SRC_DIR}/config/config_watcher.c
    ${SRC_DIR}/core/main.c
    ${SRC_DIR}/graphics/animation.c
    ${SRC_DIR}/graphics/animation_init.c
    ${SRC_DIR}/graphics/bar.c
    ${SRC_DIR}/graphics/embedded_assets.c
    ${SRC_DIR}/graphics/embedded_assets/bongocat.c
    ${SRC_DIR}/platform/input.c
    ${SRC_DIR}/platform/wayland.c
    ${SRC_DIR}/utils/error.c
    ${SRC_DIR}/utils/memory.c
    ${SRC_DIR}/utils/time.c
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

set(WARNING_FLAGS
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
    -Wlogical-op
    -Wjump-misses-init
    -Wdouble-promotion
    -Wshadow
)
target_compile_options(bongocat PRIVATE ${WARNING_FLAGS} -fstack-protector-strong)

target_compile_options(bongocat PRIVATE
        $<$<CONFIG:Release>:-march=native;-fomit-frame-pointer;-funroll-loops;-finline-functions>
)

if (ENABLE_THREAD_SANITIZERS)
    target_link_options(bongocat PRIVATE
            $<$<CONFIG:Debug>:-fsanitize=thread>
            $<$<CONFIG:RelWithDebInfo>:-fsanitize=thread>
    )
else()
    target_link_options(bongocat PRIVATE
            $<$<CONFIG:Debug>:-fsanitize=address;-fsanitize=undefined>
            $<$<CONFIG:RelWithDebInfo>:-fsanitize=thread;-fsanitize=undefined>
    )
endif()

target_compile_definitions(bongocat PRIVATE
        $<$<CONFIG:Debug>:BONGOCAT_LOG_LEVEL=4>
        $<$<CONFIG:RelWithDebInfo>:BONGOCAT_LOG_LEVEL=3>
        $<$<CONFIG:Release>:_FORTIFY_SOURCE=2>
        $<$<CONFIG:MinSizeRel>:BONGOCAT_DISABLE_MEMORY_STATISTICS>
        $<$<CONFIG:MinSizeRel>:BONGOCAT_DISABLE_LOGGER>
)

# wayland-client dependency
find_package(PkgConfig REQUIRED)
pkg_check_modules(WAYLAND_CLIENT REQUIRED wayland-client)
target_include_directories(bongocat PRIVATE ${WAYLAND_CLIENT_INCLUDE_DIRS})
target_compile_options(bongocat PRIVATE ${WAYLAND_CLIENT_CFLAGS_OTHER})
target_link_libraries(bongocat PRIVATE ${WAYLAND_CLIENT_LIBRARIES})

target_link_libraries(bongocat PRIVATE m rt pthread)

set_target_properties(bongocat PROPERTIES INTERPROCEDURAL_OPTIMIZATION_RELEASE TRUE)
target_compile_options(bongocat PRIVATE
        $<$<CONFIG:Release>:-flto=8>
)

include(GNUInstallDirs)
install(TARGETS bongocat DESTINATION ${CMAKE_INSTALL_BINDIR})
install(FILES bongocat.conf DESTINATION ${CMAKE_INSTALL_DATADIR}/bongocat RENAME bongocat.conf.example)
install(PROGRAMS scripts/find_input_devices.sh DESTINATION ${CMAKE_INSTALL_BINDIR} RENAME bongocat-find-devices)

set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES "${GENERATED_PROTOCOLS}")