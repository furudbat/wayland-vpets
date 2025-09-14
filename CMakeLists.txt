cmake_minimum_required(VERSION 3.24)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_C_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD_REQUIRED ON)
include(FetchContent)
if(CMAKE_VERSION VERSION_GREATER_EQUAL "3.24.0")
    cmake_policy(SET CMP0135 NEW)
endif()

get_property(BUILDING_MULTI_CONFIG GLOBAL PROPERTY GENERATOR_IS_MULTI_CONFIG)
if(BUILDING_MULTI_CONFIG)
    if(NOT CMAKE_BUILD_TYPE)
        # Make sure that all supported configuration types have their associated conan packages available. You can reduce this list to only the
        # configuration types you use, but only if one is not forced-set on the command line for VS
        message(TRACE "Setting up multi-config build types")
        set(CMAKE_CONFIGURATION_TYPES
                Debug Release RelWithDebInfo MinSizeRel
                CACHE STRING "Enabled build types" FORCE)
    else()
        message(TRACE "User chose a specific build type, so we are using that")
        set(CMAKE_CONFIGURATION_TYPES
                ${CMAKE_BUILD_TYPE}
                CACHE STRING "Enabled build types" FORCE)
    endif()
endif()
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the build type." FORCE)
endif()



project(bongocat LANGUAGES C CXX VERSION 2.4.0)

# Feature Flags
include(CMakeDependentOption)
option(FEATURE_BONGOCAT_EMBEDDED_ASSETS "Include bongocat assets (default)" ON)
option(FEATURE_ENABLE_DM_EMBEDDED_ASSETS "Enable include dm embedded assets" ON)
cmake_dependent_option(FEATURE_DM_EMBEDDED_ASSETS "Include dm embedded assets" OFF FEATURE_ENABLE_DM_EMBEDDED_ASSETS OFF)
cmake_dependent_option(FEATURE_DM20_EMBEDDED_ASSETS "Include dm20 embedded assets (replaces original dm)" OFF FEATURE_ENABLE_DM_EMBEDDED_ASSETS OFF)
cmake_dependent_option(FEATURE_DMC_EMBEDDED_ASSETS "Include dmc embedded assets" OFF FEATURE_ENABLE_DM_EMBEDDED_ASSETS OFF)
cmake_dependent_option(FEATURE_DMX_EMBEDDED_ASSETS "Include dmx embedded assets" OFF FEATURE_ENABLE_DM_EMBEDDED_ASSETS OFF)
#cmake_dependent_option(FEATURE_PEN20_EMBEDDED_ASSETS "Include pen20 embedded assets" OFF FEATURE_ENABLE_DM_EMBEDDED_ASSETS OFF)
cmake_dependent_option(FEATURE_DMALL_EMBEDDED_ASSETS "Include custom colored dm (replace dmc) embedded assets" OFF FEATURE_ENABLE_DM_EMBEDDED_ASSETS OFF)
option(FEATURE_MS_AGENT_EMBEDDED_ASSETS "Include MS agent (Clippy) embedded assets" ON)
cmake_dependent_option(FEATURE_MORE_MS_AGENT_EMBEDDED_ASSETS "Include more MS agents (Links) embedded assets" OFF FEATURE_MS_AGENT_EMBEDDED_ASSETS OFF)
option(FEATURE_DISABLE_LOGGER "Disable Logger (makes enable_debug option obsolete)" OFF)
option(FEATURE_PRELOAD_ASSETS "Preload available assets (More RAM usage, sprite switching on hot-reload)" OFF)
option(FEATURE_MULTI_VERSIONS "Build multiple versions with different assets for installation" OFF)
option(FEATURE_LAZY_LOAD_ASSETS "No Preload assets (less RAM usage, more CPU usage, sprite lazy-load on config reload) (Recommended)" ON)

option(ENABLE_ASAN "Enable Address Sanitizer" OFF)
option(ENABLE_UBSAN "Enable Undefined Behavior Sanitizer" OFF)
option(ENABLE_TSAN "Enable Thread Sanitizer" OFF)

