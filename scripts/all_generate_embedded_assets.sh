#!/bin/bash

./scripts/generate_embedded_assets.sh assets/dm assets/input/dm include/graphics/embedded_assets/dm.h src/graphics/embedded_assets/dm.c include/graphics/embedded_assets/dm.hpp --frame-size 128
./scripts/generate_embedded_assets.sh assets/dm20 assets/input/dm20 include/graphics/embedded_assets/dm20.h src/graphics/embedded_assets/dm20.c include/graphics/embedded_assets/dm20.hpp --frame-size 128
./scripts/generate_embedded_assets.sh assets/dmc assets/input/dmc include/graphics/embedded_assets/dmc.h src/graphics/embedded_assets/dmc.c include/graphics/embedded_assets/dmc.hpp --frame-size 128
./scripts/generate_embedded_assets.sh assets/dmx assets/input/dmx include/graphics/embedded_assets/dmx.h src/graphics/embedded_assets/dmx.c include/graphics/embedded_assets/dmx.hpp --frame-size 128

./scripts/generate_embedded_assets.sh assets/pen20 assets/input/pen20 include/graphics/embedded_assets/pen20.h src/graphics/embedded_assets/pen20.c include/graphics/embedded_assets/pen20.hpp --frame-size 128
