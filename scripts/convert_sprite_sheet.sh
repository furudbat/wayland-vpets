#!/bin/bash
# Convert "dmc" (1x12) or "penc" (3x4, optional cutin) sprite sheets / frame files into
# the custom single-row Dm layout (13 frames):
#
#   idle1 idle2 angry down1 happy eat1 sleep1 refuse sad down2 eat2 sleep2 attack
#
# Two outputs per sprite:
#   OUTPUT_INPUT_DIR/<set>/<name>.png  fixed 128x128 frames, every source cell centered
#   OUTPUT_DIR/<set>/<name>.png        same, cropped to the content (crop_spritesheet.sh)
#
# Source formats (cell index in reading order, row-major):
#   dmc  (1x12): idle_1 idle_2 happy angry training attacking eating_1 eating_2 refusing sleep_1 sleep_2 sick
#   dmc15 (1x15): idle_1 idle_2 happy angry training_1 training_2 attacking_1 attacking_2
#                 eating_1 eating_2 refuse sleep_1 sleep_2 sick_1 sick_2
#   penc (3x4) : idle_1   idle_2  eating_1
#                eating_2 sleep_1 sleep_2
#                refusing happy   angry
#                sick_1   sick_2  attack
#                [cutin ...]      (only with --cutin, ignored)
#
# Blank (fully transparent) or missing cells are replaced by a fallback cell.
#
# Inputs (FILE_OR_DIR_OR_FILES...):
#   sheet.png                     one sprite sheet               -> name = "sheet"
#   name/0.png name/1.png ...     frame files (>= 12)            -> name = "name" (parent dir)
#   name/                         dir with frame files           -> name = "name"
#   -r set/                       set/*.png sheets and set/*/ frame dirs (1 level deep)
#                                                                -> one output per sheet/dir

set -u

OUTPUT_DIR="assets"
OUTPUT_INPUT_DIR="assets/input"
FORMAT=""
SET_NAME=""
RECURSIVE=0
CUTIN=0
FRAME_SIZE_ARG=""
FORCE=0

FRAME_SIZE=128
CROP_PADDING=4
CROP_SCRIPT="$(dirname "$0")/crop_spritesheet.sh"
NUM_CELLS=12

usage() {
    cat <<EOF
Usage: $0 (--dmc | --dmc15 | --penc) --set PREFIX_NAME [-r] [--cutin --frame-size FRAME_SIZE]
          [--output OUTPUT_DIR] [--output-input OUTPUT_INPUT_DIR] [--force] FILE_OR_DIR_OR_FILES...

  --dmc | --dmc15 | --penc    source format (required): dmc 1x12, dmc15 1x15, penc 3x4
  --set PREFIX_NAME           output set name, e.g. dm, dm20, dmc (required)
  -r                          scan directory one level deep: set/*.png (sheets) and set/*/ (frame dirs)
  --cutin                     sheet has extra cutin below the frames, only the first 12 (dmc15: 15) frames are used
                              (requires --frame-size)
  --frame-size N | WxH        source frame size, e.g. 48 (=48x48) or 64x48
                              (default: derived from the sheet size)
  --output OUTPUT_DIR         cropped output        -> OUTPUT_DIR/PREFIX_NAME/<name>.png (default: $OUTPUT_DIR)
  --output-input DIR          128x128 frames output -> DIR/PREFIX_NAME/<name>.png        (default: $OUTPUT_INPUT_DIR)
  --force                     overwrite existing outputs
EOF
}

# === Parse args ===
INPUTS=()
while [[ $# -gt 0 ]]; do
    case $1 in
        --dmc) FORMAT="dmc"; shift ;;
        --dmc15) FORMAT="dmc15"; shift ;;
        --penc) FORMAT="penc"; shift ;;
        --set) SET_NAME="${2:-}"; shift 2 ;;
        -r|--recursive) RECURSIVE=1; shift ;;
        --cutin) CUTIN=1; shift ;;
        --frame-size) FRAME_SIZE_ARG="${2:-}"; shift 2 ;;
        --output) OUTPUT_DIR="${2:-}"; shift 2 ;;
        --output-input) OUTPUT_INPUT_DIR="${2:-}"; shift 2 ;;
        --force) FORCE=1; shift ;;
        -h|--help) usage; exit 0 ;;
        --) shift; INPUTS+=("$@"); break ;;
        -*) echo "Unknown option $1"; usage; exit 1 ;;
        *) INPUTS+=("$1"); shift ;;
    esac
