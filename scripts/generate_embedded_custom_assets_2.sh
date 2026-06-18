#!/bin/bash

# === Usage Check ===
if [[ $# -lt 3 ]]; then
    echo "Usage: $0 <input-dir> <og-input-dir> <output-header> <output-source>"
    echo "Example: $0 assets/pmd assets/input/pmd include/graphics/embedded_assets/pmd_images.h src/embedded_assets/pmd_images.c include/embedded_assets/pmd.hpp include/embedded_assets/pmd_sprite.h src/embedded_assets/pmd_images.c"
    exit 1
fi

# === Arguments ===
INPUT_DIR="$1"
OG_INPUT_DIR="$2"
C_HEADER_IMAGES_OUT="$3"
C_SOURCE_IMAGES_OUT="$4"
CPP_HEADER_OUT="$5"
CPP_HEADER_GET_SPRITE_OUT="$6"
CPP_SOURCE_GET_SPRITE_OUT="$7"
CPP_SOURCE_LOAD_SPRITE_OUT="$8"
CPP_SOURCE_GET_SPRITE_OUT_2="$9"
JSON_META="${10}"
START_INDEX="${11:-0}"

LAYOUT="Custom"
SET=""
LOAD_FUNC=""

# === Parse args ===
POSITIONAL_ARGS=()
while [[ $# -gt 0 ]]; do
    case $1 in
        --set) SET="$2"; shift 2 ;;
        --layout) LAYOUT="$2"; shift 2 ;;
        --json) JSON_META="$2"; shift 2 ;;
        --load-function) LOAD_FUNC="$2"; shift 2 ;;
        -*|--*)
            echo "Unknown option $1"; exit 1 ;;
        *) POSITIONAL_ARGS+=("$1"); shift ;;
    esac
done
set -- "${POSITIONAL_ARGS[@]}"

INPUT_DIR="${POSITIONAL_ARGS[0]}"
OG_INPUT_DIR="${POSITIONAL_ARGS[1]}"
C_HEADER_IMAGES_OUT="${POSITIONAL_ARGS[2]}"
C_SOURCE_IMAGES_OUT="${POSITIONAL_ARGS[3]}"
CPP_HEADER_OUT="${POSITIONAL_ARGS[4]}"
CPP_HEADER_GET_SPRITE_OUT="${POSITIONAL_ARGS[5]}"
CPP_SOURCE_GET_SPRITE_OUT="${POSITIONAL_ARGS[6]}"
CPP_SOURCE_LOAD_SPRITE_OUT="${POSITIONAL_ARGS[7]}"
CPP_SOURCE_GET_SPRITE_OUT_2="${POSITIONAL_ARGS[8]}"
JSON_META="${POSITIONAL_ARGS[9]}"
START_INDEX="${POSITIONAL_ARGS[10]:-0}"

# === Dependency check ===
if ! command -v magick &>/dev/null; then
    echo "ImageMagick v7+ (magick command) is required."
    exit 1
fi

#echo $INPUT_DIR
#echo $OG_INPUT_DIR
#echo $C_HEADER_IMAGES_OUT
#echo $C_SOURCE_IMAGES_OUT
#echo $CPP_HEADER_OUT
#echo $CPP_HEADER_GET_SPRITE_OUT
#echo $CPP_SOURCE_GET_SPRITE_OUT
#echo $CPP_SOURCE_LOAD_SPRITE_OUT
#echo $CPP_SOURCE_GET_SPRITE_OUT_2
#echo $JSON_META
#echo $SET
#echo $LAYOUT
#exit 1

if [[ -z "$INPUT_DIR" || -z "$OG_INPUT_DIR" || -z "$C_HEADER_IMAGES_OUT" || -z "$C_SOURCE_IMAGES_OUT" || -z "$CPP_HEADER_OUT" || -z "$LAYOUT" ]]; then
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
> "$C_HEADER_IMAGES_OUT"
> "$C_SOURCE_IMAGES_OUT"
> "$CPP_HEADER_OUT"
> "$CPP_HEADER_GET_SPRITE_OUT"
> "$CPP_SOURCE_GET_SPRITE_OUT"
> "$CPP_SOURCE_LOAD_SPRITE_OUT"
> "$CPP_SOURCE_GET_SPRITE_OUT_2"

