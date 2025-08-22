#ifndef BONGOCAT_ANIMATION_EVENT_CONTEXT_H
#define BONGOCAT_ANIMATION_EVENT_CONTEXT_H

#include "graphics/animation_context.h"
#include "platform/input_context.h"

namespace bongocat::animation {

    struct animation_session_t;
    void cleanup(animation_session_t& anim);

    struct animation_session_t {
        animation_context_t anim;

        // event file descriptor
        platform::FileDescriptor trigger_efd;
        platform::FileDescriptor render_efd;

        platform::input::input_context_t *_input{nullptr};

        animation_session_t() = default;
        ~animation_session_t() {
            cleanup(*this);
        }

        animation_session_t(const animation_session_t& other) = delete;
        animation_session_t& operator=(const animation_session_t& other) = delete;

        animation_session_t(animation_session_t&& other) noexcept
            : anim(std::move(other.anim)),
              trigger_efd(std::move(other.trigger_efd)),
              render_efd(std::move(other.render_efd)),
              _input(other._input) // transfer pointer
        {
            other._input = nullptr;
        }
        animation_session_t& operator=(animation_session_t&& other) noexcept {
            if (this != &other) {
                anim = std::move(other.anim);
                trigger_efd = std::move(other.trigger_efd);
                render_efd = std::move(other.render_efd);

                _input = other._input;
                other._input = nullptr;
            }
            return *this;
        }
    };
    inline void cleanup(animation_session_t& anim_ctx) {
        cleanup(anim_ctx.anim);
        platform::close_fd(anim_ctx.trigger_efd);
        platform::close_fd(anim_ctx.render_efd);
        anim_ctx._input = nullptr;
    }
}

#endif
