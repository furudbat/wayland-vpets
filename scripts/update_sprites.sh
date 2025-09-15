#!/bin/bash


mkdir -p ./assets/dm
mkdir -p ./assets/dm20
mkdir -p ./assets/dmx
mkdir -p ./assets/dmc
mkdir -p ./assets/pen20
mkdir -p ./assets/dmall
mkdir -p ./assets/pkmn

touch ./assets/dm/.gitkeep
touch ./assets/dm20/.gitkeep
touch ./assets/dmx/.gitkeep
touch ./assets/dmc/.gitkeep
touch ./assets/pen20/.gitkeep
touch ./assets/dmall/.gitkeep
touch ./assets/pkmn/.gitkeep

rm ./assets./dm/*.png 2> /dev/null
rm ./assets./dm20/*.png 2> /dev/null
rm ./assets./dmx/*.png 2> /dev/null
rm ./assets./dmc/*.png 2> /dev/null
rm ./assets./pen20/*.png 2> /dev/null
rm ./assets./dmall/*.png 2> /dev/null
rm ./assets./pkmn/*.png 2> /dev/null

cp ./assets/input/dm/*.png ./assets/dm/.
cp ./assets/input/dm20/*.png ./assets/dm20/.
cp ./assets/input/dmx/*.png ./assets/dmx/.
cp ./assets/input/pen20/*.png ./assets/pen20/.
cp ./assets/input/all-colored/*.png ./assets/dmall/.

mkdir -p ./assets/input/dmc-fixed
rm -rf ./assets/input/dmc-fixed/*.png
cp ./assets/input/dmc/*.png ./assets/input/dmc-fixed/.
rsync -av --existing ./assets/input/all-colored/ ./assets/input/dmc-fixed
cp ./assets/input/dmc-fixed/*.png ./assets/dmc/.


# @NOTE(assets): 0. add assets folder, (input) assets and sub folder in image_loader etc.

./scripts/make_poke_sheets.sh

./scripts/all_crop_spritesheets.sh

./scripts/all_generate_embedded_assets.sh

./scripts/all_generate_init_dm_anim_inl.sh