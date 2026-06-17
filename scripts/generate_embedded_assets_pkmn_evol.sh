#!/bin/bash

POKEAPI_URL=http://localhost:8081/api/v2

# === Usage Check ===
if [[ $# -lt 3 ]]; then
    echo "Usage: $0 <input-dir> <og-input-dir> <output-source>"
    echo "Example: $0 assets/pkmn assets/input/pkmn src/embedded_assets/pkmn/pkmn_get_evolution_data.cpp"
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
LAYOUT="None"
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

    NAME_NO_EXT_2="${BASENAME%.png}"
    NUMBER="${NAME_NO_EXT_2%%_*}"
    PKMN_NAME="${NAME_NO_EXT_2#*_}"

    NEXT_INDEX_MAP["$PKMN_NAME"]=${MACRO_PREFIX}_ANIM_INDEX

    ((INDEX++))
done

# === Start animation index counter ===
INDEX=$START_INDEX

CPP_SOURCE_GET_EVOL_DATA_TABLE_OUT=""

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

    NAME_NO_EXT_2="${BASENAME%.png}"
    NUMBER="${NAME_NO_EXT_2%%_*}"
    PKMN_NAME="${NAME_NO_EXT_2#*_}"

    num_animation_indices=0
    animation_indices=()
    MAX_ANIMATION_INDICES=15  # Enforce the fixed-array max capacity


    SPECIES_URL="$POKEAPI_URL/pokemon-species/$PKMN_NAME/"
    #echo $SPECIES_URL

    SPECIES_JSON=$(curl -s "$SPECIES_URL")
    if ! echo "$SPECIES_JSON" | jq empty 2>/dev/null; then
        echo "⚠️ Invalid species JSON for $PKMN_NAME" >&2
        continue
    fi
    #sleep $((30 + RANDOM % 15))

    CHAIN_URL=$(echo "$SPECIES_JSON" | jq -r '.evolution_chain.url // empty')
    if [ -z "$CHAIN_URL" ]; then
        echo "⚠️ No evolution chain for $PKMN_NAME" >&2
        continue
    fi
    NEXT_NAMES=$(curl -s "$CHAIN_URL" | jq -r --arg name "$PKMN_NAME" '
      def walk($from):
        if .species.name == $from then
          .evolves_to[]? | .species.name
        else
          .evolves_to[]? | walk($from)
        end;

      .chain | walk($name)
    ')
    #sleep $((30 + RANDOM % 15))

    EVOL_DATA=$(curl -fsS "$CHAIN_URL" | jq -c --arg name "$PKMN_NAME" '
      def walk($from):
        if .species.name == $from then
          .evolves_to[]? |
          {
            next: .species.name,
            details: .evolution_details[]
          }
        else
          .evolves_to[]? | walk($from)
        end;

      .chain | walk($name)
    ')
    #sleep $((30 + RANDOM % 15))
    REQ_LEVEL=$(echo "$EVOL_DATA" | jq -s '
      map(
        .details as $d
        | (
            if $d.min_level? != null then $d.min_level
            elif $d.held_item? != null then 32
            elif $d.item? != null then 32
            elif $d.trigger?.name == "trade" then 28
            elif (
              $d.trigger?.name == "friendship"
              or $d.trigger?.name == "affection"
            ) then 8
            else 24
            end
          )
      )
      | if length == 0 then -1 else min end
    ')

    #echo $EVOL_DATA

    while IFS= read -r NEXT_NAME; do
        [ -z "$NEXT_NAME" ] && continue

        # limit size
        if [ "$num_animation_indices" -ge "$MAX_ANIMATION_INDICES" ]; then
            echo "⚠️ Too many evolutions for $PKMN_NAME (truncating $NEXT_NAME)" >&2
            continue
        fi

        # lookup index
        TARGET_INDEX="${NEXT_INDEX_MAP["$NEXT_NAME"]}"

        if [ -n "$TARGET_INDEX" ]; then
            animation_indices+=("$TARGET_INDEX")
            ((num_animation_indices++))
        else
            echo "⚠️ Missing index mapping for evolution '$NEXT_NAME'" >&2
        fi
    done <<< "$NEXT_NAMES"

    ANIMATION_INDICES_STR=$(IFS=,; echo "${animation_indices[*]}")
    ANIMATION_INDICES_STR="${ANIMATION_INDICES_STR//,/ ,}"

    CPP_SOURCE_GET_EVOL_DATA_TABLE_OUT="${CPP_SOURCE_GET_EVOL_DATA_TABLE_OUT}        // Name: $NAME_NO_EXT\n"
    CPP_SOURCE_GET_EVOL_DATA_TABLE_OUT="${CPP_SOURCE_GET_EVOL_DATA_TABLE_OUT}        {\n"
    CPP_SOURCE_GET_EVOL_DATA_TABLE_OUT="${CPP_SOURCE_GET_EVOL_DATA_TABLE_OUT}            // Stage: ${STAGE}\n"
    CPP_SOURCE_GET_EVOL_DATA_TABLE_OUT="${CPP_SOURCE_GET_EVOL_DATA_TABLE_OUT}            .conditions = { .next_evolution_time_sec = -1, .min_lvl = ${REQ_LEVEL} },\n"
    CPP_SOURCE_GET_EVOL_DATA_TABLE_OUT="${CPP_SOURCE_GET_EVOL_DATA_TABLE_OUT}            \n"
    CPP_SOURCE_GET_EVOL_DATA_TABLE_OUT="${CPP_SOURCE_GET_EVOL_DATA_TABLE_OUT}            .num_animation_indices = ${num_animation_indices},\n"
    CPP_SOURCE_GET_EVOL_DATA_TABLE_OUT="${CPP_SOURCE_GET_EVOL_DATA_TABLE_OUT}            .animation_indices = {\n"
    CPP_SOURCE_GET_EVOL_DATA_TABLE_OUT="${CPP_SOURCE_GET_EVOL_DATA_TABLE_OUT}                ${ANIMATION_INDICES_STR}\n"
    CPP_SOURCE_GET_EVOL_DATA_TABLE_OUT="${CPP_SOURCE_GET_EVOL_DATA_TABLE_OUT}            },\n"
    CPP_SOURCE_GET_EVOL_DATA_TABLE_OUT="${CPP_SOURCE_GET_EVOL_DATA_TABLE_OUT}        },\n"

    echo "Add $NUMBER $PKMN_NAME with $num_animation_indices evols; lvl: $REQ_LEVEL"

    ((INDEX++))
done

echo "$INDEX done"

echo "#include \"embedded_assets/embedded_image.h\"" >> "$CPP_SOURCE_GET_EVOL_OUT"
echo "#include \"embedded_assets/${ASSETS_PREFIX_LOWER}/${ASSETS_PREFIX_LOWER}.hpp\"" >> "$CPP_SOURCE_GET_EVOL_OUT"
echo "#include \"embedded_assets/${ASSETS_PREFIX_LOWER}/${ASSETS_PREFIX_LOWER}_evol.h\"" >> "$CPP_SOURCE_GET_EVOL_OUT"
echo "#include \"graphics/animation_shared_memory.h\"" >> "$CPP_SOURCE_GET_EVOL_OUT"
echo >> "$CPP_SOURCE_GET_EVOL_OUT"
echo "/// @NOTE: Generated evolution data $ASSETS_PREFIX" >> "$CPP_SOURCE_GET_EVOL_OUT"
echo >> "$CPP_SOURCE_GET_EVOL_OUT"
echo "namespace bongocat::assets {" >> "$CPP_SOURCE_GET_EVOL_OUT"
echo "    static constexpr animation::animation_evolution_data_t ${ASSETS_PREFIX_LOWER}_evol_data_table[] = {" >> "$CPP_SOURCE_GET_EVOL_OUT"
echo -e "${CPP_SOURCE_GET_EVOL_DATA_TABLE_OUT}" >> "$CPP_SOURCE_GET_EVOL_OUT"
echo "    };" >> "$CPP_SOURCE_GET_EVOL_OUT"
echo "    animation::animation_evolution_data_t ${GET_EVOL_DATA_FUNC_NAME}(size_t index) {" >> "$CPP_SOURCE_GET_EVOL_OUT"
echo "        using namespace assets;" >> "$CPP_SOURCE_GET_EVOL_OUT"
echo "        assert(LEN_ARRAY(${ASSETS_PREFIX_LOWER}_evol_data_table) == ${ASSETS_PREFIX_UPPER}_ANIM_COUNT);" >> "$CPP_SOURCE_GET_EVOL_OUT"
echo "        assert(index < ${ASSETS_PREFIX_UPPER}_ANIM_COUNT);" >> "$CPP_SOURCE_GET_EVOL_OUT"
echo "        return ${ASSETS_PREFIX_LOWER}_evol_data_table[index];" >> "$CPP_SOURCE_GET_EVOL_OUT"
echo '    }' >> "$CPP_SOURCE_GET_EVOL_OUT"
echo '}' >> "$CPP_SOURCE_GET_EVOL_OUT"
echo >> "$CPP_SOURCE_GET_EVOL_OUT"
