#!/usr/bin/env bash

set -euo pipefail

#make debug
#PROGRAM="./cmake-build-debug-all-assets-colored-preload/bongocat"
#PROGRAM="./cmake-build-debug/bongocat-all"
PROGRAM="./cmake-build-debug-all-features/bongocat-all"
#PROGRAM="./build/bongocat-all"

WORKDIR=$(mktemp -d)
CONFIG="$WORKDIR/test.bongocat.conf"  # config file to modify
OG_CONFIG=./examples/test/test.bongocat.conf2
cp $OG_CONFIG $CONFIG

if [[ $# -ge 1 ]]; then
    PID="$1"
    CONFIG="$2"
    cp $CONFIG "${CONFIG}.bak"
    OG_CONFIG="${CONFIG}.bak"
    echo "[TEST] Using provided PID = $PID"
else
    echo "[TEST] Starting program..."
    "$PROGRAM" --config "$CONFIG" --ignore-running --strict &
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

sed -i -E 's/^cat_height=[0-9]+/cat_height=64/' "$CONFIG"
sed -i -E 's/^overlay_height=[0-9]+/overlay_height=128/' "$CONFIG"

echo "[TEST] Change animation sprite"
echo "[INFO] Set animation_name..."
sed -i -E 's/^animation_name=.*/animation_name=Koromon/' "$CONFIG"
sed -i -E 's/^evolution=.*/evolution=normal/' "$CONFIG"
sed -i -E 's/^evolution_speed_factor=.*/evolution_speed_factor=3600.0/' "$CONFIG"
echo "[INFO] Send SIGUSR2"
kill -USR2 "$PID" # Reload config
sleep 60
sleep 60
sleep 60
sleep 45

sed -i -E 's/^cat_height=[0-9]+/cat_height=72/' "$CONFIG"
sed -i -E 's/^overlay_height=[0-9]+/overlay_height=128/' "$CONFIG"

echo "[TEST] Change animation sprite"
echo "[INFO] Set animation_name..."
sed -i -E 's/^animation_name=.*/animation_name=pkmn:bulbasaur/' "$CONFIG"
sed -i -E 's/^evolution=.*/evolution=normal/' "$CONFIG"
sed -i -E 's/^evolution_speed_factor=.*/evolution_speed_factor=3600.0/' "$CONFIG"
echo "[INFO] Send SIGUSR2"
kill -USR2 "$PID" # Reload config
sleep 35

sed -i -E 's/^cat_height=[0-9]+/cat_height=96/' "$CONFIG"
sed -i -E 's/^overlay_height=[0-9]+/overlay_height=128/' "$CONFIG"

echo "[TEST] Change animation sprite"
echo "[INFO] Set animation_name..."
sed -i -E 's/^animation_name=.*/animation_name=pmd:charmander/' "$CONFIG"
sed -i -E 's/^evolution=.*/evolution=normal/' "$CONFIG"
sed -i -E 's/^evolution_speed_factor=.*/evolution_speed_factor=3600.0/' "$CONFIG"
echo "[INFO] Send SIGUSR2"
kill -USR2 "$PID" # Reload config
sleep 60


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
