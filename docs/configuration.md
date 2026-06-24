### Options Reference

| **Option**                   | **Values**                                                         | **Default**   | **Description**                                                                           |
|------------------------------|--------------------------------------------------------------------|---------------|-------------------------------------------------------------------------------------------|
| `cat_height`                 | 8–1024                                                             | 40            | Height of bongo cat in pixels (width auto-calculated to maintain aspect ratio)            |
| `cat_x_offset`               | -16000 to 16000                                                    | 100           | Horizontal offset from center (behavior depends on `cat_align`)                           |
| `cat_y_offset`               | -16000 to 16000                                                    | 10            | Vertical offset from center (positive=down, negative=up)                                  |
| `cat_align`                  | "center", "left", "right"                                          | "center"      | Horizontal alignment of cat inside overlay bar                                            |
| `overlay_height`             | 16–2560                                                            | 50            | Height of the entire overlay bar                                                          |
| `overlay_position`           | "top" or "bottom"                                                  | "top"         | Position of overlay on screen                                                             |
| `overlay_opacity`            | 0–255                                                              | 60            | Background opacity (0=transparent, 255=opaque)                                            |
| `overlay_layer`              | "overlay", "top", "bottom" or "background"                         | "overlay"     | Surface layer of overlay on screen                                                        |
| `animation_name`             | "bongocat", `<digimon name>`, "clippy", `<pokemon name>` or "neko" | "bongocat"    | Name of the V-Pet sprite (see list below)                                                 |
| `invert_color`               | 0 or 1                                                             | 0             | Invert color (useful for white digimon sprites & dark mode)                               |
| `idle_frame`                 | 0–2 (varies by sprite type)                                        | 0             | Which frame to use when idle (sprite-specific options)                                    |
| `idle_animation`             | 0 or 1                                                             | 0             | Enable idle animation                                                                     |
| `animation_speed`            | 0–5000                                                             | 0             | Frame duration in ms (0 = use `fps`)                                                      |
| `keypress_duration`          | 50–5000                                                            | 100           | Duration to display keypress animation (ms)                                               |
| `mirror_x`                   | 0 or 1                                                             | 0             | Flip cat horizontally (mirror across Y axis)                                              |
| `mirror_y`                   | 0 or 1                                                             | 0             | Flip cat vertically (mirror across X axis)                                                |
| `test_animation_duration`    | 0–5000                                                             | 0             | Duration of test animation (ms) (deprecated, use `animation_speed`)                       |
| `test_animation_interval`    | 0–60                                                               | 0             | Interval for test animation in seconds (0 = disabled, deprecated)                         |
| `fps`                        | 1–540                                                              | 60            | Animation frame rate                                                                      |
| `input_fps`                  | 0–540                                                              | 0             | Input thread frame rate (0 = use `fps`)                                                   |
| `enable_scheduled_sleep`     | 0 or 1                                                             | 0             | Enable scheduled sleep mode                                                               |
| `sleep_begin`                | "00:00" – "23:59"                                                  | "00:00"       | Start time of scheduled sleep (24h format)                                                |
| `sleep_end`                  | "00:00" – "23:59"                                                  | "00:00"       | End time of scheduled sleep (24h format)                                                  |
| `idle_sleep_timeout`         | 0+                                                                 | 0             | Time of inactivity before entering sleep (0 = disabled) (in seconds)                      |
| `happy_kpm`                  | 0–10000                                                            | 0             | Minimum keystrokes per minute to trigger happy animation (0 = disabled)                   |
| `keyboard_device`            | Valid `/dev/input/*` path(s)                                       | \<No Device\> | Input device path (multiple entries allowed)                                              |
| `enable_antialiasing`        | 0 or 1                                                             | 1             | Enable bilinear interpolation for smooth scaling (Bongocat and MS Agent only)             |
| `enable_debug`               | 0 or 1                                                             | 0             | Enable debug logging                                                                      |
| `monitor`                    | Monitor name                                                       | Auto-detect   | Which monitor to display on (e.g., "eDP-1", "HDMI-A-1")                                   |
| `random`                     | 0 or 1                                                             | 0             | Randomize `animation_index` (`animation_name` needs to be set as base sprite sheet set)   |
| `random_on_reload`           | 0 or 1                                                             | 0             | Randomize `animation_index` when reloading config (`random` needs to be `1`)              |
| `update_rate`                | 0–10000                                                            | 0             | Check (CPU) states rate (0 = disabled) (in milliseconds)                                  |
| `cpu_threshold`              | 0–100                                                              | 0             | Threshold of CPU usage for triggering work animation (0 = disabled)                       |
| `movement_radius`            | 0-8000                                                             | 0             | Radius of moving area (0 = disabled)                                                      |
| `movement_speed`             | 0–5000                                                             | 0             | Movement speed (0 = disabled)                                                             |
| `enable_movement_debug`      | 0 or 1                                                             | 0             | Show Movement area                                                                        |
| `cpu_running_factor`         | 0.0–50.0                                                           | 0             | Speed up factor for 100% CPU, it's linear so the animation slowly speed up (0 = disabled) |
| `evolution`                  | 0 or "normal", "program_start", "uptime"                           | 0             | Animation change over time (0 = disabled)                                                 |
| `evolution_speed_factor`     | 0.0–5000.0                                                         | 0             | Speed up factor for evolution time (0 = disabled)                                         |

#### Available Sprites (`animation_name`)

See man pages for more details and full list:

- [Bongocat 😺](fragments/set-bongocat.md)
- [MS Agent 📎](fragments/set-ms-agent.md) 
- [Pokémon 🐭](fragments/set-pkmn.md)
- [Misc 🐈‍](fragments/set-misc.md)

##### Bongocat 😺

SVG-based rendering (pixel-perfect at any size). No need for `enable_antialiasing`.

##### Digimon 🦖 - Variety of V-Pets

- [Original](fragments/set-dm.md)
- [Pendulum Original](fragments/set-pen.md)
- [20th Anniversary](fragments/set-dm20.md)
- [Pendulum Ver.20th](fragments/set-pen20.md)
- [X](docs/fragments/set-dmx.md)
- [Colored](fragments/set-dmc.md)

> When building with ALL assets, use full names to avoid conflicts: `dm:Greymon`, `dm20:Greymon`, `dmc:Greymon`

##### Pokémon 🐭 - up to Gen 5 + Mystery Dungeon sprites

`wpets-all` and `wpets-pkmn` includes up to Gen. 5.
[Pokémon Mystery Dungeon](fragments/set-pmd.md) sprites are bundled in `wpets-pkmn`, not in `wpets-all`: `pmd:Pikachu`

_Best to disable antialiasing (`enable_antialiasing=0`) for pixel-perfect scaling_

##### MS Agent 📎 - Your Classic Microsoft Companion

While only Clippy is bundled in `wpets-all`, the other MS Agent friends are bundled in `wpets-ms-agent`: `Links`


#### Evolution (`evolution`)

Sprites change form over time.
Trigger modes:
 - `normal` - measure time since kast evolution
 - `program_start` - since program start
 - `uptime` - since uptime

_Only available for Digimon and Pokémon._ 
See [evolution docs](fragments/evol-all.md).

#### Custom Sprite Sheet (`custom_...`)

Use custom sprite sheet at runtime make your own pets

Set `animation_name=custom` and point `custom_sprite_sheet_filename` to your PNG sprite sheet. Full frame/row control per animation state:

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


*You can find more config- and sprite-sheet examples: [here](../examples/custom-sprite-sheets).*