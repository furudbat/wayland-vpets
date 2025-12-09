# stb_image lib
add_library(assets_image_loader STATIC)
target_include_directories(
  assets_image_loader
  PRIVATE ${INCLUDE_DIR}/image_loader
  PUBLIC ${INCLUDE_DIR})
target_include_directories(assets_image_loader SYSTEM PRIVATE ${PROJECT_SOURCE_DIR}/lib)
target_link_libraries(assets_image_loader PRIVATE bongocat_options)

if(FEATURE_USE_HYBRID_IMAGE_BACKEND)
  add_library(pngle STATIC)
  target_include_directories(pngle SYSTEM PRIVATE ${PROJECT_SOURCE_DIR}/lib)
  target_sources(pngle PRIVATE pngle.c miniz.c)
  target_compile_definitions(pngle PUBLIC PNGLE_NO_GAMMA_CORRECTION)

  add_library(stb_image STATIC)
  target_include_directories(stb_image SYSTEM PRIVATE ${PROJECT_SOURCE_DIR}/lib)
  target_sources(stb_image PRIVATE stb_image.c)
  target_compile_definitions(stb_image PUBLIC STBI_NO_STDIO STBI_ONLY_PNG)
  target_compile_definitions(stb_image PUBLIC $<$<CONFIG:MinSizeRel>:STBI_NO_LINEAR>)

  target_sources(assets_image_loader PRIVATE load_images.cpp load_images_hybrid.cpp)
  target_link_libraries(assets_image_loader PRIVATE pngle stb_image)
  target_compile_definitions(assets_image_loader PUBLIC FEATURE_USE_HYBRID_IMAGE_BACKEND)
  message(STATUS "Use hybrid image backend (stb_image + pngle)")
else()
  if(FEATURE_USE_PNGLE)
    add_library(pngle STATIC)
    target_include_directories(pngle SYSTEM PRIVATE ${PROJECT_SOURCE_DIR}/lib)
    target_sources(pngle PRIVATE pngle.c miniz.c)
    target_compile_definitions(pngle PUBLIC PNGLE_NO_GAMMA_CORRECTION)

    target_sources(assets_image_loader PRIVATE load_images.cpp load_images_pngle.cpp)
    target_link_libraries(assets_image_loader PRIVATE pngle)
    target_compile_definitions(assets_image_loader PUBLIC FEATURE_USE_PNGLE)
    message(STATUS "Use pngle image backend")
  else()
    add_library(stb_image STATIC)
    target_include_directories(stb_image SYSTEM PRIVATE ${PROJECT_SOURCE_DIR}/lib)
    target_sources(stb_image PRIVATE stb_image.c)
    target_compile_definitions(stb_image PUBLIC STBI_NO_STDIO STBI_ONLY_PNG)
    target_compile_definitions(stb_image PUBLIC $<$<CONFIG:MinSizeRel>:STBI_NO_LINEAR>)

    target_sources(assets_image_loader PRIVATE load_images.cpp load_images_stb_image.cpp)
    target_link_libraries(assets_image_loader PRIVATE stb_image)
    target_compile_definitions(assets_image_loader PUBLIC FEATURE_USE_STB_IMAGE)
    message(STATUS "Use stb_image backend")
  endif()
endif()

# @NOTE(assets): 3. add image_loader sub directory
add_subdirectory(bongocat)
add_subdirectory(base_dm)
add_subdirectory(dm)
add_subdirectory(dm20)
add_subdirectory(dmc)
add_subdirectory(dmx)
add_subdirectory(pen)
add_subdirectory(pen20)
add_subdirectory(dmall)
add_subdirectory(min_dm)
add_subdirectory(ms_agent)
add_subdirectory(pkmn)
add_subdirectory(custom)
add_subdirectory(misc)
add_subdirectory(pmd)

# @NOTE(assets): 3.1. add image_loader in include/image_loader (see other load_images_...h as reference) @NOTE(assets): 3.2. add
# image_loader in src/image_loader/xxx (see other load_images_...cpp as reference)
