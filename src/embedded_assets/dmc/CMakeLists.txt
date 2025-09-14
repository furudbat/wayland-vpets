add_library(assets_dmc_interface INTERFACE)
target_include_directories(assets_dmc_interface INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include ${SRC_DIR}/embedded_assets/dmc/include)

add_library(assets_dmc_feature INTERFACE)
target_compile_definitions(assets_dmc_feature INTERFACE FEATURE_ENABLE_DM_EMBEDDED_ASSETS FEATURE_DMC_EMBEDDED_ASSETS)

add_library(assets_dmc STATIC)
target_sources(assets_dmc PRIVATE dmc_get_sprite_sheet.cpp dmc_config_parse_animation_name.cpp dmc_images.c)
target_compile_options(assets_dmc PRIVATE -ffunction-sections -fdata-sections)
target_include_directories(assets_dmc
        PRIVATE ${INCLUDE_DIR}/embedded_assets/dmc
        PUBLIC ${INCLUDE_DIR})
target_link_libraries(assets_dmc
        PUBLIC assets_dmc_interface
        PRIVATE assets_dmc_feature bongocat_options)