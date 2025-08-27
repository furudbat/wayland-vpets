echo "Testing bongocat toggle functionality..."
echo

#PROGRAM="./cmake-build-debug/bongocat"
PROGRAM="./build/bongocat"

echo "1. Starting bongocat with --toggle (should start since not running):"
$PROGRAM --toggle &
TOGGLE_PID=$!
sleep 2

echo
echo "2. Checking if bongocat is running:"
ps aux | grep bongocat | grep -v grep | grep -v test_toggle

echo
echo "3. Toggling bongocat off (should stop the running instance):"
$PROGRAM --toggle

echo
echo "4. Checking if bongocat is still running:"
ps aux | grep bongocat | grep -v grep | grep -v test_toggle || echo "No bongocat processes found - toggle worked!"

echo
echo "5. Toggling bongocat on again (should start since not running):"
$PROGRAM --toggle &
TOGGLE_PID2=$!
sleep 2

echo
echo "6. Final check - bongocat should be running:"
ps aux | grep bongocat | grep -v grep | grep -v test_toggle

echo
echo "7. Cleaning up - stopping bongocat:"
$PROGRAM --toggle

echo
echo "Toggle functionality test completed!"
