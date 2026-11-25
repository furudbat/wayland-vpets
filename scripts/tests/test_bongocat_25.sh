#!/usr/bin/env bash

set -euo pipefail

#make debug
#PROGRAM="./cmake-build-debug/bongocat"
#PROGRAM="./build/bongocat"
PROGRAM="./cmake-build-relwithdebinfo-all-features-tsan/bongocat-all"

NR=$((900 + RANDOM % 100))  # don't clash with a real running instance
PID_FILE="${XDG_RUNTIME_DIR:-/tmp}/bongocat-${NR}.pid"
MAX_SHUTDOWN_MS=1000
RESTART_WAIT_SEC=10


WORKDIR=$(mktemp -d)
CONFIG="$WORKDIR/test.bongocat.conf"  # config file to modify
OG_CONFIG=./examples/test/test.bongocat.conf
cp $OG_CONFIG $CONFIG
# long sleeps in the threads (update thread sleeps update_rate ms), shutdown must not wait for them
sed -i -E 's/^update_rate=.*/update_rate=5000/' "$CONFIG"
sed -i -E 's/^cpu_threshold=.*/cpu_threshold=50/' "$CONFIG"

PIDS=()
cleanup() {
    echo "[TEST] Cleaning up..."
    for p in "${PIDS[@]}"; do
        kill -9 "$p" 2>/dev/null || true
    done
    rm -f "$PID_FILE"
    rm -rf "$WORKDIR"
}
trap cleanup EXIT

fail() {
    echo "[FAIL] $*"
    exit 1
}

start() {
    "$PROGRAM" --config "$CONFIG" --nr "$NR" > "$WORKDIR/$1.log" 2>&1 &
    LAST_PID=$!
    PIDS+=("$LAST_PID")
    echo "[TEST] Started instance $1 (pid=$LAST_PID)"
}

pid_file() {
    cat "$PID_FILE" 2>/dev/null || true
}

if [[ ! -x $PROGRAM ]]; then
    fail "$PROGRAM not found, build first"
fi

echo "[INFO] Test Program: ${PROGRAM} --config $CONFIG --nr $NR"

# --- 1. first instance ---
start A
PID_A=$LAST_PID
sleep 3
kill -0 "$PID_A" 2>/dev/null || { cat "$WORKDIR/A.log"; fail "instance A not running"; }
[[ "$(pid_file)" == "$PID_A" ]] || fail "PID file does not contain $PID_A: '$(pid_file)'"
echo "[OK] instance A running"

# --- 2. second instance, same nr ---
start B
PID_B=$LAST_PID
if wait "$PID_B"; then
    fail "instance B started, but should not"
fi
grep -q "already running" "$WORKDIR/B.log" || { cat "$WORKDIR/B.log"; fail "instance B: missing 'already running' message"; }
[[ "$(pid_file)" == "$PID_A" ]] || fail "PID file got wiped by instance B: '$(pid_file)'"
kill -0 "$PID_A" 2>/dev/null || fail "instance A died"
echo "[OK] instance B refused, PID file intact"

# --- 3. shutdown ---
echo "[TEST] Send SIGTERM to A..."
START=$(date +%s%3N)
kill -TERM "$PID_A"
wait "$PID_A" || true
END=$(date +%s%3N)
echo "[INFO] Shutdown took $((END - START))ms"
((END - START <= MAX_SHUTDOWN_MS)) || fail "shutdown too slow ($((END - START))ms)"
echo "[OK] shutdown fast"

# --- 4. restart (overlapping) ---
start C
PID_C=$LAST_PID
sleep 3
kill -0 "$PID_C" 2>/dev/null || { cat "$WORKDIR/C.log"; fail "instance C not running"; }

echo "[TEST] Restart: SIGTERM C and start D immediately..."
kill -TERM "$PID_C"
start D
PID_D=$LAST_PID
wait "$PID_C" || true

# waits for the lock until it's gone
for ((i = 0; i < RESTART_WAIT_SEC; i++)); do
    if [[ "$(pid_file)" == "$PID_D" ]] || ! kill -0 "$PID_D" 2>/dev/null; then
        break
    fi
    sleep 1
done
kill -0 "$PID_D" 2>/dev/null || { cat "$WORKDIR/D.log"; fail "restart failed"; }
[[ "$(pid_file)" == "$PID_D" ]] || fail "PID file does not contain $PID_D: '$(pid_file)'"
echo "[OK] restart works"

kill -TERM "$PID_D"
wait "$PID_D" || true

echo "[TEST] Done"
