# stb_image lib
add_library(assets_image_loader STATIC)
target_sources(assets_image_loader PRIVATE stb_image.cpp load_images.cpp)
target_include_directories(assets_image_loader
        PRIVATE ${INCLUDE_DIR}/image_loader
        PUBLIC ${INCLUDE_DIR}
        SYSTEM PRIVATE ${PROJECT_SOURCE_DIR}/lib)
target_link_libraries(assets_image_loader PRIVATE bongocat_options)


add_subdirectory(bongocat)
add_subdirectory(ms_agent)
add_subdirectory(base_dm)
add_subdirectory(dm)
add_subdirectory(dm20)
add_subdirectory(dmc)
add_subdirectory(dmx)
add_subdirectory(min_dm)
