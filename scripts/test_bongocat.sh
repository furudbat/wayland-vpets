#!/usr/bin/env bash
set -euo pipefail

#PROGRAM="./cmake-build-debug-all-assets-colored-preload/bongocat"
#PROGRAM="./cmake-build-debug/bongocat"
PROGRAM="./build/bongocat"

WORKDIR=$(mktemp -d)
CONFIG="$WORKDIR/test.bongocat.conf"  # config file to modify
cp ./examples/digimon.bongocat.conf $CONFIG

# --- start program ---
echo "[TEST] Starting program..."
$PROGRAM --watch-config --config $CONFIG &
PID=$!
echo "[TEST] Program PID = $PID"
sleep 20

# --- trap cleanup ---
cleanup() {
    echo "[TEST] Cleaning up..."
    kill -9 "$PID" 2>/dev/null || true
    rm -rf "$WORKDIR"
}
trap cleanup EXIT

# --- function to toggle idle_sleep_timeout ---
toggle_config() {
    if grep -q '^idle_sleep_timeout=10' "$CONFIG"; then
        new=3600
    else
        new=10
    fi
    echo "[TEST] Setting idle_sleep_timeout=$new"
    sed -i -E "s/^idle_sleep_timeout=[0-9]+/idle_sleep_timeout=$new/" "$CONFIG"
}

# --- modify config to trigger hot reload ---
sed -i 's/^enable_scheduled_sleep=1/enable_scheduled_sleep=0/' "$CONFIG"
sleep 5
toggle_config
sleep 15
toggle_config
sleep 15
echo "[TEST] Trigger Sleep"
sed -i -E "s/^idle_sleep_timeout=[0-9]+/idle_sleep_timeout=10/" "$CONFIG"
sed -i 's/^enable_scheduled_sleep=0/enable_scheduled_sleep=1/' "$CONFIG"
sleep 20
echo "[TEST] Wake up Sleep"
printf '\e' > /proc/$PID/fd/0
sleep 5
sed -i 's/^enable_scheduled_sleep=1/enable_scheduled_sleep=0/' "$CONFIG"
sed -i -E "s/^idle_sleep_timeout=[0-9]+/idle_sleep_timeout=3600/" "$CONFIG"
sleep 5
echo "[TEST] Change animation sprite"
sed -i -E 's/^animation_name=[A-Za-z_]+/animation_name=agumon/' "$CONFIG"
sleep 5
sed -i -E 's/^animation_name=[A-Za-z_]+/animation_name=greymon/' "$CONFIG"
sleep 1

echo "[TEST] move and delete config..."
cp $CONFIG "${CONFIG}.bak"
mv $CONFIG "${CONFIG}.del"
sleep 5
rm "${CONFIG}.del"
rm "${CONFIG}.bak"
sleep 5
cp ./examples/digimon.bongocat.conf $CONFIG
sleep 10
rm $CONFIG
sleep 10
cp ./examples/digimon.bongocat.conf $CONFIG
sleep 5

# --- simulate pressing ESC ---
echo "[TEST] Sending ESC key..."
# Example if stdin is used:
printf '\e' > /proc/$PID/fd/0
sleep 5
printf '\e' > /proc/$PID/fd/0
sleep 1
# a bit of a spam
printf '\e' > /proc/$PID/fd/0
printf '\e' > /proc/$PID/fd/0
printf '\e' > /proc/$PID/fd/0
printf '\e' > /proc/$PID/fd/0
sleep 5
printf '\e' > /proc/$PID/fd/0
sleep 1
printf '\e' > /proc/$PID/fd/0
sleep 1
printf '\e' > /proc/$PID/fd/0
sleep 1
printf '\e' > /proc/$PID/fd/0
sleep 5

echo "[TEST] Sending SIGUSR2..."
kill -USR2 "$PID"
sleep 5
kill -USR2 "$PID"
sleep 10
# a bit of a spam
kill -USR2 "$PID"
kill -USR2 "$PID"
kill -USR2 "$PID"
kill -USR2 "$PID"
sleep 15

# --- verify not running ---
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

# wait up to 5 seconds
for i in {1..5}; do
    if ! kill -0 "$PID" 2>/dev/null; then
        break
    fi
    sleep 1
done

# if still alive, force kill
if kill -0 "$PID" 2>/dev/null; then
    echo "[TEST] SIGTERM timed out, killing..."
    exit 1
fi

echo "[TEST] Program exited with code $EXIT_CODE"

# --- verify not running ---
if kill -0 "$PID" 2>/dev/null; then
    echo "[FAIL] Process $PID still running!"
    exit 1
else
    echo "[PASS] Process terminated successfully"
fi
