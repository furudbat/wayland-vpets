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
#include "image_loader/dmc/load_images_dmc.h"
#include "image_loader/dmx/load_images_dmx.h"
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
    };

    struct animation_state_t {
        platform::time_ms_t frame_delta_ms_counter{0};
        platform::time_ns_t frame_time_ns{0};
        platform::time_ms_t frame_time_ms{0};
        platform::time_ms_t hold_frame_ms{0};
        platform::timestamp_ms_t last_frame_update_ms{0};
        animation_state_row_t row_state{animation_state_row_t::Idle};
        bool boring_frame_showed{false};
        bool hold_frame_after_release{false};
    };

    struct anim_next_frame_result_t {
        bool changed{false};
        int new_frame{0};
    };

    struct anim_handle_key_press_result_t {
        int any_key_press_counter{0};
        bool changed{false};
        trigger_animation_cause_mask_t triggered_anim_cause{trigger_animation_cause_mask_t::NONE};
    };

#ifdef FEATURE_BONGOCAT_EMBEDDED_ASSETS
    static anim_next_frame_result_t anim_bongocat_idle_next_frame(animation_context_t& ctx, const platform::input::input_context_t& input,
                                                                  animation_state_t& state, const anim_handle_key_press_result_t& trigger_result) {
        using namespace assets;
        // read-only config
        assert(ctx._local_copy_config != nullptr);
        const config::config_t& current_config = *ctx._local_copy_config;

        assert(input.shm != nullptr);
        assert(ctx.shm != nullptr);
        animation_shared_memory_t& anim_shm = *ctx.shm;
        const auto& input_shm = *input.shm;
        auto& animation_player_data = anim_shm.animation_player_data;
        const auto current_frame = animation_player_data.frame_index;
        //const auto current_row = animation_player_data.sprite_sheet_row;
        //const animation_state_row_t current_row_state = state.row_state;
        [[maybe_unused]] const int anim_index = anim_shm.anim_index;
        const platform::timestamp_ms_t last_key_pressed_timestamp = input_shm.last_key_pressed_timestamp;

        animation_state_row_t new_row_state = state.row_state;
        int new_row = animation_player_data.sprite_sheet_row;
        int new_start_frame_index = animation_player_data.start_frame_index;
        int new_end_frame_index = animation_player_data.end_frame_index;
        int new_frame = current_frame;

        const bool any_key_pressed = has_flag(trigger_result.triggered_anim_cause, trigger_animation_cause_mask_t::KeyPress) && trigger_result.any_key_press_counter > 0;

        // @TODO: get variables as struct to make it more reusable
        const bool release_frame_after_press = !any_key_pressed && state.hold_frame_ms > current_config.keypress_duration_ms;
        //const bool process_idle_animation = (current_config.idle_animation && current_config.animation_speed_ms > 0 && state.frame_delta_ms_counter > current_config.animation_speed_ms) || (current_config.idle_animation && current_config.animation_speed_ms <= 0 && state.frame_delta_ms_counter > 1000/current_config.fps);
        const bool trigger_test_animation = current_config.test_animation_interval_sec > 0 && state.frame_delta_ms_counter > current_config.test_animation_interval_sec*1000;
        const bool release_test_frame = current_config.test_animation_duration_ms > 0 && state.frame_delta_ms_counter > current_config.test_animation_duration_ms;
        const bool check_for_idle_sleep = current_config.idle_sleep_timeout_sec > 0 && state.frame_delta_ms_counter > current_config.idle_sleep_timeout_sec*1000/2;

        if (!release_frame_after_press && !trigger_test_animation && !release_test_frame && !check_for_idle_sleep && !current_config.enable_scheduled_sleep) {
            return { .changed = false, .new_frame = new_frame};
        }

        // Idle/Test animation
        if (!any_key_pressed && trigger_test_animation && state.row_state == animation_state_row_t::Idle) {
            new_row = BONGOCAT_SPRITE_SHEET_ROWS-1;
            new_start_frame_index = BONGOCAT_FRAME_LEFT_DOWN;
            new_end_frame_index = BONGOCAT_FRAME_RIGHT_DOWN;
            new_row_state = animation_state_row_t::Test;
            // toggle frame
            if (current_frame == BONGOCAT_FRAME_LEFT_DOWN) {
                new_frame = BONGOCAT_FRAME_RIGHT_DOWN;
            } else if (current_frame == BONGOCAT_FRAME_RIGHT_DOWN) {
                new_frame = BONGOCAT_FRAME_LEFT_DOWN;
            } else {
                static_assert(BONGOCAT_FRAME_RIGHT_DOWN >= BONGOCAT_FRAME_LEFT_DOWN);
                static_assert(BONGOCAT_FRAME_LEFT_DOWN >= 0);
                static_assert(BONGOCAT_FRAME_RIGHT_DOWN >= 0);
                new_frame = static_cast<int>(ctx._rng.range(BONGOCAT_FRAME_LEFT_DOWN, BONGOCAT_FRAME_RIGHT_DOWN));
            }
        }
        // Idle Animation
        if (release_frame_after_press || (trigger_test_animation && state.row_state == animation_state_row_t::Test && release_test_frame)) {
            // back to idle
            new_start_frame_index = BONGOCAT_FRAME_BOTH_UP;
            new_end_frame_index = BONGOCAT_FRAME_BOTH_UP;
            new_frame = BONGOCAT_FRAME_BOTH_UP;
            new_row = BONGOCAT_SPRITE_SHEET_ROWS-1;
            new_row_state = animation_state_row_t::Idle;
        }

        // Sleep Mode
        if (current_config.enable_scheduled_sleep) {
            if (is_sleep_time(current_config)) {
                new_frame = BONGOCAT_FRAME_BOTH_DOWN;
                new_start_frame_index = BONGOCAT_FRAME_BOTH_DOWN;
                new_end_frame_index = BONGOCAT_FRAME_BOTH_DOWN;
                new_row_state = animation_state_row_t::Sleep;
            }
        }
        // Idle Sleep
        if (current_config.idle_sleep_timeout_sec > 0 && last_key_pressed_timestamp > 0) {
            const platform::timestamp_ms_t now = platform::get_current_time_ms();
            const platform::time_ms_t idle_sleep_timeout_ms = current_config.idle_sleep_timeout_sec*1000;
            // boring
            if (!state.boring_frame_showed && now - last_key_pressed_timestamp >= idle_sleep_timeout_ms/2) {
                new_frame = BONGOCAT_FRAME_BOTH_DOWN;
                new_start_frame_index = BONGOCAT_FRAME_BOTH_DOWN;
                new_end_frame_index = BONGOCAT_FRAME_BOTH_DOWN;
                new_row_state = animation_state_row_t::Boring;
            }
            // sleep
            if (now - last_key_pressed_timestamp >= idle_sleep_timeout_ms) {
                new_frame = BONGOCAT_FRAME_BOTH_DOWN;
                new_start_frame_index = BONGOCAT_FRAME_BOTH_DOWN;
                new_end_frame_index = BONGOCAT_FRAME_BOTH_DOWN;
                new_row_state = animation_state_row_t::Sleep;
            }
        }

        const bool changed = animation_player_data.frame_index != new_frame || animation_player_data.sprite_sheet_row != new_row || state.row_state != new_row_state;
        if (changed) {
            ctx.shm->animation_player_data.frame_index = new_frame;
            animation_player_data.sprite_sheet_row = new_row;
            animation_player_data.start_frame_index = new_start_frame_index;
            animation_player_data.end_frame_index = new_end_frame_index;
            state.row_state = new_row_state;
            if (new_row_state == animation_state_row_t::Boring) {
                state.boring_frame_showed = true;
            }
            if (current_config.enable_debug) {
                BONGOCAT_LOG_VERBOSE("Animation frame change: %d", new_frame);
            }
            state.frame_delta_ms_counter = 0;
        }

        return { .changed = changed, .new_frame = new_frame};
    }
#endif

