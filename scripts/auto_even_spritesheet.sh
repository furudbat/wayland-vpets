#!/bin/bash
# auto_even_spritesheet.sh
# Usage: ./auto_even_spritesheet.sh INPUT_DIR

INPUT_DIR="$1"
DIV=$2
[ -d "$INPUT_DIR" ] || { echo "Directory not found"; exit 1; }

for f in "$INPUT_DIR"/*.png; do
    [ -f "$f" ] || continue

    # Get current dimensions
    read width height < <(magick identify -format "%w %h" "$f")

    # Compute padding to make divisible by DIV
    pad_w=$(( (DIV - (width % DIV)) % DIV ))
    pad_h=$(( (DIV - (height % DIV)) % DIV ))

    if [ "$pad_w" -eq 0 ] && [ "$pad_h" -eq 0 ]; then
        #echo "Skipping $f: already divisible by $DIV"
        continue
    fi

    new_w=$(( width + pad_w ))
    new_h=$(( height + pad_h ))

    echo "Processing $f: ${width}x${height} -> ${new_w}x${new_h} (pad ${pad_w}x${pad_h})"

    # Pad the image (transparent) from bottom-right
    magick "$f" -background transparent -gravity Southeast -extent "${new_w}x${new_h}" "$f"
done