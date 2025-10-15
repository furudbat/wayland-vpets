#include "graphics/animation_context.h"
#include "graphics/animation.h"
#include "platform/wayland.h"
#include "utils/time.h"
#include <ctime>
#include <pthread.h>
#include <sys/stat.h>
#include <cassert>
#include <climits>
#include <poll.h>
#include <unistd.h>

#include "embedded_assets/bongocat/bongocat.hpp"
#include "graphics/embedded_assets_dms.h"
#include "image_loader/bongocat/load_images_bongocat.h"
#include "image_loader/ms_agent/load_images_ms_agent.h"
#include "image_loader/dm/load_images_dm.h"
#include "image_loader/dm20/load_images_dm20.h"
#include "image_loader/dmx/load_images_dmx.h"
#include "image_loader/pen/load_images_pen.h"
#include "image_loader/pen20/load_images_pen20.h"
#include "image_loader/dmc/load_images_dmc.h"
#include "embedded_assets/bongocat/bongocat.h"
#include "embedded_assets/ms_agent/ms_agent.hpp"
#include "embedded_assets/ms_agent/ms_agent_sprite.h"
#include "embedded_assets/min_dm/min_dm_sprite.h"
#include "graphics/embedded_assets_pkmn.h"
#include "embedded_assets/pkmn/pkmn_sprite.h"

namespace bongocat::animation {
    // =============================================================================
    // GLOBAL STATE AND CONFIGURATION
    // =============================================================================

    inline static constexpr platform::time_ms_t POOL_MIN_TIMEOUT_MS = 5;
    inline static constexpr platform::time_ms_t POOL_MAX_TIMEOUT_MS = 1000;
    inline static constexpr int MAX_ATTEMPTS = 2048;
    static_assert(POOL_MAX_TIMEOUT_MS >= POOL_MIN_TIMEOUT_MS);

    inline static constexpr platform::time_ms_t COND_RELOAD_CONFIGS_TIMEOUT_MS = 5000;

    inline static constexpr int CHANCE_FOR_SKIPPING_MOVEMENT_PERCENT = 30;  // in percent
    inline static constexpr int SMALL_MAX_DISTANCE_PER_MOVEMENT_PART = 3;   // 1/3 of movement_radius (for small areas)
    inline static constexpr int MAX_DISTANCE_PER_MOVEMENT_PART = 5;         // 1/5 of movement_radius
    static_assert(SMALL_MAX_DISTANCE_PER_MOVEMENT_PART > 0);
    static_assert(MAX_DISTANCE_PER_MOVEMENT_PART > 0);
    inline static constexpr int MAX_MOVEMENT_RADIUS_SMALL = 100;
    inline static constexpr int FLIP_DIRECTION_NEAR_WALL_PERCENT = 70;
    inline static constexpr int SMALL_FLIP_DIRECTION_NEAR_WALL_PERCENT = 40;

    inline static constexpr int SLEEP_BORING_PART = 2;   // 1/2 of sleep time for triggering boring animation

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

    enum class animation_state_row_t : uint8_t {
        Idle,
        StartWriting,
        Writing,
        EndWriting,
        Happy,
        Sleep,
        WakeUp,
        Boring,
        Test,
        StartWorking,
        Working,
        EndWorking,
        StartMoving,
        Moving,
        EndMoving,
    };

    struct animation_state_t {
        // animation timing
        platform::time_ms_t frame_delta_ms_counter{0};
        platform::time_ns_t frame_time_ns{0};
        platform::time_ms_t frame_time_ms{0};
        platform::time_ms_t hold_frame_ms{0};
        platform::timestamp_ms_t last_frame_update_ms{0};
        platform::timestamp_ms_t time_until_next_frame_ms{0};

        // state
        bool hold_frame_after_release{false};
        bool show_boring_animation_once{false};

        // moving
        float anim_velocity{0.0};
        float anim_distance{0.0};
        float anim_last_direction{0.0};
        int32_t anim_pause_after_movement_ms{0};

        // animation player data
        animation_state_row_t row_state{animation_state_row_t::Idle};
        // for ms agent
        int32_t start_col_index{0};
        int32_t end_col_index{0};
        // for am/bongocat/pkmn (cached animation frames)
        int32_t animations_index{0};                            // for sprite_sheet.frames (col indices) array
    };

    struct anim_next_frame_result_t {
        bool changed{false};
        int new_frame{0};
    };


    struct animation_trigger_t {
        trigger_animation_cause_mask_t anim_cause{trigger_animation_cause_mask_t::NONE};
        int any_key_press_counter{0};
    };
    struct anim_handle_key_press_result_t {
        animation_trigger_t trigger;
        bool changed{false};
    };

    struct anim_conditions_t {
        bool any_key_pressed{false};
        platform::timestamp_ms_t last_key_pressed_timestamp{0};

        bool release_frame_after_press{false};
        bool process_idle_animation{false};
        bool trigger_test_animation{false};
        bool release_test_frame{false};
        bool check_for_idle_sleep{false};

        bool is_writing{false};
    };
    static anim_conditions_t get_anim_conditions([[maybe_unused]] const animation_context_t& ctx,
                                                 const platform::input::input_context_t& input,
                                                 const animation_state_t& current_state,
                                                 const animation_trigger_t& trigger,
                                                 const config::config_t& current_config) {
        assert(input.shm != nullptr);
        const auto& input_shm = *input.shm;
        const platform::timestamp_ms_t last_key_pressed_timestamp = input_shm.last_key_pressed_timestamp;
        const bool any_key_pressed = has_flag(trigger.anim_cause, trigger_animation_cause_mask_t::KeyPress) && trigger.any_key_press_counter > 0;
        const bool process_idle_animation = (current_config.idle_animation && current_config.animation_speed_ms > 0 && current_state.frame_delta_ms_counter > current_config.animation_speed_ms) || (current_config.idle_animation && current_config.animation_speed_ms <= 0 && current_state.frame_delta_ms_counter > 1000/current_config.fps);

        return {
            .any_key_pressed = any_key_pressed,
            .last_key_pressed_timestamp = last_key_pressed_timestamp,

            .release_frame_after_press = !any_key_pressed && current_state.hold_frame_ms > current_config.keypress_duration_ms,
            .process_idle_animation = process_idle_animation,
            .trigger_test_animation = current_config.test_animation_interval_sec > 0 && current_state.frame_delta_ms_counter > current_config.test_animation_interval_sec*1000,
            .release_test_frame = current_config.test_animation_duration_ms > 0 && current_state.frame_delta_ms_counter > current_config.test_animation_duration_ms,
            .check_for_idle_sleep = current_config.idle_sleep_timeout_sec > 0 && ((SLEEP_BORING_PART > 0 && current_state.frame_delta_ms_counter > current_config.idle_sleep_timeout_sec*1000/SLEEP_BORING_PART && last_key_pressed_timestamp > 0) || process_idle_animation),

            .is_writing = current_state.row_state == animation_state_row_t::StartWriting || current_state.row_state == animation_state_row_t::Writing || current_state.row_state == animation_state_row_t::EndWriting,
        };
    }

    static anim_next_frame_result_t anim_update_animation_state(animation_shared_memory_t& anim_shm,
                                                                animation_state_t& state,
                                                                const animation_player_result_t& new_animation_result,
                                                                const animation_state_t& new_state,
                                                                const animation_player_result_t& current_animation_result,
                                                                const animation_state_t& current_state,
                                                                const config::config_t& current_config) {
        const bool changed = new_animation_result.sprite_sheet_col != current_animation_result.sprite_sheet_col || new_animation_result.sprite_sheet_row != current_animation_result.sprite_sheet_row || current_state.row_state != new_state.row_state;
        if (new_state.animations_index != current_state.animations_index || changed) {
            anim_shm.animation_player_result = new_animation_result;
            state = new_state;
            if (current_config.enable_debug) {
                BONGOCAT_LOG_VERBOSE("Animation frame change: %d", new_animation_result.sprite_sheet_col);
            }
            state.frame_delta_ms_counter = 0;
        }

        return { .changed = changed, .new_frame = new_animation_result.sprite_sheet_col };
    }

#ifdef FEATURE_BONGOCAT_EMBEDDED_ASSETS
    enum class anim_bongocat_process_animation_result_t : uint8_t { Started, Updated, End };
    static anim_bongocat_process_animation_result_t anim_bongocat_process_animation(animation_player_result_t& new_animation_result,
                                                                                    animation_state_t& new_state,
                                                                                    const animation_state_t& current_state,
                                                                                    const bongocat_sprite_sheet_t& current_frames) {
        assert(MAX_ANIMATION_FRAMES > 0);
        assert(MAX_ANIMATION_FRAMES <= INT_MAX);
        anim_bongocat_process_animation_result_t ret = anim_bongocat_process_animation_result_t::Updated;
        // forward animation
        new_state.animations_index = current_state.animations_index + 1;
        if (new_state.animations_index > static_cast<int>(MAX_ANIMATION_FRAMES-1)) {
            ret = anim_bongocat_process_animation_result_t::End;
            new_state.animations_index = 0;
        }
        /*
        // backwards animation
        else if (new_state.animations_index < 0) {
            ret = anim_bongocat_process_animation_result_t::End;
            new_state.animations_index = MAX_ANIMATION_FRAMES-1;
        }
        */
        switch (new_state.row_state) {
            case animation_state_row_t::Idle:
                new_animation_result.sprite_sheet_col = current_frames._cached_animations.idle[new_state.animations_index];
                break;
            case animation_state_row_t::StartWriting:
            case animation_state_row_t::Writing:
            case animation_state_row_t::EndWriting:
                new_animation_result.sprite_sheet_col = current_frames._cached_animations.writing[new_state.animations_index];
                break;
            case animation_state_row_t::Happy:
                new_animation_result.sprite_sheet_col = current_frames._cached_animations.happy[new_state.animations_index];
                break;
            case animation_state_row_t::Sleep:
                new_animation_result.sprite_sheet_col = current_frames._cached_animations.sleep[new_state.animations_index];
                break;
            case animation_state_row_t::WakeUp:
                new_animation_result.sprite_sheet_col = current_frames._cached_animations.wake_up[new_state.animations_index];
                break;
            case animation_state_row_t::Boring:
                new_animation_result.sprite_sheet_col = current_frames._cached_animations.boring[new_state.animations_index];
                break;
            case animation_state_row_t::Test:
                new_animation_result.sprite_sheet_col = current_frames._cached_animations.writing[new_state.animations_index];
                break;
            case animation_state_row_t::StartWorking:
            case animation_state_row_t::Working:
            case animation_state_row_t::EndWorking:
                new_animation_result.sprite_sheet_col = current_frames._cached_animations.working[new_state.animations_index];
                break;
            case animation_state_row_t::StartMoving:
            case animation_state_row_t::Moving:
            case animation_state_row_t::EndMoving:
                new_animation_result.sprite_sheet_col = current_frames._cached_animations.moving[new_state.animations_index];
                break;
        }
        return ret;
    }
    static anim_bongocat_process_animation_result_t anim_bongocat_restart_animation(animation_context_t& ctx,
                                                                                    animation_state_row_t new_row_state,
                                                                                    animation_player_result_t& new_animation_result,
                                                                                    animation_state_t& new_state,
                                                                                    [[maybe_unused]] const animation_state_t& current_state,
                                                                                    const bongocat_sprite_sheet_t& current_frames,
                                                                                    const config::config_t& current_config) {
        using namespace assets;
        assert(MAX_ANIMATION_FRAMES > 0);
        assert(MAX_ANIMATION_FRAMES <= INT_MAX);
        anim_bongocat_process_animation_result_t ret = anim_bongocat_process_animation_result_t::Started;
        new_state.row_state = new_row_state;
        new_animation_result.sprite_sheet_row = BONGOCAT_SPRITE_SHEET_ROW;
        new_state.animations_index = 0;
        switch (new_state.row_state) {
            case animation_state_row_t::Idle:
                new_animation_result.sprite_sheet_col = current_frames._cached_animations.idle[new_state.animations_index];
                if (current_config.idle_frame) {
                    new_animation_result.sprite_sheet_col = current_config.idle_frame;
                }
                break;
            case animation_state_row_t::StartWriting:
                new_state.animations_index = static_cast<int>(ctx._rng.range(0, (MAX_ANIMATION_FRAMES-1) / 2));
                new_state.show_boring_animation_once = false;
                [[fallthrough]];
            case animation_state_row_t::Writing:
            case animation_state_row_t::EndWriting:
                new_animation_result.sprite_sheet_col = current_frames._cached_animations.writing[new_state.animations_index];
                break;
            case animation_state_row_t::Happy:
                new_animation_result.sprite_sheet_col = current_frames._cached_animations.happy[new_state.animations_index];
                break;
            case animation_state_row_t::Sleep:
                new_animation_result.sprite_sheet_col = current_frames._cached_animations.sleep[new_state.animations_index];
                new_state.show_boring_animation_once = false;
                break;
            case animation_state_row_t::WakeUp:
                new_animation_result.sprite_sheet_col = current_frames._cached_animations.wake_up[new_state.animations_index];
                new_state.show_boring_animation_once = false;
                break;
            case animation_state_row_t::Boring:
                new_animation_result.sprite_sheet_col = current_frames._cached_animations.boring[new_state.animations_index];
                new_state.show_boring_animation_once = true;
                break;
            case animation_state_row_t::Test:
                new_animation_result.sprite_sheet_col = current_frames._cached_animations.writing[new_state.animations_index];
                break;
            case animation_state_row_t::StartWorking:
            case animation_state_row_t::Working:
            case animation_state_row_t::EndWorking:
                new_animation_result.sprite_sheet_col = current_frames._cached_animations.working[new_state.animations_index];
                break;
            case animation_state_row_t::StartMoving:
            case animation_state_row_t::Moving:
            case animation_state_row_t::EndMoving:
                new_animation_result.sprite_sheet_col = current_frames._cached_animations.moving[new_state.animations_index];
                break;
        }
        return ret;
    }
    static anim_bongocat_process_animation_result_t anim_bongocat_start_or_process_animation(animation_context_t& ctx,
                                                                                             animation_state_row_t new_row_state,
                                                                                             animation_player_result_t& new_animation_result,
                                                                                             animation_state_t& new_state,
                                                                                             const animation_state_t& current_state,
                                                                                             const bongocat_sprite_sheet_t& current_frames,
                                                                                             const config::config_t& current_config) {

        if (new_state.row_state == new_row_state) {
            const auto result = anim_bongocat_process_animation(new_animation_result, new_state, current_state, current_frames);
            if (result == anim_bongocat_process_animation_result_t::End) {
                return anim_bongocat_restart_animation(ctx, new_row_state, new_animation_result, new_state,
                                                       current_state, current_frames, current_config);
            }
            return result;
        }

        return anim_bongocat_restart_animation(ctx, new_row_state, new_animation_result, new_state,
                                               current_state, current_frames, current_config);
    }

