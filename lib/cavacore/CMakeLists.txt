find_package(Threads)
find_package(PkgConfig)

pkg_search_module(FFTW3 fftw3)

# ---------------------------------------------------------
# TARGET 1: cavacore lib
# ---------------------------------------------------------
add_library(cavacore STATIC EXCLUDE_FROM_ALL)
target_sources(cavacore PRIVATE cavacore.c)

target_include_directories(cavacore SYSTEM PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(cavacore PRIVATE m ${FFTW3_LIBRARIES} project_lib_options)
target_include_directories(cavacore PRIVATE ${FFTW3_INCLUDE_DIRS})