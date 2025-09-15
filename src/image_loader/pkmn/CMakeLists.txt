add_library(assets_pkmn_loader STATIC)
target_sources(assets_pkmn_loader PRIVATE pkmn_load_sprite_sheet.cpp load_images_pkmn.cpp)
target_compile_options(assets_pkmn_loader PRIVATE -ffunction-sections -fdata-sections)
target_include_directories(assets_pkmn_loader
        PRIVATE ${INCLUDE_DIR}/embedded_assets/pkmn ${INCLUDE_DIR}/image_loader/pkmn
        PUBLIC ${INCLUDE_DIR})
target_link_libraries(assets_pkmn_loader
        PUBLIC assets_image_loader assets_pkmn
        PRIVATE assets_pkmn_interface assets_pkmn_feature bongocat_options)