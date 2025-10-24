# Assets

## Sprite Sheet Formats

## bongo-cat

4 lose frames, put together at runtime into one sprite sheet.

Cols: 4  
Rows: 1
Frame Size: 864x360px  

- `both-up` -- Idle pose
- `left-down` -- input animation (frame 1)
- `right-down` -- input animation (frame 1)
- `both-down` -- use for sleep

_I kept it lose so it's compatible with the old bongocat_

### dm/pen

Custom digimon sprite sheet format (I used in my other projects).  
Single row with all frames, optional frames at the end, cols can vary.

Cols: 9 - 15  
Rows: 1
Frame Size: 64x64px

- `idle1` -- Idle animation (frame 1)
- `idle2` -- Idle animation (frame 2)
- `angry` -- Angry _(unused)_
- `down1` -- Sick (frame 1) _(unused)_
- `happy` -- Happy (for KPM animation)
- `eat1` -- Eating (frame 1) _(unused)_
- `sleep1` -- Sleep, use for sleep animation (frame 1), fallback to `down1` if not exists
- `refuse` -- Nope, Refuse _(unused)_
- `sad` -- Lose _(unused)_
- `down2` -- Sick, Lose (frame 2) _(unused)_ (optional)
- `eat2` -- Eat (frame 2) _(unused)_ (optional)
- `sleep2` -- Sleep (frame 2) (optional)
- `attack` -- Attack (use for react to CPU usage), fallback to `angry` (optional)
- `movement1` -- Moving, Walking animation (frame 1) (optional)
- `movement2` -- Moving, Walking animation (frame 2) (optional)

_(I choose this format, so I can fall back to frames when some frames don't exist like `sleep`, I could fall back to `down`)_

### ms_agent

Custom MS Agent sprite sheet, each row is a full animation.

Cols: varies
Rows: 6 - 12
Frame Size: 96x96px - 128x128px

- `Idle`/`Boring` -- Idle Pose (First frame), Boring animation for inactivity
- `StartWriting` -- First keystroke
- `Writing` -- Keep Typing (looping)
- `EndWriting` -- After last keystroke (return to Idle pose)
- `Sleep` -- Start falling asleep (last frame for freeze/in sleep mode)
- `WakeUp` -- After sleep (back to Idle pose)
- `StartWorking` -- Start seen spike in CPU usage _(unused)_ (optional)
- `Working` -- CPU usage over threshold (looping) _(unused)_ (optional)
- `EndWorking` -- CPU usage under threshold _(unused)_ (optional)
- `StartMoving` -- (optional)
- `Moving` -- (optional)
- `EndMoving` -- (optional)

### pkmn

Simple 2 frame sprite sheet with idle animation. _(Originated from the animation from the PC Box)_

Cols: 2  
Rows: 1  
Frame Size: varies from 22x22 - 32x32px

- `idle1`
- `idle2`


### custom/misc

Custom and misc sprite sheets, each row is a full animation.
Number of frames needs to be provided per row.

- `Idle` -- Idle Pose
- `Boring` -- Boring animation for inactivity
- `StartWriting` -- First keystroke
- `Writing` -- Keep Typing (looping)
- `EndWriting` -- After last keystroke (return to Idle pose)
- `Happy` -- Show Happy animation when KPM is reached, while writing
- `FallAsleep` -- Start falling asleep
- `Sleep` -- Sleep (looping)
- `WakeUp` -- After sleep (back to Idle pose)
- `StartWorking` -- Start seen spike in CPU usage
- `Working` -- CPU usage over threshold (looping)
- `EndWorking` -- CPU usage under threshold (cooldown)
- `StartMoving` -- Start Moving
- `Moving` -- Moving (looping)
- `EndMoving` -- Stop moving

Rows can be skipped by not providing the columns, but order needs to be the same.

#### Example

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

`Idle` and `Writing` should be required.
No `StartWriting` and `EndWriting` animation are played when start typing, directly start the `Writing` animation.
`Sleeping` and `Wake Up` animation are provided so "Sleeping Mode" feature can be used.
If rows and animations are missing, some features can't be used, for example Working feature is disabled.
`Boring` animation are played after inactivity and before going to sleep.
Moving feature can be enabled (see config `movement` options).

See [custom sprite sheets](../examples/custom-sprite-sheets) for custom sprite and config settings.