done

[[ -z "$FORMAT" ]] && { echo "ERROR: --dmc, --dmc15 or --penc is required"; usage; exit 1; }
[[ -z "$SET_NAME" ]] && { echo "ERROR: --set is required"; usage; exit 1; }
(( ${#INPUTS[@]} == 0 )) && { echo "ERROR: no input file/directory given"; usage; exit 1; }
[[ -z "$OUTPUT_DIR" || -z "$OUTPUT_INPUT_DIR" ]] && { echo "ERROR: empty output directory"; exit 1; }

SRC_FW=""
SRC_FH=""
if [[ -n "$FRAME_SIZE_ARG" ]]; then
    if [[ "$FRAME_SIZE_ARG" =~ ^([1-9][0-9]*)$ ]]; then
        SRC_FW=${BASH_REMATCH[1]}; SRC_FH=${BASH_REMATCH[1]}
    elif [[ "$FRAME_SIZE_ARG" =~ ^([1-9][0-9]*)[xX]([1-9][0-9]*)$ ]]; then
        SRC_FW=${BASH_REMATCH[1]}; SRC_FH=${BASH_REMATCH[2]}
    else
        echo "ERROR: invalid --frame-size '$FRAME_SIZE_ARG' (expected N or WxH)"
        exit 1
    fi
fi
if (( CUTIN )) && [[ -z "$SRC_FW" ]]; then
    echo "ERROR: --cutin requires --frame-size"
    exit 1
fi

# === Dependency check ===
if ! command -v magick &>/dev/null; then
    echo "ImageMagick v7+ (magick command) is required."
    exit 1
fi
if [[ ! -f "$CROP_SCRIPT" ]]; then
    echo "Crop script not found: $CROP_SCRIPT"
    exit 1
fi

# === Format definitions ===
# CELL_NAMES: source cells in reading order
# FALLBACK:   fallback chain per source cell (first non-blank wins)
# MAP:        output frame index -> source cell
# GRID_COLS/GRID_ROWS: default sheet layout (used when --frame-size is not given)
OUT_NAMES=(idle1 idle2 angry down1 happy eat1 sleep1 refuse sad down2 eat2 sleep2 attack)
case $FORMAT in
    dmc)
        IDLE1=0; IDLE2=1; HAPPY=2; ANGRY=3; TRAINING=4; ATTACK=5
        EAT1=6; EAT2=7; REFUSE=8; SLEEP1=9; SLEEP2=10; SICK=11
        CELL_NAMES=("idle_1" "idle_2" "happy" "angry" "training" "attacking"
                    "eating_1" "eating_2" "refusing" "sleep_1" "sleep_2" "sick")
        FALLBACK=(
            "$IDLE2"                       # idle_1
            "$IDLE1"                       # idle_2
            "$EAT2 $IDLE2"                 # happy
            "$REFUSE $ATTACK $IDLE1"       # angry
            "$ATTACK $IDLE1"               # training
            "$TRAINING $ANGRY $IDLE1"      # attacking
            "$EAT2 $IDLE1"                 # eating_1
            "$EAT1 $HAPPY $IDLE2"          # eating_2
            "$ANGRY $IDLE1"                # refusing
            "$SLEEP2 $SICK $IDLE1"         # sleep_1
            "$SLEEP1 $SICK $IDLE2"         # sleep_2
            "$SLEEP1 $IDLE1"               # sick
        )
        MAP=(
            "$IDLE1"   #  0 idle1
            "$IDLE2"   #  1 idle2
            "$ANGRY"   #  2 angry
            "$SICK"    #  3 down1
            "$HAPPY"   #  4 happy
            "$EAT2"    #  5 eat1
            "$SLEEP1"  #  6 sleep1
            "$REFUSE"  #  7 refuse
            "$SICK"    #  8 sad
            "$SICK"    #  9 down2
            "$EAT1"    # 10 eat2
            "$SLEEP2"  # 11 sleep2
            "$ATTACK"  # 12 attack
        )
        GRID_COLS=12; GRID_ROWS=1
        ;;
    dmc15)
        IDLE1=0; IDLE2=1; HAPPY=2; ANGRY=3; TRAINING1=4; TRAINING2=5; ATTACK1=6; ATTACK2=7
        EAT1=8; EAT2=9; REFUSE=10; SLEEP1=11; SLEEP2=12; SICK1=13; SICK2=14
        CELL_NAMES=("idle_1" "idle_2" "happy" "angry" "training_1" "training_2" "attacking_1" "attacking_2"
                    "eating_1" "eating_2" "refuse" "sleep_1" "sleep_2" "sick_1" "sick_2")
        FALLBACK=(
            "$IDLE2"                            # idle_1
            "$IDLE1"                            # idle_2
            "$EAT2 $IDLE2"                      # happy
            "$REFUSE $ATTACK1 $IDLE1"           # angry
            "$TRAINING2 $ATTACK1 $IDLE1"        # training_1
            "$TRAINING1 $ATTACK2 $IDLE2"        # training_2
            "$ATTACK2 $TRAINING1 $ANGRY $IDLE1" # attacking_1
            "$ATTACK1 $TRAINING2 $ANGRY $IDLE2" # attacking_2
            "$EAT2 $IDLE1"                      # eating_1
            "$EAT1 $HAPPY $IDLE2"               # eating_2
            "$ANGRY $IDLE1"                     # refuse
            "$SLEEP2 $SICK1 $IDLE1"             # sleep_1
            "$SLEEP1 $SICK2 $IDLE2"             # sleep_2
            "$SICK2 $SLEEP1 $IDLE1"             # sick_1
            "$SICK1 $SLEEP2 $IDLE2"             # sick_2
        )
        MAP=(
            "$IDLE1"    #  0 idle1
            "$IDLE2"    #  1 idle2
            "$ANGRY"    #  2 angry
            "$SICK1"    #  3 down1
            "$HAPPY"    #  4 happy
            "$EAT2"     #  5 eat1
            "$SLEEP1"   #  6 sleep1
            "$REFUSE"   #  7 refuse
            "$SICK1"    #  8 sad
            "$SICK2"    #  9 down2
            "$EAT1"     # 10 eat2
            "$SLEEP2"   # 11 sleep2
            "$ATTACK2"  # 12 attack
        )
        GRID_COLS=15; GRID_ROWS=1; NUM_CELLS=15
        ;;
    penc)
        IDLE1=0; IDLE2=1; EAT1=2
        EAT2=3; SLEEP1=4; SLEEP2=5
        REFUSE=6; HAPPY=7; ANGRY=8
        SICK1=9; SICK2=10; ATTACK=11
        CELL_NAMES=("idle_1" "idle_2" "eating_1" "eating_2" "sleep_1" "sleep_2"
                    "refusing" "happy" "angry" "sick_1" "sick_2" "attack")
        FALLBACK=(
            "$IDLE2"                       # idle_1
            "$IDLE1"                       # idle_2
            "$EAT2 $IDLE1"                 # eating_1
            "$HAPPY $EAT1 $IDLE2"          # eating_2
            "$SLEEP2 $SICK1 $IDLE1"        # sleep_1
            "$SLEEP1 $SICK2 $IDLE2"        # sleep_2
            "$ANGRY $IDLE1"                # refusing
            "$EAT2 $IDLE2"                 # happy
            "$REFUSE $ATTACK $IDLE1"       # angry
            "$SICK2 $SLEEP1 $IDLE1"        # sick_1
            "$SICK1 $SLEEP2 $IDLE2"        # sick_2
            "$REFUSE $ANGRY $IDLE1"        # attack
        )
        MAP=(
            "$IDLE1"   #  0 idle1
            "$IDLE2"   #  1 idle2
            "$ANGRY"   #  2 angry
            "$SICK1"   #  3 down1
            "$HAPPY"   #  4 happy
            "$EAT1"    #  5 eat1
            "$SLEEP1"  #  6 sleep1
            "$REFUSE"  #  7 refuse
            "$SICK1"   #  8 sad
            "$SICK2"   #  9 down2
            "$EAT2"    # 10 eat2
            "$SLEEP2"  # 11 sleep2
            "$ATTACK"  # 12 attack
        )
        GRID_COLS=3; GRID_ROWS=4
        ;;
