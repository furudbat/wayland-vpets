#include "config/config.h"
#include "core/bongocat.h"
#include "graphics/animation.h"

#include <doctest/doctest.h>

TEST_CASE("scale_size_120") {
  using namespace bongocat::animation::details;

  CHECK(scale_size_120({100, 120}) == 100);
  CHECK(scale_size_120({100, 144}) == 120);
  CHECK(scale_size_120({100, 180}) == 150);
  CHECK(scale_size_120({100, 240}) == 200);
}

TEST_CASE("scale_offset_120") {
  using namespace bongocat::animation::details;

  CHECK(scale_offset_120({-10, 180}) == -15);
}

TEST_CASE("output_logical_size") {
  using namespace bongocat::animation::details;

  SUBCASE("scale 2") {
    const auto [width, height] = output_logical_size({2560, 1600}, 0, 2, {0, 0});

    CHECK(width == 1280);
    CHECK(height == 800);
  }
  SUBCASE("transform 1") {
    const auto [width, height] = output_logical_size({2560, 1600}, 1, 2, {0, 0});

    CHECK(width == 800);
    CHECK(height == 1280);
  }
  SUBCASE("xdg") {
    const auto [width, height] = output_logical_size({3840, 2160}, 0, 2, {1920, 1080});

    CHECK(width == 1920);
    CHECK(height == 1080);
  }
  SUBCASE("scale 1") {
    const auto [width, height] = output_logical_size({1920, 1080}, 0, 1, {0, 0});

    CHECK(width == 1920);
    CHECK(height == 1080);
  }
}