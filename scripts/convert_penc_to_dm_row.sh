#!/bin/bash
# Convert "penc" 3x4 sprite sheets into the old single-row Dm layout
# (13 frames of 128x128 = 1664x128), so the existing generate scripts can consume them.
#
# penc layout (col,row), cell size = sheet_width/3 x sheet_height/4 (e.g. 48x48):
#   Walk 1    (0,0) | Walk 2    (1,0) | Eat 1   (2,0)
#   Eat 2*    (0,1) | Sleep 1   (1,1) | Sleep 2 (2,1)
#   Refuse**  (0,2) | Happy     (1,2) | Angry   (2,2)
#   Injured 1 (0,3) | Injured 2 (1,3) | Attack  (2,3)
#   *  also used for Happy
#   ** also used for Angry and Attack
#
# Blank (fully transparent) cells are replaced with a fallback cell (see FALLBACK).
#
# Sub format "penc + cutout" (--skip-cutout): same 3x4 grid at the top-left, plus extra
# sprite(s) below it (e.g. the cutout/portrait row), which are ignored. The cell size can't
# be derived from the sheet size, so it is given by --frame-width/--frame-height (default 48x48).
#
# Usage: $0 [input-dir] [og-output-dir] [cropped-output-dir] [--scale N] [--force] [--no-crop]
#           [--skip-cutout [--frame-width W] [--frame-height H]]

INPUT_DIR="assets/input/all-dmc"
OG_OUTPUT_DIR="assets/input/all-colored-2"
CROPPED_OUTPUT_DIR="assets/dmall"
FORCE=0
NO_CROP=0
SCALE=1
SKIP_CUTOUT=0
CUT_FRAME_W=48   # only used with --skip-cutout
CUT_FRAME_H=48   # only used with --skip-cutout

FRAME_SIZE=128
BOTTOM_Y=110  # sprite bottom line inside a 128x128 frame (matches existing sheets)
CROP_PADDING=4
CROP_SCRIPT="./scripts/crop_spritesheet.sh"

# penc cell index = row*3 + col
WALK1=0; WALK2=1; EAT1=2
EAT2=3; SLEEP1=4; SLEEP2=5
REFUSE=6; HAPPY=7; ANGRY=8
INJURED1=9; INJURED2=10; ATTACK=11
CELL_NAMES=("Walk 1" "Walk 2" "Eat 1" "Eat 2" "Sleep 1" "Sleep 2" "Refuse" "Happy" "Angry" "Injured 1" "Injured 2" "Attack")

# fallback chain per penc cell (first non-blank wins)
FALLBACK=(
    "$WALK2"                                   # Walk 1
    "$WALK1"                                   # Walk 2
    "$EAT2 $WALK1"                             # Eat 1
    "$HAPPY $EAT1 $WALK2"                      # Eat 2
    "$SLEEP2 $INJURED1 $WALK1"                 # Sleep 1
    "$SLEEP1 $INJURED2 $WALK2"                 # Sleep 2
    "$ANGRY $WALK1"                            # Refuse
    "$EAT2 $WALK2"                             # Happy
    "$REFUSE $ATTACK $WALK1"                   # Angry
    "$INJURED2 $SLEEP1 $WALK1"                 # Injured 1
    "$INJURED1 $SLEEP2 $WALK2"                 # Injured 2
    "$REFUSE $ANGRY $WALK1"                    # Attack
)

# old frame index -> penc cell
MAP=(
    "$WALK1"     #  0 idle1
    "$WALK2"     #  1 idle2
    "$ANGRY"     #  2 angry
    "$INJURED1"  #  3 down1
    "$HAPPY"     #  4 happy
    "$EAT1"      #  5 eat1
    "$SLEEP1"    #  6 sleep1
    "$REFUSE"    #  7 refuse
    "$INJURED1"  #  8 sad
    "$INJURED2"  #  9 down2
    "$EAT2"      # 10 eat2
    "$SLEEP2"    # 11 sleep2
    "$ATTACK"    # 12 attack
)

usage() {
    echo "Usage: $0 [input-dir=$INPUT_DIR] [og-output-dir=$OG_OUTPUT_DIR] [cropped-output-dir=$CROPPED_OUTPUT_DIR] [--scale N] [--force] [--no-crop]"
    echo "          [--skip-cutout [--frame-width W=$CUT_FRAME_W] [--frame-height H=$CUT_FRAME_H]]"
    echo ""
    echo "  --skip-cutout       sheet has extra sprite(s) below the 3x4 grid (ignored);"
    echo "                      only the top-left 3x4 frames of --frame-width x --frame-height are used"
    echo "  --frame-width W     frame width  (default: 48, only used with --skip-cutout)"
    echo "  --frame-height H    frame height (default: 48, only used with --skip-cutout)"
}

