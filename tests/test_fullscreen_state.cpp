#include "config/config.h"
#include "core/bongocat.h"
#include "platform/wayland_callbacks.h"

#include <doctest/doctest.h>

TEST_CASE("fullscreen_toplevel_relevant") {
  using namespace bongocat::platform::wayland::details;

  CHECK(fullscreen_toplevel_relevant({.has_output_events = true, .is_on_output = true, .is_activated = true}));
  CHECK(!fullscreen_toplevel_relevant({.has_output_events = true, .is_on_output = true, .is_activated = false}));
  CHECK(!fullscreen_toplevel_relevant({.has_output_events = true, .is_on_output = false, .is_activated = true}));
  CHECK(fullscreen_toplevel_relevant({.has_output_events = false, .is_on_output = false, .is_activated = true}));
  CHECK(!fullscreen_toplevel_relevant({.has_output_events = false, .is_on_output = false, .is_activated = false}));
}