#!/usr/bin/env bash

set -euo pipefail

#make debug
#PROGRAM="./cmake-build-debug/bongocat"
#PROGRAM="./build/bongocat"
PROGRAM="./cmake-build-relwithdebinfo-all-features-tsan/bongocat-all"

NR=$((800 + RANDOM % 100))
PID_FILE="${XDG_RUNTIME_DIR:-/tmp}/bongocat-${NR}.pid"
MAX_SHUTDOWN_MS=1000
SIGNALS=100

WORKDIR=$(mktemp -d)
CONFIG="$WORKDIR/test.bongocat.conf"  # config file to modify
OG_CONFIG=./examples/test/test.bongocat.conf
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
    "$PROGRAM" --config "$CONFIG" --nr "$NR" > "$WORKDIR/$1.log" 2>&1 &
    LAST_PID=$!
    PIDS+=("$LAST_PID")
    echo "[TEST] Started instance $1 (pid=$LAST_PID)"
}

pid_file() {
    cat "$PID_FILE" 2>/dev/null || true
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
    [[ ! -e "$PID_FILE" ]] || fail "$1: PID file not removed"
}

if [[ ! -x $PROGRAM ]]; then
    fail "$PROGRAM not found, build first"
fi

echo "[INFO] Test Program: ${PROGRAM} --config $CONFIG --nr $NR"

for SIG in TERM INT HUP; do
    start "$SIG"
    PID=$LAST_PID
    sleep 2
    kill -0 "$PID" 2>/dev/null || { cat "$WORKDIR/$SIG.log"; fail "instance $SIG not running"; }

    echo "[TEST] $SIG: signal storm ($SIGNALS signals)..."
    for ((i = 0; i < SIGNALS; i++)); do
        if ((i % 2 == 0)); then
            kill -USR1 "$PID"
        else
            kill -USR2 "$PID"
        fi
    done
    sleep 2

    kill -0 "$PID" 2>/dev/null || { tail -n 30 "$WORKDIR/$SIG.log"; fail "$SIG: instance died during signal storm"; }
    [[ "$(pid_file)" == "$PID" ]] || fail "$SIG: PID file does not contain $PID: '$(pid_file)'"
    echo "[OK] $SIG: survived signal storm"

    stop_and_check "$SIG" "$PID" "$SIG"
    echo "[OK] $SIG: shutdown fast and clean"
done

echo "[TEST] Done"
