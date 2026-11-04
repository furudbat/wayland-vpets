#!/usr/bin/env bash

set -euo pipefail

#make debug
#PROGRAM="./cmake-build-debug-all-assets-colored-preload/bongocat"
#PROGRAM="./cmake-build-debug/bongocat-all"
PROGRAM="./cmake-build-debug-all-features/bongocat-all"
#PROGRAM="./build/bongocat-all"

WORKDIR=$(mktemp -d)
CONFIG_1="$WORKDIR/test.bongocat.conf"  # config file to modify
OG_CONFIG_1=./examples/test/test.bongocat.conf
cp $OG_CONFIG_1 $CONFIG_1

CONFIG_2="$WORKDIR/invalid.test.bongocat.conf"  # config file to modify
OG_CONFIG_2=./examples/test/invalid.test.bongocat.conf
cp $OG_CONFIG_2 $CONFIG_2

# --- trap cleanup ---
cleanup() {
    echo "[TEST] Cleaning up..."
    cp $OG_CONFIG_1 $CONFIG_1
    cp $OG_CONFIG_2 $CONFIG_2
    rm -rf "$WORKDIR"
}
trap cleanup EXIT


echo "[TEST] Starting program with valid config..."
"$PROGRAM" --check-config --config "$CONFIG_1" --ignore-running
sleep 10
RET=$?
echo "[INFO] Program exit code: $RET"
echo "[INFO] Test Program: ${PROGRAM} --check-config --config $CONFIG_1"
if [ "$RET" -eq 0 ]; then
    echo "[PASS] Configuration check successful"
else
    echo "[FAIL] Configuration check failed (exit code: $RET)"
    exit 1
fi


echo "[TEST] Starting program with invalid config..."
"$PROGRAM" --check-config --config "$CONFIG_2" --ignore-running
sleep 10
RET=$?
echo "[INFO] Program exit code: $RET"
echo "[INFO] Test Program: ${PROGRAM} --check-config --config $CONFIG_2"
if [ "$RET" -eq 0 ]; then
    echo "[PASS] Configuration check successful"
else
    echo "[FAIL] Configuration check failed (exit code: $RET)"
    exit 1
fi
