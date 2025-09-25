#!/usr/bin/env bash

set -euo pipefail

#make debug
#PROGRAM="./cmake-build-debug-all-assets-colored-preload/bongocat"
#PROGRAM="./cmake-build-debug/bongocat"
#PROGRAM="./build/bongocat-all"
PROGRAM="./cmake-build-release-all-assets-multi/bongocat-all"

WORKDIR=$(mktemp -d)
CONFIG="$WORKDIR/test.bongocat.conf"  # config file to modify
OG_CONFIG=./examples/test.bongocat.conf
cp $OG_CONFIG $CONFIG

# pre config
echo "[INFO] Set Sprite Sheet: pkmn:Charizard"
sed -i 's/^enable_scheduled_sleep=1/enable_scheduled_sleep=0/' "$CONFIG"
sed -i -E 's/^animation_name=[:A-Za-z0-9_. ]+/animation_name=pkmn:Charizard/' "$CONFIG"
sed -i -E 's/^cat_x_offset=[0-9]+/cat_x_offset=165/' "$CONFIG"
sed -i -E 's/^cat_y_offset=[0-9]+/cat_y_offset=0/' "$CONFIG"
sed -i -E 's/^cat_align=[a-zA-Z]+/cat_align=right/' "$CONFIG"
sed -i -E 's/^cat_height=[0-9]+/cat_height=64/' "$CONFIG"
sed -i -E 's/^overlay_height=[0-9]+/overlay_height=128/' "$CONFIG"
sed -i -E 's/^idle_animation=[0-9]+/idle_animation=1/' "$CONFIG"
sed -i -E 's/^animation_speed=[0-9]+/animation_speed=893/' "$CONFIG"
sed -i -E 's/^fps=[0-9]+/fps=60/' "$CONFIG"
sed -i -E 's/^input_fps=[0-9]+/input_fps=60/' "$CONFIG"
sed -i -E 's/^overlay_opacity=[0-9]+/overlay_opacity=0/' "$CONFIG"

#cat "$CONFIG"
#sleep 10
#clear

RECORD_FILE="assets/test-output.mp4"
REGION="4155,1296 270x130"
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
sleep 7

# Test 0
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
sleep 3



# Test 1
echo "[INFO] Set Sprite Sheet: dmc:Agumon"
sed -i -E 's/^invert_color=[0-9]+/invert_color=0/' "$CONFIG"
sed -i -E 's/^animation_name=[:A-Za-z0-9_. ]+/animation_name=dmc:Agumon/' "$CONFIG"
sed -i -E 's/^cat_x_offset=[0-9]+/cat_x_offset=165/' "$CONFIG"
sed -i -E 's/^cat_y_offset=[0-9]+/cat_y_offset=5/' "$CONFIG"
sed -i -E 's/^cat_align=[a-zA-Z]+/cat_align=right/' "$CONFIG"
sed -i -E 's/^cat_height=[0-9]+/cat_height=64/' "$CONFIG"
sed -i -E 's/^overlay_height=[0-9]+/overlay_height=128/' "$CONFIG"
kill -USR2 "$PID"
sleep 2
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
sleep 5

# Test 2
echo "[INFO] Set Sprite Sheet: bongocat"
sed -i -E 's/^invert_color=[0-9]+/invert_color=0/' "$CONFIG"
sed -i -E 's/^animation_name=[:A-Za-z0-9_. ]+/animation_name=bongocat/' "$CONFIG"
sed -i -E 's/^cat_x_offset=[0-9]+/cat_x_offset=155/' "$CONFIG"
sed -i -E 's/^cat_y_offset=[0-9]+/cat_y_offset=15/' "$CONFIG"
sed -i -E 's/^cat_align=[a-zA-Z]+/cat_align=right/' "$CONFIG"
sed -i -E 's/^cat_height=[0-9]+/cat_height=64/' "$CONFIG"
sed -i -E 's/^idle_animation=[0-9]+/idle_animation=0/' "$CONFIG"
sed -i -E 's/^overlay_height=[0-9]+/overlay_height=128/' "$CONFIG"
kill -USR2 "$PID"
sleep 2
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
sleep 3

