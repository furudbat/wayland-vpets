#!/bin/bash
# auto_center_sprites.sh
# Usage: ./auto_center_sprites.sh INPUT_DIR

INPUT_DIR="$1"
[ -d "$INPUT_DIR" ] || { echo "Directory not found"; exit 1; }

TMP_DIR=$(mktemp -d)
trap 'rm -rf "$TMP_DIR"' EXIT

# Function to compute GCD
gcd() {
    a=$1; b=$2
    while [ $b -ne 0 ]; do
        t=$b
        b=$((a % b))
        a=$t
    done
    echo $a
}

for f in "$INPUT_DIR"/*.png; do
    [ -f "$f" ] || continue

    # Get image dimensions
    read width height < <(magick identify -format "%w %h" "$f")

    # Detect bounding boxes of connected components (sprites)
    boxes=$(magick "$f" -define connected-components:verbose=true -connected-components 4 null: | awk '/BoundingBox/ {print $2}')

    # Extract widths and heights from bounding boxes
    sprite_w=$width
    sprite_h=$height
    for box in $boxes; do
        w=$(echo $box | cut -d'x' -f1)
        h=$(echo $box | cut -d'x' -f2)
        sprite_w=$(gcd $sprite_w $w)
        sprite_h=$(gcd $sprite_h $h)
    done

    # Compute number of columns and rows
    cols=$(( (width + sprite_w - 1) / sprite_w ))
    rows=$(( (height + sprite_h - 1) / sprite_h ))

    # Compute padded sheet size
    new_w=$(( cols * sprite_w ))
    new_h=$(( rows * sprite_h ))

    # Pad sheet to full grid
    magick "$f" -background transparent -extent "${new_w}x${new_h}" "${TMP_DIR}/tmp_extent.png"

    # Center each frame
    magick "${TMP_DIR}/tmp_extent.png" -crop "${sprite_w}x${sprite_h}" +repage -gravity center -background transparent -extent "${sprite_w}x${sprite_h}" "$f"
done
