#include "graphics/animation.h"
#include "graphics/animation_thread_context.h"
#include "platform/wayland.h"
#include "utils/memory.h"
#include "utils/system_error.h"

#include <cassert>
#include <cstdint>
#include <sys/eventfd.h>
#include <sys/mman.h>
#include <unistd.h>
#ifdef __GLIBC__
#  include <malloc.h>
#endif

// assets
#include "embedded_assets/bongocat/assets_bongocat_features.h"
#include "embedded_assets/bongocat/bongocat.h"
#include "embedded_assets/bongocat/bongocat.hpp"
#include "embedded_assets/dm/assets_dm_features.h"
#include "embedded_assets/dm/dm_sprite.h"
#include "embedded_assets/dm20/assets_dm20_features.h"
#include "embedded_assets/dm20/dm20_sprite.h"
#include "embedded_assets/dmall/assets_dmall_features.h"
#include "embedded_assets/dmall/dmall_sprite.h"
#include "embedded_assets/dmc/assets_dmc_features.h"
#include "embedded_assets/dmc/dmc_sprite.h"
#include "embedded_assets/dmx/assets_dmx_features.h"
#include "embedded_assets/dmx/dmx_sprite.h"
#include "embedded_assets/min_dm/min_dm_sprite.h"
#include "embedded_assets/misc/assets_misc_features.h"
#include "embedded_assets/misc/misc.hpp"
#include "embedded_assets/misc/misc_sprite.h"
#include "embedded_assets/ms_agent/assets_ms_agent_features.h"
#include "embedded_assets/ms_agent/ms_agent.hpp"
#include "embedded_assets/ms_agent/ms_agent_sprite.h"
#include "embedded_assets/pen/assets_pen_features.h"
#include "embedded_assets/pen/pen_sprite.h"
#include "embedded_assets/pen20/assets_pen20_features.h"
#include "embedded_assets/pen20/pen20_sprite.h"
#include "embedded_assets/pkmn/assets_pkmn_features.h"
#include "embedded_assets/pkmn/pkmn_sprite.h"
#include "embedded_assets/pmd/assets_pmd_features.h"
#include "embedded_assets/pmd/pmd_sprite.h"
#include "graphics/embedded_assets_dms.h"
#include "graphics/embedded_assets_pkmn.h"

// image loader
#include "image_loader/base_dm/load_dm.h"
#include "image_loader/bongocat/load_images_bongocat.h"
#include "image_loader/custom/load_custom.h"
#include "image_loader/custom/load_custom_features.h"
#include "image_loader/dm/load_images_dm.h"
#include "image_loader/dm20/load_images_dm20.h"
#include "image_loader/dmall/load_images_dmall.h"
#include "image_loader/dmc/load_images_dmc.h"
#include "image_loader/dmx/load_images_dmx.h"
#include "image_loader/min_dm/load_images_min_dm.h"
#include "image_loader/misc/load_images_misc.h"
#include "image_loader/ms_agent/load_images_ms_agent.h"
#include "image_loader/pen/load_images_pen.h"
#include "image_loader/pen20/load_images_pen20.h"
#include "image_loader/pkmn/load_images_pkmn.h"
#include "image_loader/pmd/load_images_pmd.h"

