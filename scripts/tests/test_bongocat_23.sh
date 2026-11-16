#!/usr/bin/env bash

set -euo pipefail

cd ./examples/custom-sprite-sheets-2

#make debug
#PROGRAM="../../cmake-build-debug-all-assets-colored-preload/bongocat"
PROGRAM="../../cmake-build-debug-all-features/bongocat-all"
#PROGRAM="../../build/bongocat-all"

CONFIG1="../../examples/test/test.bongocat.conf"

find . -maxdepth 1 -type f -name "*.conf" | while read -r CONFIG2; do
  echo "[TEST] Starting program..."
  cat "$CONFIG1" "$CONFIG2"  | "$PROGRAM" --ignore-running --strict --config - &
  PID=$!
  echo "[TEST] Program PID = $PID"
  sleep 10

  # --- trap cleanup ---
  cleanup() {
      echo "[TEST] Cleaning up..."
      kill -9 "$PID" 2>/dev/null || true
      cp $OG_CONFIG $CONFIG
      rm -rf "$WORKDIR"
  }
  trap cleanup EXIT

  echo "[INFO] Test Program: ${PROGRAM} ${CONFIG2}"

  # --- verify not running ---
  if kill -0 "$PID" 2>/dev/null; then
      echo "[FAIL] Process $PID still running!"
      kill -9 "$PID" 2>/dev/null
      exit 1
  else
      echo "[PASS] Process terminated successfully"
  fi
done