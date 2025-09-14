#!/bin/bash

./scripts/generate_init_dm_anim_inl.sh assets/dm src/embedded_assets/dm ./include/embedded_assets/dm/dm_images.h dm
./scripts/generate_init_dm_anim_inl.sh assets/dm20 src/embedded_assets/dm20 ./include/embedded_assets/dm20/dm20_images.h dm20
./scripts/generate_init_dm_anim_inl.sh assets/dmc src/embedded_assets/dmc ./include/embedded_assets/dmc/dmc_images.h dmc
./scripts/generate_init_dm_anim_inl.sh assets/dmx src/embedded_assets/dmx ./include/embedded_assets/dmx/dmx_images.h dmx

#./scripts/generate_init_dm_anim_inl.sh assets/pen20 src/embedded_assets/pen20 ./include/embedded_assets/pen20/pen20_images.h pen20

./scripts/generate_init_dm_anim_inl.sh assets/dmall src/embedded_assets/dmall ./include/embedded_assets/dmall/dmall_images.h dmall
