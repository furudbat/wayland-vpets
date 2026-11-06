#!/usr/bin/env bash
##############################################################################
# check_assets_sections.sh
#
# Validates the loadable/unloadable (madvise) blocks in the built executables,
# see cmake/EmbeddedAssets.cmake and include/embedded_assets/assets.h:
#
#   * .bongocat.assets / .bongocat.config exist, are allocated (A) and NOT writable (W),
#     page-aligned, inside a read-only LOAD segment and without dynamic relocations
#     (MADV_DONTNEED on relocated pages would bring back the unrelocated file bytes)
#   * no orphan .assets.* / .config.* output sections (input sections the linker script does not match,
#     e.g. a wrong kind name -> never evicted)
#   * _bongocat_start_* / _bongocat_stop_* exist (defined, not weak-undefined), as pairs,
#     page-aligned, start <= stop, inside their block
#   * every linked asset set (from assets_segment/<exe>.ld, "animation sets: ...") has its range,
#     no range for a set that is not linked
#
# Usage:
#   scripts/tests/check_assets_sections.sh [-v] [build-dir|executable ...]
#   (default: all cmake-build-*/bongocat* executables)
#
# Exit code: 0 = ok (warnings allowed), 1 = errors
##############################################################################

set -uo pipefail

VERBOSE=0
if [[ "${1:-}" == "-v" ]]; then
  VERBOSE=1
  shift
fi

for tool in readelf nm awk; do
  if ! command -v "$tool" >/dev/null 2>&1; then
    echo "Error: '$tool' not found" >&2
    exit 2
  fi
done

PAGE_SIZE=$(getconf PAGESIZE 2>/dev/null || echo 4096)