    static anim_next_frame_result_t anim_bongocat_idle_next_frame(animation_context_t& ctx, const platform::input::input_context_t& input,
                                                                  animation_state_t& state, const anim_handle_key_press_result_t& trigger_result) {
        using namespace assets;
        // read-only config
        assert(ctx._local_copy_config != nullptr);
        const config::config_t& current_config = *ctx._local_copy_config;

        assert(ctx.shm != nullptr);
        assert(input.shm != nullptr);
        animation_shared_memory_t& anim_shm = *ctx.shm;
        const auto& input_shm = *input.shm;
        const auto current_state = state;
        const auto& current_animation_result = anim_shm.animation_player_result;
        [[maybe_unused]] const int anim_index = anim_shm.anim_index;
        const platform::timestamp_ms_t last_key_pressed_timestamp = input_shm.last_key_pressed_timestamp;
        const auto& current_frames = reinterpret_cast<bongocat_sprite_sheet_t&>(get_current_animation(ctx));

        auto new_animation_result = anim_shm.animation_player_result;
        auto new_state = state;

        const auto conditions = get_anim_conditions(ctx, input, current_state, trigger_result.trigger, current_config);

        // Idle Animation
        const bool stop_writing = conditions.is_writing && conditions.release_frame_after_press;
        const bool stop_test_animation = conditions.trigger_test_animation && current_state.row_state == animation_state_row_t::Test && conditions.release_test_frame;
        if (stop_writing || stop_test_animation) {
            // back to idle
            anim_bongocat_restart_animation(ctx, animation_state_row_t::Idle,
                                            new_animation_result, new_state,
                                            current_state, current_frames, current_config);
        }
        if constexpr (features::BongocatIdleAnimation) {
            if (!stop_writing && !stop_test_animation && conditions.process_idle_animation) {
                if (current_state.row_state == animation_state_row_t::Idle) {
                    anim_bongocat_process_animation(new_animation_result, new_state, current_state, current_frames);
                } else if (current_state.row_state == animation_state_row_t::WakeUp) {
                    anim_bongocat_start_or_process_animation(ctx, animation_state_row_t::Idle,  // back to idle, when animation ended
                                                    new_animation_result, new_state,
                                                    current_state, current_frames, current_config);
                }
            }
        } else {
            if (current_state.row_state == animation_state_row_t::WakeUp && conditions.release_frame_after_press) {
                // back to idle
                anim_bongocat_restart_animation(ctx, animation_state_row_t::Idle,
                                                new_animation_result, new_state,
                                                current_state, current_frames, current_config);
            }
        }

        // Start Test animation
        if (!conditions.any_key_pressed && conditions.trigger_test_animation && current_state.row_state == animation_state_row_t::Idle) {
            anim_bongocat_restart_animation(ctx, animation_state_row_t::Test,
                                            new_animation_result, new_state,
                                            current_state, current_frames, current_config);
        }
        // Test Animation
        if (!conditions.any_key_pressed && conditions.trigger_test_animation && current_state.row_state == animation_state_row_t::Test) {
            anim_bongocat_start_or_process_animation(ctx, animation_state_row_t::Idle,  // back to idle, when animation ended
                                            new_animation_result, new_state,
                                            current_state, current_frames, current_config);
        }

        // Idle Sleep
        if (current_config.idle_sleep_timeout_sec > 0 && last_key_pressed_timestamp > 0 && conditions.check_for_idle_sleep) {
            const platform::timestamp_ms_t now = platform::get_current_time_ms();
            const platform::time_ms_t idle_sleep_timeout_ms = current_config.idle_sleep_timeout_sec*1000;
            if constexpr (features::BongocatBoringAnimation) {
                const bool start_boring = SLEEP_BORING_PART > 0 && now - last_key_pressed_timestamp >= idle_sleep_timeout_ms/SLEEP_BORING_PART;
                const bool is_past_boring_animation = (features::BongocatIdleAnimation && current_state.row_state == animation_state_row_t::Boring && !conditions.process_idle_animation && conditions.release_frame_after_press) ||
                                                      (!features::BongocatIdleAnimation && current_state.row_state == animation_state_row_t::Boring && (conditions.process_idle_animation || conditions.release_frame_after_press));
                // boring
                if (new_state.row_state == animation_state_row_t::Idle) {
                    if (start_boring && !current_state.show_boring_animation_once) {
                        anim_bongocat_restart_animation(ctx, animation_state_row_t::Boring,
                                                        new_animation_result, new_state,
                                                        current_state, current_frames, current_config);
                    }
                } else if (features::BongocatIdleAnimation && current_state.row_state == animation_state_row_t::Boring && conditions.process_idle_animation) {
                    anim_bongocat_start_or_process_animation(ctx, animation_state_row_t::Idle, // back to idle, when animation ended
                                                    new_animation_result, new_state,
                                                    current_state, current_frames, current_config);
                } else if ((!start_boring && is_past_boring_animation) || (start_boring && current_state.show_boring_animation_once && is_past_boring_animation)) {
                    // back to idle
                    anim_bongocat_restart_animation(ctx, animation_state_row_t::Idle,
                                                    new_animation_result, new_state,
                                                    current_state, current_frames, current_config);
                }
            }

            // sleep
            if (now - last_key_pressed_timestamp >= idle_sleep_timeout_ms) {
                if (new_state.row_state == animation_state_row_t::Idle) {
                    anim_bongocat_restart_animation(ctx, animation_state_row_t::Sleep,
                                                    new_animation_result, new_state,
                                                    current_state, current_frames, current_config);
                } else if (features::BongocatIdleAnimation && current_state.row_state == animation_state_row_t::Sleep && conditions.process_idle_animation) {
                    anim_bongocat_process_animation(new_animation_result, new_state, current_state, current_frames);
                }
            } else if (current_state.row_state == animation_state_row_t::Sleep) {
                // back to idle
                anim_bongocat_restart_animation(ctx, animation_state_row_t::Idle,
                                                new_animation_result, new_state,
                                                current_state, current_frames, current_config);
            }
        }

        // Sleep Mode
        if (current_config.enable_scheduled_sleep) {
            if (is_sleep_time(current_config)) {
                if (new_state.row_state == animation_state_row_t::Idle) {
                    anim_bongocat_restart_animation(ctx, animation_state_row_t::Sleep,
                                                    new_animation_result, new_state,
                                                    current_state, current_frames, current_config);
                } else if (features::BongocatIdleAnimation && state.row_state == animation_state_row_t::Sleep && conditions.process_idle_animation) {
                    anim_bongocat_process_animation(new_animation_result, new_state, current_state, current_frames);
                }
            } else if (state.row_state == animation_state_row_t::Sleep) {
                // back to idle
                anim_bongocat_restart_animation(ctx, animation_state_row_t::Idle,
                                                new_animation_result, new_state,
                                                current_state, current_frames, current_config);
            }
        }

        return anim_update_animation_state(anim_shm, state,
                                            new_animation_result, new_state,
                                            current_animation_result, current_state,
                                            current_config);
    }

    static anim_next_frame_result_t anim_bongocat_key_pressed_next_frame(animation_context_t& ctx, animation_state_t& state,
                                                                         const platform::input::input_context_t& input,
                                                                         const animation_trigger_t& trigger) {
        using namespace assets;

        // read-only config
        assert(ctx._local_copy_config != nullptr);
        const config::config_t& current_config = *ctx._local_copy_config;

        assert(ctx.shm != nullptr);
        assert(input.shm != nullptr);
        animation_shared_memory_t& anim_shm = *ctx.shm;
        const auto& input_shm = *input.shm;
        const auto current_state = state;
        const auto& current_animation_result = anim_shm.animation_player_result;
        [[maybe_unused]] const int anim_index = anim_shm.anim_index;
        //const platform::timestamp_ms_t last_key_pressed_timestamp = input_shm.last_key_pressed_timestamp;
        const auto& current_frames = reinterpret_cast<bongocat_sprite_sheet_t&>(get_current_animation(ctx));

        auto new_animation_result = anim_shm.animation_player_result;
        auto new_state = state;

        const auto conditions = get_anim_conditions(ctx, input, current_state, trigger, current_config);

        /// @TODO: use state machine for animation (states)

        // in Writing mode/start writing
        if (!conditions.is_writing) {
            if (state.row_state == animation_state_row_t::Sleep) {
                // wake up
                anim_bongocat_restart_animation(ctx, animation_state_row_t::WakeUp,
                                                new_animation_result, new_state,
                                                current_state, current_frames, current_config);
            } else {
                // start writing
                anim_bongocat_restart_animation(ctx, animation_state_row_t::StartWriting,
                                                new_animation_result, new_state,
                                                current_state, current_frames, current_config);
            }
        } else if (state.row_state == animation_state_row_t::StartWriting) {
            anim_bongocat_start_or_process_animation(ctx, animation_state_row_t::Writing,
                                            new_animation_result, new_state,
                                            current_state, current_frames, current_config);
        }

        if constexpr (features::BongocatIdleAnimation) {
            if (conditions.is_writing) {
                if (conditions.release_frame_after_press && current_state.row_state == animation_state_row_t::Writing && conditions.process_idle_animation) {
                    anim_bongocat_start_or_process_animation(ctx, animation_state_row_t::EndWriting,
                                                    new_animation_result, new_state,
                                                    current_state, current_frames, current_config);
                } else if (conditions.release_frame_after_press && (current_state.row_state == animation_state_row_t::EndWriting || current_state.row_state == animation_state_row_t::WakeUp) && conditions.process_idle_animation) {
                    anim_bongocat_start_or_process_animation(ctx, animation_state_row_t::Idle,      // back to idle
                                                    new_animation_result, new_state,
                                                    current_state, current_frames, current_config);
                }
            }
        } else {
            if (!conditions.release_frame_after_press && conditions.is_writing) {
                // keep writing
                anim_bongocat_process_animation(new_animation_result, new_state, current_state, current_frames);
            } else if ((conditions.is_writing || state.row_state == animation_state_row_t::WakeUp) && conditions.release_frame_after_press && !conditions.process_idle_animation) {
                // back to idle
                anim_bongocat_restart_animation(ctx, animation_state_row_t::Idle,
                                                new_animation_result, new_state,
                                                current_state, current_frames, current_config);
            }
        }

        return anim_update_animation_state(anim_shm, state,
                                            new_animation_result, new_state,
                                            current_animation_result, current_state,
                                            current_config);
    }
#endif

#ifdef FEATURE_ENABLE_DM_EMBEDDED_ASSETS
    enum class anim_dm_process_animation_result_t : uint8_t { Started, Updated, End };
    static anim_dm_process_animation_result_t anim_dm_process_animation(animation_player_result_t& new_animation_result,
                                                                        animation_state_t& new_state,
                                                                        const animation_state_t& current_state,
                                                                        const dm_sprite_sheet_t& current_frames) {
        assert(MAX_ANIMATION_FRAMES > 0);
        assert(MAX_ANIMATION_FRAMES <= INT_MAX);
        anim_dm_process_animation_result_t ret = anim_dm_process_animation_result_t::Updated;
        new_state.animations_index = current_state.animations_index + 1;
        if (new_state.animations_index > static_cast<int>(MAX_ANIMATION_FRAMES-1)) {
            ret = anim_dm_process_animation_result_t::End;
            new_state.animations_index = 0;
        }
        /*
        else if (new_state.animations_index < 0) {
            ret = anim_bongocat_process_animation_result_t::End;
            new_state.animations_index = MAX_ANIMATION_FRAMES-1;
        }
        */
        switch (new_state.row_state) {
            case animation_state_row_t::Idle:
                new_animation_result.sprite_sheet_col = current_frames.animations.idle[new_state.animations_index];
                break;
            case animation_state_row_t::StartWriting:
            case animation_state_row_t::Writing:
            case animation_state_row_t::EndWriting:
                new_animation_result.sprite_sheet_col = current_frames.animations.writing[new_state.animations_index];
                break;
            case animation_state_row_t::Happy:
                new_animation_result.sprite_sheet_col = current_frames.animations.happy[new_state.animations_index];
                break;
            case animation_state_row_t::Sleep:
                new_animation_result.sprite_sheet_col = current_frames.animations.sleep[new_state.animations_index];
                break;
            case animation_state_row_t::WakeUp:
                new_animation_result.sprite_sheet_col = current_frames.animations.wake_up[new_state.animations_index];
                break;
            case animation_state_row_t::Boring:
                new_animation_result.sprite_sheet_col = current_frames.animations.boring[new_state.animations_index];
                break;
            case animation_state_row_t::Test:
                new_animation_result.sprite_sheet_col = current_frames.animations.writing[new_state.animations_index];
                break;
            case animation_state_row_t::StartWorking:
            case animation_state_row_t::Working:
            case animation_state_row_t::EndWorking:
                new_animation_result.sprite_sheet_col = current_frames.animations.working[new_state.animations_index];
                break;
            case animation_state_row_t::StartMoving:
            case animation_state_row_t::Moving:
            case animation_state_row_t::EndMoving:
                new_animation_result.sprite_sheet_col = current_frames.animations.moving[new_state.animations_index];
                break;
        }
        return ret;
    }
    static anim_dm_process_animation_result_t anim_dm_restart_animation(animation_context_t& ctx,
                                                                        animation_state_row_t new_row_state,
                                                                        animation_player_result_t& new_animation_result,
                                                                        animation_state_t& new_state,
                                                                        const animation_state_t& current_state,
                                                                        const dm_sprite_sheet_t& current_frames,
                                                                        const config::config_t& current_config) {
        using namespace assets;
        assert(MAX_ANIMATION_FRAMES > 0);
        assert(MAX_ANIMATION_FRAMES <= INT_MAX);
        anim_dm_process_animation_result_t ret = anim_dm_process_animation_result_t::Started;
        new_state.row_state = new_row_state;
        new_animation_result.sprite_sheet_row = DM_SPRITE_SHEET_ROWS-1;
        new_state.animations_index = 0;
        switch (new_state.row_state) {
            case animation_state_row_t::Idle:
                new_animation_result.sprite_sheet_col = current_frames.animations.idle[new_state.animations_index];
                if (current_config.idle_frame) {
                    new_animation_result.sprite_sheet_col = current_config.idle_frame;
                }
                break;
            case animation_state_row_t::StartWriting:
            case animation_state_row_t::Writing:
            case animation_state_row_t::EndWriting:
                new_animation_result.sprite_sheet_col = current_frames.animations.writing[new_state.animations_index];
                new_state.show_boring_animation_once = false;
                break;
            case animation_state_row_t::Happy:
                new_animation_result.sprite_sheet_col = current_frames.animations.happy[new_state.animations_index];
                break;
            case animation_state_row_t::Sleep:
                new_animation_result.sprite_sheet_col = current_frames.animations.sleep[new_state.animations_index];
                new_state.show_boring_animation_once = false;
                break;
            case animation_state_row_t::WakeUp:
                new_animation_result.sprite_sheet_col = current_frames.animations.wake_up[new_state.animations_index];
                new_state.show_boring_animation_once = false;
                break;
            case animation_state_row_t::Boring:
                new_animation_result.sprite_sheet_col = current_frames.animations.boring[new_state.animations_index];
                new_state.show_boring_animation_once = true;
                break;
            case animation_state_row_t::Test:
                new_animation_result.sprite_sheet_col = current_frames.animations.writing[new_state.animations_index];
                break;
            case animation_state_row_t::StartWorking:
            case animation_state_row_t::Working:
            case animation_state_row_t::EndWorking:
                new_animation_result.sprite_sheet_col = current_frames.animations.working[new_state.animations_index];
                break;
            case animation_state_row_t::StartMoving:
            case animation_state_row_t::Moving:
            case animation_state_row_t::EndMoving:
                new_animation_result.sprite_sheet_col = current_frames.animations.moving[new_state.animations_index];
                break;
        }
        return ret;
    }
    static anim_dm_process_animation_result_t anim_dm_start_or_process_animation(animation_context_t& ctx,
                                                                                 animation_state_row_t new_row_state,
                                                                                 animation_player_result_t& new_animation_result,
                                                                                 animation_state_t& new_state,
                                                                                 const animation_state_t& current_state,
                                                                                 const dm_sprite_sheet_t& current_frames,
                                                                                 const config::config_t& current_config) {

        if (new_state.row_state == new_row_state) {
            const auto result = anim_dm_process_animation(new_animation_result, new_state, current_state, current_frames);
            if (result == anim_dm_process_animation_result_t::End) {
                return anim_dm_restart_animation(ctx, new_row_state, new_animation_result, new_state,
                                                       current_state, current_frames, current_config);
            }
            return result;
        }

        return anim_dm_restart_animation(ctx, new_row_state, new_animation_result, new_state,
                                         current_state, current_frames, current_config);
    }

