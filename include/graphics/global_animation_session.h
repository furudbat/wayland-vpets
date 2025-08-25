#ifndef BONGOCAT_ANIMATION_EVENT_CONTEXT_H
#define BONGOCAT_ANIMATION_EVENT_CONTEXT_H

#include "graphics/animation_context.h"
#include "platform/input_context.h"

namespace bongocat::animation {

    struct animation_session_t;
    void stop(animation_session_t& anim_ctx);
    void cleanup(animation_session_t& anim_ctx);

    struct animation_session_t {
        animation_context_t anim;

        // event file descriptor
        platform::FileDescriptor trigger_efd;
        platform::FileDescriptor render_efd;

        // config reload threading
        pthread_mutex_t *config_reload_mutex{nullptr};
        platform::FileDescriptor update_config_efd;
        atomic_uint64_t config_seen_generation{0};
        pthread_cond_t *config_reload_cond{nullptr};
        atomic_uint64_t *config_generation{nullptr};
        platform::Mutex input_lock;                     // for syncing input/animation thread (start)

        // globals (references)
        platform::input::input_context_t *_input{nullptr};
        const config::config_t *_config{nullptr};



        animation_session_t() = default;
        ~animation_session_t() {
            cleanup(*this);
        }

        animation_session_t(const animation_session_t& other) = delete;
        animation_session_t& operator=(const animation_session_t& other) = delete;
        animation_session_t(animation_session_t&& other) noexcept = delete;
        animation_session_t& operator=(animation_session_t&& other) noexcept = delete;

        /*
        /// @TODO: mutex in anim is not movable
        animation_session_t(animation_session_t&& other) noexcept
            : anim(bongocat::move(other.anim)),
              trigger_efd(bongocat::move(other.trigger_efd)),
              render_efd(bongocat::move(other.render_efd)),
              config_reload_mutex(other.config_reload_mutex),
              update_config_efd(bongocat::move(other.update_config_efd)),
              config_seen_generation(atomic_load(&other.config_seen_generation)),
              config_reload_cond(other.config_reload_cond),
              config_generation(other.config_generation),
              _input(other._input),
              _config(other._config)
        {
            other.config_reload_mutex = nullptr;
            other.config_reload_cond = nullptr;
            other.config_generation = nullptr;
            atomic_store(&other.config_seen_generation, 0);
            other._input = nullptr;
            other._config = nullptr;
        }
        animation_session_t& operator=(animation_session_t&& other) noexcept {
            if (this != &other) {
                anim = bongocat::move(other.anim);
                trigger_efd = bongocat::move(other.trigger_efd);
                render_efd = bongocat::move(other.render_efd);
                config_reload_mutex = other.config_reload_mutex;
                update_config_efd = bongocat::move(other.update_config_efd);
                atomic_store(&config_seen_generation, atomic_load(&other.config_seen_generation));
                config_reload_cond = other.config_reload_cond;
                config_generation = other.config_generation;
                _input = other._input;
                _config = other._config;

                other._input = nullptr;
                other._config = nullptr;
                other.config_reload_mutex = nullptr;
                other.config_reload_cond = nullptr;
                atomic_store(&other.config_seen_generation, 0);
                other.config_generation = nullptr;
            }
            return *this;
        }
        */
    };
    inline void stop(animation_session_t& anim_ctx) {
        stop(anim_ctx.anim);
        // make sure broadcast on exit
        if (anim_ctx.config_reload_mutex && anim_ctx.config_reload_cond) pthread_mutex_lock(anim_ctx.config_reload_mutex);
        if (anim_ctx.config_reload_cond) pthread_cond_broadcast(anim_ctx.config_reload_cond);
        if (anim_ctx.config_reload_mutex && anim_ctx.config_reload_cond) pthread_mutex_unlock(anim_ctx.config_reload_mutex);
    }
    inline void cleanup(animation_session_t& anim_ctx) {
        cleanup(anim_ctx.anim);
        platform::close_fd(anim_ctx.trigger_efd);
        platform::close_fd(anim_ctx.render_efd);
        platform::close_fd(anim_ctx.update_config_efd);
        anim_ctx._input = nullptr;
        anim_ctx._config = nullptr;
        anim_ctx.config_reload_mutex = nullptr;
        anim_ctx.config_reload_cond = nullptr;
        atomic_store(&anim_ctx.config_seen_generation, 0);
        anim_ctx.config_generation = nullptr;
    }
}

#endif