# === Header file intro ===
C_HEADER_GUARD="BONGOCAT_EMBEDDED_ASSETS_CUSTOM_${ASSETS_PREFIX_UPPER}_H"
echo "#ifndef $C_HEADER_GUARD" >> "$C_HEADER_IMAGES_OUT"
echo "#define $C_HEADER_GUARD" >> "$C_HEADER_IMAGES_OUT"
echo >> "$C_HEADER_IMAGES_OUT"
echo "#include <stddef.h>" >> "$C_HEADER_IMAGES_OUT"
echo >> "$C_HEADER_IMAGES_OUT"
echo "/// @NOTE: Generated embedded assets from $INPUT_DIR" >> "$C_HEADER_IMAGES_OUT"
echo >> "$C_HEADER_IMAGES_OUT"
echo "#ifndef ASSETS_SECTION" >> "$C_SOURCE_IMAGES_OUT"
echo "#if defined(__GNUC__) || defined(__clang__)" >> "$C_SOURCE_IMAGES_OUT"
echo "  #define ASSETS_SECTION __attribute__((section(\".assets\")))" >> "$C_SOURCE_IMAGES_OUT"
echo "#elif defined(_MSC_VER)" >> "$C_SOURCE_IMAGES_OUT"
echo "  #define ASSETS_SECTION __declspec(allocate(\".assets\"))" >> "$C_SOURCE_IMAGES_OUT"
echo "  #pragma section(\".assets\", read)" >> "$C_SOURCE_IMAGES_OUT"
echo "#else" >> "$C_SOURCE_IMAGES_OUT"
echo "  #define ASSETS_SECTION" >> "$C_SOURCE_IMAGES_OUT"
echo "#endif" >> "$C_SOURCE_IMAGES_OUT"
echo "#endif" >> "$C_SOURCE_IMAGES_OUT"
echo >> "$C_HEADER_IMAGES_OUT"

CPP_HEADER_GUARD="BONGOCAT_EMBEDDED_ASSETS_CUSTOM_${ASSETS_PREFIX_UPPER}_HPP"
echo "#ifndef $CPP_HEADER_GUARD" >> "$CPP_HEADER_OUT"
echo "#define $CPP_HEADER_GUARD" >> "$CPP_HEADER_OUT"
echo >> "$CPP_HEADER_OUT"
echo "#include <cstddef>" >> "$CPP_HEADER_OUT"
echo '#include "embedded_assets/custom/custom_sprite.h"' >> "$CPP_HEADER_OUT"
echo >> "$CPP_HEADER_OUT"
echo "/// @NOTE: Generated embedded assets images data from $INPUT_DIR" >> "$CPP_HEADER_OUT"
echo >> "$CPP_HEADER_OUT"
echo "namespace bongocat::assets {" >> "$CPP_HEADER_OUT"

# === Source file intro ===
HEADER_RELATIVE_PATH="${C_HEADER_IMAGES_OUT#include/}"
echo "#include \"$HEADER_RELATIVE_PATH\"" >> "$C_SOURCE_IMAGES_OUT"
echo "#include <stddef.h>" >> "$C_SOURCE_IMAGES_OUT"
echo >> "$C_SOURCE_IMAGES_OUT"
echo "/// @NOTE: Generated embedded assets from $INPUT_DIR" >> "$C_SOURCE_IMAGES_OUT"
echo >> "$C_SOURCE_IMAGES_OUT"


GET_SPRITE_SHEET_FUNC_NAME="get_${ASSETS_PREFIX_LOWER}_sprite_sheet"
GET_SPRITE_SHEET_SETTINGS_FUNC_NAME="get_${ASSETS_PREFIX_LOWER}_sprite_sheet_settings"
CPP_HEADER_GET_SPRITE_OUT_HEADER_GUARD="BONGOCAT_EMBEDDED_ASSETS_${ASSETS_PREFIX_UPPER}_SPRITE_H"
echo "#ifndef $CPP_HEADER_GET_SPRITE_OUT_HEADER_GUARD" >> "$CPP_HEADER_GET_SPRITE_OUT"
echo "#define $CPP_HEADER_GET_SPRITE_OUT_HEADER_GUARD" >> "$CPP_HEADER_GET_SPRITE_OUT"
echo >> "$CPP_HEADER_GET_SPRITE_OUT"
echo "#include \"embedded_assets/embedded_image.h\"" >> "$CPP_HEADER_GET_SPRITE_OUT"
echo >> "$CPP_HEADER_GET_SPRITE_OUT"
echo "namespace bongocat::assets {" >> "$CPP_HEADER_GET_SPRITE_OUT"
echo "    BONGOCAT_NODISCARD extern embedded_image_t ${GET_SPRITE_SHEET_FUNC_NAME}(size_t i);" >> "$CPP_HEADER_GET_SPRITE_OUT"
echo "    BONGOCAT_NODISCARD extern custom_animation_settings_t ${GET_SPRITE_SHEET_SETTINGS_FUNC_NAME}(size_t i);" >> "$CPP_HEADER_GET_SPRITE_OUT"
echo "}" >> "$CPP_HEADER_GET_SPRITE_OUT"
echo >> "$CPP_HEADER_GET_SPRITE_OUT"
echo "#endif" >> "$CPP_HEADER_GET_SPRITE_OUT"
echo >> "$CPP_HEADER_GET_SPRITE_OUT"

LAYOUT_LOWER=$(echo "$LAYOUT" | tr '[:upper:]' '[:lower:]')
LOAD_SPRITE_SHEET_FUNC_NAME="load_${ASSETS_PREFIX_LOWER}_sprite_sheet"

LOAD_CUSTOM_ANIM_FUNC_NAME="load_${LAYOUT_LOWER}_anim"
if [[ -n "$LOAD_FUNC" ]]; then
  LOAD_CUSTOM_ANIM_FUNC_NAME=$LOAD_FUNC