namespace bongocat::animation {
[[maybe_unused]] static constexpr bool should_load_bongocat([[maybe_unused]] const config::config_t& config) {
  return features::EnablePreloadAssets ||
         config.animation_sprite_sheet_layout == config::config_animation_sprite_sheet_layout_t::Bongocat;
}
[[maybe_unused]] static constexpr bool should_load_dm([[maybe_unused]] const config::config_t& config) {
  return features::EnablePreloadAssets ||
         (config.animation_sprite_sheet_layout == config::config_animation_sprite_sheet_layout_t::Dm &&
          config.animation_dm_set != config::config_animation_dm_set_t::None);
}
[[maybe_unused]] static constexpr bool should_load_ms_agent([[maybe_unused]] const config::config_t& config) {
  return features::EnablePreloadAssets ||
         config.animation_sprite_sheet_layout == config::config_animation_sprite_sheet_layout_t::MsAgent;
}
[[maybe_unused]] static constexpr bool should_load_pkmn([[maybe_unused]] const config::config_t& config) {
  return features::EnablePreloadAssets ||
         config.animation_sprite_sheet_layout == config::config_animation_sprite_sheet_layout_t::Pkmn;
}
[[maybe_unused]] static constexpr bool should_load_misc([[maybe_unused]] const config::config_t& config) {
  return features::EnablePreloadAssets ||
         (config.animation_sprite_sheet_layout == config::config_animation_sprite_sheet_layout_t::Custom &&
          config.animation_custom_set == config::config_animation_custom_set_t::misc);
}
[[maybe_unused]] static constexpr bool should_load_custom([[maybe_unused]] const config::config_t& config) {
  return (features::EnablePreloadAssets && config._custom) ||
         (config._custom &&
          config.animation_sprite_sheet_layout == config::config_animation_sprite_sheet_layout_t::Custom &&
          config.animation_custom_set == config::config_animation_custom_set_t::custom);
}
[[maybe_unused]] static constexpr bool should_load_pmd([[maybe_unused]] const config::config_t& config) {
  return features::EnablePreloadAssets ||
         (config._custom &&
          config.animation_sprite_sheet_layout == config::config_animation_sprite_sheet_layout_t::Custom &&
          config.animation_custom_set == config::config_animation_custom_set_t::pmd);
}

namespace details {
  created_result_t<custom_sprite_sheet_t> anim_load_custom_animation(animation_thread_context_t& ctx,
                                                                     const config::config_t& config) {
    BONGOCAT_CHECK_NULL(config.custom_sprite_sheet_filename.c_str(), bongocat_error_t::BONGOCAT_ERROR_INVALID_PARAM);
    if (strlen(config.custom_sprite_sheet_filename.c_str()) <= 0) {
      return bongocat_error_t::BONGOCAT_ERROR_INVALID_PARAM;
    }

    assert(ctx.shm.ptr);
    assert(ctx._local_copy_config.ptr);

    BONGOCAT_LOG_VERBOSE("Load custom Animation: %s ...", config.custom_sprite_sheet_filename.c_str());
    auto sprite_sheet_image_result = load_custom_sprite_sheet_file(config.custom_sprite_sheet_filename.c_str());
    if (sprite_sheet_image_result.error != bongocat_error_t::BONGOCAT_SUCCESS) [[unlikely]] {
      BONGOCAT_LOG_ERROR("Load custom Animation failed: %s", config.custom_sprite_sheet_filename.c_str());
      return bongocat_error_t::BONGOCAT_ERROR_ANIMATION;
    }

    auto result = load_custom_anim(ctx, sprite_sheet_image_result.result, config.custom_sprite_sheet_settings);
    free_custom_sprite_sheet_file(sprite_sheet_image_result.result);
    if (result.error != bongocat_error_t::BONGOCAT_SUCCESS) [[unlikely]] {
      BONGOCAT_LOG_ERROR("Load custom Animation failed: %s", config.custom_sprite_sheet_filename.c_str());
      return bongocat_error_t::BONGOCAT_ERROR_ANIMATION;
    }

    return result;
  }
}  // namespace details

static void unload_assets_readonly_sections();
created_result_t<animation_t *> hot_load_animation(animation_thread_context_t& ctx) {
  // read-only config
  assert(ctx._local_copy_config);
  const config::config_t& current_config = *ctx._local_copy_config;
  assert(ctx.shm);
  animation_shared_memory_t& anim_shm = *ctx.shm;
  const int anim_index = anim_shm.anim_index;

  [[maybe_unused]] const auto t0 = platform::get_current_time_us();

  switch (anim_shm.anim_type) {
  case config::config_animation_sprite_sheet_layout_t::None:
    // unload other sprite sheets
    cleanup_animation(anim_shm.anim);
    break;
  case config::config_animation_sprite_sheet_layout_t::Bongocat: {
    if constexpr (features::EnableBongocatEmbeddedAssets) {
      auto [result, error] = load_bongocat_sprite_sheet(ctx, anim_index);
      if (error != bongocat_error_t::BONGOCAT_SUCCESS) [[unlikely]] {
        return error;
      }
      anim_shm.anim = bongocat::move(result);
    }
  } break;
  case config::config_animation_sprite_sheet_layout_t::Dm: {
    bongocat_error_t error = bongocat_error_t::BONGOCAT_ERROR_INVALID_PARAM;
    dm_sprite_sheet_t result;
    switch (anim_shm.anim_dm_set) {
    case config::config_animation_dm_set_t::None:
      cleanup_animation(result);
      error = bongocat_error_t::BONGOCAT_SUCCESS;
      break;
    case config::config_animation_dm_set_t::min_dm: {
      if constexpr (features::EnableMinDmEmbeddedAssets) {
        assert(anim_index >= 0);
        auto [l_result, l_error] = load_min_dm_sprite_sheet(ctx, static_cast<size_t>(anim_index));
        patch_dm_anim(l_result, {.sleep_in_bed = true});
        result = bongocat::move(l_result);
        error = bongocat::move(l_error);
      }
    } break;
    case config::config_animation_dm_set_t::dm: {
      if constexpr (features::EnableFullDmEmbeddedAssets) {
        assert(anim_index >= 0);
        auto [l_result, l_error] = load_dm_sprite_sheet(ctx, static_cast<size_t>(anim_index));
        patch_dm_anim(l_result, {.sleep_in_bed = true});
        result = bongocat::move(l_result);
        error = bongocat::move(l_error);
      }
    } break;
    case config::config_animation_dm_set_t::dm20: {
      if constexpr (features::EnableDm20EmbeddedAssets) {
        assert(anim_index >= 0);
        auto [l_result, l_error] = load_dm20_sprite_sheet(ctx, static_cast<size_t>(anim_index));
        patch_dm_anim(l_result, {.sleep_in_bed = true});
        result = bongocat::move(l_result);
        error = bongocat::move(l_error);
      }
    } break;
    case config::config_animation_dm_set_t::dmx: {
      if constexpr (features::EnableDmxEmbeddedAssets) {
        assert(anim_index >= 0);
        auto [l_result, l_error] = load_dmx_sprite_sheet(ctx, static_cast<size_t>(anim_index));
        result = bongocat::move(l_result);
        error = bongocat::move(l_error);
      }
    } break;
    case config::config_animation_dm_set_t::pen: {
      if constexpr (features::EnablePenEmbeddedAssets) {
        assert(anim_index >= 0);
        auto [l_result, l_error] = load_pen_sprite_sheet(ctx, static_cast<size_t>(anim_index));
        result = bongocat::move(l_result);
        error = bongocat::move(l_error);
      }
    } break;
    case config::config_animation_dm_set_t::pen20: {
      if constexpr (features::EnablePen20EmbeddedAssets) {
        assert(anim_index >= 0);
        auto [l_result, l_error] = load_pen20_sprite_sheet(ctx, static_cast<size_t>(anim_index));
        result = bongocat::move(l_result);
        error = bongocat::move(l_error);
      }
    } break;
    case config::config_animation_dm_set_t::dmc: {
      if constexpr (features::EnableDmcEmbeddedAssets) {
        assert(anim_index >= 0);
        auto [l_result, l_error] = load_dmc_sprite_sheet(ctx, static_cast<size_t>(anim_index));
        patch_dm_anim(l_result, {.sleep_in_bed = false, .no_happy = true});
        result = bongocat::move(l_result);
        error = bongocat::move(l_error);
      }
    } break;
    case config::config_animation_dm_set_t::dmall: {
      if constexpr (features::EnableDmAllEmbeddedAssets) {
        assert(anim_index >= 0);
        auto [l_result, l_error] = load_dmall_sprite_sheet(ctx, static_cast<size_t>(anim_index));
        result = bongocat::move(l_result);
        error = bongocat::move(l_error);
      }
    } break;
    }
    if (error != bongocat_error_t::BONGOCAT_SUCCESS) [[unlikely]] {
      return error;
    }
    anim_shm.anim = bongocat::move(result);
  } break;
  case config::config_animation_sprite_sheet_layout_t::Pkmn:
    if constexpr (features::EnablePkmnEmbeddedAssets) {
      assert(anim_index >= 0);
      auto [result, error] = load_pkmn_sprite_sheet(ctx, static_cast<size_t>(anim_index));
      if (error != bongocat_error_t::BONGOCAT_SUCCESS) [[unlikely]] {
        return error;
      }
      anim_shm.anim = bongocat::move(result);
    }
    break;
  case config::config_animation_sprite_sheet_layout_t::MsAgent:
    if constexpr (features::EnableMsAgentEmbeddedAssets) {
      assert(anim_index >= 0);
      auto [result, error] = load_ms_agent_sprite_sheet(ctx, static_cast<size_t>(anim_index));
      if (error != bongocat_error_t::BONGOCAT_SUCCESS) [[unlikely]] {
        return error;
      }
      anim_shm.anim = bongocat::move(result);
    }
    break;
  case config::config_animation_sprite_sheet_layout_t::Custom:
    assert(anim_index >= 0);
    if constexpr (features::EnableCustomSpriteSheetsAssets && features::EnableMiscEmbeddedAssets) {
      static_assert(assets::CUSTOM_ANIM_INDEX > assets::MAX_MISC_ANIM_INDEX);
    }
    if constexpr (features::EnableCustomSpriteSheetsAssets) {
      if (current_config._custom && anim_index == assets::CUSTOM_ANIM_INDEX) {
        auto [result, error] = details::anim_load_custom_animation(ctx, current_config);
        if (error != bongocat_error_t::BONGOCAT_SUCCESS) {
          return error;
        }
        anim_shm.anim = bongocat::move(result);
      }
    }
    if constexpr (features::EnableMiscEmbeddedAssets) {
      assert(anim_index >= 0);
      if (current_config.animation_custom_set == config::config_animation_custom_set_t::misc &&
          static_cast<size_t>(anim_index) < assets::MISC_ANIM_COUNT) {
        auto [result, error] = load_misc_sprite_sheet(ctx, static_cast<size_t>(anim_index));
        if (error != bongocat_error_t::BONGOCAT_SUCCESS) [[unlikely]] {
          return error;
        }
        anim_shm.anim = bongocat::move(result);
      }
    }
    if constexpr (features::EnablePmdEmbeddedAssets) {
      assert(anim_index >= 0);
      if (current_config.animation_custom_set == config::config_animation_custom_set_t::pmd &&
          static_cast<size_t>(anim_index) < assets::PMD_ANIM_COUNT) {
        auto [result, error] = load_pmd_sprite_sheet(ctx, static_cast<size_t>(anim_index));
        if (error != bongocat_error_t::BONGOCAT_SUCCESS) [[unlikely]] {
          return error;
        }
        anim_shm.anim = bongocat::move(result);
      }
    }

    break;
    /// @NOTE(assets): 6. add hot reload asset
  }

  // init evolution data
  if constexpr (features::EnableEvolution) {
    details::update_evolution_data(anim_shm);

    BONGOCAT_LOG_VERBOSE("Update Evolution (anim_index=%d) with %d possible evolution(s), next evolution in %dsec",
                         anim_shm.anim_index, anim_shm.evolution.data.num_animation_indices,
                         anim_shm.evolution.data.conditions.next_evolution_time_sec);
  }

  created_result_t<animation_t *> ret;
  ret.result = &get_current_animation(ctx);
  ret.error = bongocat_error_t::BONGOCAT_SUCCESS;

  // after heavy sprite loading, try to free some memory
  unload_assets_readonly_sections();
  // return unused heap memory back to the OS
#ifdef __GLIBC__
  malloc_trim(0);
#endif

  [[maybe_unused]] const auto t1 = platform::get_current_time_us();

  BONGOCAT_LOG_VERBOSE("hot_load_animation; reload assets in %.3fms (%.6fsec)", static_cast<double>(t1 - t0) / 1000.0,
                       static_cast<double>(t1 - t0) / 1000000.0);

  return ret;
}

struct madvise_region {
  const char *start{};
  const char *stop{};
  const char *name{};
};
void unload_assets_readonly_sections() {
  static constexpr madvise_region evictable_regions[] = {
      {__start_assets_images,          __stop_assets_images,          ".assets.images"         },
      {__start_assets_data_evol,       __stop_assets_data_evol,       ".assets.data_evol"      },
      {__start_assets_sprite_settings, __stop_assets_sprite_settings, ".assets.sprite_settings"},
      //{ __start_config_str,            __stop_config_str,            ".config.str"             },
  };

  for (const auto& region : evictable_regions) {
    const uintptr_t start = reinterpret_cast<uintptr_t>(region.start);
    const uintptr_t stop = reinterpret_cast<uintptr_t>(region.stop);
    assert(stop >= start);
    const size_t size = stop - start;
    if (size == 0) {
      continue;
    }

    // @TODO: check for MAXPAGESIZE
    // assert((start % 4096) == 0);
    // assert((size % 4096) == 0);

    if (madvise(reinterpret_cast<void *>(start), size, MADV_DONTNEED) != 0) {
      BONGOCAT_LOG_WARNING("madvise: failed to evict %s: %s", region.name, strerror(errno));
    } else {
      BONGOCAT_LOG_VERBOSE("madvise: evicted %s: %zu kb", region.name, size / 1024);
    }
  }
}

animation_t& get_current_animation(animation_thread_context_t& ctx) {
  using namespace assets;
  // fallback sprite
  static animation_t none_sprite_sheet{};

  // read-only config
  assert(ctx._local_copy_config);
  // const config::config_t& current_config = *ctx._local_copy_config;
  assert(ctx.shm);
  animation_shared_memory_t& anim_shm = *ctx.shm;
  const int anim_index = anim_shm.anim_index;

  switch (anim_shm.anim_type) {
  case config::config_animation_sprite_sheet_layout_t::None:
    return none_sprite_sheet;
  case config::config_animation_sprite_sheet_layout_t::Bongocat: {
    if constexpr (features::EnableLazyLoadAssets) {
      assert(anim_shm.anim.type == animation_t::type_t::Bongocat);
      return anim_shm.anim;
    }
    assert(anim_index >= 0);
    return static_cast<size_t>(anim_index) < anim_shm.bongocat_anims.count
               ? anim_shm.bongocat_anims[static_cast<size_t>(anim_index)]
               : none_sprite_sheet;
  }
  case config::config_animation_sprite_sheet_layout_t::Dm: {
    switch (anim_shm.anim_dm_set) {
    case config::config_animation_dm_set_t::None:
      return none_sprite_sheet;
    case config::config_animation_dm_set_t::min_dm:
      if constexpr (features::EnableLazyLoadAssets) {
        assert(anim_shm.anim.type == animation_t::type_t::Dm);
        return anim_shm.anim;
      }
      assert(anim_index >= 0);
      return static_cast<size_t>(anim_index) < anim_shm.min_dm_anims.count
                 ? anim_shm.min_dm_anims[static_cast<size_t>(anim_index)]
                 : none_sprite_sheet;
    case config::config_animation_dm_set_t::dm:
      if constexpr (features::EnableLazyLoadAssets) {
        assert(anim_shm.anim.type == animation_t::type_t::Dm);
        return anim_shm.anim;
      }
      return static_cast<size_t>(anim_index) < anim_shm.dm_anims.count
                 ? anim_shm.dm_anims[static_cast<size_t>(anim_index)]
                 : none_sprite_sheet;
    case config::config_animation_dm_set_t::dm20:
      if constexpr (features::EnableLazyLoadAssets) {
        assert(anim_shm.anim.type == animation_t::type_t::Dm);
        return anim_shm.anim;
      }
      assert(anim_index >= 0);
      return static_cast<size_t>(anim_index) < anim_shm.dm20_anims.count
                 ? anim_shm.dm20_anims[static_cast<size_t>(anim_index)]
                 : none_sprite_sheet;
    case config::config_animation_dm_set_t::dmx:
      if constexpr (features::EnableLazyLoadAssets) {
        assert(anim_shm.anim.type == animation_t::type_t::Dm);
        return anim_shm.anim;
      }
      assert(anim_index >= 0);
      return static_cast<size_t>(anim_index) < anim_shm.dmx_anims.count
                 ? anim_shm.dmx_anims[static_cast<size_t>(anim_index)]
                 : none_sprite_sheet;
    case config::config_animation_dm_set_t::pen:
      if constexpr (features::EnableLazyLoadAssets) {
        assert(anim_shm.anim.type == animation_t::type_t::Dm);
        return anim_shm.anim;
      }
      return static_cast<size_t>(anim_index) < anim_shm.pen_anims.count
                 ? anim_shm.pen_anims[static_cast<size_t>(anim_index)]
                 : none_sprite_sheet;
    case config::config_animation_dm_set_t::pen20:
      if constexpr (features::EnableLazyLoadAssets) {
        assert(anim_shm.anim.type == animation_t::type_t::Dm);
        return anim_shm.anim;
      }
      assert(anim_index >= 0);
      return static_cast<size_t>(anim_index) < anim_shm.pen20_anims.count
                 ? anim_shm.pen20_anims[static_cast<size_t>(anim_index)]
                 : none_sprite_sheet;
    case config::config_animation_dm_set_t::dmc:
      if constexpr (features::EnableLazyLoadAssets) {
        assert(anim_shm.anim.type == animation_t::type_t::Dm);
        return anim_shm.anim;
      }
      assert(anim_index >= 0);
      return static_cast<size_t>(anim_index) < anim_shm.dmc_anims.count
                 ? anim_shm.dmc_anims[static_cast<size_t>(anim_index)]
                 : none_sprite_sheet;
    case config::config_animation_dm_set_t::dmall:
      if constexpr (features::EnableLazyLoadAssets) {
        assert(anim_shm.anim.type == animation_t::type_t::Dm);
        return anim_shm.anim;
      }
      assert(anim_index >= 0);
      return static_cast<size_t>(anim_index) < anim_shm.dmall_anims.count
                 ? anim_shm.dmall_anims[static_cast<size_t>(anim_index)]
                 : none_sprite_sheet;
    }
  } break;
  case config::config_animation_sprite_sheet_layout_t::Pkmn:
    if constexpr (features::EnableLazyLoadAssets) {
      assert(anim_shm.anim.type == animation_t::type_t::Pkmn);
      return anim_shm.anim;
    }
    assert(anim_index >= 0);
    return static_cast<size_t>(anim_index) < anim_shm.pkmn_anims.count
               ? anim_shm.pkmn_anims[static_cast<size_t>(anim_index)]
               : none_sprite_sheet;
  case config::config_animation_sprite_sheet_layout_t::MsAgent:
    if constexpr (features::EnableLazyLoadAssets) {
      assert(anim_shm.anim.type == animation_t::type_t::MsAgent);
      return anim_shm.anim;
    }
    assert(anim_index >= 0);
    return static_cast<size_t>(anim_index) < anim_shm.ms_anims.count
               ? anim_shm.ms_anims[static_cast<size_t>(anim_index)]
               : none_sprite_sheet;
  case config::config_animation_sprite_sheet_layout_t::Custom:
    switch (anim_shm.anim_custom_set) {
    case config::config_animation_custom_set_t::None:
      break;
    case config::config_animation_custom_set_t::misc:
      if constexpr (features::EnableLazyLoadAssets) {
        assert(anim_shm.anim.type == animation_t::type_t::Custom);
        return anim_shm.anim;
      }
      assert(anim_index >= 0);
      return static_cast<size_t>(anim_index) < anim_shm.misc_anims.count
                 ? anim_shm.misc_anims[static_cast<size_t>(anim_index)]
                 : none_sprite_sheet;
      break;
    case config::config_animation_custom_set_t::pmd:
      if constexpr (features::EnableLazyLoadAssets) {
        assert(anim_shm.anim.type == animation_t::type_t::Custom);
        return anim_shm.anim;
      }
      assert(anim_index >= 0);
      return static_cast<size_t>(anim_index) < anim_shm.pmd_anims.count
                 ? anim_shm.pmd_anims[static_cast<size_t>(anim_index)]
                 : none_sprite_sheet;
      break;
    case config::config_animation_custom_set_t::custom:
      if constexpr (features::EnableLazyLoadAssets) {
        assert(anim_shm.anim.type == animation_t::type_t::Custom);
        return anim_shm.anim;
      }
      if (static_cast<size_t>(anim_index) == CUSTOM_ANIM_INDEX) {
        return anim_shm.anim;
      }
      break;
    }
  }

  return none_sprite_sheet;
}

// =============================================================================
// PUBLIC API IMPLEMENTATION
// =============================================================================

created_result_t<AllocatedMemory<animation_context_t>> create(const config::config_t& config) {
  using namespace assets;
  BONGOCAT_LOG_INFO("Initializing animation system");
  AllocatedMemory<animation_context_t> ret = make_allocated_memory<animation_context_t>();
  assert(ret);
  if (!ret) [[unlikely]] {
    return bongocat_error_t::BONGOCAT_ERROR_MEMORY;
  }

  ret->_config = &config;

  // Initialize shared memory
  ret->thread_context.shm = platform::make_allocated_mmap<animation_shared_memory_t>();
  if (!ret->thread_context.shm) {
    BONGOCAT_LOG_ERROR("Failed to create shared memory for animation system: %s", strerror(errno));
    return bongocat_error_t::BONGOCAT_ERROR_MEMORY;
  }
  assert(ret->thread_context.shm);

  // Initialize shared memory for local config
  ret->thread_context._local_copy_config = platform::make_allocated_mmap<config::config_t>();
  if (!ret->thread_context._local_copy_config) {
    BONGOCAT_LOG_ERROR("Failed to create shared memory for animation system: %s", strerror(errno));
    return bongocat_error_t::BONGOCAT_ERROR_MEMORY;
  }
  assert(ret->thread_context._local_copy_config);
  // config_set_defaults(*ctx._local_copy_config);
  *ret->thread_context._local_copy_config = config;
  ret->thread_context.shm->animation_player_result.sprite_sheet_col = config.idle_frame;  // initial frame

  ret->trigger_efd = platform::FileDescriptor(eventfd(0, EFD_NONBLOCK | EFD_CLOEXEC));
  if (ret->trigger_efd._fd < 0) {
    BONGOCAT_LOG_ERROR("Failed to create notify pipe for animation trigger: %s", strerror(errno));
    return bongocat_error_t::BONGOCAT_ERROR_FILE_IO;
  }

  ret->render_efd = platform::FileDescriptor(eventfd(0, EFD_NONBLOCK | EFD_CLOEXEC));
  if (ret->render_efd._fd < 0) {
    BONGOCAT_LOG_ERROR("Failed to create notify pipe for animation render: %s", strerror(errno));
    return bongocat_error_t::BONGOCAT_ERROR_FILE_IO;
  }

  ret->reload_animation_efd = platform::FileDescriptor(eventfd(0, EFD_NONBLOCK | EFD_CLOEXEC));
  if (ret->reload_animation_efd._fd < 0) {
    BONGOCAT_LOG_ERROR("Failed to create notify pipe for animation reload: %s", strerror(errno));
    return bongocat_error_t::BONGOCAT_ERROR_FILE_IO;
  }

  ret->thread_context.update_config_efd = platform::FileDescriptor(eventfd(0, EFD_NONBLOCK | EFD_CLOEXEC));
  if (ret->thread_context.update_config_efd._fd < 0) {
    BONGOCAT_LOG_ERROR("Failed to create notify pipe for input update config: %s", strerror(errno));
    return bongocat_error_t::BONGOCAT_ERROR_FILE_IO;
  }

  // Initialize embedded images/animations
  [[maybe_unused]] const auto t0 = platform::get_current_time_us();
  /// @TODO: async assets load
  if constexpr (!features::EnableLazyLoadAssets || features::EnablePreloadAssets) {
    assert(ret->thread_context._local_copy_config);
    // preload assets
    if constexpr (features::EnableBongocatEmbeddedAssets) {
      // Load Bongocat
      if (should_load_bongocat(*ret->thread_context._local_copy_config)) {
        BONGOCAT_LOG_INFO("Load bongocat sprite sheet frames: %d", BONGOCAT_EMBEDDED_IMAGES_COUNT);
        assert(ret->thread_context.shm);
        animation_thread_context_t& ctx = ret->thread_context;  // alias for inits in includes

        ctx.shm->bongocat_anims = platform::make_allocated_mmap_array<animation_t>(BONGOCAT_ANIM_COUNT);

        if constexpr (features::EnableBongocatSvg) {
          const int cat_height = ret->thread_context._local_copy_config->cat_height;
          init_bongocat_anim(ctx, BONGOCAT_ANIM_INDEX, get_bongocat_sprite_svg, BONGOCAT_EMBEDDED_IMAGES_COUNT,
                             load_bongocat_anim_type_t::SVG, anim_bongocat_get_svg_params(cat_height),
                             anim_bongocat_get_svg_cropping(cat_height));
        } else {
          init_bongocat_anim(ctx, BONGOCAT_ANIM_INDEX, get_bongocat_sprite, BONGOCAT_EMBEDDED_IMAGES_COUNT,
                             load_bongocat_anim_type_t::PNG, {0, 0, 0, 0}, {0, 0, 0, 0});
        }
      }
    }

    if constexpr (features::EnableDmEmbeddedAssets) {
      // Load dm
      if (should_load_dm(*ret->thread_context._local_copy_config)) {
        BONGOCAT_LOG_INFO("Load dm sprite sheets: %d", DM_ANIMATIONS_COUNT);
        assert(ret->thread_context.shm);
        animation_thread_context_t& ctx = ret->thread_context;  // alias for inits in includes

        if constexpr (features::EnableMinDmEmbeddedAssets) {
          BONGOCAT_LOG_INFO("Init min_dm sprite sheets: %d", MIN_DM_ANIM_COUNT);
          ctx.shm->min_dm_anims = platform::make_allocated_mmap_array<animation_t>(MIN_DM_ANIM_COUNT);
#ifdef FEATURE_MIN_DM_EMBEDDED_ASSETS
          init_all_min_dm_anim(ctx);
#endif
          for (size_t i = 0; i < MIN_DM_ANIM_COUNT; ++i) {
            patch_dm_anim(ctx.shm->min_dm_anims[i].dm, {.sleep_in_bed = true});
          }
        }
        if constexpr (features::EnableFullDmEmbeddedAssets) {
          BONGOCAT_LOG_INFO("Init dm sprite sheets: %d", DM_ANIM_COUNT);
          ctx.shm->dm_anims = platform::make_allocated_mmap_array<animation_t>(DM_ANIM_COUNT);
#ifdef FEATURE_DM_EMBEDDED_ASSETS
          // dm
          init_all_dm_anim(ctx);
#endif
          for (size_t i = 0; i < DM_ANIM_COUNT; ++i) {
            patch_dm_anim(ctx.shm->dm_anims[i].dm, {.sleep_in_bed = true});
          }
        }
        if constexpr (features::EnableDm20EmbeddedAssets) {
          BONGOCAT_LOG_INFO("Init dm20 sprite sheets: %d", DM20_ANIM_COUNT);
          ctx.shm->dm20_anims = platform::make_allocated_mmap_array<animation_t>(DM20_ANIM_COUNT);
#ifdef FEATURE_DM20_EMBEDDED_ASSETS
          // dm20
          init_all_dm20_anim(ctx);
#endif
          for (size_t i = 0; i < MIN_DM_ANIM_COUNT; ++i) {
            patch_dm_anim(ctx.shm->dm20_anims[i].dm, {.sleep_in_bed = true});
          }
        }
        if constexpr (features::EnableDmxEmbeddedAssets) {
          BONGOCAT_LOG_INFO("Init dmx sprite sheets: %d", DMX_ANIM_COUNT);
          ctx.shm->dmx_anims = platform::make_allocated_mmap_array<animation_t>(DMX_ANIM_COUNT);
#ifdef FEATURE_DMX_EMBEDDED_ASSETS
          // dmx
          init_all_dmx_anim(ctx);
#endif
        }
        if constexpr (features::EnablePenEmbeddedAssets) {
          BONGOCAT_LOG_INFO("Init pen sprite sheets: %d", PEN20_ANIM_COUNT);
          ctx.shm->pen_anims = platform::make_allocated_mmap_array<animation_t>(PEN_ANIM_COUNT);
#ifdef FEATURE_PEN_EMBEDDED_ASSETS
          // pen
          init_all_pen_anim(ctx);
#endif
        }
        if constexpr (features::EnablePen20EmbeddedAssets) {
          BONGOCAT_LOG_INFO("Init pen20 sprite sheets: %d", PEN20_ANIM_COUNT);
          ctx.shm->pen20_anims = platform::make_allocated_mmap_array<animation_t>(PEN20_ANIM_COUNT);
#ifdef FEATURE_PEN20_EMBEDDED_ASSETS
          // pen20
          init_all_pen20_anim(ctx);
#endif
        }
        if constexpr (features::EnableDmcEmbeddedAssets) {
          BONGOCAT_LOG_INFO("Init dmc sprite sheets: %d", DMC_ANIM_COUNT);
          ctx.shm->dmc_anims = platform::make_allocated_mmap_array<animation_t>(DMC_ANIM_COUNT);
#ifdef FEATURE_DMC_EMBEDDED_ASSETS
          // dmc
          init_all_dmc_anim(ctx);
#endif
        }
        if constexpr (features::EnableDmAllEmbeddedAssets) {
          BONGOCAT_LOG_INFO("Init dmall sprite sheets: %d", DMALL_ANIM_COUNT);
          ctx.shm->dmall_anims = platform::make_allocated_mmap_array<animation_t>(DMALL_ANIM_COUNT);
#ifdef FEATURE_DMALL_EMBEDDED_ASSETS
          // dmall
          init_all_dmall_anim(ctx);
#endif
        }
      }
    }

    if constexpr (features::EnableMsAgentEmbeddedAssets) {
      // Load Ms Pets (Clippy)
      if (should_load_ms_agent(*ret->thread_context._local_copy_config)) {
        BONGOCAT_LOG_INFO("Load MS agent sprite sheets: %d", MS_AGENTS_ANIM_COUNT);
        assert(ret->thread_context.shm);
        animation_thread_context_t& ctx = ret->thread_context;  // alias for inits in includes

        ctx.shm->ms_anims = platform::make_allocated_mmap_array<animation_t>(MS_AGENTS_ANIM_COUNT);

#ifdef FEATURE_MS_AGENT_EMBEDDED_ASSETS
        init_all_ms_agent_anim(ctx);
#endif
      }
    }

    if constexpr (features::EnablePkmnEmbeddedAssets) {
      // Load pkmn
      if (should_load_pkmn(*ret->thread_context._local_copy_config)) {
        BONGOCAT_LOG_INFO("Load pkmn sprite sheets: %d", PKMN_ANIM_COUNT);
        assert(ret->thread_context.shm);
        animation_thread_context_t& ctx = ret->thread_context;  // alias for inits in includes

        ctx.shm->pkmn_anims = platform::make_allocated_mmap_array<animation_t>(PKMN_ANIM_COUNT);
#ifdef FEATURE_PKMN_EMBEDDED_ASSETS
        // pkmn
        init_all_pkmn_anim(ctx);
#endif
      }
    }
    if constexpr (features::EnablePmdEmbeddedAssets) {
      // Load pmd (pkmn)
      if (should_load_pmd(*ret->thread_context._local_copy_config)) {
        BONGOCAT_LOG_INFO("Load pmd sprite sheets: %d", PMD_ANIM_COUNT);
        assert(ret->thread_context.shm);
        animation_thread_context_t& ctx = ret->thread_context;  // alias for inits in includes

        ctx.shm->pmd_anims = platform::make_allocated_mmap_array<animation_t>(PMD_ANIM_COUNT);
#ifdef FEATURE_PMD_EMBEDDED_ASSETS
        // pmd (pkmn)
        init_all_pmd_anim(ctx);
#endif
      }
    }

    if constexpr (features::EnableMiscEmbeddedAssets) {
      // Load Misc Pets (neko)
      if (should_load_misc(*ret->thread_context._local_copy_config)) {
        BONGOCAT_LOG_INFO("Load Misc sprite sheets: %d", MISC_ANIM_COUNT);
        assert(ret->thread_context.shm);
        animation_thread_context_t& ctx = ret->thread_context;  // alias for inits in includes

        ctx.shm->misc_anims = platform::make_allocated_mmap_array<animation_t>(MISC_ANIM_COUNT);
#ifdef FEATURE_MISC_EMBEDDED_ASSETS
        init_all_misc_anim(ctx);
#endif
      }
    }

    if constexpr (features::EnableCustomSpriteSheetsAssets) {
      assert(ret->thread_context._local_copy_config.ptr);
      // Load custom sprite sheet
      if (should_load_custom(*ret->thread_context._local_copy_config)) {
        assert(ret->thread_context.shm);
        animation_thread_context_t& ctx = ret->thread_context;  // alias for inits in includes
        assert(ctx.shm.ptr);
        assert(ctx._local_copy_config.ptr);

        if (ctx._local_copy_config->_custom) {
          BONGOCAT_LOG_INFO("Load custom sprite sheets: %s",
                            ctx._local_copy_config->custom_sprite_sheet_filename.c_str());

          auto result = details::anim_load_custom_animation(ctx, *ctx._local_copy_config);
          if (result.error != bongocat_error_t::BONGOCAT_SUCCESS) {
            return bongocat_error_t::BONGOCAT_ERROR_ANIMATION;
          }

          ctx.shm->anim = bongocat::move(result.result);
        }
      }
    }

    /// @NOTE(assets): 7. add pre-load asset

    // init evolution data
    if constexpr (features::EnableEvolution) {
      assert(ret->thread_context.shm);
      animation_thread_context_t& ctx = ret->thread_context;  // alias for inits in includes
      assert(ctx.shm.ptr);

      details::update_evolution_data(*ctx.shm);

      BONGOCAT_LOG_INFO("Init Evolution (anim_index=%d) with %d possible evolution(s)", ctx.shm->anim_index,
                        ctx.shm->evolution.data.num_animation_indices);
    }
  }
  // Load embedded images/animations
  else if constexpr (features::EnableLazyLoadAssets) {
    hot_load_animation(ret->thread_context);
  }
  [[maybe_unused]] const auto t1 = platform::get_current_time_us();

  // init anim
  ret->thread_context._rng = platform::random_xoshiro128(platform::slow_rand());

  /// @TODO: not needed anymore ?, config got already initialized above
  // Initialize shared memory for local config
  if (!ret->thread_context._local_copy_config) [[unlikely]] {
    ret->thread_context._local_copy_config = platform::make_allocated_mmap<config::config_t>();
    if (!ret->thread_context._local_copy_config) [[unlikely]] {
      BONGOCAT_LOG_ERROR("Failed to create shared memory for input monitoring: %s", strerror(errno));
      return bongocat_error_t::BONGOCAT_ERROR_MEMORY;
    }
  }
  assert(ret->thread_context._local_copy_config);

  BONGOCAT_LOG_INFO("Animation system initialized successfully with embedded assets; load assets in %.3fms (%.6fsec)",
                    static_cast<double>(t1 - t0) / 1000.0, static_cast<double>(t1 - t0) / 1000000.0);
  return ret;
}

void stop(animation_thread_context_t& ctx) {
  atomic_store(&ctx._animation_running, false);
  if (ctx._anim_thread) {
    BONGOCAT_LOG_DEBUG("Stopping animation thread");
    // Wait for thread to finish gracefully
    // pthread_cancel(ctx->_anim_thread);
    if (platform::stop_thread_graceful_or_cancel(ctx._anim_thread, ctx._animation_running) != 0) {
      BONGOCAT_LOG_ERROR("Failed to join animation thread: %s", strerror(errno));
    }
    BONGOCAT_LOG_DEBUG("Animation thread terminated");
  }
  ctx._anim_thread = 0;

  ctx.config_updated.notify_all();
}
}  // namespace bongocat::animation
