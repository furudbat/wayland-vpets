enable_testing()

add_library(test_bongocat_all_loaders INTERFACE)
target_link_libraries(
  test_bongocat_all_loaders
  INTERFACE
    assets_bongocat_loader
    assets_bongocat_feature
    assets_bongocat_interface
    -Wl,--whole-archive
    assets_bongocat
    -Wl,--no-whole-archive
    assets_dm_loader
    assets_dm_feature
    assets_dm_interface
    -Wl,--whole-archive
    assets_dm
    -Wl,--no-whole-archive
    assets_dm20_loader
    assets_dm20_feature
    assets_dm20_interface
    -Wl,--whole-archive
    assets_dm20
    -Wl,--no-whole-archive
    assets_dmx_loader
    assets_dmx_feature
    assets_dmx_interface
    -Wl,--whole-archive
    assets_dmx
    -Wl,--no-whole-archive
    assets_dmc_loader
    assets_dmc_feature
    assets_dmc_interface
    -Wl,--whole-archive
    assets_dmc
    -Wl,--no-whole-archive
    assets_pen_loader
    assets_pen_feature
    assets_pen_interface
    -Wl,--whole-archive
    assets_pen
    -Wl,--no-whole-archive
    assets_pen20_loader
    assets_pen20_feature
    assets_pen20_interface
    -Wl,--whole-archive
    assets_pen20
    -Wl,--no-whole-archive
    assets_dmall_loader
    assets_dmall_feature
    assets_dmall_interface
    -Wl,--whole-archive
    assets_dmall
    -Wl,--no-whole-archive
    assets_more_ms_agent_loader
    assets_more_ms_agent
    assets_more_ms_agent_feature
    assets_more_ms_agent_interface
    -Wl,--whole-archive
    assets_more_ms_agent
    -Wl,--no-whole-archive
    assets_misc_loader
    assets_misc_feature
    assets_misc_interface
    assets_custom_loader
    -Wl,--whole-archive
    assets_misc
    -Wl,--no-whole-archive
    assets_pmd_loader
    assets_pmd_feature
    assets_pmd_interface
    assets_custom_loader
    -Wl,--whole-archive
    assets_pmd
    -Wl,--no-whole-archive
    assets_pkmn_loader
    assets_pkmn_feature
    assets_pkmn_interface
    -Wl,--whole-archive
    assets_pkmn
    -Wl,--no-whole-archive
)
# base for assembling exec(s)
set(
  BASE_TEST_SOURCES
  ${CMAKE_SOURCE_DIR}/src/utils/error.cpp
  ${CMAKE_SOURCE_DIR}/src/utils/memory.cpp
  ${CMAKE_SOURCE_DIR}/src/utils/random.cpp
  ${CMAKE_SOURCE_DIR}/src/utils/system_memory.cpp
  ${CMAKE_SOURCE_DIR}/src/utils/time.cpp
  ${CMAKE_SOURCE_DIR}/src/config/config.cpp
  ${CMAKE_SOURCE_DIR}/src/config/config_watcher.cpp
  ${CMAKE_SOURCE_DIR}/src/graphics/animation.cpp
  ${CMAKE_SOURCE_DIR}/src/graphics/animation_init.cpp
  ${CMAKE_SOURCE_DIR}/src/graphics/bar.cpp
  ${CMAKE_SOURCE_DIR}/src/graphics/drawing_images.cpp
  ${CMAKE_SOURCE_DIR}/src/platform/input.cpp
  ${CMAKE_SOURCE_DIR}/src/platform/update.cpp
  ${CMAKE_SOURCE_DIR}/src/platform/wayland.cpp
  ${CMAKE_SOURCE_DIR}/src/platform/wayland_callbacks.cpp
  ${CMAKE_SOURCE_DIR}/src/platform/wayland_hyprland.cpp
  ${CMAKE_SOURCE_DIR}/src/platform/wayland_setups.cpp
  ${CMAKE_SOURCE_DIR}/src/platform/wayland_sway.cpp
)
add_library(test_bongocat_base INTERFACE)
target_sources(test_bongocat_base INTERFACE ${BASE_TEST_SOURCES})
target_include_directories(test_bongocat_base INTERFACE ${INCLUDE_DIR})
target_link_libraries(test_bongocat_base INTERFACE bongocat_options bongocat_libs)
target_compile_options(test_bongocat_base INTERFACE -ffunction-sections -fdata-sections)
target_compile_definitions(test_bongocat_base INTERFACE TEST_BUILD)

add_executable(
  bongocat_tests
  test_main.cpp
  test_utils.cpp
  test_memory.cpp
  test_config.cpp
  test_config_2.cpp
  test_config_3.cpp
)
target_include_directories(bongocat_tests PRIVATE ${CMAKE_SOURCE_DIR}/tests ${CMAKE_SOURCE_DIR}/lib)
target_link_libraries(
  bongocat_tests
  PRIVATE
    test_bongocat_base
    test_bongocat_all_loaders
    assets_custom_sprite_sheet_feature
    assets_custom_loader
    bongocat_options
    bongocat_libs
)
target_link_options(bongocat_tests PRIVATE -Wl,-T,${CMAKE_BINARY_DIR}/assets_segment.ld)

add_test(NAME bongocat_tests COMMAND bongocat_tests)
