#!/bin/bash


mkdir -p ./assets/dm
mkdir -p ./assets/dm20
mkdir -p ./assets/dmx
mkdir -p ./assets/dmc
mkdir -p ./assets/pen20

touch ./assets/dm/.gitkeep
touch ./assets/dm20/.gitkeep
touch ./assets/dmx/.gitkeep
touch ./assets/dmc/.gitkeep
touch ./assets/pen20/.gitkeep

rm ./assets./dm/*.png 2> /dev/null
rm ./assets./dm20/*.png 2> /dev/null
rm ./assets./dmx/*.png 2> /dev/null
rm ./assets./dmc/*.png 2> /dev/null
rm ./assets./pen20/*.png 2> /dev/null

#cp ./assets/input/dm/*.png ./assets/dm/.
#cp ./assets/input/dm20/*.png ./assets/dm20/.
#cp ./assets/input/dmx/*.png ./assets/dmx/.
#cp ./assets/input/pen20/*.png ./assets/pen20/.


mkdir -p ./assets/input/dmc-fixed
cp ./assets/input/dmc/*.png ./assets/input/dmc-fixed/.
rsync -av --existing ./assets/input/all-colored/ ./assets/input/dmc-fixed
cp ./assets/input/dmc-fixed/*.png ./assets/dmc/.

./scripts/all_crop_spritesheets.sh