    static anim_next_frame_result_t anim_dm_idle_next_frame(animation_context_t& ctx, const platform::input::input_context_t& input,
                                                            [[maybe_unused]] const platform::update::update_context_t& upd,
                                                            animation_state_t& state, const anim_handle_key_press_result_t& trigger_result) {
        using namespace assets;

        // read-only config
        assert(ctx._local_copy_config != nullptr);
        const config::config_t& current_config = *ctx._local_copy_config;

        assert(ctx.shm != nullptr);
        assert(input.shm != nullptr);
        assert(upd.shm != nullptr);
        animation_shared_memory_t& anim_shm = *ctx.shm;
        const auto& input_shm = *input.shm;
        const auto& update_shm = *upd.shm;
        const auto current_state = state;
        const auto& current_animation_result = anim_shm.animation_player_result;
        [[maybe_unused]] const int anim_index = anim_shm.anim_index;
        const platform::timestamp_ms_t last_key_pressed_timestamp = input_shm.last_key_pressed_timestamp;
        const auto& current_frames = reinterpret_cast<dm_sprite_sheet_t&>(get_current_animation(ctx));

        auto new_animation_result = anim_shm.animation_player_result;
        auto new_state = state;

        const bool any_key_pressed = has_flag(trigger_result.trigger.anim_cause, trigger_animation_cause_mask_t::KeyPress) && trigger_result.trigger.any_key_press_counter > 0;

        assert(SMALL_MAX_DISTANCE_PER_MOVEMENT_PART > 0);
        assert(MAX_DISTANCE_PER_MOVEMENT_PART > 0);
        const bool release_frame_after_press = (!any_key_pressed && !has_flag(trigger_result.trigger.anim_cause, trigger_animation_cause_mask_t::CpuUpdate)) && current_state.hold_frame_ms > current_config.keypress_duration_ms;
        const bool release_frame_after_update = (!any_key_pressed && has_flag(trigger_result.trigger.anim_cause, trigger_animation_cause_mask_t::CpuUpdate)) && current_state.hold_frame_ms > current_config.keypress_duration_ms;
        const bool process_idle_animation = (current_config.idle_animation && current_config.animation_speed_ms > 0 && current_state.frame_delta_ms_counter > current_config.animation_speed_ms) || (current_config.idle_animation && current_config.animation_speed_ms <= 0 && current_state.frame_delta_ms_counter > 1000/current_config.fps);
        const bool process_movement = current_config.movement_speed > 0 && current_config.movement_radius > 0 && (current_state.frame_delta_ms_counter > current_config.movement_speed || current_state.frame_delta_ms_counter > 1000/current_config.fps);
        const bool process_movement_animation = current_config.movement_speed > 0 && current_config.movement_radius > 0 && ((current_config.animation_speed_ms > 0 && current_state.frame_delta_ms_counter > current_config.animation_speed_ms) || (current_config.animation_speed_ms <= 0 && current_state.frame_delta_ms_counter > 1000/current_config.fps));
        const bool trigger_test_animation = current_config.test_animation_interval_sec > 0 && current_state.frame_delta_ms_counter > current_config.test_animation_interval_sec*1000;
        const bool release_test_frame = current_config.test_animation_duration_ms > 0 && current_state.frame_delta_ms_counter > current_config.test_animation_duration_ms;
        const bool check_for_idle_sleep = current_config.idle_sleep_timeout_sec > 0 && current_state.frame_delta_ms_counter > current_config.idle_sleep_timeout_sec*1000/2 && last_key_pressed_timestamp > 0;
        const bool process_working_animation = (current_config.animation_speed_ms > 0 && current_state.frame_delta_ms_counter > current_config.animation_speed_ms) || (current_config.animation_speed_ms <= 0 && current_state.frame_delta_ms_counter > 1000/current_config.fps);

        /// @TODO: extract set animation state

        const bool is_moving = current_state.row_state == animation_state_row_t::StartMoving || current_state.row_state == animation_state_row_t::Moving || state.row_state == animation_state_row_t::EndMoving;
        const bool is_working = current_state.row_state == animation_state_row_t::StartWorking || current_state.row_state == animation_state_row_t::Working;
        if (!is_moving) {
            // Start Test animation
            if (!any_key_pressed && trigger_test_animation && current_state.row_state == animation_state_row_t::Idle) {
                anim_dm_restart_animation(ctx, animation_state_row_t::Test,
                                                new_animation_result, new_state,
                                                current_state, current_frames, current_config);
            }
            // Test Animation
            if (!any_key_pressed && trigger_test_animation && current_state.row_state == animation_state_row_t::Test) {
                anim_dm_start_or_process_animation(ctx, animation_state_row_t::Idle, // back to idle, when animation ended
                                                new_animation_result, new_state,
                                                current_state, current_frames, current_config);
            }

            // Idle Animation
            if (release_frame_after_press || process_idle_animation || (trigger_test_animation && release_test_frame && state.row_state == animation_state_row_t::Test)) {
                // back to idle
                anim_dm_restart_animation(ctx, animation_state_row_t::Idle,
                                                new_animation_result, new_state,
                                                current_state, current_frames, current_config);
            }
        }
        if (release_frame_after_update && current_state.row_state == animation_state_row_t::EndWorking) {
            // back to idle
            anim_dm_restart_animation(ctx, animation_state_row_t::Idle,
                                            new_animation_result, new_state,
                                            current_state, current_frames, current_config);
        } else if ((process_working_animation || release_frame_after_update) && !update_shm.cpu_active && is_working) {
            if (current_state.row_state != animation_state_row_t::EndWorking) {
                anim_dm_start_or_process_animation(ctx, animation_state_row_t::EndWorking, // start end working animation, when animation ended
                                                new_animation_result, new_state,
                                                current_state, current_frames, current_config);
            } else {
                anim_dm_start_or_process_animation(ctx, animation_state_row_t::Idle, // back to idle, when animation ended
                                                new_animation_result, new_state,
                                                current_state, current_frames, current_config);
            }
        }

        // Move Animation
        if ((process_idle_animation || process_movement || process_movement_animation) && current_config.movement_speed > 0 && current_config.movement_radius > 0 && current_config.fps > 0) {
            const float delta = 1.0f / static_cast<float>(current_config.fps);
            const auto delta_ms = static_cast<int32_t>(delta * 1000);
            const auto frame_height = current_config.cat_height;
            const auto frame_width  = static_cast<int>(static_cast<float>(frame_height) * (static_cast<float>(current_frames.frame_width) / static_cast<float>(current_frames.frame_height)));
            const auto fmovement_radius = static_cast<float>(current_config.movement_radius);

            assert(current_config.movement_radius > 0);
            float max_movement_offset_x_left = 0.0f;
            float max_movement_offset_x_right = 0.0f;
            float wall_distance = 0.0f;
            switch (current_config.cat_align) {
                case config::align_type_t::ALIGN_CENTER:
                    // range: [-r, +r]
                    max_movement_offset_x_left = -static_cast<float>(current_config.movement_radius) + static_cast<float>(frame_width) / 2.0f;
                    max_movement_offset_x_right = static_cast<float>(current_config.movement_radius - frame_width);
                    wall_distance = anim_shm.movement_offset_x / fmovement_radius;
                    break;
                case config::align_type_t::ALIGN_LEFT:
                    // range: [0, +2r]
                    max_movement_offset_x_left = 0.0f;
                    max_movement_offset_x_right = static_cast<float>(current_config.movement_radius) * 2.0f - static_cast<float>(frame_width);
                    wall_distance = (anim_shm.movement_offset_x / (fmovement_radius * 2.0f)) * 2.0f - 1.0f;
                    break;
                case config::align_type_t::ALIGN_RIGHT:
                    // range: [-2r, 0]
                    max_movement_offset_x_left = -(static_cast<float>(current_config.movement_radius) * 2.0f) + static_cast<float>(frame_width);
                    max_movement_offset_x_right = 0.0f;
                    wall_distance = (anim_shm.movement_offset_x / (fmovement_radius * 2.0f)) * 2.0f + 1.0f;  // normalize to -1 → 1
                    break;
            }

            if (current_state.row_state == animation_state_row_t::Idle && (current_state.anim_pause_after_movement_ms > 0 || (ctx._rng.range(0, 100) <= CHANCE_FOR_SKIPPING_MOVEMENT_PERCENT))) {
                // skip movement
                anim_shm.anim_direction = 0.0;
                new_state.anim_velocity = 0.0f;
                new_state.anim_distance = 0.0f;
                if (new_state.anim_pause_after_movement_ms > 0) {
                    new_state.anim_pause_after_movement_ms -= delta_ms;
                    if (new_state.anim_pause_after_movement_ms <= 0) {
                        new_state.anim_pause_after_movement_ms = 0;
                    }
                }
            } else {
                // moving animation
                constexpr float DIR_EPSILON = 1e-3f;
                assert(MAX_DISTANCE_PER_MOVEMENT_PART > 0);
                const int movement_part = current_config.movement_radius <= MAX_MOVEMENT_RADIUS_SMALL ? SMALL_MAX_DISTANCE_PER_MOVEMENT_PART : MAX_DISTANCE_PER_MOVEMENT_PART;
                const float fmovement_part = static_cast<float>(movement_part);
                if (current_state.row_state == animation_state_row_t::Idle) {
                    const auto min_movement = current_config.movement_radius <= MAX_MOVEMENT_RADIUS_SMALL ? (fmovement_radius / fmovement_part / 2) + 1 : (fmovement_radius / fmovement_part / fmovement_part) + 1;
                    float max_move_distance = fmovement_radius / fmovement_part;
                    max_move_distance = max_move_distance <= min_movement ? min_movement : max_move_distance;

                    assert(max_move_distance >= 0);
                    assert(min_movement >= 0);
                    new_state.anim_distance = static_cast<float>(ctx._rng.range(static_cast<uint32_t>(min_movement), static_cast<uint32_t>(max_move_distance)));

                    if (anim_shm.movement_offset_x >= max_movement_offset_x_right) {
                        // run against wall, change direction
                        anim_shm.anim_direction = -1.0;
                        anim_shm.movement_offset_x = max_movement_offset_x_right;
                    } else if (anim_shm.movement_offset_x <= max_movement_offset_x_left) {
                        // run against wall, change direction
                        anim_shm.anim_direction = 1.0;
                        anim_shm.movement_offset_x = max_movement_offset_x_left;
                    } else {
                        float toward_wall_bias = fabs(wall_distance);
                        toward_wall_bias = toward_wall_bias >= 1.0f ? 1.0f : toward_wall_bias;
                        toward_wall_bias = toward_wall_bias <= 0.0f ? 0.0f : toward_wall_bias;

                        const int flip_direction_chance = current_config.movement_radius <= MAX_MOVEMENT_RADIUS_SMALL ? SMALL_FLIP_DIRECTION_NEAR_WALL_PERCENT : FLIP_DIRECTION_NEAR_WALL_PERCENT;

                        assert(toward_wall_bias >= 0.0f);
                        // change direction: chance drops at center, changes falloff steeper near walls
                        const auto dir_chance = static_cast<uint32_t>(static_cast<float>(100 - flip_direction_chance + 10) * (1.0f - pow(toward_wall_bias, 1.5f)));

                        if (fabs(state.anim_last_direction) >= DIR_EPSILON) {
                            anim_shm.anim_direction = (ctx._rng.range(0, 100) < dir_chance) ? -state.anim_last_direction : state.anim_last_direction;
                        } else if (fabs(anim_shm.anim_direction) < DIR_EPSILON) {
                            // idle: choose random start direction
                            anim_shm.anim_direction = (ctx._rng.range(0, 100) < dir_chance) ? 1.0f : -1.0f;
                        } else {
                            if (wall_distance > (100.0f / static_cast<float>(flip_direction_chance))) {
                                anim_shm.anim_direction = (ctx._rng.range(0, 100) < dir_chance) ? -1.0f : 1.0f;
                            } else if (wall_distance < -(100.0f / static_cast<float>(flip_direction_chance))) {
                                anim_shm.anim_direction = (ctx._rng.range(0, 100) < dir_chance) ? 1.0f : -1.0f;
                            } else {
                                anim_shm.anim_direction = (ctx._rng.range(0, 100) < dir_chance) ? anim_shm.anim_direction : -anim_shm.anim_direction;
                            }
                        }
                    }
                    // start moving animation
                    new_state.anim_velocity = anim_shm.anim_direction * static_cast<float>(current_config.movement_speed);
                    anim_dm_restart_animation(ctx, animation_state_row_t::StartMoving,
                                                    new_animation_result, new_state,
                                                    current_state, current_frames, current_config);
                } else if (current_state.row_state == animation_state_row_t::StartMoving) {
                    anim_dm_start_or_process_animation(ctx, animation_state_row_t::Moving, // continue with moving
                                                    new_animation_result, new_state,
                                                    current_state, current_frames, current_config);
                } else if (current_state.row_state == animation_state_row_t::Moving) {
                    if (process_movement_animation) {
                        anim_dm_process_animation(new_animation_result, new_state, current_state, current_frames);

                        new_state.anim_distance -= fabs(new_state.anim_velocity);
                        anim_shm.movement_offset_x += new_state.anim_velocity;
                        // clamp walking/movement area
                        if (anim_shm.movement_offset_x > max_movement_offset_x_right) {
                            anim_shm.movement_offset_x = max_movement_offset_x_right;
                            anim_dm_restart_animation(ctx, animation_state_row_t::EndMoving,
                                                    new_animation_result, new_state,
                                                    current_state, current_frames, current_config);
                        } else if (anim_shm.movement_offset_x < max_movement_offset_x_left) {
                            anim_shm.movement_offset_x = max_movement_offset_x_left;
                            anim_dm_restart_animation(ctx, animation_state_row_t::EndMoving,
                                                    new_animation_result, new_state,
                                                    current_state, current_frames, current_config);
                        }
                    }
                    if (fabs(new_state.anim_distance) < DIR_EPSILON || fabs(state.anim_velocity) < DIR_EPSILON) {
                        anim_dm_restart_animation(ctx, animation_state_row_t::EndMoving,
                                                new_animation_result, new_state,
                                                current_state, current_frames, current_config);
                    }
                } else if (state.row_state == animation_state_row_t::EndMoving) {
                    // back to idle
                    anim_dm_restart_animation(ctx, animation_state_row_t::Idle,
                                            new_animation_result, new_state,
                                            current_state, current_frames, current_config);
                    new_state.anim_last_direction = anim_shm.anim_direction;
                    new_state.anim_velocity = 0.0f;
                    new_state.anim_pause_after_movement_ms = current_config.animation_speed_ms * movement_part / 2;
                }
            }
        } else if (release_frame_after_press) {
            // movement got disabled, back to idle
            if (is_moving) {
                // back to idle
                anim_dm_restart_animation(ctx, animation_state_row_t::Idle,
                                        new_animation_result, new_state,
                                        current_state, current_frames, current_config);
                new_state.anim_velocity = 0.0f;
            }
        }

        // Sleep animation
        if (current_config.enable_scheduled_sleep && is_sleep_time(current_config) && new_state.row_state != animation_state_row_t::Idle) {
            new_state.row_state = animation_state_row_t::Sleep;
            assert(MAX_ANIMATION_FRAMES > 0);
            new_state.animations_index = (current_state.animations_index+1) % static_cast<int>(MAX_ANIMATION_FRAMES-1);
            new_animation_result.sprite_sheet_col = current_frames.animations.sleep[new_state.animations_index];
            state.anim_last_direction = 0.0f;
        }

        // Idle Sleep
        if (check_for_idle_sleep) {
            const platform::timestamp_ms_t now = platform::get_current_time_ms();
            const platform::time_ms_t idle_sleep_timeout_ms = current_config.idle_sleep_timeout_sec*1000;
            // boring
            if (new_state.row_state == animation_state_row_t::Idle) {
                if (state.row_state != animation_state_row_t::Boring && now - last_key_pressed_timestamp >= idle_sleep_timeout_ms/2) {
                    anim_dm_restart_animation(ctx, animation_state_row_t::Boring,
                                                    new_animation_result, new_state,
                                                    current_state, current_frames, current_config);
                }
            } else if (current_state.row_state == animation_state_row_t::Boring && process_idle_animation) {
                anim_dm_start_or_process_animation(ctx, animation_state_row_t::Idle, // back to idle, when animation ended
                                                new_animation_result, new_state,
                                                current_state, current_frames, current_config);
            } else if (current_state.row_state == animation_state_row_t::Boring && !process_idle_animation && release_frame_after_press) {
                // back to idle
                anim_dm_restart_animation(ctx, animation_state_row_t::Idle,
                                                new_animation_result, new_state,
                                                current_state, current_frames, current_config);
            }

            // sleep
            if (now - last_key_pressed_timestamp >= idle_sleep_timeout_ms) {
                // start sleeping
                if (new_state.row_state == animation_state_row_t::Idle) {
                    anim_dm_restart_animation(ctx, animation_state_row_t::Sleep,
                                                    new_animation_result, new_state,
                                                    current_state, current_frames, current_config);
                    state.anim_last_direction = 0.0f;
                } else if (current_state.row_state == animation_state_row_t::Sleep && process_idle_animation) {
                    anim_dm_process_animation(new_animation_result, new_state, current_state, current_frames);
                }
            }
        }

        // Sleep Mode
        if (current_config.enable_scheduled_sleep) {
            if (is_sleep_time(current_config)) {
                if (new_state.row_state == animation_state_row_t::Idle) {
                    anim_dm_restart_animation(ctx, animation_state_row_t::Sleep,
                                                    new_animation_result, new_state,
                                                    current_state, current_frames, current_config);
                    state.anim_last_direction = 0.0f;
                } else if (state.row_state == animation_state_row_t::Sleep && process_idle_animation) {
                    anim_dm_process_animation(new_animation_result, new_state, current_state, current_frames);
                }
            } else if (state.row_state == animation_state_row_t::Sleep) {
                // back to idle
                anim_dm_restart_animation(ctx, animation_state_row_t::Idle,
                                                new_animation_result, new_state,
                                                current_state, current_frames, current_config);
            }
        }

        return anim_update_animation_state(anim_shm, state,
                                            new_animation_result, new_state,
                                            current_animation_result, current_state,
                                            current_config);
    }

