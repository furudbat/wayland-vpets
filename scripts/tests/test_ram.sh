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
echo "$(bloaty ./cmake-build-relwithdebinfo/bongocat-all -d compileunits --source-filter=src | sed "s|$P/||g" | sed "s|$P||g")" >> "$REPORT"
echo '```' >> "$REPORT"
echo "" >> "$REPORT"
echo "" >> "$REPORT"


echo '`bloaty ./cmake-build-relwithdebinfo/bongocat-all -d compileunits,symbols`' >> "$REPORT"
echo '```bash' >> "$REPORT"
echo "$(bloaty ./cmake-build-relwithdebinfo/bongocat-all -d compileunits,symbols --source-filter=src | sed "s|$P/||g" | sed "s|$P||g")" >> "$REPORT"
echo '```' >> "$REPORT"
echo "" >> "$REPORT"
echo "" >> "$REPORT"


echo '`bloaty ./cmake-build-relwithdebinfo-all-features/bongocat-all -d compileunits,symbols`' >> "$REPORT"
echo '```bash' >> "$REPORT"
echo "$(bloaty ./cmake-build-relwithdebinfo-all-features/bongocat-all -d compileunits,symbols --source-filter=src | sed "s|$P/||g" | sed "s|$P||g")" >> "$REPORT"
echo '```' >> "$REPORT"
echo "" >> "$REPORT"
echo "" >> "$REPORT"


echo '`bloaty -d compileunits --source-filter=src ./cmake-build-relwithdebinfo/bongocat-all -- ./cmake-build-debug/bongocat-all`' >> "$REPORT"
echo '```bash' >> "$REPORT"
echo "$(bloaty -d compileunits --source-filter=src ./cmake-build-relwithdebinfo-all-features/bongocat-all -- ./cmake-build-relwithdebinfo/bongocat-all | sed "s|$P/||g" | sed "s|$P||g")" >> "$REPORT"
echo '```' >> "$REPORT"
echo "" >> "$REPORT"
echo "" >> "$REPORT"


echo '`bloaty -d compileunits --source-filter=src ./cmake-build-relwithdebinfo/bongocat-all -- ./cmake-build-debug/bongocat-all`' >> "$REPORT"
echo '```bash' >> "$REPORT"
echo "$(bloaty -d compileunits --source-filter=src ./cmake-build-relwithdebinfo/bongocat-all -- ./cmake-build-debug/bongocat-all | sed "s|$P/||g" | sed "s|$P||g")" >> "$REPORT"
echo '```' >> "$REPORT"
echo "" >> "$REPORT"
echo "" >> "$REPORT"

echo '`bloaty ./cmake-build-relwithdebinfo-all-features/bongocat-all -d sections`' >> "$REPORT"
echo '```bash' >> "$REPORT"
echo "$(bloaty ./cmake-build-relwithdebinfo-all-features/bongocat-all -d sections)" >> "$REPORT"
echo '```' >> "$REPORT"
echo "" >> "$REPORT"
echo "" >> "$REPORT"

echo '`readelf -S ./cmake-build-relwithdebinfo-all-features/bongocat-all`' >>  "$REPORT"
echo '```bash' >> "$REPORT"
echo "$(readelf -S ./cmake-build-relwithdebinfo-all-features/bongocat-all)" >>  "$REPORT"
echo '```' >> "$REPORT"
echo "" >> "$REPORT"
echo "" >> "$REPORT"

echo '`readelf -l ./cmake-build-relwithdebinfo-all-features/bongocat-all`' >>  "$REPORT"
echo '```bash' >> "$REPORT"
echo "$(readelf -l ./cmake-build-relwithdebinfo-all-features/bongocat-all)" >>  "$REPORT"
echo '```' >> "$REPORT"
echo "" >> "$REPORT"
echo "" >> "$REPORT"