fi

INIT_ANIM_FUNC_NAME="init_${ASSETS_PREFIX_LOWER}_anim"
INIT_ALL_ANIM_FUNC_NAME="init_all_${ASSETS_PREFIX_LOWER}_anim"

# === Start animation index counter ===
INDEX=$START_INDEX

CPP_SOURCE_LOAD_SPRITE_OUT_IMAGES_TABLE=""
CPP_SOURCE_LOAD_SPRITE_OUT_DIMS_TABLE=""
CPP_SOURCE_LOAD_SPRITE_OUT_PNGS_TABLE=""
CPP_SOURCE_LOAD_SPRITE_OUT_PNG_SIZES_TABLE=""
CPP_SOURCE_LOAD_SPRITE_OUT_NAMES_TABLE=""

CPP_SOURCE_GET_SPRITE_OUT_IMAGES_TABLE=""

CPP_SOURCE_GET_SPRITE_OUT_2_SETTINGS_TABLE=""
CPP_SOURCE_GET_SPRITE_OUT_SETTINGS_TABLE=""

MAX_COLS=0
# === Process all PNGs ===
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

    KEY="${BASENAME%.png}"

    COLS=$(jq -r --arg k "$KEY" '.[$k].cols // 0' "$JSON_META")
    ROWS=$(jq -r --arg k "$KEY" '.[$k].rows // 0' "$JSON_META")

    idle_frames=$(jq -r --arg k "$KEY" '.[$k].frames_idle // -1' "$JSON_META")
    boring_frames=$(jq -r --arg k "$KEY" '.[$k].frames_boring // -1' "$JSON_META")
    start_writing_frames=$(jq -r --arg k "$KEY" '.[$k].frames_start_writing // -1' "$JSON_META")
    writing_frames=$(jq -r --arg k "$KEY" '.[$k].frames_writing // -1' "$JSON_META")
    end_writing_frames=$(jq -r --arg k "$KEY" '.[$k].frames_end_writing // -1' "$JSON_META")

    happy_frames=$(jq -r --arg k "$KEY" '.[$k].frames_happy // -1' "$JSON_META")
    asleep_frames=$(jq -r --arg k "$KEY" '.[$k].frames_asleep // -1' "$JSON_META")
    sleep_frames=$(jq -r --arg k "$KEY" '.[$k].frames_sleep // -1' "$JSON_META")
    wake_up_frames=$(jq -r --arg k "$KEY" '.[$k].frames_wake_up // -1' "$JSON_META")

    start_working_frames=$(jq -r --arg k "$KEY" '.[$k].frames_start_working // -1' "$JSON_META")
    working_frames=$(jq -r --arg k "$KEY" '.[$k].frames_working // -1' "$JSON_META")
    end_working_frames=$(jq -r --arg k "$KEY" '.[$k].frames_end_working // -1' "$JSON_META")

    start_moving_frames=$(jq -r --arg k "$KEY" '.[$k].frames_start_moving // -1' "$JSON_META")
    moving_frames=$(jq -r --arg k "$KEY" '.[$k].frames_moving // -1' "$JSON_META")
    end_moving_frames=$(jq -r --arg k "$KEY" '.[$k].frames_end_moving // -1' "$JSON_META")

    start_running_frames=$(jq -r --arg k "$KEY" '.[$k].frames_start_running // -1' "$JSON_META")
    running_frames=$(jq -r --arg k "$KEY" '.[$k].frames_running // -1' "$JSON_META")
    end_running_frames=$(jq -r --arg k "$KEY" '.[$k].frames_end_running // -1' "$JSON_META")

    FRAMES_COUNT=$((COLS * ROWS))
    (( COLS > MAX_COLS )) && MAX_COLS=$COLS

    EMBED_SYMBOL="${ASSETS_PREFIX_LOWER}_${IDENTIFIER}_png"
    SIZE_SYMBOL="${EMBED_SYMBOL}_size"
    RELATIVE_PATH="../../../$INPUT_DIR/$BASENAME"

    # === Header content ===
    echo "// Name: $NAME_NO_EXT" >> "$C_HEADER_IMAGES_OUT"
    #echo "#define ${MACRO_PREFIX}_NAME \"$NAME_NO_EXT\"" >> "$C_HEADER_OUT"
    echo "extern const unsigned char $EMBED_SYMBOL[];" >> "$C_HEADER_IMAGES_OUT"
    echo "extern const size_t $SIZE_SYMBOL;" >> "$C_HEADER_IMAGES_OUT"
    echo >> "$C_HEADER_IMAGES_OUT"

    FQID="${ASSETS_PREFIX_LOWER}:${IDENTIFIER}"
    FQNAME="${ASSETS_PREFIX_LOWER}:${NAME_NO_EXT}"

    echo "    // Name: $NAME_NO_EXT" >> "$CPP_HEADER_OUT"
    echo "    inline static constexpr char ${MACRO_PREFIX}_FQID_ARR[] = \"${FQID}\";" >> "$CPP_HEADER_OUT"
    echo "    inline static constexpr const char* ${MACRO_PREFIX}_FQID = ${MACRO_PREFIX}_FQID_ARR;" >> "$CPP_HEADER_OUT"
    echo "    inline static constexpr size_t ${MACRO_PREFIX}_FQID_LEN = sizeof(${MACRO_PREFIX}_FQID_ARR)-1;" >> "$CPP_HEADER_OUT"
    echo "    inline static constexpr char ${MACRO_PREFIX}_ID_ARR[] = \"${IDENTIFIER}\";" >> "$CPP_HEADER_OUT"
    echo "    inline static constexpr const char* ${MACRO_PREFIX}_ID = ${MACRO_PREFIX}_ID_ARR;" >> "$CPP_HEADER_OUT"
    echo "    inline static constexpr size_t ${MACRO_PREFIX}_ID_LEN = sizeof(${MACRO_PREFIX}_ID)-1;" >> "$CPP_HEADER_OUT"
    echo "    inline static constexpr char ${MACRO_PREFIX}_NAME_ARR[] = \"${NAME_NO_EXT}\";" >> "$CPP_HEADER_OUT"
    echo "    inline static constexpr const char* ${MACRO_PREFIX}_NAME = ${MACRO_PREFIX}_NAME_ARR;" >> "$CPP_HEADER_OUT"
    echo "    inline static constexpr size_t ${MACRO_PREFIX}_NAME_LEN = sizeof(${MACRO_PREFIX}_NAME_ARR)-1;" >> "$CPP_HEADER_OUT"
    echo "    inline static constexpr char ${MACRO_PREFIX}_FQNAME_ARR[] = \"${FQNAME}\";" >> "$CPP_HEADER_OUT"
    echo "    inline static constexpr const char* ${MACRO_PREFIX}_FQNAME = ${MACRO_PREFIX}_FQNAME_ARR;" >> "$CPP_HEADER_OUT"
    echo "    inline static constexpr size_t ${MACRO_PREFIX}_FQNAME_LEN = sizeof(${MACRO_PREFIX}_FQNAME_ARR)-1;" >> "$CPP_HEADER_OUT"
    echo "    inline static constexpr size_t ${MACRO_PREFIX}_SPRITE_SHEET_FRAMES_COUNT = $FRAMES_COUNT;" >> "$CPP_HEADER_OUT"
    echo "    inline static constexpr size_t ${MACRO_PREFIX}_ANIM_INDEX = $INDEX;" >> "$CPP_HEADER_OUT"

    echo "    inline static constexpr custom_animation_settings_t ${MACRO_PREFIX}_SPRITE_SHEET_SETTINGS {" >> "$CPP_HEADER_OUT"
    echo "        .idle_frames = ${idle_frames}," >> "$CPP_HEADER_OUT"
    echo "        .boring_frames = ${boring_frames}," >> "$CPP_HEADER_OUT"
    echo "        .start_writing_frames = ${start_writing_frames}," >> "$CPP_HEADER_OUT"
    echo "        .writing_frames = ${writing_frames}," >> "$CPP_HEADER_OUT"
    echo "        .end_writing_frames = ${end_writing_frames}," >> "$CPP_HEADER_OUT"
    echo "        .happy_frames = ${happy_frames}," >> "$CPP_HEADER_OUT"
    echo "        .asleep_frames = ${asleep_frames}," >> "$CPP_HEADER_OUT"
    echo "        .sleep_frames = ${sleep_frames}," >> "$CPP_HEADER_OUT"
    echo "        .wake_up_frames = ${wake_up_frames}," >> "$CPP_HEADER_OUT"
    echo "        .start_working_frames = ${start_working_frames}," >> "$CPP_HEADER_OUT"
    echo "        .working_frames = ${working_frames}," >> "$CPP_HEADER_OUT"
    echo "        .end_working_frames = ${end_working_frames}," >> "$CPP_HEADER_OUT"
    echo "        .start_moving_frames = ${start_moving_frames}," >> "$CPP_HEADER_OUT"
    echo "        .moving_frames = ${moving_frames}," >> "$CPP_HEADER_OUT"
    echo "        .end_moving_frames = ${end_moving_frames}," >> "$CPP_HEADER_OUT"
    echo "        .start_running_frames = ${start_running_frames}," >> "$CPP_HEADER_OUT"
    echo "        .running_frames = ${running_frames}," >> "$CPP_HEADER_OUT"
    echo "        .end_running_frames = ${end_running_frames}," >> "$CPP_HEADER_OUT"
    echo "    };" >> "$CPP_HEADER_OUT"

    echo "    inline static constexpr int ${MACRO_PREFIX}_SPRITE_SHEET_ROWS = $ROWS;" >> "$CPP_HEADER_OUT"
    echo "    inline static constexpr int ${MACRO_PREFIX}_SPRITE_SHEET_MAX_COLS = $COLS;" >> "$CPP_HEADER_OUT"

    echo >> "$CPP_HEADER_OUT"

    # === Source content ===
    echo "// Name: $NAME_NO_EXT" >> "$C_SOURCE_IMAGES_OUT"
    echo "const unsigned char $EMBED_SYMBOL[] ASSETS_SECTION = {" >> "$C_SOURCE_IMAGES_OUT"
    echo "#embed \"$RELATIVE_PATH\"" >> "$C_SOURCE_IMAGES_OUT"
    echo "};" >> "$C_SOURCE_IMAGES_OUT"
    echo "const size_t $SIZE_SYMBOL ASSETS_SECTION = sizeof($EMBED_SYMBOL);" >> "$C_SOURCE_IMAGES_OUT"
    echo >> "$C_SOURCE_IMAGES_OUT"
    echo >> "$C_SOURCE_IMAGES_OUT" # extra EOL

    #echo "            case ${MACRO_PREFIX}_ANIM_INDEX: return {$EMBED_SYMBOL, $SIZE_SYMBOL, \"${IDENTIFIER}\"};" >> "$CPP_SOURCE_GET_SPRITE_OUT"
    CPP_SOURCE_GET_SPRITE_OUT_IMAGES_TABLE="${CPP_SOURCE_GET_SPRITE_OUT_IMAGES_TABLE}{${EMBED_SYMBOL}, ${SIZE_SYMBOL}, \"${IDENTIFIER}\"}, \n        "

    #echo "            case ${MACRO_PREFIX}_ANIM_INDEX: return ${MACRO_PREFIX}_SPRITE_SHEET_SETTINGS;" >> "$CPP_SOURCE_GET_SPRITE_OUT_2"
    CPP_SOURCE_GET_SPRITE_OUT_2_SETTINGS_TABLE="${CPP_SOURCE_GET_SPRITE_OUT_2_SETTINGS_TABLE}assets::${MACRO_PREFIX}_SPRITE_SHEET_SETTINGS, \n        "

    #echo "            case ${MACRO_PREFIX}_ANIM_INDEX: return ${LOAD_CUSTOM_ANIM_FUNC_NAME}(ctx, ${GET_SPRITE_SHEET_FUNC_NAME}(${MACRO_PREFIX}_ANIM_INDEX), ${GET_SPRITE_SHEET_SETTINGS_FUNC_NAME}(${MACRO_PREFIX}_ANIM_INDEX));" >> "$CPP_SOURCE_LOAD_SPRITE_OUT"
    CPP_SOURCE_GET_SPRITE_OUT_SETTINGS_TABLE="${CPP_SOURCE_GET_SPRITE_OUT_SETTINGS_TABLE}assets::${MACRO_PREFIX}_SPRITE_SHEET_SETTINGS, \n        "

    CPP_SOURCE_LOAD_SPRITE_OUT_IMAGES_TABLE="${CPP_SOURCE_LOAD_SPRITE_OUT_IMAGES_TABLE}\n// Name: $NAME_NO_EXT\n"
    CPP_SOURCE_LOAD_SPRITE_OUT_IMAGES_TABLE="${CPP_SOURCE_LOAD_SPRITE_OUT_IMAGES_TABLE}const unsigned char $EMBED_SYMBOL[] = {\n"
    CPP_SOURCE_LOAD_SPRITE_OUT_IMAGES_TABLE="${CPP_SOURCE_LOAD_SPRITE_OUT_IMAGES_TABLE}#embed \"$RELATIVE_PATH\"\n"
    CPP_SOURCE_LOAD_SPRITE_OUT_IMAGES_TABLE="${CPP_SOURCE_LOAD_SPRITE_OUT_IMAGES_TABLE}};\n"
    CPP_SOURCE_LOAD_SPRITE_OUT_IMAGES_TABLE="${CPP_SOURCE_LOAD_SPRITE_OUT_IMAGES_TABLE}const size_t $SIZE_SYMBOL = sizeof($EMBED_SYMBOL);\n"

    CPP_SOURCE_LOAD_SPRITE_OUT_DIMS_TABLE="${CPP_SOURCE_LOAD_SPRITE_OUT_DIMS_TABLE}{assets::${MACRO_PREFIX}_SPRITE_SHEET_COLS, assets::${MACRO_PREFIX}_SPRITE_SHEET_ROWS}, \n        "
    CPP_SOURCE_LOAD_SPRITE_OUT_PNGS_TABLE="${CPP_SOURCE_LOAD_SPRITE_OUT_PNGS_TABLE}${EMBED_SYMBOL}, \n        "
    CPP_SOURCE_LOAD_SPRITE_OUT_PNG_SIZES_TABLE="${CPP_SOURCE_LOAD_SPRITE_OUT_PNG_SIZES_TABLE}${SIZE_SYMBOL}, \n        "
    CPP_SOURCE_LOAD_SPRITE_OUT_NAMES_TABLE="${CPP_SOURCE_LOAD_SPRITE_OUT_NAMES_TABLE}\"${IDENTIFIER}\", \n        "

    echo "Add $IDENTIFIER"

    ((INDEX++))
