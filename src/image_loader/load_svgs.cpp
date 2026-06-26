#include "image_loader/load_svgs.h"
#include "image_loader/load_images.h"
#include "graphics/animation.h"
#include "graphics/drawing.h"
#include "utils/memory.h"
#include <cassert>
#include <cstddef>
#include <cstring>
#include <cstdint>

#include <nanosvg.h>
#include <nanosvgrast.h>

namespace bongocat::animation {
// =============================================================================
// SVG LOADING MODULE
// =============================================================================

constexpr static inline const char* SVG_UNITS = "px";
constexpr static inline float SVG_DPI = 96.0;

void init_svg_loader() {}

void cleanup_svg(SvgImage& image) {
  nsvgDelete(image.image);
  image.image = BONGOCAT_NULLPTR;
  image._units = BONGOCAT_NULLPTR;
  image._dpi = 0;
}

created_result_t<SvgImage> load_svg(char *data, const char* units, float dpi) {
  SvgImage ret;
  ret.image = ::nsvgParse(data, units, dpi);
  if (ret.image != BONGOCAT_NULLPTR) {
    ret._units = duplicate_string(units);
    ret._dpi = dpi;

    return ret;
  }

  return bongocat_error_t::BONGOCAT_ERROR_SVG;
}

#ifdef FEATURE_USE_RASTER_IMAGE_LOADER
void cleanup_svg_raster(SvgRasterImage& image) {
  nsvgDeleteRasterizer(image.image);
  image.image = BONGOCAT_NULLPTR;
}

BONGOCAT_NODISCARD created_result_t<SvgRasterImage> create_svg_rasterizer() {
  SvgRasterImage ret;
  if (ret.image == BONGOCAT_NULLPTR) [[unlikely]] {
    return bongocat_error_t::BONGOCAT_ERROR_SVG;
  }

  return ret;
}


created_result_t<Image> load_svg_image(SvgImage& svg, LoadSvgImageParams params) {
  BONGOCAT_CHECK_ERROR(params.w < 0, bongocat_error_t::BONGOCAT_ERROR_SVG, "svg image width can not be zero nor negative");
  BONGOCAT_CHECK_ERROR(params.h < 0, bongocat_error_t::BONGOCAT_ERROR_SVG, "svg image height can not be zero nor negative");

  auto [image, image_error] = make_image(params.w, params.h, RGBA_CHANNELS);
  if (image_error != bongocat_error_t::BONGOCAT_SUCCESS) [[unlikely]] {
    return image_error;
  }

  auto [svg_raster, svg_raster_error] = create_svg_rasterizer();
  if (svg_raster_error != bongocat_error_t::BONGOCAT_SUCCESS) [[unlikely]] {
    return svg_raster_error;
  }
  assert(svg_raster.image != BONGOCAT_NULLPTR);
  //assert(image.width >= 0);
  //assert(image.height >= 0);
  //assert(image.channels >= 0);
  //::memset(image.pixels, 0, static_cast<size_t>(image.width) * static_cast<size_t>(image.height) * static_cast<size_t>(image.channels));
  ::nsvgRasterizeA(svg_raster.image, svg.image, params.tx, params.ty, params.scale, image.pixels.data, params.w, params.h, image.width * image.channels, params.alpha_mask);

  return bongocat::move(image);
}

created_result_t<generic_sprite_sheet_t> anim_sprite_sheet_from_embedded_svgs(get_sprite_callback_t get_sprite,
                                                                              size_t embedded_images_count,
                                                                              anim_sprite_sheet_from_embedded_svgs_t svg_params,
                                                                              anim_sprite_sheet_from_embedded_svgs_cropping_t cropping) {
  generic_sprite_sheet_t ret;

  int total_frames = 0;
  int max_frame_width = 0;
  int max_frame_height = 0;
  int max_channels = 0;
  auto loaded_images = make_allocated_array<Image>(embedded_images_count);
  for (size_t i = 0; i < embedded_images_count && i < loaded_images.count; i++) {
    const assets::embedded_image_t img = get_sprite(i);
    AllocatedString svg_data = duplicate_string(reinterpret_cast<const char*>(img.data), img.size);

    BONGOCAT_LOG_DEBUG("Loading embedded svg: %s", img.name);
    auto [loaded_svg, svg_error] = load_svg(svg_data.ptr, SVG_UNITS, SVG_DPI);
    if (svg_error != bongocat_error_t::BONGOCAT_SUCCESS) [[unlikely]] {
      BONGOCAT_LOG_ERROR("Failed to load embedded svg: %s (%d)", img.name, svg_error);
      continue;
    }
    bongocat::release_allocated_string(svg_data);
    svg_data = BONGOCAT_NULLPTR;
    assert(loaded_svg.image != nullptr);
    const float svg_w = loaded_svg.image->width;
    const float svg_h = loaded_svg.image->height;
    if (svg_w <= 0.0f || svg_h <= 0.0f) [[unlikely]] {
      BONGOCAT_LOG_ERROR("Failed to load embedded svg: width/height can not be zero (%fx%f)", static_cast<double>(svg_w), static_cast<double>(svg_h));
      continue;
    }

    assert(svg_w > 0);
    assert(svg_h > 0);
    const float scale = static_cast<float>(svg_params.target_w) / svg_w;
    auto [loaded_image, image_error] = load_svg_image(loaded_svg, {
      .tx = svg_params.tx,
      .ty = svg_params.ty,
      .scale = scale,
      .w = svg_params.target_w,
      .h = svg_params.target_h,
      .alpha_mask = svg_params.alpha_mask,
    });
    if (image_error != bongocat_error_t::BONGOCAT_SUCCESS) [[unlikely]] {
      BONGOCAT_LOG_ERROR("Failed to load embedded svg: %s (%d)", img.name, image_error);
      continue;
    }
    loaded_images[i] = bongocat::move(loaded_image);
    assert(loaded_images[i].width >= 0);
    assert(loaded_images[i].height >= 0);
    assert(loaded_images[i].channels >= 0);

    // update image properties
    max_frame_width = loaded_images[i].width > max_frame_width ? loaded_images[i].width : max_frame_width;
    max_frame_height = loaded_images[i].height > max_frame_height ? loaded_images[i].height : max_frame_height;
    max_channels = loaded_images[i].channels > max_channels ? loaded_images[i].channels : max_channels;

    BONGOCAT_LOG_DEBUG("Loaded %dx%d embedded svg", loaded_images[i].width, loaded_images[i].height);
    total_frames++;
  }

  // prepare sprite sheet size
  int cropped_w = max_frame_width - cropping.left - cropping.right;
  int cropped_h = max_frame_height - cropping.top - cropping.bottom;
  if (cropped_w < 0) cropped_w = 0;
  if (cropped_h < 0) cropped_h = 0;
  max_frame_width  = cropped_w;
  max_frame_height = cropped_h;
  assert(max_frame_width >= 0);
  assert(max_frame_height >= 0);
  ret.frame_width = max_frame_width;
  ret.frame_height = max_frame_height;
  ret.total_frames = total_frames;
  ret.image.sprite_sheet_width = max_frame_width * total_frames;
  ret.image.sprite_sheet_height = max_frame_height;
  ret.image.channels = max_channels;
  // create sprite sheet
  assert(ret.image.sprite_sheet_width >= 0);
  assert(ret.image.sprite_sheet_height >= 0);
  assert(ret.image.channels >= 0);
  if (ret.image.sprite_sheet_width == 0 || ret.image.sprite_sheet_height == 0 || ret.image.channels == 0) {
    ret.frame_width = 0;
    ret.frame_height = 0;
    ret.total_frames = 0;
    ret.image.sprite_sheet_width = 0;
    ret.image.sprite_sheet_height = 0;
    ret.image.channels = 0;

    return bongocat_error_t::BONGOCAT_ERROR_SVG;
  }

  ret.image.pixels = make_allocated_array<uint8_t>(static_cast<size_t>(ret.image.sprite_sheet_width) *
                                                   static_cast<size_t>(ret.image.sprite_sheet_height) *
                                                   static_cast<size_t>(ret.image.channels));
  if (!ret.image.pixels) {
    ret.frame_width = 0;
    ret.frame_height = 0;
    ret.total_frames = 0;
    ret.image.sprite_sheet_width = 0;
    ret.image.sprite_sheet_height = 0;
    ret.image.channels = 0;

    return bongocat_error_t::BONGOCAT_ERROR_MEMORY;
  }

  // reset frames
  ::memset(ret.image.pixels.data, 0, ret.image.pixels._size_bytes);
  for (size_t i = 0; i < MAX_NUM_FRAMES; i++) {
    ret.frames[i] = {};
  }

  // append images into one sprite sheet
  assert(max_frame_width >= 0);
  assert(max_channels >= 0);
  assert(ret.image.sprite_sheet_width >= 0);
  for (size_t frame = 0; frame < loaded_images.count; frame++) {
    const auto& src = loaded_images[frame];

    if (src.pixels != BONGOCAT_NULLPTR && src.height > 0) {
      const int s_cropped_w = src.width  - cropping.left - cropping.right;
      const int s_cropped_h = src.height - cropping.top  - cropping.bottom;
      if (s_cropped_w <= 0 || s_cropped_h <= 0) {
        continue;
      }

      int dy = 0;
      int end_y = cropping.top + s_cropped_h;
      if (end_y > src.height) end_y = src.height;
      for (int y = cropping.top; y < end_y; y++) {
        assert(dy >= 0);
        unsigned char* dest_row =
            ret.image.pixels.data +
            (((static_cast<size_t>(dy) * static_cast<size_t>(ret.image.sprite_sheet_width)) +
              (frame * static_cast<size_t>(max_frame_width))) *
             static_cast<size_t>(max_channels));

        if (y < src.height) {
          const unsigned char* src_row =
              src.pixels.data +
              static_cast<ptrdiff_t>(((y * src.width) + cropping.left) * src.channels);

          assert(ret.image.sprite_sheet_height >= 0);
          if (dy < ret.image.sprite_sheet_height) {
            assert(s_cropped_w >= 0);
            int line_w = s_cropped_w;
            if (line_w >= max_frame_width) line_w = max_frame_width;
            if (line_w >= src.width) line_w = src.width;
            if (line_w >= ret.image.sprite_sheet_width) line_w = ret.image.sprite_sheet_width;

            assert(max_channels == src.channels);
            assert(max_channels == ret.image.channels);
            ::memcpy(dest_row,
                     src_row,
                     static_cast<size_t>(line_w) * static_cast<size_t>(max_channels));
          }
        }

        dy++;
      }

      if (frame < MAX_NUM_FRAMES) {
        ret.frames[frame] = {
          .valid = true,
          .col = static_cast<int>(frame),
          .row = 0
        };
      }
    } else {
      if (frame < MAX_NUM_FRAMES) {
        ret.frames[frame] = {
          .valid = false,
          .col = static_cast<int>(frame),
          .row = 0
        };
      }
    }
  }

  return ret;
}

#endif

}  // namespace bongocat::animation