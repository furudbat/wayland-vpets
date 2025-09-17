add_library(assets_dm20_interface INTERFACE)
target_include_directories(assets_dm20_interface INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include ${SRC_DIR}/embedded_assets/dm20/include)

add_library(assets_dm20_feature INTERFACE)
target_compile_definitions(assets_dm20_feature INTERFACE FEATURE_ENABLE_DM_EMBEDDED_ASSETS FEATURE_DM20_EMBEDDED_ASSETS)

add_library(assets_dm20 STATIC)
target_sources(assets_dm20 PRIVATE dm20_get_sprite_sheet.cpp dm20_config_parse_animation_name.cpp dm20_images.c)
target_compile_options(assets_dm20 PRIVATE -ffunction-sections -fdata-sections -fno-unroll-loops)
target_include_directories(assets_dm20
        PRIVATE ${INCLUDE_DIR}/embedded_assets/dm20
        PUBLIC ${INCLUDE_DIR})
target_link_libraries(assets_dm20
        PUBLIC assets_dm20_interface
        PRIVATE assets_dm20_feature bongocat_options)