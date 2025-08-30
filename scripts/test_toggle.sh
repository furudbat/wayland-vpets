echo "Testing bongocat toggle functionality..."
echo

#make
#PROGRAM="./cmake-build-debug/bongocat"
PROGRAM="./build/bongocat"

trap 'killall bongocat 2>/dev/null' EXIT

echo "[TEST] --- Toggle Functionality ---"

# Start initial instance
if [[ $# -ge 1 ]]; then
    TOGGLE_PID="$1"
    echo "[TEST] Using provided PID = $TOGGLE_PID"
else
    echo "[TEST] Starting program..."
    "$PROGRAM" --toggle --config bongocat.conf &
    TOGGLE_PID=$!
    echo "[TEST] Program PID = $TOGGLE_PID"
    sleep 20
fi
echo "[TEST] Initial bongocat PID = $TOGGLE_PID"
sleep 2

# Toggle off
echo "[TEST] Sending --toggle to stop the instance..."
"$PROGRAM" --toggle --config bongocat.conf
# Wait for shutdown
for i in {1..10}; do
    if ! kill -0 "$TOGGLE_PID" 2>/dev/null; then break; fi
    sleep 0.5
done

if kill -0 "$TOGGLE_PID" 2>/dev/null; then
    echo "[FAIL] Toggle failed: Process $TOGGLE_PID still running!"
    kill -9 "$TOGGLE_PID" 2>/dev/null || true
    exit 1
else
    echo "[PASS] Process terminated successfully via toggle"
fi

# Toggle on (should start new instance)
echo "[TEST] Sending --toggle to start a new instance..."
"$PROGRAM" --toggle --config bongocat.conf  &
NEW_PID=$!
sleep 2

if kill -0 "$NEW_PID" 2>/dev/null; then
    echo "[PASS] New process $NEW_PID started successfully via toggle"
else
    echo "[FAIL] Toggle failed to start new instance!"
    exit 1
fi

# Clean up new instance
kill -TERM "$NEW_PID"
for i in {1..10}; do
    if ! kill -0 "$NEW_PID" 2>/dev/null; then break; fi
    sleep 0.5
done
echo "[TEST] Toggle functionality test completed!"
