add_library(assets_dmall_interface INTERFACE)
target_include_directories(assets_dmall_interface INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include ${SRC_DIR}/embedded_assets/dmall/include)

add_library(assets_dmall_feature INTERFACE)
target_compile_definitions(assets_dmall_feature INTERFACE FEATURE_ENABLE_DM_EMBEDDED_ASSETS FEATURE_DMALL_EMBEDDED_ASSETS)

add_library(assets_dmall STATIC)
target_sources(assets_dmall PRIVATE dmall_get_sprite_sheet.cpp dmall_images.c)
target_compile_options(assets_dmall PRIVATE -ffunction-sections -fdata-sections)
target_include_directories(assets_dmall
        PRIVATE ${INCLUDE_DIR}/embedded_assets/dmall
        PUBLIC ${INCLUDE_DIR})
target_link_libraries(assets_dmall
        PUBLIC assets_dmall_interface
        PRIVATE assets_dmall_feature bongocat_options)