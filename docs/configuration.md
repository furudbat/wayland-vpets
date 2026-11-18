### Config File Location

Without `--config`, the first readable file is used:

1. `$XDG_CONFIG_HOME/bongocat/bongocat.conf`
2. `~/.config/bongocat/bongocat.conf`
3. `./bongocat.conf` (current directory)

If none is found, the defaults are used.  
With `--config -` you can read the configuration from standard input, like this: `echo "" | bongocat --config -`

**Format:**
Each line is `key=value`; comments start with `#`.
Boolean options accept `0`/`1`, `false`/`true`, `no`/`yes` or `off`/`on`.
```ini
cat_height=60
cat_x_offset=0
cat_y_offset=10
enable_debug=0
```

### Options Reference

| **Option**                   | **Values**                                                         | **Default**   | **Description**                                                                           |
|------------------------------|--------------------------------------------------------------------|---------------|-----------------------------------------------------------------------------------------------|
| `cat_height`                 | 8–1024                                                             | 40            | Height of the pet in pixels (width auto-calculated to maintain aspect ratio)            |
| `cat_x_offset`               | -16000 to 16000                                                    | 100           | Horizontal offset from center (behavior depends on `cat_align`)                           |
| `cat_y_offset`               | -16000 to 16000                                                    | 10            | Vertical offset from center (positive=down, negative=up)                                  |
| `cat_align`                  | "center", "left", "right"                                          | "center"      | Horizontal alignment of cat inside overlay bar                                            |
| `overlay_height`             | 16–2560                                                            | 50            | Height of the entire overlay bar                                                          |
| `overlay_position`           | "top" or "bottom"                                                  | "top"         | Position of overlay on screen                                                             |
| `overlay_opacity`            | 0–255                                                              | 0             | Background opacity (0=transparent, 255=opaque)                                            |
| `overlay_layer`              | "overlay", "top", "bottom" or "background"                         | "top"         | Surface layer of overlay on screen (`layer` is a deprecated alias)                        |
| `screen_width`               | 0–16000                                                            | 0             | Override the detected screen width in pixels (0 = auto-detect)                            |
| `disable_fullscreen_hide`    | 0 or 1                                                             | 0             | Keep the overlay visible when a fullscreen window is detected                             |
| `animation_name`             | "bongocat", `<digimon name>`, "clippy", `<pokemon name>` or "neko" | "bongocat"    | Name of the V-Pet sprite (see list below)                                                 |
| `invert_color`               | 0 or 1                                                             | 0             | Invert color (useful for white digimon sprites & dark mode)                               |
| `padding_x`                  | 0–16000                                                            | 0             | Horizontal padding (pixels) around each frame when loading the sprite sheet               |
| `padding_y`                  | 0–16000                                                            | 0             | Vertical padding (pixels) around each frame when loading the sprite sheet                 |
| `idle_frame`                 | 0–3 (varies by sprite type)                                        | 0             | Which frame to use when idle (sprite-specific options)                                    |
| `idle_animation`             | 0 or 1                                                             | 0             | Enable idle animation                                  |
| `animation_speed`            | 0–60000                                                            | 0             | Frame duration in ms (0 = use `fps`)                                                      |
| `keypress_duration`          | 0–60000                                                            | 100           | Duration to display keypress animation (ms)                                               |
| `enable_hand_mapping`        | 0 or 1                                                             | 1             | Left half of the keyboard triggers the left hand, right half the right hand (Bongocat)    |
| `mirror_x`                   | 0 or 1                                                             | 0             | Flip cat horizontally (mirror across Y axis)                                              |
| `mirror_y`                   | 0 or 1                                                             | 0             | Flip cat vertically (mirror across X axis)                                                |
| `test_animation_duration`    | 0–60000                                                            | 0             | Duration of test animation (ms) (deprecated, use `animation_speed`)                       |
| `test_animation_interval`    | 0+                                                                 | 0             | Interval for test animation in seconds (0 = disabled, deprecated)                         |
| `fps`                        | 1–540                                                              | 60            | Animation frame rate                                                                      |
| `input_fps`                  | 0–540                                                              | 0             | Input thread frame rate (0 = use `fps`)                                                   |
| `enable_scheduled_sleep`     | 0 or 1                                                             | 0             | Enable scheduled sleep mode                                                               |
| `sleep_begin`                | "00:00" – "23:59"                                                  | "00:00"       | Start time of scheduled sleep (24h format)                                                |
| `sleep_end`                  | "00:00" – "23:59"                                                  | "00:00"       | End time of scheduled sleep (24h format)                                                  |
| `idle_sleep_timeout`         | 0–2592000                                                          | 0             | Time of inactivity before entering sleep (0 = disabled) (in seconds)                      |
| `happy_kpm`                  | 0–10000                                                            | 0             | Minimum keystrokes per minute to trigger happy animation (0 = disabled)                   |
| `keyboard_device`            | Valid `/dev/input/*` path(s)                                       | \<No Device\> | Input device path (multiple entries allowed, alias: `keyboard_devices`)                   |
| `keyboard_name`              | Device name (substring)                                            | \<None\>      | Add every input device whose name contains this text (multiple entries allowed)           |
| `hotplug_scan_interval`      | 0–3600                                                             | 30            | How often to rescan for new input devices (in seconds) (0 = scan once at startup)         |
| `enable_antialiasing`        | 0 or 1                                                             | 1             | Enable bilinear interpolation for smooth scaling (Bongocat and MS Agent only)             |
| `enable_debug`               | 0 or 1                                                             | 0             | Enable debug logging (default is 1 in debug builds)                                       |
| `monitor`                    | Monitor name                                                       | Auto-detect   | Which monitor to display on (e.g., "eDP-1", "HDMI-A-1") (alias: `output_name`)            |
| `random`                     | 0 or 1                                                             | 0             | Randomize `animation_index` (`animation_name` needs to be set as base sprite sheet set)   |
| `random_on_reload`           | 0 or 1                                                             | 0             | Randomize `animation_index` when reloading config (`random` needs to be `1`)              |
| `update_rate`                | 0–3600000                                                          | 0             | Check (CPU) states rate (0 = disabled) (in milliseconds)                                  |
| `cpu_threshold`              | 0–100                                                              | 0             | Threshold of CPU usage for triggering work animation (0 = disabled)                       |
| `cpu_running_factor`         | 0.0–50.0                                                           | 0             | Speed up factor for 100% CPU, it's linear so the animation slowly speed up (0 = disabled) |
| `movement_radius`            | 0–8000                                                             | 0             | Radius of moving area (0 = disabled)                                                      |
| `movement_speed`             | 0–60000                                                            | 0             | Movement speed (0 = disabled)                                                             |
| `movement_wait_factor`       | 0.0+                                                               | 5.1           | Pause after a movement: `movement_speed * movement_wait_factor`                           |
| `enable_movement_debug`      | 0 or 1                                                             | 0             | Show Movement area                                                                        |
| `audio`                      | 0 or 1                                                             | 0             | React to playing audio (PipeWire sink monitor, requires audio module) |
| `audio_sink`                 | PipeWire sink name                                                 | (default)     | Sink to listen to (`pactl list short sinks`), empty = system default sink                 |
| `audio_happy_peak`           | 0.0–1.0                                                            | 0.6           | Fraction of bars reaching their top at the same time that triggers happy (0 = disabled)   |
| `audio_fps`                  | 0–540                                                              | 0             | Audio thread update rate (0 = use `fps`)                                                  |
| `evolution`                  | "none", "normal", "program_start", "uptime"                    | "none"        | Animation change over time (see below)                                                    |
| `evolution_speed_factor`     | 0.0–5000.0                                                         | 1.0           | Speed up factor for evolution time (0 is reset to 1.0 when `evolution` is enabled)        |

