#!/bin/bash

# === Usage Check ===
if [[ $# -lt 3 ]]; then
    echo "Usage: $0 <input-dir> <og-input-dir> <output-source>"
    echo "Example: $0 assets/dm assets/input/dm src/embedded_assets/dm/dm_get_evolution_data.cpp"
    exit 1
fi

# === Arguments ===
INPUT_DIR="$1"
OG_INPUT_DIR="$2"
CPP_SOURCE_GET_EVOL_OUT="$3"
START_INDEX="$4"

FRAME_SIZE=""
COLS=""
ROWS=""
LAYOUT="Dm"
SET=""

# === Parse args ===
POSITIONAL_ARGS=()
while [[ $# -gt 0 ]]; do
    case $1 in
        --frame-size) FRAME_SIZE="$2"; shift 2 ;;
        --cols) COLS="$2"; shift 2 ;;
        --rows) ROWS="$2"; shift 2 ;;
        --set) SET="$2"; shift 2 ;;
        --layout) LAYOUT="$2"; shift 2 ;;
        -*|--*)
            echo "Unknown option $1"; exit 1 ;;
        *) POSITIONAL_ARGS+=("$1"); shift ;;
    esac
done
set -- "${POSITIONAL_ARGS[@]}"

INPUT_DIR="${POSITIONAL_ARGS[0]}"
OG_INPUT_DIR="${POSITIONAL_ARGS[1]}"
CPP_SOURCE_GET_EVOL_OUT="${POSITIONAL_ARGS[2]}"
START_INDEX="${POSITIONAL_ARGS[3]:-0}"

# === Dependency check ===
if ! command -v magick &>/dev/null; then
    echo "ImageMagick v7+ (magick command) is required."
    exit 1
fi

#echo $INPUT_DIR
#echo $OG_INPUT_DIR
#echo $CPP_SOURCE_GET_EVOL_OUT
#exit 1

if [[ -z "$INPUT_DIR" || -z "$OG_INPUT_DIR" || -z "$CPP_SOURCE_GET_EVOL_OUT" ]]; then
    echo "Usage: $0 <input-dir> <og-input-dir> <output-header> <output-source>"
    exit 1
fi

