#!/bin/bash
# Generate the min_dm evolution data (src/embedded_assets/min_dm/min_dm_get_evolution_data.cpp).
#
# Only the min_dm sub-set is used (NOT the whole dm set):
#   sprites:   "<set>" list of the min db (default: assets/min-digimon-vpets.db.json, --set dm)
#   order:     MIN_DM_<NAME>_ANIM_INDEX from include/embedded_assets/min_dm/min_dm.hpp (table index == anim index)
#   evolution: "next" of the min db, only targets inside the sub-set
#   stage:     assets/digimon.db.pretty.json, evolution times: _next_evolution_time_secs.<set> of the min db
#
# Usage (same arguments as generate_embedded_assets_dm_evol.sh; <og-input-dir>/--frame-size/--layout are not needed
# for the evolution data and are only accepted for compatibility):
#   ./scripts/generate_embedded_assets_min_dm_evol.sh assets/dm assets/input/dm-2 \
#       src/embedded_assets/min_dm/min_dm_get_evolution_data.cpp --frame-size 128 --layout Dm --set dm
# The output prefix (min_dm) is taken from the output path, <input-dir> is only used to check the images.

set -uo pipefail

SET="dm"
DB_FILE="assets/min-digimon-vpets.db.json"
STAGE_DB_FILE="assets/digimon.db.pretty.json"
MAX_ANIMATION_INDICES=15  # animation::MAX_ANIMATION_EVOLUTION_INDICIES

POSITIONAL_ARGS=()
while [[ $# -gt 0 ]]; do
    case $1 in
        --frame-size|--cols|--rows|--layout) shift 2 ;;  # not needed for the evolution data
        --set) SET="$2"; shift 2 ;;
        --db) DB_FILE="$2"; shift 2 ;;
        -h|--help)
            echo "Usage: $0 <output-prefix-dir, e.g. assets/min_dm> <og-input-dir> <output-source> [--set dm] [--db FILE]"
            exit 0 ;;
        -*) echo "Unknown option $1"; exit 1 ;;
        *) POSITIONAL_ARGS+=("$1"); shift ;;
    esac
done

INPUT_DIR="${POSITIONAL_ARGS[0]:-}"
CPP_SOURCE_GET_EVOL_OUT="${POSITIONAL_ARGS[2]:-}"
if [[ -z "$INPUT_DIR" || -z "$CPP_SOURCE_GET_EVOL_OUT" ]]; then
    echo "Usage: $0 <input-dir, e.g. assets/dm> <og-input-dir> <output-source> [--set dm] [--db FILE]"
    exit 1
fi
command -v jq &>/dev/null || { echo "jq is required."; exit 1; }

# output prefix (min_dm) from the output path: src/embedded_assets/<prefix>/<prefix>_get_evolution_data.cpp
# (NOT from <input-dir>: the images are shared with the full set, e.g. assets/dm)
ASSETS_PREFIX=$(basename "$(dirname "$CPP_SOURCE_GET_EVOL_OUT")")
ASSETS_PREFIX_LOWER=$(echo "$ASSETS_PREFIX" | sed 's/[^a-zA-Z0-9]/_/g; s/_\+/_/g' | tr '[:upper:]' '[:lower:]')
ASSETS_PREFIX_UPPER=$(echo "$ASSETS_PREFIX_LOWER" | tr '[:lower:]' '[:upper:]')
# images: <input-dir> (assets/dm), fallback assets/<set> (e.g. when called with assets/min_dm)
IMAGES_DIR="${INPUT_DIR%/}"
[[ -d "$IMAGES_DIR" ]] || IMAGES_DIR="assets/$SET"
SPRITES_HPP="include/embedded_assets/${ASSETS_PREFIX_LOWER}/${ASSETS_PREFIX_LOWER}.hpp"
echo "Output prefix: $ASSETS_PREFIX_LOWER ($SPRITES_HPP), images: $IMAGES_DIR, sprites: \"$SET\" of $DB_FILE"

for f in "$DB_FILE" "$STAGE_DB_FILE" "$SPRITES_HPP"; do
    [[ -f "$f" ]] || { echo "ERROR: '$f' not found (run from the repository root)"; exit 1; }
done
jq -e --arg set "$SET" '.[$set] | type == "array"' "$DB_FILE" >/dev/null \
    || { echo "ERROR: '$DB_FILE' has no \"$SET\" list"; exit 1; }

# same name cleanup as generate_embedded_assets.sh
clean_name() {
    echo "$1" | sed "s/['().:]//g; s/[^a-zA-Z0-9]/_/g; s/_\+/_/g"
}

