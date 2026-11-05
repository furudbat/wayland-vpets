#!/usr/bin/env bash

set -euo pipefail

#make debug
#PROGRAM="./cmake-build-debug-all-assets-colored-preload/bongocat"
#PROGRAM="./cmake-build-debug-all-assets-preload/bongocat-all"
PROGRAM="./cmake-build-debug/bongocat-all"
#PROGRAM="./build/bongocat-all"

BINARY="$PROGRAM"
TARGET_GROUP="input"
DUMMY_USER="bongocattest"
DUMMY_GROUP="bongocattestgrp"
# Identify original non-root user and group for cleanup
ORIG_USER="${SUDO_USER:-$USER}"
ORIG_GROUP=$(id -gn "$ORIG_USER")
# Check for root privileges (required for chown and setting setgid bits)
if [ "$EUID" -ne 0 ]; then
    echo "[INFO] This script needs root privileges to set up setgid permissions. Rerunning with sudo..."
    exec sudo "$0" "$@"
fi
# Identify original non-root user and group for cleanup
ORIG_USER="${SUDO_USER:-$USER}"
ORIG_GROUP=$(id -gn "$ORIG_USER")
# Capture the real user's environment variables needed for Wayland/XDG runtime
ORIG_XDG_RUNTIME_DIR=$(eval echo ~"$ORIG_USER")
# If SUDO_USER is set, fetch their actual XDG_RUNTIME_DIR or fallback to standard path (/run/user/UID)
if [ -n "$SUDO_USER" ]; then
    ORIG_UID=$(id -u "$SUDO_USER")
    ORIG_XDG_RUNTIME_DIR="/run/user/$ORIG_UID"
fi
# Verify target group exists on the system
if ! getent group "$TARGET_GROUP" > /dev/null 2>&1; then
    echo "[WARN]: Group '$TARGET_GROUP' does not exist. Defaulting to user group."
    TARGET_GROUP="$ORIG_GROUP"
fi

# Create a isolated dummy user that is NOT part of the 'input' group
echo "[INFO] Creating isolated test user '$DUMMY_USER'..."
groupadd "$DUMMY_GROUP" 2>/dev/null || true
useradd -m -g "$DUMMY_GROUP" -s /bin/bash "$DUMMY_USER" 2>/dev/null || true

WORKDIR=$(sudo -u "$DUMMY_USER" mktemp -d)
CONFIG="$WORKDIR/test.bongocat.conf"  # config file to modify
OG_CONFIG=./examples/test/test4.bongocat.conf
sudo -u "$DUMMY_USER" cp $OG_CONFIG $CONFIG

echo "[INFO] Configuring binary permissions (root:$TARGET_GROUP, setgid 2755)..."
chown "$DUMMY_USER:$DUMMY_GROUP" "$CONFIG"
chmod 777 "$CONFIG"
chown root:"$TARGET_GROUP" "$BINARY"
chmod 2755 "$BINARY"

echo "[INFO] Verifying file permissions and setgid bit:"
ls -l "$BINARY"

# --- trap cleanup ---
cleanup() {
    echo "[TEST] Cleaning up..."
    kill -9 "$PID" 2>/dev/null || true
    echo -e "[INFO] Reverting binary permissions and ownership..."
    if [ -f "$BINARY" ]; then
        chown "$ORIG_USER:$ORIG_GROUP" "$BINARY"
        chmod 755 "$BINARY"
        echo "[INFO] Binary restored with permissions 755."
    fi
    cp $OG_CONFIG $CONFIG
    rm -rf "$WORKDIR"
    echo "[INFO] Removing dummy user and group ($DUMMY_USER)..."
    userdel -r "$DUMMY_USER" 2>/dev/null || true
    groupdel "$DUMMY_GROUP" 2>/dev/null || true
}
trap cleanup EXIT

# FIXME: dummyuser without input group and without wayland (session) vs. current user with input group and with wayland (session)
#        For the test I need a user without input group and with wayland (session; best case the current wayland session for testing)
# TODO: add /etc/udev/rules.d/bongocat.rules and use bongocat group

