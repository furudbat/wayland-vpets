#!/usr/bin/env bash

set -euo pipefail

for group in debug relwithdebinfo; do
  find ./cmake-build-* -type f -executable -name "bongocat*" | grep -i "$group" | while read -r PROGRAM; do
    WORKDIR=$(mktemp -d)
    CONFIG="$WORKDIR/test.bongocat.conf"  # config file to modify
    OG_CONFIG=./examples/digimon.bongocat.conf
    cp $OG_CONFIG $CONFIG

    echo "[TEST] Starting program..."
    "$PROGRAM" --watch-config --config "$CONFIG" --ignore-running --strict &
    PID=$!
    echo "[TEST] Program PID = $PID"
    sleep 5

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
        echo "[TEST] Setting idle_sleep_timeout=$new"
        #sed -i -E "s/^idle_sleep_timeout=[0-9]+/idle_sleep_timeout=$new/" "$CONFIG"
    }

    # --- modify config to trigger hot reload ---
    sed -i -E 's/^cpu_threshold=[0-9]+/cpu_threshold=0/' "$CONFIG"
    sed -i 's/^enable_scheduled_sleep=1/enable_scheduled_sleep=0/' "$CONFIG"
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
    sleep 20
    echo "[TEST] Wake up Sleep"
    if [[ -f "/proc/$PID/fd/0" ]]; then
      printf '\e' > /proc/$PID/fd/0
      sleep 5
    fi
    echo "[INFO] Disable idle_sleep_timeout..."
    sed -i -E "s/^idle_sleep_timeout=[0-9]+/idle_sleep_timeout=3600/" "$CONFIG"
    sleep 5
    sed -i 's/^enable_scheduled_sleep=1/enable_scheduled_sleep=0/' "$CONFIG"
    sleep 5
    echo "[TEST] Change animation sprite"
    echo "[INFO] Set animation_name..."
    sed -i -E 's/^animation_name=[:A-Za-z_. ]+/animation_name=agumon/' "$CONFIG"
    sleep 5
    echo "[INFO] Set animation_name..."
    sed -i -E 's/^animation_name=[:A-Za-z_. ]+/animation_name=greymon/' "$CONFIG"
    sleep 1

    echo "[TEST] Invalid animation sprite"
    echo "[INFO] Set animation_name..."
    sed -i -E 's/^animation_name=[:A-Za-z_. ]+/animation_name=NoNo/' "$CONFIG"
    sleep 5
    echo "[INFO] Set animation_name..."
    sed -i -E 's/^animation_name=[:A-Za-z. ]+/animation_name=greymon/' "$CONFIG"
    sleep 1

    echo "[TEST] move and delete config..."
    echo "[INFO] Move Config: $CONFIG > ${CONFIG}.del"
    mv $CONFIG "${CONFIG}.del"
    sleep 5
    rm "${CONFIG}.del"
    sleep 5
    echo "[INFO] Recreate Config: $CONFIG"
    cp ./examples/digimon.bongocat.conf $CONFIG
    sleep 5
    echo "[INFO] Delete Config: $CONFIG"
    rm $CONFIG
    sleep 5
    echo "[INFO] Recreate Config: $CONFIG"
    cp ./examples/digimon.bongocat.conf $CONFIG
    sleep 3

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
    sed -i 's/^enable_scheduled_sleep=1/enable_scheduled_sleep=0/' "$CONFIG"
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

    echo "[TEST] replace config..."
    echo "[INFO] Replace Config: $CONFIG > ${CONFIG}.del"
    cp ./examples/idle-only-digimon.bongocat.conf $CONFIG
    sleep 5
    echo "[TEST] Sending ESC key..."
    if [[ -f "/proc/$PID/fd/0" ]]; then
      echo "[INFO] Send stdin"
      printf '\e' > /proc/$PID/fd/0
      sleep 2
      printf '\e' > /proc/$PID/fd/0
      sleep 2
      printf '\e' > /proc/$PID/fd/0
      sleep 5
    fi
    echo "[INFO] Restore old config"
    cp $OG_CONFIG $CONFIG
    sleep 5

    echo "[TEST] Change Config by other config (Digimon -> Clippy): $CONFIG"
    cp ./examples/clippy.bongocat.conf $CONFIG
    sleep 5


    echo "[TEST] Load biggest assets"
    echo "[INFO] Set Sprite Sheet: Links"
    sed -i -E 's/^invert_color=[0-9]+/invert_color=0/' "$CONFIG"
    sed -i -E 's/^animation_name=[:A-Za-z0-9_. ]+/animation_name=Links/' "$CONFIG"
    echo "[INFO] Send SIGUSR2"
    kill -USR2 "$PID" # Reload config
    sleep 2
    echo "[INFO] Set Sprite Sheet: pkmn:dialga"
    sed -i -E 's/^invert_color=[0-9]+/invert_color=0/' "$CONFIG"
    sed -i -E 's/^animation_name=[:A-Za-z0-9_. ]+/animation_name=pkmn:dialga/' "$CONFIG"
    echo "[INFO] Send SIGUSR2"
    kill -USR2 "$PID" # Reload config
    sleep 2
    echo "[INFO] Set Sprite Sheet: dmx:Hexeblaumon"
    sed -i -E 's/^invert_color=[0-9]+/invert_color=1/' "$CONFIG"
    sed -i -E 's/^animation_name=[:A-Za-z0-9_. ]+/animation_name=dmx:Hexeblaumon/' "$CONFIG"
    echo "[INFO] Send SIGUSR2"
    kill -USR2 "$PID" # Reload config
    sleep 2
    echo "[INFO] Set Sprite Sheet: dm20:Omegamon"
    sed -i -E 's/^invert_color=[0-9]+/invert_color=1/' "$CONFIG"
    sed -i -E 's/^animation_name=[:A-Za-z0-9_. ]+/animation_name=dm20:Omegamon/' "$CONFIG"
    echo "[INFO] Send SIGUSR2"
    kill -USR2 "$PID" # Reload config
    sleep 2
    echo "[INFO] Set Sprite Sheet: dmc:Omegamon"
    sed -i -E 's/^invert_color=[0-9]+/invert_color=0/' "$CONFIG"
    sed -i -E 's/^animation_name=[:A-Za-z0-9_. ]+/animation_name=dmc:Omegamon/' "$CONFIG"
    echo "[INFO] Send SIGUSR2"
    kill -USR2 "$PID" # Reload config
    sleep 2
    echo "[INFO] Set Sprite Sheet: dm:Coronamon"
    sed -i -E 's/^invert_color=[0-9]+/invert_color=1/' "$CONFIG"
    sed -i -E 's/^animation_name=[:A-Za-z0-9_. ]+/animation_name=dm:Coronamon/' "$CONFIG"
    echo "[INFO] Send SIGUSR2"
    kill -USR2 "$PID" # Reload config
    sleep 2
    echo "[INFO] Set Sprite Sheet: Metal Greymon"
    sed -i -E 's/^invert_color=[0-9]+/invert_color=0/' "$CONFIG"
    sed -i -E 's/^animation_name=[:A-Za-z0-9_. ]+/animation_name=Metal Greymon/' "$CONFIG"
    echo "[INFO] Send SIGUSR2"
    kill -USR2 "$PID" # Reload config
    sleep 5


    echo "[TEST] CPU threshold"
    echo "[INFO] Enable CPU threshold"
    sed -i -E 's/^invert_color=[0-9]+/invert_color=1/' "$CONFIG"
    sed -i -E 's/^animation_name=[:A-Za-z0-9_. ]+/animation_name=dm20:Agumon/' "$CONFIG"
    sed -i -E 's/^update_rate=[0-9]+/update_rate=1000/' "$CONFIG"
    sed -i -E 's/^cpu_threshold=[0-9]+/cpu_threshold=30/' "$CONFIG"
    echo "[INFO] Send SIGUSR2"
    kill -USR2 "$PID" # Reload config
    sleep 2
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
    echo "[INFO] Disable CPU threshold"
    sed -i -E 's/^update_rate=[0-9]+/update_rate=0/' "$CONFIG"
    sed -i -E 's/^cpu_threshold=[0-9]+/cpu_threshold=90/' "$CONFIG"
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

    # --- send SIGTERM ---
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
  done
done