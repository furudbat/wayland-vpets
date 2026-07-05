#!/usr/bin/env bash

set -euo pipefail

#make debug
#PROGRAM="./cmake-build-debug-all-assets-colored-preload/bongocat"
#PROGRAM="./cmake-build-debug/bongocat-all"
PROGRAM="./cmake-build-debug-all-features/bongocat-all"
#PROGRAM="./build/bongocat-all"

WORKDIR=$(mktemp -d)
CONFIG="$WORKDIR/test.bongocat.conf"  # config file to modify
OG_CONFIG=./examples/test/test3.bongocat.conf
cp $OG_CONFIG $CONFIG

sed -i -E 's/^cat_height=[0-9]+/cat_height=256/' "$CONFIG"
sed -i -E 's/^overlay_height=[0-9]+/overlay_height=256/' "$CONFIG"

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

echo "[TEST] Change offset_y"
echo "[INFO] Set Sprite Sheet: pkmn:charmander"
sed -i -E 's/^enable_antialiasing=[0-9]+/enable_antialiasing=0/' "$CONFIG"
sed -i -E 's/^invert_color=[0-9]+/invert_color=0/' "$CONFIG"
sed -i -E 's/^animation_name=.*/animation_name=pkmn:charmander/' "$CONFIG"
sed -i -E 's/^evolution=.*/evolution=normal/' "$CONFIG"
sed -i -E 's/^evolution_speed_factor=.*/evolution_speed_factor=3700.0/' "$CONFIG"
sed -i -E 's/^animation_speed=[0-9]+/animation_speed=600/' "$CONFIG"
echo "[INFO] Send SIGUSR2"
kill -USR2 "$PID" # Reload config
sleep 2
sleep 20

echo "[INFO] Set Sprite Sheet: dmx:Agumon X"
sed -i -E 's/^enable_antialiasing=[0-9]+/enable_antialiasing=0/' "$CONFIG"
sed -i -E 's/^invert_color=[0-9]+/invert_color=1/' "$CONFIG"
sed -i -E 's/^animation_name=.*/animation_name=dmx:Agumon X/' "$CONFIG"
sed -i -E 's/^evolution=.*/evolution=normal/' "$CONFIG"
sed -i -E 's/^evolution_speed_factor=.*/evolution_speed_factor=3800.0/' "$CONFIG"
sed -i -E 's/^animation_speed=[0-9]+/animation_speed=800/' "$CONFIG"
echo "[INFO] Send SIGUSR2"
kill -USR2 "$PID" # Reload config
sleep 2
sleep 80

echo "[INFO] Set Sprite Sheet: dm20:Botamon"
sed -i -E 's/^enable_antialiasing=[0-9]+/enable_antialiasing=0/' "$CONFIG"
sed -i -E 's/^invert_color=[0-9]+/invert_color=1/' "$CONFIG"
sed -i -E 's/^animation_name=.*/animation_name=dm20:Botamon/' "$CONFIG"
sed -i -E 's/^evolution=.*/evolution=normal/' "$CONFIG"
sed -i -E 's/^evolution_speed_factor=.*/evolution_speed_factor=3600.0/' "$CONFIG"
sed -i -E 's/^animation_speed=[0-9]+/animation_speed=900/' "$CONFIG"
echo "[INFO] Send SIGUSR2"
kill -USR2 "$PID" # Reload config
sleep 2
sleep 120

echo "[INFO] Set Sprite Sheet: pen20:Agumon"
sed -i -E 's/^enable_antialiasing=[0-9]+/enable_antialiasing=0/' "$CONFIG"
sed -i -E 's/^invert_color=[0-9]+/invert_color=1/' "$CONFIG"
sed -i -E 's/^animation_name=.*/animation_name=pen20:Agumon/' "$CONFIG"
sed -i -E 's/^evolution=.*/evolution=normal/' "$CONFIG"
sed -i -E 's/^evolution_speed_factor=.*/evolution_speed_factor=3600.0/' "$CONFIG"
sed -i -E 's/^animation_speed=[0-9]+/animation_speed=1000/' "$CONFIG"
echo "[INFO] Send SIGUSR2"
kill -USR2 "$PID" # Reload config
sleep 2
sleep 180

