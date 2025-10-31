#!/usr/bin/env bash

set -euo pipefail

#make debug
#PROGRAM="./cmake-build-debug-all-assets-colored-preload/bongocat"
PROGRAM="./cmake-build-relwithdebinfo-tsan/bongocat-all"
#PROGRAM="./build/bongocat-all"

find ./examples -maxdepth 1 -type f -name "*.conf" | while read -r OG_CONFIG; do
  WORKDIR=$(mktemp -d)
  CONFIG="$WORKDIR/test.bongocat.conf"  # config file to modify
  cp $OG_CONFIG $CONFIG

  echo "[TEST] Starting program..."
  "$PROGRAM" --watch-config --config "$CONFIG" --ignore-running --strict &
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

  echo "[TEST] Sending SIGUSR2..."
  echo "[INFO] Send SIGUSR2"
  kill -USR2 "$PID"
  sleep 3
  echo "[INFO] Send SIGUSR2"
  kill -USR2 "$PID"
  sleep 5
  echo "[INFO] Spam SIGUSR2"
  kill -USR2 "$PID"
  kill -USR2 "$PID"
  kill -USR2 "$PID"
  kill -USR2 "$PID"
  sleep 7

  sleep 10

  # --- send SIGTERM ---
  echo "[TEST] Sending SIGTERM..."
  kill -TERM "$PID"
  sleep 10
  echo "[INFO] Wait for TERM"
  # wait up to 5 seconds
  for i in {1..5}; do
      if ! kill -0 "$PID" 2>/dev/null; then
          break
      fi
      sleep 1
  done

  # --- verify not running ---
  if kill -0 "$PID" 2>/dev/null; then
      echo "[FAIL] Process $PID still running!"
      kill -9 "$PID" 2>/dev/null
      exit 1
  else
      echo "[PASS] Process terminated successfully"
  fi
done