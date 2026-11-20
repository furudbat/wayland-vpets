#include "config/config.h"
#include "dm20_config_parse_animation_name.h"
#include "dm_config_parse_animation_name.h"
#include "dmall_config_parse_animation_name.h"
#include "dmc_config_parse_animation_name.h"
#include "dmx_config_parse_animation_name.h"
#include "embedded_assets/dm/dm.hpp"
#include "embedded_assets/dm20/dm20.hpp"
#include "embedded_assets/dmall/dmall.hpp"
#include "embedded_assets/dmc/dmc.hpp"
#include "embedded_assets/dmx/dmx.hpp"
#include "embedded_assets/pen/pen.hpp"
#include "embedded_assets/pen20/pen20.hpp"
#include "embedded_assets/pkmn/pkmn.hpp"
#include "embedded_assets/pmd/pmd.hpp"
#include "pen20_config_parse_animation_name.h"
#include "pen_config_parse_animation_name.h"
#include "pkmn_config_parse_animation_name.h"
#include "pmd_config_parse_animation_name.h"

#include <doctest.h>
#include <string>

namespace {

template <typename GetFn, typename ParseFn>
void check_animation_names(const std::string& set, const char *alt_set, size_t count, GetFn get, ParseFn parse) {
  using namespace bongocat;
  CAPTURE(set);
  CHECK(count > 0);
  for (size_t i = 0; i < count; ++i) {
    const auto entry = get(i);
    CAPTURE(i);
    CAPTURE(entry.fqname);
    CHECK(entry.anim_index == static_cast<int>(i));
    CHECK(std::string(entry.fqid) == set + ":" + entry.id);
    CHECK(std::string(entry.fqname) == set + ":" + entry.name);

    std::string names[] = {entry.name, entry.id, entry.fqid, entry.fqname, std::string()};
    if (alt_set != nullptr) {
      names[4] = std::string(alt_set) + ":" + entry.id;
    }
    for (const auto& name : names) {
      if (name.empty()) {
        continue;
      }
      CAPTURE(name);
      config::config_t cfg;
      const int found = parse(cfg, name.c_str());
      CHECK(found >= 0);
      if (found < 0) {
        continue;
      }
      // names can be shared by different sprites (first match wins), so compare what was found
      const auto found_entry = get(static_cast<size_t>(found));
      const bool matches = name == found_entry.name || name == found_entry.id || name == found_entry.fqid ||
                           name == found_entry.fqname ||
                           (alt_set != nullptr && name == std::string(alt_set) + ":" + found_entry.id);
      CHECK(matches);
      CHECK(cfg.animation_index == found);
    }
  }

  config::config_t cfg;
  CHECK(parse(cfg, (set + ":does_not_exist").c_str()) < 0);
}

}  // namespace

TEST_CASE("animation name tables round-trip (string blobs)") {
  using namespace bongocat::assets;
  check_animation_names("dm", nullptr, DM_ANIM_COUNT, get_config_animation_name_dm, config_parse_animation_name_dm);
  check_animation_names("dm20", "dm", DM20_ANIM_COUNT, get_config_animation_name_dm20,
                        config_parse_animation_name_dm20);
  check_animation_names("dmx", nullptr, DMX_ANIM_COUNT, get_config_animation_name_dmx, config_parse_animation_name_dmx);
  check_animation_names("dmc", nullptr, DMC_ANIM_COUNT, get_config_animation_name_dmc, config_parse_animation_name_dmc);
  check_animation_names("pen", nullptr, PEN_ANIM_COUNT, get_config_animation_name_pen, config_parse_animation_name_pen);
  check_animation_names("pen20", "pen", PEN20_ANIM_COUNT, get_config_animation_name_pen20,
                        config_parse_animation_name_pen20);
  check_animation_names("dmall", "dmc", DMALL_ANIM_COUNT, get_config_animation_name_dmall,
                        config_parse_animation_name_dmall);
  check_animation_names("pkmn", nullptr, PKMN_ANIM_COUNT, get_config_animation_name_pkmn,
                        config_parse_animation_name_pkmn);
  check_animation_names("pmd", nullptr, PMD_ANIM_COUNT, get_config_animation_name_pmd, config_parse_animation_name_pmd);
}
