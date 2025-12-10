# Bongo Cat + V-Pets Wayland Overlay

[![License: MIT](https://img.shields.io/badge/License-MIT-green.svg)](https://opensource.org/licenses/MIT)
[![Version](https://img.shields.io/badge/version-3.6.0-blue.svg)](https://github.com/furudbat/wayland-vpets/releases)
[![Release Build](https://github.com/furudbat/wayland-vpets/actions/workflows/release.yml/badge.svg?branch=main)](https://github.com/furudbat/wayland-vpets/actions/workflows/release.yml)

A cute Wayland overlay that shows an animated pets reacting to your keyboard input.

![Bongocat - Demo](assets/demo.gif)  
_Classic Bongocat_

![Digimon Greymon - Demo animated](assets/digimon-demo.gif)  
_Digimon V-Pets_

![MS Agent Clippy - Demo animated](assets/clippy-demo.gif)  
_Clippy_

![Pokemon Charizard - Demo](assets/pokemon-demo.png)  
_Pokemon_

## Features

- **🐈 More Pets**
  - Bongocat 😺
  - Digimon V-Pets 🦖
  - Clippy 📎
  - Pokemon 🐭
  - Misc & custom sprite sheets 🐈‍⬛
- 🎯 Real-time keyboard animation
- 🔥 Hot-reload configuration
- 🎮 Auto-hides in fullscreen apps
- 🖥️ Multi-monitor support
- 😴 Idle/scheduled sleep mode
- 😄 Happy animation when reach KPM (Keystroke per minute)
- 🎲 Randomize sprite at start up
- 🔲 React to CPU usage
- ↔️ Movement on screen
- ⚡ Lightweight (~10MB RAM)


## Quick Start

### Install

```bash
# Arch Linux
yay -S wpets
```

#### Other distros - build from source

```bash
git clone https://github.com/furudbat/wayland-vpets.git
cd wayland-vpets
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
```

_If you only want to test without replacing bongocat, run the binary directly from `./build/` instead of installing._

##### Install ⚠️

```bash
sudo cmake --install build
```
⚠️ **this can overwrite the original installation of bongocat** ⚠️



### Setup Permissions

```bash
sudo usermod -a -G input $USER
# Log out and back in
```

### Find Your Keyboard

```bash
wpets-find-devices  # or ./scripts/find_input_devices.sh
```

### Run

```bash
wpets-all --watch-config
```

## Configuration

Create `~/.config/bongocat/bongocat.conf`:

```ini
# Bongo Cat Configuration File
# Edit these values to customize your bongo cat overlay

# Save this file to: ~/.config/bongocat/bongocat.conf
# Run with: wpets-all --watch-config --config ~/.config/bongocat/bongocat.conf

# Position & Size
cat_height=80
cat_align=center
# cat_x_offset=0
# cat_y_offset=0

# Appearance
enable_antialiasing=1
overlay_height=80
overlay_opacity=0
overlay_position=bottom
# mirror_x=0
# mirror_y=0

# Input device (run wpet-find-devices to find yours)
keyboard_device=/dev/input/event4

# Multi-monitor (optional - auto-detects by default)
# monitor=HDMI-A-1

# Sleep mode (optional)
# idle_sleep_timeout=300
# enable_scheduled_sleep=0
# sleep_begin=22:00
# sleep_end=06:00
```

### Options Reference

<details>
<summary>Click to expand all options</summary>

| **Option**                | **Values**                                                         | **Default**   | **Description**                                                                               |
|---------------------------|--------------------------------------------------------------------|---------------|-------------------------------------------------------------------------------------------|
| `cat_height`              | 8–1024                                                             | 40            | Height of bongo cat in pixels (width auto-calculated to maintain aspect ratio)            |
| `cat_x_offset`            | -16000 to 16000                                                    | 100           | Horizontal offset from center (behavior depends on `cat_align`)                           |
| `cat_y_offset`            | -16000 to 16000                                                    | 10            | Vertical offset from center (positive=down, negative=up)                                  |
| `cat_align`               | "center", "left", "right"                                          | "center"      | Horizontal alignment of cat inside overlay bar                                            |
| `overlay_height`          | 16–2560                                                            | 50            | Height of the entire overlay bar                                                          |
| `overlay_position`        | "top" or "bottom"                                                  | "top"         | Position of overlay on screen                                                             |
| `overlay_opacity`         | 0–255                                                              | 60            | Background opacity (0=transparent, 255=opaque)                                            |
| `overlay_layer`           | "overlay", "top", "bottom" or "background"                         | "overlay"     | Surface layer of overlay on screen                                                        |
| `animation_name`          | "bongocat", `<digimon name>`, "clippy", `<pokemon name>` or "neko" | "bongocat"    | Name of the V-Pet sprite (see list below)                                                 |
| `invert_color`            | 0 or 1                                                             | 0             | Invert color (useful for white digimon sprites & dark mode)                               |
| `idle_frame`              | 0–2 (varies by sprite type)                                        | 0             | Which frame to use when idle (sprite-specific options)                                    |
| `idle_animation`          | 0 or 1                                                             | 0             | Enable idle animation                                                                     |
| `animation_speed`         | 0–5000                                                             | 0             | Frame duration in ms (0 = use `fps`)                                                      |
| `keypress_duration`       | 50–5000                                                            | 100           | Duration to display keypress animation (ms)                                               |
| `mirror_x`                | 0 or 1                                                             | 0             | Flip cat horizontally (mirror across Y axis)                                              |
| `mirror_y`                | 0 or 1                                                             | 0             | Flip cat vertically (mirror across X axis)                                                |
| `test_animation_duration` | 0–5000                                                             | 0             | Duration of test animation (ms) (deprecated, use `animation_speed`)                       |
| `test_animation_interval` | 0–60                                                               | 0             | Interval for test animation in seconds (0 = disabled, deprecated)                         |
| `fps`                     | 1–144                                                              | 60            | Animation frame rate                                                                      |
| `input_fps`               | 0–144                                                              | 0             | Input thread frame rate (0 = use `fps`)                                                   |
| `enable_scheduled_sleep`  | 0 or 1                                                             | 0             | Enable scheduled sleep mode                                                               |
| `sleep_begin`             | "00:00" – "23:59"                                                  | "00:00"       | Start time of scheduled sleep (24h format)                                                |
| `sleep_end`               | "00:00" – "23:59"                                                  | "00:00"       | End time of scheduled sleep (24h format)                                                  |
| `idle_sleep_timeout`      | 0+                                                                 | 0             | Time of inactivity before entering sleep (0 = disabled) (in seconds)                      |
| `happy_kpm`               | 0–10000                                                            | 0             | Minimum keystrokes per minute to trigger happy animation (0 = disabled)                   |
| `keyboard_device`         | Valid `/dev/input/*` path(s)                                       | \<No Device\> | Input device path (multiple entries allowed)                                              |
| `enable_antialiasing`     | 0 or 1                                                             | 1             | Enable bilinear interpolation for smooth scaling (Bongocat and MS Agent only)             |
| `enable_debug`            | 0 or 1                                                             | 0             | Enable debug logging                                                                      |
| `monitor`                 | Monitor name                                                       | Auto-detect   | Which monitor to display on (e.g., "eDP-1", "HDMI-A-1")                                   |
| `random`                  | 0 or 1                                                             | 0             | Randomize `animation_index` (`animation_name` needs to be set as base sprite sheet set)   |
| `random_on_reload`        | 0 or 1                                                             | 0             | Randomize `animation_index` when reloading config (`random` needs to be `1`)              |
| `update_rate`             | 0–10000                                                            | 0             | Check (CPU) states rate (0 = disabled) (in milliseconds)                                  |
| `cpu_threshold`           | 0–100                                                              | 0             | Threshold of CPU usage for triggering work animation (0 = disabled)                       |
| `movement_radius`         | 0-8000                                                             | 0             | Radius of moving area (0 = disabled)                                                      |
| `movement_speed`          | 0–5000                                                             | 0             | Movement speed (0 = disabled)                                                             |
| `enable_movement_debug`   | 0 or 1                                                             | 0             | Show Movement area                                                                        |
| `cpu_running_factor`      | 0.0–50.0                                                           | 0             | Speed up factor for 100% CPU, it's linear so the animation slowly speed up (0 = disabled) |

#### Available Sprites (`animation_name`)

See man pages for more details and full list:

 - [Bongocat 😺](docs/fragments/set-bongocat.md)
 - [MS Agent 📎](docs/fragments/set-ms-agent.md) Clippy and friends
 - [Pokemon 🐭](docs/fragments/set-pkmn.md) up to Gen. 5
 - [Misc 🐈‍⬛](docs/fragments/set-misc.md)

##### Digimon 🦖

 - [Original](docs/fragments/set-dm.md) [`dm`](https://humulos.com/digimon/dm/)
 - [Pendulum Original](docs/fragments/set-pen.md) [`pen`](https://humulos.com/digimon/pen/)
 - [20th Anniversary](docs/fragments/set-dm20.md) [`dm20`](https://humulos.com/digimon/dm20/)
 - [Pendulum Ver.20th](docs/fragments/set-pen20.md) [`pen20`](https://humulos.com/digimon/pen20/)
 - [X](docs/fragments/set-dmx.md) [`dmx`](https://humulos.com/digimon/dmx/)
 - [Colored](docs/fragments/set-dmc.md) [`dmc`](https://humulos.com/digimon/dmc/)

_If you build with ALL assets included you can void naming conflicts by using the full name: `dm:Greymon`, `dm20:Greymon`, `dmc:Greymon`_


#### Custom Sprite Sheet (`custom_...`)

| **Option**                                  | **Values**         | **Default**      | **Description**                                                                      |
|---------------------------------------------|--------------------|------------------|--------------------------------------------------------------------------------------|
| `animation_name`                            | `"custom"`         |                  | Must be `"custom"` for custom-options to work                                        |
| `custom_sprite_sheet_filename`              | Path to image file |                  | Path to the custom sprite sheet image (**must be png**)                              |
| `custom_idle_frames`                        | 1-500              | 0 (disabled)     | Number of frames for idle animation                                                  |
| `custom_boring_frames`                      | 1-500              | 0 (disabled)     | Number of frames for boring animation                                                |
| `custom_start_writing_frames`               | 1-500              | 0 (disabled)     | Number of frames for start writing animation                                         |
| `custom_writing_frames`                     | 1-500              | 0 (disabled)     | Number of frames for writing animation                                               |
| `custom_end_writing_frames`                 | 1-500              | 0 (disabled)     | Number of frames for end writing animation                                           |
| `custom_happy_frames`                       | 1-500              | 0 (disabled)     | Number of frames for happy animation                                                 |
| `custom_asleep_frames`                      | 1-500              | 0 (disabled)     | Number of frames for falling asleep animation                                        |
| `custom_sleep_frames`                       | 1-500              | 0 (disabled)     | Number of frames for sleeping animation                                              |
| `custom_wake_up_frames`                     | 1-500              | 0 (disabled)     | Number of frames for waking up animation                                             |
| `custom_start_working_frames`               | 1-500              | 0 (disabled)     | Number of frames for start working animation                                         |
| `custom_working_frames`                     | 1-500              | 0 (disabled)     | Number of frames for working animation                                               |
| `custom_end_working_frames`                 | 1-500              | 0 (disabled)     | Number of frames for end working animation                                           |
| `custom_start_moving_frames`                | 1-500              | 0 (disabled)     | Number of frames for start moving animation                                          |
| `custom_moving_frames`                      | 1-500              | 0 (disabled)     | Number of frames for moving animation                                                |
| `custom_end_moving_frames`                  | 1-500              | 0 (disabled)     | Number of frames for end moving animation                                            |
| `custom_toggle_writing_frames`              | 0 or 1             | -1 (auto)        | Toggle writing frames when writing (`custom_writing_frames` needs to be `2`)         |
| `custom_toggle_writing_frames_random`       | 0 or 1             | -1 (auto)        | Randomize writing frame when start writing (`custom_writing_frames` needs to be `2`) |
| `custom_mirror_x_moving`                    | 0 or 1             | -1 (ignore)      | Mirror frames horizontally when moving                                               |
| `custom_idle_row`                           | 1-15               | -1 (auto)        | Row nr for idle animation in sprite sheet                                            |
| `custom_boring_row`                         | 1-15               | -1 (auto)        | Row nr for boring animation                                                          |
| `custom_start_writing_row`                  | 1-15               | -1 (auto)        | Row nr for start writing animation                                                   |
| `custom_writing_row`                        | 1-15               | -1 (auto)        | Row nr for writing animation                                                         |
| `custom_end_writing_row`                    | 1-15               | -1 (auto)        | Row nr for end writing animation                                                     |
| `custom_happy_row`                          | 1-15               | -1 (auto)        | Row nr for happy animation                                                           |
| `custom_asleep_row`                         | 1-15               | -1 (auto)        | Row nr for asleep animation                                                          |
| `custom_sleep_row`                          | 1-15               | -1 (auto)        | Row nr for sleep animation                                                           |
| `custom_wake_up_row`                        | 1-15               | -1 (auto)        | Row nr for wake-up animation                                                         |
| `custom_start_working_row`                  | 1-15               | -1 (auto)        | Row nr for start working animation                                                   |
| `custom_working_row`                        | 1-15               | -1 (auto)        | Row nr for working animation                                                         |
| `custom_end_working_row`                    | 1-15               | -1 (auto)        | Row nr for end working animation                                                     |
| `custom_start_moving_row`                   | 1-15               | -1 (auto)        | Row nr for start moving animation                                                    |
| `custom_moving_row`                         | 1-15               | -1 (auto)        | Row nr for moving animation                                                          |
| `custom_end_moving_row`                     | 1-15               | -1 (auto)        | Row nr for end moving animation                                                      |

See [examples](examples/custom-sprite-sheets) for more details.

</details>


## Command Line

```bash
wpets-all [OPTIONS]

Options:
  -h, --help                Show this help message
  -v, --version             Show version information
  -c, --config              Specify config file (default: ~/.config/bongocat.conf)
  -w, --watch-config        Watch config file for changes and reload automatically
  -t, --toggle              Toggle bongocat on/off (start if not running, stop if running)
  -o, --output-name NAME    Specify output name (overwrite output_name from config)
      --random              Randomize animation_name at start up
      --strict              Only start up with a valid config and valid parameter
      --nr NR               Specify Nr. for PID file to avoid conflicting ruinning instances
      --ignore-running      Ignore current running instance (avoid PID file conflicts)
```

### Examples

```bash
# Basic usage (bongocat)
wpets

# Run immediately (bongocat)
wpets --watch-config

# Custom config with hot-reload (bongocat)
wpets --watch-config --config ~/.config/bongocat/bongocat.conf


# drop-in replacement for bongocat (bongocat)
wpets --watch-config --config ~/.config/bongocat/bongocat.conf

# pokemon sprites
wpets-pkmn --watch-config --config ~/.config/bongocat/pkmn.bongocat.conf
wpets-pkmn --watch-config --config ~/.config/bongocat/pmd.bongocat.conf

# all sprites available (Recommended)
wpets-all --watch-config --config ~/.config/bongocat/bongocat.conf
wpets-all --watch-config --config ~/.config/bongocat/digimon.bongocat.conf
wpets-all --watch-config --config ~/.config/bongocat/clippy.bongocat.conf
wpets-all --watch-config --config ~/.config/bongocat/neko.bongocat.conf
```

_`wpets` is the default **minimal** binary. **`wpets-all`** and `wpets-pkmn` are variants with specific sprite sets._  
_Just use `wpets-all` with all sprites included, try out all the pets._

See [examples/](examples) for more configs.

#### Hyprland

For [hyprland](https://hypr.land/) users, you can autostart `wpets` in your `hyprland.conf`:

```ini
# Auto start
exec-once = wpets-all --watch-config --config ~/.config/bongocat/screen1.bongocat.conf -o HDMI-A-1
exec-once = wpets-all --watch-config --config ~/.config/bongocat/screen2.bongocat.conf -o DP-1
exec-once = wpets-all --watch-config --config ~/.config/bongocat/screen3.bongocat.conf
exec-once = wpets-all --watch-config --config ~/.config/bongocat/screen4.bongocat.conf --random
```

_It can happen that waybar is rendered over the wpet, because they are on the same layer and waybar is started "over" the waybar, just delay the `wpets` start: `exec-once = sleep 5 && wpets-all ...`._

## Troubleshooting

<details>
<summary>Permission denied on input device</summary>

```bash
sudo usermod -a -G input $USER
# Then log out and back in
```

</details>

<details>
<summary>Cat not responding to keyboard</summary>

1. Run `wpets-find-devices` to find correct device
2. Update `keyboard_device` in config
3. Restart bongocat

</details>

<details>
<summary>Not showing on correct monitor</summary>

Add `monitor=YOUR_MONITOR` to config. Find monitor names with `wlr-randr` or `hyprctl monitors`.

</details>

## Building

```bash
git clone https://github.com/furudbat/wayland-vpets.git
cd wayland-vpets
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
```

**Requirements:** wayland-client, wayland-protocols, gcc/clang, make, cmake

## License

MIT License - see [LICENSE](LICENSE)