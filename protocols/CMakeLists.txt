if(DEFINED ENV{WAYLAND_PROTOCOLS_DIR})
  set(WAYLAND_PROTOCOLS_DIR "$ENV{WAYLAND_PROTOCOLS_DIR}" CACHE PATH "Path to wayland-protocols")
  set(PROTOCOL_XML_XDG_EXTERNAL ${WAYLAND_PROTOCOLS_DIR}/stable/xdg-shell/xdg-shell.xml)
else()
  set(WAYLAND_PROTOCOLS_DIR "/usr/share/wayland-protocols" CACHE PATH "Path to wayland-protocols")
  set(PROTOCOL_XML_XDG_EXTERNAL ${WAYLAND_PROTOCOLS_DIR}/stable/xdg-shell/xdg-shell.xml)
endif()

set(PROTOCOL_XML_WLR ${PROTOCOLS_DIR}/wlr-layer-shell-unstable-v1.xml)
if(EXISTS "${PROTOCOL_XML_XDG_EXTERNAL}")
  set(PROTOCOL_XML_XDG ${PROTOCOL_XML_XDG_EXTERNAL})
else()
  set(PROTOCOL_XML_XDG ${PROTOCOLS_DIR}/xdg-shell.xml)
endif()
set(PROTOCOL_XML_WLR_FOREIGN ${PROTOCOLS_DIR}/wlr-foreign-toplevel-management-unstable-v1.xml)
set(PROTOCOL_XML_XDG_OUTPUT ${PROTOCOLS_DIR}/xdg-output-unstable-v1.xml)
set(PROTOCOL_XML_FRACTIONAL_SCALE ${PROTOCOLS_DIR}/fractional-scale-v1.xml)
set(PROTOCOL_XML_VIEWPORTER ${PROTOCOLS_DIR}/viewporter.xml)
set(
  GENERATED_PROTOCOLS_SOURCES
  ${PROTOCOLS_DIR}/zwlr-layer-shell-v1-protocol.c
  ${PROTOCOLS_DIR}/xdg-shell-protocol.c
  ${PROTOCOLS_DIR}/wlr-foreign-toplevel-management-v1-protocol.c
  ${PROTOCOLS_DIR}/xdg-output-unstable-v1-protocol.c
  ${PROTOCOLS_DIR}/fractional-scale-v1-protocol.c
  ${PROTOCOLS_DIR}/viewporter-protocol.c
)
set(
  GENERATED_PROTOCOLS_HEADERS
  ${PROTOCOLS_DIR}/zwlr-layer-shell-v1-client-protocol.h
  ${PROTOCOLS_DIR}/xdg-shell-client-protocol.h
  ${PROTOCOLS_DIR}/wlr-foreign-toplevel-management-v1-client-protocol.h
  ${PROTOCOLS_DIR}/xdg-output-unstable-v1-client-protocol.h
  ${PROTOCOLS_DIR}/fractional-scale-v1-client-protocol.h
  ${PROTOCOLS_DIR}/viewporter-client-protocol.h
)
set(GENERATED_PROTOCOLS ${GENERATED_PROTOCOLS_SOURCES} ${GENERATED_PROTOCOLS_HEADERS})

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  set(_generated_protocols_default ON)
else()
  set(_generated_protocols_default OFF)
endif()
cmake_dependent_option(
  GENERATED_PROTOCOLS_ENABLED
  "Generate protocols files for wayland"
  ${_generated_protocols_default}
  WAYLAND_SCANNER_EXECUTABLE
  OFF
)
if(GENERATED_PROTOCOLS_ENABLED)
  if(NOT WAYLAND_SCANNER_EXECUTABLE)
    message(WARNING "wayland-scanner not installed")
  endif()
  add_custom_command(
    OUTPUT ${GENERATED_PROTOCOLS}
    COMMAND ${WAYLAND_SCANNER_EXECUTABLE} client-header ${PROTOCOL_XML_XDG} ${PROTOCOLS_DIR}/xdg-shell-client-protocol.h
    COMMAND ${WAYLAND_SCANNER_EXECUTABLE} private-code ${PROTOCOL_XML_XDG} ${PROTOCOLS_DIR}/xdg-shell-protocol.c
    COMMAND ${WAYLAND_SCANNER_EXECUTABLE} client-header ${PROTOCOL_XML_WLR} ${PROTOCOLS_DIR}/zwlr-layer-shell-v1-client-protocol.h
    COMMAND ${WAYLAND_SCANNER_EXECUTABLE} private-code ${PROTOCOL_XML_WLR} ${PROTOCOLS_DIR}/zwlr-layer-shell-v1-protocol.c
    COMMAND
      ${WAYLAND_SCANNER_EXECUTABLE} private-code ${PROTOCOL_XML_WLR_FOREIGN} ${PROTOCOLS_DIR}/wlr-foreign-toplevel-management-v1-protocol.c
    COMMAND
      ${WAYLAND_SCANNER_EXECUTABLE} client-header ${PROTOCOL_XML_WLR_FOREIGN}
      ${PROTOCOLS_DIR}/wlr-foreign-toplevel-management-v1-client-protocol.h
    COMMAND ${WAYLAND_SCANNER_EXECUTABLE} client-header ${PROTOCOL_XML_XDG_OUTPUT} ${PROTOCOLS_DIR}/xdg-output-unstable-v1-client-protocol.h
    COMMAND ${WAYLAND_SCANNER_EXECUTABLE} private-code ${PROTOCOL_XML_XDG_OUTPUT} ${PROTOCOLS_DIR}/xdg-output-unstable-v1-protocol.c
    COMMAND
      ${WAYLAND_SCANNER_EXECUTABLE} client-header ${PROTOCOL_XML_FRACTIONAL_SCALE} ${PROTOCOLS_DIR}/fractional-scale-v1-client-protocol.h
    COMMAND ${WAYLAND_SCANNER_EXECUTABLE} private-code ${PROTOCOL_XML_FRACTIONAL_SCALE} ${PROTOCOLS_DIR}/fractional-scale-v1-protocol.c
    COMMAND ${WAYLAND_SCANNER_EXECUTABLE} client-header ${PROTOCOL_XML_VIEWPORTER} ${PROTOCOLS_DIR}/viewporter-client-protocol.h
    COMMAND ${WAYLAND_SCANNER_EXECUTABLE} private-code ${PROTOCOL_XML_VIEWPORTER} ${PROTOCOLS_DIR}/viewporter-protocol.c
    DEPENDS
      ${PROTOCOL_XML_WLR}
      ${PROTOCOL_XML_XDG}
      ${PROTOCOL_XML_WLR_FOREIGN}
      ${PROTOCOL_XML_XDG_OUTPUT}
      ${PROTOCOL_XML_FRACTIONAL_SCALE}
      ${PROTOCOL_XML_VIEWPORTER}
    COMMENT "Generating Wayland protocol files..."
  )
  add_custom_target(gen_protocols DEPENDS ${GENERATED_PROTOCOLS})
  set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES "${GENERATED_PROTOCOLS}")
endif()

add_library(protocols STATIC ${GENERATED_PROTOCOLS_SOURCES})
target_sources(protocols PRIVATE ${GENERATED_PROTOCOLS_SOURCES})
target_sources(protocols PUBLIC FILE_SET HEADERS BASE_DIRS ${PROTOCOLS_DIR} FILES ${GENERATED_PROTOCOLS_HEADERS})
if(GENERATED_PROTOCOLS_ENABLED)
  add_dependencies(protocols gen_protocols)
endif()
target_include_directories(protocols SYSTEM PUBLIC ${PROTOCOLS_DIR})
