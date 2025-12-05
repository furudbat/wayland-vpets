add_library(assets_pmd_interface INTERFACE)
target_include_directories(assets_pmd_interface INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include ${SRC_DIR}/embedded_assets/pmd/include)

add_library(assets_pmd_feature INTERFACE)
target_compile_definitions(assets_pmd_feature INTERFACE FEATURE_PMD_EMBEDDED_ASSETS)

add_library(assets_pmd STATIC)
target_sources(assets_pmd PRIVATE pmd_get_sprite_sheet.cpp pmd_get_sprite_sheet_settings.cpp pmd_config_parse_animation_name.cpp pmd_images.c)
target_compile_options(assets_pmd PRIVATE -ffunction-sections -fdata-sections -fno-unroll-loops)
target_include_directories(assets_pmd
        PRIVATE ${INCLUDE_DIR}/embedded_assets/pmd
        PUBLIC ${INCLUDE_DIR})
target_link_libraries(assets_pmd
        PUBLIC assets_pmd_interface
        PRIVATE assets_pmd_feature bongocat_options)