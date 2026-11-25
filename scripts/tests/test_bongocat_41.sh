#!/usr/bin/env bash

set -euo pipefail

# Idle: threads of disabled features don't run, idle threads don't wake up (much)
# wakeups = voluntary context switches per thread (/proc/PID/task/TID/status), thread names see pthread_setname_np

#make debug
#PROGRAM="./cmake-build-debug/bongocat"
#PROGRAM="./build/bongocat"
PROGRAM="./cmake-build-release-all-features/bongocat-all"  # no sanitizer: measure real wakeups

NR=$((4100 + RANDOM % 100))
PID_FILE="${XDG_RUNTIME_DIR:-/tmp}/bongocat-${NR}.pid"
MAX_SHUTDOWN_MS=1000
MEASURE_SEC=5
# max. wakeups per second for idle threads
MAX_WATCH_WAKEUPS=1
MAX_UPDATE_WAKEUPS=5    # update_rate=1000
MAX_MAIN_WAKEUPS=20     # event driven (renders only when animation changes, fullscreen check 1/s)
MAX_ANIM_WAKEUPS=150    # animation (game) loop at fps=60: ~2 wakeups per frame
MAX_INPUT_WAKEUPS=2     # no real device (no key presses), only device re-check

WORKDIR=$(mktemp -d)
CONFIG="$WORKDIR/test6.bongocat.conf"  # config file to modify
OG_CONFIG=./examples/test/test6.bongocat.conf
cp $OG_CONFIG $CONFIG
sed -i -E 's/^enable_debug=.*/enable_debug=0/' "$CONFIG"
sed -i -E 's/^update_rate=.*/update_rate=0/' "$CONFIG"
sed -i -E 's/^evolution=.*/evolution=none/' "$CONFIG"
sed -i '/^audio=/d' "$CONFIG"
printf '\naudio=0\n' >> "$CONFIG"  # config may not end with a newline
# no real input device: key presses/mouse moves while measuring would add wakeups
sed -i '/^keyboard_device=/d' "$CONFIG"
printf 'keyboard_device=/dev/input/bongocat-test-missing\n' >> "$CONFIG"

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
        tail -n 30 "$WORKDIR/$1.log"
        fail "$1: exit code $RET"
    fi
    ((END - START <= MAX_SHUTDOWN_MS)) || fail "$1: shutdown too slow ($((END - START))ms)"
    ! grep -q "Thread did not exit in time" "$WORKDIR/$1.log" || fail "$1: thread had to be cancelled"
    ! grep -q "did not acknowledge config gen\|Timed out waiting for reload" "$WORKDIR/$1.log" || fail "$1: reload not acknowledged in time"
    [[ ! -e "$PID_FILE" ]] || fail "$1: PID file not removed"
}

# measure <pid>: sets WAKEUPS[thread name] = voluntary context switches per second (main thread = "main")
declare -A WAKEUPS
measure() {
    local t name n
    declare -A before
    WAKEUPS=()
    for t in /proc/$1/task/*; do
        before[$t]=$(awk '/^voluntary_ctxt_switches/{print $2}' "$t/status" 2>/dev/null || echo 0)
    done
    sleep "$MEASURE_SEC"
    for t in /proc/$1/task/*; do
        name=$(cat "$t/comm" 2>/dev/null) || continue
        [[ "$(basename "$t")" == "$1" ]] && name="main"
        n=$(awk '/^voluntary_ctxt_switches/{print $2}' "$t/status" 2>/dev/null) || continue
        WAKEUPS[$name]=$(( (n - ${before[$t]:-$n}) / MEASURE_SEC ))
    done
    local out="" k
    for k in "${!WAKEUPS[@]}"; do out+=" $k=${WAKEUPS[$k]}/s"; done
    echo "[INFO] wakeups:$out"
}

# check_wakeups <thread name> <max per second>: thread must exist and not wake up more often
check_wakeups() {
    [[ -n "${WAKEUPS[$1]+x}" ]] || fail "thread $1 not running"
    ((WAKEUPS[$1] <= $2)) || fail "thread $1 wakes up too often: ${WAKEUPS[$1]}/s > $2/s"
}

# check_absent <thread name>: thread of a disabled feature must not run
check_absent() {
    [[ -z "${WAKEUPS[$1]+x}" ]] || fail "thread $1 running, but feature is disabled"
}

if [[ ! -x $PROGRAM ]]; then
    fail "$PROGRAM not found, build first"
fi

echo "[INFO] Test Program: ${PROGRAM} --config $CONFIG --nr $NR"

# 1. features off (audio, update): no audio/update thread, no config watcher
start A
PID=$LAST_PID
wait_ready A "$PID"
sleep 1
measure "$PID"
check_absent bc-audio
check_absent bc-update
check_absent bc-watch
check_wakeups main "$MAX_MAIN_WAKEUPS"
check_wakeups bc-anim "$MAX_ANIM_WAKEUPS"
check_wakeups bc-input "$MAX_INPUT_WAKEUPS"
echo "[OK] A: disabled features have no thread, idle threads quiet"

# 2. bar hidden (SIGUSR1): nothing to render
kill -USR1 "$PID"
sleep 1
measure "$PID"
check_wakeups main "$MAX_MAIN_WAKEUPS"
check_wakeups bc-anim "$MAX_ANIM_WAKEUPS"
echo "[OK] A: hidden, idle threads quiet"
stop_and_check A "$PID" TERM

# 3. config watcher + update (cpu monitoring every 1s): watcher only wakes up on changes
sed -i -E 's/^update_rate=.*/update_rate=1000/' "$CONFIG"
sed -i -E 's/^cpu_threshold=.*/cpu_threshold=90/' "$CONFIG"
start B --watch-config
PID=$LAST_PID
wait_ready B "$PID"
sleep 1
measure "$PID"
check_wakeups bc-watch "$MAX_WATCH_WAKEUPS"
check_wakeups bc-update "$MAX_UPDATE_WAKEUPS"
check_absent bc-audio
echo "[OK] B: config watcher and update thread quiet"
stop_and_check B "$PID" TERM

echo "[TEST] Done"
