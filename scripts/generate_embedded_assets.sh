#!/bin/bash

# === Usage Check ===
if [[ $# -lt 3 ]]; then
    echo "Usage: $0 <input-dir> <og-input-dir> <output-header> <output-source>"
    echo "Example: $0 assets/dm20 assets/input/dm20 include/graphics/embedded_assets/dm20_images.h src/embedded_assets/dm20_images.c include/embedded_assets/dm20.hpp include/embedded_assets/dm20_sprite.h src/embedded_assets/dm20_images.c"
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
START_INDEX="$9"

FRAME_SIZE=""
COLS=""
ROWS=""

# === Parse args ===
POSITIONAL_ARGS=()
while [[ $# -gt 0 ]]; do
    case $1 in
        --frame-size) FRAME_SIZE="$2"; shift 2 ;;
        --cols) COLS="$2"; shift 2 ;;
        --rows) ROWS="$2"; shift 2 ;;
        -*|--*)
            echo "Unknown option $1"; exit 1 ;;
        *) POSITIONAL_ARGS+=("$1"); shift ;;
    esac
done
set -- "${POSITIONAL_ARGS[@]}"

INPUT="${POSITIONAL_ARGS[0]}"
OG_INPUT_DIR="${POSITIONAL_ARGS[1]}"
C_HEADER_IMAGES_OUT="${POSITIONAL_ARGS[2]}"
C_SOURCE_IMAGES_OUT="${POSITIONAL_ARGS[3]}"
CPP_HEADER_OUT="${POSITIONAL_ARGS[4]}"
CPP_HEADER_GET_SPRITE_OUT="${POSITIONAL_ARGS[5]}"
CPP_SOURCE_GET_SPRITE_OUT="${POSITIONAL_ARGS[6]}"
CPP_SOURCE_LOAD_SPRITE_OUT="${POSITIONAL_ARGS[7]}"
START_INDEX="${POSITIONAL_ARGS[8]:-0}"

# === Dependency check ===
if ! command -v magick &>/dev/null; then
    echo "ImageMagick v7+ (magick command) is required."
    exit 1
fi

if [[ -z "$INPUT" || -z "$OG_INPUT_DIR" || -z "$C_HEADER_IMAGES_OUT" || -z "$C_SOURCE_IMAGES_OUT" || -z "$CPP_HEADER_OUT" ]]; then
    echo "Usage: $0 <input-dir> <og-input-dir> <output-header> <output-source>"
    exit 1
fi

#echo $INPUT
#echo $OG_INPUT_DIR
#echo $C_HEADER_IMAGES_OUT
#echo $C_SOURCE_IMAGES_OUT
#echo $CPP_HEADER_OUT
#echo $FRAME_SIZE
#exit 1

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

# === Header file intro ===
C_HEADER_GUARD="BONGOCAT_EMBEDDED_ASSETS_${ASSETS_PREFIX_UPPER}_H"
echo "#ifndef $C_HEADER_GUARD" >> "$C_HEADER_IMAGES_OUT"
echo "#define $C_HEADER_GUARD" >> "$C_HEADER_IMAGES_OUT"
echo >> "$C_HEADER_IMAGES_OUT"
echo "#include <stddef.h>" >> "$C_HEADER_IMAGES_OUT"
echo >> "$C_HEADER_IMAGES_OUT"
echo "/// @NOTE: Generated embedded assets from $INPUT_DIR" >> "$C_HEADER_IMAGES_OUT"
echo >> "$C_HEADER_IMAGES_OUT"

