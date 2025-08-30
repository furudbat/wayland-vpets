#!/bin/bash

#./scripts/even_sprite_sheet.sh ./assets/input/links.sprite-sheet.png ./assets/input/links.png 28 26

# Input sprite sheet
INPUT="$1"
OUTPUT="$2"

# Number of columns and rows
COLS=$3
ROWS=$4

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