# project_options
# More Warnings
set(CLANG_WARNINGS
        -Wall
        -Wextra # reasonable and standard
        -Wextra-semi # Warn about semicolon after in-class function definition.
        -Wshadow # warn the user if a variable declaration shadows one from a parent context
        -Wnon-virtual-dtor # warn the user if a class with virtual functions has a non-virtual destructor. This helps
        # catch hard to track down memory errors
        -Wold-style-cast # warn for c-style casts
        -Wcast-align # warn for potential performance problem casts
        -Wunused # warn on anything being unused
        -Woverloaded-virtual # warn if you overload (not override) a virtual function
        -Wpedantic # warn if non-standard C++ is used
        -Wconversion # warn on type conversions that may lose data
        -Wsign-conversion # warn on sign conversions
        -Wnull-dereference # warn if a null dereference is detected
        -Wdouble-promotion # warn if float is implicit promoted to double
        -Wformat=2 # warn on security issues around functions that format output (ie printf)
        -Wimplicit-fallthrough # warn on statements that fallthrough without an explicit annotation
)
set(GCC_WARNINGS
        ${CLANG_WARNINGS}
        -Wmisleading-indentation # warn if indentation implies blocks where blocks do not exist
        -Wduplicated-cond # warn if if / else chain has duplicated conditions
        -Wduplicated-branches # warn if if / else branches have duplicated code
        -Wlogical-op # warn about logical operations being used where bitwise were probably wanted
        -Wuseless-cast # warn if you perform a cast to the same type
)
set(C_WARNING_FLAGS
        -Wall -Wextra -Wpedantic -Wformat=2 -Wstrict-prototypes
        -Wmissing-prototypes -Wold-style-definition -Wredundant-decls
        -Wnested-externs -Wmissing-include-dirs -Wlogical-op
        -Wjump-misses-init -Wdouble-promotion -Wshadow
)
set(GCC_C_WARNING_FLAGS
        -Wall -Wextra -Wpedantic -Wshadow -Wcast-align -Wunused 
        -Wconversion -Wsign-conversion -Wformat=2 -Wimplicit-fallthrough 
        -Wnull-dereference -Wdouble-promotion -Wmissing-prototypes 
        -Wstrict-prototypes -Wpointer-arith -Wundef 
        -Wmissing-field-initializers -Wvla)
set(CLANG_C_WARNING_FLAGS
        -Wall -Wextra -Wpedantic -Wshadow -Wcast-align -Wunused 
        -Wconversion -Wsign-conversion -Wformat=2 -Wimplicit-fallthrough 
        -Wnull-dereference -Wdouble-promotion -Wmissing-prototypes 
        -Wstrict-prototypes -Wpointer-arith -Wundef 
        -Wmissing-field-initializers -Wvla 
        -Wmisleading-indentation -Wduplicated-cond -Wduplicated-branches -Wlogical-op)
