#pragma once
#ifdef __cplusplus
// #define namespace zwl_namespace
#  if defined(__GNUC__) || defined(__clang__)
#    pragma GCC diagnostic push
#    pragma GCC diagnostic ignored "-Wdouble-promotion"
#    pragma GCC diagnostic ignored "-Wsign-compare"
#    pragma GCC diagnostic ignored "-Wunused-function"
#    pragma GCC diagnostic ignored "-Wold-style-cast"
// #pragma GCC diagnostic ignored "-Wsign-conversion"
#  endif
extern "C" {
#  include "../protocols/wlr-foreign-toplevel-management-v1-client-protocol.h"
#  include "../protocols/xdg-output-unstable-v1-client-protocol.h"
#  include "../protocols/xdg-shell-client-protocol.h"
#  include "../protocols/zwlr-layer-shell-v1-client-protocol.h"
}
#  if defined(__GNUC__) || defined(__clang__)
#    pragma GCC diagnostic pop
#  endif
// #undef namespace
#else
#  include "../protocols/wlr-foreign-toplevel-management-v1-client-protocol.h"
#  include "../protocols/xdg-output-unstable-v1-client-protocol.h"
#  include "../protocols/xdg-shell-client-protocol.h"
#  include "../protocols/zwlr-layer-shell-v1-client-protocol.h"
#endif