ANIM_COUNT=$(sed -n "s/.*${ASSETS_PREFIX_UPPER}_ANIM_COUNT[^=]*=[[:space:]]*\([0-9]\+\);.*/\1/p" "$SPRITES_HPP" | head -1)
[[ -n "$ANIM_COUNT" ]] || { echo "ERROR: ${ASSETS_PREFIX_UPPER}_ANIM_COUNT not found in $SPRITES_HPP"; exit 1; }

# === Sub-set: name -> anim index (from the sprites header) ===
mapfile -t NAMES < <(jq -r --arg set "$SET" '.[$set][].name' "$DB_FILE")
declare -A INDEX_OF=()     # name -> anim index
declare -A MACRO_OF=()     # name -> MIN_DM_<NAME>_ANIM_INDEX
declare -A NAME_AT=()      # anim index -> name
errors=0
for name in "${NAMES[@]}"; do
    [[ -z "$name" ]] && continue
    macro="${ASSETS_PREFIX_UPPER}_$(clean_name "$name" | tr '[:lower:]' '[:upper:]')_ANIM_INDEX"
    index=$(sed -n "s/.*[^A-Z_]${macro}[[:space:]]*=[[:space:]]*\([0-9]\+\);.*/\1/p" "$SPRITES_HPP" | head -1)
    if [[ -z "$index" ]]; then
        echo "ERROR: '$name': $macro not found in $SPRITES_HPP" >&2; errors=$((errors + 1)); continue
    fi
    [[ -f "$IMAGES_DIR/$name.png" ]] || echo "⚠️  WARNING: Missing asset for '$name' -> Expecting: $IMAGES_DIR/$name.png" >&2
    if [[ -n "${NAME_AT[$index]:-}" ]]; then
        echo "ERROR: '$name' and '${NAME_AT[$index]}' have the same anim index $index" >&2; errors=$((errors + 1)); continue
    fi
    INDEX_OF["$name"]=$index
    MACRO_OF["$name"]=$macro
    NAME_AT[$index]="$name"
done
for ((i = 0; i < ANIM_COUNT; i++)); do
    if [[ -z "${NAME_AT[$i]:-}" ]]; then
        echo "ERROR: anim index $i ($SPRITES_HPP) has no entry in \"$SET\" of $DB_FILE" >&2; errors=$((errors + 1))
    fi
