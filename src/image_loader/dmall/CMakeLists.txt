add_library(assets_dmall_loader STATIC)
target_sources(assets_dmall_loader PRIVATE dmall_load_sprite_sheet.cpp load_images_dmall.cpp)
target_compile_options(assets_dmall_loader PRIVATE -ffunction-sections -fdata-sections)
target_include_directories(assets_dmall_loader
        PRIVATE ${INCLUDE_DIR}/embedded_assets/dmall ${INCLUDE_DIR}/image_loader/dmall
        PUBLIC ${INCLUDE_DIR})
target_link_libraries(assets_dmall_loader
        PUBLIC assets_image_loader assets_base_dm_loader assets_dmall
        PRIVATE assets_dmall_interface assets_dmall_feature bongocat_options)