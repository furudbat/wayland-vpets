add_library(assets_dmc_loader STATIC)
target_sources(assets_dmc_loader PRIVATE dmc_load_sprite_sheet.cpp load_images_dmc.cpp)
target_compile_options(assets_dmc_loader PRIVATE -ffunction-sections -fdata-sections)
target_include_directories(assets_dmc_loader
        PRIVATE ${INCLUDE_DIR}/embedded_assets/dmc ${INCLUDE_DIR}/image_loader/dmc
        PUBLIC ${INCLUDE_DIR})
target_link_libraries(assets_dmc_loader
        PUBLIC assets_image_loader assets_base_dm_loader assets_dmc
        PRIVATE assets_dmc_interface assets_dmc_feature bongocat_options)