done
if (( ${#INDEX_OF[@]} != ANIM_COUNT )); then
    echo "ERROR: $DB_FILE \"$SET\" has ${#INDEX_OF[@]} sprites, $SPRITES_HPP has ${ASSETS_PREFIX_UPPER}_ANIM_COUNT = $ANIM_COUNT" >&2
    errors=$((errors + 1))
fi
(( errors == 0 )) || { echo "ERROR: $errors error(s), nothing written"; exit 1; }

# === jq helpers ===
db_entry() {  # db_entry NAME FIELD
    jq -r --arg name "$1" --arg set "$SET" "first(.[\$set][] | select(.name == \$name or (.altNames? and any(.altNames[]; . == \$name)))) | .$2 // empty" "$DB_FILE"
}
evo_time() {  # evo_time STAGE
    local t
    t=$(jq -r --arg set "$SET" --arg stage "$1" '._next_evolution_time_secs[$set][$stage] // empty' "$DB_FILE")
    [[ -z "$t" ]] && t=$(jq -r --arg set "$SET" --arg stage "$1" '._next_evolution_time_secs[$set][$stage] // empty' assets/digimon-vpets.db.json 2>/dev/null)
    echo "$t"
}
stage_of() {  # stage_of NAME
    jq -r --arg name "$1" --arg id "$(clean_name "$1")" '
      first(.digimons[] | select(.id == $id or .name == $name or (.altNames? and any(.altNames[]; . == $name)))) | .level // empty
    ' "$STAGE_DB_FILE"
}

# === Table, ordered by anim index ===
TABLE=""
for ((i = 0; i < ANIM_COUNT; i++)); do
    name="${NAME_AT[$i]}"
    STAGE=$(stage_of "$name")
    EVO_TIME=-1
    if [[ -z "$STAGE" ]]; then
        echo "⚠️  WARNING: Digimon '$name' was not found in $STAGE_DB_FILE!" >&2
    else
        EVO_TIME=$(evo_time "$STAGE")
        if [[ -z "$EVO_TIME" ]]; then
            echo "⚠️  WARNING: No evolution time found for '$SET' at Stage '$STAGE' ('$name')" >&2
            EVO_TIME=-1
        fi
    fi

    JOGRESS=$(db_entry "$name" "jogress")
    if [[ "$JOGRESS" == "true" ]]; then
        t=$(evo_time "Jogress"); [[ -n "$t" ]] && EVO_TIME=$t
    fi
    MAX_STAGE=$(db_entry "$name" "max")
    if [[ "$MAX_STAGE" == "true" ]]; then
        t=$(evo_time "max"); [[ -n "$t" ]] && EVO_TIME=$t
    fi

    animation_indices=()
    while IFS= read -r next; do
        [[ -z "$next" ]] && continue
        if [[ -z "${MACRO_OF[$next]:-}" ]]; then
            echo "⚠️  WARNING: '$name' -> '$next' is not part of the $ASSETS_PREFIX_LOWER sub-set, skipped" >&2
            continue
        fi
        if (( ${#animation_indices[@]} >= MAX_ANIMATION_INDICES )); then
            echo "⚠️  WARNING: '$name' has more than $MAX_ANIMATION_INDICES evolutions, '$next' truncated" >&2
            continue
        fi
        # same Ultimate -> Ultimate rule as generate_embedded_assets_dm_evol.sh
        if [[ "$JOGRESS" != "true" && "$MAX_STAGE" != "true" && "$STAGE" == "Ultimate" && "$(stage_of "$next")" == "Ultimate" ]]; then
            t=$(evo_time "Jogress"); [[ -n "$t" ]] && EVO_TIME=$t
        fi
        animation_indices+=("${MACRO_OF[$next]}")
    done < <(jq -r --arg name "$name" --arg set "$SET" 'first(.[$set][] | select(.name == $name)) | .next[]?' "$DB_FILE")

    INDICES_STR=$(IFS=,; echo "${animation_indices[*]:-}")
    INDICES_STR="${INDICES_STR//,/ ,}"
    TABLE+="        // Name: $name\n"
    TABLE+="        {\n"
    TABLE+="            // Stage: ${STAGE}\n"
    TABLE+="            .conditions = { .next_evolution_time_sec = ${EVO_TIME} },\n"
    TABLE+="            .num_animation_indices = ${#animation_indices[@]},\n"
    TABLE+="            .animation_indices = {\n"
    TABLE+="                ${INDICES_STR}\n"
    TABLE+="            },\n"
    TABLE+="        },\n"
    echo "Add $name ($i) with ${#animation_indices[@]} evols"
done

# === Write ===
{
    echo "#include \"embedded_assets/embedded_image.h\""
    echo "#include \"embedded_assets/${ASSETS_PREFIX_LOWER}/${ASSETS_PREFIX_LOWER}.hpp\""
    echo "#include \"embedded_assets/${ASSETS_PREFIX_LOWER}/${ASSETS_PREFIX_LOWER}_evol.h\""
    echo "#include \"graphics/animation_shared_memory.h\""
    echo ""
    echo "/// @NOTE: Generated evolution data $ASSETS_PREFIX_LOWER"
    echo ""
    echo "namespace bongocat::assets {"
    cat <<'EOF'
      struct compact_evolution_conditions_t {
          int32_t next_evolution_time_sec{-1};
          int8_t min_lvl{-1};
      };
      struct compact_evolution_data_t {
          compact_evolution_conditions_t conditions;
          uint8_t num_animation_indices{0};
          int16_t animation_indices[animation::MAX_ANIMATION_EVOLUTION_INDICIES]{};
      };
      static animation::animation_evolution_data_t expand_evolution_data(const compact_evolution_data_t& data) {
          animation::animation_evolution_data_t ret;
          ret.conditions.next_evolution_time_sec = data.conditions.next_evolution_time_sec;
          ret.conditions.min_lvl = data.conditions.min_lvl;
          ret.num_animation_indices = data.num_animation_indices;
          for (size_t i = 0; i < animation::MAX_ANIMATION_EVOLUTION_INDICIES; ++i) {
              ret.animation_indices[i] = data.animation_indices[i];
          }
          return ret;
      }
EOF
    echo "    static constexpr compact_evolution_data_t ${ASSETS_PREFIX_LOWER}_evol_data_table[] ASSETS_${ASSETS_PREFIX_UPPER}_EVOL_DATA_SECTION = {"
    echo -en "$TABLE"
    echo "    };"
    echo "    static_assert(LEN_ARRAY(${ASSETS_PREFIX_LOWER}_evol_data_table) == ${ASSETS_PREFIX_UPPER}_ANIM_COUNT, \"re-run scripts/generate_embedded_assets_min_dm_evol.sh\");"
    echo "    animation::animation_evolution_data_t get_${ASSETS_PREFIX_LOWER}_evolution_data(size_t index) {"
    echo "        using namespace assets;"
    echo "        assert(index < ${ASSETS_PREFIX_UPPER}_ANIM_COUNT);"
    echo "        return expand_evolution_data(${ASSETS_PREFIX_LOWER}_evol_data_table[index]);"
    echo "    }"
    echo "}"
} > "$CPP_SOURCE_GET_EVOL_OUT"

echo "$ANIM_COUNT done -> $CPP_SOURCE_GET_EVOL_OUT"
