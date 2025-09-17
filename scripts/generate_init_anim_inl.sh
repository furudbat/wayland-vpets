#!/bin/bash

INPUT_DIR="$1"
OUTPUT_DIR="$2"
HEADER_FILE="$3"
PREFIX="$4"
START_INDEX="$5"
SET="Dm"
ALT=""

# === Parse args ===
POSITIONAL_ARGS=()
while [[ $# -gt 0 ]]; do
    case $1 in
        --set) SET="$2"; shift 2 ;;
        --alt) ALT="$2"; shift 2 ;;
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

SET_LOWER=$(echo "$SET" | tr '[:upper:]' '[:lower:]')

mkdir -p "${OUTPUT_DIR}/include"

OUTPUT_FILE_1="${OUTPUT_DIR}/include/${ASSETS_PREFIX_LOWER}_config_parse_enum_key.cpp.inl"
OUTPUT_FILE_2="${OUTPUT_DIR}/include/${ASSETS_PREFIX_LOWER}_init_${SET_LOWER}_anim.cpp.inl"
OUTPUT_FILE_3="${OUTPUT_DIR}/${ASSETS_PREFIX_LOWER}_get_sprite_sheet.cpp"
OUTPUT_FILE_4="${OUTPUT_DIR}/include/${ASSETS_PREFIX_LOWER}_config_parse_animation_name.h"
OUTPUT_FILE_5="${OUTPUT_DIR}/${ASSETS_PREFIX_LOWER}_config_parse_animation_name.cpp"

# Clean output files at the start
> "${OUTPUT_FILE_1}"
> "${OUTPUT_FILE_2}"
> "${OUTPUT_FILE_3}"
> "${OUTPUT_FILE_4}"
> "${OUTPUT_FILE_5}"

GET_SPRITE_SHEET_FUNC_NAME="get_${ASSETS_PREFIX_LOWER}_sprite_sheet"

echo "#include \"embedded_assets/embedded_image.h\"" >> "$OUTPUT_FILE_3"
echo "#include \"embedded_assets/${ASSETS_PREFIX_LOWER}/${ASSETS_PREFIX_LOWER}.hpp\"" >> "$OUTPUT_FILE_3"
echo "#include \"embedded_assets/${ASSETS_PREFIX_LOWER}/${ASSETS_PREFIX_LOWER}_images.h\"" >> "$OUTPUT_FILE_3"
echo "#include \"embedded_assets/${ASSETS_PREFIX_LOWER}/${ASSETS_PREFIX_LOWER}_sprite.h\"" >> "$OUTPUT_FILE_3"
echo "" >> "$OUTPUT_FILE_3"
echo "namespace bongocat::assets {" >> "$OUTPUT_FILE_3"
echo "    embedded_image_t ${GET_SPRITE_SHEET_FUNC_NAME}(size_t index) {" >> "$OUTPUT_FILE_3"
echo "        switch (index) {" >> "$OUTPUT_FILE_3"



GET_CONFIG_ANIMATION_NAME_FUNC_NAME="get_config_animation_name_${ASSETS_PREFIX_LOWER}"
CONFIG_PARSE_FUNC_NAME="config_parse_animation_name_${ASSETS_PREFIX_LOWER}"
OUTPUT_FILE_4_HEADER_GUARD="BONGOCAT_EMBEDDED_ASSETS_CONFIG_PARSE_${ASSETS_PREFIX_UPPER}_ANIMATION_NAME_H"
echo "#ifndef $OUTPUT_FILE_4_HEADER_GUARD" >> "$OUTPUT_FILE_4"
echo "#define $OUTPUT_FILE_4_HEADER_GUARD" >> "$OUTPUT_FILE_4"
echo >> "$OUTPUT_FILE_4"
echo "#include \"config/config.h\"" >> "$OUTPUT_FILE_4"
echo "#include \"embedded_assets/embedded_image.h\"" >> "$OUTPUT_FILE_4"
echo >> "$OUTPUT_FILE_4"
echo "namespace bongocat::assets {" >> "$OUTPUT_FILE_4"
echo "    [[nodiscard]] extern config_animation_entry_t ${GET_CONFIG_ANIMATION_NAME_FUNC_NAME}(size_t i);" >> "$OUTPUT_FILE_4"
echo "    extern void ${CONFIG_PARSE_FUNC_NAME}(config::config_t& config, const char *value);" >> "$OUTPUT_FILE_4"
echo "}" >> "$OUTPUT_FILE_4"
echo >> "$OUTPUT_FILE_4"
echo "#endif" >> "$OUTPUT_FILE_4"
echo >> "$OUTPUT_FILE_4"


