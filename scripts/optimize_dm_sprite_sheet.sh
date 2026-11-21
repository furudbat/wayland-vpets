#!/bin/bash
# Optimize "Dm" layout sprite sheets (single row, 9-15 frames) by removing duplicated frames.
#
#   idle1 idle2 angry down1 happy eat1 sleep1 refuse sad [down2 eat2 sleep2 attack movement1 movement2]
#     0     1     2     3     4     5     6      7     8     9    10    11     12      13        14
#
# The loader (src/image_loader/base_dm/load_dm.cpp) maps frames by column, so frames in the middle can not be
# removed. Instead:
#
#   1. blank:  a frame that is identical to its BLANK_TARGET is replaced by a fully transparent cell,
#              the loader resolves blank cells to BLANK_TARGET (resolve_blank_dm_frames)
#   2. trim:   trailing frames (index >= 9) that are identical to their MISSING_TARGET are removed (cols shrink),
#              MISSING_TARGET is what the loader already uses when a frame does not exist
#
#   idx frame      BLANK_TARGET   MISSING_TARGET
#    2  angry      0 idle1        -
#    3  down1      1 idle2        -
#    4  happy      2 angry        -
#    5  eat1       2 angry        -
#    6  sleep1     3 down1        -
#    7  refuse     2 angry        -
#    8  sad        3 down1        -
#    9  down2      3 down1        1 idle2   (boring)
#   10  eat2       5 eat1         5 eat1    (unused)
#   11  sleep2     6 sleep1       0 idle1   (boring)
#   12  attack     2 angry        2 angry   (working)
#   13  movement1  0 idle1        0 idle1   (moving, running)
#   14  movement2  1 idle2        1 idle2   (moving, running)
#
# !!! BLANK_TARGET must be kept in sync with DM_BLANK_FALLBACK in src/image_loader/base_dm/load_dm.cpp !!!
#
# Two sprite sheets per sprite are optimized (and OVERWRITTEN) together:
#   OUTPUT_DIR/<name>.png         final (cropped) sprite sheet, frame size = width / cols
#   OUTPUT_INPUT_DIR/<name>.png   input sprite sheet with fixed frame size (--frame-size, default 128),
#                                 used to calculate the frame count (cols), see generate_embedded_assets.sh
# A frame is only blanked/trimmed when it is identical in both sheets.
#
# Optional (--unify-size): give all final sprite sheets the same frame size (OUTPUT_DIR only, cols stay the same).
#   auto   = biggest frame width and height of all processed sprite sheets
#   N, WxH = fixed size (sheets with bigger frames are skipped)
# Every frame is placed bottom-aligned (feet stay on the same level) and centered horizontally.

set -u

OUTPUT_DIR=""
OUTPUT_INPUT_DIR=""
SET_NAME=""
RECURSIVE=0
FRAME_SIZE=128
DRY_RUN=0
UNIFY_SIZE=""
ONLY_UNIFY=0

MIN_COLS=4       # loader requires idle1 idle2 angry down1
MIN_TRIM_COLS=9  # never trim below the 9 base frames
MAX_COLS=15
FRAME_NAMES=(idle1 idle2 angry down1 happy eat1 sleep1 refuse sad down2 eat2 sleep2 attack movement1 movement2)
BLANK_TARGET=(-1 -1 0 1 2 2 3 2 3 3 5 6 2 0 1)
MISSING_TARGET=(-1 -1 -1 -1 -1 -1 -1 -1 -1 1 5 0 2 0 1)

usage() {
    cat <<EOF
Usage: $0 --output OUTPUT_DIR --output-input OUTPUT_INPUT_DIR [--set SET] [-r] [--frame-size N] [--dry-run]
          [ASSETS_DIR | FILE...]

  --output DIR          final sprite sheets, e.g. assets (with --set dm) or assets/dm
                        the list of *.png files is taken from here
  --output-input DIR    fixed frame size sprite sheets with matching names, e.g. assets/input/dm
  --set SET             use OUTPUT_DIR/SET as final sprite sheet directory
  -r                    process all *.png in ASSETS_DIR (default: OUTPUT_DIR[/SET])
  --frame-size N        frame size of the OUTPUT_INPUT_DIR sheets (default: $FRAME_SIZE)
  --dry-run             only print what would be changed
  --unify-size SIZE     unify the frame size of all final sprite sheets: auto | N | WxH
                        (bottom-aligned, centered horizontally)
  --only-unify          skip the duplicate frame optimization, only unify the frame size
  ASSETS_DIR | FILE...  directory with final sprite sheets (-r) or single sprite sheets (names are matched)

Overwrites the files in OUTPUT_DIR and OUTPUT_INPUT_DIR.
EOF
}