#### Available Sprites (`animation_name`)

See man pages for more details and full list:

- [Bongocat 😺](fragments/set-bongocat.md)
- [MS Agent 📎](fragments/set-ms-agent.md) 
- [Pokémon 🐭](fragments/set-pkmn.md)
- [Misc 🐈‍](fragments/set-misc.md)

##### Bongocat 😺

SVG-based rendering (pixel-perfect at any size). No need for `enable_antialiasing`.

##### Digimon - Variety of V-Pets

- [Original](fragments/set-dm.md)
- [Pendulum Original](fragments/set-pen.md)
- [20th Anniversary](fragments/set-dm20.md)
- [Pendulum Ver.20th](fragments/set-pen20.md)
- [X](fragments/set-dmx.md)
- [Colored](fragments/set-dmc.md)
- [Custom Colored (fan sprites)](fragments/set-dmall.md)

> When building with ALL assets, use full names to avoid conflicts: `dm:Greymon`, `dm20:Greymon`, `dmc:Greymon`

##### Pokémon - up to Gen 5 + Mystery Dungeon sprites

`wpets-all` and `wpets-pkmn` include up to Gen. 5.
[Pokémon Mystery Dungeon](fragments/set-pmd.md) sprites are bundled in `wpets-pkmn`, not in `wpets-all`: `pmd:Pikachu`