    static anim_next_frame_result_t anim_dm_key_pressed_next_frame(animation_context_t& ctx, const platform::input::input_context_t& input,
                                                                   animation_state_t& state,
                                                                   const animation_trigger_t& trigger) {
        using namespace assets;

        // read-only config
        assert(ctx._local_copy_config != nullptr);
        const config::config_t& current_config = *ctx._local_copy_config;

        assert(ctx.shm != nullptr);
        assert(input.shm != nullptr);
        animation_shared_memory_t& anim_shm = *ctx.shm;
        const auto& input_shm = *input.shm;
        const auto current_state = state;
        const auto& current_animation_result = anim_shm.animation_player_result;
        [[maybe_unused]] const int anim_index = anim_shm.anim_index;
        const platform::timestamp_ms_t last_key_pressed_timestamp = input_shm.last_key_pressed_timestamp;
        const auto& current_frames = reinterpret_cast<dm_sprite_sheet_t&>(get_current_animation(ctx));

        auto new_animation_result = anim_shm.animation_player_result;
        auto new_state = state;
        const bool any_key_pressed = has_flag(trigger.anim_cause, trigger_animation_cause_mask_t::KeyPress) && trigger.any_key_press_counter > 0;

        const bool release_frame_after_press = !any_key_pressed && current_state.hold_frame_ms > current_config.keypress_duration_ms;
        const bool process_idle_animation = (current_config.idle_animation && current_config.animation_speed_ms > 0 && current_state.frame_delta_ms_counter > current_config.animation_speed_ms) || (current_config.idle_animation && current_config.animation_speed_ms <= 0 && current_state.frame_delta_ms_counter > 1000/current_config.fps);

        bool show_happy = false;
        if (input_shm.kpm > 0) {
            if (current_config.happy_kpm > 0 && input_shm.kpm >= current_config.happy_kpm) {
                show_happy = DM_HAPPY_CHANCE_PERCENT >= 100 || ctx._rng.range(0, 99) < DM_HAPPY_CHANCE_PERCENT;
            }
        }
        const bool is_writing = state.row_state == animation_state_row_t::StartWriting || state.row_state == animation_state_row_t::Writing || state.row_state == animation_state_row_t::EndWriting;

        /// @TODO: use state machine for animation (states)

        if (show_happy && (is_writing || current_state.row_state != animation_state_row_t::Idle)) {
            // show happy animation (KPM)
            anim_dm_restart_animation(ctx, animation_state_row_t::Happy,
                                            new_animation_result, new_state,
                                            current_state, current_frames, current_config);
        } else if (is_writing || current_state.row_state == animation_state_row_t::Idle) {
            // in Writing mode/start writing
            if (!is_writing) {
                anim_dm_restart_animation(ctx, animation_state_row_t::StartWriting,
                                                new_animation_result, new_state,
                                                current_state, current_frames, current_config);
            } else if (state.row_state == animation_state_row_t::StartWriting) {
                anim_dm_start_or_process_animation(ctx, animation_state_row_t::Writing,
                                                new_animation_result, new_state,
                                                current_state, current_frames, current_config);
            } else if (release_frame_after_press && state.row_state == animation_state_row_t::Writing && process_idle_animation) {
                anim_dm_start_or_process_animation(ctx, animation_state_row_t::EndWriting,
                                                new_animation_result, new_state,
                                                current_state, current_frames, current_config);
            } else if (release_frame_after_press && state.row_state == animation_state_row_t::EndWriting && process_idle_animation) {
                anim_dm_start_or_process_animation(ctx, animation_state_row_t::Idle,      // back to idle
                                                new_animation_result, new_state,
                                                current_state, current_frames, current_config);
            } else if (!release_frame_after_press && is_writing) {
                // keep writing
                anim_dm_process_animation(new_animation_result, new_state, current_state, current_frames);
            }
        }

        return anim_update_animation_state(anim_shm, state,
                                            new_animation_result, new_state,
                                            current_animation_result, current_state,
                                            current_config);
    }

