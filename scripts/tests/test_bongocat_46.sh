#!/usr/bin/env bash

set -euo pipefail

# Logs into a closed pipe (e.g. `bongocat | head -n1`): no SIGPIPE crash, still reloads and shuts down cleanly

#make debug
#PROGRAM="./cmake-build-debug/bongocat"
#PROGRAM="./build/bongocat"
PROGRAM="./cmake-build-relwithdebinfo-all-features-tsan/bongocat-all"

NR=$((4600 + RANDOM % 100))
PID_FILE="${XDG_RUNTIME_DIR:-/tmp}/bongocat-${NR}.pid"
MAX_SHUTDOWN_MS=1000

WORKDIR=$(mktemp -d)
CONFIG="$WORKDIR/test6.bongocat.conf"  # config file to modify
OG_CONFIG=./examples/test/test6.bongocat.conf
cp $OG_CONFIG $CONFIG
sed -i -E 's/^enable_debug=.*/enable_debug=1/' "$CONFIG"

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

pid_file() {
    cat "$PID_FILE" 2>/dev/null || true
}

if [[ ! -x $PROGRAM ]]; then
    fail "$PROGRAM not found, build first"
fi

echo "[INFO] Test Program: ${PROGRAM} --config $CONFIG --nr $NR | head -n 1"

# stdout + stderr into a pipe that is closed after the first line
"$PROGRAM" --config "$CONFIG" --nr "$NR" > >(head -n 1 > /dev/null) 2>&1 &
PID=$!
PIDS+=("$PID")
echo "[TEST] Started instance A (pid=$PID)"
sleep 3
kill -0 "$PID" 2>/dev/null || { wait "$PID" || RET=$?; fail "died after pipe was closed (exit=${RET:-?}, 141 = SIGPIPE)"; }

# reloads + toggles write more logs into the closed pipe
for i in 1 2 3 4 5; do
    kill -USR2 "$PID"
    sleep 0.3
    kill -USR1 "$PID"
    sleep 0.2
done
sleep 1
kill -0 "$PID" 2>/dev/null || { wait "$PID" || RET=$?; fail "died while logging into closed pipe (exit=${RET:-?}, 141 = SIGPIPE)"; }
[[ "$(pid_file)" == "$PID" ]] || fail "PID file does not contain $PID: '$(pid_file)'"
echo "[OK] survived logging into closed pipe"

START=$(date +%s%3N)
RET=0
kill -TERM "$PID"
wait "$PID" || RET=$?
END=$(date +%s%3N)
echo "[INFO] A: shutdown took $((END - START))ms (exit=$RET)"
[[ $RET -eq 0 ]] || fail "A: exit code $RET"
((END - START <= MAX_SHUTDOWN_MS)) || fail "A: shutdown too slow ($((END - START))ms)"
[[ ! -e "$PID_FILE" ]] || fail "A: PID file not removed"
echo "[OK] shutdown fast and clean"

echo "[TEST] Done"
