add_library(assets_dm_interface INTERFACE)
target_include_directories(assets_dm_interface INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include ${SRC_DIR}/embedded_assets/dm/include)

add_library(assets_dm_feature INTERFACE)
target_compile_definitions(assets_dm_feature INTERFACE FEATURE_ENABLE_DM_EMBEDDED_ASSETS FEATURE_DM_EMBEDDED_ASSETS)

add_library(assets_dm STATIC)
target_sources(assets_dm PRIVATE dm_get_sprite_sheet.cpp dm_images.c)
target_compile_options(assets_dm PRIVATE -ffunction-sections -fdata-sections)
target_include_directories(assets_dm
        PRIVATE ${INCLUDE_DIR}/embedded_assets/dm
        PUBLIC ${INCLUDE_DIR})
target_link_libraries(assets_dm
        PUBLIC assets_dm_interface
        PRIVATE assets_dm_feature bongocat_options)