#!/bin/bash

./scripts/generate_init_anim_inl.sh assets/dm src/embedded_assets/dm ./include/embedded_assets/dm/dm_images.h dm --layout Dm
./scripts/generate_init_anim_inl.sh assets/dm20 src/embedded_assets/dm20 ./include/embedded_assets/dm20/dm20_images.h dm20 --layout Dm --alt dm
./scripts/generate_init_anim_inl.sh assets/dmc src/embedded_assets/dmc ./include/embedded_assets/dmc/dmc_images.h dmc --layout Dm
./scripts/generate_init_anim_inl.sh assets/dmx src/embedded_assets/dmx ./include/embedded_assets/dmx/dmx_images.h dmx --layout Dm

./scripts/generate_init_anim_inl.sh assets/pen src/embedded_assets/pen ./include/embedded_assets/pen/pen_images.h pen --layout Dm
./scripts/generate_init_anim_inl.sh assets/pen20 src/embedded_assets/pen20 ./include/embedded_assets/pen20/pen20_images.h pen20 --layout Dm --alt pen

./scripts/generate_init_anim_inl.sh assets/dmall src/embedded_assets/dmall ./include/embedded_assets/dmall/dmall_images.h dmall --layout Dm --alt dmc

./scripts/generate_init_anim_inl.sh assets/pkmn src/embedded_assets/pkmn ./include/embedded_assets/pkmn/pkmn.h pkmn --layout Pkmn

./scripts/generate_custom_init_anim_inl.sh assets/pmd src/embedded_assets/pmd ./include/embedded_assets/pmd/pmd.h pmd --layout Custom --set pmd

# @NOTE(assets): 2.2. generate embedded_assets code