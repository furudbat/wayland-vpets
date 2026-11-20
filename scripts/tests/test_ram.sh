#!/usr/bin/env bash

set -euo pipefail

usage() {
    cat <<USAGE
Usage: $(basename "$0") [--cpu-stress] [--log-dir DIR] [-h|--help]

  --cpu-stress   Also run the CPU threshold test (generates load with stress-ng/stress).
                 Off by default. Can also be enabled with CPU_STRESS=1.
  --log-dir DIR  Where to write the logs (default: build/test_ram_logs/<timestamp>).
                 Can also be set with LOG_DIR=DIR.

Logs:
  <log-dir>/test_ram.log        everything this script prints (steps, commands, errors)
  <log-dir>/<variant>.log       stdout/stderr of each tested binary, with step markers
  <log-dir>/<variant>.conf      config as it was at the end of that binary's run
USAGE
}

CPU_STRESS="${CPU_STRESS:-0}"
LOG_DIR="${LOG_DIR:-build/test_ram_logs/$(date +%Y%m%d-%H%M%S)}"
SCRIPT_ARGS="$*"
while [[ $# -gt 0 ]]; do
    case "$1" in
        --cpu-stress) CPU_STRESS=1; shift ;;
        --no-cpu-stress) CPU_STRESS=0; shift ;;
        --log-dir) LOG_DIR="${2:?--log-dir needs a directory}"; shift 2 ;;
        -h|--help) usage; exit 0 ;;
        *) echo "Unknown option: $1" >&2; usage >&2; exit 1 ;;
    esac
done


# --- logging ---
mkdir -p "$LOG_DIR"
MAIN_LOG="$LOG_DIR/test_ram.log"
# per-binary log of the binary currently under test (empty = none)
BIN_LOG=""
# Mirror all output of this script (and of the tools it runs) into the main log
exec > >(tee -a "$MAIN_LOG") 2>&1

# log MSG...: timestamped line to stdout (-> main log) and into the current binary's log
log() {
    local line
    line="[$(date +%H:%M:%S)] $*"
    echo "$line"
    if [[ -n "$BIN_LOG" ]]; then
        echo "### $line" >> "$BIN_LOG"
    fi
}

# Log the failing command when the script stops on an error (set -e)
trap 'rc=$?; log "[ERROR] line $LINENO: \`$BASH_COMMAND\` failed (exit $rc)"' ERR

log "[INFO] test_ram.sh started: $0 $SCRIPT_ARGS"
log "[INFO] cwd=$(pwd) git=$(git rev-parse --short HEAD 2>/dev/null || echo '-') CPU_STRESS=$CPU_STRESS"
log "[INFO] Logs: $LOG_DIR"

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
    local rc=$?
    log "[INFO] Cleaning up... (exit $rc)"
    if (( rc != 0 )) && [[ -n "$BIN_LOG" && -f "$BIN_LOG" ]]; then
        log "[FAIL] Last 30 lines of $BIN_LOG:"
        tail -n 30 "$BIN_LOG"
    fi
    log "[INFO] Logs written to: $LOG_DIR"
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

# Send SIGUSR2 (reload config) and log what the config now selects
reload_config() {
    local pid="$1" config="$2"
    log "[INFO] Send SIGUSR2 to $pid ($(grep -E '^(animation_name|invert_color|update_rate|cpu_threshold|evolution|enable_antialiasing)=' "$config" | tr '\n' ' '))"
    kill -USR2 "$pid"
}