esac

OUT1_DIR="$OUTPUT_DIR/$SET_NAME"
OUT2_DIR="$OUTPUT_INPUT_DIR"
mkdir -p "$OUT1_DIR" "$OUT2_DIR"

WORKDIR=$(mktemp -d)
trap 'rm -rf "$WORKDIR"' EXIT

converted=0
skipped=0
failed=0

shopt -s nullglob

# list *.png files of a directory, natural sort (0.png 1.png ... 10.png)
list_pngs() {
    local dir="$1"
    find "$dir" -maxdepth 1 -type f -iname '*.png' -print0 | sort -zV
}

# === Extract cells into $CELL_DIR/cell-NN.png ===
# extract_from_sheet SHEET CELL_DIR
extract_from_sheet() {
    local file="$1" cell_dir="$2" W H fw fh cols rows i c r
    read -r W H < <(magick identify -format "%w %h" "$file[0]" 2>/dev/null)
    if [[ -z "${W:-}" || -z "${H:-}" ]]; then
        echo "ERROR: '$file': failed to read image size"
        return 1
    fi
    if [[ -n "$SRC_FW" ]]; then
        fw=$SRC_FW; fh=$SRC_FH
        cols=$((W / fw)); rows=$((H / fh))
        # penc: the frames are always a 3 col grid (cutin may be wider/narrower)
        [[ "$FORMAT" == "penc" ]] && cols=3
        if (( cols < 1 || cols * rows < NUM_CELLS || fw * cols > W )); then
            echo "WARN: skip '$file': size ${W}x${H} is too small for $NUM_CELLS frames of ${fw}x${fh}"
            return 2
        fi
        if (( ! CUTIN )) && (( W % fw != 0 || H % fh != 0 )); then
            echo "NOTE: '$file': size ${W}x${H} is not a multiple of ${fw}x${fh} (cutin? try --cutin)"
        fi
    else
        cols=$GRID_COLS; rows=$GRID_ROWS
        if (( W % cols != 0 || H % rows != 0 )); then
            echo "WARN: skip '$file': size ${W}x${H} is not divisible into a ${cols}x${rows} grid (try --frame-size)"
            return 2
        fi
        fw=$((W / cols)); fh=$((H / rows))
        if [[ "$FORMAT" == "penc" ]] && (( fw != fh )); then
            echo "NOTE: '$file': non-square frame ${fw}x${fh} (sheet with cutin? try --cutin --frame-size)"
        fi
    fi
    if (( fw > FRAME_SIZE || fh > FRAME_SIZE )); then
        echo "WARN: skip '$file': frame ${fw}x${fh} does not fit into ${FRAME_SIZE}x${FRAME_SIZE}"
        return 2
    fi

    local ARGS=("$file[0]")
    for ((i = 0; i < NUM_CELLS; i++)); do
        c=$((i % cols)); r=$((i / cols))
        ARGS+=( "(" -clone 0 -crop "${fw}x${fh}+$((c * fw))+$((r * fh))" +repage
                -write "PNG32:$cell_dir/cell-$(printf '%02d' "$i").png" +delete ")" )
    done
    ARGS+=( null: )
    magick "${ARGS[@]}" 2>/dev/null || { echo "ERROR: '$file': failed to split frames"; return 1; }
    echo "${fw}x${fh}"
}

