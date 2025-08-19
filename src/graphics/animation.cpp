#include "graphics/embedded_assets.h"
#include "graphics/embedded_assets_bongocat.h"
#include "graphics/embedded_assets_digimon.h"
#include "graphics/embedded_assets_clippy.h"
#include "graphics/animation_context.h"
#include "graphics/animation.h"
#include "platform/wayland.h"
#include "utils/time.h"
#include "utils/memory.h"
#include <ctime>
#include <pthread.h>
#include <sys/stat.h>
#include <cassert>
#include <climits>
#include <poll.h>
#include <unistd.h>

namespace bongocat::animation {
    // =============================================================================
    // GLOBAL STATE AND CONFIGURATION
    // =============================================================================

    inline static constexpr platform::time_ms_t POOL_MIN_TIMEOUT_MS = 5;
    inline static constexpr platform::time_ms_t POOL_MAX_TIMEOUT_MS = 1000;
    inline static constexpr size_t MAX_ATTEMPTS = 2048;
    static_assert(POOL_MAX_TIMEOUT_MS >= POOL_MIN_TIMEOUT_MS);


    static int rand_minmax(int min, int max) {
        return rand() % (max - min + 1) + min;
    }

    // =============================================================================
    // ANIMATION STATE MANAGEMENT MODULE
    // =============================================================================

    static bool is_sleep_time(const config::config_t& config) {
        time_t raw_time;
        tm time_info{};
        time(&raw_time);
        localtime_r(&raw_time, &time_info);

        const int now_minutes = time_info.tm_hour * 60 + time_info.tm_min;
        const int begin = config.sleep_begin.hour * 60 + config.sleep_begin.min;
        const int end = config.sleep_end.hour * 60 + config.sleep_end.min;

        // Normal range (e.g., 10:00–22:00): begin < end && (now_minutes >= begin && now_minutes < end)
        // Overnight range (e.g., 22:00–06:00): begin > end && (now_minutes >= begin || now_minutes < end)

        return (begin == end) ||
               (begin < end ? (now_minutes >= begin && now_minutes < end)
                            : (now_minutes >= begin || now_minutes < end));
    }

    struct animation_state_t {
        platform::timestamp_us_t hold_until_us{0};
        int test_counter{0};
        int test_interval_frames{0};
        platform::time_ns_t frame_time_ns{0};
    };

    static int anim_get_random_active_frame(animation_context_t& ctx, [[maybe_unused]] const platform::input::input_shared_memory_t& input_shm) {
        using namespace assets;
#ifdef FEATURE_INCLUDE_ONLY_BONGOCAT_EMBEDDED_ASSETS
        assert(ctx.shm != nullptr && ctx.shm != MAP_FAILED);
        const animation_shared_memory_t& anim_shm = *ctx.shm;

        const int current_frame = anim_shm.anim_frame_index;
        if (current_frame == 1) {
            return 2;
        }
        if (current_frame == 2) {
            return 1;
        }

        return rand_minmax(1, 2); // Frame 1 or 2 (active frames)
#else
        assert(ctx.shm != nullptr);
        const animation_shared_memory_t& anim_shm = *ctx.shm;

        const int current_frame = anim_shm.animation_player_data.frame_index;
        if (anim_shm.anim_index == BONGOCAT_ANIM_INDEX) {
            if (current_frame == 1) {
                return 2;
            } else if (current_frame == 2) {
                return 1;
            }
            return rand_minmax(1, 2); // Frame 1 or 2 (active frames)
        }

        // read-only config
        assert(ctx._local_copy_config != nullptr);
        const config::config_t& current_config = *ctx._local_copy_config;

        // toggle sleep frame (if 2 frame exists for sleeping)
        if (current_config.enable_scheduled_sleep && is_sleep_time(current_config)) {
            if (current_frame == DIGIMON_FRAME_SLEEP1) {
                if (anim_shm.anims[anim_shm.anim_index].digimon.sleep_2.valid) {
                    return DIGIMON_FRAME_SLEEP2;
                } else if (anim_shm.anims[anim_shm.anim_index].digimon.sleep1.valid) {
                    return DIGIMON_FRAME_SLEEP1;
                } else if (anim_shm.anims[anim_shm.anim_index].digimon.down1.valid) {
                    BONGOCAT_LOG_VERBOSE("No Sleeping Frame for %d", anim_shm.anim_index);
                    // fallback frame
                    return DIGIMON_FRAME_DOWN1;
                }
            } else if (current_frame == DIGIMON_FRAME_SLEEP2) {
                if (anim_shm.anims[anim_shm.anim_index].digimon.sleep1.valid) {
                    return DIGIMON_FRAME_SLEEP1;
                } else if (anim_shm.anims[anim_shm.anim_index].digimon.down1.valid) {
                    BONGOCAT_LOG_VERBOSE("No Sleeping Frame for %d", anim_shm.anim_index);
                    // fallback frame
                    return DIGIMON_FRAME_DOWN1;
                }
            }
        }

        // toggle frame
        if (current_frame == DIGIMON_FRAME_IDLE1) {
            if (input_shm.kpm > 0) {
                if (current_config.happy_kpm > 0 && input_shm.kpm >= current_config.happy_kpm) {
                    if (anim_shm.anims[anim_shm.anim_index].digimon.happy.valid) {
                        if (rand() % 100 < HAPPY_CHANCE_PERCENT) {
                            BONGOCAT_LOG_VERBOSE("Show Happy Frame at %d KPM", input_shm.kpm);
                            return DIGIMON_FRAME_HAPPY;
                        }
                    }
                }
            }

            return DIGIMON_FRAME_IDLE2;
        } else if (current_frame == DIGIMON_FRAME_IDLE2) {
            return DIGIMON_FRAME_IDLE1;
        }

        return rand_minmax(0, 1); // Frame 0 or 1 (active frames)
#endif
    }

