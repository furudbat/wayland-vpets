#!/bin/bash

##############################################################################
# check_readonly_sections.sh
# Validates that the asset/config blocks are read-only for safe MADV_DONTNEED usage
#
# Layout (cmake/EmbeddedAssets.cmake, include/embedded_assets/assets.h):
#   .bongocat.assets   all .assets.<set>.<kind> input sections, one page-aligned range per set
#                      (_bongocat_start/stop_assets_<set>)
#   .bongocat.config   all .config.str input sections (_bongocat_start/stop_config)
#
# Full check over all build dirs: scripts/tests/check_assets_sections.sh
##############################################################################

set -e

BINARY="${1:-./cmake-build-release-all-features/bongocat-all}"

if [[ ! -f "$BINARY" ]]; then
    echo "Error: Binary not found: $BINARY"
    exit 1
fi

if command -v bloaty >/dev/null 2>&1; then
    bloaty "$BINARY" -d sections
    echo
fi

PAGE_SIZE=$(getconf PAGESIZE 2>/dev/null || echo 4096)

# Sections that must be read-only (A flag, but NO W flag); the evicted blocks must be page-aligned
declare -a READONLY_SECTIONS=(
    ".bongocat.assets"
    ".bongocat.config"
    ".rodata"
)
declare -a EVICTED_SECTIONS=(
    ".bongocat.assets"
    ".bongocat.config"
)

ERRORS=0
WARNINGS=0

READELF_OUTPUT=$(readelf --wide -S "$BINARY" 2>/dev/null)

# input sections the linker script did not match end up as their own output section (never evicted)
mapfile -t ORPHAN_SECTIONS < <(echo "$READELF_OUTPUT" | sed -n 's/^ *\[ *[0-9]*\] *//p' | awk '$1 ~ /^\.(assets|config)\./ {print $1}')

is_evicted_section() {
    local s
    for s in "${EVICTED_SECTIONS[@]}"; do
        [[ "$s" == "$1" ]] && return 0
    done
    return 1
}