echo "#include \"embedded_assets/embedded_image.h\"" >> "$OUTPUT_FILE_5"
echo "#include \"embedded_assets/${ASSETS_PREFIX_LOWER}/${ASSETS_PREFIX_LOWER}.hpp\"" >> "$OUTPUT_FILE_5"
echo "#include \"${ASSETS_PREFIX_LOWER}_config_parse_animation_name.h\"" >> "$OUTPUT_FILE_5"
echo "" >> "$OUTPUT_FILE_5"
echo "namespace bongocat::assets {" >> "$OUTPUT_FILE_5"
echo "    static const config_animation_entry_t ${ASSETS_PREFIX_LOWER}_animation_table[] = {" >> "$OUTPUT_FILE_5"

# === Start animation index counter ===
INDEX=$START_INDEX

# === Process all PNGs ===
for FILE in "$INPUT_DIR"/*.png; do
    BASENAME=$(basename "$FILE")

    NAME_NO_EXT="${BASENAME%.png}"
    NAME_NO_EXT="${NAME_NO_EXT#[0-9]*_}"
    NAME_CLEAN=$(echo "$NAME_NO_EXT" | sed "s/['().:]//g")
    NAME_CLEAN=$(echo "$NAME_CLEAN" | sed 's/[^a-zA-Z0-9]/_/g')
    NAME_CLEAN=$(echo "$NAME_CLEAN" | sed 's/_\+/_/g')
    IDENTIFIER=$(echo "$NAME_CLEAN" | tr '[:upper:]' '[:lower:]')
    MACRO_PREFIX=$(echo "${ASSETS_PREFIX_UPPER}_${IDENTIFIER}" | tr '[:lower:]' '[:upper:]')

    FQID="${ASSETS_PREFIX_LOWER}:${IDENTIFIER}"
    FQNAME="${ASSETS_PREFIX_LOWER}:${NAME_NO_EXT}"

    EMBED_SYMBOL="${ASSETS_PREFIX_LOWER}_${IDENTIFIER}_png"
    SIZE_SYMBOL="${EMBED_SYMBOL}_size"

    echo "// check for ${NAME_NO_EXT^} (${IDENTIFIER})" >> "$OUTPUT_FILE_1"
    if [[ -n $ALT ]]; then
      ALT_LOWER=$(echo "$ALT" | tr '[:upper:]' '[:lower:]')
      ALT_UPPER=$(echo "$ALT" | tr '[:lower:]' '[:upper:]')

      ALT_FQID="${ALT_LOWER}:${IDENTIFIER}"
      ALT_FQNAME="${ALT_LOWER}:${NAME_NO_EXT}"

      echo "if (strcmp(value, ${MACRO_PREFIX}_NAME) == 0 ||" >> "$OUTPUT_FILE_1"
      echo "    strcmp(value, ${MACRO_PREFIX}_ID) == 0 ||" >> "$OUTPUT_FILE_1"
      echo "    strcmp(value, ${MACRO_PREFIX}_FQID) == 0 ||" >> "$OUTPUT_FILE_1"
      echo "    strcmp(value, ${MACRO_PREFIX}_FQNAME) == 0 ||" >> "$OUTPUT_FILE_1"
      echo "    // alt" >> "$OUTPUT_FILE_1"
      echo "    strcmp(value, \"${ALT_FQID}\") == 0 ||" >> "$OUTPUT_FILE_1"
      echo "    strcmp(value, \"${ALT_FQNAME}\") == 0) {" >> "$OUTPUT_FILE_1"
      echo "    config.animation_index = ${MACRO_PREFIX}_ANIM_INDEX;" >> "$OUTPUT_FILE_1"
      echo "    config.animation_dm_set = config_animation_dm_set_t::${ASSETS_PREFIX_LOWER};" >> "$OUTPUT_FILE_1"
      echo "    config.animation_sprite_sheet_layout = config_animation_sprite_sheet_layout_t::${SET};" >> "$OUTPUT_FILE_1"
      echo "}" >> "$OUTPUT_FILE_1"
    else
      echo "if (strcmp(value, ${MACRO_PREFIX}_NAME) == 0 ||" >> "$OUTPUT_FILE_1"
      echo "    strcmp(value, ${MACRO_PREFIX}_ID) == 0 ||" >> "$OUTPUT_FILE_1"
      echo "    strcmp(value, ${MACRO_PREFIX}_FQID) == 0 ||" >> "$OUTPUT_FILE_1"
      echo "    strcmp(value, ${MACRO_PREFIX}_FQNAME) == 0) {" >> "$OUTPUT_FILE_1"
      echo "    config.animation_index = ${MACRO_PREFIX}_ANIM_INDEX;" >> "$OUTPUT_FILE_1"
      echo "    config.animation_dm_set = config_animation_dm_set_t::${ASSETS_PREFIX_LOWER};" >> "$OUTPUT_FILE_1"
      echo "    config.animation_sprite_sheet_layout = config_animation_sprite_sheet_layout_t::${SET};" >> "$OUTPUT_FILE_1"
      echo "}" >> "$OUTPUT_FILE_1"
    fi

    echo "init_${ASSETS_PREFIX_LOWER}_anim(ctx, ${MACRO_PREFIX}_ANIM_INDEX, ${GET_SPRITE_SHEET_FUNC_NAME}(${MACRO_PREFIX}_ANIM_INDEX), ${MACRO_PREFIX}_SPRITE_SHEET_COLS, ${MACRO_PREFIX}_SPRITE_SHEET_ROWS);" >> "$OUTPUT_FILE_2"

    echo "            case ${MACRO_PREFIX}_ANIM_INDEX: return {${EMBED_SYMBOL}, ${SIZE_SYMBOL}, \"${IDENTIFIER}\"};" >> "$OUTPUT_FILE_3"

    echo "        { ${MACRO_PREFIX}_NAME, ${MACRO_PREFIX}_ID, ${MACRO_PREFIX}_FQID, ${MACRO_PREFIX}_FQNAME, ${MACRO_PREFIX}_ANIM_INDEX, config::config_animation_dm_set_t::${ASSETS_PREFIX_LOWER}, config::config_animation_sprite_sheet_layout_t::${SET} }," >> "$OUTPUT_FILE_5"
    if [[ -n $ALT ]]; then
      ALT_LOWER=$(echo "$ALT" | tr '[:upper:]' '[:lower:]')
      ALT_UPPER=$(echo "$ALT" | tr '[:lower:]' '[:upper:]')

      ALT_FQID="${ALT_LOWER}:${IDENTIFIER}"
      ALT_FQNAME="${ALT_LOWER}:${NAME_NO_EXT}"

      echo "        { ${MACRO_PREFIX}_NAME, ${MACRO_PREFIX}_ID, \"${ALT_FQID}\", \"${ALT_FQNAME}\", ${MACRO_PREFIX}_ANIM_INDEX, config::config_animation_dm_set_t::${ASSETS_PREFIX_LOWER}, config::config_animation_sprite_sheet_layout_t::${SET} },  // alt ids for ${NAME_NO_EXT}" >> "$OUTPUT_FILE_5"
    fi

    ((INDEX++))
done

echo '            default: return { nullptr, 0, "" };' >> "$OUTPUT_FILE_3"
echo '        }' >> "$OUTPUT_FILE_3"
echo '        return { nullptr, 0, "" };' >> "$OUTPUT_FILE_3"
echo '    }' >> "$OUTPUT_FILE_3"
echo '}' >> "$OUTPUT_FILE_3"
echo >> "$OUTPUT_FILE_3"

echo '    };' >> "$OUTPUT_FILE_5"
echo >> "$OUTPUT_FILE_5"
echo "    config_animation_entry_t ${GET_CONFIG_ANIMATION_NAME_FUNC_NAME}(size_t index) {" >> "$OUTPUT_FILE_5"
echo "        return ${ASSETS_PREFIX_LOWER}_animation_table[index];" >> "$OUTPUT_FILE_5"
echo '    }' >> "$OUTPUT_FILE_5"
echo >> "$OUTPUT_FILE_5"
echo "    void ${CONFIG_PARSE_FUNC_NAME}(config::config_t& config, const char *value) {" >> "$OUTPUT_FILE_5"
echo "        for (const auto& entry : ${ASSETS_PREFIX_LOWER}_animation_table) {" >> "$OUTPUT_FILE_5"
echo "            if (strcmp(value, entry.name) == 0 ||" >> "$OUTPUT_FILE_5"
echo "                strcmp(value, entry.id) == 0 ||" >> "$OUTPUT_FILE_5"
echo "                strcmp(value, entry.fqid) == 0 ||" >> "$OUTPUT_FILE_5"
echo "                strcmp(value, entry.fqname) == 0) {" >> "$OUTPUT_FILE_5"
echo "                config.animation_index = entry.anim_index;" >> "$OUTPUT_FILE_5"
echo "                config.animation_dm_set = entry.set;" >> "$OUTPUT_FILE_5"
echo "                config.animation_sprite_sheet_layout = entry.layout;" >> "$OUTPUT_FILE_5"
echo '                break;' >> "$OUTPUT_FILE_5"
echo '            }' >> "$OUTPUT_FILE_5"
echo '        }' >> "$OUTPUT_FILE_5"
echo '    }' >> "$OUTPUT_FILE_5"
echo '}' >> "$OUTPUT_FILE_5"
echo >> "$OUTPUT_FILE_5"