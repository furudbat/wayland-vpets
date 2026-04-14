#include "embedded_assets/bongocat/bongocat.h"
#include "embedded_assets/bongocat/bongocat_images.h"
#include "embedded_assets/embedded_image.h"

namespace bongocat::assets {
embedded_image_t get_bongocat_sprite_svg(size_t i) {
  using namespace assets;
  switch (i) {
  case BONGOCAT_FRAME_BOTH_UP:
    return {bongo_cat_both_up_svg, bongo_cat_both_up_svg_size, "bongo-cat-both-up"};
  case BONGOCAT_FRAME_LEFT_DOWN:
    return {bongo_cat_left_down_svg, bongo_cat_left_down_svg_size, "bongo-cat-left-down"};
  case BONGOCAT_FRAME_RIGHT_DOWN:
    return {bongo_cat_right_down_svg, bongo_cat_right_down_svg_size, "bongo-cat-right-down"};
  case BONGOCAT_FRAME_BOTH_DOWN:
    return {bongo_cat_both_down_svg, bongo_cat_both_down_svg_size, "bongo-cat-both-down"};
  case BONGOCAT_FRAME_SLEEPING:
    return {bongo_cat_sleeping_svg, bongo_cat_sleeping_svg_size, "bongo-cat-sleeping"};
  default:
    return {};
  }
  return {};
}
}  // namespace bongocat::assets