echo "READ-ONLY SECTIONS"
for section in "${READONLY_SECTIONS[@]}" "${ORPHAN_SECTIONS[@]}"; do
    # exact section name (dots escaped)
    line=$(echo "$READELF_OUTPUT" | sed -n 's/^ *\[ *[0-9]*\] *//p' | awk -v s="$section" '$1 == s' | head -1)

    if [[ -z "$line" ]]; then
        if is_evicted_section "$section"; then
            echo "$section - NOT FOUND"
            ERRORS=$((ERRORS + 1))
        else
            echo "$section - NOT FOUND"
        fi
        continue
    fi

    # Format (after "[Nr]"): Name Type Address Offset Size EntSize Flags Link Info Align
    name=$(echo "$line" | awk '{print $1}')
    addr=$(echo "$line" | awk '{print $3}')
    size_hex=$(echo "$line" | awk '{print $5}')
    flags=$(echo "$line" | awk '{print $7}')
    [[ "$flags" =~ ^[0-9]+$ ]] && flags=""
    size_dec=$((16#$size_hex))

    human_size=$(numfmt --to=iec-i --suffix=B "$size_dec")

    printf "%-30s Size: %-8s (%s)  Addr: %-18s " "$name" "$human_size" "$size_hex" "$addr"
    printf "Flags: %-6s " "$flags"

    # Check for W flag (writable)
    if [[ "$flags" == *"W"* ]]; then
        echo "❌ ERROR: Has W flag (should be read-only!)"
        ERRORS=$((ERRORS + 1))
    elif [[ "$name" =~ ^\.(assets|config)\. ]]; then
        echo "❌ ERROR: orphan section, not inside .bongocat.assets/.bongocat.config (never evicted, kind name missing in the linker script?)"
        ERRORS=$((ERRORS + 1))
    else
        echo "✓ OK"
    fi

    # Check for A flag (allocated)
    if [[ "$flags" != *"A"* ]]; then
        echo "  ⚠️  WARNING: Missing A flag (not allocated to memory)"
        WARNINGS=$((WARNINGS + 1))
    fi

    # Check page alignment of the evicted blocks (start and size)
    if is_evicted_section "$name"; then
        addr_dec=$((16#${addr}))
        if (( addr_dec % PAGE_SIZE != 0 )); then
            printf "  ❌ ERROR: Address 0x%s not page-aligned (need multiple of 0x%x)\n" "$addr" "$PAGE_SIZE"
            ERRORS=$((ERRORS + 1))
        fi
        if (( size_dec % PAGE_SIZE != 0 )); then
            printf "  ❌ ERROR: Size 0x%s not a multiple of the page size 0x%x\n" "$size_hex" "$PAGE_SIZE"
            ERRORS=$((ERRORS + 1))
        fi

        # dynamic relocations inside the block: MADV_DONTNEED would bring back the unrelocated file bytes
        lo_hex=$(printf '%016x' "$addr_dec")
        hi_hex=$(printf '%016x' $((addr_dec + size_dec)))
        # force STRING comparison (fixed width hex): awk would compare "0000000000835000" or "...840e18" as numbers
        relocs=$(readelf --wide -r "$BINARY" 2>/dev/null | awk -v lo="$lo_hex" -v hi="$hi_hex" \
            '/^[0-9a-f]+ +[0-9a-f]+ / { o = "" $1; if (o >= ("" lo) && o < ("" hi)) c++ } END { print c + 0 }')
        if (( relocs > 0 )); then
            echo "  ❌ ERROR: $relocs dynamic relocation(s) inside (pointers in an evicted section)"
            ERRORS=$((ERRORS + 1))
        fi
    fi
done

echo
echo "ASSET SET RANGES (inside .bongocat.assets)"
if nm "$BINARY" >/dev/null 2>&1; then
    # defined start/stop symbols: "addr type name"
    declare -A SYM=()
    while read -r s_addr _ s_name; do
        SYM[$s_name]=$s_addr
    done < <(nm "$BINARY" 2>/dev/null | awk 'NF == 3 && $3 ~ /^_bongocat_(start|stop)_/')

    # sub range (e.g. assets_dm20_evol_data inside assets_dm20): may be empty (set without evolution data)
    is_sub_range() {
        local other
        for other in "${!SYM[@]}"; do
            other=${other#_bongocat_start_}
            [[ "$other" == _bongocat_stop_* || "$other" == "$1" ]] && continue
            [[ "$1" == "${other}_"* && "$other" == assets_* && "$other" != assets ]] && return 0
        done
        return 1
    }

    for start_sym in $(printf '%s\n' "${!SYM[@]}" | grep '^_bongocat_start_' | sort); do
        range=${start_sym#_bongocat_start_}
        stop_sym="_bongocat_stop_$range"
        if [[ -z "${SYM[$stop_sym]:-}" ]]; then
            echo "$range - ❌ ERROR: $stop_sym missing"
            ERRORS=$((ERRORS + 1))
            continue
        fi
        start_dec=$((16#${SYM[$start_sym]}))
        stop_dec=$((16#${SYM[$stop_sym]}))
        printf "%-30s 0x%s .. 0x%s  %-10s " "$range" "${SYM[$start_sym]}" "${SYM[$stop_sym]}" \
            "$(numfmt --to=iec-i --suffix=B $((stop_dec - start_dec)))"
        if (( start_dec > stop_dec )); then
            echo "❌ ERROR: start > stop"
            ERRORS=$((ERRORS + 1))
        elif (( start_dec % PAGE_SIZE != 0 || stop_dec % PAGE_SIZE != 0 )); then
            echo "❌ ERROR: not page-aligned"
            ERRORS=$((ERRORS + 1))
        elif (( start_dec == stop_dec )) && [[ "$range" != "assets_common" ]] && ! is_sub_range "$range"; then
            echo "⚠️  WARNING: empty"
            WARNINGS=$((WARNINGS + 1))
        else
            echo "✓ OK"
        fi
    done
    for stop_sym in $(printf '%s\n' "${!SYM[@]}" | grep '^_bongocat_stop_' | sort); do
        if [[ -z "${SYM[_bongocat_start_${stop_sym#_bongocat_stop_}]:-}" ]]; then
            echo "${stop_sym#_bongocat_stop_} - ❌ ERROR: _bongocat_start_${stop_sym#_bongocat_stop_} missing"
            ERRORS=$((ERRORS + 1))
        fi
    done
    if (( ${#SYM[@]} == 0 )); then
        echo "❌ ERROR: no _bongocat_start_*/_bongocat_stop_* symbols"
        ERRORS=$((ERRORS + 1))
    fi

    # referenced by the code but never defined (weak undefined -> null -> empty range):
    # fine for a set that is not linked, an ERROR when the name matches no known set (typo, broken ## pasting)
    CMAKE_SETS_FILE="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)/cmake/EmbeddedAssets.cmake"
    mapfile -t ALL_SETS < <(awk '
        !f && /BONGOCAT_ASSET_SETS/ && !/\$\{/ { f = 1; sub(/.*BONGOCAT_ASSET_SETS/, "") }
        f { done = sub(/\).*/, ""); sub(/#.*/, ""); n = split($0, w, /[ \t]+/); for (i = 1; i <= n; i++) if (w[i] != "") print w[i]; if (done) exit }
      ' "$CMAKE_SETS_FILE" 2>/dev/null)
    declare -A UNDEF_REPORTED=()
    while read -r _ u_name; do
        range=${u_name#_bongocat_start_}
        range=${range#_bongocat_stop_}
        [[ -n "${UNDEF_REPORTED[$range]:-}" ]] && continue
        UNDEF_REPORTED[$range]=1
        owner=""
        for set in "${ALL_SETS[@]}" common; do
            if [[ ("$range" == "assets_$set" || "$range" == "assets_${set}_"*) && ${#set} -gt ${#owner} ]]; then
                owner=$set
            fi
        done
        if [[ -z "$owner" ]]; then
            echo "$range - ❌ ERROR: referenced but never defined and no such set (typo/macro bug?), always empty"
            ERRORS=$((ERRORS + 1))
        else
            echo "$range - not defined (set '$owner' not linked or no such sub range), empty"
        fi
    done < <(nm "$BINARY" 2>/dev/null | awk 'NF == 2 && $2 ~ /^_bongocat_(start|stop)_/')
else
    echo "(no symbols, stripped binary?)"
fi

echo
echo "SEGMENT ANALYSIS (LOAD segments)"
readelf --wide -l "$BINARY" 2>/dev/null | awk '$1 == "LOAD" {
    flags = ""; for (i = 7; i < NF; i++) flags = flags $i;
    printf "LOAD segment: VirtAddr=%s MemSz=%s Flags=%s\n", $3, $6, flags }'
for section in "${EVICTED_SECTIONS[@]}"; do
    seg=$(readelf --wide -l "$BINARY" 2>/dev/null | sed -n '/Section to Segment mapping/,$p' \
        | awk -v s="$section" '{ for (i = 2; i <= NF; i++) if ($i == s) print $1 }' | head -1)
    [[ -z "$seg" ]] && continue
    # segment index -> flags of the n-th program header
    seg_flags=$(readelf --wide -l "$BINARY" 2>/dev/null | sed -n '/Program Headers/,/Section to Segment/p' \
        | awk -v n=$((10#$seg)) '$1 ~ /^[A-Z_]+$/ && $1 != "Type" { if (idx == n) { f = ""; for (i = 7; i < NF; i++) f = f $i; print f } idx++ }')
    if [[ "$seg_flags" == *W* ]]; then
        echo "❌ ERROR: $section is in writable segment $seg ($seg_flags)"
        ERRORS=$((ERRORS + 1))
    else
        echo "$section in segment $seg ($seg_flags) ✓ OK"
    fi
done
if readelf --wide -l "$BINARY" 2>/dev/null | grep -q GNU_RELRO; then
    echo "GNU_RELRO present ✓ OK"
else
    echo "⚠️  WARNING: no GNU_RELRO segment (writable section before .data.rel.ro?)"
    WARNINGS=$((WARNINGS + 1))
fi

echo
if (( ERRORS == 0 )); then
    echo "✓ All checks passed ($WARNINGS warning(s))! Safe to use MADV_DONTNEED on:"
    for section in "${EVICTED_SECTIONS[@]}"; do
        if echo "$READELF_OUTPUT" | grep -qF " $section "; then
            echo "  • $section"
        fi
    done
    exit 0
else
    echo "❌ Found $ERRORS error(s), $WARNINGS warning(s)"
    echo ""
    echo "DO NOT call MADV_DONTNEED until errors are fixed!"
    echo ""
    echo "Full readelf output:"
    echo "$READELF_OUTPUT" | grep -E "(\.bongocat\.|\.assets\.|\.config\.)"
    exit 1
fi
