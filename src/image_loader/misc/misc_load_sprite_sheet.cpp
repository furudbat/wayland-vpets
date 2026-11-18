#include "load_images_misc.h"
#include "misc_images.h"
#include "core/bongocat.h"
#include "embedded_assets/embedded_image.h"
#include "embedded_assets/misc/misc.hpp"
#include "embedded_assets/misc/misc_sprite.h"
#include "graphics/animation_thread_context.h"
#include "graphics/sprite_sheet.h"
#include "image_loader/custom/load_custom.h"

#include <cstdint>

namespace bongocat::animation {
      // same fields (and order) as assets::custom_animation_settings_t
#define BONGOCAT_CUSTOM_SETTINGS_FIELDS(X) \
      X(idle_frames) X(boring_frames) \
      X(start_writing_frames) X(writing_frames) X(end_writing_frames) X(happy_frames) \
      X(asleep_frames) X(sleep_frames) X(wake_up_frames) \
      X(start_working_frames) X(working_frames) X(end_working_frames) \
      X(start_moving_frames) X(moving_frames) X(end_moving_frames) \
      X(start_running_frames) X(running_frames) X(end_running_frames) \
      X(start_evolving_frames) X(evolving_frames) X(after_evolving_frames) \
      X(feature_toggle_writing_frames) X(feature_toggle_writing_frames_random) X(feature_mirror_x_moving) \
      X(idle_row_index) X(boring_row_index) \
      X(start_writing_row_index) X(writing_row_index) X(end_writing_row_index) X(happy_row_index) \
      X(asleep_row_index) X(sleep_row_index) X(wake_up_row_index) \
      X(start_working_row_index) X(working_row_index) X(end_working_row_index) \
      X(start_moving_row_index) X(moving_row_index) X(end_moving_row_index) \
      X(start_running_row_index) X(running_row_index) X(end_running_row_index) \
      X(start_evolving_row_index) X(evolving_row_index) X(after_evolving_row_index) \
      X(rows)

      struct compact_custom_animation_settings_t {
#define BONGOCAT_X(field) int8_t field;
          BONGOCAT_CUSTOM_SETTINGS_FIELDS(BONGOCAT_X)
#undef BONGOCAT_X
      };
#define BONGOCAT_X(field) +1
      static_assert(sizeof(assets::custom_animation_settings_t) == sizeof(int32_t) * (0 BONGOCAT_CUSTOM_SETTINGS_FIELDS(BONGOCAT_X)),
                    "custom_animation_settings_t changed, update BONGOCAT_CUSTOM_SETTINGS_FIELDS in generate_embedded_custom_assets.sh");
#undef BONGOCAT_X

      static constexpr int8_t compact_settings_value(int32_t value) {
          assert(value >= INT8_MIN && value <= INT8_MAX);
          return (value >= INT8_MIN && value <= INT8_MAX) ? static_cast<int8_t>(value)
                                                          : int8_t{0};
      }
      static constexpr compact_custom_animation_settings_t compact_settings(const assets::custom_animation_settings_t& settings) {
          compact_custom_animation_settings_t ret{};
#define BONGOCAT_X(field) ret.field = compact_settings_value(settings.field);
          BONGOCAT_CUSTOM_SETTINGS_FIELDS(BONGOCAT_X)
#undef BONGOCAT_X
          return ret;
      }
      static assets::custom_animation_settings_t expand_settings(const compact_custom_animation_settings_t& settings) {
          assets::custom_animation_settings_t ret;
#define BONGOCAT_X(field) ret.field = settings.field;
          BONGOCAT_CUSTOM_SETTINGS_FIELDS(BONGOCAT_X)
#undef BONGOCAT_X
          return ret;
      }
#undef BONGOCAT_CUSTOM_SETTINGS_FIELDS


static constexpr compact_custom_animation_settings_t misc_settings_table[] = {
  compact_settings(assets::MISC_NEKO_SPRITE_SHEET_SETTINGS),
};

static const unsigned char* const misc_pngs_table[] = {
  misc_neko_png,
};
static constexpr uint32_t misc_png_sizes_table[] = {
  misc_neko_png_size,
};
static const char* const misc_names_table[] = {
  "neko",
};

created_result_t<custom_sprite_sheet_t> load_misc_sprite_sheet(const animation_thread_context_t& ctx, size_t index) {
  using namespace assets;
  assert(LEN_ARRAY(misc_settings_table) == MISC_ANIM_COUNT);
  assert(LEN_ARRAY(misc_pngs_table) == MISC_ANIM_COUNT);
  assert(LEN_ARRAY(misc_png_sizes_table) == MISC_ANIM_COUNT);
  assert(LEN_ARRAY(misc_names_table) == MISC_ANIM_COUNT);
  assert(index < MISC_ANIM_COUNT);
  auto result = load_custom_anim(ctx, {misc_pngs_table[index], misc_png_sizes_table[index], misc_names_table[index]}, expand_settings(misc_settings_table[index]));
  return result;
}
void init_all_misc_anim(animation_thread_context_t& ctx) {
  using namespace assets;
  for (size_t i = 0;i < MISC_ANIM_COUNT;++i) {
    init_misc_anim(ctx, i, {misc_pngs_table[i], misc_png_sizes_table[i], misc_names_table[i]}, expand_settings(misc_settings_table[i]));
  }
}
}  // namespace bongocat::animation