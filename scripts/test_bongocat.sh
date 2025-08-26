#!/usr/bin/env bash
set -euo pipefail

PROGRAM="./cmake-build-debug-all-assets-preload/bongocat"          # path to your program
CONFIG="./debug.bongocat.conf"  # config file to modify
INPUT_DEV="/dev/stdin"          # replace with correct device

# --- start program ---
echo "[TEST] Starting program..."
$PROGRAM --watch-config --config $CONFIG &
PID=$!
echo "[TEST] Program PID = $PID"
sleep 20

# --- function to toggle idle_sleep_timeout ---
toggle_config() {
    if grep -q '^idle_sleep_timeout=10' "$CONFIG"; then
        echo "[TEST] Changing idle_sleep_timeout=10 → 3600"
        sed -i 's/^idle_sleep_timeout=10/idle_sleep_timeout=3600/' "$CONFIG"
    elif grep -q '^idle_sleep_timeout=[0-9]\+' "$CONFIG"; then
        echo "[TEST] Changing idle_sleep_timeout → 10"
        sed -i 's/^idle_sleep_timeout=[0-9]\+/idle_sleep_timeout=10/' "$CONFIG"
    else
        echo "[WARN] idle_sleep_timeout line not found in config"
    fi
}

# --- modify config to trigger hot reload ---
sed -i 's/^enable_scheduled_sleep=1/enable_scheduled_sleep=0/' "$CONFIG"
sleep 5
toggle_config
sleep 15
toggle_config
sleep 10
sed -i 's/^enable_scheduled_sleep=0/enable_scheduled_sleep=1/' "$CONFIG"
sleep 10
printf '\e' > /proc/$PID/fd/0
sleep 5
sed -i 's/^enable_scheduled_sleep=1/enable_scheduled_sleep=0/' "$CONFIG"
sleep 5
sed -i 's/^enable_scheduled_sleep=0/enable_scheduled_sleep=1/' "$CONFIG"
sed -i 's/^idle_sleep_timeout=[0-9]\+/idle_sleep_timeout=3600/' "$CONFIG"

# --- simulate pressing ESC ---
echo "[TEST] Sending ESC key..."
# Example if stdin is used:
printf '\e' > /proc/$PID/fd/0
# Example if /dev/input is used (requires root & evemu):
# evemu-event "$INPUT_DEV" --type EV_KEY --code KEY_ESC --value 1
# evemu-event "$INPUT_DEV" --type EV_KEY --code KEY_ESC --value 0
sleep 5
printf '\e' > /proc/$PID/fd/0
sleep 1
# a bit of a spam
printf '\e' > /proc/$PID/fd/0
printf '\e' > /proc/$PID/fd/0
printf '\e' > /proc/$PID/fd/0
printf '\e' > /proc/$PID/fd/0

echo "[TEST] Sending SIGUSR2..."
kill -USR2 "$PID"
sleep 5
kill -USR2 "$PID"
sleep 10
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
sleep 10

# --- wait and check exit status ---
if wait "$PID"; then
    EXIT_CODE=0
else
    EXIT_CODE=$?
fi

echo "[TEST] Program exited with code $EXIT_CODE"

# --- verify not running ---
if kill -0 "$PID" 2>/dev/null; then
    echo "[FAIL] Process $PID still running!"
    exit 1
else
    echo "[PASS] Process terminated successfully"
fi
