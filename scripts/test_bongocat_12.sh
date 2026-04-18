#!/usr/bin/env bash

set -euo pipefail

#make debug
#PROGRAM="./cmake-build-debug-all-assets-colored-preload/bongocat"
PROGRAM="./cmake-build-debug/bongocat-all"
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

# --- function to toggle idle_sleep_timeout ---
toggle_config() {
    if grep -q '^idle_sleep_timeout=10' "$CONFIG"; then
        new=3600
    else
        new=10
    fi
    sed -i -E "s/^idle_sleep_timeout=[0-9]+/idle_sleep_timeout=$new/" "$CONFIG"
    echo "[TEST] Setting idle_sleep_timeout=$new"
}

sed -i -E 's/^overlay_position=[a-zA-Z]+/overlay_position=top/' "$CONFIG"
sed -i -E 's/^overlay_opacity=[0-9]+/overlay_opacity=128/' "$CONFIG"
sed -i -E 's/^cat_x_offset=[0-9]+/cat_x_offset=0/' "$CONFIG"
sed -i -E 's/^cat_y_offset=[0-9]+/cat_y_offset=0/' "$CONFIG"
sed -i -E 's/^cat_align=[a-zA-Z]+/cat_align=center/' "$CONFIG"
sed -i -E 's/^enable_antialiasing=[0-9]+/enable_antialiasing=1/' "$CONFIG"
sed -i -E 's/^cat_height=[0-9]+/cat_height=60/' "$CONFIG"
sed -i -E 's/^overlay_height=[0-9]+/overlay_height=80/' "$CONFIG"

# Test Sleep
sed -i -E 's/^cpu_threshold=[0-9]+/cpu_threshold=0/' "$CONFIG"
sed -i 's/^enable_scheduled_sleep=1/enable_scheduled_sleep=0/' "$CONFIG"
sed -i -E 's/^animation_name=.*/animation_name=bongocat/' "$CONFIG"
sleep 3
toggle_config
sleep 10
toggle_config
sleep 10
echo "[TEST] Trigger Sleep"
echo "[INFO] Enable idle_sleep_timeout..."
sed -i -E "s/^idle_sleep_timeout=[0-9]+/idle_sleep_timeout=10/" "$CONFIG"
sleep 5
sed -i 's/^enable_scheduled_sleep=0/enable_scheduled_sleep=1/' "$CONFIG"
echo "[INFO] Send SIGUSR2"
kill -USR2 "$PID" # Reload config
sleep 20
echo "[TEST] Wake up Sleep"
if [[ -f "/proc/$PID/fd/0" ]]; then
  printf '\e' > /proc/$PID/fd/0
  sleep 5
fi
echo "[INFO] Disable idle_sleep_timeout..."
sed -i -E "s/^idle_sleep_timeout=[0-9]+/idle_sleep_timeout=3600/" "$CONFIG"
echo "[INFO] Send SIGUSR2"
kill -USR2 "$PID" # Reload config
sleep 5
sed -i 's/^enable_scheduled_sleep=1/enable_scheduled_sleep=0/' "$CONFIG"
echo "[INFO] Send SIGUSR2"
kill -USR2 "$PID" # Reload config
sleep 5

echo "[INFO] Disable sleep"
sed -i 's/^enable_scheduled_sleep=1/enable_scheduled_sleep=0/' "$CONFIG"
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

echo "[INFO] Disable sleep"
sed -i -E 's/^enable_antialiasing=[0-9]+/enable_antialiasing=0/' "$CONFIG"
sed -i 's/^enable_scheduled_sleep=1/enable_scheduled_sleep=0/' "$CONFIG"
sed -i -E 's/^animation_name=.*/animation_name=bongocat/' "$CONFIG"
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
sleep 10
echo "[INFO] Spam SIGUSR2 slower"
kill -USR2 "$PID"
sleep 5
kill -USR2 "$PID"
sleep 3
kill -USR2 "$PID"
sleep 2
kill -USR2 "$PID"
sleep 15

echo "[TEST] Sending SIGUSR1..."
echo "[INFO] Send SIGUSR1"
kill -USR1 "$PID"
sleep 2
echo "[INFO] Send SIGUSR1"
kill -USR1 "$PID"
sleep 2

# Test Sleep + reload in middle
sed -i -E 's/^enable_antialiasing=[0-9]+/enable_antialiasing=0/' "$CONFIG"
sed -i -E 's/^invert_color=[0-9]+/invert_color=0/' "$CONFIG"
sed -i -E 's/^animation_name=.*/animation_name=bongocat/' "$CONFIG"
echo "[TEST] Trigger Sleep"
echo "[INFO] Enable idle_sleep_timeout..."
sed -i -E "s/^idle_sleep_timeout=[0-9]+/idle_sleep_timeout=10/" "$CONFIG"
sed -i 's/^enable_scheduled_sleep=0/enable_scheduled_sleep=1/' "$CONFIG"
echo "[INFO] Send SIGUSR2"
kill -USR2 "$PID" # Reload config
sleep 25
echo "[TEST] Reload config while sleeping Sleep"
sed -i -E 's/^invert_color=[0-9]+/invert_color=0/' "$CONFIG"
sed -i -E 's/^animation_name=.*/animation_name=bongocat/' "$CONFIG"
echo "[INFO] Send SIGUSR2"
kill -USR2 "$PID" # Reload config
sleep 5
echo "[INFO] Disable idle_sleep_timeout..."
sed -i -E "s/^idle_sleep_timeout=[0-9]+/idle_sleep_timeout=3600/" "$CONFIG"
sed -i 's/^enable_scheduled_sleep=1/enable_scheduled_sleep=0/' "$CONFIG"
echo "[INFO] Send SIGUSR2"
kill -USR2 "$PID" # Reload config
sleep 5

