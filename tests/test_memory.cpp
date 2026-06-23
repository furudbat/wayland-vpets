#include "config/config.h"
#include "core/bongocat.h"
#include "utils/error.h"
#include "utils/system_error.h"

#include <doctest/doctest.h>

TEST_CASE("malloc_free") {
  using namespace bongocat;

  void *p = bongocat::malloc(256);
  CHECK(p != nullptr);
  bongocat::free(p);
}

TEST_CASE("malloc_free zero") {
  using namespace bongocat;

  void *z = bongocat::malloc(0);
  if (z) {
    bongocat::free(z);
  }
}