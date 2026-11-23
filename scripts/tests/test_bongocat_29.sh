#!/usr/bin/env bash

set -euo pipefail

#make debug
#PROGRAM="./cmake-build-debug/bongocat"
#PROGRAM="./build/bongocat"
PROGRAM="./cmake-build-relwithdebinfo-all-features-tsan/bongocat-all"

NR=$((900 + RANDOM % 100))
PID_FILE="${XDG_RUNTIME_DIR:-/tmp}/bongocat-${NR}.pid"
MAX_SHUTDOWN_MS=1000
WRITES=30

WORKDIR=$(mktemp -d)
CONFIG="$WORKDIR/test.bongocat.conf"  # config file to modify
OG_CONFIG=./examples/test/test.bongocat.conf
cp $OG_CONFIG $CONFIG
sed -i -E 's/^update_rate=.*/update_rate=5000/' "$CONFIG"
sed -i -E 's/^cpu_threshold=.*/cpu_threshold=50/' "$CONFIG"

PIDS=()
WRITER_PID=""
cleanup() {
    echo "[TEST] Cleaning up..."
    [[ -n "$WRITER_PID" ]] && kill "$WRITER_PID" 2>/dev/null || true
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
    "$PROGRAM" --config "$CONFIG" --nr "$NR" --watch-config > "$WORKDIR/$1.log" 2>&1 &
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

# write_config <i>: change the config, every 2nd write is an atomic replace (like editors do)
write_config() {
    local fps=$((30 + ($1 % 2) * 30))
    if (($1 % 2 == 0)); then
        sed -i -E "s/^fps=.*/fps=$fps/" "$CONFIG"
    else
        sed -E "s/^fps=.*/fps=$fps/" "$CONFIG" > "$CONFIG.tmp"
        mv "$CONFIG.tmp" "$CONFIG"
    fi
}

if [[ ! -x $PROGRAM ]]; then
    fail "$PROGRAM not found, build first"
fi

echo "[INFO] Test Program: ${PROGRAM} --config $CONFIG --nr $NR --watch-config"

start A
PID_A=$LAST_PID
sleep 3
kill -0 "$PID_A" 2>/dev/null || { cat "$WORKDIR/A.log"; fail "instance A not running"; }

echo "[TEST] Config writes ($WRITES writes)..."
for ((i = 0; i < WRITES; i++)); do
    write_config "$i"
    sleep 0.2
done
sleep 2

kill -0 "$PID_A" 2>/dev/null || { tail -n 30 "$WORKDIR/A.log"; fail "instance A died during config writes"; }
[[ "$(pid_file)" == "$PID_A" ]] || fail "PID file does not contain $PID_A: '$(pid_file)'"
grep -q "Config file changed, trigger reload" "$WORKDIR/A.log" || { grep -i "watch\|reload" "$WORKDIR/A.log" | head -30; fail "config watcher never triggered a reload"; }
echo "[OK] survived config writes"

echo "[TEST] Shutdown while writing config..."
(
    for ((i = 0; ; i++)); do
        write_config "$i"
        sleep 0.05
    done
) &
WRITER_PID=$!
sleep 1
stop_and_check A "$PID_A" TERM
kill "$WRITER_PID" 2>/dev/null || true
wait "$WRITER_PID" 2>/dev/null || true
WRITER_PID=""
echo "[OK] shutdown fast and clean"

echo "[TEST] Done"