#ifdef FEATURE_ENABLE_DM_EMBEDDED_ASSETS
    static anim_next_frame_result_t anim_dm_idle_next_frame(animation_context_t& ctx, const platform::input::input_context_t& input, const platform::update::update_context_t& upd,
                                                            animation_state_t& state, const anim_handle_key_press_result_t& trigger_result) {
        using namespace assets;

        // read-only config
        assert(ctx._local_copy_config != nullptr);
        const config::config_t& current_config = *ctx._local_copy_config;

        assert(ctx.shm != nullptr);
        animation_shared_memory_t& anim_shm = *ctx.shm;
        const auto& input_shm = *input.shm;
        const auto& update_shm = *upd.shm;
        auto& animation_player_data = anim_shm.animation_player_data;
        const auto current_frame = animation_player_data.frame_index;
        //const int current_row = animation_player_data.sprite_sheet_row;
        //const animation_state_row_t current_row_state = state.row_state;
        [[maybe_unused]] const auto anim_index = anim_shm.anim_index;
        const platform::timestamp_ms_t last_key_pressed_timestamp = input_shm.last_key_pressed_timestamp;

        animation_state_row_t new_row_state = state.row_state;
        int new_row = animation_player_data.sprite_sheet_row;
        int new_start_frame_index = animation_player_data.start_frame_index;
        int new_end_frame_index = animation_player_data.end_frame_index;
        int new_frame = current_frame;

        const bool any_key_pressed = has_flag(trigger_result.triggered_anim_cause, trigger_animation_cause_mask_t::KeyPress) && trigger_result.any_key_press_counter > 0;

        const bool release_frame_after_press = (!any_key_pressed && !has_flag(trigger_result.triggered_anim_cause, trigger_animation_cause_mask_t::CpuUpdate)) && state.hold_frame_ms > current_config.keypress_duration_ms;
        const bool process_idle_animation = (current_config.idle_animation && current_config.animation_speed_ms > 0 && state.frame_delta_ms_counter > current_config.animation_speed_ms) || (current_config.idle_animation && current_config.animation_speed_ms <= 0 && state.frame_delta_ms_counter > 1000/current_config.fps);
        const bool trigger_test_animation = current_config.test_animation_interval_sec > 0 && state.frame_delta_ms_counter > current_config.test_animation_interval_sec*1000;
        const bool release_test_frame = current_config.test_animation_duration_ms > 0 && state.frame_delta_ms_counter > current_config.test_animation_duration_ms;
        const bool check_for_idle_sleep = current_config.idle_sleep_timeout_sec > 0 && state.frame_delta_ms_counter > current_config.idle_sleep_timeout_sec*1000/2;

        if (!release_frame_after_press && !trigger_test_animation && !release_test_frame && !process_idle_animation && !check_for_idle_sleep && !current_config.enable_scheduled_sleep) {
            return { .changed = false, .new_frame = new_frame};
        }

        /// @TODO: extract set animation state

        const auto& current_frames = reinterpret_cast<dm_animation_t&>(get_current_animation(ctx));
        new_row = DM_SPRITE_SHEET_ROWS-1;
        // Test Animation
        if (!any_key_pressed && trigger_test_animation && state.row_state == animation_state_row_t::Idle) {
            new_start_frame_index = DM_FRAME_IDLE1;
            new_end_frame_index = DM_FRAME_IDLE2;
            new_row_state = animation_state_row_t::Test;
            // toggle frame
            if (current_frame == DM_FRAME_IDLE2) {
                new_frame = DM_FRAME_IDLE1;
            } else if (current_frame == DM_FRAME_IDLE1) {
                new_frame = DM_FRAME_IDLE2;
            } else {
                static_assert(DM_FRAME_IDLE2 >= DM_FRAME_IDLE1);
                static_assert(DM_FRAME_IDLE1 >= 0);
                static_assert(DM_FRAME_IDLE2 >= 0);
                new_frame = static_cast<int>(ctx._rng.range(DM_FRAME_IDLE1, DM_FRAME_IDLE2)); // Frame 0 or 1 (active frames)
            }
        }
        // Idle Animation
        if (release_frame_after_press || process_idle_animation || (trigger_test_animation && release_test_frame && state.row_state == animation_state_row_t::Test)) {
            new_start_frame_index = DM_FRAME_IDLE1;
            new_end_frame_index = DM_FRAME_IDLE2;
            new_row_state = animation_state_row_t::Idle;
            // toggle frame
            if (current_frame == DM_FRAME_IDLE2) {
                new_frame = DM_FRAME_IDLE1;
            } else if (current_frame == DM_FRAME_IDLE1) {
                new_frame = DM_FRAME_IDLE2;
            } else {
                // recover from working animation
                if (!update_shm.cpu_active && (current_frame == DM_FRAME_ATTACK || current_frame == DM_FRAME_ANGRY)) {
                    new_frame = DM_FRAME_IDLE1;
                } else {
                    static_assert(DM_FRAME_IDLE2 >= DM_FRAME_IDLE1);
                    static_assert(DM_FRAME_IDLE1 >= 0);
                    static_assert(DM_FRAME_IDLE2 >= 0);
                    new_frame = static_cast<int>(ctx._rng.range(DM_FRAME_IDLE1, DM_FRAME_IDLE2)); // Frame 0 or 1 (active frames)
                }
            }
        }
        // Sleep animation
        if (current_config.enable_scheduled_sleep && is_sleep_time(current_config)) {
            if (current_frames.sleep_2.valid) {
                new_start_frame_index = DM_FRAME_SLEEP2;
                new_end_frame_index = DM_FRAME_SLEEP2;
                new_frame = DM_FRAME_SLEEP1;
                new_row_state = animation_state_row_t::Sleep;
            } else if (current_frames.sleep1.valid) {
                new_start_frame_index = DM_FRAME_SLEEP1;
                new_end_frame_index = DM_FRAME_SLEEP1;
                new_frame = DM_FRAME_SLEEP1;
                new_row_state = animation_state_row_t::Sleep;
            } else if (current_frames.down1.valid) {
                BONGOCAT_LOG_VERBOSE("No Sleeping Frame for %d", anim_index);
                // fallback frame
                new_start_frame_index = DM_FRAME_DOWN1;
                new_end_frame_index = DM_FRAME_DOWN1;
                new_frame = DM_FRAME_DOWN1;
                new_row_state = animation_state_row_t::Sleep;
            }
        }
        // Idle Sleep
        if (current_config.idle_sleep_timeout_sec > 0 && last_key_pressed_timestamp > 0) {
            const platform::timestamp_ms_t now = platform::get_current_time_ms();
            const platform::time_ms_t idle_sleep_timeout_ms = current_config.idle_sleep_timeout_sec*1000;
            // boring
            if (!state.boring_frame_showed && now - last_key_pressed_timestamp >= idle_sleep_timeout_ms/2) {
                if (current_frames.sad.valid) {
                    new_start_frame_index = DM_FRAME_SAD;
                    new_end_frame_index = DM_FRAME_SAD;
                    new_frame = DM_FRAME_SAD;
                    new_row_state = animation_state_row_t::Boring;
                } else if (current_frames.down1.valid) {
                    BONGOCAT_LOG_VERBOSE("No Boring Frame for %d", anim_index);
                    // fallback frame
                    new_start_frame_index = DM_FRAME_DOWN1;
                    new_end_frame_index = DM_FRAME_DOWN1;
                    new_frame = DM_FRAME_DOWN1;
                    new_row_state = animation_state_row_t::Boring;
                }
            }
            // sleep
            if (now - last_key_pressed_timestamp >= idle_sleep_timeout_ms) {
                // start sleeping
                if (current_frames.sleep1.valid) {
                    new_start_frame_index = DM_FRAME_SLEEP1;
                    new_end_frame_index = DM_FRAME_SLEEP1;
                    new_frame = DM_FRAME_SLEEP1;
                    new_row_state = animation_state_row_t::Sleep;
                } else if (current_frames.down1.valid) {
                    BONGOCAT_LOG_VERBOSE("No Sleeping Frame for %d", anim_index);
                    // fallback frame
                    new_start_frame_index = DM_FRAME_DOWN1;
                    new_end_frame_index = DM_FRAME_DOWN1;
                    new_frame = DM_FRAME_DOWN1;
                    new_row_state = animation_state_row_t::Sleep;
                }
            }
        }

        const bool changed = animation_player_data.frame_index != new_frame || animation_player_data.sprite_sheet_row != new_row || state.row_state != new_row_state;
        if (changed) {
            animation_player_data.frame_index = new_frame;
            animation_player_data.sprite_sheet_row = new_row;
            animation_player_data.start_frame_index = new_start_frame_index;
            animation_player_data.end_frame_index = new_end_frame_index;
            state.row_state = new_row_state;
            if (new_row_state == animation_state_row_t::Boring) {
                state.boring_frame_showed = true;
            } else if (state.boring_frame_showed && new_row_state == animation_state_row_t::Writing) {
                // reset boring frame state
                state.boring_frame_showed = false;
            }
            if (current_config.enable_debug) {
                BONGOCAT_LOG_VERBOSE("Animation frame change: %d", new_frame);
            }
            state.frame_delta_ms_counter = 0;
        }

        return { .changed = changed, .new_frame = new_frame};
    }
