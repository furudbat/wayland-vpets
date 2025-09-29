% BONGOCAT.CONF(5)
% 
% September 2025

# NAME

bongocat.conf - configuration file for Bongo Cat overlay application

# SYNOPSIS

`bongocat.conf` [options]

# DESCRIPTION

`bongocat.conf` contains settings to customize the Bongo Cat overlay, including position, animation, input, and display options.  
Comments start with `#`. Each setting follows the format:

    parameter=value

Changes to some settings require restarting Bongo Cat to take effect.



# POSITION SETTINGS

- **cat_x_offset**: Horizontal offset from center (pixels). Positive moves right, negative moves left. Behavior changes based on **cat_align** (`center`, `left`, `right`).
- **cat_y_offset**: Vertical offset (pixels). Positive moves down, negative moves up.
- **cat_align**: Horizontal alignment in the bar. Options: `center` (default), `left`, `right`.
- **cat_height**: Height of the cat in pixels. Width auto-calculated.

# MIRRORING

- **mirror_x**: Flip cat horizontally (0 = off, 1 = on).
- **mirror_y**: Flip cat vertically (0 = off, 1 = on).

# ANTI-ALIASING

- **enable_antialiasing**: Smooth scaling using bilinear interpolation (0 = off, 1 = on).

# SIZE SETTINGS

- **overlay_height**: Height of overlay bar (pixels).
- **overlay_position**: Screen position of overlay. Options: `top`, `bottom`.
- **overlay_layer**: Layer of overlay. Options: `overlay`, `top`, `bottom` or `background`.

# FRAME RATE

- **fps**: Animation frames per second.
- **input_fps**: Input thread frame rate (optional, 0 = use fps).

# TRANSPARENCY

- **overlay_opacity**: Background opacity (0–255).

# DEBUG

- **enable_debug**: Show debug messages (0 = off, 1 = on).

# INPUT DEVICES

- **keyboard_device**: Input device path (can specify multiple).  

## Example

      keyboard_device=/dev/input/event4     # Keyboard
      keyboard_device=/dev/input/event20    # External/Bluetooth keyboard

## Example with devices by-id

      keyboard_device=/dev/input/by-id/usb-MY_KEYBOARD-event-kbd                                                          # MY_KEYBOARD  (/dev/input/event9)
      keyboard_device=/dev/input/by-id/usb-MY_KEYBOARD-event-if01                                                         # MY_KEYBOARD  Consumer Control (/dev/input/event10)
      keyboard_device=/dev/input/event11                                                                                  # MY_KEYBOARD  System Control
      keyboard_device=/dev/input/by-id/usb-MY_KEYBOARD-if01-event-kbd                                                     # MY_KEYBOARD  Keyboard (/dev/input/event12)

# MULTI-MONITOR

- **monitor**: Monitor to display Bongo Cat. Uses first available if unspecified.


# ANIMATION

- **animation_name**: Animation set. Examples: `bongocat`, `Clippy`, `Bulbasaur`. _(see below for full list)_
- **invert_color**: Invert colors for dark mode (0 = off, 1 = on).
- **random**: Random animation index (0 = off, 1 = on).
- **idle_frame**: Frame to use when idle (0–3 for Bongo Cat).
- **enable_scheduled_sleep**: Scheduled sleep mode (0 = off, 1 = on).
- **sleep_begin** / **sleep_end**: Start/end times for sleep mode (24-hour format).
- **idle_sleep_timeout**: Seconds of inactivity before sleep (0 = disabled).
- **happy_kpm**: Minimum keystrokes per minute to trigger happy animation.
- **keypress_duration**: Duration (ms) to display keypress animation.
- **idle_animation**: Enable idle animation (0 = off, 1 = on).
- **animation_speed**: Milliseconds per frame (0 = use FPS speed).
- ~~**test_animation_duration** / **test_animation_interval**~~: Deprecated, use **animation_speed** and **idle_animation**.
