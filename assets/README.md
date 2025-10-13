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
