#!/usr/bin/env bash
set -euo pipefail

# -----------------------------
# build-pmd-sheets.sh
# -----------------------------
# Dependencies: ImageMagick (magick), xmllint
# -----------------------------

INPUT_ROOT="${1:-assets/input/pmd/sprite}"
OUTPUT_ROOT="${2:-assets/input/pmd-new}"
OUTPUT_ROOT_FINAL="${2:-assets/input/pmd-fixed}"
JSON_ROOT="${3:-assets/input}"

mkdir -p "$OUTPUT_ROOT"
mkdir -p "$OUTPUT_ROOT_FINAL"
mkdir -p "$JSON_ROOT"

CACHE_FILE="${JSON_ROOT}/pkmn_cache.json"
[[ ! -f "$CACHE_FILE" ]] && echo "{}" > "$CACHE_FILE"


META_JSON="${JSON_ROOT}/pmd-sprite-meta.json"
echo "{}" > "$META_JSON"
declare -A META

TMPROOT="$(mktemp -d)"
trap 'rm -rf "$TMPROOT"' EXIT

# -----------------------------
# Helpers
# -----------------------------

trim() { printf "%s" "$1" | sed -e 's/^[[:space:]]*//;s/[[:space:]]*$//'; }

XML_QUERY() {
    local xmlfile="$1"; shift
    local xpath="$*"
    xmllint --xpath "$xpath" "$xmlfile" 2>/dev/null || echo ""
}