    static anim_next_frame_result_t anim_dm_working_next_frame(animation_context_t& ctx, const platform::update::update_context_t& upd,
                                                               animation_state_t& state) {
        using namespace assets;

        // read-only config
        assert(ctx._local_copy_config != nullptr);
        const config::config_t& current_config = *ctx._local_copy_config;

        assert(ctx.shm != nullptr);
        //assert(input.shm != nullptr);
        assert(upd.shm != nullptr);
        animation_shared_memory_t& anim_shm = *ctx.shm;
        //const auto& input_shm = *input.shm;
        const auto& update_shm = *upd.shm;
        const auto current_state = state;
        const auto& current_animation_result = anim_shm.animation_player_result;
        [[maybe_unused]] const int anim_index = anim_shm.anim_index;
        //const platform::timestamp_ms_t last_key_pressed_timestamp = input_shm.last_key_pressed_timestamp;
        const auto& current_frames = reinterpret_cast<dm_sprite_sheet_t&>(get_current_animation(ctx));

        auto new_animation_result = anim_shm.animation_player_result;
        auto new_state = state;

        const bool process_idle_animation = (current_config.idle_animation && current_config.animation_speed_ms > 0 && state.frame_delta_ms_counter > current_config.animation_speed_ms) || (current_config.idle_animation && current_config.animation_speed_ms <= 0 && state.frame_delta_ms_counter > 1000/current_config.fps);
        const bool process_working_animation = (current_config.animation_speed_ms > 0 && state.frame_delta_ms_counter > current_config.animation_speed_ms) || (current_config.animation_speed_ms <= 0 && state.frame_delta_ms_counter > 1000/current_config.fps);

        /// @TODO: use state machine for animation (states)

        if (process_working_animation && !process_idle_animation && !current_config.idle_animation && state.row_state == animation_state_row_t::EndWorking) {
            anim_dm_start_or_process_animation(ctx, animation_state_row_t::Idle,      // back to idle
                                            new_animation_result, new_state,
                                            current_state, current_frames, current_config);
        } else if (process_working_animation) {
            // toggle frame, show attack animation
            const bool above_threshold = current_config.cpu_threshold >= platform::ENABLED_MIN_CPU_PERCENT && (update_shm.avg_cpu_usage >= current_config.cpu_threshold || update_shm.max_cpu_usage >= current_config.cpu_threshold);
            const bool lower_threshold = current_config.cpu_threshold >= platform::ENABLED_MIN_CPU_PERCENT && (update_shm.avg_cpu_usage < current_config.cpu_threshold || update_shm.max_cpu_usage < current_config.cpu_threshold);
            if (above_threshold) {
                if (current_state.row_state == animation_state_row_t::Idle) {
                    anim_dm_restart_animation(ctx, animation_state_row_t::StartWorking,
                                                    new_animation_result, new_state,
                                                    current_state, current_frames, current_config);
                    BONGOCAT_LOG_VERBOSE("Start Working: %d %d; %d%%", above_threshold, lower_threshold, update_shm.avg_cpu_usage);
                } else if (update_shm.cpu_active && current_state.row_state == animation_state_row_t::StartWorking) {
                    anim_dm_start_or_process_animation(ctx, animation_state_row_t::Working,     // continue working
                                                    new_animation_result, new_state,
                                                    current_state, current_frames, current_config);
                } else if (!update_shm.cpu_active && (current_state.row_state == animation_state_row_t::StartWorking || state.row_state == animation_state_row_t::Working)) {
                    // end working, cool down
                    anim_dm_start_or_process_animation(ctx, animation_state_row_t::EndWorking,
                                            new_animation_result, new_state,
                                            current_state, current_frames, current_config);
                } else if (!update_shm.cpu_active && current_state.row_state == animation_state_row_t::EndWorking) {
                    // back to idle
                    anim_dm_start_or_process_animation(ctx, animation_state_row_t::Idle,
                                            new_animation_result, new_state,
                                            current_state, current_frames, current_config);
                }
            } else if (lower_threshold) {
                if (current_state.row_state == animation_state_row_t::Working) {
                    // end working, cool down
                    anim_dm_start_or_process_animation(ctx, animation_state_row_t::EndWorking,
                                            new_animation_result, new_state,
                                            current_state, current_frames, current_config);
                    if (new_state.row_state == animation_state_row_t::EndWorking) {
                        BONGOCAT_LOG_VERBOSE("Stop Working: %d %d; %d%%", above_threshold, lower_threshold, update_shm.avg_cpu_usage);
                    }
                } else if (current_state.row_state == animation_state_row_t::EndWorking) {
                    // back to idle
                    anim_dm_start_or_process_animation(ctx, animation_state_row_t::Idle,
                                            new_animation_result, new_state,
                                            current_state, current_frames, current_config);
                }
            }
        }

        return anim_update_animation_state(anim_shm, state,
                                            new_animation_result, new_state,
                                            current_animation_result, current_state,
                                            current_config);
    }
#endif

#ifdef FEATURE_MS_AGENT_EMBEDDED_ASSETS
    static anim_next_frame_result_t anim_ms_agent_idle_next_frame(animation_context_t& ctx, const platform::input::input_context_t& input,
                                                                  animation_state_t& state, const anim_handle_key_press_result_t& trigger_result) {
        using namespace assets;

        // read-only config
        assert(ctx._local_copy_config != nullptr);
        const config::config_t& current_config = *ctx._local_copy_config;

        assert(ctx.shm != nullptr);
        assert(input.shm != nullptr);
        //assert(upd.shm != nullptr);
        animation_shared_memory_t& anim_shm = *ctx.shm;
        const auto& input_shm = *input.shm;
        //const auto& update_shm = *upd.shm;
        const auto current_state = state;
        const auto& current_animation_result = anim_shm.animation_player_result;
        [[maybe_unused]] const int anim_index = anim_shm.anim_index;
        const platform::timestamp_ms_t last_key_pressed_timestamp = input_shm.last_key_pressed_timestamp;
        const auto& current_frames = reinterpret_cast<ms_agent_sprite_sheet_t&>(get_current_animation(ctx));

        auto new_animation_result = anim_shm.animation_player_result;
        auto new_state = state;

        const bool any_key_pressed = has_flag(trigger_result.trigger.anim_cause, trigger_animation_cause_mask_t::KeyPress) && trigger_result.trigger.any_key_press_counter > 0;

        const bool go_next_frame = (current_config.animation_speed_ms > 0 && current_state.frame_delta_ms_counter > current_config.animation_speed_ms) || (current_config.animation_speed_ms <= 0 && current_state.frame_delta_ms_counter > 1000/current_config.fps);
        const bool release_frame_after_press = (!any_key_pressed && !has_flag(trigger_result.trigger.anim_cause, trigger_animation_cause_mask_t::CpuUpdate)) && current_state.hold_frame_ms > current_config.keypress_duration_ms;
        const bool process_idle_animation = (current_config.idle_animation && current_config.animation_speed_ms > 0 && current_state.frame_delta_ms_counter > current_config.animation_speed_ms) || (current_config.idle_animation && current_config.animation_speed_ms <= 0 && current_state.frame_delta_ms_counter > 1000/current_config.fps);
        //const bool trigger_test_animation = current_config.test_animation_interval_sec > 0 && state.frame_delta_ms_counter > current_config.test_animation_interval_sec*1000;
        //const bool release_test_frame = current_config.test_animation_duration_ms > 0 && state.frame_delta_ms_counter > current_config.test_animation_duration_ms;
        const bool check_for_idle_sleep = current_config.idle_sleep_timeout_sec > 0 && current_state.frame_delta_ms_counter > current_config.idle_sleep_timeout_sec*1000/2;
        const bool process_movement = current_config.movement_speed > 0 && current_config.movement_radius > 0 && (current_state.frame_delta_ms_counter > current_config.movement_speed || current_state.frame_delta_ms_counter > 1000/current_config.fps);
        const bool process_movement_animation = current_config.movement_speed > 0 && current_config.movement_radius > 0 && ((current_config.animation_speed_ms > 0 && current_state.frame_delta_ms_counter > current_config.animation_speed_ms) || (current_config.animation_speed_ms <= 0 && current_state.frame_delta_ms_counter > 1000/current_config.fps));

        /// @TODO: extract state change and player_data update

        const bool is_moving = current_state.row_state == animation_state_row_t::StartMoving || current_state.row_state == animation_state_row_t::Moving || current_state.row_state == animation_state_row_t::EndMoving || current_state.row_state == animation_state_row_t::StartMoving || current_state.row_state == animation_state_row_t::Moving || current_state.row_state == animation_state_row_t::EndMoving;
        const auto delta = 1.0f / static_cast<float>(current_config.fps);
        const auto delta_ms = static_cast<int32_t>(delta * 1000);
        //const auto frame_height = current_config.cat_height;
        //const auto frame_width  = static_cast<int>(static_cast<float>(frame_height) * (static_cast<float>(current_frames.frame_width) / static_cast<float>(current_frames.frame_height)));
        const auto fmovement_radius = static_cast<float>(current_config.movement_radius);
        constexpr float DIR_EPSILON = 1e-3f;
        assert(MAX_DISTANCE_PER_MOVEMENT_PART > 0);
        const auto movement_part = current_config.movement_radius <= MAX_MOVEMENT_RADIUS_SMALL ? SMALL_MAX_DISTANCE_PER_MOVEMENT_PART : MAX_DISTANCE_PER_MOVEMENT_PART;
        const auto fmovement_part = static_cast<float>(movement_part);

        const auto min_movement = current_config.movement_radius <= MAX_MOVEMENT_RADIUS_SMALL ? (fmovement_radius / fmovement_part / 2) + 1 : (fmovement_radius / fmovement_part / fmovement_part) + 1;
        auto max_move_distance = fmovement_radius / fmovement_part;
        max_move_distance = max_move_distance <= min_movement ? min_movement : max_move_distance;
        float max_movement_offset_x_left = 0.0f;
        float max_movement_offset_x_right = 0.0f;
        float wall_distance = 0.0f;

        return anim_update_animation_state(anim_shm, state,
                                            new_animation_result, new_state,
                                            current_animation_result, current_state,
                                            current_config);
    }


    static anim_next_frame_result_t anim_ms_agent_key_pressed_next_frame(animation_context_t& ctx,
                                                                         animation_state_t& state,
                                                                         const platform::input::input_context_t& input,
                                                                         const animation_trigger_t& trigger) {
        using namespace assets;

        // read-only config
        assert(ctx._local_copy_config != nullptr);
        const config::config_t& current_config = *ctx._local_copy_config;

        assert(ctx.shm != nullptr);
        assert(input.shm != nullptr);
        animation_shared_memory_t& anim_shm = *ctx.shm;
        const auto& input_shm = *input.shm;
        const auto current_state = state;
        const auto& current_animation_result = anim_shm.animation_player_result;
        [[maybe_unused]] const int anim_index = anim_shm.anim_index;
        const platform::timestamp_ms_t last_key_pressed_timestamp = input_shm.last_key_pressed_timestamp;
        const auto& current_frames = reinterpret_cast<ms_agent_sprite_sheet_t&>(get_current_animation(ctx));

        auto new_animation_result = anim_shm.animation_player_result;
        auto new_state = state;

        const bool any_key_pressed = has_flag(trigger.anim_cause, trigger_animation_cause_mask_t::KeyPress) && trigger.any_key_press_counter > 0;

        const bool release_frame_after_press = !any_key_pressed && current_state.hold_frame_ms > current_config.keypress_duration_ms;
        const bool process_idle_animation = (current_config.idle_animation && current_config.animation_speed_ms > 0 && current_state.frame_delta_ms_counter > current_config.animation_speed_ms) || (current_config.idle_animation && current_config.animation_speed_ms <= 0 && current_state.frame_delta_ms_counter > 1000/current_config.fps);

        const bool is_writing = state.row_state == animation_state_row_t::StartWriting || state.row_state == animation_state_row_t::Writing || state.row_state == animation_state_row_t::EndWriting;

        return anim_update_animation_state(anim_shm, state,
                                            new_animation_result, new_state,
                                            current_animation_result, current_state,
                                            current_config);
    }


