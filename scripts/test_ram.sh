#!/usr/bin/env bash

set -euo pipefail


REPORT="ram_report.md"

> "$REPORT"
echo "# Memory Report" >> "$REPORT"
echo "" >> "$REPORT"

echo "## Binary Size" >> "$REPORT"
echo "" >> "$REPORT"

P="$(pwd)"


echo '`bloaty ./cmake-build-relwithdebinfo/bongocat-all -d compileunits`' >> "$REPORT"
echo '```bash' >> "$REPORT"
echo "$(bloaty ./cmake-build-relwithdebinfo/bongocat-all -d compileunits,symbols --source-filter=src | sed "s|$P/||g" | sed "s|$P||g")" >> "$REPORT"
echo '```' >> "$REPORT"
echo "" >> "$REPORT"
echo "" >> "$REPORT"


echo '`bloaty ./cmake-build-relwithdebinfo/bongocat-all -d compileunits,symbols`' >> "$REPORT"
echo '```bash' >> "$REPORT"
echo "$(bloaty ./cmake-build-relwithdebinfo/bongocat-all -d compileunits,symbols --source-filter=src | sed "s|$P/||g" | sed "s|$P||g")" >> "$REPORT"
echo '```' >> "$REPORT"
echo "" >> "$REPORT"
echo "" >> "$REPORT"

echo '`bloaty -d compileunits --source-filter=src ./cmake-build-relwithdebinfo/bongocat-all -- ./cmake-build-debug/bongocat-all`' >> "$REPORT"
echo '```bash' >> "$REPORT"
echo "$(bloaty -d compileunits --source-filter=src ./cmake-build-relwithdebinfo/bongocat-all -- ./cmake-build-debug/bongocat-all | sed "s|$P/||g" | sed "s|$P||g")" >> "$REPORT"
echo '```' >> "$REPORT"
echo "" >> "$REPORT"
echo "" >> "$REPORT"



echo '`du -h ./cmake-build-*/bongocat* --exclude=*.1 --exclude=*.5`' >>  "$REPORT"
echo '```bash' >> "$REPORT"
echo "$(du -h ./cmake-build-*/bongocat* --exclude='*.1' --exclude='*.5')" >>  "$REPORT"
echo '```' >> "$REPORT"
echo "" >> "$REPORT"
echo "" >> "$REPORT"


echo "## RAM Usage" >> "$REPORT"
echo "" >> "$REPORT"

measure_ram() {
    local pid="$1"
    local max_rss=0
    for i in {1..10}; do
        if ps -p "$pid" -o rss= | grep -q '[0-9]'; then
            local rss=$(ps -p "$pid" -o rss= | awk '{print $1}')
            (( rss > max_rss )) && max_rss=$rss
        else
            break
        fi
        sleep 1
    done
    echo "$max_rss"
}

convert_size() {
    # Convert KiB to MB with 1 decimal
    local kib="$1"
    if (( kib == 0 )); then
        echo "-"
    else
        awk -v kib="$kib" 'BEGIN { printf "%.1f MB", kib / 1024 }'
    fi
}

convert_file_size() {
    # Normalize binary file size using du -k
    local f="$1"
    local kib=$(du -k "$f" | awk '{print $1}')
    if (( kib < 1024 )); then
        echo "${kib} KB"
    else
        awk -v kib="$kib" 'BEGIN { printf "%.1f MB", kib / 1024 }'
    fi
}

WORKDIR=$(mktemp -d)
CONFIG="$WORKDIR/test.bongocat.conf"  # config file to modify
OG_CONFIG=./examples/test.bongocat.conf
cp $OG_CONFIG $CONFIG
# --- trap cleanup ---
cleanup() {
    echo "[INFO] Cleaning up..."
    #kill -9 "$PID" 2>/dev/null || true
    rm -rf "$WORKDIR"
}
trap cleanup EXIT


USE_HEAPTRACK=false
HEAPTRACK_BIN=$(command -v heaptrack || true)
if [ "$USE_HEAPTRACK" = true ] && [ -z "$HEAPTRACK_BIN" ]; then
    echo "Warning: heaptrack not found, running binary without it"
    USE_HEAPTRACK=false