if [[ $# -ge 1 ]]; then
    PID="$1"
    CONFIG="$2"
    cp $CONFIG "${CONFIG}.bak"
    OG_CONFIG="${CONFIG}.bak"
    echo "[TEST] Using provided PID = $PID"
else
    # Inside your script, replace the program execution block with this:
    echo "[TEST] Starting program as isolated user '$DUMMY_USER'..."
    set +e
    # Create a writable runtime dir for the test user
    TEST_RUNTIME_DIR="$WORKDIR/runtime"
    mkdir -p "$TEST_RUNTIME_DIR"
    chown -R "$DUMMY_USER:$DUMMY_GROUP" "$TEST_RUNTIME_DIR"
    chmod 700 "$TEST_RUNTIME_DIR"

    # Execute with the corrected XDG_RUNTIME_DIR
    sudo -u "$DUMMY_USER" XDG_RUNTIME_DIR="$TEST_RUNTIME_DIR" "$PROGRAM" --config "$CONFIG" --ignore-running &
    PID=$!
    set -e
    echo "[TEST] Program PID = $PID"
    sleep 5
fi

# --- verify running ---
if kill -0 "$PID" 2>/dev/null; then
    echo "[PASS] Process $PID still running!"
else
    echo "[FAIL] Process terminated"
    exit 1
fi

echo "[INFO] Test Program: ${PROGRAM} --config $CONFIG (pid=${PID})"

echo "[TEST] Change hotplug_scan_interval settings"
echo "[INFO] Set hotplug_scan_interval"
sed -i -E 's/^hotplug_scan_interval=[0-9]+/hotplug_scan_interval=30/' "$CONFIG"
echo "[INFO] Send SIGUSR2"
kill -USR2 "$PID" # Reload config
sleep 10
if [[ -f "/proc/$PID/fd/0" ]]; then
  # --- simulate pressing ESC ---
  echo "[TEST] Sending ESC key..."
  echo "[INFO] Send stdin"
  printf '\e' > /proc/$PID/fd/0
  sleep 5
  echo "[INFO] Send stdin"
  printf '\e' > /proc/$PID/fd/0
  sleep 1
  # a bit of a spam
  echo "[INFO] Spam stdin"
  printf '\e' > /proc/$PID/fd/0
  printf '\e' > /proc/$PID/fd/0
  printf '\e' > /proc/$PID/fd/0
  printf '\e' > /proc/$PID/fd/0
  sleep 5
  echo "[INFO] Spam stdin slower"
  printf '\e' > /proc/$PID/fd/0
  sleep 1
  printf '\e' > /proc/$PID/fd/0
  sleep 1
  printf '\e' > /proc/$PID/fd/0
  sleep 1
  printf '\e' > /proc/$PID/fd/0
  sleep 3
fi
# --- verify running ---
if kill -0 "$PID" 2>/dev/null; then
    echo "[PASS] Process $PID still running!"
else
    echo "[FAIL] Process terminated"
    exit 1
fi
echo "[INFO] Set hotplug_scan_interval"
sed -i -E 's/^hotplug_scan_interval=[0-9]+/hotplug_scan_interval=0/' "$CONFIG"
echo "[INFO] Send SIGUSR2"
kill -USR2 "$PID" # Reload config
sleep 10
if [[ -f "/proc/$PID/fd/0" ]]; then
  # --- simulate pressing ESC ---
  echo "[TEST] Sending ESC key..."
  echo "[INFO] Send stdin"
  printf '\e' > /proc/$PID/fd/0
  sleep 5
  echo "[INFO] Send stdin"
  printf '\e' > /proc/$PID/fd/0
  sleep 1
  # a bit of a spam
  echo "[INFO] Spam stdin"
  printf '\e' > /proc/$PID/fd/0
  printf '\e' > /proc/$PID/fd/0
  printf '\e' > /proc/$PID/fd/0
  printf '\e' > /proc/$PID/fd/0
  sleep 5
  echo "[INFO] Spam stdin slower"
  printf '\e' > /proc/$PID/fd/0
  sleep 1
  printf '\e' > /proc/$PID/fd/0
  sleep 1
  printf '\e' > /proc/$PID/fd/0
  sleep 1
  printf '\e' > /proc/$PID/fd/0
  sleep 3
fi
# --- verify running ---
if kill -0 "$PID" 2>/dev/null; then
    echo "[PASS] Process $PID still running!"
else
    echo "[FAIL] Process terminated"
    exit 1
fi

sleep 20

# --- send SIGTERM ---
echo "[TEST] Sending SIGTERM..."
kill -TERM "$PID"
sleep 10
echo "[INFO] Wait for TERM"
# wait up to 5 seconds
for i in {1..5}; do
    if ! kill -0 "$PID" 2>/dev/null; then
        break
    fi
    sleep 1
done

# --- verify not running ---
if kill -0 "$PID" 2>/dev/null; then
    echo "[FAIL] Process $PID still running!"
    kill -9 "$PID" 2>/dev/null
    exit 1
else
    echo "[PASS] Process terminated successfully"
fi