done

echo "$INDEX done"


echo >> "$C_HEADER_IMAGES_OUT"
echo "#endif // $C_HEADER_GUARD" >> "$C_HEADER_IMAGES_OUT"
echo >> "$C_HEADER_IMAGES_OUT"

echo "    inline static constexpr size_t ${ASSETS_PREFIX_UPPER}_ANIM_COUNT = $((INDEX-START_INDEX));" >> "$CPP_HEADER_OUT"
echo '}' >> "$CPP_HEADER_OUT"
echo >> "$CPP_HEADER_OUT"
echo "#endif // $CPP_HEADER_GUARD" >> "$CPP_HEADER_OUT"
echo >> "$CPP_HEADER_OUT"

echo "#include \"embedded_assets/embedded_image.h\"" >> "$CPP_SOURCE_GET_SPRITE_OUT"
echo "#include \"embedded_assets/${ASSETS_PREFIX_LOWER}/${ASSETS_PREFIX_LOWER}.hpp\"" >> "$CPP_SOURCE_GET_SPRITE_OUT"
echo "#include \"embedded_assets/${ASSETS_PREFIX_LOWER}/${ASSETS_PREFIX_LOWER}_images.h\"" >> "$CPP_SOURCE_GET_SPRITE_OUT"
echo "#include \"embedded_assets/${ASSETS_PREFIX_LOWER}/${ASSETS_PREFIX_LOWER}_sprite.h\"" >> "$CPP_SOURCE_GET_SPRITE_OUT"
echo >> "$CPP_SOURCE_GET_SPRITE_OUT"
echo "namespace bongocat::assets {" >> "$CPP_SOURCE_GET_SPRITE_OUT"
#echo -e "${CPP_SOURCE_LOAD_SPRITE_OUT_IMAGES_TABLE}" >> "$CPP_SOURCE_GET_SPRITE_OUT"
echo "    static const embedded_image_t ${ASSETS_PREFIX_LOWER}_images_table[] = {" >> "$CPP_SOURCE_GET_SPRITE_OUT"
echo -e "        ${CPP_SOURCE_GET_SPRITE_OUT_IMAGES_TABLE}" >> "$CPP_SOURCE_GET_SPRITE_OUT"
echo "    };" >> "$CPP_SOURCE_GET_SPRITE_OUT"
echo "    embedded_image_t ${GET_SPRITE_SHEET_FUNC_NAME}(size_t index) {" >> "$CPP_SOURCE_GET_SPRITE_OUT"
echo "        assert(LEN_ARRAY(${ASSETS_PREFIX_LOWER}_images_table) == ${ASSETS_PREFIX_UPPER}_ANIM_COUNT);" >> "$CPP_SOURCE_GET_SPRITE_OUT"
echo "        assert(index < ${ASSETS_PREFIX_UPPER}_ANIM_COUNT);" >> "$CPP_SOURCE_GET_SPRITE_OUT"
echo "        return ${ASSETS_PREFIX_LOWER}_images_table[index];" >> "$CPP_SOURCE_GET_SPRITE_OUT"
echo '    }' >> "$CPP_SOURCE_GET_SPRITE_OUT"
echo '}' >> "$CPP_SOURCE_GET_SPRITE_OUT"
echo >> "$CPP_SOURCE_GET_SPRITE_OUT"


