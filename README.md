# Bongo Cat + V-Pets Wayland Overlay

[![License: MIT](https://img.shields.io/badge/License-MIT-green.svg)](https://opensource.org/licenses/MIT)
[![Version](https://img.shields.io/badge/version-3.0.0-blue.svg)](https://github.com/furudbat/wayland-vpets/releases)

A delightful Wayland overlay that displays an animated V-Pet reacting to your keyboard input! 
Perfect for streamers, content creators, or anyone who wants to add some fun to their desktop.

![Bongocat - Demo](assets/demo.gif)  
_Classic Bongocat_

![Digimon Greymon - Demo animated](assets/digimon-demo.gif)  
_Digimon V-Pets_

![MS Agent Clippy - Demo animated](assets/clippy-demo.gif)  
_Clippy_

![Pokemon Charizard - Demo](assets/pokemon-demo.png)  
_Pokemon_

![Pokemon Charizard - Demo](assets/pokemon-demo.png)  
_Pokemon_

## ✨ Features

- **🐈 More Pets** - More Sprite to choose from
  - Bongocat 😺
  - Digimon V-Pets 🦖 (v1.3.0)
  - Clippy 📎 (v2.1.0)
  - Pokemon 🐭 (v3.0.0)
- **🎯 Real-time Animation** - Bongo cat reacts instantly to keyboard input
- **🔥 Hot-Reload Configuration** - Modify settings without restarting (v1.2.0)
- **🔄 Dynamic Device Detection** - Automatically detects Bluetooth/USB keyboards (v1.2.0)
- **⚡ Performance Optimized** - Adaptive monitoring and batch processing (v1.4.0)
  - triggers rendering, only when needed (v2.0.0)
- **🖥️ Screen Detection** - Automatic screen detection for all sizes and orientations (v1.2.2)
- **🎮 Smart Fullscreen Detection** - Automatically hides during fullscreen applications (v1.2.3)
- **🖥️ Multi-Monitor Support** - Choose which monitor to display on in multi-monitor setups (v1.2.4)
- **😴 Sleep Mode** - Scheduled or idle-based sleep mode with custom timing (v1.2.5)
- **🎨 Customizable Appearance** - Fine-tune position, size, alignment, and opacity
- **💾 Lightweight** - Minimal resource usage (~10MB RAM, depends on the loaded sprites)
  - Lazy loading - Load only used assets into RAM (v2.4.0)
- **🎛️ Multi-device Support** - Monitor multiple keyboards simultaneously
- **🏗️ Cross-platform** - Works on x86_64 and ARM64
- **😄 Happy Frame** - Reach KPM (Keystroke per minute) to trigger the happy frame (Digimon)
- **🎲 Random Frame** - Randomize sprite frame at start up (Digimon) (v2.4.0)

## 🚀 Installation

### Arch Linux (Recommended)

```bash
# Using yay
yay -S bongocat

# Using paru
paru -S bongocat

# Run immediately
bongocat --watch-config

# Custom config with hot-reload
bongocat --config ~/.config/bongocat.conf --watch-config
```

#### From Source

```bash
# Install dependencies
pacman -S gcc make cmake libinput wayland wayland-protocols

# Clone repository
git clone https://github.com/furudbat/wayland-vpets.git
cd wayland-vpets

# Build
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build

# Install
sudo cmake --install build
```

### Other Distributions

<details>
<summary>Fedora</summary>

```bash
# Install dependencies
sudo dnf install wayland-devel wayland-protocols-devel gcc make cmake

# Build from source
git clone https://github.com/furudbat/wayland-vpets.git
cd wayland-vpets
cmake -B build
cmake --build build

# Run
./build/bongocat
```

</details>

<details>
<summary>NixOS</summary>

```bash
# Quick start with flakes
nix run github:furudbat/wayland-vpets -- --watch-config

# Install to user profile
nix profile install github:furudbat/wayland-vpets
```

📖 **For comprehensive NixOS setup, see [nix/NIXOS.md](nix/NIXOS.md)**

</details>

## 🎮 Quick Start

### 1. Setup Permissions

```bash
# Add your user to the input group
sudo usermod -a -G input $USER
# Log out and back in for changes to take effect
```

### 2. Find Your Input Devices

```bash
# If installed via AUR
bongocat-find-devices

# If built from source
./scripts/find_input_devices.sh
```

### 3. Run with Hot-Reload

```bash
# AUR installation
bongocat --watch-config

# From source
./build/bongocat --watch-config
```

## ⚙️ Configuration

Bongo Cat uses a simple configuration file format. With hot-reload enabled (`--watch-config`), changes apply instantly without restarting.

### Basic Configuration

Create or edit `bongocat.conf`:

```ini
# Position settings
cat_x_offset=0                   # Horizontal offset from center position
cat_y_offset=0                   # Vertical offset from default position
cat_align=center                 # Horizontal alignment in the bar (left/center/right)

# Size settings
cat_height=80                    # Height of bongo cat (10-200)

# Visual settings
mirror_x=0                       # Flip horizontally (mirror across Y axis)
mirror_y=0                       # Flip vertically (mirror across X axis)

# Anti-aliasing settings
enable_antialiasing=1            # Use bilinear interpolation for smooth scaling (0=off, 1=on)

# Overlay settings (requires restart)
overlay_height=60                # Height of the entire overlay bar (20-300)
overlay_opacity=150              # Background opacity (0-255)
overlay_position=top             # Position on screen (top/bottom)
layer=top                        # Layer type (top/overlay)

# Animation settings
idle_frame=0                     # Frame to show when idle (0-3)
fps=60                           # Frame rate (1-120)
keypress_duration=100            # Animation duration (ms)
test_animation_duration=200      # Test animation duration (ms)
test_animation_interval=0        # Test animation every N seconds (0=off)

# Input devices (add multiple lines for multiple keyboards)
keyboard_device=/dev/input/event4
# keyboard_device=/dev/input/event20  # External/Bluetooth keyboard

# Multi-monitor support
monitor=eDP-1                    # Specify which monitor to display on (optional)

# Sleep mode settings
enable_scheduled_sleep=0         # Enable scheduled sleep mode (0=off, 1=on)
sleep_begin=20:00                # Begin of sleeping phase (HH:MM)
sleep_end=06:00                  # End of sleeping phase (HH:MM)
idle_sleep_timeout=0             # Inactivity timeout before sleep (seconds, 0=off)

# Debug
enable_debug=0                   # Show debug messages
```

### Configuration Reference

| Setting                   | Type     | Range / Options                                            | Default             | Description                                                                             |
|---------------------------|----------|------------------------------------------------------------|---------------------|-----------------------------------------------------------------------------------------|
| `cat_height`              | Integer  | 10–200                                                     | 40                  | Height of bongo cat in pixels (width auto-calculated to maintain aspect ratio)          |
| `cat_x_offset`            | Integer  | -9999 to 9999                                              | 100                 | Horizontal offset from center (behavior depends on `cat_align`)                         |
| `cat_y_offset`            | Integer  | -9999 to 9999                                              | 10                  | Vertical offset from center (positive=down, negative=up)                                |
| `cat_align`               | String   | "center", "left", "right"                                  | "center"            | Horizontal alignment of cat inside overlay bar                                          |
| `overlay_height`          | Integer  | 20–300                                                     | 50                  | Height of the entire overlay bar                                                        |
| `overlay_position`        | String   | "top" or "bottom"                                          | "top"               | Position of overlay on screen                                                           |
| `overlay_opacity`         | Integer  | 0–255                                                      | 60                  | Background opacity (0=transparent, 255=opaque)                                          |
| `animation_name`          | String   | "bongocat", `<digimon name>`, "clippy" or `<pokemon name>` | "bongocat"          | Name of the V-Pet sprite (see list below)                                               |
| `invert_color`            | Boolean  | 0 or 1                                                     | 0                   | Invert color (useful for white digimon sprites & dark mode)                             |
| `padding_x`               | Integer  | 0–9999                                                     | 0                   | Horizontal padding per frame (ignored for bongocat)                                     |
| `padding_y`               | Integer  | 0–9999                                                     | 0                   | Vertical padding per frame (ignored for bongocat)                                       |
| `idle_frame`              | Integer  | 0–2 (varies by sprite type)                                | 0                   | Which frame to use when idle (sprite-specific options)                                  |
| `idle_animation`          | Boolean  | 0 or 1                                                     | 0                   | Enable idle animation                                                                   |
| `animation_speed`         | Integer  | 0–5000                                                     | 0                   | Frame duration in ms (0 = use `fps`)                                                    |
| `keypress_duration`       | Integer  | 50–5000                                                    | 100                 | Duration to display keypress animation (ms)                                             |
| `mirror_x`                | Boolean  | 0 or 1                                                     | 0                   | Flip cat horizontally (mirror across Y axis)                                            |
| `mirror_y`                | Boolean  | 0 or 1                                                     | 0                   | Flip cat vertically (mirror across X axis)                                              |
| `test_animation_duration` | Integer  | 0–5000                                                     | 0                   | Duration of test animation (ms) (deprecated, use `animation_speed`)                     |
| `test_animation_interval` | Integer  | 0–60                                                       | 0                   | Interval for test animation in seconds (0 = disabled, deprecated)                       |
| `fps`                     | Integer  | 1–144                                                      | 60                  | Animation frame rate                                                                    |
| `input_fps`               | Integer  | 0–144                                                      | 0                   | Input thread frame rate (0 = use `fps`)                                                 |
| `enable_scheduled_sleep`  | Boolean  | 0 or 1                                                     | 0                   | Enable scheduled sleep mode                                                             |
| `sleep_begin`             | String   | "00:00" – "23:59"                                          | "00:00"             | Start time of scheduled sleep (24h format)                                              |
| `sleep_end`               | String   | "00:00" – "23:59"                                          | "00:00"             | End time of scheduled sleep (24h format)                                                |
| `idle_sleep_timeout`      | Integer  | 0+                                                         | 0                   | Time of inactivity before entering sleep (0 = disabled) (in seconds)                    |
| `happy_kpm`               | Integer  | 0–10000                                                    | 0                   | Minimum keystrokes per minute to trigger happy animation (0 = disabled)                 |
| `keyboard_device`         | String   | Valid `/dev/input/*` path(s)                               | `/dev/input/event4` | Input device path (multiple entries allowed)                                            |
| `enable_antialiasing`     | Boolean  | 0 or 1                                                     | 1                   | Enable bilinear interpolation for smooth scaling (Bongocat and MS Agent only)           |
| `enable_debug`            | Boolean  | 0 or 1                                                     | 0                   | Enable debug logging                                                                    |
| `monitor`                 | String   | Monitor name                                               | Auto-detect         | Which monitor to display on (e.g., "eDP-1", "HDMI-A-1")                                 |
| `random`                  | Boolean  | 0 or 1                                                     | 0                   | Randomize `animation_index` (`animation_name` needs to be set as base sprite sheet set) |

#### Available Sprites (`animation_name`)

##### Bongocat 😺

- `bongocat`

##### MS Agent 📎

- `clippy`

<details>
<summary>More Agents</summary>

_Build with `-DFEATURE_MS_AGENT_EMBEDDED_ASSETS` and `-DFEATURE_MORE_MS_AGENT_EMBEDDED_ASSETS`, see [CMake](CMakeLists.txt)_

- `links`

</details>

##### Digimon 🦖

_If you build with ALL assets included you can void naming conflicts by using the full name: `dm:Greymon`, `dm20:Greymon`, `dmc:Greymon`_

###### Original ([`dm`](https://humulos.com/digimon/dm/))

<details>
<summary>Default Minimal Sprites (from dm Version 1) when no other dms are compiled</summary>

- `Botamon`
- `Koromon`
- `Agumon`
- `Betamon`
- `Greymon`
- `Tyranomon`
- `Devimon`
- `Meramon`
- `Airdramon`
- `Seadramon`
- `Numemon`
- `Metal Greymon`
- `Mamemon`
- `Monzaemon`

</details>


<details>

<summary>Full List</summary>

_Build with `-DFEATURE_ENABLE_DM_EMBEDDED_ASSETS` and `-DFEATURE_DM_EMBEDDED_ASSETS`, see [CMake](CMakeLists.txt)_

- `Agumon`
- `Airdramon`
- `Andromon`
- `Angemon`
- `Bakemon`
- `Betamon`
- `Birdramon`
- `Botamon`
- `Centalmon`
- `Cockatrimon`
- `Coelamon`
- `Coronamon`
- `Cyclomon`
- `Dark Tyranomon`
- `Deltamon`
- `Devidramon`
- `Devimon`
- `Digitamamon`
- `Drimogemon`
- `Elecmon`
- `Etemon`
- `Ex-Tyranomon`
- `Flymon`
- `Gabumon`
- `Garurumon`
- `Gazimon`
- `Giromon`
- `Gizamon`
- `Greymon`
- `Kabuterimon`
- `Koromon`
- `Kunemon`
- `Kuwagamon`
- `Leomon`
- `Mamemon`
- `Megadramon`
- `Meramon`
- `Metal Greymon`
- `Metal Mamemon`
- `Metal Tyranomon`
- `Mojyamon`
- `Monochromon`
- `Monzaemon`
- `Nanimon`
- `Nanomon`
- `Numemon`
- `Ogremon`
- `Pagumon`
- `Palmon`
- `Patamon`
- `Piccolomon`
- `Piyomon`
- `Poyomon`
- `Punimon`
- `Raremon`
- `Scumon`
- `Seadramon`
- `Shellmon`
- `Skull Greymon`
- `Tanemon`
- `Tokomon`
- `Tunomon`
- `Tuskmon`
- `Tyranomon`
- `Unimon`
- `Vademon`
- `Vegimon`
- `Whamon`
- `Yukidarumon`
- `Yuramon`

</details>


###### 20th Anniversary ([`dm20`](https://humulos.com/digimon/dm20/))

<details>
<summary>Full List</summary>

_Build with `-DFEATURE_ENABLE_DM_EMBEDDED_ASSETS` and `-DFEATURE_DM20_EMBEDDED_ASSETS`, see [CMake](CMakeLists.txt)_
_dm20 will replace dm, if both are enabled_

Should be the same as dm, but with some extras:

- `Aegisdramon`
- `Agumon`
- `Airdramon`
- `Alphamon`
- `Andromon`
- `Angemon`
- `Apollomon`
- `Babydmon`
- `Bakemon`
- `Bancho Mamemon`
- `Bao Hackmon`
- `Betamon`
- `Birdramon`
- `Blitz Greymon`
- `Botamon`
- `Breakdramon`
- `Centalmon`
- `Cockatrimon`
- `Coelamon`
- `Coredramon (Blue)`
- `Coredramon (Green)`
- `Coronamon`
- `Crescemon`
- `Cres Garurumon`
- `Cyclomon`
- `Dark Tyranomon`
- `Deltamon`
- `Devidramon`
- `Devimon`
- `Dianamon`
- `Digitamamon`
- `Dodomon`
- `Dorimon`
- `DORUgamon`
- `DORUguremon`
- `DORUmon`
- `Dracomon`
- `Drimogemon`
- `Duramon`
- `Durandamon`
- `Durandramon`
- `Elecmon`
- `Etemon`
- `Examon`
- `Ex-Tyranomon`
- `Firamon`
- `Flaremon`
- `Flymon`
- `Gabumon`
- `Garurumon`
- `Gazimon`
- `Giromon`
- `Gizamon`
- `Grace Novamon`
- `Greymon`
- `Groundramon`
- `Hackmon`
- `Hi Andromon`
- `Jesmon`
- `Jijimon`
- `Kabuterimon`
- `King Etemon`
- `Koromon`
- `Kunemon`
- `Kuwagamon`
- `Lekismon`
- `Leomon`
- `Lunamon`
- `Mamemon`
- `Megadramon`
- `Meicoomon`
- `Meicrackmon`
- `Meramon`
- `Metal Garurumon`
- `Metal Greymon`
- `Metal Mamemon`
- `Metal Tyranomon`
- `Mojyamon`
- `Monchromon`
- `Monochromon`
- `Monzaemon`
- `Mozaemon`
- `Mugendramon`
- `Nanimon`
- `Nanomon`
- `Numemon`
- `Nyaromon`
- `Ogremon`
- `Omegamon Alter S`
- `Omegamon`
- `Pagumon`
- `Pakumon`
- `Palmon`
- `Patamon`
- `Petitmon`
- `Piccolomon`
- `Pinochimon`
- `Pitchmon`
- `Piyomon`
- `Plotmon`
- `Poyomon`
- `Pukamon`
- `Punimon`
- `Raremon`
- `Rasielmon`
- `Rust Tyranomon`
- `Sakumon`
- `Sakuttomon`
- `Savior Hackmon`
- `Scumon`
- `Seadramon`
- `Shellmon`
- `Skull Greymon`
- `Skull Mammon`
- `Slayerdramon`
- `Taichi Metal Greymon`
- `Taichis Agumon`
- `Taichis Greymon`
- `Taichis Metal Greymon`
- `Taichis War Greymon`
- `Tanemon`
- `Titamon`
- `Tokomon`
- `Tsunomon`
- `Tunomon`
- `Tuskmon`
- `Tyranomon`
- `Unimon`
- `Vademon`
- `Vegimon`
- `War Greymon`
- `Were Garurumon`
- `Whamon`
- `Wingdramon`
- `Yamato Gabumon`
- `Yamatos Gabumon`
- `Yamatos Garurumon`
- `Yamatos Metal Garurumon`
- `Yamatos Were Garurumon`
- `Yukidarumon`
- `Yukimi Botamon`
- `Yuramon`
- `Zubaeagermon`
- `Zubamon`
- `Zurumon`

</details>


###### X ([`dmx`](https://humulos.com/digimon/dmx/))

<details>
<summary>Full List</summary>

_Build with `-DFEATURE_ENABLE_DM_EMBEDDED_ASSETS` and `-DFEATURE_DMX_EMBEDDED_ASSETS`, see [CMake](CMakeLists.txt)_


- `Agumon (Black) X`
- `Agumon X`
- `Allomon X`
- `Alphamon Ouryuken`
- `Alphamon`
- `Ancient Sphinxmon`
- `Angewomon X`
- `Anomalocarimon X`
- `Bagramon`
- `Barbamon X`
- `Beel Starmon X`
- `Beelzebumon X`
- `Belial Vamdemon`
- `Belphemon X`
- `Black Wargreymon X`
- `Cannon Beemon`
- `Cerberumon X`
- `Chaosdramon X`
- `Cherubimon (Vice) X`
- `Cherubimon (Virtue) X`
- `Chocomon`
- `Cho Hakkaimon`
- `Cocomon`
- `Craniummon X`
- `Crys Paledramon`
- `Cyberdramon X`
- `Damemon`
- `Dark Knightmon X`
- `Darkness Bagramon`
- `Dark Tyranomon X`
- `Demon X`
- `Diablomon X`
- `Dinorexmon`
- `Dinotigermon`
- `DORUgamon`
- `DORUguremon`
- `DORUmon`
- `Dracomon X`
- `Duftmon X`
- `Dukemon X`
- `Duskmon`
- `Dynasmon X`
- `Ebemon X`
- `Examon`
- `Examon X`
- `Filmon`
- `Gabumon X`
- `Gaioumon`
- `Gankoomon X`
- `Garudamon X`
- `Giga Seadramon`
- `Ginryumon`
- `Goddramon X`
- `Gomamon X`
- `Grademon`
- `Grand Darcumon`
- `Grandis Kuwagamon`
- `Growmon X`
- `Gummymon`
- `Herissmon`
- `Hexeblaumon`
- `Hisyaryumon`
- `Holydramon X`
- `Hououmon X`
- `Impmon X`
- `Jararchimon`
- `Jazamon`
- `Jazardmon`
- `Jesmon GX`
- `Jesmon X`
- `Justimon X`
- `Kaiser Leomon`
- `Keemon`
- `Keramon X`
- `Kiimon`
- `Kokuwamon X`
- `Kuwagamon X`
- `Lady Devimon X`
- `Leomon X`
- `Leviamon X`
- `Lilimon X`
- `Lilithmon X`
- `Lopmon X`
- `Lord Kightmon X`
- `Lucemon X`
- `Magidramon X`
- `Magnamon X`
- `Mamemon X`
- `Mame Tyramon`
- `Mammon X`
- `Mantaraymon X`
- `Megalo Growmon X`
- `Mega Seadramon X`
- `Mephismon X`
- `Meramon X`
- `Metal Fantomon`
- `Metal Garurumon X`
- `Metal Greymon (Virus) X`
- `Metal Greymon X`
- `Metallicdramon`
- `Metal Piranimon`
- `Metal Tyranomon X`
- `Minervamon X`
- `Monzaemon X`
- `Nefertimon X`
- `Noble Pumpmon`
- `Numemon X`
- `Ogremon X`
- `Ogudomon X`
- `Okuwamon X`
- `Omegamon X`
- `Omega Shoutmon X`
- `Omekamon`
- `Ophanimon Falldown Mode`
- `Ophanimon X`
- `Otamamon X`
- `Ouryumon`
- `Paledramon`
- `Palmon X`
- `Pegasmon X`
- `Platinum Numemon`
- `Plesiomon X`
- `Plotmon X`
- `Prince Mamemon X`
- `Pteranmon X`
- `Pumpmon`
- `Puttimon`
- `Rafflesimon`
- `Raihimon`
- `Rapidmon X`
- `Rasenmon Fury Mode`
- `Rasenmon`
- `Rekamon X`
- `Rhinomon X`
- `Rize Greymon X`
- `Rosemon X`
- `Ryudamon`
- `Sakuyamon X`
- `Sangoupmon`
- `Seadramon X`
- `Shakomon X`
- `Siesamon X`
- `Sistermon Blanc`
- `Skull Baluchimon`
- `Skull Mammon X`
- `Sleipmon X`
- `Stiffimon`
- `Tailmon X`
- `Tierriermon X`
- `Tiger Vespamon`
- `Tobcatmon`
- `Togemon X`
- `Tokomon X`
- `Triceramon X`
- `Tylomon X`
- `Tyranomon X`
- `Ulforce V-dramon X`
- `Ultimate Brachimon`
- `Valdurmon`
- `Vamdemon X`
- `Velgrman`
- `Voltobautamon`
- `War Greymon X`
- `Were Garurumon X`
- `Wizarmon X`
- `Yaamon`
- `Yatagaramon`
- `Zerimon`

</details>


##### Pokemon 🐭 (`pkmn`)

<details>
<summary>Full List</summary>

_Build with `-DFEATURE_PKMN_EMBEDDED_ASSETS`, see [CMake](CMakeLists.txt)_

- `Bulbasaur`
- `Ivysaur`
- `Venusaur`
- `Charmander`
- `Charmeleon`
- `Charizard`
- `Squirtle`
- `Wartortle`
- `Blastoise`
- `Caterpie`
- `Metapod`
- `Butterfree`
- `Weedle`
- `Kakuna`
- `Beedrill`
- `Pidgey`
- `Pidgeotto`
- `Pidgeot`
- `Rattata`
- `Raticate`
- `Spearow`
- `Fearow`
- `Ekans`
- `Arbok`
- `Pikachu`
- `Raichu`
- `Sandshrew`
- `Sandslash`
- `Nidoran-f`
- `Nidorina`
- `Nidoqueen`
- `Nidoran-m`
- `Nidorino`
- `Nidoking`
- `Clefairy`
- `Clefable`
- `Vulpix`
- `Ninetales`
- `Jigglypuff`
- `Wigglytuff`
- `Zubat`
- `Golbat`
- `Oddish`
- `Gloom`
- `Vileplume`
- `Paras`
- `Parasect`
- `Venonat`
- `Venomoth`
- `Diglett`
- `Dugtrio`
- `Meowth`
- `Persian`
- `Psyduck`
- `Golduck`
- `Mankey`
- `Primeape`
- `Growlithe`
- `Arcanine`
- `Poliwag`
- `Poliwhirl`
- `Poliwrath`
- `Abra`
- `Kadabra`
- `Alakazam`
- `Machop`
- `Machoke`
- `Machamp`
- `Bellsprout`
- `Weepinbell`
- `Victreebel`
- `Tentacool`
- `Tentacruel`
- `Geodude`
- `Graveler`
- `Golem`
- `Ponyta`
- `Rapidash`
- `Slowpoke`
- `Slowbro`
- `Magnemite`
- `Magneton`
- `Farfetchd`
- `Doduo`
- `Dodrio`
- `Seel`
- `Dewgong`
- `Grimer`
- `Muk`
- `Shellder`
- `Cloyster`
- `Gastly`
- `Haunter`
- `Gengar`
- `Onix`
- `Drowzee`
- `Hypno`
- `Krabby`
- `Kingler`
- `Voltorb`
- `Electrode`
- `Exeggcute`
- `Exeggutor`
- `Cubone`
- `Marowak`
- `Hitmonlee`
- `Hitmonchan`
- `Lickitung`
- `Koffing`
- `Weezing`
- `Rhyhorn`
- `Rhydon`
- `Chansey`
- `Tangela`
- `Kangaskhan`
- `Horsea`
- `Seadra`
- `Goldeen`
- `Seaking`
- `Staryu`
- `Starmie`
- `Mr-mime`
- `Scyther`
- `Jynx`
- `Electabuzz`
- `Magmar`
- `Pinsir`
- `Tauros`
- `Magikarp`
- `Gyarados`
- `Lapras`
- `Ditto`
- `Eevee`
- `Vaporeon`
- `Jolteon`
- `Flareon`
- `Porygon`
- `Omanyte`
- `Omastar`
- `Kabuto`
- `Kabutops`
- `Aerodactyl`
- `Snorlax`
- `Articuno`
- `Zapdos`
- `Moltres`
- `Dratini`
- `Dragonair`
- `Dragonite`
- `Mewtwo`
- `Mew`
- `Chikorita`
- `Bayleef`
- `Meganium`
- `Cyndaquil`
- `Quilava`
- `Typhlosion`
- `Totodile`
- `Croconaw`
- `Feraligatr`
- `Sentret`
- `Furret`
- `Hoothoot`
- `Noctowl`
- `Ledyba`
- `Ledian`
- `Spinarak`
- `Ariados`
- `Crobat`
- `Chinchou`
- `Lanturn`
- `Pichu`
- `Cleffa`
- `Igglybuff`
- `Togepi`
- `Togetic`
- `Natu`
- `Xatu`
- `Mareep`
- `Flaaffy`
- `Ampharos`
- `Bellossom`
- `Marill`
- `Azumarill`
- `Sudowoodo`
- `Politoed`
- `Hoppip`
- `Skiploom`
- `Jumpluff`
- `Aipom`
- `Sunkern`
- `Sunflora`
- `Yanma`
- `Wooper`
- `Quagsire`
- `Espeon`
- `Umbreon`
- `Murkrow`
- `Slowking`
- `Misdreavus`
- `Unown`
- `Wobbuffet`
- `Girafarig`
- `Pineco`
- `Forretress`
- `Dunsparce`
- `Gligar`
- `Steelix`
- `Snubbull`
- `Granbull`
- `Qwilfish`
- `Scizor`
- `Shuckle`
- `Heracross`
- `Sneasel`
- `Teddiursa`
- `Ursaring`
- `Slugma`
- `Magcargo`
- `Swinub`
- `Piloswine`
- `Corsola`
- `Remoraid`
- `Octillery`
- `Delibird`
- `Mantine`
- `Skarmory`
- `Houndour`
- `Houndoom`
- `Kingdra`
- `Phanpy`
- `Donphan`
- `Porygon2`
- `Stantler`
- `Smeargle`
- `Tyrogue`
- `Hitmontop`
- `Smoochum`
- `Elekid`
- `Magby`
- `Miltank`
- `Blissey`
- `Raikou`
- `Entei`
- `Suicune`
- `Larvitar`
- `Pupitar`
- `Tyranitar`
- `Lugia`
- `Ho-oh`
- `Celebi`
- `Treecko`
- `Grovyle`
- `Sceptile`
- `Torchic`
- `Combusken`
- `Blaziken`
- `Mudkip`
- `Marshtomp`
- `Swampert`
- `Poochyena`
- `Mightyena`
- `Zigzagoon`
- `Linoone`
- `Wurmple`
- `Silcoon`
- `Beautifly`
- `Cascoon`
- `Dustox`
- `Lotad`
- `Lombre`
- `Ludicolo`
- `Seedot`
- `Nuzleaf`
- `Shiftry`
- `Taillow`
- `Swellow`
- `Wingull`
- `Pelipper`
- `Ralts`
- `Kirlia`
- `Gardevoir`
- `Surskit`
- `Masquerain`
- `Shroomish`
- `Breloom`
- `Slakoth`
- `Vigoroth`
- `Slaking`
- `Nincada`
- `Ninjask`
- `Shedinja`
- `Whismur`
- `Loudred`
- `Exploud`
- `Makuhita`
- `Hariyama`
- `Azurill`
- `Nosepass`
- `Skitty`
- `Delcatty`
- `Sableye`
- `Mawile`
- `Aron`
- `Lairon`
- `Aggron`
- `Meditite`
- `Medicham`
- `Electrike`
- `Manectric`
- `Plusle`
- `Minun`
- `Volbeat`
- `Illumise`
- `Roselia`
- `Gulpin`
- `Swalot`
- `Carvanha`
- `Sharpedo`
- `Wailmer`
- `Wailord`
- `Numel`
- `Camerupt`
- `Torkoal`
- `Spoink`
- `Grumpig`
- `Spinda`
- `Trapinch`
- `Vibrava`
- `Flygon`
- `Cacnea`
- `Cacturne`
- `Swablu`
- `Altaria`
- `Zangoose`
- `Seviper`
- `Lunatone`
- `Solrock`
- `Barboach`
- `Whiscash`
- `Corphish`
- `Crawdaunt`
- `Baltoy`
- `Claydol`
- `Lileep`
- `Cradily`
- `Anorith`
- `Armaldo`
- `Feebas`
- `Milotic`
- `Castform`
- `Kecleon`
- `Shuppet`
- `Banette`
- `Duskull`
- `Dusclops`
- `Tropius`
- `Chimecho`
- `Absol`
- `Wynaut`
- `Snorunt`
- `Glalie`
- `Spheal`
- `Sealeo`
- `Walrein`
- `Clamperl`
- `Huntail`
- `Gorebyss`
- `Relicanth`
- `Luvdisc`
- `Bagon`
- `Shelgon`
- `Salamence`
- `Beldum`
- `Metang`
- `Metagross`
- `Regirock`
- `Regice`
- `Registeel`
- `Latias`
- `Latios`
- `Kyogre`
- `Groudon`
- `Rayquaza`
- `Jirachi`
- `Deoxys`
- `Turtwig`
- `Grotle`
- `Torterra`
- `Chimchar`
- `Monferno`
- `Infernape`
- `Piplup`
- `Prinplup`
- `Empoleon`
- `Starly`
- `Staravia`
- `Staraptor`
- `Bidoof`
- `Bibarel`
- `Kricketot`
- `Kricketune`
- `Shinx`
- `Luxio`
- `Luxray`
- `Budew`
- `Roserade`
- `Cranidos`
- `Rampardos`
- `Shieldon`
- `Bastiodon`
- `Burmy`
- `Wormadam`
- `Mothim`
- `Combee`
- `Vespiquen`
- `Pachirisu`
- `Buizel`
- `Floatzel`
- `Cherubi`
- `Cherrim`
- `Shellos`
- `Gastrodon`
- `Ambipom`
- `Drifloon`
- `Drifblim`
- `Buneary`
- `Lopunny`
- `Mismagius`
- `Honchkrow`
- `Glameow`
- `Purugly`
- `Chingling`
- `Stunky`
- `Skuntank`
- `Bronzor`
- `Bronzong`
- `Bonsly`
- `Mime-jr`
- `Happiny`
- `Chatot`
- `Spiritomb`
- `Gible`
- `Gabite`
- `Garchomp`
- `Munchlax`
- `Riolu`
- `Lucario`
- `Hippopotas`
- `Hippowdon`
- `Skorupi`
- `Drapion`
- `Croagunk`
- `Toxicroak`
- `Carnivine`
- `Finneon`
- `Lumineon`
- `Mantyke`
- `Snover`
- `Abomasnow`
- `Weavile`
- `Magnezone`
- `Lickilicky`
- `Rhyperior`
- `Tangrowth`
- `Electivire`
- `Magmortar`
- `Togekiss`
- `Yanmega`
- `Leafeon`
- `Glaceon`
- `Gliscor`
- `Mamoswine`
- `Porygon-z`
- `Gallade`
- `Probopass`
- `Dusknoir`
- `Froslass`
- `Rotom`
- `Uxie`
- `Mesprit`
- `Azelf`
- `Dialga`
- `Palkia`
- `Heatran`
- `Regigigas`
- `Giratina`
- `Cresselia`
- `Phione`
- `Manaphy`
- `Darkrai`
- `Shaymin`
- `Arceus`
- `Victini`
- `Snivy`
- `Servine`
- `Serperior`
- `Tepig`
- `Pignite`
- `Emboar`
- `Oshawott`
- `Dewott`
- `Samurott`
- `Patrat`
- `Watchog`
- `Lillipup`
- `Herdier`
- `Stoutland`
- `Purrloin`
- `Liepard`
- `Pansage`
- `Simisage`
- `Pansear`
- `Simisear`
- `Panpour`
- `Simipour`
- `Munna`
- `Musharna`
- `Pidove`
- `Tranquill`
- `Unfezant`
- `Blitzle`
- `Zebstrika`
- `Roggenrola`
- `Boldore`
- `Gigalith`
- `Woobat`
- `Swoobat`
- `Drilbur`
- `Excadrill`
- `Audino`
- `Timburr`
- `Gurdurr`
- `Conkeldurr`
- `Tympole`
- `Palpitoad`
- `Seismitoad`
- `Throh`
- `Sawk`
- `Sewaddle`
- `Swadloon`
- `Leavanny`
- `Venipede`
- `Whirlipede`
- `Scolipede`
- `Cottonee`
- `Whimsicott`
- `Petilil`
- `Lilligant`
- `Basculin`
- `Sandile`
- `Krokorok`
- `Krookodile`
- `Darumaka`
- `Darmanitan`
- `Maractus`
- `Dwebble`
- `Crustle`
- `Scraggy`
- `Scrafty`
- `Sigilyph`
- `Yamask`
- `Cofagrigus`
- `Tirtouga`
- `Carracosta`
- `Archen`
- `Archeops`
- `Trubbish`
- `Garbodor`
- `Zorua`
- `Zoroark`
- `Minccino`
- `Cinccino`
- `Gothita`
- `Gothorita`
- `Gothitelle`
- `Solosis`
- `Duosion`
- `Reuniclus`
- `Ducklett`
- `Swanna`
- `Vanillite`
- `Vanillish`
- `Vanilluxe`
- `Deerling`
- `Sawsbuck`
- `Emolga`
- `Karrablast`
- `Escavalier`
- `Foongus`
- `Amoonguss`
- `Frillish`
- `Jellicent`
- `Alomomola`
- `Joltik`
- `Galvantula`
- `Ferroseed`
- `Ferrothorn`
- `Klink`
- `Klang`
- `Klinklang`
- `Tynamo`
- `Eelektrik`
- `Eelektross`
- `Elgyem`
- `Beheeyem`
- `Litwick`
- `Lampent`
- `Chandelure`
- `Axew`
- `Fraxure`
- `Haxorus`
- `Cubchoo`
- `Beartic`
- `Cryogonal`
- `Shelmet`
- `Accelgor`
- `Stunfisk`
- `Mienfoo`
- `Mienshao`
- `Druddigon`
- `Golett`
- `Golurk`
- `Pawniard`
- `Bisharp`
- `Bouffalant`
- `Rufflet`
- `Braviary`
- `Vullaby`
- `Mandibuzz`
- `Heatmor`
- `Durant`
- `Deino`
- `Zweilous`
- `Hydreigon`
- `Larvesta`
- `Volcarona`
- `Cobalion`
- `Terrakion`
- `Virizion`
- `Tornadus`
- `Thundurus`
- `Reshiram`
- `Zekrom`
- `Landorus`
- `Kyurem`
- `Keldeo`
- `Meloetta`
- `Genesect`

</details>



## 🔧 Usage

### Command Line Options

```bash
bongocat [OPTIONS]

Options:
  -h, --help            Show this help message
  -v, --version         Show version information
  -c, --config          Specify config file (default: bongocat.conf)
  -w, --watch-config    Watch config file for changes and reload automatically
  -o, --output-name     Specify output name (overwrite output_name from config)
  -t, --toggle          Toggle bongocat on/off (start if not running, stop if running)
  --random              Randomize animation_name at start up
  --strict              Only start up with a valid config and valid parameter
```

### Examples

```bash
# Basic usage
bongocat

# With hot-reload (recommended)
bongocat --watch-config

# Custom config with hot-reload
bongocat --config ~/.config/bongocat.conf --watch-config

# Debug mode
bongocat --watch-config --config bongocat.conf

# Toggle mode
bongocat --toggle

# Custom config with hot-reload and custom output_name
bongocat --watch-config --output-name DP-2 --config ~/.config/bongocat.conf
```

## 🛠️ Building from Source

### Prerequisites

**Required:**

- Wayland compositor with layer shell support
- C23/C++23 compiler (GCC 15+ or Clang 19+)
- Make or CMake
- libwayland-client
- wayland-protocols
- wayland-scanner

### Build Process

```bash
# Clone repository
git clone https://github.com/furudbat/wayland-vpets.git
cd wayland-vpets

# Build (production)
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build

# Build (debug)
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build

# Clean
cmake --build build --target clean
```

The build process automatically:

1. Generates Wayland protocol files
2. Compiles with optimizations and security hardening
3. Embeds assets directly in the binary
4. Links with required libraries

## 🔍 Device Discovery

The `bongocat-find-devices` tool provides professional input device analysis with a clean, user-friendly interface:

```bash
$ bongocat-find-devices

╔══════════════════════════════════════════════════════════════════╗
║ Wayland Bongo Cat - Input Device Discovery v2.4.0                ║
╚══════════════════════════════════════════════════════════════════╝

[SCAN] Scanning for input devices...

[DEVICES] Found Input Devices:
┌─────────────────────────────────────────────────────────────────┐
│ Device: AT Translated Set 2 keyboard                            │
│ Path:   /dev/input/event4                                       │
│ Type:   Keyboard                                                │
│ Status: [OK] Accessible                                         │
└─────────────────────────────────────────────────────────────────┘

┌─────────────────────────────────────────────────────────────────┐
│ Device: Logitech MX Keys                                        │
│ Path:   /dev/input/event20                                      │
│ Type:   Keyboard (Bluetooth)                                    │
│ Status: [OK] Accessible                                         │
└─────────────────────────────────────────────────────────────────┘

[CONFIG] Configuration Suggestions:
Add these lines to your bongocat.conf:

keyboard_device=/dev/input/event4   # AT Translated Set 2 keyboard
keyboard_device=/dev/input/event20  # Logitech MX Keys
```

### Advanced Features

```bash
# Show all input devices (including mice, touchpads)
bongocat-find-devices --all

# Generate complete configuration file
bongocat-find-devices --generate-config > bongocat.conf

# Test device responsiveness (requires root)
sudo bongocat-find-devices --test

# Show detailed device information
bongocat-find-devices --verbose

# Get help and usage information
bongocat-find-devices --help
```

### Key Features

- **Smart Detection** - Automatically identifies keyboards vs other input devices
- **Device Classification** - Distinguishes between built-in, Bluetooth, and USB keyboards
- **Permission Checking** - Verifies device accessibility and provides fix suggestions
- **Config Generation** - Creates ready-to-use configuration snippets
- **Device Testing** - Integrated evtest functionality for troubleshooting
- **Professional UI** - Clean, colorized output with status indicators
- **Error Handling** - Comprehensive error messages and troubleshooting guidance

## 📊 Performance

### System Requirements

This program is lightweight and runs even on very modern desktop systems.  
Minimal builds require just a few MB of RAM, while asset-heavy builds may use more memory.

## 🖥️ System Requirements

|                | Minimum                                                  | Recommended                                                                  |
|----------------|----------------------------------------------------------|------------------------------------------------------------------------------|
| **CPU**        | Any modern **x86_64** or **ARM64** processor (SSE2/NEON) | Dual-core **x86_64** or **ARM64** processor                                  |
| **RAM**        | **10 MB free** (minimal build with minimal assets)       | **64 MB free** (full builds with all assets, preloaded, and config overhead) |
| **Storage**    | **1 MB free** (binary + config files)                    | **5 MB free** (multiple binaries/builds + config files)                      |
| **Compositor** | Wayland with **wlr-layer-shell** protocol support        | Modern Wayland compositor (Sway, Hyprland, Wayfire, KDE Plasma 6)            |


### Tested Compositors

- ✅ **Hyprland** - Full support
- ✅ **Sway** - Full support
- ✅ **Wayfire** - Compatible
- ✅ **KDE Wayland** - Compatible
- ❌ **GNOME Wayland** - Unsupported

## 🐛 Troubleshooting

### Common Issues

<details>
<summary>Permission denied accessing /dev/input/eventX</summary>

**Solution:**

```bash
# Add user to input group (recommended)
sudo usermod -a -G input $USER
# Log out and back in

# Or create udev rule
echo 'KERNEL=="event*", GROUP="input", MODE="0664"' | sudo tee /etc/udev/rules.d/99-input.rules
sudo udevadm control --reload-rules
```

</details>

<details>
<summary>Keyboard input not detected</summary>

**Diagnosis:**

```bash
# Find correct device
bongocat-find-devices

# Test device manually
sudo evtest /dev/input/event4
```

**Solution:** Update `keyboard_device` in `bongocat.conf` with correct path.

</details>

<details>
<summary>Overlay not visible or clickable</summary>

**Check:**

- Ensure compositor supports `wlr-layer-shell-unstable-v1`
- Verify `WAYLAND_DISPLAY` environment variable is set
- Try different `overlay_opacity` values

**Tested compositors:** Hyprland, Sway, Wayfire

</details>

<details>
<summary>Multi-monitor setup issues</summary>

**Finding monitor names:**

```bash
# Using wlr-randr (recommended)
wlr-randr

# Using swaymsg (Sway only)
swaymsg -t get_outputs

# Check bongocat logs for detected monitors
bongocat --watch-config  # Look for "xdg-output name received" messages
```

**Configuration:**

```ini
# Specify exact monitor name
monitor=eDP-1        # Laptop screen
monitor=HDMI-A-1     # External HDMI monitor
monitor=DP-1         # DisplayPort monitor
```

**Troubleshooting:**

- If monitor name is wrong, bongocat falls back to first available monitor
- Monitor names are case-sensitive
- Remove or comment out `monitor=` line to use auto-detection
</details>

<details>
<summary>Build errors</summary>

**Common fixes:**

- Install development packages: `libwayland-dev wayland-protocols`
- Ensure C23/C++23 compiler: GCC 15+ or Clang 19+ _(requires [`#embed`](https://en.cppreference.com/w/c/preprocessor/embed.html) feature)_
- Install `wayland-scanner` package
</details>

### Getting Help

1. Enable debug logging: `bongocat --watch-config` (ensure `enable_debug=1`)
2. Check compositor compatibility
3. Verify all dependencies are installed
4. Test with minimal configuration

## 🏗️ Architecture

### Project Structure

```
wayland-vpets/
├── src/                 # Source code
│   ├── main.c          # Application entry point
│   ├── config.c        # Configuration management
│   ├── config_watcher.c # Hot-reload system (v1.2.1)
│   ├── input.c         # Input device monitoring
│   ├── wayland.c       # Wayland protocol handling
│   └── ...
├── include/            # Header files
├── scripts/            # Build and utility scripts
├── assets/             # Animation frames
├── protocols/          # Generated Wayland protocols
└── nix/               # NixOS integration
```

## 🤝 Contributing

This project follows industry best practices with a modular architecture. Contributions are welcome!

### Development Setup

```bash
git clone https://github.com/furudbat/wayland-vpets.git
cd wayland-vpets
make debug
```

### Code Standards

- C23/C++23 standard compliance
- Comprehensive error handling
- Memory safety with leak detection
- Extensive documentation

#### Moving to C++

I'm moving this Project ~~a little bit~~ to C++.

* using modern C++23/C23 compiler (required for `#embed`)
* thread-safe Logging
* use assert and static_assert (Preconditions, postconditions, invariants.)
* use mmap for multi-threading and shared memory
* use Mutex and LockGuard
* prefer stack to heap
  * use heap when: Mutex is used in structs or other non-movable objects
  * use mmap for shared memory
  * dynamics arrays like buffers
* **reduce usage of pre-processor** - replace `#define` with `constexpr`
* use `ref&` instead of pointer parameter (not-nullable)
* use `nullptr` instead of `NULL`
* **Memory Management** - Simple Wrapper for malloc/free calls
  * move semantics
  * reduce manually clean up
  * system memory and resources use RAII
    * Mutex
    * MMap + MMapArray (for shared memory)
    * MMap mapped Files (Buffers)
    * malloc/free
    * FileDescriptor
* use `enum class`
* use default and brace initialization
* It's still C with Linux + Wayland libraries under the hood
* ~~NO STL~~ - Almost NO STL - I had to use `<type_traits>` :(
* NO classes (except for RAII)
  * **Rule of five** 😬
* keep templates at minimum
* move big assets (like embedded images) into its own TU (cpp file) and get needed asset from a function call
* reduce globals, use context structs and pass parameter
* use C atomic style (`atomic_store` and `atomic_load`), `atomic_bool`, `atomic_int` is still fine
* fixed-size types
* try to allocate upfront, before starting a thread (see ~~`init` or~~`create` functions)
* prefer `create` functions with RVO, instead of `init` with out-ref-parameter
* stop (all) threads before releasing memory

## 📄 License

MIT License - see [LICENSE](LICENSE) file for details.

## 🙏 Acknowledgments

Built with ❤️ for the Wayland community. Special thanks to:

- Redditor: [u/akonzu](https://www.reddit.com/user/akonzu/) for the inspiration
- [@Shreyabardia](https://github.com/Shreyabardia) for the beautiful custom-drawn bongo cat artwork
- All the contributors and users
- [Waybar](https://github.com/Alexays/Waybar)


Pokémon are owned by Nintendo, Creatures Inc. and GAME FREAK Inc.
Digimon and all related characters, and associated images are owned by Bandai Co., Ltd, Akiyoshi Hongo, and Toei Animation Co., Ltd.
Clippy and other MS Agents are owed by Microsoft.
This project is **free**, **non-commercial** and not associated with these entities.
See [COPYRIGHT](assets/COPYRIGHT.md) for more details.

---

**₍^. .^₎ Wayland Bongo Cat Overlay v3.0.0** - Making desktops more delightful, one keystroke at a time!
Now with Digimon V-Pets, Clippy and Pokémon.
