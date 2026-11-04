
#!/usr/bin/env bash

set -euo pipefail

# make debug
# PROGRAM="./cmake-build-debug-all-assets-colored-preload/bongocat"
# PROGRAM="./cmake-build-debug/bongocat-all"
PROGRAM="./cmake-build-debug-all-features/bongocat-all"
# PROGRAM="./build/bongocat-all"

WORKDIR=$(mktemp -d)

CONFIG_1="$WORKDIR/test.bongocat.conf"
OG_CONFIG_1="./examples/test/test.bongocat.conf"
cp "$OG_CONFIG_1" "$CONFIG_1"

CONFIG_2="$WORKDIR/invalid.test.bongocat.conf"
OG_CONFIG_2="./examples/test/invalid.test.bongocat.conf"
cp "$OG_CONFIG_2" "$CONFIG_2"

# --- test tracking ---
FAILED_TESTS=0
TOTAL_TESTS=0

# --- trap cleanup ---
cleanup() {
    echo "[TEST] Cleaning up..."
    rm -rf "$WORKDIR"
}
trap cleanup EXIT

# --- test function ---
run_test() {
    local description="$1"
    local expected_exit="$2"
    shift 2

    local ret=0

    TOTAL_TESTS=$((TOTAL_TESTS + 1))

    echo
    echo "[TEST] $description"
    echo "[INFO] Test Program: $*"

    if "$@"; then
        ret=0
    else
        ret=$?
    fi

    echo "[INFO] Program exit code: $ret"

    if [ "$ret" -eq "$expected_exit" ]; then
        echo "[PASS] $description"
    else
        echo "[FAIL] $description (expected: $expected_exit, got: $ret)"
        FAILED_TESTS=$((FAILED_TESTS + 1))
    fi
}

# --- tests ---

run_test \
    "Valid configuration check" \
    0 \
    "$PROGRAM" --check-config --config "$CONFIG_1" --ignore-running

run_test \
    "Invalid configuration validation" \
    1 \
    "$PROGRAM" --check-config --config "$CONFIG_2" --ignore-running

# --- summary ---

if [ "$FAILED_TESTS" -gt 0 ]; then
    exit 1
fi

echo "[SUCCESS] All tests passed!"
exit 0
