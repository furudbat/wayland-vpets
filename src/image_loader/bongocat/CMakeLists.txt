add_library(assets_bongocat_loader STATIC)
target_sources(assets_bongocat_loader PRIVATE load_images_bongocat.cpp)
target_compile_options(assets_bongocat_loader PRIVATE -ffunction-sections -fdata-sections)
target_include_directories(assets_bongocat_loader
        PRIVATE ${INCLUDE_DIR}/embedded_assets/bongocat ${INCLUDE_DIR}/image_loader/bongocat
        PUBLIC ${INCLUDE_DIR})
target_link_libraries(assets_bongocat_loader
        PUBLIC assets_image_loader assets_bongocat
        PRIVATE assets_bongocat_interface assets_bongocat_feature bongocat_options)