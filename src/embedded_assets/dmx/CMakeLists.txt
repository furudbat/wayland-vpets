add_library(assets_dmx_interface INTERFACE)
target_include_directories(assets_dmx_interface INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include ${SRC_DIR}/embedded_assets/dmx/include)

add_library(assets_dmx_feature INTERFACE)
target_compile_definitions(assets_dmx_feature INTERFACE FEATURE_ENABLE_DM_EMBEDDED_ASSETS FEATURE_DMX_EMBEDDED_ASSETS)

add_library(assets_dmx STATIC)
target_sources(assets_dmx PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/dmx_get_sprite_sheet.cpp ${CMAKE_CURRENT_SOURCE_DIR}/dmx_images.c)
target_compile_options(assets_dmx PRIVATE -ffunction-sections -fdata-sections)
target_include_directories(assets_dmx
        PRIVATE ${INCLUDE_DIR}/embedded_assets/dmx
        PUBLIC ${INCLUDE_DIR})
target_link_libraries(assets_dmx
        PUBLIC assets_dmx_interface
        PRIVATE assets_dmx_feature bongocat_options)