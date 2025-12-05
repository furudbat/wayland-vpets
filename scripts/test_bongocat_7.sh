#!/usr/bin/env bash

set -euo pipefail

#make debug
#PROGRAM="./cmake-build-debug-all-assets-colored-preload/bongocat"
PROGRAM="./cmake-build-debug-all-assets-preload/bongocat-all"
#PROGRAM="./build/bongocat-all"

WORKDIR=$(mktemp -d)
CONFIG="$WORKDIR/test.bongocat.conf"  # config file to modify
OG_CONFIG=./examples/test.bongocat.conf
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

echo "[TEST] Load biggest assets"
echo "[INFO] Set Sprite Sheet: Links"
sed -i -E 's/^invert_color=[0-9]+/invert_color=0/' "$CONFIG"
sed -i -E 's/^animation_name=.*/animation_name=Links/' "$CONFIG"
echo "[INFO] Send SIGUSR2"
kill -USR2 "$PID" # Reload config
sleep 5
echo "[INFO] Set Sprite Sheet: pkmn:dialga"
sed -i -E 's/^invert_color=[0-9]+/invert_color=0/' "$CONFIG"
sed -i -E 's/^animation_name=.*/animation_name=pkmn:dialga/' "$CONFIG"
echo "[INFO] Send SIGUSR2"
kill -USR2 "$PID" # Reload config
sleep 2
echo "[INFO] Set Sprite Sheet: dmx:Hexeblaumon"
sed -i -E 's/^invert_color=[0-9]+/invert_color=1/' "$CONFIG"
sed -i -E 's/^animation_name=.*/animation_name=dmx:Hexeblaumon/' "$CONFIG"
echo "[INFO] Send SIGUSR2"
kill -USR2 "$PID" # Reload config
sleep 2
echo "[INFO] Set Sprite Sheet: dm20:Omegamon"
sed -i -E 's/^invert_color=[0-9]+/invert_color=1/' "$CONFIG"
sed -i -E 's/^animation_name=.*/animation_name=dm20:Omegamon/' "$CONFIG"
echo "[INFO] Send SIGUSR2"
kill -USR2 "$PID" # Reload config
sleep 2
echo "[INFO] Set Sprite Sheet: pen20:Megalo Growmon"
sed -i -E 's/^invert_color=[0-9]+/invert_color=1/' "$CONFIG"
sed -i -E 's/^animation_name=.*/animation_name=pen20:Megalo Growmon/' "$CONFIG"
echo "[INFO] Send SIGUSR2"
kill -USR2 "$PID" # Reload config
sleep 2
echo "[INFO] Set Sprite Sheet: dmc:Omegamon"
sed -i -E 's/^invert_color=[0-9]+/invert_color=0/' "$CONFIG"
sed -i -E 's/^animation_name=.*/animation_name=dmc:Omegamon/' "$CONFIG"
echo "[INFO] Send SIGUSR2"
kill -USR2 "$PID" # Reload config
sleep 2
echo "[INFO] Set Sprite Sheet: dm:Coronamon"
sed -i -E 's/^invert_color=[0-9]+/invert_color=1/' "$CONFIG"
sed -i -E 's/^animation_name=.*/animation_name=dm:Coronamon/' "$CONFIG"
echo "[INFO] Send SIGUSR2"
kill -USR2 "$PID" # Reload config
sleep 2
echo "[INFO] Set Sprite Sheet: Metal Greymon"
sed -i -E 's/^invert_color=[0-9]+/invert_color=0/' "$CONFIG"
sed -i -E 's/^animation_name=.*/animation_name=Metal Greymon/' "$CONFIG"
echo "[INFO] Send SIGUSR2"
kill -USR2 "$PID" # Reload config
sleep 2
echo "[INFO] Set Sprite Sheet: neko"
sed -i -E 's/^invert_color=[0-9]+/invert_color=0/' "$CONFIG"
sed -i -E 's/^animation_name=.*/animation_name=neko/' "$CONFIG"
echo "[INFO] Send SIGUSR2"
kill -USR2 "$PID" # Reload config
sleep 5
echo "[INFO] Set Sprite Sheet: pmd:volcanion"
sed -i -E 's/^invert_color=[0-9]+/invert_color=0/' "$CONFIG"
sed -i -E 's/^animation_name=.*/animation_name=pmd:volcanion/' "$CONFIG"
echo "[INFO] Send SIGUSR2"
kill -USR2 "$PID" # Reload config
sleep 2


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
