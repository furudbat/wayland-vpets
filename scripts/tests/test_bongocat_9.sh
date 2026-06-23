#!/usr/bin/env bash

set -euo pipefail

#make debug
#PROGRAM="./cmake-build-debug-all-assets-colored-preload/bongocat"
PROGRAM="./cmake-build-debug/bongocat-all"
#PROGRAM="./build/bongocat-all"

echo "[TEST] Starting program (with wrong config)..."
"$PROGRAM" --ignore-running --config 123.not-found.bongocat.conf &
PID=$!
echo "[TEST] Program PID = $PID"
sleep 5

# --- trap cleanup ---
cleanup() {
    echo "[TEST] Cleaning up..."
    kill -9 "$PID" 2>/dev/null || true
}
trap cleanup EXIT

echo "[INFO] Test Program: ${PROGRAM} (pid=${PID})"

# --- verify not running ---
if kill -0 "$PID" 2>/dev/null; then
    echo "[FAIL] Process $PID still running!"
    kill -9 "$PID" 2>/dev/null
    exit 1
else
    echo "[PASS] Process terminated successfully"
fi