#endif

#ifdef FEATURE_MS_AGENT_EMBEDDED_ASSETS
    static anim_next_frame_result_t anim_ms_pet_idle_next_frame(animation_context_t& ctx, const platform::input::input_context_t& input,
                                                                animation_state_t& state, const anim_handle_key_press_result_t& trigger_result) {
        using namespace assets;

        // read-only config
        assert(ctx._local_copy_config != nullptr);
        const config::config_t& current_config = *ctx._local_copy_config;

        assert(input.shm != nullptr);
        assert(ctx.shm != nullptr);
        animation_shared_memory_t& anim_shm = *ctx.shm;
        const auto& input_shm = *input.shm;
        auto& animation_player_data = anim_shm.animation_player_data;
        const auto current_frame = animation_player_data.frame_index;
        //const int current_row = animation_player_data.sprite_sheet_row;
        //const animation_state_row_t current_row_state = state.row_state;
        //const int anim_index = anim_shm.anim_index;
        const platform::timestamp_ms_t last_key_pressed_timestamp = input_shm.last_key_pressed_timestamp;

        animation_state_row_t new_row_state = state.row_state;
        auto new_row = animation_player_data.sprite_sheet_row;
        auto new_start_frame_index = animation_player_data.start_frame_index;
        auto new_end_frame_index = animation_player_data.end_frame_index;
        auto new_frame = current_frame;

        const bool any_key_pressed = has_flag(trigger_result.triggered_anim_cause, trigger_animation_cause_mask_t::KeyPress) && trigger_result.any_key_press_counter > 0;

        const bool go_next_frame = (current_config.animation_speed_ms > 0 && state.frame_delta_ms_counter > current_config.animation_speed_ms) || (current_config.animation_speed_ms <= 0 && state.frame_delta_ms_counter > 1000/current_config.fps);
        const bool release_frame_after_press = (!any_key_pressed && !has_flag(trigger_result.triggered_anim_cause, trigger_animation_cause_mask_t::CpuUpdate)) && state.hold_frame_ms > current_config.keypress_duration_ms;
        const bool process_idle_animation = (current_config.idle_animation && current_config.animation_speed_ms > 0 && state.frame_delta_ms_counter > current_config.animation_speed_ms) || (current_config.idle_animation && current_config.animation_speed_ms <= 0 && state.frame_delta_ms_counter > 1000/current_config.fps);
        //const bool trigger_test_animation = current_config.test_animation_interval_sec > 0 && state.frame_delta_ms_counter > current_config.test_animation_interval_sec*1000;
        //const bool release_test_frame = current_config.test_animation_duration_ms > 0 && state.frame_delta_ms_counter > current_config.test_animation_duration_ms;
        const bool check_for_idle_sleep = current_config.idle_sleep_timeout_sec > 0 && state.frame_delta_ms_counter > current_config.idle_sleep_timeout_sec*1000/2;

        // only show next frame by animation speed or when any key was pressed (writing animation)
        if (state.frame_delta_ms_counter <= current_config.animation_speed_ms && !any_key_pressed && !check_for_idle_sleep && !current_config.enable_scheduled_sleep) {
            return { .changed = false, .new_frame = new_frame};
        }

        /// @TODO: extract state change and player_data update

        assert(anim_shm.anim_index >= 0);
        const ms_agent_animation_indices_t animation_indices = get_ms_agent_animation_indices(static_cast<size_t>(anim_shm.anim_index));

        switch (state.row_state) {
            case animation_state_row_t::Test:
            case animation_state_row_t::Happy:
                // not supported, same as idle
            case animation_state_row_t::Idle: {
                new_start_frame_index = animation_indices.start_index_frame_idle;
                new_end_frame_index = animation_indices.end_index_frame_idle;
                new_row = MS_AGENT_SPRITE_SHEET_ROW_IDLE;
                new_row_state = animation_state_row_t::Idle;
                if (current_config.idle_animation && process_idle_animation) {
                    // loop idle animation
                    new_frame = current_frame + 1;
                    if (new_frame > animation_player_data.end_frame_index) new_frame = animation_player_data.start_frame_index;
                    //if (new_frame < animation_player_data.start_frame_index) new_frame = animation_player_data.end_frame_index;
                } else if (!current_config.idle_animation) {
                    new_frame = current_config.idle_animation;
                }
                // is not sleeping, yet
                if (state.row_state != animation_state_row_t::Sleep) {
                    // Sleep Mode
                    if (current_config.enable_scheduled_sleep) {
                        if (is_sleep_time(current_config)) {
                            // start sleeping
                            new_frame = 0;
                            new_start_frame_index = animation_indices.start_index_frame_sleep;
                            new_end_frame_index = animation_indices.end_index_frame_sleep;
                            new_row = MS_AGENT_SPRITE_SHEET_ROW_SLEEP;
                            new_row_state = animation_state_row_t::Sleep;
                        }
                    }
                    // Idle Sleep
                    if (current_config.idle_sleep_timeout_sec > 0 && last_key_pressed_timestamp > 0) {
                        const platform::timestamp_ms_t now = platform::get_current_time_ms();
                        const platform::time_ms_t idle_sleep_timeout_ms = current_config.idle_sleep_timeout_sec*1000;
                        // boring
                        if (!state.boring_frame_showed && now - last_key_pressed_timestamp >= idle_sleep_timeout_ms/2) {
                            // start boring animation
                            new_frame = 0;
                            new_start_frame_index = animation_indices.start_index_frame_boring;
                            new_end_frame_index = animation_indices.end_index_frame_boring;
                            new_row = MS_AGENT_SPRITE_SHEET_ROW_BORING;
                            new_row_state = animation_state_row_t::Boring;
                        }
                        // sleeping
                        if (now - last_key_pressed_timestamp >= idle_sleep_timeout_ms) {
                            // start sleeping
                            new_frame = 0;
                            new_start_frame_index = animation_indices.start_index_frame_sleep;
                            new_end_frame_index = animation_indices.end_index_frame_sleep;
                            new_row = MS_AGENT_SPRITE_SHEET_ROW_SLEEP;
                            new_row_state = animation_state_row_t::Sleep;
                        }
                    }
                }
            }break;
            case animation_state_row_t::Writing: {
                // keep writing
                new_start_frame_index = animation_indices.start_index_frame_writing;
                new_end_frame_index = animation_indices.end_index_frame_writing;
                new_row = MS_AGENT_SPRITE_SHEET_ROW_WRITING;
                new_row_state = animation_state_row_t::Writing;
                if (any_key_pressed || go_next_frame) {
                    // loop writing animation
                    new_frame = current_frame + 1;
                    if (new_frame > animation_player_data.end_frame_index) new_frame = animation_player_data.start_frame_index;
                    //if (new_frame < animation_player_data.start_frame_index) new_frame = animation_player_data.end_frame_index;
                }
                // still in writing process ?
                if (state.hold_frame_after_release && any_key_pressed) {
                    state.hold_frame_after_release = false;
                    state.hold_frame_ms = 0;
                }
                // cancel writing
                if (release_frame_after_press) {
                    // start, end writing animation
                    new_frame = 0;
                    new_start_frame_index = animation_indices.start_index_frame_end_writing;
                    new_end_frame_index = animation_indices.end_index_frame_end_writing;
                    new_row = MS_AGENT_SPRITE_SHEET_ROW_END_WRITING;
                    new_row_state = animation_state_row_t::EndWriting;
                }
            }break;
            case animation_state_row_t::StartWriting:
                // end current animation
                new_start_frame_index = animation_indices.start_index_frame_start_writing;
                new_end_frame_index = animation_indices.end_index_frame_start_writing;
                new_row = MS_AGENT_SPRITE_SHEET_ROW_START_WRITING;
                new_row_state = animation_state_row_t::StartWriting;
                if (go_next_frame) {
                    new_frame = current_frame + 1;
                }
                if (new_frame > new_end_frame_index) {
                    // start writing animation
                    new_start_frame_index = animation_indices.start_index_frame_writing;
                    new_end_frame_index = animation_indices.end_index_frame_writing;
                    new_frame = new_start_frame_index;
                    new_row = MS_AGENT_SPRITE_SHEET_ROW_WRITING;
                    new_row_state = animation_state_row_t::Writing;
                    // reset release counter after writing is started (for real)
                    state.hold_frame_after_release = true;
                    state.hold_frame_ms = 0;
                }
                break;
            case animation_state_row_t::EndWriting:
                // end current animation
                new_start_frame_index = animation_indices.start_index_frame_end_writing;
                new_end_frame_index = animation_indices.end_index_frame_end_writing;
                new_row = MS_AGENT_SPRITE_SHEET_ROW_END_WRITING;
                new_row_state = animation_state_row_t::EndWriting;
                if (go_next_frame) {
                    new_frame = current_frame + 1;
                }
                if (new_frame > new_end_frame_index) {
                    new_start_frame_index = animation_indices.start_index_frame_idle;
                    new_end_frame_index = animation_indices.end_index_frame_idle;
                    // back to idle
                    if (current_config.idle_animation) {
                        new_frame = new_start_frame_index;
                    } else {
                        new_frame = current_config.idle_frame;
                    }
                    new_row = MS_AGENT_SPRITE_SHEET_ROW_IDLE;
                    new_row_state = animation_state_row_t::Idle;
                }
                break;
            case animation_state_row_t::Sleep:
                new_start_frame_index = animation_indices.start_index_frame_sleep;
                new_end_frame_index = animation_indices.end_index_frame_sleep;
                new_row = MS_AGENT_SPRITE_SHEET_ROW_SLEEP;
                new_row_state = animation_state_row_t::Sleep;
                // continue (start) sleeping, stop at last frame
                if (go_next_frame) {
                    if (new_frame < new_end_frame_index) {
                        new_frame = current_frame + 1;
                    } else {
                        new_frame = new_end_frame_index;
                    }
                }
                break;
            case animation_state_row_t::WakeUp:
                new_start_frame_index = animation_indices.start_index_frame_wake_up;
                new_end_frame_index = animation_indices.end_index_frame_wake_up;
                new_row = MS_AGENT_SPRITE_SHEET_ROW_WAKE_UP;
                new_row_state = animation_state_row_t::WakeUp;
                if (go_next_frame) {
                    new_frame = current_frame + 1;
                }
                if (new_frame > new_end_frame_index) {
                    // back to idle
                    new_start_frame_index = animation_indices.start_index_frame_idle;
                    new_end_frame_index = animation_indices.end_index_frame_idle;
                    if (current_config.idle_animation) {
                        new_frame = new_start_frame_index;
                    } else {
                        new_frame = current_config.idle_frame;
                    }
                    new_row = MS_AGENT_SPRITE_SHEET_ROW_IDLE;
                    new_row_state = animation_state_row_t::Idle;
                }
                break;
            case animation_state_row_t::Boring:
                // end current animation
                new_start_frame_index = animation_indices.start_index_frame_boring;
                new_end_frame_index = animation_indices.end_index_frame_boring;
                new_row = MS_AGENT_SPRITE_SHEET_ROW_BORING;
                new_row_state = animation_state_row_t::Boring;
                if (go_next_frame) {
                    new_frame = current_frame + 1;
                }
                if (new_frame > new_end_frame_index) {
                    // back to idle
                    new_start_frame_index = animation_indices.start_index_frame_idle;
                    new_end_frame_index = animation_indices.end_index_frame_idle;
                    if (current_config.idle_animation) {
                        new_frame = new_start_frame_index;
                    } else {
                        new_frame = current_config.idle_frame;
                    }
                    new_row = MS_AGENT_SPRITE_SHEET_ROW_IDLE;
                    new_row_state = animation_state_row_t::Idle;
                }
                break;
        }


        const bool changed = animation_player_data.frame_index != new_frame || animation_player_data.sprite_sheet_row != new_row || state.row_state != new_row_state;
        if (changed) {
            animation_player_data.frame_index = new_frame;
            animation_player_data.sprite_sheet_row = new_row;
            animation_player_data.start_frame_index = new_start_frame_index;
            animation_player_data.end_frame_index = new_end_frame_index;
            state.row_state = new_row_state;
            if (new_row_state == animation_state_row_t::Boring) {
                state.boring_frame_showed = true;
            } else if (state.boring_frame_showed && (new_row_state == animation_state_row_t::StartWriting || new_row_state == animation_state_row_t::Writing || new_row_state == animation_state_row_t::EndWriting)) {
                // reset boring frame state
                state.boring_frame_showed = false;
            }
            if (current_config.enable_debug) {
                BONGOCAT_LOG_VERBOSE("Idle Animation frame change: %d", new_frame);
            }
            state.frame_delta_ms_counter = 0;
        }

        return { .changed = changed, .new_frame = new_frame };
    }