add_library(project_warnings INTERFACE)
target_compile_options(project_warnings INTERFACE $<$<COMPILE_LANGUAGE:C>:${C_WARNING_FLAGS}>)
target_compile_options(project_warnings INTERFACE
        $<$<AND:$<COMPILE_LANGUAGE:C>,$<C_COMPILER_ID:Clang>>:${CLANG_C_WARNINGS}>
        $<$<AND:$<COMPILE_LANGUAGE:C>,$<C_COMPILER_ID:GNU>>:${GCC_C_WARNINGS}>
        $<$<AND:$<COMPILE_LANGUAGE:CXX>,$<CXX_COMPILER_ID:Clang>>:${CLANG_WARNINGS}>
        $<$<AND:$<COMPILE_LANGUAGE:CXX>,$<CXX_COMPILER_ID:GNU>>:${GCC_WARNINGS}>
)
add_library(project_options INTERFACE)
#target_compile_options(project_options INTERFACE $<$<C_COMPILER_ID:MSVC>:/external:anglebrackets /external:W0>)
#target_compile_options(project_options INTERFACE $<$<CXX_COMPILER_ID:MSVC>:/external:anglebrackets /external:W0>)
set_target_properties(project_options PROPERTIES INTERPROCEDURAL_OPTIMIZATION_RELEASE ON)
set_target_properties(project_options PROPERTIES INTERPROCEDURAL_OPTIMIZATION_RELWITHDEBINFO ON)
add_library(project_sanitizers INTERFACE)
if(CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
    # Check for incompatible options
    if(ENABLE_ASAN AND ENABLE_TSAN)
        message(FATAL_ERROR "ASan and TSan are incompatible. Please enable only one of them.")
    endif()
    if(ENABLE_ASAN)
        target_compile_options(project_sanitizers INTERFACE -fsanitize=address)
        target_link_options(project_sanitizers INTERFACE -fsanitize=address)
    endif()
    if(ENABLE_UBSAN)
        target_compile_options(project_sanitizers INTERFACE -fsanitize=undefined)
        target_link_options(project_sanitizers INTERFACE -fsanitize=undefined)
    endif()
    if(ENABLE_TSAN)
        target_compile_options(project_sanitizers INTERFACE -fsanitize=thread)
        target_link_options(project_sanitizers INTERFACE -fsanitize=thread)
    endif()
endif()

set(PROTOCOLS_DIR ${PROJECT_SOURCE_DIR}/protocols)
add_subdirectory(protocols)


set(SRC_DIR ${PROJECT_SOURCE_DIR}/src)
set(INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
add_subdirectory(src)



add_executable(bongocat)
if (FEATURE_BONGOCAT_EMBEDDED_ASSETS)
    target_link_libraries(bongocat PRIVATE assets_bongocat_loader assets_bongocat assets_bongocat_feature assets_bongocat_interface)
    message(STATUS "Include bongocat assets")
endif()
if (FEATURE_ENABLE_DM_EMBEDDED_ASSETS)
    if (NOT FEATURE_DM20_EMBEDDED_ASSETS AND NOT FEATURE_DM_EMBEDDED_ASSETS AND NOT FEATURE_DMX_EMBEDDED_ASSETS AND NOT FEATURE_DMC_EMBEDDED_ASSETS)
        target_link_libraries(bongocat PRIVATE assets_min_dm_loader assets_min_dm assets_min_dm_feature assets_min_dm_interface)
        message(STATUS "Include min_dm assets")
    else()
        if (FEATURE_DM20_EMBEDDED_ASSETS)
            target_link_libraries(bongocat PRIVATE assets_dm20_loader assets_dm20 assets_dm20_feature assets_dm20_interface)
            message(STATUS "Include dm20 assets")
        elseif (FEATURE_DM_EMBEDDED_ASSETS)
            target_link_libraries(bongocat PRIVATE assets_dm_loader assets_dm assets_dm_feature assets_dm_interface)
            message(STATUS "Include dm assets")
        endif()
        if (FEATURE_DMX_EMBEDDED_ASSETS)
            target_link_libraries(bongocat PRIVATE assets_dmx_loader assets_dmx assets_dmx_feature assets_dmx_interface)
            message(STATUS "Include dmx assets")
        endif()
        if (FEATURE_DMALL_EMBEDDED_ASSETS)
            target_link_libraries(bongocat PRIVATE assets_dmall_loader assets_dmall assets_dmall_feature assets_dmall_interface)
            message(STATUS "Include dmall assets")
        elseif (FEATURE_DMC_EMBEDDED_ASSETS)
            target_link_libraries(bongocat PRIVATE assets_dmc_loader assets_dmc assets_dmc_feature assets_dmc_interface)
            message(STATUS "Include dmc assets")
        endif()
    endif()
endif()
if (FEATURE_MS_AGENT_EMBEDDED_ASSETS)
    target_link_libraries(bongocat PRIVATE assets_ms_agent_loader assets_ms_agent assets_ms_agent_feature assets_ms_agent_interface)
    message(STATUS "Include MS agent assets")
endif()
target_link_libraries(bongocat PRIVATE bongocat_base bongocat_options bongocat_libs)

if (FEATURE_MULTI_VERSIONS)
    add_executable(bongocat-digimon)
    target_link_libraries(bongocat-digimon PRIVATE assets_bongocat_loader assets_bongocat assets_bongocat_feature assets_bongocat_interface)
    target_link_libraries(bongocat-digimon PRIVATE assets_dm20_loader assets_dm20 assets_dm20_feature assets_dm20_interface)
    target_link_libraries(bongocat-digimon PRIVATE assets_dmx_loader assets_dmx assets_dmx_feature assets_dmx_interface)
    target_link_libraries(bongocat-digimon PRIVATE bongocat_base bongocat_options bongocat_libs)

    add_executable(bongocat-digimon-colored)
    target_link_libraries(bongocat-digimon-colored PRIVATE assets_bongocat_loader assets_bongocat assets_bongocat_feature assets_bongocat_interface)
    target_link_libraries(bongocat-digimon-colored PRIVATE assets_dm20_loader assets_dm20 assets_dm20_feature assets_dm20_interface)
    target_link_libraries(bongocat-digimon-colored PRIVATE assets_dmx_loader assets_dmx assets_dmx_feature assets_dmx_interface)
    target_link_libraries(bongocat-digimon-colored PRIVATE assets_dmc_loader assets_dmc assets_dmc_feature assets_dmc_interface)
    target_link_libraries(bongocat-digimon-colored PRIVATE bongocat_base bongocat_options bongocat_libs)

    add_executable(bongocat-digimon-colored-all)
    target_link_libraries(bongocat-digimon-colored-all PRIVATE assets_bongocat_loader assets_bongocat assets_bongocat_feature assets_bongocat_interface)
    target_link_libraries(bongocat-digimon-colored-all PRIVATE assets_dmall_loader assets_dmall assets_dmall_feature assets_dmall_interface)
    target_link_libraries(bongocat-digimon-colored-all PRIVATE bongocat_base bongocat_options bongocat_libs)

    add_executable(bongocat-ms-agent)
    target_link_libraries(bongocat-ms-agent PRIVATE assets_bongocat_loader assets_bongocat assets_bongocat_feature assets_bongocat_interface)
    target_link_libraries(bongocat-ms-agent PRIVATE assets_ms_agent_loader assets_ms_agent assets_ms_agent_feature assets_ms_agent_interface)
    target_link_libraries(bongocat-ms-agent PRIVATE bongocat_base bongocat_options bongocat_libs)
endif()



# Install
include(GNUInstallDirs)
if (FEATURE_MULTI_VERSIONS)
    # sudo cmake --install ./cmake-build-release-all-assets-multi-lazy-load
    install(TARGETS bongocat bongocat-digimon bongocat-digimon-colored bongocat-digimon-colored-all bongocat-ms-agent COMPONENT bongocat-targets RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
else()
    install(TARGETS bongocat RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
endif()
install(FILES bongocat.conf DESTINATION ${CMAKE_INSTALL_DATADIR}/bongocat RENAME bongocat.conf.example)
install(PROGRAMS scripts/find_input_devices.sh DESTINATION ${CMAKE_INSTALL_BINDIR} RENAME bongocat-find-devices)

# Package
#set(CPACK_PACKAGE_NAME "bongocat")
#set(CPACK_PACKAGE_VERSION "2.2.0")
#set(CPACK_PACKAGE_CONTACT "hircreacc@gmail.com")
#set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "A delightful Wayland overlay that displays an animated V-Pet reacting to your keyboard input! ")
#set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/LICENSE")
#set(CPACK_GENERATOR "DEB;RPM")
#include(CPack)


# If MSVC is being used, and ASAN is enabled, we need to set the debugger environment so that it behaves well with MSVC's debugger, and we
# can run the target from visual studio
if(MSVC)
    get_all_installable_targets(all_targets)
    message("all_targets=${all_targets}")
    set_target_properties(${all_targets} PROPERTIES VS_DEBUGGER_ENVIRONMENT "PATH=$(VC_ExecutablePath_x64);%PATH%")
endif()
