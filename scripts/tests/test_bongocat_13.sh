#!/usr/bin/env bash

set -euo pipefail

#make debug
#PROGRAM="./cmake-build-debug-all-assets-colored-preload/bongocat"
PROGRAM="./cmake-build-debug/bongocat-all"
#PROGRAM="./build/bongocat-all"

WORKDIR=$(mktemp -d)
CONFIG="$WORKDIR/invalid.test.bongocat.conf"  # config file to modify
OG_CONFIG=./examples/test/invalid.test.bongocat.conf
cp $OG_CONFIG $CONFIG
CONFIG2="$WORKDIR/invalid2.test.bongocat.conf"
OG_CONFIG2=./examples/test/invalid2.test.bongocat.conf
cp $OG_CONFIG2 $CONFIG2

if [[ $# -ge 1 ]]; then
    PID="$1"
    CONFIG="$2"
    cp $CONFIG "${CONFIG}.bak"
    OG_CONFIG="${CONFIG}.bak"
    echo "[TEST] Using provided PID = $PID"
else
    echo "[TEST] Starting program..."
    "$PROGRAM" --config "$CONFIG" --ignore-running &
    PID=$!
    echo "[TEST] Program PID = $PID"
    sleep 5
fi
# --- verify running ---
if kill -0 "$PID" 2>/dev/null; then
    echo "[PASS] Process $PID still running!"
else
    echo "[FAIL] Process terminated"
    exit 1
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

# --- verify running ---
if kill -0 "$PID" 2>/dev/null; then
    echo "[PASS] Process $PID still running!"
else
    echo "[FAIL] Process terminated"
    exit 1
fi

# Restart
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
cat "$CONFIG" | "$PROGRAM" --ignore-running --config - &
PID=$!
sleep 10
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

# Restart - stdin default config
echo "[TEST] Start config in strict mode..."
"$PROGRAM" --config "$CONFIG" --ignore-running --strict &
PID=$!
sleep 10
# --- verify not running ---
if kill -0 "$PID" 2>/dev/null; then
    echo "[FAIL] Process $PID still running!"
    kill -9 "$PID" 2>/dev/null
    exit 1
else
    echo "[PASS] Process terminated successfully"
fi


# Restart - config2
echo "[TEST] Start invalid config..."
"$PROGRAM" --ignore-running --config "$CONFIG2" &
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


# Restart config2 - strict
echo "[TEST] Start config in strict mode..."
"$PROGRAM" --ignore-running --config "$CONFIG2" --strict &
PID=$!
sleep 10
# --- verify not running ---
if kill -0 "$PID" 2>/dev/null; then
    echo "[FAIL] Process $PID still running!"
    kill -9 "$PID" 2>/dev/null
    exit 1
else
    echo "[PASS] Process terminated successfully"
fi
