# Custom Sprite Sheets

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


## General Example

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


## Neko

![neko sprite sheet](neko.png)

- Idle animation (2 frames)
- Boring animation (2 frames)
- Writing animation (2 frames)
- Happy animation (2 frames)
- Start Sleeping animation (2 frames)
- Sleeping animation (2 frames)
- Wake up animation (1 frame)
- Working animation (2 frames)
- Moving animation (2 frames)

```ini
# Sprite Sheet Settings
animation_name=custom
```

## skink

[skink](https://thestarvingartificer.itch.io/blue-tongued-skink) by TheStarvingArtificer

_minimal moving example, frames can vary_

![skink sprite sheet](skink.png)

- Idle animation (2 frames)
- Moving animation (4 frames)

```ini
# Sprite Sheet Settings
animation_name=custom
```


## Know issues

### extra sprite when sprite is flipping (moving)

Please add some left and right empty padding in your frames.
Doing to some rounding error, when flipping the frame, some pixels can be visible from the nearer frames.