#!/usr/bin/env bash
# =============================================================================
# build_string_blobs.sh - turn generated string constants into ONE char blob + uint32_t offsets
# =============================================================================
#
# Why: tables of `const char*` (e.g. <set>_animation_table) need one relative relocation per pointer
# in a PIE binary. The dynamic loader patches them at startup, so every page of those tables becomes
# private dirty memory (.data.rel.ro) for the whole run. Tables of uint32_t offsets into a blob need
# no relocations: they stay plain read-only data and can be evicted with the config section.
#
# Input (as written by generate_embedded_assets.sh / generate_init_anim.sh and the custom variants):
#     inline constexpr char X_ARR[] CONFIG_STRING_SECTION(X_ARR) = "dm:agumon";
#     inline constexpr const char* X = X_ARR;
#     inline constexpr size_t X_LEN = sizeof(X_ARR)-1;
# Output:
#     // @string-blob BLOB ...
#     inline constexpr char BLOB[] CONFIG_STRING_SECTION(BLOB) =
#         "dm:agumon\0"
#         ...;
#     inline constexpr uint32_t X_OFF = 0;
#     inline constexpr const char* X = BLOB + X_OFF;
#     inline constexpr size_t X_LEN = 9;
#   (+ one static_assert per string that checks the offset at compile time)
#
# Strings are stored once: exact duplicates and suffixes share storage
# ("agumon" points into "dm:agumon\0", "Agumon" into "dm:Agumon\0").
# Offsets are byte offsets (LC_ALL=C), only \" and \\ escapes are supported in the literals.
#
# Usage:
#   build_string_blobs.sh [--check] [--no-asserts] --blob NAME FILE
#     --blob NAME    name of the generated blob (e.g. DMALL_STRINGS, ALT_DMALL_STRINGS)
#     --check        only print statistics, don't write
#     --no-asserts   don't emit the compile-time static_asserts
#
# Run it after the generators (scripts/all_generate_embedded_assets.sh does). A file that already
# contains the "@string-blob" marker is left alone ("already processed"), so re-running is safe;
# regenerate the file (generators) to recompute offsets after adding sprites/strings.
# The generated tables reference X_OFF / BLOB, so forgetting this step is a compile error.
# =============================================================================
set -euo pipefail
export LC_ALL=C

BLOB=""
CHECK=0
ASSERTS=1
FILE=""

usage() { sed -n '/^# Usage:/,/^# Run it/p' "$0" | sed 's/^# \{0,1\}//'; }

while [[ $# -gt 0 ]]; do
    case "$1" in
        --blob) BLOB="${2:?--blob needs a name}"; shift 2 ;;
        --check) CHECK=1; shift ;;
        --no-asserts) ASSERTS=0; shift ;;
        -h|--help) usage; exit 0 ;;
        -*) echo "Unknown option: $1" >&2; usage >&2; exit 1 ;;
        *) [[ -z "$FILE" ]] || { echo "Only one FILE per call" >&2; exit 1; }; FILE="$1"; shift ;;
    esac
done

[[ -n "$BLOB" && -n "$FILE" ]] || { usage >&2; exit 1; }
[[ "$BLOB" =~ ^[A-Za-z_][A-Za-z0-9_]*$ ]] || { echo "Invalid blob name: $BLOB" >&2; exit 1; }
[[ -f "$FILE" ]] || { echo "File not found: $FILE" >&2; exit 1; }
command -v gawk >/dev/null || { echo "gawk is required" >&2; exit 1; }

if grep -q '@string-blob' "$FILE"; then
    echo "$FILE: already processed (@string-blob marker found), regenerate it to recompute offsets"
    exit 0
fi

TMP=$(mktemp)
trap 'rm -f "$TMP"' EXIT

