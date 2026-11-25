#!/usr/bin/env bash

set -euo pipefail

#make debug
#PROGRAM="./cmake-build-debug/bongocat"
#PROGRAM="./build/bongocat"
PROGRAM="./cmake-build-relwithdebinfo-all-features-tsan/bongocat-all"

NR=$((1400 + RANDOM % 100))
PID_FILE="${XDG_RUNTIME_DIR:-/tmp}/bongocat-${NR}.pid"
MAX_SHUTDOWN_MS=1000
RELOADS=50
MAX_FD_DIFF=2
MAX_THREAD_DIFF=1
MAX_RSS_DIFF_KB=$((64 * 1024))  # TSan shadow memory grows, keep it generous
EXTRA_DEVICE="keyboard_device=/dev/input/bongocat-test-missing"

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

fd_count() { ls "/proc/$1/fd" | wc -l; }
threads() { awk '/^Threads:/{print $2}' "/proc/$1/status"; }
rss_kb() { awk '/^VmRSS:/{print $2}' "/proc/$1/status"; }

if [[ ! -x $PROGRAM ]]; then
    fail "$PROGRAM not found, build first"
fi

echo "[INFO] Test Program: ${PROGRAM} --config $CONFIG --nr $NR"

start A
PID_A=$LAST_PID
wait_ready A "$PID_A"
sleep 2  # let the update thread stop itself ("not needed")

FD0=$(fd_count "$PID_A"); TH0=$(threads "$PID_A"); RSS0=$(rss_kb "$PID_A")
echo "[INFO] before: fds=$FD0 threads=$TH0 rss=${RSS0}kB"

echo "[TEST] $RELOADS reloads (audio, fps, devices)..."
for ((i = 0; i < RELOADS; i++)); do
    case $((i % 4)) in
        0) sed -i -E 's/^audio=.*/audio=0/' "$CONFIG" ;;
        1) sed -i -E 's/^audio=.*/audio=1/' "$CONFIG" ;;
        2) sed -i -E 's/^fps=.*/fps=30/' "$CONFIG"
           echo "$EXTRA_DEVICE" >> "$CONFIG" ;;  # devices changed -> input restart
        3) sed -i -E 's/^fps=.*/fps=60/' "$CONFIG"
           sed -i "\|^$EXTRA_DEVICE\$|d" "$CONFIG" ;;  # devices changed -> input restart
    esac
    kill -USR2 "$PID_A"
    sleep 0.2
done
sleep 3

kill -0 "$PID_A" 2>/dev/null || { tail -n 30 "$WORKDIR/A.log"; fail "instance A died during reloads"; }
FD1=$(fd_count "$PID_A"); TH1=$(threads "$PID_A"); RSS1=$(rss_kb "$PID_A")
echo "[INFO] after:  fds=$FD1 threads=$TH1 rss=${RSS1}kB"

((FD1 - FD0 <= MAX_FD_DIFF)) || { ls -l "/proc/$PID_A/fd"; fail "fd leak: $FD0 -> $FD1"; }
((TH1 - TH0 <= MAX_THREAD_DIFF)) || fail "thread leak: $TH0 -> $TH1"
((RSS1 - RSS0 <= MAX_RSS_DIFF_KB)) || fail "memory growth: ${RSS0}kB -> ${RSS1}kB"
echo "[OK] no fd/thread leak, memory stable"

stop_and_check A "$PID_A" TERM
echo "[OK] shutdown fast and clean"

echo "[TEST] Done"
