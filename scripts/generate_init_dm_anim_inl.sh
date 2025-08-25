#!/bin/bash

OUTPUT_DIR="$1"
HEADER_FILE="$2"
PREFIX="$3"

# Either (COLS and ROWS) or --frame-size must be provided
if [[ -z "$OUTPUT_DIR" || -z "$HEADER_FILE" || -z $PREFIX ]]; then
    echo "Usage: $0 <input-dir> <og-input-dir> <output-header> <output-source>"
    exit 1
fi

PREFIX_LOWER=$(echo "$PREFIX" | tr '[:upper:]' '[:lower:]')
PREFIX_UPPER=$(echo "$PREFIX" | tr '[:lower:]' '[:upper:]')


OUTPUT_FILE_1="${OUTPUT_DIR}/${PREFIX_LOWER}_init_dm_anim.c.inl"
OUTPUT_FILE_2="${OUTPUT_DIR}/${PREFIX_LOWER}_init_dm_embedded_images.c.inl"
OUTPUT_FILE_3="${OUTPUT_DIR}/${PREFIX_LOWER}_config_parse_enum_key.c.inl"
OUTPUT_FILE_4="${OUTPUT_DIR}/${PREFIX_LOWER}_config_parse_enum_key.cpp.inl"
OUTPUT_FILE_5="${OUTPUT_DIR}/${PREFIX_LOWER}_init_dm_embedded_images.cpp.inl"
OUTPUT_FILE_6="${OUTPUT_DIR}/${PREFIX_LOWER}_init_dm_anim.cpp.inl"
OUTPUT_FILE_7="${OUTPUT_DIR}/${PREFIX_LOWER}_dm_embedded_images_array.cpp.inl"
OUTPUT_FILE_8="${OUTPUT_DIR}/${PREFIX_LOWER}_get_dm_sprite_sheet.hpp.inl"
OUTPUT_FILE_9="${OUTPUT_DIR}/${PREFIX_LOWER}_get_dm_sprite_sheet.cpp.inl"

# Clean output files at the start
> "$OUTPUT_FILE_1"
> "$OUTPUT_FILE_2"
> "$OUTPUT_FILE_3"
> "$OUTPUT_FILE_4"
> "$OUTPUT_FILE_5"
> "$OUTPUT_FILE_6"
> "$OUTPUT_FILE_7"
> "$OUTPUT_FILE_8"
> "$OUTPUT_FILE_9"

echo "constexpr embedded_image_t get_${PREFIX_LOWER}_sprite_sheet(size_t i) {" >> "$OUTPUT_FILE_8"
echo "using namespace animation;" >> "$OUTPUT_FILE_8"
echo "switch (i) {" >> "$OUTPUT_FILE_8"

echo "embedded_image_t get_${PREFIX_LOWER}_sprite_sheet(size_t i) {" >> "$OUTPUT_FILE_9"
echo "using namespace animation;" >> "$OUTPUT_FILE_9"
echo "switch (i) {" >> "$OUTPUT_FILE_9"

# Extract lowercase dm names based on the 'extern const unsigned char ..._*_png[];' pattern
grep -oP "extern const unsigned char ${PREFIX_LOWER}_\K[a-z0-9_]+(?=_png)" "$HEADER_FILE" | while read -r name; do
    upper_name=$(echo "$name" | tr '[:lower:]' '[:upper:]')
    lower_name=$(echo "$name" | tr '[:upper:]' '[:lower:]')

    echo "init_digimon_anim(ctx, ${PREFIX_UPPER}_${upper_name}_ANIM_INDEX, &dm_sprite_sheet_embedded_images[${PREFIX_UPPER}_${upper_name}_ANIM_INDEX], ${PREFIX_UPPER}_${upper_name}_SPRITE_SHEET_COLS, ${PREFIX_UPPER}_${upper_name}_SPRITE_SHEET_ROWS);" >> "$OUTPUT_FILE_1"

    echo "dm_sprite_sheet_embedded_images[${PREFIX_UPPER}_${upper_name}_ANIM_INDEX] = (embedded_image_t){${PREFIX_LOWER}_${lower_name}_png, ${PREFIX_LOWER}_${lower_name}_png_size, \"embedded ${name}\"};" >> "$OUTPUT_FILE_2"

    echo "if (strcmp(lower_value, \"${lower_name}\") == 0) {" >> "$OUTPUT_FILE_3"
    echo "    config->animation_index = ${PREFIX_UPPER}_${upper_name}_ANIM_INDEX;" >> "$OUTPUT_FILE_3"
    echo "}" >> "$OUTPUT_FILE_3"

    echo "do {" >> "$OUTPUT_FILE_4"
    echo "    constexpr std::size_t lower_name_len = sizeof(\"${lower_name}\") - 1;" >> "$OUTPUT_FILE_4"
    echo "    if (strncmp(lower_value, \"${lower_name}\", lower_name_len) == 0) {" >> "$OUTPUT_FILE_4"
    echo "        config.animation_index = ${PREFIX_UPPER}_${upper_name}_ANIM_INDEX;" >> "$OUTPUT_FILE_4"
    echo "    }" >> "$OUTPUT_FILE_4"
    echo "} while(false);" >> "$OUTPUT_FILE_4"

    echo "dm_sprite_sheet_embedded_images[${PREFIX_UPPER}_${upper_name}_ANIM_INDEX] = {${PREFIX_LOWER}_${lower_name}_png, ${PREFIX_LOWER}_${lower_name}_png_size, \"embedded ${name}\"};" >> "$OUTPUT_FILE_5"

    echo "init_dm_anim(ctx, ${PREFIX_UPPER}_${upper_name}_ANIM_INDEX, get_${PREFIX_LOWER}_sprite_sheet(${PREFIX_UPPER}_${upper_name}_ANIM_INDEX), ${PREFIX_UPPER}_${upper_name}_SPRITE_SHEET_COLS, ${PREFIX_UPPER}_${upper_name}_SPRITE_SHEET_ROWS);" >> "$OUTPUT_FILE_6"

    echo "{${PREFIX_LOWER}_${lower_name}_png, ${PREFIX_LOWER}_${lower_name}_png_size, \"embedded ${name}\"}," >> "$OUTPUT_FILE_7"


    echo "case ${PREFIX_UPPER}_${upper_name}_ANIM_INDEX: return {${PREFIX_LOWER}_${lower_name}_png, ${PREFIX_LOWER}_${lower_name}_png_size, \"embedded ${name}\"};" >> "$OUTPUT_FILE_8"

    echo "case ${PREFIX_UPPER}_${upper_name}_ANIM_INDEX: return {${PREFIX_LOWER}_${lower_name}_png, ${PREFIX_LOWER}_${lower_name}_png_size, \"embedded ${name}\"};" >> "$OUTPUT_FILE_9"
done

echo "        default: return { nullptr, 0, "" };" >> "$OUTPUT_FILE_8"
echo "    }" >> "$OUTPUT_FILE_8"
echo "}" >> "$OUTPUT_FILE_8"
echo "" >> "$OUTPUT_FILE_8"

echo "        default: return { nullptr, 0, "" };" >> "$OUTPUT_FILE_9"
echo "    }" >> "$OUTPUT_FILE_9"
echo "}" >> "$OUTPUT_FILE_9"
echo "" >> "$OUTPUT_FILE_9"
