# @NOTE: based on project_options and bongocat_options)
add_library(project_lib_options INTERFACE)
target_compile_options(
  project_lib_options
  INTERFACE
    # allow --gc-sections (MinSizeRel) to drop unused lib functions
    -ffunction-sections
    -fdata-sections
    -fstack-protector-strong
    # no exceptions
    $<$<COMPILE_LANGUAGE:CXX>:-fno-exceptions -fno-unwind-tables -fno-rtti -nostdlib++>
    # optimization
    $<$<CONFIG:Release>:-fomit-frame-pointer>
    $<$<CONFIG:MinSizeRel>:
    -fno-inline-functions
    -fomit-frame-pointer
    -fno-asynchronous-unwind-tables
    -fno-unroll-loops
    -fmerge-all-constants
    -fno-math-errno
    -fno-stack-protector
    >
)

add_subdirectory(cavacore)
add_subdirectory(doctest)
add_subdirectory(nanosvg)
add_subdirectory(pngle)
add_subdirectory(stb_image)