#!/bin/bash

##############################################################################
# check_readonly_sections.sh
# Validates that asset sections are read-only for safe MADV_DONTNEED usage
##############################################################################

set -e

BINARY="${1:-./cmake-build-release-all-features/bongocat-all}"

if [[ ! -f "$BINARY" ]]; then
    echo "Error: Binary not found: $BINARY"
    exit 1
fi


echo "$(bloaty $BINARY -d sections)"
echo

# Sections that should be read-only (A flag, but NO W flag)
declare -a TEST_READONLY_SECTIONS=(
    ".assets.images"
    ".config.str"
    ".assets.data_evol"
    ".assets.sprite_settings"
    ".config.anim_entries_table"
    ".assets.images_table"
    ".config.custom_anim_entries_table"
    ".assets.sizes"
    ".rodata"
)

ERRORS=0
WARNINGS=0

READELF_OUTPUT=$(readelf --wide -S "$BINARY" 2>/dev/null)
echo "READ-ONLY SECTIONS"
for section in "${TEST_READONLY_SECTIONS[@]}"; do
    # Use grep to find the line, with word boundary to match exact section
    line=$(echo "$READELF_OUTPUT" | grep -E "\s$section\s" | head -1)

    if [[ -z "$line" ]]; then
        echo "$section - NOT FOUND"
        continue
    fi

    # Extract fields from readelf --wide output
    # Format: [Nr] Name Type Address Offset Size EntSize Flags Link Info Align
    name=$(echo "$line" | awk '{print $2}')
    type=$(echo "$line" | awk '{print $3}')
    addr=$(echo "$line" | awk '{print $4}')
    size=$(echo "$line" | awk '{print $6}')
    flags=$(echo "$line" | awk '{print $8}')
    size_hex=$(echo "$line" | awk '{print $6}')
    size_dec=$((16#$size_hex))

    human_size=$(numfmt --to=iec-i --suffix=B "$size_dec")

    printf "%-30s Size: %-8s (%s)  Addr: %-18s " "$name" "$human_size" "$size_hex" "$addr"
    printf "Flags: %-10s " "$flags"

    # Check for W flag (writable)
    if [[ "$flags" == *"W"* ]]; then
        echo "❌ ERROR: Has W flag (should be read-only!)"
        ((ERRORS++))
    else
        echo "✓ OK"
    fi

    # Check for A flag (allocated)
    if [[ "$flags" != *"A"* ]]; then
        echo "  ⚠️  WARNING: Missing A flag (not allocated to memory)"
        ((WARNINGS++))
    fi

    # Check page alignment (4096 = 0x1000)
    if [[ -n "$addr" ]] && [[ "$addr" != "0000000000000000" ]]; then
        addr_dec=$((16#${addr}))
        if (( addr_dec > 0 )) && (( addr_dec % 4096 != 0 )); then
            printf "  ⚠️  WARNING: Address 0x%s not page-aligned (need multiple of 0x1000)\n" "$addr"
            ((WARNINGS++))
        fi
    fi
done

echo
echo "SEGMENT ANALYSIS (LOAD segments with readonly asset sections)"

readelf --wide -l "$BINARY" 2>/dev/null | grep -A 20 "LOAD" | while read -r line; do
    if [[ "$line" =~ "LOAD" ]]; then
        flags=$(echo "$line" | awk '{print $(NF-1)}')
        filesz=$(echo "$line" | awk '{print $(NF-3)}')
        echo "LOAD segment: Flags=$flags FileSz=$filesz"
    fi
done


if (( ERRORS == 0 )); then
    echo "✓ All checks passed! Safe to use MADV_DONTNEED on:"
    for section in "${READONLY_SECTIONS[@]}"; do
        if echo "$READELF_OUTPUT" | grep -q "$section"; then
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
    echo "$READELF_OUTPUT" | grep -E "(^\[|\.assets\.|\.config\.)"
    exit 1
fi