add_library(assets_dmx_loader STATIC)
target_sources(assets_dmx_loader PRIVATE dmx_load_sprite_sheet.cpp load_images_dmx.cpp)
target_compile_options(assets_dmx_loader PRIVATE -ffunction-sections -fdata-sections)
target_include_directories(
  assets_dmx_loader
  PRIVATE ${INCLUDE_DIR}/embedded_assets/dmx ${INCLUDE_DIR}/image_loader/dmx
  PUBLIC ${INCLUDE_DIR})
target_link_libraries(
  assets_dmx_loader
  PUBLIC assets_image_loader assets_base_dm_loader assets_dmx
  PRIVATE assets_dmx_interface assets_dmx_feature bongocat_options)