_Best to disable antialiasing (`enable_antialiasing=0`) for pixel-perfect scaling_

##### MS Agent - Your Classic Microsoft Companion

Only Clippy is bundled in `wpets-all`; the other MS Agent friends (like `Links`) are bundled in `wpets-ms-agent`.


#### Audio (`audio`)

The pet reacts to audio playing on a PipeWire sink (requires a build with `-DENABLE_AUDIO_MODULE=ON`, needs `libpipewire-0.3` and `fftw3`).
The pet switches to the happy animation when enough visualizer bars peak at the same time (`audio_happy_peak`).

```ini
audio=1
audio_sink=            # empty = default sink, see `pactl list short sinks`
audio_happy_peak=0.6
audio_fps=30           # 0 = use fps
```

See [examples/audio-digimon.bongocat.conf](../examples/audio-digimon.bongocat.conf) for a full config.


#### Evolution (`evolution`)

Sprites change form over time.
Trigger modes:
 - `none` - disabled
 - `normal` - measure time since last evolution
 - `program_start` - since program start
 - `uptime` - since uptime

_Only available for Digimon and Pokémon._ 
See [evolution docs](fragments/evol-all.md).

#### Custom Sprite Sheet (`custom_...`)

Use a custom sprite sheet at runtime to make your own pets.

Set `animation_name=custom` and point `custom_sprite_sheet_filename` to your PNG sprite sheet. Full frame/row control per animation state:

