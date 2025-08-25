#include "graphics/embedded_assets.h"
#include "graphics/animation_context.h"
#include "graphics/embedded_assets/bongocat.hpp"
#include "graphics/embedded_assets/clippy.hpp"
#include "graphics/animation.h"
#include "platform/wayland.h"
#include "utils/memory.h"
#include "load_images.h"
#include <ctime>
#include <pthread.h>
#include <sys/stat.h>
#include <cassert>
#include <sys/eventfd.h>

namespace bongocat::animation {
    [[maybe_unused]] static bool should_load_bongocat([[maybe_unused]] const config::config_t& config) {
#ifdef FEATURE_PRELOAD_ASSETS
        return true;
#else
        return config.animation_sprite_sheet_layout == config::config_animation_sprite_sheet_layout_t::Bongocat;
#endif
    }
    [[maybe_unused]] static bool should_load_dm([[maybe_unused]] const config::config_t& config) {
#ifdef FEATURE_PRELOAD_ASSETS
        return true;
#else
        return config.animation_sprite_sheet_layout == config::config_animation_sprite_sheet_layout_t::Dm;
#endif
    }
    [[maybe_unused]] static bool should_load_ms_pet([[maybe_unused]] const config::config_t& config) {
#ifdef FEATURE_PRELOAD_ASSETS
        return true;
#else
        return config.animation_sprite_sheet_layout == config::config_animation_sprite_sheet_layout_t::MsAgent;
#endif
    }

    // =============================================================================
    // PUBLIC API IMPLEMENTATION
    // =============================================================================

    created_result_t<AllocatedMemory<animation_session_t>> create(const config::config_t& config) {
        using namespace assets;
        BONGOCAT_LOG_INFO("Initializing animation system");
        AllocatedMemory<animation_session_t> ret = make_allocated_memory<animation_session_t>();

        assert(ret != nullptr);
        ret->_config = &config;

        // Initialize shared memory
        ret->anim.shm = platform::make_allocated_mmap<animation_shared_memory_t>();
        if (ret->anim.shm == nullptr) {
            BONGOCAT_LOG_ERROR("Failed to create shared memory for animation system: %s", strerror(errno));
            return bongocat_error_t::BONGOCAT_ERROR_MEMORY;
        }
        assert(ret->anim.shm != nullptr);

        // Initialize shared memory for local config
        ret->anim._local_copy_config = platform::make_allocated_mmap<config::config_t>();
        if (ret->anim._local_copy_config == nullptr) {
            BONGOCAT_LOG_ERROR("Failed to create shared memory for animation system: %s", strerror(errno));
            return bongocat_error_t::BONGOCAT_ERROR_MEMORY;
        }
        assert(ret->anim._local_copy_config != nullptr);
        //config_set_defaults(*ctx._local_copy_config);
        update_config(ret->anim, config);
        ret->anim.shm->animation_player_data.frame_index = config.idle_frame;  // initial frame

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

        ret->update_config_efd = platform::FileDescriptor(eventfd(0, EFD_NONBLOCK | EFD_CLOEXEC));
        if (ret->update_config_efd._fd < 0) {
            BONGOCAT_LOG_ERROR("Failed to create notify pipe for animation update config: %s", strerror(errno));
            return bongocat_error_t::BONGOCAT_ERROR_FILE_IO;
        }

        // Initialize embedded images data
        /// @TODO: async assets load

        // Load Bongocat
#ifdef FEATURE_BONGOCAT_EMBEDDED_ASSETS
        if (should_load_bongocat(config)) {
            BONGOCAT_LOG_INFO("Load sprite sheet frames: %i", BONGOCAT_EMBEDDED_IMAGES_COUNT);
            assert(ret->anim.shm != nullptr);
            animation_context_t& ctx = ret->anim; // alias for inits in includes

            const auto result = init_bongocat_anim(ctx, BONGOCAT_ANIM_INDEX, get_bongocat_sprite, BONGOCAT_EMBEDDED_IMAGES_COUNT);
            if (result != bongocat_error_t::BONGOCAT_SUCCESS) {
                BONGOCAT_LOG_ERROR("Load Bongocat images failed");
                //return result;
                // ignore error ?
            }
            BONGOCAT_LOG_INFO("Bongocat loaded into sprite sheet");
        }
#endif


        // Load dm
#ifdef FEATURE_ENABLE_DM_EMBEDDED_ASSETS
        if (should_load_dm(config)) {
            BONGOCAT_LOG_INFO("Load more sprite sheets: %i", DM_SPRITE_SHEET_EMBEDDED_IMAGES_COUNT);
            assert(ret->anim.shm != nullptr);
            animation_context_t& ctx = ret->anim; // alias for inits in includes

#ifdef FEATURE_MIN_DM_EMBEDDED_ASSETS
            //init_dm_anim(ctx, DM_AGUMON_ANIM_INDEX, get_min_dm_sprite_sheet(DM_AGUMON_ANIM_INDEX), DM_AGUMON_SPRITE_SHEET_COLS, DM_AGUMON_SPRITE_SHEET_ROWS);
#include "embedded_assets/min_dm_init_dm_anim.cpp.inl"

#endif

            // dm
#ifdef FEATURE_DM_EMBEDDED_ASSETS
#include "embedded_assets/dm_init_dm_anim.cpp.inl"
#endif
            // dm20
#ifdef FEATURE_DM_EMBEDDED_ASSETS
#include "embedded_assets/dm20_init_dm_anim.cpp.inl"
#endif
            // dmc
#ifdef FEATURE_DMC_EMBEDDED_ASSETS
#include "embedded_assets/dmc_init_dm_anim.cpp.inl"
#endif
            // dmx
#ifdef FEATURE_DMX_EMBEDDED_ASSETS
#include "embedded_assets/dmx_init_dm_anim.cpp.inl"
#endif
            // pen20
#ifdef FEATURE_PEN20_EMBEDDED_ASSETS
#include "embedded_assets/pen20_init_dm_anim.cpp.inl"
#endif
        }
#endif


        // Load Ms Pets (Clippy)
#ifdef FEATURE_MS_AGENT_EMBEDDED_ASSETS
        if (should_load_ms_pet(config)) {
            BONGOCAT_LOG_INFO("Load more sprite sheets: %i", MS_AGENTS_SPRITE_SHEET_EMBEDDED_IMAGES_COUNT);
            assert(ret->anim.shm != nullptr);
            animation_context_t& ctx = ret->anim; // alias for inits in includes

            // clippy
            init_ms_pet_anim(ctx, CLIPPY_ANIM_INDEX, get_ms_agent_sprite_sheet(CLIPPY_ANIM_INDEX), CLIPPY_SPRITE_SHEET_COLS, CLIPPY_SPRITE_SHEET_ROWS);
        }
#endif

        BONGOCAT_LOG_INFO("Animation system initialized successfully with embedded assets");
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
    }
}