echo '`nm -S --size-sort ./cmake-build-relwithdebinfo-all-features/bongocat-all | tail -100`' >>  "$REPORT"
echo '```bash' >> "$REPORT"
echo "$(nm -S --size-sort ./cmake-build-relwithdebinfo-all-features/bongocat-all | tail -100)" >>  "$REPORT"
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
OG_CONFIG=./examples/test/test.bongocat.conf
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


PMAP_TABLE="# pmaps

"

# Group by build type
for group in release minsizerel relwithdebinfo; do
    echo "## $(tr '[:lower:]' '[:upper:]' <<< ${group:0:1})${group:1}" >> "$REPORT"
    echo "" >> "$REPORT"
    echo "| Variant | Binary Size | Peak RAM | Avg. RAM | Median RAM |" >> "$REPORT"
    echo "|---------|-------------|----------|----------|------------|" >> "$REPORT"

    find ./cmake-build-* -type f -executable -name "bongocat*" | grep -i "$group" | while read -r binary; do
        size=$(convert_file_size "$binary")
        echo "Testing $binary (size $size)..."

        # Start binary normally
        "$binary" --config "$CONFIG" --ignore-running &
        PID=$!
        echo "Binary PID: $PID"

        RAM_LOG=$(mktemp)
        # Monitor RAM in background
        (
            while kill -0 "$PID" 2>/dev/null; do
                awk '/VmRSS:/ {print $2}' /proc/$PID/status 2>/dev/null
                sleep 0.25
            done
        ) > "$RAM_LOG" &
        MONITOR_PID=$!

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
        sleep 5
        echo "[INFO] Set Sprite Sheet: Rover"
        sed -i -E 's/^invert_color=[0-9]+/invert_color=0/' "$CONFIG"
        sed -i -E 's/^animation_name=[:A-Za-z0-9_. ]+/animation_name=Rover/' "$CONFIG"
        echo "[INFO] Send SIGUSR2"
        kill -USR2 "$PID" # Reload config
        sleep 5
        echo "[INFO] Set Sprite Sheet: pkmn:ho_oh"
        sed -i -E 's/^invert_color=[0-9]+/invert_color=0/' "$CONFIG"
        sed -i -E 's/^animation_name=[:A-Za-z0-9_. ]+/animation_name=pkmn:ho_oh/' "$CONFIG"
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
        sleep 2
        echo "[INFO] Set Sprite Sheet: pmd:volcanion"
        sed -i -E 's/^invert_color=[0-9]+/invert_color=0/' "$CONFIG"
        sed -i -E 's/^animation_name=[:A-Za-z0-9_. ]+/animation_name=pmd:volcanion/' "$CONFIG"
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

        #sed -i -E 's/^cat_height=[0-9]+/cat_height=64/' "$CONFIG"
        #sed -i -E 's/^overlay_height=[0-9]+/overlay_height=128/' "$CONFIG"

        echo "[TEST] Change animation sprite"
        echo "[INFO] Set animation_name..."
        sed -i -E 's/^animation_name=.*/animation_name=dm20:Koromon/' "$CONFIG"
        sed -i -E 's/^invert_color=[0-9]+/invert_color=1/' "$CONFIG"
        sed -i -E 's/^evolution=.*/evolution=normal/' "$CONFIG"
        sed -i -E 's/^evolution_speed_factor=.*/evolution_speed_factor=3600.0/' "$CONFIG"
        echo "[INFO] Send SIGUSR2"
        kill -USR2 "$PID" # Reload config
        sleep 40

        echo "[TEST] Change animation sprite"
        echo "[INFO] Set animation_name..."
        sed -i -E 's/^animation_name=.*/animation_name=Koromon/' "$CONFIG"
        sed -i -E 's/^invert_color=[0-9]+/invert_color=0/' "$CONFIG"
        sed -i -E 's/^evolution=.*/evolution=normal/' "$CONFIG"
        sed -i -E 's/^evolution_speed_factor=.*/evolution_speed_factor=3600.0/' "$CONFIG"
        echo "[INFO] Send SIGUSR2"
        kill -USR2 "$PID" # Reload config
        sleep 40

        #sed -i -E 's/^cat_height=[0-9]+/cat_height=72/' "$CONFIG"
        #sed -i -E 's/^overlay_height=[0-9]+/overlay_height=128/' "$CONFIG"

        echo "[TEST] Change animation sprite"
        echo "[INFO] Set animation_name..."
        sed -i -E 's/^animation_name=.*/animation_name=pkmn:bulbasaur/' "$CONFIG"
        sed -i -E 's/^invert_color=[0-9]+/invert_color=0/' "$CONFIG"
        sed -i -E 's/^evolution=.*/evolution=normal/' "$CONFIG"
        sed -i -E 's/^evolution_speed_factor=.*/evolution_speed_factor=3600.0/' "$CONFIG"
        echo "[INFO] Send SIGUSR2"
        kill -USR2 "$PID" # Reload config
        sleep 30

        #sed -i -E 's/^cat_height=[0-9]+/cat_height=96/' "$CONFIG"
        #sed -i -E 's/^overlay_height=[0-9]+/overlay_height=128/' "$CONFIG"

        echo "[TEST] Change animation sprite"
        echo "[INFO] Set animation_name..."
        sed -i -E 's/^animation_name=.*/animation_name=pmd:charmander/' "$CONFIG"
        sed -i -E 's/^invert_color=[0-9]+/invert_color=0/' "$CONFIG"
        sed -i -E 's/^evolution=.*/evolution=normal/' "$CONFIG"
        sed -i -E 's/^evolution_speed_factor=.*/evolution_speed_factor=3600.0/' "$CONFIG"
        echo "[INFO] Send SIGUSR2"
        kill -USR2 "$PID" # Reload config
        sleep 30

        # --- verify running ---
        if kill -0 "$PID" 2>/dev/null; then
            echo "[INFO] Process $PID still running!"
        else
            echo "[FAIL] Process terminated"
            exit 1
        fi

        sleep 10
        pmap_output=$(pmap -x $PID || echo "")
        ram_kib=$(measure_ram "$PID" || echo 0)
        sleep 5

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

        # Stop monitor
        #kill "$MONITOR_PID" 2>/dev/null
        #wait "$MONITOR_PID" 2>/dev/null

        avg_ram_kib=$(awk '
        {
            sum += $1
            n++
        }
        END {
            if (n > 0)
                printf "%.0f", sum / n
            else
                print 0
        }' "$RAM_LOG")

        median_ram_kib=$(awk '
        {
            samples[n++] = $1
        }
        END {
            if (n == 0) {
                print 0
                exit
            }

            # sort samples numerically
            for (i = 0; i < n; i++) {
                for (j = i + 1; j < n; j++) {
                    if (samples[i] > samples[j]) {
                        tmp = samples[i]
                        samples[i] = samples[j]
                        samples[j] = tmp
                    }
                }
            }

            if (n % 2 == 1)
                printf "%.0f", samples[int(n/2)]
            else
                printf "%.0f", (samples[n/2-1] + samples[n/2]) / 2
        }' "$RAM_LOG")

        ram=$(convert_size "$ram_kib")
        avg_ram=$(convert_size "$avg_ram_kib")
        median_ram=$(convert_size "$median_ram_kib")

        # Variant name = path relative to build dir
        variant=$(basename "$(dirname "$binary")")/$(basename "$binary")

        echo "| \`$variant\` | $size | $ram | $avg_ram | $median_ram |" >> "$REPORT"

        PMAP_TABLE="${PMAP_TABLE} **\`$variant\`**\n\`\`\`bash\n$pmap_output\n\`\`\`\n\n"

        if [ "$USE_HEAPTRACK" = true ]; then
            if ps -p $HEAPTRACK_PID > /dev/null; then
                kill -TERM "$HEAPTRACK_PID"
            fi
            echo "Heaptrack recording finished for PID $PID"
        fi

        rm "$RAM_LOG"
    done
    echo "" >> "$REPORT"
done

echo -e "$PMAP_TABLE" >> "$REPORT"

echo ""
echo "Report generated: $REPORT"
