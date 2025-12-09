#ifndef BONGOCAT_ANIMATION_EVENT_CONTEXT_H
#define BONGOCAT_ANIMATION_EVENT_CONTEXT_H

#include "graphics/animation_context.h"
#include "platform/input_context.h"
#include "platform/update_context.h"

namespace bongocat::animation {

struct animation_session_t;
void stop(animation_session_t& anim_ctx);
void cleanup(animation_session_t& anim_ctx);

struct animation_session_t {
  animation_context_t anim;

  // event file descriptor
  platform::FileDescriptor trigger_efd;
  platform::FileDescriptor render_efd;

  // globals (references)
  const config::config_t *_config{BONGOCAT_NULLPTR};
  platform::CondVariable *_configs_reloaded_cond{BONGOCAT_NULLPTR};
  platform::input::input_context_t *_input{BONGOCAT_NULLPTR};
  platform::update::update_context_t *_update{BONGOCAT_NULLPTR};
  atomic_uint64_t *_config_generation{BONGOCAT_NULLPTR};
  atomic_bool ready{false};
  platform::CondVariable init_cond;

  animation_session_t() = default;
  ~animation_session_t() {
    cleanup(*this);
  }

  animation_session_t(const animation_session_t& other) = delete;
  animation_session_t& operator=(const animation_session_t& other) = delete;
  animation_session_t(animation_session_t&& other) noexcept = delete;
  animation_session_t& operator=(animation_session_t&& other) noexcept = delete;
};
inline void stop(animation_session_t& anim_ctx) {
  stop(anim_ctx.anim);

  anim_ctx._config = BONGOCAT_NULLPTR;
  anim_ctx._configs_reloaded_cond = BONGOCAT_NULLPTR;
  anim_ctx._config_generation = BONGOCAT_NULLPTR;

  anim_ctx.anim.config_updated.notify_all();
  atomic_store(&anim_ctx.ready, false);
  anim_ctx.init_cond.notify_all();
}
inline void cleanup(animation_session_t& anim_ctx) {
  cleanup(anim_ctx.anim);

  platform::close_fd(anim_ctx.trigger_efd);
  platform::close_fd(anim_ctx.render_efd);

  anim_ctx._config = BONGOCAT_NULLPTR;
  anim_ctx._input = BONGOCAT_NULLPTR;
  anim_ctx._update = BONGOCAT_NULLPTR;
  anim_ctx._configs_reloaded_cond = BONGOCAT_NULLPTR;
  atomic_store(&anim_ctx.ready, false);
  anim_ctx.init_cond.notify_all();
}
}  // namespace bongocat::animation

#endif
