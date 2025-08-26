#!/bin/bash

./scripts/generate_init_dm_anim_inl.sh src/graphics/embedded_assets ./include/graphics/embedded_assets/dm_images.h dm
./scripts/generate_init_dm_anim_inl.sh src/graphics/embedded_assets ./include/graphics/embedded_assets/dm20_images.h dm20
./scripts/generate_init_dm_anim_inl.sh src/graphics/embedded_assets ./include/graphics/embedded_assets/dmc_images.h dmc
./scripts/generate_init_dm_anim_inl.sh src/graphics/embedded_assets ./include/graphics/embedded_assets/dmx_images.h dmx

#./scripts/generate_init_dm_anim_inl.sh src/graphics/embedded_assets ./include/graphics/embedded_assets/pen20_images.h pen20
