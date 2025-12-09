add_library(assets_pen20_loader STATIC)
target_sources(assets_pen20_loader PRIVATE pen20_load_sprite_sheet.cpp load_images_pen20.cpp)
target_compile_options(assets_pen20_loader PRIVATE -ffunction-sections -fdata-sections)
target_include_directories(
  assets_pen20_loader
  PRIVATE ${INCLUDE_DIR}/embedded_assets/pen20 ${INCLUDE_DIR}/image_loader/pen20
  PUBLIC ${INCLUDE_DIR})
target_link_libraries(
  assets_pen20_loader
  PUBLIC assets_image_loader assets_base_dm_loader assets_pen20
  PRIVATE assets_pen20_interface assets_pen20_feature bongocat_options)
