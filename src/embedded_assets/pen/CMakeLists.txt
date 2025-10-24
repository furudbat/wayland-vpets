add_library(assets_pen_interface INTERFACE)
target_include_directories(assets_pen_interface INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include ${SRC_DIR}/embedded_assets/pen/include)

add_library(assets_pen_feature INTERFACE)
target_compile_definitions(assets_pen_feature INTERFACE FEATURE_ENABLE_DM_EMBEDDED_ASSETS FEATURE_PEN_EMBEDDED_ASSETS)

add_library(assets_pen STATIC)
target_sources(assets_pen PRIVATE pen_get_sprite_sheet.cpp pen_config_parse_animation_name.cpp pen_images.c)
target_compile_options(assets_pen PRIVATE -ffunction-sections -fdata-sections -fno-unroll-loops)
target_include_directories(assets_pen
        PRIVATE ${INCLUDE_DIR}/embedded_assets/pen
        PUBLIC ${INCLUDE_DIR})
target_link_libraries(assets_pen
        PUBLIC assets_pen_interface
        PRIVATE assets_pen_feature bongocat_options)