gawk -v BLOB="$BLOB" -v CHECK="$CHECK" -v ASSERTS="$ASSERTS" -v FILE="$FILE" '
function fail(msg) { print FILE ": " msg > "/dev/stderr"; failed = 1; exit 1 }
function unescape(s,   t) {
    t = s
    gsub(/\\\\/, "\001", t)   # escaped backslash
    gsub(/\\"/, "\"", t)       # escaped quote
    if (index(t, "\\") > 0) return "\002"  # any other escape: unsupported
    gsub(/\001/, "\\", t)
    return t
}
{ line[NR] = $0 }
END {
    if (failed) exit 1
    n = 0; total_in = 0
    # pass 1: collect string constants
    for (i = 1; i <= NR; i++) {
        if (match(line[i], /^([ \t]*)(inline |static )?(inline |static )?constexpr char ([A-Za-z_][A-Za-z0-9_]*)_ARR\[\] ([A-Za-z_][A-Za-z0-9_]*)(\([A-Za-z0-9_]*\))? = "(.*)";[ \t]*$/, m)) {
            n++
            name[n] = m[4]; at[n] = i; raw[n] = m[7]
            indent[n] = m[1]; storage[n] = m[2] m[3]
            sec[n] = m[5]; secargs[n] = (m[6] != "")
            val[n] = unescape(m[7])
            if (val[n] == "\002") fail("line " i ": unsupported escape sequence in " m[4] "_ARR")
            if (index(val[n], "\0") > 0) fail("line " i ": embedded NUL in " m[4] "_ARR")
            if (name[n] in byname) fail("line " i ": duplicate constant " m[4] "_ARR")
            byname[name[n]] = n
            total_in += length(val[n]) + 1
        }
    }
    if (n == 0) fail("no string constants (X_ARR[] ... = \"...\";) found")
    for (k = 2; k <= n; k++)
        if (sec[k] != sec[1] || secargs[k] != secargs[1] || storage[k] != storage[1])
            fail("line " at[k] ": mixed storage/section (" storage[k] sec[k] " vs " storage[1] sec[1] "), one blob per kind")

    # pass 2: build the blob, longest first so shorter strings can share a suffix
    for (k = 1; k <= n; k++) keys[k] = sprintf("%08d %08d", 99999999 - length(val[k]), k)
    asort(keys)
    total = 0; stored = 0
    for (j = 1; j <= n; j++) {
        split(keys[j], kk, " "); k = kk[2] + 0
        s = val[k]
        if (s in seen) { off[k] = seen[s]; continue }
        off[k] = total
        stored++; order[stored] = k
        len = length(s)
        for (c = 0; c < len; c++) { suf = substr(s, c + 1); if (!(suf in seen)) seen[suf] = total + c }
        if (!("" in seen)) seen[""] = total + len
        total += len + 1
    }
    if (total > 4294967295) fail("blob too big for uint32_t offsets")

    if (CHECK) {
        printf "%s: %d strings, %d stored, blob %d bytes (before: %d bytes in %d arrays, saved %d bytes + per-array alignment padding)\n", FILE, n, stored, total + 1, total_in, n, total_in - total - 1
        exit 0
    }

    # pass 3: rewrite
    first = at[1]
    for (i = 1; i <= NR; i++) out_line[i] = line[i]
    for (k = 1; k <= n; k++) {
        i = at[k]
        o = indent[k] storage[k] "constexpr uint32_t " name[k] "_OFF = " off[k] ";"
        if (ASSERTS) o = o "\n" indent[k] "static_assert(::bongocat::assets::details::cstr_equal(" BLOB " + " name[k] "_OFF, \"" raw[k] "\"), \"re-run scripts/build_string_blobs.sh\");"
        out_line[i] = o
    }
    # the blob itself goes right before the first constant (all uses come after it)
    secexpr = sec[1] (secargs[1] ? "(" BLOB ")" : "")
    b = indent[1] "// @string-blob " BLOB " (generated by scripts/build_string_blobs.sh, " n " strings, " total + 1 " bytes)\n"
    b = b indent[1] storage[1] "constexpr char " BLOB "[] " secexpr " ="
    for (j = 1; j <= stored; j++) { k = order[j]; b = b "\n" indent[1] "    \"" raw[k] "\\0\"" }
    b = b ";\n"
    out_line[first] = b out_line[first]

    # rewrite the remaining references to X_ARR
    for (i = 1; i <= NR; i++) {
        t = out_line[i]
        if (index(t, "_ARR") == 0) continue
        while (match(t, /([A-Za-z_][A-Za-z0-9_]*)_ARR\>/, r)) {
            x = r[1]
            if (!(x in byname)) fail("line " i ": unknown reference " x "_ARR")
            k = byname[x]
            pre = substr(t, 1, RSTART - 1); post = substr(t, RSTART + RLENGTH)
            if (match(pre, /sizeof\($/) && match(post, /^\)-1/)) {
                t = substr(pre, 1, length(pre) - 7) length(val[k]) substr(post, 4)
            } else if (match(pre, /sizeof\($/) && match(post, /^\)/)) {
                t = substr(pre, 1, length(pre) - 7) (length(val[k]) + 1) substr(post, 2)
            } else {
                t = pre BLOB " + " x "_OFF" post
            }
        }
        out_line[i] = t
    }

    # uint32_t needs <cstdint>
    has_cstdint = 0; first_include = 0
    for (i = 1; i <= NR; i++) {
        if (line[i] ~ /^#include <cstdint>/) has_cstdint = 1
        if (!first_include && line[i] ~ /^#include /) first_include = i
    }
    if (!has_cstdint) {
        if (!first_include) fail("no #include line to add <cstdint> after")
        out_line[first_include] = out_line[first_include] "\n#include <cstdint>"
    }

    for (i = 1; i <= NR; i++) print out_line[i]
    printf "%s: %d strings -> %s (%d stored, %d bytes, was %d bytes in %d arrays)\n", FILE, n, BLOB, stored, total + 1, total_in, n > "/dev/stderr"
}
' "$FILE" > "$TMP"

if [[ "$CHECK" -eq 1 ]]; then
    cat "$TMP"
else
    cat "$TMP" > "$FILE"
fi
