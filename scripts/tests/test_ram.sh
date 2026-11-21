#!/usr/bin/env bash

set -euo pipefail

usage() {
    cat <<USAGE
Usage: $(basename "$0") [--quick] [--only REGEX] [--skip REGEX] [--cpu-stress] [--log-dir DIR] [-h|--help]

  --quick        Scale the pauses of the test sequence to 25% (about 4x faster, ~35s instead of ~2min
                 per binary). Same steps, but less time per sprite/evolution, so numbers are not
                 directly comparable with full runs. Scale factor: SLEEP_SCALE=0.25.
  --only REGEX   Only test binaries whose path matches REGEX (grep -E), e.g. 'release/bongocat-all\$'
  --skip REGEX   Skip binaries whose path matches REGEX, e.g. 'preload'

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
SLEEP_SCALE="${SLEEP_SCALE:-1}"
ONLY_REGEX=""
SKIP_REGEX=""
LOG_DIR="${LOG_DIR:-build/test_ram_logs/$(date +%Y%m%d-%H%M%S)}"
SCRIPT_ARGS="$*"
while [[ $# -gt 0 ]]; do
    case "$1" in
        --cpu-stress) CPU_STRESS=1; shift ;;
        --no-cpu-stress) CPU_STRESS=0; shift ;;
        --quick) SLEEP_SCALE=0.25; shift ;;
        --only) ONLY_REGEX="${2:?--only needs a regex}"; shift 2 ;;
        --skip) SKIP_REGEX="${2:?--skip needs a regex}"; shift 2 ;;
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
log "[INFO] cwd=$(pwd) git=$(git rev-parse --short HEAD 2>/dev/null || echo '-') CPU_STRESS=$CPU_STRESS SLEEP_SCALE=$SLEEP_SCALE only='$ONLY_REGEX' skip='$SKIP_REGEX'"
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
if [[ "$SLEEP_SCALE" != "1" || -n "$ONLY_REGEX" || -n "$SKIP_REGEX" ]]; then
    echo "> Partial/quick run: SLEEP_SCALE=$SLEEP_SCALE only='$ONLY_REGEX' skip='$SKIP_REGEX' (not directly comparable with full runs)" >> "$REPORT"
    echo "" >> "$REPORT"
fi

# Read a field (in KiB) from /proc/<pid>/status, e.g. VmRSS, VmHWM, RssAnon
proc_status_kib() {
    local pid="$1" field="$2"
    awk -v f="$field:" '$1 == f {print $2; found=1} END {if (!found) print 0}' "/proc/$pid/status" 2>/dev/null || echo 0
}

# One sample "rss pss private_dirty" (KiB) from /proc/<pid>/smaps_rollup (kernel >= 4.14),
# falls back to "VmRSS 0 0" when smaps_rollup isn't available.
#   Rss           = resident pages, shared library pages counted fully (what top/htop show)
#   Pss           = proportional set size, shared pages divided by the number of processes mapping them
#   Private_Dirty = memory only this process uses and that can't be dropped (heap, stack, relocated .data.rel.ro, ...)
proc_mem_sample() {
    local pid="$1"
    if [[ -r "/proc/$pid/smaps_rollup" ]]; then
        awk '$1 == "Rss:" {r = $2} $1 == "Pss:" {p = $2} $1 == "Private_Dirty:" {d = $2}
             END {if (r != "") print r, p + 0, d + 0}' "/proc/$pid/smaps_rollup" 2>/dev/null
    else
        awk '$1 == "VmRSS:" {print $2, 0, 0}' "/proc/$pid/status" 2>/dev/null
    fi
}

