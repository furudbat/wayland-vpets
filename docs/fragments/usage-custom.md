## Custom Sprite Sheets

Custom sprite sheets has a full animation per row.
To determine the number of rows, the number of frames needs to be provided per row.

- `Idle` -- Idle Pose
- `Boring` -- Boring animation for inactivity
- `StartWriting` -- First keystroke
- `Writing` -- Keep Typing (looping)
- `EndWriting` -- After last keystroke (return to Idle pose)
- `Happy` -- Show Happy animation when KPM is reached, while writing
- `ASleep` -- Start falling asleep
- `Sleep` -- Sleep (looping)
- `WakeUp` -- After sleep (back to Idle pose)
- `StartWorking` -- Start seen spike in CPU usage
- `Working` -- CPU usage over threshold (looping)
- `EndWorking` -- CPU usage under threshold (cooldown)
- `StartMoving` -- Start moving
- `Moving` -- Moving (looping)
- `EndMoving` -- Stop moving
- `StartRunning` -- Start running
- `Running` -- Running (looping)
- `EndRunning` -- Stop running

Rows can be skipped by not providing the frames/columns, but the order of the rows needs to be the same.

_**animation_name** needs to be "custom"_

- **custom_sprite_sheet_filename**: Path to the custom sprite sheet image (**must be png**)
- **custom_idle_frames**: Number of frames for idle animation (0 = disabled)
- **custom_boring_frames**: Number of frames for boring animation (0 = disabled)
- **custom_start_writing_frames**: Number of frames for start writing animation (0 = disabled)
- **custom_writing_frames**: Number of frames for writing animation (0 = disabled)
- **custom_end_writing_frames**: Number of frames for end writing animation (0 = disabled)
- **custom_happy_frames**: Number of frames for happy animation (0 = disabled)
- **custom_asleep_frames**: Number of frames for falling asleep animation (0 = disabled)
- **custom_sleep_frames**: Number of frames for sleeping animation (0 = disabled)
- **custom_wake_up_frames**: Number of frames for waking up animation (0 = disabled)
- **custom_start_working_frames**: Number of frames for start working animation (0 = disabled)
- **custom_working_frames**: Number of frames for working animation (0 = disabled)
- **custom_end_working_frames**: Number of frames for end working animation (0 = disabled)
- **custom_start_moving_frames**: Number of frames for start moving animation (0 = disabled)
- **custom_moving_frames**: Number of frames for moving animation (0 = disabled)
- **custom_end_moving_frames**: Number of frames for end moving animation (0 = disabled)
- **custom_toggle_writing_frames**: Toggle writing frames when writing (`custom_writing_frames` must be `2`) (default; -1 = auto)
- **custom_toggle_writing_frames_random**: Randomize writing frames on start writing (`custom_writing_frames` must be `2`) (default; -1 = auto)
- **custom_mirror_x_moving**: Mirror frames horizontally when moving (default; -1 = ignore)
- **custom_idle_row**: Row number for idle animation in sprite sheet (default; -1 = auto)
- **custom_boring_row**: Row number for boring animation (default; -1 = auto)
- **custom_start_writing_row**: Row number for start writing animation (default; -1 = auto)
- **custom_writing_row**: Row number for writing animation (default; -1 = auto)
- **custom_end_writing_row**: Row number for end writing animation (default; -1 = auto)
- **custom_happy_row**: Row number for happy animation (default; -1 = auto)
- **custom_asleep_row**: Row number for asleep animation (default; -1 = auto)
- **custom_sleep_row**: Row number for sleep animation (default; -1 = auto)
- **custom_wake_up_row**: Row number for wake-up animation (default; -1 = auto)
- **custom_start_working_row**: Row number for start working animation (default; -1 = auto)
- **custom_working_row**: Row number for working animation (default; -1 = auto)
- **custom_end_working_row**: Row number for end working animation (default; -1 = auto)
- **custom_start_moving_row**: Row number for start moving animation (default; -1 = auto)
- **custom_moving_row**: Row number for moving animation (default; -1 = auto)
- **custom_end_moving_row**: Row number for end moving animation (default; -1 = auto)


### General Example

**Sprite Sheet**

| Idle 1     | Idle 2     |          |          |
|------------|------------|----------|----------|
| Boring 1   | Boring 2   | Boring 3 | Boring 4 |
| Writing 1  | Writing 2  |          |          |
| Sleeping 1 | Sleeping 2 |          |          |
| Wake Up 1  |            |          |          |
| Moving 1   | Moving 2   |          |          |

**Sprite Sheet Settings**
- Idle = 1 frames
- Boring = 4 frames
- Writing = 2 frames
- Sleeping = 2 frames
- Wake Up = 1 frame
- Moving = 2 frame

`Idle`, `Writing`, `Sleeping` and `Moving` animations are set.
No `StartWriting` and `EndWriting` animation are provided when start typing, directly play the `Writing` animation.
`Sleeping` and `Wake Up` animation are provided so "Sleeping Mode" feature can be used.
If rows and animations are missing, some features can't be used, for example Working feature is disabled.
`Boring` animation are played after inactivity and before going to sleep.
`Moving` feature available and can can be enabled with moving options (see config `movement` options).


### Neko

```ini
# Sprite Sheet Settings
animation_name=custom
custom_sprite_sheet_filename=neko.png
custom_idle_frames=2
custom_boring_frames=2
custom_writing_frames=2
custom_happy_frames=2
custom_asleep_frames=2
custom_sleep_frames=2
custom_wake_up_frames=1
custom_working_frames=2
custom_moving_frames=2
animation_speed=500
```

### skink

```ini
# Sprite Sheet Settings
animation_name=custom
custom_sprite_sheet_filename=skink.png
custom_idle_frames=2
custom_moving_frames=4
animation_speed=800
```

### Blue witch

_no writing animation, but with movement and more_

```ini
# Sprite Sheet Settings
animation_name=custom
custom_sprite_sheet_filename=witch.png
custom_idle_frames=6
custom_asleep_frames=12
custom_sleep_frames=1
custom_wake_up_frames=12
custom_working_frames=5
custom_moving_frames=8
custom_mirror_x_moving=1
animation_speed=250
```

_flip moving frames so the move direction is correct_

### ferret

```ini
# Sprite Sheet Settings
animation_name=custom
custom_sprite_sheet_filename=ferret.png
custom_idle_frames=8
custom_boring_frames=8
custom_writing_frames=8
custom_sleep_frames=8
custom_working_frames=8
custom_moving_frames=8
custom_mirror_x_moving=1
animation_speed=200
```

### RunCat

```ini
# Sprite Sheet Settings
animation_name=custom
custom_sprite_sheet_filename=runcat.png
custom_idle_row=1
custom_idle_frames=1
custom_running_row=1
custom_running_frames=5
custom_rows=1
animation_speed=250
```

### Know issues

#### extra sprite when sprite is flipping (moving)

Please add some left and right empty padding in your frames.
Doing to some rounding error, when flipping the frame, some pixels can be visible from the nearer frames.