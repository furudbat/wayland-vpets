#!/bin/bash

# dm
./scripts/generate_embedded_assets_2.sh assets/dm assets/input/dm include/embedded_assets/dm/dm_images.h src/embedded_assets/dm/dm_images.c include/embedded_assets/dm/dm.hpp include/embedded_assets/dm/dm_sprite.h src/embedded_assets/dm/dm_get_sprite_sheet.cpp src/image_loader/dm/dm_load_sprite_sheet.cpp --frame-size 128 --layout Dm --set dm --load-function "load_base_dm_anim"
./scripts/generate_init_anim.sh assets/dm src/embedded_assets/dm ./include/embedded_assets/dm/dm_images.h dm --layout Dm --set dm
./scripts/generate_embedded_assets_dm_evol.sh assets/dm assets/input/dm src/embedded_assets/dm/dm_get_evolution_data.cpp --frame-size 128 --layout Dm --set dm

# dm20
./scripts/generate_embedded_assets_2.sh assets/dm20 assets/input/dm20 include/embedded_assets/dm20/dm20_images.h src/embedded_assets/dm20/dm20_images.c include/embedded_assets/dm20/dm20.hpp include/embedded_assets/dm20/dm20_sprite.h src/embedded_assets/dm20/dm20_get_sprite_sheet.cpp src/image_loader/dm20/dm20_load_sprite_sheet.cpp --frame-size 128 --layout Dm --set dm20 --load-function "load_base_dm_anim"
./scripts/generate_init_anim.sh assets/dm20 src/embedded_assets/dm20 ./include/embedded_assets/dm20/dm20_images.h dm20 --layout Dm --alt dm --set dm20
./scripts/generate_embedded_assets_dm_evol.sh assets/dm20 assets/input/dm20 src/embedded_assets/dm20/dm20_get_evolution_data.cpp --frame-size 128 --layout Dm --set dm20

# pen
./scripts/generate_init_anim.sh assets/pen src/embedded_assets/pen ./include/embedded_assets/pen/pen_images.h pen --layout Dm --set pen
./scripts/generate_embedded_assets_dm_evol.sh assets/pen assets/input/pen src/embedded_assets/pen/pen_get_evolution_data.cpp --frame-size 128 --layout Dm --set pen
./scripts/generate_embedded_assets_2.sh assets/pen assets/input/pen include/embedded_assets/pen/pen_images.h src/embedded_assets/pen/pen_images.c include/embedded_assets/pen/pen.hpp include/embedded_assets/pen/pen_sprite.h src/embedded_assets/pen/pen_get_sprite_sheet.cpp src/image_loader/pen/pen_load_sprite_sheet.cpp --frame-size 128 --layout Dm --set pen --load-function "load_base_dm_anim"

# pen20
./scripts/generate_embedded_assets_2.sh assets/pen20 assets/input/pen20 include/embedded_assets/pen20/pen20_images.h src/embedded_assets/pen20/pen20_images.c include/embedded_assets/pen20/pen20.hpp include/embedded_assets/pen20/pen20_sprite.h src/embedded_assets/pen20/pen20_get_sprite_sheet.cpp src/image_loader/pen20/pen20_load_sprite_sheet.cpp --frame-size 128 --layout Dm --set pen20 --load-function "load_base_dm_anim"
./scripts/generate_init_anim.sh assets/pen20 src/embedded_assets/pen20 ./include/embedded_assets/pen20/pen20_images.h pen20 --layout Dm --alt pen --set pen20
./scripts/generate_embedded_assets_dm_evol.sh assets/pen20 assets/input/pen20 src/embedded_assets/pen20/pen20_get_evolution_data.cpp --frame-size 128 --layout Dm --set pen20

# dmx
./scripts/generate_embedded_assets_2.sh assets/dmx assets/input/dmx include/embedded_assets/dmx/dmx_images.h src/embedded_assets/dmx/dmx_images.c include/embedded_assets/dmx/dmx.hpp include/embedded_assets/dmx/dmx_sprite.h src/embedded_assets/dmx/dmx_get_sprite_sheet.cpp src/image_loader/dmx/dmx_load_sprite_sheet.cpp --frame-size 128 --layout Dm --set dmx --load-function "load_base_dm_anim"
./scripts/generate_init_anim.sh assets/dmx src/embedded_assets/dmx ./include/embedded_assets/dmx/dmx_images.h dmx --layout Dm --set dmx
./scripts/generate_embedded_assets_dm_evol.sh assets/dmx assets/input/dmx src/embedded_assets/dmx/dmx_get_evolution_data.cpp --frame-size 128 --layout Dm --set dmx

