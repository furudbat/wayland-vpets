#!/usr/bin/env bash

set -euo pipefail

cd ./examples/custom-sprite-sheets

#make debug
#PROGRAM="../../cmake-build-debug-all-assets-colored-preload/bongocat"
PROGRAM="../../cmake-build-relwithdebinfo-tsan/bongocat-all"
#PROGRAM="../../build/bongocat-all"

CONFIG1="../../examples/test.bongocat.conf"

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

  echo "[INFO] Test Program: ${PROGRAM} ${CONFIG2} (pid=${PID})"

  sleep 10
  if [[ -f "/proc/$PID/fd/0" ]]; then
    # --- simulate pressing ESC ---
    echo "[TEST] Sending ESC key..."
    echo "[INFO] Send stdin"
    printf '\e' > /proc/$PID/fd/0
    sleep 5
    echo "[INFO] Send stdin"
    printf '\e' > /proc/$PID/fd/0
    sleep 1
    # a bit of a spam
    echo "[INFO] Spam stdin"
    printf '\e' > /proc/$PID/fd/0
    printf '\e' > /proc/$PID/fd/0
    printf '\e' > /proc/$PID/fd/0
    printf '\e' > /proc/$PID/fd/0
    sleep 5
    echo "[INFO] Spam stdin slower"
    printf '\e' > /proc/$PID/fd/0
    sleep 1
    printf '\e' > /proc/$PID/fd/0
    sleep 1
    printf '\e' > /proc/$PID/fd/0
    sleep 1
    printf '\e' > /proc/$PID/fd/0
    sleep 3
  fi

  echo "[TEST] Sending SIGUSR1..."
  echo "[INFO] Send SIGUSR1"
  kill -USR1 "$PID"
  sleep 2
  echo "[INFO] Send SIGUSR1"
  kill -USR1 "$PID"
  sleep 2

  echo "[TEST] CPU threshold"
  if command -v stress-ng >/dev/null 2>&1; then
      echo "[INFO] Running stress-ng to generate load"
      stress-ng --cpu 0 --timeout 15s --metrics-brief &
      sleep 20
  elif command -v stress >/dev/null 2>&1; then
      echo "[INFO] Running stress to generate load"
      stress --cpu "$(nproc)" --timeout 15s &
      sleep 20
  else
      echo "[WARN] No stress tool found, skipping load generation"
  fi
  sleep 5

  # --- verify running ---
  if kill -0 "$PID" 2>/dev/null; then
      echo "[PASS] Process $PID still running!"
  else
      echo "[FAIL] Process terminated"
      exit 1
  fi

  sleep 20

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