    static bool anim_trigger_frame_change(animation_context_t& ctx,
                                          int new_frame, long duration_us, long current_time_us,
                                          animation_state_t& state) {
        // read-only config
        assert(ctx._local_copy_config != nullptr);
        const config::config_t& current_config = *ctx._local_copy_config;

        if (current_config.enable_debug) {
            BONGOCAT_LOG_VERBOSE("Animation frame change: %d (duration: %ld us)", new_frame, duration_us);
        }

        assert(ctx.shm != nullptr);
        const bool changed = ctx.shm->animation_player_data.frame_index != new_frame;
        ctx.shm->animation_player_data.frame_index = new_frame;
        if (changed) {
            state.hold_until_us = current_time_us + duration_us;
        }
        return changed;
    }

    static bool anim_handle_test_animation(animation_context_t& ctx, const platform::input::input_context_t& input, animation_state_t& state, platform::timestamp_us_t current_time_us) {
        // read-only config
        assert(ctx._local_copy_config != nullptr);
        const config::config_t& current_config = *ctx._local_copy_config;

        if (current_config.test_animation_interval_sec <= 0) {
            return false;
        }

        state.test_counter++;
        bool ret = false;
        if (state.test_counter > state.test_interval_frames) {
            assert(input.shm);
            const int new_frame = anim_get_random_active_frame(ctx, *input.shm.ptr);
            const platform::time_us_t duration_us = current_config.test_animation_duration_ms * 1000;

            BONGOCAT_LOG_VERBOSE("Test animation trigger");
            ret = anim_trigger_frame_change(ctx, new_frame, duration_us, current_time_us, state);
            state.test_counter = 0;
        }
        return ret;
    }