echo "[INFO] Set Sprite Sheet: dmc:Elecmon"
sed -i -E 's/^enable_antialiasing=[0-9]+/enable_antialiasing=0/' "$CONFIG"
sed -i -E 's/^invert_color=[0-9]+/invert_color=0/' "$CONFIG"
sed -i -E 's/^animation_name=.*/animation_name=dmc:Elecmon/' "$CONFIG"
sed -i -E 's/^evolution=.*/evolution=normal/' "$CONFIG"
sed -i -E 's/^evolution_speed_factor=.*/evolution_speed_factor=3600.0/' "$CONFIG"
sed -i -E 's/^animation_speed=[0-9]+/animation_speed=800/' "$CONFIG"
echo "[INFO] Send SIGUSR2"
kill -USR2 "$PID" # Reload config
sleep 2
sleep 90

echo "[INFO] Set Sprite Sheet: dm:Gabumon"
sed -i -E 's/^enable_antialiasing=[0-9]+/enable_antialiasing=0/' "$CONFIG"
sed -i -E 's/^invert_color=[0-9]+/invert_color=1/' "$CONFIG"
sed -i -E 's/^animation_name=.*/animation_name=dm:Gabumon/' "$CONFIG"
sed -i -E 's/^evolution=.*/evolution=normal/' "$CONFIG"
sed -i -E 's/^evolution_speed_factor=.*/evolution_speed_factor=3600.0/' "$CONFIG"
sed -i -E 's/^animation_speed=[0-9]+/animation_speed=1000/' "$CONFIG"
echo "[INFO] Send SIGUSR2"
kill -USR2 "$PID" # Reload config
sleep 2
sleep 120

echo "[INFO] Set Sprite Sheet: Koromon"
sed -i -E 's/^enable_antialiasing=[0-9]+/enable_antialiasing=0/' "$CONFIG"
sed -i -E 's/^invert_color=[0-9]+/invert_color=0/' "$CONFIG"
sed -i -E 's/^animation_name=.*/animation_name=Koromon/' "$CONFIG"
sed -i -E 's/^evolution=.*/evolution=normal/' "$CONFIG"
sed -i -E 's/^evolution_speed_factor=.*/evolution_speed_factor=3600.0/' "$CONFIG"
sed -i -E 's/^animation_speed=[0-9]+/animation_speed=900/' "$CONFIG"
echo "[INFO] Send SIGUSR2"
kill -USR2 "$PID" # Reload config
sleep 2
sleep 160

echo "[INFO] Set Sprite Sheet: Clippy"
sed -i -E 's/^enable_antialiasing=[0-9]+/enable_antialiasing=1/' "$CONFIG"
sed -i -E 's/^invert_color=[0-9]+/invert_color=0/' "$CONFIG"
sed -i -E 's/^animation_name=.*/animation_name=Clippy/' "$CONFIG"
sed -i -E 's/^evolution=.*/evolution=normal/' "$CONFIG"
sed -i -E 's/^evolution_speed_factor=.*/evolution_speed_factor=3600.0/' "$CONFIG"
sed -i -E 's/^animation_speed=[0-9]+/animation_speed=200/' "$CONFIG"
echo "[INFO] Send SIGUSR2"
kill -USR2 "$PID" # Reload config
sleep 5
sleep 20

echo "[INFO] Set Sprite Sheet: neko"
sed -i -E 's/^enable_antialiasing=[0-9]+/enable_antialiasing=0/' "$CONFIG"
sed -i -E 's/^invert_color=[0-9]+/invert_color=0/' "$CONFIG"
sed -i -E 's/^animation_name=.*/animation_name=neko/' "$CONFIG"
sed -i -E 's/^evolution=.*/evolution=normal/' "$CONFIG"
sed -i -E 's/^evolution_speed_factor=.*/evolution_speed_factor=3600.0/' "$CONFIG"
sed -i -E 's/^animation_speed=[0-9]+/animation_speed=600/' "$CONFIG"
echo "[INFO] Send SIGUSR2"
kill -USR2 "$PID" # Reload config
sleep 5
sleep 15

echo "[INFO] Set Sprite Sheet: pmd:pikachu"
sed -i -E 's/^enable_antialiasing=[0-9]+/enable_antialiasing=0/' "$CONFIG"
sed -i -E 's/^invert_color=[0-9]+/invert_color=0/' "$CONFIG"
sed -i -E 's/^animation_name=.*/animation_name=pmd:Pikachu/' "$CONFIG"
sed -i -E 's/^evolution=.*/evolution=normal/' "$CONFIG"
sed -i -E 's/^evolution_speed_factor=.*/evolution_speed_factor=3600.0/' "$CONFIG"
sed -i -E 's/^animation_speed=[0-9]+/animation_speed=500/' "$CONFIG"
echo "[INFO] Send SIGUSR2"
kill -USR2 "$PID" # Reload config
sleep 2
sleep 20

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
