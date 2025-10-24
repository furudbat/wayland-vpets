add_library(assets_pen20_interface INTERFACE)
target_include_directories(assets_pen20_interface INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include ${SRC_DIR}/embedded_assets/pen20/include)

add_library(assets_pen20_feature INTERFACE)
target_compile_definitions(assets_pen20_feature INTERFACE FEATURE_ENABLE_DM_EMBEDDED_ASSETS FEATURE_PEN20_EMBEDDED_ASSETS)

add_library(assets_pen20 STATIC)
target_sources(assets_pen20 PRIVATE pen20_get_sprite_sheet.cpp pen20_config_parse_animation_name.cpp pen20_images.c)
target_compile_options(assets_pen20 PRIVATE -ffunction-sections -fdata-sections -fno-unroll-loops)
target_include_directories(assets_pen20
        PRIVATE ${INCLUDE_DIR}/embedded_assets/pen20
        PUBLIC ${INCLUDE_DIR})
target_link_libraries(assets_pen20
        PUBLIC assets_pen20_interface
        PRIVATE assets_pen20_feature bongocat_options)