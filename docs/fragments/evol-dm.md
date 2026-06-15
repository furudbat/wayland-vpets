
## EVOLUTION

Evolution timing and available evolution paths depend on the selected sprite set.
This feature is only available Digimon.
Some evolution paths may be unavailable due to missing sprite sheets.

- **evolution**: Evolution mode selector (0 = disabled).
    normal - Evolution occurs relative to the previous evolution stage.
    program - Evolution timing is based on program start time.
    uptime - Evolution timing is based on system uptime (time since boot).
- **evolution_speed_factor**: Multiplies evolution speed.
    1.0 = normal speed
    2.0 = twice as fast
    0.5 = half speed

### Evolution Timers

Evolution occurs automatically after the required amount of time has elapsed:

**Digimon**

| Stage    | dm     | dm20   | dmx    | pen   | pen20  |
| -------- | ------ | ------ | ------ | ----- | ------ |
| Digitama | 1 min  | 1 min  | 1 min  | 1 min | 1 min  |
| Baby I   | 10 min | 10 min | 10 min | 1 h   | 10 min |
| Baby II  | 6 h    | 6 h    | 12 h   | 16 h  | 12 h   |
| Child    | 24 h   | 24 h   | 24 h   | 20 h  | 24 h   |
| Adult    | 36 h   | 36 h   | 32 h   | 60 h  | 40 h   |
| Perfect  | 48 h   | 48 h   | 40 h   | 68 h  | 48 h   |
| Ultimate | —      | —      | 48 h   | —     | —      |

#### Notes

- The Humulos evolution guides are used as the primary reference for Digimon evolution requirements and progression data: https://humulos.com/digimon/
