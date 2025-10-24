add_library(assets_misc_interface INTERFACE)

add_library(assets_misc_feature INTERFACE)
target_compile_definitions(assets_misc_feature INTERFACE FEATURE_MISC_EMBEDDED_ASSETS)

add_library(assets_misc STATIC)
target_sources(assets_misc PRIVATE misc_get_sprite_sheet.cpp misc_images.c)
target_compile_options(assets_misc PRIVATE -ffunction-sections -fdata-sections -fno-unroll-loops)
target_include_directories(assets_misc
        PRIVATE ${INCLUDE_DIR}/embedded_assets/misc
        PUBLIC ${INCLUDE_DIR})
target_link_libraries(assets_misc
        PUBLIC assets_misc_interface
        PRIVATE assets_misc_feature bongocat_options)