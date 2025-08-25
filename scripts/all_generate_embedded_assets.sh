#!/bin/bash

./scripts/generate_embedded_assets.sh assets/dm assets/input/dm include/graphics/embedded_assets/dm_images.h src/graphics/embedded_assets/dm_images.c include/graphics/embedded_assets/dm.hpp --frame-size 128
./scripts/generate_embedded_assets.sh assets/dm20 assets/input/dm20 include/graphics/embedded_assets/dm20_images.h src/graphics/embedded_assets/dm20_images.c include/graphics/embedded_assets/dm20.hpp --frame-size 128
#./scripts/generate_embedded_assets.sh assets/dmc assets/input/dmc include/graphics/embedded_assets/dmc_images.h src/graphics/embedded_assets/dmc_images.c include/graphics/embedded_assets/dmc.hpp --frame-size 128
./scripts/generate_embedded_assets.sh assets/dmx assets/input/dmx include/graphics/embedded_assets/dmx_images.h src/graphics/embedded_assets/dmx_images.c include/graphics/embedded_assets/dmx.hpp --frame-size 128

#./scripts/generate_embedded_assets.sh assets/pen20 assets/input/pen20 include/graphics/embedded_assets/pen20_images.h src/graphics/embedded_assets/pen20_images.c include/graphics/embedded_assets/pen20.hpp --frame-size 128
