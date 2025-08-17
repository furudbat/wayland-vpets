#include "graphics/embedded_assets.h"
#include "graphics/embedded_assets/bongocat.hpp"
#include "graphics/animation_context.h"
#include "graphics/animation.h"
#include "platform/wayland.h"
#include "utils/memory.h"
#include <ctime>
#include <pthread.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <cassert>
#include <sys/eventfd.h>
#include <unistd.h>

#include "load_images.inl.h"

namespace bongocat::animation {
    // =============================================================================
    // PUBLIC API IMPLEMENTATION
    // =============================================================================

    created_result_t<animation_session_t> create(const config::config_t& config) {
        using namespace assets;
        BONGOCAT_LOG_INFO("Initializing animation system");
        animation_session_t ret;

        // Initialize shared memory
        ret.anim.shm = platform::make_allocated_mmap<animation_shared_memory_t>();
        if (ret.anim.shm == nullptr) {
            BONGOCAT_LOG_ERROR("Failed to create shared memory for animation system: %s", strerror(errno));
            return bongocat_error_t::BONGOCAT_ERROR_MEMORY;
        }
        assert(ret.anim.shm != nullptr);

        // Initialize shared memory for local config
        ret.anim._local_copy_config = platform::make_allocated_mmap<config::config_t>();
        if (ret.anim._local_copy_config == nullptr) {
            BONGOCAT_LOG_ERROR("Failed to create shared memory for animation system: %s", strerror(errno));
            return bongocat_error_t::BONGOCAT_ERROR_MEMORY;
        }
        assert(ret.anim._local_copy_config != nullptr);
        //config_set_defaults(*ctx._local_copy_config);
        update_config(ret.anim, config);
        ret.anim.shm->anim_frame_index = config.idle_frame;  // initial frame

        ret.trigger_efd = platform::FileDescriptor(eventfd(0, EFD_NONBLOCK | EFD_CLOEXEC));
        if (ret.trigger_efd._fd < 0) {
            BONGOCAT_LOG_ERROR("Failed to create notify pipe for animation trigger: %s", strerror(errno));
            return bongocat_error_t::BONGOCAT_ERROR_FILE_IO;
        }

        ret.render_efd = platform::FileDescriptor(eventfd(0, EFD_NONBLOCK | EFD_CLOEXEC));
        if (ret.render_efd._fd < 0) {
            BONGOCAT_LOG_ERROR("Failed to create notify pipe for animation render: %s", strerror(errno));
            return bongocat_error_t::BONGOCAT_ERROR_FILE_IO;
        }

        // Initialize embedded images data
        const embedded_image_t* bongocat_embedded_images = init_bongocat_embedded_images();
        assert(ret.anim.shm != nullptr);
        const auto result = anim_load_embedded_images_into_sprite_sheet(ret.anim.shm->anims[BONGOCAT_ANIM_INDEX].sprite_sheet, bongocat_embedded_images, BONGOCAT_EMBEDDED_IMAGES_COUNT);
        if (result != bongocat_error_t::BONGOCAT_SUCCESS) {
            BONGOCAT_LOG_ERROR("Load Bongocat images failed");
            //return result;
            // ignore error ?
        }
        BONGOCAT_LOG_INFO("Bongocat loaded into sprite sheet");

#ifndef FEATURE_INCLUDE_ONLY_BONGOCAT_EMBEDDED_ASSETS
        const embedded_image_t* digimon_sprite_sheet_embedded_images = init_digimon_embedded_images();
        BONGOCAT_LOG_INFO("Load more sprite sheets: %i", DIGIMON_SPRITE_SHEET_EMBEDDED_IMAGES_COUNT);
        do {
            animation_context_t& ctx = ret.anim; // alias for inits in includes
#ifdef FEATURE_INCLUDE_DM_EMBEDDED_ASSETS

#else
            //init_digimon_anim(ctx, DM_AGUMON_ANIM_INDEX, digimon_sprite_sheet_embedded_images[DM_AGUMON_ANIM_INDEX], DM_AGUMON_SPRITE_SHEET_COLS, DM_AGUMON_SPRITE_SHEET_ROWS);
#include "embedded_assets/min_dm_init_digimon_anim.cpp.inl"
#endif
        } while (false);
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