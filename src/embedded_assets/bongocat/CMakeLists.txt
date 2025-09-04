add_library(assets_bongocat_interface INTERFACE)

add_library(assets_bongocat_feature INTERFACE)
target_compile_definitions(assets_bongocat_feature INTERFACE FEATURE_BONGOCAT_EMBEDDED_ASSETS)

add_library(assets_bongocat STATIC)
target_sources(assets_bongocat PRIVATE bongocat_get_sprite_sheet.cpp bongocat_images.c)
target_compile_options(assets_bongocat PRIVATE -ffunction-sections -fdata-sections)
target_include_directories(assets_bongocat
        PUBLIC ${INCLUDE_DIR}
        PRIVATE ${INCLUDE_DIR}/embedded_assets/bongocat)
target_link_libraries(assets_bongocat
        PUBLIC assets_bongocat_interface
        PRIVATE assets_bongocat_feature bongocat_options)
