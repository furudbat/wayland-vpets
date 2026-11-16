add_library(stb_image STATIC EXCLUDE_FROM_ALL stb_image.c)
target_include_directories(stb_image SYSTEM PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_definitions(stb_image PUBLIC STBI_NO_STDIO STBI_ONLY_PNG)
target_compile_definitions(stb_image PUBLIC STBI_NO_LINEAR)
target_compile_definitions(
  stb_image PRIVATE $<$<OR:$<NOT:$<CONFIG:Debug>>,$<BOOL:${FEATURE_DISABLE_LOGGER}>>:STBI_NO_FAILURE_STRINGS>
)
target_link_libraries(stb_image PRIVATE project_lib_options)
