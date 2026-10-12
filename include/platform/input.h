#ifndef BONGOCAT_INPUT_H
#define BONGOCAT_INPUT_H

#include "config/config.h"
#include "graphics/animation_context.h"
#include "input_context.h"
#include "utils/error.h"

namespace bongocat::platform::input {

// =============================================================================
// INPUT MONITORING FUNCTIONS
// =============================================================================

BONGOCAT_NODISCARD created_result_t<AllocatedMemory<input_context_t>> create(const config::config_t& config);

// Start input monitoring - must be checked
BONGOCAT_NODISCARD bongocat_error_t start(input_context_t& input, animation::animation_context_t& animation_ctx,
                                          const config::config_t& config, CondVariable& configs_reloaded_cond,
                                          atomic_uint64_t& config_generation);

// Restart input monitoring with new devices - must be checked
BONGOCAT_NODISCARD bongocat_error_t restart(input_context_t& input, animation::animation_context_t& animation_ctx,
                                            const config::config_t& config, CondVariable& configs_reloaded_cond,
                                            atomic_uint64_t& config_generation);
void trigger_update_config(input_context_t& ctx, const config::config_t& config, uint64_t config_generation);
void update_config(input_context_t& ctx, const config::config_t& config, uint64_t new_gen);

namespace details {
  enum class privilege_result_t : int8_t {
    Fatal = -1,
    Noop = 0,
    Success = 1,
    Warning = 2,
  };

  [[nodiscard]] privilege_result_t privilege_init(input_context_t& input);
  [[nodiscard]] privilege_result_t privilege_raise(input_context_t& input);
  [[nodiscard]] privilege_result_t privilege_lower(input_context_t& input);
  [[nodiscard]] privilege_result_t privilege_drop(input_context_t& input);
}  // namespace details

}  // namespace bongocat::platform::input

#endif  // BONGOCAT_INPUT_H