    static bool anim_handle_key_press(animation_session_t& animation_trigger_ctx, animation_state_t& state, platform::timestamp_us_t current_time_us) {
        assert(animation_trigger_ctx._input != nullptr);
        assert(animation_trigger_ctx._input->shm != nullptr);
        const platform::input::input_shared_memory_t& input_shm = *animation_trigger_ctx._input->shm;
        animation_context_t& ctx = animation_trigger_ctx.anim;
        // read-only config
        assert(ctx._local_copy_config != nullptr);
        const config::config_t& current_config = *ctx._local_copy_config;


        constexpr size_t fds_animation_trigger_index = 0;
        constexpr int fds_count = 1;
        pollfd fds[fds_count] = {
            { .fd = animation_trigger_ctx.trigger_efd._fd, .events = POLLIN, .revents = 0 },
        };
        assert(fds_count == LEN_ARRAY(fds));

        // check poll, close to FPS
        platform::time_ms_t timeout_ms = current_config.fps > 0 ? 1000 / current_config.fps / 3 : 0;
        timeout_ms = timeout_ms < POOL_MIN_TIMEOUT_MS ? POOL_MIN_TIMEOUT_MS : timeout_ms;
        timeout_ms = timeout_ms > POOL_MAX_TIMEOUT_MS ? POOL_MAX_TIMEOUT_MS : timeout_ms;

        int any_key_pressed = 0;
        timeout_ms = timeout_ms >= INT_MAX ? INT_MAX : timeout_ms;
        const int poll_result = poll(fds, fds_count, static_cast<int>(timeout_ms));
        if (poll_result > 0) {
            // animation trigger event
            if (fds[fds_animation_trigger_index].revents & POLLIN) {
                BONGOCAT_LOG_VERBOSE("Receive animation trigger event");
                any_key_pressed = 1;

                uint64_t u;
                assert(MAX_ATTEMPTS <= INT_MAX);
                while (read(animation_trigger_ctx.trigger_efd._fd, &u, sizeof(uint64_t)) == sizeof(uint64_t) && any_key_pressed <= static_cast<int>(MAX_ATTEMPTS)) {
                    any_key_pressed++;
                }
                // supress compiler warning
#if EAGAIN == EWOULDBLOCK
                if (errno != EAGAIN) {
                    BONGOCAT_LOG_ERROR("Error reading animation trigger eventfd: %s", strerror(errno));
                }
#else
                if (errno != EAGAIN && errno != EWOULDBLOCK) {
                    BONGOCAT_LOG_ERROR("Error reading animation trigger eventfd: %s", strerror(errno));
                }
#endif
            }
        }
        if (any_key_pressed <= 0) {
            return false;
        }

        const int new_frame = anim_get_random_active_frame(ctx, input_shm);
        const platform::time_us_t duration_us = current_config.keypress_duration_ms * 1000;

        BONGOCAT_LOG_VERBOSE("Key press detected - switching to frame %d", new_frame);
        const bool ret = anim_trigger_frame_change(ctx, new_frame, duration_us, current_time_us, state);

        state.test_counter = 0; // Reset test counter

        return ret;
    }

    static bool anim_handle_idle_return(animation_context_t& ctx, const platform::input::input_context_t& input, const animation_state_t& state, platform::timestamp_us_t current_time_us) {
        using namespace assets;

        assert(input.shm);
        const platform::input::input_shared_memory_t& input_shm = *input.shm;
        // read-only config
        assert(ctx._local_copy_config != nullptr);
        const config::config_t& current_config = *ctx._local_copy_config;

        assert(ctx.shm != nullptr);
        const int old_anim_frame_index = ctx.shm->animation_player_data.frame_index;

        // Sleep Mode
        if (current_config.enable_scheduled_sleep) {
            if (is_sleep_time(current_config)) {
                if (ctx.shm->anim_index == assets::BONGOCAT_ANIM_INDEX) {
                    ctx.shm->animation_player_data.frame_index = BONGOCAT_FRAME_BOTH_DOWN;
                    return old_anim_frame_index != ctx.shm->animation_player_data.frame_index;
                }

#ifndef FEATURE_INCLUDE_ONLY_BONGOCAT_EMBEDDED_ASSETS
                // assume it's a digimon
                if (ctx.shm->anims[ctx.shm->anim_index].digimon.sleep1.valid) {
                    ctx.shm->animation_player_data.frame_index = DIGIMON_FRAME_SLEEP1;
                    return old_anim_frame_index != ctx.shm->animation_player_data.frame_index;
                }
                if (ctx.shm->anims[ctx.shm->anim_index].digimon.down1.valid) {
                    // fallback frame
                    ctx.shm->animation_player_data.frame_index = DIGIMON_FRAME_DOWN1;
                    return old_anim_frame_index != ctx.shm->animation_player_data.frame_index;
                }
#endif
            }
        }

        // Idle Sleep
        const platform::timestamp_ms_t last_key_pressed_timestamp = input_shm.last_key_pressed_timestamp;
        if (current_config.idle_sleep_timeout_sec > 0 && last_key_pressed_timestamp > 0) {
            const platform::timestamp_ms_t now = platform::get_current_time_ms();
            const platform::time_ms_t idle_sleep_timeout_ms = current_config.idle_sleep_timeout_sec*1000;
            if (now - last_key_pressed_timestamp >= idle_sleep_timeout_ms) {
                if (ctx.shm->anim_index == assets::BONGOCAT_ANIM_INDEX) {
                    ctx.shm->animation_player_data.frame_index = BONGOCAT_FRAME_BOTH_DOWN;
                    return old_anim_frame_index != ctx.shm->animation_player_data.frame_index;
                }

#ifndef FEATURE_INCLUDE_ONLY_BONGOCAT_EMBEDDED_ASSETS
                // assume it's a digimon
                if (ctx.shm->anims[ctx.shm->anim_index].digimon.down1.valid) {
                    ctx.shm->animation_player_data.frame_index = DIGIMON_FRAME_DOWN1;
                    return old_anim_frame_index != ctx.shm->animation_player_data.frame_index;
                }
#endif
            }
        }

        if (current_time_us <= state.hold_until_us) {
            return false;
        }

        if (old_anim_frame_index != current_config.idle_frame) {
            BONGOCAT_LOG_VERBOSE("Returning to idle frame %d", current_config.idle_frame);
            ctx.shm->animation_player_data.frame_index = current_config.idle_frame;
            return true;
        }

        return false;
    }