echo "[TEST] Scale Height"
sed -i -E 's/^invert_color=[0-9]+/invert_color=0/' "$CONFIG"
sed -i -E 's/^animation_name=.*/animation_name=bongocat/' "$CONFIG"
echo "[INFO] Normal height..."
sed -i -E "s/^cat_height=[0-9]+/cat_height=500/" "$CONFIG"
sed -i -E "s/^overlay_height=[0-9]+/overlay_height=500/" "$CONFIG"
echo "[INFO] Send SIGUSR2"
kill -USR2 "$PID" # Reload config
sleep 5
echo "[INFO] Big height..."
sed -i -E "s/^cat_height=[0-9]+/cat_height=1080/" "$CONFIG"
sed -i -E "s/^overlay_height=[0-9]+/overlay_height=1080/" "$CONFIG"
echo "[INFO] Send SIGUSR2"
kill -USR2 "$PID" # Reload config
sleep 10
echo "[INFO] Small height..."
sed -i -E "s/^cat_height=[0-9]+/cat_height=32/" "$CONFIG"
sed -i -E "s/^overlay_height=[0-9]+/overlay_height=32/" "$CONFIG"
echo "[INFO] Send SIGUSR2"
kill -USR2 "$PID" # Reload config
sleep 5


echo "[TEST] Set Position"
echo "[INFO] Top Position..."
sed -i -E "s/^overlay_position=[a-zA-Z]+/overlay_position=top/" "$CONFIG"
echo "[INFO] Send SIGUSR2"
kill -USR2 "$PID" # Reload config
sleep 10
echo "[INFO] Bottom Position..."
sed -i -E "s/^overlay_position=[a-zA-Z]+/overlay_position=bottom/" "$CONFIG"
echo "[INFO] Send SIGUSR2"
kill -USR2 "$PID" # Reload config
echo "[INFO] Top Position..."
sed -i -E "s/^overlay_position=[a-zA-Z]+/overlay_position=top/" "$CONFIG"
echo "[INFO] Send SIGUSR2"
kill -USR2 "$PID" # Reload config
sleep 10

echo "[TEST] Set Layer"
echo "[INFO] Top Layer..."
sed -i -E "s/^overlay_position=[a-zA-Z]+/overlay_position=bottom/" "$CONFIG"
sed -i -E "s/^overlay_layer=[a-zA-Z]+/overlay_layer=top/" "$CONFIG"
echo "[INFO] Send SIGUSR2"
kill -USR2 "$PID" # Reload config
sleep 10
echo "[INFO] Bottom Layer..."
sed -i -E "s/^overlay_layer=[a-zA-Z]+/overlay_layer=bottom/" "$CONFIG"
echo "[INFO] Send SIGUSR2"
kill -USR2 "$PID" # Reload config
sleep 5
echo "[INFO] Overlay Layer..."
sed -i -E "s/^overlay_layer=[a-zA-Z]+/overlay_layer=overlay/" "$CONFIG"
echo "[INFO] Send SIGUSR2"
kill -USR2 "$PID" # Reload config
sleep 5
echo "[INFO] Overlay Layer..."
sed -i -E "s/^overlay_position=[a-zA-Z]+/overlay_position=top/" "$CONFIG"
sed -i -E "s/^overlay_layer=[a-zA-Z]+/overlay_layer=overlay/" "$CONFIG"
echo "[INFO] Send SIGUSR2"
kill -USR2 "$PID" # Reload config
sleep 10
echo "[INFO] Background Layer..."
sed -i -E "s/^overlay_position=[a-zA-Z]+/overlay_position=bottom/" "$CONFIG"
sed -i -E "s/^overlay_layer=[a-zA-Z]+/overlay_layer=background/" "$CONFIG"
echo "[INFO] Send SIGUSR2"
kill -USR2 "$PID" # Reload config
sleep 5
echo "[INFO] Top Layer..."
sed -i -E "s/^overlay_layer=[a-zA-Z]+/overlay_layer=top/" "$CONFIG"
echo "[INFO] Send SIGUSR2"
kill -USR2 "$PID" # Reload config
sleep 5

# --- verify running ---
if kill -0 "$PID" 2>/dev/null; then
    echo "[PASS] Process $PID still running!"
else
    echo "[FAIL] Process terminated"
    exit 1
fi

# Restart - stdin config
echo "[INFO] Restart..."
echo "[INFO] Sending SIGTERM..."
kill -TERM "$PID"
sleep 15
echo "[INFO] Wait for TERM"
# wait up to 5 seconds
for i in {1..5}; do
    if ! kill -0 "$PID" 2>/dev/null; then
        break
    fi
    sleep 1
done
echo "[TEST] Start with stdin config..."
cat "$CONFIG" | "$PROGRAM" --ignore-running --strict --config - &
PID=$!
sleep 10
sed -i -E 's/^animation_name=.*/animation_name=agumon/' "$CONFIG"
sleep 5
# --- verify running ---
if kill -0 "$PID" 2>/dev/null; then
    echo "[PASS] Process $PID still running!"
else
    echo "[FAIL] Process terminated"
    exit 1
fi

# Restart - stdin default config
echo "[INFO] Restart..."
echo "[INFO] Sending SIGTERM..."
kill -TERM "$PID"
sleep 15
echo "[INFO] Wait for TERM"
# wait up to 5 seconds
for i in {1..5}; do
    if ! kill -0 "$PID" 2>/dev/null; then
        break
    fi
    sleep 1
done
echo "[TEST] Start with stdin default config..."
cat bongocat.conf.example | "$PROGRAM" --ignore-running --config - &
PID=$!
sleep 10
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
