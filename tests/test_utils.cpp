#include "config/config.h"
#include "core/bongocat.h"
#include "utils/error.h"
#include "utils/system_error.h"

#include <doctest/doctest.h>

TEST_CASE("has_flag") {
  using namespace bongocat;

  CHECK(has_flag(config::config_parsing_info_t::UnknownConfigKey, config::config_parsing_info_t::UnknownConfigKey));
  CHECK(!has_flag(config::config_parsing_info_t::Success, config::config_parsing_info_t::UnknownConfigKey));
}

TEST_CASE("has_flag - comb") {
  using namespace bongocat;

  const auto combined =
      flag_add(config::config_parsing_info_t::UnknownConfigKey, config::config_parsing_info_t::NoInputDevices);

  CHECK(has_flag(combined, config::config_parsing_info_t::UnknownConfigKey));
  CHECK(has_flag(combined, config::config_parsing_info_t::NoInputDevices));
  CHECK(!has_flag(combined, config::config_parsing_info_t::ConfigLineTooLong));
}

TEST_CASE("flag_remove") {
  using namespace bongocat;
  CHECK(flag_remove(bongocat::config::config_parsing_info_t::UnknownConfigKey,
                    config::config_parsing_info_t::UnknownConfigKey) == config::config_parsing_info_t::Success);
}

TEST_CASE("flag_remove - comb") {
  using namespace bongocat;

  const auto combined =
      flag_add(config::config_parsing_info_t::UnknownConfigKey, config::config_parsing_info_t::NoInputDevices);
  const auto after = flag_remove(combined, config::config_parsing_info_t::UnknownConfigKey);
  CHECK(!has_flag(after, config::config_parsing_info_t::UnknownConfigKey));
  CHECK(has_flag(after, config::config_parsing_info_t::NoInputDevices));
}

TEST_CASE("error string") {
  using namespace bongocat;
  CHECK(bongocat::get_strerror(1).c_str() != nullptr);
  BONGOCAT_LOG_VERBOSE("Test: Error string: %s", get_strerror(1).c_str());
}