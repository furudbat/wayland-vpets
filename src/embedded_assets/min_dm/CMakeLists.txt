add_library(assets_min_dm_interface INTERFACE)
target_include_directories(assets_min_dm_interface INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include ${SRC_DIR}/embedded_assets/min_dm/include)

add_library(assets_min_dm_feature INTERFACE)
target_compile_definitions(assets_min_dm_feature INTERFACE FEATURE_ENABLE_DM_EMBEDDED_ASSETS FEATURE_MIN_DM_EMBEDDED_ASSETS)

add_library(assets_min_dm STATIC)
target_sources(assets_min_dm PRIVATE min_dm_get_sprite_sheet.cpp min_dm_images.c)
target_compile_options(assets_min_dm PRIVATE -ffunction-sections -fdata-sections)
target_include_directories(assets_min_dm
        PRIVATE ${INCLUDE_DIR}/embedded_assets/min_dm
        PUBLIC ${INCLUDE_DIR})
target_link_libraries(assets_min_dm
        PUBLIC assets_min_dm_interface
        PRIVATE assets_min_dm_feature bongocat_options)