# Test 3
echo "[INFO] Set Sprite Sheet: dm20:Agumon"
sed -i -E 's/^invert_color=[0-9]+/invert_color=1/' "$CONFIG"
sed -i -E 's/^animation_name=[:A-Za-z0-9_. ]+/animation_name=dm20:Agumon/' "$CONFIG"
sed -i -E 's/^cat_x_offset=[0-9]+/cat_x_offset=165/' "$CONFIG"
sed -i -E 's/^cat_y_offset=[0-9]+/cat_y_offset=5/' "$CONFIG"
sed -i -E 's/^cat_align=[a-zA-Z]+/cat_align=right/' "$CONFIG"
sed -i -E 's/^cat_height=[0-9]+/cat_height=64/' "$CONFIG"
sed -i -E 's/^idle_animation=[0-9]+/idle_animation=1/' "$CONFIG"
sed -i -E 's/^overlay_height=[0-9]+/overlay_height=128/' "$CONFIG"
kill -USR2 "$PID"
sleep 2
if [[ -f "/proc/$PID/fd/0" ]]; then
  printf '\e' > /proc/$PID/fd/0
  sleep 1
  printf '\e' > /proc/$PID/fd/0
  sleep 1
  printf '\e' > /proc/$PID/fd/0
  sleep 1
fi
sleep 3

# Test 3
echo "[INFO] Set Sprite Sheet: dmc:Greymon"
sed -i -E 's/^invert_color=[0-9]+/invert_color=0/' "$CONFIG"
sed -i -E 's/^animation_name=[:A-Za-z0-9_. ]+/animation_name=dmc:Greymon/' "$CONFIG"
sed -i -E 's/^cat_x_offset=[0-9]+/cat_x_offset=165/' "$CONFIG"
sed -i -E 's/^cat_y_offset=[0-9]+/cat_y_offset=5/' "$CONFIG"
sed -i -E 's/^cat_align=[a-zA-Z]+/cat_align=right/' "$CONFIG"
sed -i -E 's/^cat_height=[0-9]+/cat_height=64/' "$CONFIG"
sed -i -E 's/^idle_animation=[0-9]+/idle_animation=0/' "$CONFIG"
sed -i -E 's/^overlay_height=[0-9]+/overlay_height=128/' "$CONFIG"
kill -USR2 "$PID"
sleep 1
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
sleep 5


# Test 4
echo "[INFO] Set Sprite Sheet: Clippy"
sed -i -E 's/^invert_color=[0-9]+/invert_color=0/' "$CONFIG"
sed -i -E 's/^animation_name=[:A-Za-z0-9_. ]+/animation_name=Clippy/' "$CONFIG"
sed -i -E 's/^cat_x_offset=[0-9]+/cat_x_offset=56/' "$CONFIG"
sed -i -E 's/^cat_y_offset=[0-9]+/cat_y_offset=-20/' "$CONFIG"
sed -i -E 's/^cat_align=[a-zA-Z]+/cat_align=right/' "$CONFIG"
sed -i -E 's/^cat_height=[0-9]+/cat_height=96/' "$CONFIG"
sed -i -E 's/^overlay_height=[0-9]+/overlay_height=128/' "$CONFIG"
sed -i -E 's/^idle_animation=[0-9]+/idle_animation=0/' "$CONFIG"
sed -i -E 's/^fps=[0-9]+/fps=20/' "$CONFIG"
sed -i -E 's/^animation_speed=[0-9]+/animation_speed=50/' "$CONFIG"
kill -USR2 "$PID"
sleep 2
if [[ -f "/proc/$PID/fd/0" ]]; then
  printf '\e' > /proc/$PID/fd/0
  sleep 1
fi
sleep 7

# Test 4
echo "[INFO] Set Sprite Sheet: Links"
sed -i -E 's/^invert_color=[0-9]+/invert_color=0/' "$CONFIG"
sed -i -E 's/^animation_name=[:A-Za-z0-9_. ]+/animation_name=Links/' "$CONFIG"
sed -i -E 's/^cat_x_offset=[0-9]+/cat_x_offset=56/' "$CONFIG"
sed -i -E 's/^cat_y_offset=[0-9]+/cat_y_offset=-20/' "$CONFIG"
sed -i -E 's/^cat_align=[a-zA-Z]+/cat_align=right/' "$CONFIG"
sed -i -E 's/^cat_height=[0-9]+/cat_height=96/' "$CONFIG"
sed -i -E 's/^overlay_height=[0-9]+/overlay_height=128/' "$CONFIG"
sed -i -E 's/^idle_animation=[0-9]+/idle_animation=0/' "$CONFIG"
sed -i -E 's/^fps=[0-9]+/fps=15/' "$CONFIG"
sed -i -E 's/^animation_speed=[0-9]+/animation_speed=66/' "$CONFIG"
kill -USR2 "$PID"
sleep 2
if [[ -f "/proc/$PID/fd/0" ]]; then
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
RECORD_FILE_2="assets/test-demo.gif"
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