# === Derived prefix from directory (after 'assets/') ===
ASSETS_PREFIX=${INPUT_DIR#assets/}
ASSETS_PREFIX_CLEAN=$(echo "$ASSETS_PREFIX" | sed "s/['().:]//g")
ASSETS_PREFIX_CLEAN=$(echo "$ASSETS_PREFIX_CLEAN" | sed "s/.png$//g")
ASSETS_PREFIX_CLEAN=$(echo "$ASSETS_PREFIX_CLEAN" | sed 's/[^a-zA-Z0-9]/_/g')
ASSETS_PREFIX_CLEAN=$(echo "$ASSETS_PREFIX_CLEAN" | sed 's/_\+/_/g')
ASSETS_PREFIX_LOWER=$(echo "$ASSETS_PREFIX_CLEAN" | tr '[:upper:]' '[:lower:]')
ASSETS_PREFIX_UPPER=$(echo "$ASSETS_PREFIX_CLEAN" | tr '[:lower:]' '[:upper:]')

# Clean output files at the start
> "$CPP_SOURCE_GET_EVOL_OUT"

GET_EVOL_DATA_FUNC_NAME="get_${ASSETS_PREFIX_LOWER}_evolution_data"

echo "#include \"embedded_assets/embedded_image.h\"" >> "$CPP_SOURCE_GET_EVOL_OUT"
echo "#include \"embedded_assets/${ASSETS_PREFIX_LOWER}/${ASSETS_PREFIX_LOWER}.hpp\"" >> "$CPP_SOURCE_GET_EVOL_OUT"
echo "#include \"embedded_assets/${ASSETS_PREFIX_LOWER}/${ASSETS_PREFIX_LOWER}_evol.h\"" >> "$CPP_SOURCE_GET_EVOL_OUT"
echo "#include \"graphics/animation_shared_memory.h\"" >> "$CPP_SOURCE_GET_EVOL_OUT"
echo >> "$CPP_SOURCE_GET_EVOL_OUT"
echo "namespace bongocat::assets {" >> "$CPP_SOURCE_GET_EVOL_OUT"
echo "    animation::animation_evolution_data_t ${GET_EVOL_DATA_FUNC_NAME}(size_t index) {" >> "$CPP_SOURCE_GET_EVOL_OUT"
echo "        switch (index) {" >> "$CPP_SOURCE_GET_EVOL_OUT"


# === Start animation index counter ===
INDEX=$START_INDEX

# Build Evol Map
declare -A NEXT_INDEX_MAP
for FILE in "$INPUT_DIR"/*.png; do
    BASENAME=$(basename "$FILE")

    NAME_NO_EXT="${BASENAME%.png}"
    NAME_NO_EXT="${NAME_NO_EXT#[0-9]*_}"
    NAME_NO_EXT="${NAME_NO_EXT^}"
    NAME_CLEAN=$(echo "$NAME_NO_EXT" | sed "s/['().:]//g")
    NAME_CLEAN=$(echo "$NAME_CLEAN" | sed 's/[^a-zA-Z0-9]/_/g')
    NAME_CLEAN=$(echo "$NAME_CLEAN" | sed 's/_\+/_/g')
    IDENTIFIER=$(echo "$NAME_CLEAN" | tr '[:upper:]' '[:lower:]')
    MACRO_PREFIX=$(echo "${ASSETS_PREFIX_UPPER}_${IDENTIFIER}" | tr '[:lower:]' '[:upper:]')

    RELATIVE_PATH="../../../$INPUT_DIR/$BASENAME"

    FQID="${ASSETS_PREFIX_LOWER}:${IDENTIFIER}"
    FQNAME="${ASSETS_PREFIX_LOWER}:${NAME_NO_EXT}"

    DIGIMON_NAME=$NAME_NO_EXT
    NEXT_INDEX_MAP["$DIGIMON_NAME"]=${MACRO_PREFIX}_ANIM_INDEX

    ((INDEX++))
done

# === Start animation index counter ===
INDEX=$START_INDEX

# === Process all PNGs ===
for FILE in "$INPUT_DIR"/*.png; do
    BASENAME=$(basename "$FILE")

    # Handle optional frame size or COLS/ROWS
    if [[ -n "$FRAME_SIZE" ]]; then
        OG_FILE="$OG_INPUT_DIR/$BASENAME"
        if [ -f "$OG_FILE" ]; then
          SHEET_WIDTH=$(magick identify -format "%w" "$OG_FILE")
          SHEET_HEIGHT=$(magick identify -format "%h" "$OG_FILE")

          # Compute cols/rows based on fixed frame size
          if [[ -n "$FRAME_SIZE" ]]; then
              COLS=$(( SHEET_WIDTH / FRAME_SIZE ))
              ROWS=$(( SHEET_HEIGHT / FRAME_SIZE ))
          else
              # fallback if frame size not specified
              COLS=1
              ROWS=$(( SHEET_HEIGHT / SHEET_WIDTH ))
          fi

          # Frames count is always original width*height / (frame_size^2)
          FRAMES_COUNT=$(( (SHEET_WIDTH / FRAME_SIZE) * (SHEET_HEIGHT / FRAME_SIZE) ))
        else
            COLS=0
            ROWS=0
            echo "$OG_FILE not found"
            continue
        fi
    else
      FRAMES_COUNT=$((COLS * ROWS))
    fi

    NAME_NO_EXT="${BASENAME%.png}"
    NAME_NO_EXT="${NAME_NO_EXT#[0-9]*_}"
    NAME_NO_EXT="${NAME_NO_EXT^}"
    NAME_CLEAN=$(echo "$NAME_NO_EXT" | sed "s/['().:]//g")
    NAME_CLEAN=$(echo "$NAME_CLEAN" | sed 's/[^a-zA-Z0-9]/_/g')
    NAME_CLEAN=$(echo "$NAME_CLEAN" | sed 's/_\+/_/g')
    IDENTIFIER=$(echo "$NAME_CLEAN" | tr '[:upper:]' '[:lower:]')
    MACRO_PREFIX=$(echo "${ASSETS_PREFIX_UPPER}_${IDENTIFIER}" | tr '[:lower:]' '[:upper:]')

    RELATIVE_PATH="../../../$INPUT_DIR/$BASENAME"

    FQID="${ASSETS_PREFIX_LOWER}:${IDENTIFIER}"
    FQNAME="${ASSETS_PREFIX_LOWER}:${NAME_NO_EXT}"

    DIGIMON_NAME=$NAME_NO_EXT
    STAGE=$(jq -r --arg name "$DIGIMON_NAME" --arg id "$NAME_CLEAN" '
      first(
         .digimons[] |
         select(.id == $id or .name == $name or (.altNames? and any(.altNames[]; . == $name)))
      ) | .level
    ' assets/digimon.db.json)

    EVO_TIME=-1
    if [ -z "$STAGE" ] || [ "$STAGE" == "null" ]; then
        echo "⚠️  WARNING: Digimon '$DIGIMON_NAME' was not found in the database!" >&2
    else
        EVO_TIME=$(jq -r --arg prefix "$ASSETS_PREFIX_CLEAN" --arg stage "$STAGE" '
          ._next_evolution_time_secs[$prefix][$stage]
        ' assets/digimon-vpets.db.json)

        if [ -z "$EVO_TIME" ] || [ "$EVO_TIME" == "null" ]; then
            echo "⚠️  WARNING: No evolution time found for Prefix: '$PREFIX' at Stage: '$STAGE'" >&2
            EVO_TIME=-1
        fi
    fi

    num_animation_indices=0
    animation_indices=()
    MAX_ANIMATION_INDICES=15  # Enforce the fixed-array max capacity
    NEXT_NAMES=$(jq -r --arg name "$DIGIMON_NAME" --arg id "$IDENTIFIER" --arg prefix "$ASSETS_PREFIX_CLEAN" '
        first(
           .[$prefix][] |
           select(.id == $id or .name == $name or (.names? and any(.names[]; . == $name)))
        ) | .next[]?
      ' assets/digimon-vpets.db.json)
      if [ -n "$NEXT_NAMES" ] && [ "$NEXT_NAMES" != "null" ]; then
        while IFS= read -r NEXT_NAME; do
            # Ensure the name is not empty
            [ -z "$NEXT_NAME" ] && continue

            # Check if we have already reached the maximum allowed elements
            if [ "$num_animation_indices" -ge "$MAX_ANIMATION_INDICES" ]; then
                echo "⚠️  WARNING: Digimon '$DIGIMON_NAME' has more than $MAX_ANIMATION_INDICES evolutions! Truncating excess target: '$NEXT_NAME'" >&2
                continue # Skip adding further items but continue loop if you want to log all truncated targets
            fi

            # Look up the index from your previously built map
            TARGET_INDEX="${NEXT_INDEX_MAP["$NEXT_NAME"]}"

            if [ -n "$TARGET_INDEX" ]; then
                animation_indices+=("$TARGET_INDEX")
                ((num_animation_indices++))
            else
                echo "⚠️  WARNING: Next evolution target '\''$NEXT_NAME'\'' for $DIGIMON_NAME has no mapped image index!" >&2
            fi
        done <<< "$NEXT_NAMES"
    fi
    ANIMATION_INDICES_STR=$(IFS=,; echo "${animation_indices[*]}")
    ANIMATION_INDICES_STR="${ANIMATION_INDICES_STR//,/ ,}"

    echo "            case ${MACRO_PREFIX}_ANIM_INDEX:" >> "$CPP_SOURCE_GET_EVOL_OUT"
    echo "              return {" >> "$CPP_SOURCE_GET_EVOL_OUT"
    echo "                // Stage: ${STAGE}" >> "$CPP_SOURCE_GET_EVOL_OUT"
    echo "                .conditions = { .next_evolution_time_sec = ${EVO_TIME} }," >> "$CPP_SOURCE_GET_EVOL_OUT"
    echo "                " >> "$CPP_SOURCE_GET_EVOL_OUT"
    echo "                .num_animation_indices = $num_animation_indices," >> "$CPP_SOURCE_GET_EVOL_OUT"
    echo "                .animation_indices = {" >> "$CPP_SOURCE_GET_EVOL_OUT"
    echo "                  ${ANIMATION_INDICES_STR}" >> "$CPP_SOURCE_GET_EVOL_OUT"
    echo "                }," >> "$CPP_SOURCE_GET_EVOL_OUT"
    echo "              };" >> "$CPP_SOURCE_GET_EVOL_OUT"

    ((INDEX++))
done

echo '            default: return {};' >> "$CPP_SOURCE_GET_EVOL_OUT"
echo '        }' >> "$CPP_SOURCE_GET_EVOL_OUT"
echo '        return {};' >> "$CPP_SOURCE_GET_EVOL_OUT"
echo '    }' >> "$CPP_SOURCE_GET_EVOL_OUT"
echo '}' >> "$CPP_SOURCE_GET_EVOL_OUT"
echo >> "$CPP_SOURCE_GET_EVOL_OUT"
