#!/bin/bash

INPUT_DIR="$1"
OUTPUT_DIR="$2"
HEADER_FILE="$3"
PREFIX="$4"
START_INDEX="$5"

# === Parse args ===
POSITIONAL_ARGS=()
while [[ $# -gt 0 ]]; do
    case $1 in
        -*|--*)
            echo "Unknown option $1"; exit 1 ;;
        *) POSITIONAL_ARGS+=("$1"); shift ;;
    esac
done
set -- "${POSITIONAL_ARGS[@]}"

INPUT_DIR="${POSITIONAL_ARGS[0]}"
OUTPUT_DIR="${POSITIONAL_ARGS[1]}"
HEADER_FILE="${POSITIONAL_ARGS[2]}"
PREFIX="${POSITIONAL_ARGS[3]}"
START_INDEX="${POSITIONAL_ARGS[4]:-0}"

# Either (COLS and ROWS) or --frame-size must be provided
if [[ -z "$OUTPUT_DIR" || -z "$HEADER_FILE" || -z $PREFIX ]]; then
    echo "Usage: $0 <input-dir> <output-dir> <output-header-file> <prefix>"
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

mkdir -p "${OUTPUT_DIR}/include"

OUTPUT_FILE_1="${OUTPUT_DIR}/include/${ASSETS_PREFIX_LOWER}_config_parse_enum_key.cpp.inl"
OUTPUT_FILE_2="${OUTPUT_DIR}/include/${ASSETS_PREFIX_LOWER}_init_dm_anim.cpp.inl"
OUTPUT_FILE_3="${OUTPUT_DIR}/${ASSETS_PREFIX_LOWER}_get_sprite_sheet.cpp"

# Clean output files at the start
> "${OUTPUT_FILE_1}"
> "${OUTPUT_FILE_2}"
> "${OUTPUT_FILE_3}"

GET_SPRITE_SHEET_FUNC_NAME="get_${ASSETS_PREFIX_LOWER}_sprite_sheet"

echo "#include \"embedded_assets/embedded_image.h\"" >> "$OUTPUT_FILE_3"
echo "#include \"embedded_assets/${ASSETS_PREFIX_LOWER}/${ASSETS_PREFIX_LOWER}.hpp\"" >> "$OUTPUT_FILE_3"
echo "#include \"embedded_assets/${ASSETS_PREFIX_LOWER}/${ASSETS_PREFIX_LOWER}_images.h\"" >> "$OUTPUT_FILE_3"
echo "#include \"embedded_assets/${ASSETS_PREFIX_LOWER}/${ASSETS_PREFIX_LOWER}_sprite.h\"" >> "$OUTPUT_FILE_3"
echo "" >> "$OUTPUT_FILE_3"
echo "namespace bongocat::assets {" >> "$OUTPUT_FILE_3"
echo "    embedded_image_t ${GET_SPRITE_SHEET_FUNC_NAME}(size_t i) {" >> "$OUTPUT_FILE_3"
echo "        using namespace assets;" >> "$OUTPUT_FILE_3"
echo "        switch (i) {" >> "$OUTPUT_FILE_3"

# === Start animation index counter ===
INDEX=$START_INDEX

# === Process all PNGs ===
for FILE in "$INPUT_DIR"/*.png; do
    BASENAME=$(basename "$FILE")

    NAME_NO_EXT="${BASENAME%.png}"
    NAME_CLEAN=$(echo "$NAME_NO_EXT" | sed "s/['().:]//g")
    NAME_CLEAN=$(echo "$NAME_CLEAN" | sed 's/[^a-zA-Z0-9]/_/g')
    NAME_CLEAN=$(echo "$NAME_CLEAN" | sed 's/_\+/_/g')
    IDENTIFIER=$(echo "$NAME_CLEAN" | tr '[:upper:]' '[:lower:]')
    MACRO_PREFIX=$(echo "${ASSETS_PREFIX_UPPER}_${IDENTIFIER}" | tr '[:lower:]' '[:upper:]')

    EMBED_SYMBOL="${ASSETS_PREFIX_LOWER}_${IDENTIFIER}_png"
    SIZE_SYMBOL="${EMBED_SYMBOL}_size"

    echo "if (strncmp(lower_value, \"${IDENTIFIER}\", sizeof(\"${IDENTIFIER}\") - 1) == 0) {" >> "$OUTPUT_FILE_1"
    echo "    config.animation_index = ${MACRO_PREFIX}_ANIM_INDEX;" >> "$OUTPUT_FILE_1"
    echo "    config.animation_dm_set = config_animation_dm_set_t::${ASSETS_PREFIX_LOWER};" >> "$OUTPUT_FILE_1"
    echo "    config.animation_sprite_sheet_layout = config_animation_sprite_sheet_layout_t::Dm;" >> "$OUTPUT_FILE_1"
    echo "}" >> "$OUTPUT_FILE_1"

    echo "init_${ASSETS_PREFIX_LOWER}_anim(ctx, ${MACRO_PREFIX}_ANIM_INDEX, ${GET_SPRITE_SHEET_FUNC_NAME}(${MACRO_PREFIX}_ANIM_INDEX), ${MACRO_PREFIX}_SPRITE_SHEET_COLS, ${MACRO_PREFIX}_SPRITE_SHEET_ROWS);" >> "$OUTPUT_FILE_2"

    echo "        case ${MACRO_PREFIX}_ANIM_INDEX: return {${EMBED_SYMBOL}, ${SIZE_SYMBOL}, \"${IDENTIFIER}\"};" >> "$OUTPUT_FILE_3"


    ((INDEX++))
done

echo "            default: return { nullptr, 0, \"\" };" >> "$OUTPUT_FILE_3"
echo "        }" >> "$OUTPUT_FILE_3"
echo "        return { nullptr, 0, \"\" };" >> "$OUTPUT_FILE_3"
echo "    }" >> "$OUTPUT_FILE_3"
echo "}" >> "$OUTPUT_FILE_3"
echo "" >> "$OUTPUT_FILE_3"
