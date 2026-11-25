#!/usr/bin/env bash

set -euo pipefail

#make debug
#PROGRAM="./cmake-build-debug/bongocat"
#PROGRAM="./build/bongocat"
PROGRAM="./cmake-build-relwithdebinfo-all-features-tsan/bongocat-all"

NR=$((1700 + RANDOM % 100))
PID_FILE="${XDG_RUNTIME_DIR:-/tmp}/bongocat-${NR}.pid"

WORKDIR=$(mktemp -d)
CONFIG="$WORKDIR/test6.bongocat.conf"
OG_CONFIG=./examples/test/test6.bongocat.conf
cp $OG_CONFIG $CONFIG

cleanup() {
    rm -f "$PID_FILE"
    rm -rf "$WORKDIR"
}
trap cleanup EXIT

fail() {
    echo "[FAIL] $*"
    exit 1
}

# run_check <description> <expected exit code> <grep pattern or ""> <args...>
run_check() {
    local description=$1 expected=$2 pattern=$3 ret=0
    shift 3
    echo
    echo "[TEST] $description"
    echo "[INFO] Test Program: ${PROGRAM} $*"
    timeout 20 "$PROGRAM" "$@" > "$WORKDIR/out.log" 2>&1 || ret=$?
    echo "[INFO] Program exit code: $ret"
    if [[ $ret -ne $expected ]]; then
        tail -n 30 "$WORKDIR/out.log"
        fail "$description: expected exit code $expected, got $ret"
    fi
    if [[ -n "$pattern" ]] && ! grep -qE -- "$pattern" "$WORKDIR/out.log"; then
        tail -n 30 "$WORKDIR/out.log"
        fail "$description: output does not match '$pattern'"
    fi
    [[ ! -e "$PID_FILE" ]] || fail "$description: left a PID file"
    echo "[PASS] $description"
}

if [[ ! -x $PROGRAM ]]; then
    fail "$PROGRAM not found, build first"
fi

run_check "Version" 0 "[0-9]+\.[0-9]+\.[0-9]+" --version
run_check "Help" 0 "--config" --help
run_check "List devices (config format)" 0 "keyboard_device=" --list-devices-config
run_check "Check config --random" 0 "valid" --check-config --random --config "$CONFIG" --nr "$NR"
run_check "Check config --output-name" 0 "valid" --check-config --output-name DP-1 --config "$CONFIG" --nr "$NR"
run_check "Check config --monitor" 0 "valid" --check-config --monitor DP-1 --config "$CONFIG" --nr "$NR"
run_check "Invalid --nr" 1 "" --nr abc --config "$CONFIG"
run_check "Missing --nr value" 1 "" --config "$CONFIG" --nr
run_check "Missing config file" 1 "" --check-config --config "$WORKDIR/does-not-exist.conf"

echo
echo "[SUCCESS] All tests passed!"
