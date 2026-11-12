find_package(Threads REQUIRED)
find_package(PkgConfig REQUIRED)

pkg_search_module(FFTW3 REQUIRED fftw3)

# ---------------------------------------------------------
# TARGET 1: cavacore lib
# ---------------------------------------------------------
add_library(cavacore STATIC)
target_sources(cavacore PRIVATE cavacore.c)

target_include_directories(cavacore PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(cavacore PRIVATE m ${FFTW3_LIBRARIES})
target_include_directories(cavacore PRIVATE ${FFTW3_INCLUDE_DIRS})