#pragma once
#ifdef __cplusplus
//#define namespace zwl_namespace
extern "C" {
#include "../protocols/wlr-foreign-toplevel-management-v1-client-protocol.h"
#include "../protocols/xdg-output-unstable-v1-client-protocol.h"
#include "../protocols/xdg-shell-client-protocol.h"
#include "../protocols/zwlr-layer-shell-v1-client-protocol.h"
}
//#undef namespace
#else
#include "../protocols/wlr-foreign-toplevel-management-v1-client-protocol.h"
#include "../protocols/xdg-output-unstable-v1-client-protocol.h"
#include "../protocols/xdg-shell-client-protocol.h"
#include "../protocols/zwlr-layer-shell-v1-client-protocol.h"
#endif