find_anim_png() {
    local dir="$1"; shift
    local -a candidates=( "$@" )
    shopt -s nullglob nocaseglob
    for c in "${candidates[@]}"; do
        for patt in "${c}-Anim.png" "${c}*-Anim.png" "*${c}*-Anim.png" "${c}Anim.png" "*${c}Anim.png"; do
            files=( "$dir"/$patt )
            if [[ ${#files[@]} -gt 0 ]]; then
                shopt -u nullglob nocaseglob
                echo "${files[0]}"
                return 0
            fi
        done
    done
    shopt -u nullglob nocaseglob
    return 1
}

get_pokemon_name() {
    local id=$1

    # normalize: strip leading zeros (0001 → 1)
    id=$((10#$id))

    # read from cache
    local cached
    cached=$(jq -r --arg id "$id" '.[$id] // empty' "$CACHE_FILE")
    if [[ -n "$cached" && "$cached" != "null" ]]; then
        echo "$cached"
        return 0
    fi

    # fetch from API
    local api_json name
    api_json=$(curl -s "https://pokeapi.co/api/v2/pokemon/${id}")
    name=$(echo "$api_json" | jq -r '.name // empty')
    if [[ -z "$name" ]]; then
        echo "ERROR: could not retrieve Pokémon name for ID $id" >&2
        name="unknown"
    fi

    # update cache
    tmp=$(mktemp)
    jq --arg id "$id" --arg name "$name" '. + {($id): $name}' "$CACHE_FILE" > "$tmp"
    mv "$tmp" "$CACHE_FILE"

    echo "$name"
    return 0
}

pick_row_from_png() {
    local png="$1"
    local is_moving="$2"   # "1" if moving, "0" otherwise

    # Count rows: ImageMagick identify gets height
    local w h
    read w h <<< "$(magick identify -format "%w %h" "$png")"

    # Frame height assumed correct
    local frame_h="$3"

    local rows=$(( h / frame_h ))

    if (( rows >= 8 )); then
        if [[ "$is_moving" == "1" ]]; then
            echo 7
        else
            echo 8
        fi
    else
        echo 1
    fi
}


# -----------------------------
# Row definitions
# -----------------------------
ROW_LABELS=( "Idle" "Boring" "Writing" "Happy" "Sleep" "Working" "Moving" )
ROW_CANDIDATES=(
    "Idle,Hover,Walk"
    "Pose,DeepBreath,Appeal,Dance,Twirl,TailWhip"
    "Uppercut,Punch,Slap,Scratch,Slice,Chop,Strike,Ricochet,Jab,Bite,Kick,Lick,Slam,Stomp,Attack,Idle"
    "Hop,Withdraw,Nod"
    "Sleep,EventSleep,Laying"
    "MultiScratch,MultiStrike,Shock,Emit,Shake,Sing,Sound,Gas,Withdraw,RearUp,Rumble,Swell,SpAttack,Shot,Shoot,Charge,Attack"
    "Walk,Hover"
)

# -----------------------------
# Process each sprite folder
# -----------------------------
GLOBAL_W=0
GLOBAL_H=0
FIXED_FRAME_SIZE=64
FRAME_SIZE=0
PADDING=4
for folder in "$INPUT_ROOT"/*/; do
    base="$(basename "$folder")"
    [[ "$base" =~ ^[0-9]+$ ]] || continue
    echo ">>> Processing $base ..."
    poke_id="${base}"
    poke_name=$(get_pokemon_name "$poke_id")
    new_base="${poke_id}_${poke_name}"

    anim_xml="$folder/AnimData.xml"
    [[ -f "$anim_xml" ]] || { echo "   - no AnimData.xml, skipping."; continue; }

    tmpdir="$TMPROOT/$base"
    mkdir -p "$tmpdir/frames"

    declare -a ROW_FRAMEW=() ROW_FRAMEH=() ROW_COLS=() ROW_PNG=()
    max_fw=0; max_fh=0

    # --- Gather frame info from XML ---
    for i in "${!ROW_LABELS[@]}"; do
        label="${ROW_LABELS[$i]}"
        IFS=',' read -r -a candidates <<< "${ROW_CANDIDATES[$i]}"
        found_name=""
        for c in "${candidates[@]}"; do
            c_trim=$(trim "$c")
            count=$(XML_QUERY "$anim_xml" "count(//Anim[Name='$c_trim']/Durations/Duration)")
            if [[ $count -gt 0 ]]; then
                found_name="$c_trim"
                break
            fi
        done
        [[ -z "$found_name" ]] && continue

        fw=$(XML_QUERY "$anim_xml" "string(//Anim[Name='$found_name']/FrameWidth)")
        fh=$(XML_QUERY "$anim_xml" "string(//Anim[Name='$found_name']/FrameHeight)")
        frames_count=$(XML_QUERY "$anim_xml" "count(//Anim[Name='$found_name']/Durations/Duration)")

        ROW_FRAMEW[$i]=$fw
        ROW_FRAMEH[$i]=$fh
        ROW_COLS[$i]=$frames_count

        (( fw > max_fw )) && max_fw=$fw
        (( fh > max_fh )) && max_fh=$fh

        (( fw > GLOBAL_W )) && GLOBAL_W=$fw
        (( fh > GLOBAL_H )) && GLOBAL_H=$fh

        (( fw > FRAME_SIZE )) && FRAME_SIZE=$fw
        (( fh > FRAME_SIZE )) && FRAME_SIZE=$fh

        # Find PNG
        ROW_PNG[$i]=$(find_anim_png "$folder" "$found_name")
        if [[ -z "${ROW_PNG[$i]}" ]]; then
            echo "   - skipping $label: PNG not found"
        else
            echo "   Found PNG for $label: ${ROW_PNG[$i]}"
        fi
    done

    # -----------------------------
    # Split, trim, align, and pad frames
    # -----------------------------
    row_images=()
    max_cols=0
    rows=0

    for i in "${!ROW_LABELS[@]}"; do
        png="${ROW_PNG[$i]:-}"  # default empty string
        [[ -z "$png" ]] && continue
        outdir="$tmpdir/frames/$i"
        mkdir -p "$outdir"
        fw="${ROW_FRAMEW[$i]}"
        fh="${ROW_FRAMEH[$i]}"
        cols="${ROW_COLS[$i]}"
        [[ $cols -le 0 ]] && continue

        # Determine if this animation is "Moving"
        is_moving=0
        [[ "${ROW_LABELS[$i]}" == "Moving" || "${ROW_LABELS[$i]}" == "Running" ]] && is_moving=1

        # Determine which row from the PNG to use
        row_number=$(pick_row_from_png "$png" "$is_moving" "$fh")
        row_y=$(( (row_number - 1) * fh ))

        echo "   -> Using row $row_number from ${ROW_LABELS[$i]}"

        # Split frames horizontally BUT from chosen row
        for ((c=0;c<cols;c++)); do
            xoff=$((c * fw))
            dst="$outdir/frame_$(printf "%03d" $c).png"
            magick "$png" -crop "${fw}x${fh}+${xoff}+${row_y}" +repage PNG32:"$dst"
        done

        frames_sorted=("$outdir"/frame_*.png)
        [[ ${#frames_sorted[@]} -eq 0 ]] && continue

        # --- Compute minimal top offset across all frames ---
        MIN_TOP=$((max_fh))
        for f in "${frames_sorted[@]}"; do
            magick "$f" -trim +repage "$f"
            TOP=$(magick identify -format "%[fx:page.y]" "$f")
            (( TOP < MIN_TOP )) && MIN_TOP=$TOP
        done

        # --- Pad each frame consistently ---
        PAD_LEFT=$((PADDING))
        PAD_RIGHT=$((PADDING))
        PAD_TOP=$((PADDING))
        PAD_BOTTOM=$((PADDING))

        new_fw=0
        new_fh=0
        for f in "${frames_sorted[@]}"; do
            PADDED="$outdir/padded_$(basename "$f")"
            magick "$f" \
                -background none \
                -gravity south \
                -extent "${FIXED_FRAME_SIZE}x${FIXED_FRAME_SIZE}" \
                -splice "0x${PAD_BOTTOM}" \
                "$PADDED" || echo "Warning: Failed to generate $PADDED"
            (( max_fw > new_fw )) && new_fw=$max_fw
            (( (max_fh - MIN_TOP) > new_fh )) && new_fh=(max_fh - MIN_TOP)
        done

        # Horizontal append of padded frames
        PADDED_FRAMES=("$outdir"/padded_frame_*.png)
        if [[ ${#PADDED_FRAMES[@]} -gt 0 ]]; then
            magick "${PADDED_FRAMES[@]}" +append "$tmpdir/row_${i}.png"
            row_images+=("$tmpdir/row_${i}.png")
            META["$base:frames_${ROW_LABELS[$i],,}"]=$cols
            META["$new_base:frames_${ROW_LABELS[$i],,}"]=$cols
            (( cols > max_cols )) && max_cols=$cols
        fi
    done

    # --- Vertical append all rows ---
    if [[ ${#row_images[@]} -gt 0 ]]; then
        out_name="$base.png"
        magick "${row_images[@]}" -background none -append -gravity center "$OUTPUT_ROOT/$out_name"
        META["$base:rows"]=${#row_images[@]}
        META["$new_base:rows"]=${#row_images[@]}
        META["$base:cols"]=${max_cols}
        META["$new_base:cols"]=${max_cols}
        echo "   => Cols: ${max_cols} Rows: ${#row_images[@]}"
        echo "   => written $OUTPUT_ROOT_FINAL/$out_name"

        new_file_name="${poke_id}_${poke_name}.png"
        cp "$OUTPUT_ROOT/$out_name" "$OUTPUT_ROOT_FINAL/$new_file_name"
        # trim every frame in sprite sheet at minimum and keep the same frame size with south direction and bottom padding
        #./scripts/crop_spritesheet.sh "$OUTPUT_ROOT/$out_name" "$OUTPUT_ROOT_FINAL/$new_file_name" --frame-size "${FIXED_FRAME_SIZE}" --padding "$PADDING"
        echo "   => renamed to $new_file_name"
    else
        echo "   - no rows to assemble for $base"
    fi
done

# -----------------------------
# Write JSON metadata
# -----------------------------
{
    echo "{"
    first_entry=1

    for file in "$OUTPUT_ROOT_FINAL"/*.png; do

        basefile="$(basename "$file" .png)"
        poke_id="$(echo "$basefile" | cut -d'_' -f1)"

        [[ "$poke_id" =~ ^[0-9]+$ ]] || continue

        # Build a list of keys we want to output:
        #   1. numeric ID (0001)
        #   2. alias with name (0001_bulbasaur)
        output_keys=( "$poke_id" "$basefile" )

        for outkey in "${output_keys[@]}"; do

            # Collect metadata for this key
            declare -A merged=()

            for key in "${!META[@]}"; do
                case "$key" in
                    "$poke_id:"* )
                        sub="${key#*:}"
                        merged["$sub"]="${META[$key]}"
                        ;;
                    "$basefile:"* )
                        sub="${key#*:}"
                        merged["$sub"]="${META[$key]}"
                        ;;
                esac
            done

            # Skip empty
            [[ ${#merged[@]} -eq 0 ]] && continue

            # JSON formatting
            [[ $first_entry -eq 1 ]] || echo ","
            first_entry=0

            echo "  \"$outkey\": {"

            first_sub=1
            for subkey in "${!merged[@]}"; do
                [[ $first_sub -eq 1 ]] || echo ","
                first_sub=0
                echo -n "    \"$subkey\": ${merged[$subkey]}"
            done

            echo ""
            echo -n "  }"

        done
    done

    echo ""
    echo "}"
} > "$META_JSON"



echo "All done. Outputs: $OUTPUT_ROOT"
echo "Metadata JSON: $META_JSON"