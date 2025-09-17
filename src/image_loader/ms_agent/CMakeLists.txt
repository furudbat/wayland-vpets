add_library(assets_ms_agent_loader STATIC)
target_sources(assets_ms_agent_loader PRIVATE load_images_ms_agent.cpp)
target_compile_options(assets_ms_agent_loader PRIVATE -ffunction-sections -fdata-sections)
target_include_directories(assets_ms_agent_loader
        PRIVATE ${INCLUDE_DIR}/embedded_assets/ms_agent ${INCLUDE_DIR}/image_loader/ms_agent
        PUBLIC ${INCLUDE_DIR})
target_link_libraries(assets_ms_agent_loader
        PUBLIC assets_image_loader assets_ms_agent
        PRIVATE assets_ms_agent_interface assets_ms_agent_feature bongocat_options)



add_library(assets_more_ms_agent_loader STATIC)
target_sources(assets_more_ms_agent_loader PRIVATE load_images_ms_agent.cpp)
target_compile_options(assets_more_ms_agent_loader PRIVATE -ffunction-sections -fdata-sections)
target_include_directories(assets_more_ms_agent_loader
        PRIVATE ${INCLUDE_DIR}/embedded_assets/ms_agent ${INCLUDE_DIR}/image_loader/ms_agent
        PUBLIC ${INCLUDE_DIR})
target_link_libraries(assets_more_ms_agent_loader
        PUBLIC assets_image_loader assets_more_ms_agent
        PRIVATE assets_more_ms_agent_interface assets_more_ms_agent_feature bongocat_options)