CPP_HEADER_GUARD="BONGOCAT_EMBEDDED_ASSETS_${ASSETS_PREFIX_UPPER}_HPP"
echo "#ifndef $CPP_HEADER_GUARD" >> "$CPP_HEADER_OUT"
echo "#define $CPP_HEADER_GUARD" >> "$CPP_HEADER_OUT"
echo >> "$CPP_HEADER_OUT"
echo "#include <cstddef>" >> "$CPP_HEADER_OUT"
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
CPP_HEADER_GET_SPRITE_OUT_HEADER_GUARD="BONGOCAT_EMBEDDED_ASSETS_${ASSETS_PREFIX_UPPER}_SPRITE_H"
echo "#ifndef $CPP_HEADER_GET_SPRITE_OUT_HEADER_GUARD" >> "$CPP_HEADER_GET_SPRITE_OUT"
echo "#define $CPP_HEADER_GET_SPRITE_OUT_HEADER_GUARD" >> "$CPP_HEADER_GET_SPRITE_OUT"
echo >> "$CPP_HEADER_GET_SPRITE_OUT"
echo "#include \"embedded_assets/embedded_image.h\"" >> "$CPP_HEADER_GET_SPRITE_OUT"
echo >> "$CPP_HEADER_GET_SPRITE_OUT"
echo "namespace bongocat::assets {" >> "$CPP_HEADER_GET_SPRITE_OUT"
echo "    [[nodiscard]] extern embedded_image_t ${GET_SPRITE_SHEET_FUNC_NAME}(size_t i);" >> "$CPP_HEADER_GET_SPRITE_OUT"
echo "}" >> "$CPP_HEADER_GET_SPRITE_OUT"
echo >> "$CPP_HEADER_GET_SPRITE_OUT"
echo "#endif" >> "$CPP_HEADER_GET_SPRITE_OUT"
echo >> "$CPP_HEADER_GET_SPRITE_OUT"

echo "#include \"embedded_assets/embedded_image.h\"" >> "$CPP_SOURCE_GET_SPRITE_OUT"
echo "#include \"embedded_assets/${ASSETS_PREFIX_LOWER}/${ASSETS_PREFIX_LOWER}.hpp\"" >> "$CPP_SOURCE_GET_SPRITE_OUT"
echo "#include \"embedded_assets/${ASSETS_PREFIX_LOWER}/${ASSETS_PREFIX_LOWER}_images.h\"" >> "$CPP_SOURCE_GET_SPRITE_OUT"
echo "#include \"embedded_assets/${ASSETS_PREFIX_LOWER}/${ASSETS_PREFIX_LOWER}_sprite.h\"" >> "$CPP_SOURCE_GET_SPRITE_OUT"
echo >> "$CPP_SOURCE_GET_SPRITE_OUT"
echo "namespace bongocat::assets {" >> "$CPP_SOURCE_GET_SPRITE_OUT"
echo "    embedded_image_t ${GET_SPRITE_SHEET_FUNC_NAME}(size_t i) {" >> "$CPP_SOURCE_GET_SPRITE_OUT"
echo "    using namespace assets;" >> "$CPP_SOURCE_GET_SPRITE_OUT"
echo "    switch(i) {" >> "$CPP_SOURCE_GET_SPRITE_OUT"