# dmc
./scripts/generate_embedded_assets_2.sh assets/dmc assets/input/dmc-fixed include/embedded_assets/dmc/dmc_images.h src/embedded_assets/dmc/dmc_images.c include/embedded_assets/dmc/dmc.hpp include/embedded_assets/dmc/dmc_sprite.h src/embedded_assets/dmc/dmc_get_sprite_sheet.cpp src/image_loader/dmc/dmc_load_sprite_sheet.cpp --frame-size 128 --layout Dm --set dmc --load-function "load_base_dm_anim"
./scripts/generate_init_anim.sh assets/dmc src/embedded_assets/dmc ./include/embedded_assets/dmc/dmc_images.h dmc --layout Dm --set dmc
./scripts/generate_embedded_assets_dm_evol.sh assets/dmc assets/input/dmc-fixed src/embedded_assets/dmc/dmc_get_evolution_data.cpp --frame-size 128 --layout Dm --set dmc

# dmall
./scripts/generate_embedded_assets_2.sh assets/dmall assets/input/all-colored include/embedded_assets/dmall/dmall_images.h src/embedded_assets/dmall/dmall_images.c include/embedded_assets/dmall/dmall.hpp include/embedded_assets/dmall/dmall_sprite.h src/embedded_assets/dmall/dmall_get_sprite_sheet.cpp src/image_loader/dmall/dmall_load_sprite_sheet.cpp --frame-size 128 --layout Dm --set dmall --load-function "load_base_dm_anim"
./scripts/generate_init_anim.sh assets/dmall src/embedded_assets/dmall ./include/embedded_assets/dmall/dmall_images.h dmall --layout Dm --alt dmc --set dmall
./scripts/generate_embedded_assets_dmall_evol.sh assets/dmall assets/input/all-colored src/embedded_assets/dmall/dmall_get_evolution_data.cpp --frame-size 128 --layout Dm --set dmall

# pkmn
./scripts/generate_embedded_assets_2.sh assets/pkmn assets/input/pkmn include/embedded_assets/pkmn/pkmn_images.h src/embedded_assets/pkmn/pkmn_images.c include/embedded_assets/pkmn/pkmn.hpp include/embedded_assets/pkmn/pkmn_sprite.h src/embedded_assets/pkmn/pkmn_get_sprite_sheet.cpp src/image_loader/pkmn/pkmn_load_sprite_sheet.cpp --cols 2 --rows 1 --layout Pkmn
./scripts/generate_init_anim.sh assets/pkmn src/embedded_assets/pkmn ./include/embedded_assets/pkmn/pkmn.h pkmn --layout Pkmn --set None
./scripts/generate_embedded_assets_pkmn_evol.sh assets/pkmn assets/input/pkmn src/embedded_assets/pkmn/pkmn_get_evolution_data.cpp --cols 2 --rows 1 --layout Pkmn

# pmd
./scripts/generate_embedded_custom_assets_2.sh assets/pmd assets/input/pmd include/embedded_assets/pmd/pmd_images.h src/embedded_assets/pmd/pmd_images.c include/embedded_assets/pmd/pmd.hpp include/embedded_assets/pmd/pmd_sprite.h src/embedded_assets/pmd/pmd_get_sprite_sheet.cpp src/image_loader/pmd/pmd_load_sprite_sheet.cpp src/embedded_assets/pmd/pmd_get_sprite_sheet_settings.cpp assets/input/pmd-sprite-meta.json --layout Custom --set pmd
./scripts/generate_custom_init_anim.sh assets/pmd src/embedded_assets/pmd ./include/embedded_assets/pmd/pmd.h pmd --layout Custom --set pmd
./scripts/generate_embedded_assets_pmd_evol.sh assets/pmd assets/input/pmd src/embedded_assets/pmd/pmd_get_evolution_data.cpp assets/input/pmd-sprite-meta.json --layout Custom --set pmd

# @NOTE(assets): 2. generate embedded_assets code
