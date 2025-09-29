#!/usr/bin/env bash

set -euo pipefail

#make debug
#PROGRAM="./cmake-build-debug-all-assets-colored-preload/bongocat"
#PROGRAM="./cmake-build-debug/bongocat"
#PROGRAM="./build/bongocat-all"
PROGRAM="./cmake-build-release/bongocat-all"

for base in animated-digimon.bongocat digimon.bongocat dmc.bongocat idle-only-digimon.bongocat; do
  WORKDIR=$(mktemp -d)
  CONFIG="$WORKDIR/${base}.conf"  # config file to modify
  OG_CONFIG=./examples/${base}.conf
  cp $OG_CONFIG $CONFIG

  RECORD_FILE="assets/test-output-${base}.mp4"
  REGION="2110,0 200x50"
  sleep 2
  echo "wf-recorder -y -o DP-1 -g '${REGION}' -f ${RECORD_FILE}"
  wf-recorder -y -o DP-1 -g "${REGION}" -f "${RECORD_FILE}" &
  REC_PID=$!


  "$PROGRAM" --config "$CONFIG" --ignore-running --strict &
  PID=$!
  # --- trap cleanup ---
  cleanup() {
      kill -9 "$PID" 2>/dev/null || true
      rm -rf "$WORKDIR"
  }
  trap cleanup EXIT
  sleep 3

  # Test
  echo "[INFO] Start testing"
  sleep 5
  if [[ -f "/proc/$PID/fd/0" ]]; then
    printf '\e' > /proc/$PID/fd/0
    sleep 1
    printf '\e' > /proc/$PID/fd/0
    sleep 1
    printf '\e' > /proc/$PID/fd/0
    sleep 1
  fi
  sleep 5

  # --- verify running ---
  if kill -0 "$PID" 2>/dev/null; then
      echo "[PASS] Process $PID still running!"
  else
      echo "[FAIL] Process terminated"
      exit 1
  fi

  kill -INT "$REC_PID"
  wait "$REC_PID"
  RECORD_FILE_2="assets/test-demo-${base}.gif"
  ffmpeg -y -i "$RECORD_FILE" -vf "fps=15,scale=480:-1:flags=lanczos,split[s0][s1];[s0]palettegen[p];[s1][p]paletteuse" "${RECORD_FILE_2}"
  #rm "$RECORD_FILE"

  # --- send SIGTERM ---
  kill -TERM "$PID"
  sleep 5
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