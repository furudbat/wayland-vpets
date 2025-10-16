#include "graphics/animation_context.h"
#include "graphics/animation.h"
#include "platform/wayland.h"
#include "utils/memory.h"
#include <ctime>
#include <pthread.h>
#include <sys/stat.h>
#include <cassert>
#include <sys/eventfd.h>

// assets
#include "graphics/embedded_assets_dms.h"
#include "embedded_assets/bongocat/bongocat.hpp"
#include "embedded_assets/ms_agent/ms_agent.hpp"
#include "embedded_assets/bongocat/bongocat.h"
#include "embedded_assets/ms_agent/ms_agent_sprite.h"
#include "embedded_assets/dm/dm_sprite.h"
#include "embedded_assets/min_dm/min_dm_sprite.h"
#include "embedded_assets/dm20/dm20_sprite.h"
#include "embedded_assets/dmx/dmx_sprite.h"
#include "embedded_assets/pen/pen_sprite.h"
#include "embedded_assets/pen20/pen20_sprite.h"
#include "embedded_assets/dmc/dmc_sprite.h"
#include "embedded_assets/dmall/dmall_sprite.h"
#include "graphics/embedded_assets_pkmn.h"
#include "embedded_assets/pkmn/pkmn_sprite.h"

// image loader
#include "image_loader/bongocat/load_images_bongocat.h"
#include "image_loader/ms_agent/load_images_ms_agent.h"
#include "image_loader/dm/load_images_dm.h"
#include "image_loader/min_dm/load_images_min_dm.h"
#include "image_loader/dm20/load_images_dm20.h"
#include "image_loader/dmx/load_images_dmx.h"
#include "image_loader/pen/load_images_pen.h"
#include "image_loader/pen20/load_images_pen20.h"
#include "image_loader/dmc/load_images_dmc.h"
#include "image_loader/dmall/load_images_dmall.h"
#include "image_loader/pkmn/load_images_pkmn.h"


namespace bongocat::animation {
    [[maybe_unused]] static constexpr bool should_load_bongocat([[maybe_unused]] const config::config_t& config) {
        return features::EnablePreloadAssets || config.animation_sprite_sheet_layout == config::config_animation_sprite_sheet_layout_t::Bongocat;
    }
    [[maybe_unused]] static constexpr bool should_load_dm([[maybe_unused]] const config::config_t& config) {
        return features::EnablePreloadAssets || config.animation_sprite_sheet_layout == config::config_animation_sprite_sheet_layout_t::Dm;
    }
    [[maybe_unused]] static constexpr bool should_load_ms_agent([[maybe_unused]] const config::config_t& config) {
        return features::EnablePreloadAssets || config.animation_sprite_sheet_layout == config::config_animation_sprite_sheet_layout_t::MsAgent;
    }
    [[maybe_unused]] static constexpr bool should_load_pkmn([[maybe_unused]] const config::config_t& config) {
        return features::EnablePreloadAssets || config.animation_sprite_sheet_layout == config::config_animation_sprite_sheet_layout_t::Pkmn;
    }

