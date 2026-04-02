#!/usr/bin/env bash
set -euo pipefail

#PROGRAM="./cmake-build-debug/bongocat"
PROGRAM="./build/bongocat"

if [[ ! -x $PROGRAM ]]; then
  echo "Error: ./build/bongocat not found. Build first with: make"
  exit 1
fi

if [[ -z "${WAYLAND_DISPLAY:-}" ]]; then
  echo "Skipping toggle test: WAYLAND_DISPLAY is not set."
  exit 0
fi

if [[ -z "${XDG_RUNTIME_DIR:-}" || ! -S "${XDG_RUNTIME_DIR}/${WAYLAND_DISPLAY}" ]]; then
  echo "Skipping toggle test: Wayland socket is not available."
  exit 0
fi

show_processes() {
  if ! pgrep -x -a bongocat; then
    echo "No bongocat processes found"
  fi
}

is_running() {
  pgrep -x bongocat >/dev/null 2>&1
}

echo "Testing bongocat toggle functionality..."
echo

# Start initial instance
if [[ $# -ge 1 ]]; then
  TOGGLE_PID="$1"
  echo "Using provided PID = $TOGGLE_PID"
else
  if is_running; then
    echo "Pre-clean: existing bongocat instance detected, toggling it off first."
    $PROGRAM --toggle --config bongocat.conf.example || true
    sleep 1
  fi

  echo "1. Starting bongocat with --toggle (should start since not running):"
  "$PROGRAM" --toggle --config bongocat.conf.example &
  TOGGLE_PID=$!
  echo "Program PID = $TOGGLE_PID"
  sleep 2

  if kill -0 "$NEW_PID" 2>/dev/null; then
    echo "New process $NEW_PID started successfully via toggle"
  else
    echo "Skipping toggle test: bongocat could not start (Wayland unavailable)."
    exit 1
  fi
  sleep 2
fi


echo
echo "2. Checking if bongocat is running:"
show_processes

echo
echo "3. Toggling bongocat off (should stop the running instance):"
$PROGRAM --toggle --config bongocat.conf.example
sleep 1

echo
echo "4. Checking if bongocat is still running:"
show_processes

echo
echo "5. Toggling bongocat on again (should start since not running):"
$PROGRAM --toggle --config bongocat.conf.example
sleep 2

echo
echo "6. Final check - bongocat should be running:"
show_processes

echo
echo "7. Cleaning up - stopping bongocat:"
$PROGRAM --toggle --config bongocat.conf.example || true

echo
echo "Toggle functionality test completed!"