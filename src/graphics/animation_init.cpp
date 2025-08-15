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

void set_defaults_animation_shared_memory(animation_shared_memory_t& shm) {
    /*
    shm.time_until_next_frame_ms = 0;
    shm.anim_index = BONGOCAT_ANIM_INDEX;
    shm.anim_frame_index = 0;
    // empty animations
    for (size_t i = 0;i < ANIMS_COUNT; i++) {
        shm.anims[i].sprite_sheet.sprite_sheet_width = 0;
        shm.anims[i].sprite_sheet.sprite_sheet_height = 0;
        shm.anims[i].sprite_sheet.channels = RGBA_CHANNELS;
        shm.anims[i].sprite_sheet.pixels = nullptr;
        shm.anims[i].sprite_sheet.frame_width = 0;
        shm.anims[i].sprite_sheet.frame_height = 0;
        shm.anims[i].sprite_sheet.total_frames = 0;
        for (size_t j = 0; j < MAX_NUM_FRAMES; j++) {
            shm.anims[i].sprite_sheet.frames[j] = { .valid = false, .col = 0, .row = 0};
        }
    }
    */
    shm = {};
}

// =============================================================================
// PUBLIC API IMPLEMENTATION
// =============================================================================

bongocat_error_t animation_init(animation_trigger_context_t& trigger_ctx, animation_context_t& ctx, const config_t& config) {
    BONGOCAT_LOG_INFO("Initializing animation system");

    ctx._animation_running = false;
    pthread_mutex_init(&ctx.anim_lock.pt_mutex, nullptr);

    // Initialize shared memory
    ctx.shm = make_allocated_mmap<animation_shared_memory_t>();
    if (!ctx.shm) {
        BONGOCAT_LOG_ERROR("Failed to create shared memory for animation system: %s", strerror(errno));
        return bongocat_error_t::BONGOCAT_ERROR_MEMORY;
    }
    assert(ctx.shm);
    set_defaults_animation_shared_memory(*ctx.shm);

    // Initialize shared memory for local config
    ctx._local_copy_config = make_allocated_mmap<config_t>();
    if (!ctx._local_copy_config) {
        BONGOCAT_LOG_ERROR("Failed to create shared memory for animation system: %s", strerror(errno));
        ctx.shm._release();
        return bongocat_error_t::BONGOCAT_ERROR_MEMORY;
    }
    assert(ctx._local_copy_config);
    //config_set_defaults(*ctx._local_copy_config);
    animation_update_config(ctx, config);
    ctx.shm->anim_frame_index = config.idle_frame;  // initial frame

    trigger_ctx.trigger_efd = FileDescriptor(eventfd(0, EFD_NONBLOCK | EFD_CLOEXEC));
    if (trigger_ctx.trigger_efd._fd < 0) {
        BONGOCAT_LOG_ERROR("Failed to create notify pipe for animation trigger: %s", strerror(errno));
        ctx._local_copy_config._release();
        ctx.shm._release();
        return bongocat_error_t::BONGOCAT_ERROR_FILE_IO;
    }

    trigger_ctx.render_efd = FileDescriptor(eventfd(0, EFD_NONBLOCK | EFD_CLOEXEC));
    if (trigger_ctx.render_efd._fd < 0) {
        BONGOCAT_LOG_ERROR("Failed to create notify pipe for animation render: %s", strerror(errno));
        trigger_ctx.trigger_efd._close();
        ctx._local_copy_config._release();
        ctx.shm._release();
        return bongocat_error_t::BONGOCAT_ERROR_FILE_IO;
    }
    
    // Initialize embedded images data
    const embedded_image_t* bongocat_embedded_images = init_bongocat_embedded_images();
    const auto result = anim_load_embedded_images_into_sprite_sheet(&ctx.shm->anims[BONGOCAT_ANIM_INDEX].sprite_sheet, bongocat_embedded_images, BONGOCAT_EMBEDDED_IMAGES_COUNT);
    if (result != bongocat_error_t::BONGOCAT_SUCCESS) {
        BONGOCAT_LOG_ERROR("Load Bongocat images failed");
        /*
        trigger_ctx.render_efd._close();
        trigger_ctx.trigger_efd._close();
        ctx._local_copy_config._release();
        ctx.shm._release();
        return result;
        */
        // ignore error ?
    }
    BONGOCAT_LOG_INFO("Bongocat loaded into sprite sheet");

#ifndef FEATURE_INCLUDE_ONLY_BONGOCAT_EMBEDDED_ASSETS
    const embedded_image_t* digimon_sprite_sheet_embedded_images = init_digimon_embedded_images();
    BONGOCAT_LOG_INFO("Load more sprite sheets: %i", DIGIMON_SPRITE_SHEET_EMBEDDED_IMAGES_COUNT);

#ifdef FEATURE_INCLUDE_DM_EMBEDDED_ASSETS

#else
    //init_digimon_anim(ctx, DM_AGUMON_ANIM_INDEX, digimon_sprite_sheet_embedded_images[DM_AGUMON_ANIM_INDEX], DM_AGUMON_SPRITE_SHEET_COLS, DM_AGUMON_SPRITE_SHEET_ROWS);
    #include "embedded_assets/min_dm_init_digimon_anim.cpp.inl"
#endif
#endif
    
    BONGOCAT_LOG_INFO("Animation system initialized successfully with embedded assets");
    return bongocat_error_t::BONGOCAT_SUCCESS;
}

void animation_stop(animation_context_t& ctx) {
    atomic_store(&ctx._animation_running, false);
    if (ctx._anim_thread) {
        BONGOCAT_LOG_DEBUG("Stopping animation thread");
        // Wait for thread to finish gracefully
        //pthread_cancel(ctx->_anim_thread);
        if (stop_thread_graceful_or_cancel(ctx._anim_thread, ctx._animation_running) != 0) {
            BONGOCAT_LOG_ERROR("Failed to join animation thread: %s", strerror(errno));
        }
        BONGOCAT_LOG_DEBUG("Animation thread terminated");
    }
    ctx._anim_thread = 0;
}

void animation_cleanup(animation_trigger_context_t& trigger_ctx, animation_context_t& ctx) {
    animation_stop(ctx);

    // Cleanup mutex
    pthread_mutex_destroy(&ctx.anim_lock.pt_mutex);

    trigger_ctx.trigger_efd._close();
    trigger_ctx.render_efd._close();

    ctx._local_copy_config._release();

    if (ctx.shm) {
        // Cleanup loaded images
        for (size_t i = 0;i < ANIMS_COUNT; i++) {
            anim_free_pixels(ctx.shm->anims[i].sprite_sheet);
        }
        ctx.shm._release();
    }

    trigger_ctx._anim = nullptr;
    trigger_ctx._input = nullptr;
    
    BONGOCAT_LOG_DEBUG("Animation cleanup complete");
}