#!/bin/bash

INPUT_DIR="$1"
OUTPUT_DIR="$2"
HEADER_FILE="$3"
PREFIX="$4"
START_INDEX="$5"
LAYOUT="Dm"
SET=""
ALT=""

# === Parse args ===
POSITIONAL_ARGS=()
while [[ $# -gt 0 ]]; do
    case $1 in
        --layout) LAYOUT="$2"; shift 2 ;;
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

LAYOUT_LOWER=$(echo "$LAYOUT" | tr '[:upper:]' '[:lower:]')

mkdir -p "${OUTPUT_DIR}/include"

# TODO: better variable naming
OUTPUT_FILE_4="${OUTPUT_DIR}/include/${ASSETS_PREFIX_LOWER}_config_parse_animation_name.h"
OUTPUT_FILE_5="${OUTPUT_DIR}/${ASSETS_PREFIX_LOWER}_config_parse_animation_name.cpp"

# Clean output files at the start
> "${OUTPUT_FILE_4}"
> "${OUTPUT_FILE_5}"

GET_SPRITE_SHEET_FUNC_NAME="get_${ASSETS_PREFIX_LOWER}_sprite_sheet"
GET_SPRITE_SHEET_SETTINGS_FUNC_NAME="get_${ASSETS_PREFIX_LOWER}_sprite_sheet_settings"


GET_CONFIG_ANIMATION_NAME_FUNC_NAME="get_config_animation_name_${ASSETS_PREFIX_LOWER}"
CONFIG_PARSE_FUNC_NAME="config_parse_animation_name_${ASSETS_PREFIX_LOWER}"
UNLOAD_CONFIG_PARSE_NAMES_FUNC_NAME="unload_config_parse_animation_names_${ASSETS_PREFIX_LOWER}"
OUTPUT_FILE_4_HEADER_GUARD="BONGOCAT_EMBEDDED_ASSETS_CONFIG_PARSE_CUSTOM_${ASSETS_PREFIX_UPPER}_ANIMATION_NAME_H"
echo "#ifndef $OUTPUT_FILE_4_HEADER_GUARD" >> "$OUTPUT_FILE_4"
echo "#define $OUTPUT_FILE_4_HEADER_GUARD" >> "$OUTPUT_FILE_4"
echo >> "$OUTPUT_FILE_4"
echo "#include \"config/config.h\"" >> "$OUTPUT_FILE_4"
echo "#include \"embedded_assets/embedded_image.h\"" >> "$OUTPUT_FILE_4"
echo >> "$OUTPUT_FILE_4"
echo "namespace bongocat::assets {" >> "$OUTPUT_FILE_4"
echo "    BONGOCAT_NODISCARD extern config_custom_animation_entry_t ${GET_CONFIG_ANIMATION_NAME_FUNC_NAME}(size_t i);" >> "$OUTPUT_FILE_4"
echo "    extern int ${CONFIG_PARSE_FUNC_NAME}(config::config_t& config, const char *value);" >> "$OUTPUT_FILE_4"
echo "}" >> "$OUTPUT_FILE_4"
echo >> "$OUTPUT_FILE_4"
echo "#endif" >> "$OUTPUT_FILE_4"
echo >> "$OUTPUT_FILE_4"


# === Start animation index counter ===
INDEX=$START_INDEX

OUTPUT_FILE_3_IMAGES_TABLE=""
OUTPUT_FILE_5_ANIMATION_TABLE=""
OUTPUT_FILE_5_ALT_ANIMATIONS=""
OUTPUT_FILE_5_NORMAL_ENTRY=""

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

    KEY="${BASENAME%.png}"

    FQID="${ASSETS_PREFIX_LOWER}:${IDENTIFIER}"
    FQNAME="${ASSETS_PREFIX_LOWER}:${NAME_NO_EXT}"

    EMBED_SYMBOL="${ASSETS_PREFIX_LOWER}_${IDENTIFIER}_png"
    SIZE_SYMBOL="${EMBED_SYMBOL}_size"

    #echo "init_${ASSETS_PREFIX_LOWER}_anim(ctx, ${MACRO_PREFIX}_ANIM_INDEX, ${GET_SPRITE_SHEET_FUNC_NAME}(${MACRO_PREFIX}_ANIM_INDEX), ${GET_SPRITE_SHEET_SETTINGS_FUNC_NAME}(${MACRO_PREFIX}_ANIM_INDEX));" >> "$OUTPUT_FILE_2"

    #echo "            case ${MACRO_PREFIX}_ANIM_INDEX: return {${EMBED_SYMBOL}, ${SIZE_SYMBOL}, \"${IDENTIFIER}\"};" >> "$OUTPUT_FILE_3"
    OUTPUT_FILE_3_IMAGES_TABLE="${OUTPUT_FILE_3_IMAGES_TABLE}{${EMBED_SYMBOL}, ${SIZE_SYMBOL}, ${MACRO_PREFIX}_ID}, \n        "

    #echo "        { ${MACRO_PREFIX}_NAME, ${MACRO_PREFIX}_ID, ${MACRO_PREFIX}_FQID, ${MACRO_PREFIX}_FQNAME, ${MACRO_PREFIX}_ANIM_INDEX, config::config_animation_custom_set_t::${ASSETS_PREFIX_LOWER}, config::config_animation_sprite_sheet_layout_t::${LAYOUT} }," >> "$OUTPUT_FILE_5"
    # offsets into ${ASSETS_PREFIX_UPPER}_STRINGS (written by scripts/build_string_blobs.sh)
    OUTPUT_FILE_5_NORMAL_ENTRY="${MACRO_PREFIX}_NAME_OFF, ${MACRO_PREFIX}_ID_OFF, ${MACRO_PREFIX}_FQID_OFF, ${MACRO_PREFIX}_FQNAME_OFF, ${MACRO_PREFIX}_ANIM_INDEX, config::config_animation_custom_set_t::${SET}, config::config_animation_sprite_sheet_layout_t::${LAYOUT}"


    if [[ -n $ALT ]]; then
      ALT_LOWER=$(echo "$ALT" | tr '[:upper:]' '[:lower:]')
      ALT_UPPER=$(echo "$ALT" | tr '[:lower:]' '[:upper:]')

      ALT_FQID="${ALT_LOWER}:${IDENTIFIER}"
      ALT_FQNAME="${ALT_LOWER}:${NAME_NO_EXT}"

      ALT_MACRO_PREFIX=$(echo "${ALT_UPPER}_${IDENTIFIER}" | tr '[:lower:]' '[:upper:]')

      OUTPUT_FILE_5_ALT_ANIMATIONS="${OUTPUT_FILE_5_ALT_ANIMATIONS}    static constexpr char ALT_${MACRO_PREFIX}_FQID_ARR[] CONFIG_LOCAL_STRING_SECTION = \"${ALT_FQID}\";\n"
      OUTPUT_FILE_5_ALT_ANIMATIONS="${OUTPUT_FILE_5_ALT_ANIMATIONS}    static constexpr char ALT_${MACRO_PREFIX}_FQNAME_ARR[] CONFIG_LOCAL_STRING_SECTION = \"${ALT_FQNAME}\";\n"

      # one row per animation: normal offsets + alt fqid/fqname offsets (into ALT_${ASSETS_PREFIX_UPPER}_STRINGS)
      OUTPUT_FILE_5_ANIMATION_TABLE="${OUTPUT_FILE_5_ANIMATION_TABLE}{ ${OUTPUT_FILE_5_NORMAL_ENTRY}, ALT_${MACRO_PREFIX}_FQID_OFF, ALT_${MACRO_PREFIX}_FQNAME_OFF },  // ${NAME_NO_EXT}\n        "

    else
      OUTPUT_FILE_5_ANIMATION_TABLE="${OUTPUT_FILE_5_ANIMATION_TABLE}{ ${OUTPUT_FILE_5_NORMAL_ENTRY} },  // ${NAME_NO_EXT}\n        "
    fi

    echo "Add $IDENTIFIER"

    ((INDEX++))
done

echo "$INDEX done"


echo "#include \"embedded_assets/embedded_image.h\"" >> "$OUTPUT_FILE_5"
echo "#include \"embedded_assets/${ASSETS_PREFIX_LOWER}/${ASSETS_PREFIX_LOWER}.hpp\"" >> "$OUTPUT_FILE_5"
echo "#include \"${ASSETS_PREFIX_LOWER}_config_parse_animation_name.h\"" >> "$OUTPUT_FILE_5"
echo "#include \"utils/memory.h\"" >> "$OUTPUT_FILE_5"
echo "#include <cstdint>" >> "$OUTPUT_FILE_5"
echo "#include \"utils/system_memory.h\"" >> "$OUTPUT_FILE_5"
echo "" >> "$OUTPUT_FILE_5"
echo "namespace bongocat::assets {" >> "$OUTPUT_FILE_5"
STRINGS="${ASSETS_PREFIX_UPPER}_STRINGS"
ALT_STRINGS="ALT_${ASSETS_PREFIX_UPPER}_STRINGS"
OUTPUT_FILE_5_ENTRY_TYPE="${ASSETS_PREFIX_LOWER}_animation_table_entry_t"
if [[ -n $ALT ]]; then
  # alt strings, turned into ${ALT_STRINGS} + *_OFF by scripts/build_string_blobs.sh
  echo -e "${OUTPUT_FILE_5_ALT_ANIMATIONS}" >> "$OUTPUT_FILE_5"
fi
# offsets instead of pointers: no relocations, the table stays read-only (and evictable with the config section)
echo "    struct ${OUTPUT_FILE_5_ENTRY_TYPE} {" >> "$OUTPUT_FILE_5"
echo "        // offsets into ${STRINGS}" >> "$OUTPUT_FILE_5"
echo "        uint32_t name;" >> "$OUTPUT_FILE_5"
echo "        uint32_t id;" >> "$OUTPUT_FILE_5"
echo "        uint32_t fqid;" >> "$OUTPUT_FILE_5"
echo "        uint32_t fqname;" >> "$OUTPUT_FILE_5"
echo "        int32_t anim_index;" >> "$OUTPUT_FILE_5"
echo "        config::config_animation_custom_set_t set;" >> "$OUTPUT_FILE_5"
echo "        config::config_animation_sprite_sheet_layout_t layout;" >> "$OUTPUT_FILE_5"
if [[ -n $ALT ]]; then
  echo "        // offsets into ${ALT_STRINGS}" >> "$OUTPUT_FILE_5"
  echo "        uint32_t alt_fqid;" >> "$OUTPUT_FILE_5"
  echo "        uint32_t alt_fqname;" >> "$OUTPUT_FILE_5"
fi
echo "    };" >> "$OUTPUT_FILE_5"
echo "    static constexpr ${OUTPUT_FILE_5_ENTRY_TYPE} ${ASSETS_PREFIX_LOWER}_animation_table[] CONFIG_LOCAL_STRING_SECTION = {" >> "$OUTPUT_FILE_5"
echo -e "        ${OUTPUT_FILE_5_ANIMATION_TABLE}" >> "$OUTPUT_FILE_5"
echo '    };' >> "$OUTPUT_FILE_5"
echo "    static_assert(LEN_ARRAY(${ASSETS_PREFIX_LOWER}_animation_table) == ${ASSETS_PREFIX_UPPER}_ANIM_COUNT);" >> "$OUTPUT_FILE_5"
echo >> "$OUTPUT_FILE_5"
echo "    config_custom_animation_entry_t ${GET_CONFIG_ANIMATION_NAME_FUNC_NAME}(size_t index) {" >> "$OUTPUT_FILE_5"
echo "        assert(index < ${ASSETS_PREFIX_UPPER}_ANIM_COUNT);" >> "$OUTPUT_FILE_5"
echo "        const auto& entry = ${ASSETS_PREFIX_LOWER}_animation_table[index];" >> "$OUTPUT_FILE_5"
echo "        return { ${STRINGS} + entry.name, ${STRINGS} + entry.id, ${STRINGS} + entry.fqid, ${STRINGS} + entry.fqname, entry.anim_index, entry.set, entry.layout };" >> "$OUTPUT_FILE_5"
echo '    }' >> "$OUTPUT_FILE_5"
echo >> "$OUTPUT_FILE_5"
echo "    int ${CONFIG_PARSE_FUNC_NAME}(config::config_t& config, const char *value) {" >> "$OUTPUT_FILE_5"
echo "        int ret = -1;" >> "$OUTPUT_FILE_5"
echo "        for (size_t i = 0;ret < 0 && i < ${ASSETS_PREFIX_UPPER}_ANIM_COUNT;++i) {" >> "$OUTPUT_FILE_5"
echo "            const auto& entry = ${ASSETS_PREFIX_LOWER}_animation_table[i];" >> "$OUTPUT_FILE_5"
echo "            if (strcmp(value, ${STRINGS} + entry.name) == 0 ||" >> "$OUTPUT_FILE_5"
echo "                strcmp(value, ${STRINGS} + entry.id) == 0 ||" >> "$OUTPUT_FILE_5"
echo "                strcmp(value, ${STRINGS} + entry.fqid) == 0 ||" >> "$OUTPUT_FILE_5"
if [[ -n $ALT ]]; then
  echo "                strcmp(value, ${STRINGS} + entry.fqname) == 0 ||" >> "$OUTPUT_FILE_5"
  echo "                strcmp(value, ${ALT_STRINGS} + entry.alt_fqid) == 0 ||" >> "$OUTPUT_FILE_5"
  echo "                strcmp(value, ${ALT_STRINGS} + entry.alt_fqname) == 0) {" >> "$OUTPUT_FILE_5"
else
  echo "                strcmp(value, ${STRINGS} + entry.fqname) == 0) {" >> "$OUTPUT_FILE_5"
fi
echo "                config.animation_index = entry.anim_index;" >> "$OUTPUT_FILE_5"
echo "                config.animation_custom_set = entry.set;" >> "$OUTPUT_FILE_5"
echo "                config.animation_sprite_sheet_layout = entry.layout;" >> "$OUTPUT_FILE_5"
echo '                ret = entry.anim_index;' >> "$OUTPUT_FILE_5"
echo '                break;' >> "$OUTPUT_FILE_5"
echo '            }' >> "$OUTPUT_FILE_5"
echo '        }' >> "$OUTPUT_FILE_5"
echo '        return ret;' >> "$OUTPUT_FILE_5"
echo '    }' >> "$OUTPUT_FILE_5"
echo '}' >> "$OUTPUT_FILE_5"

if [[ -n $ALT ]]; then
  # alt strings -> ALT_<SET>_STRINGS blob + offsets (the main <SET>_STRINGS blob is built in <set>.hpp, see all_generate_embedded_assets.sh)
  bash "$(dirname "$0")/build_string_blobs.sh" --blob "${ALT_STRINGS}" "$OUTPUT_FILE_5"
fi