#endif


#ifdef FEATURE_PKMN_EMBEDDED_ASSETS
    static anim_next_frame_result_t anim_pkmn_idle_next_frame(animation_context_t& ctx, [[maybe_unused]] const platform::input::input_context_t& input,
                                                              animation_state_t& state, const anim_handle_key_press_result_t& trigger_result) {
        using namespace assets;
        // read-only config
        assert(ctx._local_copy_config != nullptr);
        const config::config_t& current_config = *ctx._local_copy_config;

        assert(input.shm != nullptr);
        assert(ctx.shm != nullptr);
        animation_shared_memory_t& anim_shm = *ctx.shm;
        //const auto& input_shm = *input.shm;
        auto& animation_player_data = anim_shm.animation_player_data;
        const auto current_frame = animation_player_data.frame_index;
        //const auto current_row = animation_player_data.sprite_sheet_row;
        //const animation_state_row_t current_row_state = state.row_state;
        [[maybe_unused]] const int anim_index = anim_shm.anim_index;
        //const platform::timestamp_ms_t last_key_pressed_timestamp = input_shm.last_key_pressed_timestamp;

        volatile animation_state_row_t new_row_state = state.row_state;
        int new_row = animation_player_data.sprite_sheet_row;
        int new_start_frame_index = animation_player_data.start_frame_index;
        int new_end_frame_index = animation_player_data.end_frame_index;
        int new_frame = current_frame;

        const bool any_key_pressed = has_flag(trigger_result.triggered_anim_cause, trigger_animation_cause_mask_t::KeyPress) && trigger_result.any_key_press_counter > 0;

        // @TODO: get variables as struct to make it more reusable
        const bool release_frame_after_press = !any_key_pressed && state.hold_frame_ms > current_config.keypress_duration_ms;
        const bool process_idle_animation = (current_config.idle_animation && current_config.animation_speed_ms > 0 && state.frame_delta_ms_counter > current_config.animation_speed_ms) || (current_config.idle_animation && current_config.animation_speed_ms <= 0 && state.frame_delta_ms_counter > 1000/current_config.fps);
        const bool trigger_test_animation = current_config.test_animation_interval_sec > 0 && state.frame_delta_ms_counter > current_config.test_animation_interval_sec*1000;
        const bool release_test_frame = current_config.test_animation_duration_ms > 0 && state.frame_delta_ms_counter > current_config.test_animation_duration_ms;

        if (!release_frame_after_press && !trigger_test_animation && !release_test_frame && !process_idle_animation && !current_config.enable_scheduled_sleep) {
            return { .changed = false, .new_frame = new_frame};
        }

        //const auto& current_frames = reinterpret_cast<pkmn_animation_t&>(get_current_animation(ctx));
        new_row = PKMN_SPRITE_SHEET_ROWS-1;
        // Test animation
        if (!any_key_pressed && trigger_test_animation && state.row_state == animation_state_row_t::Idle) {
            new_row = PKMN_SPRITE_SHEET_ROWS-1;
            new_start_frame_index = PKMN_FRAME_IDLE1;
            new_end_frame_index = PKMN_FRAME_IDLE2;
            new_row_state = animation_state_row_t::Test;
            // toggle frame
            if (current_frame == PKMN_FRAME_IDLE2) {
                new_frame = PKMN_FRAME_IDLE1;
            } else if (current_frame == PKMN_FRAME_IDLE1) {
                new_frame = PKMN_FRAME_IDLE2;
            } else {
                static_assert(PKMN_FRAME_IDLE2 >= PKMN_FRAME_IDLE1);
                static_assert(PKMN_FRAME_IDLE1 >= 0);
                static_assert(PKMN_FRAME_IDLE2 >= 0);
                new_frame = static_cast<int>(ctx._rng.range(PKMN_FRAME_IDLE1, PKMN_FRAME_IDLE2)); // Frame 0 or 1 (active frames)
            }
        }
        // Idle Animation
        if (release_frame_after_press || process_idle_animation || (trigger_test_animation && release_test_frame && state.row_state == animation_state_row_t::Test)) {
            new_start_frame_index = PKMN_FRAME_IDLE1;
            new_end_frame_index = PKMN_FRAME_IDLE2;
            new_row_state = animation_state_row_t::Idle;
            // toggle frame
            if (current_frame == PKMN_FRAME_IDLE2) {
                new_frame = PKMN_FRAME_IDLE1;
            } else if (current_frame == PKMN_FRAME_IDLE1) {
                new_frame = PKMN_FRAME_IDLE2;
            } else {
                static_assert(PKMN_FRAME_IDLE2 >= PKMN_FRAME_IDLE1);
                static_assert(PKMN_FRAME_IDLE1 >= 0);
                static_assert(DM_FRAME_IDLE2 >= 0);
                new_frame = static_cast<int>(ctx._rng.range(PKMN_FRAME_IDLE1, PKMN_FRAME_IDLE2)); // Frame 0 or 1 (active frames)
            }
        }

        const bool changed = animation_player_data.frame_index != new_frame || animation_player_data.sprite_sheet_row != new_row || state.row_state != new_row_state;
        if (changed) {
            ctx.shm->animation_player_data.frame_index = new_frame;
            animation_player_data.sprite_sheet_row = new_row;
            animation_player_data.start_frame_index = new_start_frame_index;
            animation_player_data.end_frame_index = new_end_frame_index;
            state.row_state = new_row_state;
            if (current_config.enable_debug) {
                BONGOCAT_LOG_VERBOSE("Animation frame change: %d", new_frame);
            }
            state.frame_delta_ms_counter = 0;
        }

        return { .changed = changed, .new_frame = new_frame};
    }