    static anim_next_frame_result_t anim_ms_agent_working_next_frame(animation_context_t& ctx, const platform::update::update_context_t& upd,
                                                                     animation_state_t& state) {
        using namespace assets;

        // read-only config
        assert(ctx._local_copy_config != nullptr);
        const config::config_t& current_config = *ctx._local_copy_config;

        assert(ctx.shm != nullptr);
        assert(upd.shm != nullptr);
        //assert(input.shm != nullptr);
        animation_shared_memory_t& anim_shm = *ctx.shm;
        //const auto& input_shm = *input.shm;
        const auto& update_shm = *upd.shm;
        const auto current_state = state;
        const auto& current_animation_result = anim_shm.animation_player_result;
        [[maybe_unused]] const int anim_index = anim_shm.anim_index;
        //const platform::timestamp_ms_t last_key_pressed_timestamp = input_shm.last_key_pressed_timestamp;
        const auto& current_frames = reinterpret_cast<ms_agent_sprite_sheet_t&>(get_current_animation(ctx));

        auto new_animation_result = anim_shm.animation_player_result;
        auto new_state = state;

        const bool process_working_animation = (current_config.animation_speed_ms > 0 && state.frame_delta_ms_counter > current_config.animation_speed_ms) || (current_config.animation_speed_ms <= 0 && state.frame_delta_ms_counter > 1000/current_config.fps);

        /// @TODO: use state machine for animation (states)

        return anim_update_animation_state(anim_shm, state,
                                            new_animation_result, new_state,
                                            current_animation_result, current_state,
                                            current_config);
    }
#endif


#ifdef FEATURE_PKMN_EMBEDDED_ASSETS
    static anim_next_frame_result_t anim_pkmn_idle_next_frame(animation_context_t& ctx, [[maybe_unused]] const platform::input::input_context_t& input,
                                                              animation_state_t& state, const anim_handle_key_press_result_t& trigger_result) {
        using namespace assets;
        // read-only config
        assert(ctx._local_copy_config != nullptr);
        const config::config_t& current_config = *ctx._local_copy_config;

        assert(ctx.shm != nullptr);
        assert(input.shm != nullptr);
        animation_shared_memory_t& anim_shm = *ctx.shm;
        const auto& input_shm = *input.shm;
        const auto current_state = state;
        const auto& current_animation_result = anim_shm.animation_player_result;
        [[maybe_unused]] const int anim_index = anim_shm.anim_index;
        const platform::timestamp_ms_t last_key_pressed_timestamp = input_shm.last_key_pressed_timestamp;
        const auto& current_frames = reinterpret_cast<pkmn_sprite_sheet_t&>(get_current_animation(ctx));

        auto new_animation_result = anim_shm.animation_player_result;
        auto new_state = state;

        const bool any_key_pressed = has_flag(trigger_result.trigger.anim_cause, trigger_animation_cause_mask_t::KeyPress) && trigger_result.trigger.any_key_press_counter > 0;

        // @TODO: get variables as struct to make it more reusable
        const bool release_frame_after_press = !any_key_pressed && state.hold_frame_ms > current_config.keypress_duration_ms;
        const bool process_idle_animation = (current_config.idle_animation && current_config.animation_speed_ms > 0 && state.frame_delta_ms_counter > current_config.animation_speed_ms) || (current_config.idle_animation && current_config.animation_speed_ms <= 0 && state.frame_delta_ms_counter > 1000/current_config.fps);
        const bool trigger_test_animation = current_config.test_animation_interval_sec > 0 && state.frame_delta_ms_counter > current_config.test_animation_interval_sec*1000;
        const bool release_test_frame = current_config.test_animation_duration_ms > 0 && state.frame_delta_ms_counter > current_config.test_animation_duration_ms;

        return anim_update_animation_state(anim_shm, state,
                                            new_animation_result, new_state,
                                            current_animation_result, current_state,
                                            current_config);
    }

    static anim_next_frame_result_t anim_pkmn_key_pressed_next_frame(animation_context_t& ctx, [[maybe_unused]] const platform::input::input_context_t& input,
                                                                     animation_state_t& state,
                                                                     const animation_trigger_t& trigger) {
        using namespace assets;

        // read-only config
        assert(ctx._local_copy_config != nullptr);
        const config::config_t& current_config = *ctx._local_copy_config;

        assert(ctx.shm != nullptr);
        assert(input.shm != nullptr);
        animation_shared_memory_t& anim_shm = *ctx.shm;
        const auto& input_shm = *input.shm;
        const auto current_state = state;
        const auto& current_animation_result = anim_shm.animation_player_result;
        [[maybe_unused]] const int anim_index = anim_shm.anim_index;
        const platform::timestamp_ms_t last_key_pressed_timestamp = input_shm.last_key_pressed_timestamp;
        const auto& current_frames = reinterpret_cast<pkmn_sprite_sheet_t&>(get_current_animation(ctx));

        auto new_animation_result = anim_shm.animation_player_result;
        auto new_state = state;

        /// @TODO: use state machine for animation (states)

        return anim_update_animation_state(anim_shm, state,
                                            new_animation_result, new_state,
                                            current_animation_result, current_state,
                                            current_config);
    }
#endif

    static bool anim_handle_idle_animation(animation_context_t& ctx,
                                            [[maybe_unused]] const platform::input::input_context_t& input,
                                            [[maybe_unused]] const platform::update::update_context_t& upd,
                                            animation_state_t& state, const anim_handle_key_press_result_t& trigger_result) {
        using namespace assets;

        // read-only config
        assert(ctx._local_copy_config != nullptr);
        //const config::config_t& current_config = *ctx._local_copy_config;

        assert(input.shm != nullptr);
        assert(ctx.shm != nullptr);
        animation_shared_memory_t& anim_shm = *ctx.shm;
        //const auto& input_shm = *input.shm;
        //auto& animation_player_data = anim_shm.animation_player_data;
        //const int current_frame = animation_player_data.frame_index;
        //const int current_row = animation_player_data.sprite_sheet_row;
        //const animation_state_row_t current_row_state = state.row_state;
        //const int anim_index = anim_shm.anim_index;

        bool ret = false;
        switch (anim_shm.anim_type) {
            case config::config_animation_sprite_sheet_layout_t::None:
                break;
            case config::config_animation_sprite_sheet_layout_t::Bongocat: {
#ifdef FEATURE_BONGOCAT_EMBEDDED_ASSETS
                auto [changed, new_frame] = anim_bongocat_idle_next_frame(ctx, input, state, trigger_result);
                ret = changed;
#endif
            }break;
            case config::config_animation_sprite_sheet_layout_t::Dm: {
#ifdef FEATURE_ENABLE_DM_EMBEDDED_ASSETS
                auto [changed, new_frame] = anim_dm_idle_next_frame(ctx, input, upd, state, trigger_result);
                ret = changed;
#endif
            }break;
            case config::config_animation_sprite_sheet_layout_t::Pkmn: {
#ifdef FEATURE_PKMN_EMBEDDED_ASSETS
                auto [changed, new_frame] = anim_pkmn_idle_next_frame(ctx, input, state, trigger_result);
                ret = changed;
#endif
            }break;
            case config::config_animation_sprite_sheet_layout_t::MsAgent: {
#ifdef FEATURE_MS_AGENT_EMBEDDED_ASSETS
                auto [changed, new_frame] = anim_ms_agent_idle_next_frame(ctx, input, state, trigger_result);
                ret = changed;
#endif
            }break;
        }
        return ret;
    }

    static anim_handle_key_press_result_t anim_handle_animation_trigger(animation_session_t& animation_trigger_ctx, animation_state_t& state, const animation_trigger_t& trigger) {
        using namespace assets;

        assert(animation_trigger_ctx._input != nullptr);
        assert(animation_trigger_ctx._input->shm != nullptr);
        assert(animation_trigger_ctx._update != nullptr);
        assert(animation_trigger_ctx._update->shm != nullptr);
        animation_context_t& ctx = animation_trigger_ctx.anim;
        [[maybe_unused]] const platform::input::input_context_t& input = *animation_trigger_ctx._input;
        [[maybe_unused]] const platform::update::update_context_t& upd = *animation_trigger_ctx._update;

        // read-only config
        //assert(ctx._local_copy_config != nullptr);
        //assert(ctx.shm != nullptr);
        //assert(animation_trigger_ctx._config != nullptr);
        //const config::config_t& current_config = *ctx._local_copy_config;

        assert(input.shm != nullptr);
        assert(upd.shm != nullptr);
        assert(ctx.shm != nullptr);
        animation_shared_memory_t& anim_shm = *ctx.shm;
        //const auto& input_shm = *input.shm;
        const auto current_state = state;
        const auto& current_animation_result = anim_shm.animation_player_result;
        [[maybe_unused]] const int anim_index = anim_shm.anim_index;

        bool ret = false;
        [[maybe_unused]] int ret_new_frame = current_animation_result.sprite_sheet_col;

        // handle working animation
        if (has_flag(trigger.anim_cause, trigger_animation_cause_mask_t::CpuUpdate)) {
            switch (anim_shm.anim_type) {
                case config::config_animation_sprite_sheet_layout_t::None:
                    break;
                case config::config_animation_sprite_sheet_layout_t::Bongocat:
                    break;
                case config::config_animation_sprite_sheet_layout_t::Dm: {
#ifdef FEATURE_ENABLE_DM_EMBEDDED_ASSETS
                    auto [changed, new_frame] = anim_dm_working_next_frame(ctx, upd, state);
                    ret = changed;
                    ret_new_frame = new_frame;
#endif
                }break;
                case config::config_animation_sprite_sheet_layout_t::Pkmn:
                    break;
                case config::config_animation_sprite_sheet_layout_t::MsAgent: {
#ifdef FEATURE_MS_AGENT_EMBEDDED_ASSETS
                    auto [changed, new_frame] = anim_ms_agent_working_next_frame(ctx, upd, state);
                    ret = changed;
                    ret_new_frame = new_frame;
#endif
                }break;
            }
            BONGOCAT_LOG_VERBOSE("CPU update detected - switching to frame %d (%zu)", ret_new_frame, trigger.anim_cause);
        }

        // handle key press animation
        if (has_flag(trigger.anim_cause, trigger_animation_cause_mask_t::KeyPress)) {
            switch (anim_shm.anim_type) {
                case config::config_animation_sprite_sheet_layout_t::None:
                    break;
                case config::config_animation_sprite_sheet_layout_t::Bongocat: {
#ifdef FEATURE_BONGOCAT_EMBEDDED_ASSETS
                    auto [changed, new_frame] = anim_bongocat_key_pressed_next_frame(ctx, state, input, trigger);
                    ret = changed;
                    ret_new_frame = new_frame;
#endif
                }break;
                case config::config_animation_sprite_sheet_layout_t::Dm: {
#ifdef FEATURE_ENABLE_DM_EMBEDDED_ASSETS
                    auto [changed, new_frame] = anim_dm_key_pressed_next_frame(ctx, input, state, trigger);
                    ret = changed;
                    ret_new_frame = new_frame;
#endif
                }break;
                case config::config_animation_sprite_sheet_layout_t::Pkmn: {
#ifdef FEATURE_PKMN_EMBEDDED_ASSETS
                    auto [changed, new_frame] = anim_pkmn_key_pressed_next_frame(ctx, input, state, trigger);
                    ret = changed;
                    ret_new_frame = new_frame;
#endif
                }break;
                case config::config_animation_sprite_sheet_layout_t::MsAgent: {
#ifdef FEATURE_MS_AGENT_EMBEDDED_ASSETS
                    auto [changed, new_frame] = anim_ms_agent_key_pressed_next_frame(ctx, state, input, trigger);
                    ret = changed;
                    ret_new_frame = new_frame;
#endif
                }break;
            }
            BONGOCAT_LOG_VERBOSE("Key press detected - switching to frame %d (%zu)", ret_new_frame, trigger.anim_cause);
        }

        return { .trigger = trigger, .changed = ret};
    }

    static bool anim_update_state(animation_session_t& animation_trigger_ctx, animation_state_t& state, const animation_trigger_t& trigger) {
        assert(animation_trigger_ctx._input);
        platform::input::input_context_t& input = *animation_trigger_ctx._input;
        platform::update::update_context_t& upd = *animation_trigger_ctx._update;
        animation_context_t& ctx = animation_trigger_ctx.anim;
        // read-only config
        assert(ctx._local_copy_config != nullptr);
        const config::config_t& current_config = *ctx._local_copy_config;

        bool ret = false;
        {
            state.frame_delta_ms_counter += state.frame_time_ms;

            anim_handle_key_press_result_t trigger_result;
            bool idle_changed = false;
            bool hold_frame = false;
            bool key_pressed = false;
            {
                platform::LockGuard input_guard (input.input_lock);
                platform::LockGuard update_guard (upd.update_lock);
                trigger_result = anim_handle_animation_trigger(animation_trigger_ctx, state, trigger);
                hold_frame = has_flag(trigger_result.trigger.anim_cause, trigger_animation_cause_mask_t::KeyPress) || has_flag(trigger_result.trigger.anim_cause, trigger_animation_cause_mask_t::CpuUpdate);
                idle_changed = anim_handle_idle_animation(ctx, input, upd, state, trigger_result);
            }
            key_pressed = has_flag(trigger_result.trigger.anim_cause, trigger_animation_cause_mask_t::KeyPress) && trigger_result.trigger.any_key_press_counter > 0;
            ret = idle_changed || trigger_result.changed;
            if (key_pressed) {
                BONGOCAT_LOG_VERBOSE("Trigger key press animation");
            }
            if (idle_changed) {
                BONGOCAT_LOG_VERBOSE("Trigger idle animation");
            }

            if (!state.hold_frame_after_release && hold_frame) {
                state.hold_frame_after_release = true;
            }
            if (state.hold_frame_after_release && (!key_pressed && !hold_frame) && state.hold_frame_ms > current_config.keypress_duration_ms && idle_changed) {
                state.hold_frame_after_release = false;
                state.hold_frame_ms = 0;
            }
            if (state.hold_frame_after_release) {
                state.hold_frame_ms += state.frame_time_ms;
            }
        }

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

        state.hold_frame_ms = 0;
        state.frame_delta_ms_counter = 0;
        state.frame_time_ns = 1000000000LL / current_config.fps;
        state.frame_time_ms = state.frame_time_ns/1000000LL;
        state.last_frame_update_ms = platform::get_current_time_ms();
        state.row_state = animation_state_row_t::Idle;
    }

    static void cleanup_anim_thread(void* arg) {
        assert(arg);
        animation_session_t& trigger_ctx = *static_cast<animation_session_t*>(arg);

        atomic_store(&trigger_ctx.anim._animation_running, false);

        trigger_ctx.anim.config_updated.notify_all();

        BONGOCAT_LOG_INFO("Animation thread cleanup completed (via pthread_cancel)");
    }

