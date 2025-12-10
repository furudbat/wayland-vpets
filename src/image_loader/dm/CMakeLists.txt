add_library(assets_dm_loader STATIC)
target_sources(assets_dm_loader PRIVATE dm_load_sprite_sheet.cpp load_images_dm.cpp)
target_compile_options(assets_dm_loader PRIVATE -ffunction-sections -fdata-sections)
target_include_directories(
  assets_dm_loader
  PRIVATE ${INCLUDE_DIR}/embedded_assets/dm ${INCLUDE_DIR}/image_loader/dm
  PUBLIC ${INCLUDE_DIR})
target_link_libraries(
  assets_dm_loader
  PUBLIC assets_image_loader assets_base_dm_loader assets_dm
  PRIVATE assets_dm_interface assets_dm_feature bongocat_options)
