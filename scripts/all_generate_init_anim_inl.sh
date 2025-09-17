#!/bin/bash

./scripts/generate_init_anim_inl.sh assets/dm src/embedded_assets/dm ./include/embedded_assets/dm/dm_images.h dm --set Dm
./scripts/generate_init_anim_inl.sh assets/dm20 src/embedded_assets/dm20 ./include/embedded_assets/dm20/dm20_images.h dm20 --set Dm --alt dm
./scripts/generate_init_anim_inl.sh assets/dmc src/embedded_assets/dmc ./include/embedded_assets/dmc/dmc_images.h dmc --set Dm
./scripts/generate_init_anim_inl.sh assets/dmx src/embedded_assets/dmx ./include/embedded_assets/dmx/dmx_images.h dmx --set Dm

#./scripts/generate_init_anim_inl.sh assets/pen20 src/embedded_assets/pen20 ./include/embedded_assets/pen20/pen20_images.h pen20 --set Dm

./scripts/generate_init_anim_inl.sh assets/dmall src/embedded_assets/dmall ./include/embedded_assets/dmall/dmall_images.h dmall --set Dm --alt dmc

./scripts/generate_init_anim_inl.sh assets/pkmn src/embedded_assets/pkmn ./include/embedded_assets/pkmn/pkmn.h pkmn --set Pkmn

# @NOTE(assets): 2.2. generate embedded_assets code