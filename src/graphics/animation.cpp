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
    };

    struct animation_state_t {
        platform::time_ms_t frame_delta_ms_counter{0};
        platform::time_ns_t frame_time_ns{0};
        platform::time_ms_t frame_time_ms{0};
        platform::time_ms_t hold_frame_ms{0};
        platform::timestamp_ms_t last_frame_update_ms{0};
        animation_state_row_t row_state{animation_state_row_t::Idle};
    };

    struct anim_next_frame_result_t {
        bool changed{false};
        int new_frame{0};
    };

    static anim_next_frame_result_t anim_bongocat_idle_next_frame(animation_context_t& ctx, const platform::input::input_context_t& input,
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
        const int current_frame = animation_player_data.frame_index;
        //const int current_row = animation_player_data.sprite_sheet_row;
        //const animation_state_row_t current_row_state = state.row_state;
        //const int anim_index = anim_shm.anim_index;
        const platform::timestamp_ms_t last_key_pressed_timestamp = input_shm.last_key_pressed_timestamp;

        animation_state_row_t new_row_state = state.row_state;
        int new_row = animation_player_data.sprite_sheet_row;
        int new_start_frame_index = animation_player_data.start_frame_index;
        int new_end_frame_index = animation_player_data.end_frame_index;
        int new_frame = current_frame;

        const bool can_go_next_frame = current_config.test_animation_duration_ms > 0 && state.frame_delta_ms_counter > current_config.test_animation_duration_ms;

        // Idle Animation
        if (can_go_next_frame) {
            // toggle frame
            if (current_frame == BONGOCAT_FRAME_LEFT_DOWN) {
                new_frame = BONGOCAT_FRAME_RIGHT_DOWN;
            } else if (current_frame == BONGOCAT_FRAME_RIGHT_DOWN) {
                new_frame = BONGOCAT_FRAME_LEFT_DOWN;
            } else {
                static_assert(BONGOCAT_FRAME_RIGHT_DOWN >= BONGOCAT_FRAME_LEFT_DOWN);
                static_assert(BONGOCAT_FRAME_LEFT_DOWN >= 0);
                static_assert(BONGOCAT_FRAME_RIGHT_DOWN >= 0);
                new_frame = static_cast<int>(ctx.rng.range(BONGOCAT_FRAME_LEFT_DOWN, BONGOCAT_FRAME_RIGHT_DOWN));
            }
        }
        new_row = BONGOCAT_SPRITE_SHEET_ROWS-1;
        new_start_frame_index = 1;
        new_end_frame_index = 2;
        new_row_state = animation_state_row_t::Idle;

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
            if (now - last_key_pressed_timestamp >= idle_sleep_timeout_ms) {
                new_frame = BONGOCAT_FRAME_BOTH_DOWN;
                new_start_frame_index = BONGOCAT_FRAME_BOTH_DOWN;
                new_end_frame_index = BONGOCAT_FRAME_BOTH_DOWN;
                new_row_state = animation_state_row_t::Sleep;
            }
        }

        const bool changed = ctx.shm->animation_player_data.frame_index != new_frame || ctx.shm->animation_player_data.sprite_sheet_row != new_row;
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

    static anim_next_frame_result_t anim_digimon_idle_next_frame(animation_context_t& ctx,
                                                                 animation_state_t& state) {
        using namespace assets;

        // read-only config
        assert(ctx._local_copy_config != nullptr);
        const config::config_t& current_config = *ctx._local_copy_config;

        assert(ctx.shm != nullptr);
        animation_shared_memory_t& anim_shm = *ctx.shm;
        //const auto& input_shm = *input.shm;
        auto& animation_player_data = anim_shm.animation_player_data;
        const int current_frame = animation_player_data.frame_index;
        //const int current_row = animation_player_data.sprite_sheet_row;
        //const animation_state_row_t current_row_state = state.row_state;
        const int anim_index = anim_shm.anim_index;

        animation_state_row_t new_row_state = state.row_state;
        int new_row = animation_player_data.sprite_sheet_row;
        int new_start_frame_index = animation_player_data.start_frame_index;
        int new_end_frame_index = animation_player_data.end_frame_index;
        int new_frame = current_frame;

        const bool can_go_next_frame = (current_config.animation_speed_ms > 0 && state.frame_delta_ms_counter > current_config.animation_speed_ms) || (current_config.test_animation_duration_ms > 0 && state.frame_delta_ms_counter > current_config.test_animation_duration_ms);

        // Idle Animation
        const auto& current_frames = anim_shm.anims[anim_index].digimon;
        new_end_frame_index = 1;
        new_row = DIGIMON_SPRITE_SHEET_ROWS-1;
        new_start_frame_index = 0;
        new_row_state = animation_state_row_t::Idle;
        // Idle Animation
        if (can_go_next_frame) {
            // toggle frame
            if (current_frame == DIGIMON_FRAME_IDLE2) {
                new_frame = DIGIMON_FRAME_IDLE1;
                new_row_state = animation_state_row_t::Idle;
            } else if (current_frame == DIGIMON_FRAME_IDLE1) {
                new_frame = DIGIMON_FRAME_IDLE2;
                new_row_state = animation_state_row_t::Idle;
            } else {
                static_assert(DIGIMON_FRAME_IDLE2 >= DIGIMON_FRAME_IDLE1);
                static_assert(DIGIMON_FRAME_IDLE1 >= 0);
                static_assert(DIGIMON_FRAME_IDLE2 >= 0);
                new_frame = static_cast<int>(ctx.rng.range(DIGIMON_FRAME_IDLE1, DIGIMON_FRAME_IDLE2)); // Frame 0 or 1 (active frames)
            }
        }
        // Sleep animation
        if (current_config.enable_scheduled_sleep && is_sleep_time(current_config)) {
            // toggle sleep frame (if 2 frame exists for sleeping)
            if (can_go_next_frame) {
                if (current_frame == DIGIMON_FRAME_SLEEP1) {
                    if (current_frames.sleep_2.valid) {
                        new_frame = DIGIMON_FRAME_SLEEP2;
                        new_row_state = animation_state_row_t::Sleep;
                    } else if (current_frames.sleep1.valid) {
                        new_frame = DIGIMON_FRAME_SLEEP1;
                        new_row_state = animation_state_row_t::Sleep;
                    } else if (current_frames.down1.valid) {
                        BONGOCAT_LOG_VERBOSE("No Sleeping Frame for %d", anim_index);
                        // fallback frame
                        new_frame = DIGIMON_FRAME_DOWN1;
                        new_row_state = animation_state_row_t::Sleep;
                    }
                } else if (current_frame == DIGIMON_FRAME_SLEEP2) {
                    if (current_frames.sleep1.valid) {
                        new_frame = DIGIMON_FRAME_SLEEP1;
                        new_row_state = animation_state_row_t::Sleep;
                    } else if (current_frames.down1.valid) {
                        BONGOCAT_LOG_VERBOSE("No Sleeping Frame for %d", anim_index);
                        // fallback frame
                        new_frame = DIGIMON_FRAME_DOWN1;
                        new_row_state = animation_state_row_t::Sleep;
                    }
                }
            } else {
                // start sleeping
                if (current_frames.sleep1.valid) {
                    new_frame = DIGIMON_FRAME_SLEEP1;
                    new_row_state = animation_state_row_t::Sleep;
                } else if (current_frames.down1.valid) {
                    BONGOCAT_LOG_VERBOSE("No Sleeping Frame for %d", anim_index);
                    // fallback frame
                    new_frame = DIGIMON_FRAME_DOWN1;
                    new_row_state = animation_state_row_t::Sleep;
                }
            }
        }

        const bool changed = animation_player_data.frame_index != new_frame || animation_player_data.sprite_sheet_row != new_row;
        if (changed) {
            animation_player_data.frame_index = new_frame;
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


    static anim_next_frame_result_t anim_ms_pet_idle_next_frame(animation_context_t& ctx, const platform::input::input_context_t& input,
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
        const int current_frame = animation_player_data.frame_index;
        const int current_row = animation_player_data.sprite_sheet_row;
        const animation_state_row_t current_row_state = state.row_state;
        //const int anim_index = anim_shm.anim_index;
        const platform::timestamp_ms_t last_key_pressed_timestamp = input_shm.last_key_pressed_timestamp;

        animation_state_row_t new_row_state = state.row_state;
        int new_row = animation_player_data.sprite_sheet_row;
        int new_start_frame_index = animation_player_data.start_frame_index;
        int new_end_frame_index = animation_player_data.end_frame_index;
        int new_frame = current_frame;

        const bool can_go_next_frame = current_config.animation_speed_ms <= 0 || state.frame_delta_ms_counter > current_config.animation_speed_ms;

        switch (current_row) {
            case CLIPPY_SPRITE_SHEET_ROW_IDLE: {
                // loop idle animation
                if (can_go_next_frame) {
                    const int range = animation_player_data.end_frame_index - animation_player_data.start_frame_index + 1;
                    new_frame = (range != 0) ? animation_player_data.start_frame_index +
                                ((current_frame - animation_player_data.start_frame_index + 1) % range) : current_frame;
                    new_row = CLIPPY_SPRITE_SHEET_ROW_IDLE;
                    new_row_state = animation_state_row_t::Idle;
                }
                // is not sleeping, yet
                if (current_row_state != animation_state_row_t::Sleep) {
                    // Sleep Mode
                    if (current_config.enable_scheduled_sleep) {
                        if (is_sleep_time(current_config)) {
                            // start sleeping
                            new_frame = 0;
                            new_start_frame_index = 0;
                            new_end_frame_index = CLIPPY_FRAMES_SLEEP-1;
                            new_row = CLIPPY_SPRITE_SHEET_ROW_SLEEP;
                            new_row_state = animation_state_row_t::Sleep;
                        }
                    }
                    // Idle Sleep
                    if (current_config.idle_sleep_timeout_sec > 0 && last_key_pressed_timestamp > 0) {
                        const platform::timestamp_ms_t now = platform::get_current_time_ms();
                        const platform::time_ms_t idle_sleep_timeout_ms = current_config.idle_sleep_timeout_sec*1000;
                        if (now - last_key_pressed_timestamp >= idle_sleep_timeout_ms) {
                            // start sleeping
                            new_frame = 0;
                            new_start_frame_index = 0;
                            new_end_frame_index = CLIPPY_FRAMES_SLEEP-1;
                            new_row = CLIPPY_SPRITE_SHEET_ROW_SLEEP;
                            new_row_state = animation_state_row_t::Sleep;
                        }
                    }
                }
            }break;
            case CLIPPY_SPRITE_SHEET_ROW_WRITING:
            case CLIPPY_SPRITE_SHEET_ROW_START_WRITING:
                if (can_go_next_frame) {
                    // cancel writing
                    // start, end writing animation
                    new_frame = 0;
                    new_start_frame_index = 0;
                    new_end_frame_index = CLIPPY_FRAMES_END_WRITING-1;
                    new_row = CLIPPY_SPRITE_SHEET_ROW_END_WRITING;
                    new_row_state = animation_state_row_t::EndWriting;
                }
                break;
            case CLIPPY_SPRITE_SHEET_ROW_END_WRITING:
                if (can_go_next_frame) {
                    // end current animation
                    new_frame = current_frame + 1;
                    if (current_frame >= animation_player_data.end_frame_index) {
                        // back to idle
                        new_frame = 0;
                        new_row = CLIPPY_SPRITE_SHEET_ROW_IDLE;
                        assert(CLIPPY_FRAMES_IDLE <= INT_MAX);
                        new_start_frame_index = current_config.idle_frame % static_cast<int>(CLIPPY_FRAMES_IDLE);
                        new_end_frame_index = CLIPPY_FRAMES_IDLE-1;
                        new_row_state = animation_state_row_t::Idle;
                    }
                }
                break;
            case CLIPPY_SPRITE_SHEET_ROW_SLEEP:
                if (can_go_next_frame) {
                    // continue sleeping, stop at last frame
                    new_frame = current_frame + 1;
                    new_frame = (new_frame >= animation_player_data.end_frame_index) ? animation_player_data.end_frame_index : new_frame;
                }
                break;
        }


        const bool changed = animation_player_data.frame_index != new_frame || animation_player_data.sprite_sheet_row != new_row;
        if (changed) {
            animation_player_data.frame_index = new_frame;
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


    static anim_next_frame_result_t anim_bongocat_key_pressed_next_frame(animation_context_t& ctx,
                                                                         animation_state_t& state) {
        using namespace assets;

        // read-only config
        assert(ctx._local_copy_config != nullptr);
        const config::config_t& current_config = *ctx._local_copy_config;

        assert(ctx.shm != nullptr);
        animation_shared_memory_t& anim_shm = *ctx.shm;
        //const auto& input_shm = *input.shm;
        auto& animation_player_data = anim_shm.animation_player_data;
        const int current_frame = animation_player_data.frame_index;
        //const int current_row = animation_player_data.sprite_sheet_row;
        //const animation_state_row_t current_row_state = state.row_state;
        //const int anim_index = anim_shm.anim_index;
        //const platform::timestamp_ms_t last_key_pressed_timestamp = input_shm.last_key_pressed_timestamp;

        animation_state_row_t new_row_state = state.row_state;
        int new_row = animation_player_data.sprite_sheet_row;
        int new_start_frame_index = animation_player_data.start_frame_index;
        int new_end_frame_index = animation_player_data.end_frame_index;
        int new_frame = current_frame;

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
            new_frame = static_cast<int>(ctx.rng.range(BONGOCAT_FRAME_LEFT_DOWN, BONGOCAT_FRAME_RIGHT_DOWN));
        }
        new_row = BONGOCAT_SPRITE_SHEET_ROWS-1;
        new_start_frame_index = 1;
        new_end_frame_index = 2;
        new_row_state = animation_state_row_t::Writing;

        const bool changed = anim_shm.animation_player_data.frame_index != new_frame || anim_shm.animation_player_data.sprite_sheet_row != new_row;
        if (changed) {
            anim_shm.animation_player_data.frame_index = new_frame;
            animation_player_data.sprite_sheet_row = new_row;
            animation_player_data.start_frame_index = new_start_frame_index;
            animation_player_data.end_frame_index = new_end_frame_index;
            state.row_state = new_row_state;
            if (current_config.enable_debug) {
                BONGOCAT_LOG_VERBOSE("Animation frame change: %d", new_frame);
            }
        }

        return { .changed = changed, .new_frame = new_frame};
    }
    static anim_next_frame_result_t anim_digimon_key_pressed_next_frame(animation_context_t& ctx, const platform::input::input_context_t& input,
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
        const int current_frame = animation_player_data.frame_index;
        //const int current_row = animation_player_data.sprite_sheet_row;
        //const animation_state_row_t current_row_state = state.row_state;
        //const int anim_index = anim_shm.anim_index;
        //const platform::timestamp_ms_t last_key_pressed_timestamp = input_shm.last_key_pressed_timestamp;

        animation_state_row_t new_row_state = state.row_state;
        int new_row = animation_player_data.sprite_sheet_row;
        int new_start_frame_index = animation_player_data.start_frame_index;
        int new_end_frame_index = animation_player_data.end_frame_index;
        int new_frame = current_frame;

        /// @TODO: use state machine for animation (states)

        // in Writing mode/start writing
        new_end_frame_index = 1;
        new_row = DIGIMON_SPRITE_SHEET_ROWS-1;
        new_start_frame_index = 0;
        new_row_state = animation_state_row_t::Writing;
        // toggle frame
        if (current_frame == DIGIMON_FRAME_IDLE1) {
            new_frame = DIGIMON_FRAME_IDLE2;

            if (input_shm.kpm > 0) {
                if (current_config.happy_kpm > 0 && input_shm.kpm >= current_config.happy_kpm) {
                    if (anim_shm.anims[anim_shm.anim_index].digimon.happy.valid) {
                        if (HAPPY_CHANCE_PERCENT >= 100 || ctx.rng.range(0, 99) < HAPPY_CHANCE_PERCENT) {
                            BONGOCAT_LOG_VERBOSE("Show Happy Frame at %d KPM", input_shm.kpm);
                            new_frame = DIGIMON_FRAME_HAPPY;
                            new_row_state = animation_state_row_t::Happy;
                        }
                    }
                }
            }
        } else if (current_frame == DIGIMON_FRAME_IDLE2) {
            new_frame = DIGIMON_FRAME_IDLE1;
        } else {
            static_assert(DIGIMON_FRAME_IDLE2 >= DIGIMON_FRAME_IDLE1);
            static_assert(DIGIMON_FRAME_IDLE1 >= 0);
            static_assert(DIGIMON_FRAME_IDLE2 >= 0);
            new_frame = static_cast<int>(ctx.rng.range(DIGIMON_FRAME_IDLE1, DIGIMON_FRAME_IDLE2)); // Frame 0 or 1 (active frames)
        }

        const bool changed = anim_shm.animation_player_data.frame_index != new_frame || anim_shm.animation_player_data.sprite_sheet_row != new_row;
        if (changed) {
            anim_shm.animation_player_data.frame_index = new_frame;
            animation_player_data.sprite_sheet_row = new_row;
            animation_player_data.start_frame_index = new_start_frame_index;
            animation_player_data.end_frame_index = new_end_frame_index;
            state.row_state = new_row_state;
            if (current_config.enable_debug) {
                BONGOCAT_LOG_VERBOSE("Animation frame change: %d", new_frame);
            }
        }

        return { .changed = changed, .new_frame = new_frame};
    }
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
        const int current_frame = animation_player_data.frame_index;
        const int current_row = animation_player_data.sprite_sheet_row;
        //const animation_state_row_t current_row_state = state.row_state;
        //const int anim_index = anim_shm.anim_index;
        //const platform::timestamp_ms_t last_key_pressed_timestamp = input_shm.last_key_pressed_timestamp;

        animation_state_row_t new_row_state = state.row_state;
        int new_row = animation_player_data.sprite_sheet_row;
        int new_start_frame_index = animation_player_data.start_frame_index;
        int new_end_frame_index = animation_player_data.end_frame_index;
        int new_frame = current_frame;

        /// @TODO: use state machine for animation (states)

        // in Writing mode/start writing
        switch (current_row) {
            case CLIPPY_SPRITE_SHEET_ROW_IDLE:
                // START Writing
                new_frame = 0;
                new_row = CLIPPY_SPRITE_SHEET_ROW_START_WRITING;
                new_start_frame_index = 0;
                new_end_frame_index = CLIPPY_FRAMES_START_WRITING-1;
                new_row_state = animation_state_row_t::StartWriting;
                break;
            case CLIPPY_FRAMES_START_WRITING:
                // writing started, continue
                new_frame = current_frame + 1;
                if (new_frame > animation_player_data.end_frame_index) {
                    // continue with writing animation
                    new_frame = 0;
                    new_row = CLIPPY_SPRITE_SHEET_ROW_WRITING;
                    new_start_frame_index = 0;
                    new_end_frame_index = CLIPPY_FRAMES_WRITING-1;
                    new_row_state = animation_state_row_t::Writing;
                }
                break;
            case CLIPPY_FRAMES_WRITING: {
                // loop writing animation
                const int range = animation_player_data.end_frame_index - animation_player_data.start_frame_index + 1;
                new_frame = (range != 0) ? animation_player_data.start_frame_index +
                            ((current_frame - animation_player_data.start_frame_index + 1) % range) : current_frame;
                new_row = CLIPPY_SPRITE_SHEET_ROW_WRITING;
                new_row_state = animation_state_row_t::Writing;
            }break;
            case CLIPPY_FRAMES_END_WRITING:
                // end writing, continue
                new_frame = current_frame + 1;
                if (new_frame > animation_player_data.end_frame_index) {
                    // back to idle
                    new_frame = 0;
                    new_row = CLIPPY_SPRITE_SHEET_ROW_IDLE;
                    assert(CLIPPY_FRAMES_IDLE <= INT_MAX);
                    new_start_frame_index = current_config.idle_frame % static_cast<int>(CLIPPY_FRAMES_IDLE);
                    new_end_frame_index = CLIPPY_FRAMES_IDLE-1;
                    new_row_state = animation_state_row_t::Idle;
                }
                break;
            case CLIPPY_SPRITE_SHEET_ROW_SLEEP:
                // when not in sleep mode, wake up
                if (!current_config.enable_scheduled_sleep || !is_sleep_time(current_config)) {
                    // back to idle
                    new_frame = 0;
                    new_row = CLIPPY_SPRITE_SHEET_ROW_IDLE;
                    assert(CLIPPY_FRAMES_IDLE <= INT_MAX);
                    new_start_frame_index = current_config.idle_frame % static_cast<int>(CLIPPY_FRAMES_IDLE);
                    new_end_frame_index = CLIPPY_FRAMES_IDLE-1;
                    new_row_state = animation_state_row_t::Idle;
                }
                break;
        }

        const bool changed = anim_shm.animation_player_data.frame_index != new_frame || anim_shm.animation_player_data.sprite_sheet_row != new_row;
        if (changed) {
            anim_shm.animation_player_data.frame_index = new_frame;
            animation_player_data.sprite_sheet_row = new_row;
            animation_player_data.start_frame_index = new_start_frame_index;
            animation_player_data.end_frame_index = new_end_frame_index;
            state.row_state = new_row_state;
            if (current_config.enable_debug) {
                BONGOCAT_LOG_VERBOSE("Animation frame change: %d", new_frame);
            }
        }

        return { .changed = changed, .new_frame = new_frame};
    }

    static bool anim_handle_idle_animation(animation_context_t& ctx, const platform::input::input_context_t& input, animation_state_t& state) {
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

        if (current_config.animation_speed_ms <= 0 && current_config.test_animation_interval_sec <= 0) {
            return false;
        }

        bool ret = false;
        switch (anim_shm.anim_type) {
            case config::config_animation_type_t::None:
                break;
            case config::config_animation_type_t::Bongocat: {
                auto [changed, new_frame] = anim_bongocat_idle_next_frame(ctx, input, state);
                ret = changed;
            }break;
            case config::config_animation_type_t::Digimon: {
                auto [changed, new_frame] = anim_digimon_idle_next_frame(ctx, state);
                ret = changed;
            }break;
            case config::config_animation_type_t::MsPet: {
                auto [changed, new_frame] = anim_ms_pet_idle_next_frame(ctx, input, state);
                ret = changed;
            }break;
        }
        return ret;
    }

    static bool anim_handle_key_press(animation_session_t& animation_trigger_ctx, animation_state_t& state) {
        using namespace assets;

        assert(animation_trigger_ctx._input != nullptr);
        assert(animation_trigger_ctx._input->shm != nullptr);
        animation_context_t& ctx = animation_trigger_ctx.anim;
        const platform::input::input_context_t& input = *animation_trigger_ctx._input;
        // read-only config
        assert(ctx._local_copy_config != nullptr);
        assert(ctx.shm != nullptr);
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

        assert(input.shm != nullptr);
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
        switch (anim_shm.anim_type) {
            case config::config_animation_type_t::None:
                break;
            case config::config_animation_type_t::Bongocat: {
                auto [changed, new_frame] = anim_bongocat_key_pressed_next_frame(ctx, state);
                ret = changed;
                ret_new_frame = new_frame;
            }break;
            case config::config_animation_type_t::Digimon: {
                auto [changed, new_frame] = anim_digimon_key_pressed_next_frame(ctx, input, state);
                ret = changed;
                ret_new_frame = new_frame;
            }break;
            case config::config_animation_type_t::MsPet: {
                auto [changed, new_frame] = anim_ms_pet_key_pressed_next_frame(ctx, state);
                ret = changed;
                ret_new_frame = new_frame;
            }break;
        }
        BONGOCAT_LOG_VERBOSE("Key press detected - switching to frame %d", ret_new_frame);
        return ret;
    }

    static bool anim_update_state(animation_session_t& animation_trigger_ctx, animation_state_t& state) {
        assert(animation_trigger_ctx._input);
        const platform::input::input_context_t& input = *animation_trigger_ctx._input;
        animation_context_t& ctx = animation_trigger_ctx.anim;
        // read-only config
        assert(ctx._local_copy_config != nullptr);
        const config::config_t& current_config = *ctx._local_copy_config;

        bool ret = false;
        do {
            platform::LockGuard guard (ctx.anim_lock);
            state.frame_delta_ms_counter += state.frame_time_ms;

            bool idle_changed = false;
            bool press_changed = anim_handle_key_press(animation_trigger_ctx, state);
            if ((!press_changed && state.hold_frame_ms >= current_config.keypress_duration_ms) || (current_config.test_animation_interval_sec > 0 && state.frame_delta_ms_counter > current_config.test_animation_interval_sec * current_config.fps)) {
                idle_changed = anim_handle_idle_animation(ctx, input, state);
            }

            if (press_changed) {
                BONGOCAT_LOG_VERBOSE("Trigger key press animation");
            }
            if (idle_changed) {
                BONGOCAT_LOG_VERBOSE("Trigger idle animation");
            }

            ret = idle_changed || press_changed;
            if (!ret) {
                state.hold_frame_ms += state.frame_time_ms;
            } else {
                state.frame_delta_ms_counter = 0;
            }
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

        state.hold_frame_ms = 0;
        state.frame_delta_ms_counter = 0;
        state.frame_time_ns = 1000000000LL / current_config.fps;
        state.frame_time_ms = state.frame_time_ns/1000000LL;
        state.last_frame_update_ms = platform::get_current_time_ms();
        state.row_state = animation_state_row_t::Idle;
    }


    static void *anim_thread_main(void *arg) {
        assert(arg);
        auto& trigger_ctx = *static_cast<animation_session_t *>(arg);
        assert(trigger_ctx._input);
        animation_context_t& ctx = trigger_ctx.anim;
        //input_context_t& input = *trigger_ctx._input;

        // read-only config
        assert(ctx._local_copy_config != nullptr);
        const config::config_t& current_config = *ctx._local_copy_config;

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

            // update variables from config
            state.frame_time_ns = 1000000000LL / current_config.fps;
            state.frame_time_ms = state.frame_time_ns/1000000LL;
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
