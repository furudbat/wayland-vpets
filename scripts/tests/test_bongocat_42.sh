#!/usr/bin/env bash

set -euo pipefail

# Enable/disable features with config reloads: threads are (re)started and stopped accordingly
# thread names see pthread_setname_np (/proc/PID/task/TID/comm)

#make debug
#PROGRAM="./cmake-build-debug/bongocat"
#PROGRAM="./build/bongocat"
PROGRAM="./cmake-build-relwithdebinfo-all-features-tsan/bongocat-all"

NR=$((4200 + RANDOM % 100))
PID_FILE="${XDG_RUNTIME_DIR:-/tmp}/bongocat-${NR}.pid"
MAX_SHUTDOWN_MS=1000
ROUNDS=3

WORKDIR=$(mktemp -d)
CONFIG="$WORKDIR/test6.bongocat.conf"  # config file to modify
OG_CONFIG=./examples/test/test6.bongocat.conf
cp $OG_CONFIG $CONFIG
sed -i -E 's/^update_rate=.*/update_rate=0/' "$CONFIG"
sed -i -E 's/^cpu_threshold=.*/cpu_threshold=50/' "$CONFIG"
sed -i -E 's/^evolution=.*/evolution=none/' "$CONFIG"
sed -i '/^audio=/d' "$CONFIG"
printf '\naudio=0\n' >> "$CONFIG"  # config may not end with a newline

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

has_thread() {
    grep -qx "$2" /proc/"$1"/task/*/comm 2>/dev/null
}

# expect_thread <pid> <thread name> <yes|no> <what>: wait up to 5s for thread to (dis)appear
expect_thread() {
    local i
    for ((i = 0; i < 50; i++)); do
        if [[ $3 == yes ]] && has_thread "$1" "$2"; then return 0; fi
        if [[ $3 == no ]] && ! has_thread "$1" "$2"; then return 0; fi
        kill -0 "$1" 2>/dev/null || { tail -n 30 "$WORKDIR/A.log"; fail "instance died: $4"; }
        sleep 0.1
    done
    tail -n 30 "$WORKDIR/A.log"
    fail "$4: thread $2 running=$( has_thread "$1" "$2" && echo yes || echo no ), expected $3"
}

# set_config <key> <value> + reload
set_config() {
    sed -i "/^$1=/d" "$CONFIG"
    printf '\n%s=%s\n' "$1" "$2" >> "$CONFIG"  # config may not end with a newline
    kill -USR2 "$PID"
}

if [[ ! -x $PROGRAM ]]; then
    fail "$PROGRAM not found, build first"
fi

echo "[INFO] Test Program: ${PROGRAM} --config $CONFIG --nr $NR"

start A
PID=$LAST_PID
wait_ready A "$PID"
expect_thread "$PID" bc-anim yes "start"
expect_thread "$PID" bc-input yes "start"
expect_thread "$PID" bc-audio no "start (audio disabled)"
expect_thread "$PID" bc-update no "start (update disabled)"
echo "[OK] start: only needed threads running"

for ((r = 0; r < ROUNDS; r++)); do
    # audio on/off
    set_config audio 1
    expect_thread "$PID" bc-audio yes "R$r: audio enabled"
    set_config audio 0
    expect_thread "$PID" bc-audio no "R$r: audio disabled"

    # cpu monitoring on/off (update_rate + cpu_threshold)
    set_config update_rate 500
    expect_thread "$PID" bc-update yes "R$r: update_rate enabled"
    set_config cpu_threshold 0
    expect_thread "$PID" bc-update no "R$r: cpu_threshold disabled"
    set_config cpu_threshold 50
    expect_thread "$PID" bc-update yes "R$r: cpu_threshold re-enabled"
    set_config update_rate 0
    expect_thread "$PID" bc-update no "R$r: update_rate disabled"

    # always running
    expect_thread "$PID" bc-anim yes "R$r: animation"
    expect_thread "$PID" bc-input yes "R$r: input"
    echo "[OK] R$r: threads follow enabled features"
done

# features enabled on start
set_config audio 1
set_config update_rate 500
sleep 1
stop_and_check A "$PID" TERM

start B
PID=$LAST_PID
wait_ready B "$PID"
expect_thread "$PID" bc-audio yes "start (audio enabled)"
expect_thread "$PID" bc-update yes "start (update enabled)"
echo "[OK] start: enabled features have threads"
stop_and_check B "$PID" TERM

echo "[TEST] Done"
