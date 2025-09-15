add_library(assets_pkmn_interface INTERFACE)
target_include_directories(assets_pkmn_interface INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include ${SRC_DIR}/embedded_assets/pkmn/include)

add_library(assets_pkmn_feature INTERFACE)
target_compile_definitions(assets_pkmn_feature INTERFACE FEATURE_PKMN_EMBEDDED_ASSETS)

add_library(assets_pkmn STATIC)
target_sources(assets_pkmn PRIVATE pkmn_get_sprite_sheet.cpp pkmn_config_parse_animation_name.cpp pkmn_images.c)
target_compile_options(assets_pkmn PRIVATE -ffunction-sections -fdata-sections)
target_include_directories(assets_pkmn
        PRIVATE ${INCLUDE_DIR}/embedded_assets/pkmn
        PUBLIC ${INCLUDE_DIR})
target_link_libraries(assets_pkmn
        PUBLIC assets_pkmn_interface
        PRIVATE assets_pkmn_feature bongocat_options)