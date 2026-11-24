#!/usr/bin/env bash

set -euo pipefail

#make debug
#PROGRAM="./cmake-build-debug/bongocat"
#PROGRAM="./build/bongocat"
PROGRAM="./cmake-build-relwithdebinfo-all-features-tsan/bongocat-all"

NR=$((1500 + RANDOM % 100))
PID_FILE="${XDG_RUNTIME_DIR:-/tmp}/bongocat-${NR}.pid"
MAX_SHUTDOWN_MS=1000

WORKDIR=$(mktemp -d)
CONFIG="$WORKDIR/test6.bongocat.conf"  # config file to modify
OG_CONFIG=./examples/test/test6.bongocat.conf
cp $OG_CONFIG $CONFIG
sed -i -E 's/^update_rate=.*/update_rate=5000/' "$CONFIG"
sed -i -E 's/^cpu_threshold=.*/cpu_threshold=50/' "$CONFIG"

PIDS=()
WRITER_PID=""
stop_writer() {
    if [[ -n "$WRITER_PID" ]]; then
        kill "$WRITER_PID" 2>/dev/null || true
        wait "$WRITER_PID" 2>/dev/null || true
    fi
    WRITER_PID=""
}
cleanup() {
    echo "[TEST] Cleaning up..."
    stop_writer
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

reload_count() { grep -c "Config file changed, trigger reload" "$WORKDIR/A.log" || true; }

if [[ ! -x $PROGRAM ]]; then
    fail "$PROGRAM not found, build first"
fi

echo "[INFO] Test Program: ${PROGRAM} --config $CONFIG --nr $NR --watch-config"
cp "$CONFIG" "$WORKDIR/backup.conf"

start A --watch-config
PID_A=$LAST_PID
wait_ready A "$PID_A"

echo "[TEST] config writes + SIGUSR2 at the same time..."
(
    for ((i = 0; ; i++)); do
        sed -i -E "s/^fps=.*/fps=$((30 + (i % 2) * 30))/" "$CONFIG"
        sleep 0.05
    done
) &
WRITER_PID=$!
for ((i = 0; i < 40; i++)); do
    kill -USR2 "$PID_A"
    sleep 0.07
done
stop_writer
sleep 2
kill -0 "$PID_A" 2>/dev/null || { tail -n 30 "$WORKDIR/A.log"; fail "A died during writes + SIGUSR2"; }
echo "[OK] survived writes + SIGUSR2"

echo "[TEST] delete config..."
rm -f "$CONFIG"
kill -USR2 "$PID_A"  # reload without a config file
sleep 2
kill -0 "$PID_A" 2>/dev/null || { tail -n 30 "$WORKDIR/A.log"; fail "A died after config was deleted"; }
echo "[OK] survived deleted config"

echo "[TEST] recreate config..."
BEFORE=$(reload_count)
cp "$WORKDIR/backup.conf" "$CONFIG"
sleep 1
sed -i -E 's/^fps=.*/fps=30/' "$CONFIG"
sleep 2
AFTER=$(reload_count)
kill -0 "$PID_A" 2>/dev/null || { tail -n 30 "$WORKDIR/A.log"; fail "A died after config was recreated"; }
((AFTER > BEFORE)) || { grep -i "watch" "$WORKDIR/A.log" | tail -n 20; fail "watcher did not reload after recreate ($BEFORE -> $AFTER)"; }
echo "[OK] watcher reloads again after recreate ($BEFORE -> $AFTER)"

stop_and_check A "$PID_A" TERM
echo "[OK] shutdown fast and clean"

echo "[TEST] Done"
