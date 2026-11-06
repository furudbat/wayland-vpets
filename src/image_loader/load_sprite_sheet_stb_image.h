#ifndef BONGOCAT_LOAD_SPRITE_SHEET_STB_IMAGE_H
#define BONGOCAT_LOAD_SPRITE_SHEET_STB_IMAGE_H

// Private header (src/image_loader): include AFTER "stb_image.h".
// stb_image always decodes the whole image into its own buffer, so the layout is applied with one memcpy per frame
// row straight from that buffer (no extra intermediate copy like load_image()).

#include "image_loader/load_images.h"

#include <climits>
#include <cstdint>

namespace bongocat::animation::details {
BONGOCAT_NODISCARD inline created_result_t<generic_sprite_sheet_image_t>
load_sprite_sheet_image_stb_image(const unsigned char *data, size_t size, sprite_sheet_layout_t layout) {
  if (size > INT_MAX) [[unlikely]] {
    return bongocat_error_t::BONGOCAT_ERROR_INVALID_PARAM;
  }
  int width{0};
  int height{0};
  int channels_in_file{0};
  unsigned char *stbi_pixels =
      stbi_load_from_memory(data, static_cast<int>(size), &width, &height, &channels_in_file, RGBA_CHANNELS);
  if (stbi_pixels == BONGOCAT_NULLPTR) [[unlikely]] {
    return bongocat_error_t::BONGOCAT_ERROR_IMAGE;
  }

  const sprite_sheet_layout_mapper_t mapper = make_sprite_sheet_layout_mapper(width, height, layout);
  auto [image, error] = allocate_sprite_sheet_image(mapper);
  if (error != bongocat_error_t::BONGOCAT_SUCCESS) [[unlikely]] {
    stbi_image_free(stbi_pixels);
    return error;
  }
  copy_rgba_into_sprite_sheet_layout(image, mapper, stbi_pixels);
  stbi_image_free(stbi_pixels);
  return bongocat::move(image);
}
}  // namespace bongocat::animation::details

#endif  // BONGOCAT_LOAD_SPRITE_SHEET_STB_IMAGE_H