# === Parse args ===
INPUTS=()
while [[ $# -gt 0 ]]; do
    case $1 in
        --output) OUTPUT_DIR="${2:-}"; shift 2 ;;
        --output-input) OUTPUT_INPUT_DIR="${2:-}"; shift 2 ;;
        --set) SET_NAME="${2:-}"; shift 2 ;;
        -r|--recursive) RECURSIVE=1; shift ;;
        --frame-size) FRAME_SIZE="${2:-}"; shift 2 ;;
        --dry-run) DRY_RUN=1; shift ;;
        --unify-size) UNIFY_SIZE="${2:-}"; shift 2 ;;
        --only-unify) ONLY_UNIFY=1; shift ;;
        -h|--help) usage; exit 0 ;;
        --) shift; INPUTS+=("$@"); break ;;
        -*) echo "Unknown option $1"; usage; exit 1 ;;
        *) INPUTS+=("$1"); shift ;;
    esac
done

[[ -z "$OUTPUT_DIR" ]] && { echo "ERROR: --output is required"; usage; exit 1; }
[[ -z "$OUTPUT_INPUT_DIR" ]] && { echo "ERROR: --output-input is required"; usage; exit 1; }
[[ "$FRAME_SIZE" =~ ^[1-9][0-9]*$ ]] || { echo "ERROR: invalid --frame-size '$FRAME_SIZE'"; exit 1; }
[[ -n "$SET_NAME" ]] && OUTPUT_DIR="$OUTPUT_DIR/$SET_NAME"
[[ -d "$OUTPUT_DIR" ]] || { echo "ERROR: output directory not found: $OUTPUT_DIR"; exit 1; }
[[ -d "$OUTPUT_INPUT_DIR" ]] || { echo "ERROR: output-input directory not found: $OUTPUT_INPUT_DIR"; exit 1; }
UNIFY_W=0
UNIFY_H=0
if [[ -n "$UNIFY_SIZE" ]]; then
    if [[ "$UNIFY_SIZE" == "auto" ]]; then
        :
    elif [[ "$UNIFY_SIZE" =~ ^([1-9][0-9]*)$ ]]; then
        UNIFY_W=${BASH_REMATCH[1]}; UNIFY_H=${BASH_REMATCH[1]}
    elif [[ "$UNIFY_SIZE" =~ ^([1-9][0-9]*)[xX]([1-9][0-9]*)$ ]]; then
        UNIFY_W=${BASH_REMATCH[1]}; UNIFY_H=${BASH_REMATCH[2]}
    else
        echo "ERROR: invalid --unify-size '$UNIFY_SIZE' (expected auto, N or WxH)"; exit 1
    fi
elif (( ONLY_UNIFY )); then
    echo "ERROR: --only-unify requires --unify-size"; exit 1
fi

if ! command -v magick &>/dev/null; then
    echo "ImageMagick v7+ (magick command) is required."
    exit 1
fi
PNG_OPTIMIZER=""
if command -v oxipng &>/dev/null; then
    PNG_OPTIMIZER="oxipng"
elif command -v optipng &>/dev/null; then
    PNG_OPTIMIZER="optipng"
fi

WORKDIR=$(mktemp -d)
trap 'rm -rf "$WORKDIR"' EXIT

optimized=0
unchanged=0
total_trimmed=0
total_blanked=0
skipped=0
failed=0
bytes_before=0
bytes_after=0

shopt -s nullglob

list_pngs() {
    find "$1" -maxdepth 1 -type f -iname '*.png' -print0 | sort -zV
}

file_size() {
    stat -c %s "$1"
}

optimize_png() {
    case $PNG_OPTIMIZER in
        oxipng) oxipng -q -o 4 --strip safe "$1" >/dev/null 2>&1 ;;
        optipng) optipng -quiet -o2 "$1" >/dev/null 2>&1 ;;
    esac
    return 0
}

