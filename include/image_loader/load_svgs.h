#ifndef BONGOCAT_EMBEDDED_LOAD_SVGS_H
#define BONGOCAT_EMBEDDED_LOAD_SVGS_H

#include "load_images.h"
#include "config/config.h"
#include "core/bongocat.h"
#include "embedded_assets/embedded_image.h"
#include "graphics/sprite_sheet.h"
#include "utils/memory.h"
#ifdef FEATURE_USE_RASTER_IMAGE_LOADER
#include "load_images.h"
#include <nanosvgrast.h>
#endif
#include <nanosvg.h>
#include <cstdlib>

namespace bongocat::animation {
// =============================================================================
// SVG LOADING MODULE
// =============================================================================

constexpr static inline const char* SVG_UNITS = "px";
constexpr static inline float SVG_DPI = 96.0;

class SvgImage;
BONGOCAT_NODISCARD created_result_t<SvgImage> load_svg(char *data, const char* units, float dpi);
void cleanup_svg(SvgImage& image);
void init_svg_loader();

#ifdef FEATURE_USE_RASTER_IMAGE_LOADER
class SvgRasterImage;
void cleanup_svg_raster(SvgRasterImage& image);
BONGOCAT_NODISCARD created_result_t<SvgRasterImage> create_svg_rasterizer();

struct LoadSvgImageParams {
  float tx;
  float ty;
  float scale;
  int w;
  int h;
  int alpha_threshold;
};
BONGOCAT_NODISCARD created_result_t<Image> load_svg_image(SvgImage& svg, LoadSvgImageParams params);
#endif

class SvgImage {
public:
	NSVGimage *image{BONGOCAT_NULLPTR};
  AllocatedString _units;
  float _dpi;

  SvgImage() = default;
  ~SvgImage() {
    cleanup_svg(*this);
  }

  /// @TODO: ctor svg image
  SvgImage(const SvgImage& other) = delete;
  SvgImage& operator=(const SvgImage& other) = delete;

  SvgImage(SvgImage&& other) noexcept
      : image(other.image), _units(bongocat::move(other._units)), _dpi(other._dpi) {
    other.image = BONGOCAT_NULLPTR;
    other._units = BONGOCAT_NULLPTR;
    other._dpi = 0;
  }
  SvgImage& operator=(SvgImage&& other) noexcept {
    if (this == &other) {
      return *this;
    }

    cleanup_svg(*this);

    image = other.image;
    _units = other._units;
    _dpi = other._dpi;

    other.image = BONGOCAT_NULLPTR;
    other._units = BONGOCAT_NULLPTR;
    other._dpi = 0;

    return *this;
  }
};

#ifdef FEATURE_USE_RASTER_IMAGE_LOADER
class SvgRasterImage {
public:
  NSVGrasterizer *image{BONGOCAT_NULLPTR};

  SvgRasterImage() {
    image = nsvgCreateRasterizer();
  }
  ~SvgRasterImage() {
    cleanup_svg_raster(*this);
  }

  /// @TODO: ctor svg image
  SvgRasterImage(const SvgRasterImage& other) = delete;
  SvgRasterImage& operator=(const SvgRasterImage& other) = delete;

  SvgRasterImage(SvgRasterImage&& other) noexcept
      : image(other.image) {
    other.image = BONGOCAT_NULLPTR;
  }
  SvgRasterImage& operator=(SvgRasterImage&& other) noexcept {
    if (this == &other) {
      return *this;
    }

    cleanup_svg_raster(*this);

    image = other.image;

    other.image = BONGOCAT_NULLPTR;

    return *this;
  }
};

struct anim_sprite_sheet_from_embedded_svgs_t {
  int target_w;
  int target_h;
  float tx{0.0f};
  float ty{0.0f};
  int alpha_threshold{0};
};
BONGOCAT_NODISCARD created_result_t<generic_sprite_sheet_t>
anim_sprite_sheet_from_embedded_svgs(get_sprite_callback_t get_sprite, size_t embedded_images_count, anim_sprite_sheet_from_embedded_svgs_t svg_params);

#endif

}  // namespace bongocat::animation

#endif