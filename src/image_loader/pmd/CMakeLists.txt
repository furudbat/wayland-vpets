add_library(assets_pmd_loader STATIC)
target_sources(assets_pmd_loader PRIVATE load_images_pmd.cpp pmd_load_sprite_sheet.cpp)
target_compile_options(assets_pmd_loader PRIVATE -ffunction-sections -fdata-sections)
target_include_directories(
  assets_pmd_loader
  PRIVATE ${INCLUDE_DIR}/embedded_assets/misc ${INCLUDE_DIR}/image_loader/pmd
  PUBLIC ${INCLUDE_DIR})
target_link_libraries(
  assets_pmd_loader
  PUBLIC assets_image_loader assets_custom_loader assets_pmd
  PRIVATE assets_pmd_interface assets_pmd_feature bongocat_options)
