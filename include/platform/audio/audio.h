#ifndef BONGOCAT_AUDIO_H
#define BONGOCAT_AUDIO_H

#include "audio_context.h"
#include "config/config.h"
#include "graphics/animation_context.h"
#include "module.h"
#include "utils/error.h"

namespace bongocat::platform::audio {

BONGOCAT_STUBS_BEGIN

BONGOCAT_NODISCARD BONGOCAT_AUDIO_STUB_INLINE created_result_t<AllocatedMemory<audio_context_t>>
create(const config::config_t& config) BONGOCAT_AUDIO_STUB_RETURN({});
BONGOCAT_NODISCARD BONGOCAT_AUDIO_STUB_INLINE bongocat_error_t start(audio_context_t& audio,
                                                                     animation::animation_context_t& animation_ctx,
                                                                     const config::config_t& config,
                                                                     CondVariable& configs_reloaded_cond,
                                                                     atomic_uint64_t& config_generation)
    BONGOCAT_AUDIO_STUB_RETURN(bongocat_error_t::BONGOCAT_SUCCESS);
BONGOCAT_NODISCARD BONGOCAT_AUDIO_STUB_INLINE bongocat_error_t restart(audio_context_t& audio,
                                                                       animation::animation_context_t& animation_ctx,
                                                                       const config::config_t& config,
                                                                       CondVariable& configs_reloaded_cond,
                                                                       atomic_uint64_t& config_generation)
    BONGOCAT_AUDIO_STUB_RETURN(bongocat_error_t::BONGOCAT_SUCCESS);
BONGOCAT_AUDIO_STUB_INLINE void trigger_audio_config(audio_context_t& ctx, const config::config_t& config,
                                                     uint64_t config_generation) BONGOCAT_AUDIO_STUB;
BONGOCAT_AUDIO_STUB_INLINE void update_config(audio_context_t& ctx, const config::config_t& config,
                                              uint64_t new_gen) BONGOCAT_AUDIO_STUB;

BONGOCAT_AUDIO_STUB_INLINE void init_audio_backend() BONGOCAT_AUDIO_STUB;
BONGOCAT_AUDIO_STUB_INLINE void deinit_audio_backend() BONGOCAT_AUDIO_STUB;

BONGOCAT_STUBS_END

}  // namespace bongocat::platform::audio

#endif