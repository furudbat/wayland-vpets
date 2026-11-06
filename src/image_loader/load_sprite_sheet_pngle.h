#ifndef BONGOCAT_LOAD_SPRITE_SHEET_PNGLE_H
#define BONGOCAT_LOAD_SPRITE_SHEET_PNGLE_H

// Private header (src/image_loader): include AFTER "pngle.h".
// Streams the PNG through pngle and writes every pixel straight to its final place in the padded sprite sheet:
// RAM while decoding = final sprite sheet + pngle state (inflate window + 2 scanlines), no intermediate image.

#include "image_loader/load_images.h"

#include <cassert>
#include <cstdint>
#include <cstring>

namespace bongocat::animation::details {
struct pngle_sprite_sheet_state_t {
  sprite_sheet_layout_t layout;
  sprite_sheet_layout_mapper_t mapper;
  generic_sprite_sheet_image_t *image{BONGOCAT_NULLPTR};
  bongocat_error_t error{bongocat_error_t::BONGOCAT_SUCCESS};

  // per-row cache, pixels arrive row by row with increasing x (also for every interlace pass)
  uint32_t row_y{UINT32_MAX};
  uint8_t *dest_row{BONGOCAT_NULLPTR};
  uint32_t col_begin_x{0};
  uint32_t col_end_x{0};
  uint32_t col_offset_x{0};  ///< added padding in front of the current frame column
};

inline void pngle_sprite_sheet_reset_column(pngle_sprite_sheet_state_t& st) {
  st.col_begin_x = 0;
  st.col_end_x = static_cast<uint32_t>(st.mapper.frame_width);
  st.col_offset_x = static_cast<uint32_t>(st.mapper.padding_x);
}

BONGOCAT_NODISCARD inline created_result_t<generic_sprite_sheet_image_t>
load_sprite_sheet_image_pngle(const unsigned char *data, size_t size, sprite_sheet_layout_t layout) {
  generic_sprite_sheet_image_t ret;
  pngle_sprite_sheet_state_t state;
  state.layout = layout;
  state.image = &ret;

  pngle_t *pngle = pngle_new();
  if (pngle == BONGOCAT_NULLPTR) [[unlikely]] {
    return bongocat_error_t::BONGOCAT_ERROR_MEMORY;
  }
  pngle_set_user_data(pngle, &state);

  // header parsed: validate grid + allocate the FINAL buffer once
  pngle_set_init_callback(pngle, [](pngle_t *p_pngle, uint32_t w, uint32_t h) {
    auto *st = static_cast<pngle_sprite_sheet_state_t *>(pngle_get_user_data(p_pngle));
    if (w > INT32_MAX || h > INT32_MAX) [[unlikely]] {
      st->error = bongocat_error_t::BONGOCAT_ERROR_IMAGE;
      return;
    }
    st->mapper = make_sprite_sheet_layout_mapper(static_cast<int32_t>(w), static_cast<int32_t>(h), st->layout);
    if (!st->mapper.valid) [[unlikely]] {
      st->error = bongocat_error_t::BONGOCAT_ERROR_INVALID_PARAM;
      return;
    }
    auto [image, error] = allocate_sprite_sheet_image(st->mapper);
    if (error != bongocat_error_t::BONGOCAT_SUCCESS) [[unlikely]] {
      st->error = error;
      return;
    }
    *st->image = bongocat::move(image);
    pngle_sprite_sheet_reset_column(*st);
  });

  // every pixel: write RGBA directly into the padded layout (no division per pixel, only per row/frame column)
  pngle_set_draw_callback(pngle, [](pngle_t *p_pngle, uint32_t x, uint32_t y, [[maybe_unused]] uint32_t w,
                                    [[maybe_unused]] uint32_t h, const uint8_t rgba[4]) {
    auto *st = static_cast<pngle_sprite_sheet_state_t *>(pngle_get_user_data(p_pngle));
    if (st->error != bongocat_error_t::BONGOCAT_SUCCESS || st->image->pixels.data == BONGOCAT_NULLPTR) [[unlikely]] {
      return;
    }
    if (x >= static_cast<uint32_t>(st->mapper.src_width) || y >= static_cast<uint32_t>(st->mapper.src_height))
        [[unlikely]] {
      return;
    }
    if (y != st->row_y) {
      st->row_y = y;
      st->dest_row = st->image->pixels.data + (static_cast<size_t>(st->mapper.dest_y(static_cast<int32_t>(y))) *
                                               static_cast<size_t>(st->mapper.dest_width) * RGBA_CHANNELS);
      pngle_sprite_sheet_reset_column(*st);
    } else if (x < st->col_begin_x) [[unlikely]] {
      pngle_sprite_sheet_reset_column(*st);
    }
    while (x >= st->col_end_x) {
      st->col_begin_x = st->col_end_x;
      st->col_end_x += static_cast<uint32_t>(st->mapper.frame_width);
      st->col_offset_x += static_cast<uint32_t>(st->mapper.padding_x) * 2;
    }
    ::memcpy(st->dest_row + (static_cast<size_t>(x + st->col_offset_x) * RGBA_CHANNELS), rgba, RGBA_CHANNELS);
  });

  const int fed = pngle_feed(pngle, data, size);
  pngle_destroy(pngle);
  pngle = BONGOCAT_NULLPTR;

  if (state.error != bongocat_error_t::BONGOCAT_SUCCESS) [[unlikely]] {
    return state.error;
  }
  if (fed < 0 || ret.pixels.data == BONGOCAT_NULLPTR) [[unlikely]] {
    return bongocat_error_t::BONGOCAT_ERROR_IMAGE;
  }
  return ret;
}
}  // namespace bongocat::animation::details

#endif  // BONGOCAT_LOAD_SPRITE_SHEET_PNGLE_H
