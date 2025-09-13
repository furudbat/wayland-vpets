#!/usr/bin/env bash

set -euo pipefail


REPORT="ram_report.md"

> "$REPORT"
echo "# Memory Report" >> "$REPORT"
echo "" >> "$REPORT"

echo "## Binary Size" >> "$REPORT"
echo "" >> "$REPORT"

P="$(pwd)"

echo '`bloaty ./cmake-build-relwithdebinfo-all-assets-colored-preload/bongocat -d compileunits`' >> "$REPORT"
echo '```bash' >> "$REPORT"
echo "$(bloaty ./cmake-build-relwithdebinfo-all-assets-colored-preload/bongocat -d compileunits --source-filter=src | sed "s|$P/||g" | sed "s|$P||g")" >> "$REPORT"
echo '```' >> "$REPORT"
echo "" >> "$REPORT"
echo "" >> "$REPORT"



echo '`bloaty ./cmake-build-relwithdebinfo-all-assets-colored-preload/bongocat -d compileunits,symbols`' >> "$REPORT"
echo '```bash' >> "$REPORT"
echo "$(bloaty ./cmake-build-relwithdebinfo-all-assets-colored-preload/bongocat -d compileunits,symbols --source-filter=src | sed "s|$P/||g" | sed "s|$P||g")" >> "$REPORT"
echo '```' >> "$REPORT"
echo "" >> "$REPORT"
echo "" >> "$REPORT"



echo '`bloaty -d compileunits --source-filter=src ./cmake-build-relwithdebinfo/bongocat -- ./cmake-build-debug/bongocat`' >> "$REPORT"
echo '```bash' >> "$REPORT"
echo "$(bloaty -d compileunits --source-filter=src ./cmake-build-relwithdebinfo/bongocat -- ./cmake-build-debug/bongocat | sed "s|$P/||g" | sed "s|$P||g")" >> "$REPORT"
echo '```' >> "$REPORT"
echo "" >> "$REPORT"
echo "" >> "$REPORT"

echo '```bash' >> "$REPORT"
echo "$(du -h ./cmake-build-*/bongocat*)" >>  "$REPORT"
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


# Group by build type
for group in release minsizerel relwithdebinfo debug; do
    echo "## $(tr '[:lower:]' '[:upper:]' <<< ${group:0:1})${group:1}" >> "$REPORT"
    echo "" >> "$REPORT"
    echo "| Variant | Binary Size | Peak RAM |" >> "$REPORT"
    echo "|---------|-------------|----------|" >> "$REPORT"

    find ./cmake-build-* -type f -executable -name "bongocat*" | grep -i "$group" | while read -r binary; do
        size=$(convert_file_size "$binary")
        echo "Testing $binary (size $size)..."

        # Run binary
        "$binary" --watch-config --config debug.bongocat.conf &
        PID=$!

        # Give it time to start
        sleep 10
        echo "[INFO] Disable sleep"
        sed -i 's/^enable_scheduled_sleep=1/enable_scheduled_sleep=0/' debug.bongocat.conf  # Reload config
        sleep 5
        if [[ -f "/proc/$PID/fd/0" ]]; then
          echo "[INFO] Send stdin"
          printf '\e' > "/proc/$PID/fd/0"
          sleep 5
        fi
        echo "[TEST] Send SIGUSR2"
        kill -USR2 "$PID"
        sleep 5

        ram_kib=$(measure_ram "$PID" || echo 0)

        # --- send SIGTERM ---
        echo "[INFO] Sending SIGTERM..."
        kill -TERM "$PID"
        sleep 10

        echo "[INFO] Wait for TERM"
        # wait up to 5 seconds
        for i in {1..10}; do
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

        ram=$(convert_size "$ram_kib")

        # Variant name = path relative to build dir
        variant=$(basename "$(dirname "$binary")")/$(basename "$binary")

        echo "| \`$variant\` | $size | $ram |" >> "$REPORT"
    done
    echo "" >> "$REPORT"
done

echo ""
echo "Report generated: $REPORT"