fi

# Group by build type
for group in release minsizerel relwithdebinfo debug; do
    echo "## $(tr '[:lower:]' '[:upper:]' <<< ${group:0:1})${group:1}" >> "$REPORT"
    echo "" >> "$REPORT"
    echo "| Variant | Binary Size | Peak RAM |" >> "$REPORT"
    echo "|---------|-------------|----------|" >> "$REPORT"

    find ./cmake-build-* -type f -executable -name "bongocat*" | grep -i "$group" | while read -r binary; do
        size=$(convert_file_size "$binary")
        echo "Testing $binary (size $size)..."

        # Start binary normally
        "$binary" --config "$CONFIG" --ignore-running &
        PID=$!
        echo "Binary PID: $PID"

        if [ "$USE_HEAPTRACK" = true ]; then
            BINARY_NAME=$(basename "$binary")
            mkdir -p build
            HEAPTRACK_FILE="build/heaptrack.${group}.${BINARY_NAME}.$(date +%s).gz"
            echo "Attaching heaptrack with --use-inject, output: $HEAPTRACK_FILE"

            # Wait a bit for the binary to initialize
            sleep 1

            #echo 0 | sudo tee /proc/sys/kernel/yama/ptrace_scope

            # Attach heaptrack to the running process
            "$HEAPTRACK_BIN" --use-inject --record-only -p "$PID" -o "$HEAPTRACK_FILE" &
            HEAPTRACK_PID=$!
        fi

        # Give it time to start
        sleep 5
        echo "[INFO] Update Config"
        sed -i 's/^enable_scheduled_sleep=1/enable_scheduled_sleep=0/' "$CONFIG"
        echo "[INFO] Set Sprite Sheet: bongocat"
        sed -i -E 's/^invert_color=[0-9]+/invert_color=0/' "$CONFIG"
        sed -i -E 's/^animation_name=[:A-Za-z0-9_. ]+/animation_name=Bongocat/' "$CONFIG"
        echo "[INFO] Send SIGUSR2"
        kill -USR2 "$PID" # Reload config
        sleep 2
        if [[ -f "/proc/$PID/fd/0" ]]; then
          echo "[INFO] Send stdin"
          printf '\e' > "/proc/$PID/fd/0"
          sleep 1
          printf '\e' > "/proc/$PID/fd/0"
          sleep 1
        fi
        sleep 2

        echo "[INFO] Load biggest assets"
        echo "[INFO] Set Sprite Sheet: Links"
        sed -i -E 's/^invert_color=[0-9]+/invert_color=0/' "$CONFIG"
        sed -i -E 's/^animation_name=[:A-Za-z0-9_. ]+/animation_name=Links/' "$CONFIG"
        echo "[INFO] Send SIGUSR2"
        kill -USR2 "$PID" # Reload config
        sleep 2
        echo "[INFO] Set Sprite Sheet: pkmn:dialga"
        sed -i -E 's/^invert_color=[0-9]+/invert_color=0/' "$CONFIG"
        sed -i -E 's/^animation_name=[:A-Za-z0-9_. ]+/animation_name=pkmn:dialga/' "$CONFIG"
        echo "[INFO] Send SIGUSR2"
        kill -USR2 "$PID" # Reload config
        sleep 2
        echo "[INFO] Set Sprite Sheet: dmx:Hexeblaumon"
        sed -i -E 's/^invert_color=[0-9]+/invert_color=1/' "$CONFIG"
        sed -i -E 's/^animation_name=[:A-Za-z0-9_. ]+/animation_name=dmx:Hexeblaumon/' "$CONFIG"
        echo "[INFO] Send SIGUSR2"
        kill -USR2 "$PID" # Reload config
        sleep 2
        echo "[INFO] Set Sprite Sheet: dm20:Omegamon"
        sed -i -E 's/^invert_color=[0-9]+/invert_color=1/' "$CONFIG"
        sed -i -E 's/^animation_name=[:A-Za-z0-9_. ]+/animation_name=dm20:Omegamon/' "$CONFIG"
        echo "[INFO] Send SIGUSR2"
        kill -USR2 "$PID" # Reload config
        sleep 2
        echo "[INFO] Set Sprite Sheet: dmc:Omegamon"
        sed -i -E 's/^invert_color=[0-9]+/invert_color=0/' "$CONFIG"
        sed -i -E 's/^animation_name=[:A-Za-z0-9_. ]+/animation_name=dmc:Omegamon/' "$CONFIG"
        echo "[INFO] Send SIGUSR2"
        kill -USR2 "$PID" # Reload config
        sleep 2
        echo "[INFO] Set Sprite Sheet: dm:Coronamon"
        sed -i -E 's/^invert_color=[0-9]+/invert_color=1/' "$CONFIG"
        sed -i -E 's/^animation_name=[:A-Za-z0-9_. ]+/animation_name=dm:Coronamon/' "$CONFIG"
        echo "[INFO] Send SIGUSR2"
        kill -USR2 "$PID" # Reload config
        sleep 2
        echo "[INFO] Set Sprite Sheet: Metal Greymon"
        sed -i -E 's/^invert_color=[0-9]+/invert_color=0/' "$CONFIG"
        sed -i -E 's/^animation_name=[:A-Za-z0-9_. ]+/animation_name=Metal Greymon/' "$CONFIG"
        echo "[INFO] Send SIGUSR2"
        kill -USR2 "$PID" # Reload config
        sleep 5


        echo "[TEST] CPU threshold"
        echo "[INFO] Enable CPU threshold"
        sed -i -E 's/^invert_color=[0-9]+/invert_color=1/' "$CONFIG"
        sed -i -E 's/^animation_name=[:A-Za-z0-9_. ]+/animation_name=dm20:Agumon/' "$CONFIG"
        sed -i -E 's/^update_rate=[0-9]+/update_rate=1000/' "$CONFIG"
        sed -i -E 's/^cpu_threshold=[0-9]+/cpu_threshold=30/' "$CONFIG"
        echo "[INFO] Send SIGUSR2"
        kill -USR2 "$PID" # Reload config
        sleep 2
        if command -v stress-ng >/dev/null 2>&1; then
            echo "[INFO] Running stress-ng to generate load"
            stress-ng --cpu 0 --timeout 15s --metrics-brief &
            sleep 20
        elif command -v stress >/dev/null 2>&1; then
            echo "[INFO] Running stress to generate load"
            stress --cpu "$(nproc)" --timeout 15s &
            sleep 20
        else
            echo "[WARN] No stress tool found, skipping load generation"
        fi
        echo "[INFO] Disable CPU threshold"
        sed -i -E 's/^update_rate=[0-9]+/update_rate=0/' "$CONFIG"
        sed -i -E 's/^cpu_threshold=[0-9]+/cpu_threshold=90/' "$CONFIG"
        echo "[INFO] Send SIGUSR2"
        kill -USR2 "$PID" # Reload config
        sleep 5

        # --- verify running ---
        if kill -0 "$PID" 2>/dev/null; then
            echo "[INFO] Process $PID still running!"
        else
            echo "[FAIL] Process terminated"
            exit 1
        fi

        ram_kib=$(measure_ram "$PID" || echo 0)

        # --- send SIGTERM ---
        echo "[INFO] Sending SIGTERM..."
        kill -TERM "$PID"
        sleep 7

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

        if [ "$USE_HEAPTRACK" = true ]; then
            echo "Heaptrack file generated: $HEAPTRACK_FILE"
        fi

        ram=$(convert_size "$ram_kib")

        # Variant name = path relative to build dir
        variant=$(basename "$(dirname "$binary")")/$(basename "$binary")

        echo "| \`$variant\` | $size | $ram |" >> "$REPORT"

        if [ "$USE_HEAPTRACK" = true ]; then
            if ps -p $HEAPTRACK_PID > /dev/null; then
                kill -TERM "$HEAPTRACK_PID"
            fi
            echo "Heaptrack recording finished for PID $PID"
        fi
    done
    echo "" >> "$REPORT"
done

echo ""
echo "Report generated: $REPORT"