# === Parse args ===
POSITIONAL_ARGS=()
while [[ $# -gt 0 ]]; do
    case $1 in
        --force) FORCE=1; shift ;;
        --no-crop) NO_CROP=1; shift ;;
        --scale) SCALE="$2"; shift 2 ;;
        --skip-cutout) SKIP_CUTOUT=1; shift ;;
        --frame-width) CUT_FRAME_W="$2"; shift 2 ;;
        --frame-height) CUT_FRAME_H="$2"; shift 2 ;;
        -h|--help) usage; exit 0 ;;
        -*) echo "Unknown option $1"; usage; exit 1 ;;
        *) POSITIONAL_ARGS+=("$1"); shift ;;
    esac
done
INPUT_DIR="${POSITIONAL_ARGS[0]:-$INPUT_DIR}"
OG_OUTPUT_DIR="${POSITIONAL_ARGS[1]:-$OG_OUTPUT_DIR}"
CROPPED_OUTPUT_DIR="${POSITIONAL_ARGS[2]:-$CROPPED_OUTPUT_DIR}"

if ! [[ "$SCALE" =~ ^[1-9][0-9]*$ ]]; then
    echo "--scale must be a positive integer"
    exit 1
fi
if ! [[ "$CUT_FRAME_W" =~ ^[1-9][0-9]*$ && "$CUT_FRAME_H" =~ ^[1-9][0-9]*$ ]]; then
    echo "--frame-width/--frame-height must be positive integers"
    exit 1
fi

# === Dependency check ===
if ! command -v magick &>/dev/null; then
    echo "ImageMagick v7+ (magick command) is required."
    exit 1
fi
if [[ ! -d "$INPUT_DIR" ]]; then
    echo "Input dir not found: $INPUT_DIR"
    exit 1
fi
if [[ $NO_CROP -eq 0 && ! -f "$CROP_SCRIPT" ]]; then
    echo "Crop script not found: $CROP_SCRIPT"
    exit 1
fi

mkdir -p "$OG_OUTPUT_DIR"
[[ $NO_CROP -eq 0 ]] && mkdir -p "$CROPPED_OUTPUT_DIR"

