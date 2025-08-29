echo "Testing bongocat toggle functionality..."
echo

#make
#PROGRAM="./cmake-build-debug/bongocat"
PROGRAM="./build/bongocat"

trap 'killall bongocat 2>/dev/null' EXIT

echo "[INFO] Starting bongocat with --toggle (should start since not running):"
$PROGRAM --toggle &
TOGGLE_PID=$!
sleep 10
echo
echo "[TEST] Checking if bongocat is running:"
# --- verify running ---
if kill -0 "$TOGGLE_PID" 2>/dev/null; then
    echo "[PASS] Process $TOGGLE_PID still running!"
else
    echo "[FAIL] Process terminated"
    exit 1
fi

echo
echo "[TEST] Toggling bongocat off (should stop the running instance):"
if ! timeout 5s $PROGRAM --toggle; then
    echo "[WARN] Toggle didn’t exit — force killing..."
    kill -9 "$TOGGLE_PID" 2>/dev/null || true
    pkill -9 bongocat 2>/dev/null || true
fi

echo
echo "[TEST] Toggling bongocat on again (should start since not running):"
$PROGRAM --toggle &
TOGGLE_PID2=$!
sleep 15
echo
echo "[TEST] Checking if bongocat is running:"
# --- verify running ---
if kill -0 "$TOGGLE_PID2" 2>/dev/null; then
    echo "[PASS] Process $TOGGLE_PID2 still running!"
else
    echo "[FAIL] Process terminated"
    exit 1
fi

echo
echo "[TEST] Toggling bongocat off (should stop the running instance):"
if ! timeout 5s $PROGRAM --toggle; then
    echo "[WARN] Toggle didn’t exit — force killing..."
    kill -9 "$TOGGLE_PID" 2>/dev/null || true
    pkill -9 bongocat 2>/dev/null || true
fi

echo
echo "Toggle functionality test completed!"
