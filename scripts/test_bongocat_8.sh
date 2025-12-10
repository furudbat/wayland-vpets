#!/usr/bin/env bash

set -euo pipefail

#make debug
#PROGRAM="./cmake-build-debug-all-assets-colored-preload/bongocat"
#PROGRAM="./cmake-build-debug-all-assets-preload/bongocat-all"
PROGRAM="./cmake-build-debug/bongocat-all"
#PROGRAM="./build/bongocat-all"

WORKDIR=$(mktemp -d)
CONFIG="$WORKDIR/test.bongocat.conf"  # config file to modify
OG_CONFIG=./examples/test.bongocat.conf
cp $OG_CONFIG $CONFIG

sed -i -E 's/^cat_height=[0-9]+/cat_height=96/' "$CONFIG"
sed -i -E 's/^overlay_height=[0-9]+/overlay_height=128/' "$CONFIG"
sed -i -E 's/^enable_antialiasing=[0-9]+/enable_antialiasing=1/' "$CONFIG"

if [[ $# -ge 1 ]]; then
    PID="$1"
    CONFIG="$2"
    cp $CONFIG "${CONFIG}.bak"
    OG_CONFIG="${CONFIG}.bak"
    echo "[TEST] Using provided PID = $PID"
else
    echo "[TEST] Starting program..."
    "$PROGRAM" --config "$CONFIG" --ignore-running &
    PID=$!
    echo "[TEST] Program PID = $PID"
    sleep 5
fi

# --- trap cleanup ---
cleanup() {
    echo "[TEST] Cleaning up..."
    kill -9 "$PID" 2>/dev/null || true
    cp $OG_CONFIG $CONFIG
    rm -rf "$WORKDIR"
}
trap cleanup EXIT

echo "[INFO] Test Program: ${PROGRAM} --config $CONFIG (pid=${PID})"

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

echo "[TEST] Change overlay settings"
echo "[INFO] Set overlay_height"
sed -i -E 's/^cat_height=[0-9]+/cat_height=96/' "$CONFIG"
sed -i -E 's/^overlay_height=[0-9]+/overlay_height=100/' "$CONFIG"
echo "[INFO] Send SIGUSR2"
kill -USR2 "$PID" # Reload config
sleep 10
echo "[INFO] Set overlay_position"
sed -i -E 's/^overlay_position=.*/overlay_position=top/' "$CONFIG"
echo "[INFO] Send SIGUSR2"
kill -USR2 "$PID" # Reload config
sleep 10
echo "[INFO] Set overlay_position"
sed -i -E 's/^overlay_position=.*/overlay_position=bottom/' "$CONFIG"
echo "[INFO] Send SIGUSR2"
kill -USR2 "$PID" # Reload config
sleep 10
echo "[INFO] Set overlay_layer"
sed -i -E 's/^overlay_layer=.*/overlay_layer=overlay/' "$CONFIG"
echo "[INFO] Send SIGUSR2"
kill -USR2 "$PID" # Reload config
sleep 10
echo "[INFO] Set overlay_layer"
sed -i -E 's/^overlay_layer=.*/overlay_layer=top/' "$CONFIG"
echo "[INFO] Send SIGUSR2"
kill -USR2 "$PID" # Reload config
sleep 10
echo "[INFO] Set overlay_height"
sed -i -E 's/^overlay_height=[0-9]+/overlay_height=128/' "$CONFIG"
echo "[INFO] Send SIGUSR2"
kill -USR2 "$PID" # Reload config
sleep 10

echo "[INFO] Set max size"
sed -i -E 's/^cat_height=[0-9]+/cat_height=1024/' "$CONFIG"
sed -i -E 's/^overlay_height=[0-9]+/overlay_height=2560/' "$CONFIG"
echo "[INFO] Send SIGUSR2"
kill -USR2 "$PID" # Reload config
sleep 15
echo "[INFO] Set min size"
sed -i -E 's/^cat_height=[0-9]+/cat_height=16/' "$CONFIG"
sed -i -E 's/^overlay_height=[0-9]+/overlay_height=32/' "$CONFIG"
echo "[INFO] Send SIGUSR2"
kill -USR2 "$PID" # Reload config
sleep 15

sleep 20

# --- verify running ---
if kill -0 "$PID" 2>/dev/null; then
    echo "[PASS] Process $PID still running!"
else
    echo "[FAIL] Process terminated"
    exit 1
fi

echo "[INFO] Set overlay_height"
sed -i -E 's/^cat_height=[0-9]+/cat_height=128/' "$CONFIG"
sed -i -E 's/^overlay_height=[0-9]+/overlay_height=256/' "$CONFIG"
echo "[TEST] Set Monitor"
echo "[INFO] Set monitor"
sed -i -E 's/^monitor=.*/monitor=HDMI-A-1/' "$CONFIG"
echo "[INFO] Send SIGUSR2"
kill -USR2 "$PID" # Reload config
sleep 10
echo "[INFO] Set monitor"
sed -i -E 's/^monitor=.*/monitor=DP-1/' "$CONFIG"
echo "[INFO] Send SIGUSR2"
kill -USR2 "$PID" # Reload config
sleep 10

sleep 20

# --- verify running ---
if kill -0 "$PID" 2>/dev/null; then
    echo "[PASS] Process $PID still running!"
else
    echo "[FAIL] Process terminated"
    exit 1
fi

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
