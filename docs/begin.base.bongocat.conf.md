% BONGOCAT.CONF(5)
% 
% November 2026

# NAME

bongocat.conf - configuration file for Bongo Cat overlay application

# SYNOPSIS

`bongocat.conf`

# DESCRIPTION

`bongocat.conf` contains settings to customize the Bongo Cat overlay, including position, animation, input, and display options.  
Comments start with `#`. Each setting follows the format:

    parameter=value

Changes to some settings require restarting Bongo Cat to take effect.



## POSITION SETTINGS

- **cat_x_offset**: Horizontal offset from center (pixels). Positive moves right, negative moves left. Behavior changes based on **cat_align** (`center`, `left`, `right`).
- **cat_y_offset**: Vertical offset (pixels). Positive moves down, negative moves up.
- **cat_align**: Horizontal alignment in the bar. Options: `center` (default), `left`, `right`.
- **cat_height**: Height of the cat in pixels. Width is calculated automatically.

## SIZE SETTINGS

- **overlay_height**: Height of overlay bar (pixels).
- **overlay_position**: Screen position of overlay. Options: `top`, `bottom`.
- **overlay_layer**: Layer of overlay. Options: `overlay`, `top` (default), `bottom` or `background` (`layer` is a deprecated alias).
- **screen_width**: Override the detected screen width in pixels (0 = auto-detect).
- **disable_fullscreen_hide**: Keep the overlay visible when a fullscreen window is detected (0 = off, 1 = on).

_Some overlay settings require a restart of the application_  
_**overlay_height** should work on config reload, it may take a second to reappear_

## FRAME RATE

- **fps**: Animation frames per second (used when animation_speed = 0).
- **input_fps**: Input thread frame rate (optional, 0 = use fps).
- **audio_fps**: Audio thread update rate (optional, 0 = use fps).

## TRANSPARENCY

- **overlay_opacity**: Background opacity (0–255, default 0).

## DEBUG

- **enable_debug**: Show debug messages (0 = off, 1 = on).

## INPUT DEVICES

- **keyboard_device**: Input device path (can specify multiple).
- **keyboard_name**: Add every input device whose name contains this text (can specify multiple).
- **hotplug_scan_interval**: Seconds between rescans for new input devices (0 = scan once at startup, default 30).

### Example

      keyboard_device=/dev/input/event4     # Keyboard
      keyboard_device=/dev/input/event20    # External/Bluetooth keyboard

### Example with devices by-id

      keyboard_device=/dev/input/by-id/usb-MY_KEYBOARD-event-kbd                                                          # MY_KEYBOARD  (/dev/input/event9)
      keyboard_device=/dev/input/by-id/usb-MY_KEYBOARD-event-if01                                                         # MY_KEYBOARD  Consumer Control (/dev/input/event10)
      keyboard_device=/dev/input/event11                                                                                  # MY_KEYBOARD  System Control
      keyboard_device=/dev/input/by-id/usb-MY_KEYBOARD-if01-event-kbd                                                     # MY_KEYBOARD  Keyboard (/dev/input/event12)

## MULTI-MONITOR

- **monitor**: Monitor to display Bongo Cat on. Uses the first available if unspecified (alias: `output_name`).

## AUDIO

_Requires a build with the audio module (PipeWire + FFTW); see `ENABLE_AUDIO_MODULE` in CMakeLists.txt_

- **audio**: React to audio playing on a PipeWire sink (0 = off, 1 = on).
- **audio_sink**: Sink name to listen to, see `pactl list short sinks` (empty = default sink).
- **audio_happy_peak**: Fraction of visualizer bars (0.0–1.0) that must peak at once to trigger the happy animation (0 = disabled, default 0.6).
- **audio_fps**: Audio thread update rate, see FRAME RATE.


## MIRRORING

- **mirror_x**: Flip cat horizontally (0 = off, 1 = on).
- **mirror_y**: Flip cat vertically (0 = off, 1 = on).

## ANTI-ALIASING

- **enable_antialiasing**: Smooth scaling using bilinear interpolation (0 = off, 1 = on).
    - Recommended off for pixel sprites (Digimon, Pokémon)
    - Recommended on for MS Agent

## SPRITE

- **animation_name**: Animation set. Examples: `bongocat`, `Clippy`, `Bulbasaur`. _(see below for full list)_
- **invert_color**: Invert colors for dark mode (0 = off, 1 = on).
- **padding_x** / **padding_y**: Padding (pixels) around each frame when loading the sprite sheet (default 0).
- **idle_frame**: Frame to use when idle (0–3 for Bongo Cat), otherwise 0 or 1 should be the idle frames in the other sets.
- **idle_animation**: Enable idle animation (0 = off, 1 = on).
- **animation_speed**: Milliseconds per frame (0 = use FPS speed).
- ~~**test_animation_duration** / **test_animation_interval**~~: Deprecated, use **animation_speed** and **idle_animation**.

## INPUT REACTION

- **happy_kpm**: Minimum keystrokes per minute to trigger a happy animation.
- **keypress_duration**: Duration (ms) to display keypress animation.
- **enable_hand_mapping**: Left half of the keyboard triggers the left hand, right half the right hand (0 = random, 1 = on, default 1).

## RANDOMIZE

- **random**: Random animation index (0 = off, 1 = on).
- **random_on_reload**: Randomize animation index on config reload (0 = off, 1 = on).

## SLEEP

- **enable_scheduled_sleep**: Scheduled sleep mode (0 = off, 1 = on).
- **sleep_begin** / **sleep_end**: Start/end times for sleep mode (24-hour format).
- **idle_sleep_timeout**: Seconds of inactivity before sleep (0 = disabled).

## MOVEMENT

- **movement_radius**: Moving area, the radius from center (in px; 0 = disabled).
- **movement_speed**: Traveling distance per movement animation (in px).
- **movement_wait_factor**: Pause after a movement: `movement_speed * movement_wait_factor` (default 5.1).
- **enable_movement_debug**: Show moving area in _red_ (0 = off, 1 = on).

## CPU

- **update_rate**: Update rate for the CPU watcher (ms) (0 = disabled).
- **cpu_threshold**: Threshold of avg. CPU usage for triggering the working animation (%) (0 = disabled).

## RUNNING

- **cpu_running_factor**: Speed-up factor (for `animation_speed`) when CPU reaches 100% usage (0.0–50.0) (0 = disabled).

## CUSTOM SPRITE SHEET

_**animation_name**: needs to be "custom"_

- **custom_**: For the full list of custom options and examples, see the section "Custom Sprite Sheets" in `bongocat-all(1)`.