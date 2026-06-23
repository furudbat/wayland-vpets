#!/usr/bin/env bash

set -euo pipefail

#make debug
#PROGRAM="./cmake-build-debug-all-assets-colored-preload/bongocat"
#PROGRAM="./cmake-build-debug/bongocat"
#PROGRAM="./build/bongocat-all"
PROGRAM="./cmake-build-release/bongocat-all"

WORKDIR=$(mktemp -d)
CONFIG="$WORKDIR/cpu.bongocat.conf"  # config file to modify
OG_CONFIG=./examples/cpu-digimon.bongocat.conf
cp $OG_CONFIG $CONFIG

# pre config
echo "[INFO] Set Sprite Sheet: dmc:Metal Greymon (Virus)"
sed -i 's/^enable_scheduled_sleep=1/enable_scheduled_sleep=0/' "$CONFIG"
sed -i -E 's/^invert_color=[0-9]+/invert_color=0/' "$CONFIG"
sed -i -E 's/^animation_name=.*/animation_name=dmc:Metal Greymon (Virus)/' "$CONFIG"

#cat "$CONFIG"
#sleep 10
#clear

RECORD_FILE="assets/test-output-cpu.mp4"
REGION="3640,0 338x50"
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
sleep 10

# Test 0
if [[ -f "/proc/$PID/fd/0" ]]; then
  printf '\e' > /proc/$PID/fd/0
  sleep 1
  printf '\e' > /proc/$PID/fd/0
  sleep 1
fi
sleep 7
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
sleep 3

if [[ -f "/proc/$PID/fd/0" ]]; then
  printf '\e' > /proc/$PID/fd/0
  sleep 1
  printf '\e' > /proc/$PID/fd/0
  sleep 1
  printf '\e' > /proc/$PID/fd/0
  sleep 1
  printf '\e' > /proc/$PID/fd/0
  sleep 1
fi
sleep 2

# --- verify running ---
if kill -0 "$PID" 2>/dev/null; then
    echo "[PASS] Process $PID still running!"
else
    echo "[FAIL] Process terminated"
    exit 1
fi

kill -INT "$REC_PID"
wait "$REC_PID"
RECORD_FILE_2="assets/test-demo-2.gif"
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