# "max avg median" (KiB) of column COL in a sample file
col_stats() {
    local file="$1" col="$2"
    awk -v c="$col" '{print $c}' "$file" | sort -n | awk '
        { v[n++] = $1; sum += $1 }
        END {
            if (n == 0) { print "0 0 0"; exit }
            med = (n % 2 == 1) ? v[int(n/2)] : (v[n/2-1] + v[n/2]) / 2
            printf "%d %.0f %.0f\n", v[n-1], sum / n, med
        }'
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

# sleep N seconds, scaled by SLEEP_SCALE (--quick)
nap() {
    sleep "$(awk -v s="$1" -v f="$SLEEP_SCALE" 'BEGIN { printf "%.2f", s * f }')"
}

run_test_sequence() {
    local PID="$1"
    local CONFIG="$2"

    # Give it time to start
    nap 5
    log "[INFO] Update Config"
    sed -i 's/^enable_scheduled_sleep=1/enable_scheduled_sleep=0/' "$CONFIG"
    log "[INFO] Set Sprite Sheet: bongocat"
    sed -i -E 's/^invert_color=[0-9]+/invert_color=0/' "$CONFIG"
    sed -i -E 's/^animation_name=[:A-Za-z0-9_. ]+/animation_name=Bongocat/' "$CONFIG"
    reload_config "$PID" "$CONFIG"
    nap 2
    if [[ -f "/proc/$PID/fd/0" ]]; then
      log "[INFO] Send stdin"
      printf '\e' > "/proc/$PID/fd/0"
      nap 0.5
      printf '\e' > "/proc/$PID/fd/0"
      nap 0.5
    fi
    nap 1

    log "[INFO] Load biggest assets"
    log "[INFO] Set Sprite Sheet: Links"
    sed -i -E 's/^invert_color=[0-9]+/invert_color=0/' "$CONFIG"
    sed -i -E 's/^animation_name=[:A-Za-z0-9_. ]+/animation_name=Links/' "$CONFIG"
    reload_config "$PID" "$CONFIG"
    nap 4
    log "[INFO] Set Sprite Sheet: Rover"
    sed -i -E 's/^invert_color=[0-9]+/invert_color=0/' "$CONFIG"
    sed -i -E 's/^animation_name=[:A-Za-z0-9_. ]+/animation_name=Rover/' "$CONFIG"
    reload_config "$PID" "$CONFIG"
    nap 4
    log "[INFO] Set Sprite Sheet: pkmn:ho_oh"
    sed -i -E 's/^invert_color=[0-9]+/invert_color=0/' "$CONFIG"
    sed -i -E 's/^animation_name=[:A-Za-z0-9_. ]+/animation_name=pkmn:ho_oh/' "$CONFIG"
    reload_config "$PID" "$CONFIG"
    nap 3
    log "[INFO] Set Sprite Sheet: dmx:Hexeblaumon"
    sed -i -E 's/^invert_color=[0-9]+/invert_color=1/' "$CONFIG"
    sed -i -E 's/^animation_name=[:A-Za-z0-9_. ]+/animation_name=dmx:Hexeblaumon/' "$CONFIG"
    reload_config "$PID" "$CONFIG"
    nap 2
    log "[INFO] Set Sprite Sheet: dm20:Omegamon"
    sed -i -E 's/^invert_color=[0-9]+/invert_color=1/' "$CONFIG"
    sed -i -E 's/^animation_name=[:A-Za-z0-9_. ]+/animation_name=dm20:Omegamon/' "$CONFIG"
    reload_config "$PID" "$CONFIG"
    nap 1
    log "[INFO] Set Sprite Sheet: dmc:Omegamon"
    sed -i -E 's/^invert_color=[0-9]+/invert_color=0/' "$CONFIG"
    sed -i -E 's/^animation_name=[:A-Za-z0-9_. ]+/animation_name=dmc:Omegamon/' "$CONFIG"
    reload_config "$PID" "$CONFIG"
    nap 2
    log "[INFO] Set Sprite Sheet: Gargomon"
    sed -i -E 's/^enable_antialiasing=[0-9]+/enable_antialiasing=0/' "$CONFIG"
    sed -i -E 's/^invert_color=[0-9]+/invert_color=0/' "$CONFIG"
    sed -i -E 's/^animation_name=.*/animation_name=Gargomon/' "$CONFIG"
    reload_config "$PID" "$CONFIG"
    nap 2
    log "[INFO] Set Sprite Sheet: dm:Coronamon"
    sed -i -E 's/^invert_color=[0-9]+/invert_color=1/' "$CONFIG"
    sed -i -E 's/^animation_name=[:A-Za-z0-9_. ]+/animation_name=dm:Coronamon/' "$CONFIG"
    reload_config "$PID" "$CONFIG"
    nap 1
    log "[INFO] Set Sprite Sheet: Metal Greymon"
    sed -i -E 's/^invert_color=[0-9]+/invert_color=0/' "$CONFIG"
    sed -i -E 's/^animation_name=[:A-Za-z0-9_. ]+/animation_name=Metal Greymon/' "$CONFIG"
    reload_config "$PID" "$CONFIG"
    nap 2
    log "[INFO] Set Sprite Sheet: Arma Lizamon"
    sed -i -E 's/^invert_color=[0-9]+/invert_color=0/' "$CONFIG"
    sed -i -E 's/^animation_name=[:A-Za-z0-9_. ]+/animation_name=dmall:Arma Lizamon/' "$CONFIG"
    reload_config "$PID" "$CONFIG"
    nap 2
    log "[INFO] Set Sprite Sheet: pmd:volcanion"
    sed -i -E 's/^invert_color=[0-9]+/invert_color=0/' "$CONFIG"
    sed -i -E 's/^animation_name=[:A-Za-z0-9_. ]+/animation_name=pmd:volcanion/' "$CONFIG"
    reload_config "$PID" "$CONFIG"
    nap 3


    if [[ "$CPU_STRESS" == "1" ]]; then
        log "[TEST] CPU threshold"
        log "[INFO] Enable CPU threshold"
        sed -i -E 's/^invert_color=[0-9]+/invert_color=1/' "$CONFIG"
        sed -i -E 's/^animation_name=[:A-Za-z0-9_. ]+/animation_name=dm20:Agumon/' "$CONFIG"
        sed -i -E 's/^update_rate=[0-9]+/update_rate=1000/' "$CONFIG"
        sed -i -E 's/^cpu_threshold=[0-9]+/cpu_threshold=30/' "$CONFIG"
        reload_config "$PID" "$CONFIG"
        nap 1
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
    nap 1
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
    nap 20

    log "[TEST] Change animation sprite"
    log "[INFO] Set animation_name..."
    sed -i -E 's/^animation_name=.*/animation_name=Koromon/' "$CONFIG"
    sed -i -E 's/^invert_color=[0-9]+/invert_color=0/' "$CONFIG"
    sed -i -E 's/^evolution=.*/evolution=normal/' "$CONFIG"
    sed -i -E 's/^evolution_speed_factor=.*/evolution_speed_factor=3600.0/' "$CONFIG"
    reload_config "$PID" "$CONFIG"
    nap 20

    log "[TEST] Change animation sprite"
    log "[INFO] Set animation_name..."
    sed -i -E 's/^animation_name=.*/animation_name=Chaos Seadramon/' "$CONFIG"
    sed -i -E 's/^invert_color=[0-9]+/invert_color=0/' "$CONFIG"
    sed -i -E 's/^evolution=.*/evolution=0/' "$CONFIG"
    reload_config "$PID" "$CONFIG"
    nap 2

    #sed -i -E 's/^cat_height=[0-9]+/cat_height=72/' "$CONFIG"
    #sed -i -E 's/^overlay_height=[0-9]+/overlay_height=128/' "$CONFIG"

    log "[TEST] Change animation sprite"
    log "[INFO] Set animation_name..."
    sed -i -E 's/^animation_name=.*/animation_name=pkmn:bulbasaur/' "$CONFIG"
    sed -i -E 's/^invert_color=[0-9]+/invert_color=0/' "$CONFIG"
    sed -i -E 's/^evolution=.*/evolution=normal/' "$CONFIG"
    sed -i -E 's/^evolution_speed_factor=.*/evolution_speed_factor=3600.0/' "$CONFIG"
    reload_config "$PID" "$CONFIG"
    nap 30

    #sed -i -E 's/^cat_height=[0-9]+/cat_height=96/' "$CONFIG"
    #sed -i -E 's/^overlay_height=[0-9]+/overlay_height=128/' "$CONFIG"

    log "[TEST] Change animation sprite"
    log "[INFO] Set animation_name..."
    sed -i -E 's/^animation_name=.*/animation_name=pmd:charmander/' "$CONFIG"
    sed -i -E 's/^invert_color=[0-9]+/invert_color=0/' "$CONFIG"
    sed -i -E 's/^evolution=.*/evolution=normal/' "$CONFIG"
    sed -i -E 's/^evolution_speed_factor=.*/evolution_speed_factor=3600.0/' "$CONFIG"
    reload_config "$PID" "$CONFIG"
    nap 10
}

PMAP_TABLE="# pmaps

"

# Group by build type
for group in release; do
    echo "## $(tr '[:lower:]' '[:upper:]' <<< ${group:0:1})${group:1}" >> "$REPORT"
    echo "" >> "$REPORT"
    echo "RAM = RSS (shared libraries counted fully), PSS = shared pages split between the processes that map them," >> "$REPORT"
    echo "Private Dirty = memory only bongocat uses and the kernel can't drop (heap, stack, buffers, relocated data)." >> "$REPORT"
    echo "" >> "$REPORT"
    echo "| Variant | Binary Size | Peak RAM | Avg. RAM | Median RAM | End RAM | Peak PSS | Avg. PSS | End PSS | Peak Private Dirty | Avg. Private Dirty | End Private Dirty |" >> "$REPORT"
    echo "|---------|-------------|----------|----------|------------|---------|----------|----------|---------|--------------------|--------------------|-------------------|" >> "$REPORT"

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
                proc_mem_sample "$PID"
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

        nap 10 # pre-load start up ?
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
        read -r _ end_pss_kib end_pd_kib < <(proc_mem_sample "$PID" || echo "0 0 0")
        end_pss_kib=${end_pss_kib:-0}
        end_pd_kib=${end_pd_kib:-0}

        log "[INFO] Capturing pmap for PID $PID"
        pmap_output=$(pmap -x "$PID" 2>&1 || true)
        smaps_rollup_output=$(cat "/proc/$PID/smaps_rollup" 2>&1 || true)

        # --- send SIGTERM ---
        log "[INFO] Sending SIGTERM..."
        kill -TERM "$PID" 2>/dev/null || true

        log "[INFO] Wait for TERM (max 10s)"
        for _ in {1..100}; do
            if ! kill -0 "$PID" 2>/dev/null; then
                break
            fi
            sleep 0.1
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
        # samples are "rss pss private_dirty" (KiB)
        grep -E '^[0-9]+ [0-9]+ [0-9]+$' "$RAM_LOG" > "$RAM_LOG.clean" || true

        read -r max_sample_kib avg_ram_kib median_ram_kib < <(col_stats "$RAM_LOG.clean" 1)
        read -r peak_pss_kib avg_pss_kib _ < <(col_stats "$RAM_LOG.clean" 2)
        read -r peak_pd_kib avg_pd_kib _ < <(col_stats "$RAM_LOG.clean" 3)
        ram_kib=$(( hwm_kib > max_sample_kib ? hwm_kib : max_sample_kib ))

        ram=$(convert_size "$ram_kib")
        end_ram=$(convert_size "$end_ram_kib")
        avg_ram=$(convert_size "$avg_ram_kib")
        median_ram=$(convert_size "$median_ram_kib")
        peak_pss=$(convert_size "$peak_pss_kib")
        avg_pss=$(convert_size "$avg_pss_kib")
        end_pss=$(convert_size "$end_pss_kib")
        peak_pd=$(convert_size "$peak_pd_kib")
        avg_pd=$(convert_size "$avg_pd_kib")
        end_pd=$(convert_size "$end_pd_kib")

        variant=$(basename "$(dirname "$binary")")/$(basename "$binary")


        echo "| \`$variant\` | $size | $ram | $avg_ram | $median_ram | $end_ram | $peak_pss | $avg_pss | $end_pss | $peak_pd | $avg_pd | $end_pd |" >> "$REPORT"

        PMAP_TABLE+="**\`$variant\`**\n"
        PMAP_TABLE+='```bash\n'
        PMAP_TABLE+="$pmap_output"
        PMAP_TABLE+='\n```\n\n'
        PMAP_TABLE+="smaps_rollup (end of run):\n"
        PMAP_TABLE+='```bash\n'
        PMAP_TABLE+="$smaps_rollup_output"
        PMAP_TABLE+='\n```\n\n'

        log "[INFO] $variant_name: peak=$ram avg=$avg_ram median=$median_ram end=$end_ram | pss peak=$peak_pss avg=$avg_pss end=$end_pss | private_dirty peak=$peak_pd avg=$avg_pd end=$end_pd"
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
            -o -name "bongocat-pkmn" \) | sort |
            { if [[ -n "$ONLY_REGEX" ]]; then grep -E -- "$ONLY_REGEX" || true; else cat; fi; } |
            { if [[ -n "$SKIP_REGEX" ]]; then grep -vE -- "$SKIP_REGEX" || true; else cat; fi; }
    )
    echo "" >> "$REPORT"
done

echo -e "$PMAP_TABLE" >> "$REPORT"

echo ""
log "[INFO] Report generated: $REPORT"
log "[INFO] Logs: $LOG_DIR"