    static void *anim_thread(void *arg) {
        using namespace assets;

        assert(arg);
        auto& trigger_ctx = *static_cast<animation_session_t*>(arg);

        // sanity checks
        assert(trigger_ctx._config != nullptr);
        assert(trigger_ctx._input != nullptr);
        assert(trigger_ctx._update != nullptr);
        assert(trigger_ctx._configs_reloaded_cond != nullptr);
        assert(trigger_ctx.anim.shm != nullptr);
        assert(trigger_ctx.trigger_efd._fd >= 0);
        assert(trigger_ctx.render_efd._fd >= 0);
        assert(trigger_ctx.anim.update_config_efd._fd >= 0);

        // init animation state
        animation_state_t state;
        {
            platform::LockGuard guard (trigger_ctx.anim.anim_lock);
            animation_context_t& ctx = trigger_ctx.anim;

            assert(ctx.shm != nullptr);
            //assert(input.shm != nullptr);
            animation_shared_memory_t& anim_shm = *ctx.shm;
            //const auto& input_shm = *input.shm;
            auto& current_state = state;
            auto& current_animation_result = anim_shm.animation_player_result;
            [[maybe_unused]] const int anim_index = anim_shm.anim_index;

            // read-only config
            assert(ctx._local_copy_config != nullptr);
            const config::config_t& current_config = *ctx._local_copy_config;

            anim_init_state(ctx, state);

            // setup animation player
            switch (current_config.animation_sprite_sheet_layout) {
                case config::config_animation_sprite_sheet_layout_t::None:
                    break;
                case config::config_animation_sprite_sheet_layout_t::Bongocat:
#ifdef FEATURE_BONGOCAT_EMBEDDED_ASSETS
                    current_animation_result.sprite_sheet_col = current_config.idle_frame;
                    current_animation_result.sprite_sheet_row = BONGOCAT_SPRITE_SHEET_ROW;
                    state.animations_index = 0;
                    state.row_state = animation_state_row_t::Idle;
#endif
                    break;
                case config::config_animation_sprite_sheet_layout_t::Dm:
#ifdef FEATURE_ENABLE_DM_EMBEDDED_ASSETS
                    current_animation_result.sprite_sheet_col = current_config.idle_frame;
                    current_animation_result.sprite_sheet_row = DM_SPRITE_SHEET_ROW;
                    state.animations_index = 0;
                    state.row_state = animation_state_row_t::Idle;
#endif
                    break;
                case config::config_animation_sprite_sheet_layout_t::Pkmn:
#ifdef FEATURE_PKMN_EMBEDDED_ASSETS
                    current_animation_result.sprite_sheet_col = current_config.idle_frame;
                    current_animation_result.sprite_sheet_row = PKMN_SPRITE_SHEET_ROW;
                    state.animations_index = 0;
                    state.row_state = animation_state_row_t::Idle;
#endif
                    break;
                case config::config_animation_sprite_sheet_layout_t::MsAgent: {
#ifdef FEATURE_MS_AGENT_EMBEDDED_ASSETS
                    assert(anim_shm.anim_index >= 0);
                    const ms_agent_animation_indices_t animation_indices = get_ms_agent_animation_indices(static_cast<size_t>(anim_shm.anim_index));
                    current_animation_result.sprite_sheet_col = current_config.idle_frame;
                    current_animation_result.sprite_sheet_row = MS_AGENT_SPRITE_SHEET_ROW_IDLE;
                    state.start_col_index = animation_indices.start_index_frame_idle;
                    state.end_col_index = animation_indices.end_index_frame_idle;
                    state.row_state = animation_state_row_t::Idle;
#endif
                }break;
            }
        }

        BONGOCAT_LOG_DEBUG("Animation thread main loop started");

        // trigger initial render
        platform::wayland::request_render(trigger_ctx);

        pthread_cleanup_push(cleanup_anim_thread, arg);

        // local thread context
        timespec next_frame_time{};
        clock_gettime(CLOCK_MONOTONIC, &next_frame_time);

        atomic_store(&trigger_ctx.anim._animation_running, true);
        while (atomic_load(&trigger_ctx.anim._animation_running)) {
            pthread_testcancel();  // optional, but makes cancellation more responsive

            animation_context_t& ctx = trigger_ctx.anim;

            // read from config
            platform::time_ms_t timeout_ms;
            int32_t fps = 1;
            {
                assert(ctx._local_copy_config != nullptr);
                const config::config_t& current_config = *ctx._local_copy_config;

                fps = current_config.fps;
                timeout_ms = current_config.fps > 0 ? 1000 / current_config.fps / 3 : POOL_MIN_TIMEOUT_MS;
                timeout_ms = timeout_ms < POOL_MIN_TIMEOUT_MS ? POOL_MIN_TIMEOUT_MS : timeout_ms;
                timeout_ms = timeout_ms > POOL_MAX_TIMEOUT_MS ? POOL_MAX_TIMEOUT_MS : timeout_ms;
            }

            trigger_animation_cause_mask_t triggered_anim_cause = trigger_animation_cause_mask_t::NONE;
            int any_key_press_counter = 0;

            bool reload_config = false;
            uint64_t new_gen{atomic_load(trigger_ctx._config_generation)};

            /// event poll
            constexpr size_t fds_update_config_index = 0;
            constexpr size_t fds_animation_trigger_index = 1;
            constexpr nfds_t fds_count = 2;
            pollfd fds[fds_count] = {
                { .fd = trigger_ctx.anim.update_config_efd._fd, .events = POLLIN, .revents = 0 },
                { .fd = trigger_ctx.trigger_efd._fd, .events = POLLIN, .revents = 0 },
            };

            assert(timeout_ms <= INT_MAX);
            const int poll_result = poll(fds, fds_count, static_cast<int>(timeout_ms));
            if (poll_result < 0) {
                if (errno == EINTR) continue; // Interrupted by signal
                BONGOCAT_LOG_ERROR("animation: Poll error: %s", strerror(errno));
                break;
            }
            if (poll_result > 0) {
                // cancel pooling (when not running anymore)
                if (!atomic_load(&ctx._animation_running)) {
                    // draining pools
                    for (size_t i = 0; i < fds_count; i++) {
                        platform::drain_event(fds[i], MAX_ATTEMPTS);
                    }
                    break;
                }

                // Handle config update
                if (fds[fds_update_config_index].revents & POLLIN) {
                    BONGOCAT_LOG_DEBUG("animation: Receive update config event");
                    platform::drain_event(fds[fds_update_config_index], MAX_ATTEMPTS, "update config eventfd");
                    reload_config = new_gen > 0;
                }

                // animation trigger event
                if (fds[fds_animation_trigger_index].revents & POLLIN) {
                    BONGOCAT_LOG_VERBOSE("Receive animation trigger event");
                    uint64_t u;
                    ssize_t rc;
                    int attempts = 0;
                    assert(MAX_ATTEMPTS <= INT_MAX);
                    while ((rc = read(trigger_ctx.trigger_efd._fd, &u, sizeof(u))) == sizeof(u) &&
                           attempts < static_cast<int>(MAX_ATTEMPTS))
                    {
                        attempts++;
                        auto cause = static_cast<trigger_animation_cause_mask_t>(u);
                        switch (cause) {
                            case trigger_animation_cause_mask_t::NONE:
                                break;
                            case trigger_animation_cause_mask_t::Init:
                                triggered_anim_cause = flag_add(triggered_anim_cause, cause);
                                break;
                            case trigger_animation_cause_mask_t::KeyPress:
                                any_key_press_counter++;
                                triggered_anim_cause = flag_add(triggered_anim_cause, cause);
                                break;
                            case trigger_animation_cause_mask_t::IdleUpdate:
                                triggered_anim_cause = flag_add(triggered_anim_cause, cause);
                                break;
                            case trigger_animation_cause_mask_t::CpuUpdate:
                                triggered_anim_cause = flag_add(triggered_anim_cause, cause);
                                break;
                            case trigger_animation_cause_mask_t::UpdateConfig:
                                triggered_anim_cause = flag_add(triggered_anim_cause, cause);
                                break;
                            case trigger_animation_cause_mask_t::Timeout:
                                triggered_anim_cause = flag_add(triggered_anim_cause, cause);
                                break;
                        }
                    }
                    if (rc < 0) {
                        check_errno("animation trigger eventfd");
                    }

                    BONGOCAT_LOG_VERBOSE("animation trigger: %zu", triggered_anim_cause);
                } else {
                    triggered_anim_cause = flag_add(triggered_anim_cause, trigger_animation_cause_mask_t::Timeout);
                    triggered_anim_cause = flag_add(triggered_anim_cause, trigger_animation_cause_mask_t::CpuUpdate);
                }
            }

            // Update Animations
            {
                platform::LockGuard guard (trigger_ctx.anim.anim_lock);
                assert(ctx.shm != nullptr);
                const bool frame_changed = anim_update_state(trigger_ctx, state, {
                    .anim_cause = triggered_anim_cause,
                    .any_key_press_counter = any_key_press_counter,
                });
                if (frame_changed) {
                    uint64_t u = 1;
                    if (write(trigger_ctx.render_efd._fd, &u, sizeof(uint64_t)) >= 0) {
                        BONGOCAT_LOG_VERBOSE("animation: Write animation render event");
                    } else {
                        BONGOCAT_LOG_ERROR("animation: Failed to write to notify pipe in animation: %s", strerror(errno));
                    }
                }

                // Advance next frame time by exactly one frame
                next_frame_time.tv_nsec += state.frame_time_ns;
                while (next_frame_time.tv_nsec >= 1000000000LL) {
                    next_frame_time.tv_nsec -= 1000000000LL;
                    next_frame_time.tv_sec += 1;
                }

                timespec now{};
                clock_gettime(CLOCK_MONOTONIC, &now);

                // If we're already past the next frame time, catch up (skip missed frames)
                if ((now.tv_sec > next_frame_time.tv_sec) ||
                    (now.tv_sec == next_frame_time.tv_sec && now.tv_nsec > next_frame_time.tv_nsec)) {
                    // Skip ahead until next_frame_time is >= now
                    do {
                        next_frame_time.tv_nsec += state.frame_time_ns;
                        while (next_frame_time.tv_nsec >= 1000000000LL) {
                            next_frame_time.tv_nsec -= 1000000000LL;
                            next_frame_time.tv_sec += 1;
                        }
                    } while ((now.tv_sec > next_frame_time.tv_sec) ||
                             (now.tv_sec == next_frame_time.tv_sec && now.tv_nsec > next_frame_time.tv_nsec));

                    state.time_until_next_frame_ms = 0;
                    //BONGOCAT_LOG_VERBOSE("Animation skipped frame(s) to catch up");
                } else {
                    // Sleep until the next frame using absolute time
                    const auto sec_diff  = next_frame_time.tv_sec  - now.tv_sec;
                    const auto nsec_diff = next_frame_time.tv_nsec - now.tv_nsec;
                    state.time_until_next_frame_ms = static_cast<platform::time_ms_t>(sec_diff * 1000L + (nsec_diff + 999999LL) / 1000000LL);

                    if (clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &next_frame_time, nullptr) != 0) {
                        // Interrupted, just continue
                    }
                }

                // Update variables from config in case FPS changed
                state.frame_time_ns = (fps > 0) ? 1000000000LL / fps : 1000000000LL / DEFAULT_FPS;
                state.frame_time_ms = state.frame_time_ns / 1000000LL;
            }

            // handle update config
            if (reload_config) {
                assert(trigger_ctx._config_generation != nullptr);
                assert(trigger_ctx._configs_reloaded_cond != nullptr);
                assert(trigger_ctx._config != nullptr);

                update_config(ctx, *trigger_ctx._config, new_gen);

                // wait for reload config to be done (all configs)
                const int rc = trigger_ctx._configs_reloaded_cond->timedwait([&] {
                    return atomic_load(trigger_ctx._config_generation) >= new_gen;
                }, COND_RELOAD_CONFIGS_TIMEOUT_MS);
                if (rc == ETIMEDOUT) {
                    BONGOCAT_LOG_WARNING("animation: Timed out waiting for reload eventfd: %s", strerror(errno));
                }
                if constexpr (features::Debug) {
                    if (atomic_load(&trigger_ctx.anim.config_seen_generation) < atomic_load(trigger_ctx._config_generation)) {
                        BONGOCAT_LOG_VERBOSE("animation: trigger_ctx.anim.config_seen_generation < trigger_ctx._config_generation; %d < %d", atomic_load(&trigger_ctx.anim.config_seen_generation), atomic_load(trigger_ctx._config_generation));
                    }
                }
                //assert(atomic_load(&trigger_ctx.anim.config_seen_generation) >= atomic_load(trigger_ctx._config_generation));
                atomic_store(&trigger_ctx.anim.config_seen_generation, atomic_load(trigger_ctx._config_generation));
                BONGOCAT_LOG_INFO("animation: Animation config reloaded (gen=%u)", new_gen);
            }
        }

        // Will run only on normal return
        pthread_cleanup_pop(1);  // 1 = call cleanup even if not canceled

        // done when callback cleanup_anim_context
        //cleanup_anim_context(arg);

        BONGOCAT_LOG_INFO("Animation thread main loop exited");

