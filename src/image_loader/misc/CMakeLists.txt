add_library(assets_misc_loader STATIC)
target_sources(assets_misc_loader PRIVATE load_images_misc.cpp misc_load_sprite_sheet.cpp)
target_compile_options(assets_misc_loader PRIVATE -ffunction-sections -fdata-sections)
target_include_directories(assets_misc_loader
        PRIVATE ${INCLUDE_DIR}/embedded_assets/misc ${INCLUDE_DIR}/image_loader/misc
        PUBLIC ${INCLUDE_DIR})
target_link_libraries(assets_misc_loader
        PUBLIC assets_image_loader assets_custom_loader assets_misc
        PRIVATE assets_misc_interface assets_misc_feature bongocat_options)