SHEET_W=$((FRAME_SIZE * ${#MAP[@]}))

crop_sheet() {
    bash "$CROP_SCRIPT" "$1" "$2" --frame-size "$FRAME_SIZE" --padding "$CROP_PADDING" >/dev/null 2>&1
}

converted=0
skipped=0
failed=0

shopt -s nullglob
for FILE in "$INPUT_DIR"/*.png; do
    BASENAME=$(basename "$FILE")
    OG_OUT="$OG_OUTPUT_DIR/$BASENAME"
    CROPPED_OUT="$CROPPED_OUTPUT_DIR/$BASENAME"

    if [[ -e "$OG_OUT" && $FORCE -eq 0 ]]; then
        echo "WARN: skip '$BASENAME': already exists in $OG_OUTPUT_DIR (use --force to overwrite)"
        # cropped output may have been wiped (e.g. by update_sprites.sh) -> restore it
        if [[ $NO_CROP -eq 0 && ! -e "$CROPPED_OUT" ]]; then
            echo "  re-cropping missing '$CROPPED_OUT'"
            crop_sheet "$OG_OUT" "$CROPPED_OUT" || { echo "ERROR: failed to crop '$BASENAME'"; failed=$((failed + 1)); }
        fi
        skipped=$((skipped + 1))
        continue
    fi

    # === Frame size ===
    read -r W H < <(magick identify -format "%w %h" "$FILE" 2>/dev/null)
    if [[ -z "$W" || -z "$H" ]]; then
        echo "ERROR: '$BASENAME': failed to read image size"
        failed=$((failed + 1))
        continue
    fi
    if (( SKIP_CUTOUT )); then
        # 3x4 grid of given frame size at the top-left, everything else (cutout) is ignored
        CELL_W=$CUT_FRAME_W
        CELL_H=$CUT_FRAME_H
        if (( W < CELL_W * 3 || H < CELL_H * 4 )); then
            echo "WARN: skip '$BASENAME': size ${W}x${H} is too small for a 3x4 grid of ${CELL_W}x${CELL_H} frames"
            skipped=$((skipped + 1))
            continue
        fi
    else
        # whole sheet is exactly 3 cols x 4 rows
        if (( W % 3 != 0 || H % 4 != 0 )); then
            echo "WARN: skip '$BASENAME': size ${W}x${H} is not divisible into a 3x4 grid"
            skipped=$((skipped + 1))
            continue
        fi
        CELL_W=$((W / 3))
        CELL_H=$((H / 4))
    fi
    GRID_W=$((CELL_W * 3))
    GRID_H=$((CELL_H * 4))
    OUT_W=$((CELL_W * SCALE))
    OUT_H=$((CELL_H * SCALE))
    if (( OUT_W > FRAME_SIZE || OUT_H > BOTTOM_Y )); then
        echo "WARN: skip '$BASENAME': frame ${CELL_W}x${CELL_H} (x${SCALE}) does not fit into ${FRAME_SIZE}x${BOTTOM_Y}"
        skipped=$((skipped + 1))
        continue
    fi
    if (( CELL_W != CELL_H )); then
        if (( SKIP_CUTOUT )); then
            echo "NOTE: '$BASENAME': non-square frame ${CELL_W}x${CELL_H}"
        else
            echo "NOTE: '$BASENAME': non-square frame ${CELL_W}x${CELL_H} (sheet with cutout? try --skip-cutout)"
        fi
    fi

    # === Detect blank cells (row-major, fully transparent = blank) ===
    read -r -a FILLED < <(magick "$FILE" -crop "${GRID_W}x${GRID_H}+0+0" +repage \
        -crop "${CELL_W}x${CELL_H}" +repage -alpha extract \
        -format "%[fx:maxima>0?1:0] " info: 2>/dev/null)
    if (( ${#FILLED[@]} != 12 )); then
        echo "ERROR: '$BASENAME': failed to analyze frames"
        failed=$((failed + 1))
        continue
    fi

    # resolve each penc cell to a non-blank source cell
    RESOLVED=()
    for c in "${!FILLED[@]}"; do
        if (( FILLED[c] )); then
            RESOLVED[c]=$c
            continue
        fi
        RESOLVED[c]=-1
        for f in ${FALLBACK[$c]}; do
            if (( FILLED[f] )); then RESOLVED[c]=$f; break; fi
        done
        if (( RESOLVED[c] < 0 )); then
            # last resort: first non-blank cell
            for f in "${!FILLED[@]}"; do
                if (( FILLED[f] )); then RESOLVED[c]=$f; break; fi
            done
        fi
    done
    if (( RESOLVED[WALK1] < 0 )); then
        echo "WARN: skip '$BASENAME': all frames are blank"
        skipped=$((skipped + 1))
        continue
    fi

    # report fallbacks only for cells actually used in the output
    for i in "${!MAP[@]}"; do
        c=${MAP[$i]}
        if (( RESOLVED[c] != c )); then
            echo "NOTE: '$BASENAME': '${CELL_NAMES[$c]}' is blank, using '${CELL_NAMES[${RESOLVED[$c]}]}' (frame $i)"
        fi
    done

    # === Build 1664x128 row sheet: sprite centered horizontally, bottom at BOTTOM_Y ===
    POS_X=$(( (FRAME_SIZE - OUT_W) / 2 ))
    POS_Y=$(( BOTTOM_Y - OUT_H ))
    ARGS=(-size "${SHEET_W}x${FRAME_SIZE}" xc:none)
    for i in "${!MAP[@]}"; do
        src=${RESOLVED[${MAP[$i]}]}
        C=$((src % 3))
        R=$((src / 3))
        ARGS+=( "(" "$FILE" -crop "${CELL_W}x${CELL_H}+$((C * CELL_W))+$((R * CELL_H))" +repage )
        (( SCALE > 1 )) && ARGS+=( -filter point -resize "${OUT_W}x${OUT_H}!" )
        ARGS+=( ")" -geometry "+$((i * FRAME_SIZE + POS_X))+${POS_Y}" -composite )
    done

    if ! magick "${ARGS[@]}" "PNG32:$OG_OUT"; then
        echo "ERROR: failed to convert '$BASENAME'"
        failed=$((failed + 1))
        continue
    fi
    echo "Converted: $BASENAME (frame ${CELL_W}x${CELL_H}) -> $OG_OUT"

    if [[ $NO_CROP -eq 0 ]]; then
        if [[ -e "$CROPPED_OUT" && $FORCE -eq 0 ]]; then
            echo "WARN: '$CROPPED_OUT' already exists, not cropping (use --force to overwrite)"
        elif ! crop_sheet "$OG_OUT" "$CROPPED_OUT"; then
            echo "ERROR: failed to crop '$BASENAME'"
            failed=$((failed + 1))
            continue
        fi
    fi
    converted=$((converted + 1))
done

echo "Done: converted=$converted skipped=$skipped failed=$failed"
[[ $failed -eq 0 ]]