        return nullptr;
    }

    // =============================================================================
    // PUBLIC API IMPLEMENTATION
    // =============================================================================

    bongocat_error_t start(animation_session_t& trigger_ctx, platform::input::input_context_t& input, platform::update::update_context_t& upd, const config::config_t& config, platform::CondVariable& configs_reloaded_cond, atomic_uint64_t& config_generation) {
        BONGOCAT_LOG_INFO("Starting animation thread");

        // Initialize shared memory for local config
        trigger_ctx.anim._local_copy_config = platform::make_allocated_mmap<config::config_t>();
        if (!trigger_ctx.anim._local_copy_config.ptr) {
            BONGOCAT_LOG_ERROR("Failed to create shared memory for input monitoring: %s", strerror(errno));
            return bongocat_error_t::BONGOCAT_ERROR_MEMORY;
        }
        assert(trigger_ctx.anim._local_copy_config != nullptr);
        update_config(trigger_ctx.anim, config, atomic_load(&config_generation));

        // set extern/global references
        trigger_ctx._input = &input;
        trigger_ctx._update = &upd;
        trigger_ctx._config = &config;
        trigger_ctx._configs_reloaded_cond = &configs_reloaded_cond;
        trigger_ctx._config_generation = &config_generation;
        atomic_store(&trigger_ctx.ready, true);
        trigger_ctx.init_cond.notify_all();

        trigger_ctx._configs_reloaded_cond->notify_all();

        // start animation thread
        const int result = pthread_create(&trigger_ctx.anim._anim_thread, nullptr, anim_thread, &trigger_ctx);
        if (result != 0) {
            BONGOCAT_LOG_ERROR("Failed to create animation thread: %s", strerror(result));
            return bongocat_error_t::BONGOCAT_ERROR_THREAD;
        }

        BONGOCAT_LOG_DEBUG("Animation thread started successfully");
        return bongocat_error_t::BONGOCAT_SUCCESS;
    }


    void trigger(animation_session_t& trigger_ctx, trigger_animation_cause_mask_t cause) {
        const auto u = static_cast<uint64_t>(cause);
        if (write(trigger_ctx.trigger_efd._fd, &u, sizeof(uint64_t)) >= 0) {
            BONGOCAT_LOG_VERBOSE("Write animation trigger event: %zu", cause);
        } else {
            BONGOCAT_LOG_ERROR("Failed to write to notify pipe in animation: %s", strerror(errno));
        }
    }

    void trigger_update_config(animation_session_t& trigger_ctx, const config::config_t& config, uint64_t config_generation) {
        //assert(trigger_ctx.anim._local_copy_config != nullptr);
        //assert(trigger_ctx.anim.shm != nullptr);

        trigger_ctx._config = &config;
        if (write(trigger_ctx.anim.update_config_efd._fd, &config_generation, sizeof(uint64_t)) >= 0) {
            BONGOCAT_LOG_VERBOSE("Write animation trigger update config");
        } else {
            BONGOCAT_LOG_ERROR("Failed to write to notify pipe in animation: %s", strerror(errno));
        }
    }

    [[nodiscard]] static int rand_animation_index(animation_context_t& ctx, const config::config_t& config) {
        using namespace assets;
        assert(ctx._local_copy_config != nullptr);
        assert(ctx.shm != nullptr);
        platform::random_xoshiro128& rng = ctx._rng;

        if (config.randomize_index) {
            if constexpr (features::EnableLazyLoadAssets) {
                switch (config.animation_sprite_sheet_layout) {
                    case config::config_animation_sprite_sheet_layout_t::None:
                        return config.animation_index;
                    case config::config_animation_sprite_sheet_layout_t::Bongocat:
                        assert(BONGOCAT_ANIM_COUNT <= INT32_MAX && BONGOCAT_ANIM_COUNT <= UINT32_MAX);
                        return BONGOCAT_ANIM_COUNT > 0 ? static_cast<int32_t>(rng.range(0, BONGOCAT_ANIM_COUNT-1)) : 0;
                    case config::config_animation_sprite_sheet_layout_t::Dm:
                        switch (ctx.shm->anim_dm_set) {
                        case config::config_animation_dm_set_t::None:
                            return config.animation_index;
                        case config::config_animation_dm_set_t::min_dm:
                            assert(MIN_DM_ANIM_COUNT <= INT32_MAX && MIN_DM_ANIM_COUNT<= UINT32_MAX);
                            return MIN_DM_ANIM_COUNT > 0 ? static_cast<int32_t>(rng.range(0, MIN_DM_ANIM_COUNT-1)) : 0;
                        case config::config_animation_dm_set_t::dm:
                            assert(DM_ANIM_COUNT <= INT32_MAX && DM_ANIM_COUNT <= UINT32_MAX);
                            return DM_ANIM_COUNT > 0 ? static_cast<int32_t>(rng.range(0, DM_ANIM_COUNT-1)) : 0;
                        case config::config_animation_dm_set_t::dm20:
                            assert(DM20_ANIM_COUNT <= INT32_MAX && DM20_ANIM_COUNT <= UINT32_MAX);
                            return DM20_ANIM_COUNT > 0 ? static_cast<int32_t>(rng.range(0, DM20_ANIM_COUNT-1)) : 0;
                        case config::config_animation_dm_set_t::dmx:
                            assert(DMX_ANIM_COUNT<= INT32_MAX && DMX_ANIM_COUNT <= UINT32_MAX);
                                return DMX_ANIM_COUNT > 0 ? static_cast<int32_t>(rng.range(0, DMX_ANIM_COUNT-1)) : 0;
                        case config::config_animation_dm_set_t::pen:
                                assert(PEN_ANIM_COUNT <= INT32_MAX && PEN_ANIM_COUNT <= UINT32_MAX);
                                return PEN_ANIM_COUNT > 0 ? static_cast<int32_t>(rng.range(0, PEN_ANIM_COUNT-1)) : 0;
                        case config::config_animation_dm_set_t::pen20:
                                assert(PEN20_ANIM_COUNT <= INT32_MAX && PEN20_ANIM_COUNT <= UINT32_MAX);
                                return PEN20_ANIM_COUNT > 0 ? static_cast<int32_t>(rng.range(0, PEN20_ANIM_COUNT-1)) : 0;
                        case config::config_animation_dm_set_t::dmc:
                            assert(DMC_ANIM_COUNT <= INT32_MAX && DMC_ANIM_COUNT <= UINT32_MAX);
                            return DMC_ANIM_COUNT > 0 ? static_cast<int32_t>(rng.range(0, DMC_ANIM_COUNT-1)) : 0;
                        case config::config_animation_dm_set_t::dmall:
                            assert(DMALL_ANIM_COUNT <= INT32_MAX && DMALL_ANIM_COUNT <= UINT32_MAX);
                            return DMALL_ANIM_COUNT > 0 ? static_cast<int32_t>(rng.range(0, DMALL_ANIM_COUNT-1)) : 0;
                        }
                        break;
                    case config::config_animation_sprite_sheet_layout_t::Pkmn:
                        assert(PKMN_ANIM_COUNT <= INT32_MAX && PKMN_ANIM_COUNT <= UINT32_MAX);
                        return PKMN_ANIM_COUNT > 0 ? static_cast<int32_t>(rng.range(0, PKMN_ANIM_COUNT-1)) : 0;
                    case config::config_animation_sprite_sheet_layout_t::MsAgent:
                        assert(MS_AGENTS_ANIM_COUNT <= INT32_MAX && MS_AGENTS_ANIM_COUNT <= UINT32_MAX);
                        return MS_AGENTS_ANIM_COUNT > 0 ? static_cast<int32_t>(rng.range(0, MS_AGENTS_ANIM_COUNT-1)) : 0;
                }
            }
            if constexpr (!features::EnableLazyLoadAssets || features::EnablePreloadAssets) {
                switch (config.animation_sprite_sheet_layout) {
                    case config::config_animation_sprite_sheet_layout_t::None:
                        return config.animation_index;
                    case config::config_animation_sprite_sheet_layout_t::Bongocat:
                        assert(ctx.shm->bongocat_anims.count <= INT32_MAX && ctx.shm->bongocat_anims.count <= UINT32_MAX);
                        return ctx.shm->bongocat_anims.count > 0 ? static_cast<int32_t>(rng.range(0, static_cast<uint32_t>(ctx.shm->bongocat_anims.count-1))) : 0;
                    case config::config_animation_sprite_sheet_layout_t::Dm:
                        switch (ctx.shm->anim_dm_set) {
                            case config::config_animation_dm_set_t::None:
                                return config.animation_index;
                            case config::config_animation_dm_set_t::min_dm:
                                assert(ctx.shm->min_dm_anims.count <= INT32_MAX && ctx.shm->min_dm_anims.count <= UINT32_MAX);
                                return ctx.shm->min_dm_anims.count > 0 ? static_cast<int32_t>(rng.range(0, static_cast<uint32_t>(ctx.shm->min_dm_anims.count-1))) : 0;
                            case config::config_animation_dm_set_t::dm:
                                assert(ctx.shm->dm_anims.count <= INT32_MAX && ctx.shm->dm_anims.count <= UINT32_MAX);
                                return ctx.shm->dm_anims.count > 0 ? static_cast<int32_t>(rng.range(0, static_cast<uint32_t>(ctx.shm->dm_anims.count-1))) : 0;
                            case config::config_animation_dm_set_t::dm20:
                                assert(ctx.shm->dm20_anims.count <= INT32_MAX && ctx.shm->dm20_anims.count <= UINT32_MAX);
                                return ctx.shm->dm20_anims.count > 0 ? static_cast<int32_t>(rng.range(0, static_cast<uint32_t>(ctx.shm->dm20_anims.count-1))) : 0;
                            case config::config_animation_dm_set_t::dmx:
                                assert(ctx.shm->dmx_anims.count <= INT32_MAX && ctx.shm->dmx_anims.count <= UINT32_MAX);
                                return ctx.shm->dmx_anims.count > 0 ? static_cast<int32_t>(rng.range(0, static_cast<uint32_t>(ctx.shm->dmx_anims.count-1))) : 0;
                            case config::config_animation_dm_set_t::pen:
                                assert(ctx.shm->pen_anims.count <= INT32_MAX && ctx.shm->pen_anims.count <= UINT32_MAX);
                                return ctx.shm->pen_anims.count > 0 ? static_cast<int32_t>(rng.range(0, static_cast<uint32_t>(ctx.shm->pen_anims.count-1))) : 0;
                            case config::config_animation_dm_set_t::pen20:
                                assert(ctx.shm->pen20_anims.count <= INT32_MAX && ctx.shm->pen20_anims.count <= UINT32_MAX);
                                return ctx.shm->pen20_anims.count > 0 ? static_cast<int32_t>(rng.range(0, static_cast<uint32_t>(ctx.shm->pen20_anims.count-1))) : 0;
                            case config::config_animation_dm_set_t::dmc:
                                assert(ctx.shm->dmc_anims.count <= INT32_MAX && ctx.shm->dmc_anims.count <= UINT32_MAX);
                                return ctx.shm->dmc_anims.count > 0 ? static_cast<int32_t>(rng.range(0, static_cast<uint32_t>(ctx.shm->dmc_anims.count-1))) : 0;
                            case config::config_animation_dm_set_t::dmall:
                                assert(ctx.shm->dmall_anims.count <= INT32_MAX && ctx.shm->dmall_anims.count <= UINT32_MAX);
                                return ctx.shm->dmall_anims.count > 0 ? static_cast<int32_t>(rng.range(0, static_cast<uint32_t>(ctx.shm->dmall_anims.count-1))) : 0;
                        }
                        break;
                    case config::config_animation_sprite_sheet_layout_t::Pkmn:
                        assert(ctx.shm->pkmn_anims.count <= INT32_MAX && ctx.shm->pkmn_anims.count <= UINT32_MAX);
                        return ctx.shm->pkmn_anims.count > 0 ? static_cast<int32_t>(rng.range(0, static_cast<uint32_t>(ctx.shm->pkmn_anims.count-1))) : 0;
                    case config::config_animation_sprite_sheet_layout_t::MsAgent:
                        assert(ctx.shm->ms_anims.count <= INT32_MAX && ctx.shm->ms_anims.count <= UINT32_MAX);
                        return ctx.shm->ms_anims.count > 0 ? static_cast<int32_t>(rng.range(0, static_cast<uint32_t>(ctx.shm->ms_anims.count-1))) : 0;
                }
            }
        }

        return config.animation_index;
    }

    static void update_config_reload_sprite_sheet(animation_context_t& ctx) {
        assert(ctx._local_copy_config != nullptr);

        platform::LockGuard guard (ctx.anim_lock);
        ctx.shm->anim_type = ctx._local_copy_config->animation_sprite_sheet_layout;
        ctx.shm->anim_dm_set = ctx._local_copy_config->animation_dm_set;
        const auto old_anim_index = ctx.shm->anim_index;

        [[maybe_unused]] const auto t0 = platform::get_current_time_us();

        ctx.shm->anim_index = !ctx._local_copy_config->_keep_old_animation_index ? rand_animation_index(ctx, *ctx._local_copy_config) : old_anim_index;
        if constexpr (features::EnableLazyLoadAssets) {
            auto [result, error] = hot_load_animation(ctx);
            if (error != bongocat_error_t::BONGOCAT_SUCCESS) {
                // rollback
                ctx.shm->anim_index = old_anim_index;
            }
        }
        ctx.shm->animation_player_result.sprite_sheet_col = !ctx._local_copy_config->idle_animation ? ctx._local_copy_config->idle_frame : ctx.shm->animation_player_result.sprite_sheet_col;  // initial frame

        [[maybe_unused]] const auto t1 = platform::get_current_time_us();

        BONGOCAT_LOG_DEBUG("Update sprite sheet; load assets in %.3fms (%.6fsec)", static_cast<double>(t1 - t0) / 1000.0, static_cast<double>(t1 - t0) / 1000000.0);
    }
    void update_config(animation_context_t& ctx, const config::config_t& config, uint64_t new_gen) {
        assert(ctx._local_copy_config != nullptr);
        assert(ctx.shm != nullptr);

        *ctx._local_copy_config = config;

        update_config_reload_sprite_sheet(ctx);

        atomic_store(&ctx.config_seen_generation, new_gen);
        // Signal main that reload is done
        ctx.config_updated.notify_all();
    }
}