# frame_info FILE FW FH -> lines "<filled 0|1> <md5>" per frame (reading order)
# Frames are compared as normalized 8-bit RGBA bytes, independent of the PNG color type (gray, palette, rgba):
# the color of fully transparent pixels is cleared (-alpha background), so invisible differences are ignored.
# Frames are stacked vertically (-append), so every frame is one contiguous block of FW*FH*4 bytes.
# frame_info FILE FW FH [SW SH SX SY]: optional, only use the region SWxSH+SX+SY of every frame
frame_info() {
    local file="$1" fw="$2" fh="$3" raw="$WORKDIR/frames.rgba" size total n i s zero
    local SUB=() rw="$fw" rh="$fh"
    if (( $# >= 7 )); then
        rw="$4"; rh="$5"
        SUB=(-crop "${4}x${5}+${6}+${7}" +repage)
    fi
    magick "$file[0]" -crop "${fw}x${fh}" +repage "${SUB[@]}" -background none -alpha background -append \
        -depth 8 "RGBA:$raw" 2>/dev/null || return 1
    size=$((rw * rh * 4))
    total=$(file_size "$raw")
    (( size > 0 && total % size == 0 )) || return 1
    n=$((total / size))
    zero=$(head -c "$size" /dev/zero | md5sum | cut -d' ' -f1)
    for ((i = 0; i < n; i++)); do
        s=$(tail -c +$((i * size + 1)) "$raw" | head -c "$size" | md5sum | cut -d' ' -f1)
        if [[ "$s" == "$zero" ]]; then echo "0 $s"; else echo "1 $s"; fi
    done
    rm -f "$raw"
}

# rebuild SRC DST FW FH OLD_COLS NEW_COLS BLANK_IDX...
# split into frames, replace blank frames with transparent cells, drop trimmed frames, append again
# (no -compose: a transparent overlay does not reliably clear a frame)
rebuild() {
    local src="$1" dst="$2" fw="$3" fh="$4" old_cols="$5" cols="$6"; shift 6
    local ARGS=(-background none "$src[0]" -crop "${fw}x${fh}" +repage) i
    for i in "$@"; do
        # put a transparent cell at index i: append new cell, swap with i, delete the old one (now last)
        ARGS+=( "(" -size "${fw}x${fh}" xc:none ")" -swap "$i,-1" +delete )
    done
    (( cols < old_cols )) && ARGS+=( -delete "$cols--1" )
    ARGS+=( +append +repage -define png:exclude-chunks=date,time "PNG:$dst" )
    magick "${ARGS[@]}" 2>/dev/null
}

# verify DST FW FH COLS BLANK_IDX... (expected signatures in global EXPECT_SIG)
# blank frames must be fully transparent, all other frames must be unchanged
verify() {
    local dst="$1" fw="$2" fh="$3" cols="$4"; shift 4
    local -A is_blank=() ; local b i=0 a s
    for b in "$@"; do is_blank[$b]=1; done
    while read -r a s; do
        if [[ -n "${is_blank[$i]:-}" ]]; then
            (( a == 0 )) || { echo "frame $i is not blank"; return 1; }
        elif [[ "$s" != "${EXPECT_SIG[$i]}" ]]; then
            echo "frame $i changed"; return 1
        fi
        i=$((i + 1))
    done < <(frame_info "$dst" "$fw" "$fh")
    (( i == cols )) || { echo "expected $cols frames, got $i"; return 1; }
    return 0
}

# process NAME
process() {
    local name="$1"
    local final="$OUTPUT_DIR/$name.png" input="$OUTPUT_INPUT_DIR/$name.png"
    if [[ ! -f "$final" ]]; then
        echo "WARN: skip '$name': '$final' not found"; skipped=$((skipped + 1)); return
    fi
    if [[ ! -f "$input" ]]; then
        echo "WARN: skip '$name': '$input' not found"; skipped=$((skipped + 1)); return
    fi

    local IW IH FW_ FH_
    read -r IW IH < <(magick identify -format "%w %h" "$input[0]" 2>/dev/null)
    read -r FW_ FH_ < <(magick identify -format "%w %h" "$final[0]" 2>/dev/null)
    if [[ -z "${IW:-}" || -z "${FW_:-}" ]]; then
        echo "ERROR: '$name': failed to read image size"; failed=$((failed + 1)); return
    fi
    if (( IH != FRAME_SIZE || IW % FRAME_SIZE != 0 )); then
        echo "WARN: skip '$name': '$input' (${IW}x${IH}) is not a single row of ${FRAME_SIZE}x${FRAME_SIZE} frames"
        skipped=$((skipped + 1)); return
    fi
    local cols=$((IW / FRAME_SIZE))
    if (( cols < MIN_COLS || cols > MAX_COLS )); then
        echo "WARN: skip '$name': $cols frames, expected $MIN_COLS-$MAX_COLS"; skipped=$((skipped + 1)); return
    fi
    if (( FW_ % cols != 0 )); then
        echo "WARN: skip '$name': '$final' width $FW_ is not divisible by $cols frames"; skipped=$((skipped + 1)); return
    fi
    local fw=$((FW_ / cols)) fh=$FH_

    # per frame: filled flag + signature (input and final sheet)
    local IN_FILLED=() IN_SIG=() FI_FILLED=() FI_SIG=() i=0 a s
    while read -r a s; do IN_FILLED[i]=$a; IN_SIG[i]=$s; i=$((i + 1)); done < <(frame_info "$input" "$FRAME_SIZE" "$FRAME_SIZE")
    (( i == cols )) || { echo "ERROR: '$name': failed to split '$input'"; failed=$((failed + 1)); return; }
    i=0
    while read -r a s; do FI_FILLED[i]=$a; FI_SIG[i]=$s; i=$((i + 1)); done < <(frame_info "$final" "$fw" "$fh")
    (( i == cols )) || { echo "ERROR: '$name': failed to split '$final'"; failed=$((failed + 1)); return; }

    local c
    for ((c = 0; c < 2; c++)); do
        if (( ! IN_FILLED[c] || ! FI_FILLED[c] )); then
            echo "WARN: skip '$name': frame $c (${FRAME_NAMES[$c]}) is blank"; skipped=$((skipped + 1)); return
        fi
    done

    # effective frame (what the loader shows) per column: blank cells resolve to BLANK_TARGET
    # ID[c] = column whose pixels are shown for frame c
    local ID=() BLANK=() notes=()
    for ((c = 0; c < cols; c++)); do
        ID[c]=$c
        if (( c >= 2 )); then
            if (( ! IN_FILLED[c] && ! FI_FILLED[c] )); then
                # already blank (optimized before)
                ID[c]=${ID[${BLANK_TARGET[$c]}]}
            elif (( ! IN_FILLED[c] || ! FI_FILLED[c] )); then
                echo "NOTE: '$name': frame $c (${FRAME_NAMES[$c]}) is blank only in one sheet, keep it"
            fi
        fi
    done
    same() { # same COL_A COL_B (compare shown pixels in both sheets)
        local x=${ID[$1]} y=${ID[$2]}
        [[ "${IN_SIG[$x]}" == "${IN_SIG[$y]}" && "${FI_SIG[$x]}" == "${FI_SIG[$y]}" ]]
    }
    for ((c = 2; c < cols; c++)); do
        (( IN_FILLED[c] && FI_FILLED[c] )) || continue
        local t=${BLANK_TARGET[$c]}
        if same "$c" "$t"; then
            BLANK+=("$c")
            notes+=("$c ${FRAME_NAMES[$c]}->${FRAME_NAMES[$t]}")
            ID[c]=${ID[$t]}
        elif [[ "${IN_SIG[$c]}" == "${IN_SIG[${ID[$t]}]}" ]]; then
            echo "NOTE: '$name': frame $c (${FRAME_NAMES[$c]}) equals ${FRAME_NAMES[$t]} only in '$input', keep it"
        fi
    done

    # trim trailing frames that are identical to what the loader uses when the frame is missing
    local new_cols=$cols
    while (( new_cols > MIN_TRIM_COLS )); do
        c=$((new_cols - 1))
        same "$c" "${MISSING_TARGET[$c]}" || break
        new_cols=$c
    done

    # blank cells beyond new_cols are trimmed anyway
    local BLANK_KEEP=() NOTES_KEEP=() b
    for b in "${!BLANK[@]}"; do
        if (( BLANK[b] < new_cols )); then
            BLANK_KEEP+=("${BLANK[$b]}"); NOTES_KEEP+=("${notes[$b]}")
        fi
    done

    local trimmed=$((cols - new_cols)) blanked=${#BLANK_KEEP[@]}
    if (( blanked == 0 && trimmed == 0 )); then
        unchanged=$((unchanged + 1))
        return
    fi
    total_trimmed=$((total_trimmed + trimmed))
    total_blanked=$((total_blanked + blanked))

    local info="cols $cols"
    (( trimmed > 0 )) && info+="->$new_cols"
    info+=" trimmed=$trimmed duplicates=$blanked"
    (( blanked > 0 )) && info+=" blank[$(IFS=,; echo "${NOTES_KEEP[*]}" | sed 's/,/, /g')]"
    if (( DRY_RUN )); then
        echo "Would optimize: $name $info"
        optimized=$((optimized + 1))
        return
    fi

    local tmp_in="$WORKDIR/in.png" tmp_final="$WORKDIR/final.png"
    if ! rebuild "$input" "$tmp_in" "$FRAME_SIZE" "$FRAME_SIZE" "$cols" "$new_cols" "${BLANK_KEEP[@]}" \
        || ! rebuild "$final" "$tmp_final" "$fw" "$fh" "$cols" "$new_cols" "${BLANK_KEEP[@]}"; then
        echo "ERROR: '$name': failed to rebuild sprite sheets"; failed=$((failed + 1)); return
    fi
    optimize_png "$tmp_in"
    optimize_png "$tmp_final"

    # check the result before overwriting anything
    local err
    EXPECT_SIG=("${IN_SIG[@]}")
    if ! err=$(verify "$tmp_in" "$FRAME_SIZE" "$FRAME_SIZE" "$new_cols" "${BLANK_KEEP[@]}"); then
        echo "ERROR: '$name': verify '$input' failed: $err (not written)"; failed=$((failed + 1)); return
    fi
    EXPECT_SIG=("${FI_SIG[@]}")
    if ! err=$(verify "$tmp_final" "$fw" "$fh" "$new_cols" "${BLANK_KEEP[@]}"); then
        echo "ERROR: '$name': verify '$final' failed: $err (not written)"; failed=$((failed + 1)); return
    fi

    local before_in before_final after_in after_final
    before_in=$(file_size "$input"); before_final=$(file_size "$final")
    after_in=$(file_size "$tmp_in"); after_final=$(file_size "$tmp_final")
    mv -f "$tmp_in" "$input" && mv -f "$tmp_final" "$final" \
        || { echo "ERROR: '$name': failed to overwrite sprite sheets"; failed=$((failed + 1)); return; }
    bytes_before=$((bytes_before + before_final)); bytes_after=$((bytes_after + after_final))
    echo "Optimized: $name $info final ${before_final}B->${after_final}B input ${before_in}B->${after_in}B"
    optimized=$((optimized + 1))
}

# === Unify frame size ===
unified=0
unify_unchanged=0
unify_skipped=0

# sheet_dims NAME -> "cols fw fh" of the final sheet (cols from the input sheet)
sheet_dims() {
    local name="$1" final="$OUTPUT_DIR/$1.png" input="$OUTPUT_INPUT_DIR/$1.png" IW IH W H cols
    [[ -f "$final" && -f "$input" ]] || return 1
    read -r IW IH < <(magick identify -format "%w %h" "$input[0]" 2>/dev/null)
    read -r W H < <(magick identify -format "%w %h" "$final[0]" 2>/dev/null)
    [[ -n "${IW:-}" && -n "${W:-}" ]] || return 1
    (( IW % FRAME_SIZE == 0 )) || return 1
    cols=$((IW / FRAME_SIZE))
    (( cols > 0 && W % cols == 0 )) || return 1
    echo "$cols $((W / cols)) $H"
}

# unify NAME TW TH
unify() {
    local name="$1" tw="$2" th="$3" final="$OUTPUT_DIR/$1.png" dims cols fw fh
    if ! dims=$(sheet_dims "$name"); then
        echo "WARN: unify skip '$name': can not read sprite sheet size"; unify_skipped=$((unify_skipped + 1)); return
    fi
    read -r cols fw fh <<< "$dims"
    if (( fw == tw && fh == th )); then
        unify_unchanged=$((unify_unchanged + 1)); return
    fi
    if (( fw > tw || fh > th )); then
        echo "WARN: unify skip '$name': frame ${fw}x${fh} is bigger than ${tw}x${th}"
        unify_skipped=$((unify_skipped + 1)); return
    fi
    # bottom-aligned (feet on the same level), centered horizontally
    local x=$(((tw - fw) / 2)) y=$((th - fh))
    if (( DRY_RUN )); then
        echo "Would unify: $name frame ${fw}x${fh} -> ${tw}x${th} (offset +$x+$y)"
        unified=$((unified + 1)); return
    fi

    local tmp="$WORKDIR/unified.png" before after
    if ! magick -background none "$final[0]" -crop "${fw}x${fh}" +repage \
        -gravity NorthWest -extent "${tw}x${th}-${x}-${y}" +append +repage \
        -define png:exclude-chunks=date,time "PNG:$tmp" 2>/dev/null; then
        echo "ERROR: '$name': failed to unify frame size"; failed=$((failed + 1)); return
    fi
    optimize_png "$tmp"

    # verify: same frame count, every original frame unchanged at its new position
    local W H
    read -r W H < <(magick identify -format "%w %h" "$tmp" 2>/dev/null)
    if [[ "${W:-}x${H:-}" != "$((cols * tw))x${th}" ]]; then
        echo "ERROR: '$name': unify verify failed: size ${W:-?}x${H:-?}, expected $((cols * tw))x${th} (not written)"
        failed=$((failed + 1)); return
    fi
    local orig new
    orig=$(frame_info "$final" "$fw" "$fh" | cut -d' ' -f2)
    new=$(frame_info "$tmp" "$tw" "$th" "$fw" "$fh" "$x" "$y" | cut -d' ' -f2)
    if [[ -z "$orig" || "$orig" != "$new" ]]; then
        echo "ERROR: '$name': unify verify failed: frames changed (not written)"; failed=$((failed + 1)); return
    fi

    before=$(file_size "$final"); after=$(file_size "$tmp")
    mv -f "$tmp" "$final" || { echo "ERROR: '$name': failed to overwrite '$final'"; failed=$((failed + 1)); return; }
    echo "Unified: $name frame ${fw}x${fh} -> ${tw}x${th} ${before}B->${after}B"
    unified=$((unified + 1))
}

# unify_all NAME...
unify_all() {
    local tw=$UNIFY_W th=$UNIFY_H name dims cols fw fh
    if [[ "$UNIFY_SIZE" == "auto" ]]; then
        for name in "$@"; do
            dims=$(sheet_dims "$name") || continue
            read -r cols fw fh <<< "$dims"
            (( fw > tw )) && tw=$fw
            (( fh > th )) && th=$fh
        done
        (( tw > 0 && th > 0 )) || { echo "ERROR: unify: no sprite sheet sizes found"; failed=$((failed + 1)); return; }
        echo "Unify frame size (biggest frame): ${tw}x${th}"
    else
        echo "Unify frame size: ${tw}x${th}"
    fi
    for name in "$@"; do
        unify "$name" "$tw" "$th"
    done
}

# === Collect names ===
NAMES=()
add_dir() {
    local f n
    while IFS= read -r -d '' f; do
        n=$(basename "$f"); NAMES+=("${n%.*}")
    done < <(list_pngs "$1")
}
if (( ${#INPUTS[@]} == 0 )); then
    add_dir "$OUTPUT_DIR"
else
    for p in "${INPUTS[@]}"; do
        if [[ -d "$p" ]]; then
            (( RECURSIVE )) || { echo "ERROR: '$p' is a directory (use -r)"; exit 1; }
            add_dir "$p"
        else
            n=$(basename "$p"); NAMES+=("${n%.*}")
        fi
    done
fi
(( ${#NAMES[@]} > 0 )) || { echo "ERROR: no sprite sheets found"; exit 1; }

if (( ! ONLY_UNIFY )); then
    for name in "${NAMES[@]}"; do
        process "$name"
    done
fi
# unify after the optimization (trimming changes cols, not the frame size)
[[ -n "$UNIFY_SIZE" ]] && unify_all "${NAMES[@]}"

summary="Done:"
if (( ! ONLY_UNIFY )); then
    summary+=" optimized=$optimized unchanged=$unchanged skipped=$skipped"
    summary+=" frames trimmed (end)=$total_trimmed duplicates removed (blanked)=$total_blanked"
fi
[[ -n "$UNIFY_SIZE" ]] && summary+=" unified=$unified unify-unchanged=$unify_unchanged unify-skipped=$unify_skipped"
summary+=" failed=$failed"
(( ! DRY_RUN )) && summary+=" final bytes $bytes_before->$bytes_after (optimized files)"
echo "$summary"
[[ $failed -eq 0 ]]
