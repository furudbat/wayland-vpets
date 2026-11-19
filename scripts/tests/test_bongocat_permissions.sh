#!/usr/bin/env bash
##############################################################################
# test_permissions.sh
#
# Tests keyboard access in Docker (see test_setgid_docker.sh):
#   1. not in input group, no setgid          -> fails
#   2. in input group                         -> opens
#   3. not in input group, setgid bongocat    -> opens
#
# Edit KEYBOARD below, find yours with: ls -l /dev/input/by-id/*-event-kbd
##############################################################################
set -euo pipefail

# keyboard to test with (/dev/input/by-id/... or /dev/input/eventX)
KEYBOARD="/dev/input/event7"

# seconds each case runs
TIMEOUT=10

if [[ ! -e "$KEYBOARD" ]]; then
  echo "Keyboard not found: $KEYBOARD" >&2
  echo "Available keyboards:" >&2
  ls -1 /dev/input/by-id/*-event-kbd >&2 2> /dev/null || echo "  (none)" >&2
  exit 1
fi

DEVICE="$(readlink -f "$KEYBOARD")"
echo "Keyboard: $KEYBOARD -> $DEVICE"

exec "$(dirname "$0")/test_setgid_docker.sh" -d "$DEVICE" -t "$TIMEOUT"