#endif


#ifdef FEATURE_BONGOCAT_EMBEDDED_ASSETS
    static anim_next_frame_result_t anim_bongocat_key_pressed_next_frame(animation_context_t& ctx, animation_state_t& state) {
        using namespace assets;

        // read-only config
        assert(ctx._local_copy_config != nullptr);
        const config::config_t& current_config = *ctx._local_copy_config;

        assert(ctx.shm != nullptr);
        animation_shared_memory_t& anim_shm = *ctx.shm;
        //const auto& input_shm = *input.shm;
        auto& animation_player_data = anim_shm.animation_player_data;
        const auto current_frame = animation_player_data.frame_index;
        //const auto current_row = animation_player_data.sprite_sheet_row;
        //const animation_state_row_t current_row_state = state.row_state;
        //const auto anim_index = anim_shm.anim_index;
        //const platform::timestamp_ms_t last_key_pressed_timestamp = input_shm.last_key_pressed_timestamp;

        animation_state_row_t new_row_state = state.row_state;
        auto new_row = animation_player_data.sprite_sheet_row;
        auto new_start_frame_index = animation_player_data.start_frame_index;
        auto new_end_frame_index = animation_player_data.end_frame_index;
        auto new_frame = current_frame;

        /// @TODO: use state machine for animation (states)

        // toggle frame
        if (current_frame == BONGOCAT_FRAME_LEFT_DOWN) {
            new_frame = BONGOCAT_FRAME_RIGHT_DOWN;
        } else if (current_frame == BONGOCAT_FRAME_RIGHT_DOWN) {
            new_frame = BONGOCAT_FRAME_LEFT_DOWN;
        } else {
            static_assert(BONGOCAT_FRAME_RIGHT_DOWN >= BONGOCAT_FRAME_LEFT_DOWN);
            static_assert(BONGOCAT_FRAME_LEFT_DOWN >= 0);
            static_assert(BONGOCAT_FRAME_RIGHT_DOWN >= 0);
            new_frame = static_cast<int>(ctx._rng.range(BONGOCAT_FRAME_LEFT_DOWN, BONGOCAT_FRAME_RIGHT_DOWN));
        }
        // in Writing mode/start writing
        new_row = BONGOCAT_SPRITE_SHEET_ROWS-1;
        new_start_frame_index = BONGOCAT_FRAME_LEFT_DOWN;
        new_end_frame_index = BONGOCAT_FRAME_RIGHT_DOWN;
        new_row_state = animation_state_row_t::Writing;

        const bool changed = anim_shm.animation_player_data.frame_index != new_frame || anim_shm.animation_player_data.sprite_sheet_row != new_row || state.row_state != new_row_state;
        if (changed) {
            anim_shm.animation_player_data.frame_index = new_frame;
            animation_player_data.sprite_sheet_row = new_row;
            animation_player_data.start_frame_index = new_start_frame_index;
            animation_player_data.end_frame_index = new_end_frame_index;
            state.row_state = new_row_state;
            if (current_config.enable_debug) {
                BONGOCAT_LOG_VERBOSE("Animation frame change: %d", new_frame);
            }
            state.frame_delta_ms_counter = 0;
        }

        return { .changed = changed, .new_frame = new_frame};
    }
#endif


