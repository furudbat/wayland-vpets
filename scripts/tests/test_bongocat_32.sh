#!/usr/bin/env bash

set -euo pipefail

#make debug
#PROGRAM="./cmake-build-debug/bongocat"
#PROGRAM="./build/bongocat"
PROGRAM="./cmake-build-relwithdebinfo-all-features-tsan/bongocat-all"

NR=$((1200 + RANDOM % 100))
PID_FILE="${XDG_RUNTIME_DIR:-/tmp}/bongocat-${NR}.pid"
MAX_SHUTDOWN_MS=1000
ROUNDS=3

WORKDIR=$(mktemp -d)
CONFIG="$WORKDIR/test6.bongocat.conf"  # config file to modify
OG_CONFIG=./examples/test/test6.bongocat.conf
cp $OG_CONFIG $CONFIG
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
    "$PROGRAM" --config "$CONFIG" --nr "$NR" "${@:2}" > "$WORKDIR/$1.log" 2>&1 &
    LAST_PID=$!
    PIDS+=("$LAST_PID")
    echo "[TEST] Started instance $1 (pid=$LAST_PID)"
}

pid_file() {
    cat "$PID_FILE" 2>/dev/null || true
}

# wait_ready <name> <pid>: wait until the main loop runs (no fixed sleep)
wait_ready() {
    local i
    for ((i = 0; i < 100; i++)); do
        grep -q "Starting Wayland event loop" "$WORKDIR/$1.log" 2>/dev/null && return 0
        kill -0 "$2" 2>/dev/null || { tail -n 30 "$WORKDIR/$1.log"; fail "$1 died during startup"; }
        sleep 0.1
    done
    tail -n 30 "$WORKDIR/$1.log"
    fail "$1 not ready after 10s"
}

# check_exit <name> <exit code> <start ms>: same checks as stop_and_check, for an already exited instance
check_exit() {
    local END
    END=$(date +%s%3N)
    echo "[INFO] $1: shutdown took $((END - $3))ms (exit=$2)"
    if [[ $2 -ne 0 ]]; then
        # show sanitizer report (exit code 66), otherwise the end of the log
        grep -A40 "WARNING: ThreadSanitizer\|ERROR: AddressSanitizer" "$WORKDIR/$1.log" || tail -n 30 "$WORKDIR/$1.log"
        fail "$1: exit code $2"
    fi
    ((END - $3 <= MAX_SHUTDOWN_MS)) || fail "$1: shutdown too slow ($((END - $3))ms)"
    ! grep -q "Thread did not exit in time" "$WORKDIR/$1.log" || fail "$1: thread had to be cancelled"
    ! grep -q "did not acknowledge config gen\|Timed out waiting for reload" "$WORKDIR/$1.log" || fail "$1: reload not acknowledged in time"
    [[ ! -e "$PID_FILE" ]] || fail "$1: PID file not removed"
}

if [[ ! -x $PROGRAM ]]; then
    fail "$PROGRAM not found, build first"
fi

echo "[INFO] Test Program: ${PROGRAM} --config $CONFIG --nr $NR --toggle"

for ((i = 0; i < ROUNDS; i++)); do
    # toggle on: nothing running -> starts
    start "ON$i" --toggle
    PID_ON=$LAST_PID
    wait_ready "ON$i" "$PID_ON"
    [[ "$(pid_file)" == "$PID_ON" ]] || fail "ON$i: PID file does not contain $PID_ON: '$(pid_file)'"
    echo "[OK] ON$i: toggle started instance"

    # toggle off: running -> stops it, toggle process exits by itself
    START=$(date +%s%3N)
    RET=0
    timeout 10 "$PROGRAM" --config "$CONFIG" --nr "$NR" --toggle > "$WORKDIR/OFF$i.log" 2>&1 || RET=$?
    if [[ $RET -ne 0 ]]; then
        tail -n 30 "$WORKDIR/OFF$i.log"
        fail "OFF$i: toggle exit code $RET"
    fi
    ! grep -q "Force killing" "$WORKDIR/OFF$i.log" || fail "OFF$i: instance had to be force killed"
    grep -q "Bongocat stopped successfully" "$WORKDIR/OFF$i.log" || { tail -n 30 "$WORKDIR/OFF$i.log"; fail "OFF$i: toggle did not stop the instance"; }

    RET=0
    wait "$PID_ON" || RET=$?
    check_exit "ON$i" "$RET" "$START"
    echo "[OK] OFF$i: toggle stopped instance"
done

echo "[TEST] Done"