LOAD_DM_ANIM_FUNC_NAME="load_dm_anim"
LOAD_SPRITE_SHEET_FUNC_NAME="load_${ASSETS_PREFIX_LOWER}_sprite_sheet"
echo "#include \"core/bongocat.h\"" >> "$CPP_SOURCE_LOAD_SPRITE_OUT"
echo "#include \"graphics/animation_context.h\"" >> "$CPP_SOURCE_LOAD_SPRITE_OUT"
echo "#include \"graphics/sprite_sheet.h\"" >> "$CPP_SOURCE_LOAD_SPRITE_OUT"
echo "#include \"image_loader/base_dm/load_dm.h\"" >> "$CPP_SOURCE_LOAD_SPRITE_OUT"
echo "#include \"embedded_assets/${ASSETS_PREFIX_LOWER}/${ASSETS_PREFIX_LOWER}.hpp\"" >> "$CPP_SOURCE_LOAD_SPRITE_OUT"
echo "#include \"embedded_assets/embedded_image.h\"" >> "$CPP_SOURCE_LOAD_SPRITE_OUT"
echo "#include \"embedded_assets/${ASSETS_PREFIX_LOWER}/${ASSETS_PREFIX_LOWER}_sprite.h\"" >> "$CPP_SOURCE_LOAD_SPRITE_OUT"
echo "#include \"image_loader/${ASSETS_PREFIX_LOWER}/load_images_${ASSETS_PREFIX_LOWER}.h\"" >> "$CPP_SOURCE_LOAD_SPRITE_OUT"
echo >> "$CPP_SOURCE_LOAD_SPRITE_OUT"
echo "namespace bongocat::animation {" >> "$CPP_SOURCE_LOAD_SPRITE_OUT"
echo "    created_result_t<dm_animation_t> ${LOAD_SPRITE_SHEET_FUNC_NAME}(const animation_context_t& ctx, int index) {" >> "$CPP_SOURCE_LOAD_SPRITE_OUT"
echo "        using namespace assets;" >> "$CPP_SOURCE_LOAD_SPRITE_OUT"
echo "        switch(index) {" >> "$CPP_SOURCE_LOAD_SPRITE_OUT"

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
    fi

    NAME_NO_EXT="${BASENAME%.png}"
    NAME_CLEAN=$(echo "$NAME_NO_EXT" | sed "s/['().:]//g")
    NAME_CLEAN=$(echo "$NAME_CLEAN" | sed 's/[^a-zA-Z0-9]/_/g')
    NAME_CLEAN=$(echo "$NAME_CLEAN" | sed 's/_\+/_/g')
    IDENTIFIER=$(echo "$NAME_CLEAN" | tr '[:upper:]' '[:lower:]')
    MACRO_PREFIX=$(echo "${ASSETS_PREFIX_UPPER}_${IDENTIFIER}" | tr '[:lower:]' '[:upper:]')

    EMBED_SYMBOL="${ASSETS_PREFIX_LOWER}_${IDENTIFIER}_png"
    SIZE_SYMBOL="${EMBED_SYMBOL}_size"
    RELATIVE_PATH="../../../$INPUT_DIR/$BASENAME"

    # === Header content ===
    echo "// Name: $NAME_NO_EXT" >> "$C_HEADER_IMAGES_OUT"
    #echo "#define ${MACRO_PREFIX}_NAME \"$NAME_NO_EXT\"" >> "$C_HEADER_OUT"
    echo "extern const unsigned char $EMBED_SYMBOL[];" >> "$C_HEADER_IMAGES_OUT"
    echo "extern const size_t $SIZE_SYMBOL;" >> "$C_HEADER_IMAGES_OUT"
    #echo "#define ${MACRO_PREFIX}_SPRITE_SHEET_COLS $COLS" >> "$C_HEADER_OUT"
    #echo "#define ${MACRO_PREFIX}_SPRITE_SHEET_ROWS $ROWS" >> "$C_HEADER_OUT"
    #echo "#define ${MACRO_PREFIX}_SPRITE_SHEET_FRAMES_COUNT $FRAMES_COUNT" >> "$C_HEADER_OUT"
    #echo "#define ${MACRO_PREFIX}_ANIM_INDEX $INDEX" >> "$C_HEADER_OUT"
    echo >> "$C_HEADER_IMAGES_OUT"


    echo "    // Name: $NAME_NO_EXT" >> "$CPP_HEADER_OUT"
    echo "    inline static constexpr const char* ${MACRO_PREFIX}_NAME = \"$NAME_NO_EXT\";" >> "$CPP_HEADER_OUT"
    echo "    inline static constexpr int ${MACRO_PREFIX}_SPRITE_SHEET_COLS = $COLS;" >> "$CPP_HEADER_OUT"
    echo "    inline static constexpr int ${MACRO_PREFIX}_SPRITE_SHEET_ROWS = $ROWS;" >> "$CPP_HEADER_OUT"
    echo "    inline static constexpr size_t ${MACRO_PREFIX}_SPRITE_SHEET_FRAMES_COUNT = $FRAMES_COUNT;" >> "$CPP_HEADER_OUT"
    echo "    inline static constexpr size_t ${MACRO_PREFIX}_ANIM_INDEX = $INDEX;" >> "$CPP_HEADER_OUT"
    echo >> "$CPP_HEADER_OUT"

    # === Source content ===
    echo "// Name: $NAME_NO_EXT" >> "$C_SOURCE_IMAGES_OUT"
    echo "const unsigned char $EMBED_SYMBOL[] = {" >> "$C_SOURCE_IMAGES_OUT"
    echo "#embed \"$RELATIVE_PATH\"" >> "$C_SOURCE_IMAGES_OUT"
    echo "};" >> "$C_SOURCE_IMAGES_OUT"
    echo "const size_t $SIZE_SYMBOL = sizeof($EMBED_SYMBOL);" >> "$C_SOURCE_IMAGES_OUT"
    echo >> "$C_SOURCE_IMAGES_OUT"
    echo >> "$C_SOURCE_IMAGES_OUT" # extra EOL

    echo "            case ${MACRO_PREFIX}_ANIM_INDEX: return { $EMBED_SYMBOL, $SIZE_SYMBOL, \"${IDENTIFIER}\"};" >> "$CPP_SOURCE_GET_SPRITE_OUT"

    echo "            case ${MACRO_PREFIX}_ANIM_INDEX: return ${LOAD_DM_ANIM_FUNC_NAME}(ctx, ${MACRO_PREFIX}_ANIM_INDEX, ${GET_SPRITE_SHEET_FUNC_NAME}(${MACRO_PREFIX}_ANIM_INDEX), ${MACRO_PREFIX}_SPRITE_SHEET_COLS, ${MACRO_PREFIX}_SPRITE_SHEET_ROWS);" >> "$CPP_SOURCE_LOAD_SPRITE_OUT"

    ((INDEX++))
