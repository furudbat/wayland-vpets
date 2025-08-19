#!/bin/bash
# revert_packer_boxes.sh
# Repack sprites using boxes.txt info
# Usage: ./revert_packer_boxes.sh boxes.txt input.png output.png

INPUT="$1"
OUTPUT="$2"

WORKDIR=$(mktemp -d)
trap 'rm -rf "$WORKDIR"' EXIT
SPRITES="$WORKDIR/sprites"
FRAMED="$WORKDIR/framed"
mkdir -p "$SPRITES" "$FRAMED"

echo "Using temp folder $WORKDIR"


# Number of columns and rows
COLS=22
ROWS=41

# Original image dimensions
WIDTH=$(magick identify -format "%w" "$INPUT")
HEIGHT=$(magick identify -format "%h" "$INPUT")

# Compute new frame dimensions (even)
FRAME_WIDTH=$(( WIDTH / COLS ))
FRAME_HEIGHT=$(( HEIGHT / ROWS ))

# Compute new total sprite sheet size
NEW_WIDTH=$(( FRAME_WIDTH * COLS ))
NEW_HEIGHT=$(( FRAME_HEIGHT * ROWS ))

echo "Original size: ${WIDTH}x${HEIGHT}"
echo "New frame size: ${FRAME_WIDTH}x${FRAME_HEIGHT}"
echo "New sheet size: ${NEW_WIDTH}x${NEW_HEIGHT}"

# Calculate padding needed
PAD_WIDTH=$(( NEW_WIDTH - WIDTH ))
PAD_HEIGHT=$(( NEW_HEIGHT - HEIGHT ))

# Pad the image to the new size (centered)
magick "$INPUT" -background transparent -gravity center -extent ${NEW_WIDTH}x${NEW_HEIGHT} "$OUTPUT"

echo "Done! Padded sprite sheet saved as $OUTPUT"