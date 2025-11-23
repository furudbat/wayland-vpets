#!/usr/bin/env bash

set -euo pipefail

# Usage:
# ./build-sheets.sh <input_root> <output_root>
#
# Example:
# ./build-sheets.sh assets/input/pmd/sprite assets/input/pmd-fixed
#
# Dependencies: ImageMagick (convert, identify), xmllint (preferred)

# git clone https://github.com/PMDCollab/SpriteCollab assets/input/pmd

INPUT_ROOT="${1:-assets/input/pmd/sprite}"
OUTPUT_ROOT="${2:-assets/input/pmd-fixed}"
OUTPUT_ROOT_JSON="${3:-assets/input}"
mkdir -p "$OUTPUT_ROOT"

META_JSON="${OUTPUT_ROOT_JSON}/pmd-sprite-meta.json"
declare -A META
echo "{}" > "$META_JSON"

# Temporary working dir
TMPROOT="$(mktemp -d)"
trap 'rm -rf "$TMPROOT"' EXIT

# Helper: xml querying using xmllint if available, otherwise fallback
XML_QUERY() {
  local xmlfile="$1"; shift
  local xpath="$*"
  if command -v xmllint >/dev/null 2>&1; then
    xmllint --xpath "$xpath" "$xmlfile" 2>/dev/null || true
  else
    # VERY small fallback: try to find simple tags using grep/sed (not robust)
    # Supports: FrameWidth, FrameHeight and counting <Duration> lines inside Anim with <Name>text</Name>
    if [[ "$xpath" == *"count("* ]]; then
      # Expecting pattern like count(//Anim[Name='X']/Durations/Duration)
      local name=$(echo "$xpath" | sed -n "s/.*Name=['\"]\([^'\"]*\)['\"].*/\1/p")
      if [[ -n "$name" ]]; then
        grep -Poz "(?s)<Anim>.*?<Name>${name}</Name>.*?<Durations>.*?</Durations>.*?</Anim>" "$xmlfile" \
          | grep -c "<Duration" || echo 0
      else
        echo 0
      fi
    else
      # fetch string(//Anim[Name='X']/FrameWidth) etc
      local name=$(echo "$xpath" | sed -n "s/.*Anim\[Name=['\"]\([^'\"]*\)['\"].*/\1/p")
      if [[ "$xpath" == *"FrameWidth"* ]]; then
        grep -Poz "(?s)<Anim>.*?<Name>${name}</Name>.*?<FrameWidth>[0-9]+</FrameWidth>.*?</Anim>" "$xmlfile" \
          | sed -n "s/.*<FrameWidth>\([0-9]*\)<\/FrameWidth>.*/\1/p"
      elif [[ "$xpath" == *"FrameHeight"* ]]; then
        grep -Poz "(?s)<Anim>.*?<Name>${name}</Name>.*?<FrameHeight>[0-9]+</FrameHeight>.*?</Anim>" "$xmlfile" \
          | sed -n "s/.*<FrameHeight>\([0-9]*\)<\/FrameHeight>.*/\1/p"
      else
        echo ""
      fi
    fi
  fi
}

# Normalize string trim
trim() { printf "%s" "$1" | sed -e 's/^[[:space:]]*//;s/[[:space:]]*$//' ; }

# Candidate lookup: try multiple animation names (case-insensitive)
find_anim_png() {
  local dir="$1"; shift
  local -a candidates=( "$@" )
  shopt -s nullglob nocaseglob
  for c in "${candidates[@]}"; do
    # common pattern in your repo: "<Name>-Anim.png" or "<Name> -Anim.png" or "<Name>Anim.png"
    for patt in "${c}-Anim.png" "${c}*-Anim.png" "*${c}*-Anim.png" "${c}Anim.png" "*${c}Anim.png"; do
      for f in "$dir"/$patt; do
        [[ -f "$f" ]] && { echo "$f"; shopt -u nullglob nocaseglob; return 0; }
      done
    done
  done
  shopt -u nullglob nocaseglob
  return 1
}