echo "#include \"embedded_assets/embedded_image.h\"" >> "$CPP_SOURCE_GET_SPRITE_OUT_2"
echo "#include \"embedded_assets/${ASSETS_PREFIX_LOWER}/${ASSETS_PREFIX_LOWER}.hpp\"" >> "$CPP_SOURCE_GET_SPRITE_OUT_2"
echo "#include \"embedded_assets/${ASSETS_PREFIX_LOWER}/${ASSETS_PREFIX_LOWER}_images.h\"" >> "$CPP_SOURCE_GET_SPRITE_OUT_2"
echo "#include \"embedded_assets/${ASSETS_PREFIX_LOWER}/${ASSETS_PREFIX_LOWER}_sprite.h\"" >> "$CPP_SOURCE_GET_SPRITE_OUT_2"
echo >> "$CPP_SOURCE_GET_SPRITE_OUT_2"
echo "namespace bongocat::assets {" >> "$CPP_SOURCE_GET_SPRITE_OUT_2"
echo "    static const custom_animation_settings_t ${ASSETS_PREFIX_LOWER}_settings_table[] = {" >> "$CPP_SOURCE_GET_SPRITE_OUT_2"
echo -e "        ${CPP_SOURCE_GET_SPRITE_OUT_2_SETTINGS_TABLE}" >> "$CPP_SOURCE_GET_SPRITE_OUT_2"
echo "    };" >> "$CPP_SOURCE_GET_SPRITE_OUT_2"
echo "    custom_animation_settings_t ${GET_SPRITE_SHEET_SETTINGS_FUNC_NAME}(size_t index) {" >> "$CPP_SOURCE_GET_SPRITE_OUT_2"
echo "        assert(LEN_ARRAY(${ASSETS_PREFIX_LOWER}_settings_table) == ${ASSETS_PREFIX_UPPER}_ANIM_COUNT);" >> "$CPP_SOURCE_GET_SPRITE_OUT_2"
echo "        assert(index < ${ASSETS_PREFIX_UPPER}_ANIM_COUNT);" >> "$CPP_SOURCE_GET_SPRITE_OUT_2"
echo "        return ${ASSETS_PREFIX_LOWER}_settings_table[index];" >> "$CPP_SOURCE_GET_SPRITE_OUT_2"
echo '    }' >> "$CPP_SOURCE_GET_SPRITE_OUT_2"
echo '}' >> "$CPP_SOURCE_GET_SPRITE_OUT_2"
echo >> "$CPP_SOURCE_GET_SPRITE_OUT_2"

