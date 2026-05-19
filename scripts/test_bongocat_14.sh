#!/usr/bin/env bash

set -euo pipefail

#make debug
#PROGRAM="./cmake-build-debug-all-assets-colored-preload/bongocat"
#PROGRAM="./cmake-build-debug/bongocat"
PROGRAM="./cmake-build-relwithdebinfo-tsan/bongocat-all"
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

echo "[TEST] Sending SIGUSR1..."
echo "[INFO] Send SIGUSR1"
kill -USR1 "$PID"
sleep 2
echo "[INFO] Send SIGUSR1"
kill -USR1 "$PID"
sleep 2

for i in {1..16}; do
    kill -USR1 $PID
    kill -USR2 $PID
    sleep 0.02
    # --- verify running ---
    if kill -0 "$PID" 2>/dev/null; then
        echo "[PASS] Process $PID still running!"
    else
        echo "[FAIL] Process terminated"
        exit 1
    fi

    kill -USR1 $PID
    sleep 0.02
    kill -USR2 $PID
    sleep 0.02
    # --- verify running ---
    if kill -0 "$PID" 2>/dev/null; then
        echo "[PASS] Process $PID still running!"
    else
        echo "[FAIL] Process terminated"
        exit 1
    fi

    kill -USR2 $PID
    kill -USR2 $PID
    kill -USR2 $PID
    kill -USR2 $PID
    kill -USR2 $PID
    kill -USR2 $PID
    kill -USR2 $PID
    sleep 5
    # --- verify running ---
    if kill -0 "$PID" 2>/dev/null; then
        echo "[PASS] Process $PID still running!"
    else
        echo "[FAIL] Process terminated"
        exit 1
    fi
done
# --- verify running ---
if kill -0 "$PID" 2>/dev/null; then
    echo "[PASS] Process $PID still running!"
else
    echo "[FAIL] Process terminated"
    exit 1
fi

for i in {1..100}; do
    kill -USR1 $PID
    kill -USR2 $PID
done
# --- verify running ---
if kill -0 "$PID" 2>/dev/null; then
    echo "[PASS] Process $PID still running!"
else
    echo "[FAIL] Process terminated"
    exit 1
fi

for i in {1..5}; do
    kill -STOP $PID
    sleep 5
    kill -CONT $PID
    sleep 2
done
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


# Restart
echo "[TEST] Start mal config..."
"$PROGRAM" --ignore-running --config "$CONFIG" &
PID=$!
sleep 10
kill -USR2 $PID
kill -USR2 $PID
kill -USR2 $PID
kill -USR2 $PID
kill -USR2 $PID
kill -TERM "$PID"
kill -USR2 $PID
kill -USR2 $PID
kill -TERM "$PID"
kill -USR2 $PID
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