# The list of rows to produce and their requested sources (order matters).
# Each entry: label | candidate-names (comma separated) | row-number (1-indexed)
# This follows your list 3.1..3.9
declare -a ROW_LABELS=(
  "Idle" "Boring" "Writing" "Happy" "WakeUp" "Sleep" "Working" "Moving" "Running"
)
declare -a ROW_CANDIDATES=(
  "Idle"                                              # 1 Idle row 8 -> Idle
  "Pose,Dance,Hop,Float,LostBalance,LookUp,Cringe"    # 2 Pose or Dance or Hop -> Boring
  "Swing,Rotate,Idle"                                 # 3 Idle row 8 -> Writing (you duplicated Idle)
  "Nod,Shock,EventSleep"                              # 4 Nod row 8 -> Happy
  "Wake"                                              # 5 Wake row 8 -> WakeUp
  "Sleep,Laying"                                      # 6 Sleep row 1 -> Sleep
  "Shot,Shoot,Attack,Shoot,Strike"                    # 7 Shot or Attack -> Working
  "Walk,TumbleBack"                                   # 8 Walk row 7 -> Moving
  "Charge,Hop"                                        # 9 Charge row 7 -> Running
)
declare -a DEFAULT_ROW_NUMBERS=(8 8 8 8 8 1 8 7 7)  # requested row numbers (1-indexed)


