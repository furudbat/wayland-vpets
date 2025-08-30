#!/usr/bin/env bash
set -euo pipefail

#make debug
#PROGRAM="./cmake-build-debug-all-assets-colored-preload/bongocat"
#PROGRAM="./cmake-build-debug/bongocat"
PROGRAM="./build/bongocat"

WORKDIR=$(mktemp -d)
CONFIG="$WORKDIR/test.bongocat.conf"  # config file to modify
OG_CONFIG=./examples/digimon.bongocat.conf
cp ./examples/digimon.bongocat.conf $CONFIG

if [[ $# -ge 1 ]]; then
    PID="$1"
    CONFIG="$2"
    cp $CONFIG "${CONFIG}.bak"
    OG_CONFIG="${CONFIG}.bak"
    echo "[TEST] Using provided PID = $PID"
else
    echo "[TEST] Starting program..."
    "$PROGRAM" --watch-config --config "$CONFIG" &
    PID=$!
    echo "[TEST] Program PID = $PID"
    sleep 20
fi

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
sleep 5
echo "[INFO] Send SIGUSR2"
kill -USR2 "$PID"
sleep 10
echo "[INFO] Spam SIGUSR2"
kill -USR2 "$PID"
kill -USR2 "$PID"
kill -USR2 "$PID"
kill -USR2 "$PID"
sleep 15

# --- function to toggle idle_sleep_timeout ---
toggle_config() {
    if grep -q '^idle_sleep_timeout=10' "$CONFIG"; then
        new=3600
    else
        new=10
    fi
    echo "[TEST] Setting idle_sleep_timeout=$new"
    #sed -i -E "s/^idle_sleep_timeout=[0-9]+/idle_sleep_timeout=$new/" "$CONFIG"
}

# --- modify config to trigger hot reload ---
sed -i 's/^enable_scheduled_sleep=1/enable_scheduled_sleep=0/' "$CONFIG"
sleep 5
toggle_config
sleep 15
toggle_config
sleep 15
echo "[TEST] Trigger Sleep"
echo "[INFO] Enable idle_sleep_timeout..."
sed -i -E "s/^idle_sleep_timeout=[0-9]+/idle_sleep_timeout=10/" "$CONFIG"
sleep 5
sed -i 's/^enable_scheduled_sleep=0/enable_scheduled_sleep=1/' "$CONFIG"
sleep 20
echo "[TEST] Wake up Sleep"
printf '\e' > /proc/$PID/fd/0
sleep 5
echo "[INFO] Disable idle_sleep_timeout..."
sed -i -E "s/^idle_sleep_timeout=[0-9]+/idle_sleep_timeout=3600/" "$CONFIG"
sleep 5
sed -i 's/^enable_scheduled_sleep=1/enable_scheduled_sleep=0/' "$CONFIG"
sleep 5
echo "[TEST] Change animation sprite"
echo "[INFO] Set animation_name..."
sed -i -E 's/^animation_name=[A-Za-z_]+/animation_name=agumon/' "$CONFIG"
sleep 5
echo "[INFO] Set animation_name..."
sed -i -E 's/^animation_name=[A-Za-z_]+/animation_name=greymon/' "$CONFIG"
sleep 1

echo "[TEST] move and delete config..."
echo "[INFO] Move Config: $CONFIG > ${CONFIG}.del"
mv $CONFIG "${CONFIG}.del"
sleep 5
rm "${CONFIG}.del"
sleep 5
echo "[INFO] Recreate Config: $CONFIG"
cp ./examples/digimon.bongocat.conf $CONFIG
sleep 10
echo "[INFO] Delete Config: $CONFIG"
rm $CONFIG
sleep 10
echo "[INFO] Recreate Config: $CONFIG"
cp ./examples/digimon.bongocat.conf $CONFIG
sleep 5

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
sleep 5

echo "[TEST] Sending SIGUSR2..."
echo "[INFO] Send SIGUSR2"
kill -USR2 "$PID"
sleep 5
echo "[INFO] Send SIGUSR2"
kill -USR2 "$PID"
sleep 10
echo "[INFO] Spam SIGUSR2"
kill -USR2 "$PID"
kill -USR2 "$PID"
kill -USR2 "$PID"
kill -USR2 "$PID"
sleep 15
echo "[INFO] Spam SIGUSR2 slower"
kill -USR2 "$PID"
sleep 5
kill -USR2 "$PID"
sleep 3
kill -USR2 "$PID"
sleep 2
kill -USR2 "$PID"
sleep 10


echo "[TEST] replace config..."
echo "[INFO] Replace Config: $CONFIG > ${CONFIG}.del"
cp ./examples/idle-only-digimon.bongocat.conf $CONFIG
sleep 10
echo "[TEST] Sending ESC key..."
echo "[INFO] Send stdin"
printf '\e' > /proc/$PID/fd/0
sleep 2
printf '\e' > /proc/$PID/fd/0
sleep 2
printf '\e' > /proc/$PID/fd/0
sleep 5
echo "[INFO] Restore old config"
cp $OG_CONFIG $CONFIG
sleep 5

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
sleep 15

echo "[INFO] Wait for TERM"
# wait up to 5 seconds
for i in {1..10}; do
    if ! kill -0 "$PID" 2>/dev/null; then
        break
    fi
    sleep 1
done

# --- verify not running ---
if kill -0 "$PID" 2>/dev/null; then
    echo "[FAIL] Process $PID still running!"
    exit 1
else
    echo "[PASS] Process terminated successfully"
fi
