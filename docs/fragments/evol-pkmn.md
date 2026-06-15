
## EVOLUTION

Evolution timing and available evolution paths depend on the selected sprite set.
This feature is only available Pokemon.
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

**Pokémon**

For Pokémon, each hour of age corresponds to 2 Levels. Evolution occurs when the Pokémon reaches its evolution level.
