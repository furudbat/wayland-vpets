add_library(assets_min_dm_loader STATIC)
target_sources(assets_min_dm_loader PRIVATE load_images_min_dm.cpp min_dm_load_sprite_sheet.cpp)
target_compile_options(assets_min_dm_loader PRIVATE -ffunction-sections -fdata-sections)
target_include_directories(assets_min_dm_loader
        PRIVATE ${INCLUDE_DIR}/embedded_assets/min_dm ${INCLUDE_DIR}/image_loader/min_dm
        PUBLIC ${INCLUDE_DIR})
target_link_libraries(assets_min_dm_loader
        PUBLIC assets_image_loader assets_base_dm_loader assets_min_dm
        PRIVATE assets_min_dm_interface assets_min_dm_feature bongocat_options)