#ifdef FEATURE_ENABLE_DM_EMBEDDED_ASSETS
    static anim_next_frame_result_t anim_dm_key_pressed_next_frame(animation_context_t& ctx, const platform::input::input_context_t& input,
                                                                        animation_state_t& state) {
        using namespace assets;

        // read-only config
        assert(ctx._local_copy_config != nullptr);
        const config::config_t& current_config = *ctx._local_copy_config;

        assert(input.shm != nullptr);
        assert(ctx.shm != nullptr);
        animation_shared_memory_t& anim_shm = *ctx.shm;
        const auto& input_shm = *input.shm;
        auto& animation_player_data = anim_shm.animation_player_data;
        const auto current_frame = animation_player_data.frame_index;
        //const auto current_row = animation_player_data.sprite_sheet_row;
        //const animation_state_row_t current_row_state = state.row_state;
        //const auto anim_index = anim_shm.anim_index;
        //const platform::timestamp_ms_t last_key_pressed_timestamp = input_shm.last_key_pressed_timestamp;
        const auto& current_frames = reinterpret_cast<dm_animation_t&>(get_current_animation(ctx));

        animation_state_row_t new_row_state = state.row_state;
        int new_row = animation_player_data.sprite_sheet_row;
        int new_start_frame_index = animation_player_data.start_frame_index;
        int new_end_frame_index = animation_player_data.end_frame_index;
        int new_frame = current_frame;

        /// @TODO: use state machine for animation (states)

        // in Writing mode/start writing
        new_row = DM_SPRITE_SHEET_ROWS-1;
        new_start_frame_index = DM_FRAME_IDLE1;
        new_end_frame_index = DM_FRAME_IDLE2;
        new_row_state = animation_state_row_t::Writing;
        // toggle frame
        if (current_frame == DM_FRAME_IDLE1) {
            new_frame = DM_FRAME_IDLE2;

            if (input_shm.kpm > 0) {
                if (current_config.happy_kpm > 0 && input_shm.kpm >= current_config.happy_kpm) {
                    if (current_frames.happy.valid) {
                        if (DM_HAPPY_CHANCE_PERCENT >= 100 || ctx._rng.range(0, 99) < DM_HAPPY_CHANCE_PERCENT) {
                            BONGOCAT_LOG_VERBOSE("Show Happy Frame at %d KPM", input_shm.kpm);
                            new_start_frame_index = DM_FRAME_HAPPY;
                            new_end_frame_index = DM_FRAME_HAPPY;
                            new_frame = DM_FRAME_HAPPY;
                            new_row_state = animation_state_row_t::Happy;
                        }
                    }
                }
            }
        } else if (current_frame == DM_FRAME_IDLE2) {
            new_frame = DM_FRAME_IDLE1;
        } else {
            static_assert(DM_FRAME_IDLE2 >= DM_FRAME_IDLE1);
            static_assert(DM_FRAME_IDLE1 >= 0);
            static_assert(DM_FRAME_IDLE2 >= 0);
            new_frame = static_cast<int>(ctx._rng.range(DM_FRAME_IDLE1, DM_FRAME_IDLE2)); // Frame 0 or 1 (active frames)
        }

        const bool changed = anim_shm.animation_player_data.frame_index != new_frame || anim_shm.animation_player_data.sprite_sheet_row != new_row || state.row_state != new_row_state;
        if (changed) {
            anim_shm.animation_player_data.frame_index = new_frame;
            animation_player_data.sprite_sheet_row = new_row;
            animation_player_data.start_frame_index = new_start_frame_index;
            animation_player_data.end_frame_index = new_end_frame_index;
            state.row_state = new_row_state;
            if (current_config.enable_debug) {
                BONGOCAT_LOG_VERBOSE("Animation frame change: %d", new_frame);
            }
            state.frame_delta_ms_counter = 0;
        }

        return { .changed = changed, .new_frame = new_frame};
    }

    static anim_next_frame_result_t anim_dm_working_next_frame(animation_context_t& ctx, const platform::update::update_context_t& upd,
                                                               animation_state_t& state) {
        using namespace assets;

        // read-only config
        assert(ctx._local_copy_config != nullptr);
        const config::config_t& current_config = *ctx._local_copy_config;

        assert(upd.shm != nullptr);
        assert(ctx.shm != nullptr);
        animation_shared_memory_t& anim_shm = *ctx.shm;
        const auto& update_shm = *upd.shm;
        auto& animation_player_data = anim_shm.animation_player_data;
        const auto current_frame = animation_player_data.frame_index;
        //const auto current_row = animation_player_data.sprite_sheet_row;
        //const animation_state_row_t current_row_state = state.row_state;
        //const auto anim_index = anim_shm.anim_index;
        //const platform::timestamp_ms_t last_key_pressed_timestamp = input_shm.last_key_pressed_timestamp;
        const auto& current_frames = reinterpret_cast<dm_animation_t&>(get_current_animation(ctx));

        animation_state_row_t new_row_state = state.row_state;
        int new_row = animation_player_data.sprite_sheet_row;
        int new_start_frame_index = animation_player_data.start_frame_index;
        int new_end_frame_index = animation_player_data.end_frame_index;
        int new_frame = current_frame;

        /// @TODO: use state machine for animation (states)

        // in Working mode/start working
        new_row = DM_SPRITE_SHEET_ROWS-1;
        new_start_frame_index = DM_FRAME_IDLE1;
        new_end_frame_index = DM_FRAME_IDLE2;
        /// @TODO: set new Working mode
        new_row_state = animation_state_row_t::Writing;
        // toggle frame, show attack animation
        const bool above_threshold = current_config.cpu_threshold >= platform::ENABLED_MIN_CPU_PERCENT && (update_shm.avg_cpu_usage >= current_config.cpu_threshold || update_shm.max_cpu_usage >= current_config.cpu_threshold);
        const bool lower_threshold = current_config.cpu_threshold >= platform::ENABLED_MIN_CPU_PERCENT && (update_shm.avg_cpu_usage < current_config.cpu_threshold || update_shm.max_cpu_usage < current_config.cpu_threshold);
        if (above_threshold) {
            if (!update_shm.cpu_active && (current_frame == DM_FRAME_ATTACK || current_frame == DM_FRAME_ANGRY)) {
                // toggle frame
                if (current_frame == DM_FRAME_IDLE1) {
                    new_frame = DM_FRAME_IDLE2;
                } else if (current_frame == DM_FRAME_IDLE2) {
                    new_frame = DM_FRAME_IDLE1;
                } else {
                    static_assert(DM_FRAME_IDLE2 >= DM_FRAME_IDLE1);
                    static_assert(DM_FRAME_IDLE1 >= 0);
                    static_assert(DM_FRAME_IDLE2 >= 0);
                    new_frame = static_cast<int>(ctx._rng.range(DM_FRAME_IDLE1, DM_FRAME_IDLE2)); // Frame 0 or 1 (active frames)
                }
            } else if (current_frame == DM_FRAME_IDLE1 || current_frame == DM_FRAME_IDLE2) {
                // show attack/working frame
                if (current_frames.attack.valid) {
                    new_start_frame_index = DM_FRAME_ATTACK;
                    new_end_frame_index = DM_FRAME_ATTACK;
                    new_frame = DM_FRAME_ATTACK;
                } else if (current_frames.angry.valid) {
                    new_start_frame_index = DM_FRAME_ANGRY;
                    new_end_frame_index = DM_FRAME_ANGRY;
                    new_frame = DM_FRAME_ANGRY;
                } else {
                    // toggle frame
                    if (current_frame == DM_FRAME_IDLE1) {
                        new_frame = DM_FRAME_IDLE2;
                    } else if (current_frame == DM_FRAME_IDLE2) {
                        new_frame = DM_FRAME_IDLE1;
                    } else {
                        static_assert(DM_FRAME_IDLE2 >= DM_FRAME_IDLE1);
                        static_assert(DM_FRAME_IDLE1 >= 0);
                        static_assert(DM_FRAME_IDLE2 >= 0);
                        new_frame = static_cast<int>(ctx._rng.range(DM_FRAME_IDLE1, DM_FRAME_IDLE2)); // Frame 0 or 1 (active frames)
                    }
                }
            }
        } else if (lower_threshold) {
            if (current_frame == DM_FRAME_ATTACK || current_frame == DM_FRAME_ANGRY) {
                // back to idle
                new_start_frame_index = DM_FRAME_IDLE1;
                new_end_frame_index = DM_FRAME_IDLE2;
                new_row_state = animation_state_row_t::Idle;
                new_frame = DM_FRAME_IDLE1;
            }
        }

        const bool changed = anim_shm.animation_player_data.frame_index != new_frame || anim_shm.animation_player_data.sprite_sheet_row != new_row || state.row_state != new_row_state;
        if (changed) {
            anim_shm.animation_player_data.frame_index = new_frame;
            animation_player_data.sprite_sheet_row = new_row;
            animation_player_data.start_frame_index = new_start_frame_index;
            animation_player_data.end_frame_index = new_end_frame_index;
            state.row_state = new_row_state;
            if (current_config.enable_debug) {
                BONGOCAT_LOG_VERBOSE("Animation frame change: %d", new_frame);
            }
            state.frame_delta_ms_counter = 0;
        }

        return { .changed = changed, .new_frame = new_frame};
    }
#endif

#ifdef FEATURE_PKMN_EMBEDDED_ASSETS
    static anim_next_frame_result_t anim_pkmn_key_pressed_next_frame(animation_context_t& ctx, [[maybe_unused]] const platform::input::input_context_t& input,
                                                                     animation_state_t& state) {
        using namespace assets;

        // read-only config
        assert(ctx._local_copy_config != nullptr);
        const config::config_t& current_config = *ctx._local_copy_config;

        assert(input.shm != nullptr);
        assert(ctx.shm != nullptr);
        animation_shared_memory_t& anim_shm = *ctx.shm;
        //const auto& input_shm = *input.shm;
        auto& animation_player_data = anim_shm.animation_player_data;
        const auto current_frame = animation_player_data.frame_index;
        //const auto current_row = animation_player_data.sprite_sheet_row;
        //const animation_state_row_t current_row_state = state.row_state;
        //const auto anim_index = anim_shm.anim_index;
        //const platform::timestamp_ms_t last_key_pressed_timestamp = input_shm.last_key_pressed_timestamp;
        //const auto& current_frames = reinterpret_cast<pkmn_animation_t&>(get_current_animation(ctx));

        animation_state_row_t new_row_state = state.row_state;
        int new_row = animation_player_data.sprite_sheet_row;
        int new_start_frame_index = animation_player_data.start_frame_index;
        int new_end_frame_index = animation_player_data.end_frame_index;
        int new_frame = current_frame;

        /// @TODO: use state machine for animation (states)

        // in Writing mode/start writing
        new_row = PKMN_SPRITE_SHEET_ROWS-1;
        new_start_frame_index = PKMN_FRAME_IDLE1;
        new_end_frame_index = PKMN_FRAME_IDLE2;
        new_row_state = animation_state_row_t::Writing;
        // toggle frame
        if (current_frame == PKMN_FRAME_IDLE1) {
            new_frame = PKMN_FRAME_IDLE2;
        } else if (current_frame == PKMN_FRAME_IDLE2) {
            new_frame = PKMN_FRAME_IDLE1;
        } else {
            static_assert(PKMN_FRAME_IDLE2 >= PKMN_FRAME_IDLE1);
            static_assert(PKMN_FRAME_IDLE1 >= 0);
            static_assert(PKMN_FRAME_IDLE2 >= 0);
            new_frame = static_cast<int>(ctx._rng.range(PKMN_FRAME_IDLE1, PKMN_FRAME_IDLE2)); // Frame 0 or 1 (active frames)
        }

        const bool changed = anim_shm.animation_player_data.frame_index != new_frame || anim_shm.animation_player_data.sprite_sheet_row != new_row || state.row_state != new_row_state;
        if (changed) {
            anim_shm.animation_player_data.frame_index = new_frame;
            animation_player_data.sprite_sheet_row = new_row;
            animation_player_data.start_frame_index = new_start_frame_index;
            animation_player_data.end_frame_index = new_end_frame_index;
            state.row_state = new_row_state;
            if (current_config.enable_debug) {
                BONGOCAT_LOG_VERBOSE("Animation frame change: %d", new_frame);
            }
            state.frame_delta_ms_counter = 0;
        }

        return { .changed = changed, .new_frame = new_frame};
    }
