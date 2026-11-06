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


echo '`bloaty -d compileunits --source-filter=src ./cmake-build-relwithdebinfo-all-features/bongocat-all -- ./cmake-build-relwithdebinfo/bongocat-all`' >> "$REPORT"
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

# Read a field (in KiB) from /proc/<pid>/status, e.g. VmRSS, VmHWM, RssAnon
proc_status_kib() {
    local pid="$1" field="$2"
    awk -v f="$field:" '$1 == f {print $2; found=1} END {if (!found) print 0}' "/proc/$pid/status" 2>/dev/null || echo 0
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
PID=""
MONITOR_PID=""
cleanup() {
    echo "[INFO] Cleaning up..."
    [[ -n "$MONITOR_PID" ]] && kill "$MONITOR_PID" 2>/dev/null || true
    [[ -n "$PID" ]] && kill -9 "$PID" 2>/dev/null || true
    rm -rf "$WORKDIR"
}
trap cleanup EXIT


USE_HEAPTRACK=false
HEAPTRACK_BIN=$(command -v heaptrack || true)
if [ "$USE_HEAPTRACK" = true ] && [ -z "$HEAPTRACK_BIN" ]; then
    echo "Warning: heaptrack not found, running binary without it"
    USE_HEAPTRACK=false
fi

run_test_sequence() {
    local PID="$1"
    local CONFIG="$2"

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
      sleep 0.5
      printf '\e' > "/proc/$PID/fd/0"
      sleep 0.5
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
    sleep 4
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
    sleep 3


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
    sleep 15

    echo "[TEST] Change animation sprite"
    echo "[INFO] Set animation_name..."
    sed -i -E 's/^animation_name=.*/animation_name=Koromon/' "$CONFIG"
    sed -i -E 's/^invert_color=[0-9]+/invert_color=0/' "$CONFIG"
    sed -i -E 's/^evolution=.*/evolution=normal/' "$CONFIG"
    sed -i -E 's/^evolution_speed_factor=.*/evolution_speed_factor=3600.0/' "$CONFIG"
    echo "[INFO] Send SIGUSR2"
    kill -USR2 "$PID" # Reload config
    sleep 20

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
    sleep 10
}

PMAP_TABLE="# pmaps

"

# Group by build type
for group in release; do
    echo "## $(tr '[:lower:]' '[:upper:]' <<< ${group:0:1})${group:1}" >> "$REPORT"
    echo "" >> "$REPORT"
    echo "| Variant | Binary Size | Peak RAM | Avg. RAM | Median RAM | End RAM |" >> "$REPORT"
    echo "|---------|-------------|----------|----------|------------|---------|" >> "$REPORT"

    #./cmake-build-release-all-features \
    #./cmake-build-release-preload-assets \
    #./cmake-build-release-preload-assets-svg \
    #./cmake-build-relwithdebinfo \
    while read -r binary; do
        size=$(convert_file_size "$binary")
        echo "Testing $binary (size $size)..."

        # Every binary starts from the same, unmodified config
        cp "$OG_CONFIG" "$CONFIG"

        # Start binary normally
        "$binary" --config "$CONFIG" --ignore-running &
        PID=$!
        echo "Binary PID: $PID"

        RAM_LOG=$(mktemp)

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

        run_test_sequence "$PID" "$CONFIG"

        # --- verify running ---
        if kill -0 "$PID" 2>/dev/null; then
            echo "[INFO] Process $PID still running!"
        else
            echo "[FAIL] Process terminated"
            exit 1
        fi

        # Stop sampling: avg/median only cover the test sequence, not the shutdown
        kill "$MONITOR_PID" 2>/dev/null || true
        wait "$MONITOR_PID" 2>/dev/null || true
        MONITOR_PID=""

        # VmHWM = kernel RSS high-water mark (catches peaks between samples)
        hwm_kib=$(proc_status_kib "$PID" VmHWM)
        end_ram_kib=$(proc_status_kib "$PID" VmRSS)

        echo "[INFO] Capturing pmap for PID $PID"
        pmap_output=$(pmap -x "$PID" 2>&1 || true)

        # --- send SIGTERM ---
        echo "[INFO] Sending SIGTERM..."
        kill -TERM "$PID" 2>/dev/null || true
        sleep 5

        echo "[INFO] Wait for TERM"
        for i in {1..5}; do
            if ! kill -0 "$PID" 2>/dev/null; then
                break
            fi
            sleep 1
        done

        if kill -0 "$PID" 2>/dev/null; then
            echo "[FAIL] Process $PID still running!"
            kill -9 "$PID" 2>/dev/null || true
        else
            echo "[PASS] Process terminated successfully"
        fi

        # drop empty/non-numeric samples (process starting/exiting)
        grep -E '^[0-9]+$' "$RAM_LOG" > "$RAM_LOG.clean" || true

        max_sample_kib=$(sort -n "$RAM_LOG.clean" | tail -n 1)
        max_sample_kib=${max_sample_kib:-0}
        ram_kib=$(( hwm_kib > max_sample_kib ? hwm_kib : max_sample_kib ))

        avg_ram_kib=$(awk '{ sum += $1; n++ } END { if (n > 0) printf "%.0f", sum / n; else print 0 }' "$RAM_LOG.clean")

        median_ram_kib=$(sort -n "$RAM_LOG.clean" | awk '
            { v[n++] = $1 }
            END {
                if (n == 0) { print 0; exit }
                if (n % 2 == 1) printf "%.0f", v[int(n/2)]
                else            printf "%.0f", (v[n/2-1] + v[n/2]) / 2
            }')

        ram=$(convert_size "$ram_kib")
        end_ram=$(convert_size "$end_ram_kib")
        avg_ram=$(convert_size "$avg_ram_kib")
        median_ram=$(convert_size "$median_ram_kib")

        variant=$(basename "$(dirname "$binary")")/$(basename "$binary")


        echo "| \`$variant\` | $size | $ram | $avg_ram | $median_ram | $end_ram |" >> "$REPORT"

        PMAP_TABLE+="**\`$variant\`**\n"
        PMAP_TABLE+='```bash\n'
        PMAP_TABLE+="$pmap_output"
        PMAP_TABLE+='\n```\n\n'

        rm -f "$RAM_LOG" "$RAM_LOG.clean"
        PID=""
    done < <(
        find ./cmake-build-release \
             ./cmake-build-release-all-features \
             ./cmake-build-release-preload-assets \
             ./cmake-build-release-preload-assets-svg \
             ./cmake-build-relwithdebinfo \
            -type f -executable \
            \( -name "bongocat" \
            -o -name "bongocat-ms-agent" \
            -o -name "bongocat-all" \
            -o -name "bongocat-pkmn" \) | sort
    )
    echo "" >> "$REPORT"
done

echo -e "$PMAP_TABLE" >> "$REPORT"

echo ""
echo "Report generated: $REPORT"
