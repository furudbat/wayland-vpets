#ifndef BONGOCAT_INPUT_H
#define BONGOCAT_INPUT_H

#include "input_context.h"
#include "graphics/animation_event_context.h"
#include "config/config.h"
#include "utils/error.h"

bongocat_error_t input_start_monitoring(animation_trigger_context_t& trigger_ctx, input_context_t& ctx, char **device_paths, int num_devices, int enable_debug);
bongocat_error_t input_restart_monitoring(animation_trigger_context_t& trigger_ctx, input_context_t& ctx, char **device_paths, int num_devices, int enable_debug);
void input_update_config(input_context_t& ctx, const config_t& config);
void input_stop(input_context_t& ctx);
void input_cleanup(input_context_t& ctx);

#endif // INPUT_H