#!/usr/bin/env bash

set -euo pipefail

# needs a nested headless compositor (sway or weston), otherwise skipped

#make debug
#PROGRAM="./cmake-build-debug/bongocat"
#PROGRAM="./build/bongocat"
PROGRAM="./cmake-build-relwithdebinfo-all-features-tsan/bongocat-all"

NR=$((1600 + RANDOM % 100))
PID_FILE="${XDG_RUNTIME_DIR:-/tmp}/bongocat-${NR}.pid"

WORKDIR=$(mktemp -d)
CONFIG="$WORKDIR/test6.bongocat.conf"  # config file to modify
OG_CONFIG=./examples/test/test6.bongocat.conf
cp $OG_CONFIG $CONFIG
sed -i -E 's/^update_rate=.*/update_rate=5000/' "$CONFIG"
sed -i -E 's/^cpu_threshold=.*/cpu_threshold=50/' "$CONFIG"
sed -i -E 's/^monitor=.*/monitor=/' "$CONFIG"  # headless output has another name

PIDS=()
COMPOSITOR_PID=""
stop_compositor() {
    if [[ -n "$COMPOSITOR_PID" ]]; then
        kill -9 "$COMPOSITOR_PID" 2>/dev/null || true
        wait "$COMPOSITOR_PID" 2>/dev/null || true
    fi
    COMPOSITOR_PID=""
}
cleanup() {
    echo "[TEST] Cleaning up..."
    stop_compositor
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

if [[ ! -x $PROGRAM ]]; then
    fail "$PROGRAM not found, build first"
fi

TEST_DISPLAY="wayland-bongocat-test-$NR"
if command -v weston >/dev/null; then
    weston --backend=headless --socket="$TEST_DISPLAY" > "$WORKDIR/compositor.log" 2>&1 &
    COMPOSITOR_PID=$!
elif command -v sway >/dev/null; then
    # sway picks its own socket name, find it below
    TEST_DISPLAY=""
    env -u WAYLAND_DISPLAY WLR_BACKENDS=headless WLR_LIBINPUT_NO_DEVICES=1 \
        sway -c /dev/null > "$WORKDIR/compositor.log" 2>&1 &
    COMPOSITOR_PID=$!
else
    echo "[SKIP] no headless compositor (weston or sway) installed"
    exit 0
fi

# wait for the compositor socket
for ((i = 0; i < 50; i++)); do
    if [[ -z "$TEST_DISPLAY" ]]; then
        TEST_DISPLAY=$(grep -oE 'WAYLAND_DISPLAY=[^ ]+' "$WORKDIR/compositor.log" | head -n1 | cut -d= -f2 || true)
    fi
    [[ -n "$TEST_DISPLAY" && -S "$XDG_RUNTIME_DIR/$TEST_DISPLAY" ]] && break
    sleep 0.1
done
[[ -n "$TEST_DISPLAY" && -S "$XDG_RUNTIME_DIR/$TEST_DISPLAY" ]] || { cat "$WORKDIR/compositor.log"; fail "compositor did not start"; }
echo "[INFO] compositor running on $TEST_DISPLAY (pid=$COMPOSITOR_PID)"

echo "[INFO] Test Program: WAYLAND_DISPLAY=$TEST_DISPLAY ${PROGRAM} --config $CONFIG --nr $NR"
WAYLAND_DISPLAY="$TEST_DISPLAY" "$PROGRAM" --config "$CONFIG" --nr "$NR" > "$WORKDIR/A.log" 2>&1 &
PID_A=$!
PIDS+=("$PID_A")
echo "[TEST] Started instance A (pid=$PID_A)"
wait_ready A "$PID_A"
echo "[OK] running on headless compositor"

echo "[TEST] kill compositor..."
START=$(date +%s%3N)
stop_compositor
for ((i = 0; i < 20; i++)); do
    kill -0 "$PID_A" 2>/dev/null || break
    sleep 0.1
done
if kill -0 "$PID_A" 2>/dev/null; then
    tail -n 30 "$WORKDIR/A.log"
    fail "A still running 2s after compositor died"
fi
RET=0
wait "$PID_A" || RET=$?
END=$(date +%s%3N)
echo "[INFO] A: exit after compositor loss took $((END - START))ms (exit=$RET)"
if grep -q "WARNING: ThreadSanitizer\|ERROR: AddressSanitizer" "$WORKDIR/A.log"; then
    grep -A40 "WARNING: ThreadSanitizer\|ERROR: AddressSanitizer" "$WORKDIR/A.log"
    fail "sanitizer report"
fi
((RET != 66)) || fail "sanitizer exit code"
((RET < 128)) || { tail -n 30 "$WORKDIR/A.log"; fail "A crashed (exit=$RET)"; }
! grep -q "Thread did not exit in time" "$WORKDIR/A.log" || fail "thread had to be cancelled"
[[ ! -e "$PID_FILE" ]] || fail "PID file not removed"
echo "[OK] clean exit after compositor loss"

echo "[TEST] Done"