done

echo >> "$C_HEADER_IMAGES_OUT"
echo "#endif // $C_HEADER_GUARD" >> "$C_HEADER_IMAGES_OUT"
echo >> "$C_HEADER_IMAGES_OUT"

echo "    inline static constexpr size_t ${ASSETS_PREFIX_UPPER}_ANIM_COUNT = $((INDEX-START_INDEX+1));" >> "$CPP_HEADER_OUT"
echo "}" >> "$CPP_HEADER_OUT"
echo >> "$CPP_HEADER_OUT"
echo "#endif // $CPP_HEADER_GUARD" >> "$CPP_HEADER_OUT"
echo >> "$CPP_HEADER_OUT"

echo "            default: return { nullptr, 0, "" };" >> "$CPP_SOURCE_GET_SPRITE_OUT"
echo "        }" >> "$CPP_SOURCE_GET_SPRITE_OUT"
echo "        return { nullptr, 0, "" };" >> "$CPP_SOURCE_GET_SPRITE_OUT"
echo "    }" >> "$CPP_SOURCE_GET_SPRITE_OUT"
echo "}" >> "$CPP_SOURCE_GET_SPRITE_OUT"
echo >> "$CPP_SOURCE_GET_SPRITE_OUT"

echo "            default: return bongocat_error_t::BONGOCAT_ERROR_INVALID_PARAM;" >> "$CPP_SOURCE_LOAD_SPRITE_OUT"
echo "        }" >> "$CPP_SOURCE_LOAD_SPRITE_OUT"
echo "        return bongocat_error_t::BONGOCAT_ERROR_INVALID_PARAM;" >> "$CPP_SOURCE_LOAD_SPRITE_OUT"
echo "    }" >> "$CPP_SOURCE_LOAD_SPRITE_OUT"
echo "}" >> "$CPP_SOURCE_LOAD_SPRITE_OUT"
echo >> "$CPP_SOURCE_LOAD_SPRITE_OUT"