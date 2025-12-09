#pragma once

#include "core/bongocat.h"
#include "embedded_assets/custom/custom_sprite.h"
#include "embedded_assets/embedded_image.h"
#include "graphics/sprite_sheet.h"
#include "utils/system_memory.h"

namespace bongocat::assets {
struct custom_image_t;
}
namespace bongocat::animation {
void free_custom_sprite_sheet_file(assets::custom_image_t& image) noexcept;
}

namespace bongocat::assets {
struct custom_image_t {
  platform::MMapFileContent data;
  char *name{BONGOCAT_NULLPTR};

  custom_image_t() = default;
  custom_image_t(const custom_image_t& other) = delete;
  custom_image_t(custom_image_t&& other) noexcept : data(bongocat::move(other.data)), name(other.name) {
    other.name = BONGOCAT_NULLPTR;
  }
  ~custom_image_t() {
    animation::free_custom_sprite_sheet_file(*this);
  }

  custom_image_t& operator=(const custom_image_t& other) = delete;
  custom_image_t& operator=(custom_image_t&& other) noexcept {
    if (this != &other) {
      animation::free_custom_sprite_sheet_file(*this);

      data = bongocat::move(other.data);

      if (name != BONGOCAT_NULLPTR) {
        ::free(name);
        name = BONGOCAT_NULLPTR;
      }
      name = other.name;

      other.name = BONGOCAT_NULLPTR;
    }
    return *this;
  }
};
}  // namespace bongocat::assets

namespace bongocat::animation {
struct animation_context_t;
BONGOCAT_NODISCARD created_result_t<assets::custom_image_t> load_custom_sprite_sheet_file(const char *filename);

BONGOCAT_NODISCARD created_result_t<custom_sprite_sheet_t>
load_custom_anim(const animation_context_t& ctx, const assets::custom_image_t& sprite_sheet_image,
                 const assets::custom_animation_settings_t& sprite_sheet_settings);

BONGOCAT_NODISCARD created_result_t<custom_sprite_sheet_t>
load_custom_anim(const animation_context_t& ctx, const assets::embedded_image_t& sprite_sheet_image,
                 const assets::custom_animation_settings_t& sprite_sheet_settings);
}  // namespace bongocat::animation