# extract_from_frames CELL_DIR FRAME_FILE...
extract_from_frames() {
    local cell_dir="$1"; shift
    local files=("$@") maxw=0 maxh=0 w h i f
    if (( ${#files[@]} < NUM_CELLS )); then
        echo "NOTE: only ${#files[@]} frame files, expected $NUM_CELLS (missing frames use fallbacks)" >&2
    elif (( ${#files[@]} > NUM_CELLS )); then
        echo "NOTE: ${#files[@]} frame files, only the first $NUM_CELLS are used" >&2
        files=("${files[@]:0:NUM_CELLS}")
    fi
    for f in "${files[@]}"; do
        read -r w h < <(magick identify -format "%w %h" "$f[0]" 2>/dev/null)
        if [[ -z "${w:-}" || -z "${h:-}" ]]; then
            echo "ERROR: '$f': failed to read image size" >&2
            return 1
        fi
        (( w > maxw )) && maxw=$w
        (( h > maxh )) && maxh=$h
    done
    if (( maxw > FRAME_SIZE || maxh > FRAME_SIZE )); then
        echo "WARN: frame ${maxw}x${maxh} does not fit into ${FRAME_SIZE}x${FRAME_SIZE}" >&2
        return 2
    fi
    # unify frame size (bottom-center aligned) so the relative position stays consistent
    for i in "${!files[@]}"; do
        magick "${files[$i]}[0]" -background none -gravity south -extent "${maxw}x${maxh}" \
            "PNG32:$cell_dir/cell-$(printf '%02d' "$i").png" 2>/dev/null \
            || { echo "ERROR: '${files[$i]}': failed to read frame" >&2; return 1; }
    done
    echo "${maxw}x${maxh}"
}

# === Build outputs from $CELL_DIR ===
# build NAME CELL_DIR FRAME_INFO
build() {
    local name="$1" cell_dir="$2" info="$3" i c f
    local out1="$OUT1_DIR/$name.png" out2="$OUT2_DIR/$name.png"

    # detect blank/missing cells
    local FILLED=()
    for ((c = 0; c < NUM_CELLS; c++)); do
        f="$cell_dir/cell-$(printf '%02d' "$c").png"
        if [[ -f "$f" ]] && [[ "$(magick "$f" -alpha extract -format '%[fx:maxima>0?1:0]' info: 2>/dev/null)" == "1" ]]; then
            FILLED[c]=1
        else
            FILLED[c]=0
        fi
    done

    # resolve each source cell to a non-blank cell
    local RESOLVED=()
    for ((c = 0; c < NUM_CELLS; c++)); do
        if (( FILLED[c] )); then RESOLVED[c]=$c; continue; fi
        RESOLVED[c]=-1
        for f in ${FALLBACK[$c]}; do
            if (( FILLED[f] )); then RESOLVED[c]=$f; break; fi
        done
        if (( RESOLVED[c] < 0 )); then
            for ((f = 0; f < NUM_CELLS; f++)); do
                if (( FILLED[f] )); then RESOLVED[c]=$f; break; fi
            done
        fi
    done
    if (( RESOLVED[0] < 0 )); then
        echo "WARN: skip '$name': all frames are blank"
        skipped=$((skipped + 1))
        return
    fi
    for i in "${!MAP[@]}"; do
        c=${MAP[$i]}
        if (( RESOLVED[c] != c )); then
            echo "NOTE: '$name': '${CELL_NAMES[$c]}' is blank, using '${CELL_NAMES[${RESOLVED[$c]}]}' (frame $i ${OUT_NAMES[$i]})"
        fi
    done

    # 128x128 frames, cell centered
    local sheet_w=$((FRAME_SIZE * ${#MAP[@]})) cw ch
    local ARGS=(-size "${sheet_w}x${FRAME_SIZE}" xc:none)
    for i in "${!MAP[@]}"; do
        f="$cell_dir/cell-$(printf '%02d' "${RESOLVED[${MAP[$i]}]}").png"
        read -r cw ch < <(magick identify -format "%w %h" "$f")
        ARGS+=( "$f" -geometry "+$((i * FRAME_SIZE + (FRAME_SIZE - cw) / 2))+$(((FRAME_SIZE - ch) / 2))" -composite )
    done
    if ! magick "${ARGS[@]}" "PNG32:$out2"; then
        echo "ERROR: '$name': failed to write '$out2'"
        failed=$((failed + 1))
        return
    fi

    # cropped
    if ! bash "$CROP_SCRIPT" "$out2" "$out1" --frame-size "$FRAME_SIZE" --padding "$CROP_PADDING" >/dev/null 2>&1; then
        echo "ERROR: '$name': failed to crop '$out2' -> '$out1'"
        failed=$((failed + 1))
        return
    fi
    echo "Converted: $name (frame $info) -> $out2, $out1"
    converted=$((converted + 1))
}

# returns 0 if outputs may be written
check_outputs() {
    local name="$1"
    if (( ! FORCE )) && [[ -e "$OUT1_DIR/$name.png" || -e "$OUT2_DIR/$name.png" ]]; then
        echo "WARN: skip '$name': already exists in $OUT1_DIR or $OUT2_DIR (use --force to overwrite)"
        skipped=$((skipped + 1))
        return 1
    fi
    return 0
}

new_cell_dir() {
    local d
    d=$(mktemp -d "$WORKDIR/cells.XXXXXX")
    echo "$d"
}

# process_sheet FILE
process_sheet() {
    local file="$1" name cell_dir info rc
    name=$(basename "$file"); name="${name%.*}"
    check_outputs "$name" || return
    cell_dir=$(new_cell_dir)
    info=$(extract_from_sheet "$file" "$cell_dir"); rc=$?
    if (( rc != 0 )); then
        echo "$info"
        (( rc == 2 )) && skipped=$((skipped + 1)) || failed=$((failed + 1))
        return
    fi
    # forward NOTE lines, last line is the frame size
    [[ "$info" == *$'\n'* ]] && echo "${info%$'\n'*}"
    build "$name" "$cell_dir" "${info##*$'\n'}"
}

# process_frames NAME FRAME_FILE...
process_frames() {
    local name="$1"; shift
    local cell_dir info rc
    check_outputs "$name" || return
    cell_dir=$(new_cell_dir)
    info=$(extract_from_frames "$cell_dir" "$@" 2> >(sed "s|^|'$name': |" >&2)); rc=$?
    if (( rc != 0 )); then
        (( rc == 2 )) && skipped=$((skipped + 1)) || failed=$((failed + 1))
        return
    fi
    build "$name" "$cell_dir" "$info"
}

# process_frame_dir DIR
process_frame_dir() {
    local dir="${1%/}" frames=()
    mapfile -d '' frames < <(list_pngs "$dir")
    if (( ${#frames[@]} == 0 )); then
        echo "WARN: skip '$dir': no .png files found"
        skipped=$((skipped + 1))
        return
    fi
    process_frames "$(basename "$(realpath "$dir")")" "${frames[@]}"
}

# === Dispatch inputs ===
if (( ${#INPUTS[@]} == 1 )); then
    INPUT="${INPUTS[0]}"
    if [[ -f "$INPUT" ]]; then
        process_sheet "$INPUT"
    elif [[ -d "$INPUT" ]]; then
        if (( RECURSIVE )); then
            found=0
            mapfile -d '' SHEETS < <(list_pngs "$INPUT")
            for f in "${SHEETS[@]}"; do process_sheet "$f"; found=1; done
            mapfile -d '' SUBDIRS < <(find "$INPUT" -mindepth 1 -maxdepth 1 -type d -print0 | sort -zV)
            for d in "${SUBDIRS[@]}"; do
                if [[ -n "$(find "$d" -maxdepth 1 -type f -iname '*.png' -print -quit)" ]]; then
                    process_frame_dir "$d"; found=1
                fi
            done
            (( found )) || { echo "ERROR: '$INPUT': no sprite sheets or frame directories found"; exit 1; }
        else
            if [[ -z "$(find "$INPUT" -maxdepth 1 -type f -iname '*.png' -print -quit)" ]]; then
                echo "ERROR: '$INPUT': no .png frame files found (directory of sets? try -r)"
                exit 1
            fi
            process_frame_dir "$INPUT"
        fi
    else
        echo "ERROR: input not found: $INPUT"
        exit 1
    fi
else
    # list of frame files (natural sort), name = parent directory
    for f in "${INPUTS[@]}"; do
        [[ -f "$f" ]] || { echo "ERROR: frame file not found: $f"; exit 1; }
    done
    mapfile -d '' FRAMES < <(printf '%s\0' "${INPUTS[@]}" | sort -zV)
    process_frames "$(basename "$(realpath "$(dirname "${FRAMES[0]}")")")" "${FRAMES[@]}"
fi

echo "Done: converted=$converted skipped=$skipped failed=$failed"
[[ $failed -eq 0 ]]