run_test_sequence() {
    local PID="$1"
    local CONFIG="$2"

    # Give it time to start
    sleep 5
    log "[INFO] Update Config"
    sed -i 's/^enable_scheduled_sleep=1/enable_scheduled_sleep=0/' "$CONFIG"
    log "[INFO] Set Sprite Sheet: bongocat"
    sed -i -E 's/^invert_color=[0-9]+/invert_color=0/' "$CONFIG"
    sed -i -E 's/^animation_name=[:A-Za-z0-9_. ]+/animation_name=Bongocat/' "$CONFIG"
    reload_config "$PID" "$CONFIG"
    sleep 2
    if [[ -f "/proc/$PID/fd/0" ]]; then
      log "[INFO] Send stdin"
      printf '\e' > "/proc/$PID/fd/0"
      sleep 0.5
      printf '\e' > "/proc/$PID/fd/0"
      sleep 0.5
    fi
    sleep 1

    log "[INFO] Load biggest assets"
    log "[INFO] Set Sprite Sheet: Links"
    sed -i -E 's/^invert_color=[0-9]+/invert_color=0/' "$CONFIG"
    sed -i -E 's/^animation_name=[:A-Za-z0-9_. ]+/animation_name=Links/' "$CONFIG"
    reload_config "$PID" "$CONFIG"
    sleep 4
    log "[INFO] Set Sprite Sheet: Rover"
    sed -i -E 's/^invert_color=[0-9]+/invert_color=0/' "$CONFIG"
    sed -i -E 's/^animation_name=[:A-Za-z0-9_. ]+/animation_name=Rover/' "$CONFIG"
    reload_config "$PID" "$CONFIG"
    sleep 4
    log "[INFO] Set Sprite Sheet: pkmn:ho_oh"
    sed -i -E 's/^invert_color=[0-9]+/invert_color=0/' "$CONFIG"
    sed -i -E 's/^animation_name=[:A-Za-z0-9_. ]+/animation_name=pkmn:ho_oh/' "$CONFIG"
    reload_config "$PID" "$CONFIG"
    sleep 3
    log "[INFO] Set Sprite Sheet: dmx:Hexeblaumon"
    sed -i -E 's/^invert_color=[0-9]+/invert_color=1/' "$CONFIG"
    sed -i -E 's/^animation_name=[:A-Za-z0-9_. ]+/animation_name=dmx:Hexeblaumon/' "$CONFIG"
    reload_config "$PID" "$CONFIG"
    sleep 2
    log "[INFO] Set Sprite Sheet: dm20:Omegamon"
    sed -i -E 's/^invert_color=[0-9]+/invert_color=1/' "$CONFIG"
    sed -i -E 's/^animation_name=[:A-Za-z0-9_. ]+/animation_name=dm20:Omegamon/' "$CONFIG"
    reload_config "$PID" "$CONFIG"
    sleep 1
    log "[INFO] Set Sprite Sheet: dmc:Omegamon"
    sed -i -E 's/^invert_color=[0-9]+/invert_color=0/' "$CONFIG"
    sed -i -E 's/^animation_name=[:A-Za-z0-9_. ]+/animation_name=dmc:Omegamon/' "$CONFIG"
    reload_config "$PID" "$CONFIG"
    sleep 2
    log "[INFO] Set Sprite Sheet: Gargomon"
    sed -i -E 's/^enable_antialiasing=[0-9]+/enable_antialiasing=0/' "$CONFIG"
    sed -i -E 's/^invert_color=[0-9]+/invert_color=0/' "$CONFIG"
    sed -i -E 's/^animation_name=.*/animation_name=Gargomon/' "$CONFIG"
    reload_config "$PID" "$CONFIG"
    sleep 2
    log "[INFO] Set Sprite Sheet: dm:Coronamon"
    sed -i -E 's/^invert_color=[0-9]+/invert_color=1/' "$CONFIG"
    sed -i -E 's/^animation_name=[:A-Za-z0-9_. ]+/animation_name=dm:Coronamon/' "$CONFIG"
    reload_config "$PID" "$CONFIG"
    sleep 1
    log "[INFO] Set Sprite Sheet: Metal Greymon"
    sed -i -E 's/^invert_color=[0-9]+/invert_color=0/' "$CONFIG"
    sed -i -E 's/^animation_name=[:A-Za-z0-9_. ]+/animation_name=Metal Greymon/' "$CONFIG"
    reload_config "$PID" "$CONFIG"
    sleep 2
    log "[INFO] Set Sprite Sheet: Arma Lizamon"
    sed -i -E 's/^invert_color=[0-9]+/invert_color=0/' "$CONFIG"
    sed -i -E 's/^animation_name=[:A-Za-z0-9_. ]+/animation_name=dmall:Arma Lizamon/' "$CONFIG"
    reload_config "$PID" "$CONFIG"
    sleep 2
    log "[INFO] Set Sprite Sheet: pmd:volcanion"
    sed -i -E 's/^invert_color=[0-9]+/invert_color=0/' "$CONFIG"
    sed -i -E 's/^animation_name=[:A-Za-z0-9_. ]+/animation_name=pmd:volcanion/' "$CONFIG"
    reload_config "$PID" "$CONFIG"
    sleep 3


    if [[ "$CPU_STRESS" == "1" ]]; then
        log "[TEST] CPU threshold"
        log "[INFO] Enable CPU threshold"
        sed -i -E 's/^invert_color=[0-9]+/invert_color=1/' "$CONFIG"
        sed -i -E 's/^animation_name=[:A-Za-z0-9_. ]+/animation_name=dm20:Agumon/' "$CONFIG"
        sed -i -E 's/^update_rate=[0-9]+/update_rate=1000/' "$CONFIG"
        sed -i -E 's/^cpu_threshold=[0-9]+/cpu_threshold=30/' "$CONFIG"
        reload_config "$PID" "$CONFIG"
        sleep 1
        if command -v stress-ng >/dev/null 2>&1; then
            log "[INFO] Running stress-ng to generate load"
            log "[CMD] stress-ng --cpu 0 --timeout 15s --metrics-brief"
            stress-ng --cpu 0 --timeout 15s --metrics-brief &
            sleep 7
        elif command -v stress >/dev/null 2>&1; then
            log "[INFO] Running stress to generate load"
            log "[CMD] stress --cpu $(nproc) --timeout 13s"
            stress --cpu "$(nproc)" --timeout 13s &
            sleep 6
    else
        log "[WARN] No stress tool found, skipping load generation"
    fi
    log "[INFO] Disable CPU threshold"
    sed -i -E 's/^update_rate=[0-9]+/update_rate=0/' "$CONFIG"
    sed -i -E 's/^cpu_threshold=[0-9]+/cpu_threshold=90/' "$CONFIG"
    reload_config "$PID" "$CONFIG"
    sleep 1
    else
        log "[INFO] Skipping CPU threshold/stress test (use --cpu-stress to enable)"
    fi

    # --- verify running ---
    if kill -0 "$PID" 2>/dev/null; then
        log "[INFO] Process $PID still running!"
    else
        log "[FAIL] Process terminated (see $BIN_LOG)"
        exit 1
    fi

    #sed -i -E 's/^cat_height=[0-9]+/cat_height=64/' "$CONFIG"
    #sed -i -E 's/^overlay_height=[0-9]+/overlay_height=128/' "$CONFIG"

    log "[TEST] Change animation sprite"
    log "[INFO] Set animation_name..."
    sed -i -E 's/^animation_name=.*/animation_name=dm20:Koromon/' "$CONFIG"
    sed -i -E 's/^invert_color=[0-9]+/invert_color=1/' "$CONFIG"
    sed -i -E 's/^evolution=.*/evolution=normal/' "$CONFIG"
    sed -i -E 's/^evolution_speed_factor=.*/evolution_speed_factor=3600.0/' "$CONFIG"
    reload_config "$PID" "$CONFIG"
    sleep 20

    log "[TEST] Change animation sprite"
    log "[INFO] Set animation_name..."
    sed -i -E 's/^animation_name=.*/animation_name=Koromon/' "$CONFIG"
    sed -i -E 's/^invert_color=[0-9]+/invert_color=0/' "$CONFIG"
    sed -i -E 's/^evolution=.*/evolution=normal/' "$CONFIG"
    sed -i -E 's/^evolution_speed_factor=.*/evolution_speed_factor=3600.0/' "$CONFIG"
    reload_config "$PID" "$CONFIG"
    sleep 20

    log "[TEST] Change animation sprite"
    log "[INFO] Set animation_name..."
    sed -i -E 's/^animation_name=.*/animation_name=Chaos Seadramon/' "$CONFIG"
    sed -i -E 's/^invert_color=[0-9]+/invert_color=0/' "$CONFIG"
    sed -i -E 's/^evolution=.*/evolution=0/' "$CONFIG"
    reload_config "$PID" "$CONFIG"
    sleep 2

    #sed -i -E 's/^cat_height=[0-9]+/cat_height=72/' "$CONFIG"
    #sed -i -E 's/^overlay_height=[0-9]+/overlay_height=128/' "$CONFIG"

    log "[TEST] Change animation sprite"
    log "[INFO] Set animation_name..."
    sed -i -E 's/^animation_name=.*/animation_name=pkmn:bulbasaur/' "$CONFIG"
    sed -i -E 's/^invert_color=[0-9]+/invert_color=0/' "$CONFIG"
    sed -i -E 's/^evolution=.*/evolution=normal/' "$CONFIG"
    sed -i -E 's/^evolution_speed_factor=.*/evolution_speed_factor=3600.0/' "$CONFIG"
    reload_config "$PID" "$CONFIG"
    sleep 30

    #sed -i -E 's/^cat_height=[0-9]+/cat_height=96/' "$CONFIG"
    #sed -i -E 's/^overlay_height=[0-9]+/overlay_height=128/' "$CONFIG"

    log "[TEST] Change animation sprite"
    log "[INFO] Set animation_name..."
    sed -i -E 's/^animation_name=.*/animation_name=pmd:charmander/' "$CONFIG"
    sed -i -E 's/^invert_color=[0-9]+/invert_color=0/' "$CONFIG"
    sed -i -E 's/^evolution=.*/evolution=normal/' "$CONFIG"
    sed -i -E 's/^evolution_speed_factor=.*/evolution_speed_factor=3600.0/' "$CONFIG"
    reload_config "$PID" "$CONFIG"
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

        # Every binary starts from the same, unmodified config
        cp "$OG_CONFIG" "$CONFIG"

        variant_name="$(basename "$(dirname "$binary")")_$(basename "$binary")"
        BIN_LOG="$LOG_DIR/$variant_name.log"
        : > "$BIN_LOG"
        log "[TEST] RAM test: $binary (size $size), log: $BIN_LOG"

        # Start binary normally, stdout/stderr into its own log
        log "[CMD] $binary --config $CONFIG --ignore-running"
        "$binary" --config "$CONFIG" --ignore-running >> "$BIN_LOG" 2>&1 &
        PID=$!
        log "[INFO] Binary PID: $PID"

        RAM_LOG=$(mktemp)

        (
            while kill -0 "$PID" 2>/dev/null; do
                awk '/VmRSS:/ {print $2}' /proc/$PID/status 2>/dev/null
                sleep 0.23
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
            log "[CMD] $HEAPTRACK_BIN --use-inject --record-only -p $PID -o $HEAPTRACK_FILE"
            "$HEAPTRACK_BIN" --use-inject --record-only -p "$PID" -o "$HEAPTRACK_FILE" >> "$LOG_DIR/$variant_name.heaptrack.log" 2>&1 &
            HEAPTRACK_PID=$!
        fi

        sleep 10 # pre-load start up ?
        run_test_sequence "$PID" "$CONFIG"

        # --- verify running ---
        if kill -0 "$PID" 2>/dev/null; then
            log "[INFO] Process $PID still running!"
        else
            log "[FAIL] Process terminated (see $BIN_LOG)"
            exit 1
        fi

        # Stop sampling: avg/median only cover the test sequence, not the shutdown
        kill "$MONITOR_PID" 2>/dev/null || true
        wait "$MONITOR_PID" 2>/dev/null || true
        MONITOR_PID=""

        # VmHWM = kernel RSS high-water mark (catches peaks between samples)
        hwm_kib=$(proc_status_kib "$PID" VmHWM)
        end_ram_kib=$(proc_status_kib "$PID" VmRSS)

        log "[INFO] Capturing pmap for PID $PID"
        pmap_output=$(pmap -x "$PID" 2>&1 || true)

        # --- send SIGTERM ---
        log "[INFO] Sending SIGTERM..."
        kill -TERM "$PID" 2>/dev/null || true
        sleep 5

        log "[INFO] Wait for TERM"
        for i in {1..5}; do
            if ! kill -0 "$PID" 2>/dev/null; then
                break
            fi
            sleep 1
        done

        if kill -0 "$PID" 2>/dev/null; then
            log "[FAIL] Process $PID still running!"
            kill -9 "$PID" 2>/dev/null || true
        else
            bin_rc=0
            wait "$PID" 2>/dev/null || bin_rc=$?
            log "[PASS] Process terminated successfully (exit code $bin_rc)"
        fi
        cp "$CONFIG" "$LOG_DIR/$variant_name.conf"
        # step markers (### ...) are ours, only look at the binary's own output
        if grep -v '^### ' "$BIN_LOG" | grep -qiE 'error|fail|assert|sanitizer|segmentation'; then
            log "[WARN] $variant_name: errors in log:"
            grep -v '^### ' "$BIN_LOG" | grep -iE 'error|fail|assert|sanitizer|segmentation' | head -n 20 || true
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

        log "[INFO] $variant_name: peak=$ram avg=$avg_ram median=$median_ram end=$end_ram"
        rm -f "$RAM_LOG" "$RAM_LOG.clean"
        PID=""
        BIN_LOG=""
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
log "[INFO] Report generated: $REPORT"
log "[INFO] Logs: $LOG_DIR"
