#ifndef BONGOCAT_INPUT_H
#define BONGOCAT_INPUT_H

#include "config/config.h"
#include "graphics/animation_context.h"
#include "input_context.h"
#include "module.h"
#include "utils/error.h"

namespace bongocat::platform::input {

// =============================================================================
// INPUT MONITORING FUNCTIONS
// =============================================================================

BONGOCAT_STUBS_BEGIN

BONGOCAT_NODISCARD BONGOCAT_INPUT_STUB_INLINE created_result_t<AllocatedMemory<input_context_t>>
create(const config::config_t& config) BONGOCAT_INPUT_STUB_RETURN({});

// Start input monitoring - must be checked
BONGOCAT_NODISCARD BONGOCAT_INPUT_STUB_INLINE bongocat_error_t start(input_context_t& input,
                                                                     animation::animation_context_t& animation_ctx,
                                                                     const config::config_t& config,
                                                                     CondVariable& configs_reloaded_cond,
                                                                     atomic_uint64_t& config_generation)
    BONGOCAT_INPUT_STUB_RETURN(bongocat_error_t::BONGOCAT_SUCCESS);

// Restart input monitoring with new devices - must be checked
BONGOCAT_NODISCARD BONGOCAT_INPUT_STUB_INLINE bongocat_error_t restart(input_context_t& input,
                                                                       animation::animation_context_t& animation_ctx,
                                                                       const config::config_t& config,
                                                                       CondVariable& configs_reloaded_cond,
                                                                       atomic_uint64_t& config_generation)
    BONGOCAT_INPUT_STUB_RETURN(bongocat_error_t::BONGOCAT_SUCCESS);
BONGOCAT_INPUT_STUB_INLINE void trigger_update_config(input_context_t& ctx, const config::config_t& config,
                                                      uint64_t config_generation) BONGOCAT_INPUT_STUB;
BONGOCAT_INPUT_STUB_INLINE void update_config(input_context_t& ctx, const config::config_t& config,
                                              uint64_t new_gen) BONGOCAT_INPUT_STUB;

struct cli_list_devices_args_t {
  bool doctor{false};
  bool config_format{false};
};
BONGOCAT_INPUT_STUB_INLINE int cli_list_devices(input_context_t& ctx, const cli_list_devices_args_t& args)
    BONGOCAT_INPUT_STUB_RETURN(EXIT_SUCCESS);

namespace details {
  enum class privilege_result_t : int8_t {
    Fatal = -1,
    Noop = 0,
    Success = 1,
    Warning = 2,
  };

  BONGOCAT_NODISCARD BONGOCAT_INPUT_STUB_INLINE privilege_result_t privilege_init(input_context_t& input)
      BONGOCAT_INPUT_STUB_RETURN(privilege_result_t::Success);
  BONGOCAT_NODISCARD BONGOCAT_INPUT_STUB_INLINE privilege_result_t privilege_raise(input_context_t& input)
      BONGOCAT_INPUT_STUB_RETURN(privilege_result_t::Success);
  BONGOCAT_NODISCARD BONGOCAT_INPUT_STUB_INLINE privilege_result_t privilege_lower(input_context_t& input)
      BONGOCAT_INPUT_STUB_RETURN(privilege_result_t::Success);
  BONGOCAT_NODISCARD BONGOCAT_INPUT_STUB_INLINE privilege_result_t privilege_drop(input_context_t& input)
      BONGOCAT_INPUT_STUB_RETURN(privilege_result_t::Success);
}  // namespace details

BONGOCAT_STUBS_END

}  // namespace bongocat::platform::input

#endif  // BONGOCAT_INPUT_H