echo "#include \"core/bongocat.h\"" >> "$CPP_SOURCE_LOAD_SPRITE_OUT"
echo "#include \"graphics/animation_context.h\"" >> "$CPP_SOURCE_LOAD_SPRITE_OUT"
echo "#include \"graphics/sprite_sheet.h\"" >> "$CPP_SOURCE_LOAD_SPRITE_OUT"
echo "#include \"image_loader/${LAYOUT_LOWER}/load_${LAYOUT_LOWER}.h\"" >> "$CPP_SOURCE_LOAD_SPRITE_OUT"
echo "#include \"embedded_assets/${ASSETS_PREFIX_LOWER}/${ASSETS_PREFIX_LOWER}.hpp\"" >> "$CPP_SOURCE_LOAD_SPRITE_OUT"
echo "#include \"embedded_assets/embedded_image.h\"" >> "$CPP_SOURCE_LOAD_SPRITE_OUT"
echo "#include \"embedded_assets/${ASSETS_PREFIX_LOWER}/${ASSETS_PREFIX_LOWER}_images.h\"" >> "$CPP_SOURCE_LOAD_SPRITE_OUT"
echo "#include \"embedded_assets/${ASSETS_PREFIX_LOWER}/${ASSETS_PREFIX_LOWER}_sprite.h\"" >> "$CPP_SOURCE_LOAD_SPRITE_OUT"
echo "#include \"image_loader/${ASSETS_PREFIX_LOWER}/load_images_${ASSETS_PREFIX_LOWER}.h\"" >> "$CPP_SOURCE_LOAD_SPRITE_OUT"
echo >> "$CPP_SOURCE_LOAD_SPRITE_OUT"
echo "namespace bongocat::animation {" >> "$CPP_SOURCE_LOAD_SPRITE_OUT"
echo "    static const assets::custom_animation_settings_t ${ASSETS_PREFIX_LOWER}_settings_table[] = {" >> "$CPP_SOURCE_LOAD_SPRITE_OUT"
echo -e "        ${CPP_SOURCE_GET_SPRITE_OUT_2_SETTINGS_TABLE}" >> "$CPP_SOURCE_LOAD_SPRITE_OUT"
echo "    };" >> "$CPP_SOURCE_LOAD_SPRITE_OUT"
#echo "    static constexpr assets::embedded_sprite_sheet_dims_t ${ASSETS_PREFIX_LOWER}_dims_table[] = {" >> "$CPP_SOURCE_LOAD_SPRITE_OUT"
#echo -e "        ${CPP_SOURCE_LOAD_SPRITE_OUT_DIMS_TABLE}" >> "$CPP_SOURCE_LOAD_SPRITE_OUT"
#echo "    };" >> "$CPP_SOURCE_LOAD_SPRITE_OUT"
echo "    static const unsigned char* ${ASSETS_PREFIX_LOWER}_pngs_table[] = {" >> "$CPP_SOURCE_LOAD_SPRITE_OUT"
echo -e "        ${CPP_SOURCE_LOAD_SPRITE_OUT_PNGS_TABLE}" >> "$CPP_SOURCE_LOAD_SPRITE_OUT"
echo "    };" >> "$CPP_SOURCE_LOAD_SPRITE_OUT"
echo "    static const size_t ${ASSETS_PREFIX_LOWER}_png_sizes_table[] = {" >> "$CPP_SOURCE_LOAD_SPRITE_OUT"
echo -e "        ${CPP_SOURCE_LOAD_SPRITE_OUT_PNG_SIZES_TABLE}" >> "$CPP_SOURCE_LOAD_SPRITE_OUT"
echo "    };" >> "$CPP_SOURCE_LOAD_SPRITE_OUT"
echo "    static const char* ${ASSETS_PREFIX_LOWER}_names_table[] = {" >> "$CPP_SOURCE_LOAD_SPRITE_OUT"
echo -e "        ${CPP_SOURCE_LOAD_SPRITE_OUT_NAMES_TABLE}" >> "$CPP_SOURCE_LOAD_SPRITE_OUT"
echo "    };" >> "$CPP_SOURCE_LOAD_SPRITE_OUT"
echo "    created_result_t<${LAYOUT_LOWER}_sprite_sheet_t> ${LOAD_SPRITE_SHEET_FUNC_NAME}(const animation_thread_context_t& ctx, size_t index) {" >> "$CPP_SOURCE_LOAD_SPRITE_OUT"
echo "        using namespace assets;" >> "$CPP_SOURCE_LOAD_SPRITE_OUT"
echo "        assert(LEN_ARRAY(${ASSETS_PREFIX_LOWER}_settings_table) == ${ASSETS_PREFIX_UPPER}_ANIM_COUNT);" >> "$CPP_SOURCE_LOAD_SPRITE_OUT"
echo "        assert(LEN_ARRAY(${ASSETS_PREFIX_LOWER}_pngs_table) == ${ASSETS_PREFIX_UPPER}_ANIM_COUNT);" >> "$CPP_SOURCE_LOAD_SPRITE_OUT"
echo "        assert(LEN_ARRAY(${ASSETS_PREFIX_LOWER}_png_sizes_table) == ${ASSETS_PREFIX_UPPER}_ANIM_COUNT);" >> "$CPP_SOURCE_LOAD_SPRITE_OUT"
echo "        assert(LEN_ARRAY(${ASSETS_PREFIX_LOWER}_names_table) == ${ASSETS_PREFIX_UPPER}_ANIM_COUNT);" >> "$CPP_SOURCE_LOAD_SPRITE_OUT"
echo "        auto result = ${LOAD_CUSTOM_ANIM_FUNC_NAME}(ctx, {${ASSETS_PREFIX_LOWER}_pngs_table[index], ${ASSETS_PREFIX_LOWER}_png_sizes_table[index], ${ASSETS_PREFIX_LOWER}_names_table[index]}, ${ASSETS_PREFIX_LOWER}_settings_table[index]);" >> "$CPP_SOURCE_LOAD_SPRITE_OUT"
echo "        platform::details::asset_unload(${ASSETS_PREFIX_LOWER}_pngs_table[index], ${ASSETS_PREFIX_LOWER}_png_sizes_table[index]);" >> "$CPP_SOURCE_LOAD_SPRITE_OUT"
echo "        return result;" >> "$CPP_SOURCE_LOAD_SPRITE_OUT"
echo '    }' >> "$CPP_SOURCE_LOAD_SPRITE_OUT"
echo "    void ${INIT_ALL_ANIM_FUNC_NAME}(animation_thread_context_t& ctx) {" >> "$CPP_SOURCE_LOAD_SPRITE_OUT"
echo "        using namespace assets;" >> "$CPP_SOURCE_LOAD_SPRITE_OUT"
echo "        for (size_t i = 0;i < ${ASSETS_PREFIX_UPPER}_ANIM_COUNT;++i) {" >> "$CPP_SOURCE_LOAD_SPRITE_OUT"
#echo "            assert(LEN_ARRAY(${ASSETS_PREFIX_LOWER}_dims_table) == ${ASSETS_PREFIX_UPPER}_ANIM_COUNT);" >> "$CPP_SOURCE_LOAD_SPRITE_OUT"
#echo "            assert(LEN_ARRAY(${ASSETS_PREFIX_LOWER}_pngs_table) == ${ASSETS_PREFIX_UPPER}_ANIM_COUNT);" >> "$CPP_SOURCE_LOAD_SPRITE_OUT"
#echo "            assert(LEN_ARRAY(${ASSETS_PREFIX_LOWER}_png_sizes_table) == ${ASSETS_PREFIX_UPPER}_ANIM_COUNT);" >> "$CPP_SOURCE_LOAD_SPRITE_OUT"
#echo "            assert(LEN_ARRAY(${ASSETS_PREFIX_LOWER}_names_table) == ${ASSETS_PREFIX_UPPER}_ANIM_COUNT);" >> "$CPP_SOURCE_LOAD_SPRITE_OUT"
#echo "            assert(index < ${ASSETS_PREFIX_UPPER}_ANIM_COUNT);" >> "$CPP_SOURCE_LOAD_SPRITE_OUT"
#echo "            assert(LEN_ARRAY(${ASSETS_PREFIX_LOWER}_pngs_table) <= INT32_MAX);" >> "$CPP_SOURCE_LOAD_SPRITE_OUT"
#echo "            assert(index < INT32_MAX);" >> "$CPP_SOURCE_LOAD_SPRITE_OUT"
echo "            ${INIT_ANIM_FUNC_NAME}(ctx, i, {${ASSETS_PREFIX_LOWER}_pngs_table[i], ${ASSETS_PREFIX_LOWER}_png_sizes_table[i], ${ASSETS_PREFIX_LOWER}_names_table[i]}, ${ASSETS_PREFIX_LOWER}_settings_table[i]);" >> "$CPP_SOURCE_LOAD_SPRITE_OUT"
echo '        }' >> "$CPP_SOURCE_LOAD_SPRITE_OUT"
echo "        platform::details::asset_unload_all(${ASSETS_PREFIX_LOWER}_pngs_table, ${ASSETS_PREFIX_LOWER}_png_sizes_table, ${ASSETS_PREFIX_UPPER}_ANIM_COUNT);" >> "$CPP_SOURCE_LOAD_SPRITE_OUT"
echo '    }' >> "$CPP_SOURCE_LOAD_SPRITE_OUT"
echo '}' >> "$CPP_SOURCE_LOAD_SPRITE_OUT"
echo >> "$CPP_SOURCE_LOAD_SPRITE_OUT"