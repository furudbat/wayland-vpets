add_library(assets_pen_loader STATIC)
target_sources(assets_pen_loader PRIVATE pen_load_sprite_sheet.cpp load_images_pen.cpp)
target_compile_options(assets_pen_loader PRIVATE -ffunction-sections -fdata-sections)
target_include_directories(
  assets_pen_loader
  PRIVATE ${INCLUDE_DIR}/embedded_assets/pen ${INCLUDE_DIR}/image_loader/pen
  PUBLIC ${INCLUDE_DIR})
target_link_libraries(
  assets_pen_loader
  PUBLIC assets_image_loader assets_base_dm_loader assets_pen
  PRIVATE assets_pen_interface assets_pen_feature bongocat_options)