#endif

#ifdef FEATURE_MS_AGENT_EMBEDDED_ASSETS
    static anim_next_frame_result_t anim_ms_pet_key_pressed_next_frame(animation_context_t& ctx,
                                                                       animation_state_t& state) {
        using namespace assets;

        // read-only config
        assert(ctx._local_copy_config != nullptr);
        const config::config_t& current_config = *ctx._local_copy_config;

        assert(ctx.shm != nullptr);
        animation_shared_memory_t& anim_shm = *ctx.shm;
        //const auto& input_shm = *input.shm;
        auto& animation_player_data = anim_shm.animation_player_data;
        const auto current_frame = animation_player_data.frame_index;
        //const auto current_row = animation_player_data.sprite_sheet_row;
        //const animation_state_row_t current_row_state = state.row_state;
        //const auto anim_index = anim_shm.anim_index;
        //const platform::timestamp_ms_t last_key_pressed_timestamp = input_shm.last_key_pressed_timestamp;

        volatile animation_state_row_t new_row_state = state.row_state;
        auto new_row = animation_player_data.sprite_sheet_row;
        auto new_start_frame_index = animation_player_data.start_frame_index;
        auto new_end_frame_index = animation_player_data.end_frame_index;
        auto new_frame = current_frame;

        /// @TODO: use state machine for animation (states)

        assert(anim_shm.anim_index >= 0);
        const ms_agent_animation_indices_t animation_indices = get_ms_agent_animation_indices(static_cast<size_t>(anim_shm.anim_index));

        // in Writing mode/start writing
        switch (state.row_state) {
            case animation_state_row_t::Test:
            case animation_state_row_t::Happy:
            case animation_state_row_t::Idle:
                // START Writing
                new_start_frame_index = animation_indices.start_index_frame_start_writing;
                new_end_frame_index = animation_indices.end_index_frame_start_writing;
                new_frame = new_start_frame_index;
                new_row = MS_AGENT_SPRITE_SHEET_ROW_START_WRITING;
                new_row_state = animation_state_row_t::StartWriting;
                break;
            case animation_state_row_t::StartWriting:
                // process animation in anim_ms_pet_idle_next_frame
                break;
            case animation_state_row_t::Writing:
                // process animation in anim_ms_pet_idle_next_frame
                break;
            case animation_state_row_t::EndWriting:
                // start end writing and process animation in anim_ms_pet_idle_next_frame
                break;
            case animation_state_row_t::Sleep:
                // wake up when sleeping
                new_row = MS_AGENT_SPRITE_SHEET_ROW_WAKE_UP;
                new_start_frame_index = animation_indices.start_index_frame_wake_up;
                new_end_frame_index = animation_indices.end_index_frame_sleep;
                new_frame = new_start_frame_index;
                new_row_state = animation_state_row_t::WakeUp;
            case animation_state_row_t::WakeUp:
                // process animation in anim_ms_pet_idle_next_frame
                break;
            case animation_state_row_t::Boring:
                // process animation in anim_ms_pet_idle_next_frame
                break;
        }

        const bool changed = anim_shm.animation_player_data.frame_index != new_frame || anim_shm.animation_player_data.sprite_sheet_row != new_row || state.row_state != new_row_state;
        if (changed) {
            anim_shm.animation_player_data.frame_index = new_frame;
            animation_player_data.sprite_sheet_row = new_row;
            animation_player_data.start_frame_index = new_start_frame_index;
            animation_player_data.end_frame_index = new_end_frame_index;
            state.row_state = new_row_state;
            if (current_config.enable_debug) {
                BONGOCAT_LOG_VERBOSE("Key pressed Animation frame change: %d", new_frame);
            }
            state.frame_delta_ms_counter = 0;
        }

        return { .changed = changed, .new_frame = new_frame };
    }
