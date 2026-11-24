#!/usr/bin/env bash

set -euo pipefail

#make debug
#PROGRAM="./cmake-build-debug/bongocat"
#PROGRAM="./build/bongocat"
PROGRAM="./cmake-build-relwithdebinfo-all-features-tsan/bongocat-all"

NR=$((1100 + RANDOM % 100))
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

# stop_and_check <name> <pid> <signal>
stop_and_check() {
    local START RET=0
    START=$(date +%s%3N)
    kill "-$3" "$2"
    wait "$2" || RET=$?
    check_exit "$1" "$RET" "$START"
}

if [[ ! -x $PROGRAM ]]; then
    fail "$PROGRAM not found, build first"
fi

echo "[INFO] Test Program: ${PROGRAM} --config $CONFIG --nr $NR"

# 1. hard kill leaves a stale PID file (lock is gone)
start A
PID_A=$LAST_PID
wait_ready A "$PID_A"
[[ "$(pid_file)" == "$PID_A" ]] || fail "PID file does not contain $PID_A: '$(pid_file)'"
kill -9 "$PID_A"
wait "$PID_A" 2>/dev/null || true
[[ -e "$PID_FILE" ]] || fail "expected stale PID file after SIGKILL"
echo "[OK] stale PID file left after SIGKILL: '$(pid_file)'"

start B
PID_B=$LAST_PID
wait_ready B "$PID_B"
[[ "$(pid_file)" == "$PID_B" ]] || fail "PID file does not contain $PID_B: '$(pid_file)'"
echo "[OK] B took over stale PID file"
stop_and_check B "$PID_B" TERM

# 2. stale PID file with garbage / pid of a running non-bongocat process
for content in "garbage" "" "$$" "1" "999999999"; do
    printf '%s\n' "$content" > "$PID_FILE"
    start C
    PID_C=$LAST_PID
    wait_ready C "$PID_C"
    [[ "$(pid_file)" == "$PID_C" ]] || fail "stale '$content': PID file does not contain $PID_C: '$(pid_file)'"
    echo "[OK] stale PID file '$content' replaced"
    stop_and_check C "$PID_C" TERM
done

echo "[TEST] Done"