    static bool anim_update_state(animation_session_t& animation_trigger_ctx, animation_state_t& state) {
        assert(animation_trigger_ctx._input);
        const platform::input::input_context_t& input = *animation_trigger_ctx._input;
        animation_context_t& ctx = animation_trigger_ctx.anim;
        // read-only config
        //assert(ctx->_local_copy_config);
        //const config_t& current_config = *ctx->_local_copy_config;

        const platform::timestamp_us_t current_time_us = platform::get_current_time_us();

        bool ret = false;
        do {
            platform::LockGuard guard (ctx.anim_lock);

            ret |= anim_handle_test_animation(ctx, input, state, current_time_us);
            ret |= anim_handle_key_press(animation_trigger_ctx, state, current_time_us);
            ret |= anim_handle_idle_return(ctx, input, state, current_time_us);
        } while(false);

        return ret;
    }

    // =============================================================================
    // ANIMATION THREAD MANAGEMENT MODULE
    // =============================================================================

    static void anim_init_state(animation_context_t& ctx, animation_state_t& state) {
        // read-only config
        assert(ctx._local_copy_config != nullptr);
        const config::config_t& current_config = *ctx._local_copy_config;
        assert(current_config.fps > 0);

        state.hold_until_us = 0;
        state.test_counter = 0;
        state.test_interval_frames = current_config.test_animation_interval_sec * current_config.fps;
        state.frame_time_ns = 1000000000LL / current_config.fps;
    }


