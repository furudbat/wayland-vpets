#ifndef BONGOCAT_UPDATE_H
#define BONGOCAT_UPDATE_H

#include "config/config.h"
#include "graphics/animation_context.h"
#include "module.h"
#include "update_context.h"
#include "utils/error.h"

namespace bongocat::platform::update {

BONGOCAT_STUBS_BEGIN

BONGOCAT_NODISCARD BONGOCAT_UPDATE_STUB_INLINE created_result_t<AllocatedMemory<update_context_t>>
create(const config::config_t& config) BONGOCAT_UPDATE_STUB_RETURN({});
BONGOCAT_NODISCARD BONGOCAT_UPDATE_STUB_INLINE bongocat_error_t start(update_context_t& update,
                                                                      animation::animation_context_t& animation_ctx,
                                                                      const config::config_t& config,
                                                                      CondVariable& configs_reloaded_cond,
                                                                      atomic_uint64_t& config_generation)
    BONGOCAT_UPDATE_STUB_RETURN(bongocat_error_t::BONGOCAT_SUCCESS);
BONGOCAT_NODISCARD BONGOCAT_UPDATE_STUB_INLINE bongocat_error_t restart(update_context_t& update,
                                                                        animation::animation_context_t& animation_ctx,
                                                                        const config::config_t& config,
                                                                        CondVariable& configs_reloaded_cond,
                                                                        atomic_uint64_t& config_generation)
    BONGOCAT_UPDATE_STUB_RETURN(bongocat_error_t::BONGOCAT_SUCCESS);
BONGOCAT_UPDATE_STUB_INLINE void trigger_update_config(update_context_t& ctx, const config::config_t& config,
                                                       uint64_t config_generation) BONGOCAT_UPDATE_STUB;
BONGOCAT_UPDATE_STUB_INLINE void update_config(update_context_t& ctx, const config::config_t& config,
                                               uint64_t new_gen) BONGOCAT_UPDATE_STUB;

BONGOCAT_NODISCARD BONGOCAT_UPDATE_STUB_INLINE const cpu_snapshot_t *get_latest_snapshot(update_context_t& ctx)
    BONGOCAT_UPDATE_STUB_RETURN(BONGOCAT_NULLPTR);

BONGOCAT_STUBS_END

}  // namespace bongocat::platform::update

#endif  // BONGOCAT_UPDATE_H