# stb_image lib
add_library(assets_image_loader STATIC)
target_include_directories(assets_image_loader
        PRIVATE ${INCLUDE_DIR}/image_loader
        PUBLIC ${INCLUDE_DIR}
        SYSTEM PRIVATE ${PROJECT_SOURCE_DIR}/lib)
target_link_libraries(assets_image_loader PRIVATE bongocat_options)

add_library(stb_image STATIC)
target_include_directories(stb_image SYSTEM PRIVATE ${PROJECT_SOURCE_DIR}/lib)
target_sources(stb_image PRIVATE stb_image.c)
target_compile_definitions(stb_image PUBLIC STBI_NO_STDIO STBI_ONLY_PNG)
target_compile_definitions(stb_image PUBLIC
        $<$<CONFIG:MinSizeRel>:STBI_NO_LINEAR>
)

target_sources(assets_image_loader PRIVATE load_images.cpp load_images_stb_image.cpp)
target_link_libraries(assets_image_loader PRIVATE stb_image)
target_compile_definitions(assets_image_loader PUBLIC FEATURE_USE_STB_IMAGE)


add_subdirectory(bongocat)
add_subdirectory(ms_agent)
add_subdirectory(base_dm)
add_subdirectory(dm)
add_subdirectory(dm20)
add_subdirectory(dmc)
add_subdirectory(dmx)
add_subdirectory(min_dm)