| **Option**                                  | **Values**         | **Default**      | **Description**                                                                      |
|---------------------------------------------|--------------------|------------------|--------------------------------------------------------------------------------------|
| `animation_name`                            | `"custom"`         |                  | Must be `"custom"` for custom-options to work                                        |
| `custom_sprite_sheet_filename`              | Path to image file |                  | Path to the custom sprite sheet image (**must be png**)                              |
| `custom_rows`                               | 1-17               | auto             | Total number of rows in the sprite sheet (auto = derived from the `*_row` options)   |
| `custom_idle_frames`                        | 0-512              | 0 (disabled)     | Number of frames for idle animation                                                  |
| `custom_boring_frames`                      | 0-512              | 0 (disabled)     | Number of frames for boring animation                                                |
| `custom_start_writing_frames`               | 0-512              | 0 (disabled)     | Number of frames for start writing animation                                         |
| `custom_writing_frames`                     | 0-512              | 0 (disabled)     | Number of frames for writing animation                                               |
| `custom_end_writing_frames`                 | 0-512              | 0 (disabled)     | Number of frames for end writing animation                                           |
| `custom_happy_frames`                       | 0-512              | 0 (disabled)     | Number of frames for happy animation                                                 |
| `custom_asleep_frames`                      | 0-512              | 0 (disabled)     | Number of frames for falling asleep animation                                        |
| `custom_sleep_frames`                       | 0-512              | 0 (disabled)     | Number of frames for sleeping animation                                              |
| `custom_wake_up_frames`                     | 0-512              | 0 (disabled)     | Number of frames for waking up animation                                             |
| `custom_start_working_frames`               | 0-512              | 0 (disabled)     | Number of frames for start working animation                                         |
| `custom_working_frames`                     | 0-512              | 0 (disabled)     | Number of frames for working animation                                               |
| `custom_end_working_frames`                 | 0-512              | 0 (disabled)     | Number of frames for end working animation                                           |
| `custom_start_moving_frames`                | 0-512              | 0 (disabled)     | Number of frames for start moving animation                                          |
| `custom_moving_frames`                      | 0-512              | 0 (disabled)     | Number of frames for moving animation                                                |
| `custom_end_moving_frames`                  | 0-512              | 0 (disabled)     | Number of frames for end moving animation                                            |
| `custom_start_running_frames`               | 0-512              | 0 (disabled)     | Number of frames for start running animation                                         |
| `custom_running_frames`                     | 0-512              | 0 (disabled)     | Number of frames for running animation                                               |
| `custom_end_running_frames`                 | 0-512              | 0 (disabled)     | Number of frames for end running animation                                           |
| `custom_toggle_writing_frames`              | 0 or 1             | -1 (auto)        | Toggle writing frames when writing (`custom_writing_frames` needs to be `2`)         |
| `custom_toggle_writing_frames_random`       | 0 or 1             | -1 (auto)        | Randomize writing frame when start writing (`custom_writing_frames` needs to be `2`) |
| `custom_mirror_x_moving`                    | 0 or 1             | -1 (ignore)      | Mirror frames horizontally when moving                                               |
| `custom_idle_row`                           | 1-18               | -1 (auto)        | Row nr for idle animation in sprite sheet                                            |
| `custom_boring_row`                         | 1-18               | -1 (auto)        | Row nr for boring animation                                                          |
| `custom_start_writing_row`                  | 1-18               | -1 (auto)        | Row nr for start writing animation                                                   |
| `custom_writing_row`                        | 1-18               | -1 (auto)        | Row nr for writing animation                                                         |
| `custom_end_writing_row`                    | 1-18               | -1 (auto)        | Row nr for end writing animation                                                     |
| `custom_happy_row`                          | 1-18               | -1 (auto)        | Row nr for happy animation                                                           |
| `custom_asleep_row`                         | 1-18               | -1 (auto)        | Row nr for asleep animation                                                          |
| `custom_sleep_row`                          | 1-18               | -1 (auto)        | Row nr for sleep animation                                                           |
| `custom_wake_up_row`                        | 1-18               | -1 (auto)        | Row nr for wake-up animation                                                         |
| `custom_start_working_row`                  | 1-18               | -1 (auto)        | Row nr for start working animation                                                   |
| `custom_working_row`                        | 1-18               | -1 (auto)        | Row nr for working animation                                                         |
| `custom_end_working_row`                    | 1-18               | -1 (auto)        | Row nr for end working animation                                                     |
| `custom_start_moving_row`                   | 1-18               | -1 (auto)        | Row nr for start moving animation                                                    |
| `custom_moving_row`                         | 1-18               | -1 (auto)        | Row nr for moving animation                                                          |
| `custom_end_moving_row`                     | 1-18               | -1 (auto)        | Row nr for end moving animation                                                      |
| `custom_start_running_row`                  | 1-18               | -1 (auto)        | Row nr for start running animation                                                   |
| `custom_running_row`                        | 1-18               | -1 (auto)        | Row nr for running animation                                                         |
| `custom_end_running_row`                    | 1-18               | -1 (auto)        | Row nr for end running animation                                                     |
| `custom_start_evolving_row`                 | 1-18               | -1 (auto)        | Row nr for start evolving animation (requires evolution support)                     |
| `custom_evolving_row`                       | 1-18               | -1 (auto)        | Row nr for evolving animation (requires evolution support)                           |
| `custom_after_evolving_row`                 | 1-18               | -1 (auto)        | Row nr for after evolving animation (requires evolution support)                     |


_You can find more config- and sprite-sheet examples in [examples/custom-sprite-sheets](../examples/custom-sprite-sheets)._
