# MS Agent
add_library(assets_ms_agent_interface INTERFACE)

add_library(assets_ms_agent_feature INTERFACE)
target_compile_definitions(assets_ms_agent_feature INTERFACE FEATURE_MS_AGENT_EMBEDDED_ASSETS)

add_library(assets_ms_agent STATIC)
target_sources(assets_ms_agent PRIVATE embedded_assets_ms_agent.cpp ms_agent_images.c)
target_compile_options(assets_ms_agent PRIVATE -ffunction-sections -fdata-sections)
target_include_directories(assets_ms_agent
        PRIVATE ${INCLUDE_DIR}/embedded_assets/ms_agent
        PUBLIC ${INCLUDE_DIR})
target_link_libraries(assets_ms_agent
        PUBLIC assets_ms_agent_interface
        PRIVATE assets_ms_agent_feature bongocat_options)


# More MS Agents
add_library(assets_more_ms_agent_interface INTERFACE)

add_library(assets_more_ms_agent_feature INTERFACE)
target_compile_definitions(assets_more_ms_agent_feature INTERFACE FEATURE_MS_AGENT_EMBEDDED_ASSETS)
target_compile_definitions(assets_more_ms_agent_feature INTERFACE FEATURE_MORE_MS_AGENT_EMBEDDED_ASSETS)

add_library(assets_more_ms_agent STATIC)
target_sources(assets_more_ms_agent PRIVATE embedded_assets_ms_agent.cpp ms_agent_images.c)
target_compile_options(assets_more_ms_agent PRIVATE -ffunction-sections -fdata-sections)
target_include_directories(assets_more_ms_agent
        PRIVATE ${INCLUDE_DIR}/embedded_assets/ms_agent
        PUBLIC ${INCLUDE_DIR})
target_link_libraries(assets_more_ms_agent
        PUBLIC assets_more_ms_agent_interface
        PRIVATE assets_more_ms_agent_feature bongocat_options)
