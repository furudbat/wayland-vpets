#!/usr/bin/env bash

set -euo pipefail

ctest --test-dir cmake-build-debug --output-on-failure

echo "--- Test 1 ---"
./scripts/tests/test_bongocat.sh
echo "--- Test 2 ---"
./scripts/tests/test_bongocat_2.sh
echo "--- Test 3 ---"
./scripts/tests/test_bongocat_3.sh
echo "--- Test 4 ---"
./scripts/tests/test_bongocat_4.sh
echo "--- Test 5 ---"
./scripts/tests/test_bongocat_5.sh
echo "--- Test 6 ---"
./scripts/tests/test_bongocat_6.sh
echo "--- Test 7 ---"
./scripts/tests/test_bongocat_7.sh
echo "--- Test 8 ---"
./scripts/tests/test_bongocat_8.sh
echo "--- Test 9 ---"
./scripts/tests/test_bongocat_9.sh
echo "--- Test 11 ---"
./scripts/tests/test_bongocat_11.sh
echo "--- Test 12 ---"
./scripts/tests/test_bongocat_12.sh
echo "--- Test 13 ---"
./scripts/tests/test_bongocat_13.sh
echo "--- Test 14 ---"
./scripts/tests/test_bongocat_14.sh
echo "--- Test 15 ---"
./scripts/tests/test_bongocat_15.sh
echo "--- Test 16 ---"
./scripts/tests/test_bongocat_16.sh
echo "--- Test 20 ---"
./scripts/tests/test_bongocat_20.sh

echo "--- Integration Test done ---"

echo "--- Test RAM --"
./scripts/tests/test_nix_build_docker.sh


./scripts/tests/test_ram.sh