    created_result_t<animation_t*> hot_load_animation(animation_context_t& ctx) {
        // read-only config
        assert(ctx._local_copy_config != nullptr);
        //const config::config_t& current_config = *ctx._local_copy_config;
        assert(ctx.shm != nullptr);
        animation_shared_memory_t& anim_shm = *ctx.shm;
        const int anim_index = anim_shm.anim_index;

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
            }break;
            case config::config_animation_sprite_sheet_layout_t::Dm: {
                bongocat_error_t error = bongocat_error_t::BONGOCAT_ERROR_INVALID_PARAM;
                dm_sprite_sheet_t result;
                switch (anim_shm.anim_dm_set) {
                    case config::config_animation_dm_set_t::None:
                        cleanup_animation(result);
                        error = bongocat_error_t::BONGOCAT_SUCCESS;
                        break;
                    case config::config_animation_dm_set_t::min_dm:{
                        if constexpr (features::EnableMinDmEmbeddedAssets) {
                            auto [l_result, l_error] = load_min_dm_sprite_sheet(ctx, anim_index);
                            result = bongocat::move(l_result);
                            error = bongocat::move(l_error);
                        }
                    }break;
                    case config::config_animation_dm_set_t::dm:{
                        if constexpr (features::EnableFullDmEmbeddedAssets) {
                            auto [l_result, l_error] = load_dm_sprite_sheet(ctx, anim_index);
                            result = bongocat::move(l_result);
                            error = bongocat::move(l_error);
                        }
                    }break;
                    case config::config_animation_dm_set_t::dm20:{
                        if constexpr (features::EnableDm20EmbeddedAssets) {
                            auto [l_result, l_error] = load_dm20_sprite_sheet(ctx, anim_index);
                            result = bongocat::move(l_result);
                            error = bongocat::move(l_error);
                        }
                    }break;
                    case config::config_animation_dm_set_t::dmx:{
                        if constexpr (features::EnableDmxEmbeddedAssets) {
                            auto [l_result, l_error] = load_dmx_sprite_sheet(ctx, anim_index);
                            result = bongocat::move(l_result);
                            error = bongocat::move(l_error);
                        }
                    }break;
                    case config::config_animation_dm_set_t::pen:{
                        if constexpr (features::EnablePenEmbeddedAssets) {
                            auto [l_result, l_error] = load_pen_sprite_sheet(ctx, anim_index);
                            result = bongocat::move(l_result);
                            error = bongocat::move(l_error);
                        }
                    }break;
                    case config::config_animation_dm_set_t::pen20:{
                        if constexpr (features::EnablePen20EmbeddedAssets) {
                            auto [l_result, l_error] = load_pen20_sprite_sheet(ctx, anim_index);
                            result = bongocat::move(l_result);
                            error = bongocat::move(l_error);
                        }
                    }break;
                    case config::config_animation_dm_set_t::dmc:{
                        if constexpr (features::EnableDmcEmbeddedAssets) {
                            auto [l_result, l_error] = load_dmc_sprite_sheet(ctx, anim_index);
                            result = bongocat::move(l_result);
                            error = bongocat::move(l_error);
                        }
                    }break;
                    case config::config_animation_dm_set_t::dmall:{
                        if constexpr (features::EnableDmAllEmbeddedAssets) {
                            auto [l_result, l_error] = load_dmall_sprite_sheet(ctx, anim_index);
                            result = bongocat::move(l_result);
                            error = bongocat::move(l_error);
                        }
                    }break;
                }
                if (error != bongocat_error_t::BONGOCAT_SUCCESS) {
                    return error;
                }
                anim_shm.anim = bongocat::move(result);
            }break;
            case config::config_animation_sprite_sheet_layout_t::Pkmn:
                if constexpr (features::EnablePkmnEmbeddedAssets) {
                    auto [result, error] = load_pkmn_sprite_sheet(ctx, anim_index);
                    if (error != bongocat_error_t::BONGOCAT_SUCCESS) {
                        return error;
                    }
                    anim_shm.anim = bongocat::move(result);
                }
                break;
            case config::config_animation_sprite_sheet_layout_t::MsAgent:
                if constexpr (features::EnableMsAgentEmbeddedAssets) {
                    auto [result, error] = load_ms_agent_sprite_sheet(ctx, anim_index);
                    if (error != bongocat_error_t::BONGOCAT_SUCCESS) {
                        return error;
                    }
                    anim_shm.anim = bongocat::move(result);
                }
                break;
            /// @NOTE(assets): 6. add hot reload asset
        }

        created_result_t<animation_t*> ret;
        ret.result = &get_current_animation(ctx);
        ret.error = bongocat_error_t::BONGOCAT_SUCCESS;
        return ret;
    }

    animation_t& get_current_animation(animation_context_t& ctx) {
        // fallback sprite
        static animation_t none_sprite_sheet{};

        // read-only config
        assert(ctx._local_copy_config != nullptr);
        //const config::config_t& current_config = *ctx._local_copy_config;
        assert(ctx.shm != nullptr);
        animation_shared_memory_t& anim_shm = *ctx.shm;
        const int anim_index = anim_shm.anim_index;

        switch (anim_shm.anim_type) {
            case config::config_animation_sprite_sheet_layout_t::None:
                return none_sprite_sheet;
            case config::config_animation_sprite_sheet_layout_t::Bongocat: {
                if (features::EnableLazyLoadAssets) {
                    assert(anim_shm.anim.type == animation_t::Type::Bongocat);
                    return anim_shm.anim;
                }
                assert(anim_index >= 0);
                return static_cast<size_t>(anim_index) < anim_shm.bongocat_anims.count ? anim_shm.bongocat_anims[static_cast<size_t>(anim_index)] : none_sprite_sheet;
            }
            case config::config_animation_sprite_sheet_layout_t::Dm: {
                switch (anim_shm.anim_dm_set) {
                    case config::config_animation_dm_set_t::None:
                        return none_sprite_sheet;
                    case config::config_animation_dm_set_t::min_dm:
                        if (features::EnableLazyLoadAssets) {
                            assert(anim_shm.anim.type == animation_t::Type::Dm);
                            return anim_shm.anim;
                        }
                        assert(anim_index >= 0);
                        return static_cast<size_t>(anim_index) < anim_shm.min_dm_anims.count ? anim_shm.min_dm_anims[static_cast<size_t>(anim_index)] : none_sprite_sheet;
                    case config::config_animation_dm_set_t::dm:
                        if (features::EnableLazyLoadAssets) {
                            assert(anim_shm.anim.type == animation_t::Type::Dm);
                            return anim_shm.anim;
                        }
                        return static_cast<size_t>(anim_index) < anim_shm.dm_anims.count ? anim_shm.dm_anims[static_cast<size_t>(anim_index)] : none_sprite_sheet;
                    case config::config_animation_dm_set_t::dm20:
                        if (features::EnableLazyLoadAssets) {
                            assert(anim_shm.anim.type == animation_t::Type::Dm);
                            return anim_shm.anim;
                        }
                        assert(anim_index >= 0);
                        return static_cast<size_t>(anim_index) < anim_shm.dm20_anims.count ? anim_shm.dm20_anims[static_cast<size_t>(anim_index)] : none_sprite_sheet;
                    case config::config_animation_dm_set_t::dmx:
                        if (features::EnableLazyLoadAssets) {
                            assert(anim_shm.anim.type == animation_t::Type::Dm);
                            return anim_shm.anim;
                        }
                        assert(anim_index >= 0);
                        return static_cast<size_t>(anim_index) < anim_shm.dmx_anims.count ? anim_shm.dmx_anims[static_cast<size_t>(anim_index)] : none_sprite_sheet;
                    case config::config_animation_dm_set_t::pen:
                        if (features::EnableLazyLoadAssets) {
                            assert(anim_shm.anim.type == animation_t::Type::Dm);
                            return anim_shm.anim;
                        }
                        return static_cast<size_t>(anim_index) < anim_shm.pen_anims.count ? anim_shm.pen_anims[static_cast<size_t>(anim_index)] : none_sprite_sheet;
                    case config::config_animation_dm_set_t::pen20:
                        if (features::EnableLazyLoadAssets) {
                            assert(anim_shm.anim.type == animation_t::Type::Dm);
                            return anim_shm.anim;
                        }
                        assert(anim_index >= 0);
                        return static_cast<size_t>(anim_index) < anim_shm.pen20_anims.count ? anim_shm.pen20_anims[static_cast<size_t>(anim_index)] : none_sprite_sheet;
                    case config::config_animation_dm_set_t::dmc:
                        if (features::EnableLazyLoadAssets) {
                            assert(anim_shm.anim.type == animation_t::Type::Dm);
                            return anim_shm.anim;
                        }
                        assert(anim_index >= 0);
                        return static_cast<size_t>(anim_index) < anim_shm.dmc_anims.count ? anim_shm.dmc_anims[static_cast<size_t>(anim_index)] : none_sprite_sheet;
                    case config::config_animation_dm_set_t::dmall:
                        if (features::EnableLazyLoadAssets) {
                            assert(anim_shm.anim.type == animation_t::Type::Dm);
                            return anim_shm.anim;
                        }
                        assert(anim_index >= 0);
                        return static_cast<size_t>(anim_index) < anim_shm.dmall_anims.count ? anim_shm.dmall_anims[static_cast<size_t>(anim_index)] : none_sprite_sheet;
                }
            }break;
            case config::config_animation_sprite_sheet_layout_t::Pkmn:
                if (features::EnableLazyLoadAssets) {
                    assert(anim_shm.anim.type == animation_t::Type::Pkmn);
                    return anim_shm.anim;
                }
                assert(anim_index >= 0);
                return static_cast<size_t>(anim_index) < anim_shm.pkmn_anims.count ? anim_shm.pkmn_anims[static_cast<size_t>(anim_index)] : none_sprite_sheet;
            case config::config_animation_sprite_sheet_layout_t::MsAgent:
                if (features::EnableLazyLoadAssets) {
                    assert(anim_shm.anim.type == animation_t::Type::MsAgent);
                    return anim_shm.anim;
                }
                assert(anim_index >= 0);
                return static_cast<size_t>(anim_index) < anim_shm.ms_anims.count ? anim_shm.ms_anims[static_cast<size_t>(anim_index)] : none_sprite_sheet;
        }

        return none_sprite_sheet;
    }

    // =============================================================================
    // PUBLIC API IMPLEMENTATION
    // =============================================================================

    created_result_t<AllocatedMemory<animation_session_t>> create(const config::config_t& config) {
        using namespace assets;
        BONGOCAT_LOG_INFO("Initializing animation system");
        AllocatedMemory<animation_session_t> ret = make_allocated_memory<animation_session_t>();
        assert(ret != nullptr);
        if (ret == nullptr) {
            return bongocat_error_t::BONGOCAT_ERROR_MEMORY;
        }

        ret->_config = &config;

        // Initialize shared memory
        ret->anim.shm = platform::make_allocated_mmap<animation_shared_memory_t>();
        if (!ret->anim.shm) {
            BONGOCAT_LOG_ERROR("Failed to create shared memory for animation system: %s", strerror(errno));
            return bongocat_error_t::BONGOCAT_ERROR_MEMORY;
        }
        assert(ret->anim.shm != nullptr);

        // Initialize shared memory for local config
        ret->anim._local_copy_config = platform::make_allocated_mmap<config::config_t>();
        if (!ret->anim._local_copy_config) {
            BONGOCAT_LOG_ERROR("Failed to create shared memory for animation system: %s", strerror(errno));
            return bongocat_error_t::BONGOCAT_ERROR_MEMORY;
        }
        assert(ret->anim._local_copy_config != nullptr);
        //config_set_defaults(*ctx._local_copy_config);
        *ret->anim._local_copy_config = config;
        ret->anim.shm->animation_player_result.sprite_sheet_col = config.idle_frame;  // initial frame

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

        ret->anim.update_config_efd = platform::FileDescriptor(eventfd(0, EFD_NONBLOCK | EFD_CLOEXEC));
        if (ret->anim.update_config_efd._fd < 0) {
            BONGOCAT_LOG_ERROR("Failed to create notify pipe for input update config: %s", strerror(errno));
            return bongocat_error_t::BONGOCAT_ERROR_FILE_IO;
        }

        [[maybe_unused]] const auto t0 = platform::get_current_time_us();
        /// @TODO: async assets load
        // Initialize embedded images/animations
        if constexpr (features::EnableLazyLoadAssets) {
            hot_load_animation(ret->anim);
        }
        if constexpr (!features::EnableLazyLoadAssets || features::EnablePreloadAssets) {
            // preload assets
            if constexpr (features::EnableBongocatEmbeddedAssets) {
                // Load Bongocat
                if (should_load_bongocat(config)) {
                    BONGOCAT_LOG_INFO("Load bongocat sprite sheet frames: %d", BONGOCAT_EMBEDDED_IMAGES_COUNT);
                    assert(ret->anim.shm != nullptr);
                    animation_context_t& ctx = ret->anim; // alias for inits in includes

                    ctx.shm->bongocat_anims = platform::make_allocated_mmap_array<animation_t>(BONGOCAT_ANIM_COUNT);

                    init_bongocat_anim(ctx, BONGOCAT_ANIM_INDEX, get_bongocat_sprite, BONGOCAT_EMBEDDED_IMAGES_COUNT);
                }
            }

            if constexpr (features::EnableDmEmbeddedAssets) {
                // Load dm
                if (should_load_dm(config)) {
                    BONGOCAT_LOG_INFO("Load dm sprite sheets: %d", DM_ANIMATIONS_COUNT);
                    assert(ret->anim.shm != nullptr);
                    animation_context_t& ctx = ret->anim; // alias for inits in includes

                    if constexpr (features::EnableMinDmEmbeddedAssets) {
                        BONGOCAT_LOG_INFO("Init min_dm sprite sheets: %d", MIN_DM_ANIM_COUNT);
                        ctx.shm->min_dm_anims = platform::make_allocated_mmap_array<animation_t>(MIN_DM_ANIM_COUNT);
#ifdef FEATURE_MIN_DM_EMBEDDED_ASSETS
                        //init_dm_anim(ctx, DM_AGUMON_ANIM_INDEX, get_dm_sprite_sheet(DM_AGUMON_ANIM_INDEX), DM_AGUMON_SPRITE_SHEET_COLS, DM_AGUMON_SPRITE_SHEET_ROWS);
#include "min_dm_init_dm_anim.cpp.inl"
#endif
                    }
                    if constexpr (features::EnableFullDmEmbeddedAssets) {
                        BONGOCAT_LOG_INFO("Init dm sprite sheets: %d", DM_ANIM_COUNT);
                        ctx.shm->dm_anims = platform::make_allocated_mmap_array<animation_t>(DM_ANIM_COUNT);
#ifdef FEATURE_DM_EMBEDDED_ASSETS
                        // dm
#include "dm_init_dm_anim.cpp.inl"
#endif
                    }
                    if constexpr (features::EnableDm20EmbeddedAssets) {
                        BONGOCAT_LOG_INFO("Init dm20 sprite sheets: %d", DM20_ANIM_COUNT);
                        ctx.shm->dm20_anims = platform::make_allocated_mmap_array<animation_t>(DM20_ANIM_COUNT);
#ifdef FEATURE_DM20_EMBEDDED_ASSETS
                        // dm20
#include "dm20_init_dm_anim.cpp.inl"
#endif
                    }
                    if constexpr (features::EnableDmxEmbeddedAssets) {
                        BONGOCAT_LOG_INFO("Init dmx sprite sheets: %d", DMX_ANIM_COUNT);
                        ctx.shm->dmx_anims = platform::make_allocated_mmap_array<animation_t>(DMX_ANIM_COUNT);
#ifdef FEATURE_DMX_EMBEDDED_ASSETS
                        // dmx
#include "dmx_init_dm_anim.cpp.inl"
#endif
                    }
                    if constexpr (features::EnablePenEmbeddedAssets) {
                        BONGOCAT_LOG_INFO("Init pen sprite sheets: %d", PEN20_ANIM_COUNT);
                        //ctx.shm->pen_anims = platform::make_allocated_mmap_array<animation_t>(PEN_ANIM_COUNT);
#ifdef FEATURE_PEN_EMBEDDED_ASSETS
                        // pen
#include "pen_init_dm_anim.cpp.inl"
#endif
                    }
                    if constexpr (features::EnablePen20EmbeddedAssets) {
                        BONGOCAT_LOG_INFO("Init pen20 sprite sheets: %d", PEN20_ANIM_COUNT);
                        //ctx.shm->pen20_anims = platform::make_allocated_mmap_array<animation_t>(PEN20_ANIM_COUNT);
#ifdef FEATURE_PEN20_EMBEDDED_ASSETS
                        // pen20
#include "pen20_init_dm_anim.cpp.inl"
#endif
                    }
                    if constexpr (features::EnableDmcEmbeddedAssets) {
                        BONGOCAT_LOG_INFO("Init dmc sprite sheets: %d", DMC_ANIM_COUNT);
                        ctx.shm->dmc_anims = platform::make_allocated_mmap_array<animation_t>(DMC_ANIM_COUNT);
#ifdef FEATURE_DMC_EMBEDDED_ASSETS
                        // dmc
#include "dmc_init_dm_anim.cpp.inl"
#endif
                    }
                    if constexpr (features::EnableDmAllEmbeddedAssets) {
                        BONGOCAT_LOG_INFO("Init dmall sprite sheets: %d", DMALL_ANIM_COUNT);
                        ctx.shm->dmall_anims = platform::make_allocated_mmap_array<animation_t>(DMALL_ANIM_COUNT);
#ifdef FEATURE_DMALL_EMBEDDED_ASSETS
                        // dmall
#include "dmall_init_dm_anim.cpp.inl"
#endif
                    }
                }
            }

            if constexpr (features::EnableMsAgentEmbeddedAssets) {
                // Load Ms Pets (Clippy)
                if (should_load_ms_agent(config)) {
                    BONGOCAT_LOG_INFO("Load MS agent sprite sheets: %d", MS_AGENTS_ANIM_COUNT);
                    assert(ret->anim.shm != nullptr);
                    animation_context_t& ctx = ret->anim; // alias for inits in includes

                    ctx.shm->ms_anims = platform::make_allocated_mmap_array<animation_t>(MS_AGENTS_ANIM_COUNT);

                    // clippy
                    init_ms_agent_anim(ctx, CLIPPY_ANIM_INDEX, get_ms_agent_sprite_sheet(CLIPPY_ANIM_INDEX), CLIPPY_SPRITE_SHEET_COLS, CLIPPY_SPRITE_SHEET_ROWS, get_ms_agent_animation_indices(CLIPPY_ANIM_INDEX));
#ifdef FEATURE_MORE_MS_AGENT_EMBEDDED_ASSETS
                    /// @NOTE(config): add more MS Pets here
                    init_ms_agent_anim(ctx, LINKS_ANIM_INDEX, get_ms_agent_sprite_sheet(LINKS_ANIM_INDEX), LINKS_SPRITE_SHEET_COLS, LINKS_SPRITE_SHEET_ROWS, get_ms_agent_animation_indices(LINKS_ANIM_INDEX));
                    init_ms_agent_anim(ctx, ROVER_ANIM_INDEX, get_ms_agent_sprite_sheet(ROVER_ANIM_INDEX), ROVER_SPRITE_SHEET_COLS, ROVER_SPRITE_SHEET_ROWS, get_ms_agent_animation_indices(ROVER_ANIM_INDEX));
                    init_ms_agent_anim(ctx, MERLIN_ANIM_INDEX, get_ms_agent_sprite_sheet(MERLIN_ANIM_INDEX), MERLIN_SPRITE_SHEET_COLS, MERLIN_SPRITE_SHEET_ROWS, get_ms_agent_animation_indices(MERLIN_ANIM_INDEX));
#endif
                }
            }

            if constexpr (features::EnablePkmnEmbeddedAssets) {
                // Load pkmn
                if (should_load_pkmn(config)) {
                    BONGOCAT_LOG_INFO("Load pkmn sprite sheets: %d", PKMN_ANIM_COUNT);
                    assert(ret->anim.shm != nullptr);
                    animation_context_t& ctx = ret->anim; // alias for inits in includes

                    ctx.shm->pkmn_anims = platform::make_allocated_mmap_array<animation_t>(PKMN_ANIM_COUNT);
#ifdef FEATURE_PKMN_EMBEDDED_ASSETS
                    // pkmn
#include "pkmn_init_pkmn_anim.cpp.inl"
#endif
                }
            }

            /// @NOTE(assets): 7. add pre-load asset
        }
        [[maybe_unused]] const auto t1 = platform::get_current_time_us();

        // init anim
        ret->anim._rng = platform::random_xoshiro128(platform::slow_rand());

        BONGOCAT_LOG_INFO("Animation system initialized successfully with embedded assets; load assets in %.3fms (%.6fsec)", static_cast<double>(t1 - t0) / 1000.0, static_cast<double>(t1 - t0) / 1000000.0);
        return ret;
    }

    void stop(animation_context_t& ctx) {
        atomic_store(&ctx._animation_running, false);
        if (ctx._anim_thread) {
            BONGOCAT_LOG_DEBUG("Stopping animation thread");
            // Wait for thread to finish gracefully
            //pthread_cancel(ctx->_anim_thread);
            if (platform::stop_thread_graceful_or_cancel(ctx._anim_thread, ctx._animation_running) != 0) {
                BONGOCAT_LOG_ERROR("Failed to join animation thread: %s", strerror(errno));
            }
            BONGOCAT_LOG_DEBUG("Animation thread terminated");
        }
        ctx._anim_thread = 0;

        ctx.config_updated.notify_all();
    }
}