# all known asset sets (BONGOCAT_ASSET_SETS in cmake/EmbeddedAssets.cmake)
PROJECT_ROOT=$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)
ALL_SETS=()
if [[ -f "$PROJECT_ROOT/cmake/EmbeddedAssets.cmake" ]]; then
  # set(\n  BONGOCAT_ASSET_SETS\n  bongocat\n  ...\n)   (also works for "set(BONGOCAT_ASSET_SETS a b c)")
  mapfile -t ALL_SETS < <(awk '
      !f && /BONGOCAT_ASSET_SETS/ && !/\$\{/ { f = 1; sub(/.*BONGOCAT_ASSET_SETS/, "") }
      f { done = sub(/\).*/, ""); sub(/#.*/, ""); n = split($0, w, /[ \t]+/); for (i = 1; i <= n; i++) if (w[i] != "") print w[i]; if (done) exit }
    ' "$PROJECT_ROOT/cmake/EmbeddedAssets.cmake")
fi
if ((${#ALL_SETS[@]} == 0)); then
  echo "Warning: could not read BONGOCAT_ASSET_SETS from cmake/EmbeddedAssets.cmake" >&2
fi

if [[ -t 1 ]]; then
  C_RED=$'\e[31m' C_YELLOW=$'\e[33m' C_GREEN=$'\e[32m' C_DIM=$'\e[2m' C_RESET=$'\e[0m'
else
  C_RED='' C_YELLOW='' C_GREEN='' C_DIM='' C_RESET=''
fi

TOTAL_ERRORS=0
TOTAL_WARNINGS=0
CHECKED=0
SKIPPED=0
FAILED_BINARIES=()

# per binary state
errors=0
warnings=0
messages=()

err() {
  messages+=("  ${C_RED}ERROR${C_RESET}   $*")
  ((errors++))
}
warn() {
  messages+=("  ${C_YELLOW}WARNING${C_RESET} $*")
  ((warnings++))
}
info() {
  if ((VERBOSE)); then
    messages+=("  ${C_DIM}$*${C_RESET}")
  fi
}

human_size() {
  local bytes=$1
  if command -v numfmt >/dev/null 2>&1; then
    numfmt --to=iec-i --suffix=B "$bytes"
  else
    echo "${bytes}B"
  fi
}

is_elf() {
  [[ -f "$1" && -x "$1" ]] || return 1
  [[ "$(head -c 4 "$1" 2>/dev/null | od -An -c | tr -d ' ')" == '177ELF' ]]
}

# -----------------------------------------------------------------------------
# collect executables
# -----------------------------------------------------------------------------
BINARIES=()
add_binaries_from_dir() {
  local dir=$1 exe
  for exe in "$dir"/bongocat*; do
    is_elf "$exe" && BINARIES+=("$exe")
  done
}
if (($# == 0)); then
  for dir in cmake-build-*/; do
    add_binaries_from_dir "${dir%/}"
  done
else
  for arg in "$@"; do
    if [[ -d "$arg" ]]; then
      add_binaries_from_dir "${arg%/}"
    elif is_elf "$arg"; then
      BINARIES+=("$arg")
    else
      echo "Warning: not an executable or build dir: $arg" >&2
    fi
  done
fi
if ((${#BINARIES[@]} == 0)); then
  echo "No executables found (run from the project root or pass build dirs/executables)" >&2
  exit 2
fi

# -----------------------------------------------------------------------------
# check one executable
# -----------------------------------------------------------------------------
check_binary() {
  local exe=$1
  local build_dir name ld_script
  build_dir=$(dirname "$exe")
  name=$(basename "$exe")
  ld_script="$build_dir/assets_segment/$name.ld"

  errors=0
  warnings=0
  messages=()

  if [[ ! -f "$ld_script" ]]; then
    printf '%s- %s%s (no assets_segment/%s.ld, not linked with the assets segment)\n' "$C_DIM" "$exe" "$C_RESET" "$name"
    ((SKIPPED++))
    return
  fi
  ((CHECKED++))

  # linked sets as written by bongocat_target_assets_segment()
  local -a sets=()
  local sets_line
  sets_line=$(sed -n 's/^ \* animation sets: *//p' "$ld_script" | head -1)
  if [[ -n "$sets_line" ]]; then
    IFS=';' read -r -a sets <<<"$sets_line"
  else
    warn "no 'animation sets:' line in $ld_script, can not check the linked sets"
  fi
  if [[ "$exe" -ot "$ld_script" ]]; then
    warn "executable is older than its linker script (not rebuilt?)"
  fi

  # --- sections: name type addr off size es flags -------------------------------------------------
  local -A SEC_ADDR=() SEC_SIZE=() SEC_FLAGS=()
  local sec_name sec_type sec_addr sec_off sec_size sec_es sec_flags _rest
  while read -r sec_name sec_type sec_addr sec_off sec_size sec_es sec_flags _rest; do
    [[ "$sec_name" == .* ]] || continue
    # sections without flags shift the columns (flags would be the link field, a number)
    [[ "$sec_flags" =~ ^[0-9]+$ ]] && sec_flags=""
    SEC_ADDR[$sec_name]=$sec_addr
    SEC_SIZE[$sec_name]=$sec_size
    SEC_FLAGS[$sec_name]=$sec_flags
  done < <(readelf -SW "$exe" 2>/dev/null | sed -n 's/^ *\[ *[0-9]*\] *//p')

  # --- LOAD segments: vaddr memsz flags ----------------------------------------------------------
  local -a LOAD_VADDR=() LOAD_MEMSZ=() LOAD_FLAGS=()
  local l_vaddr l_memsz l_flags
  while read -r l_vaddr l_memsz l_flags; do
    LOAD_VADDR+=("$l_vaddr")
    LOAD_MEMSZ+=("$l_memsz")
    LOAD_FLAGS+=("$l_flags")
  done < <(readelf -lW "$exe" 2>/dev/null | awk '$1 == "LOAD" {
      flags = ""; for (i = 7; i < NF; i++) flags = flags $i;
      sub(/^0x/, "", $3); sub(/^0x/, "", $6); print $3, $6, flags }')

  segment_flags_of() {
    local addr_dec=$1 i lo hi
    for i in "${!LOAD_VADDR[@]}"; do
      lo=$((16#${LOAD_VADDR[$i]}))
      hi=$((lo + $((16#${LOAD_MEMSZ[$i]}))))
      if ((addr_dec >= lo && addr_dec < hi)); then
        echo "${LOAD_FLAGS[$i]}"
        return
      fi
    done
    echo "?"
  }

  # --- symbols: defined (addr type name) and weak-undefined (type name) -----------------------------
  local -A SYM=() SYM_UNDEF=()
  local s1 s2 s3 has_symtab=0
  [[ -n "${SEC_ADDR[.symtab]:-}" ]] && has_symtab=1
  if ((has_symtab)); then
    while read -r s1 s2 s3; do
      if [[ -n "$s3" ]]; then
        SYM[$s3]=$s1
      else
        SYM_UNDEF[$s2]=$s1
      fi
    done < <(nm --no-sort "$exe" 2>/dev/null | awk '$NF ~ /^_bongocat_(start|stop)_/')
    if ((${#SYM[@]} == 0)) && ((${#SYM_UNDEF[@]} == 0)); then
      err "no _bongocat_start_*/_bongocat_stop_* symbols"
    fi
  else
    warn "stripped (no .symtab), symbol checks skipped"
  fi

  # dynamic relocations inside the blocks, one pass over all relocations
  # (offsets are zero-padded hex: compare as STRINGS, awk would take "...835000" or "...840e18" as numbers)
  local reloc_ranges="" b
  for b in .bongocat.assets .bongocat.config; do
    [[ -n "${SEC_ADDR[$b]:-}" ]] || continue
    reloc_ranges+="$b $(printf '%016x %016x' $((16#${SEC_ADDR[$b]})) $((16#${SEC_ADDR[$b]} + 16#${SEC_SIZE[$b]})));"
  done
  local -A RELOCS_IN=()
  local r_block r_count
  while read -r r_block r_count; do
    RELOCS_IN[$r_block]=$r_count
  done < <(readelf -rW "$exe" 2>/dev/null | awk -v ranges="$reloc_ranges" '
      BEGIN { n = split(ranges, rs, ";"); for (i = 1; i <= n; i++) if (split(rs[i], f, " ") == 3) { name[++k] = f[1]; lo[k] = "" f[2]; hi[k] = "" f[3]; c[k] = 0 } }
      /^[0-9a-f]+ +[0-9a-f]+ / { o = sprintf("%016s", $1); gsub(/ /, "0", o); for (i = 1; i <= k; i++) if (o >= lo[i] && o < hi[i]) c[i]++ }
      END { for (i = 1; i <= k; i++) print name[i], c[i] }')

  # --- 1. the load/unload blocks -------------------------------------------------------------------
  local block addr size flags addr_dec size_dec seg_flags nrel
  for block in .bongocat.assets .bongocat.config; do
    if [[ -z "${SEC_ADDR[$block]:-}" ]]; then
      err "$block: section missing"
      continue
    fi
    addr=${SEC_ADDR[$block]}
    size=${SEC_SIZE[$block]}
    flags=${SEC_FLAGS[$block]}
    addr_dec=$((16#$addr))
    size_dec=$((16#$size))
    ((VERBOSE)) && info "$(printf '%-18s addr=0x%s size=%s flags=%s' "$block" "$addr" "$(human_size "$size_dec")" "$flags")"

    [[ "$flags" == *A* ]] || err "$block: not allocated (flags '$flags')"
    [[ "$flags" == *W* ]] && err "$block: WRITABLE (flags '$flags'), pointers/relocated data in the section?"
    ((addr_dec % PAGE_SIZE == 0)) || err "$block: start 0x$addr not page-aligned"
    ((size_dec % PAGE_SIZE == 0)) || err "$block: size 0x$size not a multiple of the page size"

    seg_flags=$(segment_flags_of "$addr_dec")
    if [[ "$seg_flags" == "?" ]]; then
      err "$block: not inside a LOAD segment"
    elif [[ "$seg_flags" == *W* ]]; then
      err "$block: inside a writable LOAD segment ($seg_flags)"
    fi

    nrel=${RELOCS_IN[$block]:-0}
    ((nrel == 0)) || err "$block: $nrel dynamic relocation(s) inside (pointers in an evicted section)"
  done

  # --- 2. orphan output sections (not matched by the linker script) ---------------------------------
  for sec_name in "${!SEC_ADDR[@]}"; do
    if [[ "$sec_name" =~ ^\.(assets|config)\. ]]; then
      err "$sec_name: orphan output section ($(human_size "$((16#${SEC_SIZE[$sec_name]}))")), not inside .bongocat.assets/.bongocat.config -> never evicted (kind name not in the linker script?)"
      [[ "${SEC_FLAGS[$sec_name]}" == *W* ]] && err "$sec_name: WRITABLE (flags '${SEC_FLAGS[$sec_name]}')"
    fi
  done

  # --- 3. symbol pairs ----------------------------------------------------------------------------------
  # check_range <range-name> <block-section> [required: 1|0] [warn-if-empty: 1|0]
  check_range() {
    local range=$1 block=$2 required=${3:-1} warn_empty=${4:-0}
    local start_sym="_bongocat_start_$range" stop_sym="_bongocat_stop_$range"
    local start_hex=${SYM[$start_sym]:-} stop_hex=${SYM[$stop_sym]:-}

    if [[ -z "$start_hex" || -z "$stop_hex" ]]; then
      if ((required)); then
        [[ -z "$start_hex" ]] && err "$start_sym missing${SYM_UNDEF[$start_sym]:+ (weak undefined)}"
        [[ -z "$stop_hex" ]] && err "$stop_sym missing${SYM_UNDEF[$stop_sym]:+ (weak undefined)}"
      elif [[ -n "$start_hex" || -n "$stop_hex" ]]; then
        err "$range: only one of $start_sym/$stop_sym defined"
      fi
      return
    fi

    local start_dec stop_dec
    start_dec=$((16#$start_hex))
    stop_dec=$((16#$stop_hex))
    ((VERBOSE)) && info "$(printf '%-28s 0x%s .. 0x%s  %s' "$range" "$start_hex" "$stop_hex" "$(human_size $((stop_dec - start_dec)))")"

    ((start_dec <= stop_dec)) || err "$range: start 0x$start_hex > stop 0x$stop_hex"
    ((start_dec % PAGE_SIZE == 0)) || err "$start_sym 0x$start_hex not page-aligned"
    ((stop_dec % PAGE_SIZE == 0)) || err "$stop_sym 0x$stop_hex not page-aligned"
    if ((warn_empty)) && ((start_dec == stop_dec)); then
      warn "$range: empty range (set linked, but nothing in .assets.${range#assets_}.*, still using the generic section macros?)"
    fi

    if [[ -n "${SEC_ADDR[$block]:-}" ]]; then
      local block_lo block_hi
      block_lo=$((16#${SEC_ADDR[$block]}))
      block_hi=$((block_lo + $((16#${SEC_SIZE[$block]}))))
      if ((start_dec < block_lo || stop_dec > block_hi)); then
        err "$range: 0x$start_hex..0x$stop_hex outside $block"
      fi
    fi
  }

  local set
  if ((has_symtab)); then
    check_range assets .bongocat.assets
    check_range config .bongocat.config
    for set in "${sets[@]}"; do
      check_range "assets_$set" .bongocat.assets 1 1
    done
    # optional (older layouts), only checked when defined
    check_range assets_common .bongocat.assets 0 0
  fi

  # every other defined range: needs its pair, must belong to a linked set (sub ranges: assets_<set>_<kind>)
  local sym range owner known
  for sym in "${!SYM[@]}"; do
    [[ "$sym" == _bongocat_start_* ]] || [[ "$sym" == _bongocat_stop_* ]] || continue
    range=${sym#_bongocat_start_}
    range=${range#_bongocat_stop_}
    case "$range" in
    assets | config | assets_common) continue ;;
    esac
    # only once per range (from the start symbol, or the stop symbol if start is missing)
    if [[ "$sym" == _bongocat_stop_* && -n "${SYM[_bongocat_start_$range]:-}" ]]; then
      continue
    fi

    known=0
    owner=""
    for set in "${sets[@]}" common; do
      if [[ "$range" == "assets_$set" ]]; then
        known=1
        break
      fi
      # longest matching set prefix for sub ranges (dm vs dm20, pen vs pen20)
      if [[ "$range" == "assets_${set}_"* && ${#set} -gt ${#owner} ]]; then
        owner=$set
      fi
    done
    ((known)) && continue

    if [[ -n "$owner" ]]; then
      check_range "$range" .bongocat.assets 1 0
      # sub range must be inside its set range
      if [[ -n "${SYM[_bongocat_start_$range]:-}" && -n "${SYM[_bongocat_start_assets_$owner]:-}" ]]; then
        local sub_lo sub_hi set_lo set_hi
        sub_lo=$((16#${SYM[_bongocat_start_$range]}))
        sub_hi=$((16#${SYM[_bongocat_stop_$range]:-0}))
        set_lo=$((16#${SYM[_bongocat_start_assets_$owner]}))
        set_hi=$((16#${SYM[_bongocat_stop_assets_$owner]:-0}))
        if ((sub_lo < set_lo || sub_hi > set_hi)); then
          err "$range: not inside assets_$owner"
        fi
      fi
    elif [[ "$range" == assets_* ]]; then
      err "_bongocat_*_$range defined, but '${range#assets_}' is not a linked set (${sets_line:-none})"
    else
      check_range "$range" "" 1 0
    fi
  done

  # weak-undefined (referenced by the code, not defined by the linker script):
  #   set not linked           -> ok (null = empty range)
  #   linked set, sub range    -> warning (empty, e.g. no evol_data in the linker script for that set)
  #   unknown set              -> error (typo or broken macro token pasting, the range is ALWAYS empty)
  local -A REPORTED_UNDEF=()
  for sym in "${!SYM_UNDEF[@]}"; do
    range=${sym#_bongocat_start_}
    range=${range#_bongocat_stop_}
    [[ -n "${REPORTED_UNDEF[$range]:-}" ]] && continue
    REPORTED_UNDEF[$range]=1

    owner=""
    for set in "${ALL_SETS[@]}" common; do
      if [[ ("$range" == "assets_$set" || "$range" == "assets_${set}_"*) && ${#set} -gt ${#owner} ]]; then
        owner=$set
      fi
    done
    if [[ -z "$owner" ]]; then
      err "_bongocat_*_$range referenced but no such set (known: ${ALL_SETS[*]}), always empty -> typo/macro bug?"
      continue
    fi
    if [[ ";${sets_line};" == *";${owner};"* ]]; then
      if [[ "$range" == "assets_$owner" ]]; then
        : # main range of a linked set, already reported by check_range
      else
        warn "_bongocat_*_$range referenced but not defined (linked set '$owner'), empty range"
      fi
    else
      ((VERBOSE)) && info "weak undefined (set not linked): $sym"
    fi
  done

  # --- result -------------------------------------------------------------------------------------
  if ((errors > 0)); then
    printf '%s✗%s %s %s(sets: %s)%s\n' "$C_RED" "$C_RESET" "$exe" "$C_DIM" "${sets_line:-?}" "$C_RESET"
    FAILED_BINARIES+=("$exe")
  else
    printf '%s✓%s %s %s(sets: %s)%s\n' "$C_GREEN" "$C_RESET" "$exe" "$C_DIM" "${sets_line:-?}" "$C_RESET"
  fi
  local m
  for m in "${messages[@]}"; do
    echo "$m"
  done

  ((TOTAL_ERRORS += errors))
  ((TOTAL_WARNINGS += warnings))
}

for exe in "${BINARIES[@]}"; do
  check_binary "$exe"
done

echo
echo "checked: $CHECKED, skipped: $SKIPPED, errors: $TOTAL_ERRORS, warnings: $TOTAL_WARNINGS"
if ((TOTAL_ERRORS > 0)); then
  echo "${C_RED}failed:${C_RESET}"
  printf '  %s\n' "${FAILED_BINARIES[@]}"
  exit 1
fi
exit 0