    static void *anim_thread_main(void *arg) {
        assert(arg);
        auto& trigger_ctx = *static_cast<animation_session_t *>(arg);
        assert(trigger_ctx._input);
        animation_context_t& ctx = trigger_ctx.anim;
        //input_context_t& input = *trigger_ctx._input;

        // read-only config
        //assert(ctx._local_copy_config);
        //const config_t& current_config = *ctx._local_copy_config;

        animation_state_t state;
        anim_init_state(ctx, state);

        atomic_store(&ctx._animation_running, true);
        BONGOCAT_LOG_DEBUG("Animation thread main loop started");

        timespec next_frame_time{};
        clock_gettime(CLOCK_MONOTONIC, &next_frame_time);

        // trigger initial render
        platform::wayland::request_render(trigger_ctx);

        while (atomic_load(&ctx._animation_running)) {
            const bool frame_changed = anim_update_state(trigger_ctx, state);
            if (frame_changed) {
                uint64_t u = 1;
                if (write(trigger_ctx.render_efd._fd, &u, sizeof(uint64_t)) >= 0) {
                    BONGOCAT_LOG_VERBOSE("Write animation render event");
                } else {
                    BONGOCAT_LOG_ERROR("Failed to write to notify pipe in animation: %s", strerror(errno));
                }
            }

            // Advance next frame time by exactly one frame
            next_frame_time.tv_nsec += state.frame_time_ns;
            while (next_frame_time.tv_nsec >= 1000000000L) {
                next_frame_time.tv_nsec -= 1000000000L;
                next_frame_time.tv_sec += 1;
            }

            timespec now{};
            clock_gettime(CLOCK_MONOTONIC, &now);

            long sec_diff = next_frame_time.tv_sec - now.tv_sec;
            long nsec_diff = next_frame_time.tv_nsec - now.tv_nsec;
            if (nsec_diff < 0) {
                nsec_diff += 1000000000L;
                sec_diff--;
            }

            ctx.shm->animation_player_data.time_until_next_frame_ms =
                static_cast<platform::time_ms_t>(sec_diff * 1000L + (nsec_diff + 999999LL) / 1000000LL);

            if (sec_diff >= 0) {
                timespec sleep_time = { .tv_sec = sec_diff, .tv_nsec = nsec_diff };
                nanosleep(&sleep_time, nullptr);
                //BONGOCAT_LOG_VERBOSE("Animation frame sleep: %dms", ctx->shm->animation_player_data.time_until_next_frame_ms);
            } else {
                ctx.shm->animation_player_data.time_until_next_frame_ms = 0;
                next_frame_time = now; // resync
                //BONGOCAT_LOG_VERBOSE("Animation skip wait");
            }
        }

        BONGOCAT_LOG_INFO("Animation thread main loop exited");

        return nullptr;
    }

    // =============================================================================
    // PUBLIC API IMPLEMENTATION
    // =============================================================================

    bongocat_error_t start(animation_session_t& trigger_ctx, platform::input::input_context_t& input) {
        BONGOCAT_LOG_INFO("Starting animation thread");

        trigger_ctx._input = &input;

        const int result = pthread_create(&trigger_ctx.anim._anim_thread, nullptr, anim_thread_main, &trigger_ctx);
        if (result != 0) {
            BONGOCAT_LOG_ERROR("Failed to create animation thread: %s", strerror(result));
            return bongocat_error_t::BONGOCAT_ERROR_THREAD;
        }

        BONGOCAT_LOG_DEBUG("Animation thread started successfully");
        return bongocat_error_t::BONGOCAT_SUCCESS;
    }


    void trigger(animation_session_t& trigger_ctx) {
        constexpr uint64_t u = 1;
        if (write(trigger_ctx.trigger_efd._fd, &u, sizeof(uint64_t)) >= 0) {
            BONGOCAT_LOG_VERBOSE("Write animation trigger event");
        } else {
            BONGOCAT_LOG_ERROR("Failed to write to notify pipe in animation: %s", strerror(errno));
        }
    }

    void update_config(animation_context_t& ctx, const config::config_t& config) {
        assert(ctx._local_copy_config != nullptr);
        assert(ctx.shm != nullptr);

#ifndef NDEBUG
        assert(assets::ANIMS_COUNT <= INT_MAX);
        if (config.animation_index < 0 || config.animation_index >= static_cast<int>(assets::ANIMS_COUNT)) {
            BONGOCAT_LOG_WARNING("Invalid animation index %d", config.animation_index);
        }
#endif

        /// @TODO: make updating config thrad-safe (animation thread)
        *ctx._local_copy_config = config;

        ctx.shm->anim_type = ctx._local_copy_config->animation_type;

        assert(assets::ANIMS_COUNT <= INT_MAX);
        switch (config.animation_type) {
            case config::config_animation_type_t::None:
                ctx.shm->anim_index = 0;
                break;
            case config::config_animation_type_t::Bongocat:
            case config::config_animation_type_t::Digimon:
                ctx.shm->anim_index = config.animation_index % static_cast<int>(assets::ANIMS_COUNT);
                break;
            case config::config_animation_type_t::MsPet:
                ctx.shm->anim_index = config.animation_index % static_cast<int>(assets::MS_PETS_COUNT);
                break;
        }
    }
}
