
#!/usr/bin/env bash

set -euo pipefail

# Programs
# PROGRAM_1="./cmake-build-debug-all-assets-colored-preload/bongocat"
# PROGRAM_1="./cmake-build-debug/bongocat-all"
PROGRAM_1="./cmake-build-debug-all-features/bongocat-all"
PROGRAM_2="./cmake-build-release-all-features/bongocat-all"

OG_CONFIG="./examples/test/test.bongocat.conf"

# Test tracking
TOTAL_TESTS=0
FAILED_TESTS=0

# --- Test function ---
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

# --- Tests ---

run_test \
    "Check Config (default)" \
    1 \
    "$PROGRAM_2" --check-config

run_test \
    "Check Config (valid config)" \
    0 \
    "$PROGRAM_2" --check-config --config "$OG_CONFIG"

run_test \
    "List Monitors (debug)" \
    0 \
    "$PROGRAM_1" --list-monitors --debug

run_test \
    "List Monitors (release)" \
    0 \
    "$PROGRAM_2" --list-monitors

if [ "$FAILED_TESTS" -gt 0 ]; then
    echo "[FAIL] Some tests failed!"
    exit 1
fi

echo "[SUCCESS] All tests passed!"
exit 0
