add_library(assets_dm20_loader STATIC)
target_sources(assets_dm20_loader PRIVATE dm20_load_sprite_sheet.cpp load_images_dm20.cpp)
target_compile_options(assets_dm20_loader PRIVATE -ffunction-sections -fdata-sections)
target_include_directories(
  assets_dm20_loader
  PRIVATE ${INCLUDE_DIR}/embedded_assets/dm20 ${INCLUDE_DIR}/image_loader/dm20
  PUBLIC ${INCLUDE_DIR})
target_link_libraries(
  assets_dm20_loader
  PUBLIC assets_image_loader assets_base_dm_loader assets_dm20
  PRIVATE assets_dm20_interface assets_dm20_feature bongocat_options)