# -------------------------
# Process each sprite folder
# -------------------------
for folder in "$INPUT_ROOT"/000*/; do
  basename="$(basename "$folder")"
  [[ "$basename" =~ ^[0-9]+$ ]] || continue
  echo ">>> Processing $basename ..."

  anim_xml="$folder/AnimData.xml"
  [[ -f "$anim_xml" ]] || { echo "   - no AnimData.xml, skipping."; continue; }

  tmpdir="$TMPROOT/$basename"
  mkdir -p "$tmpdir/frames"

  declare -a ROW_FRAMEW=() ROW_FRAMEH=() ROW_COLS=() ROW_PNG=()
  declare -A META_ROW_FRAMES=()

  # First pass: gather frame info
  max_fw=0; max_fh=0; max_cols=0
  for i in "${!ROW_LABELS[@]}"; do
    label="${ROW_LABELS[$i]}"
    candidates="${ROW_CANDIDATES[$i]}"
    IFS=',' read -r -a candarr <<< "$candidates"
    found_png=""; found_name=""

    for cand in "${candarr[@]}"; do
      cand_trim="$(trim "$cand")"
      if f="$(find_anim_png "$folder" "$cand_trim" "${cand_trim^}" "${cand_trim,,}" "${cand_trim^^}")"; then
        found_png="$f"
        found_name="$cand_trim"
        break
      fi
    done
    [[ -z "$found_png" ]] && found_name="${candarr[0]}"

    # Frames count from XML fallback
    count_xpath="count(//Anim[Name='${found_name}']/Durations/Duration)"
    cols="$(XML_QUERY "$anim_xml" "number($count_xpath)")"
    cols="${cols:-0}"

    # Frame width/height
    fw="$(XML_QUERY "$anim_xml" "string(//Anim[Name='${found_name}']/FrameWidth)")"
    fh="$(XML_QUERY "$anim_xml" "string(//Anim[Name='${found_name}']/FrameHeight)")"

    # Fallback using identify
    if [[ -z "$fw" || -z "$fh" ]] && [[ -n "$found_png" ]]; then
      geom="$(identify -format "%wx%h" "$found_png" 2>/dev/null || true)"
      fw="${geom%x*}"; fh="${geom#*x}"
    fi

    fw=$((fw+0)); fh=$((fh+0)); cols=$((cols+0))
    ROW_FRAMEW[$i]=$fw; ROW_FRAMEH[$i]=$fh; ROW_COLS[$i]=$cols; ROW_PNG[$i]="$found_png"

    (( fw > max_fw )) && max_fw=$fw
    (( fh > max_fh )) && max_fh=$fh
    (( cols > max_cols )) && max_cols=$cols

    [[ "$cols" -gt 0 ]] && META_ROW_FRAMES["frames_${label,,}"]=$cols
  done

  META_ROW_FRAMES["rows"]="${#ROW_LABELS[@]}"
  META["$basename"]=$(printf '%s\n' "$(declare -p META_ROW_FRAMES)")

  # --- Second Pass: crop, trim, pad frames ---
  declare -A ROW_MAX_W=() ROW_MAX_H=()
  for i in "${!ROW_LABELS[@]}"; do
    label="${ROW_LABELS[$i]}"
    png="${ROW_PNG[$i]}"
    fw="${ROW_FRAMEW[$i]}"
    fh="${ROW_FRAMEH[$i]}"
    cols="${ROW_COLS[$i]}"
    rownum="${ROW_NUMBERS[$i]}"
    outrowdir="$tmpdir/frames/$i"
    mkdir -p "$outrowdir"
    [[ -z "$png" || ! -f "$png" || "$fw" -le 0 || "$fh" -le 0 || "$cols" -le 0 ]] && continue

    yoff=$(( (rownum - 1) * fh ))
    for ((c=0;c<cols;c++)); do
      xoff=$((c * fw))
      dst="$outrowdir/frame_$(printf "%03d" $c).png"
      magick "$png" -crop "${fw}x${fh}+${xoff}+${yoff}" +repage PNG32:"$dst"
      magick "$dst" -trim +repage -background none -gravity center -extent "${fw}x${fh}" "$dst"
    done

    # --- Append frames horizontally per row ---
    row_images=()
    for i in "${!ROW_LABELS[@]}"; do
      [[ ${ROW_COLS[$i]} -eq 0 ]] && continue
      outrowdir="$tmpdir/frames/$i"
      mapfile -t frames_sorted < <(find "$outrowdir" -maxdepth 1 -type f -name 'frame_*.png' | sort)
      [[ ${#frames_sorted[@]} -eq 0 ]] && continue
      magick "${frames_sorted[@]}" +append "$tmpdir/row_${i}.png"
      row_images+=("$tmpdir/row_${i}.png")
      # save frames count for meta
      row_label="${ROW_LABELS[$i],,}"   # lowercase
      META["$basename:frames_$row_label"]=${#frames_sorted[@]}
    done

    # --- Append rows vertically to sprite sheet ---
    out_name="$basename.png"
    out_path="$OUTPUT_ROOT/$out_name"
    magick "${row_images[@]}" -background none -append -gravity center -trim +repage -bordercolor none -border 2 "$out_path"

    META["$basename:rows"]=${#row_images[@]}
    echo "   => written $out_path"
  done

  # Build rows
  row_images=()
  for i in "${!ROW_LABELS[@]}"; do
    [[ ${ROW_COLS[$i]} -eq 0 ]] && continue
    outrowdir="$tmpdir/frames/$i"
    mapfile -t frames_sorted < <(find "$outrowdir" -maxdepth 1 -type f -name 'frame_*.png' | sort)
    [[ ${#frames_sorted[@]} -eq 0 ]] && continue
    magick "${frames_sorted[@]}" +append "$tmpdir/row_${i}.png"
    row_images+=("$tmpdir/row_${i}.png")
  done

  # Combine rows vertically
  out_name="$basename.png"
  magick "${row_images[@]}" -background none -append -gravity center -trim +repage -bordercolor none -border 4 "$OUTPUT_ROOT/$out_name"
  echo "   => written $OUTPUT_ROOT/$out_name"

done

# Write JSON meta
{
  echo "{"
  first=1
  for k in "${!META[@]}"; do
    [[ $first -eq 1 ]] || echo ","
    first=0
    # Convert declare output back to JSON
    eval "${META[$k]}"
    echo -n "  \"$k\": {"
    sep=""; for key in "${!META_ROW_FRAMES[@]}"; do
      echo -n "$sep\"$key\": ${META_ROW_FRAMES[$key]}"
      sep=","
    done
    echo -n "}"
  done
  echo ""
  echo "}"
} > "$META_JSON"

echo "All done. Outputs are in: $OUTPUT_ROOT"
echo "Meta JSON saved to: $META_JSON"
