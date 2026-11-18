add_library(nanosvg STATIC EXCLUDE_FROM_ALL nanosvg.c)
target_include_directories(nanosvg SYSTEM PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(nanosvg PRIVATE m project_lib_options)
