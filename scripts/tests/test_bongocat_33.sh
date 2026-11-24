#!/usr/bin/env bash

set -euo pipefail

#make debug
#PROGRAM="./cmake-build-debug/bongocat"
#PROGRAM="./build/bongocat"
PROGRAM="./cmake-build-relwithdebinfo-all-features-tsan/bongocat-all"

NR=$((1300 + RANDOM % 100))
PID_FILE="${XDG_RUNTIME_DIR:-/tmp}/bongocat-${NR}.pid"
MAX_SHUTDOWN_MS=1000

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

# stop_and_check <name> <pid> <signal>
stop_and_check() {
    local START END RET=0
    START=$(date +%s%3N)
    kill "-$3" "$2"
    wait "$2" || RET=$?
    END=$(date +%s%3N)
    echo "[INFO] $1: shutdown took $((END - START))ms (exit=$RET)"
    if [[ $RET -ne 0 ]]; then
        # show sanitizer report (exit code 66), otherwise the end of the log
        grep -A40 "WARNING: ThreadSanitizer\|ERROR: AddressSanitizer" "$WORKDIR/$1.log" || tail -n 30 "$WORKDIR/$1.log"
        fail "$1: exit code $RET"
    fi
    ((END - START <= MAX_SHUTDOWN_MS)) || fail "$1: shutdown too slow ($((END - START))ms)"
    ! grep -q "Thread did not exit in time" "$WORKDIR/$1.log" || fail "$1: thread had to be cancelled"
    ! grep -q "did not acknowledge config gen\|Timed out waiting for reload" "$WORKDIR/$1.log" || fail "$1: reload not acknowledged in time"
    [[ ! -e "$PID_FILE" ]] || fail "$1: PID file not removed"
}

if [[ ! -x $PROGRAM ]]; then
    fail "$PROGRAM not found, build first"
fi

echo "[INFO] Test Program: ${PROGRAM} --config $CONFIG --nr $NR"

# signals arriving while the program is still starting up
for delay in 0.05 0.1 0.2 0.5 1; do
    for sig in USR2 USR1; do
        name="${sig}_${delay}"
        start "$name"
        PID=$LAST_PID
        sleep "$delay"
        kill "-$sig" "$PID" 2>/dev/null || true
        wait_ready "$name" "$PID"
        sleep 0.5
        kill -0 "$PID" 2>/dev/null || { tail -n 30 "$WORKDIR/$name.log"; fail "$name: killed by early SIG$sig"; }
        stop_and_check "$name" "$PID" TERM
    done
    echo "[OK] early SIGUSR1/SIGUSR2 after ${delay}s survived"
done

# SIGTERM while still starting up: must exit (no hang), next instance must start
for delay in 0.05 0.1 0.2 0.5 1; do
    name="TERM_${delay}"
    start "$name"
    PID=$LAST_PID
    sleep "$delay"
    START=$(date +%s%3N)
    kill -TERM "$PID" 2>/dev/null || true
    RET=0
    wait "$PID" || RET=$?
    END=$(date +%s%3N)
    echo "[INFO] $name: exit took $((END - START))ms (exit=$RET)"
    # 143 = killed by SIGTERM before the handler was installed, acceptable
    if [[ $RET -ne 0 && $RET -ne 143 ]]; then
        grep -A40 "WARNING: ThreadSanitizer\|ERROR: AddressSanitizer" "$WORKDIR/$name.log" || tail -n 30 "$WORKDIR/$name.log"
        fail "$name: exit code $RET"
    fi
    ((END - START <= MAX_SHUTDOWN_MS)) || { grep -vE "VERBOSE|DEBUG" "$WORKDIR/$name.log" | tail -n 40; fail "$name: exit too slow ($((END - START))ms)"; }
    ! grep -q "Thread did not exit in time" "$WORKDIR/$name.log" || fail "$name: thread had to be cancelled"
done
echo "[OK] early SIGTERM exits fast"

start AFTER
PID=$LAST_PID
wait_ready AFTER "$PID"
stop_and_check AFTER "$PID" TERM
echo "[OK] normal start after early SIGTERMs"

echo "[TEST] Done"