#endif

    static bool anim_handle_idle_animation(animation_context_t& ctx,
                                            [[maybe_unused]] const platform::input::input_context_t& input,
                                            [[maybe_unused]] const platform::update::update_context_t& upd,
                                            animation_state_t& state, const anim_handle_key_press_result_t& trigger_result) {
        using namespace assets;

        // read-only config
        assert(ctx._local_copy_config != nullptr);
        const config::config_t& current_config = *ctx._local_copy_config;

        assert(input.shm != nullptr);
        assert(ctx.shm != nullptr);
        animation_shared_memory_t& anim_shm = *ctx.shm;
        //const auto& input_shm = *input.shm;
        //auto& animation_player_data = anim_shm.animation_player_data;
        //const int current_frame = animation_player_data.frame_index;
        //const int current_row = animation_player_data.sprite_sheet_row;
        //const animation_state_row_t current_row_state = state.row_state;
        //const int anim_index = anim_shm.anim_index;

        if (current_config.animation_speed_ms <= 0 && current_config.test_animation_interval_sec <= 0 && !current_config.idle_animation && !current_config.enable_scheduled_sleep) {
            return false;
        }

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
                auto [changed, new_frame] = anim_ms_pet_idle_next_frame(ctx, input, state, trigger_result);
                ret = changed;
#endif
            }break;
        }
        return ret;
    }

    static anim_handle_key_press_result_t anim_handle_animation_trigger(animation_session_t& animation_trigger_ctx, animation_state_t& state) {
        using namespace assets;

        assert(animation_trigger_ctx._input != nullptr);
        assert(animation_trigger_ctx._input->shm != nullptr);
        assert(animation_trigger_ctx._update != nullptr);
        assert(animation_trigger_ctx._update->shm != nullptr);
        animation_context_t& ctx = animation_trigger_ctx.anim;
        [[maybe_unused]] const platform::input::input_context_t& input = *animation_trigger_ctx._input;
        [[maybe_unused]] const platform::update::update_context_t& upd = *animation_trigger_ctx._update;
        // read-only config
        assert(ctx._local_copy_config != nullptr);
        assert(ctx.shm != nullptr);
        assert(animation_trigger_ctx._config != nullptr);
        const config::config_t& current_config = *ctx._local_copy_config;


        constexpr size_t fds_animation_trigger_index = 0;
        constexpr int fds_count = 1;
        pollfd fds[fds_count] = {
            { .fd = animation_trigger_ctx.trigger_efd._fd, .events = POLLIN, .revents = 0 },
        };
        assert(fds_count == LEN_ARRAY(fds));

        // check poll, close to FPS, 1/3 part of worktime (max) ?
        platform::time_ms_t timeout_ms = current_config.fps > 0 ? 1000 / current_config.fps / 3 : 0;
        timeout_ms = timeout_ms < POOL_MIN_TIMEOUT_MS ? POOL_MIN_TIMEOUT_MS : timeout_ms;
        timeout_ms = timeout_ms > POOL_MAX_TIMEOUT_MS ? POOL_MAX_TIMEOUT_MS : timeout_ms;

        trigger_animation_cause_mask_t triggered_anim_cause = trigger_animation_cause_mask_t::NONE;
        int any_key_press_counter = 0;

        timeout_ms = timeout_ms >= INT_MAX ? INT_MAX : timeout_ms;
        const int poll_result = poll(fds, fds_count, static_cast<int>(timeout_ms));
        if (poll_result > 0) {
            // animation trigger event
            if (fds[fds_animation_trigger_index].revents & POLLIN) {
                BONGOCAT_LOG_VERBOSE("Receive animation trigger event");
                uint64_t u;
                ssize_t rc;
                int attempts = 0;
                assert(MAX_ATTEMPTS <= INT_MAX);
                while ((rc = read(animation_trigger_ctx.trigger_efd._fd, &u, sizeof(u))) == sizeof(u) &&
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
                    }
                }
                if (rc < 0) {
                    check_errno("animation trigger eventfd");
                }

                BONGOCAT_LOG_VERBOSE("animation trigger: %zu", triggered_anim_cause);
            }
        }

        assert(input.shm != nullptr);
        assert(upd.shm != nullptr);
        assert(ctx.shm != nullptr);
        animation_shared_memory_t& anim_shm = *ctx.shm;
        //const auto& input_shm = *input.shm;
        auto& animation_player_data = anim_shm.animation_player_data;
        const int current_frame = animation_player_data.frame_index;
        //const int current_row = animation_player_data.sprite_sheet_row;
        //const animation_state_row_t current_row_state = state.row_state;
        //const int anim_index = anim_shm.anim_index;

        bool ret = false;
        [[maybe_unused]] int ret_new_frame = current_frame;

        // handle working animation
        if (has_flag(triggered_anim_cause, trigger_animation_cause_mask_t::CpuUpdate)) {
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
                case config::config_animation_sprite_sheet_layout_t::MsAgent:
                    break;
            }
            BONGOCAT_LOG_VERBOSE("CPU update detected - switching to frame %d (%zu)", ret_new_frame, triggered_anim_cause);
        }

        // handle key press animation
        if (has_flag(triggered_anim_cause, trigger_animation_cause_mask_t::KeyPress)) {
            switch (anim_shm.anim_type) {
                case config::config_animation_sprite_sheet_layout_t::None:
                    break;
                case config::config_animation_sprite_sheet_layout_t::Bongocat: {
#ifdef FEATURE_BONGOCAT_EMBEDDED_ASSETS
                    auto [changed, new_frame] = anim_bongocat_key_pressed_next_frame(ctx, state);
                    ret = changed;
                    ret_new_frame = new_frame;
#endif
                }break;
                case config::config_animation_sprite_sheet_layout_t::Dm: {
#ifdef FEATURE_ENABLE_DM_EMBEDDED_ASSETS
                    auto [changed, new_frame] = anim_dm_key_pressed_next_frame(ctx, input, state);
                    ret = changed;
                    ret_new_frame = new_frame;
#endif
                }break;
                case config::config_animation_sprite_sheet_layout_t::Pkmn: {
#ifdef FEATURE_PKMN_EMBEDDED_ASSETS
                    auto [changed, new_frame] = anim_pkmn_key_pressed_next_frame(ctx, input, state);
                    ret = changed;
                    ret_new_frame = new_frame;
#endif
                }break;
                case config::config_animation_sprite_sheet_layout_t::MsAgent: {
#ifdef FEATURE_MS_AGENT_EMBEDDED_ASSETS
                    auto [changed, new_frame] = anim_ms_pet_key_pressed_next_frame(ctx, state);
                    ret = changed;
                    ret_new_frame = new_frame;
#endif
                }break;
            }
            BONGOCAT_LOG_VERBOSE("Key press detected - switching to frame %d (%zu)", ret_new_frame, triggered_anim_cause);
        }

        return { .any_key_press_counter = any_key_press_counter, .changed = ret, .triggered_anim_cause = triggered_anim_cause };
    }

    static bool anim_update_state(animation_session_t& animation_trigger_ctx, animation_state_t& state) {
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
                trigger_result = anim_handle_animation_trigger(animation_trigger_ctx, state);
                hold_frame = has_flag(trigger_result.triggered_anim_cause, trigger_animation_cause_mask_t::KeyPress) || has_flag(trigger_result.triggered_anim_cause, trigger_animation_cause_mask_t::CpuUpdate);
                idle_changed = anim_handle_idle_animation(ctx, input, upd, state, trigger_result);
            }
            key_pressed = has_flag(trigger_result.triggered_anim_cause, trigger_animation_cause_mask_t::KeyPress) && trigger_result.any_key_press_counter > 0;
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
        state.boring_frame_showed = false;
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
            animation_shared_memory_t& anim_shm = *ctx.shm;
            auto& animation_player_data = anim_shm.animation_player_data;

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
                    animation_player_data.frame_index = current_config.idle_frame;
                    animation_player_data.sprite_sheet_row = assets::BONGOCAT_SPRITE_SHEET_ROWS-1;
                    animation_player_data.start_frame_index = 0;
                    animation_player_data.end_frame_index = 1;
                    state.row_state = animation_state_row_t::Idle;
#endif
                    break;
                case config::config_animation_sprite_sheet_layout_t::Dm:
#ifdef FEATURE_ENABLE_DM_EMBEDDED_ASSETS
                    animation_player_data.frame_index = current_config.idle_frame;
                    animation_player_data.sprite_sheet_row = assets::DM_SPRITE_SHEET_ROWS-1;
                    animation_player_data.start_frame_index = 0;
                    animation_player_data.end_frame_index = 1;
                    state.row_state = animation_state_row_t::Idle;
#endif
                    break;
                case config::config_animation_sprite_sheet_layout_t::Pkmn:
#ifdef FEATURE_PKMN_EMBEDDED_ASSETS
                    animation_player_data.frame_index = current_config.idle_frame;
                    animation_player_data.sprite_sheet_row = assets::PKMN_SPRITE_SHEET_ROWS-1;
                    animation_player_data.start_frame_index = 0;
                    animation_player_data.end_frame_index = 1;
                    state.row_state = animation_state_row_t::Idle;
#endif
                    break;
                case config::config_animation_sprite_sheet_layout_t::MsAgent: {
#ifdef FEATURE_MS_AGENT_EMBEDDED_ASSETS
                    assert(anim_shm.anim_index >= 0);
                    const ms_agent_animation_indices_t animation_indices = get_ms_agent_animation_indices(static_cast<size_t>(anim_shm.anim_index));
                    animation_player_data.frame_index = current_config.idle_frame;
                    animation_player_data.sprite_sheet_row = assets::MS_AGENT_SPRITE_SHEET_ROW_IDLE;
                    animation_player_data.start_frame_index = animation_indices.start_index_frame_idle;
                    animation_player_data.end_frame_index = animation_indices.end_index_frame_idle;
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
            platform::time_ms_t check_config_timeout_ms;
            int32_t fps = 1;
            {
                assert(ctx._local_copy_config != nullptr);
                const config::config_t& current_config = *ctx._local_copy_config;

                fps = current_config.fps;
                check_config_timeout_ms = current_config.fps > 0 ? 1000 / current_config.fps / 3 : 0;
            }

            bool reload_config = false;
            uint64_t new_gen{atomic_load(trigger_ctx._config_generation)};

            /// event poll
            constexpr size_t fds_update_config_index = 0;
            constexpr nfds_t fds_count = 1;
            pollfd fds[fds_count] = {
                { .fd = trigger_ctx.anim.update_config_efd._fd, .events = POLLIN, .revents = 0 },
            };
            const int poll_result = poll(fds, fds_count, static_cast<int>(check_config_timeout_ms));
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
            }

            // Update Animations
            {
                platform::LockGuard guard (trigger_ctx.anim.anim_lock);
                assert(ctx.shm != nullptr);
                const bool frame_changed = anim_update_state(trigger_ctx, state);
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

                    ctx.shm->animation_player_data.time_until_next_frame_ms = 0;
                    //BONGOCAT_LOG_VERBOSE("Animation skipped frame(s) to catch up");
                } else {
                    // Sleep until the next frame using absolute time
                    const auto sec_diff  = next_frame_time.tv_sec  - now.tv_sec;
                    const auto nsec_diff = next_frame_time.tv_nsec - now.tv_nsec;
                    ctx.shm->animation_player_data.time_until_next_frame_ms =
                        static_cast<platform::time_ms_t>(sec_diff * 1000L + (nsec_diff + 999999LL) / 1000000LL);

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
        ctx.shm->animation_player_data.frame_index = !ctx._local_copy_config->idle_animation ? ctx._local_copy_config->idle_frame : ctx.shm->animation_player_